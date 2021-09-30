// $Id: J4EggOkamotoGlass.cc,v 1.2 2007/03/13 17:29:14 hoshina Exp $
//*************************************************************************
//* --------------------
//* J4EggOkamotoGlass
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*     2015/02/02  L.Lu        HEX 
//*     2021/07/01  K.Hoshina   renamed from J4DEggOkamoto
//*************************************************************************

#include "J4EggSolidMaker.hh"
#include "J4EggOkamotoGlass.hh"
#include "J4EggOkamotoGlassSD.hh"
#include "J4PartsParameterList.hh"
#include "J4PartsMaterialStore.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4UserLimits.hh"
#include "G4SubtractionSolid.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4EggOkamotoGlass::fFirstName("EggOkamotoGlass");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4EggOkamotoGlass::J4EggOkamotoGlass(J4VDetectorComponent *parent,
                          G4int  nclones,
                          G4int  nbrothers, 
                          G4int  me,
                          G4int  copyno ) :
      J4VDetectorComponent("Parts", fFirstName, parent, nclones,
			       nbrothers, me, copyno ), fInside(0)
{   
}

//=====================================================================
  //* destructor --------------------------------------------------------

J4EggOkamotoGlass::~J4EggOkamotoGlass()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4EggOkamotoGlass::Assemble() 
{   
  if(!GetLV()){
    
    J4PartsParameterList *list = J4PartsParameterList::GetInstance(); 
    
    //THIS DOESNT WORK!!!
    
    G4VSolid *solid1 = J4EggSolidMaker::GetEggOuterSolid();
    G4VSolid *solid2 = J4EggSolidMaker::GetEggInnerSolid();
    
    G4SubtractionSolid *solid 
      = new G4SubtractionSolid("solid", solid1, solid2);

    Register(solid);
    SetSolid(solid);
    
    // MakeLogicalVolume --//  
    J4PartsMaterialStore *store = J4PartsMaterialStore::GetInstance();
	MakeLVWith(store-> Order(list->GetMaterial("OkamotoGlass"),
                              list->GetPropertiesTable("OkamotoGlass")));

#if 0

    // Set user limits //
    // Tracking step length will be smaller than 1.0mm //
    //GetLV()->SetUserLimits(new G4UserLimits(1.0 *mm));

    G4OpticalSurface* surface = new G4OpticalSurface(GetName());
    surface->SetType(dielectric_dielectric);
    surface->SetFinish(polished);
    surface->SetModel(glisur);

    new G4LogicalSkinSurface(GetName(),
                             GetLV(),
                             surface );

    surface->SetMaterialPropertiesTable(list->GetPropertiesTable("OkamotoGlass"));

#endif
    
    // SetVisAttribute ----//
    PaintLV(list->GetVisAtt("OkamotoGlass"), list->GetColor("OkamotoGlass"));
    
    // Install daughter PV //
    // Install Inside volume  //

  }
}


//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4EggOkamotoGlass::Cabling()
{
  J4EggOkamotoGlassSD* sd = new J4EggOkamotoGlassSD(this);
  Register(sd);
  SetSD(sd);
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4EggOkamotoGlass::InstallIn(J4VComponent         *,
                             G4RotationMatrix     *, 
                             const G4ThreeVector  & ) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  // Placement function into mother object...
  
  SetPVPlacement();
  
  //Cabling();
}



//* Draw  --------------------------------------------------------
void J4EggOkamotoGlass::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4EggOkamotoGlass::Print() const
{
}

	
	
