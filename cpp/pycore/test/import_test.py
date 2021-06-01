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


def test_simulator_interface_exposes_all_expected_methods():
    """
    Make sure that all methods that we want to expose are actually callable.
    """
    import jpscore

    sim = jpscore.Simulation()
    assert callable(getattr(sim, "compute_next_step"))
    assert callable(getattr(sim, "add_agent"))
    assert callable(getattr(sim, "get_world_builder"))
