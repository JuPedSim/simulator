import pathlib
from abc import ABCMeta, abstractclassmethod, abstractmethod
from string import Template
from typing import Dict, List

from jpscore import Agent
from jpscore.geometry import LengthUnit, Level, Units


class TrajectoryWriter(metaclass=ABCMeta):
    @abstractmethod
    def write_header(trajectory_file: pathlib.Path) -> None:
        """
        Opens the file and writes all needed header information in the `trajectory_file`. If the file contained any
        data it will be deleted.
        """
        raise NotImplementedError

    @abstractmethod
    def write_trajectory(
        trajectory_file, step: int, agents: List[Agent]
    ) -> None:
        """
        Appends the desired output for `step` to `trajectory_file`, the data written will be extracted from `agents`
        """
        raise NotImplementedError


class SimpleTrajectoryWriter(TrajectoryWriter):
    """
    First simple trajectory writer, output is a csv with spaces as delimiter. First line contains the information,
    what kind of data the specific column holds.

    Note: The z-coordinate is currently just the level information! This needs to be replaced when we have a proper
          mapping of (x,y)-position+level to the z position.

    Output is structured as follows (example):
    ------
    frame ID x y z
    0 1 0 0 2
    0 2 1 -1 0
    1 1 0.1 -0.1 2
    1 2 1 -1.1 0
    ....
    """

    header = "frame ID x y z\n"
    row_template = Template("$frame $id $x $y $z\n")

    def write_header(trajectory_file: pathlib.Path) -> None:
        with trajectory_file.open("w") as f:
            f.write(SimpleTrajectoryWriter.header)

    def write_trajectory(
        trajectory_file: pathlib.Path,
        step: int,
        agents_per_level: Dict[Level, Agent],
    ) -> None:
        with trajectory_file.open("a") as f:
            for lvl, agents in agents_per_level.items():
                for agent in agents:
                    row = SimpleTrajectoryWriter.row_template.substitute(
                        frame=step,
                        id=agent.id,
                        x=agent.pos.x.m,
                        y=agent.pos.y.m,
                        z=lvl.id,
                    )
                    f.write(row)
