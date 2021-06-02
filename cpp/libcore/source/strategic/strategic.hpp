#pragma once

#include "agent/agent.hpp"
#include "strategic/result.hpp"
#include "util/unused.hpp"

namespace jps
{
class Simulation;

/// @brief Interface for strategic models
///
/// A strategic model is responsible for deciding what the agent wants to do, e.g., go to an exit,
/// go to a store, wait, etc. For example a FSM, could be used to model the behavior of the agents.
///
struct StrategicModelInterface {
    /// Sets up all needed data structures for the strategic model
    virtual auto setup(/** const Simulation & p_simulation **/) -> void{};

    /// Determines the next goal of an agent
    ///
    /// @param p_simulation simulation context, including geometry
    /// @param p_agent agent for whom the goal is computed
    ///
    /// @return
    virtual auto computeStep(Simulation const & p_simulation, Agent const & p_agent) const
        -> StrategicModelResult = 0;

    /// Update the global state of the strategic model, e.g., when the geometry is changed or
    /// similar
    virtual auto update(/** const Simulation & p_simulation **/) -> void{};

    /// Tears down everything needed in the strategic model
    virtual auto tearDown(/** const Simulation & p_simulation **/) -> void{};
};
struct DummyStrategicModel : public StrategicModelInterface {
    auto computeStep(Simulation const & p_simulation, Agent const & p_agent) const
        -> StrategicModelResult override
    {
        unused(p_simulation, p_agent);
        return {};
    };
};
} // namespace jps
