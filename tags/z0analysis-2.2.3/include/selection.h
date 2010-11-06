/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#define kinematics_cxx
#include "kinematics.C"

#ifndef SELECTION_H
#define SELECTION_H

class selection : public kinematics
{
public:
	bool   b_print;
	
public:
	selection();
	~selection();
	
	void sinitialize();
	void sfinalize();

	//void initSelectionCuts(TMapsvd* cutFlowMapSVD, TMapds* cutFlowOrdered, TMapds* cutFlowTypeOrdered); // called by analysis, offlineAnalysis and digestAnalysis
	
	void buildMuonPairMap( TMapii& mupair, TVectorP2VL& pmu );

	bool removeOverlaps(	TMapii& mupair, int ia, int ib );
	
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
	// * * * preselection simple methods * * *
	bool oppositeChargePair(vector<float>* vcharge, int a, int b);
	
	bool findMostMassivePair(TVectorP2VL& pmu, TMapii& allmupairMap);
	void findMostHipTPair(vector<float>* mu_pt, int& iBest_a, int&iBest_b);
	void findMostMassivePair(vector<float>* vcharge, TVectorP2VL& pmu, TMapii& allmupairMap, int& iBest_a, int&iBest_b);
	
	bool findBestVertex(int nTracksCut, int nTypeCut, double z0Cut, int nvxp,
						vector<int>* v_vxp_nTracks, vector<int>* v_vxp_type, vector<float>* v_vxp_z);
	int getPVindex(int nTracksCut, int nTypeCut, double z0Cut, int nvxp,
				   vector<int>* v_vxp_nTracks, vector<int>* v_vxp_type, vector<float>* v_vxp_z);
	
	bool findHipTmuon(double hipTmuonCut, double MShipTmuonCut, int nmu,
					  vector<float>* v_pT, vector<float>* v_qoverp, vector<float>* v_theta);
	
	
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
	// * * * simple cuts methods * * *
	
	bool isGRLCut(    double isGRLCutVal,    int isGRL );
	bool isL1_MU6Cut( double isL1_MU6CutVal, int isL1_MU6 );
	bool isEF_muXCut( double isEF_muXCutVal, int isEF_muX );
	bool triggerCut(  double triggerCutVal,  int isTrigger, string triggerName );
	
	bool pTCut(           double pTCutVal,           TLorentzVector* pa, TLorentzVector* pb );
	bool pTCut(           double pTCutVal,           double pT );
	bool pTCut(           double pTCutVal,           double me_qOp_a, double me_theta_a, double me_qOp_b, double me_theta_b );
	bool pTCut(           double pTCutVal,           double me_qOp, double me_theta );
	bool etaCut(          double etaCutVal,          TLorentzVector* pa, TLorentzVector* pb );
	bool etaCut(          double etaCutVal,          double eta_a, double eta_b );
	bool etaCut(          double etaCutVal,          double eta );
	bool etaTightCut(     double etaTightCutVal,     TLorentzVector* pa, TLorentzVector* pb );
	bool etaTightCut(     double etaTightCutVal,     double eta_a, double eta_b );
	bool etaTightCut(     double etaTightCutVal,     double eta );
	bool cosThetaDimuCut( double cosThetaDimuCutVal, TLorentzVector* pa, TLorentzVector* pb );
	bool etaSumCut(       double etaSumCutVal,       TLorentzVector* pa, TLorentzVector* pb );
	bool imassCut(        double imassCutVal,        TLorentzVector* pa, TLorentzVector* pb );

	bool d0Cut(          double d0CutVal, double d0a, double d0b );
	bool d0Cut(          double d0CutVal, double d0 );
	bool z0Cut(          double z0CutVal, double z0a, double z0b );
	bool z0Cut(          double z0CutVal, double z0 );
	bool oppositeChargeCut( double ca, double cb );
	bool oppositeChargeCut( double oppositeChargeCutVal, double ca, double cb );
	
	bool prmVtxNtracksCut( double prmVtxNtracksCutVal, int nPVtracks );
	bool prmVtxTypeCut( double prmVtxTypeCutVal, int nPVtype );
	bool prmVtxZ0Cut( double prmVtxZ0CutVal, double dPVz0, double dPVz0err );
	bool isCombMuCut( double isCombMuCutVal, int isCombMua, int isCombMub );
	bool isCombMuCut( double isCombMuCutVal, int isCombMu );
	bool nSCThitsCut( double nSCThitsCutVal, int nSCThits );
	bool nPIXhitsCut( double nPIXhitsCutVal, int nPIXhits );
	bool pTmatchRatioCut( double pTmatchHighRatioCutVal,
						  double pTmatchLowRatioCutVal,
						  double me_qOp, double me_theta,
						  double id_qOp, double id_theta );
	bool pTmatchAbsDiffCut(double pTmatchDiffCutVal,
						   double me_qOp, double me_theta,
						   double id_qOp, double id_theta );
	bool isolationXXCut( double isolationCutVal, string sIsoValName, double pTmu, double pTcone );
	
	
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
	// * * * combined cuts methods * * *
	
	bool primaryVertexCut( double prmVtxNtracksCutVal, double prmVtxTypeCutVal, double prmVtxZ0CutVal,
						   vector<int>* pviPVtracks,
						   vector<int>* pviPVtype,
						   vector<float>* pvfPVz0,
						   vector<float>* pvfPVz0err,
						   int& bestVtxIndex );
	bool nIDhitsCut( double nSCThitsCutVal, double nPIXhitsCutVal, double nIDhitsCutVal, int nSCThits, int nPIXhits );
	bool nMS3stationsMDThits(double nMDTIHitsCutVal, double nMDTMHitsCutVal, double nMDTOHitsCutVal, double nMDTBEEHitsCutVal, double nMDTBIS78HitsCutVal,
							 int nMDTBIHits, int nMDTBMHits, int nMDTBOHits,
							 int nMDTEIHits, int nMDTEMHits, int nMDTEOHits,
							 int nMDTBEEHits, int nMDTBIS78Hits);
	bool pTmatchingRatioCut( double pTmatchHighRatioCutVal,
							 double pTmatchLowRatioCutVal,
							 double me_qOp_a, double me_theta_a,
							 double id_qOp_a, double id_theta_a,
							 double me_qOp_b, double me_theta_b,
							 double id_qOp_b, double id_theta_b
							);
	bool pTmatchingAbsDiffCut( double pTmatchDiffCutVal,
							   double me_qOp_a, double me_theta_a,
							   double id_qOp_a, double id_theta_a,
							   double me_qOp_b, double me_theta_b,
							   double id_qOp_b, double id_theta_b
							 );
	bool impactParameterCut( double d0CutVal, double z0CutVal,
							 double d0a, double d0b,
							 double z0a, double z0b );
	bool impactParameterCut( double d0CutVal, double z0CutVal,
							 double d0, double z0 );
	bool pTandEtaTightCut(   double pTCutVal, double etaTightCutVal,
							 double pT, double eta );
	bool pTandEtaTightCut(   double pTCutVal, double etaTightCutVal,
							 double me_qOp, double me_theta, double eta );
	bool pairXXisolation( double isolationCutVal, string sIsoValName,
						  double pTmua, double pTmub, double pTconea, double pTconeb );
	
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

private:
	int m_iVtx;

};
#endif

