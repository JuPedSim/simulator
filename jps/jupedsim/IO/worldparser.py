import sys
import ezdxf

import geometry

class WorldParser:

    def __init__(self, p_input_file):
        self.m_input_file = p_input_file

        # open file and create modelspace
        try:
            doc = ezdxf.readfile(self.m_input_file)
        except IOError:
            # TODO throw exception. file not found
            print("File not found")
        except ezdxf.DXFStructureError:
            # TODO throw exception. invalid dxf file.
            print("Invalid dxf file format")

        self.m_msp = doc.modelspace()

        self.m_unit = doc.header['$INSUNITS']  # allow only 6 for meters chec diff to LUNITS
        if self.m_unit != 6:
            # TODO accept other units as well (but not all)
            # TODO throw exception
            print("Length unit is not meter. Not yet implemented")

        print("unit: " + str(self.m_unit))

        # TODO check $MEASUREMENT = 0 English not metric
        # NOTE: these headers are not available in qcad file
        # upper_right_corner = doc.header['$EXTMAX']
        # lower_left_corner = doc.header['$EXTMIN']

        geometry.WorldBuilder()

        self.__parseLevels()
        # self.__parseSpecialAreas()

    def __parseLevels(self):
        # TODO: error if no level information
        # TODO: implement for several levels

        for line in self.m_msp.query('LINE[layer=="Level0"]'):
            print(line, line.dxf.start, line.dxf.end)
            geometry.WorldBuilder.addBoundaryLine(
                geometry.LineSegment(geometry.Coordinate(line.dxf.start[0], line.dxf.start[1], 0),
                                     geometry.Coordinate(line.dxf.end[0], line.dxf.end[1], 0)));

    def __parseSpecialAreas(self):
        # TODO: implement for several special area-layers
        # loop over lines, store: key=color, value=segment list [[[startX, startY],[endX, endY]], ...]

        color_to_segments = {}

        for line in self.m_msp.query('LINE[layer=="Level0_SpecialAreas"]'):
            # create empty list for new color
            if line.dxf.color not in color_to_segments.keys():
                color_to_segments[line.dxf.color] = []

            # append segment to list
            # TODO: convert format of dxf.start/end
            color_to_segments[line.dxf.color].append([line.dxf.start, line.dxf.end])

        # add to world builder
        for color in color_to_segments:
            print("not yet implemented")
            # TODO: pybind
            # WorldBuilder.addSpecialArea(int(color), color_to_segments[color])
