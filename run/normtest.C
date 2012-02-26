#include "../include/rawStd.h"
#include "../include/rawROOT.h"
#include "../include/logs.h"
#include "../include/bins.h"

TString model  = "ZP";
TString mutype = "33st";
TString binning = "linearbins";
bool doGrid = true;
TString version = (doGrid) ? "v19" : "";

inline TH1D* hGeV2TeV(TH1D* hGeV)
{
	const Int_t    nbins = hGeV->GetNbinsX();
	Double_t bins[nbins+1];
	TAxis* xaxis = (TAxis*)hGeV->GetXaxis();
	TAxis* yaxis = (TAxis*)hGeV->GetYaxis();

	for(int i=0 ; i<nbins ; i++)
	{
		bins[i] = xaxis->GetBinLowEdge(i+1)/1000.;
		cout << "|" << bins[i];
	}
	bins[nbins] = xaxis->GetBinUpEdge(nbins)/1000.;
	cout << "|" << bins[nbins] << "|" << endl; 
	
	TString name   = (TString)hGeV->GetName();
	TString title  = (TString)hGeV->GetTitle();
	TString xtitle = (TString)xaxis->GetTitle();
	TString ytitle = (TString)yaxis->GetTitle();
	
	TH1D* hTeV = new TH1D(name+"_TeV",title+";"+xtitle+";"+ytitle, nbins,bins);
	for(Int_t b=0 ; b<=nbins+1 ; b++) hTeV->SetBinContent(b, hGeV->GetBinContent(b));
	return hTeV;
}

inline TH1D* hTeV2GeV(TH1D* hTeV)
{
	const Int_t    nbins = hTeV->GetNbinsX();
	Double_t bins[nbins+1];
	TAxis* xaxis = (TAxis*)hTeV->GetXaxis();
	TAxis* yaxis = (TAxis*)hTeV->GetYaxis();

	for(int i=0 ; i<nbins ; i++)
	{
		bins[i] = xaxis->GetBinLowEdge(i+1)*1000.;
		cout << "|" << bins[i];
	}
	bins[nbins] = xaxis->GetBinUpEdge(nbins)*1000.;
	cout << "|" << bins[nbins] << "|" << endl; 
	
	TString name   = (TString)hTeV->GetName();
	TString title  = (TString)hTeV->GetTitle();
	TString xtitle = (TString)xaxis->GetTitle();
	TString ytitle = (TString)yaxis->GetTitle();
	
	TH1D* hGeV = new TH1D(name+"_TeV",title+";"+xtitle+";"+ytitle, nbins,bins);
	for(Int_t b=0 ; b<=nbins+1 ; b++) hGeV->SetBinContent(b, hTeV->GetBinContent(b));
	return hGeV;
}

void normtest()
{
	msglvl[DBG] = SILENT;
	msglvl[INF] = VISUAL;
	msglvl[WRN] = VISUAL;
	msglvl[ERR] = VISUAL;
	msglvl[FAT] = VISUAL;

	Int_t g4bin   = 1; //==> g^4=0 ==> DY !
	Int_t minMbin = 25; //~80 GeV
	Int_t maxMbin = 40; //~128 GeV
	TString modelNmae = (model=="ZP") ? "Zprime_SSM" : "KK";
	unsigned int precision = 10.;
	
	Int_t maxMassPointsIndex = (Int_t)((mXXmax-mXXmin)/dmXX);

	TString fBGname = (mutype=="33st") ? "plots/DimuonHists_Feb05_3stC.root" : "plots/DimuonHists_Feb05_2stC.root";
	TFile* fD = new TFile(fBGname,"READ");
	TH1D* h1dy      = (TH1D*)fD->Get("ZLogmass_DYmm")->Clone();
	TH1D* h1dummy   = (TH1D*)fD->Get("ZLogmass_DYmm")->Clone("dummy");
	h1dummy->Reset();

	TCanvas* c = new TCanvas("c","c",600,400);
	c->cd();
	c->Draw();
	c->SetLogy();
	c->SetLogx();
	c->SetGridy();

	h1dy->SetLineColor(kBlue);
	h1dy->Draw();
	
	Double_t lowerLimit = -1;
	Double_t upperLimit = -1;
	
	
	Double_t sumDYmm = 0.;
	for(Int_t bin=minMbin ; bin<=maxMbin ; bin++) sumDYmm += (h1dy->GetBinContent(bin));
	
	TString gridFile = "plots/"+binning+"/"+mutype+"_nominal/"+version+"/"+model+"_combined_"+version+".root";
	TString infName = (doGrid) ? gridFile : "plots/"+binning+"/"+mutype+"_nominal/"+model+"_combined_2dtemplates_mc11c_"+mutype+"_overallEWkF_noInAmpSigEWkF_noHighMbins_noTruth.root";	
	TFile* fT = new TFile(infName,"READ");
	TObjArray* toartmp = new TObjArray();
	toartmp->Read("template2d");
	TH2D* h2T = (TH2D*)((TH2D*)(TObjArray*)toartmp->At(0))->Clone();
	for(Int_t bin=1 ; bin<=h1dummy->GetNbinsX() ; bin++)
	{
		if(bin==minMbin)   lowerLimit = h1dummy->GetBinLowEdge(bin);
		if(bin==maxMbin+1) upperLimit = h1dummy->GetBinLowEdge(bin);
		h1dummy->SetBinContent(bin,h2T->GetBinContent(bin,g4bin)); // g^4 = 0 -> DY !
	}
	
	Double_t sumTEMPLATE = 0.;
	for(Int_t bin=minMbin ; bin<=maxMbin ; bin++) sumTEMPLATE += (h1dummy->GetBinContent(bin));
	_INFO("----- summary -----");
	_INFO("Range: "+_s(lowerLimit)+"["+_s(minMbin)+"] TeV -> "+_s(upperLimit)+"["+_s(maxMbin)+"] TeV");
	_INFO((string)model+" -> sum(data)/sum(bgNoDY+DYfromTemplate(g^4=0)) = "+_s(sumDYmm/sumTEMPLATE,precision));
	
	TLine* l1 = new TLine(h1dummy->GetXaxis()->GetBinLowEdge(minMbin),0,h1dummy->GetXaxis()->GetBinLowEdge(minMbin),1.e7);
    TLine* l2 = new TLine(h1dummy->GetXaxis()->GetBinUpEdge(maxMbin),0,h1dummy->GetXaxis()->GetBinUpEdge(maxMbin),1.e7);
    TLine* l3 = new TLine(250,0,250,1.e7);
    l1->SetLineColor(kGreen+2);
    l2->SetLineColor(kGreen+2);
    l3->SetLineColor(kViolet);
	h1dummy->SetLineColor(kRed);	
	h1dummy->SetLineWidth(2);	
	h1dummy->Draw("SAMES");
	l1->Draw("SAMES");
    l2->Draw("SAMES");
    l3->Draw("SAMES");
	c->SaveAs("dy_comparison.png");
	
	TCanvas* c1 = new TCanvas("c1","c1",600,400);
	c1->cd();
	c1->Draw();
	c1->SetLogx();
	c1->SetGridy();
	TH1D* hratio = (TH1D*)h1dy->Clone("hratio");
	TH1D* h1dummyGeV = (TH1D*)hTeV2GeV(h1dummy)->Clone("dummyGeV");
	hratio->SetMinimum(0.5);
	hratio->SetMaximum(1.5);
	hratio->SetName("hratio");
	hratio->Divide(h1dummyGeV);
	TLine* line = new TLine(h1dummyGeV->GetXaxis()->GetBinLowEdge(1),1,h1dummyGeV->GetXaxis()->GetBinUpEdge(h1dummyGeV->GetNbinsX()),1);
	hratio->SetMarkerStyle(20);
	hratio->SetMarkerSize(0.8);
	hratio->Draw("ep1");
	line->Draw("SAMES");
	l1->Draw("SAMES");
	l2->Draw("SAMES");
	l3->Draw("SAMES");
	c1->RedrawAxis();
	c1->SaveAs("dy_ratio.png");
	
	
	TFile* fratio = new TFile("dyratio_Feb2.root", "RECREATE");
	hratio->Write();
	fratio->Write();
	fratio->Close();
}
