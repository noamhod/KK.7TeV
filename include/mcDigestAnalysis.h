/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#define analysisSkeleton_cxx
#include "analysisSkeleton.C"


#ifndef MCDIGESTANALYSIS_H
#define MCDIGESTANALYSIS_H

class mcDigestAnalysis : public mcDigestPhysics, public analysisSkeleton
{
public:
	// pointers to classes
	mcDigestPhysics*  m_mcDigestPhys;
	TFile*		      m_treeFile;
	
	// local
	string sMuonRecoAlgo;
	int nMus;

public:
	mcDigestAnalysis();
	mcDigestAnalysis(mcDigestPhysics* mcDigestPhys, TFile* treeFile,
					 string sCutFlowFilePath, string sPeriodsFilePath, string sEventDumpFilePath ) :
	analysisSkeleton(sCutFlowFilePath,sPeriodsFilePath,sEventDumpFilePath)
	{
		m_mcDigestPhys = mcDigestPhys;
		m_treeFile     = treeFile;
	}
	~mcDigestAnalysis();
	
	void setEventVariables();
	void setStacoVariables();
	void setMuidVariables();
	
	void executeAdvanced();
	void executeCutFlow();
	
	void write();

private:

};
#endif

