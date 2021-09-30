// $Id: J43inchPMT.cc,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
//*************************************************************************
//* --------------------
//* J43inchPMT
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

#include "J43inchPMT.hh"
#include "J43inchPMTCathode.hh"
#include "J43inchPMTSD.hh"
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

G4String J43inchPMT::fFirstName("PMT");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J43inchPMT::J43inchPMT(J4VDetectorComponent* parent,
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

J43inchPMT::~J43inchPMT()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J43inchPMT::Assemble() 
{   
  if(!GetLV()){	  

    J4PartsParameterList *list = J4PartsParameterList::GetInstance();
    J4PartsMaterialStore * store = J4PartsMaterialStore::GetInstance();
    
    // MakeSolid ----------//
    
    G4VSolid *solid = J4PMTSolidMaker::Get3inchPMTSolid();
    
    Register(solid);
    SetSolid(solid);
    
    // MakeLogicalVolume --//  
    MakeLVWith(store->Order(list->GetMaterial("PMT"),
                            list->GetPropertiesTable("PMT")));
    GetLV()->SetOptimisation(FALSE);
    
#if 0
    G4OpticalSurface* surface = new G4OpticalSurface(GetName());
    surface->SetType(dielectric_metal);
    surface->SetFinish(polished);
    surface->SetModel(glisur);
    
    new G4LogicalSkinSurface(GetName(),
                              GetLV(),
			     surface );
    
    surface->SetMaterialPropertiesTable(list->GetPropertiesTable(list->GetMaterial("PMT")));
    
#endif
    // SetVisAttribute ----//
    
    PaintLV(list->GetVisAtt("PMT") , list->GetColor("PMT"));
    
    // Install daughter PV //

    fCathode = new J43inchPMTCathode(this);
    Register(fCathode);
    fCathode->InstallIn(this, 0, G4ThreeVector());
    SetDaughter(fCathode);

    fPMTBase = new J43inchPMTBase(this);
    Register(fPMTBase);
    fPMTBase->InstallIn(this, 0, G4ThreeVector());
    SetDaughter(fPMTBase);

  }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J43inchPMT::Cabling()
{
   /*
   J43inchPMTSD* sd = new J43inchPMTSD(this);
   Register(sd);
   SetSD(sd);
   */
} 

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J43inchPMT::InstallIn(J4VComponent       *c,
			 G4RotationMatrix     *rot, 
			 const G4ThreeVector  &trans) 
{ 
  Assemble();		       
  SetPVPlacement(rot, trans);
  //Cabling();  

}

//* Draw  --------------------------------------------------------
void J43inchPMT::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J43inchPMT::Print() const
{
}
