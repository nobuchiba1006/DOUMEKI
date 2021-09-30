// $Id: J4DEggGel.cc,v 1.2 2007/03/13 17:29:14 hoshina Exp $
//*************************************************************************
//* --------------------
//* J4DEggShield
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//*************************************************************************


#include "J4DEggShield.hh"
#include "J4DEggGel.hh"
#include "J4DEggInside.hh"
#include "J4PartsParameterList.hh"
#include "J4PartsMaterialStore.hh"
#include "J4UnionSolid.hh"
#include "G4Sphere.hh"
#include "G4Cons.hh"
#include "G4Tubs.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4UserLimits.hh"
#include "J4UnionSolid.hh"
#include "G4Polycone.hh"
#include "G4IntersectionSolid.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------


G4String J4DEggShield::fFirstName("Shield");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4DEggShield::J4DEggShield(J4VDetectorComponent* parent,
                                    G4int  nclones,
                                    G4int  nbrothers, 
                                    G4int  me,
                                    G4int  copyno ) :
  	   J4VDetectorComponent("DEgg", fFirstName, parent, nclones,
                                  nbrothers, me, copyno)
{   
}


//=====================================================================
//* destructor --------------------------------------------------------

J4DEggShield::~J4DEggShield()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4DEggShield::Assemble() 
{   
  if(!GetLV()){	  

    J4PartsParameterList * list = J4PartsParameterList::GetInstance();

    // MakeSolid ----------//
    G4VSolid * solid = CreateShieldSolid();

    Register(solid);
    SetSolid(solid);

    // MakeLogicalVolume --//  
    J4PartsMaterialStore *store = J4PartsMaterialStore::GetInstance();
    MakeLVWith(store-> Order(list->GetMaterial("Shield")));
    
    // SetVisAttribute ----//
    PaintLV(list->GetVisAtt("Shield") , list->GetColor("Shield"));    
    
    // Install daughter PV //
    
  }
}

//===================================================================== 
//* CreateSolid ----------------------------------------------------

G4VSolid* J4DEggShield::CreateShieldSolid()
{
    
    G4double rmin1, rmax1, rmin2, rmax2, dz;
    G4double ShieldThickness = 0.018 *mm;
    G4double sphi  = 0. *deg;
    G4double dphi  = 2*M_PI;      

    if (GetMyID() == 0) {

      rmax1 = 49.333086 *mm;
      rmax2 = 204./2 *mm;
      rmin1 = rmax1 - ShieldThickness;
      rmin2 = rmax2 - ShieldThickness;
      dz    = 88./2 *mm;
      G4Cons *cons = new G4Cons("cons",
				 rmin1, rmax1, rmin2, rmax2, dz,
				 sphi, dphi);
      G4double dz2 = 22./2 *mm;
      G4Tubs *tubs = new G4Tubs("tubs",
				rmin2, rmax2, dz2, sphi, dphi);
      G4ThreeVector centerOfTubs(0, 0, dz - 3.1*mm + dz2); // distance between cons and tubs
      J4UnionSolid *solid = new J4UnionSolid(GetName(),
					     cons, tubs, 0, centerOfTubs);
      return solid;

    } else if (GetMyID() == 1) {

      //rmax1 = 224./2 *mm;
      //rmax2 = 48.261065 *mm;
      rmax1 = 48.261065 *mm;
      rmax2 = 224./2 *mm;
      rmin1 = rmax1 - ShieldThickness;
      rmin2 = rmax2 - ShieldThickness;
      dz    = 106.5/2 *mm;
      G4Cons *solid = new G4Cons(GetName(),
				 rmin1, rmax1, rmin2, rmax2, dz,
				 sphi, dphi);
      return solid;

    }

}


//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4DEggShield::Cabling()
{
} 

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4DEggShield::InstallIn(J4VComponent         *,
                             G4RotationMatrix     *, 
                             const G4ThreeVector  &) 
{ 

  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object ------//
  
  //  SetPVPlacement();
  G4ThreeVector translate(0, 0, 0 *mm);
  
  if (GetMyID() == 0) { // Shield positive

    translate.setZ((267. - 15. - 71.5 - 22. + 3.1 - 88./2)*mm);
    SetPVPlacement(0, translate);

  } else if (GetMyID() == 1) { 

    // Shield negative, if fullsize of J4DEggInside is installed   
    //translate.setZ(-(267. - 15. - 71.5 - 106.5/2)*mm);

    // Shield in positive coordinate, if halfsize of J4DEggInside is installed   
    translate.setZ((267. - 15. - 71.5 - 106.5/2)*mm);
    SetPVPlacement(0, translate);
  }

}


//* Draw  --------------------------------------------------------
void J4DEggShield::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4DEggShield::Print() const
{
}

	
	
