// $Id: J44inchPMTHit.hh,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
#ifndef __J4DCLAYERHIT__hh
#define __J4DCLAYERHIT__hh
//*************************************************************************
//* --------------------
//* J44inchPMTHit
//* --------------------
//* (Description)
//*     Hit class for J44inchPMTHit 	
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

class J44inchPMTHit;
typedef G4Allocator<J44inchPMTHit> J44inchPMTHitAllocator;
typedef G4THitsCollection<J44inchPMTHit> J44inchPMTHitBuf;

//=========================================================================
//---------------------
// class definition
//---------------------
 

class J44inchPMTHit : public J4VHit {

public:
  J44inchPMTHit();
  J44inchPMTHit( J4VComponent  *dtc,
               G4ThreeVector  pre,
               G4double       ce, 
               G4int          momid,  // inside module ID
               G4int          myid) ; // pmt id
  	 	            
  virtual ~J44inchPMTHit();
  
  void* operator new    (size_t    );
  void  operator delete (void* aHit);

  virtual void Output(G4HCofThisEvent* HCTE);
  virtual void Draw();
  virtual void Print();

  // getters
  inline G4ThreeVector GetPosition()       const { return fPosition;      }
  inline G4double      GetCE()             const { return fCE;     }

  // setters 

  inline void SetPosition(G4ThreeVector x) { fPosition   = x; }
  inline void SetCE(G4double x)            { fCE= x; }
    
private: 

  static J44inchPMTHitAllocator  fHitAllocator;
  static J4Output              *fOutput;       // Pointer to Output Module

  G4ThreeVector fPosition;    // position
  G4double      fCE;          // mean CE
  G4int         fMomID;
  G4int         fMyID;
  
};

//=====================================================================
//----------------------------------------
// inline function for J44inchPMTHit
//----------------------------------------
  
//----------------------------------------
// Allocator

inline void* J44inchPMTHit::operator new(size_t)
{
  
  void* aHit;
  aHit= (void*)fHitAllocator.MallocSingle();
  return aHit;
}

inline void J44inchPMTHit::operator delete(void* aHit)
{
  fHitAllocator.FreeSingle((J44inchPMTHit*) aHit);
}



#endif

