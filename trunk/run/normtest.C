#include "../include/rawStd.h"
#include "../include/rawROOT.h"
#include "../include/logs.h"
#include "../include/bins.h"

TString model = "ZP";

void normtest()
{
	msglvl[DBG] = SILENT;
	msglvl[INF] = VISUAL;
	msglvl[WRN] = VISUAL;
	msglvl[ERR] = VISUAL;
	msglvl[FAT] = VISUAL;

	Int_t g4bin   = 1; //==> g^4=0 ==> DY !
	Int_t minMbin = 3; //~80 GeV
	Int_t maxMbin = 9; //~128 GeV
	TString modelNmae = (model=="ZP") ? "Zprime_SSM" : "KK";
	unsigned int precision = 10.;
	
	Int_t maxMassPointsIndex = (Int_t)((mXXmax-mXXmin)/dmXX);

	//TFile* fD = new TFile("plots/mumu_common_plots_2012-1-19.root","READ");
	TFile* fD   = new TFile("plots/mcdata_histograms_noTmplts_noZpeak_fastDY_noEWkFsig_noCoupScale_noHighMass.root","READ");
	TH1D* h1Dmc      = (TH1D*)fD->Get("hMassMCsum")->Clone();
	TH1D* h1Ddy      = (TH1D*)fD->Get("hMassDYmumu")->Clone();
	TH1D* h1Dtautau  = (TH1D*)fD->Get("hMassDYtautau")->Clone();
	TH1D* h1Dqcd     = (TH1D*)fD->Get("hMassQCD")->Clone();
	TH1D* h1Dwjets   = (TH1D*)fD->Get("hMassW+jets")->Clone();
	TH1D* h1Ddiboson = (TH1D*)fD->Get("hMassDiboson")->Clone();
	TH1D* h1Dttbar   = (TH1D*)fD->Get("hMassTTbar")->Clone();
	TH1D* h1Dmcnody  = (TH1D*)fD->Get("hMassMCsum")->Clone();
	
	TH1D* h1Ddummy   = (TH1D*)fD->Get("hMassMCsum")->Clone("dummy");
	h1Ddummy->Reset();

	h1Dmcnody->Reset();
	h1Dmcnody->Add(h1Dtautau);
	h1Dmcnody->Add(h1Dqcd);
	h1Dmcnody->Add(h1Dwjets);
	h1Dmcnody->Add(h1Ddiboson);
	h1Dmcnody->Add(h1Dttbar);

	TH1D* h1D   = (TH1D*)fD->Get("hMassData")->Clone("data");
	Double_t sumDATA = 0.;
	for(Int_t bin=minMbin ; bin<=maxMbin ; bin++) sumDATA += h1D->GetBinContent(bin);

	TCanvas* c = new TCanvas("c","c",600,400);
	c->cd();
	c->Draw();
	c->SetLogy();
	c->SetLogx();
	c->SetGridy();

	h1Ddy->GetXaxis()->SetRange(70.,130.);
	h1Ddy->SetLineColor(kBlue);
	h1Ddy->SetMinimum(1.e3);
	h1Ddy->SetMaximum(5.e5);
	h1Ddy->Draw();
	
	Double_t lowerLimit = -1;
	Double_t upperLimit = -1;

	Double_t sumTEMPLATE = 0.;
	for(int mass=0 ; mass<=maxMassPointsIndex ; mass++)
	{
		TString massName   = (TString)_s(mXXmin+mass*dmXX);
		TString massNumber = (TString)_s(mass);

		//TFile* fT = new TFile("plots/"+model+"_functions.root","READ");
		TFile* fT = new TFile("/srv01/tau/hod/newBAT/ZPrimeTemplate/interference/exe/"+model+"mm_functions.root","READ");
		TH2D* h2T = (TH2D*)fT->Get(massNumber+"_nominal/hg4Mass_template_"+modelNmae+massName)->Clone();

		if(mass==0) 
		{
			for(Int_t bin=1 ; bin<=h1Ddummy->GetNbinsX() ; bin++)
			{
				if(bin==minMbin)   lowerLimit = h1Ddummy->GetBinLowEdge(bin);
				if(bin==maxMbin+1) upperLimit = h1Ddummy->GetBinLowEdge(bin);
				h1Ddummy->SetBinContent(bin,h2T->GetBinContent(bin,g4bin));
			}
		}

		sumTEMPLATE = 0.;
		for(Int_t bin=minMbin ; bin<=maxMbin ; bin++) sumTEMPLATE += (h2T->GetBinContent(bin,g4bin) + h1Dmcnody->GetBinContent(bin)); // g^4 = 0

		_INFO((string)model+"("+_s(mass)+") mass="+(string)massName+" -> sum(data)/sum(bgNoDY+DYfromTemplate(g^4=0)) = "+_s(sumDATA/sumTEMPLATE,precision));
	}

	double data=0;
	double mcsum=0;
	for(Int_t bin=minMbin ; bin<=maxMbin ; bin++) data  += h1D->GetBinContent(bin);
	for(Int_t bin=minMbin ; bin<=maxMbin ; bin++) mcsum += h1Dmc->GetBinContent(bin);
	_INFO("----- summary -----");
	_INFO("sum(data)/sum(bgNoDY+DYreal) = "+_s(data/mcsum,precision)+" (THIS IS A SANITY TEST, THE VALUE IS BELOW)");
	_INFO((string)model+" -> sum(data)/sum(bgNoDY+DYfromTemplate(g^4=0)) = "+_s(sumDATA/sumTEMPLATE,precision));
	_INFO("Range: "+_s(lowerLimit)+"["+_s(minMbin)+"] TeV -> "+_s(upperLimit)+"["+_s(maxMbin)+"] TeV");
	
	
	h1Ddummy->SetLineColor(kRed);	
	h1Ddummy->SetLineWidth(2);	
	h1Ddummy->Draw("SAMES");
	c->SaveAs("dy_comparison.png");
}
