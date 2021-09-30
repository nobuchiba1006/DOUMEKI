// $Id: J4LOMGelSD.cc,v 1.2 2007/03/13 17:29:14 hoshina Exp $
//*************************************************************************
//* --------------------
//* J4LOMGelSD
//* --------------------
//* (Description)
//* 	Class for describing his/her sensitive detector.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************
//090315. important change!!!! attention!!! the photoncathode area changes!!!

#include "J4LOMGelSD.hh"
#include "J4LOMGel.hh"
#include <math.h>
 
//=====================================================================
//---------------------
// class definition
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4LOMGelSD::J4LOMGelSD(J4VDetectorComponent* detector)
		   :J4VSD<J4LOMGelHit>(detector)
{  
}

//=====================================================================
//* destructor --------------------------------------------------------

J4LOMGelSD::~J4LOMGelSD()
{
}

//=====================================================================
//* Initialize --------------------------------------------------------

void J4LOMGelSD::Initialize(G4HCofThisEvent* HCTE)
{
   //create hit collection(s) and
   //push H.C. to "Hit Collection of This Event"
  
   MakeHitBuf(HCTE);  
}

//=====================================================================
//* ProcessHits -------------------------------------------------------

G4bool J4LOMGelSD::ProcessHits(G4Step* aStep, G4TouchableHistory* )
{

    std::cerr << "J4LOMGelSD::ProcessHits: called! " << G4endl;

    //In order to use Get function, you must call SetNewStep() at first.
  
    SetNewStep(aStep);
   
    std::cout <<"the step is set as "<<aStep->GetStepLength()<<std::endl;

    // If current prestep point is not on the surface of the Gel, return.
    // Note that a geometrical information must be taken from prestep point.
    //in the past the following were turned off. now we try to turn them on again.


    G4StepPoint* preStepPoint = GetPreStepPoint();
    if ( preStepPoint->GetStepStatus() != fGeomBoundary) {
     std::cerr << "-------------------------------------------J4LOMGelSD::ProcessHits: the prestep point must on Gel surface. return " << G4endl; 
       return FALSE;
    }


    // create a hit... 

    G4ThreeVector pre         = GetPrePosition();
    
    // <<<<<<<<<<< TMP_TREATMENT!!! <<<<<<<<<<<<<<

    G4double      energy = GetTotalEnergy();
    G4double      tof    = GetTof();

    J4LOMGelHit* hit = new J4LOMGelHit(GetComponent(), pre, energy, tof); 
    ((J4LOMGelHitBuf*)GetHitBuf())->insert(hit);

    //#if 0
    //#if 1
    std::cerr<<"!survived!!!!"<<G4endl;
    std::cerr << "J4LOMGelSD::ProcessHits:intersection = " << pre.x() << " " << pre.y() 
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

void J4LOMGelSD::EndOfEvent(G4HCofThisEvent* )
{			
    // Create new hits and push them to "Hit Collection"
    
}


//=====================================================================
//* DrawAll -----------------------------------------------------------

void J4LOMGelSD::DrawAll()
{
}

//=====================================================================
//* PrintAll ----------------------------------------------------------

void J4LOMGelSD::PrintAll()
{
   G4int nHit = ((J4LOMGelHitBuf*)GetHitBuf())->entries();
   std::cout << "------------------------------------------" << G4endl
          << "*** Gelhit (#hits=" << nHit << ")" << G4endl;
   ((J4LOMGelHitBuf*)GetHitBuf())->PrintAllHits();
}

