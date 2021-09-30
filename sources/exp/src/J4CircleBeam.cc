// $Id: J4CircleBeam.cc,v 1.2 2007/03/13 17:29:14 hoshina Exp $
// GEANT4 tag $Name:  $
//
//*************************************************************************
//* --------------------
//* J4CircleBeam
//* --------------------
//* (Description)
//* 	Class for Particle beam
//*
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************
 
#include "J4CircleBeam.hh"
#include "G4PrimaryParticle.hh"
#include "J4CircleBeamMessenger.hh"
#include "G4Event.hh"
#include "G4ios.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh" 


//#define _BEAMCONVERGENCEEXTENT_   5.0*cm
#define _BEAMCONVERGENCEEXTENT_   0.3*m

//=====================================================================
//---------------------
// Class Description
//---------------------

// ====================================================================
//* constructor -------------------------------------------------------

J4CircleBeam::J4CircleBeam()
               :G4VPrimaryGenerator(),
                fParticleDefinition(0),
                fPDGMass(0),
                fParticleCharge(0),
                fMeanBeamDirection(0,0,1),
                fMeanEnergy(10.*GeV),
                fIsRandomPolarization(TRUE) 
{
   fParticlePolarization.set(0., 0., 1);

   fMessenger = new J4CircleBeamMessenger(this);
}

// ====================================================================
//* destructor --------------------------------------------------------

J4CircleBeam::~J4CircleBeam()
{
   delete fMessenger;
}

// ====================================================================
//* GenerateIsotropicBeam ----------------------------------------------
void J4CircleBeam::GenerateBeam(G4Event* evt)
{
   //--------------------------
   // choose random position 

   //std::cerr << "--------CircleBeam:: -------" << std::endl;

   G4double x = CLHEP::RandFlat::shoot(-fRadius, fRadius);
   G4double y = CLHEP::RandFlat::shoot(-fRadius, fRadius);

   while (x * x + y * y  > fRadius * fRadius) {
      x = CLHEP::RandFlat::shoot(-fRadius, fRadius);
      y = CLHEP::RandFlat::shoot(-fRadius, fRadius);
   }

   particle_position.set(x, y, 0.);   // in local circle coodinate
   G4ThreeVector finalmv = EnergyToMomentum(fMeanEnergy) * fMeanBeamDirection;
   //std::cerr << "pos, mom " <<  particle_position << " " << finalmv << std::endl; 

   //--------------------------
   // transform position and direction

   TransformPosition(particle_position);
   TransformDirection(finalmv);
   //std::cerr << "transformed pos, mom " <<  particle_position << " " << finalmv << std::endl; 

   //--------------------------
   // create new vertex

   G4PrimaryVertex   *vertex   = new G4PrimaryVertex(particle_position, particle_time);
   G4PrimaryParticle *particle = new G4PrimaryParticle(fParticleDefinition,
                                                       finalmv.x(),
                                                       finalmv.y(),
                                                       finalmv.z());
   particle->SetMass(fPDGMass);
   particle->SetCharge( fParticleCharge );

   //--------------------------
   // Set polarization

   if (fIsRandomPolarization) {
      G4double angle = CLHEP::RandFlat::shoot(0., 2*M_PI); 
      SetOptPhotonPolar(angle, finalmv);
   } 

   particle->SetPolarization(fParticlePolarization.x(),
                             fParticlePolarization.y(),
                             fParticlePolarization.z());
   vertex->SetPrimary( particle );
   evt->AddPrimaryVertex( vertex );
}

// ====================================================================
//* GeneratePrimaryVertex ---------------------------------------------

void J4CircleBeam::GeneratePrimaryVertex(G4Event* evt)
{
   if (fParticleDefinition == 0) {
      //std::cerr << " J4CircleBeam::GeneratePrimaryVertex:"
      //       << " You have to define particle at first. return." << std::endl;
      return;
   }

   // ---------------------------
   //  start loop over particles
   // ---------------------------
   
   GenerateBeam(evt);
	
}

// ====================================================================
//* SetOptPhotonPolar -------------------------------------------------
void J4CircleBeam::SetOptPhotonPolar(G4double angle, const G4ThreeVector &mom)
{
   if (fParticleDefinition->GetParticleName() != "opticalphoton") {
     std::cout << "--> warning from J4CircleBeam::SetOptPhotonPolar() :"
               "the particleGun is not an opticalphoton" << G4endl;
     return;
   }
               
   G4ThreeVector normal (1., 0., 0.);
   G4ThreeVector kphoton = mom.unit();
   G4ThreeVector product = normal.cross(kphoton); 
   G4double modul2       = product*product;
 
   G4ThreeVector e_perpend (0., 0., 1.);
   if (modul2 > 0.) e_perpend = (1./sqrt(modul2))*product; 
   G4ThreeVector e_paralle    = e_perpend.cross(kphoton);
 
   fParticlePolarization = cos(angle)*e_paralle + sin(angle)*e_perpend;
   fParticlePolarization.unit();

   //std::cerr << "angle, polarization = " << angle << " " << fParticlePolarization << G4endl;
}


