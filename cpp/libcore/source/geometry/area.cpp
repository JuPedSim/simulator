#include "area.hpp"

#include "helper.hpp"

#include <algorithm>
#include <fmt/format.h>

jps::Area::Area(std::vector<Coordinate> p_area_polygon) : m_area_polygon(p_area_polygon)
{
    // TODO need to check if polygon is valid

    // Need at least 3 elements to create polygon
    if(p_area_polygon.size() < 3) {
        throw std::runtime_error(fmt::format(
            FMT_STRING("Could not create Area. At least 3 points expected to create polygon, but "
                       "only {} have been passed."),
            p_area_polygon.size()));
    }

    // Check if all elements are on same level
    auto level = p_area_polygon.front().m_lvl;
    if(!std::all_of(
           std::begin(p_area_polygon),
           std::end(p_area_polygon),
           [level](const Coordinate & p_coordinate) { return p_coordinate.m_lvl == level; })) {
        throw std::runtime_error(fmt::format(
            FMT_STRING("Could not create Area. Not all coordinates are on the same level.")));
    }

    // Remove last element if \p p_area_polygon was closed
    if(*std::begin(p_area_polygon) == p_area_polygon.back()) {
        m_area_polygon.pop_back();
    }
}
