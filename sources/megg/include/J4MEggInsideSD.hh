// $Id: J4MEggInsideSD.hh,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
#ifndef __J4MEggInsideSD__hh
#define __J4MEggInsideSD__hh
//*************************************************************************
//* --------------------
//* J4MEggInsideSD
//* --------------------
//* (Description)
//* 	It appends Sensitive propaty to J4MEggInside. 
//*	Mother class : J4VSD <- G4VSensitiveDetector
//*     
//* (Update Record)
//*	2003/03/18  K.Hoshina	Original version.
//*************************************************************************
 
#include "J4VSD.hh"
#include "J4MEggInsideHit.hh"

//=====================================================================
//---------------------
// class definition
//---------------------


class J4MEggInsideSD : public J4VSD<J4MEggInsideHit>{
  
public:

  J4MEggInsideSD(J4VDetectorComponent* detector);
  ~J4MEggInsideSD();

  virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist);
  virtual void   Initialize (G4HCofThisEvent* HCTE);
  virtual void   EndOfEvent (G4HCofThisEvent* HCTE);

  virtual void   DrawAll();
  virtual void   PrintAll(); 
 
  virtual void   OutputAll(G4HCofThisEvent* HCTE)
  {
     if(GetHitBuf())
     {
       J4VSD<J4MEggInsideHit>::OutputAll(HCTE);
     }
     else
     {
       std::cerr << "J4MEggInsideSD::OutputAll: No HitBuf! " << std::endl;
     }
  }
  
  // set/get functions
   
private:

  
};

#endif

