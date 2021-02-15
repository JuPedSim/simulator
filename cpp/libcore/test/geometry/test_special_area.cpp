#include "geometry/special_area.hpp"

#include <cmath>
#include <gtest/gtest.h>

// NOLINTNEXTLINE
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
        EXPECT_EQ(special_area.getID(), id);
        EXPECT_EQ(special_area.getArea(), area);
        reference_values.emplace_back(special_area);
    }

    for(auto const & reference_value : reference_values) {
        // copy constructor
        SpecialArea copy_constructed{reference_value}; // NOLINTLINE
        EXPECT_EQ(reference_value, copy_constructed);

        // copy assignment operator
        SpecialArea copy_assigned = reference_value; // NOLINTLINE
        EXPECT_EQ(reference_value, copy_assigned);

        // move constructor
        SpecialArea before_move_constructor{reference_value};
        SpecialArea move_constructed{std::move(before_move_constructor)};
        EXPECT_EQ(reference_value, move_constructed);

        // move assignment operator
        SpecialArea before_move_assigned{reference_value};
        SpecialArea move_assigned = std::move(before_move_assigned);
        EXPECT_EQ(reference_value, move_assigned);
    }
}

TEST(SpecialArea, comparisonOperators) // NOLINTLINE
{
    using namespace jps;
    // ==
    EXPECT_TRUE(
        (SpecialArea{
            10,
            Area{std::vector<Coordinate>{
                {-4.1_cm, 3.7_cm, Level{1}},
                {3.1_cm, 4.9_cm, Level{1}},
                {7.5_cm, 2.3_cm, Level{1}},
                {9.2_cm, -3.1_cm, Level{1}},
                {4.1_cm, -5.9_cm, Level{1}},
                {1_cm, -1.5_cm, Level{1}},
                {-2_cm, -4.7_cm, Level{1}},
                {-6.3_cm, -2.1_cm, Level{1}}}}}) == (SpecialArea{
                                                        10,
                                                        Area{std::vector<Coordinate>{
                                                            {-10_cm, 0_cm, Level{1}},
                                                            {-20_m, 1_m, Level{1}},
                                                            {-20_m, 4_m, Level{1}},
                                                            {-15_m, 1_m, Level{1}},
                                                            {-10_cm, 0_cm, Level{1}}}}}));

    EXPECT_TRUE(
        (SpecialArea{
            123,
            Area{std::vector<LineSegment>{
                LineSegment{{-4.1_cm, 3.7_cm, Level{1}}, {3.1_cm, 4.9_cm, Level{1}}},
                LineSegment{{3.1_cm, 4.9_cm, Level{1}}, {7.5_cm, 2.3_cm, Level{1}}},
                LineSegment{{7.5_cm, 2.3_cm, Level{1}}, {9.2_cm, -3.1_cm, Level{1}}},
                LineSegment{{9.2_cm, -3.1_cm, Level{1}}, {4.1_cm, -5.9_cm, Level{1}}},
                LineSegment{{4.1_cm, -5.9_cm, Level{1}}, {1_cm, -1.5_cm, Level{1}}},
                LineSegment{{1_cm, -1.5_cm, Level{1}}, {-2_cm, -4.7_cm, Level{1}}},
                LineSegment{{-2_cm, -4.7_cm, Level{1}}, {-6.3_cm, -2.1_cm, Level{1}}},
                LineSegment{{-6.3_cm, -2.1_cm, Level{1}}, {-4.1_cm, 3.7_cm, Level{1}}}}}}) ==
        (SpecialArea{
            123,
            Area{std::vector<LineSegment>{
                LineSegment{{-4.1_cm, 3.7_cm, Level{1}}, {3.1_cm, 4.9_cm, Level{1}}},
                LineSegment{{3.1_cm, 4.9_cm, Level{1}}, {7.5_cm, 2.3_cm, Level{1}}},
                LineSegment{{7.5_cm, 2.3_cm, Level{1}}, {9.2_cm, -3.1_cm, Level{1}}},
                LineSegment{{9.2_cm, -3.1_cm, Level{1}}, {4.1_cm, -5.9_cm, Level{1}}},
                LineSegment{{4.1_cm, -5.9_cm, Level{1}}, {1_cm, -1.5_cm, Level{1}}},
                LineSegment{{1_cm, -1.5_cm, Level{1}}, {-2_cm, -4.7_cm, Level{1}}},
                LineSegment{{-2_cm, -4.7_cm, Level{1}}, {-6.3_cm, -2.1_cm, Level{1}}},
                LineSegment{{-6.3_cm, -2.1_cm, Level{1}}, {-4.1_cm, 3.7_cm, Level{1}}}}}}));
    EXPECT_TRUE(
        (SpecialArea{
            123,
            Area{std::vector<LineSegment>{
                LineSegment{{-4.1_cm, 3.7_cm, Level{1}}, {3.1_cm, 4.9_cm, Level{1}}},
                LineSegment{{3.1_cm, 4.9_cm, Level{1}}, {7.5_cm, 2.3_cm, Level{1}}},
                LineSegment{{7.5_cm, 2.3_cm, Level{1}}, {9.2_cm, -3.1_cm, Level{1}}},
                LineSegment{{9.2_cm, -3.1_cm, Level{1}}, {4.1_cm, -5.9_cm, Level{1}}},
                LineSegment{{4.1_cm, -5.9_cm, Level{1}}, {1_cm, -1.5_cm, Level{1}}},
                LineSegment{{1_cm, -1.5_cm, Level{1}}, {-2_cm, -4.7_cm, Level{1}}},
                LineSegment{{-2_cm, -4.7_cm, Level{1}}, {-6.3_cm, -2.1_cm, Level{1}}},
                LineSegment{{-6.3_cm, -2.1_cm, Level{1}}, {-4.1_cm, 3.7_cm, Level{1}}}}}}) ==
        (SpecialArea{
            123,
            Area{std::vector<Coordinate>{
                {-4.1_cm, 3.7_cm, Level{1}},
                {3.1_cm, 4.9_cm, Level{1}},
                {9.2_cm, -3.1_cm, Level{1}},
                {4.1_cm, -5.9_cm, Level{1}},
                {-2_cm, -4.7_cm, Level{1}},
                {-6.3_cm, -2.1_cm, Level{1}}}}}));

    EXPECT_FALSE(
        (SpecialArea{
            10,
            Area{std::vector<Coordinate>{
                {-4.1_cm, 3.7_cm, Level{1}},
                {3.1_cm, 4.9_cm, Level{1}},
                {7.5_cm, 2.3_cm, Level{1}},
                {9.2_cm, -3.1_cm, Level{1}},
                {4.1_cm, -5.9_cm, Level{1}},
                {1_cm, -1.5_cm, Level{1}},
                {-2_cm, -4.7_cm, Level{1}},
                {-6.3_cm, -2.1_cm, Level{1}}}}}) == (SpecialArea{
                                                        67,
                                                        Area{std::vector<Coordinate>{
                                                            {-10_cm, 0_cm, Level{1}},
                                                            {-20_m, 1_m, Level{1}},
                                                            {-20_m, 4_m, Level{1}},
                                                            {-15_m, 1_m, Level{1}},
                                                            {-10_cm, 0_cm, Level{1}}}}}));

    EXPECT_FALSE(
        (SpecialArea{
            67,
            Area{std::vector<Coordinate>{
                {-10_cm, 0_cm, Level{1}},
                {-20_m, 1_m, Level{1}},
                {-20_m, 4_m, Level{1}},
                {-15_m, 1_m, Level{1}},
                {-10_cm, 0_cm, Level{1}}}}}) ==
        (SpecialArea{
            123,
            Area{std::vector<LineSegment>{
                LineSegment{{-4.1_cm, 3.7_cm, Level{1}}, {3.1_cm, 4.9_cm, Level{1}}},
                LineSegment{{3.1_cm, 4.9_cm, Level{1}}, {7.5_cm, 2.3_cm, Level{1}}},
                LineSegment{{7.5_cm, 2.3_cm, Level{1}}, {9.2_cm, -3.1_cm, Level{1}}},
                LineSegment{{9.2_cm, -3.1_cm, Level{1}}, {4.1_cm, -5.9_cm, Level{1}}},
                LineSegment{{4.1_cm, -5.9_cm, Level{1}}, {1_cm, -1.5_cm, Level{1}}},
                LineSegment{{1_cm, -1.5_cm, Level{1}}, {-2_cm, -4.7_cm, Level{1}}},
                LineSegment{{-2_cm, -4.7_cm, Level{1}}, {-6.3_cm, -2.1_cm, Level{1}}},
                LineSegment{{-6.3_cm, -2.1_cm, Level{1}}, {-4.1_cm, 3.7_cm, Level{1}}}}}}));

    EXPECT_FALSE(
        (SpecialArea{
            123,
            Area{std::vector<LineSegment>{
                LineSegment{{-4.1_cm, 3.7_cm, Level{1}}, {3.1_cm, 4.9_cm, Level{1}}},
                LineSegment{{3.1_cm, 4.9_cm, Level{1}}, {7.5_cm, 2.3_cm, Level{1}}},
                LineSegment{{7.5_cm, 2.3_cm, Level{1}}, {9.2_cm, -3.1_cm, Level{1}}},
                LineSegment{{9.2_cm, -3.1_cm, Level{1}}, {4.1_cm, -5.9_cm, Level{1}}},
                LineSegment{{4.1_cm, -5.9_cm, Level{1}}, {1_cm, -1.5_cm, Level{1}}},
                LineSegment{{1_cm, -1.5_cm, Level{1}}, {-2_cm, -4.7_cm, Level{1}}},
                LineSegment{{-2_cm, -4.7_cm, Level{1}}, {-6.3_cm, -2.1_cm, Level{1}}},
                LineSegment{{-6.3_cm, -2.1_cm, Level{1}}, {-4.1_cm, 3.7_cm, Level{1}}}}}}) ==
        (SpecialArea{
            0,
            Area{std::vector<Coordinate>{
                {-4.1_cm, 3.7_cm, Level{1}},
                {3.1_cm, 4.9_cm, Level{1}},
                {9.2_cm, -3.1_cm, Level{1}},
                {4.1_cm, -5.9_cm, Level{1}},
                {-2_cm, -4.7_cm, Level{1}},
                {-6.3_cm, -2.1_cm, Level{1}}}}}));

    // !=
    EXPECT_TRUE(
        (SpecialArea{
            10,
            Area{std::vector<Coordinate>{
                {-4.1_cm, 3.7_cm, Level{1}},
                {3.1_cm, 4.9_cm, Level{1}},
                {7.5_cm, 2.3_cm, Level{1}},
                {9.2_cm, -3.1_cm, Level{1}},
                {4.1_cm, -5.9_cm, Level{1}},
                {1_cm, -1.5_cm, Level{1}},
                {-2_cm, -4.7_cm, Level{1}},
                {-6.3_cm, -2.1_cm, Level{1}}}}}) != (SpecialArea{
                                                        67,
                                                        Area{std::vector<Coordinate>{
                                                            {-10_cm, 0_cm, Level{1}},
                                                            {-20_m, 1_m, Level{1}},
                                                            {-20_m, 4_m, Level{1}},
                                                            {-15_m, 1_m, Level{1}},
                                                            {-10_cm, 0_cm, Level{1}}}}}));

    EXPECT_TRUE(
        (SpecialArea{
            67,
            Area{std::vector<Coordinate>{
                {-10_cm, 0_cm, Level{1}},
                {-20_m, 1_m, Level{1}},
                {-20_m, 4_m, Level{1}},
                {-15_m, 1_m, Level{1}},
                {-10_cm, 0_cm, Level{1}}}}}) !=
        (SpecialArea{
            123,
            Area{std::vector<LineSegment>{
                LineSegment{{-4.1_cm, 3.7_cm, Level{1}}, {3.1_cm, 4.9_cm, Level{1}}},
                LineSegment{{3.1_cm, 4.9_cm, Level{1}}, {7.5_cm, 2.3_cm, Level{1}}},
                LineSegment{{7.5_cm, 2.3_cm, Level{1}}, {9.2_cm, -3.1_cm, Level{1}}},
                LineSegment{{9.2_cm, -3.1_cm, Level{1}}, {4.1_cm, -5.9_cm, Level{1}}},
                LineSegment{{4.1_cm, -5.9_cm, Level{1}}, {1_cm, -1.5_cm, Level{1}}},
                LineSegment{{1_cm, -1.5_cm, Level{1}}, {-2_cm, -4.7_cm, Level{1}}},
                LineSegment{{-2_cm, -4.7_cm, Level{1}}, {-6.3_cm, -2.1_cm, Level{1}}},
                LineSegment{{-6.3_cm, -2.1_cm, Level{1}}, {-4.1_cm, 3.7_cm, Level{1}}}}}}));

    EXPECT_TRUE(
        (SpecialArea{
            123,
            Area{std::vector<LineSegment>{
                LineSegment{{-4.1_cm, 3.7_cm, Level{1}}, {3.1_cm, 4.9_cm, Level{1}}},
                LineSegment{{3.1_cm, 4.9_cm, Level{1}}, {7.5_cm, 2.3_cm, Level{1}}},
                LineSegment{{7.5_cm, 2.3_cm, Level{1}}, {9.2_cm, -3.1_cm, Level{1}}},
                LineSegment{{9.2_cm, -3.1_cm, Level{1}}, {4.1_cm, -5.9_cm, Level{1}}},
                LineSegment{{4.1_cm, -5.9_cm, Level{1}}, {1_cm, -1.5_cm, Level{1}}},
                LineSegment{{1_cm, -1.5_cm, Level{1}}, {-2_cm, -4.7_cm, Level{1}}},
                LineSegment{{-2_cm, -4.7_cm, Level{1}}, {-6.3_cm, -2.1_cm, Level{1}}},
                LineSegment{{-6.3_cm, -2.1_cm, Level{1}}, {-4.1_cm, 3.7_cm, Level{1}}}}}}) !=
        (SpecialArea{
            0,
            Area{std::vector<Coordinate>{
                {-4.1_cm, 3.7_cm, Level{1}},
                {3.1_cm, 4.9_cm, Level{1}},
                {9.2_cm, -3.1_cm, Level{1}},
                {4.1_cm, -5.9_cm, Level{1}},
                {-2_cm, -4.7_cm, Level{1}},
                {-6.3_cm, -2.1_cm, Level{1}}}}}));
    EXPECT_FALSE(
        (SpecialArea{
            10,
            Area{std::vector<Coordinate>{
                {-4.1_cm, 3.7_cm, Level{1}},
                {3.1_cm, 4.9_cm, Level{1}},
                {7.5_cm, 2.3_cm, Level{1}},
                {9.2_cm, -3.1_cm, Level{1}},
                {4.1_cm, -5.9_cm, Level{1}},
                {1_cm, -1.5_cm, Level{1}},
                {-2_cm, -4.7_cm, Level{1}},
                {-6.3_cm, -2.1_cm, Level{1}}}}}) != (SpecialArea{
                                                        10,
                                                        Area{std::vector<Coordinate>{
                                                            {-10_cm, 0_cm, Level{1}},
                                                            {-20_m, 1_m, Level{1}},
                                                            {-20_m, 4_m, Level{1}},
                                                            {-15_m, 1_m, Level{1}},
                                                            {-10_cm, 0_cm, Level{1}}}}}));

    EXPECT_FALSE(
        (SpecialArea{
            123,
            Area{std::vector<LineSegment>{
                LineSegment{{-4.1_cm, 3.7_cm, Level{1}}, {3.1_cm, 4.9_cm, Level{1}}},
                LineSegment{{3.1_cm, 4.9_cm, Level{1}}, {7.5_cm, 2.3_cm, Level{1}}},
                LineSegment{{7.5_cm, 2.3_cm, Level{1}}, {9.2_cm, -3.1_cm, Level{1}}},
                LineSegment{{9.2_cm, -3.1_cm, Level{1}}, {4.1_cm, -5.9_cm, Level{1}}},
                LineSegment{{4.1_cm, -5.9_cm, Level{1}}, {1_cm, -1.5_cm, Level{1}}},
                LineSegment{{1_cm, -1.5_cm, Level{1}}, {-2_cm, -4.7_cm, Level{1}}},
                LineSegment{{-2_cm, -4.7_cm, Level{1}}, {-6.3_cm, -2.1_cm, Level{1}}},
                LineSegment{{-6.3_cm, -2.1_cm, Level{1}}, {-4.1_cm, 3.7_cm, Level{1}}}}}}) !=
        (SpecialArea{
            123,
            Area{std::vector<LineSegment>{
                LineSegment{{-4.1_cm, 3.7_cm, Level{1}}, {3.1_cm, 4.9_cm, Level{1}}},
                LineSegment{{3.1_cm, 4.9_cm, Level{1}}, {7.5_cm, 2.3_cm, Level{1}}},
                LineSegment{{7.5_cm, 2.3_cm, Level{1}}, {9.2_cm, -3.1_cm, Level{1}}},
                LineSegment{{9.2_cm, -3.1_cm, Level{1}}, {4.1_cm, -5.9_cm, Level{1}}},
                LineSegment{{4.1_cm, -5.9_cm, Level{1}}, {1_cm, -1.5_cm, Level{1}}},
                LineSegment{{1_cm, -1.5_cm, Level{1}}, {-2_cm, -4.7_cm, Level{1}}},
                LineSegment{{-2_cm, -4.7_cm, Level{1}}, {-6.3_cm, -2.1_cm, Level{1}}},
                LineSegment{{-6.3_cm, -2.1_cm, Level{1}}, {-4.1_cm, 3.7_cm, Level{1}}}}}}));
    EXPECT_FALSE(
        (SpecialArea{
            123,
            Area{std::vector<LineSegment>{
                LineSegment{{-4.1_cm, 3.7_cm, Level{1}}, {3.1_cm, 4.9_cm, Level{1}}},
                LineSegment{{3.1_cm, 4.9_cm, Level{1}}, {7.5_cm, 2.3_cm, Level{1}}},
                LineSegment{{7.5_cm, 2.3_cm, Level{1}}, {9.2_cm, -3.1_cm, Level{1}}},
                LineSegment{{9.2_cm, -3.1_cm, Level{1}}, {4.1_cm, -5.9_cm, Level{1}}},
                LineSegment{{4.1_cm, -5.9_cm, Level{1}}, {1_cm, -1.5_cm, Level{1}}},
                LineSegment{{1_cm, -1.5_cm, Level{1}}, {-2_cm, -4.7_cm, Level{1}}},
                LineSegment{{-2_cm, -4.7_cm, Level{1}}, {-6.3_cm, -2.1_cm, Level{1}}},
                LineSegment{{-6.3_cm, -2.1_cm, Level{1}}, {-4.1_cm, 3.7_cm, Level{1}}}}}}) !=
        (SpecialArea{
            123,
            Area{std::vector<Coordinate>{
                {-4.1_cm, 3.7_cm, Level{1}},
                {3.1_cm, 4.9_cm, Level{1}},
                {9.2_cm, -3.1_cm, Level{1}},
                {4.1_cm, -5.9_cm, Level{1}},
                {-2_cm, -4.7_cm, Level{1}},
                {-6.3_cm, -2.1_cm, Level{1}}}}}));
}