/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#define analysisSkeleton_cxx
#include "analysisSkeleton.C"

#define GRLinterface_cxx
#include "GRLinterface.C"

#define WZphysD3PDmaker_cxx
#include "WZphysD3PDmaker.C"

#ifndef ANALYSIS_H
#define ANALYSIS_H

class analysis : public WZphysD3PD, public analysisSkeleton
{
public:
	// pointers
	WZphysD3PD*      m_WZphysD3PD;
	GRLinterface*    m_analysis_grl;
	WZphysD3PDmaker* m_WZphysD3PDmaker;
	TFile*		     m_treeFile;
	
	ofstream* fCandidates;
	
	// local
	string sRunType;
	string sMuonRecoAlgo;
	bool   m_isMC;
	int    nMus;
	
	// temp
	int nSkim;
	int nAll;
	int n0mu;
	int n1mu;
	int n2mu;
	int n3mu;
	int n4mu;
	int nNmu;

public:
	analysis();
	analysis(string runtype,
			 string murecalg,
			 bool isMC,
			 WZphysD3PD* wzphysd3pd,
			 GRLinterface* grl,
			 TFile* treeFile,
			 string sCutFlowFilePath,
			 string sPeriodsFilePath,
			 string sEventDumpFilePath) :
	analysisSkeleton(sCutFlowFilePath,sPeriodsFilePath,sEventDumpFilePath)
	{
		sRunType       = runtype;  // grid OR local
		sMuonRecoAlgo  = murecalg; // staco OR muid
		m_isMC         = isMC;     // ...
		
		m_WZphysD3PD   = wzphysd3pd;
		m_analysis_grl = grl;	
		m_treeFile     = treeFile;

		if(m_treeFile!=NULL) m_WZphysD3PDmaker  = new WZphysD3PDmaker( m_WZphysD3PD, sRunType, m_isMC, m_treeFile );
		
		m_trees_counter_mod   = 1000; 
		m_allCuts_counter     = 0;
		m_cutsProfile_counter = 0;
		m_efficiency_counter  = 0;
		
		nSkim = 0;
		nAll = 0;
		n0mu = 0;
		n1mu = 0;
		n2mu = 0;
		n3mu = 0;
		n4mu = 0;
		nNmu = 0;
		
		if(!m_isMC)
		{
			string fCandidatesName;
			if(sRunNumber!="") fCandidatesName = "tmp/candidates."+sRunNumber+".txt"; // sRunNumber is static string from basicIncludes.h
			else               fCandidatesName = "candidates.txt";
			fCandidates = new ofstream(fCandidatesName.c_str());
		}
	}
	~analysis();

	void setEventVariables();
	void setStacoVariables();
	void setMuidVariables();
	void setTrigVariables();
	
	void execute();
	
	void write();

private:

};
#endif

