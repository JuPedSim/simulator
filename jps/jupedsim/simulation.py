from jpscore import Simulation
from jupedsim.util.loghelper import log_debug
from jupedsim.util.simulation_files import SimulationFiles


class SimulationWrapper:
    """Contains the required jpscore and python objects for the simulation"""

    def __init__(
        self, simulation_files: SimulationFiles, simulation: Simulation
    ):
        self.simulation_files = simulation_files
        self.simulation = simulation


def simulation_command(args):
    def initialize() -> SimulationWrapper:
        """Initializes the simulation and returns the simulation wrapper."""
        simulation_files = SimulationFiles(args.path)
        log_debug("World: " + str(simulation_files.world_dxf))
        # Parse Geometry
        # world_parser = WorldParser(simulation_files.world_dxf)
        # world_builder = world_parser.parse()
        #  Build World
        # world = world_builder.build()
        # Create Simulation Object
        simulation = Simulation(
            # world
        )
        return SimulationWrapper(simulation_files, simulation)

    def simulation_loop(sim: SimulationWrapper):
        # Inner simulation loop
        # Loop over Timesteps
        # for cur_step in range(1, simulation.clock.steps()):
        # # loop
        # # jpscore.computeNextStep(simulation)
        # # trajectory writer
        pass

    def finalize(sim: SimulationWrapper):
        # Clean up simulation
        pass

    sim = initialize()
    simulation_loop(sim)
    finalize(sim)
