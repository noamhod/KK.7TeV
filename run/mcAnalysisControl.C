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

	str = checkANDsetFilepath("PWD", "/../conf/mcdataset.list");
	string strb = checkANDsetFilepath("PWD", "/mcdatasetdir/"); // ln -s /data/hod/D3PDs/group10.mcPhys-sm.data10_7TeV_mcPhysics_MuonswBeam_WZmcPhys_D3PD datasetdir
	//string strb = ""; // ln -s /tmp/hod/file1.root file1.root 
	makeChain(true, str, strb);

	m_mcPhys = new mcPhysics( m_chain );

	//str = checkANDsetFilepath("PWD", "/../data/mcAnalysisTrees.root");
	str = "mcAnalysisTrees.root";
	m_treefile = new TFile( str.c_str(), "RECREATE");
	m_treefile->cd();

	str = checkANDsetFilepath("PWD", "/../data/mcAnalysisControl.root");
	m_histfile = new TFile( str.c_str(), "RECREATE");
	m_histfile->cd();

	m_graphics = new graphicObjects();
	m_graphics->setStyle();


	// read the cut flow (ownership: selection class which analysis inherits from)
	str = checkANDsetFilepath("PWD", "/../conf/cutFlow.cuts");
	m_cutFlowHandler = new cutFlowHandler(str);
	
	m_analysis = new analysis( m_mcPhys, m_graphics, m_cutFlowHandler, m_treefile );

	book();
}

analysisControl::~analysisControl()
{
	//finalize();
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
	m_mcPhys     = NULL;
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
	// write the tree
	m_analysis->write();

	// files
	m_histfile->Write();
	m_histfile->Close();

	m_treefile->Write();
	m_treefile->Close();
	
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
	m_graphics->bookHistosMap( m_cutFlowHandler->getCutFlowOrderedMapPtr(), m_cutFlowHandler->getCutFlowTypeOrderedMapPtr(), m_dirCutFlow );	
}

void analysisControl::draw()
{
	m_graphics->drawBareHistos(m_dirNoCuts);
	m_graphics->drawHistos(m_dirAllCuts);
	m_graphics->drawHistosMap( m_cutFlowHandler->getCutFlowOrderedMapPtr(), m_cutFlowHandler->getCutFlowTypeOrderedMapPtr(), m_dirCutFlow );

	m_cutFlowHandler->printCutFlowNumbers(l64t_nentries);
}

void analysisControl::analyze()
{
	m_analysis->executeCutFlow();
}

void analysisControl::loop(Long64_t startEvent, Long64_t stopAfterNevents)
{
	if (m_mcPhys->fChain == 0)  return;

	l64t_nentries = m_mcPhys->fChain->GetEntriesFast();
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
		l64t_ientry = m_mcPhys->LoadTree(l64t_jentry);
		if (l64t_ientry < 0) break;
		l64t_nb = m_mcPhys->fChain->GetEntry(l64t_jentry);
		l64t_nbytes += l64t_nb;
		// if (Cut(l64t_ientry) < 0) continue;
		
		if(l64t_jentry%100000==0) cout << "jentry=" << l64t_jentry << "\t ientry=" << l64t_ientry << "\trun=" << m_mcPhys->RunNumber << "\tlumiblock=" << m_mcPhys->lbn << endl;
		if(l64t_jentry%l64t_mod==0) m_cutFlowHandler->printCutFlowNumbers(l64t_nentries);
		
		analyze();
	}
	
	draw();
	
	//////////////////////////////////////////////////////////////////////////
	finalize(); //////////////////////////////////////////////////////////////
	// ususally I call this messege manually, after //////////////////////////
	// the loop() method has exitted since otherwise the histos //////////////
	// will disappear. Here we usually run root with "-b -q" options /////////
	// in the grid, so this is needed to be executed automatically. //////////
	//////////////////////////////////////////////////////////////////////////
}

