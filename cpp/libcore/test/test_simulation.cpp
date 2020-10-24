#include <gtest/gtest.h>
#include <simulation.hpp>

TEST(Example, SimulationReturns1)
{
    ASSERT_EQ(jps::Simulation().getValue(), 1);
}
