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

#define muon_staco_cxx
#include "muon_staco.C"

#define muon_muid_cxx
#include "muon_muid.C"

#define offTree_cxx
#include "offTree.C"

#ifndef ANALYSIS_H
#define ANALYSIS_H

class analysis : public physics, public analysisSkeleton
{
public:
	// pointers
	physics*      m_phys;
	muon_muid*    m_muid;
	muon_staco*   m_mustaco;
	GRLinterface* m_analysis_grl;
	offTree*      m_offTree;
	TFile*		  m_treeFile;
	
	// local
	string sMuonRecoAlgo;
	int nMus;

public:
	analysis();
	//analysis(physics* phys, graphicObjects* graphicobjs, cutFlowHandler* cutFlowHandler, periodHandler* periods, fit* fitter, GRLinterface* grl, TFile* treeFile);
	analysis(physics* phys, GRLinterface* grl, TFile* treeFile,
			 string sCutFlowFilePath, string sPeriodsFilePath, string sEventDumpFilePath ) :
			 analysisSkeleton(sCutFlowFilePath,sPeriodsFilePath,sEventDumpFilePath)
			 {
				m_phys = phys;
				m_analysis_grl = grl;	
				m_treeFile = treeFile;
				m_offTree = new offTree( m_phys, NULL, m_treeFile ); // the NULL arg is the [mcPhysics* m_mcPhys;] variable
				m_muid    = new muon_muid(  m_phys ); // this will also "turn on" the desired branches (virtual in the base)
				m_mustaco = new muon_staco( m_phys ); // this will also  "turn on" the desired branches (virtual in the base)
			}
	~analysis();


	void setEventVariables();
	void setStacoVariables();
	void setMuidVariables();
	
	void executeAdvanced();
	void executeCutFlow();
	
	void write();

private:

};
#endif

