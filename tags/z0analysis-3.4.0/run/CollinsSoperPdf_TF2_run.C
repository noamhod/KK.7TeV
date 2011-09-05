#include "../include/basicIncludes.h"

using namespace std;


TH1D *hPy;

void setprobhist(TString type)
{
	TFile* f = new TFile("plots/mchistograms.root", "READ");
	hPy = (TH1D*)f->Get("hprobyQ_"+type+"_ratio")->Clone("hPy");

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
	TString type = "truqqbar";

	style();
	setprobhist(type);
	
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

	TLegend* leg = new TLegend(0.1493289,0.7150538,0.6409396,0.8602151,NULL,"brNDC");
	leg->SetFillColor(kWhite);
	
	TCanvas* cnv_TF12 = new TCanvas("cnv_TF12", "", 600, 400);
	cnv_TF12->SetFillColor(0);
	cnv_TF12->Draw();
	cnv_TF12->cd();
	TF1 *f1 = new TF1("CS(cos(#theta'))_{true}",CS,-1.,+1.,2);
	f1->SetParameters(0.,A4);
	f1->SetParNames("A0","A4");
	f1->GetXaxis()->SetTitle("cos(#theta')");
	f1->GetYaxis()->SetTitle("CS(cos(#theta')|y_{Q}=0)");
	f1->SetLineColor(kBlack);
	leg->AddEntry( f1, "CS distribution (theory)", "l");
	f1->SetMaximum(1.05*f1->GetMaximum());
	f1->Draw();
	
	TF12 *f12 = new TF12("CS(cos(#theta'))_{proj}",f2,0.0,"x");
	f12->GetXaxis()->SetTitle("cos(#theta')");
	f12->GetYaxis()->SetTitle("CS(cos(#theta')|y_{Q}=0)");
	f12->SetMinimum(0.);
	f12->SetLineColor(kRed);
	leg->AddEntry( f12, "with F-B false identify (projected)", "l");
	f12->Draw("SAMES");
	leg->Draw("SAMES");

	cnv_TF2->SaveAs("plots/CS2d_"+type+".png");
	cnv_TF2->SaveAs("plots/CS2d_"+type+".eps");
	cnv_TF2->SaveAs("plots/CS2d_"+type+".pdf");
	cnv_TF2->SaveAs("plots/CS2d_"+type+".root");
	cnv_TF2->SaveAs("plots/CS2d_"+type+".C");
	cnv_TF12->SaveAs("plots/CS1dproj_"+type+".png");
	cnv_TF12->SaveAs("plots/CS1dproj_"+type+".eps");
	cnv_TF12->SaveAs("plots/CS1dproj_"+type+".pdf");
	cnv_TF12->SaveAs("plots/CS1dproj_"+type+".root");
	cnv_TF12->SaveAs("plots/CS1dproj_"+type+".C");
}
