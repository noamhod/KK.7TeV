/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#define selection_cxx
#include "selection.C"

#ifndef MCDIGESTANALYSIS_H
#define MCDIGESTANALYSIS_H

class mcDigestAnalysis : public mcDigestPhysics, public combinedSelection
{
public:
	// pointers to classes
	mcDigestPhysics*        m_mcDigestPhys;
	
	TFile*		       m_treeFile;

public:
	mcDigestAnalysis();
	mcDigestAnalysis(mcDigestPhysics* offPhys, graphicObjects* m_graphicobjs, cutFlowHandler* cutFlowHandler, fit* fitter, TFile* treeFile);
	~mcDigestAnalysis();

	void initialize();
	void finalize();
	
	void executeAdvanced();
	void executeCutFlow();
	
	void write();

private:

};
#endif

