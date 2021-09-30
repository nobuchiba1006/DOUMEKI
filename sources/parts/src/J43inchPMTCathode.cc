// $Id: J43inchPMTCathode.cc,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
//*************************************************************************
//* --------------------
//* J43inchPMTCathode
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

#include "J43inchPMTCathode.hh"
#include "J43inchPMTCathodeSD.hh"
#include "J4DEggParameterList.hh"
#include "J4PartsParameterList.hh"
#include "J4PartsMaterialStore.hh"
#include "J4PMTSolidMaker.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J43inchPMTCathode::fFirstName("Cathode");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J43inchPMTCathode::J43inchPMTCathode(J4VDetectorComponent* parent,
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

J43inchPMTCathode::~J43inchPMTCathode()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J43inchPMTCathode::Assemble() 
{   
  if(!GetLV()){	  

    J4PartsParameterList *list = J4PartsParameterList::GetInstance();
    J4PartsMaterialStore * store = J4PartsMaterialStore::GetInstance();
    
    // MakeSolid ----------//
    
    G4VSolid *solid = J4PMTSolidMaker::Get3inchPMTCathodeSolid();
    
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
    
    surface->SetMaterialPropertiesTable(list->GetPMTSurfaceTable());
    
#endif
    // SetVisAttribute ----//
    
    PaintLV(list->GetVisAtt("Cathode") , list->GetColor("Cathode"));
    
    // Install daughter PV //
    
  }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J43inchPMTCathode::Cabling()
{
   J43inchPMTCathodeSD* sd = new J43inchPMTCathodeSD(this);
   Register(sd);
   SetSD(sd);
} 

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J43inchPMTCathode::InstallIn(J4VComponent       *c,
			 G4RotationMatrix     *rot, 
			 const G4ThreeVector  &trans) 
{ 
  Assemble();		       
  SetPVPlacement(rot, trans);
  Cabling();  

}

//* Draw  --------------------------------------------------------
void J43inchPMTCathode::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J43inchPMTCathode::Print() const
{
}
