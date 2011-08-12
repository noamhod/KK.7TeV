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
static double nbins = 200;
static double lumi = 5.;
static double mb2fb = 1.e12;

vector<string> svNames;
vector<string> svPaths;
vector<TH1D*>  hvBinnedHistos;
vector<double> dvWeights;
vector<Color_t> cvColors;
string sDir  = "/data/hod/pythia8_ntuples/";
string sName = "";

void addSample(string name, Color_t color, double events, double sigma)
{	
	svNames.push_back(name);

	sName = svNames[svNames.size()-1];

	svPaths.push_back(sDir+sName+".root");
	hvBinnedHistos.push_back(new TH1D(sName.c_str(),sName.c_str(),nbins,xmin,xmax));
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

int plot_binned_samples_new()
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
	
	cout << "chose model Z0/ZP/KK...";
	cin >> sModel;
	if(sModel!="Z0" && sModel!="ZP" && sModel!="KK") { cout << "unsupported model" << endl; exit(-1); }
	if(sModel=="ZP" || sModel=="KK")
	{
		cout << "chose mass(GeV)...";
		cin >> sMass;
	}
	
	if(sMass=="1000")
	{
		xmin  = 0.;
		xmax  = 4000.;
		nbins = 200;
	}
	if(sMass=="2000")
	{
		xmin  = 0.;
		xmax  = 5000.;
		nbins = 250;
	}
	if(sMass=="3000")
	{
		xmin  = 0.;
		xmax  = 5500.;
		nbins = 300;
	}
	
	
	TString fname = (TString)sModel + (TString)sMass;

	double nGeneratedEvents = 5e5;
	
	
	if(sModel=="Z0")
	{
		addSample("Pythia8_Zmumu_120M500",   col0, nGeneratedEvents, 7.93603e-09);
		addSample("Pythia8_Zmumu_500M1000",  col1, nGeneratedEvents, 2.70151e-11);
		addSample("Pythia8_Zmumu_1000M1500", col2, nGeneratedEvents, 9.61583e-13);
		addSample("Pythia8_Zmumu_1500M2000", col3, nGeneratedEvents, 7.84575e-14);
		addSample("Pythia8_Zmumu_2000M0",    col5, nGeneratedEvents, 9.56113e-15);
	}
	
	if(sModel=="ZP" && sMass=="1000")
	{
		addSample("Pythia8_ZprimeSSM1000mumu_120M500",  col0, nGeneratedEvents, 7.78812e-09);
		addSample("Pythia8_ZprimeSSM1000mumu_500M1500", col1, nGeneratedEvents, 1.08535e-10);
		addSample("Pythia8_ZprimeSSM1000mumu_1500M0",   col2, nGeneratedEvents, 2.42594e-13);
	}
	if(sModel=="ZP" && sMass=="2000")
	{
		addSample("Pythia8_ZprimeSSM2000mumu_120M1000",  col0, nGeneratedEvents, 7.91467e-09);
		addSample("Pythia8_ZprimeSSM2000mumu_1000M3000", col1, nGeneratedEvents, 1.94433e-12);
		addSample("Pythia8_ZprimeSSM2000mumu_3000M0",    col2, nGeneratedEvents, 3.27844e-16);
	}
	if(sModel=="ZP" && sMass=="3000")
	{
		addSample("Pythia8_ZprimeSSM3000mumu_120M1500",  col0, nGeneratedEvents, 7.94181E-09);
		addSample("Pythia8_ZprimeSSM3000mumu_1500M4500", col1, nGeneratedEvents, 8.9226E-14);
		addSample("Pythia8_ZprimeSSM3000mumu_4500M0",    col2, nGeneratedEvents, 1.18978E-19);
	}
	
	
	if(sModel=="KK" && sMass=="1000")
	{
		addSample("Pythia8_ZKK1000mumu_120M500",  col0, nGeneratedEvents, 6.87332e-09);
		addSample("Pythia8_ZKK1000mumu_500M1500", col1, nGeneratedEvents, 7.83954e-10);
		addSample("Pythia8_ZKK1000mumu_1500M0",   col2, nGeneratedEvents, 1.11827e-11);
	}
	if(sModel=="KK" && sMass=="2000")
	{
		addSample("Pythia8_ZKK2000mumu_120M1000",  col0, nGeneratedEvents, 7.68181e-09);
		addSample("Pythia8_ZKK2000mumu_1000M3000", col1, nGeneratedEvents, 1.22497e-11);
		addSample("Pythia8_ZKK2000mumu_3000M0",    col2, nGeneratedEvents, 3.44554e-15);
	}
	if(sModel=="KK" && sMass=="3000")
	{
		addSample("Pythia8_ZKK3000mumu_120M1500",  col0, nGeneratedEvents, 7.8351E-09);
		addSample("Pythia8_ZKK3000mumu_1500M4500", col1, nGeneratedEvents, 2.98849E-13);
		addSample("Pythia8_ZKK3000mumu_4500M0",    col2, nGeneratedEvents, 7.56956E-20);
	}
	
	
	
	if(sModel=="Z0")
	{
		sModel = "SM #gamma/Z^{0}";
	}
	if(sModel=="ZP")
	{
		sModel = "Z' SSM";
		sMass  = "m_{Z'} = " + sMass + " GeV";
	}
	if(sModel=="KK")
	{
		sModel = "S^{1}/Z_{2} Kaluza-Klein EDs";
		sMass  = "m_{KK} = " + sMass + " GeV";
	}
	
	
	TCanvas* cnv = new TCanvas("cnv", "cnv", 0,0,1200,800);
	cnv->Divide(1,2);
	
	TVirtualPad* pad_bin = cnv->cd(1);
	pad_bin->SetLogy();
	pad_bin->SetTickx(1);
	pad_bin->SetTicky(1);
	
	TVirtualPad* pad_sum = cnv->cd(2);
	pad_sum->SetLogy();
	pad_sum->SetTickx(1);
	pad_sum->SetTicky(1);
	
	cnv->cd();
	cnv->Draw();
	
	TLegend* leg = new TLegend(0.5852843,0.6619171,0.8712375,0.9378238,NULL,"brNDC");
	leg->SetFillColor(kWhite);
	
	TPaveText* pvtxt_bin = new TPaveText(0.3469814,0.7266839,0.5600992,0.8805052,"brNDC");
	pvtxt_bin->SetFillColor(kWhite);
	TText* txt = pvtxt_bin->AddText( sModel.c_str() );
	if(sMass!="") txt = pvtxt_bin->AddText( sMass.c_str() );
	
	TPaveText* pvtxt_sum = new TPaveText(0.6112475,0.7077936,0.8524969,0.91019,"brNDC");
	pvtxt_sum->SetFillColor(kWhite);
	txt = pvtxt_sum->AddText( "#splitline{Sum of binned samples}{normalized to ~5 fb^{-1}}" );
	
	// combined histos
	TH1D* hSum = new TH1D("sum","sum",nbins,xmin,xmax);
	
	
	
	// get the data
	TFile* file;
	TTree* tree;
	double ymin = 0.;
	int vsize = (int)svPaths.size();
	
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
		
		
		leg->AddEntry(hvBinnedHistos[n], svNames[n].c_str(), "l");
		hvBinnedHistos[n]->SetLineColor(cvColors[n]);
		hvBinnedHistos[n]->SetLineWidth(2);
		hvBinnedHistos[n]->SetTitle("");
		
		////////////////////////////////////////////////////
		hvBinnedHistos[n]->Scale(dvWeights[n]); // scale ///
		////////////////////////////////////////////////////
		
		if(n==vsize-1)
		{
			pad_bin->cd();
			pad_bin->Draw();
			ymin = 0.5*getYmin(hvBinnedHistos[n]);
			hvBinnedHistos[n]->SetMinimum(ymin);
			hvBinnedHistos[n]->SetXTitle("#hat{m}_{#mu#mu} GeV");
			hvBinnedHistos[n]->SetYTitle("Events");
			hvBinnedHistos[n]->Draw();
		}
		else hvBinnedHistos[n]->Draw("SAMES");
		
		////////////////////////////////////////
		hSum->Add(hvBinnedHistos[n]); // sum ///
		////////////////////////////////////////
		
		file->Close();
	}
	
	pad_bin->cd();
	hvBinnedHistos[vsize-1]->SetMaximum(1.5*hvBinnedHistos[0]->GetMaximum());
	leg->Draw("SAMES");
	pvtxt_bin->Draw("SAMES");
	
	pad_bin->RedrawAxis();
	pad_bin->Update();
	
	pad_sum->cd();
	pad_sum->Draw();
	hSum->SetMinimum(ymin);
	hSum->SetLineColor(col0);
	hSum->SetLineWidth(2);
	hSum->SetTitle("");
	hSum->SetXTitle("#hat{m}_{#mu#mu} GeV");
	hSum->SetYTitle("Events");
	hSum->Draw();
	pvtxt_sum->Draw("SAMES");
	pad_sum->RedrawAxis();
	pad_sum->Update();
	
	cnv->Update();
	TString name = "plots/plot_" + fname;
	cnv->SaveAs(name+".eps");
	cnv->SaveAs(name+".C");
	cnv->SaveAs(name+".root");
	cnv->SaveAs(name+".png");
	
	return 0;
}
