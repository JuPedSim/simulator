#include "geometry/coordinate.hpp"
#include "geometry/length_unit.hpp"
#include "neighborhood/neighborhood_search.hpp"

#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

TEST(NeighborhoodSearch, EmptyNeighborhood)
{
    using namespace jps;

    std::vector<Agent> empty_agents_vector;

    NeighborhoodSearch neighborhood_search(1_m, empty_agents_vector);

    Agent special_agent{{0_m, 0_m}};
    EXPECT_TRUE(neighborhood_search.getNeighborhood(special_agent).empty());

    special_agent.pos = {10_m, 0_m};
    EXPECT_TRUE(neighborhood_search.getNeighborhood(special_agent).empty());

    special_agent.pos = {5_m, 5_m};
    EXPECT_TRUE(neighborhood_search.getNeighborhood(special_agent).empty());

    special_agent.pos = {10_m, 20_m};
    EXPECT_TRUE(neighborhood_search.getNeighborhood(special_agent).empty());
}

TEST(NeighborhoodSearch, LengthUnitToIndex)
{
    EXPECT_EQ(jps::lengthUnitToIndex(1_m, 1_m), 1);
    EXPECT_EQ(jps::lengthUnitToIndex(1.1_m, 1_m), 1);
    EXPECT_EQ(jps::lengthUnitToIndex(0.99_m, 1_m), 0);

    EXPECT_EQ(jps::lengthUnitToIndex(-1_m, 1_m), -1);
    EXPECT_EQ(jps::lengthUnitToIndex(-1.1_m, 1_m), -2);
    EXPECT_EQ(jps::lengthUnitToIndex(-0.99_m, 1_m), -1);
}

class NeighborhoodSearchTests : public ::testing::Test
{
protected:
    int const m_sqrt_num_agents            = 5;
    jps::LengthUnit const m_agent_distance = 0.5_m;
    std::vector<jps::Agent> m_uniform_distributed_agents;
    jps::Agent m_special_agent{{0_m, 0_m}};

public:
    NeighborhoodSearchTests()
    {
        jps::LengthUnit max_distance = m_agent_distance * m_sqrt_num_agents;
        for(jps::LengthUnit x = 0_m; x != max_distance; x += m_agent_distance) {
            for(jps::LengthUnit y = 0_m; y != max_distance; y += m_agent_distance) {
                m_uniform_distributed_agents.emplace_back(jps::Coordinate{x, y});
            }
        }
    }
};

TEST_F(NeighborhoodSearchTests, SingleCellNeigborhood)
{
    jps::NeighborhoodSearch neighborhood_search(1_m, m_uniform_distributed_agents);

    auto neighborhood = neighborhood_search.getNeighborhood(m_special_agent, 0);
    EXPECT_EQ(neighborhood.size(), 4);

    // For single cell Neighborhood no agent is in cell -1, -1.
    m_special_agent.pos = {-0.1_m, -0.1_m};
    neighborhood        = neighborhood_search.getNeighborhood(m_special_agent, 0);
    EXPECT_EQ(neighborhood.size(), 0);

    // Move agent even further away
    m_special_agent.pos = {-10_m, -10_m};
    neighborhood        = neighborhood_search.getNeighborhood(m_special_agent, 0);
    EXPECT_EQ(neighborhood.size(), 0);
}

TEST_F(NeighborhoodSearchTests, LargeNeigborhood)
{
    jps::NeighborhoodSearch neighborhood_search(1_m, m_uniform_distributed_agents);

    auto neighborhood = neighborhood_search.getNeighborhood(m_special_agent, 1);
    EXPECT_EQ(neighborhood.size(), 16);

    // For Neighborhood with one cell distance agents can be found.
    m_special_agent.pos = {-0.1_m, -0.1_m};
    neighborhood        = neighborhood_search.getNeighborhood(m_special_agent, 1);
    EXPECT_EQ(neighborhood.size(), 4);

    // For far away no agents in neighborhood
    m_special_agent.pos = {-10_m, -10_m};
    neighborhood        = neighborhood_search.getNeighborhood(m_special_agent, 1);
    EXPECT_EQ(neighborhood.size(), 0);
    neighborhood = neighborhood_search.getNeighborhood(m_special_agent, 2);
    EXPECT_EQ(neighborhood.size(), 0);
    neighborhood = neighborhood_search.getNeighborhood(m_special_agent, 3);
    EXPECT_EQ(neighborhood.size(), 0);
}

TEST_F(NeighborhoodSearchTests, DifferentCellSize)
{
    jps::NeighborhoodSearch neighborhood_search(0.5_m, m_uniform_distributed_agents);

    auto neighborhood = neighborhood_search.getNeighborhood(m_special_agent, 1);
    EXPECT_EQ(neighborhood.size(), 4);

    // For Neighborhood with one cell distance agents can be found.
    m_special_agent.pos = {-0.1_m, -0.1_m};
    neighborhood        = neighborhood_search.getNeighborhood(m_special_agent, 1);
    EXPECT_EQ(neighborhood.size(), 1);

    // For far away no agents in neighborhood
    m_special_agent.pos = {-10_m, -10_m};
    neighborhood        = neighborhood_search.getNeighborhood(m_special_agent, 1);
    EXPECT_EQ(neighborhood.size(), 0);
    neighborhood = neighborhood_search.getNeighborhood(m_special_agent, 2);
    EXPECT_EQ(neighborhood.size(), 0);
    neighborhood = neighborhood_search.getNeighborhood(m_special_agent, 3);
    EXPECT_EQ(neighborhood.size(), 0);
}
