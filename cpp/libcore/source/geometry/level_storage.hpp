#pragma once

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

public:
    auto addLineSegment(LineSegment const & p_segment) -> void;
    auto addSpecialArea(SpecialArea const & p_area) -> void;
};
} // namespace jps
