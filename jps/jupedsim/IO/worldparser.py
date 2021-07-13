import re
from pathlib import Path
from typing import List

import ezdxf
from jpscore import JPSGeometryException, geometry
from jupedsim.util.loghelper import log_debug, log_error, log_info, log_warning


class WorldParser:
    """
    Class for parsing dxf files of the world and creating corresponding geometry objects.
    """

    def __init__(self, p_input_file: Path):
        """
        Initialization with a dxf file name.
        :param p_input_file: name of the dxf file
        """
        self.m_input_file = p_input_file

    def parse(self, world: geometry.World) -> None:
        """
        Parsing header information and entities on different levels. In case of valid file format Lines and SpecialAreas are parsed.
        :raises IOError, ezdxf.DXFStructureError: if file not found or if invalid dxf format
        """

        # try to open file
        try:
            doc = ezdxf.readfile(str(self.m_input_file))
        except IOError:
            raise JPSGeometryException(f"{str(self.m_input_file)} not found")
        except ezdxf.DXFStructureError:
            raise JPSGeometryException("Invalid dxf file format")

        # create modelspace
        self.m_msp = doc.modelspace()

        # parse header variables
        WorldParser.checkHeader(doc)
        unit = WorldParser.readLengthUnitType(doc)

        # build World
        log_info("Building world ...")

        # TODO check if the other parsing functions can be static
        self.__parseLevels(world, unit)

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

        raise JPSGeometryException(
            "Defined length unit is not supported. Supported length units: um, mm, cm, dm, m, km"
        )

    @staticmethod
    def checkHeader(doc: ezdxf.document.Drawing) -> None:
        """
        Reads in meta data defined in header of the dxf file.
        Header variables can be found on [autodesk header variables](http://help.autodesk.com/view/OARX/2018/ENU/?guid=GUID-A85E8E67-27CD-4C59-BE61-4DC9FADBE74A)
        NOTE: these headers are not available in qcad file:
        upper_right_corner = doc.header['$EXTMAX']
        lower_left_corner = doc.header['$EXTMIN']

        :param doc: document drawing of dxf file
        :raises JPSGeometryException: if chosen header variables are not supported
        """

        if not WorldParser.checkMetricUnit(doc):
            raise JPSGeometryException("Only metric units are supported.")

        # Note: changing the decimal unit did not have any effect on the units when working wih QCAD or LibreCAD. This might be only important for labels or the representation in the editor.
        if not WorldParser.checkDecimalUnit(doc):
            raise JPSGeometryException("Only decimal format is supported.")

    @staticmethod
    def parseCoordinates(
        line: str, unit: geometry.Units
    ) -> List[geometry.Coordinate]:
        """
        Method parses a dxf line with coordinates to a list
        :param line: start and end coordinate of a dxf line formatted as string '(start_x, start_y, start_z) (end_x, end_x, end_z)'
        :return: coordinates as a list [start Coordinate, end Coordinate]
        """
        start_coord_tmp = re.split(",", str(line.dxf.start))
        start_coord = geometry.Coordinate(
            geometry.LengthUnit(float(start_coord_tmp[0][1:]), unit),
            geometry.LengthUnit(float(start_coord_tmp[1]), unit),
        )
        end_coord_tmp = re.split(",", str(line.dxf.end))
        end_coord = geometry.Coordinate(
            geometry.LengthUnit(float(end_coord_tmp[0][1:]), unit),
            geometry.LengthUnit(float(end_coord_tmp[1]), unit),
        )

        return [start_coord, end_coord]

    def __parseLevels(
        self, world: geometry.World, unit: geometry.Units
    ) -> None:
        """
        Method initiates parsing of Lines and Areas for each level provided in the dxf file
        :return:
        """

        # TODO: loop over several layer, error handling
        # TODO: extract Level from layer name
        level_id = geometry.Level(0)
        cur_level = world.add_level(level_id)
        log_debug(f"Parsing {level_id}.")
        self.__parseLineSegment("Level0", cur_level, unit)
        self.__parseSpecialAreas("Level0_SpecialAreas", cur_level, unit)
        # TODO: parse polylines

    def __parseLineSegment(
        self,
        p_layer_name: str,
        p_level: geometry.LevelStorage,
        unit: geometry.Units,
    ) -> None:
        """
        Method parses dxf entities of type LINE that represent a LineSegment at the given layer. Corresponding LineSegments are added to the World.
        :param p_layer_name: name of the layer (string)
        :param p_level: Level object for the given layer
        :return:
        """
        for line in self.m_msp.query('LINE[layer=="' + p_layer_name + '"]'):
            coords = WorldParser.parseCoordinates(line, unit)
            line_segment = geometry.LineSegment(
                coords[0],
                coords[1],
            )
            log_debug(f"Adding {line_segment} to the World.")
            p_level.addLineSegment(line_segment)

    def __parseSpecialAreas(
        self,
        p_layer: str,
        p_level: geometry.LevelStorage,
        unit: geometry.Units,
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
            coords = WorldParser.parseCoordinates(line, unit)
            color_to_segments[line.dxf.color].append(
                geometry.LineSegment(
                    coords[0],
                    coords[1],
                )
            )

        # add to world builder
        for color in color_to_segments:
            log_warning("Adding SpecialAreas is not yet implemented")
            # TODO pybind for area-constructor with LineSegments
            # self._jps_world.addSpecialArea(p_level, geometry.SpecialArea(geometry.Area(color_to_segments[color]),int(color)))
