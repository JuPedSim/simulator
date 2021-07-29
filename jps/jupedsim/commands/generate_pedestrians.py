import pathlib
from argparse import ArgumentDefaultsHelpFormatter
from argparse import ArgumentTypeError
from jupedsim.util.generator import generate_spawn_events

def points(s):
    try:
        _points:list=[]
        _p_strings=list(s.split(' '))
        for _p_string in _p_strings:
            x,y=_p_string.split(',')
            x,y=float(x),float(y)
            _points.append([x,y])
        return _points
    except:
        raise ArgumentTypeError("Coordinates must be space seperated x,y points")

class GeneratePedestriansCommand:
    def __init__(self, subparsers):
        self.name = "generate-pedestrians"
        parser = subparsers.add_parser(
            self.name,
            help="Places an agent at a given position.",
            formatter_class=ArgumentDefaultsHelpFormatter,
        )
        parser.add_argument(
            "--area",
            required=False,
            type=points,
            metavar="point",
            help="Points that define an area(Polygon) where the pedestrans will spawn at, e.g. -p 1.1,2 3,4 [m]",
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
            required=False,
            type=float,
            metavar="x-pos",
            help="x-coordinate the pedestrian should be generated [m]",
        )
        parser.add_argument(
            "-y",
            required=False,
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
            "-n",
            "--number_pedestrans",
            required=False,
            type=int,
            metavar="number of pedestrians",
            default=0,
            help="The number of pedestrians that should spawn",
        )
        parser.add_argument(
            "-dt",
            "--delta_t",
            required=False,
            type=float,
            default=0,
            metavar="time between spawn",
            help="The time between spawning pedestrians [s]",
        )
        parser.add_argument(
            "-pd",
            "--pedestrian_distance",
            required=False,
            type=float,
            metavar="distance between pedastrians",
            help="Minumum distance between two points [m]",
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
