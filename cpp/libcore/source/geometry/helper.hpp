#pragma once

#include "geometry/coordinate.hpp"
#include "geometry/line_segment.hpp"

#include <optional>
#include <vector>

namespace jps
{
namespace geometry
{
///
///@brief Sorts \p p_other, to create a line chain.
///
/// The line segment in \p p_other will be sorted in a way that all line segments will be
/// connected in a way that line_segment.end == next_segment.start.
///
/// @throw std::runtime_error If no continuous line chain can be created from the given \p
/// p_other
///
/// @param p_line_segments in: unsorted line segments, out: sorted line segments
///
auto sortLineSegments(std::vector<LineSegment> & p_line_segments) -> void;

}; // namespace geometry
} // namespace jps
