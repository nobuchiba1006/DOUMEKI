#-------------------------------------
# function to write condor scripts

import os
import os.path
import sys

def write_scripts(dataset, fileno, jobid, gensubmitdir, submitdir, submithost, uid, copyfiles, outdir, command, projectbase_RHEL7, project_RHEL7, fdag, username) :

    
    outbase = "%s_%s" % (dataset, fileno)
    shellname = "%s.sh" % (outbase)
    submitname = "%s.submit" % (outbase);
    print( "shellname", shellname)
    transfer_files = True
    if submithost == 'npx' :
        transfer_files = False

    workpath = "./"
    
    f1 = open("%s/%s" % (gensubmitdir, shellname), "w")
    text = "#!/bin/sh \n"
    text += "cat /etc/redhat-release\n"
    text += "gcc --version\n"
    text += "if [ -z $G4BUILD ] ; then \n"
    text += "    if expr `gcc -dumpversion` : '4.8.5' >/dev/null; then \n"
    text += "        echo 'RHEL7 with py2-v3'\n"
    text += "        eval `/cvmfs/icecube.opensciencegrid.org/py2-v3/setup.sh`\n"
    text += "        if [ ! -e %s%s ] ; then \n" % (workpath,project_RHEL7)
    text += '            echo "copying project %s"\n' % (project_RHEL7)
    text += "            cp %s/%s.tar.gz %s\n" % (projectbase_RHEL7, project_RHEL7, workpath)
    text += "            tar -zxf %s%s.tar.gz -C %s\n" % (workpath, project_RHEL7, workpath)
    text += "        fi \n" 
    text += "        BUILDDIR=%s%s\n" % (workpath, project_RHEL7)
    text += "    else \n" 
    text += "        echo 'system not supported'\n" 
    text += "    fi \n" 
    text += '    echo "BUILDDIR is $BUILDDIR"\n'
    text += "    tar -zxf %s -C $BUILDDIR\n" % (copyfiles)
    text += "    cd $BUILDDIR \n" 
    text += '    echo "PWD is $PWD"\n'
    text += "    source ./env.sh\n"
    text += "    %s\n" % (command)
    text += "else \n"
    text += "    tar -zxf %s -C $BUILDDIR\n" % (copyfiles)
    text += "    cd $BUILDDIR \n" 
    text += "    %s\n" % (command)
    text += "fi \n\n"

    f1.write(text)
    f1.close()
    
    os.system("chmod a+x %s/%s" % (gensubmitdir,shellname))
    
    f2 = open("%s/%s" % (gensubmitdir, submitname), "w")

    text =  "executable = %s/%s \n" % (submitdir, shellname)
    text += "error      = %s/%s.error \n" % (submitdir, outbase)
    text += "output     = %s/%s.out\n" % (submitdir, outbase)
    text += "log        = %s/%s.condorlog\n" % (submitdir, outbase)
    text += 'environment = "X509_USER_PROXY=x509up_u%d"\n' % (uid)
    text += 'transfer_input_files = %s \n' % (copyfiles)

    if transfer_files :
         text += 'output_destination = %s"\n' % (outdir)
         text += 'should_transfer_files = YES\n'

    text += """
request_cpus = 1
request_memory = 2GB
request_disk = 1GB
notification = Error
priority = 10
use_x509userproxy = true
notify_user = hoshina@icecube.wisc.edu
transfer_executable = true
when_to_transfer_output = ON_EXIT_OR_EVICT
periodic_remove = CumulativeSuspensionTime > ((RemoteWallClockTime - CumulativeSuspensionTime) / 2.0)
+SingularityImage="/cvmfs/singularity.opensciencegrid.org/opensciencegrid/osgvo-el7:latest"
+WantGlidein = True
+TransferOutput=""
queue
"""[1:]

    f2.write(text)
    f2.close()
    fdag.write("JOB %d %s/%s \n" % (jobid, submitdir, submitname))


