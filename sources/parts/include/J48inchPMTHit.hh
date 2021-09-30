// $Id: J48inchPMTHit.hh,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
#ifndef __J48inchPMTHit__hh
#define __J48inchPMTHit__hh
//*************************************************************************
//* --------------------
//* J48inchPMTHit
//* --------------------
//* (Description)
//*     Hit class for J48inchPMTHit 	
//*	Mother class : G4VHit
//*     
//* (Update Record)
//*	2001/02/18  K.Hoshina	Original version.
//*************************************************************************

#include "J4RunAction.hh"
#include "J4VHit.hh"
#include "J4Output.hh"
#include "G4THitsCollection.hh"
#include "G4HCofThisEvent.hh"
#include "G4ParticleDefinition.hh"
#include "G4ThreeVector.hh"


//=========================================================================
// TypeDef

class J48inchPMTHit;
typedef G4Allocator<J48inchPMTHit> J48inchPMTHitAllocator;
typedef G4THitsCollection<J48inchPMTHit> J48inchPMTHitBuf;

//=========================================================================
//---------------------
// class definition
//---------------------
 

class J48inchPMTHit : public J4VHit {

public:
  J48inchPMTHit();
  J48inchPMTHit(J4VComponent  *dtc,
               G4ThreeVector  pre,
               G4ThreeVector  localpos,
               G4ThreeVector  localdir,
               G4double       ce);
  	 	            
  virtual ~J48inchPMTHit();
  
  void* operator new    (size_t    );
  void  operator delete (void* aHit);

  virtual void Output(G4HCofThisEvent* HCTE);
  virtual void Draw();
  virtual void Print();

  // getters
  inline G4ThreeVector GetPosition()       const { return fPosition;      }
  inline G4double      GetCE()             const { return fCE;     }
  inline G4ThreeVector GetLocalPosition()  const { return fLocalPosition; }
  inline G4ThreeVector GetLocalDirection() const { return fLocalDirection; }

  // setters 

  inline void SetPosition(G4ThreeVector x) { fPosition   = x; }
  inline void SetCE(G4double x)            { fCE = x; }
  inline void SetLocalPosition(G4ThreeVector x) { fLocalPosition   = x; }
  inline void SetLocalDirection(G4ThreeVector x) { fLocalDirection   = x; }
    
private: 

  static J48inchPMTHitAllocator  fHitAllocator;
  static J4Output              *fOutput;       // Pointer to Output Module

  G4ThreeVector fPosition;    // position
  G4ThreeVector fLocalPosition;    // position
  G4ThreeVector fLocalDirection;    // position
  G4double      fCE;          // mean CE
  
};

//=====================================================================
//----------------------------------------
// inline function for J48inchPMTHit
//----------------------------------------
  
//----------------------------------------
// Allocator

inline void* J48inchPMTHit::operator new(size_t)
{
  
  void* aHit;
  aHit= (void*)fHitAllocator.MallocSingle();
  return aHit;
}

inline void J48inchPMTHit::operator delete(void* aHit)
{
  fHitAllocator.FreeSingle((J48inchPMTHit*) aHit);
}



#endif

