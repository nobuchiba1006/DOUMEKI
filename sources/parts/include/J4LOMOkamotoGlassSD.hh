// $Id: J4LOMOkamotoGlassSD.hh,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
#ifndef __J4LOMOkamotoGlassSD__hh
#define __J4LOMOkamotoGlassSD__hh
//*************************************************************************
//* --------------------
//* J4LOMOkamotoGlassSD
//* --------------------
//* (Description)
//* 	It appends Sensitive propaty to J4DLOMOkamoto. 
//*	Mother class : J4VSD <- G4VSensitiveDetector
//*     
//* (Update Record)
//*	2003/03/18  K.Hoshina	Original version.
//*************************************************************************
 
#include "J4VSD.hh"
#include "J4LOMOkamotoGlassHit.hh"

//=====================================================================
//---------------------
// class definition
//---------------------


class J4LOMOkamotoGlassSD : public J4VSD<J4LOMOkamotoGlassHit>{
  
public:

  J4LOMOkamotoGlassSD(J4VDetectorComponent* detector);
  ~J4LOMOkamotoGlassSD();

  virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist);
  virtual void   Initialize (G4HCofThisEvent* HCTE);
  virtual void   EndOfEvent (G4HCofThisEvent* HCTE);

  virtual void   DrawAll();
  virtual void   PrintAll(); 
 
  virtual void   OutputAll(G4HCofThisEvent* HCTE)
  {
     if(GetHitBuf())
     {
       J4VSD<J4LOMOkamotoGlassHit>::OutputAll(HCTE);
     }
     else
     {
       std::cerr << "J4LOMOkamotoGlassSD::OutputAll: No HitBuf! " << std::endl;
     }
  }
  
  // set/get functions
   
private:

  
};

#endif

