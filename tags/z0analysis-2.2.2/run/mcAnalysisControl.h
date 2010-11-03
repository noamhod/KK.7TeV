/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#define chains_cxx
#include "chains.C"

#define mcAnalysis_cxx
#include "mcAnalysis.C"

#ifndef MCANALYSISCONTROL_H
#define MCANALYSISCONTROL_H

class mcAnalysisControl : public chains
{
	public:
		// from MakeClass
		mcPhysics*      m_mcPhys;
		TFile*          m_histfile;
		TFile*          m_treefile;
		mcAnalysis*     m_mcAnalysis;
		
		TDirectory*     m_dirAllCuts;
		TDirectory* 	m_dirNoCuts;
		TDirectory* 	m_dirCutFlow;


		// run control
		Long64_t l64t_nentries;
		Long64_t l64t_nbytes;
		Long64_t l64t_nb;
		Long64_t l64t_jentry;
		Long64_t l64t_ientry;
	
		Long64_t l64t_mod;
		Long64_t l64t_startEvent;
		Long64_t l64t_stopEvent;
	
	public:
		mcAnalysisControl();
		~mcAnalysisControl();
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

