#include "../include/rawStd.h"
#include "../include/rawROOT.h"
#include "../include/logs.h"
#include "../include/bins.h"
#include "../include/style.h"
#include "../include/histos.h"
#include "../include/systematics.h"

/////////////////////////////////////////
// USAGE: ///////////////////////////////
// root -b -l -q templates_syst.C++ /////
/////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////
// Global definitions ///////////////////////////////////////////////////////////////////////
TString ftype = "2dtemplates_fastDY_noTruth";
TString dir   = "plots/";

TString model   = "ZP";     // ZP or KK
TString channel = "#mu#mu"; // #mu#mu or ee

Double_t xminKK = g4min;
Double_t xmaxKK = g4max;
Double_t xminZP = g4min;
Double_t xmaxZP = g4max;

Double_t scale2Zpeak = 1.;//0.9852190620; // see normtest.C
bool doScale2Zpeak   = false;
bool doInterpolation = false;

TDirectory* oldDir = gDirectory; // remember old directory

TFile* f2DSystTemplate;

TFile* f2DTemplate;
TObjArray* tobjarr;
/////////////////////////////////////////////////////////////////////////////////////////////

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

TH1D* TH2toTH1(TH2D* h2)
{
	///////////////////////////////
	// g^4=0 is always at bin=1 ///
	Int_t g4bin=1; ////////////////
	///////////////////////////////
	TString binname  = (TString)_s(g4bin);
	TString origname = (TString)h2->GetName();
	origname.ReplaceAll("hg4Mass_template_","");
	TString name = origname+"_g4bin_"+binname;
	//------------------------------------------------------------
	const Int_t nbins = h2->GetNbinsX();
	Double_t bins[nbins+1];
	TAxis* xaxis = (TAxis*)h->GetXaxis();
	TAxis* yaxis = (TAxis*)h->GetYaxis();
	for(int i=0 ; i<nbins ; i++) bins[i] = xaxis->GetBinLowEdge(i+1);
	bins[nbins] = xaxis->GetBinUpEdge(nbins);
	//------------------------------------------------------------
	TH1D* h1 = new TH1D(name,"g^{4} bin ="+binname+";m_{"+channel+"} TeV;Events",nbins,bins);
	for(Int_t bin=1 ; bin<=nbins ; bin++)
	{
		h1->SetBinContent(bin, h2->GetBinContent(bin,g4bin));
	}
	return h1;
}

TH2D* sysUpDY(TH2D* h, TString sysName)
{
	// remember the TH1D* of the invariant mass at g4=0 (DY)
	// clone this histogram and modify it to take the "up" values (instead of the nominal) using the syst' functions
	// loop on the original h2 bins and (1) subtract the relevant bin content of the g4=0 from the h2 bin content
	//                                  (2) add the relevant bin content of the modified g4=0 histo to the h2 bin content
	// return h2
	TString h2name = (TString)h->GetName();
	TH2D* h2 = (TH2D*)h->Clone(h2Name+"_orig");
	
	h2name.ReplaceAll("hg4Mass_template_","");
	
	TH1D* hDY      = (TH1D*)TH2toTH1(h2)->Clone(h2name+"_DYnominal"); // gets the first bin (g^4=0 -> DY, nominal)
	TH1D* hDYsysUP = (TH1D*)hDY->Clone(h2name+"_DYsysUP");
	hDYsysUP->Reset();
	
	Double_t relsys  = 0.;
	Double_t sysUP   = 0.;
	Double_t nominal = 0.;
	unsigned int nbinsx = h2->GetNbinsX();
	unsigned int nbinsy = h2->GetNbinsY();
	for(unsigned int x=0 ; x<=nbinsx+1 ; x++)
	{
		Double_t mllval = h2->GetXaxis()->GetBinCenter(x);
		if(mllval<0.11) relsys = 0.;
		else
		{
			if(sysName=="PDF")   relsys = h_sys_pdfZ->SetBinContent(x,y,graph_pdfZ->Eval(mllval, 0, "S"));
			if(sysName=="QCDkF") relsys = h_sys_kQCD->SetBinContent(x,y,fsys_kQCD->Eval(mllval));  //Now included in pdfZ
			if(sysName=="EWkF")  relsys = h_sys_kEWK->SetBinContent(x,y,fsys_kEWK->Eval(mllval));
			if(sysName=="mmEff" && channel=="#mu#mu") relsys = h_sys_eff->SetBinContent(x,y,fsys_eff->Eval(mllval));
			if(sysName=="eeEff" && channel=="ee")     relsys = h_sys_eeIsoEff->SetBinContent(x,y,fsys_eeIsoEff->Eval(mllval));
		}
		nominal = hDY->GetBinContent(x);
		sysUP   = nominal*(1.+relsys);
		hDYsysUP->SetBinContent(x,sysUP);
	}
	
	// modify all the g^4 slices with sysUP-nominal
	for(unsigned int x=0 ; x<=nbinsx+1 ; x++)
	{
		nominal = hDY->GetBinContent(x);
		sysUP   = hDYsysUP->GetBinContent(x);
		for(unsigned int y=0 ; y<=nbinsy+1 ; y++)
		{
			h2->SetBinContent(x,y,sysUP-nominal);
		}
	}
	
	delete hDY;
	delete hDYsysUP;
	return h2;
}

TH2D* sysUpSignal(TH2D* h, TString sysName)
{
	// remember the TH1D* of the invariant mass at g4=0 (DY)
	// loop on the original h2 bins and subtract the relevant bin content of the g4=0 from the h2 bin content
	// modify the h2 histogram to take the "up" values (instead of the nominal) using the syst' functions
	// loop on the modified h2 bins and add the relevant bin content of the untouched g4=0 histo to the h2 bin content
	// return h2
	
	TString h2name = (TString)h->GetName();
	TH2D* h2 = (TH2D*)h->Clone(h2Name+"_orig");
	
	h2name.ReplaceAll("hg4Mass_template_","");
	
	TH2D* h2nominal = (TH2D*)h2->Clone(h2name+"_nominal");
	TH1D* hDY       = (TH1D*)TH2toTH1(h2)->Clone(h2name+"_DYnominal"); // gets the first bin (g^4=0 -> DY, nominal)
	
	Double_t relsys  = 0.;
	Double_t sysUP   = 0.;
	Double_t nominal = 0.;
	Double_t DYnominal = 0.;
	unsigned int nbinsx = h2->GetNbinsX();
	unsigned int nbinsy = h2->GetNbinsY();
	for(unsigned int x=0 ; x<=nbinsx+1 ; x++)
	{
		Double_t mllval = h2->GetXaxis()->GetBinCenter(x);
		if(mllval<0.11) relsys = 0.;
		else
		{
			if(sysName=="Zxs")   relsys = h_sys_zXsec->SetBinContent(x,y,0.05); // flat 5%
			if(sysName=="mmEff" && channel=="#mu#mu") relsys = h_sys_eff->SetBinContent(x,y,fsys_eff->Eval(mllval));
			if(sysName=="eeEff" && channel=="ee")     relsys = h_sys_eeIsoEff->SetBinContent(x,y,fsys_eeIsoEff->Eval(mllval));
		}
		DYnominal = hDY->GetBinContent(x);
		
		for(unsigned int y=0 ; y<=nbinsy+1 ; y++) // modify all the g^4 slices with sysUP-DYnominal
		{
			nominal = h2nominal->GetBinContent(x,y) - DYnominal; // nominal is only the signal (subtract the DY)
			sysUP   = nominal*(1.+relsys); // this is the modified signal
			h2->SetBinContent(x,y,sysUP+DYnominal);
		}
	}
	
	delete hDY;
	delete h2nominal;
	return h2;
}

TH2D* sysUpTemplateDY(TH2D* h2, TString sysName)
{
	// clone the original h2 template
	// if sys DY:  TH1D* h2sysUp = sysUpDY(h2)
	// if sys Sig: TH1D* h2sysUp = sysUpSignal(h2)
	// TH2D* hsysUpTemplate = h2sysUp->Clone("")
	// hsysUpTemplate->Divide(h2)
	// loop on the hsysUpTemplate bins and subtract 1 from each
	// return hsysUpTemplate
	
	TH2D* h2nominal = (TH2D*)h2->Clone(h2name+"_nominal");
	TH2D* h2syst    = (TH2D*)h2->Clone(h2name+"_"+sysName+"_syst");
	h2syst->Reset();
	TH2D* h2sysUP   = NULL;
	if(sysName=="PDF")   h2sysUP = sysUpDY(h2nominal,"PDF");
	if(sysName=="QCDkF") h2sysUP = sysUpDY(h2nominal,"QCDkF");
	if(sysName=="EWkF")  h2sysUP = sysUpDY(h2nominal,"EWkF");
	if(sysName=="mmEff") h2sysUP = sysUpDY(h2nominal,"mmEff");
	if(sysName=="eeEff") h2sysUP = sysUpDY(h2nominal,"eeEff");
	
	h2sysUP->Divide(h2nominal);
	unsigned int nbinsx = h2->GetNbinsX();
	unsigned int nbinsy = h2->GetNbinsY();
	for(unsigned int x=0 ; x<=nbinsx+1 ; x++)
	{
		for(unsigned int y=0 ; y<=nbinsy+1 ; y++)
		{
			Double_t ratio = h2sysUP->GetBinContent(x,y);
			h2syst->SetBinContent(ratio+1.);
		}
	}
	
	delete h2nominal;
	delete h2sysUP;
	
	return h2syst;
}

TH2D* sysUpTemplateSignal(TH2D* h2, TString sysName)
{
	// clone the original h2 template
	// if sys DY:  TH1D* h2sysUp = sysUpDY(h2)
	// if sys Sig: TH1D* h2sysUp = sysUpSignal(h2)
	// TH2D* hsysUpTemplate = h2sysUp->Clone("")
	// hsysUpTemplate->Divide(h2)
	// loop on the hsysUpTemplate bins and subtract 1 from each
	// return hsysUpTemplate
	
	TH2D* h2nominal = (TH2D*)h2->Clone(h2name+"_nominal");
	TH2D* h2syst    = (TH2D*)h2->Clone(h2name+"_"+sysName+"_syst");
	h2syst->Reset();
	TH2D* h2sysUP   = NULL;
	if(sysName=="Zxs")   h2sysUP = sysUpDY(h2nominal,"Zxs");
	if(sysName=="mmEff" && channel=="#mu#mu") h2sysUP = sysUpDY(h2nominal,"mmEff");
	if(sysName=="eeEff" && channel=="ee")     h2sysUP = sysUpDY(h2nominal,"eeEff");
	
	h2sysUP->Divide(h2nominal);
	unsigned int nbinsx = h2->GetNbinsX();
	unsigned int nbinsy = h2->GetNbinsY();
	for(unsigned int x=0 ; x<=nbinsx+1 ; x++)
	{
		for(unsigned int y=0 ; y<=nbinsy+1 ; y++)
		{
			Double_t ratio = h2sysUP->GetBinContent(x,y);
			h2syst->SetBinContent(ratio+1.);
		}
	}
	
	delete h2nominal;
	delete h2sysUP;
	
	return h2syst;
}

void init()
{
	f2DTemplate = new TFile(dir+model+"_"+ftype+".root","READ");
	tobjarr = new TObjArray();
	tobjarr->Read("template2d");
	
	oldDir->cd();
	
	f2DSystTemplate = new TFile(dir+model+"_2dtemplates_syst.root","RECREATE");
	
	oldDir->cd();
}

void writeRelSyst(unsigned int mX, TString sysNmae="")
{
	TString mXname = (TString)_s(mX);
	TString mXval  = (TString)_s(mXXmin+mX*dmXX);
	
	///////////////////////////////////////////////////////////
	f2DSystTemplate->cd(); ////////////////////////////////////
	TDirectory* dirX      = f2DSystTemplate->mkdir(mXname); ///
	TDirectory* dirX2d    = dirX->mkdir("2d"); ////////////////
	TDirectory* dirX2dsys = dirX->mkdir("2dsyst"); ////////////
	TDirectory* dirXsys   = dirX->mkdir("syst"); //////////////
	///////////////////////////////////////////////////////////
	
	oldDir->cd();
	
	TH2D* h2Xnominal = (TH2D*)((TH2D*)(TObjArray*)tobjarr->At(mX))->Clone(model+"_nominal_mX"+mXname);

	///////////////////////////////////////////////////////
	if(doScale2Zpeak) h2Xnominal->Scale(scale2Zpeak); /////
	///////////////////////////////////////////////////////

	TH2D* h2Xdummy = (TH2D*)h2Xnominal->Clone("dummy");
	h2Xdummy->Reset();
	
	// signal uncertainties
	TH2D* h2sys_zXsec         = (TH2D*)sysUpTemplateSignal(h2Xnominal,"Zxs")->Clone(model+"_sys_PDF_mX"+mXname); 
	TH2D* h2sys_mmSlopeEffSig = (TH2D*)sysUpTemplateSignal(h2Xnominal,"mmEff")->Clone(model+"_sys_mmSlopeEffSig_mX"+mXname); 
	TH2D* h2sys_eeIsoEffSig   = (TH2D*)sysUpTemplateSignal(h2Xnominal,"eeEff")->Clone(model+"_sys_eeIsoEffSig_mX"+mXname); 
	
	// DY uncertainties
	TH2D* h2sys_pdfZ       = (TH2D*)sysUpTemplateDY(h2Xnominal,"PDF")->Clone(model+"_sys_pdfZ_mX"+mXname);         // PDF systematic	      
	TH2D* h2sys_kEWK       = (TH2D*)sysUpTemplateDY(h2Xnominal,"EWkF")->Clone(model+"_sys_kEWK_mX"+mXname);	     // EWK K-factor
	//TH2D* h2sys_kQCD     = (TH2D*)sysUpTemplateDY(h2Xnominal,"QCDkF")->Clone(model+"_sys_kQCD_mX"+mXname);       // QCD K-factor; Now included in pdfZ
	TH2D* h2sys_mmSlopeEff = (TH2D*)sysUpTemplateDY(h2Xnominal,"mmEff")->Clone(model+"_sys_mmSlopeEff_mX"+mXname); // const slope efficiency uncertainty
	TH2D* h2sys_eeIsoEff   = (TH2D*)sysUpTemplateDY(h2Xnominal,"eeEff")->Clone(model+"_sys_eeIsoEff_mX"+mXname);   // isolation in ee channel
	
	
	// PUT THESE HISTOS IN DEDICATED TObjArrays !!!!!!!!!!!!!!!!!!!!!!!!
	
	
}


void templates_syst()
{
	msglvl[DBG] = SILENT;
	msglvl[INF] = VISUAL;
	msglvl[WRN] = VISUAL;
	msglvl[ERR] = VISUAL;
	msglvl[FAT] = VISUAL;
	
	style();
	
	init();
	
	oldDir->cd();

	unsigned int ntemplates   = (unsigned int)tobjarr->GetSize();
	unsigned int lasttemplate = (unsigned int)tobjarr->GetLast();
	for(unsigned int mX=0 ; mX<ntemplates && mX<=lasttemplate ; mX++)
	{	
		writeRelSyst(mX);
	}
	f2DSystTemplate->Write();
	f2DSystTemplate->Close();
}
