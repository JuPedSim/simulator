import pytest
from jpscore import JPSGeometryException
from jpscore.geometry import Coordinate, LengthUnit, Level, LineSegment


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
        with pytest.raises(JPSGeometryException):
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
        start_before = line_segment.start
        end_before = line_segment.end

        line_segment.rotate()

        assert line_segment.start == end_before
        assert line_segment.end == start_before

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

    @pytest.mark.parametrize(
        "line_segment, new_start, new_end",
        [
            (
                LineSegment(
                    Coordinate(LengthUnit(-32.5), LengthUnit(0.11), Level(20)),
                    Coordinate(LengthUnit(-41.1), LengthUnit(0.11), Level(20)),
                ),
                Coordinate(LengthUnit(45.1), LengthUnit(1.1), Level(20)),
                Coordinate(LengthUnit(-41.1), LengthUnit(45.1), Level(20)),
            ),
            (
                LineSegment(
                    Coordinate(LengthUnit(0.1), LengthUnit(0.65), Level(4)),
                    Coordinate(LengthUnit(0.12), LengthUnit(61.1), Level(4)),
                ),
                Coordinate(LengthUnit(234.1), LengthUnit(0.11), Level(20)),
                Coordinate(LengthUnit(-41.1), LengthUnit(0.11), Level(20)),
            ),
        ],
    )
    def test_read_only(self, line_segment, new_start, new_end):
        with pytest.raises(AttributeError):
            line_segment.start = new_start
        with pytest.raises(AttributeError):
            line_segment.end = new_end
