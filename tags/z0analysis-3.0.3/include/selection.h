/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#ifndef SELECTION_H
#define SELECTION_H

class selection : public kinematics
{
public:
	bool b_print;
	
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
	
	bool findBestVertex(int nTracksCut, int nTypeCut, float z0Cut, int nvxp,
						vector<int>* v_vxp_nTracks, vector<int>* v_vxp_type, vector<float>* v_vxp_z);
	int getPVindex();
	int getPVindex(int nTracksCut, int nTypeCut, float z0Cut, int nvxp,
				   vector<int>* v_vxp_nTracks, vector<int>* v_vxp_type, vector<float>* v_vxp_z);
	
	bool findHipTmuon(float hipTmuonCut, float MShipTmuonCut, int nmu,
					  vector<float>* v_pT, vector<float>* v_qoverp, vector<float>* v_theta);
	
	
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
	// * * * simple cuts methods * * *
	
	bool isGRLCut(    float isGRLCutVal,    int isGRL );
	bool isL1_MU6Cut( float isL1_MU6CutVal, int isL1_MU6 );
	bool isEF_muXCut( float isEF_muXCutVal, int isEF_muX );
	bool triggerCut(  float triggerCutVal,  int isTrigger, string triggerName );
	
	bool pTCut(           float pTCutVal,           TLorentzVector* pa, TLorentzVector* pb );
	bool pTCut(           float pTCutVal,           float pT );
	bool pTCut(           float pTCutVal,           float me_qOp_a, float me_theta_a, float me_qOp_b, float me_theta_b );
	bool pTCut(           float pTCutVal,           float me_qOp, float me_theta );
	bool etaCut(          float etaCutVal,          TLorentzVector* pa, TLorentzVector* pb );
	bool etaCut(          float etaCutVal,          float eta_a, float eta_b );
	bool etaCut(          float etaCutVal,          float eta );
	bool etaTightCut(     float etaTightCutVal,     TLorentzVector* pa, TLorentzVector* pb );
	bool etaTightCut(     float etaTightCutVal,     float eta_a, float eta_b );
	bool etaTightCut(     float etaTightCutVal,     float eta );
	bool etaBarrelCut(    float etaBarrelCutVal,    float eta );
	bool cosThetaDimuCut( float cosThetaDimuCutVal, TLorentzVector* pa, TLorentzVector* pb );
	bool etaSumCut(       float etaSumCutVal,       TLorentzVector* pa, TLorentzVector* pb );
	bool imassCut(        float imassCutVal,        TLorentzVector* pa, TLorentzVector* pb );
	bool imassMaxCut(     float imassCutVal,        TLorentzVector* pa, TLorentzVector* pb );

	bool d0Cut(          float d0CutVal, float d0a, float d0b );
	bool d0Cut(          float d0CutVal, float d0 );
	bool z0Cut(          float z0CutVal, float z0a, float z0b );
	bool z0Cut(          float z0CutVal, float z0 );
	bool oppositeChargeCut( float ca, float cb );
	bool oppositeChargeCut( float oppositeChargeCutVal, float ca, float cb );
	
	bool prmVtxNtracksCut( float prmVtxNtracksCutVal, int nPVtracks );
	bool prmVtxTypeCut( float prmVtxTypeCutVal, int nPVtype );
	bool prmVtxZ0Cut( float prmVtxZ0CutVal, float dPVz0, float dPVz0err );
	bool isCombMuCut( float isCombMuCutVal, int isCombMua, int isCombMub );
	bool isCombMuCut( float isCombMuCutVal, int isCombMu );
	bool nSCThitsCut( float nSCThitsCutVal, int nSCThits );
	bool nPIXhitsCut( float nPIXhitsCutVal, int nPIXhits );
	bool pTmatchRatioCut( float pTmatchHighRatioCutVal,
						  float pTmatchLowRatioCutVal,
						  float me_qOp, float me_theta,
						  float id_qOp, float id_theta );
	bool pTmatchAbsDiffCut(float pTmatchDiffCutVal,
						   float me_qOp, float me_theta,
						   float id_qOp, float id_theta );
	bool isolationXXCut( float isolationCutVal, string sIsoValName, float pTmu, float pTcone );
	bool isolationXXCut( float isolationCutVal, string sIsoValName, float qOp, float theta, float pTcone );
	
	
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
	// * * * combined cuts methods * * *
	
	bool primaryVertexCut( float prmVtxNtracksCutVal, float prmVtxTypeCutVal, float prmVtxZ0CutVal,
						   vector<int>* pviPVtracks,
						   vector<int>* pviPVtype,
						   vector<float>* pvfPVz0,
						   vector<float>* pvfPVz0err,
						   int& bestVtxIndex );
						   
	bool nIDhitsCut( float nSCThitsCutVal, float nPIXhitsCutVal, float nIDhitsCutVal, int nSCThits, int nPIXhits );
	bool nIDhitsMCPrel15Cut(float nSCThitsCutVal, float nPIXhitsCutVal, float nTRThitsCutVal,
							float etaAbsThreshold, float nTRTratioThreshold,
							int nSCThits, int nPIXhits, int nTRTHits, int nTRTOutliers,
							float eta);
	bool nIDhitsRel16Cut(float expectBLayerHitCutVal, float nBLHitsCutVal, 
						 float nPIXhitsCutVal,        float nSCThitsCutVal,     float nPIXSCTHolesCutVal,
						 float nTRThitsCutVal,        float nTRTratioThreshold, float etaAbsThreshold,
						 int   expectBLayerHit,       int nBLHits,
						 int   nPIXhits,              int nPixelDeadSensors,    int nPixHoles,
						 int   nSCThits,              int nSCTDeadSensors,      int nSCTHoles,   
						 int   nTRTHits,              int nTRTOutliers,
						 float eta);
	
	bool nMS3stationsMDThits(float nMDTIHitsCutVal, float nMDTMHitsCutVal, float nMDTOHitsCutVal, float nMDTBEEHitsCutVal, float nMDTBIS78HitsCutVal,
							 int nMDTBIHits, int nMDTBMHits, int nMDTBOHits,
							 int nMDTEIHits, int nMDTEMHits, int nMDTEOHits,
							 int nMDTBEEHits, int nMDTBIS78Hits);
	bool nMShits(float nMDTIHitsCutVal, float nMDTMHitsCutVal, float nMDTOHitsCutVal, float nMDTBIS78HitsCutVal, float nMDTBEEHitsCutVal,
				 float nRPCPhiHitsCutVal,
				 int nMDTBIHits, int nMDTBMHits, int nMDTBOHits, int nMDTBIS78Hits, int nMDTBEEHits,
				 int nRPCLayer1PhiHits, int nRPCLayer2PhiHits, int nRPCLayer3PhiHits
				 );
	bool nMShits1(float nMDTB_IMO_HitsCutVal, float nMDTE_IMEO_HitsCutVal,
				  float nMDTBIS78HitsCutVal, float nMDTBEEHitsCutVal,
				  float nCSCEtaHitsCutVal,
				  float nMDTCSCsumCutVal, float nRPCTGCCSCsumsCutVal,
				  int nMDTBIHits, int nMDTBMHits, int nMDTBOHits,
				  int nMDTEIHits, int nMDTEMHits, int nMDTEEHits, int nMDTEOHits,
				  int nMDTBIS78Hits, int nMDTBEEHits,
				  int nRPCLayer1PhiHits, int nRPCLayer2PhiHits, int nRPCLayer3PhiHits,
				  int nTGCLayer1PhiHits, int nTGCLayer2PhiHits, int nTGCLayer3PhiHits, int nTGCLayer4PhiHits,
				  int nCSCEtaHits, int nCSCPhiHits
				  );
	bool nMShits2(float nMDTB_IMO_HitsCutVal, float nMDTE_IMEO_HitsCutVal,
				  float nMDTBIS78HitsCutVal, float nMDTBEEHitsCutVal,
				  float nCSCEtaHitsCutVal,
				  float nRPCPhiHitsCutVal, float nTGCPhiHitsCutVal, float nCSCPhiHitsCutVal,
				  float nMDTCSCsumCutVal, float nRPCTGCsumsCutVal,
				  int nMDTBIHits, int nMDTBMHits, int nMDTBOHits,
				  int nMDTEIHits, int nMDTEMHits, int nMDTEEHits, int nMDTEOHits,
				  int nMDTBIS78Hits, int nMDTBEEHits,
				  int nRPCLayer1PhiHits, int nRPCLayer2PhiHits, int nRPCLayer3PhiHits,
				  int nTGCLayer1PhiHits, int nTGCLayer2PhiHits, int nTGCLayer3PhiHits, int nTGCLayer4PhiHits,
				  int nCSCEtaHits, int nCSCPhiHits
				 );
	bool nMShitsRel16(float nMDTB_IMO_HitsCutVal, float nMDTE_IMO_HitsCutVal,
					  float nMDTBEEHitsCutVal, float nMDTEEHitsCutVal, float nMDTBIS78HitsCutVal, 
					  float nCSCEtaHitsCutVal,
					  float nPhiHitsCutVal,
					  float nMDTCSCsumCutVal, float nRPCTGCCSCsumsCutVal,
					  int nMDTBIHits, int nMDTBMHits, int nMDTBOHits,
					  int nMDTEIHits, int nMDTEMHits, int nMDTEOHits,
					  int nMDTBEEHits, int nMDTEEHits, int nMDTBIS78Hits,
					  int nRPCLayer1PhiHits, int nRPCLayer2PhiHits, int nRPCLayer3PhiHits,
					  int nTGCLayer1PhiHits, int nTGCLayer2PhiHits, int nTGCLayer3PhiHits, int nTGCLayer4PhiHits,
					  int nCSCEtaHits, int nCSCPhiHits
					  );
	bool nMShits2noCSCphi(
				  float nMDTB_IMO_HitsCutVal, float nMDTE_IMEO_HitsCutVal,
				  float nMDTBIS78HitsCutVal, float nMDTBEEHitsCutVal,
				  float nCSCEtaHitsCutVal,
				  float nRPCPhiHitsCutVal, float nTGCPhiHitsCutVal,
				  float nMDTCSCsumCutVal, float nRPCTGCsumsCutVal,
				  int nMDTBIHits, int nMDTBMHits, int nMDTBOHits,
				  int nMDTEIHits, int nMDTEMHits, int nMDTEEHits, int nMDTEOHits,
				  int nMDTBIS78Hits, int nMDTBEEHits,
				  int nRPCLayer1PhiHits, int nRPCLayer2PhiHits, int nRPCLayer3PhiHits,
				  int nTGCLayer1PhiHits, int nTGCLayer2PhiHits, int nTGCLayer3PhiHits, int nTGCLayer4PhiHits,
				  int nCSCEtaHits
				 );
				 
	bool pTmatchingRatioCut( float pTmatchHighRatioCutVal,
							 float pTmatchLowRatioCutVal,
							 float me_qOp_a, float me_theta_a,
							 float id_qOp_a, float id_theta_a,
							 float me_qOp_b, float me_theta_b,
							 float id_qOp_b, float id_theta_b
							);
	bool pTmatchingAbsDiffCut( float pTmatchDiffCutVal,
							   float me_qOp_a, float me_theta_a,
							   float id_qOp_a, float id_theta_a,
							   float me_qOp_b, float me_theta_b,
							   float id_qOp_b, float id_theta_b
							 );
	bool impactParameterCut( float d0CutVal, float z0CutVal,
							 float d0a, float d0b,
							 float z0a, float z0b );
	bool impactParameterCut( float d0CutVal, float z0CutVal,
							 float d0, float z0 );
	bool pTandEtaCut(        float pTCutVal, float etaCutVal,
							 float pT, float eta );
	bool pTandEtaTightCut(   float pTCutVal, float etaTightCutVal,
							 float pT, float eta );
	bool pTandEtaBarrelCut(  float pTCutVal, float etaBarrelCutVal,
							 float pT, float eta );
	bool pTandEtaCut(        float pTCutVal, float etaCutVal,
							 float me_qOp, float me_theta, float eta );
	bool pTandEtaTightCut(   float pTCutVal, float etaTightCutVal,
							 float me_qOp, float me_theta, float eta );
	bool pTandEtaBarrelCut(  float pTCutVal, float etaBarrelCutVal,
							 float me_qOp, float me_theta, float eta );
	bool pairXXisolation( float isolationCutVal, string sIsoValName,
						  float pTmua, float pTmub, float pTconea, float pTconeb );
	
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

private:
	int m_iVtx;

};
#endif

