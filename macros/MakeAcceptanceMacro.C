//
// Generate macros for Wavelength Acceptance and Angle Acceptance
//
// to generate Wavelength macros, type
//
// .L MakeAcceptanceMacro.C
// GenerateWavelengthMacros(angle[deg])
//
// to generate angle macros, type
//
// .L MakeAcceptanceMacro.C
// GenerateAngleMacros(wavelen[nm])
//

TString outdatadir  = "./data";
TString outmacrodir = "./input";

const Double_t kRADIUS_OF_BEAMINJECTION_SPHERE = 17; //cm
const Double_t kMINWAVELENGTH = 270; // nm
const Double_t kMAXWAVELENGTH = 720; // nm
const Double_t kMINANGLERANGE = 0;   // deg

//
//setup for 8mm beam
//
//const Double_t kRADIUS  = 0.004; // radius of calibration beam spot[m]
//const TString  kFNAME = "eff_8mm"; // prefix of the output file
//const Double_t kMAXANGLERANGE = 90;  // deg
//const Int_t    kDANGLE        = 1;   // delta angle, deg

//
//setup for 13inch beam
//
const Double_t kRADIUS  = 0.1651; // radius of calibration beam spot[m]
const TString  kFNAME = "eff_13inch"; // prefix of the output file
const Double_t kMAXANGLERANGE = 180;  // deg
const Int_t    kDANGLE        = 10;   // delta angle, deg


#include <iomanip>

// wavelen must be in [nm], angle must be in [degree]
Int_t MakeAcceptanceMacro(Int_t angle, Int_t wavelen) { 

   gsystem

   TString outname(kFNAME);
   outname += "_";
   outname += angle; 
   outname += "deg_";
   outname += wavelen; 
   outname += "nm.g4mac";
   ofstream out((outmacrodir+outname).Data());

   //out << "/control/execute macros/visdawnf.g4mac" << endl;
   out << "/jupiter/generator CircleBeam" << endl;
   out << "/jupiter/beam/circle/particle opticalphoton" << endl;
   out << "/jupiter/beam/circle/radius " << kRADIUS << " m" << endl;
   out << "/jupiter/beam/circle/direction 0. 0. -1." << endl;  // local direction
   out << "/jupiter/beam/circle/position 0. 0. 0. cm" << endl; // local position
   out << "/jupiter/run/SetFileOpenMode add" << endl;

   Double_t x, y, z;
   Double_t theta = angle * (TMath::Pi()/180); // deg to rad

   // move beam position in x-z plane
   x = kRADIUS_OF_BEAMINJECTION_SPHERE * TMath::Sin(theta);
   y = 0.;
   z = kRADIUS_OF_BEAMINJECTION_SPHERE * TMath::Cos(theta); 

   out << "/jupiter/beam/circle/translation " << std::setprecision(12)  
       << x << " " << y << " " << z << " cm" << endl;
   out << "/jupiter/beam/circle/rotations " 
       //<< angle << " 0 0 degree" << endl;
       << "0 " << angle << " 0 degree" << endl;
   out << "#current angle, wavelength = " << angle << " " << wavelen << endl;
   Double_t energy = 1.24e+3 / wavelen;
   out << "/jupiter/beam/circle/energy " << energy << " eV" << endl;
   TString name(outdatadir);

   name += kFNAME;
   name += "_";
   name += angle;
   name += "deg_";
   name += wavelen;
   name += "nm.dat";
   out << "/jupiter/run/SetHitFileName " << name << endl;

   /*
   if (wavelen < 315) {
      out << "/jupiter/run/SetHeaderString nevt 1000 nrun 1000" << endl;
      out << "/control/execute macros/manybeamOn_1000evt_1000bunch.g4mac" << endl; 
   } else {
      out << "/jupiter/run/SetHeaderString nevt 100 nrun 1000" << endl;
      out << "/control/execute macros/manybeamOn_100evt_1000bunch.g4mac" << endl; 
   } 
   */
   // for acceptance generation
   out << "/jupiter/run/SetHeaderString nevt 1000 nrun 1000" << endl;
   out << "/control/execute macros/manybeamOn_1000evt_1000bunch.g4mac" << endl; 

   out << "exit" << endl;

   out.close();
   out.clear();
}

// angle in deg
Int_t GenerateWavelengthMacros(Int_t angle) 
{
   Int_t wavelen = kMINWAVELENGTH;
   while (wavelen <= kMAXWAVELENGTH) {
      MakeAcceptanceMacro(angle, wavelen); 

      if (wavelen >= 300 && wavelen < 450) wavelen += 5;
      else wavelen += 10;
   }
}

// wavelen in nm  
Int_t GenerateAngleMacros(Int_t wavelen) 
{
   Int_t angle = kMINANGLERANGE;
   while (angle <= kMAXANGLERANGE) {
      MakeAcceptanceMacro(angle, wavelen); 
      angle += kDANGLE;
   }
}


