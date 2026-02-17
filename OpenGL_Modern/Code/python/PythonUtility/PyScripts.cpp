#include "PyInspector.h"
#include "PyScripts.h"

bool Bwt::PyScripts::InitModule(const char* filename)
{
	try
	{
		m_name = filename; // Get the Name (use for ? idk)

		m_module = pybind11::module_::import(filename); // Import module

		if (pybind11::hasattr(m_module, "__file__")) // Registre the file path for hotloading later
		{
			m_path = pybind11::str(m_module.attr("__file__"));
			m_lastWrite = std::filesystem::last_write_time(m_path);
			std::cout << "Full path: " << m_path << std::endl;
		}
		else {
			std::cout << "Module has no __file__ (built-in module?)" << std::endl;
		}

		pybind11::dict module_dict = m_module.attr("__dict__");// Get all attribues
		for (auto item : module_dict)
		{
			std::string name = pybind11::str(item.first);
			if (name.substr(0, 2) == "__") continue;

			pybind11::object obj = pybind11::reinterpret_borrow<pybind11::object>(item.second);

			AddObj(name, obj);
		}
		return true;
	}
	catch (const pybind11::error_already_set& e)
	{
		std::cerr << "Python error: " << e.what() << "\n";
		return false;
	}
}

void Bwt::PyScripts::AddObj(std::string name, pybind11::object& obj)
{
	switch (PyInspector::get_type(obj))
	{
	case PyInspector::PyType::Function:
		if (name == "Start")       m_Start = obj;
		else if (name == "Update") m_Update = obj;
		else if (name == "LateUpdate") m_LateUpdate = obj;
		else if (name == "FixedUpdate") m_FixedUpdate = obj;
		m_functions.insert_or_assign(name, obj);
		break;
	case PyInspector::PyType::Class:
		m_functions.insert_or_assign(name, obj);
		break;
	default:
		std::cerr << "[Python] Not handled obj" << name << " : " << PyInspector::TypeToStr(PyInspector::get_type(obj)) << "\n";
		break;
	}
}

pybind11::object Bwt::PyScripts::GetFunction(const std::string& name)
{
	auto it = m_functions.find(name);
	if (it != m_functions.end()) {
		return it->second;
	}
	return pybind11::none();
}

bool Bwt::PyScripts::Reload()
{
	if (m_path.empty()) return false;

	try
	{
		pybind11::module_ importlib = pybind11::module_::import("importlib"); // Reload lib
		m_module = importlib.attr("reload")(m_module);

		// Re-scan
		m_functions.clear();
		m_classes.clear();
		m_variables.clear();

		pybind11::dict module_dict = m_module.attr("__dict__");
		for (auto item : module_dict)
		{
			std::string name = pybind11::str(item.first);
			if (name.substr(0, 2) == "__") continue;

			pybind11::object obj = pybind11::reinterpret_borrow<pybind11::object>(item.second);

			AddObj(name, obj);
		}

		// Update Time
		m_lastWrite = std::filesystem::last_write_time(m_path);
		return true;
	}
	catch (const pybind11::error_already_set& e)
	{
		std::cerr << "Reload failed: " << e.what() << "\n";
		return false;
	}
}

bool Bwt::PyScripts::CheckAndReload()
{
	try
	{
		if (!std::filesystem::exists(m_path))
		{
			std::cout << "File doesn't exist : " << m_path << std::endl;
			return false;
		}

		auto currentWrite = std::filesystem::last_write_time(m_path);

		if (currentWrite != m_lastWrite)
		{
			m_lastWrite = currentWrite;
			return Reload();
		}
	}
	catch (const std::filesystem::filesystem_error& e)
	{
		std::cerr << "Filesystem error: " << e.what() << std::endl;
	}

	return false;
}


void Bwt::PyScripts::Start()
{
	if (m_Start && !m_Start.is_none())
		m_Start();
}

void Bwt::PyScripts::Update(float deltaTime)
{
	try {
		if (m_Update && !m_Update.is_none())
			m_Update(deltaTime);
	}
	catch (const pybind11::error_already_set& e)
	{
		std::cerr << "Python exception in " << m_name << ": " << e.what() << std::endl;
	}
}

void Bwt::PyScripts::FixedUpdate(float deltaTime)
{
	if (m_FixedUpdate && !m_FixedUpdate.is_none())
		m_FixedUpdate(deltaTime);
}

void Bwt::PyScripts::LateUpdate()
{
	if (m_LateUpdate && !m_LateUpdate.is_none())
		m_LateUpdate();
}
