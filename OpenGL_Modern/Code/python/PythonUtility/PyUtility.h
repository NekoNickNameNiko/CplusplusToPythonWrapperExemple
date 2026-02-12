#pragma once
#include <pybind11/embed.h>
#include <memory>
#include <map>
#include <iostream>

namespace Bwt
{
	class PyScripts;

	class PyUtility
	{
	private:
		static std::unique_ptr<pybind11::scoped_interpreter> m_interpreter;
		static bool m_initialized;
		static std::unordered_map<std::string, std::unique_ptr<PyScripts>> m_pyScripts;

	public:
		static bool Initialize();
		static void Shutdown();
		static bool ExecuteScript(std::string& name);
		static bool LoadModule(std::string& name);
		static PyScripts* GetModule(std::string& name);
		static void HotReload();
		static bool IsInitialized() { return m_initialized; }
		void Print(const char* filename);
	};
}