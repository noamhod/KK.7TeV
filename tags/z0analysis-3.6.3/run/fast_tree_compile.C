{
	gROOT->ProcessLine(".include ../include/");
	gROOT->ProcessLine(".include ../src/");
	gROOT->ProcessLine(".include ./");
	
	gROOT->ProcessLine(".L fast_tree_run.C++");
	gROOT->ProcessLine("setisMC(false,false)");
	gROOT->ProcessLine("run()");
}
