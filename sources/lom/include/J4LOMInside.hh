// $Id: J4LOMInside.hh,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
#ifndef __J4LOMInside__hh
#define __J4LOMInside__hh
//*************************************************************************
//* --------------------
//* J4LOMInside
//* --------------------
//* (Description)
//* 	J4LOMInside discribes the Inside sphere.
//*     It is Spherical-shaped borosilicate glass.
//*     Mother class : J4VDEggDetectorComponent
//*    
//* (Update Record)
//*	2003/09/27  K.Hoshina	Original version.
//*************************************************************************

#include "J4LOMGel.hh"
#include "J44inchPMT.hh"
#include "J4ElectricBoard.hh"
#include "J4VDetectorComponent.hh"
class G4VSolid;

//=====================================================================
//---------------------
// class definition
//---------------------

class J4LOMInside : public J4VDetectorComponent {	

public:
  J4LOMInside(J4VDetectorComponent *parent = 0,
                      G4int  nclones   = 1,
                      G4int  nbrothers = 1, 
                      G4int  me        = 0,
                      G4int  copyno    = -1 );
  virtual ~J4LOMInside();

  virtual void  InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot = 0,
                          const G4ThreeVector  &tlate = G4ThreeVector() );
  virtual void	Draw()      ;
  virtual void	Print() const ;
  
  inline std::vector<J4LOMGel*> GetGels() const { return fGels; }
 
  inline std::vector<J44inchPMT*> GetPMTs() const { return fPMTs; }

private:
  void 	Assemble();    
  void  Cabling ();

  
private:  
  static G4String	   fFirstName;
  std::vector<J4LOMGel*>  fGels;
  std::vector<J44inchPMT*> fPMTs;
};

#endif


