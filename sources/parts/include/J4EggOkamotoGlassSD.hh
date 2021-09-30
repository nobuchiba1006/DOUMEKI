// $Id: J4EggOkamotoGlassSD.hh,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
#ifndef __J4EggOkamotoGlassSD__hh
#define __J4EggOkamotoGlassSD__hh
//*************************************************************************
//* --------------------
//* J4EggOkamotoGlassSD
//* --------------------
//* (Description)
//* 	It appends Sensitive propaty to J4DEggOkamoto. 
//*	Mother class : J4VSD <- G4VSensitiveDetector
//*     
//* (Update Record)
//*	2003/03/18  K.Hoshina	Original version.
//*************************************************************************
 
#include "J4VSD.hh"
#include "J4EggOkamotoGlassHit.hh"

//=====================================================================
//---------------------
// class definition
//---------------------


class J4EggOkamotoGlassSD : public J4VSD<J4EggOkamotoGlassHit>{
  
public:

  J4EggOkamotoGlassSD(J4VDetectorComponent* detector);
  ~J4EggOkamotoGlassSD();

  virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist);
  virtual void   Initialize (G4HCofThisEvent* HCTE);
  virtual void   EndOfEvent (G4HCofThisEvent* HCTE);

  virtual void   DrawAll();
  virtual void   PrintAll(); 
 
  virtual void   OutputAll(G4HCofThisEvent* HCTE)
  {
     if(GetHitBuf())
     {
       J4VSD<J4EggOkamotoGlassHit>::OutputAll(HCTE);
     }
     else
     {
       std::cerr << "J4EggOkamotoGlassSD::OutputAll: No HitBuf! " << std::endl;
     }
  }
  
  // set/get functions
   
private:

  
};

#endif

