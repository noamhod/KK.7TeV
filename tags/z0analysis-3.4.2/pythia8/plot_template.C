#include "TROOT.h"
#include "TStyle.h"
#include "TH1.h"
#include "TH2.h"
#include "TTree.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TPaveText.h"
#include "TText.h"
#include "TColor.h"

#include "read.h"
#include "kinematics.h"
#include "asymgraph.h"
#include "smearing.h"
#include "selection.h"

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
const int     nxbins = 100;
static double ymin  = -1.;
static double ymax  = +1.;
const int     nybins = 100;

static Double_t logMmin;
static Double_t logMmax;
static Double_t logMbinwidth;
static Double_t xbins[nxbins+1];

static double lumi = 5.;
static double mb2fb = 1.e12;

vector<string> svNames;
vector<string> svPaths;
vector<TH2D*>  hvBinnedHistos;
vector<double> dvWeights;
vector<Color_t> cvColors;
string sDir  = "/data/hod/pythia8_ntuples/";
string sName = "";

bool doLogx = false;
bool doLogz = false;

TLorentzVector* pa = new TLorentzVector();
TLorentzVector* pb = new TLorentzVector();

///////////////////////////////////////////////////////////////

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
	if(doLogx) hvBinnedHistos.push_back(new TH2D(sName.c_str(),sName.c_str(),nxbins,xbins, nybins,ymin,ymax));
	else       hvBinnedHistos.push_back(new TH2D(sName.c_str(),sName.c_str(),nxbins,xmin,xmax, nybins,ymin,ymax));
	dvWeights.push_back(lumi/(events/(sigma*mb2fb)));
	cvColors.push_back(color);
}

double getYmin(TH2D* h)
{
	double min = 1.e20;
	double binval = 0.;
	for(int bx=1 ; bx<=h->GetNbinsX() ; bx++)
	{
		for(int by=1 ; by<=h->GetNbinsY() ; by++)
		{	
			binval = h->GetBinContent(bx,by);
			min = (binval<min  &&  binval>0.) ? binval : min;
		}
	}
	return min;
}

int plot_template()
{
	gStyle->SetOptStat(0);
	gStyle->SetPalette(1);
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
	
	/*
	const Int_t Number = 5;
	Double_t Red[Number] = { 0.00, 0.09, 0.18, 0.09, 0.00 };
	Double_t Green[Number] = { 0.01, 0.02, 0.39, 0.68, 0.97 };
	Double_t Blue[Number] = { 0.17, 0.39, 0.62, 0.79, 0.97 };
	Double_t Stops[Number] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
	Int_t nb=100;
	TColor::CreateGradientColorTable(Number,Stops,Red,Green,Blue,nb);
	*/
	
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
	

	logMmin  = log10(xmin);
	logMmax  = log10(xmax);
	logMbinwidth = (Double_t)( (logMmax-logMmin)/(Double_t)nxbins );
	xbins[0] = xmin;
	for(Int_t i=1 ; i<=nxbins ; i++) xbins[i] = TMath::Power( 10,(logMmin + i*logMbinwidth) );
	
	
	TString fname = "template_M" + (TString)sMass;
	
	
	TCanvas* cnv = new TCanvas("cnv", "cnv", 0,0,1200,800);
	cnv->Divide(2,2);
	
	TVirtualPad* pad_sigma_KK = cnv->cd(1);
	if(doLogz) pad_sigma_KK->SetLogz();
	if(doLogx) pad_sigma_KK->SetLogx();
	pad_sigma_KK->SetTickx(1);
	pad_sigma_KK->SetTicky(1);
	
	TVirtualPad* pad_sigma_ZP = cnv->cd(2);
	if(doLogz) pad_sigma_ZP->SetLogz();
	if(doLogx) pad_sigma_ZP->SetLogx();
	pad_sigma_ZP->SetTickx(1);
	pad_sigma_ZP->SetTicky(1);
	
	TVirtualPad* pad_weights_KK = cnv->cd(3);
	if(doLogz) pad_weights_KK->SetLogz();
	if(doLogx) pad_weights_KK->SetLogx();
	pad_weights_KK->SetTickx(1);
	pad_weights_KK->SetTicky(1);
	
	TVirtualPad* pad_weights_ZP = cnv->cd(4);
	if(doLogz) pad_weights_ZP->SetLogz();
	if(doLogx) pad_weights_ZP->SetLogx();
	pad_weights_ZP->SetTickx(1);
	pad_weights_ZP->SetTicky(1);
	
	cnv->cd();
	cnv->Draw();
	
	TLegend* leg_mass = new TLegend(0.1471276,0.1758235,0.4333213,0.4492994,NULL,"brNDC");
	leg_mass->SetFillColor(kWhite);
	
	TLegend* leg_weights = new TLegend(0.1493752,0.649029,0.4348197,0.9255777,NULL,"brNDC");
	leg_weights->SetFillColor(kWhite);
	
	TPaveText* pvtxt = new TPaveText(0.1459286,0.4811097,0.3873797,0.683506,"brNDC");
	pvtxt->SetFillColor(kWhite);
	TText* txt = pvtxt->AddText( "#splitline{Sum of binned samples}{normalized to ~5 fb^{-1}}" );
	//if(sMass!="") txt = pvtxt->AddText( ("m_{BSM}="+sMass+" GeV").c_str() );
	
	// combined histos
	TH2D* hSumTmp;
	TH2D* hSumZ0;
	TH2D* hSumZP;
	TH2D* hSumKK;
	TH2D* hWeightsZP;
	TH2D* hWeightsKK;
	if(doLogx)
	{
		hSumTmp = new TH2D("sumTmp","sumTmp",nxbins,xbins, nybins,ymin,ymax);
		hSumZ0 = new TH2D("sumZ0","sumZ0",nxbins,xbins, nybins,ymin,ymax);
		hSumZP = new TH2D("sumZP","sumZP",nxbins,xbins, nybins,ymin,ymax);
		hSumKK = new TH2D("sumKK","sumKK",nxbins,xbins, nybins,ymin,ymax);
		hWeightsZP = new TH2D("weightsZP","weightsZP",nxbins,xbins, nybins,ymin,ymax);
		hWeightsKK = new TH2D("weightsKK","weightsKK",nxbins,xbins, nybins,ymin,ymax);
	}
	else
	{
		hSumTmp = new TH2D("sumTmp","sumTmp",nxbins,xmin,xmax, nybins,ymin,ymax);
		hSumZ0 = new TH2D("sumZ0","sumZ0",nxbins,xmin,xmax, nybins,ymin,ymax);
		hSumZP = new TH2D("sumZP","sumZP",nxbins,xmin,xmax, nybins,ymin,ymax);
		hSumKK = new TH2D("sumKK","sumKK",nxbins,xmin,xmax, nybins,ymin,ymax);
		hWeightsZP = new TH2D("weightsZP","weightsZP",nxbins,xmin,xmax, nybins,ymin,ymax);
		hWeightsKK = new TH2D("weightsKK","weightsKK",nxbins,xmin,xmax, nybins,ymin,ymax);
	}
	
	
	///////////////////////////////////
	double nGeneratedEvents = 5e5; ////
	///////////////////////////////////
	
	TFile* file;
	TTree* tree;
	double ymintmp  = 0.;
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
			addSample("Pythia8_Zmumu_120M500",   col0, nGeneratedEvents, 7.93603E-09);
			addSample("Pythia8_Zmumu_500M1000",  col1, nGeneratedEvents, 2.70151E-11);
			addSample("Pythia8_Zmumu_1000M1500", col2, nGeneratedEvents, 9.61583E-13);
			addSample("Pythia8_Zmumu_1500M2000", col3, nGeneratedEvents, 7.84575E-14);
			addSample("Pythia8_Zmumu_2000M0",    col5, nGeneratedEvents, 9.56113E-15);
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
		ymintmp = 0.;
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
				hvBinnedHistos[n]->Fill(mHat,cosThetaCS);
			}
			
			////////////////////////////////////////////////////
			hvBinnedHistos[n]->Scale(dvWeights[n]); // scale ///
			////////////////////////////////////////////////////
			
			///////////////////////////////////////////
			hSumTmp->Add(hvBinnedHistos[n]); // sum ///
			///////////////////////////////////////////
			
			file->Close();
		}
		
		if(model==Z0) hSumZ0 = (TH2D*)hSumTmp->Clone("");
		if(model==ZP) hSumZP = (TH2D*)hSumTmp->Clone("");
		if(model==KK) hSumKK = (TH2D*)hSumTmp->Clone("");
	}
	
	
	/////////////////////////////////////////////////
	// The ratios ///////////////////////////////////
	hWeightsZP = (TH2D*)hSumZP->Clone(""); //////////
	hWeightsZP->Divide(hSumZ0); /////////////////////
	hWeightsKK = (TH2D*)hSumKK->Clone(""); //////////
	hWeightsKK->Divide(hSumZ0); /////////////////////
	/////////////////////////////////////////////////
	
	
	string sYTitle = "";
	
	/*
	pad_sigma_KK->cd();
	pad_sigma_KK->Draw();
	y = 0.5*getYmin(hSumZ0);
	hSumZ0->SetMinimum(y);
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
	*/
	
	sName = sMass + " GeV S^{1}/Z_{2} Kaluza-Klein EDs";
	pad_sigma_KK->cd();
	pad_sigma_KK->Draw();
	//ymintmp = 0.5*getYmin(hSumKK);
	//hSumKK->SetMinimum(ymintmp);
	//hSumKK->SetMaximum(1.5*hSumKK->GetMaximum());
	hSumKK->SetLineColor(col1);
	hSumKK->SetLineWidth(2);
	hSumKK->SetTitle("");
	hSumKK->SetXTitle("#hat{m}_{#mu#mu} GeV");
	hSumKK->SetYTitle("cos(#theta*)");
	hSumKK->SetZTitle("Events");
	if(doLogx) hSumKK->GetXaxis()->SetMoreLogLabels(); 
	if(doLogx) hSumKK->GetXaxis()->SetMoreLogLabels();
	hSumKK->Draw("SURF2");
	//hSumKK->SetContour(nb);
	//hSumKK->Draw("surf1z");
	leg_mass->AddEntry(hSumKK, sName.c_str(), "l");
	pad_sigma_KK->cd();
	pad_sigma_KK->RedrawAxis();
	pad_sigma_KK->Update();
	
	sName = sMass + " GeV Z' SSM";
	pad_sigma_ZP->cd();
	pad_sigma_ZP->Draw();
	//ymintmp = 0.5*getYmin(hSumZP);
	//hSumZP->SetMinimum(ymintmp);
	//hSumZP->SetMaximum(1.5*hSumZP->GetMaximum());
	hSumZP->SetLineColor(col2);
	hSumZP->SetLineWidth(2);
	hSumZP->SetTitle("");
	hSumZP->SetXTitle("#hat{m}_{#mu#mu} GeV");
	hSumZP->SetYTitle("cos(#theta*)");
	hSumZP->SetZTitle("Events");
	if(doLogx) hSumZP->GetXaxis()->SetMoreLogLabels(); 
	if(doLogx) hSumZP->GetXaxis()->SetMoreLogLabels(); 
	hSumZP->Draw("SURF2");
	//hSumZP->SetContour(nb);
	//hSumZP->Draw("surf1z");
	leg_mass->AddEntry(hSumZP, sName.c_str(), "l");
	pad_sigma_ZP->cd();
	pad_sigma_ZP->RedrawAxis();
	pad_sigma_ZP->Update();
	
	//leg_mass->Draw("SAMES");
	//pvtxt->Draw("SAMES");

	
	
	
	
	
	sYTitle = "Events_{BSM}/Events_{#gamma/Z^{0}}";
	sName = sMass + " GeV S^{1}/Z_{2} Kaluza-Klein EDs";
	pad_weights_KK->cd();
	pad_weights_KK->Draw();
	//ymintmp = 0.5*getYmin(hWeightsKK);
	//hWeightsKK->SetMinimum(ymintmp);
	//hWeightsKK->SetMaximum(1.5*hWeightsKK->GetMaximum());
	hWeightsKK->SetLineColor(col1);
	hWeightsKK->SetLineWidth(2);
	hWeightsKK->SetTitle("");
	hWeightsKK->SetXTitle("#hat{m}_{#mu#mu} GeV");
	hWeightsKK->SetYTitle("cos(#theta*)");
	hWeightsKK->SetZTitle(sYTitle.c_str());
	if(doLogx) hWeightsKK->GetXaxis()->SetMoreLogLabels(); 
	if(doLogx) hWeightsKK->GetXaxis()->SetMoreLogLabels(); 
	hWeightsKK->Draw("SURF2");
	//hWeightsKK->SetContour(nb);
	//hWeightsKK->Draw("surf1z");
	leg_weights->AddEntry(hWeightsKK, sName.c_str(), "l");
	pad_weights_KK->cd();
	pad_weights_KK->RedrawAxis();
	pad_weights_KK->Update();
	
	sName = sMass + " GeV Z' SSM";
	sName = sMass + " GeV S^{1}/Z_{2} Kaluza-Klein EDs";
	pad_weights_ZP->cd();
	pad_weights_ZP->Draw();
	//ymintmp = 0.5*getYmin(hWeightsZP);
	//hWeightsZP->SetMinimum(ymintmp);
	//hWeightsZP->SetMaximum(1.5*hWeightsZP->GetMaximum());
	hWeightsZP->SetLineColor(col2);
	hWeightsZP->SetLineWidth(2);
	hWeightsZP->SetTitle("");
	hWeightsZP->SetXTitle("#hat{m}_{#mu#mu} GeV");
	hWeightsZP->SetYTitle("cos(#theta*)");
	hWeightsZP->SetZTitle(sYTitle.c_str());
	if(doLogx) hWeightsZP->GetXaxis()->SetMoreLogLabels(); 
	if(doLogx) hWeightsZP->GetXaxis()->SetMoreLogLabels(); 
	hWeightsZP->Draw("SURF2");
	//hWeightsZP->SetContour(nb);
	//hWeightsZP->Draw("surf1z");
	leg_weights->AddEntry(hWeightsZP, sName.c_str(), "l");
	pad_weights_ZP->cd();
	pad_weights_ZP->RedrawAxis();
	pad_weights_ZP->Update();
	
	//leg_weights->Draw("SAMES");
	
	cnv->Update();
	TString name = "plots/plot_" + fname;
	cnv->SaveAs(name+".eps");
	cnv->SaveAs(name+".C");
	cnv->SaveAs(name+".root");
	cnv->SaveAs(name+".png");
	
	return 0;
}
