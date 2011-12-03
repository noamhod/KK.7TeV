//#include <basicIncludes.h>
#include <TH1.h>
#include <TMath.h>

#ifndef BINS_H
#define BINS_H

static void setLogBins(Int_t nbins, Double_t min, Double_t max, Double_t* xpoints)
{
	//_DEBUG("setLogBins");

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

static const Int_t    nlogimassbins = 50;
static const Double_t logimassmin   = 120.;
static const Double_t logimassmax   = 1500.;
static Double_t logimassbins[nlogimassbins+1];

static const Int_t    nlogfullimassbins = 40;
static const Double_t logfullimassmin   = 70.;
static const Double_t logfullimassmax   = 3000.;
static Double_t logfullimassbins[nlogfullimassbins+1];

static const Int_t    nloglimitimassbins = 50;
static const Double_t loglimitimassmin   = 0.13;
static const Double_t loglimitimassmax   = 4;
static Double_t loglimitimassbins[nloglimitimassbins+1];

static const Int_t    nlinlimitimassbins = 50;
static const Double_t linlimitimassmin   = 0.13;
static const Double_t linlimitimassmax   = 4.;

static const Int_t    nlinfullimassbins = 250;
static const Double_t linfullimassmin   = 70.;
static const Double_t linfullimassmax   = 2000.;

static const Int_t    nlogptbins = 50;
static const Double_t logptmin   = 0.001;
static const Double_t logptmax   = 1500.;
static Double_t logptbins[nlogptbins+1];

static const Int_t    nlogqtbins = 40;
static const Double_t logqtmin   = 0.001;
static const Double_t logqtmax   = 1000.;
static Double_t logqtbins[nlogqtbins+1];

static const Int_t    netabins = 30;
static const Double_t etamin   = -2.5;
static const Double_t etamax   = +2.5;

static const Int_t    nphibins = 12;
static const Double_t phimin   = -TMath::Pi();
static const Double_t phimax   = +TMath::Pi();

static const double minMassBin = 120;  // for the asymmetry fit
static const double maxMassBin = 1500; // for the asymmetry fit
static const int    nMassBins  = 6;   // for the asymmetry fit
static const int    niMassBins = 40;  // for the imass histos

static const double minFullCosTheta = -1.;
static const double maxFullCosTheta = +1.;
static const int    nFullCosThetaBins = 50;

static const double minCosTheta = -1.;  // for the acceptance binning
static const double maxCosTheta = +1.;  // for the acceptance binning
static const int    nCosThetaBins = 10; // for the acceptance binning

static const double minCosThetaLimit = -1.;  // for the limit binning
static const double maxCosThetaLimit = +1.;  // for the limit binning
static const int    nCosThetaBinsLimit = 2; // for the limit binning

static const double mindEtaLimit = 0.;  // for the limit binning
static const double maxdEtaLimit = +4.;  // for the limit binning
static const int    ndEtaBinsLimit = 3; // for the limit binning

static const double minAbsCosTheta   = 0.;  // for the acceptance binning
static const double maxAbsCosTheta   = +1.; // for the acceptance binning
static const int    nAbsCosThetaBins = 8;   // for the acceptance binning

static const double minfullyQ   = -2.5;
static const double maxfullyQ   = +2.5;
static const int    nfullyQbins = 50;

static const double minyQ   = -2.5; // for the FB false identify probability binning
static const double maxyQ   = +2.5; // for the FB false identify probability binning
static const int    nyQbins = 30;   // for the FB false identify probability binning

static const double minabsyQ   = 0.;   // for the 2d acceptance binning
static const double maxabsyQ   = +2.5; // for the 2d acceptance binning
static const int    nabsyQbins = 8;    // for the 2d acceptance binning

static const double minPyQ   = -2.5; // for the FB false identify probability binning
static const double maxPyQ   = +2.5; // for the FB false identify probability binning
static const int    nPyQbins = 16;   // for the FB false identify probability binning

static const double minchi   = 0.; // for the chi binning
static const double maxchi   = 5.; // for the chi binning
static const int    nchibins = 20;   // for the chi binning

static const double minystar   = -3.; // for the chi binning
static const double maxystar   = +3.; // for the chi binning
static const int    nystarbins = 30;   // for the chi binning

const int      etalogicnbins = 22;
const Double_t etalogicbins[etalogicnbins+1] =
				{
					-2.5,-2.18,-1.95,-1.74,-1.52,-1.37,-1.05,-0.84,-0.63,-0.42,-0.21,
					0,
					+0.21,+0.42,+0.63,+0.84,+1.05,+1.37,+1.52,+1.74,+1.95,+2.18,+2.5
				};
				
const int             nlogicmassbins = 44;
static const Double_t logicmassmin   = 75.;
static const Double_t logicmassmax   = 2200.;
const Double_t logicmassbins[nlogicmassbins+1] =
				{
					75,85,95,105,120,
					135,150,165,180,195,215,230,250,
					270,290,310,330,350,375,400,
					430,460,490,520,560,600,
					640,680,720,760,800,
					850,900,950,1000,
					1075,1150,1250,
					1375,1500,
					1625,1750,
					1875,2000,
					2200
				};
const int      ndymassbins = 11;
const Double_t dymassbins[ndymassbins+1] =
				{
					75,120,250,400,600,800,1000,1250,1500,1750,2000,2200
				};
TH1* hDYbins = new TH1("hDYbins","hDYbins",ndymassbins,dymassbins);				


static const Double_t etax    = 1.05;
static const Double_t ystarlow  = 0.6;
static const Double_t ystarhigh = 1.7;

static const double minPossibleImass = 5.; // GeV
static const double maxPossibleImass = 7000.; // GeV


#endif

