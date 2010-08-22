/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#define offlineChains_cxx
#include "offlineChains.C"

#define offlineAnalysis_cxx
#include "offlineAnalysis.C"

#ifndef OFFLINECONTROL_H
#define OFFLINECONTROL_H

class offlineControl : public offlineChains, public offlineAnalysis
{
	public:
		// from MakeClass
		offlinePhysics* m_offPhys;
		cutFlowHandler* m_cutFlowHandler;
		
		// pointers
		TFile*          m_histfile;
		TFile*          m_treefile;
		
		TDirectory*     m_dirAllCuts;
		TDirectory* 	m_dirNoCuts;
		TDirectory* 	m_dirCutFlow;
		TDirectory* 	m_dirFit;
		
		offlineAnalysis* m_offlineAnalysis;
		graphicObjects*  m_graphics;

		// run control
		Long64_t l64t_nentries;
		Long64_t l64t_nbytes;
		Long64_t l64t_nb;
		Long64_t l64t_jentry;
		Long64_t l64t_ientry;
	
		Long64_t l64t_mod;
		Long64_t l64t_startEvent;
		Long64_t l64t_stopEvent;
		
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
		offlineControl();
		~offlineControl();
		void   initialize();
		void   finalize();
		
		void resetLastCut2Hist(string sLastCut2Hist = "GRL") {m_offlineAnalysis->m_sLastCut2Hist = sLastCut2Hist;}
		
		void   book();
		void   draw();
		void   analyze();
		void   loop(Long64_t startEvent = 0, Long64_t stopAfterNevents = kMaxLong64);
		
		void getCandidates(string sFilePath);
		bool matchCandidates();
		void loopCandidates();

	private:
};
#endif

