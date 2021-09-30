// $Id: J44inchPMTHit.cc,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
//*************************************************************************
//* --------------------
//* J44inchPMTHit
//* --------------------
//* (Description)
//* 	Derivated concreate hit class for J44inchPMT.
//*	Mother class : J4VHit
//*     
//* (Update Record)
//*	2001/02/18  K.Hoshina	Original version.
//*     2020/05/**  M.Suzuki  Add Line 66 to print hit PMT number
//*                  G4String MyName = GetComponent()->GetName();
//*     2020/09/03  M.Suzuki  Comment out Line 68-69 due to data garbling 
//*                  << std::setiosflags(std::ios::floatfield) 
//*                  << std::setprecision(8)
//*                 for Latest Geant4 
//*************************************************************************

#include <iomanip>
#include "J44inchPMTHit.hh"

//=========================================================================
//---------------------
// Allocator
//---------------------

J44inchPMTHitAllocator J44inchPMTHit::fHitAllocator ;
J4Output*             J44inchPMTHit::fOutput = 0 ;

//=========================================================================
//* constructor -----------------------------------------------------------

J44inchPMTHit::J44inchPMTHit(J4VComponent *dtc,
                G4ThreeVector         position, // position
                G4double              ce,       // average CE
                G4int                 momid,    // inside module ID
                G4int                 myid)     // pmt id
              : J4VHit(dtc), fPosition(position), 
               fCE(ce), fMomID(momid), fMyID(myid)
{
}

//=========================================================================
//* destructor -----------------------------------------------------------

J44inchPMTHit::~J44inchPMTHit()
{
}


//=========================================================================
//* Output ------------------------------------------------------------------

void J44inchPMTHit::Output(G4HCofThisEvent* )
{
  if (fOutput) fOutput->Output(this);
  // output hitdata to output file ....
        
  std::ofstream& ofs = GetOutputFileStream();
  if (! ofs.good()) {
    G4String errorMessage= "J44inchPMTHit::Output(): write error.";
    G4Exception(errorMessage, "FATAL", FatalException, "");
  } else {
    const G4Event* anEvent = G4RunManager::GetRunManager()->GetCurrentEvent();
    G4int eventID = anEvent->GetEventID();
    G4String MyName = GetComponent()->GetName();
    //MyName = MyName.substr(23,2); //pick up only PMT numbers

    G4double theta = fPosition.theta();
    G4double phi   = fPosition.phi();



     ofs << std::setiosflags(std::ios::scientific) << std::setprecision(14)

	 << eventID << " "
	 << fMomID << " "
	 << fMyID << " "
         //<< std::setw(18) << fPosition.x() << " " 
         //<< std::setw(18) << fPosition.y() << " " 
         //<< std::setw(18) << fPosition.z() << " " 
         << std::setw(18) << theta/deg << " " 
         << std::setw(18) << phi/deg << " " 
         << std::setw(18) << fCE<< " " 
	 << MyName << " "
       ///  << std::setiosflags(std::ios::floatfield) 
       //  << std::setprecision(8)
         << std::endl;
  }

	
}

//=========================================================================
//* Draw ------------------------------------------------------------------

void J44inchPMTHit::Draw()
{
}

//=========================================================================
//* Print -----------------------------------------------------------------

void J44inchPMTHit::Print()
{
  std::cout << std::setiosflags(std::ios::fixed);
  std::cout << std::setw(20) << GetComponentName() << " " << std::endl;
}

