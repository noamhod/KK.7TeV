#include "../include/rawStd.h"
#include "../include/rawROOT.h"
#include "../include/logs.h"
#include "../include/bins.h"
#include "../include/style.h"
#include "../include/histos.h"

///////////////////////////////////
// USAGE: /////////////////////////
// root -b -l -q TH1toTF1.C++ /////
///////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////
// Global definitions ///////////////////////////////////////////////////////////////////////
TString ftype = "2dtemplates_fastDY_smallDY_noEWkFsig_sigEWkf_noHighMbins_noTruth";
TString dir   = "plots/";

Double_t xmin = g4min; // =0
Double_t xmax = g4max; // =100

TString model   = "KK";     // ZP or KK
TString channel = "#mu#mu"; // #mu#mu or ee

Double_t scale2Zpeak = 1.14527; // muon, not final 

TFile* f2DTemplate;
TObjArray* tobjarr;
/////////////////////////////////////////////////////////////////////////////////////////////

void init()
{
	f2DTemplate = new TFile(dir+model+"_"+ftype+".root","READ");
	tobjarr = new TObjArray();
	tobjarr->Read("template2d");
}

TH1D* TH2toTH1(TH2D* h2, Int_t massbin)
{
	TString massbinname = (TString)_s(massbin);
	TString origname = (TString)h2->GetName();
	origname.ReplaceAll("hg4Mass_template_","");
	TString name = origname+"_mll_"+massbinname;
	Double_t min = h2->GetYaxis()->GetXmin();
	Double_t max = h2->GetYaxis()->GetXmax();
	Int_t nbins = h2->GetNbinsY();
	TH1D* h1 = new TH1D(name,"#frac{dN}{dg^{4}};g^{4};dN/dg^{4}",nbins,min,max);
	for(Int_t bin=1 ; bin<=nbins ; bin++)
	{
		h1->SetBinContent(bin, h2->GetBinContent(massbin+bins2chop,bin));
	}
	return h1;
}

Double_t fTH1toTF1(Double_t *x, Double_t *par)
{
	Double_t     g4  = x[0];                    // -> g^4 value
	unsigned int mX  = (unsigned int)par[0];    // -> Z' / KK mass (template running number)
	Int_t        mll = (Int_t)par[1];           // -> dilepton invariant mass bin number
	TH2D* h2         = (TH2D*)((TH2D*)(TObjArray*)tobjarr->At(mX)); // the 2d histogram (pole mass point)
	TH1D* hTmp       = (TH1D*)TH2toTH1(h2,mll); // get the TH1 histogram of g^4 in the dilepton mass bin number mll
	hTmp->Scale(scale2Zpeak);
	Double_t xxval   = hTmp->Interpolate(g4);   // get the interpolated value of dN/dg^4 at the given g^4
	delete hTmp;
	return xxval;
}

void TH1toTF1()
{
	msglvl[DBG] = SILENT;
	msglvl[INF] = VISUAL;
	msglvl[WRN] = VISUAL;
	msglvl[ERR] = VISUAL;
	msglvl[FAT] = VISUAL;
	
	style();

	TDirectory* oldDir = gDirectory; // remember old directory
	
	init();
	
	/*
	TH2D* h2 = (TH2D*)((TH2D*)(TObjArray*)tobjarr->At(0))->Clone();
	
	TH1D* h1z0  = (TH1D*)(TH2toTH1(h2,4))->Clone("");
	h1z0->Scale(1./h1z0->Integral());
	h1z0->SetLineColor(kBlack);
	TH1D* h1lowDY  = (TH1D*)(TH2toTH1(h2,19))->Clone("");
	h1lowDY->Scale(1./h1lowDY->Integral());
	h1lowDY->SetLineColor(kGreen+2);
	TH1D* h1dip  = (TH1D*)(TH2toTH1(h2,43))->Clone("");
	h1dip->Scale(1./h1dip->Integral());
	h1dip->SetLineColor(kBlue);
	TH1D* h1peak = (TH1D*)(TH2toTH1(h2,50))->Clone("");
	h1peak->Scale(1./h1peak->Integral());
	h1peak->SetLineColor(kRed);
	TH1D* h1highDY = (TH1D*)(TH2toTH1(h2,56))->Clone("");
	h1highDY->Scale(1./h1highDY->Integral());
	h1highDY->SetLineColor(kOrange);
	
	TString newtitle = "#frac{1}{N}#times"+(TString)h1highDY->GetTitle();
	TString newytitle = "1/N #times "+(TString)h1highDY->GetYaxis()->GetTitle();
	h1z0->SetTitle(newtitle);
	h1z0->GetYaxis()->SetTitle(newytitle);
	h1lowDY->SetTitle(newtitle);
	h1lowDY->GetYaxis()->SetTitle(newytitle);
	h1dip->SetTitle(newtitle);
	h1dip->GetYaxis()->SetTitle(newytitle);
	h1peak->SetTitle(newtitle);
	h1peak->GetYaxis()->SetTitle(newytitle);
	h1highDY->SetTitle(newtitle);
	h1highDY->GetYaxis()->SetTitle(newytitle);
	
	TLegend* leg = new TLegend(0.4,0.17,0.83,0.63,NULL,"brNDC");
	leg->SetFillStyle(4000); //will be transparent
	leg->SetFillColor(0);
	leg->SetTextFont(42);
	leg->AddEntry(h1z0,"m_{"+channel+"} #approx 90 GeV (Z^{0})");
	leg->AddEntry(h1lowDY,"m_{"+channel+"} #approx 250 GeV (low DY)");
	leg->AddEntry(h1dip,"m_{"+channel+"} #approx 1000 GeV (KK dip)");
	leg->AddEntry(h1peak,"m_{"+channel+"} #approx 2000 GeV (KK peak)");
	leg->AddEntry(h1highDY,"m_{"+channel+"} #approx 3000 GeV (high DY)");
	
	TCanvas* c = new TCanvas("c","c",900,400);
	c->Divide(2,1);
	c->Draw();
	TVirtualPad* p1 = c->cd(1);
	TVirtualPad* p2 = c->cd(2);
	p1->SetTicks(1,1);
	p2->SetTicks(1,1);
	p1->SetLogy();
	p2->SetLogx();
	p2->SetLogz();
	p1->cd();
	p1->Draw();
	h1z0->Draw();
	h1z0->GetYaxis()->SetRangeUser(0.0005,0.1);
	h1lowDY->Draw("SAMES");
	h1lowDY->GetYaxis()->SetRangeUser(0.0005,0.1);
	h1dip->Draw("SAMES");
	h1dip->GetYaxis()->SetRangeUser(0.0005,0.1);
	h1peak->Draw("SAMES");
	h1peak->GetYaxis()->SetRangeUser(0.0005,0.1);
	h1highDY->GetYaxis()->SetRangeUser(0.0005,0.1);
	h1highDY->Draw("SAMES");
	h1highDY->GetYaxis()->SetMoreLogLabels();
	leg->Draw("SAMES");
	p1->RedrawAxis();
	p2->cd();
	h2->Draw("SURF1");
	h2->SetTitle("#frac{dN}{dg^{4}dm_{"+channel+"}}");
	p1->Update();
	p2->Update();
	c->Update();
	c->SaveAs("plots/TH2toTH1_"+model+".png");
	
	_INFO("----------------------------------------------------------");
	
	oldDir->cd();
	
	unsigned int polemass = 0;
	unsigned int massbin = 43;
	
	TF1 *f1 = new TF1("f1",fTH1toTF1,xmin,xmax,2);
	f1->SetParameters(polemass,massbin);
	f1->SetParNames("mX","mll");
	TH1D* h1 = (TH1D*)(TH2toTH1(h2,massbin))->Clone("");
	h1->SetLineColor(kRed);
	
	TFile* file = new TFile("plots/TH2toTH1toTF1_"+model+".root","RECREATE");	
	f1->Write();
	file->Write();
	file->Close();
	
	TCanvas* ctest = new TCanvas("ctest","ctest",600,400);
	ctest->cd();
	ctest->Draw();
	f1->Draw();
	h1->Draw("SAMES");
	ctest->SaveAs("plots/TH1toTF1_"+model+".png");
	
	_INFO("----------------------------------------------------------");
	
	*/
	
	oldDir->cd();
	
	TFile* funcfile = new TFile("plots/"+model+"_functions.root","RECREATE");
	unsigned int ntemplates   = (unsigned int)tobjarr->GetSize();
	unsigned int lasttemplate = (unsigned int)tobjarr->GetLast();
	for(unsigned int mX=0 ; mX<ntemplates && mX<=lasttemplate ; mX++)
	{
		TString mXname = (TString)_s(mX);
		TString mXval  = (TString)_s(mXXmin+mX*dmXX);
		
		TDirectory* dirX = funcfile->mkdir(mXname);
		dirX->cd();
		
		TH2D* h2X = (TH2D*)((TH2D*)(TObjArray*)tobjarr->At(mX))->Clone();
		if(h2X==NULL) _FATAL("h2X is NULL at mX="+(string)mXname);
		unsigned int nbins = h2X->GetNbinsX(); // 56
		for(unsigned int mll=1 ; mll<=(nbins-bins2chop) ; mll++) // 1...(56-9 = 47)
		{
			TString mllname = (TString)_s(mll);
			TString mllval  = (TString)_s(h2X->GetXaxis()->GetBinCenter(mll+bins2chop));
			
			TF1 *f1 = new TF1("fmX"+mXname+"_mll"+mllname,fTH1toTF1,xmin,xmax,2);
			f1->SetParameters(mX,mll);
			f1->SetParNames("mX","mll");
			f1->SetLineColor(kBlue);
			f1->SetLineWidth(1);
			TH1D* h1 = (TH1D*)(TH2toTH1(h2X,mll))->Clone("");
			h1->SetLineColor(kRed);
			TCanvas* c1 = new TCanvas("cmX"+mXname+"_mll"+mllname,"",600,400);
			c1->cd();
			c1->Draw();
			f1->Draw();
			h1->SetTitle("dN/dg^{4} in mX="+mXval+" GeV and m_{"+channel+"}="+mllval+" TeV");
			h1->GetXaxis()->SetTitle("g^{4}");
			h1->GetYaxis()->SetTitle("dN/dg^{4}");
			h1->Draw("SAMES");
			c1->Write();
			f1->Write();
			h1->Write();
			
			delete h1;
			delete f1;
			delete c1;
		}
		
		TCanvas* c2 = new TCanvas("cmX"+mXname,"",600,400);
		c2->Draw();
		c2->cd();
		c2->SetLogx();
		c2->SetLogz();
		h2X->SetTitle("#frac{dN}{dg^{4}dm_{"+channel+"}}");
		h2X->Draw("SURF1");
		c2->Write();
		h2X->Write();
		
		delete h2X;
		delete c2;
	}
	funcfile->Write();
	funcfile->Close();
}
