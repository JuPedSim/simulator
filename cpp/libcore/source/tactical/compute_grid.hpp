#pragma once

#include "agent/agent.hpp"
#include "strategic/result.hpp"
#include "tactical/result.hpp"
#include "tactical/tactical.hpp"
#include <string>
#include "grid_2d.hpp"
#include <simulation.hpp>


class ComputeGrid{

private:


public:
    /// Scans the room and returns a 2D Grid as return value
    /// @return 2D Grid
   void floodfill();

    /// Compute the next step (similar to the computeStep function from tactical.hpp)
    /// @param &p_simulation Reference to simulation
    /// @param &p_strategic_result Reference to result from the Strategic Level
    /// @param &p_agent Reference to agent
    /// @return
   auto computeNextStep(jps::Simulation &p_simulation, jps::StrategicModelResult &p_strategic_result, jps::Agent &p_agent);
};