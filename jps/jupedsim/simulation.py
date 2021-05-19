from jupedsim.util.simulation_files import SimulationFiles
from jpscore import Simulation


def simulation_command(args):
    print("Not yet implemented")

    simulation_files = SimulationFiles(args.path)
    print("World: " + str(simulation_files.world_dxf))

    # Initialization
    # Parse Geometry
    # world_parser = WorldParser(simulation_files.world_dxf)
    # world_builder = world_parser.parse()
    #  Build World
    # world = world_builder.build()
    # Create Simulation Object
    simulation = Simulation(
        # world
    )
    # Simulation Loop
    # Loop over Timesteps
    # for cur_step in simulation.steps():
    # # loop
    # # jpscore.computeNextStep(simulation)

    # Finalization
