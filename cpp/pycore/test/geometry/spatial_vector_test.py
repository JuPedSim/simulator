import pytest
from jpscore.geometry import SpatialVector, LengthUnit


class TestSpatialVector:
    @pytest.mark.parametrize(
        "x, y",
        [
            (LengthUnit(-12.0), LengthUnit(435.1)),
            (LengthUnit(12.0), LengthUnit(-71.5)),
            (LengthUnit(-1.010101), LengthUnit(-0.0)),
            (LengthUnit(561.5), LengthUnit(46.11)),
            (LengthUnit(-0.01), LengthUnit(73.12)),
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
                SpatialVector(LengthUnit(-10.12), LengthUnit(34.12)),
                LengthUnit(-12.45),
                LengthUnit(657),
            ),
            (
                SpatialVector(LengthUnit(345.0), LengthUnit(-61.1)),
                LengthUnit(9.8),
                LengthUnit(0.1),
            ),
            (
                SpatialVector(LengthUnit(-0.100001), LengthUnit(65.1)),
                LengthUnit(0.00000001),
                LengthUnit(12.5),
            ),
            (
                SpatialVector(LengthUnit(-987.1), LengthUnit(-12.3)),
                LengthUnit(-987.1),
                LengthUnit(0.00001),
            ),
            (
                SpatialVector(LengthUnit(0.0), LengthUnit(0.0)),
                LengthUnit(0.3),
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
        "spatial_vector, expected",
        [
            (
                SpatialVector(LengthUnit(-10.12), LengthUnit(34.12)),
                "SPATIAL_VECTOR (-10.12 m, 34.12 m)",
            ),
            (
                SpatialVector(LengthUnit(325.1), LengthUnit(5.111)),
                "SPATIAL_VECTOR (325.1 m, 5.111 m)",
            ),
            (
                SpatialVector(LengthUnit(0.12), LengthUnit(-0)),
                "SPATIAL_VECTOR (0.1200 m, 0.000 m)",
            ),
            (
                SpatialVector(LengthUnit(-1.001), LengthUnit(-0.00001)),
                "SPATIAL_VECTOR (-1.001 m, -1.000e-05 m)",
            ),
            (
                SpatialVector(LengthUnit(94.1), LengthUnit(6.120000001)),
                "SPATIAL_VECTOR (94.10 m, 6.120 m)",
            ),
        ],
    )
    def test_to_string(self, spatial_vector, expected):
        assert str(spatial_vector) == expected
        assert repr(spatial_vector) == expected

    @pytest.mark.parametrize(
        "spatial_vector, other, result",
        [
            (
                SpatialVector(LengthUnit(-10.12), LengthUnit(34.12)),
                SpatialVector(LengthUnit(-10.12), LengthUnit(34.12)),
                True,
            ),
            (
                SpatialVector(LengthUnit(-0.00004), LengthUnit(-123.4)),
                SpatialVector(LengthUnit(-0.00004), LengthUnit(-123.4)),
                True,
            ),
            (
                SpatialVector(LengthUnit(612.12), LengthUnit(-73.1)),
                SpatialVector(LengthUnit(612.12), LengthUnit(-73.1)),
                True,
            ),
            (
                SpatialVector(LengthUnit(9.00001), LengthUnit(0.00001)),
                SpatialVector(LengthUnit(9.00001), LengthUnit(0.00001)),
                True,
            ),
            (
                SpatialVector(LengthUnit(-10.12), LengthUnit(34.12)),
                SpatialVector(LengthUnit(-10.1200001), LengthUnit(34.11)),
                False,
            ),
            (
                SpatialVector(LengthUnit(912.111), LengthUnit(4.6)),
                SpatialVector(LengthUnit(912.111), LengthUnit(-4.6)),
                False,
            ),
            (
                SpatialVector(LengthUnit(0.0000001), LengthUnit(65.11)),
                SpatialVector(LengthUnit(0), LengthUnit(65.11)),
                False,
            ),
            (
                SpatialVector(LengthUnit(67.65), LengthUnit(-76.1111)),
                SpatialVector(LengthUnit(-76.1111), LengthUnit(67.65)),
                False,
            ),
        ],
    )
    def test_comparison_operators(self, spatial_vector, other, result):
        assert (spatial_vector == other) == result
        assert (spatial_vector != other) != result
