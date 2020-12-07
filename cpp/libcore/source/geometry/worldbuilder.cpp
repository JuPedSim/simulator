#include "worldbuilder.hpp"

#include <utility>

auto WorldBuilder::addBoundaryLine(int p_level, std::vector<int> p_segment) -> void
{
    // must contain 4 values
    if(p_segment.size() != 4) {
        // TODO throw exception. Line must be defined by two points/four values
    }
    // convert
    Point start = {.x = p_segment[0], .y = p_segment[1]};
    Point end   = {.x = p_segment[2], .y = p_segment[3]};
    Line line   = {.start = start, .end = end};

    if(m_level_to_boundary_lines.find(p_level) != m_level_to_boundary_lines.end()) {
        // push back if not empty
        m_level_to_boundary_lines[p_level].push_back(line);
    } else {
        // create new vector
        m_level_to_boundary_lines[p_level] = std::vector<Line>{line};
    }
}

auto WorldBuilder::addSpecialArea(int p_level, int p_id, std::vector<int> p_segment_values) -> void
{
    if(std::find(
           m_level_to_special_areas.begin(),
           m_level_to_special_areas.end(),
           [p_id](const auto & it) -> bool { return it.second.id == p_id; }) !=
       m_level_to_special_areas.end()) {
        //TODO: throw exception. an area with this ID already exists.
    }

    if(p_segment_values.size() != 0 && p_segment_values.size() % 4 != 0) {
        //TODO: throw exception. vector of segments must contain 4 points for each segment
    }
    // convert p_segments to vector of lines
    std::vector<Line> segment_lines(p_segment_values.size() / 4);

    // loop over segments (pair of points), 4 values each
    for(size_t i = 0; i < (p_segment_values.size() - 1); i += 4) {
        Point first_point{.x = p_segment_values[i], .y = p_segment_values[i + 1]};
        Point second_point{.x = p_segment_values[i+2], .y = p_segment_values[i + 3]};
        segment_lines.push_back(Line {.start=first_point, .end=second_point});
    }

    // check if special area is a closed polygon. each start/end point of a line must be part of another line
    // Approach: loop over segments, search for point of this segment in the other remaining segments
    // if found: repeat loop with other point of found segment

    std::vector<Line> lines_to_check(segment_lines.begin()+1,segment_lines.end());
    bool found_connection;
    Point current_point=segment_lines[0].end;
    int remove_index;
    std::vector<Line> connected_lines(p_segment_values.size() / 4);

    do {
        bool found_connection=false;

        for(auto it=lines_to_check.begin(); it!=lines_to_check.end(); ++it) {
            if(it->start.x == current_point.x && it->start.y == current_point.y) {
                // found connection in start point of another segment
                found_connection = true;
                connected_lines.push_back(*it);
                // search in next loop for connection of the end point of the current segment
                current_point = it->end;
                // store index to remove current segment
                remove_index = std::distance(lines_to_check.begin(), it);
                break;
            } else if(
                it->end.x == current_point.x && it->end.y == current_point.y) {
                // found connection in end point of another segment
                found_connection = true;
                connected_lines.push_back(*it);
                // search in next loop for connection of the start point of the current segment
                current_point = it->start;
                // store index to remove current segment
                remove_index = std::distance(lines_to_check.begin(), it);
                break;
            }
        }

        if(found_connection){
            // remove current segment from points to check
            lines_to_check.erase(lines_to_check.begin(), lines_to_check.cbegin()+remove_index);
        }

    } while (found_connection);

    // check if all lines have been connected and last remaining point matches first point of first segment
    if(lines_to_check.empty() && current_point.x == segment_lines[0].start.x && current_point.y == segment_lines[0].start.y){
        connected_lines.push_back(segment_lines[0]);

        // create area and add to map
        Area valid_area {.id=p_id, .lines=connected_lines};

        if(m_level_to_special_areas.find(p_level) != (m_level_to_special_areas.end())) {
            // push back if not empty
            m_level_to_special_areas[p_level].push_back(valid_area);
        } else {
            // create new vector
            m_level_to_special_areas[p_level] = std::vector<Area>{valid_area};
        }

    }
}