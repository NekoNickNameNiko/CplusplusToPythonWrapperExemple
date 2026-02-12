#include "PyInspector.h"
#include "PyScripts.h"

bool Bwt::PyScripts::InitModule(const char* filename)
{
	try
	{
		m_name = filename; // Get the Name (use for ? idk)

		m_module = pybind11::module_::import(filename); // Import module
		pybind11::list attrs = m_module.attr("__dir__")(); // Get all attribues

		if (pybind11::hasattr(m_module, "__file__")) // Registre the file path for hotloading later
		{
			m_path = pybind11::str(m_module.attr("__file__"));
			m_lastWrite = std::filesystem::last_write_time(m_path);
			std::cout << "Full path: " << m_path << std::endl;
		}
		else {
			std::cout << "Module has no __file__ (built-in module?)" << std::endl;
		}

		for (pybind11::handle item : attrs)
		{
			std::string name = pybind11::str(item);

			pybind11::object obj = m_module.attr(name.c_str());

			if (name.substr(0, 2) == "__") continue; // Ignore private variable

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
		m_functions.emplace(name, obj);
		break;
	case PyInspector::PyType::Class:
		m_functions.emplace(name, obj);
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

		pybind11::dict module_dict = m_module.attr("__dir__");
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
	if (std::filesystem::last_write_time(m_path) != m_lastWrite) {
		return Reload();
	}
	return false;
}
