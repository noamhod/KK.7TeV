#include "../include/rawStd.h"
#include "../include/rawROOT.h"
#include "../include/types.h"
#include "../include/logs.h"
#include "../include/bins.h"
#include "../include/histos.h"
#include "../include/style.h"

TString model  = "ZP";
TString mutype = "33st";
TString binning = "linearbins";
bool doTruth = false;
bool doPileup = true;
bool doZpTrw  = true;

void mc11ac()
{
	msglvl[DBG] = SILENT;
	msglvl[INF] = VISUAL;
	msglvl[WRN] = VISUAL;
	msglvl[ERR] = VISUAL;
	msglvl[FAT] = VISUAL;

	style();
	
	TString suffix = "";
	if(doTruth) suffix = "_truth";

	_INFO("");
	
	TString pu = (doPileup) ? "" : "_noPUrw";
	TString ZpT = (doZpTrw) ? "" : "_noZpTrw";
	
	TFile* f11a = new TFile("plots/ZP_2dtemplates_mc11a_33st_noKKtmplates"+pu+"_overallEWkF_noInAmpSigEWkF"+ZpT+"_Xmass2000.root", "READ");
	// TFile* f11a = new TFile("plots/ZP_2dtemplates_mc11a_33st_noKKtmplates"+pu+"_overallEWkF_noInAmpSigEWkF"+ZpT+"_noHighMbins_wthOfficialZP_Xmass2000.root", "READ");
	TH1D* h11a = (TH1D*)f11a->Get("hMass_DYmumu"+suffix)->Clone();
	h11a->SetTitle("");
	h11a->SetLineColor(kBlack);
	h11a->SetFillStyle(4000);
	h11a->SetFillColor(0);
	TH1D* h11a_chop = hChopperUp(h11a,49);
	h11a_chop->SetMarkerStyle(20);
	h11a_chop->SetMarkerSize(0.5);
	h11a_chop->SetMarkerColor(kBlack);
	h11a_chop->SetLineColor(kBlack);
	
	
	_INFO("");
	
	TFile* f11c = new TFile("plots/ZP_2dtemplates_mc11c_33st_noKKtmplates"+pu+"_overallEWkF_noInAmpSigEWkF"+ZpT+"_Xmass2000.root", "READ");
	// TFile* f11c = new TFile("plots/ZP_2dtemplates_mc11c_33st_noKKtmplates"+pu+"_overallEWkF_noInAmpSigEWkF"+ZpT+"_noHighMbins_wthOfficialZP_Xmass2000.root", "READ");
	TH1D* h11c = (TH1D*)f11c->Get("hMass_DYmumu"+suffix)->Clone();
	h11c->SetTitle("");
	h11c->SetLineColor(kRed);
	h11c->SetFillStyle(4000);
	h11c->SetFillColor(0);
	h11c->SetLineStyle(3);
	TH1D* h11c_chop = hChopperUp(h11c,49);
	h11c_chop->SetMarkerStyle(20);
	h11c_chop->SetMarkerSize(0.5);
	h11c_chop->SetMarkerColor(kRed);
	h11c_chop->SetLineColor(kRed);

	_INFO("");
	
	TH1D* hResiduals = (TH1D*)f11c->Get("hMass_DYmumu"+suffix)->Clone("residuals");
	TH1D* hRatio     = (TH1D*)f11c->Get("hMass_DYmumu"+suffix)->Clone("ratio");
	hResiduals->Reset();
	hRatio->Reset();
	
	_INFO("");

	residuals(h11a,h11c,hResiduals);
	hRatio->Divide(h11a,h11c,1.,1.,"B");
	/*
	this = c1*h1/(c2*h2)

	if errors are defined (see TH1::Sumw2), errors are also recalculated
	Note that if h1 or h2 have Sumw2 set, Sumw2 is automatically called for this
	if not already set.
	The resulting errors are calculated assuming uncorrelated histograms.
	However, if option ="B" is specified, Binomial errors are computed.
	In this case c1 and c2 do not make real sense and they are ignored.

	IMPORTANT NOTE: If you intend to use the errors of this histogram later
	you should call Sumw2 before making this operation.
	This is particularly important if you fit the histogram after TH1::Divide

	Please note also that in the binomial case errors are calculated using standard
	binomial statistics, which means when b1 = b2, the error is zero.
	If you prefer to have efficiency errors not going to zero when the efficiency is 1, you must
	use the function TGraphAsymmErrors::BayesDivide, which will return an asymmetric and non-zero lower
	error for the case b1=b2.
	*/
	
	_INFO("");
	
	for(Int_t i=0 ; i<=hRatio->GetNbinsX()+1 ; i++) hRatio->SetBinError(i,0);
	hRatio->SetTitle("");
	hRatio->SetMarkerStyle(20);
	hRatio->SetMarkerSize(0.5);
	hRatio->GetXaxis()->SetLabelSize(0.073);
	hRatio->GetYaxis()->SetLabelSize(0.073);
	hRatio->GetXaxis()->SetTitleSize(0.073);
	hRatio->GetYaxis()->SetTitleSize(0.073);
	hRatio->SetTitleSize(0.075);
	hRatio->GetYaxis()->SetTitleOffset(0.5);
	if(doTruth)
	{
		hRatio->SetMinimum(0.99);
		hRatio->SetMaximum(1.01);
	}
	else
	{
		hRatio->SetMinimum(0.5);
		hRatio->SetMaximum(1.5);
	}
	hRatio->SetTitle("");
	hRatio->GetYaxis()->SetTitle("ratio");
	
	_INFO("");
	
	for(Int_t i=0 ; i<=hResiduals->GetNbinsX()+1 ; i++) hResiduals->SetBinError(i,0);
	hResiduals->SetTitle("");
	hResiduals->SetMarkerStyle(20);
	hResiduals->SetMarkerSize(0.5);
	hResiduals->GetXaxis()->SetLabelSize(0.073);
	hResiduals->GetYaxis()->SetLabelSize(0.073);
	hResiduals->GetXaxis()->SetTitleSize(0.073);
	hResiduals->GetYaxis()->SetTitleSize(0.073);
	hResiduals->SetTitleSize(0.075);
	hResiduals->GetYaxis()->SetTitleOffset(0.5);
	if(doTruth)
	{
		hResiduals->SetMinimum(-0.001);
		hResiduals->SetMaximum(+0.001);
	}
	else
	{
		hResiduals->SetMinimum(-10.);
		hResiduals->SetMaximum(+10.);
	}
	hResiduals->SetTitle("");
	hResiduals->GetYaxis()->SetTitle("residuals");

	_INFO("");
	
	TLine* line0 = new TLine(0.07,0.,3.,0.);	
	line0->SetLineColor(kRed);
	line0->SetLineWidth(2);
	
	TLine* line1 = new TLine(0.07,1.,3.,1.);	
	line1->SetLineColor(kRed);
	line1->SetLineWidth(2);
	
	_INFO("");
	
	TLegend* leghischop = new TLegend(0.6,0.6,0.9,0.8,NULL,"brNDC");
	leghischop->SetFillStyle(4000); //will be transparent
	leghischop->SetFillColor(0);
	leghischop->SetTextFont(42);
	leghischop->AddEntry(h11a_chop,"mc11a","P");
	leghischop->AddEntry(h11c_chop,"mc11c","P");
	
	TLegend* leghis = new TLegend(0.5,0.5,0.9,0.8,NULL,"brNDC");
	leghis->SetFillStyle(4000); //will be transparent
	leghis->SetFillColor(0);
	leghis->SetTextFont(42);
	leghis->AddEntry(h11a,"mc11a-mc11c","F");

	TLegend* legrat = new TLegend(0.55,0.8,0.85,0.92,NULL,"brNDC");
	legrat->SetFillStyle(4000); //will be transparent
	legrat->SetFillColor(0);
	legrat->SetTextFont(42);
	legrat->AddEntry(hRatio,"#frac{mc11a}{mc11c}","P");
	
	TLegend* legres = new TLegend(0.55,0.8,0.85,0.92,NULL,"brNDC");
	legres->SetFillStyle(4000); //will be transparent
	legres->SetFillColor(0);
	legres->SetTextFont(42);
	legres->AddEntry(hResiduals,"#frac{mc11a-mc11c}{#sqrt{#delta^{2}mc11a+#delta^{2}mc11c}}","P");
	
	_INFO("");
	
	TCanvas* cnv_chop = new TCanvas("c_chop","c_chop",600,400);
	cnv_chop->cd();
	cnv_chop->Draw();
	cnv_chop->SetLogy();
	// cnv_chop->SetLogx();
	// cnv_chop->SetGridy();
	cnv_chop->SetTicks(1,1);
	h11a_chop->Draw("ep");
	h11c_chop->Draw("epSAMEAS");
	leghischop->Draw("SAMEAS");
	cnv_chop->RedrawAxis();
	cnv_chop->Update();
	saveas(cnv_chop,"plots/mc11ac_chop"+suffix);
	
	
	TCanvas* cnv = new TCanvas("c","c",600,550);
	cnv->Divide(1,3);
	TVirtualPad* phis = cnv->cd(1);
	TVirtualPad* prat = cnv->cd(2);	
	TVirtualPad* pres = cnv->cd(3);	
	phis->SetPad(0.00, 0.455,  1.00, 1.00);
	prat->SetPad(0.00, 0.205, 1.00, 0.455);
	pres->SetPad(0.00, 0.00,  1.00, 0.25);
	phis->SetBottomMargin(0.012);
	prat->SetBottomMargin(0.20);
	prat->SetTopMargin(0.012);
	pres->SetBottomMargin(0.20);
	pres->SetTopMargin(0.012);
	
	_INFO("");
	
	/* phis->cd();
	phis->Draw();
	phis->SetTicks(1,1);
	phis->SetLogy();
	phis->SetLogx();
	h11a->SetMinimum(1.e-3);
	h11a->SetMaximum(1.e+6);
	h11a->Draw();
	h11c->Draw("SAME");
	leghis->Draw("SAMES");
	phis->RedrawAxis();
	phis->Update(); */

	phis->cd();
	phis->Draw();
	phis->SetLogx();
	phis->SetTicks(1,1);
	h11a->Add(h11c,-1.);
	if(doTruth)
	{
		h11a->SetMinimum(-0.00005);
		h11a->SetMaximum(+0.00005);
	}
	else
	{
		h11a->SetMinimum(-8000);
		h11a->SetMaximum(+8000);
	}
	h11a->Draw("hist");
	leghis->Draw("SAMES");
	phis->RedrawAxis();
	phis->Update();
	
	_INFO("");
	
	prat->cd();
	prat->Draw();
	prat->SetTicks(1,1);
	prat->SetGridy();
	prat->SetLogx();
	hRatio->Draw("ep");
	line1->Draw("SAMES");
	hRatio->Draw("epSAMES");
	legrat->Draw("SAMES");
	prat->RedrawAxis();
	prat->Update();
	
	_INFO("");
	
	pres->cd();
	pres->Draw();
	pres->SetTicks(1,1);
	pres->SetGridy();
	pres->SetLogx();
	hResiduals->Draw("ep");
	line0->Draw("SAMES");
	hResiduals->Draw("epSAMES");
	legres->Draw("SAMES");
	pres->RedrawAxis();
	pres->Update();
	
	_INFO("");

	suffix = (suffix=="") ? "_recon"   : suffix;
	suffix += (doPileup)  ? "_allWgts" : "_noPUrw";
	suffix += (doZpTrw)   ? ""         : "_noZpTrw";
	saveas(cnv,"plots/mc11ac"+suffix);
}
