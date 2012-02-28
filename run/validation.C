#include "../include/rawStd.h"
#include "../include/rawROOT.h"
#include "../include/types.h"
#include "../include/logs.h"
#include "../include/bins.h"
#include "../include/histos.h"
#include "../include/style.h"
#include "../include/units.h"

TString model    = "ZP";
TString mutype   = "33st";
TString binning  = "linearbins";
bool doTruth     = false;
bool doResiduals = false;
bool isMC11c     = true;
bool doInterpolation = false;

TH2D* h2Template;

inline TH1D* hGeV2TeV(TH1D* hGeV)
{
	const Int_t    nbins = hGeV->GetNbinsX();
	Double_t bins[nbins+1];
	TAxis* xaxis = (TAxis*)hGeV->GetXaxis();
	TAxis* yaxis = (TAxis*)hGeV->GetYaxis();

	for(int i=0 ; i<nbins ; i++)
	{
		bins[i] = xaxis->GetBinLowEdge(i+1)/1000.;
		cout << "|" << bins[i];
	}
	bins[nbins] = xaxis->GetBinUpEdge(nbins)/1000.;
	cout << "|" << bins[nbins] << "|" << endl;

	TString name   = (TString)hGeV->GetName();
	TString title  = (TString)hGeV->GetTitle();
	TString xtitle = (TString)xaxis->GetTitle();
	TString ytitle = (TString)yaxis->GetTitle();

	TH1D* hTeV = new TH1D(name+"_TeV",title+";"+xtitle+";"+ytitle, nbins,bins);
	for(Int_t b=0 ; b<=nbins+1 ; b++) hTeV->SetBinContent(b, hGeV->GetBinContent(b));
	return hTeV;
}

TH1D* TH2toTH1(TH2D* h2, Int_t massbin)
{
	TString massbinname = (TString)_s(massbin);
	TString origname = (TString)h2->GetName();
	// origname.ReplaceAll("hg4Mass_template_","");
	TString name = origname+"_mll_"+massbinname;
	//------------------------------------------------------------
	const Int_t nbins = h2->GetNbinsY();
	Double_t bins[nbins+1];
	TAxis* yaxis = (TAxis*)h2->GetYaxis();
	for(int i=0 ; i<nbins ; i++) bins[i] = yaxis->GetBinLowEdge(i+1);
	bins[nbins] = yaxis->GetBinUpEdge(nbins);
	//------------------------------------------------------------
	TH1D* h1 = new TH1D(name,"#frac{dN}{dg^{4}};g^{4};dN/dg^{4}",nbins,bins);
	for(Int_t bin=1 ; bin<=nbins ; bin++)
	{
		h1->SetBinContent(bin, h2->GetBinContent(massbin+bins2chop,bin));
	}
	return h1;
}

Double_t fTH1toTF1(Double_t *x, Double_t *par)
{
	Double_t g4  = x[0];          // -> g^4 value
	Int_t    mll = (Int_t)par[0]; // -> dilepton invariant mass bin number
	
	TH2D* h2 = (TH2D*)h2Template->Clone();
	TH1D* hTmp = (TH1D*)TH2toTH1(h2,mll); // TH1 histogram of g^4 in the dilepton mass bin number mll
	
	Int_t nbinsx = hTmp->GetNbinsX();
	Double_t xval = -999.;
	if(doInterpolation)
	{
		Int_t bin = hTmp->FindBin(g4);
		
		if(bin==0 || bin==1)   xval = hTmp->GetBinContent(1);     // cannot interpolate on the first bin or the underflow
		else if(bin==nbinsx+1) xval = hTmp->GetBinContent(bin-1); // cannot interpolate on the last bin or the overflow
		else if(bin==nbinsx)   xval = hTmp->GetBinContent(bin);   // cannot interpolate on the last bin or the overflow
		else                   xval = hTmp->Interpolate(g4);      // interpolated dN/dg^4 at g^4, between the 2 adjacent bin centers
	}
	else
	{
		Int_t bin = hTmp->FindBin(g4);
		if(bin==nbinsx+1) xval = hTmp->GetBinContent(bin-1); // overflow 
		else if(bin==0)   xval = hTmp->GetBinContent(1);     // underflow
		else              xval = hTmp->GetBinContent(bin);   // normal
	}
	delete h2;
	delete hTmp;
	return xval;
}


void validation()
{
	msglvl[DBG] = SILENT;
	msglvl[INF] = VISUAL;
	msglvl[WRN] = VISUAL;
	msglvl[ERR] = VISUAL;
	msglvl[FAT] = VISUAL;

	TDirectory* oldDir = gDirectory; // remember old directory

	style();

	Int_t g4bin = (ng4bins/g4max+1); //==> g^4=1 ==> SSM !
	
	TString suffix = "";
	if(doTruth) suffix = "_truth";
	
	TString mctype  = (isMC11c) ? "mc11c" : "mc11a";
	
	// TString fBGname = "plots/ZP_2dtemplates_"+mctype+"_33st_overallEWkF_noInAmpSigEWkF_noHighMbins_wthOfficialZP_Xmass2000.root";
	// TString fBGname = "plots/ZP_2dtemplates_"+mctype+"_33st_noKKtmplates_overallEWkF_noInAmpSigEWkF_noTruth_wthOfficialZP_treeLevelMass_Xmass2000.root";
	// TString fBGname = "plots/ZP_2dtemplates_"+mctype+"_33st_noKKtmplates_overallEWkF_noInAmpSigEWkF_wthOfficialZP_treeLevelMass_Xmass2000.root";
	// TString fBGname = "plots/ZP_2dtemplates_mc11c_33st_noKKtmplates_overallEWkF_noInAmpSigEWkF_wthOfficialZP_fixedBWwidth_treeLevelMass_Xmass2000.root";
	// TString fBGname = "plots/ZP_2dtemplates_mc11c_33st_noKKtmplates_overallEWkF_noInAmpSigEWkF_noTruth_wthOfficialZP_treeLevelMass_Xmass2000.root";
	// TString fBGname = "plots/ZP_2dtemplates_"+mctype+"_33st_noKKtmplates_overallEWkF_noInAmpSigEWkF_noTruth_wthOfficialZP_treeLevelMass_Xmass2000.root";
	// TString fBGname = "plots/ZP_2dtemplates_"+mctype+"_33st_noKKtmplates_overallEWkF_noInAmpSigEWkF_noTruth_wthOfficialZP_fixedBWwidth_treeLevelMass_Xmass2000.root";

	oldDir->cd();

	TString fBGname = "plots/ZP_2dtemplates_mc11c_33st_noKKtmplates_wthOfficialZP_treeLevelMass_Xmass2000.root";
	TFile* fD = new TFile(fBGname,"READ");
	TH1D* hDY = NULL;
	if(doTruth) hDY = (TH1D*)fD->Get("hMass_DYmumu_truth")->Clone();
	else        hDY = (TH1D*)fD->Get("hMass_DYmumu")->Clone();
	hDY->SetLineColor(kMagenta-5);
	hDY->SetMarkerColor(kMagenta-5);

	oldDir->cd();

	TFile* fDYrozmin    = new TFile("plots/mass_plot_tables_3st.root","READ");
	TH1D* hDYrozmin = (TH1D*)fDYrozmin->Get("mass_log_dy")->Clone();
	hDYrozmin = (TH1D*)hGeV2TeV(hDYrozmin)->Clone();
	hDYrozmin = (TH1D*)hChopper(hDYrozmin,bins2chop)->Clone();
	oldDir->cd();
	TFile* f1dTemplates = new TFile("plots/ZpSignal_MM_MC11c_5points.root","READ");
	TObjArray* toarr1d = new TObjArray();
	toarr1d->Read("template");
	TMapTSP2TH1D h1dBrandeisTmpltMap;
	double Nflat = 399948;
	double sigmaflat = 4.3988E+07*nb2fb;
	double Lmcflat = Nflat/sigmaflat;
	double scale = luminosity/Lmcflat;
	TH1D* h1dTmp = NULL;
	h1dTmp = (TH1D*)((TObjArray*)toarr1d->At(0/*22*/))->Clone();
	h1dTmp->Scale(scale);
	h1dTmp = (TH1D*)hChopper(h1dTmp,bins2chop)->Clone();
	h1dTmp->Add(hDYrozmin);
	h1dBrandeisTmpltMap.insert( make_pair("1000",(TH1D*)resetErrors(h1dTmp)->Clone("1000")) );
	h1dTmp = NULL;
	h1dTmp = (TH1D*)((TObjArray*)toarr1d->At(1/*28*/))->Clone();
	h1dTmp->Scale(scale);
	h1dTmp = (TH1D*)hChopper(h1dTmp,bins2chop)->Clone();
	h1dTmp->Add(hDYrozmin);
	h1dBrandeisTmpltMap.insert( make_pair("1250",(TH1D*)resetErrors(h1dTmp)->Clone("1250")) );
	h1dTmp = NULL;
	h1dTmp = (TH1D*)((TObjArray*)toarr1d->At(2/*34*/))->Clone();
	h1dTmp->Scale(scale);
	h1dTmp = (TH1D*)hChopper(h1dTmp,bins2chop)->Clone();
	h1dTmp->Add(hDYrozmin);
	h1dBrandeisTmpltMap.insert( make_pair("1500",(TH1D*)resetErrors(h1dTmp)->Clone("1500")) );
	h1dTmp = NULL;
	h1dTmp = (TH1D*)((TObjArray*)toarr1d->At(3/*40*/))->Clone();
	h1dTmp->Scale(scale);
	h1dTmp = (TH1D*)hChopper(h1dTmp,bins2chop)->Clone();
	h1dTmp->Add(hDYrozmin);
	h1dBrandeisTmpltMap.insert( make_pair("1750",(TH1D*)resetErrors(h1dTmp)->Clone("1750")) );
	h1dTmp = NULL;
	h1dTmp = (TH1D*)((TObjArray*)toarr1d->At(4/*47*/))->Clone();
	h1dTmp->Scale(scale);
	h1dTmp = (TH1D*)hChopper(h1dTmp,bins2chop)->Clone();
	h1dTmp->Add(hDYrozmin);
	h1dBrandeisTmpltMap.insert( make_pair("2000",(TH1D*)resetErrors(h1dTmp)->Clone("2000")) );

	oldDir->cd();

	TMapTSP2TH1D h1Map;
	h1Map.insert( make_pair("1000o", (TH1D*)fD->Get("hMass_Zprime_SSM1000"+suffix)->Clone()) );
	h1Map.insert( make_pair("1000t", (TH1D*)fD->Get("hMass_Zprime_SSM1000_template"+suffix)->Clone()) );
	if(isMC11c)
	{
		h1Map.insert( make_pair("1250o", (TH1D*)fD->Get("hMass_Zprime_SSM1250"+suffix)->Clone()) );
		h1Map.insert( make_pair("1250t", (TH1D*)fD->Get("hMass_Zprime_SSM1250_template"+suffix)->Clone()) );
	}
	h1Map.insert( make_pair("1500o", (TH1D*)fD->Get("hMass_Zprime_SSM1500"+suffix)->Clone()) );
	h1Map.insert( make_pair("1500t", (TH1D*)fD->Get("hMass_Zprime_SSM1500_template"+suffix)->Clone()) );
	h1Map.insert( make_pair("1750o", (TH1D*)fD->Get("hMass_Zprime_SSM1750"+suffix)->Clone()) );
	h1Map.insert( make_pair("1750t", (TH1D*)fD->Get("hMass_Zprime_SSM1750_template"+suffix)->Clone()) );
	h1Map.insert( make_pair("2000o", (TH1D*)fD->Get("hMass_Zprime_SSM2000"+suffix)->Clone()) );
	h1Map.insert( make_pair("2000t", (TH1D*)fD->Get("hMass_Zprime_SSM2000_template"+suffix)->Clone()) );

	TMapTSP2TH1D h1rMap;
	h1rMap.insert( make_pair("1000", (TH1D*)fD->Get("hMass_Zprime_SSM1000"+suffix)->Clone()) );
	if(isMC11c) h1rMap.insert( make_pair("1250", (TH1D*)fD->Get("hMass_Zprime_SSM1250"+suffix)->Clone()) );
	h1rMap.insert( make_pair("1500", (TH1D*)fD->Get("hMass_Zprime_SSM1500"+suffix)->Clone()) );
	h1rMap.insert( make_pair("1750", (TH1D*)fD->Get("hMass_Zprime_SSM1750"+suffix)->Clone()) );
	h1rMap.insert( make_pair("2000", (TH1D*)fD->Get("hMass_Zprime_SSM2000"+suffix)->Clone()) );
	for(TMapTSP2TH1D::iterator it=h1rMap.begin() ; it!=h1rMap.end() ; ++it)
	{
		it->second->Reset();
		if(!doResiduals) it->second->Divide(h1Map[it->first+"o"],h1Map[it->first+"t"],1.,1.,"B");
		else             residuals(h1Map[it->first+"o"], h1Map[it->first+"t"], it->second);
		
		// for(Int_t i=0 ; i<=it->second->GetNbinsX()+1 ; i++) it->second->SetBinError(i,0);
		it->second->SetMarkerStyle(20);
		it->second->SetMarkerSize(0.5);
		it->second->GetXaxis()->SetLabelSize(0.073);
		it->second->GetYaxis()->SetLabelSize(0.073);
		it->second->GetXaxis()->SetTitleSize(0.073);
		it->second->GetYaxis()->SetTitleSize(0.073);
		it->second->SetTitleSize(0.075);
		it->second->GetYaxis()->SetTitleOffset(0.5);
		if(!doResiduals)
		{
			it->second->SetMinimum(0.2);
			it->second->SetMaximum(1.8);
		}
		else
		{
			it->second->SetMinimum(-5.);
			it->second->SetMaximum(+5.);
		}
		it->second->SetTitle("");
		if(!doResiduals) it->second->GetYaxis()->SetTitle("ratio");
		else             it->second->GetYaxis()->SetTitle("residuals");
	}

	TMapTSP2TGAE poissonGraphMap;
	TMapTSP2TLeg legMap;


	_INFO("");

	oldDir->cd();

	fD->cd();	
	TH1D* h1Template = (TH1D*)fD->Get("hMass_DYmumu"+suffix)->Clone();
	h1Template->Reset();
	TObjArray* toarr = new TObjArray();
	if(doTruth) toarr->Read("truth_template2d");
	else        toarr->Read("template2d");
	TH2D* h2SSM2000 = (TH2D*)((TObjArray*)toarr->At(0))->Clone("hMass"+suffix+"_Zprime_SSM2000_template2d");
	for(Int_t bin=1 ; bin<=h2SSM2000->GetNbinsX() ; bin++)
	{
		h1Template->SetBinContent(bin, h2SSM2000->GetBinContent(bin,g4bin));
		h1Template->SetBinError(bin, h2SSM2000->GetBinError(bin,g4bin));
	}
	h1Template->SetLineColor(kViolet);
	h1Template->SetLineWidth(1);
	h1Template->SetMarkerStyle(20);
	h1Template->SetMarkerSize(0.3);
	h1Template->SetMarkerColor(kViolet);
	// the functions
	h2Template = (TH2D*)h2SSM2000->Clone();
	vector<TF1*> vfunc;
	unsigned int nmllbins = h2Template->GetNbinsX();
	for(unsigned int mll=1 ; mll<=(nmllbins-bins2chop) ; mll++) // 1...(56-9 = 47)
	{
		TString mllname = (TString)_s(mll);
		TString mllval  = (TString)_s(h2Template->GetXaxis()->GetBinCenter(mll+bins2chop));
		
		TF1* f = new TF1("fNominal_mll"+mllname,fTH1toTF1,g4min,g4max,1);
		f->SetParameter(0,mll);
		f->SetParNames("mll");
		// f->SetLineColor(kBlue);
		// f->SetLineWidth(1);
		f->SetNpx(400);
		vfunc.push_back(f);
	}
	TGraph* graphDY = new TGraph();
	graphDY->SetMarkerStyle(25);
	graphDY->SetMarkerSize(0.6);
	graphDY->SetMarkerColor(kGreen+2);
	TGraph* graphSSM = new TGraph();
	graphSSM->SetMarkerStyle(24);
	graphSSM->SetMarkerSize(0.6);
	graphSSM->SetMarkerColor(kOrange+8);
	for(unsigned int i=0 ; i<vfunc.size() ; i++)
	{
		double DY = vfunc[i]->Eval(0.0);
		double SSM = vfunc[i]->Eval(1.0);
		graphDY->SetPoint(i,h2Template->GetXaxis()->GetBinCenter(bins2chop+i+1),DY);
		graphSSM->SetPoint(i,h2Template->GetXaxis()->GetBinCenter(bins2chop+i+1),SSM);
	}
	
	
	oldDir->cd();

	TObjArray* toarr1dTLV = new TObjArray();
	TMapTSP2TH1D h1dTlvTmpltMap;
	TFile* fT = NULL;
	TString fTname = "plots/ZP_2dtemplates_mc11c_33st_noInterference_noKKtmplates_noOverallEWkF_wthOfficialZP_treeLevelMass_Xmass";
	
	fT = new TFile(fTname+"1000.root","READ");
	toarr1dTLV->Read("template");
	h1dTmp = (TH1D*)((TObjArray*)toarr1dTLV->At(0))->Clone();
	h1dTmp->Add(hDY);
	h1dTlvTmpltMap.insert( make_pair("1000",(TH1D*)resetErrors(h1dTmp)->Clone("1000")) );
	fT = new TFile(fTname+"1250.root","READ");
	toarr1dTLV->Read("template");
	h1dTmp = (TH1D*)((TObjArray*)toarr1dTLV->At(0))->Clone();
	h1dTmp->Add(hDY);
	h1dTlvTmpltMap.insert( make_pair("1250",(TH1D*)resetErrors(h1dTmp)->Clone("1250")) );
	fT = new TFile(fTname+"1500.root","READ");
	toarr1dTLV->Read("template");
	h1dTmp = (TH1D*)((TObjArray*)toarr1dTLV->At(0))->Clone();
	h1dTmp->Add(hDY);
	h1dTlvTmpltMap.insert( make_pair("1500",(TH1D*)resetErrors(h1dTmp)->Clone("1500")) );
	fT = new TFile(fTname+"1750.root","READ");
	toarr1dTLV->Read("template");
	h1dTmp = (TH1D*)((TObjArray*)toarr1dTLV->At(0))->Clone();
	h1dTmp->Add(hDY);
	h1dTlvTmpltMap.insert( make_pair("1750",(TH1D*)resetErrors(h1dTmp)->Clone("1750")) );
	fT = new TFile(fTname+"2000.root","READ");
	toarr1dTLV->Read("template");
	h1dTmp = (TH1D*)((TObjArray*)toarr1dTLV->At(0))->Clone();
	h1dTmp->Add(hDY);
	h1dTlvTmpltMap.insert( make_pair("2000",(TH1D*)resetErrors(h1dTmp)->Clone("2000")) );

	oldDir->cd();
	
	
	for(TMapTSP2TH1D::iterator it=h1Map.begin() ; it!=h1Map.end() ; ++it)
	{
		if(it->first.Contains("o"))
		{
			TString name = it->first;
			name.ReplaceAll("o","");
			it->second->SetFillColor(kAzure-9);
			if(doTruth) it->second->SetTitle("m_{Z'} = "+name+" GeV (truth)");
			else        it->second->SetTitle("m_{Z'} = "+name+" GeV");
		}
		if(it->first.Contains("t"))
		{
			//TGraphAsymmErrors* poisson(TH1D* h)
			it->second->SetLineColor(kBlue);
			it->second->SetMarkerStyle(20);
			it->second->SetMarkerSize(0.4);
			it->second->SetMarkerColor(kBlue);
			it->second->SetLineWidth(1);
			
			TString name = it->first;
			name.ReplaceAll("t","");
			poissonGraphMap.insert( make_pair(name, (TGraphAsymmErrors*)poisson(it->second)->Clone()) );
			poissonGraphMap[name]->SetMarkerStyle(20);
			poissonGraphMap[name]->SetMarkerSize(0.3);
			poissonGraphMap[name]->SetMarkerColor(kBlue);
			poissonGraphMap[name]->SetLineWidth(1);
			poissonGraphMap[name]->SetLineColor(kBlue);
		}
	}	

	Double_t yLine = (!doResiduals) ? 1. : 0.;

	TLine* line = new TLine(0.07,yLine,3.,yLine);	
	line->SetLineColor(kRed);
	line->SetLineWidth(2);
	
	TMapTSP2TCNV cnvMap;
	cnvMap.insert( make_pair("1000", new TCanvas("1000","1000",600,550)) );
	if(isMC11c) cnvMap.insert( make_pair("1250", new TCanvas("1250","1250",600,550)) );
	cnvMap.insert( make_pair("1500", new TCanvas("1500","1500",600,550)) );
	cnvMap.insert( make_pair("1750", new TCanvas("1750","1750",600,550)) );
	cnvMap.insert( make_pair("2000", new TCanvas("2000","2000",600,550)) );
	for(TMapTSP2TCNV::iterator it=cnvMap.begin() ; it!=cnvMap.end() ; ++it)
	{
		_INFO("starting "+(string)it->first);
		if(it->first=="2000") legMap.insert( make_pair(it->first, new TLegend(0.35,0.55,0.83,0.84,NULL,"brNDC")) );
		else                  legMap.insert( make_pair(it->first, new TLegend(0.35,0.60,0.83,0.84,NULL,"brNDC")) );
		legMap[it->first]->SetFillStyle(4000); //will be transparent
		legMap[it->first]->SetFillColor(0);
		legMap[it->first]->SetTextFont(42);
		legMap[it->first]->AddEntry(h1Map[it->first+"o"],"Official Z'_{SSM}","F");
		legMap[it->first]->AddEntry(hDY,"Official DY","lep");
		legMap[it->first]->AddEntry(h1Map[it->first+"t"],"Template w/o couplings scale","lep");
		if(it->first=="2000")
		{
			legMap[it->first]->AddEntry(h1Template,"Template histogram at  #it{g=1} (SSM)","lep");
			legMap[it->first]->AddEntry(graphSSM,  "Template function  at  #it{g=1} (SSM)","p");
			legMap[it->first]->AddEntry(graphDY,   "Template function  at  #it{g=0} (DY)","p");
		}
		if(!doTruth)
		{
			h1dTlvTmpltMap[it->first]->SetLineColor(kCyan+2);
			h1dTlvTmpltMap[it->first]->SetMarkerColor(kCyan+2);
			h1dTlvTmpltMap[it->first]->SetMarkerStyle(5);
			h1dTlvTmpltMap[it->first]->SetMarkerSize(0.5);
			legMap[it->first]->AddEntry(h1dTlvTmpltMap[it->first],"TLV DY+Template (#slash{interference})","p");
		
			h1dBrandeisTmpltMap[it->first]->SetLineColor(kRed);
			h1dBrandeisTmpltMap[it->first]->SetMarkerColor(kRed);
			h1dBrandeisTmpltMap[it->first]->SetMarkerStyle(27);
			h1dBrandeisTmpltMap[it->first]->SetMarkerSize(0.5);
			legMap[it->first]->AddEntry(h1dBrandeisTmpltMap[it->first],"Brandeis DY+Template (#slash{interference})","p");
		}

		it->second->Divide(1,2);
		TVirtualPad* ph = it->second->cd(1);
		TVirtualPad* pr = it->second->cd(2);	
		ph->SetPad(0.00, 0.35, 1.00, 1.00);
		pr->SetPad(0.00, 0.00, 1.00, 0.35);
		ph->SetBottomMargin(0.012);
		pr->SetBottomMargin(0.20);
		pr->SetTopMargin(0.012);
		
		ph->cd();
		ph->Draw();
		ph->SetTicks(1,1);
		ph->SetLogy();
		ph->SetLogx();
		// h1Map[it->first+"o"]->SetMaximum( h1Map[it->first+"t"]->GetMaximum()*1.5 );
		// h1Map[it->first+"o"]->Draw();
		TH1D* hTmpNoErr = (TH1D*)resetErrors(h1Map[it->first+"o"])->Clone();
		hTmpNoErr->SetMaximum( h1Map[it->first+"t"]->GetMaximum()*1.5 );
		hTmpNoErr->SetLineStyle(1);
		hTmpNoErr->SetLineColor(kBlack);
		hTmpNoErr->SetFillColor(kAzure-9);
		hTmpNoErr->Draw();
		TH1D* hTmpErr = (TH1D*)ShiftLog(h1Map[it->first+"o"],0.2)->Clone();
		hTmpErr->SetFillStyle(4000); //will be transparent
		hTmpErr->SetFillColor(0);
		hTmpErr->DrawCopy("epx0SAMES");
		hDY->Draw("SAMES");
		h1Map[it->first+"t"]->Draw("epSAMES");
		//poissonGraphMap[it->first]->Draw("pSAMES");
		if(it->first=="2000")
		{
			graphDY->Draw("SAMESp");
			graphSSM->Draw("SAMESp");
			h1Template->Draw("epSAMES");
		}
		_INFO("");
		h1dTlvTmpltMap[it->first]->Draw("SAMESp");
		h1dBrandeisTmpltMap[it->first]->Draw("SAMESp");
		legMap[it->first]->Draw("SAMES");
		ph->RedrawAxis();
		ph->Update();

		_INFO("");

		pr->cd();
		pr->Draw();
		pr->SetTicks(1,1);
		pr->SetGridy();
		pr->SetLogx();
		h1rMap[it->first]->Draw("ep");
		line->Draw("SAMES");
		h1rMap[it->first]->Draw("epSAMES");
		pr->RedrawAxis();
		pr->Update();

		unsigned int savestate = 1;
		if(it->first=="1000")      savestate = 0;
		else if(it->first=="2000") savestate = 2;
		else                       savestate = 1;
		TString testType = (doResiduals) ? "_residuals" : "_ratio";
		mutype   = (doTruth)     ? "_truth"     : "_recon";
		savemultipdf(it->second, "plots/validation"+mutype+testType+"_"+mctype+".pdf", savestate);
		
		
		TCanvas* c = new TCanvas(it->first,"",600,400);
		c->cd();
		c->Draw();
		c->SetTicks(1,1);
		c->SetLogy();
		c->SetLogx();
		hTmpNoErr->Draw();
		hTmpErr->DrawCopy("epx0SAMES");
		hDY->Draw("SAMES");
		h1Map[it->first+"t"]->Draw("epSAMES");
		//poissonGraphMap[it->first]->Draw("pSAMES");
		if(it->first=="2000")
		{
			graphDY->Draw("SAMESp");
			graphSSM->Draw("SAMESp");
			h1Template->Draw("epSAMES");
		}
		h1dTlvTmpltMap[it->first]->Draw("SAMESp");
		h1dBrandeisTmpltMap[it->first]->Draw("SAMESp");
		legMap[it->first]->Draw("SAMES");
		c->RedrawAxis();
		c->Update();
		saveas(c,"plots/validation_"+it->first+"_"+mutype+testType);
		
		_INFO("done "+(string)it->first);
	}
}
