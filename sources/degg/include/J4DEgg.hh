// $Id: J4DEgg.hh,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
#ifndef __J4DEgg__hh
#define __J4DEgg__hh
//*************************************************************************
//* --------------------
//* J4DEgg
//* --------------------
//* (Description)
//* 	J4DEgg discribes the spherical region for DEgg.
//*     It is filled with the air.
//*     Mother class : J4VDEggDetectorComponent
//*    
//* (Update Record)
//*	2003/09/27  K.Hoshina	Original version.
//*************************************************************************

#include "J4EggOkamotoGlass.hh"
#include "J4DEggInside.hh"
#include "J4VDetectorComponent.hh"

class G4VSolid;

//=====================================================================
//---------------------
// class definition
//---------------------

class J4DEgg : public J4VDetectorComponent {	

public:
  J4DEgg(J4VDetectorComponent *parent   = 0,
                      G4int  nclones   = 1,
                      G4int  nbrothers = 1, 
                      G4int  me        = 0,
                      G4int  copyno    = -1 );
  virtual ~J4DEgg();

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
  J4EggOkamotoGlass *	fOkamoto;
  J4DEggInside *	fInside;
  J4DEggInside *	fInsideDown;
  
};

#endif


