#include "simulation.hpp"

#include "agent/agent.hpp"
#include "geometry/level.hpp"
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

    std::unordered_map<Level, std::vector<OperationalModelResult>> level_to_operational_results{};
    for(auto & ls : m_world->getLevels()) {
        std::vector<OperationalModelResult> operational_results{};
        for(auto const & agent : ls.second.getAgents()) {
            auto strategic_result = strategic_model.computeStep(*this, agent);
            auto tactical_result  = tactical_model.computeStep(*this, strategic_result, agent);
            operational_results.emplace_back(
                operational_model.computeStep(*this, tactical_result, agent));
        }
        level_to_operational_results.emplace(ls.first, operational_results);
    }

    for(auto const & [lvl, operational_results] : level_to_operational_results) {
        auto res_iter = operational_results.begin();
        for(auto & agent : m_world->getLevelStorage(lvl).getAgents()) {
            agent.pos += *res_iter++;
        }
    }
}

auto Simulation::addAgent(const Coordinate & p_coordinate, Level p_level) -> void
{
    m_world->getLevelStorage(p_level).addAgent(p_coordinate);
}

auto Simulation::getWorld() -> World &
{
    return *m_world;
}

}; // namespace jps
