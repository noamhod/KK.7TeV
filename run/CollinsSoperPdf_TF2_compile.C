{
	gROOT->ProcessLine(".include ../include/");
	gROOT->ProcessLine(".include ../src/");
	gROOT->ProcessLine(".include ./");
	
	gROOT->ProcessLine(".x CollinsSoperPdf_TF2_run.C++");
}

