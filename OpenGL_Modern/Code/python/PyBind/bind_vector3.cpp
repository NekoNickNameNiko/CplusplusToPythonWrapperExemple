#include <pybind11/pybind11.h>
#include "../../Toolbox3D/Include/Vector3.h"

static void bind_Vector3(pybind11::module_& m)
{
    pybind11::class_<Bwt::Core::Maths::Vector3>(m, "Vector3")
        .def(pybind11::init<float, float, float>())
        .def_readwrite("x", &Bwt::Core::Maths::Vector3::x)
        .def_readwrite("y", &Bwt::Core::Maths::Vector3::y)
        .def_readwrite("z", &Bwt::Core::Maths::Vector3::z);
}
