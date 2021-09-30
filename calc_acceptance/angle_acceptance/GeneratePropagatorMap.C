//*********************************************************************
//  GeneratePropagatorMap
//
//  The script generates QuickPropagatorMap.data for ROMEO.
//  input data file must be placed in kDirName = "data/" and 
//  the list of data file must be written in "input.list".
//  
//  Format of QuickPropagatorMap:
//
// Line 1:
//   NBinsXY xmin xmax ymin ymax NBinsZ zmin zmax [in m]
// Line 2:
//   -99999999(separator) input_filename  angle_of_injection
// Line 3: 
//   pos_x pos_y pos_z ibin NHits
//   (position [m]
// 
//
//*********************************************************************
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include "TUnixSystem.h"
#include "TStyle.h"
#include "TString.h"
#include "TCanvas.h"
#include "TView.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TPolyMarker3D.h"
#include "TPaveText.h"
#include "TMath.h"
#include "TF1.h"
#include "TLatex.h"
#include "TFile.h"
#include "TObjString.h"

using namespace std;

// radius of DOM
Double_t kR_dom    = 0.1651;  // [m]      
// radius of PMT
Double_t kR_pmt    = 0.1367;  // [m]    
// z-position of PMT origin. 0.02[m] is thickness of glass+gel
Double_t kPmt_z    = (kR_dom - 0.02 - kR_pmt); 
//Double_t kPmt_z    = (kR_dom - 0.015 - kR_pmt);  // 5mm gel
// max arch from cathode center to cathode edge
//Double_t kMax_dist = 0.1371; // [m]
Double_t kMax_dist = 0.14; // [m]
// opening angle from cathode center to cathode edge
Double_t theta     = (kMax_dist / kR_pmt); // [rad]
Double_t rcostheta = (kR_pmt * cos(theta));

// z-position of cathode edge
Double_t z_cut = (kPmt_z + rcostheta); // [m]
Double_t z_min = (z_cut - 0.01);
Double_t z_max = (kPmt_z + kR_pmt + 0.01);

const Int_t    kNbins = 56;
const Double_t kXmin  = -0.14; // m
const Double_t kXmax  = 0.14; // m
const Double_t kYmin  = -0.14; // m
const Double_t kYmax  = 0.14; // m
const Int_t    kNzbins = 16;
const Double_t kZmin  = z_min; // m
const Double_t kZmax  = z_max; // m

const TString  kDirName = "data/";

int GeneratePropagatorMap() {

   gSystem->Load("libPhysics.so");
   gStyle->SetOptStat(1);
   gStyle->SetOptFit(1);
   gStyle->SetPalette(1);
   gStyle->SetCanvasColor(10);
   gStyle->SetFrameFillColor(10);

   TFile file("RMOCalib.root", "recreate");
   
   // input file name list
   ifstream filelist("input.list");

   // output file
   ofstream out("QuickPhotonPropagatorMap.data");

   // output nbins , min, max of each axes
   out << kNbins << " " << kXmin << " " << kXmax << " " 
       << kNbins << " " << kYmin << " " << kYmax << " "
       << kNzbins << " " << kZmin << " " << kZmax << std::endl;

   // calculate bin width
   Double_t binwx = (kXmax - kXmin) / ((Double_t)kNbins);
   Double_t binwy = (kYmax - kYmin) / ((Double_t)kNbins);
   Double_t binwz = (kZmax - kZmin) / ((Double_t)kNzbins);

   TObjArray map3Darray;
   map3Darray.SetOwner();
   TString  anglename;
   TH3D    *hMap = 0;
   TString filename, name, topname;
   TString prefix, diameter, angle, wavelen, num_angle, last_num_angle;
   const TString separator("_");

   //
   // loop over all file list
   //
   while (filelist >> filename) {

      prefix = filename;
      prefix.ReplaceAll(kDirName, "");
      diameter = prefix;
      Ssiz_t index = prefix.Index(separator);
      prefix.Remove(index);
      cerr << "prefix  : " << prefix << endl;

      topname = prefix + separator;
      diameter.ReplaceAll(topname, "");
      angle = diameter;
      index = diameter.Index(separator);
      diameter.Remove(index);
      cerr << "diameter: " << diameter << endl;

      topname = diameter + separator;
      angle.ReplaceAll(topname, "");
      wavelen = angle;
      index = angle.Index(separator);
      angle.Remove(index);
      cerr << "angle   : " << angle << endl;
      last_num_angle = num_angle;
      num_angle = angle;
      num_angle.ReplaceAll("deg","");
      cerr << "numangle: " << num_angle << endl;
      

      topname = angle + separator;
      wavelen.ReplaceAll(topname, "");
      index = wavelen.Index(".");
      wavelen.Remove(index);
      cerr << "wavelen : " << wavelen << endl;

      if (anglename != angle) {

         // output old (angle) file!

         if (hMap) {
            out << "-99999999 " << name << " " << last_num_angle << std::endl;
      
            for (Int_t i=0; i<(kNbins); i++) {
               Double_t curx = kXmin + (i + 0.5) * binwx;      
               for (Int_t j=0; j<(kNbins); j++) {
                  Double_t cury = kYmin + (j + 0.5) * binwy;      
                  for (Int_t k=0; k<kNzbins; k++) {
                     Double_t curz = kZmin + (k + 0.5) * binwz;      

                     Int_t ibin = hMap->FindBin(curx, cury, curz);
                     Double_t content = hMap->GetBinContent(ibin); 
                     if (content != 0.) {
                        out << curx << " " << cury << " " << curz << " "
                            << ibin << " " << content << std::endl;
                     }
                  }
               }
            }
         }
  
         // create new histgram for next angle

         name = prefix + separator + diameter + separator + angle + separator + wavelen;
         cerr << "histname is " << name << endl;
         hMap = new TH3D(name, name, kNbins, kXmin, kXmax,
                                     kNbins, kYmin, kYmax,
                                     kNzbins, kZmin, kZmax);
         map3Darray.Add(hMap);
         anglename = angle;
      
      }
       

      TString inname(filename); 
      cerr << "input file name is " << inname << endl;
      ifstream in(inname.Data());
      if (!in) {
         cerr << "failed to open " << inname << endl;
         return 0;
      }

      //
      // Make sure that your data has two field on the top of data:
      // number of event per run and number of run
      //
      Double_t nevents, nruns;
      TString label;
      in >> label >> nevents >> label >> nruns;

      // read data

      Int_t    irun = -1;
      Double_t dum;
      Double_t dumy, dumz, dumene, dumtime;
      TString  run_separator;

      while (in >> dum) {
         
         if ( dum == -99999999) {
            // run separator!
            in >> run_separator;
            irun++;
            if (irun % 100 == 0) std::cerr << "current runno is " << irun << std::endl;
            if (irun > nruns + 2) break;

         } else {
            in >> dumy >> dumz >> dumene >> dumtime;
            dum /= 1000.;  // [mm] to [m]
            dumy /= 1000.;
            dumz /= 1000.;

            // very tmp treatment!!!
            // beam is injected from -Y direction... (T_T)          
            //Double_t xx = -dumy;
            //Double_t yy = dum;
            //Double_t zz = dumz;

            // problem fixed!
            Double_t xx = dum;
            Double_t yy = dumy;
            Double_t zz = dumz;

            if (zz > z_cut) { 
               hMap->Fill(xx, yy, zz);  
            }
         }
      } 

      in.close();
      in.clear();
   } 

   //
   // Don't forget to output last angle data...
   //
   if (hMap) {
      out << "-99999999 " << name << " " << num_angle << std::endl;

      for (Int_t i=0; i<(kNbins); i++) {
         Double_t curx = kXmin + (i + 0.5) * binwx;
         for (Int_t j=0; j<(kNbins); j++) {
            Double_t cury = kYmin + (j + 0.5) * binwy;
            for (Int_t k=0; k<kNzbins; k++) {
               Double_t curz = kZmin + (k + 0.5) * binwz;

               Int_t ibin = hMap->FindBin(curx, cury, curz);
               Double_t content = hMap->GetBinContent(ibin);
               if (content != 0.) {
                   out << curx << " " << cury << " " << curz << " "
                     << ibin << " " << content << std::endl;
               }
            }
         }
      }
   }

   // 
   // add prefix, diameter and wavelength information
   //

   out << "-11111111 " << prefix << " " << diameter << " " << angle << " " << wavelen << " " << separator << endl;

   out.close();
   out.clear();

   TObjString prefix_obj(prefix.Data());
   TObjString diameter_obj(diameter.Data());
   TObjString angle_obj(angle.Data());
   TObjString wavelen_obj(wavelen.Data());
   TObjString separator_obj(separator.Data());

   prefix_obj.Write("prefix");
   diameter_obj.Write("diameter");
   angle_obj.Write("angle");
   wavelen_obj.Write("wavelen");
   separator_obj.Write("separator");

   file.Write();    

   return 0;

}
