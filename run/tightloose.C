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
#include <pthread.h>
#include <iomanip>

#include <TROOT.h>
#include <TSystem.h>
#include <TMatrix.h>
#include <TVector.h>
#include <TLorentzVector.h>
#include <TVector3.h>
#include <TCut.h>
#include <TChain.h>
#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TDirectory.h>
#include <TLegend.h>
#include <TMinuit.h>
#include <TApplication.h>
#include <TF1.h>
#include <TF2.h>
#include <TF12.h>
#include <TAxis.h>
#include <TLine.h>
#include <TPaveText.h>
#include <TThread.h>
#include <TList.h>
#include <Riostream.h>
#include <TDOMParser.h>
#include <TXMLNode.h>
#include <TXMLAttr.h>
#include <TEventList.h>

using namespace std;

static const float TeV2GeV = 1.e+3;

static const Int_t    nlogfullimassbins = 60;
static const Double_t logfullimassmin   = 70.;
static const Double_t logfullimassmax   = 2000.;
static Double_t logfullimassbins[nlogfullimassbins+1];

void style()
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
	gStyle->SetPadTopMargin(0.13);
	gStyle->SetPadRightMargin(0.15);
	gStyle->SetPadBottomMargin(0.14);
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
	
	gStyle->SetPalette(1);
	
	gStyle->SetTitleX(0.25); //title X location 
	gStyle->SetTitleY(0.94); //title Y location 
	gStyle->SetTitleW(0.5); //title width 
	gStyle->SetTitleH(0.05); //title height
	gStyle->SetTitleBorderSize(0);
	
	gStyle->cd();
}

static void setLogBins(Int_t nbins, Double_t min, Double_t max, Double_t* xpoints)
{
	Double_t logmin  = log10(min);
	Double_t logmax  = log10(max);
	Double_t logbinwidth = (Double_t)( (logmax-logmin)/(Double_t)nbins );
	xpoints[0] = min;
	for(Int_t i=1 ; i<=nbins ; i++) xpoints[i] = TMath::Power( 10,(logmin + i*logbinwidth) );
}

void tightloose()
{	
	style();
	setLogBins(nlogfullimassbins,logfullimassmin,logfullimassmax,logfullimassbins);

	float Mhat;
	
	TCanvas* c = new TCanvas("c","c",600,400);
	c->SetLogx();
	c->SetLogy();
	c->Draw();
	c->cd();
	
	TLegend* leg = new TLegend(0.6627517,0.6846449,0.7919463,0.8261126,NULL,"brNDC");
	leg->SetFillStyle(4000); //will be transparent
	leg->SetFillColor(0);
	leg->SetTextFont(42);

	TFile fLoose("/data/hod/2011/NTUPLE/analysisLocalControl_TightLoose.root", "READ");
	TTree* tLoose = (TTree*)fLoose.Get("allCuts/allCuts_tree");
	tLoose->SetBranchAddress("Mhat",  &Mhat);
	Int_t nLoose = tLoose->GetEntries();
	TH1D* hLoose = new TH1D("hLoose","tight-loose vs. tight-tight selection;m_{#mu#mu} TeV;Events",nlogfullimassbins,logfullimassbins);
	hLoose->SetLineColor(kRed);
	hLoose->SetMarkerColor(kRed);
	hLoose->SetMarkerStyle(24);
	hLoose->SetMarkerSize(0.8);
	hLoose->SetMinimum(1.e-3);
	hLoose->SetMaximum(7.e+5);
	hLoose->GetXaxis()->SetMoreLogLabels();
	hLoose->GetXaxis()->SetNoExponent();
	leg->AddEntry(hLoose,"tight-loose","lep");
	for(Int_t i=0 ; i<nLoose ; i++)
	{
		tLoose->GetEntry(i);
		hLoose->Fill(Mhat*TeV2GeV);
	}
	
	TFile fTight("/data/hod/2011/NTUPLE/analysisLocalControl.root", "READ");
	TTree* tTight = (TTree*)fTight.Get("allCuts/allCuts_tree");
	tTight->SetBranchAddress("Mhat",  &Mhat);
	Int_t nTight = tTight->GetEntries();
	TH1D* hTight = new TH1D("hTight","tight-loose vs. tight-tight selection;m_{#mu#mu} TeV;Events",nlogfullimassbins,logfullimassbins);
	hTight->SetLineColor(kBlack);
	hTight->SetMarkerColor(kBlack);
	hTight->SetMarkerStyle(24);
	hTight->SetMarkerSize(0.8);
	hTight->SetMinimum(1.e-3);
	hTight->SetMaximum(7.e+5);
	hTight->GetXaxis()->SetMoreLogLabels();
	hTight->GetXaxis()->SetNoExponent();
	leg->AddEntry(hTight,"tight-tight","lep");
	for(Int_t i=0 ; i<nTight ; i++)
	{
		tTight->GetEntry(i);
		hTight->Fill(Mhat*TeV2GeV);
	}

	
	hTight->Draw("e1x1");
	hLoose->Draw("e1x1SAMES");
	leg->Draw("SAMES");
	c->RedrawAxis();
	c->SaveAs("plots/Wjets.png");
}
