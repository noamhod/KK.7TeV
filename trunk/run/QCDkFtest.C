#include "../include/rawStd.h"
#include "../include/rawROOT.h"
#include "../include/logs.h"
#include "../include/bins.h"
//#include "../include/style.h"
#include "../include/histos.h"
#include "../include/kFactors.h"
#include "../src/AtlasStyle.C"

void style()
{
	gROOT->Reset();
	gROOT->ForceStyle();
	gROOT->LoadMacro("../src/AtlasStyle.C");
	SetAtlasStyle();
}

using namespace kFactors;

void QCDkFtest()
{
	msglvl[DBG] = SILENT;
	msglvl[INF] = VISUAL;
	msglvl[WRN] = VISUAL;
	msglvl[ERR] = VISUAL;
	msglvl[FAT] = VISUAL;

	style();

	TString fName1 = "plots/ZP_2dtemplates_mc11c_3332st_g4bins_noInterference_noKKtmplates_noEWkF_noQCDkF_noTruth_Xmass2000.root";
	TString fName2 = "plots/ZP_2dtemplates_mc11c_3332st_g4bins_noInterference_noKKtmplates_noEWkF_noTruth_Xmass2000.root";
	TString s1 = "no QCDkF";
	TString s2 = "with QCDkF";

	TFile* fTemplate1 = new TFile(fName1,"READ");
	TObjArray* tobjarr_1 = new TObjArray();
	tobjarr_1->Read("template");
	TH1D* h1 = (TH1D*)((TH1D*)(TObjArray*)tobjarr_1->At(0))->Clone();
	//h1 = (TH1D*)hChopper(h1,9)->Clone();
	TFile* fTemplate2 = new TFile(fName2,"READ");
	TObjArray* tobjarr_2 = new TObjArray();
	tobjarr_2->Read("template");
	TH1D* h2 = (TH1D*)((TH1D*)(TObjArray*)tobjarr_2->At(0))->Clone();
	//h2 = (TH1D*)hChopper(h2,9)->Clone();

	/*
	setLogBins(nlogofficialimassbins,logofficialimassmin,logofficialimassmax,logofficialimassbins);
	TH1D* h1 = new TH1D("h1",";m_{#mu#mu} GeV;QCD k-factor", nlogofficialimassbins,logofficialimassbins);
	TH1D* h2 = new TH1D("h2",";m_{#mu#mu} GeV;QCD k-factor", nlogofficialimassbins,logofficialimassbins);
	TString s1 = "NNLO/LO**";
        TString s2 = "NNLO/MSTW2008LO";
	for(Int_t bin=1 ; bin<=h1->GetNbinsX() ; bin++)
	{
		double mass = h1->GetBinCenter(bin);
		h1->SetBinContent(bin,QCD(mass,"NNLO/LO**"));
		h2->SetBinContent(bin,QCD(mass,"NNLO/MSTW2008LO"));
	}
	*/
	
	double max1 = h1->GetMaximum();
	double max2 = h2->GetMaximum();
	h1->SetMaximum( (max1>max2) ? 1.1*max1 : 1.1*max2 );
	h1->GetXaxis()->SetMoreLogLabels(1);
	h1->GetXaxis()->SetNoExponent();
	h2->GetXaxis()->SetMoreLogLabels(1);
	h2->GetXaxis()->SetNoExponent();


	TLegend* legH = new TLegend(0.25,0.80,0.55,0.95,NULL,"brNDC");
	legH->SetFillStyle(4000); //will be transparent
	legH->SetFillColor(0);
	legH->SetTextFont(42);
	legH->AddEntry(h1,s1,"l");
	legH->AddEntry(h2,s2,"l");

	TCanvas* c = new TCanvas("c","c",600,550);
	c->Divide(1,2);
	TVirtualPad* ph = c->cd(1);
	TVirtualPad* pr = c->cd(2);	
	ph->SetPad(0.00, 0.35, 1.00, 1.00);
	pr->SetPad(0.00, 0.00, 1.00, 0.355);
	ph->SetBottomMargin(0.012);
	pr->SetBottomMargin(0.20);
	pr->SetTopMargin(0.012);
	
	
	/////////////////////////// histos
	ph->cd();
	ph->Draw();
	ph->SetTicks(1,1);
	ph->SetLogy();
	ph->SetLogx();
	h1->SetLineColor(kRed);
	h2->SetLineColor(kBlue);
	h1->Draw();
	h2->Draw("SAMES");
	legH->Draw("SAMES");
	ph->RedrawAxis();
	ph->Update();

	/////////////////////////// ratio
	pr->cd();
	pr->Draw();
	pr->SetTicks(1,1);
	pr->SetGridy();
	pr->SetLogx();
	TLine* line = new TLine(h1->GetXaxis()->GetXmin(),1.,h1->GetXaxis()->GetXmax(),1.);
	line->SetLineColor(kRed);
	TH1D* hRatio = (TH1D*)h2->Clone();
	//hRatio->Reset();
	hRatio->Divide(h1);
	hRatio->GetYaxis()->SetTitle("Ratio");
	hRatio->SetLineColor(kBlack);
	hRatio->SetFillColor(kOrange+2);
	hRatio->SetFillStyle(3017);
	hRatio->GetXaxis()->SetLabelSize(0.075);
	hRatio->GetYaxis()->SetLabelSize(0.075);
	hRatio->GetXaxis()->SetTitleSize(0.075);
	hRatio->GetYaxis()->SetTitleSize(0.075);
	hRatio->SetTitleSize(0.075);
	hRatio->SetTitleSize(0.075);
	hRatio->GetYaxis()->SetTitleOffset(0.5);
	hRatio->GetXaxis()->SetMoreLogLabels(1);
	hRatio->GetXaxis()->SetNoExponent();	
	hRatio->Draw("hist");
	line->Draw("SAMES");
	TLegend* legR = new TLegend(0.25,0.70,0.55,0.95,NULL,"brNDC");
	legR->SetFillStyle(4000); //will be transparent
	legR->SetFillColor(0);
	legR->SetTextFont(42);
	legR->AddEntry(hRatio,"#frac{"+s1+"}{"+s2+"}","f");
	legR->Draw("SAMES");
	pr->RedrawAxis();
	pr->Update();


	c->Update();
	c->RedrawAxis();
	c->SaveAs("plots/QCDkFtest.png");
	c->SaveAs("plots/QCDkFtest.root");

	Double_t I2 = Integral(h2);
	Double_t I1 = Integral(h1);
	Double_t Iratio = I2/I1;
	cout << "I(" << s2 << ")/I(" << s1 << ") = " << Iratio << endl;
	cout << "QCDkF(2 TeV,NNLO/LO**)       = " << QCD(2000.,"NNLO/LO**") << endl;
	cout << "QCDkF(2 TeV,NNLO/MSTW2008LO) = " << QCD(2000.,"NNLO/MSTW2008LO") << endl;
}
