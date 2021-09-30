// $Id: J4LOM.hh,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
#ifndef __J4LOM__hh
#define __J4LOM__hh
//*************************************************************************
//* --------------------
//* J4LOM
//* --------------------
//* (Description)
//* 	J4LOM discribes the spherical region for DEgg.
//*     It is filled with the air.
//*     Mother class : J4VDEggDetectorComponent
//*    
//* (Update Record)
//*	2003/09/27  K.Hoshina	Original version.
//*************************************************************************

#include "J4LOMOkamotoGlass.hh"
#include "J4LOMInside.hh"
#include "J4VDetectorComponent.hh"

class G4VSolid;

//=====================================================================
//---------------------
// class definition
//---------------------

class J4LOM : public J4VDetectorComponent {	

public:
  J4LOM(J4VDetectorComponent *parent   = 0,
                      G4int  nclones   = 1,
                      G4int  nbrothers = 1, 
                      G4int  me        = 0,
                      G4int  copyno    = -1 );
  virtual ~J4LOM();

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
  J4LOMOkamotoGlass*	fOkamoto;
  J4LOMInside*	        fInside;
  
};

#endif


