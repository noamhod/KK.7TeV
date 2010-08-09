/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#ifdef fit_cxx
#include "fit.h"

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
	return par[0]*exponential(x,&par[2]) + par[1]*BreitGaus(x,&par[4]);
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


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 


/////////////////////////////////////////////////////////
// For TMinuit:
// Signal only, Breit Wigner x Double Gaussian
void fcnSignal(int& npar, double* deriv, double& f, double par[], int flag)
{
	vector<double> xVec = *xVecPtr;           // xVecPtr is public
	int n = xVec.size();

	double lnL = 0.0;
	for (int i=0; i<n; i++)
	{
		double x = xVec[i];
		double pdf = fitFunctionS2(&x, par);
		if ( pdf > 0.0 )
		{
			lnL += log(pdf);    // need positive f
		}
		else
		{
			cout << "WARNING -- pdf is negative!!!" << endl;
		}
	}
	f = -2.0 * lnL;         // factor of -2 so minuit gets the errors right 
}

/////////////////////////////////////////////////////////
// For TMinuit:
// Signal and Background, Breit Wigner x Double Gaussian + exponent
void fcnSignalBackground(int& npar, double* deriv, double& f, double par[], int flag)
{
	vector<double> xVec = *xVecPtr;           // xVecPtr is public
	int n = xVec.size();

	double lnL = 0.0;
	for (int i=0; i<n; i++)
	{
		double x = xVec[i];
		double pdf = fitFunctionSB2(&x, par);
		if ( pdf > 0.0 )
		{
			lnL += log(pdf);    // need positive f
		}
		else
		{
			cout << "WARNING -- pdf is negative!!!" << endl;
		}
	}
	f = -2.0 * lnL;         // factor of -2 so minuit gets the errors right 
}

//////////////////////////////////////////////////////////
// So it can be used in a class
static void setfcn(bool signal_only)
{
	if(signal_only) minuit->SetFCN( fcnSignal );
	else            minuit->SetFCN( fcnSignalBackground );
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 


fit::fit()
{
	finitialize();
}

fit::~fit()
{
	ffinalize();
}


void fit::finitialize()
{
	xVecPtr->clear();
}

void fit::ffinalize()
{

}

void fit::fillXvec(double x)
{
	xVecPtr->push_back(x);
}

void fit::minimize(bool signal_only, TCanvas* canv, TH1D* h, double* yields)
{
	//TF1*     fitFCN;
	/*
	double*  par;
	double*  stepSize;
	double*  minVal;
	double*  maxVal;
	string*  parName;
	double*  outpar;
	double*  err;
	
	double   parSignal[6];
	double   parSignalBackground[9];
	
	double   stepSizeSignal[6];           // step sizes
	double   stepSizeSignalBackground[9]; // step sizes
	
	double   minValSignal[6];             // minimum bound on parameter
	double   minValSignalBackground[9];   // minimum bound on parameter
	
	double   maxValSignal[6];             // maximum bound on parameter
	double   maxValSignalBackground[9];   // maximum bound on parameter
	
	string   parNameSignal[6];            // parameter name
	string   parNameSignalBackground[9];  // parameter name

	double   outparSignal[6];             // out paramenters
	double   outparSignalBackground[9];   // out errors
	
	double   errSignal[6];                // out paramenters
	double   errSignalBackground[9];      // out errors
	*/
	
	///// INITIALIZATION:  SIGNAL ONLY
	// Breit-Wigner x Gaussian convolution (can have 3 gaussians)
	parSignal[0] = 100.;    // Scale Signal (Ns)
	parSignal[1] = 2500;       // Breit Wigner Width (gamma)
	parSignal[2] = 90000.;     // Most probable location (peak mean) 
	parSignal[3] = 100.;       // Gaussian sigma 1
	parSignal[4] = 2000.;      // Gaussian sigma 2
	parSignal[5] = 1000.;      // Gaussian sigma 3
	
	minValSignal[0] = 1.;  // Scale Signal (Ns)
	minValSignal[1] = 1000.;   // Breit Wigner Width (gamma)
	minValSignal[2] = XMIN;  // Most probable location (peak mean) 
	minValSignal[3] = 10.;     // Gaussian sigma 1
	minValSignal[4] = 200.;    // Gaussian sigma 2
	minValSignal[5] = 100.;    // Gaussian sigma 3
	
	maxValSignal[0] = 1000.;  // Scale Signal (Ns)
	maxValSignal[1] = 10000.;  // Breit Wigner Width (gamma)
	maxValSignal[2] = XMAX; // Most probable location (peak mean) 
	maxValSignal[3] = 200.;    // Gaussian sigma 1
	maxValSignal[4] = 5000.;   // Gaussian sigma 2
	maxValSignal[5] = 5000.;   // Gaussian sigma 3
	
	stepSizeSignal[0] = 1.;    // Scale Signal (Ns)
	stepSizeSignal[1] = 0.01;  // Breit Wigner Width (gamma)
	stepSizeSignal[2] = 0.01;  // Most probable location (peak mean) 
	stepSizeSignal[3] = 0.01;  // Gaussian sigma 1
	stepSizeSignal[4] = 0.01;  // Gaussian sigma 2
	stepSizeSignal[5] = 0.01;  // Gaussian sigma 3
	
	parNameSignal[0] = "Nsignal";
	parNameSignal[1] = "BWgamma";
	parNameSignal[2] = "MZ0";
	parNameSignal[3] = "Gsigma1";
	parNameSignal[4] = "Gsigma2";
	parNameSignal[5] = "Gsigma3";
	
	
	///// INITIALIZATION:  SIGNAL + BACKGROUND
	// Exponential
	parSignalBackground[0] = 50000.;   // Scale Background (Nb)
	parSignalBackground[1] = 30000.;   // Scale Signal (Ns)
	parSignalBackground[2] = 1.;       // Exp: constant argument
	parSignalBackground[3] = -0.0001; // Exp: the multiplier of the x argument
	// Breit-Wigner x Gaussian convolution
	parSignalBackground[4] = 2500.;    // Breit Wigner Width (gamma)
	parSignalBackground[5] = 90000.;   // Most probable location (peak mean) 
	parSignalBackground[6] = 2000.;     // Gaussian sigma 1
	parSignalBackground[7] = 3000.;    // Gaussian sigma 2 
	parSignalBackground[8] = 3000.;    // Gaussian sigma 3
	
	minValSignalBackground[0] = 10000.;   // Scale Background (Nb)
	minValSignalBackground[1] = 10000.;   // Scale Signal (Ns)
	minValSignalBackground[2] = 0.1;      // Exp: constant argument
	minValSignalBackground[3] = -1.;     // Exp: the multiplier of the x argument
	minValSignalBackground[4] = 1000.;   // Breit Wigner Width (gamma)
	minValSignalBackground[5] = XMIN;  // Most probable location (peak mean) 
	minValSignalBackground[6] = 1000.;     // Gaussian sigma 1
	minValSignalBackground[7] = 1000.;    // Gaussian sigma 2
	minValSignalBackground[8] = 1000.;    // Gaussian sigma 3
	
	maxValSignalBackground[0] = 80000;  // Scale Background (Nb)
	maxValSignalBackground[1] = 80000;  // Scale Signal (Ns)
	maxValSignalBackground[2] = 1.5;    // Exp: constant argument
	maxValSignalBackground[3] = 0.;  // Exp: the multiplier of the x argument
	maxValSignalBackground[4] = 5000.;  // Breit Wigner Width (gamma)
	maxValSignalBackground[5] = XMAX; // Most probable location (peak mean) 
	maxValSignalBackground[6] = 4000.;    // Gaussian sigma 1
	maxValSignalBackground[7] = 5000.;   // Gaussian sigma 2
	maxValSignalBackground[8] = 5000.;   // Gaussian sigma 3
	
	stepSizeSignalBackground[0] = 1.;    // Scale Background (Nb)
	stepSizeSignalBackground[1] = 1.;    // Scale Signal (Ns)
	stepSizeSignalBackground[2] = 0.001; // Exp: constant argument
	stepSizeSignalBackground[3] = 0.000001; // Exp: the multiplier of the x argument
	stepSizeSignalBackground[4] = 0.1;  // Breit Wigner Width (gamma)
	stepSizeSignalBackground[5] = 0.1;  // Most probable location (peak mean) 
	stepSizeSignalBackground[6] = 0.1;  // Gaussian sigma 1
	stepSizeSignalBackground[7] = 0.1;  // Gaussian sigma 2
	stepSizeSignalBackground[8] = 0.1;  // Gaussian sigma 3
	
	parNameSignalBackground[0] = "Nbackground";
	parNameSignalBackground[1] = "Nsignal";
	parNameSignalBackground[2] = "expConst";
	parNameSignalBackground[3] = "expScaler";
	parNameSignalBackground[4] = "BWgamma";
	parNameSignalBackground[5] = "MZ0";
	parNameSignalBackground[6] = "Gsigma1";
	parNameSignalBackground[7] = "Gsigma2";
	parNameSignalBackground[8] = "Gsigma3";

	
	double bin_width = h->GetBinWidth(1);
	int index_mean;
	int index_gamma;
	int index_sigma1;
	int index_sigma2;
	int index_sigma3;
	int index_signal;
	
	if(signal_only)
	{
		index_mean = 2;
		index_gamma = 1;
		index_sigma1 = 3;
		index_sigma2 = 4; 
		index_sigma3 = 5; 
		index_signal = 0;
		//fitFCN = new TF1("fitFCN",fitFunctionS, XMIN, XMAX ,4);
		fitFCN = new TF1("fitFCN",fitFunctionS2, XMIN, XMAX ,5);
		//fitFCN = new TF1("fitFCN",fitFunctionS3, XMIN, XMAX ,6);
		par      = parSignal;
		stepSize = stepSizeSignal;
		minVal   = minValSignal;
		maxVal   = maxValSignal;
		parName  = parNameSignal;
		cout << "input parameters: " << par[0] << ", "
									 << par[1] << ", "
									 << par[2] << ", "
									 << par[3] << ", "
									 << par[4] << ", "
									 << par[5] << endl;
		minuit = new TMinuit(6);
	}
	else
	{
		index_mean = 5;
		index_gamma = 4;
		index_sigma1 = 6;
		index_sigma2 = 7;
		index_sigma3 = 8;
		index_signal = 1;
		fitFCN = new TF1("fitFCN",fitFunctionSB2, XMIN, XMAX ,8);
		par = parSignalBackground;
		stepSize = stepSizeSignalBackground;
		minVal   = minValSignalBackground;
		maxVal   = maxValSignalBackground;
		parName  = parNameSignalBackground;
		cout << "input parameters: " << par[0] << ", "
									 << par[1] << ", "
									 << par[2] << ", "
									 << par[3] << ", "
									 << par[4] << ", "
									 << par[5] << ", "
									 << par[6] << ", "
									 << par[7] << ", "
									 << par[8] << endl;
		minuit = new TMinuit(9);
	}
	
	/*
	// set initial parameters
	fitFCN->SetParameters(par);

	// set histogrma range and fit first time
	h->SetAxisRange(20000,200000,"X");
	h->Fit(fitFCN,"VN","",20000.,200000.);        

	// get fit parameters
	double *ParFit;
	ParFit = fitFCN->GetParameters();

	// refit using previous paramaneters and restricted fit range in mean +/- 3*signal_width
	fitFCN->SetParameters(ParFit);        

	// build fit range from data
	double signal_width = sqrt(ParFit[index_gamma]*ParFit[index_gamma] 
	+ ParFit[index_sigma1]*ParFit[index_sigma1]
	+ ParFit[index_sigma2]*ParFit[index_sigma2]);
	//+ ParFit[index_sigma3]*ParFit[index_sigma3]);

	double Lfit = ParFit[index_mean] - 5*signal_width;
	double Rfit = ParFit[index_mean] + 5*signal_width;

	// print 
	cout << "fit with:" << endl;
	cout << "- mean = " << ParFit[index_mean] << endl;
	cout << "- fit range = " << Lfit << " , " << Rfit << endl;

	// refit
	fitFCN->SetLineColor(kBlue);
	fitFCN->SetLineStyle(1);
	fitFCN->SetLineWidth(2);
	h->Fit(fitFCN,"V","pe1",Lfit,Rfit);

	// get final parameters (yields)
	ParFit = fitFCN->GetParameters();
	yields[0] = ParFit[index_signal]/bin_width;
	yields[1] = ParFit[0]/bin_width;
	
	canv->cd();
	fitFCN->Draw("sames");
	*/
	
	////////////////////
	// For TMinuit: ////
	setfcn(signal_only);
	////////////////////
	
	int npar = (signal_only) ? 6 : 9;
	
	for (int i=0; i<npar; i++)
	{
		minuit->DefineParameter( i, parName[i].c_str(), par[i], stepSize[i], minVal[i], maxVal[i] );
	}

	// Do the minimization!
	minuit->Migrad();       // Minuit's best minimization algorithm
	
	for (int i=0; i<npar; i++)
	{
		if(signal_only)
		{
			minuit->GetParameter( i, outparSignal[i], errSignal[i] );
			outpar = outparSignal;
			err    = errSignal;
		}
		else
		{
			minuit->GetParameter( i, outparSignalBackground[i], errSignalBackground[i] );
			outpar = outparSignalBackground;
			err    = errSignalBackground;
		}
	}

	for(int i=0 ; i<npar ; i++)
	{
		cout << parName[i] << " = " << outpar[i] << " +- " << err[i] << endl;;
	}

	fitFCN->SetParameters(outpar);
	m_fFitted = (TF1*)fitFCN->Clone();
	/*
	canv->cd();
	fitFCN->SetLineStyle(1);
	fitFCN->SetLineColor(kBlue);
	fitFCN->SetLineWidth(2);
	fitFCN->Draw("sames");
	*/
	
	
	//--------------------------- test ---------------------------
	//double p[9];
	///// INITIALIZATION:  SIGNAL + BACKGROUND
	// Exponential
	p[0] = 50000.;   // Scale Background (Nb)
	p[1] = 30000.;   // Scale Signal (Ns)
	p[2] = 1.;       // Exp: constant argument
	p[3] = -0.0001; // Exp: the multiplier of the x argument
	// Breit-Wigner x Gaussian convolution
	p[4] = 2500.;    // Breit Wigner Width (gamma)
	p[5] = 90000.;   // Most probable location (peak mean) 
	p[6] = 2000.;    // Gaussian sigma 1
	p[7] = 3000.;    // Gaussian sigma 2 
	p[8] = 3000.;    // Gaussian sigma 3
	//TF1* guess = new TF1("guess",fitFunctionSB2, XMIN, XMAX ,8);
	guess = new TF1("guess",fitFunctionSB2, XMIN, XMAX ,8);
	guess->SetParameters(p);
	m_fGuess = (TF1*)guess->Clone();
	/*
	guess->SetLineStyle(1);
	guess->SetLineColor(kRed);
	guess->SetLineWidth(2);
	guess->Draw("sames");
	*/
	cout << "\nIntegral = " << guess->Integral(XMIN, XMAX) << "\n" << endl;
	//---------------------------------------------------------------
}

#endif

