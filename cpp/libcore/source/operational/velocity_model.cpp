#include "velocity_model.hpp"

#include "util/simulation_clock.hpp"

namespace jps
{
auto VelocityModel::getOptimalSpeed(double p_min_spacing, const std::chrono::milliseconds p_delta_t)
    -> double
{
    // V(s) = min(v0, max(0, (s-l)/T)
    return std::min(
        v0, std::max(0., (p_min_spacing - l) / std::chrono::duration<double>(p_delta_t).count()));
}

auto VelocityModel::getRepulsion(double p_spacing, double p_a, double p_D) -> double
{
    // R(s) = a*exp((l-s)/D)
    return p_a * std::exp(((l - p_spacing) / p_D));
}

auto VelocityModel::filterNeighbors(const Agent & p_agent, std::vector<Agent> & agents)
    -> void
{
    std::remove_if(std::begin(agents), std::end(agents), [p_agent](const Agent & other) {
        // compute scalar product of agent.movement_dir and other.movement_dir
        // check if scalar product <= 0

        // compute scalar product of orthogonal(agent.movement_dir) and other.movement_dir
        // check if scalar product <= l/distance between agent and other
    });
}

auto VelocityModel::computeRepulsionFromAgents(Simulation const & p_simulation, Agent const & p_agent) -> std::tuple<double, SpatialVector> {

    // TODO: getNeighbours
    std::vector<Agent> neighbours = p_simulation.getNeighbours(p_agent);
    // consider neighbours in field of view only
    filterNeighbors(p_agent, neighbours);

    double min_spacing = std::numeric_limits<double>::max();
    SpatialVector repulsion{0._m, 0._m};

    for(const auto & neighbour : neighbours) {
        // calc spacing
        // TODO overload coordinate+-coordinate
        SpatialVector displacement_to_neighbour = neighbour.pos - p_agent.pos;
        auto spacing                            = displacement_to_neighbour.norm();
        // calc min spacing
        min_spacing = std::min(spacing, min_spacing);

        // calc repulsion
        // TODO overload SpatialVector*double
        repulsion += getRepulsion(spacing, p_agent, D_ped) * displacement_to_neighbour.normalize();
    }

    return std::make_tuple(min_spacing, repulsion);
}

auto VelocityModel::computeRepulsionFromWalls(Simulation const & p_simulation, Agent const & p_agent) -> std::tuple<double, SpatialVector> {
    double min_spacing = std::numeric_limits<double>::max();
    SpatialVector repulsion{0._m, 0._m};

    // calc repulsion to walls
    // filter walls?
    for(const auto & wall : p_simulation.getWalls()) {
        // find closest point on wall to agent

        // calc in distance closest point
        Coordinate point_on_wall =
            wall.getNearestPoint(p_agent);
        SpatialVector displacement_to_wall =
            point_on_wall.pos - p_agent.pos;
        auto spacing = displacement_to_wall.norm();
        // calc min spacing
        min_spacing = std::min(spacing, min_spacing);

        // calc repulsion
        // TODO overload SpatialVector*double
        repulsion += getRepulsion(spacing, p_agent, D_wall) * displacement_to_wall.normalize();
    }
    return std::make_tuple(min_spacing, repulsion);
}

auto VelocityModel::computeStep(
    const jps::Simulation & p_simulation,
    const jps::TacticalModelResult & p_tactical_results,
    const jps::Agent & p_agent) const -> jps::OperationalModelResult
{
    auto agent_repulsion = computeRepulsionFromAgents(p_simulation, p_agent);
    auto wall_repulsion = computeRepulsionFromWalls(p_simulation, p_agent);

    // calc e_i (p_tactical_result is e0)
    SpatialVector e_i = p_tactical_results + std::get<SpatialVector>(agent_repulsion) + std::get<SpatialVector>(wall_repulsion);
    // normalize e_i
    e_i.normalize();

    // apply OV function
    double min_spacing = std::min(std::get<double>(agent_repulsion), std::get<double>(wall_repulsion));
    auto speed = getOptimalSpeed(min_spacing, delta_t);

    return speed * e_i;
}
} // namespace jps