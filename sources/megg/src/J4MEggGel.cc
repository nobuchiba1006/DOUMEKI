// $Id: J4MEggGel.cc,v 1.2 2007/03/13 17:29:14 hoshina Exp $
//*************************************************************************
//* --------------------
//* J4MEggGel
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*     2015/02/09  L.Lu        For HEX
//*     2020/11/12  M.Suzuki    Changed to 14 gel pads design.
//*************************************************************************
//now we change logic. only use the front part of the sphere and torus to minus 


#include "J4MEggGel.hh"
#include "J4MEggGelSD.hh"
#include "J4MEggInside.hh"
#include "J4EggSolidMaker.hh"
#include "J4PartsParameterList.hh"
#include "J4PartsMaterialStore.hh"
#include "J4MEggParameterList.hh"
#include "G4Sphere.hh"
#include "G4Cons.hh"
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


G4String J4MEggGel::fFirstName("Gel");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4MEggGel::J4MEggGel(J4VDetectorComponent* parent,
                                    G4int  nclones,
                                    G4int  nbrothers, 
                                    G4int  me,
                                    G4int  copyno ) :
  	   J4VDetectorComponent("MEgg", fFirstName, parent, nclones,
                                  nbrothers, me, copyno)
{   
}


//=====================================================================
//* destructor --------------------------------------------------------

J4MEggGel::~J4MEggGel()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4MEggGel::Assemble() 
{   
  if(!GetLV()){	  

     J4PartsParameterList * list = J4PartsParameterList::GetInstance();
    
     // MakeSolid ----------//
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

     surface->SetMaterialPropertiesTable(list->GetGelSurfaceTable());

#endif
    
     // SetVisAttribute ----//
     PaintLV(list->GetVisAtt("Gel") , list->GetColor("Gel"));

  }
}

//=====================================================================
// Create gel solid for upper egg
//=====================================================================
G4VSolid* J4MEggGel::CreateGelSolid()
{
  
    J4PartsParameterList * list = J4PartsParameterList::GetInstance();

    G4VSolid *solidInside = J4EggSolidMaker::GetHalfEggInnerSolid();

    //make pmt cathode for subtraction
    double fromCathodeToCenter = (77.195 - 49.5)*mm;
    G4Sphere *sphere = new G4Sphere("sphere",0. , 56.77*mm, 
				    0., 2*M_PI, 0., 60.29*degree);
        
    //make gel pad
    G4double gelheight = 80./2.*mm;
    double r = gelheight + fromCathodeToCenter;

    G4ThreeVector centerOfPMT(0.,0.,-r);
        
    //alpha is opening angle for the pad 
    double alpha = 61*deg; //best design
    // double alpha = 77.128*deg; //vedant's design
    // double alpha = 90*deg; //simple torus design
    
    double top = (80./tan(alpha) + 49.05) *mm; 

    G4Cons *cons = new G4Cons("cons", 0, 49.05*mm, 
			      0, top, gelheight, 0, 2*M_PI); 
    G4SubtractionSolid *solid1
      = new G4SubtractionSolid("solid1", cons, sphere, 0, centerOfPMT);
    
    
    //--------------------------------------

    int id = GetMyID();
    G4RotationMatrix rot1, rot2, rot3;

    if ( id == 0 ) {
      //gel pad for pmt0    
      G4ThreeVector trans = G4ThreeVector(0,0,0*mm);
      trans.setZ((148.363 + 49.5)*mm + r);
  

      G4IntersectionSolid *solid
          = new G4IntersectionSolid("solid", solidInside, solid1, 0, trans);
      return solid;
      
    } 

    double theta = 75*deg;
    double phi = 30*deg;
    double tilt_ang = 15*deg;
    double rot_y = -(90*deg - tilt_ang); 

    G4int momid = GetMother()->GetMyID();
    J4MEggParameterList * megglist = J4MEggParameterList::GetInstance();  
    J4MEggParameterList::PMTPlacement plc = megglist->CalcUpperPMTPlacement(momid, id);
    //G4RotationMatrix *rot = plc.first;

    // for lower half hemisphere, we need counter-clockwise arrangement
    if (momid % 2 != 0) {
        phi = phi - 60*deg;
    }
      
    if ( id < 4 ) { //1 to 3
	//gel pad fot pmt1
	double x_arm = (60.948 + r*sin(theta)*cos(-phi))*mm;
	double y_arm = ( 0 + r*sin(theta)*sin(-phi))*mm;
	double z_hight = (115.43 + r*cos(theta))*mm;

	G4ThreeVector translate = G4ThreeVector(x_arm, y_arm, z_hight); 
	rot1.rotateX(0. *deg);
	rot2.rotateY(rot_y);
        if (momid % 2 == 0) {
	    rot3.rotateZ(30.*deg);
        } else {
            // make solid for counter-clockwise distribution
	    rot3.rotateZ((30 - 60)*deg);
        }
	G4RotationMatrix *rot = new G4RotationMatrix(rot1*rot2*rot3);
	//infill gel pad between glass and cathode
	G4IntersectionSolid *solid
	  = new G4IntersectionSolid("solid", solidInside, 
				    solid1, rot, translate);
	return solid;


    } else if ( id < 7 ) { //4 to 6 
	//gel pad for pmt
	double x_arm = (60.948 + r*sin(theta)*cos(-phi))*mm;
	double y_arm = ( 0 + r*sin(theta)*sin(-phi))*mm;
	double z_hight = (55.431 + r*cos(theta))*mm;
	G4ThreeVector translate = G4ThreeVector(x_arm, y_arm, z_hight); 
	translate.rotateZ(-60*deg);
	rot1.rotateX(0. *deg);
	rot2.rotateY(rot_y);
        if (momid % 2 == 0) {
	    rot3.rotateZ(90*deg);
        } else {
            // make solid for counter-clockwise distribution
	    rot3.rotateZ((90.-60)*deg);
        }
	G4RotationMatrix *rot = new G4RotationMatrix(rot1*rot2*rot3);
	G4IntersectionSolid *solid
	  = new G4IntersectionSolid("solid", solidInside, 
				    solid1, rot, translate);
	return solid;

    }
    
} 

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4MEggGel::Cabling()
{
  //If you set the Gel as SD, use this code.

  /*
  J4MEggGelSD* sd = new J4MEggGelSD(this);
  Register(sd);
  SetSD(sd);
  */

} 

//=====================================================================
// Install Gels in half inside
//=====================================================================
void J4MEggGel::InstallIn(J4VComponent         *,
                          G4RotationMatrix     *, 
                          const G4ThreeVector  &) 
{ 
  Assemble();			// You MUST call Assemble(); at first. 
  // Placement function into mother object ------//
 
  G4RotationMatrix rot1, rot2, rot3;
  G4ThreeVector trans = G4ThreeVector(0, 0, 0 *mm);
  int id = GetMyID();
  int momid = GetMother()->GetMyID();

  if (id == 0) {
      SetPVPlacement();
  
  } else { 

      rot1.rotateX(0.*deg);
      rot2.rotateY(0.*deg);
      if ( id < 4) { //1 to 3
          rot3.rotateZ(120*(id-1)*deg);
      } else if (id < 7) { //4 to 6
          rot3.rotateZ(120*(id-4)*deg);
      } 
      G4RotationMatrix *rot = new G4RotationMatrix(rot1*rot2*rot3);
      SetPVPlacement(rot, trans);
  }

  Cabling();  

}


//* Draw  --------------------------------------------------------
void J4MEggGel::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4MEggGel::Print() const
{
}

	
	
