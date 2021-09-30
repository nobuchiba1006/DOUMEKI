// $Id: J4MEggGel.hh,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
#ifndef __J4MEggGel__hh
#define __J4MEggGel__hh
//*************************************************************************
//* --------------------
//* J4MEggGel
//* --------------------
//* (Description)
//*     J4MEgg discribes the Drift Chamber component.
//*     It is cylinder-shaped chamber and includes 
//*     several layers as sensitive regions.
//*     Mother class : J4VDEggDetectorComponent
//*    
//* (Update Record)
//*	2003/09/27  K.Hoshina	Original version.
//*************************************************************************

#include "J4VDetectorComponent.hh"
#include "G4VSolid.hh"
class G4VSolid;

//=====================================================================
//---------------------
// class definition
//---------------------


class J4MEggGel : public J4VDetectorComponent {	

public:

  J4MEggGel(J4VDetectorComponent* parent    = 0,
           G4int                 nclones   = 1,
           G4int                 nbrothers = 1, 
           G4int                 me        = 0,
           G4int                 copyno    = -1);
  	     
  virtual ~J4MEggGel();

  virtual void  InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = G4ThreeVector() );
  virtual void	Draw()      ;
  virtual void	Print() const ;

private:
  void 	     Assemble();    
  void       Cabling ();
  G4VSolid * CreateGelSolid();

private:
  
  static G4String fFirstName;

};

#endif


