/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#define GRLinterface_cxx
#include "GRLinterface.C"

#define selection_cxx
#include "selection.C"

#define graphicObjects_cxx
#include "graphicObjects.C"

#define cutFlowHandler_cxx
#include "cutFlowHandler.C"

#define muon_staco_cxx
#include "muon_staco.C"

#define muon_muid_cxx
#include "muon_muid.C"

#define offlineTree_cxx
#include "offlineTree.C"

#define offTree_cxx
#include "offTree.C"

#ifndef ANALYSIS_H
#define ANALYSIS_H

class analysis : public physics, public selection, public graphicObjects
{
public:
	// pointers to classes
	physics*        m_phys;

	graphicObjects* m_graphicobjs;

	cutFlowHandler* m_cutFlowHandler;
	
	muon_muid*      m_muid;
	muon_staco*     m_mustaco;
	
	GRLinterface*   m_analysis_grl;

	//offlineTree*    m_offlineTree;
	offTree*        m_offTree;

	// variables
	TMapsvd* m_cutFlowMapSVD;
	TMapds*  m_cutFlowOrdered;
	TMapsi*  m_cutFlowNumbers;
	
	TFile*		m_treeFile;

	Bool_t b_isGRL;
	
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
	analysis();
	analysis(physics* phys, graphicObjects* m_graphicobjs, cutFlowHandler* cutFlowHandler, GRLinterface* grl, TFile* treeFile);
	~analysis();

	void initialize();
	void finalize();

	void fillCutFlow(string sCurrentCutName, TMapsd& values2fill);

	//void executeTree(bool isendofrun);
	void executeBasic();
	void executeAdvanced();
	void executeCutFlow();
	
	void write();

private:

};
#endif

