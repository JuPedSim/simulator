#pragma once

#include "agent/agent.hpp"

#include <vector>

namespace jps
{
/// SimulationData handles all data related to a single simulation
class SimulationData
{
    std::vector<Agent> m_agents;
};

} // namespace jps
