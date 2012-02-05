#include "../include/rawStd.h"
#include "../include/rawROOT.h"
#include "../include/logs.h"
#include "../include/bins.h"
#include "../include/style.h"

TString massName   = "2130";
TString massNumber_mm = "20";
TString massNumber_ee = "50";

void template_plot()
{
	msglvl[DBG] = SILENT;
	msglvl[INF] = VISUAL;
	msglvl[WRN] = VISUAL;
	msglvl[ERR] = VISUAL;
	msglvl[FAT] = VISUAL;

	style();

	gStyle->SetPadTopMargin(0.05);
	gStyle->SetPadRightMargin(0.05);
	gStyle->SetPadBottomMargin(0.05);
	gStyle->SetPadLeftMargin(0.08);

	TFile* fZPee = new TFile("plots/ZPee_functions.root","READ");
	TFile* fKKee = new TFile("plots/KKee_functions.root","READ");
	TFile* fZPmm = new TFile("plots/ZPmm_functions.root","READ");
	TFile* fKKmm = new TFile("plots/KKmm_functions.root","READ");

	TH2D* hZPee = (TH2D*)fZPee->Get(massNumber_ee+"/hg4Mass_template_ZP"+massName)->Clone();
	TH2D* hKKee = (TH2D*)fKKee->Get(massNumber_ee+"/hg4Mass_template_KK"+massName)->Clone();
	TH2D* hZPmm = (TH2D*)fZPmm->Get(massNumber_mm+"/hg4Mass_template_Zprime_SSM"+massName)->Clone();
	TH2D* hKKmm = (TH2D*)fKKmm->Get(massNumber_mm+"/hg4Mass_template_KK"+massName)->Clone();

	hZPee->SetTitle("");
	hKKee->SetTitle("");
	hZPmm->SetTitle("");
	hKKmm->SetTitle("");

	hZPee->GetXaxis()->SetTitle("m_{ee} TeV");
	hKKee->GetXaxis()->SetTitle("m_{ee} TeV");

	TCanvas* c = new TCanvas("c","",800,600);
	c->Divide(2,2);

	TVirtualPad* p1 = c->cd(1);
	TVirtualPad* p2 = c->cd(2);
	TVirtualPad* p3 = c->cd(3);
	TVirtualPad* p4 = c->cd(4);

	p1->SetLogx();
	p2->SetLogx();
	p3->SetLogx();
	p4->SetLogx();

	p1->SetLogz();
	p2->SetLogz();
	p3->SetLogz();
	p4->SetLogz();

	c->cd();
	c->Draw();

	p1->cd();	
	hZPee->Draw("SURF1");
	p2->cd();
        hKKee->Draw("SURF1");
	p3->cd();
        hZPmm->Draw("SURF1");
	p4->cd();
        hKKmm->Draw("SURF1");

	p1->Update();
	p2->Update();
	p3->Update();
	p4->Update();
	
	c->SaveAs("tempaltes_"+massName+"GeV.eps");
	c->SaveAs("tempaltes_"+massName+"GeV.png");
}
