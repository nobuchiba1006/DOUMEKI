// $Id: J4RunActionMessenger.cc,v 1.2 2007/03/13 17:29:14 hoshina Exp $
// GEANT4 tag $Name:  $
//

#include "J4RunActionMessenger.hh"
#include "J4RunAction.hh"
#include "J4EventAction.hh"
#include "G4RunManager.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithABool.hh"
#include "G4ios.hh"
#include "G4Tokenizer.hh"

#include <iomanip>              

J4RunActionMessenger::J4RunActionMessenger(J4RunAction * tracking)
  :fRunAction(tracking)
{
  fRunActionDir = new G4UIdirectory("/jupiter/run/");
  fRunActionDir->SetGuidance("JUPITER Run commands.");


  fHitRootFileNameCmd = new G4UIcmdWithAString("/jupiter/run/SetHitRootFileName",this);
  fHitRootFileNameCmd->SetGuidance("Set hit root file name");
  fHitRootFileNameCmd->SetParameterName("filename",true,true);
  fHitRootFileNameCmd->SetDefaultValue("");

  fHitFileNameCmd = new G4UIcmdWithAString("/jupiter/run/SetHitFileName",this);
  fHitFileNameCmd->SetGuidance("Set hit file name");
  fHitFileNameCmd->SetParameterName("filename",true,true);
  fHitFileNameCmd->SetDefaultValue("hit.dat");

  fSetHeaderCmd = new G4UIcmdWithAString("/jupiter/run/SetHeaderString",this);
  fSetHeaderCmd->SetGuidance("Set header string");
  fSetHeaderCmd->SetParameterName("HeaderString",true,true);
  fSetHeaderCmd->SetDefaultValue("");

  fAddHeaderCmd = new G4UIcmdWithAString("/jupiter/run/AddHeaderString",this);
  fAddHeaderCmd->SetGuidance("Add header string. Added string starts from new line");
  fAddHeaderCmd->SetParameterName("AddHeaderString",true,true);
  fAddHeaderCmd->SetDefaultValue("");

  fFileOpenModeCmd = new G4UIcmdWithAString("/jupiter/run/SetFileOpenMode",this);
  fFileOpenModeCmd->SetGuidance("Set openfile mode: recreate or add");
  fFileOpenModeCmd->SetGuidance("default is recreate");
  fFileOpenModeCmd->SetParameterName("openmode",true,true);
  fFileOpenModeCmd->SetDefaultValue("recreate");
  fRunNumberCmd = new G4UIcmdWithAnInteger("/jupiter/run/SetRunNumber",this);
  fRunNumberCmd->SetGuidance("Set run number");
  fRunNumberCmd->SetParameterName("N",true,true);
  fRunNumberCmd->SetRange("N>=0");

  fSaveSeedCmd  = new G4UIcmdWithABool("/jupiter/run/SaveSeed",this);
}

J4RunActionMessenger::~J4RunActionMessenger()
{
   delete fHitFileNameCmd;;
   delete fHitRootFileNameCmd;;
   delete fSetHeaderCmd;;
   delete fAddHeaderCmd;;
   delete fFileOpenModeCmd;;
   delete fRunNumberCmd;;
   delete fRunActionDir;
   delete fSaveSeedCmd;
}

void J4RunActionMessenger::SetNewValue(G4UIcommand * command,G4String newValues)
{

  if( command == fHitFileNameCmd ) {
     fRunAction->SetHitFileName(newValues); 
  } else if( command == fHitRootFileNameCmd ) {
     fRunAction->SetHitRootFileName(newValues); 
  }else if ( command == fSetHeaderCmd ) {
     fRunAction->SetHeaderString(newValues); 
  } else if ( command == fAddHeaderCmd ) {
     fRunAction->AddHeaderString(newValues); 
  } else if( command == fFileOpenModeCmd ) {
     fRunAction->SetFileOpenMode(newValues); 
  }  else if( command == fRunNumberCmd ) {
     fRunAction->SetRunNumber(fRunNumberCmd->GetNewIntValue(newValues)); 
  }  else if( command == fSaveSeedCmd ) {
     G4UserEventAction *eva = const_cast<G4UserEventAction *>(G4RunManager::GetRunManager()->GetUserEventAction());
     J4EventAction *action = dynamic_cast<J4EventAction *>(eva);
     if (action) {
        action->SaveSeed(fSaveSeedCmd->GetNewBoolValue(newValues)); 
     } else {
        J4cerr << "EventAction is not J4EventAction, the command is ignored" << J4endl;
     }
  }
}

G4String J4RunActionMessenger::GetCurrentValue(G4UIcommand * command)
{
   G4String cv;

   if ( command == fHitFileNameCmd ) {
      cv = fRunAction->GetHitFileName();
   } else if ( command == fHitRootFileNameCmd ) {
      cv = fRunAction->GetHitRootFileName();
   } else if ( command == fSetHeaderCmd ) {
      cv = fRunAction->GetHeaderString();
   } else if ( command == fAddHeaderCmd ) {
      cv = fRunAction->GetHeaderString();
   } else if ( command == fFileOpenModeCmd ) {
      cv = fRunAction->GetFileOpenMode();
   } else if ( command == fRunNumberCmd ) {
      cv = fRunAction->GetRunNumber();
   } else if( command == fSaveSeedCmd ) {
     G4UserEventAction *eva = const_cast<G4UserEventAction *>(G4RunManager::GetRunManager()->GetUserEventAction());
     J4EventAction *action = dynamic_cast<J4EventAction *>(eva);
     if (action) {
        cv = action->GetSaveSeedFlag(); 
     } else {
        J4cerr << "EventAction is not J4EventAction, the command is ignored" << J4endl;
     }
  }
   
   return cv;

}

