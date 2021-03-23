import re
from typing import List

import ezdxf
from jpscore import geometry
from jpscore import JPSGeometryException
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

        # parse header variables
        self.__parseHeader(doc)

        # build World
        log_info("Building world ...")
        self.m_jps_world_builder = geometry.WorldBuilder()
        self.__parseLevels()

    @staticmethod
    def checkMetricUnit(doc: ezdxf.document.Drawing) -> bool:
        """
        Check if drawing unit is metric
        :param doc: document drawing of dxf file
        :return: True if metric is chosen, false otherwise
        """

        return doc.header["$MEASUREMENT"] == 1

    @staticmethod
    def checkDecimalUnit(doc: ezdxf.document.Drawing) -> bool:
        """
        Checks if format of linear dimensions is decimal
        For metric system decimal (14.4), fractional (14 2/5) and scientific format (1.4E+01) can be chosen, only decimal is supported
        :param doc: document drawing of dxf file
        :return: True if linear dimension format is decimal
        """

        return doc.header["$DIMLUNIT"] == 2

    @staticmethod
    def readLengthUnitType(doc: ezdxf.document.Drawing) -> geometry.Units:
        """
        Parsing units according to [INSUNITS documentation](https://knowledge.autodesk.com/de/support/autocad/learn-explore/caas/CloudHelp/cloudhelp/2018/DEU/AutoCAD-Core/files/GUID-A58A87BB-482B-4042-A00A-EEF55A2B4FD8-htm.html)
        :param doc: document drawing of dxf file
        :return: corresponding geometry.Units object
        :raises JPSGeometryException: if length unit set in dxf file is not um, mm, cm, dm, m or km
        """

        dxf_unit = doc.header["$INSUNITS"]
        if dxf_unit == 4:
            return geometry.Units.mm
        elif dxf_unit == 5:
            return geometry.Units.cm
        elif dxf_unit == 6:
            return geometry.Units.m
        elif dxf_unit == 7:
            return geometry.Units.km
        elif dxf_unit == 13:
            return geometry.Units.um
        elif dxf_unit == 14:
            return geometry.Units.dm

        raise JPSGeometryException("Defined length unit is not supported. Supported length units: um, mm, cm, dm, m, km")

    def __parseHeader(self, doc: ezdxf.document.Drawing) -> None:
        """
        Reads in meta data defined in header of the dxf file.
        Header variables can be found on [autodesk header variables](http://help.autodesk.com/view/OARX/2018/ENU/?guid=GUID-A85E8E67-27CD-4C59-BE61-4DC9FADBE74A)
        NOTE: these headers are not available in qcad file:
        upper_right_corner = doc.header['$EXTMAX']
        lower_left_corner = doc.header['$EXTMIN']

        :param doc: document drawing of dxf file
        :raises JPSGeometryException: if chosen header variables are not supported
        """

        if not WorldParser.checkMetricUnit(
            doc
        ) or not WorldParser.checkDecimalUnit(doc):
            raise JPSGeometryException("Only metric units in decimal format are supported.")

        self.m_unit = WorldParser.readLengthUnitType(doc)

    def __parseCoordinates(
        self, line: str, p_level: geometry.Level
    ) -> List[geometry.Coordinate]:
        """
        Method parses a dxf line with coordinates to a list
        :param line: start and end coordinate of a dxf line formatted as string '(start_x, start_y, start_z) (end_x, end_x, end_z)'
        :return: coordinates as a list [start Coordinate, end Coordinate]
        """
        start_coord_tmp = re.split(",", str(line.dxf.start))
        start_coord = geometry.Coordinate(
            geometry.LengthUnit(float(start_coord_tmp[0][1:]), self.m_unit),
            geometry.LengthUnit(float(start_coord_tmp[1]), self.m_unit),
            p_level,
        )
        end_coord_tmp = re.split(",", str(line.dxf.end))
        end_coord = geometry.Coordinate(
            geometry.LengthUnit(float(end_coord_tmp[0][1:]), self.m_unit),
            geometry.LengthUnit(float(end_coord_tmp[1]), self.m_unit),
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
