#include "neighborhood/grid_2d.hpp"

#include <gtest/gtest.h>
#include <vector>

TEST(Grid2D, EmptyConstructor)
{
    using GridType = Grid2D<std::vector<int>>;
    GridType grid;

    // check some indices, all should be empty
    for(GridType::index_type i = -5; i != 5; ++i) {
        for(GridType::index_type j = -5; j != 5; ++j) {
            EXPECT_TRUE(grid[i][j].empty());
        }
    }
}

TEST(Grid2D, InsertAndRetreive)
{
    using GridType = Grid2D<std::vector<int>>;
    GridType grid;

    grid[0][0].push_back(1);
    grid[1][-1].push_back(2);
    grid[-1][1].push_back(3);
    grid[-1][-5].push_back(4);

    EXPECT_EQ(grid[0][0].size(), 1);
    EXPECT_EQ(grid[1][-1].size(), 1);
    EXPECT_EQ(grid[-1][1].size(), 1);
    EXPECT_EQ(grid[-1][-5].size(), 1);

    EXPECT_EQ(grid[0][0].front(), 1);
    EXPECT_EQ(grid[1][-1].front(), 2);
    EXPECT_EQ(grid[-1][1].front(), 3);
    EXPECT_EQ(grid[-1][-5].front(), 4);
}

TEST(Grid2D, ConstAccess)
{
    using GridType = Grid2D<std::vector<int>>;
    GridType grid;

    grid[0][0].push_back(1);
    grid[1][-1].push_back(2);
    grid[-1][1].push_back(3);
    grid[-1][-5].push_back(4);

    GridType const & const_grid = grid;

    EXPECT_TRUE(const_grid.get(0, 4).empty());
    EXPECT_EQ(grid.get(0, 0).front(), 1);
    EXPECT_EQ(grid.get(1, -1).front(), 2);
    EXPECT_EQ(grid.get(-1, 1).front(), 3);
    EXPECT_EQ(grid.get(-1, -5).front(), 4);
}
