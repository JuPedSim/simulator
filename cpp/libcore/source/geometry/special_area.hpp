#pragma once

#include "area.hpp"

#include <cstdint>
#include <utility>
namespace jps
{
class SpecialArea
{
    Area m_area;
    std::uint32_t m_id{};

public:
    SpecialArea(Area p_area, std::uint32_t p_id) : m_area(std::move(p_area)), m_id(p_id){};
};
} // namespace jps
