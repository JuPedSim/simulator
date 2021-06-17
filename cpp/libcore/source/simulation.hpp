#pragma once

#include "agent/pedestrian.hpp"
#include "geometry/coordinate.hpp"
#include "geometry/world.hpp"
#include "operational/operational.hpp"
#include "simulation_data.hpp"
#include "util/simulation_clock.hpp"

#include <memory>

namespace jps
{
class Simulation
{
public:
    /// Constructor
    /// @param p_world unique_ptr to the geometry storage to be used.
    /// Note: Currently will emit a debug log message to ensure log callbacks can be set and the
    /// emited log message is received in the python wrapper.
    explicit Simulation(std::unique_ptr<World> p_world);
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

    auto addAgent(const Coordinate & p_coordinate) -> void;

    auto getWorld() -> World &;

    auto getAgents() const -> const std::vector<Agent> &;

private:
    std::unique_ptr<World> m_world;
    std::vector<Agent> m_agents{};
    std::vector<OperationalModelResult> m_operational_results{};
    // NOLINTNEXTLINE
    // SimulationClock m_simulation_clock{};
};

} // namespace jps
