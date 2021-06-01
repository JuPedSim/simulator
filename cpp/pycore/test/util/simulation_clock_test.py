from datetime import timedelta

import pytest


def test_simulationclock_interface_has_bindings():
    """
    Make sure that all methods that we want to expose are actually callable.
    """
    import jpscore

    clock = jpscore.SimulationClock(500, timedelta(milliseconds=10))
    assert callable(getattr(clock, "advance"))
    assert hasattr(clock, "deltaT")
    assert hasattr(clock, "steps")
    assert hasattr(clock, "current_step")
    assert hasattr(clock, "current_time")


@pytest.mark.parametrize(
    "max_steps, delta_t",
    [
        (500, timedelta(milliseconds=0)),
    ],
)
def test_simulation_clock_invalid(max_steps, delta_t):
    from jpscore import JPSException, SimulationClock

    with pytest.raises(JPSException):
        s = SimulationClock(max_steps, delta_t)
