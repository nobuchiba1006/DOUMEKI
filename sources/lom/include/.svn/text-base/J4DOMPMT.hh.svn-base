// $Id: J4DOMPMT.hh,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
#ifndef __J4DOMPMT__hh
#define __J4DOMPMT__hh
//*************************************************************************
//* --------------------
//* J4DOMPMT
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
#include "J4DOMPhotoCathode.hh"
#include "J4DOMGel.hh"

class G4VSolid;

//=====================================================================
//---------------------
// class definition
//---------------------

class J4DOMPMT : public J4VDOMDetectorComponent {	

friend class J4DOMGel;

public:

  J4DOMPMT(J4VDetectorComponent* parent    = 0,
           G4int                 nclones   = 1,
           G4int                 nbrothers = 1, 
           G4int                 me        = 0,
           G4int                 copyno    = -1);
  	     
  virtual ~J4DOMPMT();

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

  J4DOMPhotoCathode *fPhotoCathode;

};

#endif


