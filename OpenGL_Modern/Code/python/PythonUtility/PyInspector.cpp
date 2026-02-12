#include "PyInspector.h"
#include <pybind11/embed.h>

Bwt::PyInspector::PyType Bwt::PyInspector::get_type(const pybind11::object& obj)
{
	if (obj.is_none()) return PyType::None;
	if (pybind11::isinstance<pybind11::type>(obj)) return PyType::Class;
	if (pybind11::isinstance<pybind11::module>(obj)) return PyType::Module;
	if (pybind11::isinstance<pybind11::function>(obj)) return PyType::Function;
	if (pybind11::isinstance<pybind11::int_>(obj)) return PyType::Integer;
	if (pybind11::isinstance<pybind11::float_>(obj)) return PyType::Float;
	if (pybind11::isinstance<pybind11::str>(obj)) return PyType::String;
	if (pybind11::isinstance<pybind11::list>(obj)) return PyType::List;
	if (pybind11::isinstance<pybind11::dict>(obj)) return PyType::Dict;
	if (pybind11::isinstance<pybind11::tuple>(obj)) return PyType::Tuple;
	if (pybind11::isinstance<pybind11::set>(obj)) return PyType::Set;
	if (pybind11::isinstance<pybind11::bool_>(obj)) return PyType::Bool;
	if (pybind11::isinstance<pybind11::bytes>(obj)) return PyType::Bytes;
	if (pybind11::hasattr(obj, "__call__")) return PyType::Callable;
	return PyType::Other;
}

const char* Bwt::PyInspector::TypeToStr(PyType type)
{
	switch (type) {
	case PyType::Function: return "function";
	case PyType::Class: return "class";
	case PyType::Module: return "module";
	case PyType::Integer: return "int";
	case PyType::Float: return "float";
	case PyType::String: return "str";
	case PyType::List: return "list";
	case PyType::Dict: return "dict";
	case PyType::Tuple: return "tuple";
	case PyType::Set: return "set";
	case PyType::Bool: return "bool";
	case PyType::None: return "NoneType";
	case PyType::Bytes: return "bytes";
	case PyType::Callable: return "callable";
	default: return "unknown";
	}
}
