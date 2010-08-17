/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#define analysis_cxx
#include "analysis.C"

#ifndef analysisGridControl_H
#define analysisGridControl_H

class analysisGridControl : public analysis
{
	public:
		// from MakeClass
		physics* m_phys;		

		// pointers
		TFile*          m_rootfile;
		TChain*			m_chain;
		
		TDirectory*     m_dirAllCuts;
		TDirectory* 	m_dirNoCuts;
		TDirectory* 	m_dirCutFlow;
		
		analysis*       m_analysis;
		graphicObjects* m_graphics;
		GRLinterface*   m_GRL; 

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
		analysisGridControl();
		analysisGridControl( TChain* inchain, TFile* outfile );
		~analysisGridControl();
		void   initialize();
		void   finalize();
		void   book();
		void   draw();
		void   analyze();
		void   loop(Long64_t startEvent = 0, Long64_t stopAfterNevents = 0);

	private:
};
#endif

