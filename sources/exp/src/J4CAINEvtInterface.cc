//
// ********************************************************************
// J4CAINEvtInterface
//
// See description in J4CAINEvtInterface.hh
//
// (Author)
//    Akiya Miyamoto, KEK, 20-May-2002  (akiya.miyamoto@kek.jp)
// ********************************************************************
//
//
// $Id: J4CAINEvtInterface.cc,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
// 
// --------------------------------------------------------------------

#ifdef __USEISOCXX__
#include <sstream>
#else
#include <sstream>
#endif

#include "G4ios.hh"
#include "J4CAINEvtInterface.hh"
#include "J4CAINEvtMessenger.hh"
#include "G4ParticleTable.hh"

#include "G4PrimaryVertex.hh"
#include "G4PrimaryParticle.hh"
#include "G4Event.hh"
#include "G4StateManager.hh"
#include "G4SystemOfUnits.hh"

// ------------------------------------------------------------
J4CAINEvtInterface::J4CAINEvtInterface(G4String file)
                   :fFileName(""),  fNread(0),
                    fGamma(0), fElectron(0), fPositron(0),
                    fGenGamma(true), fGenElectron(true), fGenPositron(true),
                    fVerboseLevel(0), fMessenger(0)
{

  if ( file != "" ) OpenCainFile(file); 

  G4ThreeVector zero(0,0,0);
  particle_position = zero;
  particle_time = 0.0;

  G4ParticleTable *particleTable=G4ParticleTable::GetParticleTable();

  fGamma=particleTable->FindParticle("gamma");
  fElectron=particleTable->FindParticle("e-");
  fPositron=particleTable->FindParticle("e+");

  fGenGamma=true;
  fGenElectron=true;
  fGenPositron=true;
  fGenDirection=1.0;

  fMessenger=new J4CAINEvtMessenger(this);

}

// ------------------------------------------------------------
void J4CAINEvtInterface::OpenCainFile(G4String evfile)
{
  if( evfile != "" ) fFileName = evfile; 
  if (fInputStream.is_open()) fInputStream.close();

  // change abortion level of G4Exeption temporary...
  // SuppressAbortion = 2 represents no abotion.
  G4int abortlevel_keep = G4StateManager::GetStateManager()->GetSuppressAbortion();
  G4StateManager::GetStateManager()->SetSuppressAbortion(2);

  fInputStream.open(fFileName);
  if (!fInputStream) {
     char buf[2048];
     sprintf(buf, "G4CAINEvtInterface:: check filename and retry. cannot open file %s\n", fFileName.data());
     G4Exception(buf, "FATAL", FatalException, "");
  } else {
     std::cout << "CAIN input file : " << fFileName << " is opened." << std::endl;
  }

  // reset abortion level...
  G4StateManager::GetStateManager()->SetSuppressAbortion(abortlevel_keep);
 
}

// ------------------------------------------------------------
void J4CAINEvtInterface::SetGenDirection(G4double flag)
{
  fGenDirection=flag;
}

// ------------------------------------------------------------
void J4CAINEvtInterface::SetGenGamma(G4bool flag)
{
  fGenGamma=flag;
}

// ------------------------------------------------------------
void J4CAINEvtInterface::SetGenElectron(G4bool flag)
{
  fGenElectron=flag;
}

// ------------------------------------------------------------
void J4CAINEvtInterface::SetGenPositron(G4bool flag)
{
  fGenPositron=flag;
}


// ------------------------------------------------------------
J4CAINEvtInterface::~J4CAINEvtInterface()
{;}

// ------------------------------------------------------------
void J4CAINEvtInterface::GeneratePrimaryVertex(G4Event* evt)
{

  if( !fInputStream.is_open() ) { OpenCainFile(); }

  char input[512];

  G4int id, kgen;
  G4double weight, ct,cx,cy,cs,ce,cpx,cpy,cps,csx,csy,css;
  while(1) { 
    fInputStream.getline(input,512);
    if( fInputStream.eof() ) {
      char buf[2048];
      sprintf(buf, "End-Of-File while reading CAIN file, %s", fFileName.data());
      G4Exception(buf, "WARNING", JustWarning, "");
      return;
    }
    if( input[0] != '!' ) {
      for(G4int i=0;i<512;i++){
         if( input[i] == 'D' ) {
            input[i]='E'; 
         }
         if( input[i] == '\00' ) break;
      }

#ifdef __USEISOCXX__
      std::istringstream sin(input);
#else
      std::istringstream sin(input);
#endif
      sin >>  id >> kgen >> weight >> ct >> cx >> cy >> cs >> 
	   ce >> cpx >> cpy >> cps >> csx >> csy >> css ;

      G4bool samedir= (fGenDirection*cps >= 0.0 ? true : false );

      if( samedir ) {
         if ( id == 1 && fGenGamma ) break ;
         if ( id == 2 && fGenElectron ) break ;
         if ( id == 3 && fGenPositron ) break ;
      }
    }
  }

  ct *= m;  cx *= m; cy*=m ; cs*= m ; 
  ce*= eV ; cpx *= eV ; cpy *= eV ; cps *= eV;

  if( fVerboseLevel > 0 ) {
    std::cout << "CAIN event generated: id=" << id;
    std::cout << "(px,py,pz)=(" << cpx/GeV << "," ;
    std::cout << cpy/GeV << "," << cps/GeV << ") (GeV) " << std::endl ;
  }

  // create a new vertex

  G4PrimaryVertex *vertex=
    new G4PrimaryVertex(G4ThreeVector(cx, cy, cs), ct);

  // create new primaries and set them to the vertex
  G4ParticleDefinition *particle_definition;
  switch(id) {
    case 1: 
      particle_definition=fGamma;
      break;
    case 2: 
      particle_definition=fElectron;
      break;
    case 3:
      particle_definition=fPositron;
      break;
  default:
    char sout[2048];
    sprintf(sout, "Error: Undefined particle id %d is obtained\n", id);
    G4Exception(sout, "WARNING", JustWarning, "");
    return;
  }

  G4double mass=particle_definition->GetPDGMass();
  G4PrimaryParticle *particle=
    new G4PrimaryParticle(particle_definition, cpx, cpy, cps);
  particle->SetMass( mass );
  particle->SetCharge( particle_definition->GetPDGCharge() );
  particle->SetPolarization( csx, csy, css );
  particle->SetWeight( weight );

  vertex->SetPrimary( particle );

  evt->AddPrimaryVertex( vertex );


}

