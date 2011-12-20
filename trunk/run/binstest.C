#include "../include/rawStd.h"
#include "../include/rawROOT.h"
#include "../include/types.h"
#include "../include/logs.h"
#include "../include/style.h"
#include "../include/bins.h"
#include "../include/histos.h"
#include "../include/fkinematics.h"
#include "../include/units.h"

void binstest()
{
	setLogBins(nloglimitimassbins, loglimitimassmin, loglimitimassmax, loglimitimassbins);
	for(Int_t i=0 ; i<=nloglimitimassbins ; i++) cout << loglimitimassbins[i] << ", ";
	cout << endl;
}

