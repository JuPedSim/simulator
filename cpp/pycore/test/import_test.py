import pytest


def test_import():
    """
    Most basic test that just checks that jpscore can be
    imported in python
    """
    try:
        import jpscore
    except:
        pytest.fail("Could not import jpscore!")


def test_simulator_interface_has_compute_next_step():
    """
    Make sure that all methods that we want to expose are actually callable.
    """
    import jpscore

    sim = jpscore.Simulation()
    assert callable(getattr(sim, "compute_next_step"))
