// $Id: J4PrimaryGeneratorMessenger.cc,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $

#include "J4PrimaryGeneratorMessenger.hh"
#include "J4PrimaryGeneratorAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4ios.hh"

J4PrimaryGeneratorMessenger::J4PrimaryGeneratorMessenger(J4PrimaryGeneratorAction *mpga)
:fAction(mpga), fDirectory(0), fGenCmd(0)
{
   fDirectory = new G4UIdirectory("/jupiter/");
   fDirectory->SetGuidance("Jupiter control commands.");

   fGenCmd = new G4UIcmdWithAString("/jupiter/generator",this);
   fGenCmd->SetGuidance("Select primary generator.");
   fGenCmd->SetGuidance(" Available generators : HEPEvt, CAINEvt, ParticleGun, ParticleBeam, CircleBeam");
   fGenCmd->SetParameterName("generator",true);
   fGenCmd->SetDefaultValue("ParticleGun");
   fGenCmd->SetCandidates("HEPEvt CAINEvt ParticleGun ParticleBeam CircleBeam");
}

J4PrimaryGeneratorMessenger::~J4PrimaryGeneratorMessenger()
{
   delete fGenCmd;
   delete fDirectory;
}

void J4PrimaryGeneratorMessenger::SetNewValue(G4UIcommand *command, G4String newValue)
{
   if( command==fGenCmd ) {
      if (newValue == "HEPEvt") {
         fAction->SetPrimaryGenerator(J4PrimaryGeneratorAction::kHEPEvt);
      } else if (newValue == "CAINEvt") {
         fAction->SetPrimaryGenerator(J4PrimaryGeneratorAction::kCAINEvt);
      } else if (newValue == "ParticleGun") {
         fAction->SetPrimaryGenerator(J4PrimaryGeneratorAction::kParticleGun);
      } else if (newValue == "CircleBeam") {
         fAction->SetPrimaryGenerator(J4PrimaryGeneratorAction::kCircleBeam);
      } else {
         fAction->SetPrimaryGenerator(J4PrimaryGeneratorAction::kParticleBeam);
      }
   }
}

G4String J4PrimaryGeneratorMessenger::GetCurrentValue(G4UIcommand * command)
{
   G4String cv;
  
   if( command==fGenCmd )
   {
      J4PrimaryGeneratorAction::EPrimaryGeneratorType type = fAction->GetPrimaryGeneratorType();
      switch (type) {
         case J4PrimaryGeneratorAction::kHEPEvt:
            cv = "HEPEvt";
            break;
         case J4PrimaryGeneratorAction::kCAINEvt:
            cv = "CAINEvt";
            break;
         case J4PrimaryGeneratorAction::kParticleGun:
            cv = "ParticleGun";
            break;
         case J4PrimaryGeneratorAction::kParticleBeam:
            cv = "ParticleBeam";
            break;
         case J4PrimaryGeneratorAction::kCircleBeam:
            cv = "CircleBeam";
            break;
         default:
            std::cerr << " J4PrimaryGeneratorMessenger::GetCurrrentValue:Generator is not "
                 << "prepared. break." << std::endl;  
            break;
     }
  }
  
  return cv;
}

