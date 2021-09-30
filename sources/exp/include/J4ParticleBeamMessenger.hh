// $Id: J4ParticleBeamMessenger.hh,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
// GEANT4 tag $Name:  $
//
// 

#ifndef J4ParticleBeamMessenger_h
#define J4ParticleBeamMessenger_h 1

class J4ParticleBeam;
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
// J4ParticleBeam.
//

class J4ParticleBeamMessenger: public G4UImessenger
{
  public:
    J4ParticleBeamMessenger(J4ParticleBeam * fPtclGun);
    ~J4ParticleBeamMessenger();
    
  public:
    void SetNewValue(G4UIcommand * command,G4String newValues);
    G4String GetCurrentValue(G4UIcommand * command);

  private:
    void IonCommand(G4String newValues);

  private:
    J4ParticleBeam * fParticleBeam;
    G4ParticleTable * fParticleTable;

  private: //commands
    G4UIcmdWithoutParameter    *fListCmd;
    G4UIcmdWithAnInteger       *fNVerticesPerBeamCmd;
    G4UIcmdWithAnInteger       *fNParticlesPerVertexCmd;
    G4UIcmdWithABool           *fIsRandomPolarizedCmd;
    G4UIcmdWith3Vector         *fPolarizationCmd;
    G4UIcmdWithAString         *fParticleCmd;
    G4UIcmdWithAnInteger       *fBeamtypeCmd;
    G4UIcmdWithABool           *fConvergenceCmd;
    G4UIcmdWithADouble         *fCosThetaMinCmd;
    G4UIcmdWithADouble         *fCosThetaMaxCmd;
    G4UIcmdWith3Vector         *fDirectionCmd;
    G4UIcmdWithADouble         *fDirectionSigmaCmd;
    G4UIcmdWithABool           *fPositionProfileCmd;
    G4UIcmdWith3VectorAndUnit  *fPositionCmd;
    G4UIcmdWithADoubleAndUnit  *fXPositionSigmaCmd;
    G4UIcmdWithADoubleAndUnit  *fYPositionSigmaCmd;
    G4UIcmdWithADoubleAndUnit  *fZPositionSigmaCmd;
    G4UIcmdWithADoubleAndUnit  *fXMinCmd;
    G4UIcmdWithADoubleAndUnit  *fXMaxCmd;
    G4UIcmdWithADoubleAndUnit  *fYMinCmd;
    G4UIcmdWithADoubleAndUnit  *fYMaxCmd;
    G4UIcmdWithADoubleAndUnit  *fZMinCmd;
    G4UIcmdWithADoubleAndUnit  *fZMaxCmd;
    G4UIcmdWithABool           *fEnergyProfileCmd;
    G4UIcmdWithADoubleAndUnit  *fEnergyCmd;
    G4UIcmdWithADoubleAndUnit  *fEnergySigmaCmd;
    G4UIcmdWithADoubleAndUnit  *fEnergyMinCmd;
    G4UIcmdWithADoubleAndUnit  *fEnergyMaxCmd;
    G4UIcmdWithADoubleAndUnit  *fTimeCmd;
    G4UIcommand                *fIonCmd;

  private: // for ion shooting
    G4bool   fShootIon; 
    G4int    fAtomicNumber;
    G4int    fAtomicMass;
    G4int    fIonCharge;
    G4double fIonExciteEnergy;
};

#endif

