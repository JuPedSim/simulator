import pytest
from jpscore import JPSException, SimulationClock


@pytest.mark.parametrize(
    "max_steps, delta_t",
    [(10, 0.1), (20, 0.001), (60, 0.1), (12446, 12)],
)
def test_simulation_clock_valid(max_steps, delta_t):
    s = SimulationClock(max_steps, delta_t)
    assert s.steps == max_steps
    assert s.deltaT == delta_t

    for step in range(s.steps):
        time = step * delta_t
        assert s.current_step == step
        assert s.current_time == time
        s.advance()

    with pytest.raises(JPSException):
        s.advance()


@pytest.mark.parametrize(
    "max_steps, delta_t",
    [
        (10, -0.1),
        (500, 0),
    ],
)
def test_simulation_clock_invalid(max_steps, delta_t):
    with pytest.raises(JPSException):
        s = SimulationClock(max_steps, delta_t)
