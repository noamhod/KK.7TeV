{
	//// usage: //////////////////////////////////////////////////////////////////////////////////////
	//// broot -b -l -q theory_analysis_compile.C --mcname=KK --channel=mumu --mBSM=1000 --runNum=1 /////
	//// mcname  = DY,ZP_ssm,ZP_psi,ZP_chi,ZP_eta,KK /////////////////////////////////////////////////
	//// channel = mumu,ee ///////////////////////////////////////////////////////////////////////////
	//// mBSM    = -1(for DY), >0 else ///////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////

	gROOT->ProcessLine(".include ../include/");
	gROOT->ProcessLine(".include ../src/");
	gROOT->ProcessLine(".include ./");
	
	TString mcname  = "";
	TString channel = "";
	TString massbsm = "";
	TString runnumb = "";

	for(int i=0 ; i<gApplication->Argc() ; i++)
	{
		printf("Arg  %d:  %s\n",i,gApplication->Argv(i));
	}
	if(gApplication->Argc()>13 || gApplication->Argc()<5)
	{
		cout << "gApplication->Argc()=" << gApplication->Argc() << endl;
		exit(-1);
	}
	
	TString arg1 = gApplication->Argv(1);
	for(int i=0 ; i<gApplication->Argc() ; i++)
	{
		TString arg = gApplication->Argv(i);
		if(arg.Contains("--mcname="))  mcname  = arg.ReplaceAll("--mcname=","");
		if(arg.Contains("--channel=")) channel = arg.ReplaceAll("--channel=","");
		if(arg.Contains("--mBSM="))    massbsm = arg.ReplaceAll("--mBSM=","");
		if(arg.Contains("--runNum="))  runnumb = arg.ReplaceAll("--runNum=","");
	}
	
	cout << "running with mcname  = " << mcname << endl;
	cout << "running with channel = " << channel << endl;
	cout << "running with mBSM    = " << massbsm << endl;
	cout << "running with runnumb = " << runnumb << endl;

	TString sLine = "\""+mcname+"\",\""+channel+"\","+massbsm+","+runnumb;
	cout << "Arguments: " << sLine << endl;
	
	// gROOT->ProcessLine(".L theory_analysis.C++");
	gROOT->ProcessLine(".L theory_analysis_C.so");
	gROOT->ProcessLine("analysis("+sLine+")");
}
