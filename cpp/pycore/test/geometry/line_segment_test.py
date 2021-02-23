import copy

import pytest
from jpscore.geometry import LineSegment, Coordinate, Level, LengthUnit


class TestLineSegment:
    @pytest.mark.parametrize(
        "start, end",
        [
            (
                Coordinate(LengthUnit(0.1), LengthUnit(0.65), Level(4)),
                Coordinate(LengthUnit(0.45), LengthUnit(61.1), Level(4)),
            ),
            (
                Coordinate(LengthUnit(1.3), LengthUnit(-12.1), Level(54)),
                Coordinate(LengthUnit(5.1), LengthUnit(-41.0), Level(54)),
            ),
            (
                Coordinate(LengthUnit(45.1), LengthUnit(-45.11), Level(-1)),
                Coordinate(LengthUnit(7.11), LengthUnit(45.1), Level(-1)),
            ),
            (
                Coordinate(LengthUnit(-56.61), LengthUnit(1.34), Level(0)),
                Coordinate(LengthUnit(-4.11), LengthUnit(7.0001), Level(0)),
            ),
            (
                Coordinate(
                    LengthUnit(-41.1111), LengthUnit(-324.11), Level(-4)
                ),
                Coordinate(LengthUnit(-41.0), LengthUnit(-320.11), Level(-4)),
            ),
        ],
    )
    def test_constructor(self, start, end):
        line_segment = LineSegment(start, end)
        assert line_segment.start == start
        assert line_segment.end == end

    @pytest.mark.parametrize(
        "start, end",
        [
            (
                Coordinate(LengthUnit(0.1), LengthUnit(0.65), Level(4)),
                Coordinate(LengthUnit(0.45), LengthUnit(61.1), Level(1)),
            ),
            (
                Coordinate(LengthUnit(1.1), LengthUnit(-0.1), Level(0)),
                Coordinate(LengthUnit(1.1), LengthUnit(-0.1), Level(0)),
            ),
        ],
    )
    def test_constructor_failing(self, start, end):
        with pytest.raises(ValueError):
            LineSegment(start, end)

    @pytest.mark.parametrize(
        "line_segment",
        [
            LineSegment(
                Coordinate(LengthUnit(0.1), LengthUnit(0.65), Level(4)),
                Coordinate(LengthUnit(0.45), LengthUnit(61.1), Level(4)),
            ),
            LineSegment(
                Coordinate(LengthUnit(36.1), LengthUnit(45.1), Level(1)),
                Coordinate(LengthUnit(67.1), LengthUnit(56.1), Level(1)),
            ),
            LineSegment(
                Coordinate(LengthUnit(-32.54), LengthUnit(-61.11), Level(-4)),
                Coordinate(LengthUnit(-12.6), LengthUnit(-718.3), Level(-4)),
            ),
            LineSegment(
                Coordinate(LengthUnit(0.1), LengthUnit(-56.1), Level(0)),
                Coordinate(LengthUnit(-56.1), LengthUnit(0.1), Level(0)),
            ),
        ],
    )
    def test_rotate(self, line_segment):
        line_segment_before = LineSegment(line_segment)
        line_segment.rotate()

        assert line_segment.start == line_segment_before.end
        assert line_segment.end == line_segment_before.start

    @pytest.mark.parametrize(
        "line_segment, expected",
        [
            (
                LineSegment(
                    Coordinate(LengthUnit(0.1), LengthUnit(0.65), Level(4)),
                    Coordinate(LengthUnit(0.45), LengthUnit(61.1), Level(4)),
                ),
                "LINE_SEGMENT: (COORDINATE: (0.1000 m, 0.6500 m) -- LEVEL: 4) -- (COORDINATE: (0.4500 m, 61.10 m) -- "
                "LEVEL: 4)",
            ),
            (
                LineSegment(
                    Coordinate(LengthUnit(-32.5), LengthUnit(0.11), Level(20)),
                    Coordinate(LengthUnit(-41.1), LengthUnit(0.11), Level(20)),
                ),
                "LINE_SEGMENT: (COORDINATE: (-32.50 m, 0.1100 m) -- LEVEL: 20) -- (COORDINATE: (-41.10 m, 0.1100 m) "
                "-- LEVEL: 20)",
            ),
            (
                LineSegment(
                    Coordinate(LengthUnit(4.145), LengthUnit(-3.1), Level(-2)),
                    Coordinate(LengthUnit(90.1), LengthUnit(0.11), Level(-2)),
                ),
                "LINE_SEGMENT: (COORDINATE: (4.145 m, -3.100 m) -- LEVEL: -2) -- (COORDINATE: (90.10 m, 0.1100 m) -- "
                "LEVEL: -2)",
            ),
            (
                LineSegment(
                    Coordinate(LengthUnit(0.001), LengthUnit(3.1), Level(1)),
                    Coordinate(LengthUnit(-41.1), LengthUnit(8.11), Level(1)),
                ),
                "LINE_SEGMENT: (COORDINATE: (0.001000 m, 3.100 m) -- LEVEL: 1) -- (COORDINATE: (-41.10 m, 8.110 m) -- "
                "LEVEL: 1)",
            ),
            (
                LineSegment(
                    Coordinate(LengthUnit(4.145), LengthUnit(-3.1), Level(-2)),
                    Coordinate(LengthUnit(90.1), LengthUnit(0.11), Level(-2)),
                ),
                "LINE_SEGMENT: (COORDINATE: (4.145 m, -3.100 m) -- LEVEL: -2) -- (COORDINATE: (90.10 m, 0.1100 m) -- "
                "LEVEL: -2)",
            ),
        ],
    )
    def test_to_string(self, line_segment, expected):
        assert str(line_segment) == expected
        assert repr(line_segment) == expected

    @pytest.mark.parametrize(
        "line_segment, other, result",
        [
            (
                LineSegment(
                    Coordinate(LengthUnit(0.1), LengthUnit(0.65), Level(4)),
                    Coordinate(LengthUnit(0.45), LengthUnit(61.1), Level(4)),
                ),
                LineSegment(
                    Coordinate(LengthUnit(0.1), LengthUnit(0.65), Level(4)),
                    Coordinate(LengthUnit(0.45), LengthUnit(61.1), Level(4)),
                ),
                True,
            ),
            (
                LineSegment(
                    Coordinate(LengthUnit(4.145), LengthUnit(-3.1), Level(-2)),
                    Coordinate(LengthUnit(90.1), LengthUnit(0.11), Level(-2)),
                ),
                LineSegment(
                    Coordinate(LengthUnit(90.1), LengthUnit(0.11), Level(-2)),
                    Coordinate(LengthUnit(4.145), LengthUnit(-3.1), Level(-2)),
                ),
                True,
            ),
            (
                LineSegment(
                    Coordinate(LengthUnit(-32.5), LengthUnit(0.11), Level(20)),
                    Coordinate(LengthUnit(-41.1), LengthUnit(0.11), Level(20)),
                ),
                LineSegment(
                    Coordinate(LengthUnit(-32.5), LengthUnit(0.11), Level(20)),
                    Coordinate(LengthUnit(-41.1), LengthUnit(0.11), Level(20)),
                ),
                True,
            ),
            (
                LineSegment(
                    Coordinate(LengthUnit(34.5), LengthUnit(56.81), Level(1)),
                    Coordinate(LengthUnit(0.41), LengthUnit(90.1), Level(1)),
                ),
                LineSegment(
                    Coordinate(LengthUnit(0.001), LengthUnit(3.1), Level(1)),
                    Coordinate(LengthUnit(-41.1), LengthUnit(8.11), Level(1)),
                ),
                False,
            ),
            (
                LineSegment(
                    Coordinate(LengthUnit(-32.5), LengthUnit(0.11), Level(20)),
                    Coordinate(LengthUnit(-41.1), LengthUnit(0.11), Level(20)),
                ),
                LineSegment(
                    Coordinate(LengthUnit(-32.5), LengthUnit(0.11), Level(1)),
                    Coordinate(LengthUnit(-41.1), LengthUnit(0.11), Level(1)),
                ),
                False,
            ),
        ],
    )
    def test_comparison_operators(self, line_segment, other, result):
        assert (line_segment == other) == result
        assert (line_segment != other) != result
