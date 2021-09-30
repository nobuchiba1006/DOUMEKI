// $Id: J4TrackingActionMessenger.cc,v 1.2 2007/03/13 17:29:14 hoshina Exp $
// GEANT4 tag $Name:  $
//

#include "J4TrackingActionMessenger.hh"
#include "J4TrackingAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4ios.hh"
#include "G4Tokenizer.hh"

#include <iomanip>               

J4TrackingActionMessenger::J4TrackingActionMessenger(J4TrackingAction * tracking)
  :fTrackingAction(tracking)
{
  fTrackingActionDir = new G4UIdirectory("/jupiter/tracking/");
  fTrackingActionDir->SetGuidance("JUPITER Tracking commands.");

  fChooseStoredTrajectoryCmd = new G4UIcmdWithAnInteger("/jupiter/tracking/ChooseStoredTrajectory",this);
  fChooseStoredTrajectoryCmd->SetGuidance("Choose stored trajectory");
  fChooseStoredTrajectoryCmd->SetGuidance("  1 : charged only. Default.");
  fChooseStoredTrajectoryCmd->SetGuidance("  2 : all ");
  fChooseStoredTrajectoryCmd->SetParameterName("N",true,true);
  fChooseStoredTrajectoryCmd->SetRange("N>0");

  // set initial value to J4TrackingAction
  fTrackingAction->SetStoredTrajectoryID(1);

#ifdef __THEBE__
  
  fStoreDebugPrintFromCmd = new G4UIcmdWithAnInteger("/jupiter/tracking/StoreDebugPrintFrom",this);
  fStoreDebugPrintFromCmd->SetGuidance("Store debug print from given trackID.");
  fStoreDebugPrintFromCmd->SetGuidance("  -2: no output, default");
  fStoreDebugPrintFromCmd->SetGuidance("  -1: the last track");
  fStoreDebugPrintFromCmd->SetGuidance("  N : only when TrackID=N");
  fStoreDebugPrintFromCmd->SetParameterName("N",true,true);
  fStoreDebugPrintFromCmd->SetRange("N>-3");
      
  // set initial value to J4TrackingAction
  fTrackingAction->SetStoredDebugPrintID(-3);

#endif

}

J4TrackingActionMessenger::~J4TrackingActionMessenger()
{

#ifdef __THEBE__

   delete fStoreDebugPrintFromCmd;

#endif

   delete fChooseStoredTrajectoryCmd;;
   delete fTrackingActionDir;
}

void J4TrackingActionMessenger::SetNewValue(G4UIcommand * command,G4String newValues)
{

  if( command == fChooseStoredTrajectoryCmd ) {
     fTrackingAction->SetStoredTrajectoryID(fChooseStoredTrajectoryCmd->GetNewIntValue(newValues)); 
  }

#ifdef __THEBE__

  if( command == fStoreDebugPrintFromCmd) {
     fTrackingAction->SetStoredDebugPrintID(fStoreDebugPrintFromCmd->GetNewIntValue(newValues)); 
  }

#endif

}

G4String J4TrackingActionMessenger::GetCurrentValue(G4UIcommand * command)
{
   G4String cv;

   if ( command == fChooseStoredTrajectoryCmd ) {
      cv = fChooseStoredTrajectoryCmd->ConvertToString(fTrackingAction->GetStoredTrajectoryID()); 
   } 

#ifdef __THEBE__   

   if( command == fStoreDebugPrintFromCmd) {
      cv = fStoreDebugPrintFromCmd->ConvertToString(fTrackingAction->GetStoredDebugPrintID());
   }

#endif
   
   return cv;

}

