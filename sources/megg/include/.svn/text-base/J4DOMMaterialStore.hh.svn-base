// $Id: J4DOMMaterialStore.hh,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
#ifndef __J4DOMMATERIALSTORE__hh
#define __J4DOMMATERIALSTORE__hh
//********************************************************************
//* ---------------------
//* J4DOMMaterialStore.hh
//* ---------------------
//* (Description)
//* 	Material Store class for Drift Chamber.
//*     Order(material_name) function returns material object
//*     defined in kern/include/J4MaterialCatalog or this class.
//*     Note that the Order function looks J4MaterialCatalog at first
//*     so that your materials which have same name as default materials
//*     written in J4MaterialCatalog are ignored.
//*     
//* (Update Record)
//*	2003/09/27  K.Hoshina	Original version.
//********************************************************************

#include "J4VMaterialStore.hh"

// ====================================================================
// ----------------
// class definition
// ----------------
 
class J4DOMMaterialStore : public J4VMaterialStore {
 
public:
  J4DOMMaterialStore() {};   
  ~J4DOMMaterialStore(){};  
    
private:
  
  G4Material* Create(const G4String& name,
                     G4MaterialPropertiesTable* mtable=0) ; //Define User Materials
  
};


#endif
