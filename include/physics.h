//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Oct 31 18:56:09 2010 by ROOT version 5.27/02
// from TTree physics/physics
// found on file: group10.phys-sm.03672_002223.D3PD._00022.root
//////////////////////////////////////////////////////////

#ifndef physics_h
#define physics_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class physics {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

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
   Int_t           lar_ncellA;
   Int_t           lar_ncellC;
   Float_t         lar_energyA;
   Float_t         lar_energyC;
   Float_t         lar_timeA;
   Float_t         lar_timeC;
   Float_t         lar_timeDiff;
   Int_t           el_n;
   vector<float>   *el_E;
   vector<float>   *el_Et;
   vector<float>   *el_pt;
   vector<float>   *el_m;
   vector<float>   *el_eta;
   vector<float>   *el_phi;
   vector<float>   *el_px;
   vector<float>   *el_py;
   vector<float>   *el_pz;
   vector<float>   *el_charge;
   vector<int>     *el_author;
   vector<unsigned int> *el_isEM;
   vector<int>     *el_convFlag;
   vector<int>     *el_isConv;
   vector<int>     *el_nConv;
   vector<int>     *el_nSingleTrackConv;
   vector<int>     *el_nDoubleTrackConv;
   vector<int>     *el_loose;
   vector<int>     *el_medium;
   vector<int>     *el_mediumIso;
   vector<int>     *el_tight;
   vector<int>     *el_tightIso;
   vector<float>   *el_Ethad;
   vector<float>   *el_Ethad1;
   vector<float>   *el_f1;
   vector<float>   *el_f1core;
   vector<float>   *el_Emins1;
   vector<float>   *el_fside;
   vector<float>   *el_Emax2;
   vector<float>   *el_ws3;
   vector<float>   *el_wstot;
   vector<float>   *el_emaxs1;
   vector<float>   *el_deltaEs;
   vector<float>   *el_E233;
   vector<float>   *el_E237;
   vector<float>   *el_E277;
   vector<float>   *el_weta2;
   vector<float>   *el_f3;
   vector<float>   *el_f3core;
   vector<float>   *el_rphiallcalo;
   vector<float>   *el_Etcone45;
   vector<float>   *el_Etcone20;
   vector<float>   *el_Etcone30;
   vector<float>   *el_Etcone40;
   vector<float>   *el_ptcone30;
   vector<float>   *el_convanglematch;
   vector<float>   *el_convtrackmatch;
   vector<int>     *el_hasconv;
   vector<float>   *el_convvtxx;
   vector<float>   *el_convvtxy;
   vector<float>   *el_convvtxz;
   vector<float>   *el_Rconv;
   vector<float>   *el_zconv;
   vector<float>   *el_convvtxchi2;
   vector<float>   *el_pt1conv;
   vector<int>     *el_convtrk1nBLHits;
   vector<int>     *el_convtrk1nPixHits;
   vector<int>     *el_convtrk1nSCTHits;
   vector<int>     *el_convtrk1nTRTHits;
   vector<float>   *el_pt2conv;
   vector<int>     *el_convtrk2nBLHits;
   vector<int>     *el_convtrk2nPixHits;
   vector<int>     *el_convtrk2nSCTHits;
   vector<int>     *el_convtrk2nTRTHits;
   vector<float>   *el_ptconv;
   vector<float>   *el_pzconv;
   vector<float>   *el_pos7;
   vector<float>   *el_etacorrmag;
   vector<float>   *el_deltaeta1;
   vector<float>   *el_deltaeta2;
   vector<float>   *el_deltaphi2;
   vector<float>   *el_deltaphiRescaled;
   vector<float>   *el_expectHitInBLayer;
   vector<float>   *el_reta;
   vector<float>   *el_rphi;
   vector<float>   *el_EtringnoisedR03sig2;
   vector<float>   *el_EtringnoisedR03sig3;
   vector<float>   *el_EtringnoisedR03sig4;
   vector<double>  *el_isolationlikelihoodjets;
   vector<double>  *el_isolationlikelihoodhqelectrons;
   vector<double>  *el_electronweight;
   vector<double>  *el_electronbgweight;
   vector<double>  *el_softeweight;
   vector<double>  *el_softebgweight;
   vector<double>  *el_neuralnet;
   vector<double>  *el_Hmatrix;
   vector<double>  *el_Hmatrix5;
   vector<double>  *el_adaboost;
   vector<double>  *el_softeneuralnet;
   vector<float>   *el_zvertex;
   vector<float>   *el_errz;
   vector<float>   *el_etap;
   vector<float>   *el_depth;
   vector<float>   *el_breminvpt;
   vector<float>   *el_bremradius;
   vector<float>   *el_bremx;
   vector<float>   *el_bremclusterradius;
   vector<float>   *el_breminvpterr;
   vector<float>   *el_bremtrackauthor;
   vector<float>   *el_hasbrem;
   vector<float>   *el_bremdeltaqoverp;
   vector<float>   *el_bremmaterialtraversed;
   vector<float>   *el_refittedtrackqoverp;
   vector<float>   *el_refittedtrackd0;
   vector<float>   *el_refittedtrackz0;
   vector<float>   *el_refittedtracktheta;
   vector<float>   *el_refittedtrackphi;
   vector<float>   *el_Es0;
   vector<float>   *el_etas0;
   vector<float>   *el_phis0;
   vector<float>   *el_Es1;
   vector<float>   *el_etas1;
   vector<float>   *el_phis1;
   vector<float>   *el_Es2;
   vector<float>   *el_etas2;
   vector<float>   *el_phis2;
   vector<float>   *el_Es3;
   vector<float>   *el_etas3;
   vector<float>   *el_phis3;
   vector<float>   *el_E_PreSamplerB;
   vector<float>   *el_E_EMB1;
   vector<float>   *el_E_EMB2;
   vector<float>   *el_E_EMB3;
   vector<float>   *el_E_PreSamplerE;
   vector<float>   *el_E_EME1;
   vector<float>   *el_E_EME2;
   vector<float>   *el_E_EME3;
   vector<float>   *el_E_HEC0;
   vector<float>   *el_E_HEC1;
   vector<float>   *el_E_HEC2;
   vector<float>   *el_E_HEC3;
   vector<float>   *el_E_TileBar0;
   vector<float>   *el_E_TileBar1;
   vector<float>   *el_E_TileBar2;
   vector<float>   *el_E_TileGap1;
   vector<float>   *el_E_TileGap2;
   vector<float>   *el_E_TileGap3;
   vector<float>   *el_E_TileExt0;
   vector<float>   *el_E_TileExt1;
   vector<float>   *el_E_TileExt2;
   vector<float>   *el_E_FCAL0;
   vector<float>   *el_E_FCAL1;
   vector<float>   *el_E_FCAL2;
   vector<float>   *el_cl_E;
   vector<float>   *el_cl_pt;
   vector<float>   *el_cl_eta;
   vector<float>   *el_cl_phi;
   vector<float>   *el_firstEdens;
   vector<float>   *el_cellmaxfrac;
   vector<float>   *el_longitudinal;
   vector<float>   *el_secondlambda;
   vector<float>   *el_lateral;
   vector<float>   *el_secondR;
   vector<float>   *el_centerlambda;
   vector<float>   *el_rawcl_Es0;
   vector<float>   *el_rawcl_etas0;
   vector<float>   *el_rawcl_phis0;
   vector<float>   *el_rawcl_Es1;
   vector<float>   *el_rawcl_etas1;
   vector<float>   *el_rawcl_phis1;
   vector<float>   *el_rawcl_Es2;
   vector<float>   *el_rawcl_etas2;
   vector<float>   *el_rawcl_phis2;
   vector<float>   *el_rawcl_Es3;
   vector<float>   *el_rawcl_etas3;
   vector<float>   *el_rawcl_phis3;
   vector<float>   *el_rawcl_E;
   vector<float>   *el_rawcl_pt;
   vector<float>   *el_rawcl_eta;
   vector<float>   *el_rawcl_phi;
   vector<float>   *el_refittedtrackcovd0;
   vector<float>   *el_refittedtrackcovz0;
   vector<float>   *el_refittedtrackcovphi;
   vector<float>   *el_refittedtrackcovtheta;
   vector<float>   *el_refittedtrackcovqoverp;
   vector<float>   *el_refittedtrackcovd0z0;
   vector<float>   *el_refittedtrackcovz0phi;
   vector<float>   *el_refittedtrackcovz0theta;
   vector<float>   *el_refittedtrackcovz0qoverp;
   vector<float>   *el_refittedtrackcovd0phi;
   vector<float>   *el_refittedtrackcovd0theta;
   vector<float>   *el_refittedtrackcovd0qoverp;
   vector<float>   *el_refittedtrackcovphitheta;
   vector<float>   *el_refittedtrackcovphiqoverp;
   vector<float>   *el_refittedtrackcovthetaqoverp;
   vector<float>   *el_trackd0;
   vector<float>   *el_trackz0;
   vector<float>   *el_trackphi;
   vector<float>   *el_tracktheta;
   vector<float>   *el_trackqoverp;
   vector<float>   *el_trackpt;
   vector<float>   *el_tracketa;
   vector<float>   *el_trackcov_d0;
   vector<float>   *el_trackcov_z0;
   vector<float>   *el_trackcov_phi;
   vector<float>   *el_trackcov_theta;
   vector<float>   *el_trackcov_qoverp;
   vector<float>   *el_trackcov_d0_z0;
   vector<float>   *el_trackcov_d0_phi;
   vector<float>   *el_trackcov_d0_theta;
   vector<float>   *el_trackcov_d0_qoverp;
   vector<float>   *el_trackcov_z0_phi;
   vector<float>   *el_trackcov_z0_theta;
   vector<float>   *el_trackcov_z0_qoverp;
   vector<float>   *el_trackcov_phi_theta;
   vector<float>   *el_trackcov_phi_qoverp;
   vector<float>   *el_trackcov_theta_qoverp;
   vector<float>   *el_trackfitchi2;
   vector<int>     *el_trackfitndof;
   vector<int>     *el_nBLHits;
   vector<int>     *el_nPixHits;
   vector<int>     *el_nSCTHits;
   vector<int>     *el_nTRTHits;
   vector<int>     *el_nPixHoles;
   vector<int>     *el_nSCTHoles;
   vector<int>     *el_nBLSharedHits;
   vector<int>     *el_nPixSharedHits;
   vector<int>     *el_nSCTSharedHits;
   vector<int>     *el_nTRTHighTHits;
   vector<int>     *el_nTRTOutliers;
   vector<int>     *el_nTRTHighTOutliers;
   vector<int>     *el_nSiHits;
   vector<float>   *el_TRTHighTHitsRatio;
   vector<float>   *el_pixeldEdx;
   vector<float>   *el_eProbabilityComb;
   vector<float>   *el_eProbabilityHT;
   vector<float>   *el_eProbabilityToT;
   vector<float>   *el_eProbabilityBrem;
   vector<float>   *el_vertx;
   vector<float>   *el_verty;
   vector<float>   *el_vertz;
   vector<int>     *el_hastrack;
   vector<float>   *el_deltaEmax2;
   vector<float>   *el_trackd0beam;
   vector<float>   *el_tracksigd0beam;
   vector<float>   *el_trackd0pv;
   vector<float>   *el_tracksigd0pv;
   vector<float>   *el_trackz0pv;
   vector<float>   *el_tracksigz0pv;
   vector<float>   *el_trackd0pvunbiased;
   vector<float>   *el_tracksigd0pvunbiased;
   vector<float>   *el_trackz0pvunbiased;
   vector<float>   *el_tracksigz0pvunbiased;
   vector<int>     *el_jetcone_n;
   vector<vector<float> > *el_jetcone_dr;
   vector<vector<float> > *el_jetcone_signedIP;
   vector<vector<float> > *el_jetcone_ptrel;
   vector<vector<int> > *el_jetcone_index;
   vector<vector<float> > *el_jetcone_E;
   vector<vector<float> > *el_jetcone_pt;
   vector<vector<float> > *el_jetcone_m;
   vector<vector<float> > *el_jetcone_eta;
   vector<vector<float> > *el_jetcone_phi;
   vector<unsigned int> *el_isIso;
   vector<float>   *el_jet_dr;
   vector<float>   *el_jet_E;
   vector<float>   *el_jet_pt;
   vector<float>   *el_jet_m;
   vector<float>   *el_jet_eta;
   vector<float>   *el_jet_phi;
   vector<int>     *el_jet_matched;
   vector<float>   *el_Etcone40_pt_corrected;
   vector<float>   *el_Etcone40_ED_corrected;
   vector<float>   *el_Etcone40_corrected;
   vector<float>   *el_EF_dr;
   vector<int>     *el_EF_index;
   vector<float>   *el_L2_dr;
   vector<int>     *el_L2_index;
   vector<float>   *el_L1_dr;
   vector<int>     *el_L1_index;
   vector<float>   *el_EF_E;
   vector<float>   *el_EF_Et;
   vector<float>   *el_EF_pt;
   vector<float>   *el_EF_eta;
   vector<float>   *el_EF_phi;
   vector<float>   *el_EF_charge;
   vector<float>   *el_EF_Ethad;
   vector<float>   *el_EF_Ethad1;
   vector<float>   *el_EF_f1;
   vector<float>   *el_EF_Emins1;
   vector<float>   *el_EF_fside;
   vector<float>   *el_EF_Emax2;
   vector<float>   *el_EF_ws3;
   vector<float>   *el_EF_wstot;
   vector<float>   *el_EF_E233;
   vector<float>   *el_EF_E237;
   vector<float>   *el_EF_E277;
   vector<float>   *el_EF_weta2;
   vector<float>   *el_EF_rphiallcalo;
   vector<float>   *el_EF_deltaeta1;
   vector<float>   *el_EF_deltaeta2;
   vector<float>   *el_EF_deltaphi2;
   vector<float>   *el_EF_expectHitInBLayer;
   vector<float>   *el_EF_Etcone45;
   vector<float>   *el_EF_Etcone20;
   vector<float>   *el_EF_Etcone30;
   vector<float>   *el_EF_Etcone40;
   vector<float>   *el_EF_etacorrmag;
   vector<float>   *el_EF_zvertex;
   vector<float>   *el_EF_errz;
   vector<float>   *el_EF_trackd0;
   vector<float>   *el_EF_trackz0;
   vector<float>   *el_EF_trackphi;
   vector<float>   *el_EF_tracktheta;
   vector<float>   *el_EF_trackqoverp;
   vector<float>   *el_EF_trackpt;
   vector<float>   *el_EF_tracketa;
   vector<int>     *el_EF_nBLHits;
   vector<int>     *el_EF_nPixHits;
   vector<int>     *el_EF_nSCTHits;
   vector<int>     *el_EF_nTRTHits;
   vector<int>     *el_EF_nTRTHighTHits;
   vector<int>     *el_EF_nSiHits;
   vector<float>   *el_EF_TRTHighTHitsRatio;
   vector<float>   *el_EF_pixeldEdx;
   vector<int>     *el_EF_hastrack;
   vector<int>     *el_EF_matched;
   vector<float>   *el_L2_E;
   vector<float>   *el_L2_Et;
   vector<float>   *el_L2_pt;
   vector<float>   *el_L2_eta;
   vector<float>   *el_L2_phi;
   vector<float>   *el_L2_charge;
   vector<float>   *el_L2_Ethad1;
   vector<float>   *el_L2_reta;
   vector<float>   *el_L2_Eratio;
   vector<float>   *el_L2_trackclusterdeta;
   vector<float>   *el_L2_trackclusterdphi;
   vector<float>   *el_L2_Etoverpt;
   vector<float>   *el_L2_trackpt;
   vector<int>     *el_L2_trackalgo;
   vector<float>   *el_L2_tracketa;
   vector<float>   *el_L2_trackd0;
   vector<float>   *el_L2_trackz0;
   vector<float>   *el_L2_tracktheta;
   vector<float>   *el_L2_trackphi;
   vector<float>   *el_L2_tracketaatcalo;
   vector<float>   *el_L2_trackphiatcalo;
   vector<float>   *el_L2_errpt;
   vector<float>   *el_L2_erreta;
   vector<float>   *el_L2_errphi;
   vector<float>   *el_L2_E237;
   vector<float>   *el_L2_E277;
   vector<float>   *el_L2_fside;
   vector<float>   *el_L2_weta2;
   vector<float>   *el_L2_Emaxs1;
   vector<float>   *el_L2_Emax2;
   vector<int>     *el_L2_matched;
   vector<float>   *el_L1_eta;
   vector<float>   *el_L1_phi;
   vector<float>   *el_L1_EMisol;
   vector<float>   *el_L1_hadisol;
   vector<float>   *el_L1_hadcore;
   vector<float>   *el_L1_pt;
   vector<float>   *el_L1_Et;
   vector<int>     *el_L1_matched;
   Bool_t          EF_2e10_loose;
   Bool_t          EF_2e10_medium;
   Bool_t          EF_2e15_loose;
   Bool_t          EF_2e3_loose;
   Bool_t          EF_2e3_loose_SiTrk;
   Bool_t          EF_2e3_loose_TRT;
   Bool_t          EF_2e3_medium;
   Bool_t          EF_2e3_medium_SiTrk;
   Bool_t          EF_2e3_medium_TRT;
   Bool_t          EF_2e3_tight;
   Bool_t          EF_2e5_medium;
   Bool_t          EF_2e5_medium_SiTrk;
   Bool_t          EF_2e5_medium_TRT;
   Bool_t          EF_2e5_tight;
   Bool_t          EF_2g10_loose;
   Bool_t          EF_2g15_loose;
   Bool_t          EF_2g5_loose;
   Bool_t          EF_2g7_loose;
   Bool_t          EF_2j20_deta3_5_jetNoEF;
   Bool_t          EF_2j20_deta5_jetNoEF;
   Bool_t          EF_2j20_jetNoEF;
   Bool_t          EF_2j25_j45_anymct100_NoEF;
   Bool_t          EF_2j25_j45_anymct150_NoEF;
   Bool_t          EF_2j25_j45_anymct175_NoEF;
   Bool_t          EF_2j25_j45_dphi03_NoEF;
   Bool_t          EF_2j25_j45_leadingmct100_NoEF;
   Bool_t          EF_2j25_j45_leadingmct150_NoEF;
   Bool_t          EF_2j25_j45_leadingmct175_NoEF;
   Bool_t          EF_2j25_j70_anymct150_NoEF;
   Bool_t          EF_2j25_j70_anymct175_NoEF;
   Bool_t          EF_2j25_j70_dphi03_NoEF;
   Bool_t          EF_2j25_j70_leadingmct150_NoEF;
   Bool_t          EF_2j25_j70_leadingmct175_NoEF;
   Bool_t          EF_2j30_anymct100_NoEF;
   Bool_t          EF_2j30_anymct150_NoEF;
   Bool_t          EF_2j30_anymct175_NoEF;
   Bool_t          EF_2j30_deta3_5_jetNoEF;
   Bool_t          EF_2j30_j90_dphi03_NoEF;
   Bool_t          EF_2j30_jetNoEF;
   Bool_t          EF_2j30_leadingmct100_NoEF;
   Bool_t          EF_2j30_leadingmct150_NoEF;
   Bool_t          EF_2j30_leadingmct175_NoEF;
   Bool_t          EF_2j35_deta3_5_jetNoEF;
   Bool_t          EF_2j35_jetNoEF;
   Bool_t          EF_2j35_jetNoEF_xe20_noMu;
   Bool_t          EF_2j35_jetNoEF_xe30_noMu;
   Bool_t          EF_2j35_jetNoEF_xe40_noMu;
   Bool_t          EF_2j50_jetNoEF;
   Bool_t          EF_2j75_jetNoEF;
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
   Bool_t          EF_2mu4_Upsimumu;
   Bool_t          EF_2mu6;
   Bool_t          EF_2mu6_MG;
   Bool_t          EF_2mu6_NoAlg;
   Bool_t          EF_3j20_j50_jetNoEF;
   Bool_t          EF_3j30_2j50_jetNoEF;
   Bool_t          EF_3j30_jetNoEF;
   Bool_t          EF_3j35_jetNoEF;
   Bool_t          EF_3j50_jetNoEF;
   Bool_t          EF_4j20_j35_jetNoEF;
   Bool_t          EF_4j20_j50_jetNoEF;
   Bool_t          EF_4j30_3j35_jetNoEF;
   Bool_t          EF_4j30_jetNoEF;
   Bool_t          EF_4j35_jetNoEF;
   Bool_t          EF_4j50_jetNoEF;
   Bool_t          EF_5j30_jetNoEF;
   Bool_t          EF_6j30_jetNoEF;
   Bool_t          EF_e10_NoCut;
   Bool_t          EF_e10_loose;
   Bool_t          EF_e10_loose_mu10;
   Bool_t          EF_e10_loose_mu6;
   Bool_t          EF_e10_medium;
   Bool_t          EF_e10_medium_IDTrkNoCut;
   Bool_t          EF_e10_medium_SiTrk;
   Bool_t          EF_e10_medium_TRT;
   Bool_t          EF_e10_tight;
   Bool_t          EF_e15_loose;
   Bool_t          EF_e15_loose_IDTrkNoCut;
   Bool_t          EF_e15_medium;
   Bool_t          EF_e15_medium_SiTrk;
   Bool_t          EF_e15_medium_TRT;
   Bool_t          EF_e15_tight;
   Bool_t          EF_e18_medium;
   Bool_t          EF_e20_loose;
   Bool_t          EF_e20_loose_IDTrkNoCut;
   Bool_t          EF_e20_loose_passEF;
   Bool_t          EF_e20_loose_passL2;
   Bool_t          EF_e20_loose_xe20_noMu;
   Bool_t          EF_e20_loose_xe30_noMu;
   Bool_t          EF_e20_medium;
   Bool_t          EF_e25_loose;
   Bool_t          EF_e30_loose;
   Bool_t          EF_e3_loose;
   Bool_t          EF_e3_loose_SiTrk;
   Bool_t          EF_e3_loose_TRT;
   Bool_t          EF_e3_medium;
   Bool_t          EF_e3_medium_SiTrk;
   Bool_t          EF_e3_medium_TRT;
   Bool_t          EF_e5_NoCut_firstempty;
   Bool_t          EF_e5_medium;
   Bool_t          EF_e5_medium_MV;
   Bool_t          EF_e5_medium_SiTrk;
   Bool_t          EF_e5_medium_TRT;
   Bool_t          EF_e5_medium_mu4;
   Bool_t          EF_e5_tight;
   Bool_t          EF_e5_tight_SiTrk;
   Bool_t          EF_e5_tight_TRT;
   Bool_t          EF_e5_tight_e5_NoCut;
   Bool_t          EF_eb_physics;
   Bool_t          EF_eb_physics_empty;
   Bool_t          EF_eb_physics_firstempty;
   Bool_t          EF_eb_physics_unpaired_iso;
   Bool_t          EF_eb_physics_unpaired_noniso;
   Bool_t          EF_eb_random;
   Bool_t          EF_eb_random_empty;
   Bool_t          EF_eb_random_firstempty;
   Bool_t          EF_eb_random_unpaired_iso;
   Bool_t          EF_em105_passHLT;
   Bool_t          EF_fj10_empty_NoAlg;
   Bool_t          EF_fj30_jetNoEF;
   Bool_t          EF_fj30_jetNoEF_larcalib;
   Bool_t          EF_fj50_jetNoEF;
   Bool_t          EF_fj50_jetNoEF_larcalib;
   Bool_t          EF_fj75_jetNoEF;
   Bool_t          EF_fj95_jetNoCut_larcalib;
   Bool_t          EF_g10_loose;
   Bool_t          EF_g10_loose_larcalib;
   Bool_t          EF_g11_etcut;
   Bool_t          EF_g15_loose;
   Bool_t          EF_g17_etcut;
   Bool_t          EF_g17_etcut_EFxe20_noMu;
   Bool_t          EF_g17_etcut_EFxe30_noMu;
   Bool_t          EF_g20_loose;
   Bool_t          EF_g20_loose_larcalib;
   Bool_t          EF_g20_loose_xe20_noMu;
   Bool_t          EF_g20_loose_xe30_noMu;
   Bool_t          EF_g20_tight;
   Bool_t          EF_g25_loose_xe30_noMu;
   Bool_t          EF_g30_loose;
   Bool_t          EF_g30_tight;
   Bool_t          EF_g3_NoCut_unpaired_iso;
   Bool_t          EF_g3_NoCut_unpaired_noniso;
   Bool_t          EF_g40_loose;
   Bool_t          EF_g40_loose_larcalib;
   Bool_t          EF_g40_tight;
   Bool_t          EF_g50_loose;
   Bool_t          EF_g50_loose_larcalib;
   Bool_t          EF_g5_NoCut_cosmic;
   Bool_t          EF_g5_loose;
   Bool_t          EF_g5_loose_larcalib;
   Bool_t          EF_g7_loose;
   Bool_t          EF_j115_jetNoCut_larcalib;
   Bool_t          EF_j20_jetNoEF;
   Bool_t          EF_j20_jetNoEF_larcalib;
   Bool_t          EF_j30_fj30_jetNoEF;
   Bool_t          EF_j30_jetNoCut_cosmic;
   Bool_t          EF_j30_jetNoCut_firstempty;
   Bool_t          EF_j30_jetNoCut_unpaired;
   Bool_t          EF_j30_jetNoEF;
   Bool_t          EF_j35_L1TAU_HV_jetNoEF;
   Bool_t          EF_j35_jetNoEF;
   Bool_t          EF_j50_jetNoCut_cosmic;
   Bool_t          EF_j50_jetNoCut_firstempty;
   Bool_t          EF_j50_jetNoCut_unpaired;
   Bool_t          EF_j50_jetNoEF;
   Bool_t          EF_j50_jetNoEF_larcalib;
   Bool_t          EF_j50_jetNoEF_xe20_noMu;
   Bool_t          EF_j50_jetNoEF_xe30_noMu;
   Bool_t          EF_j50_jetNoEF_xe40_noMu;
   Bool_t          EF_j5_empty_NoAlg;
   Bool_t          EF_j5_unpaired_iso_NoAlg;
   Bool_t          EF_j5_unpaired_noniso_NoAlg;
   Bool_t          EF_j75_jetNoEF;
   Bool_t          EF_j75_jetNoEF_EFxe20_noMu;
   Bool_t          EF_j75_jetNoEF_EFxe25_noMu;
   Bool_t          EF_j75_jetNoEF_EFxe30_noMu;
   Bool_t          EF_j75_jetNoEF_EFxe35_noMu;
   Bool_t          EF_j75_jetNoEF_EFxe40_noMu;
   Bool_t          EF_j95_jetNoEF;
   Bool_t          EF_j95_jetNoEF_larcalib;
   Bool_t          EF_je135_NoEF;
   Bool_t          EF_je195_NoEF;
   Bool_t          EF_je255_NoEF;
   Bool_t          EF_je300_NoEF;
   Bool_t          EF_je350_NoEF;
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
   Bool_t          EF_mu10_IDTrkNoCut;
   Bool_t          EF_mu10_MG;
   Bool_t          EF_mu10_MSonly;
   Bool_t          EF_mu10_MSonly_tight;
   Bool_t          EF_mu10_NoAlg;
   Bool_t          EF_mu10_SiTrk;
   Bool_t          EF_mu10_tight;
   Bool_t          EF_mu10i_loose;
   Bool_t          EF_mu13;
   Bool_t          EF_mu13_MG;
   Bool_t          EF_mu13_MG_tight;
   Bool_t          EF_mu13_tight;
   Bool_t          EF_mu15;
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
   Bool_t          EF_mu4_j20_jetNoEF;
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
   Bool_t          EF_mu4mu6_Upsimumu;
   Bool_t          EF_mu6;
   Bool_t          EF_mu6_Bmumu;
   Bool_t          EF_mu6_BmumuX;
   Bool_t          EF_mu6_DiMu;
   Bool_t          EF_mu6_IDTrkNoCut;
   Bool_t          EF_mu6_Jpsie5e3;
   Bool_t          EF_mu6_Jpsie5e3_FS;
   Bool_t          EF_mu6_Jpsimumu;
   Bool_t          EF_mu6_MG;
   Bool_t          EF_mu6_MSonly;
   Bool_t          EF_mu6_MSonly_outOfTime;
   Bool_t          EF_mu6_NoAlg;
   Bool_t          EF_mu6_SiTrk;
   Bool_t          EF_mu6_Trk_Jpsi;
   Bool_t          EF_mu6_Upsimumu_FS;
   Bool_t          EF_mu6_muCombTag;
   Bool_t          EF_tau125_loose;
   Bool_t          EF_tau125_medium;
   Bool_t          EF_tau12_IDTrkNoCut;
   Bool_t          EF_tau12_loose;
   Bool_t          EF_tau12_loose_2b15;
   Bool_t          EF_tau12_loose_3j35_jetNoEF;
   Bool_t          EF_tau12_loose_EFxe12_noMu;
   Bool_t          EF_tau12_loose_IdScan_EFxe12_noMu;
   Bool_t          EF_tau12_loose_IdScan_xe15_noMu;
   Bool_t          EF_tau12_loose_e10_loose;
   Bool_t          EF_tau12_loose_e10_medium;
   Bool_t          EF_tau12_loose_e10_tight;
   Bool_t          EF_tau12_loose_mu10;
   Bool_t          EF_tau12_loose_xe15_noMu;
   Bool_t          EF_tau12_loose_xe20_noMu;
   Bool_t          EF_tau16_loose;
   Bool_t          EF_tau16_loose_2b15;
   Bool_t          EF_tau16_loose_3j35_jetNoEF;
   Bool_t          EF_tau16_loose_e10_loose;
   Bool_t          EF_tau16_loose_e15_loose;
   Bool_t          EF_tau16_loose_mu10;
   Bool_t          EF_tau16_loose_mu15;
   Bool_t          EF_tau16_loose_xe20_noMu;
   Bool_t          EF_tau16_loose_xe25_noMu;
   Bool_t          EF_tau16_loose_xe25_tight_noMu;
   Bool_t          EF_tau16_loose_xe30_noMu;
   Bool_t          EF_tau16_medium;
   Bool_t          EF_tau16_medium_xe22_noMu;
   Bool_t          EF_tau16_medium_xe25_noMu;
   Bool_t          EF_tau16_medium_xe25_tight_noMu;
   Bool_t          EF_tau20_loose;
   Bool_t          EF_tau20_loose_xe25_noMu;
   Bool_t          EF_tau29_loose;
   Bool_t          EF_tau38_loose;
   Bool_t          EF_tau38_medium;
   Bool_t          EF_tau50_IDTrkNoCut;
   Bool_t          EF_tau50_loose;
   Bool_t          EF_tau50_loose_IdScan;
   Bool_t          EF_tau50_medium;
   Bool_t          EF_tau84_loose;
   Bool_t          EF_tau84_medium;
   Bool_t          EF_tauNoCut;
   Bool_t          EF_tauNoCut_IdScan;
   Bool_t          EF_tauNoCut_cosmic;
   Bool_t          EF_tauNoCut_firstempty;
   Bool_t          EF_tauNoCut_hasTrk6_EFxe15_noMu;
   Bool_t          EF_tauNoCut_hasTrk6_IdScan_EFxe15_noMu;
   Bool_t          EF_tauNoCut_hasTrk6_IdScan_xe20_noMu;
   Bool_t          EF_tauNoCut_hasTrk6_xe20_noMu;
   Bool_t          EF_tauNoCut_hasTrk9_xe20_noMu;
   Bool_t          EF_tauNoCut_hasTrk_MV;
   Bool_t          EF_tauNoCut_hasTrk_e10_tight;
   Bool_t          EF_tauNoCut_hasTrk_xe20_noMu;
   Bool_t          EF_tauNoCut_unpaired_iso;
   Bool_t          EF_tauNoCut_unpaired_noniso;
   Bool_t          EF_xe15_noMu;
   Bool_t          EF_xe15_unbiased_noMu;
   Bool_t          EF_xe20;
   Bool_t          EF_xe20_noMu;
   Bool_t          EF_xe20_tight_noMu;
   Bool_t          EF_xe25_medium_noMu;
   Bool_t          EF_xe25_noMu;
   Bool_t          EF_xe25_tight_noMu;
   Bool_t          EF_xe30_allL1;
   Bool_t          EF_xe30_allL1_FEB;
   Bool_t          EF_xe30_allL1_allCells;
   Bool_t          EF_xe30_loose_noMu;
   Bool_t          EF_xe30_medium_noMu;
   Bool_t          EF_xe30_noMu;
   Bool_t          EF_xe30_tight_noMu;
   Bool_t          EF_xe35_loose_noMu;
   Bool_t          EF_xe35_noMu;
   Bool_t          EF_xe35_tight_noMu;
   Bool_t          EF_xe40_noMu;
   Bool_t          EF_xe45_noMu;
   Bool_t          EF_xe55_noMu;
   Bool_t          EF_xe60_medium_noMu;
   Bool_t          EF_xe80_medium_noMu;
   Bool_t          L1_2EM10;
   Bool_t          L1_2EM14;
   Bool_t          L1_2EM2;
   Bool_t          L1_2EM3;
   Bool_t          L1_2EM5;
   Bool_t          L1_2J10;
   Bool_t          L1_2J10_J30;
   Bool_t          L1_2J10_J55;
   Bool_t          L1_2J15;
   Bool_t          L1_2J15_J75;
   Bool_t          L1_2J15_XE10;
   Bool_t          L1_2J15_XE15;
   Bool_t          L1_2J15_XE25;
   Bool_t          L1_2J30;
   Bool_t          L1_2J5;
   Bool_t          L1_2J55;
   Bool_t          L1_2J95;
   Bool_t          L1_2MU0;
   Bool_t          L1_2MU0_FIRSTEMPTY;
   Bool_t          L1_2MU0_MU6;
   Bool_t          L1_2MU10;
   Bool_t          L1_2MU20;
   Bool_t          L1_2MU6;
   Bool_t          L1_2MU6_EM5;
   Bool_t          L1_2TAU11;
   Bool_t          L1_2TAU5;
   Bool_t          L1_2TAU5_EM5;
   Bool_t          L1_2TAU6;
   Bool_t          L1_2TAU6_EM10;
   Bool_t          L1_2TAU6_EM5;
   Bool_t          L1_3J10;
   Bool_t          L1_3J10_2J30;
   Bool_t          L1_3J15;
   Bool_t          L1_3J30;
   Bool_t          L1_3J5_J30;
   Bool_t          L1_4J10;
   Bool_t          L1_4J10_3J15;
   Bool_t          L1_4J10_EM10;
   Bool_t          L1_4J10_MU15;
   Bool_t          L1_4J15;
   Bool_t          L1_4J30;
   Bool_t          L1_4J5;
   Bool_t          L1_4J5_J15;
   Bool_t          L1_4J5_J30;
   Bool_t          L1_5J10;
   Bool_t          L1_6J10;
   Bool_t          L1_EM10;
   Bool_t          L1_EM10I;
   Bool_t          L1_EM14;
   Bool_t          L1_EM14I;
   Bool_t          L1_EM14_XE10;
   Bool_t          L1_EM14_XE15;
   Bool_t          L1_EM2;
   Bool_t          L1_EM2_UNPAIRED_ISO;
   Bool_t          L1_EM2_UNPAIRED_NONISO;
   Bool_t          L1_EM3;
   Bool_t          L1_EM3_EMPTY;
   Bool_t          L1_EM3_FIRSTEMPTY;
   Bool_t          L1_EM3_MV;
   Bool_t          L1_EM5;
   Bool_t          L1_EM5_MU10;
   Bool_t          L1_EM5_MU6;
   Bool_t          L1_EM85;
   Bool_t          L1_FJ10;
   Bool_t          L1_FJ10_EMPTY;
   Bool_t          L1_FJ10_FIRSTEMPTY;
   Bool_t          L1_FJ10_UNPAIRED_ISO;
   Bool_t          L1_FJ30;
   Bool_t          L1_FJ55;
   Bool_t          L1_FJ95;
   Bool_t          L1_J10;
   Bool_t          L1_J10_EMPTY;
   Bool_t          L1_J10_FIRSTEMPTY;
   Bool_t          L1_J10_FJ10;
   Bool_t          L1_J10_MV;
   Bool_t          L1_J10_UNPAIRED;
   Bool_t          L1_J115;
   Bool_t          L1_J15;
   Bool_t          L1_J15_LV;
   Bool_t          L1_J15_MV;
   Bool_t          L1_J15_NL;
   Bool_t          L1_J15_XE15_EM10;
   Bool_t          L1_J15_XE15_MU15;
   Bool_t          L1_J30;
   Bool_t          L1_J30_EMPTY;
   Bool_t          L1_J30_FIRSTEMPTY;
   Bool_t          L1_J30_UNPAIRED;
   Bool_t          L1_J30_XE10;
   Bool_t          L1_J30_XE15;
   Bool_t          L1_J30_XE25;
   Bool_t          L1_J5;
   Bool_t          L1_J55;
   Bool_t          L1_J5_EMPTY;
   Bool_t          L1_J5_FIRSTEMPTY;
   Bool_t          L1_J5_UNPAIRED_ISO;
   Bool_t          L1_J5_UNPAIRED_NONISO;
   Bool_t          L1_J75;
   Bool_t          L1_J95;
   Bool_t          L1_JE100;
   Bool_t          L1_JE140;
   Bool_t          L1_JE200;
   Bool_t          L1_JE60;
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
   Bool_t          L1_RD0_EMPTY;
   Bool_t          L1_RD0_FILLED;
   Bool_t          L1_RD0_FIRSTEMPTY;
   Bool_t          L1_RD0_UNPAIRED_ISO;
   Bool_t          L1_RD1_EMPTY;
   Bool_t          L1_RD1_FILLED;
   Bool_t          L1_TAU11;
   Bool_t          L1_TAU11I;
   Bool_t          L1_TAU20;
   Bool_t          L1_TAU30;
   Bool_t          L1_TAU5;
   Bool_t          L1_TAU50;
   Bool_t          L1_TAU5_3J5_2J15;
   Bool_t          L1_TAU5_4J5_3J15;
   Bool_t          L1_TAU5_EMPTY;
   Bool_t          L1_TAU5_FIRSTEMPTY;
   Bool_t          L1_TAU5_MU6;
   Bool_t          L1_TAU5_MV;
   Bool_t          L1_TAU5_UNPAIRED_ISO;
   Bool_t          L1_TAU5_UNPAIRED_NONISO;
   Bool_t          L1_TAU5_XE10;
   Bool_t          L1_TAU6;
   Bool_t          L1_TAU6I;
   Bool_t          L1_TAU6_3J5_2J15;
   Bool_t          L1_TAU6_4J5_3J15;
   Bool_t          L1_TAU6_MU10;
   Bool_t          L1_TAU6_MU15;
   Bool_t          L1_TAU6_XE10;
   Bool_t          L1_TE100;
   Bool_t          L1_TE180;
   Bool_t          L1_TE20;
   Bool_t          L1_TE50;
   Bool_t          L1_XE10;
   Bool_t          L1_XE15;
   Bool_t          L1_XE20;
   Bool_t          L1_XE25;
   Bool_t          L1_XE30;
   Bool_t          L1_XE35;
   Bool_t          L1_XE40;
   Bool_t          L1_XE50;
   Bool_t          L1_ZB;
   Bool_t          L2_2e10_loose;
   Bool_t          L2_2e10_medium;
   Bool_t          L2_2e15_loose;
   Bool_t          L2_2e3_loose;
   Bool_t          L2_2e3_loose_SiTrk;
   Bool_t          L2_2e3_loose_TRT;
   Bool_t          L2_2e3_medium;
   Bool_t          L2_2e3_medium_SiTrk;
   Bool_t          L2_2e3_medium_TRT;
   Bool_t          L2_2e3_tight;
   Bool_t          L2_2e5_medium;
   Bool_t          L2_2e5_medium_SiTrk;
   Bool_t          L2_2e5_medium_TRT;
   Bool_t          L2_2e5_tight;
   Bool_t          L2_2g10_loose;
   Bool_t          L2_2g15_loose;
   Bool_t          L2_2g5_loose;
   Bool_t          L2_2g7_loose;
   Bool_t          L2_2j15;
   Bool_t          L2_2j15_deta3_5;
   Bool_t          L2_2j15_deta5;
   Bool_t          L2_2j25;
   Bool_t          L2_2j25_deta3_5;
   Bool_t          L2_2j25_j45_anymct100;
   Bool_t          L2_2j25_j45_anymct150;
   Bool_t          L2_2j25_j45_anymct175;
   Bool_t          L2_2j25_j45_dphi03;
   Bool_t          L2_2j25_j45_leadingmct100;
   Bool_t          L2_2j25_j45_leadingmct150;
   Bool_t          L2_2j25_j45_leadingmct175;
   Bool_t          L2_2j25_j70_anymct150;
   Bool_t          L2_2j25_j70_anymct175;
   Bool_t          L2_2j25_j70_dphi03;
   Bool_t          L2_2j25_j70_leadingmct150;
   Bool_t          L2_2j25_j70_leadingmct175;
   Bool_t          L2_2j30;
   Bool_t          L2_2j30_anymct100;
   Bool_t          L2_2j30_anymct150;
   Bool_t          L2_2j30_anymct175;
   Bool_t          L2_2j30_deta3_5;
   Bool_t          L2_2j30_j90_dphi03;
   Bool_t          L2_2j30_leadingmct100;
   Bool_t          L2_2j30_leadingmct150;
   Bool_t          L2_2j30_leadingmct175;
   Bool_t          L2_2j35_jetNoEF_xe20_noMu;
   Bool_t          L2_2j35_jetNoEF_xe30_noMu;
   Bool_t          L2_2j35_jetNoEF_xe40_noMu;
   Bool_t          L2_2j45;
   Bool_t          L2_2j70;
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
   Bool_t          L2_2mu4_Upsimumu;
   Bool_t          L2_2mu6;
   Bool_t          L2_2mu6_MG;
   Bool_t          L2_2mu6_NoAlg;
   Bool_t          L2_3j15_j45;
   Bool_t          L2_3j25;
   Bool_t          L2_3j25_2j45;
   Bool_t          L2_3j30;
   Bool_t          L2_3j45;
   Bool_t          L2_4j15_j30;
   Bool_t          L2_4j15_j45;
   Bool_t          L2_4j25;
   Bool_t          L2_4j25_3j30;
   Bool_t          L2_4j30;
   Bool_t          L2_4j45;
   Bool_t          L2_5j25;
   Bool_t          L2_6j25;
   Bool_t          L2_e10_NoCut;
   Bool_t          L2_e10_loose;
   Bool_t          L2_e10_loose_mu10;
   Bool_t          L2_e10_loose_mu6;
   Bool_t          L2_e10_medium;
   Bool_t          L2_e10_medium_IDTrkNoCut;
   Bool_t          L2_e10_medium_SiTrk;
   Bool_t          L2_e10_medium_TRT;
   Bool_t          L2_e10_tight;
   Bool_t          L2_e15_loose;
   Bool_t          L2_e15_loose_IDTrkNoCut;
   Bool_t          L2_e15_medium;
   Bool_t          L2_e15_medium_SiTrk;
   Bool_t          L2_e15_medium_TRT;
   Bool_t          L2_e15_tight;
   Bool_t          L2_e18_medium;
   Bool_t          L2_e20_loose;
   Bool_t          L2_e20_loose_IDTrkNoCut;
   Bool_t          L2_e20_loose_passEF;
   Bool_t          L2_e20_loose_passL2;
   Bool_t          L2_e20_loose_xe20_noMu;
   Bool_t          L2_e20_loose_xe30_noMu;
   Bool_t          L2_e20_medium;
   Bool_t          L2_e25_loose;
   Bool_t          L2_e30_loose;
   Bool_t          L2_e3_loose;
   Bool_t          L2_e3_loose_SiTrk;
   Bool_t          L2_e3_loose_TRT;
   Bool_t          L2_e3_medium;
   Bool_t          L2_e3_medium_SiTrk;
   Bool_t          L2_e3_medium_TRT;
   Bool_t          L2_e5_NoCut_firstempty;
   Bool_t          L2_e5_medium;
   Bool_t          L2_e5_medium_MV;
   Bool_t          L2_e5_medium_SiTrk;
   Bool_t          L2_e5_medium_TRT;
   Bool_t          L2_e5_medium_mu4;
   Bool_t          L2_e5_tight;
   Bool_t          L2_e5_tight_SiTrk;
   Bool_t          L2_e5_tight_TRT;
   Bool_t          L2_e5_tight_e5_NoCut;
   Bool_t          L2_eb_physics;
   Bool_t          L2_eb_physics_empty;
   Bool_t          L2_eb_physics_firstempty;
   Bool_t          L2_eb_physics_unpaired_iso;
   Bool_t          L2_eb_physics_unpaired_noniso;
   Bool_t          L2_eb_random;
   Bool_t          L2_eb_random_empty;
   Bool_t          L2_eb_random_firstempty;
   Bool_t          L2_eb_random_unpaired_iso;
   Bool_t          L2_em105_passHLT;
   Bool_t          L2_em3_empty_larcalib;
   Bool_t          L2_fj10_empty_NoAlg;
   Bool_t          L2_fj25;
   Bool_t          L2_fj25_larcalib;
   Bool_t          L2_fj45;
   Bool_t          L2_fj45_larcalib;
   Bool_t          L2_fj70;
   Bool_t          L2_fj95_jetNoCut_larcalib;
   Bool_t          L2_g10_loose;
   Bool_t          L2_g11_etcut;
   Bool_t          L2_g15_loose;
   Bool_t          L2_g17_etcut;
   Bool_t          L2_g17_etcut_EFxe20_noMu;
   Bool_t          L2_g17_etcut_EFxe30_noMu;
   Bool_t          L2_g20_loose;
   Bool_t          L2_g20_loose_xe20_noMu;
   Bool_t          L2_g20_loose_xe30_noMu;
   Bool_t          L2_g20_tight;
   Bool_t          L2_g25_loose_xe30_noMu;
   Bool_t          L2_g30_loose;
   Bool_t          L2_g30_tight;
   Bool_t          L2_g3_NoCut_unpaired_iso;
   Bool_t          L2_g3_NoCut_unpaired_noniso;
   Bool_t          L2_g40_loose;
   Bool_t          L2_g40_tight;
   Bool_t          L2_g50_loose;
   Bool_t          L2_g5_NoCut_cosmic;
   Bool_t          L2_g5_loose;
   Bool_t          L2_g7_loose;
   Bool_t          L2_j115_jetNoCut_larcalib;
   Bool_t          L2_j15;
   Bool_t          L2_j15_larcalib;
   Bool_t          L2_j25;
   Bool_t          L2_j25_fj25;
   Bool_t          L2_j25_jetNoCut_cosmic;
   Bool_t          L2_j25_jetNoCut_firstempty;
   Bool_t          L2_j25_jetNoCut_unpaired;
   Bool_t          L2_j30;
   Bool_t          L2_j30_L1TAU_HV;
   Bool_t          L2_j30_Trackless_HV;
   Bool_t          L2_j45;
   Bool_t          L2_j45_jetNoCut_cosmic;
   Bool_t          L2_j45_jetNoCut_firstempty;
   Bool_t          L2_j45_jetNoCut_unpaired;
   Bool_t          L2_j45_larcalib;
   Bool_t          L2_j45_xe12_noMu;
   Bool_t          L2_j45_xe20_noMu;
   Bool_t          L2_j45_xe30_noMu;
   Bool_t          L2_j5_empty_NoAlg;
   Bool_t          L2_j5_empty_larcalib;
   Bool_t          L2_j5_unpaired_iso_NoAlg;
   Bool_t          L2_j5_unpaired_noniso_NoAlg;
   Bool_t          L2_j70;
   Bool_t          L2_j70_EFxe20_noMu;
   Bool_t          L2_j70_EFxe25_noMu;
   Bool_t          L2_j70_EFxe30_noMu;
   Bool_t          L2_j70_EFxe35_noMu;
   Bool_t          L2_j70_EFxe40_noMu;
   Bool_t          L2_j90;
   Bool_t          L2_j90_larcalib;
   Bool_t          L2_je135;
   Bool_t          L2_je195;
   Bool_t          L2_je255;
   Bool_t          L2_je350;
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
   Bool_t          L2_mu10_IDTrkNoCut;
   Bool_t          L2_mu10_MG;
   Bool_t          L2_mu10_MSonly;
   Bool_t          L2_mu10_MSonly_tight;
   Bool_t          L2_mu10_NoAlg;
   Bool_t          L2_mu10_SiTrk;
   Bool_t          L2_mu10_tight;
   Bool_t          L2_mu10i_loose;
   Bool_t          L2_mu13;
   Bool_t          L2_mu13_MG;
   Bool_t          L2_mu13_MG_tight;
   Bool_t          L2_mu13_tight;
   Bool_t          L2_mu15;
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
   Bool_t          L2_mu4mu6_Upsimumu;
   Bool_t          L2_mu6;
   Bool_t          L2_mu6_Bmumu;
   Bool_t          L2_mu6_BmumuX;
   Bool_t          L2_mu6_DiMu;
   Bool_t          L2_mu6_IDTrkNoCut;
   Bool_t          L2_mu6_Jpsie5e3;
   Bool_t          L2_mu6_Jpsie5e3_FS;
   Bool_t          L2_mu6_Jpsimumu;
   Bool_t          L2_mu6_MG;
   Bool_t          L2_mu6_MSonly;
   Bool_t          L2_mu6_MSonly_outOfTime;
   Bool_t          L2_mu6_NoAlg;
   Bool_t          L2_mu6_SiTrk;
   Bool_t          L2_mu6_Trk_Jpsi;
   Bool_t          L2_mu6_Upsimumu_FS;
   Bool_t          L2_mu6_muCombTag;
   Bool_t          L2_tau125_loose;
   Bool_t          L2_tau125_medium;
   Bool_t          L2_tau12_IDTrkNoCut;
   Bool_t          L2_tau12_loose;
   Bool_t          L2_tau12_loose_2b15;
   Bool_t          L2_tau12_loose_3j30;
   Bool_t          L2_tau12_loose_EFxe12_noMu;
   Bool_t          L2_tau12_loose_IdScan_EFxe12_noMu;
   Bool_t          L2_tau12_loose_IdScan_xe15_noMu;
   Bool_t          L2_tau12_loose_e10_loose;
   Bool_t          L2_tau12_loose_e10_medium;
   Bool_t          L2_tau12_loose_e10_tight;
   Bool_t          L2_tau12_loose_mu10;
   Bool_t          L2_tau12_loose_xe15_noMu;
   Bool_t          L2_tau12_loose_xe20_noMu;
   Bool_t          L2_tau16_loose;
   Bool_t          L2_tau16_loose_2b15;
   Bool_t          L2_tau16_loose_3j30;
   Bool_t          L2_tau16_loose_e10_loose;
   Bool_t          L2_tau16_loose_e15_loose;
   Bool_t          L2_tau16_loose_mu10;
   Bool_t          L2_tau16_loose_mu15;
   Bool_t          L2_tau16_loose_xe20_noMu;
   Bool_t          L2_tau16_loose_xe25_noMu;
   Bool_t          L2_tau16_loose_xe25_tight_noMu;
   Bool_t          L2_tau16_loose_xe30_noMu;
   Bool_t          L2_tau16_medium;
   Bool_t          L2_tau16_medium_xe22_noMu;
   Bool_t          L2_tau16_medium_xe25_noMu;
   Bool_t          L2_tau16_medium_xe25_tight_noMu;
   Bool_t          L2_tau20_loose;
   Bool_t          L2_tau20_loose_xe25_noMu;
   Bool_t          L2_tau29_loose;
   Bool_t          L2_tau38_loose;
   Bool_t          L2_tau38_medium;
   Bool_t          L2_tau50_IDTrkNoCut;
   Bool_t          L2_tau50_loose;
   Bool_t          L2_tau50_loose_IdScan;
   Bool_t          L2_tau50_medium;
   Bool_t          L2_tau5_empty_larcalib;
   Bool_t          L2_tau84_loose;
   Bool_t          L2_tau84_medium;
   Bool_t          L2_tauNoCut;
   Bool_t          L2_tauNoCut_IdScan;
   Bool_t          L2_tauNoCut_cosmic;
   Bool_t          L2_tauNoCut_firstempty;
   Bool_t          L2_tauNoCut_hasTrk6_EFxe15_noMu;
   Bool_t          L2_tauNoCut_hasTrk6_IdScan_EFxe15_noMu;
   Bool_t          L2_tauNoCut_hasTrk6_IdScan_xe20_noMu;
   Bool_t          L2_tauNoCut_hasTrk6_xe20_noMu;
   Bool_t          L2_tauNoCut_hasTrk9_xe20_noMu;
   Bool_t          L2_tauNoCut_hasTrk_MV;
   Bool_t          L2_tauNoCut_hasTrk_e10_tight;
   Bool_t          L2_tauNoCut_hasTrk_xe20_noMu;
   Bool_t          L2_tauNoCut_unpaired_iso;
   Bool_t          L2_tauNoCut_unpaired_noniso;
   Bool_t          L2_xe12;
   Bool_t          L2_xe12_loose_noMu;
   Bool_t          L2_xe12_medium_noMu;
   Bool_t          L2_xe12_noMu;
   Bool_t          L2_xe15_medium_noMu;
   Bool_t          L2_xe15_noMu;
   Bool_t          L2_xe15_tight_noMu;
   Bool_t          L2_xe15_unbiased_noMu;
   Bool_t          L2_xe17_tight_noMu;
   Bool_t          L2_xe20_noMu;
   Bool_t          L2_xe22_loose_noMu;
   Bool_t          L2_xe22_tight_noMu;
   Bool_t          L2_xe25_noMu;
   Bool_t          L2_xe27_tight_noMu;
   Bool_t          L2_xe30_allL1;
   Bool_t          L2_xe30_allL1_FEB;
   Bool_t          L2_xe30_allL1_allCells;
   Bool_t          L2_xe30_noMu;
   Bool_t          L2_xe35_noMu;
   Bool_t          L2_xe40_medium_noMu;
   Bool_t          L2_xe45_noMu;
   Bool_t          L2_xe60_medium_noMu;
   Int_t           ph_n;
   vector<float>   *ph_E;
   vector<float>   *ph_Et;
   vector<float>   *ph_pt;
   vector<float>   *ph_m;
   vector<float>   *ph_eta;
   vector<float>   *ph_phi;
   vector<float>   *ph_px;
   vector<float>   *ph_py;
   vector<float>   *ph_pz;
   vector<int>     *ph_author;
   vector<int>     *ph_isRecovered;
   vector<unsigned int> *ph_isEM;
   vector<int>     *ph_convFlag;
   vector<int>     *ph_isConv;
   vector<int>     *ph_nConv;
   vector<int>     *ph_nSingleTrackConv;
   vector<int>     *ph_nDoubleTrackConv;
   vector<int>     *ph_loose;
   vector<int>     *ph_tight;
   vector<int>     *ph_tightIso;
   vector<float>   *ph_Ethad;
   vector<float>   *ph_Ethad1;
   vector<float>   *ph_E033;
   vector<float>   *ph_f1;
   vector<float>   *ph_f1core;
   vector<float>   *ph_Emins1;
   vector<float>   *ph_fside;
   vector<float>   *ph_Emax2;
   vector<float>   *ph_ws3;
   vector<float>   *ph_wstot;
   vector<float>   *ph_E132;
   vector<float>   *ph_E1152;
   vector<float>   *ph_emaxs1;
   vector<float>   *ph_deltaEs;
   vector<float>   *ph_E233;
   vector<float>   *ph_E237;
   vector<float>   *ph_E277;
   vector<float>   *ph_weta2;
   vector<float>   *ph_f3;
   vector<float>   *ph_f3core;
   vector<float>   *ph_rphiallcalo;
   vector<float>   *ph_Etcone45;
   vector<float>   *ph_Etcone20;
   vector<float>   *ph_Etcone30;
   vector<float>   *ph_Etcone40;
   vector<float>   *ph_ptcone30;
   vector<float>   *ph_convanglematch;
   vector<float>   *ph_convtrackmatch;
   vector<int>     *ph_hasconv;
   vector<float>   *ph_convvtxx;
   vector<float>   *ph_convvtxy;
   vector<float>   *ph_convvtxz;
   vector<float>   *ph_Rconv;
   vector<float>   *ph_zconv;
   vector<float>   *ph_convvtxchi2;
   vector<float>   *ph_pt1conv;
   vector<int>     *ph_convtrk1nBLHits;
   vector<int>     *ph_convtrk1nPixHits;
   vector<int>     *ph_convtrk1nSCTHits;
   vector<int>     *ph_convtrk1nTRTHits;
   vector<float>   *ph_pt2conv;
   vector<int>     *ph_convtrk2nBLHits;
   vector<int>     *ph_convtrk2nPixHits;
   vector<int>     *ph_convtrk2nSCTHits;
   vector<int>     *ph_convtrk2nTRTHits;
   vector<float>   *ph_ptconv;
   vector<float>   *ph_pzconv;
   vector<float>   *ph_reta;
   vector<float>   *ph_rphi;
   vector<float>   *ph_EtringnoisedR03sig2;
   vector<float>   *ph_EtringnoisedR03sig3;
   vector<float>   *ph_EtringnoisedR03sig4;
   vector<double>  *ph_isolationlikelihoodjets;
   vector<double>  *ph_isolationlikelihoodhqelectrons;
   vector<double>  *ph_loglikelihood;
   vector<double>  *ph_photonweight;
   vector<double>  *ph_photonbgweight;
   vector<double>  *ph_neuralnet;
   vector<double>  *ph_Hmatrix;
   vector<double>  *ph_Hmatrix5;
   vector<double>  *ph_adaboost;
   vector<float>   *ph_zvertex;
   vector<float>   *ph_errz;
   vector<float>   *ph_etap;
   vector<float>   *ph_depth;
   vector<float>   *ph_cl_E;
   vector<float>   *ph_cl_pt;
   vector<float>   *ph_cl_eta;
   vector<float>   *ph_cl_phi;
   vector<float>   *ph_Es0;
   vector<float>   *ph_etas0;
   vector<float>   *ph_phis0;
   vector<float>   *ph_Es1;
   vector<float>   *ph_etas1;
   vector<float>   *ph_phis1;
   vector<float>   *ph_Es2;
   vector<float>   *ph_etas2;
   vector<float>   *ph_phis2;
   vector<float>   *ph_Es3;
   vector<float>   *ph_etas3;
   vector<float>   *ph_phis3;
   vector<float>   *ph_rawcl_Es0;
   vector<float>   *ph_rawcl_etas0;
   vector<float>   *ph_rawcl_phis0;
   vector<float>   *ph_rawcl_Es1;
   vector<float>   *ph_rawcl_etas1;
   vector<float>   *ph_rawcl_phis1;
   vector<float>   *ph_rawcl_Es2;
   vector<float>   *ph_rawcl_etas2;
   vector<float>   *ph_rawcl_phis2;
   vector<float>   *ph_rawcl_Es3;
   vector<float>   *ph_rawcl_etas3;
   vector<float>   *ph_rawcl_phis3;
   vector<float>   *ph_rawcl_E;
   vector<float>   *ph_rawcl_pt;
   vector<float>   *ph_rawcl_eta;
   vector<float>   *ph_rawcl_phi;
   vector<float>   *ph_deltaEmax2;
   vector<unsigned int> *ph_isIso;
   vector<float>   *ph_topoEtcone20;
   vector<float>   *ph_topoEtcone40;
   vector<float>   *ph_topoEtcone60;
   vector<float>   *ph_jet_dr;
   vector<float>   *ph_jet_E;
   vector<float>   *ph_jet_pt;
   vector<float>   *ph_jet_m;
   vector<float>   *ph_jet_eta;
   vector<float>   *ph_jet_phi;
   vector<int>     *ph_jet_matched;
   vector<float>   *ph_trackIsol;
   vector<float>   *ph_convIP;
   vector<float>   *ph_convIPRev;
   vector<float>   *ph_ptIsolationCone;
   vector<float>   *ph_ptIsolationConePhAngle;
   vector<float>   *ph_Etcone40_pt_corrected;
   vector<float>   *ph_Etcone40_ED_corrected;
   vector<float>   *ph_Etcone40_corrected;
   vector<float>   *ph_topodr;
   vector<float>   *ph_topopt;
   vector<float>   *ph_topoeta;
   vector<float>   *ph_topophi;
   vector<int>     *ph_topomatched;
   vector<float>   *ph_topoEMdr;
   vector<float>   *ph_topoEMpt;
   vector<float>   *ph_topoEMeta;
   vector<float>   *ph_topoEMphi;
   vector<int>     *ph_topoEMmatched;
   vector<float>   *ph_EF_dr;
   vector<int>     *ph_EF_index;
   vector<float>   *ph_L2_dr;
   vector<int>     *ph_L2_index;
   vector<float>   *ph_L1_dr;
   vector<int>     *ph_L1_index;
   vector<float>   *ph_EF_E;
   vector<float>   *ph_EF_Et;
   vector<float>   *ph_EF_pt;
   vector<float>   *ph_EF_eta;
   vector<float>   *ph_EF_phi;
   vector<float>   *ph_EF_Ethad;
   vector<float>   *ph_EF_Ethad1;
   vector<float>   *ph_EF_f1;
   vector<float>   *ph_EF_Emins1;
   vector<float>   *ph_EF_fside;
   vector<float>   *ph_EF_Emax2;
   vector<float>   *ph_EF_ws3;
   vector<float>   *ph_EF_wstot;
   vector<float>   *ph_EF_E233;
   vector<float>   *ph_EF_E237;
   vector<float>   *ph_EF_E277;
   vector<float>   *ph_EF_weta2;
   vector<float>   *ph_EF_rphiallcalo;
   vector<float>   *ph_EF_Etcone45;
   vector<float>   *ph_EF_Etcone20;
   vector<float>   *ph_EF_Etcone30;
   vector<float>   *ph_EF_Etcone40;
   vector<float>   *ph_EF_zvertex;
   vector<float>   *ph_EF_errz;
   vector<int>     *ph_EF_matched;
   vector<float>   *ph_L2_E;
   vector<float>   *ph_L2_Et;
   vector<float>   *ph_L2_pt;
   vector<float>   *ph_L2_eta;
   vector<float>   *ph_L2_phi;
   vector<float>   *ph_L2_Ethad1;
   vector<float>   *ph_L2_reta;
   vector<float>   *ph_L2_Eratio;
   vector<float>   *ph_L2_E237;
   vector<float>   *ph_L2_E277;
   vector<float>   *ph_L2_fside;
   vector<float>   *ph_L2_weta2;
   vector<float>   *ph_L2_Emaxs1;
   vector<float>   *ph_L2_Emax2;
   vector<int>     *ph_L2_matched;
   vector<float>   *ph_L1_eta;
   vector<float>   *ph_L1_phi;
   vector<float>   *ph_L1_EMisol;
   vector<float>   *ph_L1_hadisol;
   vector<float>   *ph_L1_hadcore;
   vector<float>   *ph_L1_pt;
   vector<float>   *ph_L1_Et;
   vector<int>     *ph_L1_matched;
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
   vector<int>     *mu_muid_loose;
   vector<int>     *mu_muid_medium;
   vector<int>     *mu_muid_tight;
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
   vector<int>     *mu_staco_loose;
   vector<int>     *mu_staco_medium;
   vector<int>     *mu_staco_tight;
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
   Int_t           tau_n;
   vector<float>   *tau_Et;
   vector<float>   *tau_pt;
   vector<float>   *tau_m;
   vector<float>   *tau_eta;
   vector<float>   *tau_phi;
   vector<float>   *tau_charge;
   vector<float>   *tau_BDTEleScore;
   vector<float>   *tau_BDTJetScore;
   vector<float>   *tau_discCut;
   vector<float>   *tau_discCutTMVA;
   vector<float>   *tau_discLL;
   vector<float>   *tau_discNN;
   vector<float>   *tau_efficLL;
   vector<float>   *tau_efficNN;
   vector<float>   *tau_likelihood;
   vector<float>   *tau_tauJetNeuralNetwork;
   vector<float>   *tau_tauENeuralNetwork;
   vector<float>   *tau_tauElTauLikelihood;
   vector<int>     *tau_electronVetoLoose;
   vector<int>     *tau_electronVetoMedium;
   vector<int>     *tau_electronVetoTight;
   vector<int>     *tau_muonVeto;
   vector<int>     *tau_tauCutLoose;
   vector<int>     *tau_tauCutMedium;
   vector<int>     *tau_tauCutTight;
   vector<int>     *tau_tauCutSafeLoose;
   vector<int>     *tau_tauCutSafeMedium;
   vector<int>     *tau_tauCutSafeTight;
   vector<int>     *tau_tauCutSafeCaloLoose;
   vector<int>     *tau_tauCutSafeCaloMedium;
   vector<int>     *tau_tauCutSafeCaloTight;
   vector<int>     *tau_tauLlhLoose;
   vector<int>     *tau_tauLlhMedium;
   vector<int>     *tau_tauLlhTight;
   vector<int>     *tau_author;
   vector<int>     *tau_ROIword;
   vector<int>     *tau_nProng;
   vector<int>     *tau_numTrack;
   vector<float>   *tau_etOverPtLeadTrk;
   vector<float>   *tau_ipZ0SinThetaSigLeadTrk;
   vector<float>   *tau_leadTrkPt;
   vector<int>     *tau_nLooseTrk;
   vector<int>     *tau_nLooseConvTrk;
   vector<int>     *tau_nProngLoose;
   vector<float>   *tau_ipSigLeadTrk;
   vector<float>   *tau_ipSigLeadLooseTrk;
   vector<float>   *tau_etOverPtLeadLooseTrk;
   vector<float>   *tau_leadLooseTrkPt;
   vector<float>   *tau_chrgLooseTrk;
   vector<float>   *tau_massTrkSys;
   vector<float>   *tau_trkWidth2;
   vector<float>   *tau_trFlightPathSig;
   vector<float>   *tau_etEflow;
   vector<float>   *tau_mEflow;
   vector<int>     *tau_nPi0;
   vector<float>   *tau_ele_E237E277;
   vector<float>   *tau_ele_PresamplerFraction;
   vector<float>   *tau_ele_ECALFirstFraction;
   vector<float>   *tau_seedCalo_EMRadius;
   vector<float>   *tau_seedCalo_hadRadius;
   vector<float>   *tau_seedCalo_etEMAtEMScale;
   vector<float>   *tau_seedCalo_etHadAtEMScale;
   vector<float>   *tau_seedCalo_isolFrac;
   vector<float>   *tau_seedCalo_centFrac;
   vector<float>   *tau_seedCalo_stripWidth2;
   vector<int>     *tau_seedCalo_nStrip;
   vector<float>   *tau_seedCalo_etEMCalib;
   vector<float>   *tau_seedCalo_etHadCalib;
   vector<float>   *tau_seedCalo_eta;
   vector<float>   *tau_seedCalo_phi;
   vector<float>   *tau_seedCalo_nIsolLooseTrk;
   vector<float>   *tau_seedCalo_trkAvgDist;
   vector<float>   *tau_seedCalo_trkRmsDist;
   vector<float>   *tau_seedTrk_EMRadius;
   vector<float>   *tau_seedTrk_isolFrac;
   vector<float>   *tau_seedTrk_etChrgHadOverSumTrkPt;
   vector<float>   *tau_seedTrk_isolFracWide;
   vector<float>   *tau_seedTrk_etHadAtEMScale;
   vector<float>   *tau_seedTrk_etEMAtEMScale;
   vector<float>   *tau_seedTrk_etEMCL;
   vector<float>   *tau_seedTrk_etChrgEM;
   vector<float>   *tau_seedTrk_etNeuEM;
   vector<float>   *tau_seedTrk_etResNeuEM;
   vector<float>   *tau_seedTrk_hadLeakEt;
   vector<float>   *tau_seedTrk_sumEMCellEtOverLeadTrkPt;
   vector<float>   *tau_seedTrk_secMaxStripEt;
   vector<float>   *tau_seedTrk_stripWidth2;
   vector<int>     *tau_seedTrk_nStrip;
   vector<float>   *tau_seedTrk_etChrgHad;
   vector<int>     *tau_seedTrk_nOtherCoreTrk;
   vector<int>     *tau_seedTrk_nIsolTrk;
   vector<float>   *tau_seedTrk_etIsolEM;
   vector<float>   *tau_seedTrk_etIsolHad;
   vector<float>   *tau_calcVars_sumTrkPt;
   vector<float>   *tau_calcVars_numTopoClusters;
   vector<float>   *tau_calcVars_numEffTopoClusters;
   vector<float>   *tau_calcVars_topoInvMass;
   vector<float>   *tau_calcVars_effTopoInvMass;
   vector<float>   *tau_calcVars_topoMeanDeltaR;
   vector<float>   *tau_calcVars_effTopoMeanDeltaR;
   vector<float>   *tau_calcVars_etHadSumPtTracks;
   vector<float>   *tau_calcVars_etEMSumPtTracks;
   vector<int>     *tau_track_n;
   vector<float>   *tau_EF_dr;
   vector<float>   *tau_EF_E;
   vector<float>   *tau_EF_Et;
   vector<float>   *tau_EF_pt;
   vector<float>   *tau_EF_eta;
   vector<float>   *tau_EF_phi;
   vector<int>     *tau_EF_matched;
   vector<float>   *tau_L2_dr;
   vector<float>   *tau_L2_E;
   vector<float>   *tau_L2_Et;
   vector<float>   *tau_L2_pt;
   vector<float>   *tau_L2_eta;
   vector<float>   *tau_L2_phi;
   vector<int>     *tau_L2_matched;
   vector<float>   *tau_L1_dr;
   vector<float>   *tau_L1_Et;
   vector<float>   *tau_L1_pt;
   vector<float>   *tau_L1_eta;
   vector<float>   *tau_L1_phi;
   vector<int>     *tau_L1_matched;
   Int_t           jet_antikt4h1topo_n;
   vector<float>   *jet_antikt4h1topo_E;
   vector<float>   *jet_antikt4h1topo_pt;
   vector<float>   *jet_antikt4h1topo_m;
   vector<float>   *jet_antikt4h1topo_eta;
   vector<float>   *jet_antikt4h1topo_phi;
   vector<float>   *jet_antikt4h1topo_EtaPhys;
   vector<float>   *jet_antikt4h1topo_PhiPhys;
   vector<float>   *jet_antikt4h1topo_MPhys;
   vector<float>   *jet_antikt4h1topo_WIDTH;
   vector<float>   *jet_antikt4h1topo_n90;
   vector<float>   *jet_antikt4h1topo_n90constituents;
   vector<float>   *jet_antikt4h1topo_fracSamplingMax;
   vector<float>   *jet_antikt4h1topo_SamplingMax;
   vector<float>   *jet_antikt4h1topo_BCH_CORR_CELL;
   vector<float>   *jet_antikt4h1topo_BCH_CORR_DOTX;
   vector<float>   *jet_antikt4h1topo_BCH_CORR_JET;
   vector<float>   *jet_antikt4h1topo_BCH_CORR_JET_FORCELL;
   vector<float>   *jet_antikt4h1topo_ENG_BAD_CELLS;
   vector<float>   *jet_antikt4h1topo_N_BAD_CELLS;
   vector<float>   *jet_antikt4h1topo_N_BAD_CELLS_CORR;
   vector<float>   *jet_antikt4h1topo_BAD_CELLS_CORR_E;
   vector<float>   *jet_antikt4h1topo_hecf;
   vector<float>   *jet_antikt4h1topo_tgap3f;
   vector<int>     *jet_antikt4h1topo_isGood;
   vector<float>   *jet_antikt4h1topo_timing;
   vector<float>   *jet_antikt4h1topo_quality;
   vector<float>   *jet_antikt4h1topo_emfrac;
   vector<float>   *jet_antikt4h1topo_GCWJES;
   vector<float>   *jet_antikt4h1topo_EMJES;
   vector<float>   *jet_antikt4h1topo_CB;
   vector<float>   *jet_antikt4h1topo_emscale_E;
   vector<float>   *jet_antikt4h1topo_emscale_pt;
   vector<float>   *jet_antikt4h1topo_emscale_m;
   vector<float>   *jet_antikt4h1topo_emscale_eta;
   vector<float>   *jet_antikt4h1topo_emscale_phi;
   vector<float>   *jet_antikt4h1topo_jvtxf;
   vector<float>   *jet_antikt4h1topo_jvtx_x;
   vector<float>   *jet_antikt4h1topo_jvtx_y;
   vector<float>   *jet_antikt4h1topo_jvtx_z;
   vector<double>  *jet_antikt4h1topo_flavor_weight;
   vector<double>  *jet_antikt4h1topo_flavor_weight_TrackCounting2D;
   vector<double>  *jet_antikt4h1topo_flavor_weight_JetProb;
   vector<double>  *jet_antikt4h1topo_flavor_weight_IP1D;
   vector<double>  *jet_antikt4h1topo_flavor_weight_IP2D;
   vector<double>  *jet_antikt4h1topo_flavor_weight_IP3D;
   vector<double>  *jet_antikt4h1topo_flavor_weight_SV0;
   vector<double>  *jet_antikt4h1topo_flavor_weight_SV1;
   vector<double>  *jet_antikt4h1topo_flavor_weight_SV2;
   vector<double>  *jet_antikt4h1topo_flavor_weight_JetFitterTag;
   vector<double>  *jet_antikt4h1topo_flavor_weight_JetFitterCOMB;
   vector<double>  *jet_antikt4h1topo_flavor_weight_JetFitterTagNN;
   vector<double>  *jet_antikt4h1topo_flavor_weight_JetFitterCOMBNN;
   vector<double>  *jet_antikt4h1topo_flavor_weight_SoftMuonTag;
   vector<double>  *jet_antikt4h1topo_flavor_weight_SoftElectronTag;
   vector<float>   *jet_antikt4h1topo_e_PreSamplerB;
   vector<float>   *jet_antikt4h1topo_e_EMB1;
   vector<float>   *jet_antikt4h1topo_e_EMB2;
   vector<float>   *jet_antikt4h1topo_e_EMB3;
   vector<float>   *jet_antikt4h1topo_e_PreSamplerE;
   vector<float>   *jet_antikt4h1topo_e_EME1;
   vector<float>   *jet_antikt4h1topo_e_EME2;
   vector<float>   *jet_antikt4h1topo_e_EME3;
   vector<float>   *jet_antikt4h1topo_e_HEC0;
   vector<float>   *jet_antikt4h1topo_e_HEC1;
   vector<float>   *jet_antikt4h1topo_e_HEC2;
   vector<float>   *jet_antikt4h1topo_e_HEC3;
   vector<float>   *jet_antikt4h1topo_e_TileBar0;
   vector<float>   *jet_antikt4h1topo_e_TileBar1;
   vector<float>   *jet_antikt4h1topo_e_TileBar2;
   vector<float>   *jet_antikt4h1topo_e_TileGap1;
   vector<float>   *jet_antikt4h1topo_e_TileGap2;
   vector<float>   *jet_antikt4h1topo_e_TileGap3;
   vector<float>   *jet_antikt4h1topo_e_TileExt0;
   vector<float>   *jet_antikt4h1topo_e_TileExt1;
   vector<float>   *jet_antikt4h1topo_e_TileExt2;
   vector<float>   *jet_antikt4h1topo_e_FCAL0;
   vector<float>   *jet_antikt4h1topo_e_FCAL1;
   vector<float>   *jet_antikt4h1topo_e_FCAL2;
   vector<vector<float> > *jet_antikt4h1topo_shapeBins;
   vector<double>  *jet_antikt4h1topo_flavor_component_ip2d_pu;
   vector<double>  *jet_antikt4h1topo_flavor_component_ip2d_pb;
   vector<double>  *jet_antikt4h1topo_flavor_component_ip2d_ntrk;
   vector<double>  *jet_antikt4h1topo_flavor_component_ip3d_pu;
   vector<double>  *jet_antikt4h1topo_flavor_component_ip3d_pb;
   vector<double>  *jet_antikt4h1topo_flavor_component_ip3d_ntrk;
   vector<double>  *jet_antikt4h1topo_flavor_component_sv1_pu;
   vector<double>  *jet_antikt4h1topo_flavor_component_sv1_pb;
   vector<double>  *jet_antikt4h1topo_flavor_component_sv2_pu;
   vector<double>  *jet_antikt4h1topo_flavor_component_sv2_pb;
   vector<double>  *jet_antikt4h1topo_flavor_component_svp_mass;
   vector<double>  *jet_antikt4h1topo_flavor_component_svp_n2t;
   vector<double>  *jet_antikt4h1topo_flavor_component_svp_svok;
   vector<double>  *jet_antikt4h1topo_flavor_component_svp_ntrk;
   vector<double>  *jet_antikt4h1topo_flavor_component_svp_ntrkv;
   vector<double>  *jet_antikt4h1topo_flavor_component_svp_ntrkj;
   vector<double>  *jet_antikt4h1topo_flavor_component_svp_efrc;
   vector<double>  *jet_antikt4h1topo_flavor_component_sv0p_mass;
   vector<double>  *jet_antikt4h1topo_flavor_component_sv0p_n2t;
   vector<double>  *jet_antikt4h1topo_flavor_component_sv0p_svok;
   vector<double>  *jet_antikt4h1topo_flavor_component_sv0p_ntrk;
   vector<double>  *jet_antikt4h1topo_flavor_component_sv0p_ntrkv;
   vector<double>  *jet_antikt4h1topo_flavor_component_sv0p_ntrkj;
   vector<double>  *jet_antikt4h1topo_flavor_component_sv0p_efrc;
   vector<double>  *jet_antikt4h1topo_flavor_component_jfit_pu;
   vector<double>  *jet_antikt4h1topo_flavor_component_jfit_pb;
   vector<double>  *jet_antikt4h1topo_flavor_component_jfit_nvtxnt;
   vector<double>  *jet_antikt4h1topo_flavor_component_jfit_nvtx1t;
   vector<double>  *jet_antikt4h1topo_flavor_component_jfit_ntrk;
   vector<double>  *jet_antikt4h1topo_flavor_component_jfit_efrc;
   vector<double>  *jet_antikt4h1topo_flavor_component_jfit_mass;
   vector<double>  *jet_antikt4h1topo_flavor_component_jfit_sig3d;
   vector<float>   *jet_antikt4h1topo_constscale_E;
   vector<float>   *jet_antikt4h1topo_constscale_pt;
   vector<float>   *jet_antikt4h1topo_constscale_m;
   vector<float>   *jet_antikt4h1topo_constscale_eta;
   vector<float>   *jet_antikt4h1topo_constscale_phi;
   vector<float>   *jet_antikt4h1topo_el_dr;
   vector<int>     *jet_antikt4h1topo_el_matched;
   vector<float>   *jet_antikt4h1topo_mu_dr;
   vector<int>     *jet_antikt4h1topo_mu_matched;
   Int_t           jet_antikt4h1tower_n;
   vector<float>   *jet_antikt4h1tower_E;
   vector<float>   *jet_antikt4h1tower_pt;
   vector<float>   *jet_antikt4h1tower_m;
   vector<float>   *jet_antikt4h1tower_eta;
   vector<float>   *jet_antikt4h1tower_phi;
   vector<float>   *jet_antikt4h1tower_EtaPhys;
   vector<float>   *jet_antikt4h1tower_PhiPhys;
   vector<float>   *jet_antikt4h1tower_MPhys;
   vector<float>   *jet_antikt4h1tower_WIDTH;
   vector<float>   *jet_antikt4h1tower_n90;
   vector<float>   *jet_antikt4h1tower_n90constituents;
   vector<float>   *jet_antikt4h1tower_fracSamplingMax;
   vector<float>   *jet_antikt4h1tower_SamplingMax;
   vector<float>   *jet_antikt4h1tower_BCH_CORR_CELL;
   vector<float>   *jet_antikt4h1tower_BCH_CORR_DOTX;
   vector<float>   *jet_antikt4h1tower_BCH_CORR_JET;
   vector<float>   *jet_antikt4h1tower_BCH_CORR_JET_FORCELL;
   vector<float>   *jet_antikt4h1tower_ENG_BAD_CELLS;
   vector<float>   *jet_antikt4h1tower_N_BAD_CELLS;
   vector<float>   *jet_antikt4h1tower_N_BAD_CELLS_CORR;
   vector<float>   *jet_antikt4h1tower_BAD_CELLS_CORR_E;
   vector<float>   *jet_antikt4h1tower_hecf;
   vector<float>   *jet_antikt4h1tower_tgap3f;
   vector<int>     *jet_antikt4h1tower_isGood;
   vector<float>   *jet_antikt4h1tower_timing;
   vector<float>   *jet_antikt4h1tower_quality;
   vector<float>   *jet_antikt4h1tower_emfrac;
   vector<float>   *jet_antikt4h1tower_GCWJES;
   vector<float>   *jet_antikt4h1tower_EMJES;
   vector<float>   *jet_antikt4h1tower_CB;
   vector<float>   *jet_antikt4h1tower_emscale_E;
   vector<float>   *jet_antikt4h1tower_emscale_pt;
   vector<float>   *jet_antikt4h1tower_emscale_m;
   vector<float>   *jet_antikt4h1tower_emscale_eta;
   vector<float>   *jet_antikt4h1tower_emscale_phi;
   vector<float>   *jet_antikt4h1tower_jvtxf;
   vector<float>   *jet_antikt4h1tower_jvtx_x;
   vector<float>   *jet_antikt4h1tower_jvtx_y;
   vector<float>   *jet_antikt4h1tower_jvtx_z;
   vector<double>  *jet_antikt4h1tower_flavor_weight;
   vector<double>  *jet_antikt4h1tower_flavor_weight_TrackCounting2D;
   vector<double>  *jet_antikt4h1tower_flavor_weight_JetProb;
   vector<double>  *jet_antikt4h1tower_flavor_weight_IP1D;
   vector<double>  *jet_antikt4h1tower_flavor_weight_IP2D;
   vector<double>  *jet_antikt4h1tower_flavor_weight_IP3D;
   vector<double>  *jet_antikt4h1tower_flavor_weight_SV0;
   vector<double>  *jet_antikt4h1tower_flavor_weight_SV1;
   vector<double>  *jet_antikt4h1tower_flavor_weight_SV2;
   vector<double>  *jet_antikt4h1tower_flavor_weight_JetFitterTag;
   vector<double>  *jet_antikt4h1tower_flavor_weight_JetFitterCOMB;
   vector<double>  *jet_antikt4h1tower_flavor_weight_JetFitterTagNN;
   vector<double>  *jet_antikt4h1tower_flavor_weight_JetFitterCOMBNN;
   vector<double>  *jet_antikt4h1tower_flavor_weight_SoftMuonTag;
   vector<double>  *jet_antikt4h1tower_flavor_weight_SoftElectronTag;
   vector<float>   *jet_antikt4h1tower_e_PreSamplerB;
   vector<float>   *jet_antikt4h1tower_e_EMB1;
   vector<float>   *jet_antikt4h1tower_e_EMB2;
   vector<float>   *jet_antikt4h1tower_e_EMB3;
   vector<float>   *jet_antikt4h1tower_e_PreSamplerE;
   vector<float>   *jet_antikt4h1tower_e_EME1;
   vector<float>   *jet_antikt4h1tower_e_EME2;
   vector<float>   *jet_antikt4h1tower_e_EME3;
   vector<float>   *jet_antikt4h1tower_e_HEC0;
   vector<float>   *jet_antikt4h1tower_e_HEC1;
   vector<float>   *jet_antikt4h1tower_e_HEC2;
   vector<float>   *jet_antikt4h1tower_e_HEC3;
   vector<float>   *jet_antikt4h1tower_e_TileBar0;
   vector<float>   *jet_antikt4h1tower_e_TileBar1;
   vector<float>   *jet_antikt4h1tower_e_TileBar2;
   vector<float>   *jet_antikt4h1tower_e_TileGap1;
   vector<float>   *jet_antikt4h1tower_e_TileGap2;
   vector<float>   *jet_antikt4h1tower_e_TileGap3;
   vector<float>   *jet_antikt4h1tower_e_TileExt0;
   vector<float>   *jet_antikt4h1tower_e_TileExt1;
   vector<float>   *jet_antikt4h1tower_e_TileExt2;
   vector<float>   *jet_antikt4h1tower_e_FCAL0;
   vector<float>   *jet_antikt4h1tower_e_FCAL1;
   vector<float>   *jet_antikt4h1tower_e_FCAL2;
   vector<vector<float> > *jet_antikt4h1tower_shapeBins;
   vector<double>  *jet_antikt4h1tower_flavor_component_ip2d_pu;
   vector<double>  *jet_antikt4h1tower_flavor_component_ip2d_pb;
   vector<double>  *jet_antikt4h1tower_flavor_component_ip2d_ntrk;
   vector<double>  *jet_antikt4h1tower_flavor_component_ip3d_pu;
   vector<double>  *jet_antikt4h1tower_flavor_component_ip3d_pb;
   vector<double>  *jet_antikt4h1tower_flavor_component_ip3d_ntrk;
   vector<double>  *jet_antikt4h1tower_flavor_component_sv1_pu;
   vector<double>  *jet_antikt4h1tower_flavor_component_sv1_pb;
   vector<double>  *jet_antikt4h1tower_flavor_component_sv2_pu;
   vector<double>  *jet_antikt4h1tower_flavor_component_sv2_pb;
   vector<double>  *jet_antikt4h1tower_flavor_component_svp_mass;
   vector<double>  *jet_antikt4h1tower_flavor_component_svp_n2t;
   vector<double>  *jet_antikt4h1tower_flavor_component_svp_svok;
   vector<double>  *jet_antikt4h1tower_flavor_component_svp_ntrk;
   vector<double>  *jet_antikt4h1tower_flavor_component_svp_ntrkv;
   vector<double>  *jet_antikt4h1tower_flavor_component_svp_ntrkj;
   vector<double>  *jet_antikt4h1tower_flavor_component_svp_efrc;
   vector<double>  *jet_antikt4h1tower_flavor_component_sv0p_mass;
   vector<double>  *jet_antikt4h1tower_flavor_component_sv0p_n2t;
   vector<double>  *jet_antikt4h1tower_flavor_component_sv0p_svok;
   vector<double>  *jet_antikt4h1tower_flavor_component_sv0p_ntrk;
   vector<double>  *jet_antikt4h1tower_flavor_component_sv0p_ntrkv;
   vector<double>  *jet_antikt4h1tower_flavor_component_sv0p_ntrkj;
   vector<double>  *jet_antikt4h1tower_flavor_component_sv0p_efrc;
   vector<double>  *jet_antikt4h1tower_flavor_component_jfit_pu;
   vector<double>  *jet_antikt4h1tower_flavor_component_jfit_pb;
   vector<double>  *jet_antikt4h1tower_flavor_component_jfit_nvtxnt;
   vector<double>  *jet_antikt4h1tower_flavor_component_jfit_nvtx1t;
   vector<double>  *jet_antikt4h1tower_flavor_component_jfit_ntrk;
   vector<double>  *jet_antikt4h1tower_flavor_component_jfit_efrc;
   vector<double>  *jet_antikt4h1tower_flavor_component_jfit_mass;
   vector<double>  *jet_antikt4h1tower_flavor_component_jfit_sig3d;
   vector<float>   *jet_antikt4h1tower_constscale_E;
   vector<float>   *jet_antikt4h1tower_constscale_pt;
   vector<float>   *jet_antikt4h1tower_constscale_m;
   vector<float>   *jet_antikt4h1tower_constscale_eta;
   vector<float>   *jet_antikt4h1tower_constscale_phi;
   vector<float>   *jet_antikt4h1tower_el_dr;
   vector<int>     *jet_antikt4h1tower_el_matched;
   vector<float>   *jet_antikt4h1tower_mu_dr;
   vector<int>     *jet_antikt4h1tower_mu_matched;
   Int_t           jet_antikt6h1tower_n;
   vector<float>   *jet_antikt6h1tower_E;
   vector<float>   *jet_antikt6h1tower_pt;
   vector<float>   *jet_antikt6h1tower_m;
   vector<float>   *jet_antikt6h1tower_eta;
   vector<float>   *jet_antikt6h1tower_phi;
   vector<float>   *jet_antikt6h1tower_EtaPhys;
   vector<float>   *jet_antikt6h1tower_PhiPhys;
   vector<float>   *jet_antikt6h1tower_MPhys;
   vector<float>   *jet_antikt6h1tower_WIDTH;
   vector<float>   *jet_antikt6h1tower_n90;
   vector<float>   *jet_antikt6h1tower_n90constituents;
   vector<float>   *jet_antikt6h1tower_fracSamplingMax;
   vector<float>   *jet_antikt6h1tower_SamplingMax;
   vector<float>   *jet_antikt6h1tower_BCH_CORR_CELL;
   vector<float>   *jet_antikt6h1tower_BCH_CORR_DOTX;
   vector<float>   *jet_antikt6h1tower_BCH_CORR_JET;
   vector<float>   *jet_antikt6h1tower_BCH_CORR_JET_FORCELL;
   vector<float>   *jet_antikt6h1tower_ENG_BAD_CELLS;
   vector<float>   *jet_antikt6h1tower_N_BAD_CELLS;
   vector<float>   *jet_antikt6h1tower_N_BAD_CELLS_CORR;
   vector<float>   *jet_antikt6h1tower_BAD_CELLS_CORR_E;
   vector<float>   *jet_antikt6h1tower_hecf;
   vector<float>   *jet_antikt6h1tower_tgap3f;
   vector<int>     *jet_antikt6h1tower_isGood;
   vector<float>   *jet_antikt6h1tower_timing;
   vector<float>   *jet_antikt6h1tower_quality;
   vector<float>   *jet_antikt6h1tower_emfrac;
   vector<float>   *jet_antikt6h1tower_GCWJES;
   vector<float>   *jet_antikt6h1tower_EMJES;
   vector<float>   *jet_antikt6h1tower_CB;
   vector<float>   *jet_antikt6h1tower_emscale_E;
   vector<float>   *jet_antikt6h1tower_emscale_pt;
   vector<float>   *jet_antikt6h1tower_emscale_m;
   vector<float>   *jet_antikt6h1tower_emscale_eta;
   vector<float>   *jet_antikt6h1tower_emscale_phi;
   vector<float>   *jet_antikt6h1tower_jvtxf;
   vector<float>   *jet_antikt6h1tower_jvtx_x;
   vector<float>   *jet_antikt6h1tower_jvtx_y;
   vector<float>   *jet_antikt6h1tower_jvtx_z;
   vector<double>  *jet_antikt6h1tower_flavor_weight;
   vector<double>  *jet_antikt6h1tower_flavor_weight_TrackCounting2D;
   vector<double>  *jet_antikt6h1tower_flavor_weight_JetProb;
   vector<double>  *jet_antikt6h1tower_flavor_weight_IP1D;
   vector<double>  *jet_antikt6h1tower_flavor_weight_IP2D;
   vector<double>  *jet_antikt6h1tower_flavor_weight_IP3D;
   vector<double>  *jet_antikt6h1tower_flavor_weight_SV0;
   vector<double>  *jet_antikt6h1tower_flavor_weight_SV1;
   vector<double>  *jet_antikt6h1tower_flavor_weight_SV2;
   vector<double>  *jet_antikt6h1tower_flavor_weight_JetFitterTag;
   vector<double>  *jet_antikt6h1tower_flavor_weight_JetFitterCOMB;
   vector<double>  *jet_antikt6h1tower_flavor_weight_JetFitterTagNN;
   vector<double>  *jet_antikt6h1tower_flavor_weight_JetFitterCOMBNN;
   vector<double>  *jet_antikt6h1tower_flavor_weight_SoftMuonTag;
   vector<double>  *jet_antikt6h1tower_flavor_weight_SoftElectronTag;
   vector<float>   *jet_antikt6h1tower_e_PreSamplerB;
   vector<float>   *jet_antikt6h1tower_e_EMB1;
   vector<float>   *jet_antikt6h1tower_e_EMB2;
   vector<float>   *jet_antikt6h1tower_e_EMB3;
   vector<float>   *jet_antikt6h1tower_e_PreSamplerE;
   vector<float>   *jet_antikt6h1tower_e_EME1;
   vector<float>   *jet_antikt6h1tower_e_EME2;
   vector<float>   *jet_antikt6h1tower_e_EME3;
   vector<float>   *jet_antikt6h1tower_e_HEC0;
   vector<float>   *jet_antikt6h1tower_e_HEC1;
   vector<float>   *jet_antikt6h1tower_e_HEC2;
   vector<float>   *jet_antikt6h1tower_e_HEC3;
   vector<float>   *jet_antikt6h1tower_e_TileBar0;
   vector<float>   *jet_antikt6h1tower_e_TileBar1;
   vector<float>   *jet_antikt6h1tower_e_TileBar2;
   vector<float>   *jet_antikt6h1tower_e_TileGap1;
   vector<float>   *jet_antikt6h1tower_e_TileGap2;
   vector<float>   *jet_antikt6h1tower_e_TileGap3;
   vector<float>   *jet_antikt6h1tower_e_TileExt0;
   vector<float>   *jet_antikt6h1tower_e_TileExt1;
   vector<float>   *jet_antikt6h1tower_e_TileExt2;
   vector<float>   *jet_antikt6h1tower_e_FCAL0;
   vector<float>   *jet_antikt6h1tower_e_FCAL1;
   vector<float>   *jet_antikt6h1tower_e_FCAL2;
   vector<vector<float> > *jet_antikt6h1tower_shapeBins;
   vector<double>  *jet_antikt6h1tower_flavor_component_ip2d_pu;
   vector<double>  *jet_antikt6h1tower_flavor_component_ip2d_pb;
   vector<double>  *jet_antikt6h1tower_flavor_component_ip2d_ntrk;
   vector<double>  *jet_antikt6h1tower_flavor_component_ip3d_pu;
   vector<double>  *jet_antikt6h1tower_flavor_component_ip3d_pb;
   vector<double>  *jet_antikt6h1tower_flavor_component_ip3d_ntrk;
   vector<double>  *jet_antikt6h1tower_flavor_component_sv1_pu;
   vector<double>  *jet_antikt6h1tower_flavor_component_sv1_pb;
   vector<double>  *jet_antikt6h1tower_flavor_component_sv2_pu;
   vector<double>  *jet_antikt6h1tower_flavor_component_sv2_pb;
   vector<double>  *jet_antikt6h1tower_flavor_component_svp_mass;
   vector<double>  *jet_antikt6h1tower_flavor_component_svp_n2t;
   vector<double>  *jet_antikt6h1tower_flavor_component_svp_svok;
   vector<double>  *jet_antikt6h1tower_flavor_component_svp_ntrk;
   vector<double>  *jet_antikt6h1tower_flavor_component_svp_ntrkv;
   vector<double>  *jet_antikt6h1tower_flavor_component_svp_ntrkj;
   vector<double>  *jet_antikt6h1tower_flavor_component_svp_efrc;
   vector<double>  *jet_antikt6h1tower_flavor_component_sv0p_mass;
   vector<double>  *jet_antikt6h1tower_flavor_component_sv0p_n2t;
   vector<double>  *jet_antikt6h1tower_flavor_component_sv0p_svok;
   vector<double>  *jet_antikt6h1tower_flavor_component_sv0p_ntrk;
   vector<double>  *jet_antikt6h1tower_flavor_component_sv0p_ntrkv;
   vector<double>  *jet_antikt6h1tower_flavor_component_sv0p_ntrkj;
   vector<double>  *jet_antikt6h1tower_flavor_component_sv0p_efrc;
   vector<double>  *jet_antikt6h1tower_flavor_component_jfit_pu;
   vector<double>  *jet_antikt6h1tower_flavor_component_jfit_pb;
   vector<double>  *jet_antikt6h1tower_flavor_component_jfit_nvtxnt;
   vector<double>  *jet_antikt6h1tower_flavor_component_jfit_nvtx1t;
   vector<double>  *jet_antikt6h1tower_flavor_component_jfit_ntrk;
   vector<double>  *jet_antikt6h1tower_flavor_component_jfit_efrc;
   vector<double>  *jet_antikt6h1tower_flavor_component_jfit_mass;
   vector<double>  *jet_antikt6h1tower_flavor_component_jfit_sig3d;
   vector<float>   *jet_antikt6h1tower_constscale_E;
   vector<float>   *jet_antikt6h1tower_constscale_pt;
   vector<float>   *jet_antikt6h1tower_constscale_m;
   vector<float>   *jet_antikt6h1tower_constscale_eta;
   vector<float>   *jet_antikt6h1tower_constscale_phi;
   vector<float>   *jet_antikt6h1tower_el_dr;
   vector<int>     *jet_antikt6h1tower_el_matched;
   vector<float>   *jet_antikt6h1tower_mu_dr;
   vector<int>     *jet_antikt6h1tower_mu_matched;
   Int_t           jet_antikt4lctopo_n;
   vector<float>   *jet_antikt4lctopo_E;
   vector<float>   *jet_antikt4lctopo_pt;
   vector<float>   *jet_antikt4lctopo_m;
   vector<float>   *jet_antikt4lctopo_eta;
   vector<float>   *jet_antikt4lctopo_phi;
   vector<float>   *jet_antikt4lctopo_EtaPhys;
   vector<float>   *jet_antikt4lctopo_PhiPhys;
   vector<float>   *jet_antikt4lctopo_MPhys;
   vector<float>   *jet_antikt4lctopo_WIDTH;
   vector<float>   *jet_antikt4lctopo_n90;
   vector<float>   *jet_antikt4lctopo_n90constituents;
   vector<float>   *jet_antikt4lctopo_fracSamplingMax;
   vector<float>   *jet_antikt4lctopo_SamplingMax;
   vector<float>   *jet_antikt4lctopo_BCH_CORR_CELL;
   vector<float>   *jet_antikt4lctopo_BCH_CORR_DOTX;
   vector<float>   *jet_antikt4lctopo_BCH_CORR_JET;
   vector<float>   *jet_antikt4lctopo_BCH_CORR_JET_FORCELL;
   vector<float>   *jet_antikt4lctopo_ENG_BAD_CELLS;
   vector<float>   *jet_antikt4lctopo_N_BAD_CELLS;
   vector<float>   *jet_antikt4lctopo_N_BAD_CELLS_CORR;
   vector<float>   *jet_antikt4lctopo_BAD_CELLS_CORR_E;
   vector<float>   *jet_antikt4lctopo_hecf;
   vector<float>   *jet_antikt4lctopo_tgap3f;
   vector<int>     *jet_antikt4lctopo_isGood;
   vector<float>   *jet_antikt4lctopo_timing;
   vector<float>   *jet_antikt4lctopo_quality;
   vector<float>   *jet_antikt4lctopo_emfrac;
   vector<float>   *jet_antikt4lctopo_GCWJES;
   vector<float>   *jet_antikt4lctopo_EMJES;
   vector<float>   *jet_antikt4lctopo_CB;
   vector<float>   *jet_antikt4lctopo_emscale_E;
   vector<float>   *jet_antikt4lctopo_emscale_pt;
   vector<float>   *jet_antikt4lctopo_emscale_m;
   vector<float>   *jet_antikt4lctopo_emscale_eta;
   vector<float>   *jet_antikt4lctopo_emscale_phi;
   vector<float>   *jet_antikt4lctopo_jvtxf;
   vector<float>   *jet_antikt4lctopo_jvtx_x;
   vector<float>   *jet_antikt4lctopo_jvtx_y;
   vector<float>   *jet_antikt4lctopo_jvtx_z;
   vector<double>  *jet_antikt4lctopo_flavor_weight;
   vector<double>  *jet_antikt4lctopo_flavor_weight_TrackCounting2D;
   vector<double>  *jet_antikt4lctopo_flavor_weight_JetProb;
   vector<double>  *jet_antikt4lctopo_flavor_weight_IP1D;
   vector<double>  *jet_antikt4lctopo_flavor_weight_IP2D;
   vector<double>  *jet_antikt4lctopo_flavor_weight_IP3D;
   vector<double>  *jet_antikt4lctopo_flavor_weight_SV0;
   vector<double>  *jet_antikt4lctopo_flavor_weight_SV1;
   vector<double>  *jet_antikt4lctopo_flavor_weight_SV2;
   vector<double>  *jet_antikt4lctopo_flavor_weight_JetFitterTag;
   vector<double>  *jet_antikt4lctopo_flavor_weight_JetFitterCOMB;
   vector<double>  *jet_antikt4lctopo_flavor_weight_JetFitterTagNN;
   vector<double>  *jet_antikt4lctopo_flavor_weight_JetFitterCOMBNN;
   vector<double>  *jet_antikt4lctopo_flavor_weight_SoftMuonTag;
   vector<double>  *jet_antikt4lctopo_flavor_weight_SoftElectronTag;
   vector<float>   *jet_antikt4lctopo_e_PreSamplerB;
   vector<float>   *jet_antikt4lctopo_e_EMB1;
   vector<float>   *jet_antikt4lctopo_e_EMB2;
   vector<float>   *jet_antikt4lctopo_e_EMB3;
   vector<float>   *jet_antikt4lctopo_e_PreSamplerE;
   vector<float>   *jet_antikt4lctopo_e_EME1;
   vector<float>   *jet_antikt4lctopo_e_EME2;
   vector<float>   *jet_antikt4lctopo_e_EME3;
   vector<float>   *jet_antikt4lctopo_e_HEC0;
   vector<float>   *jet_antikt4lctopo_e_HEC1;
   vector<float>   *jet_antikt4lctopo_e_HEC2;
   vector<float>   *jet_antikt4lctopo_e_HEC3;
   vector<float>   *jet_antikt4lctopo_e_TileBar0;
   vector<float>   *jet_antikt4lctopo_e_TileBar1;
   vector<float>   *jet_antikt4lctopo_e_TileBar2;
   vector<float>   *jet_antikt4lctopo_e_TileGap1;
   vector<float>   *jet_antikt4lctopo_e_TileGap2;
   vector<float>   *jet_antikt4lctopo_e_TileGap3;
   vector<float>   *jet_antikt4lctopo_e_TileExt0;
   vector<float>   *jet_antikt4lctopo_e_TileExt1;
   vector<float>   *jet_antikt4lctopo_e_TileExt2;
   vector<float>   *jet_antikt4lctopo_e_FCAL0;
   vector<float>   *jet_antikt4lctopo_e_FCAL1;
   vector<float>   *jet_antikt4lctopo_e_FCAL2;
   vector<vector<float> > *jet_antikt4lctopo_shapeBins;
   vector<double>  *jet_antikt4lctopo_flavor_component_ip2d_pu;
   vector<double>  *jet_antikt4lctopo_flavor_component_ip2d_pb;
   vector<double>  *jet_antikt4lctopo_flavor_component_ip2d_ntrk;
   vector<double>  *jet_antikt4lctopo_flavor_component_ip3d_pu;
   vector<double>  *jet_antikt4lctopo_flavor_component_ip3d_pb;
   vector<double>  *jet_antikt4lctopo_flavor_component_ip3d_ntrk;
   vector<double>  *jet_antikt4lctopo_flavor_component_sv1_pu;
   vector<double>  *jet_antikt4lctopo_flavor_component_sv1_pb;
   vector<double>  *jet_antikt4lctopo_flavor_component_sv2_pu;
   vector<double>  *jet_antikt4lctopo_flavor_component_sv2_pb;
   vector<double>  *jet_antikt4lctopo_flavor_component_svp_mass;
   vector<double>  *jet_antikt4lctopo_flavor_component_svp_n2t;
   vector<double>  *jet_antikt4lctopo_flavor_component_svp_svok;
   vector<double>  *jet_antikt4lctopo_flavor_component_svp_ntrk;
   vector<double>  *jet_antikt4lctopo_flavor_component_svp_ntrkv;
   vector<double>  *jet_antikt4lctopo_flavor_component_svp_ntrkj;
   vector<double>  *jet_antikt4lctopo_flavor_component_svp_efrc;
   vector<double>  *jet_antikt4lctopo_flavor_component_sv0p_mass;
   vector<double>  *jet_antikt4lctopo_flavor_component_sv0p_n2t;
   vector<double>  *jet_antikt4lctopo_flavor_component_sv0p_svok;
   vector<double>  *jet_antikt4lctopo_flavor_component_sv0p_ntrk;
   vector<double>  *jet_antikt4lctopo_flavor_component_sv0p_ntrkv;
   vector<double>  *jet_antikt4lctopo_flavor_component_sv0p_ntrkj;
   vector<double>  *jet_antikt4lctopo_flavor_component_sv0p_efrc;
   vector<double>  *jet_antikt4lctopo_flavor_component_jfit_pu;
   vector<double>  *jet_antikt4lctopo_flavor_component_jfit_pb;
   vector<double>  *jet_antikt4lctopo_flavor_component_jfit_nvtxnt;
   vector<double>  *jet_antikt4lctopo_flavor_component_jfit_nvtx1t;
   vector<double>  *jet_antikt4lctopo_flavor_component_jfit_ntrk;
   vector<double>  *jet_antikt4lctopo_flavor_component_jfit_efrc;
   vector<double>  *jet_antikt4lctopo_flavor_component_jfit_mass;
   vector<double>  *jet_antikt4lctopo_flavor_component_jfit_sig3d;
   vector<float>   *jet_antikt4lctopo_constscale_E;
   vector<float>   *jet_antikt4lctopo_constscale_pt;
   vector<float>   *jet_antikt4lctopo_constscale_m;
   vector<float>   *jet_antikt4lctopo_constscale_eta;
   vector<float>   *jet_antikt4lctopo_constscale_phi;
   vector<float>   *jet_antikt4lctopo_el_dr;
   vector<int>     *jet_antikt4lctopo_el_matched;
   vector<float>   *jet_antikt4lctopo_mu_dr;
   vector<int>     *jet_antikt4lctopo_mu_matched;
   Int_t           jet_antikt6lctopo_n;
   vector<float>   *jet_antikt6lctopo_E;
   vector<float>   *jet_antikt6lctopo_pt;
   vector<float>   *jet_antikt6lctopo_m;
   vector<float>   *jet_antikt6lctopo_eta;
   vector<float>   *jet_antikt6lctopo_phi;
   vector<float>   *jet_antikt6lctopo_EtaPhys;
   vector<float>   *jet_antikt6lctopo_PhiPhys;
   vector<float>   *jet_antikt6lctopo_MPhys;
   vector<float>   *jet_antikt6lctopo_WIDTH;
   vector<float>   *jet_antikt6lctopo_n90;
   vector<float>   *jet_antikt6lctopo_n90constituents;
   vector<float>   *jet_antikt6lctopo_fracSamplingMax;
   vector<float>   *jet_antikt6lctopo_SamplingMax;
   vector<float>   *jet_antikt6lctopo_BCH_CORR_CELL;
   vector<float>   *jet_antikt6lctopo_BCH_CORR_DOTX;
   vector<float>   *jet_antikt6lctopo_BCH_CORR_JET;
   vector<float>   *jet_antikt6lctopo_BCH_CORR_JET_FORCELL;
   vector<float>   *jet_antikt6lctopo_ENG_BAD_CELLS;
   vector<float>   *jet_antikt6lctopo_N_BAD_CELLS;
   vector<float>   *jet_antikt6lctopo_N_BAD_CELLS_CORR;
   vector<float>   *jet_antikt6lctopo_BAD_CELLS_CORR_E;
   vector<float>   *jet_antikt6lctopo_hecf;
   vector<float>   *jet_antikt6lctopo_tgap3f;
   vector<int>     *jet_antikt6lctopo_isGood;
   vector<float>   *jet_antikt6lctopo_timing;
   vector<float>   *jet_antikt6lctopo_quality;
   vector<float>   *jet_antikt6lctopo_emfrac;
   vector<float>   *jet_antikt6lctopo_GCWJES;
   vector<float>   *jet_antikt6lctopo_EMJES;
   vector<float>   *jet_antikt6lctopo_CB;
   vector<float>   *jet_antikt6lctopo_emscale_E;
   vector<float>   *jet_antikt6lctopo_emscale_pt;
   vector<float>   *jet_antikt6lctopo_emscale_m;
   vector<float>   *jet_antikt6lctopo_emscale_eta;
   vector<float>   *jet_antikt6lctopo_emscale_phi;
   vector<float>   *jet_antikt6lctopo_jvtxf;
   vector<float>   *jet_antikt6lctopo_jvtx_x;
   vector<float>   *jet_antikt6lctopo_jvtx_y;
   vector<float>   *jet_antikt6lctopo_jvtx_z;
   vector<double>  *jet_antikt6lctopo_flavor_weight;
   vector<double>  *jet_antikt6lctopo_flavor_weight_TrackCounting2D;
   vector<double>  *jet_antikt6lctopo_flavor_weight_JetProb;
   vector<double>  *jet_antikt6lctopo_flavor_weight_IP1D;
   vector<double>  *jet_antikt6lctopo_flavor_weight_IP2D;
   vector<double>  *jet_antikt6lctopo_flavor_weight_IP3D;
   vector<double>  *jet_antikt6lctopo_flavor_weight_SV0;
   vector<double>  *jet_antikt6lctopo_flavor_weight_SV1;
   vector<double>  *jet_antikt6lctopo_flavor_weight_SV2;
   vector<double>  *jet_antikt6lctopo_flavor_weight_JetFitterTag;
   vector<double>  *jet_antikt6lctopo_flavor_weight_JetFitterCOMB;
   vector<double>  *jet_antikt6lctopo_flavor_weight_JetFitterTagNN;
   vector<double>  *jet_antikt6lctopo_flavor_weight_JetFitterCOMBNN;
   vector<double>  *jet_antikt6lctopo_flavor_weight_SoftMuonTag;
   vector<double>  *jet_antikt6lctopo_flavor_weight_SoftElectronTag;
   vector<float>   *jet_antikt6lctopo_e_PreSamplerB;
   vector<float>   *jet_antikt6lctopo_e_EMB1;
   vector<float>   *jet_antikt6lctopo_e_EMB2;
   vector<float>   *jet_antikt6lctopo_e_EMB3;
   vector<float>   *jet_antikt6lctopo_e_PreSamplerE;
   vector<float>   *jet_antikt6lctopo_e_EME1;
   vector<float>   *jet_antikt6lctopo_e_EME2;
   vector<float>   *jet_antikt6lctopo_e_EME3;
   vector<float>   *jet_antikt6lctopo_e_HEC0;
   vector<float>   *jet_antikt6lctopo_e_HEC1;
   vector<float>   *jet_antikt6lctopo_e_HEC2;
   vector<float>   *jet_antikt6lctopo_e_HEC3;
   vector<float>   *jet_antikt6lctopo_e_TileBar0;
   vector<float>   *jet_antikt6lctopo_e_TileBar1;
   vector<float>   *jet_antikt6lctopo_e_TileBar2;
   vector<float>   *jet_antikt6lctopo_e_TileGap1;
   vector<float>   *jet_antikt6lctopo_e_TileGap2;
   vector<float>   *jet_antikt6lctopo_e_TileGap3;
   vector<float>   *jet_antikt6lctopo_e_TileExt0;
   vector<float>   *jet_antikt6lctopo_e_TileExt1;
   vector<float>   *jet_antikt6lctopo_e_TileExt2;
   vector<float>   *jet_antikt6lctopo_e_FCAL0;
   vector<float>   *jet_antikt6lctopo_e_FCAL1;
   vector<float>   *jet_antikt6lctopo_e_FCAL2;
   vector<vector<float> > *jet_antikt6lctopo_shapeBins;
   vector<double>  *jet_antikt6lctopo_flavor_component_ip2d_pu;
   vector<double>  *jet_antikt6lctopo_flavor_component_ip2d_pb;
   vector<double>  *jet_antikt6lctopo_flavor_component_ip2d_ntrk;
   vector<double>  *jet_antikt6lctopo_flavor_component_ip3d_pu;
   vector<double>  *jet_antikt6lctopo_flavor_component_ip3d_pb;
   vector<double>  *jet_antikt6lctopo_flavor_component_ip3d_ntrk;
   vector<double>  *jet_antikt6lctopo_flavor_component_sv1_pu;
   vector<double>  *jet_antikt6lctopo_flavor_component_sv1_pb;
   vector<double>  *jet_antikt6lctopo_flavor_component_sv2_pu;
   vector<double>  *jet_antikt6lctopo_flavor_component_sv2_pb;
   vector<double>  *jet_antikt6lctopo_flavor_component_svp_mass;
   vector<double>  *jet_antikt6lctopo_flavor_component_svp_n2t;
   vector<double>  *jet_antikt6lctopo_flavor_component_svp_svok;
   vector<double>  *jet_antikt6lctopo_flavor_component_svp_ntrk;
   vector<double>  *jet_antikt6lctopo_flavor_component_svp_ntrkv;
   vector<double>  *jet_antikt6lctopo_flavor_component_svp_ntrkj;
   vector<double>  *jet_antikt6lctopo_flavor_component_svp_efrc;
   vector<double>  *jet_antikt6lctopo_flavor_component_sv0p_mass;
   vector<double>  *jet_antikt6lctopo_flavor_component_sv0p_n2t;
   vector<double>  *jet_antikt6lctopo_flavor_component_sv0p_svok;
   vector<double>  *jet_antikt6lctopo_flavor_component_sv0p_ntrk;
   vector<double>  *jet_antikt6lctopo_flavor_component_sv0p_ntrkv;
   vector<double>  *jet_antikt6lctopo_flavor_component_sv0p_ntrkj;
   vector<double>  *jet_antikt6lctopo_flavor_component_sv0p_efrc;
   vector<double>  *jet_antikt6lctopo_flavor_component_jfit_pu;
   vector<double>  *jet_antikt6lctopo_flavor_component_jfit_pb;
   vector<double>  *jet_antikt6lctopo_flavor_component_jfit_nvtxnt;
   vector<double>  *jet_antikt6lctopo_flavor_component_jfit_nvtx1t;
   vector<double>  *jet_antikt6lctopo_flavor_component_jfit_ntrk;
   vector<double>  *jet_antikt6lctopo_flavor_component_jfit_efrc;
   vector<double>  *jet_antikt6lctopo_flavor_component_jfit_mass;
   vector<double>  *jet_antikt6lctopo_flavor_component_jfit_sig3d;
   vector<float>   *jet_antikt6lctopo_constscale_E;
   vector<float>   *jet_antikt6lctopo_constscale_pt;
   vector<float>   *jet_antikt6lctopo_constscale_m;
   vector<float>   *jet_antikt6lctopo_constscale_eta;
   vector<float>   *jet_antikt6lctopo_constscale_phi;
   vector<float>   *jet_antikt6lctopo_el_dr;
   vector<int>     *jet_antikt6lctopo_el_matched;
   vector<float>   *jet_antikt6lctopo_mu_dr;
   vector<int>     *jet_antikt6lctopo_mu_matched;
   Int_t           jet_antikt6h1topo_n;
   vector<float>   *jet_antikt6h1topo_E;
   vector<float>   *jet_antikt6h1topo_pt;
   vector<float>   *jet_antikt6h1topo_m;
   vector<float>   *jet_antikt6h1topo_eta;
   vector<float>   *jet_antikt6h1topo_phi;
   vector<float>   *jet_antikt6h1topo_EtaPhys;
   vector<float>   *jet_antikt6h1topo_PhiPhys;
   vector<float>   *jet_antikt6h1topo_MPhys;
   vector<float>   *jet_antikt6h1topo_WIDTH;
   vector<float>   *jet_antikt6h1topo_n90;
   vector<float>   *jet_antikt6h1topo_n90constituents;
   vector<float>   *jet_antikt6h1topo_fracSamplingMax;
   vector<float>   *jet_antikt6h1topo_SamplingMax;
   vector<float>   *jet_antikt6h1topo_BCH_CORR_CELL;
   vector<float>   *jet_antikt6h1topo_BCH_CORR_DOTX;
   vector<float>   *jet_antikt6h1topo_BCH_CORR_JET;
   vector<float>   *jet_antikt6h1topo_BCH_CORR_JET_FORCELL;
   vector<float>   *jet_antikt6h1topo_ENG_BAD_CELLS;
   vector<float>   *jet_antikt6h1topo_N_BAD_CELLS;
   vector<float>   *jet_antikt6h1topo_N_BAD_CELLS_CORR;
   vector<float>   *jet_antikt6h1topo_BAD_CELLS_CORR_E;
   vector<float>   *jet_antikt6h1topo_hecf;
   vector<float>   *jet_antikt6h1topo_tgap3f;
   vector<int>     *jet_antikt6h1topo_isGood;
   vector<float>   *jet_antikt6h1topo_timing;
   vector<float>   *jet_antikt6h1topo_quality;
   vector<float>   *jet_antikt6h1topo_emfrac;
   vector<float>   *jet_antikt6h1topo_GCWJES;
   vector<float>   *jet_antikt6h1topo_EMJES;
   vector<float>   *jet_antikt6h1topo_CB;
   vector<float>   *jet_antikt6h1topo_emscale_E;
   vector<float>   *jet_antikt6h1topo_emscale_pt;
   vector<float>   *jet_antikt6h1topo_emscale_m;
   vector<float>   *jet_antikt6h1topo_emscale_eta;
   vector<float>   *jet_antikt6h1topo_emscale_phi;
   vector<float>   *jet_antikt6h1topo_jvtxf;
   vector<float>   *jet_antikt6h1topo_jvtx_x;
   vector<float>   *jet_antikt6h1topo_jvtx_y;
   vector<float>   *jet_antikt6h1topo_jvtx_z;
   vector<double>  *jet_antikt6h1topo_flavor_weight;
   vector<double>  *jet_antikt6h1topo_flavor_weight_TrackCounting2D;
   vector<double>  *jet_antikt6h1topo_flavor_weight_JetProb;
   vector<double>  *jet_antikt6h1topo_flavor_weight_IP1D;
   vector<double>  *jet_antikt6h1topo_flavor_weight_IP2D;
   vector<double>  *jet_antikt6h1topo_flavor_weight_IP3D;
   vector<double>  *jet_antikt6h1topo_flavor_weight_SV0;
   vector<double>  *jet_antikt6h1topo_flavor_weight_SV1;
   vector<double>  *jet_antikt6h1topo_flavor_weight_SV2;
   vector<double>  *jet_antikt6h1topo_flavor_weight_JetFitterTag;
   vector<double>  *jet_antikt6h1topo_flavor_weight_JetFitterCOMB;
   vector<double>  *jet_antikt6h1topo_flavor_weight_JetFitterTagNN;
   vector<double>  *jet_antikt6h1topo_flavor_weight_JetFitterCOMBNN;
   vector<double>  *jet_antikt6h1topo_flavor_weight_SoftMuonTag;
   vector<double>  *jet_antikt6h1topo_flavor_weight_SoftElectronTag;
   vector<float>   *jet_antikt6h1topo_e_PreSamplerB;
   vector<float>   *jet_antikt6h1topo_e_EMB1;
   vector<float>   *jet_antikt6h1topo_e_EMB2;
   vector<float>   *jet_antikt6h1topo_e_EMB3;
   vector<float>   *jet_antikt6h1topo_e_PreSamplerE;
   vector<float>   *jet_antikt6h1topo_e_EME1;
   vector<float>   *jet_antikt6h1topo_e_EME2;
   vector<float>   *jet_antikt6h1topo_e_EME3;
   vector<float>   *jet_antikt6h1topo_e_HEC0;
   vector<float>   *jet_antikt6h1topo_e_HEC1;
   vector<float>   *jet_antikt6h1topo_e_HEC2;
   vector<float>   *jet_antikt6h1topo_e_HEC3;
   vector<float>   *jet_antikt6h1topo_e_TileBar0;
   vector<float>   *jet_antikt6h1topo_e_TileBar1;
   vector<float>   *jet_antikt6h1topo_e_TileBar2;
   vector<float>   *jet_antikt6h1topo_e_TileGap1;
   vector<float>   *jet_antikt6h1topo_e_TileGap2;
   vector<float>   *jet_antikt6h1topo_e_TileGap3;
   vector<float>   *jet_antikt6h1topo_e_TileExt0;
   vector<float>   *jet_antikt6h1topo_e_TileExt1;
   vector<float>   *jet_antikt6h1topo_e_TileExt2;
   vector<float>   *jet_antikt6h1topo_e_FCAL0;
   vector<float>   *jet_antikt6h1topo_e_FCAL1;
   vector<float>   *jet_antikt6h1topo_e_FCAL2;
   vector<vector<float> > *jet_antikt6h1topo_shapeBins;
   vector<double>  *jet_antikt6h1topo_flavor_component_ip2d_pu;
   vector<double>  *jet_antikt6h1topo_flavor_component_ip2d_pb;
   vector<double>  *jet_antikt6h1topo_flavor_component_ip2d_ntrk;
   vector<double>  *jet_antikt6h1topo_flavor_component_ip3d_pu;
   vector<double>  *jet_antikt6h1topo_flavor_component_ip3d_pb;
   vector<double>  *jet_antikt6h1topo_flavor_component_ip3d_ntrk;
   vector<double>  *jet_antikt6h1topo_flavor_component_sv1_pu;
   vector<double>  *jet_antikt6h1topo_flavor_component_sv1_pb;
   vector<double>  *jet_antikt6h1topo_flavor_component_sv2_pu;
   vector<double>  *jet_antikt6h1topo_flavor_component_sv2_pb;
   vector<double>  *jet_antikt6h1topo_flavor_component_svp_mass;
   vector<double>  *jet_antikt6h1topo_flavor_component_svp_n2t;
   vector<double>  *jet_antikt6h1topo_flavor_component_svp_svok;
   vector<double>  *jet_antikt6h1topo_flavor_component_svp_ntrk;
   vector<double>  *jet_antikt6h1topo_flavor_component_svp_ntrkv;
   vector<double>  *jet_antikt6h1topo_flavor_component_svp_ntrkj;
   vector<double>  *jet_antikt6h1topo_flavor_component_svp_efrc;
   vector<double>  *jet_antikt6h1topo_flavor_component_sv0p_mass;
   vector<double>  *jet_antikt6h1topo_flavor_component_sv0p_n2t;
   vector<double>  *jet_antikt6h1topo_flavor_component_sv0p_svok;
   vector<double>  *jet_antikt6h1topo_flavor_component_sv0p_ntrk;
   vector<double>  *jet_antikt6h1topo_flavor_component_sv0p_ntrkv;
   vector<double>  *jet_antikt6h1topo_flavor_component_sv0p_ntrkj;
   vector<double>  *jet_antikt6h1topo_flavor_component_sv0p_efrc;
   vector<double>  *jet_antikt6h1topo_flavor_component_jfit_pu;
   vector<double>  *jet_antikt6h1topo_flavor_component_jfit_pb;
   vector<double>  *jet_antikt6h1topo_flavor_component_jfit_nvtxnt;
   vector<double>  *jet_antikt6h1topo_flavor_component_jfit_nvtx1t;
   vector<double>  *jet_antikt6h1topo_flavor_component_jfit_ntrk;
   vector<double>  *jet_antikt6h1topo_flavor_component_jfit_efrc;
   vector<double>  *jet_antikt6h1topo_flavor_component_jfit_mass;
   vector<double>  *jet_antikt6h1topo_flavor_component_jfit_sig3d;
   vector<float>   *jet_antikt6h1topo_constscale_E;
   vector<float>   *jet_antikt6h1topo_constscale_pt;
   vector<float>   *jet_antikt6h1topo_constscale_m;
   vector<float>   *jet_antikt6h1topo_constscale_eta;
   vector<float>   *jet_antikt6h1topo_constscale_phi;
   vector<float>   *jet_antikt6h1topo_el_dr;
   vector<int>     *jet_antikt6h1topo_el_matched;
   vector<float>   *jet_antikt6h1topo_mu_dr;
   vector<int>     *jet_antikt6h1topo_mu_matched;
   Float_t         MET_RefFinal_etx;
   Float_t         MET_RefFinal_ety;
   Float_t         MET_RefFinal_sumet;
   Float_t         MET_RefFinal_et;
   Float_t         MET_RefFinal_phi;
   Float_t         MET_MuonBoy_etx;
   Float_t         MET_MuonBoy_ety;
   Float_t         MET_MuonBoy_sumet;
   Float_t         MET_MuonBoy_et;
   Float_t         MET_MuonBoy_phi;
   Float_t         MET_Track_etx;
   Float_t         MET_Track_ety;
   Float_t         MET_Track_sumet;
   Float_t         MET_Track_et;
   Float_t         MET_Track_phi;
   Float_t         MET_RefGamma_etx;
   Float_t         MET_RefGamma_ety;
   Float_t         MET_RefGamma_sumet;
   Float_t         MET_RefGamma_et;
   Float_t         MET_RefGamma_phi;
   Float_t         MET_RefEle_etx;
   Float_t         MET_RefEle_ety;
   Float_t         MET_RefEle_sumet;
   Float_t         MET_RefEle_et;
   Float_t         MET_RefEle_phi;
   Float_t         MET_RefJet_etx;
   Float_t         MET_RefJet_ety;
   Float_t         MET_RefJet_sumet;
   Float_t         MET_RefJet_et;
   Float_t         MET_RefJet_phi;
   Float_t         MET_RefMuon_etx;
   Float_t         MET_RefMuon_ety;
   Float_t         MET_RefMuon_sumet;
   Float_t         MET_RefMuon_et;
   Float_t         MET_RefMuon_phi;
   Float_t         MET_RefTau_etx;
   Float_t         MET_RefTau_ety;
   Float_t         MET_RefTau_sumet;
   Float_t         MET_RefTau_et;
   Float_t         MET_RefTau_phi;
   Float_t         MET_Cryo_etx;
   Float_t         MET_Cryo_ety;
   Float_t         MET_Cryo_sumet;
   Float_t         MET_Cryo_et;
   Float_t         MET_Cryo_phi;
   Float_t         MET_CellOut_etx;
   Float_t         MET_CellOut_ety;
   Float_t         MET_CellOut_sumet;
   Float_t         MET_CellOut_et;
   Float_t         MET_CellOut_phi;
   Float_t         MET_Muid_etx;
   Float_t         MET_Muid_ety;
   Float_t         MET_Muid_sumet;
   Float_t         MET_Muid_et;
   Float_t         MET_Muid_phi;
   Float_t         MET_MuonBoyTrack_etx;
   Float_t         MET_MuonBoyTrack_ety;
   Float_t         MET_MuonBoyTrack_sumet;
   Float_t         MET_MuonBoyTrack_et;
   Float_t         MET_MuonBoyTrack_phi;
   Float_t         MET_MuonBoySpectro_etx;
   Float_t         MET_MuonBoySpectro_ety;
   Float_t         MET_MuonBoySpectro_sumet;
   Float_t         MET_MuonBoySpectro_et;
   Float_t         MET_MuonBoySpectro_phi;
   Float_t         MET_RefMuonTrack_etx;
   Float_t         MET_RefMuonTrack_ety;
   Float_t         MET_RefMuonTrack_sumet;
   Float_t         MET_RefMuonTrack_et;
   Float_t         MET_RefMuonTrack_phi;
   Float_t         MET_CryoCone_etx;
   Float_t         MET_CryoCone_ety;
   Float_t         MET_CryoCone_sumet;
   Float_t         MET_CryoCone_et;
   Float_t         MET_CryoCone_phi;
   Float_t         MET_Muon_etx;
   Float_t         MET_Muon_ety;
   Float_t         MET_Muon_sumet;
   Float_t         MET_Muon_et;
   Float_t         MET_Muon_phi;
   Float_t         MET_Final_etx;
   Float_t         MET_Final_ety;
   Float_t         MET_Final_sumet;
   Float_t         MET_Final_et;
   Float_t         MET_Final_phi;
   Float_t         MET_MuidTrack_etx;
   Float_t         MET_MuidTrack_ety;
   Float_t         MET_MuidTrack_sumet;
   Float_t         MET_MuidTrack_et;
   Float_t         MET_MuidTrack_phi;
   Float_t         MET_MuidSpectro_etx;
   Float_t         MET_MuidSpectro_ety;
   Float_t         MET_MuidSpectro_sumet;
   Float_t         MET_MuidSpectro_et;
   Float_t         MET_MuidSpectro_phi;
   Float_t         MET_MuonMuid_etx;
   Float_t         MET_MuonMuid_ety;
   Float_t         MET_MuonMuid_sumet;
   Float_t         MET_MuonMuid_et;
   Float_t         MET_MuonMuid_phi;
   Float_t         MET_TopoObj_etx;
   Float_t         MET_TopoObj_ety;
   Float_t         MET_TopoObj_sumet;
   Float_t         MET_TopoObj_et;
   Float_t         MET_TopoObj_phi;
   Float_t         MET_LocHadTopoObj_etx;
   Float_t         MET_LocHadTopoObj_ety;
   Float_t         MET_LocHadTopoObj_sumet;
   Float_t         MET_LocHadTopoObj_et;
   Float_t         MET_LocHadTopoObj_phi;
   Float_t         MET_Base_etx;
   Float_t         MET_Base_ety;
   Float_t         MET_Base_sumet;
   Float_t         MET_Base_et;
   Float_t         MET_Base_phi;
   Float_t         MET_Base_etx_PEMB;
   Float_t         MET_Base_ety_PEMB;
   Float_t         MET_Base_sumet_PEMB;
   Float_t         MET_Base_phi_PEMB;
   Float_t         MET_Base_etx_EMB;
   Float_t         MET_Base_ety_EMB;
   Float_t         MET_Base_sumet_EMB;
   Float_t         MET_Base_phi_EMB;
   Float_t         MET_Base_etx_PEMEC;
   Float_t         MET_Base_ety_PEMEC;
   Float_t         MET_Base_sumet_PEMEC;
   Float_t         MET_Base_phi_PEMEC;
   Float_t         MET_Base_etx_EME;
   Float_t         MET_Base_ety_EME;
   Float_t         MET_Base_sumet_EME;
   Float_t         MET_Base_phi_EME;
   Float_t         MET_Base_etx_TILE;
   Float_t         MET_Base_ety_TILE;
   Float_t         MET_Base_sumet_TILE;
   Float_t         MET_Base_phi_TILE;
   Float_t         MET_Base_etx_HEC;
   Float_t         MET_Base_ety_HEC;
   Float_t         MET_Base_sumet_HEC;
   Float_t         MET_Base_phi_HEC;
   Float_t         MET_Base_etx_FCAL;
   Float_t         MET_Base_ety_FCAL;
   Float_t         MET_Base_sumet_FCAL;
   Float_t         MET_Base_phi_FCAL;
   Float_t         MET_Base_nCell_PEMB;
   Float_t         MET_Base_nCell_EMB;
   Float_t         MET_Base_nCell_PEMEC;
   Float_t         MET_Base_nCell_EME;
   Float_t         MET_Base_nCell_TILE;
   Float_t         MET_Base_nCell_HEC;
   Float_t         MET_Base_nCell_FCAL;
   Float_t         MET_Base_etx_CentralReg;
   Float_t         MET_Base_ety_CentralReg;
   Float_t         MET_Base_sumet_CentralReg;
   Float_t         MET_Base_phi_CentralReg;
   Float_t         MET_Base_etx_EndcapRegion;
   Float_t         MET_Base_ety_EndcapRegion;
   Float_t         MET_Base_sumet_EndcapRegion;
   Float_t         MET_Base_phi_EndcapRegion;
   Float_t         MET_Base_etx_ForwardReg;
   Float_t         MET_Base_ety_ForwardReg;
   Float_t         MET_Base_sumet_ForwardReg;
   Float_t         MET_Base_phi_ForwardReg;
   Float_t         MET_Base_SUMET_EMFrac;
   Float_t         MET_Base0_etx;
   Float_t         MET_Base0_ety;
   Float_t         MET_Base0_sumet;
   Float_t         MET_Base0_et;
   Float_t         MET_Base0_phi;
   Float_t         MET_Base0_etx_PEMB;
   Float_t         MET_Base0_ety_PEMB;
   Float_t         MET_Base0_sumet_PEMB;
   Float_t         MET_Base0_phi_PEMB;
   Float_t         MET_Base0_etx_EMB;
   Float_t         MET_Base0_ety_EMB;
   Float_t         MET_Base0_sumet_EMB;
   Float_t         MET_Base0_phi_EMB;
   Float_t         MET_Base0_etx_PEMEC;
   Float_t         MET_Base0_ety_PEMEC;
   Float_t         MET_Base0_sumet_PEMEC;
   Float_t         MET_Base0_phi_PEMEC;
   Float_t         MET_Base0_etx_EME;
   Float_t         MET_Base0_ety_EME;
   Float_t         MET_Base0_sumet_EME;
   Float_t         MET_Base0_phi_EME;
   Float_t         MET_Base0_etx_TILE;
   Float_t         MET_Base0_ety_TILE;
   Float_t         MET_Base0_sumet_TILE;
   Float_t         MET_Base0_phi_TILE;
   Float_t         MET_Base0_etx_HEC;
   Float_t         MET_Base0_ety_HEC;
   Float_t         MET_Base0_sumet_HEC;
   Float_t         MET_Base0_phi_HEC;
   Float_t         MET_Base0_etx_FCAL;
   Float_t         MET_Base0_ety_FCAL;
   Float_t         MET_Base0_sumet_FCAL;
   Float_t         MET_Base0_phi_FCAL;
   Float_t         MET_Base0_nCell_PEMB;
   Float_t         MET_Base0_nCell_EMB;
   Float_t         MET_Base0_nCell_PEMEC;
   Float_t         MET_Base0_nCell_EME;
   Float_t         MET_Base0_nCell_TILE;
   Float_t         MET_Base0_nCell_HEC;
   Float_t         MET_Base0_nCell_FCAL;
   Float_t         MET_Base0_etx_CentralReg;
   Float_t         MET_Base0_ety_CentralReg;
   Float_t         MET_Base0_sumet_CentralReg;
   Float_t         MET_Base0_phi_CentralReg;
   Float_t         MET_Base0_etx_EndcapRegion;
   Float_t         MET_Base0_ety_EndcapRegion;
   Float_t         MET_Base0_sumet_EndcapRegion;
   Float_t         MET_Base0_phi_EndcapRegion;
   Float_t         MET_Base0_etx_ForwardReg;
   Float_t         MET_Base0_ety_ForwardReg;
   Float_t         MET_Base0_sumet_ForwardReg;
   Float_t         MET_Base0_phi_ForwardReg;
   Float_t         MET_Calib_etx;
   Float_t         MET_Calib_ety;
   Float_t         MET_Calib_sumet;
   Float_t         MET_Calib_et;
   Float_t         MET_Calib_phi;
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
   Float_t         MET_Topo_etx;
   Float_t         MET_Topo_ety;
   Float_t         MET_Topo_sumet;
   Float_t         MET_Topo_et;
   Float_t         MET_Topo_phi;
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
   Float_t         MET_CorrTopo_etx;
   Float_t         MET_CorrTopo_ety;
   Float_t         MET_CorrTopo_sumet;
   Float_t         MET_CorrTopo_et;
   Float_t         MET_CorrTopo_phi;
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
   Float_t         MET_LocHadTopo_etx;
   Float_t         MET_LocHadTopo_ety;
   Float_t         MET_LocHadTopo_sumet;
   Float_t         MET_LocHadTopo_et;
   Float_t         MET_LocHadTopo_phi;
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
   Float_t         MET_JetsInfo_JetPtWeightedEventEMFraction;
   Float_t         MET_JetsInfo_JetPtWeightedNumAssociatedTracks;
   Float_t         MET_JetsInfo_JetPtWeightedSize;
   Float_t         MET_JetsInfo_LeadingJetEt;
   Float_t         MET_JetsInfo_LeadingJetEta;
   Int_t           cl_n;
   vector<float>   *cl_E;
   vector<float>   *cl_pt;
   vector<float>   *cl_m;
   vector<float>   *cl_eta;
   vector<float>   *cl_phi;
   vector<float>   *cl_E_em;
   vector<float>   *cl_E_had;
   vector<float>   *cl_firstEdens;
   vector<float>   *cl_cellmaxfrac;
   vector<float>   *cl_longitudinal;
   vector<float>   *cl_secondlambda;
   vector<float>   *cl_lateral;
   vector<float>   *cl_secondR;
   vector<float>   *cl_centerlambda;
   vector<float>   *cl_deltaTheta;
   vector<float>   *cl_deltaPhi;
   vector<float>   *cl_time;
   Int_t           emcl_n;
   vector<float>   *emcl_E;
   vector<float>   *emcl_pt;
   vector<float>   *emcl_m;
   vector<float>   *emcl_eta;
   vector<float>   *emcl_phi;
   vector<float>   *emcl_E_em;
   vector<float>   *emcl_E_had;
   vector<float>   *emcl_firstEdens;
   vector<float>   *emcl_cellmaxfrac;
   vector<float>   *emcl_longitudinal;
   vector<float>   *emcl_secondlambda;
   vector<float>   *emcl_lateral;
   vector<float>   *emcl_secondR;
   vector<float>   *emcl_centerlambda;
   vector<float>   *emcl_deltaTheta;
   vector<float>   *emcl_deltaPhi;
   vector<float>   *emcl_time;
   vector<float>   *emcl_E_PreSamplerB;
   vector<float>   *emcl_E_EMB1;
   vector<float>   *emcl_E_EMB2;
   vector<float>   *emcl_E_EMB3;
   vector<float>   *emcl_E_PreSamplerE;
   vector<float>   *emcl_E_EME1;
   vector<float>   *emcl_E_EME2;
   vector<float>   *emcl_E_EME3;
   vector<float>   *emcl_E_HEC0;
   vector<float>   *emcl_E_HEC1;
   vector<float>   *emcl_E_HEC2;
   vector<float>   *emcl_E_HEC3;
   vector<float>   *emcl_E_TileBar0;
   vector<float>   *emcl_E_TileBar1;
   vector<float>   *emcl_E_TileBar2;
   vector<float>   *emcl_E_TileGap1;
   vector<float>   *emcl_E_TileGap2;
   vector<float>   *emcl_E_TileGap3;
   vector<float>   *emcl_E_TileExt0;
   vector<float>   *emcl_E_TileExt1;
   vector<float>   *emcl_E_TileExt2;
   vector<float>   *emcl_E_FCAL0;
   vector<float>   *emcl_E_FCAL1;
   vector<float>   *emcl_E_FCAL2;
   Int_t           trk_n;
   vector<float>   *trk_d0;
   vector<float>   *trk_z0;
   vector<float>   *trk_phi;
   vector<float>   *trk_theta;
   vector<float>   *trk_qoverp;
   vector<float>   *trk_pt;
   vector<float>   *trk_eta;
   vector<float>   *trk_err_d0;
   vector<float>   *trk_err_z0;
   vector<float>   *trk_err_phi;
   vector<float>   *trk_err_theta;
   vector<float>   *trk_err_qoverp;
   vector<float>   *trk_cov_d0;
   vector<float>   *trk_cov_z0;
   vector<float>   *trk_cov_phi;
   vector<float>   *trk_cov_theta;
   vector<float>   *trk_cov_qoverp;
   vector<float>   *trk_cov_d0_z0;
   vector<float>   *trk_cov_d0_phi;
   vector<float>   *trk_cov_d0_theta;
   vector<float>   *trk_cov_d0_qoverp;
   vector<float>   *trk_cov_z0_phi;
   vector<float>   *trk_cov_z0_theta;
   vector<float>   *trk_cov_z0_qoverp;
   vector<float>   *trk_cov_phi_theta;
   vector<float>   *trk_cov_phi_qoverp;
   vector<float>   *trk_cov_theta_qoverp;
   vector<int>     *trk_blayerPrediction_expectHit;
   vector<vector<float> > *trk_blayerPrediction_x;
   vector<vector<float> > *trk_blayerPrediction_y;
   vector<vector<float> > *trk_blayerPrediction_z;
   vector<vector<float> > *trk_blayerPrediction_locX;
   vector<vector<float> > *trk_blayerPrediction_locY;
   vector<vector<float> > *trk_blayerPrediction_err_locX;
   vector<vector<float> > *trk_blayerPrediction_err_locY;
   vector<vector<float> > *trk_blayerPrediction_etaDistToEdge;
   vector<vector<float> > *trk_blayerPrediction_phiDistToEdge;
   vector<vector<unsigned int> > *trk_blayerPrediction_detElementId;
   vector<vector<int> > *trk_blayerPrediction_row;
   vector<vector<int> > *trk_blayerPrediction_col;
   vector<vector<int> > *trk_blayerPrediction_type;
   vector<float>   *trk_d0_wrtPV;
   vector<float>   *trk_z0_wrtPV;
   vector<float>   *trk_phi_wrtPV;
   vector<float>   *trk_theta_wrtPV;
   vector<float>   *trk_qoverp_wrtPV;
   vector<float>   *trk_chi2;
   vector<int>     *trk_ndof;
   vector<int>     *trk_nBLHits;
   vector<int>     *trk_nPixHits;
   vector<int>     *trk_nSCTHits;
   vector<int>     *trk_nTRTHits;
   vector<int>     *trk_nPixHoles;
   vector<int>     *trk_nSCTHoles;
   vector<int>     *trk_nMDTHits;
   vector<int>     *trk_nCSCEtaHits;
   vector<int>     *trk_nCSCPhiHits;
   vector<int>     *trk_nRPCEtaHits;
   vector<int>     *trk_nRPCPhiHits;
   vector<int>     *trk_nTGCEtaHits;
   vector<int>     *trk_nTGCPhiHits;
   vector<int>     *trk_nHits;
   vector<int>     *trk_nHoles;
   vector<int>     *trk_hitPattern;
   vector<float>   *trk_TRTHighTHitsRatio;
   vector<float>   *trk_pixeldEdx;
   vector<int>     *trk_fitter;
   vector<int>     *trk_patternReco1;
   vector<int>     *trk_patternReco2;
   vector<int>     *trk_seedFinder;
   Int_t           mb_n;
   vector<float>   *mb_E;
   vector<float>   *mb_eta;
   vector<float>   *mb_phi;
   vector<float>   *mb_time;
   vector<int>     *mb_quality;
   vector<int>     *mb_type;
   vector<int>     *mb_module;
   vector<int>     *mb_channel;
   Float_t         mbtime_timeDiff;
   Float_t         mbtime_timeA;
   Float_t         mbtime_timeC;
   Int_t           mbtime_countA;
   Int_t           mbtime_countC;
   Bool_t          L1_MBTS_1;
   Bool_t          L1_MBTS_1_1;
   Bool_t          L1_MBTS_1_1_EMPTY;
   Bool_t          L1_MBTS_1_1_UNPAIRED_ISO;
   Bool_t          L1_MBTS_1_EMPTY;
   Bool_t          L1_MBTS_1_UNPAIRED_ISO;
   Bool_t          L1_MBTS_2;
   Bool_t          L1_MBTS_2_EMPTY;
   Bool_t          L1_MBTS_2_UNPAIRED_ISO;
   Bool_t          L1_MBTS_2_UNPAIRED_NONISO;
   Bool_t          L1_MBTS_4_4;
   Bool_t          L1_MBTS_4_4_UNPAIRED_ISO;
   Bool_t          collcand_passMBTSTime;
   Bool_t          collcand_passCaloTime;
   Bool_t          collcand_passTrigger;
   Bool_t          collcand_pass;
   Int_t           vxp_n;
   vector<float>   *vxp_x;
   vector<float>   *vxp_y;
   vector<float>   *vxp_z;
   vector<float>   *vxp_chi2;
   vector<int>     *vxp_ndof;
   vector<float>   *vxp_err_x;
   vector<float>   *vxp_err_y;
   vector<float>   *vxp_err_z;
   vector<float>   *vxp_px;
   vector<float>   *vxp_py;
   vector<float>   *vxp_pz;
   vector<float>   *vxp_E;
   vector<float>   *vxp_m;
   vector<int>     *vxp_nTracks;
   vector<float>   *vxp_sumPt;
   vector<int>     *vxp_type;
   vector<int>     *vxp_trk_n;
   vector<vector<float> > *vxp_trk_chi2;
   vector<vector<float> > *vxp_trk_d0;
   vector<vector<float> > *vxp_trk_z0;
   vector<vector<float> > *vxp_trk_unbiased_d0;
   vector<vector<float> > *vxp_trk_unbiased_z0;
   vector<vector<float> > *vxp_trk_err_unbiased_d0;
   vector<vector<float> > *vxp_trk_err_unbiased_z0;
   vector<vector<float> > *vxp_trk_phi;
   vector<vector<float> > *vxp_trk_theta;
   vector<vector<float> > *vxp_trk_weight;
   vector<vector<int> > *vxp_trk_index;
   Int_t           trig_L1_emtau_n;
   vector<float>   *trig_L1_emtau_eta;
   vector<float>   *trig_L1_emtau_phi;
   vector<vector<string> > *trig_L1_emtau_thrNames;
   vector<vector<float> > *trig_L1_emtau_thrValues;
   vector<float>   *trig_L1_emtau_core;
   vector<float>   *trig_L1_emtau_EMClus;
   vector<float>   *trig_L1_emtau_tauClus;
   vector<float>   *trig_L1_emtau_EMIsol;
   vector<float>   *trig_L1_emtau_hadIsol;
   vector<float>   *trig_L1_emtau_hadCore;
   vector<unsigned int> *trig_L1_emtau_thrPattern;
   vector<int>     *trig_L1_emtau_L1_2EM10;
   vector<int>     *trig_L1_emtau_L1_2EM14;
   vector<int>     *trig_L1_emtau_L1_2EM2;
   vector<int>     *trig_L1_emtau_L1_2EM3;
   vector<int>     *trig_L1_emtau_L1_2EM5;
   vector<int>     *trig_L1_emtau_L1_EM10;
   vector<int>     *trig_L1_emtau_L1_EM10I;
   vector<int>     *trig_L1_emtau_L1_EM14;
   vector<int>     *trig_L1_emtau_L1_EM14I;
   vector<int>     *trig_L1_emtau_L1_EM14_XE10;
   vector<int>     *trig_L1_emtau_L1_EM14_XE15;
   vector<int>     *trig_L1_emtau_L1_EM2;
   vector<int>     *trig_L1_emtau_L1_EM2_UNPAIRED_ISO;
   vector<int>     *trig_L1_emtau_L1_EM2_UNPAIRED_NONISO;
   vector<int>     *trig_L1_emtau_L1_EM3;
   vector<int>     *trig_L1_emtau_L1_EM3_EMPTY;
   vector<int>     *trig_L1_emtau_L1_EM3_FIRSTEMPTY;
   vector<int>     *trig_L1_emtau_L1_EM3_MV;
   vector<int>     *trig_L1_emtau_L1_EM5;
   vector<int>     *trig_L1_emtau_L1_EM5_MU10;
   vector<int>     *trig_L1_emtau_L1_EM5_MU6;
   vector<int>     *trig_L1_emtau_L1_EM85;
   Int_t           trig_L2_emcl_n;
   vector<unsigned int> *trig_L2_emcl_quality;
   vector<float>   *trig_L2_emcl_E;
   vector<float>   *trig_L2_emcl_Et;
   vector<float>   *trig_L2_emcl_eta;
   vector<float>   *trig_L2_emcl_phi;
   vector<float>   *trig_L2_emcl_E237;
   vector<float>   *trig_L2_emcl_E277;
   vector<float>   *trig_L2_emcl_fracs1;
   vector<float>   *trig_L2_emcl_weta2;
   vector<float>   *trig_L2_emcl_Ehad1;
   vector<float>   *trig_L2_emcl_eta1;
   vector<float>   *trig_L2_emcl_emaxs1;
   vector<float>   *trig_L2_emcl_e2tsts1;
   Int_t           trig_L2_trk_idscan_eGamma_n;
   vector<int>     *trig_L2_trk_idscan_eGamma_algorithmId;
   vector<short>   *trig_L2_trk_idscan_eGamma_trackStatus;
   vector<float>   *trig_L2_trk_idscan_eGamma_chi2Ndof;
   vector<int>     *trig_L2_trk_idscan_eGamma_nStrawHits;
   vector<int>     *trig_L2_trk_idscan_eGamma_nHighThrHits;
   vector<int>     *trig_L2_trk_idscan_eGamma_nPixelSpacePoints;
   vector<int>     *trig_L2_trk_idscan_eGamma_nSCT_SpacePoints;
   vector<float>   *trig_L2_trk_idscan_eGamma_a0;
   vector<float>   *trig_L2_trk_idscan_eGamma_z0;
   vector<float>   *trig_L2_trk_idscan_eGamma_phi0;
   vector<float>   *trig_L2_trk_idscan_eGamma_eta;
   vector<float>   *trig_L2_trk_idscan_eGamma_pt;
   Int_t           trig_L2_trk_sitrack_eGamma_n;
   vector<int>     *trig_L2_trk_sitrack_eGamma_algorithmId;
   vector<short>   *trig_L2_trk_sitrack_eGamma_trackStatus;
   vector<float>   *trig_L2_trk_sitrack_eGamma_chi2Ndof;
   vector<int>     *trig_L2_trk_sitrack_eGamma_nStrawHits;
   vector<int>     *trig_L2_trk_sitrack_eGamma_nHighThrHits;
   vector<int>     *trig_L2_trk_sitrack_eGamma_nPixelSpacePoints;
   vector<int>     *trig_L2_trk_sitrack_eGamma_nSCT_SpacePoints;
   vector<float>   *trig_L2_trk_sitrack_eGamma_a0;
   vector<float>   *trig_L2_trk_sitrack_eGamma_z0;
   vector<float>   *trig_L2_trk_sitrack_eGamma_phi0;
   vector<float>   *trig_L2_trk_sitrack_eGamma_eta;
   vector<float>   *trig_L2_trk_sitrack_eGamma_pt;
   Int_t           trig_L2_el_n;
   vector<float>   *trig_L2_el_E;
   vector<float>   *trig_L2_el_Et;
   vector<float>   *trig_L2_el_pt;
   vector<float>   *trig_L2_el_eta;
   vector<float>   *trig_L2_el_phi;
   vector<int>     *trig_L2_el_RoIWord;
   vector<float>   *trig_L2_el_zvertex;
   vector<int>     *trig_L2_el_charge;
   vector<int>     *trig_L2_el_trackAlgo;
   vector<float>   *trig_L2_el_TRTHighTHitsRatio;
   vector<float>   *trig_L2_el_deltaeta1;
   vector<float>   *trig_L2_el_deltaphi2;
   vector<float>   *trig_L2_el_EtOverPt;
   vector<float>   *trig_L2_el_reta;
   vector<float>   *trig_L2_el_Eratio;
   vector<float>   *trig_L2_el_Ethad1;
   vector<int>     *trig_L2_el_L2_2e10_loose;
   vector<int>     *trig_L2_el_L2_2e10_medium;
   vector<int>     *trig_L2_el_L2_2e15_loose;
   vector<int>     *trig_L2_el_L2_2e3_loose;
   vector<int>     *trig_L2_el_L2_2e3_loose_SiTrk;
   vector<int>     *trig_L2_el_L2_2e3_loose_TRT;
   vector<int>     *trig_L2_el_L2_2e3_medium;
   vector<int>     *trig_L2_el_L2_2e3_medium_SiTrk;
   vector<int>     *trig_L2_el_L2_2e3_medium_TRT;
   vector<int>     *trig_L2_el_L2_2e3_tight;
   vector<int>     *trig_L2_el_L2_2e5_medium;
   vector<int>     *trig_L2_el_L2_2e5_medium_SiTrk;
   vector<int>     *trig_L2_el_L2_2e5_medium_TRT;
   vector<int>     *trig_L2_el_L2_2e5_tight;
   vector<int>     *trig_L2_el_L2_e10_NoCut;
   vector<int>     *trig_L2_el_L2_e10_loose;
   vector<int>     *trig_L2_el_L2_e10_loose_mu10;
   vector<int>     *trig_L2_el_L2_e10_loose_mu6;
   vector<int>     *trig_L2_el_L2_e10_medium;
   vector<int>     *trig_L2_el_L2_e10_medium_IDTrkNoCut;
   vector<int>     *trig_L2_el_L2_e10_medium_SiTrk;
   vector<int>     *trig_L2_el_L2_e10_medium_TRT;
   vector<int>     *trig_L2_el_L2_e10_tight;
   vector<int>     *trig_L2_el_L2_e15_loose;
   vector<int>     *trig_L2_el_L2_e15_loose_IDTrkNoCut;
   vector<int>     *trig_L2_el_L2_e15_medium;
   vector<int>     *trig_L2_el_L2_e15_medium_SiTrk;
   vector<int>     *trig_L2_el_L2_e15_medium_TRT;
   vector<int>     *trig_L2_el_L2_e15_tight;
   vector<int>     *trig_L2_el_L2_e18_medium;
   vector<int>     *trig_L2_el_L2_e20_loose;
   vector<int>     *trig_L2_el_L2_e20_loose_IDTrkNoCut;
   vector<int>     *trig_L2_el_L2_e20_loose_passEF;
   vector<int>     *trig_L2_el_L2_e20_loose_passL2;
   vector<int>     *trig_L2_el_L2_e20_loose_xe20_noMu;
   vector<int>     *trig_L2_el_L2_e20_loose_xe30_noMu;
   vector<int>     *trig_L2_el_L2_e20_medium;
   vector<int>     *trig_L2_el_L2_e25_loose;
   vector<int>     *trig_L2_el_L2_e30_loose;
   vector<int>     *trig_L2_el_L2_e3_loose;
   vector<int>     *trig_L2_el_L2_e3_loose_SiTrk;
   vector<int>     *trig_L2_el_L2_e3_loose_TRT;
   vector<int>     *trig_L2_el_L2_e3_medium;
   vector<int>     *trig_L2_el_L2_e3_medium_SiTrk;
   vector<int>     *trig_L2_el_L2_e3_medium_TRT;
   vector<int>     *trig_L2_el_L2_e5_NoCut_firstempty;
   vector<int>     *trig_L2_el_L2_e5_medium;
   vector<int>     *trig_L2_el_L2_e5_medium_MV;
   vector<int>     *trig_L2_el_L2_e5_medium_SiTrk;
   vector<int>     *trig_L2_el_L2_e5_medium_TRT;
   vector<int>     *trig_L2_el_L2_e5_medium_mu4;
   vector<int>     *trig_L2_el_L2_e5_tight;
   vector<int>     *trig_L2_el_L2_e5_tight_SiTrk;
   vector<int>     *trig_L2_el_L2_e5_tight_TRT;
   vector<int>     *trig_L2_el_L2_e5_tight_e5_NoCut;
   vector<int>     *trig_L2_el_L2_eb_physics;
   vector<int>     *trig_L2_el_L2_eb_physics_empty;
   vector<int>     *trig_L2_el_L2_eb_physics_firstempty;
   vector<int>     *trig_L2_el_L2_eb_physics_unpaired_iso;
   vector<int>     *trig_L2_el_L2_eb_physics_unpaired_noniso;
   vector<int>     *trig_L2_el_L2_eb_random;
   vector<int>     *trig_L2_el_L2_eb_random_empty;
   vector<int>     *trig_L2_el_L2_eb_random_firstempty;
   vector<int>     *trig_L2_el_L2_eb_random_unpaired_iso;
   vector<int>     *trig_L2_el_L2_em105_passHLT;
   vector<int>     *trig_L2_el_L2_em3_empty_larcalib;
   Int_t           trig_L2_ph_n;
   vector<float>   *trig_L2_ph_E;
   vector<float>   *trig_L2_ph_Et;
   vector<float>   *trig_L2_ph_pt;
   vector<float>   *trig_L2_ph_eta;
   vector<float>   *trig_L2_ph_phi;
   vector<int>     *trig_L2_ph_RoIWord;
   vector<float>   *trig_L2_ph_HadEt1;
   vector<float>   *trig_L2_ph_Eratio;
   vector<float>   *trig_L2_ph_Reta;
   vector<float>   *trig_L2_ph_dPhi;
   vector<float>   *trig_L2_ph_dEta;
   vector<float>   *trig_L2_ph_F1;
   vector<int>     *trig_L2_ph_L2_2g10_loose;
   vector<int>     *trig_L2_ph_L2_2g15_loose;
   vector<int>     *trig_L2_ph_L2_2g5_loose;
   vector<int>     *trig_L2_ph_L2_2g7_loose;
   vector<int>     *trig_L2_ph_L2_g10_loose;
   vector<int>     *trig_L2_ph_L2_g11_etcut;
   vector<int>     *trig_L2_ph_L2_g15_loose;
   vector<int>     *trig_L2_ph_L2_g17_etcut;
   vector<int>     *trig_L2_ph_L2_g17_etcut_EFxe20_noMu;
   vector<int>     *trig_L2_ph_L2_g17_etcut_EFxe30_noMu;
   vector<int>     *trig_L2_ph_L2_g20_loose;
   vector<int>     *trig_L2_ph_L2_g20_loose_xe20_noMu;
   vector<int>     *trig_L2_ph_L2_g20_loose_xe30_noMu;
   vector<int>     *trig_L2_ph_L2_g20_tight;
   vector<int>     *trig_L2_ph_L2_g25_loose_xe30_noMu;
   vector<int>     *trig_L2_ph_L2_g30_loose;
   vector<int>     *trig_L2_ph_L2_g30_tight;
   vector<int>     *trig_L2_ph_L2_g3_NoCut_unpaired_iso;
   vector<int>     *trig_L2_ph_L2_g3_NoCut_unpaired_noniso;
   vector<int>     *trig_L2_ph_L2_g40_loose;
   vector<int>     *trig_L2_ph_L2_g40_tight;
   vector<int>     *trig_L2_ph_L2_g50_loose;
   vector<int>     *trig_L2_ph_L2_g5_NoCut_cosmic;
   vector<int>     *trig_L2_ph_L2_g5_loose;
   vector<int>     *trig_L2_ph_L2_g7_loose;
   Int_t           trig_EF_emcl_n;
   vector<float>   *trig_EF_emcl_E;
   vector<float>   *trig_EF_emcl_pt;
   vector<float>   *trig_EF_emcl_m;
   vector<float>   *trig_EF_emcl_eta;
   vector<float>   *trig_EF_emcl_phi;
   vector<float>   *trig_EF_emcl_E_em;
   vector<float>   *trig_EF_emcl_E_had;
   vector<float>   *trig_EF_emcl_firstEdens;
   vector<float>   *trig_EF_emcl_cellmaxfrac;
   vector<float>   *trig_EF_emcl_longitudinal;
   vector<float>   *trig_EF_emcl_secondlambda;
   vector<float>   *trig_EF_emcl_lateral;
   vector<float>   *trig_EF_emcl_secondR;
   vector<float>   *trig_EF_emcl_centerlambda;
   vector<float>   *trig_EF_emcl_deltaTheta;
   vector<float>   *trig_EF_emcl_deltaPhi;
   vector<float>   *trig_EF_emcl_time;
   Int_t           trig_EF_emcl_slw_n;
   vector<float>   *trig_EF_emcl_slw_E;
   vector<float>   *trig_EF_emcl_slw_pt;
   vector<float>   *trig_EF_emcl_slw_m;
   vector<float>   *trig_EF_emcl_slw_eta;
   vector<float>   *trig_EF_emcl_slw_phi;
   vector<float>   *trig_EF_emcl_slw_E_em;
   vector<float>   *trig_EF_emcl_slw_E_had;
   vector<float>   *trig_EF_emcl_slw_firstEdens;
   vector<float>   *trig_EF_emcl_slw_cellmaxfrac;
   vector<float>   *trig_EF_emcl_slw_longitudinal;
   vector<float>   *trig_EF_emcl_slw_secondlambda;
   vector<float>   *trig_EF_emcl_slw_lateral;
   vector<float>   *trig_EF_emcl_slw_secondR;
   vector<float>   *trig_EF_emcl_slw_centerlambda;
   vector<float>   *trig_EF_emcl_slw_deltaTheta;
   vector<float>   *trig_EF_emcl_slw_deltaPhi;
   vector<float>   *trig_EF_emcl_slw_time;
   Int_t           trig_EF_el_n;
   vector<float>   *trig_EF_el_E;
   vector<float>   *trig_EF_el_Et;
   vector<float>   *trig_EF_el_pt;
   vector<float>   *trig_EF_el_m;
   vector<float>   *trig_EF_el_eta;
   vector<float>   *trig_EF_el_phi;
   vector<float>   *trig_EF_el_px;
   vector<float>   *trig_EF_el_py;
   vector<float>   *trig_EF_el_pz;
   vector<float>   *trig_EF_el_charge;
   vector<int>     *trig_EF_el_author;
   vector<unsigned int> *trig_EF_el_isEM;
   vector<int>     *trig_EF_el_loose;
   vector<int>     *trig_EF_el_medium;
   vector<int>     *trig_EF_el_mediumIso;
   vector<int>     *trig_EF_el_tight;
   vector<int>     *trig_EF_el_tightIso;
   vector<float>   *trig_EF_el_Ethad;
   vector<float>   *trig_EF_el_Ethad1;
   vector<float>   *trig_EF_el_f1;
   vector<float>   *trig_EF_el_f1core;
   vector<float>   *trig_EF_el_Emins1;
   vector<float>   *trig_EF_el_fside;
   vector<float>   *trig_EF_el_Emax2;
   vector<float>   *trig_EF_el_ws3;
   vector<float>   *trig_EF_el_wstot;
   vector<float>   *trig_EF_el_emaxs1;
   vector<float>   *trig_EF_el_deltaEs;
   vector<float>   *trig_EF_el_E233;
   vector<float>   *trig_EF_el_E237;
   vector<float>   *trig_EF_el_E277;
   vector<float>   *trig_EF_el_weta2;
   vector<float>   *trig_EF_el_f3;
   vector<float>   *trig_EF_el_f3core;
   vector<float>   *trig_EF_el_rphiallcalo;
   vector<float>   *trig_EF_el_Etcone45;
   vector<float>   *trig_EF_el_Etcone20;
   vector<float>   *trig_EF_el_Etcone30;
   vector<float>   *trig_EF_el_Etcone40;
   vector<float>   *trig_EF_el_pos7;
   vector<float>   *trig_EF_el_etacorrmag;
   vector<float>   *trig_EF_el_deltaeta1;
   vector<float>   *trig_EF_el_deltaeta2;
   vector<float>   *trig_EF_el_deltaphi2;
   vector<float>   *trig_EF_el_reta;
   vector<float>   *trig_EF_el_rphi;
   vector<int>     *trig_EF_el_EF_2e10_loose;
   vector<int>     *trig_EF_el_EF_2e10_medium;
   vector<int>     *trig_EF_el_EF_2e15_loose;
   vector<int>     *trig_EF_el_EF_2e3_loose;
   vector<int>     *trig_EF_el_EF_2e3_loose_SiTrk;
   vector<int>     *trig_EF_el_EF_2e3_loose_TRT;
   vector<int>     *trig_EF_el_EF_2e3_medium;
   vector<int>     *trig_EF_el_EF_2e3_medium_SiTrk;
   vector<int>     *trig_EF_el_EF_2e3_medium_TRT;
   vector<int>     *trig_EF_el_EF_2e3_tight;
   vector<int>     *trig_EF_el_EF_2e5_medium;
   vector<int>     *trig_EF_el_EF_2e5_medium_SiTrk;
   vector<int>     *trig_EF_el_EF_2e5_medium_TRT;
   vector<int>     *trig_EF_el_EF_2e5_tight;
   vector<int>     *trig_EF_el_EF_e10_NoCut;
   vector<int>     *trig_EF_el_EF_e10_loose;
   vector<int>     *trig_EF_el_EF_e10_loose_mu10;
   vector<int>     *trig_EF_el_EF_e10_loose_mu6;
   vector<int>     *trig_EF_el_EF_e10_medium;
   vector<int>     *trig_EF_el_EF_e10_medium_IDTrkNoCut;
   vector<int>     *trig_EF_el_EF_e10_medium_SiTrk;
   vector<int>     *trig_EF_el_EF_e10_medium_TRT;
   vector<int>     *trig_EF_el_EF_e10_tight;
   vector<int>     *trig_EF_el_EF_e15_loose;
   vector<int>     *trig_EF_el_EF_e15_loose_IDTrkNoCut;
   vector<int>     *trig_EF_el_EF_e15_medium;
   vector<int>     *trig_EF_el_EF_e15_medium_SiTrk;
   vector<int>     *trig_EF_el_EF_e15_medium_TRT;
   vector<int>     *trig_EF_el_EF_e15_tight;
   vector<int>     *trig_EF_el_EF_e18_medium;
   vector<int>     *trig_EF_el_EF_e20_loose;
   vector<int>     *trig_EF_el_EF_e20_loose_IDTrkNoCut;
   vector<int>     *trig_EF_el_EF_e20_loose_passEF;
   vector<int>     *trig_EF_el_EF_e20_loose_passL2;
   vector<int>     *trig_EF_el_EF_e20_loose_xe20_noMu;
   vector<int>     *trig_EF_el_EF_e20_loose_xe30_noMu;
   vector<int>     *trig_EF_el_EF_e20_medium;
   vector<int>     *trig_EF_el_EF_e25_loose;
   vector<int>     *trig_EF_el_EF_e30_loose;
   vector<int>     *trig_EF_el_EF_e3_loose;
   vector<int>     *trig_EF_el_EF_e3_loose_SiTrk;
   vector<int>     *trig_EF_el_EF_e3_loose_TRT;
   vector<int>     *trig_EF_el_EF_e3_medium;
   vector<int>     *trig_EF_el_EF_e3_medium_SiTrk;
   vector<int>     *trig_EF_el_EF_e3_medium_TRT;
   vector<int>     *trig_EF_el_EF_e5_NoCut_firstempty;
   vector<int>     *trig_EF_el_EF_e5_medium;
   vector<int>     *trig_EF_el_EF_e5_medium_MV;
   vector<int>     *trig_EF_el_EF_e5_medium_SiTrk;
   vector<int>     *trig_EF_el_EF_e5_medium_TRT;
   vector<int>     *trig_EF_el_EF_e5_medium_mu4;
   vector<int>     *trig_EF_el_EF_e5_tight;
   vector<int>     *trig_EF_el_EF_e5_tight_SiTrk;
   vector<int>     *trig_EF_el_EF_e5_tight_TRT;
   vector<int>     *trig_EF_el_EF_e5_tight_e5_NoCut;
   vector<int>     *trig_EF_el_EF_eb_physics;
   vector<int>     *trig_EF_el_EF_eb_physics_empty;
   vector<int>     *trig_EF_el_EF_eb_physics_firstempty;
   vector<int>     *trig_EF_el_EF_eb_physics_unpaired_iso;
   vector<int>     *trig_EF_el_EF_eb_physics_unpaired_noniso;
   vector<int>     *trig_EF_el_EF_eb_random;
   vector<int>     *trig_EF_el_EF_eb_random_empty;
   vector<int>     *trig_EF_el_EF_eb_random_firstempty;
   vector<int>     *trig_EF_el_EF_eb_random_unpaired_iso;
   vector<int>     *trig_EF_el_EF_em105_passHLT;
   Int_t           trig_EF_ph_n;
   vector<float>   *trig_EF_ph_E;
   vector<float>   *trig_EF_ph_Et;
   vector<float>   *trig_EF_ph_pt;
   vector<float>   *trig_EF_ph_m;
   vector<float>   *trig_EF_ph_eta;
   vector<float>   *trig_EF_ph_phi;
   vector<float>   *trig_EF_ph_px;
   vector<float>   *trig_EF_ph_py;
   vector<float>   *trig_EF_ph_pz;
   vector<int>     *trig_EF_ph_EF_2g10_loose;
   vector<int>     *trig_EF_ph_EF_2g15_loose;
   vector<int>     *trig_EF_ph_EF_2g5_loose;
   vector<int>     *trig_EF_ph_EF_2g7_loose;
   vector<int>     *trig_EF_ph_EF_g10_loose;
   vector<int>     *trig_EF_ph_EF_g10_loose_larcalib;
   vector<int>     *trig_EF_ph_EF_g11_etcut;
   vector<int>     *trig_EF_ph_EF_g15_loose;
   vector<int>     *trig_EF_ph_EF_g17_etcut;
   vector<int>     *trig_EF_ph_EF_g17_etcut_EFxe20_noMu;
   vector<int>     *trig_EF_ph_EF_g17_etcut_EFxe30_noMu;
   vector<int>     *trig_EF_ph_EF_g20_loose;
   vector<int>     *trig_EF_ph_EF_g20_loose_larcalib;
   vector<int>     *trig_EF_ph_EF_g20_loose_xe20_noMu;
   vector<int>     *trig_EF_ph_EF_g20_loose_xe30_noMu;
   vector<int>     *trig_EF_ph_EF_g20_tight;
   vector<int>     *trig_EF_ph_EF_g25_loose_xe30_noMu;
   vector<int>     *trig_EF_ph_EF_g30_loose;
   vector<int>     *trig_EF_ph_EF_g30_tight;
   vector<int>     *trig_EF_ph_EF_g3_NoCut_unpaired_iso;
   vector<int>     *trig_EF_ph_EF_g3_NoCut_unpaired_noniso;
   vector<int>     *trig_EF_ph_EF_g40_loose;
   vector<int>     *trig_EF_ph_EF_g40_loose_larcalib;
   vector<int>     *trig_EF_ph_EF_g40_tight;
   vector<int>     *trig_EF_ph_EF_g50_loose;
   vector<int>     *trig_EF_ph_EF_g50_loose_larcalib;
   vector<int>     *trig_EF_ph_EF_g5_NoCut_cosmic;
   vector<int>     *trig_EF_ph_EF_g5_loose;
   vector<int>     *trig_EF_ph_EF_g5_loose_larcalib;
   vector<int>     *trig_EF_ph_EF_g7_loose;
   Int_t           trig_Nav_n;
   vector<short>   *trig_Nav_chain_ChainId;
   vector<vector<int> > *trig_Nav_chain_RoIType;
   vector<vector<int> > *trig_Nav_chain_RoIIndex;
   Int_t           trig_RoI_L2_e_n;
   vector<short>   *trig_RoI_L2_e_type;
   vector<short>   *trig_RoI_L2_e_lastStep;
   vector<int>     *trig_RoI_L2_e_TrigEMCluster;
   vector<int>     *trig_RoI_L2_e_TrigEMClusterStatus;
   vector<int>     *trig_RoI_L2_e_EmTau_ROI;
   vector<int>     *trig_RoI_L2_e_EmTau_ROIStatus;
   vector<vector<int> > *trig_RoI_L2_e_TrigInDetTrackCollection_TrigSiTrack_eGamma;
   vector<vector<int> > *trig_RoI_L2_e_TrigInDetTrackCollection_TrigSiTrack_eGammaStatus;
   vector<vector<int> > *trig_RoI_L2_e_TrigInDetTrackCollection_TrigIDSCAN_eGamma;
   vector<vector<int> > *trig_RoI_L2_e_TrigInDetTrackCollection_TrigIDSCAN_eGammaStatus;
   vector<vector<int> > *trig_RoI_L2_e_TrigElectronContainer;
   vector<vector<int> > *trig_RoI_L2_e_TrigElectronContainerStatus;
   Int_t           trig_RoI_EF_e_n;
   vector<short>   *trig_RoI_EF_e_type;
   vector<short>   *trig_RoI_EF_e_lastStep;
   vector<int>     *trig_RoI_EF_e_EmTau_ROI;
   vector<int>     *trig_RoI_EF_e_EmTau_ROIStatus;
   UInt_t          trig_DB_SMK;
   UInt_t          trig_DB_L1PSK;
   UInt_t          trig_DB_HLTPSK;
   vector<string>  *trig_L1_esum_thrNames;
   Float_t         trig_L1_esum_energyX;
   Float_t         trig_L1_esum_energyY;
   Float_t         trig_L1_esum_energyT;
   Bool_t          trig_L1_esum_overflowX;
   Bool_t          trig_L1_esum_overflowY;
   Bool_t          trig_L1_esum_overflowT;
   UInt_t          trig_L1_esum_RoIWord0;
   UInt_t          trig_L1_esum_RoIWord1;
   UInt_t          trig_L1_esum_RoIWord2;
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
   Char_t          trig_bgCode;
   Int_t           MET_Goodness_CalClusForwBackw_pass;
   Int_t           MET_Goodness_CalClusUpDown_pass;
   Int_t           MET_Goodness_Calo_countA;
   Int_t           MET_Goodness_Calo_countC;
   Int_t           MET_Goodness_Calo_pass;
   Int_t           MET_Goodness_IsCollisionCandidate;
   Int_t           MET_Goodness_MBTS_countA;
   Int_t           MET_Goodness_MBTS_countC;
   Int_t           MET_Goodness_MBTS_pass;
   Int_t           MET_Goodness_MuonSp0Hits;
   Int_t           MET_Goodness_MuonSp1Hits;
   Int_t           MET_Goodness_MuonSpTotHits;
   Int_t           MET_Goodness_OkayLB;
   Double_t        MET_Goodness_CalClusForwBackw_timeDiff;
   Double_t        MET_Goodness_CalClusUpDown_timeDiff;
   Double_t        MET_Goodness_CalClus_InTimeFraction;
   Double_t        MET_Goodness_CalClus_OutTimeEnergy;
   Double_t        MET_Goodness_CalClus_eventTime;
   Double_t        MET_Goodness_CalClus_ootEnergy10;
   Double_t        MET_Goodness_CalClus_ootEnergy15;
   Double_t        MET_Goodness_CalClus_ootEnergy20;
   Double_t        MET_Goodness_CalClus_ootEnergy25;
   Double_t        MET_Goodness_CalClus_ootFraction10;
   Double_t        MET_Goodness_CalClus_ootFraction15;
   Double_t        MET_Goodness_CalClus_ootFraction20;
   Double_t        MET_Goodness_CalClus_ootFraction25;
   Double_t        MET_Goodness_CalClus_timeA;
   Double_t        MET_Goodness_CalClus_timeC;
   Double_t        MET_Goodness_Calo_timeA;
   Double_t        MET_Goodness_Calo_timeC;
   Double_t        MET_Goodness_Calo_timeDiff;
   Double_t        MET_Goodness_EtoverRootSigmaEt;
   Double_t        MET_Goodness_EventEMFraction;
   Double_t        MET_Goodness_LArNoisyROSummary;
   Double_t        MET_Goodness_MBTS_timeA;
   Double_t        MET_Goodness_MBTS_timeC;
   Double_t        MET_Goodness_MBTS_timeDiff;
   Double_t        MET_Goodness_MET_CorrTopo_etx;
   Double_t        MET_Goodness_MET_CorrTopo_ety;
   Double_t        MET_Goodness_MET_CorrTopo_sumet;
   Double_t        MET_Goodness_MET_Topo_etx;
   Double_t        MET_Goodness_MET_Topo_ety;
   Double_t        MET_Goodness_MET_Topo_sumet;
   Double_t        MET_Goodness_MuonSp0Eta;
   Double_t        MET_Goodness_MuonSp0Phi;
   Double_t        MET_Goodness_MuonSp1Eta;
   Double_t        MET_Goodness_MuonSp1Phi;
   Double_t        MET_Goodness_MuonTRTTiming;
   vector<double>  *MET_Goodness_BCH_CORR_CELL_Jet;
   vector<double>  *MET_Goodness_BCH_CORR_JET;
   vector<double>  *MET_Goodness_BCH_CORR_JET_FORCELL_Jet;
   vector<double>  *MET_Goodness_ChargeFraction_Jet;
   vector<double>  *MET_Goodness_DeltaEt_JetAlgs_Jet;
   vector<double>  *MET_Goodness_DeltaEta_JetAlgs_Jet;
   vector<double>  *MET_Goodness_DeltaPhi_JetAlgs_Jet;
   vector<double>  *MET_Goodness_DeltaPhi_MET_Jet;
   vector<double>  *MET_Goodness_EEM_Jet;
   vector<double>  *MET_Goodness_EFinal_Jet;
   vector<double>  *MET_Goodness_EMFraction_Jet;
   vector<double>  *MET_Goodness_E_BadCellsCorr_Jet;
   vector<double>  *MET_Goodness_E_BadCells_Jet;
   vector<double>  *MET_Goodness_Eta_Jet;
   vector<double>  *MET_Goodness_HECf_Jet;
   vector<double>  *MET_Goodness_LArQuality_Jet;
   vector<double>  *MET_Goodness_Phi_Jet;
   vector<double>  *MET_Goodness_PtEM_Jet;
   vector<double>  *MET_Goodness_QualityFrac_Jet;
   vector<double>  *MET_Goodness_SamplingFracCryo_Jet;
   vector<double>  *MET_Goodness_SamplingFracEM_Jet;
   vector<double>  *MET_Goodness_SamplingFracFCAL_Jet;
   vector<double>  *MET_Goodness_SamplingFracGap_Jet;
   vector<double>  *MET_Goodness_SamplingFracHEC3_Jet;
   vector<double>  *MET_Goodness_SamplingFracHEC_Jet;
   vector<double>  *MET_Goodness_SamplingFracMax_Jet;
   vector<double>  *MET_Goodness_SamplingFracPS_Jet;
   vector<double>  *MET_Goodness_SamplingFracTile10_Jet;
   vector<double>  *MET_Goodness_SamplingFracTile2_Jet;
   vector<double>  *MET_Goodness_SamplingFracTile_Jet;
   vector<double>  *MET_Goodness_TileQuality_Jet;
   vector<double>  *MET_Goodness_Timing_Jet;
   vector<double>  *MET_Goodness_fcor_Jet;
   vector<double>  *MET_Goodness_ootE25_Jet;
   vector<double>  *MET_Goodness_ootE50_Jet;
   vector<double>  *MET_Goodness_ootE75_Jet;
   vector<int>     *MET_Goodness_N90Cells_Jet;
   vector<int>     *MET_Goodness_N90Constituents_Jet;
   vector<int>     *MET_Goodness_NConstituents_Jet;
   vector<int>     *MET_Goodness_N_BadCellsCorr_Jet;
   vector<int>     *MET_Goodness_N_BadCells_Jet;
   vector<int>     *MET_Goodness_NumTracks_Jet;
   vector<int>     *MET_Goodness_SamplingMaxID_Jet;
   Bool_t          MET_Goodness_All;
   Bool_t          MET_Goodness_JetCleaning;
   Long64_t        MET_Goodness_BitMask;

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
   TBranch        *b_lar_ncellA;   //!
   TBranch        *b_lar_ncellC;   //!
   TBranch        *b_lar_energyA;   //!
   TBranch        *b_lar_energyC;   //!
   TBranch        *b_lar_timeA;   //!
   TBranch        *b_lar_timeC;   //!
   TBranch        *b_lar_timeDiff;   //!
   TBranch        *b_el_n;   //!
   TBranch        *b_el_E;   //!
   TBranch        *b_el_Et;   //!
   TBranch        *b_el_pt;   //!
   TBranch        *b_el_m;   //!
   TBranch        *b_el_eta;   //!
   TBranch        *b_el_phi;   //!
   TBranch        *b_el_px;   //!
   TBranch        *b_el_py;   //!
   TBranch        *b_el_pz;   //!
   TBranch        *b_el_charge;   //!
   TBranch        *b_el_author;   //!
   TBranch        *b_el_isEM;   //!
   TBranch        *b_el_convFlag;   //!
   TBranch        *b_el_isConv;   //!
   TBranch        *b_el_nConv;   //!
   TBranch        *b_el_nSingleTrackConv;   //!
   TBranch        *b_el_nDoubleTrackConv;   //!
   TBranch        *b_el_loose;   //!
   TBranch        *b_el_medium;   //!
   TBranch        *b_el_mediumIso;   //!
   TBranch        *b_el_tight;   //!
   TBranch        *b_el_tightIso;   //!
   TBranch        *b_el_Ethad;   //!
   TBranch        *b_el_Ethad1;   //!
   TBranch        *b_el_f1;   //!
   TBranch        *b_el_f1core;   //!
   TBranch        *b_el_Emins1;   //!
   TBranch        *b_el_fside;   //!
   TBranch        *b_el_Emax2;   //!
   TBranch        *b_el_ws3;   //!
   TBranch        *b_el_wstot;   //!
   TBranch        *b_el_emaxs1;   //!
   TBranch        *b_el_deltaEs;   //!
   TBranch        *b_el_E233;   //!
   TBranch        *b_el_E237;   //!
   TBranch        *b_el_E277;   //!
   TBranch        *b_el_weta2;   //!
   TBranch        *b_el_f3;   //!
   TBranch        *b_el_f3core;   //!
   TBranch        *b_el_rphiallcalo;   //!
   TBranch        *b_el_Etcone45;   //!
   TBranch        *b_el_Etcone20;   //!
   TBranch        *b_el_Etcone30;   //!
   TBranch        *b_el_Etcone40;   //!
   TBranch        *b_el_ptcone30;   //!
   TBranch        *b_el_convanglematch;   //!
   TBranch        *b_el_convtrackmatch;   //!
   TBranch        *b_el_hasconv;   //!
   TBranch        *b_el_convvtxx;   //!
   TBranch        *b_el_convvtxy;   //!
   TBranch        *b_el_convvtxz;   //!
   TBranch        *b_el_Rconv;   //!
   TBranch        *b_el_zconv;   //!
   TBranch        *b_el_convvtxchi2;   //!
   TBranch        *b_el_pt1conv;   //!
   TBranch        *b_el_convtrk1nBLHits;   //!
   TBranch        *b_el_convtrk1nPixHits;   //!
   TBranch        *b_el_convtrk1nSCTHits;   //!
   TBranch        *b_el_convtrk1nTRTHits;   //!
   TBranch        *b_el_pt2conv;   //!
   TBranch        *b_el_convtrk2nBLHits;   //!
   TBranch        *b_el_convtrk2nPixHits;   //!
   TBranch        *b_el_convtrk2nSCTHits;   //!
   TBranch        *b_el_convtrk2nTRTHits;   //!
   TBranch        *b_el_ptconv;   //!
   TBranch        *b_el_pzconv;   //!
   TBranch        *b_el_pos7;   //!
   TBranch        *b_el_etacorrmag;   //!
   TBranch        *b_el_deltaeta1;   //!
   TBranch        *b_el_deltaeta2;   //!
   TBranch        *b_el_deltaphi2;   //!
   TBranch        *b_el_deltaphiRescaled;   //!
   TBranch        *b_el_expectHitInBLayer;   //!
   TBranch        *b_el_reta;   //!
   TBranch        *b_el_rphi;   //!
   TBranch        *b_el_EtringnoisedR03sig2;   //!
   TBranch        *b_el_EtringnoisedR03sig3;   //!
   TBranch        *b_el_EtringnoisedR03sig4;   //!
   TBranch        *b_el_isolationlikelihoodjets;   //!
   TBranch        *b_el_isolationlikelihoodhqelectrons;   //!
   TBranch        *b_el_electronweight;   //!
   TBranch        *b_el_electronbgweight;   //!
   TBranch        *b_el_softeweight;   //!
   TBranch        *b_el_softebgweight;   //!
   TBranch        *b_el_neuralnet;   //!
   TBranch        *b_el_Hmatrix;   //!
   TBranch        *b_el_Hmatrix5;   //!
   TBranch        *b_el_adaboost;   //!
   TBranch        *b_el_softeneuralnet;   //!
   TBranch        *b_el_zvertex;   //!
   TBranch        *b_el_errz;   //!
   TBranch        *b_el_etap;   //!
   TBranch        *b_el_depth;   //!
   TBranch        *b_el_breminvpt;   //!
   TBranch        *b_el_bremradius;   //!
   TBranch        *b_el_bremx;   //!
   TBranch        *b_el_bremclusterradius;   //!
   TBranch        *b_el_breminvpterr;   //!
   TBranch        *b_el_bremtrackauthor;   //!
   TBranch        *b_el_hasbrem;   //!
   TBranch        *b_el_bremdeltaqoverp;   //!
   TBranch        *b_el_bremmaterialtraversed;   //!
   TBranch        *b_el_refittedtrackqoverp;   //!
   TBranch        *b_el_refittedtrackd0;   //!
   TBranch        *b_el_refittedtrackz0;   //!
   TBranch        *b_el_refittedtracktheta;   //!
   TBranch        *b_el_refittedtrackphi;   //!
   TBranch        *b_el_Es0;   //!
   TBranch        *b_el_etas0;   //!
   TBranch        *b_el_phis0;   //!
   TBranch        *b_el_Es1;   //!
   TBranch        *b_el_etas1;   //!
   TBranch        *b_el_phis1;   //!
   TBranch        *b_el_Es2;   //!
   TBranch        *b_el_etas2;   //!
   TBranch        *b_el_phis2;   //!
   TBranch        *b_el_Es3;   //!
   TBranch        *b_el_etas3;   //!
   TBranch        *b_el_phis3;   //!
   TBranch        *b_el_E_PreSamplerB;   //!
   TBranch        *b_el_E_EMB1;   //!
   TBranch        *b_el_E_EMB2;   //!
   TBranch        *b_el_E_EMB3;   //!
   TBranch        *b_el_E_PreSamplerE;   //!
   TBranch        *b_el_E_EME1;   //!
   TBranch        *b_el_E_EME2;   //!
   TBranch        *b_el_E_EME3;   //!
   TBranch        *b_el_E_HEC0;   //!
   TBranch        *b_el_E_HEC1;   //!
   TBranch        *b_el_E_HEC2;   //!
   TBranch        *b_el_E_HEC3;   //!
   TBranch        *b_el_E_TileBar0;   //!
   TBranch        *b_el_E_TileBar1;   //!
   TBranch        *b_el_E_TileBar2;   //!
   TBranch        *b_el_E_TileGap1;   //!
   TBranch        *b_el_E_TileGap2;   //!
   TBranch        *b_el_E_TileGap3;   //!
   TBranch        *b_el_E_TileExt0;   //!
   TBranch        *b_el_E_TileExt1;   //!
   TBranch        *b_el_E_TileExt2;   //!
   TBranch        *b_el_E_FCAL0;   //!
   TBranch        *b_el_E_FCAL1;   //!
   TBranch        *b_el_E_FCAL2;   //!
   TBranch        *b_el_cl_E;   //!
   TBranch        *b_el_cl_pt;   //!
   TBranch        *b_el_cl_eta;   //!
   TBranch        *b_el_cl_phi;   //!
   TBranch        *b_el_firstEdens;   //!
   TBranch        *b_el_cellmaxfrac;   //!
   TBranch        *b_el_longitudinal;   //!
   TBranch        *b_el_secondlambda;   //!
   TBranch        *b_el_lateral;   //!
   TBranch        *b_el_secondR;   //!
   TBranch        *b_el_centerlambda;   //!
   TBranch        *b_el_rawcl_Es0;   //!
   TBranch        *b_el_rawcl_etas0;   //!
   TBranch        *b_el_rawcl_phis0;   //!
   TBranch        *b_el_rawcl_Es1;   //!
   TBranch        *b_el_rawcl_etas1;   //!
   TBranch        *b_el_rawcl_phis1;   //!
   TBranch        *b_el_rawcl_Es2;   //!
   TBranch        *b_el_rawcl_etas2;   //!
   TBranch        *b_el_rawcl_phis2;   //!
   TBranch        *b_el_rawcl_Es3;   //!
   TBranch        *b_el_rawcl_etas3;   //!
   TBranch        *b_el_rawcl_phis3;   //!
   TBranch        *b_el_rawcl_E;   //!
   TBranch        *b_el_rawcl_pt;   //!
   TBranch        *b_el_rawcl_eta;   //!
   TBranch        *b_el_rawcl_phi;   //!
   TBranch        *b_el_refittedtrackcovd0;   //!
   TBranch        *b_el_refittedtrackcovz0;   //!
   TBranch        *b_el_refittedtrackcovphi;   //!
   TBranch        *b_el_refittedtrackcovtheta;   //!
   TBranch        *b_el_refittedtrackcovqoverp;   //!
   TBranch        *b_el_refittedtrackcovd0z0;   //!
   TBranch        *b_el_refittedtrackcovz0phi;   //!
   TBranch        *b_el_refittedtrackcovz0theta;   //!
   TBranch        *b_el_refittedtrackcovz0qoverp;   //!
   TBranch        *b_el_refittedtrackcovd0phi;   //!
   TBranch        *b_el_refittedtrackcovd0theta;   //!
   TBranch        *b_el_refittedtrackcovd0qoverp;   //!
   TBranch        *b_el_refittedtrackcovphitheta;   //!
   TBranch        *b_el_refittedtrackcovphiqoverp;   //!
   TBranch        *b_el_refittedtrackcovthetaqoverp;   //!
   TBranch        *b_el_trackd0;   //!
   TBranch        *b_el_trackz0;   //!
   TBranch        *b_el_trackphi;   //!
   TBranch        *b_el_tracktheta;   //!
   TBranch        *b_el_trackqoverp;   //!
   TBranch        *b_el_trackpt;   //!
   TBranch        *b_el_tracketa;   //!
   TBranch        *b_el_trackcov_d0;   //!
   TBranch        *b_el_trackcov_z0;   //!
   TBranch        *b_el_trackcov_phi;   //!
   TBranch        *b_el_trackcov_theta;   //!
   TBranch        *b_el_trackcov_qoverp;   //!
   TBranch        *b_el_trackcov_d0_z0;   //!
   TBranch        *b_el_trackcov_d0_phi;   //!
   TBranch        *b_el_trackcov_d0_theta;   //!
   TBranch        *b_el_trackcov_d0_qoverp;   //!
   TBranch        *b_el_trackcov_z0_phi;   //!
   TBranch        *b_el_trackcov_z0_theta;   //!
   TBranch        *b_el_trackcov_z0_qoverp;   //!
   TBranch        *b_el_trackcov_phi_theta;   //!
   TBranch        *b_el_trackcov_phi_qoverp;   //!
   TBranch        *b_el_trackcov_theta_qoverp;   //!
   TBranch        *b_el_trackfitchi2;   //!
   TBranch        *b_el_trackfitndof;   //!
   TBranch        *b_el_nBLHits;   //!
   TBranch        *b_el_nPixHits;   //!
   TBranch        *b_el_nSCTHits;   //!
   TBranch        *b_el_nTRTHits;   //!
   TBranch        *b_el_nPixHoles;   //!
   TBranch        *b_el_nSCTHoles;   //!
   TBranch        *b_el_nBLSharedHits;   //!
   TBranch        *b_el_nPixSharedHits;   //!
   TBranch        *b_el_nSCTSharedHits;   //!
   TBranch        *b_el_nTRTHighTHits;   //!
   TBranch        *b_el_nTRTOutliers;   //!
   TBranch        *b_el_nTRTHighTOutliers;   //!
   TBranch        *b_el_nSiHits;   //!
   TBranch        *b_el_TRTHighTHitsRatio;   //!
   TBranch        *b_el_pixeldEdx;   //!
   TBranch        *b_el_eProbabilityComb;   //!
   TBranch        *b_el_eProbabilityHT;   //!
   TBranch        *b_el_eProbabilityToT;   //!
   TBranch        *b_el_eProbabilityBrem;   //!
   TBranch        *b_el_vertx;   //!
   TBranch        *b_el_verty;   //!
   TBranch        *b_el_vertz;   //!
   TBranch        *b_el_hastrack;   //!
   TBranch        *b_el_deltaEmax2;   //!
   TBranch        *b_el_trackd0beam;   //!
   TBranch        *b_el_tracksigd0beam;   //!
   TBranch        *b_el_trackd0pv;   //!
   TBranch        *b_el_tracksigd0pv;   //!
   TBranch        *b_el_trackz0pv;   //!
   TBranch        *b_el_tracksigz0pv;   //!
   TBranch        *b_el_trackd0pvunbiased;   //!
   TBranch        *b_el_tracksigd0pvunbiased;   //!
   TBranch        *b_el_trackz0pvunbiased;   //!
   TBranch        *b_el_tracksigz0pvunbiased;   //!
   TBranch        *b_el_jetcone_n;   //!
   TBranch        *b_el_jetcone_dr;   //!
   TBranch        *b_el_jetcone_signedIP;   //!
   TBranch        *b_el_jetcone_ptrel;   //!
   TBranch        *b_el_jetcone_index;   //!
   TBranch        *b_el_jetcone_E;   //!
   TBranch        *b_el_jetcone_pt;   //!
   TBranch        *b_el_jetcone_m;   //!
   TBranch        *b_el_jetcone_eta;   //!
   TBranch        *b_el_jetcone_phi;   //!
   TBranch        *b_el_isIso;   //!
   TBranch        *b_el_jet_dr;   //!
   TBranch        *b_el_jet_E;   //!
   TBranch        *b_el_jet_pt;   //!
   TBranch        *b_el_jet_m;   //!
   TBranch        *b_el_jet_eta;   //!
   TBranch        *b_el_jet_phi;   //!
   TBranch        *b_el_jet_matched;   //!
   TBranch        *b_el_Etcone40_pt_corrected;   //!
   TBranch        *b_el_Etcone40_ED_corrected;   //!
   TBranch        *b_el_Etcone40_corrected;   //!
   TBranch        *b_el_EF_dr;   //!
   TBranch        *b_el_EF_index;   //!
   TBranch        *b_el_L2_dr;   //!
   TBranch        *b_el_L2_index;   //!
   TBranch        *b_el_L1_dr;   //!
   TBranch        *b_el_L1_index;   //!
   TBranch        *b_el_EF_E;   //!
   TBranch        *b_el_EF_Et;   //!
   TBranch        *b_el_EF_pt;   //!
   TBranch        *b_el_EF_eta;   //!
   TBranch        *b_el_EF_phi;   //!
   TBranch        *b_el_EF_charge;   //!
   TBranch        *b_el_EF_Ethad;   //!
   TBranch        *b_el_EF_Ethad1;   //!
   TBranch        *b_el_EF_f1;   //!
   TBranch        *b_el_EF_Emins1;   //!
   TBranch        *b_el_EF_fside;   //!
   TBranch        *b_el_EF_Emax2;   //!
   TBranch        *b_el_EF_ws3;   //!
   TBranch        *b_el_EF_wstot;   //!
   TBranch        *b_el_EF_E233;   //!
   TBranch        *b_el_EF_E237;   //!
   TBranch        *b_el_EF_E277;   //!
   TBranch        *b_el_EF_weta2;   //!
   TBranch        *b_el_EF_rphiallcalo;   //!
   TBranch        *b_el_EF_deltaeta1;   //!
   TBranch        *b_el_EF_deltaeta2;   //!
   TBranch        *b_el_EF_deltaphi2;   //!
   TBranch        *b_el_EF_expectHitInBLayer;   //!
   TBranch        *b_el_EF_Etcone45;   //!
   TBranch        *b_el_EF_Etcone20;   //!
   TBranch        *b_el_EF_Etcone30;   //!
   TBranch        *b_el_EF_Etcone40;   //!
   TBranch        *b_el_EF_etacorrmag;   //!
   TBranch        *b_el_EF_zvertex;   //!
   TBranch        *b_el_EF_errz;   //!
   TBranch        *b_el_EF_trackd0;   //!
   TBranch        *b_el_EF_trackz0;   //!
   TBranch        *b_el_EF_trackphi;   //!
   TBranch        *b_el_EF_tracktheta;   //!
   TBranch        *b_el_EF_trackqoverp;   //!
   TBranch        *b_el_EF_trackpt;   //!
   TBranch        *b_el_EF_tracketa;   //!
   TBranch        *b_el_EF_nBLHits;   //!
   TBranch        *b_el_EF_nPixHits;   //!
   TBranch        *b_el_EF_nSCTHits;   //!
   TBranch        *b_el_EF_nTRTHits;   //!
   TBranch        *b_el_EF_nTRTHighTHits;   //!
   TBranch        *b_el_EF_nSiHits;   //!
   TBranch        *b_el_EF_TRTHighTHitsRatio;   //!
   TBranch        *b_el_EF_pixeldEdx;   //!
   TBranch        *b_el_EF_hastrack;   //!
   TBranch        *b_el_EF_matched;   //!
   TBranch        *b_el_L2_E;   //!
   TBranch        *b_el_L2_Et;   //!
   TBranch        *b_el_L2_pt;   //!
   TBranch        *b_el_L2_eta;   //!
   TBranch        *b_el_L2_phi;   //!
   TBranch        *b_el_L2_charge;   //!
   TBranch        *b_el_L2_Ethad1;   //!
   TBranch        *b_el_L2_reta;   //!
   TBranch        *b_el_L2_Eratio;   //!
   TBranch        *b_el_L2_trackclusterdeta;   //!
   TBranch        *b_el_L2_trackclusterdphi;   //!
   TBranch        *b_el_L2_Etoverpt;   //!
   TBranch        *b_el_L2_trackpt;   //!
   TBranch        *b_el_L2_trackalgo;   //!
   TBranch        *b_el_L2_tracketa;   //!
   TBranch        *b_el_L2_trackd0;   //!
   TBranch        *b_el_L2_trackz0;   //!
   TBranch        *b_el_L2_tracktheta;   //!
   TBranch        *b_el_L2_trackphi;   //!
   TBranch        *b_el_L2_tracketaatcalo;   //!
   TBranch        *b_el_L2_trackphiatcalo;   //!
   TBranch        *b_el_L2_errpt;   //!
   TBranch        *b_el_L2_erreta;   //!
   TBranch        *b_el_L2_errphi;   //!
   TBranch        *b_el_L2_E237;   //!
   TBranch        *b_el_L2_E277;   //!
   TBranch        *b_el_L2_fside;   //!
   TBranch        *b_el_L2_weta2;   //!
   TBranch        *b_el_L2_Emaxs1;   //!
   TBranch        *b_el_L2_Emax2;   //!
   TBranch        *b_el_L2_matched;   //!
   TBranch        *b_el_L1_eta;   //!
   TBranch        *b_el_L1_phi;   //!
   TBranch        *b_el_L1_EMisol;   //!
   TBranch        *b_el_L1_hadisol;   //!
   TBranch        *b_el_L1_hadcore;   //!
   TBranch        *b_el_L1_pt;   //!
   TBranch        *b_el_L1_Et;   //!
   TBranch        *b_el_L1_matched;   //!
   TBranch        *b_EF_2e10_loose;   //!
   TBranch        *b_EF_2e10_medium;   //!
   TBranch        *b_EF_2e15_loose;   //!
   TBranch        *b_EF_2e3_loose;   //!
   TBranch        *b_EF_2e3_loose_SiTrk;   //!
   TBranch        *b_EF_2e3_loose_TRT;   //!
   TBranch        *b_EF_2e3_medium;   //!
   TBranch        *b_EF_2e3_medium_SiTrk;   //!
   TBranch        *b_EF_2e3_medium_TRT;   //!
   TBranch        *b_EF_2e3_tight;   //!
   TBranch        *b_EF_2e5_medium;   //!
   TBranch        *b_EF_2e5_medium_SiTrk;   //!
   TBranch        *b_EF_2e5_medium_TRT;   //!
   TBranch        *b_EF_2e5_tight;   //!
   TBranch        *b_EF_2g10_loose;   //!
   TBranch        *b_EF_2g15_loose;   //!
   TBranch        *b_EF_2g5_loose;   //!
   TBranch        *b_EF_2g7_loose;   //!
   TBranch        *b_EF_2j20_deta3_5_jetNoEF;   //!
   TBranch        *b_EF_2j20_deta5_jetNoEF;   //!
   TBranch        *b_EF_2j20_jetNoEF;   //!
   TBranch        *b_EF_2j25_j45_anymct100_NoEF;   //!
   TBranch        *b_EF_2j25_j45_anymct150_NoEF;   //!
   TBranch        *b_EF_2j25_j45_anymct175_NoEF;   //!
   TBranch        *b_EF_2j25_j45_dphi03_NoEF;   //!
   TBranch        *b_EF_2j25_j45_leadingmct100_NoEF;   //!
   TBranch        *b_EF_2j25_j45_leadingmct150_NoEF;   //!
   TBranch        *b_EF_2j25_j45_leadingmct175_NoEF;   //!
   TBranch        *b_EF_2j25_j70_anymct150_NoEF;   //!
   TBranch        *b_EF_2j25_j70_anymct175_NoEF;   //!
   TBranch        *b_EF_2j25_j70_dphi03_NoEF;   //!
   TBranch        *b_EF_2j25_j70_leadingmct150_NoEF;   //!
   TBranch        *b_EF_2j25_j70_leadingmct175_NoEF;   //!
   TBranch        *b_EF_2j30_anymct100_NoEF;   //!
   TBranch        *b_EF_2j30_anymct150_NoEF;   //!
   TBranch        *b_EF_2j30_anymct175_NoEF;   //!
   TBranch        *b_EF_2j30_deta3_5_jetNoEF;   //!
   TBranch        *b_EF_2j30_j90_dphi03_NoEF;   //!
   TBranch        *b_EF_2j30_jetNoEF;   //!
   TBranch        *b_EF_2j30_leadingmct100_NoEF;   //!
   TBranch        *b_EF_2j30_leadingmct150_NoEF;   //!
   TBranch        *b_EF_2j30_leadingmct175_NoEF;   //!
   TBranch        *b_EF_2j35_deta3_5_jetNoEF;   //!
   TBranch        *b_EF_2j35_jetNoEF;   //!
   TBranch        *b_EF_2j35_jetNoEF_xe20_noMu;   //!
   TBranch        *b_EF_2j35_jetNoEF_xe30_noMu;   //!
   TBranch        *b_EF_2j35_jetNoEF_xe40_noMu;   //!
   TBranch        *b_EF_2j50_jetNoEF;   //!
   TBranch        *b_EF_2j75_jetNoEF;   //!
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
   TBranch        *b_EF_2mu4_Upsimumu;   //!
   TBranch        *b_EF_2mu6;   //!
   TBranch        *b_EF_2mu6_MG;   //!
   TBranch        *b_EF_2mu6_NoAlg;   //!
   TBranch        *b_EF_3j20_j50_jetNoEF;   //!
   TBranch        *b_EF_3j30_2j50_jetNoEF;   //!
   TBranch        *b_EF_3j30_jetNoEF;   //!
   TBranch        *b_EF_3j35_jetNoEF;   //!
   TBranch        *b_EF_3j50_jetNoEF;   //!
   TBranch        *b_EF_4j20_j35_jetNoEF;   //!
   TBranch        *b_EF_4j20_j50_jetNoEF;   //!
   TBranch        *b_EF_4j30_3j35_jetNoEF;   //!
   TBranch        *b_EF_4j30_jetNoEF;   //!
   TBranch        *b_EF_4j35_jetNoEF;   //!
   TBranch        *b_EF_4j50_jetNoEF;   //!
   TBranch        *b_EF_5j30_jetNoEF;   //!
   TBranch        *b_EF_6j30_jetNoEF;   //!
   TBranch        *b_EF_e10_NoCut;   //!
   TBranch        *b_EF_e10_loose;   //!
   TBranch        *b_EF_e10_loose_mu10;   //!
   TBranch        *b_EF_e10_loose_mu6;   //!
   TBranch        *b_EF_e10_medium;   //!
   TBranch        *b_EF_e10_medium_IDTrkNoCut;   //!
   TBranch        *b_EF_e10_medium_SiTrk;   //!
   TBranch        *b_EF_e10_medium_TRT;   //!
   TBranch        *b_EF_e10_tight;   //!
   TBranch        *b_EF_e15_loose;   //!
   TBranch        *b_EF_e15_loose_IDTrkNoCut;   //!
   TBranch        *b_EF_e15_medium;   //!
   TBranch        *b_EF_e15_medium_SiTrk;   //!
   TBranch        *b_EF_e15_medium_TRT;   //!
   TBranch        *b_EF_e15_tight;   //!
   TBranch        *b_EF_e18_medium;   //!
   TBranch        *b_EF_e20_loose;   //!
   TBranch        *b_EF_e20_loose_IDTrkNoCut;   //!
   TBranch        *b_EF_e20_loose_passEF;   //!
   TBranch        *b_EF_e20_loose_passL2;   //!
   TBranch        *b_EF_e20_loose_xe20_noMu;   //!
   TBranch        *b_EF_e20_loose_xe30_noMu;   //!
   TBranch        *b_EF_e20_medium;   //!
   TBranch        *b_EF_e25_loose;   //!
   TBranch        *b_EF_e30_loose;   //!
   TBranch        *b_EF_e3_loose;   //!
   TBranch        *b_EF_e3_loose_SiTrk;   //!
   TBranch        *b_EF_e3_loose_TRT;   //!
   TBranch        *b_EF_e3_medium;   //!
   TBranch        *b_EF_e3_medium_SiTrk;   //!
   TBranch        *b_EF_e3_medium_TRT;   //!
   TBranch        *b_EF_e5_NoCut_firstempty;   //!
   TBranch        *b_EF_e5_medium;   //!
   TBranch        *b_EF_e5_medium_MV;   //!
   TBranch        *b_EF_e5_medium_SiTrk;   //!
   TBranch        *b_EF_e5_medium_TRT;   //!
   TBranch        *b_EF_e5_medium_mu4;   //!
   TBranch        *b_EF_e5_tight;   //!
   TBranch        *b_EF_e5_tight_SiTrk;   //!
   TBranch        *b_EF_e5_tight_TRT;   //!
   TBranch        *b_EF_e5_tight_e5_NoCut;   //!
   TBranch        *b_EF_eb_physics;   //!
   TBranch        *b_EF_eb_physics_empty;   //!
   TBranch        *b_EF_eb_physics_firstempty;   //!
   TBranch        *b_EF_eb_physics_unpaired_iso;   //!
   TBranch        *b_EF_eb_physics_unpaired_noniso;   //!
   TBranch        *b_EF_eb_random;   //!
   TBranch        *b_EF_eb_random_empty;   //!
   TBranch        *b_EF_eb_random_firstempty;   //!
   TBranch        *b_EF_eb_random_unpaired_iso;   //!
   TBranch        *b_EF_em105_passHLT;   //!
   TBranch        *b_EF_fj10_empty_NoAlg;   //!
   TBranch        *b_EF_fj30_jetNoEF;   //!
   TBranch        *b_EF_fj30_jetNoEF_larcalib;   //!
   TBranch        *b_EF_fj50_jetNoEF;   //!
   TBranch        *b_EF_fj50_jetNoEF_larcalib;   //!
   TBranch        *b_EF_fj75_jetNoEF;   //!
   TBranch        *b_EF_fj95_jetNoCut_larcalib;   //!
   TBranch        *b_EF_g10_loose;   //!
   TBranch        *b_EF_g10_loose_larcalib;   //!
   TBranch        *b_EF_g11_etcut;   //!
   TBranch        *b_EF_g15_loose;   //!
   TBranch        *b_EF_g17_etcut;   //!
   TBranch        *b_EF_g17_etcut_EFxe20_noMu;   //!
   TBranch        *b_EF_g17_etcut_EFxe30_noMu;   //!
   TBranch        *b_EF_g20_loose;   //!
   TBranch        *b_EF_g20_loose_larcalib;   //!
   TBranch        *b_EF_g20_loose_xe20_noMu;   //!
   TBranch        *b_EF_g20_loose_xe30_noMu;   //!
   TBranch        *b_EF_g20_tight;   //!
   TBranch        *b_EF_g25_loose_xe30_noMu;   //!
   TBranch        *b_EF_g30_loose;   //!
   TBranch        *b_EF_g30_tight;   //!
   TBranch        *b_EF_g3_NoCut_unpaired_iso;   //!
   TBranch        *b_EF_g3_NoCut_unpaired_noniso;   //!
   TBranch        *b_EF_g40_loose;   //!
   TBranch        *b_EF_g40_loose_larcalib;   //!
   TBranch        *b_EF_g40_tight;   //!
   TBranch        *b_EF_g50_loose;   //!
   TBranch        *b_EF_g50_loose_larcalib;   //!
   TBranch        *b_EF_g5_NoCut_cosmic;   //!
   TBranch        *b_EF_g5_loose;   //!
   TBranch        *b_EF_g5_loose_larcalib;   //!
   TBranch        *b_EF_g7_loose;   //!
   TBranch        *b_EF_j115_jetNoCut_larcalib;   //!
   TBranch        *b_EF_j20_jetNoEF;   //!
   TBranch        *b_EF_j20_jetNoEF_larcalib;   //!
   TBranch        *b_EF_j30_fj30_jetNoEF;   //!
   TBranch        *b_EF_j30_jetNoCut_cosmic;   //!
   TBranch        *b_EF_j30_jetNoCut_firstempty;   //!
   TBranch        *b_EF_j30_jetNoCut_unpaired;   //!
   TBranch        *b_EF_j30_jetNoEF;   //!
   TBranch        *b_EF_j35_L1TAU_HV_jetNoEF;   //!
   TBranch        *b_EF_j35_jetNoEF;   //!
   TBranch        *b_EF_j50_jetNoCut_cosmic;   //!
   TBranch        *b_EF_j50_jetNoCut_firstempty;   //!
   TBranch        *b_EF_j50_jetNoCut_unpaired;   //!
   TBranch        *b_EF_j50_jetNoEF;   //!
   TBranch        *b_EF_j50_jetNoEF_larcalib;   //!
   TBranch        *b_EF_j50_jetNoEF_xe20_noMu;   //!
   TBranch        *b_EF_j50_jetNoEF_xe30_noMu;   //!
   TBranch        *b_EF_j50_jetNoEF_xe40_noMu;   //!
   TBranch        *b_EF_j5_empty_NoAlg;   //!
   TBranch        *b_EF_j5_unpaired_iso_NoAlg;   //!
   TBranch        *b_EF_j5_unpaired_noniso_NoAlg;   //!
   TBranch        *b_EF_j75_jetNoEF;   //!
   TBranch        *b_EF_j75_jetNoEF_EFxe20_noMu;   //!
   TBranch        *b_EF_j75_jetNoEF_EFxe25_noMu;   //!
   TBranch        *b_EF_j75_jetNoEF_EFxe30_noMu;   //!
   TBranch        *b_EF_j75_jetNoEF_EFxe35_noMu;   //!
   TBranch        *b_EF_j75_jetNoEF_EFxe40_noMu;   //!
   TBranch        *b_EF_j95_jetNoEF;   //!
   TBranch        *b_EF_j95_jetNoEF_larcalib;   //!
   TBranch        *b_EF_je135_NoEF;   //!
   TBranch        *b_EF_je195_NoEF;   //!
   TBranch        *b_EF_je255_NoEF;   //!
   TBranch        *b_EF_je300_NoEF;   //!
   TBranch        *b_EF_je350_NoEF;   //!
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
   TBranch        *b_EF_mu10_IDTrkNoCut;   //!
   TBranch        *b_EF_mu10_MG;   //!
   TBranch        *b_EF_mu10_MSonly;   //!
   TBranch        *b_EF_mu10_MSonly_tight;   //!
   TBranch        *b_EF_mu10_NoAlg;   //!
   TBranch        *b_EF_mu10_SiTrk;   //!
   TBranch        *b_EF_mu10_tight;   //!
   TBranch        *b_EF_mu10i_loose;   //!
   TBranch        *b_EF_mu13;   //!
   TBranch        *b_EF_mu13_MG;   //!
   TBranch        *b_EF_mu13_MG_tight;   //!
   TBranch        *b_EF_mu13_tight;   //!
   TBranch        *b_EF_mu15;   //!
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
   TBranch        *b_EF_mu4_j20_jetNoEF;   //!
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
   TBranch        *b_EF_mu4mu6_Upsimumu;   //!
   TBranch        *b_EF_mu6;   //!
   TBranch        *b_EF_mu6_Bmumu;   //!
   TBranch        *b_EF_mu6_BmumuX;   //!
   TBranch        *b_EF_mu6_DiMu;   //!
   TBranch        *b_EF_mu6_IDTrkNoCut;   //!
   TBranch        *b_EF_mu6_Jpsie5e3;   //!
   TBranch        *b_EF_mu6_Jpsie5e3_FS;   //!
   TBranch        *b_EF_mu6_Jpsimumu;   //!
   TBranch        *b_EF_mu6_MG;   //!
   TBranch        *b_EF_mu6_MSonly;   //!
   TBranch        *b_EF_mu6_MSonly_outOfTime;   //!
   TBranch        *b_EF_mu6_NoAlg;   //!
   TBranch        *b_EF_mu6_SiTrk;   //!
   TBranch        *b_EF_mu6_Trk_Jpsi;   //!
   TBranch        *b_EF_mu6_Upsimumu_FS;   //!
   TBranch        *b_EF_mu6_muCombTag;   //!
   TBranch        *b_EF_tau125_loose;   //!
   TBranch        *b_EF_tau125_medium;   //!
   TBranch        *b_EF_tau12_IDTrkNoCut;   //!
   TBranch        *b_EF_tau12_loose;   //!
   TBranch        *b_EF_tau12_loose_2b15;   //!
   TBranch        *b_EF_tau12_loose_3j35_jetNoEF;   //!
   TBranch        *b_EF_tau12_loose_EFxe12_noMu;   //!
   TBranch        *b_EF_tau12_loose_IdScan_EFxe12_noMu;   //!
   TBranch        *b_EF_tau12_loose_IdScan_xe15_noMu;   //!
   TBranch        *b_EF_tau12_loose_e10_loose;   //!
   TBranch        *b_EF_tau12_loose_e10_medium;   //!
   TBranch        *b_EF_tau12_loose_e10_tight;   //!
   TBranch        *b_EF_tau12_loose_mu10;   //!
   TBranch        *b_EF_tau12_loose_xe15_noMu;   //!
   TBranch        *b_EF_tau12_loose_xe20_noMu;   //!
   TBranch        *b_EF_tau16_loose;   //!
   TBranch        *b_EF_tau16_loose_2b15;   //!
   TBranch        *b_EF_tau16_loose_3j35_jetNoEF;   //!
   TBranch        *b_EF_tau16_loose_e10_loose;   //!
   TBranch        *b_EF_tau16_loose_e15_loose;   //!
   TBranch        *b_EF_tau16_loose_mu10;   //!
   TBranch        *b_EF_tau16_loose_mu15;   //!
   TBranch        *b_EF_tau16_loose_xe20_noMu;   //!
   TBranch        *b_EF_tau16_loose_xe25_noMu;   //!
   TBranch        *b_EF_tau16_loose_xe25_tight_noMu;   //!
   TBranch        *b_EF_tau16_loose_xe30_noMu;   //!
   TBranch        *b_EF_tau16_medium;   //!
   TBranch        *b_EF_tau16_medium_xe22_noMu;   //!
   TBranch        *b_EF_tau16_medium_xe25_noMu;   //!
   TBranch        *b_EF_tau16_medium_xe25_tight_noMu;   //!
   TBranch        *b_EF_tau20_loose;   //!
   TBranch        *b_EF_tau20_loose_xe25_noMu;   //!
   TBranch        *b_EF_tau29_loose;   //!
   TBranch        *b_EF_tau38_loose;   //!
   TBranch        *b_EF_tau38_medium;   //!
   TBranch        *b_EF_tau50_IDTrkNoCut;   //!
   TBranch        *b_EF_tau50_loose;   //!
   TBranch        *b_EF_tau50_loose_IdScan;   //!
   TBranch        *b_EF_tau50_medium;   //!
   TBranch        *b_EF_tau84_loose;   //!
   TBranch        *b_EF_tau84_medium;   //!
   TBranch        *b_EF_tauNoCut;   //!
   TBranch        *b_EF_tauNoCut_IdScan;   //!
   TBranch        *b_EF_tauNoCut_cosmic;   //!
   TBranch        *b_EF_tauNoCut_firstempty;   //!
   TBranch        *b_EF_tauNoCut_hasTrk6_EFxe15_noMu;   //!
   TBranch        *b_EF_tauNoCut_hasTrk6_IdScan_EFxe15_noMu;   //!
   TBranch        *b_EF_tauNoCut_hasTrk6_IdScan_xe20_noMu;   //!
   TBranch        *b_EF_tauNoCut_hasTrk6_xe20_noMu;   //!
   TBranch        *b_EF_tauNoCut_hasTrk9_xe20_noMu;   //!
   TBranch        *b_EF_tauNoCut_hasTrk_MV;   //!
   TBranch        *b_EF_tauNoCut_hasTrk_e10_tight;   //!
   TBranch        *b_EF_tauNoCut_hasTrk_xe20_noMu;   //!
   TBranch        *b_EF_tauNoCut_unpaired_iso;   //!
   TBranch        *b_EF_tauNoCut_unpaired_noniso;   //!
   TBranch        *b_EF_xe15_noMu;   //!
   TBranch        *b_EF_xe15_unbiased_noMu;   //!
   TBranch        *b_EF_xe20;   //!
   TBranch        *b_EF_xe20_noMu;   //!
   TBranch        *b_EF_xe20_tight_noMu;   //!
   TBranch        *b_EF_xe25_medium_noMu;   //!
   TBranch        *b_EF_xe25_noMu;   //!
   TBranch        *b_EF_xe25_tight_noMu;   //!
   TBranch        *b_EF_xe30_allL1;   //!
   TBranch        *b_EF_xe30_allL1_FEB;   //!
   TBranch        *b_EF_xe30_allL1_allCells;   //!
   TBranch        *b_EF_xe30_loose_noMu;   //!
   TBranch        *b_EF_xe30_medium_noMu;   //!
   TBranch        *b_EF_xe30_noMu;   //!
   TBranch        *b_EF_xe30_tight_noMu;   //!
   TBranch        *b_EF_xe35_loose_noMu;   //!
   TBranch        *b_EF_xe35_noMu;   //!
   TBranch        *b_EF_xe35_tight_noMu;   //!
   TBranch        *b_EF_xe40_noMu;   //!
   TBranch        *b_EF_xe45_noMu;   //!
   TBranch        *b_EF_xe55_noMu;   //!
   TBranch        *b_EF_xe60_medium_noMu;   //!
   TBranch        *b_EF_xe80_medium_noMu;   //!
   TBranch        *b_L1_2EM10;   //!
   TBranch        *b_L1_2EM14;   //!
   TBranch        *b_L1_2EM2;   //!
   TBranch        *b_L1_2EM3;   //!
   TBranch        *b_L1_2EM5;   //!
   TBranch        *b_L1_2J10;   //!
   TBranch        *b_L1_2J10_J30;   //!
   TBranch        *b_L1_2J10_J55;   //!
   TBranch        *b_L1_2J15;   //!
   TBranch        *b_L1_2J15_J75;   //!
   TBranch        *b_L1_2J15_XE10;   //!
   TBranch        *b_L1_2J15_XE15;   //!
   TBranch        *b_L1_2J15_XE25;   //!
   TBranch        *b_L1_2J30;   //!
   TBranch        *b_L1_2J5;   //!
   TBranch        *b_L1_2J55;   //!
   TBranch        *b_L1_2J95;   //!
   TBranch        *b_L1_2MU0;   //!
   TBranch        *b_L1_2MU0_FIRSTEMPTY;   //!
   TBranch        *b_L1_2MU0_MU6;   //!
   TBranch        *b_L1_2MU10;   //!
   TBranch        *b_L1_2MU20;   //!
   TBranch        *b_L1_2MU6;   //!
   TBranch        *b_L1_2MU6_EM5;   //!
   TBranch        *b_L1_2TAU11;   //!
   TBranch        *b_L1_2TAU5;   //!
   TBranch        *b_L1_2TAU5_EM5;   //!
   TBranch        *b_L1_2TAU6;   //!
   TBranch        *b_L1_2TAU6_EM10;   //!
   TBranch        *b_L1_2TAU6_EM5;   //!
   TBranch        *b_L1_3J10;   //!
   TBranch        *b_L1_3J10_2J30;   //!
   TBranch        *b_L1_3J15;   //!
   TBranch        *b_L1_3J30;   //!
   TBranch        *b_L1_3J5_J30;   //!
   TBranch        *b_L1_4J10;   //!
   TBranch        *b_L1_4J10_3J15;   //!
   TBranch        *b_L1_4J10_EM10;   //!
   TBranch        *b_L1_4J10_MU15;   //!
   TBranch        *b_L1_4J15;   //!
   TBranch        *b_L1_4J30;   //!
   TBranch        *b_L1_4J5;   //!
   TBranch        *b_L1_4J5_J15;   //!
   TBranch        *b_L1_4J5_J30;   //!
   TBranch        *b_L1_5J10;   //!
   TBranch        *b_L1_6J10;   //!
   TBranch        *b_L1_EM10;   //!
   TBranch        *b_L1_EM10I;   //!
   TBranch        *b_L1_EM14;   //!
   TBranch        *b_L1_EM14I;   //!
   TBranch        *b_L1_EM14_XE10;   //!
   TBranch        *b_L1_EM14_XE15;   //!
   TBranch        *b_L1_EM2;   //!
   TBranch        *b_L1_EM2_UNPAIRED_ISO;   //!
   TBranch        *b_L1_EM2_UNPAIRED_NONISO;   //!
   TBranch        *b_L1_EM3;   //!
   TBranch        *b_L1_EM3_EMPTY;   //!
   TBranch        *b_L1_EM3_FIRSTEMPTY;   //!
   TBranch        *b_L1_EM3_MV;   //!
   TBranch        *b_L1_EM5;   //!
   TBranch        *b_L1_EM5_MU10;   //!
   TBranch        *b_L1_EM5_MU6;   //!
   TBranch        *b_L1_EM85;   //!
   TBranch        *b_L1_FJ10;   //!
   TBranch        *b_L1_FJ10_EMPTY;   //!
   TBranch        *b_L1_FJ10_FIRSTEMPTY;   //!
   TBranch        *b_L1_FJ10_UNPAIRED_ISO;   //!
   TBranch        *b_L1_FJ30;   //!
   TBranch        *b_L1_FJ55;   //!
   TBranch        *b_L1_FJ95;   //!
   TBranch        *b_L1_J10;   //!
   TBranch        *b_L1_J10_EMPTY;   //!
   TBranch        *b_L1_J10_FIRSTEMPTY;   //!
   TBranch        *b_L1_J10_FJ10;   //!
   TBranch        *b_L1_J10_MV;   //!
   TBranch        *b_L1_J10_UNPAIRED;   //!
   TBranch        *b_L1_J115;   //!
   TBranch        *b_L1_J15;   //!
   TBranch        *b_L1_J15_LV;   //!
   TBranch        *b_L1_J15_MV;   //!
   TBranch        *b_L1_J15_NL;   //!
   TBranch        *b_L1_J15_XE15_EM10;   //!
   TBranch        *b_L1_J15_XE15_MU15;   //!
   TBranch        *b_L1_J30;   //!
   TBranch        *b_L1_J30_EMPTY;   //!
   TBranch        *b_L1_J30_FIRSTEMPTY;   //!
   TBranch        *b_L1_J30_UNPAIRED;   //!
   TBranch        *b_L1_J30_XE10;   //!
   TBranch        *b_L1_J30_XE15;   //!
   TBranch        *b_L1_J30_XE25;   //!
   TBranch        *b_L1_J5;   //!
   TBranch        *b_L1_J55;   //!
   TBranch        *b_L1_J5_EMPTY;   //!
   TBranch        *b_L1_J5_FIRSTEMPTY;   //!
   TBranch        *b_L1_J5_UNPAIRED_ISO;   //!
   TBranch        *b_L1_J5_UNPAIRED_NONISO;   //!
   TBranch        *b_L1_J75;   //!
   TBranch        *b_L1_J95;   //!
   TBranch        *b_L1_JE100;   //!
   TBranch        *b_L1_JE140;   //!
   TBranch        *b_L1_JE200;   //!
   TBranch        *b_L1_JE60;   //!
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
   TBranch        *b_L1_RD0_EMPTY;   //!
   TBranch        *b_L1_RD0_FILLED;   //!
   TBranch        *b_L1_RD0_FIRSTEMPTY;   //!
   TBranch        *b_L1_RD0_UNPAIRED_ISO;   //!
   TBranch        *b_L1_RD1_EMPTY;   //!
   TBranch        *b_L1_RD1_FILLED;   //!
   TBranch        *b_L1_TAU11;   //!
   TBranch        *b_L1_TAU11I;   //!
   TBranch        *b_L1_TAU20;   //!
   TBranch        *b_L1_TAU30;   //!
   TBranch        *b_L1_TAU5;   //!
   TBranch        *b_L1_TAU50;   //!
   TBranch        *b_L1_TAU5_3J5_2J15;   //!
   TBranch        *b_L1_TAU5_4J5_3J15;   //!
   TBranch        *b_L1_TAU5_EMPTY;   //!
   TBranch        *b_L1_TAU5_FIRSTEMPTY;   //!
   TBranch        *b_L1_TAU5_MU6;   //!
   TBranch        *b_L1_TAU5_MV;   //!
   TBranch        *b_L1_TAU5_UNPAIRED_ISO;   //!
   TBranch        *b_L1_TAU5_UNPAIRED_NONISO;   //!
   TBranch        *b_L1_TAU5_XE10;   //!
   TBranch        *b_L1_TAU6;   //!
   TBranch        *b_L1_TAU6I;   //!
   TBranch        *b_L1_TAU6_3J5_2J15;   //!
   TBranch        *b_L1_TAU6_4J5_3J15;   //!
   TBranch        *b_L1_TAU6_MU10;   //!
   TBranch        *b_L1_TAU6_MU15;   //!
   TBranch        *b_L1_TAU6_XE10;   //!
   TBranch        *b_L1_TE100;   //!
   TBranch        *b_L1_TE180;   //!
   TBranch        *b_L1_TE20;   //!
   TBranch        *b_L1_TE50;   //!
   TBranch        *b_L1_XE10;   //!
   TBranch        *b_L1_XE15;   //!
   TBranch        *b_L1_XE20;   //!
   TBranch        *b_L1_XE25;   //!
   TBranch        *b_L1_XE30;   //!
   TBranch        *b_L1_XE35;   //!
   TBranch        *b_L1_XE40;   //!
   TBranch        *b_L1_XE50;   //!
   TBranch        *b_L1_ZB;   //!
   TBranch        *b_L2_2e10_loose;   //!
   TBranch        *b_L2_2e10_medium;   //!
   TBranch        *b_L2_2e15_loose;   //!
   TBranch        *b_L2_2e3_loose;   //!
   TBranch        *b_L2_2e3_loose_SiTrk;   //!
   TBranch        *b_L2_2e3_loose_TRT;   //!
   TBranch        *b_L2_2e3_medium;   //!
   TBranch        *b_L2_2e3_medium_SiTrk;   //!
   TBranch        *b_L2_2e3_medium_TRT;   //!
   TBranch        *b_L2_2e3_tight;   //!
   TBranch        *b_L2_2e5_medium;   //!
   TBranch        *b_L2_2e5_medium_SiTrk;   //!
   TBranch        *b_L2_2e5_medium_TRT;   //!
   TBranch        *b_L2_2e5_tight;   //!
   TBranch        *b_L2_2g10_loose;   //!
   TBranch        *b_L2_2g15_loose;   //!
   TBranch        *b_L2_2g5_loose;   //!
   TBranch        *b_L2_2g7_loose;   //!
   TBranch        *b_L2_2j15;   //!
   TBranch        *b_L2_2j15_deta3_5;   //!
   TBranch        *b_L2_2j15_deta5;   //!
   TBranch        *b_L2_2j25;   //!
   TBranch        *b_L2_2j25_deta3_5;   //!
   TBranch        *b_L2_2j25_j45_anymct100;   //!
   TBranch        *b_L2_2j25_j45_anymct150;   //!
   TBranch        *b_L2_2j25_j45_anymct175;   //!
   TBranch        *b_L2_2j25_j45_dphi03;   //!
   TBranch        *b_L2_2j25_j45_leadingmct100;   //!
   TBranch        *b_L2_2j25_j45_leadingmct150;   //!
   TBranch        *b_L2_2j25_j45_leadingmct175;   //!
   TBranch        *b_L2_2j25_j70_anymct150;   //!
   TBranch        *b_L2_2j25_j70_anymct175;   //!
   TBranch        *b_L2_2j25_j70_dphi03;   //!
   TBranch        *b_L2_2j25_j70_leadingmct150;   //!
   TBranch        *b_L2_2j25_j70_leadingmct175;   //!
   TBranch        *b_L2_2j30;   //!
   TBranch        *b_L2_2j30_anymct100;   //!
   TBranch        *b_L2_2j30_anymct150;   //!
   TBranch        *b_L2_2j30_anymct175;   //!
   TBranch        *b_L2_2j30_deta3_5;   //!
   TBranch        *b_L2_2j30_j90_dphi03;   //!
   TBranch        *b_L2_2j30_leadingmct100;   //!
   TBranch        *b_L2_2j30_leadingmct150;   //!
   TBranch        *b_L2_2j30_leadingmct175;   //!
   TBranch        *b_L2_2j35_jetNoEF_xe20_noMu;   //!
   TBranch        *b_L2_2j35_jetNoEF_xe30_noMu;   //!
   TBranch        *b_L2_2j35_jetNoEF_xe40_noMu;   //!
   TBranch        *b_L2_2j45;   //!
   TBranch        *b_L2_2j70;   //!
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
   TBranch        *b_L2_2mu4_Upsimumu;   //!
   TBranch        *b_L2_2mu6;   //!
   TBranch        *b_L2_2mu6_MG;   //!
   TBranch        *b_L2_2mu6_NoAlg;   //!
   TBranch        *b_L2_3j15_j45;   //!
   TBranch        *b_L2_3j25;   //!
   TBranch        *b_L2_3j25_2j45;   //!
   TBranch        *b_L2_3j30;   //!
   TBranch        *b_L2_3j45;   //!
   TBranch        *b_L2_4j15_j30;   //!
   TBranch        *b_L2_4j15_j45;   //!
   TBranch        *b_L2_4j25;   //!
   TBranch        *b_L2_4j25_3j30;   //!
   TBranch        *b_L2_4j30;   //!
   TBranch        *b_L2_4j45;   //!
   TBranch        *b_L2_5j25;   //!
   TBranch        *b_L2_6j25;   //!
   TBranch        *b_L2_e10_NoCut;   //!
   TBranch        *b_L2_e10_loose;   //!
   TBranch        *b_L2_e10_loose_mu10;   //!
   TBranch        *b_L2_e10_loose_mu6;   //!
   TBranch        *b_L2_e10_medium;   //!
   TBranch        *b_L2_e10_medium_IDTrkNoCut;   //!
   TBranch        *b_L2_e10_medium_SiTrk;   //!
   TBranch        *b_L2_e10_medium_TRT;   //!
   TBranch        *b_L2_e10_tight;   //!
   TBranch        *b_L2_e15_loose;   //!
   TBranch        *b_L2_e15_loose_IDTrkNoCut;   //!
   TBranch        *b_L2_e15_medium;   //!
   TBranch        *b_L2_e15_medium_SiTrk;   //!
   TBranch        *b_L2_e15_medium_TRT;   //!
   TBranch        *b_L2_e15_tight;   //!
   TBranch        *b_L2_e18_medium;   //!
   TBranch        *b_L2_e20_loose;   //!
   TBranch        *b_L2_e20_loose_IDTrkNoCut;   //!
   TBranch        *b_L2_e20_loose_passEF;   //!
   TBranch        *b_L2_e20_loose_passL2;   //!
   TBranch        *b_L2_e20_loose_xe20_noMu;   //!
   TBranch        *b_L2_e20_loose_xe30_noMu;   //!
   TBranch        *b_L2_e20_medium;   //!
   TBranch        *b_L2_e25_loose;   //!
   TBranch        *b_L2_e30_loose;   //!
   TBranch        *b_L2_e3_loose;   //!
   TBranch        *b_L2_e3_loose_SiTrk;   //!
   TBranch        *b_L2_e3_loose_TRT;   //!
   TBranch        *b_L2_e3_medium;   //!
   TBranch        *b_L2_e3_medium_SiTrk;   //!
   TBranch        *b_L2_e3_medium_TRT;   //!
   TBranch        *b_L2_e5_NoCut_firstempty;   //!
   TBranch        *b_L2_e5_medium;   //!
   TBranch        *b_L2_e5_medium_MV;   //!
   TBranch        *b_L2_e5_medium_SiTrk;   //!
   TBranch        *b_L2_e5_medium_TRT;   //!
   TBranch        *b_L2_e5_medium_mu4;   //!
   TBranch        *b_L2_e5_tight;   //!
   TBranch        *b_L2_e5_tight_SiTrk;   //!
   TBranch        *b_L2_e5_tight_TRT;   //!
   TBranch        *b_L2_e5_tight_e5_NoCut;   //!
   TBranch        *b_L2_eb_physics;   //!
   TBranch        *b_L2_eb_physics_empty;   //!
   TBranch        *b_L2_eb_physics_firstempty;   //!
   TBranch        *b_L2_eb_physics_unpaired_iso;   //!
   TBranch        *b_L2_eb_physics_unpaired_noniso;   //!
   TBranch        *b_L2_eb_random;   //!
   TBranch        *b_L2_eb_random_empty;   //!
   TBranch        *b_L2_eb_random_firstempty;   //!
   TBranch        *b_L2_eb_random_unpaired_iso;   //!
   TBranch        *b_L2_em105_passHLT;   //!
   TBranch        *b_L2_em3_empty_larcalib;   //!
   TBranch        *b_L2_fj10_empty_NoAlg;   //!
   TBranch        *b_L2_fj25;   //!
   TBranch        *b_L2_fj25_larcalib;   //!
   TBranch        *b_L2_fj45;   //!
   TBranch        *b_L2_fj45_larcalib;   //!
   TBranch        *b_L2_fj70;   //!
   TBranch        *b_L2_fj95_jetNoCut_larcalib;   //!
   TBranch        *b_L2_g10_loose;   //!
   TBranch        *b_L2_g11_etcut;   //!
   TBranch        *b_L2_g15_loose;   //!
   TBranch        *b_L2_g17_etcut;   //!
   TBranch        *b_L2_g17_etcut_EFxe20_noMu;   //!
   TBranch        *b_L2_g17_etcut_EFxe30_noMu;   //!
   TBranch        *b_L2_g20_loose;   //!
   TBranch        *b_L2_g20_loose_xe20_noMu;   //!
   TBranch        *b_L2_g20_loose_xe30_noMu;   //!
   TBranch        *b_L2_g20_tight;   //!
   TBranch        *b_L2_g25_loose_xe30_noMu;   //!
   TBranch        *b_L2_g30_loose;   //!
   TBranch        *b_L2_g30_tight;   //!
   TBranch        *b_L2_g3_NoCut_unpaired_iso;   //!
   TBranch        *b_L2_g3_NoCut_unpaired_noniso;   //!
   TBranch        *b_L2_g40_loose;   //!
   TBranch        *b_L2_g40_tight;   //!
   TBranch        *b_L2_g50_loose;   //!
   TBranch        *b_L2_g5_NoCut_cosmic;   //!
   TBranch        *b_L2_g5_loose;   //!
   TBranch        *b_L2_g7_loose;   //!
   TBranch        *b_L2_j115_jetNoCut_larcalib;   //!
   TBranch        *b_L2_j15;   //!
   TBranch        *b_L2_j15_larcalib;   //!
   TBranch        *b_L2_j25;   //!
   TBranch        *b_L2_j25_fj25;   //!
   TBranch        *b_L2_j25_jetNoCut_cosmic;   //!
   TBranch        *b_L2_j25_jetNoCut_firstempty;   //!
   TBranch        *b_L2_j25_jetNoCut_unpaired;   //!
   TBranch        *b_L2_j30;   //!
   TBranch        *b_L2_j30_L1TAU_HV;   //!
   TBranch        *b_L2_j30_Trackless_HV;   //!
   TBranch        *b_L2_j45;   //!
   TBranch        *b_L2_j45_jetNoCut_cosmic;   //!
   TBranch        *b_L2_j45_jetNoCut_firstempty;   //!
   TBranch        *b_L2_j45_jetNoCut_unpaired;   //!
   TBranch        *b_L2_j45_larcalib;   //!
   TBranch        *b_L2_j45_xe12_noMu;   //!
   TBranch        *b_L2_j45_xe20_noMu;   //!
   TBranch        *b_L2_j45_xe30_noMu;   //!
   TBranch        *b_L2_j5_empty_NoAlg;   //!
   TBranch        *b_L2_j5_empty_larcalib;   //!
   TBranch        *b_L2_j5_unpaired_iso_NoAlg;   //!
   TBranch        *b_L2_j5_unpaired_noniso_NoAlg;   //!
   TBranch        *b_L2_j70;   //!
   TBranch        *b_L2_j70_EFxe20_noMu;   //!
   TBranch        *b_L2_j70_EFxe25_noMu;   //!
   TBranch        *b_L2_j70_EFxe30_noMu;   //!
   TBranch        *b_L2_j70_EFxe35_noMu;   //!
   TBranch        *b_L2_j70_EFxe40_noMu;   //!
   TBranch        *b_L2_j90;   //!
   TBranch        *b_L2_j90_larcalib;   //!
   TBranch        *b_L2_je135;   //!
   TBranch        *b_L2_je195;   //!
   TBranch        *b_L2_je255;   //!
   TBranch        *b_L2_je350;   //!
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
   TBranch        *b_L2_mu10_IDTrkNoCut;   //!
   TBranch        *b_L2_mu10_MG;   //!
   TBranch        *b_L2_mu10_MSonly;   //!
   TBranch        *b_L2_mu10_MSonly_tight;   //!
   TBranch        *b_L2_mu10_NoAlg;   //!
   TBranch        *b_L2_mu10_SiTrk;   //!
   TBranch        *b_L2_mu10_tight;   //!
   TBranch        *b_L2_mu10i_loose;   //!
   TBranch        *b_L2_mu13;   //!
   TBranch        *b_L2_mu13_MG;   //!
   TBranch        *b_L2_mu13_MG_tight;   //!
   TBranch        *b_L2_mu13_tight;   //!
   TBranch        *b_L2_mu15;   //!
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
   TBranch        *b_L2_mu4mu6_Upsimumu;   //!
   TBranch        *b_L2_mu6;   //!
   TBranch        *b_L2_mu6_Bmumu;   //!
   TBranch        *b_L2_mu6_BmumuX;   //!
   TBranch        *b_L2_mu6_DiMu;   //!
   TBranch        *b_L2_mu6_IDTrkNoCut;   //!
   TBranch        *b_L2_mu6_Jpsie5e3;   //!
   TBranch        *b_L2_mu6_Jpsie5e3_FS;   //!
   TBranch        *b_L2_mu6_Jpsimumu;   //!
   TBranch        *b_L2_mu6_MG;   //!
   TBranch        *b_L2_mu6_MSonly;   //!
   TBranch        *b_L2_mu6_MSonly_outOfTime;   //!
   TBranch        *b_L2_mu6_NoAlg;   //!
   TBranch        *b_L2_mu6_SiTrk;   //!
   TBranch        *b_L2_mu6_Trk_Jpsi;   //!
   TBranch        *b_L2_mu6_Upsimumu_FS;   //!
   TBranch        *b_L2_mu6_muCombTag;   //!
   TBranch        *b_L2_tau125_loose;   //!
   TBranch        *b_L2_tau125_medium;   //!
   TBranch        *b_L2_tau12_IDTrkNoCut;   //!
   TBranch        *b_L2_tau12_loose;   //!
   TBranch        *b_L2_tau12_loose_2b15;   //!
   TBranch        *b_L2_tau12_loose_3j30;   //!
   TBranch        *b_L2_tau12_loose_EFxe12_noMu;   //!
   TBranch        *b_L2_tau12_loose_IdScan_EFxe12_noMu;   //!
   TBranch        *b_L2_tau12_loose_IdScan_xe15_noMu;   //!
   TBranch        *b_L2_tau12_loose_e10_loose;   //!
   TBranch        *b_L2_tau12_loose_e10_medium;   //!
   TBranch        *b_L2_tau12_loose_e10_tight;   //!
   TBranch        *b_L2_tau12_loose_mu10;   //!
   TBranch        *b_L2_tau12_loose_xe15_noMu;   //!
   TBranch        *b_L2_tau12_loose_xe20_noMu;   //!
   TBranch        *b_L2_tau16_loose;   //!
   TBranch        *b_L2_tau16_loose_2b15;   //!
   TBranch        *b_L2_tau16_loose_3j30;   //!
   TBranch        *b_L2_tau16_loose_e10_loose;   //!
   TBranch        *b_L2_tau16_loose_e15_loose;   //!
   TBranch        *b_L2_tau16_loose_mu10;   //!
   TBranch        *b_L2_tau16_loose_mu15;   //!
   TBranch        *b_L2_tau16_loose_xe20_noMu;   //!
   TBranch        *b_L2_tau16_loose_xe25_noMu;   //!
   TBranch        *b_L2_tau16_loose_xe25_tight_noMu;   //!
   TBranch        *b_L2_tau16_loose_xe30_noMu;   //!
   TBranch        *b_L2_tau16_medium;   //!
   TBranch        *b_L2_tau16_medium_xe22_noMu;   //!
   TBranch        *b_L2_tau16_medium_xe25_noMu;   //!
   TBranch        *b_L2_tau16_medium_xe25_tight_noMu;   //!
   TBranch        *b_L2_tau20_loose;   //!
   TBranch        *b_L2_tau20_loose_xe25_noMu;   //!
   TBranch        *b_L2_tau29_loose;   //!
   TBranch        *b_L2_tau38_loose;   //!
   TBranch        *b_L2_tau38_medium;   //!
   TBranch        *b_L2_tau50_IDTrkNoCut;   //!
   TBranch        *b_L2_tau50_loose;   //!
   TBranch        *b_L2_tau50_loose_IdScan;   //!
   TBranch        *b_L2_tau50_medium;   //!
   TBranch        *b_L2_tau5_empty_larcalib;   //!
   TBranch        *b_L2_tau84_loose;   //!
   TBranch        *b_L2_tau84_medium;   //!
   TBranch        *b_L2_tauNoCut;   //!
   TBranch        *b_L2_tauNoCut_IdScan;   //!
   TBranch        *b_L2_tauNoCut_cosmic;   //!
   TBranch        *b_L2_tauNoCut_firstempty;   //!
   TBranch        *b_L2_tauNoCut_hasTrk6_EFxe15_noMu;   //!
   TBranch        *b_L2_tauNoCut_hasTrk6_IdScan_EFxe15_noMu;   //!
   TBranch        *b_L2_tauNoCut_hasTrk6_IdScan_xe20_noMu;   //!
   TBranch        *b_L2_tauNoCut_hasTrk6_xe20_noMu;   //!
   TBranch        *b_L2_tauNoCut_hasTrk9_xe20_noMu;   //!
   TBranch        *b_L2_tauNoCut_hasTrk_MV;   //!
   TBranch        *b_L2_tauNoCut_hasTrk_e10_tight;   //!
   TBranch        *b_L2_tauNoCut_hasTrk_xe20_noMu;   //!
   TBranch        *b_L2_tauNoCut_unpaired_iso;   //!
   TBranch        *b_L2_tauNoCut_unpaired_noniso;   //!
   TBranch        *b_L2_xe12;   //!
   TBranch        *b_L2_xe12_loose_noMu;   //!
   TBranch        *b_L2_xe12_medium_noMu;   //!
   TBranch        *b_L2_xe12_noMu;   //!
   TBranch        *b_L2_xe15_medium_noMu;   //!
   TBranch        *b_L2_xe15_noMu;   //!
   TBranch        *b_L2_xe15_tight_noMu;   //!
   TBranch        *b_L2_xe15_unbiased_noMu;   //!
   TBranch        *b_L2_xe17_tight_noMu;   //!
   TBranch        *b_L2_xe20_noMu;   //!
   TBranch        *b_L2_xe22_loose_noMu;   //!
   TBranch        *b_L2_xe22_tight_noMu;   //!
   TBranch        *b_L2_xe25_noMu;   //!
   TBranch        *b_L2_xe27_tight_noMu;   //!
   TBranch        *b_L2_xe30_allL1;   //!
   TBranch        *b_L2_xe30_allL1_FEB;   //!
   TBranch        *b_L2_xe30_allL1_allCells;   //!
   TBranch        *b_L2_xe30_noMu;   //!
   TBranch        *b_L2_xe35_noMu;   //!
   TBranch        *b_L2_xe40_medium_noMu;   //!
   TBranch        *b_L2_xe45_noMu;   //!
   TBranch        *b_L2_xe60_medium_noMu;   //!
   TBranch        *b_ph_n;   //!
   TBranch        *b_ph_E;   //!
   TBranch        *b_ph_Et;   //!
   TBranch        *b_ph_pt;   //!
   TBranch        *b_ph_m;   //!
   TBranch        *b_ph_eta;   //!
   TBranch        *b_ph_phi;   //!
   TBranch        *b_ph_px;   //!
   TBranch        *b_ph_py;   //!
   TBranch        *b_ph_pz;   //!
   TBranch        *b_ph_author;   //!
   TBranch        *b_ph_isRecovered;   //!
   TBranch        *b_ph_isEM;   //!
   TBranch        *b_ph_convFlag;   //!
   TBranch        *b_ph_isConv;   //!
   TBranch        *b_ph_nConv;   //!
   TBranch        *b_ph_nSingleTrackConv;   //!
   TBranch        *b_ph_nDoubleTrackConv;   //!
   TBranch        *b_ph_loose;   //!
   TBranch        *b_ph_tight;   //!
   TBranch        *b_ph_tightIso;   //!
   TBranch        *b_ph_Ethad;   //!
   TBranch        *b_ph_Ethad1;   //!
   TBranch        *b_ph_E033;   //!
   TBranch        *b_ph_f1;   //!
   TBranch        *b_ph_f1core;   //!
   TBranch        *b_ph_Emins1;   //!
   TBranch        *b_ph_fside;   //!
   TBranch        *b_ph_Emax2;   //!
   TBranch        *b_ph_ws3;   //!
   TBranch        *b_ph_wstot;   //!
   TBranch        *b_ph_E132;   //!
   TBranch        *b_ph_E1152;   //!
   TBranch        *b_ph_emaxs1;   //!
   TBranch        *b_ph_deltaEs;   //!
   TBranch        *b_ph_E233;   //!
   TBranch        *b_ph_E237;   //!
   TBranch        *b_ph_E277;   //!
   TBranch        *b_ph_weta2;   //!
   TBranch        *b_ph_f3;   //!
   TBranch        *b_ph_f3core;   //!
   TBranch        *b_ph_rphiallcalo;   //!
   TBranch        *b_ph_Etcone45;   //!
   TBranch        *b_ph_Etcone20;   //!
   TBranch        *b_ph_Etcone30;   //!
   TBranch        *b_ph_Etcone40;   //!
   TBranch        *b_ph_ptcone30;   //!
   TBranch        *b_ph_convanglematch;   //!
   TBranch        *b_ph_convtrackmatch;   //!
   TBranch        *b_ph_hasconv;   //!
   TBranch        *b_ph_convvtxx;   //!
   TBranch        *b_ph_convvtxy;   //!
   TBranch        *b_ph_convvtxz;   //!
   TBranch        *b_ph_Rconv;   //!
   TBranch        *b_ph_zconv;   //!
   TBranch        *b_ph_convvtxchi2;   //!
   TBranch        *b_ph_pt1conv;   //!
   TBranch        *b_ph_convtrk1nBLHits;   //!
   TBranch        *b_ph_convtrk1nPixHits;   //!
   TBranch        *b_ph_convtrk1nSCTHits;   //!
   TBranch        *b_ph_convtrk1nTRTHits;   //!
   TBranch        *b_ph_pt2conv;   //!
   TBranch        *b_ph_convtrk2nBLHits;   //!
   TBranch        *b_ph_convtrk2nPixHits;   //!
   TBranch        *b_ph_convtrk2nSCTHits;   //!
   TBranch        *b_ph_convtrk2nTRTHits;   //!
   TBranch        *b_ph_ptconv;   //!
   TBranch        *b_ph_pzconv;   //!
   TBranch        *b_ph_reta;   //!
   TBranch        *b_ph_rphi;   //!
   TBranch        *b_ph_EtringnoisedR03sig2;   //!
   TBranch        *b_ph_EtringnoisedR03sig3;   //!
   TBranch        *b_ph_EtringnoisedR03sig4;   //!
   TBranch        *b_ph_isolationlikelihoodjets;   //!
   TBranch        *b_ph_isolationlikelihoodhqelectrons;   //!
   TBranch        *b_ph_loglikelihood;   //!
   TBranch        *b_ph_photonweight;   //!
   TBranch        *b_ph_photonbgweight;   //!
   TBranch        *b_ph_neuralnet;   //!
   TBranch        *b_ph_Hmatrix;   //!
   TBranch        *b_ph_Hmatrix5;   //!
   TBranch        *b_ph_adaboost;   //!
   TBranch        *b_ph_zvertex;   //!
   TBranch        *b_ph_errz;   //!
   TBranch        *b_ph_etap;   //!
   TBranch        *b_ph_depth;   //!
   TBranch        *b_ph_cl_E;   //!
   TBranch        *b_ph_cl_pt;   //!
   TBranch        *b_ph_cl_eta;   //!
   TBranch        *b_ph_cl_phi;   //!
   TBranch        *b_ph_Es0;   //!
   TBranch        *b_ph_etas0;   //!
   TBranch        *b_ph_phis0;   //!
   TBranch        *b_ph_Es1;   //!
   TBranch        *b_ph_etas1;   //!
   TBranch        *b_ph_phis1;   //!
   TBranch        *b_ph_Es2;   //!
   TBranch        *b_ph_etas2;   //!
   TBranch        *b_ph_phis2;   //!
   TBranch        *b_ph_Es3;   //!
   TBranch        *b_ph_etas3;   //!
   TBranch        *b_ph_phis3;   //!
   TBranch        *b_ph_rawcl_Es0;   //!
   TBranch        *b_ph_rawcl_etas0;   //!
   TBranch        *b_ph_rawcl_phis0;   //!
   TBranch        *b_ph_rawcl_Es1;   //!
   TBranch        *b_ph_rawcl_etas1;   //!
   TBranch        *b_ph_rawcl_phis1;   //!
   TBranch        *b_ph_rawcl_Es2;   //!
   TBranch        *b_ph_rawcl_etas2;   //!
   TBranch        *b_ph_rawcl_phis2;   //!
   TBranch        *b_ph_rawcl_Es3;   //!
   TBranch        *b_ph_rawcl_etas3;   //!
   TBranch        *b_ph_rawcl_phis3;   //!
   TBranch        *b_ph_rawcl_E;   //!
   TBranch        *b_ph_rawcl_pt;   //!
   TBranch        *b_ph_rawcl_eta;   //!
   TBranch        *b_ph_rawcl_phi;   //!
   TBranch        *b_ph_deltaEmax2;   //!
   TBranch        *b_ph_isIso;   //!
   TBranch        *b_ph_topoEtcone20;   //!
   TBranch        *b_ph_topoEtcone40;   //!
   TBranch        *b_ph_topoEtcone60;   //!
   TBranch        *b_ph_jet_dr;   //!
   TBranch        *b_ph_jet_E;   //!
   TBranch        *b_ph_jet_pt;   //!
   TBranch        *b_ph_jet_m;   //!
   TBranch        *b_ph_jet_eta;   //!
   TBranch        *b_ph_jet_phi;   //!
   TBranch        *b_ph_jet_matched;   //!
   TBranch        *b_ph_trackIsol;   //!
   TBranch        *b_ph_convIP;   //!
   TBranch        *b_ph_convIPRev;   //!
   TBranch        *b_ph_ptIsolationCone;   //!
   TBranch        *b_ph_ptIsolationConePhAngle;   //!
   TBranch        *b_ph_Etcone40_pt_corrected;   //!
   TBranch        *b_ph_Etcone40_ED_corrected;   //!
   TBranch        *b_ph_Etcone40_corrected;   //!
   TBranch        *b_ph_topodr;   //!
   TBranch        *b_ph_topopt;   //!
   TBranch        *b_ph_topoeta;   //!
   TBranch        *b_ph_topophi;   //!
   TBranch        *b_ph_topomatched;   //!
   TBranch        *b_ph_topoEMdr;   //!
   TBranch        *b_ph_topoEMpt;   //!
   TBranch        *b_ph_topoEMeta;   //!
   TBranch        *b_ph_topoEMphi;   //!
   TBranch        *b_ph_topoEMmatched;   //!
   TBranch        *b_ph_EF_dr;   //!
   TBranch        *b_ph_EF_index;   //!
   TBranch        *b_ph_L2_dr;   //!
   TBranch        *b_ph_L2_index;   //!
   TBranch        *b_ph_L1_dr;   //!
   TBranch        *b_ph_L1_index;   //!
   TBranch        *b_ph_EF_E;   //!
   TBranch        *b_ph_EF_Et;   //!
   TBranch        *b_ph_EF_pt;   //!
   TBranch        *b_ph_EF_eta;   //!
   TBranch        *b_ph_EF_phi;   //!
   TBranch        *b_ph_EF_Ethad;   //!
   TBranch        *b_ph_EF_Ethad1;   //!
   TBranch        *b_ph_EF_f1;   //!
   TBranch        *b_ph_EF_Emins1;   //!
   TBranch        *b_ph_EF_fside;   //!
   TBranch        *b_ph_EF_Emax2;   //!
   TBranch        *b_ph_EF_ws3;   //!
   TBranch        *b_ph_EF_wstot;   //!
   TBranch        *b_ph_EF_E233;   //!
   TBranch        *b_ph_EF_E237;   //!
   TBranch        *b_ph_EF_E277;   //!
   TBranch        *b_ph_EF_weta2;   //!
   TBranch        *b_ph_EF_rphiallcalo;   //!
   TBranch        *b_ph_EF_Etcone45;   //!
   TBranch        *b_ph_EF_Etcone20;   //!
   TBranch        *b_ph_EF_Etcone30;   //!
   TBranch        *b_ph_EF_Etcone40;   //!
   TBranch        *b_ph_EF_zvertex;   //!
   TBranch        *b_ph_EF_errz;   //!
   TBranch        *b_ph_EF_matched;   //!
   TBranch        *b_ph_L2_E;   //!
   TBranch        *b_ph_L2_Et;   //!
   TBranch        *b_ph_L2_pt;   //!
   TBranch        *b_ph_L2_eta;   //!
   TBranch        *b_ph_L2_phi;   //!
   TBranch        *b_ph_L2_Ethad1;   //!
   TBranch        *b_ph_L2_reta;   //!
   TBranch        *b_ph_L2_Eratio;   //!
   TBranch        *b_ph_L2_E237;   //!
   TBranch        *b_ph_L2_E277;   //!
   TBranch        *b_ph_L2_fside;   //!
   TBranch        *b_ph_L2_weta2;   //!
   TBranch        *b_ph_L2_Emaxs1;   //!
   TBranch        *b_ph_L2_Emax2;   //!
   TBranch        *b_ph_L2_matched;   //!
   TBranch        *b_ph_L1_eta;   //!
   TBranch        *b_ph_L1_phi;   //!
   TBranch        *b_ph_L1_EMisol;   //!
   TBranch        *b_ph_L1_hadisol;   //!
   TBranch        *b_ph_L1_hadcore;   //!
   TBranch        *b_ph_L1_pt;   //!
   TBranch        *b_ph_L1_Et;   //!
   TBranch        *b_ph_L1_matched;   //!
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
   TBranch        *b_mu_muid_loose;   //!
   TBranch        *b_mu_muid_medium;   //!
   TBranch        *b_mu_muid_tight;   //!
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
   TBranch        *b_mu_staco_loose;   //!
   TBranch        *b_mu_staco_medium;   //!
   TBranch        *b_mu_staco_tight;   //!
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
   TBranch        *b_tau_n;   //!
   TBranch        *b_tau_Et;   //!
   TBranch        *b_tau_pt;   //!
   TBranch        *b_tau_m;   //!
   TBranch        *b_tau_eta;   //!
   TBranch        *b_tau_phi;   //!
   TBranch        *b_tau_charge;   //!
   TBranch        *b_tau_BDTEleScore;   //!
   TBranch        *b_tau_BDTJetScore;   //!
   TBranch        *b_tau_discCut;   //!
   TBranch        *b_tau_discCutTMVA;   //!
   TBranch        *b_tau_discLL;   //!
   TBranch        *b_tau_discNN;   //!
   TBranch        *b_tau_efficLL;   //!
   TBranch        *b_tau_efficNN;   //!
   TBranch        *b_tau_likelihood;   //!
   TBranch        *b_tau_tauJetNeuralNetwork;   //!
   TBranch        *b_tau_tauENeuralNetwork;   //!
   TBranch        *b_tau_tauElTauLikelihood;   //!
   TBranch        *b_tau_electronVetoLoose;   //!
   TBranch        *b_tau_electronVetoMedium;   //!
   TBranch        *b_tau_electronVetoTight;   //!
   TBranch        *b_tau_muonVeto;   //!
   TBranch        *b_tau_tauCutLoose;   //!
   TBranch        *b_tau_tauCutMedium;   //!
   TBranch        *b_tau_tauCutTight;   //!
   TBranch        *b_tau_tauCutSafeLoose;   //!
   TBranch        *b_tau_tauCutSafeMedium;   //!
   TBranch        *b_tau_tauCutSafeTight;   //!
   TBranch        *b_tau_tauCutSafeCaloLoose;   //!
   TBranch        *b_tau_tauCutSafeCaloMedium;   //!
   TBranch        *b_tau_tauCutSafeCaloTight;   //!
   TBranch        *b_tau_tauLlhLoose;   //!
   TBranch        *b_tau_tauLlhMedium;   //!
   TBranch        *b_tau_tauLlhTight;   //!
   TBranch        *b_tau_author;   //!
   TBranch        *b_tau_ROIword;   //!
   TBranch        *b_tau_nProng;   //!
   TBranch        *b_tau_numTrack;   //!
   TBranch        *b_tau_etOverPtLeadTrk;   //!
   TBranch        *b_tau_ipZ0SinThetaSigLeadTrk;   //!
   TBranch        *b_tau_leadTrkPt;   //!
   TBranch        *b_tau_nLooseTrk;   //!
   TBranch        *b_tau_nLooseConvTrk;   //!
   TBranch        *b_tau_nProngLoose;   //!
   TBranch        *b_tau_ipSigLeadTrk;   //!
   TBranch        *b_tau_ipSigLeadLooseTrk;   //!
   TBranch        *b_tau_etOverPtLeadLooseTrk;   //!
   TBranch        *b_tau_leadLooseTrkPt;   //!
   TBranch        *b_tau_chrgLooseTrk;   //!
   TBranch        *b_tau_massTrkSys;   //!
   TBranch        *b_tau_trkWidth2;   //!
   TBranch        *b_tau_trFlightPathSig;   //!
   TBranch        *b_tau_etEflow;   //!
   TBranch        *b_tau_mEflow;   //!
   TBranch        *b_tau_nPi0;   //!
   TBranch        *b_tau_ele_E237E277;   //!
   TBranch        *b_tau_ele_PresamplerFraction;   //!
   TBranch        *b_tau_ele_ECALFirstFraction;   //!
   TBranch        *b_tau_seedCalo_EMRadius;   //!
   TBranch        *b_tau_seedCalo_hadRadius;   //!
   TBranch        *b_tau_seedCalo_etEMAtEMScale;   //!
   TBranch        *b_tau_seedCalo_etHadAtEMScale;   //!
   TBranch        *b_tau_seedCalo_isolFrac;   //!
   TBranch        *b_tau_seedCalo_centFrac;   //!
   TBranch        *b_tau_seedCalo_stripWidth2;   //!
   TBranch        *b_tau_seedCalo_nStrip;   //!
   TBranch        *b_tau_seedCalo_etEMCalib;   //!
   TBranch        *b_tau_seedCalo_etHadCalib;   //!
   TBranch        *b_tau_seedCalo_eta;   //!
   TBranch        *b_tau_seedCalo_phi;   //!
   TBranch        *b_tau_seedCalo_nIsolLooseTrk;   //!
   TBranch        *b_tau_seedCalo_trkAvgDist;   //!
   TBranch        *b_tau_seedCalo_trkRmsDist;   //!
   TBranch        *b_tau_seedTrk_EMRadius;   //!
   TBranch        *b_tau_seedTrk_isolFrac;   //!
   TBranch        *b_tau_seedTrk_etChrgHadOverSumTrkPt;   //!
   TBranch        *b_tau_seedTrk_isolFracWide;   //!
   TBranch        *b_tau_seedTrk_etHadAtEMScale;   //!
   TBranch        *b_tau_seedTrk_etEMAtEMScale;   //!
   TBranch        *b_tau_seedTrk_etEMCL;   //!
   TBranch        *b_tau_seedTrk_etChrgEM;   //!
   TBranch        *b_tau_seedTrk_etNeuEM;   //!
   TBranch        *b_tau_seedTrk_etResNeuEM;   //!
   TBranch        *b_tau_seedTrk_hadLeakEt;   //!
   TBranch        *b_tau_seedTrk_sumEMCellEtOverLeadTrkPt;   //!
   TBranch        *b_tau_seedTrk_secMaxStripEt;   //!
   TBranch        *b_tau_seedTrk_stripWidth2;   //!
   TBranch        *b_tau_seedTrk_nStrip;   //!
   TBranch        *b_tau_seedTrk_etChrgHad;   //!
   TBranch        *b_tau_seedTrk_nOtherCoreTrk;   //!
   TBranch        *b_tau_seedTrk_nIsolTrk;   //!
   TBranch        *b_tau_seedTrk_etIsolEM;   //!
   TBranch        *b_tau_seedTrk_etIsolHad;   //!
   TBranch        *b_tau_calcVars_sumTrkPt;   //!
   TBranch        *b_tau_calcVars_numTopoClusters;   //!
   TBranch        *b_tau_calcVars_numEffTopoClusters;   //!
   TBranch        *b_tau_calcVars_topoInvMass;   //!
   TBranch        *b_tau_calcVars_effTopoInvMass;   //!
   TBranch        *b_tau_calcVars_topoMeanDeltaR;   //!
   TBranch        *b_tau_calcVars_effTopoMeanDeltaR;   //!
   TBranch        *b_tau_calcVars_etHadSumPtTracks;   //!
   TBranch        *b_tau_calcVars_etEMSumPtTracks;   //!
   TBranch        *b_tau_track_n;   //!
   TBranch        *b_tau_EF_dr;   //!
   TBranch        *b_tau_EF_E;   //!
   TBranch        *b_tau_EF_Et;   //!
   TBranch        *b_tau_EF_pt;   //!
   TBranch        *b_tau_EF_eta;   //!
   TBranch        *b_tau_EF_phi;   //!
   TBranch        *b_tau_EF_matched;   //!
   TBranch        *b_tau_L2_dr;   //!
   TBranch        *b_tau_L2_E;   //!
   TBranch        *b_tau_L2_Et;   //!
   TBranch        *b_tau_L2_pt;   //!
   TBranch        *b_tau_L2_eta;   //!
   TBranch        *b_tau_L2_phi;   //!
   TBranch        *b_tau_L2_matched;   //!
   TBranch        *b_tau_L1_dr;   //!
   TBranch        *b_tau_L1_Et;   //!
   TBranch        *b_tau_L1_pt;   //!
   TBranch        *b_tau_L1_eta;   //!
   TBranch        *b_tau_L1_phi;   //!
   TBranch        *b_tau_L1_matched;   //!
   TBranch        *b_jet_antikt4h1topo_n;   //!
   TBranch        *b_jet_antikt4h1topo_E;   //!
   TBranch        *b_jet_antikt4h1topo_pt;   //!
   TBranch        *b_jet_antikt4h1topo_m;   //!
   TBranch        *b_jet_antikt4h1topo_eta;   //!
   TBranch        *b_jet_antikt4h1topo_phi;   //!
   TBranch        *b_jet_antikt4h1topo_EtaPhys;   //!
   TBranch        *b_jet_antikt4h1topo_PhiPhys;   //!
   TBranch        *b_jet_antikt4h1topo_MPhys;   //!
   TBranch        *b_jet_antikt4h1topo_WIDTH;   //!
   TBranch        *b_jet_antikt4h1topo_n90;   //!
   TBranch        *b_jet_antikt4h1topo_n90constituents;   //!
   TBranch        *b_jet_antikt4h1topo_fracSamplingMax;   //!
   TBranch        *b_jet_antikt4h1topo_SamplingMax;   //!
   TBranch        *b_jet_antikt4h1topo_BCH_CORR_CELL;   //!
   TBranch        *b_jet_antikt4h1topo_BCH_CORR_DOTX;   //!
   TBranch        *b_jet_antikt4h1topo_BCH_CORR_JET;   //!
   TBranch        *b_jet_antikt4h1topo_BCH_CORR_JET_FORCELL;   //!
   TBranch        *b_jet_antikt4h1topo_ENG_BAD_CELLS;   //!
   TBranch        *b_jet_antikt4h1topo_N_BAD_CELLS;   //!
   TBranch        *b_jet_antikt4h1topo_N_BAD_CELLS_CORR;   //!
   TBranch        *b_jet_antikt4h1topo_BAD_CELLS_CORR_E;   //!
   TBranch        *b_jet_antikt4h1topo_hecf;   //!
   TBranch        *b_jet_antikt4h1topo_tgap3f;   //!
   TBranch        *b_jet_antikt4h1topo_isGood;   //!
   TBranch        *b_jet_antikt4h1topo_timing;   //!
   TBranch        *b_jet_antikt4h1topo_quality;   //!
   TBranch        *b_jet_antikt4h1topo_emfrac;   //!
   TBranch        *b_jet_antikt4h1topo_GCWJES;   //!
   TBranch        *b_jet_antikt4h1topo_EMJES;   //!
   TBranch        *b_jet_antikt4h1topo_CB;   //!
   TBranch        *b_jet_antikt4h1topo_emscale_E;   //!
   TBranch        *b_jet_antikt4h1topo_emscale_pt;   //!
   TBranch        *b_jet_antikt4h1topo_emscale_m;   //!
   TBranch        *b_jet_antikt4h1topo_emscale_eta;   //!
   TBranch        *b_jet_antikt4h1topo_emscale_phi;   //!
   TBranch        *b_jet_antikt4h1topo_jvtxf;   //!
   TBranch        *b_jet_antikt4h1topo_jvtx_x;   //!
   TBranch        *b_jet_antikt4h1topo_jvtx_y;   //!
   TBranch        *b_jet_antikt4h1topo_jvtx_z;   //!
   TBranch        *b_jet_antikt4h1topo_flavor_weight;   //!
   TBranch        *b_jet_antikt4h1topo_flavor_weight_TrackCounting2D;   //!
   TBranch        *b_jet_antikt4h1topo_flavor_weight_JetProb;   //!
   TBranch        *b_jet_antikt4h1topo_flavor_weight_IP1D;   //!
   TBranch        *b_jet_antikt4h1topo_flavor_weight_IP2D;   //!
   TBranch        *b_jet_antikt4h1topo_flavor_weight_IP3D;   //!
   TBranch        *b_jet_antikt4h1topo_flavor_weight_SV0;   //!
   TBranch        *b_jet_antikt4h1topo_flavor_weight_SV1;   //!
   TBranch        *b_jet_antikt4h1topo_flavor_weight_SV2;   //!
   TBranch        *b_jet_antikt4h1topo_flavor_weight_JetFitterTag;   //!
   TBranch        *b_jet_antikt4h1topo_flavor_weight_JetFitterCOMB;   //!
   TBranch        *b_jet_antikt4h1topo_flavor_weight_JetFitterTagNN;   //!
   TBranch        *b_jet_antikt4h1topo_flavor_weight_JetFitterCOMBNN;   //!
   TBranch        *b_jet_antikt4h1topo_flavor_weight_SoftMuonTag;   //!
   TBranch        *b_jet_antikt4h1topo_flavor_weight_SoftElectronTag;   //!
   TBranch        *b_jet_antikt4h1topo_e_PreSamplerB;   //!
   TBranch        *b_jet_antikt4h1topo_e_EMB1;   //!
   TBranch        *b_jet_antikt4h1topo_e_EMB2;   //!
   TBranch        *b_jet_antikt4h1topo_e_EMB3;   //!
   TBranch        *b_jet_antikt4h1topo_e_PreSamplerE;   //!
   TBranch        *b_jet_antikt4h1topo_e_EME1;   //!
   TBranch        *b_jet_antikt4h1topo_e_EME2;   //!
   TBranch        *b_jet_antikt4h1topo_e_EME3;   //!
   TBranch        *b_jet_antikt4h1topo_e_HEC0;   //!
   TBranch        *b_jet_antikt4h1topo_e_HEC1;   //!
   TBranch        *b_jet_antikt4h1topo_e_HEC2;   //!
   TBranch        *b_jet_antikt4h1topo_e_HEC3;   //!
   TBranch        *b_jet_antikt4h1topo_e_TileBar0;   //!
   TBranch        *b_jet_antikt4h1topo_e_TileBar1;   //!
   TBranch        *b_jet_antikt4h1topo_e_TileBar2;   //!
   TBranch        *b_jet_antikt4h1topo_e_TileGap1;   //!
   TBranch        *b_jet_antikt4h1topo_e_TileGap2;   //!
   TBranch        *b_jet_antikt4h1topo_e_TileGap3;   //!
   TBranch        *b_jet_antikt4h1topo_e_TileExt0;   //!
   TBranch        *b_jet_antikt4h1topo_e_TileExt1;   //!
   TBranch        *b_jet_antikt4h1topo_e_TileExt2;   //!
   TBranch        *b_jet_antikt4h1topo_e_FCAL0;   //!
   TBranch        *b_jet_antikt4h1topo_e_FCAL1;   //!
   TBranch        *b_jet_antikt4h1topo_e_FCAL2;   //!
   TBranch        *b_jet_antikt4h1topo_shapeBins;   //!
   TBranch        *b_jet_antikt4h1topo_flavor_component_ip2d_pu;   //!
   TBranch        *b_jet_antikt4h1topo_flavor_component_ip2d_pb;   //!
   TBranch        *b_jet_antikt4h1topo_flavor_component_ip2d_ntrk;   //!
   TBranch        *b_jet_antikt4h1topo_flavor_component_ip3d_pu;   //!
   TBranch        *b_jet_antikt4h1topo_flavor_component_ip3d_pb;   //!
   TBranch        *b_jet_antikt4h1topo_flavor_component_ip3d_ntrk;   //!
   TBranch        *b_jet_antikt4h1topo_flavor_component_sv1_pu;   //!
   TBranch        *b_jet_antikt4h1topo_flavor_component_sv1_pb;   //!
   TBranch        *b_jet_antikt4h1topo_flavor_component_sv2_pu;   //!
   TBranch        *b_jet_antikt4h1topo_flavor_component_sv2_pb;   //!
   TBranch        *b_jet_antikt4h1topo_flavor_component_svp_mass;   //!
   TBranch        *b_jet_antikt4h1topo_flavor_component_svp_n2t;   //!
   TBranch        *b_jet_antikt4h1topo_flavor_component_svp_svok;   //!
   TBranch        *b_jet_antikt4h1topo_flavor_component_svp_ntrk;   //!
   TBranch        *b_jet_antikt4h1topo_flavor_component_svp_ntrkv;   //!
   TBranch        *b_jet_antikt4h1topo_flavor_component_svp_ntrkj;   //!
   TBranch        *b_jet_antikt4h1topo_flavor_component_svp_efrc;   //!
   TBranch        *b_jet_antikt4h1topo_flavor_component_sv0p_mass;   //!
   TBranch        *b_jet_antikt4h1topo_flavor_component_sv0p_n2t;   //!
   TBranch        *b_jet_antikt4h1topo_flavor_component_sv0p_svok;   //!
   TBranch        *b_jet_antikt4h1topo_flavor_component_sv0p_ntrk;   //!
   TBranch        *b_jet_antikt4h1topo_flavor_component_sv0p_ntrkv;   //!
   TBranch        *b_jet_antikt4h1topo_flavor_component_sv0p_ntrkj;   //!
   TBranch        *b_jet_antikt4h1topo_flavor_component_sv0p_efrc;   //!
   TBranch        *b_jet_antikt4h1topo_flavor_component_jfit_pu;   //!
   TBranch        *b_jet_antikt4h1topo_flavor_component_jfit_pb;   //!
   TBranch        *b_jet_antikt4h1topo_flavor_component_jfit_nvtxnt;   //!
   TBranch        *b_jet_antikt4h1topo_flavor_component_jfit_nvtx1t;   //!
   TBranch        *b_jet_antikt4h1topo_flavor_component_jfit_ntrk;   //!
   TBranch        *b_jet_antikt4h1topo_flavor_component_jfit_efrc;   //!
   TBranch        *b_jet_antikt4h1topo_flavor_component_jfit_mass;   //!
   TBranch        *b_jet_antikt4h1topo_flavor_component_jfit_sig3d;   //!
   TBranch        *b_jet_antikt4h1topo_constscale_E;   //!
   TBranch        *b_jet_antikt4h1topo_constscale_pt;   //!
   TBranch        *b_jet_antikt4h1topo_constscale_m;   //!
   TBranch        *b_jet_antikt4h1topo_constscale_eta;   //!
   TBranch        *b_jet_antikt4h1topo_constscale_phi;   //!
   TBranch        *b_jet_antikt4h1topo_el_dr;   //!
   TBranch        *b_jet_antikt4h1topo_el_matched;   //!
   TBranch        *b_jet_antikt4h1topo_mu_dr;   //!
   TBranch        *b_jet_antikt4h1topo_mu_matched;   //!
   TBranch        *b_jet_antikt4h1tower_n;   //!
   TBranch        *b_jet_antikt4h1tower_E;   //!
   TBranch        *b_jet_antikt4h1tower_pt;   //!
   TBranch        *b_jet_antikt4h1tower_m;   //!
   TBranch        *b_jet_antikt4h1tower_eta;   //!
   TBranch        *b_jet_antikt4h1tower_phi;   //!
   TBranch        *b_jet_antikt4h1tower_EtaPhys;   //!
   TBranch        *b_jet_antikt4h1tower_PhiPhys;   //!
   TBranch        *b_jet_antikt4h1tower_MPhys;   //!
   TBranch        *b_jet_antikt4h1tower_WIDTH;   //!
   TBranch        *b_jet_antikt4h1tower_n90;   //!
   TBranch        *b_jet_antikt4h1tower_n90constituents;   //!
   TBranch        *b_jet_antikt4h1tower_fracSamplingMax;   //!
   TBranch        *b_jet_antikt4h1tower_SamplingMax;   //!
   TBranch        *b_jet_antikt4h1tower_BCH_CORR_CELL;   //!
   TBranch        *b_jet_antikt4h1tower_BCH_CORR_DOTX;   //!
   TBranch        *b_jet_antikt4h1tower_BCH_CORR_JET;   //!
   TBranch        *b_jet_antikt4h1tower_BCH_CORR_JET_FORCELL;   //!
   TBranch        *b_jet_antikt4h1tower_ENG_BAD_CELLS;   //!
   TBranch        *b_jet_antikt4h1tower_N_BAD_CELLS;   //!
   TBranch        *b_jet_antikt4h1tower_N_BAD_CELLS_CORR;   //!
   TBranch        *b_jet_antikt4h1tower_BAD_CELLS_CORR_E;   //!
   TBranch        *b_jet_antikt4h1tower_hecf;   //!
   TBranch        *b_jet_antikt4h1tower_tgap3f;   //!
   TBranch        *b_jet_antikt4h1tower_isGood;   //!
   TBranch        *b_jet_antikt4h1tower_timing;   //!
   TBranch        *b_jet_antikt4h1tower_quality;   //!
   TBranch        *b_jet_antikt4h1tower_emfrac;   //!
   TBranch        *b_jet_antikt4h1tower_GCWJES;   //!
   TBranch        *b_jet_antikt4h1tower_EMJES;   //!
   TBranch        *b_jet_antikt4h1tower_CB;   //!
   TBranch        *b_jet_antikt4h1tower_emscale_E;   //!
   TBranch        *b_jet_antikt4h1tower_emscale_pt;   //!
   TBranch        *b_jet_antikt4h1tower_emscale_m;   //!
   TBranch        *b_jet_antikt4h1tower_emscale_eta;   //!
   TBranch        *b_jet_antikt4h1tower_emscale_phi;   //!
   TBranch        *b_jet_antikt4h1tower_jvtxf;   //!
   TBranch        *b_jet_antikt4h1tower_jvtx_x;   //!
   TBranch        *b_jet_antikt4h1tower_jvtx_y;   //!
   TBranch        *b_jet_antikt4h1tower_jvtx_z;   //!
   TBranch        *b_jet_antikt4h1tower_flavor_weight;   //!
   TBranch        *b_jet_antikt4h1tower_flavor_weight_TrackCounting2D;   //!
   TBranch        *b_jet_antikt4h1tower_flavor_weight_JetProb;   //!
   TBranch        *b_jet_antikt4h1tower_flavor_weight_IP1D;   //!
   TBranch        *b_jet_antikt4h1tower_flavor_weight_IP2D;   //!
   TBranch        *b_jet_antikt4h1tower_flavor_weight_IP3D;   //!
   TBranch        *b_jet_antikt4h1tower_flavor_weight_SV0;   //!
   TBranch        *b_jet_antikt4h1tower_flavor_weight_SV1;   //!
   TBranch        *b_jet_antikt4h1tower_flavor_weight_SV2;   //!
   TBranch        *b_jet_antikt4h1tower_flavor_weight_JetFitterTag;   //!
   TBranch        *b_jet_antikt4h1tower_flavor_weight_JetFitterCOMB;   //!
   TBranch        *b_jet_antikt4h1tower_flavor_weight_JetFitterTagNN;   //!
   TBranch        *b_jet_antikt4h1tower_flavor_weight_JetFitterCOMBNN;   //!
   TBranch        *b_jet_antikt4h1tower_flavor_weight_SoftMuonTag;   //!
   TBranch        *b_jet_antikt4h1tower_flavor_weight_SoftElectronTag;   //!
   TBranch        *b_jet_antikt4h1tower_e_PreSamplerB;   //!
   TBranch        *b_jet_antikt4h1tower_e_EMB1;   //!
   TBranch        *b_jet_antikt4h1tower_e_EMB2;   //!
   TBranch        *b_jet_antikt4h1tower_e_EMB3;   //!
   TBranch        *b_jet_antikt4h1tower_e_PreSamplerE;   //!
   TBranch        *b_jet_antikt4h1tower_e_EME1;   //!
   TBranch        *b_jet_antikt4h1tower_e_EME2;   //!
   TBranch        *b_jet_antikt4h1tower_e_EME3;   //!
   TBranch        *b_jet_antikt4h1tower_e_HEC0;   //!
   TBranch        *b_jet_antikt4h1tower_e_HEC1;   //!
   TBranch        *b_jet_antikt4h1tower_e_HEC2;   //!
   TBranch        *b_jet_antikt4h1tower_e_HEC3;   //!
   TBranch        *b_jet_antikt4h1tower_e_TileBar0;   //!
   TBranch        *b_jet_antikt4h1tower_e_TileBar1;   //!
   TBranch        *b_jet_antikt4h1tower_e_TileBar2;   //!
   TBranch        *b_jet_antikt4h1tower_e_TileGap1;   //!
   TBranch        *b_jet_antikt4h1tower_e_TileGap2;   //!
   TBranch        *b_jet_antikt4h1tower_e_TileGap3;   //!
   TBranch        *b_jet_antikt4h1tower_e_TileExt0;   //!
   TBranch        *b_jet_antikt4h1tower_e_TileExt1;   //!
   TBranch        *b_jet_antikt4h1tower_e_TileExt2;   //!
   TBranch        *b_jet_antikt4h1tower_e_FCAL0;   //!
   TBranch        *b_jet_antikt4h1tower_e_FCAL1;   //!
   TBranch        *b_jet_antikt4h1tower_e_FCAL2;   //!
   TBranch        *b_jet_antikt4h1tower_shapeBins;   //!
   TBranch        *b_jet_antikt4h1tower_flavor_component_ip2d_pu;   //!
   TBranch        *b_jet_antikt4h1tower_flavor_component_ip2d_pb;   //!
   TBranch        *b_jet_antikt4h1tower_flavor_component_ip2d_ntrk;   //!
   TBranch        *b_jet_antikt4h1tower_flavor_component_ip3d_pu;   //!
   TBranch        *b_jet_antikt4h1tower_flavor_component_ip3d_pb;   //!
   TBranch        *b_jet_antikt4h1tower_flavor_component_ip3d_ntrk;   //!
   TBranch        *b_jet_antikt4h1tower_flavor_component_sv1_pu;   //!
   TBranch        *b_jet_antikt4h1tower_flavor_component_sv1_pb;   //!
   TBranch        *b_jet_antikt4h1tower_flavor_component_sv2_pu;   //!
   TBranch        *b_jet_antikt4h1tower_flavor_component_sv2_pb;   //!
   TBranch        *b_jet_antikt4h1tower_flavor_component_svp_mass;   //!
   TBranch        *b_jet_antikt4h1tower_flavor_component_svp_n2t;   //!
   TBranch        *b_jet_antikt4h1tower_flavor_component_svp_svok;   //!
   TBranch        *b_jet_antikt4h1tower_flavor_component_svp_ntrk;   //!
   TBranch        *b_jet_antikt4h1tower_flavor_component_svp_ntrkv;   //!
   TBranch        *b_jet_antikt4h1tower_flavor_component_svp_ntrkj;   //!
   TBranch        *b_jet_antikt4h1tower_flavor_component_svp_efrc;   //!
   TBranch        *b_jet_antikt4h1tower_flavor_component_sv0p_mass;   //!
   TBranch        *b_jet_antikt4h1tower_flavor_component_sv0p_n2t;   //!
   TBranch        *b_jet_antikt4h1tower_flavor_component_sv0p_svok;   //!
   TBranch        *b_jet_antikt4h1tower_flavor_component_sv0p_ntrk;   //!
   TBranch        *b_jet_antikt4h1tower_flavor_component_sv0p_ntrkv;   //!
   TBranch        *b_jet_antikt4h1tower_flavor_component_sv0p_ntrkj;   //!
   TBranch        *b_jet_antikt4h1tower_flavor_component_sv0p_efrc;   //!
   TBranch        *b_jet_antikt4h1tower_flavor_component_jfit_pu;   //!
   TBranch        *b_jet_antikt4h1tower_flavor_component_jfit_pb;   //!
   TBranch        *b_jet_antikt4h1tower_flavor_component_jfit_nvtxnt;   //!
   TBranch        *b_jet_antikt4h1tower_flavor_component_jfit_nvtx1t;   //!
   TBranch        *b_jet_antikt4h1tower_flavor_component_jfit_ntrk;   //!
   TBranch        *b_jet_antikt4h1tower_flavor_component_jfit_efrc;   //!
   TBranch        *b_jet_antikt4h1tower_flavor_component_jfit_mass;   //!
   TBranch        *b_jet_antikt4h1tower_flavor_component_jfit_sig3d;   //!
   TBranch        *b_jet_antikt4h1tower_constscale_E;   //!
   TBranch        *b_jet_antikt4h1tower_constscale_pt;   //!
   TBranch        *b_jet_antikt4h1tower_constscale_m;   //!
   TBranch        *b_jet_antikt4h1tower_constscale_eta;   //!
   TBranch        *b_jet_antikt4h1tower_constscale_phi;   //!
   TBranch        *b_jet_antikt4h1tower_el_dr;   //!
   TBranch        *b_jet_antikt4h1tower_el_matched;   //!
   TBranch        *b_jet_antikt4h1tower_mu_dr;   //!
   TBranch        *b_jet_antikt4h1tower_mu_matched;   //!
   TBranch        *b_jet_antikt6h1tower_n;   //!
   TBranch        *b_jet_antikt6h1tower_E;   //!
   TBranch        *b_jet_antikt6h1tower_pt;   //!
   TBranch        *b_jet_antikt6h1tower_m;   //!
   TBranch        *b_jet_antikt6h1tower_eta;   //!
   TBranch        *b_jet_antikt6h1tower_phi;   //!
   TBranch        *b_jet_antikt6h1tower_EtaPhys;   //!
   TBranch        *b_jet_antikt6h1tower_PhiPhys;   //!
   TBranch        *b_jet_antikt6h1tower_MPhys;   //!
   TBranch        *b_jet_antikt6h1tower_WIDTH;   //!
   TBranch        *b_jet_antikt6h1tower_n90;   //!
   TBranch        *b_jet_antikt6h1tower_n90constituents;   //!
   TBranch        *b_jet_antikt6h1tower_fracSamplingMax;   //!
   TBranch        *b_jet_antikt6h1tower_SamplingMax;   //!
   TBranch        *b_jet_antikt6h1tower_BCH_CORR_CELL;   //!
   TBranch        *b_jet_antikt6h1tower_BCH_CORR_DOTX;   //!
   TBranch        *b_jet_antikt6h1tower_BCH_CORR_JET;   //!
   TBranch        *b_jet_antikt6h1tower_BCH_CORR_JET_FORCELL;   //!
   TBranch        *b_jet_antikt6h1tower_ENG_BAD_CELLS;   //!
   TBranch        *b_jet_antikt6h1tower_N_BAD_CELLS;   //!
   TBranch        *b_jet_antikt6h1tower_N_BAD_CELLS_CORR;   //!
   TBranch        *b_jet_antikt6h1tower_BAD_CELLS_CORR_E;   //!
   TBranch        *b_jet_antikt6h1tower_hecf;   //!
   TBranch        *b_jet_antikt6h1tower_tgap3f;   //!
   TBranch        *b_jet_antikt6h1tower_isGood;   //!
   TBranch        *b_jet_antikt6h1tower_timing;   //!
   TBranch        *b_jet_antikt6h1tower_quality;   //!
   TBranch        *b_jet_antikt6h1tower_emfrac;   //!
   TBranch        *b_jet_antikt6h1tower_GCWJES;   //!
   TBranch        *b_jet_antikt6h1tower_EMJES;   //!
   TBranch        *b_jet_antikt6h1tower_CB;   //!
   TBranch        *b_jet_antikt6h1tower_emscale_E;   //!
   TBranch        *b_jet_antikt6h1tower_emscale_pt;   //!
   TBranch        *b_jet_antikt6h1tower_emscale_m;   //!
   TBranch        *b_jet_antikt6h1tower_emscale_eta;   //!
   TBranch        *b_jet_antikt6h1tower_emscale_phi;   //!
   TBranch        *b_jet_antikt6h1tower_jvtxf;   //!
   TBranch        *b_jet_antikt6h1tower_jvtx_x;   //!
   TBranch        *b_jet_antikt6h1tower_jvtx_y;   //!
   TBranch        *b_jet_antikt6h1tower_jvtx_z;   //!
   TBranch        *b_jet_antikt6h1tower_flavor_weight;   //!
   TBranch        *b_jet_antikt6h1tower_flavor_weight_TrackCounting2D;   //!
   TBranch        *b_jet_antikt6h1tower_flavor_weight_JetProb;   //!
   TBranch        *b_jet_antikt6h1tower_flavor_weight_IP1D;   //!
   TBranch        *b_jet_antikt6h1tower_flavor_weight_IP2D;   //!
   TBranch        *b_jet_antikt6h1tower_flavor_weight_IP3D;   //!
   TBranch        *b_jet_antikt6h1tower_flavor_weight_SV0;   //!
   TBranch        *b_jet_antikt6h1tower_flavor_weight_SV1;   //!
   TBranch        *b_jet_antikt6h1tower_flavor_weight_SV2;   //!
   TBranch        *b_jet_antikt6h1tower_flavor_weight_JetFitterTag;   //!
   TBranch        *b_jet_antikt6h1tower_flavor_weight_JetFitterCOMB;   //!
   TBranch        *b_jet_antikt6h1tower_flavor_weight_JetFitterTagNN;   //!
   TBranch        *b_jet_antikt6h1tower_flavor_weight_JetFitterCOMBNN;   //!
   TBranch        *b_jet_antikt6h1tower_flavor_weight_SoftMuonTag;   //!
   TBranch        *b_jet_antikt6h1tower_flavor_weight_SoftElectronTag;   //!
   TBranch        *b_jet_antikt6h1tower_e_PreSamplerB;   //!
   TBranch        *b_jet_antikt6h1tower_e_EMB1;   //!
   TBranch        *b_jet_antikt6h1tower_e_EMB2;   //!
   TBranch        *b_jet_antikt6h1tower_e_EMB3;   //!
   TBranch        *b_jet_antikt6h1tower_e_PreSamplerE;   //!
   TBranch        *b_jet_antikt6h1tower_e_EME1;   //!
   TBranch        *b_jet_antikt6h1tower_e_EME2;   //!
   TBranch        *b_jet_antikt6h1tower_e_EME3;   //!
   TBranch        *b_jet_antikt6h1tower_e_HEC0;   //!
   TBranch        *b_jet_antikt6h1tower_e_HEC1;   //!
   TBranch        *b_jet_antikt6h1tower_e_HEC2;   //!
   TBranch        *b_jet_antikt6h1tower_e_HEC3;   //!
   TBranch        *b_jet_antikt6h1tower_e_TileBar0;   //!
   TBranch        *b_jet_antikt6h1tower_e_TileBar1;   //!
   TBranch        *b_jet_antikt6h1tower_e_TileBar2;   //!
   TBranch        *b_jet_antikt6h1tower_e_TileGap1;   //!
   TBranch        *b_jet_antikt6h1tower_e_TileGap2;   //!
   TBranch        *b_jet_antikt6h1tower_e_TileGap3;   //!
   TBranch        *b_jet_antikt6h1tower_e_TileExt0;   //!
   TBranch        *b_jet_antikt6h1tower_e_TileExt1;   //!
   TBranch        *b_jet_antikt6h1tower_e_TileExt2;   //!
   TBranch        *b_jet_antikt6h1tower_e_FCAL0;   //!
   TBranch        *b_jet_antikt6h1tower_e_FCAL1;   //!
   TBranch        *b_jet_antikt6h1tower_e_FCAL2;   //!
   TBranch        *b_jet_antikt6h1tower_shapeBins;   //!
   TBranch        *b_jet_antikt6h1tower_flavor_component_ip2d_pu;   //!
   TBranch        *b_jet_antikt6h1tower_flavor_component_ip2d_pb;   //!
   TBranch        *b_jet_antikt6h1tower_flavor_component_ip2d_ntrk;   //!
   TBranch        *b_jet_antikt6h1tower_flavor_component_ip3d_pu;   //!
   TBranch        *b_jet_antikt6h1tower_flavor_component_ip3d_pb;   //!
   TBranch        *b_jet_antikt6h1tower_flavor_component_ip3d_ntrk;   //!
   TBranch        *b_jet_antikt6h1tower_flavor_component_sv1_pu;   //!
   TBranch        *b_jet_antikt6h1tower_flavor_component_sv1_pb;   //!
   TBranch        *b_jet_antikt6h1tower_flavor_component_sv2_pu;   //!
   TBranch        *b_jet_antikt6h1tower_flavor_component_sv2_pb;   //!
   TBranch        *b_jet_antikt6h1tower_flavor_component_svp_mass;   //!
   TBranch        *b_jet_antikt6h1tower_flavor_component_svp_n2t;   //!
   TBranch        *b_jet_antikt6h1tower_flavor_component_svp_svok;   //!
   TBranch        *b_jet_antikt6h1tower_flavor_component_svp_ntrk;   //!
   TBranch        *b_jet_antikt6h1tower_flavor_component_svp_ntrkv;   //!
   TBranch        *b_jet_antikt6h1tower_flavor_component_svp_ntrkj;   //!
   TBranch        *b_jet_antikt6h1tower_flavor_component_svp_efrc;   //!
   TBranch        *b_jet_antikt6h1tower_flavor_component_sv0p_mass;   //!
   TBranch        *b_jet_antikt6h1tower_flavor_component_sv0p_n2t;   //!
   TBranch        *b_jet_antikt6h1tower_flavor_component_sv0p_svok;   //!
   TBranch        *b_jet_antikt6h1tower_flavor_component_sv0p_ntrk;   //!
   TBranch        *b_jet_antikt6h1tower_flavor_component_sv0p_ntrkv;   //!
   TBranch        *b_jet_antikt6h1tower_flavor_component_sv0p_ntrkj;   //!
   TBranch        *b_jet_antikt6h1tower_flavor_component_sv0p_efrc;   //!
   TBranch        *b_jet_antikt6h1tower_flavor_component_jfit_pu;   //!
   TBranch        *b_jet_antikt6h1tower_flavor_component_jfit_pb;   //!
   TBranch        *b_jet_antikt6h1tower_flavor_component_jfit_nvtxnt;   //!
   TBranch        *b_jet_antikt6h1tower_flavor_component_jfit_nvtx1t;   //!
   TBranch        *b_jet_antikt6h1tower_flavor_component_jfit_ntrk;   //!
   TBranch        *b_jet_antikt6h1tower_flavor_component_jfit_efrc;   //!
   TBranch        *b_jet_antikt6h1tower_flavor_component_jfit_mass;   //!
   TBranch        *b_jet_antikt6h1tower_flavor_component_jfit_sig3d;   //!
   TBranch        *b_jet_antikt6h1tower_constscale_E;   //!
   TBranch        *b_jet_antikt6h1tower_constscale_pt;   //!
   TBranch        *b_jet_antikt6h1tower_constscale_m;   //!
   TBranch        *b_jet_antikt6h1tower_constscale_eta;   //!
   TBranch        *b_jet_antikt6h1tower_constscale_phi;   //!
   TBranch        *b_jet_antikt6h1tower_el_dr;   //!
   TBranch        *b_jet_antikt6h1tower_el_matched;   //!
   TBranch        *b_jet_antikt6h1tower_mu_dr;   //!
   TBranch        *b_jet_antikt6h1tower_mu_matched;   //!
   TBranch        *b_jet_antikt4lctopo_n;   //!
   TBranch        *b_jet_antikt4lctopo_E;   //!
   TBranch        *b_jet_antikt4lctopo_pt;   //!
   TBranch        *b_jet_antikt4lctopo_m;   //!
   TBranch        *b_jet_antikt4lctopo_eta;   //!
   TBranch        *b_jet_antikt4lctopo_phi;   //!
   TBranch        *b_jet_antikt4lctopo_EtaPhys;   //!
   TBranch        *b_jet_antikt4lctopo_PhiPhys;   //!
   TBranch        *b_jet_antikt4lctopo_MPhys;   //!
   TBranch        *b_jet_antikt4lctopo_WIDTH;   //!
   TBranch        *b_jet_antikt4lctopo_n90;   //!
   TBranch        *b_jet_antikt4lctopo_n90constituents;   //!
   TBranch        *b_jet_antikt4lctopo_fracSamplingMax;   //!
   TBranch        *b_jet_antikt4lctopo_SamplingMax;   //!
   TBranch        *b_jet_antikt4lctopo_BCH_CORR_CELL;   //!
   TBranch        *b_jet_antikt4lctopo_BCH_CORR_DOTX;   //!
   TBranch        *b_jet_antikt4lctopo_BCH_CORR_JET;   //!
   TBranch        *b_jet_antikt4lctopo_BCH_CORR_JET_FORCELL;   //!
   TBranch        *b_jet_antikt4lctopo_ENG_BAD_CELLS;   //!
   TBranch        *b_jet_antikt4lctopo_N_BAD_CELLS;   //!
   TBranch        *b_jet_antikt4lctopo_N_BAD_CELLS_CORR;   //!
   TBranch        *b_jet_antikt4lctopo_BAD_CELLS_CORR_E;   //!
   TBranch        *b_jet_antikt4lctopo_hecf;   //!
   TBranch        *b_jet_antikt4lctopo_tgap3f;   //!
   TBranch        *b_jet_antikt4lctopo_isGood;   //!
   TBranch        *b_jet_antikt4lctopo_timing;   //!
   TBranch        *b_jet_antikt4lctopo_quality;   //!
   TBranch        *b_jet_antikt4lctopo_emfrac;   //!
   TBranch        *b_jet_antikt4lctopo_GCWJES;   //!
   TBranch        *b_jet_antikt4lctopo_EMJES;   //!
   TBranch        *b_jet_antikt4lctopo_CB;   //!
   TBranch        *b_jet_antikt4lctopo_emscale_E;   //!
   TBranch        *b_jet_antikt4lctopo_emscale_pt;   //!
   TBranch        *b_jet_antikt4lctopo_emscale_m;   //!
   TBranch        *b_jet_antikt4lctopo_emscale_eta;   //!
   TBranch        *b_jet_antikt4lctopo_emscale_phi;   //!
   TBranch        *b_jet_antikt4lctopo_jvtxf;   //!
   TBranch        *b_jet_antikt4lctopo_jvtx_x;   //!
   TBranch        *b_jet_antikt4lctopo_jvtx_y;   //!
   TBranch        *b_jet_antikt4lctopo_jvtx_z;   //!
   TBranch        *b_jet_antikt4lctopo_flavor_weight;   //!
   TBranch        *b_jet_antikt4lctopo_flavor_weight_TrackCounting2D;   //!
   TBranch        *b_jet_antikt4lctopo_flavor_weight_JetProb;   //!
   TBranch        *b_jet_antikt4lctopo_flavor_weight_IP1D;   //!
   TBranch        *b_jet_antikt4lctopo_flavor_weight_IP2D;   //!
   TBranch        *b_jet_antikt4lctopo_flavor_weight_IP3D;   //!
   TBranch        *b_jet_antikt4lctopo_flavor_weight_SV0;   //!
   TBranch        *b_jet_antikt4lctopo_flavor_weight_SV1;   //!
   TBranch        *b_jet_antikt4lctopo_flavor_weight_SV2;   //!
   TBranch        *b_jet_antikt4lctopo_flavor_weight_JetFitterTag;   //!
   TBranch        *b_jet_antikt4lctopo_flavor_weight_JetFitterCOMB;   //!
   TBranch        *b_jet_antikt4lctopo_flavor_weight_JetFitterTagNN;   //!
   TBranch        *b_jet_antikt4lctopo_flavor_weight_JetFitterCOMBNN;   //!
   TBranch        *b_jet_antikt4lctopo_flavor_weight_SoftMuonTag;   //!
   TBranch        *b_jet_antikt4lctopo_flavor_weight_SoftElectronTag;   //!
   TBranch        *b_jet_antikt4lctopo_e_PreSamplerB;   //!
   TBranch        *b_jet_antikt4lctopo_e_EMB1;   //!
   TBranch        *b_jet_antikt4lctopo_e_EMB2;   //!
   TBranch        *b_jet_antikt4lctopo_e_EMB3;   //!
   TBranch        *b_jet_antikt4lctopo_e_PreSamplerE;   //!
   TBranch        *b_jet_antikt4lctopo_e_EME1;   //!
   TBranch        *b_jet_antikt4lctopo_e_EME2;   //!
   TBranch        *b_jet_antikt4lctopo_e_EME3;   //!
   TBranch        *b_jet_antikt4lctopo_e_HEC0;   //!
   TBranch        *b_jet_antikt4lctopo_e_HEC1;   //!
   TBranch        *b_jet_antikt4lctopo_e_HEC2;   //!
   TBranch        *b_jet_antikt4lctopo_e_HEC3;   //!
   TBranch        *b_jet_antikt4lctopo_e_TileBar0;   //!
   TBranch        *b_jet_antikt4lctopo_e_TileBar1;   //!
   TBranch        *b_jet_antikt4lctopo_e_TileBar2;   //!
   TBranch        *b_jet_antikt4lctopo_e_TileGap1;   //!
   TBranch        *b_jet_antikt4lctopo_e_TileGap2;   //!
   TBranch        *b_jet_antikt4lctopo_e_TileGap3;   //!
   TBranch        *b_jet_antikt4lctopo_e_TileExt0;   //!
   TBranch        *b_jet_antikt4lctopo_e_TileExt1;   //!
   TBranch        *b_jet_antikt4lctopo_e_TileExt2;   //!
   TBranch        *b_jet_antikt4lctopo_e_FCAL0;   //!
   TBranch        *b_jet_antikt4lctopo_e_FCAL1;   //!
   TBranch        *b_jet_antikt4lctopo_e_FCAL2;   //!
   TBranch        *b_jet_antikt4lctopo_shapeBins;   //!
   TBranch        *b_jet_antikt4lctopo_flavor_component_ip2d_pu;   //!
   TBranch        *b_jet_antikt4lctopo_flavor_component_ip2d_pb;   //!
   TBranch        *b_jet_antikt4lctopo_flavor_component_ip2d_ntrk;   //!
   TBranch        *b_jet_antikt4lctopo_flavor_component_ip3d_pu;   //!
   TBranch        *b_jet_antikt4lctopo_flavor_component_ip3d_pb;   //!
   TBranch        *b_jet_antikt4lctopo_flavor_component_ip3d_ntrk;   //!
   TBranch        *b_jet_antikt4lctopo_flavor_component_sv1_pu;   //!
   TBranch        *b_jet_antikt4lctopo_flavor_component_sv1_pb;   //!
   TBranch        *b_jet_antikt4lctopo_flavor_component_sv2_pu;   //!
   TBranch        *b_jet_antikt4lctopo_flavor_component_sv2_pb;   //!
   TBranch        *b_jet_antikt4lctopo_flavor_component_svp_mass;   //!
   TBranch        *b_jet_antikt4lctopo_flavor_component_svp_n2t;   //!
   TBranch        *b_jet_antikt4lctopo_flavor_component_svp_svok;   //!
   TBranch        *b_jet_antikt4lctopo_flavor_component_svp_ntrk;   //!
   TBranch        *b_jet_antikt4lctopo_flavor_component_svp_ntrkv;   //!
   TBranch        *b_jet_antikt4lctopo_flavor_component_svp_ntrkj;   //!
   TBranch        *b_jet_antikt4lctopo_flavor_component_svp_efrc;   //!
   TBranch        *b_jet_antikt4lctopo_flavor_component_sv0p_mass;   //!
   TBranch        *b_jet_antikt4lctopo_flavor_component_sv0p_n2t;   //!
   TBranch        *b_jet_antikt4lctopo_flavor_component_sv0p_svok;   //!
   TBranch        *b_jet_antikt4lctopo_flavor_component_sv0p_ntrk;   //!
   TBranch        *b_jet_antikt4lctopo_flavor_component_sv0p_ntrkv;   //!
   TBranch        *b_jet_antikt4lctopo_flavor_component_sv0p_ntrkj;   //!
   TBranch        *b_jet_antikt4lctopo_flavor_component_sv0p_efrc;   //!
   TBranch        *b_jet_antikt4lctopo_flavor_component_jfit_pu;   //!
   TBranch        *b_jet_antikt4lctopo_flavor_component_jfit_pb;   //!
   TBranch        *b_jet_antikt4lctopo_flavor_component_jfit_nvtxnt;   //!
   TBranch        *b_jet_antikt4lctopo_flavor_component_jfit_nvtx1t;   //!
   TBranch        *b_jet_antikt4lctopo_flavor_component_jfit_ntrk;   //!
   TBranch        *b_jet_antikt4lctopo_flavor_component_jfit_efrc;   //!
   TBranch        *b_jet_antikt4lctopo_flavor_component_jfit_mass;   //!
   TBranch        *b_jet_antikt4lctopo_flavor_component_jfit_sig3d;   //!
   TBranch        *b_jet_antikt4lctopo_constscale_E;   //!
   TBranch        *b_jet_antikt4lctopo_constscale_pt;   //!
   TBranch        *b_jet_antikt4lctopo_constscale_m;   //!
   TBranch        *b_jet_antikt4lctopo_constscale_eta;   //!
   TBranch        *b_jet_antikt4lctopo_constscale_phi;   //!
   TBranch        *b_jet_antikt4lctopo_el_dr;   //!
   TBranch        *b_jet_antikt4lctopo_el_matched;   //!
   TBranch        *b_jet_antikt4lctopo_mu_dr;   //!
   TBranch        *b_jet_antikt4lctopo_mu_matched;   //!
   TBranch        *b_jet_antikt6lctopo_n;   //!
   TBranch        *b_jet_antikt6lctopo_E;   //!
   TBranch        *b_jet_antikt6lctopo_pt;   //!
   TBranch        *b_jet_antikt6lctopo_m;   //!
   TBranch        *b_jet_antikt6lctopo_eta;   //!
   TBranch        *b_jet_antikt6lctopo_phi;   //!
   TBranch        *b_jet_antikt6lctopo_EtaPhys;   //!
   TBranch        *b_jet_antikt6lctopo_PhiPhys;   //!
   TBranch        *b_jet_antikt6lctopo_MPhys;   //!
   TBranch        *b_jet_antikt6lctopo_WIDTH;   //!
   TBranch        *b_jet_antikt6lctopo_n90;   //!
   TBranch        *b_jet_antikt6lctopo_n90constituents;   //!
   TBranch        *b_jet_antikt6lctopo_fracSamplingMax;   //!
   TBranch        *b_jet_antikt6lctopo_SamplingMax;   //!
   TBranch        *b_jet_antikt6lctopo_BCH_CORR_CELL;   //!
   TBranch        *b_jet_antikt6lctopo_BCH_CORR_DOTX;   //!
   TBranch        *b_jet_antikt6lctopo_BCH_CORR_JET;   //!
   TBranch        *b_jet_antikt6lctopo_BCH_CORR_JET_FORCELL;   //!
   TBranch        *b_jet_antikt6lctopo_ENG_BAD_CELLS;   //!
   TBranch        *b_jet_antikt6lctopo_N_BAD_CELLS;   //!
   TBranch        *b_jet_antikt6lctopo_N_BAD_CELLS_CORR;   //!
   TBranch        *b_jet_antikt6lctopo_BAD_CELLS_CORR_E;   //!
   TBranch        *b_jet_antikt6lctopo_hecf;   //!
   TBranch        *b_jet_antikt6lctopo_tgap3f;   //!
   TBranch        *b_jet_antikt6lctopo_isGood;   //!
   TBranch        *b_jet_antikt6lctopo_timing;   //!
   TBranch        *b_jet_antikt6lctopo_quality;   //!
   TBranch        *b_jet_antikt6lctopo_emfrac;   //!
   TBranch        *b_jet_antikt6lctopo_GCWJES;   //!
   TBranch        *b_jet_antikt6lctopo_EMJES;   //!
   TBranch        *b_jet_antikt6lctopo_CB;   //!
   TBranch        *b_jet_antikt6lctopo_emscale_E;   //!
   TBranch        *b_jet_antikt6lctopo_emscale_pt;   //!
   TBranch        *b_jet_antikt6lctopo_emscale_m;   //!
   TBranch        *b_jet_antikt6lctopo_emscale_eta;   //!
   TBranch        *b_jet_antikt6lctopo_emscale_phi;   //!
   TBranch        *b_jet_antikt6lctopo_jvtxf;   //!
   TBranch        *b_jet_antikt6lctopo_jvtx_x;   //!
   TBranch        *b_jet_antikt6lctopo_jvtx_y;   //!
   TBranch        *b_jet_antikt6lctopo_jvtx_z;   //!
   TBranch        *b_jet_antikt6lctopo_flavor_weight;   //!
   TBranch        *b_jet_antikt6lctopo_flavor_weight_TrackCounting2D;   //!
   TBranch        *b_jet_antikt6lctopo_flavor_weight_JetProb;   //!
   TBranch        *b_jet_antikt6lctopo_flavor_weight_IP1D;   //!
   TBranch        *b_jet_antikt6lctopo_flavor_weight_IP2D;   //!
   TBranch        *b_jet_antikt6lctopo_flavor_weight_IP3D;   //!
   TBranch        *b_jet_antikt6lctopo_flavor_weight_SV0;   //!
   TBranch        *b_jet_antikt6lctopo_flavor_weight_SV1;   //!
   TBranch        *b_jet_antikt6lctopo_flavor_weight_SV2;   //!
   TBranch        *b_jet_antikt6lctopo_flavor_weight_JetFitterTag;   //!
   TBranch        *b_jet_antikt6lctopo_flavor_weight_JetFitterCOMB;   //!
   TBranch        *b_jet_antikt6lctopo_flavor_weight_JetFitterTagNN;   //!
   TBranch        *b_jet_antikt6lctopo_flavor_weight_JetFitterCOMBNN;   //!
   TBranch        *b_jet_antikt6lctopo_flavor_weight_SoftMuonTag;   //!
   TBranch        *b_jet_antikt6lctopo_flavor_weight_SoftElectronTag;   //!
   TBranch        *b_jet_antikt6lctopo_e_PreSamplerB;   //!
   TBranch        *b_jet_antikt6lctopo_e_EMB1;   //!
   TBranch        *b_jet_antikt6lctopo_e_EMB2;   //!
   TBranch        *b_jet_antikt6lctopo_e_EMB3;   //!
   TBranch        *b_jet_antikt6lctopo_e_PreSamplerE;   //!
   TBranch        *b_jet_antikt6lctopo_e_EME1;   //!
   TBranch        *b_jet_antikt6lctopo_e_EME2;   //!
   TBranch        *b_jet_antikt6lctopo_e_EME3;   //!
   TBranch        *b_jet_antikt6lctopo_e_HEC0;   //!
   TBranch        *b_jet_antikt6lctopo_e_HEC1;   //!
   TBranch        *b_jet_antikt6lctopo_e_HEC2;   //!
   TBranch        *b_jet_antikt6lctopo_e_HEC3;   //!
   TBranch        *b_jet_antikt6lctopo_e_TileBar0;   //!
   TBranch        *b_jet_antikt6lctopo_e_TileBar1;   //!
   TBranch        *b_jet_antikt6lctopo_e_TileBar2;   //!
   TBranch        *b_jet_antikt6lctopo_e_TileGap1;   //!
   TBranch        *b_jet_antikt6lctopo_e_TileGap2;   //!
   TBranch        *b_jet_antikt6lctopo_e_TileGap3;   //!
   TBranch        *b_jet_antikt6lctopo_e_TileExt0;   //!
   TBranch        *b_jet_antikt6lctopo_e_TileExt1;   //!
   TBranch        *b_jet_antikt6lctopo_e_TileExt2;   //!
   TBranch        *b_jet_antikt6lctopo_e_FCAL0;   //!
   TBranch        *b_jet_antikt6lctopo_e_FCAL1;   //!
   TBranch        *b_jet_antikt6lctopo_e_FCAL2;   //!
   TBranch        *b_jet_antikt6lctopo_shapeBins;   //!
   TBranch        *b_jet_antikt6lctopo_flavor_component_ip2d_pu;   //!
   TBranch        *b_jet_antikt6lctopo_flavor_component_ip2d_pb;   //!
   TBranch        *b_jet_antikt6lctopo_flavor_component_ip2d_ntrk;   //!
   TBranch        *b_jet_antikt6lctopo_flavor_component_ip3d_pu;   //!
   TBranch        *b_jet_antikt6lctopo_flavor_component_ip3d_pb;   //!
   TBranch        *b_jet_antikt6lctopo_flavor_component_ip3d_ntrk;   //!
   TBranch        *b_jet_antikt6lctopo_flavor_component_sv1_pu;   //!
   TBranch        *b_jet_antikt6lctopo_flavor_component_sv1_pb;   //!
   TBranch        *b_jet_antikt6lctopo_flavor_component_sv2_pu;   //!
   TBranch        *b_jet_antikt6lctopo_flavor_component_sv2_pb;   //!
   TBranch        *b_jet_antikt6lctopo_flavor_component_svp_mass;   //!
   TBranch        *b_jet_antikt6lctopo_flavor_component_svp_n2t;   //!
   TBranch        *b_jet_antikt6lctopo_flavor_component_svp_svok;   //!
   TBranch        *b_jet_antikt6lctopo_flavor_component_svp_ntrk;   //!
   TBranch        *b_jet_antikt6lctopo_flavor_component_svp_ntrkv;   //!
   TBranch        *b_jet_antikt6lctopo_flavor_component_svp_ntrkj;   //!
   TBranch        *b_jet_antikt6lctopo_flavor_component_svp_efrc;   //!
   TBranch        *b_jet_antikt6lctopo_flavor_component_sv0p_mass;   //!
   TBranch        *b_jet_antikt6lctopo_flavor_component_sv0p_n2t;   //!
   TBranch        *b_jet_antikt6lctopo_flavor_component_sv0p_svok;   //!
   TBranch        *b_jet_antikt6lctopo_flavor_component_sv0p_ntrk;   //!
   TBranch        *b_jet_antikt6lctopo_flavor_component_sv0p_ntrkv;   //!
   TBranch        *b_jet_antikt6lctopo_flavor_component_sv0p_ntrkj;   //!
   TBranch        *b_jet_antikt6lctopo_flavor_component_sv0p_efrc;   //!
   TBranch        *b_jet_antikt6lctopo_flavor_component_jfit_pu;   //!
   TBranch        *b_jet_antikt6lctopo_flavor_component_jfit_pb;   //!
   TBranch        *b_jet_antikt6lctopo_flavor_component_jfit_nvtxnt;   //!
   TBranch        *b_jet_antikt6lctopo_flavor_component_jfit_nvtx1t;   //!
   TBranch        *b_jet_antikt6lctopo_flavor_component_jfit_ntrk;   //!
   TBranch        *b_jet_antikt6lctopo_flavor_component_jfit_efrc;   //!
   TBranch        *b_jet_antikt6lctopo_flavor_component_jfit_mass;   //!
   TBranch        *b_jet_antikt6lctopo_flavor_component_jfit_sig3d;   //!
   TBranch        *b_jet_antikt6lctopo_constscale_E;   //!
   TBranch        *b_jet_antikt6lctopo_constscale_pt;   //!
   TBranch        *b_jet_antikt6lctopo_constscale_m;   //!
   TBranch        *b_jet_antikt6lctopo_constscale_eta;   //!
   TBranch        *b_jet_antikt6lctopo_constscale_phi;   //!
   TBranch        *b_jet_antikt6lctopo_el_dr;   //!
   TBranch        *b_jet_antikt6lctopo_el_matched;   //!
   TBranch        *b_jet_antikt6lctopo_mu_dr;   //!
   TBranch        *b_jet_antikt6lctopo_mu_matched;   //!
   TBranch        *b_jet_antikt6h1topo_n;   //!
   TBranch        *b_jet_antikt6h1topo_E;   //!
   TBranch        *b_jet_antikt6h1topo_pt;   //!
   TBranch        *b_jet_antikt6h1topo_m;   //!
   TBranch        *b_jet_antikt6h1topo_eta;   //!
   TBranch        *b_jet_antikt6h1topo_phi;   //!
   TBranch        *b_jet_antikt6h1topo_EtaPhys;   //!
   TBranch        *b_jet_antikt6h1topo_PhiPhys;   //!
   TBranch        *b_jet_antikt6h1topo_MPhys;   //!
   TBranch        *b_jet_antikt6h1topo_WIDTH;   //!
   TBranch        *b_jet_antikt6h1topo_n90;   //!
   TBranch        *b_jet_antikt6h1topo_n90constituents;   //!
   TBranch        *b_jet_antikt6h1topo_fracSamplingMax;   //!
   TBranch        *b_jet_antikt6h1topo_SamplingMax;   //!
   TBranch        *b_jet_antikt6h1topo_BCH_CORR_CELL;   //!
   TBranch        *b_jet_antikt6h1topo_BCH_CORR_DOTX;   //!
   TBranch        *b_jet_antikt6h1topo_BCH_CORR_JET;   //!
   TBranch        *b_jet_antikt6h1topo_BCH_CORR_JET_FORCELL;   //!
   TBranch        *b_jet_antikt6h1topo_ENG_BAD_CELLS;   //!
   TBranch        *b_jet_antikt6h1topo_N_BAD_CELLS;   //!
   TBranch        *b_jet_antikt6h1topo_N_BAD_CELLS_CORR;   //!
   TBranch        *b_jet_antikt6h1topo_BAD_CELLS_CORR_E;   //!
   TBranch        *b_jet_antikt6h1topo_hecf;   //!
   TBranch        *b_jet_antikt6h1topo_tgap3f;   //!
   TBranch        *b_jet_antikt6h1topo_isGood;   //!
   TBranch        *b_jet_antikt6h1topo_timing;   //!
   TBranch        *b_jet_antikt6h1topo_quality;   //!
   TBranch        *b_jet_antikt6h1topo_emfrac;   //!
   TBranch        *b_jet_antikt6h1topo_GCWJES;   //!
   TBranch        *b_jet_antikt6h1topo_EMJES;   //!
   TBranch        *b_jet_antikt6h1topo_CB;   //!
   TBranch        *b_jet_antikt6h1topo_emscale_E;   //!
   TBranch        *b_jet_antikt6h1topo_emscale_pt;   //!
   TBranch        *b_jet_antikt6h1topo_emscale_m;   //!
   TBranch        *b_jet_antikt6h1topo_emscale_eta;   //!
   TBranch        *b_jet_antikt6h1topo_emscale_phi;   //!
   TBranch        *b_jet_antikt6h1topo_jvtxf;   //!
   TBranch        *b_jet_antikt6h1topo_jvtx_x;   //!
   TBranch        *b_jet_antikt6h1topo_jvtx_y;   //!
   TBranch        *b_jet_antikt6h1topo_jvtx_z;   //!
   TBranch        *b_jet_antikt6h1topo_flavor_weight;   //!
   TBranch        *b_jet_antikt6h1topo_flavor_weight_TrackCounting2D;   //!
   TBranch        *b_jet_antikt6h1topo_flavor_weight_JetProb;   //!
   TBranch        *b_jet_antikt6h1topo_flavor_weight_IP1D;   //!
   TBranch        *b_jet_antikt6h1topo_flavor_weight_IP2D;   //!
   TBranch        *b_jet_antikt6h1topo_flavor_weight_IP3D;   //!
   TBranch        *b_jet_antikt6h1topo_flavor_weight_SV0;   //!
   TBranch        *b_jet_antikt6h1topo_flavor_weight_SV1;   //!
   TBranch        *b_jet_antikt6h1topo_flavor_weight_SV2;   //!
   TBranch        *b_jet_antikt6h1topo_flavor_weight_JetFitterTag;   //!
   TBranch        *b_jet_antikt6h1topo_flavor_weight_JetFitterCOMB;   //!
   TBranch        *b_jet_antikt6h1topo_flavor_weight_JetFitterTagNN;   //!
   TBranch        *b_jet_antikt6h1topo_flavor_weight_JetFitterCOMBNN;   //!
   TBranch        *b_jet_antikt6h1topo_flavor_weight_SoftMuonTag;   //!
   TBranch        *b_jet_antikt6h1topo_flavor_weight_SoftElectronTag;   //!
   TBranch        *b_jet_antikt6h1topo_e_PreSamplerB;   //!
   TBranch        *b_jet_antikt6h1topo_e_EMB1;   //!
   TBranch        *b_jet_antikt6h1topo_e_EMB2;   //!
   TBranch        *b_jet_antikt6h1topo_e_EMB3;   //!
   TBranch        *b_jet_antikt6h1topo_e_PreSamplerE;   //!
   TBranch        *b_jet_antikt6h1topo_e_EME1;   //!
   TBranch        *b_jet_antikt6h1topo_e_EME2;   //!
   TBranch        *b_jet_antikt6h1topo_e_EME3;   //!
   TBranch        *b_jet_antikt6h1topo_e_HEC0;   //!
   TBranch        *b_jet_antikt6h1topo_e_HEC1;   //!
   TBranch        *b_jet_antikt6h1topo_e_HEC2;   //!
   TBranch        *b_jet_antikt6h1topo_e_HEC3;   //!
   TBranch        *b_jet_antikt6h1topo_e_TileBar0;   //!
   TBranch        *b_jet_antikt6h1topo_e_TileBar1;   //!
   TBranch        *b_jet_antikt6h1topo_e_TileBar2;   //!
   TBranch        *b_jet_antikt6h1topo_e_TileGap1;   //!
   TBranch        *b_jet_antikt6h1topo_e_TileGap2;   //!
   TBranch        *b_jet_antikt6h1topo_e_TileGap3;   //!
   TBranch        *b_jet_antikt6h1topo_e_TileExt0;   //!
   TBranch        *b_jet_antikt6h1topo_e_TileExt1;   //!
   TBranch        *b_jet_antikt6h1topo_e_TileExt2;   //!
   TBranch        *b_jet_antikt6h1topo_e_FCAL0;   //!
   TBranch        *b_jet_antikt6h1topo_e_FCAL1;   //!
   TBranch        *b_jet_antikt6h1topo_e_FCAL2;   //!
   TBranch        *b_jet_antikt6h1topo_shapeBins;   //!
   TBranch        *b_jet_antikt6h1topo_flavor_component_ip2d_pu;   //!
   TBranch        *b_jet_antikt6h1topo_flavor_component_ip2d_pb;   //!
   TBranch        *b_jet_antikt6h1topo_flavor_component_ip2d_ntrk;   //!
   TBranch        *b_jet_antikt6h1topo_flavor_component_ip3d_pu;   //!
   TBranch        *b_jet_antikt6h1topo_flavor_component_ip3d_pb;   //!
   TBranch        *b_jet_antikt6h1topo_flavor_component_ip3d_ntrk;   //!
   TBranch        *b_jet_antikt6h1topo_flavor_component_sv1_pu;   //!
   TBranch        *b_jet_antikt6h1topo_flavor_component_sv1_pb;   //!
   TBranch        *b_jet_antikt6h1topo_flavor_component_sv2_pu;   //!
   TBranch        *b_jet_antikt6h1topo_flavor_component_sv2_pb;   //!
   TBranch        *b_jet_antikt6h1topo_flavor_component_svp_mass;   //!
   TBranch        *b_jet_antikt6h1topo_flavor_component_svp_n2t;   //!
   TBranch        *b_jet_antikt6h1topo_flavor_component_svp_svok;   //!
   TBranch        *b_jet_antikt6h1topo_flavor_component_svp_ntrk;   //!
   TBranch        *b_jet_antikt6h1topo_flavor_component_svp_ntrkv;   //!
   TBranch        *b_jet_antikt6h1topo_flavor_component_svp_ntrkj;   //!
   TBranch        *b_jet_antikt6h1topo_flavor_component_svp_efrc;   //!
   TBranch        *b_jet_antikt6h1topo_flavor_component_sv0p_mass;   //!
   TBranch        *b_jet_antikt6h1topo_flavor_component_sv0p_n2t;   //!
   TBranch        *b_jet_antikt6h1topo_flavor_component_sv0p_svok;   //!
   TBranch        *b_jet_antikt6h1topo_flavor_component_sv0p_ntrk;   //!
   TBranch        *b_jet_antikt6h1topo_flavor_component_sv0p_ntrkv;   //!
   TBranch        *b_jet_antikt6h1topo_flavor_component_sv0p_ntrkj;   //!
   TBranch        *b_jet_antikt6h1topo_flavor_component_sv0p_efrc;   //!
   TBranch        *b_jet_antikt6h1topo_flavor_component_jfit_pu;   //!
   TBranch        *b_jet_antikt6h1topo_flavor_component_jfit_pb;   //!
   TBranch        *b_jet_antikt6h1topo_flavor_component_jfit_nvtxnt;   //!
   TBranch        *b_jet_antikt6h1topo_flavor_component_jfit_nvtx1t;   //!
   TBranch        *b_jet_antikt6h1topo_flavor_component_jfit_ntrk;   //!
   TBranch        *b_jet_antikt6h1topo_flavor_component_jfit_efrc;   //!
   TBranch        *b_jet_antikt6h1topo_flavor_component_jfit_mass;   //!
   TBranch        *b_jet_antikt6h1topo_flavor_component_jfit_sig3d;   //!
   TBranch        *b_jet_antikt6h1topo_constscale_E;   //!
   TBranch        *b_jet_antikt6h1topo_constscale_pt;   //!
   TBranch        *b_jet_antikt6h1topo_constscale_m;   //!
   TBranch        *b_jet_antikt6h1topo_constscale_eta;   //!
   TBranch        *b_jet_antikt6h1topo_constscale_phi;   //!
   TBranch        *b_jet_antikt6h1topo_el_dr;   //!
   TBranch        *b_jet_antikt6h1topo_el_matched;   //!
   TBranch        *b_jet_antikt6h1topo_mu_dr;   //!
   TBranch        *b_jet_antikt6h1topo_mu_matched;   //!
   TBranch        *b_MET_RefFinal_etx;   //!
   TBranch        *b_MET_RefFinal_ety;   //!
   TBranch        *b_MET_RefFinal_sumet;   //!
   TBranch        *b_MET_RefFinal_et;   //!
   TBranch        *b_MET_RefFinal_phi;   //!
   TBranch        *b_MET_MuonBoy_etx;   //!
   TBranch        *b_MET_MuonBoy_ety;   //!
   TBranch        *b_MET_MuonBoy_sumet;   //!
   TBranch        *b_MET_MuonBoy_et;   //!
   TBranch        *b_MET_MuonBoy_phi;   //!
   TBranch        *b_MET_Track_etx;   //!
   TBranch        *b_MET_Track_ety;   //!
   TBranch        *b_MET_Track_sumet;   //!
   TBranch        *b_MET_Track_et;   //!
   TBranch        *b_MET_Track_phi;   //!
   TBranch        *b_MET_RefGamma_etx;   //!
   TBranch        *b_MET_RefGamma_ety;   //!
   TBranch        *b_MET_RefGamma_sumet;   //!
   TBranch        *b_MET_RefGamma_et;   //!
   TBranch        *b_MET_RefGamma_phi;   //!
   TBranch        *b_MET_RefEle_etx;   //!
   TBranch        *b_MET_RefEle_ety;   //!
   TBranch        *b_MET_RefEle_sumet;   //!
   TBranch        *b_MET_RefEle_et;   //!
   TBranch        *b_MET_RefEle_phi;   //!
   TBranch        *b_MET_RefJet_etx;   //!
   TBranch        *b_MET_RefJet_ety;   //!
   TBranch        *b_MET_RefJet_sumet;   //!
   TBranch        *b_MET_RefJet_et;   //!
   TBranch        *b_MET_RefJet_phi;   //!
   TBranch        *b_MET_RefMuon_etx;   //!
   TBranch        *b_MET_RefMuon_ety;   //!
   TBranch        *b_MET_RefMuon_sumet;   //!
   TBranch        *b_MET_RefMuon_et;   //!
   TBranch        *b_MET_RefMuon_phi;   //!
   TBranch        *b_MET_RefTau_etx;   //!
   TBranch        *b_MET_RefTau_ety;   //!
   TBranch        *b_MET_RefTau_sumet;   //!
   TBranch        *b_MET_RefTau_et;   //!
   TBranch        *b_MET_RefTau_phi;   //!
   TBranch        *b_MET_Cryo_etx;   //!
   TBranch        *b_MET_Cryo_ety;   //!
   TBranch        *b_MET_Cryo_sumet;   //!
   TBranch        *b_MET_Cryo_et;   //!
   TBranch        *b_MET_Cryo_phi;   //!
   TBranch        *b_MET_CellOut_etx;   //!
   TBranch        *b_MET_CellOut_ety;   //!
   TBranch        *b_MET_CellOut_sumet;   //!
   TBranch        *b_MET_CellOut_et;   //!
   TBranch        *b_MET_CellOut_phi;   //!
   TBranch        *b_MET_Muid_etx;   //!
   TBranch        *b_MET_Muid_ety;   //!
   TBranch        *b_MET_Muid_sumet;   //!
   TBranch        *b_MET_Muid_et;   //!
   TBranch        *b_MET_Muid_phi;   //!
   TBranch        *b_MET_MuonBoyTrack_etx;   //!
   TBranch        *b_MET_MuonBoyTrack_ety;   //!
   TBranch        *b_MET_MuonBoyTrack_sumet;   //!
   TBranch        *b_MET_MuonBoyTrack_et;   //!
   TBranch        *b_MET_MuonBoyTrack_phi;   //!
   TBranch        *b_MET_MuonBoySpectro_etx;   //!
   TBranch        *b_MET_MuonBoySpectro_ety;   //!
   TBranch        *b_MET_MuonBoySpectro_sumet;   //!
   TBranch        *b_MET_MuonBoySpectro_et;   //!
   TBranch        *b_MET_MuonBoySpectro_phi;   //!
   TBranch        *b_MET_RefMuonTrack_etx;   //!
   TBranch        *b_MET_RefMuonTrack_ety;   //!
   TBranch        *b_MET_RefMuonTrack_sumet;   //!
   TBranch        *b_MET_RefMuonTrack_et;   //!
   TBranch        *b_MET_RefMuonTrack_phi;   //!
   TBranch        *b_MET_CryoCone_etx;   //!
   TBranch        *b_MET_CryoCone_ety;   //!
   TBranch        *b_MET_CryoCone_sumet;   //!
   TBranch        *b_MET_CryoCone_et;   //!
   TBranch        *b_MET_CryoCone_phi;   //!
   TBranch        *b_MET_Muon_etx;   //!
   TBranch        *b_MET_Muon_ety;   //!
   TBranch        *b_MET_Muon_sumet;   //!
   TBranch        *b_MET_Muon_et;   //!
   TBranch        *b_MET_Muon_phi;   //!
   TBranch        *b_MET_Final_etx;   //!
   TBranch        *b_MET_Final_ety;   //!
   TBranch        *b_MET_Final_sumet;   //!
   TBranch        *b_MET_Final_et;   //!
   TBranch        *b_MET_Final_phi;   //!
   TBranch        *b_MET_MuidTrack_etx;   //!
   TBranch        *b_MET_MuidTrack_ety;   //!
   TBranch        *b_MET_MuidTrack_sumet;   //!
   TBranch        *b_MET_MuidTrack_et;   //!
   TBranch        *b_MET_MuidTrack_phi;   //!
   TBranch        *b_MET_MuidSpectro_etx;   //!
   TBranch        *b_MET_MuidSpectro_ety;   //!
   TBranch        *b_MET_MuidSpectro_sumet;   //!
   TBranch        *b_MET_MuidSpectro_et;   //!
   TBranch        *b_MET_MuidSpectro_phi;   //!
   TBranch        *b_MET_MuonMuid_etx;   //!
   TBranch        *b_MET_MuonMuid_ety;   //!
   TBranch        *b_MET_MuonMuid_sumet;   //!
   TBranch        *b_MET_MuonMuid_et;   //!
   TBranch        *b_MET_MuonMuid_phi;   //!
   TBranch        *b_MET_TopoObj_etx;   //!
   TBranch        *b_MET_TopoObj_ety;   //!
   TBranch        *b_MET_TopoObj_sumet;   //!
   TBranch        *b_MET_TopoObj_et;   //!
   TBranch        *b_MET_TopoObj_phi;   //!
   TBranch        *b_MET_LocHadTopoObj_etx;   //!
   TBranch        *b_MET_LocHadTopoObj_ety;   //!
   TBranch        *b_MET_LocHadTopoObj_sumet;   //!
   TBranch        *b_MET_LocHadTopoObj_et;   //!
   TBranch        *b_MET_LocHadTopoObj_phi;   //!
   TBranch        *b_MET_Base_etx;   //!
   TBranch        *b_MET_Base_ety;   //!
   TBranch        *b_MET_Base_sumet;   //!
   TBranch        *b_MET_Base_et;   //!
   TBranch        *b_MET_Base_phi;   //!
   TBranch        *b_MET_Base_etx_PEMB;   //!
   TBranch        *b_MET_Base_ety_PEMB;   //!
   TBranch        *b_MET_Base_sumet_PEMB;   //!
   TBranch        *b_MET_Base_phi_PEMB;   //!
   TBranch        *b_MET_Base_etx_EMB;   //!
   TBranch        *b_MET_Base_ety_EMB;   //!
   TBranch        *b_MET_Base_sumet_EMB;   //!
   TBranch        *b_MET_Base_phi_EMB;   //!
   TBranch        *b_MET_Base_etx_PEMEC;   //!
   TBranch        *b_MET_Base_ety_PEMEC;   //!
   TBranch        *b_MET_Base_sumet_PEMEC;   //!
   TBranch        *b_MET_Base_phi_PEMEC;   //!
   TBranch        *b_MET_Base_etx_EME;   //!
   TBranch        *b_MET_Base_ety_EME;   //!
   TBranch        *b_MET_Base_sumet_EME;   //!
   TBranch        *b_MET_Base_phi_EME;   //!
   TBranch        *b_MET_Base_etx_TILE;   //!
   TBranch        *b_MET_Base_ety_TILE;   //!
   TBranch        *b_MET_Base_sumet_TILE;   //!
   TBranch        *b_MET_Base_phi_TILE;   //!
   TBranch        *b_MET_Base_etx_HEC;   //!
   TBranch        *b_MET_Base_ety_HEC;   //!
   TBranch        *b_MET_Base_sumet_HEC;   //!
   TBranch        *b_MET_Base_phi_HEC;   //!
   TBranch        *b_MET_Base_etx_FCAL;   //!
   TBranch        *b_MET_Base_ety_FCAL;   //!
   TBranch        *b_MET_Base_sumet_FCAL;   //!
   TBranch        *b_MET_Base_phi_FCAL;   //!
   TBranch        *b_MET_Base_nCell_PEMB;   //!
   TBranch        *b_MET_Base_nCell_EMB;   //!
   TBranch        *b_MET_Base_nCell_PEMEC;   //!
   TBranch        *b_MET_Base_nCell_EME;   //!
   TBranch        *b_MET_Base_nCell_TILE;   //!
   TBranch        *b_MET_Base_nCell_HEC;   //!
   TBranch        *b_MET_Base_nCell_FCAL;   //!
   TBranch        *b_MET_Base_etx_CentralReg;   //!
   TBranch        *b_MET_Base_ety_CentralReg;   //!
   TBranch        *b_MET_Base_sumet_CentralReg;   //!
   TBranch        *b_MET_Base_phi_CentralReg;   //!
   TBranch        *b_MET_Base_etx_EndcapRegion;   //!
   TBranch        *b_MET_Base_ety_EndcapRegion;   //!
   TBranch        *b_MET_Base_sumet_EndcapRegion;   //!
   TBranch        *b_MET_Base_phi_EndcapRegion;   //!
   TBranch        *b_MET_Base_etx_ForwardReg;   //!
   TBranch        *b_MET_Base_ety_ForwardReg;   //!
   TBranch        *b_MET_Base_sumet_ForwardReg;   //!
   TBranch        *b_MET_Base_phi_ForwardReg;   //!
   TBranch        *b_MET_Base_SUMET_EMFrac;   //!
   TBranch        *b_MET_Base0_etx;   //!
   TBranch        *b_MET_Base0_ety;   //!
   TBranch        *b_MET_Base0_sumet;   //!
   TBranch        *b_MET_Base0_et;   //!
   TBranch        *b_MET_Base0_phi;   //!
   TBranch        *b_MET_Base0_etx_PEMB;   //!
   TBranch        *b_MET_Base0_ety_PEMB;   //!
   TBranch        *b_MET_Base0_sumet_PEMB;   //!
   TBranch        *b_MET_Base0_phi_PEMB;   //!
   TBranch        *b_MET_Base0_etx_EMB;   //!
   TBranch        *b_MET_Base0_ety_EMB;   //!
   TBranch        *b_MET_Base0_sumet_EMB;   //!
   TBranch        *b_MET_Base0_phi_EMB;   //!
   TBranch        *b_MET_Base0_etx_PEMEC;   //!
   TBranch        *b_MET_Base0_ety_PEMEC;   //!
   TBranch        *b_MET_Base0_sumet_PEMEC;   //!
   TBranch        *b_MET_Base0_phi_PEMEC;   //!
   TBranch        *b_MET_Base0_etx_EME;   //!
   TBranch        *b_MET_Base0_ety_EME;   //!
   TBranch        *b_MET_Base0_sumet_EME;   //!
   TBranch        *b_MET_Base0_phi_EME;   //!
   TBranch        *b_MET_Base0_etx_TILE;   //!
   TBranch        *b_MET_Base0_ety_TILE;   //!
   TBranch        *b_MET_Base0_sumet_TILE;   //!
   TBranch        *b_MET_Base0_phi_TILE;   //!
   TBranch        *b_MET_Base0_etx_HEC;   //!
   TBranch        *b_MET_Base0_ety_HEC;   //!
   TBranch        *b_MET_Base0_sumet_HEC;   //!
   TBranch        *b_MET_Base0_phi_HEC;   //!
   TBranch        *b_MET_Base0_etx_FCAL;   //!
   TBranch        *b_MET_Base0_ety_FCAL;   //!
   TBranch        *b_MET_Base0_sumet_FCAL;   //!
   TBranch        *b_MET_Base0_phi_FCAL;   //!
   TBranch        *b_MET_Base0_nCell_PEMB;   //!
   TBranch        *b_MET_Base0_nCell_EMB;   //!
   TBranch        *b_MET_Base0_nCell_PEMEC;   //!
   TBranch        *b_MET_Base0_nCell_EME;   //!
   TBranch        *b_MET_Base0_nCell_TILE;   //!
   TBranch        *b_MET_Base0_nCell_HEC;   //!
   TBranch        *b_MET_Base0_nCell_FCAL;   //!
   TBranch        *b_MET_Base0_etx_CentralReg;   //!
   TBranch        *b_MET_Base0_ety_CentralReg;   //!
   TBranch        *b_MET_Base0_sumet_CentralReg;   //!
   TBranch        *b_MET_Base0_phi_CentralReg;   //!
   TBranch        *b_MET_Base0_etx_EndcapRegion;   //!
   TBranch        *b_MET_Base0_ety_EndcapRegion;   //!
   TBranch        *b_MET_Base0_sumet_EndcapRegion;   //!
   TBranch        *b_MET_Base0_phi_EndcapRegion;   //!
   TBranch        *b_MET_Base0_etx_ForwardReg;   //!
   TBranch        *b_MET_Base0_ety_ForwardReg;   //!
   TBranch        *b_MET_Base0_sumet_ForwardReg;   //!
   TBranch        *b_MET_Base0_phi_ForwardReg;   //!
   TBranch        *b_MET_Calib_etx;   //!
   TBranch        *b_MET_Calib_ety;   //!
   TBranch        *b_MET_Calib_sumet;   //!
   TBranch        *b_MET_Calib_et;   //!
   TBranch        *b_MET_Calib_phi;   //!
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
   TBranch        *b_MET_Topo_etx;   //!
   TBranch        *b_MET_Topo_ety;   //!
   TBranch        *b_MET_Topo_sumet;   //!
   TBranch        *b_MET_Topo_et;   //!
   TBranch        *b_MET_Topo_phi;   //!
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
   TBranch        *b_MET_CorrTopo_etx;   //!
   TBranch        *b_MET_CorrTopo_ety;   //!
   TBranch        *b_MET_CorrTopo_sumet;   //!
   TBranch        *b_MET_CorrTopo_et;   //!
   TBranch        *b_MET_CorrTopo_phi;   //!
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
   TBranch        *b_MET_LocHadTopo_etx;   //!
   TBranch        *b_MET_LocHadTopo_ety;   //!
   TBranch        *b_MET_LocHadTopo_sumet;   //!
   TBranch        *b_MET_LocHadTopo_et;   //!
   TBranch        *b_MET_LocHadTopo_phi;   //!
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
   TBranch        *b_MET_JetsInfo_JetPtWeightedEventEMFraction;   //!
   TBranch        *b_MET_JetsInfo_JetPtWeightedNumAssociatedTracks;   //!
   TBranch        *b_MET_JetsInfo_JetPtWeightedSize;   //!
   TBranch        *b_MET_JetsInfo_LeadingJetEt;   //!
   TBranch        *b_MET_JetsInfo_LeadingJetEta;   //!
   TBranch        *b_cl_n;   //!
   TBranch        *b_cl_E;   //!
   TBranch        *b_cl_pt;   //!
   TBranch        *b_cl_m;   //!
   TBranch        *b_cl_eta;   //!
   TBranch        *b_cl_phi;   //!
   TBranch        *b_cl_E_em;   //!
   TBranch        *b_cl_E_had;   //!
   TBranch        *b_cl_firstEdens;   //!
   TBranch        *b_cl_cellmaxfrac;   //!
   TBranch        *b_cl_longitudinal;   //!
   TBranch        *b_cl_secondlambda;   //!
   TBranch        *b_cl_lateral;   //!
   TBranch        *b_cl_secondR;   //!
   TBranch        *b_cl_centerlambda;   //!
   TBranch        *b_cl_deltaTheta;   //!
   TBranch        *b_cl_deltaPhi;   //!
   TBranch        *b_cl_time;   //!
   TBranch        *b_emcl_n;   //!
   TBranch        *b_emcl_E;   //!
   TBranch        *b_emcl_pt;   //!
   TBranch        *b_emcl_m;   //!
   TBranch        *b_emcl_eta;   //!
   TBranch        *b_emcl_phi;   //!
   TBranch        *b_emcl_E_em;   //!
   TBranch        *b_emcl_E_had;   //!
   TBranch        *b_emcl_firstEdens;   //!
   TBranch        *b_emcl_cellmaxfrac;   //!
   TBranch        *b_emcl_longitudinal;   //!
   TBranch        *b_emcl_secondlambda;   //!
   TBranch        *b_emcl_lateral;   //!
   TBranch        *b_emcl_secondR;   //!
   TBranch        *b_emcl_centerlambda;   //!
   TBranch        *b_emcl_deltaTheta;   //!
   TBranch        *b_emcl_deltaPhi;   //!
   TBranch        *b_emcl_time;   //!
   TBranch        *b_emcl_E_PreSamplerB;   //!
   TBranch        *b_emcl_E_EMB1;   //!
   TBranch        *b_emcl_E_EMB2;   //!
   TBranch        *b_emcl_E_EMB3;   //!
   TBranch        *b_emcl_E_PreSamplerE;   //!
   TBranch        *b_emcl_E_EME1;   //!
   TBranch        *b_emcl_E_EME2;   //!
   TBranch        *b_emcl_E_EME3;   //!
   TBranch        *b_emcl_E_HEC0;   //!
   TBranch        *b_emcl_E_HEC1;   //!
   TBranch        *b_emcl_E_HEC2;   //!
   TBranch        *b_emcl_E_HEC3;   //!
   TBranch        *b_emcl_E_TileBar0;   //!
   TBranch        *b_emcl_E_TileBar1;   //!
   TBranch        *b_emcl_E_TileBar2;   //!
   TBranch        *b_emcl_E_TileGap1;   //!
   TBranch        *b_emcl_E_TileGap2;   //!
   TBranch        *b_emcl_E_TileGap3;   //!
   TBranch        *b_emcl_E_TileExt0;   //!
   TBranch        *b_emcl_E_TileExt1;   //!
   TBranch        *b_emcl_E_TileExt2;   //!
   TBranch        *b_emcl_E_FCAL0;   //!
   TBranch        *b_emcl_E_FCAL1;   //!
   TBranch        *b_emcl_E_FCAL2;   //!
   TBranch        *b_trk_n;   //!
   TBranch        *b_trk_d0;   //!
   TBranch        *b_trk_z0;   //!
   TBranch        *b_trk_phi;   //!
   TBranch        *b_trk_theta;   //!
   TBranch        *b_trk_qoverp;   //!
   TBranch        *b_trk_pt;   //!
   TBranch        *b_trk_eta;   //!
   TBranch        *b_trk_err_d0;   //!
   TBranch        *b_trk_err_z0;   //!
   TBranch        *b_trk_err_phi;   //!
   TBranch        *b_trk_err_theta;   //!
   TBranch        *b_trk_err_qoverp;   //!
   TBranch        *b_trk_cov_d0;   //!
   TBranch        *b_trk_cov_z0;   //!
   TBranch        *b_trk_cov_phi;   //!
   TBranch        *b_trk_cov_theta;   //!
   TBranch        *b_trk_cov_qoverp;   //!
   TBranch        *b_trk_cov_d0_z0;   //!
   TBranch        *b_trk_cov_d0_phi;   //!
   TBranch        *b_trk_cov_d0_theta;   //!
   TBranch        *b_trk_cov_d0_qoverp;   //!
   TBranch        *b_trk_cov_z0_phi;   //!
   TBranch        *b_trk_cov_z0_theta;   //!
   TBranch        *b_trk_cov_z0_qoverp;   //!
   TBranch        *b_trk_cov_phi_theta;   //!
   TBranch        *b_trk_cov_phi_qoverp;   //!
   TBranch        *b_trk_cov_theta_qoverp;   //!
   TBranch        *b_trk_blayerPrediction_expectHit;   //!
   TBranch        *b_trk_blayerPrediction_x;   //!
   TBranch        *b_trk_blayerPrediction_y;   //!
   TBranch        *b_trk_blayerPrediction_z;   //!
   TBranch        *b_trk_blayerPrediction_locX;   //!
   TBranch        *b_trk_blayerPrediction_locY;   //!
   TBranch        *b_trk_blayerPrediction_err_locX;   //!
   TBranch        *b_trk_blayerPrediction_err_locY;   //!
   TBranch        *b_trk_blayerPrediction_etaDistToEdge;   //!
   TBranch        *b_trk_blayerPrediction_phiDistToEdge;   //!
   TBranch        *b_trk_blayerPrediction_detElementId;   //!
   TBranch        *b_trk_blayerPrediction_row;   //!
   TBranch        *b_trk_blayerPrediction_col;   //!
   TBranch        *b_trk_blayerPrediction_type;   //!
   TBranch        *b_trk_d0_wrtPV;   //!
   TBranch        *b_trk_z0_wrtPV;   //!
   TBranch        *b_trk_phi_wrtPV;   //!
   TBranch        *b_trk_theta_wrtPV;   //!
   TBranch        *b_trk_qoverp_wrtPV;   //!
   TBranch        *b_trk_chi2;   //!
   TBranch        *b_trk_ndof;   //!
   TBranch        *b_trk_nBLHits;   //!
   TBranch        *b_trk_nPixHits;   //!
   TBranch        *b_trk_nSCTHits;   //!
   TBranch        *b_trk_nTRTHits;   //!
   TBranch        *b_trk_nPixHoles;   //!
   TBranch        *b_trk_nSCTHoles;   //!
   TBranch        *b_trk_nMDTHits;   //!
   TBranch        *b_trk_nCSCEtaHits;   //!
   TBranch        *b_trk_nCSCPhiHits;   //!
   TBranch        *b_trk_nRPCEtaHits;   //!
   TBranch        *b_trk_nRPCPhiHits;   //!
   TBranch        *b_trk_nTGCEtaHits;   //!
   TBranch        *b_trk_nTGCPhiHits;   //!
   TBranch        *b_trk_nHits;   //!
   TBranch        *b_trk_nHoles;   //!
   TBranch        *b_trk_hitPattern;   //!
   TBranch        *b_trk_TRTHighTHitsRatio;   //!
   TBranch        *b_trk_pixeldEdx;   //!
   TBranch        *b_trk_fitter;   //!
   TBranch        *b_trk_patternReco1;   //!
   TBranch        *b_trk_patternReco2;   //!
   TBranch        *b_trk_seedFinder;   //!
   TBranch        *b_mb_n;   //!
   TBranch        *b_mb_E;   //!
   TBranch        *b_mb_eta;   //!
   TBranch        *b_mb_phi;   //!
   TBranch        *b_mb_time;   //!
   TBranch        *b_mb_quality;   //!
   TBranch        *b_mb_type;   //!
   TBranch        *b_mb_module;   //!
   TBranch        *b_mb_channel;   //!
   TBranch        *b_mbtime_timeDiff;   //!
   TBranch        *b_mbtime_timeA;   //!
   TBranch        *b_mbtime_timeC;   //!
   TBranch        *b_mbtime_countA;   //!
   TBranch        *b_mbtime_countC;   //!
   TBranch        *b_L1_MBTS_1;   //!
   TBranch        *b_L1_MBTS_1_1;   //!
   TBranch        *b_L1_MBTS_1_1_EMPTY;   //!
   TBranch        *b_L1_MBTS_1_1_UNPAIRED_ISO;   //!
   TBranch        *b_L1_MBTS_1_EMPTY;   //!
   TBranch        *b_L1_MBTS_1_UNPAIRED_ISO;   //!
   TBranch        *b_L1_MBTS_2;   //!
   TBranch        *b_L1_MBTS_2_EMPTY;   //!
   TBranch        *b_L1_MBTS_2_UNPAIRED_ISO;   //!
   TBranch        *b_L1_MBTS_2_UNPAIRED_NONISO;   //!
   TBranch        *b_L1_MBTS_4_4;   //!
   TBranch        *b_L1_MBTS_4_4_UNPAIRED_ISO;   //!
   TBranch        *b_collcand_passMBTSTime;   //!
   TBranch        *b_collcand_passCaloTime;   //!
   TBranch        *b_collcand_passTrigger;   //!
   TBranch        *b_collcand_pass;   //!
   TBranch        *b_vxp_n;   //!
   TBranch        *b_vxp_x;   //!
   TBranch        *b_vxp_y;   //!
   TBranch        *b_vxp_z;   //!
   TBranch        *b_vxp_chi2;   //!
   TBranch        *b_vxp_ndof;   //!
   TBranch        *b_vxp_err_x;   //!
   TBranch        *b_vxp_err_y;   //!
   TBranch        *b_vxp_err_z;   //!
   TBranch        *b_vxp_px;   //!
   TBranch        *b_vxp_py;   //!
   TBranch        *b_vxp_pz;   //!
   TBranch        *b_vxp_E;   //!
   TBranch        *b_vxp_m;   //!
   TBranch        *b_vxp_nTracks;   //!
   TBranch        *b_vxp_sumPt;   //!
   TBranch        *b_vxp_type;   //!
   TBranch        *b_vxp_trk_n;   //!
   TBranch        *b_vxp_trk_chi2;   //!
   TBranch        *b_vxp_trk_d0;   //!
   TBranch        *b_vxp_trk_z0;   //!
   TBranch        *b_vxp_trk_unbiased_d0;   //!
   TBranch        *b_vxp_trk_unbiased_z0;   //!
   TBranch        *b_vxp_trk_err_unbiased_d0;   //!
   TBranch        *b_vxp_trk_err_unbiased_z0;   //!
   TBranch        *b_vxp_trk_phi;   //!
   TBranch        *b_vxp_trk_theta;   //!
   TBranch        *b_vxp_trk_weight;   //!
   TBranch        *b_vxp_trk_index;   //!
   TBranch        *b_trig_L1_emtau_n;   //!
   TBranch        *b_trig_L1_emtau_eta;   //!
   TBranch        *b_trig_L1_emtau_phi;   //!
   TBranch        *b_trig_L1_emtau_thrNames;   //!
   TBranch        *b_trig_L1_emtau_thrValues;   //!
   TBranch        *b_trig_L1_emtau_core;   //!
   TBranch        *b_trig_L1_emtau_EMClus;   //!
   TBranch        *b_trig_L1_emtau_tauClus;   //!
   TBranch        *b_trig_L1_emtau_EMIsol;   //!
   TBranch        *b_trig_L1_emtau_hadIsol;   //!
   TBranch        *b_trig_L1_emtau_hadCore;   //!
   TBranch        *b_trig_L1_emtau_thrPattern;   //!
   TBranch        *b_trig_L1_emtau_L1_2EM10;   //!
   TBranch        *b_trig_L1_emtau_L1_2EM14;   //!
   TBranch        *b_trig_L1_emtau_L1_2EM2;   //!
   TBranch        *b_trig_L1_emtau_L1_2EM3;   //!
   TBranch        *b_trig_L1_emtau_L1_2EM5;   //!
   TBranch        *b_trig_L1_emtau_L1_EM10;   //!
   TBranch        *b_trig_L1_emtau_L1_EM10I;   //!
   TBranch        *b_trig_L1_emtau_L1_EM14;   //!
   TBranch        *b_trig_L1_emtau_L1_EM14I;   //!
   TBranch        *b_trig_L1_emtau_L1_EM14_XE10;   //!
   TBranch        *b_trig_L1_emtau_L1_EM14_XE15;   //!
   TBranch        *b_trig_L1_emtau_L1_EM2;   //!
   TBranch        *b_trig_L1_emtau_L1_EM2_UNPAIRED_ISO;   //!
   TBranch        *b_trig_L1_emtau_L1_EM2_UNPAIRED_NONISO;   //!
   TBranch        *b_trig_L1_emtau_L1_EM3;   //!
   TBranch        *b_trig_L1_emtau_L1_EM3_EMPTY;   //!
   TBranch        *b_trig_L1_emtau_L1_EM3_FIRSTEMPTY;   //!
   TBranch        *b_trig_L1_emtau_L1_EM3_MV;   //!
   TBranch        *b_trig_L1_emtau_L1_EM5;   //!
   TBranch        *b_trig_L1_emtau_L1_EM5_MU10;   //!
   TBranch        *b_trig_L1_emtau_L1_EM5_MU6;   //!
   TBranch        *b_trig_L1_emtau_L1_EM85;   //!
   TBranch        *b_trig_L2_emcl_n;   //!
   TBranch        *b_trig_L2_emcl_quality;   //!
   TBranch        *b_trig_L2_emcl_E;   //!
   TBranch        *b_trig_L2_emcl_Et;   //!
   TBranch        *b_trig_L2_emcl_eta;   //!
   TBranch        *b_trig_L2_emcl_phi;   //!
   TBranch        *b_trig_L2_emcl_E237;   //!
   TBranch        *b_trig_L2_emcl_E277;   //!
   TBranch        *b_trig_L2_emcl_fracs1;   //!
   TBranch        *b_trig_L2_emcl_weta2;   //!
   TBranch        *b_trig_L2_emcl_Ehad1;   //!
   TBranch        *b_trig_L2_emcl_eta1;   //!
   TBranch        *b_trig_L2_emcl_emaxs1;   //!
   TBranch        *b_trig_L2_emcl_e2tsts1;   //!
   TBranch        *b_trig_L2_trk_idscan_eGamma_n;   //!
   TBranch        *b_trig_L2_trk_idscan_eGamma_algorithmId;   //!
   TBranch        *b_trig_L2_trk_idscan_eGamma_trackStatus;   //!
   TBranch        *b_trig_L2_trk_idscan_eGamma_chi2Ndof;   //!
   TBranch        *b_trig_L2_trk_idscan_eGamma_nStrawHits;   //!
   TBranch        *b_trig_L2_trk_idscan_eGamma_nHighThrHits;   //!
   TBranch        *b_trig_L2_trk_idscan_eGamma_nPixelSpacePoints;   //!
   TBranch        *b_trig_L2_trk_idscan_eGamma_nSCT_SpacePoints;   //!
   TBranch        *b_trig_L2_trk_idscan_eGamma_a0;   //!
   TBranch        *b_trig_L2_trk_idscan_eGamma_z0;   //!
   TBranch        *b_trig_L2_trk_idscan_eGamma_phi0;   //!
   TBranch        *b_trig_L2_trk_idscan_eGamma_eta;   //!
   TBranch        *b_trig_L2_trk_idscan_eGamma_pt;   //!
   TBranch        *b_trig_L2_trk_sitrack_eGamma_n;   //!
   TBranch        *b_trig_L2_trk_sitrack_eGamma_algorithmId;   //!
   TBranch        *b_trig_L2_trk_sitrack_eGamma_trackStatus;   //!
   TBranch        *b_trig_L2_trk_sitrack_eGamma_chi2Ndof;   //!
   TBranch        *b_trig_L2_trk_sitrack_eGamma_nStrawHits;   //!
   TBranch        *b_trig_L2_trk_sitrack_eGamma_nHighThrHits;   //!
   TBranch        *b_trig_L2_trk_sitrack_eGamma_nPixelSpacePoints;   //!
   TBranch        *b_trig_L2_trk_sitrack_eGamma_nSCT_SpacePoints;   //!
   TBranch        *b_trig_L2_trk_sitrack_eGamma_a0;   //!
   TBranch        *b_trig_L2_trk_sitrack_eGamma_z0;   //!
   TBranch        *b_trig_L2_trk_sitrack_eGamma_phi0;   //!
   TBranch        *b_trig_L2_trk_sitrack_eGamma_eta;   //!
   TBranch        *b_trig_L2_trk_sitrack_eGamma_pt;   //!
   TBranch        *b_trig_L2_el_n;   //!
   TBranch        *b_trig_L2_el_E;   //!
   TBranch        *b_trig_L2_el_Et;   //!
   TBranch        *b_trig_L2_el_pt;   //!
   TBranch        *b_trig_L2_el_eta;   //!
   TBranch        *b_trig_L2_el_phi;   //!
   TBranch        *b_trig_L2_el_RoIWord;   //!
   TBranch        *b_trig_L2_el_zvertex;   //!
   TBranch        *b_trig_L2_el_charge;   //!
   TBranch        *b_trig_L2_el_trackAlgo;   //!
   TBranch        *b_trig_L2_el_TRTHighTHitsRatio;   //!
   TBranch        *b_trig_L2_el_deltaeta1;   //!
   TBranch        *b_trig_L2_el_deltaphi2;   //!
   TBranch        *b_trig_L2_el_EtOverPt;   //!
   TBranch        *b_trig_L2_el_reta;   //!
   TBranch        *b_trig_L2_el_Eratio;   //!
   TBranch        *b_trig_L2_el_Ethad1;   //!
   TBranch        *b_trig_L2_el_L2_2e10_loose;   //!
   TBranch        *b_trig_L2_el_L2_2e10_medium;   //!
   TBranch        *b_trig_L2_el_L2_2e15_loose;   //!
   TBranch        *b_trig_L2_el_L2_2e3_loose;   //!
   TBranch        *b_trig_L2_el_L2_2e3_loose_SiTrk;   //!
   TBranch        *b_trig_L2_el_L2_2e3_loose_TRT;   //!
   TBranch        *b_trig_L2_el_L2_2e3_medium;   //!
   TBranch        *b_trig_L2_el_L2_2e3_medium_SiTrk;   //!
   TBranch        *b_trig_L2_el_L2_2e3_medium_TRT;   //!
   TBranch        *b_trig_L2_el_L2_2e3_tight;   //!
   TBranch        *b_trig_L2_el_L2_2e5_medium;   //!
   TBranch        *b_trig_L2_el_L2_2e5_medium_SiTrk;   //!
   TBranch        *b_trig_L2_el_L2_2e5_medium_TRT;   //!
   TBranch        *b_trig_L2_el_L2_2e5_tight;   //!
   TBranch        *b_trig_L2_el_L2_e10_NoCut;   //!
   TBranch        *b_trig_L2_el_L2_e10_loose;   //!
   TBranch        *b_trig_L2_el_L2_e10_loose_mu10;   //!
   TBranch        *b_trig_L2_el_L2_e10_loose_mu6;   //!
   TBranch        *b_trig_L2_el_L2_e10_medium;   //!
   TBranch        *b_trig_L2_el_L2_e10_medium_IDTrkNoCut;   //!
   TBranch        *b_trig_L2_el_L2_e10_medium_SiTrk;   //!
   TBranch        *b_trig_L2_el_L2_e10_medium_TRT;   //!
   TBranch        *b_trig_L2_el_L2_e10_tight;   //!
   TBranch        *b_trig_L2_el_L2_e15_loose;   //!
   TBranch        *b_trig_L2_el_L2_e15_loose_IDTrkNoCut;   //!
   TBranch        *b_trig_L2_el_L2_e15_medium;   //!
   TBranch        *b_trig_L2_el_L2_e15_medium_SiTrk;   //!
   TBranch        *b_trig_L2_el_L2_e15_medium_TRT;   //!
   TBranch        *b_trig_L2_el_L2_e15_tight;   //!
   TBranch        *b_trig_L2_el_L2_e18_medium;   //!
   TBranch        *b_trig_L2_el_L2_e20_loose;   //!
   TBranch        *b_trig_L2_el_L2_e20_loose_IDTrkNoCut;   //!
   TBranch        *b_trig_L2_el_L2_e20_loose_passEF;   //!
   TBranch        *b_trig_L2_el_L2_e20_loose_passL2;   //!
   TBranch        *b_trig_L2_el_L2_e20_loose_xe20_noMu;   //!
   TBranch        *b_trig_L2_el_L2_e20_loose_xe30_noMu;   //!
   TBranch        *b_trig_L2_el_L2_e20_medium;   //!
   TBranch        *b_trig_L2_el_L2_e25_loose;   //!
   TBranch        *b_trig_L2_el_L2_e30_loose;   //!
   TBranch        *b_trig_L2_el_L2_e3_loose;   //!
   TBranch        *b_trig_L2_el_L2_e3_loose_SiTrk;   //!
   TBranch        *b_trig_L2_el_L2_e3_loose_TRT;   //!
   TBranch        *b_trig_L2_el_L2_e3_medium;   //!
   TBranch        *b_trig_L2_el_L2_e3_medium_SiTrk;   //!
   TBranch        *b_trig_L2_el_L2_e3_medium_TRT;   //!
   TBranch        *b_trig_L2_el_L2_e5_NoCut_firstempty;   //!
   TBranch        *b_trig_L2_el_L2_e5_medium;   //!
   TBranch        *b_trig_L2_el_L2_e5_medium_MV;   //!
   TBranch        *b_trig_L2_el_L2_e5_medium_SiTrk;   //!
   TBranch        *b_trig_L2_el_L2_e5_medium_TRT;   //!
   TBranch        *b_trig_L2_el_L2_e5_medium_mu4;   //!
   TBranch        *b_trig_L2_el_L2_e5_tight;   //!
   TBranch        *b_trig_L2_el_L2_e5_tight_SiTrk;   //!
   TBranch        *b_trig_L2_el_L2_e5_tight_TRT;   //!
   TBranch        *b_trig_L2_el_L2_e5_tight_e5_NoCut;   //!
   TBranch        *b_trig_L2_el_L2_eb_physics;   //!
   TBranch        *b_trig_L2_el_L2_eb_physics_empty;   //!
   TBranch        *b_trig_L2_el_L2_eb_physics_firstempty;   //!
   TBranch        *b_trig_L2_el_L2_eb_physics_unpaired_iso;   //!
   TBranch        *b_trig_L2_el_L2_eb_physics_unpaired_noniso;   //!
   TBranch        *b_trig_L2_el_L2_eb_random;   //!
   TBranch        *b_trig_L2_el_L2_eb_random_empty;   //!
   TBranch        *b_trig_L2_el_L2_eb_random_firstempty;   //!
   TBranch        *b_trig_L2_el_L2_eb_random_unpaired_iso;   //!
   TBranch        *b_trig_L2_el_L2_em105_passHLT;   //!
   TBranch        *b_trig_L2_el_L2_em3_empty_larcalib;   //!
   TBranch        *b_trig_L2_ph_n;   //!
   TBranch        *b_trig_L2_ph_E;   //!
   TBranch        *b_trig_L2_ph_Et;   //!
   TBranch        *b_trig_L2_ph_pt;   //!
   TBranch        *b_trig_L2_ph_eta;   //!
   TBranch        *b_trig_L2_ph_phi;   //!
   TBranch        *b_trig_L2_ph_RoIWord;   //!
   TBranch        *b_trig_L2_ph_HadEt1;   //!
   TBranch        *b_trig_L2_ph_Eratio;   //!
   TBranch        *b_trig_L2_ph_Reta;   //!
   TBranch        *b_trig_L2_ph_dPhi;   //!
   TBranch        *b_trig_L2_ph_dEta;   //!
   TBranch        *b_trig_L2_ph_F1;   //!
   TBranch        *b_trig_L2_ph_L2_2g10_loose;   //!
   TBranch        *b_trig_L2_ph_L2_2g15_loose;   //!
   TBranch        *b_trig_L2_ph_L2_2g5_loose;   //!
   TBranch        *b_trig_L2_ph_L2_2g7_loose;   //!
   TBranch        *b_trig_L2_ph_L2_g10_loose;   //!
   TBranch        *b_trig_L2_ph_L2_g11_etcut;   //!
   TBranch        *b_trig_L2_ph_L2_g15_loose;   //!
   TBranch        *b_trig_L2_ph_L2_g17_etcut;   //!
   TBranch        *b_trig_L2_ph_L2_g17_etcut_EFxe20_noMu;   //!
   TBranch        *b_trig_L2_ph_L2_g17_etcut_EFxe30_noMu;   //!
   TBranch        *b_trig_L2_ph_L2_g20_loose;   //!
   TBranch        *b_trig_L2_ph_L2_g20_loose_xe20_noMu;   //!
   TBranch        *b_trig_L2_ph_L2_g20_loose_xe30_noMu;   //!
   TBranch        *b_trig_L2_ph_L2_g20_tight;   //!
   TBranch        *b_trig_L2_ph_L2_g25_loose_xe30_noMu;   //!
   TBranch        *b_trig_L2_ph_L2_g30_loose;   //!
   TBranch        *b_trig_L2_ph_L2_g30_tight;   //!
   TBranch        *b_trig_L2_ph_L2_g3_NoCut_unpaired_iso;   //!
   TBranch        *b_trig_L2_ph_L2_g3_NoCut_unpaired_noniso;   //!
   TBranch        *b_trig_L2_ph_L2_g40_loose;   //!
   TBranch        *b_trig_L2_ph_L2_g40_tight;   //!
   TBranch        *b_trig_L2_ph_L2_g50_loose;   //!
   TBranch        *b_trig_L2_ph_L2_g5_NoCut_cosmic;   //!
   TBranch        *b_trig_L2_ph_L2_g5_loose;   //!
   TBranch        *b_trig_L2_ph_L2_g7_loose;   //!
   TBranch        *b_trig_EF_emcl_n;   //!
   TBranch        *b_trig_EF_emcl_E;   //!
   TBranch        *b_trig_EF_emcl_pt;   //!
   TBranch        *b_trig_EF_emcl_m;   //!
   TBranch        *b_trig_EF_emcl_eta;   //!
   TBranch        *b_trig_EF_emcl_phi;   //!
   TBranch        *b_trig_EF_emcl_E_em;   //!
   TBranch        *b_trig_EF_emcl_E_had;   //!
   TBranch        *b_trig_EF_emcl_firstEdens;   //!
   TBranch        *b_trig_EF_emcl_cellmaxfrac;   //!
   TBranch        *b_trig_EF_emcl_longitudinal;   //!
   TBranch        *b_trig_EF_emcl_secondlambda;   //!
   TBranch        *b_trig_EF_emcl_lateral;   //!
   TBranch        *b_trig_EF_emcl_secondR;   //!
   TBranch        *b_trig_EF_emcl_centerlambda;   //!
   TBranch        *b_trig_EF_emcl_deltaTheta;   //!
   TBranch        *b_trig_EF_emcl_deltaPhi;   //!
   TBranch        *b_trig_EF_emcl_time;   //!
   TBranch        *b_trig_EF_emcl_slw_n;   //!
   TBranch        *b_trig_EF_emcl_slw_E;   //!
   TBranch        *b_trig_EF_emcl_slw_pt;   //!
   TBranch        *b_trig_EF_emcl_slw_m;   //!
   TBranch        *b_trig_EF_emcl_slw_eta;   //!
   TBranch        *b_trig_EF_emcl_slw_phi;   //!
   TBranch        *b_trig_EF_emcl_slw_E_em;   //!
   TBranch        *b_trig_EF_emcl_slw_E_had;   //!
   TBranch        *b_trig_EF_emcl_slw_firstEdens;   //!
   TBranch        *b_trig_EF_emcl_slw_cellmaxfrac;   //!
   TBranch        *b_trig_EF_emcl_slw_longitudinal;   //!
   TBranch        *b_trig_EF_emcl_slw_secondlambda;   //!
   TBranch        *b_trig_EF_emcl_slw_lateral;   //!
   TBranch        *b_trig_EF_emcl_slw_secondR;   //!
   TBranch        *b_trig_EF_emcl_slw_centerlambda;   //!
   TBranch        *b_trig_EF_emcl_slw_deltaTheta;   //!
   TBranch        *b_trig_EF_emcl_slw_deltaPhi;   //!
   TBranch        *b_trig_EF_emcl_slw_time;   //!
   TBranch        *b_trig_EF_el_n;   //!
   TBranch        *b_trig_EF_el_E;   //!
   TBranch        *b_trig_EF_el_Et;   //!
   TBranch        *b_trig_EF_el_pt;   //!
   TBranch        *b_trig_EF_el_m;   //!
   TBranch        *b_trig_EF_el_eta;   //!
   TBranch        *b_trig_EF_el_phi;   //!
   TBranch        *b_trig_EF_el_px;   //!
   TBranch        *b_trig_EF_el_py;   //!
   TBranch        *b_trig_EF_el_pz;   //!
   TBranch        *b_trig_EF_el_charge;   //!
   TBranch        *b_trig_EF_el_author;   //!
   TBranch        *b_trig_EF_el_isEM;   //!
   TBranch        *b_trig_EF_el_loose;   //!
   TBranch        *b_trig_EF_el_medium;   //!
   TBranch        *b_trig_EF_el_mediumIso;   //!
   TBranch        *b_trig_EF_el_tight;   //!
   TBranch        *b_trig_EF_el_tightIso;   //!
   TBranch        *b_trig_EF_el_Ethad;   //!
   TBranch        *b_trig_EF_el_Ethad1;   //!
   TBranch        *b_trig_EF_el_f1;   //!
   TBranch        *b_trig_EF_el_f1core;   //!
   TBranch        *b_trig_EF_el_Emins1;   //!
   TBranch        *b_trig_EF_el_fside;   //!
   TBranch        *b_trig_EF_el_Emax2;   //!
   TBranch        *b_trig_EF_el_ws3;   //!
   TBranch        *b_trig_EF_el_wstot;   //!
   TBranch        *b_trig_EF_el_emaxs1;   //!
   TBranch        *b_trig_EF_el_deltaEs;   //!
   TBranch        *b_trig_EF_el_E233;   //!
   TBranch        *b_trig_EF_el_E237;   //!
   TBranch        *b_trig_EF_el_E277;   //!
   TBranch        *b_trig_EF_el_weta2;   //!
   TBranch        *b_trig_EF_el_f3;   //!
   TBranch        *b_trig_EF_el_f3core;   //!
   TBranch        *b_trig_EF_el_rphiallcalo;   //!
   TBranch        *b_trig_EF_el_Etcone45;   //!
   TBranch        *b_trig_EF_el_Etcone20;   //!
   TBranch        *b_trig_EF_el_Etcone30;   //!
   TBranch        *b_trig_EF_el_Etcone40;   //!
   TBranch        *b_trig_EF_el_pos7;   //!
   TBranch        *b_trig_EF_el_etacorrmag;   //!
   TBranch        *b_trig_EF_el_deltaeta1;   //!
   TBranch        *b_trig_EF_el_deltaeta2;   //!
   TBranch        *b_trig_EF_el_deltaphi2;   //!
   TBranch        *b_trig_EF_el_reta;   //!
   TBranch        *b_trig_EF_el_rphi;   //!
   TBranch        *b_trig_EF_el_EF_2e10_loose;   //!
   TBranch        *b_trig_EF_el_EF_2e10_medium;   //!
   TBranch        *b_trig_EF_el_EF_2e15_loose;   //!
   TBranch        *b_trig_EF_el_EF_2e3_loose;   //!
   TBranch        *b_trig_EF_el_EF_2e3_loose_SiTrk;   //!
   TBranch        *b_trig_EF_el_EF_2e3_loose_TRT;   //!
   TBranch        *b_trig_EF_el_EF_2e3_medium;   //!
   TBranch        *b_trig_EF_el_EF_2e3_medium_SiTrk;   //!
   TBranch        *b_trig_EF_el_EF_2e3_medium_TRT;   //!
   TBranch        *b_trig_EF_el_EF_2e3_tight;   //!
   TBranch        *b_trig_EF_el_EF_2e5_medium;   //!
   TBranch        *b_trig_EF_el_EF_2e5_medium_SiTrk;   //!
   TBranch        *b_trig_EF_el_EF_2e5_medium_TRT;   //!
   TBranch        *b_trig_EF_el_EF_2e5_tight;   //!
   TBranch        *b_trig_EF_el_EF_e10_NoCut;   //!
   TBranch        *b_trig_EF_el_EF_e10_loose;   //!
   TBranch        *b_trig_EF_el_EF_e10_loose_mu10;   //!
   TBranch        *b_trig_EF_el_EF_e10_loose_mu6;   //!
   TBranch        *b_trig_EF_el_EF_e10_medium;   //!
   TBranch        *b_trig_EF_el_EF_e10_medium_IDTrkNoCut;   //!
   TBranch        *b_trig_EF_el_EF_e10_medium_SiTrk;   //!
   TBranch        *b_trig_EF_el_EF_e10_medium_TRT;   //!
   TBranch        *b_trig_EF_el_EF_e10_tight;   //!
   TBranch        *b_trig_EF_el_EF_e15_loose;   //!
   TBranch        *b_trig_EF_el_EF_e15_loose_IDTrkNoCut;   //!
   TBranch        *b_trig_EF_el_EF_e15_medium;   //!
   TBranch        *b_trig_EF_el_EF_e15_medium_SiTrk;   //!
   TBranch        *b_trig_EF_el_EF_e15_medium_TRT;   //!
   TBranch        *b_trig_EF_el_EF_e15_tight;   //!
   TBranch        *b_trig_EF_el_EF_e18_medium;   //!
   TBranch        *b_trig_EF_el_EF_e20_loose;   //!
   TBranch        *b_trig_EF_el_EF_e20_loose_IDTrkNoCut;   //!
   TBranch        *b_trig_EF_el_EF_e20_loose_passEF;   //!
   TBranch        *b_trig_EF_el_EF_e20_loose_passL2;   //!
   TBranch        *b_trig_EF_el_EF_e20_loose_xe20_noMu;   //!
   TBranch        *b_trig_EF_el_EF_e20_loose_xe30_noMu;   //!
   TBranch        *b_trig_EF_el_EF_e20_medium;   //!
   TBranch        *b_trig_EF_el_EF_e25_loose;   //!
   TBranch        *b_trig_EF_el_EF_e30_loose;   //!
   TBranch        *b_trig_EF_el_EF_e3_loose;   //!
   TBranch        *b_trig_EF_el_EF_e3_loose_SiTrk;   //!
   TBranch        *b_trig_EF_el_EF_e3_loose_TRT;   //!
   TBranch        *b_trig_EF_el_EF_e3_medium;   //!
   TBranch        *b_trig_EF_el_EF_e3_medium_SiTrk;   //!
   TBranch        *b_trig_EF_el_EF_e3_medium_TRT;   //!
   TBranch        *b_trig_EF_el_EF_e5_NoCut_firstempty;   //!
   TBranch        *b_trig_EF_el_EF_e5_medium;   //!
   TBranch        *b_trig_EF_el_EF_e5_medium_MV;   //!
   TBranch        *b_trig_EF_el_EF_e5_medium_SiTrk;   //!
   TBranch        *b_trig_EF_el_EF_e5_medium_TRT;   //!
   TBranch        *b_trig_EF_el_EF_e5_medium_mu4;   //!
   TBranch        *b_trig_EF_el_EF_e5_tight;   //!
   TBranch        *b_trig_EF_el_EF_e5_tight_SiTrk;   //!
   TBranch        *b_trig_EF_el_EF_e5_tight_TRT;   //!
   TBranch        *b_trig_EF_el_EF_e5_tight_e5_NoCut;   //!
   TBranch        *b_trig_EF_el_EF_eb_physics;   //!
   TBranch        *b_trig_EF_el_EF_eb_physics_empty;   //!
   TBranch        *b_trig_EF_el_EF_eb_physics_firstempty;   //!
   TBranch        *b_trig_EF_el_EF_eb_physics_unpaired_iso;   //!
   TBranch        *b_trig_EF_el_EF_eb_physics_unpaired_noniso;   //!
   TBranch        *b_trig_EF_el_EF_eb_random;   //!
   TBranch        *b_trig_EF_el_EF_eb_random_empty;   //!
   TBranch        *b_trig_EF_el_EF_eb_random_firstempty;   //!
   TBranch        *b_trig_EF_el_EF_eb_random_unpaired_iso;   //!
   TBranch        *b_trig_EF_el_EF_em105_passHLT;   //!
   TBranch        *b_trig_EF_ph_n;   //!
   TBranch        *b_trig_EF_ph_E;   //!
   TBranch        *b_trig_EF_ph_Et;   //!
   TBranch        *b_trig_EF_ph_pt;   //!
   TBranch        *b_trig_EF_ph_m;   //!
   TBranch        *b_trig_EF_ph_eta;   //!
   TBranch        *b_trig_EF_ph_phi;   //!
   TBranch        *b_trig_EF_ph_px;   //!
   TBranch        *b_trig_EF_ph_py;   //!
   TBranch        *b_trig_EF_ph_pz;   //!
   TBranch        *b_trig_EF_ph_EF_2g10_loose;   //!
   TBranch        *b_trig_EF_ph_EF_2g15_loose;   //!
   TBranch        *b_trig_EF_ph_EF_2g5_loose;   //!
   TBranch        *b_trig_EF_ph_EF_2g7_loose;   //!
   TBranch        *b_trig_EF_ph_EF_g10_loose;   //!
   TBranch        *b_trig_EF_ph_EF_g10_loose_larcalib;   //!
   TBranch        *b_trig_EF_ph_EF_g11_etcut;   //!
   TBranch        *b_trig_EF_ph_EF_g15_loose;   //!
   TBranch        *b_trig_EF_ph_EF_g17_etcut;   //!
   TBranch        *b_trig_EF_ph_EF_g17_etcut_EFxe20_noMu;   //!
   TBranch        *b_trig_EF_ph_EF_g17_etcut_EFxe30_noMu;   //!
   TBranch        *b_trig_EF_ph_EF_g20_loose;   //!
   TBranch        *b_trig_EF_ph_EF_g20_loose_larcalib;   //!
   TBranch        *b_trig_EF_ph_EF_g20_loose_xe20_noMu;   //!
   TBranch        *b_trig_EF_ph_EF_g20_loose_xe30_noMu;   //!
   TBranch        *b_trig_EF_ph_EF_g20_tight;   //!
   TBranch        *b_trig_EF_ph_EF_g25_loose_xe30_noMu;   //!
   TBranch        *b_trig_EF_ph_EF_g30_loose;   //!
   TBranch        *b_trig_EF_ph_EF_g30_tight;   //!
   TBranch        *b_trig_EF_ph_EF_g3_NoCut_unpaired_iso;   //!
   TBranch        *b_trig_EF_ph_EF_g3_NoCut_unpaired_noniso;   //!
   TBranch        *b_trig_EF_ph_EF_g40_loose;   //!
   TBranch        *b_trig_EF_ph_EF_g40_loose_larcalib;   //!
   TBranch        *b_trig_EF_ph_EF_g40_tight;   //!
   TBranch        *b_trig_EF_ph_EF_g50_loose;   //!
   TBranch        *b_trig_EF_ph_EF_g50_loose_larcalib;   //!
   TBranch        *b_trig_EF_ph_EF_g5_NoCut_cosmic;   //!
   TBranch        *b_trig_EF_ph_EF_g5_loose;   //!
   TBranch        *b_trig_EF_ph_EF_g5_loose_larcalib;   //!
   TBranch        *b_trig_EF_ph_EF_g7_loose;   //!
   TBranch        *b_trig_Nav_n;   //!
   TBranch        *b_trig_Nav_chain_ChainId;   //!
   TBranch        *b_trig_Nav_chain_RoIType;   //!
   TBranch        *b_trig_Nav_chain_RoIIndex;   //!
   TBranch        *b_trig_RoI_L2_e_n;   //!
   TBranch        *b_trig_RoI_L2_e_type;   //!
   TBranch        *b_trig_RoI_L2_e_lastStep;   //!
   TBranch        *b_trig_RoI_L2_e_TrigEMCluster;   //!
   TBranch        *b_trig_RoI_L2_e_TrigEMClusterStatus;   //!
   TBranch        *b_trig_RoI_L2_e_EmTau_ROI;   //!
   TBranch        *b_trig_RoI_L2_e_EmTau_ROIStatus;   //!
   TBranch        *b_trig_RoI_L2_e_TrigInDetTrackCollection_TrigSiTrack_eGamma;   //!
   TBranch        *b_trig_RoI_L2_e_TrigInDetTrackCollection_TrigSiTrack_eGammaStatus;   //!
   TBranch        *b_trig_RoI_L2_e_TrigInDetTrackCollection_TrigIDSCAN_eGamma;   //!
   TBranch        *b_trig_RoI_L2_e_TrigInDetTrackCollection_TrigIDSCAN_eGammaStatus;   //!
   TBranch        *b_trig_RoI_L2_e_TrigElectronContainer;   //!
   TBranch        *b_trig_RoI_L2_e_TrigElectronContainerStatus;   //!
   TBranch        *b_trig_RoI_EF_e_n;   //!
   TBranch        *b_trig_RoI_EF_e_type;   //!
   TBranch        *b_trig_RoI_EF_e_lastStep;   //!
   TBranch        *b_trig_RoI_EF_e_EmTau_ROI;   //!
   TBranch        *b_trig_RoI_EF_e_EmTau_ROIStatus;   //!
   TBranch        *b_trig_DB_SMK;   //!
   TBranch        *b_trig_DB_L1PSK;   //!
   TBranch        *b_trig_DB_HLTPSK;   //!
   TBranch        *b_trig_L1_esum_thrNames;   //!
   TBranch        *b_trig_L1_esum_energyX;   //!
   TBranch        *b_trig_L1_esum_energyY;   //!
   TBranch        *b_trig_L1_esum_energyT;   //!
   TBranch        *b_trig_L1_esum_overflowX;   //!
   TBranch        *b_trig_L1_esum_overflowY;   //!
   TBranch        *b_trig_L1_esum_overflowT;   //!
   TBranch        *b_trig_L1_esum_RoIWord0;   //!
   TBranch        *b_trig_L1_esum_RoIWord1;   //!
   TBranch        *b_trig_L1_esum_RoIWord2;   //!
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
   TBranch        *b_trig_bgCode;   //!
   TBranch        *b_MET_Goodness_CalClusForwBackw_pass;   //!
   TBranch        *b_MET_Goodness_CalClusUpDown_pass;   //!
   TBranch        *b_MET_Goodness_Calo_countA;   //!
   TBranch        *b_MET_Goodness_Calo_countC;   //!
   TBranch        *b_MET_Goodness_Calo_pass;   //!
   TBranch        *b_MET_Goodness_IsCollisionCandidate;   //!
   TBranch        *b_MET_Goodness_MBTS_countA;   //!
   TBranch        *b_MET_Goodness_MBTS_countC;   //!
   TBranch        *b_MET_Goodness_MBTS_pass;   //!
   TBranch        *b_MET_Goodness_MuonSp0Hits;   //!
   TBranch        *b_MET_Goodness_MuonSp1Hits;   //!
   TBranch        *b_MET_Goodness_MuonSpTotHits;   //!
   TBranch        *b_MET_Goodness_OkayLB;   //!
   TBranch        *b_MET_Goodness_CalClusForwBackw_timeDiff;   //!
   TBranch        *b_MET_Goodness_CalClusUpDown_timeDiff;   //!
   TBranch        *b_MET_Goodness_CalClus_InTimeFraction;   //!
   TBranch        *b_MET_Goodness_CalClus_OutTimeEnergy;   //!
   TBranch        *b_MET_Goodness_CalClus_eventTime;   //!
   TBranch        *b_MET_Goodness_CalClus_ootEnergy10;   //!
   TBranch        *b_MET_Goodness_CalClus_ootEnergy15;   //!
   TBranch        *b_MET_Goodness_CalClus_ootEnergy20;   //!
   TBranch        *b_MET_Goodness_CalClus_ootEnergy25;   //!
   TBranch        *b_MET_Goodness_CalClus_ootFraction10;   //!
   TBranch        *b_MET_Goodness_CalClus_ootFraction15;   //!
   TBranch        *b_MET_Goodness_CalClus_ootFraction20;   //!
   TBranch        *b_MET_Goodness_CalClus_ootFraction25;   //!
   TBranch        *b_MET_Goodness_CalClus_timeA;   //!
   TBranch        *b_MET_Goodness_CalClus_timeC;   //!
   TBranch        *b_MET_Goodness_Calo_timeA;   //!
   TBranch        *b_MET_Goodness_Calo_timeC;   //!
   TBranch        *b_MET_Goodness_Calo_timeDiff;   //!
   TBranch        *b_MET_Goodness_EtoverRootSigmaEt;   //!
   TBranch        *b_MET_Goodness_EventEMFraction;   //!
   TBranch        *b_MET_Goodness_LArNoisyROSummary;   //!
   TBranch        *b_MET_Goodness_MBTS_timeA;   //!
   TBranch        *b_MET_Goodness_MBTS_timeC;   //!
   TBranch        *b_MET_Goodness_MBTS_timeDiff;   //!
   TBranch        *b_MET_Goodness_MET_CorrTopo_etx;   //!
   TBranch        *b_MET_Goodness_MET_CorrTopo_ety;   //!
   TBranch        *b_MET_Goodness_MET_CorrTopo_sumet;   //!
   TBranch        *b_MET_Goodness_MET_Topo_etx;   //!
   TBranch        *b_MET_Goodness_MET_Topo_ety;   //!
   TBranch        *b_MET_Goodness_MET_Topo_sumet;   //!
   TBranch        *b_MET_Goodness_MuonSp0Eta;   //!
   TBranch        *b_MET_Goodness_MuonSp0Phi;   //!
   TBranch        *b_MET_Goodness_MuonSp1Eta;   //!
   TBranch        *b_MET_Goodness_MuonSp1Phi;   //!
   TBranch        *b_MET_Goodness_MuonTRTTiming;   //!
   TBranch        *b_MET_Goodness_BCH_CORR_CELL_Jet;   //!
   TBranch        *b_MET_Goodness_BCH_CORR_JET;   //!
   TBranch        *b_MET_Goodness_BCH_CORR_JET_FORCELL_Jet;   //!
   TBranch        *b_MET_Goodness_ChargeFraction_Jet;   //!
   TBranch        *b_MET_Goodness_DeltaEt_JetAlgs_Jet;   //!
   TBranch        *b_MET_Goodness_DeltaEta_JetAlgs_Jet;   //!
   TBranch        *b_MET_Goodness_DeltaPhi_JetAlgs_Jet;   //!
   TBranch        *b_MET_Goodness_DeltaPhi_MET_Jet;   //!
   TBranch        *b_MET_Goodness_EEM_Jet;   //!
   TBranch        *b_MET_Goodness_EFinal_Jet;   //!
   TBranch        *b_MET_Goodness_EMFraction_Jet;   //!
   TBranch        *b_MET_Goodness_E_BadCellsCorr_Jet;   //!
   TBranch        *b_MET_Goodness_E_BadCells_Jet;   //!
   TBranch        *b_MET_Goodness_Eta_Jet;   //!
   TBranch        *b_MET_Goodness_HECf_Jet;   //!
   TBranch        *b_MET_Goodness_LArQuality_Jet;   //!
   TBranch        *b_MET_Goodness_Phi_Jet;   //!
   TBranch        *b_MET_Goodness_PtEM_Jet;   //!
   TBranch        *b_MET_Goodness_QualityFrac_Jet;   //!
   TBranch        *b_MET_Goodness_SamplingFracCryo_Jet;   //!
   TBranch        *b_MET_Goodness_SamplingFracEM_Jet;   //!
   TBranch        *b_MET_Goodness_SamplingFracFCAL_Jet;   //!
   TBranch        *b_MET_Goodness_SamplingFracGap_Jet;   //!
   TBranch        *b_MET_Goodness_SamplingFracHEC3_Jet;   //!
   TBranch        *b_MET_Goodness_SamplingFracHEC_Jet;   //!
   TBranch        *b_MET_Goodness_SamplingFracMax_Jet;   //!
   TBranch        *b_MET_Goodness_SamplingFracPS_Jet;   //!
   TBranch        *b_MET_Goodness_SamplingFracTile10_Jet;   //!
   TBranch        *b_MET_Goodness_SamplingFracTile2_Jet;   //!
   TBranch        *b_MET_Goodness_SamplingFracTile_Jet;   //!
   TBranch        *b_MET_Goodness_TileQuality_Jet;   //!
   TBranch        *b_MET_Goodness_Timing_Jet;   //!
   TBranch        *b_MET_Goodness_fcor_Jet;   //!
   TBranch        *b_MET_Goodness_ootE25_Jet;   //!
   TBranch        *b_MET_Goodness_ootE50_Jet;   //!
   TBranch        *b_MET_Goodness_ootE75_Jet;   //!
   TBranch        *b_MET_Goodness_N90Cells_Jet;   //!
   TBranch        *b_MET_Goodness_N90Constituents_Jet;   //!
   TBranch        *b_MET_Goodness_NConstituents_Jet;   //!
   TBranch        *b_MET_Goodness_N_BadCellsCorr_Jet;   //!
   TBranch        *b_MET_Goodness_N_BadCells_Jet;   //!
   TBranch        *b_MET_Goodness_NumTracks_Jet;   //!
   TBranch        *b_MET_Goodness_SamplingMaxID_Jet;   //!
   TBranch        *b_MET_Goodness_All;   //!
   TBranch        *b_MET_Goodness_JetCleaning;   //!
   TBranch        *b_MET_Goodness_BitMask;   //!

   physics(TTree *tree=0);
   virtual ~physics();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef physics_cxx
physics::physics(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("group10.phys-sm.03672_002223.D3PD._00022.root");
      if (!f) {
         f = new TFile("group10.phys-sm.03672_002223.D3PD._00022.root");
      }
      tree = (TTree*)gDirectory->Get("physics");

   }
   Init(tree);
}

physics::~physics()
{
   if (!fChain) return;
   //delete fChain->GetCurrentFile();
}

Int_t physics::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t physics::LoadTree(Long64_t entry)
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

void physics::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   el_E = 0;
   el_Et = 0;
   el_pt = 0;
   el_m = 0;
   el_eta = 0;
   el_phi = 0;
   el_px = 0;
   el_py = 0;
   el_pz = 0;
   el_charge = 0;
   el_author = 0;
   el_isEM = 0;
   el_convFlag = 0;
   el_isConv = 0;
   el_nConv = 0;
   el_nSingleTrackConv = 0;
   el_nDoubleTrackConv = 0;
   el_loose = 0;
   el_medium = 0;
   el_mediumIso = 0;
   el_tight = 0;
   el_tightIso = 0;
   el_Ethad = 0;
   el_Ethad1 = 0;
   el_f1 = 0;
   el_f1core = 0;
   el_Emins1 = 0;
   el_fside = 0;
   el_Emax2 = 0;
   el_ws3 = 0;
   el_wstot = 0;
   el_emaxs1 = 0;
   el_deltaEs = 0;
   el_E233 = 0;
   el_E237 = 0;
   el_E277 = 0;
   el_weta2 = 0;
   el_f3 = 0;
   el_f3core = 0;
   el_rphiallcalo = 0;
   el_Etcone45 = 0;
   el_Etcone20 = 0;
   el_Etcone30 = 0;
   el_Etcone40 = 0;
   el_ptcone30 = 0;
   el_convanglematch = 0;
   el_convtrackmatch = 0;
   el_hasconv = 0;
   el_convvtxx = 0;
   el_convvtxy = 0;
   el_convvtxz = 0;
   el_Rconv = 0;
   el_zconv = 0;
   el_convvtxchi2 = 0;
   el_pt1conv = 0;
   el_convtrk1nBLHits = 0;
   el_convtrk1nPixHits = 0;
   el_convtrk1nSCTHits = 0;
   el_convtrk1nTRTHits = 0;
   el_pt2conv = 0;
   el_convtrk2nBLHits = 0;
   el_convtrk2nPixHits = 0;
   el_convtrk2nSCTHits = 0;
   el_convtrk2nTRTHits = 0;
   el_ptconv = 0;
   el_pzconv = 0;
   el_pos7 = 0;
   el_etacorrmag = 0;
   el_deltaeta1 = 0;
   el_deltaeta2 = 0;
   el_deltaphi2 = 0;
   el_deltaphiRescaled = 0;
   el_expectHitInBLayer = 0;
   el_reta = 0;
   el_rphi = 0;
   el_EtringnoisedR03sig2 = 0;
   el_EtringnoisedR03sig3 = 0;
   el_EtringnoisedR03sig4 = 0;
   el_isolationlikelihoodjets = 0;
   el_isolationlikelihoodhqelectrons = 0;
   el_electronweight = 0;
   el_electronbgweight = 0;
   el_softeweight = 0;
   el_softebgweight = 0;
   el_neuralnet = 0;
   el_Hmatrix = 0;
   el_Hmatrix5 = 0;
   el_adaboost = 0;
   el_softeneuralnet = 0;
   el_zvertex = 0;
   el_errz = 0;
   el_etap = 0;
   el_depth = 0;
   el_breminvpt = 0;
   el_bremradius = 0;
   el_bremx = 0;
   el_bremclusterradius = 0;
   el_breminvpterr = 0;
   el_bremtrackauthor = 0;
   el_hasbrem = 0;
   el_bremdeltaqoverp = 0;
   el_bremmaterialtraversed = 0;
   el_refittedtrackqoverp = 0;
   el_refittedtrackd0 = 0;
   el_refittedtrackz0 = 0;
   el_refittedtracktheta = 0;
   el_refittedtrackphi = 0;
   el_Es0 = 0;
   el_etas0 = 0;
   el_phis0 = 0;
   el_Es1 = 0;
   el_etas1 = 0;
   el_phis1 = 0;
   el_Es2 = 0;
   el_etas2 = 0;
   el_phis2 = 0;
   el_Es3 = 0;
   el_etas3 = 0;
   el_phis3 = 0;
   el_E_PreSamplerB = 0;
   el_E_EMB1 = 0;
   el_E_EMB2 = 0;
   el_E_EMB3 = 0;
   el_E_PreSamplerE = 0;
   el_E_EME1 = 0;
   el_E_EME2 = 0;
   el_E_EME3 = 0;
   el_E_HEC0 = 0;
   el_E_HEC1 = 0;
   el_E_HEC2 = 0;
   el_E_HEC3 = 0;
   el_E_TileBar0 = 0;
   el_E_TileBar1 = 0;
   el_E_TileBar2 = 0;
   el_E_TileGap1 = 0;
   el_E_TileGap2 = 0;
   el_E_TileGap3 = 0;
   el_E_TileExt0 = 0;
   el_E_TileExt1 = 0;
   el_E_TileExt2 = 0;
   el_E_FCAL0 = 0;
   el_E_FCAL1 = 0;
   el_E_FCAL2 = 0;
   el_cl_E = 0;
   el_cl_pt = 0;
   el_cl_eta = 0;
   el_cl_phi = 0;
   el_firstEdens = 0;
   el_cellmaxfrac = 0;
   el_longitudinal = 0;
   el_secondlambda = 0;
   el_lateral = 0;
   el_secondR = 0;
   el_centerlambda = 0;
   el_rawcl_Es0 = 0;
   el_rawcl_etas0 = 0;
   el_rawcl_phis0 = 0;
   el_rawcl_Es1 = 0;
   el_rawcl_etas1 = 0;
   el_rawcl_phis1 = 0;
   el_rawcl_Es2 = 0;
   el_rawcl_etas2 = 0;
   el_rawcl_phis2 = 0;
   el_rawcl_Es3 = 0;
   el_rawcl_etas3 = 0;
   el_rawcl_phis3 = 0;
   el_rawcl_E = 0;
   el_rawcl_pt = 0;
   el_rawcl_eta = 0;
   el_rawcl_phi = 0;
   el_refittedtrackcovd0 = 0;
   el_refittedtrackcovz0 = 0;
   el_refittedtrackcovphi = 0;
   el_refittedtrackcovtheta = 0;
   el_refittedtrackcovqoverp = 0;
   el_refittedtrackcovd0z0 = 0;
   el_refittedtrackcovz0phi = 0;
   el_refittedtrackcovz0theta = 0;
   el_refittedtrackcovz0qoverp = 0;
   el_refittedtrackcovd0phi = 0;
   el_refittedtrackcovd0theta = 0;
   el_refittedtrackcovd0qoverp = 0;
   el_refittedtrackcovphitheta = 0;
   el_refittedtrackcovphiqoverp = 0;
   el_refittedtrackcovthetaqoverp = 0;
   el_trackd0 = 0;
   el_trackz0 = 0;
   el_trackphi = 0;
   el_tracktheta = 0;
   el_trackqoverp = 0;
   el_trackpt = 0;
   el_tracketa = 0;
   el_trackcov_d0 = 0;
   el_trackcov_z0 = 0;
   el_trackcov_phi = 0;
   el_trackcov_theta = 0;
   el_trackcov_qoverp = 0;
   el_trackcov_d0_z0 = 0;
   el_trackcov_d0_phi = 0;
   el_trackcov_d0_theta = 0;
   el_trackcov_d0_qoverp = 0;
   el_trackcov_z0_phi = 0;
   el_trackcov_z0_theta = 0;
   el_trackcov_z0_qoverp = 0;
   el_trackcov_phi_theta = 0;
   el_trackcov_phi_qoverp = 0;
   el_trackcov_theta_qoverp = 0;
   el_trackfitchi2 = 0;
   el_trackfitndof = 0;
   el_nBLHits = 0;
   el_nPixHits = 0;
   el_nSCTHits = 0;
   el_nTRTHits = 0;
   el_nPixHoles = 0;
   el_nSCTHoles = 0;
   el_nBLSharedHits = 0;
   el_nPixSharedHits = 0;
   el_nSCTSharedHits = 0;
   el_nTRTHighTHits = 0;
   el_nTRTOutliers = 0;
   el_nTRTHighTOutliers = 0;
   el_nSiHits = 0;
   el_TRTHighTHitsRatio = 0;
   el_pixeldEdx = 0;
   el_eProbabilityComb = 0;
   el_eProbabilityHT = 0;
   el_eProbabilityToT = 0;
   el_eProbabilityBrem = 0;
   el_vertx = 0;
   el_verty = 0;
   el_vertz = 0;
   el_hastrack = 0;
   el_deltaEmax2 = 0;
   el_trackd0beam = 0;
   el_tracksigd0beam = 0;
   el_trackd0pv = 0;
   el_tracksigd0pv = 0;
   el_trackz0pv = 0;
   el_tracksigz0pv = 0;
   el_trackd0pvunbiased = 0;
   el_tracksigd0pvunbiased = 0;
   el_trackz0pvunbiased = 0;
   el_tracksigz0pvunbiased = 0;
   el_jetcone_n = 0;
   el_jetcone_dr = 0;
   el_jetcone_signedIP = 0;
   el_jetcone_ptrel = 0;
   el_jetcone_index = 0;
   el_jetcone_E = 0;
   el_jetcone_pt = 0;
   el_jetcone_m = 0;
   el_jetcone_eta = 0;
   el_jetcone_phi = 0;
   el_isIso = 0;
   el_jet_dr = 0;
   el_jet_E = 0;
   el_jet_pt = 0;
   el_jet_m = 0;
   el_jet_eta = 0;
   el_jet_phi = 0;
   el_jet_matched = 0;
   el_Etcone40_pt_corrected = 0;
   el_Etcone40_ED_corrected = 0;
   el_Etcone40_corrected = 0;
   el_EF_dr = 0;
   el_EF_index = 0;
   el_L2_dr = 0;
   el_L2_index = 0;
   el_L1_dr = 0;
   el_L1_index = 0;
   el_EF_E = 0;
   el_EF_Et = 0;
   el_EF_pt = 0;
   el_EF_eta = 0;
   el_EF_phi = 0;
   el_EF_charge = 0;
   el_EF_Ethad = 0;
   el_EF_Ethad1 = 0;
   el_EF_f1 = 0;
   el_EF_Emins1 = 0;
   el_EF_fside = 0;
   el_EF_Emax2 = 0;
   el_EF_ws3 = 0;
   el_EF_wstot = 0;
   el_EF_E233 = 0;
   el_EF_E237 = 0;
   el_EF_E277 = 0;
   el_EF_weta2 = 0;
   el_EF_rphiallcalo = 0;
   el_EF_deltaeta1 = 0;
   el_EF_deltaeta2 = 0;
   el_EF_deltaphi2 = 0;
   el_EF_expectHitInBLayer = 0;
   el_EF_Etcone45 = 0;
   el_EF_Etcone20 = 0;
   el_EF_Etcone30 = 0;
   el_EF_Etcone40 = 0;
   el_EF_etacorrmag = 0;
   el_EF_zvertex = 0;
   el_EF_errz = 0;
   el_EF_trackd0 = 0;
   el_EF_trackz0 = 0;
   el_EF_trackphi = 0;
   el_EF_tracktheta = 0;
   el_EF_trackqoverp = 0;
   el_EF_trackpt = 0;
   el_EF_tracketa = 0;
   el_EF_nBLHits = 0;
   el_EF_nPixHits = 0;
   el_EF_nSCTHits = 0;
   el_EF_nTRTHits = 0;
   el_EF_nTRTHighTHits = 0;
   el_EF_nSiHits = 0;
   el_EF_TRTHighTHitsRatio = 0;
   el_EF_pixeldEdx = 0;
   el_EF_hastrack = 0;
   el_EF_matched = 0;
   el_L2_E = 0;
   el_L2_Et = 0;
   el_L2_pt = 0;
   el_L2_eta = 0;
   el_L2_phi = 0;
   el_L2_charge = 0;
   el_L2_Ethad1 = 0;
   el_L2_reta = 0;
   el_L2_Eratio = 0;
   el_L2_trackclusterdeta = 0;
   el_L2_trackclusterdphi = 0;
   el_L2_Etoverpt = 0;
   el_L2_trackpt = 0;
   el_L2_trackalgo = 0;
   el_L2_tracketa = 0;
   el_L2_trackd0 = 0;
   el_L2_trackz0 = 0;
   el_L2_tracktheta = 0;
   el_L2_trackphi = 0;
   el_L2_tracketaatcalo = 0;
   el_L2_trackphiatcalo = 0;
   el_L2_errpt = 0;
   el_L2_erreta = 0;
   el_L2_errphi = 0;
   el_L2_E237 = 0;
   el_L2_E277 = 0;
   el_L2_fside = 0;
   el_L2_weta2 = 0;
   el_L2_Emaxs1 = 0;
   el_L2_Emax2 = 0;
   el_L2_matched = 0;
   el_L1_eta = 0;
   el_L1_phi = 0;
   el_L1_EMisol = 0;
   el_L1_hadisol = 0;
   el_L1_hadcore = 0;
   el_L1_pt = 0;
   el_L1_Et = 0;
   el_L1_matched = 0;
   ph_E = 0;
   ph_Et = 0;
   ph_pt = 0;
   ph_m = 0;
   ph_eta = 0;
   ph_phi = 0;
   ph_px = 0;
   ph_py = 0;
   ph_pz = 0;
   ph_author = 0;
   ph_isRecovered = 0;
   ph_isEM = 0;
   ph_convFlag = 0;
   ph_isConv = 0;
   ph_nConv = 0;
   ph_nSingleTrackConv = 0;
   ph_nDoubleTrackConv = 0;
   ph_loose = 0;
   ph_tight = 0;
   ph_tightIso = 0;
   ph_Ethad = 0;
   ph_Ethad1 = 0;
   ph_E033 = 0;
   ph_f1 = 0;
   ph_f1core = 0;
   ph_Emins1 = 0;
   ph_fside = 0;
   ph_Emax2 = 0;
   ph_ws3 = 0;
   ph_wstot = 0;
   ph_E132 = 0;
   ph_E1152 = 0;
   ph_emaxs1 = 0;
   ph_deltaEs = 0;
   ph_E233 = 0;
   ph_E237 = 0;
   ph_E277 = 0;
   ph_weta2 = 0;
   ph_f3 = 0;
   ph_f3core = 0;
   ph_rphiallcalo = 0;
   ph_Etcone45 = 0;
   ph_Etcone20 = 0;
   ph_Etcone30 = 0;
   ph_Etcone40 = 0;
   ph_ptcone30 = 0;
   ph_convanglematch = 0;
   ph_convtrackmatch = 0;
   ph_hasconv = 0;
   ph_convvtxx = 0;
   ph_convvtxy = 0;
   ph_convvtxz = 0;
   ph_Rconv = 0;
   ph_zconv = 0;
   ph_convvtxchi2 = 0;
   ph_pt1conv = 0;
   ph_convtrk1nBLHits = 0;
   ph_convtrk1nPixHits = 0;
   ph_convtrk1nSCTHits = 0;
   ph_convtrk1nTRTHits = 0;
   ph_pt2conv = 0;
   ph_convtrk2nBLHits = 0;
   ph_convtrk2nPixHits = 0;
   ph_convtrk2nSCTHits = 0;
   ph_convtrk2nTRTHits = 0;
   ph_ptconv = 0;
   ph_pzconv = 0;
   ph_reta = 0;
   ph_rphi = 0;
   ph_EtringnoisedR03sig2 = 0;
   ph_EtringnoisedR03sig3 = 0;
   ph_EtringnoisedR03sig4 = 0;
   ph_isolationlikelihoodjets = 0;
   ph_isolationlikelihoodhqelectrons = 0;
   ph_loglikelihood = 0;
   ph_photonweight = 0;
   ph_photonbgweight = 0;
   ph_neuralnet = 0;
   ph_Hmatrix = 0;
   ph_Hmatrix5 = 0;
   ph_adaboost = 0;
   ph_zvertex = 0;
   ph_errz = 0;
   ph_etap = 0;
   ph_depth = 0;
   ph_cl_E = 0;
   ph_cl_pt = 0;
   ph_cl_eta = 0;
   ph_cl_phi = 0;
   ph_Es0 = 0;
   ph_etas0 = 0;
   ph_phis0 = 0;
   ph_Es1 = 0;
   ph_etas1 = 0;
   ph_phis1 = 0;
   ph_Es2 = 0;
   ph_etas2 = 0;
   ph_phis2 = 0;
   ph_Es3 = 0;
   ph_etas3 = 0;
   ph_phis3 = 0;
   ph_rawcl_Es0 = 0;
   ph_rawcl_etas0 = 0;
   ph_rawcl_phis0 = 0;
   ph_rawcl_Es1 = 0;
   ph_rawcl_etas1 = 0;
   ph_rawcl_phis1 = 0;
   ph_rawcl_Es2 = 0;
   ph_rawcl_etas2 = 0;
   ph_rawcl_phis2 = 0;
   ph_rawcl_Es3 = 0;
   ph_rawcl_etas3 = 0;
   ph_rawcl_phis3 = 0;
   ph_rawcl_E = 0;
   ph_rawcl_pt = 0;
   ph_rawcl_eta = 0;
   ph_rawcl_phi = 0;
   ph_deltaEmax2 = 0;
   ph_isIso = 0;
   ph_topoEtcone20 = 0;
   ph_topoEtcone40 = 0;
   ph_topoEtcone60 = 0;
   ph_jet_dr = 0;
   ph_jet_E = 0;
   ph_jet_pt = 0;
   ph_jet_m = 0;
   ph_jet_eta = 0;
   ph_jet_phi = 0;
   ph_jet_matched = 0;
   ph_trackIsol = 0;
   ph_convIP = 0;
   ph_convIPRev = 0;
   ph_ptIsolationCone = 0;
   ph_ptIsolationConePhAngle = 0;
   ph_Etcone40_pt_corrected = 0;
   ph_Etcone40_ED_corrected = 0;
   ph_Etcone40_corrected = 0;
   ph_topodr = 0;
   ph_topopt = 0;
   ph_topoeta = 0;
   ph_topophi = 0;
   ph_topomatched = 0;
   ph_topoEMdr = 0;
   ph_topoEMpt = 0;
   ph_topoEMeta = 0;
   ph_topoEMphi = 0;
   ph_topoEMmatched = 0;
   ph_EF_dr = 0;
   ph_EF_index = 0;
   ph_L2_dr = 0;
   ph_L2_index = 0;
   ph_L1_dr = 0;
   ph_L1_index = 0;
   ph_EF_E = 0;
   ph_EF_Et = 0;
   ph_EF_pt = 0;
   ph_EF_eta = 0;
   ph_EF_phi = 0;
   ph_EF_Ethad = 0;
   ph_EF_Ethad1 = 0;
   ph_EF_f1 = 0;
   ph_EF_Emins1 = 0;
   ph_EF_fside = 0;
   ph_EF_Emax2 = 0;
   ph_EF_ws3 = 0;
   ph_EF_wstot = 0;
   ph_EF_E233 = 0;
   ph_EF_E237 = 0;
   ph_EF_E277 = 0;
   ph_EF_weta2 = 0;
   ph_EF_rphiallcalo = 0;
   ph_EF_Etcone45 = 0;
   ph_EF_Etcone20 = 0;
   ph_EF_Etcone30 = 0;
   ph_EF_Etcone40 = 0;
   ph_EF_zvertex = 0;
   ph_EF_errz = 0;
   ph_EF_matched = 0;
   ph_L2_E = 0;
   ph_L2_Et = 0;
   ph_L2_pt = 0;
   ph_L2_eta = 0;
   ph_L2_phi = 0;
   ph_L2_Ethad1 = 0;
   ph_L2_reta = 0;
   ph_L2_Eratio = 0;
   ph_L2_E237 = 0;
   ph_L2_E277 = 0;
   ph_L2_fside = 0;
   ph_L2_weta2 = 0;
   ph_L2_Emaxs1 = 0;
   ph_L2_Emax2 = 0;
   ph_L2_matched = 0;
   ph_L1_eta = 0;
   ph_L1_phi = 0;
   ph_L1_EMisol = 0;
   ph_L1_hadisol = 0;
   ph_L1_hadcore = 0;
   ph_L1_pt = 0;
   ph_L1_Et = 0;
   ph_L1_matched = 0;
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
   mu_muid_loose = 0;
   mu_muid_medium = 0;
   mu_muid_tight = 0;
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
   mu_staco_loose = 0;
   mu_staco_medium = 0;
   mu_staco_tight = 0;
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
   tau_Et = 0;
   tau_pt = 0;
   tau_m = 0;
   tau_eta = 0;
   tau_phi = 0;
   tau_charge = 0;
   tau_BDTEleScore = 0;
   tau_BDTJetScore = 0;
   tau_discCut = 0;
   tau_discCutTMVA = 0;
   tau_discLL = 0;
   tau_discNN = 0;
   tau_efficLL = 0;
   tau_efficNN = 0;
   tau_likelihood = 0;
   tau_tauJetNeuralNetwork = 0;
   tau_tauENeuralNetwork = 0;
   tau_tauElTauLikelihood = 0;
   tau_electronVetoLoose = 0;
   tau_electronVetoMedium = 0;
   tau_electronVetoTight = 0;
   tau_muonVeto = 0;
   tau_tauCutLoose = 0;
   tau_tauCutMedium = 0;
   tau_tauCutTight = 0;
   tau_tauCutSafeLoose = 0;
   tau_tauCutSafeMedium = 0;
   tau_tauCutSafeTight = 0;
   tau_tauCutSafeCaloLoose = 0;
   tau_tauCutSafeCaloMedium = 0;
   tau_tauCutSafeCaloTight = 0;
   tau_tauLlhLoose = 0;
   tau_tauLlhMedium = 0;
   tau_tauLlhTight = 0;
   tau_author = 0;
   tau_ROIword = 0;
   tau_nProng = 0;
   tau_numTrack = 0;
   tau_etOverPtLeadTrk = 0;
   tau_ipZ0SinThetaSigLeadTrk = 0;
   tau_leadTrkPt = 0;
   tau_nLooseTrk = 0;
   tau_nLooseConvTrk = 0;
   tau_nProngLoose = 0;
   tau_ipSigLeadTrk = 0;
   tau_ipSigLeadLooseTrk = 0;
   tau_etOverPtLeadLooseTrk = 0;
   tau_leadLooseTrkPt = 0;
   tau_chrgLooseTrk = 0;
   tau_massTrkSys = 0;
   tau_trkWidth2 = 0;
   tau_trFlightPathSig = 0;
   tau_etEflow = 0;
   tau_mEflow = 0;
   tau_nPi0 = 0;
   tau_ele_E237E277 = 0;
   tau_ele_PresamplerFraction = 0;
   tau_ele_ECALFirstFraction = 0;
   tau_seedCalo_EMRadius = 0;
   tau_seedCalo_hadRadius = 0;
   tau_seedCalo_etEMAtEMScale = 0;
   tau_seedCalo_etHadAtEMScale = 0;
   tau_seedCalo_isolFrac = 0;
   tau_seedCalo_centFrac = 0;
   tau_seedCalo_stripWidth2 = 0;
   tau_seedCalo_nStrip = 0;
   tau_seedCalo_etEMCalib = 0;
   tau_seedCalo_etHadCalib = 0;
   tau_seedCalo_eta = 0;
   tau_seedCalo_phi = 0;
   tau_seedCalo_nIsolLooseTrk = 0;
   tau_seedCalo_trkAvgDist = 0;
   tau_seedCalo_trkRmsDist = 0;
   tau_seedTrk_EMRadius = 0;
   tau_seedTrk_isolFrac = 0;
   tau_seedTrk_etChrgHadOverSumTrkPt = 0;
   tau_seedTrk_isolFracWide = 0;
   tau_seedTrk_etHadAtEMScale = 0;
   tau_seedTrk_etEMAtEMScale = 0;
   tau_seedTrk_etEMCL = 0;
   tau_seedTrk_etChrgEM = 0;
   tau_seedTrk_etNeuEM = 0;
   tau_seedTrk_etResNeuEM = 0;
   tau_seedTrk_hadLeakEt = 0;
   tau_seedTrk_sumEMCellEtOverLeadTrkPt = 0;
   tau_seedTrk_secMaxStripEt = 0;
   tau_seedTrk_stripWidth2 = 0;
   tau_seedTrk_nStrip = 0;
   tau_seedTrk_etChrgHad = 0;
   tau_seedTrk_nOtherCoreTrk = 0;
   tau_seedTrk_nIsolTrk = 0;
   tau_seedTrk_etIsolEM = 0;
   tau_seedTrk_etIsolHad = 0;
   tau_calcVars_sumTrkPt = 0;
   tau_calcVars_numTopoClusters = 0;
   tau_calcVars_numEffTopoClusters = 0;
   tau_calcVars_topoInvMass = 0;
   tau_calcVars_effTopoInvMass = 0;
   tau_calcVars_topoMeanDeltaR = 0;
   tau_calcVars_effTopoMeanDeltaR = 0;
   tau_calcVars_etHadSumPtTracks = 0;
   tau_calcVars_etEMSumPtTracks = 0;
   tau_track_n = 0;
   tau_EF_dr = 0;
   tau_EF_E = 0;
   tau_EF_Et = 0;
   tau_EF_pt = 0;
   tau_EF_eta = 0;
   tau_EF_phi = 0;
   tau_EF_matched = 0;
   tau_L2_dr = 0;
   tau_L2_E = 0;
   tau_L2_Et = 0;
   tau_L2_pt = 0;
   tau_L2_eta = 0;
   tau_L2_phi = 0;
   tau_L2_matched = 0;
   tau_L1_dr = 0;
   tau_L1_Et = 0;
   tau_L1_pt = 0;
   tau_L1_eta = 0;
   tau_L1_phi = 0;
   tau_L1_matched = 0;
   jet_antikt4h1topo_E = 0;
   jet_antikt4h1topo_pt = 0;
   jet_antikt4h1topo_m = 0;
   jet_antikt4h1topo_eta = 0;
   jet_antikt4h1topo_phi = 0;
   jet_antikt4h1topo_EtaPhys = 0;
   jet_antikt4h1topo_PhiPhys = 0;
   jet_antikt4h1topo_MPhys = 0;
   jet_antikt4h1topo_WIDTH = 0;
   jet_antikt4h1topo_n90 = 0;
   jet_antikt4h1topo_n90constituents = 0;
   jet_antikt4h1topo_fracSamplingMax = 0;
   jet_antikt4h1topo_SamplingMax = 0;
   jet_antikt4h1topo_BCH_CORR_CELL = 0;
   jet_antikt4h1topo_BCH_CORR_DOTX = 0;
   jet_antikt4h1topo_BCH_CORR_JET = 0;
   jet_antikt4h1topo_BCH_CORR_JET_FORCELL = 0;
   jet_antikt4h1topo_ENG_BAD_CELLS = 0;
   jet_antikt4h1topo_N_BAD_CELLS = 0;
   jet_antikt4h1topo_N_BAD_CELLS_CORR = 0;
   jet_antikt4h1topo_BAD_CELLS_CORR_E = 0;
   jet_antikt4h1topo_hecf = 0;
   jet_antikt4h1topo_tgap3f = 0;
   jet_antikt4h1topo_isGood = 0;
   jet_antikt4h1topo_timing = 0;
   jet_antikt4h1topo_quality = 0;
   jet_antikt4h1topo_emfrac = 0;
   jet_antikt4h1topo_GCWJES = 0;
   jet_antikt4h1topo_EMJES = 0;
   jet_antikt4h1topo_CB = 0;
   jet_antikt4h1topo_emscale_E = 0;
   jet_antikt4h1topo_emscale_pt = 0;
   jet_antikt4h1topo_emscale_m = 0;
   jet_antikt4h1topo_emscale_eta = 0;
   jet_antikt4h1topo_emscale_phi = 0;
   jet_antikt4h1topo_jvtxf = 0;
   jet_antikt4h1topo_jvtx_x = 0;
   jet_antikt4h1topo_jvtx_y = 0;
   jet_antikt4h1topo_jvtx_z = 0;
   jet_antikt4h1topo_flavor_weight = 0;
   jet_antikt4h1topo_flavor_weight_TrackCounting2D = 0;
   jet_antikt4h1topo_flavor_weight_JetProb = 0;
   jet_antikt4h1topo_flavor_weight_IP1D = 0;
   jet_antikt4h1topo_flavor_weight_IP2D = 0;
   jet_antikt4h1topo_flavor_weight_IP3D = 0;
   jet_antikt4h1topo_flavor_weight_SV0 = 0;
   jet_antikt4h1topo_flavor_weight_SV1 = 0;
   jet_antikt4h1topo_flavor_weight_SV2 = 0;
   jet_antikt4h1topo_flavor_weight_JetFitterTag = 0;
   jet_antikt4h1topo_flavor_weight_JetFitterCOMB = 0;
   jet_antikt4h1topo_flavor_weight_JetFitterTagNN = 0;
   jet_antikt4h1topo_flavor_weight_JetFitterCOMBNN = 0;
   jet_antikt4h1topo_flavor_weight_SoftMuonTag = 0;
   jet_antikt4h1topo_flavor_weight_SoftElectronTag = 0;
   jet_antikt4h1topo_e_PreSamplerB = 0;
   jet_antikt4h1topo_e_EMB1 = 0;
   jet_antikt4h1topo_e_EMB2 = 0;
   jet_antikt4h1topo_e_EMB3 = 0;
   jet_antikt4h1topo_e_PreSamplerE = 0;
   jet_antikt4h1topo_e_EME1 = 0;
   jet_antikt4h1topo_e_EME2 = 0;
   jet_antikt4h1topo_e_EME3 = 0;
   jet_antikt4h1topo_e_HEC0 = 0;
   jet_antikt4h1topo_e_HEC1 = 0;
   jet_antikt4h1topo_e_HEC2 = 0;
   jet_antikt4h1topo_e_HEC3 = 0;
   jet_antikt4h1topo_e_TileBar0 = 0;
   jet_antikt4h1topo_e_TileBar1 = 0;
   jet_antikt4h1topo_e_TileBar2 = 0;
   jet_antikt4h1topo_e_TileGap1 = 0;
   jet_antikt4h1topo_e_TileGap2 = 0;
   jet_antikt4h1topo_e_TileGap3 = 0;
   jet_antikt4h1topo_e_TileExt0 = 0;
   jet_antikt4h1topo_e_TileExt1 = 0;
   jet_antikt4h1topo_e_TileExt2 = 0;
   jet_antikt4h1topo_e_FCAL0 = 0;
   jet_antikt4h1topo_e_FCAL1 = 0;
   jet_antikt4h1topo_e_FCAL2 = 0;
   jet_antikt4h1topo_shapeBins = 0;
   jet_antikt4h1topo_flavor_component_ip2d_pu = 0;
   jet_antikt4h1topo_flavor_component_ip2d_pb = 0;
   jet_antikt4h1topo_flavor_component_ip2d_ntrk = 0;
   jet_antikt4h1topo_flavor_component_ip3d_pu = 0;
   jet_antikt4h1topo_flavor_component_ip3d_pb = 0;
   jet_antikt4h1topo_flavor_component_ip3d_ntrk = 0;
   jet_antikt4h1topo_flavor_component_sv1_pu = 0;
   jet_antikt4h1topo_flavor_component_sv1_pb = 0;
   jet_antikt4h1topo_flavor_component_sv2_pu = 0;
   jet_antikt4h1topo_flavor_component_sv2_pb = 0;
   jet_antikt4h1topo_flavor_component_svp_mass = 0;
   jet_antikt4h1topo_flavor_component_svp_n2t = 0;
   jet_antikt4h1topo_flavor_component_svp_svok = 0;
   jet_antikt4h1topo_flavor_component_svp_ntrk = 0;
   jet_antikt4h1topo_flavor_component_svp_ntrkv = 0;
   jet_antikt4h1topo_flavor_component_svp_ntrkj = 0;
   jet_antikt4h1topo_flavor_component_svp_efrc = 0;
   jet_antikt4h1topo_flavor_component_sv0p_mass = 0;
   jet_antikt4h1topo_flavor_component_sv0p_n2t = 0;
   jet_antikt4h1topo_flavor_component_sv0p_svok = 0;
   jet_antikt4h1topo_flavor_component_sv0p_ntrk = 0;
   jet_antikt4h1topo_flavor_component_sv0p_ntrkv = 0;
   jet_antikt4h1topo_flavor_component_sv0p_ntrkj = 0;
   jet_antikt4h1topo_flavor_component_sv0p_efrc = 0;
   jet_antikt4h1topo_flavor_component_jfit_pu = 0;
   jet_antikt4h1topo_flavor_component_jfit_pb = 0;
   jet_antikt4h1topo_flavor_component_jfit_nvtxnt = 0;
   jet_antikt4h1topo_flavor_component_jfit_nvtx1t = 0;
   jet_antikt4h1topo_flavor_component_jfit_ntrk = 0;
   jet_antikt4h1topo_flavor_component_jfit_efrc = 0;
   jet_antikt4h1topo_flavor_component_jfit_mass = 0;
   jet_antikt4h1topo_flavor_component_jfit_sig3d = 0;
   jet_antikt4h1topo_constscale_E = 0;
   jet_antikt4h1topo_constscale_pt = 0;
   jet_antikt4h1topo_constscale_m = 0;
   jet_antikt4h1topo_constscale_eta = 0;
   jet_antikt4h1topo_constscale_phi = 0;
   jet_antikt4h1topo_el_dr = 0;
   jet_antikt4h1topo_el_matched = 0;
   jet_antikt4h1topo_mu_dr = 0;
   jet_antikt4h1topo_mu_matched = 0;
   jet_antikt4h1tower_E = 0;
   jet_antikt4h1tower_pt = 0;
   jet_antikt4h1tower_m = 0;
   jet_antikt4h1tower_eta = 0;
   jet_antikt4h1tower_phi = 0;
   jet_antikt4h1tower_EtaPhys = 0;
   jet_antikt4h1tower_PhiPhys = 0;
   jet_antikt4h1tower_MPhys = 0;
   jet_antikt4h1tower_WIDTH = 0;
   jet_antikt4h1tower_n90 = 0;
   jet_antikt4h1tower_n90constituents = 0;
   jet_antikt4h1tower_fracSamplingMax = 0;
   jet_antikt4h1tower_SamplingMax = 0;
   jet_antikt4h1tower_BCH_CORR_CELL = 0;
   jet_antikt4h1tower_BCH_CORR_DOTX = 0;
   jet_antikt4h1tower_BCH_CORR_JET = 0;
   jet_antikt4h1tower_BCH_CORR_JET_FORCELL = 0;
   jet_antikt4h1tower_ENG_BAD_CELLS = 0;
   jet_antikt4h1tower_N_BAD_CELLS = 0;
   jet_antikt4h1tower_N_BAD_CELLS_CORR = 0;
   jet_antikt4h1tower_BAD_CELLS_CORR_E = 0;
   jet_antikt4h1tower_hecf = 0;
   jet_antikt4h1tower_tgap3f = 0;
   jet_antikt4h1tower_isGood = 0;
   jet_antikt4h1tower_timing = 0;
   jet_antikt4h1tower_quality = 0;
   jet_antikt4h1tower_emfrac = 0;
   jet_antikt4h1tower_GCWJES = 0;
   jet_antikt4h1tower_EMJES = 0;
   jet_antikt4h1tower_CB = 0;
   jet_antikt4h1tower_emscale_E = 0;
   jet_antikt4h1tower_emscale_pt = 0;
   jet_antikt4h1tower_emscale_m = 0;
   jet_antikt4h1tower_emscale_eta = 0;
   jet_antikt4h1tower_emscale_phi = 0;
   jet_antikt4h1tower_jvtxf = 0;
   jet_antikt4h1tower_jvtx_x = 0;
   jet_antikt4h1tower_jvtx_y = 0;
   jet_antikt4h1tower_jvtx_z = 0;
   jet_antikt4h1tower_flavor_weight = 0;
   jet_antikt4h1tower_flavor_weight_TrackCounting2D = 0;
   jet_antikt4h1tower_flavor_weight_JetProb = 0;
   jet_antikt4h1tower_flavor_weight_IP1D = 0;
   jet_antikt4h1tower_flavor_weight_IP2D = 0;
   jet_antikt4h1tower_flavor_weight_IP3D = 0;
   jet_antikt4h1tower_flavor_weight_SV0 = 0;
   jet_antikt4h1tower_flavor_weight_SV1 = 0;
   jet_antikt4h1tower_flavor_weight_SV2 = 0;
   jet_antikt4h1tower_flavor_weight_JetFitterTag = 0;
   jet_antikt4h1tower_flavor_weight_JetFitterCOMB = 0;
   jet_antikt4h1tower_flavor_weight_JetFitterTagNN = 0;
   jet_antikt4h1tower_flavor_weight_JetFitterCOMBNN = 0;
   jet_antikt4h1tower_flavor_weight_SoftMuonTag = 0;
   jet_antikt4h1tower_flavor_weight_SoftElectronTag = 0;
   jet_antikt4h1tower_e_PreSamplerB = 0;
   jet_antikt4h1tower_e_EMB1 = 0;
   jet_antikt4h1tower_e_EMB2 = 0;
   jet_antikt4h1tower_e_EMB3 = 0;
   jet_antikt4h1tower_e_PreSamplerE = 0;
   jet_antikt4h1tower_e_EME1 = 0;
   jet_antikt4h1tower_e_EME2 = 0;
   jet_antikt4h1tower_e_EME3 = 0;
   jet_antikt4h1tower_e_HEC0 = 0;
   jet_antikt4h1tower_e_HEC1 = 0;
   jet_antikt4h1tower_e_HEC2 = 0;
   jet_antikt4h1tower_e_HEC3 = 0;
   jet_antikt4h1tower_e_TileBar0 = 0;
   jet_antikt4h1tower_e_TileBar1 = 0;
   jet_antikt4h1tower_e_TileBar2 = 0;
   jet_antikt4h1tower_e_TileGap1 = 0;
   jet_antikt4h1tower_e_TileGap2 = 0;
   jet_antikt4h1tower_e_TileGap3 = 0;
   jet_antikt4h1tower_e_TileExt0 = 0;
   jet_antikt4h1tower_e_TileExt1 = 0;
   jet_antikt4h1tower_e_TileExt2 = 0;
   jet_antikt4h1tower_e_FCAL0 = 0;
   jet_antikt4h1tower_e_FCAL1 = 0;
   jet_antikt4h1tower_e_FCAL2 = 0;
   jet_antikt4h1tower_shapeBins = 0;
   jet_antikt4h1tower_flavor_component_ip2d_pu = 0;
   jet_antikt4h1tower_flavor_component_ip2d_pb = 0;
   jet_antikt4h1tower_flavor_component_ip2d_ntrk = 0;
   jet_antikt4h1tower_flavor_component_ip3d_pu = 0;
   jet_antikt4h1tower_flavor_component_ip3d_pb = 0;
   jet_antikt4h1tower_flavor_component_ip3d_ntrk = 0;
   jet_antikt4h1tower_flavor_component_sv1_pu = 0;
   jet_antikt4h1tower_flavor_component_sv1_pb = 0;
   jet_antikt4h1tower_flavor_component_sv2_pu = 0;
   jet_antikt4h1tower_flavor_component_sv2_pb = 0;
   jet_antikt4h1tower_flavor_component_svp_mass = 0;
   jet_antikt4h1tower_flavor_component_svp_n2t = 0;
   jet_antikt4h1tower_flavor_component_svp_svok = 0;
   jet_antikt4h1tower_flavor_component_svp_ntrk = 0;
   jet_antikt4h1tower_flavor_component_svp_ntrkv = 0;
   jet_antikt4h1tower_flavor_component_svp_ntrkj = 0;
   jet_antikt4h1tower_flavor_component_svp_efrc = 0;
   jet_antikt4h1tower_flavor_component_sv0p_mass = 0;
   jet_antikt4h1tower_flavor_component_sv0p_n2t = 0;
   jet_antikt4h1tower_flavor_component_sv0p_svok = 0;
   jet_antikt4h1tower_flavor_component_sv0p_ntrk = 0;
   jet_antikt4h1tower_flavor_component_sv0p_ntrkv = 0;
   jet_antikt4h1tower_flavor_component_sv0p_ntrkj = 0;
   jet_antikt4h1tower_flavor_component_sv0p_efrc = 0;
   jet_antikt4h1tower_flavor_component_jfit_pu = 0;
   jet_antikt4h1tower_flavor_component_jfit_pb = 0;
   jet_antikt4h1tower_flavor_component_jfit_nvtxnt = 0;
   jet_antikt4h1tower_flavor_component_jfit_nvtx1t = 0;
   jet_antikt4h1tower_flavor_component_jfit_ntrk = 0;
   jet_antikt4h1tower_flavor_component_jfit_efrc = 0;
   jet_antikt4h1tower_flavor_component_jfit_mass = 0;
   jet_antikt4h1tower_flavor_component_jfit_sig3d = 0;
   jet_antikt4h1tower_constscale_E = 0;
   jet_antikt4h1tower_constscale_pt = 0;
   jet_antikt4h1tower_constscale_m = 0;
   jet_antikt4h1tower_constscale_eta = 0;
   jet_antikt4h1tower_constscale_phi = 0;
   jet_antikt4h1tower_el_dr = 0;
   jet_antikt4h1tower_el_matched = 0;
   jet_antikt4h1tower_mu_dr = 0;
   jet_antikt4h1tower_mu_matched = 0;
   jet_antikt6h1tower_E = 0;
   jet_antikt6h1tower_pt = 0;
   jet_antikt6h1tower_m = 0;
   jet_antikt6h1tower_eta = 0;
   jet_antikt6h1tower_phi = 0;
   jet_antikt6h1tower_EtaPhys = 0;
   jet_antikt6h1tower_PhiPhys = 0;
   jet_antikt6h1tower_MPhys = 0;
   jet_antikt6h1tower_WIDTH = 0;
   jet_antikt6h1tower_n90 = 0;
   jet_antikt6h1tower_n90constituents = 0;
   jet_antikt6h1tower_fracSamplingMax = 0;
   jet_antikt6h1tower_SamplingMax = 0;
   jet_antikt6h1tower_BCH_CORR_CELL = 0;
   jet_antikt6h1tower_BCH_CORR_DOTX = 0;
   jet_antikt6h1tower_BCH_CORR_JET = 0;
   jet_antikt6h1tower_BCH_CORR_JET_FORCELL = 0;
   jet_antikt6h1tower_ENG_BAD_CELLS = 0;
   jet_antikt6h1tower_N_BAD_CELLS = 0;
   jet_antikt6h1tower_N_BAD_CELLS_CORR = 0;
   jet_antikt6h1tower_BAD_CELLS_CORR_E = 0;
   jet_antikt6h1tower_hecf = 0;
   jet_antikt6h1tower_tgap3f = 0;
   jet_antikt6h1tower_isGood = 0;
   jet_antikt6h1tower_timing = 0;
   jet_antikt6h1tower_quality = 0;
   jet_antikt6h1tower_emfrac = 0;
   jet_antikt6h1tower_GCWJES = 0;
   jet_antikt6h1tower_EMJES = 0;
   jet_antikt6h1tower_CB = 0;
   jet_antikt6h1tower_emscale_E = 0;
   jet_antikt6h1tower_emscale_pt = 0;
   jet_antikt6h1tower_emscale_m = 0;
   jet_antikt6h1tower_emscale_eta = 0;
   jet_antikt6h1tower_emscale_phi = 0;
   jet_antikt6h1tower_jvtxf = 0;
   jet_antikt6h1tower_jvtx_x = 0;
   jet_antikt6h1tower_jvtx_y = 0;
   jet_antikt6h1tower_jvtx_z = 0;
   jet_antikt6h1tower_flavor_weight = 0;
   jet_antikt6h1tower_flavor_weight_TrackCounting2D = 0;
   jet_antikt6h1tower_flavor_weight_JetProb = 0;
   jet_antikt6h1tower_flavor_weight_IP1D = 0;
   jet_antikt6h1tower_flavor_weight_IP2D = 0;
   jet_antikt6h1tower_flavor_weight_IP3D = 0;
   jet_antikt6h1tower_flavor_weight_SV0 = 0;
   jet_antikt6h1tower_flavor_weight_SV1 = 0;
   jet_antikt6h1tower_flavor_weight_SV2 = 0;
   jet_antikt6h1tower_flavor_weight_JetFitterTag = 0;
   jet_antikt6h1tower_flavor_weight_JetFitterCOMB = 0;
   jet_antikt6h1tower_flavor_weight_JetFitterTagNN = 0;
   jet_antikt6h1tower_flavor_weight_JetFitterCOMBNN = 0;
   jet_antikt6h1tower_flavor_weight_SoftMuonTag = 0;
   jet_antikt6h1tower_flavor_weight_SoftElectronTag = 0;
   jet_antikt6h1tower_e_PreSamplerB = 0;
   jet_antikt6h1tower_e_EMB1 = 0;
   jet_antikt6h1tower_e_EMB2 = 0;
   jet_antikt6h1tower_e_EMB3 = 0;
   jet_antikt6h1tower_e_PreSamplerE = 0;
   jet_antikt6h1tower_e_EME1 = 0;
   jet_antikt6h1tower_e_EME2 = 0;
   jet_antikt6h1tower_e_EME3 = 0;
   jet_antikt6h1tower_e_HEC0 = 0;
   jet_antikt6h1tower_e_HEC1 = 0;
   jet_antikt6h1tower_e_HEC2 = 0;
   jet_antikt6h1tower_e_HEC3 = 0;
   jet_antikt6h1tower_e_TileBar0 = 0;
   jet_antikt6h1tower_e_TileBar1 = 0;
   jet_antikt6h1tower_e_TileBar2 = 0;
   jet_antikt6h1tower_e_TileGap1 = 0;
   jet_antikt6h1tower_e_TileGap2 = 0;
   jet_antikt6h1tower_e_TileGap3 = 0;
   jet_antikt6h1tower_e_TileExt0 = 0;
   jet_antikt6h1tower_e_TileExt1 = 0;
   jet_antikt6h1tower_e_TileExt2 = 0;
   jet_antikt6h1tower_e_FCAL0 = 0;
   jet_antikt6h1tower_e_FCAL1 = 0;
   jet_antikt6h1tower_e_FCAL2 = 0;
   jet_antikt6h1tower_shapeBins = 0;
   jet_antikt6h1tower_flavor_component_ip2d_pu = 0;
   jet_antikt6h1tower_flavor_component_ip2d_pb = 0;
   jet_antikt6h1tower_flavor_component_ip2d_ntrk = 0;
   jet_antikt6h1tower_flavor_component_ip3d_pu = 0;
   jet_antikt6h1tower_flavor_component_ip3d_pb = 0;
   jet_antikt6h1tower_flavor_component_ip3d_ntrk = 0;
   jet_antikt6h1tower_flavor_component_sv1_pu = 0;
   jet_antikt6h1tower_flavor_component_sv1_pb = 0;
   jet_antikt6h1tower_flavor_component_sv2_pu = 0;
   jet_antikt6h1tower_flavor_component_sv2_pb = 0;
   jet_antikt6h1tower_flavor_component_svp_mass = 0;
   jet_antikt6h1tower_flavor_component_svp_n2t = 0;
   jet_antikt6h1tower_flavor_component_svp_svok = 0;
   jet_antikt6h1tower_flavor_component_svp_ntrk = 0;
   jet_antikt6h1tower_flavor_component_svp_ntrkv = 0;
   jet_antikt6h1tower_flavor_component_svp_ntrkj = 0;
   jet_antikt6h1tower_flavor_component_svp_efrc = 0;
   jet_antikt6h1tower_flavor_component_sv0p_mass = 0;
   jet_antikt6h1tower_flavor_component_sv0p_n2t = 0;
   jet_antikt6h1tower_flavor_component_sv0p_svok = 0;
   jet_antikt6h1tower_flavor_component_sv0p_ntrk = 0;
   jet_antikt6h1tower_flavor_component_sv0p_ntrkv = 0;
   jet_antikt6h1tower_flavor_component_sv0p_ntrkj = 0;
   jet_antikt6h1tower_flavor_component_sv0p_efrc = 0;
   jet_antikt6h1tower_flavor_component_jfit_pu = 0;
   jet_antikt6h1tower_flavor_component_jfit_pb = 0;
   jet_antikt6h1tower_flavor_component_jfit_nvtxnt = 0;
   jet_antikt6h1tower_flavor_component_jfit_nvtx1t = 0;
   jet_antikt6h1tower_flavor_component_jfit_ntrk = 0;
   jet_antikt6h1tower_flavor_component_jfit_efrc = 0;
   jet_antikt6h1tower_flavor_component_jfit_mass = 0;
   jet_antikt6h1tower_flavor_component_jfit_sig3d = 0;
   jet_antikt6h1tower_constscale_E = 0;
   jet_antikt6h1tower_constscale_pt = 0;
   jet_antikt6h1tower_constscale_m = 0;
   jet_antikt6h1tower_constscale_eta = 0;
   jet_antikt6h1tower_constscale_phi = 0;
   jet_antikt6h1tower_el_dr = 0;
   jet_antikt6h1tower_el_matched = 0;
   jet_antikt6h1tower_mu_dr = 0;
   jet_antikt6h1tower_mu_matched = 0;
   jet_antikt4lctopo_E = 0;
   jet_antikt4lctopo_pt = 0;
   jet_antikt4lctopo_m = 0;
   jet_antikt4lctopo_eta = 0;
   jet_antikt4lctopo_phi = 0;
   jet_antikt4lctopo_EtaPhys = 0;
   jet_antikt4lctopo_PhiPhys = 0;
   jet_antikt4lctopo_MPhys = 0;
   jet_antikt4lctopo_WIDTH = 0;
   jet_antikt4lctopo_n90 = 0;
   jet_antikt4lctopo_n90constituents = 0;
   jet_antikt4lctopo_fracSamplingMax = 0;
   jet_antikt4lctopo_SamplingMax = 0;
   jet_antikt4lctopo_BCH_CORR_CELL = 0;
   jet_antikt4lctopo_BCH_CORR_DOTX = 0;
   jet_antikt4lctopo_BCH_CORR_JET = 0;
   jet_antikt4lctopo_BCH_CORR_JET_FORCELL = 0;
   jet_antikt4lctopo_ENG_BAD_CELLS = 0;
   jet_antikt4lctopo_N_BAD_CELLS = 0;
   jet_antikt4lctopo_N_BAD_CELLS_CORR = 0;
   jet_antikt4lctopo_BAD_CELLS_CORR_E = 0;
   jet_antikt4lctopo_hecf = 0;
   jet_antikt4lctopo_tgap3f = 0;
   jet_antikt4lctopo_isGood = 0;
   jet_antikt4lctopo_timing = 0;
   jet_antikt4lctopo_quality = 0;
   jet_antikt4lctopo_emfrac = 0;
   jet_antikt4lctopo_GCWJES = 0;
   jet_antikt4lctopo_EMJES = 0;
   jet_antikt4lctopo_CB = 0;
   jet_antikt4lctopo_emscale_E = 0;
   jet_antikt4lctopo_emscale_pt = 0;
   jet_antikt4lctopo_emscale_m = 0;
   jet_antikt4lctopo_emscale_eta = 0;
   jet_antikt4lctopo_emscale_phi = 0;
   jet_antikt4lctopo_jvtxf = 0;
   jet_antikt4lctopo_jvtx_x = 0;
   jet_antikt4lctopo_jvtx_y = 0;
   jet_antikt4lctopo_jvtx_z = 0;
   jet_antikt4lctopo_flavor_weight = 0;
   jet_antikt4lctopo_flavor_weight_TrackCounting2D = 0;
   jet_antikt4lctopo_flavor_weight_JetProb = 0;
   jet_antikt4lctopo_flavor_weight_IP1D = 0;
   jet_antikt4lctopo_flavor_weight_IP2D = 0;
   jet_antikt4lctopo_flavor_weight_IP3D = 0;
   jet_antikt4lctopo_flavor_weight_SV0 = 0;
   jet_antikt4lctopo_flavor_weight_SV1 = 0;
   jet_antikt4lctopo_flavor_weight_SV2 = 0;
   jet_antikt4lctopo_flavor_weight_JetFitterTag = 0;
   jet_antikt4lctopo_flavor_weight_JetFitterCOMB = 0;
   jet_antikt4lctopo_flavor_weight_JetFitterTagNN = 0;
   jet_antikt4lctopo_flavor_weight_JetFitterCOMBNN = 0;
   jet_antikt4lctopo_flavor_weight_SoftMuonTag = 0;
   jet_antikt4lctopo_flavor_weight_SoftElectronTag = 0;
   jet_antikt4lctopo_e_PreSamplerB = 0;
   jet_antikt4lctopo_e_EMB1 = 0;
   jet_antikt4lctopo_e_EMB2 = 0;
   jet_antikt4lctopo_e_EMB3 = 0;
   jet_antikt4lctopo_e_PreSamplerE = 0;
   jet_antikt4lctopo_e_EME1 = 0;
   jet_antikt4lctopo_e_EME2 = 0;
   jet_antikt4lctopo_e_EME3 = 0;
   jet_antikt4lctopo_e_HEC0 = 0;
   jet_antikt4lctopo_e_HEC1 = 0;
   jet_antikt4lctopo_e_HEC2 = 0;
   jet_antikt4lctopo_e_HEC3 = 0;
   jet_antikt4lctopo_e_TileBar0 = 0;
   jet_antikt4lctopo_e_TileBar1 = 0;
   jet_antikt4lctopo_e_TileBar2 = 0;
   jet_antikt4lctopo_e_TileGap1 = 0;
   jet_antikt4lctopo_e_TileGap2 = 0;
   jet_antikt4lctopo_e_TileGap3 = 0;
   jet_antikt4lctopo_e_TileExt0 = 0;
   jet_antikt4lctopo_e_TileExt1 = 0;
   jet_antikt4lctopo_e_TileExt2 = 0;
   jet_antikt4lctopo_e_FCAL0 = 0;
   jet_antikt4lctopo_e_FCAL1 = 0;
   jet_antikt4lctopo_e_FCAL2 = 0;
   jet_antikt4lctopo_shapeBins = 0;
   jet_antikt4lctopo_flavor_component_ip2d_pu = 0;
   jet_antikt4lctopo_flavor_component_ip2d_pb = 0;
   jet_antikt4lctopo_flavor_component_ip2d_ntrk = 0;
   jet_antikt4lctopo_flavor_component_ip3d_pu = 0;
   jet_antikt4lctopo_flavor_component_ip3d_pb = 0;
   jet_antikt4lctopo_flavor_component_ip3d_ntrk = 0;
   jet_antikt4lctopo_flavor_component_sv1_pu = 0;
   jet_antikt4lctopo_flavor_component_sv1_pb = 0;
   jet_antikt4lctopo_flavor_component_sv2_pu = 0;
   jet_antikt4lctopo_flavor_component_sv2_pb = 0;
   jet_antikt4lctopo_flavor_component_svp_mass = 0;
   jet_antikt4lctopo_flavor_component_svp_n2t = 0;
   jet_antikt4lctopo_flavor_component_svp_svok = 0;
   jet_antikt4lctopo_flavor_component_svp_ntrk = 0;
   jet_antikt4lctopo_flavor_component_svp_ntrkv = 0;
   jet_antikt4lctopo_flavor_component_svp_ntrkj = 0;
   jet_antikt4lctopo_flavor_component_svp_efrc = 0;
   jet_antikt4lctopo_flavor_component_sv0p_mass = 0;
   jet_antikt4lctopo_flavor_component_sv0p_n2t = 0;
   jet_antikt4lctopo_flavor_component_sv0p_svok = 0;
   jet_antikt4lctopo_flavor_component_sv0p_ntrk = 0;
   jet_antikt4lctopo_flavor_component_sv0p_ntrkv = 0;
   jet_antikt4lctopo_flavor_component_sv0p_ntrkj = 0;
   jet_antikt4lctopo_flavor_component_sv0p_efrc = 0;
   jet_antikt4lctopo_flavor_component_jfit_pu = 0;
   jet_antikt4lctopo_flavor_component_jfit_pb = 0;
   jet_antikt4lctopo_flavor_component_jfit_nvtxnt = 0;
   jet_antikt4lctopo_flavor_component_jfit_nvtx1t = 0;
   jet_antikt4lctopo_flavor_component_jfit_ntrk = 0;
   jet_antikt4lctopo_flavor_component_jfit_efrc = 0;
   jet_antikt4lctopo_flavor_component_jfit_mass = 0;
   jet_antikt4lctopo_flavor_component_jfit_sig3d = 0;
   jet_antikt4lctopo_constscale_E = 0;
   jet_antikt4lctopo_constscale_pt = 0;
   jet_antikt4lctopo_constscale_m = 0;
   jet_antikt4lctopo_constscale_eta = 0;
   jet_antikt4lctopo_constscale_phi = 0;
   jet_antikt4lctopo_el_dr = 0;
   jet_antikt4lctopo_el_matched = 0;
   jet_antikt4lctopo_mu_dr = 0;
   jet_antikt4lctopo_mu_matched = 0;
   jet_antikt6lctopo_E = 0;
   jet_antikt6lctopo_pt = 0;
   jet_antikt6lctopo_m = 0;
   jet_antikt6lctopo_eta = 0;
   jet_antikt6lctopo_phi = 0;
   jet_antikt6lctopo_EtaPhys = 0;
   jet_antikt6lctopo_PhiPhys = 0;
   jet_antikt6lctopo_MPhys = 0;
   jet_antikt6lctopo_WIDTH = 0;
   jet_antikt6lctopo_n90 = 0;
   jet_antikt6lctopo_n90constituents = 0;
   jet_antikt6lctopo_fracSamplingMax = 0;
   jet_antikt6lctopo_SamplingMax = 0;
   jet_antikt6lctopo_BCH_CORR_CELL = 0;
   jet_antikt6lctopo_BCH_CORR_DOTX = 0;
   jet_antikt6lctopo_BCH_CORR_JET = 0;
   jet_antikt6lctopo_BCH_CORR_JET_FORCELL = 0;
   jet_antikt6lctopo_ENG_BAD_CELLS = 0;
   jet_antikt6lctopo_N_BAD_CELLS = 0;
   jet_antikt6lctopo_N_BAD_CELLS_CORR = 0;
   jet_antikt6lctopo_BAD_CELLS_CORR_E = 0;
   jet_antikt6lctopo_hecf = 0;
   jet_antikt6lctopo_tgap3f = 0;
   jet_antikt6lctopo_isGood = 0;
   jet_antikt6lctopo_timing = 0;
   jet_antikt6lctopo_quality = 0;
   jet_antikt6lctopo_emfrac = 0;
   jet_antikt6lctopo_GCWJES = 0;
   jet_antikt6lctopo_EMJES = 0;
   jet_antikt6lctopo_CB = 0;
   jet_antikt6lctopo_emscale_E = 0;
   jet_antikt6lctopo_emscale_pt = 0;
   jet_antikt6lctopo_emscale_m = 0;
   jet_antikt6lctopo_emscale_eta = 0;
   jet_antikt6lctopo_emscale_phi = 0;
   jet_antikt6lctopo_jvtxf = 0;
   jet_antikt6lctopo_jvtx_x = 0;
   jet_antikt6lctopo_jvtx_y = 0;
   jet_antikt6lctopo_jvtx_z = 0;
   jet_antikt6lctopo_flavor_weight = 0;
   jet_antikt6lctopo_flavor_weight_TrackCounting2D = 0;
   jet_antikt6lctopo_flavor_weight_JetProb = 0;
   jet_antikt6lctopo_flavor_weight_IP1D = 0;
   jet_antikt6lctopo_flavor_weight_IP2D = 0;
   jet_antikt6lctopo_flavor_weight_IP3D = 0;
   jet_antikt6lctopo_flavor_weight_SV0 = 0;
   jet_antikt6lctopo_flavor_weight_SV1 = 0;
   jet_antikt6lctopo_flavor_weight_SV2 = 0;
   jet_antikt6lctopo_flavor_weight_JetFitterTag = 0;
   jet_antikt6lctopo_flavor_weight_JetFitterCOMB = 0;
   jet_antikt6lctopo_flavor_weight_JetFitterTagNN = 0;
   jet_antikt6lctopo_flavor_weight_JetFitterCOMBNN = 0;
   jet_antikt6lctopo_flavor_weight_SoftMuonTag = 0;
   jet_antikt6lctopo_flavor_weight_SoftElectronTag = 0;
   jet_antikt6lctopo_e_PreSamplerB = 0;
   jet_antikt6lctopo_e_EMB1 = 0;
   jet_antikt6lctopo_e_EMB2 = 0;
   jet_antikt6lctopo_e_EMB3 = 0;
   jet_antikt6lctopo_e_PreSamplerE = 0;
   jet_antikt6lctopo_e_EME1 = 0;
   jet_antikt6lctopo_e_EME2 = 0;
   jet_antikt6lctopo_e_EME3 = 0;
   jet_antikt6lctopo_e_HEC0 = 0;
   jet_antikt6lctopo_e_HEC1 = 0;
   jet_antikt6lctopo_e_HEC2 = 0;
   jet_antikt6lctopo_e_HEC3 = 0;
   jet_antikt6lctopo_e_TileBar0 = 0;
   jet_antikt6lctopo_e_TileBar1 = 0;
   jet_antikt6lctopo_e_TileBar2 = 0;
   jet_antikt6lctopo_e_TileGap1 = 0;
   jet_antikt6lctopo_e_TileGap2 = 0;
   jet_antikt6lctopo_e_TileGap3 = 0;
   jet_antikt6lctopo_e_TileExt0 = 0;
   jet_antikt6lctopo_e_TileExt1 = 0;
   jet_antikt6lctopo_e_TileExt2 = 0;
   jet_antikt6lctopo_e_FCAL0 = 0;
   jet_antikt6lctopo_e_FCAL1 = 0;
   jet_antikt6lctopo_e_FCAL2 = 0;
   jet_antikt6lctopo_shapeBins = 0;
   jet_antikt6lctopo_flavor_component_ip2d_pu = 0;
   jet_antikt6lctopo_flavor_component_ip2d_pb = 0;
   jet_antikt6lctopo_flavor_component_ip2d_ntrk = 0;
   jet_antikt6lctopo_flavor_component_ip3d_pu = 0;
   jet_antikt6lctopo_flavor_component_ip3d_pb = 0;
   jet_antikt6lctopo_flavor_component_ip3d_ntrk = 0;
   jet_antikt6lctopo_flavor_component_sv1_pu = 0;
   jet_antikt6lctopo_flavor_component_sv1_pb = 0;
   jet_antikt6lctopo_flavor_component_sv2_pu = 0;
   jet_antikt6lctopo_flavor_component_sv2_pb = 0;
   jet_antikt6lctopo_flavor_component_svp_mass = 0;
   jet_antikt6lctopo_flavor_component_svp_n2t = 0;
   jet_antikt6lctopo_flavor_component_svp_svok = 0;
   jet_antikt6lctopo_flavor_component_svp_ntrk = 0;
   jet_antikt6lctopo_flavor_component_svp_ntrkv = 0;
   jet_antikt6lctopo_flavor_component_svp_ntrkj = 0;
   jet_antikt6lctopo_flavor_component_svp_efrc = 0;
   jet_antikt6lctopo_flavor_component_sv0p_mass = 0;
   jet_antikt6lctopo_flavor_component_sv0p_n2t = 0;
   jet_antikt6lctopo_flavor_component_sv0p_svok = 0;
   jet_antikt6lctopo_flavor_component_sv0p_ntrk = 0;
   jet_antikt6lctopo_flavor_component_sv0p_ntrkv = 0;
   jet_antikt6lctopo_flavor_component_sv0p_ntrkj = 0;
   jet_antikt6lctopo_flavor_component_sv0p_efrc = 0;
   jet_antikt6lctopo_flavor_component_jfit_pu = 0;
   jet_antikt6lctopo_flavor_component_jfit_pb = 0;
   jet_antikt6lctopo_flavor_component_jfit_nvtxnt = 0;
   jet_antikt6lctopo_flavor_component_jfit_nvtx1t = 0;
   jet_antikt6lctopo_flavor_component_jfit_ntrk = 0;
   jet_antikt6lctopo_flavor_component_jfit_efrc = 0;
   jet_antikt6lctopo_flavor_component_jfit_mass = 0;
   jet_antikt6lctopo_flavor_component_jfit_sig3d = 0;
   jet_antikt6lctopo_constscale_E = 0;
   jet_antikt6lctopo_constscale_pt = 0;
   jet_antikt6lctopo_constscale_m = 0;
   jet_antikt6lctopo_constscale_eta = 0;
   jet_antikt6lctopo_constscale_phi = 0;
   jet_antikt6lctopo_el_dr = 0;
   jet_antikt6lctopo_el_matched = 0;
   jet_antikt6lctopo_mu_dr = 0;
   jet_antikt6lctopo_mu_matched = 0;
   jet_antikt6h1topo_E = 0;
   jet_antikt6h1topo_pt = 0;
   jet_antikt6h1topo_m = 0;
   jet_antikt6h1topo_eta = 0;
   jet_antikt6h1topo_phi = 0;
   jet_antikt6h1topo_EtaPhys = 0;
   jet_antikt6h1topo_PhiPhys = 0;
   jet_antikt6h1topo_MPhys = 0;
   jet_antikt6h1topo_WIDTH = 0;
   jet_antikt6h1topo_n90 = 0;
   jet_antikt6h1topo_n90constituents = 0;
   jet_antikt6h1topo_fracSamplingMax = 0;
   jet_antikt6h1topo_SamplingMax = 0;
   jet_antikt6h1topo_BCH_CORR_CELL = 0;
   jet_antikt6h1topo_BCH_CORR_DOTX = 0;
   jet_antikt6h1topo_BCH_CORR_JET = 0;
   jet_antikt6h1topo_BCH_CORR_JET_FORCELL = 0;
   jet_antikt6h1topo_ENG_BAD_CELLS = 0;
   jet_antikt6h1topo_N_BAD_CELLS = 0;
   jet_antikt6h1topo_N_BAD_CELLS_CORR = 0;
   jet_antikt6h1topo_BAD_CELLS_CORR_E = 0;
   jet_antikt6h1topo_hecf = 0;
   jet_antikt6h1topo_tgap3f = 0;
   jet_antikt6h1topo_isGood = 0;
   jet_antikt6h1topo_timing = 0;
   jet_antikt6h1topo_quality = 0;
   jet_antikt6h1topo_emfrac = 0;
   jet_antikt6h1topo_GCWJES = 0;
   jet_antikt6h1topo_EMJES = 0;
   jet_antikt6h1topo_CB = 0;
   jet_antikt6h1topo_emscale_E = 0;
   jet_antikt6h1topo_emscale_pt = 0;
   jet_antikt6h1topo_emscale_m = 0;
   jet_antikt6h1topo_emscale_eta = 0;
   jet_antikt6h1topo_emscale_phi = 0;
   jet_antikt6h1topo_jvtxf = 0;
   jet_antikt6h1topo_jvtx_x = 0;
   jet_antikt6h1topo_jvtx_y = 0;
   jet_antikt6h1topo_jvtx_z = 0;
   jet_antikt6h1topo_flavor_weight = 0;
   jet_antikt6h1topo_flavor_weight_TrackCounting2D = 0;
   jet_antikt6h1topo_flavor_weight_JetProb = 0;
   jet_antikt6h1topo_flavor_weight_IP1D = 0;
   jet_antikt6h1topo_flavor_weight_IP2D = 0;
   jet_antikt6h1topo_flavor_weight_IP3D = 0;
   jet_antikt6h1topo_flavor_weight_SV0 = 0;
   jet_antikt6h1topo_flavor_weight_SV1 = 0;
   jet_antikt6h1topo_flavor_weight_SV2 = 0;
   jet_antikt6h1topo_flavor_weight_JetFitterTag = 0;
   jet_antikt6h1topo_flavor_weight_JetFitterCOMB = 0;
   jet_antikt6h1topo_flavor_weight_JetFitterTagNN = 0;
   jet_antikt6h1topo_flavor_weight_JetFitterCOMBNN = 0;
   jet_antikt6h1topo_flavor_weight_SoftMuonTag = 0;
   jet_antikt6h1topo_flavor_weight_SoftElectronTag = 0;
   jet_antikt6h1topo_e_PreSamplerB = 0;
   jet_antikt6h1topo_e_EMB1 = 0;
   jet_antikt6h1topo_e_EMB2 = 0;
   jet_antikt6h1topo_e_EMB3 = 0;
   jet_antikt6h1topo_e_PreSamplerE = 0;
   jet_antikt6h1topo_e_EME1 = 0;
   jet_antikt6h1topo_e_EME2 = 0;
   jet_antikt6h1topo_e_EME3 = 0;
   jet_antikt6h1topo_e_HEC0 = 0;
   jet_antikt6h1topo_e_HEC1 = 0;
   jet_antikt6h1topo_e_HEC2 = 0;
   jet_antikt6h1topo_e_HEC3 = 0;
   jet_antikt6h1topo_e_TileBar0 = 0;
   jet_antikt6h1topo_e_TileBar1 = 0;
   jet_antikt6h1topo_e_TileBar2 = 0;
   jet_antikt6h1topo_e_TileGap1 = 0;
   jet_antikt6h1topo_e_TileGap2 = 0;
   jet_antikt6h1topo_e_TileGap3 = 0;
   jet_antikt6h1topo_e_TileExt0 = 0;
   jet_antikt6h1topo_e_TileExt1 = 0;
   jet_antikt6h1topo_e_TileExt2 = 0;
   jet_antikt6h1topo_e_FCAL0 = 0;
   jet_antikt6h1topo_e_FCAL1 = 0;
   jet_antikt6h1topo_e_FCAL2 = 0;
   jet_antikt6h1topo_shapeBins = 0;
   jet_antikt6h1topo_flavor_component_ip2d_pu = 0;
   jet_antikt6h1topo_flavor_component_ip2d_pb = 0;
   jet_antikt6h1topo_flavor_component_ip2d_ntrk = 0;
   jet_antikt6h1topo_flavor_component_ip3d_pu = 0;
   jet_antikt6h1topo_flavor_component_ip3d_pb = 0;
   jet_antikt6h1topo_flavor_component_ip3d_ntrk = 0;
   jet_antikt6h1topo_flavor_component_sv1_pu = 0;
   jet_antikt6h1topo_flavor_component_sv1_pb = 0;
   jet_antikt6h1topo_flavor_component_sv2_pu = 0;
   jet_antikt6h1topo_flavor_component_sv2_pb = 0;
   jet_antikt6h1topo_flavor_component_svp_mass = 0;
   jet_antikt6h1topo_flavor_component_svp_n2t = 0;
   jet_antikt6h1topo_flavor_component_svp_svok = 0;
   jet_antikt6h1topo_flavor_component_svp_ntrk = 0;
   jet_antikt6h1topo_flavor_component_svp_ntrkv = 0;
   jet_antikt6h1topo_flavor_component_svp_ntrkj = 0;
   jet_antikt6h1topo_flavor_component_svp_efrc = 0;
   jet_antikt6h1topo_flavor_component_sv0p_mass = 0;
   jet_antikt6h1topo_flavor_component_sv0p_n2t = 0;
   jet_antikt6h1topo_flavor_component_sv0p_svok = 0;
   jet_antikt6h1topo_flavor_component_sv0p_ntrk = 0;
   jet_antikt6h1topo_flavor_component_sv0p_ntrkv = 0;
   jet_antikt6h1topo_flavor_component_sv0p_ntrkj = 0;
   jet_antikt6h1topo_flavor_component_sv0p_efrc = 0;
   jet_antikt6h1topo_flavor_component_jfit_pu = 0;
   jet_antikt6h1topo_flavor_component_jfit_pb = 0;
   jet_antikt6h1topo_flavor_component_jfit_nvtxnt = 0;
   jet_antikt6h1topo_flavor_component_jfit_nvtx1t = 0;
   jet_antikt6h1topo_flavor_component_jfit_ntrk = 0;
   jet_antikt6h1topo_flavor_component_jfit_efrc = 0;
   jet_antikt6h1topo_flavor_component_jfit_mass = 0;
   jet_antikt6h1topo_flavor_component_jfit_sig3d = 0;
   jet_antikt6h1topo_constscale_E = 0;
   jet_antikt6h1topo_constscale_pt = 0;
   jet_antikt6h1topo_constscale_m = 0;
   jet_antikt6h1topo_constscale_eta = 0;
   jet_antikt6h1topo_constscale_phi = 0;
   jet_antikt6h1topo_el_dr = 0;
   jet_antikt6h1topo_el_matched = 0;
   jet_antikt6h1topo_mu_dr = 0;
   jet_antikt6h1topo_mu_matched = 0;
   cl_E = 0;
   cl_pt = 0;
   cl_m = 0;
   cl_eta = 0;
   cl_phi = 0;
   cl_E_em = 0;
   cl_E_had = 0;
   cl_firstEdens = 0;
   cl_cellmaxfrac = 0;
   cl_longitudinal = 0;
   cl_secondlambda = 0;
   cl_lateral = 0;
   cl_secondR = 0;
   cl_centerlambda = 0;
   cl_deltaTheta = 0;
   cl_deltaPhi = 0;
   cl_time = 0;
   emcl_E = 0;
   emcl_pt = 0;
   emcl_m = 0;
   emcl_eta = 0;
   emcl_phi = 0;
   emcl_E_em = 0;
   emcl_E_had = 0;
   emcl_firstEdens = 0;
   emcl_cellmaxfrac = 0;
   emcl_longitudinal = 0;
   emcl_secondlambda = 0;
   emcl_lateral = 0;
   emcl_secondR = 0;
   emcl_centerlambda = 0;
   emcl_deltaTheta = 0;
   emcl_deltaPhi = 0;
   emcl_time = 0;
   emcl_E_PreSamplerB = 0;
   emcl_E_EMB1 = 0;
   emcl_E_EMB2 = 0;
   emcl_E_EMB3 = 0;
   emcl_E_PreSamplerE = 0;
   emcl_E_EME1 = 0;
   emcl_E_EME2 = 0;
   emcl_E_EME3 = 0;
   emcl_E_HEC0 = 0;
   emcl_E_HEC1 = 0;
   emcl_E_HEC2 = 0;
   emcl_E_HEC3 = 0;
   emcl_E_TileBar0 = 0;
   emcl_E_TileBar1 = 0;
   emcl_E_TileBar2 = 0;
   emcl_E_TileGap1 = 0;
   emcl_E_TileGap2 = 0;
   emcl_E_TileGap3 = 0;
   emcl_E_TileExt0 = 0;
   emcl_E_TileExt1 = 0;
   emcl_E_TileExt2 = 0;
   emcl_E_FCAL0 = 0;
   emcl_E_FCAL1 = 0;
   emcl_E_FCAL2 = 0;
   trk_d0 = 0;
   trk_z0 = 0;
   trk_phi = 0;
   trk_theta = 0;
   trk_qoverp = 0;
   trk_pt = 0;
   trk_eta = 0;
   trk_err_d0 = 0;
   trk_err_z0 = 0;
   trk_err_phi = 0;
   trk_err_theta = 0;
   trk_err_qoverp = 0;
   trk_cov_d0 = 0;
   trk_cov_z0 = 0;
   trk_cov_phi = 0;
   trk_cov_theta = 0;
   trk_cov_qoverp = 0;
   trk_cov_d0_z0 = 0;
   trk_cov_d0_phi = 0;
   trk_cov_d0_theta = 0;
   trk_cov_d0_qoverp = 0;
   trk_cov_z0_phi = 0;
   trk_cov_z0_theta = 0;
   trk_cov_z0_qoverp = 0;
   trk_cov_phi_theta = 0;
   trk_cov_phi_qoverp = 0;
   trk_cov_theta_qoverp = 0;
   trk_blayerPrediction_expectHit = 0;
   trk_blayerPrediction_x = 0;
   trk_blayerPrediction_y = 0;
   trk_blayerPrediction_z = 0;
   trk_blayerPrediction_locX = 0;
   trk_blayerPrediction_locY = 0;
   trk_blayerPrediction_err_locX = 0;
   trk_blayerPrediction_err_locY = 0;
   trk_blayerPrediction_etaDistToEdge = 0;
   trk_blayerPrediction_phiDistToEdge = 0;
   trk_blayerPrediction_detElementId = 0;
   trk_blayerPrediction_row = 0;
   trk_blayerPrediction_col = 0;
   trk_blayerPrediction_type = 0;
   trk_d0_wrtPV = 0;
   trk_z0_wrtPV = 0;
   trk_phi_wrtPV = 0;
   trk_theta_wrtPV = 0;
   trk_qoverp_wrtPV = 0;
   trk_chi2 = 0;
   trk_ndof = 0;
   trk_nBLHits = 0;
   trk_nPixHits = 0;
   trk_nSCTHits = 0;
   trk_nTRTHits = 0;
   trk_nPixHoles = 0;
   trk_nSCTHoles = 0;
   trk_nMDTHits = 0;
   trk_nCSCEtaHits = 0;
   trk_nCSCPhiHits = 0;
   trk_nRPCEtaHits = 0;
   trk_nRPCPhiHits = 0;
   trk_nTGCEtaHits = 0;
   trk_nTGCPhiHits = 0;
   trk_nHits = 0;
   trk_nHoles = 0;
   trk_hitPattern = 0;
   trk_TRTHighTHitsRatio = 0;
   trk_pixeldEdx = 0;
   trk_fitter = 0;
   trk_patternReco1 = 0;
   trk_patternReco2 = 0;
   trk_seedFinder = 0;
   mb_E = 0;
   mb_eta = 0;
   mb_phi = 0;
   mb_time = 0;
   mb_quality = 0;
   mb_type = 0;
   mb_module = 0;
   mb_channel = 0;
   vxp_x = 0;
   vxp_y = 0;
   vxp_z = 0;
   vxp_chi2 = 0;
   vxp_ndof = 0;
   vxp_err_x = 0;
   vxp_err_y = 0;
   vxp_err_z = 0;
   vxp_px = 0;
   vxp_py = 0;
   vxp_pz = 0;
   vxp_E = 0;
   vxp_m = 0;
   vxp_nTracks = 0;
   vxp_sumPt = 0;
   vxp_type = 0;
   vxp_trk_n = 0;
   vxp_trk_chi2 = 0;
   vxp_trk_d0 = 0;
   vxp_trk_z0 = 0;
   vxp_trk_unbiased_d0 = 0;
   vxp_trk_unbiased_z0 = 0;
   vxp_trk_err_unbiased_d0 = 0;
   vxp_trk_err_unbiased_z0 = 0;
   vxp_trk_phi = 0;
   vxp_trk_theta = 0;
   vxp_trk_weight = 0;
   vxp_trk_index = 0;
   trig_L1_emtau_eta = 0;
   trig_L1_emtau_phi = 0;
   trig_L1_emtau_thrNames = 0;
   trig_L1_emtau_thrValues = 0;
   trig_L1_emtau_core = 0;
   trig_L1_emtau_EMClus = 0;
   trig_L1_emtau_tauClus = 0;
   trig_L1_emtau_EMIsol = 0;
   trig_L1_emtau_hadIsol = 0;
   trig_L1_emtau_hadCore = 0;
   trig_L1_emtau_thrPattern = 0;
   trig_L1_emtau_L1_2EM10 = 0;
   trig_L1_emtau_L1_2EM14 = 0;
   trig_L1_emtau_L1_2EM2 = 0;
   trig_L1_emtau_L1_2EM3 = 0;
   trig_L1_emtau_L1_2EM5 = 0;
   trig_L1_emtau_L1_EM10 = 0;
   trig_L1_emtau_L1_EM10I = 0;
   trig_L1_emtau_L1_EM14 = 0;
   trig_L1_emtau_L1_EM14I = 0;
   trig_L1_emtau_L1_EM14_XE10 = 0;
   trig_L1_emtau_L1_EM14_XE15 = 0;
   trig_L1_emtau_L1_EM2 = 0;
   trig_L1_emtau_L1_EM2_UNPAIRED_ISO = 0;
   trig_L1_emtau_L1_EM2_UNPAIRED_NONISO = 0;
   trig_L1_emtau_L1_EM3 = 0;
   trig_L1_emtau_L1_EM3_EMPTY = 0;
   trig_L1_emtau_L1_EM3_FIRSTEMPTY = 0;
   trig_L1_emtau_L1_EM3_MV = 0;
   trig_L1_emtau_L1_EM5 = 0;
   trig_L1_emtau_L1_EM5_MU10 = 0;
   trig_L1_emtau_L1_EM5_MU6 = 0;
   trig_L1_emtau_L1_EM85 = 0;
   trig_L2_emcl_quality = 0;
   trig_L2_emcl_E = 0;
   trig_L2_emcl_Et = 0;
   trig_L2_emcl_eta = 0;
   trig_L2_emcl_phi = 0;
   trig_L2_emcl_E237 = 0;
   trig_L2_emcl_E277 = 0;
   trig_L2_emcl_fracs1 = 0;
   trig_L2_emcl_weta2 = 0;
   trig_L2_emcl_Ehad1 = 0;
   trig_L2_emcl_eta1 = 0;
   trig_L2_emcl_emaxs1 = 0;
   trig_L2_emcl_e2tsts1 = 0;
   trig_L2_trk_idscan_eGamma_algorithmId = 0;
   trig_L2_trk_idscan_eGamma_trackStatus = 0;
   trig_L2_trk_idscan_eGamma_chi2Ndof = 0;
   trig_L2_trk_idscan_eGamma_nStrawHits = 0;
   trig_L2_trk_idscan_eGamma_nHighThrHits = 0;
   trig_L2_trk_idscan_eGamma_nPixelSpacePoints = 0;
   trig_L2_trk_idscan_eGamma_nSCT_SpacePoints = 0;
   trig_L2_trk_idscan_eGamma_a0 = 0;
   trig_L2_trk_idscan_eGamma_z0 = 0;
   trig_L2_trk_idscan_eGamma_phi0 = 0;
   trig_L2_trk_idscan_eGamma_eta = 0;
   trig_L2_trk_idscan_eGamma_pt = 0;
   trig_L2_trk_sitrack_eGamma_algorithmId = 0;
   trig_L2_trk_sitrack_eGamma_trackStatus = 0;
   trig_L2_trk_sitrack_eGamma_chi2Ndof = 0;
   trig_L2_trk_sitrack_eGamma_nStrawHits = 0;
   trig_L2_trk_sitrack_eGamma_nHighThrHits = 0;
   trig_L2_trk_sitrack_eGamma_nPixelSpacePoints = 0;
   trig_L2_trk_sitrack_eGamma_nSCT_SpacePoints = 0;
   trig_L2_trk_sitrack_eGamma_a0 = 0;
   trig_L2_trk_sitrack_eGamma_z0 = 0;
   trig_L2_trk_sitrack_eGamma_phi0 = 0;
   trig_L2_trk_sitrack_eGamma_eta = 0;
   trig_L2_trk_sitrack_eGamma_pt = 0;
   trig_L2_el_E = 0;
   trig_L2_el_Et = 0;
   trig_L2_el_pt = 0;
   trig_L2_el_eta = 0;
   trig_L2_el_phi = 0;
   trig_L2_el_RoIWord = 0;
   trig_L2_el_zvertex = 0;
   trig_L2_el_charge = 0;
   trig_L2_el_trackAlgo = 0;
   trig_L2_el_TRTHighTHitsRatio = 0;
   trig_L2_el_deltaeta1 = 0;
   trig_L2_el_deltaphi2 = 0;
   trig_L2_el_EtOverPt = 0;
   trig_L2_el_reta = 0;
   trig_L2_el_Eratio = 0;
   trig_L2_el_Ethad1 = 0;
   trig_L2_el_L2_2e10_loose = 0;
   trig_L2_el_L2_2e10_medium = 0;
   trig_L2_el_L2_2e15_loose = 0;
   trig_L2_el_L2_2e3_loose = 0;
   trig_L2_el_L2_2e3_loose_SiTrk = 0;
   trig_L2_el_L2_2e3_loose_TRT = 0;
   trig_L2_el_L2_2e3_medium = 0;
   trig_L2_el_L2_2e3_medium_SiTrk = 0;
   trig_L2_el_L2_2e3_medium_TRT = 0;
   trig_L2_el_L2_2e3_tight = 0;
   trig_L2_el_L2_2e5_medium = 0;
   trig_L2_el_L2_2e5_medium_SiTrk = 0;
   trig_L2_el_L2_2e5_medium_TRT = 0;
   trig_L2_el_L2_2e5_tight = 0;
   trig_L2_el_L2_e10_NoCut = 0;
   trig_L2_el_L2_e10_loose = 0;
   trig_L2_el_L2_e10_loose_mu10 = 0;
   trig_L2_el_L2_e10_loose_mu6 = 0;
   trig_L2_el_L2_e10_medium = 0;
   trig_L2_el_L2_e10_medium_IDTrkNoCut = 0;
   trig_L2_el_L2_e10_medium_SiTrk = 0;
   trig_L2_el_L2_e10_medium_TRT = 0;
   trig_L2_el_L2_e10_tight = 0;
   trig_L2_el_L2_e15_loose = 0;
   trig_L2_el_L2_e15_loose_IDTrkNoCut = 0;
   trig_L2_el_L2_e15_medium = 0;
   trig_L2_el_L2_e15_medium_SiTrk = 0;
   trig_L2_el_L2_e15_medium_TRT = 0;
   trig_L2_el_L2_e15_tight = 0;
   trig_L2_el_L2_e18_medium = 0;
   trig_L2_el_L2_e20_loose = 0;
   trig_L2_el_L2_e20_loose_IDTrkNoCut = 0;
   trig_L2_el_L2_e20_loose_passEF = 0;
   trig_L2_el_L2_e20_loose_passL2 = 0;
   trig_L2_el_L2_e20_loose_xe20_noMu = 0;
   trig_L2_el_L2_e20_loose_xe30_noMu = 0;
   trig_L2_el_L2_e20_medium = 0;
   trig_L2_el_L2_e25_loose = 0;
   trig_L2_el_L2_e30_loose = 0;
   trig_L2_el_L2_e3_loose = 0;
   trig_L2_el_L2_e3_loose_SiTrk = 0;
   trig_L2_el_L2_e3_loose_TRT = 0;
   trig_L2_el_L2_e3_medium = 0;
   trig_L2_el_L2_e3_medium_SiTrk = 0;
   trig_L2_el_L2_e3_medium_TRT = 0;
   trig_L2_el_L2_e5_NoCut_firstempty = 0;
   trig_L2_el_L2_e5_medium = 0;
   trig_L2_el_L2_e5_medium_MV = 0;
   trig_L2_el_L2_e5_medium_SiTrk = 0;
   trig_L2_el_L2_e5_medium_TRT = 0;
   trig_L2_el_L2_e5_medium_mu4 = 0;
   trig_L2_el_L2_e5_tight = 0;
   trig_L2_el_L2_e5_tight_SiTrk = 0;
   trig_L2_el_L2_e5_tight_TRT = 0;
   trig_L2_el_L2_e5_tight_e5_NoCut = 0;
   trig_L2_el_L2_eb_physics = 0;
   trig_L2_el_L2_eb_physics_empty = 0;
   trig_L2_el_L2_eb_physics_firstempty = 0;
   trig_L2_el_L2_eb_physics_unpaired_iso = 0;
   trig_L2_el_L2_eb_physics_unpaired_noniso = 0;
   trig_L2_el_L2_eb_random = 0;
   trig_L2_el_L2_eb_random_empty = 0;
   trig_L2_el_L2_eb_random_firstempty = 0;
   trig_L2_el_L2_eb_random_unpaired_iso = 0;
   trig_L2_el_L2_em105_passHLT = 0;
   trig_L2_el_L2_em3_empty_larcalib = 0;
   trig_L2_ph_E = 0;
   trig_L2_ph_Et = 0;
   trig_L2_ph_pt = 0;
   trig_L2_ph_eta = 0;
   trig_L2_ph_phi = 0;
   trig_L2_ph_RoIWord = 0;
   trig_L2_ph_HadEt1 = 0;
   trig_L2_ph_Eratio = 0;
   trig_L2_ph_Reta = 0;
   trig_L2_ph_dPhi = 0;
   trig_L2_ph_dEta = 0;
   trig_L2_ph_F1 = 0;
   trig_L2_ph_L2_2g10_loose = 0;
   trig_L2_ph_L2_2g15_loose = 0;
   trig_L2_ph_L2_2g5_loose = 0;
   trig_L2_ph_L2_2g7_loose = 0;
   trig_L2_ph_L2_g10_loose = 0;
   trig_L2_ph_L2_g11_etcut = 0;
   trig_L2_ph_L2_g15_loose = 0;
   trig_L2_ph_L2_g17_etcut = 0;
   trig_L2_ph_L2_g17_etcut_EFxe20_noMu = 0;
   trig_L2_ph_L2_g17_etcut_EFxe30_noMu = 0;
   trig_L2_ph_L2_g20_loose = 0;
   trig_L2_ph_L2_g20_loose_xe20_noMu = 0;
   trig_L2_ph_L2_g20_loose_xe30_noMu = 0;
   trig_L2_ph_L2_g20_tight = 0;
   trig_L2_ph_L2_g25_loose_xe30_noMu = 0;
   trig_L2_ph_L2_g30_loose = 0;
   trig_L2_ph_L2_g30_tight = 0;
   trig_L2_ph_L2_g3_NoCut_unpaired_iso = 0;
   trig_L2_ph_L2_g3_NoCut_unpaired_noniso = 0;
   trig_L2_ph_L2_g40_loose = 0;
   trig_L2_ph_L2_g40_tight = 0;
   trig_L2_ph_L2_g50_loose = 0;
   trig_L2_ph_L2_g5_NoCut_cosmic = 0;
   trig_L2_ph_L2_g5_loose = 0;
   trig_L2_ph_L2_g7_loose = 0;
   trig_EF_emcl_E = 0;
   trig_EF_emcl_pt = 0;
   trig_EF_emcl_m = 0;
   trig_EF_emcl_eta = 0;
   trig_EF_emcl_phi = 0;
   trig_EF_emcl_E_em = 0;
   trig_EF_emcl_E_had = 0;
   trig_EF_emcl_firstEdens = 0;
   trig_EF_emcl_cellmaxfrac = 0;
   trig_EF_emcl_longitudinal = 0;
   trig_EF_emcl_secondlambda = 0;
   trig_EF_emcl_lateral = 0;
   trig_EF_emcl_secondR = 0;
   trig_EF_emcl_centerlambda = 0;
   trig_EF_emcl_deltaTheta = 0;
   trig_EF_emcl_deltaPhi = 0;
   trig_EF_emcl_time = 0;
   trig_EF_emcl_slw_E = 0;
   trig_EF_emcl_slw_pt = 0;
   trig_EF_emcl_slw_m = 0;
   trig_EF_emcl_slw_eta = 0;
   trig_EF_emcl_slw_phi = 0;
   trig_EF_emcl_slw_E_em = 0;
   trig_EF_emcl_slw_E_had = 0;
   trig_EF_emcl_slw_firstEdens = 0;
   trig_EF_emcl_slw_cellmaxfrac = 0;
   trig_EF_emcl_slw_longitudinal = 0;
   trig_EF_emcl_slw_secondlambda = 0;
   trig_EF_emcl_slw_lateral = 0;
   trig_EF_emcl_slw_secondR = 0;
   trig_EF_emcl_slw_centerlambda = 0;
   trig_EF_emcl_slw_deltaTheta = 0;
   trig_EF_emcl_slw_deltaPhi = 0;
   trig_EF_emcl_slw_time = 0;
   trig_EF_el_E = 0;
   trig_EF_el_Et = 0;
   trig_EF_el_pt = 0;
   trig_EF_el_m = 0;
   trig_EF_el_eta = 0;
   trig_EF_el_phi = 0;
   trig_EF_el_px = 0;
   trig_EF_el_py = 0;
   trig_EF_el_pz = 0;
   trig_EF_el_charge = 0;
   trig_EF_el_author = 0;
   trig_EF_el_isEM = 0;
   trig_EF_el_loose = 0;
   trig_EF_el_medium = 0;
   trig_EF_el_mediumIso = 0;
   trig_EF_el_tight = 0;
   trig_EF_el_tightIso = 0;
   trig_EF_el_Ethad = 0;
   trig_EF_el_Ethad1 = 0;
   trig_EF_el_f1 = 0;
   trig_EF_el_f1core = 0;
   trig_EF_el_Emins1 = 0;
   trig_EF_el_fside = 0;
   trig_EF_el_Emax2 = 0;
   trig_EF_el_ws3 = 0;
   trig_EF_el_wstot = 0;
   trig_EF_el_emaxs1 = 0;
   trig_EF_el_deltaEs = 0;
   trig_EF_el_E233 = 0;
   trig_EF_el_E237 = 0;
   trig_EF_el_E277 = 0;
   trig_EF_el_weta2 = 0;
   trig_EF_el_f3 = 0;
   trig_EF_el_f3core = 0;
   trig_EF_el_rphiallcalo = 0;
   trig_EF_el_Etcone45 = 0;
   trig_EF_el_Etcone20 = 0;
   trig_EF_el_Etcone30 = 0;
   trig_EF_el_Etcone40 = 0;
   trig_EF_el_pos7 = 0;
   trig_EF_el_etacorrmag = 0;
   trig_EF_el_deltaeta1 = 0;
   trig_EF_el_deltaeta2 = 0;
   trig_EF_el_deltaphi2 = 0;
   trig_EF_el_reta = 0;
   trig_EF_el_rphi = 0;
   trig_EF_el_EF_2e10_loose = 0;
   trig_EF_el_EF_2e10_medium = 0;
   trig_EF_el_EF_2e15_loose = 0;
   trig_EF_el_EF_2e3_loose = 0;
   trig_EF_el_EF_2e3_loose_SiTrk = 0;
   trig_EF_el_EF_2e3_loose_TRT = 0;
   trig_EF_el_EF_2e3_medium = 0;
   trig_EF_el_EF_2e3_medium_SiTrk = 0;
   trig_EF_el_EF_2e3_medium_TRT = 0;
   trig_EF_el_EF_2e3_tight = 0;
   trig_EF_el_EF_2e5_medium = 0;
   trig_EF_el_EF_2e5_medium_SiTrk = 0;
   trig_EF_el_EF_2e5_medium_TRT = 0;
   trig_EF_el_EF_2e5_tight = 0;
   trig_EF_el_EF_e10_NoCut = 0;
   trig_EF_el_EF_e10_loose = 0;
   trig_EF_el_EF_e10_loose_mu10 = 0;
   trig_EF_el_EF_e10_loose_mu6 = 0;
   trig_EF_el_EF_e10_medium = 0;
   trig_EF_el_EF_e10_medium_IDTrkNoCut = 0;
   trig_EF_el_EF_e10_medium_SiTrk = 0;
   trig_EF_el_EF_e10_medium_TRT = 0;
   trig_EF_el_EF_e10_tight = 0;
   trig_EF_el_EF_e15_loose = 0;
   trig_EF_el_EF_e15_loose_IDTrkNoCut = 0;
   trig_EF_el_EF_e15_medium = 0;
   trig_EF_el_EF_e15_medium_SiTrk = 0;
   trig_EF_el_EF_e15_medium_TRT = 0;
   trig_EF_el_EF_e15_tight = 0;
   trig_EF_el_EF_e18_medium = 0;
   trig_EF_el_EF_e20_loose = 0;
   trig_EF_el_EF_e20_loose_IDTrkNoCut = 0;
   trig_EF_el_EF_e20_loose_passEF = 0;
   trig_EF_el_EF_e20_loose_passL2 = 0;
   trig_EF_el_EF_e20_loose_xe20_noMu = 0;
   trig_EF_el_EF_e20_loose_xe30_noMu = 0;
   trig_EF_el_EF_e20_medium = 0;
   trig_EF_el_EF_e25_loose = 0;
   trig_EF_el_EF_e30_loose = 0;
   trig_EF_el_EF_e3_loose = 0;
   trig_EF_el_EF_e3_loose_SiTrk = 0;
   trig_EF_el_EF_e3_loose_TRT = 0;
   trig_EF_el_EF_e3_medium = 0;
   trig_EF_el_EF_e3_medium_SiTrk = 0;
   trig_EF_el_EF_e3_medium_TRT = 0;
   trig_EF_el_EF_e5_NoCut_firstempty = 0;
   trig_EF_el_EF_e5_medium = 0;
   trig_EF_el_EF_e5_medium_MV = 0;
   trig_EF_el_EF_e5_medium_SiTrk = 0;
   trig_EF_el_EF_e5_medium_TRT = 0;
   trig_EF_el_EF_e5_medium_mu4 = 0;
   trig_EF_el_EF_e5_tight = 0;
   trig_EF_el_EF_e5_tight_SiTrk = 0;
   trig_EF_el_EF_e5_tight_TRT = 0;
   trig_EF_el_EF_e5_tight_e5_NoCut = 0;
   trig_EF_el_EF_eb_physics = 0;
   trig_EF_el_EF_eb_physics_empty = 0;
   trig_EF_el_EF_eb_physics_firstempty = 0;
   trig_EF_el_EF_eb_physics_unpaired_iso = 0;
   trig_EF_el_EF_eb_physics_unpaired_noniso = 0;
   trig_EF_el_EF_eb_random = 0;
   trig_EF_el_EF_eb_random_empty = 0;
   trig_EF_el_EF_eb_random_firstempty = 0;
   trig_EF_el_EF_eb_random_unpaired_iso = 0;
   trig_EF_el_EF_em105_passHLT = 0;
   trig_EF_ph_E = 0;
   trig_EF_ph_Et = 0;
   trig_EF_ph_pt = 0;
   trig_EF_ph_m = 0;
   trig_EF_ph_eta = 0;
   trig_EF_ph_phi = 0;
   trig_EF_ph_px = 0;
   trig_EF_ph_py = 0;
   trig_EF_ph_pz = 0;
   trig_EF_ph_EF_2g10_loose = 0;
   trig_EF_ph_EF_2g15_loose = 0;
   trig_EF_ph_EF_2g5_loose = 0;
   trig_EF_ph_EF_2g7_loose = 0;
   trig_EF_ph_EF_g10_loose = 0;
   trig_EF_ph_EF_g10_loose_larcalib = 0;
   trig_EF_ph_EF_g11_etcut = 0;
   trig_EF_ph_EF_g15_loose = 0;
   trig_EF_ph_EF_g17_etcut = 0;
   trig_EF_ph_EF_g17_etcut_EFxe20_noMu = 0;
   trig_EF_ph_EF_g17_etcut_EFxe30_noMu = 0;
   trig_EF_ph_EF_g20_loose = 0;
   trig_EF_ph_EF_g20_loose_larcalib = 0;
   trig_EF_ph_EF_g20_loose_xe20_noMu = 0;
   trig_EF_ph_EF_g20_loose_xe30_noMu = 0;
   trig_EF_ph_EF_g20_tight = 0;
   trig_EF_ph_EF_g25_loose_xe30_noMu = 0;
   trig_EF_ph_EF_g30_loose = 0;
   trig_EF_ph_EF_g30_tight = 0;
   trig_EF_ph_EF_g3_NoCut_unpaired_iso = 0;
   trig_EF_ph_EF_g3_NoCut_unpaired_noniso = 0;
   trig_EF_ph_EF_g40_loose = 0;
   trig_EF_ph_EF_g40_loose_larcalib = 0;
   trig_EF_ph_EF_g40_tight = 0;
   trig_EF_ph_EF_g50_loose = 0;
   trig_EF_ph_EF_g50_loose_larcalib = 0;
   trig_EF_ph_EF_g5_NoCut_cosmic = 0;
   trig_EF_ph_EF_g5_loose = 0;
   trig_EF_ph_EF_g5_loose_larcalib = 0;
   trig_EF_ph_EF_g7_loose = 0;
   trig_Nav_chain_ChainId = 0;
   trig_Nav_chain_RoIType = 0;
   trig_Nav_chain_RoIIndex = 0;
   trig_RoI_L2_e_type = 0;
   trig_RoI_L2_e_lastStep = 0;
   trig_RoI_L2_e_TrigEMCluster = 0;
   trig_RoI_L2_e_TrigEMClusterStatus = 0;
   trig_RoI_L2_e_EmTau_ROI = 0;
   trig_RoI_L2_e_EmTau_ROIStatus = 0;
   trig_RoI_L2_e_TrigInDetTrackCollection_TrigSiTrack_eGamma = 0;
   trig_RoI_L2_e_TrigInDetTrackCollection_TrigSiTrack_eGammaStatus = 0;
   trig_RoI_L2_e_TrigInDetTrackCollection_TrigIDSCAN_eGamma = 0;
   trig_RoI_L2_e_TrigInDetTrackCollection_TrigIDSCAN_eGammaStatus = 0;
   trig_RoI_L2_e_TrigElectronContainer = 0;
   trig_RoI_L2_e_TrigElectronContainerStatus = 0;
   trig_RoI_EF_e_type = 0;
   trig_RoI_EF_e_lastStep = 0;
   trig_RoI_EF_e_EmTau_ROI = 0;
   trig_RoI_EF_e_EmTau_ROIStatus = 0;
   trig_L1_esum_thrNames = 0;
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
   MET_Goodness_BCH_CORR_CELL_Jet = 0;
   MET_Goodness_BCH_CORR_JET = 0;
   MET_Goodness_BCH_CORR_JET_FORCELL_Jet = 0;
   MET_Goodness_ChargeFraction_Jet = 0;
   MET_Goodness_DeltaEt_JetAlgs_Jet = 0;
   MET_Goodness_DeltaEta_JetAlgs_Jet = 0;
   MET_Goodness_DeltaPhi_JetAlgs_Jet = 0;
   MET_Goodness_DeltaPhi_MET_Jet = 0;
   MET_Goodness_EEM_Jet = 0;
   MET_Goodness_EFinal_Jet = 0;
   MET_Goodness_EMFraction_Jet = 0;
   MET_Goodness_E_BadCellsCorr_Jet = 0;
   MET_Goodness_E_BadCells_Jet = 0;
   MET_Goodness_Eta_Jet = 0;
   MET_Goodness_HECf_Jet = 0;
   MET_Goodness_LArQuality_Jet = 0;
   MET_Goodness_Phi_Jet = 0;
   MET_Goodness_PtEM_Jet = 0;
   MET_Goodness_QualityFrac_Jet = 0;
   MET_Goodness_SamplingFracCryo_Jet = 0;
   MET_Goodness_SamplingFracEM_Jet = 0;
   MET_Goodness_SamplingFracFCAL_Jet = 0;
   MET_Goodness_SamplingFracGap_Jet = 0;
   MET_Goodness_SamplingFracHEC3_Jet = 0;
   MET_Goodness_SamplingFracHEC_Jet = 0;
   MET_Goodness_SamplingFracMax_Jet = 0;
   MET_Goodness_SamplingFracPS_Jet = 0;
   MET_Goodness_SamplingFracTile10_Jet = 0;
   MET_Goodness_SamplingFracTile2_Jet = 0;
   MET_Goodness_SamplingFracTile_Jet = 0;
   MET_Goodness_TileQuality_Jet = 0;
   MET_Goodness_Timing_Jet = 0;
   MET_Goodness_fcor_Jet = 0;
   MET_Goodness_ootE25_Jet = 0;
   MET_Goodness_ootE50_Jet = 0;
   MET_Goodness_ootE75_Jet = 0;
   MET_Goodness_N90Cells_Jet = 0;
   MET_Goodness_N90Constituents_Jet = 0;
   MET_Goodness_NConstituents_Jet = 0;
   MET_Goodness_N_BadCellsCorr_Jet = 0;
   MET_Goodness_N_BadCells_Jet = 0;
   MET_Goodness_NumTracks_Jet = 0;
   MET_Goodness_SamplingMaxID_Jet = 0;
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
   fChain->SetBranchAddress("lar_ncellA", &lar_ncellA, &b_lar_ncellA);
   fChain->SetBranchAddress("lar_ncellC", &lar_ncellC, &b_lar_ncellC);
   fChain->SetBranchAddress("lar_energyA", &lar_energyA, &b_lar_energyA);
   fChain->SetBranchAddress("lar_energyC", &lar_energyC, &b_lar_energyC);
   fChain->SetBranchAddress("lar_timeA", &lar_timeA, &b_lar_timeA);
   fChain->SetBranchAddress("lar_timeC", &lar_timeC, &b_lar_timeC);
   fChain->SetBranchAddress("lar_timeDiff", &lar_timeDiff, &b_lar_timeDiff);
   fChain->SetBranchAddress("el_n", &el_n, &b_el_n);
   fChain->SetBranchAddress("el_E", &el_E, &b_el_E);
   fChain->SetBranchAddress("el_Et", &el_Et, &b_el_Et);
   fChain->SetBranchAddress("el_pt", &el_pt, &b_el_pt);
   fChain->SetBranchAddress("el_m", &el_m, &b_el_m);
   fChain->SetBranchAddress("el_eta", &el_eta, &b_el_eta);
   fChain->SetBranchAddress("el_phi", &el_phi, &b_el_phi);
   fChain->SetBranchAddress("el_px", &el_px, &b_el_px);
   fChain->SetBranchAddress("el_py", &el_py, &b_el_py);
   fChain->SetBranchAddress("el_pz", &el_pz, &b_el_pz);
   fChain->SetBranchAddress("el_charge", &el_charge, &b_el_charge);
   fChain->SetBranchAddress("el_author", &el_author, &b_el_author);
   fChain->SetBranchAddress("el_isEM", &el_isEM, &b_el_isEM);
   fChain->SetBranchAddress("el_convFlag", &el_convFlag, &b_el_convFlag);
   fChain->SetBranchAddress("el_isConv", &el_isConv, &b_el_isConv);
   fChain->SetBranchAddress("el_nConv", &el_nConv, &b_el_nConv);
   fChain->SetBranchAddress("el_nSingleTrackConv", &el_nSingleTrackConv, &b_el_nSingleTrackConv);
   fChain->SetBranchAddress("el_nDoubleTrackConv", &el_nDoubleTrackConv, &b_el_nDoubleTrackConv);
   fChain->SetBranchAddress("el_loose", &el_loose, &b_el_loose);
   fChain->SetBranchAddress("el_medium", &el_medium, &b_el_medium);
   fChain->SetBranchAddress("el_mediumIso", &el_mediumIso, &b_el_mediumIso);
   fChain->SetBranchAddress("el_tight", &el_tight, &b_el_tight);
   fChain->SetBranchAddress("el_tightIso", &el_tightIso, &b_el_tightIso);
   fChain->SetBranchAddress("el_Ethad", &el_Ethad, &b_el_Ethad);
   fChain->SetBranchAddress("el_Ethad1", &el_Ethad1, &b_el_Ethad1);
   fChain->SetBranchAddress("el_f1", &el_f1, &b_el_f1);
   fChain->SetBranchAddress("el_f1core", &el_f1core, &b_el_f1core);
   fChain->SetBranchAddress("el_Emins1", &el_Emins1, &b_el_Emins1);
   fChain->SetBranchAddress("el_fside", &el_fside, &b_el_fside);
   fChain->SetBranchAddress("el_Emax2", &el_Emax2, &b_el_Emax2);
   fChain->SetBranchAddress("el_ws3", &el_ws3, &b_el_ws3);
   fChain->SetBranchAddress("el_wstot", &el_wstot, &b_el_wstot);
   fChain->SetBranchAddress("el_emaxs1", &el_emaxs1, &b_el_emaxs1);
   fChain->SetBranchAddress("el_deltaEs", &el_deltaEs, &b_el_deltaEs);
   fChain->SetBranchAddress("el_E233", &el_E233, &b_el_E233);
   fChain->SetBranchAddress("el_E237", &el_E237, &b_el_E237);
   fChain->SetBranchAddress("el_E277", &el_E277, &b_el_E277);
   fChain->SetBranchAddress("el_weta2", &el_weta2, &b_el_weta2);
   fChain->SetBranchAddress("el_f3", &el_f3, &b_el_f3);
   fChain->SetBranchAddress("el_f3core", &el_f3core, &b_el_f3core);
   fChain->SetBranchAddress("el_rphiallcalo", &el_rphiallcalo, &b_el_rphiallcalo);
   fChain->SetBranchAddress("el_Etcone45", &el_Etcone45, &b_el_Etcone45);
   fChain->SetBranchAddress("el_Etcone20", &el_Etcone20, &b_el_Etcone20);
   fChain->SetBranchAddress("el_Etcone30", &el_Etcone30, &b_el_Etcone30);
   fChain->SetBranchAddress("el_Etcone40", &el_Etcone40, &b_el_Etcone40);
   fChain->SetBranchAddress("el_ptcone30", &el_ptcone30, &b_el_ptcone30);
   fChain->SetBranchAddress("el_convanglematch", &el_convanglematch, &b_el_convanglematch);
   fChain->SetBranchAddress("el_convtrackmatch", &el_convtrackmatch, &b_el_convtrackmatch);
   fChain->SetBranchAddress("el_hasconv", &el_hasconv, &b_el_hasconv);
   fChain->SetBranchAddress("el_convvtxx", &el_convvtxx, &b_el_convvtxx);
   fChain->SetBranchAddress("el_convvtxy", &el_convvtxy, &b_el_convvtxy);
   fChain->SetBranchAddress("el_convvtxz", &el_convvtxz, &b_el_convvtxz);
   fChain->SetBranchAddress("el_Rconv", &el_Rconv, &b_el_Rconv);
   fChain->SetBranchAddress("el_zconv", &el_zconv, &b_el_zconv);
   fChain->SetBranchAddress("el_convvtxchi2", &el_convvtxchi2, &b_el_convvtxchi2);
   fChain->SetBranchAddress("el_pt1conv", &el_pt1conv, &b_el_pt1conv);
   fChain->SetBranchAddress("el_convtrk1nBLHits", &el_convtrk1nBLHits, &b_el_convtrk1nBLHits);
   fChain->SetBranchAddress("el_convtrk1nPixHits", &el_convtrk1nPixHits, &b_el_convtrk1nPixHits);
   fChain->SetBranchAddress("el_convtrk1nSCTHits", &el_convtrk1nSCTHits, &b_el_convtrk1nSCTHits);
   fChain->SetBranchAddress("el_convtrk1nTRTHits", &el_convtrk1nTRTHits, &b_el_convtrk1nTRTHits);
   fChain->SetBranchAddress("el_pt2conv", &el_pt2conv, &b_el_pt2conv);
   fChain->SetBranchAddress("el_convtrk2nBLHits", &el_convtrk2nBLHits, &b_el_convtrk2nBLHits);
   fChain->SetBranchAddress("el_convtrk2nPixHits", &el_convtrk2nPixHits, &b_el_convtrk2nPixHits);
   fChain->SetBranchAddress("el_convtrk2nSCTHits", &el_convtrk2nSCTHits, &b_el_convtrk2nSCTHits);
   fChain->SetBranchAddress("el_convtrk2nTRTHits", &el_convtrk2nTRTHits, &b_el_convtrk2nTRTHits);
   fChain->SetBranchAddress("el_ptconv", &el_ptconv, &b_el_ptconv);
   fChain->SetBranchAddress("el_pzconv", &el_pzconv, &b_el_pzconv);
   fChain->SetBranchAddress("el_pos7", &el_pos7, &b_el_pos7);
   fChain->SetBranchAddress("el_etacorrmag", &el_etacorrmag, &b_el_etacorrmag);
   fChain->SetBranchAddress("el_deltaeta1", &el_deltaeta1, &b_el_deltaeta1);
   fChain->SetBranchAddress("el_deltaeta2", &el_deltaeta2, &b_el_deltaeta2);
   fChain->SetBranchAddress("el_deltaphi2", &el_deltaphi2, &b_el_deltaphi2);
   fChain->SetBranchAddress("el_deltaphiRescaled", &el_deltaphiRescaled, &b_el_deltaphiRescaled);
   fChain->SetBranchAddress("el_expectHitInBLayer", &el_expectHitInBLayer, &b_el_expectHitInBLayer);
   fChain->SetBranchAddress("el_reta", &el_reta, &b_el_reta);
   fChain->SetBranchAddress("el_rphi", &el_rphi, &b_el_rphi);
   fChain->SetBranchAddress("el_EtringnoisedR03sig2", &el_EtringnoisedR03sig2, &b_el_EtringnoisedR03sig2);
   fChain->SetBranchAddress("el_EtringnoisedR03sig3", &el_EtringnoisedR03sig3, &b_el_EtringnoisedR03sig3);
   fChain->SetBranchAddress("el_EtringnoisedR03sig4", &el_EtringnoisedR03sig4, &b_el_EtringnoisedR03sig4);
   fChain->SetBranchAddress("el_isolationlikelihoodjets", &el_isolationlikelihoodjets, &b_el_isolationlikelihoodjets);
   fChain->SetBranchAddress("el_isolationlikelihoodhqelectrons", &el_isolationlikelihoodhqelectrons, &b_el_isolationlikelihoodhqelectrons);
   fChain->SetBranchAddress("el_electronweight", &el_electronweight, &b_el_electronweight);
   fChain->SetBranchAddress("el_electronbgweight", &el_electronbgweight, &b_el_electronbgweight);
   fChain->SetBranchAddress("el_softeweight", &el_softeweight, &b_el_softeweight);
   fChain->SetBranchAddress("el_softebgweight", &el_softebgweight, &b_el_softebgweight);
   fChain->SetBranchAddress("el_neuralnet", &el_neuralnet, &b_el_neuralnet);
   fChain->SetBranchAddress("el_Hmatrix", &el_Hmatrix, &b_el_Hmatrix);
   fChain->SetBranchAddress("el_Hmatrix5", &el_Hmatrix5, &b_el_Hmatrix5);
   fChain->SetBranchAddress("el_adaboost", &el_adaboost, &b_el_adaboost);
   fChain->SetBranchAddress("el_softeneuralnet", &el_softeneuralnet, &b_el_softeneuralnet);
   fChain->SetBranchAddress("el_zvertex", &el_zvertex, &b_el_zvertex);
   fChain->SetBranchAddress("el_errz", &el_errz, &b_el_errz);
   fChain->SetBranchAddress("el_etap", &el_etap, &b_el_etap);
   fChain->SetBranchAddress("el_depth", &el_depth, &b_el_depth);
   fChain->SetBranchAddress("el_breminvpt", &el_breminvpt, &b_el_breminvpt);
   fChain->SetBranchAddress("el_bremradius", &el_bremradius, &b_el_bremradius);
   fChain->SetBranchAddress("el_bremx", &el_bremx, &b_el_bremx);
   fChain->SetBranchAddress("el_bremclusterradius", &el_bremclusterradius, &b_el_bremclusterradius);
   fChain->SetBranchAddress("el_breminvpterr", &el_breminvpterr, &b_el_breminvpterr);
   fChain->SetBranchAddress("el_bremtrackauthor", &el_bremtrackauthor, &b_el_bremtrackauthor);
   fChain->SetBranchAddress("el_hasbrem", &el_hasbrem, &b_el_hasbrem);
   fChain->SetBranchAddress("el_bremdeltaqoverp", &el_bremdeltaqoverp, &b_el_bremdeltaqoverp);
   fChain->SetBranchAddress("el_bremmaterialtraversed", &el_bremmaterialtraversed, &b_el_bremmaterialtraversed);
   fChain->SetBranchAddress("el_refittedtrackqoverp", &el_refittedtrackqoverp, &b_el_refittedtrackqoverp);
   fChain->SetBranchAddress("el_refittedtrackd0", &el_refittedtrackd0, &b_el_refittedtrackd0);
   fChain->SetBranchAddress("el_refittedtrackz0", &el_refittedtrackz0, &b_el_refittedtrackz0);
   fChain->SetBranchAddress("el_refittedtracktheta", &el_refittedtracktheta, &b_el_refittedtracktheta);
   fChain->SetBranchAddress("el_refittedtrackphi", &el_refittedtrackphi, &b_el_refittedtrackphi);
   fChain->SetBranchAddress("el_Es0", &el_Es0, &b_el_Es0);
   fChain->SetBranchAddress("el_etas0", &el_etas0, &b_el_etas0);
   fChain->SetBranchAddress("el_phis0", &el_phis0, &b_el_phis0);
   fChain->SetBranchAddress("el_Es1", &el_Es1, &b_el_Es1);
   fChain->SetBranchAddress("el_etas1", &el_etas1, &b_el_etas1);
   fChain->SetBranchAddress("el_phis1", &el_phis1, &b_el_phis1);
   fChain->SetBranchAddress("el_Es2", &el_Es2, &b_el_Es2);
   fChain->SetBranchAddress("el_etas2", &el_etas2, &b_el_etas2);
   fChain->SetBranchAddress("el_phis2", &el_phis2, &b_el_phis2);
   fChain->SetBranchAddress("el_Es3", &el_Es3, &b_el_Es3);
   fChain->SetBranchAddress("el_etas3", &el_etas3, &b_el_etas3);
   fChain->SetBranchAddress("el_phis3", &el_phis3, &b_el_phis3);
   fChain->SetBranchAddress("el_E_PreSamplerB", &el_E_PreSamplerB, &b_el_E_PreSamplerB);
   fChain->SetBranchAddress("el_E_EMB1", &el_E_EMB1, &b_el_E_EMB1);
   fChain->SetBranchAddress("el_E_EMB2", &el_E_EMB2, &b_el_E_EMB2);
   fChain->SetBranchAddress("el_E_EMB3", &el_E_EMB3, &b_el_E_EMB3);
   fChain->SetBranchAddress("el_E_PreSamplerE", &el_E_PreSamplerE, &b_el_E_PreSamplerE);
   fChain->SetBranchAddress("el_E_EME1", &el_E_EME1, &b_el_E_EME1);
   fChain->SetBranchAddress("el_E_EME2", &el_E_EME2, &b_el_E_EME2);
   fChain->SetBranchAddress("el_E_EME3", &el_E_EME3, &b_el_E_EME3);
   fChain->SetBranchAddress("el_E_HEC0", &el_E_HEC0, &b_el_E_HEC0);
   fChain->SetBranchAddress("el_E_HEC1", &el_E_HEC1, &b_el_E_HEC1);
   fChain->SetBranchAddress("el_E_HEC2", &el_E_HEC2, &b_el_E_HEC2);
   fChain->SetBranchAddress("el_E_HEC3", &el_E_HEC3, &b_el_E_HEC3);
   fChain->SetBranchAddress("el_E_TileBar0", &el_E_TileBar0, &b_el_E_TileBar0);
   fChain->SetBranchAddress("el_E_TileBar1", &el_E_TileBar1, &b_el_E_TileBar1);
   fChain->SetBranchAddress("el_E_TileBar2", &el_E_TileBar2, &b_el_E_TileBar2);
   fChain->SetBranchAddress("el_E_TileGap1", &el_E_TileGap1, &b_el_E_TileGap1);
   fChain->SetBranchAddress("el_E_TileGap2", &el_E_TileGap2, &b_el_E_TileGap2);
   fChain->SetBranchAddress("el_E_TileGap3", &el_E_TileGap3, &b_el_E_TileGap3);
   fChain->SetBranchAddress("el_E_TileExt0", &el_E_TileExt0, &b_el_E_TileExt0);
   fChain->SetBranchAddress("el_E_TileExt1", &el_E_TileExt1, &b_el_E_TileExt1);
   fChain->SetBranchAddress("el_E_TileExt2", &el_E_TileExt2, &b_el_E_TileExt2);
   fChain->SetBranchAddress("el_E_FCAL0", &el_E_FCAL0, &b_el_E_FCAL0);
   fChain->SetBranchAddress("el_E_FCAL1", &el_E_FCAL1, &b_el_E_FCAL1);
   fChain->SetBranchAddress("el_E_FCAL2", &el_E_FCAL2, &b_el_E_FCAL2);
   fChain->SetBranchAddress("el_cl_E", &el_cl_E, &b_el_cl_E);
   fChain->SetBranchAddress("el_cl_pt", &el_cl_pt, &b_el_cl_pt);
   fChain->SetBranchAddress("el_cl_eta", &el_cl_eta, &b_el_cl_eta);
   fChain->SetBranchAddress("el_cl_phi", &el_cl_phi, &b_el_cl_phi);
   fChain->SetBranchAddress("el_firstEdens", &el_firstEdens, &b_el_firstEdens);
   fChain->SetBranchAddress("el_cellmaxfrac", &el_cellmaxfrac, &b_el_cellmaxfrac);
   fChain->SetBranchAddress("el_longitudinal", &el_longitudinal, &b_el_longitudinal);
   fChain->SetBranchAddress("el_secondlambda", &el_secondlambda, &b_el_secondlambda);
   fChain->SetBranchAddress("el_lateral", &el_lateral, &b_el_lateral);
   fChain->SetBranchAddress("el_secondR", &el_secondR, &b_el_secondR);
   fChain->SetBranchAddress("el_centerlambda", &el_centerlambda, &b_el_centerlambda);
   fChain->SetBranchAddress("el_rawcl_Es0", &el_rawcl_Es0, &b_el_rawcl_Es0);
   fChain->SetBranchAddress("el_rawcl_etas0", &el_rawcl_etas0, &b_el_rawcl_etas0);
   fChain->SetBranchAddress("el_rawcl_phis0", &el_rawcl_phis0, &b_el_rawcl_phis0);
   fChain->SetBranchAddress("el_rawcl_Es1", &el_rawcl_Es1, &b_el_rawcl_Es1);
   fChain->SetBranchAddress("el_rawcl_etas1", &el_rawcl_etas1, &b_el_rawcl_etas1);
   fChain->SetBranchAddress("el_rawcl_phis1", &el_rawcl_phis1, &b_el_rawcl_phis1);
   fChain->SetBranchAddress("el_rawcl_Es2", &el_rawcl_Es2, &b_el_rawcl_Es2);
   fChain->SetBranchAddress("el_rawcl_etas2", &el_rawcl_etas2, &b_el_rawcl_etas2);
   fChain->SetBranchAddress("el_rawcl_phis2", &el_rawcl_phis2, &b_el_rawcl_phis2);
   fChain->SetBranchAddress("el_rawcl_Es3", &el_rawcl_Es3, &b_el_rawcl_Es3);
   fChain->SetBranchAddress("el_rawcl_etas3", &el_rawcl_etas3, &b_el_rawcl_etas3);
   fChain->SetBranchAddress("el_rawcl_phis3", &el_rawcl_phis3, &b_el_rawcl_phis3);
   fChain->SetBranchAddress("el_rawcl_E", &el_rawcl_E, &b_el_rawcl_E);
   fChain->SetBranchAddress("el_rawcl_pt", &el_rawcl_pt, &b_el_rawcl_pt);
   fChain->SetBranchAddress("el_rawcl_eta", &el_rawcl_eta, &b_el_rawcl_eta);
   fChain->SetBranchAddress("el_rawcl_phi", &el_rawcl_phi, &b_el_rawcl_phi);
   fChain->SetBranchAddress("el_refittedtrackcovd0", &el_refittedtrackcovd0, &b_el_refittedtrackcovd0);
   fChain->SetBranchAddress("el_refittedtrackcovz0", &el_refittedtrackcovz0, &b_el_refittedtrackcovz0);
   fChain->SetBranchAddress("el_refittedtrackcovphi", &el_refittedtrackcovphi, &b_el_refittedtrackcovphi);
   fChain->SetBranchAddress("el_refittedtrackcovtheta", &el_refittedtrackcovtheta, &b_el_refittedtrackcovtheta);
   fChain->SetBranchAddress("el_refittedtrackcovqoverp", &el_refittedtrackcovqoverp, &b_el_refittedtrackcovqoverp);
   fChain->SetBranchAddress("el_refittedtrackcovd0z0", &el_refittedtrackcovd0z0, &b_el_refittedtrackcovd0z0);
   fChain->SetBranchAddress("el_refittedtrackcovz0phi", &el_refittedtrackcovz0phi, &b_el_refittedtrackcovz0phi);
   fChain->SetBranchAddress("el_refittedtrackcovz0theta", &el_refittedtrackcovz0theta, &b_el_refittedtrackcovz0theta);
   fChain->SetBranchAddress("el_refittedtrackcovz0qoverp", &el_refittedtrackcovz0qoverp, &b_el_refittedtrackcovz0qoverp);
   fChain->SetBranchAddress("el_refittedtrackcovd0phi", &el_refittedtrackcovd0phi, &b_el_refittedtrackcovd0phi);
   fChain->SetBranchAddress("el_refittedtrackcovd0theta", &el_refittedtrackcovd0theta, &b_el_refittedtrackcovd0theta);
   fChain->SetBranchAddress("el_refittedtrackcovd0qoverp", &el_refittedtrackcovd0qoverp, &b_el_refittedtrackcovd0qoverp);
   fChain->SetBranchAddress("el_refittedtrackcovphitheta", &el_refittedtrackcovphitheta, &b_el_refittedtrackcovphitheta);
   fChain->SetBranchAddress("el_refittedtrackcovphiqoverp", &el_refittedtrackcovphiqoverp, &b_el_refittedtrackcovphiqoverp);
   fChain->SetBranchAddress("el_refittedtrackcovthetaqoverp", &el_refittedtrackcovthetaqoverp, &b_el_refittedtrackcovthetaqoverp);
   fChain->SetBranchAddress("el_trackd0", &el_trackd0, &b_el_trackd0);
   fChain->SetBranchAddress("el_trackz0", &el_trackz0, &b_el_trackz0);
   fChain->SetBranchAddress("el_trackphi", &el_trackphi, &b_el_trackphi);
   fChain->SetBranchAddress("el_tracktheta", &el_tracktheta, &b_el_tracktheta);
   fChain->SetBranchAddress("el_trackqoverp", &el_trackqoverp, &b_el_trackqoverp);
   fChain->SetBranchAddress("el_trackpt", &el_trackpt, &b_el_trackpt);
   fChain->SetBranchAddress("el_tracketa", &el_tracketa, &b_el_tracketa);
   fChain->SetBranchAddress("el_trackcov_d0", &el_trackcov_d0, &b_el_trackcov_d0);
   fChain->SetBranchAddress("el_trackcov_z0", &el_trackcov_z0, &b_el_trackcov_z0);
   fChain->SetBranchAddress("el_trackcov_phi", &el_trackcov_phi, &b_el_trackcov_phi);
   fChain->SetBranchAddress("el_trackcov_theta", &el_trackcov_theta, &b_el_trackcov_theta);
   fChain->SetBranchAddress("el_trackcov_qoverp", &el_trackcov_qoverp, &b_el_trackcov_qoverp);
   fChain->SetBranchAddress("el_trackcov_d0_z0", &el_trackcov_d0_z0, &b_el_trackcov_d0_z0);
   fChain->SetBranchAddress("el_trackcov_d0_phi", &el_trackcov_d0_phi, &b_el_trackcov_d0_phi);
   fChain->SetBranchAddress("el_trackcov_d0_theta", &el_trackcov_d0_theta, &b_el_trackcov_d0_theta);
   fChain->SetBranchAddress("el_trackcov_d0_qoverp", &el_trackcov_d0_qoverp, &b_el_trackcov_d0_qoverp);
   fChain->SetBranchAddress("el_trackcov_z0_phi", &el_trackcov_z0_phi, &b_el_trackcov_z0_phi);
   fChain->SetBranchAddress("el_trackcov_z0_theta", &el_trackcov_z0_theta, &b_el_trackcov_z0_theta);
   fChain->SetBranchAddress("el_trackcov_z0_qoverp", &el_trackcov_z0_qoverp, &b_el_trackcov_z0_qoverp);
   fChain->SetBranchAddress("el_trackcov_phi_theta", &el_trackcov_phi_theta, &b_el_trackcov_phi_theta);
   fChain->SetBranchAddress("el_trackcov_phi_qoverp", &el_trackcov_phi_qoverp, &b_el_trackcov_phi_qoverp);
   fChain->SetBranchAddress("el_trackcov_theta_qoverp", &el_trackcov_theta_qoverp, &b_el_trackcov_theta_qoverp);
   fChain->SetBranchAddress("el_trackfitchi2", &el_trackfitchi2, &b_el_trackfitchi2);
   fChain->SetBranchAddress("el_trackfitndof", &el_trackfitndof, &b_el_trackfitndof);
   fChain->SetBranchAddress("el_nBLHits", &el_nBLHits, &b_el_nBLHits);
   fChain->SetBranchAddress("el_nPixHits", &el_nPixHits, &b_el_nPixHits);
   fChain->SetBranchAddress("el_nSCTHits", &el_nSCTHits, &b_el_nSCTHits);
   fChain->SetBranchAddress("el_nTRTHits", &el_nTRTHits, &b_el_nTRTHits);
   fChain->SetBranchAddress("el_nPixHoles", &el_nPixHoles, &b_el_nPixHoles);
   fChain->SetBranchAddress("el_nSCTHoles", &el_nSCTHoles, &b_el_nSCTHoles);
   fChain->SetBranchAddress("el_nBLSharedHits", &el_nBLSharedHits, &b_el_nBLSharedHits);
   fChain->SetBranchAddress("el_nPixSharedHits", &el_nPixSharedHits, &b_el_nPixSharedHits);
   fChain->SetBranchAddress("el_nSCTSharedHits", &el_nSCTSharedHits, &b_el_nSCTSharedHits);
   fChain->SetBranchAddress("el_nTRTHighTHits", &el_nTRTHighTHits, &b_el_nTRTHighTHits);
   fChain->SetBranchAddress("el_nTRTOutliers", &el_nTRTOutliers, &b_el_nTRTOutliers);
   fChain->SetBranchAddress("el_nTRTHighTOutliers", &el_nTRTHighTOutliers, &b_el_nTRTHighTOutliers);
   fChain->SetBranchAddress("el_nSiHits", &el_nSiHits, &b_el_nSiHits);
   fChain->SetBranchAddress("el_TRTHighTHitsRatio", &el_TRTHighTHitsRatio, &b_el_TRTHighTHitsRatio);
   fChain->SetBranchAddress("el_pixeldEdx", &el_pixeldEdx, &b_el_pixeldEdx);
   fChain->SetBranchAddress("el_eProbabilityComb", &el_eProbabilityComb, &b_el_eProbabilityComb);
   fChain->SetBranchAddress("el_eProbabilityHT", &el_eProbabilityHT, &b_el_eProbabilityHT);
   fChain->SetBranchAddress("el_eProbabilityToT", &el_eProbabilityToT, &b_el_eProbabilityToT);
   fChain->SetBranchAddress("el_eProbabilityBrem", &el_eProbabilityBrem, &b_el_eProbabilityBrem);
   fChain->SetBranchAddress("el_vertx", &el_vertx, &b_el_vertx);
   fChain->SetBranchAddress("el_verty", &el_verty, &b_el_verty);
   fChain->SetBranchAddress("el_vertz", &el_vertz, &b_el_vertz);
   fChain->SetBranchAddress("el_hastrack", &el_hastrack, &b_el_hastrack);
   fChain->SetBranchAddress("el_deltaEmax2", &el_deltaEmax2, &b_el_deltaEmax2);
   fChain->SetBranchAddress("el_trackd0beam", &el_trackd0beam, &b_el_trackd0beam);
   fChain->SetBranchAddress("el_tracksigd0beam", &el_tracksigd0beam, &b_el_tracksigd0beam);
   fChain->SetBranchAddress("el_trackd0pv", &el_trackd0pv, &b_el_trackd0pv);
   fChain->SetBranchAddress("el_tracksigd0pv", &el_tracksigd0pv, &b_el_tracksigd0pv);
   fChain->SetBranchAddress("el_trackz0pv", &el_trackz0pv, &b_el_trackz0pv);
   fChain->SetBranchAddress("el_tracksigz0pv", &el_tracksigz0pv, &b_el_tracksigz0pv);
   fChain->SetBranchAddress("el_trackd0pvunbiased", &el_trackd0pvunbiased, &b_el_trackd0pvunbiased);
   fChain->SetBranchAddress("el_tracksigd0pvunbiased", &el_tracksigd0pvunbiased, &b_el_tracksigd0pvunbiased);
   fChain->SetBranchAddress("el_trackz0pvunbiased", &el_trackz0pvunbiased, &b_el_trackz0pvunbiased);
   fChain->SetBranchAddress("el_tracksigz0pvunbiased", &el_tracksigz0pvunbiased, &b_el_tracksigz0pvunbiased);
   fChain->SetBranchAddress("el_jetcone_n", &el_jetcone_n, &b_el_jetcone_n);
   fChain->SetBranchAddress("el_jetcone_dr", &el_jetcone_dr, &b_el_jetcone_dr);
   fChain->SetBranchAddress("el_jetcone_signedIP", &el_jetcone_signedIP, &b_el_jetcone_signedIP);
   fChain->SetBranchAddress("el_jetcone_ptrel", &el_jetcone_ptrel, &b_el_jetcone_ptrel);
   fChain->SetBranchAddress("el_jetcone_index", &el_jetcone_index, &b_el_jetcone_index);
   fChain->SetBranchAddress("el_jetcone_E", &el_jetcone_E, &b_el_jetcone_E);
   fChain->SetBranchAddress("el_jetcone_pt", &el_jetcone_pt, &b_el_jetcone_pt);
   fChain->SetBranchAddress("el_jetcone_m", &el_jetcone_m, &b_el_jetcone_m);
   fChain->SetBranchAddress("el_jetcone_eta", &el_jetcone_eta, &b_el_jetcone_eta);
   fChain->SetBranchAddress("el_jetcone_phi", &el_jetcone_phi, &b_el_jetcone_phi);
   fChain->SetBranchAddress("el_isIso", &el_isIso, &b_el_isIso);
   fChain->SetBranchAddress("el_jet_dr", &el_jet_dr, &b_el_jet_dr);
   fChain->SetBranchAddress("el_jet_E", &el_jet_E, &b_el_jet_E);
   fChain->SetBranchAddress("el_jet_pt", &el_jet_pt, &b_el_jet_pt);
   fChain->SetBranchAddress("el_jet_m", &el_jet_m, &b_el_jet_m);
   fChain->SetBranchAddress("el_jet_eta", &el_jet_eta, &b_el_jet_eta);
   fChain->SetBranchAddress("el_jet_phi", &el_jet_phi, &b_el_jet_phi);
   fChain->SetBranchAddress("el_jet_matched", &el_jet_matched, &b_el_jet_matched);
   fChain->SetBranchAddress("el_Etcone40_pt_corrected", &el_Etcone40_pt_corrected, &b_el_Etcone40_pt_corrected);
   fChain->SetBranchAddress("el_Etcone40_ED_corrected", &el_Etcone40_ED_corrected, &b_el_Etcone40_ED_corrected);
   fChain->SetBranchAddress("el_Etcone40_corrected", &el_Etcone40_corrected, &b_el_Etcone40_corrected);
   fChain->SetBranchAddress("el_EF_dr", &el_EF_dr, &b_el_EF_dr);
   fChain->SetBranchAddress("el_EF_index", &el_EF_index, &b_el_EF_index);
   fChain->SetBranchAddress("el_L2_dr", &el_L2_dr, &b_el_L2_dr);
   fChain->SetBranchAddress("el_L2_index", &el_L2_index, &b_el_L2_index);
   fChain->SetBranchAddress("el_L1_dr", &el_L1_dr, &b_el_L1_dr);
   fChain->SetBranchAddress("el_L1_index", &el_L1_index, &b_el_L1_index);
   fChain->SetBranchAddress("el_EF_E", &el_EF_E, &b_el_EF_E);
   fChain->SetBranchAddress("el_EF_Et", &el_EF_Et, &b_el_EF_Et);
   fChain->SetBranchAddress("el_EF_pt", &el_EF_pt, &b_el_EF_pt);
   fChain->SetBranchAddress("el_EF_eta", &el_EF_eta, &b_el_EF_eta);
   fChain->SetBranchAddress("el_EF_phi", &el_EF_phi, &b_el_EF_phi);
   fChain->SetBranchAddress("el_EF_charge", &el_EF_charge, &b_el_EF_charge);
   fChain->SetBranchAddress("el_EF_Ethad", &el_EF_Ethad, &b_el_EF_Ethad);
   fChain->SetBranchAddress("el_EF_Ethad1", &el_EF_Ethad1, &b_el_EF_Ethad1);
   fChain->SetBranchAddress("el_EF_f1", &el_EF_f1, &b_el_EF_f1);
   fChain->SetBranchAddress("el_EF_Emins1", &el_EF_Emins1, &b_el_EF_Emins1);
   fChain->SetBranchAddress("el_EF_fside", &el_EF_fside, &b_el_EF_fside);
   fChain->SetBranchAddress("el_EF_Emax2", &el_EF_Emax2, &b_el_EF_Emax2);
   fChain->SetBranchAddress("el_EF_ws3", &el_EF_ws3, &b_el_EF_ws3);
   fChain->SetBranchAddress("el_EF_wstot", &el_EF_wstot, &b_el_EF_wstot);
   fChain->SetBranchAddress("el_EF_E233", &el_EF_E233, &b_el_EF_E233);
   fChain->SetBranchAddress("el_EF_E237", &el_EF_E237, &b_el_EF_E237);
   fChain->SetBranchAddress("el_EF_E277", &el_EF_E277, &b_el_EF_E277);
   fChain->SetBranchAddress("el_EF_weta2", &el_EF_weta2, &b_el_EF_weta2);
   fChain->SetBranchAddress("el_EF_rphiallcalo", &el_EF_rphiallcalo, &b_el_EF_rphiallcalo);
   fChain->SetBranchAddress("el_EF_deltaeta1", &el_EF_deltaeta1, &b_el_EF_deltaeta1);
   fChain->SetBranchAddress("el_EF_deltaeta2", &el_EF_deltaeta2, &b_el_EF_deltaeta2);
   fChain->SetBranchAddress("el_EF_deltaphi2", &el_EF_deltaphi2, &b_el_EF_deltaphi2);
   fChain->SetBranchAddress("el_EF_expectHitInBLayer", &el_EF_expectHitInBLayer, &b_el_EF_expectHitInBLayer);
   fChain->SetBranchAddress("el_EF_Etcone45", &el_EF_Etcone45, &b_el_EF_Etcone45);
   fChain->SetBranchAddress("el_EF_Etcone20", &el_EF_Etcone20, &b_el_EF_Etcone20);
   fChain->SetBranchAddress("el_EF_Etcone30", &el_EF_Etcone30, &b_el_EF_Etcone30);
   fChain->SetBranchAddress("el_EF_Etcone40", &el_EF_Etcone40, &b_el_EF_Etcone40);
   fChain->SetBranchAddress("el_EF_etacorrmag", &el_EF_etacorrmag, &b_el_EF_etacorrmag);
   fChain->SetBranchAddress("el_EF_zvertex", &el_EF_zvertex, &b_el_EF_zvertex);
   fChain->SetBranchAddress("el_EF_errz", &el_EF_errz, &b_el_EF_errz);
   fChain->SetBranchAddress("el_EF_trackd0", &el_EF_trackd0, &b_el_EF_trackd0);
   fChain->SetBranchAddress("el_EF_trackz0", &el_EF_trackz0, &b_el_EF_trackz0);
   fChain->SetBranchAddress("el_EF_trackphi", &el_EF_trackphi, &b_el_EF_trackphi);
   fChain->SetBranchAddress("el_EF_tracktheta", &el_EF_tracktheta, &b_el_EF_tracktheta);
   fChain->SetBranchAddress("el_EF_trackqoverp", &el_EF_trackqoverp, &b_el_EF_trackqoverp);
   fChain->SetBranchAddress("el_EF_trackpt", &el_EF_trackpt, &b_el_EF_trackpt);
   fChain->SetBranchAddress("el_EF_tracketa", &el_EF_tracketa, &b_el_EF_tracketa);
   fChain->SetBranchAddress("el_EF_nBLHits", &el_EF_nBLHits, &b_el_EF_nBLHits);
   fChain->SetBranchAddress("el_EF_nPixHits", &el_EF_nPixHits, &b_el_EF_nPixHits);
   fChain->SetBranchAddress("el_EF_nSCTHits", &el_EF_nSCTHits, &b_el_EF_nSCTHits);
   fChain->SetBranchAddress("el_EF_nTRTHits", &el_EF_nTRTHits, &b_el_EF_nTRTHits);
   fChain->SetBranchAddress("el_EF_nTRTHighTHits", &el_EF_nTRTHighTHits, &b_el_EF_nTRTHighTHits);
   fChain->SetBranchAddress("el_EF_nSiHits", &el_EF_nSiHits, &b_el_EF_nSiHits);
   fChain->SetBranchAddress("el_EF_TRTHighTHitsRatio", &el_EF_TRTHighTHitsRatio, &b_el_EF_TRTHighTHitsRatio);
   fChain->SetBranchAddress("el_EF_pixeldEdx", &el_EF_pixeldEdx, &b_el_EF_pixeldEdx);
   fChain->SetBranchAddress("el_EF_hastrack", &el_EF_hastrack, &b_el_EF_hastrack);
   fChain->SetBranchAddress("el_EF_matched", &el_EF_matched, &b_el_EF_matched);
   fChain->SetBranchAddress("el_L2_E", &el_L2_E, &b_el_L2_E);
   fChain->SetBranchAddress("el_L2_Et", &el_L2_Et, &b_el_L2_Et);
   fChain->SetBranchAddress("el_L2_pt", &el_L2_pt, &b_el_L2_pt);
   fChain->SetBranchAddress("el_L2_eta", &el_L2_eta, &b_el_L2_eta);
   fChain->SetBranchAddress("el_L2_phi", &el_L2_phi, &b_el_L2_phi);
   fChain->SetBranchAddress("el_L2_charge", &el_L2_charge, &b_el_L2_charge);
   fChain->SetBranchAddress("el_L2_Ethad1", &el_L2_Ethad1, &b_el_L2_Ethad1);
   fChain->SetBranchAddress("el_L2_reta", &el_L2_reta, &b_el_L2_reta);
   fChain->SetBranchAddress("el_L2_Eratio", &el_L2_Eratio, &b_el_L2_Eratio);
   fChain->SetBranchAddress("el_L2_trackclusterdeta", &el_L2_trackclusterdeta, &b_el_L2_trackclusterdeta);
   fChain->SetBranchAddress("el_L2_trackclusterdphi", &el_L2_trackclusterdphi, &b_el_L2_trackclusterdphi);
   fChain->SetBranchAddress("el_L2_Etoverpt", &el_L2_Etoverpt, &b_el_L2_Etoverpt);
   fChain->SetBranchAddress("el_L2_trackpt", &el_L2_trackpt, &b_el_L2_trackpt);
   fChain->SetBranchAddress("el_L2_trackalgo", &el_L2_trackalgo, &b_el_L2_trackalgo);
   fChain->SetBranchAddress("el_L2_tracketa", &el_L2_tracketa, &b_el_L2_tracketa);
   fChain->SetBranchAddress("el_L2_trackd0", &el_L2_trackd0, &b_el_L2_trackd0);
   fChain->SetBranchAddress("el_L2_trackz0", &el_L2_trackz0, &b_el_L2_trackz0);
   fChain->SetBranchAddress("el_L2_tracktheta", &el_L2_tracktheta, &b_el_L2_tracktheta);
   fChain->SetBranchAddress("el_L2_trackphi", &el_L2_trackphi, &b_el_L2_trackphi);
   fChain->SetBranchAddress("el_L2_tracketaatcalo", &el_L2_tracketaatcalo, &b_el_L2_tracketaatcalo);
   fChain->SetBranchAddress("el_L2_trackphiatcalo", &el_L2_trackphiatcalo, &b_el_L2_trackphiatcalo);
   fChain->SetBranchAddress("el_L2_errpt", &el_L2_errpt, &b_el_L2_errpt);
   fChain->SetBranchAddress("el_L2_erreta", &el_L2_erreta, &b_el_L2_erreta);
   fChain->SetBranchAddress("el_L2_errphi", &el_L2_errphi, &b_el_L2_errphi);
   fChain->SetBranchAddress("el_L2_E237", &el_L2_E237, &b_el_L2_E237);
   fChain->SetBranchAddress("el_L2_E277", &el_L2_E277, &b_el_L2_E277);
   fChain->SetBranchAddress("el_L2_fside", &el_L2_fside, &b_el_L2_fside);
   fChain->SetBranchAddress("el_L2_weta2", &el_L2_weta2, &b_el_L2_weta2);
   fChain->SetBranchAddress("el_L2_Emaxs1", &el_L2_Emaxs1, &b_el_L2_Emaxs1);
   fChain->SetBranchAddress("el_L2_Emax2", &el_L2_Emax2, &b_el_L2_Emax2);
   fChain->SetBranchAddress("el_L2_matched", &el_L2_matched, &b_el_L2_matched);
   fChain->SetBranchAddress("el_L1_eta", &el_L1_eta, &b_el_L1_eta);
   fChain->SetBranchAddress("el_L1_phi", &el_L1_phi, &b_el_L1_phi);
   fChain->SetBranchAddress("el_L1_EMisol", &el_L1_EMisol, &b_el_L1_EMisol);
   fChain->SetBranchAddress("el_L1_hadisol", &el_L1_hadisol, &b_el_L1_hadisol);
   fChain->SetBranchAddress("el_L1_hadcore", &el_L1_hadcore, &b_el_L1_hadcore);
   fChain->SetBranchAddress("el_L1_pt", &el_L1_pt, &b_el_L1_pt);
   fChain->SetBranchAddress("el_L1_Et", &el_L1_Et, &b_el_L1_Et);
   fChain->SetBranchAddress("el_L1_matched", &el_L1_matched, &b_el_L1_matched);
   fChain->SetBranchAddress("EF_2e10_loose", &EF_2e10_loose, &b_EF_2e10_loose);
   fChain->SetBranchAddress("EF_2e10_medium", &EF_2e10_medium, &b_EF_2e10_medium);
   fChain->SetBranchAddress("EF_2e15_loose", &EF_2e15_loose, &b_EF_2e15_loose);
   fChain->SetBranchAddress("EF_2e3_loose", &EF_2e3_loose, &b_EF_2e3_loose);
   fChain->SetBranchAddress("EF_2e3_loose_SiTrk", &EF_2e3_loose_SiTrk, &b_EF_2e3_loose_SiTrk);
   fChain->SetBranchAddress("EF_2e3_loose_TRT", &EF_2e3_loose_TRT, &b_EF_2e3_loose_TRT);
   fChain->SetBranchAddress("EF_2e3_medium", &EF_2e3_medium, &b_EF_2e3_medium);
   fChain->SetBranchAddress("EF_2e3_medium_SiTrk", &EF_2e3_medium_SiTrk, &b_EF_2e3_medium_SiTrk);
   fChain->SetBranchAddress("EF_2e3_medium_TRT", &EF_2e3_medium_TRT, &b_EF_2e3_medium_TRT);
   fChain->SetBranchAddress("EF_2e3_tight", &EF_2e3_tight, &b_EF_2e3_tight);
   fChain->SetBranchAddress("EF_2e5_medium", &EF_2e5_medium, &b_EF_2e5_medium);
   fChain->SetBranchAddress("EF_2e5_medium_SiTrk", &EF_2e5_medium_SiTrk, &b_EF_2e5_medium_SiTrk);
   fChain->SetBranchAddress("EF_2e5_medium_TRT", &EF_2e5_medium_TRT, &b_EF_2e5_medium_TRT);
   fChain->SetBranchAddress("EF_2e5_tight", &EF_2e5_tight, &b_EF_2e5_tight);
   fChain->SetBranchAddress("EF_2g10_loose", &EF_2g10_loose, &b_EF_2g10_loose);
   fChain->SetBranchAddress("EF_2g15_loose", &EF_2g15_loose, &b_EF_2g15_loose);
   fChain->SetBranchAddress("EF_2g5_loose", &EF_2g5_loose, &b_EF_2g5_loose);
   fChain->SetBranchAddress("EF_2g7_loose", &EF_2g7_loose, &b_EF_2g7_loose);
   fChain->SetBranchAddress("EF_2j20_deta3_5_jetNoEF", &EF_2j20_deta3_5_jetNoEF, &b_EF_2j20_deta3_5_jetNoEF);
   fChain->SetBranchAddress("EF_2j20_deta5_jetNoEF", &EF_2j20_deta5_jetNoEF, &b_EF_2j20_deta5_jetNoEF);
   fChain->SetBranchAddress("EF_2j20_jetNoEF", &EF_2j20_jetNoEF, &b_EF_2j20_jetNoEF);
   fChain->SetBranchAddress("EF_2j25_j45_anymct100_NoEF", &EF_2j25_j45_anymct100_NoEF, &b_EF_2j25_j45_anymct100_NoEF);
   fChain->SetBranchAddress("EF_2j25_j45_anymct150_NoEF", &EF_2j25_j45_anymct150_NoEF, &b_EF_2j25_j45_anymct150_NoEF);
   fChain->SetBranchAddress("EF_2j25_j45_anymct175_NoEF", &EF_2j25_j45_anymct175_NoEF, &b_EF_2j25_j45_anymct175_NoEF);
   fChain->SetBranchAddress("EF_2j25_j45_dphi03_NoEF", &EF_2j25_j45_dphi03_NoEF, &b_EF_2j25_j45_dphi03_NoEF);
   fChain->SetBranchAddress("EF_2j25_j45_leadingmct100_NoEF", &EF_2j25_j45_leadingmct100_NoEF, &b_EF_2j25_j45_leadingmct100_NoEF);
   fChain->SetBranchAddress("EF_2j25_j45_leadingmct150_NoEF", &EF_2j25_j45_leadingmct150_NoEF, &b_EF_2j25_j45_leadingmct150_NoEF);
   fChain->SetBranchAddress("EF_2j25_j45_leadingmct175_NoEF", &EF_2j25_j45_leadingmct175_NoEF, &b_EF_2j25_j45_leadingmct175_NoEF);
   fChain->SetBranchAddress("EF_2j25_j70_anymct150_NoEF", &EF_2j25_j70_anymct150_NoEF, &b_EF_2j25_j70_anymct150_NoEF);
   fChain->SetBranchAddress("EF_2j25_j70_anymct175_NoEF", &EF_2j25_j70_anymct175_NoEF, &b_EF_2j25_j70_anymct175_NoEF);
   fChain->SetBranchAddress("EF_2j25_j70_dphi03_NoEF", &EF_2j25_j70_dphi03_NoEF, &b_EF_2j25_j70_dphi03_NoEF);
   fChain->SetBranchAddress("EF_2j25_j70_leadingmct150_NoEF", &EF_2j25_j70_leadingmct150_NoEF, &b_EF_2j25_j70_leadingmct150_NoEF);
   fChain->SetBranchAddress("EF_2j25_j70_leadingmct175_NoEF", &EF_2j25_j70_leadingmct175_NoEF, &b_EF_2j25_j70_leadingmct175_NoEF);
   fChain->SetBranchAddress("EF_2j30_anymct100_NoEF", &EF_2j30_anymct100_NoEF, &b_EF_2j30_anymct100_NoEF);
   fChain->SetBranchAddress("EF_2j30_anymct150_NoEF", &EF_2j30_anymct150_NoEF, &b_EF_2j30_anymct150_NoEF);
   fChain->SetBranchAddress("EF_2j30_anymct175_NoEF", &EF_2j30_anymct175_NoEF, &b_EF_2j30_anymct175_NoEF);
   fChain->SetBranchAddress("EF_2j30_deta3_5_jetNoEF", &EF_2j30_deta3_5_jetNoEF, &b_EF_2j30_deta3_5_jetNoEF);
   fChain->SetBranchAddress("EF_2j30_j90_dphi03_NoEF", &EF_2j30_j90_dphi03_NoEF, &b_EF_2j30_j90_dphi03_NoEF);
   fChain->SetBranchAddress("EF_2j30_jetNoEF", &EF_2j30_jetNoEF, &b_EF_2j30_jetNoEF);
   fChain->SetBranchAddress("EF_2j30_leadingmct100_NoEF", &EF_2j30_leadingmct100_NoEF, &b_EF_2j30_leadingmct100_NoEF);
   fChain->SetBranchAddress("EF_2j30_leadingmct150_NoEF", &EF_2j30_leadingmct150_NoEF, &b_EF_2j30_leadingmct150_NoEF);
   fChain->SetBranchAddress("EF_2j30_leadingmct175_NoEF", &EF_2j30_leadingmct175_NoEF, &b_EF_2j30_leadingmct175_NoEF);
   fChain->SetBranchAddress("EF_2j35_deta3_5_jetNoEF", &EF_2j35_deta3_5_jetNoEF, &b_EF_2j35_deta3_5_jetNoEF);
   fChain->SetBranchAddress("EF_2j35_jetNoEF", &EF_2j35_jetNoEF, &b_EF_2j35_jetNoEF);
   fChain->SetBranchAddress("EF_2j35_jetNoEF_xe20_noMu", &EF_2j35_jetNoEF_xe20_noMu, &b_EF_2j35_jetNoEF_xe20_noMu);
   fChain->SetBranchAddress("EF_2j35_jetNoEF_xe30_noMu", &EF_2j35_jetNoEF_xe30_noMu, &b_EF_2j35_jetNoEF_xe30_noMu);
   fChain->SetBranchAddress("EF_2j35_jetNoEF_xe40_noMu", &EF_2j35_jetNoEF_xe40_noMu, &b_EF_2j35_jetNoEF_xe40_noMu);
   fChain->SetBranchAddress("EF_2j50_jetNoEF", &EF_2j50_jetNoEF, &b_EF_2j50_jetNoEF);
   fChain->SetBranchAddress("EF_2j75_jetNoEF", &EF_2j75_jetNoEF, &b_EF_2j75_jetNoEF);
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
   fChain->SetBranchAddress("EF_2mu4_Upsimumu", &EF_2mu4_Upsimumu, &b_EF_2mu4_Upsimumu);
   fChain->SetBranchAddress("EF_2mu6", &EF_2mu6, &b_EF_2mu6);
   fChain->SetBranchAddress("EF_2mu6_MG", &EF_2mu6_MG, &b_EF_2mu6_MG);
   fChain->SetBranchAddress("EF_2mu6_NoAlg", &EF_2mu6_NoAlg, &b_EF_2mu6_NoAlg);
   fChain->SetBranchAddress("EF_3j20_j50_jetNoEF", &EF_3j20_j50_jetNoEF, &b_EF_3j20_j50_jetNoEF);
   fChain->SetBranchAddress("EF_3j30_2j50_jetNoEF", &EF_3j30_2j50_jetNoEF, &b_EF_3j30_2j50_jetNoEF);
   fChain->SetBranchAddress("EF_3j30_jetNoEF", &EF_3j30_jetNoEF, &b_EF_3j30_jetNoEF);
   fChain->SetBranchAddress("EF_3j35_jetNoEF", &EF_3j35_jetNoEF, &b_EF_3j35_jetNoEF);
   fChain->SetBranchAddress("EF_3j50_jetNoEF", &EF_3j50_jetNoEF, &b_EF_3j50_jetNoEF);
   fChain->SetBranchAddress("EF_4j20_j35_jetNoEF", &EF_4j20_j35_jetNoEF, &b_EF_4j20_j35_jetNoEF);
   fChain->SetBranchAddress("EF_4j20_j50_jetNoEF", &EF_4j20_j50_jetNoEF, &b_EF_4j20_j50_jetNoEF);
   fChain->SetBranchAddress("EF_4j30_3j35_jetNoEF", &EF_4j30_3j35_jetNoEF, &b_EF_4j30_3j35_jetNoEF);
   fChain->SetBranchAddress("EF_4j30_jetNoEF", &EF_4j30_jetNoEF, &b_EF_4j30_jetNoEF);
   fChain->SetBranchAddress("EF_4j35_jetNoEF", &EF_4j35_jetNoEF, &b_EF_4j35_jetNoEF);
   fChain->SetBranchAddress("EF_4j50_jetNoEF", &EF_4j50_jetNoEF, &b_EF_4j50_jetNoEF);
   fChain->SetBranchAddress("EF_5j30_jetNoEF", &EF_5j30_jetNoEF, &b_EF_5j30_jetNoEF);
   fChain->SetBranchAddress("EF_6j30_jetNoEF", &EF_6j30_jetNoEF, &b_EF_6j30_jetNoEF);
   fChain->SetBranchAddress("EF_e10_NoCut", &EF_e10_NoCut, &b_EF_e10_NoCut);
   fChain->SetBranchAddress("EF_e10_loose", &EF_e10_loose, &b_EF_e10_loose);
   fChain->SetBranchAddress("EF_e10_loose_mu10", &EF_e10_loose_mu10, &b_EF_e10_loose_mu10);
   fChain->SetBranchAddress("EF_e10_loose_mu6", &EF_e10_loose_mu6, &b_EF_e10_loose_mu6);
   fChain->SetBranchAddress("EF_e10_medium", &EF_e10_medium, &b_EF_e10_medium);
   fChain->SetBranchAddress("EF_e10_medium_IDTrkNoCut", &EF_e10_medium_IDTrkNoCut, &b_EF_e10_medium_IDTrkNoCut);
   fChain->SetBranchAddress("EF_e10_medium_SiTrk", &EF_e10_medium_SiTrk, &b_EF_e10_medium_SiTrk);
   fChain->SetBranchAddress("EF_e10_medium_TRT", &EF_e10_medium_TRT, &b_EF_e10_medium_TRT);
   fChain->SetBranchAddress("EF_e10_tight", &EF_e10_tight, &b_EF_e10_tight);
   fChain->SetBranchAddress("EF_e15_loose", &EF_e15_loose, &b_EF_e15_loose);
   fChain->SetBranchAddress("EF_e15_loose_IDTrkNoCut", &EF_e15_loose_IDTrkNoCut, &b_EF_e15_loose_IDTrkNoCut);
   fChain->SetBranchAddress("EF_e15_medium", &EF_e15_medium, &b_EF_e15_medium);
   fChain->SetBranchAddress("EF_e15_medium_SiTrk", &EF_e15_medium_SiTrk, &b_EF_e15_medium_SiTrk);
   fChain->SetBranchAddress("EF_e15_medium_TRT", &EF_e15_medium_TRT, &b_EF_e15_medium_TRT);
   fChain->SetBranchAddress("EF_e15_tight", &EF_e15_tight, &b_EF_e15_tight);
   fChain->SetBranchAddress("EF_e18_medium", &EF_e18_medium, &b_EF_e18_medium);
   fChain->SetBranchAddress("EF_e20_loose", &EF_e20_loose, &b_EF_e20_loose);
   fChain->SetBranchAddress("EF_e20_loose_IDTrkNoCut", &EF_e20_loose_IDTrkNoCut, &b_EF_e20_loose_IDTrkNoCut);
   fChain->SetBranchAddress("EF_e20_loose_passEF", &EF_e20_loose_passEF, &b_EF_e20_loose_passEF);
   fChain->SetBranchAddress("EF_e20_loose_passL2", &EF_e20_loose_passL2, &b_EF_e20_loose_passL2);
   fChain->SetBranchAddress("EF_e20_loose_xe20_noMu", &EF_e20_loose_xe20_noMu, &b_EF_e20_loose_xe20_noMu);
   fChain->SetBranchAddress("EF_e20_loose_xe30_noMu", &EF_e20_loose_xe30_noMu, &b_EF_e20_loose_xe30_noMu);
   fChain->SetBranchAddress("EF_e20_medium", &EF_e20_medium, &b_EF_e20_medium);
   fChain->SetBranchAddress("EF_e25_loose", &EF_e25_loose, &b_EF_e25_loose);
   fChain->SetBranchAddress("EF_e30_loose", &EF_e30_loose, &b_EF_e30_loose);
   fChain->SetBranchAddress("EF_e3_loose", &EF_e3_loose, &b_EF_e3_loose);
   fChain->SetBranchAddress("EF_e3_loose_SiTrk", &EF_e3_loose_SiTrk, &b_EF_e3_loose_SiTrk);
   fChain->SetBranchAddress("EF_e3_loose_TRT", &EF_e3_loose_TRT, &b_EF_e3_loose_TRT);
   fChain->SetBranchAddress("EF_e3_medium", &EF_e3_medium, &b_EF_e3_medium);
   fChain->SetBranchAddress("EF_e3_medium_SiTrk", &EF_e3_medium_SiTrk, &b_EF_e3_medium_SiTrk);
   fChain->SetBranchAddress("EF_e3_medium_TRT", &EF_e3_medium_TRT, &b_EF_e3_medium_TRT);
   fChain->SetBranchAddress("EF_e5_NoCut_firstempty", &EF_e5_NoCut_firstempty, &b_EF_e5_NoCut_firstempty);
   fChain->SetBranchAddress("EF_e5_medium", &EF_e5_medium, &b_EF_e5_medium);
   fChain->SetBranchAddress("EF_e5_medium_MV", &EF_e5_medium_MV, &b_EF_e5_medium_MV);
   fChain->SetBranchAddress("EF_e5_medium_SiTrk", &EF_e5_medium_SiTrk, &b_EF_e5_medium_SiTrk);
   fChain->SetBranchAddress("EF_e5_medium_TRT", &EF_e5_medium_TRT, &b_EF_e5_medium_TRT);
   fChain->SetBranchAddress("EF_e5_medium_mu4", &EF_e5_medium_mu4, &b_EF_e5_medium_mu4);
   fChain->SetBranchAddress("EF_e5_tight", &EF_e5_tight, &b_EF_e5_tight);
   fChain->SetBranchAddress("EF_e5_tight_SiTrk", &EF_e5_tight_SiTrk, &b_EF_e5_tight_SiTrk);
   fChain->SetBranchAddress("EF_e5_tight_TRT", &EF_e5_tight_TRT, &b_EF_e5_tight_TRT);
   fChain->SetBranchAddress("EF_e5_tight_e5_NoCut", &EF_e5_tight_e5_NoCut, &b_EF_e5_tight_e5_NoCut);
   fChain->SetBranchAddress("EF_eb_physics", &EF_eb_physics, &b_EF_eb_physics);
   fChain->SetBranchAddress("EF_eb_physics_empty", &EF_eb_physics_empty, &b_EF_eb_physics_empty);
   fChain->SetBranchAddress("EF_eb_physics_firstempty", &EF_eb_physics_firstempty, &b_EF_eb_physics_firstempty);
   fChain->SetBranchAddress("EF_eb_physics_unpaired_iso", &EF_eb_physics_unpaired_iso, &b_EF_eb_physics_unpaired_iso);
   fChain->SetBranchAddress("EF_eb_physics_unpaired_noniso", &EF_eb_physics_unpaired_noniso, &b_EF_eb_physics_unpaired_noniso);
   fChain->SetBranchAddress("EF_eb_random", &EF_eb_random, &b_EF_eb_random);
   fChain->SetBranchAddress("EF_eb_random_empty", &EF_eb_random_empty, &b_EF_eb_random_empty);
   fChain->SetBranchAddress("EF_eb_random_firstempty", &EF_eb_random_firstempty, &b_EF_eb_random_firstempty);
   fChain->SetBranchAddress("EF_eb_random_unpaired_iso", &EF_eb_random_unpaired_iso, &b_EF_eb_random_unpaired_iso);
   fChain->SetBranchAddress("EF_em105_passHLT", &EF_em105_passHLT, &b_EF_em105_passHLT);
   fChain->SetBranchAddress("EF_fj10_empty_NoAlg", &EF_fj10_empty_NoAlg, &b_EF_fj10_empty_NoAlg);
   fChain->SetBranchAddress("EF_fj30_jetNoEF", &EF_fj30_jetNoEF, &b_EF_fj30_jetNoEF);
   fChain->SetBranchAddress("EF_fj30_jetNoEF_larcalib", &EF_fj30_jetNoEF_larcalib, &b_EF_fj30_jetNoEF_larcalib);
   fChain->SetBranchAddress("EF_fj50_jetNoEF", &EF_fj50_jetNoEF, &b_EF_fj50_jetNoEF);
   fChain->SetBranchAddress("EF_fj50_jetNoEF_larcalib", &EF_fj50_jetNoEF_larcalib, &b_EF_fj50_jetNoEF_larcalib);
   fChain->SetBranchAddress("EF_fj75_jetNoEF", &EF_fj75_jetNoEF, &b_EF_fj75_jetNoEF);
   fChain->SetBranchAddress("EF_fj95_jetNoCut_larcalib", &EF_fj95_jetNoCut_larcalib, &b_EF_fj95_jetNoCut_larcalib);
   fChain->SetBranchAddress("EF_g10_loose", &EF_g10_loose, &b_EF_g10_loose);
   fChain->SetBranchAddress("EF_g10_loose_larcalib", &EF_g10_loose_larcalib, &b_EF_g10_loose_larcalib);
   fChain->SetBranchAddress("EF_g11_etcut", &EF_g11_etcut, &b_EF_g11_etcut);
   fChain->SetBranchAddress("EF_g15_loose", &EF_g15_loose, &b_EF_g15_loose);
   fChain->SetBranchAddress("EF_g17_etcut", &EF_g17_etcut, &b_EF_g17_etcut);
   fChain->SetBranchAddress("EF_g17_etcut_EFxe20_noMu", &EF_g17_etcut_EFxe20_noMu, &b_EF_g17_etcut_EFxe20_noMu);
   fChain->SetBranchAddress("EF_g17_etcut_EFxe30_noMu", &EF_g17_etcut_EFxe30_noMu, &b_EF_g17_etcut_EFxe30_noMu);
   fChain->SetBranchAddress("EF_g20_loose", &EF_g20_loose, &b_EF_g20_loose);
   fChain->SetBranchAddress("EF_g20_loose_larcalib", &EF_g20_loose_larcalib, &b_EF_g20_loose_larcalib);
   fChain->SetBranchAddress("EF_g20_loose_xe20_noMu", &EF_g20_loose_xe20_noMu, &b_EF_g20_loose_xe20_noMu);
   fChain->SetBranchAddress("EF_g20_loose_xe30_noMu", &EF_g20_loose_xe30_noMu, &b_EF_g20_loose_xe30_noMu);
   fChain->SetBranchAddress("EF_g20_tight", &EF_g20_tight, &b_EF_g20_tight);
   fChain->SetBranchAddress("EF_g25_loose_xe30_noMu", &EF_g25_loose_xe30_noMu, &b_EF_g25_loose_xe30_noMu);
   fChain->SetBranchAddress("EF_g30_loose", &EF_g30_loose, &b_EF_g30_loose);
   fChain->SetBranchAddress("EF_g30_tight", &EF_g30_tight, &b_EF_g30_tight);
   fChain->SetBranchAddress("EF_g3_NoCut_unpaired_iso", &EF_g3_NoCut_unpaired_iso, &b_EF_g3_NoCut_unpaired_iso);
   fChain->SetBranchAddress("EF_g3_NoCut_unpaired_noniso", &EF_g3_NoCut_unpaired_noniso, &b_EF_g3_NoCut_unpaired_noniso);
   fChain->SetBranchAddress("EF_g40_loose", &EF_g40_loose, &b_EF_g40_loose);
   fChain->SetBranchAddress("EF_g40_loose_larcalib", &EF_g40_loose_larcalib, &b_EF_g40_loose_larcalib);
   fChain->SetBranchAddress("EF_g40_tight", &EF_g40_tight, &b_EF_g40_tight);
   fChain->SetBranchAddress("EF_g50_loose", &EF_g50_loose, &b_EF_g50_loose);
   fChain->SetBranchAddress("EF_g50_loose_larcalib", &EF_g50_loose_larcalib, &b_EF_g50_loose_larcalib);
   fChain->SetBranchAddress("EF_g5_NoCut_cosmic", &EF_g5_NoCut_cosmic, &b_EF_g5_NoCut_cosmic);
   fChain->SetBranchAddress("EF_g5_loose", &EF_g5_loose, &b_EF_g5_loose);
   fChain->SetBranchAddress("EF_g5_loose_larcalib", &EF_g5_loose_larcalib, &b_EF_g5_loose_larcalib);
   fChain->SetBranchAddress("EF_g7_loose", &EF_g7_loose, &b_EF_g7_loose);
   fChain->SetBranchAddress("EF_j115_jetNoCut_larcalib", &EF_j115_jetNoCut_larcalib, &b_EF_j115_jetNoCut_larcalib);
   fChain->SetBranchAddress("EF_j20_jetNoEF", &EF_j20_jetNoEF, &b_EF_j20_jetNoEF);
   fChain->SetBranchAddress("EF_j20_jetNoEF_larcalib", &EF_j20_jetNoEF_larcalib, &b_EF_j20_jetNoEF_larcalib);
   fChain->SetBranchAddress("EF_j30_fj30_jetNoEF", &EF_j30_fj30_jetNoEF, &b_EF_j30_fj30_jetNoEF);
   fChain->SetBranchAddress("EF_j30_jetNoCut_cosmic", &EF_j30_jetNoCut_cosmic, &b_EF_j30_jetNoCut_cosmic);
   fChain->SetBranchAddress("EF_j30_jetNoCut_firstempty", &EF_j30_jetNoCut_firstempty, &b_EF_j30_jetNoCut_firstempty);
   fChain->SetBranchAddress("EF_j30_jetNoCut_unpaired", &EF_j30_jetNoCut_unpaired, &b_EF_j30_jetNoCut_unpaired);
   fChain->SetBranchAddress("EF_j30_jetNoEF", &EF_j30_jetNoEF, &b_EF_j30_jetNoEF);
   fChain->SetBranchAddress("EF_j35_L1TAU_HV_jetNoEF", &EF_j35_L1TAU_HV_jetNoEF, &b_EF_j35_L1TAU_HV_jetNoEF);
   fChain->SetBranchAddress("EF_j35_jetNoEF", &EF_j35_jetNoEF, &b_EF_j35_jetNoEF);
   fChain->SetBranchAddress("EF_j50_jetNoCut_cosmic", &EF_j50_jetNoCut_cosmic, &b_EF_j50_jetNoCut_cosmic);
   fChain->SetBranchAddress("EF_j50_jetNoCut_firstempty", &EF_j50_jetNoCut_firstempty, &b_EF_j50_jetNoCut_firstempty);
   fChain->SetBranchAddress("EF_j50_jetNoCut_unpaired", &EF_j50_jetNoCut_unpaired, &b_EF_j50_jetNoCut_unpaired);
   fChain->SetBranchAddress("EF_j50_jetNoEF", &EF_j50_jetNoEF, &b_EF_j50_jetNoEF);
   fChain->SetBranchAddress("EF_j50_jetNoEF_larcalib", &EF_j50_jetNoEF_larcalib, &b_EF_j50_jetNoEF_larcalib);
   fChain->SetBranchAddress("EF_j50_jetNoEF_xe20_noMu", &EF_j50_jetNoEF_xe20_noMu, &b_EF_j50_jetNoEF_xe20_noMu);
   fChain->SetBranchAddress("EF_j50_jetNoEF_xe30_noMu", &EF_j50_jetNoEF_xe30_noMu, &b_EF_j50_jetNoEF_xe30_noMu);
   fChain->SetBranchAddress("EF_j50_jetNoEF_xe40_noMu", &EF_j50_jetNoEF_xe40_noMu, &b_EF_j50_jetNoEF_xe40_noMu);
   fChain->SetBranchAddress("EF_j5_empty_NoAlg", &EF_j5_empty_NoAlg, &b_EF_j5_empty_NoAlg);
   fChain->SetBranchAddress("EF_j5_unpaired_iso_NoAlg", &EF_j5_unpaired_iso_NoAlg, &b_EF_j5_unpaired_iso_NoAlg);
   fChain->SetBranchAddress("EF_j5_unpaired_noniso_NoAlg", &EF_j5_unpaired_noniso_NoAlg, &b_EF_j5_unpaired_noniso_NoAlg);
   fChain->SetBranchAddress("EF_j75_jetNoEF", &EF_j75_jetNoEF, &b_EF_j75_jetNoEF);
   fChain->SetBranchAddress("EF_j75_jetNoEF_EFxe20_noMu", &EF_j75_jetNoEF_EFxe20_noMu, &b_EF_j75_jetNoEF_EFxe20_noMu);
   fChain->SetBranchAddress("EF_j75_jetNoEF_EFxe25_noMu", &EF_j75_jetNoEF_EFxe25_noMu, &b_EF_j75_jetNoEF_EFxe25_noMu);
   fChain->SetBranchAddress("EF_j75_jetNoEF_EFxe30_noMu", &EF_j75_jetNoEF_EFxe30_noMu, &b_EF_j75_jetNoEF_EFxe30_noMu);
   fChain->SetBranchAddress("EF_j75_jetNoEF_EFxe35_noMu", &EF_j75_jetNoEF_EFxe35_noMu, &b_EF_j75_jetNoEF_EFxe35_noMu);
   fChain->SetBranchAddress("EF_j75_jetNoEF_EFxe40_noMu", &EF_j75_jetNoEF_EFxe40_noMu, &b_EF_j75_jetNoEF_EFxe40_noMu);
   fChain->SetBranchAddress("EF_j95_jetNoEF", &EF_j95_jetNoEF, &b_EF_j95_jetNoEF);
   fChain->SetBranchAddress("EF_j95_jetNoEF_larcalib", &EF_j95_jetNoEF_larcalib, &b_EF_j95_jetNoEF_larcalib);
   fChain->SetBranchAddress("EF_je135_NoEF", &EF_je135_NoEF, &b_EF_je135_NoEF);
   fChain->SetBranchAddress("EF_je195_NoEF", &EF_je195_NoEF, &b_EF_je195_NoEF);
   fChain->SetBranchAddress("EF_je255_NoEF", &EF_je255_NoEF, &b_EF_je255_NoEF);
   fChain->SetBranchAddress("EF_je300_NoEF", &EF_je300_NoEF, &b_EF_je300_NoEF);
   fChain->SetBranchAddress("EF_je350_NoEF", &EF_je350_NoEF, &b_EF_je350_NoEF);
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
   fChain->SetBranchAddress("EF_mu10_IDTrkNoCut", &EF_mu10_IDTrkNoCut, &b_EF_mu10_IDTrkNoCut);
   fChain->SetBranchAddress("EF_mu10_MG", &EF_mu10_MG, &b_EF_mu10_MG);
   fChain->SetBranchAddress("EF_mu10_MSonly", &EF_mu10_MSonly, &b_EF_mu10_MSonly);
   fChain->SetBranchAddress("EF_mu10_MSonly_tight", &EF_mu10_MSonly_tight, &b_EF_mu10_MSonly_tight);
   fChain->SetBranchAddress("EF_mu10_NoAlg", &EF_mu10_NoAlg, &b_EF_mu10_NoAlg);
   fChain->SetBranchAddress("EF_mu10_SiTrk", &EF_mu10_SiTrk, &b_EF_mu10_SiTrk);
   fChain->SetBranchAddress("EF_mu10_tight", &EF_mu10_tight, &b_EF_mu10_tight);
   fChain->SetBranchAddress("EF_mu10i_loose", &EF_mu10i_loose, &b_EF_mu10i_loose);
   fChain->SetBranchAddress("EF_mu13", &EF_mu13, &b_EF_mu13);
   fChain->SetBranchAddress("EF_mu13_MG", &EF_mu13_MG, &b_EF_mu13_MG);
   fChain->SetBranchAddress("EF_mu13_MG_tight", &EF_mu13_MG_tight, &b_EF_mu13_MG_tight);
   fChain->SetBranchAddress("EF_mu13_tight", &EF_mu13_tight, &b_EF_mu13_tight);
   fChain->SetBranchAddress("EF_mu15", &EF_mu15, &b_EF_mu15);
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
   fChain->SetBranchAddress("EF_mu4_j20_jetNoEF", &EF_mu4_j20_jetNoEF, &b_EF_mu4_j20_jetNoEF);
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
   fChain->SetBranchAddress("EF_mu4mu6_Upsimumu", &EF_mu4mu6_Upsimumu, &b_EF_mu4mu6_Upsimumu);
   fChain->SetBranchAddress("EF_mu6", &EF_mu6, &b_EF_mu6);
   fChain->SetBranchAddress("EF_mu6_Bmumu", &EF_mu6_Bmumu, &b_EF_mu6_Bmumu);
   fChain->SetBranchAddress("EF_mu6_BmumuX", &EF_mu6_BmumuX, &b_EF_mu6_BmumuX);
   fChain->SetBranchAddress("EF_mu6_DiMu", &EF_mu6_DiMu, &b_EF_mu6_DiMu);
   fChain->SetBranchAddress("EF_mu6_IDTrkNoCut", &EF_mu6_IDTrkNoCut, &b_EF_mu6_IDTrkNoCut);
   fChain->SetBranchAddress("EF_mu6_Jpsie5e3", &EF_mu6_Jpsie5e3, &b_EF_mu6_Jpsie5e3);
   fChain->SetBranchAddress("EF_mu6_Jpsie5e3_FS", &EF_mu6_Jpsie5e3_FS, &b_EF_mu6_Jpsie5e3_FS);
   fChain->SetBranchAddress("EF_mu6_Jpsimumu", &EF_mu6_Jpsimumu, &b_EF_mu6_Jpsimumu);
   fChain->SetBranchAddress("EF_mu6_MG", &EF_mu6_MG, &b_EF_mu6_MG);
   fChain->SetBranchAddress("EF_mu6_MSonly", &EF_mu6_MSonly, &b_EF_mu6_MSonly);
   fChain->SetBranchAddress("EF_mu6_MSonly_outOfTime", &EF_mu6_MSonly_outOfTime, &b_EF_mu6_MSonly_outOfTime);
   fChain->SetBranchAddress("EF_mu6_NoAlg", &EF_mu6_NoAlg, &b_EF_mu6_NoAlg);
   fChain->SetBranchAddress("EF_mu6_SiTrk", &EF_mu6_SiTrk, &b_EF_mu6_SiTrk);
   fChain->SetBranchAddress("EF_mu6_Trk_Jpsi", &EF_mu6_Trk_Jpsi, &b_EF_mu6_Trk_Jpsi);
   fChain->SetBranchAddress("EF_mu6_Upsimumu_FS", &EF_mu6_Upsimumu_FS, &b_EF_mu6_Upsimumu_FS);
   fChain->SetBranchAddress("EF_mu6_muCombTag", &EF_mu6_muCombTag, &b_EF_mu6_muCombTag);
   fChain->SetBranchAddress("EF_tau125_loose", &EF_tau125_loose, &b_EF_tau125_loose);
   fChain->SetBranchAddress("EF_tau125_medium", &EF_tau125_medium, &b_EF_tau125_medium);
   fChain->SetBranchAddress("EF_tau12_IDTrkNoCut", &EF_tau12_IDTrkNoCut, &b_EF_tau12_IDTrkNoCut);
   fChain->SetBranchAddress("EF_tau12_loose", &EF_tau12_loose, &b_EF_tau12_loose);
   fChain->SetBranchAddress("EF_tau12_loose_2b15", &EF_tau12_loose_2b15, &b_EF_tau12_loose_2b15);
   fChain->SetBranchAddress("EF_tau12_loose_3j35_jetNoEF", &EF_tau12_loose_3j35_jetNoEF, &b_EF_tau12_loose_3j35_jetNoEF);
   fChain->SetBranchAddress("EF_tau12_loose_EFxe12_noMu", &EF_tau12_loose_EFxe12_noMu, &b_EF_tau12_loose_EFxe12_noMu);
   fChain->SetBranchAddress("EF_tau12_loose_IdScan_EFxe12_noMu", &EF_tau12_loose_IdScan_EFxe12_noMu, &b_EF_tau12_loose_IdScan_EFxe12_noMu);
   fChain->SetBranchAddress("EF_tau12_loose_IdScan_xe15_noMu", &EF_tau12_loose_IdScan_xe15_noMu, &b_EF_tau12_loose_IdScan_xe15_noMu);
   fChain->SetBranchAddress("EF_tau12_loose_e10_loose", &EF_tau12_loose_e10_loose, &b_EF_tau12_loose_e10_loose);
   fChain->SetBranchAddress("EF_tau12_loose_e10_medium", &EF_tau12_loose_e10_medium, &b_EF_tau12_loose_e10_medium);
   fChain->SetBranchAddress("EF_tau12_loose_e10_tight", &EF_tau12_loose_e10_tight, &b_EF_tau12_loose_e10_tight);
   fChain->SetBranchAddress("EF_tau12_loose_mu10", &EF_tau12_loose_mu10, &b_EF_tau12_loose_mu10);
   fChain->SetBranchAddress("EF_tau12_loose_xe15_noMu", &EF_tau12_loose_xe15_noMu, &b_EF_tau12_loose_xe15_noMu);
   fChain->SetBranchAddress("EF_tau12_loose_xe20_noMu", &EF_tau12_loose_xe20_noMu, &b_EF_tau12_loose_xe20_noMu);
   fChain->SetBranchAddress("EF_tau16_loose", &EF_tau16_loose, &b_EF_tau16_loose);
   fChain->SetBranchAddress("EF_tau16_loose_2b15", &EF_tau16_loose_2b15, &b_EF_tau16_loose_2b15);
   fChain->SetBranchAddress("EF_tau16_loose_3j35_jetNoEF", &EF_tau16_loose_3j35_jetNoEF, &b_EF_tau16_loose_3j35_jetNoEF);
   fChain->SetBranchAddress("EF_tau16_loose_e10_loose", &EF_tau16_loose_e10_loose, &b_EF_tau16_loose_e10_loose);
   fChain->SetBranchAddress("EF_tau16_loose_e15_loose", &EF_tau16_loose_e15_loose, &b_EF_tau16_loose_e15_loose);
   fChain->SetBranchAddress("EF_tau16_loose_mu10", &EF_tau16_loose_mu10, &b_EF_tau16_loose_mu10);
   fChain->SetBranchAddress("EF_tau16_loose_mu15", &EF_tau16_loose_mu15, &b_EF_tau16_loose_mu15);
   fChain->SetBranchAddress("EF_tau16_loose_xe20_noMu", &EF_tau16_loose_xe20_noMu, &b_EF_tau16_loose_xe20_noMu);
   fChain->SetBranchAddress("EF_tau16_loose_xe25_noMu", &EF_tau16_loose_xe25_noMu, &b_EF_tau16_loose_xe25_noMu);
   fChain->SetBranchAddress("EF_tau16_loose_xe25_tight_noMu", &EF_tau16_loose_xe25_tight_noMu, &b_EF_tau16_loose_xe25_tight_noMu);
   fChain->SetBranchAddress("EF_tau16_loose_xe30_noMu", &EF_tau16_loose_xe30_noMu, &b_EF_tau16_loose_xe30_noMu);
   fChain->SetBranchAddress("EF_tau16_medium", &EF_tau16_medium, &b_EF_tau16_medium);
   fChain->SetBranchAddress("EF_tau16_medium_xe22_noMu", &EF_tau16_medium_xe22_noMu, &b_EF_tau16_medium_xe22_noMu);
   fChain->SetBranchAddress("EF_tau16_medium_xe25_noMu", &EF_tau16_medium_xe25_noMu, &b_EF_tau16_medium_xe25_noMu);
   fChain->SetBranchAddress("EF_tau16_medium_xe25_tight_noMu", &EF_tau16_medium_xe25_tight_noMu, &b_EF_tau16_medium_xe25_tight_noMu);
   fChain->SetBranchAddress("EF_tau20_loose", &EF_tau20_loose, &b_EF_tau20_loose);
   fChain->SetBranchAddress("EF_tau20_loose_xe25_noMu", &EF_tau20_loose_xe25_noMu, &b_EF_tau20_loose_xe25_noMu);
   fChain->SetBranchAddress("EF_tau29_loose", &EF_tau29_loose, &b_EF_tau29_loose);
   fChain->SetBranchAddress("EF_tau38_loose", &EF_tau38_loose, &b_EF_tau38_loose);
   fChain->SetBranchAddress("EF_tau38_medium", &EF_tau38_medium, &b_EF_tau38_medium);
   fChain->SetBranchAddress("EF_tau50_IDTrkNoCut", &EF_tau50_IDTrkNoCut, &b_EF_tau50_IDTrkNoCut);
   fChain->SetBranchAddress("EF_tau50_loose", &EF_tau50_loose, &b_EF_tau50_loose);
   fChain->SetBranchAddress("EF_tau50_loose_IdScan", &EF_tau50_loose_IdScan, &b_EF_tau50_loose_IdScan);
   fChain->SetBranchAddress("EF_tau50_medium", &EF_tau50_medium, &b_EF_tau50_medium);
   fChain->SetBranchAddress("EF_tau84_loose", &EF_tau84_loose, &b_EF_tau84_loose);
   fChain->SetBranchAddress("EF_tau84_medium", &EF_tau84_medium, &b_EF_tau84_medium);
   fChain->SetBranchAddress("EF_tauNoCut", &EF_tauNoCut, &b_EF_tauNoCut);
   fChain->SetBranchAddress("EF_tauNoCut_IdScan", &EF_tauNoCut_IdScan, &b_EF_tauNoCut_IdScan);
   fChain->SetBranchAddress("EF_tauNoCut_cosmic", &EF_tauNoCut_cosmic, &b_EF_tauNoCut_cosmic);
   fChain->SetBranchAddress("EF_tauNoCut_firstempty", &EF_tauNoCut_firstempty, &b_EF_tauNoCut_firstempty);
   fChain->SetBranchAddress("EF_tauNoCut_hasTrk6_EFxe15_noMu", &EF_tauNoCut_hasTrk6_EFxe15_noMu, &b_EF_tauNoCut_hasTrk6_EFxe15_noMu);
   fChain->SetBranchAddress("EF_tauNoCut_hasTrk6_IdScan_EFxe15_noMu", &EF_tauNoCut_hasTrk6_IdScan_EFxe15_noMu, &b_EF_tauNoCut_hasTrk6_IdScan_EFxe15_noMu);
   fChain->SetBranchAddress("EF_tauNoCut_hasTrk6_IdScan_xe20_noMu", &EF_tauNoCut_hasTrk6_IdScan_xe20_noMu, &b_EF_tauNoCut_hasTrk6_IdScan_xe20_noMu);
   fChain->SetBranchAddress("EF_tauNoCut_hasTrk6_xe20_noMu", &EF_tauNoCut_hasTrk6_xe20_noMu, &b_EF_tauNoCut_hasTrk6_xe20_noMu);
   fChain->SetBranchAddress("EF_tauNoCut_hasTrk9_xe20_noMu", &EF_tauNoCut_hasTrk9_xe20_noMu, &b_EF_tauNoCut_hasTrk9_xe20_noMu);
   fChain->SetBranchAddress("EF_tauNoCut_hasTrk_MV", &EF_tauNoCut_hasTrk_MV, &b_EF_tauNoCut_hasTrk_MV);
   fChain->SetBranchAddress("EF_tauNoCut_hasTrk_e10_tight", &EF_tauNoCut_hasTrk_e10_tight, &b_EF_tauNoCut_hasTrk_e10_tight);
   fChain->SetBranchAddress("EF_tauNoCut_hasTrk_xe20_noMu", &EF_tauNoCut_hasTrk_xe20_noMu, &b_EF_tauNoCut_hasTrk_xe20_noMu);
   fChain->SetBranchAddress("EF_tauNoCut_unpaired_iso", &EF_tauNoCut_unpaired_iso, &b_EF_tauNoCut_unpaired_iso);
   fChain->SetBranchAddress("EF_tauNoCut_unpaired_noniso", &EF_tauNoCut_unpaired_noniso, &b_EF_tauNoCut_unpaired_noniso);
   fChain->SetBranchAddress("EF_xe15_noMu", &EF_xe15_noMu, &b_EF_xe15_noMu);
   fChain->SetBranchAddress("EF_xe15_unbiased_noMu", &EF_xe15_unbiased_noMu, &b_EF_xe15_unbiased_noMu);
   fChain->SetBranchAddress("EF_xe20", &EF_xe20, &b_EF_xe20);
   fChain->SetBranchAddress("EF_xe20_noMu", &EF_xe20_noMu, &b_EF_xe20_noMu);
   fChain->SetBranchAddress("EF_xe20_tight_noMu", &EF_xe20_tight_noMu, &b_EF_xe20_tight_noMu);
   fChain->SetBranchAddress("EF_xe25_medium_noMu", &EF_xe25_medium_noMu, &b_EF_xe25_medium_noMu);
   fChain->SetBranchAddress("EF_xe25_noMu", &EF_xe25_noMu, &b_EF_xe25_noMu);
   fChain->SetBranchAddress("EF_xe25_tight_noMu", &EF_xe25_tight_noMu, &b_EF_xe25_tight_noMu);
   fChain->SetBranchAddress("EF_xe30_allL1", &EF_xe30_allL1, &b_EF_xe30_allL1);
   fChain->SetBranchAddress("EF_xe30_allL1_FEB", &EF_xe30_allL1_FEB, &b_EF_xe30_allL1_FEB);
   fChain->SetBranchAddress("EF_xe30_allL1_allCells", &EF_xe30_allL1_allCells, &b_EF_xe30_allL1_allCells);
   fChain->SetBranchAddress("EF_xe30_loose_noMu", &EF_xe30_loose_noMu, &b_EF_xe30_loose_noMu);
   fChain->SetBranchAddress("EF_xe30_medium_noMu", &EF_xe30_medium_noMu, &b_EF_xe30_medium_noMu);
   fChain->SetBranchAddress("EF_xe30_noMu", &EF_xe30_noMu, &b_EF_xe30_noMu);
   fChain->SetBranchAddress("EF_xe30_tight_noMu", &EF_xe30_tight_noMu, &b_EF_xe30_tight_noMu);
   fChain->SetBranchAddress("EF_xe35_loose_noMu", &EF_xe35_loose_noMu, &b_EF_xe35_loose_noMu);
   fChain->SetBranchAddress("EF_xe35_noMu", &EF_xe35_noMu, &b_EF_xe35_noMu);
   fChain->SetBranchAddress("EF_xe35_tight_noMu", &EF_xe35_tight_noMu, &b_EF_xe35_tight_noMu);
   fChain->SetBranchAddress("EF_xe40_noMu", &EF_xe40_noMu, &b_EF_xe40_noMu);
   fChain->SetBranchAddress("EF_xe45_noMu", &EF_xe45_noMu, &b_EF_xe45_noMu);
   fChain->SetBranchAddress("EF_xe55_noMu", &EF_xe55_noMu, &b_EF_xe55_noMu);
   fChain->SetBranchAddress("EF_xe60_medium_noMu", &EF_xe60_medium_noMu, &b_EF_xe60_medium_noMu);
   fChain->SetBranchAddress("EF_xe80_medium_noMu", &EF_xe80_medium_noMu, &b_EF_xe80_medium_noMu);
   fChain->SetBranchAddress("L1_2EM10", &L1_2EM10, &b_L1_2EM10);
   fChain->SetBranchAddress("L1_2EM14", &L1_2EM14, &b_L1_2EM14);
   fChain->SetBranchAddress("L1_2EM2", &L1_2EM2, &b_L1_2EM2);
   fChain->SetBranchAddress("L1_2EM3", &L1_2EM3, &b_L1_2EM3);
   fChain->SetBranchAddress("L1_2EM5", &L1_2EM5, &b_L1_2EM5);
   fChain->SetBranchAddress("L1_2J10", &L1_2J10, &b_L1_2J10);
   fChain->SetBranchAddress("L1_2J10_J30", &L1_2J10_J30, &b_L1_2J10_J30);
   fChain->SetBranchAddress("L1_2J10_J55", &L1_2J10_J55, &b_L1_2J10_J55);
   fChain->SetBranchAddress("L1_2J15", &L1_2J15, &b_L1_2J15);
   fChain->SetBranchAddress("L1_2J15_J75", &L1_2J15_J75, &b_L1_2J15_J75);
   fChain->SetBranchAddress("L1_2J15_XE10", &L1_2J15_XE10, &b_L1_2J15_XE10);
   fChain->SetBranchAddress("L1_2J15_XE15", &L1_2J15_XE15, &b_L1_2J15_XE15);
   fChain->SetBranchAddress("L1_2J15_XE25", &L1_2J15_XE25, &b_L1_2J15_XE25);
   fChain->SetBranchAddress("L1_2J30", &L1_2J30, &b_L1_2J30);
   fChain->SetBranchAddress("L1_2J5", &L1_2J5, &b_L1_2J5);
   fChain->SetBranchAddress("L1_2J55", &L1_2J55, &b_L1_2J55);
   fChain->SetBranchAddress("L1_2J95", &L1_2J95, &b_L1_2J95);
   fChain->SetBranchAddress("L1_2MU0", &L1_2MU0, &b_L1_2MU0);
   fChain->SetBranchAddress("L1_2MU0_FIRSTEMPTY", &L1_2MU0_FIRSTEMPTY, &b_L1_2MU0_FIRSTEMPTY);
   fChain->SetBranchAddress("L1_2MU0_MU6", &L1_2MU0_MU6, &b_L1_2MU0_MU6);
   fChain->SetBranchAddress("L1_2MU10", &L1_2MU10, &b_L1_2MU10);
   fChain->SetBranchAddress("L1_2MU20", &L1_2MU20, &b_L1_2MU20);
   fChain->SetBranchAddress("L1_2MU6", &L1_2MU6, &b_L1_2MU6);
   fChain->SetBranchAddress("L1_2MU6_EM5", &L1_2MU6_EM5, &b_L1_2MU6_EM5);
   fChain->SetBranchAddress("L1_2TAU11", &L1_2TAU11, &b_L1_2TAU11);
   fChain->SetBranchAddress("L1_2TAU5", &L1_2TAU5, &b_L1_2TAU5);
   fChain->SetBranchAddress("L1_2TAU5_EM5", &L1_2TAU5_EM5, &b_L1_2TAU5_EM5);
   fChain->SetBranchAddress("L1_2TAU6", &L1_2TAU6, &b_L1_2TAU6);
   fChain->SetBranchAddress("L1_2TAU6_EM10", &L1_2TAU6_EM10, &b_L1_2TAU6_EM10);
   fChain->SetBranchAddress("L1_2TAU6_EM5", &L1_2TAU6_EM5, &b_L1_2TAU6_EM5);
   fChain->SetBranchAddress("L1_3J10", &L1_3J10, &b_L1_3J10);
   fChain->SetBranchAddress("L1_3J10_2J30", &L1_3J10_2J30, &b_L1_3J10_2J30);
   fChain->SetBranchAddress("L1_3J15", &L1_3J15, &b_L1_3J15);
   fChain->SetBranchAddress("L1_3J30", &L1_3J30, &b_L1_3J30);
   fChain->SetBranchAddress("L1_3J5_J30", &L1_3J5_J30, &b_L1_3J5_J30);
   fChain->SetBranchAddress("L1_4J10", &L1_4J10, &b_L1_4J10);
   fChain->SetBranchAddress("L1_4J10_3J15", &L1_4J10_3J15, &b_L1_4J10_3J15);
   fChain->SetBranchAddress("L1_4J10_EM10", &L1_4J10_EM10, &b_L1_4J10_EM10);
   fChain->SetBranchAddress("L1_4J10_MU15", &L1_4J10_MU15, &b_L1_4J10_MU15);
   fChain->SetBranchAddress("L1_4J15", &L1_4J15, &b_L1_4J15);
   fChain->SetBranchAddress("L1_4J30", &L1_4J30, &b_L1_4J30);
   fChain->SetBranchAddress("L1_4J5", &L1_4J5, &b_L1_4J5);
   fChain->SetBranchAddress("L1_4J5_J15", &L1_4J5_J15, &b_L1_4J5_J15);
   fChain->SetBranchAddress("L1_4J5_J30", &L1_4J5_J30, &b_L1_4J5_J30);
   fChain->SetBranchAddress("L1_5J10", &L1_5J10, &b_L1_5J10);
   fChain->SetBranchAddress("L1_6J10", &L1_6J10, &b_L1_6J10);
   fChain->SetBranchAddress("L1_EM10", &L1_EM10, &b_L1_EM10);
   fChain->SetBranchAddress("L1_EM10I", &L1_EM10I, &b_L1_EM10I);
   fChain->SetBranchAddress("L1_EM14", &L1_EM14, &b_L1_EM14);
   fChain->SetBranchAddress("L1_EM14I", &L1_EM14I, &b_L1_EM14I);
   fChain->SetBranchAddress("L1_EM14_XE10", &L1_EM14_XE10, &b_L1_EM14_XE10);
   fChain->SetBranchAddress("L1_EM14_XE15", &L1_EM14_XE15, &b_L1_EM14_XE15);
   fChain->SetBranchAddress("L1_EM2", &L1_EM2, &b_L1_EM2);
   fChain->SetBranchAddress("L1_EM2_UNPAIRED_ISO", &L1_EM2_UNPAIRED_ISO, &b_L1_EM2_UNPAIRED_ISO);
   fChain->SetBranchAddress("L1_EM2_UNPAIRED_NONISO", &L1_EM2_UNPAIRED_NONISO, &b_L1_EM2_UNPAIRED_NONISO);
   fChain->SetBranchAddress("L1_EM3", &L1_EM3, &b_L1_EM3);
   fChain->SetBranchAddress("L1_EM3_EMPTY", &L1_EM3_EMPTY, &b_L1_EM3_EMPTY);
   fChain->SetBranchAddress("L1_EM3_FIRSTEMPTY", &L1_EM3_FIRSTEMPTY, &b_L1_EM3_FIRSTEMPTY);
   fChain->SetBranchAddress("L1_EM3_MV", &L1_EM3_MV, &b_L1_EM3_MV);
   fChain->SetBranchAddress("L1_EM5", &L1_EM5, &b_L1_EM5);
   fChain->SetBranchAddress("L1_EM5_MU10", &L1_EM5_MU10, &b_L1_EM5_MU10);
   fChain->SetBranchAddress("L1_EM5_MU6", &L1_EM5_MU6, &b_L1_EM5_MU6);
   fChain->SetBranchAddress("L1_EM85", &L1_EM85, &b_L1_EM85);
   fChain->SetBranchAddress("L1_FJ10", &L1_FJ10, &b_L1_FJ10);
   fChain->SetBranchAddress("L1_FJ10_EMPTY", &L1_FJ10_EMPTY, &b_L1_FJ10_EMPTY);
   fChain->SetBranchAddress("L1_FJ10_FIRSTEMPTY", &L1_FJ10_FIRSTEMPTY, &b_L1_FJ10_FIRSTEMPTY);
   fChain->SetBranchAddress("L1_FJ10_UNPAIRED_ISO", &L1_FJ10_UNPAIRED_ISO, &b_L1_FJ10_UNPAIRED_ISO);
   fChain->SetBranchAddress("L1_FJ30", &L1_FJ30, &b_L1_FJ30);
   fChain->SetBranchAddress("L1_FJ55", &L1_FJ55, &b_L1_FJ55);
   fChain->SetBranchAddress("L1_FJ95", &L1_FJ95, &b_L1_FJ95);
   fChain->SetBranchAddress("L1_J10", &L1_J10, &b_L1_J10);
   fChain->SetBranchAddress("L1_J10_EMPTY", &L1_J10_EMPTY, &b_L1_J10_EMPTY);
   fChain->SetBranchAddress("L1_J10_FIRSTEMPTY", &L1_J10_FIRSTEMPTY, &b_L1_J10_FIRSTEMPTY);
   fChain->SetBranchAddress("L1_J10_FJ10", &L1_J10_FJ10, &b_L1_J10_FJ10);
   fChain->SetBranchAddress("L1_J10_MV", &L1_J10_MV, &b_L1_J10_MV);
   fChain->SetBranchAddress("L1_J10_UNPAIRED", &L1_J10_UNPAIRED, &b_L1_J10_UNPAIRED);
   fChain->SetBranchAddress("L1_J115", &L1_J115, &b_L1_J115);
   fChain->SetBranchAddress("L1_J15", &L1_J15, &b_L1_J15);
   fChain->SetBranchAddress("L1_J15_LV", &L1_J15_LV, &b_L1_J15_LV);
   fChain->SetBranchAddress("L1_J15_MV", &L1_J15_MV, &b_L1_J15_MV);
   fChain->SetBranchAddress("L1_J15_NL", &L1_J15_NL, &b_L1_J15_NL);
   fChain->SetBranchAddress("L1_J15_XE15_EM10", &L1_J15_XE15_EM10, &b_L1_J15_XE15_EM10);
   fChain->SetBranchAddress("L1_J15_XE15_MU15", &L1_J15_XE15_MU15, &b_L1_J15_XE15_MU15);
   fChain->SetBranchAddress("L1_J30", &L1_J30, &b_L1_J30);
   fChain->SetBranchAddress("L1_J30_EMPTY", &L1_J30_EMPTY, &b_L1_J30_EMPTY);
   fChain->SetBranchAddress("L1_J30_FIRSTEMPTY", &L1_J30_FIRSTEMPTY, &b_L1_J30_FIRSTEMPTY);
   fChain->SetBranchAddress("L1_J30_UNPAIRED", &L1_J30_UNPAIRED, &b_L1_J30_UNPAIRED);
   fChain->SetBranchAddress("L1_J30_XE10", &L1_J30_XE10, &b_L1_J30_XE10);
   fChain->SetBranchAddress("L1_J30_XE15", &L1_J30_XE15, &b_L1_J30_XE15);
   fChain->SetBranchAddress("L1_J30_XE25", &L1_J30_XE25, &b_L1_J30_XE25);
   fChain->SetBranchAddress("L1_J5", &L1_J5, &b_L1_J5);
   fChain->SetBranchAddress("L1_J55", &L1_J55, &b_L1_J55);
   fChain->SetBranchAddress("L1_J5_EMPTY", &L1_J5_EMPTY, &b_L1_J5_EMPTY);
   fChain->SetBranchAddress("L1_J5_FIRSTEMPTY", &L1_J5_FIRSTEMPTY, &b_L1_J5_FIRSTEMPTY);
   fChain->SetBranchAddress("L1_J5_UNPAIRED_ISO", &L1_J5_UNPAIRED_ISO, &b_L1_J5_UNPAIRED_ISO);
   fChain->SetBranchAddress("L1_J5_UNPAIRED_NONISO", &L1_J5_UNPAIRED_NONISO, &b_L1_J5_UNPAIRED_NONISO);
   fChain->SetBranchAddress("L1_J75", &L1_J75, &b_L1_J75);
   fChain->SetBranchAddress("L1_J95", &L1_J95, &b_L1_J95);
   fChain->SetBranchAddress("L1_JE100", &L1_JE100, &b_L1_JE100);
   fChain->SetBranchAddress("L1_JE140", &L1_JE140, &b_L1_JE140);
   fChain->SetBranchAddress("L1_JE200", &L1_JE200, &b_L1_JE200);
   fChain->SetBranchAddress("L1_JE60", &L1_JE60, &b_L1_JE60);
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
   fChain->SetBranchAddress("L1_RD0_EMPTY", &L1_RD0_EMPTY, &b_L1_RD0_EMPTY);
   fChain->SetBranchAddress("L1_RD0_FILLED", &L1_RD0_FILLED, &b_L1_RD0_FILLED);
   fChain->SetBranchAddress("L1_RD0_FIRSTEMPTY", &L1_RD0_FIRSTEMPTY, &b_L1_RD0_FIRSTEMPTY);
   fChain->SetBranchAddress("L1_RD0_UNPAIRED_ISO", &L1_RD0_UNPAIRED_ISO, &b_L1_RD0_UNPAIRED_ISO);
   fChain->SetBranchAddress("L1_RD1_EMPTY", &L1_RD1_EMPTY, &b_L1_RD1_EMPTY);
   fChain->SetBranchAddress("L1_RD1_FILLED", &L1_RD1_FILLED, &b_L1_RD1_FILLED);
   fChain->SetBranchAddress("L1_TAU11", &L1_TAU11, &b_L1_TAU11);
   fChain->SetBranchAddress("L1_TAU11I", &L1_TAU11I, &b_L1_TAU11I);
   fChain->SetBranchAddress("L1_TAU20", &L1_TAU20, &b_L1_TAU20);
   fChain->SetBranchAddress("L1_TAU30", &L1_TAU30, &b_L1_TAU30);
   fChain->SetBranchAddress("L1_TAU5", &L1_TAU5, &b_L1_TAU5);
   fChain->SetBranchAddress("L1_TAU50", &L1_TAU50, &b_L1_TAU50);
   fChain->SetBranchAddress("L1_TAU5_3J5_2J15", &L1_TAU5_3J5_2J15, &b_L1_TAU5_3J5_2J15);
   fChain->SetBranchAddress("L1_TAU5_4J5_3J15", &L1_TAU5_4J5_3J15, &b_L1_TAU5_4J5_3J15);
   fChain->SetBranchAddress("L1_TAU5_EMPTY", &L1_TAU5_EMPTY, &b_L1_TAU5_EMPTY);
   fChain->SetBranchAddress("L1_TAU5_FIRSTEMPTY", &L1_TAU5_FIRSTEMPTY, &b_L1_TAU5_FIRSTEMPTY);
   fChain->SetBranchAddress("L1_TAU5_MU6", &L1_TAU5_MU6, &b_L1_TAU5_MU6);
   fChain->SetBranchAddress("L1_TAU5_MV", &L1_TAU5_MV, &b_L1_TAU5_MV);
   fChain->SetBranchAddress("L1_TAU5_UNPAIRED_ISO", &L1_TAU5_UNPAIRED_ISO, &b_L1_TAU5_UNPAIRED_ISO);
   fChain->SetBranchAddress("L1_TAU5_UNPAIRED_NONISO", &L1_TAU5_UNPAIRED_NONISO, &b_L1_TAU5_UNPAIRED_NONISO);
   fChain->SetBranchAddress("L1_TAU5_XE10", &L1_TAU5_XE10, &b_L1_TAU5_XE10);
   fChain->SetBranchAddress("L1_TAU6", &L1_TAU6, &b_L1_TAU6);
   fChain->SetBranchAddress("L1_TAU6I", &L1_TAU6I, &b_L1_TAU6I);
   fChain->SetBranchAddress("L1_TAU6_3J5_2J15", &L1_TAU6_3J5_2J15, &b_L1_TAU6_3J5_2J15);
   fChain->SetBranchAddress("L1_TAU6_4J5_3J15", &L1_TAU6_4J5_3J15, &b_L1_TAU6_4J5_3J15);
   fChain->SetBranchAddress("L1_TAU6_MU10", &L1_TAU6_MU10, &b_L1_TAU6_MU10);
   fChain->SetBranchAddress("L1_TAU6_MU15", &L1_TAU6_MU15, &b_L1_TAU6_MU15);
   fChain->SetBranchAddress("L1_TAU6_XE10", &L1_TAU6_XE10, &b_L1_TAU6_XE10);
   fChain->SetBranchAddress("L1_TE100", &L1_TE100, &b_L1_TE100);
   fChain->SetBranchAddress("L1_TE180", &L1_TE180, &b_L1_TE180);
   fChain->SetBranchAddress("L1_TE20", &L1_TE20, &b_L1_TE20);
   fChain->SetBranchAddress("L1_TE50", &L1_TE50, &b_L1_TE50);
   fChain->SetBranchAddress("L1_XE10", &L1_XE10, &b_L1_XE10);
   fChain->SetBranchAddress("L1_XE15", &L1_XE15, &b_L1_XE15);
   fChain->SetBranchAddress("L1_XE20", &L1_XE20, &b_L1_XE20);
   fChain->SetBranchAddress("L1_XE25", &L1_XE25, &b_L1_XE25);
   fChain->SetBranchAddress("L1_XE30", &L1_XE30, &b_L1_XE30);
   fChain->SetBranchAddress("L1_XE35", &L1_XE35, &b_L1_XE35);
   fChain->SetBranchAddress("L1_XE40", &L1_XE40, &b_L1_XE40);
   fChain->SetBranchAddress("L1_XE50", &L1_XE50, &b_L1_XE50);
   fChain->SetBranchAddress("L1_ZB", &L1_ZB, &b_L1_ZB);
   fChain->SetBranchAddress("L2_2e10_loose", &L2_2e10_loose, &b_L2_2e10_loose);
   fChain->SetBranchAddress("L2_2e10_medium", &L2_2e10_medium, &b_L2_2e10_medium);
   fChain->SetBranchAddress("L2_2e15_loose", &L2_2e15_loose, &b_L2_2e15_loose);
   fChain->SetBranchAddress("L2_2e3_loose", &L2_2e3_loose, &b_L2_2e3_loose);
   fChain->SetBranchAddress("L2_2e3_loose_SiTrk", &L2_2e3_loose_SiTrk, &b_L2_2e3_loose_SiTrk);
   fChain->SetBranchAddress("L2_2e3_loose_TRT", &L2_2e3_loose_TRT, &b_L2_2e3_loose_TRT);
   fChain->SetBranchAddress("L2_2e3_medium", &L2_2e3_medium, &b_L2_2e3_medium);
   fChain->SetBranchAddress("L2_2e3_medium_SiTrk", &L2_2e3_medium_SiTrk, &b_L2_2e3_medium_SiTrk);
   fChain->SetBranchAddress("L2_2e3_medium_TRT", &L2_2e3_medium_TRT, &b_L2_2e3_medium_TRT);
   fChain->SetBranchAddress("L2_2e3_tight", &L2_2e3_tight, &b_L2_2e3_tight);
   fChain->SetBranchAddress("L2_2e5_medium", &L2_2e5_medium, &b_L2_2e5_medium);
   fChain->SetBranchAddress("L2_2e5_medium_SiTrk", &L2_2e5_medium_SiTrk, &b_L2_2e5_medium_SiTrk);
   fChain->SetBranchAddress("L2_2e5_medium_TRT", &L2_2e5_medium_TRT, &b_L2_2e5_medium_TRT);
   fChain->SetBranchAddress("L2_2e5_tight", &L2_2e5_tight, &b_L2_2e5_tight);
   fChain->SetBranchAddress("L2_2g10_loose", &L2_2g10_loose, &b_L2_2g10_loose);
   fChain->SetBranchAddress("L2_2g15_loose", &L2_2g15_loose, &b_L2_2g15_loose);
   fChain->SetBranchAddress("L2_2g5_loose", &L2_2g5_loose, &b_L2_2g5_loose);
   fChain->SetBranchAddress("L2_2g7_loose", &L2_2g7_loose, &b_L2_2g7_loose);
   fChain->SetBranchAddress("L2_2j15", &L2_2j15, &b_L2_2j15);
   fChain->SetBranchAddress("L2_2j15_deta3_5", &L2_2j15_deta3_5, &b_L2_2j15_deta3_5);
   fChain->SetBranchAddress("L2_2j15_deta5", &L2_2j15_deta5, &b_L2_2j15_deta5);
   fChain->SetBranchAddress("L2_2j25", &L2_2j25, &b_L2_2j25);
   fChain->SetBranchAddress("L2_2j25_deta3_5", &L2_2j25_deta3_5, &b_L2_2j25_deta3_5);
   fChain->SetBranchAddress("L2_2j25_j45_anymct100", &L2_2j25_j45_anymct100, &b_L2_2j25_j45_anymct100);
   fChain->SetBranchAddress("L2_2j25_j45_anymct150", &L2_2j25_j45_anymct150, &b_L2_2j25_j45_anymct150);
   fChain->SetBranchAddress("L2_2j25_j45_anymct175", &L2_2j25_j45_anymct175, &b_L2_2j25_j45_anymct175);
   fChain->SetBranchAddress("L2_2j25_j45_dphi03", &L2_2j25_j45_dphi03, &b_L2_2j25_j45_dphi03);
   fChain->SetBranchAddress("L2_2j25_j45_leadingmct100", &L2_2j25_j45_leadingmct100, &b_L2_2j25_j45_leadingmct100);
   fChain->SetBranchAddress("L2_2j25_j45_leadingmct150", &L2_2j25_j45_leadingmct150, &b_L2_2j25_j45_leadingmct150);
   fChain->SetBranchAddress("L2_2j25_j45_leadingmct175", &L2_2j25_j45_leadingmct175, &b_L2_2j25_j45_leadingmct175);
   fChain->SetBranchAddress("L2_2j25_j70_anymct150", &L2_2j25_j70_anymct150, &b_L2_2j25_j70_anymct150);
   fChain->SetBranchAddress("L2_2j25_j70_anymct175", &L2_2j25_j70_anymct175, &b_L2_2j25_j70_anymct175);
   fChain->SetBranchAddress("L2_2j25_j70_dphi03", &L2_2j25_j70_dphi03, &b_L2_2j25_j70_dphi03);
   fChain->SetBranchAddress("L2_2j25_j70_leadingmct150", &L2_2j25_j70_leadingmct150, &b_L2_2j25_j70_leadingmct150);
   fChain->SetBranchAddress("L2_2j25_j70_leadingmct175", &L2_2j25_j70_leadingmct175, &b_L2_2j25_j70_leadingmct175);
   fChain->SetBranchAddress("L2_2j30", &L2_2j30, &b_L2_2j30);
   fChain->SetBranchAddress("L2_2j30_anymct100", &L2_2j30_anymct100, &b_L2_2j30_anymct100);
   fChain->SetBranchAddress("L2_2j30_anymct150", &L2_2j30_anymct150, &b_L2_2j30_anymct150);
   fChain->SetBranchAddress("L2_2j30_anymct175", &L2_2j30_anymct175, &b_L2_2j30_anymct175);
   fChain->SetBranchAddress("L2_2j30_deta3_5", &L2_2j30_deta3_5, &b_L2_2j30_deta3_5);
   fChain->SetBranchAddress("L2_2j30_j90_dphi03", &L2_2j30_j90_dphi03, &b_L2_2j30_j90_dphi03);
   fChain->SetBranchAddress("L2_2j30_leadingmct100", &L2_2j30_leadingmct100, &b_L2_2j30_leadingmct100);
   fChain->SetBranchAddress("L2_2j30_leadingmct150", &L2_2j30_leadingmct150, &b_L2_2j30_leadingmct150);
   fChain->SetBranchAddress("L2_2j30_leadingmct175", &L2_2j30_leadingmct175, &b_L2_2j30_leadingmct175);
   fChain->SetBranchAddress("L2_2j35_jetNoEF_xe20_noMu", &L2_2j35_jetNoEF_xe20_noMu, &b_L2_2j35_jetNoEF_xe20_noMu);
   fChain->SetBranchAddress("L2_2j35_jetNoEF_xe30_noMu", &L2_2j35_jetNoEF_xe30_noMu, &b_L2_2j35_jetNoEF_xe30_noMu);
   fChain->SetBranchAddress("L2_2j35_jetNoEF_xe40_noMu", &L2_2j35_jetNoEF_xe40_noMu, &b_L2_2j35_jetNoEF_xe40_noMu);
   fChain->SetBranchAddress("L2_2j45", &L2_2j45, &b_L2_2j45);
   fChain->SetBranchAddress("L2_2j70", &L2_2j70, &b_L2_2j70);
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
   fChain->SetBranchAddress("L2_2mu4_Upsimumu", &L2_2mu4_Upsimumu, &b_L2_2mu4_Upsimumu);
   fChain->SetBranchAddress("L2_2mu6", &L2_2mu6, &b_L2_2mu6);
   fChain->SetBranchAddress("L2_2mu6_MG", &L2_2mu6_MG, &b_L2_2mu6_MG);
   fChain->SetBranchAddress("L2_2mu6_NoAlg", &L2_2mu6_NoAlg, &b_L2_2mu6_NoAlg);
   fChain->SetBranchAddress("L2_3j15_j45", &L2_3j15_j45, &b_L2_3j15_j45);
   fChain->SetBranchAddress("L2_3j25", &L2_3j25, &b_L2_3j25);
   fChain->SetBranchAddress("L2_3j25_2j45", &L2_3j25_2j45, &b_L2_3j25_2j45);
   fChain->SetBranchAddress("L2_3j30", &L2_3j30, &b_L2_3j30);
   fChain->SetBranchAddress("L2_3j45", &L2_3j45, &b_L2_3j45);
   fChain->SetBranchAddress("L2_4j15_j30", &L2_4j15_j30, &b_L2_4j15_j30);
   fChain->SetBranchAddress("L2_4j15_j45", &L2_4j15_j45, &b_L2_4j15_j45);
   fChain->SetBranchAddress("L2_4j25", &L2_4j25, &b_L2_4j25);
   fChain->SetBranchAddress("L2_4j25_3j30", &L2_4j25_3j30, &b_L2_4j25_3j30);
   fChain->SetBranchAddress("L2_4j30", &L2_4j30, &b_L2_4j30);
   fChain->SetBranchAddress("L2_4j45", &L2_4j45, &b_L2_4j45);
   fChain->SetBranchAddress("L2_5j25", &L2_5j25, &b_L2_5j25);
   fChain->SetBranchAddress("L2_6j25", &L2_6j25, &b_L2_6j25);
   fChain->SetBranchAddress("L2_e10_NoCut", &L2_e10_NoCut, &b_L2_e10_NoCut);
   fChain->SetBranchAddress("L2_e10_loose", &L2_e10_loose, &b_L2_e10_loose);
   fChain->SetBranchAddress("L2_e10_loose_mu10", &L2_e10_loose_mu10, &b_L2_e10_loose_mu10);
   fChain->SetBranchAddress("L2_e10_loose_mu6", &L2_e10_loose_mu6, &b_L2_e10_loose_mu6);
   fChain->SetBranchAddress("L2_e10_medium", &L2_e10_medium, &b_L2_e10_medium);
   fChain->SetBranchAddress("L2_e10_medium_IDTrkNoCut", &L2_e10_medium_IDTrkNoCut, &b_L2_e10_medium_IDTrkNoCut);
   fChain->SetBranchAddress("L2_e10_medium_SiTrk", &L2_e10_medium_SiTrk, &b_L2_e10_medium_SiTrk);
   fChain->SetBranchAddress("L2_e10_medium_TRT", &L2_e10_medium_TRT, &b_L2_e10_medium_TRT);
   fChain->SetBranchAddress("L2_e10_tight", &L2_e10_tight, &b_L2_e10_tight);
   fChain->SetBranchAddress("L2_e15_loose", &L2_e15_loose, &b_L2_e15_loose);
   fChain->SetBranchAddress("L2_e15_loose_IDTrkNoCut", &L2_e15_loose_IDTrkNoCut, &b_L2_e15_loose_IDTrkNoCut);
   fChain->SetBranchAddress("L2_e15_medium", &L2_e15_medium, &b_L2_e15_medium);
   fChain->SetBranchAddress("L2_e15_medium_SiTrk", &L2_e15_medium_SiTrk, &b_L2_e15_medium_SiTrk);
   fChain->SetBranchAddress("L2_e15_medium_TRT", &L2_e15_medium_TRT, &b_L2_e15_medium_TRT);
   fChain->SetBranchAddress("L2_e15_tight", &L2_e15_tight, &b_L2_e15_tight);
   fChain->SetBranchAddress("L2_e18_medium", &L2_e18_medium, &b_L2_e18_medium);
   fChain->SetBranchAddress("L2_e20_loose", &L2_e20_loose, &b_L2_e20_loose);
   fChain->SetBranchAddress("L2_e20_loose_IDTrkNoCut", &L2_e20_loose_IDTrkNoCut, &b_L2_e20_loose_IDTrkNoCut);
   fChain->SetBranchAddress("L2_e20_loose_passEF", &L2_e20_loose_passEF, &b_L2_e20_loose_passEF);
   fChain->SetBranchAddress("L2_e20_loose_passL2", &L2_e20_loose_passL2, &b_L2_e20_loose_passL2);
   fChain->SetBranchAddress("L2_e20_loose_xe20_noMu", &L2_e20_loose_xe20_noMu, &b_L2_e20_loose_xe20_noMu);
   fChain->SetBranchAddress("L2_e20_loose_xe30_noMu", &L2_e20_loose_xe30_noMu, &b_L2_e20_loose_xe30_noMu);
   fChain->SetBranchAddress("L2_e20_medium", &L2_e20_medium, &b_L2_e20_medium);
   fChain->SetBranchAddress("L2_e25_loose", &L2_e25_loose, &b_L2_e25_loose);
   fChain->SetBranchAddress("L2_e30_loose", &L2_e30_loose, &b_L2_e30_loose);
   fChain->SetBranchAddress("L2_e3_loose", &L2_e3_loose, &b_L2_e3_loose);
   fChain->SetBranchAddress("L2_e3_loose_SiTrk", &L2_e3_loose_SiTrk, &b_L2_e3_loose_SiTrk);
   fChain->SetBranchAddress("L2_e3_loose_TRT", &L2_e3_loose_TRT, &b_L2_e3_loose_TRT);
   fChain->SetBranchAddress("L2_e3_medium", &L2_e3_medium, &b_L2_e3_medium);
   fChain->SetBranchAddress("L2_e3_medium_SiTrk", &L2_e3_medium_SiTrk, &b_L2_e3_medium_SiTrk);
   fChain->SetBranchAddress("L2_e3_medium_TRT", &L2_e3_medium_TRT, &b_L2_e3_medium_TRT);
   fChain->SetBranchAddress("L2_e5_NoCut_firstempty", &L2_e5_NoCut_firstempty, &b_L2_e5_NoCut_firstempty);
   fChain->SetBranchAddress("L2_e5_medium", &L2_e5_medium, &b_L2_e5_medium);
   fChain->SetBranchAddress("L2_e5_medium_MV", &L2_e5_medium_MV, &b_L2_e5_medium_MV);
   fChain->SetBranchAddress("L2_e5_medium_SiTrk", &L2_e5_medium_SiTrk, &b_L2_e5_medium_SiTrk);
   fChain->SetBranchAddress("L2_e5_medium_TRT", &L2_e5_medium_TRT, &b_L2_e5_medium_TRT);
   fChain->SetBranchAddress("L2_e5_medium_mu4", &L2_e5_medium_mu4, &b_L2_e5_medium_mu4);
   fChain->SetBranchAddress("L2_e5_tight", &L2_e5_tight, &b_L2_e5_tight);
   fChain->SetBranchAddress("L2_e5_tight_SiTrk", &L2_e5_tight_SiTrk, &b_L2_e5_tight_SiTrk);
   fChain->SetBranchAddress("L2_e5_tight_TRT", &L2_e5_tight_TRT, &b_L2_e5_tight_TRT);
   fChain->SetBranchAddress("L2_e5_tight_e5_NoCut", &L2_e5_tight_e5_NoCut, &b_L2_e5_tight_e5_NoCut);
   fChain->SetBranchAddress("L2_eb_physics", &L2_eb_physics, &b_L2_eb_physics);
   fChain->SetBranchAddress("L2_eb_physics_empty", &L2_eb_physics_empty, &b_L2_eb_physics_empty);
   fChain->SetBranchAddress("L2_eb_physics_firstempty", &L2_eb_physics_firstempty, &b_L2_eb_physics_firstempty);
   fChain->SetBranchAddress("L2_eb_physics_unpaired_iso", &L2_eb_physics_unpaired_iso, &b_L2_eb_physics_unpaired_iso);
   fChain->SetBranchAddress("L2_eb_physics_unpaired_noniso", &L2_eb_physics_unpaired_noniso, &b_L2_eb_physics_unpaired_noniso);
   fChain->SetBranchAddress("L2_eb_random", &L2_eb_random, &b_L2_eb_random);
   fChain->SetBranchAddress("L2_eb_random_empty", &L2_eb_random_empty, &b_L2_eb_random_empty);
   fChain->SetBranchAddress("L2_eb_random_firstempty", &L2_eb_random_firstempty, &b_L2_eb_random_firstempty);
   fChain->SetBranchAddress("L2_eb_random_unpaired_iso", &L2_eb_random_unpaired_iso, &b_L2_eb_random_unpaired_iso);
   fChain->SetBranchAddress("L2_em105_passHLT", &L2_em105_passHLT, &b_L2_em105_passHLT);
   fChain->SetBranchAddress("L2_em3_empty_larcalib", &L2_em3_empty_larcalib, &b_L2_em3_empty_larcalib);
   fChain->SetBranchAddress("L2_fj10_empty_NoAlg", &L2_fj10_empty_NoAlg, &b_L2_fj10_empty_NoAlg);
   fChain->SetBranchAddress("L2_fj25", &L2_fj25, &b_L2_fj25);
   fChain->SetBranchAddress("L2_fj25_larcalib", &L2_fj25_larcalib, &b_L2_fj25_larcalib);
   fChain->SetBranchAddress("L2_fj45", &L2_fj45, &b_L2_fj45);
   fChain->SetBranchAddress("L2_fj45_larcalib", &L2_fj45_larcalib, &b_L2_fj45_larcalib);
   fChain->SetBranchAddress("L2_fj70", &L2_fj70, &b_L2_fj70);
   fChain->SetBranchAddress("L2_fj95_jetNoCut_larcalib", &L2_fj95_jetNoCut_larcalib, &b_L2_fj95_jetNoCut_larcalib);
   fChain->SetBranchAddress("L2_g10_loose", &L2_g10_loose, &b_L2_g10_loose);
   fChain->SetBranchAddress("L2_g11_etcut", &L2_g11_etcut, &b_L2_g11_etcut);
   fChain->SetBranchAddress("L2_g15_loose", &L2_g15_loose, &b_L2_g15_loose);
   fChain->SetBranchAddress("L2_g17_etcut", &L2_g17_etcut, &b_L2_g17_etcut);
   fChain->SetBranchAddress("L2_g17_etcut_EFxe20_noMu", &L2_g17_etcut_EFxe20_noMu, &b_L2_g17_etcut_EFxe20_noMu);
   fChain->SetBranchAddress("L2_g17_etcut_EFxe30_noMu", &L2_g17_etcut_EFxe30_noMu, &b_L2_g17_etcut_EFxe30_noMu);
   fChain->SetBranchAddress("L2_g20_loose", &L2_g20_loose, &b_L2_g20_loose);
   fChain->SetBranchAddress("L2_g20_loose_xe20_noMu", &L2_g20_loose_xe20_noMu, &b_L2_g20_loose_xe20_noMu);
   fChain->SetBranchAddress("L2_g20_loose_xe30_noMu", &L2_g20_loose_xe30_noMu, &b_L2_g20_loose_xe30_noMu);
   fChain->SetBranchAddress("L2_g20_tight", &L2_g20_tight, &b_L2_g20_tight);
   fChain->SetBranchAddress("L2_g25_loose_xe30_noMu", &L2_g25_loose_xe30_noMu, &b_L2_g25_loose_xe30_noMu);
   fChain->SetBranchAddress("L2_g30_loose", &L2_g30_loose, &b_L2_g30_loose);
   fChain->SetBranchAddress("L2_g30_tight", &L2_g30_tight, &b_L2_g30_tight);
   fChain->SetBranchAddress("L2_g3_NoCut_unpaired_iso", &L2_g3_NoCut_unpaired_iso, &b_L2_g3_NoCut_unpaired_iso);
   fChain->SetBranchAddress("L2_g3_NoCut_unpaired_noniso", &L2_g3_NoCut_unpaired_noniso, &b_L2_g3_NoCut_unpaired_noniso);
   fChain->SetBranchAddress("L2_g40_loose", &L2_g40_loose, &b_L2_g40_loose);
   fChain->SetBranchAddress("L2_g40_tight", &L2_g40_tight, &b_L2_g40_tight);
   fChain->SetBranchAddress("L2_g50_loose", &L2_g50_loose, &b_L2_g50_loose);
   fChain->SetBranchAddress("L2_g5_NoCut_cosmic", &L2_g5_NoCut_cosmic, &b_L2_g5_NoCut_cosmic);
   fChain->SetBranchAddress("L2_g5_loose", &L2_g5_loose, &b_L2_g5_loose);
   fChain->SetBranchAddress("L2_g7_loose", &L2_g7_loose, &b_L2_g7_loose);
   fChain->SetBranchAddress("L2_j115_jetNoCut_larcalib", &L2_j115_jetNoCut_larcalib, &b_L2_j115_jetNoCut_larcalib);
   fChain->SetBranchAddress("L2_j15", &L2_j15, &b_L2_j15);
   fChain->SetBranchAddress("L2_j15_larcalib", &L2_j15_larcalib, &b_L2_j15_larcalib);
   fChain->SetBranchAddress("L2_j25", &L2_j25, &b_L2_j25);
   fChain->SetBranchAddress("L2_j25_fj25", &L2_j25_fj25, &b_L2_j25_fj25);
   fChain->SetBranchAddress("L2_j25_jetNoCut_cosmic", &L2_j25_jetNoCut_cosmic, &b_L2_j25_jetNoCut_cosmic);
   fChain->SetBranchAddress("L2_j25_jetNoCut_firstempty", &L2_j25_jetNoCut_firstempty, &b_L2_j25_jetNoCut_firstempty);
   fChain->SetBranchAddress("L2_j25_jetNoCut_unpaired", &L2_j25_jetNoCut_unpaired, &b_L2_j25_jetNoCut_unpaired);
   fChain->SetBranchAddress("L2_j30", &L2_j30, &b_L2_j30);
   fChain->SetBranchAddress("L2_j30_L1TAU_HV", &L2_j30_L1TAU_HV, &b_L2_j30_L1TAU_HV);
   fChain->SetBranchAddress("L2_j30_Trackless_HV", &L2_j30_Trackless_HV, &b_L2_j30_Trackless_HV);
   fChain->SetBranchAddress("L2_j45", &L2_j45, &b_L2_j45);
   fChain->SetBranchAddress("L2_j45_jetNoCut_cosmic", &L2_j45_jetNoCut_cosmic, &b_L2_j45_jetNoCut_cosmic);
   fChain->SetBranchAddress("L2_j45_jetNoCut_firstempty", &L2_j45_jetNoCut_firstempty, &b_L2_j45_jetNoCut_firstempty);
   fChain->SetBranchAddress("L2_j45_jetNoCut_unpaired", &L2_j45_jetNoCut_unpaired, &b_L2_j45_jetNoCut_unpaired);
   fChain->SetBranchAddress("L2_j45_larcalib", &L2_j45_larcalib, &b_L2_j45_larcalib);
   fChain->SetBranchAddress("L2_j45_xe12_noMu", &L2_j45_xe12_noMu, &b_L2_j45_xe12_noMu);
   fChain->SetBranchAddress("L2_j45_xe20_noMu", &L2_j45_xe20_noMu, &b_L2_j45_xe20_noMu);
   fChain->SetBranchAddress("L2_j45_xe30_noMu", &L2_j45_xe30_noMu, &b_L2_j45_xe30_noMu);
   fChain->SetBranchAddress("L2_j5_empty_NoAlg", &L2_j5_empty_NoAlg, &b_L2_j5_empty_NoAlg);
   fChain->SetBranchAddress("L2_j5_empty_larcalib", &L2_j5_empty_larcalib, &b_L2_j5_empty_larcalib);
   fChain->SetBranchAddress("L2_j5_unpaired_iso_NoAlg", &L2_j5_unpaired_iso_NoAlg, &b_L2_j5_unpaired_iso_NoAlg);
   fChain->SetBranchAddress("L2_j5_unpaired_noniso_NoAlg", &L2_j5_unpaired_noniso_NoAlg, &b_L2_j5_unpaired_noniso_NoAlg);
   fChain->SetBranchAddress("L2_j70", &L2_j70, &b_L2_j70);
   fChain->SetBranchAddress("L2_j70_EFxe20_noMu", &L2_j70_EFxe20_noMu, &b_L2_j70_EFxe20_noMu);
   fChain->SetBranchAddress("L2_j70_EFxe25_noMu", &L2_j70_EFxe25_noMu, &b_L2_j70_EFxe25_noMu);
   fChain->SetBranchAddress("L2_j70_EFxe30_noMu", &L2_j70_EFxe30_noMu, &b_L2_j70_EFxe30_noMu);
   fChain->SetBranchAddress("L2_j70_EFxe35_noMu", &L2_j70_EFxe35_noMu, &b_L2_j70_EFxe35_noMu);
   fChain->SetBranchAddress("L2_j70_EFxe40_noMu", &L2_j70_EFxe40_noMu, &b_L2_j70_EFxe40_noMu);
   fChain->SetBranchAddress("L2_j90", &L2_j90, &b_L2_j90);
   fChain->SetBranchAddress("L2_j90_larcalib", &L2_j90_larcalib, &b_L2_j90_larcalib);
   fChain->SetBranchAddress("L2_je135", &L2_je135, &b_L2_je135);
   fChain->SetBranchAddress("L2_je195", &L2_je195, &b_L2_je195);
   fChain->SetBranchAddress("L2_je255", &L2_je255, &b_L2_je255);
   fChain->SetBranchAddress("L2_je350", &L2_je350, &b_L2_je350);
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
   fChain->SetBranchAddress("L2_mu10_IDTrkNoCut", &L2_mu10_IDTrkNoCut, &b_L2_mu10_IDTrkNoCut);
   fChain->SetBranchAddress("L2_mu10_MG", &L2_mu10_MG, &b_L2_mu10_MG);
   fChain->SetBranchAddress("L2_mu10_MSonly", &L2_mu10_MSonly, &b_L2_mu10_MSonly);
   fChain->SetBranchAddress("L2_mu10_MSonly_tight", &L2_mu10_MSonly_tight, &b_L2_mu10_MSonly_tight);
   fChain->SetBranchAddress("L2_mu10_NoAlg", &L2_mu10_NoAlg, &b_L2_mu10_NoAlg);
   fChain->SetBranchAddress("L2_mu10_SiTrk", &L2_mu10_SiTrk, &b_L2_mu10_SiTrk);
   fChain->SetBranchAddress("L2_mu10_tight", &L2_mu10_tight, &b_L2_mu10_tight);
   fChain->SetBranchAddress("L2_mu10i_loose", &L2_mu10i_loose, &b_L2_mu10i_loose);
   fChain->SetBranchAddress("L2_mu13", &L2_mu13, &b_L2_mu13);
   fChain->SetBranchAddress("L2_mu13_MG", &L2_mu13_MG, &b_L2_mu13_MG);
   fChain->SetBranchAddress("L2_mu13_MG_tight", &L2_mu13_MG_tight, &b_L2_mu13_MG_tight);
   fChain->SetBranchAddress("L2_mu13_tight", &L2_mu13_tight, &b_L2_mu13_tight);
   fChain->SetBranchAddress("L2_mu15", &L2_mu15, &b_L2_mu15);
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
   fChain->SetBranchAddress("L2_mu4mu6_Upsimumu", &L2_mu4mu6_Upsimumu, &b_L2_mu4mu6_Upsimumu);
   fChain->SetBranchAddress("L2_mu6", &L2_mu6, &b_L2_mu6);
   fChain->SetBranchAddress("L2_mu6_Bmumu", &L2_mu6_Bmumu, &b_L2_mu6_Bmumu);
   fChain->SetBranchAddress("L2_mu6_BmumuX", &L2_mu6_BmumuX, &b_L2_mu6_BmumuX);
   fChain->SetBranchAddress("L2_mu6_DiMu", &L2_mu6_DiMu, &b_L2_mu6_DiMu);
   fChain->SetBranchAddress("L2_mu6_IDTrkNoCut", &L2_mu6_IDTrkNoCut, &b_L2_mu6_IDTrkNoCut);
   fChain->SetBranchAddress("L2_mu6_Jpsie5e3", &L2_mu6_Jpsie5e3, &b_L2_mu6_Jpsie5e3);
   fChain->SetBranchAddress("L2_mu6_Jpsie5e3_FS", &L2_mu6_Jpsie5e3_FS, &b_L2_mu6_Jpsie5e3_FS);
   fChain->SetBranchAddress("L2_mu6_Jpsimumu", &L2_mu6_Jpsimumu, &b_L2_mu6_Jpsimumu);
   fChain->SetBranchAddress("L2_mu6_MG", &L2_mu6_MG, &b_L2_mu6_MG);
   fChain->SetBranchAddress("L2_mu6_MSonly", &L2_mu6_MSonly, &b_L2_mu6_MSonly);
   fChain->SetBranchAddress("L2_mu6_MSonly_outOfTime", &L2_mu6_MSonly_outOfTime, &b_L2_mu6_MSonly_outOfTime);
   fChain->SetBranchAddress("L2_mu6_NoAlg", &L2_mu6_NoAlg, &b_L2_mu6_NoAlg);
   fChain->SetBranchAddress("L2_mu6_SiTrk", &L2_mu6_SiTrk, &b_L2_mu6_SiTrk);
   fChain->SetBranchAddress("L2_mu6_Trk_Jpsi", &L2_mu6_Trk_Jpsi, &b_L2_mu6_Trk_Jpsi);
   fChain->SetBranchAddress("L2_mu6_Upsimumu_FS", &L2_mu6_Upsimumu_FS, &b_L2_mu6_Upsimumu_FS);
   fChain->SetBranchAddress("L2_mu6_muCombTag", &L2_mu6_muCombTag, &b_L2_mu6_muCombTag);
   fChain->SetBranchAddress("L2_tau125_loose", &L2_tau125_loose, &b_L2_tau125_loose);
   fChain->SetBranchAddress("L2_tau125_medium", &L2_tau125_medium, &b_L2_tau125_medium);
   fChain->SetBranchAddress("L2_tau12_IDTrkNoCut", &L2_tau12_IDTrkNoCut, &b_L2_tau12_IDTrkNoCut);
   fChain->SetBranchAddress("L2_tau12_loose", &L2_tau12_loose, &b_L2_tau12_loose);
   fChain->SetBranchAddress("L2_tau12_loose_2b15", &L2_tau12_loose_2b15, &b_L2_tau12_loose_2b15);
   fChain->SetBranchAddress("L2_tau12_loose_3j30", &L2_tau12_loose_3j30, &b_L2_tau12_loose_3j30);
   fChain->SetBranchAddress("L2_tau12_loose_EFxe12_noMu", &L2_tau12_loose_EFxe12_noMu, &b_L2_tau12_loose_EFxe12_noMu);
   fChain->SetBranchAddress("L2_tau12_loose_IdScan_EFxe12_noMu", &L2_tau12_loose_IdScan_EFxe12_noMu, &b_L2_tau12_loose_IdScan_EFxe12_noMu);
   fChain->SetBranchAddress("L2_tau12_loose_IdScan_xe15_noMu", &L2_tau12_loose_IdScan_xe15_noMu, &b_L2_tau12_loose_IdScan_xe15_noMu);
   fChain->SetBranchAddress("L2_tau12_loose_e10_loose", &L2_tau12_loose_e10_loose, &b_L2_tau12_loose_e10_loose);
   fChain->SetBranchAddress("L2_tau12_loose_e10_medium", &L2_tau12_loose_e10_medium, &b_L2_tau12_loose_e10_medium);
   fChain->SetBranchAddress("L2_tau12_loose_e10_tight", &L2_tau12_loose_e10_tight, &b_L2_tau12_loose_e10_tight);
   fChain->SetBranchAddress("L2_tau12_loose_mu10", &L2_tau12_loose_mu10, &b_L2_tau12_loose_mu10);
   fChain->SetBranchAddress("L2_tau12_loose_xe15_noMu", &L2_tau12_loose_xe15_noMu, &b_L2_tau12_loose_xe15_noMu);
   fChain->SetBranchAddress("L2_tau12_loose_xe20_noMu", &L2_tau12_loose_xe20_noMu, &b_L2_tau12_loose_xe20_noMu);
   fChain->SetBranchAddress("L2_tau16_loose", &L2_tau16_loose, &b_L2_tau16_loose);
   fChain->SetBranchAddress("L2_tau16_loose_2b15", &L2_tau16_loose_2b15, &b_L2_tau16_loose_2b15);
   fChain->SetBranchAddress("L2_tau16_loose_3j30", &L2_tau16_loose_3j30, &b_L2_tau16_loose_3j30);
   fChain->SetBranchAddress("L2_tau16_loose_e10_loose", &L2_tau16_loose_e10_loose, &b_L2_tau16_loose_e10_loose);
   fChain->SetBranchAddress("L2_tau16_loose_e15_loose", &L2_tau16_loose_e15_loose, &b_L2_tau16_loose_e15_loose);
   fChain->SetBranchAddress("L2_tau16_loose_mu10", &L2_tau16_loose_mu10, &b_L2_tau16_loose_mu10);
   fChain->SetBranchAddress("L2_tau16_loose_mu15", &L2_tau16_loose_mu15, &b_L2_tau16_loose_mu15);
   fChain->SetBranchAddress("L2_tau16_loose_xe20_noMu", &L2_tau16_loose_xe20_noMu, &b_L2_tau16_loose_xe20_noMu);
   fChain->SetBranchAddress("L2_tau16_loose_xe25_noMu", &L2_tau16_loose_xe25_noMu, &b_L2_tau16_loose_xe25_noMu);
   fChain->SetBranchAddress("L2_tau16_loose_xe25_tight_noMu", &L2_tau16_loose_xe25_tight_noMu, &b_L2_tau16_loose_xe25_tight_noMu);
   fChain->SetBranchAddress("L2_tau16_loose_xe30_noMu", &L2_tau16_loose_xe30_noMu, &b_L2_tau16_loose_xe30_noMu);
   fChain->SetBranchAddress("L2_tau16_medium", &L2_tau16_medium, &b_L2_tau16_medium);
   fChain->SetBranchAddress("L2_tau16_medium_xe22_noMu", &L2_tau16_medium_xe22_noMu, &b_L2_tau16_medium_xe22_noMu);
   fChain->SetBranchAddress("L2_tau16_medium_xe25_noMu", &L2_tau16_medium_xe25_noMu, &b_L2_tau16_medium_xe25_noMu);
   fChain->SetBranchAddress("L2_tau16_medium_xe25_tight_noMu", &L2_tau16_medium_xe25_tight_noMu, &b_L2_tau16_medium_xe25_tight_noMu);
   fChain->SetBranchAddress("L2_tau20_loose", &L2_tau20_loose, &b_L2_tau20_loose);
   fChain->SetBranchAddress("L2_tau20_loose_xe25_noMu", &L2_tau20_loose_xe25_noMu, &b_L2_tau20_loose_xe25_noMu);
   fChain->SetBranchAddress("L2_tau29_loose", &L2_tau29_loose, &b_L2_tau29_loose);
   fChain->SetBranchAddress("L2_tau38_loose", &L2_tau38_loose, &b_L2_tau38_loose);
   fChain->SetBranchAddress("L2_tau38_medium", &L2_tau38_medium, &b_L2_tau38_medium);
   fChain->SetBranchAddress("L2_tau50_IDTrkNoCut", &L2_tau50_IDTrkNoCut, &b_L2_tau50_IDTrkNoCut);
   fChain->SetBranchAddress("L2_tau50_loose", &L2_tau50_loose, &b_L2_tau50_loose);
   fChain->SetBranchAddress("L2_tau50_loose_IdScan", &L2_tau50_loose_IdScan, &b_L2_tau50_loose_IdScan);
   fChain->SetBranchAddress("L2_tau50_medium", &L2_tau50_medium, &b_L2_tau50_medium);
   fChain->SetBranchAddress("L2_tau5_empty_larcalib", &L2_tau5_empty_larcalib, &b_L2_tau5_empty_larcalib);
   fChain->SetBranchAddress("L2_tau84_loose", &L2_tau84_loose, &b_L2_tau84_loose);
   fChain->SetBranchAddress("L2_tau84_medium", &L2_tau84_medium, &b_L2_tau84_medium);
   fChain->SetBranchAddress("L2_tauNoCut", &L2_tauNoCut, &b_L2_tauNoCut);
   fChain->SetBranchAddress("L2_tauNoCut_IdScan", &L2_tauNoCut_IdScan, &b_L2_tauNoCut_IdScan);
   fChain->SetBranchAddress("L2_tauNoCut_cosmic", &L2_tauNoCut_cosmic, &b_L2_tauNoCut_cosmic);
   fChain->SetBranchAddress("L2_tauNoCut_firstempty", &L2_tauNoCut_firstempty, &b_L2_tauNoCut_firstempty);
   fChain->SetBranchAddress("L2_tauNoCut_hasTrk6_EFxe15_noMu", &L2_tauNoCut_hasTrk6_EFxe15_noMu, &b_L2_tauNoCut_hasTrk6_EFxe15_noMu);
   fChain->SetBranchAddress("L2_tauNoCut_hasTrk6_IdScan_EFxe15_noMu", &L2_tauNoCut_hasTrk6_IdScan_EFxe15_noMu, &b_L2_tauNoCut_hasTrk6_IdScan_EFxe15_noMu);
   fChain->SetBranchAddress("L2_tauNoCut_hasTrk6_IdScan_xe20_noMu", &L2_tauNoCut_hasTrk6_IdScan_xe20_noMu, &b_L2_tauNoCut_hasTrk6_IdScan_xe20_noMu);
   fChain->SetBranchAddress("L2_tauNoCut_hasTrk6_xe20_noMu", &L2_tauNoCut_hasTrk6_xe20_noMu, &b_L2_tauNoCut_hasTrk6_xe20_noMu);
   fChain->SetBranchAddress("L2_tauNoCut_hasTrk9_xe20_noMu", &L2_tauNoCut_hasTrk9_xe20_noMu, &b_L2_tauNoCut_hasTrk9_xe20_noMu);
   fChain->SetBranchAddress("L2_tauNoCut_hasTrk_MV", &L2_tauNoCut_hasTrk_MV, &b_L2_tauNoCut_hasTrk_MV);
   fChain->SetBranchAddress("L2_tauNoCut_hasTrk_e10_tight", &L2_tauNoCut_hasTrk_e10_tight, &b_L2_tauNoCut_hasTrk_e10_tight);
   fChain->SetBranchAddress("L2_tauNoCut_hasTrk_xe20_noMu", &L2_tauNoCut_hasTrk_xe20_noMu, &b_L2_tauNoCut_hasTrk_xe20_noMu);
   fChain->SetBranchAddress("L2_tauNoCut_unpaired_iso", &L2_tauNoCut_unpaired_iso, &b_L2_tauNoCut_unpaired_iso);
   fChain->SetBranchAddress("L2_tauNoCut_unpaired_noniso", &L2_tauNoCut_unpaired_noniso, &b_L2_tauNoCut_unpaired_noniso);
   fChain->SetBranchAddress("L2_xe12", &L2_xe12, &b_L2_xe12);
   fChain->SetBranchAddress("L2_xe12_loose_noMu", &L2_xe12_loose_noMu, &b_L2_xe12_loose_noMu);
   fChain->SetBranchAddress("L2_xe12_medium_noMu", &L2_xe12_medium_noMu, &b_L2_xe12_medium_noMu);
   fChain->SetBranchAddress("L2_xe12_noMu", &L2_xe12_noMu, &b_L2_xe12_noMu);
   fChain->SetBranchAddress("L2_xe15_medium_noMu", &L2_xe15_medium_noMu, &b_L2_xe15_medium_noMu);
   fChain->SetBranchAddress("L2_xe15_noMu", &L2_xe15_noMu, &b_L2_xe15_noMu);
   fChain->SetBranchAddress("L2_xe15_tight_noMu", &L2_xe15_tight_noMu, &b_L2_xe15_tight_noMu);
   fChain->SetBranchAddress("L2_xe15_unbiased_noMu", &L2_xe15_unbiased_noMu, &b_L2_xe15_unbiased_noMu);
   fChain->SetBranchAddress("L2_xe17_tight_noMu", &L2_xe17_tight_noMu, &b_L2_xe17_tight_noMu);
   fChain->SetBranchAddress("L2_xe20_noMu", &L2_xe20_noMu, &b_L2_xe20_noMu);
   fChain->SetBranchAddress("L2_xe22_loose_noMu", &L2_xe22_loose_noMu, &b_L2_xe22_loose_noMu);
   fChain->SetBranchAddress("L2_xe22_tight_noMu", &L2_xe22_tight_noMu, &b_L2_xe22_tight_noMu);
   fChain->SetBranchAddress("L2_xe25_noMu", &L2_xe25_noMu, &b_L2_xe25_noMu);
   fChain->SetBranchAddress("L2_xe27_tight_noMu", &L2_xe27_tight_noMu, &b_L2_xe27_tight_noMu);
   fChain->SetBranchAddress("L2_xe30_allL1", &L2_xe30_allL1, &b_L2_xe30_allL1);
   fChain->SetBranchAddress("L2_xe30_allL1_FEB", &L2_xe30_allL1_FEB, &b_L2_xe30_allL1_FEB);
   fChain->SetBranchAddress("L2_xe30_allL1_allCells", &L2_xe30_allL1_allCells, &b_L2_xe30_allL1_allCells);
   fChain->SetBranchAddress("L2_xe30_noMu", &L2_xe30_noMu, &b_L2_xe30_noMu);
   fChain->SetBranchAddress("L2_xe35_noMu", &L2_xe35_noMu, &b_L2_xe35_noMu);
   fChain->SetBranchAddress("L2_xe40_medium_noMu", &L2_xe40_medium_noMu, &b_L2_xe40_medium_noMu);
   fChain->SetBranchAddress("L2_xe45_noMu", &L2_xe45_noMu, &b_L2_xe45_noMu);
   fChain->SetBranchAddress("L2_xe60_medium_noMu", &L2_xe60_medium_noMu, &b_L2_xe60_medium_noMu);
   fChain->SetBranchAddress("ph_n", &ph_n, &b_ph_n);
   fChain->SetBranchAddress("ph_E", &ph_E, &b_ph_E);
   fChain->SetBranchAddress("ph_Et", &ph_Et, &b_ph_Et);
   fChain->SetBranchAddress("ph_pt", &ph_pt, &b_ph_pt);
   fChain->SetBranchAddress("ph_m", &ph_m, &b_ph_m);
   fChain->SetBranchAddress("ph_eta", &ph_eta, &b_ph_eta);
   fChain->SetBranchAddress("ph_phi", &ph_phi, &b_ph_phi);
   fChain->SetBranchAddress("ph_px", &ph_px, &b_ph_px);
   fChain->SetBranchAddress("ph_py", &ph_py, &b_ph_py);
   fChain->SetBranchAddress("ph_pz", &ph_pz, &b_ph_pz);
   fChain->SetBranchAddress("ph_author", &ph_author, &b_ph_author);
   fChain->SetBranchAddress("ph_isRecovered", &ph_isRecovered, &b_ph_isRecovered);
   fChain->SetBranchAddress("ph_isEM", &ph_isEM, &b_ph_isEM);
   fChain->SetBranchAddress("ph_convFlag", &ph_convFlag, &b_ph_convFlag);
   fChain->SetBranchAddress("ph_isConv", &ph_isConv, &b_ph_isConv);
   fChain->SetBranchAddress("ph_nConv", &ph_nConv, &b_ph_nConv);
   fChain->SetBranchAddress("ph_nSingleTrackConv", &ph_nSingleTrackConv, &b_ph_nSingleTrackConv);
   fChain->SetBranchAddress("ph_nDoubleTrackConv", &ph_nDoubleTrackConv, &b_ph_nDoubleTrackConv);
   fChain->SetBranchAddress("ph_loose", &ph_loose, &b_ph_loose);
   fChain->SetBranchAddress("ph_tight", &ph_tight, &b_ph_tight);
   fChain->SetBranchAddress("ph_tightIso", &ph_tightIso, &b_ph_tightIso);
   fChain->SetBranchAddress("ph_Ethad", &ph_Ethad, &b_ph_Ethad);
   fChain->SetBranchAddress("ph_Ethad1", &ph_Ethad1, &b_ph_Ethad1);
   fChain->SetBranchAddress("ph_E033", &ph_E033, &b_ph_E033);
   fChain->SetBranchAddress("ph_f1", &ph_f1, &b_ph_f1);
   fChain->SetBranchAddress("ph_f1core", &ph_f1core, &b_ph_f1core);
   fChain->SetBranchAddress("ph_Emins1", &ph_Emins1, &b_ph_Emins1);
   fChain->SetBranchAddress("ph_fside", &ph_fside, &b_ph_fside);
   fChain->SetBranchAddress("ph_Emax2", &ph_Emax2, &b_ph_Emax2);
   fChain->SetBranchAddress("ph_ws3", &ph_ws3, &b_ph_ws3);
   fChain->SetBranchAddress("ph_wstot", &ph_wstot, &b_ph_wstot);
   fChain->SetBranchAddress("ph_E132", &ph_E132, &b_ph_E132);
   fChain->SetBranchAddress("ph_E1152", &ph_E1152, &b_ph_E1152);
   fChain->SetBranchAddress("ph_emaxs1", &ph_emaxs1, &b_ph_emaxs1);
   fChain->SetBranchAddress("ph_deltaEs", &ph_deltaEs, &b_ph_deltaEs);
   fChain->SetBranchAddress("ph_E233", &ph_E233, &b_ph_E233);
   fChain->SetBranchAddress("ph_E237", &ph_E237, &b_ph_E237);
   fChain->SetBranchAddress("ph_E277", &ph_E277, &b_ph_E277);
   fChain->SetBranchAddress("ph_weta2", &ph_weta2, &b_ph_weta2);
   fChain->SetBranchAddress("ph_f3", &ph_f3, &b_ph_f3);
   fChain->SetBranchAddress("ph_f3core", &ph_f3core, &b_ph_f3core);
   fChain->SetBranchAddress("ph_rphiallcalo", &ph_rphiallcalo, &b_ph_rphiallcalo);
   fChain->SetBranchAddress("ph_Etcone45", &ph_Etcone45, &b_ph_Etcone45);
   fChain->SetBranchAddress("ph_Etcone20", &ph_Etcone20, &b_ph_Etcone20);
   fChain->SetBranchAddress("ph_Etcone30", &ph_Etcone30, &b_ph_Etcone30);
   fChain->SetBranchAddress("ph_Etcone40", &ph_Etcone40, &b_ph_Etcone40);
   fChain->SetBranchAddress("ph_ptcone30", &ph_ptcone30, &b_ph_ptcone30);
   fChain->SetBranchAddress("ph_convanglematch", &ph_convanglematch, &b_ph_convanglematch);
   fChain->SetBranchAddress("ph_convtrackmatch", &ph_convtrackmatch, &b_ph_convtrackmatch);
   fChain->SetBranchAddress("ph_hasconv", &ph_hasconv, &b_ph_hasconv);
   fChain->SetBranchAddress("ph_convvtxx", &ph_convvtxx, &b_ph_convvtxx);
   fChain->SetBranchAddress("ph_convvtxy", &ph_convvtxy, &b_ph_convvtxy);
   fChain->SetBranchAddress("ph_convvtxz", &ph_convvtxz, &b_ph_convvtxz);
   fChain->SetBranchAddress("ph_Rconv", &ph_Rconv, &b_ph_Rconv);
   fChain->SetBranchAddress("ph_zconv", &ph_zconv, &b_ph_zconv);
   fChain->SetBranchAddress("ph_convvtxchi2", &ph_convvtxchi2, &b_ph_convvtxchi2);
   fChain->SetBranchAddress("ph_pt1conv", &ph_pt1conv, &b_ph_pt1conv);
   fChain->SetBranchAddress("ph_convtrk1nBLHits", &ph_convtrk1nBLHits, &b_ph_convtrk1nBLHits);
   fChain->SetBranchAddress("ph_convtrk1nPixHits", &ph_convtrk1nPixHits, &b_ph_convtrk1nPixHits);
   fChain->SetBranchAddress("ph_convtrk1nSCTHits", &ph_convtrk1nSCTHits, &b_ph_convtrk1nSCTHits);
   fChain->SetBranchAddress("ph_convtrk1nTRTHits", &ph_convtrk1nTRTHits, &b_ph_convtrk1nTRTHits);
   fChain->SetBranchAddress("ph_pt2conv", &ph_pt2conv, &b_ph_pt2conv);
   fChain->SetBranchAddress("ph_convtrk2nBLHits", &ph_convtrk2nBLHits, &b_ph_convtrk2nBLHits);
   fChain->SetBranchAddress("ph_convtrk2nPixHits", &ph_convtrk2nPixHits, &b_ph_convtrk2nPixHits);
   fChain->SetBranchAddress("ph_convtrk2nSCTHits", &ph_convtrk2nSCTHits, &b_ph_convtrk2nSCTHits);
   fChain->SetBranchAddress("ph_convtrk2nTRTHits", &ph_convtrk2nTRTHits, &b_ph_convtrk2nTRTHits);
   fChain->SetBranchAddress("ph_ptconv", &ph_ptconv, &b_ph_ptconv);
   fChain->SetBranchAddress("ph_pzconv", &ph_pzconv, &b_ph_pzconv);
   fChain->SetBranchAddress("ph_reta", &ph_reta, &b_ph_reta);
   fChain->SetBranchAddress("ph_rphi", &ph_rphi, &b_ph_rphi);
   fChain->SetBranchAddress("ph_EtringnoisedR03sig2", &ph_EtringnoisedR03sig2, &b_ph_EtringnoisedR03sig2);
   fChain->SetBranchAddress("ph_EtringnoisedR03sig3", &ph_EtringnoisedR03sig3, &b_ph_EtringnoisedR03sig3);
   fChain->SetBranchAddress("ph_EtringnoisedR03sig4", &ph_EtringnoisedR03sig4, &b_ph_EtringnoisedR03sig4);
   fChain->SetBranchAddress("ph_isolationlikelihoodjets", &ph_isolationlikelihoodjets, &b_ph_isolationlikelihoodjets);
   fChain->SetBranchAddress("ph_isolationlikelihoodhqelectrons", &ph_isolationlikelihoodhqelectrons, &b_ph_isolationlikelihoodhqelectrons);
   fChain->SetBranchAddress("ph_loglikelihood", &ph_loglikelihood, &b_ph_loglikelihood);
   fChain->SetBranchAddress("ph_photonweight", &ph_photonweight, &b_ph_photonweight);
   fChain->SetBranchAddress("ph_photonbgweight", &ph_photonbgweight, &b_ph_photonbgweight);
   fChain->SetBranchAddress("ph_neuralnet", &ph_neuralnet, &b_ph_neuralnet);
   fChain->SetBranchAddress("ph_Hmatrix", &ph_Hmatrix, &b_ph_Hmatrix);
   fChain->SetBranchAddress("ph_Hmatrix5", &ph_Hmatrix5, &b_ph_Hmatrix5);
   fChain->SetBranchAddress("ph_adaboost", &ph_adaboost, &b_ph_adaboost);
   fChain->SetBranchAddress("ph_zvertex", &ph_zvertex, &b_ph_zvertex);
   fChain->SetBranchAddress("ph_errz", &ph_errz, &b_ph_errz);
   fChain->SetBranchAddress("ph_etap", &ph_etap, &b_ph_etap);
   fChain->SetBranchAddress("ph_depth", &ph_depth, &b_ph_depth);
   fChain->SetBranchAddress("ph_cl_E", &ph_cl_E, &b_ph_cl_E);
   fChain->SetBranchAddress("ph_cl_pt", &ph_cl_pt, &b_ph_cl_pt);
   fChain->SetBranchAddress("ph_cl_eta", &ph_cl_eta, &b_ph_cl_eta);
   fChain->SetBranchAddress("ph_cl_phi", &ph_cl_phi, &b_ph_cl_phi);
   fChain->SetBranchAddress("ph_Es0", &ph_Es0, &b_ph_Es0);
   fChain->SetBranchAddress("ph_etas0", &ph_etas0, &b_ph_etas0);
   fChain->SetBranchAddress("ph_phis0", &ph_phis0, &b_ph_phis0);
   fChain->SetBranchAddress("ph_Es1", &ph_Es1, &b_ph_Es1);
   fChain->SetBranchAddress("ph_etas1", &ph_etas1, &b_ph_etas1);
   fChain->SetBranchAddress("ph_phis1", &ph_phis1, &b_ph_phis1);
   fChain->SetBranchAddress("ph_Es2", &ph_Es2, &b_ph_Es2);
   fChain->SetBranchAddress("ph_etas2", &ph_etas2, &b_ph_etas2);
   fChain->SetBranchAddress("ph_phis2", &ph_phis2, &b_ph_phis2);
   fChain->SetBranchAddress("ph_Es3", &ph_Es3, &b_ph_Es3);
   fChain->SetBranchAddress("ph_etas3", &ph_etas3, &b_ph_etas3);
   fChain->SetBranchAddress("ph_phis3", &ph_phis3, &b_ph_phis3);
   fChain->SetBranchAddress("ph_rawcl_Es0", &ph_rawcl_Es0, &b_ph_rawcl_Es0);
   fChain->SetBranchAddress("ph_rawcl_etas0", &ph_rawcl_etas0, &b_ph_rawcl_etas0);
   fChain->SetBranchAddress("ph_rawcl_phis0", &ph_rawcl_phis0, &b_ph_rawcl_phis0);
   fChain->SetBranchAddress("ph_rawcl_Es1", &ph_rawcl_Es1, &b_ph_rawcl_Es1);
   fChain->SetBranchAddress("ph_rawcl_etas1", &ph_rawcl_etas1, &b_ph_rawcl_etas1);
   fChain->SetBranchAddress("ph_rawcl_phis1", &ph_rawcl_phis1, &b_ph_rawcl_phis1);
   fChain->SetBranchAddress("ph_rawcl_Es2", &ph_rawcl_Es2, &b_ph_rawcl_Es2);
   fChain->SetBranchAddress("ph_rawcl_etas2", &ph_rawcl_etas2, &b_ph_rawcl_etas2);
   fChain->SetBranchAddress("ph_rawcl_phis2", &ph_rawcl_phis2, &b_ph_rawcl_phis2);
   fChain->SetBranchAddress("ph_rawcl_Es3", &ph_rawcl_Es3, &b_ph_rawcl_Es3);
   fChain->SetBranchAddress("ph_rawcl_etas3", &ph_rawcl_etas3, &b_ph_rawcl_etas3);
   fChain->SetBranchAddress("ph_rawcl_phis3", &ph_rawcl_phis3, &b_ph_rawcl_phis3);
   fChain->SetBranchAddress("ph_rawcl_E", &ph_rawcl_E, &b_ph_rawcl_E);
   fChain->SetBranchAddress("ph_rawcl_pt", &ph_rawcl_pt, &b_ph_rawcl_pt);
   fChain->SetBranchAddress("ph_rawcl_eta", &ph_rawcl_eta, &b_ph_rawcl_eta);
   fChain->SetBranchAddress("ph_rawcl_phi", &ph_rawcl_phi, &b_ph_rawcl_phi);
   fChain->SetBranchAddress("ph_deltaEmax2", &ph_deltaEmax2, &b_ph_deltaEmax2);
   fChain->SetBranchAddress("ph_isIso", &ph_isIso, &b_ph_isIso);
   fChain->SetBranchAddress("ph_topoEtcone20", &ph_topoEtcone20, &b_ph_topoEtcone20);
   fChain->SetBranchAddress("ph_topoEtcone40", &ph_topoEtcone40, &b_ph_topoEtcone40);
   fChain->SetBranchAddress("ph_topoEtcone60", &ph_topoEtcone60, &b_ph_topoEtcone60);
   fChain->SetBranchAddress("ph_jet_dr", &ph_jet_dr, &b_ph_jet_dr);
   fChain->SetBranchAddress("ph_jet_E", &ph_jet_E, &b_ph_jet_E);
   fChain->SetBranchAddress("ph_jet_pt", &ph_jet_pt, &b_ph_jet_pt);
   fChain->SetBranchAddress("ph_jet_m", &ph_jet_m, &b_ph_jet_m);
   fChain->SetBranchAddress("ph_jet_eta", &ph_jet_eta, &b_ph_jet_eta);
   fChain->SetBranchAddress("ph_jet_phi", &ph_jet_phi, &b_ph_jet_phi);
   fChain->SetBranchAddress("ph_jet_matched", &ph_jet_matched, &b_ph_jet_matched);
   fChain->SetBranchAddress("ph_trackIsol", &ph_trackIsol, &b_ph_trackIsol);
   fChain->SetBranchAddress("ph_convIP", &ph_convIP, &b_ph_convIP);
   fChain->SetBranchAddress("ph_convIPRev", &ph_convIPRev, &b_ph_convIPRev);
   fChain->SetBranchAddress("ph_ptIsolationCone", &ph_ptIsolationCone, &b_ph_ptIsolationCone);
   fChain->SetBranchAddress("ph_ptIsolationConePhAngle", &ph_ptIsolationConePhAngle, &b_ph_ptIsolationConePhAngle);
   fChain->SetBranchAddress("ph_Etcone40_pt_corrected", &ph_Etcone40_pt_corrected, &b_ph_Etcone40_pt_corrected);
   fChain->SetBranchAddress("ph_Etcone40_ED_corrected", &ph_Etcone40_ED_corrected, &b_ph_Etcone40_ED_corrected);
   fChain->SetBranchAddress("ph_Etcone40_corrected", &ph_Etcone40_corrected, &b_ph_Etcone40_corrected);
   fChain->SetBranchAddress("ph_topodr", &ph_topodr, &b_ph_topodr);
   fChain->SetBranchAddress("ph_topopt", &ph_topopt, &b_ph_topopt);
   fChain->SetBranchAddress("ph_topoeta", &ph_topoeta, &b_ph_topoeta);
   fChain->SetBranchAddress("ph_topophi", &ph_topophi, &b_ph_topophi);
   fChain->SetBranchAddress("ph_topomatched", &ph_topomatched, &b_ph_topomatched);
   fChain->SetBranchAddress("ph_topoEMdr", &ph_topoEMdr, &b_ph_topoEMdr);
   fChain->SetBranchAddress("ph_topoEMpt", &ph_topoEMpt, &b_ph_topoEMpt);
   fChain->SetBranchAddress("ph_topoEMeta", &ph_topoEMeta, &b_ph_topoEMeta);
   fChain->SetBranchAddress("ph_topoEMphi", &ph_topoEMphi, &b_ph_topoEMphi);
   fChain->SetBranchAddress("ph_topoEMmatched", &ph_topoEMmatched, &b_ph_topoEMmatched);
   fChain->SetBranchAddress("ph_EF_dr", &ph_EF_dr, &b_ph_EF_dr);
   fChain->SetBranchAddress("ph_EF_index", &ph_EF_index, &b_ph_EF_index);
   fChain->SetBranchAddress("ph_L2_dr", &ph_L2_dr, &b_ph_L2_dr);
   fChain->SetBranchAddress("ph_L2_index", &ph_L2_index, &b_ph_L2_index);
   fChain->SetBranchAddress("ph_L1_dr", &ph_L1_dr, &b_ph_L1_dr);
   fChain->SetBranchAddress("ph_L1_index", &ph_L1_index, &b_ph_L1_index);
   fChain->SetBranchAddress("ph_EF_E", &ph_EF_E, &b_ph_EF_E);
   fChain->SetBranchAddress("ph_EF_Et", &ph_EF_Et, &b_ph_EF_Et);
   fChain->SetBranchAddress("ph_EF_pt", &ph_EF_pt, &b_ph_EF_pt);
   fChain->SetBranchAddress("ph_EF_eta", &ph_EF_eta, &b_ph_EF_eta);
   fChain->SetBranchAddress("ph_EF_phi", &ph_EF_phi, &b_ph_EF_phi);
   fChain->SetBranchAddress("ph_EF_Ethad", &ph_EF_Ethad, &b_ph_EF_Ethad);
   fChain->SetBranchAddress("ph_EF_Ethad1", &ph_EF_Ethad1, &b_ph_EF_Ethad1);
   fChain->SetBranchAddress("ph_EF_f1", &ph_EF_f1, &b_ph_EF_f1);
   fChain->SetBranchAddress("ph_EF_Emins1", &ph_EF_Emins1, &b_ph_EF_Emins1);
   fChain->SetBranchAddress("ph_EF_fside", &ph_EF_fside, &b_ph_EF_fside);
   fChain->SetBranchAddress("ph_EF_Emax2", &ph_EF_Emax2, &b_ph_EF_Emax2);
   fChain->SetBranchAddress("ph_EF_ws3", &ph_EF_ws3, &b_ph_EF_ws3);
   fChain->SetBranchAddress("ph_EF_wstot", &ph_EF_wstot, &b_ph_EF_wstot);
   fChain->SetBranchAddress("ph_EF_E233", &ph_EF_E233, &b_ph_EF_E233);
   fChain->SetBranchAddress("ph_EF_E237", &ph_EF_E237, &b_ph_EF_E237);
   fChain->SetBranchAddress("ph_EF_E277", &ph_EF_E277, &b_ph_EF_E277);
   fChain->SetBranchAddress("ph_EF_weta2", &ph_EF_weta2, &b_ph_EF_weta2);
   fChain->SetBranchAddress("ph_EF_rphiallcalo", &ph_EF_rphiallcalo, &b_ph_EF_rphiallcalo);
   fChain->SetBranchAddress("ph_EF_Etcone45", &ph_EF_Etcone45, &b_ph_EF_Etcone45);
   fChain->SetBranchAddress("ph_EF_Etcone20", &ph_EF_Etcone20, &b_ph_EF_Etcone20);
   fChain->SetBranchAddress("ph_EF_Etcone30", &ph_EF_Etcone30, &b_ph_EF_Etcone30);
   fChain->SetBranchAddress("ph_EF_Etcone40", &ph_EF_Etcone40, &b_ph_EF_Etcone40);
   fChain->SetBranchAddress("ph_EF_zvertex", &ph_EF_zvertex, &b_ph_EF_zvertex);
   fChain->SetBranchAddress("ph_EF_errz", &ph_EF_errz, &b_ph_EF_errz);
   fChain->SetBranchAddress("ph_EF_matched", &ph_EF_matched, &b_ph_EF_matched);
   fChain->SetBranchAddress("ph_L2_E", &ph_L2_E, &b_ph_L2_E);
   fChain->SetBranchAddress("ph_L2_Et", &ph_L2_Et, &b_ph_L2_Et);
   fChain->SetBranchAddress("ph_L2_pt", &ph_L2_pt, &b_ph_L2_pt);
   fChain->SetBranchAddress("ph_L2_eta", &ph_L2_eta, &b_ph_L2_eta);
   fChain->SetBranchAddress("ph_L2_phi", &ph_L2_phi, &b_ph_L2_phi);
   fChain->SetBranchAddress("ph_L2_Ethad1", &ph_L2_Ethad1, &b_ph_L2_Ethad1);
   fChain->SetBranchAddress("ph_L2_reta", &ph_L2_reta, &b_ph_L2_reta);
   fChain->SetBranchAddress("ph_L2_Eratio", &ph_L2_Eratio, &b_ph_L2_Eratio);
   fChain->SetBranchAddress("ph_L2_E237", &ph_L2_E237, &b_ph_L2_E237);
   fChain->SetBranchAddress("ph_L2_E277", &ph_L2_E277, &b_ph_L2_E277);
   fChain->SetBranchAddress("ph_L2_fside", &ph_L2_fside, &b_ph_L2_fside);
   fChain->SetBranchAddress("ph_L2_weta2", &ph_L2_weta2, &b_ph_L2_weta2);
   fChain->SetBranchAddress("ph_L2_Emaxs1", &ph_L2_Emaxs1, &b_ph_L2_Emaxs1);
   fChain->SetBranchAddress("ph_L2_Emax2", &ph_L2_Emax2, &b_ph_L2_Emax2);
   fChain->SetBranchAddress("ph_L2_matched", &ph_L2_matched, &b_ph_L2_matched);
   fChain->SetBranchAddress("ph_L1_eta", &ph_L1_eta, &b_ph_L1_eta);
   fChain->SetBranchAddress("ph_L1_phi", &ph_L1_phi, &b_ph_L1_phi);
   fChain->SetBranchAddress("ph_L1_EMisol", &ph_L1_EMisol, &b_ph_L1_EMisol);
   fChain->SetBranchAddress("ph_L1_hadisol", &ph_L1_hadisol, &b_ph_L1_hadisol);
   fChain->SetBranchAddress("ph_L1_hadcore", &ph_L1_hadcore, &b_ph_L1_hadcore);
   fChain->SetBranchAddress("ph_L1_pt", &ph_L1_pt, &b_ph_L1_pt);
   fChain->SetBranchAddress("ph_L1_Et", &ph_L1_Et, &b_ph_L1_Et);
   fChain->SetBranchAddress("ph_L1_matched", &ph_L1_matched, &b_ph_L1_matched);
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
   fChain->SetBranchAddress("mu_muid_loose", &mu_muid_loose, &b_mu_muid_loose);
   fChain->SetBranchAddress("mu_muid_medium", &mu_muid_medium, &b_mu_muid_medium);
   fChain->SetBranchAddress("mu_muid_tight", &mu_muid_tight, &b_mu_muid_tight);
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
   fChain->SetBranchAddress("mu_staco_loose", &mu_staco_loose, &b_mu_staco_loose);
   fChain->SetBranchAddress("mu_staco_medium", &mu_staco_medium, &b_mu_staco_medium);
   fChain->SetBranchAddress("mu_staco_tight", &mu_staco_tight, &b_mu_staco_tight);
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
   fChain->SetBranchAddress("tau_n", &tau_n, &b_tau_n);
   fChain->SetBranchAddress("tau_Et", &tau_Et, &b_tau_Et);
   fChain->SetBranchAddress("tau_pt", &tau_pt, &b_tau_pt);
   fChain->SetBranchAddress("tau_m", &tau_m, &b_tau_m);
   fChain->SetBranchAddress("tau_eta", &tau_eta, &b_tau_eta);
   fChain->SetBranchAddress("tau_phi", &tau_phi, &b_tau_phi);
   fChain->SetBranchAddress("tau_charge", &tau_charge, &b_tau_charge);
   fChain->SetBranchAddress("tau_BDTEleScore", &tau_BDTEleScore, &b_tau_BDTEleScore);
   fChain->SetBranchAddress("tau_BDTJetScore", &tau_BDTJetScore, &b_tau_BDTJetScore);
   fChain->SetBranchAddress("tau_discCut", &tau_discCut, &b_tau_discCut);
   fChain->SetBranchAddress("tau_discCutTMVA", &tau_discCutTMVA, &b_tau_discCutTMVA);
   fChain->SetBranchAddress("tau_discLL", &tau_discLL, &b_tau_discLL);
   fChain->SetBranchAddress("tau_discNN", &tau_discNN, &b_tau_discNN);
   fChain->SetBranchAddress("tau_efficLL", &tau_efficLL, &b_tau_efficLL);
   fChain->SetBranchAddress("tau_efficNN", &tau_efficNN, &b_tau_efficNN);
   fChain->SetBranchAddress("tau_likelihood", &tau_likelihood, &b_tau_likelihood);
   fChain->SetBranchAddress("tau_tauJetNeuralNetwork", &tau_tauJetNeuralNetwork, &b_tau_tauJetNeuralNetwork);
   fChain->SetBranchAddress("tau_tauENeuralNetwork", &tau_tauENeuralNetwork, &b_tau_tauENeuralNetwork);
   fChain->SetBranchAddress("tau_tauElTauLikelihood", &tau_tauElTauLikelihood, &b_tau_tauElTauLikelihood);
   fChain->SetBranchAddress("tau_electronVetoLoose", &tau_electronVetoLoose, &b_tau_electronVetoLoose);
   fChain->SetBranchAddress("tau_electronVetoMedium", &tau_electronVetoMedium, &b_tau_electronVetoMedium);
   fChain->SetBranchAddress("tau_electronVetoTight", &tau_electronVetoTight, &b_tau_electronVetoTight);
   fChain->SetBranchAddress("tau_muonVeto", &tau_muonVeto, &b_tau_muonVeto);
   fChain->SetBranchAddress("tau_tauCutLoose", &tau_tauCutLoose, &b_tau_tauCutLoose);
   fChain->SetBranchAddress("tau_tauCutMedium", &tau_tauCutMedium, &b_tau_tauCutMedium);
   fChain->SetBranchAddress("tau_tauCutTight", &tau_tauCutTight, &b_tau_tauCutTight);
   fChain->SetBranchAddress("tau_tauCutSafeLoose", &tau_tauCutSafeLoose, &b_tau_tauCutSafeLoose);
   fChain->SetBranchAddress("tau_tauCutSafeMedium", &tau_tauCutSafeMedium, &b_tau_tauCutSafeMedium);
   fChain->SetBranchAddress("tau_tauCutSafeTight", &tau_tauCutSafeTight, &b_tau_tauCutSafeTight);
   fChain->SetBranchAddress("tau_tauCutSafeCaloLoose", &tau_tauCutSafeCaloLoose, &b_tau_tauCutSafeCaloLoose);
   fChain->SetBranchAddress("tau_tauCutSafeCaloMedium", &tau_tauCutSafeCaloMedium, &b_tau_tauCutSafeCaloMedium);
   fChain->SetBranchAddress("tau_tauCutSafeCaloTight", &tau_tauCutSafeCaloTight, &b_tau_tauCutSafeCaloTight);
   fChain->SetBranchAddress("tau_tauLlhLoose", &tau_tauLlhLoose, &b_tau_tauLlhLoose);
   fChain->SetBranchAddress("tau_tauLlhMedium", &tau_tauLlhMedium, &b_tau_tauLlhMedium);
   fChain->SetBranchAddress("tau_tauLlhTight", &tau_tauLlhTight, &b_tau_tauLlhTight);
   fChain->SetBranchAddress("tau_author", &tau_author, &b_tau_author);
   fChain->SetBranchAddress("tau_ROIword", &tau_ROIword, &b_tau_ROIword);
   fChain->SetBranchAddress("tau_nProng", &tau_nProng, &b_tau_nProng);
   fChain->SetBranchAddress("tau_numTrack", &tau_numTrack, &b_tau_numTrack);
   fChain->SetBranchAddress("tau_etOverPtLeadTrk", &tau_etOverPtLeadTrk, &b_tau_etOverPtLeadTrk);
   fChain->SetBranchAddress("tau_ipZ0SinThetaSigLeadTrk", &tau_ipZ0SinThetaSigLeadTrk, &b_tau_ipZ0SinThetaSigLeadTrk);
   fChain->SetBranchAddress("tau_leadTrkPt", &tau_leadTrkPt, &b_tau_leadTrkPt);
   fChain->SetBranchAddress("tau_nLooseTrk", &tau_nLooseTrk, &b_tau_nLooseTrk);
   fChain->SetBranchAddress("tau_nLooseConvTrk", &tau_nLooseConvTrk, &b_tau_nLooseConvTrk);
   fChain->SetBranchAddress("tau_nProngLoose", &tau_nProngLoose, &b_tau_nProngLoose);
   fChain->SetBranchAddress("tau_ipSigLeadTrk", &tau_ipSigLeadTrk, &b_tau_ipSigLeadTrk);
   fChain->SetBranchAddress("tau_ipSigLeadLooseTrk", &tau_ipSigLeadLooseTrk, &b_tau_ipSigLeadLooseTrk);
   fChain->SetBranchAddress("tau_etOverPtLeadLooseTrk", &tau_etOverPtLeadLooseTrk, &b_tau_etOverPtLeadLooseTrk);
   fChain->SetBranchAddress("tau_leadLooseTrkPt", &tau_leadLooseTrkPt, &b_tau_leadLooseTrkPt);
   fChain->SetBranchAddress("tau_chrgLooseTrk", &tau_chrgLooseTrk, &b_tau_chrgLooseTrk);
   fChain->SetBranchAddress("tau_massTrkSys", &tau_massTrkSys, &b_tau_massTrkSys);
   fChain->SetBranchAddress("tau_trkWidth2", &tau_trkWidth2, &b_tau_trkWidth2);
   fChain->SetBranchAddress("tau_trFlightPathSig", &tau_trFlightPathSig, &b_tau_trFlightPathSig);
   fChain->SetBranchAddress("tau_etEflow", &tau_etEflow, &b_tau_etEflow);
   fChain->SetBranchAddress("tau_mEflow", &tau_mEflow, &b_tau_mEflow);
   fChain->SetBranchAddress("tau_nPi0", &tau_nPi0, &b_tau_nPi0);
   fChain->SetBranchAddress("tau_ele_E237E277", &tau_ele_E237E277, &b_tau_ele_E237E277);
   fChain->SetBranchAddress("tau_ele_PresamplerFraction", &tau_ele_PresamplerFraction, &b_tau_ele_PresamplerFraction);
   fChain->SetBranchAddress("tau_ele_ECALFirstFraction", &tau_ele_ECALFirstFraction, &b_tau_ele_ECALFirstFraction);
   fChain->SetBranchAddress("tau_seedCalo_EMRadius", &tau_seedCalo_EMRadius, &b_tau_seedCalo_EMRadius);
   fChain->SetBranchAddress("tau_seedCalo_hadRadius", &tau_seedCalo_hadRadius, &b_tau_seedCalo_hadRadius);
   fChain->SetBranchAddress("tau_seedCalo_etEMAtEMScale", &tau_seedCalo_etEMAtEMScale, &b_tau_seedCalo_etEMAtEMScale);
   fChain->SetBranchAddress("tau_seedCalo_etHadAtEMScale", &tau_seedCalo_etHadAtEMScale, &b_tau_seedCalo_etHadAtEMScale);
   fChain->SetBranchAddress("tau_seedCalo_isolFrac", &tau_seedCalo_isolFrac, &b_tau_seedCalo_isolFrac);
   fChain->SetBranchAddress("tau_seedCalo_centFrac", &tau_seedCalo_centFrac, &b_tau_seedCalo_centFrac);
   fChain->SetBranchAddress("tau_seedCalo_stripWidth2", &tau_seedCalo_stripWidth2, &b_tau_seedCalo_stripWidth2);
   fChain->SetBranchAddress("tau_seedCalo_nStrip", &tau_seedCalo_nStrip, &b_tau_seedCalo_nStrip);
   fChain->SetBranchAddress("tau_seedCalo_etEMCalib", &tau_seedCalo_etEMCalib, &b_tau_seedCalo_etEMCalib);
   fChain->SetBranchAddress("tau_seedCalo_etHadCalib", &tau_seedCalo_etHadCalib, &b_tau_seedCalo_etHadCalib);
   fChain->SetBranchAddress("tau_seedCalo_eta", &tau_seedCalo_eta, &b_tau_seedCalo_eta);
   fChain->SetBranchAddress("tau_seedCalo_phi", &tau_seedCalo_phi, &b_tau_seedCalo_phi);
   fChain->SetBranchAddress("tau_seedCalo_nIsolLooseTrk", &tau_seedCalo_nIsolLooseTrk, &b_tau_seedCalo_nIsolLooseTrk);
   fChain->SetBranchAddress("tau_seedCalo_trkAvgDist", &tau_seedCalo_trkAvgDist, &b_tau_seedCalo_trkAvgDist);
   fChain->SetBranchAddress("tau_seedCalo_trkRmsDist", &tau_seedCalo_trkRmsDist, &b_tau_seedCalo_trkRmsDist);
   fChain->SetBranchAddress("tau_seedTrk_EMRadius", &tau_seedTrk_EMRadius, &b_tau_seedTrk_EMRadius);
   fChain->SetBranchAddress("tau_seedTrk_isolFrac", &tau_seedTrk_isolFrac, &b_tau_seedTrk_isolFrac);
   fChain->SetBranchAddress("tau_seedTrk_etChrgHadOverSumTrkPt", &tau_seedTrk_etChrgHadOverSumTrkPt, &b_tau_seedTrk_etChrgHadOverSumTrkPt);
   fChain->SetBranchAddress("tau_seedTrk_isolFracWide", &tau_seedTrk_isolFracWide, &b_tau_seedTrk_isolFracWide);
   fChain->SetBranchAddress("tau_seedTrk_etHadAtEMScale", &tau_seedTrk_etHadAtEMScale, &b_tau_seedTrk_etHadAtEMScale);
   fChain->SetBranchAddress("tau_seedTrk_etEMAtEMScale", &tau_seedTrk_etEMAtEMScale, &b_tau_seedTrk_etEMAtEMScale);
   fChain->SetBranchAddress("tau_seedTrk_etEMCL", &tau_seedTrk_etEMCL, &b_tau_seedTrk_etEMCL);
   fChain->SetBranchAddress("tau_seedTrk_etChrgEM", &tau_seedTrk_etChrgEM, &b_tau_seedTrk_etChrgEM);
   fChain->SetBranchAddress("tau_seedTrk_etNeuEM", &tau_seedTrk_etNeuEM, &b_tau_seedTrk_etNeuEM);
   fChain->SetBranchAddress("tau_seedTrk_etResNeuEM", &tau_seedTrk_etResNeuEM, &b_tau_seedTrk_etResNeuEM);
   fChain->SetBranchAddress("tau_seedTrk_hadLeakEt", &tau_seedTrk_hadLeakEt, &b_tau_seedTrk_hadLeakEt);
   fChain->SetBranchAddress("tau_seedTrk_sumEMCellEtOverLeadTrkPt", &tau_seedTrk_sumEMCellEtOverLeadTrkPt, &b_tau_seedTrk_sumEMCellEtOverLeadTrkPt);
   fChain->SetBranchAddress("tau_seedTrk_secMaxStripEt", &tau_seedTrk_secMaxStripEt, &b_tau_seedTrk_secMaxStripEt);
   fChain->SetBranchAddress("tau_seedTrk_stripWidth2", &tau_seedTrk_stripWidth2, &b_tau_seedTrk_stripWidth2);
   fChain->SetBranchAddress("tau_seedTrk_nStrip", &tau_seedTrk_nStrip, &b_tau_seedTrk_nStrip);
   fChain->SetBranchAddress("tau_seedTrk_etChrgHad", &tau_seedTrk_etChrgHad, &b_tau_seedTrk_etChrgHad);
   fChain->SetBranchAddress("tau_seedTrk_nOtherCoreTrk", &tau_seedTrk_nOtherCoreTrk, &b_tau_seedTrk_nOtherCoreTrk);
   fChain->SetBranchAddress("tau_seedTrk_nIsolTrk", &tau_seedTrk_nIsolTrk, &b_tau_seedTrk_nIsolTrk);
   fChain->SetBranchAddress("tau_seedTrk_etIsolEM", &tau_seedTrk_etIsolEM, &b_tau_seedTrk_etIsolEM);
   fChain->SetBranchAddress("tau_seedTrk_etIsolHad", &tau_seedTrk_etIsolHad, &b_tau_seedTrk_etIsolHad);
   fChain->SetBranchAddress("tau_calcVars_sumTrkPt", &tau_calcVars_sumTrkPt, &b_tau_calcVars_sumTrkPt);
   fChain->SetBranchAddress("tau_calcVars_numTopoClusters", &tau_calcVars_numTopoClusters, &b_tau_calcVars_numTopoClusters);
   fChain->SetBranchAddress("tau_calcVars_numEffTopoClusters", &tau_calcVars_numEffTopoClusters, &b_tau_calcVars_numEffTopoClusters);
   fChain->SetBranchAddress("tau_calcVars_topoInvMass", &tau_calcVars_topoInvMass, &b_tau_calcVars_topoInvMass);
   fChain->SetBranchAddress("tau_calcVars_effTopoInvMass", &tau_calcVars_effTopoInvMass, &b_tau_calcVars_effTopoInvMass);
   fChain->SetBranchAddress("tau_calcVars_topoMeanDeltaR", &tau_calcVars_topoMeanDeltaR, &b_tau_calcVars_topoMeanDeltaR);
   fChain->SetBranchAddress("tau_calcVars_effTopoMeanDeltaR", &tau_calcVars_effTopoMeanDeltaR, &b_tau_calcVars_effTopoMeanDeltaR);
   fChain->SetBranchAddress("tau_calcVars_etHadSumPtTracks", &tau_calcVars_etHadSumPtTracks, &b_tau_calcVars_etHadSumPtTracks);
   fChain->SetBranchAddress("tau_calcVars_etEMSumPtTracks", &tau_calcVars_etEMSumPtTracks, &b_tau_calcVars_etEMSumPtTracks);
   fChain->SetBranchAddress("tau_track_n", &tau_track_n, &b_tau_track_n);
   fChain->SetBranchAddress("tau_EF_dr", &tau_EF_dr, &b_tau_EF_dr);
   fChain->SetBranchAddress("tau_EF_E", &tau_EF_E, &b_tau_EF_E);
   fChain->SetBranchAddress("tau_EF_Et", &tau_EF_Et, &b_tau_EF_Et);
   fChain->SetBranchAddress("tau_EF_pt", &tau_EF_pt, &b_tau_EF_pt);
   fChain->SetBranchAddress("tau_EF_eta", &tau_EF_eta, &b_tau_EF_eta);
   fChain->SetBranchAddress("tau_EF_phi", &tau_EF_phi, &b_tau_EF_phi);
   fChain->SetBranchAddress("tau_EF_matched", &tau_EF_matched, &b_tau_EF_matched);
   fChain->SetBranchAddress("tau_L2_dr", &tau_L2_dr, &b_tau_L2_dr);
   fChain->SetBranchAddress("tau_L2_E", &tau_L2_E, &b_tau_L2_E);
   fChain->SetBranchAddress("tau_L2_Et", &tau_L2_Et, &b_tau_L2_Et);
   fChain->SetBranchAddress("tau_L2_pt", &tau_L2_pt, &b_tau_L2_pt);
   fChain->SetBranchAddress("tau_L2_eta", &tau_L2_eta, &b_tau_L2_eta);
   fChain->SetBranchAddress("tau_L2_phi", &tau_L2_phi, &b_tau_L2_phi);
   fChain->SetBranchAddress("tau_L2_matched", &tau_L2_matched, &b_tau_L2_matched);
   fChain->SetBranchAddress("tau_L1_dr", &tau_L1_dr, &b_tau_L1_dr);
   fChain->SetBranchAddress("tau_L1_Et", &tau_L1_Et, &b_tau_L1_Et);
   fChain->SetBranchAddress("tau_L1_pt", &tau_L1_pt, &b_tau_L1_pt);
   fChain->SetBranchAddress("tau_L1_eta", &tau_L1_eta, &b_tau_L1_eta);
   fChain->SetBranchAddress("tau_L1_phi", &tau_L1_phi, &b_tau_L1_phi);
   fChain->SetBranchAddress("tau_L1_matched", &tau_L1_matched, &b_tau_L1_matched);
   fChain->SetBranchAddress("jet_antikt4h1topo_n", &jet_antikt4h1topo_n, &b_jet_antikt4h1topo_n);
   fChain->SetBranchAddress("jet_antikt4h1topo_E", &jet_antikt4h1topo_E, &b_jet_antikt4h1topo_E);
   fChain->SetBranchAddress("jet_antikt4h1topo_pt", &jet_antikt4h1topo_pt, &b_jet_antikt4h1topo_pt);
   fChain->SetBranchAddress("jet_antikt4h1topo_m", &jet_antikt4h1topo_m, &b_jet_antikt4h1topo_m);
   fChain->SetBranchAddress("jet_antikt4h1topo_eta", &jet_antikt4h1topo_eta, &b_jet_antikt4h1topo_eta);
   fChain->SetBranchAddress("jet_antikt4h1topo_phi", &jet_antikt4h1topo_phi, &b_jet_antikt4h1topo_phi);
   fChain->SetBranchAddress("jet_antikt4h1topo_EtaPhys", &jet_antikt4h1topo_EtaPhys, &b_jet_antikt4h1topo_EtaPhys);
   fChain->SetBranchAddress("jet_antikt4h1topo_PhiPhys", &jet_antikt4h1topo_PhiPhys, &b_jet_antikt4h1topo_PhiPhys);
   fChain->SetBranchAddress("jet_antikt4h1topo_MPhys", &jet_antikt4h1topo_MPhys, &b_jet_antikt4h1topo_MPhys);
   fChain->SetBranchAddress("jet_antikt4h1topo_WIDTH", &jet_antikt4h1topo_WIDTH, &b_jet_antikt4h1topo_WIDTH);
   fChain->SetBranchAddress("jet_antikt4h1topo_n90", &jet_antikt4h1topo_n90, &b_jet_antikt4h1topo_n90);
   fChain->SetBranchAddress("jet_antikt4h1topo_n90constituents", &jet_antikt4h1topo_n90constituents, &b_jet_antikt4h1topo_n90constituents);
   fChain->SetBranchAddress("jet_antikt4h1topo_fracSamplingMax", &jet_antikt4h1topo_fracSamplingMax, &b_jet_antikt4h1topo_fracSamplingMax);
   fChain->SetBranchAddress("jet_antikt4h1topo_SamplingMax", &jet_antikt4h1topo_SamplingMax, &b_jet_antikt4h1topo_SamplingMax);
   fChain->SetBranchAddress("jet_antikt4h1topo_BCH_CORR_CELL", &jet_antikt4h1topo_BCH_CORR_CELL, &b_jet_antikt4h1topo_BCH_CORR_CELL);
   fChain->SetBranchAddress("jet_antikt4h1topo_BCH_CORR_DOTX", &jet_antikt4h1topo_BCH_CORR_DOTX, &b_jet_antikt4h1topo_BCH_CORR_DOTX);
   fChain->SetBranchAddress("jet_antikt4h1topo_BCH_CORR_JET", &jet_antikt4h1topo_BCH_CORR_JET, &b_jet_antikt4h1topo_BCH_CORR_JET);
   fChain->SetBranchAddress("jet_antikt4h1topo_BCH_CORR_JET_FORCELL", &jet_antikt4h1topo_BCH_CORR_JET_FORCELL, &b_jet_antikt4h1topo_BCH_CORR_JET_FORCELL);
   fChain->SetBranchAddress("jet_antikt4h1topo_ENG_BAD_CELLS", &jet_antikt4h1topo_ENG_BAD_CELLS, &b_jet_antikt4h1topo_ENG_BAD_CELLS);
   fChain->SetBranchAddress("jet_antikt4h1topo_N_BAD_CELLS", &jet_antikt4h1topo_N_BAD_CELLS, &b_jet_antikt4h1topo_N_BAD_CELLS);
   fChain->SetBranchAddress("jet_antikt4h1topo_N_BAD_CELLS_CORR", &jet_antikt4h1topo_N_BAD_CELLS_CORR, &b_jet_antikt4h1topo_N_BAD_CELLS_CORR);
   fChain->SetBranchAddress("jet_antikt4h1topo_BAD_CELLS_CORR_E", &jet_antikt4h1topo_BAD_CELLS_CORR_E, &b_jet_antikt4h1topo_BAD_CELLS_CORR_E);
   fChain->SetBranchAddress("jet_antikt4h1topo_hecf", &jet_antikt4h1topo_hecf, &b_jet_antikt4h1topo_hecf);
   fChain->SetBranchAddress("jet_antikt4h1topo_tgap3f", &jet_antikt4h1topo_tgap3f, &b_jet_antikt4h1topo_tgap3f);
   fChain->SetBranchAddress("jet_antikt4h1topo_isGood", &jet_antikt4h1topo_isGood, &b_jet_antikt4h1topo_isGood);
   fChain->SetBranchAddress("jet_antikt4h1topo_timing", &jet_antikt4h1topo_timing, &b_jet_antikt4h1topo_timing);
   fChain->SetBranchAddress("jet_antikt4h1topo_quality", &jet_antikt4h1topo_quality, &b_jet_antikt4h1topo_quality);
   fChain->SetBranchAddress("jet_antikt4h1topo_emfrac", &jet_antikt4h1topo_emfrac, &b_jet_antikt4h1topo_emfrac);
   fChain->SetBranchAddress("jet_antikt4h1topo_GCWJES", &jet_antikt4h1topo_GCWJES, &b_jet_antikt4h1topo_GCWJES);
   fChain->SetBranchAddress("jet_antikt4h1topo_EMJES", &jet_antikt4h1topo_EMJES, &b_jet_antikt4h1topo_EMJES);
   fChain->SetBranchAddress("jet_antikt4h1topo_CB", &jet_antikt4h1topo_CB, &b_jet_antikt4h1topo_CB);
   fChain->SetBranchAddress("jet_antikt4h1topo_emscale_E", &jet_antikt4h1topo_emscale_E, &b_jet_antikt4h1topo_emscale_E);
   fChain->SetBranchAddress("jet_antikt4h1topo_emscale_pt", &jet_antikt4h1topo_emscale_pt, &b_jet_antikt4h1topo_emscale_pt);
   fChain->SetBranchAddress("jet_antikt4h1topo_emscale_m", &jet_antikt4h1topo_emscale_m, &b_jet_antikt4h1topo_emscale_m);
   fChain->SetBranchAddress("jet_antikt4h1topo_emscale_eta", &jet_antikt4h1topo_emscale_eta, &b_jet_antikt4h1topo_emscale_eta);
   fChain->SetBranchAddress("jet_antikt4h1topo_emscale_phi", &jet_antikt4h1topo_emscale_phi, &b_jet_antikt4h1topo_emscale_phi);
   fChain->SetBranchAddress("jet_antikt4h1topo_jvtxf", &jet_antikt4h1topo_jvtxf, &b_jet_antikt4h1topo_jvtxf);
   fChain->SetBranchAddress("jet_antikt4h1topo_jvtx_x", &jet_antikt4h1topo_jvtx_x, &b_jet_antikt4h1topo_jvtx_x);
   fChain->SetBranchAddress("jet_antikt4h1topo_jvtx_y", &jet_antikt4h1topo_jvtx_y, &b_jet_antikt4h1topo_jvtx_y);
   fChain->SetBranchAddress("jet_antikt4h1topo_jvtx_z", &jet_antikt4h1topo_jvtx_z, &b_jet_antikt4h1topo_jvtx_z);
   fChain->SetBranchAddress("jet_antikt4h1topo_flavor_weight", &jet_antikt4h1topo_flavor_weight, &b_jet_antikt4h1topo_flavor_weight);
   fChain->SetBranchAddress("jet_antikt4h1topo_flavor_weight_TrackCounting2D", &jet_antikt4h1topo_flavor_weight_TrackCounting2D, &b_jet_antikt4h1topo_flavor_weight_TrackCounting2D);
   fChain->SetBranchAddress("jet_antikt4h1topo_flavor_weight_JetProb", &jet_antikt4h1topo_flavor_weight_JetProb, &b_jet_antikt4h1topo_flavor_weight_JetProb);
   fChain->SetBranchAddress("jet_antikt4h1topo_flavor_weight_IP1D", &jet_antikt4h1topo_flavor_weight_IP1D, &b_jet_antikt4h1topo_flavor_weight_IP1D);
   fChain->SetBranchAddress("jet_antikt4h1topo_flavor_weight_IP2D", &jet_antikt4h1topo_flavor_weight_IP2D, &b_jet_antikt4h1topo_flavor_weight_IP2D);
   fChain->SetBranchAddress("jet_antikt4h1topo_flavor_weight_IP3D", &jet_antikt4h1topo_flavor_weight_IP3D, &b_jet_antikt4h1topo_flavor_weight_IP3D);
   fChain->SetBranchAddress("jet_antikt4h1topo_flavor_weight_SV0", &jet_antikt4h1topo_flavor_weight_SV0, &b_jet_antikt4h1topo_flavor_weight_SV0);
   fChain->SetBranchAddress("jet_antikt4h1topo_flavor_weight_SV1", &jet_antikt4h1topo_flavor_weight_SV1, &b_jet_antikt4h1topo_flavor_weight_SV1);
   fChain->SetBranchAddress("jet_antikt4h1topo_flavor_weight_SV2", &jet_antikt4h1topo_flavor_weight_SV2, &b_jet_antikt4h1topo_flavor_weight_SV2);
   fChain->SetBranchAddress("jet_antikt4h1topo_flavor_weight_JetFitterTag", &jet_antikt4h1topo_flavor_weight_JetFitterTag, &b_jet_antikt4h1topo_flavor_weight_JetFitterTag);
   fChain->SetBranchAddress("jet_antikt4h1topo_flavor_weight_JetFitterCOMB", &jet_antikt4h1topo_flavor_weight_JetFitterCOMB, &b_jet_antikt4h1topo_flavor_weight_JetFitterCOMB);
   fChain->SetBranchAddress("jet_antikt4h1topo_flavor_weight_JetFitterTagNN", &jet_antikt4h1topo_flavor_weight_JetFitterTagNN, &b_jet_antikt4h1topo_flavor_weight_JetFitterTagNN);
   fChain->SetBranchAddress("jet_antikt4h1topo_flavor_weight_JetFitterCOMBNN", &jet_antikt4h1topo_flavor_weight_JetFitterCOMBNN, &b_jet_antikt4h1topo_flavor_weight_JetFitterCOMBNN);
   fChain->SetBranchAddress("jet_antikt4h1topo_flavor_weight_SoftMuonTag", &jet_antikt4h1topo_flavor_weight_SoftMuonTag, &b_jet_antikt4h1topo_flavor_weight_SoftMuonTag);
   fChain->SetBranchAddress("jet_antikt4h1topo_flavor_weight_SoftElectronTag", &jet_antikt4h1topo_flavor_weight_SoftElectronTag, &b_jet_antikt4h1topo_flavor_weight_SoftElectronTag);
   fChain->SetBranchAddress("jet_antikt4h1topo_e_PreSamplerB", &jet_antikt4h1topo_e_PreSamplerB, &b_jet_antikt4h1topo_e_PreSamplerB);
   fChain->SetBranchAddress("jet_antikt4h1topo_e_EMB1", &jet_antikt4h1topo_e_EMB1, &b_jet_antikt4h1topo_e_EMB1);
   fChain->SetBranchAddress("jet_antikt4h1topo_e_EMB2", &jet_antikt4h1topo_e_EMB2, &b_jet_antikt4h1topo_e_EMB2);
   fChain->SetBranchAddress("jet_antikt4h1topo_e_EMB3", &jet_antikt4h1topo_e_EMB3, &b_jet_antikt4h1topo_e_EMB3);
   fChain->SetBranchAddress("jet_antikt4h1topo_e_PreSamplerE", &jet_antikt4h1topo_e_PreSamplerE, &b_jet_antikt4h1topo_e_PreSamplerE);
   fChain->SetBranchAddress("jet_antikt4h1topo_e_EME1", &jet_antikt4h1topo_e_EME1, &b_jet_antikt4h1topo_e_EME1);
   fChain->SetBranchAddress("jet_antikt4h1topo_e_EME2", &jet_antikt4h1topo_e_EME2, &b_jet_antikt4h1topo_e_EME2);
   fChain->SetBranchAddress("jet_antikt4h1topo_e_EME3", &jet_antikt4h1topo_e_EME3, &b_jet_antikt4h1topo_e_EME3);
   fChain->SetBranchAddress("jet_antikt4h1topo_e_HEC0", &jet_antikt4h1topo_e_HEC0, &b_jet_antikt4h1topo_e_HEC0);
   fChain->SetBranchAddress("jet_antikt4h1topo_e_HEC1", &jet_antikt4h1topo_e_HEC1, &b_jet_antikt4h1topo_e_HEC1);
   fChain->SetBranchAddress("jet_antikt4h1topo_e_HEC2", &jet_antikt4h1topo_e_HEC2, &b_jet_antikt4h1topo_e_HEC2);
   fChain->SetBranchAddress("jet_antikt4h1topo_e_HEC3", &jet_antikt4h1topo_e_HEC3, &b_jet_antikt4h1topo_e_HEC3);
   fChain->SetBranchAddress("jet_antikt4h1topo_e_TileBar0", &jet_antikt4h1topo_e_TileBar0, &b_jet_antikt4h1topo_e_TileBar0);
   fChain->SetBranchAddress("jet_antikt4h1topo_e_TileBar1", &jet_antikt4h1topo_e_TileBar1, &b_jet_antikt4h1topo_e_TileBar1);
   fChain->SetBranchAddress("jet_antikt4h1topo_e_TileBar2", &jet_antikt4h1topo_e_TileBar2, &b_jet_antikt4h1topo_e_TileBar2);
   fChain->SetBranchAddress("jet_antikt4h1topo_e_TileGap1", &jet_antikt4h1topo_e_TileGap1, &b_jet_antikt4h1topo_e_TileGap1);
   fChain->SetBranchAddress("jet_antikt4h1topo_e_TileGap2", &jet_antikt4h1topo_e_TileGap2, &b_jet_antikt4h1topo_e_TileGap2);
   fChain->SetBranchAddress("jet_antikt4h1topo_e_TileGap3", &jet_antikt4h1topo_e_TileGap3, &b_jet_antikt4h1topo_e_TileGap3);
   fChain->SetBranchAddress("jet_antikt4h1topo_e_TileExt0", &jet_antikt4h1topo_e_TileExt0, &b_jet_antikt4h1topo_e_TileExt0);
   fChain->SetBranchAddress("jet_antikt4h1topo_e_TileExt1", &jet_antikt4h1topo_e_TileExt1, &b_jet_antikt4h1topo_e_TileExt1);
   fChain->SetBranchAddress("jet_antikt4h1topo_e_TileExt2", &jet_antikt4h1topo_e_TileExt2, &b_jet_antikt4h1topo_e_TileExt2);
   fChain->SetBranchAddress("jet_antikt4h1topo_e_FCAL0", &jet_antikt4h1topo_e_FCAL0, &b_jet_antikt4h1topo_e_FCAL0);
   fChain->SetBranchAddress("jet_antikt4h1topo_e_FCAL1", &jet_antikt4h1topo_e_FCAL1, &b_jet_antikt4h1topo_e_FCAL1);
   fChain->SetBranchAddress("jet_antikt4h1topo_e_FCAL2", &jet_antikt4h1topo_e_FCAL2, &b_jet_antikt4h1topo_e_FCAL2);
   fChain->SetBranchAddress("jet_antikt4h1topo_shapeBins", &jet_antikt4h1topo_shapeBins, &b_jet_antikt4h1topo_shapeBins);
   fChain->SetBranchAddress("jet_antikt4h1topo_flavor_component_ip2d_pu", &jet_antikt4h1topo_flavor_component_ip2d_pu, &b_jet_antikt4h1topo_flavor_component_ip2d_pu);
   fChain->SetBranchAddress("jet_antikt4h1topo_flavor_component_ip2d_pb", &jet_antikt4h1topo_flavor_component_ip2d_pb, &b_jet_antikt4h1topo_flavor_component_ip2d_pb);
   fChain->SetBranchAddress("jet_antikt4h1topo_flavor_component_ip2d_ntrk", &jet_antikt4h1topo_flavor_component_ip2d_ntrk, &b_jet_antikt4h1topo_flavor_component_ip2d_ntrk);
   fChain->SetBranchAddress("jet_antikt4h1topo_flavor_component_ip3d_pu", &jet_antikt4h1topo_flavor_component_ip3d_pu, &b_jet_antikt4h1topo_flavor_component_ip3d_pu);
   fChain->SetBranchAddress("jet_antikt4h1topo_flavor_component_ip3d_pb", &jet_antikt4h1topo_flavor_component_ip3d_pb, &b_jet_antikt4h1topo_flavor_component_ip3d_pb);
   fChain->SetBranchAddress("jet_antikt4h1topo_flavor_component_ip3d_ntrk", &jet_antikt4h1topo_flavor_component_ip3d_ntrk, &b_jet_antikt4h1topo_flavor_component_ip3d_ntrk);
   fChain->SetBranchAddress("jet_antikt4h1topo_flavor_component_sv1_pu", &jet_antikt4h1topo_flavor_component_sv1_pu, &b_jet_antikt4h1topo_flavor_component_sv1_pu);
   fChain->SetBranchAddress("jet_antikt4h1topo_flavor_component_sv1_pb", &jet_antikt4h1topo_flavor_component_sv1_pb, &b_jet_antikt4h1topo_flavor_component_sv1_pb);
   fChain->SetBranchAddress("jet_antikt4h1topo_flavor_component_sv2_pu", &jet_antikt4h1topo_flavor_component_sv2_pu, &b_jet_antikt4h1topo_flavor_component_sv2_pu);
   fChain->SetBranchAddress("jet_antikt4h1topo_flavor_component_sv2_pb", &jet_antikt4h1topo_flavor_component_sv2_pb, &b_jet_antikt4h1topo_flavor_component_sv2_pb);
   fChain->SetBranchAddress("jet_antikt4h1topo_flavor_component_svp_mass", &jet_antikt4h1topo_flavor_component_svp_mass, &b_jet_antikt4h1topo_flavor_component_svp_mass);
   fChain->SetBranchAddress("jet_antikt4h1topo_flavor_component_svp_n2t", &jet_antikt4h1topo_flavor_component_svp_n2t, &b_jet_antikt4h1topo_flavor_component_svp_n2t);
   fChain->SetBranchAddress("jet_antikt4h1topo_flavor_component_svp_svok", &jet_antikt4h1topo_flavor_component_svp_svok, &b_jet_antikt4h1topo_flavor_component_svp_svok);
   fChain->SetBranchAddress("jet_antikt4h1topo_flavor_component_svp_ntrk", &jet_antikt4h1topo_flavor_component_svp_ntrk, &b_jet_antikt4h1topo_flavor_component_svp_ntrk);
   fChain->SetBranchAddress("jet_antikt4h1topo_flavor_component_svp_ntrkv", &jet_antikt4h1topo_flavor_component_svp_ntrkv, &b_jet_antikt4h1topo_flavor_component_svp_ntrkv);
   fChain->SetBranchAddress("jet_antikt4h1topo_flavor_component_svp_ntrkj", &jet_antikt4h1topo_flavor_component_svp_ntrkj, &b_jet_antikt4h1topo_flavor_component_svp_ntrkj);
   fChain->SetBranchAddress("jet_antikt4h1topo_flavor_component_svp_efrc", &jet_antikt4h1topo_flavor_component_svp_efrc, &b_jet_antikt4h1topo_flavor_component_svp_efrc);
   fChain->SetBranchAddress("jet_antikt4h1topo_flavor_component_sv0p_mass", &jet_antikt4h1topo_flavor_component_sv0p_mass, &b_jet_antikt4h1topo_flavor_component_sv0p_mass);
   fChain->SetBranchAddress("jet_antikt4h1topo_flavor_component_sv0p_n2t", &jet_antikt4h1topo_flavor_component_sv0p_n2t, &b_jet_antikt4h1topo_flavor_component_sv0p_n2t);
   fChain->SetBranchAddress("jet_antikt4h1topo_flavor_component_sv0p_svok", &jet_antikt4h1topo_flavor_component_sv0p_svok, &b_jet_antikt4h1topo_flavor_component_sv0p_svok);
   fChain->SetBranchAddress("jet_antikt4h1topo_flavor_component_sv0p_ntrk", &jet_antikt4h1topo_flavor_component_sv0p_ntrk, &b_jet_antikt4h1topo_flavor_component_sv0p_ntrk);
   fChain->SetBranchAddress("jet_antikt4h1topo_flavor_component_sv0p_ntrkv", &jet_antikt4h1topo_flavor_component_sv0p_ntrkv, &b_jet_antikt4h1topo_flavor_component_sv0p_ntrkv);
   fChain->SetBranchAddress("jet_antikt4h1topo_flavor_component_sv0p_ntrkj", &jet_antikt4h1topo_flavor_component_sv0p_ntrkj, &b_jet_antikt4h1topo_flavor_component_sv0p_ntrkj);
   fChain->SetBranchAddress("jet_antikt4h1topo_flavor_component_sv0p_efrc", &jet_antikt4h1topo_flavor_component_sv0p_efrc, &b_jet_antikt4h1topo_flavor_component_sv0p_efrc);
   fChain->SetBranchAddress("jet_antikt4h1topo_flavor_component_jfit_pu", &jet_antikt4h1topo_flavor_component_jfit_pu, &b_jet_antikt4h1topo_flavor_component_jfit_pu);
   fChain->SetBranchAddress("jet_antikt4h1topo_flavor_component_jfit_pb", &jet_antikt4h1topo_flavor_component_jfit_pb, &b_jet_antikt4h1topo_flavor_component_jfit_pb);
   fChain->SetBranchAddress("jet_antikt4h1topo_flavor_component_jfit_nvtxnt", &jet_antikt4h1topo_flavor_component_jfit_nvtxnt, &b_jet_antikt4h1topo_flavor_component_jfit_nvtxnt);
   fChain->SetBranchAddress("jet_antikt4h1topo_flavor_component_jfit_nvtx1t", &jet_antikt4h1topo_flavor_component_jfit_nvtx1t, &b_jet_antikt4h1topo_flavor_component_jfit_nvtx1t);
   fChain->SetBranchAddress("jet_antikt4h1topo_flavor_component_jfit_ntrk", &jet_antikt4h1topo_flavor_component_jfit_ntrk, &b_jet_antikt4h1topo_flavor_component_jfit_ntrk);
   fChain->SetBranchAddress("jet_antikt4h1topo_flavor_component_jfit_efrc", &jet_antikt4h1topo_flavor_component_jfit_efrc, &b_jet_antikt4h1topo_flavor_component_jfit_efrc);
   fChain->SetBranchAddress("jet_antikt4h1topo_flavor_component_jfit_mass", &jet_antikt4h1topo_flavor_component_jfit_mass, &b_jet_antikt4h1topo_flavor_component_jfit_mass);
   fChain->SetBranchAddress("jet_antikt4h1topo_flavor_component_jfit_sig3d", &jet_antikt4h1topo_flavor_component_jfit_sig3d, &b_jet_antikt4h1topo_flavor_component_jfit_sig3d);
   fChain->SetBranchAddress("jet_antikt4h1topo_constscale_E", &jet_antikt4h1topo_constscale_E, &b_jet_antikt4h1topo_constscale_E);
   fChain->SetBranchAddress("jet_antikt4h1topo_constscale_pt", &jet_antikt4h1topo_constscale_pt, &b_jet_antikt4h1topo_constscale_pt);
   fChain->SetBranchAddress("jet_antikt4h1topo_constscale_m", &jet_antikt4h1topo_constscale_m, &b_jet_antikt4h1topo_constscale_m);
   fChain->SetBranchAddress("jet_antikt4h1topo_constscale_eta", &jet_antikt4h1topo_constscale_eta, &b_jet_antikt4h1topo_constscale_eta);
   fChain->SetBranchAddress("jet_antikt4h1topo_constscale_phi", &jet_antikt4h1topo_constscale_phi, &b_jet_antikt4h1topo_constscale_phi);
   fChain->SetBranchAddress("jet_antikt4h1topo_el_dr", &jet_antikt4h1topo_el_dr, &b_jet_antikt4h1topo_el_dr);
   fChain->SetBranchAddress("jet_antikt4h1topo_el_matched", &jet_antikt4h1topo_el_matched, &b_jet_antikt4h1topo_el_matched);
   fChain->SetBranchAddress("jet_antikt4h1topo_mu_dr", &jet_antikt4h1topo_mu_dr, &b_jet_antikt4h1topo_mu_dr);
   fChain->SetBranchAddress("jet_antikt4h1topo_mu_matched", &jet_antikt4h1topo_mu_matched, &b_jet_antikt4h1topo_mu_matched);
   fChain->SetBranchAddress("jet_antikt4h1tower_n", &jet_antikt4h1tower_n, &b_jet_antikt4h1tower_n);
   fChain->SetBranchAddress("jet_antikt4h1tower_E", &jet_antikt4h1tower_E, &b_jet_antikt4h1tower_E);
   fChain->SetBranchAddress("jet_antikt4h1tower_pt", &jet_antikt4h1tower_pt, &b_jet_antikt4h1tower_pt);
   fChain->SetBranchAddress("jet_antikt4h1tower_m", &jet_antikt4h1tower_m, &b_jet_antikt4h1tower_m);
   fChain->SetBranchAddress("jet_antikt4h1tower_eta", &jet_antikt4h1tower_eta, &b_jet_antikt4h1tower_eta);
   fChain->SetBranchAddress("jet_antikt4h1tower_phi", &jet_antikt4h1tower_phi, &b_jet_antikt4h1tower_phi);
   fChain->SetBranchAddress("jet_antikt4h1tower_EtaPhys", &jet_antikt4h1tower_EtaPhys, &b_jet_antikt4h1tower_EtaPhys);
   fChain->SetBranchAddress("jet_antikt4h1tower_PhiPhys", &jet_antikt4h1tower_PhiPhys, &b_jet_antikt4h1tower_PhiPhys);
   fChain->SetBranchAddress("jet_antikt4h1tower_MPhys", &jet_antikt4h1tower_MPhys, &b_jet_antikt4h1tower_MPhys);
   fChain->SetBranchAddress("jet_antikt4h1tower_WIDTH", &jet_antikt4h1tower_WIDTH, &b_jet_antikt4h1tower_WIDTH);
   fChain->SetBranchAddress("jet_antikt4h1tower_n90", &jet_antikt4h1tower_n90, &b_jet_antikt4h1tower_n90);
   fChain->SetBranchAddress("jet_antikt4h1tower_n90constituents", &jet_antikt4h1tower_n90constituents, &b_jet_antikt4h1tower_n90constituents);
   fChain->SetBranchAddress("jet_antikt4h1tower_fracSamplingMax", &jet_antikt4h1tower_fracSamplingMax, &b_jet_antikt4h1tower_fracSamplingMax);
   fChain->SetBranchAddress("jet_antikt4h1tower_SamplingMax", &jet_antikt4h1tower_SamplingMax, &b_jet_antikt4h1tower_SamplingMax);
   fChain->SetBranchAddress("jet_antikt4h1tower_BCH_CORR_CELL", &jet_antikt4h1tower_BCH_CORR_CELL, &b_jet_antikt4h1tower_BCH_CORR_CELL);
   fChain->SetBranchAddress("jet_antikt4h1tower_BCH_CORR_DOTX", &jet_antikt4h1tower_BCH_CORR_DOTX, &b_jet_antikt4h1tower_BCH_CORR_DOTX);
   fChain->SetBranchAddress("jet_antikt4h1tower_BCH_CORR_JET", &jet_antikt4h1tower_BCH_CORR_JET, &b_jet_antikt4h1tower_BCH_CORR_JET);
   fChain->SetBranchAddress("jet_antikt4h1tower_BCH_CORR_JET_FORCELL", &jet_antikt4h1tower_BCH_CORR_JET_FORCELL, &b_jet_antikt4h1tower_BCH_CORR_JET_FORCELL);
   fChain->SetBranchAddress("jet_antikt4h1tower_ENG_BAD_CELLS", &jet_antikt4h1tower_ENG_BAD_CELLS, &b_jet_antikt4h1tower_ENG_BAD_CELLS);
   fChain->SetBranchAddress("jet_antikt4h1tower_N_BAD_CELLS", &jet_antikt4h1tower_N_BAD_CELLS, &b_jet_antikt4h1tower_N_BAD_CELLS);
   fChain->SetBranchAddress("jet_antikt4h1tower_N_BAD_CELLS_CORR", &jet_antikt4h1tower_N_BAD_CELLS_CORR, &b_jet_antikt4h1tower_N_BAD_CELLS_CORR);
   fChain->SetBranchAddress("jet_antikt4h1tower_BAD_CELLS_CORR_E", &jet_antikt4h1tower_BAD_CELLS_CORR_E, &b_jet_antikt4h1tower_BAD_CELLS_CORR_E);
   fChain->SetBranchAddress("jet_antikt4h1tower_hecf", &jet_antikt4h1tower_hecf, &b_jet_antikt4h1tower_hecf);
   fChain->SetBranchAddress("jet_antikt4h1tower_tgap3f", &jet_antikt4h1tower_tgap3f, &b_jet_antikt4h1tower_tgap3f);
   fChain->SetBranchAddress("jet_antikt4h1tower_isGood", &jet_antikt4h1tower_isGood, &b_jet_antikt4h1tower_isGood);
   fChain->SetBranchAddress("jet_antikt4h1tower_timing", &jet_antikt4h1tower_timing, &b_jet_antikt4h1tower_timing);
   fChain->SetBranchAddress("jet_antikt4h1tower_quality", &jet_antikt4h1tower_quality, &b_jet_antikt4h1tower_quality);
   fChain->SetBranchAddress("jet_antikt4h1tower_emfrac", &jet_antikt4h1tower_emfrac, &b_jet_antikt4h1tower_emfrac);
   fChain->SetBranchAddress("jet_antikt4h1tower_GCWJES", &jet_antikt4h1tower_GCWJES, &b_jet_antikt4h1tower_GCWJES);
   fChain->SetBranchAddress("jet_antikt4h1tower_EMJES", &jet_antikt4h1tower_EMJES, &b_jet_antikt4h1tower_EMJES);
   fChain->SetBranchAddress("jet_antikt4h1tower_CB", &jet_antikt4h1tower_CB, &b_jet_antikt4h1tower_CB);
   fChain->SetBranchAddress("jet_antikt4h1tower_emscale_E", &jet_antikt4h1tower_emscale_E, &b_jet_antikt4h1tower_emscale_E);
   fChain->SetBranchAddress("jet_antikt4h1tower_emscale_pt", &jet_antikt4h1tower_emscale_pt, &b_jet_antikt4h1tower_emscale_pt);
   fChain->SetBranchAddress("jet_antikt4h1tower_emscale_m", &jet_antikt4h1tower_emscale_m, &b_jet_antikt4h1tower_emscale_m);
   fChain->SetBranchAddress("jet_antikt4h1tower_emscale_eta", &jet_antikt4h1tower_emscale_eta, &b_jet_antikt4h1tower_emscale_eta);
   fChain->SetBranchAddress("jet_antikt4h1tower_emscale_phi", &jet_antikt4h1tower_emscale_phi, &b_jet_antikt4h1tower_emscale_phi);
   fChain->SetBranchAddress("jet_antikt4h1tower_jvtxf", &jet_antikt4h1tower_jvtxf, &b_jet_antikt4h1tower_jvtxf);
   fChain->SetBranchAddress("jet_antikt4h1tower_jvtx_x", &jet_antikt4h1tower_jvtx_x, &b_jet_antikt4h1tower_jvtx_x);
   fChain->SetBranchAddress("jet_antikt4h1tower_jvtx_y", &jet_antikt4h1tower_jvtx_y, &b_jet_antikt4h1tower_jvtx_y);
   fChain->SetBranchAddress("jet_antikt4h1tower_jvtx_z", &jet_antikt4h1tower_jvtx_z, &b_jet_antikt4h1tower_jvtx_z);
   fChain->SetBranchAddress("jet_antikt4h1tower_flavor_weight", &jet_antikt4h1tower_flavor_weight, &b_jet_antikt4h1tower_flavor_weight);
   fChain->SetBranchAddress("jet_antikt4h1tower_flavor_weight_TrackCounting2D", &jet_antikt4h1tower_flavor_weight_TrackCounting2D, &b_jet_antikt4h1tower_flavor_weight_TrackCounting2D);
   fChain->SetBranchAddress("jet_antikt4h1tower_flavor_weight_JetProb", &jet_antikt4h1tower_flavor_weight_JetProb, &b_jet_antikt4h1tower_flavor_weight_JetProb);
   fChain->SetBranchAddress("jet_antikt4h1tower_flavor_weight_IP1D", &jet_antikt4h1tower_flavor_weight_IP1D, &b_jet_antikt4h1tower_flavor_weight_IP1D);
   fChain->SetBranchAddress("jet_antikt4h1tower_flavor_weight_IP2D", &jet_antikt4h1tower_flavor_weight_IP2D, &b_jet_antikt4h1tower_flavor_weight_IP2D);
   fChain->SetBranchAddress("jet_antikt4h1tower_flavor_weight_IP3D", &jet_antikt4h1tower_flavor_weight_IP3D, &b_jet_antikt4h1tower_flavor_weight_IP3D);
   fChain->SetBranchAddress("jet_antikt4h1tower_flavor_weight_SV0", &jet_antikt4h1tower_flavor_weight_SV0, &b_jet_antikt4h1tower_flavor_weight_SV0);
   fChain->SetBranchAddress("jet_antikt4h1tower_flavor_weight_SV1", &jet_antikt4h1tower_flavor_weight_SV1, &b_jet_antikt4h1tower_flavor_weight_SV1);
   fChain->SetBranchAddress("jet_antikt4h1tower_flavor_weight_SV2", &jet_antikt4h1tower_flavor_weight_SV2, &b_jet_antikt4h1tower_flavor_weight_SV2);
   fChain->SetBranchAddress("jet_antikt4h1tower_flavor_weight_JetFitterTag", &jet_antikt4h1tower_flavor_weight_JetFitterTag, &b_jet_antikt4h1tower_flavor_weight_JetFitterTag);
   fChain->SetBranchAddress("jet_antikt4h1tower_flavor_weight_JetFitterCOMB", &jet_antikt4h1tower_flavor_weight_JetFitterCOMB, &b_jet_antikt4h1tower_flavor_weight_JetFitterCOMB);
   fChain->SetBranchAddress("jet_antikt4h1tower_flavor_weight_JetFitterTagNN", &jet_antikt4h1tower_flavor_weight_JetFitterTagNN, &b_jet_antikt4h1tower_flavor_weight_JetFitterTagNN);
   fChain->SetBranchAddress("jet_antikt4h1tower_flavor_weight_JetFitterCOMBNN", &jet_antikt4h1tower_flavor_weight_JetFitterCOMBNN, &b_jet_antikt4h1tower_flavor_weight_JetFitterCOMBNN);
   fChain->SetBranchAddress("jet_antikt4h1tower_flavor_weight_SoftMuonTag", &jet_antikt4h1tower_flavor_weight_SoftMuonTag, &b_jet_antikt4h1tower_flavor_weight_SoftMuonTag);
   fChain->SetBranchAddress("jet_antikt4h1tower_flavor_weight_SoftElectronTag", &jet_antikt4h1tower_flavor_weight_SoftElectronTag, &b_jet_antikt4h1tower_flavor_weight_SoftElectronTag);
   fChain->SetBranchAddress("jet_antikt4h1tower_e_PreSamplerB", &jet_antikt4h1tower_e_PreSamplerB, &b_jet_antikt4h1tower_e_PreSamplerB);
   fChain->SetBranchAddress("jet_antikt4h1tower_e_EMB1", &jet_antikt4h1tower_e_EMB1, &b_jet_antikt4h1tower_e_EMB1);
   fChain->SetBranchAddress("jet_antikt4h1tower_e_EMB2", &jet_antikt4h1tower_e_EMB2, &b_jet_antikt4h1tower_e_EMB2);
   fChain->SetBranchAddress("jet_antikt4h1tower_e_EMB3", &jet_antikt4h1tower_e_EMB3, &b_jet_antikt4h1tower_e_EMB3);
   fChain->SetBranchAddress("jet_antikt4h1tower_e_PreSamplerE", &jet_antikt4h1tower_e_PreSamplerE, &b_jet_antikt4h1tower_e_PreSamplerE);
   fChain->SetBranchAddress("jet_antikt4h1tower_e_EME1", &jet_antikt4h1tower_e_EME1, &b_jet_antikt4h1tower_e_EME1);
   fChain->SetBranchAddress("jet_antikt4h1tower_e_EME2", &jet_antikt4h1tower_e_EME2, &b_jet_antikt4h1tower_e_EME2);
   fChain->SetBranchAddress("jet_antikt4h1tower_e_EME3", &jet_antikt4h1tower_e_EME3, &b_jet_antikt4h1tower_e_EME3);
   fChain->SetBranchAddress("jet_antikt4h1tower_e_HEC0", &jet_antikt4h1tower_e_HEC0, &b_jet_antikt4h1tower_e_HEC0);
   fChain->SetBranchAddress("jet_antikt4h1tower_e_HEC1", &jet_antikt4h1tower_e_HEC1, &b_jet_antikt4h1tower_e_HEC1);
   fChain->SetBranchAddress("jet_antikt4h1tower_e_HEC2", &jet_antikt4h1tower_e_HEC2, &b_jet_antikt4h1tower_e_HEC2);
   fChain->SetBranchAddress("jet_antikt4h1tower_e_HEC3", &jet_antikt4h1tower_e_HEC3, &b_jet_antikt4h1tower_e_HEC3);
   fChain->SetBranchAddress("jet_antikt4h1tower_e_TileBar0", &jet_antikt4h1tower_e_TileBar0, &b_jet_antikt4h1tower_e_TileBar0);
   fChain->SetBranchAddress("jet_antikt4h1tower_e_TileBar1", &jet_antikt4h1tower_e_TileBar1, &b_jet_antikt4h1tower_e_TileBar1);
   fChain->SetBranchAddress("jet_antikt4h1tower_e_TileBar2", &jet_antikt4h1tower_e_TileBar2, &b_jet_antikt4h1tower_e_TileBar2);
   fChain->SetBranchAddress("jet_antikt4h1tower_e_TileGap1", &jet_antikt4h1tower_e_TileGap1, &b_jet_antikt4h1tower_e_TileGap1);
   fChain->SetBranchAddress("jet_antikt4h1tower_e_TileGap2", &jet_antikt4h1tower_e_TileGap2, &b_jet_antikt4h1tower_e_TileGap2);
   fChain->SetBranchAddress("jet_antikt4h1tower_e_TileGap3", &jet_antikt4h1tower_e_TileGap3, &b_jet_antikt4h1tower_e_TileGap3);
   fChain->SetBranchAddress("jet_antikt4h1tower_e_TileExt0", &jet_antikt4h1tower_e_TileExt0, &b_jet_antikt4h1tower_e_TileExt0);
   fChain->SetBranchAddress("jet_antikt4h1tower_e_TileExt1", &jet_antikt4h1tower_e_TileExt1, &b_jet_antikt4h1tower_e_TileExt1);
   fChain->SetBranchAddress("jet_antikt4h1tower_e_TileExt2", &jet_antikt4h1tower_e_TileExt2, &b_jet_antikt4h1tower_e_TileExt2);
   fChain->SetBranchAddress("jet_antikt4h1tower_e_FCAL0", &jet_antikt4h1tower_e_FCAL0, &b_jet_antikt4h1tower_e_FCAL0);
   fChain->SetBranchAddress("jet_antikt4h1tower_e_FCAL1", &jet_antikt4h1tower_e_FCAL1, &b_jet_antikt4h1tower_e_FCAL1);
   fChain->SetBranchAddress("jet_antikt4h1tower_e_FCAL2", &jet_antikt4h1tower_e_FCAL2, &b_jet_antikt4h1tower_e_FCAL2);
   fChain->SetBranchAddress("jet_antikt4h1tower_shapeBins", &jet_antikt4h1tower_shapeBins, &b_jet_antikt4h1tower_shapeBins);
   fChain->SetBranchAddress("jet_antikt4h1tower_flavor_component_ip2d_pu", &jet_antikt4h1tower_flavor_component_ip2d_pu, &b_jet_antikt4h1tower_flavor_component_ip2d_pu);
   fChain->SetBranchAddress("jet_antikt4h1tower_flavor_component_ip2d_pb", &jet_antikt4h1tower_flavor_component_ip2d_pb, &b_jet_antikt4h1tower_flavor_component_ip2d_pb);
   fChain->SetBranchAddress("jet_antikt4h1tower_flavor_component_ip2d_ntrk", &jet_antikt4h1tower_flavor_component_ip2d_ntrk, &b_jet_antikt4h1tower_flavor_component_ip2d_ntrk);
   fChain->SetBranchAddress("jet_antikt4h1tower_flavor_component_ip3d_pu", &jet_antikt4h1tower_flavor_component_ip3d_pu, &b_jet_antikt4h1tower_flavor_component_ip3d_pu);
   fChain->SetBranchAddress("jet_antikt4h1tower_flavor_component_ip3d_pb", &jet_antikt4h1tower_flavor_component_ip3d_pb, &b_jet_antikt4h1tower_flavor_component_ip3d_pb);
   fChain->SetBranchAddress("jet_antikt4h1tower_flavor_component_ip3d_ntrk", &jet_antikt4h1tower_flavor_component_ip3d_ntrk, &b_jet_antikt4h1tower_flavor_component_ip3d_ntrk);
   fChain->SetBranchAddress("jet_antikt4h1tower_flavor_component_sv1_pu", &jet_antikt4h1tower_flavor_component_sv1_pu, &b_jet_antikt4h1tower_flavor_component_sv1_pu);
   fChain->SetBranchAddress("jet_antikt4h1tower_flavor_component_sv1_pb", &jet_antikt4h1tower_flavor_component_sv1_pb, &b_jet_antikt4h1tower_flavor_component_sv1_pb);
   fChain->SetBranchAddress("jet_antikt4h1tower_flavor_component_sv2_pu", &jet_antikt4h1tower_flavor_component_sv2_pu, &b_jet_antikt4h1tower_flavor_component_sv2_pu);
   fChain->SetBranchAddress("jet_antikt4h1tower_flavor_component_sv2_pb", &jet_antikt4h1tower_flavor_component_sv2_pb, &b_jet_antikt4h1tower_flavor_component_sv2_pb);
   fChain->SetBranchAddress("jet_antikt4h1tower_flavor_component_svp_mass", &jet_antikt4h1tower_flavor_component_svp_mass, &b_jet_antikt4h1tower_flavor_component_svp_mass);
   fChain->SetBranchAddress("jet_antikt4h1tower_flavor_component_svp_n2t", &jet_antikt4h1tower_flavor_component_svp_n2t, &b_jet_antikt4h1tower_flavor_component_svp_n2t);
   fChain->SetBranchAddress("jet_antikt4h1tower_flavor_component_svp_svok", &jet_antikt4h1tower_flavor_component_svp_svok, &b_jet_antikt4h1tower_flavor_component_svp_svok);
   fChain->SetBranchAddress("jet_antikt4h1tower_flavor_component_svp_ntrk", &jet_antikt4h1tower_flavor_component_svp_ntrk, &b_jet_antikt4h1tower_flavor_component_svp_ntrk);
   fChain->SetBranchAddress("jet_antikt4h1tower_flavor_component_svp_ntrkv", &jet_antikt4h1tower_flavor_component_svp_ntrkv, &b_jet_antikt4h1tower_flavor_component_svp_ntrkv);
   fChain->SetBranchAddress("jet_antikt4h1tower_flavor_component_svp_ntrkj", &jet_antikt4h1tower_flavor_component_svp_ntrkj, &b_jet_antikt4h1tower_flavor_component_svp_ntrkj);
   fChain->SetBranchAddress("jet_antikt4h1tower_flavor_component_svp_efrc", &jet_antikt4h1tower_flavor_component_svp_efrc, &b_jet_antikt4h1tower_flavor_component_svp_efrc);
   fChain->SetBranchAddress("jet_antikt4h1tower_flavor_component_sv0p_mass", &jet_antikt4h1tower_flavor_component_sv0p_mass, &b_jet_antikt4h1tower_flavor_component_sv0p_mass);
   fChain->SetBranchAddress("jet_antikt4h1tower_flavor_component_sv0p_n2t", &jet_antikt4h1tower_flavor_component_sv0p_n2t, &b_jet_antikt4h1tower_flavor_component_sv0p_n2t);
   fChain->SetBranchAddress("jet_antikt4h1tower_flavor_component_sv0p_svok", &jet_antikt4h1tower_flavor_component_sv0p_svok, &b_jet_antikt4h1tower_flavor_component_sv0p_svok);
   fChain->SetBranchAddress("jet_antikt4h1tower_flavor_component_sv0p_ntrk", &jet_antikt4h1tower_flavor_component_sv0p_ntrk, &b_jet_antikt4h1tower_flavor_component_sv0p_ntrk);
   fChain->SetBranchAddress("jet_antikt4h1tower_flavor_component_sv0p_ntrkv", &jet_antikt4h1tower_flavor_component_sv0p_ntrkv, &b_jet_antikt4h1tower_flavor_component_sv0p_ntrkv);
   fChain->SetBranchAddress("jet_antikt4h1tower_flavor_component_sv0p_ntrkj", &jet_antikt4h1tower_flavor_component_sv0p_ntrkj, &b_jet_antikt4h1tower_flavor_component_sv0p_ntrkj);
   fChain->SetBranchAddress("jet_antikt4h1tower_flavor_component_sv0p_efrc", &jet_antikt4h1tower_flavor_component_sv0p_efrc, &b_jet_antikt4h1tower_flavor_component_sv0p_efrc);
   fChain->SetBranchAddress("jet_antikt4h1tower_flavor_component_jfit_pu", &jet_antikt4h1tower_flavor_component_jfit_pu, &b_jet_antikt4h1tower_flavor_component_jfit_pu);
   fChain->SetBranchAddress("jet_antikt4h1tower_flavor_component_jfit_pb", &jet_antikt4h1tower_flavor_component_jfit_pb, &b_jet_antikt4h1tower_flavor_component_jfit_pb);
   fChain->SetBranchAddress("jet_antikt4h1tower_flavor_component_jfit_nvtxnt", &jet_antikt4h1tower_flavor_component_jfit_nvtxnt, &b_jet_antikt4h1tower_flavor_component_jfit_nvtxnt);
   fChain->SetBranchAddress("jet_antikt4h1tower_flavor_component_jfit_nvtx1t", &jet_antikt4h1tower_flavor_component_jfit_nvtx1t, &b_jet_antikt4h1tower_flavor_component_jfit_nvtx1t);
   fChain->SetBranchAddress("jet_antikt4h1tower_flavor_component_jfit_ntrk", &jet_antikt4h1tower_flavor_component_jfit_ntrk, &b_jet_antikt4h1tower_flavor_component_jfit_ntrk);
   fChain->SetBranchAddress("jet_antikt4h1tower_flavor_component_jfit_efrc", &jet_antikt4h1tower_flavor_component_jfit_efrc, &b_jet_antikt4h1tower_flavor_component_jfit_efrc);
   fChain->SetBranchAddress("jet_antikt4h1tower_flavor_component_jfit_mass", &jet_antikt4h1tower_flavor_component_jfit_mass, &b_jet_antikt4h1tower_flavor_component_jfit_mass);
   fChain->SetBranchAddress("jet_antikt4h1tower_flavor_component_jfit_sig3d", &jet_antikt4h1tower_flavor_component_jfit_sig3d, &b_jet_antikt4h1tower_flavor_component_jfit_sig3d);
   fChain->SetBranchAddress("jet_antikt4h1tower_constscale_E", &jet_antikt4h1tower_constscale_E, &b_jet_antikt4h1tower_constscale_E);
   fChain->SetBranchAddress("jet_antikt4h1tower_constscale_pt", &jet_antikt4h1tower_constscale_pt, &b_jet_antikt4h1tower_constscale_pt);
   fChain->SetBranchAddress("jet_antikt4h1tower_constscale_m", &jet_antikt4h1tower_constscale_m, &b_jet_antikt4h1tower_constscale_m);
   fChain->SetBranchAddress("jet_antikt4h1tower_constscale_eta", &jet_antikt4h1tower_constscale_eta, &b_jet_antikt4h1tower_constscale_eta);
   fChain->SetBranchAddress("jet_antikt4h1tower_constscale_phi", &jet_antikt4h1tower_constscale_phi, &b_jet_antikt4h1tower_constscale_phi);
   fChain->SetBranchAddress("jet_antikt4h1tower_el_dr", &jet_antikt4h1tower_el_dr, &b_jet_antikt4h1tower_el_dr);
   fChain->SetBranchAddress("jet_antikt4h1tower_el_matched", &jet_antikt4h1tower_el_matched, &b_jet_antikt4h1tower_el_matched);
   fChain->SetBranchAddress("jet_antikt4h1tower_mu_dr", &jet_antikt4h1tower_mu_dr, &b_jet_antikt4h1tower_mu_dr);
   fChain->SetBranchAddress("jet_antikt4h1tower_mu_matched", &jet_antikt4h1tower_mu_matched, &b_jet_antikt4h1tower_mu_matched);
   fChain->SetBranchAddress("jet_antikt6h1tower_n", &jet_antikt6h1tower_n, &b_jet_antikt6h1tower_n);
   fChain->SetBranchAddress("jet_antikt6h1tower_E", &jet_antikt6h1tower_E, &b_jet_antikt6h1tower_E);
   fChain->SetBranchAddress("jet_antikt6h1tower_pt", &jet_antikt6h1tower_pt, &b_jet_antikt6h1tower_pt);
   fChain->SetBranchAddress("jet_antikt6h1tower_m", &jet_antikt6h1tower_m, &b_jet_antikt6h1tower_m);
   fChain->SetBranchAddress("jet_antikt6h1tower_eta", &jet_antikt6h1tower_eta, &b_jet_antikt6h1tower_eta);
   fChain->SetBranchAddress("jet_antikt6h1tower_phi", &jet_antikt6h1tower_phi, &b_jet_antikt6h1tower_phi);
   fChain->SetBranchAddress("jet_antikt6h1tower_EtaPhys", &jet_antikt6h1tower_EtaPhys, &b_jet_antikt6h1tower_EtaPhys);
   fChain->SetBranchAddress("jet_antikt6h1tower_PhiPhys", &jet_antikt6h1tower_PhiPhys, &b_jet_antikt6h1tower_PhiPhys);
   fChain->SetBranchAddress("jet_antikt6h1tower_MPhys", &jet_antikt6h1tower_MPhys, &b_jet_antikt6h1tower_MPhys);
   fChain->SetBranchAddress("jet_antikt6h1tower_WIDTH", &jet_antikt6h1tower_WIDTH, &b_jet_antikt6h1tower_WIDTH);
   fChain->SetBranchAddress("jet_antikt6h1tower_n90", &jet_antikt6h1tower_n90, &b_jet_antikt6h1tower_n90);
   fChain->SetBranchAddress("jet_antikt6h1tower_n90constituents", &jet_antikt6h1tower_n90constituents, &b_jet_antikt6h1tower_n90constituents);
   fChain->SetBranchAddress("jet_antikt6h1tower_fracSamplingMax", &jet_antikt6h1tower_fracSamplingMax, &b_jet_antikt6h1tower_fracSamplingMax);
   fChain->SetBranchAddress("jet_antikt6h1tower_SamplingMax", &jet_antikt6h1tower_SamplingMax, &b_jet_antikt6h1tower_SamplingMax);
   fChain->SetBranchAddress("jet_antikt6h1tower_BCH_CORR_CELL", &jet_antikt6h1tower_BCH_CORR_CELL, &b_jet_antikt6h1tower_BCH_CORR_CELL);
   fChain->SetBranchAddress("jet_antikt6h1tower_BCH_CORR_DOTX", &jet_antikt6h1tower_BCH_CORR_DOTX, &b_jet_antikt6h1tower_BCH_CORR_DOTX);
   fChain->SetBranchAddress("jet_antikt6h1tower_BCH_CORR_JET", &jet_antikt6h1tower_BCH_CORR_JET, &b_jet_antikt6h1tower_BCH_CORR_JET);
   fChain->SetBranchAddress("jet_antikt6h1tower_BCH_CORR_JET_FORCELL", &jet_antikt6h1tower_BCH_CORR_JET_FORCELL, &b_jet_antikt6h1tower_BCH_CORR_JET_FORCELL);
   fChain->SetBranchAddress("jet_antikt6h1tower_ENG_BAD_CELLS", &jet_antikt6h1tower_ENG_BAD_CELLS, &b_jet_antikt6h1tower_ENG_BAD_CELLS);
   fChain->SetBranchAddress("jet_antikt6h1tower_N_BAD_CELLS", &jet_antikt6h1tower_N_BAD_CELLS, &b_jet_antikt6h1tower_N_BAD_CELLS);
   fChain->SetBranchAddress("jet_antikt6h1tower_N_BAD_CELLS_CORR", &jet_antikt6h1tower_N_BAD_CELLS_CORR, &b_jet_antikt6h1tower_N_BAD_CELLS_CORR);
   fChain->SetBranchAddress("jet_antikt6h1tower_BAD_CELLS_CORR_E", &jet_antikt6h1tower_BAD_CELLS_CORR_E, &b_jet_antikt6h1tower_BAD_CELLS_CORR_E);
   fChain->SetBranchAddress("jet_antikt6h1tower_hecf", &jet_antikt6h1tower_hecf, &b_jet_antikt6h1tower_hecf);
   fChain->SetBranchAddress("jet_antikt6h1tower_tgap3f", &jet_antikt6h1tower_tgap3f, &b_jet_antikt6h1tower_tgap3f);
   fChain->SetBranchAddress("jet_antikt6h1tower_isGood", &jet_antikt6h1tower_isGood, &b_jet_antikt6h1tower_isGood);
   fChain->SetBranchAddress("jet_antikt6h1tower_timing", &jet_antikt6h1tower_timing, &b_jet_antikt6h1tower_timing);
   fChain->SetBranchAddress("jet_antikt6h1tower_quality", &jet_antikt6h1tower_quality, &b_jet_antikt6h1tower_quality);
   fChain->SetBranchAddress("jet_antikt6h1tower_emfrac", &jet_antikt6h1tower_emfrac, &b_jet_antikt6h1tower_emfrac);
   fChain->SetBranchAddress("jet_antikt6h1tower_GCWJES", &jet_antikt6h1tower_GCWJES, &b_jet_antikt6h1tower_GCWJES);
   fChain->SetBranchAddress("jet_antikt6h1tower_EMJES", &jet_antikt6h1tower_EMJES, &b_jet_antikt6h1tower_EMJES);
   fChain->SetBranchAddress("jet_antikt6h1tower_CB", &jet_antikt6h1tower_CB, &b_jet_antikt6h1tower_CB);
   fChain->SetBranchAddress("jet_antikt6h1tower_emscale_E", &jet_antikt6h1tower_emscale_E, &b_jet_antikt6h1tower_emscale_E);
   fChain->SetBranchAddress("jet_antikt6h1tower_emscale_pt", &jet_antikt6h1tower_emscale_pt, &b_jet_antikt6h1tower_emscale_pt);
   fChain->SetBranchAddress("jet_antikt6h1tower_emscale_m", &jet_antikt6h1tower_emscale_m, &b_jet_antikt6h1tower_emscale_m);
   fChain->SetBranchAddress("jet_antikt6h1tower_emscale_eta", &jet_antikt6h1tower_emscale_eta, &b_jet_antikt6h1tower_emscale_eta);
   fChain->SetBranchAddress("jet_antikt6h1tower_emscale_phi", &jet_antikt6h1tower_emscale_phi, &b_jet_antikt6h1tower_emscale_phi);
   fChain->SetBranchAddress("jet_antikt6h1tower_jvtxf", &jet_antikt6h1tower_jvtxf, &b_jet_antikt6h1tower_jvtxf);
   fChain->SetBranchAddress("jet_antikt6h1tower_jvtx_x", &jet_antikt6h1tower_jvtx_x, &b_jet_antikt6h1tower_jvtx_x);
   fChain->SetBranchAddress("jet_antikt6h1tower_jvtx_y", &jet_antikt6h1tower_jvtx_y, &b_jet_antikt6h1tower_jvtx_y);
   fChain->SetBranchAddress("jet_antikt6h1tower_jvtx_z", &jet_antikt6h1tower_jvtx_z, &b_jet_antikt6h1tower_jvtx_z);
   fChain->SetBranchAddress("jet_antikt6h1tower_flavor_weight", &jet_antikt6h1tower_flavor_weight, &b_jet_antikt6h1tower_flavor_weight);
   fChain->SetBranchAddress("jet_antikt6h1tower_flavor_weight_TrackCounting2D", &jet_antikt6h1tower_flavor_weight_TrackCounting2D, &b_jet_antikt6h1tower_flavor_weight_TrackCounting2D);
   fChain->SetBranchAddress("jet_antikt6h1tower_flavor_weight_JetProb", &jet_antikt6h1tower_flavor_weight_JetProb, &b_jet_antikt6h1tower_flavor_weight_JetProb);
   fChain->SetBranchAddress("jet_antikt6h1tower_flavor_weight_IP1D", &jet_antikt6h1tower_flavor_weight_IP1D, &b_jet_antikt6h1tower_flavor_weight_IP1D);
   fChain->SetBranchAddress("jet_antikt6h1tower_flavor_weight_IP2D", &jet_antikt6h1tower_flavor_weight_IP2D, &b_jet_antikt6h1tower_flavor_weight_IP2D);
   fChain->SetBranchAddress("jet_antikt6h1tower_flavor_weight_IP3D", &jet_antikt6h1tower_flavor_weight_IP3D, &b_jet_antikt6h1tower_flavor_weight_IP3D);
   fChain->SetBranchAddress("jet_antikt6h1tower_flavor_weight_SV0", &jet_antikt6h1tower_flavor_weight_SV0, &b_jet_antikt6h1tower_flavor_weight_SV0);
   fChain->SetBranchAddress("jet_antikt6h1tower_flavor_weight_SV1", &jet_antikt6h1tower_flavor_weight_SV1, &b_jet_antikt6h1tower_flavor_weight_SV1);
   fChain->SetBranchAddress("jet_antikt6h1tower_flavor_weight_SV2", &jet_antikt6h1tower_flavor_weight_SV2, &b_jet_antikt6h1tower_flavor_weight_SV2);
   fChain->SetBranchAddress("jet_antikt6h1tower_flavor_weight_JetFitterTag", &jet_antikt6h1tower_flavor_weight_JetFitterTag, &b_jet_antikt6h1tower_flavor_weight_JetFitterTag);
   fChain->SetBranchAddress("jet_antikt6h1tower_flavor_weight_JetFitterCOMB", &jet_antikt6h1tower_flavor_weight_JetFitterCOMB, &b_jet_antikt6h1tower_flavor_weight_JetFitterCOMB);
   fChain->SetBranchAddress("jet_antikt6h1tower_flavor_weight_JetFitterTagNN", &jet_antikt6h1tower_flavor_weight_JetFitterTagNN, &b_jet_antikt6h1tower_flavor_weight_JetFitterTagNN);
   fChain->SetBranchAddress("jet_antikt6h1tower_flavor_weight_JetFitterCOMBNN", &jet_antikt6h1tower_flavor_weight_JetFitterCOMBNN, &b_jet_antikt6h1tower_flavor_weight_JetFitterCOMBNN);
   fChain->SetBranchAddress("jet_antikt6h1tower_flavor_weight_SoftMuonTag", &jet_antikt6h1tower_flavor_weight_SoftMuonTag, &b_jet_antikt6h1tower_flavor_weight_SoftMuonTag);
   fChain->SetBranchAddress("jet_antikt6h1tower_flavor_weight_SoftElectronTag", &jet_antikt6h1tower_flavor_weight_SoftElectronTag, &b_jet_antikt6h1tower_flavor_weight_SoftElectronTag);
   fChain->SetBranchAddress("jet_antikt6h1tower_e_PreSamplerB", &jet_antikt6h1tower_e_PreSamplerB, &b_jet_antikt6h1tower_e_PreSamplerB);
   fChain->SetBranchAddress("jet_antikt6h1tower_e_EMB1", &jet_antikt6h1tower_e_EMB1, &b_jet_antikt6h1tower_e_EMB1);
   fChain->SetBranchAddress("jet_antikt6h1tower_e_EMB2", &jet_antikt6h1tower_e_EMB2, &b_jet_antikt6h1tower_e_EMB2);
   fChain->SetBranchAddress("jet_antikt6h1tower_e_EMB3", &jet_antikt6h1tower_e_EMB3, &b_jet_antikt6h1tower_e_EMB3);
   fChain->SetBranchAddress("jet_antikt6h1tower_e_PreSamplerE", &jet_antikt6h1tower_e_PreSamplerE, &b_jet_antikt6h1tower_e_PreSamplerE);
   fChain->SetBranchAddress("jet_antikt6h1tower_e_EME1", &jet_antikt6h1tower_e_EME1, &b_jet_antikt6h1tower_e_EME1);
   fChain->SetBranchAddress("jet_antikt6h1tower_e_EME2", &jet_antikt6h1tower_e_EME2, &b_jet_antikt6h1tower_e_EME2);
   fChain->SetBranchAddress("jet_antikt6h1tower_e_EME3", &jet_antikt6h1tower_e_EME3, &b_jet_antikt6h1tower_e_EME3);
   fChain->SetBranchAddress("jet_antikt6h1tower_e_HEC0", &jet_antikt6h1tower_e_HEC0, &b_jet_antikt6h1tower_e_HEC0);
   fChain->SetBranchAddress("jet_antikt6h1tower_e_HEC1", &jet_antikt6h1tower_e_HEC1, &b_jet_antikt6h1tower_e_HEC1);
   fChain->SetBranchAddress("jet_antikt6h1tower_e_HEC2", &jet_antikt6h1tower_e_HEC2, &b_jet_antikt6h1tower_e_HEC2);
   fChain->SetBranchAddress("jet_antikt6h1tower_e_HEC3", &jet_antikt6h1tower_e_HEC3, &b_jet_antikt6h1tower_e_HEC3);
   fChain->SetBranchAddress("jet_antikt6h1tower_e_TileBar0", &jet_antikt6h1tower_e_TileBar0, &b_jet_antikt6h1tower_e_TileBar0);
   fChain->SetBranchAddress("jet_antikt6h1tower_e_TileBar1", &jet_antikt6h1tower_e_TileBar1, &b_jet_antikt6h1tower_e_TileBar1);
   fChain->SetBranchAddress("jet_antikt6h1tower_e_TileBar2", &jet_antikt6h1tower_e_TileBar2, &b_jet_antikt6h1tower_e_TileBar2);
   fChain->SetBranchAddress("jet_antikt6h1tower_e_TileGap1", &jet_antikt6h1tower_e_TileGap1, &b_jet_antikt6h1tower_e_TileGap1);
   fChain->SetBranchAddress("jet_antikt6h1tower_e_TileGap2", &jet_antikt6h1tower_e_TileGap2, &b_jet_antikt6h1tower_e_TileGap2);
   fChain->SetBranchAddress("jet_antikt6h1tower_e_TileGap3", &jet_antikt6h1tower_e_TileGap3, &b_jet_antikt6h1tower_e_TileGap3);
   fChain->SetBranchAddress("jet_antikt6h1tower_e_TileExt0", &jet_antikt6h1tower_e_TileExt0, &b_jet_antikt6h1tower_e_TileExt0);
   fChain->SetBranchAddress("jet_antikt6h1tower_e_TileExt1", &jet_antikt6h1tower_e_TileExt1, &b_jet_antikt6h1tower_e_TileExt1);
   fChain->SetBranchAddress("jet_antikt6h1tower_e_TileExt2", &jet_antikt6h1tower_e_TileExt2, &b_jet_antikt6h1tower_e_TileExt2);
   fChain->SetBranchAddress("jet_antikt6h1tower_e_FCAL0", &jet_antikt6h1tower_e_FCAL0, &b_jet_antikt6h1tower_e_FCAL0);
   fChain->SetBranchAddress("jet_antikt6h1tower_e_FCAL1", &jet_antikt6h1tower_e_FCAL1, &b_jet_antikt6h1tower_e_FCAL1);
   fChain->SetBranchAddress("jet_antikt6h1tower_e_FCAL2", &jet_antikt6h1tower_e_FCAL2, &b_jet_antikt6h1tower_e_FCAL2);
   fChain->SetBranchAddress("jet_antikt6h1tower_shapeBins", &jet_antikt6h1tower_shapeBins, &b_jet_antikt6h1tower_shapeBins);
   fChain->SetBranchAddress("jet_antikt6h1tower_flavor_component_ip2d_pu", &jet_antikt6h1tower_flavor_component_ip2d_pu, &b_jet_antikt6h1tower_flavor_component_ip2d_pu);
   fChain->SetBranchAddress("jet_antikt6h1tower_flavor_component_ip2d_pb", &jet_antikt6h1tower_flavor_component_ip2d_pb, &b_jet_antikt6h1tower_flavor_component_ip2d_pb);
   fChain->SetBranchAddress("jet_antikt6h1tower_flavor_component_ip2d_ntrk", &jet_antikt6h1tower_flavor_component_ip2d_ntrk, &b_jet_antikt6h1tower_flavor_component_ip2d_ntrk);
   fChain->SetBranchAddress("jet_antikt6h1tower_flavor_component_ip3d_pu", &jet_antikt6h1tower_flavor_component_ip3d_pu, &b_jet_antikt6h1tower_flavor_component_ip3d_pu);
   fChain->SetBranchAddress("jet_antikt6h1tower_flavor_component_ip3d_pb", &jet_antikt6h1tower_flavor_component_ip3d_pb, &b_jet_antikt6h1tower_flavor_component_ip3d_pb);
   fChain->SetBranchAddress("jet_antikt6h1tower_flavor_component_ip3d_ntrk", &jet_antikt6h1tower_flavor_component_ip3d_ntrk, &b_jet_antikt6h1tower_flavor_component_ip3d_ntrk);
   fChain->SetBranchAddress("jet_antikt6h1tower_flavor_component_sv1_pu", &jet_antikt6h1tower_flavor_component_sv1_pu, &b_jet_antikt6h1tower_flavor_component_sv1_pu);
   fChain->SetBranchAddress("jet_antikt6h1tower_flavor_component_sv1_pb", &jet_antikt6h1tower_flavor_component_sv1_pb, &b_jet_antikt6h1tower_flavor_component_sv1_pb);
   fChain->SetBranchAddress("jet_antikt6h1tower_flavor_component_sv2_pu", &jet_antikt6h1tower_flavor_component_sv2_pu, &b_jet_antikt6h1tower_flavor_component_sv2_pu);
   fChain->SetBranchAddress("jet_antikt6h1tower_flavor_component_sv2_pb", &jet_antikt6h1tower_flavor_component_sv2_pb, &b_jet_antikt6h1tower_flavor_component_sv2_pb);
   fChain->SetBranchAddress("jet_antikt6h1tower_flavor_component_svp_mass", &jet_antikt6h1tower_flavor_component_svp_mass, &b_jet_antikt6h1tower_flavor_component_svp_mass);
   fChain->SetBranchAddress("jet_antikt6h1tower_flavor_component_svp_n2t", &jet_antikt6h1tower_flavor_component_svp_n2t, &b_jet_antikt6h1tower_flavor_component_svp_n2t);
   fChain->SetBranchAddress("jet_antikt6h1tower_flavor_component_svp_svok", &jet_antikt6h1tower_flavor_component_svp_svok, &b_jet_antikt6h1tower_flavor_component_svp_svok);
   fChain->SetBranchAddress("jet_antikt6h1tower_flavor_component_svp_ntrk", &jet_antikt6h1tower_flavor_component_svp_ntrk, &b_jet_antikt6h1tower_flavor_component_svp_ntrk);
   fChain->SetBranchAddress("jet_antikt6h1tower_flavor_component_svp_ntrkv", &jet_antikt6h1tower_flavor_component_svp_ntrkv, &b_jet_antikt6h1tower_flavor_component_svp_ntrkv);
   fChain->SetBranchAddress("jet_antikt6h1tower_flavor_component_svp_ntrkj", &jet_antikt6h1tower_flavor_component_svp_ntrkj, &b_jet_antikt6h1tower_flavor_component_svp_ntrkj);
   fChain->SetBranchAddress("jet_antikt6h1tower_flavor_component_svp_efrc", &jet_antikt6h1tower_flavor_component_svp_efrc, &b_jet_antikt6h1tower_flavor_component_svp_efrc);
   fChain->SetBranchAddress("jet_antikt6h1tower_flavor_component_sv0p_mass", &jet_antikt6h1tower_flavor_component_sv0p_mass, &b_jet_antikt6h1tower_flavor_component_sv0p_mass);
   fChain->SetBranchAddress("jet_antikt6h1tower_flavor_component_sv0p_n2t", &jet_antikt6h1tower_flavor_component_sv0p_n2t, &b_jet_antikt6h1tower_flavor_component_sv0p_n2t);
   fChain->SetBranchAddress("jet_antikt6h1tower_flavor_component_sv0p_svok", &jet_antikt6h1tower_flavor_component_sv0p_svok, &b_jet_antikt6h1tower_flavor_component_sv0p_svok);
   fChain->SetBranchAddress("jet_antikt6h1tower_flavor_component_sv0p_ntrk", &jet_antikt6h1tower_flavor_component_sv0p_ntrk, &b_jet_antikt6h1tower_flavor_component_sv0p_ntrk);
   fChain->SetBranchAddress("jet_antikt6h1tower_flavor_component_sv0p_ntrkv", &jet_antikt6h1tower_flavor_component_sv0p_ntrkv, &b_jet_antikt6h1tower_flavor_component_sv0p_ntrkv);
   fChain->SetBranchAddress("jet_antikt6h1tower_flavor_component_sv0p_ntrkj", &jet_antikt6h1tower_flavor_component_sv0p_ntrkj, &b_jet_antikt6h1tower_flavor_component_sv0p_ntrkj);
   fChain->SetBranchAddress("jet_antikt6h1tower_flavor_component_sv0p_efrc", &jet_antikt6h1tower_flavor_component_sv0p_efrc, &b_jet_antikt6h1tower_flavor_component_sv0p_efrc);
   fChain->SetBranchAddress("jet_antikt6h1tower_flavor_component_jfit_pu", &jet_antikt6h1tower_flavor_component_jfit_pu, &b_jet_antikt6h1tower_flavor_component_jfit_pu);
   fChain->SetBranchAddress("jet_antikt6h1tower_flavor_component_jfit_pb", &jet_antikt6h1tower_flavor_component_jfit_pb, &b_jet_antikt6h1tower_flavor_component_jfit_pb);
   fChain->SetBranchAddress("jet_antikt6h1tower_flavor_component_jfit_nvtxnt", &jet_antikt6h1tower_flavor_component_jfit_nvtxnt, &b_jet_antikt6h1tower_flavor_component_jfit_nvtxnt);
   fChain->SetBranchAddress("jet_antikt6h1tower_flavor_component_jfit_nvtx1t", &jet_antikt6h1tower_flavor_component_jfit_nvtx1t, &b_jet_antikt6h1tower_flavor_component_jfit_nvtx1t);
   fChain->SetBranchAddress("jet_antikt6h1tower_flavor_component_jfit_ntrk", &jet_antikt6h1tower_flavor_component_jfit_ntrk, &b_jet_antikt6h1tower_flavor_component_jfit_ntrk);
   fChain->SetBranchAddress("jet_antikt6h1tower_flavor_component_jfit_efrc", &jet_antikt6h1tower_flavor_component_jfit_efrc, &b_jet_antikt6h1tower_flavor_component_jfit_efrc);
   fChain->SetBranchAddress("jet_antikt6h1tower_flavor_component_jfit_mass", &jet_antikt6h1tower_flavor_component_jfit_mass, &b_jet_antikt6h1tower_flavor_component_jfit_mass);
   fChain->SetBranchAddress("jet_antikt6h1tower_flavor_component_jfit_sig3d", &jet_antikt6h1tower_flavor_component_jfit_sig3d, &b_jet_antikt6h1tower_flavor_component_jfit_sig3d);
   fChain->SetBranchAddress("jet_antikt6h1tower_constscale_E", &jet_antikt6h1tower_constscale_E, &b_jet_antikt6h1tower_constscale_E);
   fChain->SetBranchAddress("jet_antikt6h1tower_constscale_pt", &jet_antikt6h1tower_constscale_pt, &b_jet_antikt6h1tower_constscale_pt);
   fChain->SetBranchAddress("jet_antikt6h1tower_constscale_m", &jet_antikt6h1tower_constscale_m, &b_jet_antikt6h1tower_constscale_m);
   fChain->SetBranchAddress("jet_antikt6h1tower_constscale_eta", &jet_antikt6h1tower_constscale_eta, &b_jet_antikt6h1tower_constscale_eta);
   fChain->SetBranchAddress("jet_antikt6h1tower_constscale_phi", &jet_antikt6h1tower_constscale_phi, &b_jet_antikt6h1tower_constscale_phi);
   fChain->SetBranchAddress("jet_antikt6h1tower_el_dr", &jet_antikt6h1tower_el_dr, &b_jet_antikt6h1tower_el_dr);
   fChain->SetBranchAddress("jet_antikt6h1tower_el_matched", &jet_antikt6h1tower_el_matched, &b_jet_antikt6h1tower_el_matched);
   fChain->SetBranchAddress("jet_antikt6h1tower_mu_dr", &jet_antikt6h1tower_mu_dr, &b_jet_antikt6h1tower_mu_dr);
   fChain->SetBranchAddress("jet_antikt6h1tower_mu_matched", &jet_antikt6h1tower_mu_matched, &b_jet_antikt6h1tower_mu_matched);
   fChain->SetBranchAddress("jet_antikt4lctopo_n", &jet_antikt4lctopo_n, &b_jet_antikt4lctopo_n);
   fChain->SetBranchAddress("jet_antikt4lctopo_E", &jet_antikt4lctopo_E, &b_jet_antikt4lctopo_E);
   fChain->SetBranchAddress("jet_antikt4lctopo_pt", &jet_antikt4lctopo_pt, &b_jet_antikt4lctopo_pt);
   fChain->SetBranchAddress("jet_antikt4lctopo_m", &jet_antikt4lctopo_m, &b_jet_antikt4lctopo_m);
   fChain->SetBranchAddress("jet_antikt4lctopo_eta", &jet_antikt4lctopo_eta, &b_jet_antikt4lctopo_eta);
   fChain->SetBranchAddress("jet_antikt4lctopo_phi", &jet_antikt4lctopo_phi, &b_jet_antikt4lctopo_phi);
   fChain->SetBranchAddress("jet_antikt4lctopo_EtaPhys", &jet_antikt4lctopo_EtaPhys, &b_jet_antikt4lctopo_EtaPhys);
   fChain->SetBranchAddress("jet_antikt4lctopo_PhiPhys", &jet_antikt4lctopo_PhiPhys, &b_jet_antikt4lctopo_PhiPhys);
   fChain->SetBranchAddress("jet_antikt4lctopo_MPhys", &jet_antikt4lctopo_MPhys, &b_jet_antikt4lctopo_MPhys);
   fChain->SetBranchAddress("jet_antikt4lctopo_WIDTH", &jet_antikt4lctopo_WIDTH, &b_jet_antikt4lctopo_WIDTH);
   fChain->SetBranchAddress("jet_antikt4lctopo_n90", &jet_antikt4lctopo_n90, &b_jet_antikt4lctopo_n90);
   fChain->SetBranchAddress("jet_antikt4lctopo_n90constituents", &jet_antikt4lctopo_n90constituents, &b_jet_antikt4lctopo_n90constituents);
   fChain->SetBranchAddress("jet_antikt4lctopo_fracSamplingMax", &jet_antikt4lctopo_fracSamplingMax, &b_jet_antikt4lctopo_fracSamplingMax);
   fChain->SetBranchAddress("jet_antikt4lctopo_SamplingMax", &jet_antikt4lctopo_SamplingMax, &b_jet_antikt4lctopo_SamplingMax);
   fChain->SetBranchAddress("jet_antikt4lctopo_BCH_CORR_CELL", &jet_antikt4lctopo_BCH_CORR_CELL, &b_jet_antikt4lctopo_BCH_CORR_CELL);
   fChain->SetBranchAddress("jet_antikt4lctopo_BCH_CORR_DOTX", &jet_antikt4lctopo_BCH_CORR_DOTX, &b_jet_antikt4lctopo_BCH_CORR_DOTX);
   fChain->SetBranchAddress("jet_antikt4lctopo_BCH_CORR_JET", &jet_antikt4lctopo_BCH_CORR_JET, &b_jet_antikt4lctopo_BCH_CORR_JET);
   fChain->SetBranchAddress("jet_antikt4lctopo_BCH_CORR_JET_FORCELL", &jet_antikt4lctopo_BCH_CORR_JET_FORCELL, &b_jet_antikt4lctopo_BCH_CORR_JET_FORCELL);
   fChain->SetBranchAddress("jet_antikt4lctopo_ENG_BAD_CELLS", &jet_antikt4lctopo_ENG_BAD_CELLS, &b_jet_antikt4lctopo_ENG_BAD_CELLS);
   fChain->SetBranchAddress("jet_antikt4lctopo_N_BAD_CELLS", &jet_antikt4lctopo_N_BAD_CELLS, &b_jet_antikt4lctopo_N_BAD_CELLS);
   fChain->SetBranchAddress("jet_antikt4lctopo_N_BAD_CELLS_CORR", &jet_antikt4lctopo_N_BAD_CELLS_CORR, &b_jet_antikt4lctopo_N_BAD_CELLS_CORR);
   fChain->SetBranchAddress("jet_antikt4lctopo_BAD_CELLS_CORR_E", &jet_antikt4lctopo_BAD_CELLS_CORR_E, &b_jet_antikt4lctopo_BAD_CELLS_CORR_E);
   fChain->SetBranchAddress("jet_antikt4lctopo_hecf", &jet_antikt4lctopo_hecf, &b_jet_antikt4lctopo_hecf);
   fChain->SetBranchAddress("jet_antikt4lctopo_tgap3f", &jet_antikt4lctopo_tgap3f, &b_jet_antikt4lctopo_tgap3f);
   fChain->SetBranchAddress("jet_antikt4lctopo_isGood", &jet_antikt4lctopo_isGood, &b_jet_antikt4lctopo_isGood);
   fChain->SetBranchAddress("jet_antikt4lctopo_timing", &jet_antikt4lctopo_timing, &b_jet_antikt4lctopo_timing);
   fChain->SetBranchAddress("jet_antikt4lctopo_quality", &jet_antikt4lctopo_quality, &b_jet_antikt4lctopo_quality);
   fChain->SetBranchAddress("jet_antikt4lctopo_emfrac", &jet_antikt4lctopo_emfrac, &b_jet_antikt4lctopo_emfrac);
   fChain->SetBranchAddress("jet_antikt4lctopo_GCWJES", &jet_antikt4lctopo_GCWJES, &b_jet_antikt4lctopo_GCWJES);
   fChain->SetBranchAddress("jet_antikt4lctopo_EMJES", &jet_antikt4lctopo_EMJES, &b_jet_antikt4lctopo_EMJES);
   fChain->SetBranchAddress("jet_antikt4lctopo_CB", &jet_antikt4lctopo_CB, &b_jet_antikt4lctopo_CB);
   fChain->SetBranchAddress("jet_antikt4lctopo_emscale_E", &jet_antikt4lctopo_emscale_E, &b_jet_antikt4lctopo_emscale_E);
   fChain->SetBranchAddress("jet_antikt4lctopo_emscale_pt", &jet_antikt4lctopo_emscale_pt, &b_jet_antikt4lctopo_emscale_pt);
   fChain->SetBranchAddress("jet_antikt4lctopo_emscale_m", &jet_antikt4lctopo_emscale_m, &b_jet_antikt4lctopo_emscale_m);
   fChain->SetBranchAddress("jet_antikt4lctopo_emscale_eta", &jet_antikt4lctopo_emscale_eta, &b_jet_antikt4lctopo_emscale_eta);
   fChain->SetBranchAddress("jet_antikt4lctopo_emscale_phi", &jet_antikt4lctopo_emscale_phi, &b_jet_antikt4lctopo_emscale_phi);
   fChain->SetBranchAddress("jet_antikt4lctopo_jvtxf", &jet_antikt4lctopo_jvtxf, &b_jet_antikt4lctopo_jvtxf);
   fChain->SetBranchAddress("jet_antikt4lctopo_jvtx_x", &jet_antikt4lctopo_jvtx_x, &b_jet_antikt4lctopo_jvtx_x);
   fChain->SetBranchAddress("jet_antikt4lctopo_jvtx_y", &jet_antikt4lctopo_jvtx_y, &b_jet_antikt4lctopo_jvtx_y);
   fChain->SetBranchAddress("jet_antikt4lctopo_jvtx_z", &jet_antikt4lctopo_jvtx_z, &b_jet_antikt4lctopo_jvtx_z);
   fChain->SetBranchAddress("jet_antikt4lctopo_flavor_weight", &jet_antikt4lctopo_flavor_weight, &b_jet_antikt4lctopo_flavor_weight);
   fChain->SetBranchAddress("jet_antikt4lctopo_flavor_weight_TrackCounting2D", &jet_antikt4lctopo_flavor_weight_TrackCounting2D, &b_jet_antikt4lctopo_flavor_weight_TrackCounting2D);
   fChain->SetBranchAddress("jet_antikt4lctopo_flavor_weight_JetProb", &jet_antikt4lctopo_flavor_weight_JetProb, &b_jet_antikt4lctopo_flavor_weight_JetProb);
   fChain->SetBranchAddress("jet_antikt4lctopo_flavor_weight_IP1D", &jet_antikt4lctopo_flavor_weight_IP1D, &b_jet_antikt4lctopo_flavor_weight_IP1D);
   fChain->SetBranchAddress("jet_antikt4lctopo_flavor_weight_IP2D", &jet_antikt4lctopo_flavor_weight_IP2D, &b_jet_antikt4lctopo_flavor_weight_IP2D);
   fChain->SetBranchAddress("jet_antikt4lctopo_flavor_weight_IP3D", &jet_antikt4lctopo_flavor_weight_IP3D, &b_jet_antikt4lctopo_flavor_weight_IP3D);
   fChain->SetBranchAddress("jet_antikt4lctopo_flavor_weight_SV0", &jet_antikt4lctopo_flavor_weight_SV0, &b_jet_antikt4lctopo_flavor_weight_SV0);
   fChain->SetBranchAddress("jet_antikt4lctopo_flavor_weight_SV1", &jet_antikt4lctopo_flavor_weight_SV1, &b_jet_antikt4lctopo_flavor_weight_SV1);
   fChain->SetBranchAddress("jet_antikt4lctopo_flavor_weight_SV2", &jet_antikt4lctopo_flavor_weight_SV2, &b_jet_antikt4lctopo_flavor_weight_SV2);
   fChain->SetBranchAddress("jet_antikt4lctopo_flavor_weight_JetFitterTag", &jet_antikt4lctopo_flavor_weight_JetFitterTag, &b_jet_antikt4lctopo_flavor_weight_JetFitterTag);
   fChain->SetBranchAddress("jet_antikt4lctopo_flavor_weight_JetFitterCOMB", &jet_antikt4lctopo_flavor_weight_JetFitterCOMB, &b_jet_antikt4lctopo_flavor_weight_JetFitterCOMB);
   fChain->SetBranchAddress("jet_antikt4lctopo_flavor_weight_JetFitterTagNN", &jet_antikt4lctopo_flavor_weight_JetFitterTagNN, &b_jet_antikt4lctopo_flavor_weight_JetFitterTagNN);
   fChain->SetBranchAddress("jet_antikt4lctopo_flavor_weight_JetFitterCOMBNN", &jet_antikt4lctopo_flavor_weight_JetFitterCOMBNN, &b_jet_antikt4lctopo_flavor_weight_JetFitterCOMBNN);
   fChain->SetBranchAddress("jet_antikt4lctopo_flavor_weight_SoftMuonTag", &jet_antikt4lctopo_flavor_weight_SoftMuonTag, &b_jet_antikt4lctopo_flavor_weight_SoftMuonTag);
   fChain->SetBranchAddress("jet_antikt4lctopo_flavor_weight_SoftElectronTag", &jet_antikt4lctopo_flavor_weight_SoftElectronTag, &b_jet_antikt4lctopo_flavor_weight_SoftElectronTag);
   fChain->SetBranchAddress("jet_antikt4lctopo_e_PreSamplerB", &jet_antikt4lctopo_e_PreSamplerB, &b_jet_antikt4lctopo_e_PreSamplerB);
   fChain->SetBranchAddress("jet_antikt4lctopo_e_EMB1", &jet_antikt4lctopo_e_EMB1, &b_jet_antikt4lctopo_e_EMB1);
   fChain->SetBranchAddress("jet_antikt4lctopo_e_EMB2", &jet_antikt4lctopo_e_EMB2, &b_jet_antikt4lctopo_e_EMB2);
   fChain->SetBranchAddress("jet_antikt4lctopo_e_EMB3", &jet_antikt4lctopo_e_EMB3, &b_jet_antikt4lctopo_e_EMB3);
   fChain->SetBranchAddress("jet_antikt4lctopo_e_PreSamplerE", &jet_antikt4lctopo_e_PreSamplerE, &b_jet_antikt4lctopo_e_PreSamplerE);
   fChain->SetBranchAddress("jet_antikt4lctopo_e_EME1", &jet_antikt4lctopo_e_EME1, &b_jet_antikt4lctopo_e_EME1);
   fChain->SetBranchAddress("jet_antikt4lctopo_e_EME2", &jet_antikt4lctopo_e_EME2, &b_jet_antikt4lctopo_e_EME2);
   fChain->SetBranchAddress("jet_antikt4lctopo_e_EME3", &jet_antikt4lctopo_e_EME3, &b_jet_antikt4lctopo_e_EME3);
   fChain->SetBranchAddress("jet_antikt4lctopo_e_HEC0", &jet_antikt4lctopo_e_HEC0, &b_jet_antikt4lctopo_e_HEC0);
   fChain->SetBranchAddress("jet_antikt4lctopo_e_HEC1", &jet_antikt4lctopo_e_HEC1, &b_jet_antikt4lctopo_e_HEC1);
   fChain->SetBranchAddress("jet_antikt4lctopo_e_HEC2", &jet_antikt4lctopo_e_HEC2, &b_jet_antikt4lctopo_e_HEC2);
   fChain->SetBranchAddress("jet_antikt4lctopo_e_HEC3", &jet_antikt4lctopo_e_HEC3, &b_jet_antikt4lctopo_e_HEC3);
   fChain->SetBranchAddress("jet_antikt4lctopo_e_TileBar0", &jet_antikt4lctopo_e_TileBar0, &b_jet_antikt4lctopo_e_TileBar0);
   fChain->SetBranchAddress("jet_antikt4lctopo_e_TileBar1", &jet_antikt4lctopo_e_TileBar1, &b_jet_antikt4lctopo_e_TileBar1);
   fChain->SetBranchAddress("jet_antikt4lctopo_e_TileBar2", &jet_antikt4lctopo_e_TileBar2, &b_jet_antikt4lctopo_e_TileBar2);
   fChain->SetBranchAddress("jet_antikt4lctopo_e_TileGap1", &jet_antikt4lctopo_e_TileGap1, &b_jet_antikt4lctopo_e_TileGap1);
   fChain->SetBranchAddress("jet_antikt4lctopo_e_TileGap2", &jet_antikt4lctopo_e_TileGap2, &b_jet_antikt4lctopo_e_TileGap2);
   fChain->SetBranchAddress("jet_antikt4lctopo_e_TileGap3", &jet_antikt4lctopo_e_TileGap3, &b_jet_antikt4lctopo_e_TileGap3);
   fChain->SetBranchAddress("jet_antikt4lctopo_e_TileExt0", &jet_antikt4lctopo_e_TileExt0, &b_jet_antikt4lctopo_e_TileExt0);
   fChain->SetBranchAddress("jet_antikt4lctopo_e_TileExt1", &jet_antikt4lctopo_e_TileExt1, &b_jet_antikt4lctopo_e_TileExt1);
   fChain->SetBranchAddress("jet_antikt4lctopo_e_TileExt2", &jet_antikt4lctopo_e_TileExt2, &b_jet_antikt4lctopo_e_TileExt2);
   fChain->SetBranchAddress("jet_antikt4lctopo_e_FCAL0", &jet_antikt4lctopo_e_FCAL0, &b_jet_antikt4lctopo_e_FCAL0);
   fChain->SetBranchAddress("jet_antikt4lctopo_e_FCAL1", &jet_antikt4lctopo_e_FCAL1, &b_jet_antikt4lctopo_e_FCAL1);
   fChain->SetBranchAddress("jet_antikt4lctopo_e_FCAL2", &jet_antikt4lctopo_e_FCAL2, &b_jet_antikt4lctopo_e_FCAL2);
   fChain->SetBranchAddress("jet_antikt4lctopo_shapeBins", &jet_antikt4lctopo_shapeBins, &b_jet_antikt4lctopo_shapeBins);
   fChain->SetBranchAddress("jet_antikt4lctopo_flavor_component_ip2d_pu", &jet_antikt4lctopo_flavor_component_ip2d_pu, &b_jet_antikt4lctopo_flavor_component_ip2d_pu);
   fChain->SetBranchAddress("jet_antikt4lctopo_flavor_component_ip2d_pb", &jet_antikt4lctopo_flavor_component_ip2d_pb, &b_jet_antikt4lctopo_flavor_component_ip2d_pb);
   fChain->SetBranchAddress("jet_antikt4lctopo_flavor_component_ip2d_ntrk", &jet_antikt4lctopo_flavor_component_ip2d_ntrk, &b_jet_antikt4lctopo_flavor_component_ip2d_ntrk);
   fChain->SetBranchAddress("jet_antikt4lctopo_flavor_component_ip3d_pu", &jet_antikt4lctopo_flavor_component_ip3d_pu, &b_jet_antikt4lctopo_flavor_component_ip3d_pu);
   fChain->SetBranchAddress("jet_antikt4lctopo_flavor_component_ip3d_pb", &jet_antikt4lctopo_flavor_component_ip3d_pb, &b_jet_antikt4lctopo_flavor_component_ip3d_pb);
   fChain->SetBranchAddress("jet_antikt4lctopo_flavor_component_ip3d_ntrk", &jet_antikt4lctopo_flavor_component_ip3d_ntrk, &b_jet_antikt4lctopo_flavor_component_ip3d_ntrk);
   fChain->SetBranchAddress("jet_antikt4lctopo_flavor_component_sv1_pu", &jet_antikt4lctopo_flavor_component_sv1_pu, &b_jet_antikt4lctopo_flavor_component_sv1_pu);
   fChain->SetBranchAddress("jet_antikt4lctopo_flavor_component_sv1_pb", &jet_antikt4lctopo_flavor_component_sv1_pb, &b_jet_antikt4lctopo_flavor_component_sv1_pb);
   fChain->SetBranchAddress("jet_antikt4lctopo_flavor_component_sv2_pu", &jet_antikt4lctopo_flavor_component_sv2_pu, &b_jet_antikt4lctopo_flavor_component_sv2_pu);
   fChain->SetBranchAddress("jet_antikt4lctopo_flavor_component_sv2_pb", &jet_antikt4lctopo_flavor_component_sv2_pb, &b_jet_antikt4lctopo_flavor_component_sv2_pb);
   fChain->SetBranchAddress("jet_antikt4lctopo_flavor_component_svp_mass", &jet_antikt4lctopo_flavor_component_svp_mass, &b_jet_antikt4lctopo_flavor_component_svp_mass);
   fChain->SetBranchAddress("jet_antikt4lctopo_flavor_component_svp_n2t", &jet_antikt4lctopo_flavor_component_svp_n2t, &b_jet_antikt4lctopo_flavor_component_svp_n2t);
   fChain->SetBranchAddress("jet_antikt4lctopo_flavor_component_svp_svok", &jet_antikt4lctopo_flavor_component_svp_svok, &b_jet_antikt4lctopo_flavor_component_svp_svok);
   fChain->SetBranchAddress("jet_antikt4lctopo_flavor_component_svp_ntrk", &jet_antikt4lctopo_flavor_component_svp_ntrk, &b_jet_antikt4lctopo_flavor_component_svp_ntrk);
   fChain->SetBranchAddress("jet_antikt4lctopo_flavor_component_svp_ntrkv", &jet_antikt4lctopo_flavor_component_svp_ntrkv, &b_jet_antikt4lctopo_flavor_component_svp_ntrkv);
   fChain->SetBranchAddress("jet_antikt4lctopo_flavor_component_svp_ntrkj", &jet_antikt4lctopo_flavor_component_svp_ntrkj, &b_jet_antikt4lctopo_flavor_component_svp_ntrkj);
   fChain->SetBranchAddress("jet_antikt4lctopo_flavor_component_svp_efrc", &jet_antikt4lctopo_flavor_component_svp_efrc, &b_jet_antikt4lctopo_flavor_component_svp_efrc);
   fChain->SetBranchAddress("jet_antikt4lctopo_flavor_component_sv0p_mass", &jet_antikt4lctopo_flavor_component_sv0p_mass, &b_jet_antikt4lctopo_flavor_component_sv0p_mass);
   fChain->SetBranchAddress("jet_antikt4lctopo_flavor_component_sv0p_n2t", &jet_antikt4lctopo_flavor_component_sv0p_n2t, &b_jet_antikt4lctopo_flavor_component_sv0p_n2t);
   fChain->SetBranchAddress("jet_antikt4lctopo_flavor_component_sv0p_svok", &jet_antikt4lctopo_flavor_component_sv0p_svok, &b_jet_antikt4lctopo_flavor_component_sv0p_svok);
   fChain->SetBranchAddress("jet_antikt4lctopo_flavor_component_sv0p_ntrk", &jet_antikt4lctopo_flavor_component_sv0p_ntrk, &b_jet_antikt4lctopo_flavor_component_sv0p_ntrk);
   fChain->SetBranchAddress("jet_antikt4lctopo_flavor_component_sv0p_ntrkv", &jet_antikt4lctopo_flavor_component_sv0p_ntrkv, &b_jet_antikt4lctopo_flavor_component_sv0p_ntrkv);
   fChain->SetBranchAddress("jet_antikt4lctopo_flavor_component_sv0p_ntrkj", &jet_antikt4lctopo_flavor_component_sv0p_ntrkj, &b_jet_antikt4lctopo_flavor_component_sv0p_ntrkj);
   fChain->SetBranchAddress("jet_antikt4lctopo_flavor_component_sv0p_efrc", &jet_antikt4lctopo_flavor_component_sv0p_efrc, &b_jet_antikt4lctopo_flavor_component_sv0p_efrc);
   fChain->SetBranchAddress("jet_antikt4lctopo_flavor_component_jfit_pu", &jet_antikt4lctopo_flavor_component_jfit_pu, &b_jet_antikt4lctopo_flavor_component_jfit_pu);
   fChain->SetBranchAddress("jet_antikt4lctopo_flavor_component_jfit_pb", &jet_antikt4lctopo_flavor_component_jfit_pb, &b_jet_antikt4lctopo_flavor_component_jfit_pb);
   fChain->SetBranchAddress("jet_antikt4lctopo_flavor_component_jfit_nvtxnt", &jet_antikt4lctopo_flavor_component_jfit_nvtxnt, &b_jet_antikt4lctopo_flavor_component_jfit_nvtxnt);
   fChain->SetBranchAddress("jet_antikt4lctopo_flavor_component_jfit_nvtx1t", &jet_antikt4lctopo_flavor_component_jfit_nvtx1t, &b_jet_antikt4lctopo_flavor_component_jfit_nvtx1t);
   fChain->SetBranchAddress("jet_antikt4lctopo_flavor_component_jfit_ntrk", &jet_antikt4lctopo_flavor_component_jfit_ntrk, &b_jet_antikt4lctopo_flavor_component_jfit_ntrk);
   fChain->SetBranchAddress("jet_antikt4lctopo_flavor_component_jfit_efrc", &jet_antikt4lctopo_flavor_component_jfit_efrc, &b_jet_antikt4lctopo_flavor_component_jfit_efrc);
   fChain->SetBranchAddress("jet_antikt4lctopo_flavor_component_jfit_mass", &jet_antikt4lctopo_flavor_component_jfit_mass, &b_jet_antikt4lctopo_flavor_component_jfit_mass);
   fChain->SetBranchAddress("jet_antikt4lctopo_flavor_component_jfit_sig3d", &jet_antikt4lctopo_flavor_component_jfit_sig3d, &b_jet_antikt4lctopo_flavor_component_jfit_sig3d);
   fChain->SetBranchAddress("jet_antikt4lctopo_constscale_E", &jet_antikt4lctopo_constscale_E, &b_jet_antikt4lctopo_constscale_E);
   fChain->SetBranchAddress("jet_antikt4lctopo_constscale_pt", &jet_antikt4lctopo_constscale_pt, &b_jet_antikt4lctopo_constscale_pt);
   fChain->SetBranchAddress("jet_antikt4lctopo_constscale_m", &jet_antikt4lctopo_constscale_m, &b_jet_antikt4lctopo_constscale_m);
   fChain->SetBranchAddress("jet_antikt4lctopo_constscale_eta", &jet_antikt4lctopo_constscale_eta, &b_jet_antikt4lctopo_constscale_eta);
   fChain->SetBranchAddress("jet_antikt4lctopo_constscale_phi", &jet_antikt4lctopo_constscale_phi, &b_jet_antikt4lctopo_constscale_phi);
   fChain->SetBranchAddress("jet_antikt4lctopo_el_dr", &jet_antikt4lctopo_el_dr, &b_jet_antikt4lctopo_el_dr);
   fChain->SetBranchAddress("jet_antikt4lctopo_el_matched", &jet_antikt4lctopo_el_matched, &b_jet_antikt4lctopo_el_matched);
   fChain->SetBranchAddress("jet_antikt4lctopo_mu_dr", &jet_antikt4lctopo_mu_dr, &b_jet_antikt4lctopo_mu_dr);
   fChain->SetBranchAddress("jet_antikt4lctopo_mu_matched", &jet_antikt4lctopo_mu_matched, &b_jet_antikt4lctopo_mu_matched);
   fChain->SetBranchAddress("jet_antikt6lctopo_n", &jet_antikt6lctopo_n, &b_jet_antikt6lctopo_n);
   fChain->SetBranchAddress("jet_antikt6lctopo_E", &jet_antikt6lctopo_E, &b_jet_antikt6lctopo_E);
   fChain->SetBranchAddress("jet_antikt6lctopo_pt", &jet_antikt6lctopo_pt, &b_jet_antikt6lctopo_pt);
   fChain->SetBranchAddress("jet_antikt6lctopo_m", &jet_antikt6lctopo_m, &b_jet_antikt6lctopo_m);
   fChain->SetBranchAddress("jet_antikt6lctopo_eta", &jet_antikt6lctopo_eta, &b_jet_antikt6lctopo_eta);
   fChain->SetBranchAddress("jet_antikt6lctopo_phi", &jet_antikt6lctopo_phi, &b_jet_antikt6lctopo_phi);
   fChain->SetBranchAddress("jet_antikt6lctopo_EtaPhys", &jet_antikt6lctopo_EtaPhys, &b_jet_antikt6lctopo_EtaPhys);
   fChain->SetBranchAddress("jet_antikt6lctopo_PhiPhys", &jet_antikt6lctopo_PhiPhys, &b_jet_antikt6lctopo_PhiPhys);
   fChain->SetBranchAddress("jet_antikt6lctopo_MPhys", &jet_antikt6lctopo_MPhys, &b_jet_antikt6lctopo_MPhys);
   fChain->SetBranchAddress("jet_antikt6lctopo_WIDTH", &jet_antikt6lctopo_WIDTH, &b_jet_antikt6lctopo_WIDTH);
   fChain->SetBranchAddress("jet_antikt6lctopo_n90", &jet_antikt6lctopo_n90, &b_jet_antikt6lctopo_n90);
   fChain->SetBranchAddress("jet_antikt6lctopo_n90constituents", &jet_antikt6lctopo_n90constituents, &b_jet_antikt6lctopo_n90constituents);
   fChain->SetBranchAddress("jet_antikt6lctopo_fracSamplingMax", &jet_antikt6lctopo_fracSamplingMax, &b_jet_antikt6lctopo_fracSamplingMax);
   fChain->SetBranchAddress("jet_antikt6lctopo_SamplingMax", &jet_antikt6lctopo_SamplingMax, &b_jet_antikt6lctopo_SamplingMax);
   fChain->SetBranchAddress("jet_antikt6lctopo_BCH_CORR_CELL", &jet_antikt6lctopo_BCH_CORR_CELL, &b_jet_antikt6lctopo_BCH_CORR_CELL);
   fChain->SetBranchAddress("jet_antikt6lctopo_BCH_CORR_DOTX", &jet_antikt6lctopo_BCH_CORR_DOTX, &b_jet_antikt6lctopo_BCH_CORR_DOTX);
   fChain->SetBranchAddress("jet_antikt6lctopo_BCH_CORR_JET", &jet_antikt6lctopo_BCH_CORR_JET, &b_jet_antikt6lctopo_BCH_CORR_JET);
   fChain->SetBranchAddress("jet_antikt6lctopo_BCH_CORR_JET_FORCELL", &jet_antikt6lctopo_BCH_CORR_JET_FORCELL, &b_jet_antikt6lctopo_BCH_CORR_JET_FORCELL);
   fChain->SetBranchAddress("jet_antikt6lctopo_ENG_BAD_CELLS", &jet_antikt6lctopo_ENG_BAD_CELLS, &b_jet_antikt6lctopo_ENG_BAD_CELLS);
   fChain->SetBranchAddress("jet_antikt6lctopo_N_BAD_CELLS", &jet_antikt6lctopo_N_BAD_CELLS, &b_jet_antikt6lctopo_N_BAD_CELLS);
   fChain->SetBranchAddress("jet_antikt6lctopo_N_BAD_CELLS_CORR", &jet_antikt6lctopo_N_BAD_CELLS_CORR, &b_jet_antikt6lctopo_N_BAD_CELLS_CORR);
   fChain->SetBranchAddress("jet_antikt6lctopo_BAD_CELLS_CORR_E", &jet_antikt6lctopo_BAD_CELLS_CORR_E, &b_jet_antikt6lctopo_BAD_CELLS_CORR_E);
   fChain->SetBranchAddress("jet_antikt6lctopo_hecf", &jet_antikt6lctopo_hecf, &b_jet_antikt6lctopo_hecf);
   fChain->SetBranchAddress("jet_antikt6lctopo_tgap3f", &jet_antikt6lctopo_tgap3f, &b_jet_antikt6lctopo_tgap3f);
   fChain->SetBranchAddress("jet_antikt6lctopo_isGood", &jet_antikt6lctopo_isGood, &b_jet_antikt6lctopo_isGood);
   fChain->SetBranchAddress("jet_antikt6lctopo_timing", &jet_antikt6lctopo_timing, &b_jet_antikt6lctopo_timing);
   fChain->SetBranchAddress("jet_antikt6lctopo_quality", &jet_antikt6lctopo_quality, &b_jet_antikt6lctopo_quality);
   fChain->SetBranchAddress("jet_antikt6lctopo_emfrac", &jet_antikt6lctopo_emfrac, &b_jet_antikt6lctopo_emfrac);
   fChain->SetBranchAddress("jet_antikt6lctopo_GCWJES", &jet_antikt6lctopo_GCWJES, &b_jet_antikt6lctopo_GCWJES);
   fChain->SetBranchAddress("jet_antikt6lctopo_EMJES", &jet_antikt6lctopo_EMJES, &b_jet_antikt6lctopo_EMJES);
   fChain->SetBranchAddress("jet_antikt6lctopo_CB", &jet_antikt6lctopo_CB, &b_jet_antikt6lctopo_CB);
   fChain->SetBranchAddress("jet_antikt6lctopo_emscale_E", &jet_antikt6lctopo_emscale_E, &b_jet_antikt6lctopo_emscale_E);
   fChain->SetBranchAddress("jet_antikt6lctopo_emscale_pt", &jet_antikt6lctopo_emscale_pt, &b_jet_antikt6lctopo_emscale_pt);
   fChain->SetBranchAddress("jet_antikt6lctopo_emscale_m", &jet_antikt6lctopo_emscale_m, &b_jet_antikt6lctopo_emscale_m);
   fChain->SetBranchAddress("jet_antikt6lctopo_emscale_eta", &jet_antikt6lctopo_emscale_eta, &b_jet_antikt6lctopo_emscale_eta);
   fChain->SetBranchAddress("jet_antikt6lctopo_emscale_phi", &jet_antikt6lctopo_emscale_phi, &b_jet_antikt6lctopo_emscale_phi);
   fChain->SetBranchAddress("jet_antikt6lctopo_jvtxf", &jet_antikt6lctopo_jvtxf, &b_jet_antikt6lctopo_jvtxf);
   fChain->SetBranchAddress("jet_antikt6lctopo_jvtx_x", &jet_antikt6lctopo_jvtx_x, &b_jet_antikt6lctopo_jvtx_x);
   fChain->SetBranchAddress("jet_antikt6lctopo_jvtx_y", &jet_antikt6lctopo_jvtx_y, &b_jet_antikt6lctopo_jvtx_y);
   fChain->SetBranchAddress("jet_antikt6lctopo_jvtx_z", &jet_antikt6lctopo_jvtx_z, &b_jet_antikt6lctopo_jvtx_z);
   fChain->SetBranchAddress("jet_antikt6lctopo_flavor_weight", &jet_antikt6lctopo_flavor_weight, &b_jet_antikt6lctopo_flavor_weight);
   fChain->SetBranchAddress("jet_antikt6lctopo_flavor_weight_TrackCounting2D", &jet_antikt6lctopo_flavor_weight_TrackCounting2D, &b_jet_antikt6lctopo_flavor_weight_TrackCounting2D);
   fChain->SetBranchAddress("jet_antikt6lctopo_flavor_weight_JetProb", &jet_antikt6lctopo_flavor_weight_JetProb, &b_jet_antikt6lctopo_flavor_weight_JetProb);
   fChain->SetBranchAddress("jet_antikt6lctopo_flavor_weight_IP1D", &jet_antikt6lctopo_flavor_weight_IP1D, &b_jet_antikt6lctopo_flavor_weight_IP1D);
   fChain->SetBranchAddress("jet_antikt6lctopo_flavor_weight_IP2D", &jet_antikt6lctopo_flavor_weight_IP2D, &b_jet_antikt6lctopo_flavor_weight_IP2D);
   fChain->SetBranchAddress("jet_antikt6lctopo_flavor_weight_IP3D", &jet_antikt6lctopo_flavor_weight_IP3D, &b_jet_antikt6lctopo_flavor_weight_IP3D);
   fChain->SetBranchAddress("jet_antikt6lctopo_flavor_weight_SV0", &jet_antikt6lctopo_flavor_weight_SV0, &b_jet_antikt6lctopo_flavor_weight_SV0);
   fChain->SetBranchAddress("jet_antikt6lctopo_flavor_weight_SV1", &jet_antikt6lctopo_flavor_weight_SV1, &b_jet_antikt6lctopo_flavor_weight_SV1);
   fChain->SetBranchAddress("jet_antikt6lctopo_flavor_weight_SV2", &jet_antikt6lctopo_flavor_weight_SV2, &b_jet_antikt6lctopo_flavor_weight_SV2);
   fChain->SetBranchAddress("jet_antikt6lctopo_flavor_weight_JetFitterTag", &jet_antikt6lctopo_flavor_weight_JetFitterTag, &b_jet_antikt6lctopo_flavor_weight_JetFitterTag);
   fChain->SetBranchAddress("jet_antikt6lctopo_flavor_weight_JetFitterCOMB", &jet_antikt6lctopo_flavor_weight_JetFitterCOMB, &b_jet_antikt6lctopo_flavor_weight_JetFitterCOMB);
   fChain->SetBranchAddress("jet_antikt6lctopo_flavor_weight_JetFitterTagNN", &jet_antikt6lctopo_flavor_weight_JetFitterTagNN, &b_jet_antikt6lctopo_flavor_weight_JetFitterTagNN);
   fChain->SetBranchAddress("jet_antikt6lctopo_flavor_weight_JetFitterCOMBNN", &jet_antikt6lctopo_flavor_weight_JetFitterCOMBNN, &b_jet_antikt6lctopo_flavor_weight_JetFitterCOMBNN);
   fChain->SetBranchAddress("jet_antikt6lctopo_flavor_weight_SoftMuonTag", &jet_antikt6lctopo_flavor_weight_SoftMuonTag, &b_jet_antikt6lctopo_flavor_weight_SoftMuonTag);
   fChain->SetBranchAddress("jet_antikt6lctopo_flavor_weight_SoftElectronTag", &jet_antikt6lctopo_flavor_weight_SoftElectronTag, &b_jet_antikt6lctopo_flavor_weight_SoftElectronTag);
   fChain->SetBranchAddress("jet_antikt6lctopo_e_PreSamplerB", &jet_antikt6lctopo_e_PreSamplerB, &b_jet_antikt6lctopo_e_PreSamplerB);
   fChain->SetBranchAddress("jet_antikt6lctopo_e_EMB1", &jet_antikt6lctopo_e_EMB1, &b_jet_antikt6lctopo_e_EMB1);
   fChain->SetBranchAddress("jet_antikt6lctopo_e_EMB2", &jet_antikt6lctopo_e_EMB2, &b_jet_antikt6lctopo_e_EMB2);
   fChain->SetBranchAddress("jet_antikt6lctopo_e_EMB3", &jet_antikt6lctopo_e_EMB3, &b_jet_antikt6lctopo_e_EMB3);
   fChain->SetBranchAddress("jet_antikt6lctopo_e_PreSamplerE", &jet_antikt6lctopo_e_PreSamplerE, &b_jet_antikt6lctopo_e_PreSamplerE);
   fChain->SetBranchAddress("jet_antikt6lctopo_e_EME1", &jet_antikt6lctopo_e_EME1, &b_jet_antikt6lctopo_e_EME1);
   fChain->SetBranchAddress("jet_antikt6lctopo_e_EME2", &jet_antikt6lctopo_e_EME2, &b_jet_antikt6lctopo_e_EME2);
   fChain->SetBranchAddress("jet_antikt6lctopo_e_EME3", &jet_antikt6lctopo_e_EME3, &b_jet_antikt6lctopo_e_EME3);
   fChain->SetBranchAddress("jet_antikt6lctopo_e_HEC0", &jet_antikt6lctopo_e_HEC0, &b_jet_antikt6lctopo_e_HEC0);
   fChain->SetBranchAddress("jet_antikt6lctopo_e_HEC1", &jet_antikt6lctopo_e_HEC1, &b_jet_antikt6lctopo_e_HEC1);
   fChain->SetBranchAddress("jet_antikt6lctopo_e_HEC2", &jet_antikt6lctopo_e_HEC2, &b_jet_antikt6lctopo_e_HEC2);
   fChain->SetBranchAddress("jet_antikt6lctopo_e_HEC3", &jet_antikt6lctopo_e_HEC3, &b_jet_antikt6lctopo_e_HEC3);
   fChain->SetBranchAddress("jet_antikt6lctopo_e_TileBar0", &jet_antikt6lctopo_e_TileBar0, &b_jet_antikt6lctopo_e_TileBar0);
   fChain->SetBranchAddress("jet_antikt6lctopo_e_TileBar1", &jet_antikt6lctopo_e_TileBar1, &b_jet_antikt6lctopo_e_TileBar1);
   fChain->SetBranchAddress("jet_antikt6lctopo_e_TileBar2", &jet_antikt6lctopo_e_TileBar2, &b_jet_antikt6lctopo_e_TileBar2);
   fChain->SetBranchAddress("jet_antikt6lctopo_e_TileGap1", &jet_antikt6lctopo_e_TileGap1, &b_jet_antikt6lctopo_e_TileGap1);
   fChain->SetBranchAddress("jet_antikt6lctopo_e_TileGap2", &jet_antikt6lctopo_e_TileGap2, &b_jet_antikt6lctopo_e_TileGap2);
   fChain->SetBranchAddress("jet_antikt6lctopo_e_TileGap3", &jet_antikt6lctopo_e_TileGap3, &b_jet_antikt6lctopo_e_TileGap3);
   fChain->SetBranchAddress("jet_antikt6lctopo_e_TileExt0", &jet_antikt6lctopo_e_TileExt0, &b_jet_antikt6lctopo_e_TileExt0);
   fChain->SetBranchAddress("jet_antikt6lctopo_e_TileExt1", &jet_antikt6lctopo_e_TileExt1, &b_jet_antikt6lctopo_e_TileExt1);
   fChain->SetBranchAddress("jet_antikt6lctopo_e_TileExt2", &jet_antikt6lctopo_e_TileExt2, &b_jet_antikt6lctopo_e_TileExt2);
   fChain->SetBranchAddress("jet_antikt6lctopo_e_FCAL0", &jet_antikt6lctopo_e_FCAL0, &b_jet_antikt6lctopo_e_FCAL0);
   fChain->SetBranchAddress("jet_antikt6lctopo_e_FCAL1", &jet_antikt6lctopo_e_FCAL1, &b_jet_antikt6lctopo_e_FCAL1);
   fChain->SetBranchAddress("jet_antikt6lctopo_e_FCAL2", &jet_antikt6lctopo_e_FCAL2, &b_jet_antikt6lctopo_e_FCAL2);
   fChain->SetBranchAddress("jet_antikt6lctopo_shapeBins", &jet_antikt6lctopo_shapeBins, &b_jet_antikt6lctopo_shapeBins);
   fChain->SetBranchAddress("jet_antikt6lctopo_flavor_component_ip2d_pu", &jet_antikt6lctopo_flavor_component_ip2d_pu, &b_jet_antikt6lctopo_flavor_component_ip2d_pu);
   fChain->SetBranchAddress("jet_antikt6lctopo_flavor_component_ip2d_pb", &jet_antikt6lctopo_flavor_component_ip2d_pb, &b_jet_antikt6lctopo_flavor_component_ip2d_pb);
   fChain->SetBranchAddress("jet_antikt6lctopo_flavor_component_ip2d_ntrk", &jet_antikt6lctopo_flavor_component_ip2d_ntrk, &b_jet_antikt6lctopo_flavor_component_ip2d_ntrk);
   fChain->SetBranchAddress("jet_antikt6lctopo_flavor_component_ip3d_pu", &jet_antikt6lctopo_flavor_component_ip3d_pu, &b_jet_antikt6lctopo_flavor_component_ip3d_pu);
   fChain->SetBranchAddress("jet_antikt6lctopo_flavor_component_ip3d_pb", &jet_antikt6lctopo_flavor_component_ip3d_pb, &b_jet_antikt6lctopo_flavor_component_ip3d_pb);
   fChain->SetBranchAddress("jet_antikt6lctopo_flavor_component_ip3d_ntrk", &jet_antikt6lctopo_flavor_component_ip3d_ntrk, &b_jet_antikt6lctopo_flavor_component_ip3d_ntrk);
   fChain->SetBranchAddress("jet_antikt6lctopo_flavor_component_sv1_pu", &jet_antikt6lctopo_flavor_component_sv1_pu, &b_jet_antikt6lctopo_flavor_component_sv1_pu);
   fChain->SetBranchAddress("jet_antikt6lctopo_flavor_component_sv1_pb", &jet_antikt6lctopo_flavor_component_sv1_pb, &b_jet_antikt6lctopo_flavor_component_sv1_pb);
   fChain->SetBranchAddress("jet_antikt6lctopo_flavor_component_sv2_pu", &jet_antikt6lctopo_flavor_component_sv2_pu, &b_jet_antikt6lctopo_flavor_component_sv2_pu);
   fChain->SetBranchAddress("jet_antikt6lctopo_flavor_component_sv2_pb", &jet_antikt6lctopo_flavor_component_sv2_pb, &b_jet_antikt6lctopo_flavor_component_sv2_pb);
   fChain->SetBranchAddress("jet_antikt6lctopo_flavor_component_svp_mass", &jet_antikt6lctopo_flavor_component_svp_mass, &b_jet_antikt6lctopo_flavor_component_svp_mass);
   fChain->SetBranchAddress("jet_antikt6lctopo_flavor_component_svp_n2t", &jet_antikt6lctopo_flavor_component_svp_n2t, &b_jet_antikt6lctopo_flavor_component_svp_n2t);
   fChain->SetBranchAddress("jet_antikt6lctopo_flavor_component_svp_svok", &jet_antikt6lctopo_flavor_component_svp_svok, &b_jet_antikt6lctopo_flavor_component_svp_svok);
   fChain->SetBranchAddress("jet_antikt6lctopo_flavor_component_svp_ntrk", &jet_antikt6lctopo_flavor_component_svp_ntrk, &b_jet_antikt6lctopo_flavor_component_svp_ntrk);
   fChain->SetBranchAddress("jet_antikt6lctopo_flavor_component_svp_ntrkv", &jet_antikt6lctopo_flavor_component_svp_ntrkv, &b_jet_antikt6lctopo_flavor_component_svp_ntrkv);
   fChain->SetBranchAddress("jet_antikt6lctopo_flavor_component_svp_ntrkj", &jet_antikt6lctopo_flavor_component_svp_ntrkj, &b_jet_antikt6lctopo_flavor_component_svp_ntrkj);
   fChain->SetBranchAddress("jet_antikt6lctopo_flavor_component_svp_efrc", &jet_antikt6lctopo_flavor_component_svp_efrc, &b_jet_antikt6lctopo_flavor_component_svp_efrc);
   fChain->SetBranchAddress("jet_antikt6lctopo_flavor_component_sv0p_mass", &jet_antikt6lctopo_flavor_component_sv0p_mass, &b_jet_antikt6lctopo_flavor_component_sv0p_mass);
   fChain->SetBranchAddress("jet_antikt6lctopo_flavor_component_sv0p_n2t", &jet_antikt6lctopo_flavor_component_sv0p_n2t, &b_jet_antikt6lctopo_flavor_component_sv0p_n2t);
   fChain->SetBranchAddress("jet_antikt6lctopo_flavor_component_sv0p_svok", &jet_antikt6lctopo_flavor_component_sv0p_svok, &b_jet_antikt6lctopo_flavor_component_sv0p_svok);
   fChain->SetBranchAddress("jet_antikt6lctopo_flavor_component_sv0p_ntrk", &jet_antikt6lctopo_flavor_component_sv0p_ntrk, &b_jet_antikt6lctopo_flavor_component_sv0p_ntrk);
   fChain->SetBranchAddress("jet_antikt6lctopo_flavor_component_sv0p_ntrkv", &jet_antikt6lctopo_flavor_component_sv0p_ntrkv, &b_jet_antikt6lctopo_flavor_component_sv0p_ntrkv);
   fChain->SetBranchAddress("jet_antikt6lctopo_flavor_component_sv0p_ntrkj", &jet_antikt6lctopo_flavor_component_sv0p_ntrkj, &b_jet_antikt6lctopo_flavor_component_sv0p_ntrkj);
   fChain->SetBranchAddress("jet_antikt6lctopo_flavor_component_sv0p_efrc", &jet_antikt6lctopo_flavor_component_sv0p_efrc, &b_jet_antikt6lctopo_flavor_component_sv0p_efrc);
   fChain->SetBranchAddress("jet_antikt6lctopo_flavor_component_jfit_pu", &jet_antikt6lctopo_flavor_component_jfit_pu, &b_jet_antikt6lctopo_flavor_component_jfit_pu);
   fChain->SetBranchAddress("jet_antikt6lctopo_flavor_component_jfit_pb", &jet_antikt6lctopo_flavor_component_jfit_pb, &b_jet_antikt6lctopo_flavor_component_jfit_pb);
   fChain->SetBranchAddress("jet_antikt6lctopo_flavor_component_jfit_nvtxnt", &jet_antikt6lctopo_flavor_component_jfit_nvtxnt, &b_jet_antikt6lctopo_flavor_component_jfit_nvtxnt);
   fChain->SetBranchAddress("jet_antikt6lctopo_flavor_component_jfit_nvtx1t", &jet_antikt6lctopo_flavor_component_jfit_nvtx1t, &b_jet_antikt6lctopo_flavor_component_jfit_nvtx1t);
   fChain->SetBranchAddress("jet_antikt6lctopo_flavor_component_jfit_ntrk", &jet_antikt6lctopo_flavor_component_jfit_ntrk, &b_jet_antikt6lctopo_flavor_component_jfit_ntrk);
   fChain->SetBranchAddress("jet_antikt6lctopo_flavor_component_jfit_efrc", &jet_antikt6lctopo_flavor_component_jfit_efrc, &b_jet_antikt6lctopo_flavor_component_jfit_efrc);
   fChain->SetBranchAddress("jet_antikt6lctopo_flavor_component_jfit_mass", &jet_antikt6lctopo_flavor_component_jfit_mass, &b_jet_antikt6lctopo_flavor_component_jfit_mass);
   fChain->SetBranchAddress("jet_antikt6lctopo_flavor_component_jfit_sig3d", &jet_antikt6lctopo_flavor_component_jfit_sig3d, &b_jet_antikt6lctopo_flavor_component_jfit_sig3d);
   fChain->SetBranchAddress("jet_antikt6lctopo_constscale_E", &jet_antikt6lctopo_constscale_E, &b_jet_antikt6lctopo_constscale_E);
   fChain->SetBranchAddress("jet_antikt6lctopo_constscale_pt", &jet_antikt6lctopo_constscale_pt, &b_jet_antikt6lctopo_constscale_pt);
   fChain->SetBranchAddress("jet_antikt6lctopo_constscale_m", &jet_antikt6lctopo_constscale_m, &b_jet_antikt6lctopo_constscale_m);
   fChain->SetBranchAddress("jet_antikt6lctopo_constscale_eta", &jet_antikt6lctopo_constscale_eta, &b_jet_antikt6lctopo_constscale_eta);
   fChain->SetBranchAddress("jet_antikt6lctopo_constscale_phi", &jet_antikt6lctopo_constscale_phi, &b_jet_antikt6lctopo_constscale_phi);
   fChain->SetBranchAddress("jet_antikt6lctopo_el_dr", &jet_antikt6lctopo_el_dr, &b_jet_antikt6lctopo_el_dr);
   fChain->SetBranchAddress("jet_antikt6lctopo_el_matched", &jet_antikt6lctopo_el_matched, &b_jet_antikt6lctopo_el_matched);
   fChain->SetBranchAddress("jet_antikt6lctopo_mu_dr", &jet_antikt6lctopo_mu_dr, &b_jet_antikt6lctopo_mu_dr);
   fChain->SetBranchAddress("jet_antikt6lctopo_mu_matched", &jet_antikt6lctopo_mu_matched, &b_jet_antikt6lctopo_mu_matched);
   fChain->SetBranchAddress("jet_antikt6h1topo_n", &jet_antikt6h1topo_n, &b_jet_antikt6h1topo_n);
   fChain->SetBranchAddress("jet_antikt6h1topo_E", &jet_antikt6h1topo_E, &b_jet_antikt6h1topo_E);
   fChain->SetBranchAddress("jet_antikt6h1topo_pt", &jet_antikt6h1topo_pt, &b_jet_antikt6h1topo_pt);
   fChain->SetBranchAddress("jet_antikt6h1topo_m", &jet_antikt6h1topo_m, &b_jet_antikt6h1topo_m);
   fChain->SetBranchAddress("jet_antikt6h1topo_eta", &jet_antikt6h1topo_eta, &b_jet_antikt6h1topo_eta);
   fChain->SetBranchAddress("jet_antikt6h1topo_phi", &jet_antikt6h1topo_phi, &b_jet_antikt6h1topo_phi);
   fChain->SetBranchAddress("jet_antikt6h1topo_EtaPhys", &jet_antikt6h1topo_EtaPhys, &b_jet_antikt6h1topo_EtaPhys);
   fChain->SetBranchAddress("jet_antikt6h1topo_PhiPhys", &jet_antikt6h1topo_PhiPhys, &b_jet_antikt6h1topo_PhiPhys);
   fChain->SetBranchAddress("jet_antikt6h1topo_MPhys", &jet_antikt6h1topo_MPhys, &b_jet_antikt6h1topo_MPhys);
   fChain->SetBranchAddress("jet_antikt6h1topo_WIDTH", &jet_antikt6h1topo_WIDTH, &b_jet_antikt6h1topo_WIDTH);
   fChain->SetBranchAddress("jet_antikt6h1topo_n90", &jet_antikt6h1topo_n90, &b_jet_antikt6h1topo_n90);
   fChain->SetBranchAddress("jet_antikt6h1topo_n90constituents", &jet_antikt6h1topo_n90constituents, &b_jet_antikt6h1topo_n90constituents);
   fChain->SetBranchAddress("jet_antikt6h1topo_fracSamplingMax", &jet_antikt6h1topo_fracSamplingMax, &b_jet_antikt6h1topo_fracSamplingMax);
   fChain->SetBranchAddress("jet_antikt6h1topo_SamplingMax", &jet_antikt6h1topo_SamplingMax, &b_jet_antikt6h1topo_SamplingMax);
   fChain->SetBranchAddress("jet_antikt6h1topo_BCH_CORR_CELL", &jet_antikt6h1topo_BCH_CORR_CELL, &b_jet_antikt6h1topo_BCH_CORR_CELL);
   fChain->SetBranchAddress("jet_antikt6h1topo_BCH_CORR_DOTX", &jet_antikt6h1topo_BCH_CORR_DOTX, &b_jet_antikt6h1topo_BCH_CORR_DOTX);
   fChain->SetBranchAddress("jet_antikt6h1topo_BCH_CORR_JET", &jet_antikt6h1topo_BCH_CORR_JET, &b_jet_antikt6h1topo_BCH_CORR_JET);
   fChain->SetBranchAddress("jet_antikt6h1topo_BCH_CORR_JET_FORCELL", &jet_antikt6h1topo_BCH_CORR_JET_FORCELL, &b_jet_antikt6h1topo_BCH_CORR_JET_FORCELL);
   fChain->SetBranchAddress("jet_antikt6h1topo_ENG_BAD_CELLS", &jet_antikt6h1topo_ENG_BAD_CELLS, &b_jet_antikt6h1topo_ENG_BAD_CELLS);
   fChain->SetBranchAddress("jet_antikt6h1topo_N_BAD_CELLS", &jet_antikt6h1topo_N_BAD_CELLS, &b_jet_antikt6h1topo_N_BAD_CELLS);
   fChain->SetBranchAddress("jet_antikt6h1topo_N_BAD_CELLS_CORR", &jet_antikt6h1topo_N_BAD_CELLS_CORR, &b_jet_antikt6h1topo_N_BAD_CELLS_CORR);
   fChain->SetBranchAddress("jet_antikt6h1topo_BAD_CELLS_CORR_E", &jet_antikt6h1topo_BAD_CELLS_CORR_E, &b_jet_antikt6h1topo_BAD_CELLS_CORR_E);
   fChain->SetBranchAddress("jet_antikt6h1topo_hecf", &jet_antikt6h1topo_hecf, &b_jet_antikt6h1topo_hecf);
   fChain->SetBranchAddress("jet_antikt6h1topo_tgap3f", &jet_antikt6h1topo_tgap3f, &b_jet_antikt6h1topo_tgap3f);
   fChain->SetBranchAddress("jet_antikt6h1topo_isGood", &jet_antikt6h1topo_isGood, &b_jet_antikt6h1topo_isGood);
   fChain->SetBranchAddress("jet_antikt6h1topo_timing", &jet_antikt6h1topo_timing, &b_jet_antikt6h1topo_timing);
   fChain->SetBranchAddress("jet_antikt6h1topo_quality", &jet_antikt6h1topo_quality, &b_jet_antikt6h1topo_quality);
   fChain->SetBranchAddress("jet_antikt6h1topo_emfrac", &jet_antikt6h1topo_emfrac, &b_jet_antikt6h1topo_emfrac);
   fChain->SetBranchAddress("jet_antikt6h1topo_GCWJES", &jet_antikt6h1topo_GCWJES, &b_jet_antikt6h1topo_GCWJES);
   fChain->SetBranchAddress("jet_antikt6h1topo_EMJES", &jet_antikt6h1topo_EMJES, &b_jet_antikt6h1topo_EMJES);
   fChain->SetBranchAddress("jet_antikt6h1topo_CB", &jet_antikt6h1topo_CB, &b_jet_antikt6h1topo_CB);
   fChain->SetBranchAddress("jet_antikt6h1topo_emscale_E", &jet_antikt6h1topo_emscale_E, &b_jet_antikt6h1topo_emscale_E);
   fChain->SetBranchAddress("jet_antikt6h1topo_emscale_pt", &jet_antikt6h1topo_emscale_pt, &b_jet_antikt6h1topo_emscale_pt);
   fChain->SetBranchAddress("jet_antikt6h1topo_emscale_m", &jet_antikt6h1topo_emscale_m, &b_jet_antikt6h1topo_emscale_m);
   fChain->SetBranchAddress("jet_antikt6h1topo_emscale_eta", &jet_antikt6h1topo_emscale_eta, &b_jet_antikt6h1topo_emscale_eta);
   fChain->SetBranchAddress("jet_antikt6h1topo_emscale_phi", &jet_antikt6h1topo_emscale_phi, &b_jet_antikt6h1topo_emscale_phi);
   fChain->SetBranchAddress("jet_antikt6h1topo_jvtxf", &jet_antikt6h1topo_jvtxf, &b_jet_antikt6h1topo_jvtxf);
   fChain->SetBranchAddress("jet_antikt6h1topo_jvtx_x", &jet_antikt6h1topo_jvtx_x, &b_jet_antikt6h1topo_jvtx_x);
   fChain->SetBranchAddress("jet_antikt6h1topo_jvtx_y", &jet_antikt6h1topo_jvtx_y, &b_jet_antikt6h1topo_jvtx_y);
   fChain->SetBranchAddress("jet_antikt6h1topo_jvtx_z", &jet_antikt6h1topo_jvtx_z, &b_jet_antikt6h1topo_jvtx_z);
   fChain->SetBranchAddress("jet_antikt6h1topo_flavor_weight", &jet_antikt6h1topo_flavor_weight, &b_jet_antikt6h1topo_flavor_weight);
   fChain->SetBranchAddress("jet_antikt6h1topo_flavor_weight_TrackCounting2D", &jet_antikt6h1topo_flavor_weight_TrackCounting2D, &b_jet_antikt6h1topo_flavor_weight_TrackCounting2D);
   fChain->SetBranchAddress("jet_antikt6h1topo_flavor_weight_JetProb", &jet_antikt6h1topo_flavor_weight_JetProb, &b_jet_antikt6h1topo_flavor_weight_JetProb);
   fChain->SetBranchAddress("jet_antikt6h1topo_flavor_weight_IP1D", &jet_antikt6h1topo_flavor_weight_IP1D, &b_jet_antikt6h1topo_flavor_weight_IP1D);
   fChain->SetBranchAddress("jet_antikt6h1topo_flavor_weight_IP2D", &jet_antikt6h1topo_flavor_weight_IP2D, &b_jet_antikt6h1topo_flavor_weight_IP2D);
   fChain->SetBranchAddress("jet_antikt6h1topo_flavor_weight_IP3D", &jet_antikt6h1topo_flavor_weight_IP3D, &b_jet_antikt6h1topo_flavor_weight_IP3D);
   fChain->SetBranchAddress("jet_antikt6h1topo_flavor_weight_SV0", &jet_antikt6h1topo_flavor_weight_SV0, &b_jet_antikt6h1topo_flavor_weight_SV0);
   fChain->SetBranchAddress("jet_antikt6h1topo_flavor_weight_SV1", &jet_antikt6h1topo_flavor_weight_SV1, &b_jet_antikt6h1topo_flavor_weight_SV1);
   fChain->SetBranchAddress("jet_antikt6h1topo_flavor_weight_SV2", &jet_antikt6h1topo_flavor_weight_SV2, &b_jet_antikt6h1topo_flavor_weight_SV2);
   fChain->SetBranchAddress("jet_antikt6h1topo_flavor_weight_JetFitterTag", &jet_antikt6h1topo_flavor_weight_JetFitterTag, &b_jet_antikt6h1topo_flavor_weight_JetFitterTag);
   fChain->SetBranchAddress("jet_antikt6h1topo_flavor_weight_JetFitterCOMB", &jet_antikt6h1topo_flavor_weight_JetFitterCOMB, &b_jet_antikt6h1topo_flavor_weight_JetFitterCOMB);
   fChain->SetBranchAddress("jet_antikt6h1topo_flavor_weight_JetFitterTagNN", &jet_antikt6h1topo_flavor_weight_JetFitterTagNN, &b_jet_antikt6h1topo_flavor_weight_JetFitterTagNN);
   fChain->SetBranchAddress("jet_antikt6h1topo_flavor_weight_JetFitterCOMBNN", &jet_antikt6h1topo_flavor_weight_JetFitterCOMBNN, &b_jet_antikt6h1topo_flavor_weight_JetFitterCOMBNN);
   fChain->SetBranchAddress("jet_antikt6h1topo_flavor_weight_SoftMuonTag", &jet_antikt6h1topo_flavor_weight_SoftMuonTag, &b_jet_antikt6h1topo_flavor_weight_SoftMuonTag);
   fChain->SetBranchAddress("jet_antikt6h1topo_flavor_weight_SoftElectronTag", &jet_antikt6h1topo_flavor_weight_SoftElectronTag, &b_jet_antikt6h1topo_flavor_weight_SoftElectronTag);
   fChain->SetBranchAddress("jet_antikt6h1topo_e_PreSamplerB", &jet_antikt6h1topo_e_PreSamplerB, &b_jet_antikt6h1topo_e_PreSamplerB);
   fChain->SetBranchAddress("jet_antikt6h1topo_e_EMB1", &jet_antikt6h1topo_e_EMB1, &b_jet_antikt6h1topo_e_EMB1);
   fChain->SetBranchAddress("jet_antikt6h1topo_e_EMB2", &jet_antikt6h1topo_e_EMB2, &b_jet_antikt6h1topo_e_EMB2);
   fChain->SetBranchAddress("jet_antikt6h1topo_e_EMB3", &jet_antikt6h1topo_e_EMB3, &b_jet_antikt6h1topo_e_EMB3);
   fChain->SetBranchAddress("jet_antikt6h1topo_e_PreSamplerE", &jet_antikt6h1topo_e_PreSamplerE, &b_jet_antikt6h1topo_e_PreSamplerE);
   fChain->SetBranchAddress("jet_antikt6h1topo_e_EME1", &jet_antikt6h1topo_e_EME1, &b_jet_antikt6h1topo_e_EME1);
   fChain->SetBranchAddress("jet_antikt6h1topo_e_EME2", &jet_antikt6h1topo_e_EME2, &b_jet_antikt6h1topo_e_EME2);
   fChain->SetBranchAddress("jet_antikt6h1topo_e_EME3", &jet_antikt6h1topo_e_EME3, &b_jet_antikt6h1topo_e_EME3);
   fChain->SetBranchAddress("jet_antikt6h1topo_e_HEC0", &jet_antikt6h1topo_e_HEC0, &b_jet_antikt6h1topo_e_HEC0);
   fChain->SetBranchAddress("jet_antikt6h1topo_e_HEC1", &jet_antikt6h1topo_e_HEC1, &b_jet_antikt6h1topo_e_HEC1);
   fChain->SetBranchAddress("jet_antikt6h1topo_e_HEC2", &jet_antikt6h1topo_e_HEC2, &b_jet_antikt6h1topo_e_HEC2);
   fChain->SetBranchAddress("jet_antikt6h1topo_e_HEC3", &jet_antikt6h1topo_e_HEC3, &b_jet_antikt6h1topo_e_HEC3);
   fChain->SetBranchAddress("jet_antikt6h1topo_e_TileBar0", &jet_antikt6h1topo_e_TileBar0, &b_jet_antikt6h1topo_e_TileBar0);
   fChain->SetBranchAddress("jet_antikt6h1topo_e_TileBar1", &jet_antikt6h1topo_e_TileBar1, &b_jet_antikt6h1topo_e_TileBar1);
   fChain->SetBranchAddress("jet_antikt6h1topo_e_TileBar2", &jet_antikt6h1topo_e_TileBar2, &b_jet_antikt6h1topo_e_TileBar2);
   fChain->SetBranchAddress("jet_antikt6h1topo_e_TileGap1", &jet_antikt6h1topo_e_TileGap1, &b_jet_antikt6h1topo_e_TileGap1);
   fChain->SetBranchAddress("jet_antikt6h1topo_e_TileGap2", &jet_antikt6h1topo_e_TileGap2, &b_jet_antikt6h1topo_e_TileGap2);
   fChain->SetBranchAddress("jet_antikt6h1topo_e_TileGap3", &jet_antikt6h1topo_e_TileGap3, &b_jet_antikt6h1topo_e_TileGap3);
   fChain->SetBranchAddress("jet_antikt6h1topo_e_TileExt0", &jet_antikt6h1topo_e_TileExt0, &b_jet_antikt6h1topo_e_TileExt0);
   fChain->SetBranchAddress("jet_antikt6h1topo_e_TileExt1", &jet_antikt6h1topo_e_TileExt1, &b_jet_antikt6h1topo_e_TileExt1);
   fChain->SetBranchAddress("jet_antikt6h1topo_e_TileExt2", &jet_antikt6h1topo_e_TileExt2, &b_jet_antikt6h1topo_e_TileExt2);
   fChain->SetBranchAddress("jet_antikt6h1topo_e_FCAL0", &jet_antikt6h1topo_e_FCAL0, &b_jet_antikt6h1topo_e_FCAL0);
   fChain->SetBranchAddress("jet_antikt6h1topo_e_FCAL1", &jet_antikt6h1topo_e_FCAL1, &b_jet_antikt6h1topo_e_FCAL1);
   fChain->SetBranchAddress("jet_antikt6h1topo_e_FCAL2", &jet_antikt6h1topo_e_FCAL2, &b_jet_antikt6h1topo_e_FCAL2);
   fChain->SetBranchAddress("jet_antikt6h1topo_shapeBins", &jet_antikt6h1topo_shapeBins, &b_jet_antikt6h1topo_shapeBins);
   fChain->SetBranchAddress("jet_antikt6h1topo_flavor_component_ip2d_pu", &jet_antikt6h1topo_flavor_component_ip2d_pu, &b_jet_antikt6h1topo_flavor_component_ip2d_pu);
   fChain->SetBranchAddress("jet_antikt6h1topo_flavor_component_ip2d_pb", &jet_antikt6h1topo_flavor_component_ip2d_pb, &b_jet_antikt6h1topo_flavor_component_ip2d_pb);
   fChain->SetBranchAddress("jet_antikt6h1topo_flavor_component_ip2d_ntrk", &jet_antikt6h1topo_flavor_component_ip2d_ntrk, &b_jet_antikt6h1topo_flavor_component_ip2d_ntrk);
   fChain->SetBranchAddress("jet_antikt6h1topo_flavor_component_ip3d_pu", &jet_antikt6h1topo_flavor_component_ip3d_pu, &b_jet_antikt6h1topo_flavor_component_ip3d_pu);
   fChain->SetBranchAddress("jet_antikt6h1topo_flavor_component_ip3d_pb", &jet_antikt6h1topo_flavor_component_ip3d_pb, &b_jet_antikt6h1topo_flavor_component_ip3d_pb);
   fChain->SetBranchAddress("jet_antikt6h1topo_flavor_component_ip3d_ntrk", &jet_antikt6h1topo_flavor_component_ip3d_ntrk, &b_jet_antikt6h1topo_flavor_component_ip3d_ntrk);
   fChain->SetBranchAddress("jet_antikt6h1topo_flavor_component_sv1_pu", &jet_antikt6h1topo_flavor_component_sv1_pu, &b_jet_antikt6h1topo_flavor_component_sv1_pu);
   fChain->SetBranchAddress("jet_antikt6h1topo_flavor_component_sv1_pb", &jet_antikt6h1topo_flavor_component_sv1_pb, &b_jet_antikt6h1topo_flavor_component_sv1_pb);
   fChain->SetBranchAddress("jet_antikt6h1topo_flavor_component_sv2_pu", &jet_antikt6h1topo_flavor_component_sv2_pu, &b_jet_antikt6h1topo_flavor_component_sv2_pu);
   fChain->SetBranchAddress("jet_antikt6h1topo_flavor_component_sv2_pb", &jet_antikt6h1topo_flavor_component_sv2_pb, &b_jet_antikt6h1topo_flavor_component_sv2_pb);
   fChain->SetBranchAddress("jet_antikt6h1topo_flavor_component_svp_mass", &jet_antikt6h1topo_flavor_component_svp_mass, &b_jet_antikt6h1topo_flavor_component_svp_mass);
   fChain->SetBranchAddress("jet_antikt6h1topo_flavor_component_svp_n2t", &jet_antikt6h1topo_flavor_component_svp_n2t, &b_jet_antikt6h1topo_flavor_component_svp_n2t);
   fChain->SetBranchAddress("jet_antikt6h1topo_flavor_component_svp_svok", &jet_antikt6h1topo_flavor_component_svp_svok, &b_jet_antikt6h1topo_flavor_component_svp_svok);
   fChain->SetBranchAddress("jet_antikt6h1topo_flavor_component_svp_ntrk", &jet_antikt6h1topo_flavor_component_svp_ntrk, &b_jet_antikt6h1topo_flavor_component_svp_ntrk);
   fChain->SetBranchAddress("jet_antikt6h1topo_flavor_component_svp_ntrkv", &jet_antikt6h1topo_flavor_component_svp_ntrkv, &b_jet_antikt6h1topo_flavor_component_svp_ntrkv);
   fChain->SetBranchAddress("jet_antikt6h1topo_flavor_component_svp_ntrkj", &jet_antikt6h1topo_flavor_component_svp_ntrkj, &b_jet_antikt6h1topo_flavor_component_svp_ntrkj);
   fChain->SetBranchAddress("jet_antikt6h1topo_flavor_component_svp_efrc", &jet_antikt6h1topo_flavor_component_svp_efrc, &b_jet_antikt6h1topo_flavor_component_svp_efrc);
   fChain->SetBranchAddress("jet_antikt6h1topo_flavor_component_sv0p_mass", &jet_antikt6h1topo_flavor_component_sv0p_mass, &b_jet_antikt6h1topo_flavor_component_sv0p_mass);
   fChain->SetBranchAddress("jet_antikt6h1topo_flavor_component_sv0p_n2t", &jet_antikt6h1topo_flavor_component_sv0p_n2t, &b_jet_antikt6h1topo_flavor_component_sv0p_n2t);
   fChain->SetBranchAddress("jet_antikt6h1topo_flavor_component_sv0p_svok", &jet_antikt6h1topo_flavor_component_sv0p_svok, &b_jet_antikt6h1topo_flavor_component_sv0p_svok);
   fChain->SetBranchAddress("jet_antikt6h1topo_flavor_component_sv0p_ntrk", &jet_antikt6h1topo_flavor_component_sv0p_ntrk, &b_jet_antikt6h1topo_flavor_component_sv0p_ntrk);
   fChain->SetBranchAddress("jet_antikt6h1topo_flavor_component_sv0p_ntrkv", &jet_antikt6h1topo_flavor_component_sv0p_ntrkv, &b_jet_antikt6h1topo_flavor_component_sv0p_ntrkv);
   fChain->SetBranchAddress("jet_antikt6h1topo_flavor_component_sv0p_ntrkj", &jet_antikt6h1topo_flavor_component_sv0p_ntrkj, &b_jet_antikt6h1topo_flavor_component_sv0p_ntrkj);
   fChain->SetBranchAddress("jet_antikt6h1topo_flavor_component_sv0p_efrc", &jet_antikt6h1topo_flavor_component_sv0p_efrc, &b_jet_antikt6h1topo_flavor_component_sv0p_efrc);
   fChain->SetBranchAddress("jet_antikt6h1topo_flavor_component_jfit_pu", &jet_antikt6h1topo_flavor_component_jfit_pu, &b_jet_antikt6h1topo_flavor_component_jfit_pu);
   fChain->SetBranchAddress("jet_antikt6h1topo_flavor_component_jfit_pb", &jet_antikt6h1topo_flavor_component_jfit_pb, &b_jet_antikt6h1topo_flavor_component_jfit_pb);
   fChain->SetBranchAddress("jet_antikt6h1topo_flavor_component_jfit_nvtxnt", &jet_antikt6h1topo_flavor_component_jfit_nvtxnt, &b_jet_antikt6h1topo_flavor_component_jfit_nvtxnt);
   fChain->SetBranchAddress("jet_antikt6h1topo_flavor_component_jfit_nvtx1t", &jet_antikt6h1topo_flavor_component_jfit_nvtx1t, &b_jet_antikt6h1topo_flavor_component_jfit_nvtx1t);
   fChain->SetBranchAddress("jet_antikt6h1topo_flavor_component_jfit_ntrk", &jet_antikt6h1topo_flavor_component_jfit_ntrk, &b_jet_antikt6h1topo_flavor_component_jfit_ntrk);
   fChain->SetBranchAddress("jet_antikt6h1topo_flavor_component_jfit_efrc", &jet_antikt6h1topo_flavor_component_jfit_efrc, &b_jet_antikt6h1topo_flavor_component_jfit_efrc);
   fChain->SetBranchAddress("jet_antikt6h1topo_flavor_component_jfit_mass", &jet_antikt6h1topo_flavor_component_jfit_mass, &b_jet_antikt6h1topo_flavor_component_jfit_mass);
   fChain->SetBranchAddress("jet_antikt6h1topo_flavor_component_jfit_sig3d", &jet_antikt6h1topo_flavor_component_jfit_sig3d, &b_jet_antikt6h1topo_flavor_component_jfit_sig3d);
   fChain->SetBranchAddress("jet_antikt6h1topo_constscale_E", &jet_antikt6h1topo_constscale_E, &b_jet_antikt6h1topo_constscale_E);
   fChain->SetBranchAddress("jet_antikt6h1topo_constscale_pt", &jet_antikt6h1topo_constscale_pt, &b_jet_antikt6h1topo_constscale_pt);
   fChain->SetBranchAddress("jet_antikt6h1topo_constscale_m", &jet_antikt6h1topo_constscale_m, &b_jet_antikt6h1topo_constscale_m);
   fChain->SetBranchAddress("jet_antikt6h1topo_constscale_eta", &jet_antikt6h1topo_constscale_eta, &b_jet_antikt6h1topo_constscale_eta);
   fChain->SetBranchAddress("jet_antikt6h1topo_constscale_phi", &jet_antikt6h1topo_constscale_phi, &b_jet_antikt6h1topo_constscale_phi);
   fChain->SetBranchAddress("jet_antikt6h1topo_el_dr", &jet_antikt6h1topo_el_dr, &b_jet_antikt6h1topo_el_dr);
   fChain->SetBranchAddress("jet_antikt6h1topo_el_matched", &jet_antikt6h1topo_el_matched, &b_jet_antikt6h1topo_el_matched);
   fChain->SetBranchAddress("jet_antikt6h1topo_mu_dr", &jet_antikt6h1topo_mu_dr, &b_jet_antikt6h1topo_mu_dr);
   fChain->SetBranchAddress("jet_antikt6h1topo_mu_matched", &jet_antikt6h1topo_mu_matched, &b_jet_antikt6h1topo_mu_matched);
   fChain->SetBranchAddress("MET_RefFinal_etx", &MET_RefFinal_etx, &b_MET_RefFinal_etx);
   fChain->SetBranchAddress("MET_RefFinal_ety", &MET_RefFinal_ety, &b_MET_RefFinal_ety);
   fChain->SetBranchAddress("MET_RefFinal_sumet", &MET_RefFinal_sumet, &b_MET_RefFinal_sumet);
   fChain->SetBranchAddress("MET_RefFinal_et", &MET_RefFinal_et, &b_MET_RefFinal_et);
   fChain->SetBranchAddress("MET_RefFinal_phi", &MET_RefFinal_phi, &b_MET_RefFinal_phi);
   fChain->SetBranchAddress("MET_MuonBoy_etx", &MET_MuonBoy_etx, &b_MET_MuonBoy_etx);
   fChain->SetBranchAddress("MET_MuonBoy_ety", &MET_MuonBoy_ety, &b_MET_MuonBoy_ety);
   fChain->SetBranchAddress("MET_MuonBoy_sumet", &MET_MuonBoy_sumet, &b_MET_MuonBoy_sumet);
   fChain->SetBranchAddress("MET_MuonBoy_et", &MET_MuonBoy_et, &b_MET_MuonBoy_et);
   fChain->SetBranchAddress("MET_MuonBoy_phi", &MET_MuonBoy_phi, &b_MET_MuonBoy_phi);
   fChain->SetBranchAddress("MET_Track_etx", &MET_Track_etx, &b_MET_Track_etx);
   fChain->SetBranchAddress("MET_Track_ety", &MET_Track_ety, &b_MET_Track_ety);
   fChain->SetBranchAddress("MET_Track_sumet", &MET_Track_sumet, &b_MET_Track_sumet);
   fChain->SetBranchAddress("MET_Track_et", &MET_Track_et, &b_MET_Track_et);
   fChain->SetBranchAddress("MET_Track_phi", &MET_Track_phi, &b_MET_Track_phi);
   fChain->SetBranchAddress("MET_RefGamma_etx", &MET_RefGamma_etx, &b_MET_RefGamma_etx);
   fChain->SetBranchAddress("MET_RefGamma_ety", &MET_RefGamma_ety, &b_MET_RefGamma_ety);
   fChain->SetBranchAddress("MET_RefGamma_sumet", &MET_RefGamma_sumet, &b_MET_RefGamma_sumet);
   fChain->SetBranchAddress("MET_RefGamma_et", &MET_RefGamma_et, &b_MET_RefGamma_et);
   fChain->SetBranchAddress("MET_RefGamma_phi", &MET_RefGamma_phi, &b_MET_RefGamma_phi);
   fChain->SetBranchAddress("MET_RefEle_etx", &MET_RefEle_etx, &b_MET_RefEle_etx);
   fChain->SetBranchAddress("MET_RefEle_ety", &MET_RefEle_ety, &b_MET_RefEle_ety);
   fChain->SetBranchAddress("MET_RefEle_sumet", &MET_RefEle_sumet, &b_MET_RefEle_sumet);
   fChain->SetBranchAddress("MET_RefEle_et", &MET_RefEle_et, &b_MET_RefEle_et);
   fChain->SetBranchAddress("MET_RefEle_phi", &MET_RefEle_phi, &b_MET_RefEle_phi);
   fChain->SetBranchAddress("MET_RefJet_etx", &MET_RefJet_etx, &b_MET_RefJet_etx);
   fChain->SetBranchAddress("MET_RefJet_ety", &MET_RefJet_ety, &b_MET_RefJet_ety);
   fChain->SetBranchAddress("MET_RefJet_sumet", &MET_RefJet_sumet, &b_MET_RefJet_sumet);
   fChain->SetBranchAddress("MET_RefJet_et", &MET_RefJet_et, &b_MET_RefJet_et);
   fChain->SetBranchAddress("MET_RefJet_phi", &MET_RefJet_phi, &b_MET_RefJet_phi);
   fChain->SetBranchAddress("MET_RefMuon_etx", &MET_RefMuon_etx, &b_MET_RefMuon_etx);
   fChain->SetBranchAddress("MET_RefMuon_ety", &MET_RefMuon_ety, &b_MET_RefMuon_ety);
   fChain->SetBranchAddress("MET_RefMuon_sumet", &MET_RefMuon_sumet, &b_MET_RefMuon_sumet);
   fChain->SetBranchAddress("MET_RefMuon_et", &MET_RefMuon_et, &b_MET_RefMuon_et);
   fChain->SetBranchAddress("MET_RefMuon_phi", &MET_RefMuon_phi, &b_MET_RefMuon_phi);
   fChain->SetBranchAddress("MET_RefTau_etx", &MET_RefTau_etx, &b_MET_RefTau_etx);
   fChain->SetBranchAddress("MET_RefTau_ety", &MET_RefTau_ety, &b_MET_RefTau_ety);
   fChain->SetBranchAddress("MET_RefTau_sumet", &MET_RefTau_sumet, &b_MET_RefTau_sumet);
   fChain->SetBranchAddress("MET_RefTau_et", &MET_RefTau_et, &b_MET_RefTau_et);
   fChain->SetBranchAddress("MET_RefTau_phi", &MET_RefTau_phi, &b_MET_RefTau_phi);
   fChain->SetBranchAddress("MET_Cryo_etx", &MET_Cryo_etx, &b_MET_Cryo_etx);
   fChain->SetBranchAddress("MET_Cryo_ety", &MET_Cryo_ety, &b_MET_Cryo_ety);
   fChain->SetBranchAddress("MET_Cryo_sumet", &MET_Cryo_sumet, &b_MET_Cryo_sumet);
   fChain->SetBranchAddress("MET_Cryo_et", &MET_Cryo_et, &b_MET_Cryo_et);
   fChain->SetBranchAddress("MET_Cryo_phi", &MET_Cryo_phi, &b_MET_Cryo_phi);
   fChain->SetBranchAddress("MET_CellOut_etx", &MET_CellOut_etx, &b_MET_CellOut_etx);
   fChain->SetBranchAddress("MET_CellOut_ety", &MET_CellOut_ety, &b_MET_CellOut_ety);
   fChain->SetBranchAddress("MET_CellOut_sumet", &MET_CellOut_sumet, &b_MET_CellOut_sumet);
   fChain->SetBranchAddress("MET_CellOut_et", &MET_CellOut_et, &b_MET_CellOut_et);
   fChain->SetBranchAddress("MET_CellOut_phi", &MET_CellOut_phi, &b_MET_CellOut_phi);
   fChain->SetBranchAddress("MET_Muid_etx", &MET_Muid_etx, &b_MET_Muid_etx);
   fChain->SetBranchAddress("MET_Muid_ety", &MET_Muid_ety, &b_MET_Muid_ety);
   fChain->SetBranchAddress("MET_Muid_sumet", &MET_Muid_sumet, &b_MET_Muid_sumet);
   fChain->SetBranchAddress("MET_Muid_et", &MET_Muid_et, &b_MET_Muid_et);
   fChain->SetBranchAddress("MET_Muid_phi", &MET_Muid_phi, &b_MET_Muid_phi);
   fChain->SetBranchAddress("MET_MuonBoyTrack_etx", &MET_MuonBoyTrack_etx, &b_MET_MuonBoyTrack_etx);
   fChain->SetBranchAddress("MET_MuonBoyTrack_ety", &MET_MuonBoyTrack_ety, &b_MET_MuonBoyTrack_ety);
   fChain->SetBranchAddress("MET_MuonBoyTrack_sumet", &MET_MuonBoyTrack_sumet, &b_MET_MuonBoyTrack_sumet);
   fChain->SetBranchAddress("MET_MuonBoyTrack_et", &MET_MuonBoyTrack_et, &b_MET_MuonBoyTrack_et);
   fChain->SetBranchAddress("MET_MuonBoyTrack_phi", &MET_MuonBoyTrack_phi, &b_MET_MuonBoyTrack_phi);
   fChain->SetBranchAddress("MET_MuonBoySpectro_etx", &MET_MuonBoySpectro_etx, &b_MET_MuonBoySpectro_etx);
   fChain->SetBranchAddress("MET_MuonBoySpectro_ety", &MET_MuonBoySpectro_ety, &b_MET_MuonBoySpectro_ety);
   fChain->SetBranchAddress("MET_MuonBoySpectro_sumet", &MET_MuonBoySpectro_sumet, &b_MET_MuonBoySpectro_sumet);
   fChain->SetBranchAddress("MET_MuonBoySpectro_et", &MET_MuonBoySpectro_et, &b_MET_MuonBoySpectro_et);
   fChain->SetBranchAddress("MET_MuonBoySpectro_phi", &MET_MuonBoySpectro_phi, &b_MET_MuonBoySpectro_phi);
   fChain->SetBranchAddress("MET_RefMuonTrack_etx", &MET_RefMuonTrack_etx, &b_MET_RefMuonTrack_etx);
   fChain->SetBranchAddress("MET_RefMuonTrack_ety", &MET_RefMuonTrack_ety, &b_MET_RefMuonTrack_ety);
   fChain->SetBranchAddress("MET_RefMuonTrack_sumet", &MET_RefMuonTrack_sumet, &b_MET_RefMuonTrack_sumet);
   fChain->SetBranchAddress("MET_RefMuonTrack_et", &MET_RefMuonTrack_et, &b_MET_RefMuonTrack_et);
   fChain->SetBranchAddress("MET_RefMuonTrack_phi", &MET_RefMuonTrack_phi, &b_MET_RefMuonTrack_phi);
   fChain->SetBranchAddress("MET_CryoCone_etx", &MET_CryoCone_etx, &b_MET_CryoCone_etx);
   fChain->SetBranchAddress("MET_CryoCone_ety", &MET_CryoCone_ety, &b_MET_CryoCone_ety);
   fChain->SetBranchAddress("MET_CryoCone_sumet", &MET_CryoCone_sumet, &b_MET_CryoCone_sumet);
   fChain->SetBranchAddress("MET_CryoCone_et", &MET_CryoCone_et, &b_MET_CryoCone_et);
   fChain->SetBranchAddress("MET_CryoCone_phi", &MET_CryoCone_phi, &b_MET_CryoCone_phi);
   fChain->SetBranchAddress("MET_Muon_etx", &MET_Muon_etx, &b_MET_Muon_etx);
   fChain->SetBranchAddress("MET_Muon_ety", &MET_Muon_ety, &b_MET_Muon_ety);
   fChain->SetBranchAddress("MET_Muon_sumet", &MET_Muon_sumet, &b_MET_Muon_sumet);
   fChain->SetBranchAddress("MET_Muon_et", &MET_Muon_et, &b_MET_Muon_et);
   fChain->SetBranchAddress("MET_Muon_phi", &MET_Muon_phi, &b_MET_Muon_phi);
   fChain->SetBranchAddress("MET_Final_etx", &MET_Final_etx, &b_MET_Final_etx);
   fChain->SetBranchAddress("MET_Final_ety", &MET_Final_ety, &b_MET_Final_ety);
   fChain->SetBranchAddress("MET_Final_sumet", &MET_Final_sumet, &b_MET_Final_sumet);
   fChain->SetBranchAddress("MET_Final_et", &MET_Final_et, &b_MET_Final_et);
   fChain->SetBranchAddress("MET_Final_phi", &MET_Final_phi, &b_MET_Final_phi);
   fChain->SetBranchAddress("MET_MuidTrack_etx", &MET_MuidTrack_etx, &b_MET_MuidTrack_etx);
   fChain->SetBranchAddress("MET_MuidTrack_ety", &MET_MuidTrack_ety, &b_MET_MuidTrack_ety);
   fChain->SetBranchAddress("MET_MuidTrack_sumet", &MET_MuidTrack_sumet, &b_MET_MuidTrack_sumet);
   fChain->SetBranchAddress("MET_MuidTrack_et", &MET_MuidTrack_et, &b_MET_MuidTrack_et);
   fChain->SetBranchAddress("MET_MuidTrack_phi", &MET_MuidTrack_phi, &b_MET_MuidTrack_phi);
   fChain->SetBranchAddress("MET_MuidSpectro_etx", &MET_MuidSpectro_etx, &b_MET_MuidSpectro_etx);
   fChain->SetBranchAddress("MET_MuidSpectro_ety", &MET_MuidSpectro_ety, &b_MET_MuidSpectro_ety);
   fChain->SetBranchAddress("MET_MuidSpectro_sumet", &MET_MuidSpectro_sumet, &b_MET_MuidSpectro_sumet);
   fChain->SetBranchAddress("MET_MuidSpectro_et", &MET_MuidSpectro_et, &b_MET_MuidSpectro_et);
   fChain->SetBranchAddress("MET_MuidSpectro_phi", &MET_MuidSpectro_phi, &b_MET_MuidSpectro_phi);
   fChain->SetBranchAddress("MET_MuonMuid_etx", &MET_MuonMuid_etx, &b_MET_MuonMuid_etx);
   fChain->SetBranchAddress("MET_MuonMuid_ety", &MET_MuonMuid_ety, &b_MET_MuonMuid_ety);
   fChain->SetBranchAddress("MET_MuonMuid_sumet", &MET_MuonMuid_sumet, &b_MET_MuonMuid_sumet);
   fChain->SetBranchAddress("MET_MuonMuid_et", &MET_MuonMuid_et, &b_MET_MuonMuid_et);
   fChain->SetBranchAddress("MET_MuonMuid_phi", &MET_MuonMuid_phi, &b_MET_MuonMuid_phi);
   fChain->SetBranchAddress("MET_TopoObj_etx", &MET_TopoObj_etx, &b_MET_TopoObj_etx);
   fChain->SetBranchAddress("MET_TopoObj_ety", &MET_TopoObj_ety, &b_MET_TopoObj_ety);
   fChain->SetBranchAddress("MET_TopoObj_sumet", &MET_TopoObj_sumet, &b_MET_TopoObj_sumet);
   fChain->SetBranchAddress("MET_TopoObj_et", &MET_TopoObj_et, &b_MET_TopoObj_et);
   fChain->SetBranchAddress("MET_TopoObj_phi", &MET_TopoObj_phi, &b_MET_TopoObj_phi);
   fChain->SetBranchAddress("MET_LocHadTopoObj_etx", &MET_LocHadTopoObj_etx, &b_MET_LocHadTopoObj_etx);
   fChain->SetBranchAddress("MET_LocHadTopoObj_ety", &MET_LocHadTopoObj_ety, &b_MET_LocHadTopoObj_ety);
   fChain->SetBranchAddress("MET_LocHadTopoObj_sumet", &MET_LocHadTopoObj_sumet, &b_MET_LocHadTopoObj_sumet);
   fChain->SetBranchAddress("MET_LocHadTopoObj_et", &MET_LocHadTopoObj_et, &b_MET_LocHadTopoObj_et);
   fChain->SetBranchAddress("MET_LocHadTopoObj_phi", &MET_LocHadTopoObj_phi, &b_MET_LocHadTopoObj_phi);
   fChain->SetBranchAddress("MET_Base_etx", &MET_Base_etx, &b_MET_Base_etx);
   fChain->SetBranchAddress("MET_Base_ety", &MET_Base_ety, &b_MET_Base_ety);
   fChain->SetBranchAddress("MET_Base_sumet", &MET_Base_sumet, &b_MET_Base_sumet);
   fChain->SetBranchAddress("MET_Base_et", &MET_Base_et, &b_MET_Base_et);
   fChain->SetBranchAddress("MET_Base_phi", &MET_Base_phi, &b_MET_Base_phi);
   fChain->SetBranchAddress("MET_Base_etx_PEMB", &MET_Base_etx_PEMB, &b_MET_Base_etx_PEMB);
   fChain->SetBranchAddress("MET_Base_ety_PEMB", &MET_Base_ety_PEMB, &b_MET_Base_ety_PEMB);
   fChain->SetBranchAddress("MET_Base_sumet_PEMB", &MET_Base_sumet_PEMB, &b_MET_Base_sumet_PEMB);
   fChain->SetBranchAddress("MET_Base_phi_PEMB", &MET_Base_phi_PEMB, &b_MET_Base_phi_PEMB);
   fChain->SetBranchAddress("MET_Base_etx_EMB", &MET_Base_etx_EMB, &b_MET_Base_etx_EMB);
   fChain->SetBranchAddress("MET_Base_ety_EMB", &MET_Base_ety_EMB, &b_MET_Base_ety_EMB);
   fChain->SetBranchAddress("MET_Base_sumet_EMB", &MET_Base_sumet_EMB, &b_MET_Base_sumet_EMB);
   fChain->SetBranchAddress("MET_Base_phi_EMB", &MET_Base_phi_EMB, &b_MET_Base_phi_EMB);
   fChain->SetBranchAddress("MET_Base_etx_PEMEC", &MET_Base_etx_PEMEC, &b_MET_Base_etx_PEMEC);
   fChain->SetBranchAddress("MET_Base_ety_PEMEC", &MET_Base_ety_PEMEC, &b_MET_Base_ety_PEMEC);
   fChain->SetBranchAddress("MET_Base_sumet_PEMEC", &MET_Base_sumet_PEMEC, &b_MET_Base_sumet_PEMEC);
   fChain->SetBranchAddress("MET_Base_phi_PEMEC", &MET_Base_phi_PEMEC, &b_MET_Base_phi_PEMEC);
   fChain->SetBranchAddress("MET_Base_etx_EME", &MET_Base_etx_EME, &b_MET_Base_etx_EME);
   fChain->SetBranchAddress("MET_Base_ety_EME", &MET_Base_ety_EME, &b_MET_Base_ety_EME);
   fChain->SetBranchAddress("MET_Base_sumet_EME", &MET_Base_sumet_EME, &b_MET_Base_sumet_EME);
   fChain->SetBranchAddress("MET_Base_phi_EME", &MET_Base_phi_EME, &b_MET_Base_phi_EME);
   fChain->SetBranchAddress("MET_Base_etx_TILE", &MET_Base_etx_TILE, &b_MET_Base_etx_TILE);
   fChain->SetBranchAddress("MET_Base_ety_TILE", &MET_Base_ety_TILE, &b_MET_Base_ety_TILE);
   fChain->SetBranchAddress("MET_Base_sumet_TILE", &MET_Base_sumet_TILE, &b_MET_Base_sumet_TILE);
   fChain->SetBranchAddress("MET_Base_phi_TILE", &MET_Base_phi_TILE, &b_MET_Base_phi_TILE);
   fChain->SetBranchAddress("MET_Base_etx_HEC", &MET_Base_etx_HEC, &b_MET_Base_etx_HEC);
   fChain->SetBranchAddress("MET_Base_ety_HEC", &MET_Base_ety_HEC, &b_MET_Base_ety_HEC);
   fChain->SetBranchAddress("MET_Base_sumet_HEC", &MET_Base_sumet_HEC, &b_MET_Base_sumet_HEC);
   fChain->SetBranchAddress("MET_Base_phi_HEC", &MET_Base_phi_HEC, &b_MET_Base_phi_HEC);
   fChain->SetBranchAddress("MET_Base_etx_FCAL", &MET_Base_etx_FCAL, &b_MET_Base_etx_FCAL);
   fChain->SetBranchAddress("MET_Base_ety_FCAL", &MET_Base_ety_FCAL, &b_MET_Base_ety_FCAL);
   fChain->SetBranchAddress("MET_Base_sumet_FCAL", &MET_Base_sumet_FCAL, &b_MET_Base_sumet_FCAL);
   fChain->SetBranchAddress("MET_Base_phi_FCAL", &MET_Base_phi_FCAL, &b_MET_Base_phi_FCAL);
   fChain->SetBranchAddress("MET_Base_nCell_PEMB", &MET_Base_nCell_PEMB, &b_MET_Base_nCell_PEMB);
   fChain->SetBranchAddress("MET_Base_nCell_EMB", &MET_Base_nCell_EMB, &b_MET_Base_nCell_EMB);
   fChain->SetBranchAddress("MET_Base_nCell_PEMEC", &MET_Base_nCell_PEMEC, &b_MET_Base_nCell_PEMEC);
   fChain->SetBranchAddress("MET_Base_nCell_EME", &MET_Base_nCell_EME, &b_MET_Base_nCell_EME);
   fChain->SetBranchAddress("MET_Base_nCell_TILE", &MET_Base_nCell_TILE, &b_MET_Base_nCell_TILE);
   fChain->SetBranchAddress("MET_Base_nCell_HEC", &MET_Base_nCell_HEC, &b_MET_Base_nCell_HEC);
   fChain->SetBranchAddress("MET_Base_nCell_FCAL", &MET_Base_nCell_FCAL, &b_MET_Base_nCell_FCAL);
   fChain->SetBranchAddress("MET_Base_etx_CentralReg", &MET_Base_etx_CentralReg, &b_MET_Base_etx_CentralReg);
   fChain->SetBranchAddress("MET_Base_ety_CentralReg", &MET_Base_ety_CentralReg, &b_MET_Base_ety_CentralReg);
   fChain->SetBranchAddress("MET_Base_sumet_CentralReg", &MET_Base_sumet_CentralReg, &b_MET_Base_sumet_CentralReg);
   fChain->SetBranchAddress("MET_Base_phi_CentralReg", &MET_Base_phi_CentralReg, &b_MET_Base_phi_CentralReg);
   fChain->SetBranchAddress("MET_Base_etx_EndcapRegion", &MET_Base_etx_EndcapRegion, &b_MET_Base_etx_EndcapRegion);
   fChain->SetBranchAddress("MET_Base_ety_EndcapRegion", &MET_Base_ety_EndcapRegion, &b_MET_Base_ety_EndcapRegion);
   fChain->SetBranchAddress("MET_Base_sumet_EndcapRegion", &MET_Base_sumet_EndcapRegion, &b_MET_Base_sumet_EndcapRegion);
   fChain->SetBranchAddress("MET_Base_phi_EndcapRegion", &MET_Base_phi_EndcapRegion, &b_MET_Base_phi_EndcapRegion);
   fChain->SetBranchAddress("MET_Base_etx_ForwardReg", &MET_Base_etx_ForwardReg, &b_MET_Base_etx_ForwardReg);
   fChain->SetBranchAddress("MET_Base_ety_ForwardReg", &MET_Base_ety_ForwardReg, &b_MET_Base_ety_ForwardReg);
   fChain->SetBranchAddress("MET_Base_sumet_ForwardReg", &MET_Base_sumet_ForwardReg, &b_MET_Base_sumet_ForwardReg);
   fChain->SetBranchAddress("MET_Base_phi_ForwardReg", &MET_Base_phi_ForwardReg, &b_MET_Base_phi_ForwardReg);
   fChain->SetBranchAddress("MET_Base_SUMET_EMFrac", &MET_Base_SUMET_EMFrac, &b_MET_Base_SUMET_EMFrac);
   fChain->SetBranchAddress("MET_Base0_etx", &MET_Base0_etx, &b_MET_Base0_etx);
   fChain->SetBranchAddress("MET_Base0_ety", &MET_Base0_ety, &b_MET_Base0_ety);
   fChain->SetBranchAddress("MET_Base0_sumet", &MET_Base0_sumet, &b_MET_Base0_sumet);
   fChain->SetBranchAddress("MET_Base0_et", &MET_Base0_et, &b_MET_Base0_et);
   fChain->SetBranchAddress("MET_Base0_phi", &MET_Base0_phi, &b_MET_Base0_phi);
   fChain->SetBranchAddress("MET_Base0_etx_PEMB", &MET_Base0_etx_PEMB, &b_MET_Base0_etx_PEMB);
   fChain->SetBranchAddress("MET_Base0_ety_PEMB", &MET_Base0_ety_PEMB, &b_MET_Base0_ety_PEMB);
   fChain->SetBranchAddress("MET_Base0_sumet_PEMB", &MET_Base0_sumet_PEMB, &b_MET_Base0_sumet_PEMB);
   fChain->SetBranchAddress("MET_Base0_phi_PEMB", &MET_Base0_phi_PEMB, &b_MET_Base0_phi_PEMB);
   fChain->SetBranchAddress("MET_Base0_etx_EMB", &MET_Base0_etx_EMB, &b_MET_Base0_etx_EMB);
   fChain->SetBranchAddress("MET_Base0_ety_EMB", &MET_Base0_ety_EMB, &b_MET_Base0_ety_EMB);
   fChain->SetBranchAddress("MET_Base0_sumet_EMB", &MET_Base0_sumet_EMB, &b_MET_Base0_sumet_EMB);
   fChain->SetBranchAddress("MET_Base0_phi_EMB", &MET_Base0_phi_EMB, &b_MET_Base0_phi_EMB);
   fChain->SetBranchAddress("MET_Base0_etx_PEMEC", &MET_Base0_etx_PEMEC, &b_MET_Base0_etx_PEMEC);
   fChain->SetBranchAddress("MET_Base0_ety_PEMEC", &MET_Base0_ety_PEMEC, &b_MET_Base0_ety_PEMEC);
   fChain->SetBranchAddress("MET_Base0_sumet_PEMEC", &MET_Base0_sumet_PEMEC, &b_MET_Base0_sumet_PEMEC);
   fChain->SetBranchAddress("MET_Base0_phi_PEMEC", &MET_Base0_phi_PEMEC, &b_MET_Base0_phi_PEMEC);
   fChain->SetBranchAddress("MET_Base0_etx_EME", &MET_Base0_etx_EME, &b_MET_Base0_etx_EME);
   fChain->SetBranchAddress("MET_Base0_ety_EME", &MET_Base0_ety_EME, &b_MET_Base0_ety_EME);
   fChain->SetBranchAddress("MET_Base0_sumet_EME", &MET_Base0_sumet_EME, &b_MET_Base0_sumet_EME);
   fChain->SetBranchAddress("MET_Base0_phi_EME", &MET_Base0_phi_EME, &b_MET_Base0_phi_EME);
   fChain->SetBranchAddress("MET_Base0_etx_TILE", &MET_Base0_etx_TILE, &b_MET_Base0_etx_TILE);
   fChain->SetBranchAddress("MET_Base0_ety_TILE", &MET_Base0_ety_TILE, &b_MET_Base0_ety_TILE);
   fChain->SetBranchAddress("MET_Base0_sumet_TILE", &MET_Base0_sumet_TILE, &b_MET_Base0_sumet_TILE);
   fChain->SetBranchAddress("MET_Base0_phi_TILE", &MET_Base0_phi_TILE, &b_MET_Base0_phi_TILE);
   fChain->SetBranchAddress("MET_Base0_etx_HEC", &MET_Base0_etx_HEC, &b_MET_Base0_etx_HEC);
   fChain->SetBranchAddress("MET_Base0_ety_HEC", &MET_Base0_ety_HEC, &b_MET_Base0_ety_HEC);
   fChain->SetBranchAddress("MET_Base0_sumet_HEC", &MET_Base0_sumet_HEC, &b_MET_Base0_sumet_HEC);
   fChain->SetBranchAddress("MET_Base0_phi_HEC", &MET_Base0_phi_HEC, &b_MET_Base0_phi_HEC);
   fChain->SetBranchAddress("MET_Base0_etx_FCAL", &MET_Base0_etx_FCAL, &b_MET_Base0_etx_FCAL);
   fChain->SetBranchAddress("MET_Base0_ety_FCAL", &MET_Base0_ety_FCAL, &b_MET_Base0_ety_FCAL);
   fChain->SetBranchAddress("MET_Base0_sumet_FCAL", &MET_Base0_sumet_FCAL, &b_MET_Base0_sumet_FCAL);
   fChain->SetBranchAddress("MET_Base0_phi_FCAL", &MET_Base0_phi_FCAL, &b_MET_Base0_phi_FCAL);
   fChain->SetBranchAddress("MET_Base0_nCell_PEMB", &MET_Base0_nCell_PEMB, &b_MET_Base0_nCell_PEMB);
   fChain->SetBranchAddress("MET_Base0_nCell_EMB", &MET_Base0_nCell_EMB, &b_MET_Base0_nCell_EMB);
   fChain->SetBranchAddress("MET_Base0_nCell_PEMEC", &MET_Base0_nCell_PEMEC, &b_MET_Base0_nCell_PEMEC);
   fChain->SetBranchAddress("MET_Base0_nCell_EME", &MET_Base0_nCell_EME, &b_MET_Base0_nCell_EME);
   fChain->SetBranchAddress("MET_Base0_nCell_TILE", &MET_Base0_nCell_TILE, &b_MET_Base0_nCell_TILE);
   fChain->SetBranchAddress("MET_Base0_nCell_HEC", &MET_Base0_nCell_HEC, &b_MET_Base0_nCell_HEC);
   fChain->SetBranchAddress("MET_Base0_nCell_FCAL", &MET_Base0_nCell_FCAL, &b_MET_Base0_nCell_FCAL);
   fChain->SetBranchAddress("MET_Base0_etx_CentralReg", &MET_Base0_etx_CentralReg, &b_MET_Base0_etx_CentralReg);
   fChain->SetBranchAddress("MET_Base0_ety_CentralReg", &MET_Base0_ety_CentralReg, &b_MET_Base0_ety_CentralReg);
   fChain->SetBranchAddress("MET_Base0_sumet_CentralReg", &MET_Base0_sumet_CentralReg, &b_MET_Base0_sumet_CentralReg);
   fChain->SetBranchAddress("MET_Base0_phi_CentralReg", &MET_Base0_phi_CentralReg, &b_MET_Base0_phi_CentralReg);
   fChain->SetBranchAddress("MET_Base0_etx_EndcapRegion", &MET_Base0_etx_EndcapRegion, &b_MET_Base0_etx_EndcapRegion);
   fChain->SetBranchAddress("MET_Base0_ety_EndcapRegion", &MET_Base0_ety_EndcapRegion, &b_MET_Base0_ety_EndcapRegion);
   fChain->SetBranchAddress("MET_Base0_sumet_EndcapRegion", &MET_Base0_sumet_EndcapRegion, &b_MET_Base0_sumet_EndcapRegion);
   fChain->SetBranchAddress("MET_Base0_phi_EndcapRegion", &MET_Base0_phi_EndcapRegion, &b_MET_Base0_phi_EndcapRegion);
   fChain->SetBranchAddress("MET_Base0_etx_ForwardReg", &MET_Base0_etx_ForwardReg, &b_MET_Base0_etx_ForwardReg);
   fChain->SetBranchAddress("MET_Base0_ety_ForwardReg", &MET_Base0_ety_ForwardReg, &b_MET_Base0_ety_ForwardReg);
   fChain->SetBranchAddress("MET_Base0_sumet_ForwardReg", &MET_Base0_sumet_ForwardReg, &b_MET_Base0_sumet_ForwardReg);
   fChain->SetBranchAddress("MET_Base0_phi_ForwardReg", &MET_Base0_phi_ForwardReg, &b_MET_Base0_phi_ForwardReg);
   fChain->SetBranchAddress("MET_Calib_etx", &MET_Calib_etx, &b_MET_Calib_etx);
   fChain->SetBranchAddress("MET_Calib_ety", &MET_Calib_ety, &b_MET_Calib_ety);
   fChain->SetBranchAddress("MET_Calib_sumet", &MET_Calib_sumet, &b_MET_Calib_sumet);
   fChain->SetBranchAddress("MET_Calib_et", &MET_Calib_et, &b_MET_Calib_et);
   fChain->SetBranchAddress("MET_Calib_phi", &MET_Calib_phi, &b_MET_Calib_phi);
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
   fChain->SetBranchAddress("MET_Topo_etx", &MET_Topo_etx, &b_MET_Topo_etx);
   fChain->SetBranchAddress("MET_Topo_ety", &MET_Topo_ety, &b_MET_Topo_ety);
   fChain->SetBranchAddress("MET_Topo_sumet", &MET_Topo_sumet, &b_MET_Topo_sumet);
   fChain->SetBranchAddress("MET_Topo_et", &MET_Topo_et, &b_MET_Topo_et);
   fChain->SetBranchAddress("MET_Topo_phi", &MET_Topo_phi, &b_MET_Topo_phi);
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
   fChain->SetBranchAddress("MET_CorrTopo_etx", &MET_CorrTopo_etx, &b_MET_CorrTopo_etx);
   fChain->SetBranchAddress("MET_CorrTopo_ety", &MET_CorrTopo_ety, &b_MET_CorrTopo_ety);
   fChain->SetBranchAddress("MET_CorrTopo_sumet", &MET_CorrTopo_sumet, &b_MET_CorrTopo_sumet);
   fChain->SetBranchAddress("MET_CorrTopo_et", &MET_CorrTopo_et, &b_MET_CorrTopo_et);
   fChain->SetBranchAddress("MET_CorrTopo_phi", &MET_CorrTopo_phi, &b_MET_CorrTopo_phi);
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
   fChain->SetBranchAddress("MET_LocHadTopo_etx", &MET_LocHadTopo_etx, &b_MET_LocHadTopo_etx);
   fChain->SetBranchAddress("MET_LocHadTopo_ety", &MET_LocHadTopo_ety, &b_MET_LocHadTopo_ety);
   fChain->SetBranchAddress("MET_LocHadTopo_sumet", &MET_LocHadTopo_sumet, &b_MET_LocHadTopo_sumet);
   fChain->SetBranchAddress("MET_LocHadTopo_et", &MET_LocHadTopo_et, &b_MET_LocHadTopo_et);
   fChain->SetBranchAddress("MET_LocHadTopo_phi", &MET_LocHadTopo_phi, &b_MET_LocHadTopo_phi);
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
   fChain->SetBranchAddress("MET_JetsInfo_JetPtWeightedEventEMFraction", &MET_JetsInfo_JetPtWeightedEventEMFraction, &b_MET_JetsInfo_JetPtWeightedEventEMFraction);
   fChain->SetBranchAddress("MET_JetsInfo_JetPtWeightedNumAssociatedTracks", &MET_JetsInfo_JetPtWeightedNumAssociatedTracks, &b_MET_JetsInfo_JetPtWeightedNumAssociatedTracks);
   fChain->SetBranchAddress("MET_JetsInfo_JetPtWeightedSize", &MET_JetsInfo_JetPtWeightedSize, &b_MET_JetsInfo_JetPtWeightedSize);
   fChain->SetBranchAddress("MET_JetsInfo_LeadingJetEt", &MET_JetsInfo_LeadingJetEt, &b_MET_JetsInfo_LeadingJetEt);
   fChain->SetBranchAddress("MET_JetsInfo_LeadingJetEta", &MET_JetsInfo_LeadingJetEta, &b_MET_JetsInfo_LeadingJetEta);
   fChain->SetBranchAddress("cl_n", &cl_n, &b_cl_n);
   fChain->SetBranchAddress("cl_E", &cl_E, &b_cl_E);
   fChain->SetBranchAddress("cl_pt", &cl_pt, &b_cl_pt);
   fChain->SetBranchAddress("cl_m", &cl_m, &b_cl_m);
   fChain->SetBranchAddress("cl_eta", &cl_eta, &b_cl_eta);
   fChain->SetBranchAddress("cl_phi", &cl_phi, &b_cl_phi);
   fChain->SetBranchAddress("cl_E_em", &cl_E_em, &b_cl_E_em);
   fChain->SetBranchAddress("cl_E_had", &cl_E_had, &b_cl_E_had);
   fChain->SetBranchAddress("cl_firstEdens", &cl_firstEdens, &b_cl_firstEdens);
   fChain->SetBranchAddress("cl_cellmaxfrac", &cl_cellmaxfrac, &b_cl_cellmaxfrac);
   fChain->SetBranchAddress("cl_longitudinal", &cl_longitudinal, &b_cl_longitudinal);
   fChain->SetBranchAddress("cl_secondlambda", &cl_secondlambda, &b_cl_secondlambda);
   fChain->SetBranchAddress("cl_lateral", &cl_lateral, &b_cl_lateral);
   fChain->SetBranchAddress("cl_secondR", &cl_secondR, &b_cl_secondR);
   fChain->SetBranchAddress("cl_centerlambda", &cl_centerlambda, &b_cl_centerlambda);
   fChain->SetBranchAddress("cl_deltaTheta", &cl_deltaTheta, &b_cl_deltaTheta);
   fChain->SetBranchAddress("cl_deltaPhi", &cl_deltaPhi, &b_cl_deltaPhi);
   fChain->SetBranchAddress("cl_time", &cl_time, &b_cl_time);
   fChain->SetBranchAddress("emcl_n", &emcl_n, &b_emcl_n);
   fChain->SetBranchAddress("emcl_E", &emcl_E, &b_emcl_E);
   fChain->SetBranchAddress("emcl_pt", &emcl_pt, &b_emcl_pt);
   fChain->SetBranchAddress("emcl_m", &emcl_m, &b_emcl_m);
   fChain->SetBranchAddress("emcl_eta", &emcl_eta, &b_emcl_eta);
   fChain->SetBranchAddress("emcl_phi", &emcl_phi, &b_emcl_phi);
   fChain->SetBranchAddress("emcl_E_em", &emcl_E_em, &b_emcl_E_em);
   fChain->SetBranchAddress("emcl_E_had", &emcl_E_had, &b_emcl_E_had);
   fChain->SetBranchAddress("emcl_firstEdens", &emcl_firstEdens, &b_emcl_firstEdens);
   fChain->SetBranchAddress("emcl_cellmaxfrac", &emcl_cellmaxfrac, &b_emcl_cellmaxfrac);
   fChain->SetBranchAddress("emcl_longitudinal", &emcl_longitudinal, &b_emcl_longitudinal);
   fChain->SetBranchAddress("emcl_secondlambda", &emcl_secondlambda, &b_emcl_secondlambda);
   fChain->SetBranchAddress("emcl_lateral", &emcl_lateral, &b_emcl_lateral);
   fChain->SetBranchAddress("emcl_secondR", &emcl_secondR, &b_emcl_secondR);
   fChain->SetBranchAddress("emcl_centerlambda", &emcl_centerlambda, &b_emcl_centerlambda);
   fChain->SetBranchAddress("emcl_deltaTheta", &emcl_deltaTheta, &b_emcl_deltaTheta);
   fChain->SetBranchAddress("emcl_deltaPhi", &emcl_deltaPhi, &b_emcl_deltaPhi);
   fChain->SetBranchAddress("emcl_time", &emcl_time, &b_emcl_time);
   fChain->SetBranchAddress("emcl_E_PreSamplerB", &emcl_E_PreSamplerB, &b_emcl_E_PreSamplerB);
   fChain->SetBranchAddress("emcl_E_EMB1", &emcl_E_EMB1, &b_emcl_E_EMB1);
   fChain->SetBranchAddress("emcl_E_EMB2", &emcl_E_EMB2, &b_emcl_E_EMB2);
   fChain->SetBranchAddress("emcl_E_EMB3", &emcl_E_EMB3, &b_emcl_E_EMB3);
   fChain->SetBranchAddress("emcl_E_PreSamplerE", &emcl_E_PreSamplerE, &b_emcl_E_PreSamplerE);
   fChain->SetBranchAddress("emcl_E_EME1", &emcl_E_EME1, &b_emcl_E_EME1);
   fChain->SetBranchAddress("emcl_E_EME2", &emcl_E_EME2, &b_emcl_E_EME2);
   fChain->SetBranchAddress("emcl_E_EME3", &emcl_E_EME3, &b_emcl_E_EME3);
   fChain->SetBranchAddress("emcl_E_HEC0", &emcl_E_HEC0, &b_emcl_E_HEC0);
   fChain->SetBranchAddress("emcl_E_HEC1", &emcl_E_HEC1, &b_emcl_E_HEC1);
   fChain->SetBranchAddress("emcl_E_HEC2", &emcl_E_HEC2, &b_emcl_E_HEC2);
   fChain->SetBranchAddress("emcl_E_HEC3", &emcl_E_HEC3, &b_emcl_E_HEC3);
   fChain->SetBranchAddress("emcl_E_TileBar0", &emcl_E_TileBar0, &b_emcl_E_TileBar0);
   fChain->SetBranchAddress("emcl_E_TileBar1", &emcl_E_TileBar1, &b_emcl_E_TileBar1);
   fChain->SetBranchAddress("emcl_E_TileBar2", &emcl_E_TileBar2, &b_emcl_E_TileBar2);
   fChain->SetBranchAddress("emcl_E_TileGap1", &emcl_E_TileGap1, &b_emcl_E_TileGap1);
   fChain->SetBranchAddress("emcl_E_TileGap2", &emcl_E_TileGap2, &b_emcl_E_TileGap2);
   fChain->SetBranchAddress("emcl_E_TileGap3", &emcl_E_TileGap3, &b_emcl_E_TileGap3);
   fChain->SetBranchAddress("emcl_E_TileExt0", &emcl_E_TileExt0, &b_emcl_E_TileExt0);
   fChain->SetBranchAddress("emcl_E_TileExt1", &emcl_E_TileExt1, &b_emcl_E_TileExt1);
   fChain->SetBranchAddress("emcl_E_TileExt2", &emcl_E_TileExt2, &b_emcl_E_TileExt2);
   fChain->SetBranchAddress("emcl_E_FCAL0", &emcl_E_FCAL0, &b_emcl_E_FCAL0);
   fChain->SetBranchAddress("emcl_E_FCAL1", &emcl_E_FCAL1, &b_emcl_E_FCAL1);
   fChain->SetBranchAddress("emcl_E_FCAL2", &emcl_E_FCAL2, &b_emcl_E_FCAL2);
   fChain->SetBranchAddress("trk_n", &trk_n, &b_trk_n);
   fChain->SetBranchAddress("trk_d0", &trk_d0, &b_trk_d0);
   fChain->SetBranchAddress("trk_z0", &trk_z0, &b_trk_z0);
   fChain->SetBranchAddress("trk_phi", &trk_phi, &b_trk_phi);
   fChain->SetBranchAddress("trk_theta", &trk_theta, &b_trk_theta);
   fChain->SetBranchAddress("trk_qoverp", &trk_qoverp, &b_trk_qoverp);
   fChain->SetBranchAddress("trk_pt", &trk_pt, &b_trk_pt);
   fChain->SetBranchAddress("trk_eta", &trk_eta, &b_trk_eta);
   fChain->SetBranchAddress("trk_err_d0", &trk_err_d0, &b_trk_err_d0);
   fChain->SetBranchAddress("trk_err_z0", &trk_err_z0, &b_trk_err_z0);
   fChain->SetBranchAddress("trk_err_phi", &trk_err_phi, &b_trk_err_phi);
   fChain->SetBranchAddress("trk_err_theta", &trk_err_theta, &b_trk_err_theta);
   fChain->SetBranchAddress("trk_err_qoverp", &trk_err_qoverp, &b_trk_err_qoverp);
   fChain->SetBranchAddress("trk_cov_d0", &trk_cov_d0, &b_trk_cov_d0);
   fChain->SetBranchAddress("trk_cov_z0", &trk_cov_z0, &b_trk_cov_z0);
   fChain->SetBranchAddress("trk_cov_phi", &trk_cov_phi, &b_trk_cov_phi);
   fChain->SetBranchAddress("trk_cov_theta", &trk_cov_theta, &b_trk_cov_theta);
   fChain->SetBranchAddress("trk_cov_qoverp", &trk_cov_qoverp, &b_trk_cov_qoverp);
   fChain->SetBranchAddress("trk_cov_d0_z0", &trk_cov_d0_z0, &b_trk_cov_d0_z0);
   fChain->SetBranchAddress("trk_cov_d0_phi", &trk_cov_d0_phi, &b_trk_cov_d0_phi);
   fChain->SetBranchAddress("trk_cov_d0_theta", &trk_cov_d0_theta, &b_trk_cov_d0_theta);
   fChain->SetBranchAddress("trk_cov_d0_qoverp", &trk_cov_d0_qoverp, &b_trk_cov_d0_qoverp);
   fChain->SetBranchAddress("trk_cov_z0_phi", &trk_cov_z0_phi, &b_trk_cov_z0_phi);
   fChain->SetBranchAddress("trk_cov_z0_theta", &trk_cov_z0_theta, &b_trk_cov_z0_theta);
   fChain->SetBranchAddress("trk_cov_z0_qoverp", &trk_cov_z0_qoverp, &b_trk_cov_z0_qoverp);
   fChain->SetBranchAddress("trk_cov_phi_theta", &trk_cov_phi_theta, &b_trk_cov_phi_theta);
   fChain->SetBranchAddress("trk_cov_phi_qoverp", &trk_cov_phi_qoverp, &b_trk_cov_phi_qoverp);
   fChain->SetBranchAddress("trk_cov_theta_qoverp", &trk_cov_theta_qoverp, &b_trk_cov_theta_qoverp);
   fChain->SetBranchAddress("trk_blayerPrediction_expectHit", &trk_blayerPrediction_expectHit, &b_trk_blayerPrediction_expectHit);
   fChain->SetBranchAddress("trk_blayerPrediction_x", &trk_blayerPrediction_x, &b_trk_blayerPrediction_x);
   fChain->SetBranchAddress("trk_blayerPrediction_y", &trk_blayerPrediction_y, &b_trk_blayerPrediction_y);
   fChain->SetBranchAddress("trk_blayerPrediction_z", &trk_blayerPrediction_z, &b_trk_blayerPrediction_z);
   fChain->SetBranchAddress("trk_blayerPrediction_locX", &trk_blayerPrediction_locX, &b_trk_blayerPrediction_locX);
   fChain->SetBranchAddress("trk_blayerPrediction_locY", &trk_blayerPrediction_locY, &b_trk_blayerPrediction_locY);
   fChain->SetBranchAddress("trk_blayerPrediction_err_locX", &trk_blayerPrediction_err_locX, &b_trk_blayerPrediction_err_locX);
   fChain->SetBranchAddress("trk_blayerPrediction_err_locY", &trk_blayerPrediction_err_locY, &b_trk_blayerPrediction_err_locY);
   fChain->SetBranchAddress("trk_blayerPrediction_etaDistToEdge", &trk_blayerPrediction_etaDistToEdge, &b_trk_blayerPrediction_etaDistToEdge);
   fChain->SetBranchAddress("trk_blayerPrediction_phiDistToEdge", &trk_blayerPrediction_phiDistToEdge, &b_trk_blayerPrediction_phiDistToEdge);
   fChain->SetBranchAddress("trk_blayerPrediction_detElementId", &trk_blayerPrediction_detElementId, &b_trk_blayerPrediction_detElementId);
   fChain->SetBranchAddress("trk_blayerPrediction_row", &trk_blayerPrediction_row, &b_trk_blayerPrediction_row);
   fChain->SetBranchAddress("trk_blayerPrediction_col", &trk_blayerPrediction_col, &b_trk_blayerPrediction_col);
   fChain->SetBranchAddress("trk_blayerPrediction_type", &trk_blayerPrediction_type, &b_trk_blayerPrediction_type);
   fChain->SetBranchAddress("trk_d0_wrtPV", &trk_d0_wrtPV, &b_trk_d0_wrtPV);
   fChain->SetBranchAddress("trk_z0_wrtPV", &trk_z0_wrtPV, &b_trk_z0_wrtPV);
   fChain->SetBranchAddress("trk_phi_wrtPV", &trk_phi_wrtPV, &b_trk_phi_wrtPV);
   fChain->SetBranchAddress("trk_theta_wrtPV", &trk_theta_wrtPV, &b_trk_theta_wrtPV);
   fChain->SetBranchAddress("trk_qoverp_wrtPV", &trk_qoverp_wrtPV, &b_trk_qoverp_wrtPV);
   fChain->SetBranchAddress("trk_chi2", &trk_chi2, &b_trk_chi2);
   fChain->SetBranchAddress("trk_ndof", &trk_ndof, &b_trk_ndof);
   fChain->SetBranchAddress("trk_nBLHits", &trk_nBLHits, &b_trk_nBLHits);
   fChain->SetBranchAddress("trk_nPixHits", &trk_nPixHits, &b_trk_nPixHits);
   fChain->SetBranchAddress("trk_nSCTHits", &trk_nSCTHits, &b_trk_nSCTHits);
   fChain->SetBranchAddress("trk_nTRTHits", &trk_nTRTHits, &b_trk_nTRTHits);
   fChain->SetBranchAddress("trk_nPixHoles", &trk_nPixHoles, &b_trk_nPixHoles);
   fChain->SetBranchAddress("trk_nSCTHoles", &trk_nSCTHoles, &b_trk_nSCTHoles);
   fChain->SetBranchAddress("trk_nMDTHits", &trk_nMDTHits, &b_trk_nMDTHits);
   fChain->SetBranchAddress("trk_nCSCEtaHits", &trk_nCSCEtaHits, &b_trk_nCSCEtaHits);
   fChain->SetBranchAddress("trk_nCSCPhiHits", &trk_nCSCPhiHits, &b_trk_nCSCPhiHits);
   fChain->SetBranchAddress("trk_nRPCEtaHits", &trk_nRPCEtaHits, &b_trk_nRPCEtaHits);
   fChain->SetBranchAddress("trk_nRPCPhiHits", &trk_nRPCPhiHits, &b_trk_nRPCPhiHits);
   fChain->SetBranchAddress("trk_nTGCEtaHits", &trk_nTGCEtaHits, &b_trk_nTGCEtaHits);
   fChain->SetBranchAddress("trk_nTGCPhiHits", &trk_nTGCPhiHits, &b_trk_nTGCPhiHits);
   fChain->SetBranchAddress("trk_nHits", &trk_nHits, &b_trk_nHits);
   fChain->SetBranchAddress("trk_nHoles", &trk_nHoles, &b_trk_nHoles);
   fChain->SetBranchAddress("trk_hitPattern", &trk_hitPattern, &b_trk_hitPattern);
   fChain->SetBranchAddress("trk_TRTHighTHitsRatio", &trk_TRTHighTHitsRatio, &b_trk_TRTHighTHitsRatio);
   fChain->SetBranchAddress("trk_pixeldEdx", &trk_pixeldEdx, &b_trk_pixeldEdx);
   fChain->SetBranchAddress("trk_fitter", &trk_fitter, &b_trk_fitter);
   fChain->SetBranchAddress("trk_patternReco1", &trk_patternReco1, &b_trk_patternReco1);
   fChain->SetBranchAddress("trk_patternReco2", &trk_patternReco2, &b_trk_patternReco2);
   fChain->SetBranchAddress("trk_seedFinder", &trk_seedFinder, &b_trk_seedFinder);
   fChain->SetBranchAddress("mb_n", &mb_n, &b_mb_n);
   fChain->SetBranchAddress("mb_E", &mb_E, &b_mb_E);
   fChain->SetBranchAddress("mb_eta", &mb_eta, &b_mb_eta);
   fChain->SetBranchAddress("mb_phi", &mb_phi, &b_mb_phi);
   fChain->SetBranchAddress("mb_time", &mb_time, &b_mb_time);
   fChain->SetBranchAddress("mb_quality", &mb_quality, &b_mb_quality);
   fChain->SetBranchAddress("mb_type", &mb_type, &b_mb_type);
   fChain->SetBranchAddress("mb_module", &mb_module, &b_mb_module);
   fChain->SetBranchAddress("mb_channel", &mb_channel, &b_mb_channel);
   fChain->SetBranchAddress("mbtime_timeDiff", &mbtime_timeDiff, &b_mbtime_timeDiff);
   fChain->SetBranchAddress("mbtime_timeA", &mbtime_timeA, &b_mbtime_timeA);
   fChain->SetBranchAddress("mbtime_timeC", &mbtime_timeC, &b_mbtime_timeC);
   fChain->SetBranchAddress("mbtime_countA", &mbtime_countA, &b_mbtime_countA);
   fChain->SetBranchAddress("mbtime_countC", &mbtime_countC, &b_mbtime_countC);
   fChain->SetBranchAddress("L1_MBTS_1", &L1_MBTS_1, &b_L1_MBTS_1);
   fChain->SetBranchAddress("L1_MBTS_1_1", &L1_MBTS_1_1, &b_L1_MBTS_1_1);
   fChain->SetBranchAddress("L1_MBTS_1_1_EMPTY", &L1_MBTS_1_1_EMPTY, &b_L1_MBTS_1_1_EMPTY);
   fChain->SetBranchAddress("L1_MBTS_1_1_UNPAIRED_ISO", &L1_MBTS_1_1_UNPAIRED_ISO, &b_L1_MBTS_1_1_UNPAIRED_ISO);
   fChain->SetBranchAddress("L1_MBTS_1_EMPTY", &L1_MBTS_1_EMPTY, &b_L1_MBTS_1_EMPTY);
   fChain->SetBranchAddress("L1_MBTS_1_UNPAIRED_ISO", &L1_MBTS_1_UNPAIRED_ISO, &b_L1_MBTS_1_UNPAIRED_ISO);
   fChain->SetBranchAddress("L1_MBTS_2", &L1_MBTS_2, &b_L1_MBTS_2);
   fChain->SetBranchAddress("L1_MBTS_2_EMPTY", &L1_MBTS_2_EMPTY, &b_L1_MBTS_2_EMPTY);
   fChain->SetBranchAddress("L1_MBTS_2_UNPAIRED_ISO", &L1_MBTS_2_UNPAIRED_ISO, &b_L1_MBTS_2_UNPAIRED_ISO);
   fChain->SetBranchAddress("L1_MBTS_2_UNPAIRED_NONISO", &L1_MBTS_2_UNPAIRED_NONISO, &b_L1_MBTS_2_UNPAIRED_NONISO);
   fChain->SetBranchAddress("L1_MBTS_4_4", &L1_MBTS_4_4, &b_L1_MBTS_4_4);
   fChain->SetBranchAddress("L1_MBTS_4_4_UNPAIRED_ISO", &L1_MBTS_4_4_UNPAIRED_ISO, &b_L1_MBTS_4_4_UNPAIRED_ISO);
   fChain->SetBranchAddress("collcand_passMBTSTime", &collcand_passMBTSTime, &b_collcand_passMBTSTime);
   fChain->SetBranchAddress("collcand_passCaloTime", &collcand_passCaloTime, &b_collcand_passCaloTime);
   fChain->SetBranchAddress("collcand_passTrigger", &collcand_passTrigger, &b_collcand_passTrigger);
   fChain->SetBranchAddress("collcand_pass", &collcand_pass, &b_collcand_pass);
   fChain->SetBranchAddress("vxp_n", &vxp_n, &b_vxp_n);
   fChain->SetBranchAddress("vxp_x", &vxp_x, &b_vxp_x);
   fChain->SetBranchAddress("vxp_y", &vxp_y, &b_vxp_y);
   fChain->SetBranchAddress("vxp_z", &vxp_z, &b_vxp_z);
   fChain->SetBranchAddress("vxp_chi2", &vxp_chi2, &b_vxp_chi2);
   fChain->SetBranchAddress("vxp_ndof", &vxp_ndof, &b_vxp_ndof);
   fChain->SetBranchAddress("vxp_err_x", &vxp_err_x, &b_vxp_err_x);
   fChain->SetBranchAddress("vxp_err_y", &vxp_err_y, &b_vxp_err_y);
   fChain->SetBranchAddress("vxp_err_z", &vxp_err_z, &b_vxp_err_z);
   fChain->SetBranchAddress("vxp_px", &vxp_px, &b_vxp_px);
   fChain->SetBranchAddress("vxp_py", &vxp_py, &b_vxp_py);
   fChain->SetBranchAddress("vxp_pz", &vxp_pz, &b_vxp_pz);
   fChain->SetBranchAddress("vxp_E", &vxp_E, &b_vxp_E);
   fChain->SetBranchAddress("vxp_m", &vxp_m, &b_vxp_m);
   fChain->SetBranchAddress("vxp_nTracks", &vxp_nTracks, &b_vxp_nTracks);
   fChain->SetBranchAddress("vxp_sumPt", &vxp_sumPt, &b_vxp_sumPt);
   fChain->SetBranchAddress("vxp_type", &vxp_type, &b_vxp_type);
   fChain->SetBranchAddress("vxp_trk_n", &vxp_trk_n, &b_vxp_trk_n);
   fChain->SetBranchAddress("vxp_trk_chi2", &vxp_trk_chi2, &b_vxp_trk_chi2);
   fChain->SetBranchAddress("vxp_trk_d0", &vxp_trk_d0, &b_vxp_trk_d0);
   fChain->SetBranchAddress("vxp_trk_z0", &vxp_trk_z0, &b_vxp_trk_z0);
   fChain->SetBranchAddress("vxp_trk_unbiased_d0", &vxp_trk_unbiased_d0, &b_vxp_trk_unbiased_d0);
   fChain->SetBranchAddress("vxp_trk_unbiased_z0", &vxp_trk_unbiased_z0, &b_vxp_trk_unbiased_z0);
   fChain->SetBranchAddress("vxp_trk_err_unbiased_d0", &vxp_trk_err_unbiased_d0, &b_vxp_trk_err_unbiased_d0);
   fChain->SetBranchAddress("vxp_trk_err_unbiased_z0", &vxp_trk_err_unbiased_z0, &b_vxp_trk_err_unbiased_z0);
   fChain->SetBranchAddress("vxp_trk_phi", &vxp_trk_phi, &b_vxp_trk_phi);
   fChain->SetBranchAddress("vxp_trk_theta", &vxp_trk_theta, &b_vxp_trk_theta);
   fChain->SetBranchAddress("vxp_trk_weight", &vxp_trk_weight, &b_vxp_trk_weight);
   fChain->SetBranchAddress("vxp_trk_index", &vxp_trk_index, &b_vxp_trk_index);
   fChain->SetBranchAddress("trig_L1_emtau_n", &trig_L1_emtau_n, &b_trig_L1_emtau_n);
   fChain->SetBranchAddress("trig_L1_emtau_eta", &trig_L1_emtau_eta, &b_trig_L1_emtau_eta);
   fChain->SetBranchAddress("trig_L1_emtau_phi", &trig_L1_emtau_phi, &b_trig_L1_emtau_phi);
   fChain->SetBranchAddress("trig_L1_emtau_thrNames", &trig_L1_emtau_thrNames, &b_trig_L1_emtau_thrNames);
   fChain->SetBranchAddress("trig_L1_emtau_thrValues", &trig_L1_emtau_thrValues, &b_trig_L1_emtau_thrValues);
   fChain->SetBranchAddress("trig_L1_emtau_core", &trig_L1_emtau_core, &b_trig_L1_emtau_core);
   fChain->SetBranchAddress("trig_L1_emtau_EMClus", &trig_L1_emtau_EMClus, &b_trig_L1_emtau_EMClus);
   fChain->SetBranchAddress("trig_L1_emtau_tauClus", &trig_L1_emtau_tauClus, &b_trig_L1_emtau_tauClus);
   fChain->SetBranchAddress("trig_L1_emtau_EMIsol", &trig_L1_emtau_EMIsol, &b_trig_L1_emtau_EMIsol);
   fChain->SetBranchAddress("trig_L1_emtau_hadIsol", &trig_L1_emtau_hadIsol, &b_trig_L1_emtau_hadIsol);
   fChain->SetBranchAddress("trig_L1_emtau_hadCore", &trig_L1_emtau_hadCore, &b_trig_L1_emtau_hadCore);
   fChain->SetBranchAddress("trig_L1_emtau_thrPattern", &trig_L1_emtau_thrPattern, &b_trig_L1_emtau_thrPattern);
   fChain->SetBranchAddress("trig_L1_emtau_L1_2EM10", &trig_L1_emtau_L1_2EM10, &b_trig_L1_emtau_L1_2EM10);
   fChain->SetBranchAddress("trig_L1_emtau_L1_2EM14", &trig_L1_emtau_L1_2EM14, &b_trig_L1_emtau_L1_2EM14);
   fChain->SetBranchAddress("trig_L1_emtau_L1_2EM2", &trig_L1_emtau_L1_2EM2, &b_trig_L1_emtau_L1_2EM2);
   fChain->SetBranchAddress("trig_L1_emtau_L1_2EM3", &trig_L1_emtau_L1_2EM3, &b_trig_L1_emtau_L1_2EM3);
   fChain->SetBranchAddress("trig_L1_emtau_L1_2EM5", &trig_L1_emtau_L1_2EM5, &b_trig_L1_emtau_L1_2EM5);
   fChain->SetBranchAddress("trig_L1_emtau_L1_EM10", &trig_L1_emtau_L1_EM10, &b_trig_L1_emtau_L1_EM10);
   fChain->SetBranchAddress("trig_L1_emtau_L1_EM10I", &trig_L1_emtau_L1_EM10I, &b_trig_L1_emtau_L1_EM10I);
   fChain->SetBranchAddress("trig_L1_emtau_L1_EM14", &trig_L1_emtau_L1_EM14, &b_trig_L1_emtau_L1_EM14);
   fChain->SetBranchAddress("trig_L1_emtau_L1_EM14I", &trig_L1_emtau_L1_EM14I, &b_trig_L1_emtau_L1_EM14I);
   fChain->SetBranchAddress("trig_L1_emtau_L1_EM14_XE10", &trig_L1_emtau_L1_EM14_XE10, &b_trig_L1_emtau_L1_EM14_XE10);
   fChain->SetBranchAddress("trig_L1_emtau_L1_EM14_XE15", &trig_L1_emtau_L1_EM14_XE15, &b_trig_L1_emtau_L1_EM14_XE15);
   fChain->SetBranchAddress("trig_L1_emtau_L1_EM2", &trig_L1_emtau_L1_EM2, &b_trig_L1_emtau_L1_EM2);
   fChain->SetBranchAddress("trig_L1_emtau_L1_EM2_UNPAIRED_ISO", &trig_L1_emtau_L1_EM2_UNPAIRED_ISO, &b_trig_L1_emtau_L1_EM2_UNPAIRED_ISO);
   fChain->SetBranchAddress("trig_L1_emtau_L1_EM2_UNPAIRED_NONISO", &trig_L1_emtau_L1_EM2_UNPAIRED_NONISO, &b_trig_L1_emtau_L1_EM2_UNPAIRED_NONISO);
   fChain->SetBranchAddress("trig_L1_emtau_L1_EM3", &trig_L1_emtau_L1_EM3, &b_trig_L1_emtau_L1_EM3);
   fChain->SetBranchAddress("trig_L1_emtau_L1_EM3_EMPTY", &trig_L1_emtau_L1_EM3_EMPTY, &b_trig_L1_emtau_L1_EM3_EMPTY);
   fChain->SetBranchAddress("trig_L1_emtau_L1_EM3_FIRSTEMPTY", &trig_L1_emtau_L1_EM3_FIRSTEMPTY, &b_trig_L1_emtau_L1_EM3_FIRSTEMPTY);
   fChain->SetBranchAddress("trig_L1_emtau_L1_EM3_MV", &trig_L1_emtau_L1_EM3_MV, &b_trig_L1_emtau_L1_EM3_MV);
   fChain->SetBranchAddress("trig_L1_emtau_L1_EM5", &trig_L1_emtau_L1_EM5, &b_trig_L1_emtau_L1_EM5);
   fChain->SetBranchAddress("trig_L1_emtau_L1_EM5_MU10", &trig_L1_emtau_L1_EM5_MU10, &b_trig_L1_emtau_L1_EM5_MU10);
   fChain->SetBranchAddress("trig_L1_emtau_L1_EM5_MU6", &trig_L1_emtau_L1_EM5_MU6, &b_trig_L1_emtau_L1_EM5_MU6);
   fChain->SetBranchAddress("trig_L1_emtau_L1_EM85", &trig_L1_emtau_L1_EM85, &b_trig_L1_emtau_L1_EM85);
   fChain->SetBranchAddress("trig_L2_emcl_n", &trig_L2_emcl_n, &b_trig_L2_emcl_n);
   fChain->SetBranchAddress("trig_L2_emcl_quality", &trig_L2_emcl_quality, &b_trig_L2_emcl_quality);
   fChain->SetBranchAddress("trig_L2_emcl_E", &trig_L2_emcl_E, &b_trig_L2_emcl_E);
   fChain->SetBranchAddress("trig_L2_emcl_Et", &trig_L2_emcl_Et, &b_trig_L2_emcl_Et);
   fChain->SetBranchAddress("trig_L2_emcl_eta", &trig_L2_emcl_eta, &b_trig_L2_emcl_eta);
   fChain->SetBranchAddress("trig_L2_emcl_phi", &trig_L2_emcl_phi, &b_trig_L2_emcl_phi);
   fChain->SetBranchAddress("trig_L2_emcl_E237", &trig_L2_emcl_E237, &b_trig_L2_emcl_E237);
   fChain->SetBranchAddress("trig_L2_emcl_E277", &trig_L2_emcl_E277, &b_trig_L2_emcl_E277);
   fChain->SetBranchAddress("trig_L2_emcl_fracs1", &trig_L2_emcl_fracs1, &b_trig_L2_emcl_fracs1);
   fChain->SetBranchAddress("trig_L2_emcl_weta2", &trig_L2_emcl_weta2, &b_trig_L2_emcl_weta2);
   fChain->SetBranchAddress("trig_L2_emcl_Ehad1", &trig_L2_emcl_Ehad1, &b_trig_L2_emcl_Ehad1);
   fChain->SetBranchAddress("trig_L2_emcl_eta1", &trig_L2_emcl_eta1, &b_trig_L2_emcl_eta1);
   fChain->SetBranchAddress("trig_L2_emcl_emaxs1", &trig_L2_emcl_emaxs1, &b_trig_L2_emcl_emaxs1);
   fChain->SetBranchAddress("trig_L2_emcl_e2tsts1", &trig_L2_emcl_e2tsts1, &b_trig_L2_emcl_e2tsts1);
   fChain->SetBranchAddress("trig_L2_trk_idscan_eGamma_n", &trig_L2_trk_idscan_eGamma_n, &b_trig_L2_trk_idscan_eGamma_n);
   fChain->SetBranchAddress("trig_L2_trk_idscan_eGamma_algorithmId", &trig_L2_trk_idscan_eGamma_algorithmId, &b_trig_L2_trk_idscan_eGamma_algorithmId);
   fChain->SetBranchAddress("trig_L2_trk_idscan_eGamma_trackStatus", &trig_L2_trk_idscan_eGamma_trackStatus, &b_trig_L2_trk_idscan_eGamma_trackStatus);
   fChain->SetBranchAddress("trig_L2_trk_idscan_eGamma_chi2Ndof", &trig_L2_trk_idscan_eGamma_chi2Ndof, &b_trig_L2_trk_idscan_eGamma_chi2Ndof);
   fChain->SetBranchAddress("trig_L2_trk_idscan_eGamma_nStrawHits", &trig_L2_trk_idscan_eGamma_nStrawHits, &b_trig_L2_trk_idscan_eGamma_nStrawHits);
   fChain->SetBranchAddress("trig_L2_trk_idscan_eGamma_nHighThrHits", &trig_L2_trk_idscan_eGamma_nHighThrHits, &b_trig_L2_trk_idscan_eGamma_nHighThrHits);
   fChain->SetBranchAddress("trig_L2_trk_idscan_eGamma_nPixelSpacePoints", &trig_L2_trk_idscan_eGamma_nPixelSpacePoints, &b_trig_L2_trk_idscan_eGamma_nPixelSpacePoints);
   fChain->SetBranchAddress("trig_L2_trk_idscan_eGamma_nSCT_SpacePoints", &trig_L2_trk_idscan_eGamma_nSCT_SpacePoints, &b_trig_L2_trk_idscan_eGamma_nSCT_SpacePoints);
   fChain->SetBranchAddress("trig_L2_trk_idscan_eGamma_a0", &trig_L2_trk_idscan_eGamma_a0, &b_trig_L2_trk_idscan_eGamma_a0);
   fChain->SetBranchAddress("trig_L2_trk_idscan_eGamma_z0", &trig_L2_trk_idscan_eGamma_z0, &b_trig_L2_trk_idscan_eGamma_z0);
   fChain->SetBranchAddress("trig_L2_trk_idscan_eGamma_phi0", &trig_L2_trk_idscan_eGamma_phi0, &b_trig_L2_trk_idscan_eGamma_phi0);
   fChain->SetBranchAddress("trig_L2_trk_idscan_eGamma_eta", &trig_L2_trk_idscan_eGamma_eta, &b_trig_L2_trk_idscan_eGamma_eta);
   fChain->SetBranchAddress("trig_L2_trk_idscan_eGamma_pt", &trig_L2_trk_idscan_eGamma_pt, &b_trig_L2_trk_idscan_eGamma_pt);
   fChain->SetBranchAddress("trig_L2_trk_sitrack_eGamma_n", &trig_L2_trk_sitrack_eGamma_n, &b_trig_L2_trk_sitrack_eGamma_n);
   fChain->SetBranchAddress("trig_L2_trk_sitrack_eGamma_algorithmId", &trig_L2_trk_sitrack_eGamma_algorithmId, &b_trig_L2_trk_sitrack_eGamma_algorithmId);
   fChain->SetBranchAddress("trig_L2_trk_sitrack_eGamma_trackStatus", &trig_L2_trk_sitrack_eGamma_trackStatus, &b_trig_L2_trk_sitrack_eGamma_trackStatus);
   fChain->SetBranchAddress("trig_L2_trk_sitrack_eGamma_chi2Ndof", &trig_L2_trk_sitrack_eGamma_chi2Ndof, &b_trig_L2_trk_sitrack_eGamma_chi2Ndof);
   fChain->SetBranchAddress("trig_L2_trk_sitrack_eGamma_nStrawHits", &trig_L2_trk_sitrack_eGamma_nStrawHits, &b_trig_L2_trk_sitrack_eGamma_nStrawHits);
   fChain->SetBranchAddress("trig_L2_trk_sitrack_eGamma_nHighThrHits", &trig_L2_trk_sitrack_eGamma_nHighThrHits, &b_trig_L2_trk_sitrack_eGamma_nHighThrHits);
   fChain->SetBranchAddress("trig_L2_trk_sitrack_eGamma_nPixelSpacePoints", &trig_L2_trk_sitrack_eGamma_nPixelSpacePoints, &b_trig_L2_trk_sitrack_eGamma_nPixelSpacePoints);
   fChain->SetBranchAddress("trig_L2_trk_sitrack_eGamma_nSCT_SpacePoints", &trig_L2_trk_sitrack_eGamma_nSCT_SpacePoints, &b_trig_L2_trk_sitrack_eGamma_nSCT_SpacePoints);
   fChain->SetBranchAddress("trig_L2_trk_sitrack_eGamma_a0", &trig_L2_trk_sitrack_eGamma_a0, &b_trig_L2_trk_sitrack_eGamma_a0);
   fChain->SetBranchAddress("trig_L2_trk_sitrack_eGamma_z0", &trig_L2_trk_sitrack_eGamma_z0, &b_trig_L2_trk_sitrack_eGamma_z0);
   fChain->SetBranchAddress("trig_L2_trk_sitrack_eGamma_phi0", &trig_L2_trk_sitrack_eGamma_phi0, &b_trig_L2_trk_sitrack_eGamma_phi0);
   fChain->SetBranchAddress("trig_L2_trk_sitrack_eGamma_eta", &trig_L2_trk_sitrack_eGamma_eta, &b_trig_L2_trk_sitrack_eGamma_eta);
   fChain->SetBranchAddress("trig_L2_trk_sitrack_eGamma_pt", &trig_L2_trk_sitrack_eGamma_pt, &b_trig_L2_trk_sitrack_eGamma_pt);
   fChain->SetBranchAddress("trig_L2_el_n", &trig_L2_el_n, &b_trig_L2_el_n);
   fChain->SetBranchAddress("trig_L2_el_E", &trig_L2_el_E, &b_trig_L2_el_E);
   fChain->SetBranchAddress("trig_L2_el_Et", &trig_L2_el_Et, &b_trig_L2_el_Et);
   fChain->SetBranchAddress("trig_L2_el_pt", &trig_L2_el_pt, &b_trig_L2_el_pt);
   fChain->SetBranchAddress("trig_L2_el_eta", &trig_L2_el_eta, &b_trig_L2_el_eta);
   fChain->SetBranchAddress("trig_L2_el_phi", &trig_L2_el_phi, &b_trig_L2_el_phi);
   fChain->SetBranchAddress("trig_L2_el_RoIWord", &trig_L2_el_RoIWord, &b_trig_L2_el_RoIWord);
   fChain->SetBranchAddress("trig_L2_el_zvertex", &trig_L2_el_zvertex, &b_trig_L2_el_zvertex);
   fChain->SetBranchAddress("trig_L2_el_charge", &trig_L2_el_charge, &b_trig_L2_el_charge);
   fChain->SetBranchAddress("trig_L2_el_trackAlgo", &trig_L2_el_trackAlgo, &b_trig_L2_el_trackAlgo);
   fChain->SetBranchAddress("trig_L2_el_TRTHighTHitsRatio", &trig_L2_el_TRTHighTHitsRatio, &b_trig_L2_el_TRTHighTHitsRatio);
   fChain->SetBranchAddress("trig_L2_el_deltaeta1", &trig_L2_el_deltaeta1, &b_trig_L2_el_deltaeta1);
   fChain->SetBranchAddress("trig_L2_el_deltaphi2", &trig_L2_el_deltaphi2, &b_trig_L2_el_deltaphi2);
   fChain->SetBranchAddress("trig_L2_el_EtOverPt", &trig_L2_el_EtOverPt, &b_trig_L2_el_EtOverPt);
   fChain->SetBranchAddress("trig_L2_el_reta", &trig_L2_el_reta, &b_trig_L2_el_reta);
   fChain->SetBranchAddress("trig_L2_el_Eratio", &trig_L2_el_Eratio, &b_trig_L2_el_Eratio);
   fChain->SetBranchAddress("trig_L2_el_Ethad1", &trig_L2_el_Ethad1, &b_trig_L2_el_Ethad1);
   fChain->SetBranchAddress("trig_L2_el_L2_2e10_loose", &trig_L2_el_L2_2e10_loose, &b_trig_L2_el_L2_2e10_loose);
   fChain->SetBranchAddress("trig_L2_el_L2_2e10_medium", &trig_L2_el_L2_2e10_medium, &b_trig_L2_el_L2_2e10_medium);
   fChain->SetBranchAddress("trig_L2_el_L2_2e15_loose", &trig_L2_el_L2_2e15_loose, &b_trig_L2_el_L2_2e15_loose);
   fChain->SetBranchAddress("trig_L2_el_L2_2e3_loose", &trig_L2_el_L2_2e3_loose, &b_trig_L2_el_L2_2e3_loose);
   fChain->SetBranchAddress("trig_L2_el_L2_2e3_loose_SiTrk", &trig_L2_el_L2_2e3_loose_SiTrk, &b_trig_L2_el_L2_2e3_loose_SiTrk);
   fChain->SetBranchAddress("trig_L2_el_L2_2e3_loose_TRT", &trig_L2_el_L2_2e3_loose_TRT, &b_trig_L2_el_L2_2e3_loose_TRT);
   fChain->SetBranchAddress("trig_L2_el_L2_2e3_medium", &trig_L2_el_L2_2e3_medium, &b_trig_L2_el_L2_2e3_medium);
   fChain->SetBranchAddress("trig_L2_el_L2_2e3_medium_SiTrk", &trig_L2_el_L2_2e3_medium_SiTrk, &b_trig_L2_el_L2_2e3_medium_SiTrk);
   fChain->SetBranchAddress("trig_L2_el_L2_2e3_medium_TRT", &trig_L2_el_L2_2e3_medium_TRT, &b_trig_L2_el_L2_2e3_medium_TRT);
   fChain->SetBranchAddress("trig_L2_el_L2_2e3_tight", &trig_L2_el_L2_2e3_tight, &b_trig_L2_el_L2_2e3_tight);
   fChain->SetBranchAddress("trig_L2_el_L2_2e5_medium", &trig_L2_el_L2_2e5_medium, &b_trig_L2_el_L2_2e5_medium);
   fChain->SetBranchAddress("trig_L2_el_L2_2e5_medium_SiTrk", &trig_L2_el_L2_2e5_medium_SiTrk, &b_trig_L2_el_L2_2e5_medium_SiTrk);
   fChain->SetBranchAddress("trig_L2_el_L2_2e5_medium_TRT", &trig_L2_el_L2_2e5_medium_TRT, &b_trig_L2_el_L2_2e5_medium_TRT);
   fChain->SetBranchAddress("trig_L2_el_L2_2e5_tight", &trig_L2_el_L2_2e5_tight, &b_trig_L2_el_L2_2e5_tight);
   fChain->SetBranchAddress("trig_L2_el_L2_e10_NoCut", &trig_L2_el_L2_e10_NoCut, &b_trig_L2_el_L2_e10_NoCut);
   fChain->SetBranchAddress("trig_L2_el_L2_e10_loose", &trig_L2_el_L2_e10_loose, &b_trig_L2_el_L2_e10_loose);
   fChain->SetBranchAddress("trig_L2_el_L2_e10_loose_mu10", &trig_L2_el_L2_e10_loose_mu10, &b_trig_L2_el_L2_e10_loose_mu10);
   fChain->SetBranchAddress("trig_L2_el_L2_e10_loose_mu6", &trig_L2_el_L2_e10_loose_mu6, &b_trig_L2_el_L2_e10_loose_mu6);
   fChain->SetBranchAddress("trig_L2_el_L2_e10_medium", &trig_L2_el_L2_e10_medium, &b_trig_L2_el_L2_e10_medium);
   fChain->SetBranchAddress("trig_L2_el_L2_e10_medium_IDTrkNoCut", &trig_L2_el_L2_e10_medium_IDTrkNoCut, &b_trig_L2_el_L2_e10_medium_IDTrkNoCut);
   fChain->SetBranchAddress("trig_L2_el_L2_e10_medium_SiTrk", &trig_L2_el_L2_e10_medium_SiTrk, &b_trig_L2_el_L2_e10_medium_SiTrk);
   fChain->SetBranchAddress("trig_L2_el_L2_e10_medium_TRT", &trig_L2_el_L2_e10_medium_TRT, &b_trig_L2_el_L2_e10_medium_TRT);
   fChain->SetBranchAddress("trig_L2_el_L2_e10_tight", &trig_L2_el_L2_e10_tight, &b_trig_L2_el_L2_e10_tight);
   fChain->SetBranchAddress("trig_L2_el_L2_e15_loose", &trig_L2_el_L2_e15_loose, &b_trig_L2_el_L2_e15_loose);
   fChain->SetBranchAddress("trig_L2_el_L2_e15_loose_IDTrkNoCut", &trig_L2_el_L2_e15_loose_IDTrkNoCut, &b_trig_L2_el_L2_e15_loose_IDTrkNoCut);
   fChain->SetBranchAddress("trig_L2_el_L2_e15_medium", &trig_L2_el_L2_e15_medium, &b_trig_L2_el_L2_e15_medium);
   fChain->SetBranchAddress("trig_L2_el_L2_e15_medium_SiTrk", &trig_L2_el_L2_e15_medium_SiTrk, &b_trig_L2_el_L2_e15_medium_SiTrk);
   fChain->SetBranchAddress("trig_L2_el_L2_e15_medium_TRT", &trig_L2_el_L2_e15_medium_TRT, &b_trig_L2_el_L2_e15_medium_TRT);
   fChain->SetBranchAddress("trig_L2_el_L2_e15_tight", &trig_L2_el_L2_e15_tight, &b_trig_L2_el_L2_e15_tight);
   fChain->SetBranchAddress("trig_L2_el_L2_e18_medium", &trig_L2_el_L2_e18_medium, &b_trig_L2_el_L2_e18_medium);
   fChain->SetBranchAddress("trig_L2_el_L2_e20_loose", &trig_L2_el_L2_e20_loose, &b_trig_L2_el_L2_e20_loose);
   fChain->SetBranchAddress("trig_L2_el_L2_e20_loose_IDTrkNoCut", &trig_L2_el_L2_e20_loose_IDTrkNoCut, &b_trig_L2_el_L2_e20_loose_IDTrkNoCut);
   fChain->SetBranchAddress("trig_L2_el_L2_e20_loose_passEF", &trig_L2_el_L2_e20_loose_passEF, &b_trig_L2_el_L2_e20_loose_passEF);
   fChain->SetBranchAddress("trig_L2_el_L2_e20_loose_passL2", &trig_L2_el_L2_e20_loose_passL2, &b_trig_L2_el_L2_e20_loose_passL2);
   fChain->SetBranchAddress("trig_L2_el_L2_e20_loose_xe20_noMu", &trig_L2_el_L2_e20_loose_xe20_noMu, &b_trig_L2_el_L2_e20_loose_xe20_noMu);
   fChain->SetBranchAddress("trig_L2_el_L2_e20_loose_xe30_noMu", &trig_L2_el_L2_e20_loose_xe30_noMu, &b_trig_L2_el_L2_e20_loose_xe30_noMu);
   fChain->SetBranchAddress("trig_L2_el_L2_e20_medium", &trig_L2_el_L2_e20_medium, &b_trig_L2_el_L2_e20_medium);
   fChain->SetBranchAddress("trig_L2_el_L2_e25_loose", &trig_L2_el_L2_e25_loose, &b_trig_L2_el_L2_e25_loose);
   fChain->SetBranchAddress("trig_L2_el_L2_e30_loose", &trig_L2_el_L2_e30_loose, &b_trig_L2_el_L2_e30_loose);
   fChain->SetBranchAddress("trig_L2_el_L2_e3_loose", &trig_L2_el_L2_e3_loose, &b_trig_L2_el_L2_e3_loose);
   fChain->SetBranchAddress("trig_L2_el_L2_e3_loose_SiTrk", &trig_L2_el_L2_e3_loose_SiTrk, &b_trig_L2_el_L2_e3_loose_SiTrk);
   fChain->SetBranchAddress("trig_L2_el_L2_e3_loose_TRT", &trig_L2_el_L2_e3_loose_TRT, &b_trig_L2_el_L2_e3_loose_TRT);
   fChain->SetBranchAddress("trig_L2_el_L2_e3_medium", &trig_L2_el_L2_e3_medium, &b_trig_L2_el_L2_e3_medium);
   fChain->SetBranchAddress("trig_L2_el_L2_e3_medium_SiTrk", &trig_L2_el_L2_e3_medium_SiTrk, &b_trig_L2_el_L2_e3_medium_SiTrk);
   fChain->SetBranchAddress("trig_L2_el_L2_e3_medium_TRT", &trig_L2_el_L2_e3_medium_TRT, &b_trig_L2_el_L2_e3_medium_TRT);
   fChain->SetBranchAddress("trig_L2_el_L2_e5_NoCut_firstempty", &trig_L2_el_L2_e5_NoCut_firstempty, &b_trig_L2_el_L2_e5_NoCut_firstempty);
   fChain->SetBranchAddress("trig_L2_el_L2_e5_medium", &trig_L2_el_L2_e5_medium, &b_trig_L2_el_L2_e5_medium);
   fChain->SetBranchAddress("trig_L2_el_L2_e5_medium_MV", &trig_L2_el_L2_e5_medium_MV, &b_trig_L2_el_L2_e5_medium_MV);
   fChain->SetBranchAddress("trig_L2_el_L2_e5_medium_SiTrk", &trig_L2_el_L2_e5_medium_SiTrk, &b_trig_L2_el_L2_e5_medium_SiTrk);
   fChain->SetBranchAddress("trig_L2_el_L2_e5_medium_TRT", &trig_L2_el_L2_e5_medium_TRT, &b_trig_L2_el_L2_e5_medium_TRT);
   fChain->SetBranchAddress("trig_L2_el_L2_e5_medium_mu4", &trig_L2_el_L2_e5_medium_mu4, &b_trig_L2_el_L2_e5_medium_mu4);
   fChain->SetBranchAddress("trig_L2_el_L2_e5_tight", &trig_L2_el_L2_e5_tight, &b_trig_L2_el_L2_e5_tight);
   fChain->SetBranchAddress("trig_L2_el_L2_e5_tight_SiTrk", &trig_L2_el_L2_e5_tight_SiTrk, &b_trig_L2_el_L2_e5_tight_SiTrk);
   fChain->SetBranchAddress("trig_L2_el_L2_e5_tight_TRT", &trig_L2_el_L2_e5_tight_TRT, &b_trig_L2_el_L2_e5_tight_TRT);
   fChain->SetBranchAddress("trig_L2_el_L2_e5_tight_e5_NoCut", &trig_L2_el_L2_e5_tight_e5_NoCut, &b_trig_L2_el_L2_e5_tight_e5_NoCut);
   fChain->SetBranchAddress("trig_L2_el_L2_eb_physics", &trig_L2_el_L2_eb_physics, &b_trig_L2_el_L2_eb_physics);
   fChain->SetBranchAddress("trig_L2_el_L2_eb_physics_empty", &trig_L2_el_L2_eb_physics_empty, &b_trig_L2_el_L2_eb_physics_empty);
   fChain->SetBranchAddress("trig_L2_el_L2_eb_physics_firstempty", &trig_L2_el_L2_eb_physics_firstempty, &b_trig_L2_el_L2_eb_physics_firstempty);
   fChain->SetBranchAddress("trig_L2_el_L2_eb_physics_unpaired_iso", &trig_L2_el_L2_eb_physics_unpaired_iso, &b_trig_L2_el_L2_eb_physics_unpaired_iso);
   fChain->SetBranchAddress("trig_L2_el_L2_eb_physics_unpaired_noniso", &trig_L2_el_L2_eb_physics_unpaired_noniso, &b_trig_L2_el_L2_eb_physics_unpaired_noniso);
   fChain->SetBranchAddress("trig_L2_el_L2_eb_random", &trig_L2_el_L2_eb_random, &b_trig_L2_el_L2_eb_random);
   fChain->SetBranchAddress("trig_L2_el_L2_eb_random_empty", &trig_L2_el_L2_eb_random_empty, &b_trig_L2_el_L2_eb_random_empty);
   fChain->SetBranchAddress("trig_L2_el_L2_eb_random_firstempty", &trig_L2_el_L2_eb_random_firstempty, &b_trig_L2_el_L2_eb_random_firstempty);
   fChain->SetBranchAddress("trig_L2_el_L2_eb_random_unpaired_iso", &trig_L2_el_L2_eb_random_unpaired_iso, &b_trig_L2_el_L2_eb_random_unpaired_iso);
   fChain->SetBranchAddress("trig_L2_el_L2_em105_passHLT", &trig_L2_el_L2_em105_passHLT, &b_trig_L2_el_L2_em105_passHLT);
   fChain->SetBranchAddress("trig_L2_el_L2_em3_empty_larcalib", &trig_L2_el_L2_em3_empty_larcalib, &b_trig_L2_el_L2_em3_empty_larcalib);
   fChain->SetBranchAddress("trig_L2_ph_n", &trig_L2_ph_n, &b_trig_L2_ph_n);
   fChain->SetBranchAddress("trig_L2_ph_E", &trig_L2_ph_E, &b_trig_L2_ph_E);
   fChain->SetBranchAddress("trig_L2_ph_Et", &trig_L2_ph_Et, &b_trig_L2_ph_Et);
   fChain->SetBranchAddress("trig_L2_ph_pt", &trig_L2_ph_pt, &b_trig_L2_ph_pt);
   fChain->SetBranchAddress("trig_L2_ph_eta", &trig_L2_ph_eta, &b_trig_L2_ph_eta);
   fChain->SetBranchAddress("trig_L2_ph_phi", &trig_L2_ph_phi, &b_trig_L2_ph_phi);
   fChain->SetBranchAddress("trig_L2_ph_RoIWord", &trig_L2_ph_RoIWord, &b_trig_L2_ph_RoIWord);
   fChain->SetBranchAddress("trig_L2_ph_HadEt1", &trig_L2_ph_HadEt1, &b_trig_L2_ph_HadEt1);
   fChain->SetBranchAddress("trig_L2_ph_Eratio", &trig_L2_ph_Eratio, &b_trig_L2_ph_Eratio);
   fChain->SetBranchAddress("trig_L2_ph_Reta", &trig_L2_ph_Reta, &b_trig_L2_ph_Reta);
   fChain->SetBranchAddress("trig_L2_ph_dPhi", &trig_L2_ph_dPhi, &b_trig_L2_ph_dPhi);
   fChain->SetBranchAddress("trig_L2_ph_dEta", &trig_L2_ph_dEta, &b_trig_L2_ph_dEta);
   fChain->SetBranchAddress("trig_L2_ph_F1", &trig_L2_ph_F1, &b_trig_L2_ph_F1);
   fChain->SetBranchAddress("trig_L2_ph_L2_2g10_loose", &trig_L2_ph_L2_2g10_loose, &b_trig_L2_ph_L2_2g10_loose);
   fChain->SetBranchAddress("trig_L2_ph_L2_2g15_loose", &trig_L2_ph_L2_2g15_loose, &b_trig_L2_ph_L2_2g15_loose);
   fChain->SetBranchAddress("trig_L2_ph_L2_2g5_loose", &trig_L2_ph_L2_2g5_loose, &b_trig_L2_ph_L2_2g5_loose);
   fChain->SetBranchAddress("trig_L2_ph_L2_2g7_loose", &trig_L2_ph_L2_2g7_loose, &b_trig_L2_ph_L2_2g7_loose);
   fChain->SetBranchAddress("trig_L2_ph_L2_g10_loose", &trig_L2_ph_L2_g10_loose, &b_trig_L2_ph_L2_g10_loose);
   fChain->SetBranchAddress("trig_L2_ph_L2_g11_etcut", &trig_L2_ph_L2_g11_etcut, &b_trig_L2_ph_L2_g11_etcut);
   fChain->SetBranchAddress("trig_L2_ph_L2_g15_loose", &trig_L2_ph_L2_g15_loose, &b_trig_L2_ph_L2_g15_loose);
   fChain->SetBranchAddress("trig_L2_ph_L2_g17_etcut", &trig_L2_ph_L2_g17_etcut, &b_trig_L2_ph_L2_g17_etcut);
   fChain->SetBranchAddress("trig_L2_ph_L2_g17_etcut_EFxe20_noMu", &trig_L2_ph_L2_g17_etcut_EFxe20_noMu, &b_trig_L2_ph_L2_g17_etcut_EFxe20_noMu);
   fChain->SetBranchAddress("trig_L2_ph_L2_g17_etcut_EFxe30_noMu", &trig_L2_ph_L2_g17_etcut_EFxe30_noMu, &b_trig_L2_ph_L2_g17_etcut_EFxe30_noMu);
   fChain->SetBranchAddress("trig_L2_ph_L2_g20_loose", &trig_L2_ph_L2_g20_loose, &b_trig_L2_ph_L2_g20_loose);
   fChain->SetBranchAddress("trig_L2_ph_L2_g20_loose_xe20_noMu", &trig_L2_ph_L2_g20_loose_xe20_noMu, &b_trig_L2_ph_L2_g20_loose_xe20_noMu);
   fChain->SetBranchAddress("trig_L2_ph_L2_g20_loose_xe30_noMu", &trig_L2_ph_L2_g20_loose_xe30_noMu, &b_trig_L2_ph_L2_g20_loose_xe30_noMu);
   fChain->SetBranchAddress("trig_L2_ph_L2_g20_tight", &trig_L2_ph_L2_g20_tight, &b_trig_L2_ph_L2_g20_tight);
   fChain->SetBranchAddress("trig_L2_ph_L2_g25_loose_xe30_noMu", &trig_L2_ph_L2_g25_loose_xe30_noMu, &b_trig_L2_ph_L2_g25_loose_xe30_noMu);
   fChain->SetBranchAddress("trig_L2_ph_L2_g30_loose", &trig_L2_ph_L2_g30_loose, &b_trig_L2_ph_L2_g30_loose);
   fChain->SetBranchAddress("trig_L2_ph_L2_g30_tight", &trig_L2_ph_L2_g30_tight, &b_trig_L2_ph_L2_g30_tight);
   fChain->SetBranchAddress("trig_L2_ph_L2_g3_NoCut_unpaired_iso", &trig_L2_ph_L2_g3_NoCut_unpaired_iso, &b_trig_L2_ph_L2_g3_NoCut_unpaired_iso);
   fChain->SetBranchAddress("trig_L2_ph_L2_g3_NoCut_unpaired_noniso", &trig_L2_ph_L2_g3_NoCut_unpaired_noniso, &b_trig_L2_ph_L2_g3_NoCut_unpaired_noniso);
   fChain->SetBranchAddress("trig_L2_ph_L2_g40_loose", &trig_L2_ph_L2_g40_loose, &b_trig_L2_ph_L2_g40_loose);
   fChain->SetBranchAddress("trig_L2_ph_L2_g40_tight", &trig_L2_ph_L2_g40_tight, &b_trig_L2_ph_L2_g40_tight);
   fChain->SetBranchAddress("trig_L2_ph_L2_g50_loose", &trig_L2_ph_L2_g50_loose, &b_trig_L2_ph_L2_g50_loose);
   fChain->SetBranchAddress("trig_L2_ph_L2_g5_NoCut_cosmic", &trig_L2_ph_L2_g5_NoCut_cosmic, &b_trig_L2_ph_L2_g5_NoCut_cosmic);
   fChain->SetBranchAddress("trig_L2_ph_L2_g5_loose", &trig_L2_ph_L2_g5_loose, &b_trig_L2_ph_L2_g5_loose);
   fChain->SetBranchAddress("trig_L2_ph_L2_g7_loose", &trig_L2_ph_L2_g7_loose, &b_trig_L2_ph_L2_g7_loose);
   fChain->SetBranchAddress("trig_EF_emcl_n", &trig_EF_emcl_n, &b_trig_EF_emcl_n);
   fChain->SetBranchAddress("trig_EF_emcl_E", &trig_EF_emcl_E, &b_trig_EF_emcl_E);
   fChain->SetBranchAddress("trig_EF_emcl_pt", &trig_EF_emcl_pt, &b_trig_EF_emcl_pt);
   fChain->SetBranchAddress("trig_EF_emcl_m", &trig_EF_emcl_m, &b_trig_EF_emcl_m);
   fChain->SetBranchAddress("trig_EF_emcl_eta", &trig_EF_emcl_eta, &b_trig_EF_emcl_eta);
   fChain->SetBranchAddress("trig_EF_emcl_phi", &trig_EF_emcl_phi, &b_trig_EF_emcl_phi);
   fChain->SetBranchAddress("trig_EF_emcl_E_em", &trig_EF_emcl_E_em, &b_trig_EF_emcl_E_em);
   fChain->SetBranchAddress("trig_EF_emcl_E_had", &trig_EF_emcl_E_had, &b_trig_EF_emcl_E_had);
   fChain->SetBranchAddress("trig_EF_emcl_firstEdens", &trig_EF_emcl_firstEdens, &b_trig_EF_emcl_firstEdens);
   fChain->SetBranchAddress("trig_EF_emcl_cellmaxfrac", &trig_EF_emcl_cellmaxfrac, &b_trig_EF_emcl_cellmaxfrac);
   fChain->SetBranchAddress("trig_EF_emcl_longitudinal", &trig_EF_emcl_longitudinal, &b_trig_EF_emcl_longitudinal);
   fChain->SetBranchAddress("trig_EF_emcl_secondlambda", &trig_EF_emcl_secondlambda, &b_trig_EF_emcl_secondlambda);
   fChain->SetBranchAddress("trig_EF_emcl_lateral", &trig_EF_emcl_lateral, &b_trig_EF_emcl_lateral);
   fChain->SetBranchAddress("trig_EF_emcl_secondR", &trig_EF_emcl_secondR, &b_trig_EF_emcl_secondR);
   fChain->SetBranchAddress("trig_EF_emcl_centerlambda", &trig_EF_emcl_centerlambda, &b_trig_EF_emcl_centerlambda);
   fChain->SetBranchAddress("trig_EF_emcl_deltaTheta", &trig_EF_emcl_deltaTheta, &b_trig_EF_emcl_deltaTheta);
   fChain->SetBranchAddress("trig_EF_emcl_deltaPhi", &trig_EF_emcl_deltaPhi, &b_trig_EF_emcl_deltaPhi);
   fChain->SetBranchAddress("trig_EF_emcl_time", &trig_EF_emcl_time, &b_trig_EF_emcl_time);
   fChain->SetBranchAddress("trig_EF_emcl_slw_n", &trig_EF_emcl_slw_n, &b_trig_EF_emcl_slw_n);
   fChain->SetBranchAddress("trig_EF_emcl_slw_E", &trig_EF_emcl_slw_E, &b_trig_EF_emcl_slw_E);
   fChain->SetBranchAddress("trig_EF_emcl_slw_pt", &trig_EF_emcl_slw_pt, &b_trig_EF_emcl_slw_pt);
   fChain->SetBranchAddress("trig_EF_emcl_slw_m", &trig_EF_emcl_slw_m, &b_trig_EF_emcl_slw_m);
   fChain->SetBranchAddress("trig_EF_emcl_slw_eta", &trig_EF_emcl_slw_eta, &b_trig_EF_emcl_slw_eta);
   fChain->SetBranchAddress("trig_EF_emcl_slw_phi", &trig_EF_emcl_slw_phi, &b_trig_EF_emcl_slw_phi);
   fChain->SetBranchAddress("trig_EF_emcl_slw_E_em", &trig_EF_emcl_slw_E_em, &b_trig_EF_emcl_slw_E_em);
   fChain->SetBranchAddress("trig_EF_emcl_slw_E_had", &trig_EF_emcl_slw_E_had, &b_trig_EF_emcl_slw_E_had);
   fChain->SetBranchAddress("trig_EF_emcl_slw_firstEdens", &trig_EF_emcl_slw_firstEdens, &b_trig_EF_emcl_slw_firstEdens);
   fChain->SetBranchAddress("trig_EF_emcl_slw_cellmaxfrac", &trig_EF_emcl_slw_cellmaxfrac, &b_trig_EF_emcl_slw_cellmaxfrac);
   fChain->SetBranchAddress("trig_EF_emcl_slw_longitudinal", &trig_EF_emcl_slw_longitudinal, &b_trig_EF_emcl_slw_longitudinal);
   fChain->SetBranchAddress("trig_EF_emcl_slw_secondlambda", &trig_EF_emcl_slw_secondlambda, &b_trig_EF_emcl_slw_secondlambda);
   fChain->SetBranchAddress("trig_EF_emcl_slw_lateral", &trig_EF_emcl_slw_lateral, &b_trig_EF_emcl_slw_lateral);
   fChain->SetBranchAddress("trig_EF_emcl_slw_secondR", &trig_EF_emcl_slw_secondR, &b_trig_EF_emcl_slw_secondR);
   fChain->SetBranchAddress("trig_EF_emcl_slw_centerlambda", &trig_EF_emcl_slw_centerlambda, &b_trig_EF_emcl_slw_centerlambda);
   fChain->SetBranchAddress("trig_EF_emcl_slw_deltaTheta", &trig_EF_emcl_slw_deltaTheta, &b_trig_EF_emcl_slw_deltaTheta);
   fChain->SetBranchAddress("trig_EF_emcl_slw_deltaPhi", &trig_EF_emcl_slw_deltaPhi, &b_trig_EF_emcl_slw_deltaPhi);
   fChain->SetBranchAddress("trig_EF_emcl_slw_time", &trig_EF_emcl_slw_time, &b_trig_EF_emcl_slw_time);
   fChain->SetBranchAddress("trig_EF_el_n", &trig_EF_el_n, &b_trig_EF_el_n);
   fChain->SetBranchAddress("trig_EF_el_E", &trig_EF_el_E, &b_trig_EF_el_E);
   fChain->SetBranchAddress("trig_EF_el_Et", &trig_EF_el_Et, &b_trig_EF_el_Et);
   fChain->SetBranchAddress("trig_EF_el_pt", &trig_EF_el_pt, &b_trig_EF_el_pt);
   fChain->SetBranchAddress("trig_EF_el_m", &trig_EF_el_m, &b_trig_EF_el_m);
   fChain->SetBranchAddress("trig_EF_el_eta", &trig_EF_el_eta, &b_trig_EF_el_eta);
   fChain->SetBranchAddress("trig_EF_el_phi", &trig_EF_el_phi, &b_trig_EF_el_phi);
   fChain->SetBranchAddress("trig_EF_el_px", &trig_EF_el_px, &b_trig_EF_el_px);
   fChain->SetBranchAddress("trig_EF_el_py", &trig_EF_el_py, &b_trig_EF_el_py);
   fChain->SetBranchAddress("trig_EF_el_pz", &trig_EF_el_pz, &b_trig_EF_el_pz);
   fChain->SetBranchAddress("trig_EF_el_charge", &trig_EF_el_charge, &b_trig_EF_el_charge);
   fChain->SetBranchAddress("trig_EF_el_author", &trig_EF_el_author, &b_trig_EF_el_author);
   fChain->SetBranchAddress("trig_EF_el_isEM", &trig_EF_el_isEM, &b_trig_EF_el_isEM);
   fChain->SetBranchAddress("trig_EF_el_loose", &trig_EF_el_loose, &b_trig_EF_el_loose);
   fChain->SetBranchAddress("trig_EF_el_medium", &trig_EF_el_medium, &b_trig_EF_el_medium);
   fChain->SetBranchAddress("trig_EF_el_mediumIso", &trig_EF_el_mediumIso, &b_trig_EF_el_mediumIso);
   fChain->SetBranchAddress("trig_EF_el_tight", &trig_EF_el_tight, &b_trig_EF_el_tight);
   fChain->SetBranchAddress("trig_EF_el_tightIso", &trig_EF_el_tightIso, &b_trig_EF_el_tightIso);
   fChain->SetBranchAddress("trig_EF_el_Ethad", &trig_EF_el_Ethad, &b_trig_EF_el_Ethad);
   fChain->SetBranchAddress("trig_EF_el_Ethad1", &trig_EF_el_Ethad1, &b_trig_EF_el_Ethad1);
   fChain->SetBranchAddress("trig_EF_el_f1", &trig_EF_el_f1, &b_trig_EF_el_f1);
   fChain->SetBranchAddress("trig_EF_el_f1core", &trig_EF_el_f1core, &b_trig_EF_el_f1core);
   fChain->SetBranchAddress("trig_EF_el_Emins1", &trig_EF_el_Emins1, &b_trig_EF_el_Emins1);
   fChain->SetBranchAddress("trig_EF_el_fside", &trig_EF_el_fside, &b_trig_EF_el_fside);
   fChain->SetBranchAddress("trig_EF_el_Emax2", &trig_EF_el_Emax2, &b_trig_EF_el_Emax2);
   fChain->SetBranchAddress("trig_EF_el_ws3", &trig_EF_el_ws3, &b_trig_EF_el_ws3);
   fChain->SetBranchAddress("trig_EF_el_wstot", &trig_EF_el_wstot, &b_trig_EF_el_wstot);
   fChain->SetBranchAddress("trig_EF_el_emaxs1", &trig_EF_el_emaxs1, &b_trig_EF_el_emaxs1);
   fChain->SetBranchAddress("trig_EF_el_deltaEs", &trig_EF_el_deltaEs, &b_trig_EF_el_deltaEs);
   fChain->SetBranchAddress("trig_EF_el_E233", &trig_EF_el_E233, &b_trig_EF_el_E233);
   fChain->SetBranchAddress("trig_EF_el_E237", &trig_EF_el_E237, &b_trig_EF_el_E237);
   fChain->SetBranchAddress("trig_EF_el_E277", &trig_EF_el_E277, &b_trig_EF_el_E277);
   fChain->SetBranchAddress("trig_EF_el_weta2", &trig_EF_el_weta2, &b_trig_EF_el_weta2);
   fChain->SetBranchAddress("trig_EF_el_f3", &trig_EF_el_f3, &b_trig_EF_el_f3);
   fChain->SetBranchAddress("trig_EF_el_f3core", &trig_EF_el_f3core, &b_trig_EF_el_f3core);
   fChain->SetBranchAddress("trig_EF_el_rphiallcalo", &trig_EF_el_rphiallcalo, &b_trig_EF_el_rphiallcalo);
   fChain->SetBranchAddress("trig_EF_el_Etcone45", &trig_EF_el_Etcone45, &b_trig_EF_el_Etcone45);
   fChain->SetBranchAddress("trig_EF_el_Etcone20", &trig_EF_el_Etcone20, &b_trig_EF_el_Etcone20);
   fChain->SetBranchAddress("trig_EF_el_Etcone30", &trig_EF_el_Etcone30, &b_trig_EF_el_Etcone30);
   fChain->SetBranchAddress("trig_EF_el_Etcone40", &trig_EF_el_Etcone40, &b_trig_EF_el_Etcone40);
   fChain->SetBranchAddress("trig_EF_el_pos7", &trig_EF_el_pos7, &b_trig_EF_el_pos7);
   fChain->SetBranchAddress("trig_EF_el_etacorrmag", &trig_EF_el_etacorrmag, &b_trig_EF_el_etacorrmag);
   fChain->SetBranchAddress("trig_EF_el_deltaeta1", &trig_EF_el_deltaeta1, &b_trig_EF_el_deltaeta1);
   fChain->SetBranchAddress("trig_EF_el_deltaeta2", &trig_EF_el_deltaeta2, &b_trig_EF_el_deltaeta2);
   fChain->SetBranchAddress("trig_EF_el_deltaphi2", &trig_EF_el_deltaphi2, &b_trig_EF_el_deltaphi2);
   fChain->SetBranchAddress("trig_EF_el_reta", &trig_EF_el_reta, &b_trig_EF_el_reta);
   fChain->SetBranchAddress("trig_EF_el_rphi", &trig_EF_el_rphi, &b_trig_EF_el_rphi);
   fChain->SetBranchAddress("trig_EF_el_EF_2e10_loose", &trig_EF_el_EF_2e10_loose, &b_trig_EF_el_EF_2e10_loose);
   fChain->SetBranchAddress("trig_EF_el_EF_2e10_medium", &trig_EF_el_EF_2e10_medium, &b_trig_EF_el_EF_2e10_medium);
   fChain->SetBranchAddress("trig_EF_el_EF_2e15_loose", &trig_EF_el_EF_2e15_loose, &b_trig_EF_el_EF_2e15_loose);
   fChain->SetBranchAddress("trig_EF_el_EF_2e3_loose", &trig_EF_el_EF_2e3_loose, &b_trig_EF_el_EF_2e3_loose);
   fChain->SetBranchAddress("trig_EF_el_EF_2e3_loose_SiTrk", &trig_EF_el_EF_2e3_loose_SiTrk, &b_trig_EF_el_EF_2e3_loose_SiTrk);
   fChain->SetBranchAddress("trig_EF_el_EF_2e3_loose_TRT", &trig_EF_el_EF_2e3_loose_TRT, &b_trig_EF_el_EF_2e3_loose_TRT);
   fChain->SetBranchAddress("trig_EF_el_EF_2e3_medium", &trig_EF_el_EF_2e3_medium, &b_trig_EF_el_EF_2e3_medium);
   fChain->SetBranchAddress("trig_EF_el_EF_2e3_medium_SiTrk", &trig_EF_el_EF_2e3_medium_SiTrk, &b_trig_EF_el_EF_2e3_medium_SiTrk);
   fChain->SetBranchAddress("trig_EF_el_EF_2e3_medium_TRT", &trig_EF_el_EF_2e3_medium_TRT, &b_trig_EF_el_EF_2e3_medium_TRT);
   fChain->SetBranchAddress("trig_EF_el_EF_2e3_tight", &trig_EF_el_EF_2e3_tight, &b_trig_EF_el_EF_2e3_tight);
   fChain->SetBranchAddress("trig_EF_el_EF_2e5_medium", &trig_EF_el_EF_2e5_medium, &b_trig_EF_el_EF_2e5_medium);
   fChain->SetBranchAddress("trig_EF_el_EF_2e5_medium_SiTrk", &trig_EF_el_EF_2e5_medium_SiTrk, &b_trig_EF_el_EF_2e5_medium_SiTrk);
   fChain->SetBranchAddress("trig_EF_el_EF_2e5_medium_TRT", &trig_EF_el_EF_2e5_medium_TRT, &b_trig_EF_el_EF_2e5_medium_TRT);
   fChain->SetBranchAddress("trig_EF_el_EF_2e5_tight", &trig_EF_el_EF_2e5_tight, &b_trig_EF_el_EF_2e5_tight);
   fChain->SetBranchAddress("trig_EF_el_EF_e10_NoCut", &trig_EF_el_EF_e10_NoCut, &b_trig_EF_el_EF_e10_NoCut);
   fChain->SetBranchAddress("trig_EF_el_EF_e10_loose", &trig_EF_el_EF_e10_loose, &b_trig_EF_el_EF_e10_loose);
   fChain->SetBranchAddress("trig_EF_el_EF_e10_loose_mu10", &trig_EF_el_EF_e10_loose_mu10, &b_trig_EF_el_EF_e10_loose_mu10);
   fChain->SetBranchAddress("trig_EF_el_EF_e10_loose_mu6", &trig_EF_el_EF_e10_loose_mu6, &b_trig_EF_el_EF_e10_loose_mu6);
   fChain->SetBranchAddress("trig_EF_el_EF_e10_medium", &trig_EF_el_EF_e10_medium, &b_trig_EF_el_EF_e10_medium);
   fChain->SetBranchAddress("trig_EF_el_EF_e10_medium_IDTrkNoCut", &trig_EF_el_EF_e10_medium_IDTrkNoCut, &b_trig_EF_el_EF_e10_medium_IDTrkNoCut);
   fChain->SetBranchAddress("trig_EF_el_EF_e10_medium_SiTrk", &trig_EF_el_EF_e10_medium_SiTrk, &b_trig_EF_el_EF_e10_medium_SiTrk);
   fChain->SetBranchAddress("trig_EF_el_EF_e10_medium_TRT", &trig_EF_el_EF_e10_medium_TRT, &b_trig_EF_el_EF_e10_medium_TRT);
   fChain->SetBranchAddress("trig_EF_el_EF_e10_tight", &trig_EF_el_EF_e10_tight, &b_trig_EF_el_EF_e10_tight);
   fChain->SetBranchAddress("trig_EF_el_EF_e15_loose", &trig_EF_el_EF_e15_loose, &b_trig_EF_el_EF_e15_loose);
   fChain->SetBranchAddress("trig_EF_el_EF_e15_loose_IDTrkNoCut", &trig_EF_el_EF_e15_loose_IDTrkNoCut, &b_trig_EF_el_EF_e15_loose_IDTrkNoCut);
   fChain->SetBranchAddress("trig_EF_el_EF_e15_medium", &trig_EF_el_EF_e15_medium, &b_trig_EF_el_EF_e15_medium);
   fChain->SetBranchAddress("trig_EF_el_EF_e15_medium_SiTrk", &trig_EF_el_EF_e15_medium_SiTrk, &b_trig_EF_el_EF_e15_medium_SiTrk);
   fChain->SetBranchAddress("trig_EF_el_EF_e15_medium_TRT", &trig_EF_el_EF_e15_medium_TRT, &b_trig_EF_el_EF_e15_medium_TRT);
   fChain->SetBranchAddress("trig_EF_el_EF_e15_tight", &trig_EF_el_EF_e15_tight, &b_trig_EF_el_EF_e15_tight);
   fChain->SetBranchAddress("trig_EF_el_EF_e18_medium", &trig_EF_el_EF_e18_medium, &b_trig_EF_el_EF_e18_medium);
   fChain->SetBranchAddress("trig_EF_el_EF_e20_loose", &trig_EF_el_EF_e20_loose, &b_trig_EF_el_EF_e20_loose);
   fChain->SetBranchAddress("trig_EF_el_EF_e20_loose_IDTrkNoCut", &trig_EF_el_EF_e20_loose_IDTrkNoCut, &b_trig_EF_el_EF_e20_loose_IDTrkNoCut);
   fChain->SetBranchAddress("trig_EF_el_EF_e20_loose_passEF", &trig_EF_el_EF_e20_loose_passEF, &b_trig_EF_el_EF_e20_loose_passEF);
   fChain->SetBranchAddress("trig_EF_el_EF_e20_loose_passL2", &trig_EF_el_EF_e20_loose_passL2, &b_trig_EF_el_EF_e20_loose_passL2);
   fChain->SetBranchAddress("trig_EF_el_EF_e20_loose_xe20_noMu", &trig_EF_el_EF_e20_loose_xe20_noMu, &b_trig_EF_el_EF_e20_loose_xe20_noMu);
   fChain->SetBranchAddress("trig_EF_el_EF_e20_loose_xe30_noMu", &trig_EF_el_EF_e20_loose_xe30_noMu, &b_trig_EF_el_EF_e20_loose_xe30_noMu);
   fChain->SetBranchAddress("trig_EF_el_EF_e20_medium", &trig_EF_el_EF_e20_medium, &b_trig_EF_el_EF_e20_medium);
   fChain->SetBranchAddress("trig_EF_el_EF_e25_loose", &trig_EF_el_EF_e25_loose, &b_trig_EF_el_EF_e25_loose);
   fChain->SetBranchAddress("trig_EF_el_EF_e30_loose", &trig_EF_el_EF_e30_loose, &b_trig_EF_el_EF_e30_loose);
   fChain->SetBranchAddress("trig_EF_el_EF_e3_loose", &trig_EF_el_EF_e3_loose, &b_trig_EF_el_EF_e3_loose);
   fChain->SetBranchAddress("trig_EF_el_EF_e3_loose_SiTrk", &trig_EF_el_EF_e3_loose_SiTrk, &b_trig_EF_el_EF_e3_loose_SiTrk);
   fChain->SetBranchAddress("trig_EF_el_EF_e3_loose_TRT", &trig_EF_el_EF_e3_loose_TRT, &b_trig_EF_el_EF_e3_loose_TRT);
   fChain->SetBranchAddress("trig_EF_el_EF_e3_medium", &trig_EF_el_EF_e3_medium, &b_trig_EF_el_EF_e3_medium);
   fChain->SetBranchAddress("trig_EF_el_EF_e3_medium_SiTrk", &trig_EF_el_EF_e3_medium_SiTrk, &b_trig_EF_el_EF_e3_medium_SiTrk);
   fChain->SetBranchAddress("trig_EF_el_EF_e3_medium_TRT", &trig_EF_el_EF_e3_medium_TRT, &b_trig_EF_el_EF_e3_medium_TRT);
   fChain->SetBranchAddress("trig_EF_el_EF_e5_NoCut_firstempty", &trig_EF_el_EF_e5_NoCut_firstempty, &b_trig_EF_el_EF_e5_NoCut_firstempty);
   fChain->SetBranchAddress("trig_EF_el_EF_e5_medium", &trig_EF_el_EF_e5_medium, &b_trig_EF_el_EF_e5_medium);
   fChain->SetBranchAddress("trig_EF_el_EF_e5_medium_MV", &trig_EF_el_EF_e5_medium_MV, &b_trig_EF_el_EF_e5_medium_MV);
   fChain->SetBranchAddress("trig_EF_el_EF_e5_medium_SiTrk", &trig_EF_el_EF_e5_medium_SiTrk, &b_trig_EF_el_EF_e5_medium_SiTrk);
   fChain->SetBranchAddress("trig_EF_el_EF_e5_medium_TRT", &trig_EF_el_EF_e5_medium_TRT, &b_trig_EF_el_EF_e5_medium_TRT);
   fChain->SetBranchAddress("trig_EF_el_EF_e5_medium_mu4", &trig_EF_el_EF_e5_medium_mu4, &b_trig_EF_el_EF_e5_medium_mu4);
   fChain->SetBranchAddress("trig_EF_el_EF_e5_tight", &trig_EF_el_EF_e5_tight, &b_trig_EF_el_EF_e5_tight);
   fChain->SetBranchAddress("trig_EF_el_EF_e5_tight_SiTrk", &trig_EF_el_EF_e5_tight_SiTrk, &b_trig_EF_el_EF_e5_tight_SiTrk);
   fChain->SetBranchAddress("trig_EF_el_EF_e5_tight_TRT", &trig_EF_el_EF_e5_tight_TRT, &b_trig_EF_el_EF_e5_tight_TRT);
   fChain->SetBranchAddress("trig_EF_el_EF_e5_tight_e5_NoCut", &trig_EF_el_EF_e5_tight_e5_NoCut, &b_trig_EF_el_EF_e5_tight_e5_NoCut);
   fChain->SetBranchAddress("trig_EF_el_EF_eb_physics", &trig_EF_el_EF_eb_physics, &b_trig_EF_el_EF_eb_physics);
   fChain->SetBranchAddress("trig_EF_el_EF_eb_physics_empty", &trig_EF_el_EF_eb_physics_empty, &b_trig_EF_el_EF_eb_physics_empty);
   fChain->SetBranchAddress("trig_EF_el_EF_eb_physics_firstempty", &trig_EF_el_EF_eb_physics_firstempty, &b_trig_EF_el_EF_eb_physics_firstempty);
   fChain->SetBranchAddress("trig_EF_el_EF_eb_physics_unpaired_iso", &trig_EF_el_EF_eb_physics_unpaired_iso, &b_trig_EF_el_EF_eb_physics_unpaired_iso);
   fChain->SetBranchAddress("trig_EF_el_EF_eb_physics_unpaired_noniso", &trig_EF_el_EF_eb_physics_unpaired_noniso, &b_trig_EF_el_EF_eb_physics_unpaired_noniso);
   fChain->SetBranchAddress("trig_EF_el_EF_eb_random", &trig_EF_el_EF_eb_random, &b_trig_EF_el_EF_eb_random);
   fChain->SetBranchAddress("trig_EF_el_EF_eb_random_empty", &trig_EF_el_EF_eb_random_empty, &b_trig_EF_el_EF_eb_random_empty);
   fChain->SetBranchAddress("trig_EF_el_EF_eb_random_firstempty", &trig_EF_el_EF_eb_random_firstempty, &b_trig_EF_el_EF_eb_random_firstempty);
   fChain->SetBranchAddress("trig_EF_el_EF_eb_random_unpaired_iso", &trig_EF_el_EF_eb_random_unpaired_iso, &b_trig_EF_el_EF_eb_random_unpaired_iso);
   fChain->SetBranchAddress("trig_EF_el_EF_em105_passHLT", &trig_EF_el_EF_em105_passHLT, &b_trig_EF_el_EF_em105_passHLT);
   fChain->SetBranchAddress("trig_EF_ph_n", &trig_EF_ph_n, &b_trig_EF_ph_n);
   fChain->SetBranchAddress("trig_EF_ph_E", &trig_EF_ph_E, &b_trig_EF_ph_E);
   fChain->SetBranchAddress("trig_EF_ph_Et", &trig_EF_ph_Et, &b_trig_EF_ph_Et);
   fChain->SetBranchAddress("trig_EF_ph_pt", &trig_EF_ph_pt, &b_trig_EF_ph_pt);
   fChain->SetBranchAddress("trig_EF_ph_m", &trig_EF_ph_m, &b_trig_EF_ph_m);
   fChain->SetBranchAddress("trig_EF_ph_eta", &trig_EF_ph_eta, &b_trig_EF_ph_eta);
   fChain->SetBranchAddress("trig_EF_ph_phi", &trig_EF_ph_phi, &b_trig_EF_ph_phi);
   fChain->SetBranchAddress("trig_EF_ph_px", &trig_EF_ph_px, &b_trig_EF_ph_px);
   fChain->SetBranchAddress("trig_EF_ph_py", &trig_EF_ph_py, &b_trig_EF_ph_py);
   fChain->SetBranchAddress("trig_EF_ph_pz", &trig_EF_ph_pz, &b_trig_EF_ph_pz);
   fChain->SetBranchAddress("trig_EF_ph_EF_2g10_loose", &trig_EF_ph_EF_2g10_loose, &b_trig_EF_ph_EF_2g10_loose);
   fChain->SetBranchAddress("trig_EF_ph_EF_2g15_loose", &trig_EF_ph_EF_2g15_loose, &b_trig_EF_ph_EF_2g15_loose);
   fChain->SetBranchAddress("trig_EF_ph_EF_2g5_loose", &trig_EF_ph_EF_2g5_loose, &b_trig_EF_ph_EF_2g5_loose);
   fChain->SetBranchAddress("trig_EF_ph_EF_2g7_loose", &trig_EF_ph_EF_2g7_loose, &b_trig_EF_ph_EF_2g7_loose);
   fChain->SetBranchAddress("trig_EF_ph_EF_g10_loose", &trig_EF_ph_EF_g10_loose, &b_trig_EF_ph_EF_g10_loose);
   fChain->SetBranchAddress("trig_EF_ph_EF_g10_loose_larcalib", &trig_EF_ph_EF_g10_loose_larcalib, &b_trig_EF_ph_EF_g10_loose_larcalib);
   fChain->SetBranchAddress("trig_EF_ph_EF_g11_etcut", &trig_EF_ph_EF_g11_etcut, &b_trig_EF_ph_EF_g11_etcut);
   fChain->SetBranchAddress("trig_EF_ph_EF_g15_loose", &trig_EF_ph_EF_g15_loose, &b_trig_EF_ph_EF_g15_loose);
   fChain->SetBranchAddress("trig_EF_ph_EF_g17_etcut", &trig_EF_ph_EF_g17_etcut, &b_trig_EF_ph_EF_g17_etcut);
   fChain->SetBranchAddress("trig_EF_ph_EF_g17_etcut_EFxe20_noMu", &trig_EF_ph_EF_g17_etcut_EFxe20_noMu, &b_trig_EF_ph_EF_g17_etcut_EFxe20_noMu);
   fChain->SetBranchAddress("trig_EF_ph_EF_g17_etcut_EFxe30_noMu", &trig_EF_ph_EF_g17_etcut_EFxe30_noMu, &b_trig_EF_ph_EF_g17_etcut_EFxe30_noMu);
   fChain->SetBranchAddress("trig_EF_ph_EF_g20_loose", &trig_EF_ph_EF_g20_loose, &b_trig_EF_ph_EF_g20_loose);
   fChain->SetBranchAddress("trig_EF_ph_EF_g20_loose_larcalib", &trig_EF_ph_EF_g20_loose_larcalib, &b_trig_EF_ph_EF_g20_loose_larcalib);
   fChain->SetBranchAddress("trig_EF_ph_EF_g20_loose_xe20_noMu", &trig_EF_ph_EF_g20_loose_xe20_noMu, &b_trig_EF_ph_EF_g20_loose_xe20_noMu);
   fChain->SetBranchAddress("trig_EF_ph_EF_g20_loose_xe30_noMu", &trig_EF_ph_EF_g20_loose_xe30_noMu, &b_trig_EF_ph_EF_g20_loose_xe30_noMu);
   fChain->SetBranchAddress("trig_EF_ph_EF_g20_tight", &trig_EF_ph_EF_g20_tight, &b_trig_EF_ph_EF_g20_tight);
   fChain->SetBranchAddress("trig_EF_ph_EF_g25_loose_xe30_noMu", &trig_EF_ph_EF_g25_loose_xe30_noMu, &b_trig_EF_ph_EF_g25_loose_xe30_noMu);
   fChain->SetBranchAddress("trig_EF_ph_EF_g30_loose", &trig_EF_ph_EF_g30_loose, &b_trig_EF_ph_EF_g30_loose);
   fChain->SetBranchAddress("trig_EF_ph_EF_g30_tight", &trig_EF_ph_EF_g30_tight, &b_trig_EF_ph_EF_g30_tight);
   fChain->SetBranchAddress("trig_EF_ph_EF_g3_NoCut_unpaired_iso", &trig_EF_ph_EF_g3_NoCut_unpaired_iso, &b_trig_EF_ph_EF_g3_NoCut_unpaired_iso);
   fChain->SetBranchAddress("trig_EF_ph_EF_g3_NoCut_unpaired_noniso", &trig_EF_ph_EF_g3_NoCut_unpaired_noniso, &b_trig_EF_ph_EF_g3_NoCut_unpaired_noniso);
   fChain->SetBranchAddress("trig_EF_ph_EF_g40_loose", &trig_EF_ph_EF_g40_loose, &b_trig_EF_ph_EF_g40_loose);
   fChain->SetBranchAddress("trig_EF_ph_EF_g40_loose_larcalib", &trig_EF_ph_EF_g40_loose_larcalib, &b_trig_EF_ph_EF_g40_loose_larcalib);
   fChain->SetBranchAddress("trig_EF_ph_EF_g40_tight", &trig_EF_ph_EF_g40_tight, &b_trig_EF_ph_EF_g40_tight);
   fChain->SetBranchAddress("trig_EF_ph_EF_g50_loose", &trig_EF_ph_EF_g50_loose, &b_trig_EF_ph_EF_g50_loose);
   fChain->SetBranchAddress("trig_EF_ph_EF_g50_loose_larcalib", &trig_EF_ph_EF_g50_loose_larcalib, &b_trig_EF_ph_EF_g50_loose_larcalib);
   fChain->SetBranchAddress("trig_EF_ph_EF_g5_NoCut_cosmic", &trig_EF_ph_EF_g5_NoCut_cosmic, &b_trig_EF_ph_EF_g5_NoCut_cosmic);
   fChain->SetBranchAddress("trig_EF_ph_EF_g5_loose", &trig_EF_ph_EF_g5_loose, &b_trig_EF_ph_EF_g5_loose);
   fChain->SetBranchAddress("trig_EF_ph_EF_g5_loose_larcalib", &trig_EF_ph_EF_g5_loose_larcalib, &b_trig_EF_ph_EF_g5_loose_larcalib);
   fChain->SetBranchAddress("trig_EF_ph_EF_g7_loose", &trig_EF_ph_EF_g7_loose, &b_trig_EF_ph_EF_g7_loose);
   fChain->SetBranchAddress("trig_Nav_n", &trig_Nav_n, &b_trig_Nav_n);
   fChain->SetBranchAddress("trig_Nav_chain_ChainId", &trig_Nav_chain_ChainId, &b_trig_Nav_chain_ChainId);
   fChain->SetBranchAddress("trig_Nav_chain_RoIType", &trig_Nav_chain_RoIType, &b_trig_Nav_chain_RoIType);
   fChain->SetBranchAddress("trig_Nav_chain_RoIIndex", &trig_Nav_chain_RoIIndex, &b_trig_Nav_chain_RoIIndex);
   fChain->SetBranchAddress("trig_RoI_L2_e_n", &trig_RoI_L2_e_n, &b_trig_RoI_L2_e_n);
   fChain->SetBranchAddress("trig_RoI_L2_e_type", &trig_RoI_L2_e_type, &b_trig_RoI_L2_e_type);
   fChain->SetBranchAddress("trig_RoI_L2_e_lastStep", &trig_RoI_L2_e_lastStep, &b_trig_RoI_L2_e_lastStep);
   fChain->SetBranchAddress("trig_RoI_L2_e_TrigEMCluster", &trig_RoI_L2_e_TrigEMCluster, &b_trig_RoI_L2_e_TrigEMCluster);
   fChain->SetBranchAddress("trig_RoI_L2_e_TrigEMClusterStatus", &trig_RoI_L2_e_TrigEMClusterStatus, &b_trig_RoI_L2_e_TrigEMClusterStatus);
   fChain->SetBranchAddress("trig_RoI_L2_e_EmTau_ROI", &trig_RoI_L2_e_EmTau_ROI, &b_trig_RoI_L2_e_EmTau_ROI);
   fChain->SetBranchAddress("trig_RoI_L2_e_EmTau_ROIStatus", &trig_RoI_L2_e_EmTau_ROIStatus, &b_trig_RoI_L2_e_EmTau_ROIStatus);
   fChain->SetBranchAddress("trig_RoI_L2_e_TrigInDetTrackCollection_TrigSiTrack_eGamma", &trig_RoI_L2_e_TrigInDetTrackCollection_TrigSiTrack_eGamma, &b_trig_RoI_L2_e_TrigInDetTrackCollection_TrigSiTrack_eGamma);
   fChain->SetBranchAddress("trig_RoI_L2_e_TrigInDetTrackCollection_TrigSiTrack_eGammaStatus", &trig_RoI_L2_e_TrigInDetTrackCollection_TrigSiTrack_eGammaStatus, &b_trig_RoI_L2_e_TrigInDetTrackCollection_TrigSiTrack_eGammaStatus);
   fChain->SetBranchAddress("trig_RoI_L2_e_TrigInDetTrackCollection_TrigIDSCAN_eGamma", &trig_RoI_L2_e_TrigInDetTrackCollection_TrigIDSCAN_eGamma, &b_trig_RoI_L2_e_TrigInDetTrackCollection_TrigIDSCAN_eGamma);
   fChain->SetBranchAddress("trig_RoI_L2_e_TrigInDetTrackCollection_TrigIDSCAN_eGammaStatus", &trig_RoI_L2_e_TrigInDetTrackCollection_TrigIDSCAN_eGammaStatus, &b_trig_RoI_L2_e_TrigInDetTrackCollection_TrigIDSCAN_eGammaStatus);
   fChain->SetBranchAddress("trig_RoI_L2_e_TrigElectronContainer", &trig_RoI_L2_e_TrigElectronContainer, &b_trig_RoI_L2_e_TrigElectronContainer);
   fChain->SetBranchAddress("trig_RoI_L2_e_TrigElectronContainerStatus", &trig_RoI_L2_e_TrigElectronContainerStatus, &b_trig_RoI_L2_e_TrigElectronContainerStatus);
   fChain->SetBranchAddress("trig_RoI_EF_e_n", &trig_RoI_EF_e_n, &b_trig_RoI_EF_e_n);
   fChain->SetBranchAddress("trig_RoI_EF_e_type", &trig_RoI_EF_e_type, &b_trig_RoI_EF_e_type);
   fChain->SetBranchAddress("trig_RoI_EF_e_lastStep", &trig_RoI_EF_e_lastStep, &b_trig_RoI_EF_e_lastStep);
   fChain->SetBranchAddress("trig_RoI_EF_e_EmTau_ROI", &trig_RoI_EF_e_EmTau_ROI, &b_trig_RoI_EF_e_EmTau_ROI);
   fChain->SetBranchAddress("trig_RoI_EF_e_EmTau_ROIStatus", &trig_RoI_EF_e_EmTau_ROIStatus, &b_trig_RoI_EF_e_EmTau_ROIStatus);
   fChain->SetBranchAddress("trig_DB_SMK", &trig_DB_SMK, &b_trig_DB_SMK);
   fChain->SetBranchAddress("trig_DB_L1PSK", &trig_DB_L1PSK, &b_trig_DB_L1PSK);
   fChain->SetBranchAddress("trig_DB_HLTPSK", &trig_DB_HLTPSK, &b_trig_DB_HLTPSK);
   fChain->SetBranchAddress("trig_L1_esum_thrNames", &trig_L1_esum_thrNames, &b_trig_L1_esum_thrNames);
   fChain->SetBranchAddress("trig_L1_esum_energyX", &trig_L1_esum_energyX, &b_trig_L1_esum_energyX);
   fChain->SetBranchAddress("trig_L1_esum_energyY", &trig_L1_esum_energyY, &b_trig_L1_esum_energyY);
   fChain->SetBranchAddress("trig_L1_esum_energyT", &trig_L1_esum_energyT, &b_trig_L1_esum_energyT);
   fChain->SetBranchAddress("trig_L1_esum_overflowX", &trig_L1_esum_overflowX, &b_trig_L1_esum_overflowX);
   fChain->SetBranchAddress("trig_L1_esum_overflowY", &trig_L1_esum_overflowY, &b_trig_L1_esum_overflowY);
   fChain->SetBranchAddress("trig_L1_esum_overflowT", &trig_L1_esum_overflowT, &b_trig_L1_esum_overflowT);
   fChain->SetBranchAddress("trig_L1_esum_RoIWord0", &trig_L1_esum_RoIWord0, &b_trig_L1_esum_RoIWord0);
   fChain->SetBranchAddress("trig_L1_esum_RoIWord1", &trig_L1_esum_RoIWord1, &b_trig_L1_esum_RoIWord1);
   fChain->SetBranchAddress("trig_L1_esum_RoIWord2", &trig_L1_esum_RoIWord2, &b_trig_L1_esum_RoIWord2);
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
   fChain->SetBranchAddress("trig_bgCode", &trig_bgCode, &b_trig_bgCode);
   fChain->SetBranchAddress("MET_Goodness_CalClusForwBackw_pass", &MET_Goodness_CalClusForwBackw_pass, &b_MET_Goodness_CalClusForwBackw_pass);
   fChain->SetBranchAddress("MET_Goodness_CalClusUpDown_pass", &MET_Goodness_CalClusUpDown_pass, &b_MET_Goodness_CalClusUpDown_pass);
   fChain->SetBranchAddress("MET_Goodness_Calo_countA", &MET_Goodness_Calo_countA, &b_MET_Goodness_Calo_countA);
   fChain->SetBranchAddress("MET_Goodness_Calo_countC", &MET_Goodness_Calo_countC, &b_MET_Goodness_Calo_countC);
   fChain->SetBranchAddress("MET_Goodness_Calo_pass", &MET_Goodness_Calo_pass, &b_MET_Goodness_Calo_pass);
   fChain->SetBranchAddress("MET_Goodness_IsCollisionCandidate", &MET_Goodness_IsCollisionCandidate, &b_MET_Goodness_IsCollisionCandidate);
   fChain->SetBranchAddress("MET_Goodness_MBTS_countA", &MET_Goodness_MBTS_countA, &b_MET_Goodness_MBTS_countA);
   fChain->SetBranchAddress("MET_Goodness_MBTS_countC", &MET_Goodness_MBTS_countC, &b_MET_Goodness_MBTS_countC);
   fChain->SetBranchAddress("MET_Goodness_MBTS_pass", &MET_Goodness_MBTS_pass, &b_MET_Goodness_MBTS_pass);
   fChain->SetBranchAddress("MET_Goodness_MuonSp0Hits", &MET_Goodness_MuonSp0Hits, &b_MET_Goodness_MuonSp0Hits);
   fChain->SetBranchAddress("MET_Goodness_MuonSp1Hits", &MET_Goodness_MuonSp1Hits, &b_MET_Goodness_MuonSp1Hits);
   fChain->SetBranchAddress("MET_Goodness_MuonSpTotHits", &MET_Goodness_MuonSpTotHits, &b_MET_Goodness_MuonSpTotHits);
   fChain->SetBranchAddress("MET_Goodness_OkayLB", &MET_Goodness_OkayLB, &b_MET_Goodness_OkayLB);
   fChain->SetBranchAddress("MET_Goodness_CalClusForwBackw_timeDiff", &MET_Goodness_CalClusForwBackw_timeDiff, &b_MET_Goodness_CalClusForwBackw_timeDiff);
   fChain->SetBranchAddress("MET_Goodness_CalClusUpDown_timeDiff", &MET_Goodness_CalClusUpDown_timeDiff, &b_MET_Goodness_CalClusUpDown_timeDiff);
   fChain->SetBranchAddress("MET_Goodness_CalClus_InTimeFraction", &MET_Goodness_CalClus_InTimeFraction, &b_MET_Goodness_CalClus_InTimeFraction);
   fChain->SetBranchAddress("MET_Goodness_CalClus_OutTimeEnergy", &MET_Goodness_CalClus_OutTimeEnergy, &b_MET_Goodness_CalClus_OutTimeEnergy);
   fChain->SetBranchAddress("MET_Goodness_CalClus_eventTime", &MET_Goodness_CalClus_eventTime, &b_MET_Goodness_CalClus_eventTime);
   fChain->SetBranchAddress("MET_Goodness_CalClus_ootEnergy10", &MET_Goodness_CalClus_ootEnergy10, &b_MET_Goodness_CalClus_ootEnergy10);
   fChain->SetBranchAddress("MET_Goodness_CalClus_ootEnergy15", &MET_Goodness_CalClus_ootEnergy15, &b_MET_Goodness_CalClus_ootEnergy15);
   fChain->SetBranchAddress("MET_Goodness_CalClus_ootEnergy20", &MET_Goodness_CalClus_ootEnergy20, &b_MET_Goodness_CalClus_ootEnergy20);
   fChain->SetBranchAddress("MET_Goodness_CalClus_ootEnergy25", &MET_Goodness_CalClus_ootEnergy25, &b_MET_Goodness_CalClus_ootEnergy25);
   fChain->SetBranchAddress("MET_Goodness_CalClus_ootFraction10", &MET_Goodness_CalClus_ootFraction10, &b_MET_Goodness_CalClus_ootFraction10);
   fChain->SetBranchAddress("MET_Goodness_CalClus_ootFraction15", &MET_Goodness_CalClus_ootFraction15, &b_MET_Goodness_CalClus_ootFraction15);
   fChain->SetBranchAddress("MET_Goodness_CalClus_ootFraction20", &MET_Goodness_CalClus_ootFraction20, &b_MET_Goodness_CalClus_ootFraction20);
   fChain->SetBranchAddress("MET_Goodness_CalClus_ootFraction25", &MET_Goodness_CalClus_ootFraction25, &b_MET_Goodness_CalClus_ootFraction25);
   fChain->SetBranchAddress("MET_Goodness_CalClus_timeA", &MET_Goodness_CalClus_timeA, &b_MET_Goodness_CalClus_timeA);
   fChain->SetBranchAddress("MET_Goodness_CalClus_timeC", &MET_Goodness_CalClus_timeC, &b_MET_Goodness_CalClus_timeC);
   fChain->SetBranchAddress("MET_Goodness_Calo_timeA", &MET_Goodness_Calo_timeA, &b_MET_Goodness_Calo_timeA);
   fChain->SetBranchAddress("MET_Goodness_Calo_timeC", &MET_Goodness_Calo_timeC, &b_MET_Goodness_Calo_timeC);
   fChain->SetBranchAddress("MET_Goodness_Calo_timeDiff", &MET_Goodness_Calo_timeDiff, &b_MET_Goodness_Calo_timeDiff);
   fChain->SetBranchAddress("MET_Goodness_EtoverRootSigmaEt", &MET_Goodness_EtoverRootSigmaEt, &b_MET_Goodness_EtoverRootSigmaEt);
   fChain->SetBranchAddress("MET_Goodness_EventEMFraction", &MET_Goodness_EventEMFraction, &b_MET_Goodness_EventEMFraction);
   fChain->SetBranchAddress("MET_Goodness_LArNoisyROSummary", &MET_Goodness_LArNoisyROSummary, &b_MET_Goodness_LArNoisyROSummary);
   fChain->SetBranchAddress("MET_Goodness_MBTS_timeA", &MET_Goodness_MBTS_timeA, &b_MET_Goodness_MBTS_timeA);
   fChain->SetBranchAddress("MET_Goodness_MBTS_timeC", &MET_Goodness_MBTS_timeC, &b_MET_Goodness_MBTS_timeC);
   fChain->SetBranchAddress("MET_Goodness_MBTS_timeDiff", &MET_Goodness_MBTS_timeDiff, &b_MET_Goodness_MBTS_timeDiff);
   fChain->SetBranchAddress("MET_Goodness_MET_CorrTopo_etx", &MET_Goodness_MET_CorrTopo_etx, &b_MET_Goodness_MET_CorrTopo_etx);
   fChain->SetBranchAddress("MET_Goodness_MET_CorrTopo_ety", &MET_Goodness_MET_CorrTopo_ety, &b_MET_Goodness_MET_CorrTopo_ety);
   fChain->SetBranchAddress("MET_Goodness_MET_CorrTopo_sumet", &MET_Goodness_MET_CorrTopo_sumet, &b_MET_Goodness_MET_CorrTopo_sumet);
   fChain->SetBranchAddress("MET_Goodness_MET_Topo_etx", &MET_Goodness_MET_Topo_etx, &b_MET_Goodness_MET_Topo_etx);
   fChain->SetBranchAddress("MET_Goodness_MET_Topo_ety", &MET_Goodness_MET_Topo_ety, &b_MET_Goodness_MET_Topo_ety);
   fChain->SetBranchAddress("MET_Goodness_MET_Topo_sumet", &MET_Goodness_MET_Topo_sumet, &b_MET_Goodness_MET_Topo_sumet);
   fChain->SetBranchAddress("MET_Goodness_MuonSp0Eta", &MET_Goodness_MuonSp0Eta, &b_MET_Goodness_MuonSp0Eta);
   fChain->SetBranchAddress("MET_Goodness_MuonSp0Phi", &MET_Goodness_MuonSp0Phi, &b_MET_Goodness_MuonSp0Phi);
   fChain->SetBranchAddress("MET_Goodness_MuonSp1Eta", &MET_Goodness_MuonSp1Eta, &b_MET_Goodness_MuonSp1Eta);
   fChain->SetBranchAddress("MET_Goodness_MuonSp1Phi", &MET_Goodness_MuonSp1Phi, &b_MET_Goodness_MuonSp1Phi);
   fChain->SetBranchAddress("MET_Goodness_MuonTRTTiming", &MET_Goodness_MuonTRTTiming, &b_MET_Goodness_MuonTRTTiming);
   fChain->SetBranchAddress("MET_Goodness_BCH_CORR_CELL_Jet", &MET_Goodness_BCH_CORR_CELL_Jet, &b_MET_Goodness_BCH_CORR_CELL_Jet);
   fChain->SetBranchAddress("MET_Goodness_BCH_CORR_JET", &MET_Goodness_BCH_CORR_JET, &b_MET_Goodness_BCH_CORR_JET);
   fChain->SetBranchAddress("MET_Goodness_BCH_CORR_JET_FORCELL_Jet", &MET_Goodness_BCH_CORR_JET_FORCELL_Jet, &b_MET_Goodness_BCH_CORR_JET_FORCELL_Jet);
   fChain->SetBranchAddress("MET_Goodness_ChargeFraction_Jet", &MET_Goodness_ChargeFraction_Jet, &b_MET_Goodness_ChargeFraction_Jet);
   fChain->SetBranchAddress("MET_Goodness_DeltaEt_JetAlgs_Jet", &MET_Goodness_DeltaEt_JetAlgs_Jet, &b_MET_Goodness_DeltaEt_JetAlgs_Jet);
   fChain->SetBranchAddress("MET_Goodness_DeltaEta_JetAlgs_Jet", &MET_Goodness_DeltaEta_JetAlgs_Jet, &b_MET_Goodness_DeltaEta_JetAlgs_Jet);
   fChain->SetBranchAddress("MET_Goodness_DeltaPhi_JetAlgs_Jet", &MET_Goodness_DeltaPhi_JetAlgs_Jet, &b_MET_Goodness_DeltaPhi_JetAlgs_Jet);
   fChain->SetBranchAddress("MET_Goodness_DeltaPhi_MET_Jet", &MET_Goodness_DeltaPhi_MET_Jet, &b_MET_Goodness_DeltaPhi_MET_Jet);
   fChain->SetBranchAddress("MET_Goodness_EEM_Jet", &MET_Goodness_EEM_Jet, &b_MET_Goodness_EEM_Jet);
   fChain->SetBranchAddress("MET_Goodness_EFinal_Jet", &MET_Goodness_EFinal_Jet, &b_MET_Goodness_EFinal_Jet);
   fChain->SetBranchAddress("MET_Goodness_EMFraction_Jet", &MET_Goodness_EMFraction_Jet, &b_MET_Goodness_EMFraction_Jet);
   fChain->SetBranchAddress("MET_Goodness_E_BadCellsCorr_Jet", &MET_Goodness_E_BadCellsCorr_Jet, &b_MET_Goodness_E_BadCellsCorr_Jet);
   fChain->SetBranchAddress("MET_Goodness_E_BadCells_Jet", &MET_Goodness_E_BadCells_Jet, &b_MET_Goodness_E_BadCells_Jet);
   fChain->SetBranchAddress("MET_Goodness_Eta_Jet", &MET_Goodness_Eta_Jet, &b_MET_Goodness_Eta_Jet);
   fChain->SetBranchAddress("MET_Goodness_HECf_Jet", &MET_Goodness_HECf_Jet, &b_MET_Goodness_HECf_Jet);
   fChain->SetBranchAddress("MET_Goodness_LArQuality_Jet", &MET_Goodness_LArQuality_Jet, &b_MET_Goodness_LArQuality_Jet);
   fChain->SetBranchAddress("MET_Goodness_Phi_Jet", &MET_Goodness_Phi_Jet, &b_MET_Goodness_Phi_Jet);
   fChain->SetBranchAddress("MET_Goodness_PtEM_Jet", &MET_Goodness_PtEM_Jet, &b_MET_Goodness_PtEM_Jet);
   fChain->SetBranchAddress("MET_Goodness_QualityFrac_Jet", &MET_Goodness_QualityFrac_Jet, &b_MET_Goodness_QualityFrac_Jet);
   fChain->SetBranchAddress("MET_Goodness_SamplingFracCryo_Jet", &MET_Goodness_SamplingFracCryo_Jet, &b_MET_Goodness_SamplingFracCryo_Jet);
   fChain->SetBranchAddress("MET_Goodness_SamplingFracEM_Jet", &MET_Goodness_SamplingFracEM_Jet, &b_MET_Goodness_SamplingFracEM_Jet);
   fChain->SetBranchAddress("MET_Goodness_SamplingFracFCAL_Jet", &MET_Goodness_SamplingFracFCAL_Jet, &b_MET_Goodness_SamplingFracFCAL_Jet);
   fChain->SetBranchAddress("MET_Goodness_SamplingFracGap_Jet", &MET_Goodness_SamplingFracGap_Jet, &b_MET_Goodness_SamplingFracGap_Jet);
   fChain->SetBranchAddress("MET_Goodness_SamplingFracHEC3_Jet", &MET_Goodness_SamplingFracHEC3_Jet, &b_MET_Goodness_SamplingFracHEC3_Jet);
   fChain->SetBranchAddress("MET_Goodness_SamplingFracHEC_Jet", &MET_Goodness_SamplingFracHEC_Jet, &b_MET_Goodness_SamplingFracHEC_Jet);
   fChain->SetBranchAddress("MET_Goodness_SamplingFracMax_Jet", &MET_Goodness_SamplingFracMax_Jet, &b_MET_Goodness_SamplingFracMax_Jet);
   fChain->SetBranchAddress("MET_Goodness_SamplingFracPS_Jet", &MET_Goodness_SamplingFracPS_Jet, &b_MET_Goodness_SamplingFracPS_Jet);
   fChain->SetBranchAddress("MET_Goodness_SamplingFracTile10_Jet", &MET_Goodness_SamplingFracTile10_Jet, &b_MET_Goodness_SamplingFracTile10_Jet);
   fChain->SetBranchAddress("MET_Goodness_SamplingFracTile2_Jet", &MET_Goodness_SamplingFracTile2_Jet, &b_MET_Goodness_SamplingFracTile2_Jet);
   fChain->SetBranchAddress("MET_Goodness_SamplingFracTile_Jet", &MET_Goodness_SamplingFracTile_Jet, &b_MET_Goodness_SamplingFracTile_Jet);
   fChain->SetBranchAddress("MET_Goodness_TileQuality_Jet", &MET_Goodness_TileQuality_Jet, &b_MET_Goodness_TileQuality_Jet);
   fChain->SetBranchAddress("MET_Goodness_Timing_Jet", &MET_Goodness_Timing_Jet, &b_MET_Goodness_Timing_Jet);
   fChain->SetBranchAddress("MET_Goodness_fcor_Jet", &MET_Goodness_fcor_Jet, &b_MET_Goodness_fcor_Jet);
   fChain->SetBranchAddress("MET_Goodness_ootE25_Jet", &MET_Goodness_ootE25_Jet, &b_MET_Goodness_ootE25_Jet);
   fChain->SetBranchAddress("MET_Goodness_ootE50_Jet", &MET_Goodness_ootE50_Jet, &b_MET_Goodness_ootE50_Jet);
   fChain->SetBranchAddress("MET_Goodness_ootE75_Jet", &MET_Goodness_ootE75_Jet, &b_MET_Goodness_ootE75_Jet);
   fChain->SetBranchAddress("MET_Goodness_N90Cells_Jet", &MET_Goodness_N90Cells_Jet, &b_MET_Goodness_N90Cells_Jet);
   fChain->SetBranchAddress("MET_Goodness_N90Constituents_Jet", &MET_Goodness_N90Constituents_Jet, &b_MET_Goodness_N90Constituents_Jet);
   fChain->SetBranchAddress("MET_Goodness_NConstituents_Jet", &MET_Goodness_NConstituents_Jet, &b_MET_Goodness_NConstituents_Jet);
   fChain->SetBranchAddress("MET_Goodness_N_BadCellsCorr_Jet", &MET_Goodness_N_BadCellsCorr_Jet, &b_MET_Goodness_N_BadCellsCorr_Jet);
   fChain->SetBranchAddress("MET_Goodness_N_BadCells_Jet", &MET_Goodness_N_BadCells_Jet, &b_MET_Goodness_N_BadCells_Jet);
   fChain->SetBranchAddress("MET_Goodness_NumTracks_Jet", &MET_Goodness_NumTracks_Jet, &b_MET_Goodness_NumTracks_Jet);
   fChain->SetBranchAddress("MET_Goodness_SamplingMaxID_Jet", &MET_Goodness_SamplingMaxID_Jet, &b_MET_Goodness_SamplingMaxID_Jet);
   fChain->SetBranchAddress("MET_Goodness_All", &MET_Goodness_All, &b_MET_Goodness_All);
   fChain->SetBranchAddress("MET_Goodness_JetCleaning", &MET_Goodness_JetCleaning, &b_MET_Goodness_JetCleaning);
   fChain->SetBranchAddress("MET_Goodness_BitMask", &MET_Goodness_BitMask, &b_MET_Goodness_BitMask);
   
   
      //////////////////////////////////////////////////
   //////////////////////////////////////////////////
   // disable all branches first ////////////////////
   fChain->SetBranchStatus("L1*",0);/////////////////
   fChain->SetBranchStatus("L2*",0);/////////////////
   fChain->SetBranchStatus("EF*",0);/////////////////
   fChain->SetBranchStatus("ph_*",0);////////////////
   fChain->SetBranchStatus("tau_*",0);///////////////
   fChain->SetBranchStatus("jet_*",0);///////////////
   fChain->SetBranchStatus("trig_*",0);//////////////
   fChain->SetBranchStatus("MET_*",0);///////////////
   fChain->SetBranchStatus("trk_*",0);///////////////
   fChain->SetBranchStatus("mb*",0);/////////////////
   fChain->SetBranchStatus("L1_MBTS*",0);////////////
   fChain->SetBranchStatus("collcand_*",0);//////////
   //////////////////////////////////////////////////
   // disable vector<vector<>> for the vertex branches
   fChain->SetBranchStatus("vxp_trk_chi2", 0); //////
   fChain->SetBranchStatus("vxp_trk_d0", 0); ////////
   fChain->SetBranchStatus("vxp_trk_z0", 0); ////////
   fChain->SetBranchStatus("vxp_trk_unbiased_d0", 0);
   fChain->SetBranchStatus("vxp_trk_unbiased_z0", 0);
   fChain->SetBranchStatus("vxp_trk_err_unbiased_d0", 0);
   fChain->SetBranchStatus("vxp_trk_err_unbiased_z0", 0);
   fChain->SetBranchStatus("vxp_trk_phi", 0); ///////
   fChain->SetBranchStatus("vxp_trk_theta", 0); /////
   fChain->SetBranchStatus("vxp_trk_weight", 0); ////
   fChain->SetBranchStatus("vxp_trk_index", 0); /////
   //////////////////////////////////////////////////
   //////////////////////////////////////////////////
   
   
   //////////////////////////////////////////////////
   //////////////////////////////////////////////////
   // enable only the necessary branches ////////////
   fChain->SetBranchStatus("L1_MU0",1);//////////////
   fChain->SetBranchStatus("L1_MU6",1);//////////////
   fChain->SetBranchStatus("L1_MU10",1);/////////////
   fChain->SetBranchStatus("L1_MU15",1);/////////////
   fChain->SetBranchStatus("L1_MU20",1);/////////////
   fChain->SetBranchStatus("EF_mu10",1);/////////////
	fChain->SetBranchStatus("EF_mu10_MG",1);//////////////
	fChain->SetBranchStatus("EF_mu10_MSonly",1);//////////////
	fChain->SetBranchStatus("EF_mu10_MSonly_tight",1);//////////////
	fChain->SetBranchStatus("EF_mu10_NoAlg",1);//////////////
	fChain->SetBranchStatus("EF_mu10_tight",1);//////////////
	fChain->SetBranchStatus("EF_mu10i_loose",1);//////////////
	fChain->SetBranchStatus("EF_mu13",1);//////////////
	fChain->SetBranchStatus("EF_mu13_MG",1);//////////////
	fChain->SetBranchStatus("EF_mu13_MG_tight",1);//////////////
	fChain->SetBranchStatus("EF_mu13_tight",1);//////////////
	fChain->SetBranchStatus("EF_mu15",1);//////////////
	fChain->SetBranchStatus("EF_mu15_NoAlg",1);//////////////
	fChain->SetBranchStatus("EF_mu20",1);//////////////
	fChain->SetBranchStatus("EF_mu20_MSonly",1);//////////////
	fChain->SetBranchStatus("EF_mu20_NoAlg",1);//////////////
	fChain->SetBranchStatus("EF_mu20_slow",1);//////////////
	fChain->SetBranchStatus("EF_mu30_MSonly",1);//////////////
	fChain->SetBranchStatus("EF_mu40_MSonly",1);//////////////
	   
	fChain->SetBranchStatus("L1_MU0",1);//////////////
	fChain->SetBranchStatus("L1_MU10",1);//////////////
	fChain->SetBranchStatus("L1_MU15",1);//////////////
	fChain->SetBranchStatus("L1_MU20",1);//////////////
	fChain->SetBranchStatus("L1_MU6",1);//////////////
   //////////////////////////////////////////////////
   //////////////////////////////////////////////////
   
   
   Notify();
}

Bool_t physics::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void physics::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t physics::Cut(Long64_t entry)
{
   if(false) cout << "entry = " << entry << endl;
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef physics_cxx
