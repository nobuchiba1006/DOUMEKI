// $Id: J4PMTSolidMaker.cc,v 1.2 2007/03/13 17:29:14 hoshina Exp $
/**
* @file J4PMTSolidMaker.cc
* @brief namespace that provides geometory functions to generate G4Solids
* @date 2021/04/11
* @note many numbers are hard coded, if you want to change it on the fly move these parameters to J4PartsParameterList.
* (Update Record)
*	2021/04/11  K.Hoshina	collected functions from each detector classes
*/

#include "J4PMTSolidMaker.hh"
#include "J4GeomFunctions.hh"
#include "G4Sphere.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "J4UnionSolid.hh"
#include "G4UserLimits.hh"
#include "G4Polycone.hh"
#include "G4Cons.hh"
#include "G4Tubs.hh"
#include "G4SubtractionSolid.hh"
#include "G4SystemOfUnits.hh"

G4VSolid * J4PMTSolidMaker::f8inchPMTSolid;
G4VSolid * J4PMTSolidMaker::f3inchPMTSolid;
G4VSolid * J4PMTSolidMaker::f3inchPMTBaseSolid;
G4VSolid * J4PMTSolidMaker::f3inchPMTCathodeSolid;
G4VSolid * J4PMTSolidMaker::f4inchPMTSolid;
G4VSolid * J4PMTSolidMaker::f4inchPMTBaseSolid;
G4VSolid * J4PMTSolidMaker::f4inchPMTCathodeSolid;

//////////////////////////////////////////////////////////////////////////////////////
G4VSolid* J4PMTSolidMaker::Get8inchPMTSolid()
{
   if (!f8inchPMTSolid) {
       Create8inchPMTSolid();
   }

   return f8inchPMTSolid;
}

//////////////////////////////////////////////////////////////////////////////////////
G4VSolid* J4PMTSolidMaker::Get4inchPMTSolid()
{
   if (!f4inchPMTSolid) {
       Create4inchPMTSolid();
   }

   return f4inchPMTSolid;
}

//////////////////////////////////////////////////////////////////////////////////////
G4VSolid* J4PMTSolidMaker::Get4inchPMTBaseSolid()
{
   if (!f4inchPMTSolid) {
       Create4inchPMTSolid();
   }

   return f4inchPMTBaseSolid;
}



//////////////////////////////////////////////////////////////////////////////////////
G4VSolid* J4PMTSolidMaker::Get4inchPMTCathodeSolid()
{
   if (!f4inchPMTCathodeSolid) {
       Create4inchPMTSolid();
   }

   return f4inchPMTCathodeSolid;
}
//////////////////////////////////////////////////////////////////////////////////////
G4VSolid* J4PMTSolidMaker::Get3inchPMTSolid()
{
   if (!f3inchPMTSolid) {
       Create3inchPMTSolid();
   }

   return f3inchPMTSolid;
}

//////////////////////////////////////////////////////////////////////////////////////
G4VSolid* J4PMTSolidMaker::Get3inchPMTBaseSolid()
{
   if (!f3inchPMTSolid) {
       Create3inchPMTSolid();
   }

   return f3inchPMTBaseSolid;
}
//////////////////////////////////////////////////////////////////////////////////////
G4VSolid* J4PMTSolidMaker::Get3inchPMTCathodeSolid()
{
   if (!f3inchPMTCathodeSolid) {
       Create3inchPMTSolid();
   }

   return f3inchPMTCathodeSolid;
}


///////////////////////////////////////////////////////
///
///
///////////////////////////////////////////////////////
void J4PMTSolidMaker::Create8inchPMTSolid()
{

    G4ThreeVector centerOfPolycone;
    G4ThreeVector centerOfCons; 
    G4ThreeVector centerOfTubs; 
  
    G4double rmin2, rmax2, dz;
    G4double rmin, rmax, sphi, dphi, stheta, dtheta;
    G4double rSmin, rSmax, sSphi, dSphi, sStheta, dStheta;
  
    rSmin   = 0;
    rSmax   = 131.0 * mm;
    dSphi   = 2*M_PI;
    dStheta = 37.6392 *degree;
     
    std::vector<G4double> tempZ, tempInner, tempOuter;

    G4int segment = 100;
  
    G4double sr0 = 57.0894;//radius of spindle torus sphere
    G4double centerOfsr0 = 43.9106; // distance from center of torus sphere to z-axis      
    G4double rplanet = sr0*2./segment; // z length of each planet
  
    //our function is a fixed number+the value of the sphere projection
    //should spread across 2R

    G4double rInner[segment+1], rOuter[segment+1], zPlane[segment+1];

    for (G4int j=0; j<=segment; ++j) {
      tempZ.push_back((sr0 - j*rplanet)*mm);
      tempInner.push_back(0.);
      tempOuter.push_back((centerOfsr0 + sqrt(sr0*sr0-(sr0-j*rplanet)*(sr0-j*rplanet)))*mm);
      //std::cout<< "pmt " <<j<<"  ,  "<<sr0-j*rplanet<<", "<<(centerOfsr0+sqrt(sr0*sr0-(sr0-j*rplanet)*(sr0-j*rplanet)))<<std::endl;
    }
    
    for (G4int i=0; i<=segment; i++) {
      rInner[i] = tempInner[i];
      rOuter[i] = tempOuter[i];
      zPlane[i] = tempZ[i];
    }
    
    G4Polycone* polycone1 = new 
      G4Polycone("polycone1", 0, 2*M_PI, segment+1, zPlane, rInner, rOuter);
    
    std::cout<<"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXxpositive"<<std::endl;
    centerOfPolycone = G4ThreeVector(0, 0, 59.5 *mm);
    centerOfCons = G4ThreeVector(0, 0, (70.4284+33.8363/2-89.) *mm); 
    centerOfTubs = G4ThreeVector(0, 0, -(89.-70.4284/2) *mm); 

    sSphi = 0;
    sStheta = 0;
    G4Sphere *sphere = new G4Sphere("sphere",rSmin, rSmax, 
				      sSphi, dSphi, sStheta, dStheta);
      
    //to create two cons
     
    rmin   = 0;
    rmin2  = 0;
    rmax   = 84.5/2 *mm;
    rmax2  = 160./2 *mm;  
    dz     = 33.8363/2 *mm;
    sphi   = 0;
    dphi   = 2*M_PI;
      
    G4Cons *cons= new G4Cons("cons",rmin, rmax, rmin2, 
			       rmax2, dz, sphi, dphi);
      
    // create two tubs....
      
    rmin   = 0;
    rmax   = 84.5/2 *mm;
    dz     = 70.4284/2 *mm;
    sphi   = 0;
    dphi   = 2*M_PI;
      
    G4Tubs *tubs = new G4Tubs("tubs",rmin, rmax, dz, 
				sphi, dphi);
      
    // to create two PMTs
      
    J4UnionSolid *solid1
	= new J4UnionSolid("solid1", sphere, polycone1, 0, centerOfPolycone);
      
    J4UnionSolid *solid2
	= new J4UnionSolid("solid2", solid1, tubs, 0, centerOfTubs);
      
    f8inchPMTSolid = new J4UnionSolid("solid", solid2, cons, 0, centerOfCons);
     
}

void J4PMTSolidMaker::Create4inchPMTSolid()
{

	// center of PMT is that of photo cathode 
	G4double rmin2, rmax2, dz;
    G4double rmin, rmax, sphi, dphi, stheta, dtheta;
    G4double rSmin, rSmax, sSphi, dSphi, sStheta, dStheta;


	double r_envelope = 51.0 * mm;
    rSmin   = 0;
    rSmax   = 65.0 * mm;
    dSphi   = 2*M_PI;
    dStheta = asin(r_envelope/rSmax)*radian;
	sSphi = 0;
    sStheta = 0;

	//cathode
    G4double cathodethickness = 0.5 * mm;
    G4double rSmin_cathode   = rSmax - cathodethickness;
    f4inchPMTCathodeSolid = new G4Sphere("sphere_cathode",rSmin_cathode, rSmax,
                                    sSphi, dSphi, sStheta, dStheta);

	// PMT full
	G4Sphere *full_sphere = new G4Sphere("sphere_full",rSmin, rSmax, 
				    sSphi, dSphi, sStheta, dStheta);

	// PMT semi
	G4Sphere *semi_sphere = new G4Sphere("sphere_full",rSmin, rSmin_cathode, 
				    sSphi, dSphi, sStheta, dStheta);


	double leng_body = 70*mm;

	G4ThreeVector centerOfCons1(0, 0, leng_body/2-(106.0*mm-rSmax));
    //to create con1   
    rmin   = 0;
    rmin2  = 0;
    rmax2  = 51.9/2 * mm;  
    rmax   = 51.9/2 * mm;
    dz     = leng_body/2;
    sphi   = 0;
    dphi   = 2*M_PI;
    
    G4Cons *cons1 = new G4Cons("cons1",rmin, rmax, rmin2, 
			       rmax2, dz, sphi, dphi);
   
    J4UnionSolid *solid
      = new J4UnionSolid("solid", full_sphere, cons1, 0, centerOfCons1);
    f4inchPMTSolid = solid;
    f4inchPMTBaseSolid  = new J4UnionSolid("PMTBase", semi_sphere,cons1, 0, centerOfCons1);

} 

///////////////////////////////////////////////////////
/// If you change parameters in this function, 
/// do not forget to change parameters in other functions
/// either!
/// Create3inchPMTCathodeSolid()
/// Create3inchPMTBaseSolid()
///////////////////////////////////////////////////////
void J4PMTSolidMaker::Create3inchPMTSolid()
{
    G4double rSmin   = 0;
    G4double rSmax   = 56.77 * mm;
    G4double dSphi   = 2*M_PI;
    G4double dStheta = 60.29 * degree;
    G4double sSphi = 0;
    G4double sStheta = 0;

    //full pmt
    G4Sphere *full_sphere = new G4Sphere("full_sphere",rSmin, rSmax,
                                    sSphi, dSphi, sStheta, dStheta);


    //pmt base
    G4double from0tocathode = 78.11-49.5 *mm;
    G4double costheta = from0tocathode / rSmax; 
    G4double semi_sStheta = acos(costheta);
    G4double dSthetadiff = dStheta - semi_sStheta;
    G4Sphere *semi_sphere = new G4Sphere("semi_sphere",rSmin, rSmax,
                                    sSphi, dSphi, semi_sStheta, dSthetadiff);

    //cathode
    G4double cathodethickness = 0.5 * mm;
    G4double rSmin_cathode   = rSmax - cathodethickness;
    f3inchPMTCathodeSolid = new G4Sphere("sphere",rSmin_cathode, rSmax,
                                    sSphi, dSphi, sStheta, semi_sStheta);


    G4int nsegments = 6;
    G4double rInner[6] = {0, 0, 0, 0, 0, 0};
    G4double rOuter[6], zPlane[6];
    zPlane[0] = -49.5 * mm;
    zPlane[1] = -6.285 * mm;
    zPlane[2] = 4.315 * mm;
    zPlane[3] = 21.715 * mm;
    zPlane[4] = 25.255 * mm;
    zPlane[5] = 27.695 * mm;
    rOuter[0] = 26.5 * mm;
    rOuter[1] = 26.5 * mm;
    rOuter[2] = 30.895 * mm;
    rOuter[3] = 48.221 * mm;
    rOuter[4] = 49.64 * mm;
    rOuter[5] = 49.05 * mm;
  
    G4Polycone* polycone1 = new 
      G4Polycone("polycone1", 0, 2*M_PI, nsegments, zPlane, rInner, rOuter);

    f3inchPMTSolid  = new J4UnionSolid("fullPMT", full_sphere, polycone1, 0, G4ThreeVector());
    f3inchPMTBaseSolid  = new J4UnionSolid("PMTBase", semi_sphere, polycone1, 0, G4ThreeVector());


}

///////////////////////////////////////////////////////
///
///
///////////////////////////////////////////////////////
void J4PMTSolidMaker::Create3inchPMTSolid2()
{

    G4ThreeVector centerOfCons1;
    G4ThreeVector centerOfCons2;
    G4ThreeVector centerOfCons3;
    G4ThreeVector centerOfCons4;
    G4ThreeVector centerOfTubs;

    G4double rmin2, rmax2, dz;
    G4double rmin, rmax, sphi, dphi, stheta, dtheta;
    G4double rSmin, rSmax, sSphi, dSphi, sStheta, dStheta;

    rSmin   = 0;
    rSmax   = 56.77 * mm;
    dSphi   = 2*M_PI;
    dStheta = 60.29 * degree;

    centerOfCons1 = G4ThreeVector(0, 0, (56.7 - 29.005 - 2.44/2.) *mm);
    centerOfCons2 = G4ThreeVector(0, 0, (56.7 - 29.005 - 2.44 - 3.54/2.) *mm);
    centerOfCons3 = G4ThreeVector(0, 0, (56.7 - 29.005 - 2.44 - 3.54 - 17.4/2.) *mm);
    centerOfCons4 = G4ThreeVector(0, 0, (4.393 - 10.606/2.) *mm);
    centerOfTubs = G4ThreeVector(0, 0, (-6.213 - 43.287/2.) *mm);


    sSphi = 0;
    sStheta = 0;

    G4Sphere *sphere = new G4Sphere("sphere",rSmin, rSmax,
                                    sSphi, dSphi, sStheta, dStheta);


    //to create con1
    rmin   = 0;
    rmin2  = 0;
    rmax2  = 49.05 *mm;
    rmax   = 49.64 *mm;
    dz     = 2.44/2 *mm;
    sphi   = 0;
    dphi   = 2*M_PI;

    G4Cons *cons1 = new G4Cons("cons1",rmin, rmax, rmin2,
                               rmax2, dz, sphi, dphi);
    //to create con2

    rmin   = 0;
    rmin2  = 0;
    rmax2  = 49.64 *mm;
    rmax   = 48.221 *mm;
    dz     = 3.54/2 *mm;
    sphi   = 0;
    dphi   = 2*M_PI;

    G4Cons *cons2 = new G4Cons("cons2",rmin, rmax, rmin2,
                               rmax2, dz, sphi, dphi);
    //to create con3

    rmin   = 0;
    rmin2  = 0;
    rmax   = 61.79/2 *mm;
    rmax2  = 48.221 *mm;
    //dz     = 17.4/2 *mm; // When you use this value, visualization is stopped.
    dz = 17.8/2. *mm; //After modification
    sphi   = 0;
    dphi   = 2*M_PI;
    
    G4Cons *cons3 = new G4Cons("cons3",rmin, rmax, rmin2,
                               rmax2, dz, sphi, dphi);
    //to create con4

    rmin   = 0;
    rmin2  = 0;
    rmax   = 53./2 *mm;
    rmax2  = 61.79/2 *mm;
    dz     = 10.6/2 *mm;
    sphi   = 0;
    dphi   = 2*M_PI;

    G4Cons *cons4 = new G4Cons("cons4",rmin, rmax, rmin2,
                               rmax2, dz, sphi, dphi);
    // create tub

    rmin   = 0 *mm;
    rmax = 53./2 *mm;
    dz = 43.287/2*mm;
    sphi   = 0;
    dphi   = 2*M_PI;

    G4Tubs *tubs = new G4Tubs("tubs",rmin, rmax, dz,
                              sphi, dphi);

   
    J4UnionSolid *solid1
      = new J4UnionSolid("solid1", sphere, cons1, 0, centerOfCons1);

    J4UnionSolid *solid2
      = new J4UnionSolid("solid2", solid1, cons2, 0, centerOfCons2);

    J4UnionSolid *solid3
      = new J4UnionSolid("solid3", solid2, cons3, 0, centerOfCons3);

    J4UnionSolid *solid4
      = new J4UnionSolid("solid4", solid3, cons4, 0, centerOfCons4);

    f3inchPMTSolid  = new J4UnionSolid("solid", solid4, tubs, 0, centerOfTubs);

}
 
