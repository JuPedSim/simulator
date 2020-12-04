"""
pytest will emit error code 5 if there was no test run.
For the CI we use this dummy test to check if the test infrastructure is working.
"""


def test_dummy_CI():
    pass
