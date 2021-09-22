#include "tactical/floodfill.hpp"


using namespace std;

jps::Floodfill::Floodfill() {

}

auto jps::Floodfill::computeGrid(jps::Simulation const & p_simulation, jps::Agent const & p_agent){

    World w = p_simulation.getWorld();


    for (LevelStorage ls: w.getLevelStorages()){
        for(SpecialArea specialArea: ls.getSpecialAreas()){
            vector<Coordinate> &area = specialArea.getArea().getPolygon();



        }

    }


    return m_flood_grid;
}