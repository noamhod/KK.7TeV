#include "../include/rawStd.h"
#include "../include/rawROOT.h"
#include "../include/enums.h"
#include "../include/logs.h"
#include "../include/style.h"
//#include "../include/bins.h"
//#include "../include/histos.h"
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
	
	TCanvas* cnv_1d = new TCanvas("c1d","c1d",600,400);
	cnv_1d->SetLogy();
	TCanvas* cnv_2d = new TCanvas("c2d","c2d",600,900);
	cnv_2d->Divide(1,2);
	TVirtualPad* pad_2dKK = cnv_2d->cd(1);
	TVirtualPad* pad_2dZP = cnv_2d->cd(2);
	pad_2dKK->SetLogz();
	pad_2dZP->SetLogz();

	double xMin = 60.;
	double xMax = 3000.;
	double dx   = 10.;
	Int_t  Nx   = (Int_t)((xMax-xMin)/dx);
	
	double yMin = -1.;
	double yMax = +1.;
	double dy   = 0.05;
	Int_t  Ny   = (Int_t)((yMax-yMin)/dy);

	double cosTheta = 0.;

	TH1D* h1KK = new TH1D("h1KK","", Nx,xMin,xMax);
	TH1D* h1ZP = new TH1D("h1ZP","", Nx,xMin,xMax);
	TH1D* h1SM = new TH1D("h1SM","", Nx,xMin,xMax);
	h1SM->SetLineColor(kBlack);
	h1SM->SetLineStyle(1);
	h1ZP->SetLineColor(kBlue);
	h1ZP->SetLineStyle(3);
	h1KK->SetLineColor(kRed);
	h1KK->SetLineStyle(5);
	
	TH2D* h2KK = new TH2D("h2KK","", Nx,xMin,xMax, Ny,yMin,yMax);
	TH2D* h2ZP = new TH2D("h2ZP","", Nx,xMin,xMax, Ny,yMin,yMax);
	
	for(double m=xMin ; m<=xMax ; m+=dx)
	{
		double A2KK = 0.;
		double A2ZP = 0.;
		double A2SM = 0.;
		double s  = m*m;
		
		// A2 = hA2KK(s,cosTheta,s2f["dwn"]->id,s2f["muon"]->id); // one incoming flavor (d-quark) in a given cosTheta
		A2KK = hA2KKsumQ(s,cosTheta,s2f["muon"]->id);               // sum the incoming flavors in a given cosTheta
		A2ZP = hA2ZPsumQ(s,cosTheta,s2f["muon"]->id);               // sum the incoming flavors in a given cosTheta
		A2SM = hA2SMsumQ(s,cosTheta,s2f["muon"]->id);               // sum the incoming flavors in a given cosTheta
		// A2 = hA2KKtot(double s, unsigned int idOut)            // sum the incoming flavors and integrate over cosTheta
		
		Int_t bin = h1KK->FindBin(m);
		h1KK->SetBinContent(bin,A2KK);
		h1ZP->SetBinContent(bin,A2ZP);
		h1SM->SetBinContent(bin,A2SM);
		cout << "m=" << m << "\r" << flush;
		
		for(double cost=yMin ; cost<=yMax ; cost+=dy)
		{
			A2KK = hA2KKsumQ(s,cost,s2f["muon"]->id);
			A2ZP = hA2ZPsumQ(s,cost,s2f["muon"]->id);
			Int_t binxy = h2KK->FindBin(m,cost);
			h2KK->SetBinContent(binxy,A2KK);
			h2ZP->SetBinContent(binxy,A2ZP);
		}
	}
	
	cnv_1d->cd();
	cnv_1d->Draw();
	h1SM->Draw();
	h1KK->Draw("SAMES");
	h1ZP->Draw("SAMES");
	
	cnv_2d->cd();
	cnv_2d->Draw();
	pad_2dKK->cd();
	h2KK->Draw("COLZ");
	pad_2dZP->cd();
	h2ZP->Draw("COLZ");
}
