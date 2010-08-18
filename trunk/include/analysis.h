/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#define GRLinterface_cxx
#include "GRLinterface.C"

#define selection_cxx
#include "selection.C"

#define graphicObjects_cxx
#include "graphicObjects.C"

#define muon_staco_cxx
#include "muon_staco.C"

#define muon_muid_cxx
#include "muon_muid.C"

#define offlineTree_cxx
#include "offlineTree.C"

#ifndef ANALYSIS_H
#define ANALYSIS_H

class analysis : public physics, public selection, public graphicObjects
{
	public:
		// pointers to classes
		physics*        m_phys;

		graphicObjects* m_graphicobjs;

		muon_muid*      m_muid;
		muon_staco*     m_mustaco;
		
		GRLinterface*   m_analysis_grl;

		offlineTree*    m_offlineTree;

		// variables
		TMapsd*         m_cutFlowMap;
		TMapds*         m_cutFlowOrdered;
		TMapsi*         m_cutFlowNumbers;
		
		TFile*		m_treeFile;

		Bool_t b_isGRL;
		int    nAllEvents;

	public:
		analysis();
		analysis(physics* phys, graphicObjects* m_graphicobjs, GRLinterface* grl, TFile* treeFile);
		~analysis();

		void initialize();
		void finalize();

		void enableGeneralBranches();

		void printCutFlowNumbers(Long64_t chainEntries);
		void fillCutFlow(string sCurrentCutName, TMapsd& values2fill);

		void executeTree(bool isendofrun);
		void executeBasic();
		void executeAdvanced();
		void executeCutFlow();
		
		void write();

		void    readCutFlow(string sCutFlowFilePath);
		TMapsd* getCutFlowMapPtr();
		TMapds* getCutFlowOrderedPtr();

	private:

};
#endif

