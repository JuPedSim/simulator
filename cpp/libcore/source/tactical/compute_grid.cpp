#include "tactical/compute_grid.hpp"


using namespace std;

auto ComputeGrid::floodfill(jps::Agent &p_agent){
    Grid2D</*which typename? We don't want agents here*/> flood_grid;
    auto pos_x = p_agent.pos.x;
    auto pos_y = p_agent.pos.y;

    return flood_grid;
}

auto ComputeGrid::computeNextStep(jps::Simulation &p_simulation, jps::StrategicModelResult &p_strategic_result, jps::Agent &p_agent) {
    floodfill(&p_agent);
    return 0;
}

auto ComputeGrid::setup(jps::Simulation &p_simulation) {

    return 0;
}

auto ComputeGrid::update(jps::Simulation &p_simulation) {

    return 0;
}

auto ComputeGrid::updateNeighborhood(const std::vector<Agent> &p_agents) {
    std::unique_lock exclusive_lock(m_grid_mutex);

    m_grid.clear();

    for(auto const & agent : p_agents) {
        auto id_x = lengthUnitToIndex(agent.pos.x, m_cell_size);
        auto id_y = lengthUnitToIndex(agent.pos.y, m_cell_size);

        m_grid[id_x][id_y].push_back(std::cref(agent));
    }
}