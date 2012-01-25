#include "../include/rawStd.h"
#include "../include/rawROOT.h"
#include "../include/logs.h"

void normtest()
{
	Int_t g4bin = 1;
	Int_t minMbin = 3;
	Int_t maxMbin = 9;

	for(int mass=0 ; mass<=125 ; mass++)
	{
		TString massName   = (TString)_s(130+mass*40);
		TString massNumber = (TString)_s(mass);

		TFile* fD = new TFile("plots/mumu_common_plots_2012-1-19.root","READ");
		TH1D* h1Dmc = (TH1D*)fD->Get("hMassMCsum")->Clone();
		TH1D* h1Ddy = (TH1D*)fD->Get("hMassDYmumu")->Clone();
		TH1D* h1D = (TH1D*)fD->Get("hMassData")->Clone();
		Double_t sumDATA = 0.;
		for(Int_t bin=minMbin ; bin<=maxMbin ; bin++) sumDATA += h1D->GetBinContent(bin);
		//cout << "sumDATA="     << sumDATA     << endl;

		TFile* fT = new TFile("plots/ZP_functions.root","READ");
                TH2D* h2T = (TH2D*)fT->Get(massNumber+"/hg4Mass_template_Zprime_SSM"+massName)->Clone();
                if(h2T==NULL) return;
                Double_t sumTEMPLATE = 0.;
                for(Int_t bin=minMbin ; bin<=maxMbin ; bin++) sumTEMPLATE += (h2T->GetBinContent(bin,g4bin) + h1Dmc->GetBinContent(bin) - h1Ddy->GetBinContent(bin)); // g^4 = 0
                //cout << "sumTEMPLATE=" << sumTEMPLATE << endl;

		cout << "(" << mass << ") mass=" << massName << " -> Norm = " << sumDATA/sumTEMPLATE << endl;
	}
}
