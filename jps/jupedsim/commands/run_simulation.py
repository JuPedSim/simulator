from collections import deque
from pathlib import Path

from jpscore import Simulation
from jpscore.geometry import Coordinate, LengthUnit, Level, Units
from jupedsim.IO.trajectorywriter import SimpleTrajectoryWriter
from jupedsim.IO.worldparser import WorldParser
from jupedsim.util.event import SpawnPedestrianEvent
from jupedsim.util.generator import read_events
from jupedsim.util.loghelper import log_debug, log_error, log_info
from jupedsim.util.simulation_files import SimulationFiles


class RunSimulationCommand:
    def __init__(self, subparsers):
        self.name = "run-simulation"
        parser = subparsers.add_parser(self.name, help="Will run a simulation")
        parser.add_argument(
            "--iterations",
            required=True,
            type=int,
            metavar="count",
            help="How many iterations to simulate",
        )
        parser.add_argument(
            "--path",
            type=Path,
            default=Path.cwd(),
            metavar="Path",
            help="Path to the simulation configuration directory",
        )

    def execute(self, args) -> int:
        self.args = args
        try:
            self.simulation_files = SimulationFiles(args.path)
        except FileNotFoundError as e:
            log_error(f"Error gathering required files: {e}")
            return 0
        self.simulation = Simulation()
        self.events = deque(read_events(self.simulation_files.events_json))
        dxf_parser = WorldParser(self.simulation_files.world_dxf)
        dxf_parser.parse(self.simulation.get_world())
        self.trajectory_writer = SimpleTrajectoryWriter

        self.trajectory_writer.write_header(
            self.simulation_files.trajctory_out
        )

        for iteration in range(args.iterations):
            log_info(f"Simulating iteration {iteration}")
            self._process_events(iteration)
            log_debug("Updating agents")
            self.simulation.compute_next_step()

            self.trajectory_writer.write_trajectory(
                self.simulation_files.trajctory_out,
                iteration,
                self.simulation.agents,
            )
        return 0

    def _process_events(self, current_iteration: int) -> None:
        log_debug("Processing events")
        while self.events and self.events[0].time <= current_iteration:
            event = self.events.popleft()
            log_info(f"{event}")
            if isinstance(event.event, SpawnPedestrianEvent):
                log_debug(
                    f"Adding agent to simulation at {event.event.position}"
                )
                # TODO (kkz) The SpawnPedestrianEvent should already contian jpscore.Coordinates.
                # It feels way to verbose to create them here
                self.simulation.add_agent(
                    Coordinate(
                        LengthUnit(event.event.position[0], Units.m),
                        LengthUnit(event.event.position[1], Units.m),
                        Level(event.event.level),
                    )
                )
