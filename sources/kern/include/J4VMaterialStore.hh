// $Id: J4VMaterialStore.hh,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
#ifndef __J4VMATERIALSTORE__
#define __J4VMATERIALSTORE__
// ====================================================================
//    J4VMaterialStore.hh
//
/// ====================================================================

#include "J4MaterialCatalog.hh"
#include "G4MaterialPropertiesTable.hh"

// ====================================================================
//
// class definition
//
// ====================================================================
 
class J4VMaterialStore {
 
public:
  J4VMaterialStore();   
  virtual ~J4VMaterialStore();

  virtual G4Material* 	Order(const G4String& name,
                              G4MaterialPropertiesTable* mtable=0) ;
   
protected:
  J4MaterialCatalog* 	fMaterialCatalog;
  
private:  
  virtual G4Material* 	Create(const G4String& name,
                               G4MaterialPropertiesTable* mtable=0) ;   
};


#endif
