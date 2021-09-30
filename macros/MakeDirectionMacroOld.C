{

#include <iomanip>

   ofstream out("direction.g4mac");
 
   Double_t r = 17;          // radius of DOM [cm]
   //Double_t npoints = 181;   // sumpling points
   Double_t npoints = 19;   // sumpling points
   Double_t nbins   = 19;    // 
   Double_t nevents = 20000;   //
   Int_t    nmarged = (Int_t)npoints / nbins;    // 

   Double_t x, y, z;
   Double_t dtheta  = TMath::Pi() / (npoints - 1);    // radian
   Double_t x, y, z;
   Double_t wavelen = 400.;
   Double_t energy = 1.24e+3 / wavelen;

   Int_t count = 0;

   out << "/jupiter/generator CircleBeam" << endl;
   out << "/jupiter/beam/circle/particle opticalphoton" << endl;
   //out << "/jupiter/beam/circle/energy 3.64 eV" << endl;   // 340nm
   out << "/jupiter/beam/circle/energy 3.10 eV" << endl;     // 400nm
   out << "/jupiter/beam/circle/radius 16.51 cm" << endl;
   out << "/jupiter/beam/circle/direction 0. 0. -1." << endl;  // local direction
   out << "/jupiter/beam/circle/position 0. 0. 0. cm" << endl; // local position
   out << "/jupiter/run/SetFileOpenMode add" << endl;

   TString fname("surv_fullsize_");

   for (Int_t i=0; i<npoints; i++) {
      Double_t theta = i * dtheta;
      x = 0.;
      y = - r * TMath::Sin(theta); 
      z = r * TMath::Cos(theta); 

      TString name(fname);
      Double_t thetadeg = theta * 180 / TMath::Pi();
      name += (Int_t)thetadeg;
      name += "deg_400nm.dat";
      out << "#current theta = " << theta / TMath::Pi() * 180. << endl;
      out << "/jupiter/run/SetHitFileName " << name << endl;
      out << "/jupiter/beam/circle/translation " << std::setprecision(12)  
          << x << " " << y << " " << z << " cm" << endl;
      out << "/jupiter/beam/circle/rotations " 
          << theta * 180 / TMath::Pi() << " 0. 0 degree" << endl;

      out << "/control/execute macros/manybeamOn.g4mac" << endl; 
      //out << "/jupiter/run/SetRunNumber " << i << endl; 
      //out << "/run/beamOn " << nevents << endl; 
      
   }
   out.close();
   out.clear();

}
