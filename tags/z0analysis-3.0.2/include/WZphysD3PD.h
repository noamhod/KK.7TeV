//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Dec 30 11:45:04 2010 by ROOT version 5.26/00
// from TTree physics/physics
// found on file: group10.phys-sm.06830_002695.D3PD._00017.root
//////////////////////////////////////////////////////////

#ifndef WZphysD3PD_h
#define WZphysD3PD_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class WZphysD3PD {
	public :
	TTree          *fChain;   //!pointer to the analyzed TTree or TChain
	Int_t           fCurrent; //!current Tree number in a TChain
	Bool_t          isMC;

	// Declaration of leaf types
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
	
	Bool_t          EF_2mu0_NoAlg;
	Bool_t          EF_2mu10;
	Bool_t          EF_2mu10_NoAlg;
	Bool_t          EF_2mu4;
	Bool_t          EF_2mu4_Bmumu;
	Bool_t          EF_2mu4_Bmumux;
	Bool_t          EF_2mu4_DiMu;
	Bool_t          EF_2mu4_DiMu_SiTrk;
	Bool_t          EF_2mu4_DiMu_noVtx;
	Bool_t          EF_2mu4_DiMu_noVtx_noOS;
	Bool_t          EF_2mu4_Jpsimumu;
	Bool_t          EF_2mu4_Jpsimumu_IDTrkNoCut;
	Bool_t          EF_2mu4_Upsimumu;
	Bool_t          EF_2mu6;
	Bool_t          EF_2mu6_Bmumu;
	Bool_t          EF_2mu6_Bmumux;
	Bool_t          EF_2mu6_DiMu;
	Bool_t          EF_2mu6_Jpsimumu;
	Bool_t          EF_2mu6_MG;
	Bool_t          EF_2mu6_NoAlg;
	Bool_t          EF_2mu6_Upsimumu;
	Bool_t          EF_2mu6_g10_loose;
	
	Bool_t          EF_mu0_NoAlg;
	Bool_t          EF_mu0_comm_NoAlg;
	Bool_t          EF_mu0_comm_empty_NoAlg;
	Bool_t          EF_mu0_comm_firstempty_NoAlg;
	Bool_t          EF_mu0_comm_unpaired_iso_NoAlg;
	Bool_t          EF_mu0_comm_unpaired_noniso_NoAlg;
	Bool_t          EF_mu0_empty_NoAlg;
	Bool_t          EF_mu0_firstempty_NoAlg;
	Bool_t          EF_mu0_missingRoi;
	Bool_t          EF_mu0_outOfTime1;
	Bool_t          EF_mu0_outOfTime2;
	Bool_t          EF_mu0_rpcOnly;
	Bool_t          EF_mu0_unpaired_iso_NoAlg;
	Bool_t          EF_mu0_unpaired_noniso_NoAlg;
	Bool_t          EF_mu10;
	Bool_t          EF_mu10_Ecut12;
	Bool_t          EF_mu10_Ecut123;
	Bool_t          EF_mu10_Ecut13;
	Bool_t          EF_mu10_IDTrkNoCut;
	Bool_t          EF_mu10_MG;
	Bool_t          EF_mu10_MSonly;
	Bool_t          EF_mu10_MSonly_Ecut12;
	Bool_t          EF_mu10_MSonly_Ecut123;
	Bool_t          EF_mu10_MSonly_Ecut13;
	Bool_t          EF_mu10_MSonly_tight;
	Bool_t          EF_mu10_NoAlg;
	Bool_t          EF_mu10_SiTrk;
	Bool_t          EF_mu10_j30;
	Bool_t          EF_mu10_tight;
	Bool_t          EF_mu10i_loose;
	Bool_t          EF_mu13;
	Bool_t          EF_mu13_MG;
	Bool_t          EF_mu13_MG_tight;
	Bool_t          EF_mu13_tight;
	Bool_t          EF_mu15;
	Bool_t          EF_mu15_MG;
	Bool_t          EF_mu15_NoAlg;
	Bool_t          EF_mu20;
	Bool_t          EF_mu20_MSonly;
	Bool_t          EF_mu20_NoAlg;
	Bool_t          EF_mu20_passHLT;
	Bool_t          EF_mu20_slow;
	Bool_t          EF_mu30_MSonly;
	Bool_t          EF_mu4;
	Bool_t          EF_mu40_MSonly;
	Bool_t          EF_mu4_Bmumu;
	Bool_t          EF_mu4_BmumuX;
	Bool_t          EF_mu4_DiMu;
	Bool_t          EF_mu4_DiMu_FS;
	Bool_t          EF_mu4_DiMu_FS_noOS;
	Bool_t          EF_mu4_DiMu_MG;
	Bool_t          EF_mu4_DiMu_MG_FS;
	Bool_t          EF_mu4_DiMu_SiTrk;
	Bool_t          EF_mu4_DiMu_SiTrk_FS;
	Bool_t          EF_mu4_DiMu_noOS;
	Bool_t          EF_mu4_IDTrkNoCut;
	Bool_t          EF_mu4_Jpsie5e3;
	Bool_t          EF_mu4_Jpsie5e3_FS;
	Bool_t          EF_mu4_Jpsie5e3_SiTrk;
	Bool_t          EF_mu4_Jpsie5e3_SiTrk_FS;
	Bool_t          EF_mu4_Jpsimumu;
	Bool_t          EF_mu4_Jpsimumu_FS;
	Bool_t          EF_mu4_Jpsimumu_SiTrk_FS;
	Bool_t          EF_mu4_L1J10_matched;
	Bool_t          EF_mu4_L1J15_matched;
	Bool_t          EF_mu4_L1J30_matched;
	Bool_t          EF_mu4_L1J55_matched;
	Bool_t          EF_mu4_L1J5_matched;
	Bool_t          EF_mu4_L2MSonly_EFFS_passL2;
	Bool_t          EF_mu4_MG;
	Bool_t          EF_mu4_MSonly;
	Bool_t          EF_mu4_MSonly_EFFS_passL2;
	Bool_t          EF_mu4_MSonly_MB2_noL2_EFFS;
	Bool_t          EF_mu4_MSonly_cosmic;
	Bool_t          EF_mu4_MSonly_outOfTime;
	Bool_t          EF_mu4_MV;
	Bool_t          EF_mu4_SiTrk;
	Bool_t          EF_mu4_Trk_Jpsi;
	Bool_t          EF_mu4_Trk_Jpsi_FS;
	Bool_t          EF_mu4_Trk_Jpsi_loose;
	Bool_t          EF_mu4_Trk_Upsi_FS;
	Bool_t          EF_mu4_Trk_Upsi_loose_FS;
	Bool_t          EF_mu4_Upsimumu_FS;
	Bool_t          EF_mu4_Upsimumu_SiTrk_FS;
	Bool_t          EF_mu4_comm_MSonly_cosmic;
	Bool_t          EF_mu4_comm_cosmic;
	Bool_t          EF_mu4_comm_firstempty;
	Bool_t          EF_mu4_comm_unpaired_iso;
	Bool_t          EF_mu4_cosmic;
	Bool_t          EF_mu4_firstempty;
	Bool_t          EF_mu4_j20;
	Bool_t          EF_mu4_j20_jetNoEF;
	Bool_t          EF_mu4_j30;
	Bool_t          EF_mu4_j30_jetNoEF;
	Bool_t          EF_mu4_mu6;
	Bool_t          EF_mu4_muCombTag;
	Bool_t          EF_mu4_tile;
	Bool_t          EF_mu4_tile_cosmic;
	Bool_t          EF_mu4_unpaired_iso;
	Bool_t          EF_mu4mu6_Bmumu;
	Bool_t          EF_mu4mu6_BmumuX;
	Bool_t          EF_mu4mu6_DiMu;
	Bool_t          EF_mu4mu6_Jpsimumu;
	Bool_t          EF_mu4mu6_Jpsimumu_IDTrkNoCut;
	Bool_t          EF_mu4mu6_Upsimumu;
	Bool_t          EF_mu6;
	Bool_t          EF_mu6_Bmumu;
	Bool_t          EF_mu6_BmumuX;
	Bool_t          EF_mu6_DiMu;
	Bool_t          EF_mu6_Ecut12;
	Bool_t          EF_mu6_Ecut123;
	Bool_t          EF_mu6_Ecut13;
	Bool_t          EF_mu6_Ecut2;
	Bool_t          EF_mu6_Ecut3;
	Bool_t          EF_mu6_IDTrkNoCut;
	Bool_t          EF_mu6_Jpsie5e3;
	Bool_t          EF_mu6_Jpsie5e3_FS;
	Bool_t          EF_mu6_Jpsie5e3_SiTrk;
	Bool_t          EF_mu6_Jpsie5e3_SiTrk_FS;
	Bool_t          EF_mu6_Jpsimumu;
	Bool_t          EF_mu6_MG;
	Bool_t          EF_mu6_MSonly;
	Bool_t          EF_mu6_MSonly_Ecut12;
	Bool_t          EF_mu6_MSonly_Ecut123;
	Bool_t          EF_mu6_MSonly_Ecut13;
	Bool_t          EF_mu6_MSonly_Ecut2;
	Bool_t          EF_mu6_MSonly_Ecut3;
	Bool_t          EF_mu6_MSonly_outOfTime;
	Bool_t          EF_mu6_NoAlg;
	Bool_t          EF_mu6_SiTrk;
	Bool_t          EF_mu6_Trk_Jpsi;
	Bool_t          EF_mu6_Upsimumu_FS;
	Bool_t          EF_mu6_muCombTag;
	
	Bool_t          L1_2MU0;
	Bool_t          L1_2MU0_FIRSTEMPTY;
	Bool_t          L1_2MU0_MU6;
	Bool_t          L1_2MU10;
	Bool_t          L1_2MU20;
	Bool_t          L1_2MU6;
	Bool_t          L1_2MU6_EM5;
	
	Bool_t          L1_MU0;
	Bool_t          L1_MU0_COMM;
	Bool_t          L1_MU0_COMM_EMPTY;
	Bool_t          L1_MU0_COMM_FIRSTEMPTY;
	Bool_t          L1_MU0_COMM_UNPAIRED_ISO;
	Bool_t          L1_MU0_COMM_UNPAIRED_NONISO;
	Bool_t          L1_MU0_EM3;
	Bool_t          L1_MU0_EMPTY;
	Bool_t          L1_MU0_FIRSTEMPTY;
	Bool_t          L1_MU0_J10;
	Bool_t          L1_MU0_J15;
	Bool_t          L1_MU0_J30;
	Bool_t          L1_MU0_J5;
	Bool_t          L1_MU0_J55;
	Bool_t          L1_MU0_MV;
	Bool_t          L1_MU0_UNPAIRED_ISO;
	Bool_t          L1_MU0_UNPAIRED_NONISO;
	Bool_t          L1_MU10;
	Bool_t          L1_MU10_FIRSTEMPTY;
	Bool_t          L1_MU10_J10;
	Bool_t          L1_MU15;
	Bool_t          L1_MU20;
	Bool_t          L1_MU6;
	Bool_t          L1_MU6_EM3;
	Bool_t          L1_MU6_FIRSTEMPTY;
	Bool_t          L1_MU6_J5;
	
	Bool_t          L2_2mu0_NoAlg;
	Bool_t          L2_2mu10;
	Bool_t          L2_2mu10_NoAlg;
	Bool_t          L2_2mu4;
	Bool_t          L2_2mu4_Bmumu;
	Bool_t          L2_2mu4_Bmumux;
	Bool_t          L2_2mu4_DiMu;
	Bool_t          L2_2mu4_DiMu_SiTrk;
	Bool_t          L2_2mu4_DiMu_noVtx;
	Bool_t          L2_2mu4_DiMu_noVtx_noOS;
	Bool_t          L2_2mu4_Jpsimumu;
	Bool_t          L2_2mu4_Jpsimumu_IDTrkNoCut;
	Bool_t          L2_2mu4_Upsimumu;
	Bool_t          L2_2mu6;
	Bool_t          L2_2mu6_Bmumu;
	Bool_t          L2_2mu6_Bmumux;
	Bool_t          L2_2mu6_DiMu;
	Bool_t          L2_2mu6_Jpsimumu;
	Bool_t          L2_2mu6_MG;
	Bool_t          L2_2mu6_NoAlg;
	Bool_t          L2_2mu6_Upsimumu;
	Bool_t          L2_2mu6_g10_loose;
	
	Bool_t          L2_mu0_NoAlg;
	Bool_t          L2_mu0_comm_NoAlg;
	Bool_t          L2_mu0_comm_empty_NoAlg;
	Bool_t          L2_mu0_comm_firstempty_NoAlg;
	Bool_t          L2_mu0_comm_unpaired_iso_NoAlg;
	Bool_t          L2_mu0_comm_unpaired_noniso_NoAlg;
	Bool_t          L2_mu0_empty_NoAlg;
	Bool_t          L2_mu0_firstempty_NoAlg;
	Bool_t          L2_mu0_missingRoi;
	Bool_t          L2_mu0_outOfTime1;
	Bool_t          L2_mu0_outOfTime2;
	Bool_t          L2_mu0_rpcOnly;
	Bool_t          L2_mu0_unpaired_iso_NoAlg;
	Bool_t          L2_mu0_unpaired_noniso_NoAlg;
	Bool_t          L2_mu10;
	Bool_t          L2_mu10_Ecut12;
	Bool_t          L2_mu10_Ecut123;
	Bool_t          L2_mu10_Ecut13;
	Bool_t          L2_mu10_IDTrkNoCut;
	Bool_t          L2_mu10_MG;
	Bool_t          L2_mu10_MSonly;
	Bool_t          L2_mu10_MSonly_Ecut12;
	Bool_t          L2_mu10_MSonly_Ecut123;
	Bool_t          L2_mu10_MSonly_Ecut13;
	Bool_t          L2_mu10_MSonly_tight;
	Bool_t          L2_mu10_NoAlg;
	Bool_t          L2_mu10_SiTrk;
	Bool_t          L2_mu10_j30;
	Bool_t          L2_mu10_tight;
	Bool_t          L2_mu10i_loose;
	Bool_t          L2_mu13;
	Bool_t          L2_mu13_MG;
	Bool_t          L2_mu13_MG_tight;
	Bool_t          L2_mu13_tight;
	Bool_t          L2_mu15;
	Bool_t          L2_mu15_MG;
	Bool_t          L2_mu15_NoAlg;
	Bool_t          L2_mu20;
	Bool_t          L2_mu20_MSonly;
	Bool_t          L2_mu20_NoAlg;
	Bool_t          L2_mu20_passHLT;
	Bool_t          L2_mu20_slow;
	Bool_t          L2_mu30_MSonly;
	Bool_t          L2_mu4;
	Bool_t          L2_mu40_MSonly;
	Bool_t          L2_mu4_Bmumu;
	Bool_t          L2_mu4_BmumuX;
	Bool_t          L2_mu4_DiMu;
	Bool_t          L2_mu4_DiMu_FS;
	Bool_t          L2_mu4_DiMu_FS_noOS;
	Bool_t          L2_mu4_DiMu_MG;
	Bool_t          L2_mu4_DiMu_MG_FS;
	Bool_t          L2_mu4_DiMu_SiTrk;
	Bool_t          L2_mu4_DiMu_SiTrk_FS;
	Bool_t          L2_mu4_DiMu_noOS;
	Bool_t          L2_mu4_IDTrkNoCut;
	Bool_t          L2_mu4_Jpsie5e3;
	Bool_t          L2_mu4_Jpsie5e3_FS;
	Bool_t          L2_mu4_Jpsie5e3_SiTrk;
	Bool_t          L2_mu4_Jpsie5e3_SiTrk_FS;
	Bool_t          L2_mu4_Jpsimumu;
	Bool_t          L2_mu4_Jpsimumu_FS;
	Bool_t          L2_mu4_Jpsimumu_SiTrk_FS;
	Bool_t          L2_mu4_L1J10_matched;
	Bool_t          L2_mu4_L1J15_matched;
	Bool_t          L2_mu4_L1J30_matched;
	Bool_t          L2_mu4_L1J55_matched;
	Bool_t          L2_mu4_L1J5_matched;
	Bool_t          L2_mu4_L2MSonly_EFFS_passL2;
	Bool_t          L2_mu4_MG;
	Bool_t          L2_mu4_MSonly;
	Bool_t          L2_mu4_MSonly_EFFS_passL2;
	Bool_t          L2_mu4_MSonly_MB2_noL2_EFFS;
	Bool_t          L2_mu4_MSonly_cosmic;
	Bool_t          L2_mu4_MSonly_outOfTime;
	Bool_t          L2_mu4_MV;
	Bool_t          L2_mu4_SiTrk;
	Bool_t          L2_mu4_Trk_Jpsi;
	Bool_t          L2_mu4_Trk_Jpsi_FS;
	Bool_t          L2_mu4_Trk_Jpsi_loose;
	Bool_t          L2_mu4_Trk_Upsi_FS;
	Bool_t          L2_mu4_Trk_Upsi_loose_FS;
	Bool_t          L2_mu4_Upsimumu_FS;
	Bool_t          L2_mu4_Upsimumu_SiTrk_FS;
	Bool_t          L2_mu4_comm_MSonly_cosmic;
	Bool_t          L2_mu4_comm_cosmic;
	Bool_t          L2_mu4_comm_firstempty;
	Bool_t          L2_mu4_comm_unpaired_iso;
	Bool_t          L2_mu4_cosmic;
	Bool_t          L2_mu4_firstempty;
	Bool_t          L2_mu4_j20;
	Bool_t          L2_mu4_j20_jetNoEF;
	Bool_t          L2_mu4_j25;
	Bool_t          L2_mu4_mu6;
	Bool_t          L2_mu4_muCombTag;
	Bool_t          L2_mu4_tile;
	Bool_t          L2_mu4_tile_cosmic;
	Bool_t          L2_mu4_unpaired_iso;
	Bool_t          L2_mu4mu6_Bmumu;
	Bool_t          L2_mu4mu6_BmumuX;
	Bool_t          L2_mu4mu6_DiMu;
	Bool_t          L2_mu4mu6_Jpsimumu;
	Bool_t          L2_mu4mu6_Jpsimumu_IDTrkNoCut;
	Bool_t          L2_mu4mu6_Upsimumu;
	Bool_t          L2_mu6;
	Bool_t          L2_mu6_Bmumu;
	Bool_t          L2_mu6_BmumuX;
	Bool_t          L2_mu6_DiMu;
	Bool_t          L2_mu6_Ecut12;
	Bool_t          L2_mu6_Ecut123;
	Bool_t          L2_mu6_Ecut13;
	Bool_t          L2_mu6_Ecut2;
	Bool_t          L2_mu6_Ecut3;
	Bool_t          L2_mu6_IDTrkNoCut;
	Bool_t          L2_mu6_Jpsie5e3;
	Bool_t          L2_mu6_Jpsie5e3_FS;
	Bool_t          L2_mu6_Jpsie5e3_SiTrk;
	Bool_t          L2_mu6_Jpsie5e3_SiTrk_FS;
	Bool_t          L2_mu6_Jpsimumu;
	Bool_t          L2_mu6_MG;
	Bool_t          L2_mu6_MSonly;
	Bool_t          L2_mu6_MSonly_Ecut12;
	Bool_t          L2_mu6_MSonly_Ecut123;
	Bool_t          L2_mu6_MSonly_Ecut13;
	Bool_t          L2_mu6_MSonly_Ecut2;
	Bool_t          L2_mu6_MSonly_Ecut3;
	Bool_t          L2_mu6_MSonly_outOfTime;
	Bool_t          L2_mu6_NoAlg;
	Bool_t          L2_mu6_SiTrk;
	Bool_t          L2_mu6_Trk_Jpsi;
	Bool_t          L2_mu6_Upsimumu_FS;
	Bool_t          L2_mu6_muCombTag;
	
	Int_t           mu_muid_n;
	vector<float>   *mu_muid_E;
	vector<float>   *mu_muid_pt;
	vector<float>   *mu_muid_m;
	vector<float>   *mu_muid_eta;
	vector<float>   *mu_muid_phi;
	vector<float>   *mu_muid_px;
	vector<float>   *mu_muid_py;
	vector<float>   *mu_muid_pz;
	vector<float>   *mu_muid_charge;
	vector<unsigned short> *mu_muid_allauthor;
	vector<int>     *mu_muid_author;
	vector<float>   *mu_muid_beta;
	vector<float>   *mu_muid_isMuonLikelihood;
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
	vector<float>   *mu_muid_etCore;
	vector<float>   *mu_muid_energyLossType;
	vector<unsigned short> *mu_muid_caloMuonIdTag;
	vector<double>  *mu_muid_caloLRLikelihood;
	vector<int>     *mu_muid_bestMatch;
	vector<int>     *mu_muid_isStandAloneMuon;
	vector<int>     *mu_muid_isCombinedMuon;
	vector<int>     *mu_muid_isLowPtReconstructedMuon;
	vector<int>     *mu_muid_loose;
	vector<int>     *mu_muid_medium;
	vector<int>     *mu_muid_tight;
	vector<float>   *mu_muid_d0_exPV;
	vector<float>   *mu_muid_z0_exPV;
	vector<float>   *mu_muid_phi_exPV;
	vector<float>   *mu_muid_theta_exPV;
	vector<float>   *mu_muid_qoverp_exPV;
	vector<float>   *mu_muid_cb_d0_exPV;
	vector<float>   *mu_muid_cb_z0_exPV;
	vector<float>   *mu_muid_cb_phi_exPV;
	vector<float>   *mu_muid_cb_theta_exPV;
	vector<float>   *mu_muid_cb_qoverp_exPV;
	vector<float>   *mu_muid_id_d0_exPV;
	vector<float>   *mu_muid_id_z0_exPV;
	vector<float>   *mu_muid_id_phi_exPV;
	vector<float>   *mu_muid_id_theta_exPV;
	vector<float>   *mu_muid_id_qoverp_exPV;
	vector<float>   *mu_muid_me_d0_exPV;
	vector<float>   *mu_muid_me_z0_exPV;
	vector<float>   *mu_muid_me_phi_exPV;
	vector<float>   *mu_muid_me_theta_exPV;
	vector<float>   *mu_muid_me_qoverp_exPV;
	vector<float>   *mu_muid_ie_d0_exPV;
	vector<float>   *mu_muid_ie_z0_exPV;
	vector<float>   *mu_muid_ie_phi_exPV;
	vector<float>   *mu_muid_ie_theta_exPV;
	vector<float>   *mu_muid_ie_qoverp_exPV;
	vector<vector<int> > *mu_muid_SpaceTime_detID;
	vector<vector<float> > *mu_muid_SpaceTime_t;
	vector<vector<float> > *mu_muid_SpaceTime_tError;
	vector<vector<float> > *mu_muid_SpaceTime_weight;
	vector<vector<float> > *mu_muid_SpaceTime_x;
	vector<vector<float> > *mu_muid_SpaceTime_y;
	vector<vector<float> > *mu_muid_SpaceTime_z;
	vector<vector<float> > *mu_muid_SpaceTime_t_Tile;
	vector<vector<float> > *mu_muid_SpaceTime_tError_Tile;
	vector<vector<float> > *mu_muid_SpaceTime_weight_Tile;
	vector<vector<float> > *mu_muid_SpaceTime_x_Tile;
	vector<vector<float> > *mu_muid_SpaceTime_y_Tile;
	vector<vector<float> > *mu_muid_SpaceTime_z_Tile;
	vector<vector<float> > *mu_muid_SpaceTime_t_TRT;
	vector<vector<float> > *mu_muid_SpaceTime_tError_TRT;
	vector<vector<float> > *mu_muid_SpaceTime_weight_TRT;
	vector<vector<float> > *mu_muid_SpaceTime_x_TRT;
	vector<vector<float> > *mu_muid_SpaceTime_y_TRT;
	vector<vector<float> > *mu_muid_SpaceTime_z_TRT;
	vector<vector<float> > *mu_muid_SpaceTime_t_MDT;
	vector<vector<float> > *mu_muid_SpaceTime_tError_MDT;
	vector<vector<float> > *mu_muid_SpaceTime_weight_MDT;
	vector<vector<float> > *mu_muid_SpaceTime_x_MDT;
	vector<vector<float> > *mu_muid_SpaceTime_y_MDT;
	vector<vector<float> > *mu_muid_SpaceTime_z_MDT;
	vector<float>   *mu_muid_TileCellEnergyLayer1;
	vector<float>   *mu_muid_TileTimeLayer1;
	vector<float>   *mu_muid_TileCellRmsNoiseLayer1;
	vector<float>   *mu_muid_TileCellSignLayer1;
	vector<float>   *mu_muid_TileCellEnergyLayer2;
	vector<float>   *mu_muid_TileTimeLayer2;
	vector<float>   *mu_muid_TileCellRmsNoiseLayer2;
	vector<float>   *mu_muid_TileCellSignLayer2;
	vector<float>   *mu_muid_TileCellEnergyLayer3;
	vector<float>   *mu_muid_TileTimeLayer3;
	vector<float>   *mu_muid_TileCellRmsNoiseLayer3;
	vector<float>   *mu_muid_TileCellSignLayer3;
	vector<float>   *mu_muid_MSTrkT0_1;
	vector<float>   *mu_muid_MSTrkT0_2;
	vector<float>   *mu_muid_MSTrkT0_3;
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
	vector<float>   *mu_muid_id_cov_d0_exPV;
	vector<float>   *mu_muid_id_cov_z0_exPV;
	vector<float>   *mu_muid_id_cov_phi_exPV;
	vector<float>   *mu_muid_id_cov_theta_exPV;
	vector<float>   *mu_muid_id_cov_qoverp_exPV;
	vector<float>   *mu_muid_id_cov_d0_z0_exPV;
	vector<float>   *mu_muid_id_cov_d0_phi_exPV;
	vector<float>   *mu_muid_id_cov_d0_theta_exPV;
	vector<float>   *mu_muid_id_cov_d0_qoverp_exPV;
	vector<float>   *mu_muid_id_cov_z0_phi_exPV;
	vector<float>   *mu_muid_id_cov_z0_theta_exPV;
	vector<float>   *mu_muid_id_cov_z0_qoverp_exPV;
	vector<float>   *mu_muid_id_cov_phi_theta_exPV;
	vector<float>   *mu_muid_id_cov_phi_qoverp_exPV;
	vector<float>   *mu_muid_id_cov_theta_qoverp_exPV;
	vector<float>   *mu_muid_me_cov_d0_exPV;
	vector<float>   *mu_muid_me_cov_z0_exPV;
	vector<float>   *mu_muid_me_cov_phi_exPV;
	vector<float>   *mu_muid_me_cov_theta_exPV;
	vector<float>   *mu_muid_me_cov_qoverp_exPV;
	vector<float>   *mu_muid_me_cov_d0_z0_exPV;
	vector<float>   *mu_muid_me_cov_d0_phi_exPV;
	vector<float>   *mu_muid_me_cov_d0_theta_exPV;
	vector<float>   *mu_muid_me_cov_d0_qoverp_exPV;
	vector<float>   *mu_muid_me_cov_z0_phi_exPV;
	vector<float>   *mu_muid_me_cov_z0_theta_exPV;
	vector<float>   *mu_muid_me_cov_z0_qoverp_exPV;
	vector<float>   *mu_muid_me_cov_phi_theta_exPV;
	vector<float>   *mu_muid_me_cov_phi_qoverp_exPV;
	vector<float>   *mu_muid_me_cov_theta_qoverp_exPV;
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
	vector<int>     *mu_muid_nOutliersOnTrack;
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
	vector<int>     *mu_muid_nGangedPixels;
	vector<int>     *mu_muid_nPixelDeadSensors;
	vector<int>     *mu_muid_nSCTDeadSensors;
	vector<int>     *mu_muid_nTRTDeadStraws;
	vector<int>     *mu_muid_expectBLayerHit;
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
	vector<float>   *mu_muid_truth_dr;
	vector<float>   *mu_muid_truth_E;
	vector<float>   *mu_muid_truth_pt;
	vector<float>   *mu_muid_truth_eta;
	vector<float>   *mu_muid_truth_phi;
	vector<int>     *mu_muid_truth_type;
	vector<int>     *mu_muid_truth_status;
	vector<int>     *mu_muid_truth_barcode;
	vector<int>     *mu_muid_truth_mothertype;
	vector<int>     *mu_muid_truth_motherbarcode;
	vector<int>     *mu_muid_truth_matched;
	vector<float>   *mu_muid_EFCB_dr;
	vector<int>     *mu_muid_EFCB_index;
	vector<float>   *mu_muid_EFMG_dr;
	vector<int>     *mu_muid_EFMG_index;
	vector<float>   *mu_muid_EFME_dr;
	vector<int>     *mu_muid_EFME_index;
	vector<float>   *mu_muid_L2CB_dr;
	vector<int>     *mu_muid_L2CB_index;
	vector<float>   *mu_muid_L1_dr;
	vector<int>     *mu_muid_L1_index;
	
	Int_t           mu_staco_n;
	vector<float>   *mu_staco_E;
	vector<float>   *mu_staco_pt;
	vector<float>   *mu_staco_m;
	vector<float>   *mu_staco_eta;
	vector<float>   *mu_staco_phi;
	vector<float>   *mu_staco_px;
	vector<float>   *mu_staco_py;
	vector<float>   *mu_staco_pz;
	vector<float>   *mu_staco_charge;
	vector<unsigned short> *mu_staco_allauthor;
	vector<int>     *mu_staco_author;
	vector<float>   *mu_staco_beta;
	vector<float>   *mu_staco_isMuonLikelihood;
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
	vector<float>   *mu_staco_etCore;
	vector<float>   *mu_staco_energyLossType;
	vector<unsigned short> *mu_staco_caloMuonIdTag;
	vector<double>  *mu_staco_caloLRLikelihood;
	vector<int>     *mu_staco_bestMatch;
	vector<int>     *mu_staco_isStandAloneMuon;
	vector<int>     *mu_staco_isCombinedMuon;
	vector<int>     *mu_staco_isLowPtReconstructedMuon;
	vector<int>     *mu_staco_loose;
	vector<int>     *mu_staco_medium;
	vector<int>     *mu_staco_tight;
	vector<float>   *mu_staco_d0_exPV;
	vector<float>   *mu_staco_z0_exPV;
	vector<float>   *mu_staco_phi_exPV;
	vector<float>   *mu_staco_theta_exPV;
	vector<float>   *mu_staco_qoverp_exPV;
	vector<float>   *mu_staco_cb_d0_exPV;
	vector<float>   *mu_staco_cb_z0_exPV;
	vector<float>   *mu_staco_cb_phi_exPV;
	vector<float>   *mu_staco_cb_theta_exPV;
	vector<float>   *mu_staco_cb_qoverp_exPV;
	vector<float>   *mu_staco_id_d0_exPV;
	vector<float>   *mu_staco_id_z0_exPV;
	vector<float>   *mu_staco_id_phi_exPV;
	vector<float>   *mu_staco_id_theta_exPV;
	vector<float>   *mu_staco_id_qoverp_exPV;
	vector<float>   *mu_staco_me_d0_exPV;
	vector<float>   *mu_staco_me_z0_exPV;
	vector<float>   *mu_staco_me_phi_exPV;
	vector<float>   *mu_staco_me_theta_exPV;
	vector<float>   *mu_staco_me_qoverp_exPV;
	vector<float>   *mu_staco_ie_d0_exPV;
	vector<float>   *mu_staco_ie_z0_exPV;
	vector<float>   *mu_staco_ie_phi_exPV;
	vector<float>   *mu_staco_ie_theta_exPV;
	vector<float>   *mu_staco_ie_qoverp_exPV;
	vector<vector<int> > *mu_staco_SpaceTime_detID;
	vector<vector<float> > *mu_staco_SpaceTime_t;
	vector<vector<float> > *mu_staco_SpaceTime_tError;
	vector<vector<float> > *mu_staco_SpaceTime_weight;
	vector<vector<float> > *mu_staco_SpaceTime_x;
	vector<vector<float> > *mu_staco_SpaceTime_y;
	vector<vector<float> > *mu_staco_SpaceTime_z;
	vector<vector<float> > *mu_staco_SpaceTime_t_Tile;
	vector<vector<float> > *mu_staco_SpaceTime_tError_Tile;
	vector<vector<float> > *mu_staco_SpaceTime_weight_Tile;
	vector<vector<float> > *mu_staco_SpaceTime_x_Tile;
	vector<vector<float> > *mu_staco_SpaceTime_y_Tile;
	vector<vector<float> > *mu_staco_SpaceTime_z_Tile;
	vector<vector<float> > *mu_staco_SpaceTime_t_TRT;
	vector<vector<float> > *mu_staco_SpaceTime_tError_TRT;
	vector<vector<float> > *mu_staco_SpaceTime_weight_TRT;
	vector<vector<float> > *mu_staco_SpaceTime_x_TRT;
	vector<vector<float> > *mu_staco_SpaceTime_y_TRT;
	vector<vector<float> > *mu_staco_SpaceTime_z_TRT;
	vector<vector<float> > *mu_staco_SpaceTime_t_MDT;
	vector<vector<float> > *mu_staco_SpaceTime_tError_MDT;
	vector<vector<float> > *mu_staco_SpaceTime_weight_MDT;
	vector<vector<float> > *mu_staco_SpaceTime_x_MDT;
	vector<vector<float> > *mu_staco_SpaceTime_y_MDT;
	vector<vector<float> > *mu_staco_SpaceTime_z_MDT;
	vector<float>   *mu_staco_TileCellEnergyLayer1;
	vector<float>   *mu_staco_TileTimeLayer1;
	vector<float>   *mu_staco_TileCellRmsNoiseLayer1;
	vector<float>   *mu_staco_TileCellSignLayer1;
	vector<float>   *mu_staco_TileCellEnergyLayer2;
	vector<float>   *mu_staco_TileTimeLayer2;
	vector<float>   *mu_staco_TileCellRmsNoiseLayer2;
	vector<float>   *mu_staco_TileCellSignLayer2;
	vector<float>   *mu_staco_TileCellEnergyLayer3;
	vector<float>   *mu_staco_TileTimeLayer3;
	vector<float>   *mu_staco_TileCellRmsNoiseLayer3;
	vector<float>   *mu_staco_TileCellSignLayer3;
	vector<float>   *mu_staco_MSTrkT0_1;
	vector<float>   *mu_staco_MSTrkT0_2;
	vector<float>   *mu_staco_MSTrkT0_3;
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
	vector<float>   *mu_staco_id_cov_d0_exPV;
	vector<float>   *mu_staco_id_cov_z0_exPV;
	vector<float>   *mu_staco_id_cov_phi_exPV;
	vector<float>   *mu_staco_id_cov_theta_exPV;
	vector<float>   *mu_staco_id_cov_qoverp_exPV;
	vector<float>   *mu_staco_id_cov_d0_z0_exPV;
	vector<float>   *mu_staco_id_cov_d0_phi_exPV;
	vector<float>   *mu_staco_id_cov_d0_theta_exPV;
	vector<float>   *mu_staco_id_cov_d0_qoverp_exPV;
	vector<float>   *mu_staco_id_cov_z0_phi_exPV;
	vector<float>   *mu_staco_id_cov_z0_theta_exPV;
	vector<float>   *mu_staco_id_cov_z0_qoverp_exPV;
	vector<float>   *mu_staco_id_cov_phi_theta_exPV;
	vector<float>   *mu_staco_id_cov_phi_qoverp_exPV;
	vector<float>   *mu_staco_id_cov_theta_qoverp_exPV;
	vector<float>   *mu_staco_me_cov_d0_exPV;
	vector<float>   *mu_staco_me_cov_z0_exPV;
	vector<float>   *mu_staco_me_cov_phi_exPV;
	vector<float>   *mu_staco_me_cov_theta_exPV;
	vector<float>   *mu_staco_me_cov_qoverp_exPV;
	vector<float>   *mu_staco_me_cov_d0_z0_exPV;
	vector<float>   *mu_staco_me_cov_d0_phi_exPV;
	vector<float>   *mu_staco_me_cov_d0_theta_exPV;
	vector<float>   *mu_staco_me_cov_d0_qoverp_exPV;
	vector<float>   *mu_staco_me_cov_z0_phi_exPV;
	vector<float>   *mu_staco_me_cov_z0_theta_exPV;
	vector<float>   *mu_staco_me_cov_z0_qoverp_exPV;
	vector<float>   *mu_staco_me_cov_phi_theta_exPV;
	vector<float>   *mu_staco_me_cov_phi_qoverp_exPV;
	vector<float>   *mu_staco_me_cov_theta_qoverp_exPV;
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
	vector<int>     *mu_staco_nOutliersOnTrack;
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
	vector<int>     *mu_staco_nGangedPixels;
	vector<int>     *mu_staco_nPixelDeadSensors;
	vector<int>     *mu_staco_nSCTDeadSensors;
	vector<int>     *mu_staco_nTRTDeadStraws;
	vector<int>     *mu_staco_expectBLayerHit;
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
	vector<float>   *mu_staco_truth_dr;
	vector<float>   *mu_staco_truth_E;
	vector<float>   *mu_staco_truth_pt;
	vector<float>   *mu_staco_truth_eta;
	vector<float>   *mu_staco_truth_phi;
	vector<int>     *mu_staco_truth_type;
	vector<int>     *mu_staco_truth_status;
	vector<int>     *mu_staco_truth_barcode;
	vector<int>     *mu_staco_truth_mothertype;
	vector<int>     *mu_staco_truth_motherbarcode;
	vector<int>     *mu_staco_truth_matched;
	vector<float>   *mu_staco_EFCB_dr;
	vector<int>     *mu_staco_EFCB_index;
	vector<float>   *mu_staco_EFMG_dr;
	vector<int>     *mu_staco_EFMG_index;
	vector<float>   *mu_staco_EFME_dr;
	vector<int>     *mu_staco_EFME_index;
	vector<float>   *mu_staco_L2CB_dr;
	vector<int>     *mu_staco_L2CB_index;
	vector<float>   *mu_staco_L1_dr;
	vector<int>     *mu_staco_L1_index;
	
	Int_t           mu_calo_n;
	vector<float>   *mu_calo_E;
	vector<float>   *mu_calo_pt;
	vector<float>   *mu_calo_m;
	vector<float>   *mu_calo_eta;
	vector<float>   *mu_calo_phi;
	vector<float>   *mu_calo_px;
	vector<float>   *mu_calo_py;
	vector<float>   *mu_calo_pz;
	vector<float>   *mu_calo_charge;
	vector<unsigned short> *mu_calo_allauthor;
	vector<int>     *mu_calo_hastrack;
	vector<float>   *mu_calo_truth_dr;
	vector<float>   *mu_calo_truth_E;
	vector<float>   *mu_calo_truth_pt;
	vector<float>   *mu_calo_truth_eta;
	vector<float>   *mu_calo_truth_phi;
	vector<int>     *mu_calo_truth_type;
	vector<int>     *mu_calo_truth_status;
	vector<int>     *mu_calo_truth_barcode;
	vector<int>     *mu_calo_truth_mothertype;
	vector<int>     *mu_calo_truth_motherbarcode;
	vector<int>     *mu_calo_truth_matched;
	
	Float_t         MET_RefFinal_phi;
	Float_t         MET_RefFinal_et;
	Float_t         MET_RefFinal_sumet;
	Float_t         MET_Cryo_phi;
	Float_t         MET_Cryo_et;
	Float_t         MET_Cryo_sumet;
	Float_t         MET_RefEle_phi;
	Float_t         MET_RefEle_et;
	Float_t         MET_RefEle_sumet;
	Float_t         MET_RefJet_phi;
	Float_t         MET_RefJet_et;
	Float_t         MET_RefJet_sumet;
	Float_t         MET_SoftJets_phi;
	Float_t         MET_SoftJets_et;
	Float_t         MET_SoftJets_sumet;
	Float_t         MET_RefMuon_phi;
	Float_t         MET_RefMuon_et;
	Float_t         MET_RefMuon_sumet;
	Float_t         MET_RefMuon_Staco_phi;
	Float_t         MET_RefMuon_Staco_et;
	Float_t         MET_RefMuon_Staco_sumet;
	Float_t         MET_RefMuon_Muid_phi;
	Float_t         MET_RefMuon_Muid_et;
	Float_t         MET_RefMuon_Muid_sumet;
	Float_t         MET_RefGamma_phi;
	Float_t         MET_RefGamma_et;
	Float_t         MET_RefGamma_sumet;
	Float_t         MET_RefTau_phi;
	Float_t         MET_RefTau_et;
	Float_t         MET_RefTau_sumet;
	Float_t         MET_CellOut_phi;
	Float_t         MET_CellOut_et;
	Float_t         MET_CellOut_sumet;
	Float_t         MET_Track_phi;
	Float_t         MET_Track_et;
	Float_t         MET_Track_sumet;
	Float_t         MET_RefFinal_em_etx;
	Float_t         MET_RefFinal_em_ety;
	Float_t         MET_RefFinal_em_phi;
	Float_t         MET_RefFinal_em_et;
	Float_t         MET_RefFinal_em_sumet;
	Float_t         MET_RefEle_em_phi;
	Float_t         MET_RefEle_em_et;
	Float_t         MET_RefEle_em_sumet;
	Float_t         MET_RefJet_em_phi;
	Float_t         MET_RefJet_em_et;
	Float_t         MET_RefJet_em_sumet;
	Float_t         MET_SoftJets_em_phi;
	Float_t         MET_SoftJets_em_et;
	Float_t         MET_SoftJets_em_sumet;
	Float_t         MET_RefMuon_em_phi;
	Float_t         MET_RefMuon_em_et;
	Float_t         MET_RefMuon_em_sumet;
	Float_t         MET_RefMuon_Track_em_phi;
	Float_t         MET_RefMuon_Track_em_et;
	Float_t         MET_RefMuon_Track_em_sumet;
	Float_t         MET_RefGamma_em_phi;
	Float_t         MET_RefGamma_em_et;
	Float_t         MET_RefGamma_em_sumet;
	Float_t         MET_RefTau_em_phi;
	Float_t         MET_RefTau_em_et;
	Float_t         MET_RefTau_em_sumet;
	Float_t         MET_CellOut_em_etx;
	Float_t         MET_CellOut_em_ety;
	Float_t         MET_CellOut_em_phi;
	Float_t         MET_CellOut_em_et;
	Float_t         MET_CellOut_em_sumet;
	Float_t         MET_Muon_Isol_Staco_phi;
	Float_t         MET_Muon_Isol_Staco_et;
	Float_t         MET_Muon_Isol_Staco_sumet;
	Float_t         MET_Muon_NonIsol_Staco_phi;
	Float_t         MET_Muon_NonIsol_Staco_et;
	Float_t         MET_Muon_NonIsol_Staco_sumet;
	Float_t         MET_Muon_Total_Staco_phi;
	Float_t         MET_Muon_Total_Staco_et;
	Float_t         MET_Muon_Total_Staco_sumet;
	Float_t         MET_Muon_Isol_Muid_phi;
	Float_t         MET_Muon_Isol_Muid_et;
	Float_t         MET_Muon_Isol_Muid_sumet;
	Float_t         MET_Muon_NonIsol_Muid_phi;
	Float_t         MET_Muon_NonIsol_Muid_et;
	Float_t         MET_Muon_NonIsol_Muid_sumet;
	Float_t         MET_Muon_Total_Muid_phi;
	Float_t         MET_Muon_Total_Muid_et;
	Float_t         MET_Muon_Total_Muid_sumet;
	Float_t         MET_MuonBoy_phi;
	Float_t         MET_MuonBoy_et;
	Float_t         MET_MuonBoy_sumet;
	Float_t         MET_RefMuon_Track_phi;
	Float_t         MET_RefMuon_Track_et;
	Float_t         MET_RefMuon_Track_sumet;
	Float_t         MET_RefMuon_Track_Staco_phi;
	Float_t         MET_RefMuon_Track_Staco_et;
	Float_t         MET_RefMuon_Track_Staco_sumet;
	Float_t         MET_RefMuon_Track_Muid_phi;
	Float_t         MET_RefMuon_Track_Muid_et;
	Float_t         MET_RefMuon_Track_Muid_sumet;
	Float_t         MET_CryoCone_phi;
	Float_t         MET_CryoCone_et;
	Float_t         MET_CryoCone_sumet;
	Float_t         MET_Final_phi;
	Float_t         MET_Final_et;
	Float_t         MET_Final_sumet;
	Float_t         MET_MuonBoy_Spectro_phi;
	Float_t         MET_MuonBoy_Spectro_et;
	Float_t         MET_MuonBoy_Spectro_sumet;
	Float_t         MET_MuonBoy_Track_phi;
	Float_t         MET_MuonBoy_Track_et;
	Float_t         MET_MuonBoy_Track_sumet;
	Float_t         MET_MuonMuid_phi;
	Float_t         MET_MuonMuid_et;
	Float_t         MET_MuonMuid_sumet;
	Float_t         MET_Muid_phi;
	Float_t         MET_Muid_et;
	Float_t         MET_Muid_sumet;
	Float_t         MET_Muid_Spectro_phi;
	Float_t         MET_Muid_Spectro_et;
	Float_t         MET_Muid_Spectro_sumet;
	Float_t         MET_Muid_Track_phi;
	Float_t         MET_Muid_Track_et;
	Float_t         MET_Muid_Track_sumet;
	Float_t         MET_Muon_phi;
	Float_t         MET_Muon_et;
	Float_t         MET_Muon_sumet;
	Float_t         MET_TopoObj_phi;
	Float_t         MET_TopoObj_et;
	Float_t         MET_TopoObj_sumet;
	Float_t         MET_LocHadTopoObj_phi;
	Float_t         MET_LocHadTopoObj_et;
	Float_t         MET_LocHadTopoObj_sumet;
	Float_t         MET_Topo_phi;
	Float_t         MET_Topo_et;
	Float_t         MET_Topo_sumet;
	Float_t         MET_Topo_SUMET_EMFrac;
	Float_t         MET_Topo_etx_PEMB;
	Float_t         MET_Topo_ety_PEMB;
	Float_t         MET_Topo_sumet_PEMB;
	Float_t         MET_Topo_phi_PEMB;
	Float_t         MET_Topo_etx_EMB;
	Float_t         MET_Topo_ety_EMB;
	Float_t         MET_Topo_sumet_EMB;
	Float_t         MET_Topo_phi_EMB;
	Float_t         MET_Topo_etx_PEMEC;
	Float_t         MET_Topo_ety_PEMEC;
	Float_t         MET_Topo_sumet_PEMEC;
	Float_t         MET_Topo_phi_PEMEC;
	Float_t         MET_Topo_etx_EME;
	Float_t         MET_Topo_ety_EME;
	Float_t         MET_Topo_sumet_EME;
	Float_t         MET_Topo_phi_EME;
	Float_t         MET_Topo_etx_TILE;
	Float_t         MET_Topo_ety_TILE;
	Float_t         MET_Topo_sumet_TILE;
	Float_t         MET_Topo_phi_TILE;
	Float_t         MET_Topo_etx_HEC;
	Float_t         MET_Topo_ety_HEC;
	Float_t         MET_Topo_sumet_HEC;
	Float_t         MET_Topo_phi_HEC;
	Float_t         MET_Topo_etx_FCAL;
	Float_t         MET_Topo_ety_FCAL;
	Float_t         MET_Topo_sumet_FCAL;
	Float_t         MET_Topo_phi_FCAL;
	Float_t         MET_Topo_nCell_PEMB;
	Float_t         MET_Topo_nCell_EMB;
	Float_t         MET_Topo_nCell_PEMEC;
	Float_t         MET_Topo_nCell_EME;
	Float_t         MET_Topo_nCell_TILE;
	Float_t         MET_Topo_nCell_HEC;
	Float_t         MET_Topo_nCell_FCAL;
	Float_t         MET_Topo_etx_CentralReg;
	Float_t         MET_Topo_ety_CentralReg;
	Float_t         MET_Topo_sumet_CentralReg;
	Float_t         MET_Topo_phi_CentralReg;
	Float_t         MET_Topo_etx_EndcapRegion;
	Float_t         MET_Topo_ety_EndcapRegion;
	Float_t         MET_Topo_sumet_EndcapRegion;
	Float_t         MET_Topo_phi_EndcapRegion;
	Float_t         MET_Topo_etx_ForwardReg;
	Float_t         MET_Topo_ety_ForwardReg;
	Float_t         MET_Topo_sumet_ForwardReg;
	Float_t         MET_Topo_phi_ForwardReg;
	Float_t         MET_CorrTopo_phi;
	Float_t         MET_CorrTopo_et;
	Float_t         MET_CorrTopo_sumet;
	Float_t         MET_CorrTopo_SUMET_EMFrac;
	Float_t         MET_CorrTopo_etx_PEMB;
	Float_t         MET_CorrTopo_ety_PEMB;
	Float_t         MET_CorrTopo_sumet_PEMB;
	Float_t         MET_CorrTopo_phi_PEMB;
	Float_t         MET_CorrTopo_etx_EMB;
	Float_t         MET_CorrTopo_ety_EMB;
	Float_t         MET_CorrTopo_sumet_EMB;
	Float_t         MET_CorrTopo_phi_EMB;
	Float_t         MET_CorrTopo_etx_PEMEC;
	Float_t         MET_CorrTopo_ety_PEMEC;
	Float_t         MET_CorrTopo_sumet_PEMEC;
	Float_t         MET_CorrTopo_phi_PEMEC;
	Float_t         MET_CorrTopo_etx_EME;
	Float_t         MET_CorrTopo_ety_EME;
	Float_t         MET_CorrTopo_sumet_EME;
	Float_t         MET_CorrTopo_phi_EME;
	Float_t         MET_CorrTopo_etx_TILE;
	Float_t         MET_CorrTopo_ety_TILE;
	Float_t         MET_CorrTopo_sumet_TILE;
	Float_t         MET_CorrTopo_phi_TILE;
	Float_t         MET_CorrTopo_etx_HEC;
	Float_t         MET_CorrTopo_ety_HEC;
	Float_t         MET_CorrTopo_sumet_HEC;
	Float_t         MET_CorrTopo_phi_HEC;
	Float_t         MET_CorrTopo_etx_FCAL;
	Float_t         MET_CorrTopo_ety_FCAL;
	Float_t         MET_CorrTopo_sumet_FCAL;
	Float_t         MET_CorrTopo_phi_FCAL;
	Float_t         MET_CorrTopo_nCell_PEMB;
	Float_t         MET_CorrTopo_nCell_EMB;
	Float_t         MET_CorrTopo_nCell_PEMEC;
	Float_t         MET_CorrTopo_nCell_EME;
	Float_t         MET_CorrTopo_nCell_TILE;
	Float_t         MET_CorrTopo_nCell_HEC;
	Float_t         MET_CorrTopo_nCell_FCAL;
	Float_t         MET_CorrTopo_etx_CentralReg;
	Float_t         MET_CorrTopo_ety_CentralReg;
	Float_t         MET_CorrTopo_sumet_CentralReg;
	Float_t         MET_CorrTopo_phi_CentralReg;
	Float_t         MET_CorrTopo_etx_EndcapRegion;
	Float_t         MET_CorrTopo_ety_EndcapRegion;
	Float_t         MET_CorrTopo_sumet_EndcapRegion;
	Float_t         MET_CorrTopo_phi_EndcapRegion;
	Float_t         MET_CorrTopo_etx_ForwardReg;
	Float_t         MET_CorrTopo_ety_ForwardReg;
	Float_t         MET_CorrTopo_sumet_ForwardReg;
	Float_t         MET_CorrTopo_phi_ForwardReg;
	Float_t         MET_LocHadTopo_phi;
	Float_t         MET_LocHadTopo_et;
	Float_t         MET_LocHadTopo_sumet;
	Float_t         MET_LocHadTopo_SUMET_EMFrac;
	Float_t         MET_LocHadTopo_etx_PEMB;
	Float_t         MET_LocHadTopo_ety_PEMB;
	Float_t         MET_LocHadTopo_sumet_PEMB;
	Float_t         MET_LocHadTopo_phi_PEMB;
	Float_t         MET_LocHadTopo_etx_EMB;
	Float_t         MET_LocHadTopo_ety_EMB;
	Float_t         MET_LocHadTopo_sumet_EMB;
	Float_t         MET_LocHadTopo_phi_EMB;
	Float_t         MET_LocHadTopo_etx_PEMEC;
	Float_t         MET_LocHadTopo_ety_PEMEC;
	Float_t         MET_LocHadTopo_sumet_PEMEC;
	Float_t         MET_LocHadTopo_phi_PEMEC;
	Float_t         MET_LocHadTopo_etx_EME;
	Float_t         MET_LocHadTopo_ety_EME;
	Float_t         MET_LocHadTopo_sumet_EME;
	Float_t         MET_LocHadTopo_phi_EME;
	Float_t         MET_LocHadTopo_etx_TILE;
	Float_t         MET_LocHadTopo_ety_TILE;
	Float_t         MET_LocHadTopo_sumet_TILE;
	Float_t         MET_LocHadTopo_phi_TILE;
	Float_t         MET_LocHadTopo_etx_HEC;
	Float_t         MET_LocHadTopo_ety_HEC;
	Float_t         MET_LocHadTopo_sumet_HEC;
	Float_t         MET_LocHadTopo_phi_HEC;
	Float_t         MET_LocHadTopo_etx_FCAL;
	Float_t         MET_LocHadTopo_ety_FCAL;
	Float_t         MET_LocHadTopo_sumet_FCAL;
	Float_t         MET_LocHadTopo_phi_FCAL;
	Float_t         MET_LocHadTopo_nCell_PEMB;
	Float_t         MET_LocHadTopo_nCell_EMB;
	Float_t         MET_LocHadTopo_nCell_PEMEC;
	Float_t         MET_LocHadTopo_nCell_EME;
	Float_t         MET_LocHadTopo_nCell_TILE;
	Float_t         MET_LocHadTopo_nCell_HEC;
	Float_t         MET_LocHadTopo_nCell_FCAL;
	Float_t         MET_LocHadTopo_etx_CentralReg;
	Float_t         MET_LocHadTopo_ety_CentralReg;
	Float_t         MET_LocHadTopo_sumet_CentralReg;
	Float_t         MET_LocHadTopo_phi_CentralReg;
	Float_t         MET_LocHadTopo_etx_EndcapRegion;
	Float_t         MET_LocHadTopo_ety_EndcapRegion;
	Float_t         MET_LocHadTopo_sumet_EndcapRegion;
	Float_t         MET_LocHadTopo_phi_EndcapRegion;
	Float_t         MET_LocHadTopo_etx_ForwardReg;
	Float_t         MET_LocHadTopo_ety_ForwardReg;
	Float_t         MET_LocHadTopo_sumet_ForwardReg;
	Float_t         MET_LocHadTopo_phi_ForwardReg;
	Float_t         MET_Calib_phi;
	Float_t         MET_Calib_et;
	Float_t         MET_Calib_sumet;
	Float_t         MET_Calib_SUMET_EMFrac;
	Float_t         MET_Calib_etx_PEMB;
	Float_t         MET_Calib_ety_PEMB;
	Float_t         MET_Calib_sumet_PEMB;
	Float_t         MET_Calib_phi_PEMB;
	Float_t         MET_Calib_etx_EMB;
	Float_t         MET_Calib_ety_EMB;
	Float_t         MET_Calib_sumet_EMB;
	Float_t         MET_Calib_phi_EMB;
	Float_t         MET_Calib_etx_PEMEC;
	Float_t         MET_Calib_ety_PEMEC;
	Float_t         MET_Calib_sumet_PEMEC;
	Float_t         MET_Calib_phi_PEMEC;
	Float_t         MET_Calib_etx_EME;
	Float_t         MET_Calib_ety_EME;
	Float_t         MET_Calib_sumet_EME;
	Float_t         MET_Calib_phi_EME;
	Float_t         MET_Calib_etx_TILE;
	Float_t         MET_Calib_ety_TILE;
	Float_t         MET_Calib_sumet_TILE;
	Float_t         MET_Calib_phi_TILE;
	Float_t         MET_Calib_etx_HEC;
	Float_t         MET_Calib_ety_HEC;
	Float_t         MET_Calib_sumet_HEC;
	Float_t         MET_Calib_phi_HEC;
	Float_t         MET_Calib_etx_FCAL;
	Float_t         MET_Calib_ety_FCAL;
	Float_t         MET_Calib_sumet_FCAL;
	Float_t         MET_Calib_phi_FCAL;
	Float_t         MET_Calib_nCell_PEMB;
	Float_t         MET_Calib_nCell_EMB;
	Float_t         MET_Calib_nCell_PEMEC;
	Float_t         MET_Calib_nCell_EME;
	Float_t         MET_Calib_nCell_TILE;
	Float_t         MET_Calib_nCell_HEC;
	Float_t         MET_Calib_nCell_FCAL;
	Float_t         MET_Calib_etx_CentralReg;
	Float_t         MET_Calib_ety_CentralReg;
	Float_t         MET_Calib_sumet_CentralReg;
	Float_t         MET_Calib_phi_CentralReg;
	Float_t         MET_Calib_etx_EndcapRegion;
	Float_t         MET_Calib_ety_EndcapRegion;
	Float_t         MET_Calib_sumet_EndcapRegion;
	Float_t         MET_Calib_phi_EndcapRegion;
	Float_t         MET_Calib_etx_ForwardReg;
	Float_t         MET_Calib_ety_ForwardReg;
	Float_t         MET_Calib_sumet_ForwardReg;
	Float_t         MET_Calib_phi_ForwardReg;
	Float_t         MET_Truth_NonInt_etx;
	Float_t         MET_Truth_NonInt_ety;
	Float_t         MET_Truth_NonInt_phi;
	Float_t         MET_Truth_NonInt_et;
	Float_t         MET_Truth_NonInt_sumet;
	Float_t         MET_Truth_Int_phi;
	Float_t         MET_Truth_IntCentral_phi;
	Float_t         MET_Truth_IntFwd_phi;
	Float_t         MET_Truth_IntOutCover_phi;
	Float_t         MET_Truth_IntMuons_phi;
	Float_t         MET_Truth_Int_et;
	Float_t         MET_Truth_IntCentral_et;
	Float_t         MET_Truth_IntFwd_et;
	Float_t         MET_Truth_IntOutCover_et;
	Float_t         MET_Truth_IntMuons_et;
	Float_t         MET_Truth_Int_sumet;
	Float_t         MET_Truth_IntCentral_sumet;
	Float_t         MET_Truth_IntFwd_sumet;
	Float_t         MET_Truth_IntOutCover_sumet;
	Float_t         MET_Truth_IntMuons_sumet;
	Float_t         MET_Truth_PileUp_NonInt_etx;
	Float_t         MET_Truth_PileUp_NonInt_ety;
	Float_t         MET_Truth_PileUp_NonInt_phi;
	Float_t         MET_Truth_PileUp_NonInt_et;
	Float_t         MET_Truth_PileUp_NonInt_sumet;
	Float_t         MET_Truth_PileUp_Int_etx;
	Float_t         MET_Truth_PileUp_Int_ety;
	Float_t         MET_Truth_PileUp_IntCentral_etx;
	Float_t         MET_Truth_PileUp_IntCentral_ety;
	Float_t         MET_Truth_PileUp_IntFwd_etx;
	Float_t         MET_Truth_PileUp_IntFwd_ety;
	Float_t         MET_Truth_PileUp_IntOutCover_etx;
	Float_t         MET_Truth_PileUp_IntOutCover_ety;
	Float_t         MET_Truth_PileUp_IntMuons_etx;
	Float_t         MET_Truth_PileUp_IntMuons_ety;
	Float_t         MET_Truth_PileUp_Int_phi;
	Float_t         MET_Truth_PileUp_IntCentral_phi;
	Float_t         MET_Truth_PileUp_IntFwd_phi;
	Float_t         MET_Truth_PileUp_IntOutCover_phi;
	Float_t         MET_Truth_PileUp_IntMuons_phi;
	Float_t         MET_Truth_PileUp_Int_et;
	Float_t         MET_Truth_PileUp_IntCentral_et;
	Float_t         MET_Truth_PileUp_IntFwd_et;
	Float_t         MET_Truth_PileUp_IntOutCover_et;
	Float_t         MET_Truth_PileUp_IntMuons_et;
	Float_t         MET_Truth_PileUp_Int_sumet;
	Float_t         MET_Truth_PileUp_IntCentral_sumet;
	Float_t         MET_Truth_PileUp_IntFwd_sumet;
	Float_t         MET_Truth_PileUp_IntOutCover_sumet;
	Float_t         MET_Truth_PileUp_IntMuons_sumet;
	Float_t         MET_DM_Crack1_etx;
	Float_t         MET_DM_Crack1_ety;
	Float_t         MET_DM_Crack1_phi;
	Float_t         MET_DM_Crack1_et;
	Float_t         MET_DM_Crack1_sumet;
	Float_t         MET_DM_Crack2_etx;
	Float_t         MET_DM_Crack2_ety;
	Float_t         MET_DM_Crack2_phi;
	Float_t         MET_DM_Crack2_et;
	Float_t         MET_DM_Crack2_sumet;
	Float_t         MET_DM_All_etx;
	Float_t         MET_DM_All_ety;
	Float_t         MET_DM_All_phi;
	Float_t         MET_DM_All_et;
	Float_t         MET_DM_All_sumet;
	Float_t         MET_DM_Cryo_etx;
	Float_t         MET_DM_Cryo_ety;
	Float_t         MET_DM_Cryo_phi;
	Float_t         MET_DM_Cryo_et;
	Float_t         MET_DM_Cryo_sumet;
	Float_t         METJetsInfo_JetPtWeightedEventEMFraction;
	Float_t         METJetsInfo_JetPtWeightedNumAssociatedTracks;
	Float_t         METJetsInfo_JetPtWeightedSize;
	Float_t         METJetsInfo_LeadingJetEt;
	Float_t         METJetsInfo_LeadingJetEta;
	
	Int_t           vxp_n;
	vector<float>   *vxp_x;
	vector<float>   *vxp_y;
	vector<float>   *vxp_z;
	vector<float>   *vxp_cov_x;
	vector<float>   *vxp_cov_y;
	vector<float>   *vxp_cov_z;
	vector<float>   *vxp_chi2;
	vector<int>     *vxp_ndof;
	vector<float>   *vxp_px;
	vector<float>   *vxp_py;
	vector<float>   *vxp_pz;
	vector<float>   *vxp_E;
	vector<float>   *vxp_m;
	vector<int>     *vxp_nTracks;
	vector<float>   *vxp_sumPt;
	vector<int>     *vxp_type;
	vector<int>     *vxp_trk_n;
	vector<vector<int> > *vxp_trk_index;
	
	Int_t           muonTruth_n;
	vector<float>   *muonTruth_pt;
	vector<float>   *muonTruth_m;
	vector<float>   *muonTruth_eta;
	vector<float>   *muonTruth_phi;
	vector<float>   *muonTruth_charge;
	vector<int>     *muonTruth_PDGID;
	vector<int>     *muonTruth_barcode;
	vector<int>     *muonTruth_type;
	vector<int>     *muonTruth_origin;
	
	Int_t           mcevt_n;
	vector<int>     *mcevt_signal_process_id;
	vector<int>     *mcevt_event_number;
	vector<double>  *mcevt_event_scale;
	vector<double>  *mcevt_alphaQCD;
	vector<double>  *mcevt_alphaQED;
	vector<int>     *mcevt_pdf_id1;
	vector<int>     *mcevt_pdf_id2;
	vector<double>  *mcevt_pdf_x1;
	vector<double>  *mcevt_pdf_x2;
	vector<double>  *mcevt_pdf_scale;
	vector<double>  *mcevt_pdf1;
	vector<double>  *mcevt_pdf2;
	vector<double>  *mcevt_weight;
	
	Int_t           mc_n;
	vector<float>   *mc_pt;
	vector<float>   *mc_m;
	vector<float>   *mc_eta;
	vector<float>   *mc_phi;
	vector<int>     *mc_status;
	vector<int>     *mc_barcode;
	vector<vector<int> > *mc_parents;
	vector<vector<int> > *mc_children;
	vector<int>     *mc_pdgId;
	vector<float>   *mc_charge;
	vector<float>   *mc_vx_x;
	vector<float>   *mc_vx_y;
	vector<float>   *mc_vx_z;
	vector<vector<int> > *mc_child_index;
	vector<vector<int> > *mc_parent_index;
	
	
	vector<unsigned int> *trig_L1_TAV;
	vector<short>   *trig_L2_passedPhysics;
	vector<short>   *trig_EF_passedPhysics;
	vector<unsigned int> *trig_L1_TBP;
	vector<unsigned int> *trig_L1_TAP;
	vector<short>   *trig_L2_passedRaw;
	vector<short>   *trig_EF_passedRaw;
	Bool_t          trig_L2_truncated;
	Bool_t          trig_EF_truncated;
	vector<short>   *trig_L2_resurrected;
	vector<short>   *trig_EF_resurrected;
	vector<short>   *trig_L2_passedThrough;
	vector<short>   *trig_EF_passedThrough;
	UInt_t          trig_DB_SMK;
	UInt_t          trig_DB_L1PSK;
	UInt_t          trig_DB_HLTPSK;
	Char_t          trig_bgCode;
	
	Int_t           trig_L1_mu_n;
	vector<float>   *trig_L1_mu_pt;
	vector<float>   *trig_L1_mu_eta;
	vector<float>   *trig_L1_mu_phi;
	vector<string>  *trig_L1_mu_thrName;
	Int_t           trig_L2_muonfeature_n;
	vector<float>   *trig_L2_muonfeature_pt;
	vector<float>   *trig_L2_muonfeature_eta;
	vector<float>   *trig_L2_muonfeature_phi;
	Int_t           trig_L2_muonfeaturedetails_n;
	Int_t           trig_L2_combmuonfeature_n;
	vector<float>   *trig_L2_combmuonfeature_pt;
	vector<float>   *trig_L2_combmuonfeature_eta;
	vector<float>   *trig_L2_combmuonfeature_phi;
	vector<int>     *trig_L2_combmuonfeature_idscantrk_index;
	vector<int>     *trig_L2_combmuonfeature_sitracktrk_index;
	Int_t           trig_L2_isomuonfeature_n;
	vector<float>   *trig_L2_isomuonfeature_pt;
	vector<float>   *trig_L2_isomuonfeature_eta;
	vector<float>   *trig_L2_isomuonfeature_phi;
	vector<float>   *trig_L2_isomuonfeature_EtInnerConeEC ;
	vector<float>   *trig_L2_isomuonfeature_EtOuterConeEC;
	vector<float>   *trig_L2_isomuonfeature_EtInnerConeHC;
	vector<float>   *trig_L2_isomuonfeature_EtOuterConeHC;
	vector<int>     *trig_L2_isomuonfeature_NTracksCone;
	vector<float>   *trig_L2_isomuonfeature_SumPtTracksCone;
	vector<float>   *trig_L2_isomuonfeature_PtMuTracksCone;
	Int_t           trig_L2_tilemufeature_n;
	vector<float>   *trig_L2_tilemufeature_eta;
	vector<float>   *trig_L2_tilemufeature_phi;
	Int_t           trig_L2_tiletrackmufeature_n;
	vector<float>   *trig_L2_tiletrackmufeature_pt;
	vector<float>   *trig_L2_tiletrackmufeature_eta;
	vector<float>   *trig_L2_tiletrackmufeature_phi;
	vector<int>     *trig_L2_tiletrackmufeature_tilemu_index;
	vector<int>     *trig_L2_tiletrackmufeature_idtrk_algorithmId;
	vector<short>   *trig_L2_tiletrackmufeature_idtrk_trackStatus;
	vector<float>   *trig_L2_tiletrackmufeature_idtrk_chi2Ndof;
	vector<float>   *trig_L2_tiletrackmufeature_idtrk_idtrkfitpar_a0;
	vector<float>   *trig_L2_tiletrackmufeature_idtrk_idtrkfitpar_z0;
	vector<float>   *trig_L2_tiletrackmufeature_idtrk_idtrkfitpar_phi0;
	vector<float>   *trig_L2_tiletrackmufeature_idtrk_idtrkfitpar_eta;
	vector<float>   *trig_L2_tiletrackmufeature_idtrk_idtrkfitpar_pt;
	vector<int>     *trig_L2_tiletrackmufeature_idtrk_idtrkfitpar_hasidtrkfitpar;
	vector<int>     *trig_L2_tiletrackmufeature_idtrk_hasidtrk;
	Int_t           trig_EF_trigmuonef_n;
	vector<int>     *trig_EF_trigmuonef_track_n;
	vector<vector<int> > *trig_EF_trigmuonef_track_MuonType;
	vector<vector<float> > *trig_EF_trigmuonef_track_MS_pt;
	vector<vector<float> > *trig_EF_trigmuonef_track_MS_eta;
	vector<vector<float> > *trig_EF_trigmuonef_track_MS_phi;
	vector<vector<int> > *trig_EF_trigmuonef_track_MS_hasMS;
	vector<vector<float> > *trig_EF_trigmuonef_track_SA_pt;
	vector<vector<float> > *trig_EF_trigmuonef_track_SA_eta;
	vector<vector<float> > *trig_EF_trigmuonef_track_SA_phi;
	vector<vector<int> > *trig_EF_trigmuonef_track_SA_hasSA;
	vector<vector<float> > *trig_EF_trigmuonef_track_CB_pt;
	vector<vector<float> > *trig_EF_trigmuonef_track_CB_eta;
	vector<vector<float> > *trig_EF_trigmuonef_track_CB_phi;
	vector<vector<int> > *trig_EF_trigmuonef_track_CB_hasCB;
	Int_t           trig_EF_trigmugirl_n;
	vector<int>     *trig_EF_trigmugirl_track_n;
	vector<vector<int> > *trig_EF_trigmugirl_track_MuonType;
	vector<vector<float> > *trig_EF_trigmugirl_track_MS_pt;
	vector<vector<float> > *trig_EF_trigmugirl_track_MS_eta;
	vector<vector<float> > *trig_EF_trigmugirl_track_MS_phi;
	vector<vector<int> > *trig_EF_trigmugirl_track_MS_hasMS;
	vector<vector<float> > *trig_EF_trigmugirl_track_SA_pt;
	vector<vector<float> > *trig_EF_trigmugirl_track_SA_eta;
	vector<vector<float> > *trig_EF_trigmugirl_track_SA_phi;
	vector<vector<int> > *trig_EF_trigmugirl_track_SA_hasSA;
	vector<vector<float> > *trig_EF_trigmugirl_track_CB_pt;
	vector<vector<float> > *trig_EF_trigmugirl_track_CB_eta;
	vector<vector<float> > *trig_EF_trigmugirl_track_CB_phi;
	vector<vector<int> > *trig_EF_trigmugirl_track_CB_hasCB;
	Int_t           trig_L2_sitrack_muon_n;
	vector<int>     *trig_L2_sitrack_muon_algorithmId;
	vector<short>   *trig_L2_sitrack_muon_trackStatus;
	vector<float>   *trig_L2_sitrack_muon_chi2Ndof;
	vector<float>   *trig_L2_sitrack_muon_a0;
	vector<float>   *trig_L2_sitrack_muon_z0;
	vector<float>   *trig_L2_sitrack_muon_phi0;
	vector<float>   *trig_L2_sitrack_muon_eta;
	vector<float>   *trig_L2_sitrack_muon_pt;
	Int_t           trig_L2_idscan_muon_n;
	vector<int>     *trig_L2_idscan_muon_algorithmId;
	vector<short>   *trig_L2_idscan_muon_trackStatus;
	vector<float>   *trig_L2_idscan_muon_chi2Ndof;
	vector<float>   *trig_L2_idscan_muon_a0;
	vector<float>   *trig_L2_idscan_muon_z0;
	vector<float>   *trig_L2_idscan_muon_phi0;
	vector<float>   *trig_L2_idscan_muon_eta;
	vector<float>   *trig_L2_idscan_muon_pt;
	Int_t           trig_L2_sitrack_isomuon_n;
	vector<int>     *trig_L2_sitrack_isomuon_algorithmId;
	vector<short>   *trig_L2_sitrack_isomuon_trackStatus;
	vector<float>   *trig_L2_sitrack_isomuon_chi2Ndof;
	vector<float>   *trig_L2_sitrack_isomuon_a0;
	vector<float>   *trig_L2_sitrack_isomuon_z0;
	vector<float>   *trig_L2_sitrack_isomuon_phi0;
	vector<float>   *trig_L2_sitrack_isomuon_eta;
	vector<float>   *trig_L2_sitrack_isomuon_pt;
	Int_t           trig_L2_idscan_isomuon_n;
	vector<int>     *trig_L2_idscan_isomuon_algorithmId;
	vector<short>   *trig_L2_idscan_isomuon_trackStatus;
	vector<float>   *trig_L2_idscan_isomuon_chi2Ndof;
	vector<float>   *trig_L2_idscan_isomuon_a0;
	vector<float>   *trig_L2_idscan_isomuon_z0;
	vector<float>   *trig_L2_idscan_isomuon_phi0;
	vector<float>   *trig_L2_idscan_isomuon_eta;
	vector<float>   *trig_L2_idscan_isomuon_pt;
	Int_t           trig_RoI_L2_mu_n;
	vector<short>   *trig_RoI_L2_mu_type;
	vector<short>   *trig_RoI_L2_mu_lastStep;
	vector<int>     *trig_RoI_L2_mu_MuonFeature;
	vector<int>     *trig_RoI_L2_mu_MuonFeatureStatus;
	vector<int>     *trig_RoI_L2_mu_MuonFeatureDetails;
	vector<int>     *trig_RoI_L2_mu_MuonFeatureDetailsStatus;
	vector<int>     *trig_RoI_L2_mu_CombinedMuonFeature;
	vector<int>     *trig_RoI_L2_mu_CombinedMuonFeatureStatus;
	vector<int>     *trig_RoI_L2_mu_IsoMuonFeature;
	vector<int>     *trig_RoI_L2_mu_IsoMuonFeatureStatus;
	vector<int>     *trig_RoI_L2_mu_Muon_ROI;
	vector<int>     *trig_RoI_L2_mu_Muon_ROIStatus;
	vector<vector<int> > *trig_RoI_L2_mu_TrigInDetTrackCollection_TrigSiTrack_Muon;
	vector<vector<int> > *trig_RoI_L2_mu_TrigInDetTrackCollection_TrigSiTrack_MuonStatus;
	vector<vector<int> > *trig_RoI_L2_mu_TrigInDetTrackCollection_TrigIDSCAN_Muon;
	vector<vector<int> > *trig_RoI_L2_mu_TrigInDetTrackCollection_TrigIDSCAN_MuonStatus;
	vector<vector<int> > *trig_RoI_L2_mu_TrigInDetTrackCollection_TrigSiTrack_muonIso;
	vector<vector<int> > *trig_RoI_L2_mu_TrigInDetTrackCollection_TrigSiTrack_muonIsoStatus;
	vector<vector<int> > *trig_RoI_L2_mu_TrigInDetTrackCollection_TrigIDSCAN_muonIso;
	vector<vector<int> > *trig_RoI_L2_mu_TrigInDetTrackCollection_TrigIDSCAN_muonIsoStatus;
	Int_t           trig_RoI_L2_TileMu_n;
	vector<short>   *trig_RoI_L2_TileMu_type;
	vector<short>   *trig_RoI_L2_TileMu_lastStep;
	vector<int>     *trig_RoI_L2_TileMu_TileMuFeature;
	vector<int>     *trig_RoI_L2_TileMu_TileMuFeatureStatus;
	vector<int>     *trig_RoI_L2_TileMu_TileTrackMuFeature;
	vector<int>     *trig_RoI_L2_TileMu_TileTrackMuFeatureStatus;
	vector<int>     *trig_RoI_L2_TileMu_Muon_ROI;
	vector<int>     *trig_RoI_L2_TileMu_Muon_ROIStatus;
	vector<vector<int> > *trig_RoI_L2_TileMu_TrigInDetTrackCollection_TrigSiTrack_Tile;
	vector<vector<int> > *trig_RoI_L2_TileMu_TrigInDetTrackCollection_TrigSiTrack_TileStatus;
	vector<vector<int> > *trig_RoI_L2_TileMu_TrigInDetTrackCollection_TrigIDSCAN_Tile;
	vector<vector<int> > *trig_RoI_L2_TileMu_TrigInDetTrackCollection_TrigIDSCAN_TileStatus;
	Int_t           trig_RoI_EF_mu_n;
	vector<short>   *trig_RoI_EF_mu_type;
	vector<short>   *trig_RoI_EF_mu_lastStep;
	vector<int>     *trig_RoI_EF_mu_Muon_ROI;
	vector<int>     *trig_RoI_EF_mu_Muon_ROIStatus;
	vector<vector<int> > *trig_RoI_EF_mu_TrackCollection_InDetTrigTrackSlimmer_Muon_EFID;
	vector<vector<int> > *trig_RoI_EF_mu_TrackCollection_InDetTrigTrackSlimmer_Muon_EFIDStatus;
	vector<vector<int> > *trig_RoI_EF_mu_TrigMuonEFInfoContainer;
	vector<vector<int> > *trig_RoI_EF_mu_TrigMuonEFInfoContainerStatus;
	vector<vector<int> > *trig_RoI_EF_mu_TrigMuonEFInfoContainer_MuGirl;
	vector<vector<int> > *trig_RoI_EF_mu_TrigMuonEFInfoContainer_MuGirlStatus;
	vector<vector<int> > *trig_RoI_EF_mu_TrigMuonEFInfoContainer_MuTagIMO_EF;
	vector<vector<int> > *trig_RoI_EF_mu_TrigMuonEFInfoContainer_MuTagIMO_EFStatus;
	Int_t           trig_RoI_EF_TileMu_n;
	vector<short>   *trig_RoI_EF_TileMu_type;
	vector<short>   *trig_RoI_EF_TileMu_lastStep;
	vector<int>     *trig_RoI_EF_TileMu_Muon_ROI;
	vector<int>     *trig_RoI_EF_TileMu_Muon_ROIStatus;
	vector<vector<int> > *trig_RoI_EF_TileMu_TrigMuonEFContainer;
	vector<vector<int> > *trig_RoI_EF_TileMu_TrigMuonEFContainerStatus;
	vector<vector<int> > *trig_RoI_EF_TileMu_TrigMuonEFInfoContainer;
	vector<vector<int> > *trig_RoI_EF_TileMu_TrigMuonEFInfoContainerStatus;
	vector<vector<int> > *trig_RoI_EF_TileMu_TrigMuonEFInfoContainer_MuGirl;
	vector<vector<int> > *trig_RoI_EF_TileMu_TrigMuonEFInfoContainer_MuGirlStatus;
	vector<vector<int> > *trig_RoI_EF_TileMu_TrigMuonEFInfoContainer_MuTagIMO_EF;
	vector<vector<int> > *trig_RoI_EF_TileMu_TrigMuonEFInfoContainer_MuTagIMO_EFStatus;
	
	Float_t         trig_L2_met_MEx;
	Float_t         trig_L2_met_MEy;
	Float_t         trig_L2_met_MEz;
	Float_t         trig_L2_met_sumEt;
	Float_t         trig_L2_met_sumE;
	Int_t           trig_L2_met_flag;
	vector<string>  *trig_L2_met_nameOfComponent;
	vector<float>   *trig_L2_met_MExComponent;
	vector<float>   *trig_L2_met_MEyComponent;
	vector<float>   *trig_L2_met_MEzComponent;
	vector<float>   *trig_L2_met_sumEtComponent;
	vector<float>   *trig_L2_met_sumEComponent;
	vector<float>   *trig_L2_met_componentCalib0;
	vector<float>   *trig_L2_met_componentCalib1;
	vector<short>   *trig_L2_met_sumOfSigns;
	vector<unsigned short> *trig_L2_met_usedChannels;
	vector<short>   *trig_L2_met_status;
	Float_t         trig_EF_met_MEx;
	Float_t         trig_EF_met_MEy;
	Float_t         trig_EF_met_MEz;
	Float_t         trig_EF_met_sumEt;
	Float_t         trig_EF_met_sumE;
	Int_t           trig_EF_met_flag;
	vector<string>  *trig_EF_met_nameOfComponent;
	vector<float>   *trig_EF_met_MExComponent;
	vector<float>   *trig_EF_met_MEyComponent;
	vector<float>   *trig_EF_met_MEzComponent;
	vector<float>   *trig_EF_met_sumEtComponent;
	vector<float>   *trig_EF_met_sumEComponent;
	vector<float>   *trig_EF_met_componentCalib0;
	vector<float>   *trig_EF_met_componentCalib1;
	vector<short>   *trig_EF_met_sumOfSigns;
	vector<unsigned short> *trig_EF_met_usedChannels;
	vector<short>   *trig_EF_met_status;

	// List of branches
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
	
	TBranch        *b_EF_2mu0_NoAlg;   //!
	TBranch        *b_EF_2mu10;   //!
	TBranch        *b_EF_2mu10_NoAlg;   //!
	TBranch        *b_EF_2mu4;   //!
	TBranch        *b_EF_2mu4_Bmumu;   //!
	TBranch        *b_EF_2mu4_Bmumux;   //!
	TBranch        *b_EF_2mu4_DiMu;   //!
	TBranch        *b_EF_2mu4_DiMu_SiTrk;   //!
	TBranch        *b_EF_2mu4_DiMu_noVtx;   //!
	TBranch        *b_EF_2mu4_DiMu_noVtx_noOS;   //!
	TBranch        *b_EF_2mu4_Jpsimumu;   //!
	TBranch        *b_EF_2mu4_Jpsimumu_IDTrkNoCut;   //!
	TBranch        *b_EF_2mu4_Upsimumu;   //!
	TBranch        *b_EF_2mu6;   //!
	TBranch        *b_EF_2mu6_Bmumu;   //!
	TBranch        *b_EF_2mu6_Bmumux;   //!
	TBranch        *b_EF_2mu6_DiMu;   //!
	TBranch        *b_EF_2mu6_Jpsimumu;   //!
	TBranch        *b_EF_2mu6_MG;   //!
	TBranch        *b_EF_2mu6_NoAlg;   //!
	TBranch        *b_EF_2mu6_Upsimumu;   //!
	TBranch        *b_EF_2mu6_g10_loose;   //!
	
	TBranch        *b_EF_mu0_NoAlg;   //!
	TBranch        *b_EF_mu0_comm_NoAlg;   //!
	TBranch        *b_EF_mu0_comm_empty_NoAlg;   //!
	TBranch        *b_EF_mu0_comm_firstempty_NoAlg;   //!
	TBranch        *b_EF_mu0_comm_unpaired_iso_NoAlg;   //!
	TBranch        *b_EF_mu0_comm_unpaired_noniso_NoAlg;   //!
	TBranch        *b_EF_mu0_empty_NoAlg;   //!
	TBranch        *b_EF_mu0_firstempty_NoAlg;   //!
	TBranch        *b_EF_mu0_missingRoi;   //!
	TBranch        *b_EF_mu0_outOfTime1;   //!
	TBranch        *b_EF_mu0_outOfTime2;   //!
	TBranch        *b_EF_mu0_rpcOnly;   //!
	TBranch        *b_EF_mu0_unpaired_iso_NoAlg;   //!
	TBranch        *b_EF_mu0_unpaired_noniso_NoAlg;   //!
	TBranch        *b_EF_mu10;   //!
	TBranch        *b_EF_mu10_Ecut12;   //!
	TBranch        *b_EF_mu10_Ecut123;   //!
	TBranch        *b_EF_mu10_Ecut13;   //!
	TBranch        *b_EF_mu10_IDTrkNoCut;   //!
	TBranch        *b_EF_mu10_MG;   //!
	TBranch        *b_EF_mu10_MSonly;   //!
	TBranch        *b_EF_mu10_MSonly_Ecut12;   //!
	TBranch        *b_EF_mu10_MSonly_Ecut123;   //!
	TBranch        *b_EF_mu10_MSonly_Ecut13;   //!
	TBranch        *b_EF_mu10_MSonly_tight;   //!
	TBranch        *b_EF_mu10_NoAlg;   //!
	TBranch        *b_EF_mu10_SiTrk;   //!
	TBranch        *b_EF_mu10_j30;   //!
	TBranch        *b_EF_mu10_tight;   //!
	TBranch        *b_EF_mu10i_loose;   //!
	TBranch        *b_EF_mu13;   //!
	TBranch        *b_EF_mu13_MG;   //!
	TBranch        *b_EF_mu13_MG_tight;   //!
	TBranch        *b_EF_mu13_tight;   //!
	TBranch        *b_EF_mu15;   //!
	TBranch        *b_EF_mu15_MG;   //!
	TBranch        *b_EF_mu15_NoAlg;   //!
	TBranch        *b_EF_mu20;   //!
	TBranch        *b_EF_mu20_MSonly;   //!
	TBranch        *b_EF_mu20_NoAlg;   //!
	TBranch        *b_EF_mu20_passHLT;   //!
	TBranch        *b_EF_mu20_slow;   //!
	TBranch        *b_EF_mu30_MSonly;   //!
	TBranch        *b_EF_mu4;   //!
	TBranch        *b_EF_mu40_MSonly;   //!
	TBranch        *b_EF_mu4_Bmumu;   //!
	TBranch        *b_EF_mu4_BmumuX;   //!
	TBranch        *b_EF_mu4_DiMu;   //!
	TBranch        *b_EF_mu4_DiMu_FS;   //!
	TBranch        *b_EF_mu4_DiMu_FS_noOS;   //!
	TBranch        *b_EF_mu4_DiMu_MG;   //!
	TBranch        *b_EF_mu4_DiMu_MG_FS;   //!
	TBranch        *b_EF_mu4_DiMu_SiTrk;   //!
	TBranch        *b_EF_mu4_DiMu_SiTrk_FS;   //!
	TBranch        *b_EF_mu4_DiMu_noOS;   //!
	TBranch        *b_EF_mu4_IDTrkNoCut;   //!
	TBranch        *b_EF_mu4_Jpsie5e3;   //!
	TBranch        *b_EF_mu4_Jpsie5e3_FS;   //!
	TBranch        *b_EF_mu4_Jpsie5e3_SiTrk;   //!
	TBranch        *b_EF_mu4_Jpsie5e3_SiTrk_FS;   //!
	TBranch        *b_EF_mu4_Jpsimumu;   //!
	TBranch        *b_EF_mu4_Jpsimumu_FS;   //!
	TBranch        *b_EF_mu4_Jpsimumu_SiTrk_FS;   //!
	TBranch        *b_EF_mu4_L1J10_matched;   //!
	TBranch        *b_EF_mu4_L1J15_matched;   //!
	TBranch        *b_EF_mu4_L1J30_matched;   //!
	TBranch        *b_EF_mu4_L1J55_matched;   //!
	TBranch        *b_EF_mu4_L1J5_matched;   //!
	TBranch        *b_EF_mu4_L2MSonly_EFFS_passL2;   //!
	TBranch        *b_EF_mu4_MG;   //!
	TBranch        *b_EF_mu4_MSonly;   //!
	TBranch        *b_EF_mu4_MSonly_EFFS_passL2;   //!
	TBranch        *b_EF_mu4_MSonly_MB2_noL2_EFFS;   //!
	TBranch        *b_EF_mu4_MSonly_cosmic;   //!
	TBranch        *b_EF_mu4_MSonly_outOfTime;   //!
	TBranch        *b_EF_mu4_MV;   //!
	TBranch        *b_EF_mu4_SiTrk;   //!
	TBranch        *b_EF_mu4_Trk_Jpsi;   //!
	TBranch        *b_EF_mu4_Trk_Jpsi_FS;   //!
	TBranch        *b_EF_mu4_Trk_Jpsi_loose;   //!
	TBranch        *b_EF_mu4_Trk_Upsi_FS;   //!
	TBranch        *b_EF_mu4_Trk_Upsi_loose_FS;   //!
	TBranch        *b_EF_mu4_Upsimumu_FS;   //!
	TBranch        *b_EF_mu4_Upsimumu_SiTrk_FS;   //!
	TBranch        *b_EF_mu4_comm_MSonly_cosmic;   //!
	TBranch        *b_EF_mu4_comm_cosmic;   //!
	TBranch        *b_EF_mu4_comm_firstempty;   //!
	TBranch        *b_EF_mu4_comm_unpaired_iso;   //!
	TBranch        *b_EF_mu4_cosmic;   //!
	TBranch        *b_EF_mu4_firstempty;   //!
	TBranch        *b_EF_mu4_j20;   //!
	TBranch        *b_EF_mu4_j20_jetNoEF;   //!
	TBranch        *b_EF_mu4_j30;   //!
	TBranch        *b_EF_mu4_j30_jetNoEF;   //!
	TBranch        *b_EF_mu4_mu6;   //!
	TBranch        *b_EF_mu4_muCombTag;   //!
	TBranch        *b_EF_mu4_tile;   //!
	TBranch        *b_EF_mu4_tile_cosmic;   //!
	TBranch        *b_EF_mu4_unpaired_iso;   //!
	TBranch        *b_EF_mu4mu6_Bmumu;   //!
	TBranch        *b_EF_mu4mu6_BmumuX;   //!
	TBranch        *b_EF_mu4mu6_DiMu;   //!
	TBranch        *b_EF_mu4mu6_Jpsimumu;   //!
	TBranch        *b_EF_mu4mu6_Jpsimumu_IDTrkNoCut;   //!
	TBranch        *b_EF_mu4mu6_Upsimumu;   //!
	TBranch        *b_EF_mu6;   //!
	TBranch        *b_EF_mu6_Bmumu;   //!
	TBranch        *b_EF_mu6_BmumuX;   //!
	TBranch        *b_EF_mu6_DiMu;   //!
	TBranch        *b_EF_mu6_Ecut12;   //!
	TBranch        *b_EF_mu6_Ecut123;   //!
	TBranch        *b_EF_mu6_Ecut13;   //!
	TBranch        *b_EF_mu6_Ecut2;   //!
	TBranch        *b_EF_mu6_Ecut3;   //!
	TBranch        *b_EF_mu6_IDTrkNoCut;   //!
	TBranch        *b_EF_mu6_Jpsie5e3;   //!
	TBranch        *b_EF_mu6_Jpsie5e3_FS;   //!
	TBranch        *b_EF_mu6_Jpsie5e3_SiTrk;   //!
	TBranch        *b_EF_mu6_Jpsie5e3_SiTrk_FS;   //!
	TBranch        *b_EF_mu6_Jpsimumu;   //!
	TBranch        *b_EF_mu6_MG;   //!
	TBranch        *b_EF_mu6_MSonly;   //!
	TBranch        *b_EF_mu6_MSonly_Ecut12;   //!
	TBranch        *b_EF_mu6_MSonly_Ecut123;   //!
	TBranch        *b_EF_mu6_MSonly_Ecut13;   //!
	TBranch        *b_EF_mu6_MSonly_Ecut2;   //!
	TBranch        *b_EF_mu6_MSonly_Ecut3;   //!
	TBranch        *b_EF_mu6_MSonly_outOfTime;   //!
	TBranch        *b_EF_mu6_NoAlg;   //!
	TBranch        *b_EF_mu6_SiTrk;   //!
	TBranch        *b_EF_mu6_Trk_Jpsi;   //!
	TBranch        *b_EF_mu6_Upsimumu_FS;   //!
	TBranch        *b_EF_mu6_muCombTag;   //!
	
	TBranch        *b_L1_2MU0;   //!
	TBranch        *b_L1_2MU0_FIRSTEMPTY;   //!
	TBranch        *b_L1_2MU0_MU6;   //!
	TBranch        *b_L1_2MU10;   //!
	TBranch        *b_L1_2MU20;   //!
	TBranch        *b_L1_2MU6;   //!
	TBranch        *b_L1_2MU6_EM5;   //!
	
	TBranch        *b_L1_MU0;   //!
	TBranch        *b_L1_MU0_COMM;   //!
	TBranch        *b_L1_MU0_COMM_EMPTY;   //!
	TBranch        *b_L1_MU0_COMM_FIRSTEMPTY;   //!
	TBranch        *b_L1_MU0_COMM_UNPAIRED_ISO;   //!
	TBranch        *b_L1_MU0_COMM_UNPAIRED_NONISO;   //!
	TBranch        *b_L1_MU0_EM3;   //!
	TBranch        *b_L1_MU0_EMPTY;   //!
	TBranch        *b_L1_MU0_FIRSTEMPTY;   //!
	TBranch        *b_L1_MU0_J10;   //!
	TBranch        *b_L1_MU0_J15;   //!
	TBranch        *b_L1_MU0_J30;   //!
	TBranch        *b_L1_MU0_J5;   //!
	TBranch        *b_L1_MU0_J55;   //!
	TBranch        *b_L1_MU0_MV;   //!
	TBranch        *b_L1_MU0_UNPAIRED_ISO;   //!
	TBranch        *b_L1_MU0_UNPAIRED_NONISO;   //!
	TBranch        *b_L1_MU10;   //!
	TBranch        *b_L1_MU10_FIRSTEMPTY;   //!
	TBranch        *b_L1_MU10_J10;   //!
	TBranch        *b_L1_MU15;   //!
	TBranch        *b_L1_MU20;   //!
	TBranch        *b_L1_MU6;   //!
	TBranch        *b_L1_MU6_EM3;   //!
	TBranch        *b_L1_MU6_FIRSTEMPTY;   //!
	TBranch        *b_L1_MU6_J5;   //!
	
	TBranch        *b_L2_2mu0_NoAlg;   //!
	TBranch        *b_L2_2mu10;   //!
	TBranch        *b_L2_2mu10_NoAlg;   //!
	TBranch        *b_L2_2mu4;   //!
	TBranch        *b_L2_2mu4_Bmumu;   //!
	TBranch        *b_L2_2mu4_Bmumux;   //!
	TBranch        *b_L2_2mu4_DiMu;   //!
	TBranch        *b_L2_2mu4_DiMu_SiTrk;   //!
	TBranch        *b_L2_2mu4_DiMu_noVtx;   //!
	TBranch        *b_L2_2mu4_DiMu_noVtx_noOS;   //!
	TBranch        *b_L2_2mu4_Jpsimumu;   //!
	TBranch        *b_L2_2mu4_Jpsimumu_IDTrkNoCut;   //!
	TBranch        *b_L2_2mu4_Upsimumu;   //!
	TBranch        *b_L2_2mu6;   //!
	TBranch        *b_L2_2mu6_Bmumu;   //!
	TBranch        *b_L2_2mu6_Bmumux;   //!
	TBranch        *b_L2_2mu6_DiMu;   //!
	TBranch        *b_L2_2mu6_Jpsimumu;   //!
	TBranch        *b_L2_2mu6_MG;   //!
	TBranch        *b_L2_2mu6_NoAlg;   //!
	TBranch        *b_L2_2mu6_Upsimumu;   //!
	TBranch        *b_L2_2mu6_g10_loose;   //!
	
	TBranch        *b_L2_mu0_NoAlg;   //!
	TBranch        *b_L2_mu0_comm_NoAlg;   //!
	TBranch        *b_L2_mu0_comm_empty_NoAlg;   //!
	TBranch        *b_L2_mu0_comm_firstempty_NoAlg;   //!
	TBranch        *b_L2_mu0_comm_unpaired_iso_NoAlg;   //!
	TBranch        *b_L2_mu0_comm_unpaired_noniso_NoAlg;   //!
	TBranch        *b_L2_mu0_empty_NoAlg;   //!
	TBranch        *b_L2_mu0_firstempty_NoAlg;   //!
	TBranch        *b_L2_mu0_missingRoi;   //!
	TBranch        *b_L2_mu0_outOfTime1;   //!
	TBranch        *b_L2_mu0_outOfTime2;   //!
	TBranch        *b_L2_mu0_rpcOnly;   //!
	TBranch        *b_L2_mu0_unpaired_iso_NoAlg;   //!
	TBranch        *b_L2_mu0_unpaired_noniso_NoAlg;   //!
	TBranch        *b_L2_mu10;   //!
	TBranch        *b_L2_mu10_Ecut12;   //!
	TBranch        *b_L2_mu10_Ecut123;   //!
	TBranch        *b_L2_mu10_Ecut13;   //!
	TBranch        *b_L2_mu10_IDTrkNoCut;   //!
	TBranch        *b_L2_mu10_MG;   //!
	TBranch        *b_L2_mu10_MSonly;   //!
	TBranch        *b_L2_mu10_MSonly_Ecut12;   //!
	TBranch        *b_L2_mu10_MSonly_Ecut123;   //!
	TBranch        *b_L2_mu10_MSonly_Ecut13;   //!
	TBranch        *b_L2_mu10_MSonly_tight;   //!
	TBranch        *b_L2_mu10_NoAlg;   //!
	TBranch        *b_L2_mu10_SiTrk;   //!
	TBranch        *b_L2_mu10_j30;   //!
	TBranch        *b_L2_mu10_tight;   //!
	TBranch        *b_L2_mu10i_loose;   //!
	TBranch        *b_L2_mu13;   //!
	TBranch        *b_L2_mu13_MG;   //!
	TBranch        *b_L2_mu13_MG_tight;   //!
	TBranch        *b_L2_mu13_tight;   //!
	TBranch        *b_L2_mu15;   //!
	TBranch        *b_L2_mu15_MG;   //!
	TBranch        *b_L2_mu15_NoAlg;   //!
	TBranch        *b_L2_mu20;   //!
	TBranch        *b_L2_mu20_MSonly;   //!
	TBranch        *b_L2_mu20_NoAlg;   //!
	TBranch        *b_L2_mu20_passHLT;   //!
	TBranch        *b_L2_mu20_slow;   //!
	TBranch        *b_L2_mu30_MSonly;   //!
	TBranch        *b_L2_mu4;   //!
	TBranch        *b_L2_mu40_MSonly;   //!
	TBranch        *b_L2_mu4_Bmumu;   //!
	TBranch        *b_L2_mu4_BmumuX;   //!
	TBranch        *b_L2_mu4_DiMu;   //!
	TBranch        *b_L2_mu4_DiMu_FS;   //!
	TBranch        *b_L2_mu4_DiMu_FS_noOS;   //!
	TBranch        *b_L2_mu4_DiMu_MG;   //!
	TBranch        *b_L2_mu4_DiMu_MG_FS;   //!
	TBranch        *b_L2_mu4_DiMu_SiTrk;   //!
	TBranch        *b_L2_mu4_DiMu_SiTrk_FS;   //!
	TBranch        *b_L2_mu4_DiMu_noOS;   //!
	TBranch        *b_L2_mu4_IDTrkNoCut;   //!
	TBranch        *b_L2_mu4_Jpsie5e3;   //!
	TBranch        *b_L2_mu4_Jpsie5e3_FS;   //!
	TBranch        *b_L2_mu4_Jpsie5e3_SiTrk;   //!
	TBranch        *b_L2_mu4_Jpsie5e3_SiTrk_FS;   //!
	TBranch        *b_L2_mu4_Jpsimumu;   //!
	TBranch        *b_L2_mu4_Jpsimumu_FS;   //!
	TBranch        *b_L2_mu4_Jpsimumu_SiTrk_FS;   //!
	TBranch        *b_L2_mu4_L1J10_matched;   //!
	TBranch        *b_L2_mu4_L1J15_matched;   //!
	TBranch        *b_L2_mu4_L1J30_matched;   //!
	TBranch        *b_L2_mu4_L1J55_matched;   //!
	TBranch        *b_L2_mu4_L1J5_matched;   //!
	TBranch        *b_L2_mu4_L2MSonly_EFFS_passL2;   //!
	TBranch        *b_L2_mu4_MG;   //!
	TBranch        *b_L2_mu4_MSonly;   //!
	TBranch        *b_L2_mu4_MSonly_EFFS_passL2;   //!
	TBranch        *b_L2_mu4_MSonly_MB2_noL2_EFFS;   //!
	TBranch        *b_L2_mu4_MSonly_cosmic;   //!
	TBranch        *b_L2_mu4_MSonly_outOfTime;   //!
	TBranch        *b_L2_mu4_MV;   //!
	TBranch        *b_L2_mu4_SiTrk;   //!
	TBranch        *b_L2_mu4_Trk_Jpsi;   //!
	TBranch        *b_L2_mu4_Trk_Jpsi_FS;   //!
	TBranch        *b_L2_mu4_Trk_Jpsi_loose;   //!
	TBranch        *b_L2_mu4_Trk_Upsi_FS;   //!
	TBranch        *b_L2_mu4_Trk_Upsi_loose_FS;   //!
	TBranch        *b_L2_mu4_Upsimumu_FS;   //!
	TBranch        *b_L2_mu4_Upsimumu_SiTrk_FS;   //!
	TBranch        *b_L2_mu4_comm_MSonly_cosmic;   //!
	TBranch        *b_L2_mu4_comm_cosmic;   //!
	TBranch        *b_L2_mu4_comm_firstempty;   //!
	TBranch        *b_L2_mu4_comm_unpaired_iso;   //!
	TBranch        *b_L2_mu4_cosmic;   //!
	TBranch        *b_L2_mu4_firstempty;   //!
	TBranch        *b_L2_mu4_j20;   //!
	TBranch        *b_L2_mu4_j20_jetNoEF;   //!
	TBranch        *b_L2_mu4_j25;   //!
	TBranch        *b_L2_mu4_mu6;   //!
	TBranch        *b_L2_mu4_muCombTag;   //!
	TBranch        *b_L2_mu4_tile;   //!
	TBranch        *b_L2_mu4_tile_cosmic;   //!
	TBranch        *b_L2_mu4_unpaired_iso;   //!
	TBranch        *b_L2_mu4mu6_Bmumu;   //!
	TBranch        *b_L2_mu4mu6_BmumuX;   //!
	TBranch        *b_L2_mu4mu6_DiMu;   //!
	TBranch        *b_L2_mu4mu6_Jpsimumu;   //!
	TBranch        *b_L2_mu4mu6_Jpsimumu_IDTrkNoCut;   //!
	TBranch        *b_L2_mu4mu6_Upsimumu;   //!
	TBranch        *b_L2_mu6;   //!
	TBranch        *b_L2_mu6_Bmumu;   //!
	TBranch        *b_L2_mu6_BmumuX;   //!
	TBranch        *b_L2_mu6_DiMu;   //!
	TBranch        *b_L2_mu6_Ecut12;   //!
	TBranch        *b_L2_mu6_Ecut123;   //!
	TBranch        *b_L2_mu6_Ecut13;   //!
	TBranch        *b_L2_mu6_Ecut2;   //!
	TBranch        *b_L2_mu6_Ecut3;   //!
	TBranch        *b_L2_mu6_IDTrkNoCut;   //!
	TBranch        *b_L2_mu6_Jpsie5e3;   //!
	TBranch        *b_L2_mu6_Jpsie5e3_FS;   //!
	TBranch        *b_L2_mu6_Jpsie5e3_SiTrk;   //!
	TBranch        *b_L2_mu6_Jpsie5e3_SiTrk_FS;   //!
	TBranch        *b_L2_mu6_Jpsimumu;   //!
	TBranch        *b_L2_mu6_MG;   //!
	TBranch        *b_L2_mu6_MSonly;   //!
	TBranch        *b_L2_mu6_MSonly_Ecut12;   //!
	TBranch        *b_L2_mu6_MSonly_Ecut123;   //!
	TBranch        *b_L2_mu6_MSonly_Ecut13;   //!
	TBranch        *b_L2_mu6_MSonly_Ecut2;   //!
	TBranch        *b_L2_mu6_MSonly_Ecut3;   //!
	TBranch        *b_L2_mu6_MSonly_outOfTime;   //!
	TBranch        *b_L2_mu6_NoAlg;   //!
	TBranch        *b_L2_mu6_SiTrk;   //!
	TBranch        *b_L2_mu6_Trk_Jpsi;   //!
	TBranch        *b_L2_mu6_Upsimumu_FS;   //!
	TBranch        *b_L2_mu6_muCombTag;   //!
	
	TBranch        *b_mu_muid_n;   //!
	TBranch        *b_mu_muid_E;   //!
	TBranch        *b_mu_muid_pt;   //!
	TBranch        *b_mu_muid_m;   //!
	TBranch        *b_mu_muid_eta;   //!
	TBranch        *b_mu_muid_phi;   //!
	TBranch        *b_mu_muid_px;   //!
	TBranch        *b_mu_muid_py;   //!
	TBranch        *b_mu_muid_pz;   //!
	TBranch        *b_mu_muid_charge;   //!
	TBranch        *b_mu_muid_allauthor;   //!
	TBranch        *b_mu_muid_author;   //!
	TBranch        *b_mu_muid_beta;   //!
	TBranch        *b_mu_muid_isMuonLikelihood;   //!
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
	TBranch        *b_mu_muid_etCore;   //!
	TBranch        *b_mu_muid_energyLossType;   //!
	TBranch        *b_mu_muid_caloMuonIdTag;   //!
	TBranch        *b_mu_muid_caloLRLikelihood;   //!
	TBranch        *b_mu_muid_bestMatch;   //!
	TBranch        *b_mu_muid_isStandAloneMuon;   //!
	TBranch        *b_mu_muid_isCombinedMuon;   //!
	TBranch        *b_mu_muid_isLowPtReconstructedMuon;   //!
	TBranch        *b_mu_muid_loose;   //!
	TBranch        *b_mu_muid_medium;   //!
	TBranch        *b_mu_muid_tight;   //!
	TBranch        *b_mu_muid_d0_exPV;   //!
	TBranch        *b_mu_muid_z0_exPV;   //!
	TBranch        *b_mu_muid_phi_exPV;   //!
	TBranch        *b_mu_muid_theta_exPV;   //!
	TBranch        *b_mu_muid_qoverp_exPV;   //!
	TBranch        *b_mu_muid_cb_d0_exPV;   //!
	TBranch        *b_mu_muid_cb_z0_exPV;   //!
	TBranch        *b_mu_muid_cb_phi_exPV;   //!
	TBranch        *b_mu_muid_cb_theta_exPV;   //!
	TBranch        *b_mu_muid_cb_qoverp_exPV;   //!
	TBranch        *b_mu_muid_id_d0_exPV;   //!
	TBranch        *b_mu_muid_id_z0_exPV;   //!
	TBranch        *b_mu_muid_id_phi_exPV;   //!
	TBranch        *b_mu_muid_id_theta_exPV;   //!
	TBranch        *b_mu_muid_id_qoverp_exPV;   //!
	TBranch        *b_mu_muid_me_d0_exPV;   //!
	TBranch        *b_mu_muid_me_z0_exPV;   //!
	TBranch        *b_mu_muid_me_phi_exPV;   //!
	TBranch        *b_mu_muid_me_theta_exPV;   //!
	TBranch        *b_mu_muid_me_qoverp_exPV;   //!
	TBranch        *b_mu_muid_ie_d0_exPV;   //!
	TBranch        *b_mu_muid_ie_z0_exPV;   //!
	TBranch        *b_mu_muid_ie_phi_exPV;   //!
	TBranch        *b_mu_muid_ie_theta_exPV;   //!
	TBranch        *b_mu_muid_ie_qoverp_exPV;   //!
	TBranch        *b_mu_muid_SpaceTime_detID;   //!
	TBranch        *b_mu_muid_SpaceTime_t;   //!
	TBranch        *b_mu_muid_SpaceTime_tError;   //!
	TBranch        *b_mu_muid_SpaceTime_weight;   //!
	TBranch        *b_mu_muid_SpaceTime_x;   //!
	TBranch        *b_mu_muid_SpaceTime_y;   //!
	TBranch        *b_mu_muid_SpaceTime_z;   //!
	TBranch        *b_mu_muid_SpaceTime_t_Tile;   //!
	TBranch        *b_mu_muid_SpaceTime_tError_Tile;   //!
	TBranch        *b_mu_muid_SpaceTime_weight_Tile;   //!
	TBranch        *b_mu_muid_SpaceTime_x_Tile;   //!
	TBranch        *b_mu_muid_SpaceTime_y_Tile;   //!
	TBranch        *b_mu_muid_SpaceTime_z_Tile;   //!
	TBranch        *b_mu_muid_SpaceTime_t_TRT;   //!
	TBranch        *b_mu_muid_SpaceTime_tError_TRT;   //!
	TBranch        *b_mu_muid_SpaceTime_weight_TRT;   //!
	TBranch        *b_mu_muid_SpaceTime_x_TRT;   //!
	TBranch        *b_mu_muid_SpaceTime_y_TRT;   //!
	TBranch        *b_mu_muid_SpaceTime_z_TRT;   //!
	TBranch        *b_mu_muid_SpaceTime_t_MDT;   //!
	TBranch        *b_mu_muid_SpaceTime_tError_MDT;   //!
	TBranch        *b_mu_muid_SpaceTime_weight_MDT;   //!
	TBranch        *b_mu_muid_SpaceTime_x_MDT;   //!
	TBranch        *b_mu_muid_SpaceTime_y_MDT;   //!
	TBranch        *b_mu_muid_SpaceTime_z_MDT;   //!
	TBranch        *b_mu_muid_TileCellEnergyLayer1;   //!
	TBranch        *b_mu_muid_TileTimeLayer1;   //!
	TBranch        *b_mu_muid_TileCellRmsNoiseLayer1;   //!
	TBranch        *b_mu_muid_TileCellSignLayer1;   //!
	TBranch        *b_mu_muid_TileCellEnergyLayer2;   //!
	TBranch        *b_mu_muid_TileTimeLayer2;   //!
	TBranch        *b_mu_muid_TileCellRmsNoiseLayer2;   //!
	TBranch        *b_mu_muid_TileCellSignLayer2;   //!
	TBranch        *b_mu_muid_TileCellEnergyLayer3;   //!
	TBranch        *b_mu_muid_TileTimeLayer3;   //!
	TBranch        *b_mu_muid_TileCellRmsNoiseLayer3;   //!
	TBranch        *b_mu_muid_TileCellSignLayer3;   //!
	TBranch        *b_mu_muid_MSTrkT0_1;   //!
	TBranch        *b_mu_muid_MSTrkT0_2;   //!
	TBranch        *b_mu_muid_MSTrkT0_3;   //!
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
	TBranch        *b_mu_muid_id_cov_d0_exPV;   //!
	TBranch        *b_mu_muid_id_cov_z0_exPV;   //!
	TBranch        *b_mu_muid_id_cov_phi_exPV;   //!
	TBranch        *b_mu_muid_id_cov_theta_exPV;   //!
	TBranch        *b_mu_muid_id_cov_qoverp_exPV;   //!
	TBranch        *b_mu_muid_id_cov_d0_z0_exPV;   //!
	TBranch        *b_mu_muid_id_cov_d0_phi_exPV;   //!
	TBranch        *b_mu_muid_id_cov_d0_theta_exPV;   //!
	TBranch        *b_mu_muid_id_cov_d0_qoverp_exPV;   //!
	TBranch        *b_mu_muid_id_cov_z0_phi_exPV;   //!
	TBranch        *b_mu_muid_id_cov_z0_theta_exPV;   //!
	TBranch        *b_mu_muid_id_cov_z0_qoverp_exPV;   //!
	TBranch        *b_mu_muid_id_cov_phi_theta_exPV;   //!
	TBranch        *b_mu_muid_id_cov_phi_qoverp_exPV;   //!
	TBranch        *b_mu_muid_id_cov_theta_qoverp_exPV;   //!
	TBranch        *b_mu_muid_me_cov_d0_exPV;   //!
	TBranch        *b_mu_muid_me_cov_z0_exPV;   //!
	TBranch        *b_mu_muid_me_cov_phi_exPV;   //!
	TBranch        *b_mu_muid_me_cov_theta_exPV;   //!
	TBranch        *b_mu_muid_me_cov_qoverp_exPV;   //!
	TBranch        *b_mu_muid_me_cov_d0_z0_exPV;   //!
	TBranch        *b_mu_muid_me_cov_d0_phi_exPV;   //!
	TBranch        *b_mu_muid_me_cov_d0_theta_exPV;   //!
	TBranch        *b_mu_muid_me_cov_d0_qoverp_exPV;   //!
	TBranch        *b_mu_muid_me_cov_z0_phi_exPV;   //!
	TBranch        *b_mu_muid_me_cov_z0_theta_exPV;   //!
	TBranch        *b_mu_muid_me_cov_z0_qoverp_exPV;   //!
	TBranch        *b_mu_muid_me_cov_phi_theta_exPV;   //!
	TBranch        *b_mu_muid_me_cov_phi_qoverp_exPV;   //!
	TBranch        *b_mu_muid_me_cov_theta_qoverp_exPV;   //!
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
	TBranch        *b_mu_muid_nOutliersOnTrack;   //!
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
	TBranch        *b_mu_muid_nGangedPixels;   //!
	TBranch        *b_mu_muid_nPixelDeadSensors;   //!
	TBranch        *b_mu_muid_nSCTDeadSensors;   //!
	TBranch        *b_mu_muid_nTRTDeadStraws;   //!
	TBranch        *b_mu_muid_expectBLayerHit;   //!
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
	TBranch        *b_mu_muid_truth_dr;   //!
	TBranch        *b_mu_muid_truth_E;   //!
	TBranch        *b_mu_muid_truth_pt;   //!
	TBranch        *b_mu_muid_truth_eta;   //!
	TBranch        *b_mu_muid_truth_phi;   //!
	TBranch        *b_mu_muid_truth_type;   //!
	TBranch        *b_mu_muid_truth_status;   //!
	TBranch        *b_mu_muid_truth_barcode;   //!
	TBranch        *b_mu_muid_truth_mothertype;   //!
	TBranch        *b_mu_muid_truth_motherbarcode;   //!
	TBranch        *b_mu_muid_truth_matched;   //!
	TBranch        *b_mu_muid_EFCB_dr;   //!
	TBranch        *b_mu_muid_EFCB_index;   //!
	TBranch        *b_mu_muid_EFMG_dr;   //!
	TBranch        *b_mu_muid_EFMG_index;   //!
	TBranch        *b_mu_muid_EFME_dr;   //!
	TBranch        *b_mu_muid_EFME_index;   //!
	TBranch        *b_mu_muid_L2CB_dr;   //!
	TBranch        *b_mu_muid_L2CB_index;   //!
	TBranch        *b_mu_muid_L1_dr;   //!
	TBranch        *b_mu_muid_L1_index;   //!
	
	TBranch        *b_mu_staco_n;   //!
	TBranch        *b_mu_staco_E;   //!
	TBranch        *b_mu_staco_pt;   //!
	TBranch        *b_mu_staco_m;   //!
	TBranch        *b_mu_staco_eta;   //!
	TBranch        *b_mu_staco_phi;   //!
	TBranch        *b_mu_staco_px;   //!
	TBranch        *b_mu_staco_py;   //!
	TBranch        *b_mu_staco_pz;   //!
	TBranch        *b_mu_staco_charge;   //!
	TBranch        *b_mu_staco_allauthor;   //!
	TBranch        *b_mu_staco_author;   //!
	TBranch        *b_mu_staco_beta;   //!
	TBranch        *b_mu_staco_isMuonLikelihood;   //!
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
	TBranch        *b_mu_staco_etCore;   //!
	TBranch        *b_mu_staco_energyLossType;   //!
	TBranch        *b_mu_staco_caloMuonIdTag;   //!
	TBranch        *b_mu_staco_caloLRLikelihood;   //!
	TBranch        *b_mu_staco_bestMatch;   //!
	TBranch        *b_mu_staco_isStandAloneMuon;   //!
	TBranch        *b_mu_staco_isCombinedMuon;   //!
	TBranch        *b_mu_staco_isLowPtReconstructedMuon;   //!
	TBranch        *b_mu_staco_loose;   //!
	TBranch        *b_mu_staco_medium;   //!
	TBranch        *b_mu_staco_tight;   //!
	TBranch        *b_mu_staco_d0_exPV;   //!
	TBranch        *b_mu_staco_z0_exPV;   //!
	TBranch        *b_mu_staco_phi_exPV;   //!
	TBranch        *b_mu_staco_theta_exPV;   //!
	TBranch        *b_mu_staco_qoverp_exPV;   //!
	TBranch        *b_mu_staco_cb_d0_exPV;   //!
	TBranch        *b_mu_staco_cb_z0_exPV;   //!
	TBranch        *b_mu_staco_cb_phi_exPV;   //!
	TBranch        *b_mu_staco_cb_theta_exPV;   //!
	TBranch        *b_mu_staco_cb_qoverp_exPV;   //!
	TBranch        *b_mu_staco_id_d0_exPV;   //!
	TBranch        *b_mu_staco_id_z0_exPV;   //!
	TBranch        *b_mu_staco_id_phi_exPV;   //!
	TBranch        *b_mu_staco_id_theta_exPV;   //!
	TBranch        *b_mu_staco_id_qoverp_exPV;   //!
	TBranch        *b_mu_staco_me_d0_exPV;   //!
	TBranch        *b_mu_staco_me_z0_exPV;   //!
	TBranch        *b_mu_staco_me_phi_exPV;   //!
	TBranch        *b_mu_staco_me_theta_exPV;   //!
	TBranch        *b_mu_staco_me_qoverp_exPV;   //!
	TBranch        *b_mu_staco_ie_d0_exPV;   //!
	TBranch        *b_mu_staco_ie_z0_exPV;   //!
	TBranch        *b_mu_staco_ie_phi_exPV;   //!
	TBranch        *b_mu_staco_ie_theta_exPV;   //!
	TBranch        *b_mu_staco_ie_qoverp_exPV;   //!
	TBranch        *b_mu_staco_SpaceTime_detID;   //!
	TBranch        *b_mu_staco_SpaceTime_t;   //!
	TBranch        *b_mu_staco_SpaceTime_tError;   //!
	TBranch        *b_mu_staco_SpaceTime_weight;   //!
	TBranch        *b_mu_staco_SpaceTime_x;   //!
	TBranch        *b_mu_staco_SpaceTime_y;   //!
	TBranch        *b_mu_staco_SpaceTime_z;   //!
	TBranch        *b_mu_staco_SpaceTime_t_Tile;   //!
	TBranch        *b_mu_staco_SpaceTime_tError_Tile;   //!
	TBranch        *b_mu_staco_SpaceTime_weight_Tile;   //!
	TBranch        *b_mu_staco_SpaceTime_x_Tile;   //!
	TBranch        *b_mu_staco_SpaceTime_y_Tile;   //!
	TBranch        *b_mu_staco_SpaceTime_z_Tile;   //!
	TBranch        *b_mu_staco_SpaceTime_t_TRT;   //!
	TBranch        *b_mu_staco_SpaceTime_tError_TRT;   //!
	TBranch        *b_mu_staco_SpaceTime_weight_TRT;   //!
	TBranch        *b_mu_staco_SpaceTime_x_TRT;   //!
	TBranch        *b_mu_staco_SpaceTime_y_TRT;   //!
	TBranch        *b_mu_staco_SpaceTime_z_TRT;   //!
	TBranch        *b_mu_staco_SpaceTime_t_MDT;   //!
	TBranch        *b_mu_staco_SpaceTime_tError_MDT;   //!
	TBranch        *b_mu_staco_SpaceTime_weight_MDT;   //!
	TBranch        *b_mu_staco_SpaceTime_x_MDT;   //!
	TBranch        *b_mu_staco_SpaceTime_y_MDT;   //!
	TBranch        *b_mu_staco_SpaceTime_z_MDT;   //!
	TBranch        *b_mu_staco_TileCellEnergyLayer1;   //!
	TBranch        *b_mu_staco_TileTimeLayer1;   //!
	TBranch        *b_mu_staco_TileCellRmsNoiseLayer1;   //!
	TBranch        *b_mu_staco_TileCellSignLayer1;   //!
	TBranch        *b_mu_staco_TileCellEnergyLayer2;   //!
	TBranch        *b_mu_staco_TileTimeLayer2;   //!
	TBranch        *b_mu_staco_TileCellRmsNoiseLayer2;   //!
	TBranch        *b_mu_staco_TileCellSignLayer2;   //!
	TBranch        *b_mu_staco_TileCellEnergyLayer3;   //!
	TBranch        *b_mu_staco_TileTimeLayer3;   //!
	TBranch        *b_mu_staco_TileCellRmsNoiseLayer3;   //!
	TBranch        *b_mu_staco_TileCellSignLayer3;   //!
	TBranch        *b_mu_staco_MSTrkT0_1;   //!
	TBranch        *b_mu_staco_MSTrkT0_2;   //!
	TBranch        *b_mu_staco_MSTrkT0_3;   //!
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
	TBranch        *b_mu_staco_id_cov_d0_exPV;   //!
	TBranch        *b_mu_staco_id_cov_z0_exPV;   //!
	TBranch        *b_mu_staco_id_cov_phi_exPV;   //!
	TBranch        *b_mu_staco_id_cov_theta_exPV;   //!
	TBranch        *b_mu_staco_id_cov_qoverp_exPV;   //!
	TBranch        *b_mu_staco_id_cov_d0_z0_exPV;   //!
	TBranch        *b_mu_staco_id_cov_d0_phi_exPV;   //!
	TBranch        *b_mu_staco_id_cov_d0_theta_exPV;   //!
	TBranch        *b_mu_staco_id_cov_d0_qoverp_exPV;   //!
	TBranch        *b_mu_staco_id_cov_z0_phi_exPV;   //!
	TBranch        *b_mu_staco_id_cov_z0_theta_exPV;   //!
	TBranch        *b_mu_staco_id_cov_z0_qoverp_exPV;   //!
	TBranch        *b_mu_staco_id_cov_phi_theta_exPV;   //!
	TBranch        *b_mu_staco_id_cov_phi_qoverp_exPV;   //!
	TBranch        *b_mu_staco_id_cov_theta_qoverp_exPV;   //!
	TBranch        *b_mu_staco_me_cov_d0_exPV;   //!
	TBranch        *b_mu_staco_me_cov_z0_exPV;   //!
	TBranch        *b_mu_staco_me_cov_phi_exPV;   //!
	TBranch        *b_mu_staco_me_cov_theta_exPV;   //!
	TBranch        *b_mu_staco_me_cov_qoverp_exPV;   //!
	TBranch        *b_mu_staco_me_cov_d0_z0_exPV;   //!
	TBranch        *b_mu_staco_me_cov_d0_phi_exPV;   //!
	TBranch        *b_mu_staco_me_cov_d0_theta_exPV;   //!
	TBranch        *b_mu_staco_me_cov_d0_qoverp_exPV;   //!
	TBranch        *b_mu_staco_me_cov_z0_phi_exPV;   //!
	TBranch        *b_mu_staco_me_cov_z0_theta_exPV;   //!
	TBranch        *b_mu_staco_me_cov_z0_qoverp_exPV;   //!
	TBranch        *b_mu_staco_me_cov_phi_theta_exPV;   //!
	TBranch        *b_mu_staco_me_cov_phi_qoverp_exPV;   //!
	TBranch        *b_mu_staco_me_cov_theta_qoverp_exPV;   //!
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
	TBranch        *b_mu_staco_nOutliersOnTrack;   //!
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
	TBranch        *b_mu_staco_nGangedPixels;   //!
	TBranch        *b_mu_staco_nPixelDeadSensors;   //!
	TBranch        *b_mu_staco_nSCTDeadSensors;   //!
	TBranch        *b_mu_staco_nTRTDeadStraws;   //!
	TBranch        *b_mu_staco_expectBLayerHit;   //!
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
	TBranch        *b_mu_staco_truth_dr;   //!
	TBranch        *b_mu_staco_truth_E;   //!
	TBranch        *b_mu_staco_truth_pt;   //!
	TBranch        *b_mu_staco_truth_eta;   //!
	TBranch        *b_mu_staco_truth_phi;   //!
	TBranch        *b_mu_staco_truth_type;   //!
	TBranch        *b_mu_staco_truth_status;   //!
	TBranch        *b_mu_staco_truth_barcode;   //!
	TBranch        *b_mu_staco_truth_mothertype;   //!
	TBranch        *b_mu_staco_truth_motherbarcode;   //!
	TBranch        *b_mu_staco_truth_matched;   //!
	TBranch        *b_mu_staco_EFCB_dr;   //!
	TBranch        *b_mu_staco_EFCB_index;   //!
	TBranch        *b_mu_staco_EFMG_dr;   //!
	TBranch        *b_mu_staco_EFMG_index;   //!
	TBranch        *b_mu_staco_EFME_dr;   //!
	TBranch        *b_mu_staco_EFME_index;   //!
	TBranch        *b_mu_staco_L2CB_dr;   //!
	TBranch        *b_mu_staco_L2CB_index;   //!
	TBranch        *b_mu_staco_L1_dr;   //!
	TBranch        *b_mu_staco_L1_index;   //!
	
	TBranch        *b_mu_calo_n;   //!
	TBranch        *b_mu_calo_E;   //!
	TBranch        *b_mu_calo_pt;   //!
	TBranch        *b_mu_calo_m;   //!
	TBranch        *b_mu_calo_eta;   //!
	TBranch        *b_mu_calo_phi;   //!
	TBranch        *b_mu_calo_px;   //!
	TBranch        *b_mu_calo_py;   //!
	TBranch        *b_mu_calo_pz;   //!
	TBranch        *b_mu_calo_charge;   //!
	TBranch        *b_mu_calo_allauthor;   //!
	TBranch        *b_mu_calo_hastrack;   //!
	TBranch        *b_mu_calo_truth_dr;   //!
	TBranch        *b_mu_calo_truth_E;   //!
	TBranch        *b_mu_calo_truth_pt;   //!
	TBranch        *b_mu_calo_truth_eta;   //!
	TBranch        *b_mu_calo_truth_phi;   //!
	TBranch        *b_mu_calo_truth_type;   //!
	TBranch        *b_mu_calo_truth_status;   //!
	TBranch        *b_mu_calo_truth_barcode;   //!
	TBranch        *b_mu_calo_truth_mothertype;   //!
	TBranch        *b_mu_calo_truth_motherbarcode;   //!
	TBranch        *b_mu_calo_truth_matched;   //!
	
	TBranch        *b_MET_RefFinal_phi;   //!
	TBranch        *b_MET_RefFinal_et;   //!
	TBranch        *b_MET_RefFinal_sumet;   //!
	TBranch        *b_MET_Cryo_phi;   //!
	TBranch        *b_MET_Cryo_et;   //!
	TBranch        *b_MET_Cryo_sumet;   //!
	TBranch        *b_MET_RefEle_phi;   //!
	TBranch        *b_MET_RefEle_et;   //!
	TBranch        *b_MET_RefEle_sumet;   //!
	TBranch        *b_MET_RefJet_phi;   //!
	TBranch        *b_MET_RefJet_et;   //!
	TBranch        *b_MET_RefJet_sumet;   //!
	TBranch        *b_MET_SoftJets_phi;   //!
	TBranch        *b_MET_SoftJets_et;   //!
	TBranch        *b_MET_SoftJets_sumet;   //!
	TBranch        *b_MET_RefMuon_phi;   //!
	TBranch        *b_MET_RefMuon_et;   //!
	TBranch        *b_MET_RefMuon_sumet;   //!
	TBranch        *b_MET_RefMuon_Staco_phi;   //!
	TBranch        *b_MET_RefMuon_Staco_et;   //!
	TBranch        *b_MET_RefMuon_Staco_sumet;   //!
	TBranch        *b_MET_RefMuon_Muid_phi;   //!
	TBranch        *b_MET_RefMuon_Muid_et;   //!
	TBranch        *b_MET_RefMuon_Muid_sumet;   //!
	TBranch        *b_MET_RefGamma_phi;   //!
	TBranch        *b_MET_RefGamma_et;   //!
	TBranch        *b_MET_RefGamma_sumet;   //!
	TBranch        *b_MET_RefTau_phi;   //!
	TBranch        *b_MET_RefTau_et;   //!
	TBranch        *b_MET_RefTau_sumet;   //!
	TBranch        *b_MET_CellOut_phi;   //!
	TBranch        *b_MET_CellOut_et;   //!
	TBranch        *b_MET_CellOut_sumet;   //!
	TBranch        *b_MET_Track_phi;   //!
	TBranch        *b_MET_Track_et;   //!
	TBranch        *b_MET_Track_sumet;   //!
	TBranch        *b_MET_RefFinal_em_etx;   //!
	TBranch        *b_MET_RefFinal_em_ety;   //!
	TBranch        *b_MET_RefFinal_em_phi;   //!
	TBranch        *b_MET_RefFinal_em_et;   //!
	TBranch        *b_MET_RefFinal_em_sumet;   //!
	TBranch        *b_MET_RefEle_em_phi;   //!
	TBranch        *b_MET_RefEle_em_et;   //!
	TBranch        *b_MET_RefEle_em_sumet;   //!
	TBranch        *b_MET_RefJet_em_phi;   //!
	TBranch        *b_MET_RefJet_em_et;   //!
	TBranch        *b_MET_RefJet_em_sumet;   //!
	TBranch        *b_MET_SoftJets_em_phi;   //!
	TBranch        *b_MET_SoftJets_em_et;   //!
	TBranch        *b_MET_SoftJets_em_sumet;   //!
	TBranch        *b_MET_RefMuon_em_phi;   //!
	TBranch        *b_MET_RefMuon_em_et;   //!
	TBranch        *b_MET_RefMuon_em_sumet;   //!
	TBranch        *b_MET_RefMuon_Track_em_phi;   //!
	TBranch        *b_MET_RefMuon_Track_em_et;   //!
	TBranch        *b_MET_RefMuon_Track_em_sumet;   //!
	TBranch        *b_MET_RefGamma_em_phi;   //!
	TBranch        *b_MET_RefGamma_em_et;   //!
	TBranch        *b_MET_RefGamma_em_sumet;   //!
	TBranch        *b_MET_RefTau_em_phi;   //!
	TBranch        *b_MET_RefTau_em_et;   //!
	TBranch        *b_MET_RefTau_em_sumet;   //!
	TBranch        *b_MET_CellOut_em_etx;   //!
	TBranch        *b_MET_CellOut_em_ety;   //!
	TBranch        *b_MET_CellOut_em_phi;   //!
	TBranch        *b_MET_CellOut_em_et;   //!
	TBranch        *b_MET_CellOut_em_sumet;   //!
	TBranch        *b_MET_Muon_Isol_Staco_phi;   //!
	TBranch        *b_MET_Muon_Isol_Staco_et;   //!
	TBranch        *b_MET_Muon_Isol_Staco_sumet;   //!
	TBranch        *b_MET_Muon_NonIsol_Staco_phi;   //!
	TBranch        *b_MET_Muon_NonIsol_Staco_et;   //!
	TBranch        *b_MET_Muon_NonIsol_Staco_sumet;   //!
	TBranch        *b_MET_Muon_Total_Staco_phi;   //!
	TBranch        *b_MET_Muon_Total_Staco_et;   //!
	TBranch        *b_MET_Muon_Total_Staco_sumet;   //!
	TBranch        *b_MET_Muon_Isol_Muid_phi;   //!
	TBranch        *b_MET_Muon_Isol_Muid_et;   //!
	TBranch        *b_MET_Muon_Isol_Muid_sumet;   //!
	TBranch        *b_MET_Muon_NonIsol_Muid_phi;   //!
	TBranch        *b_MET_Muon_NonIsol_Muid_et;   //!
	TBranch        *b_MET_Muon_NonIsol_Muid_sumet;   //!
	TBranch        *b_MET_Muon_Total_Muid_phi;   //!
	TBranch        *b_MET_Muon_Total_Muid_et;   //!
	TBranch        *b_MET_Muon_Total_Muid_sumet;   //!
	TBranch        *b_MET_MuonBoy_phi;   //!
	TBranch        *b_MET_MuonBoy_et;   //!
	TBranch        *b_MET_MuonBoy_sumet;   //!
	TBranch        *b_MET_RefMuon_Track_phi;   //!
	TBranch        *b_MET_RefMuon_Track_et;   //!
	TBranch        *b_MET_RefMuon_Track_sumet;   //!
	TBranch        *b_MET_RefMuon_Track_Staco_phi;   //!
	TBranch        *b_MET_RefMuon_Track_Staco_et;   //!
	TBranch        *b_MET_RefMuon_Track_Staco_sumet;   //!
	TBranch        *b_MET_RefMuon_Track_Muid_phi;   //!
	TBranch        *b_MET_RefMuon_Track_Muid_et;   //!
	TBranch        *b_MET_RefMuon_Track_Muid_sumet;   //!
	TBranch        *b_MET_CryoCone_phi;   //!
	TBranch        *b_MET_CryoCone_et;   //!
	TBranch        *b_MET_CryoCone_sumet;   //!
	TBranch        *b_MET_Final_phi;   //!
	TBranch        *b_MET_Final_et;   //!
	TBranch        *b_MET_Final_sumet;   //!
	TBranch        *b_MET_MuonBoy_Spectro_phi;   //!
	TBranch        *b_MET_MuonBoy_Spectro_et;   //!
	TBranch        *b_MET_MuonBoy_Spectro_sumet;   //!
	TBranch        *b_MET_MuonBoy_Track_phi;   //!
	TBranch        *b_MET_MuonBoy_Track_et;   //!
	TBranch        *b_MET_MuonBoy_Track_sumet;   //!
	TBranch        *b_MET_MuonMuid_phi;   //!
	TBranch        *b_MET_MuonMuid_et;   //!
	TBranch        *b_MET_MuonMuid_sumet;   //!
	TBranch        *b_MET_Muid_phi;   //!
	TBranch        *b_MET_Muid_et;   //!
	TBranch        *b_MET_Muid_sumet;   //!
	TBranch        *b_MET_Muid_Spectro_phi;   //!
	TBranch        *b_MET_Muid_Spectro_et;   //!
	TBranch        *b_MET_Muid_Spectro_sumet;   //!
	TBranch        *b_MET_Muid_Track_phi;   //!
	TBranch        *b_MET_Muid_Track_et;   //!
	TBranch        *b_MET_Muid_Track_sumet;   //!
	TBranch        *b_MET_Muon_phi;   //!
	TBranch        *b_MET_Muon_et;   //!
	TBranch        *b_MET_Muon_sumet;   //!
	TBranch        *b_MET_TopoObj_phi;   //!
	TBranch        *b_MET_TopoObj_et;   //!
	TBranch        *b_MET_TopoObj_sumet;   //!
	TBranch        *b_MET_LocHadTopoObj_phi;   //!
	TBranch        *b_MET_LocHadTopoObj_et;   //!
	TBranch        *b_MET_LocHadTopoObj_sumet;   //!
	TBranch        *b_MET_Topo_phi;   //!
	TBranch        *b_MET_Topo_et;   //!
	TBranch        *b_MET_Topo_sumet;   //!
	TBranch        *b_MET_Topo_SUMET_EMFrac;   //!
	TBranch        *b_MET_Topo_etx_PEMB;   //!
	TBranch        *b_MET_Topo_ety_PEMB;   //!
	TBranch        *b_MET_Topo_sumet_PEMB;   //!
	TBranch        *b_MET_Topo_phi_PEMB;   //!
	TBranch        *b_MET_Topo_etx_EMB;   //!
	TBranch        *b_MET_Topo_ety_EMB;   //!
	TBranch        *b_MET_Topo_sumet_EMB;   //!
	TBranch        *b_MET_Topo_phi_EMB;   //!
	TBranch        *b_MET_Topo_etx_PEMEC;   //!
	TBranch        *b_MET_Topo_ety_PEMEC;   //!
	TBranch        *b_MET_Topo_sumet_PEMEC;   //!
	TBranch        *b_MET_Topo_phi_PEMEC;   //!
	TBranch        *b_MET_Topo_etx_EME;   //!
	TBranch        *b_MET_Topo_ety_EME;   //!
	TBranch        *b_MET_Topo_sumet_EME;   //!
	TBranch        *b_MET_Topo_phi_EME;   //!
	TBranch        *b_MET_Topo_etx_TILE;   //!
	TBranch        *b_MET_Topo_ety_TILE;   //!
	TBranch        *b_MET_Topo_sumet_TILE;   //!
	TBranch        *b_MET_Topo_phi_TILE;   //!
	TBranch        *b_MET_Topo_etx_HEC;   //!
	TBranch        *b_MET_Topo_ety_HEC;   //!
	TBranch        *b_MET_Topo_sumet_HEC;   //!
	TBranch        *b_MET_Topo_phi_HEC;   //!
	TBranch        *b_MET_Topo_etx_FCAL;   //!
	TBranch        *b_MET_Topo_ety_FCAL;   //!
	TBranch        *b_MET_Topo_sumet_FCAL;   //!
	TBranch        *b_MET_Topo_phi_FCAL;   //!
	TBranch        *b_MET_Topo_nCell_PEMB;   //!
	TBranch        *b_MET_Topo_nCell_EMB;   //!
	TBranch        *b_MET_Topo_nCell_PEMEC;   //!
	TBranch        *b_MET_Topo_nCell_EME;   //!
	TBranch        *b_MET_Topo_nCell_TILE;   //!
	TBranch        *b_MET_Topo_nCell_HEC;   //!
	TBranch        *b_MET_Topo_nCell_FCAL;   //!
	TBranch        *b_MET_Topo_etx_CentralReg;   //!
	TBranch        *b_MET_Topo_ety_CentralReg;   //!
	TBranch        *b_MET_Topo_sumet_CentralReg;   //!
	TBranch        *b_MET_Topo_phi_CentralReg;   //!
	TBranch        *b_MET_Topo_etx_EndcapRegion;   //!
	TBranch        *b_MET_Topo_ety_EndcapRegion;   //!
	TBranch        *b_MET_Topo_sumet_EndcapRegion;   //!
	TBranch        *b_MET_Topo_phi_EndcapRegion;   //!
	TBranch        *b_MET_Topo_etx_ForwardReg;   //!
	TBranch        *b_MET_Topo_ety_ForwardReg;   //!
	TBranch        *b_MET_Topo_sumet_ForwardReg;   //!
	TBranch        *b_MET_Topo_phi_ForwardReg;   //!
	TBranch        *b_MET_CorrTopo_phi;   //!
	TBranch        *b_MET_CorrTopo_et;   //!
	TBranch        *b_MET_CorrTopo_sumet;   //!
	TBranch        *b_MET_CorrTopo_SUMET_EMFrac;   //!
	TBranch        *b_MET_CorrTopo_etx_PEMB;   //!
	TBranch        *b_MET_CorrTopo_ety_PEMB;   //!
	TBranch        *b_MET_CorrTopo_sumet_PEMB;   //!
	TBranch        *b_MET_CorrTopo_phi_PEMB;   //!
	TBranch        *b_MET_CorrTopo_etx_EMB;   //!
	TBranch        *b_MET_CorrTopo_ety_EMB;   //!
	TBranch        *b_MET_CorrTopo_sumet_EMB;   //!
	TBranch        *b_MET_CorrTopo_phi_EMB;   //!
	TBranch        *b_MET_CorrTopo_etx_PEMEC;   //!
	TBranch        *b_MET_CorrTopo_ety_PEMEC;   //!
	TBranch        *b_MET_CorrTopo_sumet_PEMEC;   //!
	TBranch        *b_MET_CorrTopo_phi_PEMEC;   //!
	TBranch        *b_MET_CorrTopo_etx_EME;   //!
	TBranch        *b_MET_CorrTopo_ety_EME;   //!
	TBranch        *b_MET_CorrTopo_sumet_EME;   //!
	TBranch        *b_MET_CorrTopo_phi_EME;   //!
	TBranch        *b_MET_CorrTopo_etx_TILE;   //!
	TBranch        *b_MET_CorrTopo_ety_TILE;   //!
	TBranch        *b_MET_CorrTopo_sumet_TILE;   //!
	TBranch        *b_MET_CorrTopo_phi_TILE;   //!
	TBranch        *b_MET_CorrTopo_etx_HEC;   //!
	TBranch        *b_MET_CorrTopo_ety_HEC;   //!
	TBranch        *b_MET_CorrTopo_sumet_HEC;   //!
	TBranch        *b_MET_CorrTopo_phi_HEC;   //!
	TBranch        *b_MET_CorrTopo_etx_FCAL;   //!
	TBranch        *b_MET_CorrTopo_ety_FCAL;   //!
	TBranch        *b_MET_CorrTopo_sumet_FCAL;   //!
	TBranch        *b_MET_CorrTopo_phi_FCAL;   //!
	TBranch        *b_MET_CorrTopo_nCell_PEMB;   //!
	TBranch        *b_MET_CorrTopo_nCell_EMB;   //!
	TBranch        *b_MET_CorrTopo_nCell_PEMEC;   //!
	TBranch        *b_MET_CorrTopo_nCell_EME;   //!
	TBranch        *b_MET_CorrTopo_nCell_TILE;   //!
	TBranch        *b_MET_CorrTopo_nCell_HEC;   //!
	TBranch        *b_MET_CorrTopo_nCell_FCAL;   //!
	TBranch        *b_MET_CorrTopo_etx_CentralReg;   //!
	TBranch        *b_MET_CorrTopo_ety_CentralReg;   //!
	TBranch        *b_MET_CorrTopo_sumet_CentralReg;   //!
	TBranch        *b_MET_CorrTopo_phi_CentralReg;   //!
	TBranch        *b_MET_CorrTopo_etx_EndcapRegion;   //!
	TBranch        *b_MET_CorrTopo_ety_EndcapRegion;   //!
	TBranch        *b_MET_CorrTopo_sumet_EndcapRegion;   //!
	TBranch        *b_MET_CorrTopo_phi_EndcapRegion;   //!
	TBranch        *b_MET_CorrTopo_etx_ForwardReg;   //!
	TBranch        *b_MET_CorrTopo_ety_ForwardReg;   //!
	TBranch        *b_MET_CorrTopo_sumet_ForwardReg;   //!
	TBranch        *b_MET_CorrTopo_phi_ForwardReg;   //!
	TBranch        *b_MET_LocHadTopo_phi;   //!
	TBranch        *b_MET_LocHadTopo_et;   //!
	TBranch        *b_MET_LocHadTopo_sumet;   //!
	TBranch        *b_MET_LocHadTopo_SUMET_EMFrac;   //!
	TBranch        *b_MET_LocHadTopo_etx_PEMB;   //!
	TBranch        *b_MET_LocHadTopo_ety_PEMB;   //!
	TBranch        *b_MET_LocHadTopo_sumet_PEMB;   //!
	TBranch        *b_MET_LocHadTopo_phi_PEMB;   //!
	TBranch        *b_MET_LocHadTopo_etx_EMB;   //!
	TBranch        *b_MET_LocHadTopo_ety_EMB;   //!
	TBranch        *b_MET_LocHadTopo_sumet_EMB;   //!
	TBranch        *b_MET_LocHadTopo_phi_EMB;   //!
	TBranch        *b_MET_LocHadTopo_etx_PEMEC;   //!
	TBranch        *b_MET_LocHadTopo_ety_PEMEC;   //!
	TBranch        *b_MET_LocHadTopo_sumet_PEMEC;   //!
	TBranch        *b_MET_LocHadTopo_phi_PEMEC;   //!
	TBranch        *b_MET_LocHadTopo_etx_EME;   //!
	TBranch        *b_MET_LocHadTopo_ety_EME;   //!
	TBranch        *b_MET_LocHadTopo_sumet_EME;   //!
	TBranch        *b_MET_LocHadTopo_phi_EME;   //!
	TBranch        *b_MET_LocHadTopo_etx_TILE;   //!
	TBranch        *b_MET_LocHadTopo_ety_TILE;   //!
	TBranch        *b_MET_LocHadTopo_sumet_TILE;   //!
	TBranch        *b_MET_LocHadTopo_phi_TILE;   //!
	TBranch        *b_MET_LocHadTopo_etx_HEC;   //!
	TBranch        *b_MET_LocHadTopo_ety_HEC;   //!
	TBranch        *b_MET_LocHadTopo_sumet_HEC;   //!
	TBranch        *b_MET_LocHadTopo_phi_HEC;   //!
	TBranch        *b_MET_LocHadTopo_etx_FCAL;   //!
	TBranch        *b_MET_LocHadTopo_ety_FCAL;   //!
	TBranch        *b_MET_LocHadTopo_sumet_FCAL;   //!
	TBranch        *b_MET_LocHadTopo_phi_FCAL;   //!
	TBranch        *b_MET_LocHadTopo_nCell_PEMB;   //!
	TBranch        *b_MET_LocHadTopo_nCell_EMB;   //!
	TBranch        *b_MET_LocHadTopo_nCell_PEMEC;   //!
	TBranch        *b_MET_LocHadTopo_nCell_EME;   //!
	TBranch        *b_MET_LocHadTopo_nCell_TILE;   //!
	TBranch        *b_MET_LocHadTopo_nCell_HEC;   //!
	TBranch        *b_MET_LocHadTopo_nCell_FCAL;   //!
	TBranch        *b_MET_LocHadTopo_etx_CentralReg;   //!
	TBranch        *b_MET_LocHadTopo_ety_CentralReg;   //!
	TBranch        *b_MET_LocHadTopo_sumet_CentralReg;   //!
	TBranch        *b_MET_LocHadTopo_phi_CentralReg;   //!
	TBranch        *b_MET_LocHadTopo_etx_EndcapRegion;   //!
	TBranch        *b_MET_LocHadTopo_ety_EndcapRegion;   //!
	TBranch        *b_MET_LocHadTopo_sumet_EndcapRegion;   //!
	TBranch        *b_MET_LocHadTopo_phi_EndcapRegion;   //!
	TBranch        *b_MET_LocHadTopo_etx_ForwardReg;   //!
	TBranch        *b_MET_LocHadTopo_ety_ForwardReg;   //!
	TBranch        *b_MET_LocHadTopo_sumet_ForwardReg;   //!
	TBranch        *b_MET_LocHadTopo_phi_ForwardReg;   //!
	TBranch        *b_MET_Calib_phi;   //!
	TBranch        *b_MET_Calib_et;   //!
	TBranch        *b_MET_Calib_sumet;   //!
	TBranch        *b_MET_Calib_SUMET_EMFrac;   //!
	TBranch        *b_MET_Calib_etx_PEMB;   //!
	TBranch        *b_MET_Calib_ety_PEMB;   //!
	TBranch        *b_MET_Calib_sumet_PEMB;   //!
	TBranch        *b_MET_Calib_phi_PEMB;   //!
	TBranch        *b_MET_Calib_etx_EMB;   //!
	TBranch        *b_MET_Calib_ety_EMB;   //!
	TBranch        *b_MET_Calib_sumet_EMB;   //!
	TBranch        *b_MET_Calib_phi_EMB;   //!
	TBranch        *b_MET_Calib_etx_PEMEC;   //!
	TBranch        *b_MET_Calib_ety_PEMEC;   //!
	TBranch        *b_MET_Calib_sumet_PEMEC;   //!
	TBranch        *b_MET_Calib_phi_PEMEC;   //!
	TBranch        *b_MET_Calib_etx_EME;   //!
	TBranch        *b_MET_Calib_ety_EME;   //!
	TBranch        *b_MET_Calib_sumet_EME;   //!
	TBranch        *b_MET_Calib_phi_EME;   //!
	TBranch        *b_MET_Calib_etx_TILE;   //!
	TBranch        *b_MET_Calib_ety_TILE;   //!
	TBranch        *b_MET_Calib_sumet_TILE;   //!
	TBranch        *b_MET_Calib_phi_TILE;   //!
	TBranch        *b_MET_Calib_etx_HEC;   //!
	TBranch        *b_MET_Calib_ety_HEC;   //!
	TBranch        *b_MET_Calib_sumet_HEC;   //!
	TBranch        *b_MET_Calib_phi_HEC;   //!
	TBranch        *b_MET_Calib_etx_FCAL;   //!
	TBranch        *b_MET_Calib_ety_FCAL;   //!
	TBranch        *b_MET_Calib_sumet_FCAL;   //!
	TBranch        *b_MET_Calib_phi_FCAL;   //!
	TBranch        *b_MET_Calib_nCell_PEMB;   //!
	TBranch        *b_MET_Calib_nCell_EMB;   //!
	TBranch        *b_MET_Calib_nCell_PEMEC;   //!
	TBranch        *b_MET_Calib_nCell_EME;   //!
	TBranch        *b_MET_Calib_nCell_TILE;   //!
	TBranch        *b_MET_Calib_nCell_HEC;   //!
	TBranch        *b_MET_Calib_nCell_FCAL;   //!
	TBranch        *b_MET_Calib_etx_CentralReg;   //!
	TBranch        *b_MET_Calib_ety_CentralReg;   //!
	TBranch        *b_MET_Calib_sumet_CentralReg;   //!
	TBranch        *b_MET_Calib_phi_CentralReg;   //!
	TBranch        *b_MET_Calib_etx_EndcapRegion;   //!
	TBranch        *b_MET_Calib_ety_EndcapRegion;   //!
	TBranch        *b_MET_Calib_sumet_EndcapRegion;   //!
	TBranch        *b_MET_Calib_phi_EndcapRegion;   //!
	TBranch        *b_MET_Calib_etx_ForwardReg;   //!
	TBranch        *b_MET_Calib_ety_ForwardReg;   //!
	TBranch        *b_MET_Calib_sumet_ForwardReg;   //!
	TBranch        *b_MET_Calib_phi_ForwardReg;   //!
	TBranch        *b_MET_Truth_NonInt_etx;   //!
	TBranch        *b_MET_Truth_NonInt_ety;   //!
	TBranch        *b_MET_Truth_NonInt_phi;   //!
	TBranch        *b_MET_Truth_NonInt_et;   //!
	TBranch        *b_MET_Truth_NonInt_sumet;   //!
	TBranch        *b_MET_Truth_Int_phi;   //!
	TBranch        *b_MET_Truth_IntCentral_phi;   //!
	TBranch        *b_MET_Truth_IntFwd_phi;   //!
	TBranch        *b_MET_Truth_IntOutCover_phi;   //!
	TBranch        *b_MET_Truth_IntMuons_phi;   //!
	TBranch        *b_MET_Truth_Int_et;   //!
	TBranch        *b_MET_Truth_IntCentral_et;   //!
	TBranch        *b_MET_Truth_IntFwd_et;   //!
	TBranch        *b_MET_Truth_IntOutCover_et;   //!
	TBranch        *b_MET_Truth_IntMuons_et;   //!
	TBranch        *b_MET_Truth_Int_sumet;   //!
	TBranch        *b_MET_Truth_IntCentral_sumet;   //!
	TBranch        *b_MET_Truth_IntFwd_sumet;   //!
	TBranch        *b_MET_Truth_IntOutCover_sumet;   //!
	TBranch        *b_MET_Truth_IntMuons_sumet;   //!
	TBranch        *b_MET_Truth_PileUp_NonInt_etx;   //!
	TBranch        *b_MET_Truth_PileUp_NonInt_ety;   //!
	TBranch        *b_MET_Truth_PileUp_NonInt_phi;   //!
	TBranch        *b_MET_Truth_PileUp_NonInt_et;   //!
	TBranch        *b_MET_Truth_PileUp_NonInt_sumet;   //!
	TBranch        *b_MET_Truth_PileUp_Int_etx;   //!
	TBranch        *b_MET_Truth_PileUp_Int_ety;   //!
	TBranch        *b_MET_Truth_PileUp_IntCentral_etx;   //!
	TBranch        *b_MET_Truth_PileUp_IntCentral_ety;   //!
	TBranch        *b_MET_Truth_PileUp_IntFwd_etx;   //!
	TBranch        *b_MET_Truth_PileUp_IntFwd_ety;   //!
	TBranch        *b_MET_Truth_PileUp_IntOutCover_etx;   //!
	TBranch        *b_MET_Truth_PileUp_IntOutCover_ety;   //!
	TBranch        *b_MET_Truth_PileUp_IntMuons_etx;   //!
	TBranch        *b_MET_Truth_PileUp_IntMuons_ety;   //!
	TBranch        *b_MET_Truth_PileUp_Int_phi;   //!
	TBranch        *b_MET_Truth_PileUp_IntCentral_phi;   //!
	TBranch        *b_MET_Truth_PileUp_IntFwd_phi;   //!
	TBranch        *b_MET_Truth_PileUp_IntOutCover_phi;   //!
	TBranch        *b_MET_Truth_PileUp_IntMuons_phi;   //!
	TBranch        *b_MET_Truth_PileUp_Int_et;   //!
	TBranch        *b_MET_Truth_PileUp_IntCentral_et;   //!
	TBranch        *b_MET_Truth_PileUp_IntFwd_et;   //!
	TBranch        *b_MET_Truth_PileUp_IntOutCover_et;   //!
	TBranch        *b_MET_Truth_PileUp_IntMuons_et;   //!
	TBranch        *b_MET_Truth_PileUp_Int_sumet;   //!
	TBranch        *b_MET_Truth_PileUp_IntCentral_sumet;   //!
	TBranch        *b_MET_Truth_PileUp_IntFwd_sumet;   //!
	TBranch        *b_MET_Truth_PileUp_IntOutCover_sumet;   //!
	TBranch        *b_MET_Truth_PileUp_IntMuons_sumet;   //!
	TBranch        *b_MET_DM_Crack1_etx;   //!
	TBranch        *b_MET_DM_Crack1_ety;   //!
	TBranch        *b_MET_DM_Crack1_phi;   //!
	TBranch        *b_MET_DM_Crack1_et;   //!
	TBranch        *b_MET_DM_Crack1_sumet;   //!
	TBranch        *b_MET_DM_Crack2_etx;   //!
	TBranch        *b_MET_DM_Crack2_ety;   //!
	TBranch        *b_MET_DM_Crack2_phi;   //!
	TBranch        *b_MET_DM_Crack2_et;   //!
	TBranch        *b_MET_DM_Crack2_sumet;   //!
	TBranch        *b_MET_DM_All_etx;   //!
	TBranch        *b_MET_DM_All_ety;   //!
	TBranch        *b_MET_DM_All_phi;   //!
	TBranch        *b_MET_DM_All_et;   //!
	TBranch        *b_MET_DM_All_sumet;   //!
	TBranch        *b_MET_DM_Cryo_etx;   //!
	TBranch        *b_MET_DM_Cryo_ety;   //!
	TBranch        *b_MET_DM_Cryo_phi;   //!
	TBranch        *b_MET_DM_Cryo_et;   //!
	TBranch        *b_MET_DM_Cryo_sumet;   //!
	TBranch        *b_METJetsInfo_JetPtWeightedEventEMFraction;   //!
	TBranch        *b_METJetsInfo_JetPtWeightedNumAssociatedTracks;   //!
	TBranch        *b_METJetsInfo_JetPtWeightedSize;   //!
	TBranch        *b_METJetsInfo_LeadingJetEt;   //!
	TBranch        *b_METJetsInfo_LeadingJetEta;   //!
	
	TBranch        *b_vxp_n;   //!
	TBranch        *b_vxp_x;   //!
	TBranch        *b_vxp_y;   //!
	TBranch        *b_vxp_z;   //!
	TBranch        *b_vxp_cov_x;   //!
	TBranch        *b_vxp_cov_y;   //!
	TBranch        *b_vxp_cov_z;   //!
	TBranch        *b_vxp_chi2;   //!
	TBranch        *b_vxp_ndof;   //!
	TBranch        *b_vxp_px;   //!
	TBranch        *b_vxp_py;   //!
	TBranch        *b_vxp_pz;   //!
	TBranch        *b_vxp_E;   //!
	TBranch        *b_vxp_m;   //!
	TBranch        *b_vxp_nTracks;   //!
	TBranch        *b_vxp_sumPt;   //!
	TBranch        *b_vxp_type;   //!
	TBranch        *b_vxp_trk_n;   //!
	TBranch        *b_vxp_trk_index;   //!
	
	TBranch        *b_muonTruth_n;   //!
	TBranch        *b_muonTruth_pt;   //!
	TBranch        *b_muonTruth_m;   //!
	TBranch        *b_muonTruth_eta;   //!
	TBranch        *b_muonTruth_phi;   //!
	TBranch        *b_muonTruth_charge;   //!
	TBranch        *b_muonTruth_PDGID;   //!
	TBranch        *b_muonTruth_barcode;   //!
	TBranch        *b_muonTruth_type;   //!
	TBranch        *b_muonTruth_origin;   //!
	
	TBranch        *b_mcevt_n;   //!
	TBranch        *b_mcevt_signal_process_id;   //!
	TBranch        *b_mcevt_event_number;   //!
	TBranch        *b_mcevt_event_scale;   //!
	TBranch        *b_mcevt_alphaQCD;   //!
	TBranch        *b_mcevt_alphaQED;   //!
	TBranch        *b_mcevt_pdf_id1;   //!
	TBranch        *b_mcevt_pdf_id2;   //!
	TBranch        *b_mcevt_pdf_x1;   //!
	TBranch        *b_mcevt_pdf_x2;   //!
	TBranch        *b_mcevt_pdf_scale;   //!
	TBranch        *b_mcevt_pdf1;   //!
	TBranch        *b_mcevt_pdf2;   //!
	TBranch        *b_mcevt_weight;   //!
	
	TBranch        *b_mc_n;   //!
	TBranch        *b_mc_pt;   //!
	TBranch        *b_mc_m;   //!
	TBranch        *b_mc_eta;   //!
	TBranch        *b_mc_phi;   //!
	TBranch        *b_mc_status;   //!
	TBranch        *b_mc_barcode;   //!
	TBranch        *b_mc_parents;   //!
	TBranch        *b_mc_children;   //!
	TBranch        *b_mc_pdgId;   //!
	TBranch        *b_mc_charge;   //!
	TBranch        *b_mc_vx_x;   //!
	TBranch        *b_mc_vx_y;   //!
	TBranch        *b_mc_vx_z;   //!
	TBranch        *b_mc_child_index;   //!
	TBranch        *b_mc_parent_index;   //!
	
	TBranch        *b_trig_L1_TAV;   //!
	TBranch        *b_trig_L2_passedPhysics;   //!
	TBranch        *b_trig_EF_passedPhysics;   //!
	TBranch        *b_trig_L1_TBP;   //!
	TBranch        *b_trig_L1_TAP;   //!
	TBranch        *b_trig_L2_passedRaw;   //!
	TBranch        *b_trig_EF_passedRaw;   //!
	TBranch        *b_trig_L2_truncated;   //!
	TBranch        *b_trig_EF_truncated;   //!
	TBranch        *b_trig_L2_resurrected;   //!
	TBranch        *b_trig_EF_resurrected;   //!
	TBranch        *b_trig_L2_passedThrough;   //!
	TBranch        *b_trig_EF_passedThrough;   //!
	TBranch        *b_trig_DB_SMK;   //!
	TBranch        *b_trig_DB_L1PSK;   //!
	TBranch        *b_trig_DB_HLTPSK;   //!
	TBranch        *b_trig_bgCode;   //!
	
	TBranch        *b_trig_L1_mu_n;   //!
	TBranch        *b_trig_L1_mu_pt;   //!
	TBranch        *b_trig_L1_mu_eta;   //!
	TBranch        *b_trig_L1_mu_phi;   //!
	TBranch        *b_trig_L1_mu_thrName;   //!
	TBranch        *b_trig_L2_muonfeature_n;   //!
	TBranch        *b_trig_L2_muonfeature_pt;   //!
	TBranch        *b_trig_L2_muonfeature_eta;   //!
	TBranch        *b_trig_L2_muonfeature_phi;   //!
	TBranch        *b_trig_L2_muonfeaturedetails_n;   //!
	TBranch        *b_trig_L2_combmuonfeature_n;   //!
	TBranch        *b_trig_L2_combmuonfeature_pt;   //!
	TBranch        *b_trig_L2_combmuonfeature_eta;   //!
	TBranch        *b_trig_L2_combmuonfeature_phi;   //!
	TBranch        *b_trig_L2_combmuonfeature_idscantrk_index;   //!
	TBranch        *b_trig_L2_combmuonfeature_sitracktrk_index;   //!
	TBranch        *b_trig_L2_isomuonfeature_n;   //!
	TBranch        *b_trig_L2_isomuonfeature_pt;   //!
	TBranch        *b_trig_L2_isomuonfeature_eta;   //!
	TBranch        *b_trig_L2_isomuonfeature_phi;   //!
	TBranch        *b_trig_L2_isomuonfeature_EtInnerConeEC ;   //!
	TBranch        *b_trig_L2_isomuonfeature_EtOuterConeEC;   //!
	TBranch        *b_trig_L2_isomuonfeature_EtInnerConeHC;   //!
	TBranch        *b_trig_L2_isomuonfeature_EtOuterConeHC;   //!
	TBranch        *b_trig_L2_isomuonfeature_NTracksCone;   //!
	TBranch        *b_trig_L2_isomuonfeature_SumPtTracksCone;   //!
	TBranch        *b_trig_L2_isomuonfeature_PtMuTracksCone;   //!
	TBranch        *b_trig_L2_tilemufeature_n;   //!
	TBranch        *b_trig_L2_tilemufeature_eta;   //!
	TBranch        *b_trig_L2_tilemufeature_phi;   //!
	TBranch        *b_trig_L2_tiletrackmufeature_n;   //!
	TBranch        *b_trig_L2_tiletrackmufeature_pt;   //!
	TBranch        *b_trig_L2_tiletrackmufeature_eta;   //!
	TBranch        *b_trig_L2_tiletrackmufeature_phi;   //!
	TBranch        *b_trig_L2_tiletrackmufeature_tilemu_index;   //!
	TBranch        *b_trig_L2_tiletrackmufeature_idtrk_algorithmId;   //!
	TBranch        *b_trig_L2_tiletrackmufeature_idtrk_trackStatus;   //!
	TBranch        *b_trig_L2_tiletrackmufeature_idtrk_chi2Ndof;   //!
	TBranch        *b_trig_L2_tiletrackmufeature_idtrk_idtrkfitpar_a0;   //!
	TBranch        *b_trig_L2_tiletrackmufeature_idtrk_idtrkfitpar_z0;   //!
	TBranch        *b_trig_L2_tiletrackmufeature_idtrk_idtrkfitpar_phi0;   //!
	TBranch        *b_trig_L2_tiletrackmufeature_idtrk_idtrkfitpar_eta;   //!
	TBranch        *b_trig_L2_tiletrackmufeature_idtrk_idtrkfitpar_pt;   //!
	TBranch        *b_trig_L2_tiletrackmufeature_idtrk_idtrkfitpar_hasidtrkfitpar;   //!
	TBranch        *b_trig_L2_tiletrackmufeature_idtrk_hasidtrk;   //!
	TBranch        *b_trig_EF_trigmuonef_n;   //!
	TBranch        *b_trig_EF_trigmuonef_track_n;   //!
	TBranch        *b_trig_EF_trigmuonef_track_MuonType;   //!
	TBranch        *b_trig_EF_trigmuonef_track_MS_pt;   //!
	TBranch        *b_trig_EF_trigmuonef_track_MS_eta;   //!
	TBranch        *b_trig_EF_trigmuonef_track_MS_phi;   //!
	TBranch        *b_trig_EF_trigmuonef_track_MS_hasMS;   //!
	TBranch        *b_trig_EF_trigmuonef_track_SA_pt;   //!
	TBranch        *b_trig_EF_trigmuonef_track_SA_eta;   //!
	TBranch        *b_trig_EF_trigmuonef_track_SA_phi;   //!
	TBranch        *b_trig_EF_trigmuonef_track_SA_hasSA;   //!
	TBranch        *b_trig_EF_trigmuonef_track_CB_pt;   //!
	TBranch        *b_trig_EF_trigmuonef_track_CB_eta;   //!
	TBranch        *b_trig_EF_trigmuonef_track_CB_phi;   //!
	TBranch        *b_trig_EF_trigmuonef_track_CB_hasCB;   //!
	TBranch        *b_trig_EF_trigmugirl_n;   //!
	TBranch        *b_trig_EF_trigmugirl_track_n;   //!
	TBranch        *b_trig_EF_trigmugirl_track_MuonType;   //!
	TBranch        *b_trig_EF_trigmugirl_track_MS_pt;   //!
	TBranch        *b_trig_EF_trigmugirl_track_MS_eta;   //!
	TBranch        *b_trig_EF_trigmugirl_track_MS_phi;   //!
	TBranch        *b_trig_EF_trigmugirl_track_MS_hasMS;   //!
	TBranch        *b_trig_EF_trigmugirl_track_SA_pt;   //!
	TBranch        *b_trig_EF_trigmugirl_track_SA_eta;   //!
	TBranch        *b_trig_EF_trigmugirl_track_SA_phi;   //!
	TBranch        *b_trig_EF_trigmugirl_track_SA_hasSA;   //!
	TBranch        *b_trig_EF_trigmugirl_track_CB_pt;   //!
	TBranch        *b_trig_EF_trigmugirl_track_CB_eta;   //!
	TBranch        *b_trig_EF_trigmugirl_track_CB_phi;   //!
	TBranch        *b_trig_EF_trigmugirl_track_CB_hasCB;   //!
	TBranch        *b_trig_L2_sitrack_muon_n;   //!
	TBranch        *b_trig_L2_sitrack_muon_algorithmId;   //!
	TBranch        *b_trig_L2_sitrack_muon_trackStatus;   //!
	TBranch        *b_trig_L2_sitrack_muon_chi2Ndof;   //!
	TBranch        *b_trig_L2_sitrack_muon_a0;   //!
	TBranch        *b_trig_L2_sitrack_muon_z0;   //!
	TBranch        *b_trig_L2_sitrack_muon_phi0;   //!
	TBranch        *b_trig_L2_sitrack_muon_eta;   //!
	TBranch        *b_trig_L2_sitrack_muon_pt;   //!
	TBranch        *b_trig_L2_idscan_muon_n;   //!
	TBranch        *b_trig_L2_idscan_muon_algorithmId;   //!
	TBranch        *b_trig_L2_idscan_muon_trackStatus;   //!
	TBranch        *b_trig_L2_idscan_muon_chi2Ndof;   //!
	TBranch        *b_trig_L2_idscan_muon_a0;   //!
	TBranch        *b_trig_L2_idscan_muon_z0;   //!
	TBranch        *b_trig_L2_idscan_muon_phi0;   //!
	TBranch        *b_trig_L2_idscan_muon_eta;   //!
	TBranch        *b_trig_L2_idscan_muon_pt;   //!
	TBranch        *b_trig_L2_sitrack_isomuon_n;   //!
	TBranch        *b_trig_L2_sitrack_isomuon_algorithmId;   //!
	TBranch        *b_trig_L2_sitrack_isomuon_trackStatus;   //!
	TBranch        *b_trig_L2_sitrack_isomuon_chi2Ndof;   //!
	TBranch        *b_trig_L2_sitrack_isomuon_a0;   //!
	TBranch        *b_trig_L2_sitrack_isomuon_z0;   //!
	TBranch        *b_trig_L2_sitrack_isomuon_phi0;   //!
	TBranch        *b_trig_L2_sitrack_isomuon_eta;   //!
	TBranch        *b_trig_L2_sitrack_isomuon_pt;   //!
	TBranch        *b_trig_L2_idscan_isomuon_n;   //!
	TBranch        *b_trig_L2_idscan_isomuon_algorithmId;   //!
	TBranch        *b_trig_L2_idscan_isomuon_trackStatus;   //!
	TBranch        *b_trig_L2_idscan_isomuon_chi2Ndof;   //!
	TBranch        *b_trig_L2_idscan_isomuon_a0;   //!
	TBranch        *b_trig_L2_idscan_isomuon_z0;   //!
	TBranch        *b_trig_L2_idscan_isomuon_phi0;   //!
	TBranch        *b_trig_L2_idscan_isomuon_eta;   //!
	TBranch        *b_trig_L2_idscan_isomuon_pt;   //!
	TBranch        *b_trig_RoI_L2_mu_n;   //!
	TBranch        *b_trig_RoI_L2_mu_type;   //!
	TBranch        *b_trig_RoI_L2_mu_lastStep;   //!
	TBranch        *b_trig_RoI_L2_mu_MuonFeature;   //!
	TBranch        *b_trig_RoI_L2_mu_MuonFeatureStatus;   //!
	TBranch        *b_trig_RoI_L2_mu_MuonFeatureDetails;   //!
	TBranch        *b_trig_RoI_L2_mu_MuonFeatureDetailsStatus;   //!
	TBranch        *b_trig_RoI_L2_mu_CombinedMuonFeature;   //!
	TBranch        *b_trig_RoI_L2_mu_CombinedMuonFeatureStatus;   //!
	TBranch        *b_trig_RoI_L2_mu_IsoMuonFeature;   //!
	TBranch        *b_trig_RoI_L2_mu_IsoMuonFeatureStatus;   //!
	TBranch        *b_trig_RoI_L2_mu_Muon_ROI;   //!
	TBranch        *b_trig_RoI_L2_mu_Muon_ROIStatus;   //!
	TBranch        *b_trig_RoI_L2_mu_TrigInDetTrackCollection_TrigSiTrack_Muon;   //!
	TBranch        *b_trig_RoI_L2_mu_TrigInDetTrackCollection_TrigSiTrack_MuonStatus;   //!
	TBranch        *b_trig_RoI_L2_mu_TrigInDetTrackCollection_TrigIDSCAN_Muon;   //!
	TBranch        *b_trig_RoI_L2_mu_TrigInDetTrackCollection_TrigIDSCAN_MuonStatus;   //!
	TBranch        *b_trig_RoI_L2_mu_TrigInDetTrackCollection_TrigSiTrack_muonIso;   //!
	TBranch        *b_trig_RoI_L2_mu_TrigInDetTrackCollection_TrigSiTrack_muonIsoStatus;   //!
	TBranch        *b_trig_RoI_L2_mu_TrigInDetTrackCollection_TrigIDSCAN_muonIso;   //!
	TBranch        *b_trig_RoI_L2_mu_TrigInDetTrackCollection_TrigIDSCAN_muonIsoStatus;   //!
	TBranch        *b_trig_RoI_L2_TileMu_n;   //!
	TBranch        *b_trig_RoI_L2_TileMu_type;   //!
	TBranch        *b_trig_RoI_L2_TileMu_lastStep;   //!
	TBranch        *b_trig_RoI_L2_TileMu_TileMuFeature;   //!
	TBranch        *b_trig_RoI_L2_TileMu_TileMuFeatureStatus;   //!
	TBranch        *b_trig_RoI_L2_TileMu_TileTrackMuFeature;   //!
	TBranch        *b_trig_RoI_L2_TileMu_TileTrackMuFeatureStatus;   //!
	TBranch        *b_trig_RoI_L2_TileMu_Muon_ROI;   //!
	TBranch        *b_trig_RoI_L2_TileMu_Muon_ROIStatus;   //!
	TBranch        *b_trig_RoI_L2_TileMu_TrigInDetTrackCollection_TrigSiTrack_Tile;   //!
	TBranch        *b_trig_RoI_L2_TileMu_TrigInDetTrackCollection_TrigSiTrack_TileStatus;   //!
	TBranch        *b_trig_RoI_L2_TileMu_TrigInDetTrackCollection_TrigIDSCAN_Tile;   //!
	TBranch        *b_trig_RoI_L2_TileMu_TrigInDetTrackCollection_TrigIDSCAN_TileStatus;   //!
	TBranch        *b_trig_RoI_EF_mu_n;   //!
	TBranch        *b_trig_RoI_EF_mu_type;   //!
	TBranch        *b_trig_RoI_EF_mu_lastStep;   //!
	TBranch        *b_trig_RoI_EF_mu_Muon_ROI;   //!
	TBranch        *b_trig_RoI_EF_mu_Muon_ROIStatus;   //!
	TBranch        *b_trig_RoI_EF_mu_TrackCollection_InDetTrigTrackSlimmer_Muon_EFID;   //!
	TBranch        *b_trig_RoI_EF_mu_TrackCollection_InDetTrigTrackSlimmer_Muon_EFIDStatus;   //!
	TBranch        *b_trig_RoI_EF_mu_TrigMuonEFInfoContainer;   //!
	TBranch        *b_trig_RoI_EF_mu_TrigMuonEFInfoContainerStatus;   //!
	TBranch        *b_trig_RoI_EF_mu_TrigMuonEFInfoContainer_MuGirl;   //!
	TBranch        *b_trig_RoI_EF_mu_TrigMuonEFInfoContainer_MuGirlStatus;   //!
	TBranch        *b_trig_RoI_EF_mu_TrigMuonEFInfoContainer_MuTagIMO_EF;   //!
	TBranch        *b_trig_RoI_EF_mu_TrigMuonEFInfoContainer_MuTagIMO_EFStatus;   //!
	TBranch        *b_trig_RoI_EF_TileMu_n;   //!
	TBranch        *b_trig_RoI_EF_TileMu_type;   //!
	TBranch        *b_trig_RoI_EF_TileMu_lastStep;   //!
	TBranch        *b_trig_RoI_EF_TileMu_Muon_ROI;   //!
	TBranch        *b_trig_RoI_EF_TileMu_Muon_ROIStatus;   //!
	TBranch        *b_trig_RoI_EF_TileMu_TrigMuonEFContainer;   //!
	TBranch        *b_trig_RoI_EF_TileMu_TrigMuonEFContainerStatus;   //!
	TBranch        *b_trig_RoI_EF_TileMu_TrigMuonEFInfoContainer;   //!
	TBranch        *b_trig_RoI_EF_TileMu_TrigMuonEFInfoContainerStatus;   //!
	TBranch        *b_trig_RoI_EF_TileMu_TrigMuonEFInfoContainer_MuGirl;   //!
	TBranch        *b_trig_RoI_EF_TileMu_TrigMuonEFInfoContainer_MuGirlStatus;   //!
	TBranch        *b_trig_RoI_EF_TileMu_TrigMuonEFInfoContainer_MuTagIMO_EF;   //!
	TBranch        *b_trig_RoI_EF_TileMu_TrigMuonEFInfoContainer_MuTagIMO_EFStatus;   //!
	
	TBranch        *b_trig_L2_met_MEx;   //!
	TBranch        *b_trig_L2_met_MEy;   //!
	TBranch        *b_trig_L2_met_MEz;   //!
	TBranch        *b_trig_L2_met_sumEt;   //!
	TBranch        *b_trig_L2_met_sumE;   //!
	TBranch        *b_trig_L2_met_flag;   //!
	TBranch        *b_trig_L2_met_nameOfComponent;   //!
	TBranch        *b_trig_L2_met_MExComponent;   //!
	TBranch        *b_trig_L2_met_MEyComponent;   //!
	TBranch        *b_trig_L2_met_MEzComponent;   //!
	TBranch        *b_trig_L2_met_sumEtComponent;   //!
	TBranch        *b_trig_L2_met_sumEComponent;   //!
	TBranch        *b_trig_L2_met_componentCalib0;   //!
	TBranch        *b_trig_L2_met_componentCalib1;   //!
	TBranch        *b_trig_L2_met_sumOfSigns;   //!
	TBranch        *b_trig_L2_met_usedChannels;   //!
	TBranch        *b_trig_L2_met_status;   //!
	TBranch        *b_trig_EF_met_MEx;   //!
	TBranch        *b_trig_EF_met_MEy;   //!
	TBranch        *b_trig_EF_met_MEz;   //!
	TBranch        *b_trig_EF_met_sumEt;   //!
	TBranch        *b_trig_EF_met_sumE;   //!
	TBranch        *b_trig_EF_met_flag;   //!
	TBranch        *b_trig_EF_met_nameOfComponent;   //!
	TBranch        *b_trig_EF_met_MExComponent;   //!
	TBranch        *b_trig_EF_met_MEyComponent;   //!
	TBranch        *b_trig_EF_met_MEzComponent;   //!
	TBranch        *b_trig_EF_met_sumEtComponent;   //!
	TBranch        *b_trig_EF_met_sumEComponent;   //!
	TBranch        *b_trig_EF_met_componentCalib0;   //!
	TBranch        *b_trig_EF_met_componentCalib1;   //!
	TBranch        *b_trig_EF_met_sumOfSigns;   //!
	TBranch        *b_trig_EF_met_usedChannels;   //!
	TBranch        *b_trig_EF_met_status;   //!

	WZphysD3PD(TTree *tree=0, Bool_t ismc = false);
	virtual ~WZphysD3PD();
	virtual Int_t    Cut(Long64_t entry);
	virtual Int_t    GetEntry(Long64_t entry);
	virtual Long64_t LoadTree(Long64_t entry);
	virtual void     Init(TTree *tree);
	virtual void     Loop();
	virtual Bool_t   Notify();
	virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef WZphysD3PD_cxx
WZphysD3PD::WZphysD3PD(TTree *tree, Bool_t ismc)
{
	isMC = ismc;

	/*
	// if parameter tree is not specified (or zero), connect the file
	// used to generate this class and read the Tree.
	if (tree == 0) {
		TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("group10.phys-sm.06830_002695.D3PD._00017.root");
		if (!f) {
			f = new TFile("group10.phys-sm.06830_002695.D3PD._00017.root");
		}
		tree = (TTree*)gDirectory->Get("physics");

	}
	*/
	Init(tree);
}

WZphysD3PD::~WZphysD3PD()
{
	if (!fChain) return;
	//delete fChain->GetCurrentFile();
}

Int_t WZphysD3PD::GetEntry(Long64_t entry)
{
	// Read contents of entry.
	if (!fChain) return 0;
	return fChain->GetEntry(entry);
}
Long64_t WZphysD3PD::LoadTree(Long64_t entry)
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

void WZphysD3PD::Init(TTree *tree)
{
	// The Init() function is called when the selector needs to initialize
	// a new tree or chain. Typically here the branch addresses and branch
	// pointers of the tree will be set.
	// It is normally not necessary to make changes to the generated
	// code, but the routine can be extended by the user if needed.
	// Init() will be called many times when running on PROOF
	// (once per file to be processed).

	// Set object pointer
	mu_muid_E = 0;
	mu_muid_pt = 0;
	mu_muid_m = 0;
	mu_muid_eta = 0;
	mu_muid_phi = 0;
	mu_muid_px = 0;
	mu_muid_py = 0;
	mu_muid_pz = 0;
	mu_muid_charge = 0;
	mu_muid_allauthor = 0;
	mu_muid_author = 0;
	mu_muid_beta = 0;
	mu_muid_isMuonLikelihood = 0;
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
	mu_muid_etCore = 0;
	mu_muid_energyLossType = 0;
	mu_muid_caloMuonIdTag = 0;
	mu_muid_caloLRLikelihood = 0;
	mu_muid_bestMatch = 0;
	mu_muid_isStandAloneMuon = 0;
	mu_muid_isCombinedMuon = 0;
	mu_muid_isLowPtReconstructedMuon = 0;
	mu_muid_loose = 0;
	mu_muid_medium = 0;
	mu_muid_tight = 0;
	mu_muid_d0_exPV = 0;
	mu_muid_z0_exPV = 0;
	mu_muid_phi_exPV = 0;
	mu_muid_theta_exPV = 0;
	mu_muid_qoverp_exPV = 0;
	mu_muid_cb_d0_exPV = 0;
	mu_muid_cb_z0_exPV = 0;
	mu_muid_cb_phi_exPV = 0;
	mu_muid_cb_theta_exPV = 0;
	mu_muid_cb_qoverp_exPV = 0;
	mu_muid_id_d0_exPV = 0;
	mu_muid_id_z0_exPV = 0;
	mu_muid_id_phi_exPV = 0;
	mu_muid_id_theta_exPV = 0;
	mu_muid_id_qoverp_exPV = 0;
	mu_muid_me_d0_exPV = 0;
	mu_muid_me_z0_exPV = 0;
	mu_muid_me_phi_exPV = 0;
	mu_muid_me_theta_exPV = 0;
	mu_muid_me_qoverp_exPV = 0;
	mu_muid_ie_d0_exPV = 0;
	mu_muid_ie_z0_exPV = 0;
	mu_muid_ie_phi_exPV = 0;
	mu_muid_ie_theta_exPV = 0;
	mu_muid_ie_qoverp_exPV = 0;
	mu_muid_SpaceTime_detID = 0;
	mu_muid_SpaceTime_t = 0;
	mu_muid_SpaceTime_tError = 0;
	mu_muid_SpaceTime_weight = 0;
	mu_muid_SpaceTime_x = 0;
	mu_muid_SpaceTime_y = 0;
	mu_muid_SpaceTime_z = 0;
	mu_muid_SpaceTime_t_Tile = 0;
	mu_muid_SpaceTime_tError_Tile = 0;
	mu_muid_SpaceTime_weight_Tile = 0;
	mu_muid_SpaceTime_x_Tile = 0;
	mu_muid_SpaceTime_y_Tile = 0;
	mu_muid_SpaceTime_z_Tile = 0;
	mu_muid_SpaceTime_t_TRT = 0;
	mu_muid_SpaceTime_tError_TRT = 0;
	mu_muid_SpaceTime_weight_TRT = 0;
	mu_muid_SpaceTime_x_TRT = 0;
	mu_muid_SpaceTime_y_TRT = 0;
	mu_muid_SpaceTime_z_TRT = 0;
	mu_muid_SpaceTime_t_MDT = 0;
	mu_muid_SpaceTime_tError_MDT = 0;
	mu_muid_SpaceTime_weight_MDT = 0;
	mu_muid_SpaceTime_x_MDT = 0;
	mu_muid_SpaceTime_y_MDT = 0;
	mu_muid_SpaceTime_z_MDT = 0;
	mu_muid_TileCellEnergyLayer1 = 0;
	mu_muid_TileTimeLayer1 = 0;
	mu_muid_TileCellRmsNoiseLayer1 = 0;
	mu_muid_TileCellSignLayer1 = 0;
	mu_muid_TileCellEnergyLayer2 = 0;
	mu_muid_TileTimeLayer2 = 0;
	mu_muid_TileCellRmsNoiseLayer2 = 0;
	mu_muid_TileCellSignLayer2 = 0;
	mu_muid_TileCellEnergyLayer3 = 0;
	mu_muid_TileTimeLayer3 = 0;
	mu_muid_TileCellRmsNoiseLayer3 = 0;
	mu_muid_TileCellSignLayer3 = 0;
	mu_muid_MSTrkT0_1 = 0;
	mu_muid_MSTrkT0_2 = 0;
	mu_muid_MSTrkT0_3 = 0;
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
	mu_muid_id_cov_d0_exPV = 0;
	mu_muid_id_cov_z0_exPV = 0;
	mu_muid_id_cov_phi_exPV = 0;
	mu_muid_id_cov_theta_exPV = 0;
	mu_muid_id_cov_qoverp_exPV = 0;
	mu_muid_id_cov_d0_z0_exPV = 0;
	mu_muid_id_cov_d0_phi_exPV = 0;
	mu_muid_id_cov_d0_theta_exPV = 0;
	mu_muid_id_cov_d0_qoverp_exPV = 0;
	mu_muid_id_cov_z0_phi_exPV = 0;
	mu_muid_id_cov_z0_theta_exPV = 0;
	mu_muid_id_cov_z0_qoverp_exPV = 0;
	mu_muid_id_cov_phi_theta_exPV = 0;
	mu_muid_id_cov_phi_qoverp_exPV = 0;
	mu_muid_id_cov_theta_qoverp_exPV = 0;
	mu_muid_me_cov_d0_exPV = 0;
	mu_muid_me_cov_z0_exPV = 0;
	mu_muid_me_cov_phi_exPV = 0;
	mu_muid_me_cov_theta_exPV = 0;
	mu_muid_me_cov_qoverp_exPV = 0;
	mu_muid_me_cov_d0_z0_exPV = 0;
	mu_muid_me_cov_d0_phi_exPV = 0;
	mu_muid_me_cov_d0_theta_exPV = 0;
	mu_muid_me_cov_d0_qoverp_exPV = 0;
	mu_muid_me_cov_z0_phi_exPV = 0;
	mu_muid_me_cov_z0_theta_exPV = 0;
	mu_muid_me_cov_z0_qoverp_exPV = 0;
	mu_muid_me_cov_phi_theta_exPV = 0;
	mu_muid_me_cov_phi_qoverp_exPV = 0;
	mu_muid_me_cov_theta_qoverp_exPV = 0;
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
	mu_muid_nOutliersOnTrack = 0;
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
	mu_muid_nGangedPixels = 0;
	mu_muid_nPixelDeadSensors = 0;
	mu_muid_nSCTDeadSensors = 0;
	mu_muid_nTRTDeadStraws = 0;
	mu_muid_expectBLayerHit = 0;
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
	mu_muid_truth_dr = 0;
	mu_muid_truth_E = 0;
	mu_muid_truth_pt = 0;
	mu_muid_truth_eta = 0;
	mu_muid_truth_phi = 0;
	mu_muid_truth_type = 0;
	mu_muid_truth_status = 0;
	mu_muid_truth_barcode = 0;
	mu_muid_truth_mothertype = 0;
	mu_muid_truth_motherbarcode = 0;
	mu_muid_truth_matched = 0;
	mu_muid_EFCB_dr = 0;
	mu_muid_EFCB_index = 0;
	mu_muid_EFMG_dr = 0;
	mu_muid_EFMG_index = 0;
	mu_muid_EFME_dr = 0;
	mu_muid_EFME_index = 0;
	mu_muid_L2CB_dr = 0;
	mu_muid_L2CB_index = 0;
	mu_muid_L1_dr = 0;
	mu_muid_L1_index = 0;
	
	mu_staco_E = 0;
	mu_staco_pt = 0;
	mu_staco_m = 0;
	mu_staco_eta = 0;
	mu_staco_phi = 0;
	mu_staco_px = 0;
	mu_staco_py = 0;
	mu_staco_pz = 0;
	mu_staco_charge = 0;
	mu_staco_allauthor = 0;
	mu_staco_author = 0;
	mu_staco_beta = 0;
	mu_staco_isMuonLikelihood = 0;
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
	mu_staco_etCore = 0;
	mu_staco_energyLossType = 0;
	mu_staco_caloMuonIdTag = 0;
	mu_staco_caloLRLikelihood = 0;
	mu_staco_bestMatch = 0;
	mu_staco_isStandAloneMuon = 0;
	mu_staco_isCombinedMuon = 0;
	mu_staco_isLowPtReconstructedMuon = 0;
	mu_staco_loose = 0;
	mu_staco_medium = 0;
	mu_staco_tight = 0;
	mu_staco_d0_exPV = 0;
	mu_staco_z0_exPV = 0;
	mu_staco_phi_exPV = 0;
	mu_staco_theta_exPV = 0;
	mu_staco_qoverp_exPV = 0;
	mu_staco_cb_d0_exPV = 0;
	mu_staco_cb_z0_exPV = 0;
	mu_staco_cb_phi_exPV = 0;
	mu_staco_cb_theta_exPV = 0;
	mu_staco_cb_qoverp_exPV = 0;
	mu_staco_id_d0_exPV = 0;
	mu_staco_id_z0_exPV = 0;
	mu_staco_id_phi_exPV = 0;
	mu_staco_id_theta_exPV = 0;
	mu_staco_id_qoverp_exPV = 0;
	mu_staco_me_d0_exPV = 0;
	mu_staco_me_z0_exPV = 0;
	mu_staco_me_phi_exPV = 0;
	mu_staco_me_theta_exPV = 0;
	mu_staco_me_qoverp_exPV = 0;
	mu_staco_ie_d0_exPV = 0;
	mu_staco_ie_z0_exPV = 0;
	mu_staco_ie_phi_exPV = 0;
	mu_staco_ie_theta_exPV = 0;
	mu_staco_ie_qoverp_exPV = 0;
	mu_staco_SpaceTime_detID = 0;
	mu_staco_SpaceTime_t = 0;
	mu_staco_SpaceTime_tError = 0;
	mu_staco_SpaceTime_weight = 0;
	mu_staco_SpaceTime_x = 0;
	mu_staco_SpaceTime_y = 0;
	mu_staco_SpaceTime_z = 0;
	mu_staco_SpaceTime_t_Tile = 0;
	mu_staco_SpaceTime_tError_Tile = 0;
	mu_staco_SpaceTime_weight_Tile = 0;
	mu_staco_SpaceTime_x_Tile = 0;
	mu_staco_SpaceTime_y_Tile = 0;
	mu_staco_SpaceTime_z_Tile = 0;
	mu_staco_SpaceTime_t_TRT = 0;
	mu_staco_SpaceTime_tError_TRT = 0;
	mu_staco_SpaceTime_weight_TRT = 0;
	mu_staco_SpaceTime_x_TRT = 0;
	mu_staco_SpaceTime_y_TRT = 0;
	mu_staco_SpaceTime_z_TRT = 0;
	mu_staco_SpaceTime_t_MDT = 0;
	mu_staco_SpaceTime_tError_MDT = 0;
	mu_staco_SpaceTime_weight_MDT = 0;
	mu_staco_SpaceTime_x_MDT = 0;
	mu_staco_SpaceTime_y_MDT = 0;
	mu_staco_SpaceTime_z_MDT = 0;
	mu_staco_TileCellEnergyLayer1 = 0;
	mu_staco_TileTimeLayer1 = 0;
	mu_staco_TileCellRmsNoiseLayer1 = 0;
	mu_staco_TileCellSignLayer1 = 0;
	mu_staco_TileCellEnergyLayer2 = 0;
	mu_staco_TileTimeLayer2 = 0;
	mu_staco_TileCellRmsNoiseLayer2 = 0;
	mu_staco_TileCellSignLayer2 = 0;
	mu_staco_TileCellEnergyLayer3 = 0;
	mu_staco_TileTimeLayer3 = 0;
	mu_staco_TileCellRmsNoiseLayer3 = 0;
	mu_staco_TileCellSignLayer3 = 0;
	mu_staco_MSTrkT0_1 = 0;
	mu_staco_MSTrkT0_2 = 0;
	mu_staco_MSTrkT0_3 = 0;
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
	mu_staco_id_cov_d0_exPV = 0;
	mu_staco_id_cov_z0_exPV = 0;
	mu_staco_id_cov_phi_exPV = 0;
	mu_staco_id_cov_theta_exPV = 0;
	mu_staco_id_cov_qoverp_exPV = 0;
	mu_staco_id_cov_d0_z0_exPV = 0;
	mu_staco_id_cov_d0_phi_exPV = 0;
	mu_staco_id_cov_d0_theta_exPV = 0;
	mu_staco_id_cov_d0_qoverp_exPV = 0;
	mu_staco_id_cov_z0_phi_exPV = 0;
	mu_staco_id_cov_z0_theta_exPV = 0;
	mu_staco_id_cov_z0_qoverp_exPV = 0;
	mu_staco_id_cov_phi_theta_exPV = 0;
	mu_staco_id_cov_phi_qoverp_exPV = 0;
	mu_staco_id_cov_theta_qoverp_exPV = 0;
	mu_staco_me_cov_d0_exPV = 0;
	mu_staco_me_cov_z0_exPV = 0;
	mu_staco_me_cov_phi_exPV = 0;
	mu_staco_me_cov_theta_exPV = 0;
	mu_staco_me_cov_qoverp_exPV = 0;
	mu_staco_me_cov_d0_z0_exPV = 0;
	mu_staco_me_cov_d0_phi_exPV = 0;
	mu_staco_me_cov_d0_theta_exPV = 0;
	mu_staco_me_cov_d0_qoverp_exPV = 0;
	mu_staco_me_cov_z0_phi_exPV = 0;
	mu_staco_me_cov_z0_theta_exPV = 0;
	mu_staco_me_cov_z0_qoverp_exPV = 0;
	mu_staco_me_cov_phi_theta_exPV = 0;
	mu_staco_me_cov_phi_qoverp_exPV = 0;
	mu_staco_me_cov_theta_qoverp_exPV = 0;
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
	mu_staco_nOutliersOnTrack = 0;
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
	mu_staco_nGangedPixels = 0;
	mu_staco_nPixelDeadSensors = 0;
	mu_staco_nSCTDeadSensors = 0;
	mu_staco_nTRTDeadStraws = 0;
	mu_staco_expectBLayerHit = 0;
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
	mu_staco_truth_dr = 0;
	mu_staco_truth_E = 0;
	mu_staco_truth_pt = 0;
	mu_staco_truth_eta = 0;
	mu_staco_truth_phi = 0;
	mu_staco_truth_type = 0;
	mu_staco_truth_status = 0;
	mu_staco_truth_barcode = 0;
	mu_staco_truth_mothertype = 0;
	mu_staco_truth_motherbarcode = 0;
	mu_staco_truth_matched = 0;
	mu_staco_EFCB_dr = 0;
	mu_staco_EFCB_index = 0;
	mu_staco_EFMG_dr = 0;
	mu_staco_EFMG_index = 0;
	mu_staco_EFME_dr = 0;
	mu_staco_EFME_index = 0;
	mu_staco_L2CB_dr = 0;
	mu_staco_L2CB_index = 0;
	mu_staco_L1_dr = 0;
	mu_staco_L1_index = 0;
	
	mu_calo_E = 0;
	mu_calo_pt = 0;
	mu_calo_m = 0;
	mu_calo_eta = 0;
	mu_calo_phi = 0;
	mu_calo_px = 0;
	mu_calo_py = 0;
	mu_calo_pz = 0;
	mu_calo_charge = 0;
	mu_calo_allauthor = 0;
	mu_calo_hastrack = 0;
	mu_calo_truth_dr = 0;
	mu_calo_truth_E = 0;
	mu_calo_truth_pt = 0;
	mu_calo_truth_eta = 0;
	mu_calo_truth_phi = 0;
	mu_calo_truth_type = 0;
	mu_calo_truth_status = 0;
	mu_calo_truth_barcode = 0;
	mu_calo_truth_mothertype = 0;
	mu_calo_truth_motherbarcode = 0;
	mu_calo_truth_matched = 0;
	
	vxp_x = 0;
	vxp_y = 0;
	vxp_z = 0;
	vxp_cov_x = 0;
	vxp_cov_y = 0;
	vxp_cov_z = 0;
	vxp_chi2 = 0;
	vxp_ndof = 0;
	vxp_px = 0;
	vxp_py = 0;
	vxp_pz = 0;
	vxp_E = 0;
	vxp_m = 0;
	vxp_nTracks = 0;
	vxp_sumPt = 0;
	vxp_type = 0;
	vxp_trk_n = 0;
	vxp_trk_index = 0;
	
	muonTruth_pt = 0;
	muonTruth_m = 0;
	muonTruth_eta = 0;
	muonTruth_phi = 0;
	muonTruth_charge = 0;
	muonTruth_PDGID = 0;
	muonTruth_barcode = 0;
	muonTruth_type = 0;
	muonTruth_origin = 0;
	
	mcevt_signal_process_id = 0;
	mcevt_event_number = 0;
	mcevt_event_scale = 0;
	mcevt_alphaQCD = 0;
	mcevt_alphaQED = 0;
	mcevt_pdf_id1 = 0;
	mcevt_pdf_id2 = 0;
	mcevt_pdf_x1 = 0;
	mcevt_pdf_x2 = 0;
	mcevt_pdf_scale = 0;
	mcevt_pdf1 = 0;
	mcevt_pdf2 = 0;
	mcevt_weight = 0;
	
	mc_pt = 0;
	mc_m = 0;
	mc_eta = 0;
	mc_phi = 0;
	mc_status = 0;
	mc_barcode = 0;
	mc_parents = 0;
	mc_children = 0;
	mc_pdgId = 0;
	mc_charge = 0;
	mc_vx_x = 0;
	mc_vx_y = 0;
	mc_vx_z = 0;
	mc_child_index = 0;
	mc_parent_index = 0;
	
	trig_L1_TAV = 0;
	trig_L2_passedPhysics = 0;
	trig_EF_passedPhysics = 0;
	trig_L1_TBP = 0;
	trig_L1_TAP = 0;
	trig_L2_passedRaw = 0;
	trig_EF_passedRaw = 0;
	trig_L2_resurrected = 0;
	trig_EF_resurrected = 0;
	trig_L2_passedThrough = 0;
	trig_EF_passedThrough = 0;
	
	trig_L1_mu_pt = 0;
	trig_L1_mu_eta = 0;
	trig_L1_mu_phi = 0;
	trig_L1_mu_thrName = 0;
	trig_L2_muonfeature_pt = 0;
	trig_L2_muonfeature_eta = 0;
	trig_L2_muonfeature_phi = 0;
	trig_L2_combmuonfeature_pt = 0;
	trig_L2_combmuonfeature_eta = 0;
	trig_L2_combmuonfeature_phi = 0;
	trig_L2_combmuonfeature_idscantrk_index = 0;
	trig_L2_combmuonfeature_sitracktrk_index = 0;
	trig_L2_isomuonfeature_pt = 0;
	trig_L2_isomuonfeature_eta = 0;
	trig_L2_isomuonfeature_phi = 0;
	trig_L2_isomuonfeature_EtInnerConeEC  = 0;
	trig_L2_isomuonfeature_EtOuterConeEC = 0;
	trig_L2_isomuonfeature_EtInnerConeHC = 0;
	trig_L2_isomuonfeature_EtOuterConeHC = 0;
	trig_L2_isomuonfeature_NTracksCone = 0;
	trig_L2_isomuonfeature_SumPtTracksCone = 0;
	trig_L2_isomuonfeature_PtMuTracksCone = 0;
	trig_L2_tilemufeature_eta = 0;
	trig_L2_tilemufeature_phi = 0;
	trig_L2_tiletrackmufeature_pt = 0;
	trig_L2_tiletrackmufeature_eta = 0;
	trig_L2_tiletrackmufeature_phi = 0;
	trig_L2_tiletrackmufeature_tilemu_index = 0;
	trig_L2_tiletrackmufeature_idtrk_algorithmId = 0;
	trig_L2_tiletrackmufeature_idtrk_trackStatus = 0;
	trig_L2_tiletrackmufeature_idtrk_chi2Ndof = 0;
	trig_L2_tiletrackmufeature_idtrk_idtrkfitpar_a0 = 0;
	trig_L2_tiletrackmufeature_idtrk_idtrkfitpar_z0 = 0;
	trig_L2_tiletrackmufeature_idtrk_idtrkfitpar_phi0 = 0;
	trig_L2_tiletrackmufeature_idtrk_idtrkfitpar_eta = 0;
	trig_L2_tiletrackmufeature_idtrk_idtrkfitpar_pt = 0;
	trig_L2_tiletrackmufeature_idtrk_idtrkfitpar_hasidtrkfitpar = 0;
	trig_L2_tiletrackmufeature_idtrk_hasidtrk = 0;
	trig_EF_trigmuonef_track_n = 0;
	trig_EF_trigmuonef_track_MuonType = 0;
	trig_EF_trigmuonef_track_MS_pt = 0;
	trig_EF_trigmuonef_track_MS_eta = 0;
	trig_EF_trigmuonef_track_MS_phi = 0;
	trig_EF_trigmuonef_track_MS_hasMS = 0;
	trig_EF_trigmuonef_track_SA_pt = 0;
	trig_EF_trigmuonef_track_SA_eta = 0;
	trig_EF_trigmuonef_track_SA_phi = 0;
	trig_EF_trigmuonef_track_SA_hasSA = 0;
	trig_EF_trigmuonef_track_CB_pt = 0;
	trig_EF_trigmuonef_track_CB_eta = 0;
	trig_EF_trigmuonef_track_CB_phi = 0;
	trig_EF_trigmuonef_track_CB_hasCB = 0;
	trig_EF_trigmugirl_track_n = 0;
	trig_EF_trigmugirl_track_MuonType = 0;
	trig_EF_trigmugirl_track_MS_pt = 0;
	trig_EF_trigmugirl_track_MS_eta = 0;
	trig_EF_trigmugirl_track_MS_phi = 0;
	trig_EF_trigmugirl_track_MS_hasMS = 0;
	trig_EF_trigmugirl_track_SA_pt = 0;
	trig_EF_trigmugirl_track_SA_eta = 0;
	trig_EF_trigmugirl_track_SA_phi = 0;
	trig_EF_trigmugirl_track_SA_hasSA = 0;
	trig_EF_trigmugirl_track_CB_pt = 0;
	trig_EF_trigmugirl_track_CB_eta = 0;
	trig_EF_trigmugirl_track_CB_phi = 0;
	trig_EF_trigmugirl_track_CB_hasCB = 0;
	trig_L2_sitrack_muon_algorithmId = 0;
	trig_L2_sitrack_muon_trackStatus = 0;
	trig_L2_sitrack_muon_chi2Ndof = 0;
	trig_L2_sitrack_muon_a0 = 0;
	trig_L2_sitrack_muon_z0 = 0;
	trig_L2_sitrack_muon_phi0 = 0;
	trig_L2_sitrack_muon_eta = 0;
	trig_L2_sitrack_muon_pt = 0;
	trig_L2_idscan_muon_algorithmId = 0;
	trig_L2_idscan_muon_trackStatus = 0;
	trig_L2_idscan_muon_chi2Ndof = 0;
	trig_L2_idscan_muon_a0 = 0;
	trig_L2_idscan_muon_z0 = 0;
	trig_L2_idscan_muon_phi0 = 0;
	trig_L2_idscan_muon_eta = 0;
	trig_L2_idscan_muon_pt = 0;
	trig_L2_sitrack_isomuon_algorithmId = 0;
	trig_L2_sitrack_isomuon_trackStatus = 0;
	trig_L2_sitrack_isomuon_chi2Ndof = 0;
	trig_L2_sitrack_isomuon_a0 = 0;
	trig_L2_sitrack_isomuon_z0 = 0;
	trig_L2_sitrack_isomuon_phi0 = 0;
	trig_L2_sitrack_isomuon_eta = 0;
	trig_L2_sitrack_isomuon_pt = 0;
	trig_L2_idscan_isomuon_algorithmId = 0;
	trig_L2_idscan_isomuon_trackStatus = 0;
	trig_L2_idscan_isomuon_chi2Ndof = 0;
	trig_L2_idscan_isomuon_a0 = 0;
	trig_L2_idscan_isomuon_z0 = 0;
	trig_L2_idscan_isomuon_phi0 = 0;
	trig_L2_idscan_isomuon_eta = 0;
	trig_L2_idscan_isomuon_pt = 0;
	trig_RoI_L2_mu_type = 0;
	trig_RoI_L2_mu_lastStep = 0;
	trig_RoI_L2_mu_MuonFeature = 0;
	trig_RoI_L2_mu_MuonFeatureStatus = 0;
	trig_RoI_L2_mu_MuonFeatureDetails = 0;
	trig_RoI_L2_mu_MuonFeatureDetailsStatus = 0;
	trig_RoI_L2_mu_CombinedMuonFeature = 0;
	trig_RoI_L2_mu_CombinedMuonFeatureStatus = 0;
	trig_RoI_L2_mu_IsoMuonFeature = 0;
	trig_RoI_L2_mu_IsoMuonFeatureStatus = 0;
	trig_RoI_L2_mu_Muon_ROI = 0;
	trig_RoI_L2_mu_Muon_ROIStatus = 0;
	trig_RoI_L2_mu_TrigInDetTrackCollection_TrigSiTrack_Muon = 0;
	trig_RoI_L2_mu_TrigInDetTrackCollection_TrigSiTrack_MuonStatus = 0;
	trig_RoI_L2_mu_TrigInDetTrackCollection_TrigIDSCAN_Muon = 0;
	trig_RoI_L2_mu_TrigInDetTrackCollection_TrigIDSCAN_MuonStatus = 0;
	trig_RoI_L2_mu_TrigInDetTrackCollection_TrigSiTrack_muonIso = 0;
	trig_RoI_L2_mu_TrigInDetTrackCollection_TrigSiTrack_muonIsoStatus = 0;
	trig_RoI_L2_mu_TrigInDetTrackCollection_TrigIDSCAN_muonIso = 0;
	trig_RoI_L2_mu_TrigInDetTrackCollection_TrigIDSCAN_muonIsoStatus = 0;
	trig_RoI_L2_TileMu_type = 0;
	trig_RoI_L2_TileMu_lastStep = 0;
	trig_RoI_L2_TileMu_TileMuFeature = 0;
	trig_RoI_L2_TileMu_TileMuFeatureStatus = 0;
	trig_RoI_L2_TileMu_TileTrackMuFeature = 0;
	trig_RoI_L2_TileMu_TileTrackMuFeatureStatus = 0;
	trig_RoI_L2_TileMu_Muon_ROI = 0;
	trig_RoI_L2_TileMu_Muon_ROIStatus = 0;
	trig_RoI_L2_TileMu_TrigInDetTrackCollection_TrigSiTrack_Tile = 0;
	trig_RoI_L2_TileMu_TrigInDetTrackCollection_TrigSiTrack_TileStatus = 0;
	trig_RoI_L2_TileMu_TrigInDetTrackCollection_TrigIDSCAN_Tile = 0;
	trig_RoI_L2_TileMu_TrigInDetTrackCollection_TrigIDSCAN_TileStatus = 0;
	trig_RoI_EF_mu_type = 0;
	trig_RoI_EF_mu_lastStep = 0;
	trig_RoI_EF_mu_Muon_ROI = 0;
	trig_RoI_EF_mu_Muon_ROIStatus = 0;
	trig_RoI_EF_mu_TrackCollection_InDetTrigTrackSlimmer_Muon_EFID = 0;
	trig_RoI_EF_mu_TrackCollection_InDetTrigTrackSlimmer_Muon_EFIDStatus = 0;
	trig_RoI_EF_mu_TrigMuonEFInfoContainer = 0;
	trig_RoI_EF_mu_TrigMuonEFInfoContainerStatus = 0;
	trig_RoI_EF_mu_TrigMuonEFInfoContainer_MuGirl = 0;
	trig_RoI_EF_mu_TrigMuonEFInfoContainer_MuGirlStatus = 0;
	trig_RoI_EF_mu_TrigMuonEFInfoContainer_MuTagIMO_EF = 0;
	trig_RoI_EF_mu_TrigMuonEFInfoContainer_MuTagIMO_EFStatus = 0;
	trig_RoI_EF_TileMu_type = 0;
	trig_RoI_EF_TileMu_lastStep = 0;
	trig_RoI_EF_TileMu_Muon_ROI = 0;
	trig_RoI_EF_TileMu_Muon_ROIStatus = 0;
	trig_RoI_EF_TileMu_TrigMuonEFContainer = 0;
	trig_RoI_EF_TileMu_TrigMuonEFContainerStatus = 0;
	trig_RoI_EF_TileMu_TrigMuonEFInfoContainer = 0;
	trig_RoI_EF_TileMu_TrigMuonEFInfoContainerStatus = 0;
	trig_RoI_EF_TileMu_TrigMuonEFInfoContainer_MuGirl = 0;
	trig_RoI_EF_TileMu_TrigMuonEFInfoContainer_MuGirlStatus = 0;
	trig_RoI_EF_TileMu_TrigMuonEFInfoContainer_MuTagIMO_EF = 0;
	trig_RoI_EF_TileMu_TrigMuonEFInfoContainer_MuTagIMO_EFStatus = 0;
	
	trig_L2_met_nameOfComponent = 0;
	trig_L2_met_MExComponent = 0;
	trig_L2_met_MEyComponent = 0;
	trig_L2_met_MEzComponent = 0;
	trig_L2_met_sumEtComponent = 0;
	trig_L2_met_sumEComponent = 0;
	trig_L2_met_componentCalib0 = 0;
	trig_L2_met_componentCalib1 = 0;
	trig_L2_met_sumOfSigns = 0;
	trig_L2_met_usedChannels = 0;
	trig_L2_met_status = 0;
	trig_EF_met_nameOfComponent = 0;
	trig_EF_met_MExComponent = 0;
	trig_EF_met_MEyComponent = 0;
	trig_EF_met_MEzComponent = 0;
	trig_EF_met_sumEtComponent = 0;
	trig_EF_met_sumEComponent = 0;
	trig_EF_met_componentCalib0 = 0;
	trig_EF_met_componentCalib1 = 0;
	trig_EF_met_sumOfSigns = 0;
	trig_EF_met_usedChannels = 0;
	trig_EF_met_status = 0;
	// Set branch addresses and branch pointers
	if (!tree) return;
	fChain = tree;
	fCurrent = -1;
	fChain->SetMakeClass(1);

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
	
	fChain->SetBranchAddress("EF_2mu0_NoAlg", &EF_2mu0_NoAlg, &b_EF_2mu0_NoAlg);
	fChain->SetBranchAddress("EF_2mu10", &EF_2mu10, &b_EF_2mu10);
	fChain->SetBranchAddress("EF_2mu10_NoAlg", &EF_2mu10_NoAlg, &b_EF_2mu10_NoAlg);
	fChain->SetBranchAddress("EF_2mu4", &EF_2mu4, &b_EF_2mu4);
	fChain->SetBranchAddress("EF_2mu4_Bmumu", &EF_2mu4_Bmumu, &b_EF_2mu4_Bmumu);
	fChain->SetBranchAddress("EF_2mu4_Bmumux", &EF_2mu4_Bmumux, &b_EF_2mu4_Bmumux);
	fChain->SetBranchAddress("EF_2mu4_DiMu", &EF_2mu4_DiMu, &b_EF_2mu4_DiMu);
	fChain->SetBranchAddress("EF_2mu4_DiMu_SiTrk", &EF_2mu4_DiMu_SiTrk, &b_EF_2mu4_DiMu_SiTrk);
	fChain->SetBranchAddress("EF_2mu4_DiMu_noVtx", &EF_2mu4_DiMu_noVtx, &b_EF_2mu4_DiMu_noVtx);
	fChain->SetBranchAddress("EF_2mu4_DiMu_noVtx_noOS", &EF_2mu4_DiMu_noVtx_noOS, &b_EF_2mu4_DiMu_noVtx_noOS);
	fChain->SetBranchAddress("EF_2mu4_Jpsimumu", &EF_2mu4_Jpsimumu, &b_EF_2mu4_Jpsimumu);
	fChain->SetBranchAddress("EF_2mu4_Jpsimumu_IDTrkNoCut", &EF_2mu4_Jpsimumu_IDTrkNoCut, &b_EF_2mu4_Jpsimumu_IDTrkNoCut);
	fChain->SetBranchAddress("EF_2mu4_Upsimumu", &EF_2mu4_Upsimumu, &b_EF_2mu4_Upsimumu);
	fChain->SetBranchAddress("EF_2mu6", &EF_2mu6, &b_EF_2mu6);
	fChain->SetBranchAddress("EF_2mu6_Bmumu", &EF_2mu6_Bmumu, &b_EF_2mu6_Bmumu);
	fChain->SetBranchAddress("EF_2mu6_Bmumux", &EF_2mu6_Bmumux, &b_EF_2mu6_Bmumux);
	fChain->SetBranchAddress("EF_2mu6_DiMu", &EF_2mu6_DiMu, &b_EF_2mu6_DiMu);
	fChain->SetBranchAddress("EF_2mu6_Jpsimumu", &EF_2mu6_Jpsimumu, &b_EF_2mu6_Jpsimumu);
	fChain->SetBranchAddress("EF_2mu6_MG", &EF_2mu6_MG, &b_EF_2mu6_MG);
	fChain->SetBranchAddress("EF_2mu6_NoAlg", &EF_2mu6_NoAlg, &b_EF_2mu6_NoAlg);
	fChain->SetBranchAddress("EF_2mu6_Upsimumu", &EF_2mu6_Upsimumu, &b_EF_2mu6_Upsimumu);
	fChain->SetBranchAddress("EF_2mu6_g10_loose", &EF_2mu6_g10_loose, &b_EF_2mu6_g10_loose);
	
	fChain->SetBranchAddress("EF_mu0_NoAlg", &EF_mu0_NoAlg, &b_EF_mu0_NoAlg);
	fChain->SetBranchAddress("EF_mu0_comm_NoAlg", &EF_mu0_comm_NoAlg, &b_EF_mu0_comm_NoAlg);
	fChain->SetBranchAddress("EF_mu0_comm_empty_NoAlg", &EF_mu0_comm_empty_NoAlg, &b_EF_mu0_comm_empty_NoAlg);
	fChain->SetBranchAddress("EF_mu0_comm_firstempty_NoAlg", &EF_mu0_comm_firstempty_NoAlg, &b_EF_mu0_comm_firstempty_NoAlg);
	fChain->SetBranchAddress("EF_mu0_comm_unpaired_iso_NoAlg", &EF_mu0_comm_unpaired_iso_NoAlg, &b_EF_mu0_comm_unpaired_iso_NoAlg);
	fChain->SetBranchAddress("EF_mu0_comm_unpaired_noniso_NoAlg", &EF_mu0_comm_unpaired_noniso_NoAlg, &b_EF_mu0_comm_unpaired_noniso_NoAlg);
	fChain->SetBranchAddress("EF_mu0_empty_NoAlg", &EF_mu0_empty_NoAlg, &b_EF_mu0_empty_NoAlg);
	fChain->SetBranchAddress("EF_mu0_firstempty_NoAlg", &EF_mu0_firstempty_NoAlg, &b_EF_mu0_firstempty_NoAlg);
	fChain->SetBranchAddress("EF_mu0_missingRoi", &EF_mu0_missingRoi, &b_EF_mu0_missingRoi);
	fChain->SetBranchAddress("EF_mu0_outOfTime1", &EF_mu0_outOfTime1, &b_EF_mu0_outOfTime1);
	fChain->SetBranchAddress("EF_mu0_outOfTime2", &EF_mu0_outOfTime2, &b_EF_mu0_outOfTime2);
	fChain->SetBranchAddress("EF_mu0_rpcOnly", &EF_mu0_rpcOnly, &b_EF_mu0_rpcOnly);
	fChain->SetBranchAddress("EF_mu0_unpaired_iso_NoAlg", &EF_mu0_unpaired_iso_NoAlg, &b_EF_mu0_unpaired_iso_NoAlg);
	fChain->SetBranchAddress("EF_mu0_unpaired_noniso_NoAlg", &EF_mu0_unpaired_noniso_NoAlg, &b_EF_mu0_unpaired_noniso_NoAlg);
	fChain->SetBranchAddress("EF_mu10", &EF_mu10, &b_EF_mu10);
	fChain->SetBranchAddress("EF_mu10_Ecut12", &EF_mu10_Ecut12, &b_EF_mu10_Ecut12);
	fChain->SetBranchAddress("EF_mu10_Ecut123", &EF_mu10_Ecut123, &b_EF_mu10_Ecut123);
	fChain->SetBranchAddress("EF_mu10_Ecut13", &EF_mu10_Ecut13, &b_EF_mu10_Ecut13);
	fChain->SetBranchAddress("EF_mu10_IDTrkNoCut", &EF_mu10_IDTrkNoCut, &b_EF_mu10_IDTrkNoCut);
	fChain->SetBranchAddress("EF_mu10_MG", &EF_mu10_MG, &b_EF_mu10_MG);
	fChain->SetBranchAddress("EF_mu10_MSonly", &EF_mu10_MSonly, &b_EF_mu10_MSonly);
	fChain->SetBranchAddress("EF_mu10_MSonly_Ecut12", &EF_mu10_MSonly_Ecut12, &b_EF_mu10_MSonly_Ecut12);
	fChain->SetBranchAddress("EF_mu10_MSonly_Ecut123", &EF_mu10_MSonly_Ecut123, &b_EF_mu10_MSonly_Ecut123);
	fChain->SetBranchAddress("EF_mu10_MSonly_Ecut13", &EF_mu10_MSonly_Ecut13, &b_EF_mu10_MSonly_Ecut13);
	fChain->SetBranchAddress("EF_mu10_MSonly_tight", &EF_mu10_MSonly_tight, &b_EF_mu10_MSonly_tight);
	fChain->SetBranchAddress("EF_mu10_NoAlg", &EF_mu10_NoAlg, &b_EF_mu10_NoAlg);
	fChain->SetBranchAddress("EF_mu10_SiTrk", &EF_mu10_SiTrk, &b_EF_mu10_SiTrk);
	fChain->SetBranchAddress("EF_mu10_j30", &EF_mu10_j30, &b_EF_mu10_j30);
	fChain->SetBranchAddress("EF_mu10_tight", &EF_mu10_tight, &b_EF_mu10_tight);
	fChain->SetBranchAddress("EF_mu10i_loose", &EF_mu10i_loose, &b_EF_mu10i_loose);
	fChain->SetBranchAddress("EF_mu13", &EF_mu13, &b_EF_mu13);
	fChain->SetBranchAddress("EF_mu13_MG", &EF_mu13_MG, &b_EF_mu13_MG);
	fChain->SetBranchAddress("EF_mu13_MG_tight", &EF_mu13_MG_tight, &b_EF_mu13_MG_tight);
	fChain->SetBranchAddress("EF_mu13_tight", &EF_mu13_tight, &b_EF_mu13_tight);
	fChain->SetBranchAddress("EF_mu15", &EF_mu15, &b_EF_mu15);
	fChain->SetBranchAddress("EF_mu15_MG", &EF_mu15_MG, &b_EF_mu15_MG);
	fChain->SetBranchAddress("EF_mu15_NoAlg", &EF_mu15_NoAlg, &b_EF_mu15_NoAlg);
	fChain->SetBranchAddress("EF_mu20", &EF_mu20, &b_EF_mu20);
	fChain->SetBranchAddress("EF_mu20_MSonly", &EF_mu20_MSonly, &b_EF_mu20_MSonly);
	fChain->SetBranchAddress("EF_mu20_NoAlg", &EF_mu20_NoAlg, &b_EF_mu20_NoAlg);
	fChain->SetBranchAddress("EF_mu20_passHLT", &EF_mu20_passHLT, &b_EF_mu20_passHLT);
	fChain->SetBranchAddress("EF_mu20_slow", &EF_mu20_slow, &b_EF_mu20_slow);
	fChain->SetBranchAddress("EF_mu30_MSonly", &EF_mu30_MSonly, &b_EF_mu30_MSonly);
	fChain->SetBranchAddress("EF_mu4", &EF_mu4, &b_EF_mu4);
	fChain->SetBranchAddress("EF_mu40_MSonly", &EF_mu40_MSonly, &b_EF_mu40_MSonly);
	fChain->SetBranchAddress("EF_mu4_Bmumu", &EF_mu4_Bmumu, &b_EF_mu4_Bmumu);
	fChain->SetBranchAddress("EF_mu4_BmumuX", &EF_mu4_BmumuX, &b_EF_mu4_BmumuX);
	fChain->SetBranchAddress("EF_mu4_DiMu", &EF_mu4_DiMu, &b_EF_mu4_DiMu);
	fChain->SetBranchAddress("EF_mu4_DiMu_FS", &EF_mu4_DiMu_FS, &b_EF_mu4_DiMu_FS);
	fChain->SetBranchAddress("EF_mu4_DiMu_FS_noOS", &EF_mu4_DiMu_FS_noOS, &b_EF_mu4_DiMu_FS_noOS);
	fChain->SetBranchAddress("EF_mu4_DiMu_MG", &EF_mu4_DiMu_MG, &b_EF_mu4_DiMu_MG);
	fChain->SetBranchAddress("EF_mu4_DiMu_MG_FS", &EF_mu4_DiMu_MG_FS, &b_EF_mu4_DiMu_MG_FS);
	fChain->SetBranchAddress("EF_mu4_DiMu_SiTrk", &EF_mu4_DiMu_SiTrk, &b_EF_mu4_DiMu_SiTrk);
	fChain->SetBranchAddress("EF_mu4_DiMu_SiTrk_FS", &EF_mu4_DiMu_SiTrk_FS, &b_EF_mu4_DiMu_SiTrk_FS);
	fChain->SetBranchAddress("EF_mu4_DiMu_noOS", &EF_mu4_DiMu_noOS, &b_EF_mu4_DiMu_noOS);
	fChain->SetBranchAddress("EF_mu4_IDTrkNoCut", &EF_mu4_IDTrkNoCut, &b_EF_mu4_IDTrkNoCut);
	fChain->SetBranchAddress("EF_mu4_Jpsie5e3", &EF_mu4_Jpsie5e3, &b_EF_mu4_Jpsie5e3);
	fChain->SetBranchAddress("EF_mu4_Jpsie5e3_FS", &EF_mu4_Jpsie5e3_FS, &b_EF_mu4_Jpsie5e3_FS);
	fChain->SetBranchAddress("EF_mu4_Jpsie5e3_SiTrk", &EF_mu4_Jpsie5e3_SiTrk, &b_EF_mu4_Jpsie5e3_SiTrk);
	fChain->SetBranchAddress("EF_mu4_Jpsie5e3_SiTrk_FS", &EF_mu4_Jpsie5e3_SiTrk_FS, &b_EF_mu4_Jpsie5e3_SiTrk_FS);
	fChain->SetBranchAddress("EF_mu4_Jpsimumu", &EF_mu4_Jpsimumu, &b_EF_mu4_Jpsimumu);
	fChain->SetBranchAddress("EF_mu4_Jpsimumu_FS", &EF_mu4_Jpsimumu_FS, &b_EF_mu4_Jpsimumu_FS);
	fChain->SetBranchAddress("EF_mu4_Jpsimumu_SiTrk_FS", &EF_mu4_Jpsimumu_SiTrk_FS, &b_EF_mu4_Jpsimumu_SiTrk_FS);
	fChain->SetBranchAddress("EF_mu4_L1J10_matched", &EF_mu4_L1J10_matched, &b_EF_mu4_L1J10_matched);
	fChain->SetBranchAddress("EF_mu4_L1J15_matched", &EF_mu4_L1J15_matched, &b_EF_mu4_L1J15_matched);
	fChain->SetBranchAddress("EF_mu4_L1J30_matched", &EF_mu4_L1J30_matched, &b_EF_mu4_L1J30_matched);
	fChain->SetBranchAddress("EF_mu4_L1J55_matched", &EF_mu4_L1J55_matched, &b_EF_mu4_L1J55_matched);
	fChain->SetBranchAddress("EF_mu4_L1J5_matched", &EF_mu4_L1J5_matched, &b_EF_mu4_L1J5_matched);
	fChain->SetBranchAddress("EF_mu4_L2MSonly_EFFS_passL2", &EF_mu4_L2MSonly_EFFS_passL2, &b_EF_mu4_L2MSonly_EFFS_passL2);
	fChain->SetBranchAddress("EF_mu4_MG", &EF_mu4_MG, &b_EF_mu4_MG);
	fChain->SetBranchAddress("EF_mu4_MSonly", &EF_mu4_MSonly, &b_EF_mu4_MSonly);
	fChain->SetBranchAddress("EF_mu4_MSonly_EFFS_passL2", &EF_mu4_MSonly_EFFS_passL2, &b_EF_mu4_MSonly_EFFS_passL2);
	fChain->SetBranchAddress("EF_mu4_MSonly_MB2_noL2_EFFS", &EF_mu4_MSonly_MB2_noL2_EFFS, &b_EF_mu4_MSonly_MB2_noL2_EFFS);
	fChain->SetBranchAddress("EF_mu4_MSonly_cosmic", &EF_mu4_MSonly_cosmic, &b_EF_mu4_MSonly_cosmic);
	fChain->SetBranchAddress("EF_mu4_MSonly_outOfTime", &EF_mu4_MSonly_outOfTime, &b_EF_mu4_MSonly_outOfTime);
	fChain->SetBranchAddress("EF_mu4_MV", &EF_mu4_MV, &b_EF_mu4_MV);
	fChain->SetBranchAddress("EF_mu4_SiTrk", &EF_mu4_SiTrk, &b_EF_mu4_SiTrk);
	fChain->SetBranchAddress("EF_mu4_Trk_Jpsi", &EF_mu4_Trk_Jpsi, &b_EF_mu4_Trk_Jpsi);
	fChain->SetBranchAddress("EF_mu4_Trk_Jpsi_FS", &EF_mu4_Trk_Jpsi_FS, &b_EF_mu4_Trk_Jpsi_FS);
	fChain->SetBranchAddress("EF_mu4_Trk_Jpsi_loose", &EF_mu4_Trk_Jpsi_loose, &b_EF_mu4_Trk_Jpsi_loose);
	fChain->SetBranchAddress("EF_mu4_Trk_Upsi_FS", &EF_mu4_Trk_Upsi_FS, &b_EF_mu4_Trk_Upsi_FS);
	fChain->SetBranchAddress("EF_mu4_Trk_Upsi_loose_FS", &EF_mu4_Trk_Upsi_loose_FS, &b_EF_mu4_Trk_Upsi_loose_FS);
	fChain->SetBranchAddress("EF_mu4_Upsimumu_FS", &EF_mu4_Upsimumu_FS, &b_EF_mu4_Upsimumu_FS);
	fChain->SetBranchAddress("EF_mu4_Upsimumu_SiTrk_FS", &EF_mu4_Upsimumu_SiTrk_FS, &b_EF_mu4_Upsimumu_SiTrk_FS);
	fChain->SetBranchAddress("EF_mu4_comm_MSonly_cosmic", &EF_mu4_comm_MSonly_cosmic, &b_EF_mu4_comm_MSonly_cosmic);
	fChain->SetBranchAddress("EF_mu4_comm_cosmic", &EF_mu4_comm_cosmic, &b_EF_mu4_comm_cosmic);
	fChain->SetBranchAddress("EF_mu4_comm_firstempty", &EF_mu4_comm_firstempty, &b_EF_mu4_comm_firstempty);
	fChain->SetBranchAddress("EF_mu4_comm_unpaired_iso", &EF_mu4_comm_unpaired_iso, &b_EF_mu4_comm_unpaired_iso);
	fChain->SetBranchAddress("EF_mu4_cosmic", &EF_mu4_cosmic, &b_EF_mu4_cosmic);
	fChain->SetBranchAddress("EF_mu4_firstempty", &EF_mu4_firstempty, &b_EF_mu4_firstempty);
	fChain->SetBranchAddress("EF_mu4_j20", &EF_mu4_j20, &b_EF_mu4_j20);
	fChain->SetBranchAddress("EF_mu4_j20_jetNoEF", &EF_mu4_j20_jetNoEF, &b_EF_mu4_j20_jetNoEF);
	fChain->SetBranchAddress("EF_mu4_j30", &EF_mu4_j30, &b_EF_mu4_j30);
	fChain->SetBranchAddress("EF_mu4_j30_jetNoEF", &EF_mu4_j30_jetNoEF, &b_EF_mu4_j30_jetNoEF);
	fChain->SetBranchAddress("EF_mu4_mu6", &EF_mu4_mu6, &b_EF_mu4_mu6);
	fChain->SetBranchAddress("EF_mu4_muCombTag", &EF_mu4_muCombTag, &b_EF_mu4_muCombTag);
	fChain->SetBranchAddress("EF_mu4_tile", &EF_mu4_tile, &b_EF_mu4_tile);
	fChain->SetBranchAddress("EF_mu4_tile_cosmic", &EF_mu4_tile_cosmic, &b_EF_mu4_tile_cosmic);
	fChain->SetBranchAddress("EF_mu4_unpaired_iso", &EF_mu4_unpaired_iso, &b_EF_mu4_unpaired_iso);
	fChain->SetBranchAddress("EF_mu4mu6_Bmumu", &EF_mu4mu6_Bmumu, &b_EF_mu4mu6_Bmumu);
	fChain->SetBranchAddress("EF_mu4mu6_BmumuX", &EF_mu4mu6_BmumuX, &b_EF_mu4mu6_BmumuX);
	fChain->SetBranchAddress("EF_mu4mu6_DiMu", &EF_mu4mu6_DiMu, &b_EF_mu4mu6_DiMu);
	fChain->SetBranchAddress("EF_mu4mu6_Jpsimumu", &EF_mu4mu6_Jpsimumu, &b_EF_mu4mu6_Jpsimumu);
	fChain->SetBranchAddress("EF_mu4mu6_Jpsimumu_IDTrkNoCut", &EF_mu4mu6_Jpsimumu_IDTrkNoCut, &b_EF_mu4mu6_Jpsimumu_IDTrkNoCut);
	fChain->SetBranchAddress("EF_mu4mu6_Upsimumu", &EF_mu4mu6_Upsimumu, &b_EF_mu4mu6_Upsimumu);
	fChain->SetBranchAddress("EF_mu6", &EF_mu6, &b_EF_mu6);
	fChain->SetBranchAddress("EF_mu6_Bmumu", &EF_mu6_Bmumu, &b_EF_mu6_Bmumu);
	fChain->SetBranchAddress("EF_mu6_BmumuX", &EF_mu6_BmumuX, &b_EF_mu6_BmumuX);
	fChain->SetBranchAddress("EF_mu6_DiMu", &EF_mu6_DiMu, &b_EF_mu6_DiMu);
	fChain->SetBranchAddress("EF_mu6_Ecut12", &EF_mu6_Ecut12, &b_EF_mu6_Ecut12);
	fChain->SetBranchAddress("EF_mu6_Ecut123", &EF_mu6_Ecut123, &b_EF_mu6_Ecut123);
	fChain->SetBranchAddress("EF_mu6_Ecut13", &EF_mu6_Ecut13, &b_EF_mu6_Ecut13);
	fChain->SetBranchAddress("EF_mu6_Ecut2", &EF_mu6_Ecut2, &b_EF_mu6_Ecut2);
	fChain->SetBranchAddress("EF_mu6_Ecut3", &EF_mu6_Ecut3, &b_EF_mu6_Ecut3);
	fChain->SetBranchAddress("EF_mu6_IDTrkNoCut", &EF_mu6_IDTrkNoCut, &b_EF_mu6_IDTrkNoCut);
	fChain->SetBranchAddress("EF_mu6_Jpsie5e3", &EF_mu6_Jpsie5e3, &b_EF_mu6_Jpsie5e3);
	fChain->SetBranchAddress("EF_mu6_Jpsie5e3_FS", &EF_mu6_Jpsie5e3_FS, &b_EF_mu6_Jpsie5e3_FS);
	fChain->SetBranchAddress("EF_mu6_Jpsie5e3_SiTrk", &EF_mu6_Jpsie5e3_SiTrk, &b_EF_mu6_Jpsie5e3_SiTrk);
	fChain->SetBranchAddress("EF_mu6_Jpsie5e3_SiTrk_FS", &EF_mu6_Jpsie5e3_SiTrk_FS, &b_EF_mu6_Jpsie5e3_SiTrk_FS);
	fChain->SetBranchAddress("EF_mu6_Jpsimumu", &EF_mu6_Jpsimumu, &b_EF_mu6_Jpsimumu);
	fChain->SetBranchAddress("EF_mu6_MG", &EF_mu6_MG, &b_EF_mu6_MG);
	fChain->SetBranchAddress("EF_mu6_MSonly", &EF_mu6_MSonly, &b_EF_mu6_MSonly);
	fChain->SetBranchAddress("EF_mu6_MSonly_Ecut12", &EF_mu6_MSonly_Ecut12, &b_EF_mu6_MSonly_Ecut12);
	fChain->SetBranchAddress("EF_mu6_MSonly_Ecut123", &EF_mu6_MSonly_Ecut123, &b_EF_mu6_MSonly_Ecut123);
	fChain->SetBranchAddress("EF_mu6_MSonly_Ecut13", &EF_mu6_MSonly_Ecut13, &b_EF_mu6_MSonly_Ecut13);
	fChain->SetBranchAddress("EF_mu6_MSonly_Ecut2", &EF_mu6_MSonly_Ecut2, &b_EF_mu6_MSonly_Ecut2);
	fChain->SetBranchAddress("EF_mu6_MSonly_Ecut3", &EF_mu6_MSonly_Ecut3, &b_EF_mu6_MSonly_Ecut3);
	fChain->SetBranchAddress("EF_mu6_MSonly_outOfTime", &EF_mu6_MSonly_outOfTime, &b_EF_mu6_MSonly_outOfTime);
	fChain->SetBranchAddress("EF_mu6_NoAlg", &EF_mu6_NoAlg, &b_EF_mu6_NoAlg);
	fChain->SetBranchAddress("EF_mu6_SiTrk", &EF_mu6_SiTrk, &b_EF_mu6_SiTrk);
	fChain->SetBranchAddress("EF_mu6_Trk_Jpsi", &EF_mu6_Trk_Jpsi, &b_EF_mu6_Trk_Jpsi);
	fChain->SetBranchAddress("EF_mu6_Upsimumu_FS", &EF_mu6_Upsimumu_FS, &b_EF_mu6_Upsimumu_FS);
	fChain->SetBranchAddress("EF_mu6_muCombTag", &EF_mu6_muCombTag, &b_EF_mu6_muCombTag);
	
	fChain->SetBranchAddress("L1_2MU0", &L1_2MU0, &b_L1_2MU0);
	fChain->SetBranchAddress("L1_2MU0_FIRSTEMPTY", &L1_2MU0_FIRSTEMPTY, &b_L1_2MU0_FIRSTEMPTY);
	fChain->SetBranchAddress("L1_2MU0_MU6", &L1_2MU0_MU6, &b_L1_2MU0_MU6);
	fChain->SetBranchAddress("L1_2MU10", &L1_2MU10, &b_L1_2MU10);
	fChain->SetBranchAddress("L1_2MU20", &L1_2MU20, &b_L1_2MU20);
	fChain->SetBranchAddress("L1_2MU6", &L1_2MU6, &b_L1_2MU6);
	fChain->SetBranchAddress("L1_2MU6_EM5", &L1_2MU6_EM5, &b_L1_2MU6_EM5);
	
	fChain->SetBranchAddress("L1_MU0", &L1_MU0, &b_L1_MU0);
	fChain->SetBranchAddress("L1_MU0_COMM", &L1_MU0_COMM, &b_L1_MU0_COMM);
	fChain->SetBranchAddress("L1_MU0_COMM_EMPTY", &L1_MU0_COMM_EMPTY, &b_L1_MU0_COMM_EMPTY);
	fChain->SetBranchAddress("L1_MU0_COMM_FIRSTEMPTY", &L1_MU0_COMM_FIRSTEMPTY, &b_L1_MU0_COMM_FIRSTEMPTY);
	fChain->SetBranchAddress("L1_MU0_COMM_UNPAIRED_ISO", &L1_MU0_COMM_UNPAIRED_ISO, &b_L1_MU0_COMM_UNPAIRED_ISO);
	fChain->SetBranchAddress("L1_MU0_COMM_UNPAIRED_NONISO", &L1_MU0_COMM_UNPAIRED_NONISO, &b_L1_MU0_COMM_UNPAIRED_NONISO);
	fChain->SetBranchAddress("L1_MU0_EM3", &L1_MU0_EM3, &b_L1_MU0_EM3);
	fChain->SetBranchAddress("L1_MU0_EMPTY", &L1_MU0_EMPTY, &b_L1_MU0_EMPTY);
	fChain->SetBranchAddress("L1_MU0_FIRSTEMPTY", &L1_MU0_FIRSTEMPTY, &b_L1_MU0_FIRSTEMPTY);
	fChain->SetBranchAddress("L1_MU0_J10", &L1_MU0_J10, &b_L1_MU0_J10);
	fChain->SetBranchAddress("L1_MU0_J15", &L1_MU0_J15, &b_L1_MU0_J15);
	fChain->SetBranchAddress("L1_MU0_J30", &L1_MU0_J30, &b_L1_MU0_J30);
	fChain->SetBranchAddress("L1_MU0_J5", &L1_MU0_J5, &b_L1_MU0_J5);
	fChain->SetBranchAddress("L1_MU0_J55", &L1_MU0_J55, &b_L1_MU0_J55);
	fChain->SetBranchAddress("L1_MU0_MV", &L1_MU0_MV, &b_L1_MU0_MV);
	fChain->SetBranchAddress("L1_MU0_UNPAIRED_ISO", &L1_MU0_UNPAIRED_ISO, &b_L1_MU0_UNPAIRED_ISO);
	fChain->SetBranchAddress("L1_MU0_UNPAIRED_NONISO", &L1_MU0_UNPAIRED_NONISO, &b_L1_MU0_UNPAIRED_NONISO);
	fChain->SetBranchAddress("L1_MU10", &L1_MU10, &b_L1_MU10);
	fChain->SetBranchAddress("L1_MU10_FIRSTEMPTY", &L1_MU10_FIRSTEMPTY, &b_L1_MU10_FIRSTEMPTY);
	fChain->SetBranchAddress("L1_MU10_J10", &L1_MU10_J10, &b_L1_MU10_J10);
	fChain->SetBranchAddress("L1_MU15", &L1_MU15, &b_L1_MU15);
	fChain->SetBranchAddress("L1_MU20", &L1_MU20, &b_L1_MU20);
	fChain->SetBranchAddress("L1_MU6", &L1_MU6, &b_L1_MU6);
	fChain->SetBranchAddress("L1_MU6_EM3", &L1_MU6_EM3, &b_L1_MU6_EM3);
	fChain->SetBranchAddress("L1_MU6_FIRSTEMPTY", &L1_MU6_FIRSTEMPTY, &b_L1_MU6_FIRSTEMPTY);
	fChain->SetBranchAddress("L1_MU6_J5", &L1_MU6_J5, &b_L1_MU6_J5);
	
	fChain->SetBranchAddress("L2_2mu0_NoAlg", &L2_2mu0_NoAlg, &b_L2_2mu0_NoAlg);
	fChain->SetBranchAddress("L2_2mu10", &L2_2mu10, &b_L2_2mu10);
	fChain->SetBranchAddress("L2_2mu10_NoAlg", &L2_2mu10_NoAlg, &b_L2_2mu10_NoAlg);
	fChain->SetBranchAddress("L2_2mu4", &L2_2mu4, &b_L2_2mu4);
	fChain->SetBranchAddress("L2_2mu4_Bmumu", &L2_2mu4_Bmumu, &b_L2_2mu4_Bmumu);
	fChain->SetBranchAddress("L2_2mu4_Bmumux", &L2_2mu4_Bmumux, &b_L2_2mu4_Bmumux);
	fChain->SetBranchAddress("L2_2mu4_DiMu", &L2_2mu4_DiMu, &b_L2_2mu4_DiMu);
	fChain->SetBranchAddress("L2_2mu4_DiMu_SiTrk", &L2_2mu4_DiMu_SiTrk, &b_L2_2mu4_DiMu_SiTrk);
	fChain->SetBranchAddress("L2_2mu4_DiMu_noVtx", &L2_2mu4_DiMu_noVtx, &b_L2_2mu4_DiMu_noVtx);
	fChain->SetBranchAddress("L2_2mu4_DiMu_noVtx_noOS", &L2_2mu4_DiMu_noVtx_noOS, &b_L2_2mu4_DiMu_noVtx_noOS);
	fChain->SetBranchAddress("L2_2mu4_Jpsimumu", &L2_2mu4_Jpsimumu, &b_L2_2mu4_Jpsimumu);
	fChain->SetBranchAddress("L2_2mu4_Jpsimumu_IDTrkNoCut", &L2_2mu4_Jpsimumu_IDTrkNoCut, &b_L2_2mu4_Jpsimumu_IDTrkNoCut);
	fChain->SetBranchAddress("L2_2mu4_Upsimumu", &L2_2mu4_Upsimumu, &b_L2_2mu4_Upsimumu);
	fChain->SetBranchAddress("L2_2mu6", &L2_2mu6, &b_L2_2mu6);
	fChain->SetBranchAddress("L2_2mu6_Bmumu", &L2_2mu6_Bmumu, &b_L2_2mu6_Bmumu);
	fChain->SetBranchAddress("L2_2mu6_Bmumux", &L2_2mu6_Bmumux, &b_L2_2mu6_Bmumux);
	fChain->SetBranchAddress("L2_2mu6_DiMu", &L2_2mu6_DiMu, &b_L2_2mu6_DiMu);
	fChain->SetBranchAddress("L2_2mu6_Jpsimumu", &L2_2mu6_Jpsimumu, &b_L2_2mu6_Jpsimumu);
	fChain->SetBranchAddress("L2_2mu6_MG", &L2_2mu6_MG, &b_L2_2mu6_MG);
	fChain->SetBranchAddress("L2_2mu6_NoAlg", &L2_2mu6_NoAlg, &b_L2_2mu6_NoAlg);
	fChain->SetBranchAddress("L2_2mu6_Upsimumu", &L2_2mu6_Upsimumu, &b_L2_2mu6_Upsimumu);
	fChain->SetBranchAddress("L2_2mu6_g10_loose", &L2_2mu6_g10_loose, &b_L2_2mu6_g10_loose);
	
	fChain->SetBranchAddress("L2_mu0_NoAlg", &L2_mu0_NoAlg, &b_L2_mu0_NoAlg);
	fChain->SetBranchAddress("L2_mu0_comm_NoAlg", &L2_mu0_comm_NoAlg, &b_L2_mu0_comm_NoAlg);
	fChain->SetBranchAddress("L2_mu0_comm_empty_NoAlg", &L2_mu0_comm_empty_NoAlg, &b_L2_mu0_comm_empty_NoAlg);
	fChain->SetBranchAddress("L2_mu0_comm_firstempty_NoAlg", &L2_mu0_comm_firstempty_NoAlg, &b_L2_mu0_comm_firstempty_NoAlg);
	fChain->SetBranchAddress("L2_mu0_comm_unpaired_iso_NoAlg", &L2_mu0_comm_unpaired_iso_NoAlg, &b_L2_mu0_comm_unpaired_iso_NoAlg);
	fChain->SetBranchAddress("L2_mu0_comm_unpaired_noniso_NoAlg", &L2_mu0_comm_unpaired_noniso_NoAlg, &b_L2_mu0_comm_unpaired_noniso_NoAlg);
	fChain->SetBranchAddress("L2_mu0_empty_NoAlg", &L2_mu0_empty_NoAlg, &b_L2_mu0_empty_NoAlg);
	fChain->SetBranchAddress("L2_mu0_firstempty_NoAlg", &L2_mu0_firstempty_NoAlg, &b_L2_mu0_firstempty_NoAlg);
	fChain->SetBranchAddress("L2_mu0_missingRoi", &L2_mu0_missingRoi, &b_L2_mu0_missingRoi);
	fChain->SetBranchAddress("L2_mu0_outOfTime1", &L2_mu0_outOfTime1, &b_L2_mu0_outOfTime1);
	fChain->SetBranchAddress("L2_mu0_outOfTime2", &L2_mu0_outOfTime2, &b_L2_mu0_outOfTime2);
	fChain->SetBranchAddress("L2_mu0_rpcOnly", &L2_mu0_rpcOnly, &b_L2_mu0_rpcOnly);
	fChain->SetBranchAddress("L2_mu0_unpaired_iso_NoAlg", &L2_mu0_unpaired_iso_NoAlg, &b_L2_mu0_unpaired_iso_NoAlg);
	fChain->SetBranchAddress("L2_mu0_unpaired_noniso_NoAlg", &L2_mu0_unpaired_noniso_NoAlg, &b_L2_mu0_unpaired_noniso_NoAlg);
	fChain->SetBranchAddress("L2_mu10", &L2_mu10, &b_L2_mu10);
	fChain->SetBranchAddress("L2_mu10_Ecut12", &L2_mu10_Ecut12, &b_L2_mu10_Ecut12);
	fChain->SetBranchAddress("L2_mu10_Ecut123", &L2_mu10_Ecut123, &b_L2_mu10_Ecut123);
	fChain->SetBranchAddress("L2_mu10_Ecut13", &L2_mu10_Ecut13, &b_L2_mu10_Ecut13);
	fChain->SetBranchAddress("L2_mu10_IDTrkNoCut", &L2_mu10_IDTrkNoCut, &b_L2_mu10_IDTrkNoCut);
	fChain->SetBranchAddress("L2_mu10_MG", &L2_mu10_MG, &b_L2_mu10_MG);
	fChain->SetBranchAddress("L2_mu10_MSonly", &L2_mu10_MSonly, &b_L2_mu10_MSonly);
	fChain->SetBranchAddress("L2_mu10_MSonly_Ecut12", &L2_mu10_MSonly_Ecut12, &b_L2_mu10_MSonly_Ecut12);
	fChain->SetBranchAddress("L2_mu10_MSonly_Ecut123", &L2_mu10_MSonly_Ecut123, &b_L2_mu10_MSonly_Ecut123);
	fChain->SetBranchAddress("L2_mu10_MSonly_Ecut13", &L2_mu10_MSonly_Ecut13, &b_L2_mu10_MSonly_Ecut13);
	fChain->SetBranchAddress("L2_mu10_MSonly_tight", &L2_mu10_MSonly_tight, &b_L2_mu10_MSonly_tight);
	fChain->SetBranchAddress("L2_mu10_NoAlg", &L2_mu10_NoAlg, &b_L2_mu10_NoAlg);
	fChain->SetBranchAddress("L2_mu10_SiTrk", &L2_mu10_SiTrk, &b_L2_mu10_SiTrk);
	fChain->SetBranchAddress("L2_mu10_j30", &L2_mu10_j30, &b_L2_mu10_j30);
	fChain->SetBranchAddress("L2_mu10_tight", &L2_mu10_tight, &b_L2_mu10_tight);
	fChain->SetBranchAddress("L2_mu10i_loose", &L2_mu10i_loose, &b_L2_mu10i_loose);
	fChain->SetBranchAddress("L2_mu13", &L2_mu13, &b_L2_mu13);
	fChain->SetBranchAddress("L2_mu13_MG", &L2_mu13_MG, &b_L2_mu13_MG);
	fChain->SetBranchAddress("L2_mu13_MG_tight", &L2_mu13_MG_tight, &b_L2_mu13_MG_tight);
	fChain->SetBranchAddress("L2_mu13_tight", &L2_mu13_tight, &b_L2_mu13_tight);
	fChain->SetBranchAddress("L2_mu15", &L2_mu15, &b_L2_mu15);
	fChain->SetBranchAddress("L2_mu15_MG", &L2_mu15_MG, &b_L2_mu15_MG);
	fChain->SetBranchAddress("L2_mu15_NoAlg", &L2_mu15_NoAlg, &b_L2_mu15_NoAlg);
	fChain->SetBranchAddress("L2_mu20", &L2_mu20, &b_L2_mu20);
	fChain->SetBranchAddress("L2_mu20_MSonly", &L2_mu20_MSonly, &b_L2_mu20_MSonly);
	fChain->SetBranchAddress("L2_mu20_NoAlg", &L2_mu20_NoAlg, &b_L2_mu20_NoAlg);
	fChain->SetBranchAddress("L2_mu20_passHLT", &L2_mu20_passHLT, &b_L2_mu20_passHLT);
	fChain->SetBranchAddress("L2_mu20_slow", &L2_mu20_slow, &b_L2_mu20_slow);
	fChain->SetBranchAddress("L2_mu30_MSonly", &L2_mu30_MSonly, &b_L2_mu30_MSonly);
	fChain->SetBranchAddress("L2_mu4", &L2_mu4, &b_L2_mu4);
	fChain->SetBranchAddress("L2_mu40_MSonly", &L2_mu40_MSonly, &b_L2_mu40_MSonly);
	fChain->SetBranchAddress("L2_mu4_Bmumu", &L2_mu4_Bmumu, &b_L2_mu4_Bmumu);
	fChain->SetBranchAddress("L2_mu4_BmumuX", &L2_mu4_BmumuX, &b_L2_mu4_BmumuX);
	fChain->SetBranchAddress("L2_mu4_DiMu", &L2_mu4_DiMu, &b_L2_mu4_DiMu);
	fChain->SetBranchAddress("L2_mu4_DiMu_FS", &L2_mu4_DiMu_FS, &b_L2_mu4_DiMu_FS);
	fChain->SetBranchAddress("L2_mu4_DiMu_FS_noOS", &L2_mu4_DiMu_FS_noOS, &b_L2_mu4_DiMu_FS_noOS);
	fChain->SetBranchAddress("L2_mu4_DiMu_MG", &L2_mu4_DiMu_MG, &b_L2_mu4_DiMu_MG);
	fChain->SetBranchAddress("L2_mu4_DiMu_MG_FS", &L2_mu4_DiMu_MG_FS, &b_L2_mu4_DiMu_MG_FS);
	fChain->SetBranchAddress("L2_mu4_DiMu_SiTrk", &L2_mu4_DiMu_SiTrk, &b_L2_mu4_DiMu_SiTrk);
	fChain->SetBranchAddress("L2_mu4_DiMu_SiTrk_FS", &L2_mu4_DiMu_SiTrk_FS, &b_L2_mu4_DiMu_SiTrk_FS);
	fChain->SetBranchAddress("L2_mu4_DiMu_noOS", &L2_mu4_DiMu_noOS, &b_L2_mu4_DiMu_noOS);
	fChain->SetBranchAddress("L2_mu4_IDTrkNoCut", &L2_mu4_IDTrkNoCut, &b_L2_mu4_IDTrkNoCut);
	fChain->SetBranchAddress("L2_mu4_Jpsie5e3", &L2_mu4_Jpsie5e3, &b_L2_mu4_Jpsie5e3);
	fChain->SetBranchAddress("L2_mu4_Jpsie5e3_FS", &L2_mu4_Jpsie5e3_FS, &b_L2_mu4_Jpsie5e3_FS);
	fChain->SetBranchAddress("L2_mu4_Jpsie5e3_SiTrk", &L2_mu4_Jpsie5e3_SiTrk, &b_L2_mu4_Jpsie5e3_SiTrk);
	fChain->SetBranchAddress("L2_mu4_Jpsie5e3_SiTrk_FS", &L2_mu4_Jpsie5e3_SiTrk_FS, &b_L2_mu4_Jpsie5e3_SiTrk_FS);
	fChain->SetBranchAddress("L2_mu4_Jpsimumu", &L2_mu4_Jpsimumu, &b_L2_mu4_Jpsimumu);
	fChain->SetBranchAddress("L2_mu4_Jpsimumu_FS", &L2_mu4_Jpsimumu_FS, &b_L2_mu4_Jpsimumu_FS);
	fChain->SetBranchAddress("L2_mu4_Jpsimumu_SiTrk_FS", &L2_mu4_Jpsimumu_SiTrk_FS, &b_L2_mu4_Jpsimumu_SiTrk_FS);
	fChain->SetBranchAddress("L2_mu4_L1J10_matched", &L2_mu4_L1J10_matched, &b_L2_mu4_L1J10_matched);
	fChain->SetBranchAddress("L2_mu4_L1J15_matched", &L2_mu4_L1J15_matched, &b_L2_mu4_L1J15_matched);
	fChain->SetBranchAddress("L2_mu4_L1J30_matched", &L2_mu4_L1J30_matched, &b_L2_mu4_L1J30_matched);
	fChain->SetBranchAddress("L2_mu4_L1J55_matched", &L2_mu4_L1J55_matched, &b_L2_mu4_L1J55_matched);
	fChain->SetBranchAddress("L2_mu4_L1J5_matched", &L2_mu4_L1J5_matched, &b_L2_mu4_L1J5_matched);
	fChain->SetBranchAddress("L2_mu4_L2MSonly_EFFS_passL2", &L2_mu4_L2MSonly_EFFS_passL2, &b_L2_mu4_L2MSonly_EFFS_passL2);
	fChain->SetBranchAddress("L2_mu4_MG", &L2_mu4_MG, &b_L2_mu4_MG);
	fChain->SetBranchAddress("L2_mu4_MSonly", &L2_mu4_MSonly, &b_L2_mu4_MSonly);
	fChain->SetBranchAddress("L2_mu4_MSonly_EFFS_passL2", &L2_mu4_MSonly_EFFS_passL2, &b_L2_mu4_MSonly_EFFS_passL2);
	fChain->SetBranchAddress("L2_mu4_MSonly_MB2_noL2_EFFS", &L2_mu4_MSonly_MB2_noL2_EFFS, &b_L2_mu4_MSonly_MB2_noL2_EFFS);
	fChain->SetBranchAddress("L2_mu4_MSonly_cosmic", &L2_mu4_MSonly_cosmic, &b_L2_mu4_MSonly_cosmic);
	fChain->SetBranchAddress("L2_mu4_MSonly_outOfTime", &L2_mu4_MSonly_outOfTime, &b_L2_mu4_MSonly_outOfTime);
	fChain->SetBranchAddress("L2_mu4_MV", &L2_mu4_MV, &b_L2_mu4_MV);
	fChain->SetBranchAddress("L2_mu4_SiTrk", &L2_mu4_SiTrk, &b_L2_mu4_SiTrk);
	fChain->SetBranchAddress("L2_mu4_Trk_Jpsi", &L2_mu4_Trk_Jpsi, &b_L2_mu4_Trk_Jpsi);
	fChain->SetBranchAddress("L2_mu4_Trk_Jpsi_FS", &L2_mu4_Trk_Jpsi_FS, &b_L2_mu4_Trk_Jpsi_FS);
	fChain->SetBranchAddress("L2_mu4_Trk_Jpsi_loose", &L2_mu4_Trk_Jpsi_loose, &b_L2_mu4_Trk_Jpsi_loose);
	fChain->SetBranchAddress("L2_mu4_Trk_Upsi_FS", &L2_mu4_Trk_Upsi_FS, &b_L2_mu4_Trk_Upsi_FS);
	fChain->SetBranchAddress("L2_mu4_Trk_Upsi_loose_FS", &L2_mu4_Trk_Upsi_loose_FS, &b_L2_mu4_Trk_Upsi_loose_FS);
	fChain->SetBranchAddress("L2_mu4_Upsimumu_FS", &L2_mu4_Upsimumu_FS, &b_L2_mu4_Upsimumu_FS);
	fChain->SetBranchAddress("L2_mu4_Upsimumu_SiTrk_FS", &L2_mu4_Upsimumu_SiTrk_FS, &b_L2_mu4_Upsimumu_SiTrk_FS);
	fChain->SetBranchAddress("L2_mu4_comm_MSonly_cosmic", &L2_mu4_comm_MSonly_cosmic, &b_L2_mu4_comm_MSonly_cosmic);
	fChain->SetBranchAddress("L2_mu4_comm_cosmic", &L2_mu4_comm_cosmic, &b_L2_mu4_comm_cosmic);
	fChain->SetBranchAddress("L2_mu4_comm_firstempty", &L2_mu4_comm_firstempty, &b_L2_mu4_comm_firstempty);
	fChain->SetBranchAddress("L2_mu4_comm_unpaired_iso", &L2_mu4_comm_unpaired_iso, &b_L2_mu4_comm_unpaired_iso);
	fChain->SetBranchAddress("L2_mu4_cosmic", &L2_mu4_cosmic, &b_L2_mu4_cosmic);
	fChain->SetBranchAddress("L2_mu4_firstempty", &L2_mu4_firstempty, &b_L2_mu4_firstempty);
	fChain->SetBranchAddress("L2_mu4_j20", &L2_mu4_j20, &b_L2_mu4_j20);
	fChain->SetBranchAddress("L2_mu4_j20_jetNoEF", &L2_mu4_j20_jetNoEF, &b_L2_mu4_j20_jetNoEF);
	fChain->SetBranchAddress("L2_mu4_j25", &L2_mu4_j25, &b_L2_mu4_j25);
	fChain->SetBranchAddress("L2_mu4_mu6", &L2_mu4_mu6, &b_L2_mu4_mu6);
	fChain->SetBranchAddress("L2_mu4_muCombTag", &L2_mu4_muCombTag, &b_L2_mu4_muCombTag);
	fChain->SetBranchAddress("L2_mu4_tile", &L2_mu4_tile, &b_L2_mu4_tile);
	fChain->SetBranchAddress("L2_mu4_tile_cosmic", &L2_mu4_tile_cosmic, &b_L2_mu4_tile_cosmic);
	fChain->SetBranchAddress("L2_mu4_unpaired_iso", &L2_mu4_unpaired_iso, &b_L2_mu4_unpaired_iso);
	fChain->SetBranchAddress("L2_mu4mu6_Bmumu", &L2_mu4mu6_Bmumu, &b_L2_mu4mu6_Bmumu);
	fChain->SetBranchAddress("L2_mu4mu6_BmumuX", &L2_mu4mu6_BmumuX, &b_L2_mu4mu6_BmumuX);
	fChain->SetBranchAddress("L2_mu4mu6_DiMu", &L2_mu4mu6_DiMu, &b_L2_mu4mu6_DiMu);
	fChain->SetBranchAddress("L2_mu4mu6_Jpsimumu", &L2_mu4mu6_Jpsimumu, &b_L2_mu4mu6_Jpsimumu);
	fChain->SetBranchAddress("L2_mu4mu6_Jpsimumu_IDTrkNoCut", &L2_mu4mu6_Jpsimumu_IDTrkNoCut, &b_L2_mu4mu6_Jpsimumu_IDTrkNoCut);
	fChain->SetBranchAddress("L2_mu4mu6_Upsimumu", &L2_mu4mu6_Upsimumu, &b_L2_mu4mu6_Upsimumu);
	fChain->SetBranchAddress("L2_mu6", &L2_mu6, &b_L2_mu6);
	fChain->SetBranchAddress("L2_mu6_Bmumu", &L2_mu6_Bmumu, &b_L2_mu6_Bmumu);
	fChain->SetBranchAddress("L2_mu6_BmumuX", &L2_mu6_BmumuX, &b_L2_mu6_BmumuX);
	fChain->SetBranchAddress("L2_mu6_DiMu", &L2_mu6_DiMu, &b_L2_mu6_DiMu);
	fChain->SetBranchAddress("L2_mu6_Ecut12", &L2_mu6_Ecut12, &b_L2_mu6_Ecut12);
	fChain->SetBranchAddress("L2_mu6_Ecut123", &L2_mu6_Ecut123, &b_L2_mu6_Ecut123);
	fChain->SetBranchAddress("L2_mu6_Ecut13", &L2_mu6_Ecut13, &b_L2_mu6_Ecut13);
	fChain->SetBranchAddress("L2_mu6_Ecut2", &L2_mu6_Ecut2, &b_L2_mu6_Ecut2);
	fChain->SetBranchAddress("L2_mu6_Ecut3", &L2_mu6_Ecut3, &b_L2_mu6_Ecut3);
	fChain->SetBranchAddress("L2_mu6_IDTrkNoCut", &L2_mu6_IDTrkNoCut, &b_L2_mu6_IDTrkNoCut);
	fChain->SetBranchAddress("L2_mu6_Jpsie5e3", &L2_mu6_Jpsie5e3, &b_L2_mu6_Jpsie5e3);
	fChain->SetBranchAddress("L2_mu6_Jpsie5e3_FS", &L2_mu6_Jpsie5e3_FS, &b_L2_mu6_Jpsie5e3_FS);
	fChain->SetBranchAddress("L2_mu6_Jpsie5e3_SiTrk", &L2_mu6_Jpsie5e3_SiTrk, &b_L2_mu6_Jpsie5e3_SiTrk);
	fChain->SetBranchAddress("L2_mu6_Jpsie5e3_SiTrk_FS", &L2_mu6_Jpsie5e3_SiTrk_FS, &b_L2_mu6_Jpsie5e3_SiTrk_FS);
	fChain->SetBranchAddress("L2_mu6_Jpsimumu", &L2_mu6_Jpsimumu, &b_L2_mu6_Jpsimumu);
	fChain->SetBranchAddress("L2_mu6_MG", &L2_mu6_MG, &b_L2_mu6_MG);
	fChain->SetBranchAddress("L2_mu6_MSonly", &L2_mu6_MSonly, &b_L2_mu6_MSonly);
	fChain->SetBranchAddress("L2_mu6_MSonly_Ecut12", &L2_mu6_MSonly_Ecut12, &b_L2_mu6_MSonly_Ecut12);
	fChain->SetBranchAddress("L2_mu6_MSonly_Ecut123", &L2_mu6_MSonly_Ecut123, &b_L2_mu6_MSonly_Ecut123);
	fChain->SetBranchAddress("L2_mu6_MSonly_Ecut13", &L2_mu6_MSonly_Ecut13, &b_L2_mu6_MSonly_Ecut13);
	fChain->SetBranchAddress("L2_mu6_MSonly_Ecut2", &L2_mu6_MSonly_Ecut2, &b_L2_mu6_MSonly_Ecut2);
	fChain->SetBranchAddress("L2_mu6_MSonly_Ecut3", &L2_mu6_MSonly_Ecut3, &b_L2_mu6_MSonly_Ecut3);
	fChain->SetBranchAddress("L2_mu6_MSonly_outOfTime", &L2_mu6_MSonly_outOfTime, &b_L2_mu6_MSonly_outOfTime);
	fChain->SetBranchAddress("L2_mu6_NoAlg", &L2_mu6_NoAlg, &b_L2_mu6_NoAlg);
	fChain->SetBranchAddress("L2_mu6_SiTrk", &L2_mu6_SiTrk, &b_L2_mu6_SiTrk);
	fChain->SetBranchAddress("L2_mu6_Trk_Jpsi", &L2_mu6_Trk_Jpsi, &b_L2_mu6_Trk_Jpsi);
	fChain->SetBranchAddress("L2_mu6_Upsimumu_FS", &L2_mu6_Upsimumu_FS, &b_L2_mu6_Upsimumu_FS);
	fChain->SetBranchAddress("L2_mu6_muCombTag", &L2_mu6_muCombTag, &b_L2_mu6_muCombTag);
	
	fChain->SetBranchAddress("mu_muid_n", &mu_muid_n, &b_mu_muid_n);
	fChain->SetBranchAddress("mu_muid_E", &mu_muid_E, &b_mu_muid_E);
	fChain->SetBranchAddress("mu_muid_pt", &mu_muid_pt, &b_mu_muid_pt);
	fChain->SetBranchAddress("mu_muid_m", &mu_muid_m, &b_mu_muid_m);
	fChain->SetBranchAddress("mu_muid_eta", &mu_muid_eta, &b_mu_muid_eta);
	fChain->SetBranchAddress("mu_muid_phi", &mu_muid_phi, &b_mu_muid_phi);
	fChain->SetBranchAddress("mu_muid_px", &mu_muid_px, &b_mu_muid_px);
	fChain->SetBranchAddress("mu_muid_py", &mu_muid_py, &b_mu_muid_py);
	fChain->SetBranchAddress("mu_muid_pz", &mu_muid_pz, &b_mu_muid_pz);
	fChain->SetBranchAddress("mu_muid_charge", &mu_muid_charge, &b_mu_muid_charge);
	fChain->SetBranchAddress("mu_muid_allauthor", &mu_muid_allauthor, &b_mu_muid_allauthor);
	fChain->SetBranchAddress("mu_muid_author", &mu_muid_author, &b_mu_muid_author);
	fChain->SetBranchAddress("mu_muid_beta", &mu_muid_beta, &b_mu_muid_beta);
	fChain->SetBranchAddress("mu_muid_isMuonLikelihood", &mu_muid_isMuonLikelihood, &b_mu_muid_isMuonLikelihood);
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
	fChain->SetBranchAddress("mu_muid_etCore", &mu_muid_etCore, &b_mu_muid_etCore);
	fChain->SetBranchAddress("mu_muid_energyLossType", &mu_muid_energyLossType, &b_mu_muid_energyLossType);
	fChain->SetBranchAddress("mu_muid_caloMuonIdTag", &mu_muid_caloMuonIdTag, &b_mu_muid_caloMuonIdTag);
	fChain->SetBranchAddress("mu_muid_caloLRLikelihood", &mu_muid_caloLRLikelihood, &b_mu_muid_caloLRLikelihood);
	fChain->SetBranchAddress("mu_muid_bestMatch", &mu_muid_bestMatch, &b_mu_muid_bestMatch);
	fChain->SetBranchAddress("mu_muid_isStandAloneMuon", &mu_muid_isStandAloneMuon, &b_mu_muid_isStandAloneMuon);
	fChain->SetBranchAddress("mu_muid_isCombinedMuon", &mu_muid_isCombinedMuon, &b_mu_muid_isCombinedMuon);
	fChain->SetBranchAddress("mu_muid_isLowPtReconstructedMuon", &mu_muid_isLowPtReconstructedMuon, &b_mu_muid_isLowPtReconstructedMuon);
	fChain->SetBranchAddress("mu_muid_loose", &mu_muid_loose, &b_mu_muid_loose);
	fChain->SetBranchAddress("mu_muid_medium", &mu_muid_medium, &b_mu_muid_medium);
	fChain->SetBranchAddress("mu_muid_tight", &mu_muid_tight, &b_mu_muid_tight);
	fChain->SetBranchAddress("mu_muid_d0_exPV", &mu_muid_d0_exPV, &b_mu_muid_d0_exPV);
	fChain->SetBranchAddress("mu_muid_z0_exPV", &mu_muid_z0_exPV, &b_mu_muid_z0_exPV);
	fChain->SetBranchAddress("mu_muid_phi_exPV", &mu_muid_phi_exPV, &b_mu_muid_phi_exPV);
	fChain->SetBranchAddress("mu_muid_theta_exPV", &mu_muid_theta_exPV, &b_mu_muid_theta_exPV);
	fChain->SetBranchAddress("mu_muid_qoverp_exPV", &mu_muid_qoverp_exPV, &b_mu_muid_qoverp_exPV);
	fChain->SetBranchAddress("mu_muid_cb_d0_exPV", &mu_muid_cb_d0_exPV, &b_mu_muid_cb_d0_exPV);
	fChain->SetBranchAddress("mu_muid_cb_z0_exPV", &mu_muid_cb_z0_exPV, &b_mu_muid_cb_z0_exPV);
	fChain->SetBranchAddress("mu_muid_cb_phi_exPV", &mu_muid_cb_phi_exPV, &b_mu_muid_cb_phi_exPV);
	fChain->SetBranchAddress("mu_muid_cb_theta_exPV", &mu_muid_cb_theta_exPV, &b_mu_muid_cb_theta_exPV);
	fChain->SetBranchAddress("mu_muid_cb_qoverp_exPV", &mu_muid_cb_qoverp_exPV, &b_mu_muid_cb_qoverp_exPV);
	fChain->SetBranchAddress("mu_muid_id_d0_exPV", &mu_muid_id_d0_exPV, &b_mu_muid_id_d0_exPV);
	fChain->SetBranchAddress("mu_muid_id_z0_exPV", &mu_muid_id_z0_exPV, &b_mu_muid_id_z0_exPV);
	fChain->SetBranchAddress("mu_muid_id_phi_exPV", &mu_muid_id_phi_exPV, &b_mu_muid_id_phi_exPV);
	fChain->SetBranchAddress("mu_muid_id_theta_exPV", &mu_muid_id_theta_exPV, &b_mu_muid_id_theta_exPV);
	fChain->SetBranchAddress("mu_muid_id_qoverp_exPV", &mu_muid_id_qoverp_exPV, &b_mu_muid_id_qoverp_exPV);
	fChain->SetBranchAddress("mu_muid_me_d0_exPV", &mu_muid_me_d0_exPV, &b_mu_muid_me_d0_exPV);
	fChain->SetBranchAddress("mu_muid_me_z0_exPV", &mu_muid_me_z0_exPV, &b_mu_muid_me_z0_exPV);
	fChain->SetBranchAddress("mu_muid_me_phi_exPV", &mu_muid_me_phi_exPV, &b_mu_muid_me_phi_exPV);
	fChain->SetBranchAddress("mu_muid_me_theta_exPV", &mu_muid_me_theta_exPV, &b_mu_muid_me_theta_exPV);
	fChain->SetBranchAddress("mu_muid_me_qoverp_exPV", &mu_muid_me_qoverp_exPV, &b_mu_muid_me_qoverp_exPV);
	fChain->SetBranchAddress("mu_muid_ie_d0_exPV", &mu_muid_ie_d0_exPV, &b_mu_muid_ie_d0_exPV);
	fChain->SetBranchAddress("mu_muid_ie_z0_exPV", &mu_muid_ie_z0_exPV, &b_mu_muid_ie_z0_exPV);
	fChain->SetBranchAddress("mu_muid_ie_phi_exPV", &mu_muid_ie_phi_exPV, &b_mu_muid_ie_phi_exPV);
	fChain->SetBranchAddress("mu_muid_ie_theta_exPV", &mu_muid_ie_theta_exPV, &b_mu_muid_ie_theta_exPV);
	fChain->SetBranchAddress("mu_muid_ie_qoverp_exPV", &mu_muid_ie_qoverp_exPV, &b_mu_muid_ie_qoverp_exPV);
	fChain->SetBranchAddress("mu_muid_SpaceTime_detID", &mu_muid_SpaceTime_detID, &b_mu_muid_SpaceTime_detID);
	fChain->SetBranchAddress("mu_muid_SpaceTime_t", &mu_muid_SpaceTime_t, &b_mu_muid_SpaceTime_t);
	fChain->SetBranchAddress("mu_muid_SpaceTime_tError", &mu_muid_SpaceTime_tError, &b_mu_muid_SpaceTime_tError);
	fChain->SetBranchAddress("mu_muid_SpaceTime_weight", &mu_muid_SpaceTime_weight, &b_mu_muid_SpaceTime_weight);
	fChain->SetBranchAddress("mu_muid_SpaceTime_x", &mu_muid_SpaceTime_x, &b_mu_muid_SpaceTime_x);
	fChain->SetBranchAddress("mu_muid_SpaceTime_y", &mu_muid_SpaceTime_y, &b_mu_muid_SpaceTime_y);
	fChain->SetBranchAddress("mu_muid_SpaceTime_z", &mu_muid_SpaceTime_z, &b_mu_muid_SpaceTime_z);
	fChain->SetBranchAddress("mu_muid_SpaceTime_t_Tile", &mu_muid_SpaceTime_t_Tile, &b_mu_muid_SpaceTime_t_Tile);
	fChain->SetBranchAddress("mu_muid_SpaceTime_tError_Tile", &mu_muid_SpaceTime_tError_Tile, &b_mu_muid_SpaceTime_tError_Tile);
	fChain->SetBranchAddress("mu_muid_SpaceTime_weight_Tile", &mu_muid_SpaceTime_weight_Tile, &b_mu_muid_SpaceTime_weight_Tile);
	fChain->SetBranchAddress("mu_muid_SpaceTime_x_Tile", &mu_muid_SpaceTime_x_Tile, &b_mu_muid_SpaceTime_x_Tile);
	fChain->SetBranchAddress("mu_muid_SpaceTime_y_Tile", &mu_muid_SpaceTime_y_Tile, &b_mu_muid_SpaceTime_y_Tile);
	fChain->SetBranchAddress("mu_muid_SpaceTime_z_Tile", &mu_muid_SpaceTime_z_Tile, &b_mu_muid_SpaceTime_z_Tile);
	fChain->SetBranchAddress("mu_muid_SpaceTime_t_TRT", &mu_muid_SpaceTime_t_TRT, &b_mu_muid_SpaceTime_t_TRT);
	fChain->SetBranchAddress("mu_muid_SpaceTime_tError_TRT", &mu_muid_SpaceTime_tError_TRT, &b_mu_muid_SpaceTime_tError_TRT);
	fChain->SetBranchAddress("mu_muid_SpaceTime_weight_TRT", &mu_muid_SpaceTime_weight_TRT, &b_mu_muid_SpaceTime_weight_TRT);
	fChain->SetBranchAddress("mu_muid_SpaceTime_x_TRT", &mu_muid_SpaceTime_x_TRT, &b_mu_muid_SpaceTime_x_TRT);
	fChain->SetBranchAddress("mu_muid_SpaceTime_y_TRT", &mu_muid_SpaceTime_y_TRT, &b_mu_muid_SpaceTime_y_TRT);
	fChain->SetBranchAddress("mu_muid_SpaceTime_z_TRT", &mu_muid_SpaceTime_z_TRT, &b_mu_muid_SpaceTime_z_TRT);
	fChain->SetBranchAddress("mu_muid_SpaceTime_t_MDT", &mu_muid_SpaceTime_t_MDT, &b_mu_muid_SpaceTime_t_MDT);
	fChain->SetBranchAddress("mu_muid_SpaceTime_tError_MDT", &mu_muid_SpaceTime_tError_MDT, &b_mu_muid_SpaceTime_tError_MDT);
	fChain->SetBranchAddress("mu_muid_SpaceTime_weight_MDT", &mu_muid_SpaceTime_weight_MDT, &b_mu_muid_SpaceTime_weight_MDT);
	fChain->SetBranchAddress("mu_muid_SpaceTime_x_MDT", &mu_muid_SpaceTime_x_MDT, &b_mu_muid_SpaceTime_x_MDT);
	fChain->SetBranchAddress("mu_muid_SpaceTime_y_MDT", &mu_muid_SpaceTime_y_MDT, &b_mu_muid_SpaceTime_y_MDT);
	fChain->SetBranchAddress("mu_muid_SpaceTime_z_MDT", &mu_muid_SpaceTime_z_MDT, &b_mu_muid_SpaceTime_z_MDT);
	fChain->SetBranchAddress("mu_muid_TileCellEnergyLayer1", &mu_muid_TileCellEnergyLayer1, &b_mu_muid_TileCellEnergyLayer1);
	fChain->SetBranchAddress("mu_muid_TileTimeLayer1", &mu_muid_TileTimeLayer1, &b_mu_muid_TileTimeLayer1);
	fChain->SetBranchAddress("mu_muid_TileCellRmsNoiseLayer1", &mu_muid_TileCellRmsNoiseLayer1, &b_mu_muid_TileCellRmsNoiseLayer1);
	fChain->SetBranchAddress("mu_muid_TileCellSignLayer1", &mu_muid_TileCellSignLayer1, &b_mu_muid_TileCellSignLayer1);
	fChain->SetBranchAddress("mu_muid_TileCellEnergyLayer2", &mu_muid_TileCellEnergyLayer2, &b_mu_muid_TileCellEnergyLayer2);
	fChain->SetBranchAddress("mu_muid_TileTimeLayer2", &mu_muid_TileTimeLayer2, &b_mu_muid_TileTimeLayer2);
	fChain->SetBranchAddress("mu_muid_TileCellRmsNoiseLayer2", &mu_muid_TileCellRmsNoiseLayer2, &b_mu_muid_TileCellRmsNoiseLayer2);
	fChain->SetBranchAddress("mu_muid_TileCellSignLayer2", &mu_muid_TileCellSignLayer2, &b_mu_muid_TileCellSignLayer2);
	fChain->SetBranchAddress("mu_muid_TileCellEnergyLayer3", &mu_muid_TileCellEnergyLayer3, &b_mu_muid_TileCellEnergyLayer3);
	fChain->SetBranchAddress("mu_muid_TileTimeLayer3", &mu_muid_TileTimeLayer3, &b_mu_muid_TileTimeLayer3);
	fChain->SetBranchAddress("mu_muid_TileCellRmsNoiseLayer3", &mu_muid_TileCellRmsNoiseLayer3, &b_mu_muid_TileCellRmsNoiseLayer3);
	fChain->SetBranchAddress("mu_muid_TileCellSignLayer3", &mu_muid_TileCellSignLayer3, &b_mu_muid_TileCellSignLayer3);
	fChain->SetBranchAddress("mu_muid_MSTrkT0_1", &mu_muid_MSTrkT0_1, &b_mu_muid_MSTrkT0_1);
	fChain->SetBranchAddress("mu_muid_MSTrkT0_2", &mu_muid_MSTrkT0_2, &b_mu_muid_MSTrkT0_2);
	fChain->SetBranchAddress("mu_muid_MSTrkT0_3", &mu_muid_MSTrkT0_3, &b_mu_muid_MSTrkT0_3);
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
	fChain->SetBranchAddress("mu_muid_id_cov_d0_exPV", &mu_muid_id_cov_d0_exPV, &b_mu_muid_id_cov_d0_exPV);
	fChain->SetBranchAddress("mu_muid_id_cov_z0_exPV", &mu_muid_id_cov_z0_exPV, &b_mu_muid_id_cov_z0_exPV);
	fChain->SetBranchAddress("mu_muid_id_cov_phi_exPV", &mu_muid_id_cov_phi_exPV, &b_mu_muid_id_cov_phi_exPV);
	fChain->SetBranchAddress("mu_muid_id_cov_theta_exPV", &mu_muid_id_cov_theta_exPV, &b_mu_muid_id_cov_theta_exPV);
	fChain->SetBranchAddress("mu_muid_id_cov_qoverp_exPV", &mu_muid_id_cov_qoverp_exPV, &b_mu_muid_id_cov_qoverp_exPV);
	fChain->SetBranchAddress("mu_muid_id_cov_d0_z0_exPV", &mu_muid_id_cov_d0_z0_exPV, &b_mu_muid_id_cov_d0_z0_exPV);
	fChain->SetBranchAddress("mu_muid_id_cov_d0_phi_exPV", &mu_muid_id_cov_d0_phi_exPV, &b_mu_muid_id_cov_d0_phi_exPV);
	fChain->SetBranchAddress("mu_muid_id_cov_d0_theta_exPV", &mu_muid_id_cov_d0_theta_exPV, &b_mu_muid_id_cov_d0_theta_exPV);
	fChain->SetBranchAddress("mu_muid_id_cov_d0_qoverp_exPV", &mu_muid_id_cov_d0_qoverp_exPV, &b_mu_muid_id_cov_d0_qoverp_exPV);
	fChain->SetBranchAddress("mu_muid_id_cov_z0_phi_exPV", &mu_muid_id_cov_z0_phi_exPV, &b_mu_muid_id_cov_z0_phi_exPV);
	fChain->SetBranchAddress("mu_muid_id_cov_z0_theta_exPV", &mu_muid_id_cov_z0_theta_exPV, &b_mu_muid_id_cov_z0_theta_exPV);
	fChain->SetBranchAddress("mu_muid_id_cov_z0_qoverp_exPV", &mu_muid_id_cov_z0_qoverp_exPV, &b_mu_muid_id_cov_z0_qoverp_exPV);
	fChain->SetBranchAddress("mu_muid_id_cov_phi_theta_exPV", &mu_muid_id_cov_phi_theta_exPV, &b_mu_muid_id_cov_phi_theta_exPV);
	fChain->SetBranchAddress("mu_muid_id_cov_phi_qoverp_exPV", &mu_muid_id_cov_phi_qoverp_exPV, &b_mu_muid_id_cov_phi_qoverp_exPV);
	fChain->SetBranchAddress("mu_muid_id_cov_theta_qoverp_exPV", &mu_muid_id_cov_theta_qoverp_exPV, &b_mu_muid_id_cov_theta_qoverp_exPV);
	fChain->SetBranchAddress("mu_muid_me_cov_d0_exPV", &mu_muid_me_cov_d0_exPV, &b_mu_muid_me_cov_d0_exPV);
	fChain->SetBranchAddress("mu_muid_me_cov_z0_exPV", &mu_muid_me_cov_z0_exPV, &b_mu_muid_me_cov_z0_exPV);
	fChain->SetBranchAddress("mu_muid_me_cov_phi_exPV", &mu_muid_me_cov_phi_exPV, &b_mu_muid_me_cov_phi_exPV);
	fChain->SetBranchAddress("mu_muid_me_cov_theta_exPV", &mu_muid_me_cov_theta_exPV, &b_mu_muid_me_cov_theta_exPV);
	fChain->SetBranchAddress("mu_muid_me_cov_qoverp_exPV", &mu_muid_me_cov_qoverp_exPV, &b_mu_muid_me_cov_qoverp_exPV);
	fChain->SetBranchAddress("mu_muid_me_cov_d0_z0_exPV", &mu_muid_me_cov_d0_z0_exPV, &b_mu_muid_me_cov_d0_z0_exPV);
	fChain->SetBranchAddress("mu_muid_me_cov_d0_phi_exPV", &mu_muid_me_cov_d0_phi_exPV, &b_mu_muid_me_cov_d0_phi_exPV);
	fChain->SetBranchAddress("mu_muid_me_cov_d0_theta_exPV", &mu_muid_me_cov_d0_theta_exPV, &b_mu_muid_me_cov_d0_theta_exPV);
	fChain->SetBranchAddress("mu_muid_me_cov_d0_qoverp_exPV", &mu_muid_me_cov_d0_qoverp_exPV, &b_mu_muid_me_cov_d0_qoverp_exPV);
	fChain->SetBranchAddress("mu_muid_me_cov_z0_phi_exPV", &mu_muid_me_cov_z0_phi_exPV, &b_mu_muid_me_cov_z0_phi_exPV);
	fChain->SetBranchAddress("mu_muid_me_cov_z0_theta_exPV", &mu_muid_me_cov_z0_theta_exPV, &b_mu_muid_me_cov_z0_theta_exPV);
	fChain->SetBranchAddress("mu_muid_me_cov_z0_qoverp_exPV", &mu_muid_me_cov_z0_qoverp_exPV, &b_mu_muid_me_cov_z0_qoverp_exPV);
	fChain->SetBranchAddress("mu_muid_me_cov_phi_theta_exPV", &mu_muid_me_cov_phi_theta_exPV, &b_mu_muid_me_cov_phi_theta_exPV);
	fChain->SetBranchAddress("mu_muid_me_cov_phi_qoverp_exPV", &mu_muid_me_cov_phi_qoverp_exPV, &b_mu_muid_me_cov_phi_qoverp_exPV);
	fChain->SetBranchAddress("mu_muid_me_cov_theta_qoverp_exPV", &mu_muid_me_cov_theta_qoverp_exPV, &b_mu_muid_me_cov_theta_qoverp_exPV);
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
	fChain->SetBranchAddress("mu_muid_nOutliersOnTrack", &mu_muid_nOutliersOnTrack, &b_mu_muid_nOutliersOnTrack);
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
	fChain->SetBranchAddress("mu_muid_nGangedPixels", &mu_muid_nGangedPixels, &b_mu_muid_nGangedPixels);
	fChain->SetBranchAddress("mu_muid_nPixelDeadSensors", &mu_muid_nPixelDeadSensors, &b_mu_muid_nPixelDeadSensors);
	fChain->SetBranchAddress("mu_muid_nSCTDeadSensors", &mu_muid_nSCTDeadSensors, &b_mu_muid_nSCTDeadSensors);
	fChain->SetBranchAddress("mu_muid_nTRTDeadStraws", &mu_muid_nTRTDeadStraws, &b_mu_muid_nTRTDeadStraws);
	fChain->SetBranchAddress("mu_muid_expectBLayerHit", &mu_muid_expectBLayerHit, &b_mu_muid_expectBLayerHit);
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
	if(isMC)
	{
		fChain->SetBranchAddress("mu_muid_truth_dr", &mu_muid_truth_dr, &b_mu_muid_truth_dr);
		fChain->SetBranchAddress("mu_muid_truth_E", &mu_muid_truth_E, &b_mu_muid_truth_E);
		fChain->SetBranchAddress("mu_muid_truth_pt", &mu_muid_truth_pt, &b_mu_muid_truth_pt);
		fChain->SetBranchAddress("mu_muid_truth_eta", &mu_muid_truth_eta, &b_mu_muid_truth_eta);
		fChain->SetBranchAddress("mu_muid_truth_phi", &mu_muid_truth_phi, &b_mu_muid_truth_phi);
		fChain->SetBranchAddress("mu_muid_truth_type", &mu_muid_truth_type, &b_mu_muid_truth_type);
		fChain->SetBranchAddress("mu_muid_truth_status", &mu_muid_truth_status, &b_mu_muid_truth_status);
		fChain->SetBranchAddress("mu_muid_truth_barcode", &mu_muid_truth_barcode, &b_mu_muid_truth_barcode);
		fChain->SetBranchAddress("mu_muid_truth_mothertype", &mu_muid_truth_mothertype, &b_mu_muid_truth_mothertype);
		fChain->SetBranchAddress("mu_muid_truth_motherbarcode", &mu_muid_truth_motherbarcode, &b_mu_muid_truth_motherbarcode);
		fChain->SetBranchAddress("mu_muid_truth_matched", &mu_muid_truth_matched, &b_mu_muid_truth_matched);
	}
	fChain->SetBranchAddress("mu_muid_EFCB_dr", &mu_muid_EFCB_dr, &b_mu_muid_EFCB_dr);
	fChain->SetBranchAddress("mu_muid_EFCB_index", &mu_muid_EFCB_index, &b_mu_muid_EFCB_index);
	fChain->SetBranchAddress("mu_muid_EFMG_dr", &mu_muid_EFMG_dr, &b_mu_muid_EFMG_dr);
	fChain->SetBranchAddress("mu_muid_EFMG_index", &mu_muid_EFMG_index, &b_mu_muid_EFMG_index);
	fChain->SetBranchAddress("mu_muid_EFME_dr", &mu_muid_EFME_dr, &b_mu_muid_EFME_dr);
	fChain->SetBranchAddress("mu_muid_EFME_index", &mu_muid_EFME_index, &b_mu_muid_EFME_index);
	fChain->SetBranchAddress("mu_muid_L2CB_dr", &mu_muid_L2CB_dr, &b_mu_muid_L2CB_dr);
	fChain->SetBranchAddress("mu_muid_L2CB_index", &mu_muid_L2CB_index, &b_mu_muid_L2CB_index);
	fChain->SetBranchAddress("mu_muid_L1_dr", &mu_muid_L1_dr, &b_mu_muid_L1_dr);
	fChain->SetBranchAddress("mu_muid_L1_index", &mu_muid_L1_index, &b_mu_muid_L1_index);
	
	fChain->SetBranchAddress("mu_staco_n", &mu_staco_n, &b_mu_staco_n);
	fChain->SetBranchAddress("mu_staco_E", &mu_staco_E, &b_mu_staco_E);
	fChain->SetBranchAddress("mu_staco_pt", &mu_staco_pt, &b_mu_staco_pt);
	fChain->SetBranchAddress("mu_staco_m", &mu_staco_m, &b_mu_staco_m);
	fChain->SetBranchAddress("mu_staco_eta", &mu_staco_eta, &b_mu_staco_eta);
	fChain->SetBranchAddress("mu_staco_phi", &mu_staco_phi, &b_mu_staco_phi);
	fChain->SetBranchAddress("mu_staco_px", &mu_staco_px, &b_mu_staco_px);
	fChain->SetBranchAddress("mu_staco_py", &mu_staco_py, &b_mu_staco_py);
	fChain->SetBranchAddress("mu_staco_pz", &mu_staco_pz, &b_mu_staco_pz);
	fChain->SetBranchAddress("mu_staco_charge", &mu_staco_charge, &b_mu_staco_charge);
	fChain->SetBranchAddress("mu_staco_allauthor", &mu_staco_allauthor, &b_mu_staco_allauthor);
	fChain->SetBranchAddress("mu_staco_author", &mu_staco_author, &b_mu_staco_author);
	fChain->SetBranchAddress("mu_staco_beta", &mu_staco_beta, &b_mu_staco_beta);
	fChain->SetBranchAddress("mu_staco_isMuonLikelihood", &mu_staco_isMuonLikelihood, &b_mu_staco_isMuonLikelihood);
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
	fChain->SetBranchAddress("mu_staco_etCore", &mu_staco_etCore, &b_mu_staco_etCore);
	fChain->SetBranchAddress("mu_staco_energyLossType", &mu_staco_energyLossType, &b_mu_staco_energyLossType);
	fChain->SetBranchAddress("mu_staco_caloMuonIdTag", &mu_staco_caloMuonIdTag, &b_mu_staco_caloMuonIdTag);
	fChain->SetBranchAddress("mu_staco_caloLRLikelihood", &mu_staco_caloLRLikelihood, &b_mu_staco_caloLRLikelihood);
	fChain->SetBranchAddress("mu_staco_bestMatch", &mu_staco_bestMatch, &b_mu_staco_bestMatch);
	fChain->SetBranchAddress("mu_staco_isStandAloneMuon", &mu_staco_isStandAloneMuon, &b_mu_staco_isStandAloneMuon);
	fChain->SetBranchAddress("mu_staco_isCombinedMuon", &mu_staco_isCombinedMuon, &b_mu_staco_isCombinedMuon);
	fChain->SetBranchAddress("mu_staco_isLowPtReconstructedMuon", &mu_staco_isLowPtReconstructedMuon, &b_mu_staco_isLowPtReconstructedMuon);
	fChain->SetBranchAddress("mu_staco_loose", &mu_staco_loose, &b_mu_staco_loose);
	fChain->SetBranchAddress("mu_staco_medium", &mu_staco_medium, &b_mu_staco_medium);
	fChain->SetBranchAddress("mu_staco_tight", &mu_staco_tight, &b_mu_staco_tight);
	fChain->SetBranchAddress("mu_staco_d0_exPV", &mu_staco_d0_exPV, &b_mu_staco_d0_exPV);
	fChain->SetBranchAddress("mu_staco_z0_exPV", &mu_staco_z0_exPV, &b_mu_staco_z0_exPV);
	fChain->SetBranchAddress("mu_staco_phi_exPV", &mu_staco_phi_exPV, &b_mu_staco_phi_exPV);
	fChain->SetBranchAddress("mu_staco_theta_exPV", &mu_staco_theta_exPV, &b_mu_staco_theta_exPV);
	fChain->SetBranchAddress("mu_staco_qoverp_exPV", &mu_staco_qoverp_exPV, &b_mu_staco_qoverp_exPV);
	fChain->SetBranchAddress("mu_staco_cb_d0_exPV", &mu_staco_cb_d0_exPV, &b_mu_staco_cb_d0_exPV);
	fChain->SetBranchAddress("mu_staco_cb_z0_exPV", &mu_staco_cb_z0_exPV, &b_mu_staco_cb_z0_exPV);
	fChain->SetBranchAddress("mu_staco_cb_phi_exPV", &mu_staco_cb_phi_exPV, &b_mu_staco_cb_phi_exPV);
	fChain->SetBranchAddress("mu_staco_cb_theta_exPV", &mu_staco_cb_theta_exPV, &b_mu_staco_cb_theta_exPV);
	fChain->SetBranchAddress("mu_staco_cb_qoverp_exPV", &mu_staco_cb_qoverp_exPV, &b_mu_staco_cb_qoverp_exPV);
	fChain->SetBranchAddress("mu_staco_id_d0_exPV", &mu_staco_id_d0_exPV, &b_mu_staco_id_d0_exPV);
	fChain->SetBranchAddress("mu_staco_id_z0_exPV", &mu_staco_id_z0_exPV, &b_mu_staco_id_z0_exPV);
	fChain->SetBranchAddress("mu_staco_id_phi_exPV", &mu_staco_id_phi_exPV, &b_mu_staco_id_phi_exPV);
	fChain->SetBranchAddress("mu_staco_id_theta_exPV", &mu_staco_id_theta_exPV, &b_mu_staco_id_theta_exPV);
	fChain->SetBranchAddress("mu_staco_id_qoverp_exPV", &mu_staco_id_qoverp_exPV, &b_mu_staco_id_qoverp_exPV);
	fChain->SetBranchAddress("mu_staco_me_d0_exPV", &mu_staco_me_d0_exPV, &b_mu_staco_me_d0_exPV);
	fChain->SetBranchAddress("mu_staco_me_z0_exPV", &mu_staco_me_z0_exPV, &b_mu_staco_me_z0_exPV);
	fChain->SetBranchAddress("mu_staco_me_phi_exPV", &mu_staco_me_phi_exPV, &b_mu_staco_me_phi_exPV);
	fChain->SetBranchAddress("mu_staco_me_theta_exPV", &mu_staco_me_theta_exPV, &b_mu_staco_me_theta_exPV);
	fChain->SetBranchAddress("mu_staco_me_qoverp_exPV", &mu_staco_me_qoverp_exPV, &b_mu_staco_me_qoverp_exPV);
	fChain->SetBranchAddress("mu_staco_ie_d0_exPV", &mu_staco_ie_d0_exPV, &b_mu_staco_ie_d0_exPV);
	fChain->SetBranchAddress("mu_staco_ie_z0_exPV", &mu_staco_ie_z0_exPV, &b_mu_staco_ie_z0_exPV);
	fChain->SetBranchAddress("mu_staco_ie_phi_exPV", &mu_staco_ie_phi_exPV, &b_mu_staco_ie_phi_exPV);
	fChain->SetBranchAddress("mu_staco_ie_theta_exPV", &mu_staco_ie_theta_exPV, &b_mu_staco_ie_theta_exPV);
	fChain->SetBranchAddress("mu_staco_ie_qoverp_exPV", &mu_staco_ie_qoverp_exPV, &b_mu_staco_ie_qoverp_exPV);
	fChain->SetBranchAddress("mu_staco_SpaceTime_detID", &mu_staco_SpaceTime_detID, &b_mu_staco_SpaceTime_detID);
	fChain->SetBranchAddress("mu_staco_SpaceTime_t", &mu_staco_SpaceTime_t, &b_mu_staco_SpaceTime_t);
	fChain->SetBranchAddress("mu_staco_SpaceTime_tError", &mu_staco_SpaceTime_tError, &b_mu_staco_SpaceTime_tError);
	fChain->SetBranchAddress("mu_staco_SpaceTime_weight", &mu_staco_SpaceTime_weight, &b_mu_staco_SpaceTime_weight);
	fChain->SetBranchAddress("mu_staco_SpaceTime_x", &mu_staco_SpaceTime_x, &b_mu_staco_SpaceTime_x);
	fChain->SetBranchAddress("mu_staco_SpaceTime_y", &mu_staco_SpaceTime_y, &b_mu_staco_SpaceTime_y);
	fChain->SetBranchAddress("mu_staco_SpaceTime_z", &mu_staco_SpaceTime_z, &b_mu_staco_SpaceTime_z);
	fChain->SetBranchAddress("mu_staco_SpaceTime_t_Tile", &mu_staco_SpaceTime_t_Tile, &b_mu_staco_SpaceTime_t_Tile);
	fChain->SetBranchAddress("mu_staco_SpaceTime_tError_Tile", &mu_staco_SpaceTime_tError_Tile, &b_mu_staco_SpaceTime_tError_Tile);
	fChain->SetBranchAddress("mu_staco_SpaceTime_weight_Tile", &mu_staco_SpaceTime_weight_Tile, &b_mu_staco_SpaceTime_weight_Tile);
	fChain->SetBranchAddress("mu_staco_SpaceTime_x_Tile", &mu_staco_SpaceTime_x_Tile, &b_mu_staco_SpaceTime_x_Tile);
	fChain->SetBranchAddress("mu_staco_SpaceTime_y_Tile", &mu_staco_SpaceTime_y_Tile, &b_mu_staco_SpaceTime_y_Tile);
	fChain->SetBranchAddress("mu_staco_SpaceTime_z_Tile", &mu_staco_SpaceTime_z_Tile, &b_mu_staco_SpaceTime_z_Tile);
	fChain->SetBranchAddress("mu_staco_SpaceTime_t_TRT", &mu_staco_SpaceTime_t_TRT, &b_mu_staco_SpaceTime_t_TRT);
	fChain->SetBranchAddress("mu_staco_SpaceTime_tError_TRT", &mu_staco_SpaceTime_tError_TRT, &b_mu_staco_SpaceTime_tError_TRT);
	fChain->SetBranchAddress("mu_staco_SpaceTime_weight_TRT", &mu_staco_SpaceTime_weight_TRT, &b_mu_staco_SpaceTime_weight_TRT);
	fChain->SetBranchAddress("mu_staco_SpaceTime_x_TRT", &mu_staco_SpaceTime_x_TRT, &b_mu_staco_SpaceTime_x_TRT);
	fChain->SetBranchAddress("mu_staco_SpaceTime_y_TRT", &mu_staco_SpaceTime_y_TRT, &b_mu_staco_SpaceTime_y_TRT);
	fChain->SetBranchAddress("mu_staco_SpaceTime_z_TRT", &mu_staco_SpaceTime_z_TRT, &b_mu_staco_SpaceTime_z_TRT);
	fChain->SetBranchAddress("mu_staco_SpaceTime_t_MDT", &mu_staco_SpaceTime_t_MDT, &b_mu_staco_SpaceTime_t_MDT);
	fChain->SetBranchAddress("mu_staco_SpaceTime_tError_MDT", &mu_staco_SpaceTime_tError_MDT, &b_mu_staco_SpaceTime_tError_MDT);
	fChain->SetBranchAddress("mu_staco_SpaceTime_weight_MDT", &mu_staco_SpaceTime_weight_MDT, &b_mu_staco_SpaceTime_weight_MDT);
	fChain->SetBranchAddress("mu_staco_SpaceTime_x_MDT", &mu_staco_SpaceTime_x_MDT, &b_mu_staco_SpaceTime_x_MDT);
	fChain->SetBranchAddress("mu_staco_SpaceTime_y_MDT", &mu_staco_SpaceTime_y_MDT, &b_mu_staco_SpaceTime_y_MDT);
	fChain->SetBranchAddress("mu_staco_SpaceTime_z_MDT", &mu_staco_SpaceTime_z_MDT, &b_mu_staco_SpaceTime_z_MDT);
	fChain->SetBranchAddress("mu_staco_TileCellEnergyLayer1", &mu_staco_TileCellEnergyLayer1, &b_mu_staco_TileCellEnergyLayer1);
	fChain->SetBranchAddress("mu_staco_TileTimeLayer1", &mu_staco_TileTimeLayer1, &b_mu_staco_TileTimeLayer1);
	fChain->SetBranchAddress("mu_staco_TileCellRmsNoiseLayer1", &mu_staco_TileCellRmsNoiseLayer1, &b_mu_staco_TileCellRmsNoiseLayer1);
	fChain->SetBranchAddress("mu_staco_TileCellSignLayer1", &mu_staco_TileCellSignLayer1, &b_mu_staco_TileCellSignLayer1);
	fChain->SetBranchAddress("mu_staco_TileCellEnergyLayer2", &mu_staco_TileCellEnergyLayer2, &b_mu_staco_TileCellEnergyLayer2);
	fChain->SetBranchAddress("mu_staco_TileTimeLayer2", &mu_staco_TileTimeLayer2, &b_mu_staco_TileTimeLayer2);
	fChain->SetBranchAddress("mu_staco_TileCellRmsNoiseLayer2", &mu_staco_TileCellRmsNoiseLayer2, &b_mu_staco_TileCellRmsNoiseLayer2);
	fChain->SetBranchAddress("mu_staco_TileCellSignLayer2", &mu_staco_TileCellSignLayer2, &b_mu_staco_TileCellSignLayer2);
	fChain->SetBranchAddress("mu_staco_TileCellEnergyLayer3", &mu_staco_TileCellEnergyLayer3, &b_mu_staco_TileCellEnergyLayer3);
	fChain->SetBranchAddress("mu_staco_TileTimeLayer3", &mu_staco_TileTimeLayer3, &b_mu_staco_TileTimeLayer3);
	fChain->SetBranchAddress("mu_staco_TileCellRmsNoiseLayer3", &mu_staco_TileCellRmsNoiseLayer3, &b_mu_staco_TileCellRmsNoiseLayer3);
	fChain->SetBranchAddress("mu_staco_TileCellSignLayer3", &mu_staco_TileCellSignLayer3, &b_mu_staco_TileCellSignLayer3);
	fChain->SetBranchAddress("mu_staco_MSTrkT0_1", &mu_staco_MSTrkT0_1, &b_mu_staco_MSTrkT0_1);
	fChain->SetBranchAddress("mu_staco_MSTrkT0_2", &mu_staco_MSTrkT0_2, &b_mu_staco_MSTrkT0_2);
	fChain->SetBranchAddress("mu_staco_MSTrkT0_3", &mu_staco_MSTrkT0_3, &b_mu_staco_MSTrkT0_3);
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
	fChain->SetBranchAddress("mu_staco_id_cov_d0_exPV", &mu_staco_id_cov_d0_exPV, &b_mu_staco_id_cov_d0_exPV);
	fChain->SetBranchAddress("mu_staco_id_cov_z0_exPV", &mu_staco_id_cov_z0_exPV, &b_mu_staco_id_cov_z0_exPV);
	fChain->SetBranchAddress("mu_staco_id_cov_phi_exPV", &mu_staco_id_cov_phi_exPV, &b_mu_staco_id_cov_phi_exPV);
	fChain->SetBranchAddress("mu_staco_id_cov_theta_exPV", &mu_staco_id_cov_theta_exPV, &b_mu_staco_id_cov_theta_exPV);
	fChain->SetBranchAddress("mu_staco_id_cov_qoverp_exPV", &mu_staco_id_cov_qoverp_exPV, &b_mu_staco_id_cov_qoverp_exPV);
	fChain->SetBranchAddress("mu_staco_id_cov_d0_z0_exPV", &mu_staco_id_cov_d0_z0_exPV, &b_mu_staco_id_cov_d0_z0_exPV);
	fChain->SetBranchAddress("mu_staco_id_cov_d0_phi_exPV", &mu_staco_id_cov_d0_phi_exPV, &b_mu_staco_id_cov_d0_phi_exPV);
	fChain->SetBranchAddress("mu_staco_id_cov_d0_theta_exPV", &mu_staco_id_cov_d0_theta_exPV, &b_mu_staco_id_cov_d0_theta_exPV);
	fChain->SetBranchAddress("mu_staco_id_cov_d0_qoverp_exPV", &mu_staco_id_cov_d0_qoverp_exPV, &b_mu_staco_id_cov_d0_qoverp_exPV);
	fChain->SetBranchAddress("mu_staco_id_cov_z0_phi_exPV", &mu_staco_id_cov_z0_phi_exPV, &b_mu_staco_id_cov_z0_phi_exPV);
	fChain->SetBranchAddress("mu_staco_id_cov_z0_theta_exPV", &mu_staco_id_cov_z0_theta_exPV, &b_mu_staco_id_cov_z0_theta_exPV);
	fChain->SetBranchAddress("mu_staco_id_cov_z0_qoverp_exPV", &mu_staco_id_cov_z0_qoverp_exPV, &b_mu_staco_id_cov_z0_qoverp_exPV);
	fChain->SetBranchAddress("mu_staco_id_cov_phi_theta_exPV", &mu_staco_id_cov_phi_theta_exPV, &b_mu_staco_id_cov_phi_theta_exPV);
	fChain->SetBranchAddress("mu_staco_id_cov_phi_qoverp_exPV", &mu_staco_id_cov_phi_qoverp_exPV, &b_mu_staco_id_cov_phi_qoverp_exPV);
	fChain->SetBranchAddress("mu_staco_id_cov_theta_qoverp_exPV", &mu_staco_id_cov_theta_qoverp_exPV, &b_mu_staco_id_cov_theta_qoverp_exPV);
	fChain->SetBranchAddress("mu_staco_me_cov_d0_exPV", &mu_staco_me_cov_d0_exPV, &b_mu_staco_me_cov_d0_exPV);
	fChain->SetBranchAddress("mu_staco_me_cov_z0_exPV", &mu_staco_me_cov_z0_exPV, &b_mu_staco_me_cov_z0_exPV);
	fChain->SetBranchAddress("mu_staco_me_cov_phi_exPV", &mu_staco_me_cov_phi_exPV, &b_mu_staco_me_cov_phi_exPV);
	fChain->SetBranchAddress("mu_staco_me_cov_theta_exPV", &mu_staco_me_cov_theta_exPV, &b_mu_staco_me_cov_theta_exPV);
	fChain->SetBranchAddress("mu_staco_me_cov_qoverp_exPV", &mu_staco_me_cov_qoverp_exPV, &b_mu_staco_me_cov_qoverp_exPV);
	fChain->SetBranchAddress("mu_staco_me_cov_d0_z0_exPV", &mu_staco_me_cov_d0_z0_exPV, &b_mu_staco_me_cov_d0_z0_exPV);
	fChain->SetBranchAddress("mu_staco_me_cov_d0_phi_exPV", &mu_staco_me_cov_d0_phi_exPV, &b_mu_staco_me_cov_d0_phi_exPV);
	fChain->SetBranchAddress("mu_staco_me_cov_d0_theta_exPV", &mu_staco_me_cov_d0_theta_exPV, &b_mu_staco_me_cov_d0_theta_exPV);
	fChain->SetBranchAddress("mu_staco_me_cov_d0_qoverp_exPV", &mu_staco_me_cov_d0_qoverp_exPV, &b_mu_staco_me_cov_d0_qoverp_exPV);
	fChain->SetBranchAddress("mu_staco_me_cov_z0_phi_exPV", &mu_staco_me_cov_z0_phi_exPV, &b_mu_staco_me_cov_z0_phi_exPV);
	fChain->SetBranchAddress("mu_staco_me_cov_z0_theta_exPV", &mu_staco_me_cov_z0_theta_exPV, &b_mu_staco_me_cov_z0_theta_exPV);
	fChain->SetBranchAddress("mu_staco_me_cov_z0_qoverp_exPV", &mu_staco_me_cov_z0_qoverp_exPV, &b_mu_staco_me_cov_z0_qoverp_exPV);
	fChain->SetBranchAddress("mu_staco_me_cov_phi_theta_exPV", &mu_staco_me_cov_phi_theta_exPV, &b_mu_staco_me_cov_phi_theta_exPV);
	fChain->SetBranchAddress("mu_staco_me_cov_phi_qoverp_exPV", &mu_staco_me_cov_phi_qoverp_exPV, &b_mu_staco_me_cov_phi_qoverp_exPV);
	fChain->SetBranchAddress("mu_staco_me_cov_theta_qoverp_exPV", &mu_staco_me_cov_theta_qoverp_exPV, &b_mu_staco_me_cov_theta_qoverp_exPV);
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
	fChain->SetBranchAddress("mu_staco_nOutliersOnTrack", &mu_staco_nOutliersOnTrack, &b_mu_staco_nOutliersOnTrack);
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
	fChain->SetBranchAddress("mu_staco_nGangedPixels", &mu_staco_nGangedPixels, &b_mu_staco_nGangedPixels);
	fChain->SetBranchAddress("mu_staco_nPixelDeadSensors", &mu_staco_nPixelDeadSensors, &b_mu_staco_nPixelDeadSensors);
	fChain->SetBranchAddress("mu_staco_nSCTDeadSensors", &mu_staco_nSCTDeadSensors, &b_mu_staco_nSCTDeadSensors);
	fChain->SetBranchAddress("mu_staco_nTRTDeadStraws", &mu_staco_nTRTDeadStraws, &b_mu_staco_nTRTDeadStraws);
	fChain->SetBranchAddress("mu_staco_expectBLayerHit", &mu_staco_expectBLayerHit, &b_mu_staco_expectBLayerHit);
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
	if(isMC)
	{
		fChain->SetBranchAddress("mu_staco_truth_dr", &mu_staco_truth_dr, &b_mu_staco_truth_dr);
		fChain->SetBranchAddress("mu_staco_truth_E", &mu_staco_truth_E, &b_mu_staco_truth_E);
		fChain->SetBranchAddress("mu_staco_truth_pt", &mu_staco_truth_pt, &b_mu_staco_truth_pt);
		fChain->SetBranchAddress("mu_staco_truth_eta", &mu_staco_truth_eta, &b_mu_staco_truth_eta);
		fChain->SetBranchAddress("mu_staco_truth_phi", &mu_staco_truth_phi, &b_mu_staco_truth_phi);
		fChain->SetBranchAddress("mu_staco_truth_type", &mu_staco_truth_type, &b_mu_staco_truth_type);
		fChain->SetBranchAddress("mu_staco_truth_status", &mu_staco_truth_status, &b_mu_staco_truth_status);
		fChain->SetBranchAddress("mu_staco_truth_barcode", &mu_staco_truth_barcode, &b_mu_staco_truth_barcode);
		fChain->SetBranchAddress("mu_staco_truth_mothertype", &mu_staco_truth_mothertype, &b_mu_staco_truth_mothertype);
		fChain->SetBranchAddress("mu_staco_truth_motherbarcode", &mu_staco_truth_motherbarcode, &b_mu_staco_truth_motherbarcode);
		fChain->SetBranchAddress("mu_staco_truth_matched", &mu_staco_truth_matched, &b_mu_staco_truth_matched);
	}
	fChain->SetBranchAddress("mu_staco_EFCB_dr", &mu_staco_EFCB_dr, &b_mu_staco_EFCB_dr);
	fChain->SetBranchAddress("mu_staco_EFCB_index", &mu_staco_EFCB_index, &b_mu_staco_EFCB_index);
	fChain->SetBranchAddress("mu_staco_EFMG_dr", &mu_staco_EFMG_dr, &b_mu_staco_EFMG_dr);
	fChain->SetBranchAddress("mu_staco_EFMG_index", &mu_staco_EFMG_index, &b_mu_staco_EFMG_index);
	fChain->SetBranchAddress("mu_staco_EFME_dr", &mu_staco_EFME_dr, &b_mu_staco_EFME_dr);
	fChain->SetBranchAddress("mu_staco_EFME_index", &mu_staco_EFME_index, &b_mu_staco_EFME_index);
	fChain->SetBranchAddress("mu_staco_L2CB_dr", &mu_staco_L2CB_dr, &b_mu_staco_L2CB_dr);
	fChain->SetBranchAddress("mu_staco_L2CB_index", &mu_staco_L2CB_index, &b_mu_staco_L2CB_index);
	fChain->SetBranchAddress("mu_staco_L1_dr", &mu_staco_L1_dr, &b_mu_staco_L1_dr);
	fChain->SetBranchAddress("mu_staco_L1_index", &mu_staco_L1_index, &b_mu_staco_L1_index);
	
	fChain->SetBranchAddress("mu_calo_n", &mu_calo_n, &b_mu_calo_n);
	fChain->SetBranchAddress("mu_calo_E", &mu_calo_E, &b_mu_calo_E);
	fChain->SetBranchAddress("mu_calo_pt", &mu_calo_pt, &b_mu_calo_pt);
	fChain->SetBranchAddress("mu_calo_m", &mu_calo_m, &b_mu_calo_m);
	fChain->SetBranchAddress("mu_calo_eta", &mu_calo_eta, &b_mu_calo_eta);
	fChain->SetBranchAddress("mu_calo_phi", &mu_calo_phi, &b_mu_calo_phi);
	fChain->SetBranchAddress("mu_calo_px", &mu_calo_px, &b_mu_calo_px);
	fChain->SetBranchAddress("mu_calo_py", &mu_calo_py, &b_mu_calo_py);
	fChain->SetBranchAddress("mu_calo_pz", &mu_calo_pz, &b_mu_calo_pz);
	fChain->SetBranchAddress("mu_calo_charge", &mu_calo_charge, &b_mu_calo_charge);
	fChain->SetBranchAddress("mu_calo_allauthor", &mu_calo_allauthor, &b_mu_calo_allauthor);
	fChain->SetBranchAddress("mu_calo_hastrack", &mu_calo_hastrack, &b_mu_calo_hastrack);
	if(isMC)
	{
		fChain->SetBranchAddress("mu_calo_truth_dr", &mu_calo_truth_dr, &b_mu_calo_truth_dr);
		fChain->SetBranchAddress("mu_calo_truth_E", &mu_calo_truth_E, &b_mu_calo_truth_E);
		fChain->SetBranchAddress("mu_calo_truth_pt", &mu_calo_truth_pt, &b_mu_calo_truth_pt);
		fChain->SetBranchAddress("mu_calo_truth_eta", &mu_calo_truth_eta, &b_mu_calo_truth_eta);
		fChain->SetBranchAddress("mu_calo_truth_phi", &mu_calo_truth_phi, &b_mu_calo_truth_phi);
		fChain->SetBranchAddress("mu_calo_truth_type", &mu_calo_truth_type, &b_mu_calo_truth_type);
		fChain->SetBranchAddress("mu_calo_truth_status", &mu_calo_truth_status, &b_mu_calo_truth_status);
		fChain->SetBranchAddress("mu_calo_truth_barcode", &mu_calo_truth_barcode, &b_mu_calo_truth_barcode);
		fChain->SetBranchAddress("mu_calo_truth_mothertype", &mu_calo_truth_mothertype, &b_mu_calo_truth_mothertype);
		fChain->SetBranchAddress("mu_calo_truth_motherbarcode", &mu_calo_truth_motherbarcode, &b_mu_calo_truth_motherbarcode);
		fChain->SetBranchAddress("mu_calo_truth_matched", &mu_calo_truth_matched, &b_mu_calo_truth_matched);
	}
	
	fChain->SetBranchAddress("MET_RefFinal_phi", &MET_RefFinal_phi, &b_MET_RefFinal_phi);
	fChain->SetBranchAddress("MET_RefFinal_et", &MET_RefFinal_et, &b_MET_RefFinal_et);
	fChain->SetBranchAddress("MET_RefFinal_sumet", &MET_RefFinal_sumet, &b_MET_RefFinal_sumet);
	fChain->SetBranchAddress("MET_Cryo_phi", &MET_Cryo_phi, &b_MET_Cryo_phi);
	fChain->SetBranchAddress("MET_Cryo_et", &MET_Cryo_et, &b_MET_Cryo_et);
	fChain->SetBranchAddress("MET_Cryo_sumet", &MET_Cryo_sumet, &b_MET_Cryo_sumet);
	fChain->SetBranchAddress("MET_RefEle_phi", &MET_RefEle_phi, &b_MET_RefEle_phi);
	fChain->SetBranchAddress("MET_RefEle_et", &MET_RefEle_et, &b_MET_RefEle_et);
	fChain->SetBranchAddress("MET_RefEle_sumet", &MET_RefEle_sumet, &b_MET_RefEle_sumet);
	fChain->SetBranchAddress("MET_RefJet_phi", &MET_RefJet_phi, &b_MET_RefJet_phi);
	fChain->SetBranchAddress("MET_RefJet_et", &MET_RefJet_et, &b_MET_RefJet_et);
	fChain->SetBranchAddress("MET_RefJet_sumet", &MET_RefJet_sumet, &b_MET_RefJet_sumet);
	fChain->SetBranchAddress("MET_SoftJets_phi", &MET_SoftJets_phi, &b_MET_SoftJets_phi);
	fChain->SetBranchAddress("MET_SoftJets_et", &MET_SoftJets_et, &b_MET_SoftJets_et);
	fChain->SetBranchAddress("MET_SoftJets_sumet", &MET_SoftJets_sumet, &b_MET_SoftJets_sumet);
	fChain->SetBranchAddress("MET_RefMuon_phi", &MET_RefMuon_phi, &b_MET_RefMuon_phi);
	fChain->SetBranchAddress("MET_RefMuon_et", &MET_RefMuon_et, &b_MET_RefMuon_et);
	fChain->SetBranchAddress("MET_RefMuon_sumet", &MET_RefMuon_sumet, &b_MET_RefMuon_sumet);
	fChain->SetBranchAddress("MET_RefMuon_Staco_phi", &MET_RefMuon_Staco_phi, &b_MET_RefMuon_Staco_phi);
	fChain->SetBranchAddress("MET_RefMuon_Staco_et", &MET_RefMuon_Staco_et, &b_MET_RefMuon_Staco_et);
	fChain->SetBranchAddress("MET_RefMuon_Staco_sumet", &MET_RefMuon_Staco_sumet, &b_MET_RefMuon_Staco_sumet);
	fChain->SetBranchAddress("MET_RefMuon_Muid_phi", &MET_RefMuon_Muid_phi, &b_MET_RefMuon_Muid_phi);
	fChain->SetBranchAddress("MET_RefMuon_Muid_et", &MET_RefMuon_Muid_et, &b_MET_RefMuon_Muid_et);
	fChain->SetBranchAddress("MET_RefMuon_Muid_sumet", &MET_RefMuon_Muid_sumet, &b_MET_RefMuon_Muid_sumet);
	fChain->SetBranchAddress("MET_RefGamma_phi", &MET_RefGamma_phi, &b_MET_RefGamma_phi);
	fChain->SetBranchAddress("MET_RefGamma_et", &MET_RefGamma_et, &b_MET_RefGamma_et);
	fChain->SetBranchAddress("MET_RefGamma_sumet", &MET_RefGamma_sumet, &b_MET_RefGamma_sumet);
	fChain->SetBranchAddress("MET_RefTau_phi", &MET_RefTau_phi, &b_MET_RefTau_phi);
	fChain->SetBranchAddress("MET_RefTau_et", &MET_RefTau_et, &b_MET_RefTau_et);
	fChain->SetBranchAddress("MET_RefTau_sumet", &MET_RefTau_sumet, &b_MET_RefTau_sumet);
	fChain->SetBranchAddress("MET_CellOut_phi", &MET_CellOut_phi, &b_MET_CellOut_phi);
	fChain->SetBranchAddress("MET_CellOut_et", &MET_CellOut_et, &b_MET_CellOut_et);
	fChain->SetBranchAddress("MET_CellOut_sumet", &MET_CellOut_sumet, &b_MET_CellOut_sumet);
	fChain->SetBranchAddress("MET_Track_phi", &MET_Track_phi, &b_MET_Track_phi);
	fChain->SetBranchAddress("MET_Track_et", &MET_Track_et, &b_MET_Track_et);
	fChain->SetBranchAddress("MET_Track_sumet", &MET_Track_sumet, &b_MET_Track_sumet);
	fChain->SetBranchAddress("MET_RefFinal_em_etx", &MET_RefFinal_em_etx, &b_MET_RefFinal_em_etx);
	fChain->SetBranchAddress("MET_RefFinal_em_ety", &MET_RefFinal_em_ety, &b_MET_RefFinal_em_ety);
	fChain->SetBranchAddress("MET_RefFinal_em_phi", &MET_RefFinal_em_phi, &b_MET_RefFinal_em_phi);
	fChain->SetBranchAddress("MET_RefFinal_em_et", &MET_RefFinal_em_et, &b_MET_RefFinal_em_et);
	fChain->SetBranchAddress("MET_RefFinal_em_sumet", &MET_RefFinal_em_sumet, &b_MET_RefFinal_em_sumet);
	fChain->SetBranchAddress("MET_RefEle_em_phi", &MET_RefEle_em_phi, &b_MET_RefEle_em_phi);
	fChain->SetBranchAddress("MET_RefEle_em_et", &MET_RefEle_em_et, &b_MET_RefEle_em_et);
	fChain->SetBranchAddress("MET_RefEle_em_sumet", &MET_RefEle_em_sumet, &b_MET_RefEle_em_sumet);
	fChain->SetBranchAddress("MET_RefJet_em_phi", &MET_RefJet_em_phi, &b_MET_RefJet_em_phi);
	fChain->SetBranchAddress("MET_RefJet_em_et", &MET_RefJet_em_et, &b_MET_RefJet_em_et);
	fChain->SetBranchAddress("MET_RefJet_em_sumet", &MET_RefJet_em_sumet, &b_MET_RefJet_em_sumet);
	fChain->SetBranchAddress("MET_SoftJets_em_phi", &MET_SoftJets_em_phi, &b_MET_SoftJets_em_phi);
	fChain->SetBranchAddress("MET_SoftJets_em_et", &MET_SoftJets_em_et, &b_MET_SoftJets_em_et);
	fChain->SetBranchAddress("MET_SoftJets_em_sumet", &MET_SoftJets_em_sumet, &b_MET_SoftJets_em_sumet);
	fChain->SetBranchAddress("MET_RefMuon_em_phi", &MET_RefMuon_em_phi, &b_MET_RefMuon_em_phi);
	fChain->SetBranchAddress("MET_RefMuon_em_et", &MET_RefMuon_em_et, &b_MET_RefMuon_em_et);
	fChain->SetBranchAddress("MET_RefMuon_em_sumet", &MET_RefMuon_em_sumet, &b_MET_RefMuon_em_sumet);
	fChain->SetBranchAddress("MET_RefMuon_Track_em_phi", &MET_RefMuon_Track_em_phi, &b_MET_RefMuon_Track_em_phi);
	fChain->SetBranchAddress("MET_RefMuon_Track_em_et", &MET_RefMuon_Track_em_et, &b_MET_RefMuon_Track_em_et);
	fChain->SetBranchAddress("MET_RefMuon_Track_em_sumet", &MET_RefMuon_Track_em_sumet, &b_MET_RefMuon_Track_em_sumet);
	fChain->SetBranchAddress("MET_RefGamma_em_phi", &MET_RefGamma_em_phi, &b_MET_RefGamma_em_phi);
	fChain->SetBranchAddress("MET_RefGamma_em_et", &MET_RefGamma_em_et, &b_MET_RefGamma_em_et);
	fChain->SetBranchAddress("MET_RefGamma_em_sumet", &MET_RefGamma_em_sumet, &b_MET_RefGamma_em_sumet);
	fChain->SetBranchAddress("MET_RefTau_em_phi", &MET_RefTau_em_phi, &b_MET_RefTau_em_phi);
	fChain->SetBranchAddress("MET_RefTau_em_et", &MET_RefTau_em_et, &b_MET_RefTau_em_et);
	fChain->SetBranchAddress("MET_RefTau_em_sumet", &MET_RefTau_em_sumet, &b_MET_RefTau_em_sumet);
	fChain->SetBranchAddress("MET_CellOut_em_etx", &MET_CellOut_em_etx, &b_MET_CellOut_em_etx);
	fChain->SetBranchAddress("MET_CellOut_em_ety", &MET_CellOut_em_ety, &b_MET_CellOut_em_ety);
	fChain->SetBranchAddress("MET_CellOut_em_phi", &MET_CellOut_em_phi, &b_MET_CellOut_em_phi);
	fChain->SetBranchAddress("MET_CellOut_em_et", &MET_CellOut_em_et, &b_MET_CellOut_em_et);
	fChain->SetBranchAddress("MET_CellOut_em_sumet", &MET_CellOut_em_sumet, &b_MET_CellOut_em_sumet);
	fChain->SetBranchAddress("MET_Muon_Isol_Staco_phi", &MET_Muon_Isol_Staco_phi, &b_MET_Muon_Isol_Staco_phi);
	fChain->SetBranchAddress("MET_Muon_Isol_Staco_et", &MET_Muon_Isol_Staco_et, &b_MET_Muon_Isol_Staco_et);
	fChain->SetBranchAddress("MET_Muon_Isol_Staco_sumet", &MET_Muon_Isol_Staco_sumet, &b_MET_Muon_Isol_Staco_sumet);
	fChain->SetBranchAddress("MET_Muon_NonIsol_Staco_phi", &MET_Muon_NonIsol_Staco_phi, &b_MET_Muon_NonIsol_Staco_phi);
	fChain->SetBranchAddress("MET_Muon_NonIsol_Staco_et", &MET_Muon_NonIsol_Staco_et, &b_MET_Muon_NonIsol_Staco_et);
	fChain->SetBranchAddress("MET_Muon_NonIsol_Staco_sumet", &MET_Muon_NonIsol_Staco_sumet, &b_MET_Muon_NonIsol_Staco_sumet);
	fChain->SetBranchAddress("MET_Muon_Total_Staco_phi", &MET_Muon_Total_Staco_phi, &b_MET_Muon_Total_Staco_phi);
	fChain->SetBranchAddress("MET_Muon_Total_Staco_et", &MET_Muon_Total_Staco_et, &b_MET_Muon_Total_Staco_et);
	fChain->SetBranchAddress("MET_Muon_Total_Staco_sumet", &MET_Muon_Total_Staco_sumet, &b_MET_Muon_Total_Staco_sumet);
	fChain->SetBranchAddress("MET_Muon_Isol_Muid_phi", &MET_Muon_Isol_Muid_phi, &b_MET_Muon_Isol_Muid_phi);
	fChain->SetBranchAddress("MET_Muon_Isol_Muid_et", &MET_Muon_Isol_Muid_et, &b_MET_Muon_Isol_Muid_et);
	fChain->SetBranchAddress("MET_Muon_Isol_Muid_sumet", &MET_Muon_Isol_Muid_sumet, &b_MET_Muon_Isol_Muid_sumet);
	fChain->SetBranchAddress("MET_Muon_NonIsol_Muid_phi", &MET_Muon_NonIsol_Muid_phi, &b_MET_Muon_NonIsol_Muid_phi);
	fChain->SetBranchAddress("MET_Muon_NonIsol_Muid_et", &MET_Muon_NonIsol_Muid_et, &b_MET_Muon_NonIsol_Muid_et);
	fChain->SetBranchAddress("MET_Muon_NonIsol_Muid_sumet", &MET_Muon_NonIsol_Muid_sumet, &b_MET_Muon_NonIsol_Muid_sumet);
	fChain->SetBranchAddress("MET_Muon_Total_Muid_phi", &MET_Muon_Total_Muid_phi, &b_MET_Muon_Total_Muid_phi);
	fChain->SetBranchAddress("MET_Muon_Total_Muid_et", &MET_Muon_Total_Muid_et, &b_MET_Muon_Total_Muid_et);
	fChain->SetBranchAddress("MET_Muon_Total_Muid_sumet", &MET_Muon_Total_Muid_sumet, &b_MET_Muon_Total_Muid_sumet);
	fChain->SetBranchAddress("MET_MuonBoy_phi", &MET_MuonBoy_phi, &b_MET_MuonBoy_phi);
	fChain->SetBranchAddress("MET_MuonBoy_et", &MET_MuonBoy_et, &b_MET_MuonBoy_et);
	fChain->SetBranchAddress("MET_MuonBoy_sumet", &MET_MuonBoy_sumet, &b_MET_MuonBoy_sumet);
	fChain->SetBranchAddress("MET_RefMuon_Track_phi", &MET_RefMuon_Track_phi, &b_MET_RefMuon_Track_phi);
	fChain->SetBranchAddress("MET_RefMuon_Track_et", &MET_RefMuon_Track_et, &b_MET_RefMuon_Track_et);
	fChain->SetBranchAddress("MET_RefMuon_Track_sumet", &MET_RefMuon_Track_sumet, &b_MET_RefMuon_Track_sumet);
	fChain->SetBranchAddress("MET_RefMuon_Track_Staco_phi", &MET_RefMuon_Track_Staco_phi, &b_MET_RefMuon_Track_Staco_phi);
	fChain->SetBranchAddress("MET_RefMuon_Track_Staco_et", &MET_RefMuon_Track_Staco_et, &b_MET_RefMuon_Track_Staco_et);
	fChain->SetBranchAddress("MET_RefMuon_Track_Staco_sumet", &MET_RefMuon_Track_Staco_sumet, &b_MET_RefMuon_Track_Staco_sumet);
	fChain->SetBranchAddress("MET_RefMuon_Track_Muid_phi", &MET_RefMuon_Track_Muid_phi, &b_MET_RefMuon_Track_Muid_phi);
	fChain->SetBranchAddress("MET_RefMuon_Track_Muid_et", &MET_RefMuon_Track_Muid_et, &b_MET_RefMuon_Track_Muid_et);
	fChain->SetBranchAddress("MET_RefMuon_Track_Muid_sumet", &MET_RefMuon_Track_Muid_sumet, &b_MET_RefMuon_Track_Muid_sumet);
	fChain->SetBranchAddress("MET_CryoCone_phi", &MET_CryoCone_phi, &b_MET_CryoCone_phi);
	fChain->SetBranchAddress("MET_CryoCone_et", &MET_CryoCone_et, &b_MET_CryoCone_et);
	fChain->SetBranchAddress("MET_CryoCone_sumet", &MET_CryoCone_sumet, &b_MET_CryoCone_sumet);
	fChain->SetBranchAddress("MET_Final_phi", &MET_Final_phi, &b_MET_Final_phi);
	fChain->SetBranchAddress("MET_Final_et", &MET_Final_et, &b_MET_Final_et);
	fChain->SetBranchAddress("MET_Final_sumet", &MET_Final_sumet, &b_MET_Final_sumet);
	fChain->SetBranchAddress("MET_MuonBoy_Spectro_phi", &MET_MuonBoy_Spectro_phi, &b_MET_MuonBoy_Spectro_phi);
	fChain->SetBranchAddress("MET_MuonBoy_Spectro_et", &MET_MuonBoy_Spectro_et, &b_MET_MuonBoy_Spectro_et);
	fChain->SetBranchAddress("MET_MuonBoy_Spectro_sumet", &MET_MuonBoy_Spectro_sumet, &b_MET_MuonBoy_Spectro_sumet);
	fChain->SetBranchAddress("MET_MuonBoy_Track_phi", &MET_MuonBoy_Track_phi, &b_MET_MuonBoy_Track_phi);
	fChain->SetBranchAddress("MET_MuonBoy_Track_et", &MET_MuonBoy_Track_et, &b_MET_MuonBoy_Track_et);
	fChain->SetBranchAddress("MET_MuonBoy_Track_sumet", &MET_MuonBoy_Track_sumet, &b_MET_MuonBoy_Track_sumet);
	fChain->SetBranchAddress("MET_MuonMuid_phi", &MET_MuonMuid_phi, &b_MET_MuonMuid_phi);
	fChain->SetBranchAddress("MET_MuonMuid_et", &MET_MuonMuid_et, &b_MET_MuonMuid_et);
	fChain->SetBranchAddress("MET_MuonMuid_sumet", &MET_MuonMuid_sumet, &b_MET_MuonMuid_sumet);
	fChain->SetBranchAddress("MET_Muid_phi", &MET_Muid_phi, &b_MET_Muid_phi);
	fChain->SetBranchAddress("MET_Muid_et", &MET_Muid_et, &b_MET_Muid_et);
	fChain->SetBranchAddress("MET_Muid_sumet", &MET_Muid_sumet, &b_MET_Muid_sumet);
	fChain->SetBranchAddress("MET_Muid_Spectro_phi", &MET_Muid_Spectro_phi, &b_MET_Muid_Spectro_phi);
	fChain->SetBranchAddress("MET_Muid_Spectro_et", &MET_Muid_Spectro_et, &b_MET_Muid_Spectro_et);
	fChain->SetBranchAddress("MET_Muid_Spectro_sumet", &MET_Muid_Spectro_sumet, &b_MET_Muid_Spectro_sumet);
	fChain->SetBranchAddress("MET_Muid_Track_phi", &MET_Muid_Track_phi, &b_MET_Muid_Track_phi);
	fChain->SetBranchAddress("MET_Muid_Track_et", &MET_Muid_Track_et, &b_MET_Muid_Track_et);
	fChain->SetBranchAddress("MET_Muid_Track_sumet", &MET_Muid_Track_sumet, &b_MET_Muid_Track_sumet);
	fChain->SetBranchAddress("MET_Muon_phi", &MET_Muon_phi, &b_MET_Muon_phi);
	fChain->SetBranchAddress("MET_Muon_et", &MET_Muon_et, &b_MET_Muon_et);
	fChain->SetBranchAddress("MET_Muon_sumet", &MET_Muon_sumet, &b_MET_Muon_sumet);
	fChain->SetBranchAddress("MET_TopoObj_phi", &MET_TopoObj_phi, &b_MET_TopoObj_phi);
	fChain->SetBranchAddress("MET_TopoObj_et", &MET_TopoObj_et, &b_MET_TopoObj_et);
	fChain->SetBranchAddress("MET_TopoObj_sumet", &MET_TopoObj_sumet, &b_MET_TopoObj_sumet);
	fChain->SetBranchAddress("MET_LocHadTopoObj_phi", &MET_LocHadTopoObj_phi, &b_MET_LocHadTopoObj_phi);
	fChain->SetBranchAddress("MET_LocHadTopoObj_et", &MET_LocHadTopoObj_et, &b_MET_LocHadTopoObj_et);
	fChain->SetBranchAddress("MET_LocHadTopoObj_sumet", &MET_LocHadTopoObj_sumet, &b_MET_LocHadTopoObj_sumet);
	fChain->SetBranchAddress("MET_Topo_phi", &MET_Topo_phi, &b_MET_Topo_phi);
	fChain->SetBranchAddress("MET_Topo_et", &MET_Topo_et, &b_MET_Topo_et);
	fChain->SetBranchAddress("MET_Topo_sumet", &MET_Topo_sumet, &b_MET_Topo_sumet);
	fChain->SetBranchAddress("MET_Topo_SUMET_EMFrac", &MET_Topo_SUMET_EMFrac, &b_MET_Topo_SUMET_EMFrac);
	fChain->SetBranchAddress("MET_Topo_etx_PEMB", &MET_Topo_etx_PEMB, &b_MET_Topo_etx_PEMB);
	fChain->SetBranchAddress("MET_Topo_ety_PEMB", &MET_Topo_ety_PEMB, &b_MET_Topo_ety_PEMB);
	fChain->SetBranchAddress("MET_Topo_sumet_PEMB", &MET_Topo_sumet_PEMB, &b_MET_Topo_sumet_PEMB);
	fChain->SetBranchAddress("MET_Topo_phi_PEMB", &MET_Topo_phi_PEMB, &b_MET_Topo_phi_PEMB);
	fChain->SetBranchAddress("MET_Topo_etx_EMB", &MET_Topo_etx_EMB, &b_MET_Topo_etx_EMB);
	fChain->SetBranchAddress("MET_Topo_ety_EMB", &MET_Topo_ety_EMB, &b_MET_Topo_ety_EMB);
	fChain->SetBranchAddress("MET_Topo_sumet_EMB", &MET_Topo_sumet_EMB, &b_MET_Topo_sumet_EMB);
	fChain->SetBranchAddress("MET_Topo_phi_EMB", &MET_Topo_phi_EMB, &b_MET_Topo_phi_EMB);
	fChain->SetBranchAddress("MET_Topo_etx_PEMEC", &MET_Topo_etx_PEMEC, &b_MET_Topo_etx_PEMEC);
	fChain->SetBranchAddress("MET_Topo_ety_PEMEC", &MET_Topo_ety_PEMEC, &b_MET_Topo_ety_PEMEC);
	fChain->SetBranchAddress("MET_Topo_sumet_PEMEC", &MET_Topo_sumet_PEMEC, &b_MET_Topo_sumet_PEMEC);
	fChain->SetBranchAddress("MET_Topo_phi_PEMEC", &MET_Topo_phi_PEMEC, &b_MET_Topo_phi_PEMEC);
	fChain->SetBranchAddress("MET_Topo_etx_EME", &MET_Topo_etx_EME, &b_MET_Topo_etx_EME);
	fChain->SetBranchAddress("MET_Topo_ety_EME", &MET_Topo_ety_EME, &b_MET_Topo_ety_EME);
	fChain->SetBranchAddress("MET_Topo_sumet_EME", &MET_Topo_sumet_EME, &b_MET_Topo_sumet_EME);
	fChain->SetBranchAddress("MET_Topo_phi_EME", &MET_Topo_phi_EME, &b_MET_Topo_phi_EME);
	fChain->SetBranchAddress("MET_Topo_etx_TILE", &MET_Topo_etx_TILE, &b_MET_Topo_etx_TILE);
	fChain->SetBranchAddress("MET_Topo_ety_TILE", &MET_Topo_ety_TILE, &b_MET_Topo_ety_TILE);
	fChain->SetBranchAddress("MET_Topo_sumet_TILE", &MET_Topo_sumet_TILE, &b_MET_Topo_sumet_TILE);
	fChain->SetBranchAddress("MET_Topo_phi_TILE", &MET_Topo_phi_TILE, &b_MET_Topo_phi_TILE);
	fChain->SetBranchAddress("MET_Topo_etx_HEC", &MET_Topo_etx_HEC, &b_MET_Topo_etx_HEC);
	fChain->SetBranchAddress("MET_Topo_ety_HEC", &MET_Topo_ety_HEC, &b_MET_Topo_ety_HEC);
	fChain->SetBranchAddress("MET_Topo_sumet_HEC", &MET_Topo_sumet_HEC, &b_MET_Topo_sumet_HEC);
	fChain->SetBranchAddress("MET_Topo_phi_HEC", &MET_Topo_phi_HEC, &b_MET_Topo_phi_HEC);
	fChain->SetBranchAddress("MET_Topo_etx_FCAL", &MET_Topo_etx_FCAL, &b_MET_Topo_etx_FCAL);
	fChain->SetBranchAddress("MET_Topo_ety_FCAL", &MET_Topo_ety_FCAL, &b_MET_Topo_ety_FCAL);
	fChain->SetBranchAddress("MET_Topo_sumet_FCAL", &MET_Topo_sumet_FCAL, &b_MET_Topo_sumet_FCAL);
	fChain->SetBranchAddress("MET_Topo_phi_FCAL", &MET_Topo_phi_FCAL, &b_MET_Topo_phi_FCAL);
	fChain->SetBranchAddress("MET_Topo_nCell_PEMB", &MET_Topo_nCell_PEMB, &b_MET_Topo_nCell_PEMB);
	fChain->SetBranchAddress("MET_Topo_nCell_EMB", &MET_Topo_nCell_EMB, &b_MET_Topo_nCell_EMB);
	fChain->SetBranchAddress("MET_Topo_nCell_PEMEC", &MET_Topo_nCell_PEMEC, &b_MET_Topo_nCell_PEMEC);
	fChain->SetBranchAddress("MET_Topo_nCell_EME", &MET_Topo_nCell_EME, &b_MET_Topo_nCell_EME);
	fChain->SetBranchAddress("MET_Topo_nCell_TILE", &MET_Topo_nCell_TILE, &b_MET_Topo_nCell_TILE);
	fChain->SetBranchAddress("MET_Topo_nCell_HEC", &MET_Topo_nCell_HEC, &b_MET_Topo_nCell_HEC);
	fChain->SetBranchAddress("MET_Topo_nCell_FCAL", &MET_Topo_nCell_FCAL, &b_MET_Topo_nCell_FCAL);
	fChain->SetBranchAddress("MET_Topo_etx_CentralReg", &MET_Topo_etx_CentralReg, &b_MET_Topo_etx_CentralReg);
	fChain->SetBranchAddress("MET_Topo_ety_CentralReg", &MET_Topo_ety_CentralReg, &b_MET_Topo_ety_CentralReg);
	fChain->SetBranchAddress("MET_Topo_sumet_CentralReg", &MET_Topo_sumet_CentralReg, &b_MET_Topo_sumet_CentralReg);
	fChain->SetBranchAddress("MET_Topo_phi_CentralReg", &MET_Topo_phi_CentralReg, &b_MET_Topo_phi_CentralReg);
	fChain->SetBranchAddress("MET_Topo_etx_EndcapRegion", &MET_Topo_etx_EndcapRegion, &b_MET_Topo_etx_EndcapRegion);
	fChain->SetBranchAddress("MET_Topo_ety_EndcapRegion", &MET_Topo_ety_EndcapRegion, &b_MET_Topo_ety_EndcapRegion);
	fChain->SetBranchAddress("MET_Topo_sumet_EndcapRegion", &MET_Topo_sumet_EndcapRegion, &b_MET_Topo_sumet_EndcapRegion);
	fChain->SetBranchAddress("MET_Topo_phi_EndcapRegion", &MET_Topo_phi_EndcapRegion, &b_MET_Topo_phi_EndcapRegion);
	fChain->SetBranchAddress("MET_Topo_etx_ForwardReg", &MET_Topo_etx_ForwardReg, &b_MET_Topo_etx_ForwardReg);
	fChain->SetBranchAddress("MET_Topo_ety_ForwardReg", &MET_Topo_ety_ForwardReg, &b_MET_Topo_ety_ForwardReg);
	fChain->SetBranchAddress("MET_Topo_sumet_ForwardReg", &MET_Topo_sumet_ForwardReg, &b_MET_Topo_sumet_ForwardReg);
	fChain->SetBranchAddress("MET_Topo_phi_ForwardReg", &MET_Topo_phi_ForwardReg, &b_MET_Topo_phi_ForwardReg);
	fChain->SetBranchAddress("MET_CorrTopo_phi", &MET_CorrTopo_phi, &b_MET_CorrTopo_phi);
	fChain->SetBranchAddress("MET_CorrTopo_et", &MET_CorrTopo_et, &b_MET_CorrTopo_et);
	fChain->SetBranchAddress("MET_CorrTopo_sumet", &MET_CorrTopo_sumet, &b_MET_CorrTopo_sumet);
	fChain->SetBranchAddress("MET_CorrTopo_SUMET_EMFrac", &MET_CorrTopo_SUMET_EMFrac, &b_MET_CorrTopo_SUMET_EMFrac);
	fChain->SetBranchAddress("MET_CorrTopo_etx_PEMB", &MET_CorrTopo_etx_PEMB, &b_MET_CorrTopo_etx_PEMB);
	fChain->SetBranchAddress("MET_CorrTopo_ety_PEMB", &MET_CorrTopo_ety_PEMB, &b_MET_CorrTopo_ety_PEMB);
	fChain->SetBranchAddress("MET_CorrTopo_sumet_PEMB", &MET_CorrTopo_sumet_PEMB, &b_MET_CorrTopo_sumet_PEMB);
	fChain->SetBranchAddress("MET_CorrTopo_phi_PEMB", &MET_CorrTopo_phi_PEMB, &b_MET_CorrTopo_phi_PEMB);
	fChain->SetBranchAddress("MET_CorrTopo_etx_EMB", &MET_CorrTopo_etx_EMB, &b_MET_CorrTopo_etx_EMB);
	fChain->SetBranchAddress("MET_CorrTopo_ety_EMB", &MET_CorrTopo_ety_EMB, &b_MET_CorrTopo_ety_EMB);
	fChain->SetBranchAddress("MET_CorrTopo_sumet_EMB", &MET_CorrTopo_sumet_EMB, &b_MET_CorrTopo_sumet_EMB);
	fChain->SetBranchAddress("MET_CorrTopo_phi_EMB", &MET_CorrTopo_phi_EMB, &b_MET_CorrTopo_phi_EMB);
	fChain->SetBranchAddress("MET_CorrTopo_etx_PEMEC", &MET_CorrTopo_etx_PEMEC, &b_MET_CorrTopo_etx_PEMEC);
	fChain->SetBranchAddress("MET_CorrTopo_ety_PEMEC", &MET_CorrTopo_ety_PEMEC, &b_MET_CorrTopo_ety_PEMEC);
	fChain->SetBranchAddress("MET_CorrTopo_sumet_PEMEC", &MET_CorrTopo_sumet_PEMEC, &b_MET_CorrTopo_sumet_PEMEC);
	fChain->SetBranchAddress("MET_CorrTopo_phi_PEMEC", &MET_CorrTopo_phi_PEMEC, &b_MET_CorrTopo_phi_PEMEC);
	fChain->SetBranchAddress("MET_CorrTopo_etx_EME", &MET_CorrTopo_etx_EME, &b_MET_CorrTopo_etx_EME);
	fChain->SetBranchAddress("MET_CorrTopo_ety_EME", &MET_CorrTopo_ety_EME, &b_MET_CorrTopo_ety_EME);
	fChain->SetBranchAddress("MET_CorrTopo_sumet_EME", &MET_CorrTopo_sumet_EME, &b_MET_CorrTopo_sumet_EME);
	fChain->SetBranchAddress("MET_CorrTopo_phi_EME", &MET_CorrTopo_phi_EME, &b_MET_CorrTopo_phi_EME);
	fChain->SetBranchAddress("MET_CorrTopo_etx_TILE", &MET_CorrTopo_etx_TILE, &b_MET_CorrTopo_etx_TILE);
	fChain->SetBranchAddress("MET_CorrTopo_ety_TILE", &MET_CorrTopo_ety_TILE, &b_MET_CorrTopo_ety_TILE);
	fChain->SetBranchAddress("MET_CorrTopo_sumet_TILE", &MET_CorrTopo_sumet_TILE, &b_MET_CorrTopo_sumet_TILE);
	fChain->SetBranchAddress("MET_CorrTopo_phi_TILE", &MET_CorrTopo_phi_TILE, &b_MET_CorrTopo_phi_TILE);
	fChain->SetBranchAddress("MET_CorrTopo_etx_HEC", &MET_CorrTopo_etx_HEC, &b_MET_CorrTopo_etx_HEC);
	fChain->SetBranchAddress("MET_CorrTopo_ety_HEC", &MET_CorrTopo_ety_HEC, &b_MET_CorrTopo_ety_HEC);
	fChain->SetBranchAddress("MET_CorrTopo_sumet_HEC", &MET_CorrTopo_sumet_HEC, &b_MET_CorrTopo_sumet_HEC);
	fChain->SetBranchAddress("MET_CorrTopo_phi_HEC", &MET_CorrTopo_phi_HEC, &b_MET_CorrTopo_phi_HEC);
	fChain->SetBranchAddress("MET_CorrTopo_etx_FCAL", &MET_CorrTopo_etx_FCAL, &b_MET_CorrTopo_etx_FCAL);
	fChain->SetBranchAddress("MET_CorrTopo_ety_FCAL", &MET_CorrTopo_ety_FCAL, &b_MET_CorrTopo_ety_FCAL);
	fChain->SetBranchAddress("MET_CorrTopo_sumet_FCAL", &MET_CorrTopo_sumet_FCAL, &b_MET_CorrTopo_sumet_FCAL);
	fChain->SetBranchAddress("MET_CorrTopo_phi_FCAL", &MET_CorrTopo_phi_FCAL, &b_MET_CorrTopo_phi_FCAL);
	fChain->SetBranchAddress("MET_CorrTopo_nCell_PEMB", &MET_CorrTopo_nCell_PEMB, &b_MET_CorrTopo_nCell_PEMB);
	fChain->SetBranchAddress("MET_CorrTopo_nCell_EMB", &MET_CorrTopo_nCell_EMB, &b_MET_CorrTopo_nCell_EMB);
	fChain->SetBranchAddress("MET_CorrTopo_nCell_PEMEC", &MET_CorrTopo_nCell_PEMEC, &b_MET_CorrTopo_nCell_PEMEC);
	fChain->SetBranchAddress("MET_CorrTopo_nCell_EME", &MET_CorrTopo_nCell_EME, &b_MET_CorrTopo_nCell_EME);
	fChain->SetBranchAddress("MET_CorrTopo_nCell_TILE", &MET_CorrTopo_nCell_TILE, &b_MET_CorrTopo_nCell_TILE);
	fChain->SetBranchAddress("MET_CorrTopo_nCell_HEC", &MET_CorrTopo_nCell_HEC, &b_MET_CorrTopo_nCell_HEC);
	fChain->SetBranchAddress("MET_CorrTopo_nCell_FCAL", &MET_CorrTopo_nCell_FCAL, &b_MET_CorrTopo_nCell_FCAL);
	fChain->SetBranchAddress("MET_CorrTopo_etx_CentralReg", &MET_CorrTopo_etx_CentralReg, &b_MET_CorrTopo_etx_CentralReg);
	fChain->SetBranchAddress("MET_CorrTopo_ety_CentralReg", &MET_CorrTopo_ety_CentralReg, &b_MET_CorrTopo_ety_CentralReg);
	fChain->SetBranchAddress("MET_CorrTopo_sumet_CentralReg", &MET_CorrTopo_sumet_CentralReg, &b_MET_CorrTopo_sumet_CentralReg);
	fChain->SetBranchAddress("MET_CorrTopo_phi_CentralReg", &MET_CorrTopo_phi_CentralReg, &b_MET_CorrTopo_phi_CentralReg);
	fChain->SetBranchAddress("MET_CorrTopo_etx_EndcapRegion", &MET_CorrTopo_etx_EndcapRegion, &b_MET_CorrTopo_etx_EndcapRegion);
	fChain->SetBranchAddress("MET_CorrTopo_ety_EndcapRegion", &MET_CorrTopo_ety_EndcapRegion, &b_MET_CorrTopo_ety_EndcapRegion);
	fChain->SetBranchAddress("MET_CorrTopo_sumet_EndcapRegion", &MET_CorrTopo_sumet_EndcapRegion, &b_MET_CorrTopo_sumet_EndcapRegion);
	fChain->SetBranchAddress("MET_CorrTopo_phi_EndcapRegion", &MET_CorrTopo_phi_EndcapRegion, &b_MET_CorrTopo_phi_EndcapRegion);
	fChain->SetBranchAddress("MET_CorrTopo_etx_ForwardReg", &MET_CorrTopo_etx_ForwardReg, &b_MET_CorrTopo_etx_ForwardReg);
	fChain->SetBranchAddress("MET_CorrTopo_ety_ForwardReg", &MET_CorrTopo_ety_ForwardReg, &b_MET_CorrTopo_ety_ForwardReg);
	fChain->SetBranchAddress("MET_CorrTopo_sumet_ForwardReg", &MET_CorrTopo_sumet_ForwardReg, &b_MET_CorrTopo_sumet_ForwardReg);
	fChain->SetBranchAddress("MET_CorrTopo_phi_ForwardReg", &MET_CorrTopo_phi_ForwardReg, &b_MET_CorrTopo_phi_ForwardReg);
	fChain->SetBranchAddress("MET_LocHadTopo_phi", &MET_LocHadTopo_phi, &b_MET_LocHadTopo_phi);
	fChain->SetBranchAddress("MET_LocHadTopo_et", &MET_LocHadTopo_et, &b_MET_LocHadTopo_et);
	fChain->SetBranchAddress("MET_LocHadTopo_sumet", &MET_LocHadTopo_sumet, &b_MET_LocHadTopo_sumet);
	fChain->SetBranchAddress("MET_LocHadTopo_SUMET_EMFrac", &MET_LocHadTopo_SUMET_EMFrac, &b_MET_LocHadTopo_SUMET_EMFrac);
	fChain->SetBranchAddress("MET_LocHadTopo_etx_PEMB", &MET_LocHadTopo_etx_PEMB, &b_MET_LocHadTopo_etx_PEMB);
	fChain->SetBranchAddress("MET_LocHadTopo_ety_PEMB", &MET_LocHadTopo_ety_PEMB, &b_MET_LocHadTopo_ety_PEMB);
	fChain->SetBranchAddress("MET_LocHadTopo_sumet_PEMB", &MET_LocHadTopo_sumet_PEMB, &b_MET_LocHadTopo_sumet_PEMB);
	fChain->SetBranchAddress("MET_LocHadTopo_phi_PEMB", &MET_LocHadTopo_phi_PEMB, &b_MET_LocHadTopo_phi_PEMB);
	fChain->SetBranchAddress("MET_LocHadTopo_etx_EMB", &MET_LocHadTopo_etx_EMB, &b_MET_LocHadTopo_etx_EMB);
	fChain->SetBranchAddress("MET_LocHadTopo_ety_EMB", &MET_LocHadTopo_ety_EMB, &b_MET_LocHadTopo_ety_EMB);
	fChain->SetBranchAddress("MET_LocHadTopo_sumet_EMB", &MET_LocHadTopo_sumet_EMB, &b_MET_LocHadTopo_sumet_EMB);
	fChain->SetBranchAddress("MET_LocHadTopo_phi_EMB", &MET_LocHadTopo_phi_EMB, &b_MET_LocHadTopo_phi_EMB);
	fChain->SetBranchAddress("MET_LocHadTopo_etx_PEMEC", &MET_LocHadTopo_etx_PEMEC, &b_MET_LocHadTopo_etx_PEMEC);
	fChain->SetBranchAddress("MET_LocHadTopo_ety_PEMEC", &MET_LocHadTopo_ety_PEMEC, &b_MET_LocHadTopo_ety_PEMEC);
	fChain->SetBranchAddress("MET_LocHadTopo_sumet_PEMEC", &MET_LocHadTopo_sumet_PEMEC, &b_MET_LocHadTopo_sumet_PEMEC);
	fChain->SetBranchAddress("MET_LocHadTopo_phi_PEMEC", &MET_LocHadTopo_phi_PEMEC, &b_MET_LocHadTopo_phi_PEMEC);
	fChain->SetBranchAddress("MET_LocHadTopo_etx_EME", &MET_LocHadTopo_etx_EME, &b_MET_LocHadTopo_etx_EME);
	fChain->SetBranchAddress("MET_LocHadTopo_ety_EME", &MET_LocHadTopo_ety_EME, &b_MET_LocHadTopo_ety_EME);
	fChain->SetBranchAddress("MET_LocHadTopo_sumet_EME", &MET_LocHadTopo_sumet_EME, &b_MET_LocHadTopo_sumet_EME);
	fChain->SetBranchAddress("MET_LocHadTopo_phi_EME", &MET_LocHadTopo_phi_EME, &b_MET_LocHadTopo_phi_EME);
	fChain->SetBranchAddress("MET_LocHadTopo_etx_TILE", &MET_LocHadTopo_etx_TILE, &b_MET_LocHadTopo_etx_TILE);
	fChain->SetBranchAddress("MET_LocHadTopo_ety_TILE", &MET_LocHadTopo_ety_TILE, &b_MET_LocHadTopo_ety_TILE);
	fChain->SetBranchAddress("MET_LocHadTopo_sumet_TILE", &MET_LocHadTopo_sumet_TILE, &b_MET_LocHadTopo_sumet_TILE);
	fChain->SetBranchAddress("MET_LocHadTopo_phi_TILE", &MET_LocHadTopo_phi_TILE, &b_MET_LocHadTopo_phi_TILE);
	fChain->SetBranchAddress("MET_LocHadTopo_etx_HEC", &MET_LocHadTopo_etx_HEC, &b_MET_LocHadTopo_etx_HEC);
	fChain->SetBranchAddress("MET_LocHadTopo_ety_HEC", &MET_LocHadTopo_ety_HEC, &b_MET_LocHadTopo_ety_HEC);
	fChain->SetBranchAddress("MET_LocHadTopo_sumet_HEC", &MET_LocHadTopo_sumet_HEC, &b_MET_LocHadTopo_sumet_HEC);
	fChain->SetBranchAddress("MET_LocHadTopo_phi_HEC", &MET_LocHadTopo_phi_HEC, &b_MET_LocHadTopo_phi_HEC);
	fChain->SetBranchAddress("MET_LocHadTopo_etx_FCAL", &MET_LocHadTopo_etx_FCAL, &b_MET_LocHadTopo_etx_FCAL);
	fChain->SetBranchAddress("MET_LocHadTopo_ety_FCAL", &MET_LocHadTopo_ety_FCAL, &b_MET_LocHadTopo_ety_FCAL);
	fChain->SetBranchAddress("MET_LocHadTopo_sumet_FCAL", &MET_LocHadTopo_sumet_FCAL, &b_MET_LocHadTopo_sumet_FCAL);
	fChain->SetBranchAddress("MET_LocHadTopo_phi_FCAL", &MET_LocHadTopo_phi_FCAL, &b_MET_LocHadTopo_phi_FCAL);
	fChain->SetBranchAddress("MET_LocHadTopo_nCell_PEMB", &MET_LocHadTopo_nCell_PEMB, &b_MET_LocHadTopo_nCell_PEMB);
	fChain->SetBranchAddress("MET_LocHadTopo_nCell_EMB", &MET_LocHadTopo_nCell_EMB, &b_MET_LocHadTopo_nCell_EMB);
	fChain->SetBranchAddress("MET_LocHadTopo_nCell_PEMEC", &MET_LocHadTopo_nCell_PEMEC, &b_MET_LocHadTopo_nCell_PEMEC);
	fChain->SetBranchAddress("MET_LocHadTopo_nCell_EME", &MET_LocHadTopo_nCell_EME, &b_MET_LocHadTopo_nCell_EME);
	fChain->SetBranchAddress("MET_LocHadTopo_nCell_TILE", &MET_LocHadTopo_nCell_TILE, &b_MET_LocHadTopo_nCell_TILE);
	fChain->SetBranchAddress("MET_LocHadTopo_nCell_HEC", &MET_LocHadTopo_nCell_HEC, &b_MET_LocHadTopo_nCell_HEC);
	fChain->SetBranchAddress("MET_LocHadTopo_nCell_FCAL", &MET_LocHadTopo_nCell_FCAL, &b_MET_LocHadTopo_nCell_FCAL);
	fChain->SetBranchAddress("MET_LocHadTopo_etx_CentralReg", &MET_LocHadTopo_etx_CentralReg, &b_MET_LocHadTopo_etx_CentralReg);
	fChain->SetBranchAddress("MET_LocHadTopo_ety_CentralReg", &MET_LocHadTopo_ety_CentralReg, &b_MET_LocHadTopo_ety_CentralReg);
	fChain->SetBranchAddress("MET_LocHadTopo_sumet_CentralReg", &MET_LocHadTopo_sumet_CentralReg, &b_MET_LocHadTopo_sumet_CentralReg);
	fChain->SetBranchAddress("MET_LocHadTopo_phi_CentralReg", &MET_LocHadTopo_phi_CentralReg, &b_MET_LocHadTopo_phi_CentralReg);
	fChain->SetBranchAddress("MET_LocHadTopo_etx_EndcapRegion", &MET_LocHadTopo_etx_EndcapRegion, &b_MET_LocHadTopo_etx_EndcapRegion);
	fChain->SetBranchAddress("MET_LocHadTopo_ety_EndcapRegion", &MET_LocHadTopo_ety_EndcapRegion, &b_MET_LocHadTopo_ety_EndcapRegion);
	fChain->SetBranchAddress("MET_LocHadTopo_sumet_EndcapRegion", &MET_LocHadTopo_sumet_EndcapRegion, &b_MET_LocHadTopo_sumet_EndcapRegion);
	fChain->SetBranchAddress("MET_LocHadTopo_phi_EndcapRegion", &MET_LocHadTopo_phi_EndcapRegion, &b_MET_LocHadTopo_phi_EndcapRegion);
	fChain->SetBranchAddress("MET_LocHadTopo_etx_ForwardReg", &MET_LocHadTopo_etx_ForwardReg, &b_MET_LocHadTopo_etx_ForwardReg);
	fChain->SetBranchAddress("MET_LocHadTopo_ety_ForwardReg", &MET_LocHadTopo_ety_ForwardReg, &b_MET_LocHadTopo_ety_ForwardReg);
	fChain->SetBranchAddress("MET_LocHadTopo_sumet_ForwardReg", &MET_LocHadTopo_sumet_ForwardReg, &b_MET_LocHadTopo_sumet_ForwardReg);
	fChain->SetBranchAddress("MET_LocHadTopo_phi_ForwardReg", &MET_LocHadTopo_phi_ForwardReg, &b_MET_LocHadTopo_phi_ForwardReg);
	fChain->SetBranchAddress("MET_Calib_phi", &MET_Calib_phi, &b_MET_Calib_phi);
	fChain->SetBranchAddress("MET_Calib_et", &MET_Calib_et, &b_MET_Calib_et);
	fChain->SetBranchAddress("MET_Calib_sumet", &MET_Calib_sumet, &b_MET_Calib_sumet);
	fChain->SetBranchAddress("MET_Calib_SUMET_EMFrac", &MET_Calib_SUMET_EMFrac, &b_MET_Calib_SUMET_EMFrac);
	fChain->SetBranchAddress("MET_Calib_etx_PEMB", &MET_Calib_etx_PEMB, &b_MET_Calib_etx_PEMB);
	fChain->SetBranchAddress("MET_Calib_ety_PEMB", &MET_Calib_ety_PEMB, &b_MET_Calib_ety_PEMB);
	fChain->SetBranchAddress("MET_Calib_sumet_PEMB", &MET_Calib_sumet_PEMB, &b_MET_Calib_sumet_PEMB);
	fChain->SetBranchAddress("MET_Calib_phi_PEMB", &MET_Calib_phi_PEMB, &b_MET_Calib_phi_PEMB);
	fChain->SetBranchAddress("MET_Calib_etx_EMB", &MET_Calib_etx_EMB, &b_MET_Calib_etx_EMB);
	fChain->SetBranchAddress("MET_Calib_ety_EMB", &MET_Calib_ety_EMB, &b_MET_Calib_ety_EMB);
	fChain->SetBranchAddress("MET_Calib_sumet_EMB", &MET_Calib_sumet_EMB, &b_MET_Calib_sumet_EMB);
	fChain->SetBranchAddress("MET_Calib_phi_EMB", &MET_Calib_phi_EMB, &b_MET_Calib_phi_EMB);
	fChain->SetBranchAddress("MET_Calib_etx_PEMEC", &MET_Calib_etx_PEMEC, &b_MET_Calib_etx_PEMEC);
	fChain->SetBranchAddress("MET_Calib_ety_PEMEC", &MET_Calib_ety_PEMEC, &b_MET_Calib_ety_PEMEC);
	fChain->SetBranchAddress("MET_Calib_sumet_PEMEC", &MET_Calib_sumet_PEMEC, &b_MET_Calib_sumet_PEMEC);
	fChain->SetBranchAddress("MET_Calib_phi_PEMEC", &MET_Calib_phi_PEMEC, &b_MET_Calib_phi_PEMEC);
	fChain->SetBranchAddress("MET_Calib_etx_EME", &MET_Calib_etx_EME, &b_MET_Calib_etx_EME);
	fChain->SetBranchAddress("MET_Calib_ety_EME", &MET_Calib_ety_EME, &b_MET_Calib_ety_EME);
	fChain->SetBranchAddress("MET_Calib_sumet_EME", &MET_Calib_sumet_EME, &b_MET_Calib_sumet_EME);
	fChain->SetBranchAddress("MET_Calib_phi_EME", &MET_Calib_phi_EME, &b_MET_Calib_phi_EME);
	fChain->SetBranchAddress("MET_Calib_etx_TILE", &MET_Calib_etx_TILE, &b_MET_Calib_etx_TILE);
	fChain->SetBranchAddress("MET_Calib_ety_TILE", &MET_Calib_ety_TILE, &b_MET_Calib_ety_TILE);
	fChain->SetBranchAddress("MET_Calib_sumet_TILE", &MET_Calib_sumet_TILE, &b_MET_Calib_sumet_TILE);
	fChain->SetBranchAddress("MET_Calib_phi_TILE", &MET_Calib_phi_TILE, &b_MET_Calib_phi_TILE);
	fChain->SetBranchAddress("MET_Calib_etx_HEC", &MET_Calib_etx_HEC, &b_MET_Calib_etx_HEC);
	fChain->SetBranchAddress("MET_Calib_ety_HEC", &MET_Calib_ety_HEC, &b_MET_Calib_ety_HEC);
	fChain->SetBranchAddress("MET_Calib_sumet_HEC", &MET_Calib_sumet_HEC, &b_MET_Calib_sumet_HEC);
	fChain->SetBranchAddress("MET_Calib_phi_HEC", &MET_Calib_phi_HEC, &b_MET_Calib_phi_HEC);
	fChain->SetBranchAddress("MET_Calib_etx_FCAL", &MET_Calib_etx_FCAL, &b_MET_Calib_etx_FCAL);
	fChain->SetBranchAddress("MET_Calib_ety_FCAL", &MET_Calib_ety_FCAL, &b_MET_Calib_ety_FCAL);
	fChain->SetBranchAddress("MET_Calib_sumet_FCAL", &MET_Calib_sumet_FCAL, &b_MET_Calib_sumet_FCAL);
	fChain->SetBranchAddress("MET_Calib_phi_FCAL", &MET_Calib_phi_FCAL, &b_MET_Calib_phi_FCAL);
	fChain->SetBranchAddress("MET_Calib_nCell_PEMB", &MET_Calib_nCell_PEMB, &b_MET_Calib_nCell_PEMB);
	fChain->SetBranchAddress("MET_Calib_nCell_EMB", &MET_Calib_nCell_EMB, &b_MET_Calib_nCell_EMB);
	fChain->SetBranchAddress("MET_Calib_nCell_PEMEC", &MET_Calib_nCell_PEMEC, &b_MET_Calib_nCell_PEMEC);
	fChain->SetBranchAddress("MET_Calib_nCell_EME", &MET_Calib_nCell_EME, &b_MET_Calib_nCell_EME);
	fChain->SetBranchAddress("MET_Calib_nCell_TILE", &MET_Calib_nCell_TILE, &b_MET_Calib_nCell_TILE);
	fChain->SetBranchAddress("MET_Calib_nCell_HEC", &MET_Calib_nCell_HEC, &b_MET_Calib_nCell_HEC);
	fChain->SetBranchAddress("MET_Calib_nCell_FCAL", &MET_Calib_nCell_FCAL, &b_MET_Calib_nCell_FCAL);
	fChain->SetBranchAddress("MET_Calib_etx_CentralReg", &MET_Calib_etx_CentralReg, &b_MET_Calib_etx_CentralReg);
	fChain->SetBranchAddress("MET_Calib_ety_CentralReg", &MET_Calib_ety_CentralReg, &b_MET_Calib_ety_CentralReg);
	fChain->SetBranchAddress("MET_Calib_sumet_CentralReg", &MET_Calib_sumet_CentralReg, &b_MET_Calib_sumet_CentralReg);
	fChain->SetBranchAddress("MET_Calib_phi_CentralReg", &MET_Calib_phi_CentralReg, &b_MET_Calib_phi_CentralReg);
	fChain->SetBranchAddress("MET_Calib_etx_EndcapRegion", &MET_Calib_etx_EndcapRegion, &b_MET_Calib_etx_EndcapRegion);
	fChain->SetBranchAddress("MET_Calib_ety_EndcapRegion", &MET_Calib_ety_EndcapRegion, &b_MET_Calib_ety_EndcapRegion);
	fChain->SetBranchAddress("MET_Calib_sumet_EndcapRegion", &MET_Calib_sumet_EndcapRegion, &b_MET_Calib_sumet_EndcapRegion);
	fChain->SetBranchAddress("MET_Calib_phi_EndcapRegion", &MET_Calib_phi_EndcapRegion, &b_MET_Calib_phi_EndcapRegion);
	fChain->SetBranchAddress("MET_Calib_etx_ForwardReg", &MET_Calib_etx_ForwardReg, &b_MET_Calib_etx_ForwardReg);
	fChain->SetBranchAddress("MET_Calib_ety_ForwardReg", &MET_Calib_ety_ForwardReg, &b_MET_Calib_ety_ForwardReg);
	fChain->SetBranchAddress("MET_Calib_sumet_ForwardReg", &MET_Calib_sumet_ForwardReg, &b_MET_Calib_sumet_ForwardReg);
	fChain->SetBranchAddress("MET_Calib_phi_ForwardReg", &MET_Calib_phi_ForwardReg, &b_MET_Calib_phi_ForwardReg);
	if(isMC)
	{
		fChain->SetBranchAddress("MET_Truth_NonInt_etx", &MET_Truth_NonInt_etx, &b_MET_Truth_NonInt_etx);
		fChain->SetBranchAddress("MET_Truth_NonInt_ety", &MET_Truth_NonInt_ety, &b_MET_Truth_NonInt_ety);
		fChain->SetBranchAddress("MET_Truth_NonInt_phi", &MET_Truth_NonInt_phi, &b_MET_Truth_NonInt_phi);
		fChain->SetBranchAddress("MET_Truth_NonInt_et", &MET_Truth_NonInt_et, &b_MET_Truth_NonInt_et);
		fChain->SetBranchAddress("MET_Truth_NonInt_sumet", &MET_Truth_NonInt_sumet, &b_MET_Truth_NonInt_sumet);
		fChain->SetBranchAddress("MET_Truth_Int_phi", &MET_Truth_Int_phi, &b_MET_Truth_Int_phi);
		fChain->SetBranchAddress("MET_Truth_IntCentral_phi", &MET_Truth_IntCentral_phi, &b_MET_Truth_IntCentral_phi);
		fChain->SetBranchAddress("MET_Truth_IntFwd_phi", &MET_Truth_IntFwd_phi, &b_MET_Truth_IntFwd_phi);
		fChain->SetBranchAddress("MET_Truth_IntOutCover_phi", &MET_Truth_IntOutCover_phi, &b_MET_Truth_IntOutCover_phi);
		fChain->SetBranchAddress("MET_Truth_IntMuons_phi", &MET_Truth_IntMuons_phi, &b_MET_Truth_IntMuons_phi);
		fChain->SetBranchAddress("MET_Truth_Int_et", &MET_Truth_Int_et, &b_MET_Truth_Int_et);
		fChain->SetBranchAddress("MET_Truth_IntCentral_et", &MET_Truth_IntCentral_et, &b_MET_Truth_IntCentral_et);
		fChain->SetBranchAddress("MET_Truth_IntFwd_et", &MET_Truth_IntFwd_et, &b_MET_Truth_IntFwd_et);
		fChain->SetBranchAddress("MET_Truth_IntOutCover_et", &MET_Truth_IntOutCover_et, &b_MET_Truth_IntOutCover_et);
		fChain->SetBranchAddress("MET_Truth_IntMuons_et", &MET_Truth_IntMuons_et, &b_MET_Truth_IntMuons_et);
		fChain->SetBranchAddress("MET_Truth_Int_sumet", &MET_Truth_Int_sumet, &b_MET_Truth_Int_sumet);
		fChain->SetBranchAddress("MET_Truth_IntCentral_sumet", &MET_Truth_IntCentral_sumet, &b_MET_Truth_IntCentral_sumet);
		fChain->SetBranchAddress("MET_Truth_IntFwd_sumet", &MET_Truth_IntFwd_sumet, &b_MET_Truth_IntFwd_sumet);
		fChain->SetBranchAddress("MET_Truth_IntOutCover_sumet", &MET_Truth_IntOutCover_sumet, &b_MET_Truth_IntOutCover_sumet);
		fChain->SetBranchAddress("MET_Truth_IntMuons_sumet", &MET_Truth_IntMuons_sumet, &b_MET_Truth_IntMuons_sumet);
		fChain->SetBranchAddress("MET_Truth_PileUp_NonInt_etx", &MET_Truth_PileUp_NonInt_etx, &b_MET_Truth_PileUp_NonInt_etx);
		fChain->SetBranchAddress("MET_Truth_PileUp_NonInt_ety", &MET_Truth_PileUp_NonInt_ety, &b_MET_Truth_PileUp_NonInt_ety);
		fChain->SetBranchAddress("MET_Truth_PileUp_NonInt_phi", &MET_Truth_PileUp_NonInt_phi, &b_MET_Truth_PileUp_NonInt_phi);
		fChain->SetBranchAddress("MET_Truth_PileUp_NonInt_et", &MET_Truth_PileUp_NonInt_et, &b_MET_Truth_PileUp_NonInt_et);
		fChain->SetBranchAddress("MET_Truth_PileUp_NonInt_sumet", &MET_Truth_PileUp_NonInt_sumet, &b_MET_Truth_PileUp_NonInt_sumet);
		fChain->SetBranchAddress("MET_Truth_PileUp_Int_etx", &MET_Truth_PileUp_Int_etx, &b_MET_Truth_PileUp_Int_etx);
		fChain->SetBranchAddress("MET_Truth_PileUp_Int_ety", &MET_Truth_PileUp_Int_ety, &b_MET_Truth_PileUp_Int_ety);
		fChain->SetBranchAddress("MET_Truth_PileUp_IntCentral_etx", &MET_Truth_PileUp_IntCentral_etx, &b_MET_Truth_PileUp_IntCentral_etx);
		fChain->SetBranchAddress("MET_Truth_PileUp_IntCentral_ety", &MET_Truth_PileUp_IntCentral_ety, &b_MET_Truth_PileUp_IntCentral_ety);
		fChain->SetBranchAddress("MET_Truth_PileUp_IntFwd_etx", &MET_Truth_PileUp_IntFwd_etx, &b_MET_Truth_PileUp_IntFwd_etx);
		fChain->SetBranchAddress("MET_Truth_PileUp_IntFwd_ety", &MET_Truth_PileUp_IntFwd_ety, &b_MET_Truth_PileUp_IntFwd_ety);
		fChain->SetBranchAddress("MET_Truth_PileUp_IntOutCover_etx", &MET_Truth_PileUp_IntOutCover_etx, &b_MET_Truth_PileUp_IntOutCover_etx);
		fChain->SetBranchAddress("MET_Truth_PileUp_IntOutCover_ety", &MET_Truth_PileUp_IntOutCover_ety, &b_MET_Truth_PileUp_IntOutCover_ety);
		fChain->SetBranchAddress("MET_Truth_PileUp_IntMuons_etx", &MET_Truth_PileUp_IntMuons_etx, &b_MET_Truth_PileUp_IntMuons_etx);
		fChain->SetBranchAddress("MET_Truth_PileUp_IntMuons_ety", &MET_Truth_PileUp_IntMuons_ety, &b_MET_Truth_PileUp_IntMuons_ety);
		fChain->SetBranchAddress("MET_Truth_PileUp_Int_phi", &MET_Truth_PileUp_Int_phi, &b_MET_Truth_PileUp_Int_phi);
		fChain->SetBranchAddress("MET_Truth_PileUp_IntCentral_phi", &MET_Truth_PileUp_IntCentral_phi, &b_MET_Truth_PileUp_IntCentral_phi);
		fChain->SetBranchAddress("MET_Truth_PileUp_IntFwd_phi", &MET_Truth_PileUp_IntFwd_phi, &b_MET_Truth_PileUp_IntFwd_phi);
		fChain->SetBranchAddress("MET_Truth_PileUp_IntOutCover_phi", &MET_Truth_PileUp_IntOutCover_phi, &b_MET_Truth_PileUp_IntOutCover_phi);
		fChain->SetBranchAddress("MET_Truth_PileUp_IntMuons_phi", &MET_Truth_PileUp_IntMuons_phi, &b_MET_Truth_PileUp_IntMuons_phi);
		fChain->SetBranchAddress("MET_Truth_PileUp_Int_et", &MET_Truth_PileUp_Int_et, &b_MET_Truth_PileUp_Int_et);
		fChain->SetBranchAddress("MET_Truth_PileUp_IntCentral_et", &MET_Truth_PileUp_IntCentral_et, &b_MET_Truth_PileUp_IntCentral_et);
		fChain->SetBranchAddress("MET_Truth_PileUp_IntFwd_et", &MET_Truth_PileUp_IntFwd_et, &b_MET_Truth_PileUp_IntFwd_et);
		fChain->SetBranchAddress("MET_Truth_PileUp_IntOutCover_et", &MET_Truth_PileUp_IntOutCover_et, &b_MET_Truth_PileUp_IntOutCover_et);
		fChain->SetBranchAddress("MET_Truth_PileUp_IntMuons_et", &MET_Truth_PileUp_IntMuons_et, &b_MET_Truth_PileUp_IntMuons_et);
		fChain->SetBranchAddress("MET_Truth_PileUp_Int_sumet", &MET_Truth_PileUp_Int_sumet, &b_MET_Truth_PileUp_Int_sumet);
		fChain->SetBranchAddress("MET_Truth_PileUp_IntCentral_sumet", &MET_Truth_PileUp_IntCentral_sumet, &b_MET_Truth_PileUp_IntCentral_sumet);
		fChain->SetBranchAddress("MET_Truth_PileUp_IntFwd_sumet", &MET_Truth_PileUp_IntFwd_sumet, &b_MET_Truth_PileUp_IntFwd_sumet);
		fChain->SetBranchAddress("MET_Truth_PileUp_IntOutCover_sumet", &MET_Truth_PileUp_IntOutCover_sumet, &b_MET_Truth_PileUp_IntOutCover_sumet);
		fChain->SetBranchAddress("MET_Truth_PileUp_IntMuons_sumet", &MET_Truth_PileUp_IntMuons_sumet, &b_MET_Truth_PileUp_IntMuons_sumet);
	}
	fChain->SetBranchAddress("MET_DM_Crack1_etx", &MET_DM_Crack1_etx, &b_MET_DM_Crack1_etx);
	fChain->SetBranchAddress("MET_DM_Crack1_ety", &MET_DM_Crack1_ety, &b_MET_DM_Crack1_ety);
	fChain->SetBranchAddress("MET_DM_Crack1_phi", &MET_DM_Crack1_phi, &b_MET_DM_Crack1_phi);
	fChain->SetBranchAddress("MET_DM_Crack1_et", &MET_DM_Crack1_et, &b_MET_DM_Crack1_et);
	fChain->SetBranchAddress("MET_DM_Crack1_sumet", &MET_DM_Crack1_sumet, &b_MET_DM_Crack1_sumet);
	fChain->SetBranchAddress("MET_DM_Crack2_etx", &MET_DM_Crack2_etx, &b_MET_DM_Crack2_etx);
	fChain->SetBranchAddress("MET_DM_Crack2_ety", &MET_DM_Crack2_ety, &b_MET_DM_Crack2_ety);
	fChain->SetBranchAddress("MET_DM_Crack2_phi", &MET_DM_Crack2_phi, &b_MET_DM_Crack2_phi);
	fChain->SetBranchAddress("MET_DM_Crack2_et", &MET_DM_Crack2_et, &b_MET_DM_Crack2_et);
	fChain->SetBranchAddress("MET_DM_Crack2_sumet", &MET_DM_Crack2_sumet, &b_MET_DM_Crack2_sumet);
	fChain->SetBranchAddress("MET_DM_All_etx", &MET_DM_All_etx, &b_MET_DM_All_etx);
	fChain->SetBranchAddress("MET_DM_All_ety", &MET_DM_All_ety, &b_MET_DM_All_ety);
	fChain->SetBranchAddress("MET_DM_All_phi", &MET_DM_All_phi, &b_MET_DM_All_phi);
	fChain->SetBranchAddress("MET_DM_All_et", &MET_DM_All_et, &b_MET_DM_All_et);
	fChain->SetBranchAddress("MET_DM_All_sumet", &MET_DM_All_sumet, &b_MET_DM_All_sumet);
	fChain->SetBranchAddress("MET_DM_Cryo_etx", &MET_DM_Cryo_etx, &b_MET_DM_Cryo_etx);
	fChain->SetBranchAddress("MET_DM_Cryo_ety", &MET_DM_Cryo_ety, &b_MET_DM_Cryo_ety);
	fChain->SetBranchAddress("MET_DM_Cryo_phi", &MET_DM_Cryo_phi, &b_MET_DM_Cryo_phi);
	fChain->SetBranchAddress("MET_DM_Cryo_et", &MET_DM_Cryo_et, &b_MET_DM_Cryo_et);
	fChain->SetBranchAddress("MET_DM_Cryo_sumet", &MET_DM_Cryo_sumet, &b_MET_DM_Cryo_sumet);
	fChain->SetBranchAddress("METJetsInfo_JetPtWeightedEventEMFraction", &METJetsInfo_JetPtWeightedEventEMFraction, &b_METJetsInfo_JetPtWeightedEventEMFraction);
	fChain->SetBranchAddress("METJetsInfo_JetPtWeightedNumAssociatedTracks", &METJetsInfo_JetPtWeightedNumAssociatedTracks, &b_METJetsInfo_JetPtWeightedNumAssociatedTracks);
	fChain->SetBranchAddress("METJetsInfo_JetPtWeightedSize", &METJetsInfo_JetPtWeightedSize, &b_METJetsInfo_JetPtWeightedSize);
	fChain->SetBranchAddress("METJetsInfo_LeadingJetEt", &METJetsInfo_LeadingJetEt, &b_METJetsInfo_LeadingJetEt);
	fChain->SetBranchAddress("METJetsInfo_LeadingJetEta", &METJetsInfo_LeadingJetEta, &b_METJetsInfo_LeadingJetEta);
	
	fChain->SetBranchAddress("vxp_n", &vxp_n, &b_vxp_n);
	fChain->SetBranchAddress("vxp_x", &vxp_x, &b_vxp_x);
	fChain->SetBranchAddress("vxp_y", &vxp_y, &b_vxp_y);
	fChain->SetBranchAddress("vxp_z", &vxp_z, &b_vxp_z);
	fChain->SetBranchAddress("vxp_cov_x", &vxp_cov_x, &b_vxp_cov_x);
	fChain->SetBranchAddress("vxp_cov_y", &vxp_cov_y, &b_vxp_cov_y);
	fChain->SetBranchAddress("vxp_cov_z", &vxp_cov_z, &b_vxp_cov_z);
	fChain->SetBranchAddress("vxp_chi2", &vxp_chi2, &b_vxp_chi2);
	fChain->SetBranchAddress("vxp_ndof", &vxp_ndof, &b_vxp_ndof);
	fChain->SetBranchAddress("vxp_px", &vxp_px, &b_vxp_px);
	fChain->SetBranchAddress("vxp_py", &vxp_py, &b_vxp_py);
	fChain->SetBranchAddress("vxp_pz", &vxp_pz, &b_vxp_pz);
	fChain->SetBranchAddress("vxp_E", &vxp_E, &b_vxp_E);
	fChain->SetBranchAddress("vxp_m", &vxp_m, &b_vxp_m);
	fChain->SetBranchAddress("vxp_nTracks", &vxp_nTracks, &b_vxp_nTracks);
	fChain->SetBranchAddress("vxp_sumPt", &vxp_sumPt, &b_vxp_sumPt);
	fChain->SetBranchAddress("vxp_type", &vxp_type, &b_vxp_type);
	fChain->SetBranchAddress("vxp_trk_n", &vxp_trk_n, &b_vxp_trk_n);
	fChain->SetBranchAddress("vxp_trk_index", &vxp_trk_index, &b_vxp_trk_index);
	
	if(isMC)
	{
		fChain->SetBranchAddress("muonTruth_n", &muonTruth_n, &b_muonTruth_n);
		fChain->SetBranchAddress("muonTruth_pt", &muonTruth_pt, &b_muonTruth_pt);
		fChain->SetBranchAddress("muonTruth_m", &muonTruth_m, &b_muonTruth_m);
		fChain->SetBranchAddress("muonTruth_eta", &muonTruth_eta, &b_muonTruth_eta);
		fChain->SetBranchAddress("muonTruth_phi", &muonTruth_phi, &b_muonTruth_phi);
		fChain->SetBranchAddress("muonTruth_charge", &muonTruth_charge, &b_muonTruth_charge);
		fChain->SetBranchAddress("muonTruth_PDGID", &muonTruth_PDGID, &b_muonTruth_PDGID);
		fChain->SetBranchAddress("muonTruth_barcode", &muonTruth_barcode, &b_muonTruth_barcode);
		fChain->SetBranchAddress("muonTruth_type", &muonTruth_type, &b_muonTruth_type);
		fChain->SetBranchAddress("muonTruth_origin", &muonTruth_origin, &b_muonTruth_origin);
		
		fChain->SetBranchAddress("mcevt_n", &mcevt_n, &b_mcevt_n);
		fChain->SetBranchAddress("mcevt_signal_process_id", &mcevt_signal_process_id, &b_mcevt_signal_process_id);
		fChain->SetBranchAddress("mcevt_event_number", &mcevt_event_number, &b_mcevt_event_number);
		fChain->SetBranchAddress("mcevt_event_scale", &mcevt_event_scale, &b_mcevt_event_scale);
		fChain->SetBranchAddress("mcevt_alphaQCD", &mcevt_alphaQCD, &b_mcevt_alphaQCD);
		fChain->SetBranchAddress("mcevt_alphaQED", &mcevt_alphaQED, &b_mcevt_alphaQED);
		fChain->SetBranchAddress("mcevt_pdf_id1", &mcevt_pdf_id1, &b_mcevt_pdf_id1);
		fChain->SetBranchAddress("mcevt_pdf_id2", &mcevt_pdf_id2, &b_mcevt_pdf_id2);
		fChain->SetBranchAddress("mcevt_pdf_x1", &mcevt_pdf_x1, &b_mcevt_pdf_x1);
		fChain->SetBranchAddress("mcevt_pdf_x2", &mcevt_pdf_x2, &b_mcevt_pdf_x2);
		fChain->SetBranchAddress("mcevt_pdf_scale", &mcevt_pdf_scale, &b_mcevt_pdf_scale);
		fChain->SetBranchAddress("mcevt_pdf1", &mcevt_pdf1, &b_mcevt_pdf1);
		fChain->SetBranchAddress("mcevt_pdf2", &mcevt_pdf2, &b_mcevt_pdf2);
		fChain->SetBranchAddress("mcevt_weight", &mcevt_weight, &b_mcevt_weight);
		
		fChain->SetBranchAddress("mc_n", &mc_n, &b_mc_n);
		fChain->SetBranchAddress("mc_pt", &mc_pt, &b_mc_pt);
		fChain->SetBranchAddress("mc_m", &mc_m, &b_mc_m);
		fChain->SetBranchAddress("mc_eta", &mc_eta, &b_mc_eta);
		fChain->SetBranchAddress("mc_phi", &mc_phi, &b_mc_phi);
		fChain->SetBranchAddress("mc_status", &mc_status, &b_mc_status);
		fChain->SetBranchAddress("mc_barcode", &mc_barcode, &b_mc_barcode);
		fChain->SetBranchAddress("mc_parents", &mc_parents, &b_mc_parents);
		fChain->SetBranchAddress("mc_children", &mc_children, &b_mc_children);
		fChain->SetBranchAddress("mc_pdgId", &mc_pdgId, &b_mc_pdgId);
		fChain->SetBranchAddress("mc_charge", &mc_charge, &b_mc_charge);
		fChain->SetBranchAddress("mc_vx_x", &mc_vx_x, &b_mc_vx_x);
		fChain->SetBranchAddress("mc_vx_y", &mc_vx_y, &b_mc_vx_y);
		fChain->SetBranchAddress("mc_vx_z", &mc_vx_z, &b_mc_vx_z);
		fChain->SetBranchAddress("mc_child_index", &mc_child_index, &b_mc_child_index);
		fChain->SetBranchAddress("mc_parent_index", &mc_parent_index, &b_mc_parent_index);
	}
	
	fChain->SetBranchAddress("trig_L1_TAV", &trig_L1_TAV, &b_trig_L1_TAV);
	fChain->SetBranchAddress("trig_L2_passedPhysics", &trig_L2_passedPhysics, &b_trig_L2_passedPhysics);
	fChain->SetBranchAddress("trig_EF_passedPhysics", &trig_EF_passedPhysics, &b_trig_EF_passedPhysics);
	fChain->SetBranchAddress("trig_L1_TBP", &trig_L1_TBP, &b_trig_L1_TBP);
	fChain->SetBranchAddress("trig_L1_TAP", &trig_L1_TAP, &b_trig_L1_TAP);
	fChain->SetBranchAddress("trig_L2_passedRaw", &trig_L2_passedRaw, &b_trig_L2_passedRaw);
	fChain->SetBranchAddress("trig_EF_passedRaw", &trig_EF_passedRaw, &b_trig_EF_passedRaw);
	fChain->SetBranchAddress("trig_L2_truncated", &trig_L2_truncated, &b_trig_L2_truncated);
	fChain->SetBranchAddress("trig_EF_truncated", &trig_EF_truncated, &b_trig_EF_truncated);
	fChain->SetBranchAddress("trig_L2_resurrected", &trig_L2_resurrected, &b_trig_L2_resurrected);
	fChain->SetBranchAddress("trig_EF_resurrected", &trig_EF_resurrected, &b_trig_EF_resurrected);
	fChain->SetBranchAddress("trig_L2_passedThrough", &trig_L2_passedThrough, &b_trig_L2_passedThrough);
	fChain->SetBranchAddress("trig_EF_passedThrough", &trig_EF_passedThrough, &b_trig_EF_passedThrough);
	fChain->SetBranchAddress("trig_DB_SMK", &trig_DB_SMK, &b_trig_DB_SMK);
	fChain->SetBranchAddress("trig_DB_L1PSK", &trig_DB_L1PSK, &b_trig_DB_L1PSK);
	fChain->SetBranchAddress("trig_DB_HLTPSK", &trig_DB_HLTPSK, &b_trig_DB_HLTPSK);
	fChain->SetBranchAddress("trig_bgCode", &trig_bgCode, &b_trig_bgCode);
	
	fChain->SetBranchAddress("trig_L1_mu_n", &trig_L1_mu_n, &b_trig_L1_mu_n);
	fChain->SetBranchAddress("trig_L1_mu_pt", &trig_L1_mu_pt, &b_trig_L1_mu_pt);
	fChain->SetBranchAddress("trig_L1_mu_eta", &trig_L1_mu_eta, &b_trig_L1_mu_eta);
	fChain->SetBranchAddress("trig_L1_mu_phi", &trig_L1_mu_phi, &b_trig_L1_mu_phi);
	fChain->SetBranchAddress("trig_L1_mu_thrName", &trig_L1_mu_thrName, &b_trig_L1_mu_thrName);
	fChain->SetBranchAddress("trig_L2_muonfeature_n", &trig_L2_muonfeature_n, &b_trig_L2_muonfeature_n);
	fChain->SetBranchAddress("trig_L2_muonfeature_pt", &trig_L2_muonfeature_pt, &b_trig_L2_muonfeature_pt);
	fChain->SetBranchAddress("trig_L2_muonfeature_eta", &trig_L2_muonfeature_eta, &b_trig_L2_muonfeature_eta);
	fChain->SetBranchAddress("trig_L2_muonfeature_phi", &trig_L2_muonfeature_phi, &b_trig_L2_muonfeature_phi);
	fChain->SetBranchAddress("trig_L2_muonfeaturedetails_n", &trig_L2_muonfeaturedetails_n, &b_trig_L2_muonfeaturedetails_n);
	fChain->SetBranchAddress("trig_L2_combmuonfeature_n", &trig_L2_combmuonfeature_n, &b_trig_L2_combmuonfeature_n);
	fChain->SetBranchAddress("trig_L2_combmuonfeature_pt", &trig_L2_combmuonfeature_pt, &b_trig_L2_combmuonfeature_pt);
	fChain->SetBranchAddress("trig_L2_combmuonfeature_eta", &trig_L2_combmuonfeature_eta, &b_trig_L2_combmuonfeature_eta);
	fChain->SetBranchAddress("trig_L2_combmuonfeature_phi", &trig_L2_combmuonfeature_phi, &b_trig_L2_combmuonfeature_phi);
	fChain->SetBranchAddress("trig_L2_combmuonfeature_idscantrk_index", &trig_L2_combmuonfeature_idscantrk_index, &b_trig_L2_combmuonfeature_idscantrk_index);
	fChain->SetBranchAddress("trig_L2_combmuonfeature_sitracktrk_index", &trig_L2_combmuonfeature_sitracktrk_index, &b_trig_L2_combmuonfeature_sitracktrk_index);
	fChain->SetBranchAddress("trig_L2_isomuonfeature_n", &trig_L2_isomuonfeature_n, &b_trig_L2_isomuonfeature_n);
	fChain->SetBranchAddress("trig_L2_isomuonfeature_pt", &trig_L2_isomuonfeature_pt, &b_trig_L2_isomuonfeature_pt);
	fChain->SetBranchAddress("trig_L2_isomuonfeature_eta", &trig_L2_isomuonfeature_eta, &b_trig_L2_isomuonfeature_eta);
	fChain->SetBranchAddress("trig_L2_isomuonfeature_phi", &trig_L2_isomuonfeature_phi, &b_trig_L2_isomuonfeature_phi);
	fChain->SetBranchAddress("trig_L2_isomuonfeature_EtInnerConeEC ", &trig_L2_isomuonfeature_EtInnerConeEC , &b_trig_L2_isomuonfeature_EtInnerConeEC );
	fChain->SetBranchAddress("trig_L2_isomuonfeature_EtOuterConeEC", &trig_L2_isomuonfeature_EtOuterConeEC, &b_trig_L2_isomuonfeature_EtOuterConeEC);
	fChain->SetBranchAddress("trig_L2_isomuonfeature_EtInnerConeHC", &trig_L2_isomuonfeature_EtInnerConeHC, &b_trig_L2_isomuonfeature_EtInnerConeHC);
	fChain->SetBranchAddress("trig_L2_isomuonfeature_EtOuterConeHC", &trig_L2_isomuonfeature_EtOuterConeHC, &b_trig_L2_isomuonfeature_EtOuterConeHC);
	fChain->SetBranchAddress("trig_L2_isomuonfeature_NTracksCone", &trig_L2_isomuonfeature_NTracksCone, &b_trig_L2_isomuonfeature_NTracksCone);
	fChain->SetBranchAddress("trig_L2_isomuonfeature_SumPtTracksCone", &trig_L2_isomuonfeature_SumPtTracksCone, &b_trig_L2_isomuonfeature_SumPtTracksCone);
	fChain->SetBranchAddress("trig_L2_isomuonfeature_PtMuTracksCone", &trig_L2_isomuonfeature_PtMuTracksCone, &b_trig_L2_isomuonfeature_PtMuTracksCone);
	fChain->SetBranchAddress("trig_L2_tilemufeature_n", &trig_L2_tilemufeature_n, &b_trig_L2_tilemufeature_n);
	fChain->SetBranchAddress("trig_L2_tilemufeature_eta", &trig_L2_tilemufeature_eta, &b_trig_L2_tilemufeature_eta);
	fChain->SetBranchAddress("trig_L2_tilemufeature_phi", &trig_L2_tilemufeature_phi, &b_trig_L2_tilemufeature_phi);
	fChain->SetBranchAddress("trig_L2_tiletrackmufeature_n", &trig_L2_tiletrackmufeature_n, &b_trig_L2_tiletrackmufeature_n);
	fChain->SetBranchAddress("trig_L2_tiletrackmufeature_pt", &trig_L2_tiletrackmufeature_pt, &b_trig_L2_tiletrackmufeature_pt);
	fChain->SetBranchAddress("trig_L2_tiletrackmufeature_eta", &trig_L2_tiletrackmufeature_eta, &b_trig_L2_tiletrackmufeature_eta);
	fChain->SetBranchAddress("trig_L2_tiletrackmufeature_phi", &trig_L2_tiletrackmufeature_phi, &b_trig_L2_tiletrackmufeature_phi);
	fChain->SetBranchAddress("trig_L2_tiletrackmufeature_tilemu_index", &trig_L2_tiletrackmufeature_tilemu_index, &b_trig_L2_tiletrackmufeature_tilemu_index);
	fChain->SetBranchAddress("trig_L2_tiletrackmufeature_idtrk_algorithmId", &trig_L2_tiletrackmufeature_idtrk_algorithmId, &b_trig_L2_tiletrackmufeature_idtrk_algorithmId);
	fChain->SetBranchAddress("trig_L2_tiletrackmufeature_idtrk_trackStatus", &trig_L2_tiletrackmufeature_idtrk_trackStatus, &b_trig_L2_tiletrackmufeature_idtrk_trackStatus);
	fChain->SetBranchAddress("trig_L2_tiletrackmufeature_idtrk_chi2Ndof", &trig_L2_tiletrackmufeature_idtrk_chi2Ndof, &b_trig_L2_tiletrackmufeature_idtrk_chi2Ndof);
	fChain->SetBranchAddress("trig_L2_tiletrackmufeature_idtrk_idtrkfitpar_a0", &trig_L2_tiletrackmufeature_idtrk_idtrkfitpar_a0, &b_trig_L2_tiletrackmufeature_idtrk_idtrkfitpar_a0);
	fChain->SetBranchAddress("trig_L2_tiletrackmufeature_idtrk_idtrkfitpar_z0", &trig_L2_tiletrackmufeature_idtrk_idtrkfitpar_z0, &b_trig_L2_tiletrackmufeature_idtrk_idtrkfitpar_z0);
	fChain->SetBranchAddress("trig_L2_tiletrackmufeature_idtrk_idtrkfitpar_phi0", &trig_L2_tiletrackmufeature_idtrk_idtrkfitpar_phi0, &b_trig_L2_tiletrackmufeature_idtrk_idtrkfitpar_phi0);
	fChain->SetBranchAddress("trig_L2_tiletrackmufeature_idtrk_idtrkfitpar_eta", &trig_L2_tiletrackmufeature_idtrk_idtrkfitpar_eta, &b_trig_L2_tiletrackmufeature_idtrk_idtrkfitpar_eta);
	fChain->SetBranchAddress("trig_L2_tiletrackmufeature_idtrk_idtrkfitpar_pt", &trig_L2_tiletrackmufeature_idtrk_idtrkfitpar_pt, &b_trig_L2_tiletrackmufeature_idtrk_idtrkfitpar_pt);
	fChain->SetBranchAddress("trig_L2_tiletrackmufeature_idtrk_idtrkfitpar_hasidtrkfitpar", &trig_L2_tiletrackmufeature_idtrk_idtrkfitpar_hasidtrkfitpar, &b_trig_L2_tiletrackmufeature_idtrk_idtrkfitpar_hasidtrkfitpar);
	fChain->SetBranchAddress("trig_L2_tiletrackmufeature_idtrk_hasidtrk", &trig_L2_tiletrackmufeature_idtrk_hasidtrk, &b_trig_L2_tiletrackmufeature_idtrk_hasidtrk);
	fChain->SetBranchAddress("trig_EF_trigmuonef_n", &trig_EF_trigmuonef_n, &b_trig_EF_trigmuonef_n);
	fChain->SetBranchAddress("trig_EF_trigmuonef_track_n", &trig_EF_trigmuonef_track_n, &b_trig_EF_trigmuonef_track_n);
	fChain->SetBranchAddress("trig_EF_trigmuonef_track_MuonType", &trig_EF_trigmuonef_track_MuonType, &b_trig_EF_trigmuonef_track_MuonType);
	fChain->SetBranchAddress("trig_EF_trigmuonef_track_MS_pt", &trig_EF_trigmuonef_track_MS_pt, &b_trig_EF_trigmuonef_track_MS_pt);
	fChain->SetBranchAddress("trig_EF_trigmuonef_track_MS_eta", &trig_EF_trigmuonef_track_MS_eta, &b_trig_EF_trigmuonef_track_MS_eta);
	fChain->SetBranchAddress("trig_EF_trigmuonef_track_MS_phi", &trig_EF_trigmuonef_track_MS_phi, &b_trig_EF_trigmuonef_track_MS_phi);
	fChain->SetBranchAddress("trig_EF_trigmuonef_track_MS_hasMS", &trig_EF_trigmuonef_track_MS_hasMS, &b_trig_EF_trigmuonef_track_MS_hasMS);
	fChain->SetBranchAddress("trig_EF_trigmuonef_track_SA_pt", &trig_EF_trigmuonef_track_SA_pt, &b_trig_EF_trigmuonef_track_SA_pt);
	fChain->SetBranchAddress("trig_EF_trigmuonef_track_SA_eta", &trig_EF_trigmuonef_track_SA_eta, &b_trig_EF_trigmuonef_track_SA_eta);
	fChain->SetBranchAddress("trig_EF_trigmuonef_track_SA_phi", &trig_EF_trigmuonef_track_SA_phi, &b_trig_EF_trigmuonef_track_SA_phi);
	fChain->SetBranchAddress("trig_EF_trigmuonef_track_SA_hasSA", &trig_EF_trigmuonef_track_SA_hasSA, &b_trig_EF_trigmuonef_track_SA_hasSA);
	fChain->SetBranchAddress("trig_EF_trigmuonef_track_CB_pt", &trig_EF_trigmuonef_track_CB_pt, &b_trig_EF_trigmuonef_track_CB_pt);
	fChain->SetBranchAddress("trig_EF_trigmuonef_track_CB_eta", &trig_EF_trigmuonef_track_CB_eta, &b_trig_EF_trigmuonef_track_CB_eta);
	fChain->SetBranchAddress("trig_EF_trigmuonef_track_CB_phi", &trig_EF_trigmuonef_track_CB_phi, &b_trig_EF_trigmuonef_track_CB_phi);
	fChain->SetBranchAddress("trig_EF_trigmuonef_track_CB_hasCB", &trig_EF_trigmuonef_track_CB_hasCB, &b_trig_EF_trigmuonef_track_CB_hasCB);
	fChain->SetBranchAddress("trig_EF_trigmugirl_n", &trig_EF_trigmugirl_n, &b_trig_EF_trigmugirl_n);
	fChain->SetBranchAddress("trig_EF_trigmugirl_track_n", &trig_EF_trigmugirl_track_n, &b_trig_EF_trigmugirl_track_n);
	fChain->SetBranchAddress("trig_EF_trigmugirl_track_MuonType", &trig_EF_trigmugirl_track_MuonType, &b_trig_EF_trigmugirl_track_MuonType);
	fChain->SetBranchAddress("trig_EF_trigmugirl_track_MS_pt", &trig_EF_trigmugirl_track_MS_pt, &b_trig_EF_trigmugirl_track_MS_pt);
	fChain->SetBranchAddress("trig_EF_trigmugirl_track_MS_eta", &trig_EF_trigmugirl_track_MS_eta, &b_trig_EF_trigmugirl_track_MS_eta);
	fChain->SetBranchAddress("trig_EF_trigmugirl_track_MS_phi", &trig_EF_trigmugirl_track_MS_phi, &b_trig_EF_trigmugirl_track_MS_phi);
	fChain->SetBranchAddress("trig_EF_trigmugirl_track_MS_hasMS", &trig_EF_trigmugirl_track_MS_hasMS, &b_trig_EF_trigmugirl_track_MS_hasMS);
	fChain->SetBranchAddress("trig_EF_trigmugirl_track_SA_pt", &trig_EF_trigmugirl_track_SA_pt, &b_trig_EF_trigmugirl_track_SA_pt);
	fChain->SetBranchAddress("trig_EF_trigmugirl_track_SA_eta", &trig_EF_trigmugirl_track_SA_eta, &b_trig_EF_trigmugirl_track_SA_eta);
	fChain->SetBranchAddress("trig_EF_trigmugirl_track_SA_phi", &trig_EF_trigmugirl_track_SA_phi, &b_trig_EF_trigmugirl_track_SA_phi);
	fChain->SetBranchAddress("trig_EF_trigmugirl_track_SA_hasSA", &trig_EF_trigmugirl_track_SA_hasSA, &b_trig_EF_trigmugirl_track_SA_hasSA);
	fChain->SetBranchAddress("trig_EF_trigmugirl_track_CB_pt", &trig_EF_trigmugirl_track_CB_pt, &b_trig_EF_trigmugirl_track_CB_pt);
	fChain->SetBranchAddress("trig_EF_trigmugirl_track_CB_eta", &trig_EF_trigmugirl_track_CB_eta, &b_trig_EF_trigmugirl_track_CB_eta);
	fChain->SetBranchAddress("trig_EF_trigmugirl_track_CB_phi", &trig_EF_trigmugirl_track_CB_phi, &b_trig_EF_trigmugirl_track_CB_phi);
	fChain->SetBranchAddress("trig_EF_trigmugirl_track_CB_hasCB", &trig_EF_trigmugirl_track_CB_hasCB, &b_trig_EF_trigmugirl_track_CB_hasCB);
	fChain->SetBranchAddress("trig_L2_sitrack_muon_n", &trig_L2_sitrack_muon_n, &b_trig_L2_sitrack_muon_n);
	fChain->SetBranchAddress("trig_L2_sitrack_muon_algorithmId", &trig_L2_sitrack_muon_algorithmId, &b_trig_L2_sitrack_muon_algorithmId);
	fChain->SetBranchAddress("trig_L2_sitrack_muon_trackStatus", &trig_L2_sitrack_muon_trackStatus, &b_trig_L2_sitrack_muon_trackStatus);
	fChain->SetBranchAddress("trig_L2_sitrack_muon_chi2Ndof", &trig_L2_sitrack_muon_chi2Ndof, &b_trig_L2_sitrack_muon_chi2Ndof);
	fChain->SetBranchAddress("trig_L2_sitrack_muon_a0", &trig_L2_sitrack_muon_a0, &b_trig_L2_sitrack_muon_a0);
	fChain->SetBranchAddress("trig_L2_sitrack_muon_z0", &trig_L2_sitrack_muon_z0, &b_trig_L2_sitrack_muon_z0);
	fChain->SetBranchAddress("trig_L2_sitrack_muon_phi0", &trig_L2_sitrack_muon_phi0, &b_trig_L2_sitrack_muon_phi0);
	fChain->SetBranchAddress("trig_L2_sitrack_muon_eta", &trig_L2_sitrack_muon_eta, &b_trig_L2_sitrack_muon_eta);
	fChain->SetBranchAddress("trig_L2_sitrack_muon_pt", &trig_L2_sitrack_muon_pt, &b_trig_L2_sitrack_muon_pt);
	fChain->SetBranchAddress("trig_L2_idscan_muon_n", &trig_L2_idscan_muon_n, &b_trig_L2_idscan_muon_n);
	fChain->SetBranchAddress("trig_L2_idscan_muon_algorithmId", &trig_L2_idscan_muon_algorithmId, &b_trig_L2_idscan_muon_algorithmId);
	fChain->SetBranchAddress("trig_L2_idscan_muon_trackStatus", &trig_L2_idscan_muon_trackStatus, &b_trig_L2_idscan_muon_trackStatus);
	fChain->SetBranchAddress("trig_L2_idscan_muon_chi2Ndof", &trig_L2_idscan_muon_chi2Ndof, &b_trig_L2_idscan_muon_chi2Ndof);
	fChain->SetBranchAddress("trig_L2_idscan_muon_a0", &trig_L2_idscan_muon_a0, &b_trig_L2_idscan_muon_a0);
	fChain->SetBranchAddress("trig_L2_idscan_muon_z0", &trig_L2_idscan_muon_z0, &b_trig_L2_idscan_muon_z0);
	fChain->SetBranchAddress("trig_L2_idscan_muon_phi0", &trig_L2_idscan_muon_phi0, &b_trig_L2_idscan_muon_phi0);
	fChain->SetBranchAddress("trig_L2_idscan_muon_eta", &trig_L2_idscan_muon_eta, &b_trig_L2_idscan_muon_eta);
	fChain->SetBranchAddress("trig_L2_idscan_muon_pt", &trig_L2_idscan_muon_pt, &b_trig_L2_idscan_muon_pt);
	fChain->SetBranchAddress("trig_L2_sitrack_isomuon_n", &trig_L2_sitrack_isomuon_n, &b_trig_L2_sitrack_isomuon_n);
	fChain->SetBranchAddress("trig_L2_sitrack_isomuon_algorithmId", &trig_L2_sitrack_isomuon_algorithmId, &b_trig_L2_sitrack_isomuon_algorithmId);
	fChain->SetBranchAddress("trig_L2_sitrack_isomuon_trackStatus", &trig_L2_sitrack_isomuon_trackStatus, &b_trig_L2_sitrack_isomuon_trackStatus);
	fChain->SetBranchAddress("trig_L2_sitrack_isomuon_chi2Ndof", &trig_L2_sitrack_isomuon_chi2Ndof, &b_trig_L2_sitrack_isomuon_chi2Ndof);
	fChain->SetBranchAddress("trig_L2_sitrack_isomuon_a0", &trig_L2_sitrack_isomuon_a0, &b_trig_L2_sitrack_isomuon_a0);
	fChain->SetBranchAddress("trig_L2_sitrack_isomuon_z0", &trig_L2_sitrack_isomuon_z0, &b_trig_L2_sitrack_isomuon_z0);
	fChain->SetBranchAddress("trig_L2_sitrack_isomuon_phi0", &trig_L2_sitrack_isomuon_phi0, &b_trig_L2_sitrack_isomuon_phi0);
	fChain->SetBranchAddress("trig_L2_sitrack_isomuon_eta", &trig_L2_sitrack_isomuon_eta, &b_trig_L2_sitrack_isomuon_eta);
	fChain->SetBranchAddress("trig_L2_sitrack_isomuon_pt", &trig_L2_sitrack_isomuon_pt, &b_trig_L2_sitrack_isomuon_pt);
	fChain->SetBranchAddress("trig_L2_idscan_isomuon_n", &trig_L2_idscan_isomuon_n, &b_trig_L2_idscan_isomuon_n);
	fChain->SetBranchAddress("trig_L2_idscan_isomuon_algorithmId", &trig_L2_idscan_isomuon_algorithmId, &b_trig_L2_idscan_isomuon_algorithmId);
	fChain->SetBranchAddress("trig_L2_idscan_isomuon_trackStatus", &trig_L2_idscan_isomuon_trackStatus, &b_trig_L2_idscan_isomuon_trackStatus);
	fChain->SetBranchAddress("trig_L2_idscan_isomuon_chi2Ndof", &trig_L2_idscan_isomuon_chi2Ndof, &b_trig_L2_idscan_isomuon_chi2Ndof);
	fChain->SetBranchAddress("trig_L2_idscan_isomuon_a0", &trig_L2_idscan_isomuon_a0, &b_trig_L2_idscan_isomuon_a0);
	fChain->SetBranchAddress("trig_L2_idscan_isomuon_z0", &trig_L2_idscan_isomuon_z0, &b_trig_L2_idscan_isomuon_z0);
	fChain->SetBranchAddress("trig_L2_idscan_isomuon_phi0", &trig_L2_idscan_isomuon_phi0, &b_trig_L2_idscan_isomuon_phi0);
	fChain->SetBranchAddress("trig_L2_idscan_isomuon_eta", &trig_L2_idscan_isomuon_eta, &b_trig_L2_idscan_isomuon_eta);
	fChain->SetBranchAddress("trig_L2_idscan_isomuon_pt", &trig_L2_idscan_isomuon_pt, &b_trig_L2_idscan_isomuon_pt);
	fChain->SetBranchAddress("trig_RoI_L2_mu_n", &trig_RoI_L2_mu_n, &b_trig_RoI_L2_mu_n);
	fChain->SetBranchAddress("trig_RoI_L2_mu_type", &trig_RoI_L2_mu_type, &b_trig_RoI_L2_mu_type);
	fChain->SetBranchAddress("trig_RoI_L2_mu_lastStep", &trig_RoI_L2_mu_lastStep, &b_trig_RoI_L2_mu_lastStep);
	fChain->SetBranchAddress("trig_RoI_L2_mu_MuonFeature", &trig_RoI_L2_mu_MuonFeature, &b_trig_RoI_L2_mu_MuonFeature);
	fChain->SetBranchAddress("trig_RoI_L2_mu_MuonFeatureStatus", &trig_RoI_L2_mu_MuonFeatureStatus, &b_trig_RoI_L2_mu_MuonFeatureStatus);
	fChain->SetBranchAddress("trig_RoI_L2_mu_MuonFeatureDetails", &trig_RoI_L2_mu_MuonFeatureDetails, &b_trig_RoI_L2_mu_MuonFeatureDetails);
	fChain->SetBranchAddress("trig_RoI_L2_mu_MuonFeatureDetailsStatus", &trig_RoI_L2_mu_MuonFeatureDetailsStatus, &b_trig_RoI_L2_mu_MuonFeatureDetailsStatus);
	fChain->SetBranchAddress("trig_RoI_L2_mu_CombinedMuonFeature", &trig_RoI_L2_mu_CombinedMuonFeature, &b_trig_RoI_L2_mu_CombinedMuonFeature);
	fChain->SetBranchAddress("trig_RoI_L2_mu_CombinedMuonFeatureStatus", &trig_RoI_L2_mu_CombinedMuonFeatureStatus, &b_trig_RoI_L2_mu_CombinedMuonFeatureStatus);
	fChain->SetBranchAddress("trig_RoI_L2_mu_IsoMuonFeature", &trig_RoI_L2_mu_IsoMuonFeature, &b_trig_RoI_L2_mu_IsoMuonFeature);
	fChain->SetBranchAddress("trig_RoI_L2_mu_IsoMuonFeatureStatus", &trig_RoI_L2_mu_IsoMuonFeatureStatus, &b_trig_RoI_L2_mu_IsoMuonFeatureStatus);
	fChain->SetBranchAddress("trig_RoI_L2_mu_Muon_ROI", &trig_RoI_L2_mu_Muon_ROI, &b_trig_RoI_L2_mu_Muon_ROI);
	fChain->SetBranchAddress("trig_RoI_L2_mu_Muon_ROIStatus", &trig_RoI_L2_mu_Muon_ROIStatus, &b_trig_RoI_L2_mu_Muon_ROIStatus);
	fChain->SetBranchAddress("trig_RoI_L2_mu_TrigInDetTrackCollection_TrigSiTrack_Muon", &trig_RoI_L2_mu_TrigInDetTrackCollection_TrigSiTrack_Muon, &b_trig_RoI_L2_mu_TrigInDetTrackCollection_TrigSiTrack_Muon);
	fChain->SetBranchAddress("trig_RoI_L2_mu_TrigInDetTrackCollection_TrigSiTrack_MuonStatus", &trig_RoI_L2_mu_TrigInDetTrackCollection_TrigSiTrack_MuonStatus, &b_trig_RoI_L2_mu_TrigInDetTrackCollection_TrigSiTrack_MuonStatus);
	fChain->SetBranchAddress("trig_RoI_L2_mu_TrigInDetTrackCollection_TrigIDSCAN_Muon", &trig_RoI_L2_mu_TrigInDetTrackCollection_TrigIDSCAN_Muon, &b_trig_RoI_L2_mu_TrigInDetTrackCollection_TrigIDSCAN_Muon);
	fChain->SetBranchAddress("trig_RoI_L2_mu_TrigInDetTrackCollection_TrigIDSCAN_MuonStatus", &trig_RoI_L2_mu_TrigInDetTrackCollection_TrigIDSCAN_MuonStatus, &b_trig_RoI_L2_mu_TrigInDetTrackCollection_TrigIDSCAN_MuonStatus);
	fChain->SetBranchAddress("trig_RoI_L2_mu_TrigInDetTrackCollection_TrigSiTrack_muonIso", &trig_RoI_L2_mu_TrigInDetTrackCollection_TrigSiTrack_muonIso, &b_trig_RoI_L2_mu_TrigInDetTrackCollection_TrigSiTrack_muonIso);
	fChain->SetBranchAddress("trig_RoI_L2_mu_TrigInDetTrackCollection_TrigSiTrack_muonIsoStatus", &trig_RoI_L2_mu_TrigInDetTrackCollection_TrigSiTrack_muonIsoStatus, &b_trig_RoI_L2_mu_TrigInDetTrackCollection_TrigSiTrack_muonIsoStatus);
	fChain->SetBranchAddress("trig_RoI_L2_mu_TrigInDetTrackCollection_TrigIDSCAN_muonIso", &trig_RoI_L2_mu_TrigInDetTrackCollection_TrigIDSCAN_muonIso, &b_trig_RoI_L2_mu_TrigInDetTrackCollection_TrigIDSCAN_muonIso);
	fChain->SetBranchAddress("trig_RoI_L2_mu_TrigInDetTrackCollection_TrigIDSCAN_muonIsoStatus", &trig_RoI_L2_mu_TrigInDetTrackCollection_TrigIDSCAN_muonIsoStatus, &b_trig_RoI_L2_mu_TrigInDetTrackCollection_TrigIDSCAN_muonIsoStatus);
	fChain->SetBranchAddress("trig_RoI_L2_TileMu_n", &trig_RoI_L2_TileMu_n, &b_trig_RoI_L2_TileMu_n);
	fChain->SetBranchAddress("trig_RoI_L2_TileMu_type", &trig_RoI_L2_TileMu_type, &b_trig_RoI_L2_TileMu_type);
	fChain->SetBranchAddress("trig_RoI_L2_TileMu_lastStep", &trig_RoI_L2_TileMu_lastStep, &b_trig_RoI_L2_TileMu_lastStep);
	fChain->SetBranchAddress("trig_RoI_L2_TileMu_TileMuFeature", &trig_RoI_L2_TileMu_TileMuFeature, &b_trig_RoI_L2_TileMu_TileMuFeature);
	fChain->SetBranchAddress("trig_RoI_L2_TileMu_TileMuFeatureStatus", &trig_RoI_L2_TileMu_TileMuFeatureStatus, &b_trig_RoI_L2_TileMu_TileMuFeatureStatus);
	fChain->SetBranchAddress("trig_RoI_L2_TileMu_TileTrackMuFeature", &trig_RoI_L2_TileMu_TileTrackMuFeature, &b_trig_RoI_L2_TileMu_TileTrackMuFeature);
	fChain->SetBranchAddress("trig_RoI_L2_TileMu_TileTrackMuFeatureStatus", &trig_RoI_L2_TileMu_TileTrackMuFeatureStatus, &b_trig_RoI_L2_TileMu_TileTrackMuFeatureStatus);
	fChain->SetBranchAddress("trig_RoI_L2_TileMu_Muon_ROI", &trig_RoI_L2_TileMu_Muon_ROI, &b_trig_RoI_L2_TileMu_Muon_ROI);
	fChain->SetBranchAddress("trig_RoI_L2_TileMu_Muon_ROIStatus", &trig_RoI_L2_TileMu_Muon_ROIStatus, &b_trig_RoI_L2_TileMu_Muon_ROIStatus);
	fChain->SetBranchAddress("trig_RoI_L2_TileMu_TrigInDetTrackCollection_TrigSiTrack_Tile", &trig_RoI_L2_TileMu_TrigInDetTrackCollection_TrigSiTrack_Tile, &b_trig_RoI_L2_TileMu_TrigInDetTrackCollection_TrigSiTrack_Tile);
	fChain->SetBranchAddress("trig_RoI_L2_TileMu_TrigInDetTrackCollection_TrigSiTrack_TileStatus", &trig_RoI_L2_TileMu_TrigInDetTrackCollection_TrigSiTrack_TileStatus, &b_trig_RoI_L2_TileMu_TrigInDetTrackCollection_TrigSiTrack_TileStatus);
	fChain->SetBranchAddress("trig_RoI_L2_TileMu_TrigInDetTrackCollection_TrigIDSCAN_Tile", &trig_RoI_L2_TileMu_TrigInDetTrackCollection_TrigIDSCAN_Tile, &b_trig_RoI_L2_TileMu_TrigInDetTrackCollection_TrigIDSCAN_Tile);
	fChain->SetBranchAddress("trig_RoI_L2_TileMu_TrigInDetTrackCollection_TrigIDSCAN_TileStatus", &trig_RoI_L2_TileMu_TrigInDetTrackCollection_TrigIDSCAN_TileStatus, &b_trig_RoI_L2_TileMu_TrigInDetTrackCollection_TrigIDSCAN_TileStatus);
	fChain->SetBranchAddress("trig_RoI_EF_mu_n", &trig_RoI_EF_mu_n, &b_trig_RoI_EF_mu_n);
	fChain->SetBranchAddress("trig_RoI_EF_mu_type", &trig_RoI_EF_mu_type, &b_trig_RoI_EF_mu_type);
	fChain->SetBranchAddress("trig_RoI_EF_mu_lastStep", &trig_RoI_EF_mu_lastStep, &b_trig_RoI_EF_mu_lastStep);
	fChain->SetBranchAddress("trig_RoI_EF_mu_Muon_ROI", &trig_RoI_EF_mu_Muon_ROI, &b_trig_RoI_EF_mu_Muon_ROI);
	fChain->SetBranchAddress("trig_RoI_EF_mu_Muon_ROIStatus", &trig_RoI_EF_mu_Muon_ROIStatus, &b_trig_RoI_EF_mu_Muon_ROIStatus);
	fChain->SetBranchAddress("trig_RoI_EF_mu_TrackCollection_InDetTrigTrackSlimmer_Muon_EFID", &trig_RoI_EF_mu_TrackCollection_InDetTrigTrackSlimmer_Muon_EFID, &b_trig_RoI_EF_mu_TrackCollection_InDetTrigTrackSlimmer_Muon_EFID);
	fChain->SetBranchAddress("trig_RoI_EF_mu_TrackCollection_InDetTrigTrackSlimmer_Muon_EFIDStatus", &trig_RoI_EF_mu_TrackCollection_InDetTrigTrackSlimmer_Muon_EFIDStatus, &b_trig_RoI_EF_mu_TrackCollection_InDetTrigTrackSlimmer_Muon_EFIDStatus);
	fChain->SetBranchAddress("trig_RoI_EF_mu_TrigMuonEFInfoContainer", &trig_RoI_EF_mu_TrigMuonEFInfoContainer, &b_trig_RoI_EF_mu_TrigMuonEFInfoContainer);
	fChain->SetBranchAddress("trig_RoI_EF_mu_TrigMuonEFInfoContainerStatus", &trig_RoI_EF_mu_TrigMuonEFInfoContainerStatus, &b_trig_RoI_EF_mu_TrigMuonEFInfoContainerStatus);
	fChain->SetBranchAddress("trig_RoI_EF_mu_TrigMuonEFInfoContainer_MuGirl", &trig_RoI_EF_mu_TrigMuonEFInfoContainer_MuGirl, &b_trig_RoI_EF_mu_TrigMuonEFInfoContainer_MuGirl);
	fChain->SetBranchAddress("trig_RoI_EF_mu_TrigMuonEFInfoContainer_MuGirlStatus", &trig_RoI_EF_mu_TrigMuonEFInfoContainer_MuGirlStatus, &b_trig_RoI_EF_mu_TrigMuonEFInfoContainer_MuGirlStatus);
	fChain->SetBranchAddress("trig_RoI_EF_mu_TrigMuonEFInfoContainer_MuTagIMO_EF", &trig_RoI_EF_mu_TrigMuonEFInfoContainer_MuTagIMO_EF, &b_trig_RoI_EF_mu_TrigMuonEFInfoContainer_MuTagIMO_EF);
	fChain->SetBranchAddress("trig_RoI_EF_mu_TrigMuonEFInfoContainer_MuTagIMO_EFStatus", &trig_RoI_EF_mu_TrigMuonEFInfoContainer_MuTagIMO_EFStatus, &b_trig_RoI_EF_mu_TrigMuonEFInfoContainer_MuTagIMO_EFStatus);
	fChain->SetBranchAddress("trig_RoI_EF_TileMu_n", &trig_RoI_EF_TileMu_n, &b_trig_RoI_EF_TileMu_n);
	fChain->SetBranchAddress("trig_RoI_EF_TileMu_type", &trig_RoI_EF_TileMu_type, &b_trig_RoI_EF_TileMu_type);
	fChain->SetBranchAddress("trig_RoI_EF_TileMu_lastStep", &trig_RoI_EF_TileMu_lastStep, &b_trig_RoI_EF_TileMu_lastStep);
	fChain->SetBranchAddress("trig_RoI_EF_TileMu_Muon_ROI", &trig_RoI_EF_TileMu_Muon_ROI, &b_trig_RoI_EF_TileMu_Muon_ROI);
	fChain->SetBranchAddress("trig_RoI_EF_TileMu_Muon_ROIStatus", &trig_RoI_EF_TileMu_Muon_ROIStatus, &b_trig_RoI_EF_TileMu_Muon_ROIStatus);
	fChain->SetBranchAddress("trig_RoI_EF_TileMu_TrigMuonEFContainer", &trig_RoI_EF_TileMu_TrigMuonEFContainer, &b_trig_RoI_EF_TileMu_TrigMuonEFContainer);
	fChain->SetBranchAddress("trig_RoI_EF_TileMu_TrigMuonEFContainerStatus", &trig_RoI_EF_TileMu_TrigMuonEFContainerStatus, &b_trig_RoI_EF_TileMu_TrigMuonEFContainerStatus);
	fChain->SetBranchAddress("trig_RoI_EF_TileMu_TrigMuonEFInfoContainer", &trig_RoI_EF_TileMu_TrigMuonEFInfoContainer, &b_trig_RoI_EF_TileMu_TrigMuonEFInfoContainer);
	fChain->SetBranchAddress("trig_RoI_EF_TileMu_TrigMuonEFInfoContainerStatus", &trig_RoI_EF_TileMu_TrigMuonEFInfoContainerStatus, &b_trig_RoI_EF_TileMu_TrigMuonEFInfoContainerStatus);
	fChain->SetBranchAddress("trig_RoI_EF_TileMu_TrigMuonEFInfoContainer_MuGirl", &trig_RoI_EF_TileMu_TrigMuonEFInfoContainer_MuGirl, &b_trig_RoI_EF_TileMu_TrigMuonEFInfoContainer_MuGirl);
	fChain->SetBranchAddress("trig_RoI_EF_TileMu_TrigMuonEFInfoContainer_MuGirlStatus", &trig_RoI_EF_TileMu_TrigMuonEFInfoContainer_MuGirlStatus, &b_trig_RoI_EF_TileMu_TrigMuonEFInfoContainer_MuGirlStatus);
	fChain->SetBranchAddress("trig_RoI_EF_TileMu_TrigMuonEFInfoContainer_MuTagIMO_EF", &trig_RoI_EF_TileMu_TrigMuonEFInfoContainer_MuTagIMO_EF, &b_trig_RoI_EF_TileMu_TrigMuonEFInfoContainer_MuTagIMO_EF);
	fChain->SetBranchAddress("trig_RoI_EF_TileMu_TrigMuonEFInfoContainer_MuTagIMO_EFStatus", &trig_RoI_EF_TileMu_TrigMuonEFInfoContainer_MuTagIMO_EFStatus, &b_trig_RoI_EF_TileMu_TrigMuonEFInfoContainer_MuTagIMO_EFStatus);
	
	fChain->SetBranchAddress("trig_L2_met_MEx", &trig_L2_met_MEx, &b_trig_L2_met_MEx);
	fChain->SetBranchAddress("trig_L2_met_MEy", &trig_L2_met_MEy, &b_trig_L2_met_MEy);
	fChain->SetBranchAddress("trig_L2_met_MEz", &trig_L2_met_MEz, &b_trig_L2_met_MEz);
	fChain->SetBranchAddress("trig_L2_met_sumEt", &trig_L2_met_sumEt, &b_trig_L2_met_sumEt);
	fChain->SetBranchAddress("trig_L2_met_sumE", &trig_L2_met_sumE, &b_trig_L2_met_sumE);
	fChain->SetBranchAddress("trig_L2_met_flag", &trig_L2_met_flag, &b_trig_L2_met_flag);
	fChain->SetBranchAddress("trig_L2_met_nameOfComponent", &trig_L2_met_nameOfComponent, &b_trig_L2_met_nameOfComponent);
	fChain->SetBranchAddress("trig_L2_met_MExComponent", &trig_L2_met_MExComponent, &b_trig_L2_met_MExComponent);
	fChain->SetBranchAddress("trig_L2_met_MEyComponent", &trig_L2_met_MEyComponent, &b_trig_L2_met_MEyComponent);
	fChain->SetBranchAddress("trig_L2_met_MEzComponent", &trig_L2_met_MEzComponent, &b_trig_L2_met_MEzComponent);
	fChain->SetBranchAddress("trig_L2_met_sumEtComponent", &trig_L2_met_sumEtComponent, &b_trig_L2_met_sumEtComponent);
	fChain->SetBranchAddress("trig_L2_met_sumEComponent", &trig_L2_met_sumEComponent, &b_trig_L2_met_sumEComponent);
	fChain->SetBranchAddress("trig_L2_met_componentCalib0", &trig_L2_met_componentCalib0, &b_trig_L2_met_componentCalib0);
	fChain->SetBranchAddress("trig_L2_met_componentCalib1", &trig_L2_met_componentCalib1, &b_trig_L2_met_componentCalib1);
	fChain->SetBranchAddress("trig_L2_met_sumOfSigns", &trig_L2_met_sumOfSigns, &b_trig_L2_met_sumOfSigns);
	fChain->SetBranchAddress("trig_L2_met_usedChannels", &trig_L2_met_usedChannels, &b_trig_L2_met_usedChannels);
	fChain->SetBranchAddress("trig_L2_met_status", &trig_L2_met_status, &b_trig_L2_met_status);
	fChain->SetBranchAddress("trig_EF_met_MEx", &trig_EF_met_MEx, &b_trig_EF_met_MEx);
	fChain->SetBranchAddress("trig_EF_met_MEy", &trig_EF_met_MEy, &b_trig_EF_met_MEy);
	fChain->SetBranchAddress("trig_EF_met_MEz", &trig_EF_met_MEz, &b_trig_EF_met_MEz);
	fChain->SetBranchAddress("trig_EF_met_sumEt", &trig_EF_met_sumEt, &b_trig_EF_met_sumEt);
	fChain->SetBranchAddress("trig_EF_met_sumE", &trig_EF_met_sumE, &b_trig_EF_met_sumE);
	fChain->SetBranchAddress("trig_EF_met_flag", &trig_EF_met_flag, &b_trig_EF_met_flag);
	fChain->SetBranchAddress("trig_EF_met_nameOfComponent", &trig_EF_met_nameOfComponent, &b_trig_EF_met_nameOfComponent);
	fChain->SetBranchAddress("trig_EF_met_MExComponent", &trig_EF_met_MExComponent, &b_trig_EF_met_MExComponent);
	fChain->SetBranchAddress("trig_EF_met_MEyComponent", &trig_EF_met_MEyComponent, &b_trig_EF_met_MEyComponent);
	fChain->SetBranchAddress("trig_EF_met_MEzComponent", &trig_EF_met_MEzComponent, &b_trig_EF_met_MEzComponent);
	fChain->SetBranchAddress("trig_EF_met_sumEtComponent", &trig_EF_met_sumEtComponent, &b_trig_EF_met_sumEtComponent);
	fChain->SetBranchAddress("trig_EF_met_sumEComponent", &trig_EF_met_sumEComponent, &b_trig_EF_met_sumEComponent);
	fChain->SetBranchAddress("trig_EF_met_componentCalib0", &trig_EF_met_componentCalib0, &b_trig_EF_met_componentCalib0);
	fChain->SetBranchAddress("trig_EF_met_componentCalib1", &trig_EF_met_componentCalib1, &b_trig_EF_met_componentCalib1);
	fChain->SetBranchAddress("trig_EF_met_sumOfSigns", &trig_EF_met_sumOfSigns, &b_trig_EF_met_sumOfSigns);
	fChain->SetBranchAddress("trig_EF_met_usedChannels", &trig_EF_met_usedChannels, &b_trig_EF_met_usedChannels);
	fChain->SetBranchAddress("trig_EF_met_status", &trig_EF_met_status, &b_trig_EF_met_status);

	Notify();
}

Bool_t WZphysD3PD::Notify()
{
	// The Notify() function is called when a new file is opened. This
	// can be either for a new TTree in a TChain or when when a new TTree
	// is started when using PROOF. It is normally not necessary to make changes
	// to the generated code, but the routine can be extended by the
	// user if needed. The return value is currently not used.

	return kTRUE;
}

void WZphysD3PD::Show(Long64_t entry)
{
	// Print contents of entry.
	// If entry is not specified, print current entry
	if (!fChain) return;
	fChain->Show(entry);
}
Int_t WZphysD3PD::Cut(Long64_t entry)
{
	if(false) cout << "entry = " << entry << endl;
	// This function may be called from Loop.
	// returns  1 if entry is accepted.
	// returns -1 otherwise.
	return 1;
}
#endif // #ifdef WZphysD3PD_cxx
