/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "analysisGridControl.h"

analysisGridControl::analysisGridControl()
{

}

analysisGridControl::analysisGridControl( TChain* inchain, TFile* outfile )
{
	string str = "";
	
	initialize();
	
	m_chain    = inchain;
	m_rootfile = outfile;

	m_phys = new physics( m_chain );

	m_rootfile->cd();

	str = "Z_GRL_CURRENT.xml";
	m_GRL = new GRLinterface();
	m_GRL->glrinitialize( (TString)str );

	m_analysis = new analysis( m_phys, m_GRL, m_rootfile, "cutFlow.cuts", "dataPeriods.data", "" );
	
	book();
}

analysisGridControl::~analysisGridControl()
{
	//finalize();
}

void analysisGridControl::initialize()
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
	m_rootfile = NULL;
	m_rootfile = NULL;
}

void analysisGridControl::finalize()
{
	// write the tree
	m_analysis->write();

	// file
	m_rootfile->Write();
	m_rootfile->Close();
}

void analysisGridControl::book()
{
	m_dirNoCuts = m_rootfile->mkdir("noCuts");
	m_analysis->bookBareHistos(m_dirNoCuts);

	m_dirAllCuts = m_rootfile->mkdir("allCuts");
	m_analysis->bookHistos(m_dirAllCuts);

	m_dirCutFlow = m_rootfile->mkdir("cutFlow");
	m_analysis->bookHistosMap( m_analysis->getCutFlowOrderedMapPtr(), m_analysis->getCutFlowTypeOrderedMapPtr(), m_dirCutFlow );
	
	m_analysis->bookFitHistos(m_dirAllCuts);	
}

void analysisGridControl::draw()
{
	m_analysis->drawBareHistos(m_dirNoCuts);
	m_analysis->drawHistos(m_dirAllCuts);
	m_analysis->drawHistosMap( m_analysis->getCutFlowOrderedMapPtr(), m_analysis->getCutFlowTypeOrderedMapPtr(), m_dirCutFlow );

	m_analysis->printCutFlowNumbers(l64t_nentries);
}

void analysisGridControl::fits()
{
	cout << "### in fits ####" << endl;

	double yields[2];
	
	// Preform the fit
	m_analysis->minimize( false, m_analysis->h1_imassFit, yields );
}

void analysisGridControl::analyze()
{
	m_analysis->executeCutFlow();
}

void analysisGridControl::loop(Long64_t startEvent, Long64_t stopAfterNevents)
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
		
		if(l64t_jentry%1000==0) cout << "jentry=" << l64t_jentry << "\t ientry=" << l64t_ientry << "\trun=" << m_phys->RunNumber << "\tlumiblock=" << m_phys->lbn << endl;
		if(l64t_jentry%l64t_mod==0) m_analysis->printCutFlowNumbers(l64t_nentries);
		
		analyze();
	}
	
	draw();
	
	finalize();
}

