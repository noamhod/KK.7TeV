/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#define fit_cxx
#include "fit.C"

#define selection_cxx
#include "selection.C"

#define graphicObjects_cxx
#include "graphicObjects.C"

#define cutFlowHandler_cxx
#include "cutFlowHandler.C"

#define eventDumper_cxx
#include "eventDumper.C"


#ifndef COMBINEDSELECTION_H
#define COMBINEDSELECTION_H

class combinedSelection : public selection
{
public:
	///////////////////////
	// pointers
	graphicObjects* m_graphicobjs;
	
	cutFlowHandler* m_cutFlowHandler;
	
	TMapsvd* m_cutFlowMapSVD;
	TMapds*  m_cutFlowOrdered;
	TMapds*  m_cutFlowTypeOrdered;
	TMapsi*  m_cutFlowNumbers;
	
	eventDumper* m_eventDumper;
	bool doEventDump;
	
	fit* m_fitter;
	
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
	
	// * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * *
	// muon & vertex variables for preselection

	// event level
	int runnumber;
	int lumiblock;
	int eventnumber;
	int isGRL;
	int isL1MU6;
	int isEF_mu13;
	
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
	
	void initCombinedSelection(graphicObjects* graphicobjs, cutFlowHandler* cutFlowHandler, fit* fitter, string sEventDumpFilePath = "");

	/* MUST BE CALLED AFTER THE ALLOCATION OF PRESELECTION VARIABLES */
	bool applyPreselection(string sRunType = "offline");
	
	/* SHOULD BE CALLED AFTER THE applyPreselection METHOD */
	bool setMUindices(TVectorP2VL& pmu, string sRunType = "offline"); 
	
	/* MUST BE CALLED AFTER THE setMUindices METHOD */
	/* MUST BE CALLED AFTER THE ALLOCATION OF MUON VARIABLES */
	void applySelection(TVectorP2VL& pmu, TMapsd& values2fill);

private:
	void setEventDumper(string sEventDumpFilePath);
	void runEventDumper(bool passCutFlow, int ai);
	
	void fillAfterCuts(bool passCutFlow, int counter, string sorderedcutname, TMapsd& values2fill);
	void fillBeforeCuts();

};
#endif

