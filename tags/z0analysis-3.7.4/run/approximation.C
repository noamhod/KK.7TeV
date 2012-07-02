#include "../include/rawStd.h"
#include "../include/rawROOT.h"
#include "../include/types.h"
#include "../include/logs.h"
#include "../src/AtlasStyle.C"

#include "../include/couplings.h"
#include "../include/width.h"
#include "../include/helicity.h"

using namespace couplings;
using namespace width;
using namespace helicity;
 
void style()
{       
	gROOT->Reset();
	gROOT->ForceStyle();
	gROOT->LoadMacro("../src/AtlasStyle.C");
	SetAtlasStyle(); 
} 

Double_t c12(Double_t *x, Double_t *par)
{
	double mll = x[0];
	double mX  = x[1];
	double delta = fabs(mll-mX);
	setKKmass(mX);
	double wX = wTotZKK(1);
	if(delta<=100.) return 1.;
	return 1./(((mll*mll-mX*mX)/(wX*mX))*((mll*mll-mX*mX)/(wX*mX)));
}

void approximation()
{
	style();
	
	///////////////////////////////////////////////
	setFermions(); ////////////////////////////////
	setFixedWidth(false); /////////////////////////
	setScaleWidth(false); /////////////////////////
	resetKKmass();/////////////////////////////////
	resetfgGKK(); /////////////////////////////////
	resetfgZKK();//////////////////////////////////
	setCouplingsScale(false); /////////////////////
	///////////////////////////////////////////////

	/*
	TString wX  = "230.";
	TString mX  = "3500.";
	TString mX2 = mX+"*"+mX;
	TString c1  = "(x*x-"+mX2+")/("+wX+"*"+mX+")";
	TString c12 = c1+"*"+c1;
	TString formula = "1./("+c12+")";
	TF1* f = new TF1("f",formula,130,3030);
	*/
	TF2 *f = new TF2("c12",c12, 130,3030, 1000,5000);
	//f->SetNpx(50);
	
	TLatex *t = new TLatex();
	t->SetNDC(1);
	t->SetTextAlign(13);
	t->SetTextSize(0.05);
	t->SetTextColor(kBlack);

	TCanvas* c = new TCanvas("c","c",600,400);
	c->cd();
	c->Draw();
	c->SetLogx();
	c->SetLogz();
	f->GetXaxis()->SetTitle("m_{ll} TeV");
	f->GetYaxis()->SetTitle("m_{KK} GeV");
	f->GetYaxis()->SetTitleOffset(1.8);
	f->GetZaxis()->SetTitle("c_{1}^{-2}");
	f->Draw("surf3");
	t->DrawLatex(0.61,0.38,"c_{1}^{-2} = #left(#frac{s_{ll}-m_{X}^{2}}{#Gamma_{X}m_{X}}#right)^{-2}");
	c->SaveAs("plots/approximation.eps");
	c->SaveAs("plots/approximation.png");
}
