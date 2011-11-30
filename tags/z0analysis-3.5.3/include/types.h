#ifndef TYPES_H
#define TYPES_H

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <map>
#include <string>

#include <TLorentzVector.h>
#include <TH1.h>
#include <TH2.h>
#include <TCanvas.h>
#include <TLine.h>
#include <TTree.h>
#include <TGraph.h>


class fermion
{
	public:
		fermion(string Name, unsigned int PDGid, double Mass, double Charge, double WeakI3)
		{
			this->name = Name;
			this->id = PDGid;
			this->mass = Mass;
			this->charge = Charge;
			this->I3 = WeakI3;
			if(fabs(this->charge)<1.) this->Nc = 3;
			else                      this->Nc = 1;
		}
		~fermion();

	public:
		string name;
		unsigned int id;
		unsigned int Nc;
		double mass; // MeV
		double charge; // in units of the proton's charge
		double I3;
};


typedef map<int, const char*>   TMapiP2cc;
typedef multimap<int, int>      TMapii;
typedef multimap<int, string>   TMapis;
typedef map<double, double>     TMapdd;
typedef map<double, vector<int> > TMapdvi;
typedef map<float,  vector<int> > TMapfvi;
typedef vector<TLorentzVector*> TVectorP2VL;
typedef map<string, TObject*>   TMapSP2TOBJ;
typedef map<TString, TObject*>  TMapTSP2TOBJ;
typedef map<string, TH1*>       TMapSP2TH1;
typedef map<string, vector<TH1*> > TMapSvTH1;
typedef map<string, TH2*>       TMapSP2TH2;
typedef map<string, TGraph*>    TMapSP2TGraph;
typedef map<TString, TString>   TMapTSTS;
typedef map<TString, TH1*>      TMapTSP2TH1;
typedef map<TString, TH2*>      TMapTSP2TH2;
typedef map<TString, TGraph*>   TMapTSP2TGraph;
typedef map<TString, TLine*>    TMapTSP2TLINE;
typedef map<TString, TTree*>    TMapTSP2TTREE;
typedef map<TString, double>    TMapTSd;
typedef map<TString, Color_t>   TMapTSTC;
typedef map<string, TH1D*>      TMapSP2TH1D;
typedef map<string, TH2D*>      TMapSP2TH2D;
typedef map<string, TCanvas*>   TMapSP2TCNV;
typedef map<TString, TCanvas*>  TMapTSP2TCNV;
typedef map<string, double>     TMapsd;
typedef map<string, int>        TMapsi;
typedef map<string, bool>       TMapsb;
typedef map<double, string>     TMapds;
typedef map<double, int>        TMapdi;
typedef map<TString, vector<float> >  TMapTSvf;
typedef map<string, vector<double> >  TMapsvd;
typedef map<string, vector<double>* > TMapsP2vd;
typedef map<string, vector<float>* > TMapsP2vf;
typedef map<string, string> TMapss;
typedef map<string, vector<string> > TMapsvs;
typedef map<string, vector<string>* > TMapsP2vs;
typedef map<int, vector<string>* >    TMapiP2vs;
typedef multimap<float, float > TMultimapff;
typedef vector<TCanvas*> TVecCanvas;

typedef map<unsigned int, fermion*> ui2fermion;
typedef map<string, fermion*>       s2fermion;

typedef complex<double> dcomplex;
typedef complex<int>    icomplex;

static dcomplex Im = dcomplex(0.,1.);

#endif

