#pragma once

#include "operational/operational.hpp"
#include "simulation_data.hpp"
#include "util/simulation_clock.hpp"

namespace jps
{
class Simulation
{
public:
    /// Constructor
    /// Note: Currently will emit a debug log message to ensure log callbacks can be set and the
    /// emited log message is received in the python wrapper.
    Simulation();
    /// Default destructor
    ~Simulation() = default;
    /// Non-copyable
    Simulation(const Simulation &) = delete;
    /// Non-copyable
    auto operator=(const Simulation &) -> Simulation & = delete;
    /// Non-movable
    Simulation(Simulation &&) = delete;
    /// Non-movable
    auto operator=(Simulation &&) -> Simulation & = delete;

    auto computeNextStep() -> void;

private:
    std::vector<Agent> m_agents;
    std::vector<OperationalModelResult> m_operational_results;
    // NOLINTNEXTLINE
    // SimulationClock m_simulation_clock{};
};

} // namespace jps
