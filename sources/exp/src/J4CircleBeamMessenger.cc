// $Id: J4CircleBeamMessenger.cc,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
// GEANT4 tag $Name:  $
//

#include "J4CircleBeamMessenger.hh"
#include "J4CircleBeam.hh"
#include "G4Geantino.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWith3Vector.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4ios.hh"
#include "G4Tokenizer.hh"
#include "G4SystemOfUnits.hh"

#include "./iomanip"               

// ====================================================================
//* constructor -------------------------------------------------------
J4CircleBeamMessenger::J4CircleBeamMessenger(J4CircleBeam * beam)
                      :fCircleBeam(beam)
{

  //----------------------------------
  // common field
  //----------------------------------

  fParticleTable = G4ParticleTable::GetParticleTable();

  fBeamDir = new G4UIdirectory("/jupiter/beam/");
  fDirectory = new G4UIdirectory("/jupiter/beam/circle/");
  fDirectory->SetGuidance("circle Beam control commands.");

  fListCmd = new G4UIcmdWithoutParameter("/jupiter/beam/circle/List",this);
  fListCmd->SetGuidance("List available particles.");
  fListCmd->SetGuidance(" Invoke G4ParticleTable.");

  fIsRandomPolarizedCmd  = new G4UIcmdWithABool("/jupiter/beam/circle/isRandomPolarized",this);
  fIsRandomPolarizedCmd->SetGuidance("Randomize polarization: (0:1)=(True:False)"); 
  fIsRandomPolarizedCmd->SetParameterName("IsRandomPolarized",true); 
  fIsRandomPolarizedCmd->SetDefaultValue(true);
  
  fPolarizationCmd = new G4UIcmdWith3Vector("/jupiter/beam/circle/polarization",this);
  fPolarizationCmd->SetGuidance("Set polarization.");
  fPolarizationCmd->SetParameterName("Px","Py","Pz",true,true); 
  fPolarizationCmd->SetRange("Px>=-1.&&Px<=1.&&Py>=-1.&&Py<=1.&&Pz>=-1.&&Pz<=1.");

  fParticleCmd = new G4UIcmdWithAString("/jupiter/beam/circle/particle",this);
  fParticleCmd->SetGuidance("Set particle to be generated.");
  fParticleCmd->SetGuidance(" (geantino is default)");
  fParticleCmd->SetGuidance(" (ion can be specified for shooting ions)");
  fParticleCmd->SetParameterName("particleName",true);
  fParticleCmd->SetDefaultValue("geantino");
  G4String candidateList; 
  G4int nPtcl = fParticleTable->entries();
  for(G4int i=0;i<nPtcl;i++)
  {
    candidateList += fParticleTable->GetParticleName(i);
    candidateList += " ";
  }
  candidateList += "ion ";
  fParticleCmd->SetCandidates(candidateList);

  //----------------------------------
  // beam type
  //----------------------------------

  fDirectionCmd = new G4UIcmdWith3Vector("/jupiter/beam/circle/direction",this);
  fDirectionCmd->SetGuidance("Set beam direction for gaussian beam");
  fDirectionCmd->SetGuidance("non-unit vector is allowded also." );
  fDirectionCmd->SetParameterName("vx","vy","vz",true,true); 
  fDirectionCmd->SetRange("vx != 0 || vy != 0 || vz != 0");

  //----------------------------------
  // initial beam position profile 
  //----------------------------------

  fPositionCmd = new G4UIcmdWith3VectorAndUnit("/jupiter/beam/circle/position",this);
  fPositionCmd->SetGuidance("Set starting beam position for gaussian position profile.");
  fPositionCmd->SetParameterName("X","Y","Z",true,true);
  fPositionCmd->SetDefaultUnit("cm");
  fPositionCmd->SetUnitCategory("Length");
  fPositionCmd->SetUnitCandidates("microm mm cm m km");

  //----------------------------------
  // beam energy profile
  //----------------------------------

  fEnergyCmd = new G4UIcmdWithADoubleAndUnit("/jupiter/beam/circle/energy",this);
  fEnergyCmd->SetGuidance("Set total energy for gaussian energy profile");
  fEnergyCmd->SetParameterName("Energy",true,true);
  fEnergyCmd->SetDefaultUnit("GeV");
  fEnergyCmd->SetUnitCategory("Energy");
  fEnergyCmd->SetUnitCandidates("eV keV MeV GeV TeV");

  // others

  fTimeCmd = new G4UIcmdWithADoubleAndUnit("/jupiter/beam/circle/time",this);
  fTimeCmd->SetGuidance("Set initial time of the particle.");
  fTimeCmd->SetParameterName("t0",true,true);
  fTimeCmd->SetDefaultUnit("ns");
  fTimeCmd->SetUnitCategory("Time");
  fTimeCmd->SetUnitCandidates("ns ms s");

  fRadiusCmd = new G4UIcmdWithADoubleAndUnit("/jupiter/beam/circle/radius",this);
  fRadiusCmd->SetGuidance("Set radius of beam circle");
  fRadiusCmd->SetParameterName("R",true,true);
  fRadiusCmd->SetDefaultUnit("cm");
  fRadiusCmd->SetUnitCategory("Length");
  fRadiusCmd->SetUnitCandidates("mm cm m");

  fRotAnglesCmd = new G4UIcmdWith3VectorAndUnit("/jupiter/beam/circle/rotations",this);
  fRotAnglesCmd->SetGuidance("Set rotation angles of beam plane around axes x, y, z");
  fRotAnglesCmd->SetParameterName("theta","psi","phi",true,true); 
  fRotAnglesCmd->SetDefaultUnit("degree");
  fRotAnglesCmd->SetUnitCategory("Angle");
  fRotAnglesCmd->SetUnitCandidates("degree rad");

  fTranslateCmd = new G4UIcmdWith3VectorAndUnit("/jupiter/beam/circle/translation",this);
  fTranslateCmd->SetGuidance("Set translation of origin of circle");
  fTranslateCmd->SetParameterName("tx","ty","tz",true,true); 
  fTranslateCmd->SetDefaultUnit("cm");
  fTranslateCmd->SetUnitCategory("Length");
  fTranslateCmd->SetUnitCandidates("microm mm cm m km");

  fPositionCmd = new G4UIcmdWith3VectorAndUnit("/jupiter/beam/circle/position",this);
  fPositionCmd->SetGuidance("Set starting beam position for gaussian position profile.");
  fPositionCmd->SetParameterName("X","Y","Z",true,true);
  fPositionCmd->SetUnitCategory("Length");
  
  // set initial value to J4CircleBeam
  fCircleBeam->SetParticleDefinition( G4Geantino::Geantino() );
  fCircleBeam->SetMeanBeamDirection( G4ThreeVector(1.0,0.0,0.0) );
  fCircleBeam->SetMeanEnergy( 1.0*GeV );
  fCircleBeam->SetParticlePosition(G4ThreeVector(0.0*cm, 0.0*cm, 0.0*cm));
  fCircleBeam->SetParticleTime( 0.0*ns );
  fCircleBeam->SetRadius( 16.51 *cm );
  fCircleBeam->RotateAroundXYZ(0, 0, 0);
  fCircleBeam->SetTranslate( G4ThreeVector(0, 0, 17 *cm) );
}

// ====================================================================
//* destructor -------------------------------------------------------
J4CircleBeamMessenger::~J4CircleBeamMessenger()
{
  delete fListCmd;
  delete fIsRandomPolarizedCmd;
  delete fPolarizationCmd;
  delete fParticleCmd;
  delete fDirectionCmd;
  delete fPositionCmd;
  delete fEnergyCmd;
  delete fTimeCmd;
  delete fRadiusCmd;
  delete fRotAnglesCmd;
  delete fTranslateCmd;
  delete fDirectory;

}

// ====================================================================
//* SetNewValue -------------------------------------------------------
void J4CircleBeamMessenger::SetNewValue(G4UIcommand * command,G4String newValues)
{
  if ( command == fListCmd )
  { 
     fParticleTable->DumpTable();
  } else if ( command == fParticleCmd ) {
      G4ParticleDefinition* pd = fParticleTable->FindParticle(newValues);
      if (pd != 0)
      { fCircleBeam->SetParticleDefinition( pd ); }
  } else if ( command == fIsRandomPolarizedCmd ) { 
     fCircleBeam->RandomizePolarization(fIsRandomPolarizedCmd->GetNewBoolValue(newValues)); 

  } else if ( command == fPolarizationCmd ) { 
     fCircleBeam->SetParticlePolarization(fPolarizationCmd->GetNew3VectorValue(newValues)); 

  } else if ( command == fDirectionCmd ) {
     fCircleBeam->SetMeanBeamDirection(fDirectionCmd->GetNew3VectorValue(newValues)); 

  } else if ( command == fPositionCmd ) { 
     fCircleBeam->SetParticlePosition(fPositionCmd->GetNew3VectorValue(newValues)); 

  } else if ( command == fEnergyCmd ) { 
     fCircleBeam->SetMeanEnergy(fEnergyCmd->GetNewDoubleValue(newValues)); 

  } else if ( command == fTimeCmd ) { 
     fCircleBeam->SetParticleTime(fTimeCmd->GetNewDoubleValue(newValues)); 

  } else if ( command == fRadiusCmd ) { 
     fCircleBeam->SetRadius(fTimeCmd->GetNewDoubleValue(newValues)); 

  } else if ( command == fRotAnglesCmd ) {
     G4ThreeVector ang = fRotAnglesCmd->GetNew3VectorValue(newValues);
     fCircleBeam->RotateAroundXYZ(ang.x(), ang.y(), ang.z()); 

  } else if ( command == fTranslateCmd ) {
     fCircleBeam->SetTranslate(fTranslateCmd->GetNew3VectorValue(newValues)); 

  }
}


// ====================================================================
//* GetCurrentValue ---------------------------------------------------
G4String J4CircleBeamMessenger::GetCurrentValue(G4UIcommand * command)
{
  G4String cv;

  if ( command == fIsRandomPolarizedCmd ) {
     cv = fIsRandomPolarizedCmd->ConvertToString(fCircleBeam->IsRandomPolarization()); 

  } else if ( command == fPolarizationCmd ) {
     cv = fPolarizationCmd->ConvertToString(fCircleBeam->GetParticlePolarization()); 

  } else if ( command == fParticleCmd ) { 
     cv = fCircleBeam->GetParticleDefinition()->GetParticleName(); 

  } else if ( command == fDirectionCmd ) { 
     cv = fDirectionCmd->ConvertToString(fCircleBeam->GetMeanBeamDirection()); 

  } else if ( command == fPositionCmd ) { 
     cv = fPositionCmd->ConvertToString(fCircleBeam->GetParticlePosition(),"cm"); 

  } else if ( command == fEnergyCmd ) { 
     cv = fEnergyCmd->ConvertToString(fCircleBeam->GetMeanEnergy(),"GeV"); 

  } else if ( command == fTimeCmd ) { 
     cv = fTimeCmd->ConvertToString(fCircleBeam->GetParticleTime(),"ns"); 

  } else if ( command == fRadiusCmd ) { 
     cv = fRadiusCmd->ConvertToString(fCircleBeam->GetRadius(),"cm"); 

  } else if ( command == fRotAnglesCmd ) { 
     cv = fRotAnglesCmd->ConvertToString(fCircleBeam->GetRotAngles()); 

  } else if ( command == fTranslateCmd ) { 
     cv = fTranslateCmd->ConvertToString(fCircleBeam->GetTranslate()); 

  }    

  return cv;
}


