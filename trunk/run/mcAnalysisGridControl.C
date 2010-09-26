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
	string str = "";
	
	initialize();
	
	m_chain    = inchain;
	m_rootfile = outfile;

	m_mcPhys = new mcPhysics( m_chain );

	m_rootfile->cd();

	m_graphics = new graphicObjects();
	m_graphics->setStyle();

	str = "cutFlow.cuts";
	m_cutFlowHandler = new cutFlowHandler(str);
	
	m_mcAnalysis = new mcAnalysis( m_mcPhys, m_graphics, m_cutFlowHandler, m_rootfile );

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
	m_graphics = NULL;
	m_rootfile = NULL;
	m_rootfile = NULL;

	kinitialize();
	uinitialize();
}

void mcAnalysisGridControl::finalize()
{
	// write the tree
	m_mcAnalysis->write();

	// file
	m_rootfile->Write();
	m_rootfile->Close();

	kfinalize();
	ufinalize();
}

void mcAnalysisGridControl::book()
{
	m_dirNoCuts = m_rootfile->mkdir("noCuts");
	m_graphics->bookBareHistos(m_dirNoCuts);

	m_dirAllCuts = m_rootfile->mkdir("allCuts");
	m_graphics->bookHistos(m_dirAllCuts);

	m_dirCutFlow = m_rootfile->mkdir("cutFlow");
	m_graphics->bookHistosMap( m_cutFlowHandler->getCutFlowOrderedMapPtr(), m_cutFlowHandler->getCutFlowTypeOrderedMapPtr(), m_dirCutFlow );	
}

void mcAnalysisGridControl::draw()
{
	m_graphics->drawBareHistos(m_dirNoCuts);
	m_graphics->drawHistos(m_dirAllCuts);
	m_graphics->drawHistosMap( m_cutFlowHandler->getCutFlowOrderedMapPtr(), m_cutFlowHandler->getCutFlowTypeOrderedMapPtr(), m_dirCutFlow );

	m_cutFlowHandler->printCutFlowNumbers(l64t_nentries);
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
		if(l64t_jentry%l64t_mod==0) m_cutFlowHandler->printCutFlowNumbers(l64t_nentries);
		
		analyze();
	}
	
	draw();
	
	finalize();
}

