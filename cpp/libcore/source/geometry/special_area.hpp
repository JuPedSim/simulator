#pragma once

#include "area.hpp"

#include <cstdint>
#include <fmt/ostream.h>
#include <utility>

namespace jps
{
class SpecialArea
{
    Area m_area;
    std::uint32_t m_id{};

public:
    SpecialArea(std::uint32_t p_id, Area p_area) : m_area(std::move(p_area)), m_id(p_id){};
    SpecialArea(SpecialArea const & p_other) = default;
    auto operator=(SpecialArea const & p_other) -> SpecialArea & = default;
    SpecialArea(SpecialArea && p_other)                          = default;
    auto operator=(SpecialArea && p_other) -> SpecialArea & = default;
    ~SpecialArea()                                          = default;

    auto operator==(SpecialArea const & p_other) const noexcept -> bool
    {
        // TODO also check if same area?
        return m_id == p_other.m_id;
    }
    auto operator!=(SpecialArea const & p_other) const noexcept -> bool
    {
        return !(*this == p_other);
    }

    auto getArea() const -> Area const & { return m_area; }

    auto getID() const -> std::uint32_t { return m_id; }
};
} // namespace jps

namespace fmt
{
template <>
struct formatter<jps::SpecialArea> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext & p_ctx)
    {
        return p_ctx.begin();
    }

    template <typename FormatContext>
    auto format(const jps::SpecialArea & p_area, FormatContext & p_ctx)
    {
        return format_to(p_ctx.out(), "SPECIAL_AREA ({}, {})", p_area.getID(), p_area.getArea());
    }
};
} // namespace fmt