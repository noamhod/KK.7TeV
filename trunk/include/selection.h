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
	
	TMapsd* m_cutFlowMap;
	TMapds* m_cutFlowOrdered;

public:
	selection();
	~selection();
	
	void sinitialize();
	void sfinalize();

	void initSelectionCuts(TMapsd* cutFlowMap, TMapds* cutFlowOrdered); // called by analysis.C
	
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
	// all cuts methods:
	
	bool isGRLCut( double isGRLCutVal, int isGRL );
	bool isL1_MU6Cut( double isL1_MU6CutVal, int isL1_MU6 );
	
	bool pTCut(           double pTCutVal,           TLorentzVector* pa, TLorentzVector* pb );
	bool etaCut(          double etaCutVal,          TLorentzVector* pa, TLorentzVector* pb );
	bool cosThetaDimuCut( double cosThetaDimuCutVal, TLorentzVector* pa, TLorentzVector* pb );
	bool imassCut(        double imassCutVal,        TLorentzVector* pa, TLorentzVector* pb );

	bool d0Cut(          double d0CutVal, double d0a, double d0b );
	bool z0Cut(          double z0CutVal, double z0a, double z0b );
	bool oppositeChargeCut( double ca, double cb );
	
	bool prmVtxNtracksCut( double prmVtxNtracksCutVal, vector<int>* nPVtracksPtr, int& pvtxIndex );
	bool prmVtxTypeCut( double prmVtxTypeCutVal, vector<int>* nPVtypePtr, int& pvtxIndex );
	bool prmVtxZ0Cut( double prmVtxZ0CutVal, vector<double>* PVz0Ptr, vector<double>* PVz0errPtr, int& pvtxIndex );
	bool isCombMuCut( double isCombMuCutVal, int isCombMu );
	bool nSCThitsCut( double nSCThitsCutVal, int nSCThits );
	bool nPIXhitsCut( double nPIXhitsCutVal, int nPIXhits );
	bool nIDhitsCut( double nIDhitsCutVal, int nIDhits );
	bool pTmatchLowRatioCut();
	bool pTmatchHighRatioCut();
	bool impcatParamZ0Cut( double impcatParamZ0CutVal, double impPrmZ0);
	bool impcatParamD0Cut( double impcatParamD0CutVal, double impPrmD0 );
	bool isolation20Cut( double isolationCutVal, double pTmu, double pTcone );
	bool isolation30Cut( double isolationCutVal, double pTmu, double pTcone );
	bool isolation40Cut( double isolationCutVal, double pTmu, double pTcone );
	
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
	
	void buildMuonPairMap(	TMapii& mupair,
							double ca, int ia,
							double cb, int ib);

	void buildMuonPairMap(	TMapii& mupair,
							TLorentzVector* pa, double ca, double d0a, double z0a, int ia,
							TLorentzVector* pb, double cb, double d0b, double z0b, int ib );

	bool removeOverlaps(	TMapii& mupair, int ia, int ib );
	void findBestMuonPair(	TMapii& mupair, int& ia, int& ib);

private:

};
#endif

