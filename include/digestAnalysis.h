/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#define analysisSkeleton_cxx
#include "analysisSkeleton.C"

#ifndef DIGESTANALYSIS_H
#define DIGESTANALYSIS_H

class digestAnalysis : public analysisSkeleton
{
public:
	// pointers to classes
	digestPhysics* m_digestPhys;
	
	TFile* m_treeFile;

public:
	digestAnalysis();
	digestAnalysis(digestPhysics* digestPhys, TFile* treeFile,
				   string sCutFlowFilePath, string sPeriodsFilePath, string sEventDumpFilePath ) :
	analysisSkeleton(sCutFlowFilePath,sPeriodsFilePath,sEventDumpFilePath)
	{
		m_digestPhys = digestPhys;
		m_treeFile   = treeFile;
	}
	~digestAnalysis();
	
	void executeAdvanced();
	void executeCutFlow();
	
	void write();

private:

};
#endif

