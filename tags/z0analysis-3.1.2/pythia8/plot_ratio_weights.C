#include "TROOT.h"
#include "TStyle.h"
#include "TH1.h"
#include "TTree.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TPaveText.h"
#include "TText.h"

#include "read.h"
#include "kinematics.h"
#include "asymgraph.h"
#include "smearing.h"

#include <iostream>
#include <stdlib.h>
#include <stdio.h>      // for the sprintf call
#include <string>
#include <sstream>      // for the int to string operation (stringstream call)
#include <cstring>      // for the string functions
#include <math.h>
#include <cmath>
#include <complex>
#include <fstream>
#include <vector>
#include <map>
#include <ctime>
#include <time.h>
#include <assert.h>
#include <pthread.h>

using namespace std;

enum models
{
	Z0,ZP,KK
};

static Color_t cData    = kBlack;
static Color_t cGammaZ  = kAzure-9;
static Color_t cTTBar   = kRed+1;
static Color_t cDiboson = kOrange+7;
static Color_t cQCD     = kYellow-9;
static Color_t cWJets   = kGreen-3;

static Color_t col0 = kBlack;
static Color_t col1 = kAzure-9;
static Color_t col2 = kRed+1;
static Color_t col3 = kOrange+7;
static Color_t col4 = kYellow-9;
static Color_t col5 = kGreen-3;


// bins for the mHat histos
static double   xmin  = 120.;
static double   xmax  = 5000.;
const  int      nxbins = 200;
static Double_t logMmin;
static Double_t logMmax;
static Double_t logMbinwidth;
static Double_t xbins[nxbins+1];

// bins for the afb (the binning is in mHat)
static double   imass_afb_min   = 120.;
static double   imass_afb_max   = 1620.;
const  int      imass_afb_nbins = 10;
static Double_t logMmin_afb;
static Double_t logMmax_afb;
static Double_t logMbinwidth_afb;
static Double_t imass_afb_bins[imass_afb_nbins+1];

static double lumi = 5.;
static double mb2fb = 1.e12;
static double nb2mb = 1.e-6;

vector<string> svNames;
vector<string> svPaths;
vector<TH1D*>  hvBinnedHistos_imass;
vector<TH1D*>  hvBinnedHistos_imassRes;
vector<vector<TH1D*> > hvvBinnedHistos_cosTh;
vector<double> dvWeights;
vector<Color_t> cvColors;

string sDir  = "/data/hod/pythia8_ntuples/";
string sName = "";

bool doLogx = true;

double sumWeights = 0.;




void clearSamples()
{	
	svNames.clear();
	svPaths.clear();
	for(int n=0 ; n<(int)hvBinnedHistos_imass.size() ; n++)
	{
		if(hvBinnedHistos_imass[n]!=NULL) delete hvBinnedHistos_imass[n];
		if(hvBinnedHistos_imassRes[n]!=NULL) delete hvBinnedHistos_imassRes[n];
		for(int m=0 ; m<(int)hvvBinnedHistos_cosTh[n].size() ; m++)
		{
			if(hvvBinnedHistos_cosTh[n][m]!=NULL) delete hvvBinnedHistos_cosTh[n][m];
		}
		hvvBinnedHistos_cosTh[n].clear();
	}
	hvBinnedHistos_imass.clear();
	hvBinnedHistos_imassRes.clear();
	hvvBinnedHistos_cosTh.clear();
	dvWeights.clear();
	cvColors.clear();
}

void addSample(string name, Color_t color, double events, double sigma)
{	
	svNames.push_back(name);

	sName = svNames[svNames.size()-1];

	svPaths.push_back(sDir+sName+".root");
	
	if(doLogx) hvBinnedHistos_imass.push_back(new TH1D(sName.c_str(),sName.c_str(),nxbins,xbins));
	else       hvBinnedHistos_imass.push_back(new TH1D(sName.c_str(),sName.c_str(),nxbins,xmin,xmax));

	hvBinnedHistos_imassRes.push_back(new TH1D((sName+"Res").c_str(),(sName+"Res").c_str(),nxbins,-0.2,+0.2));

	vector<TH1D*> vTmp;
	stringstream strm;
	string s;
	for(int b=0 ; b<imass_afb_nbins ; b++)
	{
		strm.clear();
		s.clear();
		strm << b;
		strm >> s;
		vTmp.push_back( new TH1D((sName+"_massbin_"+s).c_str(),(sName+"_massbin_"+s).c_str(),50,-1.,+1.) );
	}
	hvvBinnedHistos_cosTh.push_back( vTmp );
	
	dvWeights.push_back(lumi/(events/(sigma*mb2fb)));
	cvColors.push_back(color);
	
	sumWeights += lumi/(events/(sigma*mb2fb));
}

double getYmin(TH1D* h)
{
	double min = 1.e20;
	double binval = 0.;
	for(int b=1 ; b<=h->GetNbinsX() ; b++)
	{
		binval = h->GetBinContent(b);
		min = (binval<min  &&  binval>0.) ? binval : min;
	}
	return min;
}

int plot_ratio_weights()
{
	gStyle->SetOptStat(0);
	gStyle->SetFrameBorderMode(0);
	gStyle->SetCanvasBorderMode(0);
	gStyle->SetPadBorderMode(0);
	gStyle->SetPadColor(0);
	gStyle->SetCanvasColor(0);
	gStyle->SetStatColor(0);
	//gStyle->SetFillColor(0);
	gStyle->SetFrameFillColor(0);
	gStyle->SetTitleFillColor(0);
	gStyle->SetPaperSize(20,26);
	gStyle->SetPadTopMargin(0.05);
	gStyle->SetPadRightMargin(0.12);
	gStyle->SetPadBottomMargin(0.16);
	gStyle->SetPadLeftMargin(0.12);
	Int_t font=42;
	Double_t tsize=0.04;
	gStyle->SetTextFont(font);
	gStyle->SetTextSize(tsize);
	gStyle->SetLabelFont(font,"x");
	gStyle->SetTitleFont(font,"x");
	gStyle->SetLabelFont(font,"y");
	gStyle->SetTitleFont(font,"y");
	gStyle->SetLabelFont(font,"z");
	gStyle->SetTitleFont(font,"z");
	gStyle->SetLabelSize(tsize,"x");
	gStyle->SetTitleSize(tsize,"x");
	gStyle->SetLabelSize(tsize,"y");
	gStyle->SetTitleSize(tsize,"y");
	gStyle->SetLabelSize(tsize,"z");
	gStyle->SetTitleSize(tsize,"z");
	gStyle->SetStatBorderSize(0);
	gStyle->SetStatColor(0);
	gStyle->SetStatX(0);
	gStyle->SetStatY(0);
	gStyle->SetStatFont(42);
	gStyle->SetStatFontSize(0);
	gStyle->SetOptStat(0);
	gStyle->SetStatW(0);
	gStyle->SetStatH(0);
	gStyle->SetTitleX(0.12);
	gStyle->SetTitleY(1);
	//gStyle->SetTitleW(1);
	//gStyle->SetTitleH(1);
	
	float mHat;
	float qT;
	float ysystem;
	float cosThetaHE;
	float cosThetaCS;
	vector<int>*    index  = new vector<int>;
	vector<int>*    id     = new vector<int>;
	vector<double>* charge = new vector<double>;
	vector<double>* px     = new vector<double>;
	vector<double>* py     = new vector<double>;
	vector<double>* pz     = new vector<double>;
	vector<double>* E      = new vector<double>;
	vector<double>* m      = new vector<double>;
	vector<double>* y      = new vector<double>;
	vector<double>* pT     = new vector<double>;
	vector<double>* eta    = new vector<double>;
	vector<double>* phi    = new vector<double>;
	vector<double>* theta  = new vector<double>;	
	
	bool truth_all_isValid;
	vector<float>* truth_all_dr = new vector<float>;
	vector<float>* truth_all_E = new vector<float>;
	vector<float>* truth_all_pt = new vector<float>;
	vector<float>* truth_all_eta = new vector<float>;
	vector<float>* truth_all_phi = new vector<float>;
	vector<int>*   truth_all_type = new vector<int>;
	vector<int>*   truth_all_status = new vector<int>;
	vector<int>*   truth_all_barcode = new vector<int>;
	vector<int>*   truth_all_mothertype = new vector<int>;
	vector<int>*   truth_all_motherbarcode = new vector<int>;
	vector<int>*   truth_all_matched = new vector<int>;
	float truth_all_Mhat;
	float truth_all_CosThetaCS;
	float truth_all_CosThetaHE;
	float truth_all_ySystem;
	float truth_all_QT;
	
	bool recon_all_isValid;
	vector<float>* recon_all_E = new vector<float>;
	vector<float>* recon_all_pt = new vector<float>;
	vector<float>* recon_all_m = new vector<float>;
	vector<float>* recon_all_eta = new vector<float>;
	vector<float>* recon_all_phi = new vector<float>;
	vector<float>* recon_all_px = new vector<float>;
	vector<float>* recon_all_py = new vector<float>;
	vector<float>* recon_all_pz = new vector<float>;
	vector<float>* recon_all_charge = new vector<float>;
	vector<float>* recon_all_y = new vector<float>;
	vector<int>*   recon_all_id = new vector<int>;
	vector<float>* recon_all_theta = new vector<float>;
	float recon_all_Mhat;
	float recon_all_CosThetaCS;
	float recon_all_CosThetaHE;
	float recon_all_ySystem;
	float recon_all_QT;

	
	string sModel = "";
	string sMass  = "";
	cout << "chose mass(GeV)...";
	cin >> sMass;
	

	logMmin  = log10(xmin);
	logMmax  = log10(xmax);
	logMbinwidth = (Double_t)( (logMmax-logMmin)/(Double_t)nxbins );
	xbins[0] = xmin;
	for(Int_t i=1 ; i<=nxbins ; i++) xbins[i] = TMath::Power( 10,(logMmin + i*logMbinwidth) );
	
	
	TString fname = "weights_M" + (TString)sMass;
	
	
	TCanvas* cnv = new TCanvas("cnv", "cnv", 0,0,1200,800);
	cnv->Divide(2,2);
	
	TVirtualPad* pad_recon_template = cnv->cd(2);
	pad_recon_template->SetLogy();
	if(doLogx) pad_recon_template->SetLogx();
	pad_recon_template->SetTickx(1);
	pad_recon_template->SetTicky(1);
	
	TVirtualPad* pad_sigma = cnv->cd(1);
	pad_sigma->SetLogy();
	if(doLogx) pad_sigma->SetLogx();
	pad_sigma->SetTickx(1);
	pad_sigma->SetTicky(1);
	
	TVirtualPad* pad_weights = cnv->cd(3);
	pad_weights->SetLogy();
	if(doLogx) pad_weights->SetLogx();
	pad_weights->SetTickx(1);
	pad_weights->SetTicky(1);
	
	TVirtualPad* pad_compare = cnv->cd(4);
	pad_compare->SetLogy();
	if(doLogx) pad_compare->SetLogx();
	pad_compare->SetTickx(1);
	pad_compare->SetTicky(1);
	
	cnv->cd();
	cnv->Draw();
	
	TLegend* leg_mass = new TLegend(0.1462841,0.1774325,0.5373268,0.4004816,NULL,"brNDC");
	leg_mass->SetFillColor(kWhite);
	
	TLegend* leg_mass_recon = new TLegend(0.1446488,0.1788644,0.6376115,0.4271373,NULL,"brNDC");
	leg_mass_recon->SetFillColor(kWhite);
	
	TLegend* leg_weights = new TLegend(0.1480616,0.7509715,0.4342337,0.9272078,NULL,"brNDC");
	leg_weights->SetFillColor(kWhite);
	
	TLegend* leg_compare = new TLegend(0.2840022,0.8211356,0.8361901,0.9290803,NULL,"brNDC");
	leg_compare->SetFillColor(kWhite);
	
	TPaveText* pvtxt = new TPaveText(0.1462841,0.4417869,0.5177747,0.6400528,"brNDC");
	pvtxt->SetFillColor(kWhite);
	TText* txt = pvtxt->AddText( "#splitline{Sum of binned #bf{truth}}{samples normalized to ~5 fb^{-1}}" );
	
	TPaveText* pvtxt_recon = new TPaveText(0.1462841,0.4417869,0.5177747,0.6400528,"brNDC");
	pvtxt_recon->SetFillColor(kWhite);
	txt = pvtxt_recon->AddText( "#splitline{Sum of binned #bf{template}}{samples normalized to ~5 fb^{-1}}" );
	
	TPaveText* pvtxt_compare = new TPaveText(0.5940635,0.6619171,0.8501254,0.8319301,"brNDC");
	pvtxt_compare->SetFillColor(kWhite);
	txt = pvtxt_compare->AddText( "#splitline{Template vs. #it{ATLAS}}{MC10 reconstructed}" );
	
	
	// for the binned-wights histograms
	logMmin_afb       = log10(imass_afb_min);
	logMmax_afb       = log10(imass_afb_max);
	logMbinwidth_afb  = (Double_t)( (logMmax_afb-logMmin_afb)/(Double_t)imass_afb_nbins );
	imass_afb_bins[0] = imass_afb_min;
	for(Int_t i=1 ; i<=imass_afb_nbins ; i++) imass_afb_bins[i] = TMath::Power( 10,(logMmin_afb + i*logMbinwidth_afb) );
	
	
	
	TH1D* hDummy_afb = new TH1D("dummy","dummy",imass_afb_nbins,imass_afb_bins);
	
	vector<TH1D*> vhCosThSumTmp;
	vector<TH1D*> vhCosThSumZ0;
	vector<TH1D*> vhCosThSumKK;
	vector<TH1D*> vhCosThSumZP;
	vector<TH1D*> vhCosThSumKKweights;
	vector<TH1D*> vhCosThSumZPweights;
	stringstream strm;
	string str;
	string range;
	for(Int_t i=0 ; i<imass_afb_nbins ; i++)
	{
		range.clear();
		strm.clear();
		str.clear();
		strm << imass_afb_bins[i];
		strm >> str;
		range += str + " GeV #rightarrow ";
		strm.clear();
		str.clear();
		strm << imass_afb_bins[i+1];
		strm >> str;
		range += str + " GeV";
		
		vhCosThSumTmp.push_back( new TH1D((""+range).c_str(),(""+range).c_str(), 50,-1.,+1.) );
		
		vhCosThSumZ0.push_back( new TH1D(("sumZ0_"+range).c_str(),("sumZ0_"+range).c_str(), 50,-1.,+1.) );
		vhCosThSumZP.push_back( new TH1D(("sumZP_"+range).c_str(),("sumZP_"+range).c_str(), 50,-1.,+1.) );
		vhCosThSumKK.push_back( new TH1D(("sumKK_"+range).c_str(),("sumKK_"+range).c_str(), 50,-1.,+1.) );
		
		vhCosThSumZPweights.push_back( new TH1D(("wgtZP_"+range).c_str(),("wgtZP_"+range).c_str(), 50,-1.,+1.) );
		vhCosThSumKKweights.push_back( new TH1D(("wgtKK_"+range).c_str(),("wgtKK_"+range).c_str(), 50,-1.,+1.) );
	}
	
	
	// combined histos
	TH1D* hMassSumTmp;
	TH1D* hResTmp;
	TH1D* hMassSumZ0;
	TH1D* hMassSumZP;
	TH1D* hMassSumKK;
	TH1D* hWeightsZP;
	TH1D* hWeightsKK;
	TH1D* hMassReconZ0;
	TH1D* hMassReconZP;
	TH1D* hMassReconTemplateZP;
	TH1D* hMassReconTemplateKK;
	TH1D* hResReconZ0;
	TH1D* hResReconZP;
	TH1D* hResTemplateZP;
	TH1D* hResTemplateKK;
	if(doLogx)
	{
		hMassSumTmp = new TH1D("sumTmp","sumTmp",nxbins,xbins);
		hMassSumZ0 = new TH1D("sumZ0","sumZ0",nxbins,xbins);
		hMassSumZP = new TH1D("sumZP","sumZP",nxbins,xbins);
		hMassSumKK = new TH1D("sumKK","sumKK",nxbins,xbins);
		hWeightsZP = new TH1D("weightsZP","weightsZP",nxbins,xbins);
		hWeightsKK = new TH1D("weightsKK","weightsKK",nxbins,xbins);
		
		hMassReconZ0 = new TH1D("ReconZ0","ReconZ0",nxbins,xbins);
		hMassReconZP = new TH1D("ReconZP","ReconZP",nxbins,xbins);
		hMassReconTemplateZP = new TH1D("ReconTemplateZP","ReconTemplateZP",nxbins,xbins);
		hMassReconTemplateKK = new TH1D("ReconTemplateKK","ReconTemplateKK",nxbins,xbins);
	}
	else
	{
		hMassSumTmp = new TH1D("sumTmp","sumTmp",nxbins,xmin,xmax);
		hMassSumZ0 = new TH1D("sumZ0","sumZ0",nxbins,xmin,xmax);
		hMassSumZP = new TH1D("sumZP","sumZP",nxbins,xmin,xmax);
		hMassSumKK = new TH1D("sumKK","sumKK",nxbins,xmin,xmax);
		hWeightsZP = new TH1D("weightsZP","weightsZP",nxbins,xmin,xmax);
		hWeightsKK = new TH1D("weightsKK","weightsKK",nxbins,xmin,xmax);
		
		hMassReconZ0 = new TH1D("ReconZ0","ReconZ0",nxbins,xmin,xmax);
		hMassReconZP = new TH1D("ReconZP","ReconZP",nxbins,xmin,xmax);
		hMassReconTemplateZP = new TH1D("ReconTemplateZP","ReconTemplateZP",nxbins,xmin,xmax);
		hMassReconTemplateKK = new TH1D("ReconTemplateKK","ReconTemplateKK",nxbins,xmin,xmax);
	}
	
	hResTmp = new TH1D("ResTmp","ResTmp",nxbins,-0.2,+0.2);
	hResReconZ0 = new TH1D("ResReconZ0","ResReconZ0",nxbins,-0.2,+0.2);
	hResReconZP = new TH1D("ResReconZP","ResReconZP",nxbins,-0.2,+0.2);
	hResTemplateZP = new TH1D("ResZP","ResZP",nxbins,-0.2,+0.2);
	hResTemplateKK = new TH1D("ResKK","ResKK",nxbins,-0.2,+0.2);
	
	
	///////////////////////////////////
	double nGeneratedEvents = 5e5; ////
	///////////////////////////////////
	
	TFile* file;
	TTree* tree;
	double ymin = 0.;
	int vsize = 0;
	
	for(int model=Z0 ; model<=KK ; model++)
	{
		////////////////////////////
		// reset all ///////////////
		clearSamples(); ////////////
		if(doLogx) hMassSumTmp->Reset(); //////////
		else { for(Int_t b=0 ; b<=hMassSumTmp->GetNbinsX() ; b++) hMassSumTmp->SetBinContent(b,0.); }
		for(int i=0 ; i<imass_afb_nbins ; i++) vhCosThSumTmp[i]->Reset();
		////////////////////////////
	
		if(model==Z0)
		{
			addSample("ATLASZ0/mcLocalControl_DYmumu_120M250",   col0, 19999, 0.0086861*nb2mb);
			addSample("ATLASZ0/mcLocalControl_DYmumu_250M400",   col1, 19996, 0.00041431*nb2mb);
			addSample("ATLASZ0/mcLocalControl_DYmumu_400M600",   col2, 19993, 0.000067464*nb2mb);
			addSample("ATLASZ0/mcLocalControl_DYmumu_600M800",   col3, 15994, 0.000011168*nb2mb);
			addSample("ATLASZ0/mcLocalControl_DYmumu_800M1000",  col5, 19992, 0.0000027277*nb2mb);
			addSample("ATLASZ0/mcLocalControl_DYmumu_1000M1250", col5, 19995, 0.00000091646*nb2mb);
			addSample("ATLASZ0/mcLocalControl_DYmumu_1250M1500", col5, 19993, 0.00000024942*nb2mb);
			addSample("ATLASZ0/mcLocalControl_DYmumu_1500M1750", col5, 19997, 0.000000076876*nb2mb);
			addSample("ATLASZ0/mcLocalControl_DYmumu_1750M2000", col5, 19993, 0.000000026003*nb2mb);
			addSample("ATLASZ0/mcLocalControl_DYmumu_M2000",     col5, 19996, 0.000000015327*nb2mb);
		}
		
		if(model==ZP && sMass=="1000")
		{
			addSample("Pythia8_ZprimeSSM1000mumu_120M500",  col0, nGeneratedEvents, 7.78812E-09);
			addSample("Pythia8_ZprimeSSM1000mumu_500M1500", col1, nGeneratedEvents, 1.08535E-10);
			addSample("Pythia8_ZprimeSSM1000mumu_1500M0",   col2, nGeneratedEvents, 2.42594E-13);
		}
		if(model==ZP && sMass=="2000")
		{
			addSample("Pythia8_ZprimeSSM2000mumu_120M1000",  col0, nGeneratedEvents, 7.91467E-09);
			addSample("Pythia8_ZprimeSSM2000mumu_1000M3000", col1, nGeneratedEvents, 1.94433E-12);
			addSample("Pythia8_ZprimeSSM2000mumu_3000M0",    col2, nGeneratedEvents, 3.27844E-16);
		}
		if(model==ZP && sMass=="3000")
		{
			addSample("Pythia8_ZprimeSSM3000mumu_120M1500",  col0, nGeneratedEvents, 7.94181E-09);
			addSample("Pythia8_ZprimeSSM3000mumu_1500M4500", col1, nGeneratedEvents, 8.9226E-14);
			addSample("Pythia8_ZprimeSSM3000mumu_4500M0",    col2, nGeneratedEvents, 1.18978E-19);
		}
		
		
		if(model==KK && sMass=="1000")
		{
			addSample("Pythia8_ZKK1000mumu_120M500",  col0, nGeneratedEvents, 6.87332E-09);
			addSample("Pythia8_ZKK1000mumu_500M1500", col1, nGeneratedEvents, 7.83954E-10);
			addSample("Pythia8_ZKK1000mumu_1500M0",   col2, nGeneratedEvents, 1.11827E-11);
		}
		if(model==KK && sMass=="2000")
		{
			addSample("Pythia8_ZKK2000mumu_120M1000",  col0, nGeneratedEvents, 7.68181E-09);
			addSample("Pythia8_ZKK2000mumu_1000M3000", col1, nGeneratedEvents, 1.22497E-11);
			addSample("Pythia8_ZKK2000mumu_3000M0",    col2, nGeneratedEvents, 3.44554E-15);
		}
		if(model==KK && sMass=="3000")
		{
			addSample("Pythia8_ZKK3000mumu_120M1500",  col0, nGeneratedEvents, 7.8351E-09);
			addSample("Pythia8_ZKK3000mumu_1500M4500", col1, nGeneratedEvents, 2.98849E-13);
			addSample("Pythia8_ZKK3000mumu_4500M0",    col2, nGeneratedEvents, 7.56956E-20);
		}
			
		// get the data
		ymin = 0.;
		vsize = (int)svPaths.size();
		
		for(int n=vsize-1 ; n>=0 ; n--)
		{
			cout << "svPaths[" << n << "]=" << svPaths[n] << endl;
			file = TFile::Open(svPaths[n].c_str(),"READ");	
			if(model==Z0)
			{
				tree = (TTree*)file->Get("truth/truth_tree");
				tree->SetBranchAddress("truth_all_isValid", &truth_all_isValid);
				tree->SetBranchAddress("truth_all_dr", &truth_all_dr);
				tree->SetBranchAddress("truth_all_E", &truth_all_E);
				tree->SetBranchAddress("truth_all_pt", &truth_all_pt);
				tree->SetBranchAddress("truth_all_eta", &truth_all_eta);
				tree->SetBranchAddress("truth_all_phi", &truth_all_phi);
				tree->SetBranchAddress("truth_all_type", &truth_all_type);
				tree->SetBranchAddress("truth_all_status", &truth_all_status);
				tree->SetBranchAddress("truth_all_barcode", &truth_all_barcode);
				tree->SetBranchAddress("truth_all_mothertype", &truth_all_mothertype);
				tree->SetBranchAddress("truth_all_motherbarcode", &truth_all_motherbarcode);
				tree->SetBranchAddress("truth_all_matched", &truth_all_matched);
				tree->SetBranchAddress("truth_all_Mhat", &truth_all_Mhat);
				tree->SetBranchAddress("truth_all_CosThetaCS", &truth_all_CosThetaCS);
				tree->SetBranchAddress("truth_all_CosThetaHE", &truth_all_CosThetaHE);
				tree->SetBranchAddress("truth_all_ySystem",&truth_all_ySystem);
				tree->SetBranchAddress("truth_all_QT", &truth_all_QT);
				
				int valids = 0;

				for(Int_t i=0 ; i<tree->GetEntries() ; i++)
				{
					tree->GetEntry(i);
					
					if(truth_all_isValid)
					{
						valids++;
						hvBinnedHistos_imass[n]->Fill(truth_all_Mhat);
						int bin = hDummy_afb->FindBin(truth_all_Mhat);
						if(bin<=0 || bin>imass_afb_nbins) continue;
						hvvBinnedHistos_cosTh[n][bin-1]->Fill(truth_all_CosThetaCS);
					}
				}
				cout << "n=" << n << ", valids=" << valids << endl;
			}
			else
			{ 
				tree = (TTree*)file->Get("tree");
				tree->SetBranchAddress("mHat",&mHat);
				tree->SetBranchAddress("QT",&qT);
				tree->SetBranchAddress("ySystem",&ysystem);
				tree->SetBranchAddress("cosThetaHE",&cosThetaHE);
				tree->SetBranchAddress("cosThetaCS",&cosThetaCS);
				tree->SetBranchAddress("id",&id);
				tree->SetBranchAddress("charge",&charge);
				tree->SetBranchAddress("px",&px);
				tree->SetBranchAddress("py",&py);
				tree->SetBranchAddress("pz",&pz);
				tree->SetBranchAddress("E",&E);
				tree->SetBranchAddress("m",&m);
				tree->SetBranchAddress("y",&y);
				tree->SetBranchAddress("pT",&pT);
				tree->SetBranchAddress("eta",&eta);
				tree->SetBranchAddress("phi",&phi);
				tree->SetBranchAddress("theta",&theta);

				for(Int_t i=0 ; i<tree->GetEntries() ; i++)
				{
					tree->GetEntry(i);
					hvBinnedHistos_imass[n]->Fill(mHat);
					
					int bin = hDummy_afb->FindBin(mHat);
					if(bin<=0 || bin>imass_afb_nbins) continue;
					hvvBinnedHistos_cosTh[n][bin-1]->Fill(cosThetaCS); 
				}
			}
			
			/////////////////////////////////////////////////////////////
			hvBinnedHistos_imass[n]->Scale(dvWeights[n]); // scale //////
			for(Int_t i=0 ; i<imass_afb_nbins ; i++)       // scale /////
			{
				hvvBinnedHistos_cosTh[n][i]->Scale(dvWeights[n]);
			}
			/////////////////////////////////////////////////////////////
			
			////////////////////////////////////////////////////////
			hMassSumTmp->Add(hvBinnedHistos_imass[n]); // sum //////
			for(Int_t i=0 ; i<imass_afb_nbins ; i++)   // sum //////
			{
				vhCosThSumTmp[i]->Add(hvvBinnedHistos_cosTh[n][i]);
			}
			////////////////////////////////////////////////////////
			
			file->Close();
		}
		
		
		if(model==Z0)
		{
			hMassSumZ0 = (TH1D*)hMassSumTmp->Clone("");
			for(Int_t i=0 ; i<imass_afb_nbins ; i++) vhCosThSumZ0[i] = (TH1D*)vhCosThSumTmp[i]->Clone("");
		}
		if(model==ZP)
		{
			hMassSumZP = (TH1D*)hMassSumTmp->Clone("");
			for(Int_t i=0 ; i<imass_afb_nbins ; i++) vhCosThSumZP[i] = (TH1D*)vhCosThSumTmp[i]->Clone("");
		}
		if(model==KK)
		{
			hMassSumKK = (TH1D*)hMassSumTmp->Clone("");
			for(Int_t i=0 ; i<imass_afb_nbins ; i++) vhCosThSumKK[i] = (TH1D*)vhCosThSumTmp[i]->Clone("");
		}
	}
	
	
	////////////////////////////////////////////////////////////////
	// The ratios //////////////////////////////////////////////////
	hWeightsZP = (TH1D*)hMassSumZP->Clone(""); /////////////////////
	hWeightsZP->Divide(hMassSumZ0); ////////////////////////////////
	for(Int_t i=0 ; i<imass_afb_nbins ; i++) 
	{
		vhCosThSumZPweights[i] = (TH1D*)vhCosThSumZP[i]->Clone(""); //////////
		vhCosThSumZPweights[i]->Divide(vhCosThSumZ0[i]); /////////////////////
	}
	//--------------------------------------------------------------
	hWeightsKK = (TH1D*)hMassSumKK->Clone(""); /////////////////////
	hWeightsKK->Divide(hMassSumZ0); ////////////////////////////////
	for(Int_t i=0 ; i<imass_afb_nbins ; i++) 
	{
		vhCosThSumKKweights[i] = (TH1D*)vhCosThSumKK[i]->Clone(""); //////////
		vhCosThSumKKweights[i]->Divide(vhCosThSumZ0[i]); /////////////////////
	}
	////////////////////////////////////////////////////////////////
	
	
	for(Int_t i=0 ; i<imass_afb_nbins ; i++)
	{
		// WEIGHTS ....
		vhCosThSumZPweights[i]->SetTitle((TString)"weights: " + (TString)vhCosThSumZPweights[i]->GetTitle());
		vhCosThSumKKweights[i]->SetTitle((TString)"weights: " + (TString)vhCosThSumKKweights[i]->GetTitle());
	}
	////////////////////////////////////////////////////////////////////////////
	
	
	// test draw
	vector<TCanvas*> vC;
	vector<TVirtualPad*> vP1;
	vector<TVirtualPad*> vP2;
	vector<TLegend*> vL1;
	vector<TLegend*> vL2;
	for(Int_t i=0 ; i<imass_afb_nbins ; i++)
	{
		strm.clear();
		str.clear();
		strm << i;
		strm >> str;
		vC.push_back( new TCanvas(("c"+str).c_str(),("c"+str).c_str(),0,0,1200,800) );
		vC[i]->Divide(1,2);
		vC[i]->Draw();
		
		vP1.push_back( vC[i]->cd(1) );
		//vP1[i]->Range(-1.315789,-270.0778,1.315789,1417.908);
		vP1[i]->SetLogy();
		
		vP2.push_back( vC[i]->cd(2) );
		//vP2[i]->Range(-1.315789,-1.165699,1.315789,0.9704915);
		vP2[i]->SetLogy();
		
		//vL1.push_back( new TLegend(0.1462841,0.1774325,0.5373268,0.4004816,NULL,"brNDC") );
		vL1.push_back( new TLegend(0.6518668,0.1842617,0.8583373,0.3434801,NULL,"brNDC") );
		vL1[i]->SetFillColor(kWhite);
		
		//vL2.push_back( new TLegend(0.1480616,0.7509715,0.4342337,0.9272078,NULL,"brNDC") );
		vL2.push_back( new TLegend(0.7315023,0.181969,0.8745992,0.3018068,NULL,"brNDC") );
		vL2[i]->SetFillColor(kWhite);
		
		
		
		vP1[i]->cd();
		vP1[i]->Draw();
		float max = vhCosThSumZ0[i]->GetMaximum();
		max = (vhCosThSumZP[i]->GetMaximum() > max) ? vhCosThSumZP[i]->GetMaximum() : max;
		max = (vhCosThSumKK[i]->GetMaximum() > max) ? vhCosThSumKK[i]->GetMaximum() : max;
	
		vhCosThSumZ0[i]->SetMinimum(1.e-2);
		vhCosThSumZ0[i]->SetMaximum(2.*max);
		vhCosThSumZ0[i]->SetLineColor(col0);
		vhCosThSumZ0[i]->SetLineStyle(1);
		vhCosThSumZ0[i]->SetLineWidth(2);
		vhCosThSumZ0[i]->SetXTitle("cos#theta*");
		vhCosThSumZ0[i]->SetYTitle("Events");
		/*if(2.*max<1.e2)*/ vhCosThSumZ0[i]->GetYaxis()->SetMoreLogLabels();
		vhCosThSumZ0[i]->Draw();
		vL1[i]->AddEntry(vhCosThSumZ0[i], "SM #gamma/Z^{0} (#it{ATLAS} MC10 truth)", "l");
		vhCosThSumZP[i]->SetMinimum(1.e-2);
		vhCosThSumZP[i]->SetMaximum(2.*max);
		vhCosThSumZP[i]->SetLineColor(col2);
		vhCosThSumZP[i]->SetLineStyle(1);
		vhCosThSumZP[i]->SetLineWidth(2);
		vhCosThSumZP[i]->SetXTitle("cos#theta*");
		vhCosThSumZP[i]->SetYTitle("Events");
		/*if(2.*max<1.e2)*/ vhCosThSumZP[i]->GetYaxis()->SetMoreLogLabels();
		vhCosThSumZP[i]->Draw("SAMES");
		sName = sMass + " GeV Z' SSM (#scale[1.1]{P}#scale[0.9]{YTHIA8})";
		vL1[i]->AddEntry(vhCosThSumZP[i], sName.c_str(), "l");
		vhCosThSumKK[i]->SetMinimum(1.e-2);
		vhCosThSumKK[i]->SetMaximum(2.*max);
		vhCosThSumKK[i]->SetLineColor(col1);
		vhCosThSumKK[i]->SetLineStyle(1);
		vhCosThSumKK[i]->SetLineWidth(2);
		vhCosThSumKK[i]->SetXTitle("cos#theta*");
		vhCosThSumKK[i]->SetYTitle("Events");
		/*if(2.*max<1.e2)*/ vhCosThSumKK[i]->GetYaxis()->SetMoreLogLabels();
		vhCosThSumKK[i]->Draw("SAMES");
		sName = sMass + " GeV S^{1}/Z_{2} KK (#scale[1.1]{P}#scale[0.9]{YTHIA8})"; 
		vL1[i]->AddEntry(vhCosThSumKK[i], sName.c_str(), "l");
		vL1[i]->Draw("SAMES");
		
		vP1[i]->cd();
		vP1[i]->RedrawAxis();
		vP1[i]->Update();
		
		//--------------------------------------------
		
		vP2[i]->cd();
		vP2[i]->Draw();
		max = vhCosThSumZPweights[i]->GetMaximum();
		max = (vhCosThSumKKweights[i]->GetMaximum() > max) ? vhCosThSumKKweights[i]->GetMaximum() : max;
		
		string sYTitle = "Events_{BSM}/Events_{#gamma/Z^{0}}";
		sName = sMass + " GeV Z' SSM";
		vhCosThSumZPweights[i]->SetMinimum(1.e-1);
		vhCosThSumZPweights[i]->SetMaximum(2.*max);
		vhCosThSumZPweights[i]->SetLineColor(col2);
		vhCosThSumZPweights[i]->SetLineStyle(1);
		vhCosThSumZPweights[i]->SetLineWidth(2);
		vhCosThSumZPweights[i]->SetXTitle("cos#theta*");
		vhCosThSumZPweights[i]->SetYTitle(sYTitle.c_str());
		/*if(2.*max<1.e2)*/ vhCosThSumZPweights[i]->GetYaxis()->SetMoreLogLabels(); 
		vhCosThSumZPweights[i]->Draw();
		vL2[i]->AddEntry(vhCosThSumZPweights[i], sName.c_str(), "l");
		sName   = sMass + " GeV S^{1}/Z_{2} KK";
		vhCosThSumKKweights[i]->SetMinimum(1.e-1);
		vhCosThSumKKweights[i]->SetMaximum(2.*max);
		vhCosThSumKKweights[i]->SetLineColor(col1);
		vhCosThSumKKweights[i]->SetLineStyle(1);
		vhCosThSumKKweights[i]->SetLineWidth(2);
		vhCosThSumKKweights[i]->SetXTitle("cos#theta*");
		vhCosThSumKKweights[i]->SetYTitle(sYTitle.c_str());
		/*if(2.*max<1.e2)*/ vhCosThSumKKweights[i]->GetYaxis()->SetMoreLogLabels(); 
		vhCosThSumKKweights[i]->Draw("SAMES");
		vL2[i]->AddEntry(vhCosThSumKKweights[i], sName.c_str(), "l");
		vL2[i]->Draw("SAMES");
		
		vP2[i]->cd();
		vP2[i]->RedrawAxis();
		vP2[i]->Update();
		
		vC[i]->Update();
		TString name = "plots/plot_cosTheta_" + str;
		vC[i]->SaveAs(name+".eps");
		vC[i]->SaveAs(name+".C");
		vC[i]->SaveAs(name+".root");
		vC[i]->SaveAs(name+".png");
	}
	
	
	cout << "Weights are calculated\n" << endl;
	//-------------------------------------------------------------------------------------
	
	
	for(int model=Z0 ; model<=KK ; model++)
	{
		////////////////////////////
		// reset all ///////////////
		clearSamples(); ////////////
		if(doLogx) hMassSumTmp->Reset(); //////////
		else { for(Int_t b=0 ; b<=hMassSumTmp->GetNbinsX() ; b++) hMassSumTmp->SetBinContent(b,0.); }
		hResTmp->Reset();
		////////////////////////////
	
		addSample("ATLASZ0/mcLocalControl_DYmumu_120M250",   col0, 19999, 0.0086861*nb2mb);
		addSample("ATLASZ0/mcLocalControl_DYmumu_250M400",   col1, 19996, 0.00041431*nb2mb);
		addSample("ATLASZ0/mcLocalControl_DYmumu_400M600",   col2, 19993, 0.000067464*nb2mb);
		addSample("ATLASZ0/mcLocalControl_DYmumu_600M800",   col3, 15994, 0.000011168*nb2mb);
		addSample("ATLASZ0/mcLocalControl_DYmumu_800M1000",  col5, 19992, 0.0000027277*nb2mb);
		addSample("ATLASZ0/mcLocalControl_DYmumu_1000M1250", col5, 19995, 0.00000091646*nb2mb);
		addSample("ATLASZ0/mcLocalControl_DYmumu_1250M1500", col5, 19993, 0.00000024942*nb2mb);
		addSample("ATLASZ0/mcLocalControl_DYmumu_1500M1750", col5, 19997, 0.000000076876*nb2mb);
		addSample("ATLASZ0/mcLocalControl_DYmumu_1750M2000", col5, 19993, 0.000000026003*nb2mb);
		addSample("ATLASZ0/mcLocalControl_DYmumu_M2000",     col5, 19996, 0.000000015327*nb2mb);
			
		// get the data
		ymin = 0.;
		vsize = (int)svPaths.size();
		
		for(int n=vsize-1 ; n>=0 ; n--)
		{
			cout << "svPaths[" << n << "]=" << svPaths[n] << endl;
			file = TFile::Open(svPaths[n].c_str(),"READ");	
			tree = (TTree*)file->Get("truth/truth_tree");
			
			tree->SetBranchAddress("truth_all_isValid", &truth_all_isValid);
			tree->SetBranchAddress("truth_all_dr", &truth_all_dr);
			tree->SetBranchAddress("truth_all_E", &truth_all_E);
			tree->SetBranchAddress("truth_all_pt", &truth_all_pt);
			tree->SetBranchAddress("truth_all_eta", &truth_all_eta);
			tree->SetBranchAddress("truth_all_phi", &truth_all_phi);
			tree->SetBranchAddress("truth_all_type", &truth_all_type);
			tree->SetBranchAddress("truth_all_status", &truth_all_status);
			tree->SetBranchAddress("truth_all_barcode", &truth_all_barcode);
			tree->SetBranchAddress("truth_all_mothertype", &truth_all_mothertype);
			tree->SetBranchAddress("truth_all_motherbarcode", &truth_all_motherbarcode);
			tree->SetBranchAddress("truth_all_matched", &truth_all_matched);
			tree->SetBranchAddress("truth_all_Mhat", &truth_all_Mhat);
			tree->SetBranchAddress("truth_all_CosThetaCS", &truth_all_CosThetaCS);
			tree->SetBranchAddress("truth_all_CosThetaHE", &truth_all_CosThetaHE);
			tree->SetBranchAddress("truth_all_ySystem",&truth_all_ySystem);
			tree->SetBranchAddress("truth_all_QT", &truth_all_QT);
				
			tree->SetBranchAddress("recon_all_isValid", &recon_all_isValid);
			tree->SetBranchAddress("recon_all_E", &recon_all_E);
			tree->SetBranchAddress("recon_all_pt", &recon_all_pt);
			tree->SetBranchAddress("recon_all_m", &recon_all_m);
			tree->SetBranchAddress("recon_all_eta", &recon_all_eta);
			tree->SetBranchAddress("recon_all_phi", &recon_all_phi);
			tree->SetBranchAddress("recon_all_px", &recon_all_px);
			tree->SetBranchAddress("recon_all_py", &recon_all_py);
			tree->SetBranchAddress("recon_all_pz", &recon_all_pz);
			tree->SetBranchAddress("recon_all_charge", &recon_all_charge);
			tree->SetBranchAddress("recon_all_y", &recon_all_y);
			tree->SetBranchAddress("recon_all_id", &recon_all_id);
			tree->SetBranchAddress("recon_all_theta", &recon_all_theta);
			tree->SetBranchAddress("recon_all_Mhat", &recon_all_Mhat);
			tree->SetBranchAddress("recon_all_CosThetaCS", &recon_all_CosThetaCS);
			tree->SetBranchAddress("recon_all_CosThetaHE", &recon_all_CosThetaHE);
			tree->SetBranchAddress("recon_all_ySystem",&recon_all_ySystem);
			tree->SetBranchAddress("recon_all_QT", &recon_all_QT);

			for(Int_t i=0 ; i<tree->GetEntries() ; i++)
			{
				tree->GetEntry(i);
				
				if(recon_all_isValid  &&  truth_all_isValid)
				{
					Int_t    bin    = 0;
					Double_t weight = 0.;
					if(model==Z0)
					{
						hvBinnedHistos_imass[n]->Fill(recon_all_Mhat);
						hvBinnedHistos_imassRes[n]->Fill((recon_all_Mhat-truth_all_Mhat)/truth_all_Mhat); // use all events
					}
					if(model==ZP)
					{
						bin = hWeightsZP->FindBin(truth_all_Mhat);
						weight = hWeightsZP->GetBinContent(bin);
						hvBinnedHistos_imass[n]->Fill(recon_all_Mhat,weight);
						hvBinnedHistos_imassRes[n]->Fill((recon_all_Mhat-truth_all_Mhat)/truth_all_Mhat, weight); // use all events
					}
					if(model==KK)
					{
						bin = hWeightsKK->FindBin(truth_all_Mhat);
						weight = hWeightsKK->GetBinContent(bin);
						hvBinnedHistos_imass[n]->Fill(recon_all_Mhat,weight);
						hvBinnedHistos_imassRes[n]->Fill((recon_all_Mhat-truth_all_Mhat)/truth_all_Mhat, weight); // use all events
					}
				}
			}
			
			/////////////////////////////////////////////////////////////
			hvBinnedHistos_imass[n]->Scale(dvWeights[n]); // scale //////
			hvBinnedHistos_imassRes[n]->Scale(dvWeights[n]); // scale ///
			/////////////////////////////////////////////////////////////
			
			////////////////////////////////////////////////////
			hMassSumTmp->Add(hvBinnedHistos_imass[n]); // sum //////
			hResTmp->Add(hvBinnedHistos_imassRes[n]); // sum ///
			////////////////////////////////////////////////////
			
			file->Close();
		}
		
		if(model==Z0) hMassReconZ0         = (TH1D*)hMassSumTmp->Clone("");
		if(model==ZP) hMassReconTemplateZP = (TH1D*)hMassSumTmp->Clone("");
		if(model==KK) hMassReconTemplateKK = (TH1D*)hMassSumTmp->Clone("");
		
		if(model==Z0) hResReconZ0 = (TH1D*)hResTmp->Clone("");
		if(model==ZP) hResTemplateZP = (TH1D*)hResTmp->Clone("");
		if(model==KK) hResTemplateKK = (TH1D*)hResTmp->Clone("");
	}
	cout << "Templates are ready\n" << endl;
	//-----------------------------------------------------------------------------
	
	
	
	
	
	
	//bool calcSumSigma = true;
	////////////////////////////
	// reset all ///////////////
	clearSamples(); ////////////
	if(doLogx) hMassSumTmp->Reset(); //////////
	else { for(Int_t b=0 ; b<=hMassSumTmp->GetNbinsX() ; b++) hMassSumTmp->SetBinContent(b,0.); }
	hResTmp->Reset();
	////////////////////////////
	
	addSample("ATLASZP/mcLocalControl_Zprime_mumu_SSM1000",  col2, 18996, 0.00012973*nb2mb);
	
	// get the data
	ymin = 0.;
	vsize = (int)svPaths.size();
	
	for(int n=vsize-1 ; n>=0 ; n--)
	{
		cout << "svPaths[" << n << "]=" << svPaths[n] << endl;
		file = TFile::Open(svPaths[n].c_str(),"READ");	
		tree = (TTree*)file->Get("truth/truth_tree");
		
		tree->SetBranchAddress("truth_all_isValid", &truth_all_isValid);
		tree->SetBranchAddress("truth_all_dr", &truth_all_dr);
		tree->SetBranchAddress("truth_all_E", &truth_all_E);
		tree->SetBranchAddress("truth_all_pt", &truth_all_pt);
		tree->SetBranchAddress("truth_all_eta", &truth_all_eta);
		tree->SetBranchAddress("truth_all_phi", &truth_all_phi);
		tree->SetBranchAddress("truth_all_type", &truth_all_type);
		tree->SetBranchAddress("truth_all_status", &truth_all_status);
		tree->SetBranchAddress("truth_all_barcode", &truth_all_barcode);
		tree->SetBranchAddress("truth_all_mothertype", &truth_all_mothertype);
		tree->SetBranchAddress("truth_all_motherbarcode", &truth_all_motherbarcode);
		tree->SetBranchAddress("truth_all_matched", &truth_all_matched);
		tree->SetBranchAddress("truth_all_Mhat", &truth_all_Mhat);
		tree->SetBranchAddress("truth_all_CosThetaCS", &truth_all_CosThetaCS);
		tree->SetBranchAddress("truth_all_CosThetaHE", &truth_all_CosThetaHE);
		tree->SetBranchAddress("truth_all_ySystem",&truth_all_ySystem);
		tree->SetBranchAddress("truth_all_QT", &truth_all_QT);
				
		tree->SetBranchAddress("recon_all_isValid", &recon_all_isValid);
		tree->SetBranchAddress("recon_all_E", &recon_all_E);
		tree->SetBranchAddress("recon_all_pt", &recon_all_pt);
		tree->SetBranchAddress("recon_all_m", &recon_all_m);
		tree->SetBranchAddress("recon_all_eta", &recon_all_eta);
		tree->SetBranchAddress("recon_all_phi", &recon_all_phi);
		tree->SetBranchAddress("recon_all_px", &recon_all_px);
		tree->SetBranchAddress("recon_all_py", &recon_all_py);
		tree->SetBranchAddress("recon_all_pz", &recon_all_pz);
		tree->SetBranchAddress("recon_all_charge", &recon_all_charge);
		tree->SetBranchAddress("recon_all_y", &recon_all_y);
		tree->SetBranchAddress("recon_all_id", &recon_all_id);
		tree->SetBranchAddress("recon_all_theta", &recon_all_theta);
		tree->SetBranchAddress("recon_all_Mhat", &recon_all_Mhat);
		tree->SetBranchAddress("recon_all_CosThetaCS", &recon_all_CosThetaCS);
		tree->SetBranchAddress("recon_all_CosThetaHE", &recon_all_CosThetaHE);
		tree->SetBranchAddress("recon_all_ySystem",&recon_all_ySystem);
		tree->SetBranchAddress("recon_all_QT", &recon_all_QT);
		for(Int_t i=0 ; i<tree->GetEntries() ; i++)
		{
			tree->GetEntry(i);
			
			//if(recon_all_isValid  &&  truth_all_isValid)
			//{
				hvBinnedHistos_imass[n]->Fill(recon_all_Mhat);
				hvBinnedHistos_imassRes[n]->Fill((recon_all_Mhat-truth_all_Mhat)/truth_all_Mhat); // use all events
			//}
		}

		/////////////////////////////////////////////////////////////
		hvBinnedHistos_imass[n]->Scale(dvWeights[n]); // scale //////
		hvBinnedHistos_imassRes[n]->Scale(dvWeights[n]); // scale ///
		/////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////
		hMassSumTmp->Add(hvBinnedHistos_imass[n]); // sum //////
		hResTmp->Add(hvBinnedHistos_imassRes[n]); // sum ///
		////////////////////////////////////////////////////

		file->Close();
		hMassReconZP    = (TH1D*)hMassSumTmp->Clone("");
		hResReconZP = (TH1D*)hResTmp->Clone("");
	}
	cout << "Templates are ready\n" << endl;
	//-----------------------------------------------------------------------------
	
	


	
	
	
	string sYTitle = "";
	
	
	pad_sigma->cd();
	pad_sigma->Draw();
	ymin = 0.5*getYmin(hMassSumZ0);
	hMassSumZ0->SetMinimum(ymin);
	hMassSumZ0->SetMaximum(1.5*hMassSumZ0->GetMaximum());
	hMassSumZ0->SetLineColor(col0);
	hMassSumZ0->SetLineWidth(2);
	hMassSumZ0->SetTitle("");
	hMassSumZ0->SetXTitle("#hat{m}_{#mu#mu} GeV");
	hMassSumZ0->SetYTitle("Events");
	if(doLogx) hMassSumZ0->GetXaxis()->SetMoreLogLabels(); 
	if(doLogx) hMassSumZ0->GetXaxis()->SetMoreLogLabels(); 
	hMassSumZ0->Draw();
	//leg_mass->AddEntry(hMassSumZ0, "SM #gamma/Z^{0}", "l");
	leg_mass->AddEntry(hMassSumZ0, "SM #gamma/Z^{0} (#it{ATLAS} MC10 truth)", "l");
	
	sName = sMass + " GeV S^{1}/Z_{2} KK (#scale[1.1]{P}#scale[0.9]{YTHIA8})";
	hMassSumKK->SetLineColor(col1);
	hMassSumKK->SetLineWidth(2);
	hMassSumKK->SetTitle("");
	hMassSumKK->SetXTitle("#hat{m}_{#mu#mu} GeV");
	hMassSumKK->SetYTitle("Events");
	if(doLogx) hMassSumKK->GetXaxis()->SetMoreLogLabels(); 
	if(doLogx) hMassSumKK->GetXaxis()->SetMoreLogLabels();
	hMassSumKK->Draw("SAMES");
	leg_mass->AddEntry(hMassSumKK, sName.c_str(), "l");
	
	sName = sMass + " GeV Z' SSM (#scale[1.1]{P}#scale[0.9]{YTHIA8})";
	hMassSumZP->SetLineColor(col2);
	hMassSumZP->SetLineWidth(2);
	hMassSumZP->SetTitle("");
	hMassSumZP->SetXTitle("#hat{m}_{#mu#mu} GeV");
	hMassSumZP->SetYTitle("Events");
	if(doLogx) hMassSumZP->GetXaxis()->SetMoreLogLabels(); 
	if(doLogx) hMassSumZP->GetXaxis()->SetMoreLogLabels(); 
	hMassSumZP->Draw("SAMES");
	leg_mass->AddEntry(hMassSumZP, sName.c_str(), "l");
	
	leg_mass->Draw("SAMES");
	pvtxt->Draw("SAMES");
	
	pad_sigma->cd();
	pad_sigma->RedrawAxis();
	pad_sigma->Update();
	//-----------------------------------------------------------
	
	
	
	
	sYTitle = "Events_{BSM}/Events_{#gamma/Z^{0}}";
	pad_weights->cd();
	pad_weights->Draw();
	sName = sMass + " GeV S^{1}/Z_{2} KK";
	ymin = 0.5*getYmin(hWeightsKK);
	hWeightsKK->SetMinimum(ymin);
	hWeightsKK->SetMaximum(1.5*hWeightsKK->GetMaximum());
	hWeightsKK->SetLineColor(col1);
	hWeightsKK->SetLineWidth(2);
	hWeightsKK->SetTitle("");
	hWeightsKK->SetXTitle("#hat{m}_{#mu#mu} GeV");
	hWeightsKK->SetYTitle(sYTitle.c_str());
	if(doLogx) hWeightsKK->GetXaxis()->SetMoreLogLabels(); 
	if(doLogx) hWeightsKK->GetXaxis()->SetMoreLogLabels(); 
	hWeightsKK->Draw();
	leg_weights->AddEntry(hWeightsKK, sName.c_str(), "l");
	
	sName = sMass + " GeV Z' SSM";
	hWeightsZP->SetLineColor(col2);
	hWeightsZP->SetLineWidth(2);
	hWeightsZP->SetTitle("");
	hWeightsZP->SetXTitle("#hat{m}_{#mu#mu} GeV");
	hWeightsZP->SetYTitle(sYTitle.c_str());
	if(doLogx) hWeightsZP->GetXaxis()->SetMoreLogLabels(); 
	if(doLogx) hWeightsZP->GetXaxis()->SetMoreLogLabels(); 
	hWeightsZP->Draw("SAMES");
	leg_weights->AddEntry(hWeightsZP, sName.c_str(), "l");
	
	leg_weights->Draw("SAMES");
	
	pad_weights->cd();
	pad_weights->RedrawAxis();
	pad_weights->Update();
	//-----------------------------------------------------------
	
	
	
	
	sYTitle = "Events";
	pad_recon_template->cd();
	pad_recon_template->Draw();
	
	ymin = 0.5*getYmin(hMassReconZ0);
	hMassReconZ0->SetMinimum(ymin);
	hMassReconZ0->SetMaximum(1.5*hMassReconTemplateKK->GetMaximum()); // !!!
	hMassReconZ0->SetLineColor(col0);
	hMassReconZ0->SetLineWidth(2);
	hMassReconZ0->SetTitle("");
	hMassReconZ0->SetXTitle("#hat{m}_{#mu#mu} GeV");
	hMassReconZ0->SetYTitle(sYTitle.c_str());
	if(doLogx) hMassReconZ0->GetXaxis()->SetMoreLogLabels(); 
	if(doLogx) hMassReconZ0->GetXaxis()->SetMoreLogLabels(); 
	hMassReconZ0->Draw();
	leg_mass_recon->AddEntry(hMassReconZ0, "SM #gamma/Z^{0} (#it{ATLAS} MC10 reconstructed)", "l");
	
	sName = sMass + " GeV S^{1}/Z_{2} KK Template";
	hMassReconTemplateKK->SetLineColor(col1);
	hMassReconTemplateKK->SetLineWidth(2);
	hMassReconTemplateKK->SetTitle("");
	hMassReconTemplateKK->SetXTitle("#hat{m}_{#mu#mu} GeV");
	hMassReconTemplateKK->SetYTitle(sYTitle.c_str());
	if(doLogx) hMassReconTemplateKK->GetXaxis()->SetMoreLogLabels(); 
	if(doLogx) hMassReconTemplateKK->GetXaxis()->SetMoreLogLabels();
	hMassReconTemplateKK->Draw("SAMES");
	leg_mass_recon->AddEntry(hMassReconTemplateKK, sName.c_str(), "l");
	
	sName = sMass + " GeV Z' SSM Template";
	hMassReconTemplateZP->SetLineColor(col2);
	hMassReconTemplateZP->SetLineWidth(2);
	hMassReconTemplateZP->SetTitle("");
	hMassReconTemplateZP->SetXTitle("#hat{m}_{#mu#mu} GeV");
	hMassReconTemplateZP->SetYTitle(sYTitle.c_str());
	if(doLogx) hMassReconTemplateZP->GetXaxis()->SetMoreLogLabels(); 
	if(doLogx) hMassReconTemplateZP->GetXaxis()->SetMoreLogLabels(); 
	hMassReconTemplateZP->Draw("SAMES");
	leg_mass_recon->AddEntry(hMassReconTemplateZP, sName.c_str(), "l");
	
	leg_mass_recon->Draw("SAMES");
	pvtxt_recon->Draw("SAMES");
	
	pad_recon_template->cd();
	pad_recon_template->RedrawAxis();
	pad_recon_template->Update();
	//--------------------------------------------------------------------------
	
	
	
	
	sYTitle = "Events";
	pad_compare->cd();
	pad_compare->Draw();
	
	sName = sMass + " GeV Z' SSM Template";
	ymin = 0.5*getYmin(hMassReconTemplateZP);
	hMassReconTemplateZP->SetMinimum(ymin);
	hMassReconTemplateZP->SetMaximum(1.5*hMassReconTemplateZP->GetMaximum()); // !!!
	hMassReconTemplateZP->SetLineColor(col2);
	hMassReconTemplateZP->SetLineWidth(2);
	hMassReconTemplateZP->SetTitle("");
	hMassReconTemplateZP->SetXTitle("#hat{m}_{#mu#mu} GeV");
	hMassReconTemplateZP->SetYTitle(sYTitle.c_str());
	if(doLogx) hMassReconTemplateZP->GetXaxis()->SetMoreLogLabels(); 
	if(doLogx) hMassReconTemplateZP->GetXaxis()->SetMoreLogLabels(); 
	hMassReconTemplateZP->Draw();
	leg_compare->AddEntry(hMassReconTemplateZP, sName.c_str(), "l");
	
	
	sName = sMass + " GeV Z' SSM (#it{ATLAS} MC10 reconstructed)";
	hMassReconZP->SetLineColor(col5);
	//hMassReconZP->SetLineStyle(2);
	hMassReconZP->SetLineWidth(2);
	hMassReconZP->SetTitle("");
	hMassReconZP->SetXTitle("#hat{m}_{#mu#mu} GeV");
	hMassReconZP->SetYTitle(sYTitle.c_str());
	if(doLogx) hMassReconZP->GetXaxis()->SetMoreLogLabels(); 
	if(doLogx) hMassReconZP->GetXaxis()->SetMoreLogLabels(); 
	hMassReconZP->Draw("SAMES");
	leg_compare->AddEntry(hMassReconZP, sName.c_str(), "l");
	
	leg_compare->Draw("SAMES");
	pvtxt_compare->Draw("SAMES");
	
	pad_compare->cd();
	pad_compare->RedrawAxis();
	pad_compare->Update();
	
	
	
	cnv->Update();
	TString name = "plots/plot_" + fname;
	cnv->SaveAs(name+".eps");
	cnv->SaveAs(name+".C");
	cnv->SaveAs(name+".root");
	cnv->SaveAs(name+".png");
	
	return 0;
}
