import json
from typing import List

from jupedsim.util.event import (
    DataclassJSONEncoder,
    Event,
    SpawnPedestrianEvent,
)
from jupedsim.util.loghelper import log_debug, log_error, log_info, log_warning


def process_generator(args) -> None:
    """
    Processes the event file generator
    :param args: Commandline arguments
    :return:
    """
    events = []
    if args.floor is not None:
        log_error("need floor")
    if len(args.x) == 1 and len(args.y) == 1 and args.floor is not None:
        if args.n != 1:
            log_warning("number of pedestrians != 1")
        else:
            events = generate_pedestrian_on_position(
                args.time, [args.x[0], args.y[0]], args.floor
            )

    write_to_event_file(args.o, events, args.overwrite)


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
    time: float, position, floor: int
) -> List[Event]:
    """
    Generates one pedestrian at time at position in floor.
    :param time: Time the pedestrian is spawned
    :param position: Position the pedestrian is spawned
    :param floor: Floor the pedestrian is spawned
    :return: List of length one containing the spawn pedestrian event
    """
    spawn_event = SpawnPedestrianEvent(position, floor)
    return [Event(time, spawn_event)]


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
    existing_events = read_events(file)

    if overwrite:
        other_events = [
            event
            for event in existing_events
            if event.event.type == "spawn_pedestrians"
        ]
        events = other_events + events
    else:
        events = existing_events + events

    with open(file, "w+") as json_file:
        json_file.write(json.dumps(events, indent=4, cls=DataclassJSONEncoder))

    return True
