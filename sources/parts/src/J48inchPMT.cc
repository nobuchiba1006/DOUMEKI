// $Id: J48inchPMT.cc,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $ //*************************************************************************
//* --------------------
//* J48inchPMT
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*     2015/02/03  L.Lu        HEX
//*************************************************************************

//there are two APMTs per degg. each APMT has two torus, one sphere, one tub and one cons
//090315. important change!!! angle of the top sphere!!!

#include "J48inchPMT.hh"
#include "J4PMTSolidMaker.hh"
#include "J48inchPMTSD.hh"
#include "J4PartsParameterList.hh"
#include "J4PartsMaterialStore.hh"
#include "G4Sphere.hh"
#include "G4Torus.hh"
#include "G4Cons.hh"
#include "G4Tubs.hh"
#include "G4IntersectionSolid.hh"
#include "J4UnionSolid.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4Polycone.hh"


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------


G4String J48inchPMT::fFirstName("8inchPMT");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J48inchPMT::J48inchPMT(J4VDetectorComponent* parent,
                                  G4int  nclones,
                                  G4int  nbrothers, 
                                  G4int  me,
                                  G4int  copyno ) :
  	   J4VDetectorComponent("Parts", fFirstName, parent, nclones,
                                  nbrothers, me, copyno)
{   
}


//=====================================================================
//* destructor --------------------------------------------------------

J48inchPMT::~J48inchPMT()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J48inchPMT::Assemble() 
{   
  if(!GetLV()){	  

    J4PartsParameterList * list = J4PartsParameterList::GetInstance();
    J4PartsMaterialStore * store = J4PartsMaterialStore::GetInstance();
    
    // MakeSolid ----------//
    
    //G4VSolid *solid = CreatePMTSolid(); 
    G4VSolid *solid = J4PMTSolidMaker::Get8inchPMTSolid();
    
    Register(solid);
    SetSolid(solid);
    
    // MakeLogicalVolume --//  
    
    MakeLVWith(store->Order(list->GetMaterial("PMT"),
                            list->GetPropertiesTable("PMT")));
    GetLV()->SetOptimisation(FALSE);
    
#if 0
    G4OpticalSurface* surface = new G4OpticalSurface(GetName());
    surface->SetType(dielectric_dielectric);
    surface->SetFinish(polished);
    surface->SetModel(glisur);
    
    new G4LogicalSkinSurface(GetName(),
                              GetLV(),
			     surface );
    
    surface->SetMaterialPropertiesTable(list->GetPropertiesTable("PMT"));
    
#endif
    // SetVisAttribute ----//
    
    PaintLV(list->GetVisAtt("PMT") , list->GetColor("PMT"));    
    
    // Install daughter PV //
    
  }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J48inchPMT::Cabling()
{
  J48inchPMTSD* sd = new J48inchPMTSD(this);
   Register(sd);
   SetSD(sd);
} 

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J48inchPMT::InstallIn(J4VComponent       *mother,
			 G4RotationMatrix     *rot, 
			 const G4ThreeVector  &trans) 
{ 
  Assemble();		       

  SetPVPlacement(rot, trans);

  Cabling();
}


//* Draw  --------------------------------------------------------
void J48inchPMT::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J48inchPMT::Print() const
{
}

	
	
