//
// ********************************************************************
// * DISCLAIMER                                                       *
// *                                                                  *
// * The following disclaimer summarizes all the specific disclaimers *
// * of contributors to this software. The specific disclaimers,which *
// * govern, are listed with their locations in:                      *
// *   http://cern.ch/geant4/license                                  *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.                                                             *
// *                                                                  *
// * This  code  implementation is the  intellectual property  of the *
// * GEANT4 collaboration.                                            *
// * By copying,  distributing  or modifying the Program (or any work *
// * based  on  the Program)  you indicate  your  acceptance of  this *
// * statement, and all its terms.                                    *
// ********************************************************************
//
//
// $Id: J4PhysicsListMessenger.cc,v 1.2 2007/03/13 17:29:14 hoshina Exp $
// GEANT4 tag $Name:  $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "J4PhysicsListMessenger.hh"

#include "J4PhysicsList.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAnInteger.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

J4PhysicsListMessenger::J4PhysicsListMessenger(J4PhysicsList* pPhys)
:pPhysicsList(pPhys)
{
  jupiterDir = new G4UIdirectory("/jupiter/");
  jupiterDir->SetGuidance("UI commands of this example");
  
  physDir = new G4UIdirectory("/jupiter/phys/");
  physDir->SetGuidance("PhysicsList control");
 
  verboseCmd = new G4UIcmdWithAnInteger("/jupiter/phys/verbose",this);  
  verboseCmd->SetGuidance("set verbose for physics processes");
  verboseCmd->SetParameterName("verbose",true);
  verboseCmd->SetDefaultValue(1);
  verboseCmd->SetRange("verbose>=0");
  verboseCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  cerenkovCmd = new G4UIcmdWithAnInteger("/jupiter/phys/cerenkovMaxPhotons",this);  
  cerenkovCmd->SetGuidance("set max nb of photons per step");
  cerenkovCmd->SetParameterName("MaxNumber",false);
  cerenkovCmd->SetRange("MaxNumber>=0");
  cerenkovCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

J4PhysicsListMessenger::~J4PhysicsListMessenger()
{
  delete verboseCmd;
  delete cerenkovCmd;
  delete physDir;
  delete jupiterDir;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void J4PhysicsListMessenger::SetNewValue(G4UIcommand* command,
                                          G4String newValue)
{       
  if( command == verboseCmd )
   { pPhysicsList->SetVerbose(verboseCmd->GetNewIntValue(newValue));}
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
