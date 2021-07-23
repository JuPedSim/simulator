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
    using Agents                = std::vector<Agent>;
    using AgentsRef             = std::reference_wrapper<Agents>;
    using LevelStorageContainer = std::unordered_map<Level, LevelStorage>;
    LevelStorageContainer m_level_to_level_storage;

public:
    World()  = default;
    ~World() = default;

    World(const World &) = delete;
    auto operator=(const World &) -> World & = delete;

    World(World &&) = default;
    auto operator=(World &&) -> World & = default;

    [[nodiscard]] auto addLevel(Level const & p_level) -> LevelStorage &;
    auto getLevelStorage(Level const & p_level) -> LevelStorage &;
    auto getLevelStorage(Level const & p_level) const -> LevelStorage const &;
    auto getLevelStorages() -> LevelStorageContainer & { return m_level_to_level_storage; };
    auto getLevelStorages() const -> LevelStorageContainer const &
    {
        return m_level_to_level_storage;
    };

    auto getAgents() -> std::unordered_map<Level, AgentsRef>;
};

} // namespace jps
