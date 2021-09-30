// $Id: J4EggOkamotoGlassSD.cc,v 1.2 2007/03/13 17:29:14 hoshina Exp $
//*************************************************************************
//* --------------------
//* J4EggOkamotoGlassSD
//* --------------------
//* (Description)
//* 	Class for describing his/her sensitive detector.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************
//090315. important change!!!! attention!!! the photoncathode area changes!!!

#include "J4EggOkamotoGlassSD.hh"
#include "J4EggOkamotoGlassHit.hh"
#include "J4EggOkamotoGlass.hh"
#include <math.h>
 
//=====================================================================
//---------------------
// class definition
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4EggOkamotoGlassSD::J4EggOkamotoGlassSD(J4VDetectorComponent* detector)
		   :J4VSD<J4EggOkamotoGlassHit>(detector)
{  
}

//=====================================================================
//* destructor --------------------------------------------------------

J4EggOkamotoGlassSD::~J4EggOkamotoGlassSD()
{
}

//=====================================================================
//* Initialize --------------------------------------------------------

void J4EggOkamotoGlassSD::Initialize(G4HCofThisEvent* HCTE)
{
   //create hit collection(s) and
   //push H.C. to "Hit Collection of This Event"
  
   MakeHitBuf(HCTE);  
}

//=====================================================================
//* ProcessHits -------------------------------------------------------

G4bool J4EggOkamotoGlassSD::ProcessHits(G4Step* aStep, G4TouchableHistory* )
{

    std::cout << "J4EggOkamotoGlassSD::ProcessHits: called! " << std::endl;

    //In order to use Get function, you must call SetNewStep() at first.
  
    SetNewStep(aStep);
   
    std::cout <<"the step is set as "<<aStep->GetStepLength()<<std::endl;

    // If current prestep point is not on the surface of the Okamoto, return.
    // Note that a geometrical information must be taken from prestep point.
    //in the past the following were turned off. now we try to turn them on again.


    G4StepPoint* preStepPoint = GetPreStepPoint();
    if ( preStepPoint->GetStepStatus() != fGeomBoundary) {
     std::cerr << "-------------------------------------------J4EggOkamotoGlassSD::ProcessHits: the prestep point must on Okamoto surface. return " << G4endl; 
       return FALSE;
    }

    // create a hit... 

    G4ThreeVector pre         = GetPrePosition();
    

    // <<<<<<<<<<< TMP_TREATMENT!!! <<<<<<<<<<<<<<

    G4double      energy = GetTotalEnergy();
    G4double      tof    = GetTof();

    J4EggOkamotoGlassHit* hit = new J4EggOkamotoGlassHit(GetComponent(), pre, energy, tof); 
    ((J4EggOkamotoGlassHitBuf*)GetHitBuf())->insert(hit);

    //#if 0
    //#if 1
    std::cout <<"!survived!!!!" <<std::endl;
    std::cout << "J4EggOkamotoGlassSD::ProcessHits:intersection = " << pre.x() << " " << pre.y() 
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

void J4EggOkamotoGlassSD::EndOfEvent(G4HCofThisEvent* )
{			
    // Create new hits and push them to "Hit Collection"
    
}


//=====================================================================
//* DrawAll -----------------------------------------------------------

void J4EggOkamotoGlassSD::DrawAll()
{
}

//=====================================================================
//* PrintAll ----------------------------------------------------------

void J4EggOkamotoGlassSD::PrintAll()
{
   G4int nHit = ((J4EggOkamotoGlassHitBuf*)GetHitBuf())->entries();
   G4cout << "------------------------------------------" << G4endl
          << "*** Okamotohit (#hits=" << nHit << ")" << G4endl;
   ((J4EggOkamotoGlassHitBuf*)GetHitBuf())->PrintAllHits();
}

