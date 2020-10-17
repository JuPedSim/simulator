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
