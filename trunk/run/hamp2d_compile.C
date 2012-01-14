{
	gROOT->ProcessLine(".include ../include/");
	gROOT->ProcessLine(".include ../src/");
	gROOT->ProcessLine(".include ./");
	
	gROOT->ProcessLine(".include ../../../lhapdf_current/include/");
	gROOT->ProcessLine(".L ../../../lhapdf_current/lib/libLHAPDF.so");
	
	gROOT->ProcessLine(".x hamp2d.C++");
}
