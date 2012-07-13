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
#include "../src/AtlasStyle.C"

using namespace couplings;
using namespace width;
using namespace helicity;
using namespace kFactors;
using namespace lhapdf;

void atlstyle()
{
	gROOT->Reset();
	gROOT->ForceStyle();
	gROOT->LoadMacro("../src/AtlasStyle.C");
	SetAtlasStyle();
}

const unsigned int fstQrk = PDTDWN;
const unsigned int lstQrk = PDTTOP;

unsigned int qstate(unsigned int qrk)
{
	if(qrk==fstQrk-1) return 0;
	if(qrk==lstQrk-1) return 2;
	return 1;
}

/* void *handle(void *ptr)
{
	long nr = (long) ptr;

	// for (int i = 0; i < 10; i++)
	// {
		// TThread::Printf("Here I am loop index: %d , thread: %ld", i, nr);
		// gSystem->Sleep(1000);
	// }
	
	TThread::Printf("Here I am loop index: %d , thread: %ld", i, nr);
	
	return 0;
} */

void simpleplot_withpdfs(double Xmass, TString chan="mm", double gRe=1., double gIm=0.)
{
	msglvl[DBG] = SILENT;
	msglvl[INF] = VISUAL;
	msglvl[WRN] = VISUAL;
	msglvl[ERR] = VISUAL;
	msglvl[FAT] = VISUAL;

	TString styletype="atlas";
	if(styletype=="atlas") atlstyle();
	else                   style(); // noam's style
	
	bool dologx = true;//false;
	bool dology = true;
	bool dologz = true;
	
	TString sXmass  = (TString)_s(Xmass);
	TString channel = (chan=="mm") ? "#mu#mu" : "ee";
	
	TString E6model = "psi"; // "psi", "chi", "eta", "I"
	vector<TString> vE6models;
	vE6models.push_back("psi");
	vE6models.push_back("chi");
	vE6models.push_back("eta");
	// vE6models.push_back("I");
	
	vector<Int_t> vE6modelsLines;
	vE6modelsLines.push_back(1);
	vE6modelsLines.push_back(2);
	vE6modelsLines.push_back(3);
	// vE6modelsLines.push_back(3);
	
	////////////////////////////
	setFermions(); /////////////
	setFixedWidth(false); ////// !!! should be false
	setTTbarWidth(true); /////// !!! should be true
	setGZKKmode(BOTHGZ); ///////
	setThetaE6(E6model); ///////
	////////////////////////////
	resetKKmass(); /////////////
	resetZPmass(); /////////////
	resetfgZP(); ///////////////
	resetfgGKK(); //////////////
	resetfgZKK(); //////////////
	////////////////////////////
	setKKmass(Xmass); ////////// set the KK mass
	setZPmass(Xmass); ////////// set the Z' mass
	setFgZP(gRe,gIm); ////////// set the Z' couplings scalse
	setFgGKK(gRe,gIm); ///////// set the gamma KK couplings scalse
	setFgZKK(gRe,gIm); ///////// set the Z KK couplings scalse
	////////////////////////////
	
	///////////////////////////////////////////////////////////// 
	setpdfpath("/srv01/tau/hod/lhapdf_current/share/lhapdf"); ///
	initset("MRSTMCal",0,true); /////////////////////////////////
	/////////////////////////////////////////////////////////////
	
	setLogBins(nlogofficialimassbins,logofficialimassmin,logofficialimassmax,logofficialimassbins);
	setLogBins(nlogofficiallongimassbins,logofficiallongimassmin,logofficiallongimassmax,logofficiallongimassbins);
	setLinBins(nlinmassbins,linmassmin,linmassmax,linmassbins);
	setLogBins(nlogtheoryAFBimassbins, logtheoryAFBimassmin, logtheoryAFBimassmax, logtheoryAFBimassbins);
	setLogBins(nlogtheoryimassbins, logtheoryimassmin, logtheoryimassmax, logtheoryimassbins);
	
	
	_INFO("Width SSM = "+_s(wTotZP()/Xmass));
	setThetaE6("psi");
	_INFO("Width psi = "+_s(wTotE6()/Xmass));
	setThetaE6("chi");
	_INFO("Width chi = "+_s(wTotE6()/Xmass));
	setThetaE6("eta");
	_INFO("Width eta = "+_s(wTotE6()/Xmass));
	setThetaE6("I");
	_INFO("Width I   = "+_s(wTotE6()/Xmass));
	
	vector<TH1D*> h1Tmp;
	vector<TH2D*> h2Tmp;
	
	TLegend* leg_sigma = new TLegend(0.6459732,0.6612903,0.8959732,0.8817204,NULL,"brNDC");
	leg_sigma->SetFillStyle(4000); //will be transparent
	leg_sigma->SetFillColor(0);
	leg_sigma->SetTextFont(42);
	
	TLegend* leg_afb = new TLegend(0.6459732,0.2231183,0.8959732,0.4435484,NULL,"brNDC");
	leg_afb->SetFillStyle(4000); //will be transparent
	leg_afb->SetFillColor(0);
	leg_afb->SetTextFont(42);
	
	TLegend* leg_quarks = new TLegend(0.6627517,0.60,0.7919463,0.87,NULL,"brNDC");
	leg_quarks->SetFillStyle(4000); //will be transparent
	leg_quarks->SetFillColor(0);
	leg_quarks->SetTextFont(42);
	
	//////////////////////// 
	TH1D* h1SumqDY = new TH1D("h1SumqDY",";m_{"+channel+"} GeV;#frac{d#sigma}{dm_{"+channel+"}} in arbitrary scale", nlogtheoryimassbins,logtheoryimassbins /* nlogofficiallongimassbins,logofficiallongimassbins */  /*nlogofficialimassbins,logofficialimassbins*/  /* nlinmassbins,linmassbins */  );
	if(dologx) h1SumqDY->GetXaxis()->SetMoreLogLabels();
	if(dologx) h1SumqDY->GetXaxis()->SetNoExponent();
	h1SumqDY->SetLineColor(kAzure-9); // kBlack
	h1SumqDY->SetFillColor(kAzure-9);
	leg_sigma->AddEntry(h1SumqDY,"DY","f");
	
	TH1D* h1SumqZP = new TH1D("h1SumqZP",";m_{"+channel+"} GeV;#frac{d#sigma}{dm_{"+channel+"}} in arbitrary scale", nlogtheoryimassbins,logtheoryimassbins /* nlogofficiallongimassbins,logofficiallongimassbins */  /*nlogofficialimassbins,logofficialimassbins*/  /* nlinmassbins,linmassbins */ );
	if(dologx) h1SumqZP->GetXaxis()->SetMoreLogLabels();
	if(dologx) h1SumqZP->GetXaxis()->SetNoExponent();
	h1SumqZP->SetLineColor(kRed+2);
	h1SumqZP->SetLineWidth(1);
	leg_sigma->AddEntry(h1SumqZP,"Z'_{SSM} ("+sXmass+" GeV)","F");
	
	
	vector<TH1D*> h1SumqE6;
	for(unsigned int iE6=0 ; iE6<vE6models.size() ; iE6++)
	{
		h1SumqE6.push_back( new TH1D("h1SumqE6_"+vE6models[iE6],";m_{"+channel+"} GeV;#frac{d#sigma}{dm_{"+channel+"}} in arbitrary scale", nlogtheoryimassbins,logtheoryimassbins /* nlogofficiallongimassbins,logofficiallongimassbins */  /*nlogofficialimassbins,logofficialimassbins*/  /* nlinmassbins,linmassbins */ ));
		if(dologx) h1SumqE6[iE6]->GetXaxis()->SetMoreLogLabels();
		if(dologx) h1SumqE6[iE6]->GetXaxis()->SetNoExponent();
		h1SumqE6[iE6]->SetLineColor(kOrange+2);
		h1SumqE6[iE6]->SetLineWidth(1);
		h1SumqE6[iE6]->SetLineStyle(vE6modelsLines[iE6]);
		TString name = "Z'_{#"+vE6models[iE6]+"} ("+sXmass+" GeV)";
		if(vE6models[iE6]=="I") name = "Z'_{"+vE6models[iE6]+"} ("+sXmass+" GeV)";
		leg_sigma->AddEntry(h1SumqE6[iE6],name,"F");
	}
	
	TH1D* h1SumqKK = new TH1D("h1SumqKK",";m_{"+channel+"} GeV;#frac{d#sigma}{dm_{"+channel+"}} in arbitrary scale", nlogtheoryimassbins,logtheoryimassbins /* nlogofficiallongimassbins,logofficiallongimassbins */  /*nlogofficialimassbins,logofficialimassbins*/  /* nlinmassbins,linmassbins */ );
	if(dologx) h1SumqKK->GetXaxis()->SetMoreLogLabels();
	if(dologx) h1SumqKK->GetXaxis()->SetNoExponent();
	h1SumqKK->SetLineColor(kGreen+2);
	h1SumqKK->SetLineWidth(1);
	leg_sigma->AddEntry(h1SumqKK,"KK ("+sXmass+" GeV)","F");
	////////////////////////
	
	
	////////////////////////
	TH1D* h1fSumqDY = new TH1D("h1fSumqDY",";m_{"+channel+"} GeV;A_{fb}", nlogtheoryAFBimassbins,logtheoryAFBimassbins );
	TH1D* h1fSumqZP = new TH1D("h1fSumqZP",";m_{"+channel+"} GeV;A_{fb}", nlogtheoryAFBimassbins,logtheoryAFBimassbins );
	TH1D* h1fSumqKK = new TH1D("h1fSumqKK",";m_{"+channel+"} GeV;A_{fb}", nlogtheoryAFBimassbins,logtheoryAFBimassbins );
	
	TH1D* h1bSumqDY = new TH1D("h1bSumqDY",";m_{"+channel+"} GeV;A_{fb}", nlogtheoryAFBimassbins,logtheoryAFBimassbins );
	TH1D* h1bSumqZP = new TH1D("h1bSumqZP",";m_{"+channel+"} GeV;A_{fb}", nlogtheoryAFBimassbins,logtheoryAFBimassbins );
	TH1D* h1bSumqKK = new TH1D("h1bSumqKK",";m_{"+channel+"} GeV;A_{fb}", nlogtheoryAFBimassbins,logtheoryAFBimassbins );
	
	vector<TH1D*> h1fSumqE6;
	vector<TH1D*> h1bSumqE6;
	for(unsigned int iE6=0 ; iE6<vE6models.size() ; iE6++)
	{
		h1fSumqE6.push_back( new TH1D("h1fSumqE6_"+vE6models[iE6],";m_{"+channel+"} GeV;A_{fb}", nlogtheoryAFBimassbins,logtheoryAFBimassbins ));
		h1bSumqE6.push_back( new TH1D("h1bSumqE6_"+vE6models[iE6],";m_{"+channel+"} GeV;A_{fb}", nlogtheoryAFBimassbins,logtheoryAFBimassbins ));
	}
	
	TH1D* h1AfbSumqDY = new TH1D("h1AfbSumqDY",";m_{"+channel+"} GeV;A_{fb}", nlogtheoryAFBimassbins,logtheoryAFBimassbins  );
	if(dologx) h1AfbSumqDY->GetXaxis()->SetMoreLogLabels();
	if(dologx) h1AfbSumqDY->GetXaxis()->SetNoExponent();
	h1AfbSumqDY->SetLineColor(kAzure-9);
	h1AfbSumqDY->SetLineWidth(1);
	leg_afb->AddEntry(h1AfbSumqDY,"DY","f");
	
	TH1D* h1AfbSumqZP = new TH1D("h1AfbSumqZP",";m_{"+channel+"} GeV;A_{fb}", nlogtheoryAFBimassbins,logtheoryAFBimassbins );
	if(dologx) h1AfbSumqZP->GetXaxis()->SetMoreLogLabels();
	if(dologx) h1AfbSumqZP->GetXaxis()->SetNoExponent();
	h1AfbSumqZP->SetLineColor(kRed+2);
	h1AfbSumqZP->SetLineWidth(1);
	leg_afb->AddEntry(h1AfbSumqZP,"Z'_{SSM} ("+sXmass+" GeV)","F");
	
	vector<TH1D*> h1AfbSumqE6;
	for(unsigned int iE6=0 ; iE6<vE6models.size() ; iE6++)
	{
		h1AfbSumqE6.push_back( new TH1D("h1AfbSumqE6_"+vE6models[iE6],";m_{"+channel+"} GeV;A_{fb}", nlogtheoryAFBimassbins,logtheoryAFBimassbins ));
		if(dologx) h1AfbSumqE6[iE6]->GetXaxis()->SetMoreLogLabels();
		if(dologx) h1AfbSumqE6[iE6]->GetXaxis()->SetNoExponent();
		h1AfbSumqE6[iE6]->SetLineColor(kOrange+2);
		h1AfbSumqE6[iE6]->SetLineWidth(1);
		h1AfbSumqE6[iE6]->SetLineStyle(vE6modelsLines[iE6]);
		TString name = "Z'_{#"+vE6models[iE6]+"} ("+sXmass+" GeV)";
		if(vE6models[iE6]=="I") name = "Z'_{"+vE6models[iE6]+"} ("+sXmass+" GeV)";
		leg_afb->AddEntry(h1AfbSumqE6[iE6],name,"F");
	}
	
	TH1D* h1AfbSumqKK = new TH1D("h1AfbSumqKK",";m_{"+channel+"} GeV;A_{fb}", nlogtheoryAFBimassbins,logtheoryAFBimassbins );
	if(dologx) h1AfbSumqKK->GetXaxis()->SetMoreLogLabels();
	if(dologx) h1AfbSumqKK->GetXaxis()->SetNoExponent();
	h1AfbSumqKK->SetLineColor(kGreen+2);
	h1AfbSumqKK->SetLineWidth(1);
	//leg_afb->AddEntry(h1AfbSumqKK,"KK ("+sXmass+" GeV)","F");
	////////////////////////
	
	
	////////////////////////
	TH2D* h2SumqDY = new TH2D("h2SumqDY",";m_{"+channel+"} GeV;cos#theta*;#frac{d#sigma}{dm_{"+channel+"}} in arbitrary scale", nlogtheoryimassbins,logtheoryimassbins /* nlogofficiallongimassbins,logofficiallongimassbins */  /*nlogofficialimassbins,logofficialimassbins*/  /* nlinmassbins,linmassbins */,nFullCosThetaBins,minFullCosTheta,maxFullCosTheta );
	if(dologx) h2SumqDY->GetXaxis()->SetMoreLogLabels();
	if(dologx) h2SumqDY->GetXaxis()->SetNoExponent();
	
	TH2D* h2SumqZP = new TH2D("h2SumqZP",";m_{"+channel+"} GeV;cos#theta*;#frac{d#sigma}{dm_{"+channel+"}} in arbitrary scale", nlogtheoryimassbins,logtheoryimassbins /* nlogofficiallongimassbins,logofficiallongimassbins */  /*nlogofficialimassbins,logofficialimassbins*/  /* nlinmassbins,linmassbins */,nFullCosThetaBins,minFullCosTheta,maxFullCosTheta );
	if(dologx) h2SumqZP->GetXaxis()->SetMoreLogLabels();
	if(dologx) h2SumqZP->GetXaxis()->SetNoExponent();
	
	vector<TH2D*> h2SumqE6;
	for(unsigned int iE6=0 ; iE6<vE6models.size() ; iE6++)
	{
		h2SumqE6.push_back( new TH2D("h2SumqE6_"+vE6models[iE6],";m_{"+channel+"} GeV;cos#theta*;#frac{d#sigma}{dm_{"+channel+"}} in arbitrary scale", nlogtheoryimassbins,logtheoryimassbins /* nlogofficiallongimassbins,logofficiallongimassbins */  /*nlogofficialimassbins,logofficialimassbins*/  /* nlinmassbins,linmassbins */,nFullCosThetaBins,minFullCosTheta,maxFullCosTheta ));
		if(dologx) h2SumqE6[iE6]->GetXaxis()->SetMoreLogLabels();
		if(dologx) h2SumqE6[iE6]->GetXaxis()->SetNoExponent();
	}
	
	TH2D* h2SumqKK = new TH2D("h2SumqKK",";m_{"+channel+"} GeV;cos#theta*;#frac{d#sigma}{dm_{"+channel+"}} in arbitrary scale", nlogtheoryimassbins,logtheoryimassbins /* nlogofficiallongimassbins,logofficiallongimassbins */  /*nlogofficialimassbins,logofficialimassbins*/  /* nlinmassbins,linmassbins */,nFullCosThetaBins,minFullCosTheta,maxFullCosTheta );
	if(dologx) h2SumqKK->GetXaxis()->SetMoreLogLabels();
	if(dologx) h2SumqKK->GetXaxis()->SetNoExponent();
	
	
	
	///////////////////////////////
	TString xTitle = "m_{"+channel+"} GeV";
	TString yTitle = "d#sigma/dm_{"+channel+"} fb/GeV";
	
	vector<TH1D*> h1DY;
	vector<TH1D*> h1ZP;
	vector<vector<TH1D*> > h1E6;
	for(unsigned int iE6=0 ; iE6<vE6models.size() ; iE6++) h1E6.push_back( h1Tmp );
	vector<TH1D*> h1KK;
	
	vector<TH1D*> h1fDY;
	vector<TH1D*> h1fZP;
	vector<vector<TH1D*> > h1fE6;
	for(unsigned int iE6=0 ; iE6<vE6models.size() ; iE6++) h1fE6.push_back( h1Tmp );
	vector<TH1D*> h1fKK;
	
	vector<TH1D*> h1bDY;
	vector<TH1D*> h1bZP;
	
	vector<vector<TH1D*> > h1bE6;
	for(unsigned int iE6=0 ; iE6<vE6models.size() ; iE6++) h1bE6.push_back( h1Tmp );
	vector<TH1D*> h1bKK;
	
	vector<TH2D*> h2DY;
	vector<TH2D*> h2ZP;
	vector<vector<TH2D*> > h2E6;
	for(unsigned int iE6=0 ; iE6<vE6models.size() ; iE6++) h2E6.push_back( h2Tmp );
	vector<TH2D*> h2KK;
	
	for(unsigned int q=(fstQrk-1) ; q<=(lstQrk-1) ; q++)
	{
		TString quark = qname(q+1);
		
		//// invariant mass plots
		h1DY.push_back( new TH1D("h1DY_"+quark,"DY with pdf;m_{#mu#mu} GeV;fb/GeV", nlogtheoryimassbins,logtheoryimassbins /* nlogofficiallongimassbins,logofficiallongimassbins */  /*nlogofficialimassbins,logofficialimassbins*/  /* nlinmassbins,linmassbins */  ) );
		h1DY[q]->SetLineColor(kBlack+q);
		leg_quarks->AddEntry(h1DY[q],"DY "+quark,"l");
		h1ZP.push_back( new TH1D("h1ZP_"+quark,"ZP with pdf;m_{#mu#mu} GeV;fb/GeV", nlogtheoryimassbins,logtheoryimassbins /* nlogofficiallongimassbins,logofficiallongimassbins */  /*nlogofficialimassbins,logofficialimassbins*/  /* nlinmassbins,linmassbins */  ) );
		h1ZP[q]->SetLineColor(kBlack+q+6);
		leg_quarks->AddEntry(h1ZP[q],"Z' "+quark,"l");
		for(unsigned int iE6=0 ; iE6<vE6models.size() ; iE6++)
		{
			h1E6[iE6].push_back( new TH1D("h1E6_"+vE6models[iE6]+"_"+quark,"E6 with pdf;m_{#mu#mu} GeV;fb/GeV", nlogtheoryimassbins,logtheoryimassbins /* nlogofficiallongimassbins,logofficiallongimassbins */  /*nlogofficialimassbins,logofficialimassbins*/  /* nlinmassbins,linmassbins */  ) );
			h1E6[iE6][q]->SetLineColor(kBlack+q+6);
			leg_quarks->AddEntry(h1E6[iE6][q],"Z'_{#"+vE6models[iE6]+"} "+quark,"l");
		}
		h1KK.push_back( new TH1D("h1KK_"+quark,"KK with pdf;m_{#mu#mu} GeV;fb/GeV", nlogtheoryimassbins,logtheoryimassbins /* nlogofficiallongimassbins,logofficiallongimassbins */  /*nlogofficialimassbins,logofficialimassbins*/  /* nlinmassbins,linmassbins */  ) );
		h1KK[q]->SetLineColor(kBlack+q+12);
		leg_quarks->AddEntry(h1KK[q],"KK "+quark,"l");
		
		
		//// for Afb plots
		h1fDY.push_back( new TH1D("h1fDY_"+quark,"DY with pdf;m_{#mu#mu} GeV;fb/GeV", nlogtheoryAFBimassbins,logtheoryAFBimassbins  ) );
		h1fZP.push_back( new TH1D("h1fZP_"+quark,"ZP with pdf;m_{#mu#mu} GeV;fb/GeV", nlogtheoryAFBimassbins,logtheoryAFBimassbins  ) );
		for(unsigned int iE6=0 ; iE6<vE6models.size() ; iE6++)
		{
			h1fE6[iE6].push_back( new TH1D("h1fE6_"+vE6models[iE6]+"_"+quark,"E6 with pdf;m_{#mu#mu} GeV;fb/GeV", nlogtheoryAFBimassbins,logtheoryAFBimassbins  ) );
		}
		h1fKK.push_back( new TH1D("h1fKK_"+quark,"KK with pdf;m_{#mu#mu} GeV;fb/GeV", nlogtheoryAFBimassbins,logtheoryAFBimassbins  ) );
		
		h1bDY.push_back( new TH1D("h1bDY_"+quark,"DY with pdf;m_{#mu#mu} GeV;fb/GeV", nlogtheoryAFBimassbins,logtheoryAFBimassbins  ) );
		h1bZP.push_back( new TH1D("h1bZP_"+quark,"ZP with pdf;m_{#mu#mu} GeV;fb/GeV", nlogtheoryAFBimassbins,logtheoryAFBimassbins  ) );
		for(unsigned int iE6=0 ; iE6<vE6models.size() ; iE6++)
		{
			h1bE6[iE6].push_back( new TH1D("h1bE6_"+vE6models[iE6]+"_"+quark,"E6 with pdf;m_{#mu#mu} GeV;fb/GeV", nlogtheoryAFBimassbins,logtheoryAFBimassbins  ) );
		}
		h1bKK.push_back( new TH1D("h1bKK_"+quark,"KK with pdf;m_{#mu#mu} GeV;fb/GeV", nlogtheoryAFBimassbins,logtheoryAFBimassbins  ) );

		
		//// 2d plots
		h2DY.push_back( new TH2D("h2DY_"+quark,"DY with pdf;m_{#mu#mu} GeV;cos#theta*;fb/GeV", nlogtheoryimassbins,logtheoryimassbins /* nlogofficiallongimassbins,logofficiallongimassbins */  /*nlogofficialimassbins,logofficialimassbins*/  /* nlinmassbins,linmassbins */,nFullCosThetaBins,minFullCosTheta,maxFullCosTheta  ) );
		h2ZP.push_back( new TH2D("h2ZP_"+quark,"ZP with pdf;m_{#mu#mu} GeV;cos#theta*;fb/GeV", nlogtheoryimassbins,logtheoryimassbins /* nlogofficiallongimassbins,logofficiallongimassbins */  /*nlogofficialimassbins,logofficialimassbins*/  /* nlinmassbins,linmassbins */,nFullCosThetaBins,minFullCosTheta,maxFullCosTheta  ) );
		for(unsigned int iE6=0 ; iE6<vE6models.size() ; iE6++)
		{
			h2E6[iE6].push_back( new TH2D("h2E6_"+vE6models[iE6]+"_"+quark,"E6 with pdf;m_{#mu#mu} GeV;cos#theta*;fb/GeV", nlogtheoryimassbins,logtheoryimassbins /* nlogofficiallongimassbins,logofficiallongimassbins */  /*nlogofficialimassbins,logofficialimassbins*/  /* nlinmassbins,linmassbins */,nFullCosThetaBins,minFullCosTheta,maxFullCosTheta  ) );
		}
		h2KK.push_back( new TH2D("h2KK_"+quark,"KK with pdf;m_{#mu#mu} GeV;cos#theta*;fb/GeV", nlogtheoryimassbins,logtheoryimassbins /* nlogofficiallongimassbins,logofficiallongimassbins */  /*nlogofficialimassbins,logofficialimassbins*/  /* nlinmassbins,linmassbins */,nFullCosThetaBins,minFullCosTheta,maxFullCosTheta  ) );
		
		
		
		
		//// FILL
		for(Int_t bin=1 ; bin<=h1SumqDY->GetNbinsX() ; bin++)
		{
			double m  = h1SumqDY->GetBinCenter(bin);
			double dm = h1SumqDY->GetBinWidth(bin);
			double s  = m*m;
			double s2 = s*s;
			unsigned int idOut = (chan=="mm") ? s2f["muon"]->id : s2f["electron"]->id;
			unsigned int idIn = q+1;
			unsigned int nsegments = 500;
			double yMax = rapidityMax(s);
			
			
			//--------------- 1d mass distribution -----------------------------
			// instead of integrating over cosTheta*, just ignore it in the ME^2
			double ME2DY = hA2SM(s,idIn,idOut);
			double ME2ZP = hA2ZP(s,idIn,idOut);
			vector<double> ME2E6;
			for(unsigned int iE6=0 ; iE6<vE6models.size() ; iE6++)
			{
				setThetaE6(vE6models[iE6]);
				ME2E6.push_back( hA2E6(s,idIn,idOut) );
			}
			double ME2KK = hA2KK(s,idIn,idOut);
			
			template_pdfintegrand TpdfDY(s,idIn);
			double Ipdf_A2DY = integrate(TpdfDY,-yMax,+yMax,nsegments);
			double fullA2DY = (2.*pi)*(alphaEM*alphaEM/(4.*s))*(s2/4.)*ME2DY*(8./3.)*(2.*Ipdf_A2DY/3.); // units of GeV^-4
			fullA2DY *= 2.*sqrt(s); // Jacobian transformation -> units of GeV^-3
			fullA2DY *= GeV2fb;     // units of fb/GeV
			
			template_pdfintegrand TpdfZP(s,idIn);
			double Ipdf_A2ZP = integrate(TpdfZP,-yMax,+yMax,nsegments);
			double fullA2ZP = (2.*pi)*(alphaEM*alphaEM/(4.*s))*(s2/4.)*ME2ZP*(8./3.)*(2.*Ipdf_A2ZP/3.); // units of GeV^-4
			fullA2ZP *= 2.*sqrt(s); // Jacobian transformation -> units of GeV^-3
			fullA2ZP *= GeV2fb;     // units of fb/GeV
			
			template_pdfintegrand TpdfE6(s,idIn);
			vector<double> fullA2E6;
			vector<double> Ipdf_A2E6;
			for(unsigned int iE6=0 ; iE6<vE6models.size() ; iE6++)
			{
				setThetaE6(vE6models[iE6]);
				Ipdf_A2E6.push_back( integrate(TpdfE6,-yMax,+yMax,nsegments) );
				fullA2E6.push_back( (2.*pi)*(alphaEM*alphaEM/(4.*s))*(s2/4.)*ME2E6[iE6]*(8./3.)*(2.*Ipdf_A2E6[iE6]/3.) ); // units of GeV^-4
				fullA2E6[iE6] *= 2.*sqrt(s); // Jacobian transformation -> units of GeV^-3
				fullA2E6[iE6] *= GeV2fb;     // units of fb/GeV
			}
			
			template_pdfintegrand TpdfKK(s,idIn);
			double Ipdf_A2KK = integrate(TpdfKK,-yMax,+yMax,nsegments);
			double fullA2KK = (2.*pi)*(alphaEM*alphaEM/(4.*s))*(s2/4.)*ME2KK*(8./3.)*(2.*Ipdf_A2KK/3.); // units of GeV^-4
			fullA2KK *= 2.*sqrt(s); // Jacobian transformation -> units of GeV^-3
			fullA2KK *= GeV2fb;     // units of fb/GeV
			
			//------ FILL
			h1DY[q]->SetBinContent(bin,fullA2DY);
			h1ZP[q]->SetBinContent(bin,fullA2ZP);
			for(unsigned int iE6=0 ; iE6<vE6models.size() ; iE6++)
			{
				setThetaE6(vE6models[iE6]);
				h1E6[iE6][q]->SetBinContent(bin,fullA2E6[iE6]);
			}
			h1KK[q]->SetBinContent(bin,fullA2KK);
			//------------------------------------------------------------------
			
			
			//------------------- forward backward asymmetry -------------------
			template_hA2SM TcosThetaDY(s,idIn,idOut);
			template_hA2ZP TcosThetaZP(s,idIn,idOut);
			template_hA2E6 TcosThetaE6(s,idIn,idOut);
			template_hA2KK TcosThetaKK(s,idIn,idOut);
			
			double ME2fA2DY = integrate(TcosThetaDY,0.,+1.,nsegments);
			double ME2fA2ZP = integrate(TcosThetaZP,0.,+1.,nsegments);
			vector<double> ME2fA2E6;
			for(unsigned int iE6=0 ; iE6<vE6models.size() ; iE6++)
			{
				setThetaE6(vE6models[iE6]);
				ME2fA2E6.push_back( integrate(TcosThetaE6,0.,+1.,nsegments) );
			}
			double ME2fA2KK = integrate(TcosThetaKK,0.,+1.,nsegments);
			
			double ME2bA2DY = integrate(TcosThetaDY,-1.,0.,nsegments);
			double ME2bA2ZP = integrate(TcosThetaZP,-1.,0.,nsegments);
			vector<double> ME2bA2E6;
			for(unsigned int iE6=0 ; iE6<vE6models.size() ; iE6++)
			{
				setThetaE6(vE6models[iE6]);
				ME2bA2E6.push_back( integrate(TcosThetaE6,-1.,0.,nsegments) );
			}
			double ME2bA2KK = integrate(TcosThetaKK,-1.,0.,nsegments);
			
			//------ FILL
			h1fDY[q]->SetBinContent(bin,ME2fA2DY);
			h1fZP[q]->SetBinContent(bin,ME2fA2ZP);
			for(unsigned int iE6=0 ; iE6<vE6models.size() ; iE6++)
			{
				setThetaE6(vE6models[iE6]);
				h1fE6[iE6][q]->SetBinContent(bin,ME2fA2E6[iE6]);
			}
			h1fKK[q]->SetBinContent(bin,ME2fA2KK);
			
			h1bDY[q]->SetBinContent(bin,ME2bA2DY);
			h1bZP[q]->SetBinContent(bin,ME2bA2ZP);
			for(unsigned int iE6=0 ; iE6<vE6models.size() ; iE6++)
			{
				setThetaE6(vE6models[iE6]);
				h1bE6[iE6][q]->SetBinContent(bin,ME2bA2E6[iE6]);
			}
			h1bKK[q]->SetBinContent(bin,ME2bA2KK);
			//------------------------------------------------------------------
			
			
			//------------------- 2d cos(theta) vs mass distributions -----------
			for(Int_t ybin=1 ; ybin<=h2SumqDY->GetNbinsY() ; ybin++)
			{
				double costheta  = h2SumqDY->GetYaxis()->GetBinCenter(ybin);
				
				double ME2DYang = hA2SM(costheta,s,idIn,idOut);
				double ME2ZPang = hA2ZP(costheta,s,idIn,idOut);
				vector<double> ME2E6ang;
				for(unsigned int iE6=0 ; iE6<vE6models.size() ; iE6++)
				{
					setThetaE6(vE6models[iE6]);
					ME2E6ang.push_back( hA2E6(costheta,s,idIn,idOut) );
				}
				double ME2KKang = hA2KK(costheta,s,idIn,idOut);
				
				fullA2DY = (2.*pi)*(alphaEM*alphaEM/(4.*s))*(s2/4.)*ME2DYang*(2.*Ipdf_A2DY/3.); // units of GeV^-4
				fullA2DY *= 2.*sqrt(s); // Jacobian transformation -> units of GeV^-3
				fullA2DY *= GeV2fb;     // units of fb/GeV
				
				fullA2ZP = (2.*pi)*(alphaEM*alphaEM/(4.*s))*(s2/4.)*ME2ZPang*(2.*Ipdf_A2ZP/3.); // units of GeV^-4
				fullA2ZP *= 2.*sqrt(s); // Jacobian transformation -> units of GeV^-3
				fullA2ZP *= GeV2fb;     // units of fb/GeV
				
				fullA2E6.clear();
				for(unsigned int iE6=0 ; iE6<vE6models.size() ; iE6++)
				{
					setThetaE6(vE6models[iE6]);
					fullA2E6[iE6] = (2.*pi)*(alphaEM*alphaEM/(4.*s))*(s2/4.)*ME2E6ang[iE6]*(2.*Ipdf_A2E6[iE6]/3.); // units of GeV^-4
					fullA2E6[iE6] *= 2.*sqrt(s); // Jacobian transformation -> units of GeV^-3
					fullA2E6[iE6] *= GeV2fb;     // units of fb/GeV
				}
				
				fullA2KK = (2.*pi)*(alphaEM*alphaEM/(4.*s))*(s2/4.)*ME2KKang*(2.*Ipdf_A2KK/3.); // units of GeV^-4
				fullA2KK *= 2.*sqrt(s); // Jacobian transformation -> units of GeV^-3
				fullA2KK *= GeV2fb;     // units of fb/GeV
				
				//------ FILL
				h2DY[q]->SetBinContent(bin,ybin,fullA2DY);
				h2ZP[q]->SetBinContent(bin,ybin,fullA2ZP);
				for(unsigned int iE6=0 ; iE6<vE6models.size() ; iE6++)
				{
					setThetaE6(vE6models[iE6]);
					h2E6[iE6][q]->SetBinContent(bin,ybin,fullA2E6[iE6]);
				}
				h2KK[q]->SetBinContent(bin,ybin,fullA2KK);
			}
			//------------------------------------------------------------------
			cout << "q=" << idIn << ", m=" << m << "\r" << flush;
		}
	}
	
	for(unsigned int q=(fstQrk-1) ; q<=(lstQrk-1) ; q++)
	{
		h1SumqDY->Add(h1DY[q]);
		h1SumqZP->Add(h1ZP[q]);
		for(unsigned int iE6=0 ; iE6<vE6models.size() ; iE6++)
		{
			h1SumqE6[iE6]->Add(h1E6[iE6][q]);
		}
		h1SumqKK->Add(h1KK[q]);
		
		h1fSumqDY->Add(h1fDY[q]);
		h1fSumqZP->Add(h1fZP[q]);
		for(unsigned int iE6=0 ; iE6<vE6models.size() ; iE6++)
		{
			h1fSumqE6[iE6]->Add(h1fE6[iE6][q]);
		}
		h1fSumqKK->Add(h1fKK[q]);
		
		h1bSumqDY->Add(h1bDY[q]);
		h1bSumqZP->Add(h1bZP[q]);
		for(unsigned int iE6=0 ; iE6<vE6models.size() ; iE6++)
		{
			h1bSumqE6[iE6]->Add(h1bE6[iE6][q]);
		}
		h1bSumqKK->Add(h1bKK[q]);
		
		h2SumqDY->Add(h2DY[q]);
		h2SumqZP->Add(h2ZP[q]);
		for(unsigned int iE6=0 ; iE6<vE6models.size() ; iE6++)
		{
			h2SumqE6[iE6]->Add(h2E6[iE6][q]);
		}
		h2SumqKK->Add(h2KK[q]);
	}
	
	for(Int_t bin=1 ; bin<=h1AfbSumqZP->GetNbinsX() ; bin++)
	{
		Double_t Afb = 0.;
		
		Afb = (h1fSumqDY->GetBinContent(bin)-h1bSumqDY->GetBinContent(bin))/(h1fSumqDY->GetBinContent(bin)+h1bSumqDY->GetBinContent(bin));
		h1AfbSumqDY->SetBinContent(bin,Afb);
		
		Afb = (h1fSumqZP->GetBinContent(bin)-h1bSumqZP->GetBinContent(bin))/(h1fSumqZP->GetBinContent(bin)+h1bSumqZP->GetBinContent(bin));
		h1AfbSumqZP->SetBinContent(bin,Afb);
		
		for(unsigned int iE6=0 ; iE6<vE6models.size() ; iE6++)
		{
			Afb = (h1fSumqE6[iE6]->GetBinContent(bin)-h1bSumqE6[iE6]->GetBinContent(bin))/(h1fSumqE6[iE6]->GetBinContent(bin)+h1bSumqE6[iE6]->GetBinContent(bin));
			h1AfbSumqE6[iE6]->SetBinContent(bin,Afb);
		}
		
		Afb = (h1fSumqKK->GetBinContent(bin)-h1bSumqKK->GetBinContent(bin))/(h1fSumqKK->GetBinContent(bin)+h1bSumqKK->GetBinContent(bin));
		h1AfbSumqKK->SetBinContent(bin,Afb);
	}
	
	
	//-------------------- bare histos -------------------
	TFile* histFile = new TFile("plots/theory_mass"+sXmass+"GeV_withpdf_histos.root","RECREATE");
	h1SumqDY->Write();
	h1SumqZP->Write();
	for(unsigned int iE6=0 ; iE6<vE6models.size() ; iE6++) h1SumqE6[iE6]->Write();
	h1SumqKK->Write();
	
	h1AfbSumqDY->Write();
	h1AfbSumqZP->Write();
	for(unsigned int iE6=0 ; iE6<vE6models.size() ; iE6++) h1AfbSumqE6[iE6]->Write();
	h1AfbSumqKK->Write();
	
	h2SumqDY->Write();
	h2SumqZP->Write();
	for(unsigned int iE6=0 ; iE6<vE6models.size() ; iE6++) h2SumqE6[iE6]->Write();
	h2SumqKK->Write();
	//-----------------------------------------------------
	
	
	
	
	
	
	
	//-------------------- invariant mass 1d histo --------------------------------------
	Double_t max = 0.;
	max = (h1SumqDY->GetMaximum()>max) ? h1SumqDY->GetMaximum() : max;
	max = (h1SumqZP->GetMaximum()>max) ? h1SumqZP->GetMaximum() : max;
	max = (h1SumqKK->GetMaximum()>max) ? h1SumqKK->GetMaximum() : max;
	for(unsigned int iE6=0 ; iE6<vE6models.size() ; iE6++)
	{
		max = (h1SumqE6[iE6]->GetMaximum()>max) ? h1SumqE6[iE6]->GetMaximum() : max;
	}
	max *= 2.;
	TCanvas* cnv_mass = new TCanvas("cnv_mass","cnv_mass",600,400);
	cnv_mass->SetTicks(1,1);
	if(dologx) cnv_mass->SetLogx();
	if(dology) cnv_mass->SetLogy();
	cnv_mass->cd();
	cnv_mass->Draw();
	h1SumqDY->SetMaximum(max);
	h1SumqDY->Draw();
	h1SumqZP->Draw("SAMES");
	for(unsigned int iE6=0 ; iE6<vE6models.size() ; iE6++) h1SumqE6[iE6]->Draw("SAMES");
	h1SumqKK->Draw("SAMES");
	leg_sigma->Draw("SAMES");
	saveas(cnv_mass,"plots/theory_mass"+sXmass+"GeV_withpdf_mass");
	//-----------------------------------------------------------------------------------
	
	
	//-------------------- Afb 1d histo -------------------------------------------------
	TCanvas* cnv_afb = new TCanvas("cnv_afb","cnv_afb",600,400);
	cnv_afb->SetTicks(1,1);
	cnv_afb->SetLogx();
	cnv_afb->cd();
	cnv_afb->Draw();
	h1AfbSumqDY->SetMinimum(-1.);
	h1AfbSumqDY->SetMaximum(+1.);
	h1AfbSumqDY->Draw();
	h1AfbSumqZP->Draw("SAMES");
	for(unsigned int iE6=0 ; iE6<vE6models.size() ; iE6++) h1AfbSumqE6[iE6]->Draw("SAMES");
	// h1AfbSumqKK->Draw("SAMES");
	leg_afb->Draw("SAMES");
	saveas(cnv_afb,"plots/theory_mass"+sXmass+"GeV_withpdf_afb");
	//-----------------------------------------------------------------------------------
	
	
	//////////////////////////////////
	Double_t phi = -25.;
	TString drawopt = "COLZ";
	
	TCanvas* cnv2dDY = new TCanvas("c2dDY","c2dDY",600,400);
	cnv2dDY->SetTicks(1,1);
	if(dologx) cnv2dDY->SetLogx();
	if(dologz) cnv2dDY->SetLogz();
	h2SumqDY->Draw(drawopt);
	saveas(cnv2dDY,"plots/theory_mass"+sXmass+"GeV_withpdf_2d_DY");
	plotsurface(h2SumqDY, "plots/theory_mass"+sXmass+"GeV_withpdf_2d_DY_surf", phi, dologz, -1., +1, 10);
	
	TCanvas* cnv2dZP = new TCanvas("c2dZP","c2dZP",600,400);
	cnv2dZP->SetTicks(1,1);
	if(dologx) cnv2dZP->SetLogx();
	if(dologz) cnv2dZP->SetLogz();
	h2SumqZP->Draw(drawopt);
	saveas(cnv2dZP,"plots/theory_mass"+sXmass+"GeV_withpdf_2d_ZP");
	plotsurface(h2SumqZP, "plots/theory_mass"+sXmass+"GeV_withpdf_2d_ZP_surf", phi, dologz, -1., +1, 10);
	
	vector<TCanvas*> cnv2dE6;
	for(unsigned int iE6=0 ; iE6<vE6models.size() ; iE6++)
	{
		cnv2dE6.push_back( new TCanvas("c2dE6_"+vE6models[iE6],"c2dE6_"+vE6models[iE6],600,400) );
		cnv2dE6[iE6]->SetTicks(1,1);
		if(dologx) cnv2dE6[iE6]->SetLogx();
		if(dologz) cnv2dE6[iE6]->SetLogz();
		h2SumqE6[iE6]->Draw(drawopt);
		saveas(cnv2dE6[iE6],"plots/theory_mass"+sXmass+"GeV_withpdf_2d_E6_"+vE6models[iE6]);
		plotsurface(h2SumqE6[iE6], "plots/theory_mass"+sXmass+"GeV_withpdf_2d_E6_"+vE6models[iE6]+"_surf", phi, dologz, -1., +1, 10);
	}
	
	TCanvas* cnv2dKK = new TCanvas("c2dKK","c2dKK",600,400);
	cnv2dKK->SetTicks(1,1);
	if(dologx) cnv2dKK->SetLogx();
	if(dologz) cnv2dKK->SetLogz();
	h2SumqKK->Draw(drawopt);
	saveas(cnv2dKK,"plots/theory_mass"+sXmass+"GeV_withpdf_2d_KK");
	plotsurface(h2SumqKK, "plots/theory_mass"+sXmass+"GeV_withpdf_2d_KK_surf", phi, dologz, -1., +1, 10);
}
