{
   gROOT->Reset();
   gROOT->ProcessLine(".L analysisLocalControlMain.C");
   gROOT->ProcessLine("compile(\"00-00-95\")");
}
