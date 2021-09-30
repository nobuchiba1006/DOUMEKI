// $Id: J4DEggInside.hh,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
#ifndef __J4DEggInside__hh
#define __J4DEggInside__hh
//*************************************************************************
//* --------------------
//* J4DEggInside
//* --------------------
//* (Description)
//* 	J4DEggInside discribes the Inside sphere.
//*     It is Spherical-shaped borosilicate glass.
//*     Mother class : J4VDEggDetectorComponent
//*    
//* (Update Record)
//*	2003/09/27  K.Hoshina	Original version.
//*************************************************************************

#include "J4DEggGel.hh"
#include "J48inchPMT.hh"
#include "J4ElectricBoard.hh"
#include "J4VDetectorComponent.hh"
#include "J4DEggShield.hh"
#include "J4Flasher.hh"
class G4VSolid;

//=====================================================================
//---------------------
// class definition
//---------------------

class J4DEggInside : public J4VDetectorComponent {	

public:
  J4DEggInside(J4VDetectorComponent *parent = 0,
                      G4int  nclones   = 1,
                      G4int  nbrothers = 1, 
                      G4int  me        = 0,
                      G4int  copyno    = -1 );
  virtual ~J4DEggInside();

  virtual void  InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot = 0,
                          const G4ThreeVector  &tlate = G4ThreeVector() );
  virtual void	Draw()      ;
  virtual void	Print() const ;
  
  inline J4DEggGel* GetGel() const { return fGel; }
  //inline J4DEggGel* GetGeldown() const { return fGeldown; }
 
  inline J48inchPMT* GetPMT() const { return fPMT; }
  //inline J4DEggPMT* GetPMTdown() const { return fPMTdown; }

  //inline J4DEggFlasher* GetFlasher() const { return fFlasher; }
  //inline J4DEggShield* GetShield() const { return fShield; }
  //inline J4DEggShield* GetShielddown() const { return fShielddown; }

  //inline J4DEggPMT* GetDEgg() const { return fDEgg; }
  //inline J4DEggPMT* GetInside() const { return fInside; }


private:
  void 	Assemble();    
  void  Cabling ();
  
private:  
  static G4String	fFirstName;
  J4DEggGel*		fGel;
  J4DEggGel*		fGeldown;

  J48inchPMT*		fPMT;
  J48inchPMT*		fPMTdown;

  J4ElectricBoard*	fMainBoard;
  J4ElectricBoard*	fHVBoard;
  J4ElectricBoard*	fHVBoarddown;
  J4ElectricBoard*	fDivider;
  J4ElectricBoard*	fDividerdown;
  J4DEggShield*         fShield;
  J4DEggShield*         fShielddown;  
  J4Flasher*            fFlasher;
};

#endif


