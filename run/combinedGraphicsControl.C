/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "combinedGraphicsControl.h"


combinedGraphicsControl::combinedGraphicsControl()
{

}

combinedGraphicsControl::~combinedGraphicsControl()
{
	
}

void combinedGraphicsControl::initialize(string sAnalysisSelector)
{
	string str = "";
	
	str = checkANDsetFilepath("PWD", "/../data/combinedGraphicsControl.root");
	m_histfile = new TFile( str.c_str(), "RECREATE");
	m_histfile->cd();

	// read the cut flow (ownership: selection class which offlineAnalysis inherits from)
	string sCutFlowFilePath  = checkANDsetFilepath("PWD", "/../conf/cutFlow.cuts");
	string sPeriodsFilePath  = checkANDsetFilepath("PWD", "/../conf/dataPeriods.data");
	
	m_combinedGraphics = new combinedGraphics(sCutFlowFilePath, sPeriodsFilePath, "", sAnalysisSelector, m_histfile);
}

void  combinedGraphicsControl::finalize()
{
	m_histfile->Write();
	m_histfile->Close();
}

void combinedGraphicsControl::execute()
{
	m_combinedGraphics->drawimass();
	m_combinedGraphics->drawpT();
	m_combinedGraphics->drawMCcutFlow();
	m_combinedGraphics->drawDataCutFlow();
}
