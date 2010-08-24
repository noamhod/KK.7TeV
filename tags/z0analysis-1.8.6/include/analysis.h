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

#define cutFlowHandler_cxx
#include "cutFlowHandler.C"

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

		cutFlowHandler* m_cutFlowHandler;
		
		muon_muid*      m_muid;
		muon_staco*     m_mustaco;
		
		GRLinterface*   m_analysis_grl;

		offlineTree*    m_offlineTree;

		// variables
		TMapsvd* m_cutFlowMapSVD;
		TMapds*  m_cutFlowOrdered;
		TMapsi*  m_cutFlowNumbers;
		
		TFile*		m_treeFile;

		Bool_t b_isGRL;

	public:
		analysis();
		analysis(physics* phys, graphicObjects* m_graphicobjs, cutFlowHandler* cutFlowHandler, GRLinterface* grl, TFile* treeFile);
		~analysis();

		void initialize();
		void finalize();

		void fillCutFlow(string sCurrentCutName, TMapsd& values2fill);

		void executeTree(bool isendofrun);
		void executeBasic();
		void executeAdvanced();
		void executeCutFlow();
		
		void write();

	private:

};
#endif

