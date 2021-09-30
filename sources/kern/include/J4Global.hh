// $Id: J4Global.hh,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
#ifndef __J4GLOBAL__
#define __J4GLOBAL__
//*************************************************************************
//* -----------------------
//* J4Global
//* -----------------------
//* (Description)
//* 	 
//*     
//* (Update Record)
//*	2001/03/27  K.Hoshina	Original version.
//*************************************************************************

#include <fstream>
#include "G4ios.hh"
#include "G4String.hh"

// ====================================================================
// global valiables

#ifdef __THEBE__
#define J4cerr J4Global::GetErrorOutputStream()
#define J4endl std::endl; if (J4Global::GetErrorOutputDeviceID()) J4cerr<<std::flush
#else 
#define J4cerr std::cerr
#define J4endl std::endl
#endif

// ====================================================================
class J4GlobalMessenger;
class J4Global 
{
public:

  J4Global();
  virtual ~J4Global();
  
  static J4Global*        GetGlobal()               { return fGlobal;      }    
  
  static std::ostream&  GetErrorOutputStream();
  static std::ostream&  GetEndl(std::ostream& outs);
  static G4int            GetErrorCounter()        { return fErrorCounter; }
  static G4int            GetErrorNevents()        { return fErrorNevents; }
  static G4int            GetErrorOutputDeviceID() { return fErrorOutputDeviceID; }
  static G4String         GetErrorOutputFilename() { return fErrorOutputFilename; }
  static G4String         GetErrorOutputUnit()     { return fErrorOutputUnit; }
       
  static void             SetErrorOutputStream(std::ofstream& ofs) 
                                                   { fErrorOfs = &ofs;     }
  static void             SetErrorNevents(G4int n) { fErrorNevents = n;    }
  static void             SetErrorOutputDeviceID(G4int i)
                                                   { fErrorOutputDeviceID = i; }
  static void             SetErrorOutputFilename(G4String fname)
                                                   { fErrorOutputFilename = fname; }
  static void             SetErrorOutputUnit(G4String ounit)
                                                   { fErrorOutputUnit = ounit; }
  void                    CloseErrorOutputStream();
  
private:
  static J4Global          *fGlobal;
  static std::ofstream   *fErrorOfs;
  static G4int              fErrorCounter;
  static G4int              fErrorNevents;
  static G4int              fErrorOutputDeviceID;   // 0: std::cerr, 1:fileoutput
  static G4String           fErrorOutputFilename;
  static G4String           fErrorOutputUnit;       // "Run", "Event", "Track"  
  J4GlobalMessenger        *fMessenger;
};

#endif
