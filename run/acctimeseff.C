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

void savecnv(TString name, TH1D* hOrig, TH1D* hChop, TH1D* hTru)
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
	c->SaveAs("plots/"+name+"_test.png");
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
	
	TFile* fTemplates = new TFile("plots/ZP_templates.root","READ");
	
	TObjArray* toarr_recon = new TObjArray();
	toarr_recon->Read("template");
	
	TObjArray* toarr_truth = new TObjArray();
	toarr_truth->Read("truth_template");
	
	Double_t minPoleMass = 0.13; // TeV
	Double_t maxPoleMass = 3.00; // TeV
	
	unsigned const int arraysize = (unsigned int)toarr_recon->GetSize();
	Double_t actimesef[arraysize];
	Double_t actimeseferr[arraysize];
	Double_t bsmmass[arraysize];
	
	
	TCanvas* c = new TCanvas("c","c", 600, 400);
	c->SetLogy();
	c->cd();
	c->Draw();
	
	TH1D* hActimesEf = new TH1D("hActimesEf","Acceptance #times Efficiency vs. the pole mass;m_{BSM} TeV;Acceptance #times Efficiency",arraysize,minPoleMass,maxPoleMass);
	hActimesEf->SetMarkerStyle(24);
	hActimesEf->SetMarkerSize(0.8);
	
	for(unsigned int t=0 ; t<arraysize ; t++)
	{
		TH1D* hRec = (TH1D*)(TObjArray*)toarr_recon->At(t);
		_DEBUG((string)hRec->GetName());
		TH1D* hTru = (TH1D*)(TObjArray*)toarr_truth->At(t);
		_DEBUG((string)hTru->GetName());
		
		TH1D* hRec_chop = hChopper(hRec,9);
		// TH1D* hRec_zero = hZeroize(hRec,9);
		// for(int i=0 ; i<20 ; i++)
		// {
			// if(hRec_zero->GetBinContent(i)>0.) { cout << "1st bin = " << hRec_zero->GetBinLowEdge(i) << endl; break; }
		// }
		// for(int i=0 ; i<20 ; i++)
		// {
			// if(hRec_chop->GetBinContent(i)>0.) { cout << "1st bin = " << hRec_chop->GetBinLowEdge(i) << endl; break; }
		// }
		// cout << "last bin = " << hRec_chop->GetBinLowEdge(hRec_chop->GetNbinsX()) + hRec_chop->GetBinWidth(hRec_chop->GetNbinsX()) << endl;
		
		Double_t sum_rec = Sum(hRec_chop,false,true); // add also overflow
		Double_t sum_tru = Sum(hTru,true,true); // add also underflow and overflow
		
		actimesef[t]    = (sum_tru>0.) ? sum_rec/sum_tru : -1.;
		actimeseferr[t] = (sum_tru>0.) ? binomialError(sum_rec,sum_tru) : 0.;
		bsmmass[t]      = 0.04*t + 0.13;// [TeV/c^2];
		
		Int_t bin = hActimesEf->FindBin(bsmmass[t]);
		hActimesEf->SetBinContent(bin,actimesef[t]);
		hActimesEf->SetBinError(bin,actimeseferr[t]);
		
		TString name = (TString)hRec->GetName();
		//savecnv(name, hRec, hRec_chop, hTru);
	}
	
	double sigma   = 0.;
	double average = getYaverage(hActimesEf,sigma);
	
	_INFO("BSM averaged acceptance = "+_s(average)+" +- "+_s(sigma));
	
	TF1* accMM= new TF1("accMM","pol1",minPoleMass,maxPoleMass);
	// accMM->SetParameters(0.455201,-0.0114039);
	accMM->SetParameters(0.4,-0.0114039);
	accMM->SetLineColor(kRed);
	accMM->SetLineWidth(1);
	
	c->cd();
	hActimesEf->SetMinimum(1.e-2);
	hActimesEf->Draw("e1x0");
	accMM->Draw("SAMES");
	saveas(c,"plots/acceptancetimesefficiency");
	
	TH1D* hActimesEfDYrec = (TH1D*)fTemplates->Get("hMass_1d_full_DYmumu");
	TH1D* hActimesEfDYtru = (TH1D*)fTemplates->Get("hMass_1d_full_DYmumu_truth");
	TH1D* hActimesEfDYrec_chop = hChopper(hActimesEfDYrec,9);
	TH1D* hActimesEfDYtru_chop = hChopper(hActimesEfDYtru,9);
	double nDYrec = Sum(hActimesEfDYrec_chop,true,true);
	double nDYtru = Sum(hActimesEfDYtru,true,true);
	double DYacc = nDYrec/nDYtru;
	double DYaccErr = binomialError(nDYrec,nDYtru);
	_INFO("Nrec_DY = "+_s(nDYrec));
	_INFO("Ntru_DY = "+_s(nDYtru));
	_INFO("DY acceptance = "+_s(DYacc)+" +- "+_s(DYaccErr));
	TString name = (TString)hActimesEfDYrec->GetName();
	savecnv(name, hActimesEfDYrec, hActimesEfDYrec_chop, hActimesEfDYtru);
}
