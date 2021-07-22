#pragma once

#include "agent/agent.hpp"
#include "geometry/coordinate.hpp"
#include "geometry/level.hpp"
#include "geometry/line_segment.hpp"
#include "geometry/special_area.hpp"

#include <vector>

namespace jps
{
class LevelStorage
{
    std::vector<LineSegment> m_line_segments;
    std::vector<SpecialArea> m_special_areas;
    std::vector<Agent> m_agents;

public:
    auto addLineSegment(LineSegment const & p_segment) -> void;
    auto addSpecialArea(SpecialArea const & p_area) -> void;
    auto getAgents() -> std::vector<Agent> & { return m_agents; };
    auto getAgents() const -> std::vector<Agent> const & { return m_agents; };
    auto addAgent(Coordinate const & p_coordinate) -> void;
};
} // namespace jps
