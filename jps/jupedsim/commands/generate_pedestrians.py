import pathlib
from argparse import ArgumentDefaultsHelpFormatter, ArgumentParser
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
            help="Either place a single or multiple agents.",
            formatter_class=ArgumentDefaultsHelpFormatter,
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
            "-level",
            required=False,
            type=int,
            metavar="level ID",
            default=0,
            help="ID of the level the pedestrian is generated according to the defined geometry",
        )
        sub_subparsers = parser.add_subparsers(dest='generate_mode')
        parser_single = sub_subparsers.add_parser(
            "single",
            help="Places an agent at a given position.",
            formatter_class=ArgumentDefaultsHelpFormatter,
        )
        parser_single.add_argument(
            "-x",
            required=True,
            type=float,
            metavar="x-pos",
            help="x-coordinate the pedestrian should be generated [m]",
        )
        parser_single.add_argument(
            "-y",
            required=True,
            type=float,
            metavar="y-pos",
            help="y-coordinate the pedestrian should be generated [m]",
        )
        parser_area = sub_subparsers.add_parser(
            "area",
            help="Places agents at a given area.",
            formatter_class=ArgumentDefaultsHelpFormatter,
        )
        parser_area.add_argument(
            "--area",
            required=True,
            type=points,
            metavar="point",
            help="Points that define an area(Polygon) where the pedestrans will spawn at, e.g. -p 1.1,2 3,4 ... [m]",
        )
        parser_area.add_argument(
            "-n",
            "--number_pedestrans",
            required=False,
            type=int,
            metavar="number of pedestrians",
            default=0,
            help="The number of pedestrians that should spawn",
        )
        parser_area.add_argument(
            "-dt",
            "--delta_t",
            required=False,
            type=float,
            default=0,
            metavar="time between spawn",
            help="The time between spawning pedestrians [s]",
        )
        parser_area.add_argument(
            "-pd",
            "--pedestrian_distance",
            required=True,
            type=float,
            metavar="distance between pedastrians",
            help="Minumum distance between two points [m]",
        )
        

    def execute(self, args):
        generate_spawn_events(args)
