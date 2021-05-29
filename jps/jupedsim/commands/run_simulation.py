from pathlib import Path

from jpscore import Simulation
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
        for iteration in range(args.iterations):
            log_info(f"Simulating iteration {iteration}")
            log_debug("Processing events")
            self.process_events()
            log_debug("Updating agents")
            self.simulation.compute_next_step()
        return 0

    def process_events(self) -> None:
        # TODO
        pass
