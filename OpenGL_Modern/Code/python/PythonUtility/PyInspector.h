#pragma once

namespace pybind11 {
	class object; 
}

namespace Bwt
{
	class PyInspector 
	{
	public:
		enum class PyType {
			Function,
			Class,
			Module,
			Integer,
			Float,
			String,
			List,
			Dict,
			Tuple,
			Set,
			Bool,
			None,
			Bytes,
			Callable,
			Other
		};

		static PyType get_type(const pybind11::object& obj);
		static const char* TypeToStr(PyType type);
	};
}