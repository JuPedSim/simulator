#pragma once

#include "geometry/coordinate.hpp"

#include <utility>
#include <vector>

namespace jps
{
class Area
{
    std::vector<Coordinate> m_area_polygon;

public:
    Area(std::vector<Coordinate> p_area_polygon) : m_area_polygon(std::move(p_area_polygon)){};
};

} // namespace jps
