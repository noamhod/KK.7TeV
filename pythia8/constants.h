#include "basics.h"

#ifndef CONSTANTS_H
#define CONSTANTS_H

const double luminosity = 5.; // 1/fb

const double minMassBin = 120;  // for the asymmetry fit
const double maxMassBin = 1620; // for the asymmetry fit
const int nMassBins = 12;        // for the asymmetry fit

static double   minCosTheta = -1.;  // for the acceptance binning
static double   maxCosTheta = +1.;  // for the acceptance binning
const  int      nCosThetaBins = 25; // for the acceptance binning

enum models
{
	Z0d3pd=-1,
	Z0,ZP,KK
};

float MeV2TeV = 1.e-6;
float MeV2GeV = 1.e-3;
float GeV2TeV = 1.e-3;
float GeV2MeV = 1.e+3;
float TeV2MeV = 1.e+6;
float TeV2GeV = 1.e+3;

static Color_t cData    = kBlack;
static Color_t cGammaZ  = kAzure-9;
static Color_t cTTBar   = kRed+1;
static Color_t cDiboson = kOrange+7;
static Color_t cQCD     = kYellow-9;
static Color_t cWJets   = kGreen-3;

static Color_t col0 = kBlack;
static Color_t col1 = kAzure-9;
static Color_t col2 = kRed+1;
static Color_t col3 = kOrange+7;
static Color_t col4 = kYellow-9;
static Color_t col5 = kGreen-3;

#endif
