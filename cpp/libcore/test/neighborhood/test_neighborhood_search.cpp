#include "neighborhood/neighborhood_search.hpp"

#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

TEST(NeighborhoodSearch, EmptyNeighborhood)
{
    using namespace jps;

    Level lvl{0};
    NeighborhoodSearch neighborhood_search(0_m, 10_m, 0_m, 20_m, 1_m, {lvl});

    Agent special_agent{{0_m, 0_m, Level(0)}};
    EXPECT_TRUE(neighborhood_search.getNeighborhood(lvl, special_agent).empty());

    special_agent.pos = {10_m, 0_m, Level(0)};
    EXPECT_TRUE(neighborhood_search.getNeighborhood(lvl, special_agent).empty());

    special_agent.pos = {5_m, 5_m, Level(0)};
    EXPECT_TRUE(neighborhood_search.getNeighborhood(lvl, special_agent).empty());

    special_agent.pos = {10_m, 20_m, Level(0)};
    EXPECT_TRUE(neighborhood_search.getNeighborhood(lvl, special_agent).empty());
}

TEST(NeighborhoodSearch, NonEmptyNeighborhood)
{
    using namespace jps;
    using AgentRef = std::reference_wrapper<Agent>;

    Level lvl{0};
    LengthUnit cellsize = 1_m;
    NeighborhoodSearch neighborhood_search(-10_m, 10_m, -10_m, 10_m, cellsize, {lvl});

    size_t num_agents = 10;
    std::vector<Agent> agents_others{num_agents, Agent{{0_m, 0_m, Level(0)}}};
    std::vector<AgentRef> agents_others_ref;
    for(auto agent : agents_others) {
        agents_others_ref.emplace_back(std::ref(agent));
    }

    // Agents at the same position as the others
    Agent special_agent{{0_m, 0_m, Level(0)}};
    std::vector<Agent> agents = agents_others;
    agents.emplace_back(special_agent);

    std::unordered_map<std::int32_t, std::vector<Agent>> agents_per_level{{lvl.id(), agents}};

    neighborhood_search.update(agents_per_level);
    std::vector<Agent> neighborhood;
    auto neighborhood_ref = neighborhood_search.getNeighborhood(lvl, special_agent);
    for(auto neighbor : neighborhood_ref) {
        neighborhood.emplace_back(neighbor.get());
    }

    EXPECT_TRUE(!neighborhood.empty());
    EXPECT_THAT(neighborhood, ::testing::UnorderedElementsAreArray(agents_others));
    neighborhood.clear();
    neighborhood_ref.clear();

    // Move special_agent far away from others
    special_agent.pos = {10_m, 10_m, Level(0)};

    neighborhood_search.update(agents_per_level);
    neighborhood_ref = neighborhood_search.getNeighborhood(lvl, special_agent);
    EXPECT_TRUE(neighborhood_ref.empty());
    neighborhood.clear();
    neighborhood_ref.clear();

    // Move special_agent closer, but still too far away from others
    special_agent.pos = {0_m, 2 * cellsize, Level(0)};

    neighborhood_search.update(agents_per_level);
    neighborhood_ref = neighborhood_search.getNeighborhood(lvl, special_agent);
    EXPECT_TRUE(neighborhood_ref.empty());
    neighborhood.clear();
    neighborhood_ref.clear();

    // Move special agent inside cut off distance
    special_agent.pos = {0_m, cellsize - 0.1_m, Level(0)};

    neighborhood_search.update(agents_per_level);
    neighborhood_ref = neighborhood_search.getNeighborhood(lvl, special_agent);
    for(auto neighbor : neighborhood_ref) {
        neighborhood.emplace_back(neighbor.get());
    }

    EXPECT_THAT(neighborhood, ::testing::UnorderedElementsAreArray(agents_others));
    neighborhood.clear();
    neighborhood_ref.clear();
}
