// $Id: J4VFunction.cc,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
//*************************************************************************
//* --------------------
//* J4VFunction
//* --------------------
//* (Description)
//*    
//* (Update Record)
//*	2002/12/20  K.Hoshina       Original version.
//*************************************************************************

#include "J4VFunction.hh" 
#include "Randomize.hh"
#include <vector>
#include <algorithm>

//=====================================================================
//---------------------
// class description
//---------------------

J4VFunction::J4VFunction(G4String name, G4double xmin, G4double xmax, std::vector<G4double> params)
   : fName(name), fXmin(xmin), fXmax(xmax), fParams(params)
{
#ifdef __THEBE__
     std::cerr << "J4VFunction::constructor is called for " << fName << std::endl;
#endif

   // default npx
   fNpx = 100;
   fOpt = "lin"; // linear integration
   fRedoComputeCdf = true;
}

G4bool J4VFunction::ComputeCdfTable(G4String opt)
{ 
   fIntegral.resize(fNpx + 1);
   fAlpha.resize(fNpx + 1);
   fBeta.resize(fNpx);
   fGamma.resize(fNpx);
   fIntegral[0] = 0;
   fAlpha[fNpx] = 0;
   G4double integ;
   G4int intNegative = 0;
   G4int i;
   G4bool logbin = false;
   G4double dx;
   G4double xmin = fXmin;
   G4double xmax = fXmax;
   // perform a log binning if specified by user (option="Log") or if some conditions are met
   // and the user explicitly does not specify a Linear binning option
   if ((opt == "log") || (xmin > 0 && xmax / xmin > fNpx)) {
      logbin = true;
      fAlpha[fNpx] = 1;
      xmin = log10(fXmin);
      xmax = log10(fXmax);
   }
   dx = (xmax - xmin) / fNpx;

   std::vector<double> xx(fNpx + 1);
   for (i = 0; i < fNpx; i++) {
      xx[i] = xmin + i * dx;
   }
   xx[fNpx] = xmax;
   for (i = 0; i < fNpx; i++) {
      if (logbin) {
         integ = Integral(pow(10, xx[i]), pow(10, xx[i + 1]));
      } else {
         integ = Integral(xx[i], xx[i + 1]);
      }
      if (integ < 0) {
         intNegative++;
         integ = -integ;
      }
      fIntegral[i + 1] = fIntegral[i] + integ;
   }
   if (intNegative > 0) {
      std::cerr << "GetRandom:function: "<< GetName() << " has "<< intNegative << " negative values: abs assumed" << std::endl;
   }
   if (fIntegral[fNpx] == 0) {
      std::cerr << "GetRandom:Integral of function is zero" << std::endl;;
      return false;
   }
   G4double total = fIntegral[fNpx];
   for (i = 1; i <= fNpx; i++) { // normalize integral to 1
      fIntegral[i] /= total;
   }

   // the integral r for each bin is approximated by a parabola
   //  x = alpha + beta*r +gamma*r**2
   // compute the coefficients alpha, beta, gamma for each bin
   G4double x0, r1, r2, r3;
   for (i = 0; i < fNpx; i++) {
      x0 = xx[i];
      r2 = fIntegral[i + 1] - fIntegral[i];
      if (logbin)
         r1 = Integral(pow(10, x0), pow(10, x0 + 0.5 * dx)) / total;
      else
         r1 = Integral(x0, x0 + 0.5 * dx) / total;
      r3 = 2 * r2 - 4 * r1;
      if (fabs(r3) > 1e-8)
         fGamma[i] = r3 / (dx * dx);
      else
         fGamma[i] = 0;
      fBeta[i] = r2 / dx - fGamma[i] * dx;
      fAlpha[i] = x0;
      fGamma[i] *= 2;
   }
   fOpt = opt;
   fRedoComputeCdf = false;
   return true;
}
 
G4double J4VFunction::GetRandom(G4String opt)
{
   //  Check if integral array must be built
   if (fIntegral.size() == 0 || fOpt != opt || fRedoComputeCdf) {
      bool ret = ComputeCdfTable(opt);
   }
 
   // return random number
   G4double r = CLHEP::RandFlat::shoot(0., 1.);
   std::vector<double>::iterator iter_lower = lower_bound(fIntegral.begin(), fIntegral.end(), r); 
   long bin = distance(fIntegral.begin(), iter_lower);
   G4double rr = r - fIntegral[bin];
 
   G4double yy;
   if (fGamma[bin] != 0)
      yy = (-fBeta[bin] + sqrt(fBeta[bin] * fBeta[bin] + 2 * fGamma[bin] * rr)) / fGamma[bin];
   else
      yy = rr / fBeta[bin];
   G4double x = fAlpha[bin] + yy;
   if (fAlpha[fNpx] > 0) return pow(10, x);
   return x;
}

 
G4double J4VFunction::GetRandom(double xmin, double xmax, G4String opt)
{
   //  Check if integral array must be built
   if (fIntegral.size() == 0 || fOpt != opt || fRedoComputeCdf) {
      bool ret = ComputeCdfTable(opt);
   }
 
   // return random number
   G4double dx   = (fXmax - fXmin) / fNpx;
   G4int nbinmin = (G4int)((xmin - fXmin) / dx);
   G4int nbinmax = (G4int)((xmax - fXmin) / dx) + 2;
   if (nbinmax > fNpx) nbinmax = fNpx;
 
   G4double pmin = fIntegral[nbinmin];
   G4double pmax = fIntegral[nbinmax];
 
   G4double r, x, xx, rr;

   do {
      G4double r = CLHEP::RandFlat::shoot(pmin, pmax);
      std::vector<double>::iterator iter_lower = lower_bound(fIntegral.begin(), fIntegral.end(), r); 
      long bin = distance(fIntegral.begin(), iter_lower);
      rr = r - fIntegral[bin];
 
      if (fGamma[bin] != 0)
         xx = (-fBeta[bin] + sqrt(fBeta[bin] * fBeta[bin] + 2 * fGamma[bin] * rr)) / fGamma[bin];
      else
         xx = rr / fBeta[bin];
      x = fAlpha[bin] + xx;
   } while (x < xmin || x > xmax);
   return x;
}
 
 

