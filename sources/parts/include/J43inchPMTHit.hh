// $Id: J43inchPMTHit.hh,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
#ifndef __J4DCLAYERHIT__hh
#define __J4DCLAYERHIT__hh
//*************************************************************************
//* --------------------
//* J43inchPMTHit
//* --------------------
//* (Description)
//*     Hit class for J43inchPMTHit 	
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

class J43inchPMTHit;
typedef G4Allocator<J43inchPMTHit> J43inchPMTHitAllocator;
typedef G4THitsCollection<J43inchPMTHit> J43inchPMTHitBuf;

//=========================================================================
//---------------------
// class definition
//---------------------
 

class J43inchPMTHit : public J4VHit {

public:
  J43inchPMTHit();
  J43inchPMTHit( J4VComponent  *dtc,
               G4ThreeVector  pre,
               G4ThreeVector  localpos,
               G4ThreeVector  localdir,
               G4double       ce, 
               G4int          momid,  // inside module ID
               G4int          myid) ; // pmt id
  	 	            
  virtual ~J43inchPMTHit();
  
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
  inline void SetCE(G4double x)            { fCE= x; }
  inline void SetLocalPosition(G4ThreeVector x) { fLocalPosition   = x; }
  inline void SetLocalDirection(G4ThreeVector x) { fLocalDirection   = x; }
    
private: 

  static J43inchPMTHitAllocator  fHitAllocator;
  static J4Output              *fOutput;       // Pointer to Output Module

  G4ThreeVector fPosition;    // position
  G4ThreeVector fLocalPosition;    // position
  G4ThreeVector fLocalDirection;    // position
  G4double      fCE;          // mean CE
  G4int         fMomID;
  G4int         fMyID;
  
};

//=====================================================================
//----------------------------------------
// inline function for J43inchPMTHit
//----------------------------------------
  
//----------------------------------------
// Allocator

inline void* J43inchPMTHit::operator new(size_t)
{
  
  void* aHit;
  aHit= (void*)fHitAllocator.MallocSingle();
  return aHit;
}

inline void J43inchPMTHit::operator delete(void* aHit)
{
  fHitAllocator.FreeSingle((J43inchPMTHit*) aHit);
}



#endif

