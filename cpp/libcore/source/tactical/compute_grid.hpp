#pragma once

#include "agent/agent.hpp"
#include "strategic/result.hpp"
#include "tactical/result.hpp"
#include "tactical/tactical.hpp"
#include <string>
#include "neighborhood/grid_2d.hpp"
#include "simulation.hpp"
#include "agent/agent.hpp"
#include "geometry/length_unit.hpp"

inline auto lengthUnitToIndex(LengthUnit p_lu, LengthUnit p_cellsize) -> std::int64_t
{
    return static_cast<std::int64_t>(std::floor(p_lu / p_cellsize));
}

class ComputeGrid{
    using AgentRef = std::reference_wrapper<Agent const>;
    using Agents   = std::deque<AgentRef>;

private:
    LengthUnit m_cell_size;
    Grid2D<Agents> m_grid;
    mutable std::shared_mutex m_grid_mutex;

public:
    /// Scans the room and returns a 2D Grid as return value
    /// @return 2D Grid
    /// @param &p_agent Reference to agent
   auto floodfill(jps::Agent &p_agent);

    /// Compute the next step (similar to the computeStep function from tactical.hpp)
    /// @param &p_simulation Reference to simulation
    /// @param &p_strategic_result Reference to result from the Strategic Level
    /// @param &p_agent Reference to agent
    /// @return
   auto computeNextStep(jps::Simulation &p_simulation, jps::StrategicModelResult &p_strategic_result, jps::Agent &p_agent);

    /// Sets up data structures for the strategic model
    /// @param &p_simulation Reference to simulation
    /// @return
    auto setup(jps::Simulation &p_simulation);

    /// Update global state
    /// @param &p_simulation Reference to simulation
    /// @return
    auto update(jps::Simulation &p_simulation);

    /// A copy from neighborhood_search.cpp
    /// just a test
    /// @param &p_agents Reference to a vector with agents (pedestrians)
    /// return
    auto updateNeighborhood(std::vector<Agent> const &p_agents);
};