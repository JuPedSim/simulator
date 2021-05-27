#include "util/jpsexception.hpp"
#include "util/simulation_clock.hpp"

#include <gtest/gtest.h>
#include <memory>


TEST(SimulationClock, general)
{
    std::vector<std::pair<std::uint64_t, double>> clock{
        {12, 0.1}, {50, 1}, {3456, 0.05}, {634553, 0.0001}};

    for(auto [max_steps, delta_t] : clock) {
        SimulationClock s{max_steps, delta_t};
        EXPECT_EQ(s.getMaxSteps(), max_steps);
        EXPECT_EQ(s.getDeltaT(), delta_t);

        for(std::uint64_t i = 0; i < max_steps; ++i) {
            EXPECT_EQ(s.getCurrentStep(), i);
            EXPECT_EQ(s.getCurrentTime(), static_cast<double>(i) * delta_t);
            s.advance();
        }

        EXPECT_EQ(s.getCurrentStep(), max_steps);
        EXPECT_THROW(s.advance(), JPSException);
    }
}

TEST(SimulationClock, invalid)
{
    EXPECT_THROW(SimulationClock s(10, -1), JPSException);
}
