


class Datum : public TObject
{
   public:
   Double_t fX; //
   Double_t fY; //
   Datum(Double_t x=0, Double_t y=0) : fX(x), fY(y) {}

   Bool_t   IsSortable() const { return kTRUE; } // must return
   Int_t    Compare(const TObject *obj) const
   {
       if (fX < ((Datum *)obj)->fX) return -1;
       if (fX > ((Datum *)obj)->fX) return 1;
       else return 0;
   }
};


int plot_angle_acceptance(const char *beamradius = "13inch") {

   gSystem->Load("libPhysics.so");
   gStyle->SetOptStat(1);
   gStyle->SetOptFit(1);
   gStyle->SetPalette(1);
   gStyle->SetCanvasColor(10);
   gStyle->SetFrameFillColor(10);

   // read input data

   ifstream infile("penet.data");
   if (!infile) {
      cerr << "file open failed!" << endl;
      return 0;
   }

   // count number of data
   Double_t dumangle, dumwave, dumpenet, dumsigma;
   Int_t nAngleBins = 0;
   while (infile >> dumwave >>  dumangle >> dumpenet >> dumsigma) {
      cerr << dumwave << " " << dumangle << " " << dumpenet << " " << dumsigma << endl;
      nAngleBins++;
   }

   infile.close();
   infile.clear();
   infile.open("penet.data");


   Double_t *angle = new Double_t[nAngleBins]; 
   Double_t *wavelen = new Double_t[nAngleBins];
   Double_t *penet = new Double_t[nAngleBins];
   TString  dums;
   Int_t    iangle = 0;

   TCanvas *c_all = new TCanvas("c_all", "c_all", 10, 10, 600, 400);

   // read data again.
   // the output must be normalized 1 at angle 0!
   // data must start from angle 0...

   Double_t penet_at_0deg = 0;

   while (infile >> dumwave >>  dumangle >> dumpenet >> dumsigma) {
   
      angle[iangle]   = dumangle; 
      if (angle[iangle] == 0) penet_at_0deg = dumpenet;
 
      penet[iangle]   = dumpenet / penet_at_0deg;
      cerr << "iangle, ang, penet = " 
           << iangle << " " 
           << angle[iangle] << " "
           << penet[iangle] 
           << endl;
           
      iangle++;
   } 

   // generate output angle_acceptance file...

   char outname[256];
   sprintf(outname, "angle_acceptance_%s_%dnm.data", beamradius, dumwave); 
   char command[1024];
   sprintf(command, "cat header.txt > %s", outname); 
   gSystem->Exec(command);
   ofstream ofile(outname, ios::app);
   ofile << "HEAD wavelenght : " << (int)dumwave << " nm  beam radius : " << beamradius << endl;
   ofile << "HEAD" << endl;
   ofile << endl;
   ofile << "ndata " << nAngleBins << endl;
   ofile << endl;
   for (Int_t i=0; i<nAngleBins; i++) {
      ofile << angle[i] << " " << penet[i] << endl; 
   }
   ofile.close();

   // create TGraph

   TGraph *penetcurve  = new TGraph(nAngleBins, angle, penet);
      
   TString title("angle_vs_penet");
   penetcurve->SetNameTitle(title, title);
   penetcurve->SetMarkerStyle(8);
   penetcurve->SetMarkerColor( 2);
   penetcurve->GetXaxis()->SetTitle("Theta");
   penetcurve->GetXaxis()->SetLabelSize(0.06);
   penetcurve->GetYaxis()->SetTitle("Probability of acceptance");
   penetcurve->GetYaxis()->SetLabelSize(0.06);
   
   c_all->cd(); penetcurve->Draw("AP");
   
}
