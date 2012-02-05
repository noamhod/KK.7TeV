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
// TString ftype = "2dtemplates_fastDY_smallDY_noEWkFsig_sigEWkf_noHighMbins_noTruth";
// TString ftype = "2dtemplates_fastDY_smallDY_noHighMbins_noTruth";
// TString ftype = "2dtemplates_fastDY_noTruth"; // mc11a with the in-amplitude k-factor
// TString ftype = "2dtemplates_fastDY_overallEWkF_noInAmpSigEWkF_noTruth"; // mc11a with the overall k-factor
TString ftype = "2dtemplates_mc11c_overallEWkF_noInAmpSigEWkF_noTruth"; // mc11c with the overall k-factor
TString dir   = "plots/";

Double_t xmin = g4min;
Double_t xmax = g4max;

TString model   = "KK";     // ZP or KK
TString channel = "#mu#mu"; // #mu#mu or ee

// the normalization is for bins 3-9 of the logx invariant mass plot.
// it is the ratio between the data yeild and the yield of:
//   2dtemplate(at g^4=0) + (allBGs without DY)
// in the range covered between bin 3 and 9 (80-128 GeV).
// The "allBGs without DY" histogram is given to BAT but it is chopped at 128 GeV.
// All the TF1 objects given to BAT must be normalized to this ratio  -> done by running TH12TF1.C again with the ratio provided here.   *IMPORTANT*
// The "allBGs without DY" histogram must be normalized to this ratio -> done while initializing BAT.                                    *IMPORTANT*
Double_t scale2Zpeak = 1.;//0.9852190620; // see normtest.C
bool doScale2Zpeak   = false;
bool doInterpolation = true;


TFile* f2DTemplate;
TObjArray* tobjarr;
TObjArray* tobjarr_syst_Zxs;
TObjArray* tobjarr_syst_PDF;
TObjArray* tobjarr_syst_EWkF;
TObjArray* tobjarr_syst_QCDkF;
TObjArray* tobjarr_syst_mmSlopeEff;
TObjArray* tobjarr_syst_eeIsoEff;

enum template_types
{
	NOMINAL,
	ZXS,
	PDF, EWKF, QCDKF, MMSLOPEFF, EEISOEFF
};
/////////////////////////////////////////////////////////////////////////////////////////////

void init()
{
	f2DTemplate = new TFile(dir+model+"_"+ftype+".root","READ");
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
	tobjarr_syst_mmSlopeEff = new TObjArray();
	tobjarr_syst_mmSlopeEff->Read("template2d_mmSlopeEff_syst");
	_INFO("mmSlopeEff: "+_s(tobjarr_syst_mmSlopeEff->GetLast()));
	tobjarr_syst_eeIsoEff = new TObjArray();
	tobjarr_syst_eeIsoEff->Read("template2d_eeIsoEff_syst");
	_INFO("eeIsoEff:   "+_s(tobjarr_syst_eeIsoEff->GetLast()));
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
		
		if(bin==0 || bin==1)                  xval = hTmp->GetBinContent(1); // cannot interpolate on the first bin or the underflow
		else if(bin==nbinsx+1 || bin==nbinsx) xval = hTmp->GetBinContent(bin-1); // cannot interpolate on the last bin or the overflow
		else                                  xval = hTmp->Interpolate(g4); // interpolated dN/dg^4 at g^4, between the 2 adjacent bin centers
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
	
	style();

	TDirectory* oldDir = gDirectory; // remember old directory
	
	init();
	
	oldDir->cd();
	
	Int_t npx = 200;
	
	TString fname = dir+model+"_functions";
	fname += (!doScale2Zpeak)   ? "" : "_norm2Zpeak";
	fname += (!doInterpolation) ? "" : "_interpolated";
	fname += (!doSinglePoint)   ? "" : "_mX_"+(TString)_s(mXX);
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
		TDirectory* dirXeeIsoEff = dirXsyst->mkdir("eeIsoEff");
				
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
		
		_INFO("done mX="+_s(mX));
		
		//////////////////////////////
		if(doSinglePoint) break; /////
		//////////////////////////////
	}
	funcfile->Write();
	funcfile->Close();
}
