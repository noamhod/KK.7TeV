/////////////////////////////////////////////////////////////
// USAGE ////////////////////////////////////////////////////
// broot hstack.C++ --ftype=noPUrw --htype=Mass --istru=0 ///
/////////////////////////////////////////////////////////////


#include "../include/rawStd.h"
#include "../include/rawROOT.h"
#include "../include/types.h"
#include "../include/logs.h"
//#include "../include/style.h"
#include "../include/histos.h"
#include "../include/units.h"
#include "../src/AtlasStyle.C"

#define VERBOSEARGS

void style()
{
	gROOT->Reset();
	gROOT->ForceStyle();
	gROOT->LoadMacro("../src/AtlasStyle.C");
	SetAtlasStyle();
}

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
	
	// flags
	bool isLogx      = (htype.Contains("Mass")) ? true : false;
	bool isLogy      = (htype.Contains("Mass") || htype.Contains("pT") || htype.Contains("QT") || htype.Contains("Isolation")) ? true : false;
	bool doSignals   = ((htype.Contains("Mass") || htype.Contains("pT")) && !htype.Contains("Subleading") && !htype.Contains("Numbers")) ? true : false;
	bool isIsolation = (htype.Contains("Isolat")) ? true : false;
	TString QCD      = (isIsolation) ? "jjmu15X" : "QCD";
	TString legQCD   = (isIsolation) ? "QCD (MC)" : "QCD";
	if(isIsolation) doSignals = false;
	
	TString fname = "plots/mcdata_histograms_"+ftype+".root";
	TFile* fhistos = new TFile(fname,"READ");
	TH1D* htmp;
	
	TString titles = (TString)(((TH1D*)fhistos->Get("h"+htype+"DYmumu"+truth))->GetTitle());
	titles += ";" + (TString)(((TH1D*)fhistos->Get("h"+htype+"DYmumu"+truth))->GetXaxis()->GetTitle());
	titles += ";" + (TString)(((TH1D*)fhistos->Get("h"+htype+"DYmumu"+truth))->GetYaxis()->GetTitle());
	THStack* backgounds = new THStack("hs_"+htype+"_"+ftype,titles);
	
	
	// MC sum of backgrounds
	TH1D* hMCsum = (TH1D*)fhistos->Get("h"+htype+"DYmumu"+truth)->Clone();
	if(htype.Contains("Subleading"))
		if(htype=="pTSubleading")  hMCsum->GetXaxis()->SetTitle("p_{T}^{subleading} GeV");
		if(htype=="EtaSubleading") hMCsum->GetXaxis()->SetTitle("#eta^{subleading}");
		if(htype=="PhiSubleading") hMCsum->GetXaxis()->SetTitle("#phi^{subleading}");
	hMCsum->Reset();
	hMCsum->SetName("h"+htype+"MCsum"+truth);
	
	TH1D* hMCsumNODY = (TH1D*)fhistos->Get("h"+htype+"DYmumu"+truth)->Clone();
		if(htype=="pTSubleading")  hMCsumNODY->GetXaxis()->SetTitle("p_{T}^{subleading} GeV");
		if(htype=="EtaSubleading") hMCsumNODY->GetXaxis()->SetTitle("#eta^{subleading}");
		if(htype=="PhiSubleading") hMCsumNODY->GetXaxis()->SetTitle("#phi^{subleading}");
	hMCsumNODY->Reset();
	hMCsumNODY->SetName("h"+htype+"MCsumNODY"+truth);
	
	// BACKGROUNDS
	TH1D* hQCD  = (TH1D*)fhistos->Get("h"+htype+QCD+truth)->Clone();
		if(htype=="pTSubleading")  hQCD->GetXaxis()->SetTitle("p_{T}^{subleading} GeV");
		if(htype=="EtaSubleading") hQCD->GetXaxis()->SetTitle("#eta^{subleading}");
		if(htype=="PhiTSubleading") hQCD->GetXaxis()->SetTitle("#phi^{subleading}");
	// if(isIsolation) hQCD->Scale(2.);
	hQCD->SetFillColor(kYellow-9);
	backgounds->Add(hQCD);
	hMCsum->Add(hQCD);
	hMCsumNODY->Add(hQCD);
	
	TH1D* hWjets = (TH1D*)fhistos->Get("h"+htype+"W+jets"+truth)->Clone();
		if(htype=="pTSubleading")  hWjets->GetXaxis()->SetTitle("p_{T}^{subleading} GeV");
		if(htype=="EtaSubleading") hWjets->GetXaxis()->SetTitle("#eta^{subleading}");
		if(htype=="PhiSubleading") hWjets->GetXaxis()->SetTitle("#phi^{subleading}");
	hWjets->SetFillColor(kGreen-3);
	backgounds->Add(hWjets);
	hMCsum->Add(hWjets);
	hMCsumNODY->Add(hWjets);
	
	TH1D* hTTbar = (TH1D*)fhistos->Get("h"+htype+"TTbar"+truth)->Clone();
		if(htype=="pTSubleading")  hTTbar->GetXaxis()->SetTitle("p_{T}^{subleading} GeV");
		if(htype=="EtaSubleading") hTTbar->GetXaxis()->SetTitle("#eta^{subleading}");
		if(htype=="PhiSubleading") hTTbar->GetXaxis()->SetTitle("#phi^{subleading}");
	hTTbar->SetFillColor(kRed+1);
	backgounds->Add(hTTbar);
	hMCsum->Add(hTTbar);
	hMCsumNODY->Add(hTTbar);
	
	TH1D* hDiboson = (TH1D*)fhistos->Get("h"+htype+"Diboson"+truth)->Clone();
		if(htype=="pTSubleading")  hDiboson->GetXaxis()->SetTitle("p_{T}^{subleading} GeV");
		if(htype=="EtaSubleading") hDiboson->GetXaxis()->SetTitle("#eta^{subleading}");
		if(htype=="PhiSubleading") hDiboson->GetXaxis()->SetTitle("#phi^{subleading}");
	hDiboson->SetFillColor(kOrange);
	backgounds->Add(hDiboson);
	hMCsum->Add(hDiboson);
	hMCsumNODY->Add(hDiboson);
	
	TH1D* hDY = (TH1D*)fhistos->Get("h"+htype+"DYmumu"+truth)->Clone();
		if(htype=="pTSubleading")  hDY->GetXaxis()->SetTitle("p_{T}^{subleading} GeV");
		if(htype=="EtaSubleading") hDY->GetXaxis()->SetTitle("#eta^{subleading}");
		if(htype=="PhiSubleading") hDY->GetXaxis()->SetTitle("#phi^{subleading}");
	hDY->SetFillColor(kAzure-9);
	backgounds->Add(hDY);
	hMCsum->Add(hDY);	
	
	
	// data
	TH1D* hData = (TH1D*)fhistos->Get("h"+htype+"Data")->Clone();
		if(htype=="pTSubleading")  hData->GetXaxis()->SetTitle("p_{T}^{subleading} GeV");
		if(htype=="EtaSubleading") hData->GetXaxis()->SetTitle("#eta^{subleading}");
		if(htype=="PhiSubleading") hData->GetXaxis()->SetTitle("#phi^{subleading}");
	hData->SetLineWidth(2);
	hData->SetMarkerStyle(20);
	TGraphAsymmErrors* gaData = (TGraphAsymmErrors*)(poisson(hData))->Clone("");
	
	// signals
	TList* signals = new TList;
	TMapTSTS signalNames;
	TH1D* ZP1500 = NULL;
	TH1D* ZP1750 = NULL;
	TH1D* ZP2000 = NULL;
	if(!isIsolation  &&  doSignals)
	{
		ZP1500 = (TH1D*)fhistos->Get("h"+htype+"Zprime_SSM1500_template"+truth);
		ZP1500->Add(hMCsumNODY);
			if(htype=="pTSubleading")  ZP1500->GetXaxis()->SetTitle("p_{T}^{subleading} GeV");
			if(htype=="EtaSubleading") ZP1500->GetXaxis()->SetTitle("#eta^{subleading}");
			if(htype=="PhiSubleading") ZP1500->GetXaxis()->SetTitle("#phi^{subleading}");
		ZP1500->SetLineColor(kRed+2);
		signals->Add(ZP1500);
		signalNames.insert(make_pair((TString)ZP1500->GetName(),"Z'_{SSM} (1500 GeV)"));
		ZP1750 = (TH1D*)fhistos->Get("h"+htype+"Zprime_SSM1750_template"+truth);
		ZP1750->Add(hMCsumNODY);
			if(htype=="pTSubleading")  ZP1750->GetXaxis()->SetTitle("p_{T}^{subleading} GeV");
			if(htype=="EtaSubleading") ZP1750->GetXaxis()->SetTitle("#eta^{subleading}");
			if(htype=="PhiSubleading") ZP1750->GetXaxis()->SetTitle("#phi^{subleading}");
		ZP1750->SetLineColor(kGreen+2);
		signals->Add(ZP1750);
		signalNames.insert(make_pair((TString)ZP1750->GetName(),"Z'_{SSM} (1750 GeV)"));
		ZP2000 = (TH1D*)fhistos->Get("h"+htype+"Zprime_SSM2000_template"+truth);
		ZP2000->Add(hMCsumNODY);
			if(htype=="pTSubleading")  ZP2000->GetXaxis()->SetTitle("p_{T}^{subleading} GeV");
			if(htype=="EtaSubleading") ZP2000->GetXaxis()->SetTitle("#eta^{subleading}");
			if(htype=="PhiSubleading") ZP2000->GetXaxis()->SetTitle("#phi^{subleading}");
		ZP2000->SetLineColor(kViolet+2);
		signals->Add(ZP2000);
		signalNames.insert(make_pair((TString)ZP2000->GetName(),"Z'_{SSM} (2000 GeV)"));
	}
	
	_INFO("");

	// legend
	TLegend* leg = new TLegend(0.70,0.55,0.87,0.92);
	leg->SetFillStyle(4000); //will be transparent
	leg->SetFillColor(0);
	// leg->SetTextFont(42);
	leg->SetTextSize(0.04);
	leg->AddEntry(hData,"Data 2011","P");
	leg->AddEntry(hDY,"Z/#gamma*","f");
	leg->AddEntry(hDiboson,"Diboson","f");
	leg->AddEntry(hTTbar,"t#bar{t}","f");
	leg->AddEntry(hWjets,"W+jets","f");
	leg->AddEntry(hQCD,legQCD,"f");
	if(!isIsolation  &&  doSignals)
	{
		TIter next_sig(signals);
		while(( htmp=(TH1D*)next_sig() )!=NULL)
		{
			cout << "Adding to legend " << ((TH1D*)htmp)->GetName() << endl;
			TString signame = signalNames[(TString)htmp->GetName()];
			leg->AddEntry(htmp,signame,"F");
		}
	}


	
	// text
	TLatex *t = new TLatex();
	t->SetNDC(1);
	t->SetTextAlign(13);
	t->SetTextSize(0.05);
	t->SetTextColor(kBlack);
	
	
	
	// draw !
	TCanvas* c = new TCanvas("Canvas","Canvas",10,10,800,600); 
	c->SetTicks(1,1);
	if(isLogx) c->SetLogx();
	if(isLogy) c->SetLogy();
	c->cd();
	c->Draw();
	float maximum = 1.5*hDY->GetMaximum();
	float minimum = 0.001;
	if(isLogy) maximum = 20*hDY->GetMaximum();
	if(isIsolation)
	{
		minimum = (htype.Contains("Isolation")) ? 10. : minimum;
		minimum = (htype.Contains("Mass"))      ? 1.  : minimum;
	}
	if(htype.Contains("pT"))
	{
		minimum = 0.02;
		maximum = 2.e7;
	}
	TIter next_bg((TList*)backgounds->GetHists());
	while(( htmp=(TH1D*)next_bg() )!= NULL)
	{
		_INFO("Adding "+(string)((TH1D*)htmp)->GetName());
		htmp->SetMinimum(minimum);
		htmp->SetMaximum(maximum);
		htmp->GetXaxis()->SetMoreLogLabels(1);
		htmp->GetXaxis()->SetNoExponent();
		// htmp->SetYTitle("Events");
		// htmp->SetXTitle("m_{#mu#mu} GeV");
	}
	backgounds->SetMinimum(minimum);
	backgounds->SetMaximum(maximum);
	backgounds->Draw();
	if(!isIsolation  &&  doSignals)
	{
		TIter next_sig(signals);
		while(( htmp=(TH1D*)next_sig() )!=NULL)
		{
			cout << "Drawing " << ((TH1D*)htmp)->GetName() << endl;
			htmp->SetMinimum(minimum);
			htmp->SetMaximum(maximum);
			htmp->GetXaxis()->SetMoreLogLabels(1);
			htmp->GetXaxis()->SetNoExponent();
			// htmp->SetYTitle("Events");
			// htmp->SetXTitle("m_{#mu#mu} GeV");
			htmp->Draw("SAMES");
		}
	}
	gaData->Draw("psame");  // "esame" or "psame" (p for Poisson)
	leg->Draw("SAMES");
	TString atlasit = "#font[72]{ATLAS}";
	// TString atlaspr = "#font[42]{preliminary}";
	TString atlaspr = "#font[42]{work in progress}";
	TString ppcme   = "#sqrt{s} = 7 TeV";
	TString lumi    = "#int L dt = "+(TString)_s(luminosity,2)+" fb^{-1}";
	
	
	TString atlas1 = atlasit+" "+atlaspr;
	TString atlas2 = "";
	TString atlas3 = ppcme;
	TString atlas4 = lumi;
	// t->DrawLatex(0.400,0.90,atlas1);
	t->DrawLatex(0.33,0.90,atlas1);
	t->DrawLatex(0.440,0.85,atlas2);
	t->DrawLatex(0.40,0.80,atlas3);
	t->DrawLatex(0.40,0.70,atlas4);
	c->RedrawAxis();
	TString name = "hstack_"+htype+"_"+ftype;
	saveas(c,"plots/"+name);
	
	
	
	// RATIO PLOT
	Double_t ymin = (isIsolation) ? 20 : -1;
	Double_t ymax = -1;
	ymin = (htype=="MassAntiIsolated") ? 2.e-2 : -1;
	ymax = (htype=="MassAntiIsolated") ? hQCD->GetMaximum()*1.5 : -1;
	ymin = (htype=="Mass") ? 1.e-3 : -1;
	ymax = (htype=="Mass") ? hDY->GetMaximum()*1.5 : -1;
	
	TLegend* legR          = NULL;
	if(signals->GetSize()==0) legR = new TLegend(0.67,0.38,0.93,0.93,NULL,"brNDC");
	else                      legR = new TLegend(0.67,0.38,0.93,0.93,NULL,"brNDC");
	legR->SetFillStyle(4000); //will be transparent
	legR->SetFillColor(0);
	// legR->SetTextFont(42);
	leg->SetTextSize(0.04);
	legR->AddEntry(hData,"Data 2011","P");
	legR->AddEntry(hDY,"Z/#gamma*","f");
	legR->AddEntry(hDiboson,"Diboson","f");
	legR->AddEntry(hTTbar,"t#bar{t}","f");
	legR->AddEntry(hWjets,"W+jets","f");
	legR->AddEntry(hQCD,legQCD,"f");
	if(!isIsolation  &&  doSignals)
	{
		TIter next_sig(signals);
		while(( htmp=(TH1D*)next_sig() )!=NULL)
		{
			cout << "Drawing " << ((TH1D*)htmp)->GetName() << endl;
			htmp->SetMinimum(minimum);
			htmp->SetMaximum(maximum);
			htmp->GetXaxis()->SetMoreLogLabels(1);
			htmp->GetXaxis()->SetNoExponent();
			// htmp->SetYTitle("Events");
			// htmp->SetXTitle("m_{#mu#mu} GeV");
			TString signame = signalNames[(TString)htmp->GetName()];
			legR->AddEntry(htmp,signame,"F");
		}
	}
	
	
	Double_t xtxtmin = 0.;
	Double_t xtxtmax = 0.;
	if(signals->GetSize()!=0)
	{
		xtxtmin = 0.2;//0.3;
		xtxtmax = 0.6;//0.6;
	}
	else
	{
		xtxtmin = 0.3;//0.42;
		xtxtmax = 0.7;//0.6;
	}
	TText* txt = NULL;
	TPaveText* pvtxt_atlas = new TPaveText(xtxtmin,0.5,xtxtmax,0.85,"brNDC");
	pvtxt_atlas->SetFillStyle(4000); //will be transparent
	pvtxt_atlas->SetFillColor(0);
	pvtxt_atlas->SetTextFont(42);
	txt = pvtxt_atlas->AddText(atlasit+" "+atlaspr);
	txt = pvtxt_atlas->AddText(ppcme);
	txt = pvtxt_atlas->AddText( lumi );
	
	name = name + "_ratio";
	TCanvas* cR = (TCanvas*)(stackratio(name,hData,backgounds,signals,legR,pvtxt_atlas,"Data/#SigmaMC",isLogx,isLogy,ymin,ymax))->Clone("");
	saveas(cR,"plots/"+name, false);
	
	/*
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
		
	// TLegend* leg = NULL;
	// if(hKKtemplate!=NULL && hZPtemplate!=NULL) leg = new TLegend(0.58,0.50,0.82,0.85,NULL,"brNDC");
	// else                                       leg = new TLegend(0.65,0.55,0.82,0.85,NULL,"brNDC");
	// leg->SetFillStyle(4000); //will be transparent
	// leg->SetFillColor(0);
	// leg->SetTextFont(42);
	TLegend* leg = new TLegend(0.72,0.55,0.89,0.92);
	leg->SetTextSize(0.04);
	leg->SetFillColor(0);
	
	// leg->AddEntry(hData,"Data 2011","EP0");
	leg->AddEntry(hData,"Data 2011","P");
	leg->AddEntry(hDY,"Z/#gamma*","f");
	leg->AddEntry(hDiboson,"Diboson","f");
	leg->AddEntry(hTTbar,"t#bar{t}","f");
	leg->AddEntry(hWjets,"W+jets","f");
	leg->AddEntry(hQCD,QCD,"f");
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
	
	// TCanvas* c = new TCanvas("c","c", 600, 400);
	TCanvas* c = new TCanvas("Canvas","Canvas",10,10,800,600); 
	c->SetTicks(1,1);
	c->cd();
	c->Draw();
	
	TString name = "hstack_"+htype+"_"+ftype;

	c->cd();
	if(htype.Contains("Isolation")) backgounds->SetMinimum(1.);
	if(isIsolation) backgounds->SetMinimum(10.);
	backgounds->Draw(); // Draw("nostack");
	bool isLogx = (htype.Contains("Mass") || htype.Contains("pT") || htype.Contains("QT")) ? true : false;
	if(isLogx)
	{
		c->SetLogx();
		backgounds->GetXaxis()->SetMoreLogLabels();
		backgounds->GetXaxis()->SetNoExponent();
	}
		
	bool isLogy = (htype.Contains("Mass") || htype.Contains("pT") || htype.Contains("QT") || htype.Contains("Isolation")) ? true : false;
	if(isLogy) c->SetLogy();
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
	
	Double_t ymin = (isIsolation) ? 20 : -1;
	Double_t ymax = -1;
	ymin = (htype=="MassAntiIsolated") ? 2.e-2 : -1;
	ymax = (htype=="MassAntiIsolated") ? hQCD->GetMaximum()*1.5 : -1;
	ymin = (htype=="Mass") ? 1.e-3 : -1;
	ymax = (htype=="Mass") ? hDY->GetMaximum()*1.5 : -1;

	TCanvas* cR = (TCanvas*)(stackratio(name,hData,backgounds,signals,leg,pvtxt_lumi,pvtxt_atlas,"Data/#SigmaMC","epx0",isLogx,isLogy,ymin,ymax))->Clone("");
	saveas(cR,"plots/"+name, false);
	*/
}
