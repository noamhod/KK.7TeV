/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "offlineTreeDigest.h"

offlineTreeDigest::offlineTreeDigest()
{

}

offlineTreeDigest::~offlineTreeDigest()
{

}

offlineTreeDigest::offlineTreeDigest(offlinePhysics* offPhys, TFile* treeFile)
{
	m_offPhys = offPhys;

	m_treeFile = treeFile;

	m_treeFile->cd();

	m_tree = new TTree("digest", "digest");

	//m_tree->SetMaxTreeSize(50000000); // 50Mb per file
	
	setBranches();
}

void offlineTreeDigest::setBranches()
{
	mu_staco_px        = new vector<float>;
	mu_staco_py        = new vector<float>;
	mu_staco_pz        = new vector<float>;
	mu_staco_E         = new vector<float>;
	mu_staco_m         = new vector<float>;
	mu_staco_charge    = new vector<float>;
	mu_staco_pt        = new vector<float>;
	mu_staco_ptcone20  = new vector<float>;
	mu_staco_ptcone30  = new vector<float>;
	mu_staco_ptcone40  = new vector<float>;
	mu_staco_eta       = new vector<float>;
	mu_staco_d0_exPV   = new vector<float>;
	mu_staco_z0_exPV   = new vector<float>;
	mu_staco_me_qoverp = new vector<float>;
	mu_staco_id_qoverp = new vector<float>;
	mu_staco_me_theta  = new vector<float>;
	mu_staco_id_theta  = new vector<float>;
	mu_staco_isCombinedMuon = new vector<int>;
	mu_staco_nSCTHits  = new vector<int>;
	mu_staco_nPixHits  = new vector<int>;
	
	// muid
	//mu_muid_m         = new vector<float>;
	//mu_muid_px        = new vector<float>;
	//mu_muid_py        = new vector<float>;
	//mu_muid_pz        = new vector<float>;
	//mu_muid_E         = new vector<float>;
	//mu_muid_charge    = new vector<float>;
	//mu_muid_pt        = new vector<float>;
	//mu_muid_ptcone20  = new vector<float>;
	//mu_muid_ptcone30  = new vector<float>;
	//mu_muid_ptcone40  = new vector<float>;
	//mu_muid_eta       = new vector<float>;
	//mu_muid_d0_exPV   = new vector<float>;
	//mu_muid_z0_exPV   = new vector<float>;
	//mu_muid_me_qoverp = new vector<float>;
	//mu_muid_id_qoverp = new vector<float>;
	//mu_muid_me_theta  = new vector<float>;
	//mu_muid_id_theta  = new vector<float>;
	//mu_muid_isCombinedMuon = new vector<int>;
	//mu_muid_nSCTHits  = new vector<int>;
	//mu_muid_nPixHits  = new vector<int>;
	
	vxp_z       = new vector<float>;
	vxp_z_err   = new vector<float>;
	vxp_nTracks = new vector<int>;
	vxp_type    = new vector<int>;
	

	// run variables branches
	m_tree->Branch( "RunNumber",   &RunNumber );
	m_tree->Branch( "lbn",         &lbn );
	m_tree->Branch( "EventNumber", &EventNumber );
	
	// preselection
	m_tree->Branch( "isGRL",  &isGRL );
	m_tree->Branch( "L1_MU6", &L1_MU6 );
	
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
	m_tree->Branch( "mu_staco_d0_exPV",   &mu_staco_d0_exPV );
	m_tree->Branch( "mu_staco_z0_exPV",   &mu_staco_z0_exPV );
	m_tree->Branch( "mu_staco_me_qoverp",       &mu_staco_me_qoverp );
	m_tree->Branch( "mu_staco_id_qoverp",       &mu_staco_id_qoverp );
	m_tree->Branch( "mu_staco_me_theta",        &mu_staco_me_theta );
	m_tree->Branch( "mu_staco_id_theta",        &mu_staco_id_theta );
	m_tree->Branch( "mu_staco_isCombinedMuon",  &mu_staco_isCombinedMuon );
	m_tree->Branch( "mu_staco_nSCTHits",        &mu_staco_nSCTHits );
	m_tree->Branch( "mu_staco_nPixHits",        &mu_staco_nPixHits );
	
	// //mu_muid
	//m_tree->Branch( "mu_muid_n",         &//mu_muid_n );
	//m_tree->Branch( "mu_muid_px",        &//mu_muid_px );
	//m_tree->Branch( "mu_muid_py",        &//mu_muid_py );
	//m_tree->Branch( "mu_muid_pz",        &//mu_muid_pz );
	//m_tree->Branch( "mu_muid_E",         &//mu_muid_E );
	//m_tree->Branch( "mu_muid_m",         &//mu_muid_m );
	//m_tree->Branch( "mu_muid_charge",    &//mu_muid_charge );
	//m_tree->Branch( "mu_muid_pt",        &//mu_muid_pt );
	//m_tree->Branch( "mu_muid_ptcone20",  &//mu_muid_ptcone20 );
	//m_tree->Branch( "mu_muid_ptcone30",  &//mu_muid_ptcone30 );
	//m_tree->Branch( "mu_muid_ptcone40",  &//mu_muid_ptcone40 );
	//m_tree->Branch( "mu_muid_eta",       &//mu_muid_eta );
	//m_tree->Branch( "mu_muid_d0_exPV",   &//mu_muid_d0_exPV );
	//m_tree->Branch( "mu_muid_z0_exPV",   &//mu_muid_z0_exPV );
	//m_tree->Branch( "mu_muid_me_qoverp",       &//mu_muid_me_qoverp );
	//m_tree->Branch( "mu_muid_id_qoverp",       &//mu_muid_id_qoverp );
	//m_tree->Branch( "mu_muid_me_theta",        &//mu_muid_me_theta );
	//m_tree->Branch( "mu_muid_id_theta",        &//mu_muid_id_theta );
	//m_tree->Branch( "mu_muid_isCombinedMuon",  &//mu_muid_isCombinedMuon );
	//m_tree->Branch( "mu_muid_nSCTHits",        &//mu_muid_nSCTHits );
	//m_tree->Branch( "mu_muid_nPixHits",        &//mu_muid_nPixHits );
	
	// vertex branches
	m_tree->Branch( "vxp_n",       &vxp_n );
	m_tree->Branch( "vxp_nTracks", &vxp_nTracks );
	m_tree->Branch( "vxp_type",    &vxp_type );
	m_tree->Branch( "vxp_z",       &vxp_z );
	m_tree->Branch( "vxp_z_err",   &vxp_z_err );	
}

void offlineTreeDigest::fill(int a, int b, int v)
{

	//////////////////
	reset(); /////////
	//////////////////


	// fill run branches
	RunNumber   = m_offPhys->RunNumber;
	lbn         = m_offPhys->lbn;
	EventNumber = m_offPhys->EventNumber;
	
	// preselection
	isGRL  = m_offPhys->isGRL;
	L1_MU6 = m_offPhys->L1_MU6;
	
	// staco
	mu_staco_n = m_offPhys->mu_staco_n;
	mu_staco_px->push_back( m_offPhys->mu_staco_px->at(a) );
	mu_staco_px->push_back( m_offPhys->mu_staco_px->at(b) );
	mu_staco_py->push_back( m_offPhys->mu_staco_py->at(a) );
	mu_staco_py->push_back( m_offPhys->mu_staco_py->at(b) );
	mu_staco_pz->push_back( m_offPhys->mu_staco_pz->at(a) );
	mu_staco_pz->push_back( m_offPhys->mu_staco_pz->at(b) );
	mu_staco_E->push_back( m_offPhys->mu_staco_E->at(a) );
	mu_staco_E->push_back( m_offPhys->mu_staco_E->at(b) );
	mu_staco_m->push_back( m_offPhys->mu_staco_m->at(a) );
	mu_staco_m->push_back( m_offPhys->mu_staco_m->at(b) );
	mu_staco_charge->push_back( m_offPhys->mu_staco_charge->at(a) );
	mu_staco_charge->push_back( m_offPhys->mu_staco_charge->at(b) );
	mu_staco_pt->push_back( m_offPhys->mu_staco_pt->at(a) );
	mu_staco_pt->push_back( m_offPhys->mu_staco_pt->at(b) );
	mu_staco_ptcone20->push_back( m_offPhys->mu_staco_ptcone20->at(a) );
	mu_staco_ptcone20->push_back( m_offPhys->mu_staco_ptcone20->at(b) );
	mu_staco_ptcone30->push_back( m_offPhys->mu_staco_ptcone30->at(a) );
	mu_staco_ptcone30->push_back( m_offPhys->mu_staco_ptcone30->at(b) );
	mu_staco_ptcone40->push_back( m_offPhys->mu_staco_ptcone40->at(a) );
	mu_staco_ptcone40->push_back( m_offPhys->mu_staco_ptcone40->at(b) );
	mu_staco_eta->push_back( m_offPhys->mu_staco_eta->at(a) );
	mu_staco_eta->push_back( m_offPhys->mu_staco_eta->at(b) );
	mu_staco_d0_exPV->push_back( m_offPhys->mu_staco_d0_exPV->at(a) );
	mu_staco_d0_exPV->push_back( m_offPhys->mu_staco_d0_exPV->at(b) );
	mu_staco_z0_exPV->push_back( m_offPhys->mu_staco_z0_exPV->at(a) );
	mu_staco_z0_exPV->push_back( m_offPhys->mu_staco_z0_exPV->at(b) );
	mu_staco_me_qoverp->push_back( m_offPhys->mu_staco_me_qoverp->at(a) );
	mu_staco_me_qoverp->push_back( m_offPhys->mu_staco_me_qoverp->at(b) );
	mu_staco_id_qoverp->push_back( m_offPhys->mu_staco_id_qoverp->at(a) );
	mu_staco_id_qoverp->push_back( m_offPhys->mu_staco_id_qoverp->at(b) );
	mu_staco_me_theta->push_back( m_offPhys->mu_staco_me_theta->at(a) );
	mu_staco_me_theta->push_back( m_offPhys->mu_staco_me_theta->at(b) );
	mu_staco_id_theta->push_back( m_offPhys->mu_staco_id_theta->at(a) );
	mu_staco_id_theta->push_back( m_offPhys->mu_staco_id_theta->at(b) );
	mu_staco_isCombinedMuon->push_back( m_offPhys->mu_staco_isCombinedMuon->at(a) );
	mu_staco_isCombinedMuon->push_back( m_offPhys->mu_staco_isCombinedMuon->at(b) );
	mu_staco_nSCTHits->push_back( m_offPhys->mu_staco_nSCTHits->at(a) );
	mu_staco_nSCTHits->push_back( m_offPhys->mu_staco_nSCTHits->at(b) );
	mu_staco_nPixHits->push_back( m_offPhys->mu_staco_nPixHits->at(a) );
	mu_staco_nPixHits->push_back( m_offPhys->mu_staco_nPixHits->at(b) );
	
	// muid
	//mu_muid_n = m_offPhys->//mu_muid_n;
	//mu_muid_px->push_back( m_offPhys->//mu_muid_px->at(a) );
	//mu_muid_px->push_back( m_offPhys->//mu_muid_px->at(b) );
	//mu_muid_py->push_back( m_offPhys->//mu_muid_py->at(a) );
	//mu_muid_py->push_back( m_offPhys->//mu_muid_py->at(b) );
	//mu_muid_pz->push_back( m_offPhys->//mu_muid_pz->at(a) );
	//mu_muid_pz->push_back( m_offPhys->//mu_muid_pz->at(b) );
	//mu_muid_E->push_back( m_offPhys->//mu_muid_E->at(a) );
	//mu_muid_E->push_back( m_offPhys->//mu_muid_E->at(b) );
	//mu_muid_m->push_back( m_offPhys->//mu_muid_m->at(a) );
	//mu_muid_m->push_back( m_offPhys->//mu_muid_m->at(b) );
	//mu_muid_charge->push_back( m_offPhys->//mu_muid_charge->at(a) );
	//mu_muid_charge->push_back( m_offPhys->//mu_muid_charge->at(b) );
	//mu_muid_pt->push_back( m_offPhys->//mu_muid_pt->at(a) );
	//mu_muid_pt->push_back( m_offPhys->//mu_muid_pt->at(b) );
	//mu_muid_ptcone20->push_back( m_offPhys->//mu_muid_ptcone20->at(a) );
	//mu_muid_ptcone20->push_back( m_offPhys->//mu_muid_ptcone20->at(b) );
	//mu_muid_ptcone30->push_back( m_offPhys->//mu_muid_ptcone30->at(a) );
	//mu_muid_ptcone30->push_back( m_offPhys->//mu_muid_ptcone30->at(b) );
	//mu_muid_ptcone40->push_back( m_offPhys->//mu_muid_ptcone40->at(a) );
	//mu_muid_ptcone40->push_back( m_offPhys->//mu_muid_ptcone40->at(b) );
	//mu_muid_eta->push_back( m_offPhys->//mu_muid_eta->at(a) );
	//mu_muid_eta->push_back( m_offPhys->//mu_muid_eta->at(b) );
	//mu_muid_d0_exPV->push_back( m_offPhys->//mu_muid_d0_exPV->at(a) );
	//mu_muid_d0_exPV->push_back( m_offPhys->//mu_muid_d0_exPV->at(b) );
	//mu_muid_z0_exPV->push_back( m_offPhys->//mu_muid_z0_exPV->at(a) );
	//mu_muid_z0_exPV->push_back( m_offPhys->//mu_muid_z0_exPV->at(b) );
	//mu_muid_me_qoverp->push_back( m_offPhys->//mu_muid_me_qoverp->at(a) );
	//mu_muid_me_qoverp->push_back( m_offPhys->//mu_muid_me_qoverp->at(b) );
	//mu_muid_id_qoverp->push_back( m_offPhys->//mu_muid_id_qoverp->at(a) );
	//mu_muid_id_qoverp->push_back( m_offPhys->//mu_muid_id_qoverp->at(b) );
	//mu_muid_me_theta->push_back( m_offPhys->//mu_muid_me_theta->at(a) );
	//mu_muid_me_theta->push_back( m_offPhys->//mu_muid_me_theta->at(b) );
	//mu_muid_id_theta->push_back( m_offPhys->//mu_muid_id_theta->at(a) );
	//mu_muid_id_theta->push_back( m_offPhys->//mu_muid_id_theta->at(b) );
	//mu_muid_isCombinedMuon->push_back( m_offPhys->//mu_muid_isCombinedMuon->at(a) );
	//mu_muid_isCombinedMuon->push_back( m_offPhys->//mu_muid_isCombinedMuon->at(b) );
	//mu_muid_nSCTHits->push_back( m_offPhys->//mu_muid_nSCTHits->at(a) );
	//mu_muid_nSCTHits->push_back( m_offPhys->//mu_muid_nSCTHits->at(b) );
	//mu_muid_nPixHits->push_back( m_offPhys->//mu_muid_nPixHits->at(a) );
	//mu_muid_nPixHits->push_back( m_offPhys->//mu_muid_nPixHits->at(b) );
	
	// vertex
	vxp_n = m_offPhys->vxp_n;
	vxp_nTracks->push_back( m_offPhys->vxp_nTracks->at(v) );
	vxp_type->push_back( m_offPhys->vxp_type->at(v) );
	vxp_z->push_back( m_offPhys->vxp_z->at(v) );
	vxp_z_err->push_back( m_offPhys->vxp_z_err->at(v) );
	
	///////////////////////////////
	m_tree->Fill(); ///////////////
	///////////////////////////////
}

void offlineTreeDigest::reset()
{
	// staco
	mu_staco_px->clear();
	mu_staco_py->clear();
	mu_staco_pz->clear();
	mu_staco_E->clear();
	mu_staco_m->clear();
	mu_staco_charge->clear();
	mu_staco_pt->clear();
	mu_staco_ptcone20->clear();
	mu_staco_ptcone30->clear();
	mu_staco_ptcone40->clear();
	mu_staco_eta->clear();
	mu_staco_d0_exPV->clear();
	mu_staco_z0_exPV->clear();
	mu_staco_me_qoverp->clear();
	mu_staco_id_qoverp->clear();
	mu_staco_me_theta->clear();
	mu_staco_id_theta->clear();
	mu_staco_isCombinedMuon->clear();
	mu_staco_nSCTHits->clear();
	mu_staco_nPixHits->clear();
	
	// muid
	//mu_muid_px->clear();
	//mu_muid_py->clear();
	//mu_muid_pz->clear();
	//mu_muid_E->clear();
	//mu_muid_m->clear();
	//mu_muid_charge->clear();
	//mu_muid_pt->clear();
	//mu_muid_ptcone20->clear();
	//mu_muid_ptcone30->clear();
	//mu_muid_ptcone40->clear();
	//mu_muid_eta->clear();
	//mu_muid_d0_exPV->clear();
	//mu_muid_z0_exPV->clear();
	//mu_muid_me_qoverp->clear();
	//mu_muid_id_qoverp->clear();
	//mu_muid_me_theta->clear();
	//mu_muid_id_theta->clear();
	//mu_muid_isCombinedMuon->clear();
	//mu_muid_nSCTHits->clear();
	//mu_muid_nPixHits->clear();
	
	vxp_nTracks->clear();
	vxp_type->clear();
	vxp_z->clear();
	vxp_z_err->clear();
}

void offlineTreeDigest::write()
{
	m_treeFile->cd();
	m_tree->Write();
}


