// $Id: J48inchPMTSD.hh,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
#ifndef __J48inchPMTSD__hh
#define __J48inchPMTSD__hh
//*************************************************************************
//* --------------------
//* J48inchPMTSD
//* --------------------
//* (Description)
//* 	It appends Sensitive propaty to J48inchPMT. 
//*	Mother class : J4VSD <- G4VSensitiveDetector
//*     
//* (Update Record)
//*	2003/03/18  K.Hoshina	Original version.
//*************************************************************************
 
#include "J4VSD.hh"
#include "J48inchPMTHit.hh"
#include "J4ChargeResponse.hh"
#include <map>

//=====================================================================
//---------------------
// class definition
//---------------------


class J48inchPMTSD : public J4VSD<J48inchPMTHit>{
  
public:

  J48inchPMTSD(J4VDetectorComponent* detector);
  ~J48inchPMTSD();

  virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist);
  virtual void   Initialize (G4HCofThisEvent* HCTE);
  virtual void   EndOfEvent (G4HCofThisEvent* HCTE);

  virtual void   DrawAll();
  virtual void   PrintAll(); 
 
  virtual void   OutputAll(G4HCofThisEvent* HCTE)
  {
     if(GetHitBuf())
     {
       J4VSD<J48inchPMTHit>::OutputAll(HCTE);
     }
     else
     {
       std::cerr << "J48inchPMTSD::OutputAll: No HitBuf! " << std::endl;
     }
  }
  
  // set/get functions
   
private:

  void LoadCETable_1D();
  G4double GetCE_1D(G4double zendeg);
  G4double GetCharge(G4double zendeg);

  std::map<G4double, G4double> fCE1D; 

  J4ChargeResponse *fChargeResponse1;
  J4ChargeResponse *fChargeResponse2;
  
};

#endif

