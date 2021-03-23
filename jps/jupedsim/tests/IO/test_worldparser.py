import ezdxf
import pytest
from jpscore import JPSGeometryException, geometry
from jupedsim.IO.worldparser import WorldParser


class TestWorldParser:
    @pytest.mark.parametrize(
        "insunit, result",
        [
            (4, geometry.Units.mm),
            (5, geometry.Units.cm),
            (6, geometry.Units.m),
            (7, geometry.Units.km),
            (13, geometry.Units.um),
            (14, geometry.Units.dm),
        ],
    )
    def test_length_unit_correct(self, insunit, result):
        doc = ezdxf.new()
        doc.header["$INSUNITS"] = insunit
        unit = WorldParser.readLengthUnitType(doc)
        assert unit == result

    @pytest.mark.parametrize(
        "insunit",
        [-1, 0, 1, 2, 3, 8, 9, 10, 11, 12, 15, 16, 17, 18, 19, 20, 21],
    )
    def test_length_unit_incorrect(self, insunit):
        doc = ezdxf.new()
        doc.header["$INSUNITS"] = insunit

        with pytest.raises(JPSGeometryException):
            WorldParser.readLengthUnitType(doc)

    @pytest.mark.parametrize(
        "measurement, result", [(-1, False), (0, False), (1, True), (2, False)]
    )
    def test_metric_unit(self, measurement, result):
        doc = ezdxf.new()
        doc.header["$MEASUREMENT"] = measurement
        assert WorldParser.checkMetricUnit(doc) == result

    @pytest.mark.parametrize(
        "dimlunit, result",
        [
            (-1, False),
            (0, False),
            (1, False),
            (2, True),
            (3, False),
            (4, False),
            (5, False),
            (6, False),
        ],
    )
    def test_decimal_unit(self, dimlunit, result):
        doc = ezdxf.new()
        doc.header["$DIMLUNIT"] = dimlunit
        assert WorldParser.checkDecimalUnit(doc) == result
