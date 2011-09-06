#include "basicIncludes.h"

TTree* tree;
TH1D* hEtaCentral = new TH1D("hEtaCentral", ";#eta;Events", 25,-2.5,+2.5);
TH1D* hEtaSides   = new TH1D("hEtaSides", ";#eta;Events", 25,-2.5,+2.5);
TH1D* hEtaTotal   = new TH1D("hEtaTotal", ";#eta;Events", 25,-2.5,+2.5);

vector<TH1D*> vhEllipticity;
TMapTSP2TCNV  cnvMap;
Bool_t dolog=true;

float mass_tru, mass_rec, mass_wgt;
float cost_tru, cost_rec, cost_wgt;
float yQ_tru, yQ_rec, yQ_wgt;
float xscn_wgt;

TFile* file = new TFile("/srv01/tau/hod/z0analysis-tests/z0analysis-tmp_qsub/pythia8/weights.root", "READ");

float theta2eta(float costheta)
{
	_DEBUG("theta2eta");
	return -1.*log(tan(acos(costheta)/2.));
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
		if(fabs(eta)<=etax) hEtaCentral->Fill(eta,wgt);
		else                hEtaSides->Fill(eta,wgt);
		hEtaTotal->Fill(eta,wgt);
	}
}

Int_t loop(int mod)
{
	_DEBUG("loop");
	Int_t N = tree->GetEntries();
	float w = 1.;
	for(Int_t i=0 ; i<N ; i++)
	{
		tree->GetEntry(i);
		if(mod==DT)
		{
			w = 1.;
		}
		else if(mod==Z0)
		{
			w = (xscn_wgt*luminosity)*1.; // the weights!=1 are for the Z0 template. The weights==1 are for the DYmumu events
		}
		else
		{
			w = (xscn_wgt*luminosity)*cost_wgt;
		}
		float eta = theta2eta(cost_rec);
		fill(eta,w);
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
	setLogBins(nlogmassbins,logmassmin,logmassmax,logmassbins);
	
	vhEllipticity.push_back ( new TH1D("hEllipticity_Z0", ";m_{#mu#mu} Gev;E_{#eta}",nlogmassbins,logmassbins) );
	vhEllipticity.push_back ( new TH1D("hEllipticity_ZP", ";m_{#mu#mu} Gev;E_{#eta}",nlogmassbins,logmassbins) );
	vhEllipticity.push_back ( new TH1D("hEllipticity_KK", ";m_{#mu#mu} Gev;E_{#eta}",nlogmassbins,logmassbins) );
	vhEllipticity.push_back ( new TH1D("hEllipticity_DT", ";m_{#mu#mu} Gev;E_{#eta}",nlogmassbins,logmassbins) );
	
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
				Double_t Nsides   = hEtaSides->Integral();
				Double_t Ncentral = hEtaCentral->Integral();
				Double_t Nall     = hEtaTotal->Integral();
				Double_t Eeta  = (Nall!=0.) ? (Ncentral-Nsides)/Nall : -999.;
				Double_t dEeta = (Nall!=0.) ? sqrt((1.-Eeta*Eeta)/Nall) : -999.;
				vhEllipticity[mod]->SetBinContent(massbin,Eeta);
				vhEllipticity[mod]->SetBinError(massbin,dEeta);
			}
		}
	}
	
	vhEllipticity[Z0]->SetMinimum(-1.);
	vhEllipticity[Z0]->SetMaximum(+1.);
	vhEllipticity[Z0]->SetFillStyle(3003);
	vhEllipticity[Z0]->SetFillColor(kGreen);
	vhEllipticity[Z0]->SetLineColor(kGreen);
	vhEllipticity[Z0]->GetXaxis()->SetMoreLogLabels();
	vhEllipticity[Z0]->GetXaxis()->SetNoExponent();
	draw(vhEllipticity[Z0], "hEllipticity_Z0", "E5 Y+", dolog);

	vhEllipticity[ZP]->SetFillStyle(3017);
	vhEllipticity[ZP]->SetFillColor(kBlue);
	vhEllipticity[ZP]->SetLineColor(kBlue);
	drawon("hEllipticity_Z0", vhEllipticity[ZP], "E5 Y+ SAMES");
	
	vhEllipticity[KK]->SetFillStyle(3018);
	vhEllipticity[KK]->SetFillColor(kRed);
	vhEllipticity[KK]->SetLineColor(kRed);
	drawon("hEllipticity_Z0", vhEllipticity[KK], "E5 Y+ SAMES");
	
	vhEllipticity[DT]->SetMarkerStyle(24);
	vhEllipticity[DT]->SetLineColor(kBlack);
	vhEllipticity[DT]->SetMarkerColor(kBlack);
	drawon("hEllipticity_Z0", vhEllipticity[DT], "e1x1 SAMES");
	
	save("plots");
}
