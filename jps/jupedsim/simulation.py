from jupedsim.util.simulation_files import SimulationFiles
from jpscore import Simulation


class SimulationWrapper:
    """SimulationWrapper contains the jpscore simulation and all required python objects for simulations"""

    def __init__(
        self, simulation_files: SimulationFiles, simulation: Simulation
    ):
        self.simulation_files = simulation_files
        self.simulation = simulation


def simulation_command(args):
    print("Not yet implemented")

    def initialize() -> SimulationWrapper:
        """Initializes the simulation and returns the simulation manager."""
        simulation_files = SimulationFiles(args.path)
        print("World: " + str(simulation_files.world_dxf))
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
        # Start by step 1 (simulation clock should return total number of steps)
        # simulation time before step should be (cur_step - 1) * step_length
        # for cur_step in range(1, simulation.clock.steps()):
        # # loop
        # # jpscore.computeNextStep(simulation)
        # # trajectory writer
        test = "asd"

    def finalize(sim: SimulationWrapper):
        # Clean up simulation
        print("test")

    sim = initialize()
    simulation_loop(sim)
    finalize(sim)
