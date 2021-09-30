//*********************************************************************
//  GenerateSurvivingCurve
// 
//  The script generates wavelength_acceptance.data for ROMEO.
//  input data file must be placed in kDirName = "data/" and 
//  the list of data file must be written in "input.list".
//
//*********************************************************************

#include <stdlib.h>
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


Double_t Poisson(Double_t *x, Double_t *par)
{
   Double_t xx   = x[0];
   Double_t cnst = par[0];
   Double_t mu   = par[1];
   return (cnst * TMath::PoissonI(xx, mu));
   //return (cnst * TMath::Poisson(xx, mu));
}

Double_t Binominal(Double_t *x, Double_t *par)
{
   Int_t    xx      = (Int_t)x[0];
   Int_t    nevents = (Int_t)par[0];
   Double_t cnst    = par[1];
   Double_t mu      = par[2];
   Double_t prop    = mu / nevents;
   Double_t subprop = 1 - prop;
   Double_t prod = 1;
 
   for (Int_t i=1; i<xx; i++) {
      //prod *= (1 - (i - 1) / nevents);
      prod *= (nevents - i + 1);
   }
   prod /= TMath::Power(nevents, xx);

   //Bool_t islite = kTRUE;
   Bool_t islite = kFALSE;
   Double_t cur;

   if (islite) {
      cur =  (cnst * TMath::Power(mu, xx) / TMath::Factorial(xx)
                * TMath::Power(subprop, nevents - xx) * prod);
   } else {
      cur = (cnst * TMath::Factorial(nevents) / TMath::Factorial(nevents - xx)
            / TMath::Factorial(xx) * TMath::Power(prop, xx) 
             * TMath::Power(subprop, nevents - xx));   
   }
   return cur;
}

const Double_t kPoissonLimit  = 10.;
const TString  kDirName = "data/";
const TString  kOUTFILENAME = "penet.data";

int GenerateSurvivingCurve() {

   gSystem->Load("libPhysics.so");
   gStyle->SetOptStat(1);
   gStyle->SetOptFit(1);
   gStyle->SetPalette(1);
   gStyle->SetCanvasColor(10);
   gStyle->SetFrameFillColor(10);

   ifstream filelist("input.list");
   ofstream out(kOUTFILENAME);

   TObjArray map3Darray;
   TObjArray survarray;
   TCanvas *c2 = 0;
   TF1 *gauss = 0;
   TF1 *poisson = 0;

   TString filename, topname;
   TString prefix, diameter, angle, wavelen, num_angle, last_num_angle, num_wavelen;
   const TString separator = "_";

   TFile *file = new TFile("penet.root","recreate");

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
      num_wavelen = wavelen;
      num_wavelen.ReplaceAll("nm","");
      cerr << "num_wavelen: " << num_wavelen << endl;


      // open input stream

      ifstream in(filename.Data());
      if (!in) {
         cerr << "file open faild!" << endl;
         return 0;
      }

      // create 1d hist
      TString name = prefix + separator + diameter + separator + angle + separator + wavelen;
   
      TH1D *hSurvived;
      Int_t i_wavelen = atoi(num_wavelen.Data());
      cerr << "i_wavelen = " << i_wavelen << endl;
      //if (i_wavelen <= 310) {
      if (i_wavelen <= 305) {
         hSurvived = new TH1D(name, name, 30, 0., 30);
      } else {
         hSurvived = new TH1D(name, name, 120, 0., 120);
      }
      survarray.Add(hSurvived);

      // read data

      Int_t    irun = -1;
      Int_t    nsurvived = -1;
      Double_t dum;
      Double_t dumy, dumz, dumene, dumtime;
      TString  dum_separator;

      Double_t nevents, nruns;
      TString label;
      in >> label >> nevents >> label >> nruns;

      while (in >> dum) {
         
         if ( dum == -99999999) {
            // run separator!
            in >> dum_separator;
            irun++;
            if (nsurvived != -1)  hSurvived->Fill(nsurvived);
            nsurvived = 0; 

            if (irun % 100 == 0) std::cerr << "current runno is " << irun << std::endl;
            //if (irun > nruns + 2) break;

         } else {
            in >> dumy >> dumz >> dumene >> dumtime;
            dum /= 1000.;  // [mm] to [m]
            dumy /= 1000.;
            dumz /= 1000.;
            nsurvived++;
         }
      } 

      in.close();
      in.clear();

      // make drawing canvas

      name = filename;
      name.ReplaceAll("data/", ""); 
      name.ReplaceAll(".dat", "_c"); 
      c2 = new TCanvas(name, name, 10, 10, 600, 400);
      c2->cd();

      // gaussian fit

      gauss = new TF1("gauss", "gaus", 0., 100.);
      gauss->SetLineColor(kMagenta);
      hSurvived->Fit("gauss","R0");
      Double_t gauspar[3];
      gauss->GetParameters(gauspar);
      Double_t mu = gauspar[1];
      Double_t sigma = TMath::Sqrt(mu * (1 - mu / nevents));
      gauss->SetParameter(2, sigma);
      hSurvived->SetLineWidth(2);
      hSurvived->Draw();
      gauss->Draw("same");

      // poisson fit

      poisson = new TF1("Poisson", Poisson, 0, 30, 2);
      Double_t poissonpar[2];
      if (mu <  kPoissonLimit) {
         poisson->SetNpx(300);
         poisson->SetParName(0, "const");
         poisson->SetParName(1, "mu");
         poisson->SetLineColor(kBlue);
         Double_t mean = (gauspar[1] > 0 ? gauspar[1] : 1);
         poisson->SetParameter(0, gauspar[0]);
         poisson->SetParameter(1, mean);
         hSurvived->Fit("Poisson", "R+");
   
         poisson->GetParameters(poissonpar);

         mu = poissonpar[1];
         sigma = TMath::Sqrt(mu);
      }

      // output results
 
      out << num_wavelen << " " << num_angle << " "
          << mu/nevents << " " << sigma/nevents << std::endl;

      // label settings

      Double_t latexyedge = hSurvived->GetMaximum() * 0.6;
      Double_t latexystep = hSurvived->GetMaximum() * 0.1;
      Double_t latexxedge;
      if (mu < 40) {
         latexxedge = mu + 3 * sigma;
      } else {
         //latexxedge = mu - 7 * sigma;
         latexxedge = 0.1;
         gStyle->SetStatX(0.5);
      }

      TLatex *txt_fname = new TLatex(latexxedge, latexyedge, filename.Data());
      txt_fname->Draw();

      TLatex *txt_beamsize = new TLatex(latexxedge, latexyedge - latexystep, diameter.Data() );
      txt_beamsize->Draw();

      TLatex *txt_fit;
      if (mu < kPoissonLimit) {
         txt_fit = new TLatex(latexxedge, latexyedge - 2 * latexystep, "Poisson fit");
      } else {
         txt_fit = new TLatex(latexxedge, latexyedge - 2 * latexystep, "gaussian fit");
      }
      txt_fit->Draw();

      TString buf("n = ");
      buf += nevents;
      TLatex *txt_n = new TLatex(latexxedge, latexyedge - 3 * latexystep, buf.Data());
      txt_n->Draw();

      if (mu < kPoissonLimit) {
         buf = "sqrt(mu) = ";
      } else {
         buf = "sqrt(np(1-p)) = ";
      }
      buf += sigma;
      TLatex *txt_sigma = new TLatex(latexxedge, latexyedge - 4 * latexystep, buf.Data());
      txt_sigma->Draw();

      // output figs

      TString epsname("./eps/");
      epsname += name;
      epsname += ".eps";
      c2->Print(epsname.Data());

      TString gifname("./gif/");
      gifname += name;
      gifname += ".gif";
      c2->Print(gifname.Data());


      txt_fname->Delete();
      txt_beamsize->Delete();
      txt_fit->Delete();
      txt_n->Delete();
      txt_sigma->Delete();
      c2->Delete();
      gauss->Delete();
      poisson->Delete();
      hSurvived->Delete();

   } // filelist loop end

   file->Write();    

   return 0;

}
