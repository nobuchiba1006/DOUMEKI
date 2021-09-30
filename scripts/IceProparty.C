//
// calculate ice property
//

{

const Double_t kA      = (8.0e+39);
const Double_t kB      = 8100;
const Double_t kBeffAtRefLambda = (1./24);  // m-1, 
const Double_t kCMdust = (158 * kBeffAtRefLambda - 0.634);
const Double_t kKappa  = 1.07;

double wlmin = 270;
double wlmax = 720;
double dwl = 10;

Int_t nent =(int) (wlmax - wlmin) / dwl;
cerr << " nentry = " << nent << endl;

 for (int i = nent-1; i>=0; i-- ) {

   double wavelen = wlmin + i*dwl;
   Double_t energy = 1.24e+3 / wavelen;
   cerr <<"energy " << energy << "*ev, " << endl;


   double wlu = wavelen/1000; // in um
   double index = 1.55749 - 1.57988*wlu
           + 3.99993 *wlu *wlu
           - 4.68271 *wlu *wlu *wlu
           + 2.09354 *wlu *wlu *wlu *wlu;
   cerr <<"index " << index << ", " << endl;

   double absorptioncoeff =  
                kA * TMath::Exp(-0.48175 * wavelen)
              + kB * TMath::Exp(-6700 / wavelen)
              + kCMdust * TMath::Power(wavelen, -kKappa);

   double abslen = 1./absorptioncoeff;
   cerr <<"abslen " << abslen << "*m, " << endl;
 }
}

