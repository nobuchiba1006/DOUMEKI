// $Id: J4Bubble.hh,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
#ifndef __J4Bubble__hh
#define __J4Bubble__hh
//*************************************************************************
//* --------------------
//* J4Bubble
//* --------------------
//* (Description)
//* 	J4Bubble discribes the spherical region for DEgg.
//*     It is filled with the air.
//*     Mother class : J4VDEggDetectorComponent
//*    
//* (Update Record)
//*	2003/09/27  K.Hoshina	Original version.
//*************************************************************************

#include "J4VDetectorComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4Bubble : public J4VDetectorComponent {	

public:
  J4Bubble(J4VDetectorComponent *parent   = 0,
                      G4int  nclones   = 1,
                      G4int  nbrothers = 1, 
                      G4int  me        = 0,
                      G4int  copyno    = -1 );
  virtual ~J4Bubble();

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
  
};

#endif


