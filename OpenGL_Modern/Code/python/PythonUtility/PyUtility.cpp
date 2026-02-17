#include "PyUtility.h"
#include <iostream>
#include <filesystem>
#include <string>
#include "PyScripts.h"
#include "PyInspector.h"

std::unique_ptr<pybind11::scoped_interpreter> Bwt::PyUtility::m_interpreter;
bool Bwt::PyUtility::m_initialized = false;
std::unordered_map<std::string, std::unique_ptr<Bwt::PyScripts>> Bwt::PyUtility::m_pyScripts;

bool Bwt::PyUtility::Initialize()
{
	if (!m_initialized)
	{
		try {
			m_interpreter = std::make_unique<pybind11::scoped_interpreter>();

			// Configuration une seule fois
			pybind11::module_ sys = pybind11::module_::import("sys");

			std::filesystem::path p = "Code/python";  // TODO : Change to list editable
			p = std::filesystem::absolute(p);

			sys.attr("path").attr("append")(p.string());

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
		catch (const std::exception& e) {
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

bool Bwt::PyUtility::ExecuteScript(std::string& name)
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
	for (auto it = m_pyScripts.begin() ; it != m_pyScripts.end(); it++)
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
