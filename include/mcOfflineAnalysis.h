/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#define combinedSelection_cxx
#include "combinedSelection.C"

#define mcOfflineTreeDigest_cxx
#include "mcOfflineTreeDigest.C"

#ifndef MCOFFLINEANALYSIS_H
#define MCOFFLINEANALYSIS_H

class mcOfflineAnalysis : public mcOfflinePhysics, public combinedSelection
{
public:
	// pointers to classes
	mcOfflinePhysics* m_mcOffPhys;

	TFile*		       m_treeFile;
	mcOfflineTreeDigest* m_mcOfffTreeDigest;

public:
	mcOfflineAnalysis();
	mcOfflineAnalysis(mcOfflinePhysics* mcOffPhys, graphicObjects* m_graphicobjs, cutFlowHandler* cutFlowHandler, fit* fitter, TFile* treeFile);
	~mcOfflineAnalysis();

	void initialize();
	void finalize();
	
	void executeAdvanced();
	void executeCutFlow();
	
	void write();

private:

};
#endif

