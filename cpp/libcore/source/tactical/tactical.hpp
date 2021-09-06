#pragma once

#include <sudo_plugin.h>
#include "agent/agent.hpp"
#include "strategic/result.hpp"
#include "tactical/result.hpp"
#include "shorthestpathtactical.hpp"
#include "ShortestPathTactical.hpp"

namespace jps
{
class Simulation;

    ShortestPathTactical shortestPathTactical;

/// @brief Interface for tactical models
///
/// A tactical model is responsible for determining the desired direction an agent would move to
/// reach its desired target (via a strategic model).
///

struct TacticalModelInterface {
    /// Sets up all needed data structures for the strategic model
    virtual auto setup(/* const Simulation & p_simulation **/) -> void{};

    /// Determines the desired direction towards a specific goal
    /// Computes the next position of the agents / an agent
    ///

    ///
    /// @return
    virtual auto computeStep(
        Simulation const & p_simulation,
        StrategicModelResult const & p_strategic_result,
        Agent const & p_agent) const -> TacticalModelResult = 0;

    /// Update the global state of the tactical model, e.g., when the geometry is changed or
    /// similar
    virtual auto update(/** const Simulation & p_simulation **/) -> void{};

    /// Tears down everything needed in the tactical model
    virtual auto tearDown(/** const Simulation & p_simulation **/) -> void{};
};

struct DummyTacticalModel : TacticalModelInterface {
    auto computeStep(
        [[maybe_unused]] Simulation const & p_simulation,
        [[maybe_unused]] StrategicModelResult const & p_strategic_result,
        [[maybe_unused]] Agent const & p_agent) const -> TacticalModelResult override
    {

        /*
         * Algorithmus für nächsten Schritt berechnen  -- > shortestPathTactical.floodfill(p_simulation, p_strategic_result, p_agent);
         * Position von p_agent ändern
         * p_agent.pos.x & p_agent.pos.y zurückgeben
         */

        return {};
    };
};
} // namespace jps
