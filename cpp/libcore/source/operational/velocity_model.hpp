#pragma once

#include "operational.hpp"

#include <chrono>

namespace jps
{
/**
 * @brief Implementation of the Collision free speed model by Tordeux et. al
 *
 * For further information see the paper:
 * - https://link.springer.com/chapter/10.1007%2F978-3-319-33482-0_29 (original)
 * - 10.1007/978-3-319-33482-0_29 (DOI)
 * - https://juser.fz-juelich.de/record/281542/files/ArticleTGF15.pdf
 *
 */
struct VelocityModel : OperationalModelInterface {
    static constexpr double l      = 0.3;  // in m
    static constexpr double a_ped  = 5;    // repulsion coefficient for pedestrians
    static constexpr double a_wall = 5;    // repulsion coefficient for walls
    static constexpr double D_ped  = 0.1;  // in m
    static constexpr double D_wall = 0.02; // in m
    static constexpr double v0     = 1.2;  // in m/s
    static constexpr std::chrono::milliseconds delta_t{10};

    auto computeStep(
        Simulation const & p_simulation,
        TacticalModelResult const & p_tactical_results,
        Agent const & p_agent) const -> OperationalModelResult override;


private:
    /**
     * Optimal speed function depending on the minimal spacing in front.
     * @return optimal speed for the agent
     */
    static auto getOptimalSpeed(double p_min_spacing, const std::chrono::milliseconds p_delta_t)
        -> double;

    /**
     * Repulsion function
     * @return repulsion of given spacing
     */
    static auto getRepulsion(double p_spacing, double p_a, double p_D) -> double;

    /**
     * Remove all neighbor which are not in the gray area (better description later)
     * @param agents
     */
    static auto filterNeighbors(const Agent & agent, std::vector<Agent> & agents) -> void;

    static auto computeRepulsionFromAgents(Simulation const & p_simulation, Agent const & p_agent)
        -> std::tuple<double, SpatialVector>;

    static auto computeRepulsionFromWalls(Simulation const & p_simulation, Agent const & p_agent)
        -> std::tuple<double, SpatialVector>;
};

} // namespace jps
