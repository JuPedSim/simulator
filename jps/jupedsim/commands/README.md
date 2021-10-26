
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

## generate_pedestrians.py
A user can either run 'single' to spawn a pedestrian at a position or run 'area' which requires an area, that consists of multiple points forming a ploygon.

Within the polygon, sectors are calculated that ensure the minimum distance between the pedestrian and the wall or other pedestrians.

If all possible positions to spawn for pedestrians are used, the positions going to be reused. Spawn events can also be timed, with a delta time between the spawn events.

Example usage: 

```
jps generate-pedestrians -level=0 -t=0 -overwrite single -x=1.5 -y=2.6
```
or
```
jps generate-pedestrians -level=0 -t=3.1 -overwrite area -n=10 --delta_t=0.05 -pd=0.5 "--area=0,0 4.5,0 4.5,2.5 0,2.5" 
```

Note that e.g. level or t are more general than the arguments 'single' or 'area' and therefore must be written before the special cases.

### Visualisation examples of the area spawn points, sectors and polygon 
<div class="align-center">
  <img src="https://user-images.githubusercontent.com/74569620/127882636-12be0041-dc50-4510-ad52-689acf71960e.png" width="400">
  <img src="https://user-images.githubusercontent.com/74569620/127882959-6a017950-fdeb-4abc-aa42-ac0760ba6119.png" width="400">
</div>
