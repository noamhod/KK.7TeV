#include "../include/rawStd.h"
#include "../include/rawROOT.h"
#include "../include/logs.h"
#include "../include/bins.h"
#include "../include/style.h"
#include "../include/histos.h"

///////////////////////////////////
// USAGE: /////////////////////////
// Compile: root -b -l -q TH1toTF1.C++\(\"ZP\",-1\) /////
// Loop:    root -b -l -q TH1toTF1.C++\(\"ZP\",-2\)
// SINGLE:  root -b -l -q TH1toTF1.C++\(\"ZP\"\,19)
///////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////
// Global definitions ///////////////////////////////////////////////////////////////////////
bool doGrid         = false;
bool doInterference = false;
bool doHighMass     = true;
bool doKKtemplates  = false;
bool doArbitraryScale  = false;
TString mutype  = "33st";
TString binning = "linearbins";
TString version = (doGrid) ? "v30/" : "";
TString interference = (doInterference) ? "" : "_noInterference";
TString KKtemplates  = (doKKtemplates)  ? "" : "_noKKtmplates";
TString highmass     = (doHighMass)     ? "" : "_noHighMbins";
Double_t arbitraryScale = 1.15;    // arbitrary scale by 15%
TString sArbitraryScale = (doArbitraryScale) ? "_scaledBy"+(TString)_s((arbitraryScale-1)*100)+"percent" : "";
//TString fpath = (doGrid) ? "_combined_"+version+sArbitraryScale : "_combined_2dtemplates_mc11c_"+mutype+interference+KKtemplates+"_overallEWkF_noInAmpSigEWkF"+highmass+"_noTruth"; // for mc11c with the overall k-factor
// TString fpath = "_combined_2dtemplates_mc11c_33st_noInterference_noKKtmplates_noInAmpSigEWkF_treeLevelMass";
TString fpath = "_combined_2dtemplates_mc11c_33st_noInterference_noKKtmplates_noOverallEWkF_noTruth_treeLevelMass";
TString sDirNoint = (doInterference) ? "" : "nointerference/";
TString sDir  = "plots/"+sDirNoint+binning+"/"+mutype+"_nominal/"+version;

Double_t xmin = 0.; // g4min;
Double_t xmax = g4max; // TMath::Power(npowerbins*step,power); // g4max;

TString model   = "KK";     // ZP or KK
TString channel = "#mu#mu"; // #mu#mu or ee

bool doScale2Zpeak = false;
Double_t scale2Zpeak = (mutype=="33st") ? 1. : 1.;    // For linear bins, see normtest.C
bool doInterpolation = false;

Int_t npx = 2000;




//////////////////////////////////////////
TFile* f2DTemplate;
TObjArray* tobjarr;
TObjArray* tobjarr_syst_Zxs;
TObjArray* tobjarr_syst_PDF;
TObjArray* tobjarr_syst_EWkF;
TObjArray* tobjarr_syst_QCDkF;
TObjArray* tobjarr_syst_mmSlopeEff;
TObjArray* tobjarr_syst_eeIsoEff;
TObjArray* tobjarr_syst_mmRes;
TObjArray* tobjarr_syst_eeRes;

enum template_types
{
	NOMINAL,
	ZXS,
	PDF, EWKF, QCDKF, MMSLOPEFF, EEISOEFF, MMRES, EERES
};
/////////////////////////////////////////////////////////////////////////////////////////////

void init()
{
	f2DTemplate = new TFile(sDir+model+fpath+".root","READ");
	tobjarr = new TObjArray();
	tobjarr->Read("template2d");
	_INFO("nominal:    "+_s(tobjarr->GetLast()));
	tobjarr_syst_Zxs = new TObjArray();
	tobjarr_syst_Zxs->Read("template2d_Zxs_syst");
	_INFO("Zxs:        "+_s(tobjarr_syst_Zxs->GetLast()));
	tobjarr_syst_PDF = new TObjArray();
	tobjarr_syst_PDF->Read("template2d_PDF_syst");
	_INFO("PDF:        "+_s(tobjarr_syst_PDF->GetLast()));
	tobjarr_syst_EWkF = new TObjArray();
	tobjarr_syst_EWkF->Read("template2d_EWkF_syst");
	_INFO("EWkF:       "+_s(tobjarr_syst_EWkF->GetLast()));
	// tobjarr_syst_QCDkF = new TObjArray();
	// tobjarr_syst_QCDkF->Read("template2d_QCDkF_syst");
	// _INFO("QCDkF:   "+_s(tobjarr_syst_QCDkF->GetLast()));
	
	if(channel=="#mu#mu")
	{
		tobjarr_syst_mmSlopeEff = new TObjArray();
		tobjarr_syst_mmSlopeEff->Read("template2d_mmSlopeEff_syst");
		_INFO("mmSlopeEff: "+_s(tobjarr_syst_mmSlopeEff->GetLast()));
		if(doInterference)
		{
			tobjarr_syst_mmRes = new TObjArray();
			tobjarr_syst_mmRes->Read("template2d_mmRes_syst");
			_INFO("mmRes:      "+_s(tobjarr_syst_mmRes->GetLast()));
		}
	}
	if(channel=="ee")
	{
		tobjarr_syst_eeIsoEff = new TObjArray();
		tobjarr_syst_eeIsoEff->Read("template2d_eeIsoEff_syst");
		_INFO("eeIsoEff:   "+_s(tobjarr_syst_eeIsoEff->GetLast()));
		tobjarr_syst_eeRes = new TObjArray();
		tobjarr_syst_eeRes->Read("template2d_eeRes_syst");
		_INFO("eeRes:      "+_s(tobjarr_syst_eeRes->GetLast()));
	}
}

TH1D* TH2toTH1(TH2D* h2, Int_t massbin)
{
	TString massbinname = (TString)_s(massbin);
	TString origname = (TString)h2->GetName();
	origname.ReplaceAll("hg4Mass_template_","");
	TString name = origname+"_mll_"+massbinname;
	// Double_t min = h2->GetYaxis()->GetXmin();
	// Double_t max = h2->GetYaxis()->GetXmax();
	// Int_t nbins = h2->GetNbinsY();
	//------------------------------------------------------------
	const Int_t nbins = h2->GetNbinsY();
	Double_t bins[nbins+1];
	TAxis* yaxis = (TAxis*)h2->GetYaxis();
	for(int i=0 ; i<nbins ; i++) bins[i] = yaxis->GetBinLowEdge(i+1);
	bins[nbins] = yaxis->GetBinUpEdge(nbins);
	//------------------------------------------------------------
	TH1D* h1 = new TH1D(name,"#frac{dN}{dg^{4}};g^{4};dN/dg^{4}",nbins,bins);
	for(Int_t bin=1 ; bin<=nbins ; bin++)
	{
		h1->SetBinContent(bin, h2->GetBinContent(massbin+bins2chop,bin));
	}
	return h1;
}

Double_t fTH1toTF1(Double_t *x, Double_t *par)
{
	Double_t     g4  = x[0]; // -> g^4 value
	unsigned int mX  = (unsigned int)par[0];    // -> Z' / KK mass (template running number)
	Int_t        mll = (Int_t)par[1];           // -> dilepton invariant mass bin number
	unsigned int typ = (unsigned int)par[2];    // -> typ=nominal,Zxs,PDF,EWkF,QCDkF,mmSlopeEff,eeIsoEff (see the enum above)
	
	TH2D* h2 = NULL;  // the 2d histogram (pole mass point)
	switch(typ)
	{
		case NOMINAL:   h2 = (TH2D*)((TH2D*)(TObjArray*)tobjarr->At(mX))->Clone();                 break;
		case ZXS:       h2 = (TH2D*)((TH2D*)(TObjArray*)tobjarr_syst_Zxs->At(mX))->Clone();        break;
		case PDF:       h2 = (TH2D*)((TH2D*)(TObjArray*)tobjarr_syst_PDF->At(mX))->Clone();        break;
		case EWKF:      h2 = (TH2D*)((TH2D*)(TObjArray*)tobjarr_syst_EWkF->At(mX)->Clone());       break;
		// case QCDKF:  h2 = (TH2D*)((TH2D*)(TObjArray*)tobjarr_syst_QCDkF->At(mX))->Clone();      break;
		case MMSLOPEFF: h2 = (TH2D*)((TH2D*)(TObjArray*)tobjarr_syst_mmSlopeEff->At(mX))->Clone(); break;
		case EEISOEFF:  h2 = (TH2D*)((TH2D*)(TObjArray*)tobjarr_syst_eeIsoEff->At(mX))->Clone();   break;
		case MMRES:     h2 = (TH2D*)((TH2D*)(TObjArray*)tobjarr_syst_mmRes->At(mX))->Clone();      break;
		case EERES:     h2 = (TH2D*)((TH2D*)(TObjArray*)tobjarr_syst_eeRes->At(mX))->Clone();      break;
		default: _FATAL("unknown template type");
	}
	TH1D* hTmp = (TH1D*)TH2toTH1(h2,mll); // TH1 histogram of g^4 in the dilepton mass bin number mll
	
	Int_t nbinsx = hTmp->GetNbinsX();
	////////////////////////////////////////////////////////////////
	if(doScale2Zpeak && typ==NOMINAL) hTmp->Scale(scale2Zpeak); ////
	////////////////////////////////////////////////////////////////
	Double_t xval = -999.;
	if(doInterpolation)
	{
		Int_t bin = hTmp->FindBin(g4);
		
		if(bin==0 || bin==1)   xval = hTmp->GetBinContent(1); // cannot interpolate on the first bin or the underflow
		else if(bin==nbinsx+1) xval = hTmp->GetBinContent(bin-1); // cannot interpolate on the last bin or the overflow
		else if(bin==nbinsx)   xval = hTmp->GetBinContent(bin); // cannot interpolate on the last bin or the overflow
		else                   xval = hTmp->Interpolate(g4); // interpolated dN/dg^4 at g^4, between the 2 adjacent bin centers
	}
	else
	{
		Int_t bin = hTmp->FindBin(g4);
		if(bin==nbinsx+1) xval = hTmp->GetBinContent(bin-1); // overflow 
		else if(bin==0)   xval = hTmp->GetBinContent(1);     // underflow
		else              xval = hTmp->GetBinContent(bin);   // normal
	}
	delete h2;
	delete hTmp;
	return xval;
}

void TH1toTF1(TString mod, int mXX)
{
	msglvl[DBG] = SILENT;
	msglvl[INF] = VISUAL;
	msglvl[WRN] = VISUAL;
	msglvl[ERR] = VISUAL;
	msglvl[FAT] = VISUAL;
	
	/////////////////
	model = mod; ////
	/////////////////
	
	bool doSinglePoint = false;
	if(mXX>=0)
	{
		doSinglePoint = true;
	}
	else if(mXX==-1)
	{
		_INFO("COMPILED SUCCESSFULY");
		return;
	}
	else if(mXX==-2)
	{
		_INFO("looping.");
	}
	
	_INFO("working in -> "+(string)sDir);
	
	style();

	TDirectory* oldDir = gDirectory; // remember old directory
	
	init();
	
	oldDir->cd();
	
	TString fname = sDir+model+"_"+mutype+"_functions";
	fname += (!doScale2Zpeak)   ? "" : "_norm2Zpeak";
	fname += (!doInterpolation) ? "" : "_interpolated";
	fname += (!doSinglePoint)   ? "" : "_mX_"+(TString)_s(mXX);
	fname += "_npx"+(TString)_s(npx);
	fname += ".root";
	TFile* funcfile = new TFile(fname,"RECREATE");

	unsigned int ntemplates   = (unsigned int)tobjarr->GetSize();
	unsigned int lasttemplate = (unsigned int)tobjarr->GetLast();
	for(unsigned int mX=0 ; mX<ntemplates && mX<=lasttemplate ; mX++)
	{
		//////////////////////////////
		if(doSinglePoint) mX=mXX; ////
		//////////////////////////////
	
		TString mXname = (TString)_s(mX);
		TString mXval  = (TString)_s(mXXmin+mX*dmXX);

		TDirectory* dirXnominal = funcfile->mkdir(mXname+"_nominal");
		TDirectory* dirXsyst = funcfile->mkdir(mXname+"_syst");
		TDirectory* dirXZxs = dirXsyst->mkdir("Zxs");
		TDirectory* dirXPDF = dirXsyst->mkdir("PDF");
		TDirectory* dirXEWkF = dirXsyst->mkdir("EWkF");
		TDirectory* dirXQCDkF = dirXsyst->mkdir("QCDkF");
		TDirectory* dirXmmSlopeEff = dirXsyst->mkdir("mmSlopeEff");
		TDirectory* dirXmmRes = dirXsyst->mkdir("mmRes");
		TDirectory* dirXeeIsoEff = dirXsyst->mkdir("eeIsoEff");
		TDirectory* dirXeeRes = dirXsyst->mkdir("eeRes");
		
		TH2D* h2Xdummy = (TH2D*)((TH2D*)(TObjArray*)tobjarr->At(mX))->Clone("dummy");
		
		TH2D*    h2X = NULL;
		TH1D*    h   = NULL;
		TF1*     f   = NULL;
		TCanvas* c   = NULL;
		TCanvas* c2  = NULL;

		unsigned int nbins = h2Xdummy->GetNbinsX(); // 56
		for(unsigned int mll=1 ; mll<=(nbins-bins2chop) ; mll++) // 1...(56-9 = 47)
		{
			TString mllname = (TString)_s(mll);
			TString mllval  = (TString)_s(h2Xdummy->GetXaxis()->GetBinCenter(mll+bins2chop));

			
			oldDir->cd();
			h2X = (TH2D*)((TH2D*)(TObjArray*)tobjarr->At(mX))->Clone();
			////////////////////////////////////////////////
			if(doScale2Zpeak) h2X->Scale(scale2Zpeak); /////
			////////////////////////////////////////////////
			f = new TF1("fNominal_mX"+mXname+"_mll"+mllname,fTH1toTF1,xmin,xmax,3); // this will be scaled since h2X is delivered via the global TObjArray (not from here)
			f->SetParameters(mX,mll,NOMINAL);
			f->SetParNames("mX","mll","typ");
			f->SetLineColor(kBlue);
			f->SetLineWidth(1);
			f->SetNpx(npx);
			h = (TH1D*)(TH2toTH1(h2X,mll))->Clone("");
			h->SetLineColor(kRed);
			c = new TCanvas("cNominal_mX"+mXname+"_mll"+mllname,"",600,400);
			c->cd();
			c->Draw();
			f->Draw();
			h->SetTitle("dN/dg^{4} in mX="+mXval+" GeV and m_{"+channel+"}="+mllval+" TeV");
			h->GetXaxis()->SetTitle("g^{4}");
			h->GetYaxis()->SetTitle("dN/dg^{4}");
			h->Draw("SAMES");
			dirXnominal->cd();
			c->Write();
			f->Write();
			h->Write();
			delete h2X;
			delete h;
			delete f;
			delete c;
			
			oldDir->cd();
			h2X = (TH2D*)((TH2D*)(TObjArray*)tobjarr_syst_Zxs->At(mX))->Clone();
			f = new TF1("fZxs_mX"+mXname+"_mll"+mllname,fTH1toTF1,xmin,xmax,3);
			f->SetParameters(mX,mll,ZXS);
			f->SetParNames("mX","mll","typ");
			f->SetLineColor(kBlue);
			f->SetLineWidth(1);
			f->SetNpx(npx);
			h = (TH1D*)(TH2toTH1(h2X,mll))->Clone("");
			h->SetLineColor(kRed);
			c = new TCanvas("cZxs_mX"+mXname+"_mll"+mllname,"",600,400);
			c->cd();
			c->Draw();
			f->Draw();
			h->SetTitle("dN/dg^{4} in mX="+mXval+" GeV and m_{"+channel+"}="+mllval+" TeV");
			h->GetXaxis()->SetTitle("g^{4}");
			h->GetYaxis()->SetTitle("dN/dg^{4}");
			h->Draw("SAMES");
			dirXZxs->cd();
			c->Write();
			f->Write();
			h->Write();
			delete h2X;
			delete h;
			delete f;
			delete c;
			
			oldDir->cd();
			h2X = (TH2D*)((TH2D*)(TObjArray*)tobjarr_syst_PDF->At(mX))->Clone();
			f = new TF1("fPDF_mX"+mXname+"_mll"+mllname,fTH1toTF1,xmin,xmax,3);
			f->SetParameters(mX,mll,PDF);
			f->SetParNames("mX","mll","typ");
			f->SetLineColor(kBlue);
			f->SetLineWidth(1);
			f->SetNpx(npx);
			h = (TH1D*)(TH2toTH1(h2X,mll))->Clone("");
			h->SetLineColor(kRed);
			c = new TCanvas("cPDF_mX"+mXname+"_mll"+mllname,"",600,400);
			c->cd();
			c->Draw();
			f->Draw();
			h->SetTitle("dN/dg^{4} in mX="+mXval+" GeV and m_{"+channel+"}="+mllval+" TeV");
			h->GetXaxis()->SetTitle("g^{4}");
			h->GetYaxis()->SetTitle("dN/dg^{4}");
			h->Draw("SAMES");
			dirXPDF->cd();
			c->Write();
			f->Write();
			h->Write();
			delete h2X;
			delete h;
			delete f;
			delete c;			
			
			oldDir->cd();
			h2X = (TH2D*)((TH2D*)(TObjArray*)tobjarr_syst_EWkF->At(mX))->Clone();
			TF1 *f = new TF1("fEWkF_mX"+mXname+"_mll"+mllname,fTH1toTF1,xmin,xmax,3);
			f->SetParameters(mX,mll,EWKF);
			f->SetParNames("mX","mll","typ");
			f->SetLineColor(kBlue);
			f->SetLineWidth(1);
			f->SetNpx(npx);
			h = (TH1D*)(TH2toTH1(h2X,mll))->Clone("");
			h->SetLineColor(kRed);
			c = new TCanvas("cEWkF_mX"+mXname+"_mll"+mllname,"",600,400);
			c->cd();
			c->Draw();
			f->Draw();
			h->SetTitle("dN/dg^{4} in mX="+mXval+" GeV and m_{"+channel+"}="+mllval+" TeV");
			h->GetXaxis()->SetTitle("g^{4}");
			h->GetYaxis()->SetTitle("dN/dg^{4}");
			h->Draw("SAMES");
			dirXEWkF->cd();
			c->Write();
			f->Write();
			h->Write();
			delete h2X;
			delete h;
			delete f;
			delete c;
			
			/* 
			oldDir->cd();
			h2X = (TH2D*)((TH2D*)(TObjArray*)tobjarr_syst_QCDkF->At(mX))->Clone();
			f = new TF1("fQCDkF_mX"+mXname+"_mll"+mllname,fTH1toTF1,xmin,xmax,3);
			f->SetParameters(mX,mll,QCDKF);
			f->SetParNames("mX","mll","typ");
			f->SetLineColor(kBlue);
			f->SetLineWidth(1);
			f->SetNpx(npx);
			h = (TH1D*)(TH2toTH1(h2X,mll))->Clone("");
			h->SetLineColor(kRed);
			c = new TCanvas("cQCDkF_mX"+mXname+"_mll"+mllname,"",600,400);
			c->cd();
			c->Draw();
			f->Draw();
			h->SetTitle("dN/dg^{4} in mX="+mXval+" GeV and m_{"+channel+"}="+mllval+" TeV");
			h->GetXaxis()->SetTitle("g^{4}");
			h->GetYaxis()->SetTitle("dN/dg^{4}");
			h->Draw("SAMES");
			dirXQCDkF->cd();
			c->Write();
			f->Write();
			h->Write();
			delete h2X;
			delete h;
			delete f;
			delete c; */
			
			if(channel=="#mu#mu")
			{
				oldDir->cd();
				h2X = (TH2D*)((TH2D*)(TObjArray*)tobjarr_syst_mmSlopeEff->At(mX))->Clone();
				f = new TF1("fmmSlopeEff_mX"+mXname+"_mll"+mllname,fTH1toTF1,xmin,xmax,3);
				f->SetParameters(mX,mll,MMSLOPEFF);
				f->SetParNames("mX","mll","typ");
				f->SetLineColor(kBlue);
				f->SetLineWidth(1);
				f->SetNpx(npx);
				h = (TH1D*)(TH2toTH1(h2X,mll))->Clone("");
				h->SetLineColor(kRed);
				c = new TCanvas("cmmSlopeEff_mX"+mXname+"_mll"+mllname,"",600,400);
				c->cd();
				c->Draw();
				f->Draw();
				h->SetTitle("dN/dg^{4} in mX="+mXval+" GeV and m_{"+channel+"}="+mllval+" TeV");
				h->GetXaxis()->SetTitle("g^{4}");
				h->GetYaxis()->SetTitle("dN/dg^{4}");
				h->Draw("SAMES");
				dirXmmSlopeEff->cd();
				c->Write();
				f->Write();
				h->Write();
				delete h2X;
				delete h;
				delete f;
				delete c;

				if(doInterference)
				{
					oldDir->cd();
					h2X = (TH2D*)((TH2D*)(TObjArray*)tobjarr_syst_mmRes->At(mX))->Clone();
					f = new TF1("fmmRes_mX"+mXname+"_mll"+mllname,fTH1toTF1,xmin,xmax,3);
					f->SetParameters(mX,mll,MMRES);
					f->SetParNames("mX","mll","typ");
					f->SetLineColor(kBlue);
					f->SetLineWidth(1);
					f->SetNpx(npx);
					h = (TH1D*)(TH2toTH1(h2X,mll))->Clone("");
					h->SetLineColor(kRed);
					c = new TCanvas("cmmRes_mX"+mXname+"_mll"+mllname,"",600,400);
					c->cd();
					c->Draw();
					f->Draw();
					h->SetTitle("dN/dg^{4} in mX="+mXval+" GeV and m_{"+channel+"}="+mllval+" TeV");
					h->GetXaxis()->SetTitle("g^{4}");
					h->GetYaxis()->SetTitle("dN/dg^{4}");
					h->Draw("SAMES");
					dirXmmRes->cd();
					c->Write();
					f->Write();
					h->Write();
					delete h2X;
					delete h;
					delete f;
					delete c;
				}
			}
			
			if(channel=="ee")
			{
				oldDir->cd();
				h2X = (TH2D*)((TH2D*)(TObjArray*)tobjarr_syst_eeIsoEff->At(mX))->Clone();
				f = new TF1("feeIsoEff_mX"+mXname+"_mll"+mllname,fTH1toTF1,xmin,xmax,3);
				f->SetParameters(mX,mll,EEISOEFF);
				f->SetParNames("mX","mll","typ");
				f->SetLineColor(kBlue);
				f->SetLineWidth(1);
				f->SetNpx(npx);
				h = (TH1D*)(TH2toTH1(h2X,mll))->Clone("");
				h->SetLineColor(kRed);
				c = new TCanvas("ceeIsoEff_mX"+mXname+"_mll"+mllname,"",600,400);
				c->cd();
				c->Draw();
				f->Draw();
				h->SetTitle("dN/dg^{4} in mX="+mXval+" GeV and m_{"+channel+"}="+mllval+" TeV");
				h->GetXaxis()->SetTitle("g^{4}");
				h->GetYaxis()->SetTitle("dN/dg^{4}");
				h->Draw("SAMES");
				dirXeeIsoEff->cd();
				c->Write();
				f->Write();
				h->Write();
				delete h2X;
				delete h;
				delete f;
				delete c;
				
				/* oldDir->cd();
				h2X = (TH2D*)((TH2D*)(TObjArray*)tobjarr_syst_eeRes->At(mX))->Clone();
				f = new TF1("feeRes_mX"+mXname+"_mll"+mllname,fTH1toTF1,xmin,xmax,3);
				f->SetParameters(mX,mll,EERES);
				f->SetParNames("mX","mll","typ");
				f->SetLineColor(kBlue);
				f->SetLineWidth(1);
				f->SetNpx(npx);
				h = (TH1D*)(TH2toTH1(h2X,mll))->Clone("");
				h->SetLineColor(kRed);
				c = new TCanvas("ceeRes_mX"+mXname+"_mll"+mllname,"",600,400);
				c->cd();
				c->Draw();
				f->Draw();
				h->SetTitle("dN/dg^{4} in mX="+mXval+" GeV and m_{"+channel+"}="+mllval+" TeV");
				h->GetXaxis()->SetTitle("g^{4}");
				h->GetYaxis()->SetTitle("dN/dg^{4}");
				h->Draw("SAMES");
				dirXeeRes->cd();
				c->Write();
				f->Write();
				h->Write();
				delete h2X;
				delete h;
				delete f;
				delete c; */
			}
		}
		
		oldDir->cd();
		c2 = new TCanvas("cmX"+mXname,"",600,400);
		c2->Draw();
		c2->cd();
		c2->SetLogx();
		c2->SetLogz();
		h2X = (TH2D*)((TH2D*)(TObjArray*)tobjarr->At(mX))->Clone();
		h2X->SetTitle("#frac{dN}{dg^{4}dm_{"+channel+"}} nominal");
		h2X->Draw("SURF1");
		dirXnominal->cd();
		c2->Write();
		h2X->Write();
		delete h2X;
		delete c2;
		
		oldDir->cd();
		c2 = new TCanvas("cZxs_mX"+mXname,"",600,400);
		c2->Draw();
		c2->cd();
		c2->SetLogx();
		h2X = (TH2D*)((TH2D*)(TObjArray*)tobjarr_syst_Zxs->At(mX))->Clone();
		h2X->SetTitle("#frac{nominal + Zxs syst}{nominal}-1 vs. g^{4} vs. m_{"+channel+"}");
		h2X->Draw("SURF1");
		dirXZxs->cd();
		c2->Write();
		h2X->Write();
		delete h2X;
		delete c2;
		
		oldDir->cd();
		c2 = new TCanvas("cPDF_mX"+mXname,"",600,400);
		c2->Draw();
		c2->cd();
		c2->SetLogx();
		h2X = (TH2D*)((TH2D*)(TObjArray*)tobjarr_syst_PDF->At(mX))->Clone();
		h2X->SetTitle("#frac{nominal + PDF syst}{nominal}-1 vs. g^{4} vs. m_{"+channel+"}");
		h2X->Draw("SURF1");
		dirXPDF->cd();
		c2->Write();
		h2X->Write();
		delete h2X;
		delete c2;
		
		oldDir->cd();
		c2 = new TCanvas("cEWkF_mX"+mXname,"",600,400);
		c2->Draw();
		c2->cd();
		c2->SetLogx();
		h2X = (TH2D*)((TH2D*)(TObjArray*)tobjarr_syst_EWkF->At(mX))->Clone();
		h2X->SetTitle("#frac{nominal + EWkF syst}{nominal}-1 vs. g^{4} vs. m_{"+channel+"}");
		h2X->Draw("SURF1");
		dirXEWkF->cd();
		c2->Write();
		h2X->Write();
		delete h2X;
		delete c2;
		
		/* oldDir->cd();
		c2 = new TCanvas("cQCDkF_mX"+mXname,"",600,400);
		c2->Draw();
		c2->cd();
		c2->SetLogx();
		h2X = (TH2D*)((TH2D*)(TObjArray*)tobjarr_syst_QCDkF->At(mX))->Clone();
		h2X->SetTitle("#frac{nominal + QCDkF syst}{nominal}-1 vs. g^{4} vs. m_{"+channel+"}");
		h2X->Draw("SURF1");
		dirXQCDkF->cd();
		c2->Write();
		h2X->Write();
		delete h2X;
		delete c2; */
		
		if(channel=="#mu#mu")
		{
			oldDir->cd();
			c2 = new TCanvas("cmmSlopeEff_mX"+mXname,"",600,400);
			c2->Draw();
			c2->cd();
			c2->SetLogx();
			h2X = (TH2D*)((TH2D*)(TObjArray*)tobjarr_syst_mmSlopeEff->At(mX))->Clone();
			h2X->SetTitle("#frac{nominal + mmSlopeEff syst}{nominal}-1 vs. g^{4} vs. m_{"+channel+"}");
			h2X->Draw("SURF1");
			dirXmmSlopeEff->cd();
			c2->Write();
			h2X->Write();
			delete h2X;
			delete c2;
			
			if(doInterference)
			{
				oldDir->cd();
				c2 = new TCanvas("cmmRes_mX"+mXname,"",600,400);
				c2->Draw();
				c2->cd();
				c2->SetLogx();
				h2X = (TH2D*)((TH2D*)(TObjArray*)tobjarr_syst_mmRes->At(mX))->Clone();
				h2X->SetTitle("#frac{smeared +1#sigma}{nominal}-1 vs. g^{4} vs. m_{"+channel+"}");
				h2X->Draw("SURF1");
				dirXmmRes->cd();
				c2->Write();
				h2X->Write();
				delete h2X;
				delete c2;
			}
		}
		
		if(channel=="ee")
		{
			oldDir->cd();
			c2 = new TCanvas("ceeIsoEff_mX"+mXname,"",600,400);
			c2->Draw();
			c2->cd();
			c2->SetLogx();
			h2X = (TH2D*)((TH2D*)(TObjArray*)tobjarr_syst_eeIsoEff->At(mX))->Clone();
			h2X->SetTitle("#frac{nominal + eeIsoEff syst}{nominal}-1 vs. g^{4} vs. m_{"+channel+"}");
			h2X->Draw("SURF1");
			dirXeeIsoEff->cd();
			c2->Write();
			h2X->Write();
			delete h2X;
			delete c2;
			
			/* oldDir->cd();
			c2 = new TCanvas("ceeRes_mX"+mXname,"",600,400);
			c2->Draw();
			c2->cd();
			c2->SetLogx();
			h2X = (TH2D*)((TH2D*)(TObjArray*)tobjarr_syst_eeRes->At(mX))->Clone();
			h2X->SetTitle("#frac{smeared +1#sigma}{nominal}-1 vs. g^{4} vs. m_{"+channel+"}");
			h2X->Draw("SURF1");
			dirXeeRes->cd();
			c2->Write();
			h2X->Write();
			delete h2X;
			delete c2; */
		}
		
		_INFO("done mX="+_s(mX));
		
		//////////////////////////////
		if(doSinglePoint) break; /////
		//////////////////////////////
	}
	funcfile->Write();
	funcfile->Close();
}
