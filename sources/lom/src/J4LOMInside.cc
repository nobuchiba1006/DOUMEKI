// $Id: J4LOMInside.cc,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
//*************************************************************************
//* --------------------
//* J4LOMInside
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4LOMSolidMaker.hh"
#include "J4LOMInside.hh"
#include "J4LOMParameterList.hh"
#include "J4PMTSolidMaker.hh"
#include "J44inchPMT.hh"
#include "J4LOMGel.hh"
#include "J4PartsParameterList.hh"
#include "J4PartsMaterialStore.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4LOMInside::fFirstName("Inside");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4LOMInside::J4LOMInside(J4VDetectorComponent *parent,
                          G4int  nclones,
                          G4int  nbrothers, 
                          G4int  me,
                          G4int  copyno ) :

  J4VDetectorComponent( "LOM", fFirstName, parent, nclones, nbrothers, me, copyno )
{
}

//=====================================================================
//* destructor --------------------------------------------------------

J4LOMInside::~J4LOMInside()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4LOMInside::Assemble() 
{   
  if(!GetLV()){

    J4PartsParameterList *list = J4PartsParameterList::GetInstance();

    // MakeSolid ----------//
    //G4VSolid * solid = J4LOMSolidMaker::GetLOMInnerSolid();
    G4VSolid * solid = J4LOMSolidMaker::GetLOMInnerSolid();
	Register(solid);
    SetSolid(solid);

    // MakeLogicalVolume --//
    J4PartsMaterialStore *store = J4PartsMaterialStore::GetInstance();
    MakeLVWith(store->Order(list->GetMaterial("Inside"),
                            list->GetPropertiesTable("Inside")));

  	
#if 0
    G4OpticalSurface* surface = new G4OpticalSurface(GetName());
    surface->SetType(dielectric_dielectric);
    surface->SetFinish(polished);
    surface->SetModel(glisur);

    new G4LogicalSkinSurface(GetName(),
                             GetLV(),
                             surface );

    surface->SetMaterialPropertiesTable(list->GetInsideSurfaceTable());
#endif
    
    // SetVisAttribute ----//
    PaintLV(list->GetVisAtt("Inside"), list->GetColor("Inside"));
  	
    // Install daughter PV //
    // Install Inside volume  //

    // Make PMT at first in order to substruct DLOMGel by PMT...

    //fPMT = new J4DLOMPMT(this);


	for(int i=0;i<18;i++){
		J44inchPMT* pmt = new J44inchPMT(this, 1, 18, i);
        fPMTs.push_back(pmt);
        Register(pmt);
	}

		
	G4VSolid* solidPMT = J4PMTSolidMaker::Get4inchPMTCathodeSolid();
	for(int i=0;i<18;i++){
		//if(i==0 || i==17) continue;
        J4LOMGel* gel = new J4LOMGel(this, 1, 18, i);
		gel->SetPMTCathodeSolid(solidPMT);
		gel->SetInsideSolid(solid);
		fGels.push_back(gel);
        Register(gel);
	}

	J4LOMParameterList *lomlist = J4LOMParameterList::GetInstance();
    J4LOMParameterList::PMTPlacement plc;

    for (G4int i=0; i<18; ++i) {
        plc = lomlist->CalcPMTPlacement(i);
        fPMTs[i]->InstallIn(this, plc.first, plc.second);
        SetDaughter(fPMTs[i]);

        // gels know where is it installed
        fGels[i]->InstallIn(this);
        SetDaughter(fGels[i]);
    }

    

  }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4LOMInside::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4LOMInside::InstallIn(J4VComponent         *c,
                             G4RotationMatrix     *rot, 
                             const G4ThreeVector  &trans) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  // Placement function into mother object...
  
  SetPVPlacement(rot, trans);
  
}



//* Draw  --------------------------------------------------------
void J4LOMInside::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4LOMInside::Print() const
{
}

