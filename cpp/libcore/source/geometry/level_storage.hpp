#pragma once

#include "agent/agent.hpp"
#include "geometry/coordinate.hpp"
#include "geometry/level.hpp"
#include "geometry/line_segment.hpp"
#include "geometry/special_area.hpp"

#include <limits>
#include <vector>
namespace jps
{
struct BoundingBox {
    Coordinate lower_left;  // NOLINTLINE(cppcoreguidelines-non-private-member-variables-in-classes)
    Coordinate upper_right; // NOLINTLINE(cppcoreguidelines-non-private-member-variables-in-classes)

    [[maybe_unused]] BoundingBox(Coordinate p_lower_left, Coordinate p_upper_right) :
        lower_left(p_lower_left), upper_right(p_upper_right){};
};

class LevelStorage
{
    std::vector<LineSegment> m_line_segments;
    std::vector<SpecialArea> m_special_areas;
    std::vector<Agent> m_agents;

    BoundingBox m_bounding_box{
        Coordinate(
            makeLengthUnit<Units::m>(std::numeric_limits<double>::infinity()),
            makeLengthUnit<Units::m>(std::numeric_limits<double>::infinity())),
        Coordinate(
            makeLengthUnit<Units::m>(-std::numeric_limits<double>::infinity()),
            makeLengthUnit<Units::m>(-std::numeric_limits<double>::infinity()))};

public:
    auto addLineSegment(LineSegment const & p_segment) -> void;
    auto addSpecialArea(SpecialArea const & p_area) -> void;
    auto getAgents() -> std::vector<Agent> & { return m_agents; };
    auto getAgents() const -> std::vector<Agent> const & { return m_agents; };
    auto addAgent(Coordinate const & p_coordinate) -> void;
    auto getBoundingBox() -> BoundingBox const & { return m_bounding_box; };

private:
    auto updateBoundingBox(Coordinate const & p_coordinate) -> void;
};
} // namespace jps
