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
	
	inline void buildMuonPairMap( TMapii& mupair, TVectorP2VL& pmu );

	inline bool removeOverlaps(	TMapii& mupair, int ia, int ib );
	
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
	// * * * preselection simple methods * * *
	inline bool oppositeChargePair(vector<float>* vcharge, int a, int b);
	
	inline bool findMostMassivePair(TVectorP2VL& pmu, TMapii& allmupairMap);
	inline void findMostHipTPair(vector<float>* mu_pt, int& iBest_a, int&iBest_b);
	inline void findMostMassivePair(vector<float>* vcharge, TVectorP2VL& pmu, TMapii& allmupairMap, int& iBest_a, int&iBest_b);
	
	inline bool findBestVertex(int nTracksCut, int nTypeCut, float z0Cut, int nvxp,
						vector<int>* v_vxp_nTracks, vector<int>* v_vxp_type, vector<float>* v_vxp_z);
	inline int getPVindex();
	inline int getPVindex(int nTracksCut, int nTypeCut, float z0Cut, int nvxp,
						  vector<int>* v_vxp_nTracks, vector<int>* v_vxp_type, vector<float>* v_vxp_z);
	
	inline bool findHipTmuon(float hipTmuonCut, float MShipTmuonCut, int nmu,
							 vector<float>* v_pT, vector<float>* v_qoverp, vector<float>* v_theta);
	
	
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
	// * * * simple cuts methods * * *
	
	inline bool isGRLCut(    float isGRLCutVal,    int isGRL );
	inline bool isL1_MU6Cut( float isL1_MU6CutVal, int isL1_MU6 );
	inline bool isEF_muXCut( float isEF_muXCutVal, int isEF_muX );
	inline bool triggerCut(  float triggerCutVal,  int isTrigger, string triggerName );
	
	inline bool pTCut(           float pTCutVal,           TLorentzVector* pa, TLorentzVector* pb );
	inline bool pTCut(           float pTCutVal,           float pT );
	inline bool pTCut(           float pTCutVal,           float me_qOp_a, float me_theta_a, float me_qOp_b, float me_theta_b );
	inline bool pTCut(           float pTCutVal,           float me_qOp, float me_theta );
	inline bool etaCut(          float etaCutVal,          TLorentzVector* pa, TLorentzVector* pb );
	inline bool etaCut(          float etaCutVal,          float eta_a, float eta_b );
	inline bool etaCut(          float etaCutVal,          float eta );
	inline bool etaTightCut(     float etaTightCutVal,     TLorentzVector* pa, TLorentzVector* pb );
	inline bool etaTightCut(     float etaTightCutVal,     float eta_a, float eta_b );
	inline bool etaTightCut(     float etaTightCutVal,     float eta );
	inline bool etaBarrelCut(    float etaBarrelCutVal,    float eta );
	inline bool cosThetaDimuCut( float cosThetaDimuCutVal, TLorentzVector* pa, TLorentzVector* pb );
	inline bool etaSumCut(       float etaSumCutVal,       TLorentzVector* pa, TLorentzVector* pb );
	inline bool imassCut(        float imassCutVal,        TLorentzVector* pa, TLorentzVector* pb );
	inline bool imassMaxCut(     float imassCutVal,        TLorentzVector* pa, TLorentzVector* pb );

	inline bool d0Cut(          float d0CutVal, float d0a, float d0b );
	inline bool d0Cut(          float d0CutVal, float d0 );
	inline bool z0Cut(          float z0CutVal, float z0a, float z0b );
	inline bool z0Cut(          float z0CutVal, float z0 );
	inline bool oppositeChargeCut( float ca, float cb );
	inline bool oppositeChargeCut( float oppositeChargeCutVal, float ca, float cb );
	
	inline bool prmVtxNtracksCut( float prmVtxNtracksCutVal, int nPVtracks );
	inline bool prmVtxTypeCut( float prmVtxTypeCutVal, int nPVtype );
	inline bool prmVtxZ0Cut( float prmVtxZ0CutVal, float dPVz0, float dPVz0err );
	inline bool isCombMuCut( float isCombMuCutVal, int isCombMua, int isCombMub );
	inline bool isCombMuCut( float isCombMuCutVal, int isCombMu );
	inline bool nSCThitsCut( float nSCThitsCutVal, int nSCThits );
	inline bool nPIXhitsCut( float nPIXhitsCutVal, int nPIXhits );
	inline bool pTmatchRatioCut( float pTmatchHighRatioCutVal,
								 float pTmatchLowRatioCutVal,
								 float me_qOp, float me_theta,
								 float id_qOp, float id_theta );
	inline bool pTmatchAbsDiffCut(float pTmatchDiffCutVal,
								  float me_qOp, float me_theta,
								  float id_qOp, float id_theta );
	inline bool isolationXXCut( float isolationCutVal, string sIsoValName, float pTmu, float pTcone );
	inline bool isolationXXCut( float isolationCutVal, string sIsoValName, float qOp, float theta, float pTcone );
	
	
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
	// * * * combined cuts methods * * *
	
	inline bool primaryVertexCut( float prmVtxNtracksCutVal, float prmVtxTypeCutVal, float prmVtxZ0CutVal,
								  vector<int>* pviPVtracks,
								  vector<int>* pviPVtype,
								  vector<float>* pvfPVz0,
								  vector<float>* pvfPVz0err,
								  int& bestVtxIndex);
						   
	inline bool nIDhitsCut( float nSCThitsCutVal, float nPIXhitsCutVal, float nIDhitsCutVal, int nSCThits, int nPIXhits );
	inline bool nIDhitsMCPrel15Cut(float nSCThitsCutVal, float nPIXhitsCutVal, float nTRThitsCutVal,
								   float etaAbsThreshold, float nTRTratioThreshold,
								   int nSCThits, int nPIXhits, int nTRTHits, int nTRTOutliers,
								   float eta);
	inline bool nIDhitsRel16Cut(float expectBLayerHitCutVal, float nBLHitsCutVal, 
								float nPIXhitsCutVal,        float nSCThitsCutVal,     float nPIXSCTHolesCutVal,
								float nTRThitsCutVal,        float nTRTratioThreshold, float etaAbsThreshold,
								int   expectBLayerHit,       int nBLHits,
								int   nPIXhits,              int nPixelDeadSensors,    int nPixHoles,
								int   nSCThits,              int nSCTDeadSensors,      int nSCTHoles,   
								int   nTRTHits,              int nTRTOutliers,
								float eta);
	
	inline bool nMS3stationsMDThits(float nMDTIHitsCutVal, float nMDTMHitsCutVal, float nMDTOHitsCutVal, float nMDTBEEHitsCutVal, float nMDTBIS78HitsCutVal,
									int nMDTBIHits, int nMDTBMHits, int nMDTBOHits,
									int nMDTEIHits, int nMDTEMHits, int nMDTEOHits,
									int nMDTBEEHits, int nMDTBIS78Hits);
	inline bool nMShits(float nMDTIHitsCutVal, float nMDTMHitsCutVal, float nMDTOHitsCutVal, float nMDTBIS78HitsCutVal, float nMDTBEEHitsCutVal,
						float nRPCPhiHitsCutVal,
						int nMDTBIHits, int nMDTBMHits, int nMDTBOHits, int nMDTBIS78Hits, int nMDTBEEHits,
						int nRPCLayer1PhiHits, int nRPCLayer2PhiHits, int nRPCLayer3PhiHits);
	inline bool nMShits1(float nMDTB_IMO_HitsCutVal, float nMDTE_IMEO_HitsCutVal,
						 float nMDTBIS78HitsCutVal, float nMDTBEEHitsCutVal,
						 float nCSCEtaHitsCutVal,
						 float nMDTCSCsumCutVal, float nRPCTGCCSCsumsCutVal,
						 int nMDTBIHits, int nMDTBMHits, int nMDTBOHits,
						 int nMDTEIHits, int nMDTEMHits, int nMDTEEHits, int nMDTEOHits,
						 int nMDTBIS78Hits, int nMDTBEEHits,
						 int nRPCLayer1PhiHits, int nRPCLayer2PhiHits, int nRPCLayer3PhiHits,
						 int nTGCLayer1PhiHits, int nTGCLayer2PhiHits, int nTGCLayer3PhiHits, int nTGCLayer4PhiHits,
						 int nCSCEtaHits, int nCSCPhiHits);
	inline bool nMShits2(float nMDTB_IMO_HitsCutVal, float nMDTE_IMEO_HitsCutVal,
						 float nMDTBIS78HitsCutVal, float nMDTBEEHitsCutVal,
						 float nCSCEtaHitsCutVal,
						 float nRPCPhiHitsCutVal, float nTGCPhiHitsCutVal, float nCSCPhiHitsCutVal,
						 float nMDTCSCsumCutVal, float nRPCTGCsumsCutVal,
						 int nMDTBIHits, int nMDTBMHits, int nMDTBOHits,
						 int nMDTEIHits, int nMDTEMHits, int nMDTEEHits, int nMDTEOHits,
						 int nMDTBIS78Hits, int nMDTBEEHits,
						 int nRPCLayer1PhiHits, int nRPCLayer2PhiHits, int nRPCLayer3PhiHits,
						 int nTGCLayer1PhiHits, int nTGCLayer2PhiHits, int nTGCLayer3PhiHits, int nTGCLayer4PhiHits,
						 int nCSCEtaHits, int nCSCPhiHits);
	inline bool nMShitsRel16(float nMDTB_IMO_HitsCutVal, float nMDTE_IMO_HitsCutVal,
							 float nMDTBEEHitsCutVal, float nMDTEEHitsCutVal, float nMDTBIS78HitsCutVal, 
							 float nCSCEtaHitsCutVal,
							 float nPhiHitsCutVal,
							 float nMDTCSCsumCutVal, float nRPCTGCCSCsumsCutVal,
							 int nMDTBIHits, int nMDTBMHits, int nMDTBOHits,
							 int nMDTEIHits, int nMDTEMHits, int nMDTEOHits,
							 int nMDTBEEHits, int nMDTEEHits, int nMDTBIS78Hits,
							 int nRPCLayer1PhiHits, int nRPCLayer2PhiHits, int nRPCLayer3PhiHits,
							 int nTGCLayer1PhiHits, int nTGCLayer2PhiHits, int nTGCLayer3PhiHits, int nTGCLayer4PhiHits,
							 int nCSCEtaHits, int nCSCPhiHits);
	inline bool nMShits2noCSCphi(float nMDTB_IMO_HitsCutVal, float nMDTE_IMEO_HitsCutVal,
								 float nMDTBIS78HitsCutVal, float nMDTBEEHitsCutVal,
								 float nCSCEtaHitsCutVal,
								 float nRPCPhiHitsCutVal, float nTGCPhiHitsCutVal,
								 float nMDTCSCsumCutVal, float nRPCTGCsumsCutVal,
							     int nMDTBIHits, int nMDTBMHits, int nMDTBOHits,
							     int nMDTEIHits, int nMDTEMHits, int nMDTEEHits, int nMDTEOHits,
							     int nMDTBIS78Hits, int nMDTBEEHits,
							     int nRPCLayer1PhiHits, int nRPCLayer2PhiHits, int nRPCLayer3PhiHits,
							     int nTGCLayer1PhiHits, int nTGCLayer2PhiHits, int nTGCLayer3PhiHits, int nTGCLayer4PhiHits,
							     int nCSCEtaHits);
				 
	inline bool pTmatchingRatioCut(float pTmatchHighRatioCutVal,
								   float pTmatchLowRatioCutVal,
								   float me_qOp_a, float me_theta_a,
								   float id_qOp_a, float id_theta_a,
								   float me_qOp_b, float me_theta_b,
								   float id_qOp_b, float id_theta_b);
	inline bool pTmatchingAbsDiffCut(float pTmatchDiffCutVal,
									 float me_qOp_a, float me_theta_a,
									 float id_qOp_a, float id_theta_a,
									 float me_qOp_b, float me_theta_b,
									 float id_qOp_b, float id_theta_b);
	inline bool impactParameterCut(float d0CutVal, float z0CutVal,
								   float d0a, float d0b,
								   float z0a, float z0b);
	inline bool impactParameterCut( float d0CutVal, float z0CutVal, float d0, float z0);
	inline bool pTandEtaCut(float pTCutVal, float etaCutVal, float pT, float eta);
	inline bool pTandEtaTightCut(float pTCutVal, float etaTightCutVal, float pT, float eta);
	inline bool pTandEtaBarrelCut(float pTCutVal, float etaBarrelCutVal, float pT, float eta);
	inline bool pTandEtaCut(float pTCutVal, float etaCutVal, float me_qOp, float me_theta, float eta );
	inline bool pTandEtaTightCut(float pTCutVal, float etaTightCutVal, float me_qOp, float me_theta, float eta );
	inline bool pTandEtaBarrelCut(float pTCutVal, float etaBarrelCutVal, float me_qOp, float me_theta, float eta );
	inline bool pairXXisolation( float isolationCutVal, string sIsoValName, float pTmua, float pTmub, float pTconea, float pTconeb);
	
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

private:
	int m_iVtx;

};
#endif

