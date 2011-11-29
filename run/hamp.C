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
	style();

	/////////////////////
	setFermions(); //////
	/////////////////////
	
	double xMin = 5.;
	double xMax = 3005.;
	double dx   = 5.;
	Int_t  Nx   = (Int_t)((xMax-xMin)/dx);
	
	double yMin = -1.;
	double yMax = +1.;
	double dy   = 0.01;
	Int_t  Ny   = (Int_t)((yMax-yMin)/dy);

	TH1D* h1KK = new TH1D("h1KK","DY(black), 1 TeV Z'_{SSM}(blue) and 1 TeV KK(red);m_{#mu#mu} GeV;arbitrary scale", Nx,xMin,xMax);
	TH1D* h1ZP = new TH1D("h1ZP","DY(black), 1 TeV Z'_{SSM}(blue) and 1 TeV KK(red);m_{#mu#mu} GeV;arbitrary scale", Nx,xMin,xMax);
	TH1D* h1SM = new TH1D("h1SM","DY(black), 1 TeV Z'_{SSM}(blue) and 1 TeV KK(red);m_{#mu#mu} GeV;arbitrary scale", Nx,xMin,xMax);
	h1SM->SetLineColor(kBlack);
	h1SM->SetLineStyle(1);
	h1ZP->SetLineColor(kBlue);
	h1ZP->SetLineStyle(3);
	h1KK->SetLineColor(kRed);
	h1KK->SetLineStyle(5);
	
	TH1D* h1AsymKK = new TH1D("h1AsymKK","DY(black), 1 TeV Z'_{SSM}(blue) and 1 TeV KK(red);m_{#mu#mu} GeV;A_{fb}", Nx,xMin,xMax);
	TH1D* h1AsymZP = new TH1D("h1AsymZP","DY(black), 1 TeV Z'_{SSM}(blue) and 1 TeV KK(red);m_{#mu#mu} GeV;A_{fb}", Nx,xMin,xMax);
	TH1D* h1AsymSM = new TH1D("h1AsymSM","DY(black), 1 TeV Z'_{SSM}(blue) and 1 TeV KK(red);m_{#mu#mu} GeV;A_{fb}", Nx,xMin,xMax);
	h1AsymSM->SetLineColor(kBlack);
	h1AsymSM->SetLineStyle(1);
	h1AsymZP->SetLineColor(kBlue);
	h1AsymZP->SetLineStyle(3);
	h1AsymKK->SetLineColor(kRed);
	h1AsymKK->SetLineStyle(5);
	
	TH2D* h2KK = new TH2D("h2KK","1 TeV KK;m_{#mu#mu} GeV;cos#theta*;arbitrary scale", Nx,xMin,xMax, Ny,yMin,yMax);
	TH2D* h2ZP = new TH2D("h2ZP","1 TeV Z'_{SSM};m_{#mu#mu} GeV;cos#theta*;arbitrary scale", Nx,xMin,xMax, Ny,yMin,yMax);
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
		
		double s  = m*m;
		unsigned int idOut = s2f["muon"]->id;
		
		ISM fSM(s,idOut);
		IZP fZP(s,idOut);
		IKK fKK(s,idOut);
		
		IFA2KK = integrate(fKK,0.,+1.,1000);
		IFA2ZP = integrate(fZP,0.,+1.,1000);
		IFA2SM = integrate(fSM,0.,+1.,1000);
		IBA2KK = integrate(fKK,-1.,0.,1000);
		IBA2ZP = integrate(fZP,-1.,0.,1000);
		IBA2SM = integrate(fSM,-1.,0.,1000);
		
		AfbSM = (IFA2SM-IBA2SM)/(IFA2SM+IBA2SM);
		AfbZP = (IFA2ZP-IBA2ZP)/(IFA2ZP+IBA2ZP);
		AfbKK = (IFA2KK-IBA2KK)/(IFA2KK-IBA2KK);
		
		Int_t bin = h1AsymKK->FindBin(m);
		h1AsymKK->SetBinContent(bin,AfbKK);
		h1AsymZP->SetBinContent(bin,AfbZP);
		h1AsymSM->SetBinContent(bin,AfbSM);
		
		/////////////////////////////////////////////////////////////////////
		
		// double cosTheta = 0.;
		// A2KK = hA2KK(s,cosTheta,s2f["dwn"]->id,s2f["muon"]->id); // one incoming flavor (d-quark) in a given cosTheta
		// A2ZP = hA2ZP(s,cosTheta,s2f["dwn"]->id,s2f["muon"]->id); // one incoming flavor (d-quark) in a given cosTheta
		// A2SK = hA2SM(s,cosTheta,s2f["dwn"]->id,s2f["muon"]->id); // one incoming flavor (d-quark) in a given cosTheta
		// double cosTheta = 0.;
		// A2KK = hA2KKsumQ(cosTheta,s,idOut); // sum the incoming flavors in a given cosTheta
		// A2ZP = hA2ZPsumQ(cosTheta,s,idOut); // sum the incoming flavors in a given cosTheta
		// A2SM = hA2SMsumQ(cosTheta,s,idOut); // sum the incoming flavors in a given cosTheta
		// 
		A2KK = IFA2KK+IBA2KK; // sum the incoming flavors and integrate over cosTheta
		A2ZP = IFA2ZP+IBA2ZP; // sum the incoming flavors and integrate over cosTheta
		A2SM = IFA2SM+IBA2SM; // sum the incoming flavors and integrate over cosTheta
		
		
		bin = h1KK->FindBin(m);
		h1KK->SetBinContent(bin,A2KK);
		h1ZP->SetBinContent(bin,A2ZP);
		h1SM->SetBinContent(bin,A2SM);
		cout << "m=" << m << "\r" << flush;
		
		for(double cost=yMin ; cost<=yMax ; cost+=dy)
		{
			A2KK = hA2KKsumQ(cost,s,idOut);
			A2ZP = hA2ZPsumQ(cost,s,idOut);
			A2SM = hA2SMsumQ(cost,s,idOut);
			Int_t binxy = h2KK->FindBin(m,cost);
			h2KK->SetBinContent(binxy,A2KK);
			h2ZP->SetBinContent(binxy,A2ZP);
			h2SM->SetBinContent(binxy,A2SM);
		}
	}
	
	TCanvas* cnv_1d = new TCanvas("c1d","c1d",600,400);
	cnv_1d->SetLogy();
	cnv_1d->cd();
	cnv_1d->Draw();
	h1SM->Draw();
	h1KK->Draw("SAMES");
	h1ZP->Draw("SAMES");
	saveas(cnv_1d,"plots/theory_mass");
	// cnv_1d->SaveAs("plots/theory_mass.png");
	// cnv_1d->SaveAs("plots/theory_mass.eps");
	// cnv_1d->SaveAs("plots/theory_mass.C");
	// cnv_1d->SaveAs("plots/theory_mass.root");
	
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
	// cnv_2d->SaveAs("plots/theory_massVScost.png");
	// cnv_2d->SaveAs("plots/theory_massVScost.eps");
	// cnv_2d->SaveAs("plots/theory_massVScost.C");
	// cnv_2d->SaveAs("plots/theory_massVScost.root");
	
	TCanvas* cnv_1dAsym = new TCanvas("c1dAsym","c1dAsym",600,400);
	cnv_1dAsym->cd();
	cnv_1dAsym->Draw();
	h1AsymSM->Draw();
	h1AsymZP->Draw("SAMES");
	h1AsymKK->Draw("SAMES");
	saveas(cnv_1dAsym,"plots/theory_asymVSmass");
	// cnv_1dAsym->SaveAs("plots/theory_asymVSmass.png");
	// cnv_1dAsym->SaveAs("plots/theory_asymVSmass.eps");
	// cnv_1dAsym->SaveAs("plots/theory_asymVSmass.C");
	// cnv_1dAsym->SaveAs("plots/theory_asymVSmass.root");
	
	//F f(1.,1.);
	//cout << "integrate: " << integrate(f,0.,+100.,1000) << endl;
}
