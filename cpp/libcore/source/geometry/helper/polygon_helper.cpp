#include "polygon_helper.hpp"

#include <algorithm>
#include <fmt/format.h>
#include <string>

auto jps::geometry::sortLineSegments(std::vector<LineSegment> & p_line_segments) -> void
{
    if(p_line_segments.size() <= 1) {
        return;
    }

    for(auto compare = std::begin(p_line_segments); compare != std::prev(std::end(p_line_segments));
        ++compare) {
        // find element that succeeds compare
        auto next_itr = std::find_if(
            std::next(compare), std::end(p_line_segments), [&compare](const LineSegment & p_other) {
                return (
                    p_other.getStart() == compare->getEnd() ||
                    p_other.getEnd() == compare->getEnd());
            });

        if(next_itr != std::end(p_line_segments)) {
            // move found element such that it follows compare in vector
            if(next_itr->getEnd() == compare->getEnd()) {
                next_itr->rotate();
            }
            std::iter_swap(next_itr, std::next(compare));
        } else {
            // if no succeeding element found, there is an issue
            throw std::runtime_error(fmt::format(
                FMT_STRING("Line segments could not be sorted. Could not find a wall succeeding "
                           "{}. Please check your geometry."),
                *compare));
        }
    }
}

auto jps::geometry::getPolygonCoordinates(std::vector<LineSegment> & p_line_segments)
    -> std::vector<Coordinate>
{
    // Need at least 3 elements to create polygon
    if(p_line_segments.size() < 3) {
        throw std::runtime_error(fmt::format(
            FMT_STRING("Could not create Polygon. At least 3 line segments expected to create "
                       "polygon, but "
                       "only {} have been passed."),
            p_line_segments.size()));
    }

    // Check if all elements are on same level
    auto level = p_line_segments.front().getStart().lvl;
    if(!std::all_of(
           std::begin(p_line_segments),
           std::end(p_line_segments),
           [level](const LineSegment & p_coordinate) {
               return p_coordinate.getStart().lvl == level;
           })) {
        throw std::runtime_error(fmt::format(
            FMT_STRING("Could not create Polygon. Not all line segments are on the same level.")));
    }

    // sort walls
    try {
        geometry::sortLineSegments(p_line_segments);
    } catch(const std::runtime_error & e) {
        throw std::runtime_error(
            fmt::format(FMT_STRING("Could not create Polygon. See: {}"), e.what()));
    }

    // check if line segments form a closed polygon
    if(std::begin(p_line_segments)->getStart() != p_line_segments.back().getEnd()) {
        throw std::runtime_error(fmt::format(
            FMT_STRING("Could not create Polygon. Needs to be a closed polygon, but endpoints "
                       "seems not to be "
                       "connected. Endpoints are {} and {}."),
            std::begin(p_line_segments)->getStart(),
            p_line_segments.back().getEnd()));
    }

    std::vector<Coordinate> boundary_points;
    // Get the start points of the line segments, they should contain all points of the polygon.
    std::transform(
        std::begin(p_line_segments),
        std::end(p_line_segments),
        std::back_inserter(boundary_points),
        [](const LineSegment & p_line) { return p_line.getStart(); });

    return boundary_points;
}

auto jps::geometry::checkPolygonEquality(
    const std::vector<Coordinate> & p_polygon,
    const std::vector<Coordinate> & p_other) -> bool
{
    if(p_polygon.size() != p_other.size()) {
        return false;
    }

    auto doubled_polygon{p_polygon};
    doubled_polygon.insert(std::end(doubled_polygon), std::begin(p_polygon), std::end(p_polygon));

    auto found = std::search(
        std::begin(doubled_polygon),
        std::end(doubled_polygon),
        std::begin(p_other),
        std::end(p_other));

    return found != std::end(doubled_polygon);
}
