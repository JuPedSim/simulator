#include "simulation_binding.hpp"

#include "geometry/world_builder.hpp"

#include <memory>
#include <pybind11/pybind11.h>
#include <simulation.hpp>

void bind_simulation(pybind11::module_ & m)
{
    pybind11::class_<jps::Simulation>(m, "Simulation")
        .def(pybind11::init([] {
            return std::make_unique<jps::Simulation>(std::make_unique<jps::WorldBuilder>());
        }))
        .def("compute_next_step", &jps::Simulation::computeNextStep)
        .def("add_agent", &jps::Simulation::addAgent)
        .def(
            "get_world_builder",
            &jps::Simulation::getWorldBuilder,
            pybind11::return_value_policy::reference_internal);
}
