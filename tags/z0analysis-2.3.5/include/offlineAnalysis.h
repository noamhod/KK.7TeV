/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#define analysisSkeleton_cxx
#include "analysisSkeleton.C"

#define GRLinterface_cxx
#include "GRLinterface.C"

#define digestTree_cxx
#include "digestTree.C"

#ifndef OFFLINEANALYSIS_H
#define OFFLINEANALYSIS_H

class offlineAnalysis : public offlinePhysics, public analysisSkeleton
{
public:
	// pointers to classes
	offlinePhysics* m_offPhys;
	GRLinterface*   m_offAnalysis_grl;
	TFile*		    m_treeFile;
	digestTree*     m_dgsTree;
	
	// local
	string sMuonRecoAlgo;
	int nMus;

public:
	offlineAnalysis();
	offlineAnalysis(offlinePhysics* offPhys, GRLinterface* grl, TFile* treeFile,
					string sCutFlowFilePath, string sPeriodsFilePath, string sEventDumpFilePath ) :
	analysisSkeleton(sCutFlowFilePath,sPeriodsFilePath,sEventDumpFilePath)
	{
		m_offPhys = offPhys;
		m_offAnalysis_grl = grl;
		m_treeFile = treeFile;
		m_dgsTree = new digestTree( m_offPhys, NULL, m_treeFile ); // the NULL arg is the [mcOfflinePhysics* mcOffPhys] variable
	}
	~offlineAnalysis();

	void setEventVariables();
	void setStacoVariables();
	void setMuidVariables();
	
	void executeAdvanced();
	void executeCutFlow();
	
	void write();

private:

};
#endif
