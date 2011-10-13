#ifndef HISTOS_H
#define HISTOS_H

double Integral(TH1* h)
{
	double I=0.;
	for(int i=1 ; i<=h->GetNbinsX() ; i++)
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

#endif
