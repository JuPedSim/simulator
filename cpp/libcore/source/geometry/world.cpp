#include "world.hpp"

#include "geometry/level_storage.hpp"
#include "util/jpsexception.hpp"

namespace jps
{
auto World::addLevel(Level const & p_level) -> LevelStorage &
{
    if(m_level_to_level_storage.find(p_level) != m_level_to_level_storage.end()) {
        throw JPSGeometryException(
            fmt::format(FMT_STRING("Trying to add Level {} which already exists."), p_level));
    }
    return m_level_to_level_storage[p_level];
}

auto World::getLevelStorage(Level const & p_level) -> LevelStorage &
{
    return m_level_to_level_storage.at(p_level);
}

auto World::getLevelStorage(Level const & p_level) const -> LevelStorage const &
{
    return m_level_to_level_storage.at(p_level);
}

auto World::getAgents() -> std::unordered_map<Level, AgentsRef>
{
    std::unordered_map<Level, AgentsRef> agents_per_level;
    for(auto & [lvl, ls] : m_level_to_level_storage) {
        agents_per_level.emplace(lvl, ls.getAgents());
    }
    return agents_per_level;
}

} // namespace jps
