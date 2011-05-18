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
	Z0,
	ZP,
	KK
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

static double xmin  = 120.;
static double xmax  = 5000.;
const int     nxbins = 200;
static Double_t logMmin;
static Double_t logMmax;
static Double_t logMbinwidth;
static Double_t xbins[nxbins+1];

static double lumi = 5.;
static double mb2fb = 1.e12;
static double nb2mb = 1.e-6;

vector<string> svNames;
vector<string> svPaths;
vector<TH1D*>  hvBinnedHistos_imass;
vector<TH1D*>  hvBinnedHistos_imassRes;
vector<double> dvWeights;
vector<Color_t> cvColors;
string sDir  = "/data/hod/pythia8_ntuples/";
string sName = "";

bool doLogx = true;

double sumSigma = 0.;

void clearSamples()
{	
	svNames.clear();
	svPaths.clear();
	for(int n=0 ; n<(int)hvBinnedHistos_imass.size() ; n++)
	{
		if(hvBinnedHistos_imass[n]!=NULL) delete hvBinnedHistos_imass[n];
		if(hvBinnedHistos_imassRes[n]!=NULL) delete hvBinnedHistos_imassRes[n];
	}
	hvBinnedHistos_imass.clear();
	hvBinnedHistos_imassRes.clear();
	dvWeights.clear();
	cvColors.clear();
}

void addSample(string name, Color_t color, double events, double sigma, bool calcSumSigma=false)
{	
	svNames.push_back(name);

	sName = svNames[svNames.size()-1];

	svPaths.push_back(sDir+sName+".root");
	
	if(doLogx) hvBinnedHistos_imass.push_back(new TH1D(sName.c_str(),sName.c_str(),nxbins,xbins));
	else       hvBinnedHistos_imass.push_back(new TH1D(sName.c_str(),sName.c_str(),nxbins,xmin,xmax));
	
	hvBinnedHistos_imassRes.push_back(new TH1D((sName+"Res").c_str(),(sName+"Res").c_str(),nxbins,-0.2,+0.2));
	
	dvWeights.push_back(lumi/(events/(sigma*mb2fb)));
	cvColors.push_back(color);
	
	if(calcSumSigma) sumSigma += sigma;
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
	
	// combined histos
	TH1D* hSumTmp;
	TH1D* hResTmp;
	TH1D* hSumZ0;
	TH1D* hSumZP;
	TH1D* hSumKK;
	TH1D* hWeightsZP;
	TH1D* hWeightsKK;
	TH1D* hReconZ0;
	TH1D* hReconZP;
	TH1D* hReconTemplateZP;
	TH1D* hReconTemplateKK;
	TH1D* hResReconZ0;
	TH1D* hResReconZP;
	TH1D* hResTemplateZP;
	TH1D* hResTemplateKK;
	if(doLogx)
	{
		hSumTmp = new TH1D("sumTmp","sumTmp",nxbins,xbins);
		hSumZ0 = new TH1D("sumZ0","sumZ0",nxbins,xbins);
		hSumZP = new TH1D("sumZP","sumZP",nxbins,xbins);
		hSumKK = new TH1D("sumKK","sumKK",nxbins,xbins);
		hWeightsZP = new TH1D("weightsZP","weightsZP",nxbins,xbins);
		hWeightsKK = new TH1D("weightsKK","weightsKK",nxbins,xbins);
		
		hReconZ0 = new TH1D("ReconZ0","ReconZ0",nxbins,xbins);
		hReconZP = new TH1D("ReconZP","ReconZP",nxbins,xbins);
		hReconTemplateZP = new TH1D("ReconTemplateZP","ReconTemplateZP",nxbins,xbins);
		hReconTemplateKK = new TH1D("ReconTemplateKK","ReconTemplateKK",nxbins,xbins);
	}
	else
	{
		hSumTmp = new TH1D("sumTmp","sumTmp",nxbins,xmin,xmax);
		hSumZ0 = new TH1D("sumZ0","sumZ0",nxbins,xmin,xmax);
		hSumZP = new TH1D("sumZP","sumZP",nxbins,xmin,xmax);
		hSumKK = new TH1D("sumKK","sumKK",nxbins,xmin,xmax);
		hWeightsZP = new TH1D("weightsZP","weightsZP",nxbins,xmin,xmax);
		hWeightsKK = new TH1D("weightsKK","weightsKK",nxbins,xmin,xmax);
		
		hReconZ0 = new TH1D("ReconZ0","ReconZ0",nxbins,xmin,xmax);
		hReconZP = new TH1D("ReconZP","ReconZP",nxbins,xmin,xmax);
		hReconTemplateZP = new TH1D("ReconTemplateZP","ReconTemplateZP",nxbins,xmin,xmax);
		hReconTemplateKK = new TH1D("ReconTemplateKK","ReconTemplateKK",nxbins,xmin,xmax);
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
		if(doLogx) hSumTmp->Reset(); //////////
		else { for(Int_t b=0 ; b<=hSumTmp->GetNbinsX() ; b++) hSumTmp->SetBinContent(b,0.); }
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
				
				for(Int_t i=0 ; i<tree->GetEntries() ; i++)
				{
					tree->GetEntry(i);
					
					if(truth_all_isValid)
					{
						hvBinnedHistos_imass[n]->Fill(truth_all_Mhat);
					}
				}
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
				}
			}
			
			////////////////////////////////////////////////////
			hvBinnedHistos_imass[n]->Scale(dvWeights[n]); // scale ///
			////////////////////////////////////////////////////
			
			///////////////////////////////////////////
			hSumTmp->Add(hvBinnedHistos_imass[n]); // sum ///
			///////////////////////////////////////////
			
			file->Close();
		}
		
		if(model==Z0) hSumZ0 = (TH1D*)hSumTmp->Clone("");
		if(model==ZP) hSumZP = (TH1D*)hSumTmp->Clone("");
		if(model==KK) hSumKK = (TH1D*)hSumTmp->Clone("");
	}
	
	
	/////////////////////////////////////////////////
	// The ratios ///////////////////////////////////
	hWeightsZP = (TH1D*)hSumZP->Clone(""); //////////
	hWeightsZP->Divide(hSumZ0); /////////////////////
	hWeightsKK = (TH1D*)hSumKK->Clone(""); //////////
	hWeightsKK->Divide(hSumZ0); /////////////////////
	/////////////////////////////////////////////////
	cout << "Weights are calculated\n" << endl;
	//-------------------------------------------------------------------------------------
	
	
	
	
	bool calcSumSigma = true;
	for(int model=Z0 ; model<=KK ; model++)
	{
		////////////////////////////
		// reset all ///////////////
		clearSamples(); ////////////
		if(doLogx) hSumTmp->Reset(); //////////
		else { for(Int_t b=0 ; b<=hSumTmp->GetNbinsX() ; b++) hSumTmp->SetBinContent(b,0.); }
		hResTmp->Reset();
		////////////////////////////
	
		addSample("ATLASZ0/mcLocalControl_DYmumu_120M250",   col0, 19999, 0.0086861*nb2mb, calcSumSigma);
		addSample("ATLASZ0/mcLocalControl_DYmumu_250M400",   col1, 19996, 0.00041431*nb2mb, calcSumSigma);
		addSample("ATLASZ0/mcLocalControl_DYmumu_400M600",   col2, 19993, 0.000067464*nb2mb, calcSumSigma);
		addSample("ATLASZ0/mcLocalControl_DYmumu_600M800",   col3, 15994, 0.000011168*nb2mb, calcSumSigma);
		addSample("ATLASZ0/mcLocalControl_DYmumu_800M1000",  col5, 19992, 0.0000027277*nb2mb, calcSumSigma);
		addSample("ATLASZ0/mcLocalControl_DYmumu_1000M1250", col5, 19995, 0.00000091646*nb2mb, calcSumSigma);
		addSample("ATLASZ0/mcLocalControl_DYmumu_1250M1500", col5, 19993, 0.00000024942*nb2mb, calcSumSigma);
		addSample("ATLASZ0/mcLocalControl_DYmumu_1500M1750", col5, 19997, 0.000000076876*nb2mb, calcSumSigma);
		addSample("ATLASZ0/mcLocalControl_DYmumu_1750M2000", col5, 19993, 0.000000026003*nb2mb, calcSumSigma);
		addSample("ATLASZ0/mcLocalControl_DYmumu_M2000",     col5, 19996, 0.000000015327*nb2mb, calcSumSigma);
			
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
			hSumTmp->Add(hvBinnedHistos_imass[n]); // sum //////
			hResTmp->Add(hvBinnedHistos_imassRes[n]); // sum ///
			////////////////////////////////////////////////////
			
			file->Close();
		}
		
		if(model==Z0) hReconZ0         = (TH1D*)hSumTmp->Clone("");
		if(model==ZP) hReconTemplateZP = (TH1D*)hSumTmp->Clone("");
		if(model==KK) hReconTemplateKK = (TH1D*)hSumTmp->Clone("");
		
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
	if(doLogx) hSumTmp->Reset(); //////////
	else { for(Int_t b=0 ; b<=hSumTmp->GetNbinsX() ; b++) hSumTmp->SetBinContent(b,0.); }
	hResTmp->Reset();
	////////////////////////////
	
	addSample("ATLASZP/mcLocalControl_Zprime_mumu_SSM1000",  col2, 18996, 0.00012973*nb2mb, calcSumSigma);
	
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
		hSumTmp->Add(hvBinnedHistos_imass[n]); // sum //////
		hResTmp->Add(hvBinnedHistos_imassRes[n]); // sum ///
		////////////////////////////////////////////////////

		file->Close();
		hReconZP    = (TH1D*)hSumTmp->Clone("");
		hResReconZP = (TH1D*)hResTmp->Clone("");
	}
	cout << "Templates are ready\n" << endl;
	//-----------------------------------------------------------------------------
	
	


	
	
	
	string sYTitle = "";
	
	
	pad_sigma->cd();
	pad_sigma->Draw();
	ymin = 0.5*getYmin(hSumZ0);
	hSumZ0->SetMinimum(ymin);
	hSumZ0->SetMaximum(1.5*hSumZ0->GetMaximum());
	hSumZ0->SetLineColor(col0);
	hSumZ0->SetLineWidth(2);
	hSumZ0->SetTitle("");
	hSumZ0->SetXTitle("#hat{m}_{#mu#mu} GeV");
	hSumZ0->SetYTitle("Events");
	if(doLogx) hSumZ0->GetXaxis()->SetMoreLogLabels(); 
	if(doLogx) hSumZ0->GetXaxis()->SetMoreLogLabels(); 
	hSumZ0->Draw();
	//leg_mass->AddEntry(hSumZ0, "SM #gamma/Z^{0}", "l");
	leg_mass->AddEntry(hSumZ0, "SM #gamma/Z^{0} (#it{ATLAS} MC10 truth)", "l");
	
	sName = sMass + " GeV S^{1}/Z_{2} KK (#scale[1.1]{P}#scale[0.9]{YTHIA8})";
	hSumKK->SetLineColor(col1);
	hSumKK->SetLineWidth(2);
	hSumKK->SetTitle("");
	hSumKK->SetXTitle("#hat{m}_{#mu#mu} GeV");
	hSumKK->SetYTitle("Events");
	if(doLogx) hSumKK->GetXaxis()->SetMoreLogLabels(); 
	if(doLogx) hSumKK->GetXaxis()->SetMoreLogLabels();
	hSumKK->Draw("SAMES");
	leg_mass->AddEntry(hSumKK, sName.c_str(), "l");
	
	sName = sMass + " GeV Z' SSM (#scale[1.1]{P}#scale[0.9]{YTHIA8})";
	hSumZP->SetLineColor(col2);
	hSumZP->SetLineWidth(2);
	hSumZP->SetTitle("");
	hSumZP->SetXTitle("#hat{m}_{#mu#mu} GeV");
	hSumZP->SetYTitle("Events");
	if(doLogx) hSumZP->GetXaxis()->SetMoreLogLabels(); 
	if(doLogx) hSumZP->GetXaxis()->SetMoreLogLabels(); 
	hSumZP->Draw("SAMES");
	leg_mass->AddEntry(hSumZP, sName.c_str(), "l");
	
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
	
	ymin = 0.5*getYmin(hReconZ0);
	hReconZ0->SetMinimum(ymin);
	hReconZ0->SetMaximum(1.5*hReconTemplateKK->GetMaximum()); // !!!
	hReconZ0->SetLineColor(col0);
	hReconZ0->SetLineWidth(2);
	hReconZ0->SetTitle("");
	hReconZ0->SetXTitle("#hat{m}_{#mu#mu} GeV");
	hReconZ0->SetYTitle(sYTitle.c_str());
	if(doLogx) hReconZ0->GetXaxis()->SetMoreLogLabels(); 
	if(doLogx) hReconZ0->GetXaxis()->SetMoreLogLabels(); 
	hReconZ0->Draw();
	leg_mass_recon->AddEntry(hReconZ0, "SM #gamma/Z^{0} (#it{ATLAS} MC10 reconstructed)", "l");
	
	sName = sMass + " GeV S^{1}/Z_{2} KK Template";
	hReconTemplateKK->SetLineColor(col1);
	hReconTemplateKK->SetLineWidth(2);
	hReconTemplateKK->SetTitle("");
	hReconTemplateKK->SetXTitle("#hat{m}_{#mu#mu} GeV");
	hReconTemplateKK->SetYTitle(sYTitle.c_str());
	if(doLogx) hReconTemplateKK->GetXaxis()->SetMoreLogLabels(); 
	if(doLogx) hReconTemplateKK->GetXaxis()->SetMoreLogLabels();
	hReconTemplateKK->Draw("SAMES");
	leg_mass_recon->AddEntry(hReconTemplateKK, sName.c_str(), "l");
	
	sName = sMass + " GeV Z' SSM Template";
	hReconTemplateZP->SetLineColor(col2);
	hReconTemplateZP->SetLineWidth(2);
	hReconTemplateZP->SetTitle("");
	hReconTemplateZP->SetXTitle("#hat{m}_{#mu#mu} GeV");
	hReconTemplateZP->SetYTitle(sYTitle.c_str());
	if(doLogx) hReconTemplateZP->GetXaxis()->SetMoreLogLabels(); 
	if(doLogx) hReconTemplateZP->GetXaxis()->SetMoreLogLabels(); 
	hReconTemplateZP->Draw("SAMES");
	leg_mass_recon->AddEntry(hReconTemplateZP, sName.c_str(), "l");
	
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
	ymin = 0.5*getYmin(hReconTemplateZP);
	hReconTemplateZP->SetMinimum(ymin);
	hReconTemplateZP->SetMaximum(1.5*hReconTemplateZP->GetMaximum()); // !!!
	hReconTemplateZP->SetLineColor(col2);
	hReconTemplateZP->SetLineWidth(2);
	hReconTemplateZP->SetTitle("");
	hReconTemplateZP->SetXTitle("#hat{m}_{#mu#mu} GeV");
	hReconTemplateZP->SetYTitle(sYTitle.c_str());
	if(doLogx) hReconTemplateZP->GetXaxis()->SetMoreLogLabels(); 
	if(doLogx) hReconTemplateZP->GetXaxis()->SetMoreLogLabels(); 
	hReconTemplateZP->Draw();
	leg_compare->AddEntry(hReconTemplateZP, sName.c_str(), "l");
	
	
	sName = sMass + " GeV Z' SSM (#it{ATLAS} MC10 reconstructed)";
	hReconZP->SetLineColor(col5);
	//hReconZP->SetLineStyle(2);
	hReconZP->SetLineWidth(2);
	hReconZP->SetTitle("");
	hReconZP->SetXTitle("#hat{m}_{#mu#mu} GeV");
	hReconZP->SetYTitle(sYTitle.c_str());
	if(doLogx) hReconZP->GetXaxis()->SetMoreLogLabels(); 
	if(doLogx) hReconZP->GetXaxis()->SetMoreLogLabels(); 
	hReconZP->Draw("SAMES");
	leg_compare->AddEntry(hReconZP, sName.c_str(), "l");
	
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
