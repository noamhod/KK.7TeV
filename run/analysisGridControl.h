/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#define analysis_cxx
#include "analysis.C"

#ifndef ANALYSISGRIDCONTROL_H
#define ANALYSISGRIDCONTROL_H

class analysisGridControl : public utilities
{
	public:
		// pointers
		physics*        m_phys;
		GRLinterface*   m_GRL;
		TFile*          m_rootfile;
		TChain*			m_chain;
		analysis*       m_analysis;
		
		// more pointers
		TDirectory*     m_dirCutProfile;
		TDirectory*     m_dirFit;
		TDirectory*     m_dirAllCuts;
		TDirectory* 	m_dirNoCuts;
		TDirectory* 	m_dirCutFlow;
		TDirectory* 	m_dirPerformance;
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
	
		string m_muRecAlgo;
	
	public:
		analysisGridControl();
		analysisGridControl( TChain* inchain, TFile* outfile );
		~analysisGridControl();
		void   setRecAlgo(string muRecAlgo);
		void   initialize();
		void   finalize();
		void   book();
		void   draw();
		void   fits();
		void   analyze();
		void   loop(Long64_t startEvent = 0, Long64_t stopAfterNevents = 0);

	private:
};
#endif

