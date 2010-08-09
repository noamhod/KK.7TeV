/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#ifndef FIT_H
#define FIT_H

bool docout = true;
vector<double>* xVecPtr = new vector<double>;

TMinuit* minuit;

double XMIN = 50000.;
double XMAX = 120000.;

TF1* guess;
TF1* fitFCN;

static double*  par;
static double*  stepSize;
static double*  minVal;
static double*  maxVal;
static string*  parName;
static double*  outpar;
static double*  err;


static double   parSignal[6];
static double   parSignalBackground[9];

static double   stepSizeSignal[6];           // step sizes
static double   stepSizeSignalBackground[9]; // step sizes

static double   minValSignal[6];             // minimum bound on parameter
static double   minValSignalBackground[9];   // minimum bound on parameter

static double   maxValSignal[6];             // maximum bound on parameter
static double   maxValSignalBackground[9];   // maximum bound on parameter

static string   parNameSignal[6];            // parameter name
static string   parNameSignalBackground[9];  // parameter name

static double   outparSignal[6];             // out paramenters
static double   outparSignalBackground[9];   // out errors

static double   errSignal[6];                // out paramenters
static double   errSignalBackground[9];      // out errors

static double p[9];


class fit
{
	public:
		TF1* m_fGuess;
		TF1* m_fFitted;

	public:
		fit();
		~fit();

		void finitialize();
		void ffinalize();

		void fillXvec(double x);

		void fcn(int& npar, double* deriv, double& f, double par[], int flag);
		
		void minimize(bool signal_only, TH1D* h, double* yields);
		
	private:
		
};
#endif

