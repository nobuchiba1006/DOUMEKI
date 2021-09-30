// $Id: J4Flasher.cc,v 1.2 2007/03/13 17:29:14 hoshina Exp $
//*************************************************************************
//* --------------------
//* J4Flasher
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4Flasher.hh"
#include "J4DEggInside.hh"
#include "J4PartsParameterList.hh"
#include "J4PartsMaterialStore.hh"
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

G4String J4Flasher::fFirstName("Flasher");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4Flasher::J4Flasher(G4double rmin, G4double rmax, G4double dz,
                     J4VDetectorComponent* parent,
                                    G4int  nclones,
                                    G4int  nbrothers, 
                                    G4int  me,
                                    G4int  copyno ) :
  	   J4VDetectorComponent("parts", fFirstName, parent, nclones,
                                  nbrothers, me, copyno),
           fRmin(rmin), fRmax(rmax), fDz(dz)
{   
}


//=====================================================================
//* destructor --------------------------------------------------------

J4Flasher::~J4Flasher()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4Flasher::Assemble() 
{   
  if(!GetLV()){
	  
    J4PartsParameterList * list = J4PartsParameterList::GetInstance();

    G4double sphi   = 0. *degree;
    G4double dphi   = 2*M_PI;
        
    // MakeSolid ----------//
    G4Tubs *solid = new G4Tubs (GetName(),
                                fRmin, fRmax, fDz,
                                sphi, dphi);
    Register(solid);
    SetSolid(solid);
    
    // MakeLogicalVolume --//  
    J4PartsMaterialStore *store = J4PartsMaterialStore::GetInstance();
    MakeLVWith(store-> Order(list->GetMaterial("Flasher")));
    
    // Tracking optimization must be off when its solid is complicated 
    //GetLV()->SetOptimisation(FALSE);
    
    // SetVisAttribute ----//
    PaintLV(list->GetVisAtt("Flasher") , list->GetColor("Flasher"));    
    
    // Install daughter PV //
    
  }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4Flasher::Cabling()
{
} 

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4Flasher::InstallIn(J4VComponent    *c,
                          G4RotationMatrix    *rot, 
                          const G4ThreeVector &trans) 
{ 

  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object ------//

   SetPVPlacement(rot, trans);

}


//* Draw  --------------------------------------------------------
void J4Flasher::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4Flasher::Print() const
{
}

	
	
