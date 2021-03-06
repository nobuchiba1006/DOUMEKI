// $Id: J4DOMParameterList.hh,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
#ifndef __J4DOMPARAMETERLIST__hh
#define __J4DOMPARAMETERLIST__hh
//********************************************************************
//* ---------------------
//* J4DOMParameterList.hh
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

// ====================================================================
// ----------------
// class definition
// ----------------
 
class J4DOMParameterList : public J4VParameterList 
{

 protected:  
   J4DOMParameterList(const G4String &name);   

 public:
   virtual ~J4DOMParameterList();  
   
   virtual void PrintParameterList(){}

   void Initialize();
  
   //
   // get parameters
   //

   static J4DOMParameterList *GetInstance(); 

   
   //*DOM ------------------------------------------------------------------------
   inline G4double GetDOMOuterR()             const { return fDOMOuterR;         }
   
   //*Benthos ---------------------------------------------------------------------
   inline G4double GetBenthosOuterR()         const { return fDOMOuterR;         }
   inline G4double GetBenthosThickness()      const { return fBenthosThickness;  }
   inline G4double GetBenthosInnerR()         const; 

   //*Gel -------------------------------------------------------------------------
   inline G4double GetGelR()                  const { return GetBenthosInnerR(); }
   inline G4double GetGelDepth()              const { return fGelDepth;          }
   inline G4double GetGelMinThickness()       const { return fGelMinThickness;   } 
   inline G4double GetGelDTheta()             const; 

   //*PMT -------------------------------------------------------------------------
   inline G4ThreeVector GetPMTLocation()      const { return fPMTLocation;       }

   //*PhotoCathode ----------------------------------------------------------------
   inline G4double GetPhotoCathodeR()         const { return fPhotoCathodeR;     }
   inline G4double GetPhotoCathodeDepth()     const { return fPhotoCathodeDepth; }
   inline G4double GetPhotoCathodeDTheta()    const;

   //*MainBoard -------------------------------------------------------------------
   inline G4ThreeVector GetMainBoardLocation()const { return fMainBoardLocation; }
                 
   //*materials -----------------------------------------------------------------
   inline G4String GetHarnessMaterial()       const { return fHarnessMaterial;   }
   inline G4String GetDOMMaterial()           const { return fDOMMaterial;       }
   inline G4String GetBenthosMaterial()       const { return fBenthosMaterial;   }
   inline G4String GetInsideMaterial()        const { return fInsideMaterial;    }
   inline G4String GetGelMaterial()           const { return fGelMaterial;       }
   inline G4String GetPMTMaterial()           const { return fPMTMaterial;       }
   inline G4String GetPhotoCathodeMaterial()  const { return fPhotoCathodeMaterial; }
   inline G4String GetMainBoardMaterial()     const { return fMainBoardMaterial; }

   //*properties -----------------------------------------------------------------
   inline G4MaterialPropertiesTable* GetBenthosPropTable() const { return fBenthosPropTable; }
   inline G4MaterialPropertiesTable* GetInsidePropTable()  const { return fInsidePropTable; }
   inline G4MaterialPropertiesTable* GetGelPropTable()     const { return fGelPropTable; }
   inline G4MaterialPropertiesTable* GetPMTPropTable()     const { return fPMTPropTable; }
   inline G4MaterialPropertiesTable* GetBenthosSurfaceTable() const { return fBenthosSurfaceTable; }
   inline G4MaterialPropertiesTable* GetInsideSurfaceTable()  const { return fInsideSurfaceTable; }
   inline G4MaterialPropertiesTable* GetGelSurfaceTable()     const { return fGelSurfaceTable; }
   inline G4MaterialPropertiesTable* GetPMTSurfaceTable()     const { return fPMTSurfaceTable; }

   //*VisAttributes -------------------------------------------------------------
   inline G4bool   GetHarnessVisAtt()         const { return fHarnessVisAtt;     }
   inline G4bool   GetDOMVisAtt()             const { return fDOMVisAtt;         }
   inline G4bool   GetBenthosVisAtt()         const { return fBenthosVisAtt;     }
   inline G4bool   GetInsideVisAtt()          const { return fInsideVisAtt;      }
   inline G4bool   GetGelVisAtt()             const { return fGelVisAtt;         }
   inline G4bool   GetPMTVisAtt()             const { return fPMTVisAtt;         }
   inline G4bool   GetPhotoCathodeVisAtt()    const { return fPhotoCathodeVisAtt;}
   inline G4bool   GetMainBoardVisAtt()       const { return fMainBoardVisAtt;   }
   
   //*Color ---------------------------------------------------------------------
   inline G4Color  GetHarnessColor()          const { return fHarnessColor;      }
   inline G4Color  GetDOMColor()              const { return fDOMColor;          }
   inline G4Color  GetBenthosColor()          const { return fBenthosColor;      }
   inline G4Color  GetInsideColor()           const { return fInsideColor;       }
   inline G4Color  GetGelColor()              const { return fGelColor;          }
   inline G4Color  GetPMTColor()              const { return fPMTColor;          }
   inline G4Color  GetPhotoCathodeColor()     const { return fPhotoCathodeColor; }
   inline G4Color  GetMainBoardColor()        const { return fMainBoardColor;    }
  
   //
   // setters  
   //
   
   //*DOM ------------------------------------------------------------------------
   inline void SetDOMOuterR(G4double x)             { fDOMOuterR = x;           }

   //*Benthos ---------------------------------------------------------------------
   inline void SetBenthosThickness(G4double x)      { fBenthosThickness = x;    }

   //*Benthos ---------------------------------------------------------------------
   inline void SetGelDepth(G4double x)              { fGelDepth = x;            }
    
   //*materials -----------------------------------------------------------------
   inline void SetDOMMaterial(const G4String &name)     { fDOMMaterial = name;     }
   inline void SetBenthosMaterial(const G4String &name) { fBenthosMaterial = name; }
   inline void SetInsideMaterial(const G4String &name)  { fInsideMaterial = name;  }
   inline void SetGelMaterial(const G4String &name)     { fGelMaterial = name;     }
   inline void SetPMTMaterial(const G4String &name)     { fPMTMaterial = name;     }

   //*VisAttributes -------------------------------------------------------------
   inline void SetHarnessVisAtt(G4bool x)           { fHarnessVisAtt = x;      }
   inline void SetDOMVisAtt(G4bool x)               { fDOMVisAtt = x;          }
   inline void SetBenthosVisAtt(G4bool x)           { fBenthosVisAtt = x;      }
   inline void SetInsideVisAtt(G4bool x)            { fInsideVisAtt = x;       }
   inline void SetGelVisAtt(G4bool x)               { fGelVisAtt = x;          }
   inline void SetPMTVisAtt(G4bool x)               { fPMTVisAtt = x;          }
   inline void SetMainBoardVisAtt(G4bool x)         { fMainBoardVisAtt = x;    }
   
   //*Color ---------------------------------------------------------------------
   inline void SetHarnessColor(const G4Color &c)    { fHarnessColor = c;       }
   inline void SetDOMColor(const G4Color &c)        { fDOMColor = c;           }
   inline void SetBenthosColor(const G4Color &c)    { fBenthosColor = c;       }
   inline void SetInsideColor(const G4Color &c)     { fInsideColor = c;        }
   inline void SetGelColor(const G4Color &c)        { fGelColor = c;           }
   inline void SetPMTColor(const G4Color &c)        { fPMTColor = c;           }
   inline void SetPhotoCathodeColor(const G4Color &c){ fPhotoCathodeColor = c;  }
   inline void SetMainBoardColor(const G4Color &c)  { fMainBoardColor = c;  }

 private:
    virtual void  SetMaterials();
    virtual void  SetVisAttributes();
    virtual void  SetColors();
    virtual void  SetParameters();
 
 private:

   static J4DOMParameterList *fgInstance;
   
   // material
   G4String  fHarnessMaterial;
   G4String  fDOMMaterial;
   G4String  fBenthosMaterial;
   G4String  fInsideMaterial;
   G4String  fGelMaterial;
   G4String  fPMTMaterial;
   G4String  fPhotoCathodeMaterial;
   G4String  fMainBoardMaterial;

   G4MaterialPropertiesTable* fBenthosPropTable;
   G4MaterialPropertiesTable* fInsidePropTable;
   G4MaterialPropertiesTable* fGelPropTable;
   G4MaterialPropertiesTable* fPMTPropTable;

   G4MaterialPropertiesTable* fBenthosSurfaceTable;
   G4MaterialPropertiesTable* fInsideSurfaceTable;
   G4MaterialPropertiesTable* fGelSurfaceTable;
   G4MaterialPropertiesTable* fPMTSurfaceTable;
  
   // VisAttributes
   G4bool    fHarnessVisAtt;
   G4bool    fDOMVisAtt;
   G4bool    fBenthosVisAtt;
   G4bool    fInsideVisAtt;
   G4bool    fGelVisAtt;
   G4bool    fPMTVisAtt;
   G4bool    fPhotoCathodeVisAtt;
   G4bool    fMainBoardVisAtt;
   
   // Color
   G4Color   fHarnessColor;
   G4Color   fDOMColor;
   G4Color   fBenthosColor;
   G4Color   fInsideColor;
   G4Color   fGelColor;
   G4Color   fPMTColor;
   G4Color   fPhotoCathodeColor;
   G4Color   fMainBoardColor;
   
   // DOM
   G4double  fDOMOuterR;
  
   // Benthos
   G4double  fBenthosThickness; 
   
   //Gel   
   G4double  fGelDepth; 
   G4double  fGelMinThickness; 

   // PMT 
   G4ThreeVector fPMTLocation;

   // PhotoCathode 
   G4double  fPhotoCathodeR;
   G4double  fPhotoCathodeDepth; 

   // MainBoard
   G4ThreeVector fMainBoardLocation;

};

//=========================================================
//* inline functions

G4double J4DOMParameterList::GetBenthosInnerR() const
{
   return GetDOMOuterR() - fBenthosThickness;
} 

G4double J4DOMParameterList::GetGelDTheta() const
{
   G4double costheta = (GetGelR() - fGelDepth) / GetGelR();
   return acos(costheta);
} 

G4double J4DOMParameterList::GetPhotoCathodeDTheta() const
{
   G4double costheta = (fPhotoCathodeR - fPhotoCathodeDepth) / fPhotoCathodeR;
   return acos(costheta);
} 


#endif
