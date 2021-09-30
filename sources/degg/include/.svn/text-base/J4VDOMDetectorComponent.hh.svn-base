// $Id: J4VDOMDetectorComponent.hh,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
#ifndef __J4VDOMDETECTORCOMPONENT__hh
#define __J4VDOMDETECTORCOMPONENT__hh
//*************************************************************************
//* -----------------------
//* J4VDOMDetectorComponent
//* -----------------------
//* (Description)
//* 	Base class for describing detector compornents.
//*     
//* (Update Record)
//*	2003/09/27  K.Hoshina	Original version.
//*************************************************************************

#include "J4DOMMaterialStore.hh"
#include "J4DOMParameterList.hh"
#include "J4VDetectorComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4VDOMDetectorComponent : public J4VDetectorComponent
{	// abstruct class

public:
  //default constructor...
  J4VDOMDetectorComponent( const G4String       &name, 
  			  J4VDetectorComponent *parent    = 0,
                          G4int                 nclones   = 1,
                          G4int                 nbrothers = 1, 
                          G4int                 me        = 0,
                          G4int                 copyno    = -1 );

  //copy constructor...
  inline J4VDOMDetectorComponent(const J4VDOMDetectorComponent& right,
                                      G4int                   copyno);

  //destructor...
  virtual ~J4VDOMDetectorComponent();
      
protected:    
  J4VMaterialStore*  OpenMaterialStore();
  J4DOMParameterList* OpenParameterList() 
                     { return J4DOMParameterList::GetInstance(); }
  
private:
  static J4DOMMaterialStore* fMaterialStore;
  static G4String           fSubGroup;
       
};

//=====================================================================
//---------------------
// inline function
//---------------------

J4VDOMDetectorComponent::J4VDOMDetectorComponent(const J4VDOMDetectorComponent& right,
                                                     G4int                   copyno)
                       : J4VDetectorComponent(right, copyno)
{
}

#endif


