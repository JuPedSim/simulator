import pytest
from jpscore.geometry import Area, Coordinate, LengthUnit, Level, LineSegment


def is_cyclic(to_search, to_find) -> bool:
    duplicated = to_search + to_search
    n = len(to_find)
    return any(
        to_find == duplicated[i : i + n]
        for i in range(len(duplicated) - n + 1)
    )


class TestArea:
    @pytest.mark.parametrize(
        "coordinates",
        [
            [
                Coordinate(LengthUnit(0.1), LengthUnit(0.65), Level(3)),
                Coordinate(LengthUnit(0.45), LengthUnit(61.1), Level(3)),
                Coordinate(LengthUnit(1.3), LengthUnit(-12.1), Level(3)),
                Coordinate(LengthUnit(5.1), LengthUnit(-41.0), Level(3)),
                Coordinate(LengthUnit(45.1), LengthUnit(-45.11), Level(3)),
                Coordinate(LengthUnit(7.11), LengthUnit(45.1), Level(3)),
            ],
            [
                Coordinate(LengthUnit(0.1), LengthUnit(0.65), Level(3)),
                Coordinate(LengthUnit(0.45), LengthUnit(61.1), Level(3)),
                Coordinate(LengthUnit(1.3), LengthUnit(-12.1), Level(3)),
                Coordinate(LengthUnit(5.1), LengthUnit(-41.0), Level(3)),
                Coordinate(LengthUnit(45.1), LengthUnit(-45.11), Level(3)),
                Coordinate(LengthUnit(7.11), LengthUnit(45.1), Level(3)),
                Coordinate(LengthUnit(0.1), LengthUnit(0.65), Level(3)),
            ],
        ],
    )
    def test_constructor_from_coordinates(self, coordinates):
        area = Area(coordinates)

        # if start != end compare whole list, else skip last element
        if coordinates[0] != coordinates[-1]:
            assert is_cyclic(area.polygon, coordinates)
        else:
            assert is_cyclic(area.polygon, coordinates[:-1])

    @pytest.mark.parametrize(
        "coordinates",
        [
            [],
            [
                Coordinate(LengthUnit(0.1), LengthUnit(0.65), Level(4)),
                Coordinate(LengthUnit(0.45), LengthUnit(61.1), Level(4)),
            ],
            [
                Coordinate(LengthUnit(0.1), LengthUnit(0.65), Level(3)),
                Coordinate(LengthUnit(0.45), LengthUnit(61.1), Level(5)),
                Coordinate(LengthUnit(1.3), LengthUnit(-12.1), Level(3)),
                Coordinate(LengthUnit(5.1), LengthUnit(-41.0), Level(3)),
            ],
        ],
    )
    def test_constructor_from_coordinates_failing(self, coordinates):
        with pytest.raises(RuntimeError):
            Area(coordinates)

    @pytest.mark.parametrize(
        "coordinates",
        [
            [
                Coordinate(LengthUnit(7.11), LengthUnit(45.1), Level(3)),
                Coordinate(LengthUnit(0.1), LengthUnit(0.65), Level(3)),
                Coordinate(LengthUnit(0.45), LengthUnit(61.1), Level(3)),
                Coordinate(LengthUnit(1.3), LengthUnit(-12.1), Level(3)),
                Coordinate(LengthUnit(7.11), LengthUnit(45.1), Level(3)),
            ],
            [
                Coordinate(LengthUnit(7.11), LengthUnit(45.1), Level(3)),
                Coordinate(LengthUnit(0.1), LengthUnit(0.65), Level(3)),
                Coordinate(LengthUnit(0.45), LengthUnit(61.1), Level(3)),
                Coordinate(LengthUnit(7.11), LengthUnit(45.1), Level(3)),
            ],
            [
                Coordinate(LengthUnit(45.54), LengthUnit(45.1), Level(-3)),
                Coordinate(LengthUnit(1.41), LengthUnit(34.1), Level(-3)),
                Coordinate(LengthUnit(-1.6), LengthUnit(12.1), Level(-3)),
                Coordinate(LengthUnit(-6.1), LengthUnit(-6.1), Level(-3)),
                Coordinate(LengthUnit(-1.5), LengthUnit(34.1), Level(-3)),
                Coordinate(LengthUnit(30.11), LengthUnit(15.1), Level(-3)),
                Coordinate(LengthUnit(45.54), LengthUnit(45.1), Level(-3)),
            ],
        ],
    )
    def test_constructor_from_line_segments(self, coordinates):
        line_segments = []
        for index, coordinate in enumerate(coordinates[:-1]):
            line_segment = LineSegment(coordinate, coordinates[index + 1])
            if (index % 4) == 1:
                line_segment.rotate()
            line_segments.append(line_segment)

        area = Area(line_segments)
        assert is_cyclic(area.polygon, coordinates[:-1])

    @pytest.mark.parametrize(
        "line_segments",
        [
            [],
            [
                LineSegment(
                    Coordinate(LengthUnit(7.11), LengthUnit(45.1), Level(3)),
                    Coordinate(LengthUnit(0.1), LengthUnit(0.65), Level(3)),
                ),
                LineSegment(
                    Coordinate(LengthUnit(0.1), LengthUnit(0.65), Level(3)),
                    Coordinate(LengthUnit(0.45), LengthUnit(61.1), Level(3)),
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
                True,
            ),
            (
                Area(
                    [
                        Coordinate(
                            LengthUnit(7.11), LengthUnit(45.1), Level(3)
                        ),
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
                            LengthUnit(7.11), LengthUnit(45.1), Level(3)
                        ),
                    ]
                ),
                Area(
                    [
                        Coordinate(
                            LengthUnit(7.11), LengthUnit(45.1), Level(3)
                        ),
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
                            LengthUnit(7.11), LengthUnit(45.1), Level(3)
                        ),
                    ]
                ),
                True,
            ),
            (
                Area(
                    [
                        Coordinate(
                            LengthUnit(7.11), LengthUnit(45.1), Level(3)
                        ),
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
                            LengthUnit(7.11), LengthUnit(45.1), Level(3)
                        ),
                    ]
                ),
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
                False,
            ),
        ],
    )
    def test_comparison_operators(self, area, other, result):
        assert (area == other) == result
        assert (area != other) != result
