/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#define analysisModules_cxx
#include "analysisModules.C"

// #define SmearingClass_cxx
// #include "SmearingClass.cxx"

#include "SmearingClass.h"

#include "TPileupReweighting.h"

#ifndef ANALYSISSKELETON_H
#define ANALYSISSKELETON_H

class analysisSkeleton : public analysisModules
{
public:
	//////////////////////
	// basic local vars

	bool AS_isMC;
	SmearingClass* MCPpTsmearing;
	Root::TPileupReweighting* pileuprw;
	
	bool alreadyFilled;
	
	int tmp_counter_1;
	int tmp_counter_2;
	int tmp_counter_3;
	int tmp_counter_4;
	int tmp_counter_5;
	
	int EventHash;
	bool isMultiMuonPrint;
	
	string sMCsampleName;
	
	TMapii muPairMap;
	bool passCutFlow;
	bool passCurrentCut;
	bool twoMusPass;
	bool thisMuPass;
	int cutFlowMapSize;
	int counter;
	int ai;
	int bi;
	int vi;
	int ai_truth;
	int bi_truth;
	int iVtx;
	string sRunType;
	int currentRun;
	string sPeriod;
	string sCurrentPeriod;
	vector<string>* vTriggers;
	vector<bool> muQAflags;
	int nMusPassed;
	TMapdi  pTtoIndexMap;
	TMapdi  pTtoIndexMapTruth;
	TVectorP2VL	pmu;
	TVectorP2VL pmuTruth;
	TMapsd values2fill;
	int nMultiMuonEvents;
	bool inApplySingleSelection;
	ofstream* fCand;
	string sTriggerName;
	
	// tirg, local
	vector<int>*   mu_LLT_index;
	vector<float>* mu_LLT_dr;
	vector<float>* LLT_pt;
	vector<float>* LLT_phi;
	vector<float>* LLT_eta;
	
	vector<int>*   mu_HLT_index;
	vector<float>* mu_HLT_dr;
	vector<vector<float> >* HLT_pt;
	vector<vector<float> >* HLT_phi;
	vector<vector<float> >* HLT_eta;
	vector<vector<int> >*   HLT_has;
	
	
	// counter local
	int m_trees_counter_mod;
	int m_allCuts_counter;
	int m_cutsProfile_counter;
	int m_efficiency_counter;
	int m_truth_counter;
	
	// MCP smeared muon pT for MC only
	vector<double>* mu_MCP_ptcb; // same as mu_pt
	vector<double>* mu_MCP_ptms;
	vector<double>* mu_MCP_ptid;
	

	// event level
	int isGRL;
	int RunNumber;
	int EventNumber;
	int timestamp;
	int timestamp_ns;
	int lbn;
	int bcid;
	int detmask0;
	int detmask1;
	int pixelFlags;
	int sctFlags;
	int trtFlags;
	int larFlags;
	int tileFlags;
	int muonFlags;
	int fwdFlags;
	int coreFlags;
	int pixelError;
	int sctError;
	int trtError;
	int larError;
	int tileError;
	int muonError;
	int fwdError;
	int coreError;
	
	float actualIntPerXing;
	float averageIntPerXing;
	unsigned int mc_channel_number;
	unsigned int mc_event_number;
	double mc_event_weight;
	
	float pileup_weight;
	float EW_kfactor_weight;
	float QCD_kfactor_weight;
	float mcevent_weight;
	float total_weight;
	
	// L1 triggers
	bool L1_MU10;
	bool L1_MU11;

	
	// EF triggers	
	bool EF_mu18;
	bool EF_mu18_MG;
	bool EF_mu18_medium;
	bool EF_mu18_MG_medium;
	bool EF_mu22;
	bool EF_mu22_MG;
	bool EF_mu22_medium;
	bool EF_mu22_MG_medium;
	bool EF_mu40_MSonly_barrel;
	bool EF_mu40_MSonly_barrel_medium;

	
	// vertexes (for the PV preselection)
	int vxp_n;
	vector<int>*   vxp_nTracks;
	vector<int>*   vxp_type;
	vector<float>* vxp_z;
	
	Int_t           mu_n;
	vector<float>   *mu_E;
	vector<float>   *mu_pt;
	vector<float>   *mu_m;
	vector<float>   *mu_eta;
	vector<float>   *mu_phi;
	vector<float>   *mu_px;
	vector<float>   *mu_py;
	vector<float>   *mu_pz;
	vector<float>   *mu_charge;
	vector<unsigned short> *mu_allauthor;
	vector<int>     *mu_author;
	vector<float>   *mu_beta;
	vector<float>   *mu_isMuonLikelihood;
	vector<float>   *mu_matchchi2;
	vector<int>     *mu_matchndof;
	vector<float>   *mu_etcone20;
	vector<float>   *mu_etcone30;
	vector<float>   *mu_etcone40;
	vector<float>   *mu_nucone20;
	vector<float>   *mu_nucone30;
	vector<float>   *mu_nucone40;
	vector<float>   *mu_ptcone20;
	vector<float>   *mu_ptcone30;
	vector<float>   *mu_ptcone40;
	vector<float>   *mu_energyLossPar;
	vector<float>   *mu_energyLossErr;
	vector<float>   *mu_etCore;
	vector<float>   *mu_energyLossType;
	vector<unsigned short> *mu_caloMuonIdTag;
	vector<double>  *mu_caloLRLikelihood;
	vector<int>     *mu_bestMatch;
	vector<int>     *mu_isStandAloneMuon;
	vector<int>     *mu_isCombinedMuon;
	vector<int>     *mu_isLowPtReconstructedMuon;
	vector<int>     *mu_loose;
	vector<int>     *mu_medium;
	vector<int>     *mu_tight;
	vector<float>   *mu_d0_exPV;
	vector<float>   *mu_z0_exPV;
	vector<float>   *mu_phi_exPV;
	vector<float>   *mu_theta_exPV;
	vector<float>   *mu_qoverp_exPV;
	vector<float>   *mu_cb_d0_exPV;
	vector<float>   *mu_cb_z0_exPV;
	vector<float>   *mu_cb_phi_exPV;
	vector<float>   *mu_cb_theta_exPV;
	vector<float>   *mu_cb_qoverp_exPV;
	vector<float>   *mu_id_d0_exPV;
	vector<float>   *mu_id_z0_exPV;
	vector<float>   *mu_id_phi_exPV;
	vector<float>   *mu_id_theta_exPV;
	vector<float>   *mu_id_qoverp_exPV;
	vector<float>   *mu_me_d0_exPV;
	vector<float>   *mu_me_z0_exPV;
	vector<float>   *mu_me_phi_exPV;
	vector<float>   *mu_me_theta_exPV;
	vector<float>   *mu_me_qoverp_exPV;
	vector<float>   *mu_ie_d0_exPV;
	vector<float>   *mu_ie_z0_exPV;
	vector<float>   *mu_ie_phi_exPV;
	vector<float>   *mu_ie_theta_exPV;
	vector<float>   *mu_ie_qoverp_exPV;
	vector<vector<int> > *mu_SpaceTime_detID;
	vector<vector<float> > *mu_SpaceTime_t;
	vector<vector<float> > *mu_SpaceTime_tError;
	vector<vector<float> > *mu_SpaceTime_weight;
	vector<vector<float> > *mu_SpaceTime_x;
	vector<vector<float> > *mu_SpaceTime_y;
	vector<vector<float> > *mu_SpaceTime_z;
	vector<vector<float> > *mu_SpaceTime_t_Tile;
	vector<vector<float> > *mu_SpaceTime_tError_Tile;
	vector<vector<float> > *mu_SpaceTime_weight_Tile;
	vector<vector<float> > *mu_SpaceTime_x_Tile;
	vector<vector<float> > *mu_SpaceTime_y_Tile;
	vector<vector<float> > *mu_SpaceTime_z_Tile;
	vector<vector<float> > *mu_SpaceTime_t_TRT;
	vector<vector<float> > *mu_SpaceTime_tError_TRT;
	vector<vector<float> > *mu_SpaceTime_weight_TRT;
	vector<vector<float> > *mu_SpaceTime_x_TRT;
	vector<vector<float> > *mu_SpaceTime_y_TRT;
	vector<vector<float> > *mu_SpaceTime_z_TRT;
	vector<vector<float> > *mu_SpaceTime_t_MDT;
	vector<vector<float> > *mu_SpaceTime_tError_MDT;
	vector<vector<float> > *mu_SpaceTime_weight_MDT;
	vector<vector<float> > *mu_SpaceTime_x_MDT;
	vector<vector<float> > *mu_SpaceTime_y_MDT;
	vector<vector<float> > *mu_SpaceTime_z_MDT;
	vector<float>   *mu_TileCellEnergyLayer1;
	vector<float>   *mu_TileTimeLayer1;
	vector<float>   *mu_TileCellRmsNoiseLayer1;
	vector<float>   *mu_TileCellSignLayer1;
	vector<float>   *mu_TileCellEnergyLayer2;
	vector<float>   *mu_TileTimeLayer2;
	vector<float>   *mu_TileCellRmsNoiseLayer2;
	vector<float>   *mu_TileCellSignLayer2;
	vector<float>   *mu_TileCellEnergyLayer3;
	vector<float>   *mu_TileTimeLayer3;
	vector<float>   *mu_TileCellRmsNoiseLayer3;
	vector<float>   *mu_TileCellSignLayer3;
	vector<float>   *mu_MSTrkT0_1;
	vector<float>   *mu_MSTrkT0_2;
	vector<float>   *mu_MSTrkT0_3;
	vector<float>   *mu_cov_d0_exPV;
	vector<float>   *mu_cov_z0_exPV;
	vector<float>   *mu_cov_phi_exPV;
	vector<float>   *mu_cov_theta_exPV;
	vector<float>   *mu_cov_qoverp_exPV;
	vector<float>   *mu_cov_d0_z0_exPV;
	vector<float>   *mu_cov_d0_phi_exPV;
	vector<float>   *mu_cov_d0_theta_exPV;
	vector<float>   *mu_cov_d0_qoverp_exPV;
	vector<float>   *mu_cov_z0_phi_exPV;
	vector<float>   *mu_cov_z0_theta_exPV;
	vector<float>   *mu_cov_z0_qoverp_exPV;
	vector<float>   *mu_cov_phi_theta_exPV;
	vector<float>   *mu_cov_phi_qoverp_exPV;
	vector<float>   *mu_cov_theta_qoverp_exPV;
	vector<float>   *mu_id_cov_d0_exPV;
	vector<float>   *mu_id_cov_z0_exPV;
	vector<float>   *mu_id_cov_phi_exPV;
	vector<float>   *mu_id_cov_theta_exPV;
	vector<float>   *mu_id_cov_qoverp_exPV;
	vector<float>   *mu_id_cov_d0_z0_exPV;
	vector<float>   *mu_id_cov_d0_phi_exPV;
	vector<float>   *mu_id_cov_d0_theta_exPV;
	vector<float>   *mu_id_cov_d0_qoverp_exPV;
	vector<float>   *mu_id_cov_z0_phi_exPV;
	vector<float>   *mu_id_cov_z0_theta_exPV;
	vector<float>   *mu_id_cov_z0_qoverp_exPV;
	vector<float>   *mu_id_cov_phi_theta_exPV;
	vector<float>   *mu_id_cov_phi_qoverp_exPV;
	vector<float>   *mu_id_cov_theta_qoverp_exPV;
	vector<float>   *mu_me_cov_d0_exPV;
	vector<float>   *mu_me_cov_z0_exPV;
	vector<float>   *mu_me_cov_phi_exPV;
	vector<float>   *mu_me_cov_theta_exPV;
	vector<float>   *mu_me_cov_qoverp_exPV;
	vector<float>   *mu_me_cov_d0_z0_exPV;
	vector<float>   *mu_me_cov_d0_phi_exPV;
	vector<float>   *mu_me_cov_d0_theta_exPV;
	vector<float>   *mu_me_cov_d0_qoverp_exPV;
	vector<float>   *mu_me_cov_z0_phi_exPV;
	vector<float>   *mu_me_cov_z0_theta_exPV;
	vector<float>   *mu_me_cov_z0_qoverp_exPV;
	vector<float>   *mu_me_cov_phi_theta_exPV;
	vector<float>   *mu_me_cov_phi_qoverp_exPV;
	vector<float>   *mu_me_cov_theta_qoverp_exPV;
	vector<float>   *mu_ms_d0;
	vector<float>   *mu_ms_z0;
	vector<float>   *mu_ms_phi;
	vector<float>   *mu_ms_theta;
	vector<float>   *mu_ms_qoverp;
	vector<float>   *mu_id_d0;
	vector<float>   *mu_id_z0;
	vector<float>   *mu_id_phi;
	vector<float>   *mu_id_theta;
	vector<float>   *mu_id_qoverp;
	vector<float>   *mu_me_d0;
	vector<float>   *mu_me_z0;
	vector<float>   *mu_me_phi;
	vector<float>   *mu_me_theta;
	vector<float>   *mu_me_qoverp;
	vector<float>   *mu_ie_d0;
	vector<float>   *mu_ie_z0;
	vector<float>   *mu_ie_phi;
	vector<float>   *mu_ie_theta;
	vector<float>   *mu_ie_qoverp;
	vector<int>     *mu_nOutliersOnTrack;
	vector<int>     *mu_nBLHits;
	vector<int>     *mu_nPixHits;
	vector<int>     *mu_nSCTHits;
	vector<int>     *mu_nTRTHits;
	vector<int>     *mu_nTRTHighTHits;
	vector<int>     *mu_nBLSharedHits;
	vector<int>     *mu_nPixSharedHits;
	vector<int>     *mu_nPixHoles;
	vector<int>     *mu_nSCTSharedHits;
	vector<int>     *mu_nSCTHoles;
	vector<int>     *mu_nTRTOutliers;
	vector<int>     *mu_nTRTHighTOutliers;
	vector<int>     *mu_nGangedPixels;
	vector<int>     *mu_nPixelDeadSensors;
	vector<int>     *mu_nSCTDeadSensors;
	vector<int>     *mu_nTRTDeadStraws;
	vector<int>     *mu_expectBLayerHit;
	vector<int>     *mu_nMDTHits;
	vector<int>     *mu_nMDTHoles;
	vector<int>     *mu_nCSCEtaHits;
	vector<int>     *mu_nCSCEtaHoles;
	vector<int>     *mu_nCSCPhiHits;
	vector<int>     *mu_nCSCPhiHoles;
	vector<int>     *mu_nRPCEtaHits;
	vector<int>     *mu_nRPCEtaHoles;
	vector<int>     *mu_nRPCPhiHits;
	vector<int>     *mu_nRPCPhiHoles;
	vector<int>     *mu_nTGCEtaHits;
	vector<int>     *mu_nTGCEtaHoles;
	vector<int>     *mu_nTGCPhiHits;
	vector<int>     *mu_nTGCPhiHoles;
	vector<int>     *mu_nMDTBIHits;
	vector<int>     *mu_nMDTBMHits;
	vector<int>     *mu_nMDTBOHits;
	vector<int>     *mu_nMDTBEEHits;
	vector<int>     *mu_nMDTBIS78Hits;
	vector<int>     *mu_nMDTEIHits;
	vector<int>     *mu_nMDTEMHits;
	vector<int>     *mu_nMDTEOHits;
	vector<int>     *mu_nMDTEEHits;
	vector<int>     *mu_nRPCLayer1EtaHits;
	vector<int>     *mu_nRPCLayer2EtaHits;
	vector<int>     *mu_nRPCLayer3EtaHits;
	vector<int>     *mu_nRPCLayer1PhiHits;
	vector<int>     *mu_nRPCLayer2PhiHits;
	vector<int>     *mu_nRPCLayer3PhiHits;
	vector<int>     *mu_nTGCLayer1EtaHits;
	vector<int>     *mu_nTGCLayer2EtaHits;
	vector<int>     *mu_nTGCLayer3EtaHits;
	vector<int>     *mu_nTGCLayer4EtaHits;
	vector<int>     *mu_nTGCLayer1PhiHits;
	vector<int>     *mu_nTGCLayer2PhiHits;
	vector<int>     *mu_nTGCLayer3PhiHits;
	vector<int>     *mu_nTGCLayer4PhiHits;
	vector<int>     *mu_barrelSectors;
	vector<int>     *mu_endcapSectors;
	vector<float>   *mu_trackd0;
	vector<float>   *mu_trackz0;
	vector<float>   *mu_trackphi;
	vector<float>   *mu_tracktheta;
	vector<float>   *mu_trackqoverp;
	vector<float>   *mu_trackcov_d0;
	vector<float>   *mu_trackcov_z0;
	vector<float>   *mu_trackcov_phi;
	vector<float>   *mu_trackcov_theta;
	vector<float>   *mu_trackcov_qoverp;
	vector<float>   *mu_trackcov_d0_z0;
	vector<float>   *mu_trackcov_d0_phi;
	vector<float>   *mu_trackcov_d0_theta;
	vector<float>   *mu_trackcov_d0_qoverp;
	vector<float>   *mu_trackcov_z0_phi;
	vector<float>   *mu_trackcov_z0_theta;
	vector<float>   *mu_trackcov_z0_qoverp;
	vector<float>   *mu_trackcov_phi_theta;
	vector<float>   *mu_trackcov_phi_qoverp;
	vector<float>   *mu_trackcov_theta_qoverp;
	vector<float>   *mu_trackfitchi2;
	vector<int>     *mu_trackfitndof;
	vector<int>     *mu_hastrack;
	vector<float>   *mu_EFCB_dr;
	vector<int>     *mu_EFCB_index;
	vector<float>   *mu_EFMG_dr;
	vector<int>     *mu_EFMG_index;
	vector<float>   *mu_EFME_dr;
	vector<int>     *mu_EFME_index;
	vector<float>   *mu_L2CB_dr;
	vector<int>     *mu_L2CB_index;
	vector<float>   *mu_L1_dr;
	vector<int>     *mu_L1_index;
	
	
	// * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * *
	// Monte Carlo truth
	// staco/muid truth
	vector<float>   *mu_truth_dr;
	vector<float>   *mu_truth_E;
	vector<float>   *mu_truth_pt;
	vector<float>   *mu_truth_eta;
	vector<float>   *mu_truth_phi;
	vector<int>     *mu_truth_type;
	vector<int>     *mu_truth_status;
	vector<int>     *mu_truth_barcode;
	vector<int>     *mu_truth_mothertype;
	vector<int>     *mu_truth_motherbarcode;
	vector<int>     *mu_truth_matched;
	
	// muonTruth
	int              muonTruth_n;
	vector<float>*   muonTruth_pt;
	vector<float>*   muonTruth_m;
	vector<float>*   muonTruth_eta;
	vector<float>*   muonTruth_phi;
	vector<float>*   muonTruth_charge;
	vector<int>*     muonTruth_PDGID;
	vector<int>*     muonTruth_barcode;
	vector<int>*     muonTruth_type;
	vector<int>*     muonTruth_origin;
	
	// MC event
	int              mcevt_n;
	vector<int>*     mcevt_signal_process_id;
	vector<int>*     mcevt_event_number;
	vector<double>*  mcevt_event_scale;
	vector<double>*  mcevt_alphaQCD;
	vector<double>*  mcevt_alphaQED;
	vector<int>*     mcevt_pdf_id1;
	vector<int>*     mcevt_pdf_id2;
	vector<double>*  mcevt_pdf_x1;
	vector<double>*  mcevt_pdf_x2;
	vector<double>*  mcevt_pdf_scale;
	vector<double>*  mcevt_pdf1;
	vector<double>*  mcevt_pdf2;
	vector<double>*  mcevt_weight;
	
	//MC
	int            mc_n;
	vector<float>* mc_pt;
	vector<float>* mc_m;
	vector<float>* mc_eta;
	vector<float>* mc_phi;
	vector<int>*   mc_status;
	vector<int>*   mc_barcode;
	vector<vector<int> >* mc_parents;
	vector<vector<int> >* mc_children;
	vector<int>*   mc_pdgId;
	vector<float>* mc_charge;
	vector<float>* mc_vx_x;
	vector<float>* mc_vx_y;
	vector<float>* mc_vx_z;
	vector<vector<int> >* mc_child_index;
	vector<vector<int> >* mc_parent_index;
	
	// triggers
	Int_t           trig_L1_mu_n;
	vector<float>   *trig_L1_mu_pt;
	vector<float>   *trig_L1_mu_eta;
	vector<float>   *trig_L1_mu_phi;
	vector<string>  *trig_L1_mu_thrName;
	
	// EF: CB, MS, SA
	Int_t           	 trig_EF_trigmuonef_n;
	vector<int>     	 *trig_EF_trigmuonef_track_n;
	vector<vector<int> > *trig_EF_trigmuonef_track_MuonType;
	
	vector<vector<float> > *trig_EF_trigmuonef_track_MS_pt;
	vector<vector<float> > *trig_EF_trigmuonef_track_MS_eta;
	vector<vector<float> > *trig_EF_trigmuonef_track_MS_phi;
	vector<vector<int> >   *trig_EF_trigmuonef_track_MS_hasMS;
	
	vector<vector<float> > *trig_EF_trigmuonef_track_SA_pt;
	vector<vector<float> > *trig_EF_trigmuonef_track_SA_eta;
	vector<vector<float> > *trig_EF_trigmuonef_track_SA_phi;
	vector<vector<int> >   *trig_EF_trigmuonef_track_SA_hasSA;
	
	vector<vector<float> > *trig_EF_trigmuonef_track_CB_pt;
	vector<vector<float> > *trig_EF_trigmuonef_track_CB_eta;
	vector<vector<float> > *trig_EF_trigmuonef_track_CB_phi;
	vector<vector<int> >   *trig_EF_trigmuonef_track_CB_hasCB;
	
	// EF: MG
	Int_t           	   trig_EF_trigmugirl_n;
	vector<int>     	   *trig_EF_trigmugirl_track_n;
	vector<vector<int> >   *trig_EF_trigmugirl_track_MuonType;
	
	vector<vector<float> > *trig_EF_trigmugirl_track_MS_pt;
	vector<vector<float> > *trig_EF_trigmugirl_track_MS_eta;
	vector<vector<float> > *trig_EF_trigmugirl_track_MS_phi;
	vector<vector<int> >   *trig_EF_trigmugirl_track_MS_hasMS;
	
	vector<vector<float> > *trig_EF_trigmugirl_track_SA_pt;
	vector<vector<float> > *trig_EF_trigmugirl_track_SA_eta;
	vector<vector<float> > *trig_EF_trigmugirl_track_SA_phi;
	vector<vector<int> >   *trig_EF_trigmugirl_track_SA_hasSA;
	
	vector<vector<float> > *trig_EF_trigmugirl_track_CB_pt;
	vector<vector<float> > *trig_EF_trigmugirl_track_CB_eta;
	vector<vector<float> > *trig_EF_trigmugirl_track_CB_phi;
	vector<vector<int> >   *trig_EF_trigmugirl_track_CB_hasCB;
	
	// * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * *
	// muon variables for selection
	
	////////////////////////
	// more variables
	float current_imass;
	float current_cosTheta;
	float current_cosThetaHE;
	float current_cosThetaCS;
	float current_ySystem;
	float current_QT;
	float current_betaQ;
	float current_betazQ;
	float current_betaTQ;
	float current_cosmicCosth;
	float current_ipTdiff;
	float current_etaSum;
	float current_pTdiff;
	float current_pTdiff_muplus;
	float current_pTratio;
	float current_pTratio_muplus;
	float current_pTres;
	float current_pTres_muplus;
	float current_mu_pT;
	float current_muplus_pT;
	float current_mu_me_pT;
	float current_muplus_me_pT;
	float current_mu_id_pT;
	float current_muplus_id_pT;
	float current_mu_eta;
	float current_muplus_eta;
	float current_mu_me_qop;
	float current_muplus_me_qop;
	float current_mu_id_qop;
	float current_muplus_id_qop;
	float current_mu_me_theta;
	float current_muplus_me_theta;
	float current_mu_id_theta;
	float current_muplus_id_theta;
	int   current_ivertex;

public:
	analysisSkeleton();
	analysisSkeleton(string sEventDumpFilePath) :
	analysisModules(sEventDumpFilePath)
	{
		tmp_counter_1 = 0;
		tmp_counter_2 = 0;
		tmp_counter_3 = 0;
		tmp_counter_4 = 0;
		tmp_counter_5 = 0;

		currentRun = 0;
		sCurrentPeriod = "";
		nMultiMuonEvents = 0;
		
		mu_MCP_ptcb = new vector<double>; // same as mu_pt (after smearing)
		mu_MCP_ptms = new vector<double>;
		mu_MCP_ptid = new vector<double>;
	}
	~analysisSkeleton();
	
	void setMC(bool isMC) { AS_isMC = isMC; }
	void setSmearedMCPpT(int nMus);
	void setMCPpTparameters(string sAlgo, string spTtype, string sDataPath);
	void setPileupParameters(TString dataRootFileName, TString dataRootHistName, TString mcRootFileName, TString mcRootHistName);
	float getPileUpWeight();
	
	void setPtCandidatesFile(string sCandFilePath = "", string srunnumber = "");
	
	void resetMuQAflags(int nMus);
	int  countQAflags();
	void pTSort();
	void pTSort(TMapdi& pTtoIndex, int& index_a, int& index_b, vector<float>* charge);
	void imassSort();
	bool assignPairIndices();
	
	string          getPeriodName();
	string          getPeriodName(int run);
	vector<string>* getPeriodTriggers();
	bool            isTrigger(string trigName);
	void            matchTrigger(string speriod, string sTrigType);
	bool            checkTrigger(float trigThreshold);
	void 			printAllProperties(int ai, int bi, int iv);
	
	//void buildMU4Vector(int nMus);
	void buildMU4Vector(int nMus);
	void wipeMU4Vector();
	
	bool applyPreselection();
	bool applySingleMuonSelection();
	bool applyDoubleMuonSelection();
	
	void fillCutProfile1D();
	void fillCutProfile2D();
	void fillCutProfile();
	
	//void fillTagNProbe();
	inline void fill_tNp();
	inline void fillTruthEfficiency();
	
	inline void fillTruth();
	inline void fillRecon();
	
	void applyTagNProbe(TMapsb& cutsToSkip);
	
	void applyTruth();

private:
	void runEventDumper();
	
	bool preselection(string sSkipCut);
	bool singleSelection(string sSkipCut);
	bool doubleSelection(string sSkipCut);
	
	inline bool throwInfo(string cutName);
	
	inline bool preselection(TMapsb& cutsToSkip);
	inline bool singleSelection(TMapsb& cutsToSkip);
	inline bool doubleSelection(TMapsb& cutsToSkip);
	
	void fillAfterCuts();
	void fillBeforeCuts();
	void fillCutFlow(string sorderedcutname);

};
#endif

