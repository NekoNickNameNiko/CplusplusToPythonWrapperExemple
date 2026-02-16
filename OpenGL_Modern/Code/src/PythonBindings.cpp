#include <pybind11/embed.h>
#include "camera.h"
#include "../../Toolbox3D/Include/Vector4.h"

namespace py = pybind11;
using namespace Bwt::LowRenderer;

PYBIND11_EMBEDDED_MODULE(BwtEngine, m)
{
	m.doc() = "Module de bind des classes c++ vers python";

	py::class_<Vector3>(m, "Vector3")
		.def(py::init<float, float, float>())
		.def_readwrite("x", &Vector3::x)
		.def_readwrite("y", &Vector3::y)
		.def_readwrite("z", &Vector3::z);

	py::class_<Camera>(m, "Camera")
		.def("Move", &Camera::Move)
		.def("Rotate", &Camera::Rotate)
		.def("Update", &Camera::Update)

		.def_readwrite("center", &Camera::center)
		.def_property_readonly("position", [](Camera& self) { return self.transform.position; });
}