#pragma once

#include "geometry/coordinate.hpp"
#include "geometry/line_segment.hpp"

#include <fmt/ostream.h>
#include <utility>
#include <vector>

namespace jps
{
class Area
{
    /// Replace with geometry library when we decided which one to use
    /// A closed polygon is saved, without repeating the first element at the back!
    std::vector<Coordinate> m_area_polygon;

public:
    /// Create an Area from a vector of Coordinates
    /// \param p_area_polygon sorted list of boundary points of a closed polygon
    Area(std::vector<Coordinate> p_area_polygon);

    /// Create an Area from a vector of line segments
    /// \param p_area_boundaries (unsorted) list of boundary elements of a closed polygon
    Area(std::vector<LineSegment> p_area_boundaries);

    Area(Area const & p_other) = default;
    auto operator=(Area const & p_other) -> Area & = default;
    Area(Area && p_other)                          = default;
    auto operator=(Area && p_other) -> Area & = default;
    ~Area()                                   = default;

    auto operator==(Area const & p_other) const noexcept -> bool;
    auto operator!=(Area const & p_other) const noexcept -> bool { return !(*this == p_other); }

    auto getPolygon() const -> std::vector<Coordinate> const & { return m_area_polygon; }
};

} // namespace jps

namespace fmt
{
template <>
struct formatter<jps::Area> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext & p_ctx)
    {
        return p_ctx.begin();
    }

    template <typename FormatContext>
    auto format(const jps::Area & p_area, FormatContext & p_ctx)
    {
        return format_to(p_ctx.out(), "AREA ({})", fmt::join(p_area.getPolygon(), ", "));
    }
};
} // namespace fmt