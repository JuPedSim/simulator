import pytest
from jpscore.geometry import Coordinate, LengthUnit, Level, Units


class TestCoordinate:
    @pytest.mark.parametrize(
        "x, y, lvl",
        [
            (LengthUnit(-12.0, Units.m), LengthUnit(435.1, Units.m), Level(1)),
            (LengthUnit(0.1, Units.m), LengthUnit(0, Units.m), Level(-12)),
            (
                LengthUnit(95213, Units.m),
                LengthUnit(-123.435, Units.m),
                Level(435),
            ),
            (
                LengthUnit(94.45, Units.m),
                LengthUnit(90941, Units.m),
                Level(-912),
            ),
            (
                LengthUnit(-510.1, Units.m),
                LengthUnit(32432.11, Units.m),
                Level(63),
            ),
            (LengthUnit(-324, Units.m), LengthUnit(-435.1, Units.m), Level(0)),
        ],
    )
    def test_constructor(self, x, y, lvl):
        coordinate = Coordinate(x, y, lvl)
        assert coordinate.x == x
        assert coordinate.y == y
        assert coordinate.lvl == lvl

    @pytest.mark.parametrize(
        "coordinate, new_x, new_y, new_lvl",
        [
            (
                Coordinate(
                    LengthUnit(-10.12, Units.m),
                    LengthUnit(34.12, Units.m),
                    Level(5),
                ),
                LengthUnit(-12.45, Units.m),
                LengthUnit(657, Units.m),
                Level(5),
            ),
            (
                Coordinate(
                    LengthUnit(56.42, Units.m),
                    LengthUnit(-1.435, Units.m),
                    Level(14),
                ),
                LengthUnit(12.4, Units.m),
                LengthUnit(34.1, Units.m),
                Level(546),
            ),
            (
                Coordinate(
                    LengthUnit(0.11, Units.m),
                    LengthUnit(-1.11111, Units.m),
                    Level(-1),
                ),
                LengthUnit(0, Units.m),
                LengthUnit(0.00, Units.m),
                Level(56),
            ),
            (
                Coordinate(
                    LengthUnit(55.1, Units.m),
                    LengthUnit(5, Units.m),
                    Level(-2),
                ),
                LengthUnit(-1.1234, Units.m),
                LengthUnit(12, Units.m),
                Level(12),
            ),
        ],
    )
    def test_setters(self, coordinate, new_x, new_y, new_lvl):
        coordinate.x = new_x
        assert coordinate.x == new_x

        coordinate.y = new_y
        assert coordinate.y == new_y

        coordinate.lvl = new_lvl
        assert coordinate.lvl == new_lvl

    @pytest.mark.parametrize(
        "coordinate, other, result",
        [
            (
                Coordinate(
                    LengthUnit(-10.12, Units.m),
                    LengthUnit(34.12, Units.m),
                    Level(5),
                ),
                Coordinate(
                    LengthUnit(-10.12, Units.m),
                    LengthUnit(34.12, Units.m),
                    Level(5),
                ),
                True,
            ),
            (
                Coordinate(
                    LengthUnit(-10.1254, Units.m),
                    LengthUnit(6.12, Units.m),
                    Level(-15),
                ),
                Coordinate(
                    LengthUnit(-10.1254, Units.m),
                    LengthUnit(6.12, Units.m),
                    Level(-15),
                ),
                True,
            ),
            (
                Coordinate(
                    LengthUnit(3.56, Units.m),
                    LengthUnit(-12.67, Units.m),
                    Level(1),
                ),
                Coordinate(
                    LengthUnit(3.56, Units.m),
                    LengthUnit(-12.67, Units.m),
                    Level(1),
                ),
                True,
            ),
            (
                Coordinate(
                    LengthUnit(-78.34, Units.m),
                    LengthUnit(65.712, Units.m),
                    Level(-27),
                ),
                Coordinate(
                    LengthUnit(-78.34, Units.m),
                    LengthUnit(65.712, Units.m),
                    Level(-27),
                ),
                True,
            ),
            (
                Coordinate(
                    LengthUnit(0.0000001, Units.m),
                    LengthUnit(851.1, Units.m),
                    Level(912),
                ),
                Coordinate(
                    LengthUnit(0.0000001, Units.m),
                    LengthUnit(851.1, Units.m),
                    Level(912),
                ),
                True,
            ),
            (
                Coordinate(
                    LengthUnit(3.56, Units.m),
                    LengthUnit(-12.67, Units.m),
                    Level(1),
                ),
                Coordinate(
                    LengthUnit(0.0000001, Units.m),
                    LengthUnit(851.1, Units.m),
                    Level(912),
                ),
                False,
            ),
            (
                Coordinate(
                    LengthUnit(3.56, Units.m),
                    LengthUnit(-12.67, Units.m),
                    Level(1),
                ),
                Coordinate(
                    LengthUnit(-78.34, Units.m),
                    LengthUnit(65.712, Units.m),
                    Level(-27),
                ),
                False,
            ),
            (
                Coordinate(
                    LengthUnit(-78.34, Units.m),
                    LengthUnit(65.712, Units.m),
                    Level(-27),
                ),
                Coordinate(
                    LengthUnit(-10.12, Units.m),
                    LengthUnit(34.12, Units.m),
                    Level(5),
                ),
                False,
            ),
            (
                Coordinate(
                    LengthUnit(0.0000001, Units.m),
                    LengthUnit(851.1, Units.m),
                    Level(912),
                ),
                Coordinate(
                    LengthUnit(-10.1254, Units.m),
                    LengthUnit(6.12, Units.m),
                    Level(-15),
                ),
                False,
            ),
            (
                Coordinate(
                    LengthUnit(-10.1254, Units.m),
                    LengthUnit(6.12, Units.m),
                    Level(-15),
                ),
                Coordinate(
                    LengthUnit(3.56, Units.m),
                    LengthUnit(-12.67, Units.m),
                    Level(1),
                ),
                False,
            ),
        ],
    )
    def test_comparison_operators(self, coordinate, other, result):
        assert (coordinate == other) == result
        assert (coordinate != other) != result
