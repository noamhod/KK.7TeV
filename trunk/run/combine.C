#include "../include/rawStd.h"
#include "../include/rawROOT.h"
#include "../include/types.h"
#include "../include/logs.h"
#include "../include/style.h"
#include "../include/bins.h"
#include "../include/histos.h"
#include "../include/systematics.h"

// TString fpath = "2dtemplates_fastDY_noTruth"; // for mc11a with the in-amplitude k-factor
// TString fpath = "2dtemplates_fastDY_overallEWkF_noInAmpSigEWkF_noTruth"; // for mc11a with the overall k-factor
// TString fpath = "2dtemplates_mc11c_overallEWkF_noInAmpSigEWkF_noTruth"; // for mc11c with the overall k-factor
TObjArray* toarKKtmp;
TObjArray* toarZPtmp;

double Mmin = 130.;
double Mmax = 5030.;
double dM   = 100.;

TString channel = "#mu#mu"; // #mu#mu or ee
 
 // remember old dir
TDirectory* olddir = gDirectory;
 
// TFile* fTH2toTH1 = new TFile("plots/test_TH2toTH1.root","RECREATE");
// TFile* fsysUpDY = new TFile("plots/test_sysUpDY.root","RECREATE");
// TFile* fsysUpSignal = new TFile("plots/test_sysUpSignal.root","RECREATE");
// TFile* fsysUpTemplateDY = new TFile("plots/test_sysUpTemplateDY.root","RECREATE");
// TFile* fsysUpTemplateSignal = new TFile("plots/test_sysUpTemplateSignal.root","RECREATE");
 
 
TH1D* TH2toTH1(TH2D* h2)
{
	olddir->cd();

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
	TAxis* xaxis = (TAxis*)h2->GetXaxis();
	TAxis* yaxis = (TAxis*)h2->GetYaxis();
	for(int i=0 ; i<nbins ; i++) bins[i] = xaxis->GetBinLowEdge(i+1);
	bins[nbins] = xaxis->GetBinUpEdge(nbins);
	//------------------------------------------------------------
	TH1D* h1 = new TH1D(name,"g^{4} bin ="+binname+";m_{"+channel+"} TeV;Events",nbins,bins);
	for(Int_t bin=0 ; bin<=nbins+1 ; bin++)
	{
		h1->SetBinContent(bin, h2->GetBinContent(bin,g4bin));
	}
	// fTH2toTH1->cd();
	// h1->Write();
	return h1;
}

TH2D* sysUpDY(TH2D* h, TString sysName)
{
	olddir->cd();
	
	// remember the TH1D* of the invariant mass at g4=0 (DY)
	// clone this histogram and modify it to take the "up" values (instead of the nominal) using the syst' functions
	// loop on the original h2 bins and (1) subtract the relevant bin content of the g4=0 from the h2 bin content
	//                                  (2) add the relevant bin content of the modified g4=0 histo to the h2 bin content
	// return h2
	TString h2name = (TString)h->GetName();
	TH2D* h2 = (TH2D*)h->Clone(h2name+"_orig");
	
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
			if(sysName=="PDF")                        relsys = graph_pdfZ->Eval(mllval, 0, "S");
			// if(sysName=="QCDkF")                   relsys = fsys_kQCD->Eval(mllval);  //Now included in pdfZ
			if(sysName=="EWkF")                       relsys = fsys_kEWK->Eval(mllval);
			if(sysName=="mmEff" && channel=="#mu#mu") relsys = fsys_eff->Eval(mllval);
			if(sysName=="eeEff" && channel=="ee")     relsys = fsys_eeIsoEff->Eval(mllval);
		}
		nominal = hDY->GetBinContent(x);
		sysUP   = nominal*(1.+relsys);
		hDYsysUP->SetBinContent(x,sysUP);
	}
	
	// modify all the g^4 slices with sysUP-nominal
	double dynominal    = 0.;
	double dyup         = 0.;
	double sigdynominal = 0.;
	for(unsigned int x=0 ; x<=nbinsx+1 ; x++)
	{
		dynominal = hDY->GetBinContent(x);
		dyup      = hDYsysUP->GetBinContent(x);
		for(unsigned int y=0 ; y<=nbinsy+1 ; y++)
		{
			sigdynominal = h2->GetBinContent(x,y);
			h2->SetBinContent(x,y, (sigdynominal-dynominal)+dyup);
		}
	}
	
	delete hDY;
	delete hDYsysUP;
	// fsysUpDY->cd();
	// h2->Write();
	return h2;
}

TH2D* sysUpSignal(TH2D* h, TString sysName)
{
	olddir->cd();

	// remember the TH1D* of the invariant mass at g4=0 (DY)
	// loop on the original h2 bins and subtract the relevant bin content of the g4=0 from the h2 bin content
	// modify the h2 histogram to take the "up" values (instead of the nominal) using the syst' functions
	// loop on the modified h2 bins and add the relevant bin content of the untouched g4=0 histo to the h2 bin content
	// return h2
	
	TString h2name = (TString)h->GetName();
	TH2D* h2 = (TH2D*)h->Clone(h2name+"_orig");
	
	h2name.ReplaceAll("hg4Mass_template_","");
	
	TH2D* h2nominal = (TH2D*)h2->Clone(h2name+"_nominal");
	TH1D* hDY       = (TH1D*)TH2toTH1(h2)->Clone(h2name+"_DYnominal"); // gets the first bin (g^4=0 -> DY, nominal)
	
	Double_t relsys  = 0.;
	Double_t sysUP   = 0.;
	Double_t signominal = 0.;
	Double_t DYnominal = 0.;
	unsigned int nbinsx = h2->GetNbinsX();
	unsigned int nbinsy = h2->GetNbinsY();
	for(unsigned int x=0 ; x<=nbinsx+1 ; x++)
	{
		Double_t mllval = h2->GetXaxis()->GetBinCenter(x);
		if(mllval<0.11) relsys = 0.;
		else
		{
			if(sysName=="Zxs")   relsys = 0.05; // flat 5%
			// if(sysName=="mmEff" && channel=="#mu#mu") relsys = fsys_eff->Eval(mllval);
			// if(sysName=="eeEff" && channel=="ee")     relsys = fsys_eeIsoEff->Eval(mllval);
		}
		DYnominal = hDY->GetBinContent(x);
		
		for(unsigned int y=0 ; y<=nbinsy+1 ; y++) // modify all the g^4 slices with sysUP-DYnominal
		{
			signominal = h2nominal->GetBinContent(x,y) - DYnominal; // signominal is only the signal (subtract the DY)
			sysUP      = signominal + DYnominal*relsys; // this is the modified signal
			h2->SetBinContent(x,y,sysUP+DYnominal);
		}
	}
	
	delete hDY;
	delete h2nominal;
	
	// fsysUpSignal->cd();
	// h2->Write();
	return h2;
}

TH2D* sysUpTemplateDY(TH2D* h2, TString sysName)
{
	olddir->cd();

	// clone the original h2 template
	// if sys DY:  TH1D* h2sysUp = sysUpDY(h2)
	// if sys Sig: TH1D* h2sysUp = sysUpSignal(h2)
	// TH2D* hsysUpTemplate = h2sysUp->Clone("")
	// hsysUpTemplate->Divide(h2)
	// loop on the hsysUpTemplate bins and subtract 1 from each
	// return hsysUpTemplate
	
	TString h2name = (TString)h2->GetName();
	
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
			h2syst->SetBinContent(x,y,ratio-1.);
		}
	}
	
	delete h2nominal;
	delete h2sysUP;
	
	// fsysUpTemplateDY->cd();
	// h2syst->Write();
	return h2syst;
}

TH2D* sysUpTemplateSignal(TH2D* h2, TString sysName)
{
	olddir->cd();

	// clone the original h2 template
	// if sys DY:  TH1D* h2sysUp = sysUpDY(h2)
	// if sys Sig: TH1D* h2sysUp = sysUpSignal(h2)
	// TH2D* hsysUpTemplate = h2sysUp->Clone("")
	// hsysUpTemplate->Divide(h2)
	// loop on the hsysUpTemplate bins and subtract 1 from each
	// return hsysUpTemplate
	
	TString h2name = (TString)h2->GetName();
	
	TH2D* h2nominal = (TH2D*)h2->Clone(h2name+"_nominal");
	TH2D* h2syst    = (TH2D*)h2->Clone(h2name+"_"+sysName+"_syst");
	h2syst->Reset();
	TH2D* h2sysUP   = NULL;
	if(sysName=="Zxs")   h2sysUP = sysUpSignal(h2nominal,"Zxs");
	// if(sysName=="mmEff" && channel=="#mu#mu") h2sysUP = sysUpDY(h2nominal,"mmEff");
	// if(sysName=="eeEff" && channel=="ee")     h2sysUP = sysUpDY(h2nominal,"eeEff");
	
	h2sysUP->Divide(h2nominal);
	unsigned int nbinsx = h2->GetNbinsX();
	unsigned int nbinsy = h2->GetNbinsY();
	for(unsigned int x=0 ; x<=nbinsx+1 ; x++)
	{
		for(unsigned int y=0 ; y<=nbinsy+1 ; y++)
		{
			Double_t ratio = h2sysUP->GetBinContent(x,y);
			h2syst->SetBinContent(x,y,ratio-1.);
		}
	}
	
	delete h2nominal;
	delete h2sysUP;
	
	// fsysUpTemplateSignal->cd();
	// h2syst->Write();
	return h2syst;
}
 
 

void combine()
{
	msglvl[DBG] = SILENT;
	msglvl[INF] = VISUAL;
	msglvl[WRN] = VISUAL;
	msglvl[ERR] = VISUAL;
	msglvl[FAT] = VISUAL;

	olddir->cd();
	TFile* fKK = new TFile("plots/KK_"+fpath+".root", "RECREATE");
	TObjArray* templates2d_KK = new TObjArray;
	TObjArray* templates2d_KK_syst_Zxs        = new TObjArray;
	TObjArray* templates2d_KK_syst_PDF        = new TObjArray;
	TObjArray* templates2d_KK_syst_EWkF       = new TObjArray;
	TObjArray* templates2d_KK_syst_QCDkF      = new TObjArray;
	TObjArray* templates2d_KK_syst_mmSlopeEff = new TObjArray;
	TObjArray* templates2d_KK_syst_eeIsoEff   = new TObjArray;

	olddir->cd();
	TFile* fZP = new TFile("plots/ZP_"+fpath+".root", "RECREATE");
	TObjArray* templates2d_ZP = new TObjArray;
	TObjArray* templates2d_ZP_syst_Zxs        = new TObjArray;
	TObjArray* templates2d_ZP_syst_PDF        = new TObjArray;
	TObjArray* templates2d_ZP_syst_EWkF       = new TObjArray;
	TObjArray* templates2d_ZP_syst_QCDkF      = new TObjArray;
	TObjArray* templates2d_ZP_syst_mmSlopeEff = new TObjArray;
	TObjArray* templates2d_ZP_syst_eeIsoEff   = new TObjArray;

	olddir->cd();
	
	TH2D* h2tmp = NULL;
	
	// uncertainties
	TH2D* h2nominal        = NULL;
	TH2D* h2sys_zXsec      = NULL;
	TH2D* h2sys_pdfZ       = NULL;    
	TH2D* h2sys_kEWK       = NULL;
	TH2D* h2sys_kQCD       = NULL;
	TH2D* h2sys_mmSlopeEff = NULL;
	TH2D* h2sys_eeIsoEff   = NULL;
	
	for(double f=Mmin ; f<=Mmax ; f+=dM)
	{
		TString fname = (TString)_s(f);
		
		TString name = "";
		
		
		// nominals
		olddir->cd();
		TFile* FKK = new TFile("plots/KK_"+fpath+"_Xmass"+fname+".root","READ");
		FKK->cd();
		toarKKtmp = new TObjArray();
		toarKKtmp->Read("template2d");
		olddir->cd();
		h2tmp = (TH2D*)((TH2D*)(TObjArray*)toarKKtmp->At(0))->Clone();
		fKK->cd(); // important !
		templates2d_KK->Add( (TH2D*)h2tmp );
		templates2d_KK->SetOwner(kTRUE);
		
		/////////////////////
		// KK systematics ///
		/////////////////////
		olddir->cd();
		name = (TString)h2tmp->GetName();
		h2nominal = (TH2D*)h2tmp->Clone(name+"_syst");
		h2sys_zXsec      = (TH2D*)sysUpTemplateSignal(h2nominal,"Zxs")->Clone(name+"_sys_Zxs"); 
		h2sys_pdfZ       = (TH2D*)sysUpTemplateDY(h2nominal,"PDF")->Clone(name+"_sys_pdfZ");         // PDF systematic	      
		h2sys_kEWK       = (TH2D*)sysUpTemplateDY(h2nominal,"EWkF")->Clone(name+"_sys_kEWK");	      // EWK K-factor
		// h2sys_kQCD    = (TH2D*)sysUpTemplateDY(h2nominal,"QCDkF")->Clone(name+"_sys_kQCD");       // QCD K-factor; Now included in pdfZ
		h2sys_mmSlopeEff = (TH2D*)sysUpTemplateDY(h2nominal,"mmEff")->Clone(name+"_sys_mmSlopeEff"); // const slope efficiency uncertainty
		h2sys_eeIsoEff   = (TH2D*)sysUpTemplateDY(h2nominal,"eeEff")->Clone(name+"_sys_eeIsoEff");   // isolation in ee channel
		
		fKK->cd(); // important !
		templates2d_KK_syst_Zxs->Add( (TH2D*)h2sys_zXsec );
		templates2d_KK_syst_PDF->Add( (TH2D*)h2sys_pdfZ );
		templates2d_KK_syst_EWkF->Add( (TH2D*)h2sys_kEWK );
		// templates2d_KK_syst_QCDkF->Add( (TH2D*)h2sys_kQCD );
		templates2d_KK_syst_mmSlopeEff->Add( (TH2D*)h2sys_mmSlopeEff );
		templates2d_KK_syst_eeIsoEff->Add( (TH2D*)h2sys_eeIsoEff );
		
		templates2d_KK_syst_Zxs->SetOwner(kTRUE);
		templates2d_KK_syst_PDF->SetOwner(kTRUE);
		templates2d_KK_syst_EWkF->SetOwner(kTRUE);
		// templates2d_KK_syst_QCDkF->SetOwner(kTRUE);
		templates2d_KK_syst_mmSlopeEff->SetOwner(kTRUE);
		templates2d_KK_syst_eeIsoEff->SetOwner(kTRUE);
		
		delete FKK;
		delete toarKKtmp;
		
		_INFO("done KK "+(string)fname);
		
		
		////////////////////////////////////////
		
		
		
		olddir->cd();
		TFile* FZP = new TFile("plots/ZP_"+fpath+"_Xmass"+fname+".root","READ");
		FZP->cd();
		toarZPtmp = new TObjArray();
		toarZPtmp->Read("template2d");
		olddir->cd();
		h2tmp = (TH2D*)((TH2D*)(TObjArray*)toarZPtmp->At(0))->Clone();
		fZP->cd(); // important !
		templates2d_ZP->Add( (TH2D*)h2tmp );
		templates2d_ZP->SetOwner(kTRUE);
		
		
		/////////////////////
		// ZP systematics ///
		/////////////////////
		olddir->cd();
		name = (TString)h2tmp->GetName();
		h2nominal = (TH2D*)h2tmp->Clone(name+"_syst");
		h2sys_zXsec      = (TH2D*)sysUpTemplateSignal(h2nominal,"Zxs")->Clone(name+"_sys_Zxs"); 
		h2sys_pdfZ       = (TH2D*)sysUpTemplateDY(h2nominal,"PDF")->Clone(name+"_sys_pdfZ");         // PDF systematic	      
		h2sys_kEWK       = (TH2D*)sysUpTemplateDY(h2nominal,"EWkF")->Clone(name+"_sys_kEWK");	      // EWK K-factor
		// h2sys_kQCD    = (TH2D*)sysUpTemplateDY(h2nominal,"QCDkF")->Clone(name+"_sys_kQCD");       // QCD K-factor; Now included in pdfZ
		h2sys_mmSlopeEff = (TH2D*)sysUpTemplateDY(h2nominal,"mmEff")->Clone(name+"_sys_mmSlopeEff"); // const slope efficiency uncertainty
		h2sys_eeIsoEff   = (TH2D*)sysUpTemplateDY(h2nominal,"eeEff")->Clone(name+"_sys_eeIsoEff");   // isolation in ee channel
		
		fZP->cd(); // important !
		templates2d_ZP_syst_Zxs->Add( (TH2D*)h2sys_zXsec );
		templates2d_ZP_syst_PDF->Add( (TH2D*)h2sys_pdfZ );
		templates2d_ZP_syst_EWkF->Add( (TH2D*)h2sys_kEWK );
		// templates2d_ZP_syst_QCDkF->Add( (TH2D*)h2sys_kQCD );
		templates2d_ZP_syst_mmSlopeEff->Add( (TH2D*)h2sys_mmSlopeEff );
		templates2d_ZP_syst_eeIsoEff->Add( (TH2D*)h2sys_eeIsoEff );
		
		templates2d_ZP_syst_Zxs->SetOwner(kTRUE);
		templates2d_ZP_syst_PDF->SetOwner(kTRUE);
		templates2d_ZP_syst_EWkF->SetOwner(kTRUE);
		// templates2d_ZP_syst_QCDkF->SetOwner(kTRUE);
		templates2d_ZP_syst_mmSlopeEff->SetOwner(kTRUE);
		templates2d_ZP_syst_eeIsoEff->SetOwner(kTRUE);
		
		delete FZP;
		delete toarZPtmp;
		
		_INFO("done ZP "+(string)fname);
		
	}
	
	_INFO("done loop");
	
	olddir->cd();
	
	fKK->cd();
	templates2d_KK->SetOwner(kTRUE);
	templates2d_KK->Write("template2d", TObject::kSingleKey);
	
	templates2d_KK_syst_Zxs->SetOwner(kTRUE);
	templates2d_KK_syst_Zxs->Write("template2d_Zxs_syst", TObject::kSingleKey);
	templates2d_KK_syst_PDF->SetOwner(kTRUE);
	templates2d_KK_syst_PDF->Write("template2d_PDF_syst", TObject::kSingleKey);
	templates2d_KK_syst_EWkF->SetOwner(kTRUE);
	templates2d_KK_syst_EWkF->Write("template2d_EWkF_syst", TObject::kSingleKey);
	// templates2d_KK_syst_QCDkF->SetOwner(kTRUE);
	// templates2d_KK_syst_QCDkF->Write("template2d_QCDkF_syst", TObject::kSingleKey);
	templates2d_KK_syst_eeIsoEff->SetOwner(kTRUE);
	templates2d_KK_syst_eeIsoEff->Write("template2d_eeIsoEff_syst", TObject::kSingleKey);
	templates2d_KK_syst_mmSlopeEff->SetOwner(kTRUE);
	templates2d_KK_syst_mmSlopeEff->Write("template2d_mmSlopeEff_syst", TObject::kSingleKey);
	
	fKK->Write();
	fKK->Close();
	
	_INFO("done KK");
	
	
	olddir->cd();
	
	fZP->cd();
	templates2d_ZP->SetOwner(kTRUE);
	templates2d_ZP->Write("template2d", TObject::kSingleKey);
	
	templates2d_ZP_syst_Zxs->SetOwner(kTRUE);
	templates2d_ZP_syst_Zxs->Write("template2d_Zxs_syst", TObject::kSingleKey);
	templates2d_ZP_syst_PDF->SetOwner(kTRUE);
	templates2d_ZP_syst_PDF->Write("template2d_PDF_syst", TObject::kSingleKey);
	templates2d_ZP_syst_EWkF->SetOwner(kTRUE);
	templates2d_ZP_syst_EWkF->Write("template2d_EWkF_syst", TObject::kSingleKey);
	// templates2d_ZP_syst_QCDkF->SetOwner(kTRUE);
	// templates2d_ZP_syst_QCDkF->Write("template2d_QCDkF_syst", TObject::kSingleKey);
	templates2d_ZP_syst_eeIsoEff->SetOwner(kTRUE);
	templates2d_ZP_syst_eeIsoEff->Write("template2d_eeIsoEff_syst", TObject::kSingleKey);
	templates2d_ZP_syst_mmSlopeEff->SetOwner(kTRUE);
	templates2d_ZP_syst_mmSlopeEff->Write("template2d_mmSlopeEff_syst", TObject::kSingleKey);
	
	fZP->Write();
	fZP->Close();
	
	_INFO("done ZP");
	
	_INFO("see:");
	_INFO(" (1) "+(string)fKK->GetName());
	_INFO(" (2) "+(string)fZP->GetName());
	
	// fTH2toTH1->Write();
	// fsysUpDY->Write();
	// fsysUpSignal->Write();
	// fsysUpTemplateDY->Write();
	// fsysUpTemplateDY->Write();
	// fTH2toTH1->Close();
	// fsysUpDY->Close();
	// fsysUpSignal->Close();
	// fsysUpTemplateDY->Close();
	// fsysUpTemplateDY->Close();
}
