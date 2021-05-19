#pragma once


#include <cstdint>

/// SimulationClock handles the simulation time and time steps
///
/// For fixed time steps the SimulationClock counts the current time step and computes the current
/// simulation time.
///
/// SimulationClock provides methods for python iterator bindings.
/// In Python we want to iterate over the timesteps of the simulation like:
/// ```for cur_step in simulation.steps():```
/// see
/// https://stackoverflow.com/questions/49257947/iterating-over-c-objects-wrapped-in-python-via-pybind11
/// and https://github.com/pybind/pybind11/blob/master/tests/test_sequences_and_iterators.cpp
class SimulationClock
{
    const std::uint64_t m_max_steps;
    const double m_delta_t;

    std::uint64_t m_current_step{0};

public:
    SimulationClock(std::uint64_t p_max_steps, double p_delta_t) :
        m_max_steps(p_max_steps), m_delta_t(p_delta_t){};
};
