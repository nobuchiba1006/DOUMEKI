// $Id: J4DEggShield.hh,v 1.1.1.1 $
#ifndef __J4DEggShield__hh
#define __J4DEggShield__hh
//*************************************************************************
//* --------------------
//* J4DEggShield
//* --------------------
//* (Description)
//*     Mother class : J4VDEggDetectorComponent
//*    
//* (Update Record)
//*************************************************************************

#include "J4VDetectorComponent.hh"
class G4VSolid;

//=====================================================================
//---------------------
// class definition
//---------------------

class J4DEggShield : public J4VDetectorComponent {	

friend class J4DEggGel;

public:
  J4DEggShield(J4VDetectorComponent *parent   = 0,
                      G4int  nclones   = 1,
                      G4int  nbrothers = 1, 
                      G4int  me        = 0,
                      G4int  copyno    = -1 );
  virtual ~J4DEggShield();

  virtual void  InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = G4ThreeVector() );
  virtual void	Draw()      ;
  virtual void	Print() const ;
  
private:
  void 	Assemble();    
  void  Cabling ();
  G4VSolid* CreateShieldSolid();
  
private:  
  static G4String       fFirstName;
  
};

#endif


