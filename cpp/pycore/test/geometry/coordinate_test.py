import pytest
from jpscore.geometry import Coordinate, LengthUnit, Units


class TestCoordinate:
    @pytest.mark.parametrize(
        "x, y",
        [
            (LengthUnit(-12.0, Units.m), LengthUnit(435.1, Units.m)),
            (LengthUnit(0.1, Units.m), LengthUnit(0, Units.m)),
            (
                LengthUnit(95213, Units.m),
                LengthUnit(-123.435, Units.m),
            ),
            (
                LengthUnit(94.45, Units.m),
                LengthUnit(90941, Units.m),
            ),
            (
                LengthUnit(-510.1, Units.m),
                LengthUnit(32432.11, Units.m),
            ),
            (LengthUnit(-324, Units.m), LengthUnit(-435.1, Units.m)),
        ],
    )
    def test_constructor(self, x, y):
        coordinate = Coordinate(x, y)
        assert coordinate.x == x
        assert coordinate.y == y

    @pytest.mark.parametrize(
        "coordinate, new_x, new_y",
        [
            (
                Coordinate(
                    LengthUnit(-10.12, Units.m),
                    LengthUnit(34.12, Units.m),
                ),
                LengthUnit(-12.45, Units.m),
                LengthUnit(657, Units.m),
            ),
            (
                Coordinate(
                    LengthUnit(56.42, Units.m),
                    LengthUnit(-1.435, Units.m),
                ),
                LengthUnit(12.4, Units.m),
                LengthUnit(34.1, Units.m),
            ),
            (
                Coordinate(
                    LengthUnit(0.11, Units.m),
                    LengthUnit(-1.11111, Units.m),
                ),
                LengthUnit(0, Units.m),
                LengthUnit(0.00, Units.m),
            ),
            (
                Coordinate(
                    LengthUnit(55.1, Units.m),
                    LengthUnit(5, Units.m),
                ),
                LengthUnit(-1.1234, Units.m),
                LengthUnit(12, Units.m),
            ),
        ],
    )
    def test_setters(self, coordinate, new_x, new_y):
        coordinate.x = new_x
        assert coordinate.x == new_x

        coordinate.y = new_y
        assert coordinate.y == new_y

    @pytest.mark.parametrize(
        "coordinate, other, result",
        [
            (
                Coordinate(
                    LengthUnit(-10.12, Units.m),
                    LengthUnit(34.12, Units.m),
                ),
                Coordinate(
                    LengthUnit(-10.12, Units.m),
                    LengthUnit(34.12, Units.m),
                ),
                True,
            ),
            (
                Coordinate(
                    LengthUnit(-10.1254, Units.m),
                    LengthUnit(6.12, Units.m),
                ),
                Coordinate(
                    LengthUnit(-10.1254, Units.m),
                    LengthUnit(6.12, Units.m),
                ),
                True,
            ),
            (
                Coordinate(
                    LengthUnit(3.56, Units.m),
                    LengthUnit(-12.67, Units.m),
                ),
                Coordinate(
                    LengthUnit(3.56, Units.m),
                    LengthUnit(-12.67, Units.m),
                ),
                True,
            ),
            (
                Coordinate(
                    LengthUnit(-78.34, Units.m),
                    LengthUnit(65.712, Units.m),
                ),
                Coordinate(
                    LengthUnit(-78.34, Units.m),
                    LengthUnit(65.712, Units.m),
                ),
                True,
            ),
            (
                Coordinate(
                    LengthUnit(0.0000001, Units.m),
                    LengthUnit(851.1, Units.m),
                ),
                Coordinate(
                    LengthUnit(0.0000001, Units.m),
                    LengthUnit(851.1, Units.m),
                ),
                True,
            ),
            (
                Coordinate(
                    LengthUnit(3.56, Units.m),
                    LengthUnit(-12.67, Units.m),
                ),
                Coordinate(
                    LengthUnit(0.0000001, Units.m),
                    LengthUnit(851.1, Units.m),
                ),
                False,
            ),
            (
                Coordinate(
                    LengthUnit(3.56, Units.m),
                    LengthUnit(-12.67, Units.m),
                ),
                Coordinate(
                    LengthUnit(-78.34, Units.m),
                    LengthUnit(65.712, Units.m),
                ),
                False,
            ),
            (
                Coordinate(
                    LengthUnit(-78.34, Units.m),
                    LengthUnit(65.712, Units.m),
                ),
                Coordinate(
                    LengthUnit(-10.12, Units.m),
                    LengthUnit(34.12, Units.m),
                ),
                False,
            ),
            (
                Coordinate(
                    LengthUnit(0.0000001, Units.m),
                    LengthUnit(851.1, Units.m),
                ),
                Coordinate(
                    LengthUnit(-10.1254, Units.m),
                    LengthUnit(6.12, Units.m),
                ),
                False,
            ),
            (
                Coordinate(
                    LengthUnit(-10.1254, Units.m),
                    LengthUnit(6.12, Units.m),
                ),
                Coordinate(
                    LengthUnit(3.56, Units.m),
                    LengthUnit(-12.67, Units.m),
                ),
                False,
            ),
        ],
    )
    def test_comparison_operators(self, coordinate, other, result):
        assert (coordinate == other) == result
        assert (coordinate != other) != result
