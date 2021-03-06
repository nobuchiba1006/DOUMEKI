// $Id: J4DOMParameterList.cc,v 1.3 2007/04/02 23:25:33 hoshina Exp $
//*************************************************************************
//* --------------------
//* J4DOMParameterList
//* --------------------
//* (Description)
//* 	Parameter list for Intermediate Tracker.
//*
//* (Update Record)
//*	2003/03/18  K.Hoshina	Original version.
//*************************************************************************

#include "J4DOMParameterList.hh"
#include <fstream>

using namespace std;

J4DOMParameterList * J4DOMParameterList::fgInstance = 0;

//=====================================================================
//* public getter -----------------------------------------------------
J4DOMParameterList* J4DOMParameterList::GetInstance()
{
   if (!fgInstance) {
      fgInstance = new J4DOMParameterList("DOM");
   }
   return fgInstance;
}

//=====================================================================
//* protected constructor ---------------------------------------------
J4DOMParameterList::J4DOMParameterList(const G4String& name)
                   :J4VParameterList(name)
{
}

//=====================================================================
//* destructor -------------------------------------------------------
J4DOMParameterList::~J4DOMParameterList()
{
   fgInstance = 0;
}

//=====================================================================
//* initialize --------------------------------------------------------
void J4DOMParameterList::Initialize()
{
   SetMaterials();
   SetParameters();
   SetVisAttributes();
   SetColors();
}

//=====================================================================
//* SetMaterials ------------------------------------------------------
void J4DOMParameterList::SetMaterials()
{
#if 1
   fHarnessMaterial      = "Aluminum";
   fDOMMaterial          = "Air";
   fBenthosMaterial      = "BorosilicateGrass";
   fInsideMaterial       = "Air";
   fGelMaterial          = "SiliconGel";
   fPMTMaterial          = "BorosilicateGrass";
   fMainBoardMaterial    = "Silicon";
#else
   fHarnessMaterial      = "Air";
   fDOMMaterial          = "Air";
   fBenthosMaterial      = "Air";
   fInsideMaterial       = "Air";
   fGelMaterial          = "Air";
   fPMTMaterial          = "Air";
   fMainBoardMaterial    = "Air";
#endif

   //
   // MaterialPropatiesTable
   // 

   G4cerr << "***************************************************" << G4endl;
   G4cerr << "J4DOMParameterList::GenerateMaterialPropertiesTable" << G4endl;
   G4cerr << "***************************************************" << G4endl;

   G4double lambda, ene, rindex, penetration, abslen;

   // for Air --------------

   G4int    nindex = 2;
   G4double photonEair[2] = {2.0*eV, 6.2*eV};
   G4double rindexair[2]  = {1.0, 1.0} ;

   fInsidePropTable = new G4MaterialPropertiesTable();
   fInsidePropTable->AddProperty("RINDEX", photonEair, rindexair, nindex);

   fInsideSurfaceTable = new G4MaterialPropertiesTable();
   fInsideSurfaceTable->AddProperty("RINDEX", photonEair, rindexair, nindex);

   // for borosilicate glass --------------

   ifstream in;
   in.open("matprop_glass.dat", std::ios::in);
   if (! in.good()) {
       G4String errorMessage=
          "*** RunAction::BeginOfRunAtcion(): fail to open a file (matprop_glass.dat)."; 
       G4Exception(errorMessage, "FATAL", FatalException, "");
   }

   std::vector<G4double> egrassvec;
   std::vector<G4double> indexgrassvec;
   std::vector<G4double> abslengrassvec;

   G4String dum;
   in >> dum;   // omit comment line
   while (in >> lambda >> ene >> rindex >> penetration >> abslen) {
      egrassvec.push_back(ene);
      indexgrassvec.push_back(rindex);
      abslengrassvec.push_back(abslen);
      G4cerr << ene << " " << rindex << " " 
             << abslen << G4endl;
   }

   in.close();
   in.clear();

   nindex = egrassvec.size();
   G4double *photonEgrass = new G4double [nindex];
   G4double *rindexgrass  = new G4double [nindex];
   G4double *abslengrass  = new G4double [nindex];

   for (G4int i=0; i<nindex; i++) {
      photonEgrass[i] = egrassvec[i] * eV;
      rindexgrass[i]  = indexgrassvec[i];
      abslengrass[i]  = abslengrassvec[i] * cm;
      G4cerr << photonEgrass[i] << " " << rindexgrass[i] << " " 
             << abslengrass[i] << G4endl;
   }
   
   fBenthosPropTable = new G4MaterialPropertiesTable();
   fBenthosPropTable->AddProperty("RINDEX", photonEgrass, rindexgrass, nindex);
   fBenthosPropTable->AddProperty("ABSLENGTH", photonEgrass, abslengrass, nindex);
   fBenthosSurfaceTable = new G4MaterialPropertiesTable();
   fBenthosSurfaceTable->AddProperty("RINDEX", photonEgrass, rindexgrass, nindex);

   fPMTPropTable = new G4MaterialPropertiesTable();
   fPMTPropTable->AddProperty("RINDEX", photonEgrass, rindexgrass, nindex);
   fPMTPropTable->AddProperty("ABSLENGTH", photonEgrass, abslengrass, nindex);
   fPMTSurfaceTable = new G4MaterialPropertiesTable();
   fPMTSurfaceTable->AddProperty("RINDEX", photonEgrass, rindexgrass, nindex);
   
   // for gel --------------

   in.open("matprop_gel.dat", std::ios::in);
   if (! in.good()) {
       G4String errorMessage=
          "*** RunAction::BeginOfRunAtcion(): fail to open a file (matprop_gel.dat)."; 
       G4Exception(errorMessage, "FATAL", FatalException, "");
   }

   std::vector<G4double> egelvec;
   std::vector<G4double> indexgelvec;
   std::vector<G4double> abslengelvec;

   in >> dum;   // omit comment line
   while (in >> lambda >> ene >> rindex >> penetration >> abslen) {
      egelvec.push_back(ene);
      indexgelvec.push_back(rindex);
      abslengelvec.push_back(abslen);
   }

   in.close();
   in.clear();

   nindex = egelvec.size();
   G4double *photonEgel = new G4double [nindex];
   G4double *rindexgel  = new G4double [nindex];
   G4double *abslengel  = new G4double [nindex];

   for (G4int i=0; i<nindex; i++) {
      photonEgel[i] = egelvec[i] * eV;
      rindexgel[i]  = indexgelvec[i];
      abslengel[i]  = abslengelvec[i] * cm;
   }
  
   fGelPropTable = new G4MaterialPropertiesTable();
   fGelPropTable->AddProperty("RINDEX", photonEgel, rindexgel, nindex);
   fGelPropTable->AddProperty("ABSLENGTH", photonEgel, abslengel, nindex);
   fGelSurfaceTable = new G4MaterialPropertiesTable();
   fGelSurfaceTable->AddProperty("RINDEX", photonEgel, rindexgel, nindex);

}

//=====================================================================
//* SetParameters -----------------------------------------------------
void J4DOMParameterList::SetParameters()
{
   // DOM
   fDOMOuterR            = 0.5 * 13.* 2.54 *cm; // 16.51cm
   
   // Benthos 
   fBenthosThickness     = 1. *cm;

   // PMT 
   // radius of Photo-cathode curvature
   fPhotoCathodeR        = 13.67 *cm; 

   // Depth from top of PMT-photocathode to the edge of photocathode
   fPhotoCathodeDepth    = fPhotoCathodeR - (4.0 *cm); 

   // Gel
   // this is minimum thickness of gel between top of PMT-photocathod
   // and benthos inner radius.
   fGelMinThickness      = 10*mm; 
   //fGelMinThickness      = 5*mm; 

   // This is the depth of GEL. It should cover all photocathode.
   fGelDepth             = fPhotoCathodeDepth + 2.5*cm; 

   G4double pmtz         = GetBenthosInnerR() - fGelMinThickness 
                                              - fPhotoCathodeR; 
   fPMTLocation.set(0, 0, pmtz); 

   // MainBoard
   G4double mainboardz = -4.0 * cm;
   fMainBoardLocation.set(0, 0, mainboardz);

}

//=====================================================================
//* SetVisAttributes --------------------------------------------------
void J4DOMParameterList::SetVisAttributes()
{
   fHarnessVisAtt      = TRUE; 
   fDOMVisAtt          = FALSE; 
   fBenthosVisAtt      = TRUE;
   fInsideVisAtt       = FALSE;
   fGelVisAtt          = TRUE;
   fPMTVisAtt          = TRUE;
   fPhotoCathodeVisAtt = TRUE;
   fMainBoardVisAtt    = TRUE;
}

//=====================================================================
//* SetColors ---------------------------------------------------------
void J4DOMParameterList::SetColors()
{
   SetHarnessColor(G4Color(0., 0., 1.));
   SetDOMColor(G4Color(0., 0., 1.));
   SetBenthosColor(G4Color(0.5, 0.3, 0.2));
   SetInsideColor(G4Color(0., 0., 1.));
   SetGelColor(G4Color(0., 0.5, 0.5));
   SetPMTColor(G4Color(1., 1., 1.));
   SetPhotoCathodeColor(G4Color(0.5, 0.5, 0));
   SetMainBoardColor(G4Color(0.5, 0., 0.5));
}


