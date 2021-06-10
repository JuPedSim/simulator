import pytest
from jpscore.geometry import (
    Area,
    Coordinate,
    LengthUnit,
    Level,
    SpecialArea,
    Units,
)


class TestSpecialArea:
    @pytest.mark.parametrize(
        "area",
        [
            Area(
                [
                    Coordinate(
                        LengthUnit(0.1, Units.m),
                        LengthUnit(0.65, Units.m),
                        Level(3),
                    ),
                    Coordinate(
                        LengthUnit(0.45, Units.m),
                        LengthUnit(61.1, Units.m),
                        Level(3),
                    ),
                    Coordinate(
                        LengthUnit(1.3, Units.m),
                        LengthUnit(-12.1, Units.m),
                        Level(3),
                    ),
                    Coordinate(
                        LengthUnit(5.1, Units.m),
                        LengthUnit(-41.0, Units.m),
                        Level(3),
                    ),
                    Coordinate(
                        LengthUnit(45.1, Units.m),
                        LengthUnit(-45.11, Units.m),
                        Level(3),
                    ),
                    Coordinate(
                        LengthUnit(7.11, Units.m),
                        LengthUnit(45.1, Units.m),
                        Level(3),
                    ),
                ]
            ),
            Area(
                [
                    Coordinate(
                        LengthUnit(45.54, Units.m),
                        LengthUnit(45.1, Units.m),
                        Level(-3),
                    ),
                    Coordinate(
                        LengthUnit(1.41, Units.m),
                        LengthUnit(34.1, Units.m),
                        Level(-3),
                    ),
                    Coordinate(
                        LengthUnit(-1.6, Units.m),
                        LengthUnit(12.1, Units.m),
                        Level(-3),
                    ),
                    Coordinate(
                        LengthUnit(-6.1, Units.m),
                        LengthUnit(-6.1, Units.m),
                        Level(-3),
                    ),
                    Coordinate(
                        LengthUnit(-1.5, Units.m),
                        LengthUnit(34.1, Units.m),
                        Level(-3),
                    ),
                    Coordinate(
                        LengthUnit(30.11, Units.m),
                        LengthUnit(15.1, Units.m),
                        Level(-3),
                    ),
                    Coordinate(
                        LengthUnit(45.54, Units.m),
                        LengthUnit(45.1, Units.m),
                        Level(-3),
                    ),
                ]
            ),
        ],
    )
    def test_constructor(self, area):
        special_area = SpecialArea(area)
        assert special_area.area == area

    @pytest.mark.parametrize(
        "special_area, new_id, new_area",
        [
            (
                SpecialArea(
                    Area(
                        [
                            Coordinate(
                                LengthUnit(45.54, Units.m),
                                LengthUnit(45.1, Units.m),
                                Level(-3),
                            ),
                            Coordinate(
                                LengthUnit(1.41, Units.m),
                                LengthUnit(34.1, Units.m),
                                Level(-3),
                            ),
                            Coordinate(
                                LengthUnit(-1.6, Units.m),
                                LengthUnit(12.1, Units.m),
                                Level(-3),
                            ),
                        ]
                    ),
                ),
                1,
                Area(
                    [
                        Coordinate(
                            LengthUnit(45.54, Units.m),
                            LengthUnit(45.1, Units.m),
                            Level(-3),
                        ),
                        Coordinate(
                            LengthUnit(1.41, Units.m),
                            LengthUnit(34.1, Units.m),
                            Level(-3),
                        ),
                        Coordinate(
                            LengthUnit(-1.6, Units.m),
                            LengthUnit(12.1, Units.m),
                            Level(-3),
                        ),
                    ],
                ),
            ),
        ],
    )
    def test_read_only(self, special_area, new_id, new_area):
        with pytest.raises(AttributeError):
            special_area.id = new_id
        with pytest.raises(AttributeError):
            special_area.area = new_area
