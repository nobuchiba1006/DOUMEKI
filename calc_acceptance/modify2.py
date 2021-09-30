#!/usr/bin/env python

import os,sys
                                                                                                                
fname = sys.argv[1]
outfname = fname + ".modified"

names = fname.split("_");
wavelen_buf = names[3].split("nm");
wavelen = wavelen_buf[0]
print wavelen

if (int(wavelen) < 315) :
        cmd1 = "echo nevt 1000 nrun 1000 > " + outfname;
else :
        #cmd1 = "echo nevt 100 nrun 1000 > " + outfname;
        cmd1 = "echo nevt 1000 nrun 1000 > " + outfname;

#print cmd1
os.system(cmd1)
cmd2 = "cat " + fname + " >> " + outfname;
#print cmd2
os.system(cmd2)

