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
};
