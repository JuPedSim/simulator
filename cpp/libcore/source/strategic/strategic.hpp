#pragma once

/// @brief Interface for strategic models
///
/// A strategic model is responsible for deciding what the agent wants to do, e.g., go to an exit,
/// go to a store, wait, etc. For example a FSM, could be used to model the behavior of the agents.
///
class StrategicModelInterface
{
    /// Sets up all needed data structures for the strategic model
    virtual void setup(/** const Simulation & p_simulation **/){};

    /// Determines the next goal of an agent
    /// 
    /// @param p_simulation simulation context, including geometry
    /// @param p_agent agent for whom the goal is computed
    ///
    /// @return
    virtual StartegicModelResult computeStep(/** const Simulation & p_simulation, const Agent & p_agent **/) const = 0;

    /// Update the global state of the strategic model, e.g., when the geometry is changed or
    /// similar
    virtual void update(/** const Simulation & p_simulation **/){};

    /// Tears down everything needed in the strategic model
    virtual void tearDown(/** const Simulation & p_simulation **/){};
};
