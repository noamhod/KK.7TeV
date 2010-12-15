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

void combinedGraphicsControl::initialize(string sAnalysisSelector, string muonSelector)
{
	string str = "";
	
	str = checkANDsetFilepath("PWD", "/../data/combinedGraphicsControl.root");
	m_histfile = new TFile( str.c_str(), "RECREATE");
	m_histfile->cd();

	// read the cut flow (ownership: selection class which offlineAnalysis inherits from)
	string sCutFlowFilePath  = checkANDsetFilepath("PWD", "/../conf/cutFlow.cuts");
	string sPeriodsFilePath  = checkANDsetFilepath("PWD", "/../conf/dataPeriods.data");
	
	m_combinedGraphics = new combinedGraphics(sCutFlowFilePath, sPeriodsFilePath, "", sAnalysisSelector, muonSelector, m_histfile);
}

void  combinedGraphicsControl::finalize()
{
	m_histfile->Write();
	m_histfile->Close();
}

void combinedGraphicsControl::execute()
{
	string dir  = "/data/hod/D3PDdigest/rel15_barrel_selection/";
	string hDir = "allCuts";
	
	m_combinedGraphics->set_MCvsData(true, true, 5.e-5, 3.e+3, 0.075);
	m_combinedGraphics->draw_MCvsData(dir, hDir, "imass", "#hat{m}_{#mu#mu} (TeV)", "#frac{dN}{d#hat{m}}");

	m_combinedGraphics->set_MCvsData(true, true, 5.e-5, 3.e+3, 0.025);
	m_combinedGraphics->draw_MCvsData(dir, hDir, "pT", "p_{T}^{#mu} (TeV)", "#frac{dN}{dp_{T}}");
	
	m_combinedGraphics->set_MCvsData(false, true, 5.e-5, 1.e+3, 0.);
	m_combinedGraphics->draw_MCvsData(dir, hDir, "eta", "#eta", "#frac{dN}{d#eta}");
	
	m_combinedGraphics->set_MCvsData(false, true, 5.e-5, 1.e+3, 0.);
	m_combinedGraphics->draw_MCvsData(dir, hDir, "phi", "#phi", "#frac{dN}{d#phi}");
}
