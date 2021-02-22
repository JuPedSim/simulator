#include "geometry/special_area.hpp"

#include <cmath>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(SpecialArea, Constructor)
{
    using namespace jps;
    std::map<std::uint32_t, Area> areas{
        {10,
         Area{std::vector<Coordinate>{
             {-4.1_cm, 3.7_cm, Level{1}},
             {3.1_cm, 4.9_cm, Level{1}},
             {7.5_cm, 2.3_cm, Level{1}},
             {9.2_cm, -3.1_cm, Level{1}},
             {4.1_cm, -5.9_cm, Level{1}},
             {1_cm, -1.5_cm, Level{1}},
             {-2_cm, -4.7_cm, Level{1}},
             {-6.3_cm, -2.1_cm, Level{1}}}}},
        {67,
         Area{std::vector<Coordinate>{
             {-10_cm, 0_cm, Level{1}},
             {-20_m, 1_m, Level{1}},
             {-20_m, 4_m, Level{1}},
             {-15_m, 1_m, Level{1}},
             {-10_cm, 0_cm, Level{1}}}}},
        {123,
         Area{std::vector<LineSegment>{
             LineSegment{{-4.1_cm, 3.7_cm, Level{1}}, {3.1_cm, 4.9_cm, Level{1}}},
             LineSegment{{3.1_cm, 4.9_cm, Level{1}}, {7.5_cm, 2.3_cm, Level{1}}},
             LineSegment{{7.5_cm, 2.3_cm, Level{1}}, {9.2_cm, -3.1_cm, Level{1}}},
             LineSegment{{9.2_cm, -3.1_cm, Level{1}}, {4.1_cm, -5.9_cm, Level{1}}},
             LineSegment{{4.1_cm, -5.9_cm, Level{1}}, {1_cm, -1.5_cm, Level{1}}},
             LineSegment{{1_cm, -1.5_cm, Level{1}}, {-2_cm, -4.7_cm, Level{1}}},
             LineSegment{{-2_cm, -4.7_cm, Level{1}}, {-6.3_cm, -2.1_cm, Level{1}}},
             LineSegment{{-6.3_cm, -2.1_cm, Level{1}}, {-4.1_cm, 3.7_cm, Level{1}}}}}},
        {0,
         Area{std::vector<Coordinate>{
             {-4.1_cm, 3.7_cm, Level{1}},
             {3.1_cm, 4.9_cm, Level{1}},
             {9.2_cm, -3.1_cm, Level{1}},
             {4.1_cm, -5.9_cm, Level{1}},
             {-2_cm, -4.7_cm, Level{1}},
             {-6.3_cm, -2.1_cm, Level{1}}}}}};

    // Simple constructor
    std::vector<SpecialArea> reference_values;
    for(auto const & [id, area] : areas) {
        SpecialArea special_area{id, area};
        EXPECT_EQ(special_area.getExternalID(), id);
        EXPECT_EQ(special_area.getArea(), area);
        reference_values.emplace_back(std::move(special_area));
    }

    for(auto & reference_value : reference_values) {
        auto external_id = reference_value.getExternalID();
        auto area_before = reference_value.getArea();

        // move constructor
        SpecialArea move_constructed{std::move(reference_value)};
        EXPECT_EQ(move_constructed.getExternalID(), external_id);
        EXPECT_EQ(move_constructed.getArea(), area_before);

        // move assignment operator
        SpecialArea move_assigned = std::move(move_constructed);
        EXPECT_EQ(move_assigned.getExternalID(), external_id);
        EXPECT_EQ(move_assigned.getArea(), area_before);
    }
}
