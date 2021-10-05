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
               	G4ThreeVector  localpos,
               	G4ThreeVector  localdir,
                G4double              ce,       // collection efficiency
                G4double              edep,     // Total Energy Deposit
                G4double              tof )     // TOF 
             : J4VHit(dtc), fPosition(position), 
				 fLocalPosition(localpos), fLocalDirection(localdir),
               fEnergyDep(edep), fTof(tof), fCE(ce)
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

  
	  const G4Event* anEvent = G4RunManager::GetRunManager()->GetCurrentEvent();
	  G4int eventID = anEvent->GetEventID();
	  G4String MyName = GetComponent()->GetName();

     
	  ofs << std::setiosflags(std::ios::scientific) << std::setprecision(14)
          << std::setw(18) << fPosition.x()/mm << " " 
          << std::setw(18) << fPosition.y()/mm << " " 
          << std::setw(18) << fPosition.z()/mm << " " 
          << std::setw(18) << fEnergyDep/MeV << " " 
          << std::setw(18) << fTof/ns << " "
          << std::setiosflags(std::ios::floatfield) 
          << std::setprecision(8)
          << std::endl;


	 J4RunAction* j4runaction = ((J4RunAction*) (G4RunManager::GetRunManager()->GetUserRunAction()));
 	 if(j4runaction->trout!=nullptr){


		int pos_PMT = MyName.rfind("PMT");
		MyName = MyName.substr(pos_PMT+3, 2);

		j4runaction->EventID = eventID;
		j4runaction->ModID   = atoi(MyName.c_str());
		j4runaction->HitPos[0] = fPosition.x();
		j4runaction->HitPos[1] = fPosition.y();
		j4runaction->HitPos[2] = fPosition.z();
		j4runaction->LocalPos[0] = fLocalPosition.x();
		j4runaction->LocalPos[1] = fLocalPosition.y();
		j4runaction->LocalPos[2] = fLocalPosition.z();
  		j4runaction->LocalDir[0] = fLocalDirection.x();
		j4runaction->LocalDir[1] = fLocalDirection.y();
		j4runaction->LocalDir[2] = fLocalDirection.z();
		j4runaction->ce = fCE;
   

		G4ThreeVector pos = anEvent->GetPrimaryVertex()->GetPosition();
		
		j4runaction->GenPos[0] = pos.x();
		j4runaction->GenPos[1] = pos.y();
		j4runaction->GenPos[2] = pos.z();
	
		double ene = anEvent->GetPrimaryVertex()->GetPrimary()->GetKineticEnergy()/eV;
		G4ThreeVector dir = anEvent->GetPrimaryVertex()->GetPrimary()->GetMomentumDirection().unit();

		double th = acos(dir.z());

		j4runaction->wavelength = 1240.0/ene;
		j4runaction->angle = th;
		j4runaction->trout->Fill();

	}







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

