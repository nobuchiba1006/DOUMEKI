// $Id: J4RunActionMessenger.hh,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
// GEANT4 tag $Name:  $
// 

#ifndef J4RunActionMessenger_h
#define J4RunActionMessenger_h 1

class J4RunAction;
class G4UIcommand;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithABool;

#include "G4UImessenger.hh"
#include "globals.hh"

// class description:
//
//  This is a concrete class of G4UImessenger which handles commands for
// J4RunAction.
//

class J4RunActionMessenger: public G4UImessenger
{
  public:
    J4RunActionMessenger(J4RunAction * fRunAction);
    ~J4RunActionMessenger();
    
  public:
    void SetNewValue(G4UIcommand * command,G4String newValues);
    G4String GetCurrentValue(G4UIcommand * command);

  private:
    J4RunAction * fRunAction;

  private: //commands
    G4UIdirectory *             fRunActionDir;
    G4UIcmdWithAString *        fHitFileNameCmd;
    G4UIcmdWithAString *        fSetHeaderCmd;
    G4UIcmdWithAString *        fAddHeaderCmd;
    G4UIcmdWithAString *        fFileOpenModeCmd;
    G4UIcmdWithAnInteger *      fRunNumberCmd;
    G4UIcmdWithABool *          fSaveSeedCmd;
    
};

#endif

