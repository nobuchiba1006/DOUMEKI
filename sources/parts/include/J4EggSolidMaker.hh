// $Id: J4EggSolidMaker.hh,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
#ifndef __J4EggSolidMaker__hh
#define __J4EggSolidMaker__hh
//*************************************************************************
//* --------------------
//* J4EggSolidMaker
//* --------------------
//* (Description)
//* 	J4EggSolidMaker discribes how to make glass solid for Egg
//*    
//* (Update Record)
//*	2021/05/27  K.Hoshina	Original version.
//*************************************************************************

#include "G4VSolid.hh"

class J4EggSolidMaker {

  protected :
    J4EggSolidMaker() {}

  public:


    static void CreateEggOuterSolid();
    static void CreateEggInnerSolid();
    static void CreateEggHarnessSolid();

    static G4VSolid * GetEggOuterSolid();
    static G4VSolid * GetEggInnerSolid();
    static G4VSolid * GetHalfEggInnerSolid();
    static G4VSolid * GetHalfEggInnerTubSolid();
    static G4VSolid * GetEggHarnessSolid();

  private:

    static G4VSolid * fEggOuterSolid;
    static G4VSolid * fEggInnerSolid;
    static G4VSolid * fHalfEggInnerSolid;
    static G4VSolid * fHalfEggInnerTubSolid;
    static G4VSolid * fEggHarnessSolid;

};

#endif


