/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "mcAnalysisGridControl.h"

mcAnalysisGridControl::mcAnalysisGridControl()
{

}

mcAnalysisGridControl::mcAnalysisGridControl( TChain* inchain, TFile* outfile )
{
	startTimer();

	string str = "";
	
	initialize();
	
	m_chain    = inchain;
	m_rootfile = outfile;

	m_mcPhys = new mcPhysics( m_chain );

	m_rootfile->cd();
	
	m_mcAnalysis = new mcAnalysis( m_mcPhys, m_rootfile, "cutFlow.cuts", "dataPeriods.data", "" );

	book();
}

mcAnalysisGridControl::~mcAnalysisGridControl()
{
	//finalize();
}

void mcAnalysisGridControl::initialize()
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
	m_rootfile = NULL;
	m_rootfile = NULL;
}

void mcAnalysisGridControl::finalize()
{
	// write the tree
	m_mcAnalysis->write();

	// file
	m_rootfile->Write();
	m_rootfile->Close();
}

void mcAnalysisGridControl::book()
{
	m_dirNoCuts = m_rootfile->mkdir("noCuts");
	m_mcAnalysis->bookBareHistos(m_dirNoCuts);

	m_dirAllCuts = m_rootfile->mkdir("allCuts");
	m_mcAnalysis->bookHistos(m_dirAllCuts);

	m_dirCutFlow = m_rootfile->mkdir("cutFlow");
	m_mcAnalysis->bookHistosMap( m_mcAnalysis->getCutFlowOrderedMapPtr(), m_mcAnalysis->getCutFlowTypeOrderedMapPtr(), m_dirCutFlow );
	
	m_dirCutProfile = m_rootfile->mkdir("cutsProfile");
	m_mcAnalysis->bookCutProfileHistosMap( m_mcAnalysis->getCutFlowOrderedMapPtr(), m_dirCutProfile );	
	
	m_mcAnalysis->bookFitHistos(m_dirAllCuts);	
}

void mcAnalysisGridControl::draw()
{
	m_mcAnalysis->drawBareHistos(m_dirNoCuts);
	m_mcAnalysis->drawHistos(m_dirAllCuts);
	m_mcAnalysis->drawHistosMap( m_mcAnalysis->getCutFlowOrderedMapPtr(), m_mcAnalysis->getCutFlowTypeOrderedMapPtr(), m_dirCutFlow );
	m_mcAnalysis->drawCutProfileHistosMap( m_dirCutProfile );

	m_mcAnalysis->printCutFlowNumbers(l64t_nentries);
	cout << "nMultiMuonEvents = " << m_mcAnalysis->nMultiMuonEvents << endl;
}

void mcAnalysisGridControl::fits()
{
	cout << "### in fits ####" << endl;

	double yields[2];
	
	// Preform the fit
	m_mcAnalysis->minimize( false, m_mcAnalysis->h1_imassFit, yields );
}

void mcAnalysisGridControl::analyze()
{
	m_mcAnalysis->executeCutFlow();
}

void mcAnalysisGridControl::loop(Long64_t startEvent, Long64_t stopAfterNevents)
{
	if (m_mcPhys->fChain == 0)  return;

	l64t_nentries = m_mcPhys->fChain->GetEntriesFast();
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
	
	finalize();
	
	stopTimer(true);
}

