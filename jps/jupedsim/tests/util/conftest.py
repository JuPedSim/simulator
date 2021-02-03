from dataclasses import dataclass

from jupedsim.util.event import EventType


@dataclass(frozen=True, eq=True)
class DummyEvent(EventType):
    name: str = "dummy"


def equal_ignore_order(a, b):
    """
    Use only when elements are neither hashable nor sortable!
    See: https://stackoverflow.com/a/7829388 for more details

    Tries to remove every element of a from b. Afterwards checks if b is empty.
    """
    unmatched = list(b)

    for element in a:
        try:
            unmatched.remove(element)
        except ValueError:
            return False
    return not unmatched
