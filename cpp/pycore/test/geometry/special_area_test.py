import pytest
from jpscore.geometry import (
    Area,
    Coordinate,
    LengthUnit,
    Level,
    LineSegment,
    SpecialArea,
)


class TestSpecialArea:
    @pytest.mark.parametrize(
        "external_id, area",
        [
            (
                12,
                Area(
                    [
                        Coordinate(
                            LengthUnit(0.1), LengthUnit(0.65), Level(3)
                        ),
                        Coordinate(
                            LengthUnit(0.45), LengthUnit(61.1), Level(3)
                        ),
                        Coordinate(
                            LengthUnit(1.3), LengthUnit(-12.1), Level(3)
                        ),
                        Coordinate(
                            LengthUnit(5.1), LengthUnit(-41.0), Level(3)
                        ),
                        Coordinate(
                            LengthUnit(45.1), LengthUnit(-45.11), Level(3)
                        ),
                        Coordinate(
                            LengthUnit(7.11), LengthUnit(45.1), Level(3)
                        ),
                    ]
                ),
            ),
            (
                5611,
                Area(
                    [
                        Coordinate(
                            LengthUnit(45.54), LengthUnit(45.1), Level(-3)
                        ),
                        Coordinate(
                            LengthUnit(1.41), LengthUnit(34.1), Level(-3)
                        ),
                        Coordinate(
                            LengthUnit(-1.6), LengthUnit(12.1), Level(-3)
                        ),
                        Coordinate(
                            LengthUnit(-6.1), LengthUnit(-6.1), Level(-3)
                        ),
                        Coordinate(
                            LengthUnit(-1.5), LengthUnit(34.1), Level(-3)
                        ),
                        Coordinate(
                            LengthUnit(30.11), LengthUnit(15.1), Level(-3)
                        ),
                        Coordinate(
                            LengthUnit(45.54), LengthUnit(45.1), Level(-3)
                        ),
                    ]
                ),
            ),
        ],
    )
    def test_constructor_from_coordinates(self, external_id, area):
        special_area = SpecialArea(external_id, area)
        assert special_area.external_id == external_id
        assert special_area.area == area
