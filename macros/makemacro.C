{

#include <iomanip>

   ofstream out("direction.g4mac");
 
   Double_t r = 17;          // radius of DOM [cm]
   Double_t npoints = 181;   // sumpling points
   Double_t nbins   = 19;    // 
   Double_t nevents = 1000;   //
   Int_t    nmarged = (Int_t)npoints / nbins;    // 

   Double_t x, y, z;
   Double_t dtheta  = TMath::Pi() / npoints;    // radian

   Int_t count = 0;

   out << "/jupiter/generator CircleBeam" << endl;
   out << "/jupiter/beam/circle/particle opticalphoton" << endl;
   out << "/jupiter/beam/circle/energy 3.64 eV" << endl;
   out << "/jupiter/beam/circle/radius 16.51 cm" << endl;
   out << "/jupiter/beam/circle/direction 0. 0. -1." << endl;
   out << "/jupiter/beam/circle/position 0. 0. 0. cm" << endl;
   out << "/jupiter/run/SetFileOpenMode add" << endl;

   for (Int_t i=0; i<npoints; i++) {
      Double_t theta = i * dtheta;
      x = 0.;
      y = - r * TMath::Sin(theta); 
      z = r * TMath::Cos(theta); 

      out << "/jupiter/beam/circle/translation " << std::setprecision(12)  
          << x << " " << y << " " << z << " cm" << endl;
      out << "/jupiter/beam/circle/rotations " 
          << theta * 180 / TMath::Pi() << " 0. 0 degree" << endl;

      out << "/jupiter/run/SetRunNumber " << i << endl; 
      out << "/run/beamOn " << nevents << endl; 
      
   }
   out.close();
   out.clear();

}
