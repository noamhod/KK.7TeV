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

class mcDigestAnalysis : public mcDigestPhysics, public analysisSkeleton
{
public:
	// pointers to classes
	mcDigestPhysics*  m_mcDigestPhys;
	TFile*		      m_treeFile;

public:
	mcDigestAnalysis();
	mcDigestAnalysis(mcDigestPhysics* offPhys, TFile* treeFile,
					 string sCutFlowFilePath, string sPeriodsFilePath, string sEventDumpFilePath ) :
	analysisSkeleton(sCutFlowFilePath,sPeriodsFilePath,sEventDumpFilePath)
	{
		m_mcDigestPhys = mcDigestPhysics;
		m_treeFile     = treeFile;
	}
	~mcDigestAnalysis();
	
	void executeAdvanced();
	void executeCutFlow();
	
	void write();

private:

};
#endif

