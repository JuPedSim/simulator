#pragma once

#include "agent/agent.hpp"
#include "strategic/result.hpp"
#include "tactical/result.hpp"
#include "tactical/tactical.hpp"
#include <string>


class ShortestPathTactical{

private:


public:
    auto floodfill(jps::Simulation&, jps::StrategicModelResult&, jps::Agent&);
    /** just a test **/
    void printArray(std::string []);
    void changeColor(std::string []), std::string, std::string, int, int);
};