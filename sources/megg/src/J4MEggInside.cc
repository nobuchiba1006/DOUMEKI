// $Id: J4MEggInside.cc,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
//*************************************************************************
//* --------------------
//* J4MEggInside
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4EggSolidMaker.hh"
#include "J4MEggInside.hh"
#include "J4MEggParameterList.hh"
#include "J43inchPMT.hh"
#include "J4MEggGel.hh"
#include "J4PartsParameterList.hh"
#include "J4PartsMaterialStore.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4MEggInside::fFirstName("Inside");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4MEggInside::J4MEggInside(J4VDetectorComponent *parent,
                          G4int  nclones,
                          G4int  nbrothers, 
                          G4int  me,
                          G4int  copyno ) :

  J4VDetectorComponent( "MEgg", fFirstName, parent, nclones, nbrothers, me, copyno )
{
}

//=====================================================================
//* destructor --------------------------------------------------------

J4MEggInside::~J4MEggInside()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4MEggInside::Assemble() 
{   
  if(!GetLV()){

    J4PartsParameterList *list = J4PartsParameterList::GetInstance();

    // MakeSolid ----------//
    //G4VSolid * solid = J4EggSolidMaker::GetEggInnerSolid();
    G4VSolid * solid = J4EggSolidMaker::GetHalfEggInnerSolid();
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

    // Make PMT at first in order to substruct DEggGel by PMT...

    //fPMT = new J4DEggPMT(this);

    G4int nhalfpmts = 7;

    for (G4int i=0; i<nhalfpmts; ++i) {
        J43inchPMT* pmt = new J43inchPMT(this, 1, nhalfpmts, i);
        fPMTs.push_back(pmt);
        Register(pmt);

        J4MEggGel* gel = new J4MEggGel(this, 1, nhalfpmts, i);
        fGels.push_back(gel);
        Register(gel);
    }

    J4MEggParameterList *megglist = J4MEggParameterList::GetInstance();
    J4MEggParameterList::PMTPlacement plc;

    for (G4int i=0; i<nhalfpmts; ++i) {
        //if (i == 1) continue;
        //if (i == 2) continue;
        //if (i == 3) continue;
        //if (i == 4) continue;
        //if (i == 5) continue;
        //if (i == 6) continue;
        plc = megglist->CalcUpperPMTPlacement(GetMyID(), i);
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

void J4MEggInside::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4MEggInside::InstallIn(J4VComponent         *c,
                             G4RotationMatrix     *rot, 
                             const G4ThreeVector  &trans) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  // Placement function into mother object...
  
  SetPVPlacement(rot, trans);
  
}



//* Draw  --------------------------------------------------------
void J4MEggInside::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4MEggInside::Print() const
{
}

