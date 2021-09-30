// $Id: J4LOMParameterList.cc,v 1.3 2007/04/02 23:25:33 hoshina Exp $
//*************************************************************************
//* --------------------
//* J4LOMParameterList
//* --------------------
//* (Description)
//* 	Parameter list for module parts
//*
//* (Update Record)
//*	2003/03/18  K.Hoshina	Original version.
//*************************************************************************

#include "J4LOMParameterList.hh"
#include <fstream>

using namespace std;

//GVisAttributes::SetForceAuxEdgeVisible(1);

J4LOMParameterList * J4LOMParameterList::fgInstance = 0;

//=====================================================================
//* public getter -----------------------------------------------------
J4LOMParameterList* J4LOMParameterList::GetInstance()
{
   if (!fgInstance) {
      fgInstance = new J4LOMParameterList("LOM");
   }
   return fgInstance;
}


void J4LOMParameterList::Initialize()
{
   SetParameters();
}

//=====================================================================
//* protected constructor ---------------------------------------------

J4LOMParameterList::J4LOMParameterList(const G4String& name)
                  :J4VParameterList(name)
{
}

//=====================================================================
//* destructor -------------------------------------------------------

J4LOMParameterList::~J4LOMParameterList()
{
   fgInstance = 0;
}

//=====================================================================
//* SetParameters -----------------------------------------------------
void J4LOMParameterList::SetParameters()
{
   fMainBoardRmin = 86.0/2 *mm;
   fMainBoardRmax = 246./2 *mm;
   fMainBoardDz = 1.6/2 *mm;
   fMainBoardLocation.set(0, 0, (55. + 1.6/2) *mm);

   fHVBoardRmin = 0. *mm;
   fHVBoardRmax = 125./2 *mm;
   fHVBoardDz   = 1.6/2 *mm;
   fHVBoardLocation.set(0, 0, (13.4 + 1.6/2) *mm);
}

//=====================================================================
J4LOMParameterList::PMTPlacement J4LOMParameterList::CalcPMTPlacement(G4int id)
{

   
   PMTPlacement loc;
   G4RotationMatrix rot1, rot2, rot3;
   G4ThreeVector trans(0., 0., 0. *mm);
   
   double offset_center_frombase = 41*mm;
   double offset_tail = 9.5*mm;
   double offset_center = offset_center_frombase+offset_tail;
 
   double global_z_offset = 25*mm;
 
   if (id == 0) {
	   trans.setZ( 110.*mm - offset_tail + offset_center + global_z_offset );

	   loc.first = nullptr;
	   loc.second = trans;
   } else if (id < 5) {  // upper hemis. middle layer
   
	   double tilt_ang_deg = 45*deg;
	   double tilt_ang = M_PI*(tilt_ang_deg/deg)/180.0;
	   double z_hight = 70*mm + offset_center*cos(tilt_ang)+global_z_offset;
	   double dist_from_axis = 35.0 *mm + offset_center*sin(tilt_ang); 
     
	   G4ThreeVector translate = G4ThreeVector(dist_from_axis, 0, z_hight);
	   translate.rotateZ(90.0*deg*(id-1));
	   G4RotationMatrix *rot = new G4RotationMatrix();
	   rot->rotateZ(-90*deg*(id-1));
	   rot->rotateY(-tilt_ang_deg);
 
	   loc.first = rot;
	   loc.second = translate;
   } else if (id < 9) { //5 to 8
	   double tilt_ang_deg = 50*deg;
	   double tilt_ang = M_PI*(tilt_ang_deg/deg)/180.0;
	   double z_hight = 0.0*mm + offset_center*cos(tilt_ang)+global_z_offset;
	   double dist_from_axis = 35.0 *mm + offset_center*sin(tilt_ang); 
 	
	   G4ThreeVector translate = G4ThreeVector(dist_from_axis, 0, z_hight);
	   translate.rotateZ(90.0*deg*(id-5)+45*deg);
	   G4RotationMatrix *rot = new G4RotationMatrix();
	   rot->rotateZ(-90*deg*(id-5)-45*deg);
	   rot->rotateY(-tilt_ang_deg);
	   
	   loc.first = rot;
	   loc.second = translate;
 
   } else if (id < 13) {  // lower hemis. 
 	
	   double tilt_ang_deg = 50*deg;
	   double tilt_ang = M_PI*(tilt_ang_deg/deg)/180.0;
	   double z_hight = 0.0*mm - offset_center*cos(tilt_ang)-global_z_offset;
	   double dist_from_axis = 35.0 * mm + offset_center*sin(tilt_ang); 
	   G4ThreeVector translate = G4ThreeVector(dist_from_axis, 0, z_hight);
	   translate.rotateZ(90.0*deg*(id-9)+45*deg);
	   G4RotationMatrix *rot = new G4RotationMatrix();
	   rot->rotateZ(-90*deg*(id-9)-45*deg);
	   rot->rotateY(tilt_ang_deg-180*deg);
	   loc.first = rot;
	   loc.second = translate;
   } else if (id < 17) { 
	   double tilt_ang_deg = 45*deg;
	   double tilt_ang = M_PI*(tilt_ang_deg/deg)/180.0;
	   double z_hight = -70*mm - offset_center*cos(tilt_ang)-global_z_offset;
	   double dist_from_axis = 35.0 * mm + offset_center*sin(tilt_ang); 
	   G4ThreeVector translate = G4ThreeVector(dist_from_axis, 0, z_hight);
	   translate.rotateZ(90.0*deg*(id-13));
	   G4RotationMatrix *rot = new G4RotationMatrix();
	   rot->rotateZ(-90*deg*(id-13));
	   rot->rotateY(tilt_ang_deg-180*deg);
	   loc.first = rot;
	   loc.second = translate;
 	
   } else if (id == 17) {
	   rot2.rotateY(180*deg);
	   trans.setZ( -110*mm + offset_tail - offset_center -global_z_offset);
	   G4RotationMatrix *rot = new G4RotationMatrix(rot2);
	   loc.first = rot;
	   loc.second = trans;
   }    
   
   
 
 
 
   //typedef std::pair<G4RotationMatrix *, G4ThreeVector>  PMTPlacement;
 

   return loc;

}


