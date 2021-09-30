

def MakeManyBeamOnMacro(nevts, nbunches) :

   outfname = "manybeamOn_%devt_%dbunch.g4mac"%(nevts, nbunches)

   with open(outfname, "w") as f:


       count = 0;

       for i in range(nbunches) :
           f.write("/jupiter/run/SetRunNumber %d\n" % (i))
           f.write("/run/beamOn %d\n"%(nevts))

       f.close()
          

MakeManyBeamOnMacro(100, 1000)
MakeManyBeamOnMacro(1000, 1000)
MakeManyBeamOnMacro(1000, 100)
MakeManyBeamOnMacro(10000, 10)
MakeManyBeamOnMacro(100000, 1)
