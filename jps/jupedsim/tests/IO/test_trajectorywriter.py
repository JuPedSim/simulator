import re

import pytest
from jpscore import Agent, JPSGeometryException, Simulation
from jpscore.geometry import Coordinate, LengthUnit, Level, Units
from jupedsim.IO.trajectorywriter import (
    SimpleTrajectoryWriter,
    TrajectoryWriter,
)


def test_trajectorywriter_is_only_interface():
    file_path = "dummy"
    with pytest.raises(TypeError):
        can_not_instantiate = TrajectoryWriter()
    with pytest.raises(NotImplementedError):
        TrajectoryWriter.write_header(file_path)
    with pytest.raises(NotImplementedError):
        TrajectoryWriter.write_trajectory(file_path, 0, [])


def test_simpletrajectorywriter_writes_header_deletes_content_of_file(
    tmp_path,
):
    content_to_be_deleted = "This is some content which should be deleted\n"
    trajectory_txt = tmp_path / "trajectory.txt"
    with trajectory_txt.open("w") as f:
        f.write(content_to_be_deleted)

    SimpleTrajectoryWriter.write_header(trajectory_txt)

    with trajectory_txt.open("r") as f:
        lines = f.readlines()
        assert len(lines) == 1
        assert not content_to_be_deleted in lines[0]


def test_simpletrajectorywriter_writes_header(tmp_path):
    trajectory_txt = tmp_path / "trajectory.txt"

    SimpleTrajectoryWriter.write_header(trajectory_txt)

    with trajectory_txt.open("r") as f:
        lines = f.readlines()
        assert len(lines) == 1
        assert lines[0] == "frame ID x y z\n"


@pytest.mark.parametrize(
    "agents",
    [
        {},
        {
            Level(0): [
                Agent(
                    Coordinate(
                        LengthUnit(0.1, Units.m), LengthUnit(0, Units.m)
                    )
                ),
                Agent(
                    Coordinate(
                        LengthUnit(21, Units.m), LengthUnit(12, Units.m)
                    )
                ),
            ],
        },
        {
            Level(0): [
                Agent(
                    Coordinate(
                        LengthUnit(0.1, Units.m), LengthUnit(0, Units.m)
                    )
                ),
                Agent(
                    Coordinate(
                        LengthUnit(21, Units.m), LengthUnit(12, Units.m)
                    )
                ),
            ],
            Level(5): [
                Agent(
                    Coordinate(
                        LengthUnit(0.1, Units.m), LengthUnit(4, Units.m)
                    )
                ),
                Agent(
                    Coordinate(LengthUnit(6, Units.m), LengthUnit(1, Units.m))
                ),
                Agent(
                    Coordinate(
                        LengthUnit(43, Units.m), LengthUnit(12, Units.m)
                    )
                ),
            ],
        },
    ],
)
def test_simpletrajectorywriter_writes_trajectories(tmp_path, agents):
    trajectory_txt = tmp_path / "trajectory.txt"

    SimpleTrajectoryWriter.write_trajectory(trajectory_txt, 0, agents)

    num_agents = sum(len(v) for v in agents.values())
    with trajectory_txt.open("r") as f:
        lines = f.readlines()
        assert len(lines) == num_agents
        for line in lines:
            columns = re.split("\s+", line.rstrip())
            assert len(columns) == 5


@pytest.mark.parametrize(
    "agents",
    [
        {},
        {
            Level(0): [
                Agent(
                    Coordinate(
                        LengthUnit(0.1, Units.m), LengthUnit(0, Units.m)
                    )
                ),
                Agent(
                    Coordinate(
                        LengthUnit(21, Units.m), LengthUnit(12, Units.m)
                    )
                ),
            ],
        },
        {
            Level(0): [
                Agent(
                    Coordinate(
                        LengthUnit(0.1, Units.m), LengthUnit(0, Units.m)
                    )
                ),
                Agent(
                    Coordinate(
                        LengthUnit(21, Units.m), LengthUnit(12, Units.m)
                    )
                ),
            ],
            Level(5): [
                Agent(
                    Coordinate(
                        LengthUnit(0.1, Units.m), LengthUnit(4, Units.m)
                    )
                ),
                Agent(
                    Coordinate(LengthUnit(6, Units.m), LengthUnit(1, Units.m))
                ),
                Agent(
                    Coordinate(
                        LengthUnit(43, Units.m), LengthUnit(12, Units.m)
                    )
                ),
            ],
        },
    ],
)
def test_simpletrajectorywriter_writes_complete_trajectories(tmp_path, agents):
    max_iteratrions = 10
    trajectory_txt = tmp_path / "trajectory.txt"

    num_agents = sum(len(v) for v in agents.values())
    num_lines = num_agents * max_iteratrions + 1  # +1 for header line
    SimpleTrajectoryWriter.write_header(trajectory_txt)
    for i in range(max_iteratrions):
        SimpleTrajectoryWriter.write_trajectory(trajectory_txt, i, agents)

    with trajectory_txt.open("r") as f:
        lines = f.readlines()
        assert len(lines) == num_lines
        for line in lines:
            columns = re.split("\s+", line.rstrip())
            assert len(columns) == 5
