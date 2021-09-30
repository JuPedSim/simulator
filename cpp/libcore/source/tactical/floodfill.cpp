#include "tactical/floodfill.hpp"


using namespace std;

jps::Floodfill::Floodfill() {
}

auto jps::Floodfill::changeInteger(Grid2D<int> p_grid, int p_old_number, int p_new_number, int p_x, int p_y) {

    if (p_x < 0 || p_x > 10 || p_y < 0 || p_y > 10) {
        return;
    }
    if (p_grid[p_x][p_y] != p_old_number) {
        return;
    }

    p_grid[p_x][p_y] = p_new_number;

    changeInteger(p_grid, p_old_number, p_new_number, p_x, p_y-1);
    changeInteger(p_grid, p_old_number, p_new_number, p_x+1, p_y);
    changeInteger(p_grid, p_old_number, p_new_number, p_x, p_y+1);
    changeInteger(p_grid, p_old_number, p_new_number, p_x-1, p_y);
}


auto jps::Floodfill::computeGrid(jps::Simulation const & p_simulation){

    /// 1 = Surface
    /// 2 = Wall
    /// 3 = Walkable (Relevant for Floodfill)

    World w = p_simulation.getWorld();

    /// go through all levels
    for (LevelStorage ls: w.getLevelStorages()){

        /// We have a start grid which we need to fill with values of the environment (per level)
        Grid2D<int> m_grid;

        /// fill 10x10 grid with 1s
        /// question: how big is a LevelStorage?
        for(int i = 0; i < 10; i++) {
            for(j = 0; j < 10; j++){
                m_grid[i][j] = 1;
            }
        }

      /// go through all walls
        for(LineSegment lineSegment: ls.getLineSegments()){

            /// starting point
            Coordinate m_start = lineSegment.getStart();
            /// ending point
            Coordinate m_end = lineSegment.getEnd();

            /// Fill grid with 2s if theres a wall
            /// question: What is between m_start and m_end? How does the wall run?
            m_grid[m_start.x][m_start.y] = 2;
            m_grid[m_end.x][m_end.y] = 2;

            /// question: Where is the starting point?
            Agent agent = ls.getAgents().begin();
            changeInteger(m_grid,1,3,agent.pos.x,agent.pos.y);


        }
        m_grids.push_back(m_grid);
        m_grid.clear();

    }

    /// return all grids
    return m_grids;
}