import dataclasses
import json
import numbers
from dataclasses import dataclass
from typing import Dict, List


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

    def get_json(self) -> str:
        return json.dumps(self, default=lambda o: o.__dict__)

    @classmethod
    def from_json(cls, data: str):
        json_data = json.loads(data)
        event_type = json_data["type"]

        if event_type == "spawn_pedestrian":
            spawn = SpawnPedestrianEvent.from_json(data)
            return spawn

        raise NotImplementedError(
            "{} is a not supported EventType.".format(event_type)
        )


@dataclass
class SpawnPedestrianEvent(EventType):
    """
    EventType for spawning pedestrians at a given position on a specific floor
    """

    position: List[float]
    floor: int

    def __init__(self, position: List[float], floor: int):
        self.type = "spawn_pedestrian"
        self.position = position
        self.floor = floor
        return

    @classmethod
    def from_json(cls, data: str):
        json_data = json.loads(data)
        position = json_data.get("position")
        if (
            not isinstance(position, List)
            or not all(isinstance(x, numbers.Number) for x in position)
            or not len(position) == 2
        ):
            raise ValueError(
                '"position" needs to be a List of 2 numbers, but is {}.'.format(
                    position
                )
            )

        floor = json_data.get("floor")
        if not isinstance(floor, int):
            raise ValueError(
                '"floor" needs to be a integer value, but is {}.'.format(floor)
            )

        return cls(position, floor)


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
    def from_json(cls, data: str):
        json_data = json.loads(data)
        time = json_data.get("time")
        if not isinstance(time, numbers.Number):
            raise ValueError(
                '"time" needs to be a number, but is {}.'.format(time)
            )

        time = float(time)
        if time < 0.0:
            raise ValueError(
                '"time" needs to be a positive number, but is {}.'.format(time)
            )

        event_type_json = json_data.get("event")
        if not isinstance(event_type_json, Dict):
            raise ValueError(
                '"event" needs to be a json representation of EventType, but is {}.'.format(
                    event_type_json
                )
            )
        event_type = json.dumps(event_type_json)

        return cls(time, EventType.from_json(event_type))
