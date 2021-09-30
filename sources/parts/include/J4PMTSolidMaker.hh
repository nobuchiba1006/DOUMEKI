// $Id: J4PMTSolidMaker.hh,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
#ifndef __J4PMTSolidMaker__hh
#define __J4PMTSolidMaker__hh
//*************************************************************************
//* --------------------
//* J4PMTSolidMaker
//* --------------------
//* (Description)
//* 	J4PMTSolidMaker discribes how to make glass solid for DEgg
//*    
//* (Update Record)
//*	2021/05/27  K.Hoshina	Original version.
//*************************************************************************

#include "G4VSolid.hh"

class J4PMTSolidMaker {

  protected :
    J4PMTSolidMaker() {}

  public:


    static void Create8inchPMTSolid();
    static void Create4inchPMTSolid();
    static void Create3inchPMTSolid();
    static void Create3inchPMTSolid2();

    static G4VSolid * Get8inchPMTSolid();
    static G4VSolid * Get4inchPMTSolid();
    static G4VSolid * Get4inchPMTBaseSolid();
    static G4VSolid * Get4inchPMTCathodeSolid();
    static G4VSolid * Get3inchPMTSolid();
    static G4VSolid * Get3inchPMTBaseSolid();
    static G4VSolid * Get3inchPMTCathodeSolid();

  private:

    static G4VSolid * f8inchPMTSolid;
    static G4VSolid * f4inchPMTSolid;
    static G4VSolid * f4inchPMTBaseSolid;
    static G4VSolid * f4inchPMTCathodeSolid;
    static G4VSolid * f3inchPMTSolid;
    static G4VSolid * f3inchPMTBaseSolid;
    static G4VSolid * f3inchPMTCathodeSolid;

};

#endif


