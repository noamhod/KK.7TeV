//////////////////////////////////////////////////////////
//// usage: root -b -l -q template_plot_new.C++\(36\) ////
//////////////////////////////////////////////////////////

#include "../include/rawStd.h"
#include "../include/rawROOT.h"
#include "../include/types.h"
#include "../include/logs.h"
#include "../include/histos.h"
#include "../include/style.h"
#include "../src/AtlasStyle.C"

void atlstyle()
{
	gROOT->Reset();
	gROOT->ForceStyle();
	gROOT->LoadMacro("../src/AtlasStyle.C");
	SetAtlasStyle();
}

TH2D* getTemplate(TString fname, unsigned int uiXmass, TString model)
{
	TFile* fT = new TFile(fname,"READ");
	TString mass  = (TString)_s(uiXmass*100+130);
	TString imass = (TString)_s(uiXmass);
	TString hname = "";
	if     (model=="KK2")           hname = imass+"_nominal/hg2Mass_template_KK"+mass;
	else if(model=="KK4")           hname = imass+"_nominal/hg4Mass_template_KK"+mass;
	else if(model=="ZP2")           hname = imass+"_nominal/hg2Mass_template_Zprime_SSM"+mass;
	else if(model=="ZP4")           hname = imass+"_nominal/hg4Mass_template_Zprime_SSM"+mass;
	else if(model=="ZP4NOINT")      hname = imass+"_nominal/hg4Mass_template_Zprime_SSM"+mass+"_sumDY";
	else if(model=="ZP4NOINTNOSCL") hname = imass+"_nominal/hg4Mass_template_Zprime_SSM"+mass+"_sumDY";
	else _FATAL("model -> "+(string)model+" is undefined");
	_INFO("from    -> "+(string)fname);
	_INFO("getting -> "+(string)hname);
	TH2D* tmplt = (TH2D*)fT->Get(hname)->Clone();
	return tmplt;
}

TH2D* getSyst(TString fname, TString systName, unsigned int uiXmass, TString model)
{
	TFile* fT = new TFile(fname,"READ");
	TString mass  = (TString)_s(uiXmass*100+130);
	TString imass = (TString)_s(uiXmass);
	TString hname = "";
	TString syst = "";
	
	if(systName=="Zxs")        syst = "_sys_Zxs";
	if(systName=="PDF")        syst = "_sys_pdfZ";
	if(systName=="kEWK")       syst = "_sys_kEWK";
	if(systName=="mmSlopeEff") syst = "_sys_mmSlopeEff";
	if(systName=="mmRes")      syst = "_sys_mmRes";
	
	if     (model=="KK2")           hname = imass+"_syst/"+systName+"/hg2Mass_template_KK"+mass+syst;
	else if(model=="KK4")           hname = imass+"_syst/"+systName+"/hg4Mass_template_KK"+mass+syst;
	else if(model=="ZP2")           hname = imass+"_syst/"+systName+"/hg2Mass_template_Zprime_SSM"+mass+syst;
	else if(model=="ZP4")           hname = imass+"_syst/"+systName+"/hg4Mass_template_Zprime_SSM"+mass+syst;
	else if(model=="ZP4NOINT")      hname = imass+"_nominal/hg4Mass_template_Zprime_SSM"+mass+"_sumDY"+syst;
	else if(model=="ZP4NOINTNOSCL") hname = imass+"_nominal/hg4Mass_template_Zprime_SSM"+mass+"_sumDY"+syst;
	else _FATAL("model -> "+(string)model+" is undefined");
	_INFO("from    -> "+(string)fname);
	_INFO("getting -> "+(string)hname);
	TH2D* tmplt = (TH2D*)fT->Get(hname)->Clone();
	return tmplt;
}

void plottemplate(TH2D* h, TString name="", Float_t phi = -25, bool dologz=true)
{
	TCanvas* c = NULL;
	h->SetTitle("");
	
	if(name.Contains("Res"))
	{
		c = new TCanvas("c","c",900,600);
		c->cd();
		c->Draw();
		c->SetLogx();
		if(dologz) c->SetLogz();

		c->SetTopMargin(0.035);
		c->SetBottomMargin(0.1);
		c->SetLeftMargin(0.1);
		c->SetRightMargin(0.14);
		
		h->GetXaxis()->SetMoreLogLabels();
		h->GetXaxis()->SetNoExponent();

		//h->GetZaxis()->SetTitleOffset(1.3);

		//h->Draw("CONT4Z");
		h->Draw("COLZ");
	}
	else
	{
		c = new TCanvas("c","c",900,600);
		c->cd();
		c->Draw();
		c->SetLogx();
		if(dologz) c->SetLogz();


		h->GetYaxis()->SetLimits(0.,10.);
		Double_t xmin = 0.;
		Double_t xmax = 10.;
		Int_t nPrimitiveBins = 10;
		Int_t nBins = nPrimitiveBins*(Int_t)(xmax-xmin);
		h->GetYaxis()->Set(nBins, xmin, xmax);
		// h->GetYaxis()->SetNdivisions((Int_t)(10.*16),kFALSE);
		// h->RebinY(5);
	
		// h->SetFillColor(kOrange);
		// h->Draw("SURF4");
		
		c->SetPhi(phi);
		c->SetTheta(20);

		h->GetZaxis()->SetTitleOffset(1.3);

		h->Draw("SURF3");
	}

	c->Modified();
	c->Update();
	c->SaveAs(name+".png");
	c->SaveAs(name+".eps");
	delete c;
}

void template_plot_new(unsigned int uiXmass, TString styletype="atlas")
{
	msglvl[DBG] = SILENT;
	msglvl[INF] = VISUAL;
	msglvl[WRN] = VISUAL;
	msglvl[ERR] = VISUAL;
	msglvl[FAT] = VISUAL;

	if(styletype=="atlas") atlstyle();
	else                   style(); // noam's style
	
	//// no interf, no width scale
	// TString fname1 = "/data/hod/2011/functions/functions_APR25_v70mm_v4ee/ZPmm_nointerference_3332st_functions_g4bins_npx800.root";
	// TString fname2 = "/data/hod/2011/functions/functions_APR25_v70mm_v4ee/ZPmm_nointerference_noscalewidth_3332st_functions_g4bins_npx800.root";
	// TString fname3 = "";
	// TString oname1 = "ZPmm_nointerference_";
	// TString oname2 = "ZPmm_nointerference_noscalewidth_";
	// TString oname3 = "";

	//// no interf, no width scale
	TString fname00 = "/data/hod/2011/functions/functions_APR25_v70mm_v4ee/ZPmm_nointerference_nowidthscaling_functions_g4bins_npx800.root";
	TString fname01 = "/data/hod/2011/functions/functions_APR25_v70mm_v4ee/ZPmm_nointerference_functions_g4bins_npx800.root";
	TString fname1  = "/data/hod/2011/functions/functions_APR25_v70mm_v4ee/ZPmm_functions_g4bins_npx800.root";
	TString fname2  = "/data/hod/2011/functions/functions_APR25_v70mm_v4ee/KKmm_functions_g4bins_npx400.root";
	TString fname3  = "/data/hod/2011/functions/functions_APR25_v70mm_v4ee/KKmm_functions_g2bins_npx400.root";
	TString oname00 = "ZPmm_nointerf_nowidthscale";
	TString oname01 = "ZPmm_nointerf";
	TString oname1  = "ZPmm_";
	TString oname2  = "KKmm_g4_";
	TString oname3  = "KKmm_g2_";
	
	TString imass = (TString)_s(uiXmass);
	TString mass  = (TString)_s(uiXmass*100.+130.);

	Float_t phi = -25;
	
	TH2D* h00 = (TH2D*)getTemplate(fname00,uiXmass,"ZP4NOINT")->Clone();
	TH2D* h01 = (TH2D*)getTemplate(fname01,uiXmass,"ZP4NOINTNOSCL")->Clone();
	TH2D* h1  = (TH2D*)getTemplate(fname1,uiXmass,"ZP4")->Clone();
	TH2D* h2  = (TH2D*)getTemplate(fname2,uiXmass,"KK4")->Clone();
	TH2D* h3  = (TH2D*)getTemplate(fname3,uiXmass,"KK2")->Clone();
	plottemplate(h00, "plots/template2d_"+oname00+mass+"GeV",phi,true);
	plottemplate(h01, "plots/template2d_"+oname01+mass+"GeV",phi,true);
	plottemplate(h1, "plots/template2d_"+oname1+mass+"GeV",phi,true);
	plottemplate(h2, "plots/template2d_"+oname2+mass+"GeV",phi,true);
	plottemplate(h3, "plots/template2d_"+oname3+mass+"GeV",phi,true);
	
	TString syst = "PDF";
	//h00 = (TH2D*)getSyst(fname00,syst,uiXmass,"ZP4NOINT")->Clone();
	//h01 = (TH2D*)getSyst(fname01,syst,uiXmass,"ZP4NOINTNOSCL")->Clone();
	h1 = (TH2D*)getSyst(fname1,syst,uiXmass,"ZP4")->Clone();
	h2 = (TH2D*)getSyst(fname2,syst,uiXmass,"KK4")->Clone();
	h3 = (TH2D*)getSyst(fname3,syst,uiXmass,"KK2")->Clone();
	h00->GetZaxis()->SetTitle("Rel "+syst+" syst.");
	h01->GetZaxis()->SetTitle("Rel "+syst+" syst.");
	h1->GetZaxis()->SetTitle("Rel "+syst+" syst.");
	h2->GetZaxis()->SetTitle("rel "+syst+" syst.");
	h3->GetZaxis()->SetTitle("rel "+syst+" syst.");
	//plottemplate(h00, "plots/template2d_"+oname00+mass+"GeV"+"_syst"+syst,phi,true);
	//plottemplate(h01, "plots/template2d_"+oname01+mass+"GeV"+"_syst"+syst,phi,true);
	plottemplate(h1, "plots/template2d_"+oname1+mass+"GeV"+"_syst"+syst,phi,true);
	plottemplate(h2, "plots/template2d_"+oname2+mass+"GeV"+"_syst"+syst,phi,true);
	plottemplate(h3, "plots/template2d_"+oname3+mass+"GeV"+"_syst"+syst,phi,true);
	
	syst = "Zxs";
	//h00 = (TH2D*)getSyst(fname00,syst,uiXmass,"ZP4NOINT")->Clone();
	//h01 = (TH2D*)getSyst(fname01,syst,uiXmass,"ZP4NOINTNOSCL")->Clone();
	h1 = (TH2D*)getSyst(fname1,syst,uiXmass,"ZP4")->Clone();
	h2 = (TH2D*)getSyst(fname2,syst,uiXmass,"KK4")->Clone();
	h3 = (TH2D*)getSyst(fname3,syst,uiXmass,"KK2")->Clone();
	h1->GetZaxis()->SetTitle("Rel "+syst+" syst.");
	h2->GetZaxis()->SetTitle("rel "+syst+" syst.");
	h3->GetZaxis()->SetTitle("rel "+syst+" syst.");
	//plottemplate(h00, "plots/template2d_"+oname00+mass+"GeV"+"_syst"+syst,phi,false);
	//plottemplate(h01, "plots/template2d_"+oname01+mass+"GeV"+"_syst"+syst,phi,false);
	plottemplate(h1, "plots/template2d_"+oname1+mass+"GeV"+"_syst"+syst,phi,false);
	plottemplate(h2, "plots/template2d_"+oname2+mass+"GeV"+"_syst"+syst,phi,false);
	plottemplate(h3, "plots/template2d_"+oname3+mass+"GeV"+"_syst"+syst,phi,false);
	
	syst = "mmRes";
	//h00 = (TH2D*)getSyst(fname00,syst,uiXmass,"ZP4NOINT")->Clone();
	//h01 = (TH2D*)getSyst(fname01,syst,uiXmass,"ZP4NOINTNOSCL")->Clone();
	h1 = (TH2D*)getSyst(fname1,syst,uiXmass,"ZP4")->Clone();
	h2 = (TH2D*)getSyst(fname2,syst,uiXmass,"KK4")->Clone();
	h3 = (TH2D*)getSyst(fname3,syst,uiXmass,"KK2")->Clone();
	h1->GetZaxis()->SetTitle("Rel "+syst+" syst.");
	h2->GetZaxis()->SetTitle("rel "+syst+" syst.");
	h3->GetZaxis()->SetTitle("rel "+syst+" syst.");
	//plottemplate(h00, "plots/template2d_"+oname00+mass+"GeV"+"_syst"+syst,phi,false);
	//plottemplate(h01, "plots/template2d_"+oname01+mass+"GeV"+"_syst"+syst,phi,false);
	plottemplate(h1, "plots/template2d_"+oname1+mass+"GeV"+"_syst"+syst,-phi,false);
	plottemplate(h2, "plots/template2d_"+oname2+mass+"GeV"+"_syst"+syst,-phi,false);
	plottemplate(h3, "plots/template2d_"+oname3+mass+"GeV"+"_syst"+syst,-phi,false);
	

	/*
	TCanvas* c1 = new TCanvas("c1","c1",600,400);
	c1->cd();
	c1->Draw();
	c1->SetLogx();
	c1->SetLogz();
	h1->SetTitle("");
	// h1->GetXaxis()->SetMoreLogLabels();
	// h1->GetXaxis()->SetNoExponent();
	h1->RebinY(4);
	// h1->SetFillColor(kOrange);
	// h1->Draw("SURF4");
	h1->Draw("SURF");
	c1->SetPhi(phi);
	c1->Modified();
	c1->Update();
	c1->SaveAs("plots/template2d_"+oname1+mass+"GeV.png");
	c1->SaveAs("plots/template2d_"+oname1+mass+"GeV.eps");
	
	TCanvas* c2 = new TCanvas("c2","c2",600,400);
	c2->cd();
	c2->Draw();
	c2->SetLogx();
	c2->SetLogz();
	h2->SetTitle("");
	// h2->GetXaxis()->SetMoreLogLabels();
	// h2->GetXaxis()->SetNoExponent();
	h2->RebinY(4);
	// h2->SetFillColor(kOrange);
	// h2->Draw("SURF4");
	h2->Draw("SURF");
	c2->SetPhi(phi);
	c2->Modified();
	c2->Update();
	c2->SaveAs("plots/template2d_"+oname2+mass+"GeV.png");
	c2->SaveAs("plots/template2d_"+oname2+mass+"GeV.eps");
	*/
}
