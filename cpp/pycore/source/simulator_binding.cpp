#include <pybind11/pybind11.h>
#include <simulation.hpp>

namespace py = pybind11;

PYBIND11_MODULE(jpscore, m)
{
    py::class_<jps::Simulation>(m, "Simulation")
        .def(py::init<>())
        .def("get", &jps::Simulation::getValue);
}
