// $Id: J4MEggGelSD.hh,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
#ifndef __J4MEggGelSD__hh
#define __J4MEggGelSD__hh
//*************************************************************************
//* --------------------
//* J4MEggGelSD
//* --------------------
//* (Description)
//* 	It appends Sensitive propaty to J4MEggGel. 
//*	Mother class : J4VSD <- G4VSensitiveDetector
//*     
//* (Update Record)
//*	2003/03/18  K.Hoshina	Original version.
//*************************************************************************
 
#include "J4VSD.hh"
#include "J4MEggGelHit.hh"

//=====================================================================
//---------------------
// class definition
//---------------------


class J4MEggGelSD : public J4VSD<J4MEggGelHit>{
  
public:

  J4MEggGelSD(J4VDetectorComponent* detector);
  ~J4MEggGelSD();

  virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist);
  virtual void   Initialize (G4HCofThisEvent* HCTE);
  virtual void   EndOfEvent (G4HCofThisEvent* HCTE);

  virtual void   DrawAll();
  virtual void   PrintAll(); 
 
  virtual void   OutputAll(G4HCofThisEvent* HCTE)
  {
     if(GetHitBuf())
     {
       J4VSD<J4MEggGelHit>::OutputAll(HCTE);
     }
     else
     {
       std::cerr << "J4MEggGelSD::OutputAll: No HitBuf! " << std::endl;
     }
  }
  
  // set/get functions
   
private:

  
};

#endif

