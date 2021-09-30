// $Id: J4EggHarness.cc,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
//*************************************************************************
//* --------------------
//* J4EggHarness
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4EggHarness.hh"
#include "J4PartsParameterList.hh"
#include "J4PartsMaterialStore.hh"
#include "J4EggSolidMaker.hh"
#include "G4Sphere.hh"
#include "G4Box.hh"


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4EggHarness::fFirstName("Harness");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4EggHarness::J4EggHarness(J4VDetectorComponent *parent,
                          G4int  nclones,
                          G4int  nbrothers, 
                          G4int  me,
                          G4int  copyno ) :
      J4VDetectorComponent("DEgg", fFirstName, parent, nclones,
                              nbrothers, me, copyno ) 
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4EggHarness::~J4EggHarness()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4EggHarness::Assemble() 
{   
  if(!GetLV()){
  	
    J4PartsParameterList *list = J4PartsParameterList::GetInstance();
  	
    // MakeSolid ----------//
    G4VSolid *solid = J4EggSolidMaker::GetEggHarnessSolid();

    Register(solid);
    SetSolid(solid);
    
    // MakeLogicalVolume --//  
    J4PartsMaterialStore *store = J4PartsMaterialStore::GetInstance();
    MakeLVWith(store->Order(list->GetMaterial("Harness")));
    
    // SetVisAttribute ----//
    PaintLV(list->GetVisAtt("Harness"), list->GetColor("Harness"));
  	
    // Install daughter PV //
    // Install Okamoto     //

  }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4EggHarness::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4EggHarness::InstallIn(J4VComponent *,
                     G4RotationMatrix     *, 
                     const G4ThreeVector  &) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object...
  
  SetPVPlacement();

}



//* Draw  --------------------------------------------------------
void J4EggHarness::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4EggHarness::Print() const
{
}

