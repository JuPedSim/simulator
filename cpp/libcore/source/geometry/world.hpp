#pragma once

#include "geometry/level.hpp"
#include "geometry/level_storage.hpp"
#include "line_segment.hpp"
#include "special_area.hpp"

#include <unordered_map>
#include <vector>

namespace jps
{
class World
{
private:
    using LevelStorageContainer = std::unordered_map<Level, LevelStorage>;
    LevelStorageContainer m_level_to_level_storage;

public:
    World()  = default;
    ~World() = default;

    World(const World &) = delete;
    auto operator=(const World &) -> World & = delete;

    World(World &&) = default;
    auto operator=(World &&) -> World & = default;

    auto addLineSegment(Level const & p_level, LineSegment const & p_segment) -> void;
    auto addSpecialArea(Level const & p_level, SpecialArea const & p_area) -> void;
    auto addLevel(Level const & p_level) -> LevelStorage &;
    auto getLevel(Level const & p_level) -> LevelStorage &;
    auto getLevel(Level const & p_level) const -> LevelStorage const &;
    auto getLevels() -> LevelStorageContainer & { return m_level_to_level_storage; };
    auto getLevels() const -> LevelStorageContainer const & { return m_level_to_level_storage; };
};
} // namespace jps
