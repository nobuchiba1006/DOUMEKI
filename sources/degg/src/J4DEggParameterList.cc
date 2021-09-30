// $Id: J4DEggParameterList.cc,v 1.3 2007/04/02 23:25:33 hoshina Exp $
//*************************************************************************
//* --------------------
//* J4DEggParameterList
//* --------------------
//* (Description)
//* 	Parameter list for module parts
//*
//* (Update Record)
//*	2003/03/18  K.Hoshina	Original version.
//*************************************************************************

#include "J4DEggParameterList.hh"
#include <fstream>

using namespace std;

//GVisAttributes::SetForceAuxEdgeVisible(1);

J4DEggParameterList * J4DEggParameterList::fgInstance = 0;

//=====================================================================
//* public getter -----------------------------------------------------
J4DEggParameterList* J4DEggParameterList::GetInstance()
{
   if (!fgInstance) {
      fgInstance = new J4DEggParameterList("Parts");
   }
   return fgInstance;
}


void J4DEggParameterList::Initialize()
{
   SetParameters();
}

//=====================================================================
//* protected constructor ---------------------------------------------

J4DEggParameterList::J4DEggParameterList(const G4String& name)
                  :J4VParameterList(name)
{
}

//=====================================================================
//* destructor -------------------------------------------------------

J4DEggParameterList::~J4DEggParameterList()
{
   fgInstance = 0;
}

//=====================================================================
//* SetParameters -----------------------------------------------------
void J4DEggParameterList::SetParameters()
{

   fPMTLocation.set(0, 0, 121.0 *mm); 

   fMainBoardRmin = 86.0/2 *mm;
   fMainBoardRmax = 246./2 *mm;
   fMainBoardDz = 1.6/2 *mm;
   fMainBoardLocation.set(0, 0, (55. + 1.6/2) *mm);

   fHVBoardRmin = 0. *mm;
   fHVBoardRmax = 125./2 *mm;
   fHVBoardDz   = 1.6/2 *mm;
   fHVBoardLocation.set(0, 0, (13.4 + 1.6/2) *mm);

   fFlasherRmin = 204./2 *mm;
   fFlasherRmax = 228./2 *mm;
   fFlasherDz = 16./2 *mm;
   fFlasherLocation.set(0, 0, (267. - 15. - 71.5 - 16./2) *mm);

}



