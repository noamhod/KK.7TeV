#include "../include/rawStd.h"
#include "../include/rawROOT.h"
#include "../include/logs.h"
#include "../include/bins.h"

TString model  = "ZP";
TString mutype = "3332st";
TString binning = "linearbins";
TString gNbinning = "g2bins";
bool doGrid = false;
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
		//cout << "|" << bins[i];
	}
	bins[nbins] = xaxis->GetBinUpEdge(nbins)/1000.;
	//cout << "|" << bins[nbins] << "|" << endl; 
	
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
		//cout << "|" << bins[i];
	}
	bins[nbins] = xaxis->GetBinUpEdge(nbins)*1000.;
	//cout << "|" << bins[nbins] << "|" << endl; 
	
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

	Int_t gNbin   = 1; //==> g^4=0 ==> DY !
	Int_t minMbin = 25; //~80 GeV
	Int_t maxMbin = 40; //~128 GeV
	TString modelNmae = (model=="ZP") ? "Zprime_SSM" : "KK";
	unsigned int precision = 10.;
	
	Int_t maxMassPointsIndex = (Int_t)((mXXmax-mXXmin)/dmXX);

	TString fBGname1 = "";
	TString fBGname2 = "";
	if     (mutype=="33st") fBGname1 = "plots/DimuonHists_Feb05_3stC.root";
	else if(mutype=="32st") fBGname1 = "plots/DimuonHists_Feb05_2stC.root";
	else if(mutype=="3332st")
	{
		fBGname1 = "plots/DimuonHists_Feb05_3stC.root";
		fBGname2 = "plots/DimuonHists_Feb05_2stC.root";
	}
	TFile* fD1 = new TFile(fBGname1,"READ");
	TH1D* h1dy = (TH1D*)fD1->Get("ZLogmass_DYmm")->Clone();
	if(mutype=="3332st")
	{
		_INFO("Adding the 3+2 DY histogram");
		TFile* fD2 = new TFile(fBGname2,"READ");
		TH1D* h1dy32st = (TH1D*)fD2->Get("ZLogmass_DYmm")->Clone();
		h1dy->Add(h1dy32st);
		_INFO("done");
	}
	TH1D* h1template = (TH1D*)fD1->Get("ZLogmass_DYmm")->Clone("template");
	h1template->Reset();

	Double_t lowerLimit = -1;
	Double_t upperLimit = -1;
	
	Double_t sumDYmm = 0.;
	for(Int_t bin=minMbin ; bin<=maxMbin ; bin++) sumDYmm += (h1dy->GetBinContent(bin));
	 
	TString infName = "plots/linearbins/g2bins/3332st_nominal/ZP_2dtemplates_mc11c_3332st_g2bins_noKKtmplates_noTruth_Xmass1030.root";
	TFile* fT = new TFile(infName,"READ");
	TObjArray* toartmp = new TObjArray();
	toartmp->Read("template2d");
	TH2D* h2T = (TH2D*)((TH2D*)(TObjArray*)toartmp->At(0))->Clone();
	for(Int_t bin=1 ; bin<=h1template->GetNbinsX() ; bin++)
	{
		if(bin==minMbin)   lowerLimit = h1template->GetBinLowEdge(bin);
		if(bin==maxMbin+1) upperLimit = h1template->GetBinLowEdge(bin);
		h1template->SetBinContent(bin,h2T->GetBinContent(bin,gNbin)); // g^4=0 or g^2=0 -> DY !
		h1template->SetBinError(bin,h2T->GetBinError(bin,gNbin));
	}
	
	Double_t sumTEMPLATE = 0.;
	for(Int_t bin=minMbin ; bin<=maxMbin ; bin++) sumTEMPLATE += (h1template->GetBinContent(bin));
	_INFO("----- summary -----");
	_INFO("Range: "+_s(lowerLimit)+"["+_s(minMbin)+"] TeV -> "+_s(upperLimit)+"["+_s(maxMbin)+"] TeV");
	_INFO((string)model+" -> sum(data)/sum(bgNoDY+DYfromTemplate(g^4=0)) = "+_s(sumDYmm/sumTEMPLATE,precision));




	TCanvas* c = new TCanvas("c","c",600,400);
        c->cd();
        c->Draw();
        c->SetLogy();
        c->SetLogx();
        c->SetGridy();
	TLine* l1 = new TLine(h1template->GetXaxis()->GetBinLowEdge(minMbin),0,h1template->GetXaxis()->GetBinLowEdge(minMbin),1.e7);
	TLine* l2 = new TLine(h1template->GetXaxis()->GetBinUpEdge(maxMbin),0,h1template->GetXaxis()->GetBinUpEdge(maxMbin),1.e7);
	TLine* l3 = new TLine(250,0,250,1.e7);
	l1->SetLineColor(kGreen+2);
	l2->SetLineColor(kGreen+2);
	l3->SetLineColor(kViolet);
	h1dy->SetLineColor(kBlue);
	h1dy->SetLineWidth(1);
	h1dy->SetMarkerColor(kBlue);
	h1dy->SetMarkerSize(0.3);
	h1dy->SetMarkerStyle(2);
	h1dy->Draw();
	h1template->SetLineColor(kRed);
	h1template->SetLineWidth(1);
	h1template->SetMarkerColor(kRed);
	h1template->SetMarkerSize(0.3);
	h1template->SetMarkerStyle(2);
	h1template->Draw("SAMES");
	l1->Draw("SAMES");
	l2->Draw("SAMES");
	l3->Draw("SAMES");
	c->SaveAs("dy_comparison.png");
	
	TCanvas* c1 = new TCanvas("c1","c1",600,400);
	c1->cd();
	c1->Draw();
	c1->SetLogx();
	c1->SetGridy();
	TH1D* hratio        = (TH1D*)h1dy->Clone("hratio");
	TH1D* h1templateGeV = (TH1D*)hTeV2GeV(h1template)->Clone("GeV");
	hratio->SetMinimum(0.5);
	hratio->SetMaximum(1.5);
	hratio->SetName("hratio");
	hratio->Divide(h1templateGeV);
	TLine* line = new TLine(h1templateGeV->GetXaxis()->GetBinLowEdge(1),1,h1templateGeV->GetXaxis()->GetBinUpEdge(h1templateGeV->GetNbinsX()),1);
	hratio->SetMarkerStyle(20);
	hratio->SetMarkerSize(0.5);
	hratio->Draw("ep1");
	line->Draw("SAMES");
	l1->Draw("SAMES");
	l2->Draw("SAMES");
	l3->Draw("SAMES");
	c1->RedrawAxis();
	c1->SaveAs("dy_ratio.png");

	/*
	TFile* fratio = new TFile("dyratio.root", "RECREATE");
	hratio->Write();
	fratio->Write();
	fratio->Close();
	*/
}
