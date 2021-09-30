// $Id: J4ParameterListStore.cc,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
//*************************************************************************
//* --------------------
//* J4ParameterListStore
//* --------------------
//* (Description)
//*
//* (Update Record)
//*	2002/12/20  K.Hoshina	Original version.
//*************************************************************************

#include "G4ExceptionHandler.hh"
#include "J4ParameterListStore.hh"
#include "J4VParameterList.hh"
 
#define __NMAXPARAMLISTS__  1000

J4ParameterListStore* J4ParameterListStore::fgParameterListStore = 0;
J4ObjArray J4ParameterListStore::fgParameterLists(__NMAXPARAMLISTS__);

//=====================================================================
//* constructor -------------------------------------------------------

J4ParameterListStore::J4ParameterListStore()
{

   if (fgParameterListStore) {
      G4Exception("J4ParameterListStore constructed twice.", 
                  "warning", JustWarning, ""); 
   }  
   fgParameterListStore = this;

}

//=====================================================================
//* destructor --------------------------------------------------------

J4ParameterListStore::~J4ParameterListStore()
{
}


//=====================================================================
//* PrintAllParameters ------------------------------------------------

void J4ParameterListStore::PrintAllParameters()
{

}

//=====================================================================
//* Initialize --------------------------------------------------------

void J4ParameterListStore::Initialize()
{
   for (G4int i=0; i<fgParameterLists.entries(); ++i) {
       ((J4VParameterList*)fgParameterLists[i])->Initialize();
   }
}

