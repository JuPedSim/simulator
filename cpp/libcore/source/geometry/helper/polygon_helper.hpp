#pragma once

#include "geometry/coordinate.hpp"
#include "geometry/line_segment.hpp"

#include <optional>
#include <vector>

namespace jps
{
namespace geometry
{
/// @brief Sorts \p p_other, to create a line chain.
///
/// The line segment in \p p_other will be sorted in a way that all line segments will be
/// connected in a way that line_segment.end == next_segment.start.
///
/// @throw std::runtime_error If no continuous line chain can be created from the given \p
/// p_line_segments
///
/// @param p_line_segments in: unsorted line segments, out: sorted line segments
///
auto sortLineSegments(std::vector<LineSegment> & p_line_segments) -> void;

/// @brief Returns the polygon, represented by a list of line segments.
///
/// \param p_line_segments continuous line chain representing a polygon (note: will be sorted in the
/// process, s.th. line_segment.end == next_segment.start)
///
/// \return vector of boundary points of the polygon from \p p_line_segments
auto getPolygonCoordinates(std::vector<LineSegment> & p_line_segments) -> std::vector<Coordinate>;

/// @brief Checks if two vectors of Coordinates represent the same polygon.
///
/// It will be checked if \p p_polygon and \p p_other are a representation of the same polygon. Two
/// polygons are considered equal if the lists contain the same points in the same order, cyclic
/// permutations (as in std::rotate) are allowed. They are also considered equal if one of them is
/// reversed.
///
/// Examples:
/// (A, B, C, D) == (B, C, D, A) -> true
/// (A, B, C, D) == (D, C, B, A) -> true
/// (A, B, C, D) == (B, A, D, C) -> true
///
/// (A, B, C, D) == (B, A, C, D) -> false
/// (A, B, C, D) == (A, B, C, D, E) -> false
///
/// \param p_polygon representation of one polygon
/// \param p_other representation of the other polygon.
///
/// \return the two vectors represent the same polygon.
auto checkPolygonEquality(
    std::vector<Coordinate> const & p_polygon,
    std::vector<Coordinate> const & p_other) -> bool;
}; // namespace geometry
} // namespace jps
