#pragma once

#include "agent/agent.hpp"
#include "operational/result.hpp"
#include "tactical/result.hpp"
#include "util/unused.hpp"
namespace jps
{
class Simulation;

/// @brief Interface for operational models
///
/// An operational model is responsible for computing the movement of the agents within the
/// simulation based on the current target, geometry (walls, obstacles) and surrounding agents.
///
struct OperationalModelInterface {
    /// Sets up all needed data structures for the operational model
    ///
    /// @param p_simulation simulation context, including geometry
    virtual auto setup(/** const Simulation & p_simulation **/) -> void{};

    /// Computes the next position of the agents / an agent
    ///
    /// @param p_simulation simulation context, including geometry
    /// @param p_tactical_results result from the tactical level for the agent
    /// @param p_agent agent for whom the next position is computed
    ///
    /// @return
    virtual auto computeStep(
        Simulation const & p_simulation,
        TacticalModelResult const & p_tactical_results,
        Agent const & p_agent) const -> OperationalModelResult = 0;

    /// Update the global state of the operational model, e.g., when geometry is changed due
    /// to events or similar
    ///
    /// @param p_simulation
    virtual auto update(/** const Simulation & p_simulation **/) -> void{};

    /// Tears down everything needed in the operational model
    virtual auto tearDown() -> void{};
};

struct DummyOperationalModel : OperationalModelInterface {
    auto computeStep(
        Simulation const & p_simulation,
        TacticalModelResult const & p_tactical_results,
        Agent const & p_agent) const -> OperationalModelResult override
    {
        unused(p_simulation, p_tactical_results, p_agent);
        return {};
    }
};

} // namespace jps
