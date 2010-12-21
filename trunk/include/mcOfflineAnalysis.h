/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#define analysisSkeleton_cxx
#include "analysisSkeleton.C"

#define muSkimD3PD_cxx
#include "muSkimD3PD.C"

#define muSkimMCD3PD_cxx
#include "muSkimMCD3PD.C"

#ifndef MCOFFLINEANALYSIS_H
#define MCOFFLINEANALYSIS_H

class mcOfflineAnalysis : public mcOfflinePhysics, public analysisSkeleton
{
public:
	// pointers to classes
	mcOfflinePhysics* m_mcOffPhys;
	TFile*		      m_treeFile;
	muSkimD3PD*       m_muSkimD3PD;
	muSkimMCD3PD*     m_muSkimMCD3PD;
	
	// local
	string sMuonRecoAlgo;
	int nMus;

public:
	mcOfflineAnalysis();
	mcOfflineAnalysis(mcOfflinePhysics* mcOffPhys, TFile* treeFile,
					  string sCutFlowFilePath, string sPeriodsFilePath, string sEventDumpFilePath ) :
	analysisSkeleton(sCutFlowFilePath,sPeriodsFilePath,sEventDumpFilePath)
	{
		sMuonRecoAlgo = "staco";
		m_mcOffPhys = mcOffPhys;
		m_treeFile = treeFile;
		m_muSkimD3PD   = new muSkimD3PD( NULL, m_mcOffPhys, m_treeFile ); // the NULL arg is the [offlinePhysics* m_offPhys;] variable
		m_muSkimMCD3PD = new muSkimMCD3PD( m_mcOffPhys, m_treeFile,  m_muSkimD3PD->getTree() );
	}
	~mcOfflineAnalysis();
	
	void setEventVariables();
	void setStacoVariables();
	void setMuidVariables();
	
	void executeAdvanced();
	void execute( string mualgo = "staco" );
	
	void write();

private:

};
#endif

