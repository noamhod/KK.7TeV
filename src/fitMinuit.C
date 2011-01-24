/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#ifdef fit_cxx
#include "fitMinuit.h"



/////////////////////////////////////////////////////////
// For TMinuit:
// Signal only, Breit Wigner x Double Gaussian
void fcnSignal(int& npar, double* deriv, double& f, double par[], int flag)
{
	// irrelevant
	if(false) cout << "npar="  << npar  << endl;
	if(false) cout << "deriv=" << deriv << endl;
	if(false) cout << "flag="  << flag  << endl;

	vector<double> xVec = *m_xVecPtr;           // m_xVecPtr is public
	int n = xVec.size();

	double lnL = 0.0;
	for (int i=0; i<n; i++)
	{
		double x = xVec[i];
		//double pdf = fitFunctionS2(&x, par);
		double pdf = fitFunctionS(&x, par);
		if ( pdf > 0. )
		{
			lnL += log(pdf);    // need positive f
		}
		else
		{
			//cout << "WARNING -- pdf = " << pdf << endl;
		}
	}
	f = -2.0 * lnL;         // factor of -2 so minuit gets the errors right 
}

/////////////////////////////////////////////////////////
// For TMinuit:
// Signal and Background, Breit Wigner x Double Gaussian + exponent
void fcnSignalBackground(int& npar, double* deriv, double& f, double par[], int flag)
{
	// irrelevant
	if(false) cout << "npar="  << npar  << endl;
	if(false) cout << "deriv=" << deriv << endl;
	if(false) cout << "flag="  << flag  << endl;

	vector<double> xVec = *m_xVecPtr;           // m_xVecPtr is public
	int n = xVec.size();

	double lnL = 0.0;
	for (int i=0; i<n; i++)
	{
		double x = xVec[i];
		//double pdf = fitFunctionSB2(&x, par);
		double pdf = fitFunctionSB(&x, par);
		if ( pdf > 0. )
		{
			lnL += log(pdf);    // need positive f
		}
		else
		{
			//cout << "WARNING -- pdf = " << pdf << endl;
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


fitMinuit::fitMinuit()
{

}

fitMinuit::fitMinuit(vector<double>* x)
{
	m_xVecPtr = x;
}

fitMinuit::~fitMinuit()
{

}

void fitMinuit::minimize(bool signal_only, TH1D* h, double* yields)
{
	///// INITIALIZATION:  SIGNAL ONLY
	// Breit-Wigner x Gaussian convolution (can have 3 gaussians)
	parSignal[0] = 100.;    // Scale Signal (Ns)
	parSignal[1] = 2.5*GeV2TeV;       // Breit Wigner Width (gamma)
	parSignal[2] = 90.*GeV2TeV;     // Most probable location (peak mean) 
	parSignal[3] = 0.1*GeV2TeV;       // Gaussian sigma 1
	parSignal[4] = 2.*GeV2TeV;      // Gaussian sigma 2
	parSignal[5] = 1.*GeV2TeV;      // Gaussian sigma 3
	
	minValSignal[0] = 1.;  // Scale Signal (Ns)
	minValSignal[1] = 0;   // Breit Wigner Width (gamma)
	minValSignal[2] = XMIN;  // Most probable location (peak mean) 
	minValSignal[3] = 0;     // Gaussian sigma 1
	minValSignal[4] = 0;    // Gaussian sigma 2
	minValSignal[5] = 0;    // Gaussian sigma 3
	
	maxValSignal[0] = 0;  // Scale Signal (Ns)
	maxValSignal[1] = 0;  // Breit Wigner Width (gamma)
	maxValSignal[2] = XMAX; // Most probable location (peak mean) 
	maxValSignal[3] = 0;    // Gaussian sigma 1
	maxValSignal[4] = 0;   // Gaussian sigma 2
	maxValSignal[5] = 0;   // Gaussian sigma 3
	
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
	parSignalBackground[0] = scale2bg(h);   // Scale Background (Nb)
	parSignalBackground[1] = scale2data(h);   // Scale Signal (Ns)
	parSignalBackground[2] = 2.2e0;       // Exp: constant argument
	parSignalBackground[3] = -1.7e-5; // Exp: the multiplier of the x argument
	// Breit-Wigner x Gaussian convolution
	parSignalBackground[4] = 2.5*GeV2TeV;    // Breit Wigner Width (gamma)
	parSignalBackground[5] = 90.*GeV2TeV;   // Most probable location (peak mean) 
	parSignalBackground[6] = 5.*GeV2TeV;     // Gaussian sigma 1
	//parSignalBackground[7] = 3.*GeV2TeV;    // Gaussian sigma 2 
	//parSignalBackground[8] = 3.*GeV2TeV;    // Gaussian sigma 3
	
	minValSignalBackground[0] = 0;   // Scale Background (Nb)
	minValSignalBackground[1] = 0; // Scale Signal (Ns)
	minValSignalBackground[2] = 0;      // Exp: constant argument
	minValSignalBackground[3] = 0;     // Exp: the multiplier of the x argument
	minValSignalBackground[4] = 0;   // Breit Wigner Width (gamma)
	minValSignalBackground[5] = 0;//XMIN;  // Most probable location (peak mean) 
	minValSignalBackground[6] = 0;     // Gaussian sigma 1
	//minValSignalBackground[7] = 0;   // Gaussian sigma 2
	//minValSignalBackground[8] = 0;   // Gaussian sigma 3
	
	maxValSignalBackground[0] = 0;  // Scale Background (Nb)
	maxValSignalBackground[1] = 0;  // Scale Signal (Ns)
	maxValSignalBackground[2] = 0;    // Exp: constant argument
	maxValSignalBackground[3] = 0;  // Exp: the multiplier of the x argument
	maxValSignalBackground[4] = 0;  // Breit Wigner Width (gamma)
	maxValSignalBackground[5] = 0;//XMAX; // Most probable location (peak mean) 
	maxValSignalBackground[6] = 0;    // Gaussian sigma 1
	//maxValSignalBackground[7] = 0;   // Gaussian sigma 2
	//maxValSignalBackground[8] = 0;   // Gaussian sigma 3
	
	stepSizeSignalBackground[0] = 0.0001;    // Scale Background (Nb)
	stepSizeSignalBackground[1] = 0.0001;    // Scale Signal (Ns)
	stepSizeSignalBackground[2] = 0.0001; // Exp: constant argument
	stepSizeSignalBackground[3] = 0.000000001; // Exp: the multiplier of the x argument
	stepSizeSignalBackground[4] = 0.0001;  // Breit Wigner Width (gamma)
	stepSizeSignalBackground[5] = 0.0001;  // Most probable location (peak mean) 
	stepSizeSignalBackground[6] = 0.0001;  // Gaussian sigma 1
	//stepSizeSignalBackground[7] = 0.01;  // Gaussian sigma 2
	//stepSizeSignalBackground[8] = 0.01;  // Gaussian sigma 3
	
	parNameSignalBackground[0] = "Nbackground";
	parNameSignalBackground[1] = "Nsignal";
	parNameSignalBackground[2] = "expConst";
	parNameSignalBackground[3] = "expScaler";
	parNameSignalBackground[4] = "BWgamma";
	parNameSignalBackground[5] = "MZ0";
	parNameSignalBackground[6] = "Gsigma1";
	//parNameSignalBackground[7] = "Gsigma2";
	//parNameSignalBackground[8] = "Gsigma3";
	

	int index_signal;
	
	if(signal_only)
	{
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
		index_signal = 0;
	}
	else
	{
		fitFCN = new TF1("fitFCN",fitFunctionSB, XMIN, XMAX ,7); // used to be 8 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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
									 << par[6] << endl;
									// << par[7] << ", "
									 //<< par[8] << endl;
		minuit = new TMinuit(7);
		index_signal = 1;
	}

	
	
	//--------------------------------------------------------------------------------
	// simple minuit fitMinuit
	//--------------------------------------------------------------------------------
	////////////////////
	// For TMinuit: ////
	setfcn(signal_only);
	////////////////////
	
	int npar = (signal_only) ? 6 : 7;
	
	for (int i=0; i<npar; i++)
	{
		minuit->DefineParameter( i, parName[i].c_str(), par[i], stepSize[i], minVal[i], maxVal[i] );
	}

	// Do the minimization!
	minuit->Migrad();       // Minuit's best minimization algorithm
	
	for (int i=0; i<npar; i++)
	{
		if(signal_only) minuit->GetParameter( i, outparSignal[i], errSignal[i] );
		else            minuit->GetParameter( i, outparSignalBackground[i], errSignalBackground[i] );
	}
	
	if(signal_only)
	{
		outpar = outparSignal;
		err    = errSignal;
	}
	else
	{
		outpar = outparSignalBackground;
		err    = errSignalBackground;
	}

	for(int i=0 ; i<npar ; i++)
	{
		cout << parName[i] << " = " << outpar[i] << " +- " << err[i] << endl;;
	}

	fitFCN->SetParameters(outpar);
	
	FCNINTEGRAL = fitFCN->Integral(XMIN,XMAX);
	DATASCALE   = scale2data(h);
	cout << "DATASCALE=" << DATASCALE << ", FCNINTEGRAL=" << FCNINTEGRAL << endl;
	
	fScaled  = new TF1("fScaled", fitFunctionSBscaled, XMIN, XMAX ,7);
	fScaled->SetParameters(outpar);
	
	yields[0] = outpar[index_signal];
    yields[1] = outpar[0];
	cout << "\nyields[0] = " <<  yields[0] << endl;
	cout << "yields[1] = " <<  yields[1] << "\n" << endl;
	cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n" << endl;
	
	///////////////////////////////////////////
	//fFitted = (TF1*)fScaled->Clone(); ///////
	///////////////////////////////////////////
	//--------------------------------------------------------------------------------
	
	
	
	
	//--------------------------- test ---------------------------
	///// INITIALIZATION:  SIGNAL + BACKGROUND
	// Exponential
	ppar[0] = scale2bg(h);   // Scale Background (Nb)
	ppar[1] = scale2data(h);   // Scale Signal (Ns)
	ppar[2] = 2.;       // Exp: constant argument
	ppar[3] = -0.00001; // Exp: the multiplier of the x argument
	// Breit-Wigner x Gaussian convolution
	ppar[4] = 2.5*GeV2TeV;    // Breit Wigner Width (gamma)
	ppar[5] = 90.*GeV2TeV;   // Most probable location (peak mean) 
	ppar[6] = 2.*GeV2TeV;    // Gaussian sigma 1
	//ppar[7] = 3000.;    // Gaussian sigma 2 
	//ppar[8] = 3000.;    // Gaussian sigma 3
	guess = new TF1("guess",fitFunctionSB, XMIN, XMAX ,8);
	guess->SetParameters(ppar);
	//fGuess = (TF1*)guess->Clone();
	//cout << "\nIntegral = " << guess->Integral(XMIN, XMAX) << "\n" << endl;
	//---------------------------------------------------------------
}

#endif

