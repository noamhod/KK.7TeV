/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#define analysisSkeleton_cxx
#include "analysisSkeleton.C"

#define digestTree_cxx
#include "digestTree.C"

#ifndef MCOFFLINEANALYSIS_H
#define MCOFFLINEANALYSIS_H

class mcOfflineAnalysis : public mcOfflinePhysics, public analysisSkeleton
{
public:
	// pointers to classes
	mcOfflinePhysics* m_mcOffPhys;
	TFile*		      m_treeFile;
	digestTree*       m_dgsTree;

public:
	mcOfflineAnalysis();
	mcOfflineAnalysis(mcOfflinePhysics* mcOffPhys, TFile* treeFile,
					  string sCutFlowFilePath, string sPeriodsFilePath, string sEventDumpFilePath ) :
	analysisSkeleton(sCutFlowFilePath,sPeriodsFilePath,sEventDumpFilePath)
	{
		m_mcOffPhys = mcOffPhys;
		m_treeFile = treeFile;
		m_dgsTree = new digestTree( NULL, m_mcOffPhys, m_treeFile ); // the NULL arg is the [offlinePhysics* offPhys] variable
	}
	~mcOfflineAnalysis();
	
	void executeAdvanced();
	void executeCutFlow();
	
	void write();

private:

};
#endif

