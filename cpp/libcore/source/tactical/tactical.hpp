#pragma once

#include "tactical/result.hpp"
/// @brief Interface for tactical models
///
/// A tactical model is responsible for determining the desired direction an agent would move to
/// reach its desired target (via a strategic model).
///
struct TacticalModelInterface {
    /// Sets up all needed data structures for the strategic model
    virtual auto setup(/** const Simulation & p_simulation **/) -> void{};

    /// Determines the desired direction towards a specific goal
    /// Computes the next position of the agents / an agent
    ///
    /// @param p_simulation simulation context, including geometry
    /// @param p_tactical_results result from the strategic level for the agent
    /// @param p_agent agent for whom the next direction is computed
    ///
    /// @return
    virtual auto computeStep(/** const Simulation &, const StrategicModelResult & p_strategic_result, const Agent & p_agent **/) const -> TacticalModelResult = 0;

    /// Update the global state of the tactical model, e.g., when the geometry is changed or
    /// similar
    virtual auto update(/** const Simulation & p_simulation **/) -> void{};

    /// Tears down everything needed in the tactical model
    virtual auto tearDown(/** const Simulation & p_simulation **/) -> void{};
};

struct DummyTacticalModel : TacticalModelInterface {
    auto computeStep(/** const Simulation &, const StrategicModelResult & p_strategic_result, const Agent & p_agent **/) const  -> TacticalModelResult override
    {
        return {};
    };
};
