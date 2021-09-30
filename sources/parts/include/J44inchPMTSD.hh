// $Id: J44inchPMTSD.hh,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
#ifndef __J44inchPMTSD_hh
#define __J44inchPMTSD_hh
//*************************************************************************
//* --------------------
//* J44inchPMTSD
//* --------------------
//* (Description)
//* 	It appends Sensitive propaty to J44inchPMT. 
//*	Mother class : J4VSD <- G4VSensitiveDetector
//*     
//* (Update Record)
//*	2003/03/18  K.Hoshina	Original version.
//*************************************************************************
 
#include "J4VSD.hh"
#include "J44inchPMTHit.hh"

//=====================================================================
//---------------------
// class definition
//---------------------


class J44inchPMTSD : public J4VSD<J44inchPMTHit>{
  
public:

  J44inchPMTSD(J4VDetectorComponent* detector);
  ~J44inchPMTSD();

  virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist);
  virtual void   Initialize (G4HCofThisEvent* HCTE);
  virtual void   EndOfEvent (G4HCofThisEvent* HCTE);

  virtual void   DrawAll();
  virtual void   PrintAll(); 
 
  virtual void   OutputAll(G4HCofThisEvent* HCTE)
  {
     if(GetHitBuf())
     {
       J4VSD<J44inchPMTHit>::OutputAll(HCTE);
     }
     else
     {
       std::cerr << "J44inchPMTSD::OutputAll: No HitBuf! " << std::endl;
     }
  }
  
  // set/get functions
   
private:

  
};

#endif

