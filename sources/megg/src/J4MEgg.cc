// $Id: J4MEgg.cc,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
//*************************************************************************
//* --------------------
//* J4MEgg
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

#include "J4MEgg.hh"
#include "J4EggSolidMaker.hh"
#include "J43inchPMT.hh"
#include "J48inchPMT.hh"
#include "J4PartsParameterList.hh"
#include "J4PartsMaterialStore.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4MEgg::fFirstName("MEgg");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4MEgg::J4MEgg(J4VDetectorComponent *parent,
                          G4int  nclones,
                          G4int  nbrothers, 
                          G4int  me,
                          G4int  copyno ) :
      J4VDetectorComponent("MEgg", fFirstName, parent, nclones,
                              nbrothers, me, copyno ) 
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4MEgg::~J4MEgg()
{
  if(Deregister(fOkamoto)) delete fOkamoto;
  if(Deregister(fInsideUp)) delete fInsideUp;
  if(Deregister(fInsideDown)) delete fInsideDown;
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4MEgg::Assemble() 
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

    fOkamoto = new J4EggOkamotoGlass(this);
    Register(fOkamoto);
    //fOkamoto->InstallIn(this);  
    //SetDaughter(fOkamoto);

    //J43inchPMT *pmt = new J43inchPMT(this);
    //J48inchPMT *pmt = new J48inchPMT(this);
    //pmt->InstallIn(this);
    //SetDaughter(pmt);
    
    fInsideUp = new J4MEggInside(this, 1, 2, 0);
    Register(fInsideUp);
    fInsideUp->InstallIn(this);  
    SetDaughter(fInsideUp);

    fInsideDown = new J4MEggInside(this, 1, 2, 1);
    Register(fInsideDown);
    G4RotationMatrix rot1,rot2,rot3;
    rot1.rotateX(0. *deg);
    rot2.rotateY(180*deg);
    rot3.rotateZ(240*deg);
    G4RotationMatrix *rot = new G4RotationMatrix(rot1*rot2*rot3);
    fInsideDown->InstallIn(this, rot, G4ThreeVector());  
    SetDaughter(fInsideDown);

  }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4MEgg::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4MEgg::InstallIn(J4VComponent        *,
                     G4RotationMatrix     *, 
                     const G4ThreeVector  & ) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object...
  
  SetPVPlacement();

}



//* Draw  --------------------------------------------------------
void J4MEgg::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4MEgg::Print() const
{
}

	
	
