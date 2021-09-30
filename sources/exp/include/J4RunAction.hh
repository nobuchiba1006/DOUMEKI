// $Id: J4RunAction.hh,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
// ====================================================================
//    J4RunAction.hh
//
//    A user's optional action class which defines the user's action 
//    at the begining and the end of each run. 
//
//    The user can override the following two methods;
//      virtual void BeginOfRunAction(const G4Run* aRun);
//      virtual void EndOfRunAction(const G4Run* aRun);
//
//    This class must be set to G4RunManager via 
//    G4RunManager::SetUserAction() method.
//
//                                   .JLC-CDC, 2001
// ====================================================================
#ifndef J4_RUN_ACTION_H
#define J4_RUN_ACTION_H

#include <fstream>
#include "G4UserRunAction.hh"
#include "J4VHit.hh"

// ====================================================================
//
//      class definition
//
// ====================================================================

class G4Run;
class J4RunActionMessenger;

class J4RunAction : public G4UserRunAction {

 public:

   J4RunAction(const G4String& fname="hit.dat");
   ~J4RunAction() { }

   virtual void   BeginOfRunAction(const G4Run* aRun);
   virtual void   EndOfRunAction(const G4Run* aRun);
   G4String       GetFileOpenMode() const                  { return fFileOpenMode; }
   G4String       GetHeaderString() const                  { return fHeaderString; }
   G4String       GetHitFileName() const                   { return fHitFileName; }
   std::ofstream& GetOutputFileStream()                    { return fOfs; }
   G4int          GetRunNumber() const                     { return fRunNumber; }
   void           SetFileOpenMode(const G4String &mo = "recreate") { fFileOpenMode = mo; } 
   void           SetHeaderString(const G4String &st)       { fHeaderString= st; } 
   void           AddHeaderString(const G4String &st)       { fHeaderString += st; } 
   void           SetHitFileName(const G4String& fname)    { fHitFileName = fname; }
   void           SetRunNumber(G4int n)                    { fRunNumber = n; }

 private:

   G4String        fHitFileName;
   G4String        fFileOpenMode;
   G4String        fHeaderString;
   G4int           fRunNumber;
   std::ofstream   fOfs; 

   J4RunActionMessenger * fMessenger;

};

#endif
