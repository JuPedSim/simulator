#include "geometry/special_area.hpp"

#include <cmath>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(SpecialArea, Constructor)
{
    using namespace jps;
    std::vector<Area> areas{
        Area{std::vector<Coordinate>{
            {-4.1_cm, 3.7_cm},
            {3.1_cm, 4.9_cm},
            {7.5_cm, 2.3_cm},
            {9.2_cm, -3.1_cm},
            {4.1_cm, -5.9_cm},
            {1_cm, -1.5_cm},
            {-2_cm, -4.7_cm},
            {-6.3_cm, -2.1_cm}}},
        Area{std::vector<Coordinate>{
            {-10_cm, 0_cm}, {-20_m, 1_m}, {-20_m, 4_m}, {-15_m, 1_m}, {-10_cm, 0_cm}}},
        Area{std::vector<LineSegment>{
            LineSegment{{-4.1_cm, 3.7_cm}, {3.1_cm, 4.9_cm}},
            LineSegment{{3.1_cm, 4.9_cm}, {7.5_cm, 2.3_cm}},
            LineSegment{{7.5_cm, 2.3_cm}, {9.2_cm, -3.1_cm}},
            LineSegment{{9.2_cm, -3.1_cm}, {4.1_cm, -5.9_cm}},
            LineSegment{{4.1_cm, -5.9_cm}, {1_cm, -1.5_cm}},
            LineSegment{{1_cm, -1.5_cm}, {-2_cm, -4.7_cm}},
            LineSegment{{-2_cm, -4.7_cm}, {-6.3_cm, -2.1_cm}},
            LineSegment{{-6.3_cm, -2.1_cm}, {-4.1_cm, 3.7_cm}}}},
        Area{std::vector<Coordinate>{
            {-4.1_cm, 3.7_cm},
            {3.1_cm, 4.9_cm},
            {9.2_cm, -3.1_cm},
            {4.1_cm, -5.9_cm},
            {-2_cm, -4.7_cm},
            {-6.3_cm, -2.1_cm}}}};

    // Simple constructor
    std::vector<SpecialArea> reference_values;
    for(auto const & area : areas) {
        SpecialArea special_area{area};
        EXPECT_EQ(special_area.getArea(), area);
        reference_values.emplace_back(std::move(special_area));
    }

    for(auto & reference_value : reference_values) {
        auto area_before = reference_value.getArea();

        // move constructor
        SpecialArea move_constructed{std::move(reference_value)};
        EXPECT_EQ(move_constructed.getArea(), area_before);

        // move assignment operator
        SpecialArea move_assigned = std::move(move_constructed);
        EXPECT_EQ(move_assigned.getArea(), area_before);
    }
}
