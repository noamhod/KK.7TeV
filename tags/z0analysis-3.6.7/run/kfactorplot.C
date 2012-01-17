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

void kfactorplot()
{
	msglvl[DBG] = SILENT;
	msglvl[INF] = VISUAL;
	msglvl[WRN] = VISUAL;
	msglvl[ERR] = VISUAL;
	msglvl[FAT] = VISUAL;

	style();
	
	// mass range
	double xMin = 0.;
	double xMax = 6000.;
	double dx   = 1.;
	Int_t  Nx   = (Int_t)((xMax-xMin)/dx);
	
	TLegend* leg = new TLegend(0.55,0.70,0.90,0.8,NULL,"brNDC");
	leg->SetFillStyle(4000); //will be transparent
	leg->SetFillColor(0);
	leg->SetTextFont(42);
	
	TH1D* h1EW_NNLOvLOs   = new TH1D("h1EW_NNLOvLOs","QCD and EW parametrized k-factors;m_{#mu#mu} GeV;k-factor", Nx,xMin,xMax);
	TH1D* h1QCD_NNLOvLOss = new TH1D("h1QCD_NNLOvLOss","QCD and EW parametrized k-factors;m_{#mu#mu} GeV;k-factor", Nx,xMin,xMax);
	
	h1EW_NNLOvLOs->SetLineColor(kBlue);
	h1EW_NNLOvLOs->SetLineStyle(1);
	leg->AddEntry(h1EW_NNLOvLOs,"EW NNLO/LO*","l");
	h1QCD_NNLOvLOss->SetLineColor(kRed);
	h1QCD_NNLOvLOss->SetLineStyle(1);
	leg->AddEntry(h1QCD_NNLOvLOss,"QCD NNLO/LO**","l");

	
	for(double m=xMin ; m<=xMax ; m+=dx)
	{	
		double EW_NNLOvLOs   = ElectroWeak(m);
		double QCD_NNLOvLOss = QCD(m,"NNLO/LO**");
		
		if(isnaninf(EW_NNLOvLOs))  { _ERROR("EW NNLO/LO* is nan/inf."); }
		if(isnaninf(QCD_NNLOvLOss)) { _ERROR("QCD NNLO/LO* is nan/inf."); }
		
		if(isnaninf(sqrt(EW_NNLOvLOs)))  { _ERROR("sqrt EW NNLO/LO* is nan/inf -> mass="+_s(m)+", kF="+_s(EW_NNLOvLOs)+", sqrt(kF)="+_s(sqrt(EW_NNLOvLOs))); }
		if(isnaninf(sqrt(QCD_NNLOvLOss))) { _ERROR("sqrt QCD NNLO/LO* is nan/inf -> mass="+_s(m)+", kF="+_s(QCD_NNLOvLOss)+", sqrt(kF)="+_s(sqrt(QCD_NNLOvLOss))); }
		
		//_FATAL("test");
		
		Int_t bin = h1EW_NNLOvLOs->FindBin(m);
		
		h1EW_NNLOvLOs->SetBinContent(bin,EW_NNLOvLOs);
		h1QCD_NNLOvLOss->SetBinContent(bin,QCD_NNLOvLOss);
	}
	
	double max = -1.e10;
	max = (max>h1EW_NNLOvLOs->GetMaximum())  ? max : h1EW_NNLOvLOs->GetMaximum();
	max = (max>h1QCD_NNLOvLOss->GetMaximum()) ? max : h1EW_NNLOvLOs->GetMaximum();
	
	double min = +1.e10;
	min = (min<h1EW_NNLOvLOs->GetMinimum())  ? min : h1EW_NNLOvLOs->GetMinimum();
	min = (min<h1QCD_NNLOvLOss->GetMinimum()) ? min : h1EW_NNLOvLOs->GetMinimum();
	
	// TLine* line = new TLine(xMin,0.,xMax,0.);
	// line->SetLineColor(kBlack);
	// line->SetLineStyle(3);
	// line->SetLineWidth(1);
	
	TCanvas* cnv = new TCanvas("c","c",600,400);
	// cnv->SetLogx();
	// cnv->SetLogy();
	cnv->SetTicks(1,1);
	cnv->cd();
	cnv->Draw();
	h1EW_NNLOvLOs->SetMaximum(max*1.5);
	h1EW_NNLOvLOs->SetMinimum(0.);
	h1EW_NNLOvLOs->Draw();
	h1QCD_NNLOvLOss->Draw("SAMES");
	// line->Draw("SAMES");
	leg->Draw("SAMES");
	saveas(cnv,"plots/kfactors");
}
