// $Id: J4DEggInside.cc,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
//*************************************************************************
//* --------------------
//* J4DEggInside
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4EggSolidMaker.hh"
#include "J4DEggInside.hh"
#include "J48inchPMT.hh"
#include "J4Flasher.hh"
#include "J4ElectricBoard.hh"
#include "J4PartsParameterList.hh"
#include "J4PartsMaterialStore.hh"
#include "J4DEggParameterList.hh"
#include "G4Sphere.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4Polycone.hh"
#include "J4UnionSolid.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4DEggInside::fFirstName("Inside");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4DEggInside::J4DEggInside(J4VDetectorComponent *parent,
                          G4int  nclones,
                          G4int  nbrothers, 
                          G4int  me,
                          G4int  copyno ) :
      J4VDetectorComponent("DEgg", fFirstName, parent, nclones,
				nbrothers, me, copyno ), 
      fGel(0), fPMT(0), fMainBoard(0), 
      fHVBoard(0), fShield(0), fFlasher(0)
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4DEggInside::~J4DEggInside()
{
  if (Deregister(fGel)) delete fGel;
  if (Deregister(fPMT)) delete fPMT;
  if (Deregister(fMainBoard)) delete fMainBoard;
  if (Deregister(fHVBoard)) delete fHVBoard;
  if (Deregister(fShield)) delete fShield;
  if (Deregister(fFlasher)) delete fFlasher;
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4DEggInside::Assemble() 
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

    surface->SetMaterialPropertiesTable(list->GetPropertiesTable("Inside"));
#endif
    
    // SetVisAttribute ----//
    PaintLV(list->GetVisAtt("Inside"), list->GetColor("Inside"));
  	
    // Install daughter PV //
    // Install AInside volume  //

    J4DEggParameterList *degglist = J4DEggParameterList::GetInstance();

#if 1
    fPMT = new J48inchPMT(this);
    Register(fPMT);
    // PMT can be used for other glass housing, so install position is not hardcoded in PMT class.

    G4ThreeVector translate = degglist->GetPMTLocation();
    fPMT->InstallIn(this, 0, translate);  
    SetDaughter(fPMT);
#endif

#if 1
    fGel = new J4DEggGel(this);
    Register(fGel);
    fGel->InstallIn(this);  
    SetDaughter(fGel);
#endif

#if 1
    if (GetMyID() == 0) { // install main board
       G4double mrmin = degglist->GetMainBoardRmin();
       G4double mrmax = degglist->GetMainBoardRmax();
       G4double mdz = degglist->GetMainBoardDz();
       G4ThreeVector mlocation = degglist->GetMainBoardLocation();
       fMainBoard = new J4ElectricBoard(mrmin, mrmax, mdz, this);
       Register(fMainBoard);
       fMainBoard->InstallIn(this, 0, mlocation);  
       SetDaughter(fMainBoard);
    }

    // install HV board
    G4double hrmin = degglist->GetHVBoardRmin();
    G4double hrmax = degglist->GetHVBoardRmax();
    G4double hdz   = degglist->GetHVBoardDz();
    G4ThreeVector hlocation = degglist->GetHVBoardLocation();

    fHVBoard = new J4ElectricBoard(hrmin, hrmax, hdz, this);
    Register(fHVBoard);
    fHVBoard->InstallIn(this, 0, hlocation);  
    SetDaughter(fHVBoard);
#endif

#if 1
    if (GetMyID() == 0) { // install flasher board
       fShield = new J4DEggShield(this, 1, 2, 0);
       Register(fShield);
       fShield->InstallIn(this);
       SetDaughter(fShield);
    } else {
       fShield = new J4DEggShield(this, 1, 2, 1);
       Register(fShield);
       fShield->InstallIn(this);
       SetDaughter(fShield);
    }

    if (GetMyID() == 0) { // install flasher board
       G4double rmin = degglist->GetFlasherRmin();
       G4double rmax = degglist->GetFlasherRmax();
       G4double dz = degglist->GetFlasherDz();
       fFlasher = new J4Flasher(rmin, rmax, dz, this);
       Register(fFlasher);
       G4ThreeVector trans = degglist->GetFlasherLocation();
       fFlasher->InstallIn(this, 0, trans);
       SetDaughter(fFlasher);
    }
#endif

  } // if GetLV() end
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4DEggInside::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4DEggInside::InstallIn(J4VComponent         *mother,
                             G4RotationMatrix     *rot, 
                             const G4ThreeVector  &trans) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  // Placement function into mother object...
  
  SetPVPlacement(rot, trans);
  
}



//* Draw  --------------------------------------------------------
void J4DEggInside::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4DEggInside::Print() const
{
}



