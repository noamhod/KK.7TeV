/////////////////////////////////////////////////////////////
// USAGE ////////////////////////////////////////////////////
// broot hstack.C++ --ftype=noPUrw --htype=Mass --istru=0 ///
/////////////////////////////////////////////////////////////


#include "../include/rawStd.h"
#include "../include/rawROOT.h"
#include "../include/types.h"
#include "../include/logs.h"
#include "../include/style.h"
#include "../include/histos.h"
#include "../include/units.h"

#define VERBOSEARGS

TString c2ts(const char* c)
{
	stringstream strm;
	TString str;
	strm << c;
	strm >> str;
	return str;
}

void hstack()
{
	msglvl[DBG] = SILENT;
	msglvl[INF] = VISUAL;
	msglvl[WRN] = VISUAL;
	msglvl[ERR] = VISUAL;
	msglvl[FAT] = VISUAL;

	style();
	
	_INFO("USAGE: broot hstack.C++ --ftype=noPUrw --htype=Mass --istru=0");
	
	for(int i=0 ; i<gApplication->Argc() ; i++)
	{
		#ifdef VERBOSEARGS
			printf("Arg  %d:  %s\n",i,gApplication->Argv(i));
		#endif
	}
	if(gApplication->Argc()>10) _FATAL("gApplication->Argc()="+_s(gApplication->Argc()));
	TString ftype = "";
	TString htype = "";
	Bool_t  istru = "";
	TString truth = "";
	for(int i=0 ; i<gApplication->Argc() ; i++)
	{
		// if((TString)gApplication->Argv(i)=="--ftype")   ftype   = c2ts(gApplication->Argv(i+1));
		// if((TString)gApplication->Argv(i)=="--htype")   htype   = c2ts(gApplication->Argv(i+1));
		// if((TString)gApplication->Argv(i)=="--istruth") istruth = (c2ts(gApplication->Argv(i+1))==1) ? true : false;
		
		if(((TString)gApplication->Argv(i)).Contains("--ftype=")) ftype = ((TString)gApplication->Argv(i)).ReplaceAll("--ftype=","");
		if(((TString)gApplication->Argv(i)).Contains("--htype=")) htype = ((TString)gApplication->Argv(i)).ReplaceAll("--htype=","");
		if(((TString)gApplication->Argv(i)).Contains("--istru=")) istru = (((TString)gApplication->Argv(i)).ReplaceAll("--istru=","")=="1") ? true : false;
	}
	truth = (istru) ? "_truth" : "";
	
	_INFO("ftype="+(string)ftype);
	_INFO("htype="+(string)htype);
	_INFO("istruth="+_s(istru));
	
	
	// TString suffix = "_noData_noZpeak_noPUrw_noEWkF_noEWkFsig_noQCDkF";
	// TString suffix = "_noData_noZpeak_fastDY_smallDY_noPUrw_noEWkF_noEWkFsig_noQCDkF_noZpTrw_noCoupScale";
	// TString suffix = "";
	// TString suffix = "_noPUrw";
	// TFile* fhistos = new TFile("plots/mcdata_histograms"+suffix+".root","READ");
	TString fname = "plots/mcdata_histograms_"+ftype+".root";
	TFile* fhistos = new TFile(fname,"READ");
	
	TString titles = (TString)(((TH1D*)fhistos->Get("h"+htype+"DYmumu"+truth))->GetTitle());
	titles += ";" + (TString)(((TH1D*)fhistos->Get("h"+htype+"DYmumu"+truth))->GetXaxis()->GetTitle());
	titles += ";" + (TString)(((TH1D*)fhistos->Get("h"+htype+"DYmumu"+truth))->GetYaxis()->GetTitle());
	THStack* backgounds = new THStack("hs_"+htype+"_"+ftype,titles);
	
	TH1D* hMCsum = (TH1D*)fhistos->Get("h"+htype+"DYmumu"+truth)->Clone();
	hMCsum->Reset();
	hMCsum->SetName("h"+htype+"MCsum"+truth);
	
	TH1D* hTTbar   = (TH1D*)fhistos->Get("h"+htype+"TTbar"+truth)->Clone();
	backgounds->Add(hTTbar);
	hMCsum->Add(hTTbar);
	TH1D* hDiboson = (TH1D*)fhistos->Get("h"+htype+"Diboson"+truth)->Clone();
	backgounds->Add(hDiboson);
	hMCsum->Add(hDiboson);
	TH1D* hDY      = (TH1D*)fhistos->Get("h"+htype+"DYmumu"+truth)->Clone();
	backgounds->Add(hDY);
	hMCsum->Add(hDiboson);
	
	TH1D* hData     = (TH1D*)fhistos->Get("h"+htype+"Data")->Clone();
	hData->SetLineWidth(2);
	hData->SetMarkerStyle(20);
	TH1D* hKKtemplate = (TH1D*)fhistos->Get("h"+htype+"KK2000_template"+truth);
	if(hKKtemplate!=NULL)
	{
		hKKtemplate = (TH1D*)hKKtemplate->Clone();
		hKKtemplate->SetLineWidth(2);
		hKKtemplate->SetLineColor(kGreen+2);
	}
	TH1D* hZPtemplate = (TH1D*)fhistos->Get("h"+htype+"Zprime_SSM2000_template"+truth);
	if(hZPtemplate!=NULL)
	{
		hZPtemplate = (TH1D*)hZPtemplate->Clone();
		hZPtemplate->SetLineWidth(2);
		hZPtemplate->SetLineColor(kViolet+2); 
	}
	
	
	
	TLegend* leg = NULL;
	if(hKKtemplate!=NULL && hZPtemplate!=NULL) leg = new TLegend(0.58,0.50,0.82,0.85,NULL,"brNDC");
	else                                       leg = new TLegend(0.65,0.55,0.82,0.85,NULL,"brNDC");
	leg->SetFillStyle(4000); //will be transparent
	leg->SetFillColor(0);
	leg->SetTextFont(42);
	leg->AddEntry(hData,"2011 Data","LEP0");
	leg->AddEntry(hDY,"#gamma/Z","f");
	leg->AddEntry(hDiboson,"Diboson","f");
	leg->AddEntry(hTTbar,"t#bar{t}","f");
	if(hKKtemplate!=NULL) leg->AddEntry(hKKtemplate,"#gamma_{KK}/Z_{KK} 2 TeV Template","l");
	if(hZPtemplate!=NULL) leg->AddEntry(hZPtemplate,"Z'_{SSM} 2 TeV Template","l");

	Double_t xtxtmin = 0.;
	Double_t xtxtmax = 0.;
	if(hKKtemplate!=NULL && hZPtemplate!=NULL)
	{
		xtxtmin = 0.4032663;
		xtxtmax = 0.5678392;
	}
	else
	{
		xtxtmin = 0.42;
		xtxtmax = 0.5845729;
	}
	
	TText* txt = NULL;
	TPaveText* pvtxt_atlas = new TPaveText(xtxtmin,0.75,xtxtmax,0.85,"brNDC");
	pvtxt_atlas->SetFillStyle(4000); //will be transparent
	pvtxt_atlas->SetFillColor(0);
	pvtxt_atlas->SetTextFont(42);
	txt = pvtxt_atlas->AddText("#bf{#splitline{#it{ATLAS}}{#scale[0.42]{work in progress}}}");
	
	TPaveText* pvtxt_lumi = new TPaveText(xtxtmin,0.63,xtxtmax,0.738,"brNDC");
	pvtxt_lumi->SetFillStyle(4000); //will be transparent
	pvtxt_lumi->SetFillColor(0);
	TString sLumi = (TString)_s(luminosity,2);
	txt = pvtxt_lumi->AddText( "#intLdt~"+ sLumi +" fb^{-1}" );
	
	
	TCanvas* c = new TCanvas("c","c", 600, 400);
	c->SetTicks(1,1);
	c->cd();
	c->Draw();
	
	TString name = "hstack_"+htype+"_"+ftype;

	c->cd();
	backgounds->Draw(); // Draw("nostack");
	bool isLogxy = (htype.Contains("Mass") || htype.Contains("pT") || htype.Contains("QT")) ? true : false;
	if(isLogxy)
	{
		c->SetLogy();
		c->SetLogx();
		backgounds->GetXaxis()->SetMoreLogLabels();
		backgounds->GetXaxis()->SetNoExponent();
	}
	if(hKKtemplate!=NULL) hKKtemplate->Draw("SAMES");
	if(hZPtemplate!=NULL) hZPtemplate->Draw("SAMES");
	hData->Draw("epx0 SAMES");
	leg->Draw("SAMES");
	pvtxt_atlas->Draw("SAMES");
	pvtxt_lumi->Draw("SAMES");
	saveas(c,"plots/"+name);
	
	name = name + "_ratio";
	TList* signals = NULL;
	if(hKKtemplate!=NULL && hZPtemplate!=NULL)
	{
		signals = new TList;
		signals->Add(hKKtemplate);
		signals->Add(hZPtemplate);
	}
	TCanvas* cR = (TCanvas*)(stackratio(name,hData,backgounds,signals,leg,pvtxt_lumi,pvtxt_atlas,"Data/#sumMC","epx0",isLogxy,isLogxy))->Clone("");
	saveas(cR,"plots/"+name, false);
}
