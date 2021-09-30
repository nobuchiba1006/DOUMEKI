// $Id: J4DOMMaterialStore.cc,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
//********************************************************************
//* ---------------------
//* J4DOMMaterialStore.hh
//* ---------------------
//* (Description)
//* 	The J4DOMMaterialStore provides materials for DOM.
//*     If you cannot find your material in the J4MaterialCatalog,
//*	you can define new material at create() method.
//*     
//* (Update Record)
//*	2000/12/20  K.Hoshina	Original version.
//********************************************************************

#include "J4DOMMaterialStore.hh"
#include "G4Element.hh"
#include "G4Material.hh"

// ====================================================================
// -----------------
// class description
// -----------------


G4Material* J4DOMMaterialStore::Create(const G4String& name, 
                                       G4MaterialPropertiesTable* mtable) 
{  	

  G4Material* material= 0;

  if (name == "BorosilicateGrass") {
  
    //--------------
    // elements...  
    //--------------

    G4double a, z;
    G4String ename, symbol;

    a = 28.0855 *g/mole;
    G4Element* elSi = new G4Element(ename="Silicon", symbol="Si", z=14., a);

    a = 15.9994 *g/mole;
    G4Element* elO = new G4Element(ename="Oxygen", symbol="O", z=8., a);

    a = 10.811 *g/mole;
    G4Element* elB = new G4Element(ename="Boron", symbol="B", z=5., a);
  
    a = 22.9897 *g/mole;
    G4Element* elNa = new G4Element(ename="Sodium", symbol="Na", z=11., a);

    a = 26.9815 *g/mole;
    G4Element* elAl = new G4Element(ename="Aluminum", symbol="Al", z=13., a);

    a = 39.0983 *g/mole;
    G4Element* elK = new G4Element(ename="Potassium", symbol="K", z=19., a);

    a = 55.845 *g/mole;
    G4Element* elFe = new G4Element(ename="Iron", symbol="Fe", z=26., a);

    //--------------
    // materials...
    //--------------

    G4double density, massfraction;
    G4int nel;
    //temperature of experimental hall is controlled at 20 degree.
    const G4double expTemp= STP_Temperature+20.*kelvin; 

    // BorosilicateGrass 
    density = 2.23 * g/cm3 * STP_Temperature/expTemp;
    material = new G4Material(ename="BorosilicateGrass", 
                                          density, nel=5,
                                          kStateSolid, expTemp);
    material-> AddElement(elO,  massfraction = 0.64327);
    material-> AddElement(elSi, massfraction = 0.24678);
    material-> AddElement(elB,  massfraction = 0.07751);
    material-> AddElement(elNa, massfraction = 0.01831);
    material-> AddElement(elAl, massfraction = 0.01404);
  
  }
  
  if (name == "SiliconGel") {
  
    //--------------
    // elements...  
    //--------------

    G4double a, z;
    G4String ename, symbol;

    a = 28.0855 *g/mole;
    G4Element* elSi = new G4Element(ename="Silicon", symbol="Si", z=14., a);

    a = 15.9994 *g/mole;
    G4Element* elO = new G4Element(ename="Oxygen", symbol="O", z=8., a);

    a = 12.011 *g/mole;
    G4Element* elC= new G4Element(ename="Carbon", symbol="C", z=6., a);

    a = 1.00794 *g/mole;
    G4Element* elH= new G4Element(ename="Hydrogen", symbol="H", z=1., a);

    a = 14.00674 *g/mole;
    G4Element* elN= new G4Element(ename="Nitrogen", symbol="N", z=7., a);


    //--------------
    // materials...
    //--------------

    G4double density, massfraction;
    G4int nel, natoms;
    //temperature of experimental hall is controlled at 20 degree.
    const G4double expTemp= STP_Temperature+20.*kelvin; 

    // BorosilicateGrass
    density = 0.98 * g/cm3 * STP_Temperature/expTemp;
    material = new G4Material(ename="SiliconGel", density, nel=4,
                                       kStateSolid, expTemp);
    material-> AddElement(elO, natoms = 2);
    material-> AddElement(elSi, natoms = 2);
    material-> AddElement(elC, natoms = 2);
    material-> AddElement(elH, natoms = 6);
  
  }

  if (!material) {
     G4cerr << "J4DOMMaterialStore::Create: I cannot serve the material " 
            << name << " !" << G4endl;
     G4cerr << "Check your order. abort." << G4endl;
     abort();
  }

  

  if (mtable) material->SetMaterialPropertiesTable(mtable);

  return material;

}


