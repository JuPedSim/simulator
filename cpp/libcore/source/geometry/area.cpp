#include "area.hpp"

#include "geometry/helper/polygon_helper.hpp"
#include "util/jpsexception.hpp"

#include <algorithm>
#include <fmt/format.h>

jps::Area::Area(std::vector<Coordinate> p_area_polygon) : m_area_polygon(p_area_polygon)
{
    // TODO need to check if polygon is valid

    // Need at least 3 elements to create polygon
    if(p_area_polygon.size() < 3) {
        throw JPSGeometryException(fmt::format(
            FMT_STRING("Could not create Area. At least 3 points expected to create polygon, but "
                       "only {} have been passed."),
            p_area_polygon.size()));
    }

    // Remove last element if \p p_area_polygon was closed
    if(*std::begin(p_area_polygon) == p_area_polygon.back()) {
        m_area_polygon.pop_back();
    }
}
