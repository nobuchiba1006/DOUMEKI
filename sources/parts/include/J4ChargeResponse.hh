// $Id: J4ChargeResponse.hh,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
#ifndef __J4ChargeResponse__
#define __J4ChargeResponse__
//*************************************************************************
//* -----------------------
//* J4ChargeResponse
//* -----------------------
//* (Description)
//* 	Base class for all 1 parameter function
//*     
//* (Update Record)
//*	2021/09/02  K.Hoshina	Original version.
//*************************************************************************

//these three classes are required to make include of G4Integrator success... 
#include "J4VFunction.hh"
#include <vector>

//=====================================================================
//---------------------
// class definition
//---------------------

class J4ChargeResponse : public J4VFunction
{

public:

  J4ChargeResponse(G4String name, G4double xmin, G4double xmax, std::vector<G4double> params = std::vector<G4double>());

  virtual ~J4ChargeResponse()
  {
  }

  //
  // virtual function. Override it!
  //
  virtual G4double Eval(G4double v);


};

#endif

