#include <basicIncludes.h>

#ifndef BINS_H
#define BINS_H

static void setLogBins(Int_t nbins, Double_t min, Double_t max, Double_t* xpoints)
{
	_DEBUG("setLogBins");

	Double_t logmin  = log10(min);
	Double_t logmax  = log10(max);
	Double_t logbinwidth = (Double_t)( (logmax-logmin)/(Double_t)nbins );
	xpoints[0] = min;
	for(Int_t i=1 ; i<=nbins ; i++) xpoints[i] = TMath::Power( 10,(logmin + i*logbinwidth) );
}

static const Int_t    npbins = 20;
static const Double_t pmin   = 1.;
static const Double_t pmax   = 2000.;
static Double_t pbins[npbins+1];

static const Int_t    nlogmassbins = 6;
static const Double_t logmassmin   = 120.;
static const Double_t logmassmax   = 1500.;
static Double_t logmassbins[nlogmassbins+1];

static const Int_t    nlogimassbins = 40;
static const Double_t logimassmin   = 120.;
static const Double_t logimassmax   = 1500.;
static Double_t logimassbins[nlogimassbins+1];

static const Int_t    netabins = 30;
static const Double_t etamin   = -2.5;
static const Double_t etamax   = +2.5;
static const Double_t etax     = 1.;

static const double minMassBin = 120;  // for the asymmetry fit
static const double maxMassBin = 1500; // for the asymmetry fit
static const int    nMassBins  = 6;   // for the asymmetry fit
static const int    niMassBins = 40;  // for the imass histos

static const double minCosTheta = -1.;  // for the acceptance binning
static const double maxCosTheta = +1.;  // for the acceptance binning
static const int    nCosThetaBins = 10; // for the acceptance binning

static const double minyQ   = -2.5; // for the FB false identify probability binning
static const double maxyQ   = +2.5; // for the FB false identify probability binning
static const int    nyQbins = 30;   // for the FB false identify probability binning


static const double minPossibleImass = 5.; // GeV
static const double maxPossibleImass = 7000.; // GeV


#endif

