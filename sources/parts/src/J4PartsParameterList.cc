// $Id: J4PartsParameterList.cc,v 1.3 2007/04/02 23:25:33 hoshina Exp $
//*************************************************************************
//* --------------------
//* J4PartsParameterList
//* --------------------
//* (Description)
//* 	Parameter list for module parts
//*
//* (Update Record)
//*	2003/03/18  K.Hoshina	Original version.
//*************************************************************************

#include "J4PartsParameterList.hh"
#include <fstream>

using namespace std;

//GVisAttributes::SetForceAuxEdgeVisible(1);

J4PartsParameterList * J4PartsParameterList::fgInstance = 0;

//=====================================================================
//* public getter -----------------------------------------------------
J4PartsParameterList* J4PartsParameterList::GetInstance()
{
   if (!fgInstance) {
      fgInstance = new J4PartsParameterList("Parts");
   }
   return fgInstance;
}


void J4PartsParameterList::Initialize()
{
   SetMaterials();
   SetParameters();
   SetVisAttributes();
   SetColors();
}

//=====================================================================
//* protected constructor ---------------------------------------------

J4PartsParameterList::J4PartsParameterList(const G4String& name)
                  :J4VParameterList(name)
{
   // set default setting. If you want to change it,
   // use set method before you call Initialize.
   fMatpropHoleiceFilename = "tables/holeice/matprop_holeice_0.95_2.0cm.dat";
   f8inchPMTCETableName = "tables/average_12PMT8inch_CE_theta.dat";
}

//=====================================================================
//* destructor -------------------------------------------------------

J4PartsParameterList::~J4PartsParameterList()
{
   fgInstance = 0;
}

//=====================================================================
//* SetMaterials ------------------------------------------------------
void J4PartsParameterList::SetMaterials()
{
   fMaterials.clear();
#if 1
   fMaterials["DOM"] = "Ice";
   fMaterials["Egg"] = "Ice";
   fMaterials["LOM"] = "Ice";
   fMaterials["Glass"] = "BorosilicateGlass";
   fMaterials["OkamotoGlass"] = "BorosilicateGlass";
   fMaterials["Inside"] = "Air";
   fMaterials["Gel"] = "SiliconGel";
   fMaterials["PMT"] = "BorosilicateGlass";
   fMaterials["PMTBase"] = "Aluminum";
   fMaterials["Cathode"] = "BorosilicateGlass";
   fMaterials["ElectricBoard"] = "Silicon";
   fMaterials["Shield"] = "Iron";
   fMaterials["Flasher"] = "Silicon";
   fMaterials["Harness"] = "Aluminum";
   fMaterials["Bubble"] = "Air";

   fMaterials["BubbleColumn"] = "BubbleColumn";
   //fMaterials["BubbleColumn"] = "Ice";

#else
   fMaterials["DOM"] = "Ice";
   fMaterials["Egg"] = "Ice";
   fMaterials["OkamotoGlass"] = "Ice";
   fMaterials["Inside"] = "Ice";
   fMaterials["Gel"] = "Ice";
   fMaterials["PMT"] = "Ice";
   fMaterials["ElectricBoard"] = "Ice";
   fMaterials["Shield"] = "Ice";
   fMaterials["Flasher"] = "Ice";
   fMaterials["Harness"] = "Ice";
   fMaterials["Bubble"] = "Ice";
#endif

   //
   // MaterialPropatiesTable
   // 

   std::cerr << "***************************************************" << G4endl;
   std::cerr << "J4PartsParameterList::GenerateMaterialPropertiesTable" << G4endl;
   std::cerr << "***************************************************" << G4endl;

   fPropertiesTables.clear();
   G4double lambda, ene, rindex, penetration, abslen;

   // for Air --------------

   const G4int nair = 2;
   G4double photonEair[nair] = {2.0*eV, 6.2*eV};
   G4double rindexair[nair] = {1.0, 1.0};
   
   G4MaterialPropertiesTable *airprop = new G4MaterialPropertiesTable();
   airprop->AddProperty("RINDEX", photonEair, rindexair, nair);
   fPropertiesTables["Air"] = airprop;


   // for aluminum --------------

   const G4int nal = 2;
   G4double photonEal[nal] = {2.0*eV, 6.2*eV};
   G4double reflectivity[] = {1., 1.};
   G4double efficiency[] = {0.0, 0.0};
   
   G4MaterialPropertiesTable* alprop = new G4MaterialPropertiesTable();
      
   alprop->AddProperty("REFLECTIVITY",photonEal,reflectivity,nal);
   alprop->AddProperty("EFFICIENCY",photonEal,efficiency,nal);
   fPropertiesTables["Aluminum"] = alprop;

   
   //  --------------for icecube ice --------------
   
   const G4int nice = 45;
   // 270nm to 720 nm, every 10 nm
   G4double photonE[nice] =   
         { 1.73*eV, 1.77143*eV, 1.7971*eV, 1.82353*eV, 1.85075*eV,
           1.87879*eV, 1.90769*eV, 1.9375*eV, 1.96825*eV, 2*eV,
           2.03279*eV, 2.06667*eV, 2.10169*eV, 2.13793*eV, 2.17544*eV,
           2.21429*eV, 2.25455*eV, 2.2963*eV, 2.33962*eV, 2.38462*eV,
           2.43137*eV, 2.48*eV, 2.53061*eV, 2.58333*eV, 2.6383*eV,
           2.69565*eV, 2.75556*eV, 2.81818*eV, 2.88372*eV, 2.95238*eV,
           3.02439*eV, 3.1*eV, 3.17949*eV, 3.26316*eV, 3.35135*eV,
           3.44444*eV, 3.54286*eV, 3.64706*eV, 3.75758*eV, 3.875*eV,
           4*eV, 4.13333*eV, 4.27586*eV, 4.42857*eV, 4.59259*eV };

   // phase index, icecube ice
   G4double icerindex[nice] = 
         { 1.30815, 1.30803, 1.30797, 1.30797, 1.30802,
           1.30812, 1.30826, 1.30843, 1.30863, 1.30887,
           1.30912, 1.30939, 1.30969, 1.31, 1.31032,
           1.31067, 1.31102, 1.31139, 1.31178, 1.31218,
           1.3126, 1.31304, 1.3135, 1.314, 1.31452,
           1.31507, 1.31567, 1.31631, 1.31699, 1.31774,
           1.31855, 1.31943, 1.32039, 1.32143, 1.32257,
           1.32381, 1.32517, 1.32665, 1.32827, 1.33003,
           1.33195, 1.33404, 1.33632, 1.33879, 1.34147 };

   // icecube ice, homogeneous ice model
   G4double iceabslen[nice] =  
         { 1.53548*m, 1.75477*m, 2.01271*m, 2.31728*m, 2.67831*m,
           3.10791*m, 3.62113*m, 4.23659*m, 4.97741*m, 5.87229*m,
           6.95675*m, 8.2746*m, 9.87943*m, 11.836*m, 14.2211*m,
           17.1234*m, 20.6402*m, 24.8713*m, 29.9055*m, 35.8002*m,
           42.5523*m, 50.0649*m, 58.1194*m, 66.3693*m, 74.3702*m,
           81.65*m, 87.8004*m, 92.5553*m, 95.8262*m, 97.6856*m,
           98.3168*m, 97.9538*m, 96.8329*m, 95.1628*m, 93.1123*m,
           90.8086*m, 88.3431*m, 85.7786*m, 83.1565*m, 80.5033*m,
	   77.8352*m, 75.162*m, 72.4893*m, 69.8202*m, 67.1563*m };

   G4MaterialPropertiesTable *iceprop = new G4MaterialPropertiesTable();
   iceprop->AddProperty("RINDEX", photonE, icerindex, nice);
   iceprop->AddProperty("ABSLENGTH", photonE, iceabslen, nice);

   // icecube ice, homogeneous ice model
   G4double mieice[nice] ;

   // dummy mie scattering length
   for (int i=0; i<nice; ++i) {
       mieice[i] = DBL_MAX;
   }
   /*
   G4double mie_water_const[3]={0.99,0.99,0.8};
   iceprop->AddProperty("MIEHG",photonE,mieice,nice)->SetSpline(true);
   iceprop->AddConstProperty("MIEHG_FORWARD",mie_water_const[0]);
   iceprop->AddConstProperty("MIEHG_BACKWARD",mie_water_const[1]);
   iceprop->AddConstProperty("MIEHG_FORWARD_RATIO",mie_water_const[2]);
   */

   fPropertiesTables["Ice"] = iceprop;


   //  --------------for borosilicate glass --------------
   
   ifstream in;
   in.open("tables/matprop_glass_DEgg.dat", std::ios::in);
   if (! in.good()) {
       G4String errorMessage=
          "*** RunAction::BeginOfRunAtcion(): fail to open a file (matprop_glass_DEgg.dat)."; 
       G4Exception(errorMessage, "FATAL", FatalException, "");
   }

   std::vector<G4double> eglassvec;
   std::vector<G4double> indexglassvec;
   std::vector<G4double> abslenglassvec;

   G4String dum;
   in >> dum;   // omit comment line
   while (in >> lambda >> ene >> rindex >> penetration >> abslen) {
      eglassvec.push_back(ene);
      indexglassvec.push_back(rindex);
      abslenglassvec.push_back(abslen);
      //std::cerr << ene << " " << rindex << " " 
      //       << abslen << G4endl;
   }

   in.close();
   in.clear();

   G4int nindex = eglassvec.size();
   G4double *photonEglass = new G4double [nindex];
   G4double *rindexglass  = new G4double [nindex];
   G4double *abslenglass  = new G4double [nindex];
   G4double *mieglass     = new G4double [nindex];

   for (G4int i=0; i<nindex; i++) {
      photonEglass[i] = eglassvec[i] * eV;
      rindexglass[i]  = indexglassvec[i];
      abslenglass[i]  = abslenglassvec[i] * cm;
      //std::cerr << photonEglass[i] << " " << rindexglass[i] << " " 
      //       << abslenglass[i] << G4endl;
   }


   G4MaterialPropertiesTable *glassprop = new G4MaterialPropertiesTable();
   glassprop->AddProperty("RINDEX", photonEglass, rindexglass, nindex);
   glassprop->AddProperty("ABSLENGTH", photonEglass, abslenglass, nindex);

   // dummy mie scattering length
   for (int i=0; i<nice; ++i) {
       mieglass[i] = DBL_MAX;
   }

   /*
   glassprop->AddProperty("MIEHG",photonEglass,mieglass,nindex)->SetSpline(true);
   glassprop->AddConstProperty("MIEHG_FORWARD",mie_water_const[0]);
   glassprop->AddConstProperty("MIEHG_BACKWARD",mie_water_const[1]);
   glassprop->AddConstProperty("MIEHG_FORWARD_RATIO",mie_water_const[2]);
   */

   fPropertiesTables["BorosilicateGlass"] = glassprop;
   
   
   //  --------------for gel --------------

   in.open("tables/matprop_gel_DEgg.dat", std::ios::in);
   if (! in.good()) {
       G4String errorMessage=
          "*** RunAction::BeginOfRunAtcion(): fail to open a file (matprop_gel_DEgg.dat)."; 
       G4Exception(errorMessage, "FATAL", FatalException, "");
   }

   std::vector<G4double> egelvec;
   std::vector<G4double> indexgelvec;
   std::vector<G4double> abslengelvec;

   in >> dum;   // omit comment line
   while (in >> lambda >> ene >> rindex >> penetration >> abslen) {
      egelvec.push_back(ene);
      indexgelvec.push_back(rindex);
      abslengelvec.push_back(abslen);
   }

   in.close();
   in.clear();

   nindex = egelvec.size();
   G4double *photonEgel = new G4double [nindex];
   G4double *rindexgel  = new G4double [nindex];
   G4double *abslengel  = new G4double [nindex];
   G4double *miegel     = new G4double [nindex];

   for (G4int i=0; i<nindex; i++) {
      photonEgel[i] = egelvec[i] * eV;
      rindexgel[i]  = indexgelvec[i];
      abslengel[i]  = abslengelvec[i] * cm;
   }

   G4MaterialPropertiesTable *gelprop = new G4MaterialPropertiesTable();
   gelprop->AddProperty("RINDEX", photonEgel, rindexgel, nindex);
   gelprop->AddProperty("ABSLENGTH", photonEgel, abslengel, nindex);

   // icecube ice, homogeneous ice model

   // dummy mie scattering length
   for (int i=0; i<nice; ++i) {
       miegel[i] = DBL_MAX;
   }
   /*
   gelprop->AddProperty("MIEHG",photonEgel,miegel,nindex)->SetSpline(true);
   gelprop->AddConstProperty("MIEHG_FORWARD",mie_water_const[0]);
   gelprop->AddConstProperty("MIEHG_BACKWARD",mie_water_const[1]);
   gelprop->AddConstProperty("MIEHG_FORWARD_RATIO",mie_water_const[2]);
   */
   fPropertiesTables["SiliconGel"] = gelprop;


   // for HoleIce --------------

   in.open(fMatpropHoleiceFilename.c_str(), std::ios::in);
   if (! in.good()) {
       G4String errorMessage=
          "*** RunAction::BeginOfRunAtcion(): fail to open a file (" + fMatpropHoleiceFilename + ")";
       G4Exception(errorMessage, "FATAL", FatalException, "");
   }

   std::vector<G4double> eholeicevec;
   std::vector<G4double> indexholeicevec;
   std::vector<G4double> abslenholeicevec;
   std::vector<G4double> mieforwardvec;
   std::vector<G4double> miebackwardvec;
   std::vector<G4double> mieratiovec;
   std::vector<G4double> miescatlenvec;

   std::cout << "read holeice table " << fMatpropHoleiceFilename << std::endl;

   G4double forward, backward, ratio, scatlen;
   std::getline(in, dum);   // omit comment line
   std::cout << dum << std::endl;
   while (in >> lambda >> ene >> rindex >> abslen >> forward >> backward >> ratio >> scatlen) {
      eholeicevec.push_back(ene);
      indexholeicevec.push_back(rindex);
      abslenholeicevec.push_back(abslen);
      mieforwardvec.push_back(forward);
      miebackwardvec.push_back(backward);
      mieratiovec.push_back(ratio);
      miescatlenvec.push_back(scatlen);

      /*
      std::cout << ene << " " << rindex << " "
             << abslen << " " << forward << " "
             << backward << " " << ratio << " "
             << scatlen << G4endl;
      */
   }

   in.close();
   in.clear();

   const G4int nEntries = 45;

   nindex = eholeicevec.size();
   G4double *photonEholeice = new G4double [nindex];
   G4double *rindexholeice  = new G4double [nindex];
   G4double *abslenholeice  = new G4double [nindex];
   G4double *mieforward     = new G4double [nindex];
   G4double *miebackward    = new G4double [nindex];
   G4double *mieratio       = new G4double [nindex];
   G4double *miescatlen     = new G4double [nindex];

   for (G4int i=0; i<nindex; i++) {
      photonEholeice[i] = eholeicevec[i] * eV;
      rindexholeice[i]  = indexholeicevec[i];
      abslenholeice[i]  = abslenholeicevec[i] * m;
      mieforward[i]     = mieforwardvec[i];
      miebackward[i]    = miebackwardvec[i];
      mieratio[i]       = mieratiovec[i];
      miescatlen[i]     = miescatlenvec[i] * cm;
      std::cout << photonEholeice[i]/eV << "[eV] " << rindexholeice[i] << " "
             << abslenholeice[i] << " " << mieforward[i] << " "
             << miebackward[i] << " " << mieratio[i] << " "
             << miescatlen[i]/cm << "[cm]" << G4endl;
   }

   G4MaterialPropertiesTable *bubbleprop = new G4MaterialPropertiesTable();
   //bubbleprop->AddProperty("RINDEX",       photonEholeice, rindexholeice, nindex);
   //bubbleprop->AddProperty("ABSLENGTH",    photonEholeice, abslenholeice, nindex);
   bubbleprop->AddProperty("RINDEX",       photonE, icerindex, nindex);
   bubbleprop->AddProperty("ABSLENGTH",    photonE, iceabslen, nindex);
   bubbleprop->AddProperty("MIEHG",    photonEholeice, miescatlen, nindex)->SetSpline(true);
   bubbleprop->AddConstProperty("MIEHG_FORWARD", mieforward[0]);
   bubbleprop->AddConstProperty("MIEHG_BACKWARD", miebackward[0]);
   bubbleprop->AddConstProperty("MIEHG_FORWARD_RATIO", mieratio[0]);
   fPropertiesTables["BubbleColumn"] = bubbleprop;
}
   
//=====================================================================
//* SetParameters -----------------------------------------------------
void J4PartsParameterList::SetParameters()
{
   fBubbleColumnRadius = 5*cm;   
}

//=====================================================================
//* SetVisAttributes --------------------------------------------------
void J4PartsParameterList::SetVisAttributes()
{

   fVisAtts["DOM"] = 0;
   fVisAtts["Egg"] = 1;
   fVisAtts["LOM"] = 1;
   fVisAtts["Glass"] = 0;
   fVisAtts["OkamotoGlass"] = 1;
   fVisAtts["Inside"] = 0;
   fVisAtts["Gel"] = 1;
   fVisAtts["PMT"] = 0;
   fVisAtts["PMTBase"] = 1;
   fVisAtts["Cathode"] = 1;
   fVisAtts["ElectricBoard"] = 1;
   fVisAtts["Shield"] = 1;
   fVisAtts["Flasher"] = 1;
   fVisAtts["Harness"] = 1;
   fVisAtts["Bubble"] = 1;
   fVisAtts["BubbleColumn"] = 1;
}

//=====================================================================
//* SetColors ---------------------------------------------------------
void J4PartsParameterList::SetColors()
{
  fColors["DOM"] = G4Color(0.5, 0.5, 0.5, 0.3);
  fColors["Egg"] = G4Color(0.5, 0.5, 0.5, 0.3);
  fColors["LOM"] = G4Color(0.5, 0.5, 0.5, 0.3);
  fColors["Glass"] = G4Color(0., 0.8, 1., 0.1);
  fColors["OkamotoGlass"] = G4Color(0., 0.8, 1., 0.1);
  fColors["Inside"] = G4Color(1, 0, 1, 0.8);
  fColors["Gel"] = G4Color(1., 0.8, 0, 0.5); 
  fColors["PMT"] = G4Color(1, 0, 1, 1); 
  fColors["PMTBase"] = G4Color(1, 0, 1, 1); 
  fColors["Cathode"] = G4Color(1, 1, 1, 1); 
  fColors["ElectricBoard"] = G4Color(1., 1., 1., 0.7);
  fColors["Shield"] = G4Color(1., 1., 0., 0.5);
  fColors["Flasher"] = G4Color(0.5, 0.5, 0.5, 1.);
  fColors["Harness"] = G4Color(0.5, 0.5, 0.5, 1.);
  fColors["Bubble"] = G4Color(0.5, 0.5, 0.5, 0.8);
  fColors["BubbleColumn"] = G4Color(0.5, 0.5, 0.5, 0.8);

}


