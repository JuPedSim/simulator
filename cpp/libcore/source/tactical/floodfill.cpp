#include "tactical/floodfill.hpp"


using namespace std;

jps::Floodfill::Floodfill() {
}

auto jps::Floodfill::getGrid() {
    return m_flood_grid;
}

auto jps::Floodfill::changeInteger(Grid2D<int> p_grid, int p_old_number, int p_new_number, int p_x, int p_y) {

    changeInteger(p_grid, p_old_number, p_new_number, p_x, p_y-1);
    changeInteger(p_grid, p_old_number, p_new_number, p_x+1, p_y);
    changeInteger(p_grid, p_old_number, p_new_number, p_x, p_y+1);
    changeInteger(p_grid, p_old_number, p_new_number, p_x-1, p_y);
}


auto jps::Floodfill::computeGrid(jps::Simulation const & p_simulation){
    /// We have a start grid which we need to fill with values of the environment (per level)
    Grid2D<int> m_grid = getGrid();
    World w = p_simulation.getWorld();

    //go through all levels
    for (LevelStorage ls: w.getLevelStorages()){
      /**  SpecialArea are spawn areas
        for(SpecialArea specialArea: ls.getSpecialAreas()){
            vector<Coordinate> &area = specialArea.getArea().getPolygon();
        }
        **/

      //go through all walls
        for(LineSegment lineSegment: ls.getLineSegments()){
            //starting point
            Coordinate m_start = lineSegment.getStart();
            // ending point
            Coordinate m_end = lineSegment.getEnd();


            /// When the 2D grid is filled, changeInteger() is called.
            /// There is still a question how to fill the 2D grid and how to do it when you have only walls.
            /// One idea is to set all values in the grid to "0" and set a "1" everywhere where a wall is.
            /// From then on you would only need a starting point and you could apply a floodfill with changeInteger().

        }

    }

    /// The floodfill algorithm was applied to the grid filled with the environment.
    /// Since we have multiple layers, we need to return multiple 2D grids later.
    return m_grid;
}