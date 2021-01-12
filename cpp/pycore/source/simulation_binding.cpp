#include "simulation_binding.hpp"

#include <simulation.hpp>

void bind_simulation(pybind11::module_ & m)
{
    pybind11::class_<jps::Simulation>(m, "Simulation")
        .def(pybind11::init<>())
        .def("get", &jps::Simulation::getValue);
}
