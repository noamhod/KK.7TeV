/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "digestControl.h"


digestControl::digestControl()
{
	initialize();
	
	string str = "";

	str = checkANDsetFilepath("PWD", "/../conf/digest_dataset.list");
	string strb = checkANDsetFilepath("PWD", "/digest_datasetdir/"); // ln -s  ~hod/data  datasetdir
	makeChain(true, str, strb);

	m_digestPhys = new digestPhysics( m_chain );

	str = checkANDsetFilepath("PWD", "/../data/digestTreeDigest.root");
	m_treefile = new TFile( str.c_str(), "RECREATE");
	
	str = checkANDsetFilepath("PWD", "/../data/digestControl.root");
	m_histfile = new TFile( str.c_str(), "RECREATE");
	m_histfile->cd();

	m_graphics = new graphicObjects();
	m_graphics->setStyle();

	// read the cut flow (ownership: selection class which digestAnalysis inherits from)
	str = checkANDsetFilepath("PWD", "/../conf/cutFlow.cuts");
	m_cutFlowHandler = new cutFlowHandler(str);
	
	m_fitter = new fit();
	
	m_digestAnalysis = new digestAnalysis( m_digestPhys, m_graphics, m_cutFlowHandler, m_fitter, m_treefile );

	book();
}

digestControl::~digestControl()
{
	//finalize();
}

void digestControl::initialize()
{
	// run control
	l64t_nentries = 0;
	l64t_nbytes   = 0;
	l64t_nb       = 0;
	l64t_jentry   = 0;
	l64t_ientry   = 0;

	// pointers
	m_digestPhys     = NULL;
	m_digestAnalysis = NULL;
	m_graphics = NULL;
	m_fitter   = NULL;
	m_histfile = NULL;
	m_treefile = NULL;

	cinitialize();
	kinitialize();
	uinitialize();
}

void digestControl::finalize()
{
	// write the tree
	m_digestAnalysis->write();

	// files
	m_histfile->Write();
	m_histfile->Close();

	m_treefile->Write();
	m_treefile->Close();
	
	cfinalize();
	kfinalize();
	ufinalize();
}

void digestControl::book()
{
	m_dirNoCuts = m_histfile->mkdir("noCuts");
	m_graphics->bookBareHistos(m_dirNoCuts);

	m_dirAllCuts = m_histfile->mkdir("allCuts");
	m_graphics->bookHistos(m_dirAllCuts);
	
	m_dirFit = m_histfile->mkdir("fit");
	m_graphics->bookFitHistos(m_dirFit);

	m_dirCutFlow = m_histfile->mkdir("cutFlow");
	m_graphics->bookHistosMap( m_cutFlowHandler->getCutFlowOrderedMapPtr(), m_cutFlowHandler->getCutFlowTypeOrderedMapPtr(), m_dirCutFlow );
}

void digestControl::fits()
{
	cout << "### in fits ####" << endl;

	double yields[2];
	
	// Preform the fit
	m_fitter->minimize( false, m_graphics->h1_imassFit, yields );
}

void digestControl::draw()
{
	m_graphics->drawBareHistos(m_dirNoCuts);
	m_graphics->drawHistos(m_dirAllCuts);
	m_graphics->drawHistosMap( m_cutFlowHandler->getCutFlowOrderedMapPtr(), m_cutFlowHandler->getCutFlowTypeOrderedMapPtr(), m_dirCutFlow );
	m_graphics->drawFitHistos(m_dirFit, m_fitter->m_fitROOT->guess, m_fitter->m_fitROOT->fitFCN);
	//m_graphics->drawFitHistos(m_dirFit, m_fitter->m_fitMinuit->guess, m_fitter->m_fitMinuit->fitFCN);

	m_cutFlowHandler->printCutFlowNumbers(l64t_nentries);
}

void digestControl::analyze()
{
	m_digestAnalysis->executeCutFlow();
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
		if(l64t_jentry%l64t_mod==0) m_cutFlowHandler->printCutFlowNumbers(l64t_nentries);
		
		analyze();
	}
	
	//m_digestAnalysis->fitter();
	fits();
	
	draw();
	
	//finalize();
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
