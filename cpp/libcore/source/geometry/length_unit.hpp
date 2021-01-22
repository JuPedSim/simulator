#pragma once

#include "enum.hpp"
#include "math/int_pow.hpp"

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
    const int diff_exp = toUnderlying(from) - toUnderlying(to);

    if constexpr(diff_exp < 0) {
        return p_quantity / jps::math::intPow<DECIMAL_BASE, -diff_exp>();
    } else {
        return p_quantity * jps::math::intPow<DECIMAL_BASE, diff_exp>();
    }
}

template <typename QuantityType, Units Unit>
struct LengthUnitParams {
    const QuantityType quantity; // NOLINT(misc-non-private-member-variables-in-classes)

    LengthUnitParams()                                 = delete;
    LengthUnitParams(LengthUnitParams const & p_other) = delete;
    auto operator=(LengthUnitParams const & p_other) -> LengthUnitParams & = delete;

    LengthUnitParams(LengthUnitParams && p_other) noexcept = default;
    auto operator=(LengthUnitParams && p_other) noexcept -> LengthUnitParams & = default;

    ~LengthUnitParams() = default;

    LengthUnitParams(QuantityType p_quantity) : quantity{p_quantity} {}
};
} // namespace details

class LengthUnit
{
    /// Defines the unit which is used to store the quantity internally
    const static Units RESOLUTION = Units::m;

public:
    using QuantityType = double;

    LengthUnit() = default;

    LengthUnit(LengthUnit const & p_other) = default;
    auto operator=(LengthUnit const & p_other) -> LengthUnit & = default;

    LengthUnit(LengthUnit && p_moved) noexcept = default;
    auto operator=(LengthUnit && p_moved) noexcept -> LengthUnit & = default;

    ~LengthUnit() = default;

    template <Units Unit>
    LengthUnit(details::LengthUnitParams<QuantityType, Unit> const & p_params) :
        m_quantity{details::scaleQuantity<Unit, RESOLUTION>(p_params.quantity)}
    {
    }

    template <Units unit = RESOLUTION>
    auto get() const -> QuantityType
    {
        return details::scaleQuantity<RESOLUTION, unit>(m_quantity);
    }

    auto operator+=(LengthUnit const & p_other) noexcept -> LengthUnit &
    {
        m_quantity += p_other.m_quantity;
        return *this;
    }

    auto operator-=(LengthUnit const & p_other) noexcept -> LengthUnit &
    {
        m_quantity -= p_other.m_quantity;
        return *this;
    }


private:
    // Stores the length unit quantity stored in RESOLUTION
    QuantityType m_quantity{};

    /// friend functions
    friend auto operator-(jps::LengthUnit p_lu) -> jps::LengthUnit
    {
        p_lu.m_quantity = -p_lu.m_quantity;
        return p_lu;
    }

    friend auto operator*(jps::LengthUnit p_lu, double p_scalar) -> jps::LengthUnit
    {
        p_lu.m_quantity *= p_scalar;
        return p_lu;
    }

    friend auto operator/(jps::LengthUnit p_lu, double p_scalar) -> jps::LengthUnit
    {
        p_lu.m_quantity /= p_scalar;
        return p_lu;
    }
};

template <Units Unit>
auto makeLengthUnit(LengthUnit::QuantityType p_quantity) -> LengthUnit
{
    return LengthUnit{details::LengthUnitParams<LengthUnit::QuantityType, Unit>{p_quantity}};
}

} // namespace jps


/// arithmetic operations
inline auto operator+(jps::LengthUnit p_lhs, jps::LengthUnit const & p_rhs) -> jps::LengthUnit
{
    p_lhs += p_rhs;
    return p_lhs;
}

inline auto operator-(jps::LengthUnit p_lhs, jps::LengthUnit const & p_rhs) -> jps::LengthUnit
{
    p_lhs -= p_rhs;
    return p_lhs;
}

inline auto operator*(double p_scalar, jps::LengthUnit p_lu) -> jps::LengthUnit
{
    return p_lu * p_scalar;
}
/// User defined literals for all units
inline auto operator"" _um(long double p_quantity) -> jps::LengthUnit
{
    return jps::makeLengthUnit<jps::Units::um>(p_quantity);
}
inline auto operator"" _mm(long double p_quantity) -> jps::LengthUnit
{
    return jps::makeLengthUnit<jps::Units::mm>(p_quantity);
}
inline auto operator"" _cm(long double p_quantity) -> jps::LengthUnit
{
    return jps::makeLengthUnit<jps::Units::cm>(p_quantity);
}
inline auto operator"" _dm(long double p_quantity) -> jps::LengthUnit
{
    return jps::makeLengthUnit<jps::Units::dm>(p_quantity);
}
inline auto operator"" _m(long double p_quantity) -> jps::LengthUnit
{
    return jps::makeLengthUnit<jps::Units::m>(p_quantity);
}
inline auto operator"" _km(long double p_quantity) -> jps::LengthUnit
{
    return jps::makeLengthUnit<jps::Units::km>(p_quantity);
}

/// User defined literals for integrals
inline auto operator"" _um(unsigned long long p_quantity) -> jps::LengthUnit
{
    return jps::makeLengthUnit<jps::Units::um>(p_quantity);
}
inline auto operator"" _mm(unsigned long long p_quantity) -> jps::LengthUnit
{
    return jps::makeLengthUnit<jps::Units::mm>(p_quantity);
}
inline auto operator"" _cm(unsigned long long p_quantity) -> jps::LengthUnit
{
    return jps::makeLengthUnit<jps::Units::cm>(p_quantity);
}
inline auto operator"" _dm(unsigned long long p_quantity) -> jps::LengthUnit
{
    return jps::makeLengthUnit<jps::Units::dm>(p_quantity);
}
inline auto operator"" _m(unsigned long long p_quantity) -> jps::LengthUnit
{
    return jps::makeLengthUnit<jps::Units::m>(p_quantity);
}
inline auto operator"" _km(unsigned long long p_quantity) -> jps::LengthUnit
{
    return jps::makeLengthUnit<jps::Units::km>(p_quantity);
}
