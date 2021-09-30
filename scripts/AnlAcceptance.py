"""
Data class for simulation used by dominant
"""

import numpy as np
import math as m
import os

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


def load_data(fname, nmoms = 2, npmts = 1) :

    totalnpmts = npmts * nmoms
    events = []
    isfilled = False

    ce_up = []
    ce_down = []

    with open(fname) as f :
        for line in f :
            vals = line.split()
            if vals[0] == '-99999999' :
                if isfilled :
                    datum.make_nparray()
                    ce_up.append(datum.total_CE_per_inside(0))
                    ce_down.append(datum.total_CE_per_inside(1))
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

    return events, np.array(ce_up), np.array(ce_down)
    


def analyze(filelist = "data.list") :

    ave_ceups = []
    ave_cedowns = []
    ave_ces = []
    ave_ceups_errs = []
    ave_cedowns_errs = []
    ave_ces_errs = []

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

            events, ce_up, ce_down = load_data(filename)
            totce = ce_up + ce_down

            # normalize
            section = radius**2 * m.pi
            ce_up = ce_up / (nevts / section)
            ce_down = ce_down / (nevts / section)
            totce = totce / (nevts / section)

            ave_ceup = np.average(ce_up)
            ave_cedown = np.average(ce_down)
            ave_ce = np.average(totce)

            ave_ceup_err = np.std(ce_up)/m.sqrt(nruns)
            ave_cedown_err = np.std(ce_down)/m.sqrt(nruns)
            ave_ce_err = np.std(totce)/m.sqrt(nruns)

            ave_ceups.append(ave_ceup)
            ave_cedowns.append(ave_cedown)
            ave_ces.append(ave_ce)
            ave_ceups_errs.append(ave_ceup_err)
            ave_cedowns_errs.append(ave_cedown_err)
            ave_ces_errs.append(ave_ce_err)


    f.close()
            
    # savefile        
    # format
    # zenith, wlens, ave
    cedata = [zeniths, wlens, ave_ceups, ave_ceups_errs, ave_cedowns, ave_cedowns_errs, ave_ces, ave_ces_errs]
    cedata = np.array(cedata)
    cedata = cedata.transpose()
    print(cedata)

    
    outfile = filelist.replace(".list", "_out.dat")
    with open(outfile, "w") as f_out :
        f_out.write("#zenith, wavelen, ave_ce_up, ave_ce_up_err, ave_ce_down, ave_ce_down_err, ave_ce, ave_ce_err\n")
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


