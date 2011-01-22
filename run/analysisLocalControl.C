/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "analysisLocalControl.h"


analysisLocalControl::analysisLocalControl()
{
	
}

analysisLocalControl::~analysisLocalControl()
{
	
}

void analysisLocalControl::setRunControl(string localRunControlFile)
{
	string sRun;
	string sRec;
	string sMCorData;
	bool   isMC;
	
	ifstream ifsel( localRunControlFile.c_str() );
	ifsel >> sRun >> sRec >> sMCorData;
	ifsel.close();
	
	if(sRun!="local"  &&  sRun!="local_noskim")
	{
		cout << "ERROR: YOU CHOSE RUN   [" << sRun << "], exitting now" << endl;
		exit(-1);
	}
	if(sRec!="staco"  &&  sRec!="muid")
	{
		cout << "ERROR: YOU CHOSE REC ALG   [" << sRec << "], exitting now" << endl;
		exit(-1);
	}
	if(sMCorData!="mc"  &&  sMCorData!="data")
	{
		cout << "ERROR: YOU CHOSE MC/DATA   [" << sMCorData << "], exitting now" << endl;
		exit(-1);
	}
	isMC = (sMCorData=="mc") ? true : false;
	
	m_RunType   = sRun; // "grid" OR "local"
	m_muRecAlgo = sRec; // "staco" OR "muid"
	m_isMC      = isMC;
	
	cout << "m_RunType="   << m_RunType   << endl;
	cout << "m_muRecAlgo=" << m_muRecAlgo << endl;
	cout << "m_isMC="      << m_isMC      << endl;
}

void analysisLocalControl::initialize(int runNumber, string localRunControlFile)
{
	startTimer();
	
	setRunControl(localRunControlFile);

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
	
	string str = checkANDsetFilepath("PWD", "/../conf/Z_GRL_CURRENT.xml");;
	m_GRL = new GRLinterface();
	m_GRL->glrinitialize( (TString)str );
	
	
	if(m_isMC)
	{
		//////////////////////////////////////////
		// prompt to chose the MC sample here ////
		string sMCsample = pickMCinputSampe(); ///
		//////////////////////////////////////////
		
		str_list = checkANDsetFilepath("PWD", "/../conf/mc_local_dataset_"+sMCsample+".list");
		str_dir = checkANDsetFilepath("PWD", "/mc_local_datasetdir/");
		str_hist = checkANDsetFilepath("PWD", "/../data/mcLocalControl_"+sMCsample+".root");
		
		if(m_RunType!="local_noskim")
		{
			if(sMCsample=="mcWZphys_localTests") str_dir = checkANDsetFilepath("PWD", "/");
			str_tree = checkANDsetFilepath("PWD", "/../data/mcLocalTree_"+sMCsample+".root");
		}
	}
	else
	{
		str_list = checkANDsetFilepath("PWD", "/../conf/local_dataset.list");
		str_dir  = checkANDsetFilepath("PWD", "/local_datasetdir/");
		str_tree = checkANDsetFilepath("PWD", "/../data/localTree.root");
		str_hist = checkANDsetFilepath("PWD", "/../data/analysisLocalControl.root");
		
		// for tests only
		if(runNumber==-1)
		{
			str_dir  = checkANDsetFilepath("PWD", "/");
			str_list = checkANDsetFilepath("PWD", "/../conf/local_dataset_WZphys_localTests.list");
		}
	}
	
	vector<string>* vStr2find = NULL; // all the patterns to be found except for ".root"
	chainInit(vStr2find);
	if(runNumber==-1) makeChain(true, str_list, str_dir);
	else              makeChain(true, str_list, str_dir, runNumber);

	m_WZphysD3PD = new WZphysD3PD( m_chain, m_isMC );

	
	if(m_RunType=="local_noskim") m_treefile = NULL;
	else                          m_treefile = new TFile( str_tree.c_str(), "RECREATE");
	
	m_histfile = new TFile( str_hist.c_str(), "RECREATE");
	m_histfile->cd();

	string str1 = checkANDsetFilepath("PWD", "/../conf/cutFlow.cuts");
	string str2 = checkANDsetFilepath("PWD", "/../conf/dataPeriods.data");
	
	m_analysis = new analysis(m_RunType, m_muRecAlgo, m_isMC,
							  m_WZphysD3PD, m_GRL, m_treefile,
							  str1, str2, "interestingEvents.dump" );

	book();

	if(m_treefile!=NULL) m_treefile->cd();
}

void analysisLocalControl::finalize()
{
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
		m_analysis->m_WZphysD3PDmaker->m_tree->Write();
		m_treefile->Write();
		m_treefile->Close();
	}
	
	// histos
	//m_histfile->Write();
	//m_histfile->Close();
	m_analysis->writeTrees(m_dirAllCuts,m_dirCutProfile,m_dirEff);
	
}

void analysisLocalControl::book()
{
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
	
	m_analysis->setTrees(m_dirAllCuts, m_dirCutProfile, m_dirEff);
	
	m_dirPerformance = m_histfile->mkdir("performance");
}

void analysisLocalControl::draw()
{
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
	
	m_analysis->printCutFlowNumbers(l64t_nentries);
}

void analysisLocalControl::fits()
{
	cout << "### in fits ####" << endl;

	double yields[2];
	
	// Preform the fit
	m_analysis->minimize( false, m_analysis->h1_imassFit, yields, m_dirFit );
}

void analysisLocalControl::analyze()
{
	m_analysis->execute();
}

void analysisLocalControl::loop(Long64_t startEvent, Long64_t stopAfterNevents)
{
	if (m_WZphysD3PD->fChain == 0)  return;

	l64t_nentries = m_WZphysD3PD->fChain->GetEntriesFast();
	l64t_nbytes = 0;
	l64t_nb = 0;

	l64t_mod = 100000;

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
			l64t_nb = m_WZphysD3PD->fChain->GetEntry(l64t_jentry);
			l64t_nbytes += l64t_nb;
		}
		else
		{
			////////////////////////////////////////////
			// read only the minimal set of branches ///
			GetEntryMinimal(l64t_ientry); //////////////
			////////////////////////////////////////////
		}
		
		if(l64t_jentry%100000==0)   cout << "jentry=" << l64t_jentry << "\t ientry=" << l64t_ientry << "\trun=" << m_WZphysD3PD->RunNumber << "\tlumiblock=" << m_WZphysD3PD->lbn << endl;
		if(l64t_jentry%l64t_mod==0) m_analysis->printCutFlowNumbers(l64t_nentries);
		
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
	
	cout << "nAll           = " << m_analysis->nAll << endl;
	cout << "n0mu           = " << m_analysis->n0mu << endl;
	cout << "n1mu(pT>10GeV) = " << m_analysis->n1mu << endl;
	cout << "n2mu(pT>10GeV) = " << m_analysis->n2mu << endl;
	cout << "n3mu(pT>10GeV) = " << m_analysis->n3mu << endl;
	cout << "n4mu(pT>10GeV) = " << m_analysis->n4mu << endl;
	cout << "nNmu(pT>10GeV) = " << m_analysis->nNmu << endl;
	cout << "nSkim          = " << m_analysis->nSkim << endl;
	cout << "nSkim%         = " << (double)m_analysis->nSkim/(double)m_analysis->nAll << endl;
	
	cout << "################" << endl;
	cout << "##### " << m_analysis->sMuonRecoAlgo << " #####" << endl;
	cout << "################" << endl;
	
	stopTimer(true);
}

void analysisLocalControl::loop(int runNumber)
{
	if (m_WZphysD3PD->fChain == 0)  return;

	l64t_nentries = m_WZphysD3PD->fChain->GetEntriesFast();
	l64t_nbytes = 0;
	l64t_nb = 0;

	l64t_mod = 100000;

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
			////////////////////////////////////////////
			// read only the minimal set of branches ///
			GetEntryMinimal(l64t_ientry); //////////////
			////////////////////////////////////////////
		}
		
		// if (Cut(l64t_ientry) < 0) continue;
		
		if(l64t_jentry%100000==0) cout << "jentry=" << l64t_jentry << "\t ientry=" << l64t_ientry << "\trun=" << m_WZphysD3PD->RunNumber << "\tlumiblock=" << m_WZphysD3PD->lbn << endl;
		
		//////////////////////////////////////////////////////
		if((int)m_WZphysD3PD->RunNumber < runNumber) continue; ///////
		if((int)m_WZphysD3PD->RunNumber > runNumber) break; //////////
		//////////////////////////////////////////////////////
		
		if(l64t_jentry%l64t_mod==0) m_analysis->printCutFlowNumbers(l64t_nentries);
		
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
	
	stopTimer(true);
}


void analysisLocalControl::loop(string sPeriodStart, string sPeriodEnd, Long64_t l64t_initialGuess)
{
	if (m_WZphysD3PD->fChain == 0)  return;

	l64t_nentries = m_WZphysD3PD->fChain->GetEntriesFast();
	l64t_nbytes = 0;
	l64t_nb = 0;

	l64t_mod = 100000;

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
			////////////////////////////////////////////
			// read only the minimal set of branches ///
			GetEntryMinimal(l64t_imid); //////////////
			////////////////////////////////////////////
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
			////////////////////////////////////////////
			// read only the minimal set of branches ///
			GetEntryMinimal(l64t_ientry); //////////////
			////////////////////////////////////////////
		}
		
		// if (Cut(l64t_ientry) < 0) continue;
		
		if(l64t_jentry%100000==0) cout << "jentry=" << l64t_jentry << "\t ientry=" << l64t_ientry << "\trun=" << m_WZphysD3PD->RunNumber << "\tlumiblock=" << m_WZphysD3PD->lbn << endl;
		
		////////////////////////////////////////////////////////////
		if((int)m_WZphysD3PD->RunNumber < firstRunInRange) continue; ///////
		if((int)m_WZphysD3PD->RunNumber > lastRunInRange)  break; //////////
		////////////////////////////////////////////////////////////
		
		if(l64t_jentry%l64t_mod==0) m_analysis->printCutFlowNumbers(l64t_nentries);
		
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
	
	stopTimer(true);
}


void analysisLocalControl::GetEntryMinimal(Long64_t entry)
{
	if(m_RunType!="local_noskim") return;
	
	m_WZphysD3PD->b_RunNumber->GetEntry(entry);
	m_WZphysD3PD->b_EventNumber->GetEntry(entry);
	m_WZphysD3PD->b_timestamp->GetEntry(entry);
	m_WZphysD3PD->b_timestamp_ns->GetEntry(entry);
	m_WZphysD3PD->b_lbn->GetEntry(entry);
	m_WZphysD3PD->b_bcid->GetEntry(entry);
	//m_WZphysD3PD->b_detmask0->GetEntry(entry);
	//m_WZphysD3PD->b_detmask1->GetEntry(entry);
	//m_WZphysD3PD->b_pixelFlags->GetEntry(entry);
	//m_WZphysD3PD->b_sctFlags->GetEntry(entry);
	//m_WZphysD3PD->b_trtFlags->GetEntry(entry);
	//m_WZphysD3PD->b_larFlags->GetEntry(entry);
	//m_WZphysD3PD->b_tileFlags->GetEntry(entry);
	//m_WZphysD3PD->b_muonFlags->GetEntry(entry);
	//m_WZphysD3PD->b_fwdFlags->GetEntry(entry);
	//m_WZphysD3PD->b_coreFlags->GetEntry(entry);
	//m_WZphysD3PD->b_pixelError->GetEntry(entry);
	//m_WZphysD3PD->b_sctError->GetEntry(entry);
	//m_WZphysD3PD->b_trtError->GetEntry(entry);
	//m_WZphysD3PD->b_larError->GetEntry(entry);
	//m_WZphysD3PD->b_tileError->GetEntry(entry);
	//m_WZphysD3PD->b_muonError->GetEntry(entry);
	//m_WZphysD3PD->b_fwdError->GetEntry(entry);
	//m_WZphysD3PD->b_coreError->GetEntry(entry);
	
	//m_WZphysD3PD->b_EF_2mu0_NoAlg->GetEntry(entry);
	//m_WZphysD3PD->b_EF_2mu10->GetEntry(entry);
	//m_WZphysD3PD->b_EF_2mu10_NoAlg->GetEntry(entry);
	//m_WZphysD3PD->b_EF_2mu4->GetEntry(entry);
	//m_WZphysD3PD->b_EF_2mu4_Bmumu->GetEntry(entry);
	//m_WZphysD3PD->b_EF_2mu4_Bmumux->GetEntry(entry);
	//m_WZphysD3PD->b_EF_2mu4_DiMu->GetEntry(entry);
	//m_WZphysD3PD->b_EF_2mu4_DiMu_SiTrk->GetEntry(entry);
	//m_WZphysD3PD->b_EF_2mu4_DiMu_noVtx->GetEntry(entry);
	//m_WZphysD3PD->b_EF_2mu4_DiMu_noVtx_noOS->GetEntry(entry);
	//m_WZphysD3PD->b_EF_2mu4_Jpsimumu->GetEntry(entry);
	//m_WZphysD3PD->b_EF_2mu4_Jpsimumu_IDTrkNoCut->GetEntry(entry);
	//m_WZphysD3PD->b_EF_2mu4_Upsimumu->GetEntry(entry);
	//m_WZphysD3PD->b_EF_2mu6->GetEntry(entry);
	//m_WZphysD3PD->b_EF_2mu6_Bmumu->GetEntry(entry);
	//m_WZphysD3PD->b_EF_2mu6_Bmumux->GetEntry(entry);
	//m_WZphysD3PD->b_EF_2mu6_DiMu->GetEntry(entry);
	//m_WZphysD3PD->b_EF_2mu6_Jpsimumu->GetEntry(entry);
	//m_WZphysD3PD->b_EF_2mu6_MG->GetEntry(entry);
	//m_WZphysD3PD->b_EF_2mu6_NoAlg->GetEntry(entry);
	//m_WZphysD3PD->b_EF_2mu6_Upsimumu->GetEntry(entry);
	//m_WZphysD3PD->b_EF_2mu6_g10_loose->GetEntry(entry);
	
	//m_WZphysD3PD->b_EF_mu0_NoAlg->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu0_com//m_NoAlg->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu0_com//m_empty_NoAlg->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu0_com//m_firstempty_NoAlg->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu0_com//m_unpaired_iso_NoAlg->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu0_com//m_unpaired_noniso_NoAlg->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu0_empty_NoAlg->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu0_firstempty_NoAlg->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu0_missingRoi->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu0_outOfTime1->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu0_outOfTime2->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu0_rpcOnly->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu0_unpaired_iso_NoAlg->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu0_unpaired_noniso_NoAlg->GetEntry(entry);
	m_WZphysD3PD->b_EF_mu10->GetEntry(entry);
	m_WZphysD3PD->b_EF_mu10_Ecut12->GetEntry(entry);
	m_WZphysD3PD->b_EF_mu10_Ecut123->GetEntry(entry);
	m_WZphysD3PD->b_EF_mu10_Ecut13->GetEntry(entry);
	m_WZphysD3PD->b_EF_mu10_IDTrkNoCut->GetEntry(entry);
	m_WZphysD3PD->b_EF_mu10_MG->GetEntry(entry);
	m_WZphysD3PD->b_EF_mu10_MSonly->GetEntry(entry);
	m_WZphysD3PD->b_EF_mu10_MSonly_Ecut12->GetEntry(entry);
	m_WZphysD3PD->b_EF_mu10_MSonly_Ecut123->GetEntry(entry);
	m_WZphysD3PD->b_EF_mu10_MSonly_Ecut13->GetEntry(entry);
	m_WZphysD3PD->b_EF_mu10_MSonly_tight->GetEntry(entry);
	m_WZphysD3PD->b_EF_mu10_NoAlg->GetEntry(entry);
	m_WZphysD3PD->b_EF_mu10_SiTrk->GetEntry(entry);
	m_WZphysD3PD->b_EF_mu10_j30->GetEntry(entry);
	m_WZphysD3PD->b_EF_mu10_tight->GetEntry(entry);
	m_WZphysD3PD->b_EF_mu10i_loose->GetEntry(entry);
	m_WZphysD3PD->b_EF_mu13->GetEntry(entry);
	m_WZphysD3PD->b_EF_mu13_MG->GetEntry(entry);
	m_WZphysD3PD->b_EF_mu13_MG_tight->GetEntry(entry);
	m_WZphysD3PD->b_EF_mu13_tight->GetEntry(entry);
	m_WZphysD3PD->b_EF_mu15->GetEntry(entry);
	m_WZphysD3PD->b_EF_mu15_MG->GetEntry(entry);
	m_WZphysD3PD->b_EF_mu15_NoAlg->GetEntry(entry);
	m_WZphysD3PD->b_EF_mu20->GetEntry(entry);
	m_WZphysD3PD->b_EF_mu20_MSonly->GetEntry(entry);
	m_WZphysD3PD->b_EF_mu20_NoAlg->GetEntry(entry);
	m_WZphysD3PD->b_EF_mu20_passHLT->GetEntry(entry);
	m_WZphysD3PD->b_EF_mu20_slow->GetEntry(entry);
	m_WZphysD3PD->b_EF_mu30_MSonly->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4->GetEntry(entry);
	m_WZphysD3PD->b_EF_mu40_MSonly->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_Bmumu->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_BmumuX->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_DiMu->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_DiMu_FS->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_DiMu_FS_noOS->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_DiMu_MG->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_DiMu_MG_FS->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_DiMu_SiTrk->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_DiMu_SiTrk_FS->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_DiMu_noOS->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_IDTrkNoCut->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_Jpsie5e3->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_Jpsie5e3_FS->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_Jpsie5e3_SiTrk->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_Jpsie5e3_SiTrk_FS->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_Jpsimumu->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_Jpsimumu_FS->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_Jpsimumu_SiTrk_FS->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_L1J10_matched->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_L1J15_matched->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_L1J30_matched->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_L1J55_matched->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_L1J5_matched->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_L2MSonly_EFFS_passL2->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_MG->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_MSonly->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_MSonly_EFFS_passL2->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_MSonly_MB2_noL2_EFFS->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_MSonly_cosmic->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_MSonly_outOfTime->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_MV->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_SiTrk->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_Trk_Jpsi->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_Trk_Jpsi_FS->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_Trk_Jpsi_loose->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_Trk_Upsi_FS->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_Trk_Upsi_loose_FS->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_Upsimumu_FS->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_Upsimumu_SiTrk_FS->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_com//m_MSonly_cosmic->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_com//m_cosmic->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_com//m_firstempty->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_com//m_unpaired_iso->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_cosmic->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_firstempty->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_j20->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_j20_jetNoEF->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_j30->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_j30_jetNoEF->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_mu6->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_muCombTag->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_tile->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_tile_cosmic->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4_unpaired_iso->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4mu6_Bmumu->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4mu6_BmumuX->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4mu6_DiMu->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4mu6_Jpsimumu->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4mu6_Jpsimumu_IDTrkNoCut->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu4mu6_Upsimumu->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu6->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu6_Bmumu->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu6_BmumuX->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu6_DiMu->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu6_Ecut12->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu6_Ecut123->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu6_Ecut13->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu6_Ecut2->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu6_Ecut3->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu6_IDTrkNoCut->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu6_Jpsie5e3->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu6_Jpsie5e3_FS->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu6_Jpsie5e3_SiTrk->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu6_Jpsie5e3_SiTrk_FS->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu6_Jpsimumu->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu6_MG->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu6_MSonly->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu6_MSonly_Ecut12->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu6_MSonly_Ecut123->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu6_MSonly_Ecut13->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu6_MSonly_Ecut2->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu6_MSonly_Ecut3->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu6_MSonly_outOfTime->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu6_NoAlg->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu6_SiTrk->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu6_Trk_Jpsi->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu6_Upsimumu_FS->GetEntry(entry);
	//m_WZphysD3PD->b_EF_mu6_muCombTag->GetEntry(entry);
	
	//m_WZphysD3PD->b_L1_2MU0->GetEntry(entry);
	//m_WZphysD3PD->b_L1_2MU0_FIRSTEMPTY->GetEntry(entry);
	//m_WZphysD3PD->b_L1_2MU0_MU6->GetEntry(entry);
	//m_WZphysD3PD->b_L1_2MU10->GetEntry(entry);
	//m_WZphysD3PD->b_L1_2MU20->GetEntry(entry);
	//m_WZphysD3PD->b_L1_2MU6->GetEntry(entry);
	//m_WZphysD3PD->b_L1_2MU6_EM5->GetEntry(entry);
	
	//m_WZphysD3PD->b_L1_MU0->GetEntry(entry);
	//m_WZphysD3PD->b_L1_MU0_COMM->GetEntry(entry);
	//m_WZphysD3PD->b_L1_MU0_COMM_EMPTY->GetEntry(entry);
	//m_WZphysD3PD->b_L1_MU0_COMM_FIRSTEMPTY->GetEntry(entry);
	//m_WZphysD3PD->b_L1_MU0_COMM_UNPAIRED_ISO->GetEntry(entry);
	//m_WZphysD3PD->b_L1_MU0_COMM_UNPAIRED_NONISO->GetEntry(entry);
	//m_WZphysD3PD->b_L1_MU0_EM3->GetEntry(entry);
	//m_WZphysD3PD->b_L1_MU0_EMPTY->GetEntry(entry);
	//m_WZphysD3PD->b_L1_MU0_FIRSTEMPTY->GetEntry(entry);
	//m_WZphysD3PD->b_L1_MU0_J10->GetEntry(entry);
	//m_WZphysD3PD->b_L1_MU0_J15->GetEntry(entry);
	//m_WZphysD3PD->b_L1_MU0_J30->GetEntry(entry);
	//m_WZphysD3PD->b_L1_MU0_J5->GetEntry(entry);
	//m_WZphysD3PD->b_L1_MU0_J55->GetEntry(entry);
	//m_WZphysD3PD->b_L1_MU0_MV->GetEntry(entry);
	//m_WZphysD3PD->b_L1_MU0_UNPAIRED_ISO->GetEntry(entry);
	//m_WZphysD3PD->b_L1_MU0_UNPAIRED_NONISO->GetEntry(entry);
	m_WZphysD3PD->b_L1_MU10->GetEntry(entry);
	m_WZphysD3PD->b_L1_MU10_FIRSTEMPTY->GetEntry(entry);
	m_WZphysD3PD->b_L1_MU10_J10->GetEntry(entry);
	m_WZphysD3PD->b_L1_MU15->GetEntry(entry);
	m_WZphysD3PD->b_L1_MU20->GetEntry(entry);
	m_WZphysD3PD->b_L1_MU6->GetEntry(entry);
	m_WZphysD3PD->b_L1_MU6_EM3->GetEntry(entry);
	m_WZphysD3PD->b_L1_MU6_FIRSTEMPTY->GetEntry(entry);
	m_WZphysD3PD->b_L1_MU6_J5->GetEntry(entry);
	
	//m_WZphysD3PD->b_L2_2mu0_NoAlg->GetEntry(entry);
	//m_WZphysD3PD->b_L2_2mu10->GetEntry(entry);
	//m_WZphysD3PD->b_L2_2mu10_NoAlg->GetEntry(entry);
	//m_WZphysD3PD->b_L2_2mu4->GetEntry(entry);
	//m_WZphysD3PD->b_L2_2mu4_Bmumu->GetEntry(entry);
	//m_WZphysD3PD->b_L2_2mu4_Bmumux->GetEntry(entry);
	//m_WZphysD3PD->b_L2_2mu4_DiMu->GetEntry(entry);
	//m_WZphysD3PD->b_L2_2mu4_DiMu_SiTrk->GetEntry(entry);
	//m_WZphysD3PD->b_L2_2mu4_DiMu_noVtx->GetEntry(entry);
	//m_WZphysD3PD->b_L2_2mu4_DiMu_noVtx_noOS->GetEntry(entry);
	//m_WZphysD3PD->b_L2_2mu4_Jpsimumu->GetEntry(entry);
	//m_WZphysD3PD->b_L2_2mu4_Jpsimumu_IDTrkNoCut->GetEntry(entry);
	//m_WZphysD3PD->b_L2_2mu4_Upsimumu->GetEntry(entry);
	//m_WZphysD3PD->b_L2_2mu6->GetEntry(entry);
	//m_WZphysD3PD->b_L2_2mu6_Bmumu->GetEntry(entry);
	//m_WZphysD3PD->b_L2_2mu6_Bmumux->GetEntry(entry);
	//m_WZphysD3PD->b_L2_2mu6_DiMu->GetEntry(entry);
	//m_WZphysD3PD->b_L2_2mu6_Jpsimumu->GetEntry(entry);
	//m_WZphysD3PD->b_L2_2mu6_MG->GetEntry(entry);
	//m_WZphysD3PD->b_L2_2mu6_NoAlg->GetEntry(entry);
	//m_WZphysD3PD->b_L2_2mu6_Upsimumu->GetEntry(entry);
	//m_WZphysD3PD->b_L2_2mu6_g10_loose->GetEntry(entry);
	
	//m_WZphysD3PD->b_L2_mu0_NoAlg->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu0_com//m_NoAlg->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu0_com//m_empty_NoAlg->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu0_com//m_firstempty_NoAlg->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu0_com//m_unpaired_iso_NoAlg->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu0_com//m_unpaired_noniso_NoAlg->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu0_empty_NoAlg->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu0_firstempty_NoAlg->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu0_missingRoi->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu0_outOfTime1->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu0_outOfTime2->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu0_rpcOnly->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu0_unpaired_iso_NoAlg->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu0_unpaired_noniso_NoAlg->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu10->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu10_Ecut12->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu10_Ecut123->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu10_Ecut13->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu10_IDTrkNoCut->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu10_MG->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu10_MSonly->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu10_MSonly_Ecut12->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu10_MSonly_Ecut123->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu10_MSonly_Ecut13->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu10_MSonly_tight->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu10_NoAlg->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu10_SiTrk->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu10_j30->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu10_tight->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu10i_loose->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu13->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu13_MG->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu13_MG_tight->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu13_tight->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu15->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu15_MG->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu15_NoAlg->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu20->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu20_MSonly->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu20_NoAlg->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu20_passHLT->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu20_slow->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu30_MSonly->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu40_MSonly->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4_Bmumu->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4_BmumuX->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4_DiMu->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4_DiMu_FS->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4_DiMu_FS_noOS->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4_DiMu_MG->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4_DiMu_MG_FS->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4_DiMu_SiTrk->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4_DiMu_SiTrk_FS->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4_DiMu_noOS->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4_IDTrkNoCut->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4_Jpsie5e3->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4_Jpsie5e3_FS->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4_Jpsie5e3_SiTrk->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4_Jpsie5e3_SiTrk_FS->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4_Jpsimumu->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4_Jpsimumu_FS->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4_Jpsimumu_SiTrk_FS->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4_L1J10_matched->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4_L1J15_matched->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4_L1J30_matched->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4_L1J55_matched->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4_L1J5_matched->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4_L2MSonly_EFFS_passL2->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4_MG->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4_MSonly->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4_MSonly_EFFS_passL2->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4_MSonly_MB2_noL2_EFFS->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4_MSonly_cosmic->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4_MSonly_outOfTime->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4_MV->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4_SiTrk->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4_Trk_Jpsi->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4_Trk_Jpsi_FS->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4_Trk_Jpsi_loose->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4_Trk_Upsi_FS->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4_Trk_Upsi_loose_FS->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4_Upsimumu_FS->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4_Upsimumu_SiTrk_FS->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4_com//m_MSonly_cosmic->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4_com//m_cosmic->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4_com//m_firstempty->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4_com//m_unpaired_iso->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4_cosmic->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4_firstempty->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4_j20->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4_j20_jetNoEF->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4_j25->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4_mu6->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4_muCombTag->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4_tile->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4_tile_cosmic->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4_unpaired_iso->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4mu6_Bmumu->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4mu6_BmumuX->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4mu6_DiMu->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4mu6_Jpsimumu->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4mu6_Jpsimumu_IDTrkNoCut->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu4mu6_Upsimumu->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu6->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu6_Bmumu->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu6_BmumuX->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu6_DiMu->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu6_Ecut12->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu6_Ecut123->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu6_Ecut13->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu6_Ecut2->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu6_Ecut3->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu6_IDTrkNoCut->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu6_Jpsie5e3->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu6_Jpsie5e3_FS->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu6_Jpsie5e3_SiTrk->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu6_Jpsie5e3_SiTrk_FS->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu6_Jpsimumu->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu6_MG->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu6_MSonly->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu6_MSonly_Ecut12->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu6_MSonly_Ecut123->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu6_MSonly_Ecut13->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu6_MSonly_Ecut2->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu6_MSonly_Ecut3->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu6_MSonly_outOfTime->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu6_NoAlg->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu6_SiTrk->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu6_Trk_Jpsi->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu6_Upsimumu_FS->GetEntry(entry);
	//m_WZphysD3PD->b_L2_mu6_muCombTag->GetEntry(entry);
	
	if(m_muRecAlgo=="muid")
	{
		m_WZphysD3PD->b_mu_muid_n->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_E->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_pt->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_m->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_eta->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_phi->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_px->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_py->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_pz->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_charge->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_allauthor->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_author->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_beta->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_isMuonLikelihood->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_matchchi2->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_matchndof->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_etcone20->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_etcone30->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_etcone40->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nucone20->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nucone30->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nucone40->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_ptcone20->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_ptcone30->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_ptcone40->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_energyLossPar->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_energyLossErr->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_etCore->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_energyLossType->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_caloMuonIdTag->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_caloLRLikelihood->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_bestMatch->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_isStandAloneMuon->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_isCombinedMuon->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_isLowPtReconstructedMuon->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_loose->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_medium->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_tight->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_d0_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_z0_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_phi_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_theta_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_qoverp_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_cb_d0_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_cb_z0_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_cb_phi_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_cb_theta_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_cb_qoverp_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_id_d0_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_id_z0_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_id_phi_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_id_theta_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_id_qoverp_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_me_d0_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_me_z0_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_me_phi_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_me_theta_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_me_qoverp_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_ie_d0_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_ie_z0_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_ie_phi_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_ie_theta_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_ie_qoverp_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_SpaceTime_detID->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_SpaceTime_t->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_SpaceTime_tError->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_SpaceTime_weight->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_SpaceTime_x->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_SpaceTime_y->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_SpaceTime_z->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_SpaceTime_t_Tile->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_SpaceTime_tError_Tile->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_SpaceTime_weight_Tile->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_SpaceTime_x_Tile->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_SpaceTime_y_Tile->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_SpaceTime_z_Tile->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_SpaceTime_t_TRT->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_SpaceTime_tError_TRT->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_SpaceTime_weight_TRT->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_SpaceTime_x_TRT->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_SpaceTime_y_TRT->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_SpaceTime_z_TRT->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_SpaceTime_t_MDT->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_SpaceTime_tError_MDT->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_SpaceTime_weight_MDT->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_SpaceTime_x_MDT->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_SpaceTime_y_MDT->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_SpaceTime_z_MDT->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_TileCellEnergyLayer1->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_TileTimeLayer1->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_TileCellRmsNoiseLayer1->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_TileCellSignLayer1->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_TileCellEnergyLayer2->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_TileTimeLayer2->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_TileCellRmsNoiseLayer2->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_TileCellSignLayer2->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_TileCellEnergyLayer3->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_TileTimeLayer3->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_TileCellRmsNoiseLayer3->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_TileCellSignLayer3->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_MSTrkT0_1->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_MSTrkT0_2->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_MSTrkT0_3->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_cov_d0_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_cov_z0_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_cov_phi_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_cov_theta_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_cov_qoverp_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_cov_d0_z0_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_cov_d0_phi_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_cov_d0_theta_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_cov_d0_qoverp_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_cov_z0_phi_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_cov_z0_theta_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_cov_z0_qoverp_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_cov_phi_theta_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_cov_phi_qoverp_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_cov_theta_qoverp_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_id_cov_d0_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_id_cov_z0_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_id_cov_phi_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_id_cov_theta_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_id_cov_qoverp_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_id_cov_d0_z0_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_id_cov_d0_phi_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_id_cov_d0_theta_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_id_cov_d0_qoverp_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_id_cov_z0_phi_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_id_cov_z0_theta_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_id_cov_z0_qoverp_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_id_cov_phi_theta_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_id_cov_phi_qoverp_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_id_cov_theta_qoverp_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_me_cov_d0_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_me_cov_z0_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_me_cov_phi_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_me_cov_theta_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_me_cov_qoverp_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_me_cov_d0_z0_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_me_cov_d0_phi_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_me_cov_d0_theta_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_me_cov_d0_qoverp_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_me_cov_z0_phi_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_me_cov_z0_theta_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_me_cov_z0_qoverp_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_me_cov_phi_theta_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_me_cov_phi_qoverp_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_me_cov_theta_qoverp_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_ms_d0->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_ms_z0->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_ms_phi->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_ms_theta->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_ms_qoverp->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_id_d0->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_id_z0->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_id_phi->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_id_theta->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_id_qoverp->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_me_d0->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_me_z0->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_me_phi->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_me_theta->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_me_qoverp->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_ie_d0->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_ie_z0->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_ie_phi->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_ie_theta->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_ie_qoverp->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nOutliersOnTrack->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nBLHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nPixHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nSCTHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nTRTHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nTRTHighTHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nBLSharedHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nPixSharedHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nPixHoles->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nSCTSharedHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nSCTHoles->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nTRTOutliers->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nTRTHighTOutliers->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nGangedPixels->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nPixelDeadSensors->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nSCTDeadSensors->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nTRTDeadStraws->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_expectBLayerHit->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nMDTHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nMDTHoles->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nCSCEtaHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nCSCEtaHoles->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nCSCPhiHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nCSCPhiHoles->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nRPCEtaHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nRPCEtaHoles->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nRPCPhiHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nRPCPhiHoles->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nTGCEtaHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nTGCEtaHoles->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nTGCPhiHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nTGCPhiHoles->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nMDTBIHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nMDTBMHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nMDTBOHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nMDTBEEHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nMDTBIS78Hits->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nMDTEIHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nMDTEMHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nMDTEOHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nMDTEEHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nRPCLayer1EtaHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nRPCLayer2EtaHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nRPCLayer3EtaHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nRPCLayer1PhiHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nRPCLayer2PhiHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nRPCLayer3PhiHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nTGCLayer1EtaHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nTGCLayer2EtaHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nTGCLayer3EtaHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nTGCLayer4EtaHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nTGCLayer1PhiHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nTGCLayer2PhiHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nTGCLayer3PhiHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_nTGCLayer4PhiHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_barrelSectors->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_endcapSectors->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_trackd0->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_trackz0->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_trackphi->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_tracktheta->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_trackqoverp->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_trackcov_d0->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_trackcov_z0->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_trackcov_phi->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_trackcov_theta->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_trackcov_qoverp->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_trackcov_d0_z0->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_trackcov_d0_phi->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_trackcov_d0_theta->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_trackcov_d0_qoverp->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_trackcov_z0_phi->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_trackcov_z0_theta->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_trackcov_z0_qoverp->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_trackcov_phi_theta->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_trackcov_phi_qoverp->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_trackcov_theta_qoverp->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_trackfitchi2->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_trackfitndof->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_hastrack->GetEntry(entry);
		if(m_isMC)
		{
			m_WZphysD3PD->b_mu_muid_truth_dr->GetEntry(entry);
			m_WZphysD3PD->b_mu_muid_truth_E->GetEntry(entry);
			m_WZphysD3PD->b_mu_muid_truth_pt->GetEntry(entry);
			m_WZphysD3PD->b_mu_muid_truth_eta->GetEntry(entry);
			m_WZphysD3PD->b_mu_muid_truth_phi->GetEntry(entry);
			m_WZphysD3PD->b_mu_muid_truth_type->GetEntry(entry);
			m_WZphysD3PD->b_mu_muid_truth_status->GetEntry(entry);
			m_WZphysD3PD->b_mu_muid_truth_barcode->GetEntry(entry);
			m_WZphysD3PD->b_mu_muid_truth_mothertype->GetEntry(entry);
			m_WZphysD3PD->b_mu_muid_truth_motherbarcode->GetEntry(entry);
			m_WZphysD3PD->b_mu_muid_truth_matched->GetEntry(entry);
		}
		m_WZphysD3PD->b_mu_muid_EFCB_dr->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_EFCB_index->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_EFMG_dr->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_EFMG_index->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_EFME_dr->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_EFME_index->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_L2CB_dr->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_L2CB_index->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_L1_dr->GetEntry(entry);
		m_WZphysD3PD->b_mu_muid_L1_index->GetEntry(entry);
	}
	
	if(m_muRecAlgo=="staco")
	{
		m_WZphysD3PD->b_mu_staco_n->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_E->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_pt->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_m->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_eta->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_phi->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_px->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_py->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_pz->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_charge->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_allauthor->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_author->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_beta->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_isMuonLikelihood->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_matchchi2->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_matchndof->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_etcone20->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_etcone30->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_etcone40->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nucone20->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nucone30->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nucone40->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_ptcone20->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_ptcone30->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_ptcone40->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_energyLossPar->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_energyLossErr->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_etCore->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_energyLossType->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_caloMuonIdTag->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_caloLRLikelihood->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_bestMatch->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_isStandAloneMuon->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_isCombinedMuon->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_isLowPtReconstructedMuon->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_loose->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_medium->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_tight->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_d0_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_z0_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_phi_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_theta_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_qoverp_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_cb_d0_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_cb_z0_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_cb_phi_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_cb_theta_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_cb_qoverp_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_id_d0_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_id_z0_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_id_phi_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_id_theta_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_id_qoverp_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_me_d0_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_me_z0_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_me_phi_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_me_theta_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_me_qoverp_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_ie_d0_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_ie_z0_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_ie_phi_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_ie_theta_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_ie_qoverp_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_SpaceTime_detID->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_SpaceTime_t->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_SpaceTime_tError->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_SpaceTime_weight->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_SpaceTime_x->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_SpaceTime_y->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_SpaceTime_z->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_SpaceTime_t_Tile->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_SpaceTime_tError_Tile->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_SpaceTime_weight_Tile->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_SpaceTime_x_Tile->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_SpaceTime_y_Tile->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_SpaceTime_z_Tile->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_SpaceTime_t_TRT->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_SpaceTime_tError_TRT->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_SpaceTime_weight_TRT->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_SpaceTime_x_TRT->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_SpaceTime_y_TRT->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_SpaceTime_z_TRT->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_SpaceTime_t_MDT->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_SpaceTime_tError_MDT->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_SpaceTime_weight_MDT->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_SpaceTime_x_MDT->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_SpaceTime_y_MDT->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_SpaceTime_z_MDT->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_TileCellEnergyLayer1->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_TileTimeLayer1->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_TileCellRmsNoiseLayer1->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_TileCellSignLayer1->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_TileCellEnergyLayer2->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_TileTimeLayer2->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_TileCellRmsNoiseLayer2->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_TileCellSignLayer2->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_TileCellEnergyLayer3->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_TileTimeLayer3->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_TileCellRmsNoiseLayer3->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_TileCellSignLayer3->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_MSTrkT0_1->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_MSTrkT0_2->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_MSTrkT0_3->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_cov_d0_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_cov_z0_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_cov_phi_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_cov_theta_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_cov_qoverp_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_cov_d0_z0_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_cov_d0_phi_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_cov_d0_theta_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_cov_d0_qoverp_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_cov_z0_phi_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_cov_z0_theta_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_cov_z0_qoverp_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_cov_phi_theta_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_cov_phi_qoverp_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_cov_theta_qoverp_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_id_cov_d0_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_id_cov_z0_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_id_cov_phi_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_id_cov_theta_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_id_cov_qoverp_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_id_cov_d0_z0_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_id_cov_d0_phi_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_id_cov_d0_theta_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_id_cov_d0_qoverp_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_id_cov_z0_phi_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_id_cov_z0_theta_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_id_cov_z0_qoverp_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_id_cov_phi_theta_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_id_cov_phi_qoverp_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_id_cov_theta_qoverp_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_me_cov_d0_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_me_cov_z0_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_me_cov_phi_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_me_cov_theta_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_me_cov_qoverp_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_me_cov_d0_z0_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_me_cov_d0_phi_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_me_cov_d0_theta_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_me_cov_d0_qoverp_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_me_cov_z0_phi_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_me_cov_z0_theta_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_me_cov_z0_qoverp_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_me_cov_phi_theta_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_me_cov_phi_qoverp_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_me_cov_theta_qoverp_exPV->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_ms_d0->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_ms_z0->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_ms_phi->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_ms_theta->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_ms_qoverp->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_id_d0->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_id_z0->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_id_phi->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_id_theta->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_id_qoverp->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_me_d0->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_me_z0->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_me_phi->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_me_theta->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_me_qoverp->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_ie_d0->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_ie_z0->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_ie_phi->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_ie_theta->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_ie_qoverp->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nOutliersOnTrack->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nBLHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nPixHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nSCTHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nTRTHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nTRTHighTHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nBLSharedHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nPixSharedHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nPixHoles->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nSCTSharedHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nSCTHoles->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nTRTOutliers->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nTRTHighTOutliers->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nGangedPixels->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nPixelDeadSensors->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nSCTDeadSensors->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nTRTDeadStraws->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_expectBLayerHit->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nMDTHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nMDTHoles->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nCSCEtaHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nCSCEtaHoles->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nCSCPhiHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nCSCPhiHoles->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nRPCEtaHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nRPCEtaHoles->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nRPCPhiHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nRPCPhiHoles->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nTGCEtaHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nTGCEtaHoles->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nTGCPhiHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nTGCPhiHoles->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nMDTBIHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nMDTBMHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nMDTBOHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nMDTBEEHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nMDTBIS78Hits->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nMDTEIHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nMDTEMHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nMDTEOHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nMDTEEHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nRPCLayer1EtaHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nRPCLayer2EtaHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nRPCLayer3EtaHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nRPCLayer1PhiHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nRPCLayer2PhiHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nRPCLayer3PhiHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nTGCLayer1EtaHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nTGCLayer2EtaHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nTGCLayer3EtaHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nTGCLayer4EtaHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nTGCLayer1PhiHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nTGCLayer2PhiHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nTGCLayer3PhiHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_nTGCLayer4PhiHits->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_barrelSectors->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_endcapSectors->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_trackd0->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_trackz0->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_trackphi->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_tracktheta->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_trackqoverp->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_trackcov_d0->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_trackcov_z0->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_trackcov_phi->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_trackcov_theta->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_trackcov_qoverp->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_trackcov_d0_z0->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_trackcov_d0_phi->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_trackcov_d0_theta->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_trackcov_d0_qoverp->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_trackcov_z0_phi->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_trackcov_z0_theta->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_trackcov_z0_qoverp->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_trackcov_phi_theta->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_trackcov_phi_qoverp->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_trackcov_theta_qoverp->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_trackfitchi2->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_trackfitndof->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_hastrack->GetEntry(entry);
		if(m_isMC)
		{
			m_WZphysD3PD->b_mu_staco_truth_dr->GetEntry(entry);
			m_WZphysD3PD->b_mu_staco_truth_E->GetEntry(entry);
			m_WZphysD3PD->b_mu_staco_truth_pt->GetEntry(entry);
			m_WZphysD3PD->b_mu_staco_truth_eta->GetEntry(entry);
			m_WZphysD3PD->b_mu_staco_truth_phi->GetEntry(entry);
			m_WZphysD3PD->b_mu_staco_truth_type->GetEntry(entry);
			m_WZphysD3PD->b_mu_staco_truth_status->GetEntry(entry);
			m_WZphysD3PD->b_mu_staco_truth_barcode->GetEntry(entry);
			m_WZphysD3PD->b_mu_staco_truth_mothertype->GetEntry(entry);
			m_WZphysD3PD->b_mu_staco_truth_motherbarcode->GetEntry(entry);
			m_WZphysD3PD->b_mu_staco_truth_matched->GetEntry(entry);
		}
		m_WZphysD3PD->b_mu_staco_EFCB_dr->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_EFCB_index->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_EFMG_dr->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_EFMG_index->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_EFME_dr->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_EFME_index->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_L2CB_dr->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_L2CB_index->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_L1_dr->GetEntry(entry);
		m_WZphysD3PD->b_mu_staco_L1_index->GetEntry(entry);
	}
	
	//m_WZphysD3PD->b_mu_calo_n->GetEntry(entry);
	//m_WZphysD3PD->b_mu_calo_E->GetEntry(entry);
	//m_WZphysD3PD->b_mu_calo_pt->GetEntry(entry);
	//m_WZphysD3PD->b_mu_calo_m->GetEntry(entry);
	//m_WZphysD3PD->b_mu_calo_eta->GetEntry(entry);
	//m_WZphysD3PD->b_mu_calo_phi->GetEntry(entry);
	//m_WZphysD3PD->b_mu_calo_px->GetEntry(entry);
	//m_WZphysD3PD->b_mu_calo_py->GetEntry(entry);
	//m_WZphysD3PD->b_mu_calo_pz->GetEntry(entry);
	//m_WZphysD3PD->b_mu_calo_charge->GetEntry(entry);
	//m_WZphysD3PD->b_mu_calo_allauthor->GetEntry(entry);
	//m_WZphysD3PD->b_mu_calo_hastrack->GetEntry(entry);
	//m_WZphysD3PD->b_mu_calo_truth_dr->GetEntry(entry);
	//m_WZphysD3PD->b_mu_calo_truth_E->GetEntry(entry);
	//m_WZphysD3PD->b_mu_calo_truth_pt->GetEntry(entry);
	//m_WZphysD3PD->b_mu_calo_truth_eta->GetEntry(entry);
	//m_WZphysD3PD->b_mu_calo_truth_phi->GetEntry(entry);
	//m_WZphysD3PD->b_mu_calo_truth_type->GetEntry(entry);
	//m_WZphysD3PD->b_mu_calo_truth_status->GetEntry(entry);
	//m_WZphysD3PD->b_mu_calo_truth_barcode->GetEntry(entry);
	//m_WZphysD3PD->b_mu_calo_truth_mothertype->GetEntry(entry);
	//m_WZphysD3PD->b_mu_calo_truth_motherbarcode->GetEntry(entry);
	//m_WZphysD3PD->b_mu_calo_truth_matched->GetEntry(entry);
	
	//m_WZphysD3PD->b_MET_RefFinal_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefFinal_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefFinal_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Cryo_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Cryo_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Cryo_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefEle_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefEle_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefEle_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefJet_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefJet_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefJet_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_SoftJets_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_SoftJets_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_SoftJets_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefMuon_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefMuon_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefMuon_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefMuon_Staco_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefMuon_Staco_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefMuon_Staco_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefMuon_Muid_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefMuon_Muid_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefMuon_Muid_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefGamma_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefGamma_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefGamma_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefTau_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefTau_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefTau_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CellOut_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CellOut_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CellOut_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Track_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Track_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Track_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefFinal_e//m_etx->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefFinal_e//m_ety->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefFinal_e//m_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefFinal_e//m_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefFinal_e//m_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefEle_e//m_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefEle_e//m_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefEle_e//m_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefJet_e//m_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefJet_e//m_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefJet_e//m_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_SoftJets_e//m_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_SoftJets_e//m_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_SoftJets_e//m_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefMuon_e//m_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefMuon_e//m_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefMuon_e//m_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefMuon_Track_e//m_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefMuon_Track_e//m_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefMuon_Track_e//m_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefGamma_e//m_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefGamma_e//m_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefGamma_e//m_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefTau_e//m_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefTau_e//m_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefTau_e//m_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CellOut_e//m_etx->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CellOut_e//m_ety->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CellOut_e//m_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CellOut_e//m_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CellOut_e//m_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Muon_Isol_Staco_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Muon_Isol_Staco_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Muon_Isol_Staco_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Muon_NonIsol_Staco_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Muon_NonIsol_Staco_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Muon_NonIsol_Staco_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Muon_Total_Staco_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Muon_Total_Staco_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Muon_Total_Staco_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Muon_Isol_Muid_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Muon_Isol_Muid_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Muon_Isol_Muid_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Muon_NonIsol_Muid_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Muon_NonIsol_Muid_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Muon_NonIsol_Muid_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Muon_Total_Muid_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Muon_Total_Muid_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Muon_Total_Muid_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_MuonBoy_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_MuonBoy_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_MuonBoy_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefMuon_Track_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefMuon_Track_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefMuon_Track_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefMuon_Track_Staco_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefMuon_Track_Staco_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefMuon_Track_Staco_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefMuon_Track_Muid_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefMuon_Track_Muid_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_RefMuon_Track_Muid_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CryoCone_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CryoCone_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CryoCone_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Final_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Final_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Final_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_MuonBoy_Spectro_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_MuonBoy_Spectro_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_MuonBoy_Spectro_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_MuonBoy_Track_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_MuonBoy_Track_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_MuonBoy_Track_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_MuonMuid_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_MuonMuid_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_MuonMuid_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Muid_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Muid_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Muid_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Muid_Spectro_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Muid_Spectro_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Muid_Spectro_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Muid_Track_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Muid_Track_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Muid_Track_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Muon_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Muon_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Muon_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_TopoObj_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_TopoObj_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_TopoObj_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopoObj_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopoObj_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopoObj_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Topo_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Topo_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Topo_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Topo_SUMET_EMFrac->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Topo_etx_PEMB->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Topo_ety_PEMB->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Topo_sumet_PEMB->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Topo_phi_PEMB->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Topo_etx_EMB->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Topo_ety_EMB->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Topo_sumet_EMB->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Topo_phi_EMB->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Topo_etx_PEMEC->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Topo_ety_PEMEC->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Topo_sumet_PEMEC->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Topo_phi_PEMEC->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Topo_etx_EME->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Topo_ety_EME->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Topo_sumet_EME->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Topo_phi_EME->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Topo_etx_TILE->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Topo_ety_TILE->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Topo_sumet_TILE->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Topo_phi_TILE->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Topo_etx_HEC->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Topo_ety_HEC->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Topo_sumet_HEC->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Topo_phi_HEC->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Topo_etx_FCAL->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Topo_ety_FCAL->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Topo_sumet_FCAL->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Topo_phi_FCAL->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Topo_nCell_PEMB->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Topo_nCell_EMB->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Topo_nCell_PEMEC->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Topo_nCell_EME->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Topo_nCell_TILE->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Topo_nCell_HEC->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Topo_nCell_FCAL->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Topo_etx_CentralReg->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Topo_ety_CentralReg->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Topo_sumet_CentralReg->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Topo_phi_CentralReg->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Topo_etx_EndcapRegion->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Topo_ety_EndcapRegion->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Topo_sumet_EndcapRegion->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Topo_phi_EndcapRegion->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Topo_etx_ForwardReg->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Topo_ety_ForwardReg->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Topo_sumet_ForwardReg->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Topo_phi_ForwardReg->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CorrTopo_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CorrTopo_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CorrTopo_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CorrTopo_SUMET_EMFrac->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CorrTopo_etx_PEMB->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CorrTopo_ety_PEMB->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CorrTopo_sumet_PEMB->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CorrTopo_phi_PEMB->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CorrTopo_etx_EMB->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CorrTopo_ety_EMB->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CorrTopo_sumet_EMB->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CorrTopo_phi_EMB->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CorrTopo_etx_PEMEC->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CorrTopo_ety_PEMEC->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CorrTopo_sumet_PEMEC->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CorrTopo_phi_PEMEC->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CorrTopo_etx_EME->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CorrTopo_ety_EME->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CorrTopo_sumet_EME->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CorrTopo_phi_EME->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CorrTopo_etx_TILE->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CorrTopo_ety_TILE->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CorrTopo_sumet_TILE->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CorrTopo_phi_TILE->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CorrTopo_etx_HEC->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CorrTopo_ety_HEC->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CorrTopo_sumet_HEC->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CorrTopo_phi_HEC->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CorrTopo_etx_FCAL->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CorrTopo_ety_FCAL->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CorrTopo_sumet_FCAL->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CorrTopo_phi_FCAL->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CorrTopo_nCell_PEMB->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CorrTopo_nCell_EMB->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CorrTopo_nCell_PEMEC->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CorrTopo_nCell_EME->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CorrTopo_nCell_TILE->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CorrTopo_nCell_HEC->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CorrTopo_nCell_FCAL->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CorrTopo_etx_CentralReg->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CorrTopo_ety_CentralReg->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CorrTopo_sumet_CentralReg->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CorrTopo_phi_CentralReg->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CorrTopo_etx_EndcapRegion->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CorrTopo_ety_EndcapRegion->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CorrTopo_sumet_EndcapRegion->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CorrTopo_phi_EndcapRegion->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CorrTopo_etx_ForwardReg->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CorrTopo_ety_ForwardReg->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CorrTopo_sumet_ForwardReg->GetEntry(entry);
	//m_WZphysD3PD->b_MET_CorrTopo_phi_ForwardReg->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopo_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopo_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopo_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopo_SUMET_EMFrac->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopo_etx_PEMB->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopo_ety_PEMB->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopo_sumet_PEMB->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopo_phi_PEMB->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopo_etx_EMB->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopo_ety_EMB->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopo_sumet_EMB->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopo_phi_EMB->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopo_etx_PEMEC->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopo_ety_PEMEC->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopo_sumet_PEMEC->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopo_phi_PEMEC->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopo_etx_EME->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopo_ety_EME->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopo_sumet_EME->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopo_phi_EME->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopo_etx_TILE->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopo_ety_TILE->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopo_sumet_TILE->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopo_phi_TILE->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopo_etx_HEC->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopo_ety_HEC->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopo_sumet_HEC->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopo_phi_HEC->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopo_etx_FCAL->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopo_ety_FCAL->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopo_sumet_FCAL->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopo_phi_FCAL->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopo_nCell_PEMB->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopo_nCell_EMB->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopo_nCell_PEMEC->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopo_nCell_EME->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopo_nCell_TILE->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopo_nCell_HEC->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopo_nCell_FCAL->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopo_etx_CentralReg->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopo_ety_CentralReg->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopo_sumet_CentralReg->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopo_phi_CentralReg->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopo_etx_EndcapRegion->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopo_ety_EndcapRegion->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopo_sumet_EndcapRegion->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopo_phi_EndcapRegion->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopo_etx_ForwardReg->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopo_ety_ForwardReg->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopo_sumet_ForwardReg->GetEntry(entry);
	//m_WZphysD3PD->b_MET_LocHadTopo_phi_ForwardReg->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Calib_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Calib_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Calib_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Calib_SUMET_EMFrac->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Calib_etx_PEMB->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Calib_ety_PEMB->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Calib_sumet_PEMB->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Calib_phi_PEMB->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Calib_etx_EMB->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Calib_ety_EMB->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Calib_sumet_EMB->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Calib_phi_EMB->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Calib_etx_PEMEC->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Calib_ety_PEMEC->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Calib_sumet_PEMEC->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Calib_phi_PEMEC->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Calib_etx_EME->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Calib_ety_EME->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Calib_sumet_EME->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Calib_phi_EME->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Calib_etx_TILE->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Calib_ety_TILE->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Calib_sumet_TILE->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Calib_phi_TILE->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Calib_etx_HEC->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Calib_ety_HEC->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Calib_sumet_HEC->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Calib_phi_HEC->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Calib_etx_FCAL->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Calib_ety_FCAL->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Calib_sumet_FCAL->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Calib_phi_FCAL->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Calib_nCell_PEMB->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Calib_nCell_EMB->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Calib_nCell_PEMEC->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Calib_nCell_EME->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Calib_nCell_TILE->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Calib_nCell_HEC->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Calib_nCell_FCAL->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Calib_etx_CentralReg->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Calib_ety_CentralReg->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Calib_sumet_CentralReg->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Calib_phi_CentralReg->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Calib_etx_EndcapRegion->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Calib_ety_EndcapRegion->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Calib_sumet_EndcapRegion->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Calib_phi_EndcapRegion->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Calib_etx_ForwardReg->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Calib_ety_ForwardReg->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Calib_sumet_ForwardReg->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Calib_phi_ForwardReg->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Truth_NonInt_etx->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Truth_NonInt_ety->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Truth_NonInt_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Truth_NonInt_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Truth_NonInt_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Truth_Int_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Truth_IntCentral_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Truth_IntFwd_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Truth_IntOutCover_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Truth_IntMuons_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Truth_Int_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Truth_IntCentral_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Truth_IntFwd_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Truth_IntOutCover_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Truth_IntMuons_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Truth_Int_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Truth_IntCentral_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Truth_IntFwd_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Truth_IntOutCover_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Truth_IntMuons_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Truth_PileUp_NonInt_etx->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Truth_PileUp_NonInt_ety->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Truth_PileUp_NonInt_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Truth_PileUp_NonInt_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Truth_PileUp_NonInt_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Truth_PileUp_Int_etx->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Truth_PileUp_Int_ety->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Truth_PileUp_IntCentral_etx->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Truth_PileUp_IntCentral_ety->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Truth_PileUp_IntFwd_etx->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Truth_PileUp_IntFwd_ety->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Truth_PileUp_IntOutCover_etx->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Truth_PileUp_IntOutCover_ety->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Truth_PileUp_IntMuons_etx->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Truth_PileUp_IntMuons_ety->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Truth_PileUp_Int_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Truth_PileUp_IntCentral_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Truth_PileUp_IntFwd_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Truth_PileUp_IntOutCover_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Truth_PileUp_IntMuons_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Truth_PileUp_Int_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Truth_PileUp_IntCentral_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Truth_PileUp_IntFwd_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Truth_PileUp_IntOutCover_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Truth_PileUp_IntMuons_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Truth_PileUp_Int_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Truth_PileUp_IntCentral_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Truth_PileUp_IntFwd_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Truth_PileUp_IntOutCover_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_Truth_PileUp_IntMuons_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_DM_Crack1_etx->GetEntry(entry);
	//m_WZphysD3PD->b_MET_DM_Crack1_ety->GetEntry(entry);
	//m_WZphysD3PD->b_MET_DM_Crack1_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_DM_Crack1_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_DM_Crack1_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_DM_Crack2_etx->GetEntry(entry);
	//m_WZphysD3PD->b_MET_DM_Crack2_ety->GetEntry(entry);
	//m_WZphysD3PD->b_MET_DM_Crack2_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_DM_Crack2_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_DM_Crack2_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_DM_All_etx->GetEntry(entry);
	//m_WZphysD3PD->b_MET_DM_All_ety->GetEntry(entry);
	//m_WZphysD3PD->b_MET_DM_All_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_DM_All_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_DM_All_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_MET_DM_Cryo_etx->GetEntry(entry);
	//m_WZphysD3PD->b_MET_DM_Cryo_ety->GetEntry(entry);
	//m_WZphysD3PD->b_MET_DM_Cryo_phi->GetEntry(entry);
	//m_WZphysD3PD->b_MET_DM_Cryo_et->GetEntry(entry);
	//m_WZphysD3PD->b_MET_DM_Cryo_sumet->GetEntry(entry);
	//m_WZphysD3PD->b_METJetsInfo_JetPtWeightedEventEMFraction->GetEntry(entry);
	//m_WZphysD3PD->b_METJetsInfo_JetPtWeightedNumAssociatedTracks->GetEntry(entry);
	//m_WZphysD3PD->b_METJetsInfo_JetPtWeightedSize->GetEntry(entry);
	//m_WZphysD3PD->b_METJetsInfo_LeadingJetEt->GetEntry(entry);
	//m_WZphysD3PD->b_METJetsInfo_LeadingJetEta->GetEntry(entry);
	
	m_WZphysD3PD->b_vxp_n->GetEntry(entry);
	m_WZphysD3PD->b_vxp_x->GetEntry(entry);
	m_WZphysD3PD->b_vxp_y->GetEntry(entry);
	m_WZphysD3PD->b_vxp_z->GetEntry(entry);
	//m_WZphysD3PD->b_vxp_cov_x->GetEntry(entry);
	//m_WZphysD3PD->b_vxp_cov_y->GetEntry(entry);
	//m_WZphysD3PD->b_vxp_cov_z->GetEntry(entry);
	//m_WZphysD3PD->b_vxp_chi2->GetEntry(entry);
	//m_WZphysD3PD->b_vxp_ndof->GetEntry(entry);
	//m_WZphysD3PD->b_vxp_px->GetEntry(entry);
	//m_WZphysD3PD->b_vxp_py->GetEntry(entry);
	//m_WZphysD3PD->b_vxp_pz->GetEntry(entry);
	//m_WZphysD3PD->b_vxp_E->GetEntry(entry);
	//m_WZphysD3PD->b_vxp_m->GetEntry(entry);
	m_WZphysD3PD->b_vxp_nTracks->GetEntry(entry);
	//m_WZphysD3PD->b_vxp_sumPt->GetEntry(entry);
	m_WZphysD3PD->b_vxp_type->GetEntry(entry);
	//m_WZphysD3PD->b_vxp_trk_n->GetEntry(entry);
	//m_WZphysD3PD->b_vxp_trk_index->GetEntry(entry);
	
	if(m_isMC)
	{
		m_WZphysD3PD->b_muonTruth_n->GetEntry(entry);
		m_WZphysD3PD->b_muonTruth_pt->GetEntry(entry);
		m_WZphysD3PD->b_muonTruth_m->GetEntry(entry);
		m_WZphysD3PD->b_muonTruth_eta->GetEntry(entry);
		m_WZphysD3PD->b_muonTruth_phi->GetEntry(entry);
		m_WZphysD3PD->b_muonTruth_charge->GetEntry(entry);
		m_WZphysD3PD->b_muonTruth_PDGID->GetEntry(entry);
		m_WZphysD3PD->b_muonTruth_barcode->GetEntry(entry);
		m_WZphysD3PD->b_muonTruth_type->GetEntry(entry);
		m_WZphysD3PD->b_muonTruth_origin->GetEntry(entry);
		
		m_WZphysD3PD->b_mcevt_n->GetEntry(entry);
		m_WZphysD3PD->b_mcevt_signal_process_id->GetEntry(entry);
		m_WZphysD3PD->b_mcevt_event_number->GetEntry(entry);
		m_WZphysD3PD->b_mcevt_event_scale->GetEntry(entry);
		m_WZphysD3PD->b_mcevt_alphaQCD->GetEntry(entry);
		m_WZphysD3PD->b_mcevt_alphaQED->GetEntry(entry);
		m_WZphysD3PD->b_mcevt_pdf_id1->GetEntry(entry);
		m_WZphysD3PD->b_mcevt_pdf_id2->GetEntry(entry);
		m_WZphysD3PD->b_mcevt_pdf_x1->GetEntry(entry);
		m_WZphysD3PD->b_mcevt_pdf_x2->GetEntry(entry);
		m_WZphysD3PD->b_mcevt_pdf_scale->GetEntry(entry);
		m_WZphysD3PD->b_mcevt_pdf1->GetEntry(entry);
		m_WZphysD3PD->b_mcevt_pdf2->GetEntry(entry);
		m_WZphysD3PD->b_mcevt_weight->GetEntry(entry);

		//m_WZphysD3PD->b_mc_n->GetEntry(entry);
		//m_WZphysD3PD->b_mc_pt->GetEntry(entry);
		//m_WZphysD3PD->b_mc_m->GetEntry(entry);
		//m_WZphysD3PD->b_mc_eta->GetEntry(entry);
		//m_WZphysD3PD->b_mc_phi->GetEntry(entry);
		//m_WZphysD3PD->b_mc_status->GetEntry(entry);
		//m_WZphysD3PD->b_mc_barcode->GetEntry(entry);
		//m_WZphysD3PD->b_mc_parents->GetEntry(entry);
		//m_WZphysD3PD->b_mc_children->GetEntry(entry);
		//m_WZphysD3PD->b_mc_pdgId->GetEntry(entry);
		//m_WZphysD3PD->b_mc_charge->GetEntry(entry);
		//m_WZphysD3PD->b_mc_vx_x->GetEntry(entry);
		//m_WZphysD3PD->b_mc_vx_y->GetEntry(entry);
		//m_WZphysD3PD->b_mc_vx_z->GetEntry(entry);
		//m_WZphysD3PD->b_mc_child_index->GetEntry(entry);
		//m_WZphysD3PD->b_mc_parent_index->GetEntry(entry);
	}
	
	//m_WZphysD3PD->b_trig_L1_TAV->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_passedPhysics->GetEntry(entry);
	//m_WZphysD3PD->b_trig_EF_passedPhysics->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L1_TBP->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L1_TAP->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_passedRaw->GetEntry(entry);
	//m_WZphysD3PD->b_trig_EF_passedRaw->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_truncated->GetEntry(entry);
	//m_WZphysD3PD->b_trig_EF_truncated->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_resurrected->GetEntry(entry);
	//m_WZphysD3PD->b_trig_EF_resurrected->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_passedThrough->GetEntry(entry);
	//m_WZphysD3PD->b_trig_EF_passedThrough->GetEntry(entry);
	//m_WZphysD3PD->b_trig_DB_SMK->GetEntry(entry);
	//m_WZphysD3PD->b_trig_DB_L1PSK->GetEntry(entry);
	//m_WZphysD3PD->b_trig_DB_HLTPSK->GetEntry(entry);
	//m_WZphysD3PD->b_trig_bgCode->GetEntry(entry);
	
	m_WZphysD3PD->b_trig_L1_mu_n->GetEntry(entry);
	m_WZphysD3PD->b_trig_L1_mu_pt->GetEntry(entry);
	m_WZphysD3PD->b_trig_L1_mu_eta->GetEntry(entry);
	m_WZphysD3PD->b_trig_L1_mu_phi->GetEntry(entry);
	m_WZphysD3PD->b_trig_L1_mu_thrName->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_muonfeature_n->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_muonfeature_pt->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_muonfeature_eta->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_muonfeature_phi->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_muonfeaturedetails_n->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_combmuonfeature_n->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_combmuonfeature_pt->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_combmuonfeature_eta->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_combmuonfeature_phi->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_combmuonfeature_idscantrk_index->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_combmuonfeature_sitracktrk_index->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_isomuonfeature_n->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_isomuonfeature_pt->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_isomuonfeature_eta->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_isomuonfeature_phi->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_isomuonfeature_EtInnerConeEC ->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_isomuonfeature_EtOuterConeEC->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_isomuonfeature_EtInnerConeHC->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_isomuonfeature_EtOuterConeHC->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_isomuonfeature_NTracksCone->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_isomuonfeature_SumPtTracksCone->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_isomuonfeature_PtMuTracksCone->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_tilemufeature_n->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_tilemufeature_eta->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_tilemufeature_phi->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_tiletrackmufeature_n->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_tiletrackmufeature_pt->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_tiletrackmufeature_eta->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_tiletrackmufeature_phi->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_tiletrackmufeature_tilemu_index->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_tiletrackmufeature_idtrk_algorithmId->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_tiletrackmufeature_idtrk_trackStatus->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_tiletrackmufeature_idtrk_chi2Ndof->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_tiletrackmufeature_idtrk_idtrkfitpar_a0->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_tiletrackmufeature_idtrk_idtrkfitpar_z0->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_tiletrackmufeature_idtrk_idtrkfitpar_phi0->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_tiletrackmufeature_idtrk_idtrkfitpar_eta->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_tiletrackmufeature_idtrk_idtrkfitpar_pt->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_tiletrackmufeature_idtrk_idtrkfitpar_hasidtrkfitpar->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_tiletrackmufeature_idtrk_hasidtrk->GetEntry(entry);
	m_WZphysD3PD->b_trig_EF_trigmuonef_n->GetEntry(entry);
	m_WZphysD3PD->b_trig_EF_trigmuonef_track_n->GetEntry(entry);
	m_WZphysD3PD->b_trig_EF_trigmuonef_track_MuonType->GetEntry(entry);
	m_WZphysD3PD->b_trig_EF_trigmuonef_track_MS_pt->GetEntry(entry);
	m_WZphysD3PD->b_trig_EF_trigmuonef_track_MS_eta->GetEntry(entry);
	m_WZphysD3PD->b_trig_EF_trigmuonef_track_MS_phi->GetEntry(entry);
	m_WZphysD3PD->b_trig_EF_trigmuonef_track_MS_hasMS->GetEntry(entry);
	m_WZphysD3PD->b_trig_EF_trigmuonef_track_SA_pt->GetEntry(entry);
	m_WZphysD3PD->b_trig_EF_trigmuonef_track_SA_eta->GetEntry(entry);
	m_WZphysD3PD->b_trig_EF_trigmuonef_track_SA_phi->GetEntry(entry);
	m_WZphysD3PD->b_trig_EF_trigmuonef_track_SA_hasSA->GetEntry(entry);
	m_WZphysD3PD->b_trig_EF_trigmuonef_track_CB_pt->GetEntry(entry);
	m_WZphysD3PD->b_trig_EF_trigmuonef_track_CB_eta->GetEntry(entry);
	m_WZphysD3PD->b_trig_EF_trigmuonef_track_CB_phi->GetEntry(entry);
	m_WZphysD3PD->b_trig_EF_trigmuonef_track_CB_hasCB->GetEntry(entry);
	m_WZphysD3PD->b_trig_EF_trigmugirl_n->GetEntry(entry);
	m_WZphysD3PD->b_trig_EF_trigmugirl_track_n->GetEntry(entry);
	m_WZphysD3PD->b_trig_EF_trigmugirl_track_MuonType->GetEntry(entry);
	m_WZphysD3PD->b_trig_EF_trigmugirl_track_MS_pt->GetEntry(entry);
	m_WZphysD3PD->b_trig_EF_trigmugirl_track_MS_eta->GetEntry(entry);
	m_WZphysD3PD->b_trig_EF_trigmugirl_track_MS_phi->GetEntry(entry);
	m_WZphysD3PD->b_trig_EF_trigmugirl_track_MS_hasMS->GetEntry(entry);
	m_WZphysD3PD->b_trig_EF_trigmugirl_track_SA_pt->GetEntry(entry);
	m_WZphysD3PD->b_trig_EF_trigmugirl_track_SA_eta->GetEntry(entry);
	m_WZphysD3PD->b_trig_EF_trigmugirl_track_SA_phi->GetEntry(entry);
	m_WZphysD3PD->b_trig_EF_trigmugirl_track_SA_hasSA->GetEntry(entry);
	m_WZphysD3PD->b_trig_EF_trigmugirl_track_CB_pt->GetEntry(entry);
	m_WZphysD3PD->b_trig_EF_trigmugirl_track_CB_eta->GetEntry(entry);
	m_WZphysD3PD->b_trig_EF_trigmugirl_track_CB_phi->GetEntry(entry);
	m_WZphysD3PD->b_trig_EF_trigmugirl_track_CB_hasCB->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_sitrack_muon_n->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_sitrack_muon_algorithmId->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_sitrack_muon_trackStatus->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_sitrack_muon_chi2Ndof->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_sitrack_muon_a0->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_sitrack_muon_z0->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_sitrack_muon_phi0->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_sitrack_muon_eta->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_sitrack_muon_pt->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_idscan_muon_n->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_idscan_muon_algorithmId->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_idscan_muon_trackStatus->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_idscan_muon_chi2Ndof->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_idscan_muon_a0->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_idscan_muon_z0->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_idscan_muon_phi0->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_idscan_muon_eta->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_idscan_muon_pt->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_sitrack_isomuon_n->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_sitrack_isomuon_algorithmId->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_sitrack_isomuon_trackStatus->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_sitrack_isomuon_chi2Ndof->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_sitrack_isomuon_a0->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_sitrack_isomuon_z0->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_sitrack_isomuon_phi0->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_sitrack_isomuon_eta->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_sitrack_isomuon_pt->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_idscan_isomuon_n->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_idscan_isomuon_algorithmId->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_idscan_isomuon_trackStatus->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_idscan_isomuon_chi2Ndof->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_idscan_isomuon_a0->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_idscan_isomuon_z0->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_idscan_isomuon_phi0->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_idscan_isomuon_eta->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_idscan_isomuon_pt->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_L2_mu_n->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_L2_mu_type->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_L2_mu_lastStep->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_L2_mu_MuonFeature->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_L2_mu_MuonFeatureStatus->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_L2_mu_MuonFeatureDetails->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_L2_mu_MuonFeatureDetailsStatus->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_L2_mu_CombinedMuonFeature->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_L2_mu_CombinedMuonFeatureStatus->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_L2_mu_IsoMuonFeature->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_L2_mu_IsoMuonFeatureStatus->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_L2_mu_Muon_ROI->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_L2_mu_Muon_ROIStatus->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_L2_mu_TrigInDetTrackCollection_TrigSiTrack_Muon->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_L2_mu_TrigInDetTrackCollection_TrigSiTrack_MuonStatus->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_L2_mu_TrigInDetTrackCollection_TrigIDSCAN_Muon->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_L2_mu_TrigInDetTrackCollection_TrigIDSCAN_MuonStatus->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_L2_mu_TrigInDetTrackCollection_TrigSiTrack_muonIso->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_L2_mu_TrigInDetTrackCollection_TrigSiTrack_muonIsoStatus->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_L2_mu_TrigInDetTrackCollection_TrigIDSCAN_muonIso->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_L2_mu_TrigInDetTrackCollection_TrigIDSCAN_muonIsoStatus->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_L2_TileMu_n->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_L2_TileMu_type->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_L2_TileMu_lastStep->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_L2_TileMu_TileMuFeature->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_L2_TileMu_TileMuFeatureStatus->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_L2_TileMu_TileTrackMuFeature->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_L2_TileMu_TileTrackMuFeatureStatus->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_L2_TileMu_Muon_ROI->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_L2_TileMu_Muon_ROIStatus->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_L2_TileMu_TrigInDetTrackCollection_TrigSiTrack_Tile->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_L2_TileMu_TrigInDetTrackCollection_TrigSiTrack_TileStatus->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_L2_TileMu_TrigInDetTrackCollection_TrigIDSCAN_Tile->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_L2_TileMu_TrigInDetTrackCollection_TrigIDSCAN_TileStatus->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_EF_mu_n->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_EF_mu_type->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_EF_mu_lastStep->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_EF_mu_Muon_ROI->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_EF_mu_Muon_ROIStatus->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_EF_mu_TrackCollection_InDetTrigTrackSlimmer_Muon_EFID->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_EF_mu_TrackCollection_InDetTrigTrackSlimmer_Muon_EFIDStatus->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_EF_mu_TrigMuonEFInfoContainer->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_EF_mu_TrigMuonEFInfoContainerStatus->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_EF_mu_TrigMuonEFInfoContainer_MuGirl->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_EF_mu_TrigMuonEFInfoContainer_MuGirlStatus->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_EF_mu_TrigMuonEFInfoContainer_MuTagIMO_EF->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_EF_mu_TrigMuonEFInfoContainer_MuTagIMO_EFStatus->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_EF_TileMu_n->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_EF_TileMu_type->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_EF_TileMu_lastStep->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_EF_TileMu_Muon_ROI->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_EF_TileMu_Muon_ROIStatus->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_EF_TileMu_TrigMuonEFContainer->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_EF_TileMu_TrigMuonEFContainerStatus->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_EF_TileMu_TrigMuonEFInfoContainer->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_EF_TileMu_TrigMuonEFInfoContainerStatus->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_EF_TileMu_TrigMuonEFInfoContainer_MuGirl->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_EF_TileMu_TrigMuonEFInfoContainer_MuGirlStatus->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_EF_TileMu_TrigMuonEFInfoContainer_MuTagIMO_EF->GetEntry(entry);
	//m_WZphysD3PD->b_trig_RoI_EF_TileMu_TrigMuonEFInfoContainer_MuTagIMO_EFStatus->GetEntry(entry);
	
	//m_WZphysD3PD->b_trig_L2_met_MEx->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_met_MEy->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_met_MEz->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_met_sumEt->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_met_sumE->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_met_flag->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_met_nameOfComponent->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_met_MExComponent->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_met_MEyComponent->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_met_MEzComponent->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_met_sumEtComponent->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_met_sumEComponent->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_met_componentCalib0->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_met_componentCalib1->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_met_sumOfSigns->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_met_usedChannels->GetEntry(entry);
	//m_WZphysD3PD->b_trig_L2_met_status->GetEntry(entry);
	//m_WZphysD3PD->b_trig_EF_met_MEx->GetEntry(entry);
	//m_WZphysD3PD->b_trig_EF_met_MEy->GetEntry(entry);
	//m_WZphysD3PD->b_trig_EF_met_MEz->GetEntry(entry);
	//m_WZphysD3PD->b_trig_EF_met_sumEt->GetEntry(entry);
	//m_WZphysD3PD->b_trig_EF_met_sumE->GetEntry(entry);
	//m_WZphysD3PD->b_trig_EF_met_flag->GetEntry(entry);
	//m_WZphysD3PD->b_trig_EF_met_nameOfComponent->GetEntry(entry);
	//m_WZphysD3PD->b_trig_EF_met_MExComponent->GetEntry(entry);
	//m_WZphysD3PD->b_trig_EF_met_MEyComponent->GetEntry(entry);
	//m_WZphysD3PD->b_trig_EF_met_MEzComponent->GetEntry(entry);
	//m_WZphysD3PD->b_trig_EF_met_sumEtComponent->GetEntry(entry);
	//m_WZphysD3PD->b_trig_EF_met_sumEComponent->GetEntry(entry);
	//m_WZphysD3PD->b_trig_EF_met_componentCalib0->GetEntry(entry);
	//m_WZphysD3PD->b_trig_EF_met_componentCalib1->GetEntry(entry);
	//m_WZphysD3PD->b_trig_EF_met_sumOfSigns->GetEntry(entry);
	//m_WZphysD3PD->b_trig_EF_met_usedChannels->GetEntry(entry);
	//m_WZphysD3PD->b_trig_EF_met_status->GetEntry(entry);
}

