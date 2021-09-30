// $Id: J4DEggGel.cc,v 1.2 2007/03/13 17:29:14 hoshina Exp $
//*************************************************************************
//* --------------------
//* J4DEggGel
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*     2015/02/09  L.Lu        For HEX
//*************************************************************************
//now we change logic. only use the front part of the sphere and torus to minus 


#include "J4DEggGel.hh"
#include "J4DEggGelSD.hh"
#include "J4PartsParameterList.hh"
#include "J4PartsMaterialStore.hh"
#include "J4DEggParameterList.hh"
#include "J4EggSolidMaker.hh"
#include "J4PMTSolidMaker.hh"
#include "G4Sphere.hh"
#include "G4Tubs.hh"
#include "G4SubtractionSolid.hh"
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


G4String J4DEggGel::fFirstName("Gel");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4DEggGel::J4DEggGel(J4VDetectorComponent* parent,
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

J4DEggGel::~J4DEggGel()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4DEggGel::Assemble() 
{   
  if(!GetLV())
  {	  
     // define geometry
    
     J4PartsParameterList * list = J4PartsParameterList::GetInstance();
    
     G4VSolid *solid = CreateGelSolid();
     Register(solid);
     SetSolid(solid);
     
     // MakeLogicalVolume --//  
     J4PartsMaterialStore *store = J4PartsMaterialStore::GetInstance();
     MakeLVWith(store-> Order(list->GetMaterial("Gel"),
                              list->GetPropertiesTable("Gel")));

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

     surface->SetMaterialPropertiesTable(list->GetPropertiesTable("Gel"));

#endif
    
     // SetVisAttribute ----//
     PaintLV(list->GetVisAtt("Gel") , list->GetColor("Gel"));    
        
     // Install daughter PV //
    
  }
}

//=====================================================================
//* CreateGelSolid -------------------------------------------------------
G4VSolid * J4DEggGel::CreateGelSolid()
{

   G4VSolid *degg_inner = J4EggSolidMaker::GetHalfEggInnerSolid();
   G4VSolid *degg_innertub = J4EggSolidMaker::GetHalfEggInnerTubSolid();
   G4VSolid *pmt = J4PMTSolidMaker::Get8inchPMTSolid();

   J4DEggParameterList * list = J4DEggParameterList::GetInstance();
   G4ThreeVector loc = list->GetPMTLocation();

   G4SubtractionSolid * solid1 = new G4SubtractionSolid ("solid1", degg_inner, degg_innertub, 0, G4ThreeVector());
   G4SubtractionSolid * solid = new G4SubtractionSolid ("solid", solid1, pmt, 0, loc);

   return solid;

}

/*
//=====================================================================
//* CreateGelSolid -------------------------------------------------------

G4VSolid* J4DEggGel::CreateGelSolid()
{
  
    //need to first create inside

    G4VSolid * solidInside = J4EggSolidMaker::GetEggInnerSolid(); 
       
    //now create the middle part that not needed for GEL 

    G4VSolid * solidInsideTub = J4EggSolidMaker::GetEggInsideTubSolid(); 

    //now combine two PMTs and the middle part
    
    G4VSolid *solidPMTup  = J4PMTSolidMaker::Get8inchPMTSolid(); 
    
    //combine Inside middle and two PMTs

    G4ThreeVector centerOfPMTup, centerOfPMTdown,centerOfInside,centerOfTubs;
    //    centerOfPMTup = G4ThreeVector(0, 0, 12.2483 *cm); 
    centerOfPMTup = G4ThreeVector(0, 0, 12.1000 *cm); 
    //    centerOfPMTdown = G4ThreeVector(0, 0, -12.2483 *cm); 
    centerOfPMTdown = G4ThreeVector(0, 0, -12.1000 *cm); 
    centerOfInside = G4ThreeVector(0, 0, 0 *cm); 
    centerOfTubs = G4ThreeVector(0, 0, 0 *cm);

    G4Tubs *tubs = new G4Tubs("tubs", 0., 14.*cm, 18.1*cm, 0., 2*pi);

    if (GetMyID() == 0) {
       G4SubtractionSolid *solid2 = new G4SubtractionSolid ("solid2",solidInside,solidPMTup,0,centerOfPMTup);
       G4SubtractionSolid *solid = new G4SubtractionSolid ("solid",solid2,tubs,0,centerOfTubs);
       return solid;
    }

    if (GetMyID() == 1) {
       G4SubtractionSolid *solid2 = new G4SubtractionSolid ("solid2",solidInside,solidPMTdown,0,centerOfPMTdown);
       G4SubtractionSolid *solid = new G4SubtractionSolid ("solid",solid2,tubs,0,centerOfTubs);
       return solid;
    }
    
} 
*/


//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4DEggGel::Cabling()
{
   J4DEggGelSD* sd = new J4DEggGelSD(this);
   Register(sd);
   SetSD(sd);
} 

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4DEggGel::InstallIn(J4VComponent         *,
                          G4RotationMatrix     *, 
                          const G4ThreeVector  &) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object ------//
  
  SetPVPlacement();
  //Cabling();
  
}


//* Draw  --------------------------------------------------------
void J4DEggGel::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4DEggGel::Print() const
{
}

	
	
