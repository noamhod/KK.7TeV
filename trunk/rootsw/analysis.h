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

#define muon_staco_tree_cxx
#include "muon_staco_tree.C"

#define muon_muid_cxx
#include "muon_muid.C"

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
		
		muon_staco_tree* m_mustacotree;

		GRLinterface*   m_analysis_grl;


		// variables
		TMapsd*         m_cutFlowMap;
		TMapds*         m_cutFlowOrdered;
		TMapsi*         m_cutFlowNumbers;

		TFile*		m_treeFile;
		TTree*		m_eventLevelTree;
		TDirectory*	m_dirEventLevel;
		TDirectory*	m_dir_muon_staco;

		// branches for the trees
                vector<double>* vd_imass;
                vector<double>* vd_costh;
                vector<double>* vd_sum_pTid;
                Bool_t b_l1mu6;

		// event level variables
		double d_imass;
		double d_costh;
		double d_sum_pTid;
		Bool_t b_isL1MU6;

		// other
		int nAllEvents;

	public:
		analysis();
		analysis(physics* phys, graphicObjects* m_graphicobjs, GRLinterface* grl, TFile* treeFile);
		~analysis();

		void initialize();
		void finalize();

		void setTreeBranches(TFile* treeFile, string sname);

		void enableGeneralBranches();

		void printCutFlowNumbers(Long64_t chainEntries);
		void fillCutFlow(string sCurrentCutName, TMapsd& values2fill);

		void executeBasic(bool isendofrun);
		void executeAdvanced(bool isendofrun);
		void executeCutFlow();

		void    readCutFlow(string sCutFlowFilePath);
		TMapsd* getCutFlowMapPtr();
		TMapds* getCutFlowOrderedPtr();

		// for the tree:
		void setEventLevelTree(string sname, TDirectory* dir);
		void setEventLevelBranches();
		void clearEventLevelVectors();
		void fillEventLevelVectors();
		void fillEventLevelTree();
		void writeEventLevelTree();

	private:

};
#endif

