#include "basicIncludes.h"

TTree* tree;
TH1D* hyStarCentral = new TH1D("hyStarCentral", ";y*;Events", nystarbins,minystar,maxystar);
TH1D* hyStarTotal   = new TH1D("hyStarTotal", ";y*;Events",   nystarbins,minystar,maxystar);

TPaveText* pvtxt_lumi;
TPaveText* pvtxt_atlas;
TCanvas* cnvFchi;
TPad *pad_mHat;
TPad *pad_Fchi;
TLegend* leg;
TLegend* leg_mHat;
TPaveText* pvtxt;
TText* txt;
vector<TH1D*> vhFchi;
vector<TH1D*> vhMass;
TMapTSP2TCNV  cnvMap;
kinematics* kin;
Bool_t dolog=true;


float mass_tru, mass_rec, mass_wgt;
float cost_tru, cost_rec, cost_wgt;
float yQ_tru, yQ_rec, yQ_wgt;
float eta_tru, eta_rec, eta_wgt;
float yStar_tru, yStar_rec, yStar_wgt;
float xscn_wgt;
TLorentzVector* tlv1Tru;
TLorentzVector* tlv2Tru;
TLorentzVector* tlv1Rec;
TLorentzVector* tlv2Rec;

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

TH1* correct(TH1* hPyhsics, TString sModel, int massbin)
{
	TString hName = "";
	if(sModel=="Z0" || sModel=="DT") hName = "hyStarZ0d3pd_acceptance_"+(TString)_s(massbin);
	else                             hName = "hyStar"+sModel+"_acceptance_"+(TString)_s(massbin);
	
	TH1* hAcceptance = (TH1D*)file->Get("yStar_histograms/"+hName);
	if(hAcceptance->GetNbinsX()!=hPyhsics->GetNbinsX())
	{
		_ERROR("hAcceptance->GetNbinsX()!=hPyhsics->GetNbinsX()  ->  "+_s(hAcceptance->GetNbinsX())+":"+_s(hPyhsics->GetNbinsX())+", exitting now");
		exit(-1);
	}
	
	TH1* hCorrected = (TH1*)hPyhsics->Clone("");
	hCorrected->Divide(hAcceptance);
	
	return hCorrected;
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
	tree->SetBranchAddress( "yStar_tru",  &yStar_tru );
	tree->SetBranchAddress( "yStar_rec",  &yStar_rec );
	tree->SetBranchAddress( "yStar_wgt",  &yStar_wgt );
	tree->SetBranchAddress( "xscn_wgt", &xscn_wgt );
	
	tree->SetBranchAddress( "tlv1Tru", &tlv1Tru );
	tree->SetBranchAddress( "tlv2Tru", &tlv2Tru );
	tree->SetBranchAddress( "tlv1Rec", &tlv1Rec );
	tree->SetBranchAddress( "tlv2Rec", &tlv2Rec );
}

void reset()
{
	_DEBUG("reset");
	hyStarCentral->Reset();
	hyStarTotal->Reset();
}

void fill(float yStar, float wgt=1.)
{
	_DEBUG("fill");
	if(fabs(yStar)<=ystarhigh) hyStarTotal->Fill(yStar,wgt);
	if(fabs(yStar)<=ystarlow)  hyStarCentral->Fill(yStar,wgt);
}

Int_t loop(int mod)
{
	_DEBUG("loop");
	Int_t N = tree->GetEntries();
	float yStar_weight = 1.;
	float mass_weight  = 1.;
	for(Int_t i=0 ; i<N ; i++)
	{
		tree->GetEntry(i);
		if(mod==DT)
		{
			yStar_weight = 1.;
		}
		else if(mod==Z0)
		{
			if(doXSlumiWeights) yStar_weight = (xscn_wgt*luminosity)*1.; // the weights!=1 are for the Z0 template. The weights==1 are for the DYmumu events
			else                yStar_weight = 1.;                       // the weights!=1 are for the Z0 template. The weights==1 are for the DYmumu events
			mass_weight = (xscn_wgt*luminosity)*1.;
		}
		else
		{
			if(doXSlumiWeights) yStar_weight = (xscn_wgt*luminosity)*yStar_wgt;
			else                yStar_weight = yStar_wgt;
			mass_weight = (xscn_wgt*luminosity)*mass_wgt;
		}
		
		
		if(fabs(kin->yB(tlv1Rec,tlv2Rec))>1.1) continue;
		fill(yStar_rec,yStar_weight);
		
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
	for(int i=0 ; i<(int)vhFchi.size() ; i++) vhFchi[i]->Write();
	for(int i=0 ; i<(int)vhMass.size() ; i++) vhMass[i]->Write();
	f->Write();
	f->Close();
	delete f;
}

void Fchi()
{
	msglvl[DBG] = SILENT;
	msglvl[INF] = VISUAL;
	msglvl[WRN] = VISUAL;
	msglvl[ERR] = VISUAL;
	msglvl[FAT] = VISUAL;

	_DEBUG("Fchi");
	style();
	colors();
	setLogBins(nlogmassbins,logmassmin,logmassmax,logmassbins);
	setLogBins(nlogimassbins,logimassmin,logimassmax,logimassbins);
	
	vhFchi.push_back ( new TH1D("hFchi_Z0", ";m_{#mu#mu} Gev;F_{#chi}",nlogmassbins,logmassbins) );
	vhFchi.push_back ( new TH1D("hFchi_ZP", ";m_{#mu#mu} Gev;F_{#chi}",nlogmassbins,logmassbins) );
	vhFchi.push_back ( new TH1D("hFchi_KK", ";m_{#mu#mu} Gev;F_{#chi}",nlogmassbins,logmassbins) );
	vhFchi.push_back ( new TH1D("hFchi_DT", ";m_{#mu#mu} Gev;F_{#chi}",nlogmassbins,logmassbins) );

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
				TH1D* hyStarCentralCorrected = (TH1D*)correct(hyStarCentral, sModel, massbin);
				TH1D* hyStarTotalCorrected   = (TH1D*)correct(hyStarTotal,   sModel, massbin);
			
				TString hname = "";
				hname = (TString)hyStarCentral->GetName()+"_"+sModel+"_massbin_"+(TString)_s(massbin)+".png";
				show(hyStarCentral, hname);
				hname = (TString)hyStarTotal->GetName()+"_"+sModel+"_massbin_"+(TString)_s(massbin)+".png";
				show(hyStarTotal, hname);
				
				hname = (TString)hyStarCentralCorrected->GetName()+"_corrected_"+sModel+"_massbin_"+(TString)_s(massbin)+".png";
				show(hyStarCentralCorrected, hname);
				hname = (TString)hyStarTotalCorrected->GetName()+"_corrected_"+sModel+"_massbin_"+(TString)_s(massbin)+".png";
				show(hyStarTotalCorrected, hname);
				
				TString hName = "";
				if(mod==Z0 || mod==DT) hName = "hyStarZ0d3pd_acceptance_"+(TString)_s(massbin);
				else                   hName = "hyStar"+sModel+"_acceptance_"+(TString)_s(massbin);
				show((TH1D*)file->Get("yStar_histograms/"+hName), hName+".png");

				Double_t Ncentral = hintegral(hyStarCentralCorrected);
				Double_t Nall     = hintegral(hyStarTotalCorrected);
				_INFO("In bin "+_s(massbin)+", model "+(string)sModel+"  ->  Ncentral="+_s(Ncentral)+", Nall="+_s(Nall));
				Double_t fchi  = (Nall!=0.) ? Ncentral/Nall : -999.;
				Double_t dfchi = (Nall!=0.) ? sqrt((1.-fchi*fchi)/Nall) : 0.;
				vhFchi[mod]->SetBinContent(massbin,fchi);
				vhFchi[mod]->SetBinError(massbin,dfchi);
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
	
	cnvFchi = new TCanvas("cnvFchi", "cnvFchi", 0,0,1200,800);
	pad_mHat = new TPad("padMhat","",0,0,1,1);
	pad_mHat->SetFillColor(kWhite);
	pad_mHat->SetTicky(0);
	pad_mHat->SetLogy();
	pad_mHat->SetLogx();
	pad_Fchi = new TPad("padFchi", "",0,0,1,1);
	pad_Fchi->SetTicky(0);
	pad_Fchi->SetTickx(1);
	pad_Fchi->SetFillStyle(0);
	pad_Fchi->SetFrameFillStyle(4000); //will be transparent
	pad_Fchi->SetFrameFillColor(0);
	pad_Fchi->SetLogx();
	
	
	cnvFchi->cd();
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
	
	
	cnvFchi->cd();
	pad_Fchi->Draw();
	pad_Fchi->cd();
	vhFchi[KK]->GetYaxis()->SetRangeUser(-1.5,+1.5);
	vhFchi[KK]->SetFillStyle(3018);
	vhFchi[KK]->SetFillColor(vModelColor[KK]);
	vhFchi[KK]->SetLineColor(vModelColor[KK]);
	vhFchi[KK]->GetXaxis()->SetMoreLogLabels(); 
	vhFchi[KK]->GetXaxis()->SetNoExponent();
	vhFchi[KK]->Draw("E5 Y+");
	vhFchi[Z0]->SetFillStyle(3003);
	vhFchi[Z0]->SetFillColor(vModelColor[Z0]);
	vhFchi[Z0]->SetLineColor(vModelColor[Z0]);
	vhFchi[Z0]->GetXaxis()->SetMoreLogLabels(); 
	vhFchi[Z0]->GetXaxis()->SetNoExponent();
	vhFchi[Z0]->Draw("E5 Y+ SAMES");
	vhFchi[ZP]->SetFillStyle(3017);
	vhFchi[ZP]->SetFillColor(vModelColor[ZP]);
	vhFchi[ZP]->SetLineColor(vModelColor[ZP]);
	vhFchi[ZP]->GetXaxis()->SetMoreLogLabels(); 
	vhFchi[ZP]->GetXaxis()->SetNoExponent();
	vhFchi[ZP]->Draw("E5 Y+ SAMES");
	vhFchi[DT]->SetMarkerStyle(24);
	vhFchi[DT]->SetLineColor(vModelColor[DT]);
	vhFchi[DT]->SetMarkerColor(vModelColor[DT]);
	vhFchi[DT]->SetLineWidth(2);
	vhFchi[DT]->SetMarkerSize(2);
	vhFchi[DT]->GetXaxis()->SetMoreLogLabels(); 
	vhFchi[DT]->GetXaxis()->SetNoExponent(); 
	vhFchi[DT]->Draw("Y+ e1x1 SAMES");
	
	leg_mHat->AddEntry( vhMass[DT], "2011 Data: Events", "l");
	leg_mHat->AddEntry( vhFchi[DT], "2011 Data: F_{#chi}", "lep");
	leg_mHat->AddEntry( vhMass[Z0], "#gamma/Z^{0} [MC10b]: Events", "l");
	leg_mHat->AddEntry( vhFchi[Z0], "#gamma/Z^{0} [MC10b]: F_{#chi}", "f");
	leg_mHat->AddEntry( vhMass[ZP], "1 TeV Z'_{SSM} [Template MC10b]: Events", "l");
	leg_mHat->AddEntry( vhFchi[ZP], "1 TeV Z'_{SSM} [Template MC10b]: F_{#chi}", "f");
	leg_mHat->AddEntry( vhMass[KK], "1 TeV #gamma_{KK}/Z_{KK} [Template MC10b]: Events", "l");
	leg_mHat->AddEntry( vhFchi[KK], "1 TeV #gamma_{KK}/Z_{KK} [Template MC10b]: F_{#chi}", "f");
	
	
	pvtxt_lumi->Draw("SAMES");
	pvtxt_atlas->Draw("SAMES");
	leg_mHat->Draw("SAMES");
	cnvFchi->cd();
	pad_mHat->cd();
	pad_mHat->RedrawAxis();
	pad_mHat->Update();
	cnvFchi->Update();
	
	cnvFchi->SaveAs("plots/Fchi.root");
	cnvFchi->SaveAs("plots/Fchi.C");
	cnvFchi->SaveAs("plots/Fchi.eps");
	cnvFchi->SaveAs("plots/Fchi.ps");
	cnvFchi->SaveAs("plots/Fchi.pdf");
	cnvFchi->SaveAs("plots/Fchi.png");
	
	save("plots");
}
