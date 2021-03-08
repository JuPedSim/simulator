import pytest
from jpscore.geometry import LengthUnit, Units


class TestUnits:
    @pytest.mark.parametrize(
        "unit",
        ["um", "mm", "cm", "dm", "m", "km"],
    )
    def test_unit_exists(self, unit):
        assert Units.__members__[unit]

    @pytest.mark.parametrize(
        "unit",
        ["mmm", "KM", "Um", "M", "uM"],
    )
    def test_unit_not_exists(self, unit):
        with pytest.raises(KeyError):
            Units.__members__[unit]


class TestLengthUnit:
    @pytest.mark.parametrize(
        "unit, quantity",
        [
            (Units.um, 5),
            (Units.mm, 5),
            (Units.cm, 5),
            (Units.dm, 5),
            (Units.m, 5),
            (Units.km, 5),
            (Units.um, 1.2),
            (Units.mm, 3.4),
            (Units.cm, 0.000012),
            (Units.dm, 123123.09),
            (Units.m, 1.1),
            (Units.km, 512),
            (Units.um, -100),
            (Units.mm, -3.2),
            (Units.cm, -5.2),
            (Units.dm, -0.00001),
            (Units.m, -10),
            (Units.km, -1),
        ],
    )
    def test_length_unit_ctor(self, unit, quantity):
        assert type(LengthUnit(quantity, unit)) is LengthUnit

    @pytest.mark.parametrize(
        "lu",
        [LengthUnit(1, Units.m), LengthUnit(1.001, Units.m)],
    )
    def test_lu_getter(self, lu):
        assert type(lu.um) is float
        assert type(lu.mm) is float
        assert type(lu.cm) is float
        assert type(lu.dm) is float
        assert type(lu.m) is float
        assert type(lu.km) is float

    @pytest.mark.parametrize(
        "lu, other",
        [
            (LengthUnit(1, Units.m), LengthUnit(1, Units.m)),
            (LengthUnit(2.1, Units.m), LengthUnit(2.1, Units.m)),
            (LengthUnit(2.0, Units.mm), LengthUnit(2000.0, Units.um)),
            (LengthUnit(2, Units.m), LengthUnit(2.0, Units.m)),
        ],
    )
    def test_lu_eq_operators_positiv(self, lu, other):
        assert lu == other
        assert not (lu != other)

    @pytest.mark.parametrize(
        "lu, other",
        [
            (LengthUnit(2, Units.m), LengthUnit(1, Units.m)),
            (LengthUnit(2.1, Units.mm), LengthUnit(2.1, Units.m)),
            (LengthUnit(20.0, Units.mm), LengthUnit(2000.0, Units.um)),
            (LengthUnit(2, Units.km), LengthUnit(2.0, Units.m)),
        ],
    )
    def test_lu_eq_operators_negativ(self, lu, other):
        assert not (lu == other)
        assert lu != other

    @pytest.mark.parametrize(
        "lu, expected_str, expected_repr",
        [
            (LengthUnit(2, Units.m), "2.0000 m", "2.0000 m"),
            (LengthUnit(2, Units.mm), "0.0020 m", "0.0020 m"),
            (LengthUnit(2, Units.um), "0.0000 m", "0.0000 m"),
        ],
    )
    def test_lu_str_repr(self, lu, expected_str, expected_repr):
        assert str(lu) == expected_str
        assert repr(lu) == expected_repr
