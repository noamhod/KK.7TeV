{
	/////////////////////////////////////////////////////////////////////////////////////////////
	//// usage: broot simpleplot_withpdfs_compile.C --mass=1000 --channel=mm --gRe=1 --gIm=0 ////
	/////////////////////////////////////////////////////////////////////////////////////////////


	TString mass    = "";
	TString channel = "";
	TString gRe     = "";
	TString gIm     = "";
	
	for(int i=0 ; i<gApplication->Argc() ; i++)
	{
		printf("Arg  %d:  %s\n",i,gApplication->Argv(i));
	}
	if(gApplication->Argc()>10 || gApplication->Argc()<5)
	{
		cout << "gApplication->Argc()=" << gApplication->Argc() << endl;
		exit(-1);
	}
	else
	{
		for(int i=0 ; i<gApplication->Argc() ; i++)
		{
			TString arg = gApplication->Argv(i);
			if(arg.Contains("--mass="))    mass    = arg.ReplaceAll("--mass=","");
			if(arg.Contains("--channel=")) channel = arg.ReplaceAll("--channel=","");
			if(arg.Contains("--gRe="))     gRe     = arg.ReplaceAll("--gRe=","");
			if(arg.Contains("--gIm="))     gIm     = arg.ReplaceAll("--gIm=","");
		}

		cout << "running with mass    = " << mass << endl;
		cout << "running with channel = " << channel << endl;
		cout << "running with gRe     = " << gRe << endl;
		cout << "running with gIm     = " << gIm << endl;
	}

	TString p = gSystem->pwd();
	cout << "running from path    = " << p << endl;
	
	gROOT->ProcessLine(".include "+p+"/../include/");
	gROOT->ProcessLine(".include "+p+"/../src/");
	gROOT->ProcessLine(".include "+p);
	
	gROOT->ProcessLine(".include "+p+"/../../../lhapdf_current/include/");
	gROOT->ProcessLine(".L "+p+"/../../../lhapdf_current/lib/libLHAPDF.so");
	
	TString args = "\("+mass+",\""+channel+"\","+gRe+","+gIm+"\)";
	gROOT->ProcessLine(".x simpleplot_withpdfs.C++"+args);
}
