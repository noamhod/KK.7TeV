/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#ifndef SELECTION_H
#define SELECTION_H

namespace cuts
{

class selection : public kinematics
{
public:
	bool b_print;
	
public:
	selection();
	~selection();
	
	void sinitialize();
	void sfinalize();
	
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
	// * * * preselection simple methods * * *
	
	inline bool findBestVertex(int nTypeCut, int nTracksCut, float z0cut,
						vector<int>* v_vxp_nTracks, vector<int>* v_vxp_type, vector<float>* v_vxp_z);
	inline int getPVindex();
	inline int getPVindex(int nTypeCut, int nTracksCut, float z0cut,
						  vector<int>* v_vxp_nTracks, vector<int>* v_vxp_type, vector<float>* v_vxp_z);
	
	
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
	// * * * simple cuts methods * * *
	
	inline bool isGRLCut(    float isGRLCutVal,    int isGRL );
	inline bool triggerCut(  float triggerCutVal,  int isTrigger, string triggerName );
	
	inline bool pTCut(           float pTCutVal,           float pt );
	inline bool pTCut(           float pTCutVal,           float me_qOp, float me_theta );
	inline bool etaCut(          float etaCutVal,          float Eta );
	
	inline bool etaSumCut(       float etaSumCutVal,       TLorentzVector* pa, TLorentzVector* pb );
	inline bool imassCut(        float imassCutVal,        TLorentzVector* pa, TLorentzVector* pb );
	inline bool imassMaxCut(     float imassCutVal,        TLorentzVector* pa, TLorentzVector* pb );

	inline bool d0Cut(          float d0CutVal, float d0 );
	inline bool z0Cut(          float z0CutVal, float z0 );
	inline bool oppositeChargeCut( float ca, float cb );
	inline bool oppositeChargeCut( float oppositeChargeCutVal, float ca, float cb );
	
	inline bool isCombMuCut( float isCombMuCutVal, int isCombMu );

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
						   
	inline bool nIDhitsCut(float expectBLayerHitCutVal,
						   float nBLHitsCutVal, 
						   float sumPIXhitsAndPixelDeadSensorsCutVal,
						   float sumSCThitsAndSCTDeadSensorsCutVal,
						   float sumPIXandSCTHolesCutVal,
						   float sumTRThitsAndTRTOutliersCutVal,
						   float etaAbsThreshold,
						   float nTRToutlierRatioThreshold,
						   int   expectBLayerHit,       int nBLHits,
						   int   nPIXhits,              int nPixelDeadSensors,    int nPixHoles,
						   int   nSCThits,              int nSCTDeadSensors,      int nSCTHoles,   
						   int   nTRTHits,              int nTRTOutliers,
						   float Eta);
						 
	inline bool nMShitsCut(float nMDTBIMOHitsCutVal, float nMDTEIMOHitsCutVal, float nCSCEtaHitsCutVal,
						   float nMDTBarrel_LogicSum, float nMDTorCSCEndcap_LogicSum,
						   float nMDTBEEHitsCutVal, float nMDTEEHitsCutVal, float nMDTBIS78HitsCutVal, 
						   float nRPCLayerPhiHitsCutsVal, float nTGCLayerPhiHitsCutsVal, float nCSCLayerPhiHitsCutVal,
						   float nRPCTGCCSC_LogicSum,
						   int nMDTBIHits, int nMDTBMHits, int nMDTBOHits,
						   int nMDTEIHits, int nMDTEMHits, int nMDTEOHits,
						   int nMDTBEEHits, int nMDTEEHits, int nMDTBIS78Hits,
						   int nRPCLayer1PhiHits, int nRPCLayer2PhiHits, int nRPCLayer3PhiHits,
						   int nTGCLayer1PhiHits, int nTGCLayer2PhiHits, int nTGCLayer3PhiHits, int nTGCLayer4PhiHits,
						   int nCSCEtaHits, int nCSCPhiHits);
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

private:
	int m_iVtx;

};

}
#endif

