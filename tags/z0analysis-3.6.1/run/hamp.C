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

const unsigned int fstQrk = 1;
const unsigned int lstQrk = 2;

unsigned int qstate(unsigned int qrk)
{
	if(qrk==fstQrk-1) return 0;
	if(qrk==lstQrk-1) return 2;
	return 1;
}

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
	
	vector<TH1D*> h1KK;
	vector<TH1D*> h1KKnoSM;
	vector<TH1D*> h1ZP;
	vector<TH1D*> h1ZPnoSM;
	vector<TH1D*> h1SM;
	
	vector<TH1D*> h1AsymKK;
	vector<TH1D*> h1AsymKKnoSM;
	vector<TH1D*> h1AsymZP;
	vector<TH1D*> h1AsymZPnoSM;
	vector<TH1D*> h1AsymSM;
	
	vector<TH1D*> h1wGKK;
	vector<TH1D*> h1wZKK;
	vector<TH1D*> h1wZP;
	
	vector<TH1D*> h1rKK;
	vector<TH1D*> h1rKKnoSM;
	vector<TH1D*> h1rZP;
	vector<TH1D*> h1rZPnoSM;
	
	vector<TH2D*> h2rKK;
	vector<TH2D*> h2rKKnoSM;
	vector<TH2D*> h2rZP;
	vector<TH2D*> h2rZPnoSM;
	
	vector<TH2D*> h2KK;
	vector<TH2D*> h2KKnoSM;
	vector<TH2D*> h2ZP;
	vector<TH2D*> h2ZPnoSM;
	vector<TH2D*> h2SM;
	
	
	for(unsigned int q=(fstQrk-1) ; q<=(lstQrk-1) ; q++)
	{
		TString quark = (q==0) ? "d-quark" : "u-quark";
	
		resetKKmass(); // important !
		resetZPmass(); // important !
		
		// setFgZP(0.1,-0.1);  // important !
		// setFgGKK(0.1,+0.1); // important !
		// setFgZKK(1.5,-1.5); // important !
	
		wgtMaxZP = 0.;
		wgtMaxKK = 0.;
	
		h1KK.push_back( new TH1D("h1KK_"+quark,quark+" DY(black), "+mBSM+" TeV Z'_{SSM}(blue) and "+mBSM+" TeV KK(red);m_{#mu#mu} GeV;arbitrary scale", Nx,xMin,xMax) );
		h1KKnoSM.push_back( new TH1D("h1KKnoSM_"+quark,quark+" DY(black), "+mBSM+" TeV Z'_{SSM}(blue) and "+mBSM+" TeV KK(red);m_{#mu#mu} GeV;arbitrary scale", Nx,xMin,xMax) );
		h1ZP.push_back( new TH1D("h1ZP_"+quark,quark+" DY(black), "+mBSM+" TeV Z'_{SSM}(blue) and "+mBSM+" TeV KK(red);m_{#mu#mu} GeV;arbitrary scale", Nx,xMin,xMax) );
		h1ZPnoSM.push_back( new TH1D("h1ZPnoSM_"+quark,quark+" DY(black), "+mBSM+" TeV Z'_{SSM}(blue) and "+mBSM+" TeV KK(red);m_{#mu#mu} GeV;arbitrary scale", Nx,xMin,xMax) );
		h1SM.push_back( new TH1D("h1SM_"+quark,quark+" DY(black), "+mBSM+" TeV Z'_{SSM}(blue) and "+mBSM+" TeV KK(red);m_{#mu#mu} GeV;arbitrary scale", Nx,xMin,xMax) );
		h1SM[q]->SetLineColor(kBlack);
		h1SM[q]->SetLineStyle(1);
		h1ZP[q]->SetLineColor(kBlue);
		h1ZP[q]->SetLineStyle(1);
		h1ZPnoSM[q]->SetLineColor(kBlue);
		h1ZPnoSM[q]->SetLineStyle(3);
		h1KK[q]->SetLineColor(kRed);
		h1KK[q]->SetLineStyle(1);
		h1KKnoSM[q]->SetLineColor(kRed);
		h1KKnoSM[q]->SetLineStyle(5);
		
		h1AsymKK.push_back( new TH1D("h1AsymKK_"+quark,quark+" DY(black), "+mBSM+" TeV Z'_{SSM}(blue) and "+mBSM+" TeV KK(red);m_{#mu#mu} GeV;A_{fb}", Nx,xMin,xMax) );
		h1AsymKKnoSM.push_back( new TH1D("h1AsymKKnoSM_"+quark,quark+" DY(black), "+mBSM+" TeV Z'_{SSM}(blue) and "+mBSM+" TeV KK(red);m_{#mu#mu} GeV;A_{fb}", Nx,xMin,xMax) );
		h1AsymZP.push_back( new TH1D("h1AsymZP_"+quark,quark+" DY(black), "+mBSM+" TeV Z'_{SSM}(blue) and "+mBSM+" TeV KK(red);m_{#mu#mu} GeV;A_{fb}", Nx,xMin,xMax) );
		h1AsymZPnoSM.push_back( new TH1D("h1AsymZPnoSM_"+quark,quark+" DY(black), "+mBSM+" TeV Z'_{SSM}(blue) and "+mBSM+" TeV KK(red);m_{#mu#mu} GeV;A_{fb}", Nx,xMin,xMax) );
		h1AsymSM.push_back( new TH1D("h1AsymSM_"+quark,quark+" DY(black), "+mBSM+" TeV Z'_{SSM}(blue) and "+mBSM+" TeV KK(red);m_{#mu#mu} GeV;A_{fb}", Nx,xMin,xMax) );
		h1AsymSM[q]->SetLineColor(kBlack);
		h1AsymSM[q]->SetLineStyle(1);
		h1AsymZP[q]->SetLineColor(kBlue);
		h1AsymZP[q]->SetLineStyle(1);
		h1AsymZPnoSM[q]->SetLineColor(kBlue);
		h1AsymZPnoSM[q]->SetLineStyle(3);
		h1AsymKK[q]->SetLineColor(kRed);
		h1AsymKK[q]->SetLineStyle(1);
		h1AsymKKnoSM[q]->SetLineColor(kRed);
		h1AsymKKnoSM[q]->SetLineStyle(5);
		
		h1wGKK.push_back( new TH1D("h1wGKK_"+quark,quark+" Z'_{SSM}(blue) and KK #gamma(red)/Z(green);pole mass GeV;#Gamma_{tot}", Nm,mMin,mMax) );
		h1wZKK.push_back( new TH1D("h1wZKK_"+quark,quark+" Z'_{SSM}(blue) and KK #gamma(red)/Z(green);pole mass GeV;#Gamma_{tot}", Nm,mMin,mMax) );
		h1wZP.push_back( new TH1D("h1wZP_"+quark,  quark+" Z'_{SSM}(blue) and KK #gamma(red)/Z(green);pole mass GeV;#Gamma_{tot}", Nm,mMin,mMax) );
		h1wZP[q]->SetLineColor(kBlue);
		h1wZP[q]->SetLineStyle(3);
		h1wGKK[q]->SetLineColor(kRed);
		h1wGKK[q]->SetLineStyle(5);
		h1wZKK[q]->SetLineColor(kGreen+2);
		h1wZKK[q]->SetLineStyle(5);
		
		h1rKK.push_back( new TH1D("h1rKK_"+quark,         quark+" Z'_{SSM}(blue) and KK(red);m_{#mu#mu} GeV;ME^{2}_{BSM}/ME^{2}_{DY}", Nx,xMin,xMax) );
		h1rKKnoSM.push_back( new TH1D("h1rKKnoSM_"+quark, quark+" Z'_{SSM}(blue) and KK(red);m_{#mu#mu} GeV;ME^{2}_{BSM}/ME^{2}_{DY}", Nx,xMin,xMax) );
		h1rZP.push_back( new TH1D("h1rZP_"+quark,         quark+" Z'_{SSM}(blue) and KK(red);m_{#mu#mu} GeV;ME^{2}_{BSM}/ME^{2}_{DY}", Nx,xMin,xMax) );
		h1rZPnoSM.push_back( new TH1D("h1rZPnoSM_"+quark, quark+" Z'_{SSM}(blue) and KK(red);m_{#mu#mu} GeV;ME^{2}_{BSM}/ME^{2}_{DY}", Nx,xMin,xMax) );
		h1rZP[q]->SetLineColor(kBlue);
		h1rZP[q]->SetLineStyle(1);
		h1rZPnoSM[q]->SetLineColor(kBlue);
		h1rZPnoSM[q]->SetLineStyle(3);
		h1rKK[q]->SetLineColor(kRed);
		h1rKK[q]->SetLineStyle(1);
		h1rKKnoSM[q]->SetLineColor(kRed);
		h1rKKnoSM[q]->SetLineStyle(5);
		
		h2rKK.push_back( new TH2D("h2rKK_"+quark,         quark+" "+mBSM+" TeV KK;m_{#mu#mu} GeV;cos#theta*;ME^{2}_{BSM}/ME^{2}_{DY}", Nx,xMin,xMax, Ny,yMin,yMax) );
		h2rKKnoSM.push_back( new TH2D("h2rKKnoSM_"+quark, quark+" "+mBSM+" TeV KK no interference;m_{#mu#mu} GeV;cos#theta*;ME^{2}_{BSM}/ME^{2}_{DY}", Nx,xMin,xMax, Ny,yMin,yMax) );
		h2rZP.push_back( new TH2D("h2rZP_"+quark,         quark+" "+mBSM+" TeV Z'_{SSM};m_{#mu#mu} GeV;cos#theta*;ME^{2}_{BSM}/ME^{2}_{DY}", Nx,xMin,xMax, Ny,yMin,yMax) );
		h2rZPnoSM.push_back( new TH2D("h2rZPnoSM_"+quark, quark+" "+mBSM+" TeV Z'_{SSM} no interference;m_{#mu#mu} GeV;cos#theta*;ME^{2}_{BSM}/ME^{2}_{DY}", Nx,xMin,xMax, Ny,yMin,yMax) );
		
		h2KK.push_back( new TH2D("h2KK_"+quark,         quark+" "+mBSM+" TeV KK;m_{#mu#mu} GeV;cos#theta*;arbitrary scale", Nx,xMin,xMax, Ny,yMin,yMax) );
		h2KKnoSM.push_back( new TH2D("h2KKnoSM_"+quark, quark+" "+mBSM+" TeV KK no interference;m_{#mu#mu} GeV;cos#theta*;arbitrary scale", Nx,xMin,xMax, Ny,yMin,yMax) );
		h2ZP.push_back( new TH2D("h2ZP_"+quark,         quark+" "+mBSM+" TeV Z'_{SSM};m_{#mu#mu} GeV;cos#theta*;arbitrary scale", Nx,xMin,xMax, Ny,yMin,yMax) );
		h2ZPnoSM.push_back( new TH2D("h2ZPnoSM_"+quark, quark+" "+mBSM+" TeV Z'_{SSM} no interference;m_{#mu#mu} GeV;cos#theta*;arbitrary scale", Nx,xMin,xMax, Ny,yMin,yMax) );
		h2SM.push_back( new TH2D("h2SM_"+quark,quark+" DY;m_{#mu#mu} GeV;cos#theta*;arbitrary scale", Nx,xMin,xMax, Ny,yMin,yMax) );
		
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
			unsigned int idIn  = s2f[(q==0) ? "dwn" : "up" ]->id;
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
			
			bin = h1AsymKK[q]->FindBin(m);
			h1AsymKK[q]->SetBinContent(bin,AfbKK);
			h1AsymKKnoSM[q]->SetBinContent(bin,AfbKKnoSM);
			h1AsymZP[q]->SetBinContent(bin,AfbZP);
			h1AsymZPnoSM[q]->SetBinContent(bin,AfbZPnoSM);
			h1AsymSM[q]->SetBinContent(bin,AfbSM);
			
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
			
			bin = h1KK[q]->FindBin(m);
			h1KK[q]->SetBinContent(bin,A2KK);
			h1KKnoSM[q]->SetBinContent(bin,A2KKnoSM);
			h1ZP[q]->SetBinContent(bin,A2ZP);
			h1ZPnoSM[q]->SetBinContent(bin,A2ZPnoSM);
			h1SM[q]->SetBinContent(bin,A2SM);
			
			
			rKK = (IFA2KK+IBA2KK)/(IFA2SM+IBA2SM); // one incoming flavor (u-quark) and integrated over cosTheta
			rKKnoSM = (IFA2KKnoSM+IBA2KKnoSM)/(IFA2SM+IBA2SM); // one incoming flavor (u-quark) and integrated over cosTheta
			rZP = (IFA2ZP+IBA2ZP)/(IFA2SM+IBA2SM); // one incoming flavor (u-quark) and integrated over cosTheta
			rZPnoSM = (IFA2ZPnoSM+IBA2ZPnoSM)/(IFA2SM+IBA2SM); // one incoming flavor (u-quark) and integrated over cosTheta
			// double cosTheta = 0.;
			// rKK = weightKK(cosTheta,s,idIn,idOut); // one incoming flavor (u-quark) in a given cosTheta
			// rKKnoSM = weightKKnoSM(cosTheta,s,idIn,idOut); // one incoming flavor (u-quark) in a given cosTheta
			// rZP = weightZP(cosTheta,s,idIn,idOut); // one incoming flavor (u-quark) in a given cosTheta
			h1rKK[q]->SetBinContent(bin,rKK);
			h1rKKnoSM[q]->SetBinContent(bin,rKKnoSM);
			h1rZP[q]->SetBinContent(bin,rZP);
			h1rZPnoSM[q]->SetBinContent(bin,rZPnoSM);
			//_INFO("rKK="+_s(rKK)+", rZP="+_s(rZP));
			
			cout << "m=" << m << "\r" << flush;
			
			for(double cost=yMin ; cost<=yMax ; cost+=dy)
			{
				A2KK = hA2KK(cost,s,idIn,idOut);
				A2KKnoSM = hA2KKnoSM(cost,s,idIn,idOut);
				A2ZP = hA2ZP(cost,s,idIn,idOut);
				A2ZPnoSM = hA2ZPnoSM(cost,s,idIn,idOut);
				A2SM = hA2SM(cost,s,idIn,idOut);
				Int_t binxy = h2KK[q]->FindBin(m,cost);
				h2KK[q]->SetBinContent(binxy,A2KK);
				h2KKnoSM[q]->SetBinContent(binxy,A2KKnoSM);
				h2ZP[q]->SetBinContent(binxy,A2ZP);
				h2ZPnoSM[q]->SetBinContent(binxy,A2ZPnoSM);
				h2SM[q]->SetBinContent(binxy,A2SM);
				
				rKK = weightKK(cost,s,idIn,idOut); // one incoming flavor in a given cosTheta
				rKKnoSM = weightKKnoSM(cost,s,idIn,idOut); // one incoming flavor in a given cosTheta
				rZP = weightZP(cost,s,idIn,idOut); // one incoming flavor in a given cosTheta
				rZPnoSM = weightZPnoSM(cost,s,idIn,idOut); // one incoming flavor in a given cosTheta
				h2rKK[q]->SetBinContent(binxy,rKK);
				h2rKKnoSM[q]->SetBinContent(binxy,rKKnoSM);
				h2rZP[q]->SetBinContent(binxy,rZP);
				h2rZPnoSM[q]->SetBinContent(binxy,rZPnoSM);
				
				wgtMaxZP = (wgtMaxZP>rZPnoSM) ? wgtMaxZP : rZPnoSM;
				wgtMaxKK = (wgtMaxKK>rKKnoSM) ? wgtMaxKK : rKKnoSM;
			}
		}
		
		////////////////////////////////////////////////////////////
		for(double m=mMin ; m<=mMax ; m+=dm)
		{
			setKKmass(m);
			setZPmass(m);
		
			double widthZP  = wTotZP();
			double widthGKK = wTotGKK(1);
			double widthZKK = wTotZKK(1);
			
			Int_t bin = h1wZP[q]->FindBin(m);
			h1wGKK[q]->SetBinContent(bin,widthGKK);
			h1wZKK[q]->SetBinContent(bin,widthZKK);
			h1wZP[q]->SetBinContent(bin,widthZP);
		}
		resetKKmass(); // important !
		resetZPmass(); // important !
		////////////////////////////////////////////////////////////
		
		TString path = "";
		
		TCanvas* cnv_1d = new TCanvas("c1d"+quark,"c1d",600,400);
		cnv_1d->SetLogy();
		cnv_1d->cd();
		cnv_1d->Draw();
		h1SM[q]->Draw();
		h1KK[q]->Draw("SAMES");
		h1KKnoSM[q]->Draw("SAMES");
		h1ZP[q]->Draw("SAMES");
		h1ZPnoSM[q]->Draw("SAMES");
		saveas(cnv_1d,"plots/theory_mass_"+quark);
		savemultipdf(cnv_1d, "plots/theory_mass_allquarks.pdf", qstate(q));
		
		TCanvas* cnv_1dr = new TCanvas("c1dr"+quark,"c1dr",600,400);
		cnv_1dr->SetLogy();
		cnv_1dr->cd();
		cnv_1dr->Draw();
		h1rKK[q]->Draw();
		h1rKKnoSM[q]->Draw("SAMES");
		h1rZP[q]->Draw("SAMES");
		h1rZPnoSM[q]->Draw("SAMES");
		saveas(cnv_1dr,"plots/theory_ratioVSmass_"+quark);
		savemultipdf(cnv_1dr, "plots/theory_ratioVSmass_allquarks.pdf", qstate(q));
		
		TCanvas* cnv_2dr = new TCanvas("c2dr"+quark,"c2dr",600,1000);
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
		h2rKK[q]->Draw("COLZ");
		pad_2drKKnoSM->cd();
		h2rKKnoSM[q]->Draw("COLZ");
		pad_2drZP->cd();
		h2rZP[q]->Draw("COLZ");
		pad_2drZPnoSM->cd();
		h2rZPnoSM[q]->Draw("COLZ");
		saveas(cnv_2dr,"plots/theory_ratioVSmassVScost_"+quark);
		savemultipdf(cnv_2dr, "plots/theory_ratioVSmassVScost_allquarks.pdf", qstate(q));
		
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
		h2KK[q]->Draw("COLZ");
		pad_2dKKnoSM->cd();
		h2KKnoSM[q]->Draw("COLZ");
		pad_2dZP->cd();
		h2ZP[q]->Draw("COLZ");
		pad_2dZPnoSM->cd();
		h2ZPnoSM[q]->Draw("COLZ");
		pad_2dSM->cd();
		h2SM[q]->Draw("COLZ");
		saveas(cnv_2d,"plots/theory_massVScost_"+quark);
		savemultipdf(cnv_2d, "plots/theory_massVScost_allquarks.pdf", qstate(q));
		
		TCanvas* cnv_1dAsym = new TCanvas("c1dAsym"+quark,"c1dAsym",600,400);
		cnv_1dAsym->cd();
		cnv_1dAsym->Draw();
		h1AsymSM[q]->Draw();
		h1AsymZP[q]->Draw("SAMES");
		h1AsymKK[q]->Draw("SAMES");
		h1AsymKKnoSM[q]->Draw("SAMES");
		saveas(cnv_1dAsym,"plots/theory_asymVSmass_"+quark);
		savemultipdf(cnv_1dAsym, "plots/theory_asymVSmass_allquarks.pdf", qstate(q));
		
		TCanvas* cnv_1dw = new TCanvas("c1dw"+quark,"c1dw",600,400);
		cnv_1dw->cd();
		cnv_1dw->Draw();
		h1wGKK[q]->Draw();
		h1wZKK[q]->Draw("SAMES");
		h1wZP[q]->Draw("SAMES");
		saveas(cnv_1dw,"plots/theory_widthVSpolemass_"+quark);
		savemultipdf(cnv_1dw, "plots/theory_widthVSpolemass_allquarks.pdf", qstate(q));
		
		_INFO("wgtMaxKK["+(string)quark+"] = "+_s(wgtMaxKK));
		_INFO("wgtMaxZP["+(string)quark+"] = "+_s(wgtMaxZP));
	}
	//F f(1.,1.);
	//cout << "integrate: " << integrate(f,0.,+100.,1000) << endl;
}
