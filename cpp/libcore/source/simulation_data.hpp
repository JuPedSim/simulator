#pragma once

#include "agent/agent.hpp"
#include "util/simulation_clock.hpp"

#include <chrono>
#include <vector>

namespace jps
{
/// SimulationData handles all data related to a single simulation
struct SimulationData {
    std::vector<Agent> agents;
    // NOLINTNEXTLINE
    SimulationClock simulation_clock{10, std::chrono::milliseconds{10}};
};

} // namespace jps
