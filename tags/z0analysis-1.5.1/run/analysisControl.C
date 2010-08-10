/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "analysisControl.h"


analysisControl::analysisControl()
{
	initialize();
	
	string str = "";

	str = checkANDsetFilepath("PWD", "/../conf/dataset.list");
	string strb = checkANDsetFilepath("PWD", "/datasetdir/"); // ln -s /data/hod/D3PDs/group10.phys-sm.data10_7TeV_physics_MuonswBeam_WZphys_D3PD datasetdir
	makeChain(true, str, strb);

	m_phys = new physics( m_chain );

	str = checkANDsetFilepath("PWD", "/../data/analysisTrees.root");
	m_treefile = new TFile( str.c_str(), "RECREATE");
	m_treefile->cd();

	str = checkANDsetFilepath("PWD", "/../data/analysisControl.root");
	m_histfile = new TFile( str.c_str(), "RECREATE");
	m_histfile->cd();

	m_graphics = new graphicObjects();
	m_graphics->setStyle();

	str = checkANDsetFilepath("PWD", "/../conf/Z_GRL_152844-159224.xml");
	m_GRL = new GRLinterface();
	m_GRL->glrinitialize( (TString)str );

	m_analysis = new analysis( m_phys, m_graphics, m_GRL, m_treefile );

	// read the cut flow (ownership: selection class which analysis inherits from)
	str = checkANDsetFilepath("PWD", "/../conf/cutFlow.cuts");
	m_analysis->readCutFlow( str );

	book();
}

analysisControl::~analysisControl()
{
	finalize();
}

void analysisControl::initialize()
{
	// run control
	l64t_nentries = 0;
	l64t_nbytes   = 0;
	l64t_nb       = 0;
	l64t_jentry   = 0;
	l64t_ientry   = 0;

	// pointers
	m_phys     = NULL;
	m_analysis = NULL;
	m_graphics = NULL;
	m_histfile = NULL;
	m_treefile = NULL;

	cinitialize();
	kinitialize();
	uinitialize();
}

void analysisControl::finalize()
{
	// file
	m_histfile->Write();
	m_histfile->Close();

	cfinalize();
	kfinalize();
	ufinalize();
}

void analysisControl::book()
{
	m_dirNoCuts = m_histfile->mkdir("noCuts");
	m_graphics->bookBareHistos(m_dirNoCuts);

	m_dirAllCuts = m_histfile->mkdir("allCuts");
	m_graphics->bookHistos(m_dirAllCuts);

	m_dirCutFlow = m_histfile->mkdir("cutFlow");
	m_graphics->bookHistosMap( m_analysis->getCutFlowMapPtr(), m_analysis->getCutFlowOrderedPtr(), m_dirCutFlow );	
}

void analysisControl::draw()
{
	m_graphics->drawBareHistos(m_dirNoCuts);
	m_graphics->drawHistos(m_dirAllCuts);
	m_graphics->drawHistosMap( m_analysis->getCutFlowMapPtr(), m_analysis->getCutFlowOrderedPtr(), m_dirCutFlow );

	m_analysis->printCutFlowNumbers(l64t_nentries);
}

void analysisControl::analyze()
{
	bool isendofrun = (l64t_jentry==l64t_stopEvent-1) ? true : false;

	m_analysis->executeTree( isendofrun );
	m_analysis->executeBasic();
	m_analysis->executeAdvanced();
	m_analysis->executeCutFlow();
}

void analysisControl::loop(Long64_t startEvent, Long64_t stopAfterNevents)
{
	if (m_phys->fChain == 0)  return;

	l64t_nentries = m_phys->fChain->GetEntriesFast();
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
		l64t_ientry = m_phys->LoadTree(l64t_jentry);
		if (l64t_ientry < 0) break;
		l64t_nb = m_phys->fChain->GetEntry(l64t_jentry);
		l64t_nbytes += l64t_nb;
		// if (Cut(l64t_ientry) < 0) continue;
		
		if(l64t_jentry%10000==0) cout << "jentry=" << l64t_jentry << "\t ientry=" << l64t_ientry << "\trun=" << m_phys->RunNumber << "\tlumiblock=" << m_phys->lbn << endl;
		if(l64t_jentry%l64t_mod==0) m_analysis->printCutFlowNumbers(l64t_nentries);
		
		analyze();
	}
	
	draw();
}

