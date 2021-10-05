// $Id: J43inchPMTSD.cc,v 1.2 2007/03/13 17:29:14 hoshina Exp $
//*************************************************************************
//* --------------------
//* J43inchPMTSD
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

#include "J43inchPMTSD.hh"
#include "J43inchPMT.hh"
#include <math.h>
 
//=====================================================================
//---------------------
// class definition
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J43inchPMTSD::J43inchPMTSD(J4VDetectorComponent* detector)
		   :J4VSD<J43inchPMTHit>(detector)
{  
}

//=====================================================================
//* destructor --------------------------------------------------------

J43inchPMTSD::~J43inchPMTSD()
{
}

//=====================================================================
//* Initialize --------------------------------------------------------

void J43inchPMTSD::Initialize(G4HCofThisEvent* HCTE)
{
   //create hit collection(s) and
   //push H.C. to "Hit Collection of This Event"
  
   MakeHitBuf(HCTE);  
}

//=====================================================================
//* ProcessHits -------------------------------------------------------

G4bool J43inchPMTSD::ProcessHits(G4Step* aStep, G4TouchableHistory* )
{

  std::cerr << "J43inchPMTSD::ProcessHits: called! " << G4endl;
  
  //In order to use Get function, you must call SetNewStep() at first.
  
  SetNewStep(aStep);
  
  std::cout <<"the step is set as "<<aStep->GetStepLength()<<std::endl;
  
  // If current prestep point is not on the surface of the PMT, return.
  // Note that a geometrical information must be taken from prestep point.
  //in the past the following were turned off. now we try to turn them on again.
  
  G4StepPoint* preStepPoint = GetPreStepPoint();
  G4Track *track = GetTrack();
  
  if ( preStepPoint->GetStepStatus() != fGeomBoundary) {
    std::cerr << "---------------------------------J43inchPMTSD::ProcessHits: the prestep point must on PMT surface. return " << G4endl; 
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
  
  // <<<<<<<<<<< TMP_TREATMENT!!! <<<<<<<<<<<<<<
  
  G4double from0tocathode = 78.11-49.5 *mm;       
  //  track->SetTrackStatus(fStopAndKill);

  
  if ( localPosition.z() < from0tocathode ) {
    //Check the global coordinate
    std::cerr << "J43inchPMTSD::ProcessHits:intersection = " << pre.x() << " " << pre.y()	<< " " << pre.z() << G4endl;
    /*
    //Check the local coordinate
    std::cerr << "Local position = " << localPosition.x() << " " << localPosition.y() << " " << localPosition.z() << G4endl; 
    */
    std::cerr << "J43inchPMTSD::ProcessHits: the photon hits backside! return " << G4endl; 
    std::cerr<<"!!!!!!!!!!attention returnning false!!!!!!!!!!!"<<G4endl;
    track->SetTrackStatus(fStopAndKill);
    return FALSE;
  } 
  
  // <<<<<<<<<<< TMP_TREATMENT!!! <<<<<<<<<<<<<<
  
  G4double      ce    = 1.0;

  G4String MyName = GetComponent()->GetName();
  G4int    insideid = GetComponent()->GetMother()->GetMyID();
  G4int    pmtid = GetComponent()->GetMyID();
  
  G4ThreeVector mom = aStep->GetTrack()->GetMomentum().unit();
  G4ThreeVector org(0,0,0);
  G4ThreeVector local_pos = transformation.TransformPoint(coord1);
  G4ThreeVector local_mom = transformation.TransformPoint(mom);
  G4ThreeVector local_org = transformation.TransformPoint(org);
  G4ThreeVector local_dir = (local_mom-local_org).unit();

  G4double      energy = GetTotalEnergy();
  G4double      tof    = GetTof();
  
  J43inchPMTHit* hit = new J43inchPMTHit(GetComponent(), pre, local_pos, local_dir, ce, insideid, pmtid); 
  ((J43inchPMTHitBuf*)GetHitBuf())->insert(hit);
  
  
  
  
  //#if 0
  //#if 1
  std::cerr <<"!survived!!!!"<<G4endl;
  std::cerr << "J43inchPMTSD::ProcessHits:intersection = " << pre.x() << " " << pre.y() << " " << pre.z() << " " << MyName << G4endl;
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

void J43inchPMTSD::EndOfEvent(G4HCofThisEvent* )
{			
  // Create new hits and push them to "Hit Collection"
  
}


//=====================================================================
//* DrawAll -----------------------------------------------------------

void J43inchPMTSD::DrawAll()
{
}

//=====================================================================
//* PrintAll ----------------------------------------------------------

void J43inchPMTSD::PrintAll()
{
   G4int nHit = ((J43inchPMTHitBuf*)GetHitBuf())->entries();
   G4cout << "------------------------------------------" << G4endl
          << "*** PMThit (#hits=" << nHit << ")" << G4endl;
   ((J43inchPMTHitBuf*)GetHitBuf())->PrintAllHits();
}

