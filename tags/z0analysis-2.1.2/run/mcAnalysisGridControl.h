/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#define mcAnalysis_cxx
#include "mcAnalysis.C"

#ifndef MCANALYSISGRIDCONTROL_H
#define MCANALYSISGRIDCONTROL_H

class mcAnalysisGridControl : public mcAnalysis
{
	public:
		// from MakeClass
		mcPhysics* m_mcPhys;		

		// pointers
		TFile*          m_rootfile;
		TChain*			m_chain;
		
		TDirectory*     m_dirAllCuts;
		TDirectory* 	m_dirNoCuts;
		TDirectory* 	m_dirCutFlow;
		
		mcAnalysis*       m_mcAnalysis;
		graphicObjects* m_graphics;
		cutFlowHandler* m_cutFlowHandler;

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
		mcAnalysisGridControl();
		mcAnalysisGridControl( TChain* inchain, TFile* outfile );
		~mcAnalysisGridControl();
		void   initialize();
		void   finalize();
		void   book();
		void   draw();
		void   analyze();
		void   loop(Long64_t startEvent = 0, Long64_t stopAfterNevents = 0);

	private:
};
#endif

