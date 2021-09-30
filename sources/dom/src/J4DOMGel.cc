// $Id: J4DOMGel.cc,v 1.2 2007/03/13 17:29:14 hoshina Exp $
//*************************************************************************
//* --------------------
//* J4DOMGel
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4DOMGel.hh"
#include "J4DOMPMT.hh"
#include "J4DOMInside.hh"
#include "J4DOMParameterList.hh"
#include "G4Sphere.hh"
#include "G4Tubs.hh"
#include "G4SubtractionSolid.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4UserLimits.hh"



// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------


G4String J4DOMGel::fFirstName("Gel");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4DOMGel::J4DOMGel(J4VDetectorComponent* parent,
                                    G4int  nclones,
                                    G4int  nbrothers, 
                                    G4int  me,
                                    G4int  copyno ) :
  	   J4VDOMDetectorComponent(fFirstName, parent, nclones,
                                  nbrothers, me, copyno)
{   
}


//=====================================================================
//* destructor --------------------------------------------------------

J4DOMGel::~J4DOMGel()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4DOMGel::Assemble() 
{   
  if(!GetLV())
  {	  
     // define geometry

     J4DOMParameterList * list = OpenParameterList();

     G4VSolid *solid = CreateGelSolid();
     Register(solid);
     SetSolid(solid);
    
     // MakeLogicalVolume --//  
     MakeLVWith(OpenMaterialStore()-> Order(list->GetGelMaterial(),
                                            list->GetGelPropTable()));

     // Tracking optimization must be off when its solid is complicated 
     GetLV()->SetOptimisation(FALSE);

#if 0

     // Set user limits //
     // Tracking step length will be smaller than 1.0mm //
     GetLV()->SetUserLimits(new G4UserLimits(1.0 *mm));

     G4OpticalSurface* surface = new G4OpticalSurface(GetName());
     surface->SetType(dielectric_dielectric);
     surface->SetFinish(polished);
     surface->SetModel(glisur);

     new G4LogicalSkinSurface(GetName(),
                              GetLV(),
                              surface );

     surface->SetMaterialPropertiesTable(list->GetGelSurfaceTable());

#endif
    
     // SetVisAttribute ----//
     PaintLV(list->GetGelVisAtt() , list->GetGelColor());    
        
     // Install daughter PV //
    
  }
}

//=====================================================================
//* CreateGelSolid -------------------------------------------------------

G4VSolid* J4DOMGel::CreateGelSolid()
{

    J4DOMParameterList * list = OpenParameterList();

    // MakeSolid ----------//
    G4double rmin   = 0;
    G4double rmax   = ((G4Sphere *)GetMother()->GetSolid())->GetOuterRadius(); 
    G4double sphi   = 0;
    G4double dphi   = 2*M_PI;
    G4double stheta = 0;
    G4double dtheta = list->GetGelDTheta();

    G4Sphere *solid1  = new G4Sphere(GetName(),rmin, rmax, sphi, dphi, stheta, dtheta);

    G4double depth    = list->GetGelDepth();
    G4double cylhight = rmax - depth;
    G4double cylr     = rmax * sin(dtheta) - 0.1 * mm;

    G4VSolid *solid2  = new G4Tubs(GetName(),0, cylr, cylhight, 0, 2*M_PI);
    G4SubtractionSolid * solid3 
                      = new G4SubtractionSolid(GetName(), solid1, solid2);

    G4VSolid *solid4  = ((J4DOMInside *)GetMother())->GetPMT()->CreatePMTSolid(); 
    G4SubtractionSolid *solid = new G4SubtractionSolid(GetName(), solid3, solid4, 
                                                       0, list->GetPMTLocation());
    return solid;

} 

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4DOMGel::Cabling()
{
} 

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4DOMGel::InstallIn(J4VComponent         *,
                          G4RotationMatrix     *, 
                          const G4ThreeVector  &) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object ------//
  
  SetPVPlacement();
  
}


//* Draw  --------------------------------------------------------
void J4DOMGel::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4DOMGel::Print() const
{
}

	
	
