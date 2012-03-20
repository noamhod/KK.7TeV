{
	////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// compilation:   broot fast_templates_compile.C  ////////////////////////////////////////////////////
	//// default loop:  broot fast_templates_compile.C --mass=-1  //////////////////////////////////////////
	//// advanced loop: broot fast_templates_compile.C --channel=mm --gN=g2 --oversmeared=0 --mass=-1 //////
	//// single mass:   broot fast_templates_compile.C --channel=mm --gN=g2 --oversmeared=0 --mass=1030 ////
	////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	TString massname    = "";
	TString channelname = "";
	TString gPower      = "";
	TString oversmeared = "";
	Bool_t isOK = false;
	Bool_t make = false;

	for(int i=0 ; i<gApplication->Argc() ; i++)
	{
		printf("Arg  %d:  %s\n",i,gApplication->Argv(i));
	}
	if(gApplication->Argc()>10 || gApplication->Argc()<5)
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
			if(arg.Contains("--channel="))
			{
				channelname = arg.ReplaceAll("--channel=","");
				// isOK = true;
				// break;
			}
			if(arg.Contains("--gN="))
			{
				gPower = arg.ReplaceAll("--gN=","");
				// isOK = true;
				// break;
			}
			if(arg.Contains("--oversmeared="))
			{
				oversmeared = arg.ReplaceAll("--oversmeared=","");
				// isOK = true;
				// break;
			}
			if(arg.Contains("--mass="))
			{
				massname = arg.ReplaceAll("--mass=","");
				// isOK = true;
				// break;
			}
		}
		// if(!isOK)
		// {
			// cout << "mass parameter wasn't found" << endl;
			// exit(-1);
		// }
		cout << "running with channel = " << channelname << endl;
		cout << "running with gPower  = " << gPower << endl;
		cout << "running with mass    = " << massname << endl;
		cout << "running with sigmaup = " << oversmeared << endl;
	}
	
	TString p = gSystem->pwd();
	cout << "running from path    = " << p << endl;
	
	gROOT->ProcessLine(".include "+p+"/../include/");
	gROOT->ProcessLine(".include "+p+"/../src/");
	gROOT->ProcessLine(".include "+p);
	
	if(make) gROOT->ProcessLine(".L fast_templates_run.C++");
	else
	{
		gROOT->ProcessLine(".L fast_templates_run_C.so");
		TString sLine = "\""+channelname+"\",\""+gPower+"\","+oversmeared+","+massname;
		gROOT->ProcessLine("run("+sLine+")");
	}
}
