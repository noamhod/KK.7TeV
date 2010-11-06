/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

/*
#define fit_cxx
#include "fit.C"

#define selection_cxx
#include "selection.C"

#define graphicObjects_cxx
#include "graphicObjects.C"

#define cutFlowHandler_cxx
#include "cutFlowHandler.C"

#define periodHandler_cxx
#include "periodHandler.C"

#define eventDumper_cxx
#include "eventDumper.C"
*/

#define analysisModules_cxx
#include "analysisModules.C"

#ifndef COMBINEDSELECTION_H
#define COMBINEDSELECTION_H

class combinedSelection : public analysisModules, public selection
{
public:
	///////////////////////
	// pointers
	/*
	graphicObjects* m_graphicobjs;
	
	cutFlowHandler* m_cutFlowHandler;
	TMapsvd* m_cutFlowMapSVD;
	TMapds*  m_cutFlowOrdered;
	TMapds*  m_cutFlowTypeOrdered;
	TMapsi*  m_cutFlowNumbers;
	
	periodHandler* m_periodHandler;
	TMapis*  m_firstrun2periodMap;
	TMapis*  m_lastrun2periodMap;
	TMapsvs* m_period2triggerMap;
	
	
	eventDumper* m_eventDumper;
	bool doEventDump;
	
	fit* m_fitter;
	*/
	
	//////////////////////
	// basic local vars
	TMapii muPairMap;
	//TMapsd values2fill;
	bool passCutFlow;
	bool passCurrentCut;
	int cutFlowMapSize;
	int counter;
	int ai;
	int bi;
	int iVtx;
	string sRunType;
	int currentRun;
	string sPeriod;
	string sCurrentPeriod;
	vector<string> vTriggers;
	
	// * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * *
	// muon & vertex variables for preselection

	// event level
	int runnumber;
	int lumiblock;
	int eventnumber;
	int isGRL;
	
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
   
	
	// mu staco (for the hipTmuon preselection)
	int mu_staco_n;
	vector<float>* mu_staco_pt;
	vector<float>* mu_staco_me_qoverp;
	vector<float>* mu_staco_me_theta;
	
	// vertexes (for the PV preselection)
	int vxp_n;
	vector<int>*   vxp_nTracks;
	vector<int>*   vxp_type;
	vector<float>* vxp_z;

	
	// * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * *
	// muon variables for selection
	
	// for the indices
	vector<float>* mu_staco_charge;
	
	////////////////////////
	// more variables
	double current_imass;
	double current_cosTheta;
	double current_mu_pT;
	double current_muplus_pT;
	double current_mu_eta;
	double current_muplus_eta;
	double current_cosmicCosth;
	double current_ipTdiff;
	double current_etaSum;
	
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
	double phi_a;
	double phi_b;
	
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
	combinedSelection();
	~combinedSelection();
	
	/*
	void initCombinedSelection(graphicObjects* graphicobjs,
							   cutFlowHandler* cutFlowHandler,
							   periodHandler* periods,
							   fit* fitter,
							   string sEventDumpFilePath = "");

	*/
	
	string getPeriodName();
	
	/* MUST BE CALLED AFTER THE ALLOCATION OF PRESELECTION VARIABLES */
	bool applyPreselection(string sRunType = "offline");
	
	/* SHOULD BE CALLED AFTER THE applyPreselection METHOD */
	bool setMUindices(TVectorP2VL& pmu, string sRunType = "offline"); 
	
	/* MUST BE CALLED AFTER THE setMUindices METHOD */
	/* MUST BE CALLED AFTER THE ALLOCATION OF MUON VARIABLES */
	void applySelection(TVectorP2VL& pmu, TMapsd& values2fill);

private:
	//void setEventDumper(string sEventDumpFilePath);
	void runEventDumper(bool passCutFlow, int ai);
	
	void fillAfterCuts(bool passCutFlow, int counter, string sorderedcutname, TMapsd& values2fill);
	void fillBeforeCuts();

};
#endif

