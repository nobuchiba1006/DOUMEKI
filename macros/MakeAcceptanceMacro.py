################################################################
# Generate macros for Wavelength Acceptance and Angle Acceptance
################################################################

import math as m
import os

outdatadir  = "data";
outmacrodir = "gen";

kMINWAVELENGTH = 280  # nm 
kMAXWAVELENGTH = 720  # nm
kMINANGLERANGE = 0    # deg
kMAXANGLERANGE = 180   # deg
kDANGLE        = 10    # delta angle, deg

def MakeAcceptanceMacro(outdatadir, outmacrodir, zenith, wavelen, radius_m, height_m,  nevts = 100, nruns = 1000, azimuth = 0) :
    """
    wavelen must be in [nm], zenith must be in [degree]
    """

    prefix = "eff_r%dm_h%dm"%(radius_m, height_m)
    outfname = "%s_%03ddeg_%03ddeg_%snm_%sevts_%sruns" % (prefix, zenith, azimuth, str(wavelen), str(nevts), str(nruns))

    outmacroname = "%s/%s.mac"%(outmacrodir, outfname)
    outdatname = "%s/%s.dat"%(outdatadir, outfname)

    with open(outmacroname, "w") as f: 
        f.write("/jupiter/generator CircleBeam\n")
        f.write("/jupiter/beam/circle/particle opticalphoton\n")
        f.write("/jupiter/beam/circle/radius " + str(radius_m) + " m\n")
        f.write("/jupiter/beam/circle/direction 0. 0. -1.\n")
        f.write("/jupiter/beam/circle/position 0. 0. 0. cm\n")
        f.write("/jupiter/run/SetFileOpenMode add\n")


        theta = zenith * m.pi / 180. # deg to rad
        phi = azimuth * m.pi / 180. 
        costheta = m.cos(theta)
        sintheta = m.sin(theta)

        x = height_m * sintheta * m.cos(phi)
        y = height_m * sintheta * m.sin(phi)
        z = height_m * costheta

        f.write("/jupiter/beam/circle/translation %f %f %f m\n" % (x, y, z))
        f.write("/jupiter/beam/circle/rotations 0 %f %f degree\n" % (zenith, azimuth))
        energy = 1.24e+3 / wavelen;
        f.write("/jupiter/beam/circle/energy %f eV\n" % (energy))
        f.write("/jupiter/run/SetHitFileName  %s\n" % (outdatname))

        #f.write("/run/beamOn 100\n")
        f.write("/jupiter/run/SetHeaderString nevt %d nrun %d\n" % (nevts, nruns))
        f.write("/control/execute macros/manybeamOn_%devt_%dbunch.g4mac\n" % (nevts, nruns))
        f.write("exit")

        f.close() 

        return outdatname, outmacroname



def GenerateWavelengthMacros(outdatadir, outmacrodir, zenith, azimuth, radius_m, height_m, nevts, nruns) :
    global kMINWAVELENGTH
    global kMAXWAVELENGTH

    if not os.path.exists(outmacrodir) :
        os.makedirs(outmacrodir)
    if not os.path.exists(outdatadir) :
        os.makedirs(outdatadir)
    datalist = open(outdatadir+"/data.list", "w")
    macrolist = open(outmacrodir+"/macros.list", "w")

    wavelen = kMINWAVELENGTH
    while (wavelen <= kMAXWAVELENGTH) :
        outdataname, outmacroname = MakeAcceptanceMacro(outdatadir, outmacrodir, zenith, wavelen, radius_m, height_m, nevts, nruns, azimuth)
        if (wavelen >= 300 and wavelen < 450) :
            wavelen += 5
        else :
            wavelen += 10
        datalist.write(outdataname+"\n")
        macrolist.write(outmacroname+"\n")
        
    datalist.close()  
    macrolist.close()


def GenerateAngleMacros(outdatadir, outmacrodir, wavelen, radius_m, height_m, nevts, nruns, mode="zenith", fixedzen=90) :
    global kDANGLE
    global kMINANGLERANGE
    global kMAXANGLERANGE

    zenith = kMINANGLERANGE
    azimuth = kMINANGLERANGE

    if not os.path.exists(outmacrodir) :
        os.makedirs(outmacrodir)
    if not os.path.exists(outdatadir) :
        os.makedirs(outdatadir)

    datalistname = outdatadir+"/data.list"
    datalist = open(datalistname, "w")
    macrolistname = outmacrodir+"/macros.list"
    macrolist = open(macrolistname, "w")

    if mode == "zenith" :
        while (zenith <= kMAXANGLERANGE) :
            outdataname, outmacroname = MakeAcceptanceMacro(outdatadir, outmacrodir, zenith, wavelen, radius_m, height_m, nevts, nruns, azimuth)
            zenith += kDANGLE
            datalist.write(outdataname+"\n")
            macrolist.write(outmacroname+"\n")
    else :
        while (azimuth <= kMAXANGLERANGE) :
            outdataname, outmacroname = MakeAcceptanceMacro(outdatadir, outmacrodir, fixedzen, wavelen, radius_m, height_m, nevts, nruns, azimuth)
            azimuth += kDANGLE
            datalist.write(outdataname+"\n")
            macrolist.write(outmacroname+"\n")
            
    datalist.close()  
    macrolist.close()
    return datalistname, macrolistname


#GenerateAngleMacros(400, 1, 1000, 100)
#GenerateAngleMacros(400, 1, 1, 10000, 10)
#GenerateAngleMacros(400, 1, 5, 10000, 10)
#GenerateAngleMacros(400, 1, 10, 10000, 10)
#GenerateAngleMacros(400, 1, 15, 10000, 10)


