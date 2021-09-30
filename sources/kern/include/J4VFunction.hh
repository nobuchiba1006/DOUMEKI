// $Id: J4VFunction.hh,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
#ifndef __J4VFunction__
#define __J4VFunction__
//*************************************************************************
//* -----------------------
//* J4VFunction
//* -----------------------
//* (Description)
//* 	Base class for all 1 parameter function
//*     
//* (Update Record)
//*	2021/09/02  K.Hoshina	Original version.
//*************************************************************************

//these three classes are required to make include of G4Integrator success... 
#include "G4ExceptionSeverity.hh"
#include "G4Types.hh"
#include "globals.hh"

#include "G4Integrator.hh"
#include <vector>

//=====================================================================
//---------------------
// class definition
//---------------------

class J4VFunction 
{

public:

  J4VFunction(G4String name, G4double xmin, G4double xmax, std::vector<G4double> params = std::vector<G4double>());

  virtual ~J4VFunction()
  {
#ifdef __THEBE__
     std::cerr << "J4VFunction::destructor is called for " << fName << std::endl;
#endif
  }

  //
  // virtual function. Override it!
  //
  virtual G4double Eval(G4double v) = 0; 

  G4String GetName()  { return fName;} 

  //
  // Get random x that follows function Eval
  //
  G4double GetRandom(G4String opt = "lin");
  G4double GetRandom(G4double xmin, G4double xmax, G4String opt = "lin");

  //
  // Calculate Cdf Table
  //
  G4bool ComputeCdfTable(G4String opt = "lin");


  virtual void SetParams(std::vector<double> p) 
  {
     fParams = p;
     fRedoComputeCdf = true;
  }

  //
  // integrants
  //
  G4double SimpsonIntegral(G4double lowerlimit, G4double upperlimit, G4int niter=100)
  {
      G4Integrator<J4VFunction, G4double(J4VFunction::*)(G4double)> integral;
      G4double result = integral.Simpson(this, &J4VFunction::Eval, lowerlimit, upperlimit, niter);
      return result;
  }

  G4double Legendre10Integral(G4double lowerlimit, G4double upperlimit)
  {
      G4Integrator<J4VFunction, G4double(J4VFunction::*)(G4double)> integral;
      G4double result = integral.Legendre10(this, &J4VFunction::Eval, lowerlimit, upperlimit);
      return result;
  }

  G4double Legendre96Integral(G4double lowerlimit, G4double upperlimit)
  {
      G4Integrator<J4VFunction, G4double(J4VFunction::*)(G4double)> integral;
      G4double result = integral.Legendre96(this, &J4VFunction::Eval, lowerlimit, upperlimit);
      return result;
  }

  G4double Integral(G4double lowerlimit = -1, G4double upperlimit = -1)
  {
      double xmin = lowerlimit;
      double xmax = upperlimit;
      if (lowerlimit == upperlimit && lowerlimit == -1) {
          xmin = fXmin;
          xmax = fXmax;
      }
      return Legendre10Integral(xmin, xmax);
  }

protected:

  G4String fName;
  G4double fXmin;
  G4double fXmax;
  G4int    fNpx;
  G4String fOpt;
  G4bool   fRedoComputeCdf;

  std::vector<double> fParams;
  std::vector<double> fIntegral;
  std::vector<double> fAlpha;
  std::vector<double> fBeta;
  std::vector<double> fGamma;

};

#endif

