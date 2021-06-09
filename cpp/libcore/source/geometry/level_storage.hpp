#pragma once

#include "geometry/level.hpp"
#include "geometry/line_segment.hpp"
#include "geometry/special_area.hpp"

#include <vector>
namespace jps
{
struct LevelStorage {
    std::vector<LineSegment> m_line_segments;
    std::vector<SpecialArea> m_special_areas;
};
} // namespace jps
