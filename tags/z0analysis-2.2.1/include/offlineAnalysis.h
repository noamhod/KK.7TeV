/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#define combinedSelection_cxx
#include "combinedSelection.C"

#define offlineTreeDigest_cxx
#include "offlineTreeDigest.C"

#ifndef OFFLINEANALYSIS_H
#define OFFLINEANALYSIS_H

class offlineAnalysis : public offlinePhysics, public combinedSelection
{
public:
	// pointers to classes
	offlinePhysics*        m_offPhys;

	TFile*		       m_treeFile;
	offlineTreeDigest* m_offTreeDigest;

public:
	offlineAnalysis();
	offlineAnalysis(offlinePhysics* offPhys, graphicObjects* m_graphicobjs, cutFlowHandler* cutFlowHandler, fit* fitter, TFile* treeFile);
	~offlineAnalysis();

	void initialize();
	void finalize();

	void executeAdvanced();
	void executeCutFlow();
	
	void write();

private:

};
#endif

