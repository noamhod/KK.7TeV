#ifndef HISTOS_H
#define HISTOS_H

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

TH1D* hChopper(TH1D* h, int bins2chop)
{
	
	const Int_t    nbinsorig = h->GetNbinsX();
	const Int_t    nbins = nbinsorig-bins2chop;
	Double_t bins[nbins+1];
	TAxis* xaxis = (TAxis*)h->GetXaxis();
	TAxis* yaxis = (TAxis*)h->GetYaxis();
	// const Double_t xmin  = xaxis->GetBinLowEdge(bins2chop+1);
	// const Double_t xmax  = xaxis->GetBinUpEdge(nbinsorig);
	// setLogBins(nbins, xmin, xmax, bins);
	// _INFO("xmin="+_s(xmin));
	// _INFO("xmax="+_s(xmax));
	
	for(int i=0 ; i<nbins ; i++) bins[i] = xaxis->GetBinLowEdge(bins2chop+i+1);
	bins[nbins] = xaxis->GetBinUpEdge(nbinsorig);
	// for(int i=0 ; i<=nbins ; i++) cout << bins[i] << ", ";
	// cout << endl;
	
	TString name   = (TString)h->GetName();
	TString title  = (TString)h->GetTitle();
	TString xtitle = (TString)xaxis->GetTitle();
	TString ytitle = (TString)yaxis->GetTitle();
	
	TH1D* hChopped = new TH1D(name+"_chopped",title+";"+xtitle+";"+ytitle, nbins,bins);
	hChopped->SetBinContent(0,0.); // underflow bin
	for(Int_t b=1 ; b<=nbins+1 ; b++) hChopped->SetBinContent(b, h->GetBinContent(b+bins2chop));
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
	double min = 1.e20;
	double binval = 0.;
	for(int b=1 ; b<=h->GetNbinsX() ; b++)
	{
		binval = h->GetBinContent(b);
		min = (binval<min  &&  binval>0.) ? binval : min;
	}
	return min;
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

void saveas(TCanvas* c, TString name)
{
	c->RedrawAxis();
	c->Update();
	
	c->SaveAs(name+".png");
	c->SaveAs(name+".pdf");
	c->SaveAs(name+".eps");
	c->SaveAs(name+".C");
	c->SaveAs(name+".root");
}

#endif
