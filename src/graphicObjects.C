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
	CosThetaDimu = -9999;
	ipTDiff      = -9999;
	EtaSum       = -9999;

	// all cuts - vectors
	charge->clear();
	m->clear();
	e->clear();
	px->clear();
	py->clear();
	pz->clear();
	pt->clear();
	eta->clear();
	phi->clear();
	d0_exPV->clear();
	z0_exPV->clear();
	qoverp_ms->clear();
	theta_ms->clear();
	phi_ms->clear();
	qoverp_me->clear();
	theta_me->clear();
	phi_me->clear();
	qoverp_id->clear();
	theta_id->clear();
	phi_id->clear();
	qoverp_ie->clear();
	theta_ie->clear();
	phi_ie->clear();
	matchchi2->clear();
	matchndof->clear();
	allauthor->clear();
	author->clear();
	isStandAloneMuon->clear();
	isCombinedMuon->clear();
	trackfitchi2->clear();
	trackfitndof->clear();
	
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
	
}

void graphicObjects::writeTrees(TDirectory* tDir_allCuts,
								TDirectory* tDir_cutsProfile,
								TDirectory* tDir_efficiency)
{
	TFile* f = NULL;

	f = tree_allCuts->GetCurrentFile();
	f->cd( tDir_allCuts->GetName() );
	tree_allCuts->Write();
	
	f = tree_cutsProfile->GetCurrentFile();
	f->cd( tDir_cutsProfile->GetName() );
	tree_cutsProfile->Write();
	
	f = tree_efficiency->GetCurrentFile();
	f->cd( tDir_efficiency->GetName() );
	tree_efficiency->Write();
	
	f->Write();
	f->Close();
	
	//tDir_allCuts->cd();
	//tree_allCuts->Write();

	//tDir_cutsProfile->cd();
	//tree_cutsProfile->Write();
	
	//tDir_efficiency->cd();
	//tree_efficiency->Write();
}

void graphicObjects::setTrees(TDirectory* tDir_allCuts,
							  TDirectory* tDir_cutsProfile,
							  TDirectory* tDir_efficiency)
{
	// all cuts - vectors
	vxp_z_profile = new vector<float>;
	vxp_nTracks_profile = new vector<int>;
	charge = new vector<float>;
	m = new vector<float>;
	e = new vector<float>;
	px = new vector<float>;
	py = new vector<float>;
	pz = new vector<float>;
	pt = new vector<float>;
	eta = new vector<float>;
	phi = new vector<float>;
	d0_exPV = new vector<float>;
	z0_exPV = new vector<float>;
	qoverp_ms = new vector<float>;
	theta_ms = new vector<float>;
	phi_ms = new vector<float>;
	qoverp_me = new vector<float>;
	theta_me = new vector<float>;
	phi_me = new vector<float>;
	qoverp_id = new vector<float>;
	theta_id = new vector<float>;
	phi_id = new vector<float>;
	qoverp_ie = new vector<float>;
	theta_ie = new vector<float>;
	phi_ie = new vector<float>;
	matchchi2 = new vector<float>;
	matchndof = new vector<int>;
	allauthor = new vector<unsigned short>;
	author = new vector<int>;
	isStandAloneMuon = new vector<int>;
	isCombinedMuon = new vector<int>;
	trackfitchi2 = new vector<float>;
	trackfitndof = new vector<int>;
	
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
	tree_allCuts->Branch( "Q_T",           &Q_T );
	tree_allCuts->Branch( "CosThetaDimu", &CosThetaDimu );
	tree_allCuts->Branch( "ipTDiff",      &ipTDiff );
	tree_allCuts->Branch( "EtaSum",       &EtaSum );
	// 1 muon (vectors)
	tree_allCuts->Branch( "charge", &charge );
	tree_allCuts->Branch( "m",  &m );
	tree_allCuts->Branch( "e",  &e );
	tree_allCuts->Branch( "px", &px );
	tree_allCuts->Branch( "py", &py );
	tree_allCuts->Branch( "pz", &pz );
	tree_allCuts->Branch( "pt", &pt );
	tree_allCuts->Branch( "eta", &eta );
	tree_allCuts->Branch( "phi", &phi );
	tree_allCuts->Branch( "d0_exPV",  &d0_exPV );
	tree_allCuts->Branch( "z0_exPV",  &z0_exPV );
	tree_allCuts->Branch( "qoverp_ms",  &qoverp_ms );
	tree_allCuts->Branch( "theta_ms",  &theta_ms );
	tree_allCuts->Branch( "phi_ms",  &phi_ms );
	tree_allCuts->Branch( "qoverp_me",  &qoverp_me );
	tree_allCuts->Branch( "theta_me",  &theta_me );
	tree_allCuts->Branch( "phi_me",  &phi_me );
	tree_allCuts->Branch( "qoverp_id",  &qoverp_id );
	tree_allCuts->Branch( "theta_id",  &theta_id );
	tree_allCuts->Branch( "phi_id",  &phi_id );
	tree_allCuts->Branch( "qoverp_ie",  &qoverp_ie );
	tree_allCuts->Branch( "theta_ie",  &theta_ie );
	tree_allCuts->Branch( "phi_ie",  &phi_ie );
	tree_allCuts->Branch( "matchchi2",  &matchchi2 );
	tree_allCuts->Branch( "matchndof",  &matchndof );
	tree_allCuts->Branch( "allauthor",  &allauthor );
	tree_allCuts->Branch( "author",  &author );
	tree_allCuts->Branch( "isStandAloneMuon",  &isStandAloneMuon );
	tree_allCuts->Branch( "isCombinedMuon",  &isCombinedMuon );
	tree_allCuts->Branch( "trackfitchi2",  &trackfitchi2 );
	tree_allCuts->Branch( "trackfitndof",  &trackfitndof );
	
	
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
	TMapsvd::iterator it2=cut_cutFlowMapSVD->find("pT_loose");
	TMapsvd::iterator it3=cut_cutFlowMapSVD->find("pT_qOp+theta");
	TMapsvd::iterator it4=cut_cutFlowMapSVD->find("pT_qOp+theta_loose");
	TMapsvd::iterator it5=cut_cutFlowMapSVD->find("pTandEtaTight");
	TMapsvd::iterator it6=cut_cutFlowMapSVD->find("pTandEtaBarrel");
	TMapsvd::iterator it7=cut_cutFlowMapSVD->find("pTandEta");
	TMapsvd::iterator itEnd=cut_cutFlowMapSVD->end();
	if     ( it1 != itEnd ) pTcutNmae = "pT";
	else if( it2 != itEnd ) pTcutNmae = "pT_loose";
	else if( it3 != itEnd ) pTcutNmae = "pT_qOp+theta";
	else if( it4 != itEnd ) pTcutNmae = "pT_qOp+theta_loose";
	else if( it5 != itEnd ) pTcutNmae = "pTandEtaTight";
	else if( it6 != itEnd ) pTcutNmae = "pTandEtaBarrel";
	else if( it7 != itEnd ) pTcutNmae = "pTandEta";
	else
	{
		cout << "ERROR: in graphicObjects::ginitialize(): pT cut value was not found, exitting now" << endl;
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

void graphicObjects::setStyle()
{
	gROOT->ProcessLine(".x ../src/rootlogon_atlas.C");
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
	h2_xyVertex = new TH2D("xyVertex","xyVertex",   xyVertex_nbins, xyVertex_min, xyVertex_max,
	xyVertex_nbins, xyVertex_min, xyVertex_max);
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
	TMapds::iterator ii;
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
		string sname = it->first;
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
		string sname = it->first;
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








