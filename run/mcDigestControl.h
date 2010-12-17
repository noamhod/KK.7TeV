/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#define digestChains_cxx
#include "digestChains.C"

#define mcDigestAnalysis_cxx
#include "mcDigestAnalysis.C"

#ifndef MCDIGESTCONTROL_H
#define MCDIGESTCONTROL_H

class mcDigestControl : public digestChains, public utilities
{
	public:
		// from MakeClass
		mcDigestPhysics*  m_mcDigestPhys;
		TFile*            m_histfile;
		TFile*            m_treefile;
		mcDigestAnalysis* m_mcDigestAnalysis;
		
		TDirectory*     m_dirCutProfile;
		TDirectory*     m_dirAllCuts;
		TDirectory* 	m_dirNoCuts;
		TDirectory* 	m_dirCutFlow;
		TDirectory* 	m_dirFit;
		TDirectory* 	m_dirPerformance;
		TDirectory* 	m_dirAfb;
		TDirectory* 	m_dirEff;

		// run control
		Long64_t l64t_nentries;
		Long64_t l64t_nbytes;
		Long64_t l64t_nb;
		Long64_t l64t_jentry;
		Long64_t l64t_ientry;
	
		Long64_t l64t_mod;
		Long64_t l64t_startEvent;
		Long64_t l64t_stopEvent;
		
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
		mcDigestControl();
		~mcDigestControl();
		void   initialize();
		void   finalize();
				
		void   book();
		void   draw();
		void   fits();
		void   analyze();
		void   loop(Long64_t startEvent = 0, Long64_t stopAfterNevents = kMaxLong64);
		
		void getCandidates(string sFilePath);
		bool matchCandidates();
		void loopCandidates();

	private:
};
#endif

