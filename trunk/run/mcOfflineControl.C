/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "mcOfflineControl.h"


mcOfflineControl::mcOfflineControl()
{
	startTimer();

	initialize();
	
	string str = "";

	//////////////////////////////////////////
	// prompt to chose the MC sample here ////
	string sMCsample = pickMCinputSampe(); ///
	//////////////////////////////////////////
	
	str = checkANDsetFilepath("PWD", "/../conf/offline_mc_dataset_"+sMCsample+".list");
	string strb = checkANDsetFilepath("PWD", "/offline_mc_datasetdir/");
	if(sMCsample=="mcWZphys_localTests") strb = checkANDsetFilepath("PWD", "/");
	makeChain(true, str, strb);

	m_mcOffPhys = new mcOfflinePhysics( m_chain );

	str = checkANDsetFilepath("PWD", "/../data/mcDigestTree_"+sMCsample+".root");
	m_treefile = new TFile( str.c_str(), "RECREATE");
	
	str = checkANDsetFilepath("PWD", "/../data/mcOfflineControl_"+sMCsample+".root");
	m_histfile = new TFile( str.c_str(), "RECREATE");
	m_histfile->cd();
	
	string str1 = checkANDsetFilepath("PWD", "/../conf/cutFlow.cuts");
	string str2 = checkANDsetFilepath("PWD", "/../conf/dataPeriods.data");
	
	m_mcOfflineAnalysis = new mcOfflineAnalysis( m_mcOffPhys, m_treefile, str1, str2, "" );
	
	book();
	
	m_treefile->cd();
}

mcOfflineControl::~mcOfflineControl()
{
	//finalize();
}

void mcOfflineControl::initialize()
{
	// run control
	l64t_nentries = 0;
	l64t_nbytes   = 0;
	l64t_nb       = 0;
	l64t_jentry   = 0;
	l64t_ientry   = 0;

	// pointers
	m_mcOffPhys     = NULL;
	m_mcOfflineAnalysis = NULL;
	m_histfile = NULL;
	m_treefile = NULL;
}

void mcOfflineControl::finalize()
{
	// tree
	// the tree will split into multiple files
	// since in digestTree class there is the
	// following statement m_tree->SetMaxTreeSize(50000000);
	// i.e., 50Mb per file
	m_treefile = m_mcOfflineAnalysis->m_muSkimD3PD->m_tree->GetCurrentFile();
	m_treefile->cd();
	m_mcOfflineAnalysis->m_muSkimD3PD->m_tree->Write();
	m_treefile->Write();
	m_treefile->Close();

	// files
	m_histfile->Write();
	m_histfile->Close();
}

void mcOfflineControl::book()
{
	m_dirNoCuts = m_histfile->mkdir("noCuts");
	m_mcOfflineAnalysis->bookBareHistos(m_dirNoCuts);

	m_dirAllCuts = m_histfile->mkdir("allCuts");
	m_mcOfflineAnalysis->bookHistos(m_dirAllCuts);
	
	m_dirFit = m_histfile->mkdir("fit");
	m_mcOfflineAnalysis->bookFitHistos(m_dirFit);

	m_dirCutFlow = m_histfile->mkdir("cutFlow");
	m_mcOfflineAnalysis->bookHistosMap( m_mcOfflineAnalysis->getCutFlowOrderedMapPtr(), m_mcOfflineAnalysis->getCutFlowTypeOrderedMapPtr(), m_dirCutFlow );
	
	m_dirCutProfile = m_histfile->mkdir("cutsProfile");
	m_mcOfflineAnalysis->bookCutProfileHistosMap( m_mcOfflineAnalysis->getCutFlowOrderedMapPtr(), m_dirCutProfile );

	m_dirPerformance = m_histfile->mkdir("performance");
	
	m_dirAfb = m_histfile->mkdir("Afb");
}

void mcOfflineControl::draw()
{
	m_mcOfflineAnalysis->drawBareHistos(m_dirNoCuts);

	// these calculations must come before drawHistos
	bool isTruth = false;
	m_mcOfflineAnalysis->calculateEfficiency(m_mcOfflineAnalysis->h1_tagNprobe_candidates_pT, m_mcOfflineAnalysis->h1_tagNprobe_succeeded_pT, m_mcOfflineAnalysis->h1_tagNprobe_efficiency_pT, isTruth);
	m_mcOfflineAnalysis->calculateEfficiency(m_mcOfflineAnalysis->h1_tagNprobe_candidates_eta, m_mcOfflineAnalysis->h1_tagNprobe_succeeded_eta, m_mcOfflineAnalysis->h1_tagNprobe_efficiency_eta, isTruth);
	m_mcOfflineAnalysis->calculateEfficiency(m_mcOfflineAnalysis->h1_tagNprobe_candidates_phi, m_mcOfflineAnalysis->h1_tagNprobe_succeeded_phi, m_mcOfflineAnalysis->h1_tagNprobe_efficiency_phi, isTruth);
	isTruth = true;
	m_mcOfflineAnalysis->calculateEfficiency(m_mcOfflineAnalysis->h1_truth_candidates_pT, m_mcOfflineAnalysis->h1_truth_succeeded_pT, m_mcOfflineAnalysis->h1_truth_efficiency_pT, isTruth);
	m_mcOfflineAnalysis->calculateEfficiency(m_mcOfflineAnalysis->h1_truth_candidates_eta, m_mcOfflineAnalysis->h1_truth_succeeded_eta, m_mcOfflineAnalysis->h1_truth_efficiency_eta, isTruth);
	m_mcOfflineAnalysis->calculateEfficiency(m_mcOfflineAnalysis->h1_truth_candidates_phi, m_mcOfflineAnalysis->h1_truth_succeeded_phi, m_mcOfflineAnalysis->h1_truth_efficiency_phi, isTruth);
	
	m_mcOfflineAnalysis->calculateAfb(m_mcOfflineAnalysis->h1_Afb, m_dirAfb);
	
	m_mcOfflineAnalysis->drawHistos(m_dirAllCuts);

	m_mcOfflineAnalysis->drawHistosMap( m_mcOfflineAnalysis->getCutFlowOrderedMapPtr(), m_mcOfflineAnalysis->getCutFlowTypeOrderedMapPtr(), m_dirCutFlow );

	m_mcOfflineAnalysis->drawFitHistos(m_dirFit, m_mcOfflineAnalysis->m_fitROOT->guess, m_mcOfflineAnalysis->m_fitROOT->fitFCN);
	//m_mcOfflineAnalysis->drawFitHistos(m_dirFit, m_mcOfflineAnalysis->m_fitMinuit->guess, m_mcOfflineAnalysis->m_fitMinuit->fitFCN);

	m_mcOfflineAnalysis->drawCutProfileHistosMap( m_dirCutProfile );

	m_mcOfflineAnalysis->drawPerformance( vEntries, vResMemory, vVirMemory, m_dirPerformance );

	m_mcOfflineAnalysis->printCutFlowNumbers(l64t_nentries);
}

void mcOfflineControl::fits()
{
	cout << "### in fits ####" << endl;

	double yields[2];
	
	// Preform the fit
	m_mcOfflineAnalysis->minimize( false, m_mcOfflineAnalysis->h1_imassFit, yields, m_dirFit );
}

void mcOfflineControl::analyze()
{
	m_mcOfflineAnalysis->executeCutFlow();
}

void mcOfflineControl::loop(Long64_t startEvent, Long64_t stopAfterNevents)
{
	if (m_mcOffPhys->fChain == 0)  return;

	l64t_nentries = m_mcOffPhys->fChain->GetEntriesFast();
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
		l64t_ientry = m_mcOffPhys->LoadTree(l64t_jentry);
		if (l64t_ientry < 0) break;
		l64t_nb = m_mcOffPhys->fChain->GetEntry(l64t_jentry);
		l64t_nbytes += l64t_nb;
		// if (Cut(l64t_ientry) < 0) continue;
		
		if(l64t_jentry%100000==0) cout << "jentry=" << l64t_jentry << "\t ientry=" << l64t_ientry << "\trun=" << m_mcOffPhys->RunNumber << "\tlumiblock=" << m_mcOffPhys->lbn << endl;
		if(l64t_jentry%l64t_mod==0) m_mcOfflineAnalysis->printCutFlowNumbers(l64t_nentries);
		
		if(l64t_jentry%1000==0)
		{
			gSystem->GetProcInfo(&pi);
			//cout << "RES Mem=" << pi.fMemResident << " VIRT Mem=" << pi.fMemVirtual << endl;
			vResMemory.push_back((double)pi.fMemResident);
			vVirMemory.push_back((double)pi.fMemVirtual);
			vEntries.push_back((int)l64t_jentry);
		}
		
		analyze();
	}
	
	fits();
	
	draw();
	
	//finalize();
	
	stopTimer(true);
}







void mcOfflineControl::getCandidates(string sFilePath)
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

bool mcOfflineControl::matchCandidates()
{	
	for(int rn=0 ; rn<(int)runNumber.size() ; rn++)
	{
		if( runNumber[rn] != (double)m_mcOffPhys->RunNumber ) continue;
		for(int lb=0 ; lb<(int)lumiBlock.size() ; lb++)
		{
			if( lumiBlock[lb] != (double)m_mcOffPhys->lbn ) continue;
			for(int en=0 ; en<(int)eventNumber.size() ; en++)
			{
				if( eventNumber[en] != (double)m_mcOffPhys->EventNumber ) continue;			
				cout << "match !" << endl;
				return true;
			}
		}
	}
	return false;
}

void mcOfflineControl::loopCandidates()
{
	if (m_mcOffPhys->fChain == 0)  return;

	l64t_nentries = m_mcOffPhys->fChain->GetEntriesFast();
	l64t_nbytes = 0;
	l64t_nb = 0;

	// read the external list of Z candidates
	int nMatched = 0;
	string sFilePath = checkANDsetFilepath("PWD", "/../conf/STACO.cand");
	getCandidates(sFilePath);
	
	for (l64t_jentry=0 ; l64t_jentry<l64t_nentries ; l64t_jentry++)
	{
		l64t_ientry = m_mcOffPhys->LoadTree(l64t_jentry);
		if (l64t_ientry < 0) break;
		l64t_nb = m_mcOffPhys->fChain->GetEntry(l64t_jentry);
		l64t_nbytes += l64t_nb;
		
		if(l64t_jentry%1000==0) cout << "jentry=" << l64t_jentry << "\t ientry=" << l64t_ientry << "\trun=" << m_mcOffPhys->RunNumber << "\tlumiblock=" << m_mcOffPhys->lbn << "\tnMatched=" << nMatched << endl;
		
		// try to match this event to an entry from the external list
		if( matchCandidates() ) nMatched++;
	}
}
