// $Id: J4DEggGelSD.cc,v 1.2 2007/03/13 17:29:14 hoshina Exp $
//*************************************************************************
//* --------------------
//* J4DEggGelSD
//* --------------------
//* (Description)
//* 	Class for describing his/her sensitive detector.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************
//090315. important change!!!! attention!!! the photoncathode area changes!!!

#include "J4DEggGelSD.hh"
#include "J4DEggGel.hh"
#include <math.h>
 
//=====================================================================
//---------------------
// class definition
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4DEggGelSD::J4DEggGelSD(J4VDetectorComponent* detector)
		   :J4VSD<J4DEggGelHit>(detector)
{  
}

//=====================================================================
//* destructor --------------------------------------------------------

J4DEggGelSD::~J4DEggGelSD()
{
}

//=====================================================================
//* Initialize --------------------------------------------------------

void J4DEggGelSD::Initialize(G4HCofThisEvent* HCTE)
{
   //create hit collection(s) and
   //push H.C. to "Hit Collection of This Event"
  
   MakeHitBuf(HCTE);  
}

//=====================================================================
//* ProcessHits -------------------------------------------------------

G4bool J4DEggGelSD::ProcessHits(G4Step* aStep, G4TouchableHistory* )
{

    G4cerr << "J4DEggGelSD::ProcessHits: called! " << G4endl;

    //In order to use Get function, you must call SetNewStep() at first.
  
    SetNewStep(aStep);
   
    std::cout <<"the step is set as "<<aStep->GetStepLength()<<std::endl;

    // If current prestep point is not on the surface of the Gel, return.
    // Note that a geometrical information must be taken from prestep point.
    //in the past the following were turned off. now we try to turn them on again.


    G4StepPoint* preStepPoint = GetPreStepPoint();
    if ( preStepPoint->GetStepStatus() != fGeomBoundary) {
     G4cerr << "-------------------------------------------J4DEggGelSD::ProcessHits: the prestep point must on Gel surface. return " << G4endl; 
       return FALSE;
    }


    // create a hit... 

    G4ThreeVector pre         = GetPrePosition();
    
    // <<<<<<<<<<< TMP_TREATMENT!!! <<<<<<<<<<<<<<

    G4double      energy = GetTotalEnergy();
    G4double      tof    = GetTof();

    J4DEggGelHit* hit = new J4DEggGelHit(GetComponent(), pre, energy, tof); 
    ((J4DEggGelHitBuf*)GetHitBuf())->insert(hit);

    //#if 0
    //#if 1
    G4cerr<<"!survived!!!!"<<G4endl;
    G4cerr << "J4DEggGelSD::ProcessHits:intersection = " << pre.x() << " " << pre.y() 
                                << " " << pre.z() << G4endl;
    //#endif

    //kill current track...

    //G4Track *track = GetTrack();
    //track->SetTrackStatus(fStopAndKill);
    //    track->SetTrackStatus(fAlive);
    //track->SetTrackStatus(fStopButAlive);
    
    return TRUE;

}

//=====================================================================
//* EndOfEvent --------------------------------------------------------

void J4DEggGelSD::EndOfEvent(G4HCofThisEvent* )
{			
    // Create new hits and push them to "Hit Collection"
    
}


//=====================================================================
//* DrawAll -----------------------------------------------------------

void J4DEggGelSD::DrawAll()
{
}

//=====================================================================
//* PrintAll ----------------------------------------------------------

void J4DEggGelSD::PrintAll()
{
   G4int nHit = ((J4DEggGelHitBuf*)GetHitBuf())->entries();
   G4cout << "------------------------------------------" << G4endl
          << "*** Gelhit (#hits=" << nHit << ")" << G4endl;
   ((J4DEggGelHitBuf*)GetHitBuf())->PrintAllHits();
}

