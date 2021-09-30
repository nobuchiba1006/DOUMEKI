// $Id: J48inchPMTHit.cc,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
//*************************************************************************
//* --------------------
//* J48inchPMTHit
//* --------------------
//* (Description)
//* 	Derivated concreate hit class for J48inchPMT.
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
//*     2021/06/01  K.Hoshina renamed from J4DEggPMTHit and modified data members
//*************************************************************************

#include <iomanip>
#include "J48inchPMTHit.hh"

//=========================================================================
//---------------------
// Allocator
//---------------------

J48inchPMTHitAllocator J48inchPMTHit::fHitAllocator ;
J4Output*             J48inchPMTHit::fOutput = 0 ;

//=========================================================================
//* constructor -----------------------------------------------------------

J48inchPMTHit::J48inchPMTHit(J4VComponent *dtc,
                G4ThreeVector         position, // position
                G4double              ce)       // average CE
             : J4VHit(dtc), fPosition(position), 
               fCE(ce)
{
}

//=========================================================================
//* destructor -----------------------------------------------------------

J48inchPMTHit::~J48inchPMTHit()
{
}

//=========================================================================
//* Output ------------------------------------------------------------------

void J48inchPMTHit::Output(G4HCofThisEvent* )
{
  if (fOutput) fOutput->Output(this);
  // output hitdata to output file ....
        
  std::ofstream& ofs = GetOutputFileStream();
  if (! ofs.good()) {
    G4String errorMessage= "J48inchPMTHit::Output(): write error.";
    G4Exception(errorMessage, "FATAL", FatalException, "");
  } else {
    const G4Event* anEvent = G4RunManager::GetRunManager()->GetCurrentEvent();
    G4int eventID = anEvent->GetEventID();
    G4String MyName = GetComponent()->GetName();
    //MyName = MyName.substr(23,2); //pick up only PMT numbers

    G4int momID = GetComponent()->GetMother()->GetMyID(); 
    G4int myID  = GetComponent()->GetMyID(); 

    G4double theta = fPosition.theta();
    G4double phi   = fPosition.phi();

     ofs << std::setiosflags(std::ios::scientific) << std::setprecision(14)

	 << eventID << " "
	 << momID << " "
	 << myID << " "
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

void J48inchPMTHit::Draw()
{
}

//=========================================================================
//* Print -----------------------------------------------------------------

void J48inchPMTHit::Print()
{
  std::cout << std::setiosflags(std::ios::fixed);
  std::cout << std::setw(20) << GetComponentName() << " " << std::endl;
  std::cout << " CE = " << std::setprecision(2) 
         << std::setw(6) << fCE << " "
         << std::endl;  
}

