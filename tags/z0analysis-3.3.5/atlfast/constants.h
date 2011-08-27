//#include "basics.h"

#ifndef CONSTANTS_H
#define CONSTANTS_H

static const double luminosity = 5.; // 1/fb

static const double mumass = 0.105658367; // in GeV

static const double minMassBin = 120;  // for the asymmetry fit
static const double maxMassBin = 1500; // for the asymmetry fit
static const int    nMassBins  = 10;   // for the asymmetry fit
static const int    niMassBins = 200;  // for the imass histos

static const double minCosTheta = -1.;  // for the acceptance binning
static const double maxCosTheta = +1.;  // for the acceptance binning
static const int    nCosThetaBins = 15; // for the acceptance binning

enum models
{
	ZPd3pd=-2,
	Z0d3pd=-1,
	Z0,ZP,KK
};

static const float MeV2TeV = 1.e-6;
static const float MeV2GeV = 1.e-3;
static const float GeV2TeV = 1.e-3;
static const float GeV2MeV = 1.e+3;
static const float TeV2MeV = 1.e+6;
static const float TeV2GeV = 1.e+3;

static const double mb2fb = 1.e12;
static const double nb2mb = 1.e-6;
static const double nb2fb = 1.e6;
static const double mb2nb = 1.e6;

static const Color_t cData    = kBlack;
static const Color_t cGammaZ  = kAzure-9;
static const Color_t cTTBar   = kRed+1;
static const Color_t cDiboson = kOrange+7;
static const Color_t cQCD     = kYellow-9;
static const Color_t cWJets   = kGreen-3;

static const Color_t col0 = kBlack;
static const Color_t col1 = kAzure-9;
static const Color_t col2 = kRed+1;
static const Color_t col3 = kOrange+7;
static const Color_t col4 = kYellow-9;
static const Color_t col5 = kGreen-3;

#endif
