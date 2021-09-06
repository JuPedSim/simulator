#include "tactical/shorthestpathtactical.hpp"
#include "ShortestPathTactical.hpp"
#include <iostream>
#include <fstream>
#include <simulation.hpp>
#include <strategic/result.hpp>


auto ShortestPathTactical::floodfill(jps::Simulation &p_simulation, jps::StrategicModelResult & p_strategic_result, jps::Agent & p_agent) {

    //Logik

    return 0;

}

void ShortestPathTactical::printArray(char c[10][25]) {
    /** Inhalt ist nicht zu beachten **/
    for (int a = 0; a < 10; a++) {
        for (int b = 0; b < 25; b++) {
            std::cout << c[a][b];
        }
        std::cout << "\n";
    }
}

void ShortestPathTactical::changeColor(char c[10][25], char oldChar, char newChar, int x, int y) {
    /** Inhalt ist nicht zu beachten **/
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
    std::cout << "Start" << std::endl;
}