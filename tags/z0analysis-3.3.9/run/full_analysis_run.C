{
   gROOT->Reset();
   gROOT->ProcessLine(".L /srv01/tau/hod/z0analysis-tests/z0analysis-tmp_qsub/run/analysisLocalControlMain.C");
   gROOT->ProcessLine("load(\"00-00-91\",\"/srv01/tau/hod/z0analysis-tests/z0analysis-tmp_qsub/run/\")");
   gROOT->ProcessLine("alc.initialize()");
   gROOT->ProcessLine("alc.loop(0,0)");
}
