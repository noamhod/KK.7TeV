/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#define combinedSelection_cxx
#include "combinedSelection.C"

#define offTree_cxx
#include "offTree.C"

#define mcOffTree_cxx
#include "mcOffTree.C"

#ifndef MCANALYSIS_H
#define MCANALYSIS_H

class mcAnalysis : public mcPhysics, public combinedSelection
{
public:
	// pointers to classes
	mcPhysics*        m_mcPhys;

	offTree*        m_offTree;
	mcOffTree*      m_mcOffTree;
	
	TFile* m_treeFile;

public:
	mcAnalysis();
	mcAnalysis(mcPhysics* mcPhys, graphicObjects* m_graphicobjs, cutFlowHandler* cutFlowHandler, fit* fitter, TFile* treeFile);
	~mcAnalysis();

	void initialize();
	void finalize();

	void executeCutFlow();
	
	void write();

private:

};
#endif

