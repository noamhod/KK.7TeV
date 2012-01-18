#include "../include/rawStd.h"
#include "../include/rawROOT.h"
#include "../include/types.h"
#include "../include/logs.h"
#include "../include/style.h"
#include "../include/histos.h"
///////////////////////////////////
// USAGE: broot commonplots.C++ ///
///////////////////////////////////

string date()
{
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
	stringstream strm;
	strm << (now->tm_year + 1900) << '-'
		 << (now->tm_mon + 1) << '-'
		 <<  now->tm_mday;
	string str = "";
	strm >> str;
	return str;
}

double round(double x)
{
	const double sd = 10; //for accuracy to 1 decimal places
	return int(x*sd + (x<0? -0.5 : 0.5))/sd;
}

void commonplots()
{
	msglvl[DBG] = SILENT;
	msglvl[INF] = VISUAL;
	msglvl[WRN] = VISUAL;
	msglvl[ERR] = VISUAL;
	msglvl[FAT] = VISUAL;
	
	style();
	
	// remember old dir
	TDirectory* olddir = gDirectory;
	
	string sdate = date();
	TFile* oFile = new TFile("plots/mumu_common_plots_"+(TString)sdate+".root", "RECREATE");
	ofstream* oList  = new ofstream(("plots/mumu_common_plots_"+sdate+".txt").c_str());
	ofstream* tTable = new ofstream(("plots/mumu_common_bgtable_"+sdate+".tex").c_str());
	TString pdfname = "plots/mumu_common_canvases_"+sdate+".pdf";
	
	olddir->cd();
	
	TFile* fileAll = new TFile("plots/mcdata_histograms_noTmplts_noEWkFsig_noCoupScale.root","READ");
	TFile* fileIso = new TFile("plots/mcdata_histograms_noTmplts_noQCD_noEWkFsig_noCoupScale_isoStudy.root","READ");
	
	TMapiTS    scanvases;
	TMapTSP2TF fcanvases;
	scanvases.insert(make_pair(0,"Mass"));
	fcanvases.insert(make_pair("Mass",             new TFile("plots/hstack_Mass_noTmplts_noEWkFsig_noCoupScale.root","READ")));
	scanvases.insert(make_pair(1,"MassNumbers"));
	fcanvases.insert(make_pair("MassNumbers",      new TFile("plots/hstack_MassNumbers_noTmplts_noEWkFsig_noCoupScale.root","READ")));
	scanvases.insert(make_pair(2,"pTLeading"));
	fcanvases.insert(make_pair("pTLeading",        new TFile("plots/hstack_pTLeading_noTmplts_noEWkFsig_noCoupScale.root","READ")));
	scanvases.insert(make_pair(3,"pTSubleading"));
	fcanvases.insert(make_pair("pTSubleading",     new TFile("plots/hstack_pTSubleading_noTmplts_noEWkFsig_noCoupScale.root","READ")));
	scanvases.insert(make_pair(4,"EtaLeading"));
	fcanvases.insert(make_pair("EtaLeading",       new TFile("plots/hstack_EtaLeading_noTmplts_noEWkFsig_noCoupScale.root","READ")));
	scanvases.insert(make_pair(5,"EtaSubleading"));
	fcanvases.insert(make_pair("EtaSubleading",    new TFile("plots/hstack_EtaSubleading_noTmplts_noEWkFsig_noCoupScale.root","READ")));
	scanvases.insert(make_pair(6,"PhiLeading"));
	fcanvases.insert(make_pair("PhiLeading",       new TFile("plots/hstack_PhiLeading_noTmplts_noEWkFsig_noCoupScale.root","READ")));
	scanvases.insert(make_pair(7,"PhiSubleading"));
	fcanvases.insert(make_pair("PhiSubleading",    new TFile("plots/hstack_PhiSubleading_noTmplts_noEWkFsig_noCoupScale.root","READ")));
	scanvases.insert(make_pair(8,"EtaQ"));
	fcanvases.insert(make_pair("EtaQ",             new TFile("plots/hstack_EtaQ_noTmplts_noEWkFsig_noCoupScale.root","READ")));
	scanvases.insert(make_pair(9,"QT"));
	fcanvases.insert(make_pair("QT",               new TFile("plots/hstack_QT_noTmplts_noEWkFsig_noCoupScale.root","READ")));
	scanvases.insert(make_pair(10,"yQ"));
	fcanvases.insert(make_pair("yQ",               new TFile("plots/hstack_yQ_noTmplts_noEWkFsig_noCoupScale.root","READ")));
	scanvases.insert(make_pair(11,"IsolationFull"));
	fcanvases.insert(make_pair("IsolationFull",    new TFile("plots/hstack_IsolationFull_noTmplts_noQCD_noEWkFsig_noCoupScale_isoStudy.root","READ")));
	scanvases.insert(make_pair(12,"IsolationLow"));
	fcanvases.insert(make_pair("IsolationLow",     new TFile("plots/hstack_IsolationLow_noTmplts_noQCD_noEWkFsig_noCoupScale_isoStudy.root","READ")));
	scanvases.insert(make_pair(13,"MassAntiIsolated"));
	fcanvases.insert(make_pair("MassAntiIsolated", new TFile("plots/hstack_MassAntiIsolated_noTmplts_noQCD_noEWkFsig_noCoupScale_isoStudy.root","READ")));
	scanvases.insert(make_pair(14,"Nvxp_no_puwgt"));
	fcanvases.insert(make_pair("Nvxp_no_puwgt",    new TFile("plots/hstack_Nvxp_no_puwgt_noTmplts_noEWkFsig_noCoupScale.root","READ")));
	scanvases.insert(make_pair(15,"Nvxp_with_puwgt"));
	fcanvases.insert(make_pair("Nvxp_with_puwgt",  new TFile("plots/hstack_Nvxp_with_puwgt_noTmplts_noEWkFsig_noCoupScale.root","READ")));
	
	vector<TString> histograms;
	
	
	// muons
	histograms.push_back("hEtaLeadingDYmumu");
	histograms.push_back("hEtaLeadingDYtautau");
	histograms.push_back("hEtaLeadingData");
	histograms.push_back("hEtaLeadingDiboson");
	histograms.push_back("hEtaLeadingQCD");
	histograms.push_back("hEtaLeadingTTbar");
	histograms.push_back("hEtaLeadingW+jets");
	histograms.push_back("hEtaLeadingMCsum");
	histograms.push_back("hEtaLeadingZprime_SSM500");
	histograms.push_back("hEtaLeadingZprime_SSM750");
	histograms.push_back("hEtaLeadingZprime_SSM1000");
	histograms.push_back("hEtaLeadingZprime_SSM1500");
	histograms.push_back("hEtaLeadingZprime_SSM1750");
	histograms.push_back("hEtaLeadingZprime_SSM2000");
	
	histograms.push_back("hEtaSubleadingDYmumu");
	histograms.push_back("hEtaSubleadingDYtautau");
	histograms.push_back("hEtaSubleadingData");
	histograms.push_back("hEtaSubleadingDiboson");
	histograms.push_back("hEtaSubleadingQCD");
	histograms.push_back("hEtaSubleadingTTbar");
	histograms.push_back("hEtaSubleadingW+jets");
	histograms.push_back("hEtaSubleadingMCsum");
	histograms.push_back("hEtaSubleadingZprime_SSM500");
	histograms.push_back("hEtaSubleadingZprime_SSM750");
	histograms.push_back("hEtaSubleadingZprime_SSM1000");
	histograms.push_back("hEtaSubleadingZprime_SSM1500");
	histograms.push_back("hEtaSubleadingZprime_SSM1750");
	histograms.push_back("hEtaSubleadingZprime_SSM2000");
	
	histograms.push_back("hPhiLeadingDYmumu");
	histograms.push_back("hPhiLeadingDYtautau");
	histograms.push_back("hPhiLeadingData");
	histograms.push_back("hPhiLeadingDiboson");
	histograms.push_back("hPhiLeadingQCD");
	histograms.push_back("hPhiLeadingTTbar");
	histograms.push_back("hPhiLeadingW+jets");
	histograms.push_back("hPhiLeadingMCsum");
	histograms.push_back("hPhiLeadingZprime_SSM500");
	histograms.push_back("hPhiLeadingZprime_SSM750");
	histograms.push_back("hPhiLeadingZprime_SSM1000");
	histograms.push_back("hPhiLeadingZprime_SSM1500");
	histograms.push_back("hPhiLeadingZprime_SSM1750");
	histograms.push_back("hPhiLeadingZprime_SSM2000");	
	
	histograms.push_back("hPhiSubleadingDYmumu");
	histograms.push_back("hPhiSubleadingDYtautau");
	histograms.push_back("hPhiSubleadingData");
	histograms.push_back("hPhiSubleadingDiboson");
	histograms.push_back("hPhiSubleadingQCD");
	histograms.push_back("hPhiSubleadingTTbar");
	histograms.push_back("hPhiSubleadingW+jets");
	histograms.push_back("hPhiSubleadingMCsum");
	histograms.push_back("hPhiSubleadingZprime_SSM500");
	histograms.push_back("hPhiSubleadingZprime_SSM750");
	histograms.push_back("hPhiSubleadingZprime_SSM1000");
	histograms.push_back("hPhiSubleadingZprime_SSM1500");
	histograms.push_back("hPhiSubleadingZprime_SSM1750");
	histograms.push_back("hPhiSubleadingZprime_SSM2000");
	
	histograms.push_back("hpTLeadingDYmumu");
	histograms.push_back("hpTLeadingDYmumu_truth");
	histograms.push_back("hpTLeadingDYtautau");
	histograms.push_back("hpTLeadingData");
	histograms.push_back("hpTLeadingDiboson");
	histograms.push_back("hpTLeadingQCD");
	histograms.push_back("hpTLeadingTTbar");
	histograms.push_back("hpTLeadingW+jets");
	histograms.push_back("hpTLeadingMCsum");
	histograms.push_back("hpTLeadingKK500_template");
	histograms.push_back("hpTLeadingKK500_template_truth");
	histograms.push_back("hpTLeadingKK750_template");
	histograms.push_back("hpTLeadingKK750_template_truth");
	histograms.push_back("hpTLeadingKK1000_template");
	histograms.push_back("hpTLeadingKK1000_template_truth");
	histograms.push_back("hpTLeadingKK1500_template");
	histograms.push_back("hpTLeadingKK1500_template_truth");
	histograms.push_back("hpTLeadingKK1750_template");
	histograms.push_back("hpTLeadingKK1750_template_truth");
	histograms.push_back("hpTLeadingKK2000_template");
	histograms.push_back("hpTLeadingKK2000_template_truth");
	histograms.push_back("hpTLeadingZprime_SSM500");
	histograms.push_back("hpTLeadingZprime_SSM500_truth");
	histograms.push_back("hpTLeadingZprime_SSM500_template");
	histograms.push_back("hpTLeadingZprime_SSM500_template_truth");
	histograms.push_back("hpTLeadingZprime_SSM750");
	histograms.push_back("hpTLeadingZprime_SSM750_truth");
	histograms.push_back("hpTLeadingZprime_SSM750_template");
	histograms.push_back("hpTLeadingZprime_SSM750_template_truth");
	histograms.push_back("hpTLeadingZprime_SSM1000");
	histograms.push_back("hpTLeadingZprime_SSM1000_truth");
	histograms.push_back("hpTLeadingZprime_SSM1000_template");
	histograms.push_back("hpTLeadingZprime_SSM1000_template_truth");
	histograms.push_back("hpTLeadingZprime_SSM1500");
	histograms.push_back("hpTLeadingZprime_SSM1500_truth");
	histograms.push_back("hpTLeadingZprime_SSM1500_template");
	histograms.push_back("hpTLeadingZprime_SSM1500_template_truth");
	histograms.push_back("hpTLeadingZprime_SSM1750");
	histograms.push_back("hpTLeadingZprime_SSM1750_truth");
	histograms.push_back("hpTLeadingZprime_SSM1750_template");
	histograms.push_back("hpTLeadingZprime_SSM1750_template_truth");
	histograms.push_back("hpTLeadingZprime_SSM2000");
	histograms.push_back("hpTLeadingZprime_SSM2000_truth");
	histograms.push_back("hpTLeadingZprime_SSM2000_template");
	histograms.push_back("hpTLeadingZprime_SSM2000_template_truth");
	
	histograms.push_back("hpTSubleadingDYmumu");
	histograms.push_back("hpTSubleadingDYtautau");
	histograms.push_back("hpTSubleadingData");
	histograms.push_back("hpTSubleadingDiboson");
	histograms.push_back("hpTSubleadingQCD");
	histograms.push_back("hpTSubleadingTTbar");
	histograms.push_back("hpTSubleadingW+jets");
	histograms.push_back("hpTSubleadingMCsum");
	histograms.push_back("hpTSubleadingZprime_SSM500");
	histograms.push_back("hpTSubleadingZprime_SSM750");
	histograms.push_back("hpTSubleadingZprime_SSM1000");
	histograms.push_back("hpTSubleadingZprime_SSM1500");
	histograms.push_back("hpTSubleadingZprime_SSM1750");
	histograms.push_back("hpTSubleadingZprime_SSM2000");
	
	histograms.push_back("hIsolationFullDYmumu");
	histograms.push_back("hIsolationFullDYtautau");
	histograms.push_back("hIsolationFullData");
	histograms.push_back("hIsolationFullDiboson");
	histograms.push_back("hIsolationFulljjmu15X");
	histograms.push_back("hIsolationFullTTbar");
	histograms.push_back("hIsolationFullW+jets");
	histograms.push_back("hIsolationFullMCsum");

	histograms.push_back("hIsolationLowDYmumu");
	histograms.push_back("hIsolationLowDYtautau");
	histograms.push_back("hIsolationLowData");
	histograms.push_back("hIsolationLowDiboson");
	histograms.push_back("hIsolationLowjjmu15X");
	histograms.push_back("hIsolationLowTTbar");
	histograms.push_back("hIsolationLowW+jets");
	histograms.push_back("hIsolationLowMCsum");
	
	histograms.push_back("hMassAntiIsolatedDYmumu");
	histograms.push_back("hMassAntiIsolatedDYtautau");
	histograms.push_back("hMassAntiIsolatedData");
	histograms.push_back("hMassAntiIsolatedDiboson");
	histograms.push_back("hMassAntiIsolatedjjmu15X");
	histograms.push_back("hMassAntiIsolatedTTbar");
	histograms.push_back("hMassAntiIsolatedW+jets");
	histograms.push_back("hMassAntiIsolatedMCsum");

	
	
	
	// dimuons
	histograms.push_back("hMassDYmumu");
	histograms.push_back("hMassDYmumu_truth");
	histograms.push_back("hMassDYtautau");
	histograms.push_back("hMassData");
	histograms.push_back("hMassDiboson");
	histograms.push_back("hMassQCD");
	histograms.push_back("hMassTTbar");
	histograms.push_back("hMassW+jets");
	histograms.push_back("hMassMCsum");
	histograms.push_back("hMassKK500_template");
	histograms.push_back("hMassKK500_template_truth");
	histograms.push_back("hMassKK750_template");
	histograms.push_back("hMassKK750_template_truth");
	histograms.push_back("hMassKK1000_template");
	histograms.push_back("hMassKK1000_template_truth");
	histograms.push_back("hMassKK1500_template");
	histograms.push_back("hMassKK1500_template_truth");
	histograms.push_back("hMassKK1750_template");
	histograms.push_back("hMassKK1750_template_truth");
	histograms.push_back("hMassKK2000_template");
	histograms.push_back("hMassKK2000_template_truth");
	histograms.push_back("hMassZprime_SSM500");
	histograms.push_back("hMassZprime_SSM500_truth");
	histograms.push_back("hMassZprime_SSM500_template");
	histograms.push_back("hMassZprime_SSM500_template_truth");
	histograms.push_back("hMassZprime_SSM750");
	histograms.push_back("hMassZprime_SSM750_truth");
	histograms.push_back("hMassZprime_SSM750_template");
	histograms.push_back("hMassZprime_SSM750_template_truth");
	histograms.push_back("hMassZprime_SSM1000");
	histograms.push_back("hMassZprime_SSM1000_truth");
	histograms.push_back("hMassZprime_SSM1000_template");
	histograms.push_back("hMassZprime_SSM1000_template_truth");
	histograms.push_back("hMassZprime_SSM1500");
	histograms.push_back("hMassZprime_SSM1500_truth");
	histograms.push_back("hMassZprime_SSM1500_template");
	histograms.push_back("hMassZprime_SSM1500_template_truth");
	histograms.push_back("hMassZprime_SSM1750");
	histograms.push_back("hMassZprime_SSM1750_truth");
	histograms.push_back("hMassZprime_SSM1750_template");
	histograms.push_back("hMassZprime_SSM1750_template_truth");
	histograms.push_back("hMassZprime_SSM2000");
	histograms.push_back("hMassZprime_SSM2000_truth");
	histograms.push_back("hMassZprime_SSM2000_template");
	histograms.push_back("hMassZprime_SSM2000_template_truth");
	
	histograms.push_back("hEtaQDYmumu");
	histograms.push_back("hEtaQDYtautau");
	histograms.push_back("hEtaQData");
	histograms.push_back("hEtaQDiboson");
	histograms.push_back("hEtaQQCD");
	histograms.push_back("hEtaQTTbar");
	histograms.push_back("hEtaQW+jets");
	histograms.push_back("hEtaQMCsum");
	histograms.push_back("hEtaQZprime_SSM500");
	histograms.push_back("hEtaQZprime_SSM750");
	histograms.push_back("hEtaQZprime_SSM1000");
	histograms.push_back("hEtaQZprime_SSM1500");
	histograms.push_back("hEtaQZprime_SSM1750");
	histograms.push_back("hEtaQZprime_SSM2000");
	
	histograms.push_back("hQTDYmumu");
	histograms.push_back("hQTDYtautau");
	histograms.push_back("hQTData");
	histograms.push_back("hQTDiboson");
	histograms.push_back("hQTQCD");
	histograms.push_back("hQTTTbar");
	histograms.push_back("hQTW+jets");
	histograms.push_back("hQTMCsum");
	histograms.push_back("hQTZprime_SSM500");
	histograms.push_back("hQTZprime_SSM750");
	histograms.push_back("hQTZprime_SSM1000");
	histograms.push_back("hQTZprime_SSM1500");
	histograms.push_back("hQTZprime_SSM1750");
	histograms.push_back("hQTZprime_SSM2000");
	
	histograms.push_back("hyQDYmumu");
	histograms.push_back("hyQDYtautau");
	histograms.push_back("hyQData");
	histograms.push_back("hyQDiboson");
	histograms.push_back("hyQMCsum");
	histograms.push_back("hyQQCD");
	histograms.push_back("hyQTTbar");
	histograms.push_back("hyQW+jets");
	histograms.push_back("hQTMCsum");
	histograms.push_back("hyQZprime_SSM500");
	histograms.push_back("hyQZprime_SSM750");
	histograms.push_back("hyQZprime_SSM1000");
	histograms.push_back("hyQZprime_SSM1500");
	histograms.push_back("hyQZprime_SSM1750");
	histograms.push_back("hyQZprime_SSM2000");

	histograms.push_back("hMassNumbersDYmumu");
	histograms.push_back("hMassNumbersDYtautau");
	histograms.push_back("hMassNumbersDiboson");
	histograms.push_back("hMassNumbersTTbar");
	histograms.push_back("hMassNumbersW+jets");
	histograms.push_back("hMassNumbersQCD");
	histograms.push_back("hMassNumbersMCsum");
	histograms.push_back("hMassNumbersData");
	histograms.push_back("hMassNumbersZprime_SSM500");
	histograms.push_back("hMassNumbersZprime_SSM750");
	histograms.push_back("hMassNumbersZprime_SSM1000");
	histograms.push_back("hMassNumbersZprime_SSM1500");
	histograms.push_back("hMassNumbersZprime_SSM1750");
	histograms.push_back("hMassNumbersZprime_SSM2000");
	
	histograms.push_back("hMass_limit_DYmumu");
	histograms.push_back("hMass_limit_DYmumu_truth");
	histograms.push_back("hMass_limit_DYtautau");
	histograms.push_back("hMass_limit_Data");
	histograms.push_back("hMass_limit_Diboson");
	histograms.push_back("hMass_limit_QCD");
	histograms.push_back("hMass_limit_TTbar");
	histograms.push_back("hMass_limit_W+jets");
	histograms.push_back("hMass_limit_MCsum");
	histograms.push_back("hMass_limit_KK500_template");
	histograms.push_back("hMass_limit_KK500_template_truth");
	histograms.push_back("hMass_limit_KK750_template");
	histograms.push_back("hMass_limit_KK750_template_truth");
	histograms.push_back("hMass_limit_KK1000_template");
	histograms.push_back("hMass_limit_KK1000_template_truth");
	histograms.push_back("hMass_limit_KK1500_template");
	histograms.push_back("hMass_limit_KK1500_template_truth");
	histograms.push_back("hMass_limit_KK1750_template");
	histograms.push_back("hMass_limit_KK1750_template_truth");
	histograms.push_back("hMass_limit_KK2000_template");
	histograms.push_back("hMass_limit_KK2000_template_truth");
	histograms.push_back("hMass_limit_Zprime_SSM500");
	histograms.push_back("hMass_limit_Zprime_SSM500_truth");
	histograms.push_back("hMass_limit_Zprime_SSM500_template");
	histograms.push_back("hMass_limit_Zprime_SSM500_template_truth");
	histograms.push_back("hMass_limit_Zprime_SSM750");
	histograms.push_back("hMass_limit_Zprime_SSM750_truth");
	histograms.push_back("hMass_limit_Zprime_SSM750_template");
	histograms.push_back("hMass_limit_Zprime_SSM750_template_truth");
	histograms.push_back("hMass_limit_Zprime_SSM1000");
	histograms.push_back("hMass_limit_Zprime_SSM1000_truth");
	histograms.push_back("hMass_limit_Zprime_SSM1000_template");
	histograms.push_back("hMass_limit_Zprime_SSM1000_template_truth");
	histograms.push_back("hMass_limit_Zprime_SSM1500");
	histograms.push_back("hMass_limit_Zprime_SSM1500_truth");
	histograms.push_back("hMass_limit_Zprime_SSM1500_template");
	histograms.push_back("hMass_limit_Zprime_SSM1500_template_truth");
	histograms.push_back("hMass_limit_Zprime_SSM1750");
	histograms.push_back("hMass_limit_Zprime_SSM1750_truth");
	histograms.push_back("hMass_limit_Zprime_SSM1750_template");
	histograms.push_back("hMass_limit_Zprime_SSM1750_template_truth");
	histograms.push_back("hMass_limit_Zprime_SSM2000");
	histograms.push_back("hMass_limit_Zprime_SSM2000_truth");
	histograms.push_back("hMass_limit_Zprime_SSM2000_template");
	histograms.push_back("hMass_limit_Zprime_SSM2000_template_truth");
	
	
	histograms.push_back("hMassCosThetaCSDYmumu");
	histograms.push_back("hMassCosThetaCSDYtautau");
	histograms.push_back("hMassCosThetaCSData");
	histograms.push_back("hMassCosThetaCSDiboson");
	histograms.push_back("hMassCosThetaCSQCD");
	histograms.push_back("hMassCosThetaCSTTbar");
	histograms.push_back("hMassCosThetaCSW+jets");
	histograms.push_back("hMassCosThetaCSMCsum");
	histograms.push_back("hMassCosThetaCSZprime_SSM500");
	histograms.push_back("hMassCosThetaCSZprime_SSM750");
	histograms.push_back("hMassCosThetaCSZprime_SSM1000");
	histograms.push_back("hMassCosThetaCSZprime_SSM1500");
	histograms.push_back("hMassCosThetaCSZprime_SSM1750");
	histograms.push_back("hMassCosThetaCSZprime_SSM2000");
	
	
	histograms.push_back("hMassyQDYmumu");
	histograms.push_back("hMassyQDYtautau");
	histograms.push_back("hMassyQData");
	histograms.push_back("hMassyQDiboson");
	histograms.push_back("hMassyQQCD");
	histograms.push_back("hMassyQTTbar");
	histograms.push_back("hMassyQW+jets");
	histograms.push_back("hMassyQMCsum");
	histograms.push_back("hMassyQZprime_SSM500");
	histograms.push_back("hMassyQZprime_SSM750");
	histograms.push_back("hMassyQZprime_SSM1000");
	histograms.push_back("hMassyQZprime_SSM1500");
	histograms.push_back("hMassyQZprime_SSM1750");
	histograms.push_back("hMassyQZprime_SSM2000");
	
	
	
	
	
	// OTHER
	histograms.push_back("hNvxp_no_puwgtDYmumu");
	histograms.push_back("hNvxp_no_puwgtDYtautau");
	histograms.push_back("hNvxp_no_puwgtData");
	histograms.push_back("hNvxp_no_puwgtDiboson");
	histograms.push_back("hNvxp_no_puwgtQCD");
	histograms.push_back("hNvxp_no_puwgtTTbar");
	histograms.push_back("hNvxp_no_puwgtW+jets");
	histograms.push_back("hNvxp_no_puwgtMCsum");
	histograms.push_back("hNvxp_no_puwgtZprime_SSM500");
	histograms.push_back("hNvxp_no_puwgtZprime_SSM750");
	histograms.push_back("hNvxp_no_puwgtZprime_SSM1000");
	histograms.push_back("hNvxp_no_puwgtZprime_SSM1500");
	histograms.push_back("hNvxp_no_puwgtZprime_SSM1750");
	histograms.push_back("hNvxp_no_puwgtZprime_SSM2000");
	
	
	histograms.push_back("hNvxp_with_puwgtDYmumu");
	histograms.push_back("hNvxp_with_puwgtDYtautau");
	histograms.push_back("hNvxp_with_puwgtData");
	histograms.push_back("hNvxp_with_puwgtDiboson");
	histograms.push_back("hNvxp_with_puwgtQCD");
	histograms.push_back("hNvxp_with_puwgtTTbar");
	histograms.push_back("hNvxp_with_puwgtW+jets");
	histograms.push_back("hNvxp_with_puwgtMCsum");
	histograms.push_back("hNvxp_with_puwgtZprime_SSM500");
	histograms.push_back("hNvxp_with_puwgtZprime_SSM750");
	histograms.push_back("hNvxp_with_puwgtZprime_SSM1000");
	histograms.push_back("hNvxp_with_puwgtZprime_SSM1500");
	histograms.push_back("hNvxp_with_puwgtZprime_SSM1750");
	histograms.push_back("hNvxp_with_puwgtZprime_SSM2000");
	
	
	
	oFile->cd();
	TObject* hobj = NULL;

	for(unsigned int i=0 ; i<histograms.size() ; i++)
	{
		if(!histograms[i].Contains("Isolat")) hobj = (TObject*)fileAll->Get(histograms[i]);
		else                                  hobj = (TObject*)fileIso->Get(histograms[i]);
		_INFO("adding -> "+(string)hobj->GetName());
		hobj->Write();
		(*oList) << (string)hobj->GetName() << endl;
	}
	oList->close();
	
	unsigned int counter = 0;
	unsigned int max = scanvases.size();
	TCanvas* cnv;
	for(TMapiTS::iterator it=scanvases.begin() ; it!=scanvases.end() ; ++it)
	{
		int order    = it->first; 
		TString name = it->second;
		TFile*  file = fcanvases[name]; 
		cnv = (TCanvas*)file->Get("Canvas");
		cnv->SetName(name);
		_INFO("adding -> "+(string)cnv->GetName());
		cnv->Write();
		if     (counter==0)     cnv->SaveAs(pdfname+"(");
		else if(counter==max-1) cnv->SaveAs(pdfname+")");
		else                    cnv->SaveAs(pdfname);
		counter++;
	}
	
	oFile->Write();
	oFile->Close();
	
	
	TH1D* htmp1 = (TH1D*)fileAll->Get("hMassNumbersDYmumu");
	(*tTable) << "\\documentclass[a4paper,12pt]{article}" << endl;
	(*tTable) << "\\pagestyle{plain}" << endl;
	(*tTable) << "\\usepackage{booktabs,longtable,rotating}" << endl;
	
	(*tTable) << "\\addtolength{\\oddsidemargin}{-3.55cm}" << endl;
	(*tTable) << "\\addtolength{\\textwidth}{2.5cm}" << endl;
	(*tTable) << "\\addtolength{\\textheight}{3.7cm}" << endl;
	(*tTable) << "\\addtolength{\\topmargin}{0cm}" << endl;
	
	(*tTable) << "\\begin{document}" << endl;
	(*tTable) << "\t{\\scriptsize" << endl;
	(*tTable) << "\t\t\\begin{sidewaystable}";
	(*tTable) << "\t\t\\begin{longtable}[t]{c";
	for(Int_t bin=0 ; bin<=htmp1->GetNbinsX()+1 ; bin++)
	{
		(*tTable) << "c";
	}
	(*tTable) <<"|c}" << endl;
	(*tTable) << "\t\t\t\\toprule[2pt]" << endl;
	(*tTable) << "\t\t\t\\toprule[1pt]" << endl;
	(*tTable) << "\t\t\t $m_{\\mu\\mu}$ GeV &underflow &70-110 &110-130 &130-150 &150-170 &170-200 &200-240 &240-300 &300-400 &400-800 &800-3000 &overflow &$\\sum$\\\\" << endl;
	//(*tTable) << "\t\t\t $m_{\\mu\\mu}$ GeV &underflow &70-110 &110-130 &130-150 &150-170 &170-200 &200-240 &240-300 &300-400 &400-600 &600-900 &900-3000 &overflow &$\\sum$\\\\" << endl;
	(*tTable) << "\t\t\t\\midrule[1pt]" << endl;
	
	TH1D* htmp;
	for(unsigned int i=0 ; i<histograms.size() ; i++)
	{
		if(!histograms[i].Contains("hMassNumbers")) continue;
		if(histograms[i].Contains("tautau"))        continue; // COUNTED WITH THE DYtautau
		if(histograms[i].Contains("Zprime_SSM"))    continue; // COUNTED WITH THE DYtautau
		htmp = (TH1D*)fileAll->Get(histograms[i]);
		TString name  = (TString)htmp->GetName();
		TString title = "NULL";
		if(name=="hMassNumbersDYmumu")   title = "$Z/\\gamma^*$";
		if(name=="hMassNumbersDiboson")  title = "Diboson";
		if(name=="hMassNumbersTTbar")    title = "$t\\bar{t}$";
		if(name=="hMassNumbersW+jets")   title = "$W$+jets";
		if(name=="hMassNumbersQCD")      title = "QCD";
		if(name=="hMassNumbersMCsum")    title = "$\\sum$BGs";
		if(name=="hMassNumbersData")     title = "Data";
		_INFO("Checking -> "+(string)name);
		if(name=="hMassNumbersMCsum") (*tTable) << "\t\t\t\\midrule[1pt]" << endl;
		(*tTable) << "\t\t\t " << title;
		Double_t sum = 0.;
		for(Int_t bin=0 ; bin<=htmp->GetNbinsX()+1 ; bin++)
		{
			Double_t bincontent = htmp->GetBinContent(bin);
			if(name=="hMassNumbersDYmumu")
			{
				htmp1 = (TH1D*)fileAll->Get("hMassNumbersDYtautau");
				bincontent += htmp1->GetBinContent(bin);
			}
			(*tTable) << " &" << setprecision(1) << fixed << bincontent;
			// (*tTable) << " &" << round(bincontent);
			sum += bincontent;
		}
		(*tTable) << " &" << setprecision(1) << fixed << sum;
		// (*tTable) << " &" << round(sum);
		(*tTable) << "\\\\" << endl;
	}
	(*tTable) << "\t\t\t\\midrule[1pt]" << endl;
	
	TH1D* htmp2 = (TH1D*)fileAll->Get("hMassNumbersData");
	TH1D* htmp3 = (TH1D*)fileAll->Get("hMassNumbersMCsum");
	Double_t sumMC   = 0.;
	Double_t sumData = 0.;
	(*tTable) << "\t\t\t $\\frac{{\\rm Data}}{\\sum{\\rm BGs}}$";
	for(Int_t bin=0 ; bin<=htmp1->GetNbinsX()+1 ; bin++)
	{
		Double_t data  = htmp2->GetBinContent(bin);
		Double_t mc    = htmp3->GetBinContent(bin);
		Double_t ratio = (mc!=0.) ? data/mc : 0.;
		(*tTable) << " &" << setprecision(2) << fixed << ratio*100 << "\\%";
		// (*tTable) << " &" << round(ratio*100) << "\\%";
		sumMC   += mc;
		sumData += data;
	}
	Double_t ratio = (sumMC!=0.) ? sumData/sumMC : 0.;
	(*tTable) << " &" << setprecision(2) << fixed << ratio*100 << "\\%";
	// (*tTable) << " &" << round(ratio*100) << "\\%";
	(*tTable) << "\\\\" << endl;
	
	(*tTable) << "\t\t\t\\midrule[1pt]" << endl;
	(*tTable) << "\t\t\t\\bottomrule[2pt]" << endl;
	(*tTable) << "\t\t\\end{longtable}" << endl;
	(*tTable) << "\t\t\\end{sidewaystable}" << endl;
	(*tTable) << "\t}" << endl;
	(*tTable) << "\\end{document}" << endl;
	tTable->close();
}
