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

namespace jps {
    class Floodfill {

    private:
        Grid2D<int> m_flood_grid;
        mutable std::shared_mutex m_grid_mutex;
    public:
        /// Constructor
        Floodfill();
        ~Floodfill() = default;
        Floodfill(const Floodfill &) = delete;
        auto operator=(const Floodfill &) -> Floodfill & = delete;
        Floodfill(Floodfill &&) = delete;
        auto operator=(Floodfill &&) -> Floodfill & = delete;

        /// Scans the room and returns a 2D Grid as return value
        /// @param &p_simulation Reference to simulation
        /// @param &p_agent Reference to agent
        /// @return 2D Grid
        auto computeGrid(jps::Simulation const &p_simulation, jps::Agent const &p_agent) -> Grid2D<int>;
    };
}