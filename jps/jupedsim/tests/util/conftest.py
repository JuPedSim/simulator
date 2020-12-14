from dataclasses import dataclass

import pytest
from jupedsim.util.event import EventType


@dataclass(frozen=True, eq=True)
class DummyEvent(EventType):
    name: str = "dummy"


def equal_ignore_order(a, b):
    """ Use only when elements are neither hashable nor sortable! """
    unmatched = list(b)
    for element in a:
        try:
            unmatched.remove(element)
        except ValueError:
            return False
    return not unmatched
