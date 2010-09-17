/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#ifdef fitROOT_cxx
#include "fitROOT.h"

fitROOT::fitROOT()
{

}

fitROOT::~fitROOT()
{
	
}

void fitROOT::minimize(bool signal_only, TH1D* h, double* yields)
{
	///// INITIALIZATION:  SIGNAL ONLY
	// Breit-Wigner x Gaussian convolution (can have 3 gaussians)
	parSignal[0] = 100.;    // Scale Signal (Ns)
	parSignal[1] = 2500;       // Breit Wigner Width (gamma)
	parSignal[2] = 90000.;     // Most probable location (peak mean) 
	parSignal[3] = 100.;       // Gaussian sigma 1
	parSignal[4] = 2000.;      // Gaussian sigma 2
	parSignal[5] = 1000.;      // Gaussian sigma 3
	
	
	
	///// INITIALIZATION:  SIGNAL + BACKGROUND
	// Exponential
	parSignalBackground[0] = scale2bg(h);   // Scale Background (Nb)
	parSignalBackground[1] = scale2data(h);   // Scale Signal (Ns)
	parSignalBackground[2] = 2.2e0;       // Exp: constant argument
	parSignalBackground[3] = -1.7e-5; // Exp: the multiplier of the x argument
	// Breit-Wigner x Gaussian convolution
	parSignalBackground[4] = 2.5e3;    // Breit Wigner Width (gamma)
	parSignalBackground[5] = 9.e4;   // Most probable location (peak mean) 
	parSignalBackground[6] = 5.e3;     // Gaussian sigma 1
	//parSignalBackground[7] = 3000.;    // Gaussian sigma 2 
	//parSignalBackground[8] = 3000.;    // Gaussian sigma 3
	
	
	
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
	}
	else
	{
		index_mean = 5;
		index_gamma = 4;
		index_sigma1 = 6;
		index_sigma2 = 7;
		index_sigma3 = 8;
		index_signal = 1;
		fitFCN = new TF1("fitFCN",fitFunctionSB, XMIN, XMAX ,7); // used to be 8 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		par = parSignalBackground;
	}
	

	//--------------------------------------------------------------------------------
	// simple root fit
	//--------------------------------------------------------------------------------
	double bin_width = h->GetBinWidth(1);
	// irrelevant
	if(false) cout << "bin_width="  << bin_width  << endl;
	
	// set initial parameters
	fitFCN->SetParameters(par);
	
	// set histogrma range and fit first time
	h->SetAxisRange(20000,200000,"X");
	h->Fit(fitFCN,"VN","",XMIN,XMAX);        

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
	
	/////////////////////////////////////////
	//fFitted = (TF1*)fitFCN->Clone(); ////////
	/////////////////////////////////////////
	//----------------------------------------------------------------------------------
	
	
	
	
	//--------------------------- test ---------------------------
	///// INITIALIZATION:  SIGNAL + BACKGROUND
	// Exponential
	p[0] = scale2bg(h);   // Scale Background (Nb)
	p[1] = scale2data(h);   // Scale Signal (Ns)
	p[2] = 2.;       // Exp: constant argument
	p[3] = -0.00001; // Exp: the multiplier of the x argument
	// Breit-Wigner x Gaussian convolution
	p[4] = 2500.;    // Breit Wigner Width (gamma)
	p[5] = 90000.;   // Most probable location (peak mean) 
	p[6] = 2000.;    // Gaussian sigma 1
	//p[7] = 3000.;    // Gaussian sigma 2 
	//p[8] = 3000.;    // Gaussian sigma 3
	guess = new TF1("guess",fitFunctionSB, XMIN, XMAX ,8);
	guess->SetParameters(p);
	//fGuess = (TF1*)guess->Clone();
	//cout << "\nIntegral = " << guess->Integral(XMIN, XMAX) << "\n" << endl;
	//---------------------------------------------------------------
}

#endif

