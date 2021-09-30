// $Id: J4ElectricBoard.hh,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
#ifndef __J4ElectricBoard__hh
#define __J4ElectricBoard__hh
//*************************************************************************
//* --------------------
//* J4ElectricBoard
//* --------------------
//* (Description)
//* 	J4ElectricBoard can be used for MainBoard or HVBoard.
//*     It is filled with the air.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2003/09/27  K.Hoshina	Original version.
//*	2021/07/01  K.Hoshina	Renamed from J4DEggMainBoard and added 
//*                             initialization parameters to constructor
//*************************************************************************

#include "J4VDetectorComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4ElectricBoard : public J4VDetectorComponent {	

public:
  J4ElectricBoard(G4double rmin, G4double rmax, G4double dz,
              J4VDetectorComponent *parent   = 0,
                      G4int  nclones   = 1,
                      G4int  nbrothers = 1, 
                      G4int  me        = 0,
                      G4int  copyno    = -1 );
  virtual ~J4ElectricBoard();

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
  G4double              fRmin;
  G4double              fRmax;
  G4double              fDz;
  
};

#endif


