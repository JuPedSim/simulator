#pragma once

#include "area.hpp"
#include "util/identifiable.hpp"

#include <cstdint>
#include <fmt/core.h>
#include <fmt/ostream.h>
#include <utility>

namespace jps
{
/// Represents a special area which can be annotated with properties.
///
/// Note: after discussion, operator==/operator!= are not implemented yet as Identifiable classes
/// are not copyable and hence it is not possible that two SpecialAreas are the same.
class SpecialArea
{
    UniqueId<SpecialArea> m_id{};
    Area m_area;

public:
    explicit SpecialArea(Area p_area) : m_area(std::move(p_area)){};

    /// SpecialArea is not copyable
    SpecialArea(const SpecialArea & p_other) = delete;

    /// SpecialArea is not copyable
    auto operator=(const SpecialArea & p_other) -> SpecialArea & = delete;

    /// SpecialArea is movable
    SpecialArea(SpecialArea && p_other) = default;

    /// SpecialArea is movable
    auto operator=(SpecialArea && p_other) -> SpecialArea & = default;

    ~SpecialArea() = default;

    auto getArea() const noexcept -> Area const & { return m_area; }

    auto getID() const noexcept -> UniqueId<SpecialArea> { return m_id; }

    friend struct fmt::formatter<SpecialArea>;
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
    auto format(jps::SpecialArea const & p_area, FormatContext & p_ctx)
    {
        return format_to(p_ctx.out(), "SPECIAL_AREA ({}, {})", p_area.m_id, p_area.m_area);
    }
};
} // namespace fmt
