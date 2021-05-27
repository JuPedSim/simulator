#pragma once

#include "util/jpsexception.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <numeric>

/// SimulationClock handles the simulation time and time steps
///
/// For fixed time steps the SimulationClock counts the current time step and computes the current
/// simulation time.
///
class SimulationClock
{
    const std::uint64_t m_max_steps;
    const double m_delta_t;
    std::uint64_t m_current_step{0};

public:
    SimulationClock(std::uint64_t p_max_steps, double p_delta_t) :
        m_max_steps(p_max_steps), m_delta_t(p_delta_t)
    {
        if(m_delta_t <= 0) {
            throw JPSException("SimulationClock time step needs to be larger than 0");
        }
    }

    auto getMaxSteps() const -> std::uint64_t { return m_max_steps; }
    auto getDeltaT() const -> double { return m_delta_t; }
    auto getCurrentStep() const -> std::uint64_t { return m_current_step; }
    auto getCurrentTime() const -> double
    {
        return static_cast<double>(m_current_step) * m_delta_t;
    }

    /// Advance the clock to the next step. Increases \p m_current_step
    /// \throws JPSexception, when \p m_current_step exceeds \p m_max_steps
    auto advance() -> void
    {
        if(m_current_step >= m_max_steps) {
            throw JPSException(
                "SimulationClock advanced too far. `m_current_step' needs to be <= `m_max_steps'.");
        }
        m_current_step++;
    }
};
