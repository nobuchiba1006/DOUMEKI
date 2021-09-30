#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>

using namespace std;

int main (int argc, char *argv[]) {

  string str_avecos, str_scatlen;
  //  str_avecos = argv[1];
  //  str_scatlen = argv[2];

  ifstream in("holeice.list");
  while (in) {
    in >> str_avecos >> str_scatlen;
    double avecos, scatlen;
    avecos = stod(str_avecos);
    scatlen = stod(str_scatlen);

    string outfilename = "matprop_holeice_" + str_avecos + "_" + str_scatlen + "cm.dat";
    ofstream out(outfilename);

    out << "format:waveLen[nm]_photonE[eV]_refIndex_absLength[m]_mieForward_mieBackward_mieRatio_miescatLen[cm]" << endl;

    double mieforward[45], miebackward[45], mieratio[45], miescatlen[45];
    for (int i = 0; i < 45; i++){
      mieforward[i] = avecos;
      miebackward[i] = avecos;
      mieratio[i] = 1;
      miescatlen[i] = scatlen;
    }

    // Fixed --------------------------------------------
    double wavelen[45];
    for (int i = 0; i < 45; i++) wavelen[i] = 720 - i*10;
    double photonEholeice[45] =
      { 1.73, 1.77143, 1.7971, 1.82353, 1.85075,
	1.87879, 1.90769, 1.9375, 1.96825, 2,
	2.03279, 2.06667, 2.10169, 2.13793, 2.17544,
	2.21429, 2.25455, 2.2963, 2.33962, 2.38462,
	2.43137, 2.48, 2.53061, 2.58333, 2.6383,
	2.69565, 2.75556, 2.81818, 2.88372, 2.95238,
	3.02439, 3.1, 3.17949, 3.26316, 3.35135,
	3.44444, 3.54286, 3.64706, 3.75758, 3.875, 
	4, 4.13333, 4.27586, 4.42857, 4.59259 };
    // phase index, icecube ice
    double rindexholeice[45] =
      { 1.30815, 1.30803, 1.30797, 1.30797, 1.30802,
	1.30812, 1.30826, 1.30843, 1.30863, 1.30887,
	1.30912, 1.30939, 1.30969, 1.31, 1.31032,
	1.31067, 1.31102, 1.31139, 1.31178, 1.31218,
	1.3126, 1.31304, 1.3135, 1.314, 1.31452,
	1.31507, 1.31567, 1.31631, 1.31699, 1.31774,  
	1.31855, 1.31943, 1.32039, 1.32143, 1.32257,
	1.32381, 1.32517, 1.32665, 1.32827, 1.33003,
	1.33195, 1.33404, 1.33632, 1.33879, 1.34147 };
    // icecube ice, homogeneous ice model
    double abslenholeice[45] =
      { 1.53548, 1.75477, 2.01271, 2.31728, 2.67831,
	3.10791, 3.62113, 4.23659, 4.97741, 5.87229,
	6.95675, 8.2746, 9.87943, 11.836, 14.2211,
	17.1234, 20.6402, 24.8713, 29.9055, 35.8002,
	42.5523, 50.0649, 58.1194, 66.3693, 74.3702,
	81.65, 87.8004, 92.5553, 95.8262, 97.6856,
	98.3168, 97.9538, 96.8329, 95.1628, 93.1123,
	90.8086, 88.3431, 85.7786, 83.1565, 80.5033,
	77.8352, 75.162, 72.4893, 69.8202, 67.1563 };
    
    for (int i = 0; i < 45; i++) {
      out << wavelen[i] << " " << photonEholeice[i] << " " 
	  << rindexholeice[i] << " " << abslenholeice[i] << " "
	  << mieforward[i] << " " << miebackward[i] << " " 
	  << mieratio[i] << " " << miescatlen[i] << endl;
    }
    out.close();
  }
}
