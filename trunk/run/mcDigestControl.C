/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "mcDigestControl.h"


mcDigestControl::mcDigestControl()
{
	startTimer();

	initialize();
	
	string str = "";
	
	//////////////////////////////////////////
	// prompt to chose the MC sample here ////
	string sMCsample = pickMCinputSampe(); ///
	//////////////////////////////////////////

	str = checkANDsetFilepath("PWD", "/../conf/digest_mc_dataset_"+sMCsample+".list");
	string strb = checkANDsetFilepath("PWD", "/digest_datasetdir/"); // ln -s  ~hod/data  datasetdir
	makeChain(true, str, strb);

	m_mcDigestPhys = new mcDigestPhysics( m_chain );

	//str = checkANDsetFilepath("PWD", "/../data/mcDigestTreeDigest_"+sMCsample+".root");
	//m_treefile = new TFile( str.c_str(), "RECREATE");
	m_treefile = NULL;
	
	str = checkANDsetFilepath("PWD", "/../data/mcDigestControl_"+sMCsample+".root");
	m_histfile = new TFile( str.c_str(), "RECREATE");
	m_histfile->cd();

	string str1 = checkANDsetFilepath("PWD", "/../conf/cutFlow.cuts");
	string str2 = checkANDsetFilepath("PWD", "/../conf/dataPeriods.data");
	
	m_mcDigestAnalysis = new mcDigestAnalysis( m_mcDigestPhys, m_treefile, str1, str2, "");

	book();
}

mcDigestControl::~mcDigestControl()
{

}

void mcDigestControl::setRecAlgo(string muRecAlgo)
{
	if(muRecAlgo!="staco"  &&  muRecAlgo!="muid")
	{
		cout << "WARNING: muRecAlgo=" << muRecAlgo << " is not supported, setting to default (staco)" << endl;
		muRecAlgo = "staco";
	}
	m_muRecAlgo = muRecAlgo;
}

void mcDigestControl::initialize()
{
	// run control
	l64t_nentries = 0;
	l64t_nbytes   = 0;
	l64t_nb       = 0;
	l64t_jentry   = 0;
	l64t_ientry   = 0;
}

void mcDigestControl::finalize()
{
	// write the tree
	m_mcDigestAnalysis->write();

	// files
	m_histfile->Write();
	m_histfile->Close();

	//m_treefile->Write();
	//m_treefile->Close();
}

void mcDigestControl::book()
{
	m_dirNoCuts = m_histfile->mkdir("noCuts");
	m_mcDigestAnalysis->bookBareHistos(m_dirNoCuts);

	m_dirAllCuts = m_histfile->mkdir("allCuts");
	m_mcDigestAnalysis->bookHistos(m_dirAllCuts);
	
	m_dirFit = m_histfile->mkdir("fit");
	m_mcDigestAnalysis->bookFitHistos(m_dirFit);

	m_dirCutFlow = m_histfile->mkdir("cutFlow");
	m_mcDigestAnalysis->bookHistosMap( m_mcDigestAnalysis->getCutFlowOrderedMapPtr(), m_mcDigestAnalysis->getCutFlowTypeOrderedMapPtr(), m_dirCutFlow );
	
	m_dirCutProfile = m_histfile->mkdir("cutsProfile");
	m_mcDigestAnalysis->bookCutProfileHistosMap( m_mcDigestAnalysis->getCutFlowOrderedMapPtr(), m_dirCutProfile );
	
	m_dirEff = m_histfile->mkdir("efficiency");
	m_mcDigestAnalysis->bookEfficiencyHistos(m_mcDigestAnalysis->m_period2triggerperiodMap, m_dirEff);
	
	m_mcDigestAnalysis->setTrees(m_dirAllCuts, m_dirCutProfile, m_dirEff);
	
	m_dirPerformance = m_histfile->mkdir("performance");
}

void mcDigestControl::draw()
{
	m_mcDigestAnalysis->drawBareHistos(m_dirNoCuts);
	
	// these calculations must come before drawHistos
	m_mcDigestAnalysis->calculateAfb(m_mcDigestAnalysis->h1_Afb);
	
	m_mcDigestAnalysis->drawHistos(m_dirAllCuts);
	
	m_mcDigestAnalysis->drawHistosMap( m_mcDigestAnalysis->getCutFlowOrderedMapPtr(), m_mcDigestAnalysis->getCutFlowTypeOrderedMapPtr(), m_dirCutFlow );
	
	m_mcDigestAnalysis->drawFitHistos(m_dirFit, m_mcDigestAnalysis->m_fitROOT->guess, m_mcDigestAnalysis->m_fitROOT->fitFCN);
	//m_mcDigestAnalysis->drawFitHistos(m_dirFit, m_mcDigestAnalysis->m_fitMinuit->guess, m_mcDigestAnalysis->m_fitMinuit->fitFCN);
	
	m_mcDigestAnalysis->drawCutProfileHistosMap( m_dirCutProfile );
	
	bool isTruth = false;
	m_mcDigestAnalysis->calculateEfficiency(m_mcDigestAnalysis->h1map_tagNprobe_candidates_pT,
											m_mcDigestAnalysis->h1map_tagNprobe_succeeded_pT,
											m_mcDigestAnalysis->h1map_tagNprobe_trigEff_pT, isTruth);
	m_mcDigestAnalysis->calculateEfficiency(m_mcDigestAnalysis->h1map_tagNprobe_candidates_eta,
											m_mcDigestAnalysis->h1map_tagNprobe_succeeded_eta,
											m_mcDigestAnalysis->h1map_tagNprobe_trigEff_eta, isTruth);
	m_mcDigestAnalysis->calculateEfficiency(m_mcDigestAnalysis->h1map_tagNprobe_candidates_phi,
											m_mcDigestAnalysis->h1map_tagNprobe_succeeded_phi,
											m_mcDigestAnalysis->h1map_tagNprobe_trigEff_phi, isTruth);
	isTruth = true;
	m_mcDigestAnalysis->calculateEfficiency(m_mcDigestAnalysis->h1map_truth_candidates_pT,
											m_mcDigestAnalysis->h1map_truth_succeeded_pT,
											m_mcDigestAnalysis->h1map_truth_trigEff_pT, isTruth);
	m_mcDigestAnalysis->calculateEfficiency(m_mcDigestAnalysis->h1map_truth_candidates_eta,
											m_mcDigestAnalysis->h1map_truth_succeeded_eta,
											m_mcDigestAnalysis->h1map_truth_trigEff_eta, isTruth);
	m_mcDigestAnalysis->calculateEfficiency(m_mcDigestAnalysis->h1map_truth_candidates_phi,
											m_mcDigestAnalysis->h1map_truth_succeeded_phi,
											m_mcDigestAnalysis->h1map_truth_trigEff_phi, isTruth);
	m_mcDigestAnalysis->drawEfficiencyHistosMap(m_dirEff);
	
	m_mcDigestAnalysis->drawPerformance( vEntries, vResMemory, vVirMemory, m_dirPerformance );
	
	m_mcDigestAnalysis->printCutFlowNumbers(l64t_nentries);
}

void mcDigestControl::fits()
{
	cout << "### in fits ####" << endl;

	double yields[2];
	
	// Preform the fit
	m_mcDigestAnalysis->minimize( false, m_mcDigestAnalysis->h1_imassFit, yields, m_dirFit );
}

void mcDigestControl::analyze()
{
	m_mcDigestAnalysis->execute(m_muRecAlgo);
}

void mcDigestControl::loop(Long64_t startEvent, Long64_t stopAfterNevents)
{
	if (m_mcDigestPhys->fChain == 0)  return;

	l64t_nentries = m_mcDigestPhys->fChain->GetEntriesFast();
	l64t_nbytes = 0;
	l64t_nb = 0;

	l64t_mod = 20000;

	l64t_startEvent = startEvent;
	l64t_stopEvent = l64t_nentries;

	if(stopAfterNevents <= 0)                            { l64t_stopEvent = l64t_nentries; cout << "1. stop at event " << l64t_stopEvent << endl; }
	else if(startEvent+stopAfterNevents < l64t_nentries) { l64t_stopEvent = startEvent+stopAfterNevents; cout << "3. stop at event " << l64t_stopEvent << endl; }
	if(startEvent+stopAfterNevents > l64t_nentries)      { l64t_stopEvent = l64t_nentries; cout << "2. stop at event " << l64t_stopEvent << endl; }

	for (l64t_jentry=l64t_startEvent ; l64t_jentry<l64t_stopEvent/*l64t_nentries*/ ; l64t_jentry++)
	{
		l64t_ientry = m_mcDigestPhys->LoadTree(l64t_jentry);
		if (l64t_ientry < 0) break;
		l64t_nb = m_mcDigestPhys->fChain->GetEntry(l64t_jentry);
		l64t_nbytes += l64t_nb;
		// if (Cut(l64t_ientry) < 0) continue;
		
		if(l64t_jentry%10000==0) cout << "jentry=" << l64t_jentry << "\t ientry=" << l64t_ientry << "\trun=" << m_mcDigestPhys->RunNumber << "\tlumiblock=" << m_mcDigestPhys->lbn << endl;
		if(l64t_jentry%l64t_mod==0) m_mcDigestAnalysis->printCutFlowNumbers(l64t_nentries);
		
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
	
	finalize();
	
	stopTimer(true);
}







void mcDigestControl::getCandidates(string sFilePath)
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

bool mcDigestControl::matchCandidates()
{	
	for(int rn=0 ; rn<(int)runNumber.size() ; rn++)
	{
		if( runNumber[rn] != (double)m_mcDigestPhys->RunNumber ) continue;
		for(int lb=0 ; lb<(int)lumiBlock.size() ; lb++)
		{
			if( lumiBlock[lb] != (double)m_mcDigestPhys->lbn ) continue;
			for(int en=0 ; en<(int)eventNumber.size() ; en++)
			{
				if( eventNumber[en] != (double)m_mcDigestPhys->EventNumber ) continue;			
				cout << "match !" << endl;
				return true;
			}
		}
	}
	return false;
}

void mcDigestControl::loopCandidates()
{
	if (m_mcDigestPhys->fChain == 0)  return;

	l64t_nentries = m_mcDigestPhys->fChain->GetEntriesFast();
	l64t_nbytes = 0;
	l64t_nb = 0;

	// read the external list of Z candidates
	int nMatched = 0;
	string sFilePath = checkANDsetFilepath("PWD", "/../conf/STACO.cand");
	getCandidates(sFilePath);
	
	for (l64t_jentry=0 ; l64t_jentry<l64t_nentries ; l64t_jentry++)
	{
		l64t_ientry = m_mcDigestPhys->LoadTree(l64t_jentry);
		if (l64t_ientry < 0) break;
		l64t_nb = m_mcDigestPhys->fChain->GetEntry(l64t_jentry);
		l64t_nbytes += l64t_nb;
		
		if(l64t_jentry%1000==0) cout << "jentry=" << l64t_jentry << "\t ientry=" << l64t_ientry << "\trun=" << m_mcDigestPhys->RunNumber << "\tlumiblock=" << m_mcDigestPhys->lbn << "\tnMatched=" << nMatched << endl;
		
		// try to match this event to an entry from the external list
		if( matchCandidates() ) nMatched++;
	}
}
