#ifndef BINS_H
#define BINS_H

#include <TH1.h>
#include <TMath.h>

static void setLogBins(Int_t nbins, Double_t min, Double_t max, Double_t* xpoints)
{
	_DEBUG("setLogBins");
	Double_t logmin  = log10(min);
	Double_t logmax  = log10(max);
	Double_t logbinwidth = (Double_t)( (logmax-logmin)/(Double_t)nbins );
	xpoints[0] = min;
	for(Int_t i=1 ; i<=nbins ; i++) xpoints[i] = TMath::Power( 10,(logmin + i*logbinwidth) );
}

static void setSqrtBins(Int_t nbins, Double_t min, Double_t max, Double_t* xpoints)
{
	_DEBUG("setSqrtBins");
	Double_t sqrtmin = sqrt(min);
	Double_t sqrtmax = sqrt(max);
	Double_t sqrtbinwidth = (Double_t)((sqrtmax-sqrtmin)/(Double_t)nbins);
	xpoints[0] = min;
	for(int i=1 ; i<=nbins ; i++) xpoints[i] = pow(sqrtmin+i*sqrtbinwidth,2);
}

static void setPowerBins(Int_t nbins, Double_t step, Int_t power, Double_t* xpoints)
{
	_DEBUG("setPowerBins");
	xpoints[0] = -1.0*TMath::Power(1*step,power);
	for(int i=1 ; i<=nbins ; i++)
	{
		xpoints[i] = TMath::Power(i*step,power);
	}
}

static void setLinBins(Int_t nbins, Double_t min, Double_t max, Double_t* xpoints)
{
	_DEBUG("setSqrtBins");
	Double_t binwidth = (Double_t)((max-min)/(Double_t)nbins);
	xpoints[0] = min;
	for(int i=1 ; i<=nbins ; i++) xpoints[i] = min+i*binwidth;
}

static const int bins2chop = 9; // h1 should start at ~128 GeV


static const Int_t npowerbins = 100;
static const Double_t step    = 0.03;
static const Int_t power      = 4;
static Double_t powerbins[npowerbins+1];

static const double mXXmin = 130.;
static const double mXXmax = 5030.;
static const double dmXX   = 100.;

static const Double_t g4shift = 0.;//1./16.;
static const Int_t    ng4bins = 400;
static const Double_t g4min   = 0.-g4shift;
static const Double_t g4max   = 50.-g4shift;

static const Int_t    nsqrtg4bins = 50;
static const Double_t sqrtg4min   = 0.;
static const Double_t sqrtg4max   = 100.;
static Double_t sqrtg4bins[nsqrtg4bins+1];

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

static const Int_t    nloglimitimassbins = 56;//70;//56;
static const Double_t loglimitimassmin   = 0.07;//0.07;
static const Double_t loglimitimassmax   = 3.0;//5.2;//3.;
static Double_t loglimitimassbins[nloglimitimassbins+1];

static const Int_t    nlinlimitimassbins = 50;
static const Double_t linlimitimassmin   = 0.13;
static const Double_t linlimitimassmax   = 4.;

static const Int_t    nlinfullimassbins = 250;
static const Double_t linfullimassmin   = 70.;
static const Double_t linfullimassmax   = 2000.;

// official imass
static const Int_t    nlogofficialimassbins = 56;
static const Double_t logofficialimassmin   = 70.;
static const Double_t logofficialimassmax   = 3000.;
static Double_t logofficialimassbins[nlogofficialimassbins+1];

static const Int_t    nlogisoimassbins = 20;
static const Double_t logisoimassmin   = 70.;
static const Double_t logisoimassmax   = 600.;
static Double_t logisoimassbins[nlogisoimassbins+1];


static const Int_t    nlingevimassbins = 2930;
static const Double_t lingevimassmin   = 70.;
static const Double_t lingevimassmax   = 3000.;

// official pT
static const Int_t    nsqrtofficialptbins = 40;
static const Double_t sqrtofficialptmin   = 25.;
static const Double_t sqrtofficialptmax   = 1000.;
static Double_t sqrtofficialptbins[nsqrtofficialptbins+1];
// official qT
static const Int_t    nsqrtofficialqtbins = 40;
static const Double_t sqrtofficialqtmin   = 0.5;
static const Double_t sqrtofficialqtmax   = 1000.;
static Double_t sqrtofficialqtbins[nsqrtofficialqtbins+1];
// official etaQ
static const Int_t    netaQbins = 50;
static const Double_t etaQmin   = -5.;
static const Double_t etaQmax   = +5.;
// official eta
static const Int_t    nEtabins = 60;
static const Double_t Etamin   = -3.;
static const Double_t Etamax   = +3.;
// official phi
static const Int_t    nPhibins = 32;
static const Double_t Phimin   = -3.2;
static const Double_t Phimax   = +3.2;
// official isolation full
static const Int_t    nisofullbins = 20;
static const Double_t isofullmin   = 0.;
static const Double_t isofullmax   = 1.;
// official isolation low
static const Int_t    nisobins = 20;
static const Double_t isomin   = 0.;
static const Double_t isomax   = 0.4;
// official MET
static const Int_t    nmetbins = 100;
static const Double_t metmin   = 0.;
static const Double_t metmax   = 1000.;

static const Int_t    nlogptbins = 50;
static const Double_t logptmin   = 25.;
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

const int      imasslogicnbins = 10;
const Double_t imasslogicbins[imasslogicnbins+1] =
{
	70.,110.,130.,150.,170.,200.,240.,300.,400.,800.,3000.
};

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

