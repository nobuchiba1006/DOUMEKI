// $Id: J4CircleBeam.hh,v 1.2 2007/03/13 17:29:14 hoshina Exp $
// GEANT4 tag $Name:  $
//

#ifndef J4CircleBeam_h
#define J4CircleBeam_h 1


#include "globals.hh"
#include "G4VPrimaryGenerator.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleDefinition.hh"
#include "G4PrimaryVertex.hh"
#include "G4ParticleMomentum.hh"
#include "G4RotationMatrix.hh"

class G4Event;
class J4CircleBeamMessenger;

class J4CircleBeam : public G4VPrimaryGenerator
{

  friend class J4CircleBeamMessenger;

  public: 

     J4CircleBeam();
     virtual ~J4CircleBeam();
     J4CircleBeam(const J4CircleBeam &right);

     const J4CircleBeam & operator=(const J4CircleBeam &right);
     G4int operator==(const J4CircleBeam &right) const;
     G4int operator!=(const J4CircleBeam &right) const;

     virtual void GeneratePrimaryVertex(G4Event* evt);

     inline virtual G4ThreeVector         GetMeanBeamDirection() const    { return fMeanBeamDirection; }
     inline virtual G4double              GetMeanEnergy() const           { return fMeanEnergy;        } 
     inline virtual G4ThreeVector         GetParticlePolarization() const { return fParticlePolarization; } 
     inline virtual G4ParticleDefinition* GetParticleDefinition() const   { return fParticleDefinition; } 
     inline virtual G4double              GetParticleCharge() const       { return fParticleCharge; }
     inline virtual G4double              GetRadius() const               { return fRadius; } 
     inline virtual G4ThreeVector         GetRotAngles() const;   
     inline virtual G4ThreeVector         GetTranslate() const            { return fTransVector; }
     inline virtual G4bool                IsRandomPolarization() const    { return fIsRandomPolarization; }
     inline virtual void                  RandomizePolarization(G4bool t) { fIsRandomPolarization = t; }
     inline virtual void                  RotateAroundXYZ(G4double theta, G4double psi, G4double phi);
     inline virtual void                  SetEulerAngles(G4double phi, G4double theta, G4double psi);
     inline virtual void                  SetMeanBeamDirection(G4ThreeVector x) { fMeanBeamDirection = x.unit();}
     inline virtual void                  SetMeanEnergy(G4double x)             { fMeanEnergy = x; }
     inline virtual void                  SetParticlePolarization(const G4ThreeVector &v) { fParticlePolarization = v; }
     inline virtual void                  SetParticleDefinition(G4ParticleDefinition *p); 
     inline virtual void                  SetParicleMomentum(G4ThreeVector mom);
     inline virtual void                  SetParticleCharge(G4double x)   { fParticleCharge = x; }
     inline virtual void                  SetRadius(G4double x)           { fRadius = x; }
     inline virtual void                  SetTranslate(G4ThreeVector v)   { fTransVector = v; }

  private:
  
     virtual void            GenerateBeam(G4Event* evt);
     virtual void            SetOptPhotonPolar(G4double angle, const G4ThreeVector &mom);
     inline virtual G4double EnergyToMomentum(G4double energy);
     inline virtual G4double MomentumToEnergy(G4double momentum);
     inline  void            TransformPosition(G4ThreeVector &p)  { p = fRotMatrix * p + fTransVector; }
     inline  void            TransformDirection(G4ThreeVector &v) { v = fRotMatrix * v; }


  private: 

     // common field 

     J4CircleBeamMessenger* fMessenger;

     G4ThreeVector            fParticlePolarization;  // polarization
     G4ParticleDefinition*    fParticleDefinition;    // particle definition
     G4double                 fPDGMass;               // rest mass
     G4double                 fParticleCharge;        // charge
     G4ThreeVector            fMeanBeamDirection;     // mean beam direction
     G4double                 fMeanEnergy;            // mean energy
     G4bool                   fIsRandomPolarization;  // randomize polarization
     G4double                 fRadius;                // radius of circle
     G4double                 fEulerTheta;             // Rot angle of circle around x-axis (theta)
     G4double                 fEulerPsi;             // Rot angle of circle around y-axis (psi)
     G4double                 fEulerPhi;             // Rot angle of circle around z-axis (phi)
     G4RotationMatrix         fRotMatrix;             // lotation matrix of circle 
     G4ThreeVector            fTransVector;           // translation of circle origin

};


//====================================================================
//------------------------------------
// inline finctions
//------------------------------------

void J4CircleBeam::SetParticleDefinition(G4ParticleDefinition *p)
{ 
   fParticleDefinition = p;  
   fPDGMass = p->GetPDGMass();
   fParticleCharge = p->GetPDGCharge();
}

void J4CircleBeam::SetParicleMomentum(G4ThreeVector mom)
{ 
   fMeanBeamDirection = mom.unit();
   fMeanEnergy = MomentumToEnergy(mom.mag());
}

void J4CircleBeam::RotateAroundXYZ(G4double theta, G4double psi, G4double phi)
{

   G4RotationMatrix rot;
   rot.rotateX(theta);
   rot.rotateY(psi);
   rot.rotateZ(phi);
   fRotMatrix = rot;
   //SetEulerAngles(-phi, -theta, -psi);

}

void J4CircleBeam::SetEulerAngles(G4double phi, G4double theta, G4double psi)
{
   fEulerTheta = theta; 
   fEulerPsi = psi; 
   fEulerPhi = phi; 
   fRotMatrix = G4RotationMatrix(fEulerPhi, fEulerTheta, fEulerPsi);
}

G4ThreeVector J4CircleBeam::GetRotAngles() const 
{
   return G4ThreeVector(fEulerTheta, fEulerPsi, fEulerPhi);
}

G4double J4CircleBeam::EnergyToMomentum(G4double energy) 
{
   return sqrt(energy * energy - fPDGMass * fPDGMass);
}

G4double J4CircleBeam::MomentumToEnergy(G4double momentum) 
{
   return sqrt(momentum * momentum + fPDGMass * fPDGMass);
}


#endif







