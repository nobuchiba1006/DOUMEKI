// $Id: J4ParticleBeamMessenger.cc,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
// GEANT4 tag $Name:  $
//

#include "J4ParticleBeamMessenger.hh"
#include "J4ParticleBeam.hh"
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
J4ParticleBeamMessenger::J4ParticleBeamMessenger(J4ParticleBeam * fPtclBeam)
  :fParticleBeam(fPtclBeam),fShootIon(false)
{

  //----------------------------------
  // common field
  //----------------------------------

  fParticleTable = G4ParticleTable::GetParticleTable();

  fListCmd = new G4UIcmdWithoutParameter("/jupiter/beam/List",this);
  fListCmd->SetGuidance("List available particles.");
  fListCmd->SetGuidance(" Invoke G4ParticleTable.");

  fNVerticesPerBeamCmd = new G4UIcmdWithAnInteger("/jupiter/beam/numberOfVertices",this);
  fNVerticesPerBeamCmd->SetGuidance("Set number of vertices to be generated per a beam.");
  fNVerticesPerBeamCmd->SetParameterName("N",true,true);
  fNVerticesPerBeamCmd->SetRange("N>0");
  
  fNParticlesPerVertexCmd = new G4UIcmdWithAnInteger("/jupiter/beam/numberOfParticles",this);
  fNParticlesPerVertexCmd->SetGuidance("Set number of particles per a vertex.");
  fNParticlesPerVertexCmd->SetParameterName("N",true,true);
  fNParticlesPerVertexCmd->SetRange("N>0");

  fIsRandomPolarizedCmd  = new G4UIcmdWithABool("/jupiter/beam/isRandomPolarized",this);
  fIsRandomPolarizedCmd->SetGuidance("Randomize polarization: (0:1)=(True:False)"); 
  fIsRandomPolarizedCmd->SetParameterName("IsRandomPolarized",true); 
  fIsRandomPolarizedCmd->SetDefaultValue(true);
  
  fPolarizationCmd = new G4UIcmdWith3Vector("/jupiter/beam/polarization",this);
  fPolarizationCmd->SetGuidance("Set polarization.");
  fPolarizationCmd->SetParameterName("Px","Py","Pz",true,true); 
  fPolarizationCmd->SetRange("Px>=-1.&&Px<=1.&&Py>=-1.&&Py<=1.&&Pz>=-1.&&Pz<=1.");

  fParticleCmd = new G4UIcmdWithAString("/jupiter/beam/particle",this);
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

  fBeamtypeCmd  = new G4UIcmdWithAnInteger("/jupiter/beam/beamtype",this);
  fBeamtypeCmd->SetGuidance("Set beamtype. 0:isotropic beam, 1:gaussian beam");
  fBeamtypeCmd->SetParameterName("BeamType",true,true);
  fBeamtypeCmd->SetRange("BeamType>=0");
  fBeamtypeCmd->SetDefaultValue(0);

  // for isotropic beam

  fConvergenceCmd  = new G4UIcmdWithABool("/jupiter/beam/convergence",this);
  fConvergenceCmd->SetGuidance("Injection direction. 0:divergence, 1:injected from surrounding sphere to beam position "); 
  fConvergenceCmd->SetParameterName("IsConvergenceMode",true); 
  fConvergenceCmd->SetDefaultValue(false);

  fCosThetaMinCmd = new G4UIcmdWithADouble("/jupiter/beam/mincostheta",this);
  fCosThetaMinCmd->SetGuidance("Set minimum costheta for isotropic beam");
  fCosThetaMinCmd->SetParameterName("CosThetaMin" ,true,true);

  fCosThetaMaxCmd = new G4UIcmdWithADouble("/jupiter/beam/maxcostheta",this);
  fCosThetaMaxCmd->SetGuidance("Set maximum costheta for isotropic beam");
  fCosThetaMaxCmd->SetParameterName("CosThetaMax" ,true,true);

  // for gaussian beam

  fDirectionCmd = new G4UIcmdWith3Vector("/jupiter/beam/direction",this);
  fDirectionCmd->SetGuidance("Set beam direction for gaussian beam");
  fDirectionCmd->SetGuidance("non-unit vector is allowded also." );
  fDirectionCmd->SetParameterName("vx","vy","vz",true,true); 
  fDirectionCmd->SetRange("vx != 0 || vy != 0 || vz != 0");

  fDirectionSigmaCmd = new G4UIcmdWithADouble("/jupiter/beam/directionsigma",this);
  fDirectionSigmaCmd->SetGuidance("Set direction sigma for gaussian beam");
  fDirectionSigmaCmd->SetParameterName("DirectionSigma" ,true,true);

  //----------------------------------
  // initial beam position profile 
  //----------------------------------

  fPositionProfileCmd  = new G4UIcmdWithABool("/jupiter/beam/positionprofile",this);
  fPositionProfileCmd->SetGuidance("Set beam-injection-point profile. 0:gaussian, 1:flat");
  fPositionProfileCmd->SetGuidance("0 : Gaussian profile");
  fPositionProfileCmd->SetGuidance("1 : Flat profile");
  fPositionProfileCmd->SetParameterName("IsFlatPositionProfile",true,true); 
  fPositionProfileCmd->SetDefaultValue(false);

  fPositionCmd = new G4UIcmdWith3VectorAndUnit("/jupiter/beam/position",this);
  fPositionCmd->SetGuidance("Set starting beam position for gaussian position profile.");
  fPositionCmd->SetParameterName("X","Y","Z",true,true);
  fPositionCmd->SetDefaultUnit("cm");
  fPositionCmd->SetUnitCategory("Length");
  fPositionCmd->SetUnitCandidates("microm mm cm m km");

  // for gaussian position profile

  fXPositionSigmaCmd = new G4UIcmdWithADoubleAndUnit("/jupiter/beam/positionsigmax",this);
  fXPositionSigmaCmd->SetGuidance("Set x-positionsigma for gaussian position profile");
  fXPositionSigmaCmd->SetParameterName("XPositionSigma" ,true,true);
  fXPositionSigmaCmd->SetDefaultUnit("cm");

  fYPositionSigmaCmd = new G4UIcmdWithADoubleAndUnit("/jupiter/beam/positionsigmay",this);
  fYPositionSigmaCmd->SetGuidance("Set y-positionsigma for gaussian position profile");
  fYPositionSigmaCmd->SetParameterName("YPositionSigma" ,true,true);
  fYPositionSigmaCmd->SetDefaultUnit("cm");

  fZPositionSigmaCmd = new G4UIcmdWithADoubleAndUnit("/jupiter/beam/positionsigmaz",this);
  fZPositionSigmaCmd->SetGuidance("Set z-positionsigma for gaussian position profile");
  fZPositionSigmaCmd->SetParameterName("ZPositionSigma" ,true,true);
  fZPositionSigmaCmd->SetDefaultUnit("cm");

  // for flat position profile

  fXMinCmd = new G4UIcmdWithADoubleAndUnit("/jupiter/beam/positionminx",this);
  fXMinCmd->SetGuidance("Set minimum x-position for flat position profile");
  fXMinCmd->SetParameterName("XMin" ,true,true);
  fXMinCmd->SetDefaultUnit("cm");

  fXMaxCmd = new G4UIcmdWithADoubleAndUnit("/jupiter/beam/positionmaxx",this);
  fXMaxCmd->SetGuidance("Set maximum x-position for flat position profile");
  fXMaxCmd->SetParameterName("XMax" ,true,true);
  fXMaxCmd->SetDefaultUnit("cm");

  fYMinCmd = new G4UIcmdWithADoubleAndUnit("/jupiter/beam/positionminy",this);
  fYMinCmd->SetGuidance("Set minimum y-position for flat position profile");
  fYMinCmd->SetParameterName("YMin" ,true,true);
  fYMinCmd->SetDefaultUnit("cm");

  fYMaxCmd = new G4UIcmdWithADoubleAndUnit("/jupiter/beam/positionmaxy",this);
  fYMaxCmd->SetGuidance("Set maximum y-position for flat position profile");
  fYMaxCmd->SetParameterName("YMax" ,true,true);
  fYMaxCmd->SetDefaultUnit("cm");

  fZMinCmd = new G4UIcmdWithADoubleAndUnit("/jupiter/beam/positionminz",this);
  fZMinCmd->SetGuidance("Set minimum z-position for flat position profile");
  fZMinCmd->SetParameterName("ZMin" ,true,true);
  fZMinCmd->SetDefaultUnit("cm");

  fZMaxCmd = new G4UIcmdWithADoubleAndUnit("/jupiter/beam/positionmaxz",this);
  fZMaxCmd->SetGuidance("Set maximum z-position for flat position profile");
  fZMaxCmd->SetParameterName("ZMax" ,true,true);
  fZMaxCmd->SetDefaultUnit("cm");

  //----------------------------------
  // beam energy profile
  //----------------------------------

  fEnergyProfileCmd  = new G4UIcmdWithABool("/jupiter/beam/energyprofile",this);
  fEnergyProfileCmd->SetGuidance("Set beam-injection-eneregy profile. 0:gaussian, 1:flat");
  fEnergyProfileCmd->SetGuidance("0 : Gaussian profile");
  fEnergyProfileCmd->SetGuidance("1 : Flat profile");
  fEnergyProfileCmd->SetParameterName("IsFlatEnergyProfile",true,true); 
  fEnergyProfileCmd->SetDefaultValue(false);

  fEnergyCmd = new G4UIcmdWithADoubleAndUnit("/jupiter/beam/energy",this);
  fEnergyCmd->SetGuidance("Set total energy for gaussian energy profile");
  fEnergyCmd->SetParameterName("Energy",true,true);
  fEnergyCmd->SetDefaultUnit("GeV");
  fEnergyCmd->SetUnitCategory("Energy");
  fEnergyCmd->SetUnitCandidates("eV keV MeV GeV TeV");

  // for gaussian profile

  fEnergySigmaCmd = new G4UIcmdWithADoubleAndUnit("/jupiter/beam/energysigma",this);
  fEnergySigmaCmd->SetGuidance("Set energy sigma for gaussian energy profile");
  fEnergySigmaCmd->SetParameterName("EnergySigma" ,true,true);
  fEnergySigmaCmd->SetDefaultUnit("GeV");

  // for gaussian profile

  fEnergyMinCmd = new G4UIcmdWithADoubleAndUnit("/jupiter/beam/energymin",this);
  fEnergyMinCmd->SetGuidance("Set minimum mementum for flat energy profile.");
  fEnergyMinCmd->SetParameterName("EnergyMin" ,true,true);
  fEnergyMinCmd->SetDefaultUnit("GeV");

  fEnergyMaxCmd = new G4UIcmdWithADoubleAndUnit("/jupiter/beam/energymax",this);
  fEnergyMaxCmd->SetGuidance("Set maximum mementum for flat energy profile.");
  fEnergyMaxCmd->SetParameterName("EnergyMax" ,true,true);
  fEnergyMaxCmd->SetDefaultUnit("GeV");

  // others

  fTimeCmd = new G4UIcmdWithADoubleAndUnit("/jupiter/beam/time",this);
  fTimeCmd->SetGuidance("Set initial time of the particle.");
  fTimeCmd->SetParameterName("t0",true,true);
  fTimeCmd->SetDefaultUnit("ns");
  fTimeCmd->SetUnitCategory("Time");
  fTimeCmd->SetUnitCandidates("ns ms s");
  
  fIonCmd = new G4UIcommand("/jupiter/beam/ion",this);
  fIonCmd->SetGuidance("Set properties of ion to be generated.");
  fIonCmd->SetGuidance("[usage] /jupiter/beam/ion Z A Q");
  fIonCmd->SetGuidance("        Z:(int) AtomicNumber");
  fIonCmd->SetGuidance("        A:(int) AtomicMass");
  fIonCmd->SetGuidance("        Q:(int) Charge of Ion (in unit of e)");
  fIonCmd->SetGuidance("        E:(double) Excitation energy (in keV)");
  
  G4UIparameter* param;
  param = new G4UIparameter("Z",'i',false);
  param->SetDefaultValue("1");
  fIonCmd->SetParameter(param);
  param = new G4UIparameter("A",'i',false);
  param->SetDefaultValue("1");
  fIonCmd->SetParameter(param);
  param = new G4UIparameter("Q",'i',true);
  param->SetDefaultValue("0");
  fIonCmd->SetParameter(param);
  param = new G4UIparameter("E",'d',true);
  param->SetDefaultValue("0.0");
  fIonCmd->SetParameter(param);
  
  // set initial value to J4ParticleBeam
  fParticleBeam->SetParticleDefinition( G4Geantino::Geantino() );
  fParticleBeam->SetMeanBeamDirection( G4ThreeVector(1.0,0.0,0.0) );
  fParticleBeam->SetMeanEnergy( 1.0*GeV );
  fParticleBeam->SetParticlePosition(G4ThreeVector(0.0*cm, 0.0*cm, 0.0*cm));
  fParticleBeam->SetParticleTime( 0.0*ns );
}

// ====================================================================
//* constructor -------------------------------------------------------
J4ParticleBeamMessenger::~J4ParticleBeamMessenger()
{
  delete fListCmd;
  delete fNVerticesPerBeamCmd;
  delete fNParticlesPerVertexCmd;
  delete fIsRandomPolarizedCmd;
  delete fPolarizationCmd;
  delete fParticleCmd;
  delete fBeamtypeCmd;
  delete fConvergenceCmd;
  delete fDirectionCmd;
  delete fDirectionSigmaCmd;
  delete fPositionProfileCmd;
  delete fPositionCmd;
  delete fXPositionSigmaCmd;
  delete fYPositionSigmaCmd;
  delete fZPositionSigmaCmd;
  delete fXMinCmd;
  delete fXMaxCmd;
  delete fYMinCmd;
  delete fYMaxCmd;
  delete fZMinCmd;
  delete fZMaxCmd;
  delete fEnergyProfileCmd;
  delete fEnergyCmd;
  delete fEnergySigmaCmd;
  delete fEnergyMinCmd;
  delete fEnergyMaxCmd;
  delete fTimeCmd;
  delete fIonCmd;

}

// ====================================================================
//* SetNewValue -------------------------------------------------------
void J4ParticleBeamMessenger::SetNewValue(G4UIcommand * command,G4String newValues)
{
  if ( command == fListCmd )
  { 
     fParticleTable->DumpTable();
  } else if ( command == fParticleCmd ) {
    if (newValues =="ion") {
      fShootIon = true;
    } else {
      fShootIon = false;
      G4ParticleDefinition* pd = fParticleTable->FindParticle(newValues);
      if (pd != 0)
      { fParticleBeam->SetParticleDefinition( pd ); }
    }
  } else if ( command == fNVerticesPerBeamCmd ) { 
     fParticleBeam->SetNVerticesPerBeam(fNVerticesPerBeamCmd->GetNewIntValue(newValues)); 

  } else if ( command == fNParticlesPerVertexCmd ) { 
     fParticleBeam->SetNParticlesPerVertex(fNParticlesPerVertexCmd->GetNewIntValue(newValues)); 

  } else if ( command == fIsRandomPolarizedCmd ) { 
     fParticleBeam->RandomizePolarization(fIsRandomPolarizedCmd->GetNewBoolValue(newValues)); 

  } else if ( command == fPolarizationCmd ) { 
     fParticleBeam->SetParticlePolarization(fPolarizationCmd->GetNew3VectorValue(newValues)); 

  } else if ( command == fBeamtypeCmd ) {
     fParticleBeam->SetBeamType((J4ParticleBeam::EBeamType)fBeamtypeCmd->
                                 GetNewIntValue(newValues)); 
  } else if ( command == fConvergenceCmd ) {
     fParticleBeam->SetConvergenceMode(fConvergenceCmd->GetNewBoolValue(newValues)); 

  } else if ( command == fCosThetaMinCmd ) { 
     fParticleBeam->SetCosThetaMin(fCosThetaMinCmd->GetNewDoubleValue(newValues)); 

  } else if ( command == fCosThetaMaxCmd ) { 
     fParticleBeam->SetCosThetaMax(fCosThetaMaxCmd->GetNewDoubleValue(newValues)); 

  } else if ( command == fDirectionCmd ) {
     fParticleBeam->SetMeanBeamDirection(fDirectionCmd->GetNew3VectorValue(newValues)); 

  } else if ( command == fDirectionSigmaCmd ) { 
     fParticleBeam->SetBeamDirectionSigma(fDirectionSigmaCmd->GetNewDoubleValue(newValues)); 

  } else if ( command == fPositionProfileCmd ) {
     fParticleBeam->SetBeamPositionProfile(fPositionProfileCmd->GetNewBoolValue(newValues)); 

  } else if ( command == fPositionCmd ) { 
     fParticleBeam->SetParticlePosition(fPositionCmd->GetNew3VectorValue(newValues)); 

  } else if ( command == fXPositionSigmaCmd ) { 
     fParticleBeam->SetBeamPositionSigmaX(fXPositionSigmaCmd->GetNewDoubleValue(newValues)); 

  } else if ( command == fYPositionSigmaCmd ) { 
     fParticleBeam->SetBeamPositionSigmaY(fYPositionSigmaCmd->GetNewDoubleValue(newValues)); 

  } else if ( command == fZPositionSigmaCmd ) { 
     fParticleBeam->SetBeamPositionSigmaZ(fZPositionSigmaCmd->GetNewDoubleValue(newValues)); 

  } else if ( command == fXMinCmd ) { 
     fParticleBeam->SetBeamPositionRangeXMin(fXMinCmd->GetNewDoubleValue(newValues)); 

  } else if ( command == fXMaxCmd ) { 
     fParticleBeam->SetBeamPositionRangeXMax(fXMaxCmd->GetNewDoubleValue(newValues)); 

  } else if ( command == fYMinCmd ) { 
     fParticleBeam->SetBeamPositionRangeYMin(fYMinCmd->GetNewDoubleValue(newValues)); 

  } else if ( command == fYMaxCmd ) { 
     fParticleBeam->SetBeamPositionRangeYMax(fYMaxCmd->GetNewDoubleValue(newValues)); 

  } else if ( command == fZMinCmd ) { 
     fParticleBeam->SetBeamPositionRangeZMin(fZMinCmd->GetNewDoubleValue(newValues)); 

  } else if ( command == fZMaxCmd ) { 
     fParticleBeam->SetBeamPositionRangeZMax(fZMaxCmd->GetNewDoubleValue(newValues)); 

  } else if ( command == fEnergyProfileCmd ) { 
     fParticleBeam->SetFlatEnergyProfile(fEnergyProfileCmd->GetNewBoolValue(newValues)); 

  } else if ( command == fEnergyCmd ) { 
     fParticleBeam->SetMeanEnergy(fEnergyCmd->GetNewDoubleValue(newValues)); 

  } else if ( command == fEnergySigmaCmd ) { 
     fParticleBeam->SetMeanEnergySigma(fEnergySigmaCmd->GetNewDoubleValue(newValues)); 

  } else if ( command == fEnergyMinCmd ) { 
     fParticleBeam->SetEnergyRangeMin(fEnergyMinCmd->GetNewDoubleValue(newValues)); 

  } else if ( command == fEnergyMaxCmd ) { 
     fParticleBeam->SetEnergyRangeMax(fEnergyMaxCmd->GetNewDoubleValue(newValues)); 

  } else if ( command == fTimeCmd ) { 
     fParticleBeam->SetParticleTime(fTimeCmd->GetNewDoubleValue(newValues)); 

  } else if ( command == fIonCmd ) { 
     IonCommand(newValues); 

  }
}


// ====================================================================
//* GetCurrentValue ---------------------------------------------------
G4String J4ParticleBeamMessenger::GetCurrentValue(G4UIcommand * command)
{
  G4String cv;

  if ( command == fNVerticesPerBeamCmd ) { 
     cv = fNVerticesPerBeamCmd->ConvertToString(fParticleBeam->GetNVerticesPerBeam()); 

  } else if ( command == fNParticlesPerVertexCmd ) { 
     cv = fNParticlesPerVertexCmd->ConvertToString(fParticleBeam->GetNParticlesPerVertex()); 

  } else if ( command == fIsRandomPolarizedCmd ) {
     cv = fIsRandomPolarizedCmd->ConvertToString(fParticleBeam->IsRandomPolarization()); 

  } else if ( command == fPolarizationCmd ) {
     cv = fPolarizationCmd->ConvertToString(fParticleBeam->GetParticlePolarization()); 

  } else if ( command == fParticleCmd ) { 
     cv = fParticleBeam->GetParticleDefinition()->GetParticleName(); 

  } else if ( command == fBeamtypeCmd ) { 
     cv = fBeamtypeCmd->ConvertToString(fParticleBeam->GetBeamType());

  } else if ( command == fConvergenceCmd ) { 
     cv = fConvergenceCmd->ConvertToString(fParticleBeam->IsConvergenceMode()); 

  } else if ( command == fCosThetaMinCmd ) { 
     cv = fCosThetaMinCmd->ConvertToString(fParticleBeam->GetCosThetaMin()); 

  } else if ( command == fCosThetaMaxCmd ) { 
     cv = fCosThetaMaxCmd->ConvertToString(fParticleBeam->GetCosThetaMax()); 

  } else if ( command == fDirectionCmd ) { 
     cv = fDirectionCmd->ConvertToString(fParticleBeam->GetMeanBeamDirection()); 

  } else if ( command == fDirectionSigmaCmd ) { 
     cv = fDirectionSigmaCmd->ConvertToString(fParticleBeam->GetBeamDirectionSigma()); 

  } else if ( command == fPositionProfileCmd ) { 
     cv = fPositionProfileCmd->ConvertToString(fParticleBeam->IsFlatPositionProfile()); 

  } else if ( command == fPositionCmd ) { 
     cv = fPositionCmd->ConvertToString(fParticleBeam->GetParticlePosition(),"cm"); 

  } else if ( command == fXPositionSigmaCmd ) {
     cv = fXPositionSigmaCmd->ConvertToString(fParticleBeam->GetBeamPositionSigmaX(),"cm"); 

  } else if ( command == fYPositionSigmaCmd ) { 
     cv = fYPositionSigmaCmd->ConvertToString(fParticleBeam->GetBeamPositionSigmaY(),"cm"); 

  } else if ( command == fZPositionSigmaCmd ) { 
     cv = fZPositionSigmaCmd->ConvertToString(fParticleBeam->GetBeamPositionSigmaZ(),"cm"); 

  } else if ( command == fXMinCmd ) { 
    cv = fXMinCmd->ConvertToString(fParticleBeam->GetBeamPositionRangeXMin(),"cm"); 

  } else if ( command == fXMaxCmd ) { 
    cv = fXMaxCmd->ConvertToString(fParticleBeam->GetBeamPositionRangeXMax(),"cm"); 

  } else if ( command == fYMinCmd ) { 
    cv = fYMinCmd->ConvertToString(fParticleBeam->GetBeamPositionRangeYMin(),"cm"); 

  } else if ( command == fYMaxCmd ) { 
    cv = fYMaxCmd->ConvertToString(fParticleBeam->GetBeamPositionRangeYMax(),"cm"); 

  } else if ( command == fZMinCmd ) { 
    cv = fZMinCmd->ConvertToString(fParticleBeam->GetBeamPositionRangeZMin(),"cm"); 

  } else if ( command == fZMaxCmd ) { 
    cv = fZMaxCmd->ConvertToString(fParticleBeam->GetBeamPositionRangeZMax(),"cm"); 

  } else if ( command == fEnergyProfileCmd ) { 
     cv = fEnergyProfileCmd->ConvertToString(fParticleBeam->IsFlatEnergyProfile()); 

  } else if ( command == fEnergyCmd ) { 
     cv = fEnergyCmd->ConvertToString(fParticleBeam->GetMeanEnergy(),"GeV"); 

  } else if ( command == fEnergySigmaCmd ) { 
     cv = fEnergySigmaCmd->ConvertToString(fParticleBeam->GetMeanEnergySigma(),"GeV"); 

  } else if ( command == fEnergyMinCmd ) { 
     cv = fEnergyMinCmd->ConvertToString(fParticleBeam->GetEnergyRangeMin(),"GeV"); 

  } else if ( command == fEnergyMaxCmd ) { 
     cv = fEnergyMaxCmd->ConvertToString(fParticleBeam->GetEnergyRangeMax(),"GeV"); 

  } else if ( command == fTimeCmd ) { 
     cv = fTimeCmd->ConvertToString(fParticleBeam->GetParticleTime(),"ns"); 

  } else if ( command == fIonCmd ) { 
    if (fShootIon) {
      cv = ItoS(fAtomicNumber) + " " + ItoS(fAtomicMass) + " ";
      cv += ItoS(fIonCharge);
    } else {
      cv = "";
    }  
  }    

  return cv;
}

void J4ParticleBeamMessenger::IonCommand(G4String newValues)
{
  if (fShootIon) {
    G4Tokenizer next( newValues );
    // check argument
    fAtomicNumber = StoI(next());
    fAtomicMass = StoI(next());
    G4String sQ = next();
    if (sQ.isNull()) {
      fIonCharge = fAtomicNumber;
    } else {
	fIonCharge = StoI(sQ);
      sQ = next();
      if (sQ.isNull()) {
        fIonExciteEnergy = 0.0;
      } else {
        fIonExciteEnergy = StoD(sQ) * keV;
      }
    }

    G4IonTable *iontable = G4IonTable::GetIonTable();
    G4ParticleDefinition* ion;
    ion = iontable->GetIon( fAtomicNumber, fAtomicMass, fIonExciteEnergy);
    if (ion==0) {
    std::cout << "Ion with Z=" << fAtomicNumber;
    std::cout << " A=" << fAtomicMass << "is not be defined" << std::endl;    
    } else {
      fParticleBeam->SetParticleDefinition(ion);
      fParticleBeam->SetParticleCharge(fIonCharge*eplus);
    }
  } else {
    std::cout << "Set /jupiter/beam/particle to ion before using /jupiter/beam/ion command";
    std::cout << std::endl; 
  }
}

