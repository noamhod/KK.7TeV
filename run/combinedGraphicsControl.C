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
	m_combinedGraphics->setStyle();

	string dir  = "/data/hod/D3PDdigest/rel15_barrel_selection/";
	
	// imass, etaSum and cos(theta_mumu) (dimu)
	m_combinedGraphics->set_allMCvsData(true, true, 5.e-5, 3.e+3, 0.075);
	m_combinedGraphics->draw_allMCvsData(dir, "allCuts", "imass", "#hat{m}_{#mu#mu} (TeV)", "#frac{dN}{d#hat{m}}");
	m_combinedGraphics->set_allMCvsData(false, true, 5.e-5, 1.e+3, 0.);
	m_combinedGraphics->draw_allMCvsData(dir, "allCuts", "etaSum", "#sum#eta", "#frac{dN}{d#sum#eta}");
	m_combinedGraphics->set_allMCvsData(false, true, 5.e-5, 1.e+3, 0.);
	m_combinedGraphics->draw_allMCvsData(dir, "noCuts", "cosThetaDimu", "cos(#theta_{#mu#mu})", "#frac{dN}{dcos(#theta_{#mu#mu})}");
	m_combinedGraphics->set_allMCvsData(false, true, 5.e-5, 1.e+3, 0.);
	m_combinedGraphics->draw_allMCvsData(dir, "noCuts", "cosThetaDimuAllCuts", "cos(#theta_{#mu#mu})", "#frac{dN}{dcos(#theta_{#mu#mu})}");

	// pT and eta (mu-, mu+)
	m_combinedGraphics->set_allMCvsData(true, true, 5.e-5, 3.e+3, 0.025);
	m_combinedGraphics->draw_allMCvsData(dir, "allCuts", "pT", "p_{T}(#mu^{-}) (TeV)", "#frac{dN}{dp_{T}}");
	m_combinedGraphics->set_allMCvsData(true, true, 5.e-5, 3.e+3, 0.025);
	m_combinedGraphics->draw_allMCvsData(dir, "allCuts", "pT #mu^{+}", "p_{T}(#mu^{+}) (TeV)", "#frac{dN}{dp_{T}}");
	m_combinedGraphics->set_allMCvsData(false, true, 5.e-5, 1.e+3, 0.);
	m_combinedGraphics->draw_allMCvsData(dir, "allCuts", "eta", "#eta(#mu^{-})", "#frac{dN}{d#eta}");
	m_combinedGraphics->set_allMCvsData(false, true, 5.e-5, 1.e+3, 0.);
	m_combinedGraphics->draw_allMCvsData(dir, "allCuts", "eta #mu^{+}", "#eta(#mu^{+})", "#frac{dN}{d#eta}");
	
	// pT ratio and diff (mu-, mu+)
	m_combinedGraphics->set_sumMCvsData(false, true, 5.e-3, 1.e+3, 0., true);
	m_combinedGraphics->draw_sumMCvsData(dir, "allCuts", "pTratio_mu-", "p_{T}^{rat}(#mu^{-}) = p_{T}^{me}/p_{T}^{id}", "#frac{dN}{dp_{T}^{rat}}");
	m_combinedGraphics->set_sumMCvsData(false, true, 5.e-3, 1.e+3, 0., true);
	m_combinedGraphics->draw_sumMCvsData(dir, "allCuts", "pTratio_mu+", "p_{T}^{rat}(#mu^{+}) = p_{T}^{me}/p_{T}^{id}", "#frac{dN}{dp_{T}^{rat}}");
	m_combinedGraphics->set_sumMCvsData(false, true, 5.e-3, 1.e+3, 0., true);
	m_combinedGraphics->draw_sumMCvsData(dir, "allCuts", "pTdiff_mu-", "p_{T}^{diff}(#mu^{-}) = p_{T}^{me}-p_{T}^{id}", "#frac{dN}{dp_{T}^{diff}}");
	m_combinedGraphics->set_sumMCvsData(false, true, 5.e-3, 1.e+3, 0., true);
	m_combinedGraphics->draw_sumMCvsData(dir, "allCuts", "pTdiff_mu+", "p_{T}^{diff}(#mu^{+}) = p_{T}^{me}-p_{T}^{id}", "#frac{dN}{dp_{T}^{diff}}");
}

void combinedGraphicsControl::executeAfb()
{
	cout << "\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
	cout << "$$$ NOTE THAT THIS METHOD HAS TO BE   $$$" << endl;
	cout << "$$$ CALLED SEPERATELY, e.g.           $$$" << endl;
	cout << "$$$ .L combinedGraphicsMain.C;        $$$" << endl;
	cout << "$$$ compile(); OR load();             $$$" << endl;
	cout << "$$$ cgc.initialize('digest','staco'); $$$" << endl;
	cout << "$$$ cgc.executeAfb();                 $$$" << endl;
	cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n" << endl;

	
	//gStyle->Reset();
	TStyle* defaultstyle = (TStyle*)gROOT->GetStyle("Default");
	defaultstyle->cd();
	//gROOT->SetStyle("Default");
	//gROOT->ForceStyle();
	

	string dir  = "/data/hod/D3PDdigest/rel15_barrel_selection/";
	
	// Afb
	m_combinedGraphics->set_AfbMCvsData(false, false, -1.05, +1.05, 0.);
	m_combinedGraphics->draw_AfbMCvsData(dir, "allCuts", "Afb", "#hat{m}_{#mu#mu} TeV", "A_{FB}#left(#hat{m}_{#mu#mu}#right)");
}

void combinedGraphicsControl::executeTrig()
{
	m_combinedGraphics->setStyle();

	//string dir  = "/data/hod/D3PDdigest/rel15_barrel_selection/";
	string dir  = "/data/hod/D3PDdigest/rel15_eta24_selection/";
	
	m_combinedGraphics->draw_trigData(dir, "efficiency", "tNp_effi_pT.L1_MU10");
	m_combinedGraphics->draw_trigData(dir, "efficiency", "tNp_effi_pT.EF_mu10||EF_mu10_MG");
	m_combinedGraphics->draw_trigData(dir, "efficiency", "tNp_effi_pT.EF_mu13||EF_mu13_MG");
	m_combinedGraphics->draw_trigData(dir, "efficiency", "tNp_effi_pT.EF_mu13_tight||EF_mu13_MG_tight");
	
	m_combinedGraphics->draw_trigData(dir, "efficiency", "tNp_effi_eta.L1_MU10");
	m_combinedGraphics->draw_trigData(dir, "efficiency", "tNp_effi_eta.EF_mu10||EF_mu10_MG");
	m_combinedGraphics->draw_trigData(dir, "efficiency", "tNp_effi_eta.EF_mu13||EF_mu13_MG");
	m_combinedGraphics->draw_trigData(dir, "efficiency", "tNp_effi_eta.EF_mu13_tight||EF_mu13_MG_tight");
	
	m_combinedGraphics->draw_trigData(dir, "efficiency", "tNp_effi_phi.L1_MU10");
	m_combinedGraphics->draw_trigData(dir, "efficiency", "tNp_effi_phi.EF_mu10||EF_mu10_MG");
	m_combinedGraphics->draw_trigData(dir, "efficiency", "tNp_effi_phi.EF_mu13||EF_mu13_MG");
	m_combinedGraphics->draw_trigData(dir, "efficiency", "tNp_effi_phi.EF_mu13_tight||EF_mu13_MG_tight");
}

void combinedGraphicsControl::executeTrigTRUvsTnP()
{
	m_combinedGraphics->setStyle();

	//string dir  = "/data/hod/D3PDdigest/rel15_barrel_selection/";
	string dir  = "/data/hod/D3PDdigest/rel15_eta24_selection/";
	
	m_combinedGraphics->draw_trigTRUvsTnP(dir, "efficiency", "pT");
	m_combinedGraphics->draw_trigTRUvsTnP(dir, "efficiency", "eta");
	m_combinedGraphics->draw_trigTRUvsTnP(dir, "efficiency", "phi");
	
	/*
	m_combinedGraphics->draw_trigTRUvsTnP(dir, "efficiency", "tNp_effi_pT.L1_MU10");
	m_combinedGraphics->draw_trigTRUvsTnP(dir, "efficiency", "tNp_effi_eta.L1_MU10");
	m_combinedGraphics->draw_trigTRUvsTnP(dir, "efficiency", "tNp_effi_phi.L1_MU10");
	*/
}

void combinedGraphicsControl::executeTrigMCvsData()
{
	m_combinedGraphics->setStyle();
	
	//string dir  = "/data/hod/D3PDdigest/rel15_barrel_selection/";
	string dir  = "/data/hod/D3PDdigest/rel15_eta24_selection/";

	m_combinedGraphics->draw_trigMCvsData(dir, "efficiency", "pT");
	m_combinedGraphics->draw_trigMCvsData(dir, "efficiency", "eta");
	m_combinedGraphics->draw_trigMCvsData(dir, "efficiency", "phi");

	
	/*
	m_combinedGraphics->draw_trigMCvsData(dir, "efficiency", "tNp_effi_pT.L1_MU10", "pT");
	m_combinedGraphics->draw_trigMCvsData(dir, "efficiency", "tNp_effi_pT.EF_mu10||EF_mu10_MG", "pT");
	m_combinedGraphics->draw_trigMCvsData(dir, "efficiency", "tNp_effi_pT.EF_mu13||EF_mu13_MG", "pT");
	m_combinedGraphics->draw_trigMCvsData(dir, "efficiency", "tNp_effi_pT.EF_mu13_tight||EF_mu13_MG_tight", "pT");
	
	m_combinedGraphics->draw_trigMCvsData(dir, "efficiency", "tNp_effi_eta.L1_MU10", "eta");
	m_combinedGraphics->draw_trigMCvsData(dir, "efficiency", "tNp_effi_eta.EF_mu10||EF_mu10_MG", "eta");
	m_combinedGraphics->draw_trigMCvsData(dir, "efficiency", "tNp_effi_eta.EF_mu13||EF_mu13_MG", "eta");
	m_combinedGraphics->draw_trigMCvsData(dir, "efficiency", "tNp_effi_eta.EF_mu13_tight||EF_mu13_MG_tight", "eta");
	
	m_combinedGraphics->draw_trigMCvsData(dir, "efficiency", "tNp_effi_phi.L1_MU10", "phi");
	m_combinedGraphics->draw_trigMCvsData(dir, "efficiency", "tNp_effi_phi.EF_mu10||EF_mu10_MG", "phi");
	m_combinedGraphics->draw_trigMCvsData(dir, "efficiency", "tNp_effi_phi.EF_mu13||EF_mu13_MG", "phi");
	m_combinedGraphics->draw_trigMCvsData(dir, "efficiency", "tNp_effi_phi.EF_mu13_tight||EF_mu13_MG_tight", "phi");
	*/
}


