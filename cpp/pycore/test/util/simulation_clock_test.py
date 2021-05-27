import pytest
from jpscore import SimulationClock

class TestSimulationClock:
    def test(self):
        s = SimulationClock(5, 0.2)
        times = []
        for step in s.steps():
            times.append(step*s.deltaT)
        return 0
