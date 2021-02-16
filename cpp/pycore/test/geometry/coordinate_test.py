import pytest
from jpscore.geometry import Coordinate, LengthUnit, Level


class TestCoordinate:
    @pytest.mark.parametrize(
        "x, y, lvl",
        [
            (LengthUnit(-12.0), LengthUnit(435.1), Level(1)),
            (LengthUnit(0.1), LengthUnit(0), Level(-12)),
            (LengthUnit(95213), LengthUnit(-123.435), Level(435)),
            (LengthUnit(94.45), LengthUnit(90941), Level(-912)),
            (LengthUnit(-510.1), LengthUnit(32432.11), Level(63)),
            (LengthUnit(-324), LengthUnit(-435.1), Level(0)),
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
                Coordinate(LengthUnit(-10.12), LengthUnit(34.12), Level(5)),
                LengthUnit(-12.45),
                LengthUnit(657),
                Level(5),
            ),
            (
                Coordinate(LengthUnit(56.42), LengthUnit(-1.435), Level(14)),
                LengthUnit(12.4),
                LengthUnit(34.1),
                Level(546),
            ),
            (
                Coordinate(LengthUnit(0.11), LengthUnit(-1.11111), Level(-1)),
                LengthUnit(0),
                LengthUnit(0.00),
                Level(56),
            ),
            (
                Coordinate(LengthUnit(55.1), LengthUnit(5), Level(-2)),
                LengthUnit(-1.1234),
                LengthUnit(12),
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
        "coordinate, expected",
        [
            (
                Coordinate(LengthUnit(-10.12), LengthUnit(34.12), Level(5)),
                "COORDINATE: (-10.12 m, 34.12 m) -- LEVEL: 5",
            ),
            (
                Coordinate(LengthUnit(-10.1254), LengthUnit(6.12), Level(-15)),
                "COORDINATE: (-10.13 m, 6.120 m) -- LEVEL: -15",
            ),
            (
                Coordinate(LengthUnit(3.56), LengthUnit(-12.67), Level(1)),
                "COORDINATE: (3.560 m, -12.67 m) -- LEVEL: 1",
            ),
            (
                Coordinate(LengthUnit(-78.34), LengthUnit(65.712), Level(-27)),
                "COORDINATE: (-78.34 m, 65.71 m) -- LEVEL: -27",
            ),
            (
                Coordinate(
                    LengthUnit(0.0000001), LengthUnit(851.1), Level(912)
                ),
                "COORDINATE: (1.000e-07 m, 851.1 m) -- LEVEL: 912",
            ),
        ],
    )
    def test_to_string(self, coordinate, expected):
        assert str(coordinate) == expected
        assert repr(coordinate) == expected

    @pytest.mark.parametrize(
        "coordinate, other, result",
        [
            (
                Coordinate(LengthUnit(-10.12), LengthUnit(34.12), Level(5)),
                Coordinate(LengthUnit(-10.12), LengthUnit(34.12), Level(5)),
                True,
            ),
            (
                Coordinate(LengthUnit(-10.1254), LengthUnit(6.12), Level(-15)),
                Coordinate(LengthUnit(-10.1254), LengthUnit(6.12), Level(-15)),
                True,
            ),
            (
                Coordinate(LengthUnit(3.56), LengthUnit(-12.67), Level(1)),
                Coordinate(LengthUnit(3.56), LengthUnit(-12.67), Level(1)),
                True,
            ),
            (
                Coordinate(LengthUnit(-78.34), LengthUnit(65.712), Level(-27)),
                Coordinate(LengthUnit(-78.34), LengthUnit(65.712), Level(-27)),
                True,
            ),
            (
                Coordinate(
                    LengthUnit(0.0000001), LengthUnit(851.1), Level(912)
                ),
                Coordinate(
                    LengthUnit(0.0000001), LengthUnit(851.1), Level(912)
                ),
                True,
            ),
            (
                Coordinate(LengthUnit(3.56), LengthUnit(-12.67), Level(1)),
                Coordinate(
                    LengthUnit(0.0000001), LengthUnit(851.1), Level(912)
                ),
                False,
            ),
            (
                Coordinate(LengthUnit(3.56), LengthUnit(-12.67), Level(1)),
                Coordinate(LengthUnit(-78.34), LengthUnit(65.712), Level(-27)),
                False,
            ),
            (
                Coordinate(LengthUnit(-78.34), LengthUnit(65.712), Level(-27)),
                Coordinate(LengthUnit(-10.12), LengthUnit(34.12), Level(5)),
                False,
            ),
            (
                Coordinate(
                    LengthUnit(0.0000001), LengthUnit(851.1), Level(912)
                ),
                Coordinate(LengthUnit(-10.1254), LengthUnit(6.12), Level(-15)),
                False,
            ),
            (
                Coordinate(LengthUnit(-10.1254), LengthUnit(6.12), Level(-15)),
                Coordinate(LengthUnit(3.56), LengthUnit(-12.67), Level(1)),
                False,
            ),
        ],
    )
    def test_comparison_operators(self, coordinate, other, result):
        assert (coordinate == other) == result
        assert (coordinate != other) != result
