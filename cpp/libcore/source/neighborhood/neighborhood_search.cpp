#include "neighborhood_search.hpp"

#include <algorithm>
#include <iterator>
#include <mutex>
#include <shared_mutex>


std::shared_mutex grid_mutex;
namespace jps
{
auto NeighborhoodSearch::update(
    std::unordered_map<LevelAlias, std::vector<Agent>> const & p_level_to_agents) -> void
{
    std::unique_lock exclusive_lock(grid_mutex);

    m_level_to_grid.clear();

    for(auto const & [level, agents] : p_level_to_agents) {
        m_level_to_grid.emplace(level, Grid2D<Agents>(m_grid_size_X, m_grid_size_y));

        for(auto const & agent : agents) {
            // determine the cell coordinates of pedestrian i
            // +1 because of dummy cells
            auto ix = static_cast<size_t>(((agent.pos.x - m_grid_x_min) / m_cellsize) + 1);
            auto iy = static_cast<size_t>(((agent.pos.y - m_grid_y_min) / m_cellsize) + 1);

            m_level_to_grid.at(level)[ix][iy].push_back(std::cref(agent));
        }
    }
}

auto NeighborhoodSearch::getNeighborhood(Level p_level, Agent const & p_agent) const
    -> std::vector<AgentRef>
{
    std::vector<AgentRef> neighborhood;

    int l = (int) ((p_agent.pos.x - m_grid_x_min) / m_cellsize) + 1; // +1 because of dummy cells
    int k = (int) ((p_agent.pos.y - m_grid_y_min) / m_cellsize) + 1;

    /**
     * We only acquire a shared lock here for reading data in the grid.
     * It is not allowed to write data using a shared lock.
     * Otherwise thread safety is lost.
     */
    std::shared_lock shared_lock(grid_mutex);

    // all neighbor cells
    for(int i = l - 1; i <= l + 1; ++i) {
        for(int j = k - 1; j <= k + 1; ++j) {
            auto ui = static_cast<size_t>(i);
            auto uj = static_cast<size_t>(j);
            std::copy_if(
                m_level_to_grid.at(p_level.id())[uj][ui].begin(),
                m_level_to_grid.at(p_level.id())[uj][ui].end(),
                std::back_inserter(neighborhood),
                [p_agent]([[maybe_unused]] Agent const & p_other_ped) {
                    return p_agent.id != p_other_ped.id;
                });
        }
    }

    return neighborhood;
}
}; // namespace jps
