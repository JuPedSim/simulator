#pragma once

#include "geometry/length_unit.hpp"
#include "geometry/level.hpp"

namespace jps
{
/// Spatial Coordinate
///
/// Represents a spatial coordinate in the world (geometry).
class Coordinate
{
    LengthUnit m_x;
    LengthUnit m_y;
    Level m_lvl;
};
} // namespace jps
