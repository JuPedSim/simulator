import re
from typing import List

import ezdxf
from jpscore import geometry
from jupedsim.util.loghelper import log_debug, log_error, log_info, log_warning


class WorldParser:
    """
    Class for parsing dxf files of the world and creating corresponding geometry objects.
    """

    def __init__(self, p_input_file: str):
        """
        Initialization with a dxf file. In case of valid file format Lines and SpecialAreas are parsed.
        :param p_input_file: name of the dxf file
        """
        self.m_input_file = p_input_file

        # try to open file
        try:
            doc = ezdxf.readfile(self.m_input_file)
        except IOError:
            # TODO throw exception. file not found
            log_error("File not found")
            return
        except ezdxf.DXFStructureError:
            # TODO throw exception. invalid dxf file.
            log_error("Invalid dxf file format")
            return

        # create modelspace
        self.m_msp = doc.modelspace()

        # read in meta data
        self.m_unit = doc.header["$INSUNITS"]
        # allow only 6 for meters, TODO: check diff to LUNITS
        if self.m_unit != 6:
            # TODO accept other units as well (but not all)
            # TODO throw exception
            log_error("Length unit is not meter. Not yet implemented")

        # TODO check $MEASUREMENT = 0 English not metric
        # NOTE: these headers are not available in qcad file
        # upper_right_corner = doc.header['$EXTMAX']
        # lower_left_corner = doc.header['$EXTMIN']

        # build World
        log_info("Building world ...")
        self.m_jps_world_builder = geometry.WorldBuilder()
        self.__parseLevels()

    @staticmethod
    def parseCoordinates(
        line: str, p_level: geometry.Level
    ) -> List[geometry.Coordinate]:
        """
        Method parses a dxf line with coordinates to a list
        :param line: start and end coordinate of a dxf line formatted as string '(start_x, start_y, start_z) (end_x, end_x, end_z)'
        :return: coordinates as a list [start Coordinate, end Coordinate]
        """
        start_coord_tmp = re.split(",", str(line.dxf.start))
        start_coord = geometry.Coordinate(
            geometry.LengthUnit(float(start_coord_tmp[0][1:])),
            geometry.LengthUnit(float(start_coord_tmp[1])),
            p_level,
        )
        end_coord_tmp = re.split(",", str(line.dxf.end))
        end_coord = geometry.Coordinate(
            geometry.LengthUnit(float(end_coord_tmp[0][1:])),
            geometry.LengthUnit(float(end_coord_tmp[1])),
            p_level,
        )

        return [start_coord, end_coord]

    def __parseLevels(self) -> None:
        """
        Method initiates parsing of Lines and Areas for each level provided in the dxf file
        :return:
        """

        # TODO: loop over several layer, error handling
        # TODO: extract Level from layer name
        current_level = geometry.Level()
        self.__parseLineSegment("Level0", current_level)
        self.__parseSpecialAreas("Level0_SpecialAreas", current_level)
        # TODO: parse polylines

    def __parseLineSegment(
        self, p_layer_name: str, p_level: geometry.Level
    ) -> None:
        """
        Method parses dxf entities of type LINE that represent a LineSegment at the given layer. Corresponding LineSegments are added to the World.
        :param p_layer_name: name of the layer (string)
        :param p_level: Level object for the given layer
        :return:
        """
        for line in self.m_msp.query('LINE[layer=="' + p_layer_name + '"]'):
            coords = WorldParser.parseCoordinates(line, p_level)
            self.m_jps_world_builder.addLineSegment(
                p_level,
                geometry.LineSegment(
                    coords[0],
                    coords[1],
                ),
            )

    def __parseSpecialAreas(
        self, p_layer: str, p_level: geometry.Level
    ) -> None:
        """
        Method parses dxf entities of type LINE that represent Special Areas at the given layer. Corresponding group of LineSegments are added to the World.
        :param p_layer: name of the layer (string)
        :param p_level: Level object for the given layer
        :return:
        """
        color_to_segments = {}
        # loop over lines, store: key=color, value=segment list [LineSegment1, LineSegment2, ...]
        for line in self.m_msp.query('LINE[layer=="' + p_layer + '"]'):
            # create empty list for new color
            if line.dxf.color not in color_to_segments.keys():
                color_to_segments[line.dxf.color] = []

            # append segment to list
            coords = WorldParser.parseCoordinates(line, p_level)
            color_to_segments[line.dxf.color].append(
                geometry.LineSegment(
                    coords[0],
                    coords[1],
                )
            )

        # add to world builder
        for color in color_to_segments:
            log_warning("not yet implemented")
            # TODO pybind for area-constructor with LineSegments
            # self._jps_world_builder.addSpecialArea(p_level, geometry.SpecialArea(geometry.Area(color_to_segments[color]),int(color)))
