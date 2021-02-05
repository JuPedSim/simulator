#pragma once


#include "geometry/length_unit.hpp"
namespace jps
{
/// Represents a directed vector in space
///
/// SpatialVectors origin is not the point of origin of coordinates [(0,0)].
/// It gives a direction in the plane and has no level.
class SpatialVector
{
    LengthUnit m_x;
    LengthUnit m_y;
};
} // namespace jps
