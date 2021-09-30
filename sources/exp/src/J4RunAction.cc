// $Id: J4RunAction.cc,v 1.2 2007/03/13 17:29:14 hoshina Exp $
// ====================================================================
//    J4RunAction.cc
//
//                                   .JLC-CDC, 2001
// ====================================================================
#include "G4UImanager.hh"
#include "G4VVisManager.hh"
#include "G4Run.hh"

#include "J4RunAction.hh"
#include "J4RunActionMessenger.hh"

#define VERBOSE 1

 
int J4RunAction::RunID;
int J4RunAction::EventID;
int J4RunAction::ModID;
float J4RunAction::HitPos[3];
float J4RunAction::GenPos[3];
float J4RunAction::LocalPos[3];
float J4RunAction::LocalDir[3];
float J4RunAction::wavelength;
float J4RunAction::angle;
float J4RunAction::ce;





// ====================================================================
//
//      class description
//
// ====================================================================

///////////////////////////////////////////////////////////////
J4RunAction::J4RunAction(const G4String& fname)
  : fHitFileName(fname), fHitRootFileName(""), fFileOpenMode("recreate"), 
    fHeaderString("")
///////////////////////////////////////////////////////////////
{
   fMessenger = new J4RunActionMessenger(this);
}


////////////////////////////////////////////////////////
void J4RunAction::BeginOfRunAction(const G4Run*)
////////////////////////////////////////////////////////
{





  // choose file open mode
  if (fFileOpenMode == "recreate") {
     fOfs.open(fHitFileName.c_str(), std::ios::out);

     if (! fOfs.good()) {
         G4String errorMessage =
         "*** RunAction::BeginOfRunAtcion(): fail to open a file (" 
         + fHitFileName + ").";
         G4Exception(errorMessage, "FATAL", FatalException, "");
     }
 
     // output header string
     fOfs << fHeaderString << G4endl;

  } else if (fFileOpenMode == "add") {

     if (fRunNumber == 0) fOfs.open(fHitFileName.c_str(), std::ios::out);
     else fOfs.open(fHitFileName.c_str(), std::ios::app);

     if (! fOfs.good()) {
         G4String errorMessage =
         "*** RunAction::BeginOfRunAtcion(): fail to open a file (" 
         + fHitFileName + ").";
         G4Exception(errorMessage, "FATAL", FatalException, "");
     }
 
     std::streampos end = fOfs.tellp();
     fOfs.seekp(std::ios::beg);
     std::streampos beg = fOfs.tellp();
     if (end == beg) {
       /*
        // this is a new file!
        // output header string
       fOfs << "HEAD *" << G4endl
	    << "HEAD * Initial direction distribution:" << G4endl
	    << "HEAD * phi   [deg]: unif(0, 360)" << G4endl
	    << "HEAD * theta [deg]: unif(0, 30)" << G4endl
	    << "HEAD *" << G4endl
	    << "HEAD * Data format:" << G4endl
	    << "HEAD * [eventID] [SD(1:APMT;2:BPMT)] [initvecx] [initvecy] [initvecz] [x[mm]] [y[mm]] [z[mm]] [tof[ns]]" << G4endl
	    << "HEAD *" << G4endl
	    << G4endl
	    << fHeaderString << G4endl
	    << G4endl;
	  //	  << "data_format:eventID_SD(0:BubbleColumn;1:APMT;2:BPMT)_x[mm]_y[mm]_z[mm]_tof[ns]" << G4endl;
	  //	  << "data_format:eventID_SD(1:APMT;2:BPMT)_initvecx_initvecy_initvecz_x[mm]_y[mm]_z[mm]_tof[ns]" << G4endl;

       */
     } else {
        // this is NOT a new file. back to the end point...
        fOfs.seekp(end);
     }
  }

  J4VHit::SetOutputFileStream(fOfs);
  fOfs << "-99999999 *****_Run_" << fRunNumber << "_Start_*****" << G4endl;
#ifdef VERBOSE
  std::cout << "*****_Run_" << fRunNumber << "_Start_*****" << std::endl;
#endif

  // uncomment the following lines, if you want to 
  // automatically clear trajectories etc. in the current view.
  //G4UImanager* UI= G4UImanager::GetUIpointer();
  //UI-> ApplyCommand("/vis/scene/notifyHandlers");
  //if(G4VVisManager::GetConcreteInstance()) UI-> ApplyCommand("/vis/clear/view"); 
}

void J4RunAction::CloseRootFile(){
}


//////////////////////////////////////////////////////
void J4RunAction::EndOfRunAction(const G4Run* aRun)
//////////////////////////////////////////////////////
{
  G4UImanager* UI= G4UImanager::GetUIpointer();
#if 0
  if (G4VVisManager::GetConcreteInstance()) {
    UI-> ApplyCommand("/vis/scene/notifyHandlers");
    G4UImanager::GetUIpointer()-> ApplyCommand("/vis/draw/update");
  }  
#endif
  fOfs.close();
#ifdef VERBOSE
  std::cout << "#events generated= " << aRun-> GetNumberOfEvent() << std::endl;
#endif
}

