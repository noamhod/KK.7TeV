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

void simpleplot_withpdfs(double Xmass, TString chan="mm", double gRe=1., double gIm=0.)
{
	msglvl[DBG] = SILENT;
	msglvl[INF] = VISUAL;
	msglvl[WRN] = VISUAL;
	msglvl[ERR] = VISUAL;
	msglvl[FAT] = VISUAL;

	style();
	bool dologx = false;
	bool dology = true;
	
	TString sXmass  = (TString)_s(Xmass);
	TString channel = (chan=="mm") ? "#mu#mu" : "ee";
	
	/////////////////////////
	setFermions(); //////////
	setFixedWidth(false); ///
	resetKKmass();///////////
	resetZPmass(); //////////
	resetfgZP(); ////////////
	resetfgGKK(); ///////////
	resetfgZKK(); ///////////
	/////////////////////////
	setKKmass(Xmass); /////// set the KK mass
	setZPmass(Xmass); /////// set the Z' mass
	setFgZP(gRe,gIm); /////// set the Z' couplings scalse
	setFgGKK(gRe,gIm); ////// set the gamma KK couplings scalse
	setFgZKK(gRe,gIm); ////// set the Z KK couplings scalse
	/////////////////////////
	
	///////////////////////////////////////////////////////////// 
	setpdfpath("/srv01/tau/hod/lhapdf_current/share/lhapdf"); ///
	initset("MRSTMCal",0,true); /////////////////////////////////
	/////////////////////////////////////////////////////////////
	
	setLogBins(nlogofficialimassbins,logofficialimassmin,logofficialimassmax,logofficialimassbins);
	setLinBins(nlinmassbins,linmassmin,linmassmax,linmassbins);
	
	TLegend* leg_sigma = new TLegend(0.55,0.63,0.8,0.85,NULL,"brNDC");
	leg_sigma->SetFillStyle(4000); //will be transparent
	leg_sigma->SetFillColor(0);
	leg_sigma->SetTextFont(42);
	
	TLegend* leg_quarks = new TLegend(0.6627517,0.60,0.7919463,0.87,NULL,"brNDC");
	leg_quarks->SetFillStyle(4000); //will be transparent
	leg_quarks->SetFillColor(0);
	leg_quarks->SetTextFont(42);
	
	TH1D* hSumqDY = new TH1D("hSumqDY",";m_{"+channel+"} GeV;#frac{d#sigma}{dm_{"+channel+"}} #frac{fb}{GeV}", nlinmassbins,linmassbins  /*nlogofficialimassbins,logofficialimassbins*/);
	if(dologx) hSumqDY->GetXaxis()->SetMoreLogLabels();
	if(dologx) hSumqDY->GetXaxis()->SetNoExponent();
	hSumqDY->SetLineColor(kBlack);
	hSumqDY->SetFillColor(kAzure-9);
	leg_sigma->AddEntry(hSumqDY,"DY","f");
	
	TH1D* hSumqZP = new TH1D("hSumqZP",";m_{"+channel+"} GeV;#frac{d#sigma}{dm_{"+channel+"}} #frac{fb}{GeV}", nlinmassbins,linmassbins  /*nlogofficialimassbins,logofficialimassbins*/);
	if(dologx) hSumqZP->GetXaxis()->SetMoreLogLabels();
	if(dologx) hSumqZP->GetXaxis()->SetNoExponent();
	hSumqZP->SetLineColor(kRed+2);
	hSumqZP->SetLineWidth(2);
	leg_sigma->AddEntry(hSumqZP,"Z'_{SSM} at "+sXmass+" GeV","F");
	
	TH1D* hSumqKK = new TH1D("hSumqKK",";m_{"+channel+"} GeV;#frac{d#sigma}{dm_{"+channel+"}} #frac{fb}{GeV}", nlinmassbins,linmassbins  /*nlogofficialimassbins,logofficialimassbins*/);
	if(dologx) hSumqKK->GetXaxis()->SetMoreLogLabels();
	if(dologx) hSumqKK->GetXaxis()->SetNoExponent();
	hSumqKK->SetLineColor(kGreen+2);
	hSumqKK->SetLineWidth(2);
	leg_sigma->AddEntry(hSumqKK,"KK at "+sXmass+" GeV","F");
	
	///////////////////////////////
	TString xTitle = "m_{"+channel+"} GeV";
	TString yTitle = "#frac{d#sigma}{dm_{"+channel+"}} #frac{fb}{GeV}";
	
	TGraph* gSumqDY = new TGraph();
	TGraph* gSumqZP = new TGraph();
	TGraph* gSumqKK = new TGraph();
	
	vector<TH1D*> hDY;
	vector<TH1D*> hZP;
	vector<TH1D*> hKK;
	
	for(unsigned int q=(fstQrk-1) ; q<=(lstQrk-1) ; q++)
	{
		TString quark = qname(q+1);
		
		hDY.push_back( new TH1D("hDY_"+quark,"DY with pdf;m_{#mu#mu} GeV;fb/GeV", nlinmassbins,linmassbins  /*nlogofficialimassbins,logofficialimassbins*/) );
		hDY[q]->SetLineColor(kBlack+q);
		leg_quarks->AddEntry(hDY[q],"DY "+quark,"l");
		
		hZP.push_back( new TH1D("hZP_"+quark,"ZP with pdf;m_{#mu#mu} GeV;fb/GeV", nlinmassbins,linmassbins  /*nlogofficialimassbins,logofficialimassbins*/) );
		hZP[q]->SetLineColor(kBlack+q+6);
		leg_quarks->AddEntry(hZP[q],"Z' "+quark,"l");
		
		hKK.push_back( new TH1D("hKK_"+quark,"KK with pdf;m_{#mu#mu} GeV;fb/GeV", nlinmassbins,linmassbins  /*nlogofficialimassbins,logofficialimassbins*/) );
		hKK[q]->SetLineColor(kBlack+q+12);
		leg_quarks->AddEntry(hKK[q],"KK "+quark,"l");
		
		for(Int_t bin=1 ; bin<=hSumqDY->GetNbinsX() ; bin++)
		{
			double m  = hSumqDY->GetBinCenter(bin);
			double dm = hSumqDY->GetBinWidth(bin);
			double s  = m*m;
			double s2 = s*s;
			unsigned int idOut = (chan=="mm") ? s2f["muon"]->id : s2f["electron"]->id;
			unsigned int idIn = q+1;
			unsigned int nsegments = 10000;
			
			template_hA2SM TcosThetaSM(s,idIn,idOut);
			double IcosTheta_A2SM = integrate(TcosThetaSM,-1.,+1.,nsegments);
			
			template_hA2ZP TcosThetaZP(s,idIn,idOut);
			double IcosTheta_A2ZP = integrate(TcosThetaZP,-1.,+1.,nsegments);
			
			template_hA2KK TcosThetaKK(s,idIn,idOut);
			double IcosTheta_A2KK = integrate(TcosThetaKK,-1.,+1.,nsegments);
			
			////////////////////////////////////
			double yMax = rapidityMax(s); //////
			////////////////////////////////////
			
			template_pdfintegrand TpdfSM(s,idIn);
			double Ipdf_A2SM = integrate(TpdfSM,-yMax,+yMax,nsegments);
			double fullA2SM = (2.*pi)*(alphaEM*alphaEM/(4.*s))*(s2/4.)*IcosTheta_A2SM*(2.*Ipdf_A2SM/3.); // units of GeV^-4
			fullA2SM *= 2.*sqrt(s); // Jacobian transformation -> units of GeV^-3
			fullA2SM *= GeV2fb;     // units of fb/GeV
			
			template_pdfintegrand TpdfZP(s,idIn);
			double Ipdf_A2ZP = integrate(TpdfZP,-yMax,+yMax,nsegments);
			double fullA2ZP = (2.*pi)*(alphaEM*alphaEM/(4.*s))*(s2/4.)*IcosTheta_A2ZP*(2.*Ipdf_A2ZP/3.); // units of GeV^-4
			fullA2ZP *= 2.*sqrt(s); // Jacobian transformation -> units of GeV^-3
			fullA2ZP *= GeV2fb;     // units of fb/GeV
			
			template_pdfintegrand TpdfKK(s,idIn);
			double Ipdf_A2KK = integrate(TpdfKK,-yMax,+yMax,nsegments);
			double fullA2KK = (2.*pi)*(alphaEM*alphaEM/(4.*s))*(s2/4.)*IcosTheta_A2KK*(2.*Ipdf_A2KK/3.); // units of GeV^-4
			fullA2KK *= 2.*sqrt(s); // Jacobian transformation -> units of GeV^-3
			fullA2KK *= GeV2fb;     // units of fb/GeV
			
			hDY[q]->SetBinContent(bin,fullA2SM);
			hZP[q]->SetBinContent(bin,fullA2ZP);
			hKK[q]->SetBinContent(bin,fullA2KK);
			
			cout << "m=" << m << "\r" << flush;
		}
	}
	
	for(unsigned int q=(fstQrk-1) ; q<=(lstQrk-1) ; q++)
	{
		hSumqDY->Add(hDY[q]);
		hSumqZP->Add(hZP[q]);
		hSumqKK->Add(hKK[q]);
	}
	
	for(Int_t bin=1 ; bin<=hSumqDY->GetNbinsX() ; bin++)
	{
		gSumqDY->SetPoint(bin, hSumqDY->GetBinCenter(bin), hSumqDY->GetBinContent(bin));
		gSumqZP->SetPoint(bin, hSumqZP->GetBinCenter(bin), hSumqZP->GetBinContent(bin));
		gSumqKK->SetPoint(bin, hSumqKK->GetBinCenter(bin), hSumqKK->GetBinContent(bin));
	}
	
	
	gSumqDY->GetXaxis()->SetTitle(xTitle);
	gSumqDY->GetYaxis()->SetTitle(yTitle);
	if(dologx) gSumqDY->GetXaxis()->SetMoreLogLabels();
	if(dologx) gSumqDY->GetXaxis()->SetNoExponent();
	gSumqDY->SetLineColor(kBlack);
	gSumqDY->SetFillColor(kAzure-9);
	// leg_sigma->AddEntry(gSumqDY,"DY","f");
	
	gSumqZP->GetXaxis()->SetTitle(xTitle);
	gSumqZP->GetYaxis()->SetTitle(yTitle);
	if(dologx) gSumqZP->GetXaxis()->SetMoreLogLabels();
	if(dologx) gSumqZP->GetXaxis()->SetNoExponent();
	gSumqZP->SetLineColor(kRed+2);
	gSumqZP->SetLineWidth(2);
	// leg_sigma->AddEntry(gSumqZP,"Z'_{SSM} at "+sXmass+" GeV","F");
	
	gSumqKK->GetXaxis()->SetTitle(xTitle);
	gSumqKK->GetYaxis()->SetTitle(yTitle);
	if(dologx) gSumqKK->GetXaxis()->SetMoreLogLabels();
	if(dologx) gSumqKK->GetXaxis()->SetNoExponent();
	gSumqKK->SetLineColor(kGreen+2);
	gSumqKK->SetLineWidth(2);
	// leg_sigma->AddEntry(gSumqKK,"KK at "+sXmass+" GeV","F");
	
	
	
	TCanvas* cnv = new TCanvas("c","c",600,400);
	cnv->SetTicks(1,1);
	if(dologx) cnv->SetLogx();
	if(dology) cnv->SetLogy();
	cnv->cd();
	cnv->Draw();
	hSumqDY->Draw();
	hSumqZP->Draw("SAMES");
	hSumqKK->Draw("SAMES");
	// gSumqDY->Draw("C");
	// gSumqZP->Draw("CSAMES");
	// gSumqKK->Draw("CSAMES");
	leg_sigma->Draw("SAMES");
	saveas(cnv,"plots/theory_mass"+sXmass+"GeV_withpdf");
}
