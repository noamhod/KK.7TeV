#ifndef HISTOS_H
#define HISTOS_H

#include "rawROOT.h"

inline TH1D* resetErrors(TH1D* h)
{
	//------------------------------------------------------------
	const Int_t nbins = h->GetNbinsX();
	Double_t bins[nbins+1];
	TAxis* xaxis = (TAxis*)h->GetXaxis();
	for(int i=0 ; i<nbins ; i++) bins[i] = xaxis->GetBinLowEdge(i+1);
	bins[nbins] = xaxis->GetBinUpEdge(nbins);
	//------------------------------------------------------------
	TString name  = (TString)h->GetName();
	TString title = (TString)h->GetTitle();
	TString xtitle = (TString)h->GetXaxis()->GetTitle();
	TString ytitle = (TString)h->GetYaxis()->GetTitle();
	TH1D* h0 = new TH1D(name+"_noerrors",title+";"+xtitle+";"+ytitle,nbins,bins);
	for(Int_t bin=1 ; bin<=nbins ; bin++)
	{
		h0->SetBinContent(bin, h->GetBinContent(bin));
		h0->SetBinError(bin,0.);
	}
	return h0;
}

inline TH1D* Shift(TH1D* h, double x=0.1)
{
	/// create a new histigram shifted by some amount
	int     N = h->GetNbinsX();
	double ul = h->GetBinLowEdge(N+1);
	double ll = h->GetBinLowEdge(1);
	double delta = x*(ul-ll)/N;
	TH1D* h0 = new TH1D("h","h", N, ll-delta, ul-delta);
	h0->SetDirectory(0);
	for(int i=1 ; i<=N ; i++)
	{
		h0->SetBinContent(i,h->GetBinContent(i));
		h0->SetBinError(i,h->GetBinError(i));
	}
	return h0;
}

inline TH1D* ShiftLog(TH1D* h, double x=0.1)
{	
	//------------------------------------------------------------
	const Int_t nbins = h->GetNbinsX();
	Double_t bins[nbins+1];
	TAxis* xaxis = (TAxis*)h->GetXaxis();
	for(int i=0 ; i<nbins ; i++) bins[i] = xaxis->GetBinLowEdge(i+1) + x*xaxis->GetBinWidth(i+1);
	bins[nbins] = xaxis->GetBinUpEdge(nbins) + x*xaxis->GetBinWidth(nbins);
	//------------------------------------------------------------
	TString name  = (TString)h->GetName();
	TString title = (TString)h->GetTitle();
	TString xtitle = (TString)h->GetXaxis()->GetTitle();
	TString ytitle = (TString)h->GetYaxis()->GetTitle();
	TH1D* h0 = new TH1D(name+"_shifted",title+";"+xtitle+";"+ytitle,nbins,bins);
	for(Int_t bin=1 ; bin<=nbins ; bin++)
	{
		h0->SetBinContent(bin, h->GetBinContent(bin));
		h0->SetBinError(bin, h->GetBinError(bin));
	}
	return h0;
}

double Sum(TH1* h, bool addUunderFlow=false, bool addOverFlow=false)
{
	double I=0.;
	for(int i=1 ; i<=h->GetNbinsX() ; i++)// without under- and over-flow
	{
		I += h->GetBinContent(i);
	}
	if(addUunderFlow) I+=h->GetBinContent(0);
	if(addOverFlow)   I+=h->GetBinContent(h->GetNbinsX()+1);
	return I;
}

double Integral(TH1* h, bool addUunderFlow=false, bool addOverFlow=false)
{
	double I=0.;
	for(int i=1 ; i<=h->GetNbinsX() ; i++)// without under- and over-flow
	{
		I += h->GetBinContent(i)*h->GetBinWidth(i);
	}
	if(addUunderFlow) I+=h->GetBinContent(0)*h->GetBinWidth(0);
	if(addOverFlow)   I+=h->GetBinContent(h->GetNbinsX()+1)*h->GetBinWidth(h->GetNbinsX()+1);
	return I;
}

double IntegralWithUFOF(TH1* h) // with under- and over-flow
{
	double I=0.;
	for(int i=0 ; i<=h->GetNbinsX()+1 ; i++)
	{ 
		I += h->GetBinContent(i)*h->GetBinWidth(i);
	}
	return I;
}

void Scale(TH1* h, double d)
{ 
	/// scale including over/underflow
	for(int i=0 ; i<=h->GetNbinsX()+1 ; i++)
	{ 
		h->SetBinContent(i,h->GetBinContent(i)*d);
	}
}

void Scale(TH2* h, double d)
{ 
	/// scale including over/underflow
	for(int i=0 ; i<=h->GetNbinsX()+1 ; i++)
	{
		for(int j=0 ; j<=h->GetNbinsY()+1 ; j++)
		{
			h->SetBinContent(i,j,h->GetBinContent(i,j)*d);
		}
	}
}

void ScaleWerrors(TH1* h, double d)
{ 
	/// scale including over/underflow
	for ( int i=0 ; i<=h->GetNbinsX()+1 ; i++ )
	{ 
		h->SetBinContent(i,h->GetBinContent(i)*d);
		h->SetBinError(i,h->GetBinError(i)*d);
	}
}

TH1D* hChopper(TH1D* h, int binstochop)
{
	
	const Int_t    nbinsorig = h->GetNbinsX();
	const Int_t    nbins = nbinsorig-binstochop;
	Double_t bins[nbins+1];
	TAxis* xaxis = (TAxis*)h->GetXaxis();
	TAxis* yaxis = (TAxis*)h->GetYaxis();
	// const Double_t xmin  = xaxis->GetBinLowEdge(binstochop+1);
	// const Double_t xmax  = xaxis->GetBinUpEdge(nbinsorig);
	// setLogBins(nbins, xmin, xmax, bins);
	// _INFO("xmin="+_s(xmin));
	// _INFO("xmax="+_s(xmax));
	
	for(int i=0 ; i<nbins ; i++) bins[i] = xaxis->GetBinLowEdge(binstochop+i+1);
	bins[nbins] = xaxis->GetBinUpEdge(nbinsorig);
	// for(int i=0 ; i<=nbins ; i++) cout << bins[i] << ", ";
	// cout << endl;
	
	TString name   = (TString)h->GetName();
	TString title  = (TString)h->GetTitle();
	TString xtitle = (TString)xaxis->GetTitle();
	TString ytitle = (TString)yaxis->GetTitle();
	
	TH1D* hChopped = new TH1D(name+"_chopped",title+";"+xtitle+";"+ytitle, nbins,bins);
	hChopped->SetBinContent(0,0.); // underflow bin
	for(Int_t b=1 ; b<=nbins+1 ; b++)
	{
		hChopped->SetBinContent(b, h->GetBinContent(b+binstochop));
		hChopped->SetBinError(b, h->GetBinError(b+binstochop));
	}
	return (TH1D*)hChopped->Clone();
}

TH1D* hChopperUp(TH1D* h, int binstochop)
{
	const Int_t    nbinsorig = h->GetNbinsX();
	const Int_t    nbins = nbinsorig-binstochop;
	Double_t bins[nbins+1];
	TAxis* xaxis = (TAxis*)h->GetXaxis();
	TAxis* yaxis = (TAxis*)h->GetYaxis();
	
	for(int i=0 ; i<nbins ; i++) bins[i] = xaxis->GetBinLowEdge(i+1);
	bins[nbins] = xaxis->GetBinUpEdge(nbins);
	
	TString name   = (TString)h->GetName();
	TString title  = (TString)h->GetTitle();
	TString xtitle = (TString)xaxis->GetTitle();
	TString ytitle = (TString)yaxis->GetTitle();
	
	TH1D* hChopped = new TH1D(name+"_chopped",title+";"+xtitle+";"+ytitle, nbins,bins);
	hChopped->SetBinContent(nbins+1,0.); // overflow bin
	for(Int_t b=1 ; b<=nbins ; b++)
	{
		hChopped->SetBinContent(b, h->GetBinContent(b));
		hChopped->SetBinError(b, h->GetBinError(b));
	}
	return (TH1D*)hChopped->Clone();
}

TH1D* hZeroize(TH1D* h, int bins2zeroize)
{
	TString name = (TString)h->GetName();
	TH1D* hZeroized = (TH1D*)h->Clone();
	hZeroized->SetName(name+"_zeroized");
	for(Int_t b=0 ; b<=bins2zeroize ; b++) hZeroized->SetBinContent(b, 0.);
	return (TH1D*)hZeroized->Clone();
}

double getYmin(TH1* h)
{
	if(h==NULL)
	{
		_ERROR("Histogram is null, getYmin(TH1* h) returning 0.001");
		return 0.01;
	}
	double min = 1.e20;
	double binval = 0.;
	for(int b=1 ; b<=h->GetNbinsX() ; b++)
	{
		binval = h->GetBinContent(b);
		min = (binval<min  &&  binval>0.) ? binval : min;
	}
	return min;
}

double getYmax(TH1* h)
{
	if(h==NULL)
	{
		_ERROR("Histogram is null, getYmax(TH1* h) returning -1");
		return -1.;
	}
	double max    = 0.;
	double binval = 0.;
	for(int b=1 ; b<=h->GetNbinsX() ; b++)
	{
		binval = h->GetBinContent(b);
		max = (binval>max) ? binval : max;
	}
	return max;
}

double getXYmin(TH2* h)
{
	double min = 1.e20;
	double binval = 0.;
	for(int bx=1 ; bx<=h->GetNbinsX() ; bx++)
	{
		for(int by=1 ; by<=h->GetNbinsY() ; by++)
		{
			binval = h->GetBinContent(bx,by);
			min = (binval<min  &&  binval>0.) ? binval : min;
		}
	}
	return min;
}

void setMinMax(TH1* h1, TH1* h2, bool isLog=false)
{
	Double_t min1 = getYmin(h1);
	Double_t min2 = getYmin(h2);
	Double_t min  = (min1<min2) ? min1 : min2;
	min *= 0.1;
	h1->SetMinimum(min);
	h2->SetMinimum(min);
	
	Double_t max1 = h1->GetMaximum();
	Double_t max2 = h2->GetMaximum();
	Double_t max  = (max1>max2) ? max1 : max2;
	if(isLog) max *= 1.5;
	else      max *= 1.05;
	h1->SetMaximum(max);
	h2->SetMaximum(max);
}

void setMinMax(vector<TH1D*> h, bool isLog=false)
{
	Double_t min = +1.e40;
	Double_t max = -1.e40;
	Double_t tmp = 0.;
	
	for(unsigned int i=0 ; i<h.size() ; i++)
	{
		tmp = getYmin(h[i]);
		min = (tmp<min) ? tmp : min;
	}
	min *= 0.01;
	h[0]->SetMinimum(min);
	
	for(unsigned int i=0 ; i<h.size() ; i++)
	{
		tmp = h[i]->GetMaximum();
		max = (tmp>max) ? tmp : max;
	}
	if(isLog) max *= 1.5;
	else      max *= 1.05;
	h[0]->SetMaximum(max);
}

void setMinMax(TH2* h1, TH2* h2, bool isLog=false)
{
	Double_t min1 = getYmin(h1);
	Double_t min2 = getYmin(h2);
	Double_t min  = (min1<min2) ? min1 : min2;
	min *= 0.1;
	h1->SetMinimum(min);
	h2->SetMinimum(min);
	
	Double_t max1 = h1->GetMaximum();
	Double_t max2 = h2->GetMaximum();
	Double_t max  = (max1>max2) ? max1 : max2;
	if(isLog) max *= 1.5;
	else      max *= 1.05;
	h1->SetMaximum(max);
	h2->SetMaximum(max);
}

void divide(TH1* hNom, TH1* hDen)
{
	Int_t nNom = hNom->GetNbinsX();
	Int_t nDen = hDen->GetNbinsX();
	Double_t nom = 0.;
	Double_t den = 0.;
	if(nNom!=nDen) LOG(INF,VISUAL,"histogrma bins are not equal");
	//if(nNom!=nDen) LOG_INFO("histogrma bins are not equal");
	for(Int_t b=1 ; b<=nNom ; b++)
	{
		nom = hNom->GetBinContent(b);
		den = hDen->GetBinContent(b);
		if(den==0.) hNom->SetBinContent(b,0.); // ???????????????
		else        hNom->SetBinContent(b,nom/den);
	}
}

void residuals(TH1* h1, TH1* h2, TH1* hRes)
{
	Int_t n1 = h1->GetNbinsX();
	Int_t n2 = h2->GetNbinsX();
	Double_t y1 = 0.;
	Double_t y2 = 0.;
	Double_t dy1 = 0.;
	Double_t dy2 = 0.;
	Double_t res = 0.;
	if(n1!=n2) _FATAL("histogrma bins are not equal");
	for(Int_t b=1 ; b<=n1 ; b++)
	{
		y1 = h1->GetBinContent(b);
		y2 = h2->GetBinContent(b);
		dy1 = h1->GetBinError(b);
		dy2 = h2->GetBinError(b);
		res = ((dy1+dy2)!=0.) ? (y1-y2)/sqrt(dy1*dy1+y2*dy2): -999.;
		hRes->SetBinContent(b,res);
	}
}

double getYaverage(TH1* h)
{
	double av    = 0.;
	Int_t nbins = h->GetNbinsX();
	for(Int_t b=1 ; b<=nbins ; b++) av+=h->GetBinContent(b);
	return av/nbins;
}

double getYaverage(TH1* h, double& sigma)
{
	double av = getYaverage(h);
	double sig2 = 0.;
	Int_t nbins = h->GetNbinsX();
	for(Int_t b=1 ; b<=nbins ; b++) sig2 += (h->GetBinContent(b)-av)*(h->GetBinContent(b)-av);
	sigma = sqrt(sig2/nbins);
	return av;
}

void setlogx(TH1* h)
{
	h->GetXaxis()->SetMoreLogLabels();
	h->GetXaxis()->SetNoExponent();
}

void setlogx(TH2* h)
{
	h->GetXaxis()->SetMoreLogLabels();
	h->GetXaxis()->SetNoExponent();
}

void saveas(TCanvas* c, TString name, Bool_t savesource=false)
{
	c->RedrawAxis();
	c->Update();
	
	c->SaveAs(name+".png");
	c->SaveAs(name+".pdf");
	c->SaveAs(name+".eps");
	c->SaveAs(name+".root");
	if(savesource) c->SaveAs(name+".C");
}

void saveas(TObject* obj, TString name, Bool_t logx=false, Bool_t logy=false, Bool_t logz=false, Bool_t savesource=false, TString drwopt="")
{
	TCanvas* c = new TCanvas("","",600,400);
	c->cd();
	c->Draw();
	if(logx) c->SetLogx();
	if(logy) c->SetLogy();
	if(logz) c->SetLogz();
	c->SetTicks(1,1);
	obj->Draw(drwopt);
	if(drwopt=="COLZ" || drwopt=="CONTZ")
	{
		c->SetTopMargin(0.035);
		c->SetBottomMargin(0.1);
		c->SetLeftMargin(0.1);
		c->SetRightMargin(0.14);
	}
	c->RedrawAxis();
	c->Update();
	c->SaveAs(name+".png");
	c->SaveAs(name+".pdf");
	c->SaveAs(name+".eps");
	c->SaveAs(name+".root");
	if(savesource) c->SaveAs(name+".C");
	delete c;
}

void savemultipdf(TCanvas* c, TString fullpath, unsigned int state)
{
	switch(state)
	{
		case 0: fullpath += "("; break;
		case 2: fullpath += ")"; break;
		default: break;
	}
	c->SaveAs(fullpath);
}

void plotsurface
(
	TH2D* h,
	TString name="", Float_t phi = -25, bool dologz=true,
	Double_t ymin=0.,
	Double_t ymax=0.,
	Int_t nPrimitiveBins=0
)
{
	TCanvas* c = NULL;
	h->SetTitle("");

	c = new TCanvas("c","c",900,600);
	c->cd();
	c->Draw();
	c->SetLogx();
	if(dologz) c->SetLogz();
	
	if(nPrimitiveBins>0)
	{
		h->GetYaxis()->SetLimits(ymin,ymax);
		Int_t nBins = nPrimitiveBins*(Int_t)(ymax-ymin);
		h->GetYaxis()->Set(nBins,ymin,ymax);
	}
	//// h->GetYaxis()->SetNdivisions((Int_t)(10.*16),kFALSE);
	//// h->RebinY(5);
	
	//// h->SetFillColor(kOrange);
	//// h->Draw("SURF4");
	
	c->SetPhi(phi);
	c->SetTheta(20);
	
	h->GetZaxis()->SetTitleOffset(1.3);
	
	h->Draw("SURF3");

	c->Modified();
	c->Update();
	c->SaveAs(name+".png");
	c->SaveAs(name+".eps");
	delete c;
}


TCanvas* stackratio(TString name,
					TH1D* hNumerator, THStack* hsDenominator, TList* hlSignals,
					TLegend* leg=NULL, TPaveText* pvtxt_lumi=NULL, TPaveText* pvtxt_atlas=NULL,
					TString ratioLabel="Ratio", TString drawopt_n="",
					Bool_t logx=false, Bool_t logy=false,
					Double_t ymin=-1, Double_t ymax=-1)
{	
	TCanvas* cnv = new TCanvas(name,name,600,550);
	TH1D* htmp;
	
	cnv->Divide(1,2);
	TVirtualPad* tvp_hists = cnv->cd(1);
	TVirtualPad* tvp_ratio = cnv->cd(2);
	
	if(logx) tvp_ratio->SetLogx();
	if(logx) tvp_hists->SetLogx();
	if(logy) tvp_hists->SetLogy();
	
	tvp_hists->SetPad(0.00, 0.35, 1.00, 1.00);
	tvp_ratio->SetPad(0.00, 0.00, 1.00, 0.35);

	tvp_hists->SetBottomMargin(0.012);
	tvp_ratio->SetBottomMargin(0.20);
	tvp_ratio->SetTopMargin(0.012);
	
	tvp_hists->SetTicks(1,1);
	tvp_ratio->SetTicks(1,1);
	
	// sum the original stacked histos
	TH1D* hDenominator = (TH1D*)hNumerator->Clone("tmp");
	hDenominator->Reset();
	TIter next_bg((TList*)hsDenominator->GetHists());
	while(( htmp=(TH1D*)next_bg() )!= NULL)
	{
		cout << "Adding " << ((TH1D*)htmp)->GetName() << endl;
		if(ymin!=-1) htmp->SetMinimum(ymin);
		if(ymax!=-1) htmp->SetMaximum(ymax);
		hDenominator->Add(htmp);
	}
	
	TString cloneName_n = hNumerator->GetName();
	TString cloneName_d = hDenominator->GetName();
	TH1D* th1n_tmp = (TH1D*)hNumerator->Clone(cloneName_n+"_th1n_tmp");
	TH1D* th1d_tmp = (TH1D*)hDenominator->Clone(cloneName_d+"_th1d_tmp");
	th1n_tmp->Sumw2();
	th1d_tmp->Sumw2();

	TH1D* hr = (TH1D*)hNumerator->Clone(); // Clone(name)
	TString sXtitle = (TString)hNumerator->GetXaxis()->GetTitle();
	// TString sTitle = "#frac{Data}{#sum MC#times wgt};"+sXtitle+";Ratio";
	TString sTitle = ";"+sXtitle+";"+ratioLabel;
	hr->SetTitle(sTitle);
	hr->Divide(th1n_tmp,th1d_tmp,1.,1.,"B");
	hr->SetMarkerStyle(20);
	hr->SetMarkerSize(0.8);
	hr->GetXaxis()->SetLabelSize(0.075);
	hr->GetYaxis()->SetLabelSize(0.075);
	hr->GetXaxis()->SetTitleSize(0.075);
	hr->GetYaxis()->SetTitleSize(0.075);
	hr->SetTitleSize(0.075);
	hr->SetTitleSize(0.075);
	hr->GetYaxis()->SetTitleOffset(0.5);
	hr->SetMinimum(0.);
	hr->SetMaximum(+2.);
	
	if(logx) setlogx(hr);
	
	TLine* line = new TLine(hr->GetXaxis()->GetXmin(),1.,hr->GetXaxis()->GetXmax(),1.);

	tvp_hists->cd();
	if(ymin!=-1) hsDenominator->SetMinimum(ymin);
	if(ymax!=-1) hsDenominator->SetMaximum(ymax);
	hsDenominator->Draw(); // Draw("nostack");
	hNumerator->Draw(drawopt_n+"SAMES");
	TIter next_sig(hlSignals);
	while(( htmp=(TH1D*)next_sig() )!=NULL)
	{
		cout << "Drawing " << ((TH1D*)htmp)->GetName() << endl;
		htmp->Draw("SAMES");
	}
	if(pvtxt_lumi!=NULL)  pvtxt_lumi->Draw("SAMES");
	if(pvtxt_atlas!=NULL) pvtxt_atlas->Draw("SAMES");
	if(leg!=NULL)         leg->Draw("SAMES");
	// tvp_hists->Update();
	tvp_hists->RedrawAxis();

	tvp_ratio->cd();
	tvp_ratio->SetGridy();
	hr->Draw("epx0");
	line->Draw("SAMES");
	// tvp_ratio->Update();
	tvp_ratio->RedrawAxis();
	
	// cnv->Update();
	
	return cnv;
}

TGraphAsymmErrors* poisson(TH1D* h)
{
	double value = 0;
	double error_poisson_up   = 0;
	double error_poisson_down = 0;
	double y1 = 0;
	double y2 = 0;
	double d1 = 0;
	double d2 = 0;
	TGraphAsymmErrors *ga = new TGraphAsymmErrors();
	for(int i=1; i<=h->GetNbinsX(); i++)
	{
		value = h->GetBinContent(i);
		if(value!=0)
		{ 
			y1 = value + 1.0;
			d1 = 1.0 - 1.0/(9.0*y1) + 1.0/(3*TMath::Sqrt(y1));
			error_poisson_up = y1*d1*d1*d1 - value;
			y2 = value;
			d2 = 1.0 - 1.0/(9.0*y2) - 1.0/(3.0*TMath::Sqrt(y2));
			error_poisson_down = value - y2*d2*d2*d2;
			ga->SetPoint(i-1, h->GetBinCenter(i), value);
			ga->SetPointError(i-1, 0, 0, error_poisson_down, error_poisson_up);
		}
	}
	ga->SetMarkerStyle(h->GetMarkerStyle());
	ga->SetLineWidth(h->GetLineWidth());
	
	return ga;
}


TCanvas* stackratio(TString name,
					TH1D* hNumerator, THStack* hsDenominator, TList* hlSignals,
					TLegend* leg=NULL, TPaveText* pvtxt_atlas=NULL,
					TString ratioLabel="Ratio",
					Bool_t logx=false, Bool_t logy=false,
					Double_t ymin=-1, Double_t ymax=-1)
{	
	TCanvas* cnv = new TCanvas(name,name,600,550);
	TH1D* htmp;
	
	cnv->Divide(1,2);
	TVirtualPad* tvp_hists = cnv->cd(1);
	TVirtualPad* tvp_ratio = cnv->cd(2);
	
	if(logx) tvp_ratio->SetLogx();
	if(logx) tvp_hists->SetLogx();
	if(logy) tvp_hists->SetLogy();
	
	tvp_hists->SetPad(0.00, 0.35, 1.00, 1.00);
	tvp_ratio->SetPad(0.00, 0.00, 1.00, 0.35);

	tvp_hists->SetBottomMargin(0.012);
	tvp_ratio->SetBottomMargin(0.20);
	tvp_ratio->SetTopMargin(0.012);
	
	tvp_hists->SetTicks(1,1);
	tvp_ratio->SetTicks(1,1);
	
	// poisson graph of the data
	TGraphAsymmErrors* gaNumerator = (TGraphAsymmErrors*)(poisson(hNumerator))->Clone("");
	
	// sum the original stacked histos
	TH1D* hDenominator = (TH1D*)hNumerator->Clone("tmp");
	hDenominator->Reset();
	TIter next_bg((TList*)hsDenominator->GetHists());
	while(( htmp=(TH1D*)next_bg() )!= NULL)
	{
		cout << "Adding " << ((TH1D*)htmp)->GetName() << endl;
		if(ymin!=-1) htmp->SetMinimum(ymin);
		if(ymax!=-1) htmp->SetMaximum(ymax);
		hDenominator->Add(htmp);
	}
	
	TString cloneName_n = hNumerator->GetName();
	TString cloneName_d = hDenominator->GetName();
	TH1D* th1n_tmp = (TH1D*)hNumerator->Clone(cloneName_n+"_th1n_tmp");
	TH1D* th1d_tmp = (TH1D*)hDenominator->Clone(cloneName_d+"_th1d_tmp");
	th1n_tmp->Sumw2();
	th1d_tmp->Sumw2();

	TH1D* hr = (TH1D*)hNumerator->Clone(); // Clone(name)
	TString sXtitle = (TString)hNumerator->GetXaxis()->GetTitle();
	// TString sTitle = "#frac{Data}{#sum MC#times wgt};"+sXtitle+";Ratio";
	TString sTitle = ";"+sXtitle+";"+ratioLabel;
	hr->SetTitle(sTitle);
	hr->Divide(th1n_tmp,th1d_tmp,1.,1.,"B");
	hr->SetMarkerStyle(20);
	hr->SetMarkerSize(0.8);
	hr->GetXaxis()->SetLabelSize(0.075);
	hr->GetYaxis()->SetLabelSize(0.075);
	hr->GetXaxis()->SetTitleSize(0.075);
	hr->GetYaxis()->SetTitleSize(0.075);
	hr->SetTitleSize(0.075);
	hr->SetTitleSize(0.075);
	hr->GetYaxis()->SetTitleOffset(0.5);
	hr->SetMinimum(0.);
	hr->SetMaximum(+2.);
	
	if(logx) setlogx(hr);
	
	TLine* line = new TLine(hr->GetXaxis()->GetXmin(),1.,hr->GetXaxis()->GetXmax(),1.);

	tvp_hists->cd();
	if(ymin!=-1) hsDenominator->SetMinimum(ymin);
	if(ymax!=-1) hsDenominator->SetMaximum(ymax);
	hsDenominator->Draw(); // Draw("nostack");
	if(hlSignals->GetSize()!=0)
	{
		TIter next_sig(hlSignals);
		while(( htmp=(TH1D*)next_sig() )!=NULL)
		{
			cout << "Drawing " << ((TH1D*)htmp)->GetName() << endl;
			htmp->Draw("SAMES");
		}
	}
	// hNumerator->Draw(drawopt_n+"SAMES");
	gaNumerator->Draw("psame");
	if(pvtxt_atlas!=NULL) pvtxt_atlas->Draw("SAMES");
	if(leg!=NULL)         leg->Draw("SAMES");
	tvp_hists->Update();
	tvp_hists->RedrawAxis();

	tvp_ratio->cd();
	tvp_ratio->SetGridy();
	hr->Draw("epx0");
	line->Draw("SAMES");
	tvp_ratio->Update();
	tvp_ratio->RedrawAxis();
	
	cnv->Update();
	
	return cnv;
}


TCanvas* hratio(TString name, TH1* hNumerator, TH1* hDenominator,
				TLegend* leg=NULL, TString ratioLabel="Ratio",
				Bool_t logx=false, Bool_t logy=false)
{	
	TCanvas* cnv = new TCanvas(name,name,600,550);
	cnv->Divide(1,2);
	TVirtualPad* tvp_hists = cnv->cd(1);
	TVirtualPad* tvp_ratio = cnv->cd(2);
	
	if(logx) tvp_ratio->SetLogx();
	if(logx) tvp_hists->SetLogx();
	if(logy) tvp_hists->SetLogy();
	
	tvp_hists->SetPad(0.00, 0.35, 1.00, 1.00);
	tvp_ratio->SetPad(0.00, 0.00, 1.00, 0.355);

	tvp_hists->SetBottomMargin(0.012);
	tvp_ratio->SetBottomMargin(0.20);
	tvp_ratio->SetTopMargin(0.012);
	
	tvp_hists->SetTicks(1,1);
	tvp_ratio->SetTicks(1,1);
	
	TString cloneName_n = hNumerator->GetName();
	TString cloneName_d = hDenominator->GetName();
	TH1D* th1n_tmp = (TH1D*)hNumerator->Clone(cloneName_n+"_th1n_tmp");
	TH1D* th1d_tmp = (TH1D*)hDenominator->Clone(cloneName_d+"_th1d_tmp");
	th1n_tmp->Sumw2();
	th1d_tmp->Sumw2();

	TH1D* hr = (TH1D*)hNumerator->Clone(); // Clone(name)
	TString sXtitle = (TString)hNumerator->GetXaxis()->GetTitle();
	TString sTitle = ";"+sXtitle+";"+ratioLabel;
	hr->SetTitle(sTitle);
	hr->Divide(th1n_tmp,th1d_tmp,1.,1.);
	hr->SetMarkerStyle(20);
	hr->SetMarkerSize(0.6);
	Double_t xLabelSize = hNumerator->GetXaxis()->GetLabelSize()*1.5;
	Double_t yLabelSize = hNumerator->GetYaxis()->GetLabelSize()*1.5;
	Double_t xTitleSize = hNumerator->GetXaxis()->GetTitleSize()*1.5;
	Double_t yTitleSize = hNumerator->GetYaxis()->GetTitleSize()*1.5;
	Double_t titleSize = hNumerator->GetTitleSize()*1.5;
	hr->GetXaxis()->SetLabelSize(xLabelSize);
	hr->GetYaxis()->SetLabelSize(yLabelSize);
	hr->GetXaxis()->SetTitleSize(xTitleSize);
	hr->GetYaxis()->SetTitleSize(yTitleSize);
	hr->SetTitleSize(titleSize);
	hr->GetYaxis()->SetTitleOffset(0.5);
	hr->SetMinimum(getYmin(hr)*0.2);
	hr->SetMaximum(getYmax(hr)*1.2);
	
	if(logx) setlogx(hr);
	
	TLine* line = new TLine(hr->GetXaxis()->GetXmin(),1.,hr->GetXaxis()->GetXmax(),1.);

	tvp_hists->cd();
	setMinMax(th1d_tmp, th1n_tmp, true);
	th1d_tmp->Draw("hist");
	th1n_tmp->Draw("hist SAMES");
	if(leg!=NULL) leg->Draw("SAMES");
	tvp_hists->Update();
	tvp_hists->RedrawAxis();

	tvp_ratio->cd();
	tvp_ratio->SetGridy();
	hr->Draw("epx0");
	line->Draw("SAMES");
	tvp_ratio->Update();
	tvp_ratio->RedrawAxis();
	
	cnv->Update();
	
	return cnv;
}

#endif
