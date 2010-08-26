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
	
	// muPlus and muMinus other branches
	m_tree->Branch( "muPlus_m",         &m_muPlus_m );
	m_tree->Branch( "muMinus_m",        &m_muMinus_m );
	m_tree->Branch( "muPlus_charge",    &m_muPlus_charge );
	m_tree->Branch( "muMinus_charge",   &m_muMinus_charge );
	m_tree->Branch( "muPlus_pT",        &m_muPlus_pT );
	m_tree->Branch( "muMinus_pT",       &m_muMinus_pT );
	m_tree->Branch( "muPlus_pTcone20",  &m_muPlus_pTcone20 );
	m_tree->Branch( "muMinus_pTcone20", &m_muMinus_pTcone20 );
	m_tree->Branch( "muPlus_pTcone30",  &m_muPlus_pTcone30 );
	m_tree->Branch( "muMinus_pTcone30", &m_muMinus_pTcone30 );
	m_tree->Branch( "muPlus_pTcone40",  &m_muPlus_pTcone40 );
	m_tree->Branch( "muMinus_pTcone40", &m_muMinus_pTcone40 );
	m_tree->Branch( "muPlus_eta",       &m_muPlus_eta );
	m_tree->Branch( "muMinus_eta",      &m_muMinus_eta );
	m_tree->Branch( "muPlus_d0_exPV",   &m_muPlus_d0_exPV );
	m_tree->Branch( "muMinus_d0_exPV",  &m_muMinus_d0_exPV );
	m_tree->Branch( "muPlus_z0_exPV",   &m_muPlus_z0_exPV );
	m_tree->Branch( "muMinus_z0_exPV",  &m_muMinus_z0_exPV );
	m_tree->Branch( "muPlus_me_qOp",    &m_muPlus_me_qOp );
	m_tree->Branch( "muMinus_me_qOp",   &m_muMinus_me_qOp );
	m_tree->Branch( "muPlus_id_qOp",    &m_muPlus_id_qOp );
	m_tree->Branch( "muMinus_id_qOp",   &m_muMinus_id_qOp );
	m_tree->Branch( "muPlus_me_theta",  &m_muPlus_me_theta );
	m_tree->Branch( "muMinus_me_theta", &m_muMinus_me_theta );
	m_tree->Branch( "muPlus_id_theta",  &m_muPlus_id_theta );
	m_tree->Branch( "muMinus_id_theta", &m_muMinus_id_theta );
	m_tree->Branch( "muPlus_isCombMu",  &m_muPlus_isCombMu );
	m_tree->Branch( "muMinus_isCombMu", &m_muMinus_isCombMu );
	m_tree->Branch( "muPlus_nSCThits",  &m_muPlus_nSCThits );
	m_tree->Branch( "muMinus_nSCThits", &m_muMinus_nSCThits );
	m_tree->Branch( "muPlus_nPIXhits",  &m_muPlus_nPIXhits );
	m_tree->Branch( "muMinus_nPIXhits", &m_muMinus_nPIXhits );
	m_tree->Branch( "muPlus_nIDhits",   &m_muPlus_nIDhits );
	m_tree->Branch( "muMinus_nIDhits",  &m_muMinus_nIDhits );

	// muPlus and muMinus TLorentzVector
	m_tree->Branch( "muPlus_p4Vec",  &m_muPlus_p4Vec );
	m_tree->Branch( "muMinus_p4Vec", &m_muMinus_p4Vec );
	
	// vertex branches
	m_tree->Branch( "vxp_z",       &m_vxp_z );
	m_tree->Branch( "vxp_z_err",   &m_vxp_z_err );
	m_tree->Branch( "vxp_nTracks", &m_vxp_nTracks );
	m_tree->Branch( "vxp_type",    &m_vxp_type );
	
}

void offlineTreeDigest::fill()
{
	///////////////////////////////
	m_tree->Fill(); ///////////////
	///////////////////////////////
}

void offlineTreeDigest::fill(TMapsd& kinVars, int iMup, int iMum, int iVtx)
{
	// fill run branches
	m_RunNumber   = m_offPhys->RunNumber;
	m_lbn         = m_offPhys->lbn;
	m_EventNumber = m_offPhys->EventNumber;
	
	// preselection
	m_isGRL  = m_offPhys->isGRL;
	m_L1_MU6 = m_offPhys->L1_MU6;

	// fill kin branches
	for(TMapsd::iterator it=kinVars.begin() ; it!=kinVars.end() ; ++it)
	{
		string sname = it->first;
		double dval  = it->second;
		
		if(sname=="imass")    m_imass       = dval;
		if(sname=="cosTheta") m_cosTheta = dval;
	}
	
	// muons
	m_muPlus_m = m_offPhys->mu_staco_m->at(iMup);
	m_muMinus_m = m_offPhys->mu_staco_m->at(iMum);
	m_muPlus_charge = m_offPhys->mu_staco_charge->at(iMup);
	m_muMinus_charge = m_offPhys->mu_staco_charge->at(iMum);
	m_muPlus_pT = m_offPhys->mu_staco_pt->at(iMup);
	m_muMinus_pT = m_offPhys->mu_staco_pt->at(iMum);
	m_muPlus_pTcone20 = m_offPhys->mu_staco_ptcone20->at(iMup);
	m_muMinus_pTcone20 = m_offPhys->mu_staco_ptcone20->at(iMum);
	m_muPlus_pTcone30 = m_offPhys->mu_staco_ptcone30->at(iMup);
	m_muMinus_pTcone30 = m_offPhys->mu_staco_ptcone30->at(iMum);
	m_muPlus_pTcone40 = m_offPhys->mu_staco_ptcone40->at(iMup);
	m_muMinus_pTcone40 = m_offPhys->mu_staco_ptcone40->at(iMum);
	m_muPlus_eta = m_offPhys->mu_staco_eta->at(iMup);
	m_muMinus_eta = m_offPhys->mu_staco_eta->at(iMum);
	m_muPlus_d0_exPV = m_offPhys->mu_staco_d0_exPV->at(iMup);
	m_muMinus_d0_exPV = m_offPhys->mu_staco_d0_exPV->at(iMum);
	m_muPlus_z0_exPV = m_offPhys->mu_staco_z0_exPV->at(iMup);
	m_muMinus_z0_exPV = m_offPhys->mu_staco_z0_exPV->at(iMum);
	m_muPlus_me_qOp = m_offPhys->mu_staco_me_qoverp->at(iMup);
	m_muMinus_me_qOp = m_offPhys->mu_staco_me_qoverp->at(iMum);
	m_muPlus_id_qOp = m_offPhys->mu_staco_id_qoverp->at(iMup);
	m_muMinus_id_qOp = m_offPhys->mu_staco_id_qoverp->at(iMum);
	m_muPlus_me_theta = m_offPhys->mu_staco_me_theta->at(iMup);
	m_muMinus_me_theta = m_offPhys->mu_staco_me_theta->at(iMum);
	m_muPlus_id_theta = m_offPhys->mu_staco_id_theta->at(iMup);
	m_muMinus_id_theta = m_offPhys->mu_staco_id_theta->at(iMum);
	m_muPlus_isCombMu = m_offPhys->mu_staco_isCombinedMuon->at(iMup);
	m_muMinus_isCombMu = m_offPhys->mu_staco_isCombinedMuon->at(iMum);
	m_muPlus_nSCThits = m_offPhys->mu_staco_nSCTHits->at(iMup);
	m_muMinus_nSCThits = m_offPhys->mu_staco_nSCTHits->at(iMum);
	m_muPlus_nPIXhits = m_offPhys->mu_staco_nPixHits->at(iMup);
	m_muMinus_nPIXhits = m_offPhys->mu_staco_nPixHits->at(iMum);
	m_muPlus_nIDhits = m_muPlus_nSCThits+m_muPlus_nPIXhits;
	m_muMinus_nIDhits = m_muMinus_nSCThits+m_muMinus_nPIXhits;
	
	// muPlus and muMinus TLorentzVector
	m_muPlus_p4Vec.SetPxPyPzE(m_offPhys->mu_staco_px->at(iMup),
	m_offPhys->mu_staco_py->at(iMup),
	m_offPhys->mu_staco_pz->at(iMup),
	m_offPhys->mu_staco_E->at(iMup));
	m_muMinus_p4Vec.SetPxPyPzE(m_offPhys->mu_staco_px->at(iMum),
	m_offPhys->mu_staco_py->at(iMum),
	m_offPhys->mu_staco_pz->at(iMum),
	m_offPhys->mu_staco_E->at(iMum));
	
	// vertex
	m_vxp_z = m_offPhys->vxp_nTracks->at(iVtx);
	m_vxp_z_err = m_offPhys->vxp_type->at(iVtx);
	m_vxp_nTracks = m_offPhys->vxp_z->at(iVtx);
	m_vxp_type = m_offPhys->vxp_err_z->at(iVtx);
	
	///////////////////////////////
	m_tree->Fill(); ///////////////
	///////////////////////////////
}

void offlineTreeDigest::reset()
{
	// run
	m_RunNumber   = -999;
	m_lbn         = -999;
	m_EventNumber = -999;

	// kin
	m_imass       = -999;
	m_cosTheta = -999;
	
	// muons
	m_muPlus_m         = -999;
	m_muMinus_m        = -999;
	m_muPlus_charge    = -999;
	m_muMinus_charge   = -999;
	m_muPlus_pT        = -999;
	m_muMinus_pT       = -999;
	m_muPlus_pTcone20  = -999;
	m_muMinus_pTcone20 = -999;
	m_muPlus_pTcone30  = -999;
	m_muMinus_pTcone30 = -999;
	m_muPlus_pTcone40  = -999;
	m_muMinus_pTcone40 = -999;
	m_muPlus_eta       = -999;
	m_muMinus_eta      = -999;
	m_muPlus_d0_exPV   = -999;
	m_muMinus_d0_exPV  = -999;
	m_muPlus_z0_exPV   = -999;
	m_muMinus_z0_exPV  = -999;
	m_muPlus_me_qOp    = -999;
	m_muMinus_me_qOp   = -999;
	m_muPlus_id_qOp    = -999;
	m_muMinus_id_qOp   = -999;
	m_muPlus_me_theta  = -999;
	m_muMinus_me_theta = -999;
	m_muPlus_id_theta  = -999;
	m_muMinus_id_theta = -999;
	m_muPlus_isCombMu  = -999;
	m_muMinus_isCombMu = -999;
	m_muPlus_nSCThits  = -999;
	m_muMinus_nSCThits = -999;
	m_muPlus_nPIXhits  = -999;
	m_muMinus_nPIXhits = -999;
	m_muPlus_nIDhits   = -999;
	m_muMinus_nIDhits  = -999;
	
	m_muPlus_p4Vec.SetPxPyPzE(-999, -999, -999, -sqrt(3)*999);
	m_muMinus_p4Vec.SetPxPyPzE(-999, -999, -999, -sqrt(3)*999);
	
	// vertex variables
	m_vxp_z       = -999;
	m_vxp_z_err   = -999;
	m_vxp_nTracks = -999;
	m_vxp_type    = -999;
}

void offlineTreeDigest::write()
{
	m_treeFile->cd();
	m_tree->Write();
}


