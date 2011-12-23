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
#include <TRandom.h>
#include <TGraphAsymmErrors.h>

using namespace std;

// Declare pointer to data as global (not elegant but TMinuit needs this).
vector<vector<double> *> VVCOSTH;
vector<TH1D*> VHIST_Z0;
vector<TH1D*> VHIST_KK;
vector<TH1D*> VHIST_ZP;
vector<TVirtualPad*> VPAD;
TCanvas* CNV = new TCanvas("C", "C", 1200, 800);
unsigned int CURRENTBIN;
bool ISZ0;
bool ISZP;
bool ISKK;
string REFNAME = "CosThetaCS";
//string REFNAME = "CosThetaHE";
Float_t IMASS;
Float_t COSTH;
vector<double>* CHARGE;
vector<int>*    ID;
vector<double>* PX;
vector<double>* PY;
vector<double>* PZ;
vector<double>* E;
vector<double>* PT;
vector<double>* PHI;
vector<double>* THETA;
vector<double>* ETA;
TLorentzVector* pa = new TLorentzVector();
TLorentzVector* pb = new TLorentzVector();

vector<double>* PXsmr = new vector<double>;
vector<double>* PYsmr = new vector<double>;
vector<double>* PZsmr = new vector<double>;
vector<double>* Esmr  = new vector<double>;
vector<double>* PTsmr = new vector<double>;


vector<bool>* muQAflag = new vector<bool>;

TLorentzVector m_pTmp;

////////////////////////////////////////////////////////////////////////////
// definitions /////////////////////////////////////////////////////////////
const double GeV2TeV  = 1.e-3;
const double MeV2TeV  = 1.e-6;
const double muonMass = 0.105658367; // GeV

const double sigma_KK   = 7.68E-09; // mb
const double nevents_KK = 1500000.;
const double sigma_ZP   = 7.88E-09; // mb
const double nevents_ZP = 1500000.;
const double sigma_Z0   = 7.96E-09; // mb
const double nevents_Z0 = 1500000.;

const double minAsymmetry  = -1.; //-0.6;
const double maxAsymmetry  = +1.; //+0.6;

const double ifb2imb = 1.e+12;
const double L       = 5.; // 1/fb

const bool DOSELECTION      = true;
const bool DOSMEAR          = true;
const bool FITWITHALLEVENTS = false; // false if only fit to N events for a given luminosity (see L above)

const int minEntriesDATA = 10;
const int minEntriesMC   = 10;
const string refframe    = REFNAME;
const bool doLogM        = true;
const bool doLogx        = true;

const double AVERAGE      = 0.; // for gaussian smearing
const double SIGMA        = 1.; // for gaussian smearing
const double RESOLUTION   = 0.12; // resolution for smearing pT~1TeV
const double PTTRACKSCALE = 1.e+3; // in GeV/c
////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////
double error_poisson_up(double data)
{
	double y1 = data + 1.0;
	double d = 1.0 - 1.0/(9.0*y1) + 1.0/(3*TMath::Sqrt(y1));
	return y1*d*d*d-data;
}

double error_poisson_down(double data)
{
	double y = data;
	if (y == 0.0) return 0.0;
	double d = 1.0 - 1.0/(9.0*y) - 1.0/(3.0*TMath::Sqrt(y));
	return data-y*d*d*d;
}

TGraphAsymmErrors* GetPoissonizedGraph(TH1D* histo, bool isXerr)
{
	TGraphAsymmErrors* graph = new TGraphAsymmErrors();
	
	int j=0;
	for (int i=1;i<=histo->GetNbinsX();++i)
	{
		if (histo->GetBinContent(i)!=0)
		{ 
			graph->SetPoint(j,histo->GetBinCenter(i),histo->GetBinContent(i));
			graph->SetPointError(j,
								 (isXerr) ? histo->GetBinWidth(i)/2. : 0.,
								 (isXerr) ? histo->GetBinWidth(i)/2. : 0.,
								 error_poisson_down(histo->GetBinContent(i)),
								 error_poisson_up(histo->GetBinContent(i))
								 );
			++j;
		}
	}
	return graph;
}
///////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
// smearing
TRandom* GAUSSGENERATOR = new TRandom();

inline double gaussRand()
{
	return GAUSSGENERATOR->Gaus(AVERAGE, SIGMA); 
}
inline double smear_pT(double pT)
{
	return 1./(1./pT + gaussRand()*RESOLUTION/PTTRACKSCALE);
}
inline double smear_px(double pTsmeared, double phi)
{
	return pTsmeared*cos(phi);
}
inline double smear_py(double pTsmeared, double phi)
{
	return pTsmeared*sin(phi);
}
inline double smear_pz(double pTsmeared, double theta)
{
	return pTsmeared/tan(theta);
}
inline double smear_e(double pTsmeared,  double theta)
{
	return pTsmeared/sin(theta);
}
inline void compare2true(double px0, double py0, double pz0, double e0,
						 double pxS, double pyS, double pzS, double eS
						)
{
	cout << "(pxS[" << pxS << "]/px0[" << px0 << "] - 1)% = " << (pxS/px0 - 1.)*100 << endl;
	cout << "(pyS[" << pyS << "]/py0[" << py0 << "] - 1)% = " << (pyS/py0 - 1.)*100 << endl;
	cout << "(pzS[" << pzS << "]/pz0[" << pz0 << "] - 1)% = " << (pzS/pz0 - 1.)*100 << endl;
	cout << "(eS[" <<  eS  << "]/e0["  << e0  << "] - 1)% = " << (eS/e0 - 1.)*100 << "\n" << endl;
}
//////////////////////////////////////////////////////////////////////////////////

void Scale(TH1D* h, double d)
{ 
	/// scale including over/underflow
	for(int i=0 ; i<=h->GetNbinsX()+1 ; i++)
	{ 
		h->SetBinContent(i,h->GetBinContent(i)*d);
	}
}

void ScaleWerrors(TH1D* h, double d)
{ 
	/// scale including over/underflow
	for ( int i=0 ; i<=h->GetNbinsX()+1 ; i++ )
	{ 
		h->SetBinContent(i,h->GetBinContent(i)*d);
		h->SetBinError(i,h->GetBinError(i)*d);
	}
}


///////////////////////////////////////////////////////////////////////////////////////
// Kinematics /////////////////////////////////////////////////////////////////////////
inline float imass( TLorentzVector* pa, TLorentzVector* pb )
{
	m_pTmp = (*pa)+(*pb);
	return m_pTmp.M();
}

inline float QT( TLorentzVector* pa, TLorentzVector* pb )
{
	m_pTmp = (*pa)+(*pb);
	return m_pTmp.Perp();
}

inline float ySystem( TLorentzVector* pa, TLorentzVector* pb )
{
	m_pTmp = (*pa)+(*pb);
	return m_pTmp.Rapidity();
}

inline float cosThetaBoost( TLorentzVector* pa, float ca, TLorentzVector* pb, float cb )
{
	// http://xrootd.slac.stanford.edu/BFROOT/www/doc/workbook_backup_010108/analysis/analysis.html
	// A useful quantity in many analyses is the helicity angle.
	// In the reaction Y -> X -> a + b, the helicity angle of 
	// particle a is the angle measured in the rest frame of the
	//decaying parent particle, X, between the direction of the
	// decay daughter a and the direction of the grandparent particle Y.

	m_pTmp = (*pa)+(*pb); // this is the mumu system (Z) 4vector
	TVector3 ZboostVector = m_pTmp.BoostVector(); // this is the 3vector of the Z
	TLorentzVector p; // this is the muon 4vector
	
	if(ca<0)      p.SetPxPyPzE(pa->Px(),pa->Py(),pa->Pz(),pa->E());
	else if(cb<0) p.SetPxPyPzE(pb->Px(),pb->Py(),pb->Pz(),pb->E());
	p.Boost( -ZboostVector ); // boost p to the dimuon CM (rest) frame
	float cosThetaB = p.Vect()*m_pTmp.Vect()/(p.P()*m_pTmp.P());
	//if (ySystem(pa,pb) < 0) cosThetaB *= -1.; // reclassify ???
	return cosThetaB;
}

inline float cosThetaCollinsSoper( TLorentzVector* pa, float ca, TLorentzVector* pb, float cb )
{
	// this will work only for leptons e, mu and tau
	// by default it is assumed that pa is the lepton
	// if instead pb is the lepton, then the result is
	// reclassified by a (-) sign - see line 4.
	float mass2 = imass(pa,pb)*imass(pa,pb);
	float QT2 = QT(pa,pb)*QT(pa,pb);
	//float cosThetaCS = 2.*( pa->Plus()*pb->Minus() - pa->Minus()*pb->Plus() ) / sqrt( mass2 * (mass2 + QT2) );
	float cosThetaCS = 2.*( pa->Pz()*pb->E() - pa->E()*pb->Pz() ) / sqrt( mass2 * (mass2 + QT2) );
	if (ca>0. && cb<0.)     cosThetaCS *= -1.; // if pb is the lepton
	if (ySystem(pa,pb) < 0) cosThetaCS *= -1.; // reclassify
	return cosThetaCS;
}
///////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////
// The pdf to be fitted ///////////////////////////////////////////////////////////////
// First argument needs to be a pointer in order to plot with the TF1 class.
double cosThetaPdf(double* xPtr, double par[])
{
	double x   = *xPtr;
	double pdf = 1.;
	double A4  = par[0];

	if (fabs(x)<=1.)
	{
		// see: http://arxiv.org/PS_cache/arxiv/pdf/1004/1004.1649v1.pdf
		// pdf_CollinsSoper = (1/N)*dN/dcosThetaCS = (3/8)*((1+0.5*A0) + A4*cosThetaCS + (1-3/2*A0)*cosTetaCS^2)
		// pdf_Helicity     = (1/N)*dN/dcosThetaHE = (3/8)*(1+cosTetaHE^2 + Afb*cosThetaHE)
		// if A0=~0 then pdf_CollinsSoper = pdf_Helicity (in the Z/Z'/Z* cases, it is approximately true)
		pdf  = (3./8.)*(1. + x*x + A4*x);
		if (pdf > 0) { return pdf; }
		else { cout << "warning:  pdf<=0, pdf=" << pdf << endl; return 1e-30; }
	}
	else { cout << "warning:  x<-1 || x>+1, x=" << x << endl; return 1e-30; }
}

// fcn passes back f = - 2*ln(L), the function to be minimized.
void fcn(int& npar, double* deriv, double& f, double par[], int flag)
{
	//vector<double> xVec = *VCOSTH; // VCOSTH is global
	vector<double> xVec = *VVCOSTH[CURRENTBIN]; // VVCOSTH is global
	int n = xVec.size();
	double lnL = 0.;
	double x   = 0.;
	double pdf = 0.;
	for (int i=0; i<n; i++){
		x = xVec[i];
		pdf = cosThetaPdf(&x, par);
		if (pdf > 0.) {
			lnL += log(pdf); // need positive f
		}
		else { cout << "WARNING -- pdf is negative!!!" << endl; }
	}
	f = -2.0 * lnL; // factor of -2 so minuit gets the errors right
}
///////////////////////////////////////////////////////////////////////////////////////

inline void smear(bool print)
{
	PXsmr->clear();
	PYsmr->clear();
	PZsmr->clear();
	Esmr->clear();
	PTsmr->clear();
	double pTSmeared;
	
	for(int i=0 ; i<(int)PT->size() ; i++)
	{
		
		pTSmeared = smear_pT(PT->at(i));
		
		PTsmr->push_back(pTSmeared);
		PXsmr->push_back(smear_px(pTSmeared, PHI->at(i)));
		PYsmr->push_back(smear_py(pTSmeared, PHI->at(i)));
		PZsmr->push_back(smear_pz(pTSmeared, THETA->at(i)));
		Esmr->push_back(smear_e(pTSmeared,   THETA->at(i)));
		
		if(pTSmeared<0)
		{
			CHARGE->at(i)*=-1.;
			ID->at(i)*=-1.;
			cout << "smeared pT=" << pTSmeared  << " ==> charge flip !" << endl;
		}

		if(print)
		{
			compare2true(
						 PX->at(i),PY->at(i),PZ->at(i),E->at(i),
						 PXsmr->at(i),PYsmr->at(i),PZsmr->at(i),Esmr->at(i)
						);
		}
	}
}

inline bool selection(TLorentzVector* pa, TLorentzVector* pb)
{
	// pa and pb are in TeV
	if(imass(pa,pb)<0.06)                          return false;
	if(pa->Pt()<0.025      || pb->Pt()<0.025)      return false;
	if(fabs(pa->Eta())>2.4 || fabs(pb->Eta())>2.4) return false;
	return true;
}

inline void fill(TTree* t, Int_t Nmax, TH1D* h, TH1D* hMass)
{
	for(int v=0 ; v<(int)VVCOSTH.size() ; v++) VVCOSTH[v]->clear();
	if (t==0) return;
	
	TAxis* xaxis = h->GetXaxis();
	
	Int_t N = (Nmax > t->GetEntries()) ? t->GetEntries() : Nmax;
	
	for (Long64_t l64t_jentry=0 ; l64t_jentry<t->GetEntries() ; l64t_jentry++)
	{
		t->GetEntry(l64t_jentry);
		
		/*
		int bin = (int)xaxis->FindBin((Double_t)IMASS*GeV2TeV);
		if(bin<=0 || bin>(int)VVCOSTH.size()) continue;
		*/
		
		if(CHARGE->at(0)*CHARGE->at(1)>=0) continue;
		if(DOSMEAR)
		{
			//////////////////
			// smear by pT ///
			smear(false); ////
			//////////////////
			pa->SetPxPyPzE(PXsmr->at(0)*GeV2TeV,PYsmr->at(0)*GeV2TeV,PZsmr->at(0)*GeV2TeV,Esmr->at(0)*GeV2TeV);
			pb->SetPxPyPzE(PXsmr->at(1)*GeV2TeV,PYsmr->at(1)*GeV2TeV,PZsmr->at(1)*GeV2TeV,Esmr->at(1)*GeV2TeV);
		}
		else
		{
			pa->SetPxPyPzE(PX->at(0)*GeV2TeV,PY->at(0)*GeV2TeV,PZ->at(0)*GeV2TeV,E->at(0)*GeV2TeV);
			pb->SetPxPyPzE(PX->at(1)*GeV2TeV,PY->at(1)*GeV2TeV,PZ->at(1)*GeV2TeV,E->at(1)*GeV2TeV);
		}
		
		/////////////////////////////////////////////////
		// apply selection (namely acceptance cuts) /////
		if(DOSELECTION) /////////////////////////////////
		{               /////////////////////////////////
			if(!selection(pa,pb)) continue; /////////////
		} ///////////////////////////////////////////////
		/////////////////////////////////////////////////
		
		double mHat = imass(pa,pb);
		int bin = (int)xaxis->FindBin((Double_t)mHat);
		if(bin<=0 || bin>(int)VVCOSTH.size()) continue;
		if     (REFNAME=="CosThetaCS") COSTH = cosThetaCollinsSoper( pa, CHARGE->at(0), pb, CHARGE->at(1) );
		else if(REFNAME=="CosThetaHE") COSTH = cosThetaBoost( pa, CHARGE->at(0), pb, CHARGE->at(1) );
		else COSTH = 0.;
		
		
		////////////////////////////////////////////////////////////////////////////
		// fill in the vectors (for the fit) only the N events corresponding to ////
		// the desired luminosity //////////////////////////////////////////////////
		if(l64t_jentry<N) //////////////////////////////////////////////////////////
		{                 //////////////////////////////////////////////////////////
			////////////////////////////////////////////////////////////////////////
			// fill the appropriate vector with cos(theta) /////////////////////////
			VVCOSTH[bin-1]->push_back(COSTH); //////////////////////////////////////
			////////////////////////////////////////////////////////////////////////
		
			////////////////////////////////////////////////////////////////////////
			// fill the appropriate cos(theta) histogram ///////////////////////////
			if(ISZ0) VHIST_Z0[bin-1]->Fill(COSTH); /////////////////////////////////
			if(ISZP) VHIST_ZP[bin-1]->Fill(COSTH); /////////////////////////////////
			if(ISKK) VHIST_KK[bin-1]->Fill(COSTH); /////////////////////////////////
			////////////////////////////////////////////////////////////////////////
		} //////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////
		
		///////////////////////////////////////
		// fill the invariant mass histo //////
		// fill all the events that are in ////
		// the sample and afterwards, scale ///
		// the histograms to the luminosity /// 
		hMass->Fill(mHat); ////////////////////
		///////////////////////////////////////
	}
}

void minimize(double guess, double& A4, double& dA4)
{
	int npar = 1;      // the number of parameters
	TMinuit minuit(npar);
	minuit.SetFCN(fcn);

	double par[npar];        // the start values
	double stepSize[npar];   // step sizes
	double minVal[npar];     // minimum bound on parameter
	double maxVal[npar];     // maximum bound on parameter
	string parName[npar];

	par[0]      = guess; 
	stepSize[0] = 1e-4;
	minVal[0]   = -1.;
	maxVal[0]   = +1.;
	parName[0]  = "A4";

	for (int i=0; i<npar; i++)
	{
		minuit.DefineParameter(i, parName[i].c_str(), par[i], stepSize[i], minVal[i], maxVal[i]);
	}

	// Do the minimization!
	minuit.Migrad(); // Minuit's best minimization algorithm
	double outpar[npar], err[npar];
	for (int i=0; i<npar; i++)
	{
		minuit.GetParameter(i,outpar[i],err[i]);
	}
	
	/*
	TF1* func = new TF1("pdf", cosThetaPdf, -1., 1., npar);
	func->SetParameters(outpar);
	func->SetLineStyle(1);
	func->SetLineColor(1);
	func->SetLineWidth(1);
	func->GetXaxis()->SetTitle("cos#left(#theta^{*}#right)");
	func->GetYaxis()->SetTitle("pdf");
	*/
	
	A4  = 0.;
	dA4 = 0.;
	minuit.GetParameter(0,A4,dA4);
}


void merge(string sMergedFileName, string dir, vector<string>& vsNames)
{
	TList* list = new TList();
	string path;
	vector<TFile*> vf;
	
	for(int i=0 ; i<(int)vsNames.size() ; i++)
	{
		path = dir + vsNames[i];
		cout << "path=" << path << endl;
		vf.push_back( new TFile( path.c_str(),"READ") );
		list->Add( (TTree*)vf[i]->Get("tree") );
	}
	
	cout << "Merging trees...patience..." << endl;
	TFile* mergedFile = new TFile( sMergedFileName.c_str(), "RECREATE");
	TTree::MergeTrees(list);
	mergedFile->Write();
	mergedFile->Close();
	cout << "written file: " << sMergedFileName << "\n\n" << endl;
	
	// clean
	for(int i=0 ; i<(int)vf.size() ; i++) delete vf[i];
	vf.clear();
	delete list;
	delete mergedFile;
}


void execute(string isHistos = "")
{
	/*
	if(isHistos=="only_histos")
	{
		gROOT->ProcessLine(".x rootlogon_atlas.C");
		gROOT->SetStyle("ATLAS");
		gROOT->ForceStyle();
	}
	*/

	ofstream* of = new ofstream;
	of->open("test.tmp");
	
	
	// logarithmic boundries and bins of histograms
	Double_t logMmin;
	Double_t logMmax;
	Double_t logMbinwidth;
	
	const int imass_asymmetry_nbins = 10; //14;
	double    imass_asymmetry_min   = 120.*GeV2TeV;
	double    imass_asymmetry_max   = 1620.*GeV2TeV;
	const int ncol_pads   = 2; // = imass_asymmetry_nbins/nrow_pads !!!
	const int nrow_pads   = 50; // = imass_asymmetry_nbins/ncol_pads !!!
	logMmin     = log10(imass_asymmetry_min);
	logMmax     = log10(imass_asymmetry_max);
	Double_t imass_asymmetry_bins[imass_asymmetry_nbins+1];
	logMbinwidth = (Double_t)( (logMmax-logMmin)/(Double_t)imass_asymmetry_nbins );
	imass_asymmetry_bins[0] = imass_asymmetry_min;
	for(Int_t i=1 ; i<=imass_asymmetry_nbins ; i++) imass_asymmetry_bins[i] = TMath::Power( 10,(logMmin + i*logMbinwidth) );
	
	/*
	const int imass_asymmetry_nbins = 12;
	const int ncol_pads   = 2; // = imass_asymmetry_nbins/nrow_pads !!!
	const int nrow_pads   = 6; // = imass_asymmetry_nbins/ncol_pads !!!
	double imass_asymmetry_min   = 72.62*GeV2TeV;
	double imass_asymmetry_max   = 381.09*GeV2TeV;
	Double_t imass_asymmetry_bins[imass_asymmetry_nbins+1] = {72.62*GeV2TeV, 83.37*GeV2TeV, 95.73*GeV2TeV, 109.91*GeV2TeV,
									126.19*GeV2TeV, 144.89*GeV2TeV, 166.35*GeV2TeV, 191.00*GeV2TeV,
									219.30*GeV2TeV, 251.79*GeV2TeV, 289.09*GeV2TeV, 331.92*GeV2TeV, 381.09*GeV2TeV};
	//imass_asymmetry_bins = {2.00*GeV, 2.30*GeV, 2.64*GeV, 3.03*GeV, 3.48*GeV, 3.99*GeV, 4.58*GeV, 5.26*GeV, 6.04*GeV, 6.93*GeV, 7.96*GeV, 9.14*GeV, 10.50*GeV, 12.05*GeV, 13.84*GeV, 15.89*GeV, 18.24*GeV, 20.94*GeV, 24.05*GeV, 27.61*GeV, 31.70*GeV, 36.39*GeV, 41.79*GeV, 47.98*GeV, 55.08*GeV, 63.25*GeV, 72.62*GeV, 83.37*GeV, 95.73*GeV, 109.91*GeV, 126.19*GeV, 144.89*GeV, 166.35*GeV, 191.00*GeV, 219.30*GeV, 251.79*GeV, 289.09*GeV, 331.92*GeV, 381.09*GeV, 437.55*GeV, 502.38*GeV, 576.81*GeV, 662.26*GeV, 760.38*GeV, 873.03*GeV, 1002.37*GeV, 1150.88*GeV, 1321.39*GeV, 1517.16*GeV, 1741.93*GeV, 2000.00*GeV};
	*/
	
	const int imass_nbins = 100;
	double    imass_min   = 120.*GeV2TeV;
	double    imass_max   = 1620.*GeV2TeV;
	logMmin     = log10(imass_min);
	logMmax     = log10(imass_max);
	Double_t imass_bins[imass_nbins+1];
	logMbinwidth = (Double_t)( (logMmax-logMmin)/(Double_t)imass_nbins );
	imass_bins[0] = imass_min;
	for(Int_t i=1 ; i<=imass_nbins ; i++) imass_bins[i] = TMath::Power( 10,(logMmin + i*logMbinwidth) );
	
	
	//////////////////////////////////////////////////////////////////////////////////
	// fill the vector with new vector<double> pointers //////////////////////////////
	CNV->Divide(ncol_pads,nrow_pads);
	CNV->SetFillColor(0);
	stringstream strm;
	string str;
	for(int i=0 ; i<imass_asymmetry_nbins ; i++)
	{
		VVCOSTH.push_back(new vector<double>); ////////
		
		strm.clear();
		str.clear();
		strm << imass_asymmetry_bins[i]+(imass_asymmetry_bins[i+1]-imass_asymmetry_bins[i])/2.;
		strm >> str;
		str = "#hat{m}_{#mu#mu} = " + str + " TeV";
		VHIST_Z0.push_back(new TH1D(("Z^{0} "+str).c_str(), ("Z^{0} "+str).c_str(), 20, -1., +1.));
		VHIST_Z0[i]->SetLineColor(kAzure-5);
		VHIST_KK.push_back(new TH1D(("Data "+str).c_str(), ("Data "+str).c_str(), 20, -1., +1.));
		VHIST_ZP.push_back(new TH1D(("Z' "+str).c_str(), ("Z' "+str).c_str(), 20, -1., +1.));
		VHIST_ZP[i]->SetLineColor(kRed);
		if(i<nrow_pads) VPAD.push_back( CNV->cd(2*i+1) );
		else            VPAD.push_back( CNV->cd(2*(i-nrow_pads)+2) );
		VPAD[i]->SetFillColor(0);
		VPAD[i]->SetTicky(1);
		VPAD[i]->SetTickx(1);
	}
	//////////////////////////////////////////////////////////////////////////////////


	string dir   = "/srv01/tau/hod/pythia8145/rootexample/";
	string hDir  = "";
	string hName = "Afb";
	string xTitle = "#hat{m}_{#mu#mu} TeV";
	string yTitle= "A_{FB}";

	string hNameFixed = hName;

	gStyle->SetOptStat(0);
	gStyle->SetFrameBorderMode(0);
	gStyle->SetCanvasBorderMode(0);
	gStyle->SetPadBorderMode(0);
	gStyle->SetPadColor(0);
	gStyle->SetCanvasColor(0);
	gStyle->SetStatColor(0);
	//gStyle->SetFillColor(0);
	gStyle->SetFrameFillColor(0);
	gStyle->SetTitleFillColor(0);
	gStyle->SetPaperSize(20,26);
	gStyle->SetPadTopMargin(0.05);
	gStyle->SetPadRightMargin(0.12);
	gStyle->SetPadBottomMargin(0.16);
	gStyle->SetPadLeftMargin(0.12);
	Int_t font=42;
	Double_t tsize=0.04;
	gStyle->SetTextFont(font);
	gStyle->SetTextSize(tsize);
	gStyle->SetLabelFont(font,"x");
	gStyle->SetTitleFont(font,"x");
	gStyle->SetLabelFont(font,"y");
	gStyle->SetTitleFont(font,"y");
	gStyle->SetLabelFont(font,"z");
	gStyle->SetTitleFont(font,"z");
	gStyle->SetLabelSize(tsize,"x");
	gStyle->SetTitleSize(tsize,"x");
	gStyle->SetLabelSize(tsize,"y");
	gStyle->SetTitleSize(tsize,"y");
	gStyle->SetLabelSize(tsize,"z");
	gStyle->SetTitleSize(tsize,"z");
	gStyle->SetStatBorderSize(0);
	gStyle->SetStatColor(0);
	gStyle->SetStatX(0);
	gStyle->SetStatY(0);
	gStyle->SetStatFont(42);
	gStyle->SetStatFontSize(0);
	gStyle->SetOptStat(0);
	gStyle->SetStatW(0);
	gStyle->SetStatH(0);
	
	
	TLegend* leg_mHat = new TLegend(0.1557789,0.1818182,0.3806533,0.458042,NULL,"brNDC");
	leg_mHat->SetFillColor(kWhite);
	
	TLegend* leg_histos = new TLegend(0.85, 0.15, 0.97, 0.45,NULL,"brNDC");
	leg_histos->SetFillColor(kWhite);
	
	strm.clear();
	str.clear();
	strm << L;
	strm >> str;
	string lumilabel = "#intLdt~" + str + " fb^{-1}";
	TPaveText* pvtxt_lumi = new TPaveText(0.1620603,0.458042,0.3140704,0.5716783,"brNDC");
	pvtxt_lumi->SetFillColor(kWhite);
	TText* txt  = pvtxt_lumi->AddText( lumilabel.c_str() );
	
	TPaveText* pvtxt_smear = new TPaveText(0.4824415,0.1818182,0.6714047,0.3199482,"brNDC");
	pvtxt_smear->SetFillColor(0);
	pvtxt_smear->SetTextFont(42);
	txt = pvtxt_smear->AddText("#splitline{smear muon p_{T} by:}{#frac{#Delta p_{T}}{p_{T}} #approx #frac{12%}{1 TeV} #times p_{T}}");
	pvtxt_smear->Draw();
	
	TPaveText* pvtxt_atlfast = new TPaveText(0.2537688,0.8076923,0.3932161,0.9090909,"brNDC");
	pvtxt_atlfast->SetFillColor(0);
	pvtxt_atlfast->SetTextFont(42);
	txt = pvtxt_atlfast->AddText("#bf{#it{#scale[1.2]{P}#scale[1.0]{YTHIA8}}}");
	
	
	string cName = "cnv_" + hNameFixed;
	TCanvas* cnv = new TCanvas(cName.c_str(), cName.c_str(), 0,0,1200,800);
	
	TPad *pad_mHat = new TPad("pad_mHat","",0,0,1,1);
	pad_mHat->SetFillColor(kWhite);
	pad_mHat->SetTicky(0);
	pad_mHat->SetLogy();
	if(doLogx) pad_mHat->SetLogx();

	TPad *pad_Afb  = new TPad("pad_Afb", "",0,0,1,1);
	//pad_Afb->SetGridy();
	pad_Afb->SetTicky(0);
	pad_Afb->SetTickx(1);
	pad_Afb->SetFillStyle(0);
	pad_Afb->SetFrameFillStyle(4000); //will be transparent
	pad_Afb->SetFrameFillColor(0);
	if(doLogx) pad_Afb->SetLogx();
	
	string path = "";
	string sProc = "";
	string channel = "";
	
	
	
	///////////////////////////////////////////////
	// Z0 /////////////////////////////////////////
	TH1D* hMZ0;
	if(doLogM) hMZ0  = new TH1D("mHat_Z0","mHat_Z0", imass_nbins, imass_bins );
	else       hMZ0  = new TH1D("mHat_Z0","mHat_Z0", imass_nbins, imass_min, imass_max );
	hMZ0->SetTitle("");
	hMZ0->SetYTitle("Events");
	hMZ0->SetLineColor(kAzure-5);
	hMZ0->SetLineWidth(1);
	hMZ0->SetLineStyle(2);
	leg_mHat->AddEntry( hMZ0, "#gamma/Z^{0}: Events", "l");
	
	channel = "#gamma/Z^{0}: A_{FB} fit";
	TH1D* hAfbZ0;
	if(doLogM) hAfbZ0 = new TH1D("Afb_Z0","Afb_Z0", imass_asymmetry_nbins, imass_asymmetry_bins );
	else       hAfbZ0 = new TH1D("Afb_Z0","Afb_Z0", imass_asymmetry_nbins, imass_asymmetry_min, imass_asymmetry_max );
	hAfbZ0->SetLineColor(kAzure-5);
	hAfbZ0->SetFillColor(kAzure-5);
	hAfbZ0->SetFillStyle(3003);
	hAfbZ0->SetLineWidth(1);
	hAfbZ0->SetMarkerSize(0);
	hAfbZ0->SetMarkerColor(0);
	hAfbZ0->SetTitle("");
	hAfbZ0->SetXTitle( xTitle.c_str() );
	hAfbZ0->SetYTitle( yTitle.c_str() );
	leg_mHat->AddEntry( hAfbZ0, channel.c_str(), "f");
	
	
	///////////////////////////////////////////////
	// Z' /////////////////////////////////////////
	TH1D* hMZP;
	if(doLogM) hMZP  = new TH1D("mHat_ZP","mHat_ZP", imass_nbins, imass_bins );
	else       hMZP  = new TH1D("mHat_ZP","mHat_ZP", imass_nbins, imass_min, imass_max );
	hMZP->SetTitle("");
	hMZP->SetYTitle("Events");
	hMZP->SetLineColor(kRed);
	hMZP->SetLineWidth(1);
	hMZP->SetLineStyle(3);
	leg_mHat->AddEntry( hMZP, "1 TeV Z'_{SSM}: Events", "l");
	
	channel = "1 TeV Z'_{SSM}: A_{FB} fit";
	TH1D* hAfbZP;
	if(doLogM) hAfbZP = new TH1D("Afb_ZP","Afb_ZP", imass_asymmetry_nbins, imass_asymmetry_bins );
	else       hAfbZP = new TH1D("Afb_ZP","Afb_ZP", imass_asymmetry_nbins, imass_asymmetry_min, imass_asymmetry_max );
	hAfbZP->SetLineColor(kRed);
	hAfbZP->SetFillColor(kRed);
	hAfbZP->SetFillStyle(3017);
	hAfbZP->SetLineWidth(1);
	hAfbZP->SetMarkerSize(0);
	hAfbZP->SetMarkerColor(0);
	hAfbZP->SetTitle("");
	hAfbZP->SetXTitle( xTitle.c_str() );
	hAfbZP->SetYTitle( yTitle.c_str() );
	leg_mHat->AddEntry( hAfbZP, channel.c_str(), "f");
	
	
	///////////////////////////////////////////////
	// KK /////////////////////////////////////////
	TH1D* hMKK;
	if(doLogM) hMKK  = new TH1D("mHat_KK","mHat_KK", imass_nbins, imass_bins );
	else       hMKK  = new TH1D("mHat_KK","mHat_KK", imass_nbins, imass_min, imass_max );
	hMKK->SetTitle("");
	hMKK->SetYTitle("Events");
	hMKK->SetLineColor(kBlack);
	hMKK->SetLineWidth(1);
	hMKK->SetLineStyle(1);
	leg_mHat->AddEntry( hMKK, "1 TeV #gamma_{KK}/Z_{KK}: Events", "l");
	
	channel = "1 TeV #gamma_{KK}/Z_{KK}: A_{FB} fit";
	TH1D* hAfbKK;
	if(doLogM) hAfbKK = new TH1D("Afb_KK","Afb_KK", imass_asymmetry_nbins, imass_asymmetry_bins );
	else       hAfbKK = new TH1D("Afb_KK","Afb_KK", imass_asymmetry_nbins, imass_asymmetry_min, imass_asymmetry_max );
	hAfbKK->SetLineColor(kBlack);
	hAfbKK->SetFillColor(kBlack);
	hAfbKK->SetFillStyle(3018);
	hAfbKK->SetLineWidth(1);
	hAfbKK->SetMarkerSize(0);
	hAfbKK->SetMarkerColor(0);
	hAfbKK->SetTitle("");
	hAfbKK->SetXTitle( xTitle.c_str() );
	hAfbKK->SetYTitle( yTitle.c_str() );
	leg_mHat->AddEntry( hAfbKK, channel.c_str(), "f");
	
	Int_t maxEvents = 0;
	Int_t lumEvents = 0;
	string sMergedFileName; 
	vector<string> vsNames;
	TAxis *xaxis = hAfbZ0->GetXaxis();
	double a4  = 0.;
	double da4 = 0.;
	double afb  = 0.;
	double dafb = 0.;
	double guess = -0.1;

	ISZ0 = true;
	ISZP = false;
	ISKK = false;
	vsNames.clear();
	sMergedFileName = "Z0.merged.root";
	vsNames.push_back("bu/Z0.M1000.5e5.root");
	vsNames.push_back("bu/Z0.M1000.1e6.root");
	merge(sMergedFileName, dir, vsNames);
	//sMergedFileName = dir+"bu/Z0.lowMass.M1000.root";
	TFile* fZ0 = new TFile(sMergedFileName.c_str(), "READ");
	TTree* tree_Z0 = (TTree*)fZ0->Get("tree");
	tree_Z0->SetBranchAddress( "mHat",   &IMASS );
	tree_Z0->SetBranchAddress( "cosThetaCS", &COSTH );
	tree_Z0->SetBranchAddress( "charge", &CHARGE );
	tree_Z0->SetBranchAddress( "id", &ID );
	tree_Z0->SetBranchAddress( "px", &PX );
	tree_Z0->SetBranchAddress( "py", &PY );
	tree_Z0->SetBranchAddress( "pz", &PZ );
	tree_Z0->SetBranchAddress( "E", &E );
	tree_Z0->SetBranchAddress( "pT", &PT );
	tree_Z0->SetBranchAddress( "phi", &PHI );
	tree_Z0->SetBranchAddress( "theta", &THETA );
	tree_Z0->SetBranchAddress( "eta", &ETA );
	a4   = 0.;
	da4  = 0.;
	afb  = 0.;
	dafb = 0.;
	guess = -0.1;
	ISZ0 = false;
	ISZP = true;
	ISKK = false;
	lumEvents = (Int_t)(L*ifb2imb*sigma_Z0);
	maxEvents = (FITWITHALLEVENTS) ? tree_Z0->GetEntries() : lumEvents;
	cout << "Using " << maxEvents << "/" << tree_Z0->GetEntries() << " events" << endl;
	fill(tree_Z0, maxEvents, hAfbZ0, hMZ0); // the VVCOSTH vectors are full
	for(Int_t b=1 ; b<=hAfbZ0->GetNbinsX() ; b++)
	{
		// norm to bin width
		//hMZ0->SetBinContent(b, hMZ0->GetBinContent(b)/hMZ0->GetBinWidth(b));
		CURRENTBIN = (unsigned int)(b-1);
		//if((int)VVCOSTH[CURRENTBIN]->size()<minEntriesDATA) continue;
		minimize(guess, a4, da4);
		afb = (3./8.)*a4;
		dafb = (3./8.)*da4;
		guess = a4;
		hAfbZ0->SetBinContent(b,afb);
		hAfbZ0->SetBinError(b,dafb);
		cout << "mHat["<< b << "/" << hAfbZ0->GetNbinsX() << "]=" << xaxis->GetBinCenter(b) << ", Afb=" << afb << " +- " << dafb << "\n" << endl;
		(*of) << "Z0[currentbin=" << CURRENTBIN << "][bin=" << b << "]: " << VVCOSTH[CURRENTBIN]->size() << ", from histo: " << hMZ0->GetBinContent(b) << endl;
	}
	(*of) << endl;
	
	
	vsNames.clear();
	sMergedFileName = "ZP.merged.root";
	vsNames.push_back("bu/ZP.M1000.5e5.root");
	vsNames.push_back("bu/ZP.M1000.1e6.root");
	merge(sMergedFileName, dir, vsNames);
	//sMergedFileName = dir+"bu/ZP.lowMass.M1000.root";
	TFile* fZP = new TFile(sMergedFileName.c_str(), "READ");
	TTree* tree_ZP = (TTree*)fZP->Get("tree");
	tree_ZP->SetBranchAddress( "mHat",   &IMASS );
	tree_ZP->SetBranchAddress( "cosThetaCS", &COSTH );
	tree_ZP->SetBranchAddress( "charge", &CHARGE );
	tree_ZP->SetBranchAddress( "id", &ID );
	tree_ZP->SetBranchAddress( "px", &PX );
	tree_ZP->SetBranchAddress( "py", &PY );
	tree_ZP->SetBranchAddress( "pz", &PZ );
	tree_ZP->SetBranchAddress( "E", &E );
	tree_ZP->SetBranchAddress( "pT", &PT );
	tree_ZP->SetBranchAddress( "phi", &PHI );
	tree_ZP->SetBranchAddress( "theta", &THETA );
	tree_ZP->SetBranchAddress( "eta", &ETA );
	a4   = 0.;
	da4  = 0.;
	afb  = 0.;
	dafb = 0.;
	guess = -0.1;
	ISZ0 = false;
	ISZP = false;
	ISKK = true;
	lumEvents = (Int_t)(L*ifb2imb*sigma_ZP);
	maxEvents = (FITWITHALLEVENTS) ? tree_ZP->GetEntries() : lumEvents;
	cout << "Using " << maxEvents << "/" << tree_ZP->GetEntries() << " events" << endl;
	fill(tree_ZP, maxEvents, hAfbZP, hMZP); // the VVCOSTH vectors are full
	for(Int_t b=1 ; b<=hAfbZP->GetNbinsX() ; b++)
	{
		// norm to bin width
		//hMZ0->SetBinContent(b, hMZ0->GetBinContent(b)/hMZ0->GetBinWidth(b));
		CURRENTBIN = (unsigned int)(b-1);
		//if((int)VVCOSTH[CURRENTBIN]->size()<minEntriesDATA) continue;
		minimize(guess, a4, da4);
		afb = (3./8.)*a4;
		dafb = (3./8.)*da4;
		guess = a4;
		hAfbZP->SetBinContent(b,afb);
		hAfbZP->SetBinError(b,dafb);
		cout << "mHat["<< b << "/" << hAfbZP->GetNbinsX() << "]=" << xaxis->GetBinCenter(b) << ", Afb=" << afb << " +- " << dafb << "\n" << endl;
		(*of) << "ZP[currentbin=" << CURRENTBIN << "][bin=" << b << "]: " << VVCOSTH[CURRENTBIN]->size() << ", from histo: " << hMZP->GetBinContent(b) << endl;
	}
	(*of) << endl;
	
	
	
	vsNames.clear();
	sMergedFileName = "KK.merged.root";
	vsNames.push_back("bu/KK.M1000.5e5.root");
	vsNames.push_back("bu/KK.M1000.1e6.root");
	merge(sMergedFileName, dir, vsNames);
	//sMergedFileName = dir+"bu/KK.lowMass.M1000.root";
	TFile* fKK = new TFile(sMergedFileName.c_str(), "READ");
	TTree* tree_KK = (TTree*)fKK->Get("tree");
	tree_KK->SetBranchAddress( "mHat",   &IMASS );
	tree_KK->SetBranchAddress( "cosThetaCS", &COSTH );
	tree_KK->SetBranchAddress( "charge", &CHARGE );
	tree_KK->SetBranchAddress( "id", &ID );
	tree_KK->SetBranchAddress( "px", &PX );
	tree_KK->SetBranchAddress( "py", &PY );
	tree_KK->SetBranchAddress( "pz", &PZ );
	tree_KK->SetBranchAddress( "E", &E );
	tree_KK->SetBranchAddress( "pT", &PT );
	tree_KK->SetBranchAddress( "phi", &PHI );
	tree_KK->SetBranchAddress( "theta", &THETA );
	tree_KK->SetBranchAddress( "eta", &ETA );
	a4   = 0.;
	da4  = 0.;
	afb  = 0.;
	dafb = 0.;
	guess = -0.1;
	ISZ0 = false;
	ISZP = false;
	ISKK = true;
	lumEvents = (Int_t)(L*ifb2imb*sigma_KK);
	maxEvents = (FITWITHALLEVENTS) ? tree_KK->GetEntries() : lumEvents;
	cout << "Using " << maxEvents << "/" << tree_KK->GetEntries() << " events" << endl;
	fill(tree_KK, maxEvents, hAfbKK, hMKK); // the VVCOSTH vectors are full
	for(Int_t b=1 ; b<=hAfbKK->GetNbinsX() ; b++)
	{
		// norm to bin width
		//hMZ0->SetBinContent(b, hMZ0->GetBinContent(b)/hMZ0->GetBinWidth(b));
		CURRENTBIN = (unsigned int)(b-1);
		//if((int)VVCOSTH[CURRENTBIN]->size()<minEntriesDATA) continue;
		minimize(guess, a4, da4);
		afb = (3./8.)*a4;
		dafb = (3./8.)*da4;
		guess = a4;
		hAfbKK->SetBinContent(b,afb);
		hAfbKK->SetBinError(b,dafb);
		cout << "mHat["<< b << "/" << hAfbKK->GetNbinsX() << "]=" << xaxis->GetBinCenter(b) << ", Afb=" << afb << " +- " << dafb << "\n" << endl;
		(*of) << "KK[currentbin=" << CURRENTBIN << "][bin=" << b << "]: " << VVCOSTH[CURRENTBIN]->size() << ", from histo: " << hMKK->GetBinContent(b) << endl;
	}
	(*of) << endl;

	
	
	// scale all to lumi
	Scale(hMZ0, (L*ifb2imb)*(sigma_Z0/nevents_Z0));
	Scale(hMZP, (L*ifb2imb)*(sigma_ZP/nevents_ZP));
	Scale(hMKK, (L*ifb2imb)*(sigma_KK/nevents_KK));
	
	
	bool isXerr = false;
	TGraphAsymmErrors* gMZ0poissonErr = GetPoissonizedGraph(hMZ0, isXerr);
	gMZ0poissonErr->SetMarkerStyle(1);
	gMZ0poissonErr->SetMarkerSize(1);
	gMZ0poissonErr->SetLineColor(kBlue);
	gMZ0poissonErr->SetLineStyle(2);

	TGraphAsymmErrors* gMZPpoissonErr = GetPoissonizedGraph(hMZP, isXerr);
	gMZPpoissonErr->SetMarkerStyle(1);
	gMZPpoissonErr->SetMarkerSize(1);
	gMZPpoissonErr->SetLineColor(kRed);
	gMZPpoissonErr->SetLineStyle(3);

	TGraphAsymmErrors* gMKKpoissonErr = GetPoissonizedGraph(hMKK, isXerr);
	gMKKpoissonErr->SetMarkerStyle(1);
	gMKKpoissonErr->SetMarkerSize(1);
	gMKKpoissonErr->SetLineColor(kBlack);
	gMKKpoissonErr->SetLineStyle(1);
	
	
	pad_mHat->Draw();
	pad_mHat->cd();
	//hMKK->GetYaxis()->SetRangeUser(1,1.5*hMKK->GetMaximum());
	hMKK->SetMaximum(1.5*hMKK->GetMaximum());
	hMKK->SetMinimum((hMZ0->GetMinimum()<=0) ? 1. : 0.5*hMZ0->GetMinimum());
	hMKK->GetXaxis()->SetMoreLogLabels(); 
	hMKK->GetXaxis()->SetNoExponent();
	hMKK->Draw();
	gMKKpoissonErr->GetXaxis()->SetMoreLogLabels(); 
	gMKKpoissonErr->GetXaxis()->SetNoExponent();
	gMKKpoissonErr->Draw("SAMES");
	
	hMZ0->GetXaxis()->SetMoreLogLabels(); 
	hMZ0->GetXaxis()->SetNoExponent();
	hMZ0->Draw("SAMES");
	gMZ0poissonErr->GetXaxis()->SetMoreLogLabels(); 
	gMZ0poissonErr->GetXaxis()->SetNoExponent();
	gMZ0poissonErr->Draw("SAMES");

	hMZP->GetXaxis()->SetMoreLogLabels(); 
	hMZP->GetXaxis()->SetNoExponent(); 
	hMZP->Draw("SAMES");
	gMZPpoissonErr->GetXaxis()->SetMoreLogLabels(); 
	gMZPpoissonErr->GetXaxis()->SetNoExponent(); 
	gMZPpoissonErr->Draw("SAMES");
	

	cnv->cd();

	pad_Afb->Draw();
	pad_Afb->cd();
	hAfbKK->GetYaxis()->SetRangeUser(minAsymmetry,maxAsymmetry);
	hAfbKK->Draw("E5 Y+");
	hAfbKK->GetXaxis()->SetMoreLogLabels(); 
	hAfbKK->GetXaxis()->SetNoExponent(); 
	hAfbZ0->Draw("E5 Y+ SAMES");
	hAfbZ0->GetXaxis()->SetMoreLogLabels(); 
	hAfbZ0->GetXaxis()->SetMoreLogLabels(); 
	//hAfbZ0->Draw("e1x0SAMES");
	hAfbZP->Draw("E5 Y+ SAMES");
	hAfbZP->GetXaxis()->SetMoreLogLabels(); 
	hAfbZP->GetXaxis()->SetMoreLogLabels(); 
	pvtxt_lumi->Draw("SAMES");
	pvtxt_atlfast->Draw("SAMES");
	if(DOSMEAR) pvtxt_smear->Draw("SAMES");
	leg_mHat->Draw("SAMES");
	TLine* lUnit = new TLine(imass_asymmetry_min,0.,imass_asymmetry_max,0.);
	lUnit->SetLineColor(kBlack);
	lUnit->SetLineStyle(2);
	//lUnit->Draw("SAMES");
	//pad_Afb->RedrawAxis();
	
	cnv->cd();
	
	pad_mHat->cd();
	pad_mHat->RedrawAxis();
	pad_mHat->Update();

	cnv->Update();
	
	TString fName = (DOSMEAR) ? (TString)hNameFixed + ".smear.plot"  :  (TString)hNameFixed + ".true.plot";
	cnv->SaveAs(fName+".eps");
	cnv->SaveAs(fName+".C");
	cnv->SaveAs(fName+".root");
	cnv->SaveAs(fName+".png");
	
	of->close();
	
	/*
	CNV->Draw();
	for(int i=0 ; i<imass_asymmetry_nbins ; i++)
	{
		if(i==0)
		{
			leg_histos->AddEntry(VHIST_Z0[i], "Z#rightarrow#mu#mu");
			leg_histos->AddEntry(VHIST_Z0[i], "0.25 TeV Z' SSM#rightarrow#mu#mu");
			leg_histos->AddEntry(VHIST_Z0[i], "Data", "lep");
		}
	
		VPAD[i]->cd();
		
		Double_t NZ0     = VHIST_Z0[i]->GetEntries();
		Double_t NZprime = VHIST_ZP[i]->GetEntries();
		Double_t NDATA   = VHIST_KK[i]->GetEntries();
		
		Scale(VHIST_Z0[i], 1./NZ0);
		Scale(VHIST_ZP[i], 1./NZprime);
		ScaleWerrors(VHIST_KK[i], 1./NDATA);
		
		Double_t max = 0.;
		Double_t tmp = 0.;
		tmp = VHIST_Z0[i]->GetMaximum();
		max = (tmp>max) ? tmp : max;
		if(NZprime>=minEntriesDATA)
		{
			tmp = VHIST_ZP[i]->GetMaximum();
			max = (tmp>max) ? tmp : max;
		}
		if(NDATA>=minEntriesDATA)
		{
			tmp = VHIST_KK[i]->GetMaximum();
			max = (tmp>max) ? tmp : max;
		}
		
		
		VHIST_Z0[i]->SetMaximum(1.2*max);
		VHIST_Z0[i]->SetMinimum(0.);
		VHIST_Z0[i]->SetTitle("");
		VHIST_Z0[i]->SetXTitle("#cos#theta^{*}");
		VHIST_Z0[i]->SetYTitle("Events (normalized)");
		VHIST_Z0[i]->Draw();

		VHIST_ZP[i]->SetTitle("");
		if(NZprime>=minEntriesDATA) VHIST_ZP[i]->Draw("SAMES");
		
		VHIST_KK[i]->SetTitle("");
		if(NDATA>=minEntriesDATA) VHIST_KK[i]->Draw("e1x0SAMES");
		
		leg_histos->Draw("SAMES");
	}
	fName += ".costh";
	CNV->SaveAs(fName+".eps");
	CNV->SaveAs(fName+".C");
	CNV->SaveAs(fName+".root");
	CNV->SaveAs(fName+".png");
	*/
}
