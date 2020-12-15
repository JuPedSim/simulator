#pragma once

/// @brief Interface for operational models
///
/// An operational model is responsible for computing the movement of the agents within the
/// simulation based on the current target, geometry (walls, obstacles) and surrounding agents.
///
class OperationalModelInterface
{
    /// Sets up all needed data structures for the operational model
    virtual void setup(/** const World &, const Simulation &? **/){};

    /// Computes the next position of the agents / an agent
    /// TODO decide if this is called on all agent or on each agent individual
    /// TODO Return type: Offset or new position
    virtual void computeNextPosition(/** const Simulation &, result of tactical model **/) = 0;

    /// Update the global state of the operational model, e.g., when geometry is changed due
    /// to events or similar
    virtual void update() = 0;

    /// Tears down everything needed in the operational model
    virtual void tearDown(){};
};
