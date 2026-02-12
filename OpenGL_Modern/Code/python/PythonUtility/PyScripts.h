#pragma once

#include <pybind11/embed.h>
#include <memory>
#include <map>
#include <iostream>
#include <filesystem>

namespace Bwt
{
	class PyScripts
	{
		std::string m_name;
		std::string m_path;
		std::filesystem::file_time_type m_lastWrite;
		pybind11::module_ m_module;
		std::map<std::string, pybind11::object> m_functions;
		std::map<std::string, pybind11::object> m_classes;
		std::map<std::string, pybind11::object> m_variables;

	public:
		PyScripts() = default;
		~PyScripts() = default;

		bool InitModule(const char* filename);
		void AddObj(std::string name, pybind11::object& obj);
		pybind11::object GetFunction(const std::string& name);

		bool Reload();

		bool CheckAndReload();

		template<typename... Args>
		void Exec(const char* name, Args&&... args)
		{
			std::string _name = name;
			auto it = m_functions.find(_name);
			if (it == m_functions.end())
			{
				std::cout << _name << " : function doesn't exist or the syntax is not right" << std::endl;
				return;
			}

			pybind11::object& func = it->second;

			try {
				func(std::forward<Args>(args)...); // call Python function
			}
			catch (const pybind11::error_already_set& e)
			{
				std::cerr << "Python exception in " << _name << ": " << e.what() << std::endl;
			}
		}
	};
}