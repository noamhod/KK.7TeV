#include "../include/rawStd.h"
#include "../include/rawROOT.h"
#include "../include/logs.h"
#include "../include/style.h"
#include "../include/histos.h"


Double_t xmin = 0.;
Double_t xmax = 10.;

TFile* f2DTemplate;
TObjArray* tobjarr;

void init()
{
	f2DTemplate = new TFile("plots/KK_2dtemplates_fastDY_smallDY_noEWkFsig.root","READ");
	tobjarr = new TObjArray();
	tobjarr->Read("template2d");
}

TH1D* TH2toTH1(TH2D* h2, Int_t massbin)
{
	TString massbinname = (TString)_s(massbin);
	TString massname = (TString)_s(h2->GetXaxis()->GetBinCenter(massbin),2);
	TString name = "g2_in_fixed_massbin_"+massbinname;
	Double_t min = h2->GetYaxis()->GetXmin();
	Double_t max = h2->GetYaxis()->GetXmax();
	Int_t nbins = h2->GetNbinsY();
	TH1D* h1 = new TH1D(name,"#frac{dN}{dg^{2}};g^{2};dN/dg^{2}",nbins,min,max);
	for(Int_t bin=1 ; bin<=nbins ; bin++)
	{
		h1->SetBinContent(bin, h2->GetBinContent(massbin,bin));
	}
	return h1;
}

Double_t myfunction(Double_t *x, Double_t *par)
{
	Double_t     g2  = x[0];                   // -> g^2 value
	unsigned int mX  = (unsigned int)par[0];   // -> Z' / KK mass (template running number)
	Int_t        mll = (Int_t)par[1];          // -> dilepton invariant mass bin number
	_INFO("mX  = "+_s(mX));
	_INFO("mll = "+_s(mll));
	_INFO("g2  = "+_s(g2));
	TH2D* h2 = (TH2D*)((TH2D*)(TObjArray*)tobjarr->At(mX));
	TH1D* hTmp = (TH1D*)TH2toTH1(h2,mll);      // get the TH1 histogram of g^2 in the dilepton mass bin number mll
	Double_t xxval = hTmp->Interpolate(g2);    // get the interpolated value of dN/dg^2 at the given g^2
	return xxval;
}

void myfunc()
{
	TF1 *fTmp = new TF1("myfunc",myfunction,xmin,xmax,2);
	fTmp->SetParameters(0,43);
	fTmp->SetParNames("mX","mll");
}

void TH1toTF1()
{
	msglvl[DBG] = SILENT;
	msglvl[INF] = VISUAL;
	msglvl[WRN] = VISUAL;
	msglvl[ERR] = VISUAL;
	msglvl[FAT] = VISUAL;
	
	style();

	TDirectory* oldDir = gDirectory; // remember old directory
	
	init();
	
	TH2D* h2 = (TH2D*)((TH2D*)(TObjArray*)tobjarr->At(0))->Clone();
	
	TH1D* h1z0  = (TH1D*)(TH2toTH1(h2,4))->Clone("");
	h1z0->Scale(1./h1z0->Integral());
	h1z0->SetLineColor(kBlack);
	TH1D* h1lowDY  = (TH1D*)(TH2toTH1(h2,19))->Clone("");
	h1lowDY->Scale(1./h1lowDY->Integral());
	h1lowDY->SetLineColor(kGreen+2);
	TH1D* h1dip  = (TH1D*)(TH2toTH1(h2,43))->Clone("");
	h1dip->Scale(1./h1dip->Integral());
	h1dip->SetLineColor(kBlue);
	TH1D* h1peak = (TH1D*)(TH2toTH1(h2,50))->Clone("");
	h1peak->Scale(1./h1peak->Integral());
	h1peak->SetLineColor(kRed);
	TH1D* h1highDY = (TH1D*)(TH2toTH1(h2,56))->Clone("");
	h1highDY->Scale(1./h1highDY->Integral());
	h1highDY->SetLineColor(kOrange);
	
	TString newtitle = "#frac{1}{N}#times"+(TString)h1highDY->GetTitle();
	TString newytitle = "1/N #times "+(TString)h1highDY->GetYaxis()->GetTitle();
	h1z0->SetTitle(newtitle);
	h1z0->GetYaxis()->SetTitle(newytitle);
	h1lowDY->SetTitle(newtitle);
	h1lowDY->GetYaxis()->SetTitle(newytitle);
	h1dip->SetTitle(newtitle);
	h1dip->GetYaxis()->SetTitle(newytitle);
	h1peak->SetTitle(newtitle);
	h1peak->GetYaxis()->SetTitle(newytitle);
	h1highDY->SetTitle(newtitle);
	h1highDY->GetYaxis()->SetTitle(newytitle);
	
	TLegend* leg = new TLegend(0.4,0.17,0.83,0.63,NULL,"brNDC");
	leg->SetFillStyle(4000); //will be transparent
	leg->SetFillColor(0);
	leg->SetTextFont(42);
	leg->AddEntry(h1z0,"m_{#mu#mu} #approx 90 GeV (Z^{0})");
	leg->AddEntry(h1lowDY,"m_{#mu#mu} #approx 250 GeV (low DY)");
	leg->AddEntry(h1dip,"m_{#mu#mu} #approx 1000 GeV (KK dip)");
	leg->AddEntry(h1peak,"m_{#mu#mu} #approx 2000 GeV (KK peak)");
	leg->AddEntry(h1highDY,"m_{#mu#mu} #approx 3000 GeV (high DY)");
	
	TCanvas* c = new TCanvas("c","c",900,400);
	c->Divide(2,1);
	c->Draw();
	TVirtualPad* p1 = c->cd(1);
	TVirtualPad* p2 = c->cd(2);
	p1->SetTicks(1,1);
	p2->SetTicks(1,1);
	p1->SetLogy();
	p2->SetLogx();
	p2->SetLogz();
	p1->cd();
	p1->Draw();
	h1z0->Draw();
	h1z0->GetYaxis()->SetRangeUser(0.0005,0.1);
	h1lowDY->Draw("SAMES");
	h1lowDY->GetYaxis()->SetRangeUser(0.0005,0.1);
	h1dip->Draw("SAMES");
	h1dip->GetYaxis()->SetRangeUser(0.0005,0.1);
	h1peak->Draw("SAMES");
	h1peak->GetYaxis()->SetRangeUser(0.0005,0.1);
	h1highDY->GetYaxis()->SetRangeUser(0.0005,0.1);
	h1highDY->Draw("SAMES");
	h1highDY->GetYaxis()->SetMoreLogLabels();
	leg->Draw("SAMES");
	p1->RedrawAxis();
	p2->cd();
	h2->Draw("SURF1");
	h2->SetTitle("#frac{dN}{dg^{2}dm_{#mu#mu}}");
	p1->Update();
	p2->Update();
	c->Update();
	c->SaveAs("plots/TH2toTH1_test.png");
	
	_INFO("----------------------------------------------------------");
	
	oldDir->cd();
	
	TF1 *f1 = new TF1("f1",myfunction,xmin,xmax,2);
	f1->SetParameters(0,19);
	f1->SetParNames("mX","mll");
	
	TH1D* h1 = (TH1D*)(TH2toTH1(h2,19))->Clone("");
	h1->SetLineColor(kRed);
	
	TFile* file = new TFile("plots/TH2toTH1toTF1.root","RECREATE");	
	f1->Write();
	file->Write();
	file->Close();
	
	TCanvas* c1 = new TCanvas("c1","c1",600,400);
	c1->cd();
	c1->Draw();
	f1->Draw();
	h1->Draw("SAMES");
	c1->SaveAs("plots/TH1toTF1_test.png");
}
