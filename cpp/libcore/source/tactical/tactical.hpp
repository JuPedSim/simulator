#pragma once

/// @brief Interface for tactical models
///
/// A tactical model is responsible for determining the desired direction an agent would move to
/// reach its desired target (via a strategic model).
///
class TacticalModelInterface
{
    /// Sets up all needed data structures for the strategic model
    virtual void setup(/** const Simulation & p_simulation **/){};

    /// Determines the desired direction towards a specific goal
    /// Computes the next position of the agents / an agent
    /// 
    /// @param p_simulation simulation context, including geometry
    /// @param p_tactical_results result from the strategic level for the agent
    /// @param p_agent agent for whom the next direction is computed
    ///
    /// @return
    virtual TacticalModelResult computeStep(/** const Simulation &, const StrategicModelResult & p_strategic_result, const Agent & p_agent **/) const = 0;

    /// Update the global state of the tactical model, e.g., when the geometry is changed or
    /// similar
    virtual void update(/** const Simulation & p_simulation **/){};

    /// Tears down everything needed in the tactical model
    virtual void tearDown(/** const Simulation & p_simulation **/){};
};
