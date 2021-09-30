// $Id: J4BubbleColumn.hh,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
#ifndef __J4BubbleColumn__hh
#define __J4BubbleColumn__hh
//*************************************************************************
//* --------------------
//* J4BubbleColumn
//* --------------------
//* (Description)
//* 	J4BubbleColumn discribes the BubbleColumn sphere.
//*     It is Spherical-shaped borosilicate glass.
//*     Mother class : J4VDEggDetectorComponent
//*    
//* (Update Record)
//*	2003/09/27  K.Hoshina	Original version.
//*************************************************************************

#include "J4VDetectorComponent.hh"
class G4VSolid;

//=====================================================================
//---------------------
// class definition
//---------------------

class J4BubbleColumn : public J4VDetectorComponent {	

public:
  J4BubbleColumn(const G4String & glasstype = "Egg",
                      J4VDetectorComponent *parent = 0,
                      G4int  nclones   = 1,
                      G4int  nbrothers = 1, 
                      G4int  me        = 0,
                      G4int  copyno    = -1 );
  virtual ~J4BubbleColumn();

  virtual void  InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = G4ThreeVector() );
  virtual void	Draw()      ;
  virtual void	Print() const ;

  G4String GetGlassType()                  { return fGlassType; }
  void     SetGlassType(const G4String &n) { fGlassType = n; }
  
private:
  void 	Assemble();    
  void  Cabling ();
  G4VSolid* CreateBubbleColumnSolid();
  
private:  
  static G4String	fFirstName;
         G4String	fGlassType;
  
};

#endif


