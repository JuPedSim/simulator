import json
from typing import List

from jupedsim.util.event import (
    DataclassJSONEncoder,
    Event,
    SpawnPedestrianEvent,
)
from jupedsim.util.loghelper import log_debug, log_error, log_info, log_warning


def generate_spawn_events(args) -> None:
    """
    Generates all spawn events defined in args. Args contains time and position of the pedestrian, and also the
    output information (file, overwriting).
    :param args: Commandline arguments
    :return:
    """
    events = generate_pedestrian_on_position(
        args.time, [args.x, args.y], args.level
    )
    write_to_event_file(args.o, events, args.overwrite)
    log_info(
        "Generate pedestrian events have been written to: {}".format(args.o)
    )


def read_events(file) -> List[Event]:
    """
    Reads from a file and creates a list of Events
    :param file: path to a json file containing events
    :return: List of Events from json file
    """
    events = []
    with open(file) as json_file:
        objs = json.load(json_file)
        for obj in objs:
            test = Event.from_json(json.dumps(obj))
            events.append(test)
    return events


def generate_pedestrian_on_position(
    time: float, position, level: int
) -> List[Event]:
    """
    Generates one pedestrian at time at position in level.
    :param time: Time the pedestrian is spawned
    :param position: Position the pedestrian is spawned
    :param level: Level the pedestrian is spawned
    :return: List of length one containing the spawn pedestrian event
    """
    spawn_event = SpawnPedestrianEvent(position, level)
    return [Event(time, spawn_event)]


def merge_spawn_pedestrian_events(
    events: List[Event], existing_events: List[Event], overwrite: bool
) -> List[Event]:
    """
    Merges the two lists according to overwrite strategy.

    overwrite == True:
        Create a List from events and all not SpawnPedestrianEvents in existing_events
    overwrite == False:
        Concat events and existing_events

    :param events: List of Events, which will be kept
    :param existing_events: List of Events, where depending on overwrite SpawnPedestrianEvents may not be kept
    :param overwrite: SpawnPedestrianEvents in existing_events will be overwritten
    :return: Merged list of events
    """
    if overwrite:
        other_events = [
            event
            for event in existing_events
            if event.event.type != "spawn_pedestrian"
        ]
        merged_events = other_events + events
    else:
        merged_events = existing_events + events

    return merged_events


def write_to_event_file(
    file: str, events: List[Event], overwrite: bool
) -> bool:
    """
    Writes the list of events to the given file. If overwrite is set, all events which
    are SpawnPedestrianEvents will be deleted.
    :param file: Output file
    :param events: List of SpawnPedestrianEvents
    :param overwrite: Existing SpawnPedestrianEvents will be overwritten
    :return: success
    """
    existing_events = read_events(file) if overwrite else []
    events = merge_spawn_pedestrian_events(events, existing_events, overwrite)

    with open(file, "w+") as json_file:
        json_file.write(json.dumps(events, indent=4, cls=DataclassJSONEncoder))

    return True
