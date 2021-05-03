import argparse
import logging
import sys
from pathlib import Path

import jpscore
from jupedsim.simulation import simulation_command
from jupedsim.util.generator import generate_spawn_events
from jupedsim.util.loghelper import log_debug, log_error, log_info, log_warning


class Application:
    def __init__(self):
        self.commands = {}
        self.setup_logging()
        self.setup_main_arg_parser()
        self.setup_generate_pedestrians_command()
        self.setup_simulate_command()

    def setup_logging(self):
        logging.basicConfig(format=logging.BASIC_FORMAT)
        jpscore.logging.set_callback(
            level=jpscore.logging.Level.Error, func=log_error
        )
        jpscore.logging.set_callback(
            level=jpscore.logging.Level.Warning, func=log_warning
        )

    def upgrade_logging(self):
        logger_name = "JuPedSim"
        if self.args.v >= 1:
            logging.getLogger(logger_name).setLevel(logging.INFO)
            # Only register the callback from C++ back to python
            # if the messages are actually consumed. Otherwise
            # we pay the overhead of calling into python and then
            # discarding the log message.
            jpscore.logging.set_callback(
                level=jpscore.logging.Level.Info, func=log_info
            )
        if self.args.v >= 2:
            logging.getLogger(logger_name).setLevel(logging.DEBUG)
            # Only register the callback from C++ back to python
            # if the messages are actually consumed. Otherwise
            # we pay the overhead of calling into python and then
            # discarding the log message.
            jpscore.logging.set_callback(
                level=jpscore.logging.Level.Debug, func=log_debug
            )
        if self.args.v >= 3:
            # Enables all log messages from 3rd party libraries
            logging.getLogger().setLevel(logging.DEBUG)

    def setup_main_arg_parser(self):
        self.parser = argparse.ArgumentParser()
        self.parser.add_argument(
            "-v",
            action="count",
            default=0,
            help="Set verbosity level, use -v for info messages, "
            "-vv for debug and -vvv for everything",
        )
        self.subparsers = self.parser.add_subparsers(
            title="command", dest="cmd", required=True
        )

    def setup_generate_pedestrians_command(self):
        command = "generate-pedestrians"
        parser = self.subparsers.add_parser(
            command,
            help="Places an agent at a given position.",
        )
        parser.add_argument(
            "-time",
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
            type=bool,
            metavar="overwrite",
            help="Overwriting all existing spawn_pedestrian events in events file",
            default=False,
        )
        parser.add_argument(
            "-o",
            required=True,
            type=str,
            metavar="output file",
            help="Output file",
        )

        self.commands[command] = generate_spawn_events

    def setup_simulate_command(self):
        command = "simulate"
        parser = self.subparsers.add_parser(
            command, help="Will run a simulation"
        )
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

        self.commands[command] = simulation_command

    def parse_arguments(self):
        self.args = self.parser.parse_args()

    def run(self):
        self.parse_arguments()
        self.upgrade_logging()

        # Example log messages
        log_info("hi")
        log_debug("hi")
        log_warning("hi")
        log_error("hi")
        # Example of a "3rd-party" log messages, i.e. a log message not
        # send to the 'JuPedSim' logger
        logging.debug("hi")
        return self.commands[self.args.cmd](self.args)
