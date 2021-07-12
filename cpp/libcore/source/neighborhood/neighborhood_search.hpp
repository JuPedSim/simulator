#pragma once

#include "agent/agent.hpp"
#include "geometry/length_unit.hpp"
#include "grid_2d.hpp"

#include <deque>
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

namespace jps
{
class NeighborhoodSearch
{
    using AgentRef = std::reference_wrapper<Agent const>;
    using Agents   = std::deque<AgentRef>;

    // TODO replace with Level when #72 is merged
    using LevelAlias = std::int32_t;

private:
    LengthUnit m_grid_x_min;
    LengthUnit m_grid_y_min;
    LengthUnit m_cellsize;

    size_t m_grid_size_X;
    size_t m_grid_size_y;

    std::unordered_map<LevelAlias, Grid2D<Agents>> m_level_to_grid;

public:
    NeighborhoodSearch(const NeighborhoodSearch &) = default;
    NeighborhoodSearch(NeighborhoodSearch &&)      = default;
    auto operator=(const NeighborhoodSearch &) -> NeighborhoodSearch & = default;
    auto operator=(NeighborhoodSearch &&) -> NeighborhoodSearch & = default;
    ~NeighborhoodSearch()                                         = default;

    /**
     *
     * @param p_grid_xmin
     * @param p_grid_xmax
     * @param p_grid_ymin
     * @param p_grid_ymax
     * @param p_cell_size
     * @param p_levels
     */
    NeighborhoodSearch(
        LengthUnit p_grid_xmin,
        LengthUnit p_grid_xmax,
        LengthUnit p_grid_ymin,
        LengthUnit p_grid_ymax,
        LengthUnit p_cell_size,
        std::vector<Level> const & p_levels) :
        m_grid_x_min(p_grid_xmin),
        m_grid_y_min(p_grid_ymin),
        m_cellsize(p_cell_size),
        // 1 dummy cell on each side
        m_grid_size_X(static_cast<size_t>(((p_grid_xmax - p_grid_xmin) / m_cellsize) + 1 + 2)),
        m_grid_size_y(static_cast<size_t>(
            ((p_grid_ymax - p_grid_ymin) / m_cellsize) + 1 + 2)) // 1 dummy cell on each side
    {
        for(auto const & level : p_levels) {
            m_level_to_grid.emplace(level.id(), Grid2D<Agents>(m_grid_size_X, m_grid_size_y));
        }
    };


    /**
     * Update the cells occupation
     */
    auto update(std::unordered_map<LevelAlias, std::vector<Agent>> const & p_level_to_agents)
        -> void;

    /**
     * Returns neighborhood of the pedestrians ped
     * @param p_agent
     * @return neighbourhood
     */
    [[nodiscard]] auto getNeighborhood(Level p_level, Agent const & p_agent) const
        -> std::vector<AgentRef>;
};
} // namespace jps
