#include "../include/rawStd.h"
#include "../include/rawROOT.h"
#include "../include/enums.h"
#include "../include/logs.h"
#include "../include/style.h"
//#include "../include/bins.h"
#include "../include/histos.h"
//#include "../include/fkinematics.h"
#include "../include/units.h"
#include "../include/couplings.h"
#include "../include/width.h"
#include "../include/helicity.h"

using namespace couplings;
using namespace width;
using namespace helicity;

void hamp()
{
	msglvl[DBG] = VISUAL;
	msglvl[INF] = VISUAL;
	msglvl[WRN] = VISUAL;
	msglvl[ERR] = VISUAL;
	msglvl[FAT] = VISUAL;

	style();

	/////////////////////
	setFermions(); //////
	/////////////////////
	
	TString mBSM = (TString)_s(mKK*GeV2TeV);
	
	// mass range
	double xMin = 5.;
	double xMax = 5005.;
	double dx   = 5.;
	Int_t  Nx   = (Int_t)((xMax-xMin)/dx);
	
	// cos(theta*) range
	double yMin = -1.;
	double yMax = +1.;
	double dy   = 0.01;
	Int_t  Ny   = (Int_t)((yMax-yMin)/dy);
	
	// BSM mass range
	double mMin = 120.;
	double mMax = 5000.;
	double dm   = 5.;
	Int_t  Nm   = (Int_t)((mMax-mMin)/dm);
	

	TH1D* h1KK = new TH1D("h1KK","DY(black), "+mBSM+" TeV Z'_{SSM}(blue) and "+mBSM+" TeV KK(red);m_{#mu#mu} GeV;arbitrary scale", Nx,xMin,xMax);
	TH1D* h1ZP = new TH1D("h1ZP","DY(black), "+mBSM+" TeV Z'_{SSM}(blue) and "+mBSM+" TeV KK(red);m_{#mu#mu} GeV;arbitrary scale", Nx,xMin,xMax);
	TH1D* h1SM = new TH1D("h1SM","DY(black), "+mBSM+" TeV Z'_{SSM}(blue) and "+mBSM+" TeV KK(red);m_{#mu#mu} GeV;arbitrary scale", Nx,xMin,xMax);
	h1SM->SetLineColor(kBlack);
	h1SM->SetLineStyle(1);
	h1ZP->SetLineColor(kBlue);
	h1ZP->SetLineStyle(3);
	h1KK->SetLineColor(kRed);
	h1KK->SetLineStyle(5);
	
	TH1D* h1AsymKK = new TH1D("h1AsymKK","DY(black), "+mBSM+" TeV Z'_{SSM}(blue) and "+mBSM+" TeV KK(red);m_{#mu#mu} GeV;A_{fb}", Nx,xMin,xMax);
	TH1D* h1AsymZP = new TH1D("h1AsymZP","DY(black), "+mBSM+" TeV Z'_{SSM}(blue) and "+mBSM+" TeV KK(red);m_{#mu#mu} GeV;A_{fb}", Nx,xMin,xMax);
	TH1D* h1AsymSM = new TH1D("h1AsymSM","DY(black), "+mBSM+" TeV Z'_{SSM}(blue) and "+mBSM+" TeV KK(red);m_{#mu#mu} GeV;A_{fb}", Nx,xMin,xMax);
	h1AsymSM->SetLineColor(kBlack);
	h1AsymSM->SetLineStyle(1);
	h1AsymZP->SetLineColor(kBlue);
	h1AsymZP->SetLineStyle(3);
	h1AsymKK->SetLineColor(kRed);
	h1AsymKK->SetLineStyle(5);
	
	TH1D* h1wGKK = new TH1D("h1wGKK","Z'_{SSM}(blue) and KK #gamma(red)/Z(green);pole mass GeV;#Gamma_{tot}", Nm,mMin,mMax);
	TH1D* h1wZKK = new TH1D("h1wZKK","Z'_{SSM}(blue) and KK #gamma(red)/Z(green);pole mass GeV;#Gamma_{tot}", Nm,mMin,mMax);
	TH1D* h1wZP  = new TH1D("h1wZP","Z'_{SSM}(blue) and KK #gamma(red)/Z(green);pole mass GeV;#Gamma_{tot}", Nm,mMin,mMax);
	h1wZP->SetLineColor(kBlue);
	h1wZP->SetLineStyle(3);
	h1wGKK->SetLineColor(kRed);
	h1wGKK->SetLineStyle(5);
	h1wZKK->SetLineColor(kGreen);
	h1wZKK->SetLineStyle(5);
	
	TH1D* h1rKK = new TH1D("h1rKK","Z'_{SSM}(blue) and KK(red);m_{#mu#mu} GeV;ME^{2}_{BSM}/ME^{2}_{DY}", Nx,xMin,xMax);
	TH1D* h1rZP = new TH1D("h1rZP","Z'_{SSM}(blue) and KK(red);m_{#mu#mu} GeV;ME^{2}_{BSM}/ME^{2}_{DY}", Nx,xMin,xMax);
	h1rZP->SetLineColor(kBlue);
	h1rZP->SetLineStyle(3);
	h1rKK->SetLineColor(kRed);
	h1rKK->SetLineStyle(5);
	
	TH2D* h2rKK = new TH2D("h2rKK",mBSM+" TeV KK;m_{#mu#mu} GeV;cos#theta*;ME^{2}_{BSM}/ME^{2}_{DY}", Nx,xMin,xMax, Ny,yMin,yMax);
	TH2D* h2rZP = new TH2D("h2rZP",mBSM+" TeV Z'_{SSM};m_{#mu#mu} GeV;cos#theta*;ME^{2}_{BSM}/ME^{2}_{DY}", Nx,xMin,xMax, Ny,yMin,yMax);
	
	TH2D* h2KK = new TH2D("h2KK",mBSM+" TeV KK;m_{#mu#mu} GeV;cos#theta*;arbitrary scale", Nx,xMin,xMax, Ny,yMin,yMax);
	TH2D* h2ZP = new TH2D("h2ZP",mBSM+" TeV Z'_{SSM};m_{#mu#mu} GeV;cos#theta*;arbitrary scale", Nx,xMin,xMax, Ny,yMin,yMax);
	TH2D* h2SM = new TH2D("h2SM","DY;m_{#mu#mu} GeV;cos#theta*;arbitrary scale", Nx,xMin,xMax, Ny,yMin,yMax);
	
	for(double m=xMin ; m<=xMax ; m+=dx)
	{
		double A2KK = 0.;
		double A2ZP = 0.;
		double A2SM = 0.;
		
		double IFA2KK = 0.;
		double IFA2ZP = 0.;
		double IFA2SM = 0.;
		double IBA2KK = 0.;
		double IBA2ZP = 0.;
		double IBA2SM = 0.;
		
		double AfbSM = 0.;
		double AfbZP = 0.;
		double AfbKK = 0.;
		
		double rKK = 0.;
		double rZP = 0.;
		
		double s  = m*m;
		unsigned int idOut = s2f["muon"]->id;
		unsigned int idIn  = s2f["up"]->id;
		Int_t bin = 0;
		unsigned int nsegments = 100;
		
		ISM fSM(s,idIn,idOut);
		IZP fZP(s,idIn,idOut);
		IKK fKK(s,idIn,idOut);
		IFA2KK = integrate(fKK,0.,+1.,nsegments);
		IFA2ZP = integrate(fZP,0.,+1.,nsegments);
		IFA2SM = integrate(fSM,0.,+1.,nsegments);
		IBA2KK = integrate(fKK,-1.,0.,nsegments);
		IBA2ZP = integrate(fZP,-1.,0.,nsegments);
		IBA2SM = integrate(fSM,-1.,0.,nsegments);
		
		AfbSM = (IFA2SM-IBA2SM)/(IFA2SM+IBA2SM);
		AfbZP = (IFA2ZP-IBA2ZP)/(IFA2ZP+IBA2ZP);
		AfbKK = (IFA2KK-IBA2KK)/(IFA2KK+IBA2KK);
		
		bin = h1AsymKK->FindBin(m);
		h1AsymKK->SetBinContent(bin,AfbKK);
		h1AsymZP->SetBinContent(bin,AfbZP);
		h1AsymSM->SetBinContent(bin,AfbSM);
		
		/////////////////////////////////////////////////////////////////////
		
		// double cosTheta = 0.;
		// A2KK = hA2KK(cosTheta,s,idIn,idOut); // one incoming flavor (u-quark) in a given cosTheta
		// A2ZP = hA2ZP(cosTheta,s,idIn,idOut); // one incoming flavor (u-quark) in a given cosTheta
		// A2SK = hA2SM(cosTheta,s,idIn,idOut); // one incoming flavor (u-quark) in a given cosTheta
		// double cosTheta = 0.;
		//Meaningless // A2KK = hA2KKsumQ(cosTheta,s,idOut); // sum the incoming flavors in a given cosTheta
		//Meaningless // A2ZP = hA2ZPsumQ(cosTheta,s,idOut); // sum the incoming flavors in a given cosTheta
		//Meaningless // A2SM = hA2SMsumQ(cosTheta,s,idOut); // sum the incoming flavors in a given cosTheta
		// 
		A2KK = IFA2KK+IBA2KK; // sum the incoming flavors and integrate over cosTheta
		A2ZP = IFA2ZP+IBA2ZP; // sum the incoming flavors and integrate over cosTheta
		A2SM = IFA2SM+IBA2SM; // sum the incoming flavors and integrate over cosTheta
		
		bin = h1KK->FindBin(m);
		h1KK->SetBinContent(bin,A2KK);
		h1ZP->SetBinContent(bin,A2ZP);
		h1SM->SetBinContent(bin,A2SM);
		
		
		rKK = (IFA2KK+IBA2KK)/(IFA2SM+IBA2SM); // one incoming flavor (u-quark) and integrated over cosTheta
		rZP = (IFA2ZP+IBA2ZP)/(IFA2SM+IBA2SM); // one incoming flavor (u-quark) and integrated over cosTheta
		// double cosTheta = 0.;
		// rKK = weightKK(cosTheta,s,idIn,idOut); // one incoming flavor (u-quark) in a given cosTheta
		// rZP = weightZP(cosTheta,s,idIn,idOut); // one incoming flavor (u-quark) in a given cosTheta
		h1rKK->SetBinContent(bin,rKK);
		h1rZP->SetBinContent(bin,rZP);
		_INFO("rKK="+_s(rKK)+", rZP="+_s(rZP));
		
		cout << "m=" << m << "\r" << flush;
		
		for(double cost=yMin ; cost<=yMax ; cost+=dy)
		{
			A2KK = hA2KK(cost,s,idIn,idOut);
			A2ZP = hA2ZP(cost,s,idIn,idOut);
			A2SM = hA2SM(cost,s,idIn,idOut);
			Int_t binxy = h2KK->FindBin(m,cost);
			h2KK->SetBinContent(binxy,A2KK);
			h2ZP->SetBinContent(binxy,A2ZP);
			h2SM->SetBinContent(binxy,A2SM);
			
			rKK = weightKK(cost,s,idIn,idOut); // one incoming flavor (u-quark) in a given cosTheta
			rZP = weightZP(cost,s,idIn,idOut); // one incoming flavor (u-quark) in a given cosTheta
			h2rKK->SetBinContent(binxy,rKK);
			h2rZP->SetBinContent(binxy,rZP);
		}
	}
	
	for(double m=mMin ; m<=mMax ; m+=dm)
	{
		mKK = m;
		mZP = m;
	
		double widthZP  = wTotZP();
		double widthGKK = wTotGKK(1);
		double widthZKK = wTotZKK(1);
		
		Int_t bin = h1wZP->FindBin(m);
		h1wGKK->SetBinContent(bin,widthGKK);
		h1wZKK->SetBinContent(bin,widthZKK);
		h1wZP->SetBinContent(bin,widthZP);
	}
	
	TCanvas* cnv_1d = new TCanvas("c1d","c1d",600,400);
	cnv_1d->SetLogy();
	cnv_1d->cd();
	cnv_1d->Draw();
	h1SM->Draw();
	h1KK->Draw("SAMES");
	h1ZP->Draw("SAMES");
	saveas(cnv_1d,"plots/theory_mass");
	
	TCanvas* cnv_1dr = new TCanvas("c1dr","c1dr",600,400);
	cnv_1dr->SetLogy();
	cnv_1dr->cd();
	cnv_1dr->Draw();
	h1rKK->Draw();
	h1rZP->Draw("SAMES");
	saveas(cnv_1dr,"plots/theory_ratioVSmass");
	
	TCanvas* cnv_2dr = new TCanvas("c2dr","c2dr",600,800);
	cnv_2dr->Divide(1,2);
	TVirtualPad* pad_2drKK = cnv_2dr->cd(2);
	TVirtualPad* pad_2drZP = cnv_2dr->cd(1);
	pad_2drKK->SetLogz();
	pad_2drZP->SetLogz();
	cnv_2dr->cd();
	cnv_2dr->Draw();
	pad_2drKK->cd();
	h2rKK->Draw("COLZ");
	pad_2drZP->cd();
	h2rZP->Draw("COLZ");
	saveas(cnv_2dr,"plots/theory_ratioVSmassVScost");
	
	TCanvas* cnv_2d = new TCanvas("c2d","c2d",600,1000);
	cnv_2d->Divide(1,3);
	TVirtualPad* pad_2dKK = cnv_2d->cd(3);
	TVirtualPad* pad_2dZP = cnv_2d->cd(2);
	TVirtualPad* pad_2dSM = cnv_2d->cd(1);
	pad_2dKK->SetLogz();
	pad_2dZP->SetLogz();
	pad_2dSM->SetLogz();
	cnv_2d->cd();
	cnv_2d->Draw();
	pad_2dKK->cd();
	h2KK->Draw("COLZ");
	pad_2dZP->cd();
	h2ZP->Draw("COLZ");
	pad_2dSM->cd();
	h2SM->Draw("COLZ");
	saveas(cnv_2d,"plots/theory_massVScost");
	
	TCanvas* cnv_1dAsym = new TCanvas("c1dAsym","c1dAsym",600,400);
	cnv_1dAsym->cd();
	cnv_1dAsym->Draw();
	h1AsymSM->Draw();
	h1AsymZP->Draw("SAMES");
	h1AsymKK->Draw("SAMES");
	saveas(cnv_1dAsym,"plots/theory_asymVSmass");
	
	TCanvas* cnv_1dw = new TCanvas("c1dw","c1dw",600,400);
	cnv_1dw->cd();
	cnv_1dw->Draw();
	h1wGKK->Draw();
	h1wZKK->Draw("SAMES");
	h1wZP->Draw("SAMES");
	saveas(cnv_1dw,"plots/theory_widthVSpolemass");
	
	//F f(1.,1.);
	//cout << "integrate: " << integrate(f,0.,+100.,1000) << endl;
}
