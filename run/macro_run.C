{
   gROOT->Reset();
   gROOT->ProcessLine(".L analysisLocalControlMain.C");
   gROOT->ProcessLine("load(\"00-00-95\")");
   gROOT->ProcessLine("alc.initialize()");
   gROOT->ProcessLine("alc.loop(0,0)");
}
