#include "area.hpp"

#include "helper.hpp"

#include <algorithm>
#include <fmt/format.h>

jps::Area::Area(std::vector<Coordinate> p_area_polygon) : m_area_polygon(p_area_polygon)
{
    // TODO need to check of area of polygon == 0 (not a valid polygon)

    // Need at least 3 elements to create polygon
    if(p_area_polygon.size() < 3) {
        throw std::runtime_error(fmt::format(
            FMT_STRING("Could not create Area. At least 3 points expected to create polygon, but "
                       "only {} have been passed."),
            p_area_polygon.size()));
    }

    // Check if all elements are on same level
    auto level = p_area_polygon.front().lvl();
    if(!std::all_of(
           std::begin(p_area_polygon),
           std::end(p_area_polygon),
           [level](const Coordinate & p_coordinate) { return p_coordinate.lvl() == level; })) {
        throw std::runtime_error(fmt::format(
            FMT_STRING("Could not create Area. Not all coordinates are on the same level.")));
    }

    // Remove last element if \p p_area_polygon was closed
    if(*std::begin(p_area_polygon) == p_area_polygon.back()) {
        m_area_polygon.pop_back();
    }
}

jps::Area::Area(std::vector<LineSegment> p_area_boundaries)
{
    // TODO need to check of area of polygon == 0 (not a valid polygon)

    // Need at least 3 elements to create polygon
    if(p_area_boundaries.size() < 3) {
        throw std::runtime_error(fmt::format(
            FMT_STRING(
                "Could not create Area. At least 3 line segments expected to create polygon, but "
                "only {} have been passed."),
            p_area_boundaries.size()));
    }

    // Check if all elements are on same level
    auto level = p_area_boundaries.front().getStart().lvl();
    if(!std::all_of(
           std::begin(p_area_boundaries),
           std::end(p_area_boundaries),
           [level](const LineSegment & p_coordinate) {
               return p_coordinate.getStart().lvl() == level;
           })) {
        throw std::runtime_error(fmt::format(
            FMT_STRING("Could not create Area. Not all line segments are on the same level.")));
    }

    // sort walls
    try {
        geometry::sortLineSegments(p_area_boundaries);
    } catch(const std::runtime_error & e) {
        throw std::runtime_error(
            fmt::format(FMT_STRING("Could not create Area. See: {}"), e.what()));
    }

    // check if line segments form a closed polygon
    if(std::begin(p_area_boundaries)->getStart() != p_area_boundaries.back().getEnd()) {
        throw std::runtime_error(fmt::format(
            FMT_STRING(
                "Could not create Area. Needs to be a closed polygon, but endpoints seem not to be "
                "connected. Endpoints are {} and {}."),
            std::begin(p_area_boundaries)->getStart(),
            p_area_boundaries.back().getEnd()));
    }

    // Get the start points of the line segments, they should contain all points of the polygon.
    std::transform(
        std::begin(p_area_boundaries),
        std::end(p_area_boundaries),
        std::back_inserter(m_area_polygon),
        [](const LineSegment & p_line) { return p_line.getStart(); });
}

auto jps::Area::operator==(const jps::Area & p_other) const noexcept -> bool
{
    return std::is_permutation(
        std::begin(m_area_polygon), std::end(m_area_polygon), std::begin(p_other.m_area_polygon));
}
