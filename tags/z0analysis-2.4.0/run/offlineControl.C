/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "offlineControl.h"


offlineControl::offlineControl()
{
	
}

offlineControl::~offlineControl()
{
	
}

void offlineControl::initialize(int runNumber)
{
	startTimer();

	// run control
	l64t_nentries = 0;
	l64t_nbytes   = 0;
	l64t_nb       = 0;
	l64t_jentry   = 0;
	l64t_ientry   = 0;

	// pointers
	m_offPhys     = NULL;
	m_offlineAnalysis = NULL;
	m_histfile = NULL;
	m_treefile = NULL;
	
	string str = "";
	
	str = checkANDsetFilepath("PWD", "/../conf/Z_GRL_CURRENT.xml");;
	m_GRL = new GRLinterface();
	m_GRL->glrinitialize( (TString)str );
	
	//str = checkANDsetFilepath("PWD", "/../conf/offline_dataset.list");
	//string strb = checkANDsetFilepath("PWD", "/offline_datasetdir/");
	////////////////////////////////////////////////////////////////////////////////////////
	// for TESTS only //////////////////////////////////////////////////////////////////////
	string strb = checkANDsetFilepath("PWD", "/"); //////////////////////
	str = checkANDsetFilepath("PWD", "/../conf/offline_dataset_WZphys_localTests.list"); ///
	////////////////////////////////////////////////////////////////////////////////////////
	
	if(runNumber==0) makeChain(true, str, strb);
	else             makeChain(true, str, strb, runNumber);

	m_offPhys = new offlinePhysics( m_chain );

	//str = checkANDsetFilepath("PWD", "/../data/offlineTreeDigest.root");
	str = checkANDsetFilepath("PWD", "/../data/digestTree.root");
	m_treefile = new TFile( str.c_str(), "RECREATE");
	
	str = checkANDsetFilepath("PWD", "/../data/offlineControl.root");
	m_histfile = new TFile( str.c_str(), "RECREATE");
	m_histfile->cd();

	string str1 = checkANDsetFilepath("PWD", "/../conf/cutFlow.cuts");
	string str2 = checkANDsetFilepath("PWD", "/../conf/dataPeriods.data");
	
	m_offlineAnalysis = new offlineAnalysis( m_offPhys, m_GRL, m_treefile, str1, str2, "offlineAnalysis_interestingEvents.dump" );

	book();

	m_treefile->cd();
}

void offlineControl::finalize()
{
	//m_offlineAnalysis->m_muSkimD3PD->m_tree->Print();
	// tree
	// the tree will split into multiple files
	// since in digestTree class there is the
	// following statement m_tree->SetMaxTreeSize(50000000);
	// i.e., 50Mb per file
	m_treefile = m_offlineAnalysis->m_muSkimD3PD->m_tree->GetCurrentFile();
	m_treefile->cd();
	m_offlineAnalysis->m_muSkimD3PD->m_tree->Write();
	m_treefile->Write();
	m_treefile->Close();
	
	// histos
	m_histfile->Write();
	m_histfile->Close();
}

void offlineControl::book()
{
	m_dirNoCuts = m_histfile->mkdir("noCuts");
	m_offlineAnalysis->bookBareHistos(m_dirNoCuts);

	m_dirAllCuts = m_histfile->mkdir("allCuts");
	m_offlineAnalysis->bookHistos(m_dirAllCuts);
	
	m_dirFit = m_histfile->mkdir("fit");
	m_offlineAnalysis->bookFitHistos(m_dirFit);

	m_dirCutFlow = m_histfile->mkdir("cutFlow");
	m_offlineAnalysis->bookHistosMap( m_offlineAnalysis->getCutFlowOrderedMapPtr(), m_offlineAnalysis->getCutFlowTypeOrderedMapPtr(), m_dirCutFlow );
	
	m_dirCutProfile = m_histfile->mkdir("cutsProfile");
	m_offlineAnalysis->bookCutProfileHistosMap( m_offlineAnalysis->getCutFlowOrderedMapPtr(), m_dirCutProfile );
	
	m_dirPerformance = m_histfile->mkdir("performance");
}

void offlineControl::draw()
{
	m_offlineAnalysis->drawBareHistos(m_dirNoCuts);
	m_offlineAnalysis->drawHistos(m_dirAllCuts);
	m_offlineAnalysis->drawHistosMap( m_offlineAnalysis->getCutFlowOrderedMapPtr(), m_offlineAnalysis->getCutFlowTypeOrderedMapPtr(), m_dirCutFlow );
	m_offlineAnalysis->drawFitHistos(m_dirFit, m_offlineAnalysis->m_fitROOT->guess, m_offlineAnalysis->m_fitROOT->fitFCN);
	//m_offlineAnalysis->drawFitHistos(m_dirFit, m_offlineAnalysis->m_fitMinuit->guess, m_offlineAnalysis->m_fitMinuit->fitFCN);
	m_offlineAnalysis->drawCutProfileHistosMap( m_dirCutProfile );
	m_offlineAnalysis->drawPerformance( vEntries, vResMemory, vVirMemory, m_dirPerformance );
	
	m_offlineAnalysis->printCutFlowNumbers(l64t_nentries);
}

void offlineControl::fits()
{
	cout << "### in fits ####" << endl;

	double yields[2];
	
	// Preform the fit
	m_offlineAnalysis->minimize( false, m_offlineAnalysis->h1_imassFit, yields, m_dirFit );
}

void offlineControl::analyze()
{
	//m_offlineAnalysis->executeBasic();
	m_offlineAnalysis->executeCutFlow();
}

void offlineControl::loop(Long64_t startEvent, Long64_t stopAfterNevents)
{
	if (m_offPhys->fChain == 0)  return;

	l64t_nentries = m_offPhys->fChain->GetEntriesFast();
	l64t_nbytes = 0;
	l64t_nb = 0;

	l64t_mod = 100000;

	l64t_startEvent = startEvent;
	l64t_stopEvent = l64t_nentries;

	int nSkim = 0;
	
	if(stopAfterNevents <= 0)                            { l64t_stopEvent = l64t_nentries; cout << "1. stop at event " << l64t_stopEvent << endl; }
	else if(startEvent+stopAfterNevents < l64t_nentries) { l64t_stopEvent = startEvent+stopAfterNevents; cout << "3. stop at event " << l64t_stopEvent << endl; }
	if(startEvent+stopAfterNevents > l64t_nentries)      { l64t_stopEvent = l64t_nentries; cout << "2. stop at event " << l64t_stopEvent << endl; }

	for (l64t_jentry=l64t_startEvent ; l64t_jentry<l64t_stopEvent/*l64t_nentries*/ ; l64t_jentry++)
	{
		l64t_ientry = m_offPhys->LoadTree(l64t_jentry);
		if (l64t_ientry < 0) break;
		l64t_nb = m_offPhys->fChain->GetEntry(l64t_jentry);
		l64t_nbytes += l64t_nb;
		// if (Cut(l64t_ientry) < 0) continue;
		
		if(l64t_jentry%100000==0)   cout << "jentry=" << l64t_jentry << "\t ientry=" << l64t_ientry << "\trun=" << m_offPhys->RunNumber << "\tlumiblock=" << m_offPhys->lbn << endl;
		if(l64t_jentry%l64t_mod==0) m_offlineAnalysis->printCutFlowNumbers(l64t_nentries);
		
		if(l64t_jentry%1000==0)
		{
			gSystem->GetProcInfo(&pi);
			//cout << "RES Mem=" << pi.fMemResident << " VIRT Mem=" << pi.fMemVirtual << endl;
			vResMemory.push_back((double)pi.fMemResident);
			vVirMemory.push_back((double)pi.fMemVirtual);
			vEntries.push_back((int)l64t_jentry);
		}
		
		///////////////////////////////////////////////////////////////////////////////////
		//if( m_offlineAnalysis->getPeriodName(m_offPhys->RunNumber)=="I1" ) break; /////////
		///////////////////////////////////////////////////////////////////////////////////
		
		int muSize = (int)m_offPhys->mu_staco_pt->size();
		int skim = 0;
		for(int mu=0 ; mu<muSize ; mu++)
		{
			bool pass = true;
			pass = ( pass  &&  m_offPhys->mu_staco_isCombinedMuon->at(mu) )      ? true : false;
			pass = ( pass  &&  fabs(m_offPhys->mu_staco_pt->at(mu))>15*GeV2MeV ) ? true : false;
			if(pass) skim++;
		}
		if(skim>1) nSkim++;
		
		analyze();
	}
	
	fits();
	
	draw();
	
	//finalize();
	
	stopTimer(true);
	
	cout << "nSkim = " << nSkim << " (stopped at period=" << m_offlineAnalysis->getPeriodName(m_offPhys->RunNumber) << ", run=" << m_offPhys->RunNumber << ", lbn=" << m_offPhys->lbn  << ")" << endl;
}

void offlineControl::loop(int runNumber)
{
	if (m_offPhys->fChain == 0)  return;

	l64t_nentries = m_offPhys->fChain->GetEntriesFast();
	l64t_nbytes = 0;
	l64t_nb = 0;

	l64t_mod = 100000;

	for (l64t_jentry=0 ; l64t_jentry<l64t_nentries ; l64t_jentry++)
	{
		l64t_ientry = m_offPhys->LoadTree(l64t_jentry);
		if (l64t_ientry < 0) break;
		l64t_nb = m_offPhys->fChain->GetEntry(l64t_jentry);
		l64t_nbytes += l64t_nb;
		// if (Cut(l64t_ientry) < 0) continue;
		
		if(l64t_jentry%100000==0) cout << "jentry=" << l64t_jentry << "\t ientry=" << l64t_ientry << "\trun=" << m_offPhys->RunNumber << "\tlumiblock=" << m_offPhys->lbn << endl;
		
		if(m_offPhys->RunNumber < runNumber) continue;
		if(m_offPhys->RunNumber > runNumber) break;
		
		if(l64t_jentry%l64t_mod==0) m_offlineAnalysis->printCutFlowNumbers(l64t_nentries);
		
		analyze();
	}
	
	fits();
	
	
	
	draw();
	
	//finalize();
	
	stopTimer(true);
}







void offlineControl::getCandidates(string sFilePath)
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

bool offlineControl::matchCandidates()
{	
	for(int rn=0 ; rn<(int)runNumber.size() ; rn++)
	{
		if( runNumber[rn] != (double)m_offPhys->RunNumber ) continue;
		for(int lb=0 ; lb<(int)lumiBlock.size() ; lb++)
		{
			if( lumiBlock[lb] != (double)m_offPhys->lbn ) continue;
			for(int en=0 ; en<(int)eventNumber.size() ; en++)
			{
				if( eventNumber[en] != (double)m_offPhys->EventNumber ) continue;			
				cout << "match !" << endl;
				return true;
			}
		}
	}
	return false;
}

void offlineControl::loopCandidates()
{
	if (m_offPhys->fChain == 0)  return;

	l64t_nentries = m_offPhys->fChain->GetEntriesFast();
	l64t_nbytes = 0;
	l64t_nb = 0;

	// read the external list of Z candidates
	int nMatched = 0;
	string sFilePath = checkANDsetFilepath("PWD", "/../conf/STACO.cand");
	getCandidates(sFilePath);
	
	for (l64t_jentry=0 ; l64t_jentry<l64t_nentries ; l64t_jentry++)
	{
		l64t_ientry = m_offPhys->LoadTree(l64t_jentry);
		if (l64t_ientry < 0) break;
		l64t_nb = m_offPhys->fChain->GetEntry(l64t_jentry);
		l64t_nbytes += l64t_nb;
		
		if(l64t_jentry%1000==0) cout << "jentry=" << l64t_jentry << "\t ientry=" << l64t_ientry << "\trun=" << m_offPhys->RunNumber << "\tlumiblock=" << m_offPhys->lbn << "\tnMatched=" << nMatched << endl;
		
		// try to match this event to an entry from the external list
		if( matchCandidates() ) nMatched++;
	}
}
