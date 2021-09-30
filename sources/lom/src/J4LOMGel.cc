// $Id: J4LOMGel.cc,v 1.2 2007/03/13 17:29:14 hoshina Exp $
//*************************************************************************
//* --------------------
//* J4LOMGel
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


#include "J4LOMGel.hh"
#include "J4LOMGelSD.hh"
#include "J4LOMInside.hh"
#include "J4EggSolidMaker.hh"
#include "J4PartsParameterList.hh"
#include "J4PartsMaterialStore.hh"
#include "J4LOMParameterList.hh"
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


G4String J4LOMGel::fFirstName("Gel");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4LOMGel::J4LOMGel(J4VDetectorComponent* parent,
                                    G4int  nclones,
                                    G4int  nbrothers, 
                                    G4int  me,
                                    G4int  copyno ) :
  	   J4VDetectorComponent("LOM", fFirstName, parent, nclones,
                                  nbrothers, me, copyno)
{   
  thickness_reflector = -1;  
}


//=====================================================================
//* destructor --------------------------------------------------------

J4LOMGel::~J4LOMGel()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4LOMGel::Assemble() 
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

G4VSolid* J4LOMGel::CreateGelSolid()
{
  
    G4Cons *cons;
	


	int id = GetMyID();
    
    J4PartsParameterList *list = J4PartsParameterList::GetInstance();

    
	G4VSolid *solidInside = InsideSolid;
    G4VSolid *solidInsideMiddle = InsideSolid;
 
  
	const double r_PMT_envelope = 51.0*mm;
	const double gelheight = 80.0*mm;

   
	// r is an offset between center of gel and PMT (cathode) origin
	double r = gelheight/2+sqrt(65.0*65.0-51.0*51.0)*mm;

    G4ThreeVector centerOfPMT(0.,0., -r);
    //make gel pad
 
    //alpha is opening angle for the pad 
    //double alpha = 61*deg; //best design
    double alpha;
   
	if(id==0||id==17) alpha = 55*deg; //best design
	else if(5<=id && id<=12) alpha = 80*deg;
	else alpha = 85*deg;


    double top = (gelheight/tan(alpha)) + r_PMT_envelope; 


	G4VSolid *solid1;
   
	if(thickness_reflector<0){
		cons = new G4Cons("cons", 0, r_PMT_envelope, 
			      0, top, gelheight/2, 0, 2*M_PI); 
	
		solid1 = new G4SubtractionSolid("solid1", cons, PMTCathodeSolid, 0, centerOfPMT);
	}else{
		cons = new G4Cons("cons", r_PMT_envelope, r_PMT_envelope+thickness_reflector, 
			      top, top+thickness_reflector, gelheight/2, 0, 2*M_PI); 
		solid1 = cons;
	}


    
    
    //--------------------------------------

	double offset_center_frombase = 41*mm;
	double offset_tail = 9.5*mm;
	double offset_center = offset_center_frombase+offset_tail;
	double global_z_offset = 25*mm;


    G4RotationMatrix rot1, rot2, rot3;


    if (id==0){
      //gel pad for pmt0    
      G4ThreeVector trans = G4ThreeVector(0,0,0*mm);
      trans.setZ(110.0*mm - offset_tail + offset_center + global_z_offset + r);
 		
	  G4IntersectionSolid *solid = new G4IntersectionSolid("solid", solidInside, solid1, 0, trans);
      rmat = nullptr;
	  return solid;
      
    } else if (id < 5) {  // upper hemis. middle layer
      double tilt_ang_deg = 45*deg;
      double tilt_ang = M_PI*(tilt_ang_deg/deg)/180.0;
      double z_hight = 70*mm + offset_center*cos(tilt_ang)+global_z_offset;
      double dist_from_axis = 35.0 *mm + offset_center*sin(tilt_ang); 
      
      G4ThreeVector translate = G4ThreeVector(0,0,r);
	  translate.rotateY(tilt_ang_deg);
	  translate += G4ThreeVector(dist_from_axis, 0, z_hight);
	  translate.rotateZ(90.0*deg*(id-1));

      G4RotationMatrix *rot = new G4RotationMatrix();
      rot->rotateZ(-90*deg*(id-1));
      rot->rotateY(-tilt_ang_deg);
	  
      rmat = rot;
      G4IntersectionSolid *solid 
		  = new G4IntersectionSolid("solid", solidInside, solid1, rot, translate);
      return solid;
	  
    } else if (id < 9) { //5 to 8
       
      double tilt_ang_deg = 50*deg;
      double tilt_ang = M_PI*(tilt_ang_deg/deg)/180.0;
      double z_hight = 0.0*mm + offset_center*cos(tilt_ang)+global_z_offset;
      double dist_from_axis = 35.0 *mm + offset_center*sin(tilt_ang); 
      
      G4ThreeVector translate = G4ThreeVector(0,0,r);
	  translate.rotateY(tilt_ang);
      translate += G4ThreeVector(dist_from_axis, 0, z_hight);
	  translate.rotateZ(90.0*deg*(id-5)+45*deg);
      
      G4RotationMatrix *rot = new G4RotationMatrix();
      rot->rotateZ(-90*deg*(id-5)-45*deg);
      rot->rotateY(-tilt_ang_deg);
      rmat = rot;
      G4IntersectionSolid *solid 
		  = new G4IntersectionSolid("solid", solidInside, solid1, rot, translate);
      return solid;

    } else if (id < 13) {  // lower hemis. 
      
      double tilt_ang_deg = 50*deg;
      double tilt_ang = M_PI*(tilt_ang_deg/deg)/180.0;
      double z_hight = 0.0*mm - offset_center*cos(tilt_ang)-global_z_offset;
      double dist_from_axis = 35.0 * mm + offset_center*sin(tilt_ang); 
      
      G4ThreeVector translate = G4ThreeVector(0,0,-r);
	  translate.rotateY(-tilt_ang);
      translate += G4ThreeVector(dist_from_axis, 0, z_hight);
	  translate.rotateZ(90.0*deg*(id-9)+45*deg);
      
      G4RotationMatrix *rot = new G4RotationMatrix();
      rot->rotateZ(-90*deg*(id-9)-45*deg);
      rot->rotateY(tilt_ang_deg-180*deg);
      rmat = rot;
      G4IntersectionSolid *solid 
		  = new G4IntersectionSolid("solid", solidInside, solid1, rot, translate);
      return solid;

    } else if (id < 17) { 
     
      double tilt_ang_deg = 45*deg;
      double tilt_ang = M_PI*(tilt_ang_deg/deg)/180.0;
      double z_hight = -70.0*mm - offset_center*cos(tilt_ang)-global_z_offset;
      double dist_from_axis = 35.0 * mm + offset_center*sin(tilt_ang); 
      
      G4ThreeVector translate = G4ThreeVector(0,0,-r);
	  translate.rotateY(-tilt_ang);
      translate += G4ThreeVector(dist_from_axis, 0, z_hight);
      translate.rotateZ(90.0*deg*(id-13));
      
      G4RotationMatrix *rot = new G4RotationMatrix();
      rot->rotateZ(-90*deg*(id-13));
      rot->rotateY(tilt_ang_deg-180*deg);
      rmat = rot;
      G4IntersectionSolid *solid 
		  = new G4IntersectionSolid("solid", solidInside, solid1, rot, translate);
     
      return solid;

    } else if ( id == 17 ) {
      G4ThreeVector trans = G4ThreeVector(0,0,0*mm);
      trans.setZ(-(110*mm -offset_tail + offset_center + global_z_offset + r));
	
	  G4RotationMatrix *rot = new G4RotationMatrix();
	  rot->rotateY(180*deg);
	  G4IntersectionSolid *solid = new G4IntersectionSolid("solid", solidInside, solid1, rot, trans);
      rmat = nullptr;
      return solid;
	
    }
    
} 

#if 0
G4VSolid* J4LOMGel::CreateGelSolid()
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
    J4LOMParameterList * megglist = J4LOMParameterList::GetInstance();  
    J4LOMParameterList::PMTPlacement plc = megglist->CalcUpperPMTPlacement(momid, id);
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
#endif

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4LOMGel::Cabling()
{
  //If you set the Gel as SD, use this code.

  /*
  J4LOMGelSD* sd = new J4LOMGelSD(this);
  Register(sd);
  SetSD(sd);
  */

} 

//=====================================================================
// Install Gels in half inside
//=====================================================================
void J4LOMGel::InstallIn(J4VComponent         *,
                          G4RotationMatrix     *, 
                          const G4ThreeVector  &) 
{ 
  Assemble();			// You MUST call Assemble(); at first. 
  // Placement function into mother object ------//
 
  G4RotationMatrix rot1, rot2, rot3;
  G4ThreeVector trans = G4ThreeVector(0, 0, 0 *mm);
  int id = GetMyID();
  int momid = GetMother()->GetMyID();

  SetPVPlacement();
  Cabling();  



}


//* Draw  --------------------------------------------------------
void J4LOMGel::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4LOMGel::Print() const
{
}

	
	
