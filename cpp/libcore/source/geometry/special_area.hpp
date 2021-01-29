#pragma once

#include "area.hpp"

#include <cstdint>
namespace jps
{
class SpecialArea
{
    Area m_area;
    std::uint32_t m_id{};
};
} // namespace jps
