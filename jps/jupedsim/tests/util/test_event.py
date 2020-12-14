from dataclasses import dataclass

import pytest
from jupedsim.tests.util.conftest import DummyEvent
from jupedsim.util.event import Event, EventType, SpawnPedestrianEvent


class TestEventType:
    @pytest.mark.parametrize(
        "event, json_str",
        [
            (
                SpawnPedestrianEvent([0, 0], 0),
                SpawnPedestrianEvent([0, 0], 0).get_json(),
            ),
            (
                SpawnPedestrianEvent([1.12, 56.5], 17),
                SpawnPedestrianEvent([1.12, 56.5], 17).get_json(),
            ),
            (
                SpawnPedestrianEvent([5.21, 0], 0),
                SpawnPedestrianEvent([5.21, 0], 0).get_json(),
            ),
            (
                SpawnPedestrianEvent([0, 1.5], 42),
                SpawnPedestrianEvent([0, 1.5], 42).get_json(),
            ),
            (
                SpawnPedestrianEvent([0, 1.5], 42),
                '{"type": "spawn_pedestrian", "position": [0, 1.5], "floor": 42}',
            ),
        ],
    )
    def test_from_json_correct(self, event, json_str):
        event_read = EventType.from_json(json_str)
        assert event == event_read

    @pytest.mark.parametrize(
        "json_str",
        [
            '{"type": "foo", "position": [0, 0], "floor": 0}',
            DummyEvent("test").get_json(),
        ],
    )
    def test_from_json_incorrect(self, json_str):
        with pytest.raises((ValueError, NotImplementedError)):
            EventType.from_json(json_str)


class TestSpawnPedestrianEvent:
    @pytest.mark.parametrize(
        "event, json_str",
        [
            (
                SpawnPedestrianEvent([0, 0], 0),
                SpawnPedestrianEvent([0, 0], 0).get_json(),
            ),
            (
                SpawnPedestrianEvent([0, 0], 1),
                SpawnPedestrianEvent([0, 0], 1).get_json(),
            ),
            (
                SpawnPedestrianEvent([0, 0], 1),
                '{"type": "spawn_pedestrian", "position": [0, 0], "floor": 1}',
            ),
            (
                SpawnPedestrianEvent([0, 0], 1),
                '{"type": "spawn_pedestrian", "position": [0, 0], "floor": 1, "test": [0, 0]}',
            ),
        ],
    )
    def test_from_json_correct(self, event, json_str):
        event_read = SpawnPedestrianEvent.from_json(json_str)
        assert event == event_read

    @pytest.mark.parametrize(
        "json_str",
        [
            (SpawnPedestrianEvent(["test", 0], 0).get_json()),
            (SpawnPedestrianEvent([0, 0], "floor").get_json()),
            (SpawnPedestrianEvent([0, 0, 0], 0).get_json()),
            (SpawnPedestrianEvent(0, 0).get_json()),
            '{"type": "spawn_pedestrian", "position": 0, "floor": 0}',
            '{"type": "spawn_pedestrian", "floor": 0}',
            '{"type": "spawn_pedestrian", "position": 0}',
            '{"type": "spawn_pedestrian", "position": 0, "floor": 0, "test": [0, 0]}',
            '{"type": }',
        ],
    )
    def test_from_json_incorrect(self, json_str):
        with pytest.raises(ValueError):
            SpawnPedestrianEvent.from_json(json_str)


class TestEvent:
    @pytest.mark.parametrize(
        "event, json_str",
        [
            (
                Event(0, SpawnPedestrianEvent([0, 0], 0)),
                Event(0, SpawnPedestrianEvent([0, 0], 0)).get_json(),
            ),
            (
                Event(0.5, SpawnPedestrianEvent([0.25, 0], 6)),
                Event(0.5, SpawnPedestrianEvent([0.25, 0], 6)).get_json(),
            ),
            (
                Event(0, SpawnPedestrianEvent([0, 0], 0)),
                '{"time": 0, "event": '
                '{"type": "spawn_pedestrian", "position": [0, 0], "floor": 0}, "test":"still_correct"}',
            ),
        ],
    )
    def test_from_json_correct(self, event, json_str):
        event_read = Event.from_json(json_str)
        assert event == event_read

    @pytest.mark.parametrize(
        "json_str",
        [
            Event(0.5, DummyEvent("test")).get_json(),
            '{"time": -1, "event": {"type": "spawn_pedestrian", "position": [0, 0], "floor": 0}}',
            '{"time": "test", "event": {"type": "spawn_pedestrian", "position": [0, 0], "floor": 0}}',
            '{"time": 0, "no_event": {"type": "spawn_pedestrian", "position": [0, 0], "floor": 0}}',
            '{"time": 0,',
        ],
    )
    def test_from_json_incorrect(self, json_str):
        with pytest.raises((ValueError, NotImplementedError)):
            Event.from_json(json_str)
