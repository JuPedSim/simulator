#include "simulation.hpp"

#include "log.hpp"

#include <functional>
#include <utility>
#include <vector>
namespace jps
{
Simulation::Simulation()
{
    LOG_DEBUG("Simulator ctor");
};


void computeNextStep(Simulation & simulation)
{
    auto model_manager = simulation.model_manager;

    std::vector<std::pair<std::reference_wrapper<Agent>, OperationalModelResult>> >
        operational_results;

    for(auto & agent : simulation.getAgents()) {
        const auto & strategic_model = model_manager.getStrategicModel(agent);
        auto strategic_result        = strategic_model.computeNextStep(simulation, agent);

        auto tactical_result =
            strategic_result.tactical_model.computeNextStep(simulation, strategic_result, agent);

        const auto & operational_model = model_manager.getOperationalModel(agent);
        operational_results.emplace_back(
            agent, operational_model.computeNextStep(simulation, tactical_result, agent));
    }
}


}; // namespace jps
