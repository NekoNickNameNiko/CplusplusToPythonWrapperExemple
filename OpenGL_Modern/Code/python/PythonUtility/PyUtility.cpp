#include "PyUtility.h"
#include <iostream>
#include <filesystem>
#include <string>
#include "PyScripts.h"
#include "PyInspector.h"

#include <libloaderapi.h>
namespace fs = std::filesystem;

std::unique_ptr<pybind11::scoped_interpreter> Bwt::PyUtility::m_interpreter;
bool Bwt::PyUtility::m_initialized = false;
std::unordered_map<std::string, std::unique_ptr<Bwt::PyScripts>> Bwt::PyUtility::m_pyScripts;
std::vector<std::string> Bwt::PyUtility::m_paths;


// Jacob-Tate/snippet.cpp
// https://gist.github.com/Jacob-Tate/7b326a086cf3f9d46e32315841101109
// 2019-11-19
static std::filesystem::path abs_exe_directory()
{
#if defined(_MSC_VER)
	wchar_t path[FILENAME_MAX] = { 0 };
	GetModuleFileNameW(nullptr, path, FILENAME_MAX);
	return std::filesystem::path(path).parent_path().string();
#else
	char path[FILENAME_MAX];
	ssize_t count = readlink("/proc/self/exe", path, FILENAME_MAX);
	return std::filesystem::path(std::string(path, (count > 0) ? count : 0)).parent_path().string();
#endif
}

bool Bwt::PyUtility::Initialize()
{
	if (!m_initialized)
	{
		try {
			m_interpreter = std::make_unique<pybind11::scoped_interpreter>();

			Bwt::PyUtility::AddNewPath(""); // add default path for python script
			// Configuration une seule fois
			pybind11::module_ sys = pybind11::module_::import("sys");


			fs::path PythonDir = "Code/python/PyScripts"; // Only for IDE
			fs::path exePythonDir = abs_exe_directory() / "Python";
			fs::create_directories(exePythonDir);

			for (const std::string& path : m_paths)
			{
				if (fs::exists(PythonDir))
				{
					sys.attr("path").attr("append")(fs::absolute(PythonDir / path).string()); // IDE mode
				}
				else if (fs::exists(exePythonDir))
				{
					sys.attr("path").attr("append")((exePythonDir / path).string()); // Runtime mode
				}
			}

			sys.attr("path").attr("append")(exePythonDir.string());

			// Get all path
			pybind11::list path_list = sys.attr("path");

			std::cout << "---- Python sys.path ----\n";
			for (auto item : path_list)
			{
				std::cout << pybind11::str(item).cast<std::string>() << "\n";
			}
			std::cout << "-------------------------\n";

			m_initialized = true;
			return true;
		}
		catch (const std::exception& e)
		{
			std::cerr << "Failed to initialize Python interpreter: " << e.what() << "\n";
			return false;
		}
	}
	return true;
}

void Bwt::PyUtility::Shutdown()
{
	m_interpreter.reset();
	m_initialized = false;
}

bool Bwt::PyUtility::AddNewPath(const std::string& path)
{
	if (!m_paths.emplace_back(path).empty())
		return true;
	return false;
}

bool Bwt::PyUtility::ExecuteScript(const std::string& name)
{
	try {
		pybind11::module_ script = pybind11::module::import(name.c_str());
		pybind11::exec(script);
		return true;
	}
	catch (const pybind11::error_already_set& e)
	{
		std::cerr << "Python error: " << e.what() << "\n";
	}
	return false;
}

bool Bwt::PyUtility::LoadModule(const std::string& name)
{
	try {
		std::unique_ptr<PyScripts> newScript = std::make_unique<PyScripts>();;

		if (!newScript->InitModule(name.c_str()))
			return false;
		m_pyScripts[name] = std::move(newScript);
		return true;
	}
	catch (const pybind11::error_already_set& e)
	{
		std::cerr << "Python error: " << e.what() << "\n";
	}
	return false;
}

Bwt::PyScripts* Bwt::PyUtility::GetModule(const std::string& name)
{
	auto script = m_pyScripts.find(name);
	if (script == m_pyScripts.end())
	{
		// Handle unloaded module call
		if (LoadModule(name))
			return m_pyScripts[name].get();
		throw std::runtime_error("Script doesn't exist or is not initialized");
	}
	return script->second.get();
}

int Bwt::PyUtility::HotReload()
{
	int scriptReloaded = 0;

	fs::path PythonDir = "Code/python/PyScripts"; // Only for IDE
	if (fs::exists(PythonDir))
	{
		pybind11::module_ sys = pybind11::module_::import("sys");
		for (const std::string& path : m_paths)
		{
			sys.attr("path").attr("append")(fs::absolute(PythonDir / path).string()); // IDE mode
		}
	}

	for (auto it = m_pyScripts.begin(); it != m_pyScripts.end(); it++)
	{
		if (it->second.get()->CheckAndReload())
			scriptReloaded++;
	}
	if (scriptReloaded != 0)
		std::cout << scriptReloaded << " has been Hot Reloaded" << std::endl;
	return scriptReloaded;
}

void Bwt::PyUtility::Print(const char* filename)
{
	try
	{
		pybind11::module_ module = pybind11::module_::import(filename);
		pybind11::list attrs = module.attr("__dir__")();

		for (auto item : attrs)
		{
			std::string name = pybind11::str(item);
			pybind11::object attr = module.attr(name.c_str());
			if (name.substr(0, 2) == "__") continue;
			std::cout << "[Python]" << PyInspector::TypeToStr(PyInspector::get_type(attr)) << " found : " << name << "\n";
		}
	}
	catch (const pybind11::error_already_set& e)
	{
		std::cerr << "Python error: " << e.what() << "\n";
	}
}
