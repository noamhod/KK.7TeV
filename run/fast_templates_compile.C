{
	/////////////////////////////////////////////////////////////////
	// default usage:  broot fast_templates_compile.C --mass=-1  ////
	// advanced usage: broot fast_templates_compile.C --mass=850 ////
	/////////////////////////////////////////////////////////////////
	
	TString massname = "";
	Bool_t isOK = false;
	Bool_t make = false;

	for(int i=0 ; i<gApplication->Argc() ; i++)
	{
		printf("Arg  %d:  %s\n",i,gApplication->Argv(i));
	}
	if(gApplication->Argc()>7 || gApplication->Argc()<5)
	{
		cout << "gApplication->Argc()=" << gApplication->Argc() << endl;
		exit(-1);
	}
	else if(gApplication->Argc()==5)
	{
		cout << "running with default loop on the mass" << endl;
	}
	else
	{
		TString arg1 = gApplication->Argv(1);
		if(gApplication->Argc()==6 && arg1.Contains("-splash"))
		{
			cout << "running with default loop on the mass" << endl;
			isOK = true;
			make = true;
		}
		for(int i=0 ; i<gApplication->Argc() && !isOK ; i++)
		{
			TString arg = gApplication->Argv(i);
			if(arg.Contains("--mass="))
			{
				massname = arg.ReplaceAll("--mass=","");
				isOK = true;
				break;
			}
		}
		if(!isOK)
		{
			cout << "mass parameter wasn't found" << endl;
			exit(-1);
		}
		cout << "running with mass = " << massname << endl;
	}
	
	TString p = gSystem->pwd();

	gROOT->ProcessLine(".include "+p+"/../include/");
	gROOT->ProcessLine(".include "+p+"/../src/");
	gROOT->ProcessLine(".include "+p);
	
	if(make) gROOT->ProcessLine(".L fast_templates_run.C++");
	else
	{
		gROOT->ProcessLine(".L fast_templates_run_C.so");
		gROOT->ProcessLine("run("+massname+")");
	}
}
