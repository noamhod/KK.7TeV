#include "../include/rawStd.h"
#include "../include/rawROOT.h"
#include "../include/logs.h"
#include "../include/style.h"
#include "../include/bins.h"
#include "../include/histos.h"
#include "../include/fkinematics.h"
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

TH1D* stitch(vector<TH1D*>& vh, TString name="", TString titles="")
{
	unsigned int vhsize = vh.size();

	Int_t    nbins = vhsize*vh[0]->GetNbinsX();
	Double_t xmin  = vh[0]->GetBinLowEdge(1);
	Double_t xmax  = vhsize*(vh[0]->GetBinLowEdge(vh[0]->GetNbinsX()) + vh[0]->GetBinWidth(vh[0]->GetNbinsX()));

	TH1D* hStitched = new TH1D(name, titles, nbins, xmin, xmax);

	Int_t noffsetbins = vh[0]->GetNbinsX();
	for(unsigned int i=0 ; i<vhsize ; i++)
	{
		for(int b=1 ; b<=vh[i]->GetNbinsX() ; b++)
		{
			Int_t bin = b + (Int_t)(i*noffsetbins);
			hStitched->SetBinContent(bin, vh[i]->GetBinContent(b));
		}
	}
	
	// TCanvas* cnv = new TCanvas(name,name,1000,400);
	// cnv->Draw();
	// cnv->cd();
	// hStitched->Draw();
	// cnv->SaveAs("plots/test_"+name+".png");
	
	return hStitched;
}

void Graviton()
{
	msglvl[DBG] = VISUAL;
    msglvl[INF] = VISUAL;
    msglvl[WRN] = VISUAL;
    msglvl[ERR] = VISUAL;
    msglvl[FAT] = VISUAL;

	for (int i=0 ; i<gApplication->Argc() ; i++)
	{
		#ifdef VERBOSEARGS
			printf("Arg  %d:  %s\n",i,gApplication->Argv(i));
		#endif
	}
	
	if(gApplication->Argc()<2)
	{
		cerr << "gApplication->Argc()=" << gApplication->Argc() << ", exitting now." << endl;
	}
	
	TString sProc = "";
	for(int i=0 ; i<gApplication->Argc() ; i++)
	{	
		if(!(strcmp(gApplication->Argv(i),"--proc")))
		{
			sProc = c2ts(gApplication->Argv(i+1));
		}
	}
	_INFO("processs: "+(string)sProc);

	bool doLogx = false;
	
	// remember old dir
	TDirectory* olddir = gDirectory;

	style();
	setLogBins(nloglimitimassbins,loglimitimassmin,loglimitimassmax,loglimitimassbins);

	vector<float>* eta;
	vector<float>* phi;
	vector<float>* pt;
	vector<float>* E;
	//vector<float>* m;
	vector<float>* charge;
	
	TLorentzVector* pa = new TLorentzVector;
	TLorentzVector* pb = new TLorentzVector;
	
	TFile* fTemplates = new TFile("../data/"+sProc+"TemplatesMM.root", "RECREATE");
	TDirectory* dir_cosThetaSlices = (TDirectory*)fTemplates->mkdir("template_cosThetaSlices");
	TDirectory* dir_dEtaSlices     = (TDirectory*)fTemplates->mkdir("template_dEtaSlices");
	
	TObjArray* template_cosThetaSlices = new TObjArray;
	template_cosThetaSlices->SetName("template_cosThetaSlices");
	template_cosThetaSlices->SetOwner(kTRUE);
	TObjArray* template_dEtaSlices = new TObjArray;
	template_dEtaSlices->SetName("template_dEtaSlices");
	template_dEtaSlices->SetOwner(kTRUE);

	olddir->cd();
	
	int nMassPoints = 0;
	if(sProc=="Gmm")
	{
		nMassPoints = 3;
	}
	else if(sProc=="DYmumu")
	{
		nMassPoints = 1;
	}
	
	for(int mspt=0 ; mspt<nMassPoints ; mspt++)
	{
		TString tsName  = "";
		TString tsIndex = "";
		TString tsMass  = "";
		TString tsTitle = "";
		float Gmass = 0.;
		
		if(sProc=="Gmm")
		{
			switch(mspt)
			{
				case 0: tsName = "Gmm_01_1750"; Gmass = 1750.; break;
				case 1: tsName = "Gmm_01_2000"; Gmass = 2000.; break;
				case 2: tsName = "Gmm_01_2250"; Gmass = 2250.; break;
				default: break;
			}
			tsIndex = (TString)_s(mspt);
			tsMass  = (TString)_s(Gmass);
			tsTitle = tsMass+" GeV G*#rightarrow#mu#mu ";
		}
		else if(sProc=="DYmumu")
		{
			tsIndex = (TString)_s(mspt);
			tsMass  = (TString)_s(Gmass);
			tsTitle = "DY#rightarrow#mu#mu ";
		}
		
	
		TCanvas* cnv_cosTheta     = new TCanvas("cnv_cosTheta_"+tsName,"cnv_cosTheta_"+tsName,600,400);
		TCanvas* cnv_dEta         = new TCanvas("cnv_dEta_"+tsName,"cnv_dEta_"+tsName,600,400);
		TCanvas* cnv_mHat         = new TCanvas("cnv_mHat_"+tsName,"cnv_mHat_"+tsName,600,400);
		TCanvas* cnv_mHatCosTheta = new TCanvas("cnv_mHatCosTheta_"+tsName,"cnv_mHatCosTheta_"+tsName,600,400);
		TCanvas* cnv_stitched     = new TCanvas("cnv_stitched_"+tsName,"cnv_stitched_"+tsName,600,600);
		cnv_stitched->Divide(1,2);
	
	
		TH1D* h_dEta         = new TH1D("h_dEta_"+tsName, tsTitle+"#Delta#eta;#Delta#eta;Events", ndEtaBinsLimit,mindEtaLimit,maxdEtaLimit);
		TH1D* h_cosTheta     = new TH1D("h_cosTheta_"+tsName, tsTitle+"cos#theta*;cos#theta*;Events", nCosThetaBinsLimit,minCosThetaLimit,maxCosThetaLimit);
		TH1D* h_mHat         = new TH1D("h_mHat_"+tsName, tsTitle+"mass;m_{#mu#mu} TeV;Events", nloglimitimassbins,loglimitimassbins);
		TH2D* h_mHatCosTheta = new TH2D("h_mHatCosTheta_"+tsName, tsTitle+"mass vs. cos#theta*;m_{#mu#mu} TeV;cos#theta* (#mu-);Events", nloglimitimassbins,loglimitimassbins, nCosThetaBinsLimit,minCosThetaLimit,maxCosThetaLimit);
		
		TCanvas* cnv_mHat_cosThetaSlices = new TCanvas("cnv_mHat_cosThetaSlices_"+tsName,"cnv_mHat_cosThetaSlices_"+tsName,600,800);
		vector<TH1D*>        vh_mHat_cosThetaSlices;
		vector<TVirtualPad*> vp_mHat_cosThetaSlices;
		cnv_mHat_cosThetaSlices->Divide(1,nCosThetaBinsLimit);
		for(int i=1 ; i<=nCosThetaBinsLimit ; i++)
		{
			if(doLogx) vh_mHat_cosThetaSlices.push_back( new TH1D("h_"+tsName+"_mHat_cosThetaSlice"+(TString)_s(i), tsTitle+"mass in cos#theta* slice "+(TString)_s(i)+";m_{#mu#mu} TeV;Events", nloglimitimassbins,loglimitimassbins) );
			else       vh_mHat_cosThetaSlices.push_back( new TH1D("h_"+tsName+"_mHat_cosThetaSlice"+(TString)_s(i), tsTitle+"mass in cos#theta* slice "+(TString)_s(i)+";m_{#mu#mu} TeV;Events", nlinlimitimassbins,linlimitimassmin,linlimitimassmax) );
			vp_mHat_cosThetaSlices.push_back( (TVirtualPad*)cnv_mHat_cosThetaSlices->cd(i) );
		}
		
		TCanvas* cnv_mHat_dEtaSlices = new TCanvas("cnv_mHat_dEtaSlices_"+tsName,"cnv_mHat_dEtaSlices_"+tsName,600,800);
		vector<TH1D*>        vh_mHat_dEtaSlices;
		vector<TVirtualPad*> vp_mHat_dEtaSlices;
		cnv_mHat_dEtaSlices->Divide(1,ndEtaBinsLimit);
		for(int i=1 ; i<=ndEtaBinsLimit ; i++)
		{
			if(doLogx) vh_mHat_dEtaSlices.push_back( new TH1D("h_"+tsName+"_mHat_dEtaSlice"+(TString)_s(i), tsTitle+"mass in cos#theta* slice "+(TString)_s(i)+";m_{#mu#mu} TeV;Events", nloglimitimassbins,loglimitimassbins) );
			else       vh_mHat_dEtaSlices.push_back( new TH1D("h_"+tsName+"_mHat_dEtaSlice"+(TString)_s(i), tsTitle+"mass in cos#theta* slice "+(TString)_s(i)+";m_{#mu#mu} TeV;Events", nlinlimitimassbins,linlimitimassmin,linlimitimassmax) );
			vp_mHat_dEtaSlices.push_back( (TVirtualPad*)cnv_mHat_dEtaSlices->cd(i) );
		}
		

		if(sProc=="Gmm")
		{
			TFile f("/data/hod/2011/NTUPLE/mcLocalControl_"+tsName+".root", "READ");
			TTree* t = (TTree*)f.Get("allCuts/allCuts_tree");
			t->SetBranchAddress("phi",    &phi);
			t->SetBranchAddress("eta",    &eta);
			t->SetBranchAddress("pt",     &pt);
			t->SetBranchAddress("E",      &E);
			t->SetBranchAddress("charge", &charge);
			
			eta    = 0;
			phi    = 0;
			pt     = 0;
			E      = 0;
			charge = 0;
		
			Int_t NG = t->GetEntries();
			cout << "NG = " << NG << endl;
		
			for(Int_t i=0 ; i<NG ; i++)
			{
				t->GetEntry(i);
				
				pa->SetPtEtaPhiM(pt->at(0)*MeV2TeV, eta->at(0), phi->at(0), muonMass*GeV2TeV);
				pb->SetPtEtaPhiM(pt->at(1)*MeV2TeV, eta->at(1), phi->at(1), muonMass*GeV2TeV);
				float ca = charge->at(0);
				float cb = charge->at(1);
				float mHat     = imass(pa,pb);
				float cosTheHE = cosThetaBoost(pa,ca,pb,cb);
				float cosTheCS = cosThetaCollinsSoper(pa,ca,pb,cb);
				int   slice =  h_cosTheta->FindBin(cosTheCS);
				float dEta = fabs(eta->at(0)-eta->at(1));
				
				h_cosTheta->Fill(cosTheCS);
				h_dEta->Fill(dEta);
				h_mHat->Fill(mHat);
				h_mHatCosTheta->Fill(mHat,cosTheCS);
				vh_mHat_cosThetaSlices[slice-1]->Fill(mHat);
				vh_mHat_dEtaSlices[slice-1]->Fill(mHat);
				
				cout << tsMass << " GeV G* event: " << i+1 << "\r" << flush;
			}
			cout << endl;
			f.Close();	
		}
		
		TString name   = "";
		TString titles = "";
	
		name   = tsName+"_mHat_stitchedCosTheta_"+tsIndex;
		titles = tsTitle+"mass in cos#theta* stitched slices;Extended m_{#mu#mu} TeV;Events";
		template_cosThetaSlices->Add( (TH1D*)stitch(vh_mHat_cosThetaSlices,name,titles)->Clone("") );
		template_cosThetaSlices->SetOwner(kTRUE);
		template_cosThetaSlices->At(mspt)->Print();
		
		name   = tsName+"_mHat_stitcheddEta_"+tsIndex;
		titles = tsTitle+"mass in #Delta#eta stitched slices;Extended m_{#mu#mu} TeV;Events";
		template_dEtaSlices->Add( (TH1D*)stitch(vh_mHat_dEtaSlices,name,titles)->Clone("") );
		template_dEtaSlices->SetOwner(kTRUE);
		template_dEtaSlices->At(mspt)->Print();

		cnv_stitched->Draw();
		cnv_stitched->cd(1);
		template_cosThetaSlices->At(mspt)->Draw();
		cnv_stitched->cd(2);
		template_dEtaSlices->At(mspt)->Draw();
		cnv_stitched->RedrawAxis();
		cnv_stitched->SaveAs("plots/"+tsName+"_stitched.png");

		
		cnv_cosTheta->SetTickx();
		cnv_cosTheta->SetTicky();
		cnv_cosTheta->Draw();
		cnv_cosTheta->cd();
		h_cosTheta->Draw();
		cnv_cosTheta->RedrawAxis();
		cnv_cosTheta->SaveAs("plots/"+tsName+"_cosTheta.png");
		
		cnv_dEta->SetTickx();
		cnv_dEta->SetTicky();
		cnv_dEta->Draw();
		cnv_dEta->cd();
		h_dEta->Draw();
		cnv_dEta->RedrawAxis();
		cnv_dEta->SaveAs("plots/"+tsName+"_cosTheta.png");
		
		cnv_mHat->SetLogy();
		cnv_mHat->SetLogx();
		cnv_mHat->SetTickx();
		cnv_mHat->SetTicky();
		cnv_mHat->Draw();
		cnv_mHat->cd();
		h_mHat->Draw();
		cnv_mHat->RedrawAxis();
		cnv_mHat->SaveAs("plots/"+tsName+"_mass.png");
		
		cnv_mHatCosTheta->SetLogx();
		cnv_mHatCosTheta->SetLogz();
		cnv_mHatCosTheta->SetTickx();
		cnv_mHatCosTheta->SetTicky();
		cnv_mHatCosTheta->Draw();
		cnv_mHatCosTheta->cd();
		h_mHatCosTheta->Draw("COLZ");
		cnv_mHatCosTheta->RedrawAxis();
		cnv_mHatCosTheta->SaveAs("plots/"+tsName+"_massCosTheta.png");
		
		for(int i=1 ; i<=nCosThetaBinsLimit ; i++)
		{
			vp_mHat_cosThetaSlices[i-1]->cd();
			vp_mHat_cosThetaSlices[i-1]->SetLogy();
			vp_mHat_cosThetaSlices[i-1]->SetLogx();
			vp_mHat_cosThetaSlices[i-1]->SetTickx();
			vp_mHat_cosThetaSlices[i-1]->SetTicky();
			vp_mHat_cosThetaSlices[i-1]->Draw();
			vp_mHat_cosThetaSlices[i-1]->cd();
			vh_mHat_cosThetaSlices[i-1]->Draw();
			vp_mHat_cosThetaSlices[i-1]->RedrawAxis();
		}
		cnv_mHat_cosThetaSlices->SaveAs("plots/"+tsName+"_massCosThetaSlices.png");
		
		for(int i=1 ; i<=ndEtaBinsLimit ; i++)
		{
			vp_mHat_dEtaSlices[i-1]->cd();
			vp_mHat_dEtaSlices[i-1]->SetLogy();
			vp_mHat_dEtaSlices[i-1]->SetLogx();
			vp_mHat_dEtaSlices[i-1]->SetTickx();
			vp_mHat_dEtaSlices[i-1]->SetTicky();
			vp_mHat_dEtaSlices[i-1]->Draw();
			vp_mHat_dEtaSlices[i-1]->cd();
			vh_mHat_dEtaSlices[i-1]->Draw();
			vp_mHat_dEtaSlices[i-1]->RedrawAxis();
		}
		cnv_mHat_dEtaSlices->SaveAs("plots/"+tsName+"_massdEtaSlices.png");
	}
	
	
	dir_cosThetaSlices->cd();
	template_cosThetaSlices->Write();
	dir_dEtaSlices->cd();
	template_dEtaSlices->Write();
	
	fTemplates->Write();
	fTemplates->Close();
	
	_INFO("DONE");
}
