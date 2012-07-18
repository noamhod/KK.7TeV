#ifndef SYSTEMATICS_H
#define SYSTEMATICS_H

#include "rawROOT.h"


namespace systematics
{

static bool systDoInterference = true;
void setSystInrerference(bool doInterf)
{
	systDoInterference = doInterf;
}

//Functions to map out linear increase of systematic vs mass (relative uncertainty)
static TF1* fsys_eff  = new TF1("fsys_eff" ,"0.03*x",0.0,3.0);
static TF1* fsys_kEWK = new TF1("fsys_kEWK","0.0225*x",0.0,3.0);
static TF1* fsys_eeIsoEff = new TF1("fsys_eeIsoEff","0.01*x",0.0,3.0);


//PDF, alpha_s and kQCD (=scale) error TGraph, input from T. Nunnemann
static const double Vmass[39] = {0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.091, 0.1, 0.125, 0.15, 0.175, 
				 0.2, 0.25, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1, 1.25, 1.5, 1.75, 2, 2.25, 2.5, 
				 2.75, 3, 3.25, 3.5, 3.75, 4, 4.25, 4.5, 4.75, 5};
static const double VPDF[39] = {0.161273, 0.076909, 0.0583181, 0.0517107, 0.0485283, 0.047392, 0.0457165, 0.0449222, 
				0.0440114, 0.0434281, 0.0421782, 0.0410122, 0.0399375, 0.0399249, 0.0397618, 0.041, 
				0.0428719, 0.0454423, 0.0488774, 0.0524023, 0.0572276, 0.0628967, 0.0695557, 0.0887525, 
				0.115953, 0.151611, 0.19758, 0.25315, 0.313861, 0.377535, 0.442274, 0.507875, 0.576834, 
				0.648193, 0.726607, 0.818732, 0.945838, 1.20089, 2.00758};
static TGraph* graph_pdfZ = new TGraph(39, Vmass, VPDF);

static const double ZxsRelSyst = 0.05;


//////////////////////////////////////////////////

TH1D* TH2toTH1(TH2D* h2, TString channel, Int_t g4bin=1)
{
	// olddir->cd();

	///////////////////////////////
	// g^4=0 is always at bin=1 ///
	///////////////////////////////
	TString binname  = (TString)_s(g4bin);
	TString origname = (TString)h2->GetName();
	origname.ReplaceAll("hg4Mass_template_","");
	TString name = origname+"_g4bin_"+binname;
	//------------------------------------------------------------
	const Int_t nbins = h2->GetNbinsX();
	Double_t bins[nbins+1];
	TAxis* xaxis = (TAxis*)h2->GetXaxis();
	for(int i=0 ; i<nbins ; i++) bins[i] = xaxis->GetBinLowEdge(i+1);
	bins[nbins] = xaxis->GetBinUpEdge(nbins);
	//------------------------------------------------------------
	TH1D* h1 = new TH1D(name,"g^{4} bin ="+binname+";m_{"+channel+"} TeV;Events",nbins,bins);
	for(Int_t bin=0 ; bin<=nbins+1 ; bin++)
	{
		h1->SetBinContent(bin, h2->GetBinContent(bin,g4bin));
		h1->SetBinError(bin, h2->GetBinError(bin,g4bin));
	}
	return h1;
}

TH2D* sysUpDY(TH2D* h, TString channel, TString sysName)
{
	// olddir->cd();
	
	TString h2name = (TString)h->GetName();
	TH2D* h2 = (TH2D*)h->Clone(h2name+"_orig");
	
	h2name.ReplaceAll("hg4Mass_template_","");
	
	TH1D* hDY      = (TH1D*)TH2toTH1(h2,channel)->Clone(h2name+"_DYnominal"); // gets the first bin (g^4=0 -> DY, nominal)
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
			if(sysName=="PDF")                     relsys = graph_pdfZ->Eval(mllval, 0, "S");
			// if(sysName=="QCDkF")                relsys = fsys_kQCD->Eval(mllval);  // Now included in pdfZ
			if(sysName=="EWkF")                    relsys = fsys_kEWK->Eval(mllval); // treated seperately
			// if(sysName=="mmEff" && channel=="#mu#mu") relsys = fsys_eff->Eval(mllval);
			// if(sysName=="eeEff" && channel=="ee")     relsys = fsys_eeIsoEff->Eval(mllval);
		}
		nominal = hDY->GetBinContent(x);
		sysUP   = nominal*(1.+relsys);
		hDYsysUP->SetBinContent(x,sysUP);
		hDYsysUP->SetBinError(x,hDY->GetBinError(x)); // ???????????????????????????????????????????????????
	}
	
	// modify all the g^4 slices with sysUP
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
			h2->SetBinContent(x,y, sigdynominal-dynominal+dyup);
			h2->SetBinError(x,y, h2->GetBinError(x,y));
		}
	}
	
	delete hDY;
	delete hDYsysUP;
	return h2;
}

TH2D* sysUpSignal(TH2D* h, TString channel, TString sysName)
{
	// olddir->cd();

	TString h2name = (TString)h->GetName();
	TH2D* h2 = (TH2D*)h->Clone(h2name+"_orig");
	
	h2name.ReplaceAll("hg4Mass_template_","");
	
	TH2D* h2nominal = (TH2D*)h2->Clone(h2name+"_nominal");
	TH1D* hDY       = (TH1D*)TH2toTH1(h2,channel)->Clone(h2name+"_DYnominal"); // gets the first bin (g^4=0 -> DY, nominal)
	
	Double_t relsys  = 0.;
	Double_t sigUP   = 0.;
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
			if(sysName=="Zxs")   relsys = ZxsRelSyst; // flat 5%
			// if(sysName=="mmEff" && channel=="#mu#mu") relsys = fsys_eff->Eval(mllval);
			// if(sysName=="eeEff" && channel=="ee")     relsys = fsys_eeIsoEff->Eval(mllval);
		}
		DYnominal = hDY->GetBinContent(x);
		
		for(unsigned int y=0 ; y<=nbinsy+1 ; y++) // modify all the g^4 slices
		{
			signominal = h2nominal->GetBinContent(x,y) - DYnominal; // signominal is only the signal (subtract the DY)
			sigUP      = signominal*(1.+relsys); // this is the modified signal
			h2->SetBinContent(x,y,sigUP+DYnominal); // this the up value of DY+X
			h2->SetBinError(x,y,h2->GetBinError(x,y));
		}
	}
	
	delete hDY;
	delete h2nominal;
	return h2;
}

TH2D* sysUpSignalPlusDY(TH2D* h, TString channel, TString sysName)
{
	// olddir->cd();

	TString h2name = (TString)h->GetName();
	TH2D* h2 = (TH2D*)h->Clone(h2name+"_orig");
	
	h2name.ReplaceAll("hg4Mass_template_","");
	
	TH2D* h2nominal = (TH2D*)h2->Clone(h2name+"_nominal");
	
	Double_t relsys  = 0.;
	Double_t sigUP   = 0.;
	Double_t nominal = 0.;
	unsigned int nbinsx = h2->GetNbinsX();
	unsigned int nbinsy = h2->GetNbinsY();
	for(unsigned int x=0 ; x<=nbinsx+1 ; x++)
	{
		Double_t mllval = h2->GetXaxis()->GetBinCenter(x);
		if(mllval<0.11) relsys = 0.;
		else
		{
			if(sysName=="EWkF") relsys = fsys_kEWK->Eval(mllval);
			if(sysName=="mmEff" && channel=="#mu#mu") relsys = fsys_eff->Eval(mllval);
			if(sysName=="eeEff" && channel=="ee")     relsys = fsys_eeIsoEff->Eval(mllval);
		}
		
		for(unsigned int y=0 ; y<=nbinsy+1 ; y++) // modify all the g^4 slices
		{
			nominal = h2nominal->GetBinContent(x,y);
			sigUP      = nominal*(1.+relsys);
			h2->SetBinContent(x,y,sigUP); // this the up value of DY+X
			h2->SetBinError(x,y,h2->GetBinError(x,y)); // this the up value of DY+X
		}
	}

	delete h2nominal;
	return h2;
}

TH2D* sysUpTemplate(TH2D* h2, TString channel, TString sysName)
{
	// olddir->cd();
	
	TString h2name = (TString)h2->GetName();
	
	TH2D* h2nominal = (TH2D*)h2->Clone(h2name+"_nominal");
	TH2D* h2syst    = (TH2D*)h2->Clone(h2name+"_"+sysName+"_syst");
	h2syst->Reset();
	TH2D* h2sysUP   = NULL;
	
	if(sysName=="PDF")   h2sysUP = sysUpDY(h2nominal, channel, "PDF");
	// if(sysName=="QCDkF") h2sysUP = sysUpDY(h2nominal, channel, "QCDkF");
	if(sysName=="EWkF")
	{
		if(systDoInterference) h2sysUP = sysUpSignalPlusDY(h2nominal, channel, "EWkF");
		else                   h2sysUP = sysUpDY(h2nominal, channel, "EWkF");
	}
	if(sysName=="mmEff") h2sysUP = sysUpSignalPlusDY(h2nominal, channel, "mmEff");
	if(sysName=="eeEff") h2sysUP = sysUpSignalPlusDY(h2nominal, channel, "eeEff");
	if(sysName=="Zxs")   h2sysUP = sysUpSignal(h2nominal, channel, "Zxs");
	
	h2sysUP->Divide(h2nominal);
	unsigned int nbinsx = h2->GetNbinsX();
	unsigned int nbinsy = h2->GetNbinsY();
	for(unsigned int x=0 ; x<=nbinsx+1 ; x++)
	{
		for(unsigned int y=0 ; y<=nbinsy+1 ; y++)
		{
			Double_t ratio = h2sysUP->GetBinContent(x,y);
			h2syst->SetBinContent(x,y,ratio-1.);
			h2syst->SetBinError(x,y,h2syst->GetBinError(x,y));
		}
	}
	
	delete h2nominal;
	delete h2sysUP;
	return h2syst;
}

TH2D* smearUpTemplate(TH2D* h2, TH2D* h2up)
{
	// olddir->cd();
	
	TString h2name = (TString)h2->GetName();
	
	TH2D* h2nominal = (TH2D*)h2->Clone(h2name+"_nominal");
	TH2D* h2smearUp = (TH2D*)h2up->Clone(h2name+"_smearUp");
	TH2D* h2syst    = (TH2D*)h2->Clone(h2name+"_syst");
	h2syst->Reset();
	
	h2smearUp->Divide(h2nominal);
	unsigned int nbinsx = h2->GetNbinsX();
	unsigned int nbinsy = h2->GetNbinsY();
	for(unsigned int x=0 ; x<=nbinsx+1 ; x++)
	{
		for(unsigned int y=0 ; y<=nbinsy+1 ; y++)
		{
			Double_t ratio = h2smearUp->GetBinContent(x,y);
			Double_t ratiominus1 = ratio-1.;
			h2syst->SetBinContent(x,y,ratio-1.);
			h2syst->SetBinError(x,y,h2syst->GetBinError(x,y));
		}
	}
	delete h2nominal;
	delete h2smearUp;
	return h2syst;
}

}

#endif
