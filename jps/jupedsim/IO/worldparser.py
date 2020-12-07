import sys
import ezdxf

#TODO: object-oriented structure to get rid of global variable
#TODO: read in unit and convert data to mm

def readData(input_file):
    try:
        doc = ezdxf.readfile(input_file)
    except IOError:
        #TODO throw exception. file not found
    except ezdxf.DXFStructureError:
        #TODO throw exception. invalid dxf file.

    global msp
    msp = doc.modelspace()

def parseLevels():
    global msp

    #TODO: error if no level information
    #TODO: implement for several levels
    for line in msp.query('LINE[layer=="Level0"]'):
        #TODO: pybind
        #WorldBuilder.addBoundaryLine(int(level), [line.dxf.start, line.dxf.end])

def parseSpecialAreas():
    global msp

    #TODO: implement for several special area-layers
    #loop over lines, store: key=color, value=segment list [[[startX, startY],[endX, endY]], ...]

    color_to_segments={}

    for line in msp.query('LINE[layer=="Level0_SpecialAreas"]'):
        #create empty list for new color
        if line.dxf.color not in color_to_segments.keys():
            color_to_segments[line.dxf.color] = []

        #append segment to list
        #TODO: convert format of dxf.start/end
        color_to_segments[line.dxf.color].append([line.dxf.start, line.dxf.end])

    #add to world builder
    for color in color_to_segments:
        #TODO: pybind
        #WorldBuilder.addSpecialArea(int(color), color_to_segments[color])



