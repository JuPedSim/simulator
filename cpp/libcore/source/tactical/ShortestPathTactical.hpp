#pragma once

#include "agent/agent.hpp"
#include "strategic/result.hpp"
#include "tactical/result.hpp"
#include "tactical/tactical.hpp"


class ShortestPathTactical{

private:


public:
    auto floodfill(jps::Simulation&, jps::StrategicModelResult&, jps::Agent&);
    /** nur ein Test **/
    void printArray(char [10][25]);
    void changeColor(char [10][25], char, char, int, int);
    void changeColor2(char c[10][25], char oldChar, char newChar, int x, int y);
};



