// $Id: J4LOMGeomFunctions.cc,v 1.2 2007/03/13 17:29:14 hoshina Exp $
/**
* @file J4LOMSolidMaker.cc
* @brief namespace that provides geometory functions to generate G4Solids
* @date 2021/04/11
* @note many numbers are hard coded, if you want to change it on the fly move these parameters to J4LOMParameterList.
* (Update Record)
*	2021/04/11  K.Hoshina	collected functions from each detector classes
*/

#include "J4LOMSolidMaker.hh"
#include "J4GeomFunctions.hh"
#include "G4Sphere.hh"
#include "G4Cons.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "J4UnionSolid.hh"
#include "G4UserLimits.hh"
#include "G4Polycone.hh"
#include "G4SubtractionSolid.hh"
#include "G4SystemOfUnits.hh"

G4VSolid * J4LOMSolidMaker::fLOMOuterSolid = 0;
G4VSolid * J4LOMSolidMaker::fLOMInnerSolid = 0;
G4VSolid * J4LOMSolidMaker::fLOMHarnessSolid= 0;


//////////////////////////////////////////////////////////////////////////////////////
/// get glass outer shape(solid). 
//////////////////////////////////////////////////////////////////////////////////////
G4VSolid* J4LOMSolidMaker::GetLOMOuterSolid()
{
   if (!fLOMOuterSolid) {
       CreateLOMOuterSolid();
   }

   return fLOMOuterSolid;

}

//////////////////////////////////////////////////////////////////////////////////////
/// get glass inner shape(solid). 
//////////////////////////////////////////////////////////////////////////////////////
G4VSolid* J4LOMSolidMaker::GetLOMInnerSolid()
{
   if (!fLOMInnerSolid) {
       CreateLOMInnerSolid();
   }

   return fLOMInnerSolid;

}



//////////////////////////////////////////////////////////////////////////////////////
/// get harness.
/// it will be used to form Gel shape, by subtructing it
/// from LOMInnerSolid.
//////////////////////////////////////////////////////////////////////////////////////
G4VSolid* J4LOMSolidMaker::GetLOMHarnessSolid()
{
   if (!fLOMHarnessSolid) {
       CreateLOMHarnessSolid();
   }
   return fLOMHarnessSolid;
}





//////////////////////////////////////////////////////////////////////////////////////
/// Creating glass outer shape(solid). 
/// Parameters are hardcoded. 
//////////////////////////////////////////////////////////////////////////////////////
void J4LOMSolidMaker::CreateLOMOuterSolid()
{

    G4double rmin   = 0*mm;
    G4double rmax   = 161.0*mm;
    G4double sphi   = 0. *degree;
    G4double dphi   = 2*M_PI;
    G4double stheta = 0. *degree;
    G4double dtheta = 180 *degree;

	G4Cons *cons = new G4Cons("cons", rmin, rmax, rmin, rmax, 210*mm/2, 0, 2*M_PI);


    G4Sphere *sphere = new G4Sphere("sphere",rmin, rmax, 
				     sphi, dphi, stheta, dtheta);
    
    G4ThreeVector centerOfSphere1(0, 0,  105*mm); 
    G4ThreeVector centerOfSphere2(0, 0, -105*mm); 
    

	G4RotationMatrix* rot = new G4RotationMatrix();
	rot->rotateY(180*deg);

    J4UnionSolid *solid1
      = new J4UnionSolid("solid1", cons, sphere, 0, centerOfSphere1);
    
    J4UnionSolid *solid
      = new J4UnionSolid("solid", solid1, sphere, rot, centerOfSphere2);
		

    fLOMOuterSolid = solid;

}

//////////////////////////////////////////////////////////////////////////////////////
/// Creating LOM's glass inner shape(solid). 
/// Parameters are hardcoded. if you want to change them on the fly
/// use J4LOMParameterList.
//////////////////////////////////////////////////////////////////////////////////////
void J4LOMSolidMaker::CreateLOMInnerSolid()
{
    G4double rmin   = 0*mm;
    G4double rmax   = 145.0*mm;
    G4double sphi   = 0. *degree;
    G4double dphi   = 2*M_PI;
    G4double stheta = 0. *degree;
    G4double dtheta = 180 *degree;

	G4Cons *cons = new G4Cons("cons", rmin, rmax, rmin, rmax, 210*mm/2, 0, 2*M_PI);


    G4Sphere *sphere = new G4Sphere("sphere",rmin, rmax, 
				     sphi, dphi, stheta, dtheta);
    
    G4ThreeVector centerOfSphere1(0, 0,  105*mm); 
    G4ThreeVector centerOfSphere2(0, 0, -105*mm); 
    
	G4RotationMatrix* rot = new G4RotationMatrix();
	rot->rotateY(180*deg);

    J4UnionSolid *solid1
      = new J4UnionSolid("solid1", cons, sphere, 0, centerOfSphere1);
    
    J4UnionSolid *solid
      = new J4UnionSolid("solid", solid1, sphere, rot, centerOfSphere2);
    fLOMInnerSolid = solid;
}

//////////////////////////////////////////////////////////////////////////////////////
/// Creating LOM's harness
/// Parameters are hardcoded. if you want to change them on the fly
/// use J4LOMParameterList.
//////////////////////////////////////////////////////////////////////////////////////
void J4LOMSolidMaker::CreateLOMHarnessSolid()
{
 
    //G4double rmin   = 150. *mm;
    G4double rmin   = 165. *mm;
    G4double rmax   = rmin + 5. *mm;
    G4double sphi   = 0. *deg;
    G4double dphi   = 2*M_PI;
    G4double stheta = 0.5*M_PI - 0.187765 *rad;  //3.1cm
    G4double dtheta = 2. * 0.187765 *rad;

    // MakeSolid ----------//
    fLOMHarnessSolid = new G4Sphere ("LOMHarness",
                                   rmin, rmax,
                                   sphi, dphi,
                                   stheta, dtheta);

}

