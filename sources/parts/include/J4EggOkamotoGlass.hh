// $Id: J4EggOkamotoGlass.hh,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
#ifndef __J4EggOkamotoGlass__hh
#define __J4EggOkamotoGlass__hh
//*************************************************************************
//* --------------------
//* J4EggOkamotoGlass
//* --------------------
//* (Description)
//* 	J4EggOkamotoGlass discribes the Okamoto sphere.
//*     It is Spherical-shaped borosilicate glass.
//*     Mother class : J4VDEggDetectorComponent
//*    
//* (Update Record)
//*	2003/09/27  K.Hoshina	Original version.
//*************************************************************************

#include "J4DEggInside.hh"
#include "J4VDetectorComponent.hh"
class G4VSolid;

//=====================================================================
//---------------------
// class definition
//---------------------

class J4EggOkamotoGlass : public J4VDetectorComponent {	

public:
  J4EggOkamotoGlass(J4VDetectorComponent *parent = 0,
                      G4int  nclones   = 1,
                      G4int  nbrothers = 1, 
                      G4int  me        = 0,
                      G4int  copyno    = -1 );
  virtual ~J4EggOkamotoGlass();

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
  J4DEggInside	       *fInside;
  
};

#endif


