/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#ifndef FITPARAMETERS_H
#define FITPARAMETERS_H

static double*  par;
static double*  stepSize;
static double*  minVal;
static double*  maxVal;
static string*  parName;
static double*  outpar;
static double*  err;


static double   parSignal[6];
static double   parSignalBackground[7];

static double   stepSizeSignal[6];           // step sizes
static double   stepSizeSignalBackground[7]; // step sizes

static double   minValSignal[6];             // minimum bound on parameter
static double   minValSignalBackground[7];   // minimum bound on parameter

static double   maxValSignal[6];             // maximum bound on parameter
static double   maxValSignalBackground[7];   // maximum bound on parameter

static string   parNameSignal[6];            // parameter name
static string   parNameSignalBackground[7];  // parameter name

static double   outparSignal[6];             // out paramenters
static double   outparSignalBackground[7];   // out errors

static double   errSignal[6];                // out paramenters
static double   errSignalBackground[7];      // out errors

static double ppar[7];

#endif

