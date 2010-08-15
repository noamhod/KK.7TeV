//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Aug  2 10:47:53 2010 by ROOT version 5.22/00
// from TChain offline/
//////////////////////////////////////////////////////////

#ifndef offlinePhysics_h
#define offlinePhysics_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class offlinePhysics {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Bool_t          isGRL;
   UInt_t          RunNumber;
   UInt_t          EventNumber;
   UInt_t          timestamp;
   UInt_t          timestamp_ns;
   UInt_t          lbn;
   UInt_t          bcid;
   UInt_t          detmask0;
   UInt_t          detmask1;
   UInt_t          pixelFlags;
   UInt_t          sctFlags;
   UInt_t          trtFlags;
   UInt_t          larFlags;
   UInt_t          tileFlags;
   UInt_t          muonFlags;
   UInt_t          fwdFlags;
   UInt_t          coreFlags;
   UInt_t          pixelError;
   UInt_t          sctError;
   UInt_t          trtError;
   UInt_t          larError;
   UInt_t          tileError;
   UInt_t          muonError;
   UInt_t          fwdError;
   UInt_t          coreError;
   Int_t           lar_ncellA;
   Int_t           lar_ncellC;
   Float_t         lar_energyA;
   Float_t         lar_energyC;
   Float_t         lar_timeA;
   Float_t         lar_timeC;
   Float_t         lar_timeDiff;
   Bool_t          EF_2mu10;
   Bool_t          EF_2mu4;
   Bool_t          EF_2mu4_DiMu;
   Bool_t          EF_2mu4_DiMu_SiTrk;
   Bool_t          EF_2mu4_DiMu_noOS;
   Bool_t          EF_2mu4_DiMu_noOS_passL2;
   Bool_t          EF_2mu4_DiMu_noVtx_noOS;
   Bool_t          EF_2mu4_DiMu_noVtx_noOS_passL2;
   Bool_t          EF_2mu4_MSonly;
   Bool_t          EF_2mu6;
   Bool_t          EF_2mu6_DiMu;
   Bool_t          EF_2mu6_DiMu_noVtx_noOS;
   Bool_t          EF_L1ItemStreamer_L1_2MU0;
   Bool_t          EF_L1ItemStreamer_L1_2MU0_MU6;
   Bool_t          EF_L1ItemStreamer_L1_2MU10;
   Bool_t          EF_L1ItemStreamer_L1_2MU6;
   Bool_t          EF_L1ItemStreamer_L1_EM10;
   Bool_t          EF_L1ItemStreamer_L1_EM10I;
   Bool_t          EF_L1ItemStreamer_L1_EM14;
   Bool_t          EF_L1ItemStreamer_L1_EM2;
   //Bool_t          EF_L1ItemStreamer_L1_EM2_UNPAIRED;
   Bool_t          EF_L1ItemStreamer_L1_EM3;
   Bool_t          EF_L1ItemStreamer_L1_EM3_EMPTY;
   Bool_t          EF_L1ItemStreamer_L1_EM3_FIRSTEMPTY;
   Bool_t          EF_L1ItemStreamer_L1_EM3_MV;
   Bool_t          EF_L1ItemStreamer_L1_EM3_UNPAIRED;
   Bool_t          EF_L1ItemStreamer_L1_EM4;
   Bool_t          EF_L1ItemStreamer_L1_EM5;
   Bool_t          EF_L1ItemStreamer_L1_EM5I;
   Bool_t          EF_L1ItemStreamer_L1_MU0;
   Bool_t          EF_L1ItemStreamer_L1_MU0_COMM;
   Bool_t          EF_L1ItemStreamer_L1_MU0_COMM_EMPTY;
   Bool_t          EF_L1ItemStreamer_L1_MU0_COMM_FIRSTEMPTY;
   Bool_t          EF_L1ItemStreamer_L1_MU0_EM3;
   Bool_t          EF_L1ItemStreamer_L1_MU0_EMPTY;
   Bool_t          EF_L1ItemStreamer_L1_MU0_FIRSTEMPTY;
   Bool_t          EF_L1ItemStreamer_L1_MU0_J10;
   Bool_t          EF_L1ItemStreamer_L1_MU0_J15;
   Bool_t          EF_L1ItemStreamer_L1_MU0_J5;
   Bool_t          EF_L1ItemStreamer_L1_MU0_MV;
   Bool_t          EF_L1ItemStreamer_L1_MU0_UNPAIRED;
   Bool_t          EF_L1ItemStreamer_L1_MU10;
   Bool_t          EF_L1ItemStreamer_L1_MU10_EMPTY;
   Bool_t          EF_L1ItemStreamer_L1_MU15;
   Bool_t          EF_L1ItemStreamer_L1_MU20;
   Bool_t          EF_L1ItemStreamer_L1_MU6;
   Bool_t          EF_L1ItemStreamer_L1_MU6_EM3;
   Bool_t          EF_L1ItemStreamer_L1_MU6_EMPTY;
   Bool_t          EF_L1ItemStreamer_L1_MU6_FIRSTEMPTY;
   Bool_t          EF_L1ItemStreamer_L1_MU6_J5;
   Bool_t          EF_L1ItemStreamer_L1_MU6_UNPAIRED;
   //Bool_t          EF_mu0_missingRoi;
   //Bool_t          EF_mu0_rpcOnly;
   Bool_t          EF_mu10;
   Bool_t          EF_mu10_MG;
   Bool_t          EF_mu10_MSonly;
   Bool_t          EF_mu10_MSonly_cosmic;
   Bool_t          EF_mu10_NoIDTrkCut;
   Bool_t          EF_mu10_SiTrk;
   Bool_t          EF_mu10_cosmic;
   Bool_t          EF_mu10_muCombTag;
   Bool_t          EF_mu10_muCombTag_SiTrk;
   Bool_t          EF_mu10_passHLT;
   Bool_t          EF_mu10i_loose;
   Bool_t          EF_mu13;
   Bool_t          EF_mu15;
   Bool_t          EF_mu20;
   Bool_t          EF_mu20_MSonly;
   Bool_t          EF_mu20_passHLT;
   Bool_t          EF_mu4;
   Bool_t          EF_mu4_DiMu;
   Bool_t          EF_mu4_DiMu_FS;
   Bool_t          EF_mu4_DiMu_FS_noOS;
   //Bool_t          EF_mu4_Jpsie5e3;
   //Bool_t          EF_mu4_Jpsie5e3_FS;
   //Bool_t          EF_mu4_Jpsie5e3_SiTrk;
   //Bool_t          EF_mu4_Jpsie5e3_SiTrk_FS;
   Bool_t          EF_mu4_L2MSonly_EFFS_passL2;
   Bool_t          EF_mu4_MG;
   Bool_t          EF_mu4_MSonly;
   Bool_t          EF_mu4_MSonly_EFFS_passL2;
   Bool_t          EF_mu4_MSonly_MB2_noL2_EFFS;
   Bool_t          EF_mu4_MSonly_Trk_Jpsi_loose;
   Bool_t          EF_mu4_MSonly_Trk_Upsi_loose_FS;
   Bool_t          EF_mu4_MSonly_cosmic;
   Bool_t          EF_mu4_MSonly_firstempty;
   Bool_t          EF_mu4_MV;
   Bool_t          EF_mu4_NoIDTrkCut;
   Bool_t          EF_mu4_SiTrk;
   Bool_t          EF_mu4_Trk_Jpsi_loose;
   Bool_t          EF_mu4_Trk_Upsi_loose_FS;
   Bool_t          EF_mu4_comm;
   Bool_t          EF_mu4_comm_MSonly;
   Bool_t          EF_mu4_comm_MSonly_cosmic;
   Bool_t          EF_mu4_comm_MSonly_firstempty;
   Bool_t          EF_mu4_comm_cosmic;
   Bool_t          EF_mu4_comm_firstempty;
   Bool_t          EF_mu4_cosmic;
   Bool_t          EF_mu4_firstempty;
   Bool_t          EF_mu4_j10_matched;
   Bool_t          EF_mu4_j20_matched;
   Bool_t          EF_mu4_j5_matched;
   Bool_t          EF_mu4_mu6;
   Bool_t          EF_mu4_muCombTag;
   Bool_t          EF_mu4_muCombTag_SiTrk;
   Bool_t          EF_mu4_passHLT;
   Bool_t          EF_mu4_tile;
   Bool_t          EF_mu4_tile_SiTrk;
   Bool_t          EF_mu4_trod;
   Bool_t          EF_mu4_trod_SiTrk;
   //Bool_t          EF_mu4_unpaired;
   Bool_t          EF_mu4mu6_DiMu;
   Bool_t          EF_mu6;
   Bool_t          EF_mu6_DiMu;
   Bool_t          EF_mu6_DiMu_FS;
   Bool_t          EF_mu6_DiMu_FS_noOS;
   Bool_t          EF_mu6_DsPhiPi;
   Bool_t          EF_mu6_Jpsie5e3;
   //Bool_t          EF_mu6_Jpsie5e3_FS;
   //Bool_t          EF_mu6_Jpsie5e3_SiTrk;
   //Bool_t          EF_mu6_Jpsie5e3_SiTrk_FS;
   Bool_t          EF_mu6_MG;
   Bool_t          EF_mu6_MSonly;
   Bool_t          EF_mu6_MSonly_cosmic;
   Bool_t          EF_mu6_MSonly_firstempty;
   Bool_t          EF_mu6_MSonly_unpaired;
   Bool_t          EF_mu6_SiTrk;
   Bool_t          EF_mu6_Trk_Jpsi_loose;
   Bool_t          EF_mu6_Trk_Jpsi_loose_FS;
   Bool_t          EF_mu6_Trk_Upsi_loose_FS;
   Bool_t          EF_mu6_cosmic;
   Bool_t          EF_mu6_firstempty;
   Bool_t          EF_mu6_muCombTag;
   Bool_t          EF_mu6_muCombTag_SiTrk;
   Bool_t          EF_mu6_passHLT;
   Bool_t          EF_mu6_unpaired;
   Bool_t          L1_2EM2;
   Bool_t          L1_2EM3;
   Bool_t          L1_2EM4;
   Bool_t          L1_2EM5;
   Bool_t          L1_2MU0;
   Bool_t          L1_2MU0_MU6;
   Bool_t          L1_2MU10;
   Bool_t          L1_2MU6;
   Bool_t          L1_EM10;
   Bool_t          L1_EM10I;
   Bool_t          L1_EM14;
   Bool_t          L1_EM2;
   //Bool_t          L1_EM2_UNPAIRED;
   Bool_t          L1_EM3;
   Bool_t          L1_EM3_EMPTY;
   Bool_t          L1_EM3_FIRSTEMPTY;
   Bool_t          L1_EM3_MV;
   Bool_t          L1_EM3_UNPAIRED;
   Bool_t          L1_EM4;
   Bool_t          L1_EM5;
   Bool_t          L1_EM5I;
   Bool_t          L1_MU0;
   Bool_t          L1_MU0_COMM;
   Bool_t          L1_MU0_COMM_EMPTY;
   Bool_t          L1_MU0_COMM_FIRSTEMPTY;
   Bool_t          L1_MU0_EM3;
   Bool_t          L1_MU0_EMPTY;
   Bool_t          L1_MU0_FIRSTEMPTY;
   Bool_t          L1_MU0_J10;
   Bool_t          L1_MU0_J15;
   Bool_t          L1_MU0_J5;
   Bool_t          L1_MU0_MV;
   //Bool_t          L1_MU0_UNPAIRED;
   Bool_t          L1_MU10;
   Bool_t          L1_MU10_EMPTY;
   Bool_t          L1_MU15;
   Bool_t          L1_MU20;
   Bool_t          L1_MU6;
   Bool_t          L1_MU6_EM3;
   Bool_t          L1_MU6_EMPTY;
   Bool_t          L1_MU6_FIRSTEMPTY;
   Bool_t          L1_MU6_J5;
   Bool_t          L1_MU6_UNPAIRED;
   Bool_t          L2_2mu10;
   Bool_t          L2_2mu4;
   Bool_t          L2_2mu4_DiMu;
   Bool_t          L2_2mu4_DiMu_SiTrk;
   Bool_t          L2_2mu4_DiMu_noOS;
   Bool_t          L2_2mu4_DiMu_noOS_passL2;
   Bool_t          L2_2mu4_DiMu_noVtx_noOS;
   Bool_t          L2_2mu4_DiMu_noVtx_noOS_passL2;
   Bool_t          L2_2mu4_MSonly;
   Bool_t          L2_2mu6;
   Bool_t          L2_2mu6_DiMu;
   Bool_t          L2_2mu6_DiMu_noVtx_noOS;
   Bool_t          L2_L1ItemStreamer_L1_MU0;
   Bool_t          L2_L1ItemStreamer_L1_MU0_COMM;
   Bool_t          L2_L1ItemStreamer_L1_MU0_COMM_EMPTY;
   Bool_t          L2_L1ItemStreamer_L1_MU0_COMM_FIRSTEMPTY;
   Bool_t          L2_L1ItemStreamer_L1_MU0_EM3;
   Bool_t          L2_L1ItemStreamer_L1_MU0_EMPTY;
   Bool_t          L2_L1ItemStreamer_L1_MU0_FIRSTEMPTY;
   Bool_t          L2_L1ItemStreamer_L1_MU0_J10;
   Bool_t          L2_L1ItemStreamer_L1_MU0_J15;
   Bool_t          L2_L1ItemStreamer_L1_MU0_J5;
   Bool_t          L2_L1ItemStreamer_L1_MU0_MV;
   //Bool_t          L2_L1ItemStreamer_L1_MU0_UNPAIRED;
   Bool_t          L2_L1ItemStreamer_L1_MU10;
   Bool_t          L2_L1ItemStreamer_L1_MU10_EMPTY;
   Bool_t          L2_L1ItemStreamer_L1_MU15;
   Bool_t          L2_L1ItemStreamer_L1_MU20;
   Bool_t          L2_L1ItemStreamer_L1_MU6;
   Bool_t          L2_L1ItemStreamer_L1_MU6_EM3;
   Bool_t          L2_L1ItemStreamer_L1_MU6_EMPTY;
   Bool_t          L2_L1ItemStreamer_L1_MU6_FIRSTEMPTY;
   Bool_t          L2_L1ItemStreamer_L1_MU6_J5;
   Bool_t          L2_L1ItemStreamer_L1_MU6_UNPAIRED;
   //Bool_t          L2_mu0_missingRoi;
   //Bool_t          L2_mu0_rpcOnly;
   Bool_t          L2_mu10;
   Bool_t          L2_mu10_MG;
   Bool_t          L2_mu10_MSonly;
   Bool_t          L2_mu10_MSonly_cosmic;
   Bool_t          L2_mu10_NoIDTrkCut;
   Bool_t          L2_mu10_SiTrk;
   Bool_t          L2_mu10_cosmic;
   Bool_t          L2_mu10_muCombTag;
   Bool_t          L2_mu10_muCombTag_SiTrk;
   Bool_t          L2_mu10_passHLT;
   Bool_t          L2_mu10i_loose;
   Bool_t          L2_mu13 ;
   Bool_t          L2_mu15;
   Bool_t          L2_mu20;
   Bool_t          L2_mu20_MSonly;
   Bool_t          L2_mu20_passHLT;
   Bool_t          L2_mu4;
   Bool_t          L2_mu4_DiMu;
   Bool_t          L2_mu4_DiMu_FS;
   Bool_t          L2_mu4_DiMu_FS_noOS;
   //Bool_t          L2_mu4_Jpsie5e3;
   //Bool_t          L2_mu4_Jpsie5e3_FS;
   //Bool_t          L2_mu4_Jpsie5e3_SiTrk;
   //Bool_t          L2_mu4_Jpsie5e3_SiTrk_FS;
   Bool_t          L2_mu4_L2MSonly_EFFS_passL2;
   Bool_t          L2_mu4_MG;
   Bool_t          L2_mu4_MSonly;
   Bool_t          L2_mu4_MSonly_EFFS_passL2;
   Bool_t          L2_mu4_MSonly_MB2_noL2_EFFS;
   Bool_t          L2_mu4_MSonly_Trk_Jpsi_loose;
   Bool_t          L2_mu4_MSonly_Trk_Upsi_loose_FS;
   Bool_t          L2_mu4_MSonly_cosmic;
   Bool_t          L2_mu4_MSonly_firstempty;
   Bool_t          L2_mu4_MV;
   Bool_t          L2_mu4_NoIDTrkCut;
   Bool_t          L2_mu4_SiTrk;
   Bool_t          L2_mu4_Trk_Jpsi_loose;
   Bool_t          L2_mu4_Trk_Upsi_loose_FS;
   Bool_t          L2_mu4_comm;
   Bool_t          L2_mu4_comm_MSonly;
   Bool_t          L2_mu4_comm_MSonly_cosmic;
   Bool_t          L2_mu4_comm_MSonly_firstempty;
   Bool_t          L2_mu4_comm_cosmic;
   Bool_t          L2_mu4_comm_firstempty;
   Bool_t          L2_mu4_cosmic;
   Bool_t          L2_mu4_firstempty;
   Bool_t          L2_mu4_j10_matched;
   Bool_t          L2_mu4_j20_matched;
   Bool_t          L2_mu4_j5_matched;
   Bool_t          L2_mu4_mu6;
   Bool_t          L2_mu4_muCombTag;
   Bool_t          L2_mu4_muCombTag_SiTrk;
   Bool_t          L2_mu4_passHLT;
   Bool_t          L2_mu4_tile;
   Bool_t          L2_mu4_tile_SiTrk;
   Bool_t          L2_mu4_trod;
   Bool_t          L2_mu4_trod_SiTrk;
   //Bool_t          L2_mu4_unpaired;
   Bool_t          L2_mu4mu6_DiMu;
   Bool_t          L2_mu6;
   Bool_t          L2_mu6_DiMu;
   Bool_t          L2_mu6_DiMu_FS;
   Bool_t          L2_mu6_DiMu_FS_noOS;
   Bool_t          L2_mu6_DsPhiPi;
   Bool_t          L2_mu6_Jpsie5e3;
   //Bool_t          L2_mu6_Jpsie5e3_FS;
   //Bool_t          L2_mu6_Jpsie5e3_SiTrk;
   //Bool_t          L2_mu6_Jpsie5e3_SiTrk_FS;
   Bool_t          L2_mu6_MG;
   Bool_t          L2_mu6_MSonly;
   Bool_t          L2_mu6_MSonly_cosmic;
   Bool_t          L2_mu6_MSonly_firstempty;
   Bool_t          L2_mu6_MSonly_unpaired;
   Bool_t          L2_mu6_SiTrk;
   Bool_t          L2_mu6_Trk_Jpsi_loose;
   Bool_t          L2_mu6_Trk_Jpsi_loose_FS;
   Bool_t          L2_mu6_Trk_Upsi_loose_FS;
   Bool_t          L2_mu6_cosmic;
   Bool_t          L2_mu6_firstempty;
   Bool_t          L2_mu6_muCombTag;
   Bool_t          L2_mu6_muCombTag_SiTrk;
   Bool_t          L2_mu6_passHLT;
   Bool_t          L2_mu6_unpaired;
   Int_t           mu_staco_n;
   vector<float>   *mu_staco_E;
   vector<float>   *mu_staco_px;
   vector<float>   *mu_staco_py;
   vector<float>   *mu_staco_pz;
   vector<float>   *mu_staco_m;
   vector<float>   *mu_staco_charge;
   vector<float>   *mu_staco_pt;
   vector<float>   *mu_staco_eta;
   vector<float>   *mu_staco_phi;
   vector<unsigned short> *mu_staco_allauthor;
   vector<int>     *mu_staco_author;
   vector<float>   *mu_staco_matchchi2;
   vector<int>     *mu_staco_matchndof;
   vector<float>   *mu_staco_etcone20;
   vector<float>   *mu_staco_etcone30;
   vector<float>   *mu_staco_etcone40;
   vector<float>   *mu_staco_nucone20;
   vector<float>   *mu_staco_nucone30;
   vector<float>   *mu_staco_nucone40;
   vector<float>   *mu_staco_ptcone20;
   vector<float>   *mu_staco_ptcone30;
   vector<float>   *mu_staco_ptcone40;
   vector<float>   *mu_staco_energyLossPar;
   vector<float>   *mu_staco_energyLossErr;
   vector<int>     *mu_staco_bestMatch;
   vector<int>     *mu_staco_isStandAloneMuon;
   vector<int>     *mu_staco_isCombinedMuon;
   vector<int>     *mu_staco_isLowPtReconstructedMuon;
   vector<float>   *mu_staco_d0_exPV;
   vector<float>   *mu_staco_z0_exPV;
   vector<float>   *mu_staco_phi_exPV;
   vector<float>   *mu_staco_theta_exPV;
   vector<float>   *mu_staco_qoverp_exPV;
   vector<float>   *mu_staco_cov_d0_exPV;
   vector<float>   *mu_staco_cov_z0_exPV;
   vector<float>   *mu_staco_cov_phi_exPV;
   vector<float>   *mu_staco_cov_theta_exPV;
   vector<float>   *mu_staco_cov_qoverp_exPV;
   vector<float>   *mu_staco_cov_d0_z0_exPV;
   vector<float>   *mu_staco_cov_d0_phi_exPV;
   vector<float>   *mu_staco_cov_d0_theta_exPV;
   vector<float>   *mu_staco_cov_d0_qoverp_exPV;
   vector<float>   *mu_staco_cov_z0_phi_exPV;
   vector<float>   *mu_staco_cov_z0_theta_exPV;
   vector<float>   *mu_staco_cov_z0_qoverp_exPV;
   vector<float>   *mu_staco_cov_phi_theta_exPV;
   vector<float>   *mu_staco_cov_phi_qoverp_exPV;
   vector<float>   *mu_staco_cov_theta_qoverp_exPV;
   vector<float>   *mu_staco_ms_d0;
   vector<float>   *mu_staco_ms_z0;
   vector<float>   *mu_staco_ms_phi;
   vector<float>   *mu_staco_ms_theta;
   vector<float>   *mu_staco_ms_qoverp;
   vector<float>   *mu_staco_id_d0;
   vector<float>   *mu_staco_id_z0;
   vector<float>   *mu_staco_id_phi;
   vector<float>   *mu_staco_id_theta;
   vector<float>   *mu_staco_id_qoverp;
   vector<float>   *mu_staco_me_d0;
   vector<float>   *mu_staco_me_z0;
   vector<float>   *mu_staco_me_phi;
   vector<float>   *mu_staco_me_theta;
   vector<float>   *mu_staco_me_qoverp;
   vector<float>   *mu_staco_ie_d0;
   vector<float>   *mu_staco_ie_z0;
   vector<float>   *mu_staco_ie_phi;
   vector<float>   *mu_staco_ie_theta;
   vector<float>   *mu_staco_ie_qoverp;
   vector<int>     *mu_staco_nBLHits;
   vector<int>     *mu_staco_nPixHits;
   vector<int>     *mu_staco_nSCTHits;
   vector<int>     *mu_staco_nTRTHits;
   vector<int>     *mu_staco_nTRTHighTHits;
   vector<int>     *mu_staco_nBLSharedHits;
   vector<int>     *mu_staco_nPixSharedHits;
   vector<int>     *mu_staco_nPixHoles;
   vector<int>     *mu_staco_nSCTSharedHits;
   vector<int>     *mu_staco_nSCTHoles;
   vector<int>     *mu_staco_nTRTOutliers;
   vector<int>     *mu_staco_nTRTHighTOutliers;
   vector<int>     *mu_staco_nMDTHits;
   vector<int>     *mu_staco_nMDTHoles;
   vector<int>     *mu_staco_nCSCEtaHits;
   vector<int>     *mu_staco_nCSCEtaHoles;
   vector<int>     *mu_staco_nCSCPhiHits;
   vector<int>     *mu_staco_nCSCPhiHoles;
   vector<int>     *mu_staco_nRPCEtaHits;
   vector<int>     *mu_staco_nRPCEtaHoles;
   vector<int>     *mu_staco_nRPCPhiHits;
   vector<int>     *mu_staco_nRPCPhiHoles;
   vector<int>     *mu_staco_nTGCEtaHits;
   vector<int>     *mu_staco_nTGCEtaHoles;
   vector<int>     *mu_staco_nTGCPhiHits;
   vector<int>     *mu_staco_nTGCPhiHoles;
   vector<int>     *mu_staco_nGangedPixels;
   vector<int>     *mu_staco_nOutliersOnTrack;
   vector<int>     *mu_staco_nMDTBIHits;
   vector<int>     *mu_staco_nMDTBMHits;
   vector<int>     *mu_staco_nMDTBOHits;
   vector<int>     *mu_staco_nMDTBEEHits;
   vector<int>     *mu_staco_nMDTBIS78Hits;
   vector<int>     *mu_staco_nMDTEIHits;
   vector<int>     *mu_staco_nMDTEMHits;
   vector<int>     *mu_staco_nMDTEOHits;
   vector<int>     *mu_staco_nMDTEEHits;
   vector<int>     *mu_staco_nRPCLayer1EtaHits;
   vector<int>     *mu_staco_nRPCLayer2EtaHits;
   vector<int>     *mu_staco_nRPCLayer3EtaHits;
   vector<int>     *mu_staco_nRPCLayer1PhiHits;
   vector<int>     *mu_staco_nRPCLayer2PhiHits;
   vector<int>     *mu_staco_nRPCLayer3PhiHits;
   vector<int>     *mu_staco_nTGCLayer1EtaHits;
   vector<int>     *mu_staco_nTGCLayer2EtaHits;
   vector<int>     *mu_staco_nTGCLayer3EtaHits;
   vector<int>     *mu_staco_nTGCLayer4EtaHits;
   vector<int>     *mu_staco_nTGCLayer1PhiHits;
   vector<int>     *mu_staco_nTGCLayer2PhiHits;
   vector<int>     *mu_staco_nTGCLayer3PhiHits;
   vector<int>     *mu_staco_nTGCLayer4PhiHits;
   vector<int>     *mu_staco_barrelSectors;
   vector<int>     *mu_staco_endcapSectors;
   vector<float>   *mu_staco_trackd0;
   vector<float>   *mu_staco_trackz0;
   vector<float>   *mu_staco_trackphi;
   vector<float>   *mu_staco_tracktheta;
   vector<float>   *mu_staco_trackqoverp;
   vector<float>   *mu_staco_trackcov_d0;
   vector<float>   *mu_staco_trackcov_z0;
   vector<float>   *mu_staco_trackcov_phi;
   vector<float>   *mu_staco_trackcov_theta;
   vector<float>   *mu_staco_trackcov_qoverp;
   vector<float>   *mu_staco_trackcov_d0_z0;
   vector<float>   *mu_staco_trackcov_d0_phi;
   vector<float>   *mu_staco_trackcov_d0_theta;
   vector<float>   *mu_staco_trackcov_d0_qoverp;
   vector<float>   *mu_staco_trackcov_z0_phi;
   vector<float>   *mu_staco_trackcov_z0_theta;
   vector<float>   *mu_staco_trackcov_z0_qoverp;
   vector<float>   *mu_staco_trackcov_phi_theta;
   vector<float>   *mu_staco_trackcov_phi_qoverp;
   vector<float>   *mu_staco_trackcov_theta_qoverp;
   vector<float>   *mu_staco_trackfitchi2;
   vector<int>     *mu_staco_trackfitndof;
   vector<int>     *mu_staco_hastrack;
   vector<float>   *mu_staco_EF_dr;
   vector<float>   *mu_staco_EF_cb_eta;
   vector<float>   *mu_staco_EF_cb_phi;
   vector<float>   *mu_staco_EF_cb_pt;
   vector<float>   *mu_staco_EF_ms_eta;
   vector<float>   *mu_staco_EF_ms_phi;
   vector<float>   *mu_staco_EF_ms_pt;
   vector<float>   *mu_staco_EF_me_eta;
   vector<float>   *mu_staco_EF_me_phi;
   vector<float>   *mu_staco_EF_me_pt;
   vector<int>     *mu_staco_EF_matched;
   vector<float>   *mu_staco_L2CB_dr;
   vector<float>   *mu_staco_L2CB_pt;
   vector<float>   *mu_staco_L2CB_eta;
   vector<float>   *mu_staco_L2CB_phi;
   vector<float>   *mu_staco_L2CB_id_pt;
   vector<float>   *mu_staco_L2CB_ms_pt;
   vector<int>     *mu_staco_L2CB_nPixHits;
   vector<int>     *mu_staco_L2CB_nSCTHits;
   vector<int>     *mu_staco_L2CB_nTRTHits;
   vector<int>     *mu_staco_L2CB_nTRTHighTHits;
   vector<int>     *mu_staco_L2CB_matched;
   vector<float>   *mu_staco_L1_dr;
   vector<float>   *mu_staco_L1_pt;
   vector<float>   *mu_staco_L1_eta;
   vector<float>   *mu_staco_L1_phi;
   vector<short>   *mu_staco_L1_thrNumber;
   vector<short>   *mu_staco_L1_RoINumber;
   vector<short>   *mu_staco_L1_sectorAddress;
   vector<int>     *mu_staco_L1_firstCandidate;
   vector<int>     *mu_staco_L1_moreCandInRoI;
   vector<int>     *mu_staco_L1_moreCandInSector;
   vector<short>   *mu_staco_L1_source;
   vector<short>   *mu_staco_L1_hemisphere;
   vector<int>     *mu_staco_L1_matched;
   Int_t           mu_muid_n;
   vector<float>   *mu_muid_E;
   vector<float>   *mu_muid_px;
   vector<float>   *mu_muid_py;
   vector<float>   *mu_muid_pz;
   vector<float>   *mu_muid_m;
   vector<float>   *mu_muid_charge;
   vector<float>   *mu_muid_pt;
   vector<float>   *mu_muid_eta;
   vector<float>   *mu_muid_phi;
   vector<unsigned short> *mu_muid_allauthor;
   vector<int>     *mu_muid_author;
   vector<float>   *mu_muid_matchchi2;
   vector<int>     *mu_muid_matchndof;
   vector<float>   *mu_muid_etcone20;
   vector<float>   *mu_muid_etcone30;
   vector<float>   *mu_muid_etcone40;
   vector<float>   *mu_muid_nucone20;
   vector<float>   *mu_muid_nucone30;
   vector<float>   *mu_muid_nucone40;
   vector<float>   *mu_muid_ptcone20;
   vector<float>   *mu_muid_ptcone30;
   vector<float>   *mu_muid_ptcone40;
   vector<float>   *mu_muid_energyLossPar;
   vector<float>   *mu_muid_energyLossErr;
   vector<int>     *mu_muid_bestMatch;
   vector<int>     *mu_muid_isStandAloneMuon;
   vector<int>     *mu_muid_isCombinedMuon;
   vector<int>     *mu_muid_isLowPtReconstructedMuon;
   vector<float>   *mu_muid_d0_exPV;
   vector<float>   *mu_muid_z0_exPV;
   vector<float>   *mu_muid_phi_exPV;
   vector<float>   *mu_muid_theta_exPV;
   vector<float>   *mu_muid_qoverp_exPV;
   vector<float>   *mu_muid_cov_d0_exPV;
   vector<float>   *mu_muid_cov_z0_exPV;
   vector<float>   *mu_muid_cov_phi_exPV;
   vector<float>   *mu_muid_cov_theta_exPV;
   vector<float>   *mu_muid_cov_qoverp_exPV;
   vector<float>   *mu_muid_cov_d0_z0_exPV;
   vector<float>   *mu_muid_cov_d0_phi_exPV;
   vector<float>   *mu_muid_cov_d0_theta_exPV;
   vector<float>   *mu_muid_cov_d0_qoverp_exPV;
   vector<float>   *mu_muid_cov_z0_phi_exPV;
   vector<float>   *mu_muid_cov_z0_theta_exPV;
   vector<float>   *mu_muid_cov_z0_qoverp_exPV;
   vector<float>   *mu_muid_cov_phi_theta_exPV;
   vector<float>   *mu_muid_cov_phi_qoverp_exPV;
   vector<float>   *mu_muid_cov_theta_qoverp_exPV;
   vector<float>   *mu_muid_ms_d0;
   vector<float>   *mu_muid_ms_z0;
   vector<float>   *mu_muid_ms_phi;
   vector<float>   *mu_muid_ms_theta;
   vector<float>   *mu_muid_ms_qoverp;
   vector<float>   *mu_muid_id_d0;
   vector<float>   *mu_muid_id_z0;
   vector<float>   *mu_muid_id_phi;
   vector<float>   *mu_muid_id_theta;
   vector<float>   *mu_muid_id_qoverp;
   vector<float>   *mu_muid_me_d0;
   vector<float>   *mu_muid_me_z0;
   vector<float>   *mu_muid_me_phi;
   vector<float>   *mu_muid_me_theta;
   vector<float>   *mu_muid_me_qoverp;
   vector<float>   *mu_muid_ie_d0;
   vector<float>   *mu_muid_ie_z0;
   vector<float>   *mu_muid_ie_phi;
   vector<float>   *mu_muid_ie_theta;
   vector<float>   *mu_muid_ie_qoverp;
   vector<int>     *mu_muid_nBLHits;
   vector<int>     *mu_muid_nPixHits;
   vector<int>     *mu_muid_nSCTHits;
   vector<int>     *mu_muid_nTRTHits;
   vector<int>     *mu_muid_nTRTHighTHits;
   vector<int>     *mu_muid_nBLSharedHits;
   vector<int>     *mu_muid_nPixSharedHits;
   vector<int>     *mu_muid_nPixHoles;
   vector<int>     *mu_muid_nSCTSharedHits;
   vector<int>     *mu_muid_nSCTHoles;
   vector<int>     *mu_muid_nTRTOutliers;
   vector<int>     *mu_muid_nTRTHighTOutliers;
   vector<int>     *mu_muid_nMDTHits;
   vector<int>     *mu_muid_nMDTHoles;
   vector<int>     *mu_muid_nCSCEtaHits;
   vector<int>     *mu_muid_nCSCEtaHoles;
   vector<int>     *mu_muid_nCSCPhiHits;
   vector<int>     *mu_muid_nCSCPhiHoles;
   vector<int>     *mu_muid_nRPCEtaHits;
   vector<int>     *mu_muid_nRPCEtaHoles;
   vector<int>     *mu_muid_nRPCPhiHits;
   vector<int>     *mu_muid_nRPCPhiHoles;
   vector<int>     *mu_muid_nTGCEtaHits;
   vector<int>     *mu_muid_nTGCEtaHoles;
   vector<int>     *mu_muid_nTGCPhiHits;
   vector<int>     *mu_muid_nTGCPhiHoles;
   vector<int>     *mu_muid_nGangedPixels;
   vector<int>     *mu_muid_nOutliersOnTrack;
   vector<int>     *mu_muid_nMDTBIHits;
   vector<int>     *mu_muid_nMDTBMHits;
   vector<int>     *mu_muid_nMDTBOHits;
   vector<int>     *mu_muid_nMDTBEEHits;
   vector<int>     *mu_muid_nMDTBIS78Hits;
   vector<int>     *mu_muid_nMDTEIHits;
   vector<int>     *mu_muid_nMDTEMHits;
   vector<int>     *mu_muid_nMDTEOHits;
   vector<int>     *mu_muid_nMDTEEHits;
   vector<int>     *mu_muid_nRPCLayer1EtaHits;
   vector<int>     *mu_muid_nRPCLayer2EtaHits;
   vector<int>     *mu_muid_nRPCLayer3EtaHits;
   vector<int>     *mu_muid_nRPCLayer1PhiHits;
   vector<int>     *mu_muid_nRPCLayer2PhiHits;
   vector<int>     *mu_muid_nRPCLayer3PhiHits;
   vector<int>     *mu_muid_nTGCLayer1EtaHits;
   vector<int>     *mu_muid_nTGCLayer2EtaHits;
   vector<int>     *mu_muid_nTGCLayer3EtaHits;
   vector<int>     *mu_muid_nTGCLayer4EtaHits;
   vector<int>     *mu_muid_nTGCLayer1PhiHits;
   vector<int>     *mu_muid_nTGCLayer2PhiHits;
   vector<int>     *mu_muid_nTGCLayer3PhiHits;
   vector<int>     *mu_muid_nTGCLayer4PhiHits;
   vector<int>     *mu_muid_barrelSectors;
   vector<int>     *mu_muid_endcapSectors;
   vector<float>   *mu_muid_trackd0;
   vector<float>   *mu_muid_trackz0;
   vector<float>   *mu_muid_trackphi;
   vector<float>   *mu_muid_tracktheta;
   vector<float>   *mu_muid_trackqoverp;
   vector<float>   *mu_muid_trackcov_d0;
   vector<float>   *mu_muid_trackcov_z0;
   vector<float>   *mu_muid_trackcov_phi;
   vector<float>   *mu_muid_trackcov_theta;
   vector<float>   *mu_muid_trackcov_qoverp;
   vector<float>   *mu_muid_trackcov_d0_z0;
   vector<float>   *mu_muid_trackcov_d0_phi;
   vector<float>   *mu_muid_trackcov_d0_theta;
   vector<float>   *mu_muid_trackcov_d0_qoverp;
   vector<float>   *mu_muid_trackcov_z0_phi;
   vector<float>   *mu_muid_trackcov_z0_theta;
   vector<float>   *mu_muid_trackcov_z0_qoverp;
   vector<float>   *mu_muid_trackcov_phi_theta;
   vector<float>   *mu_muid_trackcov_phi_qoverp;
   vector<float>   *mu_muid_trackcov_theta_qoverp;
   vector<float>   *mu_muid_trackfitchi2;
   vector<int>     *mu_muid_trackfitndof;
   vector<int>     *mu_muid_hastrack;
   vector<float>   *mu_muid_EF_dr;
   vector<float>   *mu_muid_EF_cb_eta;
   vector<float>   *mu_muid_EF_cb_phi;
   vector<float>   *mu_muid_EF_cb_pt;
   vector<float>   *mu_muid_EF_ms_eta;
   vector<float>   *mu_muid_EF_ms_phi;
   vector<float>   *mu_muid_EF_ms_pt;
   vector<float>   *mu_muid_EF_me_eta;
   vector<float>   *mu_muid_EF_me_phi;
   vector<float>   *mu_muid_EF_me_pt;
   vector<int>     *mu_muid_EF_matched;
   vector<float>   *mu_muid_L2CB_dr;
   vector<float>   *mu_muid_L2CB_pt;
   vector<float>   *mu_muid_L2CB_eta;
   vector<float>   *mu_muid_L2CB_phi;
   vector<float>   *mu_muid_L2CB_id_pt;
   vector<float>   *mu_muid_L2CB_ms_pt;
   vector<int>     *mu_muid_L2CB_nPixHits;
   vector<int>     *mu_muid_L2CB_nSCTHits;
   vector<int>     *mu_muid_L2CB_nTRTHits;
   vector<int>     *mu_muid_L2CB_nTRTHighTHits;
   vector<int>     *mu_muid_L2CB_matched;
   vector<float>   *mu_muid_L1_dr;
   vector<float>   *mu_muid_L1_pt;
   vector<float>   *mu_muid_L1_eta;
   vector<float>   *mu_muid_L1_phi;
   vector<short>   *mu_muid_L1_thrNumber;
   vector<short>   *mu_muid_L1_RoINumber;
   vector<short>   *mu_muid_L1_sectorAddress;
   vector<int>     *mu_muid_L1_firstCandidate;
   vector<int>     *mu_muid_L1_moreCandInRoI;
   vector<int>     *mu_muid_L1_moreCandInSector;
   vector<short>   *mu_muid_L1_source;
   vector<short>   *mu_muid_L1_hemisphere;
   vector<int>     *mu_muid_L1_matched;

   // List of branches
   TBranch        *b_isGRL;   //!
   TBranch        *b_RunNumber;   //!
   TBranch        *b_EventNumber;   //!
   TBranch        *b_timestamp;   //!
   TBranch        *b_timestamp_ns;   //!
   TBranch        *b_lbn;   //!
   TBranch        *b_bcid;   //!
   TBranch        *b_detmask0;   //!
   TBranch        *b_detmask1;   //!
   TBranch        *b_pixelFlags;   //!
   TBranch        *b_sctFlags;   //!
   TBranch        *b_trtFlags;   //!
   TBranch        *b_larFlags;   //!
   TBranch        *b_tileFlags;   //!
   TBranch        *b_muonFlags;   //!
   TBranch        *b_fwdFlags;   //!
   TBranch        *b_coreFlags;   //!
   TBranch        *b_pixelError;   //!
   TBranch        *b_sctError;   //!
   TBranch        *b_trtError;   //!
   TBranch        *b_larError;   //!
   TBranch        *b_tileError;   //!
   TBranch        *b_muonError;   //!
   TBranch        *b_fwdError;   //!
   TBranch        *b_coreError;   //!
   TBranch        *b_lar_ncellA;   //!
   TBranch        *b_lar_ncellC;   //!
   TBranch        *b_lar_energyA;   //!
   TBranch        *b_lar_energyC;   //!
   TBranch        *b_lar_timeA;   //!
   TBranch        *b_lar_timeC;   //!
   TBranch        *b_lar_timeDiff;   //!
   TBranch        *b_EF_2mu10;   //!
   TBranch        *b_EF_2mu4;   //!
   TBranch        *b_EF_2mu4_DiMu;   //!
   TBranch        *b_EF_2mu4_DiMu_SiTrk;   //!
   TBranch        *b_EF_2mu4_DiMu_noOS;   //!
   TBranch        *b_EF_2mu4_DiMu_noOS_passL2;   //!
   TBranch        *b_EF_2mu4_DiMu_noVtx_noOS;   //!
   TBranch        *b_EF_2mu4_DiMu_noVtx_noOS_passL2;   //!
   TBranch        *b_EF_2mu4_MSonly;   //!
   TBranch        *b_EF_2mu6;   //!
   TBranch        *b_EF_2mu6_DiMu;   //!
   TBranch        *b_EF_2mu6_DiMu_noVtx_noOS;   //!
   TBranch        *b_EF_L1ItemStreamer_L1_2MU0;   //!
   TBranch        *b_EF_L1ItemStreamer_L1_2MU0_MU6;   //!
   TBranch        *b_EF_L1ItemStreamer_L1_2MU10;   //!
   TBranch        *b_EF_L1ItemStreamer_L1_2MU6;   //!
   TBranch        *b_EF_L1ItemStreamer_L1_EM10;   //!
   TBranch        *b_EF_L1ItemStreamer_L1_EM10I;   //!
   TBranch        *b_EF_L1ItemStreamer_L1_EM14;   //!
   TBranch        *b_EF_L1ItemStreamer_L1_EM2;   //!
   //TBranch        *b_EF_L1ItemStreamer_L1_EM2_UNPAIRED;   //!
   TBranch        *b_EF_L1ItemStreamer_L1_EM3;   //!
   TBranch        *b_EF_L1ItemStreamer_L1_EM3_EMPTY;   //!
   TBranch        *b_EF_L1ItemStreamer_L1_EM3_FIRSTEMPTY;   //!
   TBranch        *b_EF_L1ItemStreamer_L1_EM3_MV;   //!
   TBranch        *b_EF_L1ItemStreamer_L1_EM3_UNPAIRED;   //!
   TBranch        *b_EF_L1ItemStreamer_L1_EM4;   //!
   TBranch        *b_EF_L1ItemStreamer_L1_EM5;   //!
   TBranch        *b_EF_L1ItemStreamer_L1_EM5I;   //!
   TBranch        *b_EF_L1ItemStreamer_L1_MU0;   //!
   TBranch        *b_EF_L1ItemStreamer_L1_MU0_COMM;   //!
   TBranch        *b_EF_L1ItemStreamer_L1_MU0_COMM_EMPTY;   //!
   TBranch        *b_EF_L1ItemStreamer_L1_MU0_COMM_FIRSTEMPTY;   //!
   TBranch        *b_EF_L1ItemStreamer_L1_MU0_EM3;   //!
   TBranch        *b_EF_L1ItemStreamer_L1_MU0_EMPTY;   //!
   TBranch        *b_EF_L1ItemStreamer_L1_MU0_FIRSTEMPTY;   //!
   TBranch        *b_EF_L1ItemStreamer_L1_MU0_J10;   //!
   TBranch        *b_EF_L1ItemStreamer_L1_MU0_J15;   //!
   TBranch        *b_EF_L1ItemStreamer_L1_MU0_J5;   //!
   TBranch        *b_EF_L1ItemStreamer_L1_MU0_MV;   //!
   TBranch        *b_EF_L1ItemStreamer_L1_MU0_UNPAIRED;   //!
   TBranch        *b_EF_L1ItemStreamer_L1_MU10;   //!
   TBranch        *b_EF_L1ItemStreamer_L1_MU10_EMPTY;   //!
   TBranch        *b_EF_L1ItemStreamer_L1_MU15;   //!
   TBranch        *b_EF_L1ItemStreamer_L1_MU20;   //!
   TBranch        *b_EF_L1ItemStreamer_L1_MU6;   //!
   TBranch        *b_EF_L1ItemStreamer_L1_MU6_EM3;   //!
   TBranch        *b_EF_L1ItemStreamer_L1_MU6_EMPTY;   //!
   TBranch        *b_EF_L1ItemStreamer_L1_MU6_FIRSTEMPTY;   //!
   TBranch        *b_EF_L1ItemStreamer_L1_MU6_J5;   //!
   TBranch        *b_EF_L1ItemStreamer_L1_MU6_UNPAIRED;   //!
   //TBranch        *b_EF_mu0_missingRoi;   //!
   //TBranch        *b_EF_mu0_rpcOnly;   //!
   TBranch        *b_EF_mu10;   //!
   TBranch        *b_EF_mu10_MG;   //!
   TBranch        *b_EF_mu10_MSonly;   //!
   TBranch        *b_EF_mu10_MSonly_cosmic;   //!
   TBranch        *b_EF_mu10_NoIDTrkCut;   //!
   TBranch        *b_EF_mu10_SiTrk;   //!
   TBranch        *b_EF_mu10_cosmic;   //!
   TBranch        *b_EF_mu10_muCombTag;   //!
   TBranch        *b_EF_mu10_muCombTag_SiTrk;   //!
   TBranch        *b_EF_mu10_passHLT;   //!
   TBranch        *b_EF_mu10i_loose;   //!
   TBranch        *b_EF_mu13;   //!
   TBranch        *b_EF_mu15;   //!
   TBranch        *b_EF_mu20;   //!
   TBranch        *b_EF_mu20_MSonly;   //!
   TBranch        *b_EF_mu20_passHLT;   //!
   TBranch        *b_EF_mu4;   //!
   TBranch        *b_EF_mu4_DiMu;   //!
   TBranch        *b_EF_mu4_DiMu_FS;   //!
   TBranch        *b_EF_mu4_DiMu_FS_noOS;   //!
   //TBranch        *b_EF_mu4_Jpsie5e3;   //!
   //TBranch        *b_EF_mu4_Jpsie5e3_FS;   //!
   //TBranch        *b_EF_mu4_Jpsie5e3_SiTrk;   //!
   //TBranch        *b_EF_mu4_Jpsie5e3_SiTrk_FS;   //!
   TBranch        *b_EF_mu4_L2MSonly_EFFS_passL2;   //!
   TBranch        *b_EF_mu4_MG;   //!
   TBranch        *b_EF_mu4_MSonly;   //!
   TBranch        *b_EF_mu4_MSonly_EFFS_passL2;   //!
   TBranch        *b_EF_mu4_MSonly_MB2_noL2_EFFS;   //!
   TBranch        *b_EF_mu4_MSonly_Trk_Jpsi_loose;   //!
   TBranch        *b_EF_mu4_MSonly_Trk_Upsi_loose_FS;   //!
   TBranch        *b_EF_mu4_MSonly_cosmic;   //!
   TBranch        *b_EF_mu4_MSonly_firstempty;   //!
   TBranch        *b_EF_mu4_MV;   //!
   TBranch        *b_EF_mu4_NoIDTrkCut;   //!
   TBranch        *b_EF_mu4_SiTrk;   //!
   TBranch        *b_EF_mu4_Trk_Jpsi_loose;   //!
   TBranch        *b_EF_mu4_Trk_Upsi_loose_FS;   //!
   TBranch        *b_EF_mu4_comm;   //!
   TBranch        *b_EF_mu4_comm_MSonly;   //!
   TBranch        *b_EF_mu4_comm_MSonly_cosmic;   //!
   TBranch        *b_EF_mu4_comm_MSonly_firstempty;   //!
   TBranch        *b_EF_mu4_comm_cosmic;   //!
   TBranch        *b_EF_mu4_comm_firstempty;   //!
   TBranch        *b_EF_mu4_cosmic;   //!
   TBranch        *b_EF_mu4_firstempty;   //!
   TBranch        *b_EF_mu4_j10_matched;   //!
   TBranch        *b_EF_mu4_j20_matched;   //!
   TBranch        *b_EF_mu4_j5_matched;   //!
   TBranch        *b_EF_mu4_mu6;   //!
   TBranch        *b_EF_mu4_muCombTag;   //!
   TBranch        *b_EF_mu4_muCombTag_SiTrk;   //!
   TBranch        *b_EF_mu4_passHLT;   //!
   TBranch        *b_EF_mu4_tile;   //!
   TBranch        *b_EF_mu4_tile_SiTrk;   //!
   TBranch        *b_EF_mu4_trod;   //!
   TBranch        *b_EF_mu4_trod_SiTrk;   //!
   //TBranch        *b_EF_mu4_unpaired;   //!
   TBranch        *b_EF_mu4mu6_DiMu;   //!
   TBranch        *b_EF_mu6;   //!
   TBranch        *b_EF_mu6_DiMu;   //!
   TBranch        *b_EF_mu6_DiMu_FS;   //!
   TBranch        *b_EF_mu6_DiMu_FS_noOS;   //!
   TBranch        *b_EF_mu6_DsPhiPi;   //!
   TBranch        *b_EF_mu6_Jpsie5e3;   //!
   //TBranch        *b_EF_mu6_Jpsie5e3_FS;   //!
   //TBranch        *b_EF_mu6_Jpsie5e3_SiTrk;   //!
   //TBranch        *b_EF_mu6_Jpsie5e3_SiTrk_FS;   //!
   TBranch        *b_EF_mu6_MG;   //!
   TBranch        *b_EF_mu6_MSonly;   //!
   TBranch        *b_EF_mu6_MSonly_cosmic;   //!
   TBranch        *b_EF_mu6_MSonly_firstempty;   //!
   TBranch        *b_EF_mu6_MSonly_unpaired;   //!
   TBranch        *b_EF_mu6_SiTrk;   //!
   TBranch        *b_EF_mu6_Trk_Jpsi_loose;   //!
   TBranch        *b_EF_mu6_Trk_Jpsi_loose_FS;   //!
   TBranch        *b_EF_mu6_Trk_Upsi_loose_FS;   //!
   TBranch        *b_EF_mu6_cosmic;   //!
   TBranch        *b_EF_mu6_firstempty;   //!
   TBranch        *b_EF_mu6_muCombTag;   //!
   TBranch        *b_EF_mu6_muCombTag_SiTrk;   //!
   TBranch        *b_EF_mu6_passHLT;   //!
   TBranch        *b_EF_mu6_unpaired;   //!
   TBranch        *b_L1_2EM2;   //!
   TBranch        *b_L1_2EM3;   //!
   TBranch        *b_L1_2EM4;   //!
   TBranch        *b_L1_2EM5;   //!
   TBranch        *b_L1_2MU0;   //!
   TBranch        *b_L1_2MU0_MU6;   //!
   TBranch        *b_L1_2MU10;   //!
   TBranch        *b_L1_2MU6;   //!
   TBranch        *b_L1_EM10;   //!
   TBranch        *b_L1_EM10I;   //!
   TBranch        *b_L1_EM14;   //!
   TBranch        *b_L1_EM2;   //!
   //TBranch        *b_L1_EM2_UNPAIRED;   //!
   TBranch        *b_L1_EM3;   //!
   TBranch        *b_L1_EM3_EMPTY;   //!
   TBranch        *b_L1_EM3_FIRSTEMPTY;   //!
   TBranch        *b_L1_EM3_MV;   //!
   TBranch        *b_L1_EM3_UNPAIRED;   //!
   TBranch        *b_L1_EM4;   //!
   TBranch        *b_L1_EM5;   //!
   TBranch        *b_L1_EM5I;   //!
   TBranch        *b_L1_MU0;   //!
   TBranch        *b_L1_MU0_COMM;   //!
   TBranch        *b_L1_MU0_COMM_EMPTY;   //!
   TBranch        *b_L1_MU0_COMM_FIRSTEMPTY;   //!
   TBranch        *b_L1_MU0_EM3;   //!
   TBranch        *b_L1_MU0_EMPTY;   //!
   TBranch        *b_L1_MU0_FIRSTEMPTY;   //!
   TBranch        *b_L1_MU0_J10;   //!
   TBranch        *b_L1_MU0_J15;   //!
   TBranch        *b_L1_MU0_J5;   //!
   TBranch        *b_L1_MU0_MV;   //!
   //TBranch        *b_L1_MU0_UNPAIRED;   //!
   TBranch        *b_L1_MU10;   //!
   TBranch        *b_L1_MU10_EMPTY;   //!
   TBranch        *b_L1_MU15;   //!
   TBranch        *b_L1_MU20;   //!
   TBranch        *b_L1_MU6;   //!
   TBranch        *b_L1_MU6_EM3;   //!
   TBranch        *b_L1_MU6_EMPTY;   //!
   TBranch        *b_L1_MU6_FIRSTEMPTY;   //!
   TBranch        *b_L1_MU6_J5;   //!
   TBranch        *b_L1_MU6_UNPAIRED;   //!
   TBranch        *b_L2_2mu10;   //!
   TBranch        *b_L2_2mu4;   //!
   TBranch        *b_L2_2mu4_DiMu;   //!
   TBranch        *b_L2_2mu4_DiMu_SiTrk;   //!
   TBranch        *b_L2_2mu4_DiMu_noOS;   //!
   TBranch        *b_L2_2mu4_DiMu_noOS_passL2;   //!
   TBranch        *b_L2_2mu4_DiMu_noVtx_noOS;   //!
   TBranch        *b_L2_2mu4_DiMu_noVtx_noOS_passL2;   //!
   TBranch        *b_L2_2mu4_MSonly;   //!
   TBranch        *b_L2_2mu6;   //!
   TBranch        *b_L2_2mu6_DiMu;   //!
   TBranch        *b_L2_2mu6_DiMu_noVtx_noOS;   //!
   TBranch        *b_L2_L1ItemStreamer_L1_MU0;   //!
   TBranch        *b_L2_L1ItemStreamer_L1_MU0_COMM;   //!
   TBranch        *b_L2_L1ItemStreamer_L1_MU0_COMM_EMPTY;   //!
   TBranch        *b_L2_L1ItemStreamer_L1_MU0_COMM_FIRSTEMPTY;   //!
   TBranch        *b_L2_L1ItemStreamer_L1_MU0_EM3;   //!
   TBranch        *b_L2_L1ItemStreamer_L1_MU0_EMPTY;   //!
   TBranch        *b_L2_L1ItemStreamer_L1_MU0_FIRSTEMPTY;   //!
   TBranch        *b_L2_L1ItemStreamer_L1_MU0_J10;   //!
   TBranch        *b_L2_L1ItemStreamer_L1_MU0_J15;   //!
   TBranch        *b_L2_L1ItemStreamer_L1_MU0_J5;   //!
   TBranch        *b_L2_L1ItemStreamer_L1_MU0_MV;   //!
   //TBranch        *b_L2_L1ItemStreamer_L1_MU0_UNPAIRED;   //!
   TBranch        *b_L2_L1ItemStreamer_L1_MU10;   //!
   TBranch        *b_L2_L1ItemStreamer_L1_MU10_EMPTY;   //!
   TBranch        *b_L2_L1ItemStreamer_L1_MU15;   //!
   TBranch        *b_L2_L1ItemStreamer_L1_MU20;   //!
   TBranch        *b_L2_L1ItemStreamer_L1_MU6;   //!
   TBranch        *b_L2_L1ItemStreamer_L1_MU6_EM3;   //!
   TBranch        *b_L2_L1ItemStreamer_L1_MU6_EMPTY;   //!
   TBranch        *b_L2_L1ItemStreamer_L1_MU6_FIRSTEMPTY;   //!
   TBranch        *b_L2_L1ItemStreamer_L1_MU6_J5;   //!
   TBranch        *b_L2_L1ItemStreamer_L1_MU6_UNPAIRED;   //!
   //TBranch        *b_L2_mu0_missingRoi;   //!
   //TBranch        *b_L2_mu0_rpcOnly;   //!
   TBranch        *b_L2_mu10;   //!
   TBranch        *b_L2_mu10_MG;   //!
   TBranch        *b_L2_mu10_MSonly;   //!
   TBranch        *b_L2_mu10_MSonly_cosmic;   //!
   TBranch        *b_L2_mu10_NoIDTrkCut;   //!
   TBranch        *b_L2_mu10_SiTrk;   //!
   TBranch        *b_L2_mu10_cosmic;   //!
   TBranch        *b_L2_mu10_muCombTag;   //!
   TBranch        *b_L2_mu10_muCombTag_SiTrk;   //!
   TBranch        *b_L2_mu10_passHLT;   //!
   TBranch        *b_L2_mu10i_loose;   //!
   TBranch        *b_L2_mu13 ;   //!
   TBranch        *b_L2_mu15;   //!
   TBranch        *b_L2_mu20;   //!
   TBranch        *b_L2_mu20_MSonly;   //!
   TBranch        *b_L2_mu20_passHLT;   //!
   TBranch        *b_L2_mu4;   //!
   TBranch        *b_L2_mu4_DiMu;   //!
   TBranch        *b_L2_mu4_DiMu_FS;   //!
   TBranch        *b_L2_mu4_DiMu_FS_noOS;   //!
   //TBranch        *b_L2_mu4_Jpsie5e3;   //!
   //TBranch        *b_L2_mu4_Jpsie5e3_FS;   //!
   //TBranch        *b_L2_mu4_Jpsie5e3_SiTrk;   //!
   //TBranch        *b_L2_mu4_Jpsie5e3_SiTrk_FS;   //!
   TBranch        *b_L2_mu4_L2MSonly_EFFS_passL2;   //!
   TBranch        *b_L2_mu4_MG;   //!
   TBranch        *b_L2_mu4_MSonly;   //!
   TBranch        *b_L2_mu4_MSonly_EFFS_passL2;   //!
   TBranch        *b_L2_mu4_MSonly_MB2_noL2_EFFS;   //!
   TBranch        *b_L2_mu4_MSonly_Trk_Jpsi_loose;   //!
   TBranch        *b_L2_mu4_MSonly_Trk_Upsi_loose_FS;   //!
   TBranch        *b_L2_mu4_MSonly_cosmic;   //!
   TBranch        *b_L2_mu4_MSonly_firstempty;   //!
   TBranch        *b_L2_mu4_MV;   //!
   TBranch        *b_L2_mu4_NoIDTrkCut;   //!
   TBranch        *b_L2_mu4_SiTrk;   //!
   TBranch        *b_L2_mu4_Trk_Jpsi_loose;   //!
   TBranch        *b_L2_mu4_Trk_Upsi_loose_FS;   //!
   TBranch        *b_L2_mu4_comm;   //!
   TBranch        *b_L2_mu4_comm_MSonly;   //!
   TBranch        *b_L2_mu4_comm_MSonly_cosmic;   //!
   TBranch        *b_L2_mu4_comm_MSonly_firstempty;   //!
   TBranch        *b_L2_mu4_comm_cosmic;   //!
   TBranch        *b_L2_mu4_comm_firstempty;   //!
   TBranch        *b_L2_mu4_cosmic;   //!
   TBranch        *b_L2_mu4_firstempty;   //!
   TBranch        *b_L2_mu4_j10_matched;   //!
   TBranch        *b_L2_mu4_j20_matched;   //!
   TBranch        *b_L2_mu4_j5_matched;   //!
   TBranch        *b_L2_mu4_mu6;   //!
   TBranch        *b_L2_mu4_muCombTag;   //!
   TBranch        *b_L2_mu4_muCombTag_SiTrk;   //!
   TBranch        *b_L2_mu4_passHLT;   //!
   TBranch        *b_L2_mu4_tile;   //!
   TBranch        *b_L2_mu4_tile_SiTrk;   //!
   TBranch        *b_L2_mu4_trod;   //!
   TBranch        *b_L2_mu4_trod_SiTrk;   //!
   //TBranch        *b_L2_mu4_unpaired;   //!
   TBranch        *b_L2_mu4mu6_DiMu;   //!
   TBranch        *b_L2_mu6;   //!
   TBranch        *b_L2_mu6_DiMu;   //!
   TBranch        *b_L2_mu6_DiMu_FS;   //!
   TBranch        *b_L2_mu6_DiMu_FS_noOS;   //!
   TBranch        *b_L2_mu6_DsPhiPi;   //!
   TBranch        *b_L2_mu6_Jpsie5e3;   //!
   //TBranch        *b_L2_mu6_Jpsie5e3_FS;   //!
   //TBranch        *b_L2_mu6_Jpsie5e3_SiTrk;   //!
   //TBranch        *b_L2_mu6_Jpsie5e3_SiTrk_FS;   //!
   TBranch        *b_L2_mu6_MG;   //!
   TBranch        *b_L2_mu6_MSonly;   //!
   TBranch        *b_L2_mu6_MSonly_cosmic;   //!
   TBranch        *b_L2_mu6_MSonly_firstempty;   //!
   TBranch        *b_L2_mu6_MSonly_unpaired;   //!
   TBranch        *b_L2_mu6_SiTrk;   //!
   TBranch        *b_L2_mu6_Trk_Jpsi_loose;   //!
   TBranch        *b_L2_mu6_Trk_Jpsi_loose_FS;   //!
   TBranch        *b_L2_mu6_Trk_Upsi_loose_FS;   //!
   TBranch        *b_L2_mu6_cosmic;   //!
   TBranch        *b_L2_mu6_firstempty;   //!
   TBranch        *b_L2_mu6_muCombTag;   //!
   TBranch        *b_L2_mu6_muCombTag_SiTrk;   //!
   TBranch        *b_L2_mu6_passHLT;   //!
   TBranch        *b_L2_mu6_unpaired;   //!
   TBranch        *b_mu_staco_n;   //!
   TBranch        *b_mu_staco_E;   //!
   TBranch        *b_mu_staco_px;   //!
   TBranch        *b_mu_staco_py;   //!
   TBranch        *b_mu_staco_pz;   //!
   TBranch        *b_mu_staco_m;   //!
   TBranch        *b_mu_staco_charge;   //!
   TBranch        *b_mu_staco_pt;   //!
   TBranch        *b_mu_staco_eta;   //!
   TBranch        *b_mu_staco_phi;   //!
   TBranch        *b_mu_staco_allauthor;   //!
   TBranch        *b_mu_staco_author;   //!
   TBranch        *b_mu_staco_matchchi2;   //!
   TBranch        *b_mu_staco_matchndof;   //!
   TBranch        *b_mu_staco_etcone20;   //!
   TBranch        *b_mu_staco_etcone30;   //!
   TBranch        *b_mu_staco_etcone40;   //!
   TBranch        *b_mu_staco_nucone20;   //!
   TBranch        *b_mu_staco_nucone30;   //!
   TBranch        *b_mu_staco_nucone40;   //!
   TBranch        *b_mu_staco_ptcone20;   //!
   TBranch        *b_mu_staco_ptcone30;   //!
   TBranch        *b_mu_staco_ptcone40;   //!
   TBranch        *b_mu_staco_energyLossPar;   //!
   TBranch        *b_mu_staco_energyLossErr;   //!
   TBranch        *b_mu_staco_bestMatch;   //!
   TBranch        *b_mu_staco_isStandAloneMuon;   //!
   TBranch        *b_mu_staco_isCombinedMuon;   //!
   TBranch        *b_mu_staco_isLowPtReconstructedMuon;   //!
   TBranch        *b_mu_staco_d0_exPV;   //!
   TBranch        *b_mu_staco_z0_exPV;   //!
   TBranch        *b_mu_staco_phi_exPV;   //!
   TBranch        *b_mu_staco_theta_exPV;   //!
   TBranch        *b_mu_staco_qoverp_exPV;   //!
   TBranch        *b_mu_staco_cov_d0_exPV;   //!
   TBranch        *b_mu_staco_cov_z0_exPV;   //!
   TBranch        *b_mu_staco_cov_phi_exPV;   //!
   TBranch        *b_mu_staco_cov_theta_exPV;   //!
   TBranch        *b_mu_staco_cov_qoverp_exPV;   //!
   TBranch        *b_mu_staco_cov_d0_z0_exPV;   //!
   TBranch        *b_mu_staco_cov_d0_phi_exPV;   //!
   TBranch        *b_mu_staco_cov_d0_theta_exPV;   //!
   TBranch        *b_mu_staco_cov_d0_qoverp_exPV;   //!
   TBranch        *b_mu_staco_cov_z0_phi_exPV;   //!
   TBranch        *b_mu_staco_cov_z0_theta_exPV;   //!
   TBranch        *b_mu_staco_cov_z0_qoverp_exPV;   //!
   TBranch        *b_mu_staco_cov_phi_theta_exPV;   //!
   TBranch        *b_mu_staco_cov_phi_qoverp_exPV;   //!
   TBranch        *b_mu_staco_cov_theta_qoverp_exPV;   //!
   TBranch        *b_mu_staco_ms_d0;   //!
   TBranch        *b_mu_staco_ms_z0;   //!
   TBranch        *b_mu_staco_ms_phi;   //!
   TBranch        *b_mu_staco_ms_theta;   //!
   TBranch        *b_mu_staco_ms_qoverp;   //!
   TBranch        *b_mu_staco_id_d0;   //!
   TBranch        *b_mu_staco_id_z0;   //!
   TBranch        *b_mu_staco_id_phi;   //!
   TBranch        *b_mu_staco_id_theta;   //!
   TBranch        *b_mu_staco_id_qoverp;   //!
   TBranch        *b_mu_staco_me_d0;   //!
   TBranch        *b_mu_staco_me_z0;   //!
   TBranch        *b_mu_staco_me_phi;   //!
   TBranch        *b_mu_staco_me_theta;   //!
   TBranch        *b_mu_staco_me_qoverp;   //!
   TBranch        *b_mu_staco_ie_d0;   //!
   TBranch        *b_mu_staco_ie_z0;   //!
   TBranch        *b_mu_staco_ie_phi;   //!
   TBranch        *b_mu_staco_ie_theta;   //!
   TBranch        *b_mu_staco_ie_qoverp;   //!
   TBranch        *b_mu_staco_nBLHits;   //!
   TBranch        *b_mu_staco_nPixHits;   //!
   TBranch        *b_mu_staco_nSCTHits;   //!
   TBranch        *b_mu_staco_nTRTHits;   //!
   TBranch        *b_mu_staco_nTRTHighTHits;   //!
   TBranch        *b_mu_staco_nBLSharedHits;   //!
   TBranch        *b_mu_staco_nPixSharedHits;   //!
   TBranch        *b_mu_staco_nPixHoles;   //!
   TBranch        *b_mu_staco_nSCTSharedHits;   //!
   TBranch        *b_mu_staco_nSCTHoles;   //!
   TBranch        *b_mu_staco_nTRTOutliers;   //!
   TBranch        *b_mu_staco_nTRTHighTOutliers;   //!
   TBranch        *b_mu_staco_nMDTHits;   //!
   TBranch        *b_mu_staco_nMDTHoles;   //!
   TBranch        *b_mu_staco_nCSCEtaHits;   //!
   TBranch        *b_mu_staco_nCSCEtaHoles;   //!
   TBranch        *b_mu_staco_nCSCPhiHits;   //!
   TBranch        *b_mu_staco_nCSCPhiHoles;   //!
   TBranch        *b_mu_staco_nRPCEtaHits;   //!
   TBranch        *b_mu_staco_nRPCEtaHoles;   //!
   TBranch        *b_mu_staco_nRPCPhiHits;   //!
   TBranch        *b_mu_staco_nRPCPhiHoles;   //!
   TBranch        *b_mu_staco_nTGCEtaHits;   //!
   TBranch        *b_mu_staco_nTGCEtaHoles;   //!
   TBranch        *b_mu_staco_nTGCPhiHits;   //!
   TBranch        *b_mu_staco_nTGCPhiHoles;   //!
   TBranch        *b_mu_staco_nGangedPixels;   //!
   TBranch        *b_mu_staco_nOutliersOnTrack;   //!
   TBranch        *b_mu_staco_nMDTBIHits;   //!
   TBranch        *b_mu_staco_nMDTBMHits;   //!
   TBranch        *b_mu_staco_nMDTBOHits;   //!
   TBranch        *b_mu_staco_nMDTBEEHits;   //!
   TBranch        *b_mu_staco_nMDTBIS78Hits;   //!
   TBranch        *b_mu_staco_nMDTEIHits;   //!
   TBranch        *b_mu_staco_nMDTEMHits;   //!
   TBranch        *b_mu_staco_nMDTEOHits;   //!
   TBranch        *b_mu_staco_nMDTEEHits;   //!
   TBranch        *b_mu_staco_nRPCLayer1EtaHits;   //!
   TBranch        *b_mu_staco_nRPCLayer2EtaHits;   //!
   TBranch        *b_mu_staco_nRPCLayer3EtaHits;   //!
   TBranch        *b_mu_staco_nRPCLayer1PhiHits;   //!
   TBranch        *b_mu_staco_nRPCLayer2PhiHits;   //!
   TBranch        *b_mu_staco_nRPCLayer3PhiHits;   //!
   TBranch        *b_mu_staco_nTGCLayer1EtaHits;   //!
   TBranch        *b_mu_staco_nTGCLayer2EtaHits;   //!
   TBranch        *b_mu_staco_nTGCLayer3EtaHits;   //!
   TBranch        *b_mu_staco_nTGCLayer4EtaHits;   //!
   TBranch        *b_mu_staco_nTGCLayer1PhiHits;   //!
   TBranch        *b_mu_staco_nTGCLayer2PhiHits;   //!
   TBranch        *b_mu_staco_nTGCLayer3PhiHits;   //!
   TBranch        *b_mu_staco_nTGCLayer4PhiHits;   //!
   TBranch        *b_mu_staco_barrelSectors;   //!
   TBranch        *b_mu_staco_endcapSectors;   //!
   TBranch        *b_mu_staco_trackd0;   //!
   TBranch        *b_mu_staco_trackz0;   //!
   TBranch        *b_mu_staco_trackphi;   //!
   TBranch        *b_mu_staco_tracktheta;   //!
   TBranch        *b_mu_staco_trackqoverp;   //!
   TBranch        *b_mu_staco_trackcov_d0;   //!
   TBranch        *b_mu_staco_trackcov_z0;   //!
   TBranch        *b_mu_staco_trackcov_phi;   //!
   TBranch        *b_mu_staco_trackcov_theta;   //!
   TBranch        *b_mu_staco_trackcov_qoverp;   //!
   TBranch        *b_mu_staco_trackcov_d0_z0;   //!
   TBranch        *b_mu_staco_trackcov_d0_phi;   //!
   TBranch        *b_mu_staco_trackcov_d0_theta;   //!
   TBranch        *b_mu_staco_trackcov_d0_qoverp;   //!
   TBranch        *b_mu_staco_trackcov_z0_phi;   //!
   TBranch        *b_mu_staco_trackcov_z0_theta;   //!
   TBranch        *b_mu_staco_trackcov_z0_qoverp;   //!
   TBranch        *b_mu_staco_trackcov_phi_theta;   //!
   TBranch        *b_mu_staco_trackcov_phi_qoverp;   //!
   TBranch        *b_mu_staco_trackcov_theta_qoverp;   //!
   TBranch        *b_mu_staco_trackfitchi2;   //!
   TBranch        *b_mu_staco_trackfitndof;   //!
   TBranch        *b_mu_staco_hastrack;   //!
   TBranch        *b_mu_staco_EF_dr;   //!
   TBranch        *b_mu_staco_EF_cb_eta;   //!
   TBranch        *b_mu_staco_EF_cb_phi;   //!
   TBranch        *b_mu_staco_EF_cb_pt;   //!
   TBranch        *b_mu_staco_EF_ms_eta;   //!
   TBranch        *b_mu_staco_EF_ms_phi;   //!
   TBranch        *b_mu_staco_EF_ms_pt;   //!
   TBranch        *b_mu_staco_EF_me_eta;   //!
   TBranch        *b_mu_staco_EF_me_phi;   //!
   TBranch        *b_mu_staco_EF_me_pt;   //!
   TBranch        *b_mu_staco_EF_matched;   //!
   TBranch        *b_mu_staco_L2CB_dr;   //!
   TBranch        *b_mu_staco_L2CB_pt;   //!
   TBranch        *b_mu_staco_L2CB_eta;   //!
   TBranch        *b_mu_staco_L2CB_phi;   //!
   TBranch        *b_mu_staco_L2CB_id_pt;   //!
   TBranch        *b_mu_staco_L2CB_ms_pt;   //!
   TBranch        *b_mu_staco_L2CB_nPixHits;   //!
   TBranch        *b_mu_staco_L2CB_nSCTHits;   //!
   TBranch        *b_mu_staco_L2CB_nTRTHits;   //!
   TBranch        *b_mu_staco_L2CB_nTRTHighTHits;   //!
   TBranch        *b_mu_staco_L2CB_matched;   //!
   TBranch        *b_mu_staco_L1_dr;   //!
   TBranch        *b_mu_staco_L1_pt;   //!
   TBranch        *b_mu_staco_L1_eta;   //!
   TBranch        *b_mu_staco_L1_phi;   //!
   TBranch        *b_mu_staco_L1_thrNumber;   //!
   TBranch        *b_mu_staco_L1_RoINumber;   //!
   TBranch        *b_mu_staco_L1_sectorAddress;   //!
   TBranch        *b_mu_staco_L1_firstCandidate;   //!
   TBranch        *b_mu_staco_L1_moreCandInRoI;   //!
   TBranch        *b_mu_staco_L1_moreCandInSector;   //!
   TBranch        *b_mu_staco_L1_source;   //!
   TBranch        *b_mu_staco_L1_hemisphere;   //!
   TBranch        *b_mu_staco_L1_matched;   //!
   TBranch        *b_mu_muid_n;   //!
   TBranch        *b_mu_muid_E;   //!
   TBranch        *b_mu_muid_px;   //!
   TBranch        *b_mu_muid_py;   //!
   TBranch        *b_mu_muid_pz;   //!
   TBranch        *b_mu_muid_m;   //!
   TBranch        *b_mu_muid_charge;   //!
   TBranch        *b_mu_muid_pt;   //!
   TBranch        *b_mu_muid_eta;   //!
   TBranch        *b_mu_muid_phi;   //!
   TBranch        *b_mu_muid_allauthor;   //!
   TBranch        *b_mu_muid_author;   //!
   TBranch        *b_mu_muid_matchchi2;   //!
   TBranch        *b_mu_muid_matchndof;   //!
   TBranch        *b_mu_muid_etcone20;   //!
   TBranch        *b_mu_muid_etcone30;   //!
   TBranch        *b_mu_muid_etcone40;   //!
   TBranch        *b_mu_muid_nucone20;   //!
   TBranch        *b_mu_muid_nucone30;   //!
   TBranch        *b_mu_muid_nucone40;   //!
   TBranch        *b_mu_muid_ptcone20;   //!
   TBranch        *b_mu_muid_ptcone30;   //!
   TBranch        *b_mu_muid_ptcone40;   //!
   TBranch        *b_mu_muid_energyLossPar;   //!
   TBranch        *b_mu_muid_energyLossErr;   //!
   TBranch        *b_mu_muid_bestMatch;   //!
   TBranch        *b_mu_muid_isStandAloneMuon;   //!
   TBranch        *b_mu_muid_isCombinedMuon;   //!
   TBranch        *b_mu_muid_isLowPtReconstructedMuon;   //!
   TBranch        *b_mu_muid_d0_exPV;   //!
   TBranch        *b_mu_muid_z0_exPV;   //!
   TBranch        *b_mu_muid_phi_exPV;   //!
   TBranch        *b_mu_muid_theta_exPV;   //!
   TBranch        *b_mu_muid_qoverp_exPV;   //!
   TBranch        *b_mu_muid_cov_d0_exPV;   //!
   TBranch        *b_mu_muid_cov_z0_exPV;   //!
   TBranch        *b_mu_muid_cov_phi_exPV;   //!
   TBranch        *b_mu_muid_cov_theta_exPV;   //!
   TBranch        *b_mu_muid_cov_qoverp_exPV;   //!
   TBranch        *b_mu_muid_cov_d0_z0_exPV;   //!
   TBranch        *b_mu_muid_cov_d0_phi_exPV;   //!
   TBranch        *b_mu_muid_cov_d0_theta_exPV;   //!
   TBranch        *b_mu_muid_cov_d0_qoverp_exPV;   //!
   TBranch        *b_mu_muid_cov_z0_phi_exPV;   //!
   TBranch        *b_mu_muid_cov_z0_theta_exPV;   //!
   TBranch        *b_mu_muid_cov_z0_qoverp_exPV;   //!
   TBranch        *b_mu_muid_cov_phi_theta_exPV;   //!
   TBranch        *b_mu_muid_cov_phi_qoverp_exPV;   //!
   TBranch        *b_mu_muid_cov_theta_qoverp_exPV;   //!
   TBranch        *b_mu_muid_ms_d0;   //!
   TBranch        *b_mu_muid_ms_z0;   //!
   TBranch        *b_mu_muid_ms_phi;   //!
   TBranch        *b_mu_muid_ms_theta;   //!
   TBranch        *b_mu_muid_ms_qoverp;   //!
   TBranch        *b_mu_muid_id_d0;   //!
   TBranch        *b_mu_muid_id_z0;   //!
   TBranch        *b_mu_muid_id_phi;   //!
   TBranch        *b_mu_muid_id_theta;   //!
   TBranch        *b_mu_muid_id_qoverp;   //!
   TBranch        *b_mu_muid_me_d0;   //!
   TBranch        *b_mu_muid_me_z0;   //!
   TBranch        *b_mu_muid_me_phi;   //!
   TBranch        *b_mu_muid_me_theta;   //!
   TBranch        *b_mu_muid_me_qoverp;   //!
   TBranch        *b_mu_muid_ie_d0;   //!
   TBranch        *b_mu_muid_ie_z0;   //!
   TBranch        *b_mu_muid_ie_phi;   //!
   TBranch        *b_mu_muid_ie_theta;   //!
   TBranch        *b_mu_muid_ie_qoverp;   //!
   TBranch        *b_mu_muid_nBLHits;   //!
   TBranch        *b_mu_muid_nPixHits;   //!
   TBranch        *b_mu_muid_nSCTHits;   //!
   TBranch        *b_mu_muid_nTRTHits;   //!
   TBranch        *b_mu_muid_nTRTHighTHits;   //!
   TBranch        *b_mu_muid_nBLSharedHits;   //!
   TBranch        *b_mu_muid_nPixSharedHits;   //!
   TBranch        *b_mu_muid_nPixHoles;   //!
   TBranch        *b_mu_muid_nSCTSharedHits;   //!
   TBranch        *b_mu_muid_nSCTHoles;   //!
   TBranch        *b_mu_muid_nTRTOutliers;   //!
   TBranch        *b_mu_muid_nTRTHighTOutliers;   //!
   TBranch        *b_mu_muid_nMDTHits;   //!
   TBranch        *b_mu_muid_nMDTHoles;   //!
   TBranch        *b_mu_muid_nCSCEtaHits;   //!
   TBranch        *b_mu_muid_nCSCEtaHoles;   //!
   TBranch        *b_mu_muid_nCSCPhiHits;   //!
   TBranch        *b_mu_muid_nCSCPhiHoles;   //!
   TBranch        *b_mu_muid_nRPCEtaHits;   //!
   TBranch        *b_mu_muid_nRPCEtaHoles;   //!
   TBranch        *b_mu_muid_nRPCPhiHits;   //!
   TBranch        *b_mu_muid_nRPCPhiHoles;   //!
   TBranch        *b_mu_muid_nTGCEtaHits;   //!
   TBranch        *b_mu_muid_nTGCEtaHoles;   //!
   TBranch        *b_mu_muid_nTGCPhiHits;   //!
   TBranch        *b_mu_muid_nTGCPhiHoles;   //!
   TBranch        *b_mu_muid_nGangedPixels;   //!
   TBranch        *b_mu_muid_nOutliersOnTrack;   //!
   TBranch        *b_mu_muid_nMDTBIHits;   //!
   TBranch        *b_mu_muid_nMDTBMHits;   //!
   TBranch        *b_mu_muid_nMDTBOHits;   //!
   TBranch        *b_mu_muid_nMDTBEEHits;   //!
   TBranch        *b_mu_muid_nMDTBIS78Hits;   //!
   TBranch        *b_mu_muid_nMDTEIHits;   //!
   TBranch        *b_mu_muid_nMDTEMHits;   //!
   TBranch        *b_mu_muid_nMDTEOHits;   //!
   TBranch        *b_mu_muid_nMDTEEHits;   //!
   TBranch        *b_mu_muid_nRPCLayer1EtaHits;   //!
   TBranch        *b_mu_muid_nRPCLayer2EtaHits;   //!
   TBranch        *b_mu_muid_nRPCLayer3EtaHits;   //!
   TBranch        *b_mu_muid_nRPCLayer1PhiHits;   //!
   TBranch        *b_mu_muid_nRPCLayer2PhiHits;   //!
   TBranch        *b_mu_muid_nRPCLayer3PhiHits;   //!
   TBranch        *b_mu_muid_nTGCLayer1EtaHits;   //!
   TBranch        *b_mu_muid_nTGCLayer2EtaHits;   //!
   TBranch        *b_mu_muid_nTGCLayer3EtaHits;   //!
   TBranch        *b_mu_muid_nTGCLayer4EtaHits;   //!
   TBranch        *b_mu_muid_nTGCLayer1PhiHits;   //!
   TBranch        *b_mu_muid_nTGCLayer2PhiHits;   //!
   TBranch        *b_mu_muid_nTGCLayer3PhiHits;   //!
   TBranch        *b_mu_muid_nTGCLayer4PhiHits;   //!
   TBranch        *b_mu_muid_barrelSectors;   //!
   TBranch        *b_mu_muid_endcapSectors;   //!
   TBranch        *b_mu_muid_trackd0;   //!
   TBranch        *b_mu_muid_trackz0;   //!
   TBranch        *b_mu_muid_trackphi;   //!
   TBranch        *b_mu_muid_tracktheta;   //!
   TBranch        *b_mu_muid_trackqoverp;   //!
   TBranch        *b_mu_muid_trackcov_d0;   //!
   TBranch        *b_mu_muid_trackcov_z0;   //!
   TBranch        *b_mu_muid_trackcov_phi;   //!
   TBranch        *b_mu_muid_trackcov_theta;   //!
   TBranch        *b_mu_muid_trackcov_qoverp;   //!
   TBranch        *b_mu_muid_trackcov_d0_z0;   //!
   TBranch        *b_mu_muid_trackcov_d0_phi;   //!
   TBranch        *b_mu_muid_trackcov_d0_theta;   //!
   TBranch        *b_mu_muid_trackcov_d0_qoverp;   //!
   TBranch        *b_mu_muid_trackcov_z0_phi;   //!
   TBranch        *b_mu_muid_trackcov_z0_theta;   //!
   TBranch        *b_mu_muid_trackcov_z0_qoverp;   //!
   TBranch        *b_mu_muid_trackcov_phi_theta;   //!
   TBranch        *b_mu_muid_trackcov_phi_qoverp;   //!
   TBranch        *b_mu_muid_trackcov_theta_qoverp;   //!
   TBranch        *b_mu_muid_trackfitchi2;   //!
   TBranch        *b_mu_muid_trackfitndof;   //!
   TBranch        *b_mu_muid_hastrack;   //!
   TBranch        *b_mu_muid_EF_dr;   //!
   TBranch        *b_mu_muid_EF_cb_eta;   //!
   TBranch        *b_mu_muid_EF_cb_phi;   //!
   TBranch        *b_mu_muid_EF_cb_pt;   //!
   TBranch        *b_mu_muid_EF_ms_eta;   //!
   TBranch        *b_mu_muid_EF_ms_phi;   //!
   TBranch        *b_mu_muid_EF_ms_pt;   //!
   TBranch        *b_mu_muid_EF_me_eta;   //!
   TBranch        *b_mu_muid_EF_me_phi;   //!
   TBranch        *b_mu_muid_EF_me_pt;   //!
   TBranch        *b_mu_muid_EF_matched;   //!
   TBranch        *b_mu_muid_L2CB_dr;   //!
   TBranch        *b_mu_muid_L2CB_pt;   //!
   TBranch        *b_mu_muid_L2CB_eta;   //!
   TBranch        *b_mu_muid_L2CB_phi;   //!
   TBranch        *b_mu_muid_L2CB_id_pt;   //!
   TBranch        *b_mu_muid_L2CB_ms_pt;   //!
   TBranch        *b_mu_muid_L2CB_nPixHits;   //!
   TBranch        *b_mu_muid_L2CB_nSCTHits;   //!
   TBranch        *b_mu_muid_L2CB_nTRTHits;   //!
   TBranch        *b_mu_muid_L2CB_nTRTHighTHits;   //!
   TBranch        *b_mu_muid_L2CB_matched;   //!
   TBranch        *b_mu_muid_L1_dr;   //!
   TBranch        *b_mu_muid_L1_pt;   //!
   TBranch        *b_mu_muid_L1_eta;   //!
   TBranch        *b_mu_muid_L1_phi;   //!
   TBranch        *b_mu_muid_L1_thrNumber;   //!
   TBranch        *b_mu_muid_L1_RoINumber;   //!
   TBranch        *b_mu_muid_L1_sectorAddress;   //!
   TBranch        *b_mu_muid_L1_firstCandidate;   //!
   TBranch        *b_mu_muid_L1_moreCandInRoI;   //!
   TBranch        *b_mu_muid_L1_moreCandInSector;   //!
   TBranch        *b_mu_muid_L1_source;   //!
   TBranch        *b_mu_muid_L1_hemisphere;   //!
   TBranch        *b_mu_muid_L1_matched;   //!

   offlinePhysics(TTree *tree=0);
   virtual ~offlinePhysics();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef offlinePhysics_cxx
offlinePhysics::offlinePhysics(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {

#ifdef SINGLE_TREE
      // The following code should be used if you want this class to access
      // a single tree instead of a chain
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Memory Directory");
      if (!f) {
         f = new TFile("Memory Directory");
         f->cd("Rint:/");
      }
      tree = (TTree*)gDirectory->Get("offline");

#else // SINGLE_TREE

      // The following code should be used if you want this class to access a chain
      // of trees.
      TChain * chain = new TChain("offline","");
      chain->Add("offline_datasetdir/analysisTrees_100.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_104.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_105.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_106.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_107.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_109.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_10.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_110.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_112.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_114.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_116.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_117.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_118.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_119.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_11.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_125.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_126.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_127.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_129.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_12.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_134.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_138.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_141.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_142.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_145.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_146.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_147.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_153.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_154.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_155.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_156.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_159.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_15.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_19.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_1.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_21.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_23.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_25.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_27.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_28.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_29.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_31.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_32.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_33.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_34.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_36.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_38.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_39.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_3.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_41.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_44.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_45.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_46.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_47.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_50.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_51.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_56.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_57.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_5.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_60.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_63.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_66.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_67.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_68.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_69.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_70.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_71.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_76.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_78.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_79.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_7.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_80.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_81.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_82.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_84.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_86.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_87.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_88.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_89.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_90.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_91.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_92.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_94.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_95.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_98.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_9.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_151.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_149.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_157.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_131.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_53.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_26.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_20.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_49.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_42.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_37.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_62.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_55.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_135.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_148.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_61.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_35.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_2.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_58.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_111.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_52.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_150.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_120.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_137.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_128.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_48.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_108.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_133.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_43.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_101.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_130.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_14.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_16.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_40.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_113.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_123.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_54.root/offline");
      chain->Add("offline_datasetdir/analysisTrees.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_139.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_144.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_24.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_124.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_122.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_30.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_160.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_13.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_115.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_102.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_59.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_140.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_22.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_161.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_65.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_103.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_158.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_4.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_136.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_64.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_143.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_17.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_152.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_121.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_132.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_162.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_18.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_6.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_72.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_73.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_74.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_75.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_77.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_83.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_85.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_8.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_93.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_96.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_97.root/offline");
      chain->Add("offline_datasetdir/analysisTrees_99.root/offline");
      tree = chain;
#endif // SINGLE_TREE

   }
   Init(tree);
}

offlinePhysics::~offlinePhysics()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t offlinePhysics::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t offlinePhysics::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (!fChain->InheritsFrom(TChain::Class()))  return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void offlinePhysics::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   mu_staco_E = 0;
   mu_staco_px = 0;
   mu_staco_py = 0;
   mu_staco_pz = 0;
   mu_staco_m = 0;
   mu_staco_charge = 0;
   mu_staco_pt = 0;
   mu_staco_eta = 0;
   mu_staco_phi = 0;
   mu_staco_allauthor = 0;
   mu_staco_author = 0;
   mu_staco_matchchi2 = 0;
   mu_staco_matchndof = 0;
   mu_staco_etcone20 = 0;
   mu_staco_etcone30 = 0;
   mu_staco_etcone40 = 0;
   mu_staco_nucone20 = 0;
   mu_staco_nucone30 = 0;
   mu_staco_nucone40 = 0;
   mu_staco_ptcone20 = 0;
   mu_staco_ptcone30 = 0;
   mu_staco_ptcone40 = 0;
   mu_staco_energyLossPar = 0;
   mu_staco_energyLossErr = 0;
   mu_staco_bestMatch = 0;
   mu_staco_isStandAloneMuon = 0;
   mu_staco_isCombinedMuon = 0;
   mu_staco_isLowPtReconstructedMuon = 0;
   mu_staco_d0_exPV = 0;
   mu_staco_z0_exPV = 0;
   mu_staco_phi_exPV = 0;
   mu_staco_theta_exPV = 0;
   mu_staco_qoverp_exPV = 0;
   mu_staco_cov_d0_exPV = 0;
   mu_staco_cov_z0_exPV = 0;
   mu_staco_cov_phi_exPV = 0;
   mu_staco_cov_theta_exPV = 0;
   mu_staco_cov_qoverp_exPV = 0;
   mu_staco_cov_d0_z0_exPV = 0;
   mu_staco_cov_d0_phi_exPV = 0;
   mu_staco_cov_d0_theta_exPV = 0;
   mu_staco_cov_d0_qoverp_exPV = 0;
   mu_staco_cov_z0_phi_exPV = 0;
   mu_staco_cov_z0_theta_exPV = 0;
   mu_staco_cov_z0_qoverp_exPV = 0;
   mu_staco_cov_phi_theta_exPV = 0;
   mu_staco_cov_phi_qoverp_exPV = 0;
   mu_staco_cov_theta_qoverp_exPV = 0;
   mu_staco_ms_d0 = 0;
   mu_staco_ms_z0 = 0;
   mu_staco_ms_phi = 0;
   mu_staco_ms_theta = 0;
   mu_staco_ms_qoverp = 0;
   mu_staco_id_d0 = 0;
   mu_staco_id_z0 = 0;
   mu_staco_id_phi = 0;
   mu_staco_id_theta = 0;
   mu_staco_id_qoverp = 0;
   mu_staco_me_d0 = 0;
   mu_staco_me_z0 = 0;
   mu_staco_me_phi = 0;
   mu_staco_me_theta = 0;
   mu_staco_me_qoverp = 0;
   mu_staco_ie_d0 = 0;
   mu_staco_ie_z0 = 0;
   mu_staco_ie_phi = 0;
   mu_staco_ie_theta = 0;
   mu_staco_ie_qoverp = 0;
   mu_staco_nBLHits = 0;
   mu_staco_nPixHits = 0;
   mu_staco_nSCTHits = 0;
   mu_staco_nTRTHits = 0;
   mu_staco_nTRTHighTHits = 0;
   mu_staco_nBLSharedHits = 0;
   mu_staco_nPixSharedHits = 0;
   mu_staco_nPixHoles = 0;
   mu_staco_nSCTSharedHits = 0;
   mu_staco_nSCTHoles = 0;
   mu_staco_nTRTOutliers = 0;
   mu_staco_nTRTHighTOutliers = 0;
   mu_staco_nMDTHits = 0;
   mu_staco_nMDTHoles = 0;
   mu_staco_nCSCEtaHits = 0;
   mu_staco_nCSCEtaHoles = 0;
   mu_staco_nCSCPhiHits = 0;
   mu_staco_nCSCPhiHoles = 0;
   mu_staco_nRPCEtaHits = 0;
   mu_staco_nRPCEtaHoles = 0;
   mu_staco_nRPCPhiHits = 0;
   mu_staco_nRPCPhiHoles = 0;
   mu_staco_nTGCEtaHits = 0;
   mu_staco_nTGCEtaHoles = 0;
   mu_staco_nTGCPhiHits = 0;
   mu_staco_nTGCPhiHoles = 0;
   mu_staco_nGangedPixels = 0;
   mu_staco_nOutliersOnTrack = 0;
   mu_staco_nMDTBIHits = 0;
   mu_staco_nMDTBMHits = 0;
   mu_staco_nMDTBOHits = 0;
   mu_staco_nMDTBEEHits = 0;
   mu_staco_nMDTBIS78Hits = 0;
   mu_staco_nMDTEIHits = 0;
   mu_staco_nMDTEMHits = 0;
   mu_staco_nMDTEOHits = 0;
   mu_staco_nMDTEEHits = 0;
   mu_staco_nRPCLayer1EtaHits = 0;
   mu_staco_nRPCLayer2EtaHits = 0;
   mu_staco_nRPCLayer3EtaHits = 0;
   mu_staco_nRPCLayer1PhiHits = 0;
   mu_staco_nRPCLayer2PhiHits = 0;
   mu_staco_nRPCLayer3PhiHits = 0;
   mu_staco_nTGCLayer1EtaHits = 0;
   mu_staco_nTGCLayer2EtaHits = 0;
   mu_staco_nTGCLayer3EtaHits = 0;
   mu_staco_nTGCLayer4EtaHits = 0;
   mu_staco_nTGCLayer1PhiHits = 0;
   mu_staco_nTGCLayer2PhiHits = 0;
   mu_staco_nTGCLayer3PhiHits = 0;
   mu_staco_nTGCLayer4PhiHits = 0;
   mu_staco_barrelSectors = 0;
   mu_staco_endcapSectors = 0;
   mu_staco_trackd0 = 0;
   mu_staco_trackz0 = 0;
   mu_staco_trackphi = 0;
   mu_staco_tracktheta = 0;
   mu_staco_trackqoverp = 0;
   mu_staco_trackcov_d0 = 0;
   mu_staco_trackcov_z0 = 0;
   mu_staco_trackcov_phi = 0;
   mu_staco_trackcov_theta = 0;
   mu_staco_trackcov_qoverp = 0;
   mu_staco_trackcov_d0_z0 = 0;
   mu_staco_trackcov_d0_phi = 0;
   mu_staco_trackcov_d0_theta = 0;
   mu_staco_trackcov_d0_qoverp = 0;
   mu_staco_trackcov_z0_phi = 0;
   mu_staco_trackcov_z0_theta = 0;
   mu_staco_trackcov_z0_qoverp = 0;
   mu_staco_trackcov_phi_theta = 0;
   mu_staco_trackcov_phi_qoverp = 0;
   mu_staco_trackcov_theta_qoverp = 0;
   mu_staco_trackfitchi2 = 0;
   mu_staco_trackfitndof = 0;
   mu_staco_hastrack = 0;
   mu_staco_EF_dr = 0;
   mu_staco_EF_cb_eta = 0;
   mu_staco_EF_cb_phi = 0;
   mu_staco_EF_cb_pt = 0;
   mu_staco_EF_ms_eta = 0;
   mu_staco_EF_ms_phi = 0;
   mu_staco_EF_ms_pt = 0;
   mu_staco_EF_me_eta = 0;
   mu_staco_EF_me_phi = 0;
   mu_staco_EF_me_pt = 0;
   mu_staco_EF_matched = 0;
   mu_staco_L2CB_dr = 0;
   mu_staco_L2CB_pt = 0;
   mu_staco_L2CB_eta = 0;
   mu_staco_L2CB_phi = 0;
   mu_staco_L2CB_id_pt = 0;
   mu_staco_L2CB_ms_pt = 0;
   mu_staco_L2CB_nPixHits = 0;
   mu_staco_L2CB_nSCTHits = 0;
   mu_staco_L2CB_nTRTHits = 0;
   mu_staco_L2CB_nTRTHighTHits = 0;
   mu_staco_L2CB_matched = 0;
   mu_staco_L1_dr = 0;
   mu_staco_L1_pt = 0;
   mu_staco_L1_eta = 0;
   mu_staco_L1_phi = 0;
   mu_staco_L1_thrNumber = 0;
   mu_staco_L1_RoINumber = 0;
   mu_staco_L1_sectorAddress = 0;
   mu_staco_L1_firstCandidate = 0;
   mu_staco_L1_moreCandInRoI = 0;
   mu_staco_L1_moreCandInSector = 0;
   mu_staco_L1_source = 0;
   mu_staco_L1_hemisphere = 0;
   mu_staco_L1_matched = 0;
   mu_muid_E = 0;
   mu_muid_px = 0;
   mu_muid_py = 0;
   mu_muid_pz = 0;
   mu_muid_m = 0;
   mu_muid_charge = 0;
   mu_muid_pt = 0;
   mu_muid_eta = 0;
   mu_muid_phi = 0;
   mu_muid_allauthor = 0;
   mu_muid_author = 0;
   mu_muid_matchchi2 = 0;
   mu_muid_matchndof = 0;
   mu_muid_etcone20 = 0;
   mu_muid_etcone30 = 0;
   mu_muid_etcone40 = 0;
   mu_muid_nucone20 = 0;
   mu_muid_nucone30 = 0;
   mu_muid_nucone40 = 0;
   mu_muid_ptcone20 = 0;
   mu_muid_ptcone30 = 0;
   mu_muid_ptcone40 = 0;
   mu_muid_energyLossPar = 0;
   mu_muid_energyLossErr = 0;
   mu_muid_bestMatch = 0;
   mu_muid_isStandAloneMuon = 0;
   mu_muid_isCombinedMuon = 0;
   mu_muid_isLowPtReconstructedMuon = 0;
   mu_muid_d0_exPV = 0;
   mu_muid_z0_exPV = 0;
   mu_muid_phi_exPV = 0;
   mu_muid_theta_exPV = 0;
   mu_muid_qoverp_exPV = 0;
   mu_muid_cov_d0_exPV = 0;
   mu_muid_cov_z0_exPV = 0;
   mu_muid_cov_phi_exPV = 0;
   mu_muid_cov_theta_exPV = 0;
   mu_muid_cov_qoverp_exPV = 0;
   mu_muid_cov_d0_z0_exPV = 0;
   mu_muid_cov_d0_phi_exPV = 0;
   mu_muid_cov_d0_theta_exPV = 0;
   mu_muid_cov_d0_qoverp_exPV = 0;
   mu_muid_cov_z0_phi_exPV = 0;
   mu_muid_cov_z0_theta_exPV = 0;
   mu_muid_cov_z0_qoverp_exPV = 0;
   mu_muid_cov_phi_theta_exPV = 0;
   mu_muid_cov_phi_qoverp_exPV = 0;
   mu_muid_cov_theta_qoverp_exPV = 0;
   mu_muid_ms_d0 = 0;
   mu_muid_ms_z0 = 0;
   mu_muid_ms_phi = 0;
   mu_muid_ms_theta = 0;
   mu_muid_ms_qoverp = 0;
   mu_muid_id_d0 = 0;
   mu_muid_id_z0 = 0;
   mu_muid_id_phi = 0;
   mu_muid_id_theta = 0;
   mu_muid_id_qoverp = 0;
   mu_muid_me_d0 = 0;
   mu_muid_me_z0 = 0;
   mu_muid_me_phi = 0;
   mu_muid_me_theta = 0;
   mu_muid_me_qoverp = 0;
   mu_muid_ie_d0 = 0;
   mu_muid_ie_z0 = 0;
   mu_muid_ie_phi = 0;
   mu_muid_ie_theta = 0;
   mu_muid_ie_qoverp = 0;
   mu_muid_nBLHits = 0;
   mu_muid_nPixHits = 0;
   mu_muid_nSCTHits = 0;
   mu_muid_nTRTHits = 0;
   mu_muid_nTRTHighTHits = 0;
   mu_muid_nBLSharedHits = 0;
   mu_muid_nPixSharedHits = 0;
   mu_muid_nPixHoles = 0;
   mu_muid_nSCTSharedHits = 0;
   mu_muid_nSCTHoles = 0;
   mu_muid_nTRTOutliers = 0;
   mu_muid_nTRTHighTOutliers = 0;
   mu_muid_nMDTHits = 0;
   mu_muid_nMDTHoles = 0;
   mu_muid_nCSCEtaHits = 0;
   mu_muid_nCSCEtaHoles = 0;
   mu_muid_nCSCPhiHits = 0;
   mu_muid_nCSCPhiHoles = 0;
   mu_muid_nRPCEtaHits = 0;
   mu_muid_nRPCEtaHoles = 0;
   mu_muid_nRPCPhiHits = 0;
   mu_muid_nRPCPhiHoles = 0;
   mu_muid_nTGCEtaHits = 0;
   mu_muid_nTGCEtaHoles = 0;
   mu_muid_nTGCPhiHits = 0;
   mu_muid_nTGCPhiHoles = 0;
   mu_muid_nGangedPixels = 0;
   mu_muid_nOutliersOnTrack = 0;
   mu_muid_nMDTBIHits = 0;
   mu_muid_nMDTBMHits = 0;
   mu_muid_nMDTBOHits = 0;
   mu_muid_nMDTBEEHits = 0;
   mu_muid_nMDTBIS78Hits = 0;
   mu_muid_nMDTEIHits = 0;
   mu_muid_nMDTEMHits = 0;
   mu_muid_nMDTEOHits = 0;
   mu_muid_nMDTEEHits = 0;
   mu_muid_nRPCLayer1EtaHits = 0;
   mu_muid_nRPCLayer2EtaHits = 0;
   mu_muid_nRPCLayer3EtaHits = 0;
   mu_muid_nRPCLayer1PhiHits = 0;
   mu_muid_nRPCLayer2PhiHits = 0;
   mu_muid_nRPCLayer3PhiHits = 0;
   mu_muid_nTGCLayer1EtaHits = 0;
   mu_muid_nTGCLayer2EtaHits = 0;
   mu_muid_nTGCLayer3EtaHits = 0;
   mu_muid_nTGCLayer4EtaHits = 0;
   mu_muid_nTGCLayer1PhiHits = 0;
   mu_muid_nTGCLayer2PhiHits = 0;
   mu_muid_nTGCLayer3PhiHits = 0;
   mu_muid_nTGCLayer4PhiHits = 0;
   mu_muid_barrelSectors = 0;
   mu_muid_endcapSectors = 0;
   mu_muid_trackd0 = 0;
   mu_muid_trackz0 = 0;
   mu_muid_trackphi = 0;
   mu_muid_tracktheta = 0;
   mu_muid_trackqoverp = 0;
   mu_muid_trackcov_d0 = 0;
   mu_muid_trackcov_z0 = 0;
   mu_muid_trackcov_phi = 0;
   mu_muid_trackcov_theta = 0;
   mu_muid_trackcov_qoverp = 0;
   mu_muid_trackcov_d0_z0 = 0;
   mu_muid_trackcov_d0_phi = 0;
   mu_muid_trackcov_d0_theta = 0;
   mu_muid_trackcov_d0_qoverp = 0;
   mu_muid_trackcov_z0_phi = 0;
   mu_muid_trackcov_z0_theta = 0;
   mu_muid_trackcov_z0_qoverp = 0;
   mu_muid_trackcov_phi_theta = 0;
   mu_muid_trackcov_phi_qoverp = 0;
   mu_muid_trackcov_theta_qoverp = 0;
   mu_muid_trackfitchi2 = 0;
   mu_muid_trackfitndof = 0;
   mu_muid_hastrack = 0;
   mu_muid_EF_dr = 0;
   mu_muid_EF_cb_eta = 0;
   mu_muid_EF_cb_phi = 0;
   mu_muid_EF_cb_pt = 0;
   mu_muid_EF_ms_eta = 0;
   mu_muid_EF_ms_phi = 0;
   mu_muid_EF_ms_pt = 0;
   mu_muid_EF_me_eta = 0;
   mu_muid_EF_me_phi = 0;
   mu_muid_EF_me_pt = 0;
   mu_muid_EF_matched = 0;
   mu_muid_L2CB_dr = 0;
   mu_muid_L2CB_pt = 0;
   mu_muid_L2CB_eta = 0;
   mu_muid_L2CB_phi = 0;
   mu_muid_L2CB_id_pt = 0;
   mu_muid_L2CB_ms_pt = 0;
   mu_muid_L2CB_nPixHits = 0;
   mu_muid_L2CB_nSCTHits = 0;
   mu_muid_L2CB_nTRTHits = 0;
   mu_muid_L2CB_nTRTHighTHits = 0;
   mu_muid_L2CB_matched = 0;
   mu_muid_L1_dr = 0;
   mu_muid_L1_pt = 0;
   mu_muid_L1_eta = 0;
   mu_muid_L1_phi = 0;
   mu_muid_L1_thrNumber = 0;
   mu_muid_L1_RoINumber = 0;
   mu_muid_L1_sectorAddress = 0;
   mu_muid_L1_firstCandidate = 0;
   mu_muid_L1_moreCandInRoI = 0;
   mu_muid_L1_moreCandInSector = 0;
   mu_muid_L1_source = 0;
   mu_muid_L1_hemisphere = 0;
   mu_muid_L1_matched = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("isGRL", &isGRL, &b_isGRL);
   fChain->SetBranchAddress("RunNumber", &RunNumber, &b_RunNumber);
   fChain->SetBranchAddress("EventNumber", &EventNumber, &b_EventNumber);
   fChain->SetBranchAddress("timestamp", &timestamp, &b_timestamp);
   fChain->SetBranchAddress("timestamp_ns", &timestamp_ns, &b_timestamp_ns);
   fChain->SetBranchAddress("lbn", &lbn, &b_lbn);
   fChain->SetBranchAddress("bcid", &bcid, &b_bcid);
   fChain->SetBranchAddress("detmask0", &detmask0, &b_detmask0);
   fChain->SetBranchAddress("detmask1", &detmask1, &b_detmask1);
   fChain->SetBranchAddress("pixelFlags", &pixelFlags, &b_pixelFlags);
   fChain->SetBranchAddress("sctFlags", &sctFlags, &b_sctFlags);
   fChain->SetBranchAddress("trtFlags", &trtFlags, &b_trtFlags);
   fChain->SetBranchAddress("larFlags", &larFlags, &b_larFlags);
   fChain->SetBranchAddress("tileFlags", &tileFlags, &b_tileFlags);
   fChain->SetBranchAddress("muonFlags", &muonFlags, &b_muonFlags);
   fChain->SetBranchAddress("fwdFlags", &fwdFlags, &b_fwdFlags);
   fChain->SetBranchAddress("coreFlags", &coreFlags, &b_coreFlags);
   fChain->SetBranchAddress("pixelError", &pixelError, &b_pixelError);
   fChain->SetBranchAddress("sctError", &sctError, &b_sctError);
   fChain->SetBranchAddress("trtError", &trtError, &b_trtError);
   fChain->SetBranchAddress("larError", &larError, &b_larError);
   fChain->SetBranchAddress("tileError", &tileError, &b_tileError);
   fChain->SetBranchAddress("muonError", &muonError, &b_muonError);
   fChain->SetBranchAddress("fwdError", &fwdError, &b_fwdError);
   fChain->SetBranchAddress("coreError", &coreError, &b_coreError);
   fChain->SetBranchAddress("lar_ncellA", &lar_ncellA, &b_lar_ncellA);
   fChain->SetBranchAddress("lar_ncellC", &lar_ncellC, &b_lar_ncellC);
   fChain->SetBranchAddress("lar_energyA", &lar_energyA, &b_lar_energyA);
   fChain->SetBranchAddress("lar_energyC", &lar_energyC, &b_lar_energyC);
   fChain->SetBranchAddress("lar_timeA", &lar_timeA, &b_lar_timeA);
   fChain->SetBranchAddress("lar_timeC", &lar_timeC, &b_lar_timeC);
   fChain->SetBranchAddress("lar_timeDiff", &lar_timeDiff, &b_lar_timeDiff);
   fChain->SetBranchAddress("EF_2mu10", &EF_2mu10, &b_EF_2mu10);
   fChain->SetBranchAddress("EF_2mu4", &EF_2mu4, &b_EF_2mu4);
   fChain->SetBranchAddress("EF_2mu4_DiMu", &EF_2mu4_DiMu, &b_EF_2mu4_DiMu);
   fChain->SetBranchAddress("EF_2mu4_DiMu_SiTrk", &EF_2mu4_DiMu_SiTrk, &b_EF_2mu4_DiMu_SiTrk);
   fChain->SetBranchAddress("EF_2mu4_DiMu_noOS", &EF_2mu4_DiMu_noOS, &b_EF_2mu4_DiMu_noOS);
   fChain->SetBranchAddress("EF_2mu4_DiMu_noOS_passL2", &EF_2mu4_DiMu_noOS_passL2, &b_EF_2mu4_DiMu_noOS_passL2);
   fChain->SetBranchAddress("EF_2mu4_DiMu_noVtx_noOS", &EF_2mu4_DiMu_noVtx_noOS, &b_EF_2mu4_DiMu_noVtx_noOS);
   fChain->SetBranchAddress("EF_2mu4_DiMu_noVtx_noOS_passL2", &EF_2mu4_DiMu_noVtx_noOS_passL2, &b_EF_2mu4_DiMu_noVtx_noOS_passL2);
   fChain->SetBranchAddress("EF_2mu4_MSonly", &EF_2mu4_MSonly, &b_EF_2mu4_MSonly);
   fChain->SetBranchAddress("EF_2mu6", &EF_2mu6, &b_EF_2mu6);
   fChain->SetBranchAddress("EF_2mu6_DiMu", &EF_2mu6_DiMu, &b_EF_2mu6_DiMu);
   fChain->SetBranchAddress("EF_2mu6_DiMu_noVtx_noOS", &EF_2mu6_DiMu_noVtx_noOS, &b_EF_2mu6_DiMu_noVtx_noOS);
   fChain->SetBranchAddress("EF_L1ItemStreamer_L1_2MU0", &EF_L1ItemStreamer_L1_2MU0, &b_EF_L1ItemStreamer_L1_2MU0);
   fChain->SetBranchAddress("EF_L1ItemStreamer_L1_2MU0_MU6", &EF_L1ItemStreamer_L1_2MU0_MU6, &b_EF_L1ItemStreamer_L1_2MU0_MU6);
   fChain->SetBranchAddress("EF_L1ItemStreamer_L1_2MU10", &EF_L1ItemStreamer_L1_2MU10, &b_EF_L1ItemStreamer_L1_2MU10);
   fChain->SetBranchAddress("EF_L1ItemStreamer_L1_2MU6", &EF_L1ItemStreamer_L1_2MU6, &b_EF_L1ItemStreamer_L1_2MU6);
   fChain->SetBranchAddress("EF_L1ItemStreamer_L1_EM10", &EF_L1ItemStreamer_L1_EM10, &b_EF_L1ItemStreamer_L1_EM10);
   fChain->SetBranchAddress("EF_L1ItemStreamer_L1_EM10I", &EF_L1ItemStreamer_L1_EM10I, &b_EF_L1ItemStreamer_L1_EM10I);
   fChain->SetBranchAddress("EF_L1ItemStreamer_L1_EM14", &EF_L1ItemStreamer_L1_EM14, &b_EF_L1ItemStreamer_L1_EM14);
   fChain->SetBranchAddress("EF_L1ItemStreamer_L1_EM2", &EF_L1ItemStreamer_L1_EM2, &b_EF_L1ItemStreamer_L1_EM2);
   //fChain->SetBranchAddress("EF_L1ItemStreamer_L1_EM2_UNPAIRED", &EF_L1ItemStreamer_L1_EM2_UNPAIRED, &b_EF_L1ItemStreamer_L1_EM2_UNPAIRED);
   fChain->SetBranchAddress("EF_L1ItemStreamer_L1_EM3", &EF_L1ItemStreamer_L1_EM3, &b_EF_L1ItemStreamer_L1_EM3);
   fChain->SetBranchAddress("EF_L1ItemStreamer_L1_EM3_EMPTY", &EF_L1ItemStreamer_L1_EM3_EMPTY, &b_EF_L1ItemStreamer_L1_EM3_EMPTY);
   fChain->SetBranchAddress("EF_L1ItemStreamer_L1_EM3_FIRSTEMPTY", &EF_L1ItemStreamer_L1_EM3_FIRSTEMPTY, &b_EF_L1ItemStreamer_L1_EM3_FIRSTEMPTY);
   fChain->SetBranchAddress("EF_L1ItemStreamer_L1_EM3_MV", &EF_L1ItemStreamer_L1_EM3_MV, &b_EF_L1ItemStreamer_L1_EM3_MV);
   fChain->SetBranchAddress("EF_L1ItemStreamer_L1_EM3_UNPAIRED", &EF_L1ItemStreamer_L1_EM3_UNPAIRED, &b_EF_L1ItemStreamer_L1_EM3_UNPAIRED);
   fChain->SetBranchAddress("EF_L1ItemStreamer_L1_EM4", &EF_L1ItemStreamer_L1_EM4, &b_EF_L1ItemStreamer_L1_EM4);
   fChain->SetBranchAddress("EF_L1ItemStreamer_L1_EM5", &EF_L1ItemStreamer_L1_EM5, &b_EF_L1ItemStreamer_L1_EM5);
   fChain->SetBranchAddress("EF_L1ItemStreamer_L1_EM5I", &EF_L1ItemStreamer_L1_EM5I, &b_EF_L1ItemStreamer_L1_EM5I);
   fChain->SetBranchAddress("EF_L1ItemStreamer_L1_MU0", &EF_L1ItemStreamer_L1_MU0, &b_EF_L1ItemStreamer_L1_MU0);
   fChain->SetBranchAddress("EF_L1ItemStreamer_L1_MU0_COMM", &EF_L1ItemStreamer_L1_MU0_COMM, &b_EF_L1ItemStreamer_L1_MU0_COMM);
   fChain->SetBranchAddress("EF_L1ItemStreamer_L1_MU0_COMM_EMPTY", &EF_L1ItemStreamer_L1_MU0_COMM_EMPTY, &b_EF_L1ItemStreamer_L1_MU0_COMM_EMPTY);
   fChain->SetBranchAddress("EF_L1ItemStreamer_L1_MU0_COMM_FIRSTEMPTY", &EF_L1ItemStreamer_L1_MU0_COMM_FIRSTEMPTY, &b_EF_L1ItemStreamer_L1_MU0_COMM_FIRSTEMPTY);
   fChain->SetBranchAddress("EF_L1ItemStreamer_L1_MU0_EM3", &EF_L1ItemStreamer_L1_MU0_EM3, &b_EF_L1ItemStreamer_L1_MU0_EM3);
   fChain->SetBranchAddress("EF_L1ItemStreamer_L1_MU0_EMPTY", &EF_L1ItemStreamer_L1_MU0_EMPTY, &b_EF_L1ItemStreamer_L1_MU0_EMPTY);
   fChain->SetBranchAddress("EF_L1ItemStreamer_L1_MU0_FIRSTEMPTY", &EF_L1ItemStreamer_L1_MU0_FIRSTEMPTY, &b_EF_L1ItemStreamer_L1_MU0_FIRSTEMPTY);
   fChain->SetBranchAddress("EF_L1ItemStreamer_L1_MU0_J10", &EF_L1ItemStreamer_L1_MU0_J10, &b_EF_L1ItemStreamer_L1_MU0_J10);
   fChain->SetBranchAddress("EF_L1ItemStreamer_L1_MU0_J15", &EF_L1ItemStreamer_L1_MU0_J15, &b_EF_L1ItemStreamer_L1_MU0_J15);
   fChain->SetBranchAddress("EF_L1ItemStreamer_L1_MU0_J5", &EF_L1ItemStreamer_L1_MU0_J5, &b_EF_L1ItemStreamer_L1_MU0_J5);
   fChain->SetBranchAddress("EF_L1ItemStreamer_L1_MU0_MV", &EF_L1ItemStreamer_L1_MU0_MV, &b_EF_L1ItemStreamer_L1_MU0_MV);
   fChain->SetBranchAddress("EF_L1ItemStreamer_L1_MU0_UNPAIRED", &EF_L1ItemStreamer_L1_MU0_UNPAIRED, &b_EF_L1ItemStreamer_L1_MU0_UNPAIRED);
   fChain->SetBranchAddress("EF_L1ItemStreamer_L1_MU10", &EF_L1ItemStreamer_L1_MU10, &b_EF_L1ItemStreamer_L1_MU10);
   fChain->SetBranchAddress("EF_L1ItemStreamer_L1_MU10_EMPTY", &EF_L1ItemStreamer_L1_MU10_EMPTY, &b_EF_L1ItemStreamer_L1_MU10_EMPTY);
   fChain->SetBranchAddress("EF_L1ItemStreamer_L1_MU15", &EF_L1ItemStreamer_L1_MU15, &b_EF_L1ItemStreamer_L1_MU15);
   fChain->SetBranchAddress("EF_L1ItemStreamer_L1_MU20", &EF_L1ItemStreamer_L1_MU20, &b_EF_L1ItemStreamer_L1_MU20);
   fChain->SetBranchAddress("EF_L1ItemStreamer_L1_MU6", &EF_L1ItemStreamer_L1_MU6, &b_EF_L1ItemStreamer_L1_MU6);
   fChain->SetBranchAddress("EF_L1ItemStreamer_L1_MU6_EM3", &EF_L1ItemStreamer_L1_MU6_EM3, &b_EF_L1ItemStreamer_L1_MU6_EM3);
   fChain->SetBranchAddress("EF_L1ItemStreamer_L1_MU6_EMPTY", &EF_L1ItemStreamer_L1_MU6_EMPTY, &b_EF_L1ItemStreamer_L1_MU6_EMPTY);
   fChain->SetBranchAddress("EF_L1ItemStreamer_L1_MU6_FIRSTEMPTY", &EF_L1ItemStreamer_L1_MU6_FIRSTEMPTY, &b_EF_L1ItemStreamer_L1_MU6_FIRSTEMPTY);
   fChain->SetBranchAddress("EF_L1ItemStreamer_L1_MU6_J5", &EF_L1ItemStreamer_L1_MU6_J5, &b_EF_L1ItemStreamer_L1_MU6_J5);
   fChain->SetBranchAddress("EF_L1ItemStreamer_L1_MU6_UNPAIRED", &EF_L1ItemStreamer_L1_MU6_UNPAIRED, &b_EF_L1ItemStreamer_L1_MU6_UNPAIRED);
   //fChain->SetBranchAddress("EF_mu0_missingRoi", &EF_mu0_missingRoi, &b_EF_mu0_missingRoi);
   //fChain->SetBranchAddress("EF_mu0_rpcOnly", &EF_mu0_rpcOnly, &b_EF_mu0_rpcOnly);
   fChain->SetBranchAddress("EF_mu10", &EF_mu10, &b_EF_mu10);
   fChain->SetBranchAddress("EF_mu10_MG", &EF_mu10_MG, &b_EF_mu10_MG);
   fChain->SetBranchAddress("EF_mu10_MSonly", &EF_mu10_MSonly, &b_EF_mu10_MSonly);
   fChain->SetBranchAddress("EF_mu10_MSonly_cosmic", &EF_mu10_MSonly_cosmic, &b_EF_mu10_MSonly_cosmic);
   fChain->SetBranchAddress("EF_mu10_NoIDTrkCut", &EF_mu10_NoIDTrkCut, &b_EF_mu10_NoIDTrkCut);
   fChain->SetBranchAddress("EF_mu10_SiTrk", &EF_mu10_SiTrk, &b_EF_mu10_SiTrk);
   fChain->SetBranchAddress("EF_mu10_cosmic", &EF_mu10_cosmic, &b_EF_mu10_cosmic);
   fChain->SetBranchAddress("EF_mu10_muCombTag", &EF_mu10_muCombTag, &b_EF_mu10_muCombTag);
   fChain->SetBranchAddress("EF_mu10_muCombTag_SiTrk", &EF_mu10_muCombTag_SiTrk, &b_EF_mu10_muCombTag_SiTrk);
   fChain->SetBranchAddress("EF_mu10_passHLT", &EF_mu10_passHLT, &b_EF_mu10_passHLT);
   fChain->SetBranchAddress("EF_mu10i_loose", &EF_mu10i_loose, &b_EF_mu10i_loose);
   fChain->SetBranchAddress("EF_mu13", &EF_mu13, &b_EF_mu13);
   fChain->SetBranchAddress("EF_mu15", &EF_mu15, &b_EF_mu15);
   fChain->SetBranchAddress("EF_mu20", &EF_mu20, &b_EF_mu20);
   fChain->SetBranchAddress("EF_mu20_MSonly", &EF_mu20_MSonly, &b_EF_mu20_MSonly);
   fChain->SetBranchAddress("EF_mu20_passHLT", &EF_mu20_passHLT, &b_EF_mu20_passHLT);
   fChain->SetBranchAddress("EF_mu4", &EF_mu4, &b_EF_mu4);
   fChain->SetBranchAddress("EF_mu4_DiMu", &EF_mu4_DiMu, &b_EF_mu4_DiMu);
   fChain->SetBranchAddress("EF_mu4_DiMu_FS", &EF_mu4_DiMu_FS, &b_EF_mu4_DiMu_FS);
   fChain->SetBranchAddress("EF_mu4_DiMu_FS_noOS", &EF_mu4_DiMu_FS_noOS, &b_EF_mu4_DiMu_FS_noOS);
   //fChain->SetBranchAddress("EF_mu4_Jpsie5e3", &EF_mu4_Jpsie5e3, &b_EF_mu4_Jpsie5e3);
   //fChain->SetBranchAddress("EF_mu4_Jpsie5e3_FS", &EF_mu4_Jpsie5e3_FS, &b_EF_mu4_Jpsie5e3_FS);
   //fChain->SetBranchAddress("EF_mu4_Jpsie5e3_SiTrk", &EF_mu4_Jpsie5e3_SiTrk, &b_EF_mu4_Jpsie5e3_SiTrk);
   //fChain->SetBranchAddress("EF_mu4_Jpsie5e3_SiTrk_FS", &EF_mu4_Jpsie5e3_SiTrk_FS, &b_EF_mu4_Jpsie5e3_SiTrk_FS);
   fChain->SetBranchAddress("EF_mu4_L2MSonly_EFFS_passL2", &EF_mu4_L2MSonly_EFFS_passL2, &b_EF_mu4_L2MSonly_EFFS_passL2);
   fChain->SetBranchAddress("EF_mu4_MG", &EF_mu4_MG, &b_EF_mu4_MG);
   fChain->SetBranchAddress("EF_mu4_MSonly", &EF_mu4_MSonly, &b_EF_mu4_MSonly);
   fChain->SetBranchAddress("EF_mu4_MSonly_EFFS_passL2", &EF_mu4_MSonly_EFFS_passL2, &b_EF_mu4_MSonly_EFFS_passL2);
   fChain->SetBranchAddress("EF_mu4_MSonly_MB2_noL2_EFFS", &EF_mu4_MSonly_MB2_noL2_EFFS, &b_EF_mu4_MSonly_MB2_noL2_EFFS);
   fChain->SetBranchAddress("EF_mu4_MSonly_Trk_Jpsi_loose", &EF_mu4_MSonly_Trk_Jpsi_loose, &b_EF_mu4_MSonly_Trk_Jpsi_loose);
   fChain->SetBranchAddress("EF_mu4_MSonly_Trk_Upsi_loose_FS", &EF_mu4_MSonly_Trk_Upsi_loose_FS, &b_EF_mu4_MSonly_Trk_Upsi_loose_FS);
   fChain->SetBranchAddress("EF_mu4_MSonly_cosmic", &EF_mu4_MSonly_cosmic, &b_EF_mu4_MSonly_cosmic);
   fChain->SetBranchAddress("EF_mu4_MSonly_firstempty", &EF_mu4_MSonly_firstempty, &b_EF_mu4_MSonly_firstempty);
   fChain->SetBranchAddress("EF_mu4_MV", &EF_mu4_MV, &b_EF_mu4_MV);
   fChain->SetBranchAddress("EF_mu4_NoIDTrkCut", &EF_mu4_NoIDTrkCut, &b_EF_mu4_NoIDTrkCut);
   fChain->SetBranchAddress("EF_mu4_SiTrk", &EF_mu4_SiTrk, &b_EF_mu4_SiTrk);
   fChain->SetBranchAddress("EF_mu4_Trk_Jpsi_loose", &EF_mu4_Trk_Jpsi_loose, &b_EF_mu4_Trk_Jpsi_loose);
   fChain->SetBranchAddress("EF_mu4_Trk_Upsi_loose_FS", &EF_mu4_Trk_Upsi_loose_FS, &b_EF_mu4_Trk_Upsi_loose_FS);
   fChain->SetBranchAddress("EF_mu4_comm", &EF_mu4_comm, &b_EF_mu4_comm);
   fChain->SetBranchAddress("EF_mu4_comm_MSonly", &EF_mu4_comm_MSonly, &b_EF_mu4_comm_MSonly);
   fChain->SetBranchAddress("EF_mu4_comm_MSonly_cosmic", &EF_mu4_comm_MSonly_cosmic, &b_EF_mu4_comm_MSonly_cosmic);
   fChain->SetBranchAddress("EF_mu4_comm_MSonly_firstempty", &EF_mu4_comm_MSonly_firstempty, &b_EF_mu4_comm_MSonly_firstempty);
   fChain->SetBranchAddress("EF_mu4_comm_cosmic", &EF_mu4_comm_cosmic, &b_EF_mu4_comm_cosmic);
   fChain->SetBranchAddress("EF_mu4_comm_firstempty", &EF_mu4_comm_firstempty, &b_EF_mu4_comm_firstempty);
   fChain->SetBranchAddress("EF_mu4_cosmic", &EF_mu4_cosmic, &b_EF_mu4_cosmic);
   fChain->SetBranchAddress("EF_mu4_firstempty", &EF_mu4_firstempty, &b_EF_mu4_firstempty);
   fChain->SetBranchAddress("EF_mu4_j10_matched", &EF_mu4_j10_matched, &b_EF_mu4_j10_matched);
   fChain->SetBranchAddress("EF_mu4_j20_matched", &EF_mu4_j20_matched, &b_EF_mu4_j20_matched);
   fChain->SetBranchAddress("EF_mu4_j5_matched", &EF_mu4_j5_matched, &b_EF_mu4_j5_matched);
   fChain->SetBranchAddress("EF_mu4_mu6", &EF_mu4_mu6, &b_EF_mu4_mu6);
   fChain->SetBranchAddress("EF_mu4_muCombTag", &EF_mu4_muCombTag, &b_EF_mu4_muCombTag);
   fChain->SetBranchAddress("EF_mu4_muCombTag_SiTrk", &EF_mu4_muCombTag_SiTrk, &b_EF_mu4_muCombTag_SiTrk);
   fChain->SetBranchAddress("EF_mu4_passHLT", &EF_mu4_passHLT, &b_EF_mu4_passHLT);
   fChain->SetBranchAddress("EF_mu4_tile", &EF_mu4_tile, &b_EF_mu4_tile);
   fChain->SetBranchAddress("EF_mu4_tile_SiTrk", &EF_mu4_tile_SiTrk, &b_EF_mu4_tile_SiTrk);
   fChain->SetBranchAddress("EF_mu4_trod", &EF_mu4_trod, &b_EF_mu4_trod);
   fChain->SetBranchAddress("EF_mu4_trod_SiTrk", &EF_mu4_trod_SiTrk, &b_EF_mu4_trod_SiTrk);
   //fChain->SetBranchAddress("EF_mu4_unpaired", &EF_mu4_unpaired, &b_EF_mu4_unpaired);
   fChain->SetBranchAddress("EF_mu4mu6_DiMu", &EF_mu4mu6_DiMu, &b_EF_mu4mu6_DiMu);
   fChain->SetBranchAddress("EF_mu6", &EF_mu6, &b_EF_mu6);
   fChain->SetBranchAddress("EF_mu6_DiMu", &EF_mu6_DiMu, &b_EF_mu6_DiMu);
   fChain->SetBranchAddress("EF_mu6_DiMu_FS", &EF_mu6_DiMu_FS, &b_EF_mu6_DiMu_FS);
   fChain->SetBranchAddress("EF_mu6_DiMu_FS_noOS", &EF_mu6_DiMu_FS_noOS, &b_EF_mu6_DiMu_FS_noOS);
   fChain->SetBranchAddress("EF_mu6_DsPhiPi", &EF_mu6_DsPhiPi, &b_EF_mu6_DsPhiPi);
   fChain->SetBranchAddress("EF_mu6_Jpsie5e3", &EF_mu6_Jpsie5e3, &b_EF_mu6_Jpsie5e3);
   //fChain->SetBranchAddress("EF_mu6_Jpsie5e3_FS", &EF_mu6_Jpsie5e3_FS, &b_EF_mu6_Jpsie5e3_FS);
   //fChain->SetBranchAddress("EF_mu6_Jpsie5e3_SiTrk", &EF_mu6_Jpsie5e3_SiTrk, &b_EF_mu6_Jpsie5e3_SiTrk);
   //fChain->SetBranchAddress("EF_mu6_Jpsie5e3_SiTrk_FS", &EF_mu6_Jpsie5e3_SiTrk_FS, &b_EF_mu6_Jpsie5e3_SiTrk_FS);
   fChain->SetBranchAddress("EF_mu6_MG", &EF_mu6_MG, &b_EF_mu6_MG);
   fChain->SetBranchAddress("EF_mu6_MSonly", &EF_mu6_MSonly, &b_EF_mu6_MSonly);
   fChain->SetBranchAddress("EF_mu6_MSonly_cosmic", &EF_mu6_MSonly_cosmic, &b_EF_mu6_MSonly_cosmic);
   fChain->SetBranchAddress("EF_mu6_MSonly_firstempty", &EF_mu6_MSonly_firstempty, &b_EF_mu6_MSonly_firstempty);
   fChain->SetBranchAddress("EF_mu6_MSonly_unpaired", &EF_mu6_MSonly_unpaired, &b_EF_mu6_MSonly_unpaired);
   fChain->SetBranchAddress("EF_mu6_SiTrk", &EF_mu6_SiTrk, &b_EF_mu6_SiTrk);
   fChain->SetBranchAddress("EF_mu6_Trk_Jpsi_loose", &EF_mu6_Trk_Jpsi_loose, &b_EF_mu6_Trk_Jpsi_loose);
   fChain->SetBranchAddress("EF_mu6_Trk_Jpsi_loose_FS", &EF_mu6_Trk_Jpsi_loose_FS, &b_EF_mu6_Trk_Jpsi_loose_FS);
   fChain->SetBranchAddress("EF_mu6_Trk_Upsi_loose_FS", &EF_mu6_Trk_Upsi_loose_FS, &b_EF_mu6_Trk_Upsi_loose_FS);
   fChain->SetBranchAddress("EF_mu6_cosmic", &EF_mu6_cosmic, &b_EF_mu6_cosmic);
   fChain->SetBranchAddress("EF_mu6_firstempty", &EF_mu6_firstempty, &b_EF_mu6_firstempty);
   fChain->SetBranchAddress("EF_mu6_muCombTag", &EF_mu6_muCombTag, &b_EF_mu6_muCombTag);
   fChain->SetBranchAddress("EF_mu6_muCombTag_SiTrk", &EF_mu6_muCombTag_SiTrk, &b_EF_mu6_muCombTag_SiTrk);
   fChain->SetBranchAddress("EF_mu6_passHLT", &EF_mu6_passHLT, &b_EF_mu6_passHLT);
   fChain->SetBranchAddress("EF_mu6_unpaired", &EF_mu6_unpaired, &b_EF_mu6_unpaired);
   fChain->SetBranchAddress("L1_2EM2", &L1_2EM2, &b_L1_2EM2);
   fChain->SetBranchAddress("L1_2EM3", &L1_2EM3, &b_L1_2EM3);
   fChain->SetBranchAddress("L1_2EM4", &L1_2EM4, &b_L1_2EM4);
   fChain->SetBranchAddress("L1_2EM5", &L1_2EM5, &b_L1_2EM5);
   fChain->SetBranchAddress("L1_2MU0", &L1_2MU0, &b_L1_2MU0);
   fChain->SetBranchAddress("L1_2MU0_MU6", &L1_2MU0_MU6, &b_L1_2MU0_MU6);
   fChain->SetBranchAddress("L1_2MU10", &L1_2MU10, &b_L1_2MU10);
   fChain->SetBranchAddress("L1_2MU6", &L1_2MU6, &b_L1_2MU6);
   fChain->SetBranchAddress("L1_EM10", &L1_EM10, &b_L1_EM10);
   fChain->SetBranchAddress("L1_EM10I", &L1_EM10I, &b_L1_EM10I);
   fChain->SetBranchAddress("L1_EM14", &L1_EM14, &b_L1_EM14);
   fChain->SetBranchAddress("L1_EM2", &L1_EM2, &b_L1_EM2);
   //fChain->SetBranchAddress("L1_EM2_UNPAIRED", &L1_EM2_UNPAIRED, &b_L1_EM2_UNPAIRED);
   fChain->SetBranchAddress("L1_EM3", &L1_EM3, &b_L1_EM3);
   fChain->SetBranchAddress("L1_EM3_EMPTY", &L1_EM3_EMPTY, &b_L1_EM3_EMPTY);
   fChain->SetBranchAddress("L1_EM3_FIRSTEMPTY", &L1_EM3_FIRSTEMPTY, &b_L1_EM3_FIRSTEMPTY);
   fChain->SetBranchAddress("L1_EM3_MV", &L1_EM3_MV, &b_L1_EM3_MV);
   fChain->SetBranchAddress("L1_EM3_UNPAIRED", &L1_EM3_UNPAIRED, &b_L1_EM3_UNPAIRED);
   fChain->SetBranchAddress("L1_EM4", &L1_EM4, &b_L1_EM4);
   fChain->SetBranchAddress("L1_EM5", &L1_EM5, &b_L1_EM5);
   fChain->SetBranchAddress("L1_EM5I", &L1_EM5I, &b_L1_EM5I);
   fChain->SetBranchAddress("L1_MU0", &L1_MU0, &b_L1_MU0);
   fChain->SetBranchAddress("L1_MU0_COMM", &L1_MU0_COMM, &b_L1_MU0_COMM);
   fChain->SetBranchAddress("L1_MU0_COMM_EMPTY", &L1_MU0_COMM_EMPTY, &b_L1_MU0_COMM_EMPTY);
   fChain->SetBranchAddress("L1_MU0_COMM_FIRSTEMPTY", &L1_MU0_COMM_FIRSTEMPTY, &b_L1_MU0_COMM_FIRSTEMPTY);
   fChain->SetBranchAddress("L1_MU0_EM3", &L1_MU0_EM3, &b_L1_MU0_EM3);
   fChain->SetBranchAddress("L1_MU0_EMPTY", &L1_MU0_EMPTY, &b_L1_MU0_EMPTY);
   fChain->SetBranchAddress("L1_MU0_FIRSTEMPTY", &L1_MU0_FIRSTEMPTY, &b_L1_MU0_FIRSTEMPTY);
   fChain->SetBranchAddress("L1_MU0_J10", &L1_MU0_J10, &b_L1_MU0_J10);
   fChain->SetBranchAddress("L1_MU0_J15", &L1_MU0_J15, &b_L1_MU0_J15);
   fChain->SetBranchAddress("L1_MU0_J5", &L1_MU0_J5, &b_L1_MU0_J5);
   fChain->SetBranchAddress("L1_MU0_MV", &L1_MU0_MV, &b_L1_MU0_MV);
   //fChain->SetBranchAddress("L1_MU0_UNPAIRED", &L1_MU0_UNPAIRED, &b_L1_MU0_UNPAIRED);
   fChain->SetBranchAddress("L1_MU10", &L1_MU10, &b_L1_MU10);
   fChain->SetBranchAddress("L1_MU10_EMPTY", &L1_MU10_EMPTY, &b_L1_MU10_EMPTY);
   fChain->SetBranchAddress("L1_MU15", &L1_MU15, &b_L1_MU15);
   fChain->SetBranchAddress("L1_MU20", &L1_MU20, &b_L1_MU20);
   fChain->SetBranchAddress("L1_MU6", &L1_MU6, &b_L1_MU6);
   fChain->SetBranchAddress("L1_MU6_EM3", &L1_MU6_EM3, &b_L1_MU6_EM3);
   fChain->SetBranchAddress("L1_MU6_EMPTY", &L1_MU6_EMPTY, &b_L1_MU6_EMPTY);
   fChain->SetBranchAddress("L1_MU6_FIRSTEMPTY", &L1_MU6_FIRSTEMPTY, &b_L1_MU6_FIRSTEMPTY);
   fChain->SetBranchAddress("L1_MU6_J5", &L1_MU6_J5, &b_L1_MU6_J5);
   fChain->SetBranchAddress("L1_MU6_UNPAIRED", &L1_MU6_UNPAIRED, &b_L1_MU6_UNPAIRED);
   fChain->SetBranchAddress("L2_2mu10", &L2_2mu10, &b_L2_2mu10);
   fChain->SetBranchAddress("L2_2mu4", &L2_2mu4, &b_L2_2mu4);
   fChain->SetBranchAddress("L2_2mu4_DiMu", &L2_2mu4_DiMu, &b_L2_2mu4_DiMu);
   fChain->SetBranchAddress("L2_2mu4_DiMu_SiTrk", &L2_2mu4_DiMu_SiTrk, &b_L2_2mu4_DiMu_SiTrk);
   fChain->SetBranchAddress("L2_2mu4_DiMu_noOS", &L2_2mu4_DiMu_noOS, &b_L2_2mu4_DiMu_noOS);
   fChain->SetBranchAddress("L2_2mu4_DiMu_noOS_passL2", &L2_2mu4_DiMu_noOS_passL2, &b_L2_2mu4_DiMu_noOS_passL2);
   fChain->SetBranchAddress("L2_2mu4_DiMu_noVtx_noOS", &L2_2mu4_DiMu_noVtx_noOS, &b_L2_2mu4_DiMu_noVtx_noOS);
   fChain->SetBranchAddress("L2_2mu4_DiMu_noVtx_noOS_passL2", &L2_2mu4_DiMu_noVtx_noOS_passL2, &b_L2_2mu4_DiMu_noVtx_noOS_passL2);
   fChain->SetBranchAddress("L2_2mu4_MSonly", &L2_2mu4_MSonly, &b_L2_2mu4_MSonly);
   fChain->SetBranchAddress("L2_2mu6", &L2_2mu6, &b_L2_2mu6);
   fChain->SetBranchAddress("L2_2mu6_DiMu", &L2_2mu6_DiMu, &b_L2_2mu6_DiMu);
   fChain->SetBranchAddress("L2_2mu6_DiMu_noVtx_noOS", &L2_2mu6_DiMu_noVtx_noOS, &b_L2_2mu6_DiMu_noVtx_noOS);
   fChain->SetBranchAddress("L2_L1ItemStreamer_L1_MU0", &L2_L1ItemStreamer_L1_MU0, &b_L2_L1ItemStreamer_L1_MU0);
   fChain->SetBranchAddress("L2_L1ItemStreamer_L1_MU0_COMM", &L2_L1ItemStreamer_L1_MU0_COMM, &b_L2_L1ItemStreamer_L1_MU0_COMM);
   fChain->SetBranchAddress("L2_L1ItemStreamer_L1_MU0_COMM_EMPTY", &L2_L1ItemStreamer_L1_MU0_COMM_EMPTY, &b_L2_L1ItemStreamer_L1_MU0_COMM_EMPTY);
   fChain->SetBranchAddress("L2_L1ItemStreamer_L1_MU0_COMM_FIRSTEMPTY", &L2_L1ItemStreamer_L1_MU0_COMM_FIRSTEMPTY, &b_L2_L1ItemStreamer_L1_MU0_COMM_FIRSTEMPTY);
   fChain->SetBranchAddress("L2_L1ItemStreamer_L1_MU0_EM3", &L2_L1ItemStreamer_L1_MU0_EM3, &b_L2_L1ItemStreamer_L1_MU0_EM3);
   fChain->SetBranchAddress("L2_L1ItemStreamer_L1_MU0_EMPTY", &L2_L1ItemStreamer_L1_MU0_EMPTY, &b_L2_L1ItemStreamer_L1_MU0_EMPTY);
   fChain->SetBranchAddress("L2_L1ItemStreamer_L1_MU0_FIRSTEMPTY", &L2_L1ItemStreamer_L1_MU0_FIRSTEMPTY, &b_L2_L1ItemStreamer_L1_MU0_FIRSTEMPTY);
   fChain->SetBranchAddress("L2_L1ItemStreamer_L1_MU0_J10", &L2_L1ItemStreamer_L1_MU0_J10, &b_L2_L1ItemStreamer_L1_MU0_J10);
   fChain->SetBranchAddress("L2_L1ItemStreamer_L1_MU0_J15", &L2_L1ItemStreamer_L1_MU0_J15, &b_L2_L1ItemStreamer_L1_MU0_J15);
   fChain->SetBranchAddress("L2_L1ItemStreamer_L1_MU0_J5", &L2_L1ItemStreamer_L1_MU0_J5, &b_L2_L1ItemStreamer_L1_MU0_J5);
   fChain->SetBranchAddress("L2_L1ItemStreamer_L1_MU0_MV", &L2_L1ItemStreamer_L1_MU0_MV, &b_L2_L1ItemStreamer_L1_MU0_MV);
   //fChain->SetBranchAddress("L2_L1ItemStreamer_L1_MU0_UNPAIRED", &L2_L1ItemStreamer_L1_MU0_UNPAIRED, &b_L2_L1ItemStreamer_L1_MU0_UNPAIRED);
   fChain->SetBranchAddress("L2_L1ItemStreamer_L1_MU10", &L2_L1ItemStreamer_L1_MU10, &b_L2_L1ItemStreamer_L1_MU10);
   fChain->SetBranchAddress("L2_L1ItemStreamer_L1_MU10_EMPTY", &L2_L1ItemStreamer_L1_MU10_EMPTY, &b_L2_L1ItemStreamer_L1_MU10_EMPTY);
   fChain->SetBranchAddress("L2_L1ItemStreamer_L1_MU15", &L2_L1ItemStreamer_L1_MU15, &b_L2_L1ItemStreamer_L1_MU15);
   fChain->SetBranchAddress("L2_L1ItemStreamer_L1_MU20", &L2_L1ItemStreamer_L1_MU20, &b_L2_L1ItemStreamer_L1_MU20);
   fChain->SetBranchAddress("L2_L1ItemStreamer_L1_MU6", &L2_L1ItemStreamer_L1_MU6, &b_L2_L1ItemStreamer_L1_MU6);
   fChain->SetBranchAddress("L2_L1ItemStreamer_L1_MU6_EM3", &L2_L1ItemStreamer_L1_MU6_EM3, &b_L2_L1ItemStreamer_L1_MU6_EM3);
   fChain->SetBranchAddress("L2_L1ItemStreamer_L1_MU6_EMPTY", &L2_L1ItemStreamer_L1_MU6_EMPTY, &b_L2_L1ItemStreamer_L1_MU6_EMPTY);
   fChain->SetBranchAddress("L2_L1ItemStreamer_L1_MU6_FIRSTEMPTY", &L2_L1ItemStreamer_L1_MU6_FIRSTEMPTY, &b_L2_L1ItemStreamer_L1_MU6_FIRSTEMPTY);
   fChain->SetBranchAddress("L2_L1ItemStreamer_L1_MU6_J5", &L2_L1ItemStreamer_L1_MU6_J5, &b_L2_L1ItemStreamer_L1_MU6_J5);
   fChain->SetBranchAddress("L2_L1ItemStreamer_L1_MU6_UNPAIRED", &L2_L1ItemStreamer_L1_MU6_UNPAIRED, &b_L2_L1ItemStreamer_L1_MU6_UNPAIRED);
   //fChain->SetBranchAddress("L2_mu0_missingRoi", &L2_mu0_missingRoi, &b_L2_mu0_missingRoi);
   //fChain->SetBranchAddress("L2_mu0_rpcOnly", &L2_mu0_rpcOnly, &b_L2_mu0_rpcOnly);
   fChain->SetBranchAddress("L2_mu10", &L2_mu10, &b_L2_mu10);
   fChain->SetBranchAddress("L2_mu10_MG", &L2_mu10_MG, &b_L2_mu10_MG);
   fChain->SetBranchAddress("L2_mu10_MSonly", &L2_mu10_MSonly, &b_L2_mu10_MSonly);
   fChain->SetBranchAddress("L2_mu10_MSonly_cosmic", &L2_mu10_MSonly_cosmic, &b_L2_mu10_MSonly_cosmic);
   fChain->SetBranchAddress("L2_mu10_NoIDTrkCut", &L2_mu10_NoIDTrkCut, &b_L2_mu10_NoIDTrkCut);
   fChain->SetBranchAddress("L2_mu10_SiTrk", &L2_mu10_SiTrk, &b_L2_mu10_SiTrk);
   fChain->SetBranchAddress("L2_mu10_cosmic", &L2_mu10_cosmic, &b_L2_mu10_cosmic);
   fChain->SetBranchAddress("L2_mu10_muCombTag", &L2_mu10_muCombTag, &b_L2_mu10_muCombTag);
   fChain->SetBranchAddress("L2_mu10_muCombTag_SiTrk", &L2_mu10_muCombTag_SiTrk, &b_L2_mu10_muCombTag_SiTrk);
   fChain->SetBranchAddress("L2_mu10_passHLT", &L2_mu10_passHLT, &b_L2_mu10_passHLT);
   fChain->SetBranchAddress("L2_mu10i_loose", &L2_mu10i_loose, &b_L2_mu10i_loose);
   fChain->SetBranchAddress("L2_mu13 ", &L2_mu13 , &b_L2_mu13 );
   fChain->SetBranchAddress("L2_mu15", &L2_mu15, &b_L2_mu15);
   fChain->SetBranchAddress("L2_mu20", &L2_mu20, &b_L2_mu20);
   fChain->SetBranchAddress("L2_mu20_MSonly", &L2_mu20_MSonly, &b_L2_mu20_MSonly);
   fChain->SetBranchAddress("L2_mu20_passHLT", &L2_mu20_passHLT, &b_L2_mu20_passHLT);
   fChain->SetBranchAddress("L2_mu4", &L2_mu4, &b_L2_mu4);
   fChain->SetBranchAddress("L2_mu4_DiMu", &L2_mu4_DiMu, &b_L2_mu4_DiMu);
   fChain->SetBranchAddress("L2_mu4_DiMu_FS", &L2_mu4_DiMu_FS, &b_L2_mu4_DiMu_FS);
   fChain->SetBranchAddress("L2_mu4_DiMu_FS_noOS", &L2_mu4_DiMu_FS_noOS, &b_L2_mu4_DiMu_FS_noOS);
   //fChain->SetBranchAddress("L2_mu4_Jpsie5e3", &L2_mu4_Jpsie5e3, &b_L2_mu4_Jpsie5e3);
   //fChain->SetBranchAddress("L2_mu4_Jpsie5e3_FS", &L2_mu4_Jpsie5e3_FS, &b_L2_mu4_Jpsie5e3_FS);
   //fChain->SetBranchAddress("L2_mu4_Jpsie5e3_SiTrk", &L2_mu4_Jpsie5e3_SiTrk, &b_L2_mu4_Jpsie5e3_SiTrk);
   //fChain->SetBranchAddress("L2_mu4_Jpsie5e3_SiTrk_FS", &L2_mu4_Jpsie5e3_SiTrk_FS, &b_L2_mu4_Jpsie5e3_SiTrk_FS);
   fChain->SetBranchAddress("L2_mu4_L2MSonly_EFFS_passL2", &L2_mu4_L2MSonly_EFFS_passL2, &b_L2_mu4_L2MSonly_EFFS_passL2);
   fChain->SetBranchAddress("L2_mu4_MG", &L2_mu4_MG, &b_L2_mu4_MG);
   fChain->SetBranchAddress("L2_mu4_MSonly", &L2_mu4_MSonly, &b_L2_mu4_MSonly);
   fChain->SetBranchAddress("L2_mu4_MSonly_EFFS_passL2", &L2_mu4_MSonly_EFFS_passL2, &b_L2_mu4_MSonly_EFFS_passL2);
   fChain->SetBranchAddress("L2_mu4_MSonly_MB2_noL2_EFFS", &L2_mu4_MSonly_MB2_noL2_EFFS, &b_L2_mu4_MSonly_MB2_noL2_EFFS);
   fChain->SetBranchAddress("L2_mu4_MSonly_Trk_Jpsi_loose", &L2_mu4_MSonly_Trk_Jpsi_loose, &b_L2_mu4_MSonly_Trk_Jpsi_loose);
   fChain->SetBranchAddress("L2_mu4_MSonly_Trk_Upsi_loose_FS", &L2_mu4_MSonly_Trk_Upsi_loose_FS, &b_L2_mu4_MSonly_Trk_Upsi_loose_FS);
   fChain->SetBranchAddress("L2_mu4_MSonly_cosmic", &L2_mu4_MSonly_cosmic, &b_L2_mu4_MSonly_cosmic);
   fChain->SetBranchAddress("L2_mu4_MSonly_firstempty", &L2_mu4_MSonly_firstempty, &b_L2_mu4_MSonly_firstempty);
   fChain->SetBranchAddress("L2_mu4_MV", &L2_mu4_MV, &b_L2_mu4_MV);
   fChain->SetBranchAddress("L2_mu4_NoIDTrkCut", &L2_mu4_NoIDTrkCut, &b_L2_mu4_NoIDTrkCut);
   fChain->SetBranchAddress("L2_mu4_SiTrk", &L2_mu4_SiTrk, &b_L2_mu4_SiTrk);
   fChain->SetBranchAddress("L2_mu4_Trk_Jpsi_loose", &L2_mu4_Trk_Jpsi_loose, &b_L2_mu4_Trk_Jpsi_loose);
   fChain->SetBranchAddress("L2_mu4_Trk_Upsi_loose_FS", &L2_mu4_Trk_Upsi_loose_FS, &b_L2_mu4_Trk_Upsi_loose_FS);
   fChain->SetBranchAddress("L2_mu4_comm", &L2_mu4_comm, &b_L2_mu4_comm);
   fChain->SetBranchAddress("L2_mu4_comm_MSonly", &L2_mu4_comm_MSonly, &b_L2_mu4_comm_MSonly);
   fChain->SetBranchAddress("L2_mu4_comm_MSonly_cosmic", &L2_mu4_comm_MSonly_cosmic, &b_L2_mu4_comm_MSonly_cosmic);
   fChain->SetBranchAddress("L2_mu4_comm_MSonly_firstempty", &L2_mu4_comm_MSonly_firstempty, &b_L2_mu4_comm_MSonly_firstempty);
   fChain->SetBranchAddress("L2_mu4_comm_cosmic", &L2_mu4_comm_cosmic, &b_L2_mu4_comm_cosmic);
   fChain->SetBranchAddress("L2_mu4_comm_firstempty", &L2_mu4_comm_firstempty, &b_L2_mu4_comm_firstempty);
   fChain->SetBranchAddress("L2_mu4_cosmic", &L2_mu4_cosmic, &b_L2_mu4_cosmic);
   fChain->SetBranchAddress("L2_mu4_firstempty", &L2_mu4_firstempty, &b_L2_mu4_firstempty);
   fChain->SetBranchAddress("L2_mu4_j10_matched", &L2_mu4_j10_matched, &b_L2_mu4_j10_matched);
   fChain->SetBranchAddress("L2_mu4_j20_matched", &L2_mu4_j20_matched, &b_L2_mu4_j20_matched);
   fChain->SetBranchAddress("L2_mu4_j5_matched", &L2_mu4_j5_matched, &b_L2_mu4_j5_matched);
   fChain->SetBranchAddress("L2_mu4_mu6", &L2_mu4_mu6, &b_L2_mu4_mu6);
   fChain->SetBranchAddress("L2_mu4_muCombTag", &L2_mu4_muCombTag, &b_L2_mu4_muCombTag);
   fChain->SetBranchAddress("L2_mu4_muCombTag_SiTrk", &L2_mu4_muCombTag_SiTrk, &b_L2_mu4_muCombTag_SiTrk);
   fChain->SetBranchAddress("L2_mu4_passHLT", &L2_mu4_passHLT, &b_L2_mu4_passHLT);
   fChain->SetBranchAddress("L2_mu4_tile", &L2_mu4_tile, &b_L2_mu4_tile);
   fChain->SetBranchAddress("L2_mu4_tile_SiTrk", &L2_mu4_tile_SiTrk, &b_L2_mu4_tile_SiTrk);
   fChain->SetBranchAddress("L2_mu4_trod", &L2_mu4_trod, &b_L2_mu4_trod);
   fChain->SetBranchAddress("L2_mu4_trod_SiTrk", &L2_mu4_trod_SiTrk, &b_L2_mu4_trod_SiTrk);
   //fChain->SetBranchAddress("L2_mu4_unpaired", &L2_mu4_unpaired, &b_L2_mu4_unpaired);
   fChain->SetBranchAddress("L2_mu4mu6_DiMu", &L2_mu4mu6_DiMu, &b_L2_mu4mu6_DiMu);
   fChain->SetBranchAddress("L2_mu6", &L2_mu6, &b_L2_mu6);
   fChain->SetBranchAddress("L2_mu6_DiMu", &L2_mu6_DiMu, &b_L2_mu6_DiMu);
   fChain->SetBranchAddress("L2_mu6_DiMu_FS", &L2_mu6_DiMu_FS, &b_L2_mu6_DiMu_FS);
   fChain->SetBranchAddress("L2_mu6_DiMu_FS_noOS", &L2_mu6_DiMu_FS_noOS, &b_L2_mu6_DiMu_FS_noOS);
   fChain->SetBranchAddress("L2_mu6_DsPhiPi", &L2_mu6_DsPhiPi, &b_L2_mu6_DsPhiPi);
   fChain->SetBranchAddress("L2_mu6_Jpsie5e3", &L2_mu6_Jpsie5e3, &b_L2_mu6_Jpsie5e3);
   //fChain->SetBranchAddress("L2_mu6_Jpsie5e3_FS", &L2_mu6_Jpsie5e3_FS, &b_L2_mu6_Jpsie5e3_FS);
   //fChain->SetBranchAddress("L2_mu6_Jpsie5e3_SiTrk", &L2_mu6_Jpsie5e3_SiTrk, &b_L2_mu6_Jpsie5e3_SiTrk);
   //fChain->SetBranchAddress("L2_mu6_Jpsie5e3_SiTrk_FS", &L2_mu6_Jpsie5e3_SiTrk_FS, &b_L2_mu6_Jpsie5e3_SiTrk_FS);
   fChain->SetBranchAddress("L2_mu6_MG", &L2_mu6_MG, &b_L2_mu6_MG);
   fChain->SetBranchAddress("L2_mu6_MSonly", &L2_mu6_MSonly, &b_L2_mu6_MSonly);
   fChain->SetBranchAddress("L2_mu6_MSonly_cosmic", &L2_mu6_MSonly_cosmic, &b_L2_mu6_MSonly_cosmic);
   fChain->SetBranchAddress("L2_mu6_MSonly_firstempty", &L2_mu6_MSonly_firstempty, &b_L2_mu6_MSonly_firstempty);
   fChain->SetBranchAddress("L2_mu6_MSonly_unpaired", &L2_mu6_MSonly_unpaired, &b_L2_mu6_MSonly_unpaired);
   fChain->SetBranchAddress("L2_mu6_SiTrk", &L2_mu6_SiTrk, &b_L2_mu6_SiTrk);
   fChain->SetBranchAddress("L2_mu6_Trk_Jpsi_loose", &L2_mu6_Trk_Jpsi_loose, &b_L2_mu6_Trk_Jpsi_loose);
   fChain->SetBranchAddress("L2_mu6_Trk_Jpsi_loose_FS", &L2_mu6_Trk_Jpsi_loose_FS, &b_L2_mu6_Trk_Jpsi_loose_FS);
   fChain->SetBranchAddress("L2_mu6_Trk_Upsi_loose_FS", &L2_mu6_Trk_Upsi_loose_FS, &b_L2_mu6_Trk_Upsi_loose_FS);
   fChain->SetBranchAddress("L2_mu6_cosmic", &L2_mu6_cosmic, &b_L2_mu6_cosmic);
   fChain->SetBranchAddress("L2_mu6_firstempty", &L2_mu6_firstempty, &b_L2_mu6_firstempty);
   fChain->SetBranchAddress("L2_mu6_muCombTag", &L2_mu6_muCombTag, &b_L2_mu6_muCombTag);
   fChain->SetBranchAddress("L2_mu6_muCombTag_SiTrk", &L2_mu6_muCombTag_SiTrk, &b_L2_mu6_muCombTag_SiTrk);
   fChain->SetBranchAddress("L2_mu6_passHLT", &L2_mu6_passHLT, &b_L2_mu6_passHLT);
   fChain->SetBranchAddress("L2_mu6_unpaired", &L2_mu6_unpaired, &b_L2_mu6_unpaired);
   fChain->SetBranchAddress("mu_staco_n", &mu_staco_n, &b_mu_staco_n);
   fChain->SetBranchAddress("mu_staco_E", &mu_staco_E, &b_mu_staco_E);
   fChain->SetBranchAddress("mu_staco_px", &mu_staco_px, &b_mu_staco_px);
   fChain->SetBranchAddress("mu_staco_py", &mu_staco_py, &b_mu_staco_py);
   fChain->SetBranchAddress("mu_staco_pz", &mu_staco_pz, &b_mu_staco_pz);
   fChain->SetBranchAddress("mu_staco_m", &mu_staco_m, &b_mu_staco_m);
   fChain->SetBranchAddress("mu_staco_charge", &mu_staco_charge, &b_mu_staco_charge);
   fChain->SetBranchAddress("mu_staco_pt", &mu_staco_pt, &b_mu_staco_pt);
   fChain->SetBranchAddress("mu_staco_eta", &mu_staco_eta, &b_mu_staco_eta);
   fChain->SetBranchAddress("mu_staco_phi", &mu_staco_phi, &b_mu_staco_phi);
   fChain->SetBranchAddress("mu_staco_allauthor", &mu_staco_allauthor, &b_mu_staco_allauthor);
   fChain->SetBranchAddress("mu_staco_author", &mu_staco_author, &b_mu_staco_author);
   fChain->SetBranchAddress("mu_staco_matchchi2", &mu_staco_matchchi2, &b_mu_staco_matchchi2);
   fChain->SetBranchAddress("mu_staco_matchndof", &mu_staco_matchndof, &b_mu_staco_matchndof);
   fChain->SetBranchAddress("mu_staco_etcone20", &mu_staco_etcone20, &b_mu_staco_etcone20);
   fChain->SetBranchAddress("mu_staco_etcone30", &mu_staco_etcone30, &b_mu_staco_etcone30);
   fChain->SetBranchAddress("mu_staco_etcone40", &mu_staco_etcone40, &b_mu_staco_etcone40);
   fChain->SetBranchAddress("mu_staco_nucone20", &mu_staco_nucone20, &b_mu_staco_nucone20);
   fChain->SetBranchAddress("mu_staco_nucone30", &mu_staco_nucone30, &b_mu_staco_nucone30);
   fChain->SetBranchAddress("mu_staco_nucone40", &mu_staco_nucone40, &b_mu_staco_nucone40);
   fChain->SetBranchAddress("mu_staco_ptcone20", &mu_staco_ptcone20, &b_mu_staco_ptcone20);
   fChain->SetBranchAddress("mu_staco_ptcone30", &mu_staco_ptcone30, &b_mu_staco_ptcone30);
   fChain->SetBranchAddress("mu_staco_ptcone40", &mu_staco_ptcone40, &b_mu_staco_ptcone40);
   fChain->SetBranchAddress("mu_staco_energyLossPar", &mu_staco_energyLossPar, &b_mu_staco_energyLossPar);
   fChain->SetBranchAddress("mu_staco_energyLossErr", &mu_staco_energyLossErr, &b_mu_staco_energyLossErr);
   fChain->SetBranchAddress("mu_staco_bestMatch", &mu_staco_bestMatch, &b_mu_staco_bestMatch);
   fChain->SetBranchAddress("mu_staco_isStandAloneMuon", &mu_staco_isStandAloneMuon, &b_mu_staco_isStandAloneMuon);
   fChain->SetBranchAddress("mu_staco_isCombinedMuon", &mu_staco_isCombinedMuon, &b_mu_staco_isCombinedMuon);
   fChain->SetBranchAddress("mu_staco_isLowPtReconstructedMuon", &mu_staco_isLowPtReconstructedMuon, &b_mu_staco_isLowPtReconstructedMuon);
   fChain->SetBranchAddress("mu_staco_d0_exPV", &mu_staco_d0_exPV, &b_mu_staco_d0_exPV);
   fChain->SetBranchAddress("mu_staco_z0_exPV", &mu_staco_z0_exPV, &b_mu_staco_z0_exPV);
   fChain->SetBranchAddress("mu_staco_phi_exPV", &mu_staco_phi_exPV, &b_mu_staco_phi_exPV);
   fChain->SetBranchAddress("mu_staco_theta_exPV", &mu_staco_theta_exPV, &b_mu_staco_theta_exPV);
   fChain->SetBranchAddress("mu_staco_qoverp_exPV", &mu_staco_qoverp_exPV, &b_mu_staco_qoverp_exPV);
   fChain->SetBranchAddress("mu_staco_cov_d0_exPV", &mu_staco_cov_d0_exPV, &b_mu_staco_cov_d0_exPV);
   fChain->SetBranchAddress("mu_staco_cov_z0_exPV", &mu_staco_cov_z0_exPV, &b_mu_staco_cov_z0_exPV);
   fChain->SetBranchAddress("mu_staco_cov_phi_exPV", &mu_staco_cov_phi_exPV, &b_mu_staco_cov_phi_exPV);
   fChain->SetBranchAddress("mu_staco_cov_theta_exPV", &mu_staco_cov_theta_exPV, &b_mu_staco_cov_theta_exPV);
   fChain->SetBranchAddress("mu_staco_cov_qoverp_exPV", &mu_staco_cov_qoverp_exPV, &b_mu_staco_cov_qoverp_exPV);
   fChain->SetBranchAddress("mu_staco_cov_d0_z0_exPV", &mu_staco_cov_d0_z0_exPV, &b_mu_staco_cov_d0_z0_exPV);
   fChain->SetBranchAddress("mu_staco_cov_d0_phi_exPV", &mu_staco_cov_d0_phi_exPV, &b_mu_staco_cov_d0_phi_exPV);
   fChain->SetBranchAddress("mu_staco_cov_d0_theta_exPV", &mu_staco_cov_d0_theta_exPV, &b_mu_staco_cov_d0_theta_exPV);
   fChain->SetBranchAddress("mu_staco_cov_d0_qoverp_exPV", &mu_staco_cov_d0_qoverp_exPV, &b_mu_staco_cov_d0_qoverp_exPV);
   fChain->SetBranchAddress("mu_staco_cov_z0_phi_exPV", &mu_staco_cov_z0_phi_exPV, &b_mu_staco_cov_z0_phi_exPV);
   fChain->SetBranchAddress("mu_staco_cov_z0_theta_exPV", &mu_staco_cov_z0_theta_exPV, &b_mu_staco_cov_z0_theta_exPV);
   fChain->SetBranchAddress("mu_staco_cov_z0_qoverp_exPV", &mu_staco_cov_z0_qoverp_exPV, &b_mu_staco_cov_z0_qoverp_exPV);
   fChain->SetBranchAddress("mu_staco_cov_phi_theta_exPV", &mu_staco_cov_phi_theta_exPV, &b_mu_staco_cov_phi_theta_exPV);
   fChain->SetBranchAddress("mu_staco_cov_phi_qoverp_exPV", &mu_staco_cov_phi_qoverp_exPV, &b_mu_staco_cov_phi_qoverp_exPV);
   fChain->SetBranchAddress("mu_staco_cov_theta_qoverp_exPV", &mu_staco_cov_theta_qoverp_exPV, &b_mu_staco_cov_theta_qoverp_exPV);
   fChain->SetBranchAddress("mu_staco_ms_d0", &mu_staco_ms_d0, &b_mu_staco_ms_d0);
   fChain->SetBranchAddress("mu_staco_ms_z0", &mu_staco_ms_z0, &b_mu_staco_ms_z0);
   fChain->SetBranchAddress("mu_staco_ms_phi", &mu_staco_ms_phi, &b_mu_staco_ms_phi);
   fChain->SetBranchAddress("mu_staco_ms_theta", &mu_staco_ms_theta, &b_mu_staco_ms_theta);
   fChain->SetBranchAddress("mu_staco_ms_qoverp", &mu_staco_ms_qoverp, &b_mu_staco_ms_qoverp);
   fChain->SetBranchAddress("mu_staco_id_d0", &mu_staco_id_d0, &b_mu_staco_id_d0);
   fChain->SetBranchAddress("mu_staco_id_z0", &mu_staco_id_z0, &b_mu_staco_id_z0);
   fChain->SetBranchAddress("mu_staco_id_phi", &mu_staco_id_phi, &b_mu_staco_id_phi);
   fChain->SetBranchAddress("mu_staco_id_theta", &mu_staco_id_theta, &b_mu_staco_id_theta);
   fChain->SetBranchAddress("mu_staco_id_qoverp", &mu_staco_id_qoverp, &b_mu_staco_id_qoverp);
   fChain->SetBranchAddress("mu_staco_me_d0", &mu_staco_me_d0, &b_mu_staco_me_d0);
   fChain->SetBranchAddress("mu_staco_me_z0", &mu_staco_me_z0, &b_mu_staco_me_z0);
   fChain->SetBranchAddress("mu_staco_me_phi", &mu_staco_me_phi, &b_mu_staco_me_phi);
   fChain->SetBranchAddress("mu_staco_me_theta", &mu_staco_me_theta, &b_mu_staco_me_theta);
   fChain->SetBranchAddress("mu_staco_me_qoverp", &mu_staco_me_qoverp, &b_mu_staco_me_qoverp);
   fChain->SetBranchAddress("mu_staco_ie_d0", &mu_staco_ie_d0, &b_mu_staco_ie_d0);
   fChain->SetBranchAddress("mu_staco_ie_z0", &mu_staco_ie_z0, &b_mu_staco_ie_z0);
   fChain->SetBranchAddress("mu_staco_ie_phi", &mu_staco_ie_phi, &b_mu_staco_ie_phi);
   fChain->SetBranchAddress("mu_staco_ie_theta", &mu_staco_ie_theta, &b_mu_staco_ie_theta);
   fChain->SetBranchAddress("mu_staco_ie_qoverp", &mu_staco_ie_qoverp, &b_mu_staco_ie_qoverp);
   fChain->SetBranchAddress("mu_staco_nBLHits", &mu_staco_nBLHits, &b_mu_staco_nBLHits);
   fChain->SetBranchAddress("mu_staco_nPixHits", &mu_staco_nPixHits, &b_mu_staco_nPixHits);
   fChain->SetBranchAddress("mu_staco_nSCTHits", &mu_staco_nSCTHits, &b_mu_staco_nSCTHits);
   fChain->SetBranchAddress("mu_staco_nTRTHits", &mu_staco_nTRTHits, &b_mu_staco_nTRTHits);
   fChain->SetBranchAddress("mu_staco_nTRTHighTHits", &mu_staco_nTRTHighTHits, &b_mu_staco_nTRTHighTHits);
   fChain->SetBranchAddress("mu_staco_nBLSharedHits", &mu_staco_nBLSharedHits, &b_mu_staco_nBLSharedHits);
   fChain->SetBranchAddress("mu_staco_nPixSharedHits", &mu_staco_nPixSharedHits, &b_mu_staco_nPixSharedHits);
   fChain->SetBranchAddress("mu_staco_nPixHoles", &mu_staco_nPixHoles, &b_mu_staco_nPixHoles);
   fChain->SetBranchAddress("mu_staco_nSCTSharedHits", &mu_staco_nSCTSharedHits, &b_mu_staco_nSCTSharedHits);
   fChain->SetBranchAddress("mu_staco_nSCTHoles", &mu_staco_nSCTHoles, &b_mu_staco_nSCTHoles);
   fChain->SetBranchAddress("mu_staco_nTRTOutliers", &mu_staco_nTRTOutliers, &b_mu_staco_nTRTOutliers);
   fChain->SetBranchAddress("mu_staco_nTRTHighTOutliers", &mu_staco_nTRTHighTOutliers, &b_mu_staco_nTRTHighTOutliers);
   fChain->SetBranchAddress("mu_staco_nMDTHits", &mu_staco_nMDTHits, &b_mu_staco_nMDTHits);
   fChain->SetBranchAddress("mu_staco_nMDTHoles", &mu_staco_nMDTHoles, &b_mu_staco_nMDTHoles);
   fChain->SetBranchAddress("mu_staco_nCSCEtaHits", &mu_staco_nCSCEtaHits, &b_mu_staco_nCSCEtaHits);
   fChain->SetBranchAddress("mu_staco_nCSCEtaHoles", &mu_staco_nCSCEtaHoles, &b_mu_staco_nCSCEtaHoles);
   fChain->SetBranchAddress("mu_staco_nCSCPhiHits", &mu_staco_nCSCPhiHits, &b_mu_staco_nCSCPhiHits);
   fChain->SetBranchAddress("mu_staco_nCSCPhiHoles", &mu_staco_nCSCPhiHoles, &b_mu_staco_nCSCPhiHoles);
   fChain->SetBranchAddress("mu_staco_nRPCEtaHits", &mu_staco_nRPCEtaHits, &b_mu_staco_nRPCEtaHits);
   fChain->SetBranchAddress("mu_staco_nRPCEtaHoles", &mu_staco_nRPCEtaHoles, &b_mu_staco_nRPCEtaHoles);
   fChain->SetBranchAddress("mu_staco_nRPCPhiHits", &mu_staco_nRPCPhiHits, &b_mu_staco_nRPCPhiHits);
   fChain->SetBranchAddress("mu_staco_nRPCPhiHoles", &mu_staco_nRPCPhiHoles, &b_mu_staco_nRPCPhiHoles);
   fChain->SetBranchAddress("mu_staco_nTGCEtaHits", &mu_staco_nTGCEtaHits, &b_mu_staco_nTGCEtaHits);
   fChain->SetBranchAddress("mu_staco_nTGCEtaHoles", &mu_staco_nTGCEtaHoles, &b_mu_staco_nTGCEtaHoles);
   fChain->SetBranchAddress("mu_staco_nTGCPhiHits", &mu_staco_nTGCPhiHits, &b_mu_staco_nTGCPhiHits);
   fChain->SetBranchAddress("mu_staco_nTGCPhiHoles", &mu_staco_nTGCPhiHoles, &b_mu_staco_nTGCPhiHoles);
   fChain->SetBranchAddress("mu_staco_nGangedPixels", &mu_staco_nGangedPixels, &b_mu_staco_nGangedPixels);
   fChain->SetBranchAddress("mu_staco_nOutliersOnTrack", &mu_staco_nOutliersOnTrack, &b_mu_staco_nOutliersOnTrack);
   fChain->SetBranchAddress("mu_staco_nMDTBIHits", &mu_staco_nMDTBIHits, &b_mu_staco_nMDTBIHits);
   fChain->SetBranchAddress("mu_staco_nMDTBMHits", &mu_staco_nMDTBMHits, &b_mu_staco_nMDTBMHits);
   fChain->SetBranchAddress("mu_staco_nMDTBOHits", &mu_staco_nMDTBOHits, &b_mu_staco_nMDTBOHits);
   fChain->SetBranchAddress("mu_staco_nMDTBEEHits", &mu_staco_nMDTBEEHits, &b_mu_staco_nMDTBEEHits);
   fChain->SetBranchAddress("mu_staco_nMDTBIS78Hits", &mu_staco_nMDTBIS78Hits, &b_mu_staco_nMDTBIS78Hits);
   fChain->SetBranchAddress("mu_staco_nMDTEIHits", &mu_staco_nMDTEIHits, &b_mu_staco_nMDTEIHits);
   fChain->SetBranchAddress("mu_staco_nMDTEMHits", &mu_staco_nMDTEMHits, &b_mu_staco_nMDTEMHits);
   fChain->SetBranchAddress("mu_staco_nMDTEOHits", &mu_staco_nMDTEOHits, &b_mu_staco_nMDTEOHits);
   fChain->SetBranchAddress("mu_staco_nMDTEEHits", &mu_staco_nMDTEEHits, &b_mu_staco_nMDTEEHits);
   fChain->SetBranchAddress("mu_staco_nRPCLayer1EtaHits", &mu_staco_nRPCLayer1EtaHits, &b_mu_staco_nRPCLayer1EtaHits);
   fChain->SetBranchAddress("mu_staco_nRPCLayer2EtaHits", &mu_staco_nRPCLayer2EtaHits, &b_mu_staco_nRPCLayer2EtaHits);
   fChain->SetBranchAddress("mu_staco_nRPCLayer3EtaHits", &mu_staco_nRPCLayer3EtaHits, &b_mu_staco_nRPCLayer3EtaHits);
   fChain->SetBranchAddress("mu_staco_nRPCLayer1PhiHits", &mu_staco_nRPCLayer1PhiHits, &b_mu_staco_nRPCLayer1PhiHits);
   fChain->SetBranchAddress("mu_staco_nRPCLayer2PhiHits", &mu_staco_nRPCLayer2PhiHits, &b_mu_staco_nRPCLayer2PhiHits);
   fChain->SetBranchAddress("mu_staco_nRPCLayer3PhiHits", &mu_staco_nRPCLayer3PhiHits, &b_mu_staco_nRPCLayer3PhiHits);
   fChain->SetBranchAddress("mu_staco_nTGCLayer1EtaHits", &mu_staco_nTGCLayer1EtaHits, &b_mu_staco_nTGCLayer1EtaHits);
   fChain->SetBranchAddress("mu_staco_nTGCLayer2EtaHits", &mu_staco_nTGCLayer2EtaHits, &b_mu_staco_nTGCLayer2EtaHits);
   fChain->SetBranchAddress("mu_staco_nTGCLayer3EtaHits", &mu_staco_nTGCLayer3EtaHits, &b_mu_staco_nTGCLayer3EtaHits);
   fChain->SetBranchAddress("mu_staco_nTGCLayer4EtaHits", &mu_staco_nTGCLayer4EtaHits, &b_mu_staco_nTGCLayer4EtaHits);
   fChain->SetBranchAddress("mu_staco_nTGCLayer1PhiHits", &mu_staco_nTGCLayer1PhiHits, &b_mu_staco_nTGCLayer1PhiHits);
   fChain->SetBranchAddress("mu_staco_nTGCLayer2PhiHits", &mu_staco_nTGCLayer2PhiHits, &b_mu_staco_nTGCLayer2PhiHits);
   fChain->SetBranchAddress("mu_staco_nTGCLayer3PhiHits", &mu_staco_nTGCLayer3PhiHits, &b_mu_staco_nTGCLayer3PhiHits);
   fChain->SetBranchAddress("mu_staco_nTGCLayer4PhiHits", &mu_staco_nTGCLayer4PhiHits, &b_mu_staco_nTGCLayer4PhiHits);
   fChain->SetBranchAddress("mu_staco_barrelSectors", &mu_staco_barrelSectors, &b_mu_staco_barrelSectors);
   fChain->SetBranchAddress("mu_staco_endcapSectors", &mu_staco_endcapSectors, &b_mu_staco_endcapSectors);
   fChain->SetBranchAddress("mu_staco_trackd0", &mu_staco_trackd0, &b_mu_staco_trackd0);
   fChain->SetBranchAddress("mu_staco_trackz0", &mu_staco_trackz0, &b_mu_staco_trackz0);
   fChain->SetBranchAddress("mu_staco_trackphi", &mu_staco_trackphi, &b_mu_staco_trackphi);
   fChain->SetBranchAddress("mu_staco_tracktheta", &mu_staco_tracktheta, &b_mu_staco_tracktheta);
   fChain->SetBranchAddress("mu_staco_trackqoverp", &mu_staco_trackqoverp, &b_mu_staco_trackqoverp);
   fChain->SetBranchAddress("mu_staco_trackcov_d0", &mu_staco_trackcov_d0, &b_mu_staco_trackcov_d0);
   fChain->SetBranchAddress("mu_staco_trackcov_z0", &mu_staco_trackcov_z0, &b_mu_staco_trackcov_z0);
   fChain->SetBranchAddress("mu_staco_trackcov_phi", &mu_staco_trackcov_phi, &b_mu_staco_trackcov_phi);
   fChain->SetBranchAddress("mu_staco_trackcov_theta", &mu_staco_trackcov_theta, &b_mu_staco_trackcov_theta);
   fChain->SetBranchAddress("mu_staco_trackcov_qoverp", &mu_staco_trackcov_qoverp, &b_mu_staco_trackcov_qoverp);
   fChain->SetBranchAddress("mu_staco_trackcov_d0_z0", &mu_staco_trackcov_d0_z0, &b_mu_staco_trackcov_d0_z0);
   fChain->SetBranchAddress("mu_staco_trackcov_d0_phi", &mu_staco_trackcov_d0_phi, &b_mu_staco_trackcov_d0_phi);
   fChain->SetBranchAddress("mu_staco_trackcov_d0_theta", &mu_staco_trackcov_d0_theta, &b_mu_staco_trackcov_d0_theta);
   fChain->SetBranchAddress("mu_staco_trackcov_d0_qoverp", &mu_staco_trackcov_d0_qoverp, &b_mu_staco_trackcov_d0_qoverp);
   fChain->SetBranchAddress("mu_staco_trackcov_z0_phi", &mu_staco_trackcov_z0_phi, &b_mu_staco_trackcov_z0_phi);
   fChain->SetBranchAddress("mu_staco_trackcov_z0_theta", &mu_staco_trackcov_z0_theta, &b_mu_staco_trackcov_z0_theta);
   fChain->SetBranchAddress("mu_staco_trackcov_z0_qoverp", &mu_staco_trackcov_z0_qoverp, &b_mu_staco_trackcov_z0_qoverp);
   fChain->SetBranchAddress("mu_staco_trackcov_phi_theta", &mu_staco_trackcov_phi_theta, &b_mu_staco_trackcov_phi_theta);
   fChain->SetBranchAddress("mu_staco_trackcov_phi_qoverp", &mu_staco_trackcov_phi_qoverp, &b_mu_staco_trackcov_phi_qoverp);
   fChain->SetBranchAddress("mu_staco_trackcov_theta_qoverp", &mu_staco_trackcov_theta_qoverp, &b_mu_staco_trackcov_theta_qoverp);
   fChain->SetBranchAddress("mu_staco_trackfitchi2", &mu_staco_trackfitchi2, &b_mu_staco_trackfitchi2);
   fChain->SetBranchAddress("mu_staco_trackfitndof", &mu_staco_trackfitndof, &b_mu_staco_trackfitndof);
   fChain->SetBranchAddress("mu_staco_hastrack", &mu_staco_hastrack, &b_mu_staco_hastrack);
   fChain->SetBranchAddress("mu_staco_EF_dr", &mu_staco_EF_dr, &b_mu_staco_EF_dr);
   fChain->SetBranchAddress("mu_staco_EF_cb_eta", &mu_staco_EF_cb_eta, &b_mu_staco_EF_cb_eta);
   fChain->SetBranchAddress("mu_staco_EF_cb_phi", &mu_staco_EF_cb_phi, &b_mu_staco_EF_cb_phi);
   fChain->SetBranchAddress("mu_staco_EF_cb_pt", &mu_staco_EF_cb_pt, &b_mu_staco_EF_cb_pt);
   fChain->SetBranchAddress("mu_staco_EF_ms_eta", &mu_staco_EF_ms_eta, &b_mu_staco_EF_ms_eta);
   fChain->SetBranchAddress("mu_staco_EF_ms_phi", &mu_staco_EF_ms_phi, &b_mu_staco_EF_ms_phi);
   fChain->SetBranchAddress("mu_staco_EF_ms_pt", &mu_staco_EF_ms_pt, &b_mu_staco_EF_ms_pt);
   fChain->SetBranchAddress("mu_staco_EF_me_eta", &mu_staco_EF_me_eta, &b_mu_staco_EF_me_eta);
   fChain->SetBranchAddress("mu_staco_EF_me_phi", &mu_staco_EF_me_phi, &b_mu_staco_EF_me_phi);
   fChain->SetBranchAddress("mu_staco_EF_me_pt", &mu_staco_EF_me_pt, &b_mu_staco_EF_me_pt);
   fChain->SetBranchAddress("mu_staco_EF_matched", &mu_staco_EF_matched, &b_mu_staco_EF_matched);
   fChain->SetBranchAddress("mu_staco_L2CB_dr", &mu_staco_L2CB_dr, &b_mu_staco_L2CB_dr);
   fChain->SetBranchAddress("mu_staco_L2CB_pt", &mu_staco_L2CB_pt, &b_mu_staco_L2CB_pt);
   fChain->SetBranchAddress("mu_staco_L2CB_eta", &mu_staco_L2CB_eta, &b_mu_staco_L2CB_eta);
   fChain->SetBranchAddress("mu_staco_L2CB_phi", &mu_staco_L2CB_phi, &b_mu_staco_L2CB_phi);
   fChain->SetBranchAddress("mu_staco_L2CB_id_pt", &mu_staco_L2CB_id_pt, &b_mu_staco_L2CB_id_pt);
   fChain->SetBranchAddress("mu_staco_L2CB_ms_pt", &mu_staco_L2CB_ms_pt, &b_mu_staco_L2CB_ms_pt);
   fChain->SetBranchAddress("mu_staco_L2CB_nPixHits", &mu_staco_L2CB_nPixHits, &b_mu_staco_L2CB_nPixHits);
   fChain->SetBranchAddress("mu_staco_L2CB_nSCTHits", &mu_staco_L2CB_nSCTHits, &b_mu_staco_L2CB_nSCTHits);
   fChain->SetBranchAddress("mu_staco_L2CB_nTRTHits", &mu_staco_L2CB_nTRTHits, &b_mu_staco_L2CB_nTRTHits);
   fChain->SetBranchAddress("mu_staco_L2CB_nTRTHighTHits", &mu_staco_L2CB_nTRTHighTHits, &b_mu_staco_L2CB_nTRTHighTHits);
   fChain->SetBranchAddress("mu_staco_L2CB_matched", &mu_staco_L2CB_matched, &b_mu_staco_L2CB_matched);
   fChain->SetBranchAddress("mu_staco_L1_dr", &mu_staco_L1_dr, &b_mu_staco_L1_dr);
   fChain->SetBranchAddress("mu_staco_L1_pt", &mu_staco_L1_pt, &b_mu_staco_L1_pt);
   fChain->SetBranchAddress("mu_staco_L1_eta", &mu_staco_L1_eta, &b_mu_staco_L1_eta);
   fChain->SetBranchAddress("mu_staco_L1_phi", &mu_staco_L1_phi, &b_mu_staco_L1_phi);
   fChain->SetBranchAddress("mu_staco_L1_thrNumber", &mu_staco_L1_thrNumber, &b_mu_staco_L1_thrNumber);
   fChain->SetBranchAddress("mu_staco_L1_RoINumber", &mu_staco_L1_RoINumber, &b_mu_staco_L1_RoINumber);
   fChain->SetBranchAddress("mu_staco_L1_sectorAddress", &mu_staco_L1_sectorAddress, &b_mu_staco_L1_sectorAddress);
   fChain->SetBranchAddress("mu_staco_L1_firstCandidate", &mu_staco_L1_firstCandidate, &b_mu_staco_L1_firstCandidate);
   fChain->SetBranchAddress("mu_staco_L1_moreCandInRoI", &mu_staco_L1_moreCandInRoI, &b_mu_staco_L1_moreCandInRoI);
   fChain->SetBranchAddress("mu_staco_L1_moreCandInSector", &mu_staco_L1_moreCandInSector, &b_mu_staco_L1_moreCandInSector);
   fChain->SetBranchAddress("mu_staco_L1_source", &mu_staco_L1_source, &b_mu_staco_L1_source);
   fChain->SetBranchAddress("mu_staco_L1_hemisphere", &mu_staco_L1_hemisphere, &b_mu_staco_L1_hemisphere);
   fChain->SetBranchAddress("mu_staco_L1_matched", &mu_staco_L1_matched, &b_mu_staco_L1_matched);
   fChain->SetBranchAddress("mu_muid_n", &mu_muid_n, &b_mu_muid_n);
   fChain->SetBranchAddress("mu_muid_E", &mu_muid_E, &b_mu_muid_E);
   fChain->SetBranchAddress("mu_muid_px", &mu_muid_px, &b_mu_muid_px);
   fChain->SetBranchAddress("mu_muid_py", &mu_muid_py, &b_mu_muid_py);
   fChain->SetBranchAddress("mu_muid_pz", &mu_muid_pz, &b_mu_muid_pz);
   fChain->SetBranchAddress("mu_muid_m", &mu_muid_m, &b_mu_muid_m);
   fChain->SetBranchAddress("mu_muid_charge", &mu_muid_charge, &b_mu_muid_charge);
   fChain->SetBranchAddress("mu_muid_pt", &mu_muid_pt, &b_mu_muid_pt);
   fChain->SetBranchAddress("mu_muid_eta", &mu_muid_eta, &b_mu_muid_eta);
   fChain->SetBranchAddress("mu_muid_phi", &mu_muid_phi, &b_mu_muid_phi);
   fChain->SetBranchAddress("mu_muid_allauthor", &mu_muid_allauthor, &b_mu_muid_allauthor);
   fChain->SetBranchAddress("mu_muid_author", &mu_muid_author, &b_mu_muid_author);
   fChain->SetBranchAddress("mu_muid_matchchi2", &mu_muid_matchchi2, &b_mu_muid_matchchi2);
   fChain->SetBranchAddress("mu_muid_matchndof", &mu_muid_matchndof, &b_mu_muid_matchndof);
   fChain->SetBranchAddress("mu_muid_etcone20", &mu_muid_etcone20, &b_mu_muid_etcone20);
   fChain->SetBranchAddress("mu_muid_etcone30", &mu_muid_etcone30, &b_mu_muid_etcone30);
   fChain->SetBranchAddress("mu_muid_etcone40", &mu_muid_etcone40, &b_mu_muid_etcone40);
   fChain->SetBranchAddress("mu_muid_nucone20", &mu_muid_nucone20, &b_mu_muid_nucone20);
   fChain->SetBranchAddress("mu_muid_nucone30", &mu_muid_nucone30, &b_mu_muid_nucone30);
   fChain->SetBranchAddress("mu_muid_nucone40", &mu_muid_nucone40, &b_mu_muid_nucone40);
   fChain->SetBranchAddress("mu_muid_ptcone20", &mu_muid_ptcone20, &b_mu_muid_ptcone20);
   fChain->SetBranchAddress("mu_muid_ptcone30", &mu_muid_ptcone30, &b_mu_muid_ptcone30);
   fChain->SetBranchAddress("mu_muid_ptcone40", &mu_muid_ptcone40, &b_mu_muid_ptcone40);
   fChain->SetBranchAddress("mu_muid_energyLossPar", &mu_muid_energyLossPar, &b_mu_muid_energyLossPar);
   fChain->SetBranchAddress("mu_muid_energyLossErr", &mu_muid_energyLossErr, &b_mu_muid_energyLossErr);
   fChain->SetBranchAddress("mu_muid_bestMatch", &mu_muid_bestMatch, &b_mu_muid_bestMatch);
   fChain->SetBranchAddress("mu_muid_isStandAloneMuon", &mu_muid_isStandAloneMuon, &b_mu_muid_isStandAloneMuon);
   fChain->SetBranchAddress("mu_muid_isCombinedMuon", &mu_muid_isCombinedMuon, &b_mu_muid_isCombinedMuon);
   fChain->SetBranchAddress("mu_muid_isLowPtReconstructedMuon", &mu_muid_isLowPtReconstructedMuon, &b_mu_muid_isLowPtReconstructedMuon);
   fChain->SetBranchAddress("mu_muid_d0_exPV", &mu_muid_d0_exPV, &b_mu_muid_d0_exPV);
   fChain->SetBranchAddress("mu_muid_z0_exPV", &mu_muid_z0_exPV, &b_mu_muid_z0_exPV);
   fChain->SetBranchAddress("mu_muid_phi_exPV", &mu_muid_phi_exPV, &b_mu_muid_phi_exPV);
   fChain->SetBranchAddress("mu_muid_theta_exPV", &mu_muid_theta_exPV, &b_mu_muid_theta_exPV);
   fChain->SetBranchAddress("mu_muid_qoverp_exPV", &mu_muid_qoverp_exPV, &b_mu_muid_qoverp_exPV);
   fChain->SetBranchAddress("mu_muid_cov_d0_exPV", &mu_muid_cov_d0_exPV, &b_mu_muid_cov_d0_exPV);
   fChain->SetBranchAddress("mu_muid_cov_z0_exPV", &mu_muid_cov_z0_exPV, &b_mu_muid_cov_z0_exPV);
   fChain->SetBranchAddress("mu_muid_cov_phi_exPV", &mu_muid_cov_phi_exPV, &b_mu_muid_cov_phi_exPV);
   fChain->SetBranchAddress("mu_muid_cov_theta_exPV", &mu_muid_cov_theta_exPV, &b_mu_muid_cov_theta_exPV);
   fChain->SetBranchAddress("mu_muid_cov_qoverp_exPV", &mu_muid_cov_qoverp_exPV, &b_mu_muid_cov_qoverp_exPV);
   fChain->SetBranchAddress("mu_muid_cov_d0_z0_exPV", &mu_muid_cov_d0_z0_exPV, &b_mu_muid_cov_d0_z0_exPV);
   fChain->SetBranchAddress("mu_muid_cov_d0_phi_exPV", &mu_muid_cov_d0_phi_exPV, &b_mu_muid_cov_d0_phi_exPV);
   fChain->SetBranchAddress("mu_muid_cov_d0_theta_exPV", &mu_muid_cov_d0_theta_exPV, &b_mu_muid_cov_d0_theta_exPV);
   fChain->SetBranchAddress("mu_muid_cov_d0_qoverp_exPV", &mu_muid_cov_d0_qoverp_exPV, &b_mu_muid_cov_d0_qoverp_exPV);
   fChain->SetBranchAddress("mu_muid_cov_z0_phi_exPV", &mu_muid_cov_z0_phi_exPV, &b_mu_muid_cov_z0_phi_exPV);
   fChain->SetBranchAddress("mu_muid_cov_z0_theta_exPV", &mu_muid_cov_z0_theta_exPV, &b_mu_muid_cov_z0_theta_exPV);
   fChain->SetBranchAddress("mu_muid_cov_z0_qoverp_exPV", &mu_muid_cov_z0_qoverp_exPV, &b_mu_muid_cov_z0_qoverp_exPV);
   fChain->SetBranchAddress("mu_muid_cov_phi_theta_exPV", &mu_muid_cov_phi_theta_exPV, &b_mu_muid_cov_phi_theta_exPV);
   fChain->SetBranchAddress("mu_muid_cov_phi_qoverp_exPV", &mu_muid_cov_phi_qoverp_exPV, &b_mu_muid_cov_phi_qoverp_exPV);
   fChain->SetBranchAddress("mu_muid_cov_theta_qoverp_exPV", &mu_muid_cov_theta_qoverp_exPV, &b_mu_muid_cov_theta_qoverp_exPV);
   fChain->SetBranchAddress("mu_muid_ms_d0", &mu_muid_ms_d0, &b_mu_muid_ms_d0);
   fChain->SetBranchAddress("mu_muid_ms_z0", &mu_muid_ms_z0, &b_mu_muid_ms_z0);
   fChain->SetBranchAddress("mu_muid_ms_phi", &mu_muid_ms_phi, &b_mu_muid_ms_phi);
   fChain->SetBranchAddress("mu_muid_ms_theta", &mu_muid_ms_theta, &b_mu_muid_ms_theta);
   fChain->SetBranchAddress("mu_muid_ms_qoverp", &mu_muid_ms_qoverp, &b_mu_muid_ms_qoverp);
   fChain->SetBranchAddress("mu_muid_id_d0", &mu_muid_id_d0, &b_mu_muid_id_d0);
   fChain->SetBranchAddress("mu_muid_id_z0", &mu_muid_id_z0, &b_mu_muid_id_z0);
   fChain->SetBranchAddress("mu_muid_id_phi", &mu_muid_id_phi, &b_mu_muid_id_phi);
   fChain->SetBranchAddress("mu_muid_id_theta", &mu_muid_id_theta, &b_mu_muid_id_theta);
   fChain->SetBranchAddress("mu_muid_id_qoverp", &mu_muid_id_qoverp, &b_mu_muid_id_qoverp);
   fChain->SetBranchAddress("mu_muid_me_d0", &mu_muid_me_d0, &b_mu_muid_me_d0);
   fChain->SetBranchAddress("mu_muid_me_z0", &mu_muid_me_z0, &b_mu_muid_me_z0);
   fChain->SetBranchAddress("mu_muid_me_phi", &mu_muid_me_phi, &b_mu_muid_me_phi);
   fChain->SetBranchAddress("mu_muid_me_theta", &mu_muid_me_theta, &b_mu_muid_me_theta);
   fChain->SetBranchAddress("mu_muid_me_qoverp", &mu_muid_me_qoverp, &b_mu_muid_me_qoverp);
   fChain->SetBranchAddress("mu_muid_ie_d0", &mu_muid_ie_d0, &b_mu_muid_ie_d0);
   fChain->SetBranchAddress("mu_muid_ie_z0", &mu_muid_ie_z0, &b_mu_muid_ie_z0);
   fChain->SetBranchAddress("mu_muid_ie_phi", &mu_muid_ie_phi, &b_mu_muid_ie_phi);
   fChain->SetBranchAddress("mu_muid_ie_theta", &mu_muid_ie_theta, &b_mu_muid_ie_theta);
   fChain->SetBranchAddress("mu_muid_ie_qoverp", &mu_muid_ie_qoverp, &b_mu_muid_ie_qoverp);
   fChain->SetBranchAddress("mu_muid_nBLHits", &mu_muid_nBLHits, &b_mu_muid_nBLHits);
   fChain->SetBranchAddress("mu_muid_nPixHits", &mu_muid_nPixHits, &b_mu_muid_nPixHits);
   fChain->SetBranchAddress("mu_muid_nSCTHits", &mu_muid_nSCTHits, &b_mu_muid_nSCTHits);
   fChain->SetBranchAddress("mu_muid_nTRTHits", &mu_muid_nTRTHits, &b_mu_muid_nTRTHits);
   fChain->SetBranchAddress("mu_muid_nTRTHighTHits", &mu_muid_nTRTHighTHits, &b_mu_muid_nTRTHighTHits);
   fChain->SetBranchAddress("mu_muid_nBLSharedHits", &mu_muid_nBLSharedHits, &b_mu_muid_nBLSharedHits);
   fChain->SetBranchAddress("mu_muid_nPixSharedHits", &mu_muid_nPixSharedHits, &b_mu_muid_nPixSharedHits);
   fChain->SetBranchAddress("mu_muid_nPixHoles", &mu_muid_nPixHoles, &b_mu_muid_nPixHoles);
   fChain->SetBranchAddress("mu_muid_nSCTSharedHits", &mu_muid_nSCTSharedHits, &b_mu_muid_nSCTSharedHits);
   fChain->SetBranchAddress("mu_muid_nSCTHoles", &mu_muid_nSCTHoles, &b_mu_muid_nSCTHoles);
   fChain->SetBranchAddress("mu_muid_nTRTOutliers", &mu_muid_nTRTOutliers, &b_mu_muid_nTRTOutliers);
   fChain->SetBranchAddress("mu_muid_nTRTHighTOutliers", &mu_muid_nTRTHighTOutliers, &b_mu_muid_nTRTHighTOutliers);
   fChain->SetBranchAddress("mu_muid_nMDTHits", &mu_muid_nMDTHits, &b_mu_muid_nMDTHits);
   fChain->SetBranchAddress("mu_muid_nMDTHoles", &mu_muid_nMDTHoles, &b_mu_muid_nMDTHoles);
   fChain->SetBranchAddress("mu_muid_nCSCEtaHits", &mu_muid_nCSCEtaHits, &b_mu_muid_nCSCEtaHits);
   fChain->SetBranchAddress("mu_muid_nCSCEtaHoles", &mu_muid_nCSCEtaHoles, &b_mu_muid_nCSCEtaHoles);
   fChain->SetBranchAddress("mu_muid_nCSCPhiHits", &mu_muid_nCSCPhiHits, &b_mu_muid_nCSCPhiHits);
   fChain->SetBranchAddress("mu_muid_nCSCPhiHoles", &mu_muid_nCSCPhiHoles, &b_mu_muid_nCSCPhiHoles);
   fChain->SetBranchAddress("mu_muid_nRPCEtaHits", &mu_muid_nRPCEtaHits, &b_mu_muid_nRPCEtaHits);
   fChain->SetBranchAddress("mu_muid_nRPCEtaHoles", &mu_muid_nRPCEtaHoles, &b_mu_muid_nRPCEtaHoles);
   fChain->SetBranchAddress("mu_muid_nRPCPhiHits", &mu_muid_nRPCPhiHits, &b_mu_muid_nRPCPhiHits);
   fChain->SetBranchAddress("mu_muid_nRPCPhiHoles", &mu_muid_nRPCPhiHoles, &b_mu_muid_nRPCPhiHoles);
   fChain->SetBranchAddress("mu_muid_nTGCEtaHits", &mu_muid_nTGCEtaHits, &b_mu_muid_nTGCEtaHits);
   fChain->SetBranchAddress("mu_muid_nTGCEtaHoles", &mu_muid_nTGCEtaHoles, &b_mu_muid_nTGCEtaHoles);
   fChain->SetBranchAddress("mu_muid_nTGCPhiHits", &mu_muid_nTGCPhiHits, &b_mu_muid_nTGCPhiHits);
   fChain->SetBranchAddress("mu_muid_nTGCPhiHoles", &mu_muid_nTGCPhiHoles, &b_mu_muid_nTGCPhiHoles);
   fChain->SetBranchAddress("mu_muid_nGangedPixels", &mu_muid_nGangedPixels, &b_mu_muid_nGangedPixels);
   fChain->SetBranchAddress("mu_muid_nOutliersOnTrack", &mu_muid_nOutliersOnTrack, &b_mu_muid_nOutliersOnTrack);
   fChain->SetBranchAddress("mu_muid_nMDTBIHits", &mu_muid_nMDTBIHits, &b_mu_muid_nMDTBIHits);
   fChain->SetBranchAddress("mu_muid_nMDTBMHits", &mu_muid_nMDTBMHits, &b_mu_muid_nMDTBMHits);
   fChain->SetBranchAddress("mu_muid_nMDTBOHits", &mu_muid_nMDTBOHits, &b_mu_muid_nMDTBOHits);
   fChain->SetBranchAddress("mu_muid_nMDTBEEHits", &mu_muid_nMDTBEEHits, &b_mu_muid_nMDTBEEHits);
   fChain->SetBranchAddress("mu_muid_nMDTBIS78Hits", &mu_muid_nMDTBIS78Hits, &b_mu_muid_nMDTBIS78Hits);
   fChain->SetBranchAddress("mu_muid_nMDTEIHits", &mu_muid_nMDTEIHits, &b_mu_muid_nMDTEIHits);
   fChain->SetBranchAddress("mu_muid_nMDTEMHits", &mu_muid_nMDTEMHits, &b_mu_muid_nMDTEMHits);
   fChain->SetBranchAddress("mu_muid_nMDTEOHits", &mu_muid_nMDTEOHits, &b_mu_muid_nMDTEOHits);
   fChain->SetBranchAddress("mu_muid_nMDTEEHits", &mu_muid_nMDTEEHits, &b_mu_muid_nMDTEEHits);
   fChain->SetBranchAddress("mu_muid_nRPCLayer1EtaHits", &mu_muid_nRPCLayer1EtaHits, &b_mu_muid_nRPCLayer1EtaHits);
   fChain->SetBranchAddress("mu_muid_nRPCLayer2EtaHits", &mu_muid_nRPCLayer2EtaHits, &b_mu_muid_nRPCLayer2EtaHits);
   fChain->SetBranchAddress("mu_muid_nRPCLayer3EtaHits", &mu_muid_nRPCLayer3EtaHits, &b_mu_muid_nRPCLayer3EtaHits);
   fChain->SetBranchAddress("mu_muid_nRPCLayer1PhiHits", &mu_muid_nRPCLayer1PhiHits, &b_mu_muid_nRPCLayer1PhiHits);
   fChain->SetBranchAddress("mu_muid_nRPCLayer2PhiHits", &mu_muid_nRPCLayer2PhiHits, &b_mu_muid_nRPCLayer2PhiHits);
   fChain->SetBranchAddress("mu_muid_nRPCLayer3PhiHits", &mu_muid_nRPCLayer3PhiHits, &b_mu_muid_nRPCLayer3PhiHits);
   fChain->SetBranchAddress("mu_muid_nTGCLayer1EtaHits", &mu_muid_nTGCLayer1EtaHits, &b_mu_muid_nTGCLayer1EtaHits);
   fChain->SetBranchAddress("mu_muid_nTGCLayer2EtaHits", &mu_muid_nTGCLayer2EtaHits, &b_mu_muid_nTGCLayer2EtaHits);
   fChain->SetBranchAddress("mu_muid_nTGCLayer3EtaHits", &mu_muid_nTGCLayer3EtaHits, &b_mu_muid_nTGCLayer3EtaHits);
   fChain->SetBranchAddress("mu_muid_nTGCLayer4EtaHits", &mu_muid_nTGCLayer4EtaHits, &b_mu_muid_nTGCLayer4EtaHits);
   fChain->SetBranchAddress("mu_muid_nTGCLayer1PhiHits", &mu_muid_nTGCLayer1PhiHits, &b_mu_muid_nTGCLayer1PhiHits);
   fChain->SetBranchAddress("mu_muid_nTGCLayer2PhiHits", &mu_muid_nTGCLayer2PhiHits, &b_mu_muid_nTGCLayer2PhiHits);
   fChain->SetBranchAddress("mu_muid_nTGCLayer3PhiHits", &mu_muid_nTGCLayer3PhiHits, &b_mu_muid_nTGCLayer3PhiHits);
   fChain->SetBranchAddress("mu_muid_nTGCLayer4PhiHits", &mu_muid_nTGCLayer4PhiHits, &b_mu_muid_nTGCLayer4PhiHits);
   fChain->SetBranchAddress("mu_muid_barrelSectors", &mu_muid_barrelSectors, &b_mu_muid_barrelSectors);
   fChain->SetBranchAddress("mu_muid_endcapSectors", &mu_muid_endcapSectors, &b_mu_muid_endcapSectors);
   fChain->SetBranchAddress("mu_muid_trackd0", &mu_muid_trackd0, &b_mu_muid_trackd0);
   fChain->SetBranchAddress("mu_muid_trackz0", &mu_muid_trackz0, &b_mu_muid_trackz0);
   fChain->SetBranchAddress("mu_muid_trackphi", &mu_muid_trackphi, &b_mu_muid_trackphi);
   fChain->SetBranchAddress("mu_muid_tracktheta", &mu_muid_tracktheta, &b_mu_muid_tracktheta);
   fChain->SetBranchAddress("mu_muid_trackqoverp", &mu_muid_trackqoverp, &b_mu_muid_trackqoverp);
   fChain->SetBranchAddress("mu_muid_trackcov_d0", &mu_muid_trackcov_d0, &b_mu_muid_trackcov_d0);
   fChain->SetBranchAddress("mu_muid_trackcov_z0", &mu_muid_trackcov_z0, &b_mu_muid_trackcov_z0);
   fChain->SetBranchAddress("mu_muid_trackcov_phi", &mu_muid_trackcov_phi, &b_mu_muid_trackcov_phi);
   fChain->SetBranchAddress("mu_muid_trackcov_theta", &mu_muid_trackcov_theta, &b_mu_muid_trackcov_theta);
   fChain->SetBranchAddress("mu_muid_trackcov_qoverp", &mu_muid_trackcov_qoverp, &b_mu_muid_trackcov_qoverp);
   fChain->SetBranchAddress("mu_muid_trackcov_d0_z0", &mu_muid_trackcov_d0_z0, &b_mu_muid_trackcov_d0_z0);
   fChain->SetBranchAddress("mu_muid_trackcov_d0_phi", &mu_muid_trackcov_d0_phi, &b_mu_muid_trackcov_d0_phi);
   fChain->SetBranchAddress("mu_muid_trackcov_d0_theta", &mu_muid_trackcov_d0_theta, &b_mu_muid_trackcov_d0_theta);
   fChain->SetBranchAddress("mu_muid_trackcov_d0_qoverp", &mu_muid_trackcov_d0_qoverp, &b_mu_muid_trackcov_d0_qoverp);
   fChain->SetBranchAddress("mu_muid_trackcov_z0_phi", &mu_muid_trackcov_z0_phi, &b_mu_muid_trackcov_z0_phi);
   fChain->SetBranchAddress("mu_muid_trackcov_z0_theta", &mu_muid_trackcov_z0_theta, &b_mu_muid_trackcov_z0_theta);
   fChain->SetBranchAddress("mu_muid_trackcov_z0_qoverp", &mu_muid_trackcov_z0_qoverp, &b_mu_muid_trackcov_z0_qoverp);
   fChain->SetBranchAddress("mu_muid_trackcov_phi_theta", &mu_muid_trackcov_phi_theta, &b_mu_muid_trackcov_phi_theta);
   fChain->SetBranchAddress("mu_muid_trackcov_phi_qoverp", &mu_muid_trackcov_phi_qoverp, &b_mu_muid_trackcov_phi_qoverp);
   fChain->SetBranchAddress("mu_muid_trackcov_theta_qoverp", &mu_muid_trackcov_theta_qoverp, &b_mu_muid_trackcov_theta_qoverp);
   fChain->SetBranchAddress("mu_muid_trackfitchi2", &mu_muid_trackfitchi2, &b_mu_muid_trackfitchi2);
   fChain->SetBranchAddress("mu_muid_trackfitndof", &mu_muid_trackfitndof, &b_mu_muid_trackfitndof);
   fChain->SetBranchAddress("mu_muid_hastrack", &mu_muid_hastrack, &b_mu_muid_hastrack);
   fChain->SetBranchAddress("mu_muid_EF_dr", &mu_muid_EF_dr, &b_mu_muid_EF_dr);
   fChain->SetBranchAddress("mu_muid_EF_cb_eta", &mu_muid_EF_cb_eta, &b_mu_muid_EF_cb_eta);
   fChain->SetBranchAddress("mu_muid_EF_cb_phi", &mu_muid_EF_cb_phi, &b_mu_muid_EF_cb_phi);
   fChain->SetBranchAddress("mu_muid_EF_cb_pt", &mu_muid_EF_cb_pt, &b_mu_muid_EF_cb_pt);
   fChain->SetBranchAddress("mu_muid_EF_ms_eta", &mu_muid_EF_ms_eta, &b_mu_muid_EF_ms_eta);
   fChain->SetBranchAddress("mu_muid_EF_ms_phi", &mu_muid_EF_ms_phi, &b_mu_muid_EF_ms_phi);
   fChain->SetBranchAddress("mu_muid_EF_ms_pt", &mu_muid_EF_ms_pt, &b_mu_muid_EF_ms_pt);
   fChain->SetBranchAddress("mu_muid_EF_me_eta", &mu_muid_EF_me_eta, &b_mu_muid_EF_me_eta);
   fChain->SetBranchAddress("mu_muid_EF_me_phi", &mu_muid_EF_me_phi, &b_mu_muid_EF_me_phi);
   fChain->SetBranchAddress("mu_muid_EF_me_pt", &mu_muid_EF_me_pt, &b_mu_muid_EF_me_pt);
   fChain->SetBranchAddress("mu_muid_EF_matched", &mu_muid_EF_matched, &b_mu_muid_EF_matched);
   fChain->SetBranchAddress("mu_muid_L2CB_dr", &mu_muid_L2CB_dr, &b_mu_muid_L2CB_dr);
   fChain->SetBranchAddress("mu_muid_L2CB_pt", &mu_muid_L2CB_pt, &b_mu_muid_L2CB_pt);
   fChain->SetBranchAddress("mu_muid_L2CB_eta", &mu_muid_L2CB_eta, &b_mu_muid_L2CB_eta);
   fChain->SetBranchAddress("mu_muid_L2CB_phi", &mu_muid_L2CB_phi, &b_mu_muid_L2CB_phi);
   fChain->SetBranchAddress("mu_muid_L2CB_id_pt", &mu_muid_L2CB_id_pt, &b_mu_muid_L2CB_id_pt);
   fChain->SetBranchAddress("mu_muid_L2CB_ms_pt", &mu_muid_L2CB_ms_pt, &b_mu_muid_L2CB_ms_pt);
   fChain->SetBranchAddress("mu_muid_L2CB_nPixHits", &mu_muid_L2CB_nPixHits, &b_mu_muid_L2CB_nPixHits);
   fChain->SetBranchAddress("mu_muid_L2CB_nSCTHits", &mu_muid_L2CB_nSCTHits, &b_mu_muid_L2CB_nSCTHits);
   fChain->SetBranchAddress("mu_muid_L2CB_nTRTHits", &mu_muid_L2CB_nTRTHits, &b_mu_muid_L2CB_nTRTHits);
   fChain->SetBranchAddress("mu_muid_L2CB_nTRTHighTHits", &mu_muid_L2CB_nTRTHighTHits, &b_mu_muid_L2CB_nTRTHighTHits);
   fChain->SetBranchAddress("mu_muid_L2CB_matched", &mu_muid_L2CB_matched, &b_mu_muid_L2CB_matched);
   fChain->SetBranchAddress("mu_muid_L1_dr", &mu_muid_L1_dr, &b_mu_muid_L1_dr);
   fChain->SetBranchAddress("mu_muid_L1_pt", &mu_muid_L1_pt, &b_mu_muid_L1_pt);
   fChain->SetBranchAddress("mu_muid_L1_eta", &mu_muid_L1_eta, &b_mu_muid_L1_eta);
   fChain->SetBranchAddress("mu_muid_L1_phi", &mu_muid_L1_phi, &b_mu_muid_L1_phi);
   fChain->SetBranchAddress("mu_muid_L1_thrNumber", &mu_muid_L1_thrNumber, &b_mu_muid_L1_thrNumber);
   fChain->SetBranchAddress("mu_muid_L1_RoINumber", &mu_muid_L1_RoINumber, &b_mu_muid_L1_RoINumber);
   fChain->SetBranchAddress("mu_muid_L1_sectorAddress", &mu_muid_L1_sectorAddress, &b_mu_muid_L1_sectorAddress);
   fChain->SetBranchAddress("mu_muid_L1_firstCandidate", &mu_muid_L1_firstCandidate, &b_mu_muid_L1_firstCandidate);
   fChain->SetBranchAddress("mu_muid_L1_moreCandInRoI", &mu_muid_L1_moreCandInRoI, &b_mu_muid_L1_moreCandInRoI);
   fChain->SetBranchAddress("mu_muid_L1_moreCandInSector", &mu_muid_L1_moreCandInSector, &b_mu_muid_L1_moreCandInSector);
   fChain->SetBranchAddress("mu_muid_L1_source", &mu_muid_L1_source, &b_mu_muid_L1_source);
   fChain->SetBranchAddress("mu_muid_L1_hemisphere", &mu_muid_L1_hemisphere, &b_mu_muid_L1_hemisphere);
   fChain->SetBranchAddress("mu_muid_L1_matched", &mu_muid_L1_matched, &b_mu_muid_L1_matched);
   Notify();
}

Bool_t offlinePhysics::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void offlinePhysics::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t offlinePhysics::Cut(Long64_t entry)
{
   if(false) cout << "entry=" << entry << endl;
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef offlinePhysics_cxx
