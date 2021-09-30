// $Id: J4DOMInside.hh,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
#ifndef __J4DOMInside__hh
#define __J4DOMInside__hh
//*************************************************************************
//* --------------------
//* J4DOMInside
//* --------------------
//* (Description)
//* 	J4DOMInside discribes the Inside sphere.
//*     It is Spherical-shaped borosilicate grass.
//*     Mother class : J4VDOMDetectorComponent
//*    
//* (Update Record)
//*	2003/09/27  K.Hoshina	Original version.
//*************************************************************************

#include "J4DOMGel.hh"
#include "J4DOMPMT.hh"
#include "J4DOMMainBoard.hh"
#include "J4VDOMDetectorComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4DOMInside : public J4VDOMDetectorComponent {	

public:
  J4DOMInside(J4VDetectorComponent *parent = 0,
                      G4int  nclones   = 1,
                      G4int  nbrothers = 1, 
                      G4int  me        = 0,
                      G4int  copyno    = -1 );
  virtual ~J4DOMInside();

  virtual void  InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = G4ThreeVector() );
  virtual void	Draw()      ;
  virtual void	Print() const ;

  inline J4DOMPMT* GetPMT() const { return fPMT; }
  
private:
  void 	Assemble();    
  void  Cabling ();
  
private:  
  static G4String	fFirstName;
  J4DOMGel*		fGel;
  J4DOMPMT*		fPMT;
  J4DOMMainBoard*		fMainBoard;
  J4DOMMainBoard*		fFlasherBoard;
  J4DOMMainBoard*		fHVBoard;
  
};

#endif


