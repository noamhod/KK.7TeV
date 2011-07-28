/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#ifndef GRAPHICOBJECTS_H
#define GRAPHICOBJECTS_H

class graphicObjects// : public utilities
{
	public:
		TTree* tree_allCuts;
		TTree* tree_cutsProfile;
		TTree* tree_efficiency;
		TTree* tree_truth;
	
	
		// canvases
		TCanvas* cnv_imass;
		TCanvas* cnv_pT;
		TCanvas* cnv_eta;
		TCanvas* cnv_costh;
		TCanvas* cnv_d0exPV;
		TCanvas* cnv_z0exPV;
		TCanvas* cnv_cosmicCosth;
		TCanvas* cnv_xyVertex;
		TCanvas* cnv_imassFit;
		TCanvas* cnv_ipTdiff;
		TCanvas* cnv_etaSum;
		TCanvas* cnv_pTdiff;
		TCanvas* cnv_pTratio;
		TCanvas* cnv_pTmevspTid;
		TCanvas* cnv_pTres;
		TCanvas* cnv_Afb;
		TCanvas* cnv_efficiency_pT;
		TCanvas* cnv_efficiency_eta;
		TCanvas* cnv_efficiency_phi;
		
		// pads
		TVirtualPad* pad_pT;
		TVirtualPad* pad_eta;
		TVirtualPad* pad_pT_muplus;
		TVirtualPad* pad_eta_muplus;
		TVirtualPad* pad_cosmicCosth;
		TVirtualPad* pad_cosmicCosthAllCuts;
		TVirtualPad* pad_pTdiff;
		TVirtualPad* pad_pTdiff_muplus;
		TVirtualPad* pad_pTratio;
		TVirtualPad* pad_pTratio_muplus;
		TVirtualPad* pad_pTmevspTid;
		TVirtualPad* pad_pTmevspTid_muplus;
		TVirtualPad* pad_pTres;
		TVirtualPad* pad_pTres_muplus;
		TVirtualPad* pad_candidates_pT;
		TVirtualPad* pad_succeeded_pT;
		TVirtualPad* pad_efficiency_pT;
		TVirtualPad* pad_candidates_eta;
		TVirtualPad* pad_succeeded_eta;
		TVirtualPad* pad_efficiency_eta;
		TVirtualPad* pad_candidates_phi;
		TVirtualPad* pad_succeeded_phi;
		TVirtualPad* pad_efficiency_phi;

		// histos
		TH1D* h1_imass;
		TH1D* h1_pT;
		TH1D* h1_pT_muplus;
		TH1D* h1_eta;
		TH1D* h1_eta_muplus;
		TH1D* h1_costh;
		TH1D* h1_d0exPV;
		TH1D* h1_z0exPV;
		TH1D* h1_cosmicCosth;
		TH1D* h1_cosmicCosthAllCuts;
		TH2D* h2_xyVertex;
		TH1D* h1_imassFit;
		TH1D* h1_ipTdiff;
		TH1D* h1_etaSum;
		TH1D* h1_pTdiff;
		TH1D* h1_pTdiff_muplus;
		TH1D* h1_pTratio;
		TH1D* h1_pTratio_muplus;
		TH1D* h1_pTres;
		TH1D* h1_pTres_muplus;
		TH2D* h2_pTmevspTid;
		TH2D* h2_pTmevspTid_muplus;
		TH1D* h1_Afb;
		
		// For the graphs
		Int_t nentries;
		TCanvas* cMemoryMonitor;
		TGraph*  gResMemoryMonitor;
		TGraph*  gVirMemoryMonitor;
		Double_t* resMemoryArray;
		Double_t* virMemoryArray;
		Double_t* entryArray;

		// canvases for cut flows
		TCanvas* cnv_cutFlow_imass;
		TCanvas* cnv_cutFlow_pT;

		// legends for the cut flow histod
		TLegend* leg_cutFlow_imass;
		TLegend* leg_cutFlow_pT;
		TLegend* leg_imassFit;
		TLegend* leg_ipTdiff;
		TLegend* leg_memory;

		// map of histos
		TMapSP2TH1D* h1map_cutProfile;
		TMapSP2TH2D* h2map_cutProfile;
		TMapSP2TH1D* hmap_cutFlow_imass;
		TMapSP2TH1D* hmap_cutFlow_pT;
		
		TMapSP2TH1D* h1map_tagNprobe_candidates_pT;
		TMapSP2TH1D* h1map_tagNprobe_succeeded_pT;
		TMapSP2TH1D* h1map_tagNprobe_trigEff_pT;
		TMapSP2TH1D* h1map_tagNprobe_candidates_eta;
		TMapSP2TH1D* h1map_tagNprobe_succeeded_eta;
		TMapSP2TH1D* h1map_tagNprobe_trigEff_eta;
		TMapSP2TH1D* h1map_tagNprobe_candidates_phi;
		TMapSP2TH1D* h1map_tagNprobe_succeeded_phi;
		TMapSP2TH1D* h1map_tagNprobe_trigEff_phi;
		
		TMapSP2TH1D* h1map_truth_candidates_pT;
		TMapSP2TH1D* h1map_truth_succeeded_pT;
		TMapSP2TH1D* h1map_truth_trigEff_pT;
		TMapSP2TH1D* h1map_truth_candidates_eta;
		TMapSP2TH1D* h1map_truth_succeeded_eta;
		TMapSP2TH1D* h1map_truth_trigEff_eta;
		TMapSP2TH1D* h1map_truth_candidates_phi;
		TMapSP2TH1D* h1map_truth_succeeded_phi;
		TMapSP2TH1D* h1map_truth_trigEff_phi;
		
		// map of canvases
		TMapSP2TCNV* cmap_cutProfile;
		
		// map of cutFlow
		TMapsvd* cut_cutFlowMapSVD;
		
		// for the canvases
		Int_t    canv_x;
		Int_t    canv_y;
	
		// for the legends
		Double_t leg_x1;
		Double_t leg_x2;
		Double_t leg_y1;
		Double_t leg_y2;
			
		// for the histos
		Int_t    imass_nbins;
		Double_t imass_min;
		Double_t imass_min_cut;
		Double_t imass_max;
		Double_t imass_max_cut;
		
		Int_t imass_fit_nbins;
		Double_t imass_fit_min;
		Double_t imass_fit_max;

		Int_t    pT_nbins;
		Double_t pT_min;
		Double_t pT_min_cut;
		Double_t pT_max;
		Double_t pT_max_cut;
		
		// logarithmic boundries and bins of histograms
		Double_t logMmin;
		Double_t logMmin_cut;
		Double_t logMmax;
		Double_t logMmax_cut;
		Double_t M_binwidth;
		Double_t M_binwidth_cut;
		Double_t M_bins[100+1]; // M_bins[imass_nbins+1]; !!!!!!!!!!!!
		Double_t M_bins_cut[100+1]; // M_bins[imass_nbins+1]; !!!!!!!!!!!!

		Double_t logpTmin;
		Double_t logpTmin_cut;
		Double_t logpTmax;
		Double_t logpTmax_cut;
		Double_t pT_binwidth;
		Double_t pT_binwidth_cut;
		Double_t pT_bins[100+1]; //pT_bins[pT_nbins+1]; !!!!!!!!!!!!!!!
		Double_t pT_bins_cut[100+1]; //pT_bins[pT_nbins+1]; !!!!!!!!!!!!!!!
		
		Int_t phi_nbins;
		Double_t phi_min;
		Double_t phi_max;
		
		Int_t eta_nbins;
		Double_t eta_min;
		Double_t eta_max;
		
		Int_t costh_nbins;
		Double_t costh_min;
		Double_t costh_max;

		Int_t d0exPV_nbins;
		Double_t d0exPV_min;
		Double_t d0exPV_max;
	
		Int_t z0exPV_nbins;
		Double_t z0exPV_min;
		Double_t z0exPV_max;

		Int_t cosmicCosth_nbins;
		Double_t cosmicCosth_min;
		Double_t cosmicCosth_max;

		Int_t xyVertex_nbins;
		Double_t xyVertex_min;
		Double_t xyVertex_max;
	
		Int_t ipTdiff_nbins;
		Double_t ipTdiff_min;
		Double_t ipTdiff_max;
		
		Int_t etaSum_nbins;
		Double_t etaSum_min;
		Double_t etaSum_max;
		
		Int_t pTdiff_nbins;
		Double_t pTdiff_min;
		Double_t pTdiff_max;
		
		Int_t pTratio_nbins;
		Double_t pTratio_min;
		Double_t pTratio_max;
		
		Int_t pTmevspTid_nbins;
		Double_t pTmevspTid_min;
		Double_t pTmevspTid_max;
		
		Int_t pTres_nbins;
		Double_t pTres_min;
		Double_t pTres_max;
		
		Int_t Afb_nbins;
		Double_t Afb_min;
		Double_t Afb_max;
		
		Int_t tagNprobe_pT_nbins;
		Double_t tagNprobe_pT_min;
		Double_t tagNprobe_pT_max;
		
		//--------------------------------
		//--- for the trees
		// all cuts - floats
		int RunNumber;
		int EventNumber;
		int timestamp;
		int timestamp_ns;
		int lbn;
		int bcid;
		
		int iLeadingMuon;
		int iSubLeadingMuon;
		int ivxp;
		
		int vxp_n;
		vector<int>*   vxp_nTracks;
		vector<int>*   vxp_type;
		vector<float>* vxp_z;
		
		Int_t          n;
		vector<float>* E;
		vector<float>* pt;
		vector<float>* m;
		vector<float>* eta;
		vector<float>* phi;
		vector<float>* px;
		vector<float>* py;
		vector<float>* pz;
		vector<float>* charge;
		vector<unsigned short>* allauthor;
		vector<int>* author;
		vector<float>* beta;
		vector<float>* isMuonLikelihood;
		vector<float>* matchchi2;
		vector<int>* matchndof;
		vector<float>* etcone20;
		vector<float>* etcone30;
		vector<float>* etcone40;
		vector<float>* nucone20;
		vector<float>* nucone30;
		vector<float>* nucone40;
		vector<float>* ptcone20;
		vector<float>* ptcone30;
		vector<float>* ptcone40;
		vector<float>* energyLossPar;
		vector<float>* energyLossErr;
		vector<float>* etCore;
		vector<float>* energyLossType;
		vector<unsigned short>* caloMuonIdTag;
		vector<double>*caloLRLikelihood;
		vector<int>* bestMatch;
		vector<int>* isStandAloneMuon;
		vector<int>* isCombinedMuon;
		vector<int>* isLowPtReconstructedMuon;
		vector<int>* loose;
		vector<int>* medium;
		vector<int>* tight;
		vector<float>* d0_exPV;
		vector<float>* z0_exPV;
		vector<float>* phi_exPV;
		vector<float>* theta_exPV;
		vector<float>* qoverp_exPV;
		vector<float>* cb_d0_exPV;
		vector<float>* cb_z0_exPV;
		vector<float>* cb_phi_exPV;
		vector<float>* cb_theta_exPV;
		vector<float>* cb_qoverp_exPV;
		vector<float>* id_d0_exPV;
		vector<float>* id_z0_exPV;
		vector<float>* id_phi_exPV;
		vector<float>* id_theta_exPV;
		vector<float>* id_qoverp_exPV;
		vector<float>* me_d0_exPV;
		vector<float>* me_z0_exPV;
		vector<float>* me_phi_exPV;
		vector<float>* me_theta_exPV;
		vector<float>* me_qoverp_exPV;
		vector<float>* ie_d0_exPV;
		vector<float>* ie_z0_exPV;
		vector<float>* ie_phi_exPV;
		vector<float>* ie_theta_exPV;
		vector<float>* ie_qoverp_exPV;
		//vector<vector<int> >* SpaceTime_detID;
		//vector<vector<float> >* SpaceTime_t;
		//vector<vector<float> >* SpaceTime_tError;
		//vector<vector<float> >* SpaceTime_weight;
		//vector<vector<float> >* SpaceTime_x;
		//vector<vector<float> >* SpaceTime_y;
		//vector<vector<float> >* SpaceTime_z;
		//vector<vector<float> >* SpaceTime_t_Tile;
		//vector<vector<float> >* SpaceTime_tError_Tile;
		//vector<vector<float> >* SpaceTime_weight_Tile;
		//vector<vector<float> >* SpaceTime_x_Tile;
		//vector<vector<float> >* SpaceTime_y_Tile;
		//vector<vector<float> >* SpaceTime_z_Tile;
		//vector<vector<float> >* SpaceTime_t_TRT;
		//vector<vector<float> >* SpaceTime_tError_TRT;
		//vector<vector<float> >* SpaceTime_weight_TRT;
		//vector<vector<float> >* SpaceTime_x_TRT;
		//vector<vector<float> >* SpaceTime_y_TRT;
		//vector<vector<float> >* SpaceTime_z_TRT;
		//vector<vector<float> >* SpaceTime_t_MDT;
		//vector<vector<float> >* SpaceTime_tError_MDT;
		//vector<vector<float> >* SpaceTime_weight_MDT;
		//vector<vector<float> >* SpaceTime_x_MDT;
		//vector<vector<float> >* SpaceTime_y_MDT;
		//vector<vector<float> >* SpaceTime_z_MDT;
		vector<float>* TileCellEnergyLayer1;
		vector<float>* TileTimeLayer1;
		vector<float>* TileCellRmsNoiseLayer1;
		vector<float>* TileCellSignLayer1;
		vector<float>* TileCellEnergyLayer2;
		vector<float>* TileTimeLayer2;
		vector<float>* TileCellRmsNoiseLayer2;
		vector<float>* TileCellSignLayer2;
		vector<float>* TileCellEnergyLayer3;
		vector<float>* TileTimeLayer3;
		vector<float>* TileCellRmsNoiseLayer3;
		vector<float>* TileCellSignLayer3;
		vector<float>* MSTrkT0_1;
		vector<float>* MSTrkT0_2;
		vector<float>* MSTrkT0_3;
		vector<float>* cov_d0_exPV;
		vector<float>* cov_z0_exPV;
		vector<float>* cov_phi_exPV;
		vector<float>* cov_theta_exPV;
		vector<float>* cov_qoverp_exPV;
		vector<float>* cov_d0_z0_exPV;
		vector<float>* cov_d0_phi_exPV;
		vector<float>* cov_d0_theta_exPV;
		vector<float>* cov_d0_qoverp_exPV;
		vector<float>* cov_z0_phi_exPV;
		vector<float>* cov_z0_theta_exPV;
		vector<float>* cov_z0_qoverp_exPV;
		vector<float>* cov_phi_theta_exPV;
		vector<float>* cov_phi_qoverp_exPV;
		vector<float>* cov_theta_qoverp_exPV;
		vector<float>* id_cov_d0_exPV;
		vector<float>* id_cov_z0_exPV;
		vector<float>* id_cov_phi_exPV;
		vector<float>* id_cov_theta_exPV;
		vector<float>* id_cov_qoverp_exPV;
		vector<float>* id_cov_d0_z0_exPV;
		vector<float>* id_cov_d0_phi_exPV;
		vector<float>* id_cov_d0_theta_exPV;
		vector<float>* id_cov_d0_qoverp_exPV;
		vector<float>* id_cov_z0_phi_exPV;
		vector<float>* id_cov_z0_theta_exPV;
		vector<float>* id_cov_z0_qoverp_exPV;
		vector<float>* id_cov_phi_theta_exPV;
		vector<float>* id_cov_phi_qoverp_exPV;
		vector<float>* id_cov_theta_qoverp_exPV;
		vector<float>* me_cov_d0_exPV;
		vector<float>* me_cov_z0_exPV;
		vector<float>* me_cov_phi_exPV;
		vector<float>* me_cov_theta_exPV;
		vector<float>* me_cov_qoverp_exPV;
		vector<float>* me_cov_d0_z0_exPV;
		vector<float>* me_cov_d0_phi_exPV;
		vector<float>* me_cov_d0_theta_exPV;
		vector<float>* me_cov_d0_qoverp_exPV;
		vector<float>* me_cov_z0_phi_exPV;
		vector<float>* me_cov_z0_theta_exPV;
		vector<float>* me_cov_z0_qoverp_exPV;
		vector<float>* me_cov_phi_theta_exPV;
		vector<float>* me_cov_phi_qoverp_exPV;
		vector<float>* me_cov_theta_qoverp_exPV;
		vector<float>* ms_d0;
		vector<float>* ms_z0;
		vector<float>* ms_phi;
		vector<float>* ms_theta;
		vector<float>* ms_qoverp;
		vector<float>* id_d0;
		vector<float>* id_z0;
		vector<float>* id_phi;
		vector<float>* id_theta;
		vector<float>* id_qoverp;
		vector<float>* me_d0;
		vector<float>* me_z0;
		vector<float>* me_phi;
		vector<float>* me_theta;
		vector<float>* me_qoverp;
		vector<float>* ie_d0;
		vector<float>* ie_z0;
		vector<float>* ie_phi;
		vector<float>* ie_theta;
		vector<float>* ie_qoverp;
		vector<int>* nOutliersOnTrack;
		vector<int>* nBLHits;
		vector<int>* nPixHits;
		vector<int>* nSCTHits;
		vector<int>* nTRTHits;
		vector<int>* nTRTHighTHits;
		vector<int>* nBLSharedHits;
		vector<int>* nPixSharedHits;
		vector<int>* nPixHoles;
		vector<int>* nSCTSharedHits;
		vector<int>* nSCTHoles;
		vector<int>* nTRTOutliers;
		vector<int>* nTRTHighTOutliers;
		vector<int>* nGangedPixels;
		vector<int>* nPixelDeadSensors;
		vector<int>* nSCTDeadSensors;
		vector<int>* nTRTDeadStraws;
		vector<int>* expectBLayerHit;
		vector<int>* nMDTHits;
		vector<int>* nMDTHoles;
		vector<int>* nCSCEtaHits;
		vector<int>* nCSCEtaHoles;
		vector<int>* nCSCPhiHits;
		vector<int>* nCSCPhiHoles;
		vector<int>* nRPCEtaHits;
		vector<int>* nRPCEtaHoles;
		vector<int>* nRPCPhiHits;
		vector<int>* nRPCPhiHoles;
		vector<int>* nTGCEtaHits;
		vector<int>* nTGCEtaHoles;
		vector<int>* nTGCPhiHits;
		vector<int>* nTGCPhiHoles;
		vector<int>* nMDTBIHits;
		vector<int>* nMDTBMHits;
		vector<int>* nMDTBOHits;
		vector<int>* nMDTBEEHits;
		vector<int>* nMDTBIS78Hits;
		vector<int>* nMDTEIHits;
		vector<int>* nMDTEMHits;
		vector<int>* nMDTEOHits;
		vector<int>* nMDTEEHits;
		vector<int>* nRPCLayer1EtaHits;
		vector<int>* nRPCLayer2EtaHits;
		vector<int>* nRPCLayer3EtaHits;
		vector<int>* nRPCLayer1PhiHits;
		vector<int>* nRPCLayer2PhiHits;
		vector<int>* nRPCLayer3PhiHits;
		vector<int>* nTGCLayer1EtaHits;
		vector<int>* nTGCLayer2EtaHits;
		vector<int>* nTGCLayer3EtaHits;
		vector<int>* nTGCLayer4EtaHits;
		vector<int>* nTGCLayer1PhiHits;
		vector<int>* nTGCLayer2PhiHits;
		vector<int>* nTGCLayer3PhiHits;
		vector<int>* nTGCLayer4PhiHits;
		vector<int>* barrelSectors;
		vector<int>* endcapSectors;
		vector<float>* trackd0;
		vector<float>* trackz0;
		vector<float>* trackphi;
		vector<float>* tracktheta;
		vector<float>* trackqoverp;
		vector<float>* trackcov_d0;
		vector<float>* trackcov_z0;
		vector<float>* trackcov_phi;
		vector<float>* trackcov_theta;
		vector<float>* trackcov_qoverp;
		vector<float>* trackcov_d0_z0;
		vector<float>* trackcov_d0_phi;
		vector<float>* trackcov_d0_theta;
		vector<float>* trackcov_d0_qoverp;
		vector<float>* trackcov_z0_phi;
		vector<float>* trackcov_z0_theta;
		vector<float>* trackcov_z0_qoverp;
		vector<float>* trackcov_phi_theta;
		vector<float>* trackcov_phi_qoverp;
		vector<float>* trackcov_theta_qoverp;
		vector<float>* trackfitchi2;
		vector<int>*   trackfitndof;
		vector<float>* truth_dr;
		vector<float>* truth_E;
		vector<float>* truth_pt;
		vector<float>* truth_eta;
		vector<float>* truth_phi;
		vector<int>*   truth_type;
		vector<int>*   truth_status;
		vector<int>*   truth_barcode;
		vector<int>*   truth_mothertype;
		vector<int>*   truth_motherbarcode;
		vector<int>*   truth_matched;
		vector<int>*   hastrack;
		vector<float>* EFCB_dr;
		vector<int>*   EFCB_index;
		vector<float>* EFMG_dr;
		vector<int>*   EFMG_index;
		vector<float>* EFME_dr;
		vector<int>*   EFME_index;
		vector<float>* L2CB_dr;
		vector<int>*   L2CB_index;
		vector<float>* L1_dr;
		vector<int>*   L1_index;
		
		float Mhat;
		float CosThetaCS;
		float CosThetaHE;
		float Ysystem;
		float Q_T;
		float CosThetaDimu;
		float ipTDiff;
		float EtaSum;

		
		// cut profile 1d
		vector<float>* pT_profile;
		vector<float>* pT_loose_profile;
		vector<float>* pT_qOp_and_theta_profile;
		vector<float>* pT_qOp_and_theta_loose_profile;
		vector<float>* eta_profile;
		vector<float>* etaTight_profile;
		vector<float>* etaBarrel_profile;
		vector<float>* etaFwd_profile;
		vector<float>* etaFull_profile;
		vector<float>* pTmatchingRatio_profile;
		vector<float>* pTmatchingAbsDiff_profile;
		vector<float>* d0_profile;
		vector<float>* z0_profile;
		vector<float>* ip_d0_profile;
		vector<float>* ip_z0_profile;
		vector<float>* isolation20_profile;
		vector<float>* isolation30_profile;
		vector<float>* isolation40_profile;
		vector<float>* vxp_z_profile;
		vector<int>*   vxp_nTracks_profile;
		vector<int>* nMDTBI_profile;
		vector<int>* nMDTBM_profile;
		vector<int>* nMDTBO_profile;
		vector<int>* nMDTEI_profile;
		vector<int>* nMDTEM_profile;
		vector<int>* nMDTEO_profile;
		vector<int>* nMDTBEE_profile;
		vector<int>* nMDTEE_profile;
		vector<int>* nMDTBIS78_profile;
		vector<int>* nRPCPhi1_profile;
		vector<int>* nRPCPhi2_profile;
		vector<int>* nRPCPhi3_profile;
		vector<int>* nTGCPhi1_profile;
		vector<int>* nTGCPhi2_profile;
		vector<int>* nTGCPhi3_profile;
		vector<int>* nTGCPhi4_profile;
		vector<int>* nCSCEta_profile;
		vector<int>* nCSCPhi_profile;
		vector<int>* expectBLayerHit_profile;
		vector<int>* nBLHits_profile;
		vector<int>* nPixHits_profile;
		vector<int>* nPixelDeadSensors_profile;
		vector<int>* nPixHoles_profile;
		vector<int>* nSCTHits_profile;
		vector<int>* nSCTDeadSensors_profile;
		vector<int>* nSCTHoles_profile;
		vector<int>* nTRTHits_profile;
		vector<int>* nTRTOutliers_profile;
		vector<float>* eta_forTRThits_profile;
		
		// cut profile 2d
		vector<float>* oppositeCharge_profile;
		vector<float>* imass_profile;
		vector<float>* cosThetaDimu_profile;
		vector<float>* etaSum_profile;
		// eff
		vector<string>* tNp_triggerName; // only one entry but easier to access...
		vector<float>* tNp_cand_pT;
		vector<float>* tNp_succ_pT;
		vector<float>* tNp_cand_eta;
		vector<float>* tNp_succ_eta;
		vector<float>* tNp_cand_phi;
		vector<float>* tNp_succ_phi;
		vector<string>* tru_triggerName; // only one entry but easier to access...
		vector<float>* tru_cand_pT;
		vector<float>* tru_succ_pT;
		vector<float>* tru_cand_eta;
		vector<float>* tru_succ_eta;
		vector<float>* tru_cand_phi;
		vector<float>* tru_succ_phi;
		//--------------------------------
		
		
		///////////////////////////////////////////
		// for the truth tree (for the weights) ///
		bool truth_all_isValid;
		vector<float>* truth_all_dr;
		vector<float>* truth_all_E;
		vector<float>* truth_all_pt;
		vector<float>* truth_all_eta;
		vector<float>* truth_all_phi;
		vector<int>*   truth_all_type;
		vector<int>*   truth_all_status;
		vector<int>*   truth_all_barcode;
		vector<int>*   truth_all_mothertype;
		vector<int>*   truth_all_motherbarcode;
		vector<int>*   truth_all_matched;
		
		// muonTruth
		vector<float>*   truth_all_muonTruth_pt;
		vector<float>*   truth_all_muonTruth_m;
		vector<float>*   truth_all_muonTruth_eta;
		vector<float>*   truth_all_muonTruth_phi;
		vector<float>*   truth_all_muonTruth_charge;
		vector<int>*     truth_all_muonTruth_PDGID;
		vector<int>*     truth_all_muonTruth_barcode;
		vector<int>*     truth_all_muonTruth_type;
		vector<int>*     truth_all_muonTruth_origin;
		// MC event
		vector<int>*     truth_all_mcevt_signal_process_id;
		vector<int>*     truth_all_mcevt_event_number;
		vector<double>*  truth_all_mcevt_event_scale;
		vector<double>*  truth_all_mcevt_alphaQCD;
		vector<double>*  truth_all_mcevt_alphaQED;
		vector<int>*     truth_all_mcevt_pdf_id1;
		vector<int>*     truth_all_mcevt_pdf_id2;
		vector<double>*  truth_all_mcevt_pdf_x1;
		vector<double>*  truth_all_mcevt_pdf_x2;
		vector<double>*  truth_all_mcevt_pdf_scale;
		vector<double>*  truth_all_mcevt_pdf1;
		vector<double>*  truth_all_mcevt_pdf2;
		vector<double>*  truth_all_mcevt_weight;
		//MC
		vector<float>* truth_all_mc_pt;
		vector<float>* truth_all_mc_m;
		vector<float>* truth_all_mc_eta;
		vector<float>* truth_all_mc_phi;
		vector<int>*   truth_all_mc_status;
		vector<int>*   truth_all_mc_barcode;
		vector<int>*   truth_all_mc_pdgId;
		vector<float>* truth_all_mc_charge;
		
		float truth_all_Mhat;
		float truth_all_CosThetaCS;
		float truth_all_CosThetaHE;
		float truth_all_ySystem;
		float truth_all_QT;
		
		bool recon_all_isValid;
		vector<float>* recon_all_E;
		vector<float>* recon_all_pt;
		vector<float>* recon_all_m;
		vector<float>* recon_all_eta;
		vector<float>* recon_all_phi;
		vector<float>* recon_all_px;
		vector<float>* recon_all_py;
		vector<float>* recon_all_pz;
		vector<float>* recon_all_charge;
		vector<float>* recon_all_y;
		vector<int>*   recon_all_id;
		vector<float>* recon_all_theta;
		float recon_all_Mhat;
		float recon_all_CosThetaCS;
		float recon_all_CosThetaHE;
		float recon_all_ySystem;
		float recon_all_QT;
		
	
	public:
		graphicObjects();
		~graphicObjects();

		void ginitialize();
		void gfinalize();

		void setStyle();
		
		void setTrees(TDirectory* tDir_allCuts,
					  TDirectory* tDir_cutsProfile,
					  TDirectory* tDir_efficiency);
		void setTrees(TDirectory* tDir_allCuts,
					  TDirectory* tDir_cutsProfile,
					  TDirectory* tDir_efficiency,
					  TDirectory* tDir_truth);
		void writeTrees(TDirectory* tDir_allCuts,
						TDirectory* tDir_cutsProfile,
						TDirectory* tDir_efficiency);
		void writeTrees(TDirectory* tDir_allCuts,
						TDirectory* tDir_cutsProfile,
						TDirectory* tDir_efficiency,
						TDirectory* tDir_truth
						);
		void clearTreeVars();
		
		void setCutFlowMapSVDPtr(TMapsvd* cutFlowMapSVD);

		void bookBareHistos(TDirectory* tdir);
		void drawBareHistos(TDirectory* tdir);
		
		void bookEfficiencyHistos(TMapss* period2triggerperiodMap, TDirectory* tdir);
		void drawEfficiencyHistosMap(TDirectory* tdir);

		void bookHistos(TDirectory* tdir);
		void drawHistos(TDirectory* tdir);

		void bookFitHistos(TDirectory* tdir);
		void drawFitHistos(TDirectory* tdir, TF1* fGuess, TF1* fFitted);

		void bookHistosMap(TMapds* cutFlowOrdered, TMapds* cutFlowTypeOrdered, TDirectory* tdir);
		void drawHistosMap(TMapds* cutFlowOrdered, TMapds* cutFlowTypeOrdered, TDirectory* tdir);
		
		void bookCutProfileHistosMap(TMapds* cutFlowOrdered, TDirectory* tdir);
		void drawCutProfileHistosMap(TDirectory* tdir);
		
		void drawPerformance(vector<int>& vEntries, vector<double>& vResMemory, vector<double>& vVirMemory, TDirectory* tdir);

	private:

};
#endif

