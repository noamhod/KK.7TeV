/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#define analysisModules_cxx
#include "analysisModules.C"

#ifndef ANALYSISSKELETON_H
#define ANALYSISSKELETON_H

class analysisSkeleton : public analysisModules//, public selection
{
public:
	//////////////////////
	// basic local vars
	TMapii muPairMap;
	bool passCutFlow;
	bool passCurrentCut;
	bool twoMusPass;
	bool thisMuPass;
	int cutFlowMapSize;
	int counter;
	int ai;
	int bi;
	int iVtx;
	string sRunType;
	int currentRun;
	string sPeriod;
	string sCurrentPeriod;
	vector<string>* vTriggers;
	vector<bool> muQAflags;
	int nMusPassed;
	TMapdi pTtoIndexMap;
	TVectorP2VL	pmu;
	TVectorP2VL pmuTruth;
	TMapsd values2fill;
	int nMultiMuonEvents;
	


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
	int lar_ncellA;
	int lar_ncellC;
	float lar_energyA;
	float lar_energyC;
	float lar_timeA;
	float lar_timeC;
	float lar_timeDiff;
	
	// L1 triggers
	int isL1_MU0;
	int isL1_MU10;
	int isL1_MU15;
	int isL1_MU20;
	int isL1_MU6;
	
	// EF triggers
	int isEF_mu10;
	int isEF_mu10_MG;
	int isEF_mu10_MSonly;
	int isEF_mu10_MSonly_tight;
	int isEF_mu10_NoAlg;
	int isEF_mu10_tight;
	int isEF_mu10i_loose;
	int isEF_mu13;
	int isEF_mu13_MG;
	int isEF_mu13_MG_tight;
	int isEF_mu13_tight;
	int isEF_mu15;
	int isEF_mu15_NoAlg;
	int isEF_mu20;
	int isEF_mu20_MSonly;
	int isEF_mu20_NoAlg;
	int isEF_mu20_slow;
	int isEF_mu30_MSonly;
	int isEF_mu4;
	int isEF_mu40_MSonly;

	
	// vertexes (for the PV preselection)
	int vxp_n;
	vector<int>*   vxp_nTracks;
	vector<int>*   vxp_type;
	vector<float>* vxp_z;
	
	// muon
	int mu_n;
	vector<float>* mu_m;
	vector<float>* mu_px;
	vector<float>* mu_py;
	vector<float>* mu_pz;
	vector<float>* mu_E;
	vector<float>* mu_eta;
	vector<float>* mu_phi;
	vector<float>* mu_pt;
	vector<float>* mu_charge;
	vector<unsigned short>* mu_allauthor;
	vector<int>*   mu_author;
	vector<float>* mu_matchchi2;
	vector<int>*   mu_matchndof;
	
	// isolation
	vector<float>* mu_ptcone20;
	vector<float>* mu_ptcone30;
	vector<float>* mu_ptcone40;
	
	// for pT
	vector<float>* mu_me_qoverp;
	vector<float>* mu_id_qoverp;
	vector<float>* mu_me_theta;
	vector<float>* mu_id_theta;
	
	// for impact parameter
	vector<float>* mu_d0_exPV;
	vector<float>* mu_z0_exPV;
	
	// combined muons
	vector<int>* mu_isCombinedMuon;
	
	// inner detector hits
	vector<int>* mu_nSCTHits;
	vector<int>* mu_nPixHits; 

	// muon spectrometer hits
	vector<int>* mu_nMDTBIHits;
	vector<int>* mu_nMDTBMHits;
	vector<int>* mu_nMDTBOHits;
	vector<int>* mu_nMDTBEEHits;
	vector<int>* mu_nMDTBIS78Hits;
	vector<int>* mu_nMDTEIHits;
	vector<int>* mu_nMDTEMHits;
	vector<int>* mu_nMDTEOHits;
	vector<int>* mu_nMDTEEHits;
	vector<int>* mu_nRPCLayer1EtaHits;
	vector<int>* mu_nRPCLayer2EtaHits;
	vector<int>* mu_nRPCLayer3EtaHits;
	vector<int>* mu_nRPCLayer1PhiHits;
	vector<int>* mu_nRPCLayer2PhiHits;
	vector<int>* mu_nRPCLayer3PhiHits;
	vector<int>* mu_nTGCLayer1EtaHits;
	vector<int>* mu_nTGCLayer2EtaHits;
	vector<int>* mu_nTGCLayer3EtaHits;
	vector<int>* mu_nTGCLayer4EtaHits;
	vector<int>* mu_nTGCLayer1PhiHits;
	vector<int>* mu_nTGCLayer2PhiHits;
	vector<int>* mu_nTGCLayer3PhiHits;
	vector<int>* mu_nTGCLayer4PhiHits;

	vector<float>*   mu_etcone20;
	vector<float>*   mu_etcone30;
	vector<float>*   mu_etcone40;
	vector<float>*   mu_nucone20;
	vector<float>*   mu_nucone30;
	vector<float>*   mu_nucone40;
	vector<float>*   mu_energyLossPar;
	vector<float>*   mu_energyLossErr;
	vector<int>*     mu_bestMatch;
	vector<int>*     mu_isStandAloneMuon;
	vector<int>*     mu_isLowPtReconstructedMuon;
	vector<int>*     mu_loose;
	vector<int>*     mu_medium;
	vector<int>*     mu_tight;
	vector<float>*   mu_phi_exPV;
	vector<float>*   mu_theta_exPV;
	vector<float>*   mu_qoverp_exPV;
	vector<float>*   mu_cov_d0_exPV;
	vector<float>*   mu_cov_z0_exPV;
	vector<float>*   mu_cov_phi_exPV;
	vector<float>*   mu_cov_theta_exPV;
	vector<float>*   mu_cov_qoverp_exPV;
	vector<float>*   mu_cov_d0_z0_exPV;
	vector<float>*   mu_cov_d0_phi_exPV;
	vector<float>*   mu_cov_d0_theta_exPV;
	vector<float>*   mu_cov_d0_qoverp_exPV;
	vector<float>*   mu_cov_z0_phi_exPV;
	vector<float>*   mu_cov_z0_theta_exPV;
	vector<float>*   mu_cov_z0_qoverp_exPV;
	vector<float>*   mu_cov_phi_theta_exPV;
	vector<float>*   mu_cov_phi_qoverp_exPV;
	vector<float>*   mu_cov_theta_qoverp_exPV;
	vector<float>*   mu_ms_d0;
	vector<float>*   mu_ms_z0;
	vector<float>*   mu_ms_phi;
	vector<float>*   mu_ms_theta;
	vector<float>*   mu_ms_qoverp;
	vector<float>*   mu_id_d0;
	vector<float>*   mu_id_z0;
	vector<float>*   mu_id_phi;
	vector<float>*   mu_me_d0;
	vector<float>*   mu_me_z0;
	vector<float>*   mu_me_phi;
	vector<float>*   mu_ie_d0;
	vector<float>*   mu_ie_z0;
	vector<float>*   mu_ie_phi;
	vector<float>*   mu_ie_theta;
	vector<float>*   mu_ie_qoverp;
	vector<int>*     mu_nBLHits;
	vector<int>*     mu_nTRTHighTHits;
	vector<int>*     mu_nBLSharedHits;
	vector<int>*     mu_nPixSharedHits;
	vector<int>*     mu_nPixHoles;
	vector<int>*     mu_nSCTSharedHits;
	vector<int>*     mu_nSCTHoles;
	vector<int>*     mu_nTRTOutliers;
	vector<int>*     mu_nTRTHighTOutliers;
	vector<int>*     mu_nMDTHits;
	vector<int>*     mu_nMDTHoles;
	vector<int>*     mu_nCSCEtaHits;
	vector<int>*     mu_nCSCEtaHoles;
	vector<int>*     mu_nCSCPhiHits;
	vector<int>*     mu_nCSCPhiHoles;
	vector<int>*     mu_nRPCEtaHits;
	vector<int>*     mu_nRPCEtaHoles;
	vector<int>*     mu_nRPCPhiHits;
	vector<int>*     mu_nRPCPhiHoles;
	vector<int>*     mu_nTGCEtaHits;
	vector<int>*     mu_nTGCEtaHoles;
	vector<int>*     mu_nTGCPhiHits;
	vector<int>*     mu_nTGCPhiHoles;
	vector<int>*     mu_nGangedPixels;
	vector<int>*     mu_nOutliersOnTrack;
	vector<int>*     mu_barrelSectors;
	vector<int>*     mu_endcapSectors;
	vector<float>*   mu_trackd0;
	vector<float>*   mu_trackz0;
	vector<float>*   mu_trackphi;
	vector<float>*   mu_tracktheta;
	vector<float>*   mu_trackqoverp;
	vector<float>*   mu_trackcov_d0;
	vector<float>*   mu_trackcov_z0;
	vector<float>*   mu_trackcov_phi;
	vector<float>*   mu_trackcov_theta;
	vector<float>*   mu_trackcov_qoverp;
	vector<float>*   mu_trackcov_d0_z0;
	vector<float>*   mu_trackcov_d0_phi;
	vector<float>*   mu_trackcov_d0_theta;
	vector<float>*   mu_trackcov_d0_qoverp;
	vector<float>*   mu_trackcov_z0_phi;
	vector<float>*   mu_trackcov_z0_theta;
	vector<float>*   mu_trackcov_z0_qoverp;
	vector<float>*   mu_trackcov_phi_theta;
	vector<float>*   mu_trackcov_phi_qoverp;
	vector<float>*   mu_trackcov_theta_qoverp;
	vector<float>*   mu_trackfitchi2;
	vector<int>*     mu_trackfitndof;
	vector<int>*     mu_hastrack;
	vector<float>*   mu_EF_dr;
	vector<float>*   mu_EF_cb_eta;
	vector<float>*   mu_EF_cb_phi;
	vector<float>*   mu_EF_cb_pt;
	vector<float>*   mu_EF_ms_eta;
	vector<float>*   mu_EF_ms_phi;
	vector<float>*   mu_EF_ms_pt;
	vector<float>*   mu_EF_me_eta;
	vector<float>*   mu_EF_me_phi;
	vector<float>*   mu_EF_me_pt;
	vector<int>*     mu_EF_matched;
	vector<float>*   mu_L2CB_dr;
	vector<float>*   mu_L2CB_pt;
	vector<float>*   mu_L2CB_eta;
	vector<float>*   mu_L2CB_phi;
	vector<float>*   mu_L2CB_id_pt;
	vector<float>*   mu_L2CB_ms_pt;
	vector<int>*     mu_L2CB_nPixHits;
	vector<int>*     mu_L2CB_nSCTHits;
	vector<int>*     mu_L2CB_nTRTHits;
	vector<int>*     mu_L2CB_nTRTHighTHits;
	vector<int>*     mu_L2CB_matched;
	vector<float>*   mu_L1_dr;
	vector<float>*   mu_L1_pt;
	vector<float>*   mu_L1_eta;
	vector<float>*   mu_L1_phi;
	vector<short>*   mu_L1_thrNumber;
	vector<short>*   mu_L1_RoINumber;
	vector<short>*   mu_L1_sectorAddress;
	vector<int>*     mu_L1_firstCandidate;
	vector<int>*     mu_L1_moreCandInRoI;
	vector<int>*     mu_L1_moreCandInSector;
	vector<short>*   mu_L1_source;
	vector<short>*   mu_L1_hemisphere;
	vector<int>*     mu_L1_matched;
	
	
	// * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * *
	// Monte Carlo truth
	// staco/muid truth
	vector<float>*   mu_truth_dr;
	vector<float>*   mu_truth_E;
	vector<float>*   mu_truth_pt;
	vector<float>*   mu_truth_eta;
	vector<float>*   mu_truth_phi;
	vector<int>*     mu_truth_type;
	vector<int>*     mu_truth_status;
	vector<int>*     mu_truth_barcode;
	vector<int>*     mu_truth_mothertype;
	vector<int>*     mu_truth_motherbarcode;
	vector<int>*     mu_truth_matched;
	
	// muonTruth
	int              as_muonTruth_n;
	vector<float>*   as_muonTruth_pt;
	vector<float>*   as_muonTruth_m;
	vector<float>*   as_muonTruth_eta;
	vector<float>*   as_muonTruth_phi;
	vector<float>*   as_muonTruth_charge;
	vector<int>*     as_muonTruth_PDGID;
	vector<int>*     as_muonTruth_barcode;
	vector<int>*     as_muonTruth_type;
	vector<int>*     as_muonTruth_origin;
	
	// MC event
	int              as_mcevt_n;
	vector<int>*     as_mcevt_signal_process_id;
	vector<int>*     as_mcevt_event_number;
	vector<double>*  as_mcevt_event_scale;
	vector<double>*  as_mcevt_alphaQCD;
	vector<double>*  as_mcevt_alphaQED;
	vector<int>*     as_mcevt_pdf_id1;
	vector<int>*     as_mcevt_pdf_id2;
	vector<double>*  as_mcevt_pdf_x1;
	vector<double>*  as_mcevt_pdf_x2;
	vector<double>*  as_mcevt_pdf_scale;
	vector<double>*  as_mcevt_pdf1;
	vector<double>*  as_mcevt_pdf2;
	vector<double>*  as_mcevt_weight;
	
	// * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * *
	// muon variables for selection
	
	////////////////////////
	// more variables
	float current_imass;
	float current_cosTheta;
	float current_mu_pT;
	float current_muplus_pT;
	float current_mu_eta;
	float current_muplus_eta;
	float current_cosmicCosth;
	float current_ipTdiff;
	float current_etaSum;

public:
	analysisSkeleton();
	analysisSkeleton(string sCutFlowFilePath, string sPeriodsFilePath, string sEventDumpFilePath) :
	analysisModules(sCutFlowFilePath,sPeriodsFilePath,sEventDumpFilePath)
	{
		currentRun = 0;
		sCurrentPeriod = "";
	}
	~analysisSkeleton();
	
	void resetMuQAflags(int nMus);
	int  countQAflags();
	void pTSort();
	void imassSort();
	bool assignPairIndices();
	
	string          getPeriodName();
	string          getPeriodName(int run);
	vector<string>* getPeriodTriggers();
	int             isTrigger(string trigName);
	bool			skimD3PD(physics* phys);
	bool            digestSkim(int muSize);
	void 			printAllProperties(int ai, int bi, int iv);
	
	void buildMU4Vector(int nMus);
	void buildMU4Vector(int nMus, string fromAngles = "");
	void wipeMU4Vector();
	
	bool applyPreselection(string sSkipCut = "");
	bool applySingleMuonSelection(string sSkipCut = "");
	bool applyDoubleMuonSelection(string sSkipCut = "");
	
	void fillCutProfile1D();
	void fillCutProfile2D();
	
	void fillTagNProbe();
	void fillTruthEfficiency();

private:
	void runEventDumper();
	
	bool preselection(string sSkipCut);
	bool singleSelection(string sSkipCut);
	bool doubleSelection(string sSkipCut);
	
	void fillAfterCuts();
	void fillBeforeCuts();
	void fillCutFlow(string sorderedcutname, string sIsPreselection = "");

};
#endif

