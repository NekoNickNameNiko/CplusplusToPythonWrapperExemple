#include <pybind11/embed.h>
#include "camera.h"
#include "../../Toolbox3D/Include/Vector4.h"
#include "transform.h"

namespace py = pybind11;
using namespace Bwt::LowRenderer;

bool IsKeyDown(int key)
{
	GLFWwindow* window = glfwGetCurrentContext();
	if (window)
		return glfwGetKey(window, key) == GLFW_PRESS;
	else
		return false;
}

PYBIND11_EMBEDDED_MODULE(BwtEngine, m)
{
	m.doc() = "Module de bind des classes c++ vers python";

	m.def("IsKeyDown", &IsKeyDown);

	// forward/back/left/right
	m.attr("Key_Z") = GLFW_KEY_Z;
	m.attr("Key_S") = GLFW_KEY_S;
	m.attr("Key_Q") = GLFW_KEY_Q;
	m.attr("Key_D") = GLFW_KEY_D;
	// down/up
	m.attr("Key_A") = GLFW_KEY_A;
	m.attr("Key_E") = GLFW_KEY_E;
	// rotate left/right
	m.attr("Key_W") = GLFW_KEY_W;
	m.attr("Key_X") = GLFW_KEY_X;

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