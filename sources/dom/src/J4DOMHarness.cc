// $Id: J4DOMHarness.cc,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
//*************************************************************************
//* --------------------
//* J4DOMHarness
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4DOMHarness.hh"
#include "J4DOMParameterList.hh"
#include "G4Sphere.hh"
#include "G4Box.hh"


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4DOMHarness::fFirstName("Harness");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4DOMHarness::J4DOMHarness(J4VDetectorComponent *parent,
                          G4int  nclones,
                          G4int  nbrothers, 
                          G4int  me,
                          G4int  copyno ) :
      J4VDOMDetectorComponent( fFirstName, parent, nclones,
                              nbrothers, me, copyno ) 
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4DOMHarness::~J4DOMHarness()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4DOMHarness::Assemble() 
{   
  if(!GetLV()){
  	
    J4DOMParameterList *list = OpenParameterList(); 
    G4double rmin   = list->GetDOMOuterR(); 
    G4double rmax   = rmin + 5. *mm;
    G4double sphi   = 0. *deg;
    G4double dphi   = 2*M_PI;
    G4double stheta = 0.5*M_PI - 0.187765 *rad;  //3.1cm
    G4double dtheta = 2. * 0.187765 *rad;
  	
    // MakeSolid ----------//
    G4Sphere *solid = new G4Sphere (GetName(),
                                   rmin, rmax,
                                   sphi, dphi,
                                   stheta, dtheta);

    Register(solid);
    SetSolid(solid);
    
    // MakeLogicalVolume --//  
    MakeLVWith(OpenMaterialStore()->Order(list->GetHarnessMaterial()));
    
    // SetVisAttribute ----//
    PaintLV(list->GetHarnessVisAtt(), list->GetHarnessColor());
  	
    // Install daughter PV //
    // Install Benthos     //

  }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4DOMHarness::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4DOMHarness::InstallIn(J4VComponent *,
                     G4RotationMatrix     *, 
                     const G4ThreeVector  &) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object...
  
  SetPVPlacement();

}



//* Draw  --------------------------------------------------------
void J4DOMHarness::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4DOMHarness::Print() const
{
}

	
	
