#pragma once

#include "enum.hpp"
#include "math/int_pow.hpp"

#include <fmt/format.h>
#include <fmt/ostream.h>
#include <type_traits>

namespace jps
{
/// Enumeration for supported length units.
/// Underlying integer must be set to the decimal exponent relative to meter (like SI).
enum class Units { um = -6, mm = -3, cm = -2, dm = -1, m = 0, km = 3 };
const int DECIMAL_BASE = 10;

namespace details
{
/// Scales the given quantity of a length unit from `from` unit to `to` unit.
/// The used  quantity type T can be deduced automatically.
/// If from < to the quantity is divided and truncated towards zero for integral T.
/// Can be called like: `scaleQuantity<Units::mm, Units::cm>(10)`
template <Units from, Units to, typename T>
constexpr auto scaleQuantity(T p_quantity) -> T
{
    static_assert(
        std::is_floating_point_v<T>,
        "scaleQuantity should be used with floating point types only.");

    const int diff_exp = toUnderlying(from) - toUnderlying(to);

    if constexpr(diff_exp < 0) {
        return p_quantity / jps::math::intPow<DECIMAL_BASE, -diff_exp>();
    } else {
        return p_quantity * jps::math::intPow<DECIMAL_BASE, diff_exp>();
    }
}


/// Helper struct to encapsulate the params required for LengthUnit construction
/// @tparam QuantityType floating point type used to represent the quantity
/// @tparam Unit of the quantity
template <typename QuantityType, Units Unit>
struct LengthUnitParams {
    /// The quantity for the LengthUnit creation in Unit
    const QuantityType quantity; // NOLINT(misc-non-private-member-variables-in-classes)
    constexpr explicit LengthUnitParams(QuantityType p_quantity) : quantity{p_quantity} {}
};
} // namespace details

/// Stores the quantity of a length unit
///
/// LengthUnit is the base unit for all spatial data structures.
/// It represents a quantity in RESOLUTION unit.
/// It can only be created by explicitly passing the unit of the quantity.
/// The construction has to be done using LengthUnitParams.
class LengthUnit
{
    /// Defines the unit which is used to store the quantity internally
    const static Units RESOLUTION = Units::m;

public:
    /// Type used for the quantity.
    using QuantityType = double;

    LengthUnit() = default;

    LengthUnit(LengthUnit const & p_other) = default;
    auto operator=(LengthUnit const & p_other) -> LengthUnit & = default;

    LengthUnit(LengthUnit && p_moved) noexcept = default;
    auto operator=(LengthUnit && p_moved) noexcept -> LengthUnit & = default;

    ~LengthUnit() = default;

    /// Constructors using LengthUnitParams
    ///
    /// Template parameters in constructors have to be auto deducible.
    /// Otherwise it is not possible to distinguish class template params and constructor template
    /// params.
    /// The quantity is scaled towards the RESOLUTION unit.
    ///
    /// @tparam Unit is the input unit of the quantity.
    template <Units Unit>
    constexpr explicit LengthUnit(details::LengthUnitParams<QuantityType, Unit> const & p_params) :
        m_quantity{details::scaleQuantity<Unit, RESOLUTION>(p_params.quantity)}
    {
    }

    /// Retrieves the quantity in the desired Unit
    ///
    /// The quantity will be scaled to the target Unit.
    ///
    /// @tparam Unit target unit for the quantity
    /// @returns the quantity in the target Unit
    template <Units Unit = RESOLUTION>
    constexpr auto get() const -> QuantityType
    {
        return details::scaleQuantity<RESOLUTION, Unit>(m_quantity);
    }

    constexpr auto operator+=(LengthUnit const & p_other) noexcept -> LengthUnit &
    {
        m_quantity += p_other.m_quantity;
        return *this;
    }

    constexpr auto operator-=(LengthUnit const & p_other) noexcept -> LengthUnit &
    {
        m_quantity -= p_other.m_quantity;
        return *this;
    }

    constexpr auto operator<(LengthUnit const & p_other) const noexcept -> bool
    {
        return m_quantity < p_other.m_quantity;
    }

    constexpr auto operator>(LengthUnit const & p_other) const noexcept -> bool
    {
        return m_quantity > p_other.m_quantity;
    }

    constexpr auto operator==(LengthUnit const & p_other) const noexcept -> bool
    {
        return m_quantity == p_other.m_quantity;
    }

    constexpr auto operator!=(LengthUnit const & p_other) const noexcept -> bool
    {
        return m_quantity != p_other.m_quantity;
    }

    // friend functions
    friend constexpr auto operator-(jps::LengthUnit p_lu) -> jps::LengthUnit;

    friend constexpr auto operator*(jps::LengthUnit p_lu, double p_scalar) -> jps::LengthUnit;

    friend constexpr auto operator/(jps::LengthUnit p_lu, double p_scalar) -> jps::LengthUnit;

    friend constexpr auto operator/(jps::LengthUnit p_lu, jps::LengthUnit p_other) -> QuantityType;

private:
    /// Stores the length unit quantity stored in RESOLUTION
    QuantityType m_quantity{};
};

/// Helper for creating LengthUnit
///
/// @tparam Unit is the input Unit of p_quantity
/// @param p_quantity the quantity of the LengthUnit
/// @returns LengthUnit with the quantity
template <Units Unit>
constexpr auto makeLengthUnit(LengthUnit::QuantityType p_quantity) -> LengthUnit
{
    return LengthUnit{details::LengthUnitParams<LengthUnit::QuantityType, Unit>{p_quantity}};
}


/// arithmetic operations
constexpr inline auto operator+(jps::LengthUnit p_lhs, jps::LengthUnit const & p_rhs)
    -> jps::LengthUnit
{
    p_lhs += p_rhs;
    return p_lhs;
}

constexpr inline auto operator-(jps::LengthUnit const & p_lhs, jps::LengthUnit const & p_rhs)
    -> jps::LengthUnit
{
    auto res{p_lhs};
    res -= p_rhs;
    return res;
}

constexpr inline auto operator*(double p_scalar, jps::LengthUnit p_lu) -> jps::LengthUnit
{
    return p_lu * p_scalar;
}

constexpr inline auto operator-(jps::LengthUnit p_lu) -> jps::LengthUnit
{
    p_lu.m_quantity = -p_lu.m_quantity;
    return p_lu;
}

constexpr inline auto operator*(jps::LengthUnit p_lu, double p_scalar) -> jps::LengthUnit
{
    p_lu.m_quantity *= p_scalar;
    return p_lu;
}

constexpr inline auto operator/(jps::LengthUnit p_lu, double p_scalar) -> jps::LengthUnit
{
    p_lu.m_quantity /= p_scalar;
    return p_lu;
}

constexpr inline auto operator/(jps::LengthUnit p_lu, jps::LengthUnit p_other)
    -> LengthUnit::QuantityType
{
    return p_lu.m_quantity / p_other.m_quantity;
}
} // namespace jps
/// User defined literals for all units
/// Note that the cast is needed to silence compiler warning about narrowing down precision
constexpr inline auto operator"" _um(long double p_quantity) -> jps::LengthUnit
{
    return jps::makeLengthUnit<jps::Units::um>(
        static_cast<jps::LengthUnit::QuantityType>(p_quantity));
}
constexpr inline auto operator"" _mm(long double p_quantity) -> jps::LengthUnit
{
    return jps::makeLengthUnit<jps::Units::mm>(
        static_cast<jps::LengthUnit::QuantityType>(p_quantity));
}
constexpr inline auto operator"" _cm(long double p_quantity) -> jps::LengthUnit
{
    return jps::makeLengthUnit<jps::Units::cm>(
        static_cast<jps::LengthUnit::QuantityType>(p_quantity));
}
constexpr inline auto operator"" _dm(long double p_quantity) -> jps::LengthUnit
{
    return jps::makeLengthUnit<jps::Units::dm>(
        static_cast<jps::LengthUnit::QuantityType>(p_quantity));
}
constexpr inline auto operator"" _m(long double p_quantity) -> jps::LengthUnit
{
    return jps::makeLengthUnit<jps::Units::m>(
        static_cast<jps::LengthUnit::QuantityType>(p_quantity));
}
constexpr inline auto operator"" _km(long double p_quantity) -> jps::LengthUnit
{
    return jps::makeLengthUnit<jps::Units::km>(
        static_cast<jps::LengthUnit::QuantityType>(p_quantity));
}

/// User defined literals for integrals
/// Note that the cast is needed to silence compiler warning about narrowing down precision
constexpr inline auto operator"" _um(unsigned long long p_quantity) -> jps::LengthUnit
{
    return jps::makeLengthUnit<jps::Units::um>(
        static_cast<jps::LengthUnit::QuantityType>(p_quantity));
}
constexpr inline auto operator"" _mm(unsigned long long p_quantity) -> jps::LengthUnit
{
    return jps::makeLengthUnit<jps::Units::mm>(
        static_cast<jps::LengthUnit::QuantityType>(p_quantity));
}
constexpr inline auto operator"" _cm(unsigned long long p_quantity) -> jps::LengthUnit
{
    return jps::makeLengthUnit<jps::Units::cm>(
        static_cast<jps::LengthUnit::QuantityType>(p_quantity));
}
constexpr inline auto operator"" _dm(unsigned long long p_quantity) -> jps::LengthUnit
{
    return jps::makeLengthUnit<jps::Units::dm>(
        static_cast<jps::LengthUnit::QuantityType>(p_quantity));
}
constexpr inline auto operator"" _m(unsigned long long p_quantity) -> jps::LengthUnit
{
    return jps::makeLengthUnit<jps::Units::m>(
        static_cast<jps::LengthUnit::QuantityType>(p_quantity));
}
constexpr inline auto operator"" _km(unsigned long long p_quantity) -> jps::LengthUnit
{
    return jps::makeLengthUnit<jps::Units::km>(
        static_cast<jps::LengthUnit::QuantityType>(p_quantity));
}

namespace fmt
{
template <>
struct formatter<jps::LengthUnit> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext & p_ctx)
    {
        return p_ctx.begin();
    }

    template <typename FormatContext>
    auto format(jps::LengthUnit const & p_lu, FormatContext & p_ctx)
    {
        return format_to(p_ctx.out(), FMT_STRING("{:.4f} m"), p_lu.get<jps::Units::m>());
    }
};
} // namespace fmt
