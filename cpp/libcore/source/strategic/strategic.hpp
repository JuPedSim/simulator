#pragma once

/// @brief Interface for strategic models
///
/// A strategic model is responsible for deciding what the agent wants to do, e.g., go to an exit,
/// go to a store, wait, etc. For example a FSM, could be used to model the behavior of the agents.
///
class StrategicModelInterface
{
    /// Sets up all needed data structures for the strategic model
    virtual void setup(/** World **/){};

    /// Determines the next goal of an agent
    /// TODO Return type: How to identify an arbitrary area/point within the geometry
    virtual void computeStep(/** const Simulation & **/) = 0;

    /// Update the global state of the strategic model, e.g., when the geometry is changed or
    /// similar
    virtual void update() = 0;

    /// Tears down everything needed in the strategic model
    virtual void tearDown(){};
};
