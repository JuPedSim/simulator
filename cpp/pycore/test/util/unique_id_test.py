import pytest


def test_unique_id_agent_interface_has_bindings():
    """
    Make sure that all methods that we want to expose are actually callable.
    """
    import jpscore

    id = jpscore.UniqueIDAgent()
    assert hasattr(id, "id")
