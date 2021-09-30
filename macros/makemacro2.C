{

#include <iomanip>

   ofstream out("manybeam.g4mac");
 
   Int_t    nevts = 100;    // 
   Int_t    nbanches = 2000;    // 


   Int_t count = 0;

   out << "/jupiter/generator CircleBeam" << endl;
   out << "/jupiter/beam/circle/particle opticalphoton" << endl;
   out << "/jupiter/beam/circle/energy 3.64 eV" << endl;
   out << "/jupiter/beam/circle/radius 16.51 cm" << endl;
   out << "/jupiter/beam/circle/direction 0. 0. -1." << endl;
   out << "/jupiter/beam/circle/position 0. 0. 0. cm" << endl;
   out << "/jupiter/beam/circle/translation 0. 0. 17. cm" << endl;
   //out << "/jupiter/beam/circle/rotation 0. 0. 0. degree" << endl;
   out << "/jupiter/run/SetFileOpenMode add" << endl;

   for (Int_t i=0; i<nbanches; i++) {
      out << "/jupiter/run/SetRunNumber " << i << endl; 
      out << "/run/beamOn " << nevts << endl; 
      
   }
   out.close();
   out.clear();

}
