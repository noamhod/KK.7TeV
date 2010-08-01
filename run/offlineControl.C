/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "offlineControl.h"


offlineControl::offlineControl()
{
	initialize();
	
	string str = "";

	str = checkANDsetFilepath("PWD", "/../conf/offline_dataset.list");
	string strb = checkANDsetFilepath("PWD", "/offline_datasetdir/"); // ln -s  ~hod/data  datasetdir
	makeChain(true, str, strb);

	m_offPhys = new offlinePhysics( m_chain );

	str = checkANDsetFilepath("PWD", "/../data/offlineControl.root");
	m_histfile = new TFile( str.c_str(), "RECREATE");
        m_histfile->cd();

	m_graphics = new graphicObjects();
	m_graphics->setStyle();

        m_offlineAnalysis = new offlineAnalysis( m_offPhys, m_graphics );

	// read the cut flow (ownership: selection class which offlineAnalysis inherits from)
	str = checkANDsetFilepath("PWD", "/../conf/cutFlow.cuts");
	m_offlineAnalysis->readCutFlow( str );

	book();
}

offlineControl::~offlineControl()
{
	finalize();
}

void offlineControl::initialize()
{
	// run control
	l64t_nentries = 0;
        l64t_nbytes   = 0;
        l64t_nb       = 0;
        l64t_jentry   = 0;
        l64t_ientry   = 0;

        // pointers
	m_offPhys     = NULL;
	m_offlineAnalysis = NULL;
	m_graphics = NULL;
	m_histfile = NULL;

	cinitialize();
	kinitialize();
	uinitialize();
}

void offlineControl::finalize()
{
	// file
	m_histfile->Write();
	m_histfile->Close();

	// pointers
	/*
	delete m_offPhys;
	delete m_offlineAnalysis;
	delete m_graphics;
	delete m_histfile;
	delete m_treefile;
	*/

	cfinalize();
	kfinalize();
        ufinalize();
}

void offlineControl::book()
{
	m_dirNoCuts = m_histfile->mkdir("noCuts");
	m_graphics->bookBareHistos(m_dirNoCuts);

	m_dirAllCuts = m_histfile->mkdir("allCuts");
	m_graphics->bookHistos(m_dirAllCuts);

	m_dirCutFlow = m_histfile->mkdir("cutFlow");
        m_graphics->bookHistosMap( m_offlineAnalysis->getCutFlowMapPtr(), m_offlineAnalysis->getCutFlowOrderedPtr(), m_dirCutFlow );	
}

void offlineControl::draw()
{
	m_graphics->drawBareHistos(m_dirNoCuts);
	m_graphics->drawHistos(m_dirAllCuts);
        m_graphics->drawHistosMap( m_offlineAnalysis->getCutFlowMapPtr(), m_offlineAnalysis->getCutFlowOrderedPtr(), m_dirCutFlow );

        m_offlineAnalysis->printCutFlowNumbers(l64t_nentries);
}

void offlineControl::analyze()
{
	m_offlineAnalysis->executeBasic();
	m_offlineAnalysis->executeCutFlow();
}

void offlineControl::loop(Long64_t startEvent, Long64_t stopAfterNevents)
{
	if (m_offPhys->fChain == 0)  return;

	l64t_nentries = m_offPhys->fChain->GetEntriesFast();
	l64t_nbytes = 0;
	l64t_nb = 0;

	l64t_mod = 5000;

	l64t_startEvent = startEvent;
	l64t_stopEvent = l64t_nentries;

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
		
		if(l64t_jentry%100==0) cout << "jentry=" << l64t_jentry << "\t ientry=" << l64t_ientry << "\trun=" << m_offPhys->runnumber << "\tlumiblock=" << m_offPhys->lumiblock << endl;
		if(l64t_jentry%l64t_mod==0) m_offlineAnalysis->printCutFlowNumbers(l64t_nentries);
	
		analyze();
	}
	
	draw();
}

