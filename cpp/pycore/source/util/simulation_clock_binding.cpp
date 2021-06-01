#include "jpsexception_binding.hpp"
#include "util/simulation_clock.hpp"

#include <pybind11/chrono.h>

void bind_simulation_clock(pybind11::module_ & m)
{
    pybind11::class_<SimulationClock>(m, "SimulationClock")
        // The check for negative milliseconds needs to be done on python side before calling the
        // constructor, due to the implementation of datatime.timedelta
        .def(pybind11::init<uint64_t, std::chrono::milliseconds>())
        .def_property_readonly("deltaT", &SimulationClock::getDeltaT)
        .def_property_readonly("steps", &SimulationClock::getMaxSteps)
        .def_property_readonly("current_step", &SimulationClock::getCurrentStep)
        .def_property_readonly("current_time", &SimulationClock::getCurrentTime)
        .def("advance", &SimulationClock::advance);
}
