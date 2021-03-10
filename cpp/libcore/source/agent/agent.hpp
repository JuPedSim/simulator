#pragma once

#include "pedestrian.hpp"

#include <variant>

namespace jps
{
using Agent = std::variant<Pedestrian>;
}
