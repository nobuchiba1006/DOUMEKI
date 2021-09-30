// $Id: J4EXPHall.cc,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
//*************************************************************************
//* --------------------
//* J4EXPHall
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "G4Box.hh"

#include "J4EXPHall.hh"
#include "J4VMaterialStore.hh"
#include "J4VSensitiveDetector.hh"
#include "J4ParameterList.hh"
#include "G4Sphere.hh"
#include "G4MaterialPropertiesTable.hh"
// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------


J4VMaterialStore* J4EXPHall::fMaterialStore = 0;

G4String J4EXPHall::fProjectName("ICECUBE");
G4String J4EXPHall::fEXPName("Gen2EXPHall");

//=====================================================================
//---------------------
// Class Description
//---------------------

// ====================================================================
//* constructor -------------------------------------------------------

J4EXPHall::J4EXPHall(J4VComponent *parent,
                     G4int         nclones,
                     G4int         nbrothers, 
                     G4int         me,
                     G4int         copyno ) :
           J4VComponent( fProjectName, fEXPName, parent, 
                         nclones, nbrothers, me, copyno  )
{ 
  
      
  Assemble();

}

// ====================================================================
//* destructor --------------------------------------------------------
J4EXPHall::~J4EXPHall()
{	
#ifndef __GEANT452__
  if (Deregister(fMaterialStore)) delete fMaterialStore;
#endif
}

// ====================================================================
//* Assemble   --------------------------------------------------------
void J4EXPHall::Assemble()
{  
   if (!GetLV()){
      J4ParameterList *list = J4ParameterList::GetInstance();  	
      fSizeOfEXPHall.set(list->GetEXPHallHalfX(),
                         list->GetEXPHallHalfY(),
                         list->GetEXPHallHalfZ());


      //G4VSolid *solid = new G4Sphere(fEXPName, 0, fSizeOfEXPHall.x(), 0, 2*M_PI, 0, M_PI);

      G4VSolid *solid = new G4Box(fEXPName, 
                                  fSizeOfEXPHall.x(),
                                  fSizeOfEXPHall.y(),
                                  fSizeOfEXPHall.z());

      Register(solid);
      SetSolid(solid);

      MakeLVWith(OpenMaterialStore()->Order(list->GetEXPHallMaterial(), 
                                            list->GetEXPHallMaterialTable()));
   
      //PaintLV(TRUE, G4Colour(0., 1., 1.));
      PaintLV(FALSE, G4Colour(0., 1., 1.));
   
      SetPVPlacement();
   }	
}


//=====================================================================
//* InstallIn  --------------------------------------------------------
void J4EXPHall::InstallIn(J4VComponent         *,
                          G4RotationMatrix     *, 
                          const G4ThreeVector  &) 
{
}

//=====================================================================
//* OutputAll ---------------------------------------------------------
void J4EXPHall::OutputAll(G4HCofThisEvent* HCTE, std::ofstream & )
{

   
   if (GetSD()) {  
      if (IsOn()) {
          GetSD()->OutputAll(HCTE);  
      }
   }

   J4ComponentArray daughters = GetDaughters();
   G4int ndaughters = daughters.entries();

   G4int i;

   for( i=0; i<ndaughters; i++) {
      daughters[i]->OutputAll(HCTE);
   }
}

//* Draw  --------------------------------------------------------
void J4EXPHall::Draw()
{
  // set visualization attributes
}
	
//* Print  --------------------------------------------------------
void J4EXPHall::Print() const
{
}

//* OpenMaterialStore ---------------------------------------------
J4VMaterialStore* J4EXPHall::OpenMaterialStore()
{

  if (!fMaterialStore) {
     fMaterialStore = new J4VMaterialStore();
     Register(fMaterialStore);
  } 
  return fMaterialStore; 

}
