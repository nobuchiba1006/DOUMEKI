// $Id: J4PrimaryGeneratorAction.cc,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
//*************************************************************************
//* ------------------------
//* J4PrimaryGeneratorAction
//* ------------------------
//*     
//* (Update Record)
//*     2002/05/30  K.Hoshina   Original version.
//*************************************************************************

#include "J4PrimaryGeneratorAction.hh"

#include <math.h>
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "J4ParticleBeam.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "J4PrimaryGeneratorMessenger.hh"
#include "J4HEPEvtInterface.hh"
#include "J4CAINEvtInterface.hh"
#include "J4CircleBeam.hh"


J4PrimaryGeneratorAction* J4PrimaryGeneratorAction::fPrimaryGeneratorAction = 0;

//************************************************************************
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -----------------------------------------------

J4PrimaryGeneratorAction::J4PrimaryGeneratorAction()
                         :fHEPEvt(0), fCAINEvt(0), fParticleGun(0), 
                          fParticleBeam(0), fCircleBeam(0),
                          fMessenger(0), fHEPEvtFileName(""), 
                          fEprimarygentype(kParticleGun), 
                          fIsInitialized(false)
{
   if (fPrimaryGeneratorAction) {
      G4Exception("J4PrimaryGeneratorAction constructed twice.", "WARN", JustWarning, ""); 
   } 

   fPrimaryGeneratorAction = this;

   fMessenger = new J4PrimaryGeneratorMessenger(this);
   Initialize();
}

//=====================================================================
//* destructor --------------------------------------------------------

J4PrimaryGeneratorAction::~J4PrimaryGeneratorAction()
{
   delete fHEPEvt;
   delete fCAINEvt;
   delete fParticleGun;
   delete fParticleBeam;
   delete fCircleBeam;
   delete fMessenger;
}

//=====================================================================
//* Initialize --------------------------------------------------------

void J4PrimaryGeneratorAction::Initialize()
{

   if (fHEPEvt)      delete fHEPEvt;
   if (fCAINEvt)     delete fCAINEvt;
   if (fParticleGun) delete fParticleGun;
   if (fParticleBeam) delete fParticleBeam;
   if (fCircleBeam)  delete fCircleBeam;

   fHEPEvt  = new J4HEPEvtInterface ("");
   fCAINEvt = new J4CAINEvtInterface("");
   G4int n_particle = 1;
   fParticleGun           = new G4ParticleGun(n_particle);
   fParticleBeam          = new J4ParticleBeam(n_particle);
   fCircleBeam            = new J4CircleBeam();

   G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
   G4String particleName;
   fParticleGun->SetParticleDefinition(particleTable->FindParticle(particleName="geantino"));
   fParticleBeam->SetParticleDefinition(particleTable->FindParticle(particleName="geantino"));
   fCircleBeam->SetParticleDefinition(particleTable->FindParticle(particleName="geantino"));

   fIsInitialized = TRUE;
   std::cerr << "J4PrimaryGeneratorAction::Initialize done" << std::endl;
}

//=====================================================================
//* GeneratePrimaries -------------------------------------------------

void J4PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
   if (!fIsInitialized) Initialize();

   switch(fEprimarygentype) {

      case kHEPEvt :
         fHEPEvt->GeneratePrimaryVertex(anEvent); 
         break;

      case kCAINEvt: 
         fCAINEvt->GeneratePrimaryVertex(anEvent); 
         break;

      case kParticleGun:
         fParticleGun->GeneratePrimaryVertex(anEvent);
         break;
         
      case kParticleBeam:
         fParticleBeam->GeneratePrimaryVertex(anEvent);
         break;

      case kCircleBeam:
         fCircleBeam->GeneratePrimaryVertex(anEvent);
         break;
         
      default:
         fHEPEvt->GeneratePrimaryVertex(anEvent); 
         break;

   }
}




