import jpscore
import pytest


def test_loging():
    def cb(msg):
        print(msg)
        assert msg == "Simulator ctor"

    jpscore.logging.set_callback(level=jpscore.logging.Level.Debug, func=cb)
    simulator = jpscore.Simulation()
