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
	// external
	m_tree->Branch( "isGRL",    &isGRL );
	m_tree->Branch( "period",   &period );
	m_tree->Branch( "triggers", &triggers );

	// run variables branches
	m_tree->Branch( "RunNumber",   &RunNumber );
	m_tree->Branch( "lbn",         &lbn );
	m_tree->Branch( "EventNumber", &EventNumber );

	
	// L1 triggers
	m_tree->Branch( "L1_MU0", &L1_MU0 );
	m_tree->Branch( "L1_MU10", &L1_MU10 );
	m_tree->Branch( "L1_MU15", &L1_MU15 );
	m_tree->Branch( "L1_MU20", &L1_MU20 );
	m_tree->Branch( "L1_MU6", &L1_MU6 );
	// EF triggers
	m_tree->Branch( "EF_mu10", &EF_mu10 );
	m_tree->Branch( "EF_mu10_MG", &EF_mu10_MG );
	m_tree->Branch( "EF_mu10_MSonly", &EF_mu10_MSonly );
	m_tree->Branch( "EF_mu10_MSonly_tight", &EF_mu10_MSonly_tight );
	m_tree->Branch( "EF_mu10_NoAlg", &EF_mu10_NoAlg );
	m_tree->Branch( "EF_mu10_tight", &EF_mu10_tight );
	m_tree->Branch( "EF_mu10i_loose", &EF_mu10i_loose );
	m_tree->Branch( "EF_mu13", &EF_mu13 );
	m_tree->Branch( "EF_mu13_MG", &EF_mu13_MG );
	m_tree->Branch( "EF_mu13_MG_tight", &EF_mu13_MG_tight );
	m_tree->Branch( "EF_mu13_tight", &EF_mu13_tight );
	m_tree->Branch( "EF_mu15", &EF_mu15 );
	m_tree->Branch( "EF_mu15_NoAlg", &EF_mu15_NoAlg );
	m_tree->Branch( "EF_mu20", &EF_mu20 );
	m_tree->Branch( "EF_mu20_MSonly", &EF_mu20_MSonly );
	m_tree->Branch( "EF_mu20_NoAlg", &EF_mu20_NoAlg );
	m_tree->Branch( "EF_mu20_slow", &EF_mu20_slow );
	m_tree->Branch( "EF_mu30_MSonly", &EF_mu30_MSonly );
	m_tree->Branch( "EF_mu4", &EF_mu4 );
	m_tree->Branch( "EF_mu40_MSonly", &EF_mu40_MSonly );
	
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
	m_tree->Branch( "mu_staco_nMDTBIHits",        &mu_staco_nMDTBIHits );
	m_tree->Branch( "mu_staco_nMDTBMHits",        &mu_staco_nMDTBMHits );
	m_tree->Branch( "mu_staco_nMDTBOHits",        &mu_staco_nMDTBOHits );
	m_tree->Branch( "mu_staco_nMDTBEEHits",       &mu_staco_nMDTBEEHits );
	m_tree->Branch( "mu_staco_nMDTBIS78Hits",     &mu_staco_nMDTBIS78Hits );
	m_tree->Branch( "mu_staco_nMDTEIHits",        &mu_staco_nMDTEIHits );
	m_tree->Branch( "mu_staco_nMDTEMHits",        &mu_staco_nMDTEMHits );
	m_tree->Branch( "mu_staco_nMDTEOHits",        &mu_staco_nMDTEOHits );
	m_tree->Branch( "mu_staco_nMDTEEHits",        &mu_staco_nMDTEEHits );
	m_tree->Branch( "mu_staco_nRPCLayer1EtaHits", &mu_staco_nRPCLayer1EtaHits );
	m_tree->Branch( "mu_staco_nRPCLayer2EtaHits", &mu_staco_nRPCLayer2EtaHits );
	m_tree->Branch( "mu_staco_nRPCLayer3EtaHits", &mu_staco_nRPCLayer3EtaHits );
	m_tree->Branch( "mu_staco_nRPCLayer1PhiHits", &mu_staco_nRPCLayer1PhiHits );
	m_tree->Branch( "mu_staco_nRPCLayer2PhiHits", &mu_staco_nRPCLayer2PhiHits );
	m_tree->Branch( "mu_staco_nRPCLayer3PhiHits", &mu_staco_nRPCLayer3PhiHits );
	m_tree->Branch( "mu_staco_nTGCLayer1EtaHits", &mu_staco_nTGCLayer1EtaHits );
	m_tree->Branch( "mu_staco_nTGCLayer2EtaHits", &mu_staco_nTGCLayer2EtaHits );
	m_tree->Branch( "mu_staco_nTGCLayer3EtaHits", &mu_staco_nTGCLayer3EtaHits );
	m_tree->Branch( "mu_staco_nTGCLayer4EtaHits", &mu_staco_nTGCLayer4EtaHits );
	m_tree->Branch( "mu_staco_nTGCLayer1PhiHits", &mu_staco_nTGCLayer1PhiHits );
	m_tree->Branch( "mu_staco_nTGCLayer2PhiHits", &mu_staco_nTGCLayer2PhiHits );
	m_tree->Branch( "mu_staco_nTGCLayer3PhiHits", &mu_staco_nTGCLayer3PhiHits );
	m_tree->Branch( "mu_staco_nTGCLayer4PhiHits", &mu_staco_nTGCLayer4PhiHits );
	
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
	m_tree->Branch( "mu_muid_nMDTBIHits",        &mu_muid_nMDTBIHits );
	m_tree->Branch( "mu_muid_nMDTBMHits",        &mu_muid_nMDTBMHits );
	m_tree->Branch( "mu_muid_nMDTBOHits",        &mu_muid_nMDTBOHits );
	m_tree->Branch( "mu_muid_nMDTBEEHits",       &mu_muid_nMDTBEEHits );
	m_tree->Branch( "mu_muid_nMDTBIS78Hits",     &mu_muid_nMDTBIS78Hits );
	m_tree->Branch( "mu_muid_nMDTEIHits",        &mu_muid_nMDTEIHits );
	m_tree->Branch( "mu_muid_nMDTEMHits",        &mu_muid_nMDTEMHits );
	m_tree->Branch( "mu_muid_nMDTEOHits",        &mu_muid_nMDTEOHits );
	m_tree->Branch( "mu_muid_nMDTEEHits",        &mu_muid_nMDTEEHits );
	m_tree->Branch( "mu_muid_nRPCLayer1EtaHits", &mu_muid_nRPCLayer1EtaHits );
	m_tree->Branch( "mu_muid_nRPCLayer2EtaHits", &mu_muid_nRPCLayer2EtaHits );
	m_tree->Branch( "mu_muid_nRPCLayer3EtaHits", &mu_muid_nRPCLayer3EtaHits );
	m_tree->Branch( "mu_muid_nRPCLayer1PhiHits", &mu_muid_nRPCLayer1PhiHits );
	m_tree->Branch( "mu_muid_nRPCLayer2PhiHits", &mu_muid_nRPCLayer2PhiHits );
	m_tree->Branch( "mu_muid_nRPCLayer3PhiHits", &mu_muid_nRPCLayer3PhiHits );
	m_tree->Branch( "mu_muid_nTGCLayer1EtaHits", &mu_muid_nTGCLayer1EtaHits );
	m_tree->Branch( "mu_muid_nTGCLayer2EtaHits", &mu_muid_nTGCLayer2EtaHits );
	m_tree->Branch( "mu_muid_nTGCLayer3EtaHits", &mu_muid_nTGCLayer3EtaHits );
	m_tree->Branch( "mu_muid_nTGCLayer4EtaHits", &mu_muid_nTGCLayer4EtaHits );
	m_tree->Branch( "mu_muid_nTGCLayer1PhiHits", &mu_muid_nTGCLayer1PhiHits );
	m_tree->Branch( "mu_muid_nTGCLayer2PhiHits", &mu_muid_nTGCLayer2PhiHits );
	m_tree->Branch( "mu_muid_nTGCLayer3PhiHits", &mu_muid_nTGCLayer3PhiHits );
	m_tree->Branch( "mu_muid_nTGCLayer4PhiHits", &mu_muid_nTGCLayer4PhiHits );
	
	// vertex branches
	m_tree->Branch( "vxp_n",       &vxp_n );
	m_tree->Branch( "vxp_nTracks", &vxp_nTracks );
	m_tree->Branch( "vxp_type",    &vxp_type );
	m_tree->Branch( "vxp_z",       &vxp_z );
	m_tree->Branch( "vxp_z_err",   &vxp_z_err );	
}

void offTree::fill(int isGrl, string sPeriod, vector<string>* vsTriggers)
{ 
	// external
	isGRL    = isGrl;
	period   = sPeriod;
	triggers = vsTriggers;

	if(m_mcPhys==NULL  &&  m_phys!=NULL)
	{
		// fill run branches
		RunNumber   = m_phys->RunNumber;
		lbn         = m_phys->lbn;
		EventNumber = m_phys->EventNumber;
		
		// L1 triggers
		L1_MU0 = m_phys->L1_MU0;
		L1_MU10 = m_phys->L1_MU10;
		L1_MU15 = m_phys->L1_MU15;
		L1_MU20 = m_phys->L1_MU20;
		L1_MU6 = m_phys->L1_MU6; 
		
		// EF triggers
		EF_mu10 = m_phys->EF_mu10;
		EF_mu10_MG = m_phys->EF_mu10_MG;
		EF_mu10_MSonly = m_phys->EF_mu10_MSonly;
		EF_mu10_MSonly_tight = m_phys->EF_mu10_MSonly_tight;
		EF_mu10_NoAlg = m_phys->EF_mu10_NoAlg;
		EF_mu10_tight = m_phys->EF_mu10_tight;
		EF_mu10i_loose = m_phys->EF_mu10i_loose;
		EF_mu13 = m_phys->EF_mu13;
		EF_mu13_MG = m_phys->EF_mu13_MG;
		EF_mu13_MG_tight = m_phys->EF_mu13_MG_tight;
		EF_mu13_tight = m_phys->EF_mu13_tight;
		EF_mu15 = m_phys->EF_mu15;
		EF_mu15_NoAlg = m_phys->EF_mu15_NoAlg;
		EF_mu20 = m_phys->EF_mu20;
		EF_mu20_MSonly = m_phys->EF_mu20_MSonly;
		EF_mu20_NoAlg = m_phys->EF_mu20_NoAlg;
		EF_mu20_slow = m_phys->EF_mu20_slow;
		EF_mu30_MSonly = m_phys->EF_mu30_MSonly;
		EF_mu4 = m_phys->EF_mu4;
		EF_mu40_MSonly = m_phys->EF_mu40_MSonly;
		
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
		mu_staco_me_qoverp = m_phys->mu_staco_me_qoverp;
		mu_staco_id_qoverp = m_phys->mu_staco_id_qoverp;
		mu_staco_me_theta  = m_phys->mu_staco_me_theta;
		mu_staco_id_theta  = m_phys->mu_staco_id_theta;
		mu_staco_isCombinedMuon = m_phys->mu_staco_isCombinedMuon;
		mu_staco_nSCTHits = m_phys->mu_staco_nSCTHits;
		mu_staco_nPixHits = m_phys->mu_staco_nPixHits;
		
		mu_staco_nMDTBIHits =      m_phys->mu_staco_nMDTBIHits;
		mu_staco_nMDTBMHits =      m_phys->mu_staco_nMDTBMHits;
		mu_staco_nMDTBOHits =      m_phys->mu_staco_nMDTBOHits;
		mu_staco_nMDTBEEHits =     m_phys->mu_staco_nMDTBEEHits;
		mu_staco_nMDTBIS78Hits =   m_phys->mu_staco_nMDTBIS78Hits;
		mu_staco_nMDTEIHits    =   m_phys->mu_staco_nMDTEIHits;
		mu_staco_nMDTEMHits    =   m_phys->mu_staco_nMDTEMHits;
		mu_staco_nMDTEOHits    =   m_phys->mu_staco_nMDTEOHits;
		mu_staco_nMDTEEHits    =   m_phys->mu_staco_nMDTEEHits;
		mu_staco_nRPCLayer1EtaHits = m_phys->mu_staco_nRPCLayer1EtaHits;
		mu_staco_nRPCLayer2EtaHits = m_phys->mu_staco_nRPCLayer2EtaHits;
		mu_staco_nRPCLayer3EtaHits = m_phys->mu_staco_nRPCLayer3EtaHits;
		mu_staco_nRPCLayer1PhiHits = m_phys->mu_staco_nRPCLayer1PhiHits;
		mu_staco_nRPCLayer2PhiHits = m_phys->mu_staco_nRPCLayer2PhiHits;
		mu_staco_nRPCLayer3PhiHits = m_phys->mu_staco_nRPCLayer3PhiHits;
		mu_staco_nTGCLayer1EtaHits = m_phys->mu_staco_nTGCLayer1EtaHits;
		mu_staco_nTGCLayer2EtaHits = m_phys->mu_staco_nTGCLayer2EtaHits;
		mu_staco_nTGCLayer3EtaHits = m_phys->mu_staco_nTGCLayer3EtaHits;
		mu_staco_nTGCLayer4EtaHits = m_phys->mu_staco_nTGCLayer4EtaHits;
		mu_staco_nTGCLayer1PhiHits = m_phys->mu_staco_nTGCLayer1PhiHits;
		mu_staco_nTGCLayer2PhiHits = m_phys->mu_staco_nTGCLayer2PhiHits;
		mu_staco_nTGCLayer3PhiHits = m_phys->mu_staco_nTGCLayer3PhiHits;
		mu_staco_nTGCLayer4PhiHits = m_phys->mu_staco_nTGCLayer4PhiHits;
		
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
		mu_muid_nMDTBIHits =      m_phys->mu_muid_nMDTBIHits;
		mu_muid_nMDTBMHits =      m_phys->mu_muid_nMDTBMHits;
		mu_muid_nMDTBOHits =      m_phys->mu_muid_nMDTBOHits;
		mu_muid_nMDTBEEHits =     m_phys->mu_muid_nMDTBEEHits;
		mu_muid_nMDTBIS78Hits =   m_phys->mu_muid_nMDTBIS78Hits;
		mu_muid_nMDTEIHits =      m_phys->mu_muid_nMDTEIHits;
		mu_muid_nMDTEMHits =      m_phys->mu_muid_nMDTEMHits;
		mu_muid_nMDTEOHits =      m_phys->mu_muid_nMDTEOHits;
		mu_muid_nMDTEEHits =      m_phys->mu_muid_nMDTEEHits;
		
		mu_muid_nRPCLayer1EtaHits = m_phys->mu_muid_nRPCLayer1EtaHits;
		mu_muid_nRPCLayer2EtaHits = m_phys->mu_muid_nRPCLayer2EtaHits;
		mu_muid_nRPCLayer3EtaHits = m_phys->mu_muid_nRPCLayer3EtaHits;
		mu_muid_nRPCLayer1PhiHits = m_phys->mu_muid_nRPCLayer1PhiHits;
		mu_muid_nRPCLayer2PhiHits = m_phys->mu_muid_nRPCLayer2PhiHits;
		mu_muid_nRPCLayer3PhiHits = m_phys->mu_muid_nRPCLayer3PhiHits;
		mu_muid_nTGCLayer1EtaHits = m_phys->mu_muid_nTGCLayer1EtaHits;
		mu_muid_nTGCLayer2EtaHits = m_phys->mu_muid_nTGCLayer2EtaHits;
		mu_muid_nTGCLayer3EtaHits = m_phys->mu_muid_nTGCLayer3EtaHits;
		mu_muid_nTGCLayer4EtaHits = m_phys->mu_muid_nTGCLayer4EtaHits;
		mu_muid_nTGCLayer1PhiHits = m_phys->mu_muid_nTGCLayer1PhiHits;
		mu_muid_nTGCLayer2PhiHits = m_phys->mu_muid_nTGCLayer2PhiHits;
		mu_muid_nTGCLayer3PhiHits = m_phys->mu_muid_nTGCLayer3PhiHits;
		mu_muid_nTGCLayer4PhiHits = m_phys->mu_muid_nTGCLayer4PhiHits;
		
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
		
		// L1 triggers
		L1_MU0 = m_mcPhys->L1_MU0;
		L1_MU10 = m_mcPhys->L1_MU10;
		L1_MU15 = m_mcPhys->L1_MU15;
		L1_MU20 = m_mcPhys->L1_MU20;
		L1_MU6 = m_mcPhys->L1_MU6;
		
		///////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////
		/*
		// EF triggers
		EF_mu10 = m_mcPhys->EF_mu10;
		EF_mu10_MG = m_mcPhys->EF_mu10_MG;
		EF_mu10_MSonly = m_mcPhys->EF_mu10_MSonly;
		EF_mu10_MSonly_tight = m_mcPhys->EF_mu10_MSonly_tight;
		EF_mu10_NoAlg = m_mcPhys->EF_mu10_NoAlg;
		EF_mu10_tight = m_mcPhys->EF_mu10_tight;
		EF_mu10i_loose = m_mcPhys->EF_mu10i_loose;
		EF_mu13 = m_mcPhys->EF_mu13;
		EF_mu13_MG = m_mcPhys->EF_mu13_MG;
		EF_mu13_MG_tight = m_mcPhys->EF_mu13_MG_tight;
		EF_mu13_tight = m_mcPhys->EF_mu13_tight;
		EF_mu15 = m_mcPhys->EF_mu15;
		EF_mu15_NoAlg = m_mcPhys->EF_mu15_NoAlg;
		EF_mu20 = m_mcPhys->EF_mu20;
		EF_mu20_MSonly = m_mcPhys->EF_mu20_MSonly;
		EF_mu20_NoAlg = m_mcPhys->EF_mu20_NoAlg;
		EF_mu20_slow = m_mcPhys->EF_mu20_slow;
		EF_mu30_MSonly = m_mcPhys->EF_mu30_MSonly;
		EF_mu4 = m_mcPhys->EF_mu4;
		EF_mu40_MSonly = m_mcPhys->EF_mu40_MSonly;
		*/
		EF_mu10 = 0;
		EF_mu10_MG = 0;
		EF_mu10_MSonly = 0;
		EF_mu10_MSonly_tight = 0;
		EF_mu10_NoAlg = 0;
		EF_mu10_tight = 0;
		EF_mu10i_loose = 0;
		EF_mu13 = 0;
		EF_mu13_MG = 0;
		EF_mu13_MG_tight = 0;
		EF_mu13_tight = 0;
		EF_mu15 = 0;
		EF_mu15_NoAlg = 0;
		EF_mu20 = 0;
		EF_mu20_MSonly = 0;
		EF_mu20_NoAlg = 0;
		EF_mu20_slow = 0;
		EF_mu30_MSonly = 0;
		EF_mu4 = 0;
		EF_mu40_MSonly = 0;
		///////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////
		
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
		
		mu_staco_nMDTBIHits =    m_mcPhys->mu_staco_nMDTBIHits;
		mu_staco_nMDTBMHits =    m_mcPhys->mu_staco_nMDTBMHits;
		mu_staco_nMDTBOHits =    m_mcPhys->mu_staco_nMDTBOHits;
		mu_staco_nMDTBEEHits =   m_mcPhys->mu_staco_nMDTBEEHits;
		mu_staco_nMDTBIS78Hits = m_mcPhys->mu_staco_nMDTBIS78Hits;
		mu_staco_nMDTEIHits =    m_mcPhys->mu_staco_nMDTEIHits;
		mu_staco_nMDTEMHits =    m_mcPhys->mu_staco_nMDTEMHits;
		mu_staco_nMDTEOHits =    m_mcPhys->mu_staco_nMDTEOHits;
		mu_staco_nMDTEEHits =    m_mcPhys->mu_staco_nMDTEEHits;
		mu_staco_nRPCLayer1EtaHits = m_mcPhys->mu_staco_nRPCLayer1EtaHits;
		mu_staco_nRPCLayer2EtaHits = m_mcPhys->mu_staco_nRPCLayer2EtaHits;
		mu_staco_nRPCLayer3EtaHits = m_mcPhys->mu_staco_nRPCLayer3EtaHits;
		mu_staco_nRPCLayer1PhiHits = m_mcPhys->mu_staco_nRPCLayer1PhiHits;
		mu_staco_nRPCLayer2PhiHits = m_mcPhys->mu_staco_nRPCLayer2PhiHits;
		mu_staco_nRPCLayer3PhiHits = m_mcPhys->mu_staco_nRPCLayer3PhiHits;
		mu_staco_nTGCLayer1EtaHits = m_mcPhys->mu_staco_nTGCLayer1EtaHits;
		mu_staco_nTGCLayer2EtaHits = m_mcPhys->mu_staco_nTGCLayer2EtaHits;
		mu_staco_nTGCLayer3EtaHits = m_mcPhys->mu_staco_nTGCLayer3EtaHits;
		mu_staco_nTGCLayer4EtaHits = m_mcPhys->mu_staco_nTGCLayer4EtaHits;
		mu_staco_nTGCLayer1PhiHits = m_mcPhys->mu_staco_nTGCLayer1PhiHits;
		mu_staco_nTGCLayer2PhiHits = m_mcPhys->mu_staco_nTGCLayer2PhiHits;
		mu_staco_nTGCLayer3PhiHits = m_mcPhys->mu_staco_nTGCLayer3PhiHits;
		mu_staco_nTGCLayer4PhiHits = m_mcPhys->mu_staco_nTGCLayer4PhiHits;
		
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
		mu_muid_nMDTBIHits =      m_mcPhys->mu_muid_nMDTBIHits;
		mu_muid_nMDTBMHits =      m_mcPhys->mu_muid_nMDTBMHits;
		mu_muid_nMDTBOHits =      m_mcPhys->mu_muid_nMDTBOHits;
		mu_muid_nMDTBEEHits =     m_mcPhys->mu_muid_nMDTBEEHits;
		mu_muid_nMDTBIS78Hits =   m_mcPhys->mu_muid_nMDTBIS78Hits;
		mu_muid_nMDTEIHits =      m_mcPhys->mu_muid_nMDTEIHits;
		mu_muid_nMDTEMHits =      m_mcPhys->mu_muid_nMDTEMHits;
		mu_muid_nMDTEOHits =      m_mcPhys->mu_muid_nMDTEOHits;
		mu_muid_nMDTEEHits =      m_mcPhys->mu_muid_nMDTEEHits;
		
		mu_muid_nRPCLayer1EtaHits = m_mcPhys->mu_muid_nRPCLayer1EtaHits;
		mu_muid_nRPCLayer2EtaHits = m_mcPhys->mu_muid_nRPCLayer2EtaHits;
		mu_muid_nRPCLayer3EtaHits = m_mcPhys->mu_muid_nRPCLayer3EtaHits;
		mu_muid_nRPCLayer1PhiHits = m_mcPhys->mu_muid_nRPCLayer1PhiHits;
		mu_muid_nRPCLayer2PhiHits = m_mcPhys->mu_muid_nRPCLayer2PhiHits;
		mu_muid_nRPCLayer3PhiHits = m_mcPhys->mu_muid_nRPCLayer3PhiHits;
		mu_muid_nTGCLayer1EtaHits = m_mcPhys->mu_muid_nTGCLayer1EtaHits;
		mu_muid_nTGCLayer2EtaHits = m_mcPhys->mu_muid_nTGCLayer2EtaHits;
		mu_muid_nTGCLayer3EtaHits = m_mcPhys->mu_muid_nTGCLayer3EtaHits;
		mu_muid_nTGCLayer4EtaHits = m_mcPhys->mu_muid_nTGCLayer4EtaHits;
		mu_muid_nTGCLayer1PhiHits = m_mcPhys->mu_muid_nTGCLayer1PhiHits;
		mu_muid_nTGCLayer2PhiHits = m_mcPhys->mu_muid_nTGCLayer2PhiHits;
		mu_muid_nTGCLayer3PhiHits = m_mcPhys->mu_muid_nTGCLayer3PhiHits;
		mu_muid_nTGCLayer4PhiHits = m_mcPhys->mu_muid_nTGCLayer4PhiHits;
		
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
	mu_staco_nMDTBIHits = NULL;
	mu_staco_nMDTBMHits = NULL;
	mu_staco_nMDTBOHits = NULL;
	mu_staco_nMDTBEEHits = NULL;
	mu_staco_nMDTBIS78Hits = NULL;
	mu_staco_nMDTEIHits = NULL;
	mu_staco_nMDTEMHits = NULL;
	mu_staco_nMDTEOHits = NULL;
	mu_staco_nMDTEEHits = NULL;
	mu_staco_nRPCLayer1EtaHits = NULL;
	mu_staco_nRPCLayer2EtaHits = NULL;
	mu_staco_nRPCLayer3EtaHits = NULL;
	mu_staco_nRPCLayer1PhiHits = NULL;
	mu_staco_nRPCLayer2PhiHits = NULL;
	mu_staco_nRPCLayer3PhiHits = NULL;
	mu_staco_nTGCLayer1EtaHits = NULL;
	mu_staco_nTGCLayer2EtaHits = NULL;
	mu_staco_nTGCLayer3EtaHits = NULL;
	mu_staco_nTGCLayer4EtaHits = NULL;
	mu_staco_nTGCLayer1PhiHits = NULL;
	mu_staco_nTGCLayer2PhiHits = NULL;
	mu_staco_nTGCLayer3PhiHits = NULL;
	mu_staco_nTGCLayer4PhiHits = NULL;
	
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
	mu_muid_nMDTBIHits = NULL;
	mu_muid_nMDTBMHits = NULL;
	mu_muid_nMDTBOHits = NULL;
	mu_muid_nMDTBEEHits = NULL;
	mu_muid_nMDTBIS78Hits = NULL;
	mu_muid_nMDTEIHits = NULL;
	mu_muid_nMDTEMHits = NULL;
	mu_muid_nMDTEOHits = NULL;
	mu_muid_nMDTEEHits = NULL;
	mu_muid_nRPCLayer1EtaHits = NULL;
	mu_muid_nRPCLayer2EtaHits = NULL;
	mu_muid_nRPCLayer3EtaHits = NULL;
	mu_muid_nRPCLayer1PhiHits = NULL;
	mu_muid_nRPCLayer2PhiHits = NULL;
	mu_muid_nRPCLayer3PhiHits = NULL;
	mu_muid_nTGCLayer1EtaHits = NULL;
	mu_muid_nTGCLayer2EtaHits = NULL;
	mu_muid_nTGCLayer3EtaHits = NULL;
	mu_muid_nTGCLayer4EtaHits = NULL;
	mu_muid_nTGCLayer1PhiHits = NULL;
	mu_muid_nTGCLayer2PhiHits = NULL;
	mu_muid_nTGCLayer3PhiHits = NULL;
	mu_muid_nTGCLayer4PhiHits = NULL;
	
	
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


