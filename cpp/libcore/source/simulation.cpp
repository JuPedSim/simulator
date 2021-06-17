#include "simulation.hpp"

#include "agent/agent.hpp"
#include "geometry/world.hpp"
#include "log.hpp"
#include "operational/result.hpp"
#include "strategic/strategic.hpp"
#include "tactical/tactical.hpp"

#include <functional>
#include <utility>
#include <vector>
namespace jps
{
Simulation::Simulation(std::unique_ptr<World> p_world) : m_world(std::move(p_world))
{
    LOG_DEBUG("Simulator ctor");
};


auto Simulation::computeNextStep() -> void
{
    static const DummyOperationalModel operational_model{};
    static const DummyTacticalModel tactical_model{};
    static const DummyStrategicModel strategic_model{};

    m_operational_results.clear();
    for(const auto & agent : m_agents) {
        (void) agent;
        auto strategic_result = strategic_model.computeStep(*this, agent);
        auto tactical_result  = tactical_model.computeStep(*this, strategic_result, agent);
        m_operational_results.emplace_back(
            operational_model.computeStep(*this, tactical_result, agent));
    }

    auto res_iter = m_operational_results.begin();
    for(auto & agent : m_agents) {
        agent.pos += *res_iter++;
    }
}

auto Simulation::addAgent(const Coordinate & p_coordinate) -> void
{
    // TODO (kkz) This can be changed to
    // m_agents.emplace_back(p_coordinate);
    // but requires C++20 to fix the missing aggregate initializaition from paretheses
    // otherwise we have to provide a CTOR to the struct
    m_agents.emplace_back(p_coordinate);
}

auto Simulation::getAgents() const -> const std::vector<Agent> &
{
    return m_agents;
}

auto Simulation::getWorld() -> World &
{
    return *m_world;
}

}; // namespace jps
