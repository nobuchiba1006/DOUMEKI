// $Id: J4DEggParameterList.hh,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
#ifndef __J4PartsPARAMETERLIST__hh
#define __J4PartsPARAMETERLIST__hh
//********************************************************************
//* ---------------------
//* J4PartsParameterList.hh
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
 
class J4PartsParameterList : public J4VParameterList 
{

 protected:  
   J4PartsParameterList(const G4String &name);   

 public:
   virtual ~J4PartsParameterList();  
   
   virtual void Initialize();

   virtual void PrintParameterList(){}

   // they are replaced to G4String
   //enum PartsNames {DOM, DEgg, Glass, OkamotoGlass, Inside, Gel, PMT, ElectricBoard, Shield, Flasher, Harness, Bubble};
   //enum MaterialNames {Air, Ice, BorosilicateGlass, SiliconGel, Silicon, Iron, Aluminum};

 private:

   static J4PartsParameterList *fgInstance;
   /*
   std::map<PartsNames, MaterialNames> fMaterials;
   std::map<MaterialNames, G4MaterialPropertiesTable*> fPropertiesTables;
   std::map<PartsNames, G4bool> fVisAtts;
   std::map<PartsNames, G4Color> fColors;
   */
   std::map<G4String, G4String> fMaterials;
   std::map<G4String, G4MaterialPropertiesTable*> fPropertiesTables;
   std::map<G4String, G4bool> fVisAtts;
   std::map<G4String, G4Color> fColors;


 public:
  
   //
   // get parameters
   //

   static J4PartsParameterList *GetInstance(); 

   inline G4String GetMaterial(const G4String &n)  { return fMaterials[n];     } 

   inline G4MaterialPropertiesTable * GetPropertiesTable(const G4String &n) { return fPropertiesTables[GetMaterial(n)]; }

   inline G4bool   GetVisAtt(const G4String &n) { return fVisAtts[n];     }

   inline G4Color  GetColor(const G4String &n)  { return fColors[n];      }

   inline G4String GetHoleiceFilename()    { return fMatpropHoleiceFilename; }
   inline G4double GetBubbleColumnRadius() { return fBubbleColumnRadius; }
   inline G4String Get8inchPMTCETableName() { return f8inchPMTCETableName; }


   //
   // setters  
   //

   inline void SetMaterial(const G4String & pn, const G4String &mn) { fMaterials[pn] = mn;    }
   inline void SetVisAttributes(const G4String &pn, G4bool x)    { fVisAtts[pn] = x;      }
   inline void SetColor(const G4String &pn, const G4Color &c)    { fColors[pn] = c;       }

   inline void SeHoleiceFilename(const G4String &n)         { fMatpropHoleiceFilename = n; }
   inline void SetMatpropHoleiceFilename(const G4String &n) { fMatpropHoleiceFilename = n; }
   inline void SetBubbleColumnRadius(G4double x)            { fBubbleColumnRadius = x; }

   inline void Set8inchPMTCETableName(G4double x)           { f8inchPMTCETableName = x; }

 private:
    virtual void  SetMaterials();
    virtual void  SetParameters();
    virtual void  SetVisAttributes();
    virtual void  SetColors();

    G4String fMatpropHoleiceFilename;
    G4double fBubbleColumnRadius;
    G4String f8inchPMTCETableName;
 
};

//=========================================================
//* inline functions

#endif
