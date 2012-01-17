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
#include "../include/lhapdf.h"

using namespace couplings;
using namespace width;
using namespace helicity;
using namespace kFactors;
using namespace lhapdf;

TFile* file;

void writeTemplates()
{
	file = new TFile("plots/templates2d.root","RECREATE");
	TDirectory* dirh1ZP = file->mkdir("h1ZP");
	dirh1ZP->cd();
	TDirectory* dirh1KK = file->mkdir("h1KK");
	dirh1KK->cd();
	TDirectory* dirh2ZP = file->mkdir("h2ZP");
	dirh2ZP->cd();
	TDirectory* dirh2KK = file->mkdir("h2KK");
	dirh2KK->cd();
	
	
	// unsigned int mXmax = 73;
	unsigned int mXmax = 11;
	double mMin = 250.; // GeV
	double dm   = 250.; // GeV
	
	for(unsigned int mX=0 ; mX<mXmax ; mX++)
	{
		// double m = 130.+mX*40.;
		double m = mMin+mX*dm;
		
		TString mXpoint = (TString)_s(mX);
		TString mXtitle = (TString)_s(m) + " GeV";
		
		setKKmass(m);
		setZPmass(m);
		
		dirh2ZP->cd();
		TH2D* h2ZP = new TH2D("ZP_mXp"+mXpoint,"mZP = "+mXtitle+";m_{#mu#mu};g^{2};Arbitrary scale",nlogofficialimassbins,logofficialimassbins, ng2bins,g2min,g2max);
		dirh2KK->cd();
		TH2D* h2KK = new TH2D("KK_mXp"+mXpoint,"mKK = "+mXtitle+";m_{#mu#mu};g^{2};Arbitrary scale",nlogofficialimassbins,logofficialimassbins, ng2bins,g2min,g2max);
		
		for(unsigned int g2=0 ; g2<(unsigned int)ng2bins ; g2++)
		{
			double gRe = sqrt(g2);
			double gIm = 0.;
			
			Double_t gg = g2min+g2*(double)((g2max-g2min)/ng2bins);
			
			setFgZP(gRe,gIm);
			setFgGKK(gRe,gIm);
			setFgZKK(gRe,gIm);
		
			TString g2point = (TString)_s(g2);
			TString g2title = (TString)_s(0+g2*0.2);
			dirh1ZP->cd();
			TH1D* h1ZP = new TH1D("ZP_mXp"+mXpoint+"_g2p"+g2point,"(mZP,g^{2})=("+mXtitle+","+g2title+");m_{#mu#mu};Events",nlogofficialimassbins,logofficialimassbins);
			dirh1KK->cd();
			TH1D* h1KK = new TH1D("KK_mXp"+mXpoint+"_g2p"+g2point,"(mKK,g^{2})=("+mXtitle+","+g2title+");m_{#mu#mu};Events",nlogofficialimassbins,logofficialimassbins);
			for(unsigned int massbin = 0 ; massbin<nlogofficialimassbins+1 ; massbin++)
			{
				Double_t mll = h1ZP->GetBinCenter(massbin);
				Int_t bin2d = h2ZP->FindBin(mll,gg);
				
				unsigned int nsegments = 100;
				unsigned int idOut = 13;
				double s = mll*mll;
				double s2 = s*s;
				
				/*
				template_hA2ZP fZP(s,idIn,idOut);
				template_hA2KK fKK(s,idIn,idOut);
				double ME2ZP = integrate(fZP,-1.,+1.,nsegments);
				double ME2KK = integrate(fKK,-1.,+1.,nsegments);
				*/
				
				double fullA2ZP = 0.;
				double fullA2KK = 0.;
				for(unsigned int idIn=1 ; idIn<=4 ; idIn++)
				{
					template_hA2ZP TcosThetaZP(s,idIn,idOut);
					double IcosTheta_A2ZP = integrate(TcosThetaZP,-1.,+1.,nsegments); // can be more efficient ?
					template_hA2KK TcosThetaKK(s,idIn,idOut);
					double IcosTheta_A2KK = integrate(TcosThetaKK,-1.,+1.,nsegments); // can be more efficient ?
					
					template_pdfintegrand Tpdf(s,idIn);
					double yMax = rapidityMax(s);
					double Ipdf_A2 = integrate(Tpdf,-yMax,+yMax,nsegments);
					
					double fullA2tmp = 0.;
					
					fullA2tmp = (2.*pi)*(alphaEM*alphaEM/(4.*s))*(s2/4.)*IcosTheta_A2ZP*(2.*Ipdf_A2/3.);
					fullA2tmp *= 2.*sqrt(s)*GeV2fb*luminosity; // Jacobian and units transformatons
					fullA2ZP += fullA2tmp;
					fullA2tmp = (2.*pi)*(alphaEM*alphaEM/(4.*s))*(s2/4.)*IcosTheta_A2KK*(2.*Ipdf_A2/3.);
					fullA2tmp *= 2.*sqrt(s)*GeV2fb*luminosity; // Jacobian and units transformatons
					fullA2KK += fullA2tmp;
				}
				
				
				h1ZP->SetBinContent(massbin,fullA2ZP);
				h1KK->SetBinContent(massbin,fullA2KK);

				h2ZP->SetBinContent(bin2d,fullA2ZP);
				h2KK->SetBinContent(bin2d,fullA2KK);
			}
			// h1ZP->Write();
			// h1KK->Write();
			// if(mX==0 && g2==0)
			// {
				// h1ZP->Write("plots/templates2d.pdf(");
				// h1KK->Write("plots/templates2d.pdf(");
			// }
			// else
			// {
				// h1ZP->Write("plots/templates2d.pdf");
				// h1KK->Write("plots/templates2d.pdf");
			// }
			
			dirh1ZP->cd();
			h1ZP->Write();
			dirh1KK->cd();
			h1KK->Write();
			
			_INFO("mX = "+_s(m,2)+"("+_s(mX)+") GeV -> g2 = "+_s(gg,2)+"("+_s(g2)+")");
		}
	
		file->cd();
		gStyle->SetPalette(1);
		TCanvas* c = new TCanvas("cnv_mXp"+mXpoint,"mXp"+mXpoint, 1500, 600);
		c->Divide(2,1);
		c->cd();
		c->Draw();
		TVirtualPad* pZP = (TVirtualPad*)c->cd(1);
		TVirtualPad* pKK = (TVirtualPad*)c->cd(2);
		pZP->SetLogx();
		pZP->SetLogz();
		pKK->SetLogx();
		pKK->SetLogz();
		pZP->cd();
		pZP->Draw();
		h2ZP->GetXaxis()->SetMoreLogLabels();
		h2ZP->GetXaxis()->SetNoExponent();
		h2ZP->SetFillColor(kOrange);
		h2ZP->Draw("SURF1Z");//->Draw("SURF4");//Draw("LEGO2Z");
		pKK->cd();
		pKK->Draw();
		h2KK->GetXaxis()->SetMoreLogLabels();
		h2KK->GetXaxis()->SetNoExponent();
		h2KK->SetFillColor(kOrange);
		h2KK->Draw("SURF1Z");//->Draw("SURF4");//Draw("LEGO2Z");
		
		if(mX==0 && mXmax!=1)            c->SaveAs("plots/templates2d.pdf(");
		else if(mX==mXmax-1 && mXmax!=1) c->SaveAs("plots/templates2d.pdf)");
		else                             c->SaveAs("plots/templates2d.pdf");
		
		c->Update();
		c->Write();
		
		
		dirh2ZP->cd();
		h2ZP->Write();
		dirh2KK->cd();
		h2KK->Write();
		
		cout << endl;
	}
	file->Write();
	file->Close();
}

Double_t myfunction(Double_t *x, Double_t *par)
{
	Double_t xx =x[0];
	TString mXp = (TString)_s(par[0]);
	TString g2p = (TString)_s(par[1]);
	TH1D* hTmp = (TH1D*)file->Get("h2d_mXp"+mXp+"_g2p"+g2p);
	assert(hTmp);
	return  hTmp->Interpolate(xx);
}

void myfunc()
{
	TF1 *fTmp = new TF1("myfunc",myfunction,70.,3000.,2);
	fTmp->SetParameters(8,46);
	fTmp->SetParNames("mXp","g2p");
	//fTmp->Draw();
}

void hamp2d()
{
	msglvl[DBG] = SILENT;
	msglvl[INF] = VISUAL;
	msglvl[WRN] = VISUAL;
	msglvl[ERR] = VISUAL;
	msglvl[FAT] = VISUAL;
	
	style();
	
	setLogBins(nlogofficialimassbins,logofficialimassmin,logofficialimassmax,logofficialimassbins);

	////////////////////////////
	// theoretical stuff... ////
	setFermions(); /////////////
	setkFactors(false); ////////
	resetKKmass();//////////////
	resetZPmass(); /////////////
	setCouplingsScale(true); ///
	resetfgZP(); ///////////////
	resetfgGKK(); //////////////
	resetfgZKK(); //////////////
	////////////////////////////
	
	///////////////////////////////////////////////////////////// 
	setpdfpath("/srv01/tau/hod/lhapdf_current/share/lhapdf"); ///
	initset("MRSTMCal",0,true); /////////////////////////////////
	/////////////////////////////////////////////////////////////
	
	writeTemplates();
	
/* 	file->Open("READ");
	
	TH1F *h1=new TH1F("h1","test",nlogofficialimassbins,logofficialimassbins);
	//h1->FillRandom("myfunc",20000);
	TF1 *f1=gROOT->GetFunction("myfunc");
	f1->SetParameters(8,46);
	f1->SetParNames("mXp","g2p");
	TCanvas* c = new TCanvas("c","",600,400);
	c->cd();
	c->Draw();
	h1->Draw();
	f1->Draw("SAMES"); */
}
