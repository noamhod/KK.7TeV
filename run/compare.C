#include "/srv01/tau/hod/z0analysis-tests/z0analysis-r170/include/rawStd.h"
#include "/srv01/tau/hod/z0analysis-tests/z0analysis-r170/include/rawROOT.h"
#include "/srv01/tau/hod/z0analysis-tests/z0analysis-r170/include/logs.h"
#include "/srv01/tau/hod/z0analysis-tests/z0analysis-r170/include/types.h"
#include "/srv01/tau/hod/z0analysis-tests/z0analysis-r170/include/style.h"
#include "/srv01/tau/hod/z0analysis-tests/z0analysis-r170/include/histos.h"

void compare()
{
	msglvl[DBG] = SILENT;
	msglvl[INF] = VISUAL;
	msglvl[WRN] = VISUAL;
	msglvl[ERR] = VISUAL;
	msglvl[FAT] = VISUAL;

	TDirectory* oldDir = gDirectory;

	style();

	TFile* f2ds = NULL;
	TFile* f2d  = NULL;
	TH2D* h2ds  = NULL;
	TH2D* h2d   = NULL;
	TH1D* h1s   = NULL;
	TH1D* h1    = NULL;
	TH1D* h1dy  = NULL;

	Int_t g4bin = 50;
	TString model = "ZP";

	int imassmin = 330;
	int imassmax = 4930;
	int dimass   = 100;
	for(int imass=imassmin ; imass<=imassmax ; imass+=dimass)
	{
		TString mass = (TString)_s(imass);
		_INFO("enter "+(string)mass);

		TString modeltmp = (model=="ZP") ? "P" : "KK";

		oldDir->cd();
		f2ds = new TFile("~yiftahsi/KK_analysis_t301/2dtemplates_FEB1/templates2d_Xmass"+mass+".root","READ");
		h2ds = (TH2D*)f2ds->Get("h2"+model+"/Z"+modeltmp+"_mXp"+mass)->Clone();

		f2d  = new TFile("~yiftahsi/KK_analysis_t301/2dtemplates_FEB2/templates2d_Xmass"+mass+".root","READ");
		h2d = (TH2D*)f2d->Get("h2"+model+"/Z"+modeltmp+"_mXp"+mass)->Clone();
                oldDir->cd();

		//------------------------------------------------------------
		const Int_t nbins = h2d->GetNbinsX();
		Double_t bins[nbins+1];
		TAxis* xaxis = (TAxis*)h2d->GetXaxis();
		for(int i=0 ; i<nbins ; i++) bins[i] = xaxis->GetBinLowEdge(i+1);
		bins[nbins] = xaxis->GetBinUpEdge(nbins);
		//------------------------------------------------------------
		
		Double_t g4 = h2d->GetYaxis()->GetBinLowEdge(g4bin);
		TString g = (TString)_s(sqrt(sqrt(g4)),2);
	
		TString modelname = (model=="ZP") ? "Z'" : "KK";
	
		h1s  = new TH1D(mass+"_subtracted","g="+g+", m_{"+modelname+"} = "+mass+" GeV;m_{ee} TeV;Events",nbins,bins);
		h1   = new TH1D(mass+"_inamplitude","g="+g+", m_{"+modelname+"} = "+mass+" GeV;m_{ee} TeV;Events",nbins,bins);
		h1dy = new TH1D(mass+"_dy","g="+g+", m_{"+modelname+"} = "+mass+" GeV;m_{ee} TeV;Events",nbins,bins);
		for(Int_t bin=0 ; bin<=nbins+1 ; bin++)
		{
			h1s->SetBinContent(bin, h2ds->GetBinContent(bin,g4bin));
			h1->SetBinContent(bin, h2d->GetBinContent(bin,g4bin));
			h1dy->SetBinContent(bin, h2d->GetBinContent(bin,1));
		}

		TLegend* leg = new TLegend(0.55,0.72,0.85,0.85,NULL,"brNDC");
		leg->SetFillStyle(4000); //will be transparent
		leg->SetFillColor(0);
		leg->SetTextFont(42);
		
		TCanvas* c = new TCanvas("c"+mass,"c"+mass,600,400);
		c->Draw();
		c->cd();
		c->SetTicks(1,1);
		c->SetLogy();
		c->SetLogx();
		c->SetGridy();	
		c->cd();

		double ymin = getYmin(h1s);
		ymin = (getYmin(h1dy)<ymin) ? getYmin(h1dy): ymin;
		h1dy->SetMinimum( ymin*0.1);
		TLine* l = new TLine(0.12805,h1dy->GetMinimum(),0.12805,h1dy->GetMaximum());
		l->SetLineColor(kGreen+2);
		
		h1dy->SetLineColor(kBlue);
		h1dy->SetLineStyle(1);
		h1dy->SetLineWidth(2);
		leg->AddEntry(h1dy,"DY, in-amplitude k_{F}","l");
		h1dy->DrawCopy();

		h1s->SetLineColor(kBlack);
		h1s->SetLineStyle(1);
		h1s->SetLineWidth(2);
		leg->AddEntry(h1s,modelname+", subtracted k_{F}","l");
		h1s->DrawCopy("SAMES");

		h1->SetLineColor(kRed);
		h1->SetLineStyle(3);
		h1->SetLineWidth(2);
		leg->AddEntry(h1,modelname+", in-amplitude k_{F}","l");
		h1->DrawCopy("SAMES");
		l->Draw("SAMES");
		leg->Draw("SAMES");
	
		_INFO("done "+(string)mass);

		c->RedrawAxis();
		c->Update();
		g.ReplaceAll(".","");
		if(imass==imassmin)      c->SaveAs("kfactors_g"+model+g+".pdf(");
		else if(imass==imassmax) c->SaveAs("kfactors_g"+model+g+".pdf)");
		else                     c->SaveAs("kfactors_g"+model+g+".pdf");
	}
}
