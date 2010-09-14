/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#ifdef fitFunctions_cxx
#include "fitFunctions.h"
	
bool custom_isnan(double var)
{
    volatile double d = var;
    return d != d;
}

double scale2data(TH1D* h)
{
	double scale;
	double nentries = 0.;
	for(int i=1 ; i<(int)h->GetNbinsX() ; i++)
	{
		double binCenter = h->GetBinCenter(i);
		if( binCenter>XMIN  &&  binCenter<XMAX) nentries += h->GetBinContent(i);
	}
	scale = nentries*h->GetBinWidth(1);

	return scale;
}

double scale2bg(TH1D* h)
{
	double scale;
	double nentries = 0.;
	for(int i=1 ; i<(int)h->GetNbinsX() ; i++)
	{
		double binCenter = h->GetBinCenter(i);
		if( binCenter>XMIN  &&  binCenter<XMAXBG) nentries += h->GetBinContent(i);
	}
	scale = nentries*h->GetBinWidth(1);

	return scale;
}


///////////////////////////
// exponential background
double exponential(double *x, double *par) 
{
	double xlow = XMIN;
	double xmax = XMAX;
	double N = (TMath::Exp(par[0] + par[1]*xmax) - TMath::Exp(par[0] + par[1]*xlow))/par[1];
	if(N == 0) return 0;
	else       return (1/N)*TMath::Exp(par[0] + par[1]*x[0]);
}

///////////////////////
// Double Gaussian
// mean    --> par[0]
// sigma 1 --> par[1]
// sigma 2 --> par[2]
double DoubleGaus(double x, double mean, double sigma1, double sigma2)
{
	return TMath::Gaus(x,mean,sigma1) + TMath::Gaus(x,mean,sigma2);
}

///////////////////////
// Triple Gaussian
// mean    --> par[0]
// sigma 1 --> par[1]
// sigma 2 --> par[2]
// sigma 3 --> par[3]
double TripleGaus(double x, double mean, double sigma1, double sigma2, double sigma3)
{
	return TMath::Gaus(x,mean,sigma1) + TMath::Gaus(x,mean,sigma2)  + TMath::Gaus(x,mean,sigma3);
}

//////////////////////////////////////
// Breit-Wigner Gaussian convolution
// Fit parameters:
// par[0]=Width (scale) Breit-Wigner
// par[1]=Most Probable (MP, location) Breit mean
// par[2]=Width (sigma) of convoluted Gaussian function
double BreitGaus(double *x, double *par) 
{
	// Numeric constants
	double invsq2pi = 0.3989422804014;   // (2 pi)^(-1/2)

	// Control constants
	double np = 100.0;      // number of convolution steps
	double sc =   5.0;      // convolution extends to +-sc Gaussian sigmas

	// Variables
	double xx;
	double fland;
	double sum = 0.0;
	double xlow,xupp;
	double step;
	double i;

	// Range of convolution integral
	xlow = x[0] - sc * par[2];
	xupp = x[0] + sc * par[2];

	step = (xupp-xlow) / np;

	// Convolution integral of Breit and Gaussian by sum
	for(i=1.0; i<=np/2; i++) {
		xx = xlow + (i-.5) * step;
		fland = TMath::BreitWigner(xx,par[1],par[0]);
		sum += fland * TMath::Gaus(x[0],xx,par[2]);

		xx = xupp - (i-.5) * step;
		fland = TMath::BreitWigner(xx,par[1],par[0]);
		sum += fland * TMath::Gaus(x[0],xx,par[2]);
	} 
	return (step * sum * invsq2pi / par[2]);
}

//////////////////////////////////////
// Breit-Wigner DoubleGaussian convolution
// Fit parameters:
// par[0]=Width (scale) Breit-Wigner
// par[1]=Most Probable (MP, location) Breit mean
// par[2]=Width 1(sigma) of convoluted Double Gaussian function
// par[3]=Width 2(sigma) of convoluted Double Gaussian function
double BreitDoubleGaus(double *x, double *par) 
{
	// Numeric constants
	double invsq2pi = 0.3989422804014;   // (2 pi)^(-1/2)

	// Control constants
	double np = 100.0;      // number of convolution steps
	double sc =   5.0;      // convolution extends to +-sc Gaussian sigmas

	// Variables
	double xx;
	double fland;
	double sum = 0.0;
	double xlow,xupp;
	double step;
	double i;

	double total_width = sqrt(par[2]*par[2] + par[3]*par[3]);

	// Range of convolution integral
	xlow = x[0] - sc * total_width;
	xupp = x[0] + sc * total_width;

	step = (xupp-xlow) / np;

	// Convolution integral of Breit and Gaussian by sum
	for(i=1.0; i<=np/2; i++) {
		xx = xlow + (i-.5) * step;
		fland = TMath::BreitWigner(xx,par[1],par[0]);
		sum += fland * DoubleGaus(x[0],xx,par[2],par[3]);

		xx = xupp - (i-.5) * step;
		fland = TMath::BreitWigner(xx,par[1],par[0]);
		sum += fland * DoubleGaus(x[0],xx,par[2],par[3]);
	} 
	return (step * sum * invsq2pi / total_width);
}

//////////////////////////////////////
// Breit-Wigner TripleGaussian convolution
// Fit parameters:
// par[0]=Width (scale) Breit-Wigner
// par[1]=Most Probable (MP, location) Breit mean
// par[2]=Width 1(sigma) of convoluted Triple Gaussian function
// par[3]=Width 2(sigma) of convoluted Triple Gaussian function
// par[4]=Width 3(sigma) of convoluted Triple Gaussian function
double BreitTripleGaus(double *x, double *par) 
{
	// Numeric constants
	double invsq2pi = 0.3989422804014;   // (2 pi)^(-1/2)

	// Control constants
	double np = 100.0;      // number of convolution steps
	double sc =   5.0;      // convolution extends to +-sc Gaussian sigmas

	// Variables
	double xx;
	double fland;
	double sum = 0.0;
	double xlow,xupp;
	double step;
	double i;

	double total_width = sqrt(par[2]*par[2] + par[3]*par[3] + par[4]*par[4]);

	// Range of convolution integral
	xlow = x[0] - sc * total_width;
	xupp = x[0] + sc * total_width;

	step = (xupp-xlow) / np;

	// Convolution integral of Breit and Gaussian by sum
	for(i=1.0; i<=np/2; i++) {
		xx = xlow + (i-.5) * step;
		fland = TMath::BreitWigner(xx,par[1],par[0]);
		sum += fland * TripleGaus(x[0],xx,par[2],par[3],par[4]);

		xx = xupp - (i-.5) * step;
		fland = TMath::BreitWigner(xx,par[1],par[0]);
		sum += fland * TripleGaus(x[0],xx,par[2],par[3],par[4]);
	} 
	return (step * sum * invsq2pi / total_width);
}

/////////////////////////////////////////////////////////
// fit function = Breit-wigner x Gaussian + exponential
double fitFunctionSB(double *x, double *par) 
{
	double pdf = par[0]*exponential(x,&par[2]) + par[1]*BreitGaus(x,&par[4]);
	if(pdf != pdf) return 1.e-30;
	return pdf;
}

/////////////////////////////////////////////////////////
// fit function = Breit-wigner x DoubleGaussian + exponential
double fitFunctionSB2(double *x, double *par) 
{
	return par[0]*exponential(x,&par[2]) + par[1]*BreitDoubleGaus(x,&par[4]);
}

/////////////////////////////////////////////////////////
// fit function = Breit-wigner x Gaussian
double fitFunctionS(double *x, double *par)
{
	return par[0]*(BreitGaus(x,&par[1]));
}

/////////////////////////////////////////////////////////
// fit function = Breit-wigner x DoubleGaussian 
double fitFunctionS2(double *x, double *par)
{
	return par[0]*(BreitDoubleGaus(x,&par[1]));
}

/////////////////////////////////////////////////////////
// fit function = Breit-wigner x TripleGaussian
double fitFunctionS3(double *x, double *par)
{
	return par[0]*(BreitTripleGaus(x,&par[1]));
}

/////////////////////////////////////////////////////////
// fit function = Breit-wigner x Gaussian + exponential scaled to data
double fitFunctionSBscaled(double *x, double *par) 
{
	return fitFunctionSB(x, par) / FCNINTEGRAL * DATASCALE;
}

#endif

