import pytest


def test_world_interface_exposes_all_expected_methods():
    """
    Make sure that all methods that we want to expose are actually callable.
    """
    import jpscore

    world = jpscore.geometry.World()
    assert hasattr(world, "agents")
    assert callable(getattr(world, "add_level"))


from jpscore import Agent  # nopep8
from jpscore.geometry import (  # nopep8
    Coordinate,
    LengthUnit,
    Level,
    LevelStorage,
    Units,
    World,
)


@pytest.mark.parametrize(
    "coordinates, new_position",
    [
        (
            [
                Coordinate(LengthUnit(0.1, Units.m), LengthUnit(4, Units.m)),
                Coordinate(LengthUnit(6, Units.m), LengthUnit(1, Units.m)),
                Coordinate(LengthUnit(43, Units.m), LengthUnit(12, Units.m)),
            ],
            Coordinate(LengthUnit(51, Units.m), LengthUnit(56, Units.m)),
        ),
        (
            [
                Coordinate(LengthUnit(812, Units.m), LengthUnit(675, Units.m)),
                Coordinate(LengthUnit(656, Units.m), LengthUnit(2, Units.m)),
                Coordinate(LengthUnit(43123, Units.m), LengthUnit(6, Units.m)),
                Coordinate(LengthUnit(498, Units.m), LengthUnit(45, Units.m)),
                Coordinate(LengthUnit(45, Units.m), LengthUnit(92, Units.m)),
            ],
            Coordinate(LengthUnit(-1, Units.m), LengthUnit(0, Units.m)),
        ),
    ],
)
def test_world_agents_as_reference(coordinates, new_position):

    world = World()
    ls = world.add_level(Level(0))
    for coordinate in coordinates:
        ls.add_agent(coordinate)

    world.agents[Level(0)][0].pos = new_position

    assert world.agents[Level(0)][0].pos == new_position
