import pytest
from jpscore.geometry import Level


class TestLevel:
    @pytest.mark.parametrize(
        "level_id, reference",
        [
            (1, Level(1)),
            (34, Level(34)),
            (-12, Level(-12)),
            (76, Level(76)),
            (1239512, Level(1239512)),
            (-6739512, Level(-6739512)),
        ],
    )
    def test_constructor(self, level_id, reference):
        level = Level(level_id)
        assert level.id() == level_id
        assert level == reference

    @pytest.mark.parametrize("level_id", ["str", 12.2, [10, 10]])
    def test_constructor_failing(self, level_id):
        with pytest.raises(TypeError):
            level = Level(level_id)

    @pytest.mark.parametrize(
        "level, expected",
        [
            (Level(34), "LEVEL: 34"),
            (Level(123), "LEVEL: 123"),
            (Level(0), "LEVEL: 0"),
            (Level(-1243), "LEVEL: -1243"),
            (Level(-782), "LEVEL: -782"),
        ],
    )
    def test_to_string(self, level, expected):
        assert str(level) == expected
        assert repr(level) == expected

    @pytest.mark.parametrize(
        "level, other, result",
        [
            (Level(0), Level(0), True),
            (Level(34), Level(34), True),
            (Level(-67), Level(-67), True),
            (Level(903423), Level(903423), True),
            (Level(-123435), Level(-123435), True),
            (Level(-123435), Level(123435), False),
            (Level(56), Level(345), False),
            (Level(-12), Level(-13), False),
            (Level(0), Level(12), False),
            (Level(0), Level(1), False),
        ],
    )
    def test_comparison_operators(self, level, other, result):
        assert (level == other) == result
        assert (level != other) != result
