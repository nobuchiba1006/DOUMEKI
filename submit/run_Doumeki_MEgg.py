#-------------------------
# options
#-------------------------

import sys
import os

from optparse import OptionParser
usage = "usage: %prog [options] inputfile"
parser = OptionParser(usage)

parser.add_option("-s","--miescatlen",dest="miescatlen",default="2.0",type="string", help="mie scattering length in cm as string")
parser.add_option("-r","--holeicerad",dest="holeicerad",default="6",type="string", help="hole ice bubble column radius in cm as string")
parser.add_option("-d","--execdir",dest="execdir",default=".",type="string", help="working directory")
parser.add_option("-m","--macroname",dest="macroname",default="",type="string",help="input macro name")

(options, args) = parser.parse_args(sys.argv)

command = "%s/doumeki_megg %s %s %s" % (options.execdir, options.macroname, options.miescatlen, options.holeicerad)

os.system(command)


