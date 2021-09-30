
int DrawAngRes() {

   ifstream in;
   TString dum;
   Int_t ndata, nlines;

   in.open("angle_acceptance_13inch_420nm.data");

   const int nbuf = 2048;
   char dumbuf[nbuf];
   while (in >> dum) {
      if (dum == "HEAD") {
         in.getline(dumbuf, nbuf);
      } else if (dum == "ndata") {
         in >> ndata;
         break;
      }
   }

   Double_t *angle1 = new Double_t [ndata];
   Double_t *penet1  = new Double_t [ndata];
   nlines = 0;
   while (in >> angle1[nlines] >> penet1[nlines]) {
      cerr << angle1[nlines] << " " << penet1[nlines] << endl;
      nlines++;
   }

   TGraph *g1 = new TGraph(ndata, angle1, penet1);
   g1->SetNameTitle("AngleResponse_Dominant_420nm","AngleResponse_Dominant 420nm");
   g1->SetMarkerStyle(8);
   g1->SetMarkerColor(2);
   g1->GetXaxis()->SetTitle("angle [deg]");
   g1->GetYaxis()->SetTitle("Acceptance");
   g1->Draw("AP");

   g1->Fit("pol6");
   TF1 *pol6 = g1->GetFunction("pol6");

   // output fitted value
   Int_t ndeg = 181;
   cerr << "ndata " << ndeg << endl;
   pol6->SetParameter(0,1.0);
   for (Int_t ideg=0; ideg<ndeg; ideg++) {
      Double_t accept = pol6->Eval((Double_t)ideg);
      if (accept < 0) accept = 0;
      cerr << (Double_t)ideg << " " << accept << endl; 
   }

   in.close();
   in.clear();

   in.open("angle_acceptance_13inch_360nm.data");
   while (in >> dum) {
      if (dum == "HEAD") {
         in.getline(dumbuf, nbuf);
      } else if (dum == "ndata") {
         in >> ndata;
         break;
      }
   }

   Double_t *angle2 = new Double_t [ndata];
   Double_t *penet2  = new Double_t [ndata];
   nlines = 0;
   while (in >> angle2[nlines] >> penet2[nlines]) {
      cerr << angle2[nlines] << " " << penet2[nlines] << endl;
      nlines++;
   }

   TGraph *g2 = new TGraph(ndata, angle2, penet2);
   g2->SetNameTitle("AngleResponse_Dominant_360nm","AngleResponse_Dominant 360nm");
   g2->SetMarkerStyle(8);
   g2->SetMarkerColor(3);
   //g2->Draw("P");

   in.close();
   in.clear();

   in.open("angle_acceptance_13inch_520nm.data");
   while (in >> dum) {
      if (dum == "HEAD") {
         in.getline(dumbuf, nbuf);
      } else if (dum == "ndata") {
         in >> ndata;
         break;
      }
   }

   Double_t *angle3 = new Double_t [ndata];
   Double_t *penet3  = new Double_t [ndata];
   nlines = 0;
   while (in >> angle3[nlines] >> penet3[nlines]) {
      cerr << angle3[nlines] << " " << penet3[nlines] << endl;
      nlines++;
   }

   TGraph *g3 = new TGraph(ndata, angle3, penet3);
   g3->SetNameTitle("AngleResponse_Dominant_520nm","AngleResponse_Dominant 520nm");
   g3->SetMarkerStyle(8);
   g3->SetMarkerColor(4);
   //g3->Draw("P");

   in.close();
   in.clear();

   TLegend *leg = new TLegend(0.4, 0.6, 0.95, 0.9);
   leg->SetHeader("DOMINANT photon Angle Acceptance (no QE)");
   leg->SetMargin(0.2);
   leg->AddEntry(g2, "13inch circle parallel beam 360nm", "p");
   leg->AddEntry(g1, "13inch circle parallel beam 420nm", "p");
   leg->AddEntry(g3, "13inch circle parallel beam 520nm", "p");
   leg->Draw();
   
}
