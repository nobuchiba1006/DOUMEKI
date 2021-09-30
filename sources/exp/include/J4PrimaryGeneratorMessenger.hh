// $Id: J4PrimaryGeneratorMessenger.hh,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $

#ifndef J4PrimaryGeneratorMessenger_h
#define J4PrimaryGeneratorMessenger_h 1

class J4PrimaryGeneratorAction;
class G4UIdirectory;
class G4UIcmdWithAString;

#include "G4UImessenger.hh"
#include "globals.hh"

class J4PrimaryGeneratorMessenger: public G4UImessenger
{
  public:
    J4PrimaryGeneratorMessenger(J4PrimaryGeneratorAction *mpga);
    ~J4PrimaryGeneratorMessenger();
    
  public:
    void SetNewValue(G4UIcommand *command, G4String newValues);
    G4String GetCurrentValue(G4UIcommand *command);

  private:
    J4PrimaryGeneratorAction   *fAction;
    
  private: //commands
    G4UIdirectory              *fDirectory;
    G4UIcmdWithAString         *fGenCmd;
    
};

#endif


