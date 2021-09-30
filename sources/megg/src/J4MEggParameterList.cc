// $Id: J4MEggParameterList.cc,v 1.3 2007/04/02 23:25:33 hoshina Exp $
//*************************************************************************
//* --------------------
//* J4MEggParameterList
//* --------------------
//* (Description)
//* 	Parameter list for module parts
//*
//* (Update Record)
//*	2003/03/18  K.Hoshina	Original version.
//*************************************************************************

#include "J4MEggParameterList.hh"
#include <fstream>

using namespace std;

//GVisAttributes::SetForceAuxEdgeVisible(1);

J4MEggParameterList * J4MEggParameterList::fgInstance = 0;

//=====================================================================
//* public getter -----------------------------------------------------
J4MEggParameterList* J4MEggParameterList::GetInstance()
{
   if (!fgInstance) {
      fgInstance = new J4MEggParameterList("MEgg");
   }
   return fgInstance;
}


void J4MEggParameterList::Initialize()
{
   SetParameters();
}

//=====================================================================
//* protected constructor ---------------------------------------------

J4MEggParameterList::J4MEggParameterList(const G4String& name)
                  :J4VParameterList(name)
{
}

//=====================================================================
//* destructor -------------------------------------------------------

J4MEggParameterList::~J4MEggParameterList()
{
   fgInstance = 0;
}

//=====================================================================
//* SetParameters -----------------------------------------------------
void J4MEggParameterList::SetParameters()
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
J4MEggParameterList::PMTPlacement J4MEggParameterList::CalcUpperPMTPlacement(G4int momid, G4int myid)
{
   G4ThreeVector trans(0., 0., 0. *mm);
   PMTPlacement loc;

   if (myid == 0 ) {
       trans.setZ((148.363 + 49.5)*mm);
       loc.first = 0;
       loc.second = trans;
       return loc;
   }

   G4double z_hight;
   G4double tilt_ang = 15*deg;
   G4double x_arm = 60.948 *mm;
   G4double rot_y = -(90*deg - tilt_ang);
   G4RotationMatrix rot1, rot2, rot3;

   if (myid < 4) { //1 to 3

      z_hight = 115.43 *mm;
      trans = G4ThreeVector(x_arm, 0, z_hight);
      trans.rotateZ(0-120*(myid-1)*deg);
      rot1.rotateX(0. *deg);
      rot2.rotateY(rot_y);
      G4double zrot = (30. +120*(myid-1))*deg;
      G4double zrot_down = (-30. +120*(myid-1))*deg; // 30-60=-30
      if (momid % 2 == 0) {
          rot3.rotateZ(zrot);
      } else {
          rot3.rotateZ(zrot_down);
      }
      G4RotationMatrix *rot = new G4RotationMatrix(rot1*rot2*rot3);
      loc.first = rot;
      loc.second = trans;

   } else if (myid < 7) { //4 to 6

      z_hight = 55.431 *mm;
      trans = G4ThreeVector(x_arm, 0, z_hight);
      trans.rotateZ((-60-120*(myid-4))*deg);
      rot2.rotateY(rot_y);
      G4double zrot = (90. +120*(myid-4))*deg;
      G4double zrot_down = (30. +120*(myid-4))*deg; // 90-60=30
      if (momid % 2 == 0) {
          rot3.rotateZ(zrot);
      } else {
          rot3.rotateZ(zrot_down);
      }
      G4RotationMatrix *rot = new G4RotationMatrix(rot1*rot2*rot3);
      loc.first = rot;
      loc.second = trans;
   }

   return loc;

}


