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

public:
	analysis();
	analysis(string runtype,
			 string murecalg,
			 bool ismc,
			 WZphysD3PD* wzphysd3pd,
			 GRLinterface* grl,
			 TFile* treeFile)
	{
		sRunType       = runtype;  // grid OR local
		sMuonRecoAlgo  = murecalg; // staco OR muid
		m_isMC         = ismc;     // ...
		
		m_WZphysD3PD   = wzphysd3pd;
		m_analysis_grl = grl;	
		m_treeFile     = treeFile;

		if(m_treeFile!=NULL) m_WZphysD3PDmaker  = new WZphysD3PDmaker( m_WZphysD3PD, sRunType, m_isMC, m_treeFile );
		
		m_trees_counter_mod   = 1000; 
		m_allCuts_counter     = 0;
		m_cutsProfile_counter = 0;
		m_efficiency_counter  = 0;
		m_truth_counter       = 0;
		
		EventHash = 0;
		
		alreadyFilled = false;
		
		previous_runnumber = 0;
		
		randGen = new TRandom();
		randGen->SetSeed(0); // Note that the machine clock is returned with a precision of 1 second.
		// If one calls SetSeed(0) within a loop and the loop time is less than 1s,
		// all generated numbers will be identical!
	}
	~analysis();
	
	void   setAllCandidatesFiles(string sCandFilePath = "", string srunnumber = "", string selector = "");
	string setMCPUFiles(string sPUFilePath = "", string srunnumber = "");

	void setEventVariables();
	void setStacoVariables();
	void setMuidVariables();
	void setTrigVariables();
	
	void execute();
	
	void write();

private:

};
#endif

