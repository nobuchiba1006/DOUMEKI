int plot_wavelength_acceptance(const char* beamradius="13inch") {

   gSystem->Load("libPhysics.so");
   gStyle->SetOptStat(1);
   gStyle->SetOptFit(1);
   gStyle->SetPalette(1);
   gStyle->SetCanvasColor(10);
   gStyle->SetFrameFillColor(10);

   ifstream infile("penet.data");
   if (!infile) {
      cerr << "file open failed!" << endl;
      return;
   }

   // count number of data
   Double_t dumangle, dumwave, dumpenet, dumsigma;
   Double_t nWaveBins = 0;
   while (infile >> dumwave >> dumangle >> dumpenet >> dumsigma) {
      cerr << dumwave << " " << dumangle << " " << dumpenet << " " << dumsigma << endl;
      nWaveBins++;
   }

   infile.close();
   infile.clear();
   infile.open("penet.data");


   Double_t *wavelen = new Double_t[nWaveBins];
   Double_t *penet = new Double_t[nWaveBins];
   TString  dums;
   Int_t    iwave = 0;

   TCanvas *c_all = new TCanvas("c_all", "c_all", 10, 10, 600, 400);

   char outname[256];
   sprintf(outname, "wavelength_acceptance_withoutQE_%s_0deg.data", beamradius); 
   char command[1024];
   sprintf(command, "cat header.txt > %s", outname); 
   gSystem->Exec(command);
   ofstream ofile(outname,ios::app);
   
   ofile << "HEAD angle : 0deg   beam radius : " << beamradius << endl;
   ofile << "HEAD" << endl;
   ofile << endl;
   ofile << "ndata " << nWaveBins << endl;
   ofile << endl;
   // read data again
   while (infile >> dumwave >> dumangle >> dumpenet >> dumsigma) {
      wavelen[iwave] = dumwave;
      penet[iwave]   = dumpenet;
      cerr << "iwave, wave, penet = " 
           << iwave << " " 
           << wavelen[iwave] << " "
           << penet[iwave] 
           << endl;

      ofile << wavelen[iwave] << "e-9    " << penet[iwave] << endl;

      iwave++;
   } 
   ofile.close();

   TGraph *penetcurve = new TGraph(nWaveBins, wavelen, penet);

   TString name("canvas_");
   penetcurve->SetMarkerStyle(8);
   penetcurve->SetMarkerColor(2);
   penetcurve->GetXaxis()->SetTitle("wavelength[nm]");
   penetcurve->GetXaxis()->SetLabelSize(0.06);
   //penetcurve->GetXaxis()->SetTitleSize(0.06);
   penetcurve->GetYaxis()->SetTitle("Probability of acceptance");
   penetcurve->GetYaxis()->SetLabelSize(0.06);
   //penetcurve->GetYaxis()->SetTitleSize(0.06);
      
   c_all->cd(); penetcurve->Draw("AP");
   
}
