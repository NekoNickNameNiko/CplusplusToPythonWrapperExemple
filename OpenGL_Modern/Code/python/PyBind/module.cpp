#include <pybind11/pybind11.h>
#include "bind_vector3.cpp"
#include "bind_camera.cpp"

void bind_Vector3(pybind11::module_& m);
void bind_Camera(pybind11::module_& m);

PYBIND11_MODULE(engine, m)
{
    bind_Vector3(m);
    bind_Camera(m);
}
