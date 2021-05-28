#pragma once

#include "geometry/coordinate.hpp"
#include "geometry/length_unit.hpp"

namespace jps
{
struct Pedestrian {
    Coordinate pos{0_m, 0_m, jps::Level{1}};
};

} // namespace jps
