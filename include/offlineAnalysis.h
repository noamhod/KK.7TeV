/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#define selection_cxx
#include "selection.C"

#define graphicObjects_cxx
#include "graphicObjects.C"

#define fit_cxx
#include "fit.C"

#define offlineTreeDigest_cxx
#include "offlineTreeDigest.C"

/*
#define muon_staco_cxx
#include "muon_staco.C"

#define muon_muid_cxx
#include "muon_muid.C"
*/

#ifndef OFFLINEANALYSIS_H
#define OFFLINEANALYSIS_H

class offlineAnalysis : public offlinePhysics, public selection, public graphicObjects
{
	public:
		// pointers to classes
		graphicObjects* m_graphicobjs;

		fit* m_fit;
		TF1* m_fFitted;
		TF1* m_fGuess;
		
		TFile* m_treeFile;
		/*
		muon_muid*      m_muid;
		muon_staco*     m_mustaco;
		*/		

		offlinePhysics* m_offPhys;
		
		offlineTreeDigest* m_offTreeDigest;

		// variables
		TMapsd*         m_cutFlowMap;
		TMapds*         m_cutFlowOrdered;
		TMapsi*         m_cutFlowNumbers;
		
		Bool_t b_isGRL;
		int    nAllEvents;
		string m_sLastCut2Hist;

	public:
		offlineAnalysis();
		offlineAnalysis(offlinePhysics* offPhys, graphicObjects* graphicobjs, TFile* treeFile, string sLastCut2Hist = "GRL");
		~offlineAnalysis();

		void initialize();
		void finalize();

		void resetLastCut2Hist(string sLastCut2Hist = "GRL") {m_sLastCut2Hist = sLastCut2Hist;}
		
		void fitter();

		void printCutFlowNumbers(Long64_t chainEntries);
		void fillCutFlow(string sCurrentCutName, TMapsd& values2fill);

		void executeBasic();
		void executeCutFlow();
		void write();

		void    readCutFlow(string sCutFlowFilePath);
		TMapsd* getCutFlowMapPtr();
		TMapds* getCutFlowOrderedPtr();

	private:

};
#endif

