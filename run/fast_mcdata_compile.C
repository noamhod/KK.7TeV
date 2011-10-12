{
	gROOT->ProcessLine(".include ../include/");
	gROOT->ProcessLine(".include ../src/");
	gROOT->ProcessLine(".include ./");
	
	gROOT->ProcessLine(".L fast_mcdata_run.C++");
	gROOT->ProcessLine("run()");
}
