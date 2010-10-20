/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#define GRLinterface_cxx
#include "GRLinterface.C"

#define combinedSelection_cxx
#include "combinedSelection.C"

#define muon_staco_cxx
#include "muon_staco.C"

#define muon_muid_cxx
#include "muon_muid.C"

#define offTree_cxx
#include "offTree.C"

#ifndef ANALYSIS_H
#define ANALYSIS_H

class analysis : public physics, public combinedSelection
{
public:
	// pointers to classes
	physics*        m_phys;
	
	muon_muid*      m_muid;
	muon_staco*     m_mustaco;
	
	GRLinterface*   m_analysis_grl;

	offTree*        m_offTree;

	
	TFile*		m_treeFile;

public:
	analysis();
	analysis(physics* phys, graphicObjects* graphicobjs, cutFlowHandler* cutFlowHandler, fit* fitter, GRLinterface* grl, TFile* treeFile);
	~analysis();

	void initialize();
	void finalize();

	void executeAdvanced();
	void executeCutFlow();
	
	void write();

private:

};
#endif

