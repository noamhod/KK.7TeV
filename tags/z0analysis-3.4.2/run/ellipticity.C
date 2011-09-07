#include "basicIncludes.h"

TTree* tree;
TH1D* hEtaCentral = new TH1D("hEtaCentral", ";#eta;Events", netabins,etamin,etamax);
TH1D* hEtaSides   = new TH1D("hEtaSides", ";#eta;Events", netabins,etamin,etamax);
TH1D* hEtaTotal   = new TH1D("hEtaTotal", ";#eta;Events", netabins,etamin,etamax);

TPaveText* pvtxt_lumi;
TPaveText* pvtxt_atlas;
TCanvas* cnvEllipticity;
TPad *pad_mHat;
TPad *pad_ellipticity;
TLegend* leg;
TLegend* leg_mHat;
TPaveText* pvtxt;
TText* txt;
vector<TH1D*> vhEllipticity;
vector<TH1D*> vhMass;
TMapTSP2TCNV  cnvMap;
Bool_t dolog=true;

float mass_tru, mass_rec, mass_wgt;
float cost_tru, cost_rec, cost_wgt;
float yQ_tru, yQ_rec, yQ_wgt;
float eta_tru, eta_rec, eta_wgt;
float xscn_wgt;

TFile* file = new TFile("/srv01/tau/hod/z0analysis-tests/z0analysis-tmp_qsub/pythia8/weights.root", "READ");

bool doXSlumiWeights = false;

float hintegral(TH1* h)
{
	float I = 0.;
	for(Int_t bin=1 ; bin<=h->GetNbinsX() ; bin++) I += h->GetBinContent(bin)*h->GetBinWidth(bin);
	if(h->GetBinContent(0)>0.) _WARNING("In histo "+(string)h->GetName()+" Underflow bin is not empty");
	if(h->GetBinContent(h->GetNbinsX()+1)>0.) _WARNING("In histo "+(string)h->GetName()+" Overflow bin is not empty");
	return I;
}

void correct(TH1* hPyhsics, TString sModel, int massbin)
{
	TString hName = "";
	if(sModel=="Z0" || sModel=="DT") hName = "hEtaZ0d3pd_acceptance_"+(TString)_s(massbin);
	else                             hName = "hEta"+sModel+"_acceptance_"+(TString)_s(massbin);
	
	TH1* hFactor = (TH1D*)file->Get("etamu_histograms/"+hName);

	Int_t bins = hPyhsics->GetNbinsX();
	if(hFactor->GetNbinsX()!=bins)
	{
		_ERROR("hFactor->GetNbinsX()!=hPyhsics->GetNbinsX()  ->  "+_s(hFactor->GetNbinsX())+":"+_s(bins)+", exitting now");
		exit(-1);
	}
	for(Int_t bin=1 ; bin<=bins ; bin++)
	{
		Double_t factor = hFactor->GetBinContent(bin);
		Double_t value  = hPyhsics->GetBinContent(bin);
		Double_t newvalue = (factor!=0.) ? value/factor : 0.;
		hPyhsics->SetBinContent(bin,newvalue);
		//hPyhsics->SetBinError(bin,???);
	}
	
}

void setTree(TString model, TString massbin)
{
	_DEBUG("setTree");
	tree = (TTree*)file->Get("ntuples/tree_"+model+"_"+massbin);
	tree->SetBranchAddress( "mass_tru", &mass_tru );
	tree->SetBranchAddress( "mass_rec", &mass_rec );
	tree->SetBranchAddress( "mass_wgt", &mass_wgt );
	tree->SetBranchAddress( "cost_tru", &cost_tru );
	tree->SetBranchAddress( "cost_rec", &cost_rec );
	tree->SetBranchAddress( "cost_wgt", &cost_wgt );
	tree->SetBranchAddress( "yQ_tru",   &yQ_tru );
	tree->SetBranchAddress( "yQ_rec",   &yQ_rec );
	tree->SetBranchAddress( "yQ_wgt",   &yQ_wgt );
	tree->SetBranchAddress( "eta_tru",  &eta_tru );
	tree->SetBranchAddress( "eta_rec",  &eta_rec );
	tree->SetBranchAddress( "eta_wgt",  &eta_wgt );
	tree->SetBranchAddress( "xscn_wgt", &xscn_wgt );
}

void reset()
{
	_DEBUG("reset");
	hEtaCentral->Reset();
	hEtaSides->Reset();
	hEtaTotal->Reset();
}

void fill(float eta, float wgt=1.)
{
	_DEBUG("fill");
	if(fabs(eta)<=etamax)
	{
		if(fabs(eta)<=etax)
		{
			hEtaCentral->Fill(eta,wgt);
			hEtaTotal->Fill(eta,wgt);
		}
		else if(fabs(eta)>etax  &&  fabs(eta)<=etamax)
		{
			hEtaSides->Fill(eta,wgt);
			hEtaTotal->Fill(eta,wgt);
		}
	}
}

Int_t loop(int mod)
{
	_DEBUG("loop");
	Int_t N = tree->GetEntries();
	float eta_weight  = 1.;
	float mass_weight = 1.;
	for(Int_t i=0 ; i<N ; i++)
	{
		tree->GetEntry(i);
		if(mod==DT)
		{
			eta_weight = 1.;
		}
		else if(mod==Z0)
		{
			if(doXSlumiWeights) eta_weight = (xscn_wgt*luminosity)*1.; // the weights!=1 are for the Z0 template. The weights==1 are for the DYmumu events
			else                eta_weight = 1.;                       // the weights!=1 are for the Z0 template. The weights==1 are for the DYmumu events
			mass_weight = (xscn_wgt*luminosity)*1.;
		}
		else
		{
			if(doXSlumiWeights) eta_weight = (xscn_wgt*luminosity)*eta_wgt;
			else                eta_weight = eta_wgt;
			mass_weight = (xscn_wgt*luminosity)*mass_wgt;
		}
				
		fill(eta_rec,eta_weight);
		
		vhMass[mod]->Fill(mass_rec,mass_weight);
	}
	return N;
}

void draw(TObject* tobj, TString oName, TString drawopt="", Bool_t logx=!dolog, Bool_t logy=!dolog)
{
	_DEBUG("draw");
	TString cName = "c"+oName;
	cnvMap.insert( make_pair(oName, new TCanvas(cName,cName,600,400)) );
	if(logx) cnvMap[oName]->SetLogx();
	if(logy) cnvMap[oName]->SetLogy();
	cnvMap[oName]->cd();
	tobj->Draw(drawopt);
}

void drawon(TString existing_oName, TObject* tobj, TString drawopt="")
{
	_DEBUG("drawon");
	cnvMap[existing_oName]->cd();
	tobj->Draw(drawopt+" SAMES");
}

void show(TObject* tobj, TString oName, TString drawopt="")
{
	_DEBUG("show");
	TString cName = "c"+oName;
	TCanvas* cnv = new TCanvas(cName,cName,600,400);
	cnv->cd();
	cnv->Draw();
	tobj->Draw(drawopt);
	TString oPath = "plots/"+oName;
	cnv->SaveAs(oPath);
	delete cnv;
}

void save(TString oDir)
{
	_DEBUG("save");
	for(TMapTSP2TCNV::iterator it=cnvMap.begin() ; it!=cnvMap.end() ; ++it)
	{
		TString pName = oDir+"/"+it->first;
		it->second->SaveAs(pName+".png");
		it->second->SaveAs(pName+".eps");
		it->second->SaveAs(pName+".pdf");
		it->second->SaveAs(pName+".root");
		it->second->SaveAs(pName+".C");
	}
	TString pName = oDir+"/ellipticityhistograms.root";
	TFile* f = new TFile(pName,"RECREATE");
	f->cd();
	for(int i=0 ; i<(int)vhEllipticity.size() ; i++) vhEllipticity[i]->Write();
	for(int i=0 ; i<(int)vhMass.size() ; i++)        vhMass[i]->Write();
	f->Write();
	f->Close();
	delete f;
}

void ellipticity()
{
	msglvl[DBG] = SILENT;
	msglvl[INF] = VISUAL;
	msglvl[WRN] = VISUAL;
	msglvl[ERR] = VISUAL;
	msglvl[FAT] = VISUAL;

	_DEBUG("ellipticity");
	style();
	colors();
	setLogBins(nlogmassbins,logmassmin,logmassmax,logmassbins);
	setLogBins(nlogimassbins,logimassmin,logimassmax,logimassbins);
	
	vhEllipticity.push_back ( new TH1D("hEllipticity_Z0", ";m_{#mu#mu} Gev;E_{#eta}",nlogmassbins,logmassbins) );
	vhEllipticity.push_back ( new TH1D("hEllipticity_ZP", ";m_{#mu#mu} Gev;E_{#eta}",nlogmassbins,logmassbins) );
	vhEllipticity.push_back ( new TH1D("hEllipticity_KK", ";m_{#mu#mu} Gev;E_{#eta}",nlogmassbins,logmassbins) );
	vhEllipticity.push_back ( new TH1D("hEllipticity_DT", ";m_{#mu#mu} Gev;E_{#eta}",nlogmassbins,logmassbins) );

	vhMass.push_back ( new TH1D("hMass_Z0", ";m_{#mu#mu} Gev;Events",nlogimassbins,logimassbins) );
	vhMass.push_back ( new TH1D("hMass_ZP", ";m_{#mu#mu} Gev;Events",nlogimassbins,logimassbins) );
	vhMass.push_back ( new TH1D("hMass_KK", ";m_{#mu#mu} Gev;Events",nlogimassbins,logimassbins) );
	vhMass.push_back ( new TH1D("hMass_DT", ";m_{#mu#mu} Gev;Events",nlogimassbins,logimassbins) );
	
	for(int massbin=1 ; massbin<=nlogmassbins ; massbin++)
	{	
		TString sMassBin = (TString)_s(massbin);
		for(int mod=Z0 ; mod<=DT ; mod++)
		{
			/////////////////
			// initialize ///
			reset(); ////////
			/////////////////
			
			TString sModel = "";
			if(mod==Z0) sModel = "Z0";
			if(mod==ZP) sModel = "ZP";
			if(mod==KK) sModel = "KK";
			if(mod==DT) sModel = "DT";
		
			/////////////////////////////
			setTree(sModel,sMassBin); ///
			/////////////////////////////
			
			Int_t N = loop(mod);
			_INFO("N(model="+(string)sModel+", massbin="+_s(massbin)+") = "+_s(N));
			if(N>10)
			{
				// correct(hEtaSides, sModel, massbin);
				// correct(hEtaCentral, sModel, massbin);
				// correct(hEtaTotal, sModel, massbin);
			
				TString hname = "";
				hname = (TString)hEtaSides->GetName()+"_"+sModel+"_massbin_"+(TString)_s(massbin)+".png";
				show(hEtaSides, hname);
				hname = (TString)hEtaCentral->GetName()+"_"+sModel+"_massbin_"+(TString)_s(massbin)+".png";
				show(hEtaCentral, hname);
				hname = (TString)hEtaTotal->GetName()+"_"+sModel+"_massbin_"+(TString)_s(massbin)+".png";
				show(hEtaTotal, hname);
			
				Double_t Nsides   = hintegral(hEtaSides);
				Double_t Ncentral = hintegral(hEtaCentral);
				// Double_t Nall     = hintegral(hEtaTotal);
				Double_t Nall     = Nsides+Ncentral;
				_INFO("In bin "+_s(massbin)+", model "+(string)sModel+"  ->  Ncentral="+_s(Ncentral)+", Nsides="+_s(Nsides));
				if(Nall!=Nsides+Ncentral) _WARNING("In bin "+_s(massbin)+", model "+(string)sModel+"  ->  Nall="+_s(Nall)+" != Nsides+Ncentral="+_s(Nsides+Ncentral));
				Double_t Eeta  = (Nall!=0.) ? (Ncentral-Nsides)/Nall : -999.;
				Double_t dEeta = (Nall!=0.) ? sqrt((1.-Eeta*Eeta)/Nall) : 0.;
				vhEllipticity[mod]->SetBinContent(massbin,Eeta);
				vhEllipticity[mod]->SetBinError(massbin,dEeta);
			}
		}
	}
	
	leg_mHat = new TLegend(0.1457286,0.1678322,0.370603,0.4440559,NULL,"brNDC");
	leg_mHat->SetFillColor(kWhite);
	
	pvtxt = new TPaveText(0.3077889,0.6206294,0.4723618,0.715035,"brNDC");
	pvtxt->SetFillColor(kWhite);
	
	pvtxt_lumi = new TPaveText(0.3944724,0.1695804,0.5464824,0.2832168,"brNDC");
	pvtxt_lumi->SetFillColor(kWhite);
	TString sLumi = (TString)tostring(luminosity,2);
	txt = pvtxt_lumi->AddText( "#intLdt~"+ sLumi +" fb^{-1}" );
	
	pvtxt_atlas = new TPaveText(0.4057789,0.7202797,0.5703518,0.8146853,"brNDC");
	pvtxt_atlas->SetFillColor(0);
	pvtxt_atlas->SetTextFont(42);
	txt = pvtxt_atlas->AddText("#bf{#splitline{#it{ATLAS}}{#scale[0.42]{work in progress}}}");
	
	cnvEllipticity = new TCanvas("cnvEllipticity", "cnvEllipticity", 0,0,1200,800);
	pad_mHat = new TPad("padMhat","",0,0,1,1);
	pad_mHat->SetFillColor(kWhite);
	pad_mHat->SetTicky(0);
	pad_mHat->SetLogy();
	pad_mHat->SetLogx();
	pad_ellipticity = new TPad("padAfb", "",0,0,1,1);
	pad_ellipticity->SetTicky(0);
	pad_ellipticity->SetTickx(1);
	pad_ellipticity->SetFillStyle(0);
	pad_ellipticity->SetFrameFillStyle(4000); //will be transparent
	pad_ellipticity->SetFrameFillColor(0);
	pad_ellipticity->SetLogx();
	
	
	cnvEllipticity->cd();
	pad_mHat->Draw();
	pad_mHat->cd();
	vhMass[KK]->SetMaximum(1.5*vhMass[KK]->GetMaximum());
	vhMass[KK]->SetMinimum((vhMass[Z0]->GetMinimum()<=0) ? 1. : 0.5*vhMass[Z0]->GetMinimum());
	vhMass[KK]->SetLineColor(vModelColor[KK]);
	vhMass[KK]->SetLineStyle(5);
	vhMass[KK]->GetXaxis()->SetMoreLogLabels();
	vhMass[KK]->GetXaxis()->SetNoExponent();
	vhMass[KK]->Draw();
	vhMass[Z0]->SetLineColor(vModelColor[Z0]);
	vhMass[Z0]->SetLineStyle(2);
	vhMass[Z0]->GetXaxis()->SetMoreLogLabels();
	vhMass[Z0]->GetXaxis()->SetNoExponent();
	vhMass[Z0]->Draw("SAMES");
	vhMass[ZP]->SetLineColor(vModelColor[ZP]);
	vhMass[ZP]->SetLineStyle(3);
	vhMass[ZP]->GetXaxis()->SetMoreLogLabels();
	vhMass[ZP]->GetXaxis()->SetNoExponent();
	vhMass[ZP]->Draw("SAMES");
	vhMass[DT]->SetLineColor(vModelColor[DT]);
	vhMass[DT]->SetLineStyle(1);
	vhMass[DT]->GetXaxis()->SetMoreLogLabels();
	vhMass[DT]->GetXaxis()->SetNoExponent();
	vhMass[DT]->Draw("SAMES");
	
	
	cnvEllipticity->cd();
	pad_ellipticity->Draw();
	pad_ellipticity->cd();
	vhEllipticity[KK]->GetYaxis()->SetRangeUser(-1.5,+1.5);
	vhEllipticity[KK]->SetFillStyle(3018);
	vhEllipticity[KK]->SetFillColor(vModelColor[KK]);
	vhEllipticity[KK]->SetLineColor(vModelColor[KK]);
	vhEllipticity[KK]->GetXaxis()->SetMoreLogLabels(); 
	vhEllipticity[KK]->GetXaxis()->SetNoExponent();
	vhEllipticity[KK]->Draw("E5 Y+");
	vhEllipticity[Z0]->SetFillStyle(3003);
	vhEllipticity[Z0]->SetFillColor(vModelColor[Z0]);
	vhEllipticity[Z0]->SetLineColor(vModelColor[Z0]);
	vhEllipticity[Z0]->GetXaxis()->SetMoreLogLabels(); 
	vhEllipticity[Z0]->GetXaxis()->SetNoExponent();
	vhEllipticity[Z0]->Draw("E5 Y+ SAMES");
	vhEllipticity[ZP]->SetFillStyle(3017);
	vhEllipticity[ZP]->SetFillColor(vModelColor[ZP]);
	vhEllipticity[ZP]->SetLineColor(vModelColor[ZP]);
	vhEllipticity[ZP]->GetXaxis()->SetMoreLogLabels(); 
	vhEllipticity[ZP]->GetXaxis()->SetNoExponent();
	vhEllipticity[ZP]->Draw("E5 Y+ SAMES");
	vhEllipticity[DT]->SetMarkerStyle(24);
	vhEllipticity[DT]->SetLineColor(vModelColor[DT]);
	vhEllipticity[DT]->SetMarkerColor(vModelColor[DT]);
	vhEllipticity[DT]->SetLineWidth(2);
	vhEllipticity[DT]->SetMarkerSize(2);
	vhEllipticity[DT]->GetXaxis()->SetMoreLogLabels(); 
	vhEllipticity[DT]->GetXaxis()->SetNoExponent(); 
	vhEllipticity[DT]->Draw("Y+ e1x1 SAMES");
	
	leg_mHat->AddEntry( vhMass[DT], "2011 Data: Events", "l");
	leg_mHat->AddEntry( vhEllipticity[DT], "2011 Data: E_{#eta}", "lep");
	leg_mHat->AddEntry( vhMass[Z0], "#gamma/Z^{0} [MC10b]: Events", "l");
	leg_mHat->AddEntry( vhEllipticity[Z0], "#gamma/Z^{0} [MC10b]: E_{#eta}", "f");
	leg_mHat->AddEntry( vhMass[ZP], "1 TeV Z'_{SSM} [Template MC10b]: Events", "l");
	leg_mHat->AddEntry( vhEllipticity[ZP], "1 TeV Z'_{SSM} [Template MC10b]: E_{#eta}", "f");
	leg_mHat->AddEntry( vhMass[KK], "1 TeV #gamma_{KK}/Z_{KK} [Template MC10b]: Events", "l");
	leg_mHat->AddEntry( vhEllipticity[KK], "1 TeV #gamma_{KK}/Z_{KK} [Template MC10b]: E_{#eta}", "f");
	
	
	pvtxt_lumi->Draw("SAMES");
	pvtxt_atlas->Draw("SAMES");
	leg_mHat->Draw("SAMES");
	cnvEllipticity->cd();
	pad_mHat->cd();
	pad_mHat->RedrawAxis();
	pad_mHat->Update();
	cnvEllipticity->Update();
	
	cnvEllipticity->SaveAs("plots/Ellipticity.root");
	cnvEllipticity->SaveAs("plots/Ellipticity.C");
	cnvEllipticity->SaveAs("plots/Ellipticity.eps");
	cnvEllipticity->SaveAs("plots/Ellipticity.ps");
	cnvEllipticity->SaveAs("plots/Ellipticity.pdf");
	cnvEllipticity->SaveAs("plots/Ellipticity.png");
	
	save("plots");
}
