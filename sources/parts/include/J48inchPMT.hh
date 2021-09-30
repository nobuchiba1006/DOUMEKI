// $Id: J48inchPMT.hh,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
#ifndef __J48inchPMT__hh
#define __J48inchPMT__hh
//*************************************************************************
//* --------------------
//* J48inchPMT
//* --------------------
//* (Description)
//*     J48inch discribes the Drift Chamber component.
//*     It is cylinder-shaped chamber and includes 
//*     several layers as sensitive regions.
//*     Mother class : J4V8inchDetectorComponent
//*    
//* (Update Record)
//*	2003/09/27  K.Hoshina	Original version.
//*************************************************************************

#include "J4VDetectorComponent.hh"

class G4VSolid;

//=====================================================================
//---------------------
// class definition
//---------------------

class J48inchPMT : public J4VDetectorComponent {	

public:

  J48inchPMT(J4VDetectorComponent* parent    = 0,
           G4int                 nclones   = 1,
           G4int                 nbrothers = 1, 
           G4int                 me        = 0,
           G4int                 copyno    = -1);
  	     
  virtual ~J48inchPMT();

  virtual void  InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = G4ThreeVector() );
  virtual void	Draw()      ;
  virtual void	Print() const ;

private:
  void      Assemble();    
  void      Cabling ();
  G4VSolid* CreatePMTSolid();
  
private:
  
  static G4String fFirstName;

};

#endif


