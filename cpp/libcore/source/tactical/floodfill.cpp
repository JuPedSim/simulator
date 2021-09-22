#include "tactical/floodfill.hpp"


using namespace std;

jps::Floodfill::Floodfill() {

}

auto jps::Floodfill::computeGrid(jps::Simulation const & p_simulation, jps::Agent const & p_agent){
    Grid2D</*which typename? We don't want agents here*/> flood_grid;
    auto pos_x = p_agent.pos.x;
    auto pos_y = p_agent.pos.y;

    return flood_grid;
}