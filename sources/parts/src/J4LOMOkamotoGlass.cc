// $Id: J4LOMOkamotoGlass.cc,v 1.2 2007/03/13 17:29:14 hoshina Exp $
//*************************************************************************
//* --------------------
//* J4LOMOkamotoGlass
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*     2015/02/02  L.Lu        HEX 

//this shoulb be the substraction of degg and inside
//a better way to do is to define somehow getdegg and getinside
//when to do this?
//*************************************************************************

#include "J4LOMOkamotoGlass.hh"
#include "J4LOMOkamotoGlassSD.hh"
#include "J4LOMSolidMaker.hh"
#include "J4PartsParameterList.hh"
#include "J4PartsMaterialStore.hh"
#include "G4Sphere.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "J4UnionSolid.hh"
#include "G4UserLimits.hh"
#include "G4Polycone.hh"
#include "G4SubtractionSolid.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4LOMOkamotoGlass::fFirstName("LOMOkamoto");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4LOMOkamotoGlass::J4LOMOkamotoGlass(J4VDetectorComponent *parent,
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

J4LOMOkamotoGlass::~J4LOMOkamotoGlass()
{
}

  
//=====================================================================
//* Assemble   --------------------------------------------------------

void J4LOMOkamotoGlass::Assemble() 
{   
  if(!GetLV()){
    
    J4PartsParameterList *list = J4PartsParameterList::GetInstance(); 
    
    //THIS DOESNT WORK!!!
    //G4VSolid *solid  = ((J4LOMOkamotoGlass *)GetMother())->GetLOMInside()->CreateInsideSolid();
    
    //first get LOM, then inside. then subtract


    G4VSolid *solid1 = J4LOMSolidMaker::GetLOMOuterSolid();
    G4VSolid *solid2 = J4LOMSolidMaker::GetLOMInnerSolid();

    G4SubtractionSolid *solid 
      = new G4SubtractionSolid("solid", solid1, solid2);

    Register(solid);
    SetSolid(solid);

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

    surface->SetMaterialPropertiesTable(list->GetOkamotoSurfaceTable());

#endif
    
    // SetVisAttribute ----//
    PaintLV(list->GetVisAtt("OkamotoGlass"), list->GetColor("OkamotoGlass"));
    

    // fInside = new J4LOMInside(this);
    //Register(fInside);

    // Install daughter PV //
    // Install Inside volume  //

  }
}



//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4LOMOkamotoGlass::Cabling()
{
  J4LOMOkamotoGlassSD* sd = new J4LOMOkamotoGlassSD(this);
  Register(sd);
  SetSD(sd);
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4LOMOkamotoGlass::InstallIn(J4VComponent         *,
                             G4RotationMatrix     *, 
                             const G4ThreeVector  & ) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  // Placement function into mother object...
  
  SetPVPlacement();
  
  Cabling();
}



//* Draw  --------------------------------------------------------
void J4LOMOkamotoGlass::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4LOMOkamotoGlass::Print() const
{
}

	
	
