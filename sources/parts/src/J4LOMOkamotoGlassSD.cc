// $Id: J4LOMOkamotoGlassSD.cc,v 1.2 2007/03/13 17:29:14 hoshina Exp $
//*************************************************************************
//* --------------------
//* J4LOMOkamotoGlassSD
//* --------------------
//* (Description)
//* 	Class for describing his/her sensitive detector.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************
//090315. important change!!!! attention!!! the photoncathode area changes!!!

#include "J4LOMOkamotoGlassSD.hh"
#include "J4LOMOkamotoGlassHit.hh"
#include "J4LOMOkamotoGlass.hh"
#include <math.h>
 
//=====================================================================
//---------------------
// class definition
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4LOMOkamotoGlassSD::J4LOMOkamotoGlassSD(J4VDetectorComponent* detector)
		   :J4VSD<J4LOMOkamotoGlassHit>(detector)
{  
}

//=====================================================================
//* destructor --------------------------------------------------------

J4LOMOkamotoGlassSD::~J4LOMOkamotoGlassSD()
{
}

//=====================================================================
//* Initialize --------------------------------------------------------

void J4LOMOkamotoGlassSD::Initialize(G4HCofThisEvent* HCTE)
{
   //create hit collection(s) and
   //push H.C. to "Hit Collection of This Event"
  
   MakeHitBuf(HCTE);  
}

//=====================================================================
//* ProcessHits -------------------------------------------------------

G4bool J4LOMOkamotoGlassSD::ProcessHits(G4Step* aStep, G4TouchableHistory* )
{

    std::cout << "J4LOMOkamotoGlassSD::ProcessHits: called! " << std::endl;

    //In order to use Get function, you must call SetNewStep() at first.
  
    SetNewStep(aStep);
   
    std::cout <<"the step is set as "<<aStep->GetStepLength()<<std::endl;

    // If current prestep point is not on the surface of the Okamoto, return.
    // Note that a geometrical information must be taken from prestep point.
    //in the past the following were turned off. now we try to turn them on again.


    G4StepPoint* preStepPoint = GetPreStepPoint();
    if ( preStepPoint->GetStepStatus() != fGeomBoundary) {
     std::cerr << "-------------------------------------------J4LOMOkamotoGlassSD::ProcessHits: the prestep point must on Okamoto surface. return " << G4endl; 
       return FALSE;
    }

    // create a hit... 

    G4ThreeVector pre         = GetPrePosition();
    

    // <<<<<<<<<<< TMP_TREATMENT!!! <<<<<<<<<<<<<<

    G4double      energy = GetTotalEnergy();
    G4double      tof    = GetTof();

    J4LOMOkamotoGlassHit* hit = new J4LOMOkamotoGlassHit(GetComponent(), pre, energy, tof); 
    ((J4LOMOkamotoGlassHitBuf*)GetHitBuf())->insert(hit);

    //#if 0
    //#if 1
    std::cout <<"!survived!!!!" <<std::endl;
    std::cout << "J4LOMOkamotoGlassSD::ProcessHits:intersection = " << pre.x() << " " << pre.y() 
                                << " " << pre.z() << std::endl;
    //#endif

    //kill current track...

    G4Track *track = GetTrack();
    //track->SetTrackStatus(fAlive);
    track->SetTrackStatus(fStopAndKill);
    //track->SetTrackStatus(fStopButAlive);
    
    return TRUE;

}

//=====================================================================
//* EndOfEvent --------------------------------------------------------

void J4LOMOkamotoGlassSD::EndOfEvent(G4HCofThisEvent* )
{			
    // Create new hits and push them to "Hit Collection"
    
}


//=====================================================================
//* DrawAll -----------------------------------------------------------

void J4LOMOkamotoGlassSD::DrawAll()
{
}

//=====================================================================
//* PrintAll ----------------------------------------------------------

void J4LOMOkamotoGlassSD::PrintAll()
{
   G4int nHit = ((J4LOMOkamotoGlassHitBuf*)GetHitBuf())->entries();
   G4cout << "------------------------------------------" << G4endl
          << "*** Okamotohit (#hits=" << nHit << ")" << G4endl;
   ((J4LOMOkamotoGlassHitBuf*)GetHitBuf())->PrintAllHits();
}

