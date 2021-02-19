import re

import ezdxf
import jpscore


class WorldParser:
    """
    Class for parsing dxf files of the world and creating corresponding geometry objects.
    """

    def __init__(self, p_input_file):
        """
        Initialization with a dxf file. In case of valid file format Lines and SpecialAreas are parsed.
        :param p_input_file: name of the dxf file
        """
        self.m_input_file = p_input_file

        # open file and create modelspace

        print(p_input_file)
        try:
            doc = ezdxf.readfile(self.m_input_file)
        except IOError:
            # TODO throw exception. file not found
            print("File not found")
            return
        except ezdxf.DXFStructureError:
            # TODO throw exception. invalid dxf file.
            print("Invalid dxf file format")
            return

        self.m_msp = doc.modelspace()

        self.m_unit = doc.header[
            "$INSUNITS"
        ]  # allow only 6 for meters chec diff to LUNITS
        if self.m_unit != 6:
            # TODO accept other units as well (but not all)
            # TODO throw exception
            print("Length unit is not meter. Not yet implemented")

        # TODO check $MEASUREMENT = 0 English not metric
        # NOTE: these headers are not available in qcad file
        # upper_right_corner = doc.header['$EXTMAX']
        # lower_left_corner = doc.header['$EXTMIN']

        # build World
        self.m_jps_world_builder = jpscore.geometry.WorldBuilder()
        self.__parseLevels()

    @staticmethod
    def parseCoordinates(line):
        """
        Method parses a dxf line with coordinates to a list
        :param line: start and end coordinate of a dxf line formatted as string '(start_x, start_y, start_z) (end_x, end_x, end_z)'
        :return: coordinates as a list [start_x, start_y, end_x, end_y]
        """
        start_coords = re.split(",", str(line.dxf.start))
        start_x = float(start_coords[0][1:])
        start_y = float(start_coords[1])
        end_coords = re.split(",", str(line.dxf.end))
        end_x = float(end_coords[0][1:])
        end_y = float(end_coords[1])

        return [start_x, start_y, end_x, end_y]

    def __parseLevels(self):
        """
        Method initiates parsing of Lines and Areas for each level provided in the dxf file
        :return:
        """

        # TODO: loop over several levels, error handling
        self.__parseLineSegment("Level0")
        self.__parseSpecialAreas("Level0_SpecialAreas")
        # TODO: parse polylines

    def __parseLineSegment(self, p_layer):
        """
        Method parses dxf entities of type LINE that represent a LineSegment at the given layer. Corresponding LineSegments are added to the World.
        :param p_layer: name of the layer (string)
        :return:
        """
        for line in self.m_msp.query('LINE[layer=="' + p_layer + '"]'):
            coords = WorldParser.parseCoordinates(line)
            self.m_jps_world_builder.addLineSegment(
                jpscore.geometry.Level(),
                jpscore.geometry.LineSegment(
                    jpscore.geometry.Coordinate(
                        jpscore.geometry.LengthUnit(coords[0]),
                        jpscore.geometry.LengthUnit(coords[1]),
                        jpscore.geometry.Level(),
                    ),
                    jpscore.geometry.Coordinate(
                        jpscore.geometry.LengthUnit(coords[2]),
                        jpscore.geometry.LengthUnit(coords[3]),
                        jpscore.geometry.Level(),
                    ),
                ),
            )

    def __parseSpecialAreas(self, p_layer):
        """
        Method parses dxf entities of type LINE that represent Special Areas at the given layer. Corresponding group of LineSegments are added to the World.
        :param p_layer: name of the layer (string)
        :return:
        """
        color_to_segments = {}
        # loop over lines, store: key=color, value=segment list [LineSegment1, LineSegment2, ...]
        for line in self.m_msp.query('LINE[layer=="' + p_layer + '"]'):
            # create empty list for new color
            if line.dxf.color not in color_to_segments.keys():
                color_to_segments[line.dxf.color] = []

            # append segment to list
            coords = WorldParser.parseCoordinates(line)
            color_to_segments[line.dxf.color].append(
                jpscore.geometry.LineSegment(
                    jpscore.geometry.Coordinate(
                        jpscore.geometry.LengthUnit(coords[0]),
                        jpscore.geometry.LengthUnit(coords[1]),
                        jpscore.geometry.Level(),
                    ),
                    jpscore.geometry.Coordinate(
                        jpscore.geometry.LengthUnit(coords[2]),
                        jpscore.geometry.LengthUnit(coords[3]),
                        jpscore.geometry.Level(),
                    ),
                )
            )

        # add to world builder
        for color in color_to_segments:
            print("not yet implemented")
            # TODO pybind for area-constructor with LineSegments
            # self._jps_world_builder.addSpecialArea(jpscore.geometry.Level(), jpscore.geometry.SpecialArea(jpscore.geometry.Area(color_to_segments[color]),int(color)))
