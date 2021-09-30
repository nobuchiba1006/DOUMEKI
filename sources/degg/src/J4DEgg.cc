// $Id: J4DEgg.cc,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
//*************************************************************************
//* --------------------
//* J4DEgg
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*     2015/02/02,04  L.Lu        HEX
//*************************************************************************

//for myself. now we are using solid of revolution instead of torus
//at the moment we only use one ellpsoid to describe the egg. however. in the future this could be changed to polycone

#include "J4DEgg.hh"
#include "J4EggSolidMaker.hh"
#include "J4PartsParameterList.hh"
#include "J4PartsMaterialStore.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4DEgg::fFirstName("DEgg");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4DEgg::J4DEgg(J4VDetectorComponent *parent,
                          G4int  nclones,
                          G4int  nbrothers, 
                          G4int  me,
                          G4int  copyno ) :
      J4VDetectorComponent("DEgg",fFirstName, parent, nclones,
                              nbrothers, me, copyno ) 
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4DEgg::~J4DEgg()
{
  if(Deregister(fOkamoto)) delete fOkamoto;
  if(Deregister(fInside)) delete fInside;
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4DEgg::Assemble() 
{   
  if(!GetLV()){
   
    J4PartsParameterList *list = J4PartsParameterList::GetInstance();
    G4VSolid *solid = J4EggSolidMaker::GetEggOuterSolid();

    Register(solid);
    SetSolid(solid);
    

    // MakeLogicalVolume --//  
    J4PartsMaterialStore *store = J4PartsMaterialStore::GetInstance();
    MakeLVWith(store->Order(list->GetMaterial("Egg")));
    
    // SetVisAttribute ----//
    PaintLV(list->GetVisAtt("Egg"), list->GetColor("Egg"));
  	
    // Install daughter PV //
    // Install Okamoto     //

#if 1
    fOkamoto = new J4EggOkamotoGlass(this);
    Register(fOkamoto);
    fOkamoto->InstallIn(this);  
    SetDaughter(fOkamoto);
    
    fInside = new J4DEggInside(this, 1, 2, 0, 0);
    Register(fInside);
    fInside->InstallIn(this);  
    SetDaughter(fInside);

    fInsideDown = new J4DEggInside(this, 1, 2, 1, 1);
    Register(fInsideDown);
    G4RotationMatrix *rot = new G4RotationMatrix();
    rot->rotateY(180.*deg);
    fInsideDown->InstallIn(this, rot);  
    SetDaughter(fInsideDown);

#else
    J4DEggGel *gel = new J4DEggGel(this);
    gel->InstallIn(this);
    SetDaughter(gel);
    
    J48inchPMT *pmt = new J48inchPMT(this);
    pmt->InstallIn(this);
    SetDaughter(pmt);

#endif
      
  }
}


//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4DEgg::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4DEgg::InstallIn(J4VComponent        *,
                     G4RotationMatrix     *, 
                     const G4ThreeVector  & ) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object...
  
  SetPVPlacement();

}



//* Draw  --------------------------------------------------------
void J4DEgg::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4DEgg::Print() const
{
}



	
	
