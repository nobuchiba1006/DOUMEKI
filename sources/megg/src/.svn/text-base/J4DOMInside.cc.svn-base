// $Id: J4DOMInside.cc,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
//*************************************************************************
//* --------------------
//* J4DOMInside
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4DOMInside.hh"
#include "J4DOMParameterList.hh"
#include "G4Sphere.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"



// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4DOMInside::fFirstName("Inside");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4DOMInside::J4DOMInside(J4VDetectorComponent *parent,
                          G4int  nclones,
                          G4int  nbrothers, 
                          G4int  me,
                          G4int  copyno ) :
      J4VDOMDetectorComponent( fFirstName, parent, nclones,
                              nbrothers, me, copyno ), fGel(0), fPMT(0)
                              ,fMainBoard(0), fFlasherBoard(0), fHVBoard(0)
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4DOMInside::~J4DOMInside()
{
  if (Deregister(fGel)) delete fGel;
  if (Deregister(fPMT)) delete fPMT;
  if (Deregister(fMainBoard)) delete fMainBoard;
  if (Deregister(fFlasherBoard)) delete fFlasherBoard;
  if (Deregister(fHVBoard)) delete fHVBoard;
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4DOMInside::Assemble() 
{   
  if(!GetLV()){
  	
    J4DOMParameterList *list = OpenParameterList(); 

    G4double rmin   = 0;
    G4double rmax   = list->GetBenthosInnerR(); 
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
    MakeLVWith(OpenMaterialStore()->Order(list->GetInsideMaterial(),
                                          list->GetInsidePropTable()));

#if 0
    G4OpticalSurface* surface = new G4OpticalSurface(GetName());
    surface->SetType(dielectric_dielectric);
    surface->SetFinish(polished);
    surface->SetModel(glisur);

    new G4LogicalSkinSurface(GetName(),
                             GetLV(),
                             surface );

    surface->SetMaterialPropertiesTable(list->GetInsideSurfaceTable());
#endif
    
    // SetVisAttribute ----//
    PaintLV(list->GetInsideVisAtt(), list->GetInsideColor());
  	
    // Install daughter PV //
    // Install Inside volume  //

    // Make PMT at first in order to substruct DOMGel by PMT...

    fPMT = new J4DOMPMT(this);
    Register(fPMT);

    fGel = new J4DOMGel(this);
    Register(fGel);

    fMainBoard = new J4DOMMainBoard(this, 1, 3, 0);
    Register(fMainBoard);
    fFlasherBoard = new J4DOMMainBoard(this, 1, 3, 1);
    Register(fFlasherBoard);
    fHVBoard = new J4DOMMainBoard(this, 1, 3, 2);
    Register(fHVBoard);

#if 1
    fGel->InstallIn(this);  
    SetDaughter(fGel);
#endif

#if 1
    fPMT->InstallIn(this);  
    SetDaughter(fPMT);
#endif

#if 1
    fMainBoard->InstallIn(this);  
    SetDaughter(fMainBoard);
    fFlasherBoard->InstallIn(this);  
    SetDaughter(fFlasherBoard);
    fHVBoard->InstallIn(this);  
    SetDaughter(fHVBoard);
#endif

  }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4DOMInside::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4DOMInside::InstallIn(J4VComponent         *,
                             G4RotationMatrix     *, 
                             const G4ThreeVector  &) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  // Placement function into mother object...
  
  SetPVPlacement();
  
}



//* Draw  --------------------------------------------------------
void J4DOMInside::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4DOMInside::Print() const
{
}

	
	
