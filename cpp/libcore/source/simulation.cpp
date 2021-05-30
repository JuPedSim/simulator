#include "simulation.hpp"

#include "agent/agent.hpp"
#include "log.hpp"
#include "operational/result.hpp"
#include "strategic/strategic.hpp"
#include "tactical/tactical.hpp"

#include <functional>
#include <utility>
#include <vector>
namespace jps
{
Simulation::Simulation()
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
        auto strategic_result = strategic_model.computeStep();
        (void) strategic_result;
        auto tactical_result = tactical_model.computeStep();
        (void) tactical_result;
        m_operational_results.emplace_back(operational_model.computeStep());
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
    m_agents.push_back({p_coordinate});
}

}; // namespace jps
