import dataclasses
import json
from abc import abstractmethod
from dataclasses import asdict, dataclass, is_dataclass
from typing import Any, NamedTuple


class DataclassJSONEncoder(json.JSONEncoder):
    def default(self, o):
        if dataclasses.is_dataclass(o):
            return dataclasses.asdict(o)
        return super().default(o)


@dataclass
class EventType:
    """
    Abstract base class defining the type of events.
    """

    type: str

    @abstractmethod
    def get_json(self) -> str:
        pass

    @classmethod
    def from_json(cls, data):
        if data["type"] == "spawn_pedestrian":
            spawn = SpawnPedestrianEvent.from_json(data)
            return spawn

        return None


@dataclass
class SpawnPedestrianEvent(EventType):
    """
    EventType for spawning pedestrians at a given position on a specific floor
    """

    position: Any
    floor: int

    def __init__(self, position, floor: int):
        self.position = position
        self.floor = floor
        self.type = "spawn_pedestrian"
        return

    def get_json(self) -> str:
        return json.dumps(self, default=lambda o: o.__dict__)

    @classmethod
    def from_json(cls, data):
        position = data["position"]
        floor = data["floor"]
        return cls(position, floor)

    def __eq__(self, other):
        if type(self) is type(other):
            return (
                self.position == other.position and self.floor == other.floor
            )
        return False


@dataclass
class Event:
    """
    Class for storing the information which EventType is triggered at a given time.
    """

    time: float
    event: EventType

    def __init__(self, time: float, event: EventType):
        self.time = time
        self.event = event
        return

    def get_json(self) -> str:
        return json.dumps(self, default=lambda o: o.__dict__)

    @classmethod
    def from_json(cls, data):
        return cls(data["time"], EventType.from_json(data["event"]))

    def __eq__(self, other):
        if type(self) is type(other):
            return self.time == other.time and self.event == other.event
        return False
