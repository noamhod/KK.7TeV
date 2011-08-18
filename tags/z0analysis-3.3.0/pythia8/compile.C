{
	gROOT->ProcessLine(".include ../roofit");
	gSystem->Load("libRooFit");
	gROOT->ProcessLine(".L ../roofit/RooAngular.cxx++");
	gROOT->ProcessLine(".L ../roofit/RooCollinsSoper.cxx++");
	gSystem->Load("../roofit/RooAngular_cxx.so");
	gSystem->Load("../roofit/RooCollinsSoper_cxx.so");
	gROOT->ProcessLine(".x Afb_RooFit_weighted.C++");
}
