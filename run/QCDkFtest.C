#include "../include/rawStd.h"
#include "../include/rawROOT.h"
#include "../include/logs.h"
#include "../include/bins.h"
#include "../include/style.h"
#include "../include/histos.h"
#include "../include/kFactors.h"

using namespace kFactors;

void QCDkFtest()
{
	TString fNameWithOutQCDkF = "plots/ZP_2dtemplates_mc11c_3332st_g4bins_noInterference_noKKtmplates_noEWkF_noQCDkF_noTruth_Xmass2000.root";
	TString fNameWithQCDkF    = "plots/ZP_2dtemplates_mc11c_3332st_g4bins_noInterference_noKKtmplates_noEWkF_noTruth_Xmass2000.root";

	TFile* fTemplateWithOutQCDkF = new TFile(fNameWithOutQCDkF,"READ");
	TObjArray* tobjarr_without = new TObjArray();
	tobjarr_without->Read("template");
	TH1D* hWithOut = (TH1D*)((TH1D*)(TObjArray*)tobjarr_without->At(0))->Clone();
	hWithOut = (TH1D*)hChopper(hWithOut,9)->Clone();

	TFile* fTemplateWithQCDkF = new TFile(fNameWithQCDkF,"READ");
	TObjArray* tobjarr_with = new TObjArray();
	tobjarr_with->Read("template");
	TH1D* hWith = (TH1D*)((TH1D*)(TObjArray*)tobjarr_with->At(0))->Clone();
	hWith = (TH1D*)hChopper(hWith,9)->Clone();


	TCanvas* c = new TCanvas("c","c",600,400);
	c->SetLogx();
	c->SetLogy();
	c->cd();
	c->Draw();
	hWithOut->SetLineColor(kRed);
	hWith->SetLineColor(kBlue);
	hWithOut->Draw();
	hWith->Draw("SAMES");
	c->Update();
	c->RedrawAxis();
	c->SaveAs("plots/QCDkFtest.png");

	Double_t Iwith = Integral(hWith);
	Double_t Iwithout = Integral(hWithOut);
	Double_t QCDkFaverage = Iwith/Iwithout;
	cout << "QCDkF(2TeV)  = " << QCD(2000.) << endl;
	cout << "QCDkFaverage = " << QCDkFaverage << endl;
}
