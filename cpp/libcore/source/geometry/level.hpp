#pragma once

#include <cstdint>
#include <fmt/ostream.h>
#include <utility>

namespace jps
{
/// Represents levels in the geometry.
class Level
{
    std::int32_t m_id{};

public:
    explicit Level(std::int32_t p_id) : m_id(p_id){};

    auto operator==(Level const & p_other) const noexcept -> bool { return m_id == p_other.m_id; }
    auto operator!=(Level const & p_other) const noexcept -> bool { return !(*this == p_other); }

    auto id() const -> std::int32_t { return m_id; }
};
} // namespace jps

namespace fmt
{
template <>
struct formatter<jps::Level> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext & p_ctx)
    {
        return p_ctx.begin();
    }

    template <typename FormatContext>
    auto format(jps::Level const & p_level, FormatContext & p_ctx)
    {
        return format_to(p_ctx.out(), "LEVEL: {}", p_level.id());
    }
};
} // namespace fmt
