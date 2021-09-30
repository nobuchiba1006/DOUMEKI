// $Id: J4EventAction.cc,v 1.2 2007/03/13 17:29:14 hoshina Exp $
// ====================================================================
//      J4EventAction.cc
//
//                                 .JLC-CDC, 2001
// ====================================================================
#include <sstream>
#include <fstream>
#include <iomanip>
#include "J4Global.hh"
#include "J4Timer.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"

#include "J4RunAction.hh"
#include "J4EventAction.hh"

#include "G4VHitsCollection.hh"

#include "J4DetectorConstruction.hh"

// SD of each detector componet

// Visualization
#include "G4UImanager.hh"
#include "G4VVisManager.hh"
#include "G4Trajectory.hh"
  
#define __VERBOSE__ 1

// ====================================================================
//
// class description
//
// ====================================================================

////////////////////////////////////
J4EventAction::J4EventAction()
////////////////////////////////////
{
   //std::cerr << "J4EventAction::constructor called" << G4endl;
   G4int timerid = -1;
   G4String classname("J4EventAction");
   G4String timername("EventTimer");
   //std::cerr << "J4EventAction::constructor timer new" << G4endl;
   fEventTimer = new J4Timer(timerid, classname, timername);
   //std::cerr << "J4EventAction::constructor timer created" << G4endl;
   fSaveSeed = false;
}

////////////////////////////////////
J4EventAction::~J4EventAction()
////////////////////////////////////
{
   delete fEventTimer;
}

/////////////////////////////////////////////////////////////////
void J4EventAction::BeginOfEventAction(const G4Event* anEvent)
/////////////////////////////////////////////////////////////////
{
  // printout primary information
#ifdef __THEBE__
   if ( J4Global::GetErrorOutputUnit() == "Event" ) {
      if ( !fErrorOfs.is_open() ) {
         fErrorOfs.open(J4Global::GetErrorOutputFilename().c_str(), std::ios::out);
         if(! fErrorOfs.good()) {
            G4String errorMessage=
            "*** EventAction::BeginOfEventAction():fail to open a file ("
            + J4Global::GetErrorOutputFilename() + ").";
            G4Exception(errorMessage, "FATAL", FatalException, "");
         } else {
            J4Global::SetErrorOutputStream(fErrorOfs);
         }
      }
   }
#endif
         
//#ifdef __VERBOSE__
   G4cout << "%%%%%%%% Primary Information %%%%%%%%%" << G4endl;
   G4int nVtx= anEvent-> GetNumberOfPrimaryVertex();
   G4int i;
   for(i=0; i< nVtx; i++) {
      const G4PrimaryVertex* primaryVertex= anEvent-> GetPrimaryVertex(i);
      primaryVertex-> Print();  
   }
   G4cout << "%%%%%%%% Primary Information end EventNo = " 
          << anEvent->GetEventID() << " %%%%%%%%%" <<G4endl << std::flush;
//#endif  

   J4DetectorConstruction::GetEXPHall()->UnlockOutput();
   fEventTimer->Start();
   
}

///////////////////////////////////////////////////////////////
void J4EventAction::EndOfEventAction(const G4Event* anEvent)
///////////////////////////////////////////////////////////////
{
  const G4RunManager* runManager= G4RunManager::GetRunManager();
  const G4UserRunAction* usrRunAction= runManager-> GetUserRunAction();

  // ====================================================================  
  // printout hit information of each detector

     G4int event = anEvent->GetEventID();

     //std::cerr << "**********************************************" << G4endl;
     //std::cerr << "*******_event_number_" << event << "_*******" <<G4endl;
     //std::cerr << "**********************************************" << G4endl;


  // ====================================================================  
  // output "Hit Collection of This Event" to a hit data file
  
  G4HCofThisEvent* HCTE= anEvent-> GetHCofThisEvent();
  
  if(! HCTE) return;  // no hits in this events. nothing to do!
  
  //std::cerr << "EventAction :: HCTE = "<< HCTE->GetNumberOfCollections()<<G4endl;
  
  std::ofstream& ofs= ((J4RunAction*)usrRunAction)-> GetOutputFileStream();
  if(! ofs.good()) {
    G4String errorMessage= "EventAction::EndOfEventAction(): write error.";
    G4Exception(errorMessage, "FATAL", FatalException, "");
  }
  
 
  // =====================================================================
  // Trigger system
  
  // =====================================================================
  // 
  
   //std::cerr << "EventAction::EndOfEvent is called " << G4endl;
     
   J4DetectorConstruction::GetEXPHall()->OutputAll(HCTE, ofs);
     
   //std::cerr << "EventAction::OutputAll finished " << G4endl;
  
   fEventTimer->Stop();

  // J4Timer::PrintAllAccumulatedTimes();

  // ---------------------------------------------------------------------
  // visualization.......
  
  // get number of stored trajectories
  //

#if 0 

  G4TrajectoryContainer* trajectoryContainer = anEvent->GetTrajectoryContainer();
  G4int n_trajectories = 0;
  if (trajectoryContainer) n_trajectories = trajectoryContainer->entries();
  
  // periodic printing
  //
  if (event % 100 == 0) {
    G4cout << ">>> Event " << event << G4endl;
    G4cout << "    " << n_trajectories 
           << " trajectories stored in this event." << G4endl;
  }
    
  // extract the trajectories and draw them
  //
  if (G4VVisManager::GetConcreteInstance()) {
     for (G4int i=0; i<n_trajectories; i++) { 
        G4Trajectory* trj = (G4Trajectory*)
                            ((*(anEvent->GetTrajectoryContainer()))[i]);
        trj->DrawTrajectory(50);
     }
  }

#endif
   
  // ---------------------------------------------------------------------
  // end of event.......

   if (fSaveSeed) {
      std::stringstream tmpstr;
      tmpstr << "seeds/seed.evt." << std::setw(5) << std::setfill('0')
         << event << std::ends;
      CLHEP::HepRandom::saveEngineStatus(tmpstr.str().data());
   }

#ifdef __THEBE__
   if ( J4Global::GetErrorOutputUnit() == "Event" ) {
      J4Global::GetGlobal()->CloseErrorOutputStream();
   }
#endif
              
}
