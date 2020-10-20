import jpscore
import pytest


def test_example():
    assert jpscore.Simulation().get() == 1
