/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#ifndef BASICINCLUDES_H
#define BASICINCLUDES_H

#include <TROOT.h>
#include <TSystem.h>
#include <TMatrix.h>
#include <TVector.h>
#include <TLorentzVector.h>
#include <TVector3.h>
#include <TCut.h>
#include <TChain.h>
#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TDirectory.h>
#include <TLegend.h>
#include <TMinuit.h>
#include <TApplication.h>
#include <TF1.h>
#include <TAxis.h>
#include <TLine.h>

#include <iostream>
#include <stdlib.h>
#include <stdio.h>      // for the sprintf call
#include <string>
#include <sstream>      // for the int to string operation (stringstream call)
#include <cstring>      // for the string functions
#include <math.h>
#include <cmath>
#include <complex>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

typedef map<int, int>           TMapii;
typedef map<double, double>     TMapdd;

typedef vector<TLorentzVector*> TVectorP2VL;
typedef map<string, TH1D*>      TMapSP2TH1D;

typedef map<string, double>     TMapsd;
typedef map<string, int>        TMapsi;
typedef map<string, bool>       TMapsb;
typedef map<double, string>     TMapds;

typedef map<string, vector<double>>  TMapsvd;
typedef map<string, vector<double>*> TMapsP2vd;

#define utilities_cxx
#include "utilities.C"

#define physics_cxx
#include "physics.C"

/*
#ifdef __CINT__
#pragma link C++ class vector<vector<double> >+;
#pragma link C++ class vector<vector<float> >+;
#pragma link C++ class vector<vector<int> >+;
#pragma link C++ class vector<vector<unsigned int> >+;
#else
template class std::vector<std::vector<double> >;
template class std::vector<std::vector<float> >;
template class std::vector<std::vector<int> >;
template class std::vector<std::vector<unsigned int> >;
#endif
*/


/*
#ifdef __CINT__
#pragma link C++ class std::vector<std::vector<double> >+;
#else
	template class std::vector<std::vector<double> >;
#endif

#ifdef __CINT__
#pragma link C++ class std::vector<std::vector<float> >+;
#else
	template class std::vector<std::vector<float> >;
#endif

#ifdef __CINT__
#pragma link C++ class std::vector<std::vector<int> >+;
#else
	template class std::vector<std::vector<int> >;
#endif

#ifdef __CINT__
#pragma link C++ class std::vector<std::vector<unsigned int> >+;
#else
	template class std::vector<std::vector<unsigned int> >;
#endif
*/

#define offlinePhysics_cxx
#include "offlinePhysics.C"

#define digestPhysics_cxx
#include "digestPhysics.C"

#define particleBase_cxx
#include "particleBase.C"

enum pdtEnum { // *** note that this is not a complete list of pdt's particles ***
	PDTDWN=1, PDTUP=2, PDTSTR=3, PDTCHM=4, PDTBOT=5, PDTTOP=6,
	PDTBOTPRIME=7, PDTTOPPRIME=8,
	PDTE=11, PDTNUE=12, PDTMU=13, PDTNUMU=14, PDTTAU=15, PDTNUTAU=16,
	PDTTAUPRIME=17, PDTNUTAUPRIME=18,
	PDTGLU=21, PDTGAMMA=22, PDTZ=23, PDTWPLUS=24, PDTZPRIME0=32,
	PDTFIRSTMESON=111, PDTLASTMESON=555,
	PDTFIRSTBARYON=1103, PDTLASTBARYON=5554
};

#endif

