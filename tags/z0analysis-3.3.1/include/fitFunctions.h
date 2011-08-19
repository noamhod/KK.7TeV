/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

using namespace fitparameters;

#ifndef FITFUNCTIONS_H
#define FITFUNCTIONS_H


double XMIN = 60.*GeV2TeV;
double XMAX = 120.*GeV2TeV;

double XMAXBG = 75.*GeV2TeV;

double XFULLMIN = 0.*GeV2TeV;
double XFULLMAX = 200.*GeV2TeV;

double XFITMIN = XMIN;
double XFITMAX = XMAX;

double DATASCALE;
double FCNINTEGRAL;

bool custom_isnan(double var);
double scale2data(TH1D* h);
double exponential(double *x, double *par);
double DoubleGaus(double x, double mean, double sigma1, double sigma2);
double TripleGaus(double x, double mean, double sigma1, double sigma2, double sigma3);
double BreitGaus(double *x, double *par);
double BreitDoubleGaus(double *x, double *par);
double BreitTripleGaus(double *x, double *par);
double fitFunctionSB(double *x, double *par);
double fitFunctionSB2(double *x, double *par);
double fitFunctionS(double *x, double *par);
double fitFunctionS2(double *x, double *par);
double fitFunctionS3(double *x, double *par);
double fitFunctionSBscaled(double *x, double *par);

#endif

