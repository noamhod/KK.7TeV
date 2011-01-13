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
		
		if(m_RunType=="local")
		{
			str_list = checkANDsetFilepath("PWD", "/../conf/mc_local_dataset_"+sMCsample+".list");
			str_dir = checkANDsetFilepath("PWD", "/mc_local_datasetdir/");
			if(sMCsample=="mcWZphys_localTests") str_dir = checkANDsetFilepath("PWD", "/");
			str_tree = checkANDsetFilepath("PWD", "/../data/mcLocalTree_"+sMCsample+".root");
			str_hist = checkANDsetFilepath("PWD", "/../data/mcLocalControl_"+sMCsample+".root");
		}
		else if(m_RunType=="local_noskim")
		{
			str_list = checkANDsetFilepath("PWD", "/../conf/mc_localnoskim_dataset_"+sMCsample+".list");
			str_dir = checkANDsetFilepath("PWD", "/mc_localnoskim_datasetdir/");
			str_hist = checkANDsetFilepath("PWD", "/../data/mcLocalnkimControl_"+sMCsample+".root");
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

	m_WZphysD3PD = new WZphysD3PD( m_chain );

	if(m_RunType!="local_noskim") m_treefile = new TFile( str_tree.c_str(), "RECREATE");
	else m_treefile = NULL;
	
	m_histfile = new TFile( str_hist.c_str(), "RECREATE");
	m_histfile->cd();

	string str1 = checkANDsetFilepath("PWD", "/../conf/cutFlow.cuts");
	string str2 = checkANDsetFilepath("PWD", "/../conf/dataPeriods.data");
	
	m_analysis = new analysis(m_RunType, m_muRecAlgo, m_isMC,
							  m_WZphysD3PD, m_GRL, m_treefile,
							  str1, str2, "interestingEvents.dump" );

	book();

	if(m_RunType!="local_noskim") m_treefile->cd();
}

void analysisLocalControl::finalize()
{
	//m_analysis->m_WZphysD3PDmaker->m_tree->Print();
	// tree
	// the tree will split into multiple files
	// since in digestTree class there is the
	// following statement m_tree->SetMaxTreeSize(50000000);
	// i.e., 50Mb per file
	if(m_RunType!="local_noskim")
	{
		m_treefile = m_analysis->m_WZphysD3PDmaker->m_tree->GetCurrentFile();
		m_treefile->cd();
		m_analysis->m_WZphysD3PDmaker->m_tree->Write();
		m_treefile->Write();
		m_treefile->Close();
	}
	
	// histos
	m_histfile->Write();
	m_histfile->Close();
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
		l64t_nb = m_WZphysD3PD->fChain->GetEntry(l64t_jentry);
		l64t_nbytes += l64t_nb;
		// if (Cut(l64t_ientry) < 0) continue;
		
		if(l64t_jentry%100000==0)   cout << "jentry=" << l64t_jentry << "\t ientry=" << l64t_ientry << "\trun=" << m_WZphysD3PD->RunNumber << "\tlumiblock=" << m_WZphysD3PD->lbn << endl;
		if(l64t_jentry%l64t_mod==0) m_analysis->printCutFlowNumbers(l64t_nentries);
		
		if(l64t_jentry%1000==0)
		{
			gSystem->GetProcInfo(&pi);
			vResMemory.push_back((double)pi.fMemResident);
			vVirMemory.push_back((double)pi.fMemVirtual);
			vEntries.push_back((int)l64t_jentry);
		}
		
		///////////////////////////////////////////////////////////////////////////////////
		//if( m_analysis->getPeriodName(m_WZphysD3PD->RunNumber)=="I1" ) break; /////////
		///////////////////////////////////////////////////////////////////////////////////
		
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
	
	//cout << "stopped at period=" << m_analysis->getPeriodName(m_WZphysD3PD->RunNumber) << ", run=" << m_WZphysD3PD->RunNumber << ", lbn=" << m_WZphysD3PD->lbn << endl;
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
		l64t_nb = m_WZphysD3PD->fChain->GetEntry(l64t_jentry);
		l64t_nbytes += l64t_nb;
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
		m_WZphysD3PD->fChain->GetEntry(l64t_jmid);
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
		l64t_nb = m_WZphysD3PD->fChain->GetEntry(l64t_jentry);
		l64t_nbytes += l64t_nb;
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




void analysisLocalControl::getCandidates(string sFilePath)
{
	fstream file;
	file.open( sFilePath.c_str() );

	string sLine = "";
	vector<double> values;
	double tmpVal = 0.;

	int nLinesRead = 0;

	while(!file.eof())
	{
		getline(file,sLine);

		if(sLine == "") continue;
		cout << sLine << endl;

		// parse the line:
		if(values.size()>0) values.clear();
		stringstream strm(sLine);
		while(!strm.eof())
		{
			strm >> tmpVal;
			values.push_back(tmpVal);
		}
		
		for(int i=0 ; i<(int)values.size() ; i++)
		{
			// encoding:
			// 0=RN
			// 1=LB
			// 2=EN
			// 3=Mass(CB)
			// 4=Mass(ID)
			// 5=Mass(ME)
			// 6=pT1
			// 7=pT2
			switch(i)
			{
				case 0: runNumber.push_back( values[i] ); break;
				case 1: lumiBlock.push_back( values[i] ); break;
				case 2: eventNumber.push_back( values[i] ); break;
				case 3: mass_cb.push_back( values[i] ); break;
				case 4: mass_id.push_back( values[i] ); break;
				case 5: mass_me.push_back( values[i] ); break;
				case 6: pT1.push_back( values[i] ); break;
				case 7: pT2.push_back( values[i] ); break;
				default: break;
			}
		}
		nLinesRead++;
	}
	cout << "read " << nLinesRead << " lines" << endl;
}

bool analysisLocalControl::matchCandidates()
{	
	for(int rn=0 ; rn<(int)runNumber.size() ; rn++)
	{
		if( runNumber[rn] != (double)m_WZphysD3PD->RunNumber ) continue;
		for(int lb=0 ; lb<(int)lumiBlock.size() ; lb++)
		{
			if( lumiBlock[lb] != (double)m_WZphysD3PD->lbn ) continue;
			for(int en=0 ; en<(int)eventNumber.size() ; en++)
			{
				if( eventNumber[en] != (double)m_WZphysD3PD->EventNumber ) continue;			
				cout << "match !" << endl;
				return true;
			}
		}
	}
	return false;
}

void analysisLocalControl::loopCandidates()
{
	if (m_WZphysD3PD->fChain == 0)  return;

	l64t_nentries = m_WZphysD3PD->fChain->GetEntriesFast();
	l64t_nbytes = 0;
	l64t_nb = 0;

	// read the external list of Z candidates
	int nMatched = 0;
	string sFilePath = checkANDsetFilepath("PWD", "/../conf/STACO.cand");
	getCandidates(sFilePath);
	
	for (l64t_jentry=0 ; l64t_jentry<l64t_nentries ; l64t_jentry++)
	{
		l64t_ientry = m_WZphysD3PD->LoadTree(l64t_jentry);
		if (l64t_ientry < 0) break;
		l64t_nb = m_WZphysD3PD->fChain->GetEntry(l64t_jentry);
		l64t_nbytes += l64t_nb;
		
		if(l64t_jentry%1000==0) cout << "jentry=" << l64t_jentry << "\t ientry=" << l64t_ientry << "\trun=" << m_WZphysD3PD->RunNumber << "\tlumiblock=" << m_WZphysD3PD->lbn << "\tnMatched=" << nMatched << endl;
		
		// try to match this event to an entry from the external list
		if( matchCandidates() ) nMatched++;
	}
}
