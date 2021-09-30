// $Id: J4MEggParameterList.hh,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
#ifndef __J4MEggParameterList__hh
#define __J4MEggParameterList__hh
//********************************************************************
//* ---------------------
//* J4MEggParameterList.hh
//* ---------------------
//* (Description)
//* 	ParameterList class for Drift Chamber.
//*     The instance must be singleton. Use "GetInstance()" function
//*     to create/get the instance.
//*     
//* (Update Record)
//*	2003/09/27  K.Hoshina	Original version.
//********************************************************************

#include "G4Material.hh"
#include "G4Color.hh"
#include "G4ThreeVector.hh"
#include "J4ParameterList.hh"
#include "G4MaterialPropertiesTable.hh"
#include "G4VisAttributes.hh"
#include "G4RotationMatrix.hh"
#include "G4ThreeVector.hh"

// ====================================================================
// ----------------
// class definition
// ----------------
 
class J4MEggParameterList : public J4VParameterList 
{

 protected:  
   J4MEggParameterList(const G4String &name);   

 public:
   virtual ~J4MEggParameterList();  
   
   virtual void Initialize();

   virtual void PrintParameterList(){}
  
   //
   // get parameters
   //

   static J4MEggParameterList *GetInstance(); 
   typedef std::pair<G4RotationMatrix *, G4ThreeVector>  PMTPlacement;

   inline const G4ThreeVector &GetMainBoardLocation() const { return fMainBoardLocation; }
   inline const G4ThreeVector &GetHVBoardLocation() const   { return fHVBoardLocation;   }
   inline G4double             GetMainBoardRmin() const     { return fMainBoardRmin;     }
   inline G4double             GetMainBoardRmax() const     { return fMainBoardRmax;     }
   inline G4double             GetMainBoardDz()   const     { return fMainBoardDz;       }
   inline G4double             GetHVBoardRmin() const       { return fHVBoardRmin;       }
   inline G4double             GetHVBoardRmax() const       { return fHVBoardRmax;       }
   inline G4double             GetHVBoardDz()   const       { return fHVBoardDz;         }

   PMTPlacement CalcUpperPMTPlacement(G4int momid, G4int myid);

   //
   // setters  
   //

   inline void SetPMTLocation(const G4ThreeVector & v)       { fPMTLocation = v;       }
   inline void SetMainBoardLocation(const G4ThreeVector & v) { fMainBoardLocation = v; }
   inline void SetHVBoardLocation(const G4ThreeVector & v)   { fHVBoardLocation = v;   }
   inline void SetMainBoardRmin(G4double v)                  { fMainBoardRmin = v;     }
   inline void SetMainBoardRmax(G4double v)                  { fMainBoardRmax = v;     }
   inline void SetMainBoardDz(G4double v)                    { fMainBoardDz= v;        }
   inline void SetHVBoardRmin(G4double v)                    { fHVBoardRmin = v;       }
   inline void SetHVBoardRmax(G4double v)                    { fHVBoardRmax = v;       }
   inline void SetHVBoardDz(G4double v)                      { fHVBoardDz= v;          }
   
 private:
    virtual void  SetParameters();
 
 private:

   static J4MEggParameterList *fgInstance;

   G4ThreeVector fPMTLocation;
   G4ThreeVector fMainBoardLocation;
   G4ThreeVector fHVBoardLocation;

   G4double fMainBoardRmin;
   G4double fMainBoardRmax;
   G4double fMainBoardDz;

   G4double fHVBoardRmin;
   G4double fHVBoardRmax;
   G4double fHVBoardDz;

};

//=========================================================
//* inline functions

#endif
