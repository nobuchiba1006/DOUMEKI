// $Id: J44inchPMTCathodeSD.cc,v 1.2 2007/03/13 17:29:14 hoshina Exp $
//*************************************************************************
//* --------------------
//* J44inchPMTCathodeSD
//* --------------------
//* (Description)
//* 	Class for describing his/her sensitive detector.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*     090315. important change!!!! attention!!! the photoncathode area changes!!!
//*     2020/09/03 M.Suzuki Change the definition of the photocathode area
//*     Change PMT grobal frame position to the local frame position
//*************************************************************************

#include "J44inchPMTCathodeSD.hh"
#include "J44inchPMT.hh"
#include <math.h>
 
//=====================================================================
//---------------------
// class definition
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J44inchPMTCathodeSD::J44inchPMTCathodeSD(J4VDetectorComponent* detector)
		   :J4VSD<J44inchPMTHit>(detector)
{  
}

//=====================================================================
//* destructor --------------------------------------------------------

J44inchPMTCathodeSD::~J44inchPMTCathodeSD()
{
}

//=====================================================================
//* Initialize --------------------------------------------------------

void J44inchPMTCathodeSD::Initialize(G4HCofThisEvent* HCTE)
{
   //create hit collection(s) and
   //push H.C. to "Hit Collection of This Event"
  
   MakeHitBuf(HCTE);  
}

//=====================================================================
//* ProcessHits -------------------------------------------------------

G4bool J44inchPMTCathodeSD::ProcessHits(G4Step* aStep, G4TouchableHistory* )
{

  std::cerr << "J44inchPMTCathodeSD::ProcessHits: called! " << G4endl;
  
  //In order to use Get function, you must call SetNewStep() at first.
  
  SetNewStep(aStep);
  
  std::cout <<"the step is set as "<<aStep->GetStepLength()<<std::endl;
  
  // If current prestep point is not on the surface of the PMT, return.
  // Note that a geometrical information must be taken from prestep point.
  //in the past the following were turned off. now we try to turn them on again.
  
  G4StepPoint* preStepPoint = GetPreStepPoint();
  G4Track *track = GetTrack();
  
  if ( preStepPoint->GetStepStatus() != fGeomBoundary) {
    std::cerr << "---------------------------------J44inchPMTCathodeSD::ProcessHits: the prestep point must on PMT surface. return " << G4endl; 
    track->SetTrackStatus(fStopAndKill);
    return FALSE;
  }
    
  
  // create a hit... 
  
  G4ThreeVector pre  = GetPrePosition();
  
  //Get local frame position and rotation relative to the global frame 
  G4StepPoint* p1 = aStep->GetPreStepPoint();
  G4ThreeVector coord1 = p1->GetPosition();
  const G4AffineTransform transformation =
    p1->GetTouchable()->
    GetHistory()->GetTopTransform();
  G4ThreeVector localPosition = transformation.TransformPoint(coord1);
  
  
  G4double      ce    = 1.0;

  G4String MyName = GetComponent()->GetName();
  G4int    insideid = GetComponent()->GetMother()->GetMother()->GetMyID();
  G4int    pmtid = GetComponent()->GetMother()->GetMyID();
  
  J44inchPMTHit* hit = new J44inchPMTHit(GetComponent(), pre, ce, insideid, pmtid); 
  ((J44inchPMTHitBuf*)GetHitBuf())->insert(hit);
  
  
  
  //#if 0
  //#if 1
  std::cerr <<"!survived!!!!"<<G4endl;
  std::cerr << "J44inchPMTCathodeSD::ProcessHits:intersection = " << pre.x() << " " << pre.y() << " " << pre.z() << " " << MyName << G4endl;
  std::cerr << "localPosition= " << localPosition.x() << " " << localPosition.y() << " " << localPosition.z() << G4endl;
  
  //#endif
  
  //kill current track...
  
  // G4Track *track = GetTrack();
  track->SetTrackStatus(fStopAndKill);
  // track->SetTrackStatus(fStopButAlive);
  
  return TRUE;
  
}

//=====================================================================
//* EndOfEvent --------------------------------------------------------

void J44inchPMTCathodeSD::EndOfEvent(G4HCofThisEvent* )
{			
  // Create new hits and push them to "Hit Collection"
  
}


//=====================================================================
//* DrawAll -----------------------------------------------------------

void J44inchPMTCathodeSD::DrawAll()
{
}

//=====================================================================
//* PrintAll ----------------------------------------------------------

void J44inchPMTCathodeSD::PrintAll()
{
   G4int nHit = ((J44inchPMTHitBuf*)GetHitBuf())->entries();
   G4cout << "------------------------------------------" << G4endl
          << "*** PMThit (#hits=" << nHit << ")" << G4endl;
   ((J44inchPMTHitBuf*)GetHitBuf())->PrintAllHits();
}

