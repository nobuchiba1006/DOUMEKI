# submit jobs to condor

import os
import sys
import write_scripts

# parameters
params = sys.argv;
# datasetname, must be identical
dataset = params[1]
# nevts
nevts = params[2]
# nruns
nruns = params[3]
# input wavelength in nm
wavelen_nm = params[4]
# injection radius in m
injradius_m = params[5]
# injection height in m
injheight_m = params[6]
# mie scattering length in cm
miescatlen_cm = params[7]
# holeice radius in cm
holeicerad_cm = params[8]
# full base path to out data dir
baseoutdatadir = params[9]
# submithost. set cobalt or npx or osg
submithost = params[10]

ioptstart =  11

# flatten options
options = ""
for opt in params[ioptstart:] :
    options += "%s " % opt

#=============================================
# modify these parameters for your environment
username = "hoshina"
uid = 633 # for hoshina
#=============================================


# set dataset and outdir, macrodir
outdatadirname = "nevt%s_nruns%s_wl%snm_ir%sm_ih%sm_sl%scm_hr%scm"%(nevts, nruns, wavelen_nm, injradius_m, injheight_m, miescatlen_cm, holeicerad_cm)
outdatadir = "%s/%s"%(baseoutdatadir, outdatadirname)
if not os.path.exists(outdatadir):
    os.system("mkdir -p %s" % (outdatadir))

outmacrodir = "macros/gen"
if not os.path.exists(outmacrodir):
    os.system("mkdir -p %s" % (outmacrodir))

# make macro files. 
sys.path.append('../macros')
import MakeAcceptanceMacro as MakeMacro

datafilelist, macrofilelist = MakeMacro.GenerateAngleMacros(outdatadir,outmacrodir,float(wavelen_nm), float(injradius_m), float(injheight_m), int(nevts), int(nruns)) 

fmacro = open(macrofilelist, 'r')
macrolist = fmacro.readlines()
fdata = open(datafilelist, 'r')
datalist = fdata.readlines()

# copy analysis scripts
os.system("cp ../scripts/AnlAcceptance_megg.py %s"%(outdatadir))
os.system("cp ../scripts/draw_2D_megg.py %s"%(outdatadir))

# set condor.

#projectbase_RHEL7="/cvmfs/icecube.opensciencegrid.org/users/hoshina/RHEL7"
projectbase_RHEL7="/data/user/hoshina/DOMINANT/Doumeki"
project_RHEL7="build_doumeki"



runscript = "run_Doumeki_MEgg.py"

# create copyfiles
copyfiles = "run_Doumeki_MEgg.tgz"
os.system("rm %s" % (copyfiles))
os.system("tar -zcvf %s %s %s" % (copyfiles, runscript, outmacrodir))

# delete temporary macro files
os.system("rm -rf %s" %(outmacrodir))

subgendir= "%s" % (os.getenv("PWD"))
basedir = "/scratch/%s" % (username)

#filelistname = os.path.basename(filelist)
#filelistbase = filelistname.replace(".list","")
submitdir="%s/submit/%s" % (basedir, dataset)
gensubmitdir="%s/%s" % (subgendir, dataset)
os.system("rm -rf %s" % (submitdir))
os.system("mkdir -p %s" % (submitdir))
os.system("rm -rf %s" % (gensubmitdir))
os.system("mkdir -p %s" % (gensubmitdir))
print("submitdir %s generated" % (submitdir))

# dagman setup
dagfile="%s/%s.dag" % (submitdir, dataset)
gendagfile="%s/%s.dag" % (gensubmitdir, dataset)
dagconf="dagman.config"
fdag = open(gendagfile, "w")

# copy input files
os.system("cp -p %s %s %s" % (copyfiles, dagconf, gensubmitdir))

print("start forloop")

def gen_command(runscript, outfile, macroname, miescatlen, holeicerad, options) :

    if submithost == 'osg' and (os.path.exists(outfile)) :
        # file exists, that means it's done. skip the file.
        print("outfile %s exists. skip" % (outfile))

    else :
        outdirpath = os.path.dirname(outfile)
        print("outdirpath %s" % (outdirpath))
        if submithost != 'osg' and not os.path.exists(outdirpath):
            os.system("mkdir -p %s" % (outdirpath))
            os.system("chown -R %s:ice3simusr %s" % (username, outdirpath))

    command = "python %s -m %s -s %s -r %s %s" % (runscript, macroname, miescatlen, holeicerad, options)

    return command

#for i, macrofile in enumerate(macrolist) :
for i in range(len(macrolist)) :

    macrofile = macrolist[i].strip()
    datafile = datalist[i].strip()

    outdirpath = os.path.dirname(datafile)
    outdirurl = "gsiftp://%s"%(datafile)

    command = gen_command(runscript, datafile, macrofile, miescatlen_cm, holeicerad_cm, options)

    # write script
    if (command != "") :
        write_scripts.write_scripts(dataset, i, i, gensubmitdir, submitdir, submithost, uid, copyfiles, outdirurl, command, projectbase_RHEL7, project_RHEL7, fdag, username)

        # update count
        res = i% 100

        if (res == 100) :
            print("%d jobs done" % (res))


# submit
f3 = open("%s/run.sh" % (gensubmitdir), "w")
f3.write("condor_submit_dag -config %s/%s %s" % (submitdir, dagconf, dagfile))
f4 = open("%s/install.sh" % (gensubmitdir), "w")
f4.write("rm -rf %s\n" % (submitdir))
f4.write("cd ../\n")
f4.write("mv %s %s\n" % (gensubmitdir, submitdir))
'''
import shlex, subprocess
command = shlex.split("sh %s/run.sh" % (submitdir))
print command
p = subprocess.Popen(command)
'''
print("Done!")
