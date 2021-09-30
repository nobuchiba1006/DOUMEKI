// $Id: J4DEggParameterList.hh,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
#ifndef __J4DEggParameterList__hh
#define __J4DEggParameterList__hh
//********************************************************************
//* ---------------------
//* J4DEggParameterList.hh
//* ---------------------
//* (Description)
//* 	ParameterList class for optical module parts
//*     The instance must be singleton. Use "GetInstance()" function
//*     to create/get the instance.
//*     
//* (Update Record)
//*	2003/09/27  K.Hoshina	Original version.
//********************************************************************

#include "G4Material.hh"
#include "G4ThreeVector.hh"
#include "J4ParameterList.hh"
#include "G4MaterialPropertiesTable.hh"
#include "G4VisAttributes.hh"
#include "G4Color.hh"

// ====================================================================
// ----------------
// class definition
// ----------------
 
class J4DEggParameterList : public J4VParameterList 
{

 protected:  
   J4DEggParameterList(const G4String &name);   

 public:
   virtual ~J4DEggParameterList();  
   
   virtual void Initialize();

   virtual void PrintParameterList(){}

 public:
  
   //
   // get parameters
   //

   static J4DEggParameterList *GetInstance(); 
   inline const G4ThreeVector &GetPMTLocation() const       { return fPMTLocation;       }
   inline const G4ThreeVector &GetMainBoardLocation() const { return fMainBoardLocation; }
   inline const G4ThreeVector &GetHVBoardLocation() const   { return fHVBoardLocation;   }
   inline const G4ThreeVector &GetFlasherLocation() const   { return fFlasherLocation; }
   inline G4double             GetMainBoardRmin() const     { return fMainBoardRmin;     }
   inline G4double             GetMainBoardRmax() const     { return fMainBoardRmax;     }
   inline G4double             GetMainBoardDz()   const     { return fMainBoardDz;       }
   inline G4double             GetHVBoardRmin() const       { return fHVBoardRmin;       }
   inline G4double             GetHVBoardRmax() const       { return fHVBoardRmax;       }
   inline G4double             GetHVBoardDz()   const       { return fHVBoardDz;         }
   inline G4double             GetFlasherRmin() const       { return fFlasherRmin;     }
   inline G4double             GetFlasherRmax() const       { return fFlasherRmax;     }
   inline G4double             GetFlasherDz()   const       { return fFlasherDz;       }

   //
   // setters  
   //

   inline void SetPMTLocation(const G4ThreeVector & v)       { fPMTLocation = v;       }
   inline void SetMainBoardLocation(const G4ThreeVector & v) { fMainBoardLocation = v; }
   inline void SetHVBoardLocation(const G4ThreeVector & v)   { fHVBoardLocation = v;   }
   inline void SetFlasherLocation(const G4ThreeVector & v)   { fFlasherLocation = v; }
   inline void SetMainBoardRmin(G4double v)                  { fMainBoardRmin = v;     }
   inline void SetMainBoardRmax(G4double v)                  { fMainBoardRmax = v;     }
   inline void SetMainBoardDz(G4double v)                    { fMainBoardDz= v;        }
   inline void SetHVBoardRmin(G4double v)                    { fHVBoardRmin = v;       }
   inline void SetHVBoardRmax(G4double v)                    { fHVBoardRmax = v;       }
   inline void SetHVBoardDz(G4double v)                      { fHVBoardDz= v;          }
   inline void SetFlasherRmin(G4double v)                    { fFlasherRmin = v;     }
   inline void SetFlasherRmax(G4double v)                    { fFlasherRmax = v;     }
   inline void SetFlasherDz(G4double v)                      { fFlasherDz= v;        }

 private:

   virtual void  SetParameters();

   static J4DEggParameterList * fgInstance;

   G4ThreeVector fPMTLocation;
   G4ThreeVector fMainBoardLocation;
   G4ThreeVector fHVBoardLocation;
   G4ThreeVector fFlasherLocation;

   G4double fMainBoardRmin;
   G4double fMainBoardRmax;
   G4double fMainBoardDz;

   G4double fHVBoardRmin;
   G4double fHVBoardRmax;
   G4double fHVBoardDz;

   G4double fFlasherRmin;
   G4double fFlasherRmax;
   G4double fFlasherDz;
 
};

#endif
