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

inline static int getPhiSector(float muonPhiSigned)
{
	_DEBUG("getPhiSector");

	// Map [-Pi..Pi] to [0..2Pi]
	float muonPhi = muonPhiSigned;
	if(muonPhi<0) muonPhi += 2.*TMath::Pi();

	int sector = -1;

	float widthLarge = 0.50;  // (BML)
	float widthSmall = 0.36;  // (BOS)

	float overlap = (8*(widthLarge + widthSmall) - 2*TMath::Pi() ) / 16.;

	widthLarge -= overlap;
	widthSmall -= overlap;

	float edge[18];
	edge[0]  = 0;
	edge[17] = 2*TMath::Pi();

	for(int i=0 ; i<=7 ; i++)
	{
		edge[2*i+1] = i*(widthLarge + widthSmall) + widthLarge/2.;
		edge[2*i+2] = i*(widthLarge + widthSmall) + widthLarge/2 + widthSmall;
	}

	for(int j=0 ; j<=16 ; j++)
	{
		//cout << edge[j] << " - " << edge[j+1] << endl;
		if(muonPhi>=edge[j] && muonPhi<edge[j+1])
		{
			sector = j+1;
			break;
		}
	}

	if(sector==17) sector = 1;
	if(sector==-1) _ERROR("Error in getPhiSector: sector not found");

	return sector;
}

static inline void setMuonMomentumSignificance(vector<float>& mu_sig_diff_qoverp,
											   vector<float>* mu_me_qoverp,
											   vector<float>* mu_id_qoverp,
											   vector<float>* mu_me_cov_qoverp_exPV,
											   vector<float>* mu_id_cov_qoverp_exPV)
{
	//-----MuonMomentum-Significance-(calculated before smearing)-----//
	float mu_diff_qoverp     = 0;
	float mu_err_diff_qoverp = 1;
	
	for(unsigned int i=0; i<mu_me_qoverp->size();i++)
	{
		mu_diff_qoverp     = /* 1.e6 * */(mu_me_qoverp->at(i) - mu_id_qoverp->at(i));
		mu_err_diff_qoverp = /* 1.e6 * */sqrt(mu_me_cov_qoverp_exPV->at(i) + mu_id_cov_qoverp_exPV->at(i));

		// Signed momentum difference significance
		mu_sig_diff_qoverp.push_back(mu_diff_qoverp / mu_err_diff_qoverp);
	}
}

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
	inline bool oppositeChargeCandidatesCut( vector<float>* v_charge, vector<bool>& v_QAflag);
	
	
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
	inline bool antid0Cut(      float d0CutVal, float d0 );
	inline bool antiz0Cut(      float z0CutVal, float z0 );
	inline bool oppositeChargeCut( float ca, float cb );
	inline bool oppositeChargeCut( float oppositeChargeCutVal, float ca, float cb );
	
	inline bool isCombMuCut( float isCombMuCutVal, int isCombMu );

	inline bool isolationXXCut( float isolationCutVal, string sIsoValName, float pTmu, float pTcone );
	inline bool isolationXXCut( float isolationCutVal, string sIsoValName, float qOp, float theta, float pTcone );
	
	inline bool constrainedAntiIsolationXXCut( float minIsolationCutVal, float maxIsolationCutVal, string sIsoValName, float pTmu, float pTcone );
	
	inline bool antiIsolationXXCut( float isolationCutVal, string sIsoValName, float pTmu, float pTcone );
	
	inline bool eTisolationXXCut( float isolationCutVal, string sIsoValName, float eTcone );
	inline bool eTantiIsolationXXCut( float isolationCutVal, string sIsoValName, float eTcone );
	
	
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
	inline bool nMShitsCut3233(float MuonPhiHitsCut,    float MuonPhiLayerCut,  float MuonMDTHitsCut,  float MuonMomDiffSigCut,
							   float MuonPhiHitsCut2,   float MuonPhiLayerCut2, float MuonMDTHitsCut2, float MuonMomDiffSigCut2,
							   bool allow3_3st, bool allow3_2st, vector<bool>& muQAflags, vector<float>& mu_sig_diff_qoverp,
							   vector<float>* mu_eta, vector<float>* mu_phi, vector<float>* mu_charge,
							   vector<int>* mu_nMDTBIHits, vector<int>* mu_nMDTBMHits, vector<int>* mu_nMDTBOHits,
							   vector<int>* mu_nMDTEIHits, vector<int>* mu_nMDTEMHits, vector<int>* mu_nMDTEOHits,
							   vector<int>* mu_nMDTBEEHits, vector<int>* mu_nMDTEEHits, vector<int>* mu_nMDTBIS78Hits,
							   vector<int>* mu_nRPCLayer1PhiHits, vector<int>* mu_nRPCLayer2PhiHits, vector<int>* mu_nRPCLayer3PhiHits,
							   vector<int>* mu_nTGCLayer1PhiHits, vector<int>* mu_nTGCLayer2PhiHits, vector<int>* mu_nTGCLayer3PhiHits, vector<int>* mu_nTGCLayer4PhiHits,
							   vector<int>* mu_nCSCEtaHits, vector<int>* mu_nCSCPhiHits,
							   int& ai, int& bi);
						   
	inline bool didmuTriggerCut( float drCutVal, float trig_dr, int roi_index );
	inline bool isLooseNoTightCut( float isLooseCutVal, float isTightCutval, int isLoose, int isTight );
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

private:
	int m_iVtx;

};

}
#endif

