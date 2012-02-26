#include "../include/rawStd.h"
#include "../include/rawROOT.h"
#include "../include/rawStd.h"
#include "../include/logs.h"
#include "../include/bins.h"

void bintest()
{
	/* setSqrtBins(nsqrtg4bins, sqrtg4min, sqrtg4max, sqrtg4bins);
	for(int i=0 ; i<=nsqrtg4bins ; i++)
	{
		cout << sqrtg4bins[i] << " | ";
	}
	cout << endl;

	for(int i=0 ; i<=nsqrtg4bins ; i++)
	{
		cout << sqrt(sqrt(sqrtg4bins[i])) << " | ";
	}
	cout << endl; */

	
	const unsigned int N = 100;
	const double       d = 0.03;
	const int          p = 4;
	Double_t xpoints[N+1];
	setPowerBins(N,d,p,xpoints);
	for(int i=0 ; i<=N ; i++) cout << "|" << xpoints[i];
	cout << "|" << endl; 

	int nbinslessthanone = 0;
	for(int i=0 ; i<=N ; i++) {if(xpoints[i]<1.) nbinslessthanone++;}
	cout << "nbins less than one: " << nbinslessthanone << endl;


	const unsigned int n = 400;
	const double shift = 1./16.;
	const double xmin = 0.-shift;
	const double xmax = 50-shift;
	TH1D* h = new TH1D("","",n,xmin,xmax);
	for(int i=1 ; i<=n ; i++) cout << "|" << h->GetBinCenter(i);
	cout << "|" << endl;
}
