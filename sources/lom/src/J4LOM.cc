// $Id: J4LOM.cc,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
//*************************************************************************
//* --------------------
//* J4LOM
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

#include "J4LOMOkamotoGlass.hh"
#include "J4LOM.hh"
#include "J4LOMSolidMaker.hh"
#include "J44inchPMT.hh"
#include "J48inchPMT.hh"
#include "J4PartsParameterList.hh"
#include "J4PartsMaterialStore.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4LOM::fFirstName("LOM");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4LOM::J4LOM(J4VDetectorComponent *parent,
                          G4int  nclones,
                          G4int  nbrothers, 
                          G4int  me,
                          G4int  copyno ) :
      J4VDetectorComponent("LOM", fFirstName, parent, nclones,
                              nbrothers, me, copyno ) 
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4LOM::~J4LOM()
{
  if(Deregister(fOkamoto)) delete fOkamoto;
  if(Deregister(fInside)) delete fInside;
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4LOM::Assemble() 
{   
  if(!GetLV()){
   
    J4PartsParameterList *list = J4PartsParameterList::GetInstance();
    G4VSolid *solid = J4LOMSolidMaker::GetLOMOuterSolid();

    Register(solid);
    SetSolid(solid);

    // MakeLogicalVolume --//
    J4PartsMaterialStore *store = J4PartsMaterialStore::GetInstance();
    MakeLVWith(store->Order(list->GetMaterial("LOM")));
    
    // SetVisAttribute ----//
    PaintLV(list->GetVisAtt("LOM"), list->GetColor("LOM"));
  	
    // Install daughter PV //
    // Install Okamoto     //

    fOkamoto = new J4LOMOkamotoGlass(this);
    Register(fOkamoto);
    //fOkamoto->InstallIn(this);  
    //SetDaughter(fOkamoto);

    //J44inchPMT *pmt = new J44inchPMT(this);
    //J48inchPMT *pmt = new J48inchPMT(this);
    //pmt->InstallIn(this);
    //SetDaughter(pmt);
    
    fInside = new J4LOMInside(this, 1, 2, 0);
    Register(fInside);
    fInside->InstallIn(this);  
    SetDaughter(fInside);

  }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4LOM::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4LOM::InstallIn(J4VComponent        *,
                     G4RotationMatrix     *, 
                     const G4ThreeVector  & ) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object...
  
  SetPVPlacement();

}



//* Draw  --------------------------------------------------------
void J4LOM::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4LOM::Print() const
{
}

	
	
