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

void Scale(TH1D* h, double d)
{ 
	/// scale including over/underflow
	for(int i=0 ; i<=h->GetNbinsX()+1 ; i++)
	{ 
		h->SetBinContent(i,h->GetBinContent(i)*d);
	}
}

void ScaleWerrors(TH1D* h, double d)
{ 
	/// scale including over/underflow
	for ( int i=0 ; i<=h->GetNbinsX()+1 ; i++ )
	{ 
		h->SetBinContent(i,h->GetBinContent(i)*d);
		h->SetBinError(i,h->GetBinError(i)*d);
	}
}

double getYmin(TH1D* h)
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

void divide(TH1D* hNom, TH1D* hDen)
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
