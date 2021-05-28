#pragma once

#include "operational/result.hpp"
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
    virtual auto computeStep(/** const Simulation & p_simulation, const TacticalModelResult & p_tactical_results, const Agent & p_agent **/) const -> OperationalModelResult = 0;

    /// Update the global state of the operational model, e.g., when geometry is changed due
    /// to events or similar
    ///
    /// @param p_simulation
    virtual auto update(/** const Simulation & p_simulation **/) -> void{};

    /// Tears down everything needed in the operational model
    virtual auto tearDown() -> void{};
};

struct DummyOperationalModel : OperationalModelInterface {
    auto computeStep(/** const Simulation & p_simulation, const TacticalModelResult & p_tactical_results, const Agent & p_agent **/) const -> OperationalModelResult override
    {
        return OperationalModelResult{};
    }
};
