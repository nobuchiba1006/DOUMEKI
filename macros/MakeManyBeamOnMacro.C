Int_t MakeManyBeamOnMacro(Int_t nevts, Int_t nbanches){

   //Int_t    nevts = 1000;    // 
   //Int_t    nbanches = 1000;    // 
   //Int_t    nevts = 100;    // 
   //Int_t    nbanches = 10000;    // 

   TString outname ("manybeamOn");
   outname += "_";
   outname += nevts;
   outname += "evt_";
   outname += nbanches;
   outname += "bunch.g4mac";
   ofstream out(outname.Data());

   Int_t count = 0;

   for (Int_t i=0; i<nbanches; i++) {
      out << "/jupiter/run/SetRunNumber " << i << endl; 
      out << "/run/beamOn " << nevts << endl; 
      
   }
   out.close();
   out.clear();

}
