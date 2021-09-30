// $Id: J43inchPMTHit.cc,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
//*************************************************************************
//* --------------------
//* J43inchPMTHit
//* --------------------
//* (Description)
//* 	Derivated concreate hit class for J43inchPMT.
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
#include "J43inchPMTHit.hh"

//=========================================================================
//---------------------
// Allocator
//---------------------

J43inchPMTHitAllocator J43inchPMTHit::fHitAllocator ;
J4Output*             J43inchPMTHit::fOutput = 0 ;

//=========================================================================
//* constructor -----------------------------------------------------------

J43inchPMTHit::J43inchPMTHit(J4VComponent *dtc,
                G4ThreeVector         position, // position
               	G4ThreeVector  localpos,
               	G4ThreeVector  localdir,
                G4double              ce,       // average CE
                G4int                 momid,    // inside module ID
                G4int                 myid)     // pmt id
              : J4VHit(dtc), fPosition(position), 
				 fLocalPosition(localpos), fLocalDirection(localdir),
               fCE(ce), fMomID(momid), fMyID(myid)
{
}

//=========================================================================
//* destructor -----------------------------------------------------------

J43inchPMTHit::~J43inchPMTHit()
{
}


//=========================================================================
//* Output ------------------------------------------------------------------

void J43inchPMTHit::Output(G4HCofThisEvent* )
{
  if (fOutput) fOutput->Output(this);
  // output hitdata to output file ....
        
  std::ofstream& ofs = GetOutputFileStream();
  if (! ofs.good()) {
    G4String errorMessage= "J43inchPMTHit::Output(): write error.";
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



	 J4RunAction* j4runaction = ((J4RunAction*) (G4RunManager::GetRunManager()->GetUserRunAction()));
 	 // for root version
	 if(0){


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

	}




  }

	
}

//=========================================================================
//* Draw ------------------------------------------------------------------

void J43inchPMTHit::Draw()
{
}

//=========================================================================
//* Print -----------------------------------------------------------------

void J43inchPMTHit::Print()
{
  std::cout << std::setiosflags(std::ios::fixed);
  std::cout << std::setw(20) << GetComponentName() << " " << std::endl;
}

