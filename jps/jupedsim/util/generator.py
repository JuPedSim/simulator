import json
import pathlib
import sys
from random import shuffle
from typing import List

from jupedsim.util.event import (
    DataclassJSONEncoder,
    Event,
    SpawnPedestrianEvent,
)
from jupedsim.util.loghelper import log_debug, log_error, log_info, log_warning
from jupedsim.util.pedestran_area_generator import generate_spawn_points


def generate_spawn_events(args) -> None:
    """
    Generates all spawn events defined in args. Args contains the output information (file, overwriting), time, flag to overwrite
    and also either position of the pedestrian, or the area specification, a delta time between spawn events and  number of pedestrians.
    :param args: Commandline arguments
    :return:
    """
    events: list = []
    if args.generate_mode == "area":
        spawn_points = generate_spawn_points(
            args.area, args.pedestrian_distance
        )
        if isinstance(spawn_points, str):
            sys.exit(spawn_points)
        shuffle(spawn_points)
        for i in range(0, args.number_pedestrans):
            events.extend(
                generate_pedestrian_on_position(
                    args.time + (args.delta_t * i),
                    spawn_points[i % (len(spawn_points))],
                    args.level,
                )
            )
    elif args.generate_mode == "single":
        events = generate_pedestrian_on_position(
            args.time, [args.x, args.y], args.level
        )
    write_to_event_file(args.output, events, args.overwrite)
    log_info(f"Generate pedestrian events have been written to: {args.output}")


def read_events(file: pathlib.Path) -> List[Event]:
    """
    Reads from a file and creates a list of Events,
    the events are returned sorted in order of increasing timestamp.
    :param file: path to a json file containing events
    :return: List of Events from json file
    """
    events = []
    with open(file) as json_file:
        objs = json.load(json_file)
        for obj in objs:
            test = Event.from_json(json.dumps(obj))
            events.append(test)
    events.sort(key=lambda x: x.time)
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
    file: pathlib.Path, events: List[Event], overwrite: bool
) -> bool:
    """
    Writes the list of events to the given file. If overwrite is set, all events which
    are SpawnPedestrianEvents will be deleted.
    :param file: Output file
    :param events: List of SpawnPedestrianEvents
    :param overwrite: Existing SpawnPedestrianEvents will be overwritten
    :return: success
    """
    existing_events = read_events(file) if file.is_file() else []
    events = merge_spawn_pedestrian_events(events, existing_events, overwrite)

    with open(file, "w+") as json_file:
        json_file.write(json.dumps(events, indent=4, cls=DataclassJSONEncoder))

    return True
