{
	gROOT->ProcessLine(".include ../include/");
	gROOT->ProcessLine(".include ../src/");
	gROOT->ProcessLine(".include ./");
	
	gROOT->ProcessLine(".x ellipticity.C++");
}
