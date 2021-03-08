import pytest
from jpscore.geometry import LengthUnit, SpatialVector, Units


class TestSpatialVector:
    @pytest.mark.parametrize(
        "x, y",
        [
            (LengthUnit(-12.0, Units.m), LengthUnit(435.1, Units.m)),
            (LengthUnit(12.0, Units.m), LengthUnit(-71.5, Units.m)),
            (LengthUnit(-1.010101), LengthUnit(-0.0)),
            (LengthUnit(561.5, Units.m), LengthUnit(46.11, Units.m)),
            (LengthUnit(-0.01, Units.m), LengthUnit(73.12, Units.m)),
        ],
    )
    def test_constructor(self, x, y):
        spatial_vector = SpatialVector(x, y)
        assert spatial_vector.x == x
        assert spatial_vector.y == y

    @pytest.mark.parametrize(
        "spatial_vector, new_x, new_y",
        [
            (
                SpatialVector(
                    LengthUnit(-10.12, Units.m), LengthUnit(34.12, Units.m)
                ),
                LengthUnit(-12.45),
                LengthUnit(657, Units.m),
            ),
            (
                SpatialVector(
                    LengthUnit(345.0, Units.m), LengthUnit(-61.1, Units.m)
                ),
                LengthUnit(9.8, Units.m),
                LengthUnit(0.1, Units.m),
            ),
            (
                SpatialVector(
                    LengthUnit(-0.100001, Units.m), LengthUnit(65.1, Units.m)
                ),
                LengthUnit(0.00000001, Units.m),
                LengthUnit(12.5, Units.m),
            ),
            (
                SpatialVector(LengthUnit(-987.1), LengthUnit(-12.3)),
                LengthUnit(-987.1),
                LengthUnit(0.00001, Units.m),
            ),
            (
                SpatialVector(
                    LengthUnit(0.0, Units.m), LengthUnit(0.0, Units.m)
                ),
                LengthUnit(0.3, Units.m),
                LengthUnit(-0.001),
            ),
        ],
    )
    def test_setters(self, spatial_vector, new_x, new_y):
        spatial_vector.x = new_x
        assert spatial_vector.x == new_x

        spatial_vector.y = new_y
        assert spatial_vector.y == new_y

    @pytest.mark.parametrize(
        "spatial_vector, other, result",
        [
            (
                SpatialVector(
                    LengthUnit(-10.12, Units.m), LengthUnit(34.12, Units.m)
                ),
                SpatialVector(
                    LengthUnit(-10.12, Units.m), LengthUnit(34.12, Units.m)
                ),
                True,
            ),
            (
                SpatialVector(LengthUnit(-0.00004), LengthUnit(-123.4)),
                SpatialVector(LengthUnit(-0.00004), LengthUnit(-123.4)),
                True,
            ),
            (
                SpatialVector(
                    LengthUnit(612.12, Units.m), LengthUnit(-73.1, Units.m)
                ),
                SpatialVector(
                    LengthUnit(612.12, Units.m), LengthUnit(-73.1, Units.m)
                ),
                True,
            ),
            (
                SpatialVector(
                    LengthUnit(9.00001, Units.m), LengthUnit(0.00001, Units.m)
                ),
                SpatialVector(
                    LengthUnit(9.00001, Units.m), LengthUnit(0.00001, Units.m)
                ),
                True,
            ),
            (
                SpatialVector(
                    LengthUnit(-10.12, Units.m), LengthUnit(34.12, Units.m)
                ),
                SpatialVector(
                    LengthUnit(-10.1200001, Units.m),
                    LengthUnit(34.11, Units.m),
                ),
                False,
            ),
            (
                SpatialVector(
                    LengthUnit(912.111, Units.m), LengthUnit(4.6, Units.m)
                ),
                SpatialVector(
                    LengthUnit(912.111, Units.m), LengthUnit(-4.6, Units.m)
                ),
                False,
            ),
            (
                SpatialVector(
                    LengthUnit(0.0000001, Units.m), LengthUnit(65.11, Units.m)
                ),
                SpatialVector(
                    LengthUnit(0, Units.m), LengthUnit(65.11, Units.m)
                ),
                False,
            ),
            (
                SpatialVector(
                    LengthUnit(67.65, Units.m), LengthUnit(-76.1111, Units.m)
                ),
                SpatialVector(
                    LengthUnit(-76.1111, Units.m), LengthUnit(67.65, Units.m)
                ),
                False,
            ),
        ],
    )
    def test_comparison_operators(self, spatial_vector, other, result):
        assert (spatial_vector == other) == result
        assert (spatial_vector != other) != result
