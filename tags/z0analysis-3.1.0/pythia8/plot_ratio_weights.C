#include "TROOT.h"
#include "TStyle.h"
#include "TH1.h"
#include "TTree.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TPaveText.h"
#include "TText.h"
#include "kinematics.h"
#include "read.h"

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

static double xmin  = 0.;
static double xmax  = 4000.;
const int     nbins = 200;
static Double_t logMmin;
static Double_t logMmax;
static Double_t logMbinwidth;
static Double_t xbins[nbins+1];

static double lumi = 5.;
static double mb2fb = 1.e12;

vector<string> svNames;
vector<string> svPaths;
vector<TH1D*>  hvBinnedHistos;
vector<double> dvWeights;
vector<Color_t> cvColors;
string sDir  = "/data/hod/pythia8_ntuples/";
string sName = "";

bool doLogx = true;

void clearSamples()
{	
	svNames.clear();
	svPaths.clear();
	for(int n=0 ; n<(int)hvBinnedHistos.size() ; n++)
	{
		if(hvBinnedHistos[n]!=NULL) delete hvBinnedHistos[n];
	}
	hvBinnedHistos.clear();
	dvWeights.clear();
	cvColors.clear();
}

void addSample(string name, Color_t color, double events, double sigma)
{	
	svNames.push_back(name);

	sName = svNames[svNames.size()-1];

	svPaths.push_back(sDir+sName+".root");
	if(doLogx) hvBinnedHistos.push_back(new TH1D(sName.c_str(),sName.c_str(),nbins,xbins));
	else       hvBinnedHistos.push_back(new TH1D(sName.c_str(),sName.c_str(),nbins,xmin,xmax));
	dvWeights.push_back(lumi/(events/(sigma*mb2fb)));
	cvColors.push_back(color);
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
	
	string sModel = "";
	string sMass  = "";
	cout << "chose mass(GeV)...";
	cin >> sMass;
	
	if(sMass=="1000")
	{
		xmin  = 120.;
		xmax  = 4000.;
	}
	if(sMass=="2000")
	{
		xmin  = 120.;
		xmax  = 5000.;
	}
	if(sMass=="3000")
	{
		xmin  = 120.;
		xmax  = 5500.;
	}
	logMmin  = log10(xmin);
	logMmax  = log10(xmax);
	logMbinwidth = (Double_t)( (logMmax-logMmin)/(Double_t)nbins );
	xbins[0] = xmin;
	for(Int_t i=1 ; i<=nbins ; i++) xbins[i] = TMath::Power( 10,(logMmin + i*logMbinwidth) );
	
	
	TString fname = "weights_M" + (TString)sMass;
	
	
	TCanvas* cnv = new TCanvas("cnv", "cnv", 0,0,1200,800);
	cnv->Divide(1,2);
	
	TVirtualPad* pad_sigma = cnv->cd(1);
	pad_sigma->SetLogy();
	if(doLogx) pad_sigma->SetLogx();
	pad_sigma->SetTickx(1);
	pad_sigma->SetTicky(1);
	
	TVirtualPad* pad_weights = cnv->cd(2);
	pad_weights->SetLogy();
	if(doLogx) pad_weights->SetLogx();
	pad_weights->SetTickx(1);
	pad_weights->SetTicky(1);
	
	cnv->cd();
	cnv->Draw();
	
	TLegend* leg_mass = new TLegend(0.1471276,0.1758235,0.4333213,0.4492994,NULL,"brNDC");
	leg_mass->SetFillColor(kWhite);
	
	TLegend* leg_weights = new TLegend(0.1493752,0.649029,0.4348197,0.9255777,NULL,"brNDC");
	leg_weights->SetFillColor(kWhite);
	
	TPaveText* pvtxt = new TPaveText(0.7225119,0.6920477,0.8468788,0.9009956,"brNDC");
	pvtxt->SetFillColor(kWhite);
	TText* txt = pvtxt->AddText( "R = #frac{d#sigma^{BSM}/d#hat{m}_{#mu#mu}}{d#sigma^{#gamma/Z}/d#hat{m}_{#mu#mu}}" );
	//if(sMass!="") txt = pvtxt->AddText( sMass.c_str() );
	
	// combined histos
	TH1D* hSumTmp;
	TH1D* hSumZ0;
	TH1D* hSumZP;
	TH1D* hSumKK;
	TH1D* hWeightsZP;
	TH1D* hWeightsKK;
	if(doLogx)
	{
		hSumTmp = new TH1D("sumTmp","sumTmp",nbins,xbins);
		hSumZ0 = new TH1D("sumZ0","sumZ0",nbins,xbins);
		hSumZP = new TH1D("sumZP","sumZP",nbins,xbins);
		hSumKK = new TH1D("sumKK","sumKK",nbins,xbins);
		hWeightsZP = new TH1D("weightsZP","weightsZP",nbins,xbins);
		hWeightsKK = new TH1D("weightsKK","weightsKK",nbins,xbins);
	}
	else
	{
		hSumTmp = new TH1D("sumTmp","sumTmp",nbins,xmin,xmax);
		hSumZ0 = new TH1D("sumZ0","sumZ0",nbins,xmin,xmax);
		hSumZP = new TH1D("sumZP","sumZP",nbins,xmin,xmax);
		hSumKK = new TH1D("sumKK","sumKK",nbins,xmin,xmax);
		hWeightsZP = new TH1D("weightsZP","weightsZP",nbins,xmin,xmax);
		hWeightsKK = new TH1D("weightsKK","weightsKK",nbins,xmin,xmax);
	}
	
	
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
			addSample("Pythia8_Zmumu_120M500",   col0, nGeneratedEvents, 7.94E-09);
			addSample("Pythia8_Zmumu_500M1000",  col1, nGeneratedEvents, 2.70E-11);
			addSample("Pythia8_Zmumu_1000M1500", col2, nGeneratedEvents, 9.62E-13);
			addSample("Pythia8_Zmumu_1500M2000", col3, nGeneratedEvents, 7.80E-14);
			addSample("Pythia8_Zmumu_2000M0",    col5, nGeneratedEvents, 1.00E-14);
		}
		
		if(model==ZP && sMass=="1000")
		{
			addSample("Pythia8_ZprimeSSM1000mumu_120M500",  col0, nGeneratedEvents, 7.79E-09);
			addSample("Pythia8_ZprimeSSM1000mumu_500M1500", col1, nGeneratedEvents, 1.09E-10);
			addSample("Pythia8_ZprimeSSM1000mumu_1500M0",   col2, nGeneratedEvents, 2.43E-13);
		}
		if(model==ZP && sMass=="2000")
		{
			addSample("Pythia8_ZprimeSSM2000mumu_120M1000",  col0, nGeneratedEvents, 0.);
			addSample("Pythia8_ZprimeSSM2000mumu_1000M3000", col1, nGeneratedEvents, 0.);
			addSample("Pythia8_ZprimeSSM2000mumu_3000M0",    col2, nGeneratedEvents, 0.);
		}
		if(model==ZP && sMass=="3000")
		{
			addSample("Pythia8_ZprimeSSM3000mumu_120M1500",  col0, nGeneratedEvents, 0.);
			addSample("Pythia8_ZprimeSSM3000mumu_1500M4500", col1, nGeneratedEvents, 0.);
			addSample("Pythia8_ZprimeSSM3000mumu_4500M0",    col2, nGeneratedEvents, 0.);
		}
		
		
		if(model==KK && sMass=="1000")
		{
			addSample("Pythia8_ZKK1000mumu_120M500",  col0, nGeneratedEvents, 6.87E-09);
			addSample("Pythia8_ZKK1000mumu_500M1500", col1, nGeneratedEvents, 7.84E-10);
			//addSample("Pythia8_ZKK1000mumu_1500M0",   col2, nGeneratedEvents, 0.);
		}
		if(model==KK && sMass=="2000")
		{
			addSample("Pythia8_ZKK2000mumu_120M1000",  col0, nGeneratedEvents, 0.);
			addSample("Pythia8_ZKK2000mumu_1000M3000", col1, nGeneratedEvents, 0.);
			addSample("Pythia8_ZKK2000mumu_3000M0",    col2, nGeneratedEvents, 0.);
		}
		if(model==KK && sMass=="3000")
		{
			addSample("Pythia8_ZKK3000mumu_120M1500",  col0, nGeneratedEvents, 0.);
			addSample("Pythia8_ZKK3000mumu_1500M4500", col1, nGeneratedEvents, 0.);
			addSample("Pythia8_ZKK3000mumu_4500M0",    col2, nGeneratedEvents, 0.);
		}
		
		// get the data
		ymin = 0.;
		vsize = (int)svPaths.size();
		
		for(int n=vsize-1 ; n>=0 ; n--)
		{
			cout << "svPaths[" << n << "]=" << svPaths[n] << endl;
			file = TFile::Open(svPaths[n].c_str(),"READ");
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
				hvBinnedHistos[n]->Fill(mHat);
			}
			
			////////////////////////////////////////////////////
			hvBinnedHistos[n]->Scale(dvWeights[n]); // scale ///
			////////////////////////////////////////////////////
			
			///////////////////////////////////////////
			hSumTmp->Add(hvBinnedHistos[n]); // sum ///
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
	
	
	string sName = "";
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
	leg_mass->AddEntry(hSumZ0, "SM #gamma/Z^{0}", "l");
	
	sName = sMass + " GeV S^{1}/Z_{2} Kaluza-Klein EDs";
	hSumKK->SetLineColor(col2);
	hSumKK->SetLineWidth(2);
	hSumKK->SetTitle("");
	hSumKK->SetXTitle("#hat{m}_{#mu#mu} GeV");
	hSumKK->SetYTitle("Events");
	if(doLogx) hSumKK->GetXaxis()->SetMoreLogLabels(); 
	if(doLogx) hSumKK->GetXaxis()->SetMoreLogLabels();
	hSumKK->Draw("SAMES");
	leg_mass->AddEntry(hSumKK, sName.c_str(), "l");
	
	sName = sMass + " GeV Z' SSM";
	hSumZP->SetLineColor(col1);
	hSumZP->SetLineWidth(2);
	hSumZP->SetTitle("");
	hSumZP->SetXTitle("#hat{m}_{#mu#mu} GeV");
	hSumZP->SetYTitle("Events");
	if(doLogx) hSumZP->GetXaxis()->SetMoreLogLabels(); 
	if(doLogx) hSumZP->GetXaxis()->SetMoreLogLabels(); 
	hSumZP->Draw("SAMES");
	leg_mass->AddEntry(hSumZP, sName.c_str(), "l");
	
	leg_mass->Draw("SAMES");
	
	pad_sigma->cd();
	pad_sigma->RedrawAxis();
	pad_sigma->Update();
	
	
	
	
	
	sYTitle = "R";
	pad_weights->cd();
	pad_weights->Draw();
	sName = sMass + " GeV S^{1}/Z_{2} Kaluza-Klein EDs";
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
	pvtxt->Draw("SAMES");
	
	pad_weights->cd();
	pad_weights->RedrawAxis();
	pad_weights->Update();
	
	cnv->Update();
	TString name = "plots/plot_" + fname;
	cnv->SaveAs(name+".eps");
	cnv->SaveAs(name+".C");
	cnv->SaveAs(name+".root");
	cnv->SaveAs(name+".png");
	
	return 0;
}
