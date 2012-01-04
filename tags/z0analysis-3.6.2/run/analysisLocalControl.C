/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "analysisLocalControl.h"


analysisLocalControl::analysisLocalControl()
{
	_DEBUG("analysisLocalControl::analysisLocalControl");
}

analysisLocalControl::~analysisLocalControl()
{
	
}

void analysisLocalControl::setRunControl(string localRunControlFile)
{
	_DEBUG("analysisLocalControl::setRunControl");

	string sBaseDir;
	string sRun;
	string sDataType;
	string sRec;
	string spTtype;
	string sRel;
	string sMCPtag;
	string sPUwriteMC;
	string sPUremoveData;
	bool bPUwriteMC;
	bool bPUremoveData;
	string sMCorData;
	string sIsQCD;
	string sIsLoose;
	bool   isMC;
	bool   isQCD;
	bool   isLoose;
	string sMsgTyp;
	string sMsgLvl;
	//int    msgLvl;
	
	ifstream ifsel( localRunControlFile.c_str() );
	ifsel >> sBaseDir >> sRun >> sDataType >> sRec >> spTtype >> sRel >> sMCPtag >> sPUwriteMC >> sPUremoveData >> sMCorData >> sIsQCD >> sIsLoose;
	
	if(sBaseDir=="")
	{
		_ERROR("YOU CHOSE EMPTY BASEDIR, exitting now");
		exit(-1);
	}
	if(sRun!="local"  &&  sRun!="local_noskim")
	{
		_ERROR("YOU CHOSE RUN ["+sRun+"], exitting now");
		exit(-1);
	}
	if(sDataType!="Data11"  &&  sDataType!="Data10")
	{
		_ERROR("YOU CHOSE DATA TYPE ["+sDataType+"], exitting now");
		exit(-1);
	}
	if(sRec!="staco"  &&  sRec!="muid")
	{
		_ERROR("YOU CHOSE REC ALG ["+sRec+"], exitting now");
		exit(-1);
	}
	if(spTtype!="pT"  &&  spTtype!="q_pT")
	{
		_ERROR("YOU CHOSE SMEARING TYPE ["+spTtype+"], exitting now");
		exit(-1);
	}
	if(sRel!="Rel17")
	{
		_ERROR("YOU CHOSE RELEASE NUMBER ["+sRel+"], exitting now");
		exit(-1);
	}
	size_t found = sMCPtag.find("MuonMomentumCorrections");
	if (found==string::npos)
	{
		_ERROR("YOU CHOSE MCP TAG ["+sMCPtag+"], exitting now");
		exit(-1);
	}
	if(sPUwriteMC!="pu_writeMC=true"  &&  sPUwriteMC!="pu_writeMC=false")
	{
		_ERROR("YOU CHOSE PU WRITE FLAG ["+sPUwriteMC+"], exitting now");
		exit(-1);
	}
	bPUwriteMC = (sPUwriteMC=="pu_writeMC=true");
	if(sPUremoveData!="pu_removeData=true"  &&  sPUremoveData!="pu_removeData=false")
	{
		_ERROR("YOU CHOSE PU REMOVE DATA FLAT ["+sPUremoveData+"], exitting now");
		exit(-1);
	}
	bPUremoveData = (sPUremoveData=="pu_removeData=true");
	if(sMCorData!="mc"  &&  sMCorData!="data"  &&  sMCorData!="mcqsub")
	{
		_ERROR("ERROR: YOU CHOSE MC/DATA ["+sMCorData+"], exitting now");
		exit(-1);
	}
	isMC = (sMCorData=="mc" || sMCorData=="mcqsub") ? true : false;
	if(sIsQCD!="QCD=yes"  &&  sIsQCD!="QCD=no")
	{
		_ERROR("ERROR: YOU CHOSE QCD=yes/no ["+sIsQCD+"], exitting now");
		exit(-1);
	}
	isQCD = (sIsQCD=="QCD=yes") ? true : false;
	if(sIsLoose!="tight"  &&  sIsLoose!="loose")
	{
		_ERROR("ERROR: YOU CHOSE isLoose ["+sIsLoose+"], exitting now");
		exit(-1);
	}
	isLoose = (sIsLoose=="loose") ? true : false; // false if sIsLoose=="tight"
	for(int i=0 ; i<(int)msglvl.size()-2 ; i++)
	{
		ifsel >> sMsgTyp >> sMsgLvl;
		if(sMsgTyp!="DBG" && sMsgTyp!="INF" && sMsgTyp!="WRN") _ERROR("ERROR: YOU CHOSE MSGTYP ["+sMsgTyp+"], exitting now");
		else
		{
			if(sMsgLvl!="VISUAL" && sMsgLvl!="SILENT")
			{
				_ERROR("ERROR: YOU CHOSE MSGLVL ["+sMsgLvl+"], exitting now");
				exit(-1);
			}
		}
		msglvl[i] = (sMsgLvl=="SILENT") ? SILENT : VISUAL;
		_INFO("msglvl["+_s(i)+"]="+sMsgLvl);
	}
	
	m_basedir   = sBaseDir;
	m_RunType   = sRun; // "grid" OR "local"
	m_dataType  = sDataType; // "Data11" OR "Data10"
	m_muRecAlgo = sRec; // "staco" OR "muid"
	m_pTsmearingType = spTtype; // "pT" OR "q_pT"
	m_release   = sRel; // "Rel17"
	m_MCPtag = sMCPtag; // "MuonMomentumCorrections-XX-YY-ZZ"
	m_doPUwriteMC = bPUwriteMC;
	m_doPUremoveData = bPUremoveData;
	m_isMC      = isMC;
	m_isQCD     = isQCD;
	m_isLoose   = isLoose;
	m_input     = sMCorData;
	
	_INFO("m_basedir="+m_basedir);
	_INFO("m_RunType="+m_RunType);
	_INFO("m_dataType="+m_dataType);
	_INFO("m_muRecAlgo="+m_muRecAlgo);
	_INFO("m_pTsmearingType="+m_pTsmearingType);
	_INFO("m_release="+m_release);
	_INFO("m_MCPtag="+m_MCPtag);
	_INFO("m_doPUwriteMC="+_s(m_doPUwriteMC));
	_INFO("m_doPUremoveData="+_s(m_doPUremoveData));
	_INFO("m_isMC="+_s(m_isMC));
	_INFO("m_isQCD="+m_isQCD);
	_INFO("m_isLoose="+_s(m_isLoose));
	_INFO("m_input="+sMCorData);
	
	////////////////////////////////////////////////////////
	if(!getenv("BASEDIR"))
	{
		string senv = "BASEDIR="+m_basedir; ////////////////////
		putenv((char*)senv.c_str()); ///////////////////////////
		_INFO("getenv: BASEDIR="+(string)getenv("BASEDIR")); ///
	}
	////////////////////////////////////////////////////////
	
	///////////////////////////
	//setMSGlevel(m_msglvl); ////
	///////////////////////////
	
	ifsel.close();
}

void analysisLocalControl::initialize(string run_number_str, string runs, string basedir, string localRunControlFile)
{
	_DEBUG("analysisLocalControl::initialize");
	
	utilities::startTimer();
	
	if(runs=="ALLRUNS")   setRunControl(localRunControlFile);
	if(runs=="SINGLERUN")
	{
		_INFO("reading "+localRunControlFile+" from "+basedir);
		setRunControl(basedir+"/"+localRunControlFile);
	}
	
	_INFO("run_number_str="+run_number_str);

	// run control
	l64t_nentries = 0;
	l64t_nbytes   = 0;
	l64t_nb       = 0;
	l64t_jentry   = 0;
	l64t_ientry   = 0;
	
	string str_list = "";
	string str_dir  = "";
	string str_tree = "";
	string str_hist = "";
	string str_mcp  = "";
	string str_mcname = "";
	
	if(basedir=="")
	{
		basedir = m_basedir;
		_INFO("setting basedir -> "+basedir);
	}

	string str = "";
	if(runs=="ALLRUNS")   str = basedir+"/../conf/Z_GRL_CURRENT.xml";
	if(runs=="SINGLERUN") str = basedir+"/../conf/Z_GRL_CURRENT.xml";
	_INFO("LOADING FILE -> "+str);
	m_GRL = new GRLinterface();
	m_GRL->glrinitialize( (TString)str );
	
	
	int run_number_int = (int)validate_double(run_number_str);
	if(m_input=="mcqsub")
	{
		if(run_number_int==106047)                             str_mcname = "Zmumu";
		if(run_number_int==106044)                             str_mcname = "Wmunu";
		if(run_number_int>=105477  &&  run_number_int<=105487) str_mcname = "DYmumu";
		if(run_number_int>=105488  &&  run_number_int<=105498) str_mcname = "DYtautau";
		if(run_number_int==105200) str_mcname = "T1_McAtNlo_Jimmy";
		if(run_number_int==105985) str_mcname = "WW_Herwig";
		if(run_number_int==105986) str_mcname = "ZZ_Herwig";
		if(run_number_int==105987) str_mcname = "WZ_Herwig";
		if(run_number_int==107690) str_mcname = "AlpgenJimmyWmunuNp0_pt20";
		if(run_number_int==107691) str_mcname = "AlpgenJimmyWmunuNp1_pt20";
		if(run_number_int==107692) str_mcname = "AlpgenJimmyWmunuNp2_pt20";
		if(run_number_int==107693) str_mcname = "AlpgenJimmyWmunuNp3_pt20";
		if(run_number_int==107694) str_mcname = "AlpgenJimmyWmunuNp4_pt20";
		if(run_number_int==107695) str_mcname = "AlpgenJimmyWmunuNp5_pt20";
		if(run_number_int==106059) str_mcname = "PythiaB_ccmu15X";
		if(run_number_int==108405) str_mcname = "PythiaB_bbmu15X";
	}
	
	
	
	if(m_isMC  &&  m_input!="mcqsub")
	{
		//////////////////////////////////////////////
		// prompt to chose the MC sample here ////////
		str_mcname = utilities::pickMCinputSampe(); ///
		//////////////////////////////////////////////
		
		str_list = basedir+"/../conf/mc_local_dataset_"+str_mcname+".list";
		_INFO("LOADING FILE -> "+str_list);
		str_dir  = "";
		_INFO("LOADING FILE -> "+str_dir);
		str_hist = basedir+"/../data/mcLocalControl_"+str_mcname+".root";
		_INFO("LOADING FILE -> "+str_hist);
		str_mcp  = basedir+"/../"+m_MCPtag+"/share/";
		_INFO("LOADING FILE -> "+str_mcp);
		
		if(m_RunType!="local_noskim")
		{
			if(str_mcname=="mcWZphys_localTests") str_dir = basedir+"/";
			_INFO("LOADING FILE -> "+str_dir);
			str_tree = basedir+"/../data/mcLocalTree_"+str_mcname+".root";
			_INFO("LOADING FILE -> "+str_tree);
		}
	}
	else
	{
		if(runs=="ALLRUNS")   str_list = basedir+"/../conf/NTUP_SMDILEP_DIMUON_RUNS_CURRENT.list";
		if(runs=="SINGLERUN") str_list = basedir+"/../conf/tmp/"+run_number_str+".list";
		
		_INFO("LOADING FILE -> "+str_list);
		
		str_dir  = "";
		_INFO("LOADING FILE -> "+str_dir);
		str_tree = basedir+"/../data/localTree.root";
		_INFO("LOADING FILE -> "+str_tree);
		
		if(runs=="ALLRUNS")   str_hist = basedir+"/../data/analysisLocalControl.root";
		if(runs=="SINGLERUN") str_hist = basedir+"/../data/tmp/run_"+run_number_str+".root";
		_INFO("LOADING FILE -> "+str_hist);
		
		if(runs=="ALLRUNS")   str_mcp = "";
		if(runs=="SINGLERUN") str_mcp = basedir+"/../"+m_MCPtag+"/share/";
		_INFO("LOADING FILE -> "+str_mcp);
	}
	
	vector<string>* vStr2find = NULL; // all the patterns to be found except for ".root"
	chainInit(vStr2find);
	
	if(runs=="ALLRUNS") makeChain(true, str_list, str_dir, run_number_int);
	else                makeChain(true, str_list, str_dir);

	m_WZphysD3PD = new WZphysD3PD( m_chain, m_isMC );

	
	if(m_RunType=="local_noskim") m_treefile = NULL;
	else                          m_treefile = new TFile( str_tree.c_str(), "RECREATE");
	
	m_histfile = new TFile( str_hist.c_str(), "RECREATE");
	m_histfile->cd();
	
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// initialize the main analysis object //////////////////////////////////////////////////////////////////
	m_analysis = new analysis(m_RunType, m_muRecAlgo, m_isMC, m_WZphysD3PD, m_GRL, m_treefile ); ////////////
	m_analysis->setBaseDir(basedir); ////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	
	m_analysis->setLoose(m_isLoose);
	
	
	string str_events = "";
	if(runs=="ALLRUNS")   str_events = basedir+"/../run/interestingEvents.dump";
	if(runs=="SINGLERUN") str_events = basedir+"/../run/tmp/interestingEvents_"+run_number_str+".dump";
	_INFO("LOADING FILE -> "+str_events);
	m_analysis->setEventDumpFile(str_events, 500.);
	
	
	// string str_xml_path = utilities::checkANDsetFilepath("BASEDIR", "/../xml");
	// string str_xml_path = (string)getenv("BASEDIR")+"/../xml";
	string str_xml_path = basedir+"/../xml";
	_INFO("LOADING FILE -> "+str_xml_path);
	m_analysis->setXmlFile(str_xml_path);
	
	
	string str_logspath = "";
	if(runs=="ALLRUNS")   str_logspath = basedir+"/../run";
	if(runs=="SINGLERUN") str_logspath = basedir+"/../run/tmp";
	_INFO("LOADING FILE -> "+str_logspath);
	m_analysis->setMC(m_isMC);
	m_analysis->setQCD(m_isQCD);
	if(m_isMC) m_analysis->setMCPpTparameters(m_dataType, m_muRecAlgo, m_pTsmearingType, m_release, str_mcp);
	
	
	///////////////////////////////////
	m_analysis->ginitialize(); ////////
	///////////////////////////////////
	
	
	///////////////////////////////////////////
	m_analysis->sMCsampleName = str_mcname; ///
	///////////////////////////////////////////
	
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if(m_isMC)
	{
		m_analysis->doMCPUwrite  = m_doPUwriteMC;
		m_analysis->doRemoveData = m_doPUremoveData;
		m_analysis->sMCPUName = (m_isMC && m_analysis->doMCPUwrite) ? m_analysis->setMCPUFiles(str_logspath, run_number_str) : "";
		// string str_pileuphist_data = basedir+"/../conf/data11_7TeV.periodBtoD.root"; // this is just a default initializer. it is overriden in analysisSkeleton
		string str_pileuphist_data = basedir+"/../conf/CURRENT_iLUMICALC_HISTOGRAMS.root";
		_INFO("LOADING FILE -> "+str_pileuphist_data);
		string str_pileuphist_mc = basedir+"/../conf/pileup_"+str_mcname+".root"; // this is just a default initializer. it is overriden in analysisSkeleton
		_INFO("LOADING FILE -> "+str_pileuphist_mc);
		m_analysis->setPileupParameters((TString)str_pileuphist_data, "LumiMetaData", (TString)str_pileuphist_mc, "MCPileupReweighting");
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	m_analysis->setCutFlowFile(str_logspath, run_number_str);
	m_analysis->setPtCandidatesFile(str_logspath, run_number_str);
	m_analysis->setAllCandidatesFiles(str_logspath, run_number_str);
	
	m_analysis->setStyle((TString)basedir+"/../src");
	
	book();
	
	/////////////////////
	setFermions(); //////
	/////////////////////

	if(m_treefile!=NULL) m_treefile->cd();
}

void analysisLocalControl::finalize()
{
	_DEBUG("analysisLocalControl::finalize");

	//m_analysis->m_WZphysD3PDmaker->m_tree->Print();
	// tree
	// the tree will split into multiple files
	// since in digestTree class there is the
	// following statement m_tree->SetMaxTreeSize(50000000);
	// i.e., 50Mb per file
	if(m_treefile!=NULL)
	{
		m_treefile = m_analysis->m_WZphysD3PDmaker->m_tree->GetCurrentFile();
		m_treefile->cd();
		m_analysis->m_WZphysD3PDmaker->m_tree->Write("", TObject::kOverwrite);
		m_treefile->Write();
		m_treefile->Close();
	}
	
	// histos
	//m_histfile->Write();
	//m_histfile->Close();
	m_analysis->writeTrees(m_dirAllCuts,m_dirCutProfile,m_dirEff,m_dirTruth);
	if(m_isMC  &&  m_analysis->doMCPUwrite) m_analysis->writePileupMCfile();
}

void analysisLocalControl::book()
{
	_DEBUG("analysisLocalControl::book");

	m_dirNoCuts = m_histfile->mkdir("noCuts");
	m_analysis->bookBareHistos(m_dirNoCuts);

	m_dirAllCuts = m_histfile->mkdir("allCuts");
	m_analysis->bookHistos(m_dirAllCuts);
	
	m_dirFit = m_histfile->mkdir("fit");
	m_analysis->bookFitHistos(m_dirFit);

	m_dirCutFlow = m_histfile->mkdir("cutFlow");
	m_analysis->bookHistosMap( m_analysis->getCutFlowOrderedMapPtr(), m_analysis->getCutFlowTypeOrderedMapPtr(), m_dirCutFlow );
	
	m_dirCutProfile = m_histfile->mkdir("cutsProfile");
	m_analysis->bookCutProfileHistosMap( m_analysis->getCutFlowOrderedMapPtr(), m_dirCutProfile );
	
	m_dirEff = m_histfile->mkdir("efficiency");
	m_analysis->bookEfficiencyHistos(m_analysis->m_period2triggerperiodMap, m_dirEff);
	
	m_dirTruth = m_histfile->mkdir("truth");
	
	m_analysis->setTrees(m_dirAllCuts, m_dirCutProfile, m_dirEff, m_dirTruth);
	
	m_dirPerformance = m_histfile->mkdir("performance");
}

void analysisLocalControl::draw()
{
	_DEBUG("analysisLocalControl::draw");

	m_analysis->drawBareHistos(m_dirNoCuts);
	
	// these calculations must come before drawHistos
	m_analysis->calculateAfb(m_analysis->h1_Afb);
	
	m_analysis->drawHistos(m_dirAllCuts);
	
	m_analysis->drawHistosMap( m_analysis->getCutFlowOrderedMapPtr(), m_analysis->getCutFlowTypeOrderedMapPtr(), m_dirCutFlow );
	
	m_analysis->drawFitHistos(m_dirFit, m_analysis->m_fitROOT->guess, m_analysis->m_fitROOT->fitFCN);
	//m_analysis->drawFitHistos(m_dirFit, m_analysis->m_fitMinuit->guess, m_analysis->m_fitMinuit->fitFCN);
	
	m_analysis->drawCutProfileHistosMap( m_dirCutProfile );
	
	bool isTruth = false;
	m_analysis->calculateEfficiency(m_analysis->h1map_tagNprobe_candidates_pT,
									m_analysis->h1map_tagNprobe_succeeded_pT,
									m_analysis->h1map_tagNprobe_trigEff_pT, isTruth);
	m_analysis->calculateEfficiency(m_analysis->h1map_tagNprobe_candidates_eta,
									m_analysis->h1map_tagNprobe_succeeded_eta,
									m_analysis->h1map_tagNprobe_trigEff_eta, isTruth);
	m_analysis->calculateEfficiency(m_analysis->h1map_tagNprobe_candidates_phi,
									m_analysis->h1map_tagNprobe_succeeded_phi,
									m_analysis->h1map_tagNprobe_trigEff_phi, isTruth);
	isTruth = true;
	m_analysis->calculateEfficiency(m_analysis->h1map_truth_candidates_pT,
									m_analysis->h1map_truth_succeeded_pT,
									m_analysis->h1map_truth_trigEff_pT, isTruth);
	m_analysis->calculateEfficiency(m_analysis->h1map_truth_candidates_eta,
									m_analysis->h1map_truth_succeeded_eta,
									m_analysis->h1map_truth_trigEff_eta, isTruth);
	m_analysis->calculateEfficiency(m_analysis->h1map_truth_candidates_phi,
									m_analysis->h1map_truth_succeeded_phi,
									m_analysis->h1map_truth_trigEff_phi, isTruth);
	m_analysis->drawEfficiencyHistosMap(m_dirEff);
	
	m_analysis->drawPerformance( vEntries, vResMemory, vVirMemory, m_dirPerformance );
	
	m_analysis->printCutFlowNumbers(l64t_nentries, m_analysis->sMCsampleName);
	
	if(!m_doPUwriteMC  &&  m_doPUremoveData) _INFO("correctedMClumi -> "+_s(m_analysis->correctedMClumi));
}

void analysisLocalControl::fits()
{
	_DEBUG("analysisLocalControl::fits");

	cout << "### in fits ####" << endl;

	double yields[2];
	
	// Preform the fit
	m_analysis->minimize( false, m_analysis->h1_imassFit, yields, m_dirFit );
}

void analysisLocalControl::analyze()
{
	_DEBUG("analysisLocalControl::analyze");
	
	m_analysis->execute();
}

void analysisLocalControl::loop(Long64_t startEvent, Long64_t stopAfterNevents)
{
	_DEBUG("analysisLocalControl::loop(Long64_t startEvent, Long64_t stopAfterNevents)");
	
	if (m_WZphysD3PD->fChain == 0)  return;

	l64t_nentries = m_WZphysD3PD->fChain->GetEntriesFast();
	l64t_nbytes = 0;
	l64t_nb = 0;

	l64t_mod = 10000;

	l64t_startEvent = startEvent;
	l64t_stopEvent = l64t_nentries;
	
	if(stopAfterNevents <= 0)                            { l64t_stopEvent = l64t_nentries; cout << "1. stop at event " << l64t_stopEvent << endl; }
	else if(startEvent+stopAfterNevents < l64t_nentries) { l64t_stopEvent = startEvent+stopAfterNevents; cout << "3. stop at event " << l64t_stopEvent << endl; }
	if(startEvent+stopAfterNevents > l64t_nentries)      { l64t_stopEvent = l64t_nentries; cout << "2. stop at event " << l64t_stopEvent << endl; }

	for (l64t_jentry=l64t_startEvent ; l64t_jentry<l64t_stopEvent/*l64t_nentries*/ ; l64t_jentry++)
	{
		l64t_ientry = m_WZphysD3PD->LoadTree(l64t_jentry);
		if (l64t_ientry < 0) break;
		
		if(m_RunType!="local_noskim")
		{
			/////////////////////////////////////////////////
			l64t_nb = m_WZphysD3PD->fChain->GetEntry(l64t_jentry);
			l64t_nbytes += l64t_nb;
			// m_WZphysD3PD->GetEntryMinimal(l64t_ientry);
			/////////////////////////////////////////////////
		}
		else
		{
			/////////////////////////////////////////////////
			l64t_nb = m_WZphysD3PD->fChain->GetEntry(l64t_jentry);
			l64t_nbytes += l64t_nb;
			// m_WZphysD3PD->GetEntryMinimal(l64t_ientry); /////
			/////////////////////////////////////////////////
		}
		
		if(l64t_jentry%l64t_mod==0) cout << "jentry=" << l64t_jentry << "\t ientry=" << l64t_ientry << "\trun=" << m_WZphysD3PD->RunNumber << "\tlumiblock=" << m_WZphysD3PD->lbn << endl;
		if(l64t_jentry%l64t_mod==0) m_analysis->printCutFlowNumbers(l64t_nentries, m_analysis->sMCsampleName);
		
		if(l64t_jentry%1000==0)
		{
			gSystem->GetProcInfo(&pi);
			vResMemory.push_back((double)pi.fMemResident);
			vVirMemory.push_back((double)pi.fMemVirtual);
			vEntries.push_back((int)l64t_jentry);
		}
		
		analyze();
	}
	
	fits();
	
	draw();
	
	finalize();
	
	// cout << "nAll           = " << m_analysis->nAll << endl;
	// cout << "n0mu           = " << m_analysis->n0mu << endl;
	// cout << "n1mu(pT>10GeV) = " << m_analysis->n1mu << endl;
	// cout << "n2mu(pT>10GeV) = " << m_analysis->n2mu << endl;
	// cout << "n3mu(pT>10GeV) = " << m_analysis->n3mu << endl;
	// cout << "n4mu(pT>10GeV) = " << m_analysis->n4mu << endl;
	// cout << "nNmu(pT>10GeV) = " << m_analysis->nNmu << endl;
	// cout << "nSkim          = " << m_analysis->nSkim << endl;
	// cout << "nSkim%         = " << (double)m_analysis->nSkim/(double)m_analysis->nAll << endl;
	
	cout << "################" << endl;
	cout << "##### " << m_analysis->sMuonRecoAlgo << " #####" << endl;
	cout << "################" << endl;
	
	utilities::stopTimer(true);
}

void analysisLocalControl::loop(int RunNumber)
{
	_DEBUG("analysisLocalControl::loop(int RunNumber)");

	if (m_WZphysD3PD->fChain == 0)  return;

	l64t_nentries = m_WZphysD3PD->fChain->GetEntriesFast();
	l64t_nbytes = 0;
	l64t_nb = 0;

	l64t_mod = 10000;

	for (l64t_jentry=0 ; l64t_jentry<l64t_nentries ; l64t_jentry++)
	{
		l64t_ientry = m_WZphysD3PD->LoadTree(l64t_jentry);
		if (l64t_ientry < 0) break;
		
		if(m_RunType!="local_noskim")
		{
			l64t_nb = m_WZphysD3PD->fChain->GetEntry(l64t_jentry);
			l64t_nbytes += l64t_nb;
		}
		else
		{
			/////////////////////////////////////////////////
			// read only the minimal set of branches ////////
			//GetEntryMinimal(l64t_ientry); /////////////////
			//m_WZphysD3PD->GetEntryMinimal(l64t_ientry); /////
			l64t_nb = m_WZphysD3PD->fChain->GetEntry(l64t_jentry);
			l64t_nbytes += l64t_nb;
			/////////////////////////////////////////////////
		}
		
		// if (Cut(l64t_ientry) < 0) continue;
		
		if(l64t_jentry%100000==0) cout << "jentry=" << l64t_jentry << "\t ientry=" << l64t_ientry << "\trun=" << m_WZphysD3PD->RunNumber << "\tlumiblock=" << m_WZphysD3PD->lbn << endl;
		
		//////////////////////////////////////////////////////
		if((int)m_WZphysD3PD->RunNumber < RunNumber) continue; ///////
		if((int)m_WZphysD3PD->RunNumber > RunNumber) break; //////////
		//////////////////////////////////////////////////////
		
		if(l64t_jentry%l64t_mod==0) m_analysis->printCutFlowNumbers(l64t_nentries, m_analysis->sMCsampleName);
		
		if(l64t_jentry%1000==0)
		{
			gSystem->GetProcInfo(&pi);
			vResMemory.push_back((double)pi.fMemResident);
			vVirMemory.push_back((double)pi.fMemVirtual);
			vEntries.push_back((int)l64t_jentry);
		}
		
		analyze();
	}
	
	fits();
	
	draw();
	
	finalize();
	
	utilities::stopTimer(true);
}


void analysisLocalControl::loop(string sPeriodStart, string sPeriodEnd, Long64_t l64t_initialGuess)
{
        _DEBUG("analysisLocalControl::loop(string sPeriodStart, string sPeriodEnd, Long64_t l64t_initialGuess)");

        if (m_WZphysD3PD->fChain == 0)  return;

        l64t_nentries = m_WZphysD3PD->fChain->GetEntriesFast();
        l64t_nbytes = 0;
        l64t_nb = 0;

        l64t_mod = 10000;

        int firstRunInRange = 0;
        int lastRunInRange  = 0;
        for(TMapis::iterator it=m_analysis->m_firstrun2periodMap->begin() ; it!=m_analysis->m_firstrun2periodMap->end() ; it++)
        {
                if(it->second==sPeriodStart)
                {
                        firstRunInRange = it->first;
                        cout << "start loop in run# = " << firstRunInRange << endl;
                        break;
                }
        }
        for(TMapis::iterator it=m_analysis->m_lastrun2periodMap->begin() ; it!=m_analysis->m_lastrun2periodMap->end() ; it++)
        {
                if(it->second==sPeriodEnd)
                {
                        lastRunInRange = it->first;
                        cout << "end loop in run# = " << lastRunInRange << endl;
                        break;
                }
        }
        if(lastRunInRange==0 || firstRunInRange==0)
        {
                cout << "ERROR in analysisLocalControl::loop(string sPeriodName): didn't find period with name = " << lastRunInRange << " or " << firstRunInRange << endl;
                cout << "exitting now" << endl;
                exit(-1);
        }
        
        // bisection
        Long64_t l64t_a = 0;
        //Long64_t l64t_b = l64t_nentries;
        Long64_t l64t_b = l64t_initialGuess; //190000000 initial guess (should be bigger than firstRunInRange)
        Long64_t l64t_jmid = 0;
        Long64_t l64t_imid = 0;
        int run = 0;
        int iterations = 0;
        cout << "iteration[" << iterations << "] : run=" << run << ", a=" << l64t_a << ", b=" << l64t_b << ", mid=" << l64t_jmid << endl;
        while(run!=firstRunInRange)
        {
                iterations++;
                l64t_jmid = l64t_a + (Long64_t)((long double)(l64t_b-l64t_a)/2.);
                l64t_imid = m_WZphysD3PD->LoadTree(l64t_jmid);
                
                if(m_RunType!="local_noskim")
                {
                        m_WZphysD3PD->fChain->GetEntry(l64t_jmid);
                }
                else
                {
                        /////////////////////////////////////////////////
                        // read only the minimal set of branches ////////
                        //GetEntryMinimal(l64t_ientry); /////////////////
                        //m_WZphysD3PD->GetEntryMinimal(l64t_ientry); /////
                        l64t_nb = m_WZphysD3PD->fChain->GetEntry(l64t_jentry);
                        l64t_nbytes += l64t_nb;
                        /////////////////////////////////////////////////
                }
                
                run = m_WZphysD3PD->RunNumber;
                cout << "iteration[" << iterations << "] : run=" << run << ", a=" << l64t_a << ", b=" << l64t_b << ", mid=" << l64t_jmid << endl;
                if(run<firstRunInRange) l64t_a = l64t_jmid;
                if(run>firstRunInRange) l64t_b = l64t_jmid;
                if(run==firstRunInRange) {cout << "found first run in range=" << firstRunInRange << endl; break;}
                if(l64t_a==l64t_b || (l64t_b-l64t_a)==1) {cout << "l64t_a==l64t_b || (l64t_b-l64t_a)==1, exitting now" << endl; exit(-1);}
        }
        // now go back to the first file in the firstRunInRange
        cout << "looking for first event in run " << firstRunInRange << endl;
        while(run==firstRunInRange)
        {
                l64t_imid = m_WZphysD3PD->LoadTree(l64t_jmid);
                m_WZphysD3PD->fChain->GetEntry(l64t_jmid);
                run = m_WZphysD3PD->RunNumber;
                if(run!=firstRunInRange)
                {
                        l64t_jmid++;
                        break;
                }
                l64t_jmid--;
        }
        
        for (l64t_jentry=l64t_jmid ; l64t_jentry<l64t_nentries ; l64t_jentry++)
        {
                l64t_ientry = m_WZphysD3PD->LoadTree(l64t_jentry);
                if (l64t_ientry < 0) break;
                
                if(m_RunType!="local_noskim")
                {
                        l64t_nb = m_WZphysD3PD->fChain->GetEntry(l64t_jentry);
                        l64t_nbytes += l64t_nb;
                }
                else
                {
                        /////////////////////////////////////////////////
                        // read only the minimal set of branches ////////
                        //GetEntryMinimal(l64t_ientry); /////////////////
                        //m_WZphysD3PD->GetEntryMinimal(l64t_ientry); /////
                        l64t_nb = m_WZphysD3PD->fChain->GetEntry(l64t_jentry);
                        l64t_nbytes += l64t_nb;
                        /////////////////////////////////////////////////
                }
                
                // if (Cut(l64t_ientry) < 0) continue;
                
                if(l64t_jentry%100000==0) cout << "jentry=" << l64t_jentry << "\t ientry=" << l64t_ientry << "\trun=" << m_WZphysD3PD->RunNumber << "\tlumiblock=" << m_WZphysD3PD->lbn << endl;
                
                ////////////////////////////////////////////////////////////////////
                if((int)m_WZphysD3PD->RunNumber < firstRunInRange) continue; ///////
                if((int)m_WZphysD3PD->RunNumber > lastRunInRange)  break; //////////
                ////////////////////////////////////////////////////////////////////
                
                if(l64t_jentry%l64t_mod==0) m_analysis->printCutFlowNumbers(l64t_nentries, m_analysis->sMCsampleName);
                
                if(l64t_jentry%1000==0)
                {
                        gSystem->GetProcInfo(&pi);
                        vResMemory.push_back((double)pi.fMemResident);
                        vVirMemory.push_back((double)pi.fMemVirtual);
                        vEntries.push_back((int)l64t_jentry);
                }
                
                analyze();
        }
        
        fits();
        
        draw();
        
        finalize();
        
        utilities::stopTimer(true);
}
