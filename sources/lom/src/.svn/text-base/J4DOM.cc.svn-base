// $Id: J4DOM.cc,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
//*************************************************************************
//* --------------------
//* J4DOM
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4DOM.hh"
#include "J4DOMParameterList.hh"
#include "G4Sphere.hh"
#include "G4Box.hh"

#include "J4DOMPMT.hh"
#include "J4DOMPMTSD.hh"



// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4DOM::fFirstName("DOM");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4DOM::J4DOM(J4VDetectorComponent *parent,
                          G4int  nclones,
                          G4int  nbrothers, 
                          G4int  me,
                          G4int  copyno ) :
      J4VDOMDetectorComponent( fFirstName, parent, nclones,
                              nbrothers, me, copyno ) 
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4DOM::~J4DOM()
{
  if(Deregister(fBenthos)) delete fBenthos;
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4DOM::Assemble() 
{   
  if(!GetLV()){
  	
    J4DOMParameterList *list = OpenParameterList(); 
    G4double rmin   = 0;
    G4double rmax   = list->GetDOMOuterR(); 
    G4double sphi   = 0. *deg;
    G4double dphi   = 2*M_PI;
    G4double stheta = 0. *deg;
    G4double dtheta = M_PI;
  	
    // MakeSolid ----------//
    G4Sphere *solid = new G4Sphere (GetName(),
                                   rmin, rmax,
                                   sphi, dphi,
                                   stheta, dtheta);

    Register(solid);
    SetSolid(solid);
    
    // MakeLogicalVolume --//  
    MakeLVWith(OpenMaterialStore()->Order(list->GetDOMMaterial()));
    
    // SetVisAttribute ----//
    PaintLV(list->GetDOMVisAtt(), list->GetDOMColor());
  	
    // Install daughter PV //
    // Install Benthos     //

#if 1

    fBenthos = new J4DOMBenthos(this);
    Register(fBenthos);
    fBenthos->InstallIn(this);  
    SetDaughter(fBenthos);

    fInside = new J4DOMInside(this);
    Register(fInside);
    fInside->InstallIn(this);  
    SetDaughter(fInside);

#else
    J4DOMPMT *pmt = new J4DOMPMT(this);
    pmt->InstallIn(this);
    SetDaughter(pmt);
#endif
      
  }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4DOM::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4DOM::InstallIn(J4VComponent        *,
                     G4RotationMatrix     *, 
                     const G4ThreeVector  & ) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object...
  
  SetPVPlacement();

}



//* Draw  --------------------------------------------------------
void J4DOM::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4DOM::Print() const
{
}

	
	
