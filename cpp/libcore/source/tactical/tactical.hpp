#pragma once

/// @brief Interface for tactical models
///
/// A tactical model is responsible for determining the desired direction an agent would move to
/// reach its desired target (via a strategic model).
///
class TacticalModelInterface
{
    /// Sets up all needed data structures for the strategic model
    virtual void setup(/** World **/) = 0;

    /// Determines the desired direction towards a specific goal
    /// TODO Return type: Displacement vector?
    virtual void computeStep(/** const Simulation &, Result of strategic level **/) = 0;

    /// Update the global state of the tactical model, e.g., when the geometry is changed or
    /// similar
    virtual void update() = 0;

    /// Tears down everything needed in the tactical model
    virtual void tearDown() = 0;
};
