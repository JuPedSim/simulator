#include "geometry/helper.hpp"
#include "geometry/line_segment.hpp"

#include <gtest/gtest.h>

auto checkConnectivity(const std::vector<jps::LineSegment> & p_line_segments) -> void
{
    if(p_line_segments.size() > 1) {
        for(auto wall_itr = std::begin(p_line_segments); wall_itr != std::end(p_line_segments) - 1;
            ++wall_itr) {
            EXPECT_EQ(wall_itr->getEnd(), std::next(wall_itr)->getStart());
        }
    }
}

TEST(GeometryHelper, sortLineSegments) // NOLINTLINE
{
    using namespace jps;
    using namespace geometry;

    // Successful
    {
        std::vector<LineSegment> empty;
        EXPECT_NO_THROW(sortLineSegments(empty)); // NOLINTLINE
        EXPECT_TRUE(empty.empty());
        checkConnectivity(empty);

        std::vector<LineSegment> one_element{
            {{990_mm, 0.1_dm, Level{1}}, {1_mm, 0.1_km, Level{1}}}};
        EXPECT_NO_THROW(sortLineSegments(one_element)); // NOLINTLINE
        EXPECT_EQ(one_element.size(), 1);
        checkConnectivity(one_element);

        std::vector<LineSegment> pre_sorted{
            {{12_cm, 4_cm, Level{-1}}, {5.1_cm, -0.1_dm, Level{-1}}},
            {{5.1_cm, -0.1_dm, Level{-1}}, {-0.02_m, -20_mm, Level{-1}}},
            {{-0.02_m, -20_mm, Level{-1}}, {-15_cm, 30_mm, Level{-1}}},
            {{-15_cm, 30_mm, Level{-1}}, {12_cm, 4_cm, Level{-1}}}};
        EXPECT_NO_THROW(sortLineSegments(pre_sorted)); // NOLINTLINE
        checkConnectivity(pre_sorted);

        std::vector<LineSegment> without_rotation{
            {{3.1_m, 57_dm, Level{1}}, {1.1_m, 3_m, Level{1}}},
            {{0.1_m, 0.5_m, Level{1}}, {3.1_m, 57_dm, Level{1}}},
            {{-10.8_cm, 31_dm, Level{1}}, {-5.1_m, -2.4_m, Level{1}}},
            {{1.1_m, 3_m, Level{1}}, {-10.8_cm, 31_dm, Level{1}}},
            {{-5.1_m, -2.4_m, Level{1}}, {0.1_m, 0.5_m, Level{1}}},
        };
        EXPECT_NO_THROW(sortLineSegments(without_rotation)); // NOLINTLINE
        checkConnectivity(without_rotation);

        std::vector<LineSegment> with_rotation{
            {{3.1_m, 57_dm, Level{1}}, {1.1_m, 3_m, Level{1}}},
            {{0.1_m, 0.5_m, Level{1}}, {3.1_m, 57_dm, Level{1}}},
            {{-5.1_m, -2.4_m, Level{1}}, {-10.8_cm, 31_dm, Level{1}}},
            {{1.1_m, 3_m, Level{1}}, {-10.8_cm, 31_dm, Level{1}}},
            {{0.1_m, 0.5_m, Level{1}}, {-5.1_m, -2.4_m, Level{1}}},
        };
        EXPECT_NO_THROW(sortLineSegments(with_rotation)); // NOLINTLINE
        checkConnectivity(with_rotation);
    }

    // Not successful
    {
        std::vector<LineSegment> no_connection{
            {{3.1_m, 57_dm, Level{1}}, {1.1_m, 3_m, Level{1}}},
            {{0.1_m, 0.5_m, Level{1}}, {3.1_m, 57_dm, Level{1}}},
            {{1.1_m, 3_m, Level{1}}, {-10.8_cm, 31_dm, Level{1}}},
            {{0.1_m, 0.5_m, Level{1}}, {-5.1_m, -2.4_m, Level{1}}},
        };
        EXPECT_THROW(sortLineSegments(no_connection), std::runtime_error); // NOLINTLINE

        std::vector<LineSegment> duplicate_line_segment{
            {{3.1_m, 57_dm, Level{1}}, {1.1_m, 3_m, Level{1}}},
            {{0.1_m, 0.5_m, Level{1}}, {3.1_m, 57_dm, Level{1}}},
            {{-5.1_m, -2.4_m, Level{1}}, {-10.8_cm, 31_dm, Level{1}}},
            {{1.1_m, 3_m, Level{1}}, {-10.8_cm, 31_dm, Level{1}}},
            {{0.1_m, 0.5_m, Level{1}}, {-5.1_m, -2.4_m, Level{1}}},
            {{0.1_m, 0.5_m, Level{1}}, {-5.1_m, -2.4_m, Level{1}}},
        };
        EXPECT_THROW(sortLineSegments(duplicate_line_segment), std::runtime_error); // NOLINTLINE

        std::vector<LineSegment> different_levels{
            {{3.1_m, 57_dm, Level{1}}, {1.1_m, 3_m, Level{1}}},
            {{0.1_m, 0.5_m, Level{1}}, {3.1_m, 57_dm, Level{1}}},
            {{-5.1_m, -2.4_m, Level{1}}, {-10.8_cm, 31_dm, Level{1}}},
            {{1.1_m, 3_m, Level{1}}, {-10.8_cm, 31_dm, Level{1}}},
            {{0.1_m, 0.5_m, Level{2}}, {-5.1_m, -2.4_m, Level{2}}},
        };
        EXPECT_THROW(sortLineSegments(different_levels), std::runtime_error); // NOLINTLINE
    }
}