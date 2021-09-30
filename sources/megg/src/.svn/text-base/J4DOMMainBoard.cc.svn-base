// $Id: J4DOMMainBoard.cc,v 1.2 2007/03/13 17:29:14 hoshina Exp $
//*************************************************************************
//* --------------------
//* J4DOMMainBoard
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4DOMMainBoard.hh"
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


G4String J4DOMMainBoard::fFirstName("MainBoard");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4DOMMainBoard::J4DOMMainBoard(J4VDetectorComponent* parent,
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

J4DOMMainBoard::~J4DOMMainBoard()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4DOMMainBoard::Assemble() 
{   
  if(!GetLV())
  {	  
     // define geometry

     J4DOMParameterList * list = OpenParameterList();

     G4double rmin, rmax, dz;
     if (GetMyID() == 0) {  // main board
        rmin   = 5.75 *cm;
        rmax   = 13.75 *cm;
        dz     = 0.5 *cm;
     } else if (GetMyID() == 1) { // flasher board
        rmin   = 5.1 *cm;
        rmax   = 11.9 *cm;
        dz     = 0.1*cm;
     } else if (GetMyID() == 2) { // HV board
        rmin   = 0 *cm;
        rmax   = 5 *cm;
        dz     = 0.1*cm;
     }

     G4double sphi   = 0. *deg;
     G4double dphi   = 2*M_PI;
  	
     // MakeSolid ----------//
     G4Tubs *solid = new G4Tubs (GetName(),
                                rmin, rmax, dz,
                                sphi, dphi);
     Register(solid);
     SetSolid(solid);
    
     // MakeLogicalVolume --//  
     MakeLVWith(OpenMaterialStore()-> Order(list->GetMainBoardMaterial()));

     // Tracking optimization must be off when its solid is complicated 
     //GetLV()->SetOptimisation(FALSE);

     // SetVisAttribute ----//
     PaintLV(list->GetMainBoardVisAtt() , list->GetMainBoardColor());    
        
     // Install daughter PV //
    
  }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4DOMMainBoard::Cabling()
{
} 

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4DOMMainBoard::InstallIn(J4VComponent    *,
                          G4RotationMatrix     *, 
                          const G4ThreeVector  &) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object ------//
  
   J4DOMParameterList * list = OpenParameterList();
   G4ThreeVector translate   = list->GetMainBoardLocation();

   if (GetMyID() == 0) { // main board
      SetPVPlacement(0, translate);
   
   } else if (GetMyID() == 1) { // flasher board
      G4double z = translate.z();
      translate.setZ(z - 3.5*cm);
      SetPVPlacement(0, translate);
   } else if (GetMyID() == 2) { // HV board
      G4double z = translate.z();
      translate.setZ(z - 9*cm);
      SetPVPlacement(0, translate);
   }
  
}


//* Draw  --------------------------------------------------------
void J4DOMMainBoard::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4DOMMainBoard::Print() const
{
}

	
	
