import pytest
from jpscore.geometry import (
    Area,
    Coordinate,
    LengthUnit,
    Level,
    LineSegment,
    Units,
)


class TestArea:
    @pytest.mark.parametrize(
        "coordinates",
        [
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
            ],
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
                Coordinate(
                    LengthUnit(0.1, Units.m),
                    LengthUnit(0.65, Units.m),
                    Level(3),
                ),
            ],
        ],
    )
    def test_constructor_from_coordinates(self, coordinates):
        area = Area(coordinates)

        # if start != end compare whole list, else skip last element
        if coordinates[0] != coordinates[-1]:
            assert area.polygon == coordinates
        else:
            assert area.polygon == coordinates[:-1]

    @pytest.mark.parametrize(
        "coordinates",
        [
            [],
            [
                Coordinate(
                    LengthUnit(0.1, Units.m),
                    LengthUnit(0.65, Units.m),
                    Level(4),
                ),
                Coordinate(
                    LengthUnit(0.45, Units.m),
                    LengthUnit(61.1, Units.m),
                    Level(4),
                ),
            ],
            [
                Coordinate(
                    LengthUnit(0.1, Units.m),
                    LengthUnit(0.65, Units.m),
                    Level(3),
                ),
                Coordinate(
                    LengthUnit(0.45, Units.m),
                    LengthUnit(61.1, Units.m),
                    Level(5),
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
            ],
        ],
    )
    def test_constructor_from_coordinates_failing(self, coordinates):
        with pytest.raises(RuntimeError):
            Area(coordinates)

    @pytest.mark.parametrize(
        "line_segments",
        [
            [
                LineSegment(
                    Coordinate(
                        LengthUnit(7.11, Units.m),
                        LengthUnit(45.1, Units.m),
                        Level(3),
                    ),
                    Coordinate(
                        LengthUnit(0.1, Units.m),
                        LengthUnit(0.65, Units.m),
                        Level(3),
                    ),
                ),
                LineSegment(
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
                ),
                LineSegment(
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
                ),
                LineSegment(
                    Coordinate(
                        LengthUnit(1.3, Units.m),
                        LengthUnit(-12.1, Units.m),
                        Level(3),
                    ),
                    Coordinate(
                        LengthUnit(7.11, Units.m),
                        LengthUnit(45.1, Units.m),
                        Level(3),
                    ),
                ),
            ],
            [
                LineSegment(
                    Coordinate(
                        LengthUnit(7.11, Units.m),
                        LengthUnit(45.1, Units.m),
                        Level(3),
                    ),
                    Coordinate(
                        LengthUnit(0.1, Units.m),
                        LengthUnit(0.65, Units.m),
                        Level(3),
                    ),
                ),
                LineSegment(
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
                ),
                LineSegment(
                    Coordinate(
                        LengthUnit(0.45, Units.m),
                        LengthUnit(61.1, Units.m),
                        Level(3),
                    ),
                    Coordinate(
                        LengthUnit(7.11, Units.m),
                        LengthUnit(45.1, Units.m),
                        Level(3),
                    ),
                ),
            ],
            [
                LineSegment(
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
                ),
                LineSegment(
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
                ),
                LineSegment(
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
                ),
                LineSegment(
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
                ),
                LineSegment(
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
                ),
                LineSegment(
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
                ),
            ],
        ],
    )
    def test_constructor_from_line_segments(self, line_segments):
        coordinates = []
        for index, line_segment in enumerate(line_segments):
            coordinates.append(line_segment.start)
            if (index % 3) == 1:
                line_segment.rotate()

        assert Area(line_segments) == Area(coordinates)

    @pytest.mark.parametrize(
        "line_segments",
        [
            [],
            [
                LineSegment(
                    Coordinate(
                        LengthUnit(7.11, Units.m),
                        LengthUnit(45.1, Units.m),
                        Level(3),
                    ),
                    Coordinate(
                        LengthUnit(0.1, Units.m),
                        LengthUnit(0.65, Units.m),
                        Level(3),
                    ),
                ),
                LineSegment(
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
                ),
            ],
        ],
    )
    def test_constructor_from_line_segments_failing(self, line_segments):
        with pytest.raises(RuntimeError):
            Area(line_segments)

    @pytest.mark.parametrize(
        "area, other, result",
        [
            (
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
                True,
            ),
            (
                Area(
                    [
                        Coordinate(
                            LengthUnit(7.11, Units.m),
                            LengthUnit(45.1, Units.m),
                            Level(3),
                        ),
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
                            LengthUnit(7.11, Units.m),
                            LengthUnit(45.1, Units.m),
                            Level(3),
                        ),
                    ]
                ),
                Area(
                    [
                        Coordinate(
                            LengthUnit(7.11, Units.m),
                            LengthUnit(45.1, Units.m),
                            Level(3),
                        ),
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
                            LengthUnit(7.11, Units.m),
                            LengthUnit(45.1, Units.m),
                            Level(3),
                        ),
                    ]
                ),
                True,
            ),
            (
                Area(
                    [
                        Coordinate(
                            LengthUnit(7.11, Units.m),
                            LengthUnit(45.1, Units.m),
                            Level(3),
                        ),
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
                False,
            ),
        ],
    )
    def test_comparison_operators(self, area, other, result):
        assert (area == other) == result
        assert (area != other) != result

    @pytest.mark.parametrize(
        "area, coordinates",
        [
            (
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
                ],
            ),
            (
                Area(
                    [
                        Coordinate(
                            LengthUnit(7.11, Units.m),
                            LengthUnit(45.1, Units.m),
                            Level(3),
                        ),
                        Coordinate(
                            LengthUnit(0.1, Units.m),
                            LengthUnit(0.65, Units.m),
                            Level(3),
                        ),
                        Coordinate(
                            LengthUnit(1.3, Units.m),
                            LengthUnit(-12.1, Units.m),
                            Level(3),
                        ),
                        Coordinate(
                            LengthUnit(7.11, Units.m),
                            LengthUnit(45.1, Units.m),
                            Level(3),
                        ),
                    ]
                ),
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
                        LengthUnit(7.11, Units.m),
                        LengthUnit(45.1, Units.m),
                        Level(3),
                    ),
                ],
            ),
        ],
    )
    def test_read_only_properties(self, area, coordinates):
        with pytest.raises(AttributeError):
            area.polygon = coordinates
