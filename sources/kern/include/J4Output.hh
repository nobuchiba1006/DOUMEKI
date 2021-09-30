// $Id: J4Output.hh,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
#ifndef __J4OUTPUT__
#define __J4OUTPUT__
//*************************************************************************
//* --------------------
//* J4Output
//* --------------------
//* (Description)
//* 	Output Hit data
//*     
//* (Update Record)
//*	2002/08/07  Akiya Miyamoto  Original Version
//*	
//*************************************************************************

#include "J4VHit.hh"

//=========================================================================
//---------------------
// Class definition
//---------------------

class J4Output
{
public:
  J4Output() {}
  virtual ~J4Output() {}
  
  virtual void Output(J4VHit *) {}
  virtual void Clear() {}

};

#endif

