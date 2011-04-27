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


double xmin  = 0.;
double xmax  = 4000.;
double nbins = 200;
double lumi = 5.;
double mb2fb = 1.e12;
vector<string> svNames;
vector<string> svPaths;
vector<TH1D*>  hvHistos;
vector<double> dvWeights;
string sDir  = "/data/hod/pythia8_ntuples/";
string sName = "";

void addSample(string name, double events, double sigma)
{	
	svNames.push_back(name);

	sName = svNames[svNames.size()-1];

	svPaths.push_back(sDir+sName+".root");
	hvHistos.push_back(new TH1D(sName.c_str(),sName.c_str(),nbins,xmin,xmax));
	dvWeights.push_back(lumi/(events/(sigma*mb2fb)));
}

int plot_binned_samples()
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
	
	
	string sModel;
	string sMass;
	
	cout << "chose model KK/ZP...";
	cin >> sModel;
	cout << "chose mass(GeV)...";
	cin >> sMass;
	
	TString fname = (TString)sModel + (TString)sMass;
	
	if(sModel=="KK" && sMass=="1000")
	{
		addSample("Pythia8_KK1000mumu_120M500",   1e5, 6.88E-09);
		addSample("Pythia8_KK1000mumu_500M800",   1e5, 2.37E-11);
		addSample("Pythia8_KK1000mumu_800M1200",  1e5, 7.58E-10);
		addSample("Pythia8_KK1000mumu_1200M1500", 1e5, 3.01E-12);
		addSample("Pythia8_KK1000mumu_1500M0",    1e5, 1.12E-11);
	}
	if(sModel=="KK" && sMass=="1250")
	{
		addSample("Pythia8_KK1250mumu_120M400",   1e5, 7.24E-09);
		addSample("Pythia8_KK1250mumu_400M800",   1e5, 1.60E-11);
		addSample("Pythia8_KK1250mumu_800M1100",  1e5, 1.74E-11);
		addSample("Pythia8_KK1250mumu_1100M1600", 1e5, 2.28E-10);
		addSample("Pythia8_KK1250mumu_1600M0",    1e5, 1.84E-12);
	}
	if(sModel=="KK" && sMass=="1500")
	{
		addSample("Pythia8_KK1500mumu_120M400",   1e5, 7.43E-09);
		addSample("Pythia8_KK1500mumu_400M800",   1e5, 2.58E-11);
		addSample("Pythia8_KK1500mumu_800M1200",  1e5, 3.59E-12);
		addSample("Pythia8_KK1500mumu_1200M1700", 1e5, 8.16E-11);
		addSample("Pythia8_KK1500mumu_1700M0",    1e5, 1.01E-12);
	}
	if(sModel=="KK" && sMass=="1750")
	{
		addSample("Pythia8_KK1750mumu_120M400",   1e5, 7.55E-09);
		addSample("Pythia8_KK1750mumu_400M900",   1e5, 3.48E-11);
		addSample("Pythia8_KK1750mumu_900M1400",  1e5, 1.58E-12);
		addSample("Pythia8_KK1750mumu_1400M1900", 1e5, 2.96E-11);
		addSample("Pythia8_KK1750mumu_1900M0",    1e5, 7.04E-13);
	}
	if(sModel=="KK" && sMass=="2000")
	{
		addSample("Pythia8_KK2000mumu_120M500",   1e5, 7.66E-09);
		addSample("Pythia8_KK2000mumu_500M1100",  1e5, 1.22E-11);
		addSample("Pythia8_KK2000mumu_1100M1600", 1e5, 7.25E-13);
		addSample("Pythia8_KK2000mumu_1600M2200", 1e5, 1.13E-11);
		addSample("Pythia8_KK2000mumu_2200M0",    1e5, 1.63E-13);
	}
	
	
	
	if(sModel=="KK")
	{
		sModel = "S^{1}/Z_{2} Kaluza-Klein EDs";
		sMass  = "m_{KK} = " + sMass + " GeV";
	}
	if(sModel=="ZP")
	{
		sModel = "Z' SSM";
		sMass  = "m_{Z'} = " + sMass + " GeV";
	}
	
	
	TCanvas* c = new TCanvas("c", "c", 0,0,1200,800);
	c->SetLogy();
	
	TLegend* leg = new TLegend(0.5852843,0.6619171,0.8712375,0.9378238,NULL,"brNDC");
	leg->SetFillColor(kWhite);
	
	TPaveText* pvtxt = new TPaveText(0.1638796,0.7901554,0.3770903,0.9443005,"brNDC");
	pvtxt->SetFillColor(kWhite);
	TText* txt = pvtxt->AddText( sModel.c_str() );
	txt = pvtxt->AddText( sMass.c_str() );
	
	TFile* file;
	TTree* tree;
	
	c->cd();
	c->Draw();
	
	Color_t col = 1;
	
	for(int n=0 ; n<(int)svPaths.size() ; n++)
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
			hvHistos[n]->Fill(mHat);
		}
		
		
		leg->AddEntry(hvHistos[n], svNames[n].c_str(), "l");
		hvHistos[n]->SetLineColor(col+n);
		hvHistos[n]->Scale(dvWeights[n]);
		hvHistos[n]->SetTitle("");
		
		if(n==0)
		{
			hvHistos[0]->SetMinimum(1.e-3);
			hvHistos[0]->SetXTitle("#hat{m}_{#mu#mu} GeV");
			hvHistos[0]->SetYTitle("Events");
			hvHistos[0]->Draw();
		}
		else hvHistos[n]->Draw("SAMES");
		
		file->Close();
	}
	leg->Draw("SAMES");
	pvtxt->Draw("SAMES");
	
	c->RedrawAxis();
	c->Update();
	TString name = "plot_" + fname;
	c->SaveAs(name+".eps");
	c->SaveAs(name+".C");
	c->SaveAs(name+".root");
	c->SaveAs(name+".png");
	
	return 0;
}
