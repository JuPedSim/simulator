import json
from typing import List

import pytest
from jupedsim.tests.util.conftest import DummyEvent, equal_ignore_order
from jupedsim.util.event import (
    DataclassJSONEncoder,
    Event,
    SpawnPedestrianEvent,
)
from jupedsim.util.generator import (
    generate_pedestrian_on_position,
    merge_spawn_pedestrian_events,
    read_events,
)


class TestGenerator:
    @pytest.mark.parametrize(
        "filename, events, exception",
        [
            ("", [], FileNotFoundError),
            (
                "read_events_incorrect.json",
                [
                    Event(0, SpawnPedestrianEvent([1, -5], 1)),
                    Event(1, DummyEvent("dummy")),
                ],
                NotImplementedError,
            ),
            (
                "read_events_incorrect.json",
                [Event(-1, SpawnPedestrianEvent([1, -5], 1))],
                ValueError,
            ),
        ],
    )
    def test_read_events_incorrect(
        self, tmpdir, filename, events: List[Event], exception
    ):
        foo = SpawnPedestrianEvent([0, 0], 1)
        if not filename:
            file = filename
        else:
            file = tmpdir / filename
            file.write(json.dumps(events, indent=4, cls=DataclassJSONEncoder))

        with pytest.raises(exception):
            read_events(file)

    @pytest.mark.parametrize(
        "events",
        (
            [],
            [
                Event(0, SpawnPedestrianEvent([1, -5], 1)),
                Event(30, SpawnPedestrianEvent([11, 5], -1)),
                Event(432, SpawnPedestrianEvent([-12, -5], 0)),
                Event(123, SpawnPedestrianEvent([21, -5], 1)),
            ],
        ),
    )
    def test_read_events_correct(self, tmpdir, events: List[Event]):
        file = tmpdir / "read_events_correct.json"
        file.write(json.dumps(events, indent=4, cls=DataclassJSONEncoder))
        result = read_events(file)
        assert events == result

    @pytest.mark.parametrize(
        "event",
        [
            Event(0, SpawnPedestrianEvent([0, 0], 1)),
            Event(50, SpawnPedestrianEvent([6, -34], -1)),
            Event(123, SpawnPedestrianEvent([-1221, 435], 2)),
            Event(56123, SpawnPedestrianEvent([12, 85], 4)),
        ],
    )
    def test_generate_pedestrian_position(self, event: Event):
        generated_ped = generate_pedestrian_on_position(
            event.time, event.event.position, event.event.floor
        )
        assert len(generated_ped) == 1
        assert generated_ped[0] == event

    @pytest.mark.parametrize(
        "events, existing_events, expected",
        [
            (
                [],
                [],
                [],
            ),
            (
                [],
                [
                    Event(0, SpawnPedestrianEvent([1, -5], 1)),
                    Event(30, SpawnPedestrianEvent([11, 5], -1)),
                    Event(432, SpawnPedestrianEvent([-12, -5], 0)),
                    Event(123, SpawnPedestrianEvent([21, -5], 1)),
                ],
                [],
            ),
            (
                [
                    Event(0, SpawnPedestrianEvent([1, -5], 1)),
                    Event(30, SpawnPedestrianEvent([11, 5], -1)),
                    Event(432, SpawnPedestrianEvent([-12, -5], 0)),
                    Event(123, SpawnPedestrianEvent([21, -5], 1)),
                ],
                [],
                [
                    Event(0, SpawnPedestrianEvent([1, -5], 1)),
                    Event(30, SpawnPedestrianEvent([11, 5], -1)),
                    Event(432, SpawnPedestrianEvent([-12, -5], 0)),
                    Event(123, SpawnPedestrianEvent([21, -5], 1)),
                ],
            ),
            (
                [],
                [
                    Event(0, DummyEvent("dummy")),
                ],
                [
                    Event(0, DummyEvent("dummy")),
                ],
            ),
            (
                [],
                [
                    Event(0, SpawnPedestrianEvent([1, -5], 1)),
                    Event(30, SpawnPedestrianEvent([11, 5], -1)),
                    Event(432, SpawnPedestrianEvent([-12, -5], 0)),
                    Event(4123, DummyEvent("dummy")),
                    Event(123, SpawnPedestrianEvent([21, -5], 1)),
                    Event(0, DummyEvent("dummy")),
                ],
                [
                    Event(0, DummyEvent("dummy")),
                    Event(4123, DummyEvent("dummy")),
                ],
            ),
            (
                [
                    Event(0, SpawnPedestrianEvent([1, -5], 1)),
                    Event(30, SpawnPedestrianEvent([11, 5], -1)),
                    Event(432, SpawnPedestrianEvent([-12, -5], 0)),
                    Event(123, SpawnPedestrianEvent([21, -5], 1)),
                ],
                [
                    Event(0, SpawnPedestrianEvent([56, 11], 1)),
                    Event(23, SpawnPedestrianEvent([123, 7], -1)),
                    Event(98, SpawnPedestrianEvent([-678, 12], 0)),
                    Event(4123, DummyEvent("dummy")),
                    Event(672, SpawnPedestrianEvent([-20, -5], 1)),
                    Event(0, DummyEvent("dummy")),
                ],
                [
                    Event(0, SpawnPedestrianEvent([1, -5], 1)),
                    Event(30, SpawnPedestrianEvent([11, 5], -1)),
                    Event(432, SpawnPedestrianEvent([-12, -5], 0)),
                    Event(123, SpawnPedestrianEvent([21, -5], 1)),
                    Event(4123, DummyEvent("dummy")),
                    Event(0, DummyEvent("dummy")),
                ],
            ),
        ],
    )
    def test_merge_spawn_pedestrian_events_overwrite(
        self,
        events: List[Event],
        existing_events: List[Event],
        expected: List[Event],
    ):
        merged_events = merge_spawn_pedestrian_events(
            events, existing_events, True
        )
        assert equal_ignore_order(merged_events, expected)

    @pytest.mark.parametrize(
        "events, existing_events, expected",
        [
            (
                [],
                [],
                [],
            ),
            (
                [],
                [
                    Event(0, SpawnPedestrianEvent([1, -5], 1)),
                    Event(30, SpawnPedestrianEvent([11, 5], -1)),
                    Event(432, SpawnPedestrianEvent([-12, -5], 0)),
                    Event(123, SpawnPedestrianEvent([21, -5], 1)),
                ],
                [
                    Event(0, SpawnPedestrianEvent([1, -5], 1)),
                    Event(30, SpawnPedestrianEvent([11, 5], -1)),
                    Event(432, SpawnPedestrianEvent([-12, -5], 0)),
                    Event(123, SpawnPedestrianEvent([21, -5], 1)),
                ],
            ),
            (
                [
                    Event(0, SpawnPedestrianEvent([1, -5], 1)),
                    Event(30, SpawnPedestrianEvent([11, 5], -1)),
                    Event(432, SpawnPedestrianEvent([-12, -5], 0)),
                    Event(123, SpawnPedestrianEvent([21, -5], 1)),
                ],
                [],
                [
                    Event(0, SpawnPedestrianEvent([1, -5], 1)),
                    Event(30, SpawnPedestrianEvent([11, 5], -1)),
                    Event(432, SpawnPedestrianEvent([-12, -5], 0)),
                    Event(123, SpawnPedestrianEvent([21, -5], 1)),
                ],
            ),
            (
                [],
                [
                    Event(0, DummyEvent("dummy")),
                    Event(123, DummyEvent("dummy")),
                ],
                [
                    Event(0, DummyEvent("dummy")),
                    Event(123, DummyEvent("dummy")),
                ],
            ),
            (
                [],
                [
                    Event(0, SpawnPedestrianEvent([1, -5], 1)),
                    Event(30, SpawnPedestrianEvent([11, 5], -1)),
                    Event(432, SpawnPedestrianEvent([-12, -5], 0)),
                    Event(123, SpawnPedestrianEvent([21, -5], 1)),
                    Event(0, DummyEvent("dummy")),
                    Event(123, DummyEvent("dummy")),
                ],
                [
                    Event(0, DummyEvent("dummy")),
                    Event(123, DummyEvent("dummy")),
                    Event(0, SpawnPedestrianEvent([1, -5], 1)),
                    Event(30, SpawnPedestrianEvent([11, 5], -1)),
                    Event(432, SpawnPedestrianEvent([-12, -5], 0)),
                    Event(123, SpawnPedestrianEvent([21, -5], 1)),
                ],
            ),
            (
                [
                    Event(0, SpawnPedestrianEvent([1, -5], 1)),
                    Event(30, SpawnPedestrianEvent([11, 5], -1)),
                    Event(432, SpawnPedestrianEvent([-12, -5], 0)),
                    Event(123, SpawnPedestrianEvent([21, -5], 1)),
                ],
                [
                    Event(0, DummyEvent("dummy")),
                    Event(123, DummyEvent("dummy")),
                ],
                [
                    Event(0, SpawnPedestrianEvent([1, -5], 1)),
                    Event(30, SpawnPedestrianEvent([11, 5], -1)),
                    Event(432, SpawnPedestrianEvent([-12, -5], 0)),
                    Event(123, SpawnPedestrianEvent([21, -5], 1)),
                    Event(0, DummyEvent("dummy")),
                    Event(123, DummyEvent("dummy")),
                ],
            ),
            (
                [
                    Event(0, SpawnPedestrianEvent([1, -5], 1)),
                    Event(30, SpawnPedestrianEvent([11, 5], -1)),
                    Event(432, SpawnPedestrianEvent([-12, -5], 0)),
                    Event(123, SpawnPedestrianEvent([21, -5], 1)),
                    Event(123, SpawnPedestrianEvent([21, -5], 1)),
                ],
                [
                    Event(0, DummyEvent("dummy")),
                    Event(0, SpawnPedestrianEvent([23, -5], 4)),
                    Event(43, SpawnPedestrianEvent([96, 5], -1)),
                    Event(123, DummyEvent("dummy")),
                    Event(512, SpawnPedestrianEvent([8, -45], 1)),
                ],
                [
                    Event(0, SpawnPedestrianEvent([1, -5], 1)),
                    Event(30, SpawnPedestrianEvent([11, 5], -1)),
                    Event(432, SpawnPedestrianEvent([-12, -5], 0)),
                    Event(123, SpawnPedestrianEvent([21, -5], 1)),
                    Event(123, SpawnPedestrianEvent([21, -5], 1)),
                    Event(0, DummyEvent("dummy")),
                    Event(0, SpawnPedestrianEvent([23, -5], 4)),
                    Event(43, SpawnPedestrianEvent([96, 5], -1)),
                    Event(123, DummyEvent("dummy")),
                    Event(512, SpawnPedestrianEvent([8, -45], 1)),
                ],
            ),
        ],
    )
    def test_merge_spawn_pedestrian_events_non_overwrite(
        self,
        events: List[Event],
        existing_events: List[Event],
        expected: List[Event],
    ):
        merged_events = merge_spawn_pedestrian_events(
            events, existing_events, False
        )
        assert equal_ignore_order(merged_events, expected)
