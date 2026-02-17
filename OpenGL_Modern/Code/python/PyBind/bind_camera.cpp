#include <pybind11/pybind11.h>
#include <camera.h>

static void bind_Camera(pybind11::module_& m)
{
    pybind11::class_<Bwt::LowRenderer::Camera>(m, "Camera")
        .def("move", &Bwt::LowRenderer::Camera::Move);
}