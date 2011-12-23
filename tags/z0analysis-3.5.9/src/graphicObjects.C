/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "graphicObjects.h"

graphicObjects::graphicObjects()
{

}

graphicObjects::~graphicObjects()
{

}


void graphicObjects::clearTreeVars()
{
	// all cuts - floats
	Mhat         = -9999;
	CosThetaCS   = -9999;
	CosThetaHE   = -9999;
	Ysystem      = -9999;
	Q_T          = -9999;
	betaQ        = -9999;
	betazQ       = -9999;
	betaTQ       = -9999;
	CosThetaDimu = -9999;
	ipTDiff      = -9999;
	EtaSum       = -9999;
	
	RunNumber    = -9999;
	EventNumber  = -9999;
	timestamp    = -9999;
	timestamp_ns = -9999;
	lbn          = -9999;
	bcid         = -9999;

	actualIntPerXing  = -9999.;
	averageIntPerXing = -9999.;
	mc_channel_number = 0;
	mc_event_number   = 0;
	mc_event_weight = -9999.;
	
	pileup_weight  = -9999.;
	intime_pileup_weight = -9999.;
	outoftime_pileup_weight = -9999.;
	lumi_pileup_weight = -9999.;
	EW_kfactor_weight = -9999.;
	QCD_kfactor_weight = -9999.;
	mcevent_weight = -9999.;
	total_weight   = -9999.;
	randomized_decision = 999;
	
	iLeadingMuon    = -9999;
	iSubLeadingMuon = -9999;
	ivxp            = -9999;
	
	// all cuts - vectors
	vxp_n    = -9999;
	vxp_nTracks->clear();
	vxp_type->clear();
	vxp_z->clear();
	
	n = -9999;
	E->clear();
	pt->clear();
	m->clear();
	eta->clear();
	phi->clear();
	px->clear();
	py->clear();
	pz->clear();
	charge->clear();
	allauthor->clear();
	author->clear();
	beta->clear();
	isMuonLikelihood->clear();
	matchchi2->clear();
	matchndof->clear();
	etcone20->clear();
	etcone30->clear();
	etcone40->clear();
	nucone20->clear();
	nucone30->clear();
	nucone40->clear();
	ptcone20->clear();
	ptcone30->clear();
	ptcone40->clear();
	energyLossPar->clear();
	energyLossErr->clear();
	etCore->clear();
	energyLossType->clear();
	caloMuonIdTag->clear();
	caloLRLikelihood->clear();
	bestMatch->clear();
	isStandAloneMuon->clear();
	isCombinedMuon->clear();
	isLowPtReconstructedMuon->clear();
	loose->clear();
	medium->clear();
	tight->clear();
	d0_exPV->clear();
	z0_exPV->clear();
	phi_exPV->clear();
	theta_exPV->clear();
	qoverp_exPV->clear();
	cb_d0_exPV->clear();
	cb_z0_exPV->clear();
	cb_phi_exPV->clear();
	cb_theta_exPV->clear();
	cb_qoverp_exPV->clear();
	id_d0_exPV->clear();
	id_z0_exPV->clear();
	id_phi_exPV->clear();
	id_theta_exPV->clear();
	id_qoverp_exPV->clear();
	me_d0_exPV->clear();
	me_z0_exPV->clear();
	me_phi_exPV->clear();
	me_theta_exPV->clear();
	me_qoverp_exPV->clear();
	ie_d0_exPV->clear();
	ie_z0_exPV->clear();
	ie_phi_exPV->clear();
	ie_theta_exPV->clear();
	ie_qoverp_exPV->clear();
	//SpaceTime_detID->clear();
	//SpaceTime_t->clear();
	//SpaceTime_tError->clear();
	//SpaceTime_weight->clear();
	//SpaceTime_x->clear();
	//SpaceTime_y->clear();
	//SpaceTime_z->clear();
	//SpaceTime_t_Tile->clear();
	//SpaceTime_tError_Tile->clear();
	//SpaceTime_weight_Tile->clear();
	//SpaceTime_x_Tile->clear();
	//SpaceTime_y_Tile->clear();
	//SpaceTime_z_Tile->clear();
	//SpaceTime_t_TRT->clear();
	//SpaceTime_tError_TRT->clear();
	//SpaceTime_weight_TRT->clear();
	//SpaceTime_x_TRT->clear();
	//SpaceTime_y_TRT->clear();
	//SpaceTime_z_TRT->clear();
	//SpaceTime_t_MDT->clear();
	//SpaceTime_tError_MDT->clear();
	//SpaceTime_weight_MDT->clear();
	//SpaceTime_x_MDT->clear();
	//SpaceTime_y_MDT->clear();
	//SpaceTime_z_MDT->clear();
	TileCellEnergyLayer1->clear();
	TileTimeLayer1->clear();
	TileCellRmsNoiseLayer1->clear();
	TileCellSignLayer1->clear();
	TileCellEnergyLayer2->clear();
	TileTimeLayer2->clear();
	TileCellRmsNoiseLayer2->clear();
	TileCellSignLayer2->clear();
	TileCellEnergyLayer3->clear();
	TileTimeLayer3->clear();
	TileCellRmsNoiseLayer3->clear();
	TileCellSignLayer3->clear();
	MSTrkT0_1->clear();
	MSTrkT0_2->clear();
	MSTrkT0_3->clear();
	cov_d0_exPV->clear();
	cov_z0_exPV->clear();
	cov_phi_exPV->clear();
	cov_theta_exPV->clear();
	cov_qoverp_exPV->clear();
	cov_d0_z0_exPV->clear();
	cov_d0_phi_exPV->clear();
	cov_d0_theta_exPV->clear();
	cov_d0_qoverp_exPV->clear();
	cov_z0_phi_exPV->clear();
	cov_z0_theta_exPV->clear();
	cov_z0_qoverp_exPV->clear();
	cov_phi_theta_exPV->clear();
	cov_phi_qoverp_exPV->clear();
	cov_theta_qoverp_exPV->clear();
	id_cov_d0_exPV->clear();
	id_cov_z0_exPV->clear();
	id_cov_phi_exPV->clear();
	id_cov_theta_exPV->clear();
	id_cov_qoverp_exPV->clear();
	id_cov_d0_z0_exPV->clear();
	id_cov_d0_phi_exPV->clear();
	id_cov_d0_theta_exPV->clear();
	id_cov_d0_qoverp_exPV->clear();
	id_cov_z0_phi_exPV->clear();
	id_cov_z0_theta_exPV->clear();
	id_cov_z0_qoverp_exPV->clear();
	id_cov_phi_theta_exPV->clear();
	id_cov_phi_qoverp_exPV->clear();
	id_cov_theta_qoverp_exPV->clear();
	me_cov_d0_exPV->clear();
	me_cov_z0_exPV->clear();
	me_cov_phi_exPV->clear();
	me_cov_theta_exPV->clear();
	me_cov_qoverp_exPV->clear();
	me_cov_d0_z0_exPV->clear();
	me_cov_d0_phi_exPV->clear();
	me_cov_d0_theta_exPV->clear();
	me_cov_d0_qoverp_exPV->clear();
	me_cov_z0_phi_exPV->clear();
	me_cov_z0_theta_exPV->clear();
	me_cov_z0_qoverp_exPV->clear();
	me_cov_phi_theta_exPV->clear();
	me_cov_phi_qoverp_exPV->clear();
	me_cov_theta_qoverp_exPV->clear();
	ms_d0->clear();
	ms_z0->clear();
	ms_phi->clear();
	ms_theta->clear();
	ms_qoverp->clear();
	id_d0->clear();
	id_z0->clear();
	id_phi->clear();
	id_theta->clear();
	id_qoverp->clear();
	me_d0->clear();
	me_z0->clear();
	me_phi->clear();
	me_theta->clear();
	me_qoverp->clear();
	ie_d0->clear();
	ie_z0->clear();
	ie_phi->clear();
	ie_theta->clear();
	ie_qoverp->clear();
	nOutliersOnTrack->clear();
	nBLHits->clear();
	nPixHits->clear();
	nSCTHits->clear();
	nTRTHits->clear();
	nTRTHighTHits->clear();
	nBLSharedHits->clear();
	nPixSharedHits->clear();
	nPixHoles->clear();
	nSCTSharedHits->clear();
	nSCTHoles->clear();
	nTRTOutliers->clear();
	nTRTHighTOutliers->clear();
	nGangedPixels->clear();
	nPixelDeadSensors->clear();
	nSCTDeadSensors->clear();
	nTRTDeadStraws->clear();
	expectBLayerHit->clear();
	nMDTHits->clear();
	nMDTHoles->clear();
	nCSCEtaHits->clear();
	nCSCEtaHoles->clear();
	nCSCPhiHits->clear();
	nCSCPhiHoles->clear();
	nRPCEtaHits->clear();
	nRPCEtaHoles->clear();
	nRPCPhiHits->clear();
	nRPCPhiHoles->clear();
	nTGCEtaHits->clear();
	nTGCEtaHoles->clear();
	nTGCPhiHits->clear();
	nTGCPhiHoles->clear();
	nMDTBIHits->clear();
	nMDTBMHits->clear();
	nMDTBOHits->clear();
	nMDTBEEHits->clear();
	nMDTBIS78Hits->clear();
	nMDTEIHits->clear();
	nMDTEMHits->clear();
	nMDTEOHits->clear();
	nMDTEEHits->clear();
	nRPCLayer1EtaHits->clear();
	nRPCLayer2EtaHits->clear();
	nRPCLayer3EtaHits->clear();
	nRPCLayer1PhiHits->clear();
	nRPCLayer2PhiHits->clear();
	nRPCLayer3PhiHits->clear();
	nTGCLayer1EtaHits->clear();
	nTGCLayer2EtaHits->clear();
	nTGCLayer3EtaHits->clear();
	nTGCLayer4EtaHits->clear();
	nTGCLayer1PhiHits->clear();
	nTGCLayer2PhiHits->clear();
	nTGCLayer3PhiHits->clear();
	nTGCLayer4PhiHits->clear();
	barrelSectors->clear();
	endcapSectors->clear();
	trackd0->clear();
	trackz0->clear();
	trackphi->clear();
	tracktheta->clear();
	trackqoverp->clear();
	trackcov_d0->clear();
	trackcov_z0->clear();
	trackcov_phi->clear();
	trackcov_theta->clear();
	trackcov_qoverp->clear();
	trackcov_d0_z0->clear();
	trackcov_d0_phi->clear();
	trackcov_d0_theta->clear();
	trackcov_d0_qoverp->clear();
	trackcov_z0_phi->clear();
	trackcov_z0_theta->clear();
	trackcov_z0_qoverp->clear();
	trackcov_phi_theta->clear();
	trackcov_phi_qoverp->clear();
	trackcov_theta_qoverp->clear();
	trackfitchi2->clear();
	trackfitndof->clear();
	hastrack->clear();
	truth_dr->clear();
	truth_E->clear();
	truth_pt->clear();
	truth_eta->clear();
	truth_phi->clear();
	truth_type->clear();
	truth_status->clear();
	truth_barcode->clear();
	truth_mothertype->clear();
	truth_motherbarcode->clear();
	truth_matched->clear();
	EFCB_dr->clear();
	EFCB_index->clear();
	EFMG_dr->clear();
	EFMG_index->clear();
	EFME_dr->clear();
	EFME_index->clear();
	L2CB_dr->clear();
	L2CB_index->clear();
	L1_dr->clear();
	L1_index->clear();
	
	// cut profile vectors
	vxp_z_profile->clear();
	vxp_nTracks_profile->clear();
	pT_profile->clear();
	pT_loose_profile->clear();
	pT_qOp_and_theta_loose_profile->clear();
	eta_profile->clear();
	etaTight_profile->clear();
	etaBarrel_profile->clear();
	etaFwd_profile->clear();
	etaFull_profile->clear();
	pTmatchingRatio_profile->clear();
	pTmatchingAbsDiff_profile->clear();
	pTmatchingAbsDiff_profile->clear();
	d0_profile->clear();
	z0_profile->clear();
	ip_d0_profile->clear();
	ip_z0_profile->clear();
	isolation20_profile->clear();
	isolation30_profile->clear();
	isolation40_profile->clear();
	oppositeCharge_profile->clear();
	imass_profile->clear();
	cosThetaDimu_profile->clear();
	etaSum_profile->clear();
	nMDTBI_profile->clear();
	nMDTBM_profile->clear();
	nMDTBO_profile->clear();
	nMDTEI_profile->clear();
	nMDTEM_profile->clear();
	nMDTEO_profile->clear();
	nMDTBEE_profile->clear();
	nMDTEE_profile->clear();
	nMDTBIS78_profile->clear();
	nRPCPhi1_profile->clear();
	nRPCPhi2_profile->clear();
	nRPCPhi3_profile->clear();
	nTGCPhi1_profile->clear();
	nTGCPhi2_profile->clear();
	nTGCPhi3_profile->clear();
	nTGCPhi4_profile->clear();
	nCSCEta_profile->clear();
	nCSCPhi_profile->clear();
	expectBLayerHit_profile->clear();
	nBLHits_profile->clear();
	nPixHits_profile->clear();
	nPixelDeadSensors_profile->clear();
	nPixHoles_profile->clear();
	nSCTHits_profile->clear();
	nSCTDeadSensors_profile->clear();
	nSCTHoles_profile->clear();
	nTRTHits_profile->clear();
	nTRTOutliers_profile->clear();
	eta_forTRThits_profile->clear();
	
	// eff - vectors
	tNp_triggerName->clear();
	tNp_cand_pT->clear();
	tNp_succ_pT->clear();
	tNp_cand_eta->clear();
	tNp_succ_eta->clear();
	tNp_cand_phi->clear();
	tNp_succ_phi->clear();
	tru_triggerName->clear();
	tru_cand_pT->clear();
	tru_succ_pT->clear();
	tru_cand_eta->clear();
	tru_succ_eta->clear();
	tru_cand_phi->clear();
	tru_succ_phi->clear();
	
	// truth_all (for weights)
	all_actualIntPerXing  = -9999.;
	all_averageIntPerXing = -9999.;
	all_mc_channel_number = 0;
	all_mc_event_number   = 0;
	all_mc_event_weight = -9999.;
	
	all_RunNumber = 0;
	all_pileup_weight  = -9999.;
	all_intime_pileup_weight = -9999.;
	all_outoftime_pileup_weight = -9999.;
	all_lumi_pileup_weight = -9999.;
	all_EW_kfactor_weight = -9999.;
	all_QCD_kfactor_weight = -9999.;
	all_mcevent_weight = -9999.;
	all_total_weight   = -9999.;
	all_randomized_decision = 999;
	
	all_vxp_n = 0;
	
	truth_all_dr->clear();
	truth_all_E->clear();
	truth_all_pt->clear();
	truth_all_eta->clear();
	truth_all_phi->clear();
	truth_all_type->clear();
	truth_all_status->clear();
	truth_all_barcode->clear();
	truth_all_mothertype->clear();
	truth_all_motherbarcode->clear();
	truth_all_matched->clear();
	truth_all_isValid    = false;
	
	// muonTruth
	truth_all_muonTruth_pt->clear();
	truth_all_muonTruth_m->clear();
	truth_all_muonTruth_eta->clear();
	truth_all_muonTruth_phi->clear();
	truth_all_muonTruth_charge->clear();
	truth_all_muonTruth_PDGID->clear();
	truth_all_muonTruth_barcode->clear();
	truth_all_muonTruth_type->clear();
	truth_all_muonTruth_origin->clear();
	// MC event
	truth_all_mcevt_signal_process_id->clear();
	truth_all_mcevt_event_number->clear();
	truth_all_mcevt_event_scale->clear();
	truth_all_mcevt_alphaQCD->clear();
	truth_all_mcevt_alphaQED->clear();
	truth_all_mcevt_pdf_id1->clear();
	truth_all_mcevt_pdf_id2->clear();
	truth_all_mcevt_pdf_x1->clear();
	truth_all_mcevt_pdf_x2->clear();
	truth_all_mcevt_pdf_scale->clear();
	truth_all_mcevt_pdf1->clear();
	truth_all_mcevt_pdf2->clear();
	truth_all_mcevt_weight->clear();
	//MC
	truth_all_mc_vxp_n = -999;
	truth_all_mc_pt->clear();
	truth_all_mc_m->clear();
	truth_all_mc_eta->clear();
	truth_all_mc_phi->clear();
	truth_all_mc_status->clear();
	truth_all_mc_barcode->clear();
	truth_all_mc_pdgId->clear();
	truth_all_mc_charge->clear();
	
	truth_all_Mhat       = 0.;
	truth_all_CosThetaCS = 0.;
	truth_all_CosThetaHE = 0.;
	truth_all_ySystem    = 0.;
	truth_all_QT         = 0.;
	truth_all_betaQ      = 0.;
	truth_all_betazQ     = 0.;
	truth_all_betaTQ     = 0.;
	
	truth_all_partons_mc_pt->clear();
	truth_all_partons_mc_m->clear();
	truth_all_partons_mc_eta->clear();
	truth_all_partons_mc_phi->clear();
	truth_all_partons_mc_status->clear();
	truth_all_partons_mc_barcode->clear();
	truth_all_partons_mc_pdgId->clear();
	truth_all_partons_mc_charge->clear();
	
	truth_all_vKKwgt->clear();
	truth_all_vZPwgt->clear();
	truth_all_vBSMmass->clear();
	
	recon_all_E->clear();
	recon_all_pt->clear();
	recon_all_m->clear();
	recon_all_eta->clear();
	recon_all_phi->clear();
	recon_all_px->clear();
	recon_all_py->clear();
	recon_all_pz->clear();
	recon_all_charge->clear();
	recon_all_y->clear();
	recon_all_id->clear();
	recon_all_theta->clear();
	recon_all_isValid    = false;
	recon_all_vxp_n      = -999;
	recon_all_Mhat       = 0.;
	recon_all_CosThetaCS = 0.;
	recon_all_CosThetaHE = 0.;
	recon_all_ySystem    = 0.;
	recon_all_QT         = 0.;
	recon_all_betaQ      = 0.;
	recon_all_betazQ     = 0.;
	recon_all_betaTQ     = 0.;
}

void graphicObjects::writeTrees(TDirectory* tDir_allCuts,
TDirectory* tDir_cutsProfile,
TDirectory* tDir_efficiency)
{
	TFile* f = NULL;

	f = tree_allCuts->GetCurrentFile();
	f->cd( tDir_allCuts->GetName() );
	tree_allCuts->Write("", TObject::kOverwrite);
	
	f = tree_cutsProfile->GetCurrentFile();
	f->cd( tDir_cutsProfile->GetName() );
	tree_cutsProfile->Write("", TObject::kOverwrite);
	
	f = tree_efficiency->GetCurrentFile();
	f->cd( tDir_efficiency->GetName() );
	tree_efficiency->Write("", TObject::kOverwrite);
	
	f->Write();
	f->Close();
	
	//tDir_allCuts->cd();
	//tree_allCuts->Write();

	//tDir_cutsProfile->cd();
	//tree_cutsProfile->Write();
	
	//tDir_efficiency->cd();
	//tree_efficiency->Write();
}

void graphicObjects::writeTrees(TDirectory* tDir_allCuts,
TDirectory* tDir_cutsProfile,
TDirectory* tDir_efficiency,
TDirectory* tDir_truth)
{
	TFile* f = NULL;
	
	f = tree_truth->GetCurrentFile();
	f->cd( tDir_truth->GetName() );
	tree_truth->Write("", TObject::kOverwrite);

	//f->Write();
	//f->Close();
	
	writeTrees(tDir_allCuts, tDir_cutsProfile, tDir_efficiency);
}

void graphicObjects::setTrees(TDirectory* tDir_allCuts,
TDirectory* tDir_cutsProfile,
TDirectory* tDir_efficiency)
{
	// all cuts - vectors
	vxp_nTracks = new vector<int>;
	vxp_type = new vector<int>;
	vxp_z = new vector<float>;
	
	E = new vector<float>;
	pt = new vector<float>;
	m = new vector<float>;
	eta = new vector<float>;
	phi = new vector<float>;
	px = new vector<float>;
	py = new vector<float>;
	pz = new vector<float>;
	charge = new vector<float>;
	allauthor = new vector<unsigned short>;
	author = new vector<int>;
	beta = new vector<float>;
	isMuonLikelihood = new vector<float>;
	matchchi2 = new vector<float>;
	matchndof = new vector<int>;
	etcone20 = new vector<float>;
	etcone30 = new vector<float>;
	etcone40 = new vector<float>;
	nucone20 = new vector<float>;
	nucone30 = new vector<float>;
	nucone40 = new vector<float>;
	ptcone20 = new vector<float>;
	ptcone30 = new vector<float>;
	ptcone40 = new vector<float>;
	energyLossPar = new vector<float>;
	energyLossErr = new vector<float>;
	etCore = new vector<float>;
	energyLossType = new vector<float>;
	caloMuonIdTag = new vector<unsigned short>;
	caloLRLikelihood = new vector<double>;
	bestMatch = new vector<int>;
	isStandAloneMuon = new vector<int>;
	isCombinedMuon = new vector<int>;
	isLowPtReconstructedMuon = new vector<int>;
	loose = new vector<int>;
	medium = new vector<int>;
	tight = new vector<int>;
	d0_exPV = new vector<float>;
	z0_exPV = new vector<float>;
	phi_exPV = new vector<float>;
	theta_exPV = new vector<float>;
	qoverp_exPV = new vector<float>;
	cb_d0_exPV = new vector<float>;
	cb_z0_exPV = new vector<float>;
	cb_phi_exPV = new vector<float>;
	cb_theta_exPV = new vector<float>;
	cb_qoverp_exPV = new vector<float>;
	id_d0_exPV = new vector<float>;
	id_z0_exPV = new vector<float>;
	id_phi_exPV = new vector<float>;
	id_theta_exPV = new vector<float>;
	id_qoverp_exPV = new vector<float>;
	me_d0_exPV = new vector<float>;
	me_z0_exPV = new vector<float>;
	me_phi_exPV = new vector<float>;
	me_theta_exPV = new vector<float>;
	me_qoverp_exPV = new vector<float>;
	ie_d0_exPV = new vector<float>;
	ie_z0_exPV = new vector<float>;
	ie_phi_exPV = new vector<float>;
	ie_theta_exPV = new vector<float>;
	ie_qoverp_exPV = new vector<float>;
	////SpaceTime_detID = new vector<vector<int> >;
	////SpaceTime_t = new vector<vector<short> >;
	////SpaceTime_tError = new vector<vector<short> >;
	////SpaceTime_weight = new vector<vector<short> >;
	////SpaceTime_x = new vector<vector<short> >;
	////SpaceTime_y = new vector<vector<short> >;
	////SpaceTime_z = new vector<vector<short> >;
	////SpaceTime_t_Tile = new vector<vector<short> >;
	////SpaceTime_tError_Tile = new vector<vector<short> >;
	////SpaceTime_weight_Tile = new vector<vector<short> >;
	////SpaceTime_x_Tile = new vector<vector<short> >;
	////SpaceTime_y_Tile = new vector<vector<short> >;
	////SpaceTime_z_Tile = new vector<vector<short> >;
	////SpaceTime_t_TRT = new vector<vector<short> >;
	////SpaceTime_tError_TRT = new vector<vector<short> >;
	////SpaceTime_weight_TRT = new vector<vector<short> >;
	////SpaceTime_x_TRT = new vector<vector<short> >;
	////SpaceTime_y_TRT = new vector<vector<short> >;
	////SpaceTime_z_TRT = new vector<vector<short> >;
	////SpaceTime_t_MDT = new vector<vector<short> >;
	////SpaceTime_tError_MDT = new vector<vector<short> >;
	////SpaceTime_weight_MDT = new vector<vector<short> >;
	////SpaceTime_x_MDT = new vector<vector<short> >;
	////SpaceTime_y_MDT = new vector<vector<short> >;
	////SpaceTime_z_MDT = new vector<vector<short> >;
	TileCellEnergyLayer1 = new vector<float>;
	TileTimeLayer1 = new vector<float>;
	TileCellRmsNoiseLayer1 = new vector<float>;
	TileCellSignLayer1 = new vector<float>;
	TileCellEnergyLayer2 = new vector<float>;
	TileTimeLayer2 = new vector<float>;
	TileCellRmsNoiseLayer2 = new vector<float>;
	TileCellSignLayer2 = new vector<float>;
	TileCellEnergyLayer3 = new vector<float>;
	TileTimeLayer3 = new vector<float>;
	TileCellRmsNoiseLayer3 = new vector<float>;
	TileCellSignLayer3 = new vector<float>;
	MSTrkT0_1 = new vector<float>;
	MSTrkT0_2 = new vector<float>;
	MSTrkT0_3 = new vector<float>;
	cov_d0_exPV = new vector<float>;
	cov_z0_exPV = new vector<float>;
	cov_phi_exPV = new vector<float>;
	cov_theta_exPV = new vector<float>;
	cov_qoverp_exPV = new vector<float>;
	cov_d0_z0_exPV = new vector<float>;
	cov_d0_phi_exPV = new vector<float>;
	cov_d0_theta_exPV = new vector<float>;
	cov_d0_qoverp_exPV = new vector<float>;
	cov_z0_phi_exPV = new vector<float>;
	cov_z0_theta_exPV = new vector<float>;
	cov_z0_qoverp_exPV = new vector<float>;
	cov_phi_theta_exPV = new vector<float>;
	cov_phi_qoverp_exPV = new vector<float>;
	cov_theta_qoverp_exPV = new vector<float>;
	id_cov_d0_exPV = new vector<float>;
	id_cov_z0_exPV = new vector<float>;
	id_cov_phi_exPV = new vector<float>;
	id_cov_theta_exPV = new vector<float>;
	id_cov_qoverp_exPV = new vector<float>;
	id_cov_d0_z0_exPV = new vector<float>;
	id_cov_d0_phi_exPV = new vector<float>;
	id_cov_d0_theta_exPV = new vector<float>;
	id_cov_d0_qoverp_exPV = new vector<float>;
	id_cov_z0_phi_exPV = new vector<float>;
	id_cov_z0_theta_exPV = new vector<float>;
	id_cov_z0_qoverp_exPV = new vector<float>;
	id_cov_phi_theta_exPV = new vector<float>;
	id_cov_phi_qoverp_exPV = new vector<float>;
	id_cov_theta_qoverp_exPV = new vector<float>;
	me_cov_d0_exPV = new vector<float>;
	me_cov_z0_exPV = new vector<float>;
	me_cov_phi_exPV = new vector<float>;
	me_cov_theta_exPV = new vector<float>;
	me_cov_qoverp_exPV = new vector<float>;
	me_cov_d0_z0_exPV = new vector<float>;
	me_cov_d0_phi_exPV = new vector<float>;
	me_cov_d0_theta_exPV = new vector<float>;
	me_cov_d0_qoverp_exPV = new vector<float>;
	me_cov_z0_phi_exPV = new vector<float>;
	me_cov_z0_theta_exPV = new vector<float>;
	me_cov_z0_qoverp_exPV = new vector<float>;
	me_cov_phi_theta_exPV = new vector<float>;
	me_cov_phi_qoverp_exPV = new vector<float>;
	me_cov_theta_qoverp_exPV = new vector<float>;
	ms_d0 = new vector<float>;
	ms_z0 = new vector<float>;
	ms_phi = new vector<float>;
	ms_theta = new vector<float>;
	ms_qoverp = new vector<float>;
	id_d0 = new vector<float>;
	id_z0 = new vector<float>;
	id_phi = new vector<float>;
	id_theta = new vector<float>;
	id_qoverp = new vector<float>;
	me_d0 = new vector<float>;
	me_z0 = new vector<float>;
	me_phi = new vector<float>;
	me_theta = new vector<float>;
	me_qoverp = new vector<float>;
	ie_d0 = new vector<float>;
	ie_z0 = new vector<float>;
	ie_phi = new vector<float>;
	ie_theta = new vector<float>;
	ie_qoverp = new vector<float>;
	nOutliersOnTrack = new vector<int>;
	nBLHits = new vector<int>;
	nPixHits = new vector<int>;
	nSCTHits = new vector<int>;
	nTRTHits = new vector<int>;
	nTRTHighTHits = new vector<int>;
	nBLSharedHits = new vector<int>;
	nPixSharedHits = new vector<int>;
	nPixHoles = new vector<int>;
	nSCTSharedHits = new vector<int>;
	nSCTHoles = new vector<int>;
	nTRTOutliers = new vector<int>;
	nTRTHighTOutliers = new vector<int>;
	nGangedPixels = new vector<int>;
	nPixelDeadSensors = new vector<int>;
	nSCTDeadSensors = new vector<int>;
	nTRTDeadStraws = new vector<int>;
	expectBLayerHit = new vector<int>;
	nMDTHits = new vector<int>;
	nMDTHoles = new vector<int>;
	nCSCEtaHits = new vector<int>;
	nCSCEtaHoles = new vector<int>;
	nCSCPhiHits = new vector<int>;
	nCSCPhiHoles = new vector<int>;
	nRPCEtaHits = new vector<int>;
	nRPCEtaHoles = new vector<int>;
	nRPCPhiHits = new vector<int>;
	nRPCPhiHoles = new vector<int>;
	nTGCEtaHits = new vector<int>;
	nTGCEtaHoles = new vector<int>;
	nTGCPhiHits = new vector<int>;
	nTGCPhiHoles = new vector<int>;
	nMDTBIHits = new vector<int>;
	nMDTBMHits = new vector<int>;
	nMDTBOHits = new vector<int>;
	nMDTBEEHits = new vector<int>;
	nMDTBIS78Hits = new vector<int>;
	nMDTEIHits = new vector<int>;
	nMDTEMHits = new vector<int>;
	nMDTEOHits = new vector<int>;
	nMDTEEHits = new vector<int>;
	nRPCLayer1EtaHits = new vector<int>;
	nRPCLayer2EtaHits = new vector<int>;
	nRPCLayer3EtaHits = new vector<int>;
	nRPCLayer1PhiHits = new vector<int>;
	nRPCLayer2PhiHits = new vector<int>;
	nRPCLayer3PhiHits = new vector<int>;
	nTGCLayer1EtaHits = new vector<int>;
	nTGCLayer2EtaHits = new vector<int>;
	nTGCLayer3EtaHits = new vector<int>;
	nTGCLayer4EtaHits = new vector<int>;
	nTGCLayer1PhiHits = new vector<int>;
	nTGCLayer2PhiHits = new vector<int>;
	nTGCLayer3PhiHits = new vector<int>;
	nTGCLayer4PhiHits = new vector<int>;
	barrelSectors = new vector<int>;
	endcapSectors = new vector<int>;
	trackd0 = new vector<float>;
	trackz0 = new vector<float>;
	trackphi = new vector<float>;
	tracktheta = new vector<float>;
	trackqoverp = new vector<float>;
	trackcov_d0 = new vector<float>;
	trackcov_z0 = new vector<float>;
	trackcov_phi = new vector<float>;
	trackcov_theta = new vector<float>;
	trackcov_qoverp = new vector<float>;
	trackcov_d0_z0 = new vector<float>;
	trackcov_d0_phi = new vector<float>;
	trackcov_d0_theta = new vector<float>;
	trackcov_d0_qoverp = new vector<float>;
	trackcov_z0_phi = new vector<float>;
	trackcov_z0_theta = new vector<float>;
	trackcov_z0_qoverp = new vector<float>;
	trackcov_phi_theta = new vector<float>;
	trackcov_phi_qoverp = new vector<float>;
	trackcov_theta_qoverp = new vector<float>;
	trackfitchi2 = new vector<float>;
	trackfitndof = new vector<int>;
	hastrack = new vector<int>;
	truth_dr = new vector<float>;
	truth_E = new vector<float>;
	truth_pt = new vector<float>;
	truth_eta = new vector<float>;
	truth_phi = new vector<float>;
	truth_type = new vector<int>;
	truth_status = new vector<int>;
	truth_barcode = new vector<int>;
	truth_mothertype = new vector<int>;
	truth_motherbarcode = new vector<int>;
	truth_matched = new vector<int>;
	EFCB_dr = new vector<float>;
	EFCB_index = new vector<int>;
	EFMG_dr = new vector<float>;
	EFMG_index = new vector<int>;
	EFME_dr = new vector<float>;
	EFME_index = new vector<int>;
	L2CB_dr = new vector<float>;
	L2CB_index = new vector<int>;
	L1_dr = new vector<float>;
	L1_index = new vector<int>;

	
	// cut profile vectors
	pT_profile = new vector<float>;
	pT_loose_profile = new vector<float>;
	pT_qOp_and_theta_profile = new vector<float>;
	pT_qOp_and_theta_loose_profile = new vector<float>;
	eta_profile = new vector<float>;
	etaTight_profile = new vector<float>;
	etaBarrel_profile = new vector<float>;
	etaFwd_profile = new vector<float>;
	etaFull_profile = new vector<float>;
	pTmatchingRatio_profile = new vector<float>;
	pTmatchingAbsDiff_profile = new vector<float>;
	d0_profile = new vector<float>;
	z0_profile = new vector<float>;
	ip_d0_profile = new vector<float>;
	ip_z0_profile = new vector<float>;
	isolation20_profile = new vector<float>;
	isolation30_profile = new vector<float>;
	isolation40_profile = new vector<float>;
	oppositeCharge_profile = new vector<float>;
	imass_profile          = new vector<float>;
	cosThetaDimu_profile   = new vector<float>;
	etaSum_profile         = new vector<float>;
	nMDTBI_profile = new vector<int>;
	nMDTBM_profile = new vector<int>;
	nMDTBO_profile = new vector<int>;
	nMDTEI_profile = new vector<int>;
	nMDTEM_profile = new vector<int>;
	nMDTEO_profile = new vector<int>;
	nMDTBEE_profile = new vector<int>;
	nMDTEE_profile = new vector<int>;
	nMDTBIS78_profile = new vector<int>;
	nRPCPhi1_profile = new vector<int>;
	nRPCPhi2_profile = new vector<int>;
	nRPCPhi3_profile = new vector<int>;
	nTGCPhi1_profile = new vector<int>;
	nTGCPhi2_profile = new vector<int>;
	nTGCPhi3_profile = new vector<int>;
	nTGCPhi4_profile = new vector<int>;
	nCSCEta_profile = new vector<int>;
	nCSCPhi_profile = new vector<int>;
	expectBLayerHit_profile = new vector<int>;
	nBLHits_profile = new vector<int>;
	nPixHits_profile = new vector<int>;
	nPixelDeadSensors_profile = new vector<int>;
	nPixHoles_profile = new vector<int>;
	nSCTHits_profile = new vector<int>;
	nSCTDeadSensors_profile = new vector<int>;
	nSCTHoles_profile = new vector<int>;
	nTRTHits_profile = new vector<int>;
	nTRTOutliers_profile = new vector<int>;
	eta_forTRThits_profile = new vector<float>;
	vxp_z_profile = new vector<float>;
	vxp_nTracks_profile = new vector<int>;
	
	// eff vectors
	tNp_triggerName = new vector<string>; // only one entry but easier to access...
	tNp_cand_pT = new vector<float>;
	tNp_succ_pT = new vector<float>;
	tNp_cand_eta = new vector<float>;
	tNp_succ_eta = new vector<float>;
	tNp_cand_phi = new vector<float>;
	tNp_succ_phi = new vector<float>;
	tru_triggerName = new vector<string>; // only one entry but easier to access...
	tru_cand_pT = new vector<float>;
	tru_succ_pT = new vector<float>;
	tru_cand_eta = new vector<float>;
	tru_succ_eta = new vector<float>;
	tru_cand_phi = new vector<float>;
	tru_succ_phi = new vector<float>;
	
	
	if(tDir_allCuts!=NULL) tDir_allCuts->cd();
	tree_allCuts = new TTree("allCuts_tree","allCuts_tree");
	tree_allCuts->SetDirectory(tDir_allCuts);
	// 2 muons (floats)
	tree_allCuts->Branch( "Mhat",         &Mhat );
	tree_allCuts->Branch( "CosThetaCS",   &CosThetaCS );
	tree_allCuts->Branch( "CosThetaHE",   &CosThetaHE );
	tree_allCuts->Branch( "Ysystem",      &Ysystem );
	tree_allCuts->Branch( "Q_T",          &Q_T );
	tree_allCuts->Branch( "betaQ",          &betaQ );
	tree_allCuts->Branch( "betazQ",          &betazQ );
	tree_allCuts->Branch( "betaTQ",          &betaTQ );
	tree_allCuts->Branch( "CosThetaDimu", &CosThetaDimu );
	tree_allCuts->Branch( "ipTDiff",      &ipTDiff );
	tree_allCuts->Branch( "EtaSum",       &EtaSum );
	
	tree_allCuts->Branch( "iLeadingMuon",    &iLeadingMuon );
	tree_allCuts->Branch( "iSubLeadingMuon", &iSubLeadingMuon );
	tree_allCuts->Branch( "ivxp",            &ivxp );
	
	tree_allCuts->Branch( "RunNumber",    &RunNumber );
	tree_allCuts->Branch( "EventNumber",  &EventNumber );
	tree_allCuts->Branch( "timestamp",    &timestamp );
	tree_allCuts->Branch( "timestamp_ns", &timestamp_ns );
	tree_allCuts->Branch( "lbn",          &lbn );
	tree_allCuts->Branch( "bcid",         &bcid );
	
	tree_allCuts->Branch( "actualIntPerXing",  &actualIntPerXing );
	tree_allCuts->Branch( "averageIntPerXing", &averageIntPerXing );
	tree_allCuts->Branch( "mc_channel_number", &mc_channel_number );
	tree_allCuts->Branch( "mc_event_number",   &mc_event_number );
	tree_allCuts->Branch( "mc_event_weight",   &mc_event_weight );
	
	tree_allCuts->Branch( "pileup_weight",  &pileup_weight );
	tree_allCuts->Branch( "intime_pileup_weight",  &intime_pileup_weight );
	tree_allCuts->Branch( "outoftime_pileup_weight",  &outoftime_pileup_weight );
	tree_allCuts->Branch( "lumi_pileup_weight",  &lumi_pileup_weight );
	tree_allCuts->Branch( "EW_kfactor_weight", &EW_kfactor_weight );
	tree_allCuts->Branch( "QCD_kfactor_weight", &QCD_kfactor_weight );
	tree_allCuts->Branch( "mcevent_weight", &mcevent_weight );
	tree_allCuts->Branch( "total_weight",   &total_weight );
	tree_allCuts->Branch( "randomized_decision",   &randomized_decision );
	
	tree_allCuts->Branch( "vxp_n",       &vxp_n );
	tree_allCuts->Branch( "vxp_nTracks", &vxp_nTracks );
	tree_allCuts->Branch( "vxp_type",    &vxp_type );
	tree_allCuts->Branch( "vxp_z",       &vxp_z );
	
	// 1 muon (vectors)
	tree_allCuts->Branch( "n", &n);
	tree_allCuts->Branch( "E", &E);
	tree_allCuts->Branch( "pt", &pt);
	tree_allCuts->Branch( "m", &m);
	tree_allCuts->Branch( "eta", &eta);
	tree_allCuts->Branch( "phi", &phi);
	tree_allCuts->Branch( "px", &px);
	tree_allCuts->Branch( "py", &py);
	tree_allCuts->Branch( "pz", &pz);
	tree_allCuts->Branch( "charge", &charge);
	tree_allCuts->Branch( "allauthor", &allauthor);
	tree_allCuts->Branch( "author", &author);
	tree_allCuts->Branch( "beta", &beta);
	tree_allCuts->Branch( "isMuonLikelihood", &isMuonLikelihood);
	tree_allCuts->Branch( "matchchi2", &matchchi2);
	tree_allCuts->Branch( "matchndof", &matchndof);
	tree_allCuts->Branch( "etcone20", &etcone20);
	tree_allCuts->Branch( "etcone30", &etcone30);
	tree_allCuts->Branch( "etcone40", &etcone40);
	tree_allCuts->Branch( "nucone20", &nucone20);
	tree_allCuts->Branch( "nucone30", &nucone30);
	tree_allCuts->Branch( "nucone40", &nucone40);
	tree_allCuts->Branch( "ptcone20", &ptcone20);
	tree_allCuts->Branch( "ptcone30", &ptcone30);
	tree_allCuts->Branch( "ptcone40", &ptcone40);
	tree_allCuts->Branch( "energyLossPar", &energyLossPar);
	tree_allCuts->Branch( "energyLossErr", &energyLossErr);
	tree_allCuts->Branch( "etCore", &etCore);
	tree_allCuts->Branch( "energyLossType", &energyLossType);
	tree_allCuts->Branch( "caloMuonIdTag", &caloMuonIdTag);
	tree_allCuts->Branch( "caloLRLikelihood", &caloLRLikelihood);
	tree_allCuts->Branch( "bestMatch", &bestMatch);
	tree_allCuts->Branch( "isStandAloneMuon", &isStandAloneMuon);
	tree_allCuts->Branch( "isCombinedMuon", &isCombinedMuon);
	tree_allCuts->Branch( "isLowPtReconstructedMuon", &isLowPtReconstructedMuon);
	tree_allCuts->Branch( "loose", &loose);
	tree_allCuts->Branch( "medium", &medium);
	tree_allCuts->Branch( "tight", &tight);
	tree_allCuts->Branch( "d0_exPV", &d0_exPV);
	tree_allCuts->Branch( "z0_exPV", &z0_exPV);
	tree_allCuts->Branch( "phi_exPV", &phi_exPV);
	tree_allCuts->Branch( "theta_exPV", &theta_exPV);
	tree_allCuts->Branch( "qoverp_exPV", &qoverp_exPV);
	tree_allCuts->Branch( "cb_d0_exPV", &cb_d0_exPV);
	tree_allCuts->Branch( "cb_z0_exPV", &cb_z0_exPV);
	tree_allCuts->Branch( "cb_phi_exPV", &cb_phi_exPV);
	tree_allCuts->Branch( "cb_theta_exPV", &cb_theta_exPV);
	tree_allCuts->Branch( "cb_qoverp_exPV", &cb_qoverp_exPV);
	tree_allCuts->Branch( "id_d0_exPV", &id_d0_exPV);
	tree_allCuts->Branch( "id_z0_exPV", &id_z0_exPV);
	tree_allCuts->Branch( "id_phi_exPV", &id_phi_exPV);
	tree_allCuts->Branch( "id_theta_exPV", &id_theta_exPV);
	tree_allCuts->Branch( "id_qoverp_exPV", &id_qoverp_exPV);
	tree_allCuts->Branch( "me_d0_exPV", &me_d0_exPV);
	tree_allCuts->Branch( "me_z0_exPV", &me_z0_exPV);
	tree_allCuts->Branch( "me_phi_exPV", &me_phi_exPV);
	tree_allCuts->Branch( "me_theta_exPV", &me_theta_exPV);
	tree_allCuts->Branch( "me_qoverp_exPV", &me_qoverp_exPV);
	tree_allCuts->Branch( "ie_d0_exPV", &ie_d0_exPV);
	tree_allCuts->Branch( "ie_z0_exPV", &ie_z0_exPV);
	tree_allCuts->Branch( "ie_phi_exPV", &ie_phi_exPV);
	tree_allCuts->Branch( "ie_theta_exPV", &ie_theta_exPV);
	tree_allCuts->Branch( "ie_qoverp_exPV", &ie_qoverp_exPV);
	//tree_allCuts->Branch( "SpaceTime_detID", &SpaceTime_detID);
	//tree_allCuts->Branch( "SpaceTime_t", &SpaceTime_t);
	//tree_allCuts->Branch( "SpaceTime_tError", &SpaceTime_tError);
	//tree_allCuts->Branch( "SpaceTime_weight", &SpaceTime_weight);
	//tree_allCuts->Branch( "SpaceTime_x", &SpaceTime_x);
	//tree_allCuts->Branch( "SpaceTime_y", &SpaceTime_y);
	//tree_allCuts->Branch( "SpaceTime_z", &SpaceTime_z);
	//tree_allCuts->Branch( "SpaceTime_t_Tile", &SpaceTime_t_Tile);
	//tree_allCuts->Branch( "SpaceTime_tError_Tile", &SpaceTime_tError_Tile);
	//tree_allCuts->Branch( "SpaceTime_weight_Tile", &SpaceTime_weight_Tile);
	//tree_allCuts->Branch( "SpaceTime_x_Tile", &SpaceTime_x_Tile);
	//tree_allCuts->Branch( "SpaceTime_y_Tile", &SpaceTime_y_Tile);
	//tree_allCuts->Branch( "SpaceTime_z_Tile", &SpaceTime_z_Tile);
	//tree_allCuts->Branch( "SpaceTime_t_TRT", &SpaceTime_t_TRT);
	//tree_allCuts->Branch( "SpaceTime_tError_TRT", &SpaceTime_tError_TRT);
	//tree_allCuts->Branch( "SpaceTime_weight_TRT", &SpaceTime_weight_TRT);
	//tree_allCuts->Branch( "SpaceTime_x_TRT", &SpaceTime_x_TRT);
	//tree_allCuts->Branch( "SpaceTime_y_TRT", &SpaceTime_y_TRT);
	//tree_allCuts->Branch( "SpaceTime_z_TRT", &SpaceTime_z_TRT);
	//tree_allCuts->Branch( "SpaceTime_t_MDT", &SpaceTime_t_MDT);
	//tree_allCuts->Branch( "SpaceTime_tError_MDT", &SpaceTime_tError_MDT);
	//tree_allCuts->Branch( "SpaceTime_weight_MDT", &SpaceTime_weight_MDT);
	//tree_allCuts->Branch( "SpaceTime_x_MDT", &SpaceTime_x_MDT);
	//tree_allCuts->Branch( "SpaceTime_y_MDT", &SpaceTime_y_MDT);
	//tree_allCuts->Branch( "SpaceTime_z_MDT", &SpaceTime_z_MDT);
	tree_allCuts->Branch( "TileCellEnergyLayer1", &TileCellEnergyLayer1);
	tree_allCuts->Branch( "TileTimeLayer1", &TileTimeLayer1);
	tree_allCuts->Branch( "TileCellRmsNoiseLayer1", &TileCellRmsNoiseLayer1);
	tree_allCuts->Branch( "TileCellSignLayer1", &TileCellSignLayer1);
	tree_allCuts->Branch( "TileCellEnergyLayer2", &TileCellEnergyLayer2);
	tree_allCuts->Branch( "TileTimeLayer2", &TileTimeLayer2);
	tree_allCuts->Branch( "TileCellRmsNoiseLayer2", &TileCellRmsNoiseLayer2);
	tree_allCuts->Branch( "TileCellSignLayer2", &TileCellSignLayer2);
	tree_allCuts->Branch( "TileCellEnergyLayer3", &TileCellEnergyLayer3);
	tree_allCuts->Branch( "TileTimeLayer3", &TileTimeLayer3);
	tree_allCuts->Branch( "TileCellRmsNoiseLayer3", &TileCellRmsNoiseLayer3);
	tree_allCuts->Branch( "TileCellSignLayer3", &TileCellSignLayer3);
	tree_allCuts->Branch( "MSTrkT0_1", &MSTrkT0_1);
	tree_allCuts->Branch( "MSTrkT0_2", &MSTrkT0_2);
	tree_allCuts->Branch( "MSTrkT0_3", &MSTrkT0_3);
	tree_allCuts->Branch( "cov_d0_exPV", &cov_d0_exPV);
	tree_allCuts->Branch( "cov_z0_exPV", &cov_z0_exPV);
	tree_allCuts->Branch( "cov_phi_exPV", &cov_phi_exPV);
	tree_allCuts->Branch( "cov_theta_exPV", &cov_theta_exPV);
	tree_allCuts->Branch( "cov_qoverp_exPV", &cov_qoverp_exPV);
	tree_allCuts->Branch( "cov_d0_z0_exPV", &cov_d0_z0_exPV);
	tree_allCuts->Branch( "cov_d0_phi_exPV", &cov_d0_phi_exPV);
	tree_allCuts->Branch( "cov_d0_theta_exPV", &cov_d0_theta_exPV);
	tree_allCuts->Branch( "cov_d0_qoverp_exPV", &cov_d0_qoverp_exPV);
	tree_allCuts->Branch( "cov_z0_phi_exPV", &cov_z0_phi_exPV);
	tree_allCuts->Branch( "cov_z0_theta_exPV", &cov_z0_theta_exPV);
	tree_allCuts->Branch( "cov_z0_qoverp_exPV", &cov_z0_qoverp_exPV);
	tree_allCuts->Branch( "cov_phi_theta_exPV", &cov_phi_theta_exPV);
	tree_allCuts->Branch( "cov_phi_qoverp_exPV", &cov_phi_qoverp_exPV);
	tree_allCuts->Branch( "cov_theta_qoverp_exPV", &cov_theta_qoverp_exPV);
	tree_allCuts->Branch( "id_cov_d0_exPV", &id_cov_d0_exPV);
	tree_allCuts->Branch( "id_cov_z0_exPV", &id_cov_z0_exPV);
	tree_allCuts->Branch( "id_cov_phi_exPV", &id_cov_phi_exPV);
	tree_allCuts->Branch( "id_cov_theta_exPV", &id_cov_theta_exPV);
	tree_allCuts->Branch( "id_cov_qoverp_exPV", &id_cov_qoverp_exPV);
	tree_allCuts->Branch( "id_cov_d0_z0_exPV", &id_cov_d0_z0_exPV);
	tree_allCuts->Branch( "id_cov_d0_phi_exPV", &id_cov_d0_phi_exPV);
	tree_allCuts->Branch( "id_cov_d0_theta_exPV", &id_cov_d0_theta_exPV);
	tree_allCuts->Branch( "id_cov_d0_qoverp_exPV", &id_cov_d0_qoverp_exPV);
	tree_allCuts->Branch( "id_cov_z0_phi_exPV", &id_cov_z0_phi_exPV);
	tree_allCuts->Branch( "id_cov_z0_theta_exPV", &id_cov_z0_theta_exPV);
	tree_allCuts->Branch( "id_cov_z0_qoverp_exPV", &id_cov_z0_qoverp_exPV);
	tree_allCuts->Branch( "id_cov_phi_theta_exPV", &id_cov_phi_theta_exPV);
	tree_allCuts->Branch( "id_cov_phi_qoverp_exPV", &id_cov_phi_qoverp_exPV);
	tree_allCuts->Branch( "id_cov_theta_qoverp_exPV", &id_cov_theta_qoverp_exPV);
	tree_allCuts->Branch( "me_cov_d0_exPV", &me_cov_d0_exPV);
	tree_allCuts->Branch( "me_cov_z0_exPV", &me_cov_z0_exPV);
	tree_allCuts->Branch( "me_cov_phi_exPV", &me_cov_phi_exPV);
	tree_allCuts->Branch( "me_cov_theta_exPV", &me_cov_theta_exPV);
	tree_allCuts->Branch( "me_cov_qoverp_exPV", &me_cov_qoverp_exPV);
	tree_allCuts->Branch( "me_cov_d0_z0_exPV", &me_cov_d0_z0_exPV);
	tree_allCuts->Branch( "me_cov_d0_phi_exPV", &me_cov_d0_phi_exPV);
	tree_allCuts->Branch( "me_cov_d0_theta_exPV", &me_cov_d0_theta_exPV);
	tree_allCuts->Branch( "me_cov_d0_qoverp_exPV", &me_cov_d0_qoverp_exPV);
	tree_allCuts->Branch( "me_cov_z0_phi_exPV", &me_cov_z0_phi_exPV);
	tree_allCuts->Branch( "me_cov_z0_theta_exPV", &me_cov_z0_theta_exPV);
	tree_allCuts->Branch( "me_cov_z0_qoverp_exPV", &me_cov_z0_qoverp_exPV);
	tree_allCuts->Branch( "me_cov_phi_theta_exPV", &me_cov_phi_theta_exPV);
	tree_allCuts->Branch( "me_cov_phi_qoverp_exPV", &me_cov_phi_qoverp_exPV);
	tree_allCuts->Branch( "me_cov_theta_qoverp_exPV", &me_cov_theta_qoverp_exPV);
	tree_allCuts->Branch( "ms_d0", &ms_d0);
	tree_allCuts->Branch( "ms_z0", &ms_z0);
	tree_allCuts->Branch( "ms_phi", &ms_phi);
	tree_allCuts->Branch( "ms_theta", &ms_theta);
	tree_allCuts->Branch( "ms_qoverp", &ms_qoverp);
	tree_allCuts->Branch( "id_d0", &id_d0);
	tree_allCuts->Branch( "id_z0", &id_z0);
	tree_allCuts->Branch( "id_phi", &id_phi);
	tree_allCuts->Branch( "id_theta", &id_theta);
	tree_allCuts->Branch( "id_qoverp", &id_qoverp);
	tree_allCuts->Branch( "me_d0", &me_d0);
	tree_allCuts->Branch( "me_z0", &me_z0);
	tree_allCuts->Branch( "me_phi", &me_phi);
	tree_allCuts->Branch( "me_theta", &me_theta);
	tree_allCuts->Branch( "me_qoverp", &me_qoverp);
	tree_allCuts->Branch( "ie_d0", &ie_d0);
	tree_allCuts->Branch( "ie_z0", &ie_z0);
	tree_allCuts->Branch( "ie_phi", &ie_phi);
	tree_allCuts->Branch( "ie_theta", &ie_theta);
	tree_allCuts->Branch( "ie_qoverp", &ie_qoverp);
	tree_allCuts->Branch( "nOutliersOnTrack", &nOutliersOnTrack);
	tree_allCuts->Branch( "nBLHits", &nBLHits);
	tree_allCuts->Branch( "nPixHits", &nPixHits);
	tree_allCuts->Branch( "nSCTHits", &nSCTHits);
	tree_allCuts->Branch( "nTRTHits", &nTRTHits);
	tree_allCuts->Branch( "nTRTHighTHits", &nTRTHighTHits);
	tree_allCuts->Branch( "nBLSharedHits", &nBLSharedHits);
	tree_allCuts->Branch( "nPixSharedHits", &nPixSharedHits);
	tree_allCuts->Branch( "nPixHoles", &nPixHoles);
	tree_allCuts->Branch( "nSCTSharedHits", &nSCTSharedHits);
	tree_allCuts->Branch( "nSCTHoles", &nSCTHoles);
	tree_allCuts->Branch( "nTRTOutliers", &nTRTOutliers);
	tree_allCuts->Branch( "nTRTHighTOutliers", &nTRTHighTOutliers);
	tree_allCuts->Branch( "nGangedPixels", &nGangedPixels);
	tree_allCuts->Branch( "nPixelDeadSensors", &nPixelDeadSensors);
	tree_allCuts->Branch( "nSCTDeadSensors", &nSCTDeadSensors);
	tree_allCuts->Branch( "nTRTDeadStraws", &nTRTDeadStraws);
	tree_allCuts->Branch( "expectBLayerHit", &expectBLayerHit);
	tree_allCuts->Branch( "nMDTHits", &nMDTHits);
	tree_allCuts->Branch( "nMDTHoles", &nMDTHoles);
	tree_allCuts->Branch( "nCSCEtaHits", &nCSCEtaHits);
	tree_allCuts->Branch( "nCSCEtaHoles", &nCSCEtaHoles);
	tree_allCuts->Branch( "nCSCPhiHits", &nCSCPhiHits);
	tree_allCuts->Branch( "nCSCPhiHoles", &nCSCPhiHoles);
	tree_allCuts->Branch( "nRPCEtaHits", &nRPCEtaHits);
	tree_allCuts->Branch( "nRPCEtaHoles", &nRPCEtaHoles);
	tree_allCuts->Branch( "nRPCPhiHits", &nRPCPhiHits);
	tree_allCuts->Branch( "nRPCPhiHoles", &nRPCPhiHoles);
	tree_allCuts->Branch( "nTGCEtaHits", &nTGCEtaHits);
	tree_allCuts->Branch( "nTGCEtaHoles", &nTGCEtaHoles);
	tree_allCuts->Branch( "nTGCPhiHits", &nTGCPhiHits);
	tree_allCuts->Branch( "nTGCPhiHoles", &nTGCPhiHoles);
	tree_allCuts->Branch( "nMDTBIHits", &nMDTBIHits);
	tree_allCuts->Branch( "nMDTBMHits", &nMDTBMHits);
	tree_allCuts->Branch( "nMDTBOHits", &nMDTBOHits);
	tree_allCuts->Branch( "nMDTBEEHits", &nMDTBEEHits);
	tree_allCuts->Branch( "nMDTBIS78Hits", &nMDTBIS78Hits);
	tree_allCuts->Branch( "nMDTEIHits", &nMDTEIHits);
	tree_allCuts->Branch( "nMDTEMHits", &nMDTEMHits);
	tree_allCuts->Branch( "nMDTEOHits", &nMDTEOHits);
	tree_allCuts->Branch( "nMDTEEHits", &nMDTEEHits);
	tree_allCuts->Branch( "nRPCLayer1EtaHits", &nRPCLayer1EtaHits);
	tree_allCuts->Branch( "nRPCLayer2EtaHits", &nRPCLayer2EtaHits);
	tree_allCuts->Branch( "nRPCLayer3EtaHits", &nRPCLayer3EtaHits);
	tree_allCuts->Branch( "nRPCLayer1PhiHits", &nRPCLayer1PhiHits);
	tree_allCuts->Branch( "nRPCLayer2PhiHits", &nRPCLayer2PhiHits);
	tree_allCuts->Branch( "nRPCLayer3PhiHits", &nRPCLayer3PhiHits);
	tree_allCuts->Branch( "nTGCLayer1EtaHits", &nTGCLayer1EtaHits);
	tree_allCuts->Branch( "nTGCLayer2EtaHits", &nTGCLayer2EtaHits);
	tree_allCuts->Branch( "nTGCLayer3EtaHits", &nTGCLayer3EtaHits);
	tree_allCuts->Branch( "nTGCLayer4EtaHits", &nTGCLayer4EtaHits);
	tree_allCuts->Branch( "nTGCLayer1PhiHits", &nTGCLayer1PhiHits);
	tree_allCuts->Branch( "nTGCLayer2PhiHits", &nTGCLayer2PhiHits);
	tree_allCuts->Branch( "nTGCLayer3PhiHits", &nTGCLayer3PhiHits);
	tree_allCuts->Branch( "nTGCLayer4PhiHits", &nTGCLayer4PhiHits);
	tree_allCuts->Branch( "barrelSectors", &barrelSectors);
	tree_allCuts->Branch( "endcapSectors", &endcapSectors);
	tree_allCuts->Branch( "trackd0", &trackd0);
	tree_allCuts->Branch( "trackz0", &trackz0);
	tree_allCuts->Branch( "trackphi", &trackphi);
	tree_allCuts->Branch( "tracktheta", &tracktheta);
	tree_allCuts->Branch( "trackqoverp", &trackqoverp);
	tree_allCuts->Branch( "trackcov_d0", &trackcov_d0);
	tree_allCuts->Branch( "trackcov_z0", &trackcov_z0);
	tree_allCuts->Branch( "trackcov_phi", &trackcov_phi);
	tree_allCuts->Branch( "trackcov_theta", &trackcov_theta);
	tree_allCuts->Branch( "trackcov_qoverp", &trackcov_qoverp);
	tree_allCuts->Branch( "trackcov_d0_z0", &trackcov_d0_z0);
	tree_allCuts->Branch( "trackcov_d0_phi", &trackcov_d0_phi);
	tree_allCuts->Branch( "trackcov_d0_theta", &trackcov_d0_theta);
	tree_allCuts->Branch( "trackcov_d0_qoverp", &trackcov_d0_qoverp);
	tree_allCuts->Branch( "trackcov_z0_phi", &trackcov_z0_phi);
	tree_allCuts->Branch( "trackcov_z0_theta", &trackcov_z0_theta);
	tree_allCuts->Branch( "trackcov_z0_qoverp", &trackcov_z0_qoverp);
	tree_allCuts->Branch( "trackcov_phi_theta", &trackcov_phi_theta);
	tree_allCuts->Branch( "trackcov_phi_qoverp", &trackcov_phi_qoverp);
	tree_allCuts->Branch( "trackcov_theta_qoverp", &trackcov_theta_qoverp);
	tree_allCuts->Branch( "trackfitchi2", &trackfitchi2);
	tree_allCuts->Branch( "trackfitndof", &trackfitndof);
	tree_allCuts->Branch( "hastrack", &hastrack);
	tree_allCuts->Branch( "truth_dr", &truth_dr);
	tree_allCuts->Branch( "truth_E", &truth_E);
	tree_allCuts->Branch( "truth_pt", &truth_pt);
	tree_allCuts->Branch( "truth_eta", &truth_eta);
	tree_allCuts->Branch( "truth_phi", &truth_phi);
	tree_allCuts->Branch( "truth_type", &truth_type);
	tree_allCuts->Branch( "truth_status", &truth_status);
	tree_allCuts->Branch( "truth_barcode", &truth_barcode);
	tree_allCuts->Branch( "truth_mothertype", &truth_mothertype);
	tree_allCuts->Branch( "truth_motherbarcode", &truth_motherbarcode);
	tree_allCuts->Branch( "truth_matched", &truth_matched);
	tree_allCuts->Branch( "EFCB_dr", &EFCB_dr);
	tree_allCuts->Branch( "EFCB_index", &EFCB_index);
	tree_allCuts->Branch( "EFMG_dr", &EFMG_dr);
	tree_allCuts->Branch( "EFMG_index", &EFMG_index);
	tree_allCuts->Branch( "EFME_dr", &EFME_dr);
	tree_allCuts->Branch( "EFME_index", &EFME_index);
	tree_allCuts->Branch( "L2CB_dr", &L2CB_dr);
	tree_allCuts->Branch( "L2CB_index", &L2CB_index);
	tree_allCuts->Branch( "L1_dr", &L1_dr);
	tree_allCuts->Branch( "L1_index", &L1_index);

	
	
	if(tDir_cutsProfile!=NULL) tDir_cutsProfile->cd();
	tree_cutsProfile = new TTree("cutsProfile_tree","cutsProfile_tree");
	tree_cutsProfile->SetDirectory(tDir_cutsProfile);
	// vectors
	tree_cutsProfile->Branch( "vxp_z_profile", &vxp_z_profile );
	tree_cutsProfile->Branch( "vxp_nTracks_profile", &vxp_nTracks_profile );
	tree_cutsProfile->Branch( "pT_profile", &pT_profile );
	tree_cutsProfile->Branch( "pT_loose_profile", &pT_loose_profile );
	tree_cutsProfile->Branch( "pT_qOp_and_theta_profile", &pT_qOp_and_theta_profile );
	tree_cutsProfile->Branch( "pT_qOp_and_theta_loose_profile", &pT_qOp_and_theta_loose_profile );
	tree_cutsProfile->Branch( "eta_profile", &eta_profile );
	tree_cutsProfile->Branch( "etaTight_profile", &etaTight_profile );
	tree_cutsProfile->Branch( "etaBarrel_profile", &etaBarrel_profile );
	tree_cutsProfile->Branch( "etaFwd_profile", &etaFwd_profile );
	tree_cutsProfile->Branch( "etaFull_profile", &etaFull_profile );
	tree_cutsProfile->Branch( "pTmatchingRatio_profile", &pTmatchingRatio_profile );
	tree_cutsProfile->Branch( "pTmatchingAbsDiff_profile", &pTmatchingAbsDiff_profile );
	tree_cutsProfile->Branch( "pTmatchingAbsDiff_profile", &pTmatchingAbsDiff_profile );
	tree_cutsProfile->Branch( "d0_profile", &d0_profile );
	tree_cutsProfile->Branch( "z0_profile", &z0_profile );
	tree_cutsProfile->Branch( "isolation20_profile", &isolation20_profile );
	tree_cutsProfile->Branch( "isolation30_profile", &isolation30_profile );
	tree_cutsProfile->Branch( "isolation40_profile", &isolation40_profile );
	tree_cutsProfile->Branch( "ip_d0_profile", &ip_d0_profile );
	tree_cutsProfile->Branch( "ip_z0_profile", &ip_z0_profile );
	tree_cutsProfile->Branch( "oppositeCharge_profile", &oppositeCharge_profile );
	tree_cutsProfile->Branch( "imass_profile", &imass_profile );
	tree_cutsProfile->Branch( "cosThetaDimu_profile", &cosThetaDimu_profile );
	tree_cutsProfile->Branch( "etaSum_profile", &etaSum_profile );
	tree_cutsProfile->Branch( "nMDTBI_profile", &nMDTBI_profile );
	tree_cutsProfile->Branch( "nMDTBM_profile", &nMDTBM_profile );
	tree_cutsProfile->Branch( "nMDTBO_profile", &nMDTBO_profile );
	tree_cutsProfile->Branch( "nMDTEI_profile", &nMDTEI_profile );
	tree_cutsProfile->Branch( "nMDTEM_profile", &nMDTEM_profile );
	tree_cutsProfile->Branch( "nMDTEO_profile", &nMDTEO_profile );
	tree_cutsProfile->Branch( "nMDTBEE_profile", &nMDTBEE_profile );
	tree_cutsProfile->Branch( "nMDTEE_profile", &nMDTEE_profile );
	tree_cutsProfile->Branch( "nMDTBIS78_profile", &nMDTBIS78_profile );
	tree_cutsProfile->Branch( "nRPCPhi1_profile", &nRPCPhi1_profile );
	tree_cutsProfile->Branch( "nRPCPhi2_profile", &nRPCPhi2_profile );
	tree_cutsProfile->Branch( "nRPCPhi3_profile", &nRPCPhi3_profile );
	tree_cutsProfile->Branch( "nTGCPhi1_profile", &nTGCPhi1_profile );
	tree_cutsProfile->Branch( "nTGCPhi2_profile", &nTGCPhi2_profile );
	tree_cutsProfile->Branch( "nTGCPhi3_profile", &nTGCPhi3_profile );
	tree_cutsProfile->Branch( "nTGCPhi4_profile", &nTGCPhi4_profile );
	tree_cutsProfile->Branch( "nCSCEta_profile", &nCSCEta_profile );
	tree_cutsProfile->Branch( "nCSCPhi_profile", &nCSCPhi_profile );
	tree_cutsProfile->Branch( "expectBLayerHit_profile", &expectBLayerHit_profile );
	tree_cutsProfile->Branch( "nBLHits_profile", &nBLHits_profile );
	tree_cutsProfile->Branch( "nPixHits_profile", &nPixHits_profile );
	tree_cutsProfile->Branch( "nPixelDeadSensors_profile", &nPixelDeadSensors_profile );
	tree_cutsProfile->Branch( "nPixHoles_profile", &nPixHoles_profile );
	tree_cutsProfile->Branch( "nSCTHits_profile", &nSCTHits_profile );
	tree_cutsProfile->Branch( "nSCTDeadSensors_profile", &nSCTDeadSensors_profile );
	tree_cutsProfile->Branch( "nSCTHoles_profile", &nSCTHoles_profile );
	tree_cutsProfile->Branch( "nTRTHits_profile", &nTRTHits_profile );
	tree_cutsProfile->Branch( "nTRTOutliers_profile", &nTRTOutliers_profile );
	tree_cutsProfile->Branch( "eta_forTRThits_profile", &eta_forTRThits_profile );
	
	
	if(tDir_efficiency!=NULL) tDir_efficiency->cd();
	tree_efficiency = new TTree("eff_tree","eff_tree");
	tree_efficiency->SetDirectory(tDir_efficiency);
	tree_efficiency->Branch( "tNp_triggerName",  &tNp_triggerName );
	tree_efficiency->Branch( "tru_triggerName",  &tru_triggerName );
	tree_efficiency->Branch( "tNp_cand_pT",  &tNp_cand_pT );
	tree_efficiency->Branch( "tNp_succ_pT",  &tNp_succ_pT );
	tree_efficiency->Branch( "tNp_cand_eta", &tNp_cand_eta );
	tree_efficiency->Branch( "tNp_succ_eta", &tNp_succ_eta );
	tree_efficiency->Branch( "tNp_cand_phi", &tNp_cand_phi );
	tree_efficiency->Branch( "tNp_succ_phi", &tNp_succ_phi );
	tree_efficiency->Branch( "tru_cand_pT",  &tru_cand_pT );
	tree_efficiency->Branch( "tru_succ_pT",  &tru_succ_pT );
	tree_efficiency->Branch( "tru_cand_eta", &tru_cand_eta );
	tree_efficiency->Branch( "tru_succ_eta", &tru_succ_eta );
	tree_efficiency->Branch( "tru_cand_phi", &tru_cand_phi );
	tree_efficiency->Branch( "tru_succ_phi", &tru_succ_phi );
}

void graphicObjects::setTrees(TDirectory* tDir_allCuts,
							  TDirectory* tDir_cutsProfile,
							  TDirectory* tDir_efficiency,
							  TDirectory* tDir_truth)
{
	setTrees(tDir_allCuts, tDir_cutsProfile, tDir_efficiency);
	
	truth_all_dr = new vector<float>;
	truth_all_E = new vector<float>;
	truth_all_pt = new vector<float>;
	truth_all_eta = new vector<float>;
	truth_all_phi = new vector<float>;
	truth_all_type = new vector<int>;
	truth_all_status = new vector<int>;
	truth_all_barcode = new vector<int>;
	truth_all_mothertype = new vector<int>;
	truth_all_motherbarcode = new vector<int>;
	truth_all_matched = new vector<int>;
	
	recon_all_E = new vector<float>;
	recon_all_pt = new vector<float>;
	recon_all_m = new vector<float>;
	recon_all_eta = new vector<float>;
	recon_all_phi = new vector<float>;
	recon_all_px = new vector<float>;
	recon_all_py = new vector<float>;
	recon_all_pz = new vector<float>;
	recon_all_charge = new vector<float>;
	recon_all_y = new vector<float>;
	recon_all_id = new vector<int>;
	recon_all_theta = new vector<float>;
	
	
	// muonTruth
	truth_all_muonTruth_pt = new vector<float>;
	truth_all_muonTruth_m = new vector<float>;
	truth_all_muonTruth_eta = new vector<float>;
	truth_all_muonTruth_phi = new vector<float>;
	truth_all_muonTruth_charge = new vector<float>;
	truth_all_muonTruth_PDGID = new vector<int>;
	truth_all_muonTruth_barcode = new vector<int>;
	truth_all_muonTruth_type = new vector<int>;
	truth_all_muonTruth_origin = new vector<int>;
	// MC event
	truth_all_mcevt_signal_process_id = new vector<int>;
	truth_all_mcevt_event_number = new vector<int>;
	truth_all_mcevt_event_scale = new vector<double>;
	truth_all_mcevt_alphaQCD = new vector<double>;
	truth_all_mcevt_alphaQED = new vector<double>;
	truth_all_mcevt_pdf_id1 = new vector<int>;
	truth_all_mcevt_pdf_id2 = new vector<int>;
	truth_all_mcevt_pdf_x1 = new vector<double>;
	truth_all_mcevt_pdf_x2 = new vector<double>;
	truth_all_mcevt_pdf_scale = new vector<double>;
	truth_all_mcevt_pdf1 = new vector<double>;
	truth_all_mcevt_pdf2 = new vector<double>;
	truth_all_mcevt_weight = new vector<double>;
	//MC
	truth_all_mc_pt = new vector<float>;
	truth_all_mc_m = new vector<float>;
	truth_all_mc_eta = new vector<float>;
	truth_all_mc_phi = new vector<float>;
	truth_all_mc_status = new vector<int>;
	truth_all_mc_barcode = new vector<int>;
	truth_all_mc_pdgId = new vector<int>;
	truth_all_mc_charge = new vector<float>;
	
	// partons
	truth_all_partons_mc_pt = new vector<float>;
	truth_all_partons_mc_m = new vector<float>;
	truth_all_partons_mc_eta = new vector<float>;
	truth_all_partons_mc_phi = new vector<float>;
	truth_all_partons_mc_status = new vector<int>;
	truth_all_partons_mc_barcode = new vector<int>;
	truth_all_partons_mc_pdgId = new vector<int>;
	truth_all_partons_mc_charge = new vector<float>;
	
	truth_all_vKKwgt = new vector<double>;
	truth_all_vZPwgt = new vector<double>;
	truth_all_vBSMmass = new vector<double>;
	
	if(tDir_truth!=NULL) tDir_truth->cd();
	tree_truth = new TTree("truth_tree","truth_tree");
	tree_truth->SetDirectory(tDir_truth);
	
	tree_truth->Branch( "all_actualIntPerXing",  &all_actualIntPerXing );
	tree_truth->Branch( "all_averageIntPerXing", &all_averageIntPerXing );
	tree_truth->Branch( "all_mc_channel_number", &all_mc_channel_number );
	tree_truth->Branch( "all_mc_event_number",   &all_mc_event_number );
	tree_truth->Branch( "all_mc_event_weight",   &all_mc_event_weight );
	
	tree_truth->Branch( "all_RunNumber",  &all_RunNumber );
	tree_truth->Branch( "all_pileup_weight",  &all_pileup_weight );
	tree_truth->Branch( "all_intime_pileup_weight", &all_intime_pileup_weight );
	tree_truth->Branch( "all_outoftime_pileup_weight", &all_outoftime_pileup_weight );
	tree_truth->Branch( "all_lumi_pileup_weight", &all_lumi_pileup_weight );
	tree_truth->Branch( "all_EW_kfactor_weight", &all_EW_kfactor_weight );
	tree_truth->Branch( "all_QCD_kfactor_weight", &all_QCD_kfactor_weight );
	tree_truth->Branch( "all_mcevent_weight", &all_mcevent_weight );
	tree_truth->Branch( "all_total_weight",   &all_total_weight );
	tree_truth->Branch( "all_randomized_decision",   &all_randomized_decision );
	
	tree_truth->Branch( "all_vxp_n",   &all_vxp_n );
	
	tree_truth->Branch( "truth_all_isValid",  &truth_all_isValid );
	tree_truth->Branch( "truth_all_dr",  &truth_all_dr );
	tree_truth->Branch( "truth_all_E",  &truth_all_E );
	tree_truth->Branch( "truth_all_pt",  &truth_all_pt );
	tree_truth->Branch( "truth_all_eta",  &truth_all_eta );
	tree_truth->Branch( "truth_all_phi", &truth_all_phi );
	tree_truth->Branch( "truth_all_type", &truth_all_type );
	tree_truth->Branch( "truth_all_status", &truth_all_status );
	tree_truth->Branch( "truth_all_barcode", &truth_all_barcode );
	tree_truth->Branch( "truth_all_mothertype",  &truth_all_mothertype );
	tree_truth->Branch( "truth_all_motherbarcode",  &truth_all_motherbarcode );
	tree_truth->Branch( "truth_all_matched", &truth_all_matched );
	
	// muonTruth
	tree_truth->Branch( "truth_all_muonTruth_pt", &truth_all_muonTruth_pt );
	tree_truth->Branch( "truth_all_muonTruth_m", &truth_all_muonTruth_m );
	tree_truth->Branch( "truth_all_muonTruth_eta", &truth_all_muonTruth_eta );
	tree_truth->Branch( "truth_all_muonTruth_phi", &truth_all_muonTruth_phi );
	tree_truth->Branch( "truth_all_muonTruth_charge", &truth_all_muonTruth_charge );
	tree_truth->Branch( "truth_all_muonTruth_PDGID", &truth_all_muonTruth_PDGID );
	tree_truth->Branch( "truth_all_muonTruth_barcode", &truth_all_muonTruth_barcode );
	tree_truth->Branch( "truth_all_muonTruth_type", &truth_all_muonTruth_type );
	tree_truth->Branch( "truth_all_muonTruth_origin", &truth_all_muonTruth_origin );
	// MC event
	tree_truth->Branch( "truth_all_mcevt_signal_process_id", &truth_all_mcevt_signal_process_id );
	tree_truth->Branch( "truth_all_mcevt_event_number", &truth_all_mcevt_event_number );
	tree_truth->Branch( "truth_all_mcevt_event_scale", &truth_all_mcevt_event_scale );
	tree_truth->Branch( "truth_all_mcevt_alphaQCD", &truth_all_mcevt_alphaQCD );
	tree_truth->Branch( "truth_all_mcevt_alphaQED", &truth_all_mcevt_alphaQED );
	tree_truth->Branch( "truth_all_mcevt_pdf_id1", &truth_all_mcevt_pdf_id1 );
	tree_truth->Branch( "truth_all_mcevt_pdf_id2", &truth_all_mcevt_pdf_id2 );
	tree_truth->Branch( "truth_all_mcevt_pdf_x1", &truth_all_mcevt_pdf_x1 );
	tree_truth->Branch( "truth_all_mcevt_pdf_x2", &truth_all_mcevt_pdf_x2 );
	tree_truth->Branch( "truth_all_mcevt_pdf_scale", &truth_all_mcevt_pdf_scale );
	tree_truth->Branch( "truth_all_mcevt_pdf1", &truth_all_mcevt_pdf1 );
	tree_truth->Branch( "truth_all_mcevt_pdf2", &truth_all_mcevt_pdf2 );
	tree_truth->Branch( "truth_all_mcevt_weight", &truth_all_mcevt_weight );
	//MC
	tree_truth->Branch( "truth_all_mc_vxp_n", &truth_all_mc_vxp_n );
	tree_truth->Branch( "truth_all_mc_pt", &truth_all_mc_pt );
	tree_truth->Branch( "truth_all_mc_m", &truth_all_mc_m );
	tree_truth->Branch( "truth_all_mc_eta", &truth_all_mc_eta );
	tree_truth->Branch( "truth_all_mc_phi", &truth_all_mc_phi );
	tree_truth->Branch( "truth_all_mc_status", &truth_all_mc_status );
	tree_truth->Branch( "truth_all_mc_barcode", &truth_all_mc_barcode );
	tree_truth->Branch( "truth_all_mc_pdgId", &truth_all_mc_pdgId );
	tree_truth->Branch( "truth_all_mc_charge", &truth_all_mc_charge );
	
	tree_truth->Branch( "truth_all_Mhat", &truth_all_Mhat );
	tree_truth->Branch( "truth_all_CosThetaCS", &truth_all_CosThetaCS );
	tree_truth->Branch( "truth_all_CosThetaHE", &truth_all_CosThetaHE );
	tree_truth->Branch( "truth_all_ySystem", &truth_all_ySystem );
	tree_truth->Branch( "truth_all_QT", &truth_all_QT );
	tree_truth->Branch( "truth_all_betaQ", &truth_all_betaQ );
	tree_truth->Branch( "truth_all_betazQ", &truth_all_betazQ );
	tree_truth->Branch( "truth_all_betaTQ", &truth_all_betaTQ );
	
	// partons
	tree_truth->Branch( "truth_all_partons_mc_pt", &truth_all_partons_mc_pt);
	tree_truth->Branch( "truth_all_partons_mc_m", &truth_all_partons_mc_m);
	tree_truth->Branch( "truth_all_partons_mc_eta", &truth_all_partons_mc_eta);
	tree_truth->Branch( "truth_all_partons_mc_phi", &truth_all_partons_mc_phi);
	tree_truth->Branch( "truth_all_partons_mc_status", &truth_all_partons_mc_status);
	tree_truth->Branch( "truth_all_partons_mc_barcode", &truth_all_partons_mc_barcode);
	tree_truth->Branch( "truth_all_partons_mc_pdgId", &truth_all_partons_mc_pdgId);
	tree_truth->Branch( "truth_all_partons_mc_charge", &truth_all_partons_mc_charge);
	
	tree_truth->Branch( "truth_all_vKKwgt", &truth_all_vKKwgt);
	tree_truth->Branch( "truth_all_vZPwgt", &truth_all_vZPwgt);
	tree_truth->Branch( "truth_all_vBSMmass", &truth_all_vBSMmass);
	
	tree_truth->Branch( "recon_all_isValid",  &recon_all_isValid );
	tree_truth->Branch( "recon_all_vxp_n",  &recon_all_vxp_n );
	tree_truth->Branch( "recon_all_E", &recon_all_E );
	tree_truth->Branch( "recon_all_pt", &recon_all_pt );
	tree_truth->Branch( "recon_all_m", &recon_all_m );
	tree_truth->Branch( "recon_all_eta", &recon_all_eta );
	tree_truth->Branch( "recon_all_phi", &recon_all_phi );
	tree_truth->Branch( "recon_all_px", &recon_all_px );
	tree_truth->Branch( "recon_all_py", &recon_all_py );
	tree_truth->Branch( "recon_all_pz", &recon_all_pz );
	tree_truth->Branch( "recon_all_charge", &recon_all_charge );
	tree_truth->Branch( "recon_all_y", &recon_all_y );
	tree_truth->Branch( "recon_all_id", &recon_all_id );
	tree_truth->Branch( "recon_all_theta", &recon_all_theta );
	tree_truth->Branch( "recon_all_Mhat", &recon_all_Mhat );
	tree_truth->Branch( "recon_all_CosThetaCS", &recon_all_CosThetaCS );
	tree_truth->Branch( "recon_all_CosThetaHE", &recon_all_CosThetaHE );
	tree_truth->Branch( "recon_all_ySystem", &recon_all_ySystem );
	tree_truth->Branch( "recon_all_QT", &recon_all_QT );
	tree_truth->Branch( "recon_all_betaQ", &recon_all_betaQ );
	tree_truth->Branch( "recon_all_betazQ", &recon_all_betazQ );
	tree_truth->Branch( "recon_all_betaTQ", &recon_all_betaTQ );
}


void graphicObjects::setCutFlowMapSVDPtr(TMapsvd* cutFlowMapSVD)
{
	cut_cutFlowMapSVD = cutFlowMapSVD;
}

void graphicObjects::ginitialize()
{
	// canvas size
	canv_x = 602;
	canv_y = 400;

	// legend size
	leg_x1 = 0.765;
	leg_x2 = 0.919;
	leg_y1 = 0.376;
	leg_y2 = 0.922;

	// get the cut value from the cutFlow map
	string pTcutNmae;
	TMapsvd::iterator it1=cut_cutFlowMapSVD->find("pT");
	TMapsvd::iterator it2=cut_cutFlowMapSVD->find("pTloose");
	TMapsvd::iterator itEnd=cut_cutFlowMapSVD->end();
	if     ( it1 != itEnd ) pTcutNmae = "pT";
	else if( it2 != itEnd ) pTcutNmae = "pTloose";
	else
	{
		_ERROR("in graphicObjects::ginitialize(): pT cut value was not found, exitting now");
		exit(-1);
	}
	double pT_cut    = (*cut_cutFlowMapSVD)[pTcutNmae][0];
	double imass_cut = (*cut_cutFlowMapSVD)["imass"][0];
	
	
	imass_nbins   = 100;
	imass_min     = 10.*GeV2TeV;
	imass_min_cut = imass_cut;
	imass_max     = 2010.*GeV2TeV;
	imass_max_cut = 2000.*GeV2TeV+imass_cut;
	
	imass_fit_nbins = 200;
	imass_fit_min   = 0.*GeV2TeV;
	imass_fit_max   = 200.*GeV2TeV;
	
	pT_nbins    = 100;
	pT_min      = 5.*GeV2TeV;
	pT_min_cut  = pT_cut;
	pT_max      = 2005.*GeV2TeV;
	pT_max_cut  = 2000.*GeV2TeV+pT_cut;

	// logarithmic boundries and bins of histograms
	logMmin = log10(imass_min);
	logMmin_cut = log10(imass_min_cut);
	logMmax = log10(imass_max);
	logMmax_cut = log10(imass_max_cut);
	M_binwidth = (Double_t)( (logMmax-logMmin)/(Double_t)imass_nbins );
	M_binwidth_cut = (Double_t)( (logMmax_cut-logMmin_cut)/(Double_t)imass_nbins );
	M_bins[0] = imass_min;
	M_bins_cut[0] = imass_min_cut;
	for (Int_t i=1 ; i<=imass_nbins ; i++)
	{ 
		M_bins[i] = TMath::Power( 10,(logMmin + i*M_binwidth) );
		M_bins_cut[i] = TMath::Power( 10,(logMmin_cut + i*M_binwidth_cut) );
	}
	
	logpTmin = log10(pT_min);
	logpTmin_cut = log10(pT_min_cut);
	logpTmax = log10(pT_max);
	logpTmax_cut = log10(pT_max_cut);
	pT_binwidth = (Double_t)( (logpTmax-logpTmin)/(Double_t)pT_nbins );
	pT_binwidth_cut = (Double_t)( (logpTmax_cut-logpTmin_cut)/(Double_t)pT_nbins );
	pT_bins[0] = pT_min;
	pT_bins_cut[0] = pT_min_cut;
	for (Int_t i=1 ; i<=pT_nbins ; i++)
	{
		pT_bins[i] = TMath::Power( 10,(logpTmin + i*pT_binwidth) );
		pT_bins_cut[i] = TMath::Power( 10,(logpTmin_cut + i*pT_binwidth_cut) );
	}
	
	phi_nbins   = 10;
	phi_min     = -pi;
	phi_max     = +pi;
	
	eta_nbins   = 50;
	eta_min     = -3.;
	eta_max     = 3.;

	costh_nbins = 10;
	costh_min   = -1.;
	costh_max   = 1.;

	d0exPV_nbins = 50;
	d0exPV_min   = -300.;
	d0exPV_max   = 300.;

	z0exPV_nbins = 50;
	z0exPV_min   = -300.;
	z0exPV_max   = 300.;

	cosmicCosth_nbins = 200;
	cosmicCosth_min   = -1.;
	cosmicCosth_max   = 1.;

	xyVertex_nbins = 40;
	xyVertex_min   = -200.;
	xyVertex_max   = 200.;
	
	ipTdiff_nbins = 50;
	ipTdiff_min   = -1./(20.*GeV2TeV);
	ipTdiff_max   = +1./(20.*GeV2TeV);
	
	etaSum_nbins = 50;;
	etaSum_min   = -5.;
	etaSum_max   = +5.;
	
	pTdiff_nbins = 100;
	pTdiff_min   = -50.*GeV2TeV;
	pTdiff_max   = +50.*GeV2TeV;
	
	pTratio_nbins = 120;
	pTratio_min   = 0.;
	pTratio_max   = 3.;
	
	pTmevspTid_nbins = 100;
	pTmevspTid_min   = 0.*GeV2TeV;
	pTmevspTid_max   = 500.*GeV2TeV;
	
	pTres_nbins = 100;
	pTres_min   = -2;
	pTres_max   = +2;
	
	Afb_nbins = 40;
	Afb_min   = 60.*GeV2TeV;
	Afb_max   = 460.*GeV2TeV;
	
	tagNprobe_pT_nbins = 16;
	tagNprobe_pT_min   = 0.*MeV2GeV;
	tagNprobe_pT_max   = 100.*MeV2GeV;
}

void graphicObjects::setStyle(TString dir)
{
	gROOT->ProcessLine(".x "+dir+"/rootlogon_atlas.C"); // if in tmp
	gROOT->SetStyle("ATLAS");
	gROOT->ForceStyle();
}

void graphicObjects::bookBareHistos(TDirectory* tdir)
{
	if(tdir!=NULL) tdir->cd();

	h1_d0exPV = new TH1D("d0exPV","d0exPV", d0exPV_nbins, d0exPV_min, d0exPV_max);
	h1_z0exPV = new TH1D("z0exPV","z0exPV", z0exPV_nbins, z0exPV_min, z0exPV_max);
	
	h1_cosmicCosth = new TH1D("cosThetaDimu","cosThetaDimu", cosmicCosth_nbins, cosmicCosth_min, cosmicCosth_max);
	h1_cosmicCosthAllCuts = new TH1D("cosThetaDimuAllCuts","cosThetaDimuAllCuts", cosmicCosth_nbins, cosmicCosth_min, cosmicCosth_max);
	
	h2_xyVertex = new TH2D("xyVertex","xyVertex", xyVertex_nbins, xyVertex_min, xyVertex_max, xyVertex_nbins, xyVertex_min, xyVertex_max);
}

void graphicObjects::bookHistos(TDirectory* tdir)
{
	if(tdir!=NULL) tdir->cd();

	h1_imass = new TH1D("imass","imass", imass_nbins, M_bins_cut);
	//h1_imass = new TH1D("imass","imass", imass_nbins, M_bins);
	//h1_imass = new TH1D("imass","imass", imass_nbins, imass_min, imass_max);
	h1_ipTdiff = new TH1D("ipTdiff","ipTdiff", ipTdiff_nbins, ipTdiff_min, ipTdiff_max);
	h1_etaSum = new TH1D("etaSum","etaSum", etaSum_nbins, etaSum_min, etaSum_max);
	h1_pT = new TH1D("pT","pT", pT_nbins, pT_bins_cut);
	//h1_pT = new TH1D("pT","pT", pT_nbins, pT_bins);
	//h1_pT = new TH1D("pT","pT", pT_nbins, pT_min, pT_max);
	h1_pT_muplus = new TH1D("pT #mu^{+}","pT #mu^{+}", pT_nbins, pT_bins_cut);
	//h1_pT_muplus = new TH1D("pT #mu^{+}","pT #mu^{+}", pT_nbins, pT_bins);
	//h1_pT_muplus = new TH1D("pT #mu^{+}","pT #mu^{+}", pT_nbins, pT_min, pT_max);
	h1_eta = new TH1D("eta","eta", eta_nbins, eta_min, eta_max);
	h1_eta_muplus = new TH1D("eta #mu^{+}","eta #mu^{+}", eta_nbins, eta_min, eta_max);
	h1_costh = new TH1D("costh","costh", costh_nbins, costh_min, costh_max);
	

	h1_pTdiff = new TH1D("pTdiff_mu-", "pTdiff_mu-", pTdiff_nbins, pTdiff_min, pTdiff_max);
	h1_pTratio = new TH1D("pTratio_mu-", "pTratio_mu-", pTratio_nbins, pTratio_min, pTratio_max);
	h1_pTres = new TH1D("pTres_mu-", "pTres_mu-", pTres_nbins, pTres_min, pTres_max);
	h2_pTmevspTid = new TH2D("pTmevspTid_mu-", "pTmevspTid_mu-", pTmevspTid_nbins,pTmevspTid_min,pTmevspTid_max, pTmevspTid_nbins,pTmevspTid_min,pTmevspTid_max);
	h1_pTdiff_muplus = new TH1D("pTdiff_mu+", "pTdiff_mu+", pTdiff_nbins, pTdiff_min, pTdiff_max);
	h1_pTratio_muplus = new TH1D("pTratio_mu+", "pTratio_mu+", pTratio_nbins, pTratio_min, pTratio_max);
	h1_pTres_muplus = new TH1D("pTres_mu+", "pTres_mu+", pTres_nbins, pTres_min, pTres_max);
	h2_pTmevspTid_muplus = new TH2D("pTmevspTid_mu+", "pTmevspTid_mu+", pTmevspTid_nbins,pTmevspTid_min,pTmevspTid_max, pTmevspTid_nbins,pTmevspTid_min,pTmevspTid_max);
	
	
	
	h1_Afb = new TH1D("Afb","Afb",Afb_nbins,Afb_min,Afb_max);
}

void graphicObjects::drawPerformance(vector<int>& vEntries, vector<double>& vResMemory, vector<double>& vVirMemory, TDirectory* tdir)
{
	if(tdir!=NULL) tdir->cd();
	
	nentries = (Int_t)vEntries.size();
	resMemoryArray = (Double_t*)malloc(nentries*sizeof(Double_t));
	virMemoryArray = (Double_t*)malloc(nentries*sizeof(Double_t));
	entryArray     = (Double_t*)malloc(nentries*sizeof(Double_t));
	for(Int_t i=0 ; i<nentries ; i++)
	{
		resMemoryArray[i] = (Double_t)vResMemory[i];
		virMemoryArray[i] = (Double_t)vVirMemory[i];
		entryArray[i]     = (Double_t)vEntries[i];
	}
	
	cMemoryMonitor = new TCanvas("memory","memory",canv_x,canv_y);
	cMemoryMonitor->Draw();
	cMemoryMonitor->cd();
	
	gVirMemoryMonitor = new TGraph (nentries, entryArray, virMemoryArray);
	gVirMemoryMonitor->SetTitle("");
	gVirMemoryMonitor->SetLineStyle(3);
	gVirMemoryMonitor->SetLineColor(kBlue);
	gVirMemoryMonitor->GetXaxis()->SetTitle("entry");
	gVirMemoryMonitor->GetYaxis()->SetTitle("memory");
	gVirMemoryMonitor->SetMinimum(0.);
	gVirMemoryMonitor->Draw("AC");
	
	gResMemoryMonitor = new TGraph (nentries, entryArray, resMemoryArray);
	gResMemoryMonitor->SetTitle("");
	gResMemoryMonitor->SetLineStyle(1);
	gResMemoryMonitor->SetLineColor(kRed); 
	gResMemoryMonitor->Draw("C");
	
	leg_memory = new TLegend(leg_x1, leg_y1, leg_x2, leg_y2*2./3.);
	leg_memory->AddEntry( gVirMemoryMonitor, "VIRT", "L");
	leg_memory->AddEntry( gResMemoryMonitor, "RES", "L");
	leg_memory->Draw("sames");
	
	cMemoryMonitor->Update();
	cMemoryMonitor->SaveAs("memory.png");
	cMemoryMonitor->Write();
}

void graphicObjects::drawBareHistos(TDirectory* tdir)
{
	if(tdir!=NULL) tdir->cd();
	
	cnv_d0exPV = new TCanvas("d0exPV","d0exPV",canv_x,canv_y);
	cnv_d0exPV->SetLogy();
	cnv_d0exPV->Draw();
	cnv_d0exPV->cd();
	h1_d0exPV->Draw();
	cnv_d0exPV->Update();
	cnv_d0exPV->Write();

	cnv_z0exPV = new TCanvas("z0exPV","z0exPV",canv_x,canv_y);
	cnv_z0exPV->SetLogy();
	cnv_z0exPV->Draw();
	cnv_z0exPV->cd();
	h1_z0exPV->Draw();
	cnv_z0exPV->Update();
	cnv_z0exPV->Write();

	cnv_cosmicCosth = new TCanvas("cosThetaDimu","cosThetaDimu",canv_x,canv_y);
	cnv_cosmicCosth->Divide(1,2);
	pad_cosmicCosth = cnv_cosmicCosth->cd(1);
	pad_cosmicCosthAllCuts = cnv_cosmicCosth->cd(2);
	cnv_cosmicCosth->Draw();
	cnv_cosmicCosth->cd();
	pad_cosmicCosth->cd();
	h1_cosmicCosth->Draw();
	pad_cosmicCosthAllCuts->cd();
	h1_cosmicCosthAllCuts->Draw();
	cnv_cosmicCosth->Update();
	cnv_cosmicCosth->Write();

	cnv_xyVertex = new TCanvas("xyVertex","xyVertex",canv_x,canv_y);
	cnv_xyVertex->Draw();
	cnv_xyVertex->cd();
	h2_xyVertex->Draw("BOX");
	cnv_xyVertex->Update();
	cnv_xyVertex->Write();
}

void graphicObjects::drawHistos(TDirectory* tdir)
{
	if(tdir!=NULL) tdir->cd();

	cnv_imass = new TCanvas("imass","imass",canv_x,canv_y);
	cnv_imass->SetLogy();
	cnv_imass->Draw();
	cnv_imass->cd();
	h1_imass->Draw();
	cnv_imass->Update();
	cnv_imass->Write();

	cnv_pT = new TCanvas("pT","pT",canv_x,canv_y);
	cnv_pT->Divide(1,2);
	pad_pT = cnv_pT->cd(1);
	pad_pT->SetLogy();
	pad_pT_muplus = cnv_pT->cd(2);
	pad_pT_muplus->SetLogy();
	cnv_pT->Draw();
	cnv_pT->cd();
	pad_pT->cd();
	h1_pT->Draw();
	pad_pT_muplus->cd();
	h1_pT_muplus->Draw();
	cnv_pT->Update();
	cnv_pT->Write();

	cnv_eta = new TCanvas("eta","eta",canv_x,canv_y);
	cnv_eta->Divide(1,2);
	pad_eta = cnv_eta->cd(1);
	pad_eta_muplus = cnv_eta->cd(2);
	cnv_eta->Draw();
	pad_eta->cd();
	h1_eta->Draw();
	pad_eta_muplus->cd();
	h1_eta_muplus->Draw();
	cnv_eta->Update();
	cnv_eta->Write();

	cnv_costh = new TCanvas("costh","costh",canv_x,canv_y);
	cnv_costh->Draw();
	cnv_costh->cd();
	h1_costh->Draw();
	cnv_costh->Update();
	cnv_costh->Write();
	
	cnv_ipTdiff = new TCanvas("ipTdiff","ipTdiff",canv_x,canv_y);
	cnv_ipTdiff->Draw();
	cnv_ipTdiff->cd();
	h1_ipTdiff->SetXTitle("1/p_{T}^{#mu+} - 1/p_{T}^{#mu-} (1/TeV)");
	h1_ipTdiff->Draw("e1x0");
	//-------------------------------------------------------------------------
	TF1* f = new TF1("Lorentzian",Lorentzian,ipTdiff_min,ipTdiff_max, 3);
	f->SetParameters(0,h1_ipTdiff->GetMaximum());
	f->SetParLimits(0,0,h1_ipTdiff->GetEntries());
	f->SetParameters(1,1./(200.*GeV2TeV));
	f->SetParLimits(1,1./(2000.*GeV2TeV),1./(20.*GeV2TeV));
	f->SetParameters(2,0.);
	f->SetParLimits(2,0.1*ipTdiff_min,0.1*ipTdiff_max);
	h1_ipTdiff->Fit(f,"VN","",0.8*ipTdiff_min,0.8*ipTdiff_max);
	cout << "ipTdiff Lorentzian fit :: norm = " << f->GetParameter(0) << " +/- " << f->GetParError(0) << endl;
	cout << "ipTdiff Lorentzian fit :: widt = " << f->GetParameter(1) << " +/- " << f->GetParError(1) << endl;
	cout << "ipTdiff Lorentzian fit :: mean = " << f->GetParameter(2) << " +/- " << f->GetParError(2) << endl;
	cout << "ipTdiff Lorentzian fit :: Chi2 = " << f->GetChisquare() << endl;
	cout << "ipTdiff Lorentzian fit :: NDF  = " << f->GetNDF() << endl;
	cout << "ipTdiff Lorentzian fit :: yield = " << f->GetParameter(0)/h1_ipTdiff->GetBinWidth(1) << " +/- " << f->GetParError(0)/h1_ipTdiff->GetBinWidth(1) << endl;
	f->SetLineColor(kBlue);
	f->Draw("sames");
	leg_ipTdiff = new TLegend(leg_x1*0.8, leg_y1*2., leg_x2, leg_y2);
	leg_ipTdiff->AddEntry( h1_ipTdiff, "Data", "lep");
	leg_ipTdiff->AddEntry( f, "#chi^{2} fit = Lorentzian", "L");
	leg_ipTdiff->Draw("sames");
	//-------------------------------------------------------------------------
	cnv_ipTdiff->Update();
	cnv_ipTdiff->Write();
	
	cnv_etaSum = new TCanvas("etaSum","etaSum",canv_x,canv_y);
	cnv_etaSum->Draw();
	cnv_etaSum->cd();
	h1_etaSum->Draw();
	cnv_etaSum->Update();
	cnv_etaSum->Write();
	
	cnv_pTdiff = new TCanvas("pTdiff","pTdiff",canv_x,canv_y);
	cnv_pTdiff->Divide(1,2);
	pad_pTdiff = cnv_pTdiff->cd(1);
	pad_pTdiff_muplus = cnv_pTdiff->cd(2);
	cnv_pTdiff->Draw();
	pad_pTdiff->cd();
	h1_pTdiff->Draw();
	pad_pTdiff_muplus->cd();
	h1_pTdiff_muplus->Draw();
	cnv_pTdiff->Update();
	cnv_pTdiff->Write();
	
	cnv_pTratio = new TCanvas("pTratio","pTratio",canv_x,canv_y);
	cnv_pTratio->Divide(1,2);
	pad_pTratio = cnv_pTratio->cd(1);
	pad_pTratio_muplus = cnv_pTratio->cd(2);
	cnv_pTratio->Draw();
	pad_pTratio->cd();
	h1_pTratio->Draw();
	pad_pTratio_muplus->cd();
	h1_pTratio_muplus->Draw();
	cnv_pTratio->Update();
	cnv_pTratio->Write();
	
	cnv_pTres = new TCanvas("pTres","pTres",canv_x,canv_y);
	cnv_pTres->Divide(1,2);
	pad_pTres = cnv_pTres->cd(1);
	pad_pTres_muplus = cnv_pTres->cd(2);
	cnv_pTres->Draw();
	pad_pTres->cd();
	h1_pTres->Draw();
	pad_pTres_muplus->cd();
	h1_pTres_muplus->Draw();
	cnv_pTres->Update();
	cnv_pTres->Write();
	
	cnv_pTmevspTid = new TCanvas("pTmevspTid","pTmevspTid",canv_x,canv_y);
	cnv_pTmevspTid->Divide(1,2);
	pad_pTmevspTid = cnv_pTmevspTid->cd(1);
	pad_pTmevspTid_muplus = cnv_pTmevspTid->cd(2);
	cnv_pTmevspTid->Draw();
	pad_pTmevspTid->cd();
	h2_pTmevspTid->Draw("BOX");
	pad_pTmevspTid_muplus->cd();
	h2_pTmevspTid_muplus->Draw("BOX");
	cnv_pTmevspTid->Update();
	cnv_pTmevspTid->Write();
	
	cnv_Afb = new TCanvas("Afb","Afb",canv_x,canv_y);
	cnv_Afb->Draw();
	cnv_Afb->cd();
	h1_Afb->SetTitle("");
	h1_Afb->SetMinimum(-1.1);
	h1_Afb->SetMaximum(+1.1);
	h1_Afb->SetXTitle("#hat{m}_{#mu#mu} TeV");
	h1_Afb->SetYTitle("A_{FB}");
	h1_Afb->Draw("e1x0");
	cnv_Afb->Update();
	cnv_Afb->Write();
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *



void graphicObjects::bookHistosMap(TMapds* cutFlowOrdered, TMapds* cutFlowTypeOrdered, TDirectory* tdir)
{
	if(tdir==NULL) return;

	tdir->cd();

	hmap_cutFlow_imass = new TMapSP2TH1D();
	hmap_cutFlow_pT    = new TMapSP2TH1D();

	for(TMapds::iterator it=cutFlowOrdered->begin() ; it!=cutFlowOrdered->end() ; ++it)
	{
		double snumber = it->first;
		
		///////////////////////////////////////////////////////////////
		// ignore preselection: ///////////////////////////////////////
		if(cutFlowTypeOrdered->operator[](snumber)=="preselection") continue; /////
		///////////////////////////////////////////////////////////////

		string sname = "";

		// invariant mass cut flow histos
		sname = "imass." + it->second;
		//hmap_cutFlow_imass->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), imass_nbins, imass_min, imass_max) ) );
		hmap_cutFlow_imass->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), imass_nbins, M_bins) ) );
		cout << "(" << snumber << ") booked " << sname << endl;

		// pT cut flow histos
		sname = "pT." + it->second;
		//hmap_cutFlow_pT->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), pT_nbins, pT_min, pT_max) ) );
		hmap_cutFlow_pT->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), pT_nbins, pT_bins) ) );
		cout << "(" << snumber << ") booked " << sname << endl;
	}
}

void graphicObjects::bookEfficiencyHistos(TMapss* period2triggerperiodMap, TDirectory* tdir)
{
	if(tdir==NULL) return;

	tdir->cd();
	
	h1map_tagNprobe_candidates_pT = new TMapSP2TH1D();
	h1map_tagNprobe_succeeded_pT = new TMapSP2TH1D();
	h1map_tagNprobe_trigEff_pT = new TMapSP2TH1D();
	h1map_tagNprobe_candidates_eta = new TMapSP2TH1D();
	h1map_tagNprobe_succeeded_eta = new TMapSP2TH1D();
	h1map_tagNprobe_trigEff_eta = new TMapSP2TH1D();
	h1map_tagNprobe_candidates_phi = new TMapSP2TH1D();
	h1map_tagNprobe_succeeded_phi = new TMapSP2TH1D();
	h1map_tagNprobe_trigEff_phi = new TMapSP2TH1D();
	
	h1map_truth_candidates_pT = new TMapSP2TH1D();
	h1map_truth_succeeded_pT = new TMapSP2TH1D();
	h1map_truth_trigEff_pT = new TMapSP2TH1D();
	h1map_truth_candidates_eta = new TMapSP2TH1D();
	h1map_truth_succeeded_eta = new TMapSP2TH1D();
	h1map_truth_trigEff_eta = new TMapSP2TH1D();
	h1map_truth_candidates_phi = new TMapSP2TH1D();
	h1map_truth_succeeded_phi = new TMapSP2TH1D();
	h1map_truth_trigEff_phi = new TMapSP2TH1D();

	string strigperiod = "";
	string speriod = "";
	string sname = "";
	TMapSP2TH1D::iterator it=h1map_tagNprobe_candidates_pT->end();
	
	int count = 0;
	for(TMapss::iterator ii=period2triggerperiodMap->begin() ; ii!=period2triggerperiodMap->end() ; ++ii)
	{
		speriod      = ii->first;
		strigperiod  = ii->second;
		
		if( h1map_tagNprobe_candidates_pT->find(strigperiod)!=it ) continue;
		count++;
		
		cout << "(" << count << ") booking trigger-period: " << strigperiod << endl;
		
		sname = "tNp_cand_pT." + strigperiod;
		h1map_tagNprobe_candidates_pT->insert( make_pair( strigperiod, new TH1D(sname.c_str(),sname.c_str(),tagNprobe_pT_nbins,tagNprobe_pT_min,tagNprobe_pT_max) ) );
		sname = "tNp_succ_pT." + strigperiod;
		h1map_tagNprobe_succeeded_pT->insert( make_pair( strigperiod, new TH1D(sname.c_str(),sname.c_str(),tagNprobe_pT_nbins,tagNprobe_pT_min,tagNprobe_pT_max) ) );
		sname = "tNp_effi_pT." + strigperiod;
		h1map_tagNprobe_trigEff_pT->insert( make_pair( strigperiod, new TH1D(sname.c_str(),sname.c_str(),tagNprobe_pT_nbins,tagNprobe_pT_min,tagNprobe_pT_max) ) );
		cout << "Efficiency (T&P) booked: pT" << endl;
		sname = "tru_cand_pT." + strigperiod;
		h1map_truth_candidates_pT->insert( make_pair( strigperiod, new TH1D(sname.c_str(),sname.c_str(),tagNprobe_pT_nbins,tagNprobe_pT_min,tagNprobe_pT_max) ) );
		sname = "tru_succ_pT." + strigperiod;
		h1map_truth_succeeded_pT->insert( make_pair( strigperiod, new TH1D(sname.c_str(),sname.c_str(),tagNprobe_pT_nbins,tagNprobe_pT_min,tagNprobe_pT_max) ) );
		sname = "tru_effi_pT." + strigperiod;
		h1map_truth_trigEff_pT->insert( make_pair( strigperiod, new TH1D(sname.c_str(),sname.c_str(),tagNprobe_pT_nbins,tagNprobe_pT_min,tagNprobe_pT_max) ) );
		cout << "Efficiency (truth) booked: pT" << endl;
		
		sname = "tNp_cand_eta." + strigperiod;
		h1map_tagNprobe_candidates_eta->insert( make_pair( strigperiod, new TH1D(sname.c_str(),sname.c_str(),eta_nbins,eta_min,eta_max) ) );
		sname = "tNp_succ_eta." + strigperiod;
		h1map_tagNprobe_succeeded_eta->insert( make_pair( strigperiod, new TH1D(sname.c_str(),sname.c_str(),eta_nbins,eta_min,eta_max) ) );
		sname = "tNp_effi_eta." + strigperiod;
		h1map_tagNprobe_trigEff_eta->insert( make_pair( strigperiod, new TH1D(sname.c_str(),sname.c_str(),eta_nbins,eta_min,eta_max) ) );
		cout << "Efficiency (T&P) booked: eta" << endl;
		sname = "tru_cand_eta." + strigperiod;
		h1map_truth_candidates_eta->insert( make_pair( strigperiod, new TH1D(sname.c_str(),sname.c_str(),eta_nbins,eta_min,eta_max) ) );
		sname = "tru_succ_eta." + strigperiod;
		h1map_truth_succeeded_eta->insert( make_pair( strigperiod, new TH1D(sname.c_str(),sname.c_str(),eta_nbins,eta_min,eta_max) ) );
		sname = "tru_effi_eta." + strigperiod;
		h1map_truth_trigEff_eta->insert( make_pair( strigperiod, new TH1D(sname.c_str(),sname.c_str(),eta_nbins,eta_min,eta_max) ) );
		cout << "Efficiency (truth) booked: eta" << endl;
		
		sname = "tNp_cand_phi." + strigperiod;
		h1map_tagNprobe_candidates_phi->insert( make_pair( strigperiod, new TH1D(sname.c_str(),sname.c_str(),phi_nbins,phi_min,phi_max) ) );
		sname = "tNp_succ_phi." + strigperiod;
		h1map_tagNprobe_succeeded_phi->insert( make_pair( strigperiod, new TH1D(sname.c_str(),sname.c_str(),phi_nbins,phi_min,phi_max) ) );
		sname = "tNp_effi_phi." + strigperiod;
		h1map_tagNprobe_trigEff_phi->insert( make_pair( strigperiod, new TH1D(sname.c_str(),sname.c_str(),phi_nbins,phi_min,phi_max) ) );
		cout << "Efficiency (T&P) booked: phi" << endl;
		sname = "tru_cand_phi." + strigperiod;
		h1map_truth_candidates_phi->insert( make_pair( strigperiod, new TH1D(sname.c_str(),sname.c_str(),phi_nbins,phi_min,phi_max) ) );
		sname = "tru_succ_phi." + strigperiod;
		h1map_truth_succeeded_phi->insert( make_pair( strigperiod, new TH1D(sname.c_str(),sname.c_str(),phi_nbins,phi_min,phi_max) ) );
		sname = "tru_effi_phi." + strigperiod;
		h1map_truth_trigEff_phi->insert( make_pair( strigperiod, new TH1D(sname.c_str(),sname.c_str(),phi_nbins,phi_min,phi_max) ) );
		cout << "Efficiency (truth) booked: phi" << endl;
	}
}

void graphicObjects::drawEfficiencyHistosMap(TDirectory* tdir)
{
	if(tdir==NULL) return;
	
	tdir->cd();

	TMapSP2TCNV* cnv_tNp_eff_pT  = new TMapSP2TCNV();
	TMapSP2TCNV* cnv_tNp_eff_eta = new TMapSP2TCNV();
	TMapSP2TCNV* cnv_tNp_eff_phi = new TMapSP2TCNV();
	TMapSP2TCNV* cnv_truth_eff_pT  = new TMapSP2TCNV();
	TMapSP2TCNV* cnv_truth_eff_eta = new TMapSP2TCNV();
	TMapSP2TCNV* cnv_truth_eff_phi = new TMapSP2TCNV();
	
	string sname = "";
	string strigperiod = "";
	for(TMapSP2TH1D::iterator ii=h1map_tagNprobe_candidates_pT->begin() ; ii!=h1map_tagNprobe_candidates_pT->end() ; ++ii)
	{
		strigperiod = ii->first;
		
		sname = "tNp_eff_pT." + strigperiod;
		cnv_tNp_eff_pT->insert( make_pair( strigperiod, new TCanvas(sname.c_str(),sname.c_str(),canv_x,canv_y) ) );
		sname = "tNp_eff_eta." + strigperiod;
		cnv_tNp_eff_eta->insert( make_pair( strigperiod, new TCanvas(sname.c_str(),sname.c_str(),canv_x,canv_y) ) );
		sname = "tNp_eff_phi." + strigperiod;
		cnv_tNp_eff_phi->insert( make_pair( strigperiod, new TCanvas(sname.c_str(),sname.c_str(),canv_x,canv_y) ) );
		
		sname = "tru_eff_pT." + strigperiod;
		cnv_truth_eff_pT->insert( make_pair( strigperiod, new TCanvas(sname.c_str(),sname.c_str(),canv_x,canv_y) ) );
		sname = "tru_eff_eta." + strigperiod;
		cnv_truth_eff_eta->insert( make_pair( strigperiod, new TCanvas(sname.c_str(),sname.c_str(),canv_x,canv_y) ) );
		sname = "tru_eff_phi." + strigperiod;
		cnv_truth_eff_phi->insert( make_pair( strigperiod, new TCanvas(sname.c_str(),sname.c_str(),canv_x,canv_y) ) );
	}
	
	for(TMapSP2TH1D::iterator ii=h1map_tagNprobe_candidates_pT->begin() ; ii!=h1map_tagNprobe_candidates_pT->end() ; ++ii)
	{
		strigperiod = ii->first;
		
		
		// ------ pT
		(*cnv_tNp_eff_pT)[strigperiod]->Divide(1,3);
		pad_candidates_pT = (*cnv_tNp_eff_pT)[strigperiod]->cd(1);
		pad_succeeded_pT  = (*cnv_tNp_eff_pT)[strigperiod]->cd(2);
		pad_efficiency_pT = (*cnv_tNp_eff_pT)[strigperiod]->cd(3);
		(*cnv_tNp_eff_pT)[strigperiod]->Draw();
		pad_candidates_pT->cd();
		(*h1map_tagNprobe_candidates_pT)[strigperiod]->SetTitle("");
		(*h1map_tagNprobe_candidates_pT)[strigperiod]->SetXTitle("p_{T} TeV");
		(*h1map_tagNprobe_candidates_pT)[strigperiod]->SetYTitle("Candidate probe muons");
		(*h1map_truth_candidates_pT)[strigperiod]->SetTitle("");
		(*h1map_truth_candidates_pT)[strigperiod]->SetXTitle("p_{T} TeV");
		(*h1map_truth_candidates_pT)[strigperiod]->SetYTitle("Candidate probe muons");
		(*h1map_truth_candidates_pT)[strigperiod]->SetLineColor(kRed);
		(*h1map_truth_candidates_pT)[strigperiod]->SetLineStyle(2);
		if( (*h1map_tagNprobe_candidates_pT)[strigperiod]->GetMaximum() > (*h1map_truth_candidates_pT)[strigperiod]->GetMaximum() )
		{
			(*h1map_truth_candidates_pT)[strigperiod]->SetMaximum(1.05*(*h1map_tagNprobe_candidates_pT)[strigperiod]->GetMaximum());
		}
		(*h1map_truth_candidates_pT)[strigperiod]->SetMinimum(0.);
		(*h1map_truth_candidates_pT)[strigperiod]->Draw();
		(*h1map_tagNprobe_candidates_pT)[strigperiod]->Draw("sames");
		
		pad_succeeded_pT->cd();
		(*h1map_tagNprobe_succeeded_pT)[strigperiod]->SetTitle("");
		(*h1map_tagNprobe_succeeded_pT)[strigperiod]->SetXTitle("p_{T} TeV");
		(*h1map_tagNprobe_succeeded_pT)[strigperiod]->SetYTitle("Probe muons");
		(*h1map_truth_succeeded_pT)[strigperiod]->SetTitle("");
		(*h1map_truth_succeeded_pT)[strigperiod]->SetXTitle("p_{T} TeV");
		(*h1map_truth_succeeded_pT)[strigperiod]->SetYTitle("Probe muons");
		(*h1map_truth_succeeded_pT)[strigperiod]->SetLineColor(kRed);
		(*h1map_truth_succeeded_pT)[strigperiod]->SetLineStyle(2);
		if( (*h1map_tagNprobe_succeeded_pT)[strigperiod]->GetMaximum() > (*h1map_truth_succeeded_pT)[strigperiod]->GetMaximum() )
		{
			(*h1map_truth_succeeded_pT)[strigperiod]->SetMaximum(1.05*(*h1map_tagNprobe_succeeded_pT)[strigperiod]->GetMaximum());
		}
		(*h1map_truth_succeeded_pT)[strigperiod]->SetMinimum(0.);
		(*h1map_truth_succeeded_pT)[strigperiod]->Draw();
		(*h1map_tagNprobe_succeeded_pT)[strigperiod]->Draw("sames");
		
		pad_efficiency_pT->cd();
		pad_efficiency_pT->SetGrid();
		(*h1map_tagNprobe_trigEff_pT)[strigperiod]->SetTitle("");
		(*h1map_tagNprobe_trigEff_pT)[strigperiod]->SetXTitle("p_{T} TeV");
		(*h1map_tagNprobe_trigEff_pT)[strigperiod]->SetYTitle("#epsilon = #frac{N_{probes}}{N_{probe}^{candidates}}");
		(*h1map_truth_trigEff_pT)[strigperiod]->SetTitle("");
		(*h1map_truth_trigEff_pT)[strigperiod]->SetXTitle("p_{T} TeV");
		(*h1map_truth_trigEff_pT)[strigperiod]->SetYTitle("#epsilon = #frac{N_{probes}}{N_{probe}^{candidates}}");
		(*h1map_truth_trigEff_pT)[strigperiod]->SetLineColor(kRed);
		(*h1map_truth_trigEff_pT)[strigperiod]->SetLineWidth(2);
		(*h1map_truth_trigEff_pT)[strigperiod]->SetMarkerStyle(7);
		(*h1map_truth_trigEff_pT)[strigperiod]->SetMarkerColor(kRed);
		(*h1map_truth_trigEff_pT)[strigperiod]->SetMarkerSize(0.5);
		(*h1map_truth_trigEff_pT)[strigperiod]->SetMinimum(0.);
		(*h1map_truth_trigEff_pT)[strigperiod]->SetMaximum(1.05);
		(*h1map_truth_trigEff_pT)[strigperiod]->Draw();
		(*h1map_tagNprobe_trigEff_pT)[strigperiod]->Draw("e1x0sames");
		(*cnv_tNp_eff_pT)[strigperiod]->Update();
		(*cnv_tNp_eff_pT)[strigperiod]->Write();
		
		
		// ------ eta
		(*cnv_tNp_eff_eta)[strigperiod]->Divide(1,3);
		pad_candidates_eta = (*cnv_tNp_eff_eta)[strigperiod]->cd(1);
		pad_succeeded_eta  = (*cnv_tNp_eff_eta)[strigperiod]->cd(2);
		pad_efficiency_eta = (*cnv_tNp_eff_eta)[strigperiod]->cd(3);
		(*cnv_tNp_eff_eta)[strigperiod]->Draw();
		pad_candidates_eta->cd();
		(*h1map_tagNprobe_candidates_eta)[strigperiod]->SetTitle("");
		(*h1map_tagNprobe_candidates_eta)[strigperiod]->SetXTitle("#eta");
		(*h1map_tagNprobe_candidates_eta)[strigperiod]->SetYTitle("Candidate probe muons");
		(*h1map_truth_candidates_eta)[strigperiod]->SetTitle("");
		(*h1map_truth_candidates_eta)[strigperiod]->SetXTitle("#eta");
		(*h1map_truth_candidates_eta)[strigperiod]->SetYTitle("Candidate probe muons");
		(*h1map_truth_candidates_eta)[strigperiod]->SetLineColor(kRed);
		(*h1map_truth_candidates_eta)[strigperiod]->SetLineStyle(2);
		if( (*h1map_tagNprobe_candidates_eta)[strigperiod]->GetMaximum() > (*h1map_truth_candidates_eta)[strigperiod]->GetMaximum() )
		{
			(*h1map_truth_candidates_eta)[strigperiod]->SetMaximum(1.05*(*h1map_tagNprobe_candidates_eta)[strigperiod]->GetMaximum());
		}
		(*h1map_truth_candidates_eta)[strigperiod]->SetMinimum(0.);
		(*h1map_truth_candidates_eta)[strigperiod]->Draw();
		(*h1map_tagNprobe_candidates_eta)[strigperiod]->Draw("sames");
		
		pad_succeeded_eta->cd();
		(*h1map_tagNprobe_succeeded_eta)[strigperiod]->SetTitle("");
		(*h1map_tagNprobe_succeeded_eta)[strigperiod]->SetXTitle("#eta");
		(*h1map_tagNprobe_succeeded_eta)[strigperiod]->SetYTitle("Probe muons");
		(*h1map_truth_succeeded_eta)[strigperiod]->SetTitle("");
		(*h1map_truth_succeeded_eta)[strigperiod]->SetXTitle("#eta");
		(*h1map_truth_succeeded_eta)[strigperiod]->SetYTitle("Probe muons");
		(*h1map_truth_succeeded_eta)[strigperiod]->SetLineColor(kRed);
		(*h1map_truth_succeeded_eta)[strigperiod]->SetLineStyle(2);
		if( (*h1map_tagNprobe_succeeded_eta)[strigperiod]->GetMaximum() > (*h1map_truth_succeeded_eta)[strigperiod]->GetMaximum() )
		{
			(*h1map_truth_succeeded_eta)[strigperiod]->SetMaximum(1.05*(*h1map_tagNprobe_succeeded_eta)[strigperiod]->GetMaximum());
		}
		(*h1map_truth_succeeded_eta)[strigperiod]->SetMinimum(0.);
		(*h1map_truth_succeeded_eta)[strigperiod]->Draw();
		(*h1map_tagNprobe_succeeded_eta)[strigperiod]->Draw("sames");
		
		pad_efficiency_eta->cd();
		pad_efficiency_eta->SetGrid();
		(*h1map_tagNprobe_trigEff_eta)[strigperiod]->SetTitle("");
		(*h1map_tagNprobe_trigEff_eta)[strigperiod]->SetXTitle("#eta");
		(*h1map_tagNprobe_trigEff_eta)[strigperiod]->SetYTitle("#epsilon = #frac{N_{probes}}{N_{probe}^{candidates}}");
		(*h1map_truth_trigEff_eta)[strigperiod]->SetTitle("");
		(*h1map_truth_trigEff_eta)[strigperiod]->SetXTitle("#eta");
		(*h1map_truth_trigEff_eta)[strigperiod]->SetYTitle("#epsilon = #frac{N_{probes}}{N_{probe}^{candidates}}");
		(*h1map_truth_trigEff_eta)[strigperiod]->SetLineColor(kRed);
		(*h1map_truth_trigEff_eta)[strigperiod]->SetLineWidth(2);
		(*h1map_truth_trigEff_eta)[strigperiod]->SetMarkerStyle(7);
		(*h1map_truth_trigEff_eta)[strigperiod]->SetMarkerColor(kRed);
		(*h1map_truth_trigEff_eta)[strigperiod]->SetMarkerSize(0.5);
		(*h1map_truth_trigEff_eta)[strigperiod]->SetMinimum(0.);
		(*h1map_truth_trigEff_eta)[strigperiod]->SetMaximum(1.05);
		(*h1map_truth_trigEff_eta)[strigperiod]->Draw();
		(*h1map_tagNprobe_trigEff_eta)[strigperiod]->Draw("e1x0sames");
		(*cnv_tNp_eff_eta)[strigperiod]->Update();
		(*cnv_tNp_eff_eta)[strigperiod]->Write();
		
		
		
		// ------ phi
		(*cnv_tNp_eff_phi)[strigperiod]->Divide(1,3);
		pad_candidates_phi = (*cnv_tNp_eff_phi)[strigperiod]->cd(1);
		pad_succeeded_phi  = (*cnv_tNp_eff_phi)[strigperiod]->cd(2);
		pad_efficiency_phi = (*cnv_tNp_eff_phi)[strigperiod]->cd(3);
		(*cnv_tNp_eff_phi)[strigperiod]->Draw();
		pad_candidates_phi->cd();
		(*h1map_tagNprobe_candidates_phi)[strigperiod]->SetTitle("");
		(*h1map_tagNprobe_candidates_phi)[strigperiod]->SetXTitle("#phi");
		(*h1map_tagNprobe_candidates_phi)[strigperiod]->SetYTitle("Candidate probe muons");
		(*h1map_truth_candidates_phi)[strigperiod]->SetTitle("");
		(*h1map_truth_candidates_phi)[strigperiod]->SetXTitle("#phi");
		(*h1map_truth_candidates_phi)[strigperiod]->SetYTitle("Candidate probe muons");
		(*h1map_truth_candidates_phi)[strigperiod]->SetLineColor(kRed);
		(*h1map_truth_candidates_phi)[strigperiod]->SetLineStyle(2);
		if( (*h1map_tagNprobe_candidates_phi)[strigperiod]->GetMaximum() > (*h1map_truth_candidates_phi)[strigperiod]->GetMaximum() )
		{
			(*h1map_truth_candidates_phi)[strigperiod]->SetMaximum(1.05*(*h1map_tagNprobe_candidates_phi)[strigperiod]->GetMaximum());
		}
		(*h1map_truth_candidates_phi)[strigperiod]->SetMinimum(0.);
		(*h1map_truth_candidates_phi)[strigperiod]->Draw();
		(*h1map_tagNprobe_candidates_phi)[strigperiod]->Draw("sames");
		
		pad_succeeded_phi->cd();
		(*h1map_tagNprobe_succeeded_phi)[strigperiod]->SetTitle("");
		(*h1map_tagNprobe_succeeded_phi)[strigperiod]->SetXTitle("#phi");
		(*h1map_tagNprobe_succeeded_phi)[strigperiod]->SetYTitle("Probe muons");
		(*h1map_truth_succeeded_phi)[strigperiod]->SetTitle("");
		(*h1map_truth_succeeded_phi)[strigperiod]->SetXTitle("#phi");
		(*h1map_truth_succeeded_phi)[strigperiod]->SetYTitle("Probe muons");
		(*h1map_truth_succeeded_phi)[strigperiod]->SetLineColor(kRed);
		(*h1map_truth_succeeded_phi)[strigperiod]->SetLineStyle(2);
		if( (*h1map_tagNprobe_succeeded_phi)[strigperiod]->GetMaximum() > (*h1map_truth_succeeded_phi)[strigperiod]->GetMaximum() )
		{
			(*h1map_truth_succeeded_phi)[strigperiod]->SetMaximum(1.05*(*h1map_tagNprobe_succeeded_phi)[strigperiod]->GetMaximum());
		}
		(*h1map_truth_succeeded_phi)[strigperiod]->SetMinimum(0.);
		(*h1map_truth_succeeded_phi)[strigperiod]->Draw();
		(*h1map_tagNprobe_succeeded_phi)[strigperiod]->Draw("sames");
		
		pad_efficiency_phi->cd();
		pad_efficiency_phi->SetGrid();
		(*h1map_tagNprobe_trigEff_phi)[strigperiod]->SetTitle("");
		(*h1map_tagNprobe_trigEff_phi)[strigperiod]->SetXTitle("#phi");
		(*h1map_tagNprobe_trigEff_phi)[strigperiod]->SetYTitle("#epsilon = #frac{N_{probes}}{N_{probe}^{candidates}}");
		(*h1map_truth_trigEff_phi)[strigperiod]->SetTitle("");
		(*h1map_truth_trigEff_phi)[strigperiod]->SetXTitle("#phi");
		(*h1map_truth_trigEff_phi)[strigperiod]->SetYTitle("#epsilon = #frac{N_{probes}}{N_{probe}^{candidates}}");
		(*h1map_truth_trigEff_phi)[strigperiod]->SetLineColor(kRed);
		(*h1map_truth_trigEff_phi)[strigperiod]->SetLineWidth(2);
		(*h1map_truth_trigEff_phi)[strigperiod]->SetMarkerStyle(7);
		(*h1map_truth_trigEff_phi)[strigperiod]->SetMarkerColor(kRed);
		(*h1map_truth_trigEff_phi)[strigperiod]->SetMarkerSize(0.5);
		(*h1map_truth_trigEff_phi)[strigperiod]->SetMinimum(0.);
		(*h1map_truth_trigEff_phi)[strigperiod]->SetMaximum(1.05);
		(*h1map_truth_trigEff_phi)[strigperiod]->Draw();
		(*h1map_tagNprobe_trigEff_phi)[strigperiod]->Draw("e1x0sames");
		(*cnv_tNp_eff_phi)[strigperiod]->Update();
		(*cnv_tNp_eff_phi)[strigperiod]->Write();
	}
}

void graphicObjects::drawHistosMap(TMapds* cutFlowOrdered, TMapds* cutFlowTypeOrdered, TDirectory* tdir)
{
	if(tdir==NULL) return;
	
	tdir->cd();

	bool bfirst;
	
	Color_t colorStart  = 40;
	Color_t colorOffset = 1;
	Color_t colorAccumulate = colorStart;
	TMapSP2TH1D::iterator it;
	//TMapds::iterator ii;
	string sname = "";

	leg_cutFlow_imass = new TLegend(leg_x1, leg_y1, leg_x2, leg_y2);
	leg_cutFlow_pT    = new TLegend(leg_x1, leg_y1, leg_x2, leg_y2);

	cnv_cutFlow_imass = new TCanvas("imass.cutFlow","imass.cutFlow",canv_x,canv_y);
	cnv_cutFlow_imass->SetLogy();
	cnv_cutFlow_imass->Draw();
	cnv_cutFlow_imass->cd();
	colorAccumulate = colorStart;
	
	bfirst = true;
	for(TMapds::iterator ii=cutFlowOrdered->begin() ; ii!=cutFlowOrdered->end() ; ++ii)
	{
		double num = ii->first;
		///////////////////////////////////////////////////////////////
		// ignore preselection: ///////////////////////////////////////
		if(cutFlowTypeOrdered->operator[](num)=="preselection") continue; /////////
		///////////////////////////////////////////////////////////////
		
		//if(ii == cutFlowOrdered->begin()) bfirst = true;
		//else bfirst = false;
		
		string str = ii->second; 
		it=hmap_cutFlow_imass->find("imass."+str);
		sname = it->first;
		(*hmap_cutFlow_imass)[sname]->SetFillColor(colorAccumulate);
		(*hmap_cutFlow_imass)[sname]->SetLineColor(colorAccumulate);
		leg_cutFlow_imass->AddEntry( (*hmap_cutFlow_imass)[sname], str.c_str(), "f");
		if(bfirst)
		{
			(*hmap_cutFlow_imass)[sname]->SetMinimum(5.e-1);
			(*hmap_cutFlow_imass)[sname]->Draw();
		}
		else (*hmap_cutFlow_imass)[sname]->Draw("SAMES");
		colorAccumulate += colorOffset;
		cout << "drawn " << sname << endl;
		
		bfirst = false;
	}
	leg_cutFlow_imass->Draw("SAMES");
	cnv_cutFlow_imass->Update();
	cnv_cutFlow_imass->Write();

	//--------------
	
	cnv_cutFlow_pT = new TCanvas("pT.cutFlow","pT.cutFlow",canv_x,canv_y);
	cnv_cutFlow_pT->SetLogy();
	cnv_cutFlow_pT->Draw();
	cnv_cutFlow_pT->cd();
	colorAccumulate = colorStart;
	
	bfirst = true;
	for(TMapds::iterator ii=cutFlowOrdered->begin() ; ii!=cutFlowOrdered->end() ; ++ii)
	{
		double num = ii->first;
		///////////////////////////////////////////////////////////////
		// ignore preselection: ///////////////////////////////////////
		if(cutFlowTypeOrdered->operator[](num)=="preselection") continue; /////////
		///////////////////////////////////////////////////////////////
		
		//if(ii == cutFlowOrdered->begin()) bfirst = true;
		//else bfirst = false;
		
		string str = ii->second;
		it=hmap_cutFlow_pT->find("pT."+str);
		sname = it->first;
		(*hmap_cutFlow_pT)[sname]->SetFillColor(colorAccumulate);
		(*hmap_cutFlow_pT)[sname]->SetLineColor(colorAccumulate);
		leg_cutFlow_pT->AddEntry( (*hmap_cutFlow_pT)[sname], str.c_str(), "f");
		if(bfirst)
		{
			(*hmap_cutFlow_pT)[sname]->SetMinimum(5.e-1);
			(*hmap_cutFlow_pT)[sname]->Draw();
		}
		else (*hmap_cutFlow_pT)[sname]->Draw("SAMES");
		colorAccumulate += colorOffset;
		cout << "drawn " << sname << endl;
		
		bfirst = false;
	}
	leg_cutFlow_pT->Draw("SAMES");
	cnv_cutFlow_pT->Update();
	cnv_cutFlow_pT->Write();
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 


void graphicObjects::bookFitHistos(TDirectory* tdir)
{
	if(tdir!=NULL) tdir->cd();

	h1_imassFit = new TH1D("imassFit","imassFit", imass_fit_nbins, imass_fit_min, imass_fit_max);
}

void graphicObjects::drawFitHistos(TDirectory* tdir, TF1* fGuess, TF1* fFitted)
{
	if(tdir!=NULL) tdir->cd();
	
	leg_imassFit = new TLegend(leg_x1, leg_y1*2., leg_x2, leg_y2);
	
	cnv_imassFit = new TCanvas("imassFit","imassFit",canv_x,canv_y);
	cnv_imassFit->Draw();
	cnv_imassFit->cd();
	
	double h_max = h1_imassFit->GetMaximum();
	double f_max = fFitted->GetMaximum(XMIN,XMAX);
	double max = 0.;
	max = ( f_max > h_max) ? f_max : h_max;
	h1_imassFit->SetMaximum(1.05*max);
	
	h1_imassFit->SetMarkerStyle(20);
	h1_imassFit->Draw("e1x0");
	
	fGuess->SetLineStyle(1);
	fGuess->SetLineColor(kRed);
	fGuess->SetLineWidth(2);
	//fGuess->Draw("sames");
	
	fFitted->SetLineStyle(1);
	fFitted->SetLineColor(kBlue);
	fFitted->SetLineWidth(2);
	fFitted->Draw("sames");
	
	leg_imassFit->AddEntry( h1_imassFit, "Data", "lep");
	//leg_imassFit->AddEntry( fGuess, "Guess", "L");
	leg_imassFit->AddEntry( fFitted, "#chi^{2} fit", "L");
	leg_imassFit->Draw("sames");
	
	cnv_imassFit->Update();
	cnv_imassFit->Write();
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *


void graphicObjects::bookCutProfileHistosMap(TMapds* cutFlowOrdered, TDirectory* tdir)
{
	if(tdir==NULL) return;

	tdir->cd();

	h1map_cutProfile = new TMapSP2TH1D();
	h2map_cutProfile = new TMapSP2TH2D();
	
	cmap_cutProfile  = new TMapSP2TCNV();

	for(TMapds::iterator it=cutFlowOrdered->begin() ; it!=cutFlowOrdered->end() ; ++it)
	{
		double snumber = it->first;
		string sname   = it->second;

		if(sname=="GRL")
		{
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 2, 0.,2.) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("isGRL");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
		}
		
		else if(sname=="Trigger")
		{
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 2, 0.,2.) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("isTrigger");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
		}
		
		else if(sname=="PV")
		{
			h2map_cutProfile->insert( make_pair( sname, new TH2D(sname.c_str(),sname.c_str(), 600,-300,300.,  200,0,200) ) );
			(*h2map_cutProfile)[sname]->SetXTitle("zVtx");
			(*h2map_cutProfile)[sname]->SetYTitle("nTracks");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
		}
		
		else if(sname=="pT")
		{
			string stmp = sname;
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), pT_nbins, pT_min, pT_max) ) );
			//h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), pT_nbins, pT_bins) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("pT");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), pT_nbins, pT_min, pT_max) ) );
			//h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), pT_nbins, pT_bins) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("pT");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
		}
		
		else if(sname=="pT_qOp+theta")
		{
			string stmp = sname;
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), pT_nbins, pT_min, pT_max) ) );
			//h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), pT_nbins, pT_bins) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("p_{T}=Q/#left|p#right| #times #sin(#theta)");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), pT_nbins, pT_min, pT_max) ) );
			//h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), pT_nbins, pT_bins) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("p_{T}=Q/#left|p#right| #times #sin(#theta)");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
		}
		
		else if(sname=="eta")
		{
			string stmp = sname;
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), eta_nbins, eta_min, eta_max) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("#eta");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), eta_nbins, eta_min, eta_max) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("#eta");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
		}
		
		else if(sname=="etaTight")
		{
			string stmp = sname;
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), eta_nbins, eta_min, eta_max) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("#eta_{Tight}");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), eta_nbins, eta_min, eta_max) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("#eta_{Tight}");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
		}
		
		else if(sname=="etaBarrel")
		{
			string stmp = sname;
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), eta_nbins, eta_min, eta_max) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("#eta_{Barrel}");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), eta_nbins, eta_min, eta_max) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("#eta_{Barrel}");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
		}
		
		else if(sname=="pTandEta")
		{
			string stmp = sname;
			sname = stmp+"_1";
			h2map_cutProfile->insert( make_pair( sname, new TH2D(sname.c_str(),sname.c_str(), pT_nbins,pT_min,pT_max,  eta_nbins,eta_min,eta_max) ) );
			(*h2map_cutProfile)[sname]->SetXTitle("p_{T}");
			(*h2map_cutProfile)[sname]->SetYTitle("#eta_{Tight}");
			sname = stmp+"_2";
			h2map_cutProfile->insert( make_pair( sname, new TH2D(sname.c_str(),sname.c_str(), pT_nbins,pT_min,pT_max,  eta_nbins,eta_min,eta_max) ) );
			(*h2map_cutProfile)[sname]->SetXTitle("p_{T}");
			(*h2map_cutProfile)[sname]->SetYTitle("#eta_{Tight}");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
		}
		
		else if(sname=="pTandEtaTight")
		{
			string stmp = sname;
			sname = stmp+"_1";
			h2map_cutProfile->insert( make_pair( sname, new TH2D(sname.c_str(),sname.c_str(), pT_nbins,pT_min,pT_max,  eta_nbins,eta_min,eta_max) ) );
			(*h2map_cutProfile)[sname]->SetXTitle("p_{T}");
			(*h2map_cutProfile)[sname]->SetYTitle("#eta_{Tight}");
			sname = stmp+"_2";
			h2map_cutProfile->insert( make_pair( sname, new TH2D(sname.c_str(),sname.c_str(), pT_nbins,pT_min,pT_max,  eta_nbins,eta_min,eta_max) ) );
			(*h2map_cutProfile)[sname]->SetXTitle("p_{T}");
			(*h2map_cutProfile)[sname]->SetYTitle("#eta_{Tight}");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
		}
		
		else if(sname=="pTandEtaBarrel")
		{
			string stmp = sname;
			sname = stmp+"_1";
			h2map_cutProfile->insert( make_pair( sname, new TH2D(sname.c_str(),sname.c_str(), pT_nbins,pT_min,pT_max, eta_nbins, eta_min, eta_max) ) );
			(*h2map_cutProfile)[sname]->SetXTitle("p_{T}");
			(*h2map_cutProfile)[sname]->SetYTitle("#eta_{Barrel}");
			sname = stmp+"_2";
			h2map_cutProfile->insert( make_pair( sname, new TH2D(sname.c_str(),sname.c_str(), pT_nbins,pT_min,pT_max, eta_nbins, eta_min, eta_max) ) );
			(*h2map_cutProfile)[sname]->SetXTitle("p_{T}");
			(*h2map_cutProfile)[sname]->SetYTitle("#eta_{Barrel}");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
		}
		
		else if(sname=="msHits" || sname=="msHitsRel16")
		{
			string stmp;
			
			stmp = "nMDTBI";
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("MDT BI hits");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("MDT BI hits");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
			
			stmp = "nMDTBM";
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("MDT BM hits");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("MDT BM hits");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
			
			stmp = "nMDTBO";
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("MDT BO hits");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("MDT BO hits");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
			
			stmp = "nMDTEI";
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("MDT EI hits");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("MDT EI hits");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
			
			stmp = "nMDTEM";
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("MDT EM hits");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("MDT EM hits");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
			
			stmp = "nMDTEO";
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("MDT EO hits");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("MDT EO hits");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
			
			
			stmp = "nMDTBEE";
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("MDT BEE Hits");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("MDT BEE Hits");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
			
			stmp = "nMDTEE";
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("MDT EE Hits");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("MDT EE Hits");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
			
			stmp = "nMDTBIS78";
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("MDT BIS78 Hits");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("MDT BIS78 Hits");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
			
			
			stmp = "nRPCPhi1";
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("RPC Phi1 Hits");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("RPC Phi1 Hits");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
			
			stmp = "nRPCPhi2";
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("RPC Phi2 Hits");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("RPC Phi2 Hits");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
			
			stmp = "nRPCPhi3";
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("RPC Phi3 Hits");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("RPC Phi3 Hits");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
			
			stmp = "nTGCPhi1";
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("TGC Phi1 Hits");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("TGC Phi1 Hits");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
			
			stmp = "nTGCPhi2";
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("TGC Phi2 Hits");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("TGC Phi2 Hits");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
			
			stmp = "nTGCPhi3";
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("TGC Phi3 Hits");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("TGC Phi3 Hits");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
			
			stmp = "nTGCPhi4";
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("TGC Phi4 hits");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("TGC Phi4 hits");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
			
			stmp = "nCSCEta";
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("CSC Eta Hits");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("CSC Eta Hits");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
			
			stmp = "nCSCPhi";
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("CSC Phi Hits");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("CSC Phi Hits");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
			
		}
		
		else if(sname=="idHits" ||  sname=="idHitsRel16")
		{
			string stmp = sname;
			sname = stmp+"_1";
			h2map_cutProfile->insert( make_pair( sname, new TH2D(sname.c_str(),sname.c_str(), 20,0,20,  20,0,20) ) );
			(*h2map_cutProfile)[sname]->SetXTitle("SCT hits");
			(*h2map_cutProfile)[sname]->SetYTitle("PIX hits");
			sname = stmp+"_2";
			h2map_cutProfile->insert( make_pair( sname, new TH2D(sname.c_str(),sname.c_str(), 20,0,20,  20,0,20) ) );
			(*h2map_cutProfile)[sname]->SetXTitle("SCT hits");
			(*h2map_cutProfile)[sname]->SetYTitle("PIX hits");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
			
			stmp = "expectBLayerHit";
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 20,0,20) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("expectBLayerHit");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 20,0,20) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("expectBLayerHit");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
			
			stmp = "nBLHits";
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("BL Hits");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("BL Hits");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
			
			stmp = "nPixHits";
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("nPix Hits");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("nPix Hits");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
			
			stmp = "nPixelDeadSensors";
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("Pixel Dead Sensors");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("Pixel Dead Sensors");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
			
			stmp = "nPixHoles";
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("Pix Holes");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("Pix Holes");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
			
			stmp = "nSCTHits";
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("SCT Hits");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("SCT Hits");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
			
			stmp = "nSCTDeadSensors";
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("SCT Dead Sensors");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("SCT Dead Sensors");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
			
			stmp = "nSCTHoles";
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("SCT Holes");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("SCT Holes");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
			
			stmp = "nTRTHits";
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("TRT Hits");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("TRT Hits");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
			
			stmp = "nTRTOutliers";
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("TRT Outliers");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("TRT Outliers");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
			
			stmp = "nTRTHitsVSeta";
			sname = stmp+"_1";
			h2map_cutProfile->insert( make_pair( sname, new TH2D(sname.c_str(),sname.c_str(), 30,-3,+3,  50,0,50) ) );
			(*h2map_cutProfile)[sname]->SetXTitle("#eta");
			(*h2map_cutProfile)[sname]->SetYTitle("TRT Hits");
			sname = stmp+"_2";
			h2map_cutProfile->insert( make_pair( sname, new TH2D(sname.c_str(),sname.c_str(), 30,-3,+3,  50,0,50) ) );
			(*h2map_cutProfile)[sname]->SetXTitle("#eta");
			(*h2map_cutProfile)[sname]->SetYTitle("TRT Hits");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
			
			stmp = "nTRTOutliersVSeta";
			sname = stmp+"_1";
			h2map_cutProfile->insert( make_pair( sname, new TH2D(sname.c_str(),sname.c_str(), 30,-3,+3,  50,0,50) ) );
			(*h2map_cutProfile)[sname]->SetXTitle("#eta");
			(*h2map_cutProfile)[sname]->SetYTitle("TRT Outliers");
			sname = stmp+"_2";
			h2map_cutProfile->insert( make_pair( sname, new TH2D(sname.c_str(),sname.c_str(), 30,-3,+3,  50,0,50) ) );
			(*h2map_cutProfile)[sname]->SetXTitle("#eta");
			(*h2map_cutProfile)[sname]->SetYTitle("TRT Outliers");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
		}
		
		else if(sname=="pTmatchingRatio")
		{
			string stmp = sname;
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), pT_nbins, pT_min, pT_max) ) );
			//h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), pT_nbins, pT_bins) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("p_{T}");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), pT_nbins, pT_min, pT_max) ) );
			//h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), pT_nbins, pT_bins) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("p_{T}");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
		}
		
		else if(sname=="pTmatchingAbsDiff")
		{
			string stmp = sname;
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), pT_nbins, pT_min, pT_max) ) );
			//h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), pT_nbins, pT_bins) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("p_{T}");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), pT_nbins, pT_min, pT_max) ) );
			//h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), pT_nbins, pT_bins) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("p_{T}");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
		}
		
		else if(sname=="d0")
		{
			string stmp = sname;
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 100, -0.5, 0.5) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("d_{0}");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 100, -0.5, 0.5) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("d_{0}");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
		}
		
		else if(sname=="z0")
		{
			string stmp = sname;
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 100, -0.5, 0.5) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("z_{0}");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 100, -0.5, 0.5) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("z_{0}");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
		}
		
		else if(sname=="impactParameter")
		{
			string stmp = sname;
			sname = stmp+"_1";
			h2map_cutProfile->insert( make_pair( sname, new TH2D(sname.c_str(),sname.c_str(), 100,-0.5,0.5,  100,-0.5,0.5) ) );
			(*h2map_cutProfile)[sname]->SetXTitle("d_{0}");
			(*h2map_cutProfile)[sname]->SetYTitle("z_{0}");
			sname = stmp+"_2";
			h2map_cutProfile->insert( make_pair( sname, new TH2D(sname.c_str(),sname.c_str(), 100,-0.5,0.5,  100,-0.5,0.5) ) );
			(*h2map_cutProfile)[sname]->SetXTitle("d_{0}");
			(*h2map_cutProfile)[sname]->SetYTitle("z_{0}");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
		}
		
		else if(sname=="isolation20")
		{
			string stmp = sname;
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 400, 0, 0.01) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("#sum p_{T}^{cone20}/p_{T}");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 400, 0, 0.01) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("#sum p_{T}^{cone20}/p_{T}");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
		}
		
		else if(sname=="isolation30")
		{
			string stmp = sname;
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 400, 0, 0.01) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("#sum p_{T}^{cone30}/p_{T}");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 400, 0, 0.01) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("#sum p_{T}^{cone30}/p_{T}");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
		}
		
		else if(sname=="isolation40")
		{
			string stmp = sname;
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 400, 0, 0.01) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("#sum p_{T}^{cone40}/p_{T}");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 400, 0, 0.01) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("#sum p_{T}^{cone40}/p_{T}");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
		}
		
		else if(sname=="oppositeCharge")
		{
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 2,-1,1) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("Q_{1} #times Q_{2}");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
		}
		
		else if(sname=="imass")
		{
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), imass_nbins, imass_min, imass_max) ) );
			//h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), imass_nbins, M_bins) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("#hat{m}_{#mu#mu}");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
		}
		
		else if(sname=="cosThetaDimu")
		{
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), cosmicCosth_nbins,cosmicCosth_min,cosmicCosth_max) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("#hat{p}_{#mu^{1}} #cdot #hat{p}_{#mu^{2}}");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
		}
		
		else if(sname=="etaSum")
		{
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), etaSum_nbins,etaSum_min,etaSum_max) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("#sum{#eta_{#mu}}");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
		}
		
		else continue;
	}
}

void graphicObjects::drawCutProfileHistosMap(TDirectory* tdir)
{
	if(tdir==NULL) return;
	
	tdir->cd();
	
	string sname = "";
	string snameOrig = "";
	string sNumber = "";
	
	for(TMapSP2TH1D::iterator it=h1map_cutProfile->begin() ; it!=h1map_cutProfile->end() ; ++it)
	{
		sname   = it->first;
		sNumber = sname[sname.length()-1];
		
		if(sNumber=="1")
		{
			snameOrig = "cutProfile_" + sname.substr(0, sname.length()-2);
			cmap_cutProfile->insert( make_pair( snameOrig, new TCanvas(snameOrig.c_str(),snameOrig.c_str(), canv_x,canv_y) ) );
			(*cmap_cutProfile)[snameOrig]->Divide(1,2);
			(*cmap_cutProfile)[snameOrig]->Draw();
			(*cmap_cutProfile)[snameOrig]->cd();
			(*cmap_cutProfile)[snameOrig]->cd(1);
			(*h1map_cutProfile)[sname]->Draw();
		}
		else if(sNumber=="2")
		{
			snameOrig = "cutProfile_" + sname.substr(0, sname.length()-2);
			(*cmap_cutProfile)[snameOrig]->cd(2);
			(*h1map_cutProfile)[sname]->Draw();
			(*cmap_cutProfile)[snameOrig]->Update();
			(*cmap_cutProfile)[snameOrig]->Write();
		}
		else
		{
			snameOrig = "cutProfile_" + sname;
			cmap_cutProfile->insert( make_pair( snameOrig, new TCanvas(snameOrig.c_str(),snameOrig.c_str(), canv_x,canv_y) ) );
			(*cmap_cutProfile)[snameOrig]->Draw();
			(*cmap_cutProfile)[snameOrig]->cd();
			(*h1map_cutProfile)[sname]->Draw();
			(*cmap_cutProfile)[snameOrig]->Update();
			(*cmap_cutProfile)[snameOrig]->Write();
		}
		cout << "drawn cutProfile: " << sname << endl;
	}
	
	for(TMapSP2TH2D::iterator it=h2map_cutProfile->begin() ; it!=h2map_cutProfile->end() ; ++it)
	{
		sname = it->first;
		sNumber = sname[sname.length()-1];
		
		if(sNumber=="1")
		{
			snameOrig = "cutProfile_" + sname.substr(0, sname.length()-2);
			cmap_cutProfile->insert( make_pair( snameOrig, new TCanvas(snameOrig.c_str(),snameOrig.c_str(), canv_x,canv_y) ) );
			(*cmap_cutProfile)[snameOrig]->Divide(1,2);
			(*cmap_cutProfile)[snameOrig]->Draw();
			(*cmap_cutProfile)[snameOrig]->cd();
			(*cmap_cutProfile)[snameOrig]->cd(1);
			(*h2map_cutProfile)[sname]->Draw("BOX");
		}
		else if(sNumber=="2")
		{
			snameOrig = "cutProfile_" + sname.substr(0, sname.length()-2);
			(*cmap_cutProfile)[snameOrig]->cd(2);
			(*h2map_cutProfile)[sname]->Draw("BOX");
			(*cmap_cutProfile)[snameOrig]->Update();
			(*cmap_cutProfile)[snameOrig]->Write();
		}
		else
		{
			snameOrig = "cutProfile_" + sname;
			cmap_cutProfile->insert( make_pair( snameOrig, new TCanvas(snameOrig.c_str(),snameOrig.c_str(), canv_x,canv_y) ) );
			(*cmap_cutProfile)[snameOrig]->Draw();
			(*cmap_cutProfile)[snameOrig]->cd();
			(*h2map_cutProfile)[sname]->Draw("BOX");
			(*cmap_cutProfile)[snameOrig]->Update();
			(*cmap_cutProfile)[snameOrig]->Write();
		}
		cout << "drawn cutProfile: " << sname << endl;
	}
}








