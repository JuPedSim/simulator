#pragma once

#include "line_segment.hpp"
#include "special_area.hpp"

#include <map>
#include <vector>

namespace jps
{
class World
{
private:
    std::map<jps::Level, std::vector<jps::LineSegment>> m_level_to_line_segments;
    std::map<jps::Level, std::vector<jps::SpecialArea>> m_level_to_special_areas;

public:
    World()  = default;
    ~World() = default;

    World(const World &) = delete;
    auto operator=(const World &) -> World & = delete;

    World(World &&) = default;
    auto operator=(World &&) -> World & = default;

    auto addLineSegment(const jps::Level & p_level, const jps::LineSegment & p_segment) -> void;
    auto addSpecialArea(const jps::Level & p_level, const jps::SpecialArea & p_area) -> void;
};
} // namespace jps
