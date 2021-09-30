// $Id: J4MEgg.hh,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
#ifndef __J4MEgg__hh
#define __J4MEgg__hh
//*************************************************************************
//* --------------------
//* J4MEgg
//* --------------------
//* (Description)
//* 	J4MEgg discribes the spherical region for DEgg.
//*     It is filled with the air.
//*     Mother class : J4VDEggDetectorComponent
//*    
//* (Update Record)
//*	2003/09/27  K.Hoshina	Original version.
//*************************************************************************

#include "J4EggOkamotoGlass.hh"
#include "J4MEggInside.hh"
#include "J4VDetectorComponent.hh"

class G4VSolid;

//=====================================================================
//---------------------
// class definition
//---------------------

class J4MEgg : public J4VDetectorComponent {	

public:
  J4MEgg(J4VDetectorComponent *parent   = 0,
                      G4int  nclones   = 1,
                      G4int  nbrothers = 1, 
                      G4int  me        = 0,
                      G4int  copyno    = -1 );
  virtual ~J4MEgg();

  virtual void  InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = G4ThreeVector() );
  virtual void	Draw()      ;
  virtual void	Print() const ;
  
private:
  void 	Assemble();    
  void  Cabling ();
  
private:  
  static G4String       fFirstName;
  J4EggOkamotoGlass*	fOkamoto;
  J4MEggInside*	        fInsideUp;
  J4MEggInside*	        fInsideDown;
  
};

#endif


