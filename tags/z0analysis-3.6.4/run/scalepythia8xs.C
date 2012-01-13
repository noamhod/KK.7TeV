#include "../include/rawStd.h"
#include "../include/rawROOT.h"
#include "../include/types.h"
#include "../include/logs.h"
#include "../include/style.h"
#include "../include/histos.h"

void scalepythia8xs()
{
	msglvl[DBG] = SILENT;
	msglvl[INF] = VISUAL;
	msglvl[WRN] = VISUAL;
	msglvl[ERR] = VISUAL;
	msglvl[FAT] = VISUAL;

	style();
	
	// TFile* fhistos = new TFile("plots/mcdata_histograms_noData_noZpeak_noPUrw_noEWkF_noEWkFsig_noQCDkF.root","READ");
	TFile* fhistos = new TFile("plots/mcdata_histograms_noData_noZpeak_fastDY_smallDY_noPUrw_noEWkF_noEWkFsig_noQCDkF_noZpTrw_noCoupScale.root","READ");
	
	TLegend* leg = new TLegend(0.3,0.65,0.90,0.8,NULL,"brNDC");
	leg->SetFillStyle(4000); //will be transparent
	leg->SetFillColor(0);
	leg->SetTextFont(42);
	
	bool isKK = false;
	
	TH1D* hDY       = NULL;
	TH1D* hTemplate = NULL;
	TH1D* hPythia8  = NULL;
	
	if(isKK)
	{
		hDY       = (TH1D*)fhistos->Get("hMassDYmumu_truth")->Clone();
		hTemplate = (TH1D*)fhistos->Get("hMassKK2000_template_truth")->Clone();
		hPythia8  = (TH1D*)fhistos->Get("hMassExtraDimsTEV_m2000_truth")->Clone();
		leg->AddEntry(hDY,"#gamma/Z","f");
		leg->AddEntry(hTemplate,"#gamma_{KK}/Z_{KK} 2 TeV Template","l");
		leg->AddEntry(hPythia8,"#gamma_{KK}/Z_{KK} 2 TeV Pythia8 #times f_{6/8} #times 2","f");
	}
	else
	{
		hDY       = (TH1D*)fhistos->Get("hMassDYmumu_truth")->Clone();
		hTemplate = (TH1D*)fhistos->Get("hMassZprime_SSM2000_template_truth")->Clone();
		hPythia8  = (TH1D*)fhistos->Get("hMassZprime_SSM_m2000_truth")->Clone();
		leg->AddEntry(hDY,"#gamma/Z","f");
		leg->AddEntry(hTemplate,"Z'_{SSM} 2 TeV Template","l");
		leg->AddEntry(hPythia8,"Z'_{SSM} 2 TeV Pythia8 #times f_{6/8} #times 2","f");
	}
	
	hTemplate->SetLineColor(kBlue);
	hPythia8->SetLineColor(hPythia8->GetFillColor());
	hPythia8->SetLineStyle(5);
	hPythia8->SetFillColor(0);
	
	
	TCanvas* c = new TCanvas("c","c", 600, 400);
	c->SetLogy();
	c->SetLogx();
	c->SetTicks(1,1);
	c->cd();
	c->Draw();
	
	for(Int_t b=0 ; b<=hPythia8->GetNbinsX()+1 ; b++)
	{	
		Double_t mass = hPythia8->GetBinCenter(b);
		
		double scalef = 1.;
		if     (mass<75.) continue;
		else if(mass>=75.   &&  mass<120.)  scalef = 0.799352/0.7089;
		else if(mass>=120.  &&  mass<450.)  scalef = 0.0089152/0.008045;
		else if(mass>=450.  &&  mass<850.)  scalef = 0.0000475465/0.00004015;
		else if(mass>=850.  &&  mass<1300.) scalef = 0.00000259223/0.000002126;
		else if(mass>=1300. &&  mass<1800.) scalef = 0.000000245112/0.000000189;
		else if(mass>=1800. &&  mass<2300.) scalef = 0.0000000272204/0.00000001809;
		else if(mass>=2300. &&  mass<2800.) scalef = 0.00000000361361/0.000000002034;
		else if(mass>=2800. &&  mass<3300.) scalef = 0.000000000504288/0.0000000002361;
		else if(mass>=3300.)                scalef = 0.0000000000730056/0.00000000002798;
		else _FATAL("no scale for this mass -> "+_s(mass));
		
		Double_t pythia8 = hPythia8->GetBinContent(b);
		hPythia8->SetBinContent(b, pythia8*scalef*2);
	}
	
	TString name = (isKK) ? "scalepythia8KKxs" : "scalepythia8ZPxs";

	c->cd();
	hDY->Draw();
	hPythia8->Draw("SAMES");
	hTemplate->Draw("SAMES");
	leg->Draw("SAMES");
	saveas(c,"plots/"+name);
}
