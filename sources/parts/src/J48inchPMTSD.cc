// $Id: J48inchPMTSD.cc,v 1.2 2007/03/13 17:29:14 hoshina Exp $
//*************************************************************************
//* --------------------
//* J48inchPMTSD
//* --------------------
//* (Description)
//* 	Class for describing his/her sensitive detector.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*     090315. important change!!!! attention!!! the photoncathode area changes!!!
//*     2020/09/03 M.Suzuki Change the definition of the photocathode area
//*     Change PMT grobal frame position to the local frame position
//*     2021/07/01 K.Hoshina renamed from J4DEggPMTSD
//*************************************************************************

#include "J48inchPMTSD.hh"
#include "J48inchPMT.hh"
#include "J4PartsParameterList.hh"
#include <math.h>
#include <map>
 
//=====================================================================
//---------------------
// class definition
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J48inchPMTSD::J48inchPMTSD(J4VDetectorComponent* detector)
		   :J4VSD<J48inchPMTHit>(detector)
{  
   std::cout << "initializing J48inchPMTSD" << std::endl;
   std::cout << "load table" << std::endl;
   LoadCETable_1D();
   std::cout << "table loaded" << std::endl;

   // dummy function!
   std::vector<double> param1;
   param1.resize(4);
   param1[0] = 0.3; // alpha
   param1[1] = 0.5; // tau for exponential part
   param1[2] = 1.0; // q0 for gaussian part
   param1[3] = 0.3; // sigma for gaussian part
   fChargeResponse1 = new J4ChargeResponse("cr1", 0, 3., param1);
   std::cout << "charge response 1 loaded" << std::endl;

   std::vector<double> param2;
   param2.resize(4);
   param2[0] = 0.4; // alpha
   param2[1] = 0.5; // tau for exponential part
   param2[2] = 0.8; // q0 for gaussian part
   param2[3] = 0.4; // sigma for gaussian part
   fChargeResponse2 = new J4ChargeResponse("cr2", 0, 3., param2);
   std::cout << "charge response 2 loaded" << std::endl;

}

//=====================================================================
//* destructor --------------------------------------------------------

J48inchPMTSD::~J48inchPMTSD()
{
}

//=====================================================================
//* Initialize --------------------------------------------------------

void J48inchPMTSD::Initialize(G4HCofThisEvent* HCTE)
{
   //create hit collection(s) and
   //push H.C. to "Hit Collection of This Event"

 
   MakeHitBuf(HCTE);  
}

//=====================================================================
//* loadtable --------------------------------------------------------

void J48inchPMTSD::LoadCETable_1D()
{
   J4PartsParameterList * list = J4PartsParameterList::GetInstance();
   G4String cetable = list->Get8inchPMTCETableName();
   std::ifstream in;
   in.open(cetable, std::ios::in);
   if (! in.good()) {
       G4String errorMessage=
          "*** fail to open a file (average_12PMT_CE_theta.dat).";
       G4Exception(errorMessage, "FATAL", FatalException, "");
   }

   G4double zen, ce;
   while (in >> zen >> ce) {
      fCE1D[zen] = ce;
   }
   in.close();
   in.clear();
}

//=====================================================================
//* get QE 1dim ----------------------------------------------------
G4double J48inchPMTSD::GetCE_1D(G4double zendeg)
{
   std::map<G4double, G4double>::iterator it, itup;
   it = fCE1D.lower_bound(zendeg);
   if (it == fCE1D.end()) {
       // out of table. return 0.
       std::cout << "zendeg " << zendeg << " is out of boundary" << std::endl;
       return 0;
   }

   itup = it++;
   G4double zenlow = it->first;
   G4double celow = it->second;
   G4double zenhi = itup->first;
   G4double cehi = itup->second;
   // linear interpolation
   G4double ce = (cehi - celow)/(zenhi-zenlow)*(zendeg - zenlow) + celow;
   std::cout << "zendeg " << zendeg << " ce " << ce << std::endl;
   return ce;
}

//=====================================================================
//* get QE 1dim ----------------------------------------------------
G4double J48inchPMTSD::GetCharge(G4double zendeg)
{
   // first trial!
   return 1.;

   double q;
   if (zendeg < 50.0) {
      q = fChargeResponse1->GetRandom(0.2, 3.0);
   } else {
      q = fChargeResponse2->GetRandom(0.2, 3.0);
   }
   return q;
}

//=====================================================================
//* ProcessHits -------------------------------------------------------

G4bool J48inchPMTSD::ProcessHits(G4Step* aStep, G4TouchableHistory* )
{

  std::cout << "J48inchPMTSD::ProcessHits: called! " << std::endl;
  
  //In order to use Get function, you must call SetNewStep() at first.
  
  SetNewStep(aStep);
  
  std::cout <<"the step is set as "<<aStep->GetStepLength()<<std::endl;
  
  // If current prestep point is not on the surface of the PMT, return.
  // Note that a geometrical information must be taken from prestep point.
  //in the past the following were turned off. now we try to turn them on again.
  
  G4StepPoint* preStepPoint = GetPreStepPoint();
  G4Track *track = GetTrack();
  
  if ( preStepPoint->GetStepStatus() != fGeomBoundary) {
    std::cerr << "---------------------------------J48inchPMTSD::ProcessHits: the prestep point must on PMT surface. return " << G4endl; 
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

  G4double local_theta_deg = (localPosition.theta())/deg;
  std::cout << "J48inchPMTSD::ProcessHits:intersection = " << pre.x() << " " << pre.y()	<< " " << pre.z() << std::endl;
  std::cout << "Local position = " << localPosition.x() << " " << localPosition.y() << " " << localPosition.z() << std::endl; 
  G4double ce = GetCE_1D(local_theta_deg);
  ce *= GetCharge(local_theta_deg);
  
  //if ( localPosition.z() < from0tocathode ) {
  if ( ce <= 0 ) {
    //Check the global coordinate
    //Check the local coordinate
    std::cout << "J48inchPMTSD::ProcessHits: the photon hits backside! return " << std::endl; 
    std::cout <<"!!!!!!!!!!attention returnning false!!!!!!!!!!!"<<std::endl;
    track->SetTrackStatus(fStopAndKill);
    return FALSE;
  } 
  
  // <<<<<<<<<<< TMP_TREATMENT!!! <<<<<<<<<<<<<<
  
  
  J48inchPMTHit* hit = new J48inchPMTHit(GetComponent(), pre, ce); 
  ((J48inchPMTHitBuf*)GetHitBuf())->insert(hit);
  
  G4String MyName = GetComponent()->GetName();
  
//#if 0
#if 1
  std::cout <<"!survived!!!!"<< std::endl;
  std::cout << "J48inchPMTSD::ProcessHits:intersection = " << pre.x() << " " << pre.y() << " " << pre.z() << " " << MyName << G4endl;
  std::cout << "localPosition= " << localPosition.x() << " " << localPosition.y() << " " << localPosition.z() << G4endl;
#endif
  
  //kill current track...
  
  track->SetTrackStatus(fStopAndKill);
  // track->SetTrackStatus(fStopButAlive);
  
  return TRUE;
  
}

//=====================================================================
//* EndOfEvent --------------------------------------------------------

void J48inchPMTSD::EndOfEvent(G4HCofThisEvent* )
{			
  // Create new hits and push them to "Hit Collection"
  
}


//=====================================================================
//* DrawAll -----------------------------------------------------------

void J48inchPMTSD::DrawAll()
{
}

//=====================================================================
//* PrintAll ----------------------------------------------------------

void J48inchPMTSD::PrintAll()
{
   G4int nHit = ((J48inchPMTHitBuf*)GetHitBuf())->entries();
   G4cout << "------------------------------------------" << G4endl
          << "*** PMThit (#hits=" << nHit << ")" << G4endl;
   ((J48inchPMTHitBuf*)GetHitBuf())->PrintAllHits();
}

