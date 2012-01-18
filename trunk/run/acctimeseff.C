#include "../include/rawStd.h"
#include "../include/rawROOT.h"
#include "../include/types.h"
#include "../include/logs.h"
#include "../include/style.h"
#include "../include/histos.h"

double binomialError(double m, double N)
{
	if(N==0.)
	{
		_ERROR("N=0, exitting now.");
		exit(-1);
	}
	double epsilon = m/N;
	return sqrt(epsilon*(1-epsilon)/N);
}

void savecnv(TString name, TH1D* hOrig, TH1D* hChop, TH1D* hTru, unsigned int pdfmode=1)
{
	TCanvas* c = new TCanvas(name,name, 600, 400);
	c->SetLogy();
	c->SetLogx();
	c->cd();
	c->Draw();
	hTru->SetLineColor(kBlue);
	hTru->Draw();
	hOrig->SetLineColor(kBlack);
	hOrig->Draw("SAMES");
	hChop->SetLineColor(kRed);
	hChop->Draw("SAMES");
	// c->SaveAs("plots/"+name+"_test.png");
	if(pdfmode==0)      c->SaveAs("plots/"+name+".pdf(");
	else if(pdfmode==2) c->SaveAs("plots/"+name+".pdf)");
	else                c->SaveAs("plots/"+name+".pdf");
}

void savecnv(TString name, TH1D* h)
{
	TCanvas* c = new TCanvas(name+"_chop",name+"_chop", 600, 400);
	c->SetLogy();
	c->SetLogx();
	c->cd();
	c->Draw();
	h->Draw();
	c->SaveAs("plots/"+name+"_chop.png");
}

void acctimeseff()
{
	msglvl[DBG] = SILENT;
	msglvl[INF] = VISUAL;
	msglvl[WRN] = VISUAL;
	msglvl[ERR] = VISUAL;
	msglvl[FAT] = VISUAL;

	style();
	
	TFile* fTemplates = new TFile("plots/ZP_templates_noEWkFsig_noCoupScale_templateZP.root","READ");
	
	TObjArray* toarr_recon = new TObjArray();
	toarr_recon->Read("template");
	
	TObjArray* toarr_truth = new TObjArray();
	toarr_truth->Read("truth_template");
	
	Double_t minPoleMass = 0.13; // TeV
	Double_t maxPoleMass = 3.05; // TeV
	
	unsigned const int arraysize = (unsigned int)toarr_recon->GetSize();
	Double_t actimesef[arraysize];
	Double_t actimeseferr[arraysize];
	Double_t bsmmass[arraysize];
	
	
	TCanvas* c = new TCanvas("c","c", 600, 400);
	//c->SetLogy();
	c->SetGridy();
	c->SetTicks(1,1);
	c->cd();
	c->Draw();
	
	TLegend* leg = new TLegend(0.15,0.65,0.45,0.87,NULL,"brNDC");
	leg->SetFillStyle(4000); //will be transparent
	leg->SetFillColor(0);
	leg->SetTextFont(42);
	
	TH1D* hActimesEf = new TH1D("hActimesEf","Acceptance #times Efficiency vs. the pole mass;m_{BSM} TeV;Acceptance #times Efficiency",arraysize,minPoleMass-0.02,maxPoleMass+0.02);
	hActimesEf->SetLineWidth(2);
	hActimesEf->SetMarkerStyle(2);
	hActimesEf->SetMarkerSize(0.8);
	leg->AddEntry(hActimesEf,"Templates","lep");

	_INFO("");
	
	unsigned int pdfmode = 0;
	for(unsigned int t=0 ; t<arraysize ; t++)
	{
		TH1D* hRec = (TH1D*)(TObjArray*)toarr_recon->At(t);
		_DEBUG((string)hRec->GetName());
		TH1D* hTru = (TH1D*)(TObjArray*)toarr_truth->At(t);
		_DEBUG((string)hTru->GetName());
		
		TH1D* hRec_chop = hChopper(hRec,9);
		
		Double_t sum_rec = Sum(hRec_chop,false,true); // add also overflow
		Double_t sum_tru = Sum(hTru,true,true);       // add also underflow and overflow
		
		// Double_t sum_rec = hRec_chop->GetSumOfWeights() + hRec_chop->GetBinContent(hRec_chop->GetNbinsX()+1); // add also overflow
		// Double_t sum_tru = hTru->GetSumOfWeights() + hTru->GetBinContent(0) + hTru->GetBinContent(hTru->GetNbinsX()+1);       // add also underflow and overflow
		
		_INFO("mass="+_s((0.04*t + 0.13)*1000)+" GeV -> sum_rec="+_s(sum_rec)+", sum_tru="+_s(sum_tru));
		
		if(sum_tru<=0. || sum_rec<=0. || isnaninf(sum_tru) || isnaninf(sum_rec))
		{
			_FATAL("sum_rec="+_s(sum_rec)+", sum_tru="+_s(sum_tru)+" -> ignoring point");
			continue;
		}
		
		actimesef[t]    = (sum_tru>0.) ? sum_rec/sum_tru : -1.;
		actimeseferr[t] = (sum_tru>0.) ? binomialError(sum_rec,sum_tru) : 1.;
		bsmmass[t]      = 0.04*t + 0.13;// [TeV/c^2];
		
		Int_t bin = hActimesEf->FindBin(bsmmass[t]);
		hActimesEf->SetBinContent(bin,actimesef[t]);
		// hActimesEf->SetBinError(bin,actimeseferr[t]);
		hActimesEf->SetBinError(bin,0.);
		
		TString name = "acceptancetimesefficiency_templates_TruRecChop";
		if(t==0)                pdfmode = 0;
		else if(t==arraysize-1) pdfmode = 2;
		else                    pdfmode = 1;
		savecnv(name, hRec, hRec_chop, hTru, pdfmode);
	}
	
	_INFO("");

	double sigma   = 0.;
	double average = getYaverage(hActimesEf,sigma);
	
	_INFO("BSM averaged acceptance = "+_s(average)+" +- "+_s(sigma));
	
	TF1* accMM = new TF1("accMM","pol6",minPoleMass,maxPoleMass);
	accMM->SetParameters(0.248482,0.613077,-0.960227,0.774202,-0.339321,0.0756178,-0.00670578);
	accMM->SetLineColor(kRed);
	accMM->SetLineWidth(1);
	leg->AddEntry(accMM,"1 fb^{-1} parametrization","l");
	
	TF1* fguess = new TF1("fguess","pol6",minPoleMass,maxPoleMass);
	fguess->SetParameters(0.08145,1.17631,-1.64304,1.07162,-0.33751,0.0449013,-0.00133913);
	fguess->SetLineColor(kBlue);
	fguess->SetLineWidth(1);
	fguess->SetLineStyle(5);
	
	_INFO("Fit");
	TString fitfunctype = "pol8";
	TString fitfuncname = "acceptancefit";
	TF1* func = new TF1(fitfuncname,fitfunctype,minPoleMass-0.02,maxPoleMass+0.02);
	func->SetParameters(0.248482,0.613077,-0.960227,0.774202,-0.339321,0.0756178,-0.00670578); 
	// func->SetParLimits(0,+0.0,+0.5);
	// func->SetParLimits(1,+0.0,+1.0);
	// func->SetParLimits(2,-2.0,+0.0);
	// func->SetParLimits(3,0.0,+1.0);
	// func->SetParLimits(4,-1.,+0.0);
	// func->SetParLimits(5,0.0,+0.5);
	// func->SetParLimits(6,-0.5,+0.5);
	// hActimesEf->Fit(fitfuncname,"MV+"); // "F" If fitting a polN, switch to Minuit fitter (by default, polN functions are fitted by the linear fitter).
	hActimesEf->Fit(fitfuncname,"FLLEMV+"); // "F" If fitting a polN, switch to Minuit fitter (by default, polN functions are fitted by the linear fitter).
											// "LL" An improved Log Likelihood fit in case of very low statistics and when bin contents are not integers.
											//      Do not use this option if bin contents are large (greater than 100).
											// "V"  Verbose mode
											// "+"  Add this new fitted function to the list of fitted functions (by default, the previous function is deleted
											//      and only the last one is kept)
											// "E"  Perform better errors estimation using the Minos technique 
											// "M"  Improve fit results
	// TF1* func = (TF1*)hActimesEf->GetFunction(fitfunctype);
	func = (TF1*)hActimesEf->GetFunction(fitfuncname);
	func->SetLineColor(kBlue);
	leg->AddEntry(func,"5 fb^{-1} parametrization","l");
	Int_t npar = func->GetNpar();
	Double_t chi2 = func->GetChisquare();
	_INFO("Function has "+_s(npar)+" parameters, Chi^2/NDF = "+_s(func->GetChisquare())+"/"+_s(func->GetNDF())+" = "+_s(func->GetChisquare()/func->GetNDF()));
	for (Int_t i=0;i<npar;i++) _INFO("paramerer "+(string)func->GetParName(i)+" = "+_s(func->GetParameter(i))+"+-"+_s(func->GetParError(i)));
	TFile fFit("plots/acceptancetimesefficiency_fit.root","recreate");
	fFit.Write();
	fFit.Close();

	c->cd();
	gStyle->SetOptFit(1011);
	hActimesEf->SetMinimum(2.e-2);
	hActimesEf->SetMaximum(0.6);
	// hActimesEf->GetYaxis()->SetMoreLogLabels();
	// hActimesEf->GetYaxis()->SetNoExponent();
	hActimesEf->Draw("epx0");
	accMM->Draw("SAMES");
	func->Draw("SAMES");
	leg->Draw("SAMES");
	//fguess->Draw("SAMES");
	saveas(c,"plots/acceptancetimesefficiency");
	
	
	_INFO("");

	TH1D* hActimesEfDYrec = (TH1D*)fTemplates->Get("hMass_limit_DYmumu");
	TH1D* hActimesEfDYtru = (TH1D*)fTemplates->Get("hMass_limit_DYmumu_truth");
	TH1D* hActimesEfDYrec_chop = hChopper(hActimesEfDYrec,9);
	TH1D* hActimesEfDYtru_chop = hChopper(hActimesEfDYtru,9);
	double nDYrec = Sum(hActimesEfDYrec_chop,true,true);
	double nDYtru = Sum(hActimesEfDYtru,true,true);
	double DYacc = nDYrec/nDYtru;
	double DYaccErr = binomialError(nDYrec,nDYtru);
	_INFO("Nrec_DY = "+_s(nDYrec));
	_INFO("Ntru_DY = "+_s(nDYtru));
	_INFO("DY acceptance = "+_s(DYacc)+" +- "+_s(DYaccErr));
	// TString name = (TString)hActimesEfDYrec->GetName();
	TString name = "acceptancetimesefficiency_DYmumu_TruRecChop";
	savecnv(name, hActimesEfDYrec, hActimesEfDYrec_chop, hActimesEfDYtru);
}
