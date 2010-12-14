/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "muSkimMCD3PD.h"

muSkimMCD3PD::muSkimMCD3PD()
{

}

muSkimMCD3PD::~muSkimMCD3PD()
{

}

muSkimMCD3PD::muSkimMCD3PD(mcOfflinePhysics* mcOffPhys, TFile* treeFile, TTree* tree)
{
	m_mcOffPhys = mcOffPhys;
	
	m_treeFile = treeFile;
	m_treeFile->cd();

	m_tree = tree;
	m_tree->SetDirectory(m_treeFile);
	
	setVectorPtrsMC();
	setBranchesMC();
}

TTree* muSkimMCD3PD::getTree()
{
	return m_tree;
}

void muSkimMCD3PD::setVectorPtrsMC()
{
	mu_staco_truth_dr  = new vector<float>;
	mu_staco_truth_E   = new vector<float>;
	mu_staco_truth_pt  = new vector<float>;
	mu_staco_truth_eta = new vector<float>;
	mu_staco_truth_phi = new vector<float>;
	mu_staco_truth_type          = new vector<int>;
	mu_staco_truth_status        = new vector<int>;
	mu_staco_truth_barcode       = new vector<int>;
	mu_staco_truth_mothertype    = new vector<int>;
	mu_staco_truth_motherbarcode = new vector<int>;
	mu_staco_truth_matched       = new vector<int>;

	// muid truth
	mu_muid_truth_dr            = new vector<float>;
	mu_muid_truth_E             = new vector<float>;
	mu_muid_truth_pt            = new vector<float>;
	mu_muid_truth_eta           = new vector<float>;
	mu_muid_truth_phi           = new vector<float>;
	mu_muid_truth_type          = new vector<int>;
	mu_muid_truth_status        = new vector<int>;
	mu_muid_truth_barcode       = new vector<int>;
	mu_muid_truth_mothertype    = new vector<int>;
	mu_muid_truth_motherbarcode = new vector<int>;
	mu_muid_truth_matched       = new vector<int>;
	
	// muonTruth
	muonTruth_pt      = new vector<float>;
	muonTruth_m       = new vector<float>;
	muonTruth_eta     = new vector<float>;
	muonTruth_phi     = new vector<float>;
	muonTruth_charge  = new vector<float>;
	muonTruth_PDGID   = new vector<int>;
	muonTruth_barcode = new vector<int>;
	muonTruth_type    = new vector<int>;
	muonTruth_origin  = new vector<int>;
	
	// MC event
	mcevt_signal_process_id = new vector<int>;
	mcevt_event_number      = new vector<int>;
	mcevt_event_scale       = new vector<double>;
	mcevt_alphaQCD          = new vector<double>;
	mcevt_alphaQED          = new vector<double>;
	mcevt_pdf_id1           = new vector<int>;
	mcevt_pdf_id2           = new vector<int>;
	mcevt_pdf_x1            = new vector<double>;
	mcevt_pdf_x2            = new vector<double>;
	mcevt_pdf_scale         = new vector<double>;
	mcevt_pdf1              = new vector<double>;
	mcevt_pdf2              = new vector<double>;
	mcevt_weight            = new vector<double>;
}

void muSkimMCD3PD::resetVectorPtrsMC()
{
	mu_staco_truth_dr->clear();
	mu_staco_truth_E ->clear();
	mu_staco_truth_pt->clear();
	mu_staco_truth_eta->clear();
	mu_staco_truth_phi->clear();
	mu_staco_truth_type->clear();
	mu_staco_truth_status->clear();
	mu_staco_truth_barcode->clear();
	mu_staco_truth_mothertype->clear();
	mu_staco_truth_motherbarcode->clear();
	mu_staco_truth_matched->clear();

	// muid truth
	mu_muid_truth_dr->clear();
	mu_muid_truth_E->clear();
	mu_muid_truth_pt->clear();
	mu_muid_truth_eta->clear();
	mu_muid_truth_phi->clear();
	mu_muid_truth_type->clear();
	mu_muid_truth_status->clear();
	mu_muid_truth_barcode->clear();
	mu_muid_truth_mothertype->clear();
	mu_muid_truth_motherbarcode->clear();
	mu_muid_truth_matched->clear();
	
	// muonTruth
	muonTruth_pt->clear();
	muonTruth_m->clear();
	muonTruth_eta->clear();
	muonTruth_phi->clear();
	muonTruth_charge->clear();
	muonTruth_PDGID->clear();
	muonTruth_barcode->clear();
	muonTruth_type->clear();
	muonTruth_origin->clear();
	
	// MC event
	mcevt_signal_process_id->clear();
	mcevt_event_number->clear();
	mcevt_event_scale->clear();
	mcevt_alphaQCD->clear();
	mcevt_alphaQED->clear();
	mcevt_pdf_id1->clear();
	mcevt_pdf_id2->clear();
	mcevt_pdf_x1->clear();
	mcevt_pdf_x2->clear();
	mcevt_pdf_scale->clear();
	mcevt_pdf1->clear();
	mcevt_pdf2->clear();
	mcevt_weight->clear();
}

void muSkimMCD3PD::setBranchesMC()
{
	// mu_staco_truth
	m_tree->Branch( "mu_staco_truth_E",             &mu_staco_truth_E );
	m_tree->Branch( "mu_staco_truth_pt",            &mu_staco_truth_pt );
	m_tree->Branch( "mu_staco_truth_eta",           &mu_staco_truth_eta );
	m_tree->Branch( "mu_staco_truth_phi",           &mu_staco_truth_phi );
	m_tree->Branch( "mu_staco_truth_type",          &mu_staco_truth_type );
	m_tree->Branch( "mu_staco_truth_mothertype",    &mu_staco_truth_mothertype );
	m_tree->Branch( "mu_staco_truth_barcode",       &mu_staco_truth_barcode );
	m_tree->Branch( "mu_staco_truth_motherbarcode", &mu_staco_truth_motherbarcode );
	m_tree->Branch( "mu_staco_truth_status",        &mu_staco_truth_status );
	m_tree->Branch( "mu_staco_truth_dr",            &mu_staco_truth_dr );
	m_tree->Branch( "mu_staco_truth_matched",       &mu_staco_truth_matched );
	
	// mu_muid_truth
	m_tree->Branch( "mu_muid_truth_E",             &mu_muid_truth_E );
	m_tree->Branch( "mu_muid_truth_pt",            &mu_muid_truth_pt );
	m_tree->Branch( "mu_muid_truth_eta",           &mu_muid_truth_eta );
	m_tree->Branch( "mu_muid_truth_phi",           &mu_muid_truth_phi );
	m_tree->Branch( "mu_muid_truth_type",          &mu_muid_truth_type );
	m_tree->Branch( "mu_muid_truth_mothertype",    &mu_muid_truth_mothertype );
	m_tree->Branch( "mu_muid_truth_barcode",       &mu_muid_truth_barcode );
	m_tree->Branch( "mu_muid_truth_motherbarcode", &mu_muid_truth_motherbarcode );
	m_tree->Branch( "mu_muid_truth_status",        &mu_muid_truth_status );
	m_tree->Branch( "mu_muid_truth_dr",            &mu_muid_truth_dr );
	m_tree->Branch( "mu_muid_truth_matched",       &mu_muid_truth_matched );

	// muonTruth
	m_tree->Branch( "muonTruth_n",      &muonTruth_n );
	m_tree->Branch( "muonTruth_pt",     &muonTruth_pt );
	m_tree->Branch( "muonTruth_m",      &muonTruth_m );
	m_tree->Branch( "muonTruth_eta",    &muonTruth_eta );
	m_tree->Branch( "muonTruth_phi",    &muonTruth_phi );
	m_tree->Branch( "muonTruth_charge", &muonTruth_charge );
	m_tree->Branch( "muonTruth_PDGID",  &muonTruth_PDGID );
	m_tree->Branch( "muonTruth_barcode",&muonTruth_barcode );
	m_tree->Branch( "muonTruth_type",   &muonTruth_type );
	m_tree->Branch( "muonTruth_origin", &muonTruth_origin );
	
	// MC event
	m_tree->Branch( "mcevt_n",                 &mcevt_n );
	m_tree->Branch( "mcevt_signal_process_id", &mcevt_signal_process_id );
	m_tree->Branch( "mcevt_event_number",      &mcevt_event_number );
	m_tree->Branch( "mcevt_event_scale",       &mcevt_event_scale );
	m_tree->Branch( "mcevt_alphaQCD",          &mcevt_alphaQCD );
	m_tree->Branch( "mcevt_alphaQED",          &mcevt_alphaQED );
	m_tree->Branch( "mcevt_pdf_id1",           &mcevt_pdf_id1 );
	m_tree->Branch( "mcevt_pdf_id2",           &mcevt_pdf_id2 );
	m_tree->Branch( "mcevt_pdf_x1",            &mcevt_pdf_x1 );
	m_tree->Branch( "mcevt_pdf_x2",            &mcevt_pdf_x2 );
	m_tree->Branch( "mcevt_pdf_scale",         &mcevt_pdf_scale );
	m_tree->Branch( "mcevt_pdf1",              &mcevt_pdf1 );
	m_tree->Branch( "mcevt_pdf2",              &mcevt_pdf2 );
	m_tree->Branch( "mcevt_weight",            &mcevt_weight );
}

void muSkimMCD3PD::fillMC()
{	
	///////////////////////////////////////////////////////////////////
	// this method do not call TTree::Fill() !!! //////////////////////
	// instead, it is done by the muD3PD class, right after this //////
	// method (fillMC) was called - order matters !!! /////////////////
	///////////////////////////////////////////////////////////////////
	
	// staco truth
	int nStacoTruth = (int)m_mcOffPhys->mu_staco_truth_E->size();
	for(int i=0 ; i<nStacoTruth ; i++)
	{
		mu_staco_truth_E->push_back( m_mcOffPhys->mu_staco_truth_E->at(i) );
		mu_staco_truth_pt->push_back( m_mcOffPhys->mu_staco_truth_pt->at(i) );
		mu_staco_truth_eta->push_back( m_mcOffPhys->mu_staco_truth_eta->at(i) );
		mu_staco_truth_phi->push_back( m_mcOffPhys->mu_staco_truth_phi->at(i) );
		mu_staco_truth_type->push_back( m_mcOffPhys->mu_staco_truth_type->at(i) );
		mu_staco_truth_mothertype->push_back( m_mcOffPhys->mu_staco_truth_mothertype->at(i) );
		mu_staco_truth_barcode->push_back( m_mcOffPhys->mu_staco_truth_barcode->at(i) );
		mu_staco_truth_motherbarcode->push_back( m_mcOffPhys->mu_staco_truth_motherbarcode->at(i) );
		mu_staco_truth_status->push_back( m_mcOffPhys->mu_staco_truth_status->at(i) );
		mu_staco_truth_dr->push_back( m_mcOffPhys->mu_staco_truth_dr->at(i) );
		mu_staco_truth_matched->push_back( m_mcOffPhys->mu_staco_truth_matched->at(i) );
	}
	
	// muid truth
	int nMuidTruth = (int)m_mcOffPhys->mu_muid_truth_E->size();
	for(int i=0 ; i<nMuidTruth ; i++)
	{
		mu_muid_truth_E->push_back( m_mcOffPhys->mu_muid_truth_E->at(i) );
		mu_muid_truth_pt->push_back( m_mcOffPhys->mu_muid_truth_pt->at(i) );
		mu_muid_truth_eta->push_back( m_mcOffPhys->mu_muid_truth_eta->at(i) );
		mu_muid_truth_phi->push_back( m_mcOffPhys->mu_muid_truth_phi->at(i) );
		mu_muid_truth_type->push_back( m_mcOffPhys->mu_muid_truth_type->at(i) );
		mu_muid_truth_mothertype->push_back( m_mcOffPhys->mu_muid_truth_mothertype->at(i) );
		mu_muid_truth_barcode->push_back( m_mcOffPhys->mu_muid_truth_barcode->at(i) );
		mu_muid_truth_motherbarcode->push_back( m_mcOffPhys->mu_muid_truth_motherbarcode->at(i) );
		mu_muid_truth_status->push_back( m_mcOffPhys->mu_muid_truth_status->at(i) );
		mu_muid_truth_dr->push_back( m_mcOffPhys->mu_muid_truth_dr->at(i) );
		mu_muid_truth_matched->push_back( m_mcOffPhys->mu_muid_truth_matched->at(i) );
	}
	
	
	// muonTruth
	muonTruth_n = (int)m_mcOffPhys->muonTruth_n;
	int nMuonTruth = (int)m_mcOffPhys->muonTruth_pt->size();
	for(int i=0 ; i<nMuonTruth ; i++)
	{	
		muonTruth_pt->push_back( m_mcOffPhys->muonTruth_pt->at(i) );
		muonTruth_m->push_back( m_mcOffPhys->muonTruth_m->at(i) );
		muonTruth_eta->push_back( m_mcOffPhys->muonTruth_eta->at(i) );
		muonTruth_phi->push_back( m_mcOffPhys->muonTruth_phi->at(i) );
		muonTruth_charge->push_back( m_mcOffPhys->muonTruth_charge->at(i) );
		muonTruth_PDGID->push_back( m_mcOffPhys->muonTruth_PDGID->at(i) );
		//muonTruth_barcode->push_back( m_mcOffPhys->muonTruth_barcode->at(i) );
		muonTruth_type->push_back( m_mcOffPhys->muonTruth_type->at(i) );
		muonTruth_origin->push_back( m_mcOffPhys->muonTruth_origin->at(i) );
	}
	
	// MC event
	mcevt_n = (int)m_mcOffPhys->mcevt_n;
	int nMCevt = (int)m_mcOffPhys->mcevt_signal_process_id->size();
	for(int i=0 ; i<nMCevt ; i++)
	{
		mcevt_signal_process_id->push_back( m_mcOffPhys->mcevt_signal_process_id->at(i) );
		mcevt_event_number->push_back( m_mcOffPhys->mcevt_event_number->at(i) );
		mcevt_event_scale->push_back( m_mcOffPhys->mcevt_event_scale->at(i) );
		mcevt_alphaQCD->push_back( m_mcOffPhys->mcevt_alphaQCD->at(i) );
		mcevt_alphaQED->push_back( m_mcOffPhys->mcevt_alphaQED->at(i) );
		mcevt_pdf_id1->push_back( m_mcOffPhys->mcevt_pdf_id1->at(i) );
		mcevt_pdf_id2->push_back( m_mcOffPhys->mcevt_pdf_id2->at(i) );
		mcevt_pdf_x1->push_back( m_mcOffPhys->mcevt_pdf_x1->at(i) );
		mcevt_pdf_x2->push_back( m_mcOffPhys->mcevt_pdf_x2->at(i) );
		mcevt_pdf_scale->push_back( m_mcOffPhys->mcevt_pdf_scale->at(i) );
		mcevt_pdf1->push_back( m_mcOffPhys->mcevt_pdf1->at(i) );
		mcevt_pdf2->push_back( m_mcOffPhys->mcevt_pdf2->at(i) );
		mcevt_weight->push_back( m_mcOffPhys->mcevt_weight->at(i) );
	}
}



