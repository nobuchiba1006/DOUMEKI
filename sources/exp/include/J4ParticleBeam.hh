// $Id: J4ParticleBeam.hh,v 1.2 2007/03/13 17:29:14 hoshina Exp $
// GEANT4 tag $Name:  $
//

#ifndef J4ParticleBeam_h
#define J4ParticleBeam_h 1


#include "globals.hh"
#include "G4VPrimaryGenerator.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleDefinition.hh"
#include "G4PrimaryVertex.hh"
#include "G4ParticleMomentum.hh"

class G4Event;
class J4ParticleBeamMessenger;

// class description:
//
// This is a concrete class of G4VPrimaryGenerator. It shoots a particle of given type
// to a given direction with a given kinetic energy. 
// The position and time of the primary particle must be set by the corresponding
// set methods of G4VPrimaryGenerator base class, otherwise zero will be set.
//
// The FAQ to this class is for randomizing position/direction/kinetic energy of primary
// particle. But, J4ParticleBeam does NOT have any way of randomization. Instead, the user's
// concrete implementation of G4VUserPrimaryGeneratorAction which transmits G4Event object
// to this particle gun can randomize these quantities and set to this particle gun before
// invoking GeneratePrimaryVertex() method.
// Note that, even if the particle gun shoots more than one particles at one invokation of
// GeneratePrimaryVertex() method, all particles have the same physical quantities. If the
// user wants to shoot two particles with different momentum, position, etc., invoke
// GeneratePrimaryVertex() method twice and set quantities on demand to the particle gun.
//

class J4ParticleBeam : public G4VPrimaryGenerator
{

  friend class J4ParticleBeamMessenger;

  public: // with description

     enum EBeamType { kEIsotropic = 0, kEGaussian = 1 };

     J4ParticleBeam();
     J4ParticleBeam(G4int numberofparticles);
     J4ParticleBeam(G4ParticleDefinition * particleDef, 
                    G4int numberofparticles = 1);
     // costructors. "numberofparticles" is number of particles to be shoot at one invokation
     // of GeneratePrimaryVertex() method. All paricles are shoot with the same physical
     // quantities.

     virtual ~J4ParticleBeam();
     J4ParticleBeam(const J4ParticleBeam &right);

     const J4ParticleBeam & operator=(const J4ParticleBeam &right);
     G4int operator==(const J4ParticleBeam &right) const;
     G4int operator!=(const J4ParticleBeam &right) const;

     virtual void GeneratePrimaryVertex(G4Event* evt);

     //---------------------------------------------------------------------------------
     // general setter & getter

     inline virtual void SetNVerticesPerBeam(G4int n)     { fNVerticesPerBeam = n;     } 
     inline virtual void SetNParticlesPerVertex(G4int n)    { fNParticlesPerVertex = n;    } 
     inline virtual void SetParticlePolarization(const G4ThreeVector &v) 
                         { fParticlePolarization = v;                                 } 
     inline virtual void SetParticleDefinition(G4ParticleDefinition *p) 
                         { 
                            fParticleDefinition = p;  
                            fPDGMass = p->GetPDGMass();
                            fParticleCharge = p->GetPDGCharge();
                         }
                          
     inline virtual void SetParicleMomentum(G4ThreeVector mom)
                         { 
                            fMeanBeamDirection = mom.unit();
                            fMeanEnergy = MomentumToEnergy(mom.mag());
                         }
     inline virtual void SetParticleCharge(G4double x) { fParticleCharge = x;           }

     inline virtual G4int GetNVerticesPerBeam()    const { return fNVerticesPerBeam;    } 
     inline virtual G4int GetNParticlesPerVertex() const { return fNParticlesPerVertex; } 
     inline virtual G4ThreeVector         GetParticlePolarization() const 
                                          { return fParticlePolarization;               } 
     inline virtual G4ParticleDefinition* GetParticleDefinition() const 
                                          { return fParticleDefinition;                 } 
     inline virtual G4ThreeVector         GetParticleMomentum() const 
                                          { return fMeanEnergy * fMeanBeamDirection;    }
     inline virtual G4double              GetParticleCharge() const 
                                          { return fParticleCharge;                     }

     //---------------------------------------------------------------------------------
     // definsion of beam type (0,1 = isotropic beam , gaussian beam)

     inline virtual void      SetBeamType(EBeamType t)    { fBeamType = (EBeamType)t;  }

     inline virtual EBeamType GetBeamType() const         { return fBeamType;          }

     // ... for isotropic beam

     inline virtual void     SetConvergenceMode(G4bool x) { fIsConvergenceMode = x;    }
     inline virtual void     SetCosThetaMin(G4double x)   { fCosThetaRange[0] = x;     } 
     inline virtual void     SetCosThetaMax(G4double x)   { fCosThetaRange[1] = x;     } 

     inline virtual G4bool   IsConvergenceMode() const    { return fIsConvergenceMode; }
     inline virtual G4double GetCosThetaMin() const       { return fCosThetaRange[0];  } 
     inline virtual G4double GetCosThetaMax() const       { return fCosThetaRange[1];  } 

     // ... for gaussian beam

     inline virtual void     SetMeanBeamDirection(G4ThreeVector x) 
                                                       { fMeanBeamDirection = x.unit();}
     inline virtual void     SetBeamDirectionSigma(G4double x) 
                                                          { fBeamDirectionSigma = x;   }

     inline virtual G4ThreeVector GetMeanBeamDirection() const 
                                                          { return fMeanBeamDirection; }
     inline virtual G4double      GetBeamDirectionSigma() const 
                                                          { return fBeamDirectionSigma; }


     //---------------------------------------------------------------------------------
     // definitions of initial beam position profile (0,1 = gaussian spot, flat spread)

     inline virtual void   SetBeamPositionProfile(G4bool t) { fIsFlatPositionProfile = t;   }

     inline virtual G4bool IsFlatPositionProfile() const   { return fIsFlatPositionProfile; }

     // ... for gaussian position profile

     inline virtual void SetBeamPositionSigmaX(G4double x) { fBeamPositionSigma[0] = x;   }
     inline virtual void SetBeamPositionSigmaY(G4double x) { fBeamPositionSigma[1] = x;   }
     inline virtual void SetBeamPositionSigmaZ(G4double x) { fBeamPositionSigma[2] = x;   }

     inline virtual G4double GetBeamPositionSigmaX() const { return fBeamPositionSigma[0]; }
     inline virtual G4double GetBeamPositionSigmaY() const { return fBeamPositionSigma[1]; }
     inline virtual G4double GetBeamPositionSigmaZ() const { return fBeamPositionSigma[2]; }

     // ... for flat position profile

     inline virtual void SetBeamPositionRangeXMin(G4double x)  { fBeamPositionRange[0][0] = x;    }
     inline virtual void SetBeamPositionRangeXMax(G4double x)  { fBeamPositionRange[0][1] = x;    }
     inline virtual void SetBeamPositionRangeYMin(G4double x)  { fBeamPositionRange[1][0] = x;    }
     inline virtual void SetBeamPositionRangeYMax(G4double x)  { fBeamPositionRange[1][1] = x;    }
     inline virtual void SetBeamPositionRangeZMin(G4double x)  { fBeamPositionRange[2][0] = x;    }
     inline virtual void SetBeamPositionRangeZMax(G4double x)  { fBeamPositionRange[2][1] = x;    }

     inline virtual G4double GetBeamPositionRangeXMin() const  { return fBeamPositionRange[0][0]; }
     inline virtual G4double GetBeamPositionRangeXMax() const  { return fBeamPositionRange[0][1]; }
     inline virtual G4double GetBeamPositionRangeYMin() const  { return fBeamPositionRange[1][0]; }
     inline virtual G4double GetBeamPositionRangeYMax() const  { return fBeamPositionRange[1][1]; }
     inline virtual G4double GetBeamPositionRangeZMin() const  { return fBeamPositionRange[2][0]; }
     inline virtual G4double GetBeamPositionRangeZMax() const  { return fBeamPositionRange[2][1]; }


     //---------------------------------------------------------------------------------
     // definitions of beam energy profile (0,1 = gaussian, flat)

     inline virtual void   SetFlatEnergyProfile(G4bool t){ fIsFlatEnergyProfile = t;  }

     inline virtual G4bool IsFlatEnergyProfile() const   { return fIsFlatEnergyProfile; }

     // ... for gaussian energy profile

     inline virtual void SetMeanEnergy(G4double x)         { fMeanEnergy = x;           }
     inline virtual void SetMeanEnergySigma(G4double x)    { fMeanEnergySigma = x;      }

     inline virtual G4double GetMeanEnergy() const         { return fMeanEnergy;        } 
     inline virtual G4double GetMeanEnergySigma() const    { return fMeanEnergySigma;   }

     // ... for flat energy profile

     inline virtual void SetEnergyRangeMin(G4double x)     { fEnergyRange[0] = x;       }
     inline virtual void SetEnergyRangeMax(G4double x)     { fEnergyRange[1] = x;       }

     inline virtual G4double GetEnergyRangeMin()  const    { return fEnergyRange[0];    }
     inline virtual G4double GetEnergyRangeMax()  const    { return fEnergyRange[1];    }
     
     //---------------------------------------------------------------------------------
     // definitions of beam polarization

     inline virtual void RandomizePolarization(G4bool t){ fIsRandomPolarization = t; }
     
     inline virtual G4bool IsRandomPolarization() const   { return fIsRandomPolarization; }

  private:
  
     virtual void            GenerateIsotropicBeam(G4Event* evt);
     virtual void            GenerateGaussianBeam(G4Event* evt);

     virtual void            SetOptPhotonPolar(G4double angle, const G4ThreeVector &mom);


     inline virtual G4double EnergyToMomentum(G4double energy);
     inline virtual G4double MomentumToEnergy(G4double momentum);
    
     class RefFrame
     {
        public:
           void SetRefFrame(const G4ThreeVector &zdir)
           {
	      G4ThreeVector oldzaxis(0.,0.,1.);
              fAxes[2] = zdir.unit();
              if (fabs(fAxes[2].z()-1.) < 1.e-12) {
                 fAxes[0].set(1.,0.,0.);
              } else if (fabs(fAxes[2].z()+1.) < 1.e-12) {
                 fAxes[0].set(-1.,0.,0.);
              } else {
                 fAxes[0] = (oldzaxis.cross(fAxes[2])).unit();
              }
	      fAxes[1] = (fAxes[2].cross(fAxes[0])).unit();
           }

           G4ThreeVector Transform(const G4ThreeVector &v)
           {
              return (v.x()*fAxes[0] + v.y()*fAxes[1] + v.z()*fAxes[2]);
           }
        private:
           G4ThreeVector fAxes[3];
     };


  public:


  private: 

     // common field 

     J4ParticleBeamMessenger* fMessenger;

     G4int                    fNVerticesPerBeam;      // number of vertices per beam
     G4int                    fNParticlesPerVertex;   // number of particles per vertex
     G4ThreeVector            fParticlePolarization;  // polarization
     G4ParticleDefinition*    fParticleDefinition;    // particle definition
     G4double                 fPDGMass;               // rest mass
     G4double                 fParticleCharge;        // charge

     // definition of beam type (0,1 = isotropic, gaussian)
     EBeamType                fBeamType;              // beam type

     // ... for isotropic beam
     G4bool                   fIsConvergenceMode;     // beam direction(divergence, convergence)
     G4double                 fCosThetaRange[2];      // Cos(Theta) range for isotropic beam

     // ... for gaussian beam
     G4ThreeVector            fMeanBeamDirection;     // mean beam direction
     G4double                 fBeamDirectionSigma;    // sigma of the beam direction

     // definitions of initial beam position profile (0,1 = gaussian, flat spread)
     G4bool                   fIsFlatPositionProfile; // initial beam position

     // ... for gaussian profile
     G4double                 fBeamPositionSigma[3];  // sigma of initial beam position

     // ... for flat profile
     G4double                 fBeamPositionRange[3][2];// Beam position range for
                                                      // FlatPositionProfile

     // definitions of beam energy profile (0,1 = gaussian, flat)
     G4bool                   fIsFlatEnergyProfile;   // Momentum(Energy) profile

     // ... for gaussian profile
     G4double                 fMeanEnergy;            // mean energy
     G4double                 fMeanEnergySigma;       // sigma of mean energy 

     // ... for flat profile
     G4double                 fEnergyRange[2];        // Momentum range for FlatEnergyProfile

     // beam polarization
     G4bool                   fIsRandomPolarization;   // randomize polarization

};


//====================================================================
//------------------------------------
// inline finctions
//------------------------------------

G4double J4ParticleBeam::EnergyToMomentum(G4double energy) 
{
   return sqrt(energy * energy - fPDGMass * fPDGMass);
}

G4double J4ParticleBeam::MomentumToEnergy(G4double momentum) 
{
   return sqrt(momentum * momentum + fPDGMass * fPDGMass);
}


#endif







