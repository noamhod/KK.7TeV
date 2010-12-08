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
	
	m_rootfile->cd();
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
	//m_mcAnalysis->write();

	// tree
	// the tree will split into multiple files
	m_rootfile = m_mcAnalysis->m_muD3PD->m_tree->GetCurrentFile();
	m_rootfile->cd();
	m_mcAnalysis->m_muD3PD->m_tree->Write();
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
	
	m_dirFit = m_rootfile->mkdir("fit");
	
	m_mcAnalysis->bookFitHistos(m_dirAllCuts);	
	
	m_dirPerformance = m_rootfile->mkdir("performance");
	
	m_dirAfb = m_rootfile->mkdir("Afb");
}

void mcAnalysisGridControl::draw()
{
	m_mcAnalysis->drawBareHistos(m_dirNoCuts);

	// these calculations must come before drawHistos
	bool isTruth = false;
	m_mcAnalysis->calculateEfficiency(m_mcAnalysis->h1_tagNprobe_candidates_pT, m_mcAnalysis->h1_tagNprobe_succeeded_pT, m_mcAnalysis->h1_tagNprobe_efficiency_pT, isTruth);
	m_mcAnalysis->calculateEfficiency(m_mcAnalysis->h1_tagNprobe_candidates_eta, m_mcAnalysis->h1_tagNprobe_succeeded_eta, m_mcAnalysis->h1_tagNprobe_efficiency_eta, isTruth);
	m_mcAnalysis->calculateEfficiency(m_mcAnalysis->h1_tagNprobe_candidates_phi, m_mcAnalysis->h1_tagNprobe_succeeded_phi, m_mcAnalysis->h1_tagNprobe_efficiency_phi, isTruth);
	isTruth = true;
	m_mcAnalysis->calculateEfficiency(m_mcAnalysis->h1_truth_candidates_pT, m_mcAnalysis->h1_truth_succeeded_pT, m_mcAnalysis->h1_truth_efficiency_pT, isTruth);
	m_mcAnalysis->calculateEfficiency(m_mcAnalysis->h1_truth_candidates_eta, m_mcAnalysis->h1_truth_succeeded_eta, m_mcAnalysis->h1_truth_efficiency_eta, isTruth);
	m_mcAnalysis->calculateEfficiency(m_mcAnalysis->h1_truth_candidates_phi, m_mcAnalysis->h1_truth_succeeded_phi, m_mcAnalysis->h1_truth_efficiency_phi, isTruth);
	
	m_mcAnalysis->calculateAfb(m_mcAnalysis->h1_Afb, m_dirAfb);
	
	m_mcAnalysis->drawHistos(m_dirAllCuts);
	
	m_mcAnalysis->drawHistosMap( m_mcAnalysis->getCutFlowOrderedMapPtr(), m_mcAnalysis->getCutFlowTypeOrderedMapPtr(), m_dirCutFlow );
	
	m_mcAnalysis->drawCutProfileHistosMap( m_dirCutProfile );
	
	m_mcAnalysis->drawPerformance( vEntries, vResMemory, vVirMemory, m_dirPerformance );
	
	m_mcAnalysis->printCutFlowNumbers(l64t_nentries);
	cout << "nMultiMuonEvents = " << m_mcAnalysis->nMultiMuonEvents << endl;
}

void mcAnalysisGridControl::fits()
{
	cout << "### in fits ####" << endl;

	double yields[2];
	
	// Preform the fit
	m_mcAnalysis->minimize( false, m_mcAnalysis->h1_imassFit, yields, m_dirFit );
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
		
		if(l64t_jentry%1000==0)
		{
			gSystem->GetProcInfo(&pi);
			//cout << "RES Mem=" << pi.fMemResident << " VIRT Mem=" << pi.fMemVirtual << endl;
			vResMemory.push_back((double)pi.fMemResident);
			vVirMemory.push_back((double)pi.fMemVirtual);
			vEntries.push_back((int)l64t_jentry);
		}
		
		analyze();
	}
	
	draw();
	
	finalize();
	
	stopTimer(true);
}

