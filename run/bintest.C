#include "../include/rawStd.h"
#include "../include/rawROOT.h"
#include "../include/rawStd.h"
#include "../include/logs.h"
#include "../include/bins.h"

void bintest()
{
	setSqrtBins(nsqrtg4bins, sqrtg4min, sqrtg4max, sqrtg4bins);
	for(int i=0 ; i<=nsqrtg4bins ; i++)
	{
		cout << sqrtg4bins[i] << " | ";
	}
	cout << endl;

	for(int i=0 ; i<=nsqrtg4bins ; i++)
	{
		cout << sqrt(sqrt(sqrtg4bins[i])) << " | ";
	}
	cout << endl;
}
