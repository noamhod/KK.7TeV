#include "../include/rawStd.h"
#include "../include/rawROOT.h"
#include "../include/types.h"
#include "../include/logs.h"
#include "../include/style.h"
#include "../include/histos.h"
#include "../include/units.h"

void hstack()
{
	msglvl[DBG] = SILENT;
	msglvl[INF] = VISUAL;
	msglvl[WRN] = VISUAL;
	msglvl[ERR] = VISUAL;
	msglvl[FAT] = VISUAL;

	style();
	
	// TString suffix = "_noData_noZpeak_noPUrw_noEWkF_noEWkFsig_noQCDkF";
	// TString suffix = "_noData_noZpeak_fastDY_smallDY_noPUrw_noEWkF_noEWkFsig_noQCDkF_noZpTrw_noCoupScale";
	// TString suffix = "";
	TString suffix = "_noPUrw";
	TFile* fhistos = new TFile("plots/mcdata_histograms"+suffix+".root","READ");
	
	TString titles = (TString)(((TH1D*)fhistos->Get("hMassDYmumu"))->GetTitle());
	titles += ";" + (TString)(((TH1D*)fhistos->Get("hMassDYmumu"))->GetXaxis()->GetTitle());
	titles += ";" + (TString)(((TH1D*)fhistos->Get("hMassDYmumu"))->GetYaxis()->GetTitle());
	THStack* hs = new THStack("hs_"+suffix,titles);
	
	TH1D* hTTbar   = (TH1D*)fhistos->Get("hMassTTbar")->Clone();
	hs->Add(hTTbar);
	TH1D* hDiboson = (TH1D*)fhistos->Get("hMassDiboson")->Clone();
	hs->Add(hDiboson);
	TH1D* hDY      = (TH1D*)fhistos->Get("hMassDYmumu")->Clone();
	hs->Add(hDY);
	
	TH1D* hData     = (TH1D*)fhistos->Get("hMassData")->Clone();
	hData->SetLineWidth(2);
	hData->SetMarkerStyle(20);
	TH1D* hKKtemplate = (TH1D*)fhistos->Get("hMassKK2000_template")->Clone();
	hKKtemplate->SetLineWidth(2);
	hKKtemplate->SetLineColor(kGreen+2);
	TH1D* hZPtemplate = (TH1D*)fhistos->Get("hMassZprime_SSM2000_template")->Clone();
	hZPtemplate->SetLineWidth(2);
	hZPtemplate->SetLineColor(kViolet+2);
	
	TLegend* leg = new TLegend(0.58,0.50,0.82,0.85,NULL,"brNDC");
	leg->SetFillStyle(4000); //will be transparent
	leg->SetFillColor(0);
	leg->SetTextFont(42);
	leg->AddEntry(hData,"2011 Data","LEP0");
	leg->AddEntry(hDY,"#gamma/Z","f");
	leg->AddEntry(hDiboson,"Diboson","f");
	leg->AddEntry(hTTbar,"t#bar{t}","f");
	leg->AddEntry(hKKtemplate,"#gamma_{KK}/Z_{KK} 2 TeV Template","l");
	leg->AddEntry(hZPtemplate,"Z'_{SSM} 2 TeV Template","l");
	
	TText* txt = NULL;
	TPaveText* pvtxt_atlas = new TPaveText(0.4032663,0.75,0.5678392,0.85,"brNDC"); // 0.2110553,0.7097902,0.3756281,0.8041958 -> for 2d
	pvtxt_atlas->SetFillStyle(4000); //will be transparent
	pvtxt_atlas->SetFillColor(0);
	pvtxt_atlas->SetTextFont(42);
	txt = pvtxt_atlas->AddText("#bf{#splitline{#it{ATLAS}}{#scale[0.42]{work in progress}}}");
	
	TPaveText* pvtxt_lumi = new TPaveText(0.4032663,0.63,0.5678392,0.738,"brNDC"); // 0.2110553,0.5926573,0.3756281,0.6993007 -> for 2d
	pvtxt_lumi->SetFillStyle(4000); //will be transparent
	pvtxt_lumi->SetFillColor(0);
	TString sLumi = (TString)_s(luminosity,2);
	txt = pvtxt_lumi->AddText( "#intLdt~"+ sLumi +" fb^{-1}" );
	
	
	TCanvas* c = new TCanvas("c","c", 600, 400);
	c->SetLogy();
	c->SetLogx();
	c->SetTicks(1,1);
	c->cd();
	c->Draw();
	
	TString name = "hstack"+suffix;

	c->cd();
	hs->Draw(); // Draw("nostack");
	hs->SetMinimum(1.e-3);
	hs->GetXaxis()->SetMoreLogLabels();
	hs->GetXaxis()->SetNoExponent();
	hKKtemplate->Draw("SAMES");
	hZPtemplate->Draw("SAMES");
	hData->Draw("epx0 SAMES");
	leg->Draw("SAMES");
	pvtxt_atlas->Draw("SAMES");
	pvtxt_lumi->Draw("SAMES");
	saveas(c,"plots/"+name);
}
