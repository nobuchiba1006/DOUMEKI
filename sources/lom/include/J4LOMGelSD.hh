// $Id: J4LOMGelSD.hh,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
#ifndef __J4LOMGelSD__hh
#define __J4LOMGelSD__hh
//*************************************************************************
//* --------------------
//* J4LOMGelSD
//* --------------------
//* (Description)
//* 	It appends Sensitive propaty to J4LOMGel. 
//*	Mother class : J4VSD <- G4VSensitiveDetector
//*     
//* (Update Record)
//*	2003/03/18  K.Hoshina	Original version.
//*************************************************************************
 
#include "J4VSD.hh"
#include "J4LOMGelHit.hh"

//=====================================================================
//---------------------
// class definition
//---------------------


class J4LOMGelSD : public J4VSD<J4LOMGelHit>{
  
public:

  J4LOMGelSD(J4VDetectorComponent* detector);
  ~J4LOMGelSD();

  virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist);
  virtual void   Initialize (G4HCofThisEvent* HCTE);
  virtual void   EndOfEvent (G4HCofThisEvent* HCTE);

  virtual void   DrawAll();
  virtual void   PrintAll(); 
 
  virtual void   OutputAll(G4HCofThisEvent* HCTE)
  {
     if(GetHitBuf())
     {
       J4VSD<J4LOMGelHit>::OutputAll(HCTE);
     }
     else
     {
       std::cerr << "J4LOMGelSD::OutputAll: No HitBuf! " << std::endl;
     }
  }
  
  // set/get functions
   
private:

  
};

#endif

