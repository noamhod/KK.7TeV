#include "../include/rawStd.h"
#include "../include/rawROOT.h"
#include "../include/enums.h"
#include "../include/logs.h"
#include "../include/style.h"
#include "../include/bins.h"
#include "../include/histos.h"
#include "../include/fkinematics.h"
#include "../include/units.h"
#include "../include/couplings.h"
#include "../include/width.h"
#include "../include/helicity.h"
#include "../include/kFactors.h"

using namespace couplings;
using namespace width;
using namespace helicity;
using namespace kFactors;

void hamp()
{
	msglvl[DBG] = SILENT;
	msglvl[INF] = VISUAL;
	msglvl[WRN] = VISUAL;
	msglvl[ERR] = VISUAL;
	msglvl[FAT] = VISUAL;

	style();

	///////////////////////
	setFermions(); ////////
	setkFactors(false); ///
	///////////////////////
	
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
	
	double wgtMaxZP = 0.;
	double wgtMaxKK = 0.;
	

	TH1D* h1KK     = new TH1D("h1KK","DY(black),     "+mBSM+" TeV Z'_{SSM}(blue) and "+mBSM+" TeV KK(red);m_{#mu#mu} GeV;arbitrary scale", Nx,xMin,xMax);
	TH1D* h1KKnoSM = new TH1D("h1KKnoSM","DY(black), "+mBSM+" TeV Z'_{SSM}(blue) and "+mBSM+" TeV KK(red);m_{#mu#mu} GeV;arbitrary scale", Nx,xMin,xMax);
	TH1D* h1ZP     = new TH1D("h1ZP","DY(black),     "+mBSM+" TeV Z'_{SSM}(blue) and "+mBSM+" TeV KK(red);m_{#mu#mu} GeV;arbitrary scale", Nx,xMin,xMax);
	TH1D* h1ZPnoSM = new TH1D("h1ZPnoSM","DY(black), "+mBSM+" TeV Z'_{SSM}(blue) and "+mBSM+" TeV KK(red);m_{#mu#mu} GeV;arbitrary scale", Nx,xMin,xMax);
	TH1D* h1SM     = new TH1D("h1SM","DY(black),     "+mBSM+" TeV Z'_{SSM}(blue) and "+mBSM+" TeV KK(red);m_{#mu#mu} GeV;arbitrary scale", Nx,xMin,xMax);
	h1SM->SetLineColor(kBlack);
	h1SM->SetLineStyle(1);
	h1ZP->SetLineColor(kBlue);
	h1ZP->SetLineStyle(1);
	h1ZPnoSM->SetLineColor(kBlue);
	h1ZPnoSM->SetLineStyle(3);
	h1KK->SetLineColor(kRed);
	h1KK->SetLineStyle(1);
	h1KKnoSM->SetLineColor(kRed);
	h1KKnoSM->SetLineStyle(5);
	
	TH1D* h1AsymKK     = new TH1D("h1AsymKK","DY(black),     "+mBSM+" TeV Z'_{SSM}(blue) and "+mBSM+" TeV KK(red);m_{#mu#mu} GeV;A_{fb}", Nx,xMin,xMax);
	TH1D* h1AsymKKnoSM = new TH1D("h1AsymKKnoSM","DY(black), "+mBSM+" TeV Z'_{SSM}(blue) and "+mBSM+" TeV KK(red);m_{#mu#mu} GeV;A_{fb}", Nx,xMin,xMax);
	TH1D* h1AsymZP     = new TH1D("h1AsymZP","DY(black),     "+mBSM+" TeV Z'_{SSM}(blue) and "+mBSM+" TeV KK(red);m_{#mu#mu} GeV;A_{fb}", Nx,xMin,xMax);
	TH1D* h1AsymZPnoSM = new TH1D("h1AsymZPnoSM","DY(black), "+mBSM+" TeV Z'_{SSM}(blue) and "+mBSM+" TeV KK(red);m_{#mu#mu} GeV;A_{fb}", Nx,xMin,xMax);
	TH1D* h1AsymSM     = new TH1D("h1AsymSM","DY(black),     "+mBSM+" TeV Z'_{SSM}(blue) and "+mBSM+" TeV KK(red);m_{#mu#mu} GeV;A_{fb}", Nx,xMin,xMax);
	h1AsymSM->SetLineColor(kBlack);
	h1AsymSM->SetLineStyle(1);
	h1AsymZP->SetLineColor(kBlue);
	h1AsymZP->SetLineStyle(1);
	h1AsymZPnoSM->SetLineColor(kBlue);
	h1AsymZPnoSM->SetLineStyle(3);
	h1AsymKK->SetLineColor(kRed);
	h1AsymKK->SetLineStyle(1);
	h1AsymKKnoSM->SetLineColor(kRed);
	h1AsymKKnoSM->SetLineStyle(5);
	
	TH1D* h1wGKK = new TH1D("h1wGKK","Z'_{SSM}(blue) and KK #gamma(red)/Z(green);pole mass GeV;#Gamma_{tot}", Nm,mMin,mMax);
	TH1D* h1wZKK = new TH1D("h1wZKK","Z'_{SSM}(blue) and KK #gamma(red)/Z(green);pole mass GeV;#Gamma_{tot}", Nm,mMin,mMax);
	TH1D* h1wZP  = new TH1D("h1wZP", "Z'_{SSM}(blue) and KK #gamma(red)/Z(green);pole mass GeV;#Gamma_{tot}", Nm,mMin,mMax);
	h1wZP->SetLineColor(kBlue);
	h1wZP->SetLineStyle(3);
	h1wGKK->SetLineColor(kRed);
	h1wGKK->SetLineStyle(5);
	h1wZKK->SetLineColor(kGreen+2);
	h1wZKK->SetLineStyle(5);
	
	TH1D* h1rKK     = new TH1D("h1rKK",     "Z'_{SSM}(blue) and KK(red);m_{#mu#mu} GeV;ME^{2}_{BSM}/ME^{2}_{DY}", Nx,xMin,xMax);
	TH1D* h1rKKnoSM = new TH1D("h1rKKnoSM", "Z'_{SSM}(blue) and KK(red);m_{#mu#mu} GeV;ME^{2}_{BSM}/ME^{2}_{DY}", Nx,xMin,xMax);
	TH1D* h1rZP     = new TH1D("h1rZP",     "Z'_{SSM}(blue) and KK(red);m_{#mu#mu} GeV;ME^{2}_{BSM}/ME^{2}_{DY}", Nx,xMin,xMax);
	TH1D* h1rZPnoSM = new TH1D("h1rZPnoSM", "Z'_{SSM}(blue) and KK(red);m_{#mu#mu} GeV;ME^{2}_{BSM}/ME^{2}_{DY}", Nx,xMin,xMax);
	h1rZP->SetLineColor(kBlue);
	h1rZP->SetLineStyle(1);
	h1rZPnoSM->SetLineColor(kBlue);
	h1rZPnoSM->SetLineStyle(3);
	h1rKK->SetLineColor(kRed);
	h1rKK->SetLineStyle(1);
	h1rKKnoSM->SetLineColor(kRed);
	h1rKKnoSM->SetLineStyle(5);
	
	TH2D* h2rKK     = new TH2D("h2rKK",     mBSM+" TeV KK;m_{#mu#mu} GeV;cos#theta*;ME^{2}_{BSM}/ME^{2}_{DY}", Nx,xMin,xMax, Ny,yMin,yMax);
	TH2D* h2rKKnoSM = new TH2D("h2rKKnoSM", mBSM+" TeV KK no interference;m_{#mu#mu} GeV;cos#theta*;ME^{2}_{BSM}/ME^{2}_{DY}", Nx,xMin,xMax, Ny,yMin,yMax);
	TH2D* h2rZP     = new TH2D("h2rZP",     mBSM+" TeV Z'_{SSM};m_{#mu#mu} GeV;cos#theta*;ME^{2}_{BSM}/ME^{2}_{DY}", Nx,xMin,xMax, Ny,yMin,yMax);
	TH2D* h2rZPnoSM = new TH2D("h2rZPnoSM", mBSM+" TeV Z'_{SSM} no interference;m_{#mu#mu} GeV;cos#theta*;ME^{2}_{BSM}/ME^{2}_{DY}", Nx,xMin,xMax, Ny,yMin,yMax);
	
	TH2D* h2KK     = new TH2D("h2KK",     mBSM+" TeV KK;m_{#mu#mu} GeV;cos#theta*;arbitrary scale", Nx,xMin,xMax, Ny,yMin,yMax);
	TH2D* h2KKnoSM = new TH2D("h2KKnoSM", mBSM+" TeV KK no interference;m_{#mu#mu} GeV;cos#theta*;arbitrary scale", Nx,xMin,xMax, Ny,yMin,yMax);
	TH2D* h2ZP     = new TH2D("h2ZP",     mBSM+" TeV Z'_{SSM};m_{#mu#mu} GeV;cos#theta*;arbitrary scale", Nx,xMin,xMax, Ny,yMin,yMax);
	TH2D* h2ZPnoSM = new TH2D("h2ZPnoSM", mBSM+" TeV Z'_{SSM} no interference;m_{#mu#mu} GeV;cos#theta*;arbitrary scale", Nx,xMin,xMax, Ny,yMin,yMax);
	TH2D* h2SM     = new TH2D("h2SM","DY;m_{#mu#mu} GeV;cos#theta*;arbitrary scale", Nx,xMin,xMax, Ny,yMin,yMax);
	
	for(double m=xMin ; m<=xMax ; m+=dx)
	{
		double A2KK = 0.;
		double A2KKnoSM = 0.;
		double A2ZP = 0.;
		double A2ZPnoSM = 0.;
		double A2SM = 0.;
		
		double IFA2KK = 0.;
		double IFA2KKnoSM = 0.;
		double IFA2ZP = 0.;
		double IFA2ZPnoSM = 0.;
		double IFA2SM = 0.;
		double IBA2KK = 0.;
		double IBA2KKnoSM = 0.;
		double IBA2ZP = 0.;
		double IBA2ZPnoSM = 0.;
		double IBA2SM = 0.;
		
		double AfbSM = 0.;
		double AfbZP = 0.;
		double AfbZPnoSM = 0.;
		double AfbKK = 0.;
		double AfbKKnoSM = 0.;
		
		double rKK = 0.;
		double rKKnoSM = 0.;
		double rZP = 0.;
		double rZPnoSM = 0.;
		
		double s  = m*m;
		unsigned int idOut = s2f["muon"]->id;
		unsigned int idIn  = s2f["up"]->id;
		Int_t bin = 0;
		unsigned int nsegments = 100;
		
		template_hA2SM fSM(s,idIn,idOut);
		template_hA2ZP fZP(s,idIn,idOut);
		template_hA2KK fKK(s,idIn,idOut);
		template_hA2KKnoSM fKKnoSM(s,idIn,idOut);
		template_hA2ZPnoSM fZPnoSM(s,idIn,idOut);
		IFA2KK = integrate(fKK,0.,+1.,nsegments);
		IFA2KKnoSM = integrate(fKKnoSM,0.,+1.,nsegments);
		IFA2ZP = integrate(fZP,0.,+1.,nsegments);
		IFA2ZPnoSM = integrate(fZPnoSM,0.,+1.,nsegments);
		IFA2SM = integrate(fSM,0.,+1.,nsegments);
		IBA2KK = integrate(fKK,-1.,0.,nsegments);
		IBA2KKnoSM = integrate(fKKnoSM,-1.,0.,nsegments);
		IBA2ZP = integrate(fZP,-1.,0.,nsegments);
		IBA2ZPnoSM = integrate(fZPnoSM,-1.,0.,nsegments);
		IBA2SM = integrate(fSM,-1.,0.,nsegments);
		
		AfbSM = (IFA2SM-IBA2SM)/(IFA2SM+IBA2SM);
		AfbZP = (IFA2ZP-IBA2ZP)/(IFA2ZP+IBA2ZP);
		AfbKK = (IFA2KK-IBA2KK)/(IFA2KK+IBA2KK);
		AfbKKnoSM = (IFA2KKnoSM-IBA2KKnoSM)/(IFA2KKnoSM+IBA2KKnoSM);
		AfbZPnoSM = (IFA2ZPnoSM-IBA2ZPnoSM)/(IFA2ZPnoSM+IBA2ZPnoSM);
		
		bin = h1AsymKK->FindBin(m);
		h1AsymKK->SetBinContent(bin,AfbKK);
		h1AsymKKnoSM->SetBinContent(bin,AfbKKnoSM);
		h1AsymZP->SetBinContent(bin,AfbZP);
		h1AsymZPnoSM->SetBinContent(bin,AfbZPnoSM);
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
		A2KKnoSM = IFA2KKnoSM+IBA2KKnoSM; // sum the incoming flavors and integrate over cosTheta
		A2ZP = IFA2ZP+IBA2ZP; // sum the incoming flavors and integrate over cosTheta
		A2ZPnoSM = IFA2ZPnoSM+IBA2ZPnoSM; // sum the incoming flavors and integrate over cosTheta
		A2SM = IFA2SM+IBA2SM; // sum the incoming flavors and integrate over cosTheta
		
		bin = h1KK->FindBin(m);
		h1KK->SetBinContent(bin,A2KK);
		h1KKnoSM->SetBinContent(bin,A2KKnoSM);
		h1ZP->SetBinContent(bin,A2ZP);
		h1ZPnoSM->SetBinContent(bin,A2ZPnoSM);
		h1SM->SetBinContent(bin,A2SM);
		
		
		rKK = (IFA2KK+IBA2KK)/(IFA2SM+IBA2SM); // one incoming flavor (u-quark) and integrated over cosTheta
		rKKnoSM = (IFA2KKnoSM+IBA2KKnoSM)/(IFA2SM+IBA2SM); // one incoming flavor (u-quark) and integrated over cosTheta
		rZP = (IFA2ZP+IBA2ZP)/(IFA2SM+IBA2SM); // one incoming flavor (u-quark) and integrated over cosTheta
		rZPnoSM = (IFA2ZPnoSM+IBA2ZPnoSM)/(IFA2SM+IBA2SM); // one incoming flavor (u-quark) and integrated over cosTheta
		// double cosTheta = 0.;
		// rKK = weightKK(cosTheta,s,idIn,idOut); // one incoming flavor (u-quark) in a given cosTheta
		// rKKnoSM = weightKKnoSM(cosTheta,s,idIn,idOut); // one incoming flavor (u-quark) in a given cosTheta
		// rZP = weightZP(cosTheta,s,idIn,idOut); // one incoming flavor (u-quark) in a given cosTheta
		h1rKK->SetBinContent(bin,rKK);
		h1rKKnoSM->SetBinContent(bin,rKKnoSM);
		h1rZP->SetBinContent(bin,rZP);
		h1rZPnoSM->SetBinContent(bin,rZPnoSM);
		//_INFO("rKK="+_s(rKK)+", rZP="+_s(rZP));
		
		cout << "m=" << m << "\r" << flush;
		
		for(double cost=yMin ; cost<=yMax ; cost+=dy)
		{
			A2KK = hA2KK(cost,s,idIn,idOut);
			A2KKnoSM = hA2KKnoSM(cost,s,idIn,idOut);
			A2ZP = hA2ZP(cost,s,idIn,idOut);
			A2ZPnoSM = hA2ZPnoSM(cost,s,idIn,idOut);
			A2SM = hA2SM(cost,s,idIn,idOut);
			Int_t binxy = h2KK->FindBin(m,cost);
			h2KK->SetBinContent(binxy,A2KK);
			h2KKnoSM->SetBinContent(binxy,A2KKnoSM);
			h2ZP->SetBinContent(binxy,A2ZP);
			h2ZPnoSM->SetBinContent(binxy,A2ZPnoSM);
			h2SM->SetBinContent(binxy,A2SM);
			
			rKK = weightKK(cost,s,idIn,idOut); // one incoming flavor (u-quark) in a given cosTheta
			rKKnoSM = weightKKnoSM(cost,s,idIn,idOut); // one incoming flavor (u-quark) in a given cosTheta
			rZP = weightZP(cost,s,idIn,idOut); // one incoming flavor (u-quark) in a given cosTheta
			rZPnoSM = weightZPnoSM(cost,s,idIn,idOut); // one incoming flavor (u-quark) in a given cosTheta
			h2rKK->SetBinContent(binxy,rKK);
			h2rKKnoSM->SetBinContent(binxy,rKKnoSM);
			h2rZP->SetBinContent(binxy,rZP);
			h2rZPnoSM->SetBinContent(binxy,rZPnoSM);
			
			wgtMaxZP = (wgtMaxZP>rZPnoSM) ? wgtMaxZP : rZPnoSM;
			wgtMaxKK = (wgtMaxKK>rKKnoSM) ? wgtMaxKK : rKKnoSM;
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
	h1KKnoSM->Draw("SAMES");
	h1ZP->Draw("SAMES");
	h1ZPnoSM->Draw("SAMES");
	saveas(cnv_1d,"plots/theory_mass");
	
	TCanvas* cnv_1dr = new TCanvas("c1dr","c1dr",600,400);
	cnv_1dr->SetLogy();
	cnv_1dr->cd();
	cnv_1dr->Draw();
	h1rKK->Draw();
	h1rKKnoSM->Draw("SAMES");
	h1rZP->Draw("SAMES");
	h1rZPnoSM->Draw("SAMES");
	saveas(cnv_1dr,"plots/theory_ratioVSmass");
	
	TCanvas* cnv_2dr = new TCanvas("c2dr","c2dr",600,1000);
	cnv_2dr->Divide(1,4);
	TVirtualPad* pad_2drKK = cnv_2dr->cd(4);
	TVirtualPad* pad_2drKKnoSM = cnv_2dr->cd(3);
	TVirtualPad* pad_2drZP = cnv_2dr->cd(2);
	TVirtualPad* pad_2drZPnoSM = cnv_2dr->cd(1);
	pad_2drKK->SetLogz();
	pad_2drKKnoSM->SetLogz();
	pad_2drZP->SetLogz();
	pad_2drZPnoSM->SetLogz();
	cnv_2dr->cd();
	cnv_2dr->Draw();
	pad_2drKK->cd();
	h2rKK->Draw("COLZ");
	pad_2drKKnoSM->cd();
	h2rKKnoSM->Draw("COLZ");
	pad_2drZP->cd();
	h2rZP->Draw("COLZ");
	pad_2drZPnoSM->cd();
	h2rZPnoSM->Draw("COLZ");
	saveas(cnv_2dr,"plots/theory_ratioVSmassVScost");
	
	TCanvas* cnv_2d = new TCanvas("c2d","c2d",600,1200);
	cnv_2d->Divide(1,5);
	TVirtualPad* pad_2dKK = cnv_2d->cd(5);
	TVirtualPad* pad_2dKKnoSM = cnv_2d->cd(4);
	TVirtualPad* pad_2dZP = cnv_2d->cd(3);
	TVirtualPad* pad_2dZPnoSM = cnv_2d->cd(2);
	TVirtualPad* pad_2dSM = cnv_2d->cd(1);
	pad_2dKK->SetLogz();
	pad_2dKKnoSM->SetLogz();
	pad_2dZP->SetLogz();
	pad_2dZPnoSM->SetLogz();
	pad_2dSM->SetLogz();
	cnv_2d->cd();
	cnv_2d->Draw();
	pad_2dKK->cd();
	h2KK->Draw("COLZ");
	pad_2dKKnoSM->cd();
	h2KKnoSM->Draw("COLZ");
	pad_2dZP->cd();
	h2ZP->Draw("COLZ");
	pad_2dZPnoSM->cd();
	h2ZPnoSM->Draw("COLZ");
	pad_2dSM->cd();
	h2SM->Draw("COLZ");
	saveas(cnv_2d,"plots/theory_massVScost");
	
	TCanvas* cnv_1dAsym = new TCanvas("c1dAsym","c1dAsym",600,400);
	cnv_1dAsym->cd();
	cnv_1dAsym->Draw();
	h1AsymSM->Draw();
	h1AsymZP->Draw("SAMES");
	h1AsymKK->Draw("SAMES");
	h1AsymKKnoSM->Draw("SAMES");
	saveas(cnv_1dAsym,"plots/theory_asymVSmass");
	
	TCanvas* cnv_1dw = new TCanvas("c1dw","c1dw",600,400);
	cnv_1dw->cd();
	cnv_1dw->Draw();
	h1wGKK->Draw();
	h1wZKK->Draw("SAMES");
	h1wZP->Draw("SAMES");
	saveas(cnv_1dw,"plots/theory_widthVSpolemass");
	
	_INFO("wgtMaxKK = "+_s(wgtMaxKK));
	_INFO("wgtMaxZP = "+_s(wgtMaxZP));
	
	//F f(1.,1.);
	//cout << "integrate: " << integrate(f,0.,+100.,1000) << endl;
}
