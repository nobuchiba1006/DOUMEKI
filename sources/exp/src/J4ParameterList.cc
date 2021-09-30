// $Id: J4ParameterList.cc,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
//*************************************************************************
//* --------------------
//* J4ParameterList
//* --------------------
//* (Description)
//*
//* (Update Record)
//*	2002/12/20  K.Hoshina	Original version.
//*************************************************************************

#include "J4ParameterList.hh"
 
J4ParameterList* J4ParameterList::fgInstance = 0;

//=====================================================================
//* public get function -----------------------------------------------
J4ParameterList* J4ParameterList::GetInstance()
{
   std::cerr << "J4ParameterList GetInstance is called" << G4endl;
   if (!fgInstance) {
      fgInstance = new J4ParameterList("EXPHallParam");
   } 
   std::cerr << "J4ParameterList returning pointer" << G4endl;
   return fgInstance;
}

//=====================================================================
//* protected constructor ---------------------------------------------

J4ParameterList::J4ParameterList(const G4String &name)
                :J4VParameterList(name)
{
   std::cerr << "J4ParameterList constructor is called" << G4endl;
}

//=====================================================================
//* destructor -------------------------------------------------------

J4ParameterList::~J4ParameterList()
{
   fgInstance = 0;
}

//=====================================================================
//* initialize -----------------------------------------------
void J4ParameterList::Initialize()
{

   std::cerr << "J4ParameterList Initialize is called" << G4endl;
   if (!fgInstance) {
      fgInstance = new J4ParameterList("exphall");
   } 
   SetParameters();
}

//=====================================================================
//* SetParameters -----------------------------------------------------

void J4ParameterList::SetParameters()
{
   std::cerr << "J4ParameterList SetParameters is called" << G4endl;

   fEXPHallMaterial = "Ice"; // icecube ice 
   const G4int nEntries = 45;

   // 270nm to 720 nm, every 10 nm
   G4double photonE[nEntries] =   
         { 1.73*eV, 1.77143*eV, 1.7971*eV, 1.82353*eV, 1.85075*eV,
           1.87879*eV, 1.90769*eV, 1.9375*eV, 1.96825*eV, 2*eV,
           2.03279*eV, 2.06667*eV, 2.10169*eV, 2.13793*eV, 2.17544*eV,
           2.21429*eV, 2.25455*eV, 2.2963*eV, 2.33962*eV, 2.38462*eV,
           2.43137*eV, 2.48*eV, 2.53061*eV, 2.58333*eV, 2.6383*eV,
           2.69565*eV, 2.75556*eV, 2.81818*eV, 2.88372*eV, 2.95238*eV,
           3.02439*eV, 3.1*eV, 3.17949*eV, 3.26316*eV, 3.35135*eV,
           3.44444*eV, 3.54286*eV, 3.64706*eV, 3.75758*eV, 3.875*eV,
           4*eV, 4.13333*eV, 4.27586*eV, 4.42857*eV, 4.59259*eV };

   // phase index, icecube ice
   G4double icerindex[nEntries] = 
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
   G4double iceabslen[nEntries] =  
         { 1.53548*m, 1.75477*m, 2.01271*m, 2.31728*m, 2.67831*m,
           3.10791*m, 3.62113*m, 4.23659*m, 4.97741*m, 5.87229*m,
           6.95675*m, 8.2746*m, 9.87943*m, 11.836*m, 14.2211*m,
           17.1234*m, 20.6402*m, 24.8713*m, 29.9055*m, 35.8002*m,
           42.5523*m, 50.0649*m, 58.1194*m, 66.3693*m, 74.3702*m,
           81.65*m, 87.8004*m, 92.5553*m, 95.8262*m, 97.6856*m,
           98.3168*m, 97.9538*m, 96.8329*m, 95.1628*m, 93.1123*m,
           90.8086*m, 88.3431*m, 85.7786*m, 83.1565*m, 80.5033*m,
           77.8352*m, 75.162*m, 72.4893*m, 69.8202*m, 67.1563*m };

   // icecube ice, homogeneous ice model
   G4double mieice[nEntries] ;

   // dummy mie scattering length
   for (int i=0; i<nEntries; ++i) {
       mieice[i] = DBL_MAX;
   }
   G4double mie_water_const[3]={0.99,0.99,0.8};
  
   fEXPMaterialTable = new G4MaterialPropertiesTable();
   fEXPMaterialTable->AddProperty("RINDEX",       photonE, icerindex, nEntries);
   fEXPMaterialTable->AddProperty("ABSLENGTH",    photonE, iceabslen, nEntries);

   /*
   fEXPMaterialTable->AddProperty("MIEHG",photonE,mieice,nEntries)->SetSpline(true);
   fEXPMaterialTable->AddConstProperty("MIEHG_FORWARD",mie_water_const[0]);
   fEXPMaterialTable->AddConstProperty("MIEHG_BACKWARD",mie_water_const[1]);
   fEXPMaterialTable->AddConstProperty("MIEHG_FORWARD_RATIO",mie_water_const[2]);
   */

   fEXPSurfaceTable = new G4MaterialPropertiesTable();
   fEXPSurfaceTable->AddProperty("RINDEX", photonE, icerindex, nEntries);


   fEXPHallVisAtt   = FALSE;
   SetEXPHallColor(G4Color(1, 0, 1));


   fBPOuterR         = 1.8*cm;                 // OuterR of BeamPipe
   fBPMargin         = 0.05*cm;                // Margin between beampipe and IR
   fIRThetaMax       = 200*mrad;               // Theta Max of IR region
   fIRBoxFrontZ      = 500*cm;                 // Front-z of IR box
   fIRBoxEndZ        = 700*cm;                 // End-z of IR box

   fSupportTubInnerR = 40*cm;                  // InnerR of Support Tub
   fSupportTubOuterR = 44*cm;                  // OuterR of Support Tub

   fVTXOuterR        = 8.0*cm;                 // OuterR of VTX
   fVTXZcoverage     = 0.9015;                 // z-coverage in cos_theta of VTX

   fITZcoverage      = 0.90;                   // z-coverage in cos_theta of IT 

   fCDCOuterR        = 157*cm;                 // OuterR of CDC
   fCDCHalfZ         = 160*cm;                 // half z length of CDC

   fCALInnerR        = 157*cm;                 // InnerR of CAL
   fCALOuterR        = 370*cm;                 // OuterR of CAL
   fCALInnerHalfZ    = 185*cm;                 // half z length of innerface of CAL 
   fCALOuterHalfZ    = 400*cm;                 // half z length of outersurface of CAL

   fSOLInnerR        = 375*cm;                 // InnerR of Solenoid
   fSOLOuterR        = 450*cm;                 // OuterR of Solenoid
   fSOLHalfZ         = 430*cm;                 // half z length of Solenoid

#if 1
   fEXPHallHalfX    = 10*m;
   fEXPHallHalfY    = 10*m;
   fEXPHallHalfZ    = 10*m;
#else
   fEXPHallHalfX    = 600*m;
   fEXPHallHalfY    = 600*m;
   fEXPHallHalfZ    = 600*m;
#endif


}


