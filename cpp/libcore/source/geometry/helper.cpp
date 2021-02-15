#include "helper.hpp"

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