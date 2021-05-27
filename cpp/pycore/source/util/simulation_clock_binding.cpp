#include "jpsexception_binding.hpp"
#include "util/simulation_clock.hpp"

void bind_simulation_clock(pybind11::module_ & m)
{
    pybind11::class_<SimulationClock>(m, "SimulationClock")
        .def(pybind11::init<uint64_t, double>())
        .def_property_readonly("deltaT", &SimulationClock::getDeltaT)
        .def_property_readonly("steps", &SimulationClock::getMaxSteps)
        .def_property_readonly("currentStep", &SimulationClock::getCurrentStep)
        .def_property_readonly("currentTime", &SimulationClock::getCurrentTime)
        .def("advance", &SimulationClock::advance);
}
