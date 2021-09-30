// $Id: J4DOMPMTHit.hh,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
#ifndef __J4DCLAYERHIT__hh
#define __J4DCLAYERHIT__hh
//*************************************************************************
//* --------------------
//* J4DOMPMTHit
//* --------------------
//* (Description)
//*     Hit class for J4DOMPMTHit 	
//*	Mother class : G4VHit
//*     
//* (Update Record)
//*	2001/02/18  K.Hoshina	Original version.
//*************************************************************************

#include "J4VHit.hh"
#include "J4Output.hh"
#include "G4THitsCollection.hh"
#include "G4HCofThisEvent.hh"
#include "G4ParticleDefinition.hh"
#include "G4ThreeVector.hh"


//=========================================================================
// TypeDef

class J4DOMPMTHit;
typedef G4Allocator<J4DOMPMTHit> J4DOMPMTHitAllocator;
typedef G4THitsCollection<J4DOMPMTHit> J4DOMPMTHitBuf;

//=========================================================================
//---------------------
// class definition
//---------------------
 

class J4DOMPMTHit : public J4VHit {

public:
  J4DOMPMTHit();
  J4DOMPMTHit( J4VComponent  *dtc,
               G4ThreeVector  pre,
               G4double       edep,           // Energy Deposit
               G4double       tof ) ;         // TOF 
  	 	            
  virtual ~J4DOMPMTHit();
  
  void* operator new    (size_t    );
  void  operator delete (void* aHit);

  virtual void Output(G4HCofThisEvent* HCTE);
  virtual void Draw();
  virtual void Print();

  // getters
  inline G4ThreeVector GetPosition()       const { return fPosition;      }
  inline G4double      GetEnerygDeposit()  const { return fEnergyDep;     }
  inline G4double      GetTof()            const { return fTof;           }

  // setters 

  inline void SetPosition(G4ThreeVector x) { fPosition   = x; }
  inline void SetEnergyDeposit(G4double x) { fEnergyDep  = x; }
  inline void SetTof          (G4double x) { fTof        = x; }
    
private: 

  static J4DOMPMTHitAllocator  fHitAllocator;
  static J4Output              *fOutput;       // Pointer to Output Module

  G4ThreeVector fPosition;    // position
  G4double      fEnergyDep;   // edep
  G4double      fTof;         // tof 
  
};

//=====================================================================
//----------------------------------------
// inline function for J4DOMPMTHit
//----------------------------------------
  
//----------------------------------------
// Allocator

inline void* J4DOMPMTHit::operator new(size_t)
{
  
  void* aHit;
  aHit= (void*)fHitAllocator.MallocSingle();
  return aHit;
}

inline void J4DOMPMTHit::operator delete(void* aHit)
{
  fHitAllocator.FreeSingle((J4DOMPMTHit*) aHit);
}



#endif

