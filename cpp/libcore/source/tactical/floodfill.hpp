#pragma once

#include "agent/agent.hpp"
#include "strategic/result.hpp"
#include "tactical/result.hpp"
#include "tactical/tactical.hpp"
#include <string>
#include "neighborhood/grid_2d.hpp"
#include "simulation.hpp"
#include "geometry/length_unit.hpp"
#include <shared_mutex>
#include <array>

namespace jps {
    class Floodfill {

    private:
        std::vector<Grid2D<int>> m_grids;
    public:
        /// Constructor
        Floodfill();
        ~Floodfill() = default;
        Floodfill(const Floodfill &) = delete;
        auto operator=(const Floodfill &) -> Floodfill & = delete;
        Floodfill(Floodfill &&) = delete;
        auto operator=(Floodfill &&) -> Floodfill & = delete;

        /// Important to replace individual fields later in the grid
        /// @param p_grid The grid which was filled with the environment
        /// @param p_old_number
        /// @param p_new_number
        /// @param p_x
        /// @param p_y
        auto changeInteger(Grid2D<int> p_grid,int p_old_number, int p_new_number,int p_x, int p_y);

        /// Scans the room and returns a 2D Grid as return value
        /// @param &p_simulation Reference to simulation
        /// @return 2D Grid
        auto computeGrid(jps::Simulation const &p_simulation) -> Grid2D<int>;
    };
}