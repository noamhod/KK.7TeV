/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "digestControl.h"


digestControl::digestControl()
{
	
}

digestControl::~digestControl()
{

}

void digestControl::setRecAlgo(string muRecAlgo)
{
	if(muRecAlgo!="staco"  &&  muRecAlgo!="muid")
	{
		cout << "WARNING: muRecAlgo=" << muRecAlgo << " is not supported, setting to default (staco)" << endl;
		muRecAlgo = "staco";
	}
	m_muRecAlgo = muRecAlgo;
}

void digestControl::initialize()
{
	startTimer();
	
	m_muRecAlgo = "staco";

	// run control
	l64t_nentries = 0;
	l64t_nbytes   = 0;
	l64t_nb       = 0;
	l64t_jentry   = 0;
	l64t_ientry   = 0;
	
	string str = "";

	str = str = checkANDsetFilepath("PWD", "/../conf/Z_GRL_CURRENT.xml");
	m_GRL = new GRLinterface();
	m_GRL->glrinitialize( (TString)str );
	
	str = checkANDsetFilepath("PWD", "/../conf/digest_dataset_AtoI2_ZprimeGRL.list");
	string strb = checkANDsetFilepath("PWD", "/digest_datasetdir/"); // ln -s  ~hod/data  datasetdir
	makeChain(true, str, strb);

	m_digestPhys = new digestPhysics( m_chain );

	//str = checkANDsetFilepath("PWD", "/../data/digestTreeDigest.root");
	//m_treefile = new TFile( str.c_str(), "RECREATE");
	m_treefile = NULL;
	
	str = checkANDsetFilepath("PWD", "/../data/digestControl.root");
	m_histfile = new TFile( str.c_str(), "RECREATE");
	m_histfile->cd();

	string str1 = checkANDsetFilepath("PWD", "/../conf/cutFlow.cuts");
	string str2 = checkANDsetFilepath("PWD", "/../conf/dataPeriods.data");
	
	m_digestAnalysis = new digestAnalysis( m_digestPhys, m_GRL, m_treefile, str1, str2, "digestAnalysis_interestingEvents.dump" );

	book();
}

void digestControl::finalize()
{
	// write the tree
	m_digestAnalysis->write();

	// files
	m_histfile->Write();
	m_histfile->Close();

	//m_treefile->Write();
	//m_treefile->Close();
}

void digestControl::book()
{
	m_dirNoCuts = m_histfile->mkdir("noCuts");
	m_digestAnalysis->bookBareHistos(m_dirNoCuts);

	m_dirAllCuts = m_histfile->mkdir("allCuts");
	m_digestAnalysis->bookHistos(m_dirAllCuts);
	
	m_dirFit = m_histfile->mkdir("fit");
	m_digestAnalysis->bookFitHistos(m_dirFit);

	m_dirCutFlow = m_histfile->mkdir("cutFlow");
	m_digestAnalysis->bookHistosMap( m_digestAnalysis->getCutFlowOrderedMapPtr(), m_digestAnalysis->getCutFlowTypeOrderedMapPtr(), m_dirCutFlow );
	
	m_dirCutProfile = m_histfile->mkdir("cutsProfile");
	m_digestAnalysis->bookCutProfileHistosMap( m_digestAnalysis->getCutFlowOrderedMapPtr(), m_dirCutProfile );
	
	m_dirEff = m_histfile->mkdir("efficiency");
	m_digestAnalysis->bookEfficiencyHistos(m_digestAnalysis->m_period2triggerperiodMap, m_dirEff);
	
	m_digestAnalysis->setTrees(m_dirAllCuts, m_dirCutProfile, m_dirEff);
	
	m_dirPerformance = m_histfile->mkdir("performance");
}

void digestControl::draw()
{
	m_digestAnalysis->drawBareHistos(m_dirNoCuts);
	
	m_digestAnalysis->calculateAfb(m_digestAnalysis->h1_Afb);
	
	m_digestAnalysis->drawHistos(m_dirAllCuts);
	
	m_digestAnalysis->drawHistosMap( m_digestAnalysis->getCutFlowOrderedMapPtr(), m_digestAnalysis->getCutFlowTypeOrderedMapPtr(), m_dirCutFlow );
	
	m_digestAnalysis->drawFitHistos(m_dirFit, m_digestAnalysis->m_fitROOT->guess, m_digestAnalysis->m_fitROOT->fitFCN);
	//m_digestAnalysis->drawFitHistos(m_dirFit, m_digestAnalysis->m_fitMinuit->guess, m_digestAnalysis->m_fitMinuit->fitFCN);
	
	m_digestAnalysis->drawCutProfileHistosMap( m_dirCutProfile );
	
	bool isTruth = false;
	m_digestAnalysis->calculateEfficiency(m_digestAnalysis->h1map_tagNprobe_candidates_pT,
										  m_digestAnalysis->h1map_tagNprobe_succeeded_pT,
										  m_digestAnalysis->h1map_tagNprobe_trigEff_pT, isTruth);
	m_digestAnalysis->calculateEfficiency(m_digestAnalysis->h1map_tagNprobe_candidates_eta,
										  m_digestAnalysis->h1map_tagNprobe_succeeded_eta,
										  m_digestAnalysis->h1map_tagNprobe_trigEff_eta, isTruth);
	m_digestAnalysis->calculateEfficiency(m_digestAnalysis->h1map_tagNprobe_candidates_phi,
										  m_digestAnalysis->h1map_tagNprobe_succeeded_phi,
										  m_digestAnalysis->h1map_tagNprobe_trigEff_phi, isTruth);
	isTruth = true;
	m_digestAnalysis->calculateEfficiency(m_digestAnalysis->h1map_truth_candidates_pT,
										  m_digestAnalysis->h1map_truth_succeeded_pT,
										  m_digestAnalysis->h1map_truth_trigEff_pT, isTruth);
	m_digestAnalysis->calculateEfficiency(m_digestAnalysis->h1map_truth_candidates_eta,
										  m_digestAnalysis->h1map_truth_succeeded_eta,
										  m_digestAnalysis->h1map_truth_trigEff_eta, isTruth);
	m_digestAnalysis->calculateEfficiency(m_digestAnalysis->h1map_truth_candidates_phi,
										  m_digestAnalysis->h1map_truth_succeeded_phi,
										  m_digestAnalysis->h1map_truth_trigEff_phi, isTruth);
	m_digestAnalysis->drawEfficiencyHistosMap(m_dirEff);
	
	m_digestAnalysis->drawPerformance( vEntries, vResMemory, vVirMemory, m_dirPerformance );
	
	m_digestAnalysis->printCutFlowNumbers(l64t_nentries);
}

void digestControl::fits()
{
	cout << "### in fits ####" << endl;

	double yields[2];
	
	// Preform the fit
	m_digestAnalysis->minimize( false, m_digestAnalysis->h1_imassFit, yields, m_dirFit );
}

void digestControl::analyze()
{
	m_digestAnalysis->execute(m_muRecAlgo);
}

void digestControl::loop(Long64_t startEvent, Long64_t stopAfterNevents)
{
	if (m_digestPhys->fChain == 0)  return;

	l64t_nentries = m_digestPhys->fChain->GetEntriesFast();
	l64t_nbytes = 0;
	l64t_nb = 0;

	l64t_mod = 20000;

	l64t_startEvent = startEvent;
	l64t_stopEvent = l64t_nentries;
	
	int nSkim = 0;

	if(stopAfterNevents <= 0)                            { l64t_stopEvent = l64t_nentries; cout << "1. stop at event " << l64t_stopEvent << endl; }
	else if(startEvent+stopAfterNevents < l64t_nentries) { l64t_stopEvent = startEvent+stopAfterNevents; cout << "3. stop at event " << l64t_stopEvent << endl; }
	if(startEvent+stopAfterNevents > l64t_nentries)      { l64t_stopEvent = l64t_nentries; cout << "2. stop at event " << l64t_stopEvent << endl; }

	for (l64t_jentry=l64t_startEvent ; l64t_jentry<l64t_stopEvent/*l64t_nentries*/ ; l64t_jentry++)
	{
		l64t_ientry = m_digestPhys->LoadTree(l64t_jentry);
		if (l64t_ientry < 0) break;
		l64t_nb = m_digestPhys->fChain->GetEntry(l64t_jentry);
		l64t_nbytes += l64t_nb;
		// if (Cut(l64t_ientry) < 0) continue;
		
		if(l64t_jentry%10000==0) cout << "jentry=" << l64t_jentry << "\t ientry=" << l64t_ientry << "\trun=" << m_digestPhys->RunNumber << "\tlumiblock=" << m_digestPhys->lbn << endl;
		if(l64t_jentry%l64t_mod==0) m_digestAnalysis->printCutFlowNumbers(l64t_nentries);
		
		if(l64t_jentry%1000==0)
		{
			gSystem->GetProcInfo(&pi);
			//cout << "RES Mem=" << pi.fMemResident << " VIRT Mem=" << pi.fMemVirtual << endl;
			vResMemory.push_back((double)pi.fMemResident);
			vVirMemory.push_back((double)pi.fMemVirtual);
			vEntries.push_back((int)l64t_jentry);
		}
		
		/////////////////////////////////////////////////////////////////////////////////////
		//if( m_digestAnalysis->getPeriodName(m_digestPhys->RunNumber)=="I1" ) break; /////////
		/////////////////////////////////////////////////////////////////////////////////////
		
		
		int muSize = (int)m_digestPhys->mu_staco_pt->size();
		int skim = 0;
		for(int mu=0 ; mu<muSize ; mu++)
		{
			bool pass = true;
			pass = ( pass  &&  m_digestPhys->mu_staco_isCombinedMuon->at(mu) )      ? true : false;
			pass = ( pass  &&  fabs(m_digestPhys->mu_staco_pt->at(mu))>15*GeV2MeV ) ? true : false;
			if(pass) skim++;
		}
		if(skim>1) nSkim++;
		
		analyze();
	}
	
	fits();
	
	draw();
	
	finalize();
	
	stopTimer(true);
	
	cout << "nSkim = " << nSkim << " (stopped at period=" << m_digestAnalysis->getPeriodName(m_digestPhys->RunNumber) << ", run=" << m_digestPhys->RunNumber << ", lbn=" << m_digestPhys->lbn  << ")" << endl;
}







void digestControl::getCandidates(string sFilePath)
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

bool digestControl::matchCandidates()
{	
	for(int rn=0 ; rn<(int)runNumber.size() ; rn++)
	{
		if( runNumber[rn] != (double)m_digestPhys->RunNumber ) continue;
		for(int lb=0 ; lb<(int)lumiBlock.size() ; lb++)
		{
			if( lumiBlock[lb] != (double)m_digestPhys->lbn ) continue;
			for(int en=0 ; en<(int)eventNumber.size() ; en++)
			{
				if( eventNumber[en] != (double)m_digestPhys->EventNumber ) continue;			
				cout << "match !" << endl;
				return true;
			}
		}
	}
	return false;
}

void digestControl::loopCandidates()
{
	if (m_digestPhys->fChain == 0)  return;

	l64t_nentries = m_digestPhys->fChain->GetEntriesFast();
	l64t_nbytes = 0;
	l64t_nb = 0;

	// read the external list of Z candidates
	int nMatched = 0;
	string sFilePath = checkANDsetFilepath("PWD", "/../conf/STACO.cand");
	getCandidates(sFilePath);
	
	for (l64t_jentry=0 ; l64t_jentry<l64t_nentries ; l64t_jentry++)
	{
		l64t_ientry = m_digestPhys->LoadTree(l64t_jentry);
		if (l64t_ientry < 0) break;
		l64t_nb = m_digestPhys->fChain->GetEntry(l64t_jentry);
		l64t_nbytes += l64t_nb;
		
		if(l64t_jentry%1000==0) cout << "jentry=" << l64t_jentry << "\t ientry=" << l64t_ientry << "\trun=" << m_digestPhys->RunNumber << "\tlumiblock=" << m_digestPhys->lbn << "\tnMatched=" << nMatched << endl;
		
		// try to match this event to an entry from the external list
		if( matchCandidates() ) nMatched++;
	}
}
