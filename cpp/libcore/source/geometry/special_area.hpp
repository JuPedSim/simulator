#pragma once

#include "area.hpp"
#include "util/identifiable.hpp"

#include <cstdint>
#include <fmt/ostream.h>
#include <utility>

namespace jps
{
/// Represents a special area which can be annotated with properties.
///
/// Note: after discussion, operator==/operator!= are not implemented yet as Identifiable classes
/// are not copyable and hence it is not possible that two SpecialAreas are the same.
class SpecialArea : public Identifiable<SpecialArea>
{
    Area m_area;
    std::uint32_t m_external_id{};

public:
    SpecialArea(std::uint32_t p_id, Area p_area) : m_area(std::move(p_area)), m_external_id(p_id){};

    auto getArea() const noexcept -> Area const & { return m_area; }

    auto getExternalID() const noexcept -> std::uint32_t { return m_external_id; }
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
        return format_to(p_ctx.out(), "SPECIAL_AREA ({}, {})", p_area.getID(), p_area.getArea());
    }
};
} // namespace fmt