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
constexpr T scaleQuantity(T p_quantity)
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
    LengthUnitParams & operator=(LengthUnitParams const & p_other) = delete;

    LengthUnitParams(LengthUnitParams && p_other) noexcept = default;
    LengthUnitParams & operator=(LengthUnitParams && p_other) noexcept = default;

    ~LengthUnitParams() = default;

    LengthUnitParams(QuantityType p_quantity) : quantity{p_quantity} {}
};
} // namespace details

class LengthUnit
{
public:
    using QuantityType = double;

    /// Defines the unit which is used to store the quantity internally
    const static Units RESOLUTION = Units::m;

    LengthUnit() = default;

    LengthUnit(LengthUnit const & p_other) = default;
    LengthUnit & operator=(LengthUnit const & p_other) = default;

    LengthUnit(LengthUnit && p_moved) noexcept = default;
    LengthUnit & operator=(LengthUnit && p_moved) noexcept = default;

    ~LengthUnit() = default;

    template <Units Unit>
    LengthUnit(details::LengthUnitParams<QuantityType, Unit> const & p_params) :
        m_quantity{details::scaleQuantity<Unit, RESOLUTION>(p_params.quantity)}
    {
    }

    template <Units unit = RESOLUTION>
    QuantityType get() const
    {
        return details::scaleQuantity<RESOLUTION, unit>(m_quantity);
    }

    LengthUnit & operator+=(LengthUnit const & p_other) noexcept
    {
        m_quantity += p_other.m_quantity;
        return *this;
    }


private:
    // Stores the length unit quantity in micro meter
    QuantityType m_quantity{};
};

template <Units Unit>
LengthUnit makeLengthUnit(LengthUnit::QuantityType p_quantity)
{
    return LengthUnit{details::LengthUnitParams<LengthUnit::QuantityType, Unit>{p_quantity}};
}

} // namespace jps

inline jps::LengthUnit operator+(jps::LengthUnit p_lhs, jps::LengthUnit const & p_rhs)
{
    p_lhs += p_rhs;
    return p_lhs;
}

/// User defined literals for all units
inline jps::LengthUnit operator"" _um(long double p_quantity)
{
    return jps::makeLengthUnit<jps::Units::um>(p_quantity);
}
inline jps::LengthUnit operator"" _mm(long double p_quantity)
{
    return jps::makeLengthUnit<jps::Units::mm>(p_quantity);
}
inline jps::LengthUnit operator"" _cm(long double p_quantity)
{
    return jps::makeLengthUnit<jps::Units::cm>(p_quantity);
}
inline jps::LengthUnit operator"" _dm(long double p_quantity)
{
    return jps::makeLengthUnit<jps::Units::dm>(p_quantity);
}
inline jps::LengthUnit operator"" _m(long double p_quantity)
{
    return jps::makeLengthUnit<jps::Units::m>(p_quantity);
}
inline jps::LengthUnit operator"" _km(long double p_quantity)
{
    return jps::makeLengthUnit<jps::Units::km>(p_quantity);
}

/// User defined literals for integrals
inline jps::LengthUnit operator"" _um(unsigned long long p_quantity)
{
    return jps::makeLengthUnit<jps::Units::um>(p_quantity);
}
inline jps::LengthUnit operator"" _mm(unsigned long long p_quantity)
{
    return jps::makeLengthUnit<jps::Units::mm>(p_quantity);
}
inline jps::LengthUnit operator"" _cm(unsigned long long p_quantity)
{
    return jps::makeLengthUnit<jps::Units::cm>(p_quantity);
}
inline jps::LengthUnit operator"" _dm(unsigned long long p_quantity)
{
    return jps::makeLengthUnit<jps::Units::dm>(p_quantity);
}
inline jps::LengthUnit operator"" _m(unsigned long long p_quantity)
{
    return jps::makeLengthUnit<jps::Units::m>(p_quantity);
}
inline jps::LengthUnit operator"" _km(unsigned long long p_quantity)
{
    return jps::makeLengthUnit<jps::Units::km>(p_quantity);
}
