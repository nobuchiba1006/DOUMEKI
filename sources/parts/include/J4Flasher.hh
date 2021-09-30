// $Id: J4Flasher.hh,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
#ifndef __J4Flasher__hh
#define __J4Flasher__hh
//*************************************************************************
//* --------------------
//* J4Flasher
//* --------------------
//* (Description)
//* 	J4Flasher discribes the spherical region for DEgg.
//*     It is filled with the air.
//*     Mother class : J4VDEggDetectorComponent
//*    
//* (Update Record)
//*	2003/09/27  K.Hoshina	Original version.
//*************************************************************************

#include "J4VDetectorComponent.hh"
#include "J4DEggGel.hh"

class G4VSolid;

//=====================================================================
//---------------------
// class definition
//---------------------

class J4Flasher : public J4VDetectorComponent {	

friend class J4DEggGel;

public:
  J4Flasher(G4double rmin, G4double rmax, G4double dz,
            J4VDetectorComponent *parent   = 0,
                      G4int  nclones   = 1,
                      G4int  nbrothers = 1, 
                      G4int  me        = 0,
                      G4int  copyno    = -1 );
  virtual ~J4Flasher();

  virtual void  InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = G4ThreeVector() );
  virtual void	Draw()      ;
  virtual void	Print() const ;
  
private:
  void 	Assemble();    
  void  Cabling ();
  G4VSolid *CreateFlasherSolid();
  
private:  
  static G4String       fFirstName;
  G4double              fRmin;
  G4double              fRmax;
  G4double              fDz;
  
};

#endif


