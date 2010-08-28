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

offTree::offTree(physics* phys, TFile* treeFile)
{
	m_phys = phys;

	m_treeFile = treeFile;

	m_treeFile->cd();

	m_tree = new TTree("offline", "offline");

	//m_tree->SetMaxTreeSize(50000000); // 50Mb per file
	
	setBranches();
}

void offTree::setBranches()
{	
	// run variables branches
	m_tree->Branch( "RunNumber",   &m_RunNumber );
	m_tree->Branch( "lbn",         &m_lbn );
	m_tree->Branch( "EventNumber", &m_EventNumber );
	
	// preselection
	m_tree->Branch( "isGRL",  &m_isGRL );
	m_tree->Branch( "L1_MU6", &m_L1_MU6 );
	
	// kinematic variables branches
	m_tree->Branch( "imass",    &m_imass );
	m_tree->Branch( "cosTheta", &m_cosTheta );
	
	// mua and mub other branches
	m_tree->Branch( "mua_m",         &m_mua_m );
	m_tree->Branch( "mub_m",        &m_mub_m );
	m_tree->Branch( "mua_charge",    &m_mua_charge );
	m_tree->Branch( "mub_charge",   &m_mub_charge );
	m_tree->Branch( "mua_pT",        &m_mua_pT );
	m_tree->Branch( "mub_pT",       &m_mub_pT );
	m_tree->Branch( "mua_pTcone20",  &m_mua_pTcone20 );
	m_tree->Branch( "mub_pTcone20", &m_mub_pTcone20 );
	m_tree->Branch( "mua_pTcone30",  &m_mua_pTcone30 );
	m_tree->Branch( "mub_pTcone30", &m_mub_pTcone30 );
	m_tree->Branch( "mua_pTcone40",  &m_mua_pTcone40 );
	m_tree->Branch( "mub_pTcone40", &m_mub_pTcone40 );
	m_tree->Branch( "mua_eta",       &m_mua_eta );
	m_tree->Branch( "mub_eta",      &m_mub_eta );
	m_tree->Branch( "mua_d0_exPV",   &m_mua_d0_exPV );
	m_tree->Branch( "mub_d0_exPV",  &m_mub_d0_exPV );
	m_tree->Branch( "mua_z0_exPV",   &m_mua_z0_exPV );
	m_tree->Branch( "mub_z0_exPV",  &m_mub_z0_exPV );
	m_tree->Branch( "mua_me_qOp",    &m_mua_me_qOp );
	m_tree->Branch( "mub_me_qOp",   &m_mub_me_qOp );
	m_tree->Branch( "mua_id_qOp",    &m_mua_id_qOp );
	m_tree->Branch( "mub_id_qOp",   &m_mub_id_qOp );
	m_tree->Branch( "mua_me_theta",  &m_mua_me_theta );
	m_tree->Branch( "mub_me_theta", &m_mub_me_theta );
	m_tree->Branch( "mua_id_theta",  &m_mua_id_theta );
	m_tree->Branch( "mub_id_theta", &m_mub_id_theta );
	m_tree->Branch( "mua_isCombMu",  &m_mua_isCombMu );
	m_tree->Branch( "mub_isCombMu", &m_mub_isCombMu );
	m_tree->Branch( "mua_nSCThits",  &m_mua_nSCThits );
	m_tree->Branch( "mub_nSCThits", &m_mub_nSCThits );
	m_tree->Branch( "mua_nPIXhits",  &m_mua_nPIXhits );
	m_tree->Branch( "mub_nPIXhits", &m_mub_nPIXhits );
	m_tree->Branch( "mua_nIDhits",   &m_mua_nIDhits );
	m_tree->Branch( "mub_nIDhits",  &m_mub_nIDhits );

	// mua and mub TLorentzVector
	m_tree->Branch( "mua_p4Vec",  &m_mua_p4Vec );
	m_tree->Branch( "mub_p4Vec", &m_mub_p4Vec );
	
	// vertex branches
	m_tree->Branch( "vxp_z",       &m_vxp_z );
	m_tree->Branch( "vxp_z_err",   &m_vxp_z_err );
	m_tree->Branch( "vxp_nTracks", &m_vxp_nTracks );
	m_tree->Branch( "vxp_type",    &m_vxp_type );
	
}

void offTree::fill()
{
	///////////////////////////////
	m_tree->Fill(); ///////////////
	///////////////////////////////
}

void offTree::fill(int isGRL, TMapsd& kinVars, int ia, int ib, int iVtx)
{
	// fill run branches
	m_RunNumber   = m_phys->RunNumber;
	m_lbn         = m_phys->lbn;
	m_EventNumber = m_phys->EventNumber;
	
	// preselection
	m_isGRL  = isGRL;
	m_L1_MU6 = m_phys->L1_MU6;

	// fill kin branches
	for(TMapsd::iterator it=kinVars.begin() ; it!=kinVars.end() ; ++it)
	{
		string sname = it->first;
		double dval  = it->second;
		
		if(sname=="imass")    m_imass       = dval;
		if(sname=="cosTheta") m_cosTheta = dval;
	}
	
	// muons
	m_mua_m = m_phys->mu_staco_m->at(ia);
	m_mub_m = m_phys->mu_staco_m->at(ib);
	m_mua_charge = m_phys->mu_staco_charge->at(ia);
	m_mub_charge = m_phys->mu_staco_charge->at(ib);
	m_mua_pT = m_phys->mu_staco_pt->at(ia);
	m_mub_pT = m_phys->mu_staco_pt->at(ib);
	m_mua_pTcone20 = m_phys->mu_staco_ptcone20->at(ia);
	m_mub_pTcone20 = m_phys->mu_staco_ptcone20->at(ib);
	m_mua_pTcone30 = m_phys->mu_staco_ptcone30->at(ia);
	m_mub_pTcone30 = m_phys->mu_staco_ptcone30->at(ib);
	m_mua_pTcone40 = m_phys->mu_staco_ptcone40->at(ia);
	m_mub_pTcone40 = m_phys->mu_staco_ptcone40->at(ib);
	m_mua_eta = m_phys->mu_staco_eta->at(ia);
	m_mub_eta = m_phys->mu_staco_eta->at(ib);
	m_mua_d0_exPV = m_phys->mu_staco_d0_exPV->at(ia);
	m_mub_d0_exPV = m_phys->mu_staco_d0_exPV->at(ib);
	m_mua_z0_exPV = m_phys->mu_staco_z0_exPV->at(ia);
	m_mub_z0_exPV = m_phys->mu_staco_z0_exPV->at(ib);
	m_mua_me_qOp = m_phys->mu_staco_me_qoverp->at(ia);
	m_mub_me_qOp = m_phys->mu_staco_me_qoverp->at(ib);
	m_mua_id_qOp = m_phys->mu_staco_id_qoverp->at(ia);
	m_mub_id_qOp = m_phys->mu_staco_id_qoverp->at(ib);
	m_mua_me_theta = m_phys->mu_staco_me_theta->at(ia);
	m_mub_me_theta = m_phys->mu_staco_me_theta->at(ib);
	m_mua_id_theta = m_phys->mu_staco_id_theta->at(ia);
	m_mub_id_theta = m_phys->mu_staco_id_theta->at(ib);
	m_mua_isCombMu = m_phys->mu_staco_isCombinedMuon->at(ia);
	m_mub_isCombMu = m_phys->mu_staco_isCombinedMuon->at(ib);
	m_mua_nSCThits = m_phys->mu_staco_nSCTHits->at(ia);
	m_mub_nSCThits = m_phys->mu_staco_nSCTHits->at(ib);
	m_mua_nPIXhits = m_phys->mu_staco_nPixHits->at(ia);
	m_mub_nPIXhits = m_phys->mu_staco_nPixHits->at(ib);
	m_mua_nIDhits = m_mua_nSCThits+m_mua_nPIXhits;
	m_mub_nIDhits = m_mub_nSCThits+m_mub_nPIXhits;
	
	// mua and mub TLorentzVector
	m_mua_p4Vec.SetPxPyPzE(m_phys->mu_staco_px->at(ia),
	m_phys->mu_staco_py->at(ia),
	m_phys->mu_staco_pz->at(ia),
	m_phys->mu_staco_E->at(ia));
	m_mub_p4Vec.SetPxPyPzE(m_phys->mu_staco_px->at(ib),
	m_phys->mu_staco_py->at(ib),
	m_phys->mu_staco_pz->at(ib),
	m_phys->mu_staco_E->at(ib));
	
	// vertex
	m_vxp_z = m_phys->vxp_nTracks->at(iVtx);
	m_vxp_z_err = m_phys->vxp_type->at(iVtx);
	m_vxp_nTracks = m_phys->vxp_z->at(iVtx);
	m_vxp_type = m_phys->vxp_err_z->at(iVtx);
	
	///////////////////////////////
	m_tree->Fill(); ///////////////
	///////////////////////////////
}

void offTree::reset()
{
	// run
	m_RunNumber   = -999;
	m_lbn         = -999;
	m_EventNumber = -999;

	// kin
	m_imass       = -999;
	m_cosTheta = -999;
	
	// muons
	m_mua_m         = -999;
	m_mub_m        = -999;
	m_mua_charge    = -999;
	m_mub_charge   = -999;
	m_mua_pT        = -999;
	m_mub_pT       = -999;
	m_mua_pTcone20  = -999;
	m_mub_pTcone20 = -999;
	m_mua_pTcone30  = -999;
	m_mub_pTcone30 = -999;
	m_mua_pTcone40  = -999;
	m_mub_pTcone40 = -999;
	m_mua_eta       = -999;
	m_mub_eta      = -999;
	m_mua_d0_exPV   = -999;
	m_mub_d0_exPV  = -999;
	m_mua_z0_exPV   = -999;
	m_mub_z0_exPV  = -999;
	m_mua_me_qOp    = -999;
	m_mub_me_qOp   = -999;
	m_mua_id_qOp    = -999;
	m_mub_id_qOp   = -999;
	m_mua_me_theta  = -999;
	m_mub_me_theta = -999;
	m_mua_id_theta  = -999;
	m_mub_id_theta = -999;
	m_mua_isCombMu  = -999;
	m_mub_isCombMu = -999;
	m_mua_nSCThits  = -999;
	m_mub_nSCThits = -999;
	m_mua_nPIXhits  = -999;
	m_mub_nPIXhits = -999;
	m_mua_nIDhits   = -999;
	m_mub_nIDhits  = -999;
	
	m_mua_p4Vec.SetPxPyPzE(-999, -999, -999, -sqrt(3)*999);
	m_mub_p4Vec.SetPxPyPzE(-999, -999, -999, -sqrt(3)*999);
	
	// vertex variables
	m_vxp_z       = -999;
	m_vxp_z_err   = -999;
	m_vxp_nTracks = -999;
	m_vxp_type    = -999;
}

void offTree::write()
{
	m_treeFile->cd();
	m_tree->Write();
}


