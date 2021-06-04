import pathlib
from argparse import ArgumentDefaultsHelpFormatter

from jupedsim.util.generator import generate_spawn_events


class GeneratePedestriansCommand:
    def __init__(self, subparsers):
        self.name = "generate-pedestrians"
        parser = subparsers.add_parser(
            self.name,
            help="Places an agent at a given position.",
            formatter_class=ArgumentDefaultsHelpFormatter,
        )
        parser.add_argument(
            "-t",
            "--time",
            required=False,
            type=float,
            metavar="time",
            default=0,
            help="Time the pedestrian should be generated [s]",
        )
        parser.add_argument(
            "-x",
            required=True,
            type=float,
            metavar="x-pos",
            help="x-coordinate the pedestrian should be generated [m]",
        )
        parser.add_argument(
            "-y",
            required=True,
            type=float,
            metavar="y-pos",
            help="y-coordinate the pedestrian should be generated [m]",
        )
        parser.add_argument(
            "-level",
            required=False,
            type=int,
            metavar="level ID",
            default=0,
            help="ID of the level the pedestrian is generated according to the defined geometry",
        )
        parser.add_argument(
            "-overwrite",
            required=False,
            help="Overwriting all existing spawn_pedestrian events in events file",
            action="store_true",
        )
        parser.add_argument(
            "-o",
            "--output",
            required=False,
            type=pathlib.Path,
            default=pathlib.Path.cwd() / "events.json",
            metavar="output file",
            help="Output file",
        )

    def execute(self, args):
        generate_spawn_events(args)
