// $Id: J4MEggGelSD.cc,v 1.2 2007/03/13 17:29:14 hoshina Exp $
//*************************************************************************
//* --------------------
//* J4MEggGelSD
//* --------------------
//* (Description)
//* 	Class for describing his/her sensitive detector.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************
//090315. important change!!!! attention!!! the photoncathode area changes!!!

#include "J4MEggGelSD.hh"
#include "J4MEggGel.hh"
#include <math.h>
 
//=====================================================================
//---------------------
// class definition
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4MEggGelSD::J4MEggGelSD(J4VDetectorComponent* detector)
		   :J4VSD<J4MEggGelHit>(detector)
{  
}

//=====================================================================
//* destructor --------------------------------------------------------

J4MEggGelSD::~J4MEggGelSD()
{
}

//=====================================================================
//* Initialize --------------------------------------------------------

void J4MEggGelSD::Initialize(G4HCofThisEvent* HCTE)
{
   //create hit collection(s) and
   //push H.C. to "Hit Collection of This Event"
  
   MakeHitBuf(HCTE);  
}

//=====================================================================
//* ProcessHits -------------------------------------------------------

G4bool J4MEggGelSD::ProcessHits(G4Step* aStep, G4TouchableHistory* )
{

    std::cerr << "J4MEggGelSD::ProcessHits: called! " << G4endl;

    //In order to use Get function, you must call SetNewStep() at first.
  
    SetNewStep(aStep);
   
    std::cout <<"the step is set as "<<aStep->GetStepLength()<<std::endl;

    // If current prestep point is not on the surface of the Gel, return.
    // Note that a geometrical information must be taken from prestep point.
    //in the past the following were turned off. now we try to turn them on again.


    G4StepPoint* preStepPoint = GetPreStepPoint();
    if ( preStepPoint->GetStepStatus() != fGeomBoundary) {
     std::cerr << "-------------------------------------------J4MEggGelSD::ProcessHits: the prestep point must on Gel surface. return " << G4endl; 
       return FALSE;
    }


    // create a hit... 

    G4ThreeVector pre         = GetPrePosition();
    
    // <<<<<<<<<<< TMP_TREATMENT!!! <<<<<<<<<<<<<<

    G4double      energy = GetTotalEnergy();
    G4double      tof    = GetTof();

    J4MEggGelHit* hit = new J4MEggGelHit(GetComponent(), pre, energy, tof); 
    ((J4MEggGelHitBuf*)GetHitBuf())->insert(hit);

    //#if 0
    //#if 1
    std::cerr<<"!survived!!!!"<<G4endl;
    std::cerr << "J4MEggGelSD::ProcessHits:intersection = " << pre.x() << " " << pre.y() 
                                << " " << pre.z() << G4endl;
    //#endif

    //kill current track...

    G4Track *track = GetTrack();
    track->SetTrackStatus(fStopAndKill);
    //    track->SetTrackStatus(fAlive);
    //track->SetTrackStatus(fStopButAlive);
    
    return TRUE;

}

//=====================================================================
//* EndOfEvent --------------------------------------------------------

void J4MEggGelSD::EndOfEvent(G4HCofThisEvent* )
{			
    // Create new hits and push them to "Hit Collection"
    
}


//=====================================================================
//* DrawAll -----------------------------------------------------------

void J4MEggGelSD::DrawAll()
{
}

//=====================================================================
//* PrintAll ----------------------------------------------------------

void J4MEggGelSD::PrintAll()
{
   G4int nHit = ((J4MEggGelHitBuf*)GetHitBuf())->entries();
   std::cout << "------------------------------------------" << G4endl
          << "*** Gelhit (#hits=" << nHit << ")" << G4endl;
   ((J4MEggGelHitBuf*)GetHitBuf())->PrintAllHits();
}

