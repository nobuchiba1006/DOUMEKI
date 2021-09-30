// $Id: Dominant_DEgg.cc,v 1.1.1.1 2017/08/29 lulu Exp $
// ====================================================================
//    Dominant_DEgg.cc
//   
//    DEgg Raytrace Monte-Carlo program
//
//    NOTE:
//    Please contact (hoshina@hepburn.s.chiba-u.ac.jp) if any problems 
//    or questions. DO NOT bother Geant4 developpers and Geant4 Users
//    Group Japan.
//
//                                K.Hoshina , 2004
//
//    Modifed according to DOM geometry.
//
//
// ====================================================================
#ifdef __USEISOCXX__
#include <sstream>
#else
#include <sstream>
#endif
#include "G4RunManager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"

#include "J4DetectorConstruction.hh"
#include "J4PhysicsList.hh"
#include "J4PrimaryGeneratorAction.hh"
#include "J4RunAction.hh"
#include "J4EventAction.hh"
#include "J4TrackingAction.hh"
#include "TBookKeeper.hh"

#include "J4ParameterList.hh"
#include "J4PartsParameterList.hh"
#include "J4DEggParameterList.hh"
#include "J4ParameterListStore.hh"

#define G4VIS_USE 1
#ifdef G4VIS_USE
#include "J4VisManager.hh"
#include "G4VisExecutive.hh"

#endif

//#include "CLHEP/Random/Random.h"

#include "J4DEgg.hh"
#include "J4DEggGel.hh"
#include "J48inchPMT.hh"
#include "J4EggHarness.hh" 
#include "J4BubbleColumn.hh" 

#define __INSTALLDEGG__  
//#define __INSTALLSOL__  

#include "FTFP_BERT.hh"
#include "G4OpticalPhysics.hh"
#include "G4EmStandardPhysics_option4.hh"

TBookKeeper* TBookKeeper::fgBookKeeper = new TBookKeeper(); 

int main(int argc, char** argv) 
{

  // arguments
  G4String miescatlen = "2.0";
  G4double holeicerad = 6.0*cm;
  G4String macroname;

  if ( argc >= 2) {
      std::cout << "batch mode called" << std::endl;
      macroname = G4String(argv[1]);
      if (argc >= 3) {
          miescatlen = argv[2];
          holeicerad = atof(argv[3]) * cm;
      }
  }

  char buf[2048];
  sprintf(buf, "tables/holeice/matprop_holeice_0.95_%scm.dat", miescatlen.c_str());
  G4String holeicetablename(buf);

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

  G4RunManager* runManager = new G4RunManager();  std::cout << std::endl;
  runManager->SetVerboseLevel(2);

  //===========================================================
  // set mandatory user initialization classes...

  //*--------------------------------------------
  //* ParameterList
  //*--------------------------------------------
  // ParameterListStore is a container of J4VParameterList. 
  // It keeps array of J4VParameterLists from sub-modules

  // To modify default parameters hardcoded in ParameterList classes, 
  // reset it here before detectors are constructed. 
  // Most of child class of J4VParameterLists are
  // singleton and default value is set inside constructor.
 
  // paramlist = J4DOMParameterList::GetInstance();
  // paramlist->Set....

  // exphall must be initialized first
  J4ParameterList *expparam = J4ParameterList::GetInstance(); 
  expparam->Initialize();
  expparam->SetEXPHallHalfX(50.0 * m);
  expparam->SetEXPHallHalfY(50.0 * m);
  expparam->SetEXPHallHalfZ(50.0 * m);

  J4PartsParameterList *partsparam = J4PartsParameterList::GetInstance(); 
  partsparam->SetMatpropHoleiceFilename(holeicetablename);
  partsparam->Initialize();
  partsparam->SetBubbleColumnRadius(holeicerad);

  J4DEggParameterList *deggparam = J4DEggParameterList::GetInstance(); 
  deggparam->Initialize();

  // then initialize parameter list
  //J4ParameterListStore *paramlists = J4ParameterListStore::GetInstance();
  //paramlists->Initialize();


  //*--------------------------------------------
  //* Install detector components...
  //*--------------------------------------------
  
  J4DetectorConstruction* detecptr = new J4DetectorConstruction();

  //* Drift Chamber 
  
#ifdef __INSTALLDEGG__  
  J4DEgg *dcptr = new J4DEgg();
  //J48inchPMT *dcptr = new J48inchPMT();
  //J4DEggGel *dcptr = new J4DEggGel();
  dcptr->SetMother(detecptr->GetEXPHall());
  detecptr->AddComponent(dcptr);

  J4EggHarness *harnessptr = new J4EggHarness(); //new
  harnessptr->SetMother(detecptr->GetEXPHall());   //new
  detecptr->AddComponent(harnessptr); //new

  J4BubbleColumn *bubblecolumnptr = new J4BubbleColumn("Egg"); //new
  bubblecolumnptr->SetMother(detecptr->GetEXPHall()); 
  detecptr->AddComponent(bubblecolumnptr);

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


  // Physics list
  /*
  G4VModularPhysicsList* physicsList = new FTFP_BERT;
  physicsList->ReplacePhysics(new G4EmStandardPhysics_option4());
  G4OpticalPhysics* opticalPhysics = new G4OpticalPhysics();
  physicsList->RegisterPhysics(opticalPhysics);
  runManager-> SetUserInitialization(physicsList);
  */

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
  //G4VisManager* visManager= new J4VisManager;
  G4VisManager* visManager = new G4VisExecutive;
  visManager-> Initialize();
  std::cerr << " ------------------------------- " << std::endl
         << " ---- J4VisManager created! ---- " << std::endl
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
#ifdef __INSTALLDEGG__
  dcptr->J4VDetectorComponent::SwitchOn(); 
 

  // Then, SwitchOff Okamoto.
  /*
  std::stringstream str;
  str << "EXPName:DEgg:Okamoto";
  G4String name;
  str >> name;
  J4VDetectorComponent::GetComponentPtrByName(name)->SwitchOff();
  std::cout << "SwitchOff Okamoto" << std::endl;
  */

  /*
  // Then, SwitchOff Inside. attention!!! InsideSD does not exist now.
  std::stringstream str;
  str << "EXPName:DEgg:Inside";
  G4String name;
  str >> name;
  J4VDetectorComponent::GetComponentPtrByName(name)->SwitchOff();
  std::cout << "SwitchOff Inside" << std::endl;
  */
  // Then, SwitchOff Gel.
  /*
  for (G4int i=0; i<2; i++) {
    std::stringstream str;
    str << "EXPName:DEgg:Inside:Gel" << i;
    G4String name;
    str >> name;
    J4VDetectorComponent::GetComponentPtrByName(name)->SwitchOff();
    std::cout << "SwitchOff Gel" << i << std::endl;
  }
  */
  /*
  // Then, SwitchOff PMTs.
  for (G4int i=0; i<2; i++) {
    std::stringstream str;
    str << "EXPName:DEgg:Inside:PMT" << i;
    G4String name;
    str >> name;
    J4VDetectorComponent::GetComponentPtrByName(name)->SwitchOff();
    std::cout << "SwitchOff PMT" << i << std::endl;
  }
  */
#endif

  //*--------------------------------------------
  //* Detector Switch end
  //*--------------------------------------------

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();
  
  // Process macro or start UI session
  //
  G4UIExecutive* ui = 0;

  if ( argc!=1 ) { 
    // batch mode
    std::cerr << "batch mode called" << std::endl;
    G4String command = "/control/execute " + macroname;
    std::cout << "command " << command << std::endl;
    UImanager->ApplyCommand(command);
  }
  else { 
    // interactive mode
    ui = new G4UIExecutive(argc, argv);
    UImanager->ApplyCommand("/control/execute macros/vis.mac");
    ui-> SessionStart();
    delete ui;
  }

  //-----------------------
  // terminating...
  //-----------------------

  //#ifdef G4VIS_USE
  delete visManager;
  delete runManager;
  //#endif
  std::cout << "this is the end..."<<std::endl;

  //return 0;

}

