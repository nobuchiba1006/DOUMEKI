// $Id: J4MEggGelHit.cc,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
//*************************************************************************
//* --------------------
//* J4MEggGelHit
//* --------------------
//* (Description)
//* 	Derivated concreate hit class for J4DEggGel.
//*	Mother class : J4VHit
//*     
//* (Update Record)
//*	2001/02/18  K.Hoshina	Original version.
//*     2020/09/03  M.Suzuki  Comment out Line 68-69 due to data garbling 
//*                  << std::setiosflags(std::ios::floatfield) 
//*                  << std::setprecision(8)
//*                  for Latest Geant4 
//*************************************************************************

#include <iomanip>
#include "J4MEggGelHit.hh"

//=========================================================================
//---------------------
// Allocator
//---------------------

J4MEggGelHitAllocator J4MEggGelHit::fHitAllocator ;
J4Output*             J4MEggGelHit::fOutput = 0 ;

//=========================================================================
//* constructor -----------------------------------------------------------

J4MEggGelHit::J4MEggGelHit(J4VComponent *dtc,
                G4ThreeVector         position, // position
                G4double              edep,     // Total Energy Deposit
                G4double              tof )     // TOF 
             : J4VHit(dtc), fPosition(position), 
               fEnergyDep(edep), fTof(tof)
{
}

//=========================================================================
//* destructor -----------------------------------------------------------

J4MEggGelHit::~J4MEggGelHit()
{
}


//=========================================================================
//* Output ------------------------------------------------------------------

void J4MEggGelHit::Output(G4HCofThisEvent* )
{
  if (fOutput) fOutput->Output(this);
  // output hitdata to output file ....
        
  std::ofstream& ofs = GetOutputFileStream();
  if (! ofs.good()) {
    G4String errorMessage= "J4MEggGelHit::Output(): write error.";
    G4Exception(errorMessage, "FATAL", FatalException, "");
  } else {
    const G4Event* anEvent = G4RunManager::GetRunManager()->GetCurrentEvent();
    G4int eventID = anEvent->GetEventID();
     ofs << std::setiosflags(std::ios::scientific) << std::setprecision(14)
	 << eventID << " " << 1 << " "
         << std::setw(18) << fPosition.x() << " " 
         << std::setw(18) << fPosition.y() << " " 
         << std::setw(18) << fPosition.z() << " " 
       // << std::setw(18) << fEnergyDep << " " 
       // << std::setw(18) << fTof << " "
       // << std::setiosflags(std::ios::floatfield) 
       // << std::setprecision(8)
         << std::endl;
  }

	
}

//=========================================================================
//* Draw ------------------------------------------------------------------

void J4MEggGelHit::Draw()
{
}

//=========================================================================
//* Print -----------------------------------------------------------------

void J4MEggGelHit::Print()
{
  std::cout << std::setiosflags(std::ios::fixed);
  std::cout << std::setw(20) << GetComponentName() << " " << std::endl;
  std::cout << " edep(GeV)= " << std::setprecision(2) 
         << std::setw(6) << fEnergyDep *(1./GeV) << " "
         << " TOF(ns)= " << std::setw(4) << std::setprecision(1) 
         << fTof /ns 
         << std::endl;  
}

