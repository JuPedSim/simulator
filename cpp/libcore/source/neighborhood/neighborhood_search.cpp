#include "neighborhood_search.hpp"

#include <algorithm>
#include <cstdint>
#include <iterator>
#include <mutex>


namespace jps
{
auto NeighborhoodSearch::update(std::vector<Agent> const & p_agents) -> void
{
    std::unique_lock exclusive_lock(m_grid_mutex);

    m_grid.clear();

    for(auto const & agent : p_agents) {
        auto id_x = lengthUnitToIndex(agent.pos.x, m_cell_size);
        auto id_y = lengthUnitToIndex(agent.pos.y, m_cell_size);

        m_grid[id_x][id_y].push_back(std::cref(agent));
    }
}

auto NeighborhoodSearch::getNeighborhood(
    Agent const & p_agent,
    std::uint16_t p_num_neighborhood_cells) const -> std::vector<AgentRef>
{
    std::vector<AgentRef> neighborhood;

    auto id_x = lengthUnitToIndex(p_agent.pos.x, m_cell_size);
    auto id_y = lengthUnitToIndex(p_agent.pos.y, m_cell_size);

    /**
     * We only acquire a shared lock here for reading data in the grid.
     * It is not allowed to write data using a shared lock.
     * Otherwise thread safety is lost.
     */
    std::shared_lock shared_lock(m_grid_mutex);

    // all neighborng cells in p_num_neighborhood_cells
    for(std::int64_t i = id_x - p_num_neighborhood_cells; i <= id_x + p_num_neighborhood_cells;
        ++i) {
        for(std::int64_t j = id_y - p_num_neighborhood_cells; j <= id_y + p_num_neighborhood_cells;
            ++j) {
            std::copy_if(
                m_grid.get(j, i).begin(),
                m_grid.get(j, i).end(),
                std::back_inserter(neighborhood),
                [p_agent](Agent const & p_other_ped) { return p_agent.id != p_other_ped.id; });
        }
    }

    return neighborhood;
}
}; // namespace jps
