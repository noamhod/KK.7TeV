//////////////////////////////////////////////////////////////////////
//// usage: root -b -l -q systplot.C++\(36,\"KK\",\"g4\",false\) /////
//////////////////////////////////////////////////////////////////////

#include "../include/rawStd.h"
#include "../include/rawROOT.h"
#include "../include/types.h"
#include "../include/logs.h"
#include "../include/bins.h"
#include "../include/histos.h"
#include "../include/asymgraph.h"
#include "../include/systematics.h"
#include "../include/units.h"
#include "../src/AtlasStyle.C"


using namespace systematics;

void style()
{
	gROOT->Reset();
	gROOT->ForceStyle();
	gROOT->LoadMacro("../src/AtlasStyle.C");
	SetAtlasStyle();
}

inline TH1D* hGeV2TeV(TH1D* hGeV)
{
	const Int_t    nbins = hGeV->GetNbinsX();
	Double_t bins[nbins+1];
	TAxis* xaxis = (TAxis*)hGeV->GetXaxis();
	TAxis* yaxis = (TAxis*)hGeV->GetYaxis();

	for(int i=0 ; i<nbins ; i++) bins[i] = xaxis->GetBinLowEdge(i+1)/1000.;
	bins[nbins] = xaxis->GetBinUpEdge(nbins)/1000.;
	
	TString name   = (TString)hGeV->GetName();
	TString title  = (TString)hGeV->GetTitle();
	TString xtitle = (TString)xaxis->GetTitle();
	TString ytitle = (TString)yaxis->GetTitle();
	
	TH1D* hTeV = new TH1D(name+"_TeV",title+";"+xtitle+";"+ytitle, nbins,bins);
	for(Int_t b=0 ; b<=nbins+1 ; b++) hTeV->SetBinContent(b, hGeV->GetBinContent(b));
	return hTeV;
}

inline TH1D* hTeV2GeV(TH1D* hTeV)
{
	const Int_t    nbins = hTeV->GetNbinsX();
	Double_t bins[nbins+1];
	TAxis* xaxis = (TAxis*)hTeV->GetXaxis();
	TAxis* yaxis = (TAxis*)hTeV->GetYaxis();

	for(int i=0 ; i<nbins ; i++) bins[i] = xaxis->GetBinLowEdge(i+1)*1000.;
	bins[nbins] = xaxis->GetBinUpEdge(nbins)*1000.;
	
	TString name   = (TString)hTeV->GetName();
	TString title  = (TString)hTeV->GetTitle();
	TString xtitle = (TString)xaxis->GetTitle();
	TString ytitle = (TString)yaxis->GetTitle();
	
	TH1D* hGeV = new TH1D(name+"_TeV",title+";"+xtitle+";"+ytitle, nbins,bins);
	for(Int_t b=0 ; b<=nbins+1 ; b++) hGeV->SetBinContent(b, hTeV->GetBinContent(b));
	return hGeV;
}

void zeroizeErrors(TH1D* h)
{
	for(Int_t bin=1 ; bin<=h->GetNbinsX() ; bin++)
	{
		h->SetBinError(bin,0.);
	}
}

TH1D* getTemplate(TString mod="KK",TString mass="1530")
{
	TString gN = "g2";
	TString vs = "v81";
	TFile* fT = new TFile("plots/linearbins/"+gN+"bins/3332st_nominal/"+vs+"/template_nominal_"+mass+"GeV_"+vs+".root","READ");
	_INFO("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
	_INFO("!!!!!!!!!!!!!! note !!!!!!!!!!!!");
	_INFO("!!! reading g"+(string)gN+" !!!!!!!!!!");
	_INFO("!!! reading version "+(string)vs+"!!!");
	_INFO("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
	TObjArray* toar = new TObjArray();
	toar->Read("template"+mod);
	TH1D* templateTeV = (TH1D*)((TH1D*)(TObjArray*)toar->At(0))->Clone();
	for(Int_t bin=1 ; bin<=templateTeV->GetNbinsX() ; bin++)
	{
		templateTeV->SetBinError(bin,0.);
	}
	TH1D* templateGeV = (TH1D*)hTeV2GeV(templateTeV)->Clone();
	return templateGeV;
}

void systplot(unsigned int uiXmass, TString model="KK", TString gN="g4", bool doPlotSignals=false)
{
	msglvl[DBG] = SILENT;
	msglvl[INF] = VISUAL;
	msglvl[WRN] = VISUAL;
	msglvl[ERR] = VISUAL;
	msglvl[FAT] = VISUAL;

	style();
	
	Int_t gNbin = 9; //==> g^4=1 ==> SSM !!!
	TString sXmassGeV = (TString)_s(uiXmass*100.+130.);
	TString sXmassTeV = (TString)_s((uiXmass*100.+130.)*GeV2TeV);
	TString modellabel = (model=="KK") ? model : "Z'_{SSM}";
	
	// BG and data
	TString fBGname = "plots/invariant_mass_hists_comb_250stitch_07052012.root";
	
	TFile* file_bg_data = new TFile(fBGname,"READ");
	TH1D* h_data        = (TH1D*)file_bg_data->Get("mass_plot_data")->Clone("data");
	TH1D* h_bg          = (TH1D*)file_bg_data->Get("mass_plot_sum")->Clone("sumbg");
	TH1D* h_bgnody      = (TH1D*)file_bg_data->Get("mass_plot_dy")->Clone("h_bgnody");
	TH1D* h_dy          = (TH1D*)file_bg_data->Get("mass_plot_dy")->Clone("dy");
	//TH1D* h_wjets       = (TH1D*)file_bg_data->Get("mass_plot_wjets")->Clone("wjets");
	//TH1D* h_qcd         = (TH1D*)file_bg_data->Get("mass_plot_qcd")->Clone("qcd");
	TH1D* h_diboson     = (TH1D*)file_bg_data->Get("mass_plot_dib")->Clone("diboson");
	TH1D* h_ttbar       = (TH1D*)file_bg_data->Get("mass_plot_ttbar")->Clone("ttbar");
	TH1D* h_ttbar_sys   = (TH1D*)file_bg_data->Get("mass_plot_ttbar_sys")->Clone("ttbar_up");
	TH1D* h_diboson_sys = (TH1D*)file_bg_data->Get("mass_plot_dib_sys")->Clone("diboson_up");

	h_data->GetXaxis()->SetTitle("m_{#mu#mu} [GeV]");
	h_bg->GetXaxis()->SetTitle("m_{#mu#mu} [GeV]");
	h_bgnody->GetXaxis()->SetTitle("m_{#mu#mu} [GeV]");
	h_dy->GetXaxis()->SetTitle("m_{#mu#mu} [GeV]");
	h_diboson->GetXaxis()->SetTitle("m_{#mu#mu} [GeV]");
	h_ttbar->GetXaxis()->SetTitle("m_{#mu#mu} [GeV]");

	h_data->GetXaxis()->SetMoreLogLabels(1);
	h_data->GetXaxis()->SetNoExponent();
	h_bg->GetXaxis()->SetMoreLogLabels(1);                
        h_bg->GetXaxis()->SetNoExponent();
	h_bgnody->GetXaxis()->SetMoreLogLabels(1);                
        h_bgnody->GetXaxis()->SetNoExponent();
	h_dy->GetXaxis()->SetMoreLogLabels(1);                
        h_dy->GetXaxis()->SetNoExponent();
	h_diboson->GetXaxis()->SetMoreLogLabels(1);                
        h_diboson->GetXaxis()->SetNoExponent();
	
	_INFO("h_data: "+_s(h_data->GetNbinsX())+":"+_s(h_data->GetBinLowEdge(1))+"->"+_s(h_data->GetXaxis()->GetBinUpEdge(h_data->GetNbinsX())));
	_INFO("h_dy: "+_s(h_dy->GetNbinsX())+":"+_s(h_dy->GetBinLowEdge(1))+"->"+_s(h_dy->GetXaxis()->GetBinUpEdge(h_dy->GetNbinsX())));
	//_INFO("h_wjets: "+_s(h_wjets->GetNbinsX())+":"+_s(h_wjets->GetBinLowEdge(1))+"->"+_s(h_wjets->GetXaxis()->GetBinUpEdge(h_wjets->GetNbinsX())));
	//_INFO("h_qcd: "+_s(h_qcd->GetNbinsX())+":"+_s(h_qcd->GetBinLowEdge(1))+"->"+_s(h_qcd->GetXaxis()->GetBinUpEdge(h_qcd->GetNbinsX())));
	_INFO("h_diboson: "+_s(h_diboson->GetNbinsX())+":"+_s(h_diboson->GetBinLowEdge(1))+"->"+_s(h_diboson->GetXaxis()->GetBinUpEdge(h_diboson->GetNbinsX())));
	_INFO("h_ttbar: "+_s(h_ttbar->GetNbinsX())+":"+_s(h_ttbar->GetBinLowEdge(1))+"->"+_s(h_ttbar->GetXaxis()->GetBinUpEdge(h_ttbar->GetNbinsX())));

	h_bgnody->Reset();
	//h_bgnody->Add( h_wjets );
	//h_bgnody->Add( h_qcd );
	h_bgnody->Add( h_diboson );
	h_bgnody->Add( h_ttbar );

	//h_qcd->SetFillColor(kYellow-9);
	//h_wjets->SetFillColor(kGreen-3);
	h_ttbar->SetFillColor(kRed+1);
	h_diboson->SetFillColor(kOrange);
	h_dy->SetFillColor(kAzure-9);
	

	TH1D* h_tails_up = (TH1D*)h_ttbar_sys->Clone("tails_up");
	h_tails_up->Reset();
	for(Int_t bin=1 ; bin<=h_ttbar_sys->GetNbinsX() ; bin++)
	{
		Double_t err1 = h_ttbar_sys->GetBinError(bin);
		Double_t err2 = h_diboson_sys->GetBinError(bin);
		Double_t val = h_bgnody->GetBinContent(bin);
		Double_t err = sqrt(err1*err1 + err2*err2);
		h_tails_up->SetBinContent(bin,err/val);
	}

	//zeroizeErrors(h_qcd);
	//zeroizeErrors(h_wjets);
	zeroizeErrors(h_ttbar);
	zeroizeErrors(h_diboson);
	zeroizeErrors(h_dy);
	
	THStack* backgrounds = new THStack("hs_mass",";m_{#mu#mu} [GeV];Events");
	//backgrounds->Add(h_qcd);
	//backgrounds->Add(h_wjets);
	backgrounds->Add(h_ttbar);
	backgrounds->Add(h_diboson);
	backgrounds->Add(h_dy);
	
	
	
	
	/////////////////////////////////////////////////////////////////////////////////
	//// for the stack imass histo //////////////////////////////////////////////////
	TH1D* htmp;
	TH1D* hdata = (TH1D*)h_data->Clone();
	hdata->SetLineWidth(2);
	hdata->SetMarkerStyle(20);
	TGraphAsymmErrors* gdata = (TGraphAsymmErrors*)(poisson(hdata))->Clone("");
	gdata->GetXaxis()->SetTitle("m_{#mu#mu} [GeV]");
	gdata->GetXaxis()->SetMoreLogLabels(1);
	gdata->GetXaxis()->SetNoExponent();
	_INFO("");
	////////
	TList* signals = new TList;
	TMapTSTS signalNames;
	TH1D* ZP1530 = NULL;
	TH1D* ZP2030 = NULL;
	TH1D* ZP3030 = NULL;
	TH1D* KK1530 = NULL;
	TH1D* KK2030 = NULL;
	TH1D* KK3030 = NULL;
	if(model=="KK")
	{
		_INFO("");
		signalNames.insert(make_pair("1530","#gamma_{KK}/Z_{KK} (1530 GeV)"));
		KK1530 = (TH1D*)getTemplate("KK","1530")->Clone();
		zeroizeErrors(KK1530);
		KK1530->SetBinContent(1,h_bg->GetBinContent(1));
		KK1530->Add(h_bgnody);
		KK1530->SetLineWidth(2);
		KK1530->SetLineColor(kRed+2);
		KK1530->GetXaxis()->SetTitle("m_{#mu#mu} [GeV]");
		signals->Add(KK1530);
		signalNames.insert(make_pair("2030","#gamma_{KK}/Z_{KK} (2030 GeV)"));
		KK2030 = (TH1D*)getTemplate("KK","2030")->Clone();
		zeroizeErrors(KK2030);
		KK2030->SetBinContent(1,h_bg->GetBinContent(1));
		KK2030->Add(h_bgnody);
		KK2030->SetLineWidth(2);
		KK2030->SetLineColor(kGreen+2);
		KK2030->GetXaxis()->SetTitle("m_{#mu#mu} [GeV]");
		signals->Add(KK2030);
		signalNames.insert(make_pair("3030","#gamma_{KK}/Z_{KK} (3030 GeV)"));
		KK3030 = (TH1D*)getTemplate("KK","3030")->Clone();
		zeroizeErrors(KK3030);
		KK3030->SetBinContent(1,h_bg->GetBinContent(1));
		KK3030->Add(h_bgnody);
		KK3030->SetLineWidth(2);
		KK3030->SetLineColor(kViolet+2);
		KK3030->GetXaxis()->SetTitle("m_{#mu#mu} [GeV]");
		signals->Add(KK3030);
		_INFO("");
	}
	else
	{
		_INFO("");
		signalNames.insert(make_pair("1530","Z'_{SSM} (1530 GeV)"));
		ZP1530 = (TH1D*)getTemplate("ZP","1530")->Clone();
		zeroizeErrors(ZP1530);
		ZP1530->SetBinContent(1,h_bg->GetBinContent(1));
		ZP1530->Add(h_bgnody);
		ZP1530->SetLineWidth(2);
		ZP1530->SetLineColor(kRed+2);
		ZP1530->GetXaxis()->SetTitle("m_{#mu#mu} [GeV]");
		signals->Add(ZP1530);
		signalNames.insert(make_pair("2030","Z'_{SSM} (2030 GeV)"));
		ZP2030 = (TH1D*)getTemplate("ZP","2030")->Clone();
		zeroizeErrors(ZP2030);
		ZP2030->SetBinContent(1,h_bg->GetBinContent(1));
		ZP2030->Add(h_bgnody);
		ZP2030->SetLineWidth(2);
		ZP2030->SetLineColor(kGreen+2);
		ZP2030->GetXaxis()->SetTitle("m_{#mu#mu} [GeV]");
		signals->Add(ZP2030);
		signalNames.insert(make_pair("3030","Z'_{SSM} (3030 GeV)"));
		ZP3030 = (TH1D*)getTemplate("ZP","3030")->Clone();
		zeroizeErrors(ZP3030);
		ZP3030->SetBinContent(1,h_bg->GetBinContent(1));
		ZP3030->Add(h_bgnody);
		ZP3030->SetLineWidth(2);
		ZP3030->SetLineColor(kViolet+2);
		ZP3030->GetXaxis()->SetTitle("m_{#mu#mu} [GeV]");
		signals->Add(ZP3030);
		_INFO("");
	}
	///////////
	// legend
	Double_t legxmin = 0.65;
	Double_t legxmax = 0.85;
	Double_t legymin = 0.55;
	Double_t legymax = 0.92;
	TLegend* leg = new TLegend(legxmin,legymin,legxmax,legymax);
	leg->SetFillStyle(4000); //will be transparent
	leg->SetFillColor(0);
	leg->SetTextSize(0.035);
	leg->AddEntry(hdata,"Data 2011","P");
	leg->AddEntry(h_dy,"Z/#gamma*","f");
	leg->AddEntry(h_diboson,"Diboson","f");
	leg->AddEntry(h_ttbar,"t#bar{t}","f");
	//leg->AddEntry(h_wjets,"W+jets","f");
	//leg->AddEntry(h_qcd,"QCD","f");
	if(doPlotSignals)
	{
		TIter next_sig(signals);
		while(( htmp=(TH1D*)next_sig() )!=NULL)
		{
			cout << "Adding to legend " << ((TH1D*)htmp)->GetName() << endl;
			TString barename = (TString)htmp->GetName();
			TString modelname = (model=="KK") ? model : "Zprime_SSM";
			barename.ReplaceAll("hMass_template_"+modelname,"");
			barename.ReplaceAll("_TeV","");
			TString signame = signalNames[barename];
			leg->AddEntry(htmp,signame,"F");
		}
	}
	///////////
	// draw !
	TCanvas* cMass = new TCanvas("Canvas","Canvas",10,10,800,600); 
	cMass->SetTicks(1,1);
	cMass->SetLogx();
	cMass->SetLogy();
	cMass->cd();
	cMass->Draw();
	float maximum = 20*h_dy->GetMaximum();
	float minimum = 0.001;
	TIter next_bg((TList*)backgrounds->GetHists());
	while(( htmp=(TH1D*)next_bg() )!= NULL)
	{
		_INFO("Adding "+(string)((TH1D*)htmp)->GetName());
		htmp->SetMinimum(minimum);
		htmp->SetMaximum(maximum);
		htmp->GetXaxis()->SetMoreLogLabels(1);
		htmp->GetXaxis()->SetNoExponent();
		htmp->GetXaxis()->SetTitle("m_{#mu#mu} [GeV]");
	}
	backgrounds->SetMinimum(minimum);
	backgrounds->SetMaximum(maximum);
	backgrounds->Draw();
	backgrounds->GetXaxis()->SetMoreLogLabels(1);
	backgrounds->GetXaxis()->SetNoExponent();
	// backgrounds->GetXaxis()->SetTitle("m_{#mu#mu} TeV");
	if(doPlotSignals)
	{
		TIter next_sig(signals);
		while(( htmp=(TH1D*)next_sig() )!=NULL)
		{
			cout << "Drawing " << ((TH1D*)htmp)->GetName() << endl;
			htmp->SetMinimum(minimum);
			htmp->SetMaximum(maximum);
			htmp->GetXaxis()->SetMoreLogLabels(1);
			htmp->GetXaxis()->SetNoExponent();
			htmp->GetXaxis()->SetTitle("m_{#mu#mu} [GeV]");
			htmp->Draw("histSAMES");
		}
	}
	gdata->Draw("psame");  // "esame" or "psame" (p for Poisson)
	leg->Draw("SAMES");
	TString approval = "#font[72]{ATLAS} For Approval";
	TString ppCME = "#sqrt{s} = 7 TeV";
	TString lumin = "#int L dt = "+(TString)_s(luminosity,0)+" fb^{-1}";
	// text
	TLatex *t = new TLatex();
	t->SetNDC(1);
	t->SetTextAlign(13);
	t->SetTextSize(0.05);
	t->SetTextColor(kBlack);
	TString atlas2 = approval;
	TString atlas3 = ppCME;
	TString atlas4 = lumin;
//	t->DrawLatex(0.325,0.925,atlas2);
	t->DrawLatex(0.325,0.860,atlas3);
	t->DrawLatex(0.325,0.775,atlas4);
	cMass->RedrawAxis();
	TString name = (doPlotSignals) ? "hstack_"+model+"_3332st" : "hstack_nosignals_3332st";
	saveas(cMass,"plots/"+name);
	/////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////
	

	
	
	
	
	
	
	TH1D* hData = (TH1D*)hChopper(h_data,bins2chop)->Clone(); // GeV
	hData = (TH1D*)hGeV2TeV(hData)->Clone(); // TeV
	TH1D* hSumBG = (TH1D*)hChopper(h_bg,bins2chop)->Clone(); // GeV
	hSumBG = (TH1D*)hGeV2TeV(hSumBG)->Clone(); // TeV
	TH1D* hBGnoDY = (TH1D*)hChopper(h_bgnody,bins2chop)->Clone(); // GeV
	hBGnoDY = (TH1D*)hGeV2TeV(hBGnoDY)->Clone(); // TeV
	TH1D* hSystTails = (TH1D*)hChopper(h_tails_up,bins2chop)->Clone(); // GeV
	hSystTails = (TH1D*)hGeV2TeV(hSystTails)->Clone(); // TeV

	hSumBG->SetLineColor(kBlack);
	hSumBG->SetFillColor(kAzure-9);
	hSumBG->SetTitle("");;
	hSumBG->GetXaxis()->SetTitle("m_{#mu#mu} [GeV]");
	hSumBG->GetYaxis()->SetTitle("Events");
	
	hData->SetMarkerColor(kBlack);
	hData->SetMarkerSize(0.5);
	hData->SetMarkerStyle(20);
	TGraphAsymmErrors* gaData = (TGraphAsymmErrors*)(poisson(hData))->Clone("");
	gaData->SetMarkerStyle(20);
	gaData->SetMarkerSize(0.5);
	gaData->SetTitle("");;
	gaData->GetXaxis()->SetTitle("m_{#mu#mu} [GeV]");
	gaData->GetYaxis()->SetTitle("Events");

	//// template
	TString version = "v81";
	TString infName = "";
	if     (gN=="g4") infName = "plots/linearbins/g4bins/3332st_nominal/"+version+"/"+model+"_combined_"+version+".root";
	else if(gN=="g2") infName = "plots/linearbins/g2bins/3332st_nominal/"+version+"/"+model+"_combined_"+version+".root";
	else              _FATAL("gN=g4 or g2");
	TFile* fT = new TFile(infName,"READ");

	TObjArray* toar_nominal = new TObjArray();
	toar_nominal->Read("template2d");
	TH2D* h2T_nominal = (TH2D*)((TH2D*)(TObjArray*)toar_nominal->At(uiXmass))->Clone();
	TH1D* h1T_nominal = (TH1D*)((TH1D*)TH2toTH1(h2T_nominal,"mm",gNbin))->Clone();
	h1T_nominal = (TH1D*)hChopper(h1T_nominal,bins2chop)->Clone();
	_INFO("gNbin="+_s(gNbin)+": g4="+_s(h2T_nominal->GetYaxis()->GetBinLowEdge(gNbin)));
	
	TObjArray* toar_Zxs = new TObjArray();
	toar_Zxs->Read("template2d_Zxs_syst");
	TH2D* h2T_Zxs = (TH2D*)((TH2D*)(TObjArray*)toar_Zxs->At(uiXmass))->Clone();
	TH1D* h1T_Zxs = (TH1D*)((TH1D*)TH2toTH1(h2T_Zxs,"mm",gNbin))->Clone();
	h1T_Zxs = (TH1D*)hChopper(h1T_Zxs,bins2chop)->Clone();
	
	TObjArray* toar_PDF = new TObjArray();
	toar_PDF->Read("template2d_PDF_syst");
	TH2D* h2T_PDF = (TH2D*)((TH2D*)(TObjArray*)toar_PDF->At(uiXmass))->Clone();
	TH1D* h1T_PDF = (TH1D*)((TH1D*)TH2toTH1(h2T_PDF,"mm",gNbin))->Clone();
	h1T_PDF = (TH1D*)hChopper(h1T_PDF,bins2chop)->Clone();
	
	TObjArray* toar_EWkF = new TObjArray();
	toar_EWkF->Read("template2d_EWkF_syst");
	TH2D* h2T_EWkF = (TH2D*)((TH2D*)(TObjArray*)toar_EWkF->At(uiXmass))->Clone();
	TH1D* h1T_EWkF = (TH1D*)((TH1D*)TH2toTH1(h2T_EWkF,"mm",gNbin))->Clone();
	h1T_EWkF = (TH1D*)hChopper(h1T_EWkF,bins2chop)->Clone();
	
	TObjArray* toar_mmSlopeEff = new TObjArray();
	toar_mmSlopeEff->Read("template2d_mmSlopeEff_syst");
	TH2D* h2T_mmSlopeEff = (TH2D*)((TH2D*)(TObjArray*)toar_mmSlopeEff->At(uiXmass))->Clone();
	TH1D* h1T_mmSlopeEff = (TH1D*)((TH1D*)TH2toTH1(h2T_mmSlopeEff,"mm",gNbin))->Clone();
	h1T_mmSlopeEff = (TH1D*)hChopper(h1T_mmSlopeEff,bins2chop)->Clone();
	
	TObjArray* toar_mmRes = new TObjArray();
	toar_mmRes->Read("template2d_mmRes_syst");
	TH2D* h2T_mmRes = (TH2D*)((TH2D*)(TObjArray*)toar_mmRes->At(uiXmass))->Clone();
	TH1D* h1T_mmRes = (TH1D*)((TH1D*)TH2toTH1(h2T_mmRes,"mm",gNbin))->Clone();
	h1T_mmRes = (TH1D*)hChopper(h1T_mmRes,bins2chop)->Clone();
	
	TH1D* h1Tfull = (TH1D*)h1T_nominal->Clone();
	h1Tfull->Reset();
	for(Int_t bin=1 ; bin<=h1T_nominal->GetNbinsX() ; bin++)
	{
		double mass = h1T_nominal->GetBinCenter(bin);
	
		//// the bare (nominal) template
		double nominal = h1T_nominal->GetBinContent(bin);
		double staterrornominal = h1T_nominal->GetBinError(bin);
		double staterrorbgnody  = hBGnoDY->GetBinError(bin);
		double staterror = sqrt(staterrornominal*staterrornominal + staterrorbgnody+staterrorbgnody);
		
		//// the relative systematic errors of the template alone
		double errT_Zxs        = nominal*h1T_Zxs->GetBinContent(bin);
		double errT_PDF        = nominal*h1T_PDF->GetBinContent(bin);
		double errT_EWkF       = nominal*h1T_EWkF->GetBinContent(bin);
		double errT_mmSlopeEff = nominal*h1T_mmSlopeEff->GetBinContent(bin);
		double errT_mmRes      = nominal*h1T_mmRes->GetBinContent(bin);
	
		// if(errT_Zxs        <0.) _INFO("errT_Zxs<0");
		// if(errT_PDF        <0.) _INFO("errT_PDF<0");
		// if(errT_EWkF       <0.) _INFO("errT_EWkF<0");
		// if(errT_mmSlopeEff <0.) _INFO("errT_mmSlopeEff<0");
		// if(errT_mmRes      <0.) _INFO("errT_mmRes<0");
	
		//// add the BGs to the nominal template
		double templatePlusBG  = nominal + hBGnoDY->GetBinContent(bin);
		
		//// the bare nominal BG (no dy)
		double nominalBG = hSumBG->GetBinContent(bin);
		
		//// BGs uncertainties
		double errBG_PDF        = 0.;
		double errBG_mmSlopeEff = 0.;
		double errBGtailsFit    = 0.;
		double errBG_mmRes      = 0.;
		if(mass >= 0.11) // all uncertainties cancel to first order in norm region (70,110GeV)
		{
			errBG_PDF        = nominalBG*graph_pdfZ->Eval(mass, 0, "S");
			errBG_mmSlopeEff = nominalBG*fsys_eff->Eval(mass);
			errBGtailsFit    = nominalBG*hSystTails->GetBinContent(bin);
			errBG_mmRes      = nominalBG*0.; //// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! no resolution syst on the other BG
		}
		
		//// full syst. error
		double systerror = sqrt(
							errT_Zxs*errT_Zxs +
							errT_PDF*errT_PDF +
							errT_EWkF*errT_EWkF +
							errT_mmSlopeEff*errT_mmSlopeEff +
							errT_mmRes*errT_mmRes + 
							errBG_PDF*errBG_PDF + 
							errBG_mmSlopeEff*errBG_mmSlopeEff +
							errBGtailsFit*errBGtailsFit +
							errBG_mmRes*errBG_mmRes
							);
		
		_INFO("staterror="+_s(staterror)+", systerror="+_s(systerror));
		// double error = sqrt(staterror*staterror + systerror*systerror);
		double error = systerror;
		
		h1Tfull->SetBinContent(bin,templatePlusBG);
		h1Tfull->SetBinError(bin,error);
	}
	
	TLegend* legR = new TLegend(0.6,0.2,0.91,0.45,NULL,"brNDC");
	legR->SetFillStyle(4000); //will be transparent
	legR->SetFillColor(0);
	legR->SetTextFont(42);

	TLegend* leg_sigma = new TLegend(0.52,0.65,0.92,0.95,NULL,"brNDC");
	leg_sigma->SetFillStyle(4000); //will be transparent
	leg_sigma->SetFillColor(0);
	leg_sigma->SetTextFont(42);
	
	TCanvas* c = new TCanvas("c","c",600,550);
	c->Divide(1,2);
	TVirtualPad* ph = c->cd(1);
	TVirtualPad* pr = c->cd(2);	
	ph->SetPad(0.00, 0.35, 1.00, 1.00);
	pr->SetPad(0.00, 0.00, 1.00, 0.355);
	ph->SetBottomMargin(0.012);
	pr->SetBottomMargin(0.20);
	pr->SetTopMargin(0.012);
	
	
	/////////////////////////// histos
	ph->cd();
	ph->Draw();
	ph->SetTicks(1,1);
	ph->SetLogy();
	ph->SetLogx();
	
	hSumBG->GetXaxis()->SetMoreLogLabels();
	h1Tfull->GetXaxis()->SetMoreLogLabels();
	gaData->GetXaxis()->SetMoreLogLabels();
	hSumBG->GetXaxis()->SetNoExponent();
	h1Tfull->GetXaxis()->SetNoExponent();
	gaData->GetXaxis()->SetNoExponent();
	
	hSumBG->Draw("hist");
	h1Tfull->SetLineColor(kRed+2);
	h1Tfull->SetLineWidth(2);
	h1Tfull->SetTitle("");;
	h1Tfull->GetXaxis()->SetTitle("m_{#mu#mu} [GeV]");
	h1Tfull->GetYaxis()->SetTitle("Events");
	h1Tfull->DrawCopy("histSAMES");
	h1Tfull->SetLineColor(kRed+2);
	h1Tfull->SetFillColor(kBlue);
	h1Tfull->SetFillStyle(3144/*3017*/);
	h1Tfull->Draw("E2SAMES");
	gaData->Draw("psame");  // "esame" or "psame" (p for Poisson)
	
	leg_sigma->AddEntry(hData,"Data","lep");
	leg_sigma->AddEntry(hSumBG,"DY + #SigmaBGs","f");
	leg_sigma->AddEntry(h1Tfull,modellabel+" "+sXmassTeV+" TeV + #SigmaBGs (syst.)","FL");
	leg_sigma->Draw("SAMES");
	
	TLatex* tAtlas = new TLatex();
	tAtlas->SetNDC(1);
	tAtlas->SetTextAlign(13);
	tAtlas->SetTextSize(0.05);
	tAtlas->SetTextColor(kBlack);
	TString ppcme = "#sqrt{s} = 7 TeV";
	TString lumi  = "#int L dt = "+(TString)_s(luminosity,0)+" fb^{-1}";
	tAtlas->DrawLatex(0.25,0.25,ppcme);
	tAtlas->DrawLatex(0.25,0.15,lumi);
	
	TLatex* tgN = new TLatex();
	tgN->SetNDC(1);
	tgN->SetTextAlign(13);
	tgN->SetTextSize(0.05);
	tgN->SetTextColor(kBlack);
	double xgN = h2T_nominal->GetYaxis()->GetBinLowEdge(gNbin);
	double xg  = (gN=="g4") ? sqrt(sqrt(xgN)) : sqrt(xgN);
	TString sgN = modellabel+" couplings scale: g="+(TString)_s(xg,1);
	tgN->DrawLatex(0.22,0.92,sgN);
	
	ph->RedrawAxis();
	ph->Update();
	
	
	/////////////////////////// ratio
	pr->cd();
	pr->Draw();
	pr->SetTicks(1,1);
	pr->SetGridy();
	pr->SetLogx();
	
	TLine* line = new TLine(h1Tfull->GetXaxis()->GetXmin(),0.,h1Tfull->GetXaxis()->GetXmax(),0.);
	line->SetLineColor(kRed);
	TH1D* hResiduals = (TH1D*)h1Tfull->Clone();
	hResiduals->Reset();
	//hResiduals->Divide(hData);
	for(Int_t bin=1 ; bin<=hResiduals->GetNbinsX() ; bin++)
	{
		if(hData->GetBinContent(bin)==0.) continue;
		
		//// get the data stat error
		double statdatahigh = error_poisson_up(hData->GetBinContent(bin));
		double statdatalow  = error_poisson_down(hData->GetBinContent(bin));
		// double staterrordata = (statdatahigh>=statdatalow) ? statdatahigh : statdatalow;
		double staterrordata = statdatalow;
		
		//// get the sig+bg stat and syst error
		double staterrornominal = h1T_nominal->GetBinError(bin);
		double staterrorbgnody  = hBGnoDY->GetBinError(bin);
		double staterrorsigbg = sqrt(staterrornominal*staterrornominal + staterrorbgnody+staterrorbgnody);
		double systerrorsigbg = h1Tfull->GetBinError(bin); // contains only syst error !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
		double fullerrorsigbg = sqrt(systerrorsigbg*systerrorsigbg + staterrorsigbg*staterrorsigbg);
		
		//// get the residuals
		_INFO("staterrordata="+_s(staterrordata)+", fullerrorsigbg="+_s(fullerrorsigbg));
		double error = sqrt(staterrordata*staterrordata + fullerrorsigbg*fullerrorsigbg);
		double residuals = (hData->GetBinContent(bin) - h1Tfull->GetBinContent(bin))/error;
		
		hResiduals->SetBinContent(bin,residuals);
	}
	hResiduals->SetLineColor(kBlack);
	hResiduals->SetLineWidth(1);
	hResiduals->SetFillColor(kOrange+2);
	hResiduals->GetXaxis()->SetLabelSize(0.075);
	hResiduals->GetYaxis()->SetLabelSize(0.075);
	hResiduals->GetXaxis()->SetTitleSize(0.075);
	hResiduals->GetYaxis()->SetTitleSize(0.075);
	hResiduals->SetTitleSize(0.075);
	hResiduals->SetTitleSize(0.075);
	hResiduals->GetYaxis()->SetTitleOffset(0.5);
	hResiduals->GetYaxis()->SetTitle("significance");
	hResiduals->GetXaxis()->SetTitle("m_{#mu#mu} [GeV]");
	
	hResiduals->Draw("hist");
	line->Draw("SAMES");
	legR->AddEntry(hResiduals,"#frac{Data - ("+modellabel+"+#SigmaBGs)}{#sqrt{#delta^{2}("+modellabel+"+#SigmaBGs) + #delta^{2}(data)}}","f");
	legR->Draw("SAMES");
	
	pr->RedrawAxis();
	pr->Update();
	
	
	/////////////////////////// save
	TString fname = "plots/systplot_"+model+"_"+gN+"_xmass"+sXmassGeV+"GeV";
	c->SaveAs(fname+".png");
	c->SaveAs(fname+".eps");
}
