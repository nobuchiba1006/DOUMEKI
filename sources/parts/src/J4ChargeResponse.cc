// $Id: J4ChargeResponse.cc,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
//*************************************************************************
//* --------------------
//* J4ChargeResponse
//* --------------------
//* (Description)
//*    
//* (Update Record)
//*	2002/12/20  K.Hoshina       Original version.
//*************************************************************************

#include "J4ChargeResponse.hh" 
#include "Randomize.hh"
#include <vector>
#include <algorithm>

//=====================================================================
//---------------------
// class description
//---------------------

J4ChargeResponse::J4ChargeResponse(G4String name, G4double xmin, G4double xmax, std::vector<G4double> params)
   : J4VFunction(name, xmin, xmax, params)
{
#ifdef __THEBE__
     std::cerr << "J4ChargeResponse::constructor is called for " << fName << std::endl;
#endif
}

G4double J4ChargeResponse::Eval(G4double q)
{ 
    G4double alpha = fParams[0];
    G4double tau = fParams[1];
    G4double q0 = fParams[2];
    G4double sigma = fParams[3];

    static const G4double norm = 1./sqrt(2.* M_PI);
    G4double coeff = (q-q0)/sigma;

    return alpha / tau * exp(-q/tau) + (1-alpha) * (norm / sigma) * exp(- coeff*coeff/2.);
}
 
 

