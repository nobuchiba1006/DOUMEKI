"""
Data class for simulation used by dominant
"""

import numpy as np
import math as m
import os
import sys

class Datum() :
    def __init__(self, livetime=0, atmfluxes=None, promptfluxes=None, astrofluxes=None) :

        self.thetas = []
        self.phis = []
        self.ces = []
        self.insideids = []
        self.pmtids = []

    def make_nparray(self) :
        self.thetas = np.array(self.thetas)
        self.phis = np.array(self.phis)
        self.ces = np.array(self.ces)
        self.insideids = np.array(self.insideids)
        self.pmtids = np.array(self.pmtids)

    def total_CE(self) :
        return sum(self.ces)

    def total_CE_per_uniqpmt(self, insideid, pmtid) :

        cut = (self.insideids == insideid) & (self.pmtids == pmtid)
        return sum(self.ces[cut])

    def total_CE_per_inside(self, insideid) :
        ''' 
        print "ces", self.ces
        print "ces insideid=0", self.ces[self.insideids == 0]
        print "ces insideid=1", self.ces[self.insideids == 1]
        ''' 
        return sum(self.ces[self.insideids == insideid])


def load_data(fname, nmoms = 2, npmts = 7) :

    totalnpmts = npmts * nmoms
    events = []
    isfilled = False

    ces = []

    with open(fname) as f :
        for line in f :
            vals = line.split()
            if vals[0] == '-99999999' :
                if isfilled :
                    datum.make_nparray()

                    ce = []
                    for i in range(nmoms) :
                        for j in range(npmts) :
                            ce.append(datum.total_CE_per_uniqpmt(i, j))
                    ces.append(ce)
                    events.append(datum)

                datum = Datum()
                isfilled = True

            else :
                #print(line)
                evtid, momID, myID, theta, phi, ce, label = line.split()
                datum.thetas.append(float(theta))
                datum.phis.append(float(phi))
                datum.ces.append(float(ce))
                datum.insideids.append(int(momID))
                datum.pmtids.append(int(myID))

    f.close()

    return events, np.array(ces)
    


def analyze(filelist = "data.list", nmoms=2, npmts=7) :

    ave_totce_array = []
    ave_ces_array = []
    ave_totce_errs_array = []
    ave_ces_errs_array = []

    zeniths = []
    wlens = []    

    with open(filelist) as f :
        for filename in f :
            filename = filename.replace("\n", "")
            filename = os.path.basename(filename)

            #extract info
            fn = filename.replace(".dat","")
            head, radius, height, zenith, wlen, nevts, nruns = fn.split("_")
            radius = radius.replace("m","")
            radius = float(radius.replace("r",""))
            height = height.replace("m","")
            height = float(height.replace("h",""))
            zenith = float(zenith.replace("deg",""))
            wlen = float(wlen.replace("nm",""))
            nevts = int(nevts.replace("evts",""))
            nruns = int(nruns.replace("runs",""))

            print(head, radius, zenith, wlen, nevts, nruns)
            zeniths.append(zenith)
            wlens.append(wlen)

            events, ces = load_data(filename, nmoms, npmts)
            totce = ces.sum(axis=1)

            # normalize
            section = radius**2 * m.pi
            ces = ces / (nevts / section)
            totce = totce / (nevts / section)

            #print(ces)
            #print(totce)

            ave_ces = np.average(ces, axis=0)
            ave_totce = np.average(totce)

            #print(ave_ces)
            #print(ave_totce)

            ave_ces_err = np.std(ces, axis=0)/m.sqrt(nruns)
            ave_totce_err = np.std(totce)/m.sqrt(nruns)

            #print(ave_ces_err)
            #print(ave_totce_err)

            ave_ces_array.append(ave_ces.tolist())
            ave_totce_array.append(ave_totce)
            ave_ces_errs_array.append(ave_ces_err.tolist())
            ave_totce_errs_array.append(ave_totce_err)


    f.close()
            
    # savefile        
    # format
    # zenith, wlens, ave

    ave_ces_array = np.array(ave_ces_array)
    ave_ces_array= ave_ces_array.transpose()
    ave_ces_errs_array = np.array(ave_ces_errs_array)
    ave_ces_errs_array= ave_ces_errs_array.transpose()
    
    #print("ave_ces_array   ", ave_ces_array)
    #print("ave_totce_array   ", ave_totce_array)

    cedata = [zeniths, wlens]
    #print("ave_ces_array   ", ave_ces_array)
    #print(np.array(ave_ces_array).shape)
    for i in range(int(nmoms*npmts)) :
        cedata.append(ave_ces_array[i].tolist())
        cedata.append(ave_ces_errs_array[i].tolist())
    cedata.append(ave_totce_array)
    cedata.append(ave_totce_errs_array)
    cedata = np.array(cedata)
    cedata = cedata.transpose()
    print("cedata   ", cedata)
    
    outfile = filelist.replace(".list", "_out.dat")
    with open(outfile, "w") as f_out :
        f_out.write("#zenith, wavelen, ave_ces_and_errs(ncolumn) , ave_totce, ave_totce_err\n")
    f_out.close()
    with open(outfile, "a") as f_out :
        np.savetxt(f_out, cedata)
    f_out.close()
    

#events, ce_up, ce_down = load_data("eff_30cm_0deg_400nm_100evts_1000runs.dat")
#events, ce_up, ce_down = load_data("eff_30cm_90deg_400nm_100evts_1000runs.dat")

#ave_ceup = ce_up.mean()
#ave_cedown = ce_down.mean()

#print ave_ceup
#print ave_cedown

analyze()


