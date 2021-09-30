// $Id: J4DOMPhotoCathode.hh,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
#ifndef __J4DOMPhotoCathode__hh
#define __J4DOMPhotoCathode__hh
//*************************************************************************
//* --------------------
//* J4DOMPhotoCathode
//* --------------------
//* (Description)
//*     J4DOM discribes the Drift Chamber component.
//*     It is cylinder-shaped chamber and includes 
//*     several layers as sensitive regions.
//*     Mother class : J4VDOMDetectorComponent
//*    
//* (Update Record)
//*	2003/09/27  K.Hoshina	Original version.
//*************************************************************************

#include "J4VDOMDetectorComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------


class J4DOMPhotoCathode : public J4VDOMDetectorComponent {	

public:

  J4DOMPhotoCathode(J4VDetectorComponent* parent    = 0,
           G4int                 nclones   = 1,
           G4int                 nbrothers = 1, 
           G4int                 me        = 0,
           G4int                 copyno    = -1);
  	     
  virtual ~J4DOMPhotoCathode();

  virtual void  InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = G4ThreeVector() );
  virtual void	Draw()      ;
  virtual void	Print() const ;

private:
  void 	Assemble();    
  void  Cabling ();
  
private:
  
  static G4String fFirstName;

};

#endif


