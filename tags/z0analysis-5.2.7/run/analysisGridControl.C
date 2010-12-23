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
	startTimer();
	
	m_muRecAlgo = "staco";

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
	
	m_rootfile->cd();
}

analysisGridControl::~analysisGridControl()
{
	
}

void analysisGridControl::setRecAlgo(string muRecAlgo)
{
	if(muRecAlgo!="staco"  &&  muRecAlgo!="muid")
	{
		cout << "WARNING: muRecAlgo=" << muRecAlgo << " is not supported, setting to default (staco)" << endl;
		muRecAlgo = "staco";
	}
	m_muRecAlgo = muRecAlgo;
}

void analysisGridControl::initialize()
{
	// run control
	l64t_nentries = 0;
	l64t_nbytes   = 0;
	l64t_nb       = 0;
	l64t_jentry   = 0;
	l64t_ientry   = 0;
}

void analysisGridControl::finalize()
{
	// write the tree
	//m_analysis->write();

	// tree
	// the tree will split into multiple files
	m_rootfile = m_analysis->m_muD3PD->m_tree->GetCurrentFile();
	m_rootfile->cd();
	m_analysis->m_muD3PD->m_tree->Write();
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
	
	m_dirCutProfile = m_rootfile->mkdir("cutsProfile");
	m_analysis->bookCutProfileHistosMap( m_analysis->getCutFlowOrderedMapPtr(), m_dirCutProfile );
	
	m_dirFit = m_rootfile->mkdir("fit");
	m_analysis->bookFitHistos(m_dirFit);
	
	m_dirEff = m_rootfile->mkdir("efficiency");
	m_analysis->bookEfficiencyHistos(m_analysis->m_period2triggerperiodMap, m_dirEff);
	
	m_analysis->setTrees(m_dirAllCuts, m_dirCutProfile, m_dirEff);

	m_dirPerformance = m_rootfile->mkdir("performance");
}

void analysisGridControl::draw()
{
	m_analysis->drawBareHistos(m_dirNoCuts);
	
	// these calculations must come before drawHistos
	m_analysis->calculateAfb(m_analysis->h1_Afb);
	
	m_analysis->drawHistos(m_dirAllCuts);
	
	m_analysis->drawHistosMap( m_analysis->getCutFlowOrderedMapPtr(), m_analysis->getCutFlowTypeOrderedMapPtr(), m_dirCutFlow );
	
	m_analysis->drawCutProfileHistosMap( m_dirCutProfile );
	
	bool isTruth = false;
	m_analysis->calculateEfficiency(m_analysis->h1map_tagNprobe_candidates_pT,
									m_analysis->h1map_tagNprobe_succeeded_pT,
									m_analysis->h1map_tagNprobe_trigEff_pT, isTruth);
	m_analysis->calculateEfficiency(m_analysis->h1map_tagNprobe_candidates_eta,
									m_analysis->h1map_tagNprobe_succeeded_eta,
									m_analysis->h1map_tagNprobe_trigEff_eta, isTruth);
	m_analysis->calculateEfficiency(m_analysis->h1map_tagNprobe_candidates_phi,
									m_analysis->h1map_tagNprobe_succeeded_phi,
									m_analysis->h1map_tagNprobe_trigEff_phi, isTruth);
	isTruth = true;
	m_analysis->calculateEfficiency(m_analysis->h1map_truth_candidates_pT,
									m_analysis->h1map_truth_succeeded_pT,
									m_analysis->h1map_truth_trigEff_pT, isTruth);
	m_analysis->calculateEfficiency(m_analysis->h1map_truth_candidates_eta,
									m_analysis->h1map_truth_succeeded_eta,
									m_analysis->h1map_truth_trigEff_eta, isTruth);
	m_analysis->calculateEfficiency(m_analysis->h1map_truth_candidates_phi,
									m_analysis->h1map_truth_succeeded_phi,
									m_analysis->h1map_truth_trigEff_phi, isTruth);
	m_analysis->drawEfficiencyHistosMap(m_dirEff);
	
	m_analysis->drawPerformance( vEntries, vResMemory, vVirMemory, m_dirPerformance );
	
	m_analysis->printCutFlowNumbers(l64t_nentries);
}

void analysisGridControl::fits()
{
	double yields[2];
	
	// Preform the fit
	m_analysis->minimize( false, m_analysis->h1_imassFit, yields, m_dirFit );
}

void analysisGridControl::analyze()
{
	m_analysis->execute(m_muRecAlgo);
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
	
	cout << "nAll = " << m_analysis->nAll << endl;
	cout << "n0mu(pT>15GeV) = " << m_analysis->n0mu << endl;
	cout << "n1mu(pT>15GeV) = " << m_analysis->n1mu << endl;
	cout << "n2mu(pT>15GeV) = " << m_analysis->n2mu << endl;
	cout << "n3mu(pT>15GeV) = " << m_analysis->n3mu << endl;
	cout << "n4mu(pT>15GeV) = " << m_analysis->n4mu << endl;
	cout << "nNmu(pT>15GeV) = " << m_analysis->nNmu << endl;
}

