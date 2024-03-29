import pytest
from jpscore import JPSGeometryException
from jpscore.geometry import Coordinate, LengthUnit, LineSegment, Units


class TestLineSegment:
    @pytest.mark.parametrize(
        "start, end",
        [
            (
                Coordinate(
                    LengthUnit(0.1, Units.m),
                    LengthUnit(0.65, Units.m),
                ),
                Coordinate(
                    LengthUnit(0.45, Units.m),
                    LengthUnit(61.1, Units.m),
                ),
            ),
            (
                Coordinate(
                    LengthUnit(1.3, Units.m),
                    LengthUnit(-12.1, Units.m),
                ),
                Coordinate(
                    LengthUnit(5.1, Units.m),
                    LengthUnit(-41.0, Units.m),
                ),
            ),
            (
                Coordinate(
                    LengthUnit(45.1, Units.m),
                    LengthUnit(-45.11, Units.m),
                ),
                Coordinate(
                    LengthUnit(7.11, Units.m),
                    LengthUnit(45.1, Units.m),
                ),
            ),
            (
                Coordinate(
                    LengthUnit(-56.61, Units.m),
                    LengthUnit(1.34, Units.m),
                ),
                Coordinate(
                    LengthUnit(-4.11, Units.m),
                    LengthUnit(7.0001, Units.m),
                ),
            ),
            (
                Coordinate(
                    LengthUnit(-41.1111, Units.m),
                    LengthUnit(-324.11, Units.m),
                ),
                Coordinate(
                    LengthUnit(-41.0, Units.m),
                    LengthUnit(-320.11, Units.m),
                ),
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
                Coordinate(
                    LengthUnit(1.1, Units.m),
                    LengthUnit(-0.1, Units.m),
                ),
                Coordinate(
                    LengthUnit(1.1, Units.m),
                    LengthUnit(-0.1, Units.m),
                ),
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
                Coordinate(
                    LengthUnit(0.1, Units.m),
                    LengthUnit(0.65, Units.m),
                ),
                Coordinate(
                    LengthUnit(0.45, Units.m),
                    LengthUnit(61.1, Units.m),
                ),
            ),
            LineSegment(
                Coordinate(
                    LengthUnit(36.1, Units.m),
                    LengthUnit(45.1, Units.m),
                ),
                Coordinate(
                    LengthUnit(67.1, Units.m),
                    LengthUnit(56.1, Units.m),
                ),
            ),
            LineSegment(
                Coordinate(
                    LengthUnit(-32.54, Units.m),
                    LengthUnit(-61.11, Units.m),
                ),
                Coordinate(
                    LengthUnit(-12.6, Units.m),
                    LengthUnit(-718.3, Units.m),
                ),
            ),
            LineSegment(
                Coordinate(
                    LengthUnit(0.1, Units.m),
                    LengthUnit(-56.1, Units.m),
                ),
                Coordinate(
                    LengthUnit(-56.1, Units.m),
                    LengthUnit(0.1, Units.m),
                ),
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
                    Coordinate(
                        LengthUnit(0.1, Units.m),
                        LengthUnit(0.65, Units.m),
                    ),
                    Coordinate(
                        LengthUnit(0.45, Units.m),
                        LengthUnit(61.1, Units.m),
                    ),
                ),
                LineSegment(
                    Coordinate(
                        LengthUnit(0.1, Units.m),
                        LengthUnit(0.65, Units.m),
                    ),
                    Coordinate(
                        LengthUnit(0.45, Units.m),
                        LengthUnit(61.1, Units.m),
                    ),
                ),
                True,
            ),
            (
                LineSegment(
                    Coordinate(
                        LengthUnit(4.145, Units.m),
                        LengthUnit(-3.1, Units.m),
                    ),
                    Coordinate(
                        LengthUnit(90.1, Units.m),
                        LengthUnit(0.11, Units.m),
                    ),
                ),
                LineSegment(
                    Coordinate(
                        LengthUnit(90.1, Units.m),
                        LengthUnit(0.11, Units.m),
                    ),
                    Coordinate(
                        LengthUnit(4.145, Units.m),
                        LengthUnit(-3.1, Units.m),
                    ),
                ),
                True,
            ),
            (
                LineSegment(
                    Coordinate(
                        LengthUnit(-32.5, Units.m),
                        LengthUnit(0.11, Units.m),
                    ),
                    Coordinate(
                        LengthUnit(-41.1, Units.m),
                        LengthUnit(0.11, Units.m),
                    ),
                ),
                LineSegment(
                    Coordinate(
                        LengthUnit(-32.5, Units.m),
                        LengthUnit(0.11, Units.m),
                    ),
                    Coordinate(
                        LengthUnit(-41.1, Units.m),
                        LengthUnit(0.11, Units.m),
                    ),
                ),
                True,
            ),
            (
                LineSegment(
                    Coordinate(
                        LengthUnit(34.5, Units.m),
                        LengthUnit(56.81, Units.m),
                    ),
                    Coordinate(
                        LengthUnit(0.41, Units.m),
                        LengthUnit(90.1, Units.m),
                    ),
                ),
                LineSegment(
                    Coordinate(
                        LengthUnit(0.001, Units.m),
                        LengthUnit(3.1, Units.m),
                    ),
                    Coordinate(
                        LengthUnit(-41.1, Units.m),
                        LengthUnit(8.11, Units.m),
                    ),
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
                    Coordinate(
                        LengthUnit(-32.5, Units.m),
                        LengthUnit(0.11, Units.m),
                    ),
                    Coordinate(
                        LengthUnit(-41.1, Units.m),
                        LengthUnit(0.11, Units.m),
                    ),
                ),
                Coordinate(
                    LengthUnit(45.1, Units.m),
                    LengthUnit(1.1, Units.m),
                ),
                Coordinate(
                    LengthUnit(-41.1, Units.m),
                    LengthUnit(45.1, Units.m),
                ),
            ),
            (
                LineSegment(
                    Coordinate(
                        LengthUnit(0.1, Units.m),
                        LengthUnit(0.65, Units.m),
                    ),
                    Coordinate(
                        LengthUnit(0.12, Units.m),
                        LengthUnit(61.1, Units.m),
                    ),
                ),
                Coordinate(
                    LengthUnit(234.1, Units.m),
                    LengthUnit(0.11, Units.m),
                ),
                Coordinate(
                    LengthUnit(-41.1, Units.m),
                    LengthUnit(0.11, Units.m),
                ),
            ),
        ],
    )
    def test_read_only(self, line_segment, new_start, new_end):
        with pytest.raises(AttributeError):
            line_segment.start = new_start
        with pytest.raises(AttributeError):
            line_segment.end = new_end
