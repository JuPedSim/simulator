#include "util/jpsexception.hpp"
#include "util/simulation_clock.hpp"

#include <chrono>
#include <gtest/gtest.h>


TEST(SimulationClock, general)
{
    std::vector<std::pair<std::uint64_t, std::chrono::milliseconds>> clock{
        {12, std::chrono::milliseconds{10}},
        {50, std::chrono::milliseconds{1}},
        {3456, std::chrono::milliseconds{100}},
        {9999, std::chrono::milliseconds{5000}}};

    for(auto [max_steps, delta_t] : clock) {
        SimulationClock s{max_steps, delta_t};
        EXPECT_EQ(s.getMaxSteps(), max_steps);
        EXPECT_EQ(s.getDeltaT(), delta_t);

        int i = 1;
        while(s.advance()) {
            EXPECT_EQ(s.getCurrentStep(), i);
            EXPECT_EQ(s.getCurrentTime(), i * delta_t);
            i++;
        };

        EXPECT_EQ(s.getCurrentStep(), max_steps);
        s.advance();
        s.advance();
        EXPECT_EQ(s.getCurrentStep(), max_steps);
    }
}

TEST(SimulationClock, invalid)
{
    EXPECT_THROW(SimulationClock s(10, std::chrono::milliseconds{-10}), JPSException);
    EXPECT_THROW(SimulationClock s(10, std::chrono::milliseconds{0}), JPSException);
}
