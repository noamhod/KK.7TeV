#include "../include/basicIncludes.h"

using namespace std;


TH1D *hPy;

void setprobhist()
{
	// hPy = new TH1D("hPy","",30,-2.5,2.5);
	// hPy->SetBinContent(0,0.08598319);
	// hPy->SetBinContent(1,0.2288129);
	// hPy->SetBinContent(2,0.1093778);
	// hPy->SetBinContent(3,0.08867133);
	// hPy->SetBinContent(4,0.1471738);
	// hPy->SetBinContent(5,0.1872124);
	// hPy->SetBinContent(6,0.2276665);
	// hPy->SetBinContent(7,0.2118142);
	// hPy->SetBinContent(8,0.2743345);
	// hPy->SetBinContent(9,0.2575395);
	// hPy->SetBinContent(10,0.321228);
	// hPy->SetBinContent(11,0.3499472);
	// hPy->SetBinContent(12,0.3959785);
	// hPy->SetBinContent(13,0.4323933);
	// hPy->SetBinContent(14,0.4359501);
	// hPy->SetBinContent(15,0.3890299);
	// hPy->SetBinContent(16,0.4075662);
	// hPy->SetBinContent(17,0.4817962);
	// hPy->SetBinContent(18,0.4006299);
	// hPy->SetBinContent(19,0.3790587);
	// hPy->SetBinContent(20,0.3229748);
	// hPy->SetBinContent(21,0.297254);
	// hPy->SetBinContent(22,0.2698674);
	// hPy->SetBinContent(23,0.2708024);
	// hPy->SetBinContent(24,0.2562358);
	// hPy->SetBinContent(25,0.2140165);
	// hPy->SetBinContent(26,0.1824918);
	// hPy->SetBinContent(27,0.1901563);
	// hPy->SetBinContent(28,0.1475479);
	// hPy->SetBinContent(29,0.09851675);
	// hPy->SetBinContent(30,0.1116475);
	// hPy->SetBinContent(31,0.1238291);
	TFile* f = new TFile("plots/mchistograms.root", "READ");
	hPy = (TH1D*)f->Get("hprobyQ_rec_ratio")->Clone("hPy");

}

Double_t CS(Double_t *x, Double_t *par)
{
	Float_t xx = x[0];
	Float_t A0 = par[0];
	Float_t A4 = par[1];
	Double_t f = 3./8. * (1+A0/2. + A4*xx + (1.-3.*A0/2.)*xx*xx);
	return f;
}

Double_t CS_corrected(Double_t *x, Double_t *par)
{
	Float_t xx = x[0];
	Float_t yy = x[1];
	Float_t A0 = par[0];
	Float_t A4 = par[1];
	Int_t   b  = hPy->FindBin(yy);
	Float_t Py = hPy->GetBinContent(b);
	Double_t f = 3./8. * (1+A0/2. + (1-2.*Py)*A4*xx + (1.-3.*A0/2.)*xx*xx);
	return f;
}

void CollinsSoperPdf_TF2_run()
{
	style();
	setprobhist();
	
	Double_t Afb = 0.35;
	Double_t A4 = 8./3.*Afb;

	TCanvas* cnv_TF2 = new TCanvas("cnv_TF2", "", 600, 400);
	cnv_TF2->SetFillColor(0);
	cnv_TF2->Draw();
	cnv_TF2->cd();
	TF2 *f2 = new TF2("CS_corrected",CS_corrected,-1.,+1.,-2.5,+2.5,2);
	f2->SetParameters(0.,A4);
	f2->SetParNames("A0","A4");
	f2->GetXaxis()->SetTitle("cos(#theta')");
	f2->GetYaxis()->SetTitle("y_{Q}");
	f2->GetZaxis()->SetTitle("CS(cos(#theta')|y_{Q})");
	f2->Draw("COLZ");

	TCanvas* cnv_TF12 = new TCanvas("cnv_TF12", "", 600, 400);
	cnv_TF12->SetFillColor(0);
	cnv_TF12->Draw();
	cnv_TF12->cd();
	TF12 *f12 = new TF12("CS(cos(#theta'))_{proj}",f2,0.0,"x");
	f12->GetXaxis()->SetTitle("cos(#theta')");
	f12->GetYaxis()->SetTitle("CS(cos(#theta')|y_{Q}=0)");
	f12->SetMinimum(0.);
	
	TF1 *f1 = new TF1("CS(cos(#theta'))_{true}",CS,-1.,+1.,2);
	f1->SetParameters(0.,A4);
	f1->SetParNames("A0","A4");
	f1->GetXaxis()->SetTitle("cos(#theta')");
	f1->GetYaxis()->SetTitle("CS(cos(#theta')|y_{Q}=0)");
	f1->SetLineColor(kBlack);
	
	f12->SetMaximum(1.05*f1->GetMaximum());
	f12->Draw();
	f1->Draw("SAMES");

	cnv_TF2->SaveAs("plots/CS2d.png");
	cnv_TF2->SaveAs("plots/CS2d.eps");
	cnv_TF12->SaveAs("plots/CS1dproj.png");
	cnv_TF12->SaveAs("plots/CS1dproj.eps");
}
