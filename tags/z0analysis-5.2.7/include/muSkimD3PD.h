/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#ifndef MUSKIMD3PD_H
#define MUSKIMD3PD_H

class muSkimD3PD
{
public:
	// pointers
	offlinePhysics*   m_offPhys;
	mcOfflinePhysics* m_mcOffPhys;
	TFile*            m_treeFile;
	TTree*            m_tree;
	
	// locals
	bool doSkim;
	int counter;
	
	// event info branches
	vector<string>* period;
	vector<string>* triggers;
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
	int lar_ncellA;
	int lar_ncellC;
	float lar_energyA;
	float lar_energyC;
	float lar_timeA;
	float lar_timeC;
	float lar_timeDiff;
	
	// L1 triggers
	int L1_MU0;
	int L1_MU10;
	int L1_MU15;
	int L1_MU20;
	int L1_MU6;
	
	// EF triggers
	int EF_mu10;
	int EF_mu10_MG;
	int EF_mu10_MSonly;
	int EF_mu10_MSonly_tight;
	int EF_mu10_NoAlg;
	int EF_mu10_tight;
	int EF_mu10i_loose;
	int EF_mu13;
	int EF_mu13_MG;
	int EF_mu13_MG_tight;
	int EF_mu13_tight;
	int EF_mu15;
	int EF_mu15_NoAlg;
	int EF_mu20;
	int EF_mu20_MSonly;
	int EF_mu20_NoAlg;
	int EF_mu20_slow;
	int EF_mu30_MSonly;
	int EF_mu4;
	int EF_mu40_MSonly;
	
	// mu_staco
	int            mu_staco_n;
	vector<float>* mu_staco_px;
	vector<float>* mu_staco_py;
	vector<float>* mu_staco_pz;
	vector<float>* mu_staco_E;
	vector<float>* mu_staco_m;
	vector<float>* mu_staco_charge;
	vector<float>* mu_staco_pt;
	vector<float>* mu_staco_ptcone20;
	vector<float>* mu_staco_ptcone30;
	vector<float>* mu_staco_ptcone40;
	vector<float>* mu_staco_eta;
	vector<float>* mu_staco_phi;
	vector<float>* mu_staco_d0_exPV;
	vector<float>* mu_staco_z0_exPV;
	vector<float>* mu_staco_me_qoverp;
	vector<float>* mu_staco_id_qoverp;
	vector<float>* mu_staco_me_theta;
	vector<float>* mu_staco_id_theta;
	vector<int>*   mu_staco_isCombinedMuon;
	vector<int>*   mu_staco_nSCTHits;
	vector<int>*   mu_staco_nPixHits;
	vector<int>*   mu_staco_nMDTBIHits;
	vector<int>*   mu_staco_nMDTBMHits;
	vector<int>*   mu_staco_nMDTBOHits;
	vector<int>*   mu_staco_nMDTBEEHits;
	vector<int>*   mu_staco_nMDTBIS78Hits;
	vector<int>*   mu_staco_nMDTEIHits;
	vector<int>*   mu_staco_nMDTEMHits;
	vector<int>*   mu_staco_nMDTEOHits;
	vector<int>*   mu_staco_nMDTEEHits;
	vector<int>*   mu_staco_nRPCLayer1EtaHits;
	vector<int>*   mu_staco_nRPCLayer2EtaHits;
	vector<int>*   mu_staco_nRPCLayer3EtaHits;
	vector<int>*   mu_staco_nRPCLayer1PhiHits;
	vector<int>*   mu_staco_nRPCLayer2PhiHits;
	vector<int>*   mu_staco_nRPCLayer3PhiHits;
	vector<int>*   mu_staco_nTGCLayer1EtaHits;
	vector<int>*   mu_staco_nTGCLayer2EtaHits;
	vector<int>*   mu_staco_nTGCLayer3EtaHits;
	vector<int>*   mu_staco_nTGCLayer4EtaHits;
	vector<int>*   mu_staco_nTGCLayer1PhiHits;
	vector<int>*   mu_staco_nTGCLayer2PhiHits;
	vector<int>*   mu_staco_nTGCLayer3PhiHits;
	vector<int>*   mu_staco_nTGCLayer4PhiHits;
	vector<unsigned short>* mu_staco_allauthor;
	vector<int>*   mu_staco_author;
	vector<float>* mu_staco_matchchi2;
	vector<int>*   mu_staco_matchndof;
	vector<float>*   mu_staco_etcone20;
	vector<float>*   mu_staco_etcone30;
	vector<float>*   mu_staco_etcone40;
	vector<float>*   mu_staco_nucone20;
	vector<float>*   mu_staco_nucone30;
	vector<float>*   mu_staco_nucone40;
	vector<float>*   mu_staco_energyLossPar;
	vector<float>*   mu_staco_energyLossErr;
	vector<int>*     mu_staco_bestMatch;
	vector<int>*     mu_staco_isStandAloneMuon;
	vector<int>*     mu_staco_isLowPtReconstructedMuon;
	vector<int>*     mu_staco_loose;
	vector<int>*     mu_staco_medium;
	vector<int>*     mu_staco_tight;
	vector<float>*   mu_staco_phi_exPV;
	vector<float>*   mu_staco_theta_exPV;
	vector<float>*   mu_staco_qoverp_exPV;
	vector<float>*   mu_staco_cov_d0_exPV;
	vector<float>*   mu_staco_cov_z0_exPV;
	vector<float>*   mu_staco_cov_phi_exPV;
	vector<float>*   mu_staco_cov_theta_exPV;
	vector<float>*   mu_staco_cov_qoverp_exPV;
	vector<float>*   mu_staco_cov_d0_z0_exPV;
	vector<float>*   mu_staco_cov_d0_phi_exPV;
	vector<float>*   mu_staco_cov_d0_theta_exPV;
	vector<float>*   mu_staco_cov_d0_qoverp_exPV;
	vector<float>*   mu_staco_cov_z0_phi_exPV;
	vector<float>*   mu_staco_cov_z0_theta_exPV;
	vector<float>*   mu_staco_cov_z0_qoverp_exPV;
	vector<float>*   mu_staco_cov_phi_theta_exPV;
	vector<float>*   mu_staco_cov_phi_qoverp_exPV;
	vector<float>*   mu_staco_cov_theta_qoverp_exPV;
	vector<float>*   mu_staco_ms_d0;
	vector<float>*   mu_staco_ms_z0;
	vector<float>*   mu_staco_ms_phi;
	vector<float>*   mu_staco_ms_theta;
	vector<float>*   mu_staco_ms_qoverp;
	vector<float>*   mu_staco_id_d0;
	vector<float>*   mu_staco_id_z0;
	vector<float>*   mu_staco_id_phi;
	vector<float>*   mu_staco_me_d0;
	vector<float>*   mu_staco_me_z0;
	vector<float>*   mu_staco_me_phi;
	vector<float>*   mu_staco_ie_d0;
	vector<float>*   mu_staco_ie_z0;
	vector<float>*   mu_staco_ie_phi;
	vector<float>*   mu_staco_ie_theta;
	vector<float>*   mu_staco_ie_qoverp;
	vector<int>*     mu_staco_nBLHits;
	vector<int>*     mu_staco_nTRTHits;
	vector<int>*     mu_staco_nTRTHighTHits;
	vector<int>*     mu_staco_nBLSharedHits;
	vector<int>*     mu_staco_nPixSharedHits;
	vector<int>*     mu_staco_nPixHoles;
	vector<int>*     mu_staco_nSCTSharedHits;
	vector<int>*     mu_staco_nSCTHoles;
	vector<int>*     mu_staco_nTRTOutliers;
	vector<int>*     mu_staco_nTRTHighTOutliers;
	vector<int>*     mu_staco_nMDTHits;
	vector<int>*     mu_staco_nMDTHoles;
	vector<int>*     mu_staco_nCSCEtaHits;
	vector<int>*     mu_staco_nCSCEtaHoles;
	vector<int>*     mu_staco_nCSCPhiHits;
	vector<int>*     mu_staco_nCSCPhiHoles;
	vector<int>*     mu_staco_nRPCEtaHits;
	vector<int>*     mu_staco_nRPCEtaHoles;
	vector<int>*     mu_staco_nRPCPhiHits;
	vector<int>*     mu_staco_nRPCPhiHoles;
	vector<int>*     mu_staco_nTGCEtaHits;
	vector<int>*     mu_staco_nTGCEtaHoles;
	vector<int>*     mu_staco_nTGCPhiHits;
	vector<int>*     mu_staco_nTGCPhiHoles;
	vector<int>*     mu_staco_nGangedPixels;
	vector<int>*     mu_staco_nOutliersOnTrack;
	vector<int>*     mu_staco_barrelSectors;
	vector<int>*     mu_staco_endcapSectors;
	vector<float>*   mu_staco_trackd0;
	vector<float>*   mu_staco_trackz0;
	vector<float>*   mu_staco_trackphi;
	vector<float>*   mu_staco_tracktheta;
	vector<float>*   mu_staco_trackqoverp;
	vector<float>*   mu_staco_trackcov_d0;
	vector<float>*   mu_staco_trackcov_z0;
	vector<float>*   mu_staco_trackcov_phi;
	vector<float>*   mu_staco_trackcov_theta;
	vector<float>*   mu_staco_trackcov_qoverp;
	vector<float>*   mu_staco_trackcov_d0_z0;
	vector<float>*   mu_staco_trackcov_d0_phi;
	vector<float>*   mu_staco_trackcov_d0_theta;
	vector<float>*   mu_staco_trackcov_d0_qoverp;
	vector<float>*   mu_staco_trackcov_z0_phi;
	vector<float>*   mu_staco_trackcov_z0_theta;
	vector<float>*   mu_staco_trackcov_z0_qoverp;
	vector<float>*   mu_staco_trackcov_phi_theta;
	vector<float>*   mu_staco_trackcov_phi_qoverp;
	vector<float>*   mu_staco_trackcov_theta_qoverp;
	vector<float>*   mu_staco_trackfitchi2;
	vector<int>*     mu_staco_trackfitndof;
	vector<int>*     mu_staco_hastrack;
	vector<float>*   mu_staco_EF_dr;
	vector<float>*   mu_staco_EF_cb_eta;
	vector<float>*   mu_staco_EF_cb_phi;
	vector<float>*   mu_staco_EF_cb_pt;
	vector<float>*   mu_staco_EF_ms_eta;
	vector<float>*   mu_staco_EF_ms_phi;
	vector<float>*   mu_staco_EF_ms_pt;
	vector<float>*   mu_staco_EF_me_eta;
	vector<float>*   mu_staco_EF_me_phi;
	vector<float>*   mu_staco_EF_me_pt;
	vector<int>*     mu_staco_EF_matched;
	vector<float>*   mu_staco_L2CB_dr;
	vector<float>*   mu_staco_L2CB_pt;
	vector<float>*   mu_staco_L2CB_eta;
	vector<float>*   mu_staco_L2CB_phi;
	vector<float>*   mu_staco_L2CB_id_pt;
	vector<float>*   mu_staco_L2CB_ms_pt;
	vector<int>*     mu_staco_L2CB_nPixHits;
	vector<int>*     mu_staco_L2CB_nSCTHits;
	vector<int>*     mu_staco_L2CB_nTRTHits;
	vector<int>*     mu_staco_L2CB_nTRTHighTHits;
	vector<int>*     mu_staco_L2CB_matched;
	vector<float>*   mu_staco_L1_dr;
	vector<float>*   mu_staco_L1_pt;
	vector<float>*   mu_staco_L1_eta;
	vector<float>*   mu_staco_L1_phi;
	vector<short>*   mu_staco_L1_thrNumber;
	vector<short>*   mu_staco_L1_RoINumber;
	vector<short>*   mu_staco_L1_sectorAddress;
	vector<int>*     mu_staco_L1_firstCandidate;
	vector<int>*     mu_staco_L1_moreCandInRoI;
	vector<int>*     mu_staco_L1_moreCandInSector;
	vector<short>*   mu_staco_L1_source;
	vector<short>*   mu_staco_L1_hemisphere;
	vector<int>*     mu_staco_L1_matched;
	
	// muid
	int            mu_muid_n;
	vector<float>* mu_muid_px;
	vector<float>* mu_muid_py;
	vector<float>* mu_muid_pz;
	vector<float>* mu_muid_E;
	vector<float>* mu_muid_m;
	vector<float>* mu_muid_charge;
	vector<float>* mu_muid_pt;
	vector<float>* mu_muid_ptcone20;
	vector<float>* mu_muid_ptcone30;
	vector<float>* mu_muid_ptcone40;
	vector<float>* mu_muid_eta;
	vector<float>* mu_muid_phi;
	vector<float>* mu_muid_d0_exPV;
	vector<float>* mu_muid_z0_exPV;
	vector<float>* mu_muid_me_qoverp;
	vector<float>* mu_muid_id_qoverp;
	vector<float>* mu_muid_me_theta;
	vector<float>* mu_muid_id_theta;
	vector<int>*   mu_muid_isCombinedMuon;
	vector<int>*   mu_muid_nSCTHits;
	vector<int>*   mu_muid_nPixHits;
	vector<int>*   mu_muid_nMDTBIHits;
	vector<int>*   mu_muid_nMDTBMHits;
	vector<int>*   mu_muid_nMDTBOHits;
	vector<int>*   mu_muid_nMDTBEEHits;
	vector<int>*   mu_muid_nMDTBIS78Hits;
	vector<int>*   mu_muid_nMDTEIHits;
	vector<int>*   mu_muid_nMDTEMHits;
	vector<int>*   mu_muid_nMDTEOHits;
	vector<int>*   mu_muid_nMDTEEHits;
	vector<int>*   mu_muid_nRPCLayer1EtaHits;
	vector<int>*   mu_muid_nRPCLayer2EtaHits;
	vector<int>*   mu_muid_nRPCLayer3EtaHits;
	vector<int>*   mu_muid_nRPCLayer1PhiHits;
	vector<int>*   mu_muid_nRPCLayer2PhiHits;
	vector<int>*   mu_muid_nRPCLayer3PhiHits;
	vector<int>*   mu_muid_nTGCLayer1EtaHits;
	vector<int>*   mu_muid_nTGCLayer2EtaHits;
	vector<int>*   mu_muid_nTGCLayer3EtaHits;
	vector<int>*   mu_muid_nTGCLayer4EtaHits;
	vector<int>*   mu_muid_nTGCLayer1PhiHits;
	vector<int>*   mu_muid_nTGCLayer2PhiHits;
	vector<int>*   mu_muid_nTGCLayer3PhiHits;
	vector<int>*   mu_muid_nTGCLayer4PhiHits;
	vector<unsigned short>* mu_muid_allauthor;
	vector<int>*   mu_muid_author;
	vector<float>* mu_muid_matchchi2;
	vector<int>*   mu_muid_matchndof;
	vector<float>*   mu_muid_etcone20;
	vector<float>*   mu_muid_etcone30;
	vector<float>*   mu_muid_etcone40;
	vector<float>*   mu_muid_nucone20;
	vector<float>*   mu_muid_nucone30;
	vector<float>*   mu_muid_nucone40;
	vector<float>*   mu_muid_energyLossPar;
	vector<float>*   mu_muid_energyLossErr;
	vector<int>*     mu_muid_bestMatch;
	vector<int>*     mu_muid_isStandAloneMuon;
	vector<int>*     mu_muid_isLowPtReconstructedMuon;
	vector<int>*     mu_muid_loose;
	vector<int>*     mu_muid_medium;
	vector<int>*     mu_muid_tight;
	vector<float>*   mu_muid_phi_exPV;
	vector<float>*   mu_muid_theta_exPV;
	vector<float>*   mu_muid_qoverp_exPV;
	vector<float>*   mu_muid_cov_d0_exPV;
	vector<float>*   mu_muid_cov_z0_exPV;
	vector<float>*   mu_muid_cov_phi_exPV;
	vector<float>*   mu_muid_cov_theta_exPV;
	vector<float>*   mu_muid_cov_qoverp_exPV;
	vector<float>*   mu_muid_cov_d0_z0_exPV;
	vector<float>*   mu_muid_cov_d0_phi_exPV;
	vector<float>*   mu_muid_cov_d0_theta_exPV;
	vector<float>*   mu_muid_cov_d0_qoverp_exPV;
	vector<float>*   mu_muid_cov_z0_phi_exPV;
	vector<float>*   mu_muid_cov_z0_theta_exPV;
	vector<float>*   mu_muid_cov_z0_qoverp_exPV;
	vector<float>*   mu_muid_cov_phi_theta_exPV;
	vector<float>*   mu_muid_cov_phi_qoverp_exPV;
	vector<float>*   mu_muid_cov_theta_qoverp_exPV;
	vector<float>*   mu_muid_ms_d0;
	vector<float>*   mu_muid_ms_z0;
	vector<float>*   mu_muid_ms_phi;
	vector<float>*   mu_muid_ms_theta;
	vector<float>*   mu_muid_ms_qoverp;
	vector<float>*   mu_muid_id_d0;
	vector<float>*   mu_muid_id_z0;
	vector<float>*   mu_muid_id_phi;
	vector<float>*   mu_muid_me_d0;
	vector<float>*   mu_muid_me_z0;
	vector<float>*   mu_muid_me_phi;
	vector<float>*   mu_muid_ie_d0;
	vector<float>*   mu_muid_ie_z0;
	vector<float>*   mu_muid_ie_phi;
	vector<float>*   mu_muid_ie_theta;
	vector<float>*   mu_muid_ie_qoverp;
	vector<int>*     mu_muid_nBLHits;
	vector<int>*     mu_muid_nTRTHits;
	vector<int>*     mu_muid_nTRTHighTHits;
	vector<int>*     mu_muid_nBLSharedHits;
	vector<int>*     mu_muid_nPixSharedHits;
	vector<int>*     mu_muid_nPixHoles;
	vector<int>*     mu_muid_nSCTSharedHits;
	vector<int>*     mu_muid_nSCTHoles;
	vector<int>*     mu_muid_nTRTOutliers;
	vector<int>*     mu_muid_nTRTHighTOutliers;
	vector<int>*     mu_muid_nMDTHits;
	vector<int>*     mu_muid_nMDTHoles;
	vector<int>*     mu_muid_nCSCEtaHits;
	vector<int>*     mu_muid_nCSCEtaHoles;
	vector<int>*     mu_muid_nCSCPhiHits;
	vector<int>*     mu_muid_nCSCPhiHoles;
	vector<int>*     mu_muid_nRPCEtaHits;
	vector<int>*     mu_muid_nRPCEtaHoles;
	vector<int>*     mu_muid_nRPCPhiHits;
	vector<int>*     mu_muid_nRPCPhiHoles;
	vector<int>*     mu_muid_nTGCEtaHits;
	vector<int>*     mu_muid_nTGCEtaHoles;
	vector<int>*     mu_muid_nTGCPhiHits;
	vector<int>*     mu_muid_nTGCPhiHoles;
	vector<int>*     mu_muid_nGangedPixels;
	vector<int>*     mu_muid_nOutliersOnTrack;
	vector<int>*     mu_muid_barrelSectors;
	vector<int>*     mu_muid_endcapSectors;
	vector<float>*   mu_muid_trackd0;
	vector<float>*   mu_muid_trackz0;
	vector<float>*   mu_muid_trackphi;
	vector<float>*   mu_muid_tracktheta;
	vector<float>*   mu_muid_trackqoverp;
	vector<float>*   mu_muid_trackcov_d0;
	vector<float>*   mu_muid_trackcov_z0;
	vector<float>*   mu_muid_trackcov_phi;
	vector<float>*   mu_muid_trackcov_theta;
	vector<float>*   mu_muid_trackcov_qoverp;
	vector<float>*   mu_muid_trackcov_d0_z0;
	vector<float>*   mu_muid_trackcov_d0_phi;
	vector<float>*   mu_muid_trackcov_d0_theta;
	vector<float>*   mu_muid_trackcov_d0_qoverp;
	vector<float>*   mu_muid_trackcov_z0_phi;
	vector<float>*   mu_muid_trackcov_z0_theta;
	vector<float>*   mu_muid_trackcov_z0_qoverp;
	vector<float>*   mu_muid_trackcov_phi_theta;
	vector<float>*   mu_muid_trackcov_phi_qoverp;
	vector<float>*   mu_muid_trackcov_theta_qoverp;
	vector<float>*   mu_muid_trackfitchi2;
	vector<int>*     mu_muid_trackfitndof;
	vector<int>*     mu_muid_hastrack;
	vector<float>*   mu_muid_EF_dr;
	vector<float>*   mu_muid_EF_cb_eta;
	vector<float>*   mu_muid_EF_cb_phi;
	vector<float>*   mu_muid_EF_cb_pt;
	vector<float>*   mu_muid_EF_ms_eta;
	vector<float>*   mu_muid_EF_ms_phi;
	vector<float>*   mu_muid_EF_ms_pt;
	vector<float>*   mu_muid_EF_me_eta;
	vector<float>*   mu_muid_EF_me_phi;
	vector<float>*   mu_muid_EF_me_pt;
	vector<int>*     mu_muid_EF_matched;
	vector<float>*   mu_muid_L2CB_dr;
	vector<float>*   mu_muid_L2CB_pt;
	vector<float>*   mu_muid_L2CB_eta;
	vector<float>*   mu_muid_L2CB_phi;
	vector<float>*   mu_muid_L2CB_id_pt;
	vector<float>*   mu_muid_L2CB_ms_pt;
	vector<int>*     mu_muid_L2CB_nPixHits;
	vector<int>*     mu_muid_L2CB_nSCTHits;
	vector<int>*     mu_muid_L2CB_nTRTHits;
	vector<int>*     mu_muid_L2CB_nTRTHighTHits;
	vector<int>*     mu_muid_L2CB_matched;
	vector<float>*   mu_muid_L1_dr;
	vector<float>*   mu_muid_L1_pt;
	vector<float>*   mu_muid_L1_eta;
	vector<float>*   mu_muid_L1_phi;
	vector<short>*   mu_muid_L1_thrNumber;
	vector<short>*   mu_muid_L1_RoINumber;
	vector<short>*   mu_muid_L1_sectorAddress;
	vector<int>*     mu_muid_L1_firstCandidate;
	vector<int>*     mu_muid_L1_moreCandInRoI;
	vector<int>*     mu_muid_L1_moreCandInSector;
	vector<short>*   mu_muid_L1_source;
	vector<short>*   mu_muid_L1_hemisphere;
	vector<int>*     mu_muid_L1_matched;
	
	// vertex variables
	int            vxp_n;
	vector<float>* vxp_z;
	vector<float>* vxp_err_z;
	vector<int>*   vxp_nTracks;
	vector<int>*   vxp_type;
	
public:
	muSkimD3PD();
	muSkimD3PD(offlinePhysics* offPhys, mcOfflinePhysics* mcOffPhys, TFile* treeFile);
	~muSkimD3PD();
	
	void doSkimD3PD();
	
	TTree* getTree();
	void setVectorPtrs();
	void resetVectorPtrs();
	void setBranches();
	void fill(int GRL);
	void write();

private:

};
#endif

