#include "simulation.hpp"

#include "log.hpp"
#include "operational/operational.hpp"
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


void Simulation::computeNextStep()
{
    static const DummyOperationalModel operational_model{};
    static const DummyTacticalModel tactical_model{};
    static const DummyStrategicModel strategic_model{};

    std::vector<std::pair<std::reference_wrapper<Agent>, OperationalModelResult>>
        operational_results;
    // Maybe as transform in an lambda?
    for(auto & agent : m_simulation_data.agents) {
        auto strategic_result = strategic_model.computeStep();

        auto tactical_result = tactical_model.computeStep();

        operational_results.emplace_back(agent, operational_model.computeStep());
    }
}


}; // namespace jps
