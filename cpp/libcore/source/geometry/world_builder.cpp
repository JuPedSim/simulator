#include "world_builder.hpp"

#include <utility>

auto WorldBuilder::addLineSegment(int p_level, const jps::LineSegment &p_segment) -> void
{
    // TODO: ensure that coordinates belong to same level, add to map
}

auto WorldBuilder::addSpecialArea(int p_level, const jps::SpecialArea &p_area) -> void
{
    // TODO: check if area id at given level already exists, add to map
}
