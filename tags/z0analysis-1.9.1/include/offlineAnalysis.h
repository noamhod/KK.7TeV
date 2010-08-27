/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#define selection_cxx
#include "selection.C"

#define graphicObjects_cxx
#include "graphicObjects.C"

#define fit_cxx
#include "fit.C"

#define offlineTreeDigest_cxx
#include "offlineTreeDigest.C"

#define cutFlowHandler_cxx
#include "cutFlowHandler.C"

/*
#define muon_staco_cxx
#include "muon_staco.C"

#define muon_muid_cxx
#include "muon_muid.C"
*/

#ifndef OFFLINEANALYSIS_H
#define OFFLINEANALYSIS_H

class offlineAnalysis : public offlinePhysics, public selection, public graphicObjects
{
public:
	// pointers to classes
	graphicObjects* m_graphicobjs;
	cutFlowHandler* m_cutFlowHandler;

	fit* m_fit;
	TF1* m_fFitted;
	TF1* m_fGuess;
	
	TFile* m_treeFile;
	/*
		muon_muid*      m_muid;
		muon_staco*     m_mustaco;
		*/		

	offlinePhysics* m_offPhys;
	
	offlineTreeDigest* m_offTreeDigest;

	// variables
	TMapsvd* m_cutFlowMapSVD;
	TMapds*  m_cutFlowOrdered;
	TMapsi*  m_cutFlowNumbers;
	
	Bool_t b_isGRL;
	//int    nAllEvents;
	string m_sLastCut2Hist;
	bool   m_bOldD3PDwarning;
	int    m_nPrevRunWithWarning;
	
	
	////////////////////////
	// calculate the necessary variables
	double current_imass;
	double current_cosTheta;
	double current_mu_pT;
	double current_mu_eta;
	
	// event level
	int runnumber;
	int lumiblock;
	int isGRL;
	int isL1MU6;
	
	// deprecated !!!
	double d0exPVa;
	double z0exPVa;
	double d0exPVb;
	double z0exPVb;
	
	// primary vertex:
	// at least one primary vtx passes the z selection
	vector<int>*   nPVtracksPtr;
	vector<int>*   nPVtypePtr;
	vector<float>* PVz0Ptr;
	vector<float>* PVz0errPtr;
	
	// combined muon ?
	int isMuaComb;
	int isMubComb;
	
	// inner detector hits
	int nSCThitsMua;
	int nSCThitsMub;
	int nPIXhitsMua;
	int nPIXhitsMub;
	int nIDhitsMua;
	int nIDhitsMub;
	
	// ID - MS pT matching: pT=|p|*sin(theta), qOp=charge/|p|
	double me_qOp_a;
	double id_qOp_a;
	double me_theta_a;
	double id_theta_a;
	double me_qOp_b;
	double id_qOp_b;
	double me_theta_b;
	double id_theta_b;
	
	// impact parameter
	double impPrmZ0;
	double impPrmD0;
	
	// isolation
	double mu_pTa;
	double mu_pTb;
	double pTcone20a;
	double pTcone20b;
	double pTcone30a;
	double pTcone30b;
	double pTcone40a;
	double pTcone40b;
	
	// charge
	double mu_charge_a;
	double mu_charge_b;
	////////////////////////

public:
	offlineAnalysis();
	offlineAnalysis(offlinePhysics* offPhys, graphicObjects* graphicobjs, TFile* treeFile, cutFlowHandler* cutFlowHandler, string sLastCut2Hist = "GRL");
	~offlineAnalysis();

	void initialize();
	void finalize();

	void resetLastCut2Hist(string sLastCut2Hist = "GRL") {m_sLastCut2Hist = sLastCut2Hist;}
	
	void fitter();

	void fillCutFlow(string sCurrentCutName, TMapsd& values2fill);

	bool isD3PDreconOld();
	
	void executeBasic();
	void executeCutFlow();
	void write();

private:

};
#endif

