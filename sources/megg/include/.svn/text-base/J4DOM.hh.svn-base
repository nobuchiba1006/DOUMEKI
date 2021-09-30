// $Id: J4DOM.hh,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
#ifndef __J4DOM__hh
#define __J4DOM__hh
//*************************************************************************
//* --------------------
//* J4DOM
//* --------------------
//* (Description)
//* 	J4DOM discribes the spherical region for DOM.
//*     It is filled with the air.
//*     Mother class : J4VDOMDetectorComponent
//*    
//* (Update Record)
//*	2003/09/27  K.Hoshina	Original version.
//*************************************************************************

#include "J4DOMBenthos.hh"
#include "J4DOMInside.hh"
#include "J4VDOMDetectorComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4DOM : public J4VDOMDetectorComponent {	

public:
  J4DOM(J4VDetectorComponent *parent   = 0,
                      G4int  nclones   = 1,
                      G4int  nbrothers = 1, 
                      G4int  me        = 0,
                      G4int  copyno    = -1 );
  virtual ~J4DOM();

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
  J4DOMBenthos*	        fBenthos;
  J4DOMInside*	        fInside;
  
};

#endif


