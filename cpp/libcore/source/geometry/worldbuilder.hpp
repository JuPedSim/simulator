#ifndef SIMULATOR_WORLDBUILDER_HPP
#define SIMULATOR_WORLDBUILDER_HPP

#include <vector>
#include <map>

// 2D positions in mm
struct Point{
    int x;
    int y;
};

struct Line{
    Point start;
    Point end;
};

struct Area{
    int id;
    std::vector<Line> lines;
    //TODO: special properties
};

class WorldBuilder
{
private:
    std::map<int, std::vector<Line>> m_level_to_boundary_lines;
    std::map<int, std::vector<Area>> m_level_to_special_areas;

public:
    //TODO: somehow check for maximum dimensions and shift if necessary (to not exceed the int range)
    void addBoundaryLine(int p_level, std::vector<int> p_segment);
    void addSpecialArea(int p_level, int p_id, std::vector<int> p_segments);
};

#endif //SIMULATOR_WORLDBUILDER_HPP
