# JPS commands

Each 'command' the jps tool provides could be in theory implemented as a
seperate command line tool. To improve usability however they are all
implemented as sub-commands. Each subcommand should be implemented in a
seperate python file in this sub folder.

A Command needs to adhere to the following structure:

* The command class needs to accept the 'action object' returned by
argparse.ArgumentParser.add\_subparsers() and populate this with any required
subcommand arguemts.

* The command class needs to provide a 'name' field which will be the name of the
command on the CLI.

* The command class needs to provide a 'execute' method which takes the 'args'
returned from argument parsing. Further the 'execute' method shall return an
integer that is directly returned to the OS to indicate succes (0) or error
(>0) to the caller of 'jps'

A command that is crated in the way outlined above can then be added to
'application.py' see 'setup\_simulate\_command' or
'setup\_generate\_pedestrians\_command' for details.

Please review the implementation of run\_simulation.py for more details.
