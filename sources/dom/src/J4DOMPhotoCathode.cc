// $Id: J4DOMPhotoCathode.cc,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
//*************************************************************************
//* --------------------
//* J4DOMPhotoCathode
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4DOMPhotoCathode.hh"
#include "J4DOMParameterList.hh"
#include "G4Sphere.hh"
#include "G4Tubs.hh"
#include "G4SubtractionSolid.hh"


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------


G4String J4DOMPhotoCathode::fFirstName("PhotoCathode");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4DOMPhotoCathode::J4DOMPhotoCathode(J4VDetectorComponent* parent,
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

J4DOMPhotoCathode::~J4DOMPhotoCathode()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4DOMPhotoCathode::Assemble() 
{   
  if(!GetLV())
  {	  
     // define geometry

     J4DOMParameterList * list = OpenParameterList();
      
     // MakeSolid ----------//
     G4double rmin   = 0;
     G4double rmax   = list->GetPhotoCathodeR();
     G4double sphi   = 0;
     G4double dphi   = 2*M_PI;
     G4double stheta = 0;
     G4double dtheta = list->GetPhotoCathodeDTheta();

     G4double depth    = list->GetPhotoCathodeDepth();
     G4double cylhight = rmax - depth;
     G4double cylr     = rmax * sin(dtheta) - 0.1 * mm;

     std::cerr << " rmax, depth, cylhight, cylr = " << rmax << " " << depth << " " 
            << cylhight << " " << cylr << std::endl;

     G4Sphere *solid1 = new G4Sphere(GetName(),rmin, rmax, sphi, dphi, stheta, dtheta);
     G4Tubs   *solid2 = new G4Tubs(GetName(),0, cylr, cylhight, 0, 2*M_PI);
     G4SubtractionSolid * solid
                      = new G4SubtractionSolid(GetName(), solid1, solid2);

     Register(solid);
     SetSolid(solid);
    
     // MakeLogicalVolume --//  
     MakeLVWith(OpenMaterialStore()-> Order(list->GetPhotoCathodeMaterial()));
    
     // SetVisAttribute ----//
     PaintLV(list->GetPhotoCathodeVisAtt() , list->GetPhotoCathodeColor());    
        
     // Install daughter PV //
    
  }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4DOMPhotoCathode::Cabling()
{
} 

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4DOMPhotoCathode::InstallIn(J4VComponent         *,
                          G4RotationMatrix     *, 
                          const G4ThreeVector  &) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object ------//
  
  SetPVPlacement();
  
}


//* Draw  --------------------------------------------------------
void J4DOMPhotoCathode::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4DOMPhotoCathode::Print() const
{
}

	
	
