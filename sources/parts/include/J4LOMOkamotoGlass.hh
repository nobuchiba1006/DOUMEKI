// $Id: J4LOMOkamotoGlass.hh,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
#ifndef __J4LOMOkamotoGlass__hh
#define __J4LOMOkamotoGlass__hh
//*************************************************************************
//* --------------------
//* J4LOMOkamotoGlass
//* --------------------
//* (Description)
//* 	J4LOMOkamotoGlass discribes the Okamoto sphere.
//*     It is Spherical-shaped borosilicate glass.
//*     Mother class : J4VDEggDetectorComponent
//*    
//* (Update Record)
//*	2003/09/27  K.Hoshina	Original version.
//*************************************************************************

#include "J4LOMInside.hh"
#include "J4VDetectorComponent.hh"
class G4VSolid;

//=====================================================================
//---------------------
// class definition
//---------------------

class J4LOMOkamotoGlass : public J4VDetectorComponent {	

public:
  J4LOMOkamotoGlass(J4VDetectorComponent *parent = 0,
                      G4int  nclones   = 1,
                      G4int  nbrothers = 1, 
                      G4int  me        = 0,
                      G4int  copyno    = -1 );
  virtual ~J4LOMOkamotoGlass();

  virtual void  InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = G4ThreeVector() );
  virtual void	Draw()      ;
  virtual void	Print() const ;
  //inline J4DEggInside* GetInside() const { return fInside; }
  
private:
  void 	Assemble();    
  void  Cabling ();


private:  
  static G4String	fFirstName;
  J4LOMInside	       *fInside;
  
};

#endif


