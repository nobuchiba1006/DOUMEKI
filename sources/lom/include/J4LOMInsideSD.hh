// $Id: J4LOMInsideSD.hh,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
#ifndef __J4LOMInsideSD__hh
#define __J4LOMInsideSD__hh
//*************************************************************************
//* --------------------
//* J4LOMInsideSD
//* --------------------
//* (Description)
//* 	It appends Sensitive propaty to J4LOMInside. 
//*	Mother class : J4VSD <- G4VSensitiveDetector
//*     
//* (Update Record)
//*	2003/03/18  K.Hoshina	Original version.
//*************************************************************************
 
#include "J4VSD.hh"
#include "J4LOMInsideHit.hh"

//=====================================================================
//---------------------
// class definition
//---------------------


class J4LOMInsideSD : public J4VSD<J4LOMInsideHit>{
  
public:

  J4LOMInsideSD(J4VDetectorComponent* detector);
  ~J4LOMInsideSD();

  virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist);
  virtual void   Initialize (G4HCofThisEvent* HCTE);
  virtual void   EndOfEvent (G4HCofThisEvent* HCTE);

  virtual void   DrawAll();
  virtual void   PrintAll(); 
 
  virtual void   OutputAll(G4HCofThisEvent* HCTE)
  {
     if(GetHitBuf())
     {
       J4VSD<J4LOMInsideHit>::OutputAll(HCTE);
     }
     else
     {
       std::cerr << "J4LOMInsideSD::OutputAll: No HitBuf! " << std::endl;
     }
  }
  
  // set/get functions
   
private:

  
};

#endif

