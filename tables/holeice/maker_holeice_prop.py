import numpy as np 
def make_matprop_holeice(avecos, scatlen) :

    outfilename = "matprop_holeice_" + str(avecos) + "_" + str(scatlen) + "cm.dat";

    ndata = 45 # fixed

    mieforward = (np.ones(ndata) * avecos).tolist()
    miebackward = mieforward
    mieratio  = (np.ones(ndata)).tolist()
    miescatlen = (np.ones(ndata) * scatlen).tolist()
   
    #Fixed --------------------------------------------
    wavelen = []
    for i in range(ndata) :
        wavelen.append(720 - i*10);

    #photon energy
    photonEholeice = [1.73, 1.77143, 1.7971, 1.82353, 1.85075,
	1.87879, 1.90769, 1.9375, 1.96825, 2,
	2.03279, 2.06667, 2.10169, 2.13793, 2.17544,
	2.21429, 2.25455, 2.2963, 2.33962, 2.38462,
	2.43137, 2.48, 2.53061, 2.58333, 2.6383,
	2.69565, 2.75556, 2.81818, 2.88372, 2.95238,
	3.02439, 3.1, 3.17949, 3.26316, 3.35135,
	3.44444, 3.54286, 3.64706, 3.75758, 3.875, 
	4, 4.13333, 4.27586, 4.42857, 4.59259]

    #phase index, icecube ice
    rindexholeice = [1.30815, 1.30803, 1.30797, 1.30797, 1.30802,
	1.30812, 1.30826, 1.30843, 1.30863, 1.30887,
	1.30912, 1.30939, 1.30969, 1.31, 1.31032,
	1.31067, 1.31102, 1.31139, 1.31178, 1.31218,
	1.3126, 1.31304, 1.3135, 1.314, 1.31452,
	1.31507, 1.31567, 1.31631, 1.31699, 1.31774,  
	1.31855, 1.31943, 1.32039, 1.32143, 1.32257,
	1.32381, 1.32517, 1.32665, 1.32827, 1.33003,
	1.33195, 1.33404, 1.33632, 1.33879, 1.34147]

    #icecube ice, homogeneous ice model
    abslenholeice = [1.53548, 1.75477, 2.01271, 2.31728, 2.67831,
	3.10791, 3.62113, 4.23659, 4.97741, 5.87229,
	6.95675, 8.2746, 9.87943, 11.836, 14.2211,
	17.1234, 20.6402, 24.8713, 29.9055, 35.8002,
	42.5523, 50.0649, 58.1194, 66.3693, 74.3702,
	81.65, 87.8004, 92.5553, 95.8262, 97.6856,
	98.3168, 97.9538, 96.8329, 95.1628, 93.1123,
	90.8086, 88.3431, 85.7786, 83.1565, 80.5033,
	77.8352, 75.162, 72.4893, 69.8202, 67.1563]
 

    tmp = [wavelen, photonEholeice, rindexholeice, abslenholeice, mieforward, miebackward, mieratio, miescatlen]

    table = np.array(tmp).transpose()

    header =  "format:waveLen[nm]_photonE[eV]_refIndex_absLength[m]_mieForward_mieBackward_mieRatio_miescatLen[cm]"
    
    np.savetxt(outfilename, table, header=header)


def make_matprop_holeice_files(holeicelist = "holeice.list") :

    with open(holeicelist) as f :  
        for line in f :
           avecos, scatlen = line.split()
           make_matprop_holeice(avecos, scatlen)
        

make_matprop_holeice(0.95, 0.05)
make_matprop_holeice(0.95, 0.1)
make_matprop_holeice(0.95, 0.25)
make_matprop_holeice(0.95, 0.5)
make_matprop_holeice(0.95, 0.75)
make_matprop_holeice(0.95, 1.0)
make_matprop_holeice(0.95, 1.25)
make_matprop_holeice(0.95, 1.5)
make_matprop_holeice(0.95, 1.75)
make_matprop_holeice(0.95, 2.0)
make_matprop_holeice(0.95, 2.25)
make_matprop_holeice(0.95, 2.5)
make_matprop_holeice(0.95, 2.75)
make_matprop_holeice(0.95, 3.0)
make_matprop_holeice(0.95, 3.25)
make_matprop_holeice(0.95, 3.5)
make_matprop_holeice(0.95, 3.75)
make_matprop_holeice(0.95, 5.0)
make_matprop_holeice(0.95, 6.0)
make_matprop_holeice(0.95, 7.5)
make_matprop_holeice(0.95, 10.0)
make_matprop_holeice(0.95, 15.0)
make_matprop_holeice(0.95, 25.0)
