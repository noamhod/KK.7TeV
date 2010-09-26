/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "mcOffTree.h"

mcOffTree::mcOffTree()
{

}

mcOffTree::~mcOffTree()
{

}

mcOffTree::mcOffTree(mcPhysics* mcPhys, TFile* treeFile, TTree* tree)
{
	m_mcPhys = mcPhys;

	m_treeFile = treeFile;
	
	m_tree = tree;

	m_treeFile->cd();
	
	setBranchesMC();
}

void mcOffTree::setBranchesMC()
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

void mcOffTree::fillMC()
{
	///////////////////////////////////////////////////////////////////
	// this method do not call TTree::Fill() !!! //////////////////////
	// instead, it is done by the offTree class, right after this /////
	// method (fillMC) was called - order matters !!! /////////////////
	///////////////////////////////////////////////////////////////////

	// staco truth
	mu_staco_truth_E          = m_mcPhys->mu_staco_truth_E;
	mu_staco_truth_pt         = m_mcPhys->mu_staco_truth_pt;
	mu_staco_truth_eta        = m_mcPhys->mu_staco_truth_eta;
	mu_staco_truth_phi        = m_mcPhys->mu_staco_truth_phi;
	mu_staco_truth_type       = m_mcPhys->mu_staco_truth_type;
	mu_staco_truth_mothertype = m_mcPhys->mu_staco_truth_mothertype;
	mu_staco_truth_barcode    = m_mcPhys->mu_staco_truth_barcode;
	mu_staco_truth_motherbarcode = m_mcPhys->mu_staco_truth_motherbarcode;
	mu_staco_truth_status        = m_mcPhys->mu_staco_truth_status;
	mu_staco_truth_dr            = m_mcPhys->mu_staco_truth_dr;
	mu_staco_truth_matched       = m_mcPhys->mu_staco_truth_matched;
	
	// muid truth
	mu_muid_truth_E          = m_mcPhys->mu_muid_truth_E;
	mu_muid_truth_pt         = m_mcPhys->mu_muid_truth_pt;
	mu_muid_truth_eta        = m_mcPhys->mu_muid_truth_eta;
	mu_muid_truth_phi        = m_mcPhys->mu_muid_truth_phi;
	mu_muid_truth_type       = m_mcPhys->mu_muid_truth_type;
	mu_muid_truth_mothertype = m_mcPhys->mu_muid_truth_mothertype;
	mu_muid_truth_barcode    = m_mcPhys->mu_muid_truth_barcode;
	mu_muid_truth_motherbarcode = m_mcPhys->mu_muid_truth_motherbarcode;
	mu_muid_truth_status        = m_mcPhys->mu_muid_truth_status;
	mu_muid_truth_dr            = m_mcPhys->mu_muid_truth_dr;
	mu_muid_truth_matched       = m_mcPhys->mu_muid_truth_matched;
	
	// muonTruth
	muonTruth_n      = m_mcPhys->muonTruth_n;
	muonTruth_pt     = m_mcPhys->muonTruth_pt;
	muonTruth_m      = m_mcPhys->muonTruth_m;
	muonTruth_eta    = m_mcPhys->muonTruth_eta;
	muonTruth_phi    = m_mcPhys->muonTruth_phi;
	muonTruth_charge = m_mcPhys->muonTruth_charge;
	muonTruth_PDGID  = m_mcPhys->muonTruth_PDGID;
	muonTruth_type   = m_mcPhys->muonTruth_type;
	muonTruth_origin = m_mcPhys->muonTruth_origin;
	
	// MC event
	mcevt_n                 = m_mcPhys->mcevt_n;
	mcevt_signal_process_id = m_mcPhys->mcevt_signal_process_id;
	mcevt_event_number      = m_mcPhys->mcevt_event_number;
	mcevt_event_scale       = m_mcPhys->mcevt_event_scale;
	mcevt_alphaQCD          = m_mcPhys->mcevt_alphaQCD;
	mcevt_alphaQED          = m_mcPhys->mcevt_alphaQED;
	mcevt_pdf_id1           = m_mcPhys->mcevt_pdf_id1;
	mcevt_pdf_id2           = m_mcPhys->mcevt_pdf_id2;
	mcevt_pdf_x1            = m_mcPhys->mcevt_pdf_x1;
	mcevt_pdf_x2            = m_mcPhys->mcevt_pdf_x2;
	mcevt_pdf_scale         = m_mcPhys->mcevt_pdf_scale;
	mcevt_pdf1              = m_mcPhys->mcevt_pdf1;
	mcevt_pdf2              = m_mcPhys->mcevt_pdf2;
	mcevt_weight            = m_mcPhys->mcevt_weight;
}

void mcOffTree::resetMC()
{
	// staco truth
	mu_staco_truth_E             = NULL;
	mu_staco_truth_pt            = NULL;
	mu_staco_truth_eta           = NULL;
	mu_staco_truth_phi           = NULL;
	mu_staco_truth_type          = NULL;
	mu_staco_truth_mothertype    = NULL;
	mu_staco_truth_barcode       = NULL;
	mu_staco_truth_motherbarcode = NULL;
	mu_staco_truth_status        = NULL;
	mu_staco_truth_dr            = NULL;
	mu_staco_truth_matched       = NULL;
	
	// muid truth
	mu_muid_truth_E             = NULL;
	mu_muid_truth_pt            = NULL;
	mu_muid_truth_eta           = NULL;
	mu_muid_truth_phi           = NULL;
	mu_muid_truth_type          = NULL;
	mu_muid_truth_mothertype    = NULL;
	mu_muid_truth_barcode       = NULL;
	mu_muid_truth_motherbarcode = NULL;
	mu_muid_truth_status        = NULL;
	mu_muid_truth_dr            = NULL;
	mu_muid_truth_matched       = NULL;
	
	// muonTruth
	muonTruth_n      = -999;
	muonTruth_pt     = NULL;
	muonTruth_m      = NULL;
	muonTruth_eta    = NULL;
	muonTruth_phi    = NULL;
	muonTruth_charge = NULL;
	muonTruth_PDGID  = NULL;
	muonTruth_type   = NULL;
	muonTruth_origin = NULL;
	
	// MC event
	mcevt_n                 = -999;
	mcevt_signal_process_id = NULL;
	mcevt_event_number      = NULL;
	mcevt_event_scale       = NULL;
	mcevt_alphaQCD          = NULL;
	mcevt_alphaQED          = NULL;
	mcevt_pdf_id1           = NULL;
	mcevt_pdf_id2           = NULL;
	mcevt_pdf_x1            = NULL;
	mcevt_pdf_x2            = NULL;
	mcevt_pdf_scale         = NULL;
	mcevt_pdf1              = NULL;
	mcevt_pdf2              = NULL;
	mcevt_weight            = NULL;

}
