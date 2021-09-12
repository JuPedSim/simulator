#include "tactical/shortest_path_tactical.hpp"
#include <iostream>
#include <fstream>
#include <simulation.hpp>
#include <strategic/result.hpp>


auto ShortestPathTactical::floodfill(jps::Simulation &p_simulation, jps::StrategicModelResult & p_strategic_result, jps::Agent & p_agent) {
    //logic

    return 0;
}

void ShortestPathTactical::printArray(char c[10][25]) {
    /** content is not to be observed **/
    for (int a = 0; a < 10; a++) {
        for (int b = 0; b < 25; b++) {
            std::cout << c[a][b];
        }
        std::cout << "\n";
    }
}

void ShortestPathTactical::changeColor(char c[10][25], char oldChar, char newChar, int x, int y) {
    /** content is not to be observed **/
    if (x < 0 || x>24 || y < 0 || y>9) {
        return;
    }
    if (c[y][x] != oldChar) {
        return;
    }

    c[y][x] = newChar;

    changeColor(c, oldChar, newChar, x, y - 1);
    changeColor(c, oldChar, newChar, x + 1, y);
    changeColor(c, oldChar, newChar, x, y + 1);
    changeColor(c, oldChar, newChar, x - 1, y);
}

int main() {
    std::cout << "start" << std::endl;
}