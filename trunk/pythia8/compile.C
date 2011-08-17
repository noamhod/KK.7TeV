{
	gROOT->ProcessLine(".include ../roofit");
	gSystem->Load("libRooFit");
	gROOT->ProcessLine(".L ../roofit/RooAngular.cxx++");
	gSystem->Load("../roofit/RooAngular_cxx.so");
	gROOT->ProcessLine(".x Afb_RooFit_weighted.C++");
}
