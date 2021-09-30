// $Id: J4EggGeomFunctions.cc,v 1.2 2007/03/13 17:29:14 hoshina Exp $
/**
* @file J4EggSolidMaker.cc
* @brief namespace that provides geometory functions to generate G4Solids
* @date 2021/04/11
* @note many numbers are hard coded, if you want to change it on the fly move these parameters to J4EggParameterList.
* (Update Record)
*	2021/04/11  K.Hoshina	collected functions from each detector classes
*/

#include "J4EggSolidMaker.hh"
#include "J4GeomFunctions.hh"
#include "G4Sphere.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "J4UnionSolid.hh"
#include "G4UserLimits.hh"
#include "G4Polycone.hh"
#include "G4SubtractionSolid.hh"
#include "G4SystemOfUnits.hh"

G4VSolid * J4EggSolidMaker::fEggOuterSolid = 0;
G4VSolid * J4EggSolidMaker::fEggInnerSolid = 0;
G4VSolid * J4EggSolidMaker::fHalfEggInnerSolid = 0;
G4VSolid * J4EggSolidMaker::fHalfEggInnerTubSolid = 0;
G4VSolid * J4EggSolidMaker::fEggHarnessSolid= 0;

//////////////////////////////////////////////////////////////////////////////////////
/// get glass outer shape(solid). 
//////////////////////////////////////////////////////////////////////////////////////
G4VSolid* J4EggSolidMaker::GetEggOuterSolid()
{
   if (!fEggOuterSolid) {
       CreateEggOuterSolid();
   }

   return fEggOuterSolid;

}

//////////////////////////////////////////////////////////////////////////////////////
/// get glass inner shape(solid). 
//////////////////////////////////////////////////////////////////////////////////////
G4VSolid* J4EggSolidMaker::GetEggInnerSolid()
{
   if (!fEggInnerSolid) {
       CreateEggInnerSolid();
   }

   return fEggInnerSolid;

}

//////////////////////////////////////////////////////////////////////////////////////
/// get half of glass inner shape(solid). 
//////////////////////////////////////////////////////////////////////////////////////
G4VSolid* J4EggSolidMaker::GetHalfEggInnerSolid()
{
   if (!fHalfEggInnerSolid) {
       CreateEggInnerSolid();
   }

   return fHalfEggInnerSolid;

}



//////////////////////////////////////////////////////////////////////////////////////
/// get glass inner torus.
/// it will be used to form Gel shape, by subtructing it
/// from EggInnerSolid.
//////////////////////////////////////////////////////////////////////////////////////
G4VSolid* J4EggSolidMaker::GetHalfEggInnerTubSolid()
{
   if (!fHalfEggInnerTubSolid) {
       CreateEggInnerSolid();
   }

   return fHalfEggInnerTubSolid;

}

//////////////////////////////////////////////////////////////////////////////////////
/// get harness.
/// it will be used to form Gel shape, by subtructing it
/// from EggInnerSolid.
//////////////////////////////////////////////////////////////////////////////////////
G4VSolid* J4EggSolidMaker::GetEggHarnessSolid()
{
   if (!fEggHarnessSolid) {
       CreateEggHarnessSolid();
   }
   return fEggHarnessSolid;
}





//////////////////////////////////////////////////////////////////////////////////////
/// Creating glass outer shape(solid). 
/// Parameters are hardcoded. 
//////////////////////////////////////////////////////////////////////////////////////
void J4EggSolidMaker::CreateEggOuterSolid()
{

    G4int    nsegments1 = 30;
    G4double sphere_rmax   = 156.0 *mm;
    G4double sphere_dtheta = 45.7191 *degree;
    G4double sphere_transform_z = 111.0 * mm;

    //radius of small spindle torus sphere
    G4double torus1_r = 85. * mm; 

    // distance from center of torus1 to z-axis
    G4double centerOfTorus1_r = 50.8307 * mm; 

    G4int    nsegments2 = 40;

    //radius of large spindle torus sphere
    G4double torus2_r = 1000. * mm; 

    // distance from center of torus2_r to z-axis (signed)
    G4double centerOfTorus2_r = -850.0 * mm; 
    G4double centerOfTorus2_z = 0.1676 * mm;

    //minimum z shift from z=0 in positive z direction
    G4double torus2zmin = 24.9334 * mm; 

    //maximum z shift from z=0 in positive z direction
    G4double torus2zmax = 175.4714 * mm; 

    G4double torus_z0 = 151.0 * mm;

    G4double torus_transform_z = 160.5706 *mm;

    fEggOuterSolid = J4GeomFunctions::CreateEggSolid(
                               nsegments1, 
                               sphere_rmax, sphere_dtheta,
                               sphere_transform_z, torus1_r,
                               centerOfTorus1_r, 
                               nsegments2, torus2_r,
                               centerOfTorus2_r, centerOfTorus2_z,
                               torus2zmin, torus2zmax, torus_z0,
                               torus_transform_z);

}

//////////////////////////////////////////////////////////////////////////////////////
/// Creating Egg's glass inner shape(solid). 
/// Parameters are hardcoded. if you want to change them on the fly
/// use J4EggParameterList.
//////////////////////////////////////////////////////////////////////////////////////
void J4EggSolidMaker::CreateEggInnerSolid()
{
    G4int    nsegments1 = 300;
    G4double sphere_rmax   = 136.0 *mm;
    G4double sphere_dtheta = 46.7281 *degree;
    G4double sphere_transform_z = 121.0 * mm;

    //radius of small spindle torus sphere
    G4double torus1_r = 65. * mm; 

    // distance from center of torus1 to z-axis
    G4double centerOfTorus1_r = 51.3850 * mm; 

    G4int    nsegments2 = 200;
    //radius of large spindle torus sphere
    G4double torus2_r = 1150. * mm; 

    // distance from center of torus2_r to z-axis
    G4double centerOfTorus2_r = -1019.9992 * mm; 
    G4double centerOfTorus2_z = -1.3972 * mm;

    //minimum z shift from z=0 in positive z direction
    G4double torus2_zmin = 6.00909 * mm; 
    //G4double torus2_zmin = 0 * mm; 

    //maximum z shift from z=0 in positive z direction
    G4double torus2_zmax = 180.2726 * mm; 

    G4double torus2_z0 = 130.0 * mm;

    G4double torus1_transform_z = 170.7198 *mm;

    fEggInnerSolid = J4GeomFunctions::CreateEggSolid(
                               nsegments1,
                               sphere_rmax, sphere_dtheta,
                               sphere_transform_z, torus1_r,
                               centerOfTorus1_r, 
                               nsegments2, torus2_r,
                               centerOfTorus2_r, centerOfTorus2_z,
                               torus2_zmin, torus2_zmax, torus2_z0,
                               torus1_transform_z);

    // generate half degg solid (for subtruction for Egg gel)
    fHalfEggInnerSolid = J4GeomFunctions::CreateHalfEggSolid(
                               nsegments1,
                               sphere_rmax, sphere_dtheta,
                               sphere_transform_z, torus1_r,
                               centerOfTorus1_r, 
                               nsegments2, torus2_r,
                               centerOfTorus2_r, centerOfTorus2_z,
                               torus2_zmin, torus2_zmax, torus2_z0,
                               torus1_transform_z);

    // generate middle torus (for subtruction for Egg gel)
    // use 11th value for edge 

    // copied from J4GeomFunctions::CreateEggTorus2
    G4double zminrelative = torus2_zmin - centerOfTorus2_z; //minimum z shift from center of torus in positive z direction
    G4double zmaxrelative = torus2_zmax - centerOfTorus2_z; //maximum z shift from center of torus in positive z direction
    G4double step2 = (zmaxrelative-zminrelative)/(nsegments2-1);
    std::vector<G4double> tempZ2, tempOuter2;

    J4GeomFunctions::FillTorusSurface(nsegments2, step2, torus2_r, torus2_zmax, centerOfTorus2_z, centerOfTorus2_r,
                                      tempZ2, tempOuter2);

    G4int index = 10;
    G4double zmax_for_tub = tempZ2[index];   
    std::cerr << "zmax_for_tub = " << zmax_for_tub << G4endl;
     
    fHalfEggInnerTubSolid = J4GeomFunctions::CreateEggTorus2(
                               nsegments2-index, torus2_r,
                               centerOfTorus2_r, centerOfTorus2_z,
                               torus2_zmin, zmax_for_tub,
                               torus2_z0);

}

//////////////////////////////////////////////////////////////////////////////////////
/// Creating Egg's harness
/// Parameters are hardcoded. if you want to change them on the fly
/// use J4EggParameterList.
//////////////////////////////////////////////////////////////////////////////////////
void J4EggSolidMaker::CreateEggHarnessSolid()
{
 
    //G4double rmin   = 150. *mm;
    G4double rmin   = 165. *mm;
    G4double rmax   = rmin + 5. *mm;
    G4double sphi   = 0. *deg;
    G4double dphi   = 2*M_PI;
    G4double stheta = 0.5*M_PI - 0.187765 *rad;  //3.1cm
    G4double dtheta = 2. * 0.187765 *rad;

    // MakeSolid ----------//
    fEggHarnessSolid = new G4Sphere ("EggHarness",
                                   rmin, rmax,
                                   sphi, dphi,
                                   stheta, dtheta);

}

