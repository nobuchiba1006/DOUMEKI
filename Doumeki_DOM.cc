// $Id: Dominant.cc,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
// ====================================================================
//    Dominant.cc
//   
//    DOM Raytrace Monte-Carlo program
//
//    NOTE:
//    Please contact me(hoshina@icecube.wisc.edu) if any problem 
//    or questions. DO NOT bother Geant4 developpers and Geant4 Users
//    Group Japan.
//
//                                K.Hoshina , 2004
// ====================================================================
#ifdef __USEISOCXX__
#include <sstream>
#else
#include <sstream>
#endif
#include "G4RunManager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"

#include "J4DetectorConstruction.hh"
#include "J4PhysicsList.hh"
#include "J4PrimaryGeneratorAction.hh"
#include "J4RunAction.hh"
#include "J4EventAction.hh"
#include "J4TrackingAction.hh"
#include "TBookKeeper.hh"

#include "J4ParameterListStore.hh"
#include "J4ParameterList.hh"

#define G4VIS_USE 1
#ifdef G4VIS_USE
#include "J4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#endif

//#include "CLHEP/Random/Random.h"

#include "J4DOM.hh"
#include "J4DOMHarness.hh"

#define __INSTALLDOM__  
//#define __INSTALLSOL__  

TBookKeeper* TBookKeeper::fgBookKeeper = new TBookKeeper(); 

int main(int argc, char** argv) 
{

  //-------------------------
  // Set random engine....
  //-------------------------
  // if you want to change a random engine, for example, ...
  
#if 0
  HepJamesRandom randomEngine;
  //RanecuEngine randomEngine;
  HepRandom::setTheEngine(&randomEngine);
#endif

  //-------------------------
  // Set manager 
  //-------------------------

  // RunManager is mandatory to run Geant4
  G4RunManager* runManager = new G4RunManager();  std::cout << std::endl;
//  runManager->SetVerboseLevel(2);

  //===========================================================
  // set mandatory user initialization classes...

  //*--------------------------------------------
  //* ParameterList
  //*--------------------------------------------
  // ParameterListStore is a container of J4VParameterList. 
  // It keeps array of J4VParameterLists from sub-modules

  J4ParameterListStore *paramlistStore = new J4ParameterListStore();

  // To modify default parameters hardcoded in ParameterList classes, 
  // reset it here before detectors are constructed. 
  // Most of child class of J4VParameterLists are
  // singleton and default value is set inside constructor.
 
  // paramlist = J4DOMParameterList::GetInstance();
  // paramlist->Set....

  // then initialize parameter list
  paramlistStore->Initialize();

  //*--------------------------------------------
  //* Install detector components...
  //*--------------------------------------------
  
  J4DetectorConstruction* detecptr = new J4DetectorConstruction();
  
  //* Install detectors
  
#ifdef __INSTALLDOM__  
  J4DOM *dcptr = new J4DOM();
  dcptr->SetMother(detecptr->GetEXPHall());
  detecptr->AddComponent(dcptr);
  J4DOMHarness *harnessptr = new J4DOMHarness();
  harnessptr->SetMother(detecptr->GetEXPHall());
  detecptr->AddComponent(harnessptr);
#endif
  
  //* Solenoid Magnet (should come last)
    
#ifdef __INSTALLSOL__  
  J4SOL *solptr = new J4SOL();
  solptr->SetMother(detecptr->GetEXPHall());
  detecptr->AddComponent(solptr);
#endif

  //*--------------------------------------------
  //* Installation of detectors end
  //*--------------------------------------------
       
  runManager-> SetUserInitialization(detecptr);
  
  // particles and physics processes

  runManager-> SetUserInitialization(new J4PhysicsList);

  //---------------------------------------------
  // set mandatory user action class...
  
  //* primary generator

  J4PrimaryGeneratorAction* primarygenerator = new J4PrimaryGeneratorAction;
  
  runManager-> SetUserAction(primarygenerator);

  //* user action classes... (optional)

  runManager-> SetUserAction(new J4RunAction);
  runManager-> SetUserAction(new J4EventAction);
  runManager-> SetUserAction(new J4TrackingAction);

#ifdef G4VIS_USE
  // initialize visualization package
  G4VisManager* visManager = new G4VisExecutive;
  //G4VisManager* visManager= new J4VisManager;
  visManager-> Initialize();
  std::cerr << " ------------------------------- " << std::endl
         << " ---- VisManager created! ---- " << std::endl
         << " ------------------------------- " << std::endl;
  std::cerr << std::endl;
#endif

  //-----------------------
  // user session start
  //-----------------------

  runManager-> Initialize();
  
  
  //*--------------------------------------------
  //* SwitchOn/Off your detector...
  //*--------------------------------------------
  //* If you wants call SwitchOn/Off recursively,
  //* call virtual function with resolver, as
  //* "J4VDetectorComponent::SwitchOn()".
  //* SwitchOn/(Off() requires option flag
  //* "recursive" or other strings, however,
  //* default value is set as "recursive".
 
 
  //* dc 
  
  // SwitchOn all SDs.
#ifdef __INSTALLDOM__
  dcptr->J4VDetectorComponent::SwitchOn(); 
#endif

        
  //*--------------------------------------------
  //* Detector Switch end
  //*--------------------------------------------

  G4UImanager* UImanager = G4UImanager::GetUIpointer();
  
  G4UIExecutive* ui = 0;
  if (argc==1) { // interactive session, if no arguments given

    ui = new G4UIExecutive(argc, argv);
    UImanager->ApplyCommand("/control/execute macros/vis.mac");
    ui-> SessionStart();
    delete ui;

  } else { // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }

  //-----------------------
  // terminating...
  //-----------------------

#ifdef G4VIS_USE
  delete visManager;
#endif

  delete runManager;  std::cout << std::endl;
  return 0;

}

