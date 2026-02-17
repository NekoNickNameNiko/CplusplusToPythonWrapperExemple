#pragma once
#include <pybind11/embed.h>
#include <memory>
#include <map>
#include <iostream>

#define _AMD64_ 1
namespace Bwt
{
	class PyScripts;

	class PyUtility
	{
	private:
		static std::unique_ptr<pybind11::scoped_interpreter> m_interpreter;
		static bool m_initialized;
		static std::unordered_map<std::string, std::unique_ptr<PyScripts>> m_pyScripts;
		static std::vector<std::string> m_paths;
	public:
		static bool Initialize();
		static void Shutdown();
		static bool AddNewPath(const std::string& path);
		static bool ExecuteScript(const std::string& name);
		static bool LoadModule(const std::string& name);
		static PyScripts* GetModule(const std::string& name);
		static int HotReload();
		static bool IsInitialized() { return m_initialized; }
		static void Print(const char* filename);
	};
}