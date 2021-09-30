// $Id: J4DOMPMTSD.cc,v 1.2 2007/03/13 17:29:14 hoshina Exp $
//*************************************************************************
//* --------------------
//* J4DOMPMTSD
//* --------------------
//* (Description)
//* 	Class for describing his/her sensitive detector.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4DOMPMTSD.hh"
#include "J4DOMPMT.hh"
#include <math.h>
 
//=====================================================================
//---------------------
// class definition
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4DOMPMTSD::J4DOMPMTSD(J4VDetectorComponent* detector)
		   :J4VSD<J4DOMPMTHit>(detector)
{  
}

//=====================================================================
//* destructor --------------------------------------------------------

J4DOMPMTSD::~J4DOMPMTSD()
{
}

//=====================================================================
//* Initialize --------------------------------------------------------

void J4DOMPMTSD::Initialize(G4HCofThisEvent* HCTE)
{
   //create hit collection(s) and
   //push H.C. to "Hit Collection of This Event"
  
   MakeHitBuf(HCTE);  
}

//=====================================================================
//* ProcessHits -------------------------------------------------------

G4bool J4DOMPMTSD::ProcessHits(G4Step* aStep, G4TouchableHistory* )
{

    //G4cerr << "J4DOMPMTSD::ProcessHits: called! " << G4endl;

    //In order to use Get function, you must call SetNewStep() at first.
  
    SetNewStep(aStep);
   
    // If current prestep point is not on the surface of the PMT, return.
    // Note that a geometrical information must be taken from prestep point.
    //G4StepPoint* preStepPoint = GetPreStepPoint();
    //if ( preStepPoint->GetStepStatus() != fGeomBoundary) {
    //   G4cerr << "J4DOMPMTSD::ProcessHits: the prestep point must on PMT surface. return " << G4endl; 
    //   return FALSE;
    //}


    // create a hit... 

    G4ThreeVector pre = GetPrePosition();
    
    // <<<<<<<<<<< TMP_TREATMENT!!! <<<<<<<<<<<<<<

    G4ThreeVector localorigin = J4DOMParameterList::GetInstance()->GetPMTLocation();
    G4double      centertorus = 40 * mm;    // see J4DOMPMT.cc

    if (pre.z() < localorigin.z() + centertorus) {
       // photon cannot come into the PMT.
       //G4cerr << "J4DOMPMTSD::ProcessHits:intersection = " << pre.x() << " " << pre.y() 
       //                                                    << " " << pre.z() << G4endl;
       //G4cerr << "J4DOMPMTSD::ProcessHits: the photon hits backside! return " << G4endl; 
       return FALSE;
    }

    // <<<<<<<<<<< TMP_TREATMENT!!! <<<<<<<<<<<<<<
  	// 
  
	G4double      ce    = 1.0;
  
	G4StepPoint* p1 = aStep->GetPreStepPoint();
	G4ThreeVector coord1 = p1->GetPosition();

	const G4AffineTransform transformation =
    p1->GetTouchable()->
    GetHistory()->GetTopTransform();
  
	G4ThreeVector localPosition = transformation.TransformPoint(coord1);
  

    G4double      energy = GetTotalEnergy();
    G4double      tof    = GetTof();


	G4String MyName = GetComponent()->GetName();
    G4int    insideid = GetComponent()->GetMother()->GetMyID();
    G4int    pmtid = GetComponent()->GetMyID();
    
    G4ThreeVector mom = aStep->GetTrack()->GetMomentum().unit();
    G4ThreeVector org(0,0,0);
    G4ThreeVector local_pos = transformation.TransformPoint(coord1);
    G4ThreeVector local_mom = transformation.TransformPoint(mom);
    G4ThreeVector local_org = transformation.TransformPoint(org);
    G4ThreeVector local_dir = (local_mom-local_org).unit();

    
    J4DOMPMTHit* hit = new J4DOMPMTHit(GetComponent(), pre, local_pos, local_dir, ce, energy, tof); 
    ((J4DOMPMTHitBuf*)GetHitBuf())->insert(hit);
  


#if 0
    G4cerr << "J4DOMPMTSD::ProcessHits:intersection = " << pre.x() << " " << pre.y() 
                                << " " << pre.z() << G4endl;
#endif

    //kill current track...

    G4Track *track = GetTrack();
    track->SetTrackStatus(fStopAndKill);
    
    return TRUE;

}

//=====================================================================
//* EndOfEvent --------------------------------------------------------

void J4DOMPMTSD::EndOfEvent(G4HCofThisEvent* )
{			
    // Create new hits and push them to "Hit Collection"
    
}


//=====================================================================
//* DrawAll -----------------------------------------------------------

void J4DOMPMTSD::DrawAll()
{
}

//=====================================================================
//* PrintAll ----------------------------------------------------------

void J4DOMPMTSD::PrintAll()
{
   G4int nHit = ((J4DOMPMTHitBuf*)GetHitBuf())->entries();
   G4cout << "------------------------------------------" << G4endl
          << "*** PMThit (#hits=" << nHit << ")" << G4endl;
   ((J4DOMPMTHitBuf*)GetHitBuf())->PrintAllHits();
}

