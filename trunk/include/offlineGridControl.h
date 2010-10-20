/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#define offlineAnalysis_cxx
#include "offlineAnalysis.C"

#ifndef OFFLINEGRIDCONTROL_H
#define OFFLINEGRIDCONTROL_H

class offlineGridControl : public offlineAnalysis
{
	public:
		// from MakeClass
		offlinePhysics* m_offPhys;		

		// pointers
		TFile*          m_rootfile;
		TChain*			m_chain;
		
		TDirectory*     m_dirAllCuts;
		TDirectory* 	m_dirNoCuts;
		TDirectory* 	m_dirCutFlow;
		
		offlineAnalysis* m_offlineAnalysis;
		graphicObjects*  m_graphics;
		//GRLinterface*   m_GRL; 
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
		offlineGridControl();
		offlineGridControl( TChain* inchain, TFile* outfile );
		~offlineGridControl();
		void   initialize();
		void   finalize();
		void   book();
		void   draw();
		void   analyze();
		void   loop(Long64_t startEvent = 0, Long64_t stopAfterNevents = 0);

	private:
};
#endif

