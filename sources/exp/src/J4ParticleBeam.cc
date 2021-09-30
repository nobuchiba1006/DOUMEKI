// $Id: J4ParticleBeam.cc,v 1.2 2007/03/13 17:29:14 hoshina Exp $
// GEANT4 tag $Name:  $
//
//*************************************************************************
//* --------------------
//* J4ParticleBeam
//* --------------------
//* (Description)
//* 	Class for Particle beam
//*
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************
 
#include "J4ParticleBeam.hh"
#include "G4PrimaryParticle.hh"
#include "J4ParticleBeamMessenger.hh"
#include "G4Event.hh"
#include "G4ios.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh" 

//#define _BEAMCONVERGENCEEXTENT_   5.0*cm
#define _BEAMCONVERGENCEEXTENT_   0.8*m

//=====================================================================
//---------------------
// Class Description
//---------------------

// ====================================================================
//* constructor -------------------------------------------------------

J4ParticleBeam::J4ParticleBeam()
               :G4VPrimaryGenerator(),
                fNVerticesPerBeam(1), 
                fNParticlesPerVertex(1),
                fParticleDefinition(0),
                fPDGMass(0),
                fParticleCharge(0),
                fBeamType(kEIsotropic), 
	        fIsConvergenceMode(FALSE), 
                fMeanBeamDirection(0,0,1),
                fBeamDirectionSigma(0),
                fIsFlatPositionProfile(FALSE), 
                fIsFlatEnergyProfile(FALSE), 
                fMeanEnergy(10.*GeV),
                fMeanEnergySigma(0),
                fIsRandomPolarization(TRUE) 
{
   fCosThetaRange[0] = -1.;
   fCosThetaRange[1] = +1.;
   fEnergyRange[0] = 0.1*GeV;
   fEnergyRange[1] = 100.*GeV;
   fParticlePolarization.set(0., 0., 1);

   for (G4int i=0; i<3; i++) {
      for (G4int j=0; j<2; j++) fBeamPositionRange[i][j] = 0.;
      fBeamPositionSigma[i] = 0;
   }

   fMessenger = new J4ParticleBeamMessenger(this);
}

J4ParticleBeam::J4ParticleBeam(G4int numberofparticles)
               :G4VPrimaryGenerator(),
                fNVerticesPerBeam(1), 
                fNParticlesPerVertex(numberofparticles),
                fParticleDefinition(0),
                fPDGMass(0),
                fParticleCharge(0),
                fBeamType(kEIsotropic), 
	        fIsConvergenceMode(FALSE), 
                fMeanBeamDirection(0,0,1),
                fBeamDirectionSigma(0),
                fIsFlatPositionProfile(FALSE), 
                fIsFlatEnergyProfile(FALSE), 
                fMeanEnergy(10.*GeV),
                fMeanEnergySigma(0),
                fIsRandomPolarization(TRUE) 
{
   fCosThetaRange[0] = -1.;
   fCosThetaRange[1] = +1.;
   fEnergyRange[0] = 0.1*GeV;
   fEnergyRange[1] = 100.*GeV;
   fParticlePolarization.set(0., 0., 1);

   for (G4int i=0; i<3; i++) {
      for (G4int j=0; j<2; j++) fBeamPositionRange[i][j] = 0.;
      fBeamPositionSigma[i] = 0;
   }

   fMessenger = new J4ParticleBeamMessenger(this);
}

J4ParticleBeam::J4ParticleBeam(G4ParticleDefinition * particleDe,
                               G4int numberofparticles)
               :G4VPrimaryGenerator(),
                fNVerticesPerBeam(1), 
                fNParticlesPerVertex(numberofparticles),
                fParticleDefinition(particleDe),
                fPDGMass(particleDe->GetPDGMass()),
                fParticleCharge(particleDe->GetPDGCharge()),
                fBeamType(kEIsotropic), 
	        fIsConvergenceMode(FALSE), 
                fMeanBeamDirection(0,0,1),
                fBeamDirectionSigma(0),
                fIsFlatPositionProfile(FALSE), 
                fIsFlatEnergyProfile(FALSE), 
                fMeanEnergy(10.*GeV),
                fMeanEnergySigma(0),
                fIsRandomPolarization(TRUE) 
{
   fEnergyRange[0] = 0.1*GeV;
   fEnergyRange[1] = 100.*GeV;
   fCosThetaRange[0] = -1.;
   fCosThetaRange[1] = +1.;
   fParticlePolarization.set(0., 0., 1);

   for (G4int i=0; i<3; i++) {
      for (G4int j=0; j<2; j++) fBeamPositionRange[i][j] = 0.;
      fBeamPositionSigma[i] = 0;
   }

   fMessenger = new J4ParticleBeamMessenger(this);
}

// ====================================================================
//* destructor --------------------------------------------------------

J4ParticleBeam::~J4ParticleBeam()
{
  delete fMessenger;
}

// ====================================================================
//* GenerateIsotropicBeam ----------------------------------------------
void J4ParticleBeam::GenerateIsotropicBeam(G4Event* evt)
{
   //--------------------------
   // choose beam direction 

   std::cerr << "--------ParticleBeam:: Isotropic beamtype-------" << std::endl;

   G4double phi      = CLHEP::RandFlat::shoot(0.,2*M_PI);
   G4double costheta = CLHEP::RandFlat::shoot(fCosThetaRange[0],
                                       fCosThetaRange[1]);
   // G4double costheta = cos((2 * G4UniformRand() -1.) * M_PI);

   std::cerr << "beam profile     : phi(rad), costheta = " << phi 
          << " " << costheta << std::endl;

   G4double      sintheta = sqrt((1-costheta)*(1+costheta));
   G4ThreeVector direction(sintheta * cos(phi),
                           sintheta * sin(phi),
                           costheta);

   //--------------------------
   // define particle momentam
   
   G4double energy;

   if (fIsFlatEnergyProfile) {
      // flat momentum profile
      energy = CLHEP::RandFlat::shoot(fEnergyRange[0], fEnergyRange[1]); 
      std::cerr << "flat energy profile  : energy, momentum, direction = ";
   } else {
      // gaussian momentum profile
      energy = CLHEP::RandGauss::shoot(fMeanEnergy, fMeanEnergySigma);
      std::cerr << "gaussian energy profile  : energy, momentum, direction = ";
   }

   //G4double mom = EnergyToMomentum(energy);

   G4ThreeVector finalmv = EnergyToMomentum(energy) * direction;

   std::cerr << energy << " " << finalmv << " " << direction << std::endl; 


   //--------------------------
   // Generate verteces
 
   for (G4int i=0; i<fNParticlesPerVertex; i++) {
					
      //--------------------------
      // define particle position

      G4ThreeVector pv;

      if (fIsFlatPositionProfile) {
         // Flat position profile
         pv(0) = CLHEP::RandFlat::shoot(fBeamPositionRange[0][0],fBeamPositionRange[0][1]);
         pv(1) = CLHEP::RandFlat::shoot(fBeamPositionRange[1][0],fBeamPositionRange[1][1]);
         pv(2) = CLHEP::RandFlat::shoot(fBeamPositionRange[2][0],fBeamPositionRange[2][1]);
         std::cerr << "flat position profile  : position = " << pv << std::endl; 
      } else {
         // Gaussian position profile
         pv(0) = CLHEP::RandGauss::shoot(particle_position.x(),fBeamPositionSigma[0]);
         pv(1) = CLHEP::RandGauss::shoot(particle_position.y(),fBeamPositionSigma[1]);
         pv(2) = CLHEP::RandGauss::shoot(particle_position.z(),fBeamPositionSigma[2]);
         std::cerr << "gaussian position profile  : position = " << pv << std::endl; 
      }
			
      //----------------------------------------
      // optional treatment for convergence mode

      if (fIsConvergenceMode) {
         pv  = (_BEAMCONVERGENCEEXTENT_ * direction) + particle_position;
         direction = (-1 * direction);
         finalmv   = (-1 * finalmv);
         std::cerr << "convergence mode  : position, direction = " 
                << pv << " " << direction << std::endl; 
      } 
					
      //--------------------------
      // create new vertex

      G4PrimaryVertex   *vertex   = new G4PrimaryVertex(pv, particle_time);
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
      std::cerr << "J4ParticleBeam::GenerateIsotropicBeam: No., startp, momentum = " 
             << i << " , " << pv << " , " << finalmv << std::endl;
   }
}

// ====================================================================
//* GenerateGaussianBeam ----------------------------------------------
void J4ParticleBeam::GenerateGaussianBeam(G4Event* evt)
{
   std::cerr << "--------ParticleBeam:: Gaussian beamtype--------" << std::endl;

   for (G4int i=0; i<fNParticlesPerVertex; i++) {

      // define momentum

      G4double energy;

      if (fIsFlatEnergyProfile) {
         // flat momentum profile
         energy = CLHEP::RandFlat::shoot(fEnergyRange[0], fEnergyRange[1]); 
      } else {
         // gaussian momentum profile
         energy = CLHEP::RandGauss::shoot(fMeanEnergy, fMeanEnergySigma);
      }

      G4double mom = EnergyToMomentum(energy);
      G4double theta = CLHEP::RandGauss::shoot(0.,fBeamDirectionSigma);
      G4double phi   = CLHEP::RandFlat::shoot(0., 2*M_PI);
      G4double r     = 1.;
      /*
      G4double mvx = CLHEP::RandGauss::shoot(0.,fBeamDirectionSigma);
      G4double mvy = CLHEP::RandGauss::shoot(0.,fBeamDirectionSigma);
      G4double mvz = 1.;
      */
      G4ThreeVector mv(0,0,1);
      mv.setRThetaPhi(1., theta, phi);

      mv = mom*(mv.unit());
      RefFrame ref;
      ref.SetRefFrame(fMeanBeamDirection);
      G4ThreeVector finalmv = ref.Transform(mv);

      std::cerr << "Mean Beam Direction = " << fMeanBeamDirection << std::endl;
      mv = finalmv.unit();
      double deltaangle = fMeanBeamDirection.angle(mv);
      std::cerr << "Selected Beam Direction = " << mv << " diff angle = " << deltaangle * 180 / M_PI << std::endl;

      // define particle position
      G4ThreeVector pv; 

      if (fIsFlatPositionProfile) {
         // flat profile
         pv(0) = CLHEP::RandFlat::shoot(fBeamPositionRange[0][0],fBeamPositionRange[0][1]);
         pv(1) = CLHEP::RandFlat::shoot(fBeamPositionRange[1][0],fBeamPositionRange[1][1]);
         pv(2) = CLHEP::RandFlat::shoot(fBeamPositionRange[2][0],fBeamPositionRange[2][1]);
         std::cerr << "Flat beam position = " << pv 
                << "           minx = " << fBeamPositionRange[0][0]  
                << "  maxx = " << fBeamPositionRange[0][1] << std::endl
                << "           miny = " << fBeamPositionRange[1][0] 
                << "  maxy = " << fBeamPositionRange[1][1] << std::endl
                << "           minz = " << fBeamPositionRange[2][0] 
                << "  maxz = " << fBeamPositionRange[2][1] << std::endl;
         std::cerr << "     position = " << pv << std::endl; 
      } else {
         // gaussian profile
         pv(0) = CLHEP::RandGauss::shoot(particle_position.x(),fBeamPositionSigma[0]);
         pv(1) = CLHEP::RandGauss::shoot(particle_position.y(),fBeamPositionSigma[1]);
         pv(2) = CLHEP::RandGauss::shoot(particle_position.z(),fBeamPositionSigma[2]);
         std::cerr << "gaussian beam position = " << pv 
                << " sigma = " << fBeamPositionSigma[0] << " " 
                << fBeamPositionSigma[1] << " " << fBeamPositionSigma[2] << std::endl; 
         std::cerr << "     position = " << pv << std::endl; 
      }
    
      // create a new vertex
      G4PrimaryVertex   *vertex   = new G4PrimaryVertex(pv, particle_time);
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
      std::cerr << "J4ParticleBeam::GenerateGaussianBeam: No., startp, momentum = " 
             << i << " , " << pv << " , " << finalmv << std::endl;
   }
}

// ====================================================================
//* GeneratePrimaryVertex ---------------------------------------------

void J4ParticleBeam::GeneratePrimaryVertex(G4Event* evt)
{
   if (fParticleDefinition == 0) {
      std::cerr << " J4ParticleBeam::GeneratePrimaryVertex:"
             << " You have to define particle at first. return." << std::endl;
      return;
   }

   // ---------------------------
   //  start loop over particles
   // ---------------------------
   
   for ( G4int i=0; i<fNVerticesPerBeam; i++ ) {
  
      // ------------------------------
      //  switch on beam type
      // ------------------------------
      switch (fBeamType) {
         case kEIsotropic: 
            GenerateIsotropicBeam(evt);
            break; // end Isotropic case
         case kEGaussian:
            GenerateGaussianBeam(evt);
            break; // end Gaussian case
      } // end switch on beam type
  
   } // end loop over particles
	
}

// ====================================================================
//* SetOptPhotonPolar -------------------------------------------------
void J4ParticleBeam::SetOptPhotonPolar(G4double angle, const G4ThreeVector &dir)
{
   if (fParticleDefinition->GetParticleName() != "opticalphoton") {
     G4cout << "--> warning from J4ParticleBeam::SetOptPhotonPolar() :"
               "the particleGun is not an opticalphoton" << G4endl;
     return;
   }
               
   G4ThreeVector normal (1., 0., 0.);
   G4ThreeVector kphoton = dir.unit();
   G4ThreeVector product = normal.cross(kphoton); 
   G4double modul2       = product*product;
 
   G4ThreeVector e_perpend (0., 0., 1.);
   if (modul2 > 0.) e_perpend = (1./sqrt(modul2))*product; 
   G4ThreeVector e_paralle    = e_perpend.cross(kphoton);
 
   fParticlePolarization = cos(angle)*e_paralle + sin(angle)*e_perpend;

   G4cerr << "angle[deg], polarization, mag= " << angle / (2 * M_PI) * 180 << " " 
          << fParticlePolarization << " " << fParticlePolarization.mag() << G4endl;
}


