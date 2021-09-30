// $Id: J4VDOMDetectorComponent.cc,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
//*************************************************************************
//* -----------------------
//* J4VDOMDetectorComponent
//* -----------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VDOMDetectorComponent.hh"


J4DOMMaterialStore* J4VDOMDetectorComponent::fMaterialStore = 0;

G4String J4VDOMDetectorComponent::fSubGroup("DOM");

//=====================================================================
//---------------------
// class 
//---------------------

//=====================================================================
//* default constructor -----------------------------------------------

J4VDOMDetectorComponent::J4VDOMDetectorComponent(
			   	const G4String       &name, 
  			   	J4VDetectorComponent *parent,
                                G4int                 nclones,
                                G4int                 nbrothers, 
                                G4int                 me,
                                G4int                 copyno ) :
                         J4VDetectorComponent(fSubGroup, name, 
                         		      parent, nclones,	 
                         		      nbrothers, me, copyno)   
{ 
}


//=====================================================================
//* destructor --------------------------------------------------------

J4VDOMDetectorComponent::~J4VDOMDetectorComponent()
{	
   if (Deregister(fMaterialStore)) delete fMaterialStore;
}

//=====================================================================
//* OpenMaterialStore -------------------------------------------------

J4VMaterialStore* J4VDOMDetectorComponent::OpenMaterialStore()
{
   if (!fMaterialStore) {
      fMaterialStore = new J4DOMMaterialStore();
      Register(fMaterialStore); 
      std::cerr << "*** Opend J4DOMMaterialStore ***" << std::endl;
   }
    
   return fMaterialStore;
}


