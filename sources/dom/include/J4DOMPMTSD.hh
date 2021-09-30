// $Id: J4DOMPMTSD.hh,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
#ifndef __J4DCLAYERSD__hh
#define __J4DCLAYERSD__hh
//*************************************************************************
//* --------------------
//* J4DOMPMTSD
//* --------------------
//* (Description)
//* 	It appends Sensitive propaty to J4DOMPMT. 
//*	Mother class : J4VSD <- G4VSensitiveDetector
//*     
//* (Update Record)
//*	2003/03/18  K.Hoshina	Original version.
//*************************************************************************
 
#include "J4VSD.hh"
#include "J4DOMPMTHit.hh"

//=====================================================================
//---------------------
// class definition
//---------------------


class J4DOMPMTSD : public J4VSD<J4DOMPMTHit>{
  
public:

  J4DOMPMTSD(J4VDetectorComponent* detector);
  ~J4DOMPMTSD();

  virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist);
  virtual void   Initialize (G4HCofThisEvent* HCTE);
  virtual void   EndOfEvent (G4HCofThisEvent* HCTE);

  virtual void   DrawAll();
  virtual void   PrintAll(); 
 
  virtual void   OutputAll(G4HCofThisEvent* HCTE)
  {
     if(GetHitBuf())
     {
       J4VSD<J4DOMPMTHit>::OutputAll(HCTE);
     }
     else
     {
       std::cerr << "J4DOMPMTSD::OutputAll: No HitBuf! " << std::endl;
     }
  }
  
  // set/get functions
   
private:

  
};

#endif

