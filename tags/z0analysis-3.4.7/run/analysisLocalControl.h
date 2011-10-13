/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#define chainMaker_cxx
#include "chainMaker.C"

#define analysis_cxx
#include "analysis.C"

#ifndef ANALYSISLOCALCONTROL_H
#define ANALYSISLOCALCONTROL_H

class analysisLocalControl : public chainMaker/*, public utilities*/
{
	public:
		// from MakeClass
		WZphysD3PD*   m_WZphysD3PD;
		GRLinterface* m_GRL;
		analysis*     m_analysis;
		
		TFile*        m_histfile;
		TFile*        m_treefile;
		
		TDirectory*   m_dirCutProfile;
		TDirectory*   m_dirAllCuts;
		TDirectory*   m_dirNoCuts;
		TDirectory*   m_dirCutFlow;
		TDirectory*   m_dirFit;
		TDirectory*   m_dirPerformance;
		TDirectory*   m_dirEff;
		TDirectory*   m_dirTruth;
		
		// locals
		string m_muRecAlgo;
		string m_pTsmearingType;
		string m_MCPtag;
		string m_RunType;
		bool   m_isMC;
		int    m_msglvl;

		// run control
		Long64_t l64t_nentries;
		Long64_t l64t_nbytes;
		Long64_t l64t_nb;
		Long64_t l64t_jentry;
		Long64_t l64t_ientry;
	
		Long64_t l64t_mod;
		Long64_t l64t_startEvent;
		Long64_t l64t_stopEvent;
		
		ProcInfo_t pi;

		vector<int> vEntries;
		vector<double> vResMemory;
		vector<double> vVirMemory;
		
		
		// for matching candidates
		vector<double> runNumber;
		vector<double> lumiBlock;
		vector<double> eventNumber;
		vector<double> mass_cb;
		vector<double> mass_id;
		vector<double> mass_me;
		vector<double> pT1;
		vector<double> pT2;
	
	public:
		analysisLocalControl();
		~analysisLocalControl();
		
		//void GetEntryMinimal(Long64_t entry);
		
		void setRunControl(string localRunControlFile);
		void initialize(int runNumber = 0, string runs="ALLRUNS", string basedir="", string localRunControlFile = "localRunControl_noSkim.txt");
		void finalize();
		
		void book();
		void draw();
		void fits();
		void analyze();
		void loop(Long64_t startEvent = 0, Long64_t stopAfterNevents = 0/*kMaxLong64*/);
		void loop(int runNumber);
		void loop(string sPeriodStart, string sPeriodEnd, Long64_t l64t_initialGuess);

	private:
};
#endif

