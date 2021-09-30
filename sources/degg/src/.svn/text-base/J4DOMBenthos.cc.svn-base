// $Id: J4DOMBenthos.cc,v 1.2 2007/03/13 17:29:14 hoshina Exp $
//*************************************************************************
//* --------------------
//* J4DOMBenthos
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4DOMBenthos.hh"
#include "J4DOMParameterList.hh"
#include "G4Sphere.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4UserLimits.hh"


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4DOMBenthos::fFirstName("Benthos");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4DOMBenthos::J4DOMBenthos(J4VDetectorComponent *parent,
                          G4int  nclones,
                          G4int  nbrothers, 
                          G4int  me,
                          G4int  copyno ) :
      J4VDOMDetectorComponent( fFirstName, parent, nclones,
                              nbrothers, me, copyno ), fInside(0)
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4DOMBenthos::~J4DOMBenthos()
{
  if (Deregister(fInside)) delete fInside;
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4DOMBenthos::Assemble() 
{   
  if(!GetLV()){
  	
    J4DOMParameterList *list = OpenParameterList(); 
    G4double rmin   = list->GetBenthosInnerR(); 
    G4double rmax   = list->GetBenthosOuterR(); 
    G4double sphi   = 0. *deg;
    G4double dphi   = 2. * M_PI;
    G4double stheta = 0. *deg;
    G4double dtheta = M_PI; 
  	
    // MakeSolid ----------//
    G4Sphere *solid = new G4Sphere (GetName(),
                                   rmin, rmax,
                                   sphi, dphi,
                                   stheta, dtheta);
    Register(solid);
    SetSolid(solid);
    
    // MakeLogicalVolume --//  
    MakeLVWith(OpenMaterialStore()->Order(list->GetBenthosMaterial(),
                                          list->GetBenthosPropTable()));

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

    surface->SetMaterialPropertiesTable(list->GetBenthosSurfaceTable());

#endif
    
    // SetVisAttribute ----//
    PaintLV(list->GetBenthosVisAtt(), list->GetBenthosColor());
  	
    // Install daughter PV //
    // Install Inside volume  //

  }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4DOMBenthos::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4DOMBenthos::InstallIn(J4VComponent         *,
                             G4RotationMatrix     *, 
                             const G4ThreeVector  & ) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  // Placement function into mother object...
  
  SetPVPlacement();
  
}



//* Draw  --------------------------------------------------------
void J4DOMBenthos::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4DOMBenthos::Print() const
{
}

	
	
