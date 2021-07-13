import pytest


def test_agent_interface_has_bindings():
    """
    Make sure that all methods that we want to expose are actually callable.
    """
    import jpscore
    from jpscore.geometry import Coordinate, LengthUnit, Units

    agent = jpscore.Agent(
        Coordinate(
            LengthUnit(94.45, Units.m),
            LengthUnit(90941, Units.m),
        )
    )
    assert hasattr(agent, "id")
    assert hasattr(agent, "pos")
