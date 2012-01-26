#include "../include/rawStd.h"
#include "../include/rawROOT.h"
#include "../include/logs.h"

void normtest()
{
	Int_t g4bin   = 1;
	Int_t minMbin = 3;
	Int_t maxMbin = 9;

	//TFile* fD = new TFile("plots/mumu_common_plots_2012-1-19.root","READ");
	TFile* fD   = new TFile("plots/mcdata_histograms_noTmplts_noZpeak_fastDY_smallDY_noEWkFsig_noCoupScale.root","READ");
	TH1D* h1Dmc      = (TH1D*)fD->Get("hMassMCsum")->Clone();
	TH1D* h1Ddy      = (TH1D*)fD->Get("hMassDYmumu")->Clone();
	TH1D* h1Dqcd     = (TH1D*)fD->Get("hMassQCD")->Clone();
	TH1D* h1Dwjets   = (TH1D*)fD->Get("hMassW+jets")->Clone();
	TH1D* h1Ddiboson = (TH1D*)fD->Get("hMassDiboson")->Clone();
	TH1D* h1Dttbar   = (TH1D*)fD->Get("hMassTTbar")->Clone();
	TH1D* h1Dmcnody  = (TH1D*)fD->Get("hMassMCsum")->Clone();
	TH1D* h1Ddummy   = (TH1D*)fD->Get("hMassMCsum")->Clone();

	h1Ddummy->Reset();

	h1Dmcnody->Reset();
	h1Dmcnody->Add(h1Dqcd);
	h1Dmcnody->Add(h1Dwjets);
	h1Dmcnody->Add(h1Ddiboson);
	h1Dmcnody->Add(h1Dttbar);

	TH1D* h1D   = (TH1D*)fD->Get("hMassData")->Clone();
	Double_t sumDATA = 0.;
	for(Int_t bin=minMbin ; bin<=maxMbin ; bin++) sumDATA += h1D->GetBinContent(bin);

	TCanvas* c = new TCanvas("c","c",600,400);
	c->cd();
	c->Draw();
	c->SetLogy();
	c->SetLogx();
	c->SetGridy();

	h1Ddy->SetLineColor(kBlue);
	h1Ddy->SetMinimum(1.e3);
	h1Ddy->SetMaximum(5.e5);
	h1Ddy->Draw();

	for(int mass=0 ; mass<=125 ; mass++)
	{
		TString massName   = (TString)_s(130+mass*40);
		TString massNumber = (TString)_s(mass);

		TFile* fT = new TFile("plots/ZP_functions.root","READ");
               TH2D* h2T = (TH2D*)fT->Get(massNumber+"/hg4Mass_template_Zprime_SSM"+massName)->Clone();

		if(mass==0) 
		{
			for(Int_t bin=1 ; bin<=h1Ddummy->GetNbinsX() ; bin++)
			{
				h1Ddummy->SetBinContent(bin,h2T->GetBinContent(bin,g4bin));
			}
		}

               //TH2D* h2T = (TH2D*)fT->Get(massNumber+"/hg4Mass_template_KK"+massName)->Clone();
                Double_t sumTEMPLATE = 0.;
                //for(Int_t bin=minMbin ; bin<=maxMbin ; bin++) sumTEMPLATE += (h2T->GetBinContent(bin,g4bin) + (h1Dmc->GetBinContent(bin) - h1Ddy->GetBinContent(bin))); // g^4 = 0
                for(Int_t bin=minMbin ; bin<=maxMbin ; bin++) sumTEMPLATE += (h2T->GetBinContent(bin,g4bin) + h1Dmcnody->GetBinContent(bin)); // g^4 = 0

		cout << "(" << mass << ") mass=" << massName << " -> Norm = " << sumDATA/sumTEMPLATE << endl;
	}

	h1Ddummy->SetLineColor(kRed);	
	h1Ddummy->SetLineWidth(2);	
	h1Ddummy->Draw("SAMES");
	c->SaveAs("dy_comparison.png");


	double data=0;
	double mcsum=0;
	for(Int_t bin=minMbin ; bin<=maxMbin ; bin++) data  += h1D->GetBinContent(bin);
	for(Int_t bin=minMbin ; bin<=maxMbin ; bin++) mcsum += h1Dmc->GetBinContent(bin);
	cout << "data/mcsum = " << data/mcsum << endl;
}
