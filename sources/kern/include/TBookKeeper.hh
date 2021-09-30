// $Id: TBookKeeper.hh,v 1.1.1.1 2004/08/26 07:04:26 hoshina Exp $
#ifndef __TBOOKKEEPER__
#define __TBOOKKEEPER__
//*************************************************************************
//* -----------------------
//* TBookKeeper
//* -----------------------
//* (Description)
//* 	Base class for all object .
//*     
//* (Update Record)
//*	2001/03/27  K.Hoshina	Original version.
//*************************************************************************

#include "./vector"
#include "G4ios.hh"
#include <stdlib.h>


//=====================================================================
//---------------------
// class definition
//---------------------

class TBookKeeper 
{	// abstruct class

private:

  class TPair 
  { 
   public:
     TPair(void *parent, void *child) 
           :fParent(parent), fChild(child) {}
     virtual ~TPair(){}

     inline void SetPair (void *parent, void *child) 
                        {
                           fParent = parent;
                           fChild  = child;
                        }
   public:
     void *fParent;
     void *fChild;    
  };   

public:

  typedef std::vector<TBookKeeper::TPair* > TBook;

  TBookKeeper()
  {
     if (!fgBookKeeper) {
        fgBookKeeper = this;
     } else {
        std::cerr << " TBookKeeper is singleton. abort. " << std::endl;
        abort();
     }
  }		          
  
  virtual ~TBookKeeper(){}
  
  inline  void   Register   (void *parent, void *child);
  inline  bool   Deregister (void *child);
  inline  void*  GetParent  (void *child);

  inline static TBookKeeper* GetBookKeeper() { return fgBookKeeper; } 

private:

  static TBookKeeper *fgBookKeeper;
         TBook        fBook; 

};

//=============================
// inline functions
//=============================

void TBookKeeper::Register(void *parent, void *child) 
{
   TPair* pair = new TPair(parent, child);
   fBook.push_back(pair); 
}

bool TBookKeeper::Deregister(void *child) 
{
   if (!child) return false;

   unsigned int i;
   for (i=0; i<fBook.size();i++) {
       if (fBook[i]) {
           if (fBook[i]->fChild != child) continue;
           delete fBook[i]; 
#if 0
           unsigned int j;
           for (j=i; j<fBook.size()-1; j++) {
               fBook[j] = fBook[j+1];
           } 
#else
           fBook[i] = 0;
#endif
	   return true;

       }
   }
#ifdef __DEBUG__
   std::cerr << " TBookKeeper::Deregister: The child ("
          << child
          << ") had already been orphaned !! " << std::endl;
#endif
   return false;
}

void* TBookKeeper::GetParent(void *child) 
{
   unsigned int i;
   for (i=0; i<fBook.size(); i++) {
       if (fBook[i]) {
           if (fBook[i]->fChild != child) continue;
           return fBook[i]->fParent;
       }
   }
#ifdef __DEBUG__
   std::cerr << " TBookKeeper::GetParent: You ("
          << child
          << ") had already been orphaned !! " << std::endl;
#endif
   return 0;
}

#endif


