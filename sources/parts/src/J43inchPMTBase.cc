// $Id: J43inchPMTBase.cc,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
//*************************************************************************
//* --------------------
//* J43inchPMTBase
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*     2015/02/03  L.Lu        HEX
//*     2020/11/12  M.Suzuki    Changed 2 8inch PMTs to 14 3inch PMTs
//there are 14 4''PMTs per mEgg. each PMT has one phere,four cons and one tub.
//*************************************************************************

#include "J43inchPMTBase.hh"
#include "J4DEggParameterList.hh"
#include "J4PartsParameterList.hh"
#include "J4PartsMaterialStore.hh"
#include "J4PMTSolidMaker.hh"
#include "G4Sphere.hh"
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

G4String J43inchPMTBase::fFirstName("PMTBase");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J43inchPMTBase::J43inchPMTBase(J4VDetectorComponent* parent,
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

J43inchPMTBase::~J43inchPMTBase()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J43inchPMTBase::Assemble() 
{   
  if(!GetLV()){	  

    J4PartsParameterList *list = J4PartsParameterList::GetInstance();
    J4PartsMaterialStore * store = J4PartsMaterialStore::GetInstance();
    
    // MakeSolid ----------//
    
    G4VSolid *solid = J4PMTSolidMaker::Get3inchPMTBaseSolid();
    
    Register(solid);
    SetSolid(solid);
    
    // MakeLogicalVolume --//  
    MakeLVWith(store->Order(list->GetMaterial("PMTBase"),
                            list->GetPropertiesTable("PMTBase")));
    GetLV()->SetOptimisation(FALSE);
    
#if 1
    G4OpticalSurface* surface = new G4OpticalSurface(GetName());
    surface->SetType(dielectric_metal);
    surface->SetFinish(polished);
    surface->SetModel(glisur);
    
    new G4LogicalSkinSurface(GetName(),
                              GetLV(),
			     surface );
    
    surface->SetMaterialPropertiesTable(list->GetPropertiesTable(list->GetMaterial("PMTBase")));
    
#endif
    // SetVisAttribute ----//
    
    PaintLV(list->GetVisAtt("PMTBase") , list->GetColor("PMTBase"));
    
  }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J43inchPMTBase::Cabling()
{
} 

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J43inchPMTBase::InstallIn(J4VComponent       *c,
			 G4RotationMatrix     *rot, 
			 const G4ThreeVector  &trans) 
{ 
  Assemble();		       
  SetPVPlacement(rot, trans);
  //Cabling();  

}

//* Draw  --------------------------------------------------------
void J43inchPMTBase::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J43inchPMTBase::Print() const
{
}
