/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#define analysisSkeleton_cxx
#include "analysisSkeleton.C"

#define muD3PD_cxx
#include "muD3PD.C"

#define muMCD3PD_cxx
#include "muMCD3PD.C"

#ifndef MCANALYSIS_H
#define MCANALYSIS_H

class mcAnalysis : public mcPhysics, public analysisSkeleton
{
public:
	// pointers to classes
	mcPhysics* m_mcPhys;
	muD3PD*    m_muD3PD;
	muMCD3PD*  m_muMCD3PD;
	TFile*     m_treeFile;
	
	// local
	string sMuonRecoAlgo;
	int nMus;

public:
	mcAnalysis();
	mcAnalysis(mcPhysics* mcPhys, TFile* treeFile, string sCutFlowFilePath, string sPeriodsFilePath, string sEventDumpFilePath ) :
	analysisSkeleton(sCutFlowFilePath,sPeriodsFilePath,sEventDumpFilePath)
	{
		sMuonRecoAlgo = "staco";
		m_mcPhys = mcPhys;
		m_treeFile = treeFile;
		m_muD3PD = new muD3PD( NULL, m_mcPhys, m_treeFile ); // the NULL arg is the [physics* m_phys;] variable
		m_muMCD3PD = new muMCD3PD( m_mcPhys, m_treeFile,  m_muD3PD->getTree() );
	}
	~mcAnalysis();

	void setEventVariables();
	void setStacoVariables();
	void setMuidVariables();
	
	void execute( string mualgo = "staco" );
	
	void write();

private:

};
#endif

