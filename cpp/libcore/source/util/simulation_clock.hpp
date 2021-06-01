#pragma once

#include "log.hpp"
#include "util/jpsexception.hpp"

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <numeric>

/// SimulationClock handles the simulation time and time steps
///
/// For fixed time steps the SimulationClock counts the current time step and computes the current
/// simulation time.
class SimulationClock
{
    const std::uint64_t m_max_steps;
    const std::chrono::milliseconds m_delta_t;
    std::uint64_t m_current_step{0};

public:
    SimulationClock(std::uint64_t p_max_steps, std::chrono::milliseconds p_delta_t) :
        m_max_steps(p_max_steps), m_delta_t(p_delta_t)
    {
        if(m_delta_t <= std::chrono::milliseconds::zero()) {
            throw JPSException("SimulationClock time step needs to be larger than 0.");
        }
    }

    auto getMaxSteps() const -> std::uint64_t { return m_max_steps; }
    auto getDeltaT() const -> std::chrono::milliseconds { return m_delta_t; }
    auto getCurrentStep() const -> std::uint64_t { return m_current_step; }
    auto getCurrentTime() const -> std::chrono::milliseconds { return m_current_step * m_delta_t; }

    /// Advance the clock to the next step. Increases \p m_current_step until \p m_max_steps is
    /// reached.
    /// @return true if \p m_current_step was increased, false otherwise, which means \p
    /// m_current_step == \p m_max_steps
    auto advance() -> bool
    {
        if(m_current_step < m_max_steps) {
            m_current_step++;
            return true;
        }
        return false;
    }
};
