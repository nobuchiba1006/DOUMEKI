// $Id: J4VisManager.cc,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
// ====================================================================
//    J4VisManager.cc
//
//                                 .JLC-CDC, 2001
// ====================================================================
#include "J4VisManager.hh"

// supported drivers...

#ifdef G4VIS_USE_DAWN
#include "G4FukuiRenderer.hh"
#endif

#ifdef G4VIS_USE_DAWNFILE
#include "G4DAWNFILE.hh"
#endif

#ifdef G4VIS_USE_OPACS
#include "G4Wo.hh"
#include "G4Xo.hh"
#endif

#ifdef G4VIS_USE_OPENGLX
#include "G4OpenGLImmediateX.hh"
#include "G4OpenGLStoredX.hh"
#endif

#ifdef G4VIS_USE_OPENGLWIN32
#include "G4OpenGLImmediateWin32.hh"
#include "G4OpenGLStoredWin32.hh"
#endif

#ifdef G4VIS_USE_OPENGLXM
#include "G4OpenGLImmediateXm.hh"
#include "G4OpenGLStoredXm.hh"
#endif

#ifdef G4VIS_USE_OIX
#include "G4OpenInventorX.hh"
#endif

#ifdef G4VIS_USE_OIWIN32
#include "G4OpenInventorWin32.hh"
#endif

#ifdef G4VIS_USE_RAYX
#include "G4RayX.hh"
#endif

#ifdef G4VIS_USE_VRML
#include "G4VRML1.hh"
#include "G4VRML2.hh"
#endif

#ifdef G4VIS_USE_VRMLFILE
#include "G4VRML1File.hh"
#include "G4VRML2File.hh"
#endif

// ====================================================================
//
// class description
//
// ====================================================================

//////////////////////////////////
J4VisManager::J4VisManager() 
//////////////////////////////////
{
}

///////////////////////////////////
J4VisManager::~J4VisManager() 
///////////////////////////////////
{
}

///////////////////////////////////////////////
void J4VisManager::RegisterGraphicsSystems() 
///////////////////////////////////////////////
{
#ifdef G4VIS_USE_DAWN
  std::cout << "*  Visualizaton Driver: Fukui Renderer" << std::endl;
  RegisterGraphicsSystem(new G4FukuiRenderer);
#endif

#ifdef G4VIS_USE_DAWNFILE
  std::cout << "*  Visualizaton Driver: DAWN" << std::endl;
  RegisterGraphicsSystem(new G4DAWNFILE);
#endif

#ifdef G4VIS_USE_OPACS
  RegisterGraphicsSystem(new G4Wo);
  RegisterGraphicsSystem(new G4Xo);
#endif

#ifdef G4VIS_USE_OPENGLX
  RegisterGraphicsSystem(new G4OpenGLImmediateX);
  RegisterGraphicsSystem(new G4OpenGLStoredX);
#endif

#ifdef G4VIS_USE_OPENGLWIN32
  RegisterGraphicsSystem(new G4OpenGLImmediateWin32);
  RegisterGraphicsSystem(new G4OpenGLStoredWin32);
#endif

#ifdef G4VIS_USE_OPENGLXM
  RegisterGraphicsSystem(new G4OpenGLImmediateXm);
  RegisterGraphicsSystem(new G4OpenGLStoredXm);
#endif

#ifdef G4VIS_USE_OIX
  RegisterGraphicsSystem(new G4OpenInventorX);
#endif

#ifdef G4VIS_USE_OIWIN32
  RegisterGraphicsSystem(new G4OpenInventorWin32);
#endif

#ifdef G4VIS_USE_RAYX
  RegisterGraphicsSystem(new G4RayX);
#endif

#ifdef G4VIS_USE_VRML
  std::cout << "*  Visualizaton Driver: VRML1/2" << std::endl;
  RegisterGraphicsSystem(new G4VRML1);
  RegisterGraphicsSystem(new G4VRML2);
#endif

#ifdef G4VIS_USE_VRMLFILE
  std::cout << "*  Visualizaton Driver: VRML1/2 File" << std::endl;
  RegisterGraphicsSystem(new G4VRML1File);
  RegisterGraphicsSystem(new G4VRML2File);
#endif

  if(fVerbose> 0) {
    std::cout << std::endl 
	   << "You have successfully chosen to use "
	   << "the following graphics systems."
	   << std::endl;
    PrintAvailableGraphicsSystems (G4VisManager::warnings);
  }
}

