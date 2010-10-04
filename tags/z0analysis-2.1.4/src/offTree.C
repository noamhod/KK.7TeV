/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "offTree.h"

offTree::offTree()
{

}

offTree::~offTree()
{

}

offTree::offTree(physics* phys, mcPhysics* mcPhys, TFile* treeFile)
{
	m_phys = phys;
	m_mcPhys = mcPhys;

	m_treeFile = treeFile;

	m_treeFile->cd();

	m_tree = new TTree("offline", "offline");

	//m_tree->SetMaxTreeSize(50000000); // 50Mb per file
	
	setBranches();
}

TTree* offTree::getTree()
{
	return m_tree;
}

void offTree::setBranches()
{	
	// run variables branches
	m_tree->Branch( "RunNumber",   &RunNumber );
	m_tree->Branch( "lbn",         &lbn );
	m_tree->Branch( "EventNumber", &EventNumber );
	
	// preselection
	m_tree->Branch( "isGRL",  &isGRL );
	m_tree->Branch( "L1_MU6", &L1_MU6 );
	m_tree->Branch( "EF_mu10", &EF_mu10 );
	m_tree->Branch( "EF_mu13", &EF_mu13 );
	m_tree->Branch( "EF_mu15", &EF_mu15 );
	m_tree->Branch( "EF_mu20", &EF_mu20 );
	m_tree->Branch( "EF_mu4", &EF_mu4 );
	m_tree->Branch( "EF_mu6", &EF_mu6 );
	
	// mu_staco
	m_tree->Branch( "mu_staco_n",         &mu_staco_n );
	m_tree->Branch( "mu_staco_px",        &mu_staco_px );
	m_tree->Branch( "mu_staco_py",        &mu_staco_py );
	m_tree->Branch( "mu_staco_pz",        &mu_staco_pz );
	m_tree->Branch( "mu_staco_E",         &mu_staco_E );
	m_tree->Branch( "mu_staco_m",         &mu_staco_m );
	m_tree->Branch( "mu_staco_charge",    &mu_staco_charge );
	m_tree->Branch( "mu_staco_pt",        &mu_staco_pt );
	m_tree->Branch( "mu_staco_ptcone20",  &mu_staco_ptcone20 );
	m_tree->Branch( "mu_staco_ptcone30",  &mu_staco_ptcone30 );
	m_tree->Branch( "mu_staco_ptcone40",  &mu_staco_ptcone40 );
	m_tree->Branch( "mu_staco_eta",       &mu_staco_eta );
	m_tree->Branch( "mu_staco_phi",       &mu_staco_phi );
	m_tree->Branch( "mu_staco_d0_exPV",   &mu_staco_d0_exPV );
	m_tree->Branch( "mu_staco_z0_exPV",   &mu_staco_z0_exPV );
	m_tree->Branch( "mu_staco_allauthor", &mu_staco_allauthor );
	m_tree->Branch( "mu_staco_author",    &mu_staco_author);
	m_tree->Branch( "mu_staco_matchchi2", &mu_staco_matchchi2);
	m_tree->Branch( "mu_staco_matchndof", &mu_staco_matchndof);
	m_tree->Branch( "mu_staco_me_qoverp",       &mu_staco_me_qoverp );
	m_tree->Branch( "mu_staco_id_qoverp",       &mu_staco_id_qoverp );
	m_tree->Branch( "mu_staco_me_theta",        &mu_staco_me_theta );
	m_tree->Branch( "mu_staco_id_theta",        &mu_staco_id_theta );
	m_tree->Branch( "mu_staco_isCombinedMuon",  &mu_staco_isCombinedMuon );
	m_tree->Branch( "mu_staco_nSCTHits",        &mu_staco_nSCTHits );
	m_tree->Branch( "mu_staco_nPixHits",        &mu_staco_nPixHits );
	
	// mu_muid
	m_tree->Branch( "mu_muid_n",         &mu_muid_n );
	m_tree->Branch( "mu_muid_px",        &mu_muid_px );
	m_tree->Branch( "mu_muid_py",        &mu_muid_py );
	m_tree->Branch( "mu_muid_pz",        &mu_muid_pz );
	m_tree->Branch( "mu_muid_E",         &mu_muid_E );
	m_tree->Branch( "mu_muid_m",         &mu_muid_m );
	m_tree->Branch( "mu_muid_charge",    &mu_muid_charge );
	m_tree->Branch( "mu_muid_pt",        &mu_muid_pt );
	m_tree->Branch( "mu_muid_ptcone20",  &mu_muid_ptcone20 );
	m_tree->Branch( "mu_muid_ptcone30",  &mu_muid_ptcone30 );
	m_tree->Branch( "mu_muid_ptcone40",  &mu_muid_ptcone40 );
	m_tree->Branch( "mu_muid_eta",       &mu_muid_eta );
	m_tree->Branch( "mu_muid_phi",       &mu_muid_phi );
	m_tree->Branch( "mu_muid_d0_exPV",   &mu_muid_d0_exPV );
	m_tree->Branch( "mu_muid_z0_exPV",   &mu_muid_z0_exPV );
	m_tree->Branch( "mu_muid_allauthor", &mu_muid_allauthor );
	m_tree->Branch( "mu_muid_author",    &mu_muid_author);
	m_tree->Branch( "mu_muid_matchchi2", &mu_staco_matchchi2);
	m_tree->Branch( "mu_muid_matchndof", &mu_staco_matchndof);
	m_tree->Branch( "mu_muid_me_qoverp",       &mu_muid_me_qoverp );
	m_tree->Branch( "mu_muid_id_qoverp",       &mu_muid_id_qoverp );
	m_tree->Branch( "mu_muid_me_theta",        &mu_muid_me_theta );
	m_tree->Branch( "mu_muid_id_theta",        &mu_muid_id_theta );
	m_tree->Branch( "mu_muid_isCombinedMuon",  &mu_muid_isCombinedMuon );
	m_tree->Branch( "mu_muid_nSCTHits",        &mu_muid_nSCTHits );
	m_tree->Branch( "mu_muid_nPixHits",        &mu_muid_nPixHits );
	
	// vertex branches
	m_tree->Branch( "vxp_n",       &vxp_n );
	m_tree->Branch( "vxp_nTracks", &vxp_nTracks );
	m_tree->Branch( "vxp_type",    &vxp_type );
	m_tree->Branch( "vxp_z",       &vxp_z );
	m_tree->Branch( "vxp_z_err",   &vxp_z_err );	
}

void offTree::fill()
{
	///////////////////////////////
	m_tree->Fill(); ///////////////
	///////////////////////////////
}

void offTree::fill(int isGrl)
{
	if(m_mcPhys==NULL  &&  m_phys!=NULL)
	{
		// fill run branches
		RunNumber   = m_phys->RunNumber;
		lbn         = m_phys->lbn;
		EventNumber = m_phys->EventNumber;
		
		// preselection
		isGRL   = isGrl;
		L1_MU6  = m_phys->L1_MU6;
		EF_mu10 = m_phys->EF_mu10;
		EF_mu13 = m_phys->EF_mu13;
		EF_mu15 = m_phys->EF_mu15;
		EF_mu20 = m_phys->EF_mu20;
		EF_mu4  = m_phys->EF_mu4;
		EF_mu6  = m_phys->EF_mu6;
		
		// staco
		mu_staco_n        = m_phys->mu_staco_n;
		mu_staco_px       = m_phys->mu_staco_px;
		mu_staco_py       = m_phys->mu_staco_py;
		mu_staco_pz       = m_phys->mu_staco_pz;
		mu_staco_E        = m_phys->mu_staco_E;
		mu_staco_m        = m_phys->mu_staco_m;
		mu_staco_charge   = m_phys->mu_staco_charge;
		mu_staco_pt       = m_phys->mu_staco_pt;
		mu_staco_ptcone20 = m_phys->mu_staco_ptcone20;
		mu_staco_ptcone30 = m_phys->mu_staco_ptcone30;
		mu_staco_ptcone40 = m_phys->mu_staco_ptcone40;
		mu_staco_eta      = m_phys->mu_staco_eta;
		mu_staco_phi      = m_phys->mu_staco_phi;
		mu_staco_d0_exPV  = m_phys->mu_staco_d0_exPV;
		mu_staco_z0_exPV  = m_phys->mu_staco_z0_exPV;
		mu_staco_allauthor= m_phys->mu_staco_allauthor;
		mu_staco_author   = m_phys->mu_staco_author;
		mu_staco_matchchi2   = m_phys->mu_staco_matchchi2;
		mu_staco_matchndof   = m_phys->mu_staco_matchndof;
		mu_staco_me_qoverp= m_phys->mu_staco_me_qoverp;
		mu_staco_id_qoverp= m_phys->mu_staco_id_qoverp;
		mu_staco_me_theta = m_phys->mu_staco_me_theta;
		mu_staco_id_theta = m_phys->mu_staco_id_theta;
		mu_staco_isCombinedMuon = m_phys->mu_staco_isCombinedMuon;
		mu_staco_nSCTHits = m_phys->mu_staco_nSCTHits;
		mu_staco_nPixHits = m_phys->mu_staco_nPixHits;
		
		// muid
		mu_muid_n        = m_phys->mu_muid_n;
		mu_muid_px       = m_phys->mu_muid_px;
		mu_muid_py       = m_phys->mu_muid_py;
		mu_muid_pz       = m_phys->mu_muid_pz;
		mu_muid_E        = m_phys->mu_muid_E;
		mu_muid_m        = m_phys->mu_muid_m;
		mu_muid_charge   = m_phys->mu_muid_charge;
		mu_muid_pt       = m_phys->mu_muid_pt;
		mu_muid_ptcone20 = m_phys->mu_muid_ptcone20;
		mu_muid_ptcone30 = m_phys->mu_muid_ptcone30;
		mu_muid_ptcone40 = m_phys->mu_muid_ptcone40;
		mu_muid_eta      = m_phys->mu_muid_eta;
		mu_muid_phi      = m_phys->mu_muid_phi;
		mu_muid_d0_exPV  = m_phys->mu_muid_d0_exPV;
		mu_muid_z0_exPV  = m_phys->mu_muid_z0_exPV;
		mu_muid_allauthor= m_phys->mu_muid_allauthor;
		mu_muid_author   = m_phys->mu_muid_author;
		mu_muid_matchchi2 = m_phys->mu_muid_matchchi2;
		mu_muid_matchndof = m_phys->mu_muid_matchndof;
		mu_muid_me_qoverp = m_phys->mu_muid_me_qoverp;
		mu_muid_id_qoverp = m_phys->mu_muid_id_qoverp;
		mu_muid_me_theta = m_phys->mu_muid_me_theta;
		mu_muid_id_theta = m_phys->mu_muid_id_theta;
		mu_muid_isCombinedMuon = m_phys->mu_muid_isCombinedMuon;
		mu_muid_nSCTHits = m_phys->mu_muid_nSCTHits;
		mu_muid_nPixHits = m_phys->mu_muid_nPixHits;
		
		// vertex
		vxp_n       = m_phys->vxp_n;
		vxp_nTracks = m_phys->vxp_nTracks;
		vxp_type    = m_phys->vxp_type;
		vxp_z       = m_phys->vxp_z;
		vxp_z_err   = m_phys->vxp_err_z;
	}
	else
	{
		// fill run branches
		RunNumber   = m_mcPhys->RunNumber;
		lbn         = m_mcPhys->lbn;
		EventNumber = m_mcPhys->EventNumber;
		
		// preselection
		isGRL   = isGrl;
		L1_MU6  = m_mcPhys->L1_MU6;
		EF_mu10 = m_mcPhys->EF_mu10;
		EF_mu13 = m_mcPhys->EF_mu13;
		EF_mu15 = m_mcPhys->EF_mu15;
		EF_mu20 = m_mcPhys->EF_mu20;
		EF_mu4  = m_mcPhys->EF_mu4;
		EF_mu6  = m_mcPhys->EF_mu6;
		
		// staco
		mu_staco_n        = m_mcPhys->mu_staco_n;
		mu_staco_px       = m_mcPhys->mu_staco_px;
		mu_staco_py       = m_mcPhys->mu_staco_py;
		mu_staco_pz       = m_mcPhys->mu_staco_pz;
		mu_staco_E        = m_mcPhys->mu_staco_E;
		mu_staco_m        = m_mcPhys->mu_staco_m;
		mu_staco_charge   = m_mcPhys->mu_staco_charge;
		mu_staco_pt       = m_mcPhys->mu_staco_pt;
		mu_staco_ptcone20 = m_mcPhys->mu_staco_ptcone20;
		mu_staco_ptcone30 = m_mcPhys->mu_staco_ptcone30;
		mu_staco_ptcone40 = m_mcPhys->mu_staco_ptcone40;
		mu_staco_eta      = m_mcPhys->mu_staco_eta;
		mu_staco_phi      = m_mcPhys->mu_staco_phi;
		mu_staco_d0_exPV  = m_mcPhys->mu_staco_d0_exPV;
		mu_staco_z0_exPV  = m_mcPhys->mu_staco_z0_exPV;
		mu_staco_allauthor= m_mcPhys->mu_staco_allauthor;
		mu_staco_author   = m_mcPhys->mu_staco_author;
		mu_staco_matchchi2   = m_mcPhys->mu_staco_matchchi2;
		mu_staco_matchndof   = m_mcPhys->mu_staco_matchndof;
		mu_staco_me_qoverp= m_mcPhys->mu_staco_me_qoverp;
		mu_staco_id_qoverp= m_mcPhys->mu_staco_id_qoverp;
		mu_staco_me_theta = m_mcPhys->mu_staco_me_theta;
		mu_staco_id_theta = m_mcPhys->mu_staco_id_theta;
		mu_staco_isCombinedMuon = m_mcPhys->mu_staco_isCombinedMuon;
		mu_staco_nSCTHits = m_mcPhys->mu_staco_nSCTHits;
		mu_staco_nPixHits = m_mcPhys->mu_staco_nPixHits;
		
		// muid
		mu_muid_n        = m_mcPhys->mu_muid_n;
		mu_muid_px       = m_mcPhys->mu_muid_px;
		mu_muid_py       = m_mcPhys->mu_muid_py;
		mu_muid_pz       = m_mcPhys->mu_muid_pz;
		mu_muid_E        = m_mcPhys->mu_muid_E;
		mu_muid_m        = m_mcPhys->mu_muid_m;
		mu_muid_charge   = m_mcPhys->mu_muid_charge;
		mu_muid_pt       = m_mcPhys->mu_muid_pt;
		mu_muid_ptcone20 = m_mcPhys->mu_muid_ptcone20;
		mu_muid_ptcone30 = m_mcPhys->mu_muid_ptcone30;
		mu_muid_ptcone40 = m_mcPhys->mu_muid_ptcone40;
		mu_muid_eta      = m_mcPhys->mu_muid_eta;
		mu_muid_phi      = m_mcPhys->mu_muid_phi;
		mu_muid_d0_exPV  = m_mcPhys->mu_muid_d0_exPV;
		mu_muid_z0_exPV  = m_mcPhys->mu_muid_z0_exPV;
		mu_muid_allauthor= m_mcPhys->mu_muid_allauthor;
		mu_muid_author   = m_mcPhys->mu_muid_author;
		mu_muid_matchchi2 = m_mcPhys->mu_muid_matchchi2;
		mu_muid_matchndof = m_mcPhys->mu_muid_matchndof;
		mu_muid_me_qoverp = m_mcPhys->mu_muid_me_qoverp;
		mu_muid_id_qoverp = m_mcPhys->mu_muid_id_qoverp;
		mu_muid_me_theta = m_mcPhys->mu_muid_me_theta;
		mu_muid_id_theta = m_mcPhys->mu_muid_id_theta;
		mu_muid_isCombinedMuon = m_mcPhys->mu_muid_isCombinedMuon;
		mu_muid_nSCTHits = m_mcPhys->mu_muid_nSCTHits;
		mu_muid_nPixHits = m_mcPhys->mu_muid_nPixHits;
		
		// vertex
		vxp_n       = m_mcPhys->vxp_n;
		vxp_nTracks = m_mcPhys->vxp_nTracks;
		vxp_type    = m_mcPhys->vxp_type;
		vxp_z       = m_mcPhys->vxp_z;
		vxp_z_err   = m_mcPhys->vxp_err_z;
	}
	
	
	///////////////////////////////
	m_tree->Fill(); ///////////////
	///////////////////////////////
}

void offTree::reset()
{
	// run
	RunNumber   = -999;
	lbn         = -999;
	EventNumber = -999;
	
	// staco
	mu_staco_px        = NULL;
	mu_staco_py        = NULL;
	mu_staco_pz        = NULL;
	mu_staco_E         = NULL;
	mu_staco_m         = NULL;
	mu_staco_charge    = NULL;
	mu_staco_pt        = NULL;
	mu_staco_ptcone20  = NULL;
	mu_staco_ptcone30  = NULL;
	mu_staco_ptcone40  = NULL;
	mu_staco_eta       = NULL;
	mu_staco_phi       = NULL;
	mu_staco_d0_exPV   = NULL;
	mu_staco_z0_exPV   = NULL;
	mu_staco_allauthor = NULL;
	mu_staco_author    = NULL;
	mu_staco_matchchi2 = NULL;
	mu_staco_matchndof = NULL;
	mu_staco_me_qoverp = NULL;
	mu_staco_id_qoverp = NULL;
	mu_staco_me_theta  = NULL;
	mu_staco_id_theta  = NULL;
	mu_staco_isCombinedMuon  = NULL;
	mu_staco_nSCTHits  = NULL;
	mu_staco_nPixHits  = NULL;
	
	// muid
	mu_muid_m         = NULL;
	mu_muid_px        = NULL;
	mu_muid_py        = NULL;
	mu_muid_pz        = NULL;
	mu_muid_E         = NULL;
	mu_muid_charge    = NULL;
	mu_muid_pt        = NULL;
	mu_muid_ptcone20  = NULL;
	mu_muid_ptcone30  = NULL;
	mu_muid_ptcone40  = NULL;
	mu_muid_eta       = NULL;
	mu_muid_phi       = NULL;
	mu_muid_d0_exPV   = NULL;
	mu_muid_z0_exPV   = NULL;
	mu_muid_allauthor = NULL;
	mu_muid_author    = NULL;
	mu_muid_matchchi2 = NULL;
	mu_muid_matchndof = NULL;
	mu_muid_me_qoverp = NULL;
	mu_muid_id_qoverp = NULL;
	mu_muid_me_theta  = NULL;
	mu_muid_id_theta  = NULL;
	mu_muid_isCombinedMuon  = NULL;
	mu_muid_nSCTHits  = NULL;
	mu_muid_nPixHits  = NULL;
	
	// vertex variables
	vxp_z       = NULL;
	vxp_z_err   = NULL;
	vxp_nTracks = NULL;
	vxp_type    = NULL;
}

void offTree::write()
{
	m_treeFile->cd();
	m_tree->Write();
}


