// $Id: J4BubbleColumn.cc,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
//*************************************************************************
//* --------------------
//* J4BubbleColumn
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4BubbleColumn.hh"
#include "J4ParameterList.hh"
#include "J4PartsParameterList.hh"
#include "J4PartsMaterialStore.hh"
//#include "J4BubbleColumnSD.hh"
#include "J4EggSolidMaker.hh"
#include "G4Tubs.hh"
#include "G4SubtractionSolid.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4BubbleColumn::fFirstName("BubbleColumn");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4BubbleColumn::J4BubbleColumn(const G4String &glasstype,
                          J4VDetectorComponent *parent,
                          G4int  nclones,
                          G4int  nbrothers, 
                          G4int  me,
                          G4int  copyno ) :
      J4VDetectorComponent( "Parts", fFirstName, parent, nclones,
                              nbrothers, me, copyno ),
      fGlassType(glasstype)
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4BubbleColumn::~J4BubbleColumn()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4BubbleColumn::Assemble() 
{   
  if(!GetLV()){
  	
    J4PartsParameterList *list = J4PartsParameterList::GetInstance(); 
    J4ParameterList *explist = J4ParameterList::GetInstance(); 

    G4VSolid *solid = CreateBubbleColumnSolid();

    Register(solid);
    SetSolid(solid);

    // MakeLogicalVolume --//  
    J4PartsMaterialStore *store = J4PartsMaterialStore::GetInstance();

    MakeLVWith(store->Order(list->GetMaterial("BubbleColumn"),
                            list->GetPropertiesTable("BubbleColumn")));
    GetLV()->SetOptimisation(FALSE);

    
    // SetVisAttribute ----//
    PaintLV(list->GetVisAtt("BubbleColumn"), list->GetColor("BubbleColumn"));
  	
    // Install daughter PV //

  }
}


G4VSolid* J4BubbleColumn::CreateBubbleColumnSolid()
{

    J4PartsParameterList *list = J4PartsParameterList::GetInstance(); 
    J4ParameterList *explist = J4ParameterList::GetInstance(); 

    // column
    G4double rmin = 0.0;
    G4double rmax = list->GetBubbleColumnRadius();
    G4double dz = explist->GetEXPHallHalfZ();
    G4double sphi = 0.0;
    G4double dphi = 2*M_PI ;

    G4Tubs* tubs = new G4Tubs("tubs", rmin, rmax, dz, sphi, dphi);
 
    G4VSolid *glasssolid = 0;
    G4VSolid *harnesssolid = 0; 

    if (fGlassType == "Egg") {
        glasssolid = J4EggSolidMaker::GetEggOuterSolid();
        harnesssolid = J4EggSolidMaker::GetEggHarnessSolid();
    } else {
        std::cerr << "J4BubbleColumn::CreateBubbleColumnSolid: glass type " << fGlassType << " is not supported" << std::endl;
    }

    G4SubtractionSolid *solid1
      = new G4SubtractionSolid("solid1", tubs, glasssolid, 0, G4ThreeVector());

    G4SubtractionSolid *solid
      = new G4SubtractionSolid("solid", solid1, harnesssolid, 0, G4ThreeVector());
 
    return solid;

}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4BubbleColumn::Cabling()
{
  /*
  J4BubbleColumnSD* sd = new J4BubbleColumnSD(this);
  Register(sd);
  SetSD(sd);
  */
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4BubbleColumn::InstallIn(J4VComponent *c,
                     G4RotationMatrix     *rot, 
                     const G4ThreeVector  &trans) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object...
  
  SetPVPlacement(rot, trans);

  //Cabling();
}



//* Draw  --------------------------------------------------------
void J4BubbleColumn::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4BubbleColumn::Print() const
{
}

	
	
