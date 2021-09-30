// $Id: J4DOMPMT.cc,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
//*************************************************************************
//* --------------------
//* J4DOMPMT
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4DOMPMT.hh"
#include "J4DOMPMTSD.hh"
#include "J4DOMParameterList.hh"
#include "G4Sphere.hh"
#include "G4Torus.hh"
#include "G4Cons.hh"
#include "G4Tubs.hh"
#include "J4UnionSolid.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"



// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------


G4String J4DOMPMT::fFirstName("PMT");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4DOMPMT::J4DOMPMT(J4VDetectorComponent* parent,
                                  G4int  nclones,
                                  G4int  nbrothers, 
                                  G4int  me,
                                  G4int  copyno ) :
  	   J4VDOMDetectorComponent(fFirstName, parent, nclones,
                                  nbrothers, me, copyno)
{   
}


//=====================================================================
//* destructor --------------------------------------------------------

J4DOMPMT::~J4DOMPMT()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4DOMPMT::Assemble() 
{   
  if(!GetLV())
  {	  
     // define geometry

     J4DOMParameterList * list = OpenParameterList();
      
     // MakeSolid ----------//

     G4VSolid * solid = CreatePMTSolid(); 

     Register(solid);
     SetSolid(solid);
    
     // MakeLogicalVolume --//  

     MakeLVWith(OpenMaterialStore()-> Order(list->GetPMTMaterial(),
                                            list->GetPMTPropTable()));
     GetLV()->SetOptimisation(FALSE);

#if 0

     G4OpticalSurface* surface = new G4OpticalSurface(GetName());
     surface->SetType(dielectric_dielectric);
     surface->SetFinish(polished);
     surface->SetModel(glisur);

     new G4LogicalSkinSurface(GetName(),
                              GetLV(),
                              surface );

     surface->SetMaterialPropertiesTable(list->GetPMTSurfaceTable());

#endif
    
     // SetVisAttribute ----//

     PaintLV(list->GetPMTVisAtt() , list->GetPMTColor());    
        
     // Install daughter PV //

  }
}

//=====================================================================
//* CreatePMTSolid ----------------------------------------------------

G4VSolid* J4DOMPMT::CreatePMTSolid()
{

   J4DOMParameterList * list = OpenParameterList();
 
   G4double rmin, rmax, sphi, dphi, stheta, dtheta;
   G4double rmin2, rmax2, dz, sweptR;

   // create photo cathode...
 
   rmin   = 0;
   rmax   = list->GetPhotoCathodeR();
   sphi   = 0;
   dphi   = 2*M_PI;
   stheta = 0;
   dtheta = list->GetPhotoCathodeDTheta();
   G4Sphere *sphere = new G4Sphere("sphere",rmin, rmax, 
                                    sphi, dphi, stheta, dtheta);

   // create a torus...

   rmin   = 0;
   rmax   = 48.0 *mm;
   sweptR = 85.0 *mm;
   sphi   = 0;
   dphi   = 2*M_PI;

   G4Torus *torus = new G4Torus("torus",rmin, rmax, 
                                 sweptR, sphi, dphi);

   // create a cons... 

   rmin   = 0;
   rmax   = 112.0 *mm;
   rmin2  = 0;
   rmax2  = 130.0  *mm;
   dz     = 20    *mm;
   sphi   = 0;
   dphi   = 2*M_PI;

   G4Cons *cons1= new G4Cons("cons",rmin, rmax, rmin2, 
                              rmax2, dz, sphi, dphi);

   rmin   = 0;
   rmax   = 42.5 *mm;
   rmin2  = 0;
   rmax2  = 112.0  *mm;
   dz     = 20    *mm;
   sphi   = 0;
   dphi   = 2*M_PI;

   G4Cons *cons2= new G4Cons("cons",rmin, rmax, rmin2, 
                              rmax2, dz, sphi, dphi);

   // create a tube....

   rmin   = 0;
   rmax   = 42.5 *mm;
   dz     = 31.0 *mm;
   sphi   = 0;
   dphi   = 2*M_PI;

   G4Tubs *tubs = new G4Tubs("tubs",rmin, rmax, dz, 
                              sphi, dphi);

   // conbine all solids...

   G4ThreeVector centerOfTorus(0, 0, 40.0 *mm); 
   G4ThreeVector centerOfCons1(0, 0, 20.0 *mm); 
   G4ThreeVector centerOfCons2(0, 0, -20.0 *mm); 
   G4ThreeVector centerOfTubs (0, 0, -71.0 *mm); 

   J4UnionSolid * solid1
                  = new J4UnionSolid("solid1", sphere, cons1, 0, centerOfCons1);
   J4UnionSolid * solid2
                  = new J4UnionSolid("solid2", solid1, cons2, 0, centerOfCons2);
   J4UnionSolid * solid3
                  = new J4UnionSolid("solid3", solid2, tubs, 0, centerOfTubs);
   J4UnionSolid * solid
                  = new J4UnionSolid(GetName(), solid3, torus, 0, centerOfTorus);
   return solid;  

}
 
//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4DOMPMT::Cabling()
{
   J4DOMPMTSD* sd = new J4DOMPMTSD(this);
   Register(sd);
   SetSD(sd);
} 

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4DOMPMT::InstallIn(J4VComponent         *,
                          G4RotationMatrix     *, 
                          const G4ThreeVector  &) 
{ 
   Assemble();			// You MUST call Assemble(); at first.
  				// 
  
   // Placement function into mother object ------//

   J4DOMParameterList * list = OpenParameterList();
   G4ThreeVector translate   = list->GetPMTLocation();
 
   SetPVPlacement(0, translate);
   Cabling();
}


//* Draw  --------------------------------------------------------
void J4DOMPMT::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4DOMPMT::Print() const
{
}

	
	
