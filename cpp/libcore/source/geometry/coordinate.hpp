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

public:
    Coordinate(LengthUnit p_x, LengthUnit p_y, Level p_lvl) : m_x(p_x), m_y(p_y), m_lvl(p_lvl){};
};
} // namespace jps
