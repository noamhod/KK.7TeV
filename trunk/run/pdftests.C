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
#include "../include/integrals.h"
#include "../include/lhapdf.h"

using namespace couplings;
using namespace width;
using namespace helicity;
using namespace kFactors;
using namespace lhapdf;

const unsigned int fstQrk = PDTDWN;
const unsigned int lstQrk = PDTTOP;

unsigned int qstate(unsigned int qrk)
{
	if(qrk==fstQrk-1) return 0;
	if(qrk==lstQrk-1) return 2;
	return 1;
}

void pdftests()
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
	
	///////////////////////////////////////////////////////////// 
	setpdfpath("/srv01/tau/hod/lhapdf_current/share/lhapdf"); ///
	initset("MRSTMCal",0,true); /////////////////////////////////
	/////////////////////////////////////////////////////////////
	
	TString mBSM = (TString)_s(mKK*GeV2TeV);
	
	// mass range
	double xMin = logofficialimassmin;//5.;
	double xMax = logofficialimassmax;//5005.;
	double dx   = 1.;
	Int_t  Nx   = (Int_t)((xMax-xMin)/dx);
	
	setLogBins(nlogofficialimassbins,logofficialimassmin,logofficialimassmax,logofficialimassbins);
	
	TH1D* hSumq = new TH1D("hSumq","DY with pdf;m_{#mu#mu} GeV;Events", nlogofficialimassbins,logofficialimassbins);
	vector<TH1D*> h;

	
	
	TLegend* leg = new TLegend(0.6627517,0.60,0.7919463,0.87,NULL,"brNDC");
	leg->SetFillStyle(4000); //will be transparent
	leg->SetFillColor(0);
	leg->SetTextFont(42);
	
	for(unsigned int q=(fstQrk-1) ; q<=(lstQrk-1) ; q++)
	{
		TString quark = qname(q+1);
	
		// h.push_back( new TH1D("h_"+quark,"DY with pdf;m_{#mu#mu} GeV;nb/GeV", Nx,xMin,xMax) );
		h.push_back( new TH1D("h_"+quark,"DY with pdf;m_{#mu#mu} GeV;nb/GeV", nlogofficialimassbins,logofficialimassbins) );
		h[q]->SetLineColor(kBlack+q);
		leg->AddEntry(h[q],quark,"l");
		
		for(double m=xMin ; m<=xMax ; m+=dx)
		{
			Int_t bin = 0;
			double s  = m*m;
			double s2  = s*s;
			unsigned int idOut = s2f["muon"]->id;
			unsigned int idIn = q+1;
			unsigned int nsegments = 1000;
			
			template_hA2SM TcosThetaSM(s,idIn,idOut);
			double IcosTheta_A2SM = integrate(TcosThetaSM,-1.,+1.,nsegments);
			
			template_pdfintegrand TpdfSM(s,idIn);
			double yMax = rapidityMax(s);
			double Ipdf_A2SM = integrate(TpdfSM,-yMax,+yMax,nsegments);
			
			double fullA2SM = (2.*pi)*(alphaEM*alphaEM/(4.*s))*(s2/4.)*IcosTheta_A2SM*(2.*Ipdf_A2SM/3.);
			fullA2SM *= 2.*sqrt(s)*GeV2fb*luminosity; // Jacobian and units transformatons
			
			bin = h[q]->FindBin(m);
			h[q]->SetBinContent(bin,fullA2SM);
			
			cout << "m=" << m << "\r" << flush;
		}
	}
	
	for(unsigned int q=(fstQrk-1) ; q<=(lstQrk-1) ; q++) hSumq->Add(h[q]);
	
	bool dologx = true;
	bool dology = true;
	TString path = "";
	TCanvas* cnv = new TCanvas("c","c",600,400);
	if(dologx) cnv->SetLogx();
	if(dology) cnv->SetLogy();
	cnv->cd();
	cnv->Draw();
	/*
	setMinMax(h,dology);
	if(dologx) h[0]->GetXaxis()->SetMoreLogLabels();
	if(dologx) h[0]->GetXaxis()->SetNoExponent();
	h[0]->Draw();
	for(unsigned int q=(fstQrk-1) ; q<=(lstQrk-1) ; q++) h[q]->Draw("SAMES");
	leg->Draw("SAMES");
	*/
	if(dologx) hSumq->GetXaxis()->SetMoreLogLabels();
	if(dologx) hSumq->GetXaxis()->SetNoExponent();
	hSumq->Draw();
	saveas(cnv,"plots/theory_mass_pdf");
}
