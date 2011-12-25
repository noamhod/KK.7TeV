{
   gROOT->Reset();
   gROOT->ProcessLine(".L /srv01/tau/hod/z0analysis-tests/z0analysis-r170/run/analysisLocalControlMain.C");
   gROOT->ProcessLine("load(\"00-00-96\",\"/srv01/tau/hod/z0analysis-tests/z0analysis-r170/run/\")");
   gROOT->ProcessLine("alc.initialize()");
   gROOT->ProcessLine("alc.loop(0,0)");
}
