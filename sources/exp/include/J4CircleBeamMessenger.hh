// $Id: J4CircleBeamMessenger.hh,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
// GEANT4 tag $Name:  $
//
// 

#ifndef J4CircleBeamMessenger_h
#define J4CircleBeamMessenger_h 1

class J4CircleBeam;
class G4ParticleTable;
class G4UIcommand;
class G4UIdirectory;
class G4UIcmdWithoutParameter;
class G4UIcmdWithAString;
class G4UIcmdWithABool;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithADouble;
class G4UIcmdWith3Vector;
class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWithAnInteger;

#include "G4UImessenger.hh"
#include "globals.hh"

// class description:
//
//  This is a concrete class of G4UImessenger which handles commands for
// J4CircleBeam.
//

class J4CircleBeamMessenger: public G4UImessenger
{
  public:
    J4CircleBeamMessenger(J4CircleBeam * fPtclGun);
    ~J4CircleBeamMessenger();
    
  public:
    void SetNewValue(G4UIcommand * command,G4String newValues);
    G4String GetCurrentValue(G4UIcommand * command);

  private:
    void IonCommand(G4String newValues);

  private:
    J4CircleBeam    *fCircleBeam;
    G4ParticleTable *fParticleTable;

  private: //commands
    G4UIdirectory              *fBeamDir;
    G4UIdirectory              *fDirectory;
    G4UIcmdWithoutParameter    *fListCmd;
    G4UIcmdWithABool           *fIsRandomPolarizedCmd;
    G4UIcmdWith3Vector         *fPolarizationCmd;
    G4UIcmdWithAString         *fParticleCmd;
    G4UIcmdWithAnInteger       *fBeamtypeCmd;
    G4UIcmdWith3Vector         *fDirectionCmd;
    G4UIcmdWith3VectorAndUnit  *fPositionCmd;
    G4UIcmdWithADoubleAndUnit  *fEnergyCmd;
    G4UIcmdWithADoubleAndUnit  *fTimeCmd;
    G4UIcmdWithADoubleAndUnit  *fRadiusCmd;
    G4UIcmdWith3VectorAndUnit  *fRotAnglesCmd;
    G4UIcmdWith3VectorAndUnit  *fTranslateCmd;

  private: // for ion shooting
};

#endif

