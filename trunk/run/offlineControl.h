/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:23 */
/* * * * * * * * * * * */

/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:22 */
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

		// pointers
		TFile*          m_histfile;
		
		TDirectory*     m_dirAllCuts;
		TDirectory* 	m_dirNoCuts;
		TDirectory* 	m_dirCutFlow;
		TDirectory* 	m_dirFit;
		
		TF1* m_fGuess;
		TF1* m_fFitted;
		
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
	
	public:
		offlineControl();
		~offlineControl();
		void   initialize();
		void   finalize();
		void   book();
		void   draw();
		void   analyze();
		void   loop(Long64_t startEvent = 0, Long64_t stopAfterNevents = kMaxLong64);

	private:
};
#endif

