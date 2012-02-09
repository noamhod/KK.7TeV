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

void validation()
{
	msglvl[DBG] = SILENT;
	msglvl[INF] = VISUAL;
	msglvl[WRN] = VISUAL;
	msglvl[ERR] = VISUAL;
	msglvl[FAT] = VISUAL;

	style();

	Int_t g4bin = 2; //==> g^4=1 ==> SSM !
	
	TString fBGname = "plots/ZP_2dtemplates_mc11c_33st_overallEWkF_noInAmpSigEWkF_noHighMbins_noTruth_wthOfficialZP_Xmass2000.root";
	TFile* fD = new TFile(fBGname,"READ");
	TMapTSP2TH1D h1Map;
	h1Map.insert( make_pair("1000o", (TH1D*)fD->Get("hMass_Zprime_SSM1000")->Clone()) );
	h1Map.insert( make_pair("1000t", (TH1D*)fD->Get("hMass_Zprime_SSM1000_template")->Clone()) );
	h1Map.insert( make_pair("1250o", (TH1D*)fD->Get("hMass_Zprime_SSM1250")->Clone()) );
	h1Map.insert( make_pair("1250t", (TH1D*)fD->Get("hMass_Zprime_SSM1250_template")->Clone()) );
	h1Map.insert( make_pair("1500o", (TH1D*)fD->Get("hMass_Zprime_SSM1500")->Clone()) );
	h1Map.insert( make_pair("1500t", (TH1D*)fD->Get("hMass_Zprime_SSM1500_template")->Clone()) );
	h1Map.insert( make_pair("1750o", (TH1D*)fD->Get("hMass_Zprime_SSM1750")->Clone()) );
	h1Map.insert( make_pair("1750t", (TH1D*)fD->Get("hMass_Zprime_SSM1750_template")->Clone()) );
	h1Map.insert( make_pair("2000o", (TH1D*)fD->Get("hMass_Zprime_SSM2000")->Clone()) );
	h1Map.insert( make_pair("2000t", (TH1D*)fD->Get("hMass_Zprime_SSM2000_template")->Clone()) );

	TMapTSP2TH1D h1rMap;
	h1rMap.insert( make_pair("1000", (TH1D*)fD->Get("hMass_Zprime_SSM1000")->Clone()) );
	h1rMap.insert( make_pair("1250", (TH1D*)fD->Get("hMass_Zprime_SSM1250")->Clone()) );
	h1rMap.insert( make_pair("1500", (TH1D*)fD->Get("hMass_Zprime_SSM1500")->Clone()) );
	h1rMap.insert( make_pair("1750", (TH1D*)fD->Get("hMass_Zprime_SSM1750")->Clone()) );
	h1rMap.insert( make_pair("2000", (TH1D*)fD->Get("hMass_Zprime_SSM2000")->Clone()) );
	for(TMapTSP2TH1D::iterator it=h1rMap.begin() ; it!=h1rMap.end() ; ++it)
	{
		it->second->Reset();
		it->second->Divide(h1Map[it->first+"o"],h1Map[it->first+"t"],1.,1.,"B");
		for(Int_t i=0 ; i<=it->second->GetNbinsX()+1 ; i++) it->second->SetBinError(i,0);
		it->second->SetMarkerStyle(20);
                it->second->SetMarkerSize(0.5);
                it->second->GetXaxis()->SetLabelSize(0.073);
                it->second->GetYaxis()->SetLabelSize(0.073);
                it->second->GetXaxis()->SetTitleSize(0.073);
                it->second->GetYaxis()->SetTitleSize(0.073);
                it->second->SetTitleSize(0.075);
                it->second->GetYaxis()->SetTitleOffset(0.5);
                it->second->SetMinimum(0.2);
                it->second->SetMaximum(1.8);
		it->second->SetTitle("");
                it->second->GetYaxis()->SetTitle("ratio");
	}

	TMapTSP2TGAE poissonGraphMap;
	TMapTSP2TLeg legMap;

	
	TH1D* h1Template = (TH1D*)fD->Get("hMass_DYmumu")->Clone();
	h1Template->Reset();

	TObjArray* toarr = new TObjArray();
	toarr->Read("template2d");
	TH2D* h2SSM2000 = (TH2D*)((TObjArray*)toarr->At(0))->Clone("hMass_Zprime_SSM1000_template2d");
	for(Int_t bin=1 ; bin<=h2SSM2000->GetNbinsX() ; bin++)
	{
		h1Template->SetBinContent(bin, h2SSM2000->GetBinContent(bin,g4bin));
	}
	h1Template->SetLineColor(kViolet);


	for(TMapTSP2TH1D::iterator it=h1Map.begin() ; it!=h1Map.end() ; ++it)
	{
		if(it->first.Contains("o"))
		{
			TString name = it->first;
			name.ReplaceAll("o","");
			it->second->SetFillColor(kAzure-9);
			it->second->SetTitle("m_{Z'} = "+name+" GeV");
		}
		if(it->first.Contains("t"))
		{
			//TGraphAsymmErrors* poisson(TH1D* h)
			it->second->SetLineColor(kBlue);
			it->second->SetLineWidth(2);
			it->second->SetMarkerStyle(20);
			it->second->SetMarkerSize(0.3);
			it->second->SetMarkerColor(kBlue);
			TString name = it->first;
			name.ReplaceAll("t","");
			poissonGraphMap.insert( make_pair(name, (TGraphAsymmErrors*)poisson(it->second)->Clone()) );
			poissonGraphMap[name]->SetMarkerStyle(20);
			poissonGraphMap[name]->SetMarkerSize(0.3);
			poissonGraphMap[name]->SetMarkerColor(kBlue);
			poissonGraphMap[name]->SetLineWidth(1);
			poissonGraphMap[name]->SetLineColor(kBlue);
		}
	}	

	TLine* line = new TLine(0.07,1.,3.,1.);	
       	line->SetLineColor(kRed);
	line->SetLineWidth(2);
	
	TMapTSP2TCNV cnvMap;
	cnvMap.insert( make_pair("1000", new TCanvas("1000","1000",600,550)) );
	cnvMap.insert( make_pair("1250", new TCanvas("1250","1250",600,550)) );
	cnvMap.insert( make_pair("1500", new TCanvas("1500","1500",600,550)) );
	cnvMap.insert( make_pair("1750", new TCanvas("1750","1750",600,550)) );
	cnvMap.insert( make_pair("2000", new TCanvas("2000","2000",600,550)) );
	for(TMapTSP2TCNV::iterator it=cnvMap.begin() ; it!=cnvMap.end() ; ++it)
	{
		_INFO("starting "+(string)it->first);
		legMap.insert( make_pair(it->first, new TLegend(0.4,0.7,0.85,0.8,NULL,"brNDC")) );
		legMap[it->first]->SetFillStyle(4000); //will be transparent
		legMap[it->first]->SetFillColor(0);
		legMap[it->first]->SetTextFont(42);
		legMap[it->first]->AddEntry(h1Map[it->first+"o"],"Official Z'_{SSM}","F");
		legMap[it->first]->AddEntry(h1Map[it->first+"t"],"Template w/o couplings scale","lep");
		if(it->first=="2000") legMap[it->first]->AddEntry(h1Template,"Template at g=1","l");

		it->second->Divide(1,2);
		TVirtualPad* ph = it->second->cd(1);
		TVirtualPad* pr = it->second->cd(2);	
		ph->SetPad(0.00, 0.35, 1.00, 1.00);
		pr->SetPad(0.00, 0.00, 1.00, 0.35);
		ph->SetBottomMargin(0.012);
		pr->SetBottomMargin(0.20);
		pr->SetTopMargin(0.012);
	
		ph->cd();
		ph->Draw();
		ph->SetTicks(1,1);
		ph->SetLogy();
		ph->SetLogx();
		//ph->SetGridy();
		h1Map[it->first+"o"]->SetMaximum( h1Map[it->first+"t"]->GetMaximum()*1.5 );
		h1Map[it->first+"o"]->Draw();
		//h1Map[it->first+"t"]->Draw("SAMES");
		poissonGraphMap[it->first]->Draw("pSAMES");
		if(it->first=="2000") h1Template->Draw("SAMES");
		legMap[it->first]->Draw("SAMES");
		ph->RedrawAxis();
		ph->Update();

		pr->cd();
		pr->Draw();
		pr->SetTicks(1,1);
		pr->SetGridy();
                pr->SetLogx();
		//line->Draw();
   		//h1rMap[it->first]->Draw("epSAMES");
                h1rMap[it->first]->Draw("ep");
		line->Draw("SAMES");
		pr->RedrawAxis();
                pr->Update();

		unsigned int savestate = 1;
		if(it->first=="1000")      savestate = 0;
		else if(it->first=="2000") savestate = 2;
		else                       savestate = 1;
		savemultipdf(it->second, "plots/validation.pdf", savestate);
		_INFO("done "+(string)it->first);
	}
}
