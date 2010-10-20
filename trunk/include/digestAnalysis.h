/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#define combinedSelection_cxx
#include "combinedSelection.C"

#ifndef DIGESTANALYSIS_H
#define DIGESTANALYSIS_H

class digestAnalysis : public combinedSelection
{
public:
	// pointers to classes
	digestPhysics* m_digestPhys;
	
	TFile* m_treeFile;

public:
	digestAnalysis();
	digestAnalysis(digestPhysics* offPhys, graphicObjects* m_graphicobjs, cutFlowHandler* cutFlowHandler, fit* fitter, TFile* treeFile);
	~digestAnalysis();

	void initialize();
	void finalize();
	
	void executeAdvanced();
	void executeCutFlow();
	
	void write();

private:

};
#endif

