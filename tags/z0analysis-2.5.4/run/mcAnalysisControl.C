/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "mcAnalysisControl.h"

mcAnalysisControl::mcAnalysisControl()
{
	initialize();
	
	string str = "";

	str = checkANDsetFilepath("PWD", "/../conf/mcdataset.list");
	string strb = checkANDsetFilepath("PWD", "/mcdatasetdir/");
	makeChain(true, str, strb);

	m_mcPhys = new mcPhysics( m_chain );

	str = "mcAnalysisTrees.root";
	m_treefile = new TFile( str.c_str(), "RECREATE");
	m_treefile->cd();

	str = checkANDsetFilepath("PWD", "/../data/mcAnalysisControl.root");
	m_histfile = new TFile( str.c_str(), "RECREATE");
	m_histfile->cd();


	string str1 = checkANDsetFilepath("PWD", "/../conf/cutFlow.cuts");
	string str2 = checkANDsetFilepath("PWD", "/../conf/dataPeriods.data");
	
	m_mcAnalysis = new analysis( m_mcPhys, m_treefile, str1, str2, "" );

	book();
}

mcAnalysisControl::~mcAnalysisControl()
{
	//finalize();
}

void mcAnalysisControl::initialize()
{
	// run control
	l64t_nentries = 0;
	l64t_nbytes   = 0;
	l64t_nb       = 0;
	l64t_jentry   = 0;
	l64t_ientry   = 0;

	// pointers
	m_mcPhys     = NULL;
	m_mcAnalysis = NULL;
	m_histfile = NULL;
	m_treefile = NULL;
}

void mcAnalysisControl::finalize()
{
	// write the tree
	m_mcAnalysis->write();

	// files
	m_histfile->Write();
	m_histfile->Close();

	m_treefile->Write();
	m_treefile->Close();
}

void mcAnalysisControl::book()
{
	m_dirNoCuts = m_histfile->mkdir("noCuts");
	m_mcAnalysis->bookBareHistos(m_dirNoCuts);

	m_dirAllCuts = m_histfile->mkdir("allCuts");
	m_mcAnalysis->bookHistos(m_dirAllCuts);

	m_dirCutFlow = m_histfile->mkdir("cutFlow");
	m_mcAnalysis->bookHistosMap( m_mcAnalysis->getCutFlowOrderedMapPtr(), m_mcAnalysis->getCutFlowTypeOrderedMapPtr(), m_dirCutFlow );

	m_mcAnalysis->bookFitHistos(m_dirAllCuts);	
}

void mcAnalysisControl::draw()
{
	m_mcAnalysis->drawBareHistos(m_dirNoCuts);
	m_mcAnalysis->drawHistos(m_dirAllCuts);
	m_mcAnalysis->drawHistosMap( m_mcAnalysis->getCutFlowOrderedMapPtr(), m_mcAnalysis->getCutFlowTypeOrderedMapPtr(), m_dirCutFlow );

	m_mcAnalysis->printCutFlowNumbers(l64t_nentries);
}

void mcAnalysisControl::fits()
{
	cout << "### in fits ####" << endl;

	double yields[2];
	
	// Preform the fit
	m_mcAnalysis->minimize( false, m_mcAnalysis->h1_imassFit, yields );
}

void mcAnalysisControl::analyze()
{
	m_mcAnalysis->executeCutFlow();
}

void mcAnalysisControl::loop(Long64_t startEvent, Long64_t stopAfterNevents)
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
		if(l64t_jentry%l64t_mod==0) m_mcAnalysis->printCutFlowNumbers(l64t_nentries);
		
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

