// $Id: J43inchPMTSD.hh,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
#ifndef __J43inchPMTSD_hh
#define __J43inchPMTSD_hh
//*************************************************************************
//* --------------------
//* J43inchPMTSD
//* --------------------
//* (Description)
//* 	It appends Sensitive propaty to J43inchPMT. 
//*	Mother class : J4VSD <- G4VSensitiveDetector
//*     
//* (Update Record)
//*	2003/03/18  K.Hoshina	Original version.
//*************************************************************************
 
#include "J4VSD.hh"
#include "J43inchPMTHit.hh"

//=====================================================================
//---------------------
// class definition
//---------------------


class J43inchPMTSD : public J4VSD<J43inchPMTHit>{
  
public:

  J43inchPMTSD(J4VDetectorComponent* detector);
  ~J43inchPMTSD();

  virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist);
  virtual void   Initialize (G4HCofThisEvent* HCTE);
  virtual void   EndOfEvent (G4HCofThisEvent* HCTE);

  virtual void   DrawAll();
  virtual void   PrintAll(); 
 
  virtual void   OutputAll(G4HCofThisEvent* HCTE)
  {
     if(GetHitBuf())
     {
       J4VSD<J43inchPMTHit>::OutputAll(HCTE);
     }
     else
     {
       std::cerr << "J43inchPMTSD::OutputAll: No HitBuf! " << std::endl;
     }
  }
  
  // set/get functions
   
private:

  
};

#endif

