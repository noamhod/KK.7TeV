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
vector<float>* CHARGE;
vector<int>* ID;
vector<float>* PX;
vector<float>* PY;
vector<float>* PZ;
vector<float>* E;
TLorentzVector* pa = new TLorentzVector();
TLorentzVector* pb = new TLorentzVector();
TLorentzVector m_pTmp;
float GeV2TeV = 1.e-3;
float MeV2TeV = 1.e-6;
float muonMass = 0.105658367; // GeV

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


// The pdf to be fitted
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


void fillVec(TTree* t, TH1D* h, Int_t b)
{
	//VCOSTH->clear();
	if (t==0) return;
	
	Double_t bmin = h->GetBinLowEdge(b);
	Double_t bwid = h->GetBinWidth(b);
	Double_t bmax = bmin+bwid;
	
	for (Long64_t l64t_jentry=0 ; l64t_jentry<t->GetEntries() ; l64t_jentry++)
	{
		t->GetEntry(l64t_jentry);
		//if( IMASS>=(Float_t)bmin  &&  IMASS<(Float_t)bmax ) VCOSTH->push_back(COSTH);
		if( IMASS>=(Float_t)bmin  &&  IMASS<(Float_t)bmax ) VVCOSTH[CURRENTBIN]->push_back(COSTH);
	}
}

void fillVec(TTree* t, TH1D* h)
{
	for(int v=0 ; v<(int)VVCOSTH.size() ; v++) VVCOSTH[v]->clear();
	if (t==0) return;
	
	TAxis* xaxis = h->GetXaxis();
	
	for (Long64_t l64t_jentry=0 ; l64t_jentry<t->GetEntries() ; l64t_jentry++)
	{
		t->GetEntry(l64t_jentry);
		
		int bin = (int)xaxis->FindBin((Double_t)IMASS*GeV2TeV);
		if(bin<0 || bin>=(int)VVCOSTH.size()) continue;
		/*
		//if(CHARGE->at(0)*CHARGE->at(1)>=0) continue;
		if(ID->at(0)*ID->at(1)>=0) continue;
		pa->SetPxPyPzE(PX->at(0)*GeV2TeV,PY->at(0)*GeV2TeV,PZ->at(0)*GeV2TeV,E->at(0)*GeV2TeV);
		pb->SetPxPyPzE(PX->at(1)*GeV2TeV,PY->at(1)*GeV2TeV,PZ->at(1)*GeV2TeV,E->at(1)*GeV2TeV);
		//if(REFNAME=="CosThetaCS") COSTH = cosThetaCollinsSoper( pa, CHARGE->at(0), pb, CHARGE->at(1) );
		float ca = (ID->at(0)>0) ? -1. : +1.;
		float cb = (ID->at(1)<0) ? -1. : +1.;
		if(REFNAME=="CosThetaCS") COSTH = cosThetaCollinsSoper( pa, ca, pb, cb );
		else COSTH = 0.;
		*/
		
		
		VVCOSTH[bin]->push_back(COSTH);
		
		if(ISZ0) VHIST_Z0[bin]->Fill(COSTH);
		if(ISZP) VHIST_ZP[bin]->Fill(COSTH);
		if(ISKK) VHIST_KK[bin]->Fill(COSTH);
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


	int minEntriesDATA = 10;
	int minEntriesMC   = 10;
	string refframe = REFNAME;
	bool doLogM = true;
	bool doLogx = true;
	
	
	// logarithmic boundries and bins of histograms
	const int imass_nbins = 12;
	double    imass_min   = 120.*GeV2TeV;
	double    imass_max   = 1400.*GeV2TeV;
	const int ncol_pads   = 2; // = imass_nbins/nrow_pads !!!
	const int nrow_pads   = 50; // = imass_nbins/ncol_pads !!!
	Double_t logMmin     = log10(imass_min);
	Double_t logMmax     = log10(imass_max);
	Double_t M_bins[imass_nbins+1];
	Double_t M_binwidth = (Double_t)( (logMmax-logMmin)/(Double_t)imass_nbins );
	M_bins[0] = imass_min;
	for(Int_t i=1 ; i<=imass_nbins ; i++) M_bins[i] = TMath::Power( 10,(logMmin + i*M_binwidth) );
	
	
	/*
	const int imass_nbins = 12;
	const int ncol_pads   = 2; // = imass_nbins/nrow_pads !!!
	const int nrow_pads   = 6; // = imass_nbins/ncol_pads !!!
	double imass_min   = 72.62*GeV2TeV;
	double imass_max   = 381.09*GeV2TeV;
	Double_t M_bins[imass_nbins+1] = {72.62*GeV2TeV, 83.37*GeV2TeV, 95.73*GeV2TeV, 109.91*GeV2TeV,
									  126.19*GeV2TeV, 144.89*GeV2TeV, 166.35*GeV2TeV, 191.00*GeV2TeV,
									  219.30*GeV2TeV, 251.79*GeV2TeV, 289.09*GeV2TeV, 331.92*GeV2TeV, 381.09*GeV2TeV};
	//M_bins = {2.00*GeV, 2.30*GeV, 2.64*GeV, 3.03*GeV, 3.48*GeV, 3.99*GeV, 4.58*GeV, 5.26*GeV, 6.04*GeV, 6.93*GeV, 7.96*GeV, 9.14*GeV, 10.50*GeV, 12.05*GeV, 13.84*GeV, 15.89*GeV, 18.24*GeV, 20.94*GeV, 24.05*GeV, 27.61*GeV, 31.70*GeV, 36.39*GeV, 41.79*GeV, 47.98*GeV, 55.08*GeV, 63.25*GeV, 72.62*GeV, 83.37*GeV, 95.73*GeV, 109.91*GeV, 126.19*GeV, 144.89*GeV, 166.35*GeV, 191.00*GeV, 219.30*GeV, 251.79*GeV, 289.09*GeV, 331.92*GeV, 381.09*GeV, 437.55*GeV, 502.38*GeV, 576.81*GeV, 662.26*GeV, 760.38*GeV, 873.03*GeV, 1002.37*GeV, 1150.88*GeV, 1321.39*GeV, 1517.16*GeV, 1741.93*GeV, 2000.00*GeV};
	*/
	
	
	//////////////////////////////////////////////////////////////////////////////////
	// fill the vector with new vector<double> pointers //////////////////////////////
	CNV->Divide(ncol_pads,nrow_pads);
	CNV->SetFillColor(0);
	stringstream strm;
	string str;
	for(int i=0 ; i<imass_nbins ; i++)
	{
		VVCOSTH.push_back(new vector<double>); ////////
		
		strm.clear();
		str.clear();
		strm << M_bins[i]+(M_bins[i+1]-M_bins[i])/2.;
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

	string m_dataAnalysisSelector = "digest";	
	//string m_muonSelector = "staco/";
	string m_muonSelector = "muid/";

	double m_miny = -0.6;
	double m_maxy = +0.6;

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
	gStyle->SetPadRightMargin(0.05);
	gStyle->SetPadBottomMargin(0.16);
	gStyle->SetPadLeftMargin(0.12);
	Int_t font=42;
	Double_t tsize=0.05;
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
	
	
	TLegend* leg = new TLegend(0.1413043,0.8290155,0.3729097,0.9313472,NULL,"brNDC");
	leg->SetFillColor(kWhite);
	
	TLegend* leg_histos = new TLegend(0.85, 0.15, 0.97, 0.45,NULL,"brNDC");
	leg_histos->SetFillColor(kWhite);
	
	string muonLabel = m_muonSelector.substr(0, m_muonSelector.length()-1);
	string lumilabel = "#intLdt~42 pb^{-1}";
	TPaveText* pvtxt = new TPaveText(0.1195652,0.1334197,0.2458194,0.2318653,"brNDC");
	pvtxt->SetFillColor(kWhite);
	TText* txt  = pvtxt->AddText( lumilabel.c_str() );
	TText* txt1 = pvtxt->AddText( muonLabel.c_str() );
	
	string cName = "cnv_" + hNameFixed;
	TCanvas* cnv = new TCanvas(cName.c_str(), cName.c_str(), 0,0,1200,800);
	
	TPad *pad_mHat = new TPad("pad_mHat","",0,0,1,1);
	pad_mHat->SetFillColor(kWhite);
	pad_mHat->SetTicky(0);
	pad_mHat->SetLogy();
	if(doLogx) pad_mHat->SetLogx();

	TPad *pad_Afb  = new TPad("pad_Afb", "",0,0,1,1);
	pad_Afb->SetGridy();
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
	if(doLogM) hMZ0  = new TH1D("mHat_Z0","mHat_Z0", imass_nbins, M_bins );
	else       hMZ0  = new TH1D("mHat_Z0","mHat_Z0", imass_nbins, imass_min, imass_max );
	hMZ0->SetTitle("");
	hMZ0->SetYTitle("Events");
	hMZ0->SetLineColor(kAzure-5);
	hMZ0->SetLineWidth(2);
	/*
	TH1D* hAfbZ0;
	if(doLogM) hAfbZ0   = new TH1D("Afb_Z0","Afb_Z0", imass_nbins, M_bins );
	else       hAfbZ0   = new TH1D("Afb_Z0","Afb_Z0", imass_nbins, imass_min, imass_max );
	hAfbZ0->SetMarkerStyle(20);
	hAfbZ0->SetMarkerColor(kBlack);
	hAfbZ0->SetMarkerSize(1.2);
	leg->AddEntry( hAfbZ0, "Z0: A_{FB}", "lep");
	leg->AddEntry( hAfbZ0, "Z0: Events", "l");
	*/
	channel = "Z#rightarrow#mu#mu: A_{FB}(stat' uncertainty)";
	TH1D* hAfbZ0;
	if(doLogM) hAfbZ0 = new TH1D("Afb_Z0","Afb_Z0", imass_nbins, M_bins );
	else       hAfbZ0 = new TH1D("Afb_Z0","Afb_Z0", imass_nbins, imass_min, imass_max );
	hAfbZ0->SetLineColor(kAzure-5);
	hAfbZ0->SetFillColor(kAzure-5);
	hAfbZ0->SetLineWidth(1);
	hAfbZ0->SetMarkerSize(0);
	hAfbZ0->SetMarkerColor(0);
	hAfbZ0->SetTitle("");
	hAfbZ0->SetXTitle( xTitle.c_str() );
	hAfbZ0->SetYTitle( yTitle.c_str() );
	leg->AddEntry( hAfbZ0, channel.c_str(), "f");
	
	
	///////////////////////////////////////////////
	// Z' /////////////////////////////////////////
	TH1D* hMZP;
	if(doLogM) hMZP  = new TH1D("mHat_ZP","mHat_ZP", imass_nbins, M_bins );
	else       hMZP  = new TH1D("mHat_ZP","mHat_ZP", imass_nbins, imass_min, imass_max );
	hMZP->SetTitle("");
	hMZP->SetYTitle("Events");
	hMZP->SetLineColor(kRed);
	hMZP->SetLineWidth(2);
	
	channel = "1 TeV Z' SSM: A_{FB}(stat' uncertainty)";
	TH1D* hAfbZP;
	if(doLogM) hAfbZP = new TH1D("Afb_ZP","Afb_ZP", imass_nbins, M_bins );
	else       hAfbZP = new TH1D("Afb_ZP","Afb_ZP", imass_nbins, imass_min, imass_max );
	hAfbZP->SetLineColor(kRed);
	hAfbZP->SetFillColor(kRed);
	hAfbZP->SetLineWidth(1);
	hAfbZP->SetMarkerSize(0);
	hAfbZP->SetMarkerColor(0);
	hAfbZP->SetTitle("");
	hAfbZP->SetXTitle( xTitle.c_str() );
	hAfbZP->SetYTitle( yTitle.c_str() );
	leg->AddEntry( hAfbZP, channel.c_str(), "f");
	
	
	///////////////////////////////////////////////
	// KK /////////////////////////////////////////
	TH1D* hMKK;
	if(doLogM) hMKK  = new TH1D("mHat_KK","mHat_KK", imass_nbins, M_bins );
	else       hMKK  = new TH1D("mHat_KK","mHat_KK", imass_nbins, imass_min, imass_max );
	hMKK->SetTitle("");
	hMKK->SetYTitle("Events");
	hMKK->SetLineColor(kBlack);
	hMKK->SetLineWidth(2);
	
	channel = "1 TeV KK: A_{FB}(stat' uncertainty)";
	TH1D* hAfbKK;
	if(doLogM) hAfbKK = new TH1D("Afb_KK","Afb_KK", imass_nbins, M_bins );
	else       hAfbKK = new TH1D("Afb_KK","Afb_KK", imass_nbins, imass_min, imass_max );
	hAfbKK->SetLineColor(kBlack);
	hAfbKK->SetFillColor(kBlack);
	hAfbKK->SetLineWidth(1);
	hAfbKK->SetMarkerSize(0);
	hAfbKK->SetMarkerColor(0);
	hAfbKK->SetTitle("");
	hAfbKK->SetXTitle( xTitle.c_str() );
	hAfbKK->SetYTitle( yTitle.c_str() );
	leg->AddEntry( hAfbKK, channel.c_str(), "f");
	
	
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
	vsNames.push_back("bu/Z0.M1000.root");
	vsNames.push_back("bu/Z0.lowMass.M1000.root");
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
	
	// fill the imass histo
	if(tree_Z0==0) return;
	for (Long64_t l64t_jentry=0 ; l64t_jentry<tree_Z0->GetEntries() ; l64t_jentry++)
	{
		tree_Z0->GetEntry(l64t_jentry);
		hMZ0->Fill(IMASS*GeV2TeV);
	}
	
	a4   = 0.;
	da4  = 0.;
	afb  = 0.;
	dafb = 0.;
	guess = -0.1;
	ISZ0 = false;
	ISZP = true;
	ISKK = false;
	fillVec(tree_Z0, hAfbZ0); // the VVCOSTH vectors are full
	for(Int_t b=1 ; b<=hAfbZ0->GetNbinsX() ; b++)
	{
		// norm to bin width
		//hMZ0->SetBinContent(b, hMZ0->GetBinContent(b)/hMZ0->GetBinWidth(b));
		CURRENTBIN = (unsigned int)(b-1);
		if((int)VVCOSTH[CURRENTBIN]->size()<minEntriesDATA) continue;
		minimize(guess, a4, da4);
		afb = (3./8.)*a4;
		dafb = (3./8.)*da4;
		guess = a4;
		hAfbZ0->SetBinContent(b,afb);
		hAfbZ0->SetBinError(b,dafb);
		cout << "mHat["<< b << "/" << hAfbZ0->GetNbinsX() << "]=" << xaxis->GetBinCenter(b) << ", Afb=" << afb << " +- " << dafb << "\n" << endl;
	}
	
	
	vsNames.clear();
	sMergedFileName = "ZP.merged.root";
	vsNames.push_back("bu/ZP.M1000.root");
	vsNames.push_back("bu/ZP.lowMass.M1000.root");
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
	
	if(tree_ZP==0) return;
	for (Long64_t l64t_jentry=0 ; l64t_jentry<tree_ZP->GetEntries() ; l64t_jentry++)
	{
		tree_ZP->GetEntry(l64t_jentry);
		hMZP->Fill(IMASS*GeV2TeV);
	}
	
	
	a4   = 0.;
	da4  = 0.;
	afb  = 0.;
	dafb = 0.;
	guess = -0.1;
	ISZ0 = false;
	ISZP = false;
	ISKK = true;
	fillVec(tree_ZP, hAfbZP); // the VVCOSTH vectors are full
	for(Int_t b=1 ; b<=hAfbZP->GetNbinsX() ; b++)
	{
		// norm to bin width
		//hMZ0->SetBinContent(b, hMZ0->GetBinContent(b)/hMZ0->GetBinWidth(b));
		CURRENTBIN = (unsigned int)(b-1);
		if((int)VVCOSTH[CURRENTBIN]->size()<minEntriesDATA) continue;
		minimize(guess, a4, da4);
		afb = (3./8.)*a4;
		dafb = (3./8.)*da4;
		guess = a4;
		hAfbZP->SetBinContent(b,afb);
		hAfbZP->SetBinError(b,dafb);
		cout << "mHat["<< b << "/" << hAfbZP->GetNbinsX() << "]=" << xaxis->GetBinCenter(b) << ", Afb=" << afb << " +- " << dafb << "\n" << endl;
	}
	
	
	vsNames.clear();
	sMergedFileName = "KK.merged.root";
	vsNames.push_back("bu/KK.M1000.root");
	vsNames.push_back("bu/KK.lowMass.M1000.root");
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
	
	if(tree_KK==0) return;
	for (Long64_t l64t_jentry=0 ; l64t_jentry<tree_KK->GetEntries() ; l64t_jentry++)
	{
		tree_KK->GetEntry(l64t_jentry);
		hMKK->Fill(IMASS*GeV2TeV);
	}
	
	a4   = 0.;
	da4  = 0.;
	afb  = 0.;
	dafb = 0.;
	guess = -0.1;
	ISZ0 = false;
	ISZP = false;
	ISKK = true;
	fillVec(tree_KK, hAfbKK); // the VVCOSTH vectors are full
	for(Int_t b=1 ; b<=hAfbKK->GetNbinsX() ; b++)
	{
		// norm to bin width
		//hMZ0->SetBinContent(b, hMZ0->GetBinContent(b)/hMZ0->GetBinWidth(b));
		CURRENTBIN = (unsigned int)(b-1);
		if((int)VVCOSTH[CURRENTBIN]->size()<minEntriesDATA) continue;
		minimize(guess, a4, da4);
		afb = (3./8.)*a4;
		dafb = (3./8.)*da4;
		guess = a4;
		hAfbKK->SetBinContent(b,afb);
		hAfbKK->SetBinError(b,dafb);
		cout << "mHat["<< b << "/" << hAfbKK->GetNbinsX() << "]=" << xaxis->GetBinCenter(b) << ", Afb=" << afb << " +- " << dafb << "\n" << endl;
	}
	
	
	
	
	pad_mHat->Draw();
	pad_mHat->cd();
	//hMZ0->GetYaxis()->SetRangeUser(1,1.5*hMZ0->GetMaximum());
	hMZ0->Draw();
	hMZ0->GetXaxis()->SetMoreLogLabels(); 
	hMZ0->GetXaxis()->SetNoExponent(); 
	hMZP->Draw("SAMES");
	hMZP->GetXaxis()->SetMoreLogLabels(); 
	hMZP->GetXaxis()->SetNoExponent(); 
	hMKK->Draw("SAMES");
	hMKK->GetXaxis()->SetMoreLogLabels(); 
	hMKK->GetXaxis()->SetNoExponent(); 

	cnv->cd();

	pad_Afb->Draw();
	pad_Afb->cd();
	hAfbZP->GetYaxis()->SetRangeUser(m_miny,m_maxy);
	hAfbZP->Draw("E5 Y+");
	hAfbZP->GetXaxis()->SetMoreLogLabels(); 
	hAfbZP->GetXaxis()->SetNoExponent(); 
	hAfbZ0->Draw("E5 Y+ SAMES");
	hAfbZ0->GetXaxis()->SetMoreLogLabels(); 
	hAfbZ0->GetXaxis()->SetMoreLogLabels(); 
	//hAfbZ0->Draw("e1x0SAMES");
	hAfbKK->Draw("E5 Y+ SAMES");
	hAfbKK->GetXaxis()->SetMoreLogLabels(); 
	hAfbKK->GetXaxis()->SetMoreLogLabels(); 
	//pvtxt->Draw("SAMES");
	leg->Draw("SAMES");
	TLine* lUnit = new TLine(imass_min,0.,imass_max,0.);
	lUnit->SetLineColor(kBlack);
	lUnit->SetLineStyle(2);
	//lUnit->Draw("SAMES");
	//pad_Afb->RedrawAxis();
	
	cnv->cd();
	
	pad_mHat->cd();
	pad_mHat->RedrawAxis();
	pad_mHat->Update();

	cnv->Update();
	
	TString fName = (TString)hNameFixed + "_" + (TString)muonLabel;
	cnv->SaveAs(fName+".eps");
	cnv->SaveAs(fName+".C");
	cnv->SaveAs(fName+".root");
	cnv->SaveAs(fName+".png");
	
	/*
	CNV->Draw();
	for(int i=0 ; i<imass_nbins ; i++)
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