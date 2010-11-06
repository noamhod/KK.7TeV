/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#define analysisSkeleton_cxx
#include "analysisSkeleton.C"

#define mcOfflineTreeDigest_cxx
#include "mcOfflineTreeDigest.C"

#ifndef MCOFFLINEANALYSIS_H
#define MCOFFLINEANALYSIS_H

class mcOfflineAnalysis : public mcOfflinePhysics, public analysisSkeleton
{
public:
	// pointers to classes
	mcOfflinePhysics*    m_mcOffPhys;
	TFile*		         m_treeFile;
	mcOfflineTreeDigest* m_mcOfffTreeDigest;

public:
	mcOfflineAnalysis();
	mcOfflineAnalysis(mcOfflinePhysics* mcOffPhys, TFile* treeFile,
					  string sCutFlowFilePath, string sPeriodsFilePath, string sEventDumpFilePath ) :
	analysisSkeleton(sCutFlowFilePath,sPeriodsFilePath,sEventDumpFilePath)
	{
		m_mcOffPhys = mcOffPhys;
		m_treeFile = treeFile;
		m_mcOfffTreeDigest = new mcOfflineTreeDigest( m_mcOffPhys, m_treeFile );
	}
	~mcOfflineAnalysis();
	
	void executeAdvanced();
	void executeCutFlow();
	
	void write();

private:

};
#endif

