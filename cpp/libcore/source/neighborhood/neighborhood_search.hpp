#pragma once

#include "agent/agent.hpp"
#include "geometry/length_unit.hpp"
#include "grid_2d.hpp"

#include <cmath>
#include <cstdint>
#include <deque>
#include <functional>
#include <shared_mutex>
#include <string>
#include <unordered_map>
#include <vector>

namespace jps
{
inline auto lengthUnitToIndex(LengthUnit p_lu, LengthUnit p_cellsize) -> std::int64_t
{
    return static_cast<std::int64_t>(std::floor(p_lu / p_cellsize));
}

class NeighborhoodSearch
{
    using AgentRef = std::reference_wrapper<Agent const>;
    using Agents   = std::deque<AgentRef>;

private:
    LengthUnit m_cell_size;

    Grid2D<Agents> m_grid;
    mutable std::shared_mutex m_grid_mutex;

public:
    NeighborhoodSearch(const NeighborhoodSearch &) = delete;
    NeighborhoodSearch(NeighborhoodSearch &&)      = delete;
    auto operator=(const NeighborhoodSearch &) -> NeighborhoodSearch & = delete;
    auto operator=(NeighborhoodSearch &&) -> NeighborhoodSearch & = delete;
    ~NeighborhoodSearch()                                         = default;

    /// Creates Neighborhoodsearch using a 2D Grid with p_cell_size and distributes p_agents
    ///
    /// @param p_cell_size size of the cell of the grid
    /// @param p_agents agents to distribute in the grid
    explicit NeighborhoodSearch(LengthUnit p_cell_size, std::vector<Agent> const & p_agents) :
        m_cell_size(p_cell_size)
    {
        update(p_agents);
    };


    /// Returns the neighboring agents of p_agent in the neighboring cells
    /// (p_num_neighborhood_cells)
    ///
    /// @param p_agent agent whos neighborhood is calculated
    /// @param p_num_neighborhood_cells number of cells which should be considered neighboring
    /// @return neighbourhood
    [[nodiscard]] auto
    getNeighborhood(Agent const & p_agent, std::uint16_t p_num_neighborhood_cells = 1) const
        -> std::vector<AgentRef>;

private:
    /// Update the cells occupation.
    auto update(std::vector<Agent> const & p_agents) -> void;
};
} // namespace jps
