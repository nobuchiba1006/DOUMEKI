// $Id: J4LOMSolidMaker.hh,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
#ifndef __J4LOMSolidMaker__hh
#define __J4LOMSolidMaker__hh
//*************************************************************************
//* --------------------
//* J4LOMSolidMaker
//* --------------------
//* (Description)
//* 	J4LOMSolidMaker discribes how to make glass solid for LOM
//*    
//* (Update Record)
//*	2021/05/27  K.Hoshina	Original version.
//*************************************************************************

#include "G4VSolid.hh"

class J4LOMSolidMaker {

  protected :
    J4LOMSolidMaker() {}

  public:


    static void CreateLOMOuterSolid();
    static void CreateLOMInnerSolid();
    static void CreateLOMHarnessSolid();

    static G4VSolid * GetLOMOuterSolid();
    static G4VSolid * GetLOMInnerSolid();
    static G4VSolid * GetLOMHarnessSolid();

  private:

    static G4VSolid * fLOMOuterSolid;
    static G4VSolid * fLOMInnerSolid;
    static G4VSolid * fLOMHarnessSolid;

};

#endif


