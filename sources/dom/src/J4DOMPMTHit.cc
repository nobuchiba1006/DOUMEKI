// $Id: J4DOMPMTHit.cc,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
//*************************************************************************
//* --------------------
//* J4DOMPMTHit
//* --------------------
//* (Description)
//* 	Derivated concreate hit class for J4DOMPMT.
//*	Mother class : J4VHit
//*     
//* (Update Record)
//*	2001/02/18  K.Hoshina	Original version.
//*************************************************************************

#include <iomanip>
#include "J4DOMPMTHit.hh"

//=========================================================================
//---------------------
// Allocator
//---------------------

J4DOMPMTHitAllocator J4DOMPMTHit::fHitAllocator ;
J4Output*             J4DOMPMTHit::fOutput = 0 ;

//=========================================================================
//* constructor -----------------------------------------------------------

J4DOMPMTHit::J4DOMPMTHit(J4VComponent *dtc,
                G4ThreeVector         position, // position
                G4double              edep,     // Total Energy Deposit
                G4double              tof )     // TOF 
             : J4VHit(dtc), fPosition(position), 
               fEnergyDep(edep), fTof(tof)
{
}

//=========================================================================
//* destructor -----------------------------------------------------------

J4DOMPMTHit::~J4DOMPMTHit()
{
}


//=========================================================================
//* Output ------------------------------------------------------------------

void J4DOMPMTHit::Output(G4HCofThisEvent* )
{
  if (fOutput) fOutput->Output(this);
  // output hitdata to output file ....
        
  std::ofstream& ofs = GetOutputFileStream();
  if (! ofs.good()) {
    G4String errorMessage= "J4DOMPMTHit::Output(): write error.";
    G4Exception(errorMessage, "FATAL", FatalException, "");
  } else {

     ofs << std::setiosflags(std::ios::scientific) << std::setprecision(14)
         << std::setw(18) << fPosition.x()/mm << " " 
         << std::setw(18) << fPosition.y()/mm << " " 
         << std::setw(18) << fPosition.z()/mm << " " 
         << std::setw(18) << fEnergyDep/MeV << " " 
         << std::setw(18) << fTof/ns << " "
         << std::setiosflags(std::ios::floatfield) 
         << std::setprecision(8)
         << std::endl;
  }
}

//=========================================================================
//* Draw ------------------------------------------------------------------

void J4DOMPMTHit::Draw()
{
}

//=========================================================================
//* Print -----------------------------------------------------------------

void J4DOMPMTHit::Print()
{

  std::cout << std::setiosflags(std::ios::fixed);
  std::cout << std::setw(20) << GetComponentName() << " " << std::endl;
  std::cout << " edep(GeV)= " << std::setprecision(2) 
         << std::setw(6) << fEnergyDep *(1./GeV) << " "
         << " TOF(ns)= " << std::setw(4) << std::setprecision(1) 
         << fTof /ns 
         << std::endl;  
}

