/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#define analysisSkeleton_cxx
#include "analysisSkeleton.C"

#define offlineTreeDigest_cxx
#include "offlineTreeDigest.C"

#ifndef OFFLINEANALYSIS_H
#define OFFLINEANALYSIS_H

class offlineAnalysis : public offlinePhysics, public analysisSkeleton
{
public:
	// pointers to classes
	offlinePhysics*    m_offPhys;
	TFile*		       m_treeFile;
	offlineTreeDigest* m_offTreeDigest;

public:
	offlineAnalysis();
	offlineAnalysis(offlinePhysics* offPhys, TFile* treeFile,
					string sCutFlowFilePath, string sPeriodsFilePath, string sEventDumpFilePath ) :
	analysisSkeleton(sCutFlowFilePath,sPeriodsFilePath,sEventDumpFilePath)
	{
		m_offPhys = offPhys;
		m_treeFile = treeFile;
		m_offTreeDigest = new offlineTreeDigest( m_offPhys, m_treeFile );
	}
	~offlineAnalysis();

	void executeAdvanced();
	void executeCutFlow();
	
	void write();

private:

};
#endif

