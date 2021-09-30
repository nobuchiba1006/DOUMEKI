// $Id: J4Bubble.cc,v 1.2 2007/03/13 17:29:14 hoshina Exp $
//*************************************************************************
//* --------------------
//* J4Bubble
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4Bubble.hh"
#include "J4VDetectorComponent.hh"
#include "J4PartsParameterList.hh"
#include "J4PartsMaterialStore.hh"
#include "G4Sphere.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4UserLimits.hh"
#include "Randomize.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------


G4String J4Bubble::fFirstName("Bubble");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4Bubble::J4Bubble(J4VDetectorComponent* parent,
                                    G4int  nclones,
                                    G4int  nbrothers, 
                                    G4int  me,
                                    G4int  copyno ) :
  	   J4VDetectorComponent("Parts",fFirstName, parent, nclones,
                                  nbrothers, me, copyno)
{   
}


//=====================================================================
//* destructor --------------------------------------------------------

J4Bubble::~J4Bubble()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4Bubble::Assemble() 
{   
  if(!GetLV()){	  

     J4PartsParameterList * list = J4PartsParameterList::GetInstance();
     G4double rmin = 0;
     G4double rmax = 0.1*mm;

     // MakeSolid ----------//

     G4Sphere *solid = new G4Sphere(GetName(), rmin, rmax,
                                    0, 360*deg, 0, 180*deg);
     Register(solid);
     SetSolid(solid);
    
     // MakeLogicalVolume --//  
     J4PartsMaterialStore *store = J4PartsMaterialStore::GetInstance();
     MakeLVWith(store-> Order(list->GetMaterial("Bubble")));

     // Tracking optimization must be off when its solid is complicated 
     //GetLV()->SetOptimisation(FALSE);

     // SetVisAttribute ----//
     PaintLV(list->GetVisAtt("Bubble") , list->GetColor("Bubble"));    
        
     // Install daughter PV //
    
  }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4Bubble::Cabling()
{
} 

//=====================================================================
//* InstallIn  --------------------------------------------------------

G4ThreeVector SelectBubblePosR(G4double maxr) 
{
    J4ParameterList *list = J4ParameterList::GetInstance();

    //dummy func: uniform
    G4double r = CLHEP::RandFlat::shoot(0., maxr);    
    G4double dz = list->GetEXPHallHalfZ();
    G4double z = CLHEP::RandFlat::shoot(-dz, dz);    
    G4double phi = CLHEP::RandFlat::shoot(0., 360*deg);

}

void J4Bubble::InstallIn(J4VComponent    *c,
                          G4RotationMatrix    *rot, 
                          const G4ThreeVector & trans) 
{ 

   Assemble();			// You MUST call Assemble(); at first.
  				// 
  
   // Placement function into mother object ------//
   
   if (rot == 0 && trans == G4ThreeVector()) {
      SetPVPlacement();
   } else {
      SetPVPlacement(rot, trans);
   }

}


//* Draw  --------------------------------------------------------
void J4Bubble::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4Bubble::Print() const
{
}

	
	
