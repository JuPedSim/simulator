#pragma once

#include "geometry/coordinate.hpp"

namespace jps
{
class LineSegment
{
    Coordinate m_start, m_end;

public:
    LineSegment(Coordinate p_start, Coordinate p_end) : m_start(p_start), m_end(p_end){};
};

} // namespace jps
