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
vector<double> *VCOSTH = new vector<double>();
Float_t IMASS;
Float_t COSTH;

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
	vector<double> xVec = *VCOSTH; // VCOSTH is global
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
	VCOSTH->clear();
	if (t==0) return;
	
	Double_t bmin = h->GetBinLowEdge(b);
	Double_t bwid = h->GetBinWidth(b);
	Double_t bmax = bmin+bwid;
	
	for (Long64_t l64t_jentry=0 ; l64t_jentry<t->GetEntries() ; l64t_jentry++)
	{
		t->GetEntry(l64t_jentry);
		if( IMASS>=(Float_t)bmin  &&  IMASS<(Float_t)bmax ) VCOSTH->push_back(COSTH);
	}
}

void minimize(double& A4, double& dA4)
{
	int npar = 1;      // the number of parameters
	TMinuit minuit(npar);
	minuit.SetFCN(fcn);

	double par[npar];        // the start values
	double stepSize[npar];   // step sizes
	double minVal[npar];     // minimum bound on parameter
	double maxVal[npar];     // maximum bound on parameter
	string parName[npar];

	par[0]      = 0.01; 
	stepSize[0] = 1e-6;
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


void execute()
{
	int minEntriesDATA = 10;
	int minEntriesMC   = 10;
	string refframe = "CosThetaCS";
	//string refframe = "CosThetaHE";
	bool doLogM = true;
	bool doLogx = false;
	
	float GeV2TeV = 1.e-3;
	int    imass_nbins = 20;
	double imass_min   = 80.*GeV2TeV;
	double imass_max   = 400.*GeV2TeV;
	//double imass_min   = 60.*GeV2TeV;
	//double imass_max   = 360.*GeV2TeV;
	
	// logarithmic boundries and bins of histograms
	Double_t logMmin     = log10(imass_min);
	Double_t logMmax     = log10(imass_max);
	Double_t M_bins[100+1];
	
	Double_t M_binwidth = (Double_t)( (logMmax-logMmin)/(Double_t)imass_nbins );
	M_bins[0] = imass_min;
	for(Int_t i=1 ; i<=imass_nbins ; i++) M_bins[i] = TMath::Power( 10,(logMmin + i*M_binwidth) );

	//string dir   = "/data/hod/D3PDdigest/rel15_barrel_selection/";
	string dir   = "/data/hod/D3PDdigest/rel15_eta24_selection/";
	string hDir  = "allCuts";
	string hName = "Afb";
	string xTitle = "#hat{m}_{#mu#mu} TeV";
	string yTitle= "A_{FB}#left(#hat{m}_{#mu#mu}#right)";

	string m_dataAnalysisSelector = "digest";	
	string m_muonSelector = "staco/";

	double m_miny = -0.6;
	double m_maxy = +0.6;

	string hNameFixed = hName;

	gStyle->SetOptStat(0);
	
	TLegend* leg = new TLegend(0.7107023,0.7098446,0.867893,0.8626943,NULL,"brNDC");
	leg->SetFillColor(kWhite);
	
	string L = "43";
	string lumilabel = "#intLdt~" + L + " pb^{-1}";
	TPaveText* pvtxt = new TPaveText(0.1195652,0.1334197,0.2458194,0.2318653,"brNDC");
	pvtxt->SetFillColor(kWhite);
	TText* txt = pvtxt->AddText( lumilabel.c_str() );
	
	string muonLabel = m_muonSelector.substr(0, m_muonSelector.length()-1);
	TPaveText* pvtxt1 = new TPaveText(0.1421405,0.126943,0.2165552,0.1683938,"brNDC");
	pvtxt1->SetFillColor(kWhite);
	TText* txt1 = pvtxt1->AddText( muonLabel.c_str() );
	
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
	string analysisType = (m_dataAnalysisSelector=="digest") ? "mcDigestControl_" : "mcOfflineControl_";
	
	// Data
	TH1D* hDataM;
	if(doLogM) hDataM  = new TH1D("mHat_data","mHat_data", imass_nbins, M_bins );
	else       hDataM  = new TH1D("mHat_data","mHat_data", imass_nbins, imass_min, imass_max );
	hDataM->SetTitle("");
	hDataM->SetYTitle("#frac{dN}{d#hat{m}_{#mu#mu}} 1/TeV");
	hDataM->SetLineColor(kBlack);
	hDataM->SetLineWidth(2);
	TH1D* hData;
	if(doLogM) hData   = new TH1D("Afb_data","Afb_data", imass_nbins, M_bins );
	else       hData   = new TH1D("Afb_data","Afb_data", imass_nbins, imass_min, imass_max );
	hData->SetMarkerStyle(20);
	hData->SetMarkerColor(kBlack);
	hData->SetMarkerSize(1.2);
	leg->AddEntry( hData, "Data: A_{FB}#left(#hat{m}_{#mu#mu}#right)", "lep");
	leg->AddEntry( hData, "Data: #frac{dN}{d#hat{m}_{#mu#mu}}", "l");
	
	string sData = (m_dataAnalysisSelector=="digest") ? "digestControl" : "offlineControl";
	
	path = dir + "AtoI2_ZprimeGRL/" + m_muonSelector + sData + ".root";
	cout << "path=" << path << endl;
	TFile* fData = new TFile( path.c_str(), "READ" );
	TTree* Afb_data_tree = (TTree*)fData->Get("allCuts/allCuts_tree");
	Afb_data_tree->SetBranchAddress( "Mhat",       &IMASS );
	Afb_data_tree->SetBranchAddress( refframe.c_str(), &COSTH );
	
	// fill the imass histo
	if (Afb_data_tree==0) return;
	for (Long64_t l64t_jentry=0 ; l64t_jentry<Afb_data_tree->GetEntries() ; l64t_jentry++)
	{
		Afb_data_tree->GetEntry(l64t_jentry);
		hDataM->Fill(IMASS);
	}
	
	double a4  = 0.;
	double da4 = 0.;
	double afb  = 0.;
	double dafb = 0.;
	for(Int_t b=1 ; b<=hData->GetNbinsX() ; b++)
	{
		// norm to bin width
		hDataM->SetBinContent(b, hDataM->GetBinContent(b)/hDataM->GetBinWidth(b));
		
		fillVec(Afb_data_tree, hData, b); // the VCOSTH vector is full
		if((int)VCOSTH->size()<minEntriesDATA) continue;
		minimize(a4, da4);
		afb = (3./8.)*a4;
		dafb = (3./8.)*da4;
		hData->SetBinContent(b,afb);
		hData->SetBinError(b,dafb);
	}
	
	
	// Backgrounds
	channel = "DYmumu: A_{FB}#left(#hat{m}_{#mu#mu}#right)";
	TH1D* hBGsum;
	if(doLogM) hBGsum = new TH1D("Afb_sumBG","Afb_sumBG", imass_nbins, M_bins );
	else       hBGsum = new TH1D("Afb_sumBG","Afb_sumBG", imass_nbins, imass_min, imass_max );
	hBGsum->SetLineColor(kAzure-5);
	hBGsum->SetFillColor(kAzure-5);
	hBGsum->SetLineWidth(1);
	hBGsum->SetMarkerSize(0);
	hBGsum->SetMarkerColor(0);
	hBGsum->SetTitle("");
	hBGsum->SetXTitle( xTitle.c_str() );
	hBGsum->SetYTitle( yTitle.c_str() );
	leg->AddEntry( hBGsum, channel.c_str(), "f");
	
	
	TList* Afb_sumBG_list = new TList();
	
	/*
	sProc = "Zmumu";
	path = dir + "Zmumu/" + m_muonSelector + analysisType + sProc + ".root";
	cout << "path=" << path << endl;
	TFile* fZmumu = new TFile( path.c_str(), "READ" );
	Afb_sumBG_list->Add( (TTree*)fZmumu->Get("allCuts/allCuts_tree") );
	*/
	
	/*
	sProc = "DYmumu_75M120";
	path = "/srv01/tau/hod/z0analysis-tests/z0analysis-dev/run/mcWZphys.root";
	TFile* fDYmumu_75M120 = new TFile( path.c_str(), "READ" );
	Afb_sumBG_list->Add( (TTree*)fDYmumu_75M120->Get("allCuts/allCuts_tree") );
	*/
	
	
	sProc = "DYmumu_75M120";
	path = dir + "DYmumu/" + m_muonSelector + analysisType + sProc + ".root";
	cout << "path=" << path << endl;
	TFile* fDYmumu_75M120 = new TFile( path.c_str(), "READ" );
	Afb_sumBG_list->Add( (TTree*)fDYmumu_75M120->Get("allCuts/allCuts_tree") );
	
	sProc = "DYmumu_120M250";
	path = dir + "DYmumu/" + m_muonSelector + analysisType + sProc + ".root";
	cout << "path=" << path << endl;
	TFile* fDYmumu_120M250 = new TFile( path.c_str(), "READ" );
	Afb_sumBG_list->Add( (TTree*)fDYmumu_120M250->Get("allCuts/allCuts_tree") );
	
	sProc = "DYmumu_250M400";
	path = dir + "DYmumu/" + m_muonSelector + analysisType + sProc + ".root";
	cout << "path=" << path << endl;
	TFile* fDYmumu_250M400 = new TFile( path.c_str(), "READ" );
	Afb_sumBG_list->Add( (TTree*)fDYmumu_250M400->Get("allCuts/allCuts_tree") );

	sProc = "DYmumu_400M600";
	path = dir + "DYmumu/" + m_muonSelector + analysisType + sProc + ".root";
	cout << "path=" << path << endl;
	TFile* fDYmumu_400M600 = new TFile( path.c_str(), "READ" );
	Afb_sumBG_list->Add( (TTree*)fDYmumu_400M600->Get("allCuts/allCuts_tree") );
	
	
	/*	
	sProc = "ZZ_Herwig";
	path = dir + "ZZ_Herwig/" + m_muonSelector + analysisType + sProc + ".root";
	TFile* fZZ = new TFile( path.c_str(), "READ" );
	Afb_sumBG_list->Add( (TTree*)fZZ->Get("allCuts/allCuts_tree") );
	
	sProc = "WZ_Herwig";
	path = dir + "WZ_Herwig/" + m_muonSelector + analysisType + sProc + ".root";
	TFile* fWZ = new TFile( path.c_str(), "READ" );
	Afb_sumBG_list->Add( (TTree*)fWZ->Get("allCuts/allCuts_tree") );
	
	sProc = "WW_Herwig";
	path = dir + "WW_Herwig/" + m_muonSelector + analysisType + sProc + ".root";
	TFile* fWW = new TFile( path.c_str(), "READ" );
	Afb_sumBG_list->Add( (TTree*)fWW->Get("allCuts/allCuts_tree") );
	
	sProc = "T1_McAtNlo_Jimmy";
	path = dir + "T1_McAtNlo_Jimmy/" + m_muonSelector + analysisType + sProc + ".root";
	TFile* fT1 = new TFile( path.c_str(), "READ" );
	Afb_sumBG_list->Add( (TTree*)fT1->Get("allCuts/allCuts_tree") );
	
	
	sProc = "DYtautau_75M120";
	path = dir + "DYtautau/" + m_muonSelector + analysisType + sProc + ".root";
	TFile* fDYtautau_75M120 = new TFile( path.c_str(), "READ" );
	Afb_sumBG_list->Add( (TTree*)fDYtautau_75M120->Get("allCuts/allCuts_tree") );
	
	sProc = "DYtautau_120M250";
	path = dir + "DYtautau/" + m_muonSelector + analysisType + sProc + ".root";
	TFile* fDYtautau_120M250 = new TFile( path.c_str(), "READ" );
	Afb_sumBG_list->Add( (TTree*)fDYtautau_120M250->Get("allCuts/allCuts_tree") );
	
	sProc = "DYtautau_250M400";
	path = dir + "DYtautau/" + m_muonSelector + analysisType + sProc + ".root";
	TFile* fDYtautau_250M400 = new TFile( path.c_str(), "READ" );
	Afb_sumBG_list->Add( (TTree*)fDYtautau_250M400->Get("allCuts/allCuts_tree") );

*/	
	
	TFile* mergedFile = new TFile("Afb_sumBG_merged.root", "RECREATE");
	cout << "Merging trees...patience..." << endl;
	TTree::MergeTrees(Afb_sumBG_list);
	mergedFile->Write();
	mergedFile->Close();
	
	TFile* fBG = new TFile("Afb_sumBG_merged.root", "READ");
	//TTree* Afb_sumBG_tree = (TTree*)fBG->Get("Afb_tree");
	//Afb_sumBG_tree->SetBranchAddress( "mHat",  &IMASS );
	//Afb_sumBG_tree->SetBranchAddress( "cosTh", &COSTH );
	
	TTree* Afb_sumBG_tree = (TTree*)fBG->Get("allCuts_tree");
	Afb_sumBG_tree->SetBranchAddress( "Mhat",       &IMASS );
	Afb_sumBG_tree->SetBranchAddress( refframe.c_str(), &COSTH );

	a4   = 0.;
	da4  = 0.;
	afb  = 0.;
	dafb = 0.;
	for(Int_t b=1 ; b<=hBGsum->GetNbinsX() ; b++)
	{
		fillVec(Afb_sumBG_tree, hBGsum, b); // the VCOSTH vector is full
		if((int)VCOSTH->size()<minEntriesMC) continue;
		minimize(a4, da4);
		afb = (3./8.)*a4;
		dafb = (3./8.)*da4;
		hBGsum->SetBinContent(b,afb);
		hBGsum->SetBinError(b,dafb);
	}
	TH1D* hBGsumTmp = (TH1D*)hBGsum->Clone("");
	hBGsumTmp->Reset();
	for(Int_t b=1 ; b<hBGsumTmp->GetNbinsX() ; b++) hBGsumTmp->SetBinContent(b,hBGsum->GetBinContent(b));
	hBGsumTmp->SetLineColor(kAzure+8);
	
	
	pad_mHat->Draw();
	pad_mHat->cd();
	hDataM->GetYaxis()->SetRangeUser(1,1.5*hDataM->GetMaximum());
	hDataM->Draw();

	cnv->cd();

	pad_Afb->Draw();
	pad_Afb->cd();
	hBGsum->GetYaxis()->SetRangeUser(m_miny,m_maxy);
	hBGsum->Draw("E5 Y+");
	//hBGsumTmp->Draw("CSAMES");
	hData->Draw("e1x0SAMES");
	pvtxt->Draw("SAMES");
	pvtxt1->Draw("SAMES");
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

	
	TString fName = "figures/" + (TString)hNameFixed + "_" + (TString)muonLabel;
	cnv->SaveAs(fName+".eps");
	cnv->SaveAs(fName+".C");
	cnv->SaveAs(fName+".root");
	cnv->SaveAs(fName+".png");
}
