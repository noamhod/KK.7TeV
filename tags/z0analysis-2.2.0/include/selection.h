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
	utilities* m_util;
	
	bool   b_print;
	
	TMapsvd* m_cutFlowMapSVD;
	TMapds*  m_cutFlowOrdered;
	TMapds*  m_cutFlowTypeOrdered;

public:
	selection();
	~selection();
	
	void sinitialize();
	void sfinalize();

	void initSelectionCuts(TMapsvd* cutFlowMapSVD, TMapds* cutFlowOrdered, TMapds* cutFlowTypeOrdered); // called by analysis, offlineAnalysis and digestAnalysis
	
	void buildMuonPairMap( TMapii& mupair, TVectorP2VL& pmu );

	bool removeOverlaps(	TMapii& mupair, int ia, int ib );
	
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
	// * * * preselection simple methods * * *
	bool oppositeChargePair(vector<float>* vcharge, int a, int b);
	
	bool findMostMassivePair(TVectorP2VL& pmu, TMapii& allmupairMap);
	void findMostMassivePair(vector<float>* vcharge, TVectorP2VL& pmu, TMapii& allmupairMap, int& iBest_a, int&iBest_b);
	
	bool findBestVertex(int nTracksCut, int nTypeCut, double z0Cut, int nvxp,
						vector<int>* v_vxp_nTracks, vector<int>* v_vxp_type, vector<float>* v_vxp_z);
	int getPVindex(int nTracksCut, int nTypeCut, double z0Cut, int nvxp,
				   vector<int>* v_vxp_nTracks, vector<int>* v_vxp_type, vector<float>* v_vxp_z);
	
	bool findHipTmuon(double hipTmuonCut, double MShipTmuonCut, int nmu,
					  vector<float>* v_pT, vector<float>* v_qoverp, vector<float>* v_theta);
	
	
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
	// * * * simple cuts methods * * *
	
	bool isGRLCut( double isGRLCutVal, int isGRL );
	bool isL1_MU6Cut( double isL1_MU6CutVal, int isL1_MU6 );
	bool isEF_muXCut( double isEF_muXCutVal, int isEF_muX );
	
	bool pTCut(           double pTCutVal,           TLorentzVector* pa, TLorentzVector* pb );
	bool etaCut(          double etaCutVal,          TLorentzVector* pa, TLorentzVector* pb );
	bool etaTightCut(     double etaTightCutVal,     TLorentzVector* pa, TLorentzVector* pb );
	bool cosThetaDimuCut( double cosThetaDimuCutVal, TLorentzVector* pa, TLorentzVector* pb );
	bool imassCut(        double imassCutVal,        TLorentzVector* pa, TLorentzVector* pb );

	bool d0Cut(          double d0CutVal, double d0a, double d0b ); // deprecated !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	bool z0Cut(          double z0CutVal, double z0a, double z0b ); // deprecated !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	bool oppositeChargeCut( double ca, double cb );
	bool oppositeChargeCut( double oppositeChargeCutVal, double ca, double cb );
	
	bool prmVtxNtracksCut( double prmVtxNtracksCutVal, int nPVtracks );
	bool prmVtxTypeCut( double prmVtxTypeCutVal, int nPVtype );
	bool prmVtxZ0Cut( double prmVtxZ0CutVal, double dPVz0, double dPVz0err );
	bool isCombMuCut( double isCombMuCutVal, int isCombMua, int isCombMub );
	bool nSCThitsCut( double nSCThitsCutVal, int nSCThits );
	bool nPIXhitsCut( double nPIXhitsCutVal, int nPIXhits );
	bool pTmatchRatioCut( double pTmatchHighRatioCutVal,
						  double pTmatchLowRatioCutVal,
						  double me_qOp, double me_theta,
						  double id_qOp, double id_theta );
	bool pTmatchAbsDiffCut(double pTmatchDiffCutVal,
						   double me_qOp, double me_theta,
						   double id_qOp, double id_theta );
	bool impcatParamZ0Cut( double impcatParamZ0CutVal, double impPrmZ0);
	bool impcatParamD0Cut( double impcatParamD0CutVal, double impPrmD0 );
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
	bool impactParameterCut( double impcatParamZ0CutVal, double impcatParamD0CutVal,
							 double impPrmZ0, double impPrmD0 );
	bool pairXXisolation( double isolationCutVal, string sIsoValName,
						  double pTmua, double pTmub, double pTconea, double pTconeb );
	
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

private:
	int m_iVtx;

};
#endif

