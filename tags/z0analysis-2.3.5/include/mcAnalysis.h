/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#define analysisSkeleton_cxx
#include "analysisSkeleton.C"

#define offTree_cxx
#include "offTree.C"

#define mcOffTree_cxx
#include "mcOffTree.C"

#ifndef MCANALYSIS_H
#define MCANALYSIS_H

class mcAnalysis : public mcPhysics, public analysisSkeleton
{
public:
	// pointers to classes
	mcPhysics* m_mcPhys;
	offTree*   m_offTree;
	mcOffTree* m_mcOffTree;
	TFile*     m_treeFile;
	
	// local
	string sMuonRecoAlgo;
	int nMus;

public:
	mcAnalysis();
	mcAnalysis(mcPhysics* mcPhys, TFile* treeFile, string sCutFlowFilePath, string sPeriodsFilePath, string sEventDumpFilePath ) :
	analysisSkeleton(sCutFlowFilePath,sPeriodsFilePath,sEventDumpFilePath)
	{
		m_mcPhys = mcPhys;
		m_treeFile = treeFile;
		m_offTree = new offTree( NULL, m_mcPhys, m_treeFile ); // the NULL arg is the [physics* m_phys;] variable
		m_mcOffTree = new mcOffTree( m_mcPhys, m_treeFile,  m_offTree->getTree() );
	}
	~mcAnalysis();

	void setEventVariables();
	void setStacoVariables();
	void setMuidVariables();
	
	void executeCutFlow();
	
	void write();

private:

};
#endif

