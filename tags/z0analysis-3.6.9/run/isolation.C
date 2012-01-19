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

void isolation()
{	
	style();

	vector<float>* pt = 0;
	vector<float>* ptcone30 = 0;
	
	TCanvas* c1 = new TCanvas("c1","c1",600,400);
	c1->SetTicks(1,1);
	c1->SetLogy();
	
	TCanvas* c2 = new TCanvas("c2","c2",600,400);
	c2->SetTicks(1,1);
	c2->SetLogy();
	
	TLegend* leg = new TLegend(0.6627517,0.6846449,0.7919463,0.8261126,NULL,"brNDC");
	leg->SetFillStyle(4000); //will be transparent
	leg->SetFillColor(0);
	leg->SetTextFont(42);

	TFile fLoose("/srv01/tau/hod/z0analysis-tests/z0analysis-r170/data/merged.root", "READ");
	TTree* t = (TTree*)fLoose.Get("allCuts/allCuts_tree");
	t->SetBranchAddress("pt", &pt);
	t->SetBranchAddress("ptcone30", &ptcone30);
	Int_t n = t->GetEntries();
	
	TH1D* hIso = new TH1D("iso",";#Sigmap_{T}^{trk}/p_{T};Events",20,0.,1.);
	hIso->SetLineColor(kBlack);
	hIso->SetMarkerColor(kBlack);
	hIso->SetMarkerStyle(20);
	hIso->SetMarkerSize(0.8);
	leg->AddEntry(hIso,"data","lep");
	
	TH1D* hN = new TH1D("N",";N_{#mu};Events",10,0.,10.);
	hN->SetLineColor(kBlack);
	hN->SetMarkerColor(kBlack);
	hN->SetMarkerStyle(20);
	hN->SetMarkerSize(0.8);
	
	int mod1 = 1000;
	int mod2 = 100000;
	for(Int_t i=0 ; i<n ; i++)
	{
		t->GetEntry(i);
		hN->Fill(pt->size());
		for(unsigned int mu=0 ; mu<pt->size() ; mu++)
		{
			float iso = (pt->at(mu)>0.) ? ptcone30->at(mu)/pt->at(mu) : -1.;
			hIso->Fill(iso);
		}
		if(i%mod1==0) cout << "evt " << i << "\r" << flush;
		if(i%mod2==0) cout << endl;
	}
	
	c1->Draw();
	c1->cd();
	hIso->Draw("epx0");
	leg->Draw("SAMES");
	c1->RedrawAxis();
	c1->SaveAs("plots/isolation_iso30.png");
	
	c2->Draw();
	c2->cd();
	hN->Draw("epx0");
	leg->Draw("SAMES");
	c2->RedrawAxis();
	c2->SaveAs("plots/isolation_nMus.png");
}
