#include "include/include/rawStd.h"
#include "include/include/rawROOT.h"
#include "include/include/enums.h"
#include "include/include/style.h"
#include "include/include/logs.h"
#include "include/include/bins.h"
#include "include/include/histos.h"
#include "include/include/fkinematics.h"
#include "include/include/units.h"
#include "include/include/couplings.h"
#include "include/include/width.h"
#include "include/include/helicity.h"
#include "include/include/kFactors.h"

using namespace couplings;
using namespace width;
using namespace helicity;
using namespace kFactors;


double EWkFactorEle(Double_t *x, Double_t *par)
{
  double mass = x[0];

  // Valid up to 3 TeV
  double kF = 1.;
  if (93.09 < mass && mass <= 250)  kF *= 0.841 + 0.00258*mass - 1.08e-05*mass*mass + 1.54e-08*mass*mass*mass;
  else if (250 < mass && mass <= 1750)  kF *= 1.067 - 6.34e-05*mass;
  else if (1750 < mass)  kF *= 0.873 + 0.000183*mass - 7.97e-08*mass*mass;

  return kF;
}

double EWkFactorMu(Double_t *x, Double_t *par)
{
  double mass = x[0];

  // Valid up to 3 TeV
  double kF = 1.;
  if (96.65 < mass && mass <= 250)  kF *= 0.852 + 0.00233*mass - 0.953e-05*mass*mass + 1.31e-08*mass*mass*mass;
  else if (250 < mass && mass <= 1750)  kF *= 1.060 - 6.09e-05*mass;
  else if (1750 < mass)  kF *= 0.931 + 0.000114*mass - 5.71e-08*mass*mass;

  return kF;
}



void kf()
{

	style();

	setLogBins(nlogofficialimassbins,logofficialimassmin,logofficialimassmax,logofficialimassbins);

	TF1 *f1 = new TF1("muon",EWkFactorMu,0,3000,0);
	TF1 *f2 = new TF1("electron",EWkFactorEle,0,3000,0);

	TLine* l = new TLine(0,0,3000,0);


	setFermions(); ////////
	setkFactors(false); ///

	double xMin = 5.;
	double xMax = 3005.;
	double dx   = 5.;
	Int_t  Nx   = (Int_t)((xMax-xMin)/dx);

	double yMin = -1.;
	double yMax = +1.;
	double dy   = 0.01;
	Int_t  Ny   = (Int_t)((yMax-yMin)/dy);

	setKKmass(5090.);
	setZPmass(5090.);

	TH2D* h2dKK = new TH2D("dKK","5.09 TeV KK;m_{ll} GeV;cos#theta*;ME^{2}_{BSM}/ME^{2}_{DY}", nlogofficialimassbins,logofficialimassbins, Ny,yMin,yMax);
	TH2D* h2uKK = new TH2D("uKK","5.09 TeV KK;m_{ll} GeV;cos#theta*;ME^{2}_{BSM}/ME^{2}_{DY}", nlogofficialimassbins,logofficialimassbins, Ny,yMin,yMax);
	TH2D* h2dZP = new TH2D("dZP","5.09 TeV KK;m_{ll} GeV;cos#theta*;ME^{2}_{BSM}/ME^{2}_{DY}", nlogofficialimassbins,logofficialimassbins, Ny,yMin,yMax);
	TH2D* h2uZP = new TH2D("uZP","5.09 TeV KK;m_{ll} GeV;cos#theta*;ME^{2}_{BSM}/ME^{2}_{DY}", nlogofficialimassbins,logofficialimassbins, Ny,yMin,yMax);
	

	double dKK = 0.;
	double uKK = 0.;
	double dZP = 0.;
	double uZP = 0.;

	unsigned int idl = 11;

	//for(double m=xMin ; m<=xMax ; m+=dx)
	for(int x=1 ; x<=nlogofficialimassbins ; x++)
	{
		double m = h2dZP->GetXaxis()->GetBinCenter(x);

		double s = m*m;
		for(double cost=yMin ; cost<=yMax ; cost+=dy)
		{

			double dKK = 0.;
        		double uKK = 0.;
        		double dZP = 0.;
		        double uZP = 0.;

			dKK = weightKK(cost,s,1,idl);
			uKK = weightKK(cost,s,2,idl);
			dZP = weightZP(cost,s,1,idl);
			uZP = weightZP(cost,s,2,idl);

			dKK += (idl==13) ? (f1->Eval(m)-1) : (f2->Eval(m)-1);
			uKK += (idl==13) ? (f1->Eval(m)-1) : (f2->Eval(m)-1);
			dZP += (idl==13) ? (f1->Eval(m)-1) : (f2->Eval(m)-1);
			uZP += (idl==13) ? (f1->Eval(m)-1) : (f2->Eval(m)-1);

			Int_t bin = h2dKK->FindBin(m,cost);

			h2dKK->SetBinContent(bin,dKK);
			h2uKK->SetBinContent(bin,uKK);
			h2dZP->SetBinContent(bin,dZP);
			h2uZP->SetBinContent(bin,uZP);
		}
	}

	TCanvas* c1 = new TCanvas("c1","c1",1000,1000);
	c1->Divide(2,2);
	TVirtualPad* p1=c1->cd(1);
	TVirtualPad* p2=c1->cd(2);
	TVirtualPad* p3=c1->cd(3);
	TVirtualPad* p4=c1->cd(4);
	p1->SetLogx();
	p2->SetLogx();
	p3->SetLogx();
	p4->SetLogx();
	c1->cd();
        c1->Draw();

	p1->cd();
	h2dKK->GetXaxis()->SetMoreLogLabels();
	h2dKK->GetXaxis()->SetNoExponent();
	h2dKK->Draw("SURF1");
	p2->cd();
	h2uKK->GetXaxis()->SetMoreLogLabels();
        h2uKK->GetXaxis()->SetNoExponent();
        h2uKK->Draw("SURF1");
	p3->cd();
	h2dZP->GetXaxis()->SetMoreLogLabels();
        h2dZP->GetXaxis()->SetNoExponent();
        h2dZP->Draw("SURF1");
	p4->cd();
	h2uZP->GetXaxis()->SetMoreLogLabels();
        h2uZP->GetXaxis()->SetNoExponent();
        h2uZP->Draw("SURF1");

	c1->SaveAs("weights.png");
	c1->SaveAs("weights.root");




	TCanvas* c = new TCanvas("c","c",600,400);
	c->SetGridy();
	c->cd();
	c->Draw();

	f1->SetLineColor(kRed);
	f2->SetLineColor(kBlue);

	f1->Draw();
	f2->Draw("SAMES");
	l->Draw("SAMES");
	
	c->SaveAs("kfactors.png");
}
