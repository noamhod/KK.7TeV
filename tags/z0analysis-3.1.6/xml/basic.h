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
#include <TPaveText.h>
#include <TThread.h>
#include <TList.h>

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
#include <ctime>
#include <time.h>
#include <pthread.h>

#ifndef __CINT__
#include <boost/lexical_cast.hpp>
#else
// If needed forward declare the boost entity as 'simply' as possible
template <typename T> class boost_ptr;
#endif
//#include <boost/lexical_cast.hpp>

using namespace std;

typedef multimap<int, int>      TMapii;
typedef multimap<int, string>   TMapis;
typedef map<double, double>     TMapdd;
typedef vector<TLorentzVector*> TVectorP2VL;
typedef map<string, TH1D*>      TMapSP2TH1D;
typedef map<string, TH2D*>      TMapSP2TH2D;
typedef map<string, TCanvas*>   TMapSP2TCNV;
typedef map<string, double>     TMapsd;
typedef map<string, int>        TMapsi;
typedef map<string, bool>       TMapsb;
typedef map<double, string>     TMapds;
typedef map<double, int>        TMapdi;
typedef map<string, vector<double> >  TMapsvd;
typedef map<string, vector<double>* > TMapsP2vd;
typedef map<string, string> TMapss;
typedef map<string, vector<string> > TMapsvs;
typedef map<string, vector<string>* > TMapsP2vs;
typedef map<int, vector<string>* >    TMapiP2vs;
typedef multimap<float, float > TMultimapff;
typedef vector<TCanvas*> TVecCanvas;

//////////////////////////////////////////////////////
typedef map<int, const char*> TMapiP2cc;
#include <Riostream.h>
#include <TDOMParser.h>
#include <TXMLNode.h>
#include <TXMLAttr.h>
///////////////////////////////////////////////////////

#endif
