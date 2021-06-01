#pragma once

#include "line_segment.hpp"
#include "special_area.hpp"

#include <map>
#include <vector>

namespace jps
{
class WorldBuilder
{
private:
    std::map<jps::Level, std::vector<jps::LineSegment>> m_level_to_line_segments;
    std::map<jps::Level, std::vector<jps::SpecialArea>> m_level_to_special_areas;

public:
    WorldBuilder()  = default;
    ~WorldBuilder() = default;

    WorldBuilder(const WorldBuilder &) = delete;
    auto operator=(const WorldBuilder &) -> WorldBuilder & = delete;

    WorldBuilder(WorldBuilder &&) = default;
    auto operator=(WorldBuilder &&) -> WorldBuilder & = default;

    auto addLineSegment(const jps::Level & p_level, const jps::LineSegment & p_segment) -> void;
    auto addSpecialArea(const jps::Level & p_level, const jps::SpecialArea & p_area) -> void;
};
} // namespace jps
