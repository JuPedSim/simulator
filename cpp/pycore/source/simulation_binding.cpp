#include "simulation_binding.hpp"

#include <pybind11/pybind11.h>
#include <simulation.hpp>

void bind_simulation(pybind11::module_ & m)
{
    pybind11::class_<jps::Simulation>(m, "Simulation")
        .def(pybind11::init<>())
        .def("get", &jps::Simulation::getValue)
        //.def("steps", [](jps::Simulation const & simulation) {
        //} )
        ;
}
