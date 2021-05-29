import argparse
import logging

import jpscore
from jupedsim.commands.generate_pedestrians import GeneratePedestriansCommand
from jupedsim.commands.run_simulation import RunSimulationCommand
from jupedsim.util.loghelper import (
    log_native_debug,
    log_native_error,
    log_native_info,
    log_native_warning,
)


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
            level=jpscore.logging.Level.Error, func=log_native_error
        )
        jpscore.logging.set_callback(
            level=jpscore.logging.Level.Warning, func=log_native_warning
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
                level=jpscore.logging.Level.Info, func=log_native_info
            )
        if self.args.v >= 2:
            logging.getLogger(logger_name).setLevel(logging.DEBUG)
            # Only register the callback from C++ back to python
            # if the messages are actually consumed. Otherwise
            # we pay the overhead of calling into python and then
            # discarding the log message.
            jpscore.logging.set_callback(
                level=jpscore.logging.Level.Debug, func=log_native_debug
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
        command = GeneratePedestriansCommand(self.subparsers)
        self.commands[command.name] = command

    def setup_simulate_command(self):
        command = RunSimulationCommand(self.subparsers)
        self.commands[command.name] = command

    def parse_arguments(self):
        self.args = self.parser.parse_args()

    def run(self):
        self.parse_arguments()
        self.upgrade_logging()
        self.commands[self.args.cmd].execute(self.args)
