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
	
	/*
	// imass, etaSum and cos(theta_mumu) (dimu)
	m_combinedGraphics->set_allMCvsData(true, true, 5.e-5, 3.e+3, 0.075);
	m_combinedGraphics->draw_allMCvsData(dir, hDir, "imass", "#hat{m}_{#mu#mu} (TeV)", "#frac{dN}{d#hat{m}}");
	m_combinedGraphics->set_allMCvsData(false, true, 5.e-5, 1.e+3, 0.);
	m_combinedGraphics->draw_allMCvsData(dir, hDir, "etaSum", "#sum#eta", "#frac{dN}{d#sum#eta}");
	m_combinedGraphics->set_allMCvsData(false, true, 5.e-5, 1.e+3, 0.);
	m_combinedGraphics->draw_allMCvsData(dir, "noCuts", "cosThetaDimu", "cos(#theta_{#mu#mu})", "#frac{dN}{dcos(#theta_{#mu#mu})}");
	m_combinedGraphics->set_allMCvsData(false, true, 5.e-5, 1.e+3, 0.);
	m_combinedGraphics->draw_allMCvsData(dir, "noCuts", "cosThetaDimuAllCuts", "cos(#theta_{#mu#mu})", "#frac{dN}{dcos(#theta_{#mu#mu})}");
	*/
	
	// Afb
	m_combinedGraphics->set_AfbMCvsData(false, false, -1.05, +1.05, 0.);
	m_combinedGraphics->draw_AfbMCvsData(dir, hDir, "Afb", "#hat{m}_{#mu#mu} TeV", "A_{FB}#left(#hat{m}_{#mu#mu}#right)");
	
	/*
	// pT and eta (mu-, mu+)
	m_combinedGraphics->set_allMCvsData(true, true, 5.e-5, 3.e+3, 0.025);
	m_combinedGraphics->draw_allMCvsData(dir, hDir, "pT", "p_{T}(#mu^{-}) (TeV)", "#frac{dN}{dp_{T}}");
	m_combinedGraphics->set_allMCvsData(true, true, 5.e-5, 3.e+3, 0.025);
	m_combinedGraphics->draw_allMCvsData(dir, hDir, "pT #mu^{+}", "p_{T}(#mu^{+}) (TeV)", "#frac{dN}{dp_{T}}");
	m_combinedGraphics->set_allMCvsData(false, true, 5.e-5, 1.e+3, 0.);
	m_combinedGraphics->draw_allMCvsData(dir, hDir, "eta", "#eta(#mu^{-})", "#frac{dN}{d#eta}");
	m_combinedGraphics->set_allMCvsData(false, true, 5.e-5, 1.e+3, 0.);
	m_combinedGraphics->draw_allMCvsData(dir, hDir, "eta #mu^{+}", "#eta(#mu^{+})", "#frac{dN}{d#eta}");
	
	// pT ratio and diff (mu-, mu+)
	m_combinedGraphics->set_sumMCvsData(false, true, 5.e-3, 1.e+3, 0., true);
	m_combinedGraphics->draw_sumMCvsData(dir, hDir, "pTratio_mu-", "p_{T}^{rat}(#mu^{-}) = p_{T}^{me}/p_{T}^{id}", "#frac{dN}{dp_{T}^{rat}}");
	m_combinedGraphics->set_sumMCvsData(false, true, 5.e-3, 1.e+3, 0., true);
	m_combinedGraphics->draw_sumMCvsData(dir, hDir, "pTratio_mu+", "p_{T}^{rat}(#mu^{+}) = p_{T}^{me}/p_{T}^{id}", "#frac{dN}{dp_{T}^{rat}}");
	m_combinedGraphics->set_sumMCvsData(false, true, 5.e-3, 1.e+3, 0., true);
	m_combinedGraphics->draw_sumMCvsData(dir, hDir, "pTdiff_mu-", "p_{T}^{diff}(#mu^{-}) = p_{T}^{me}-p_{T}^{id}", "#frac{dN}{dp_{T}^{diff}}");
	m_combinedGraphics->set_sumMCvsData(false, true, 5.e-3, 1.e+3, 0., true);
	m_combinedGraphics->draw_sumMCvsData(dir, hDir, "pTdiff_mu+", "p_{T}^{diff}(#mu^{+}) = p_{T}^{me}-p_{T}^{id}", "#frac{dN}{dp_{T}^{diff}}");
	*/
}

