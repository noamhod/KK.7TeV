{
	//gROOT->ProcessLine(".x ../src/rootlogon_atlas.C");
	//gROOT->SetStyle("ATLAS");
	//gROOT->ForceStyle();

	float GeV2TeV = 1.e-3;

	int Afb_nbins = 40;
	double Afb_min   = 60.*GeV2TeV;
	double Afb_max   = 460.*GeV2TeV;

	string dir   = "/data/hod/D3PDdigest/rel15_barrel_selection/";
	string hDir  = "allCuts";
	string hName = "Afb";
	string xTitle = "#hat{m}_{#mu#mu} TeV";
	string yTitle= "A_{FB}#left(#hat{m}_{#mu#mu}#right)";

	string m_dataAnalysisSelector = "diget";	
	string m_muonSelector = "staco/";

	double m_miny = -1.05;
	double m_maxy = +1.05;



	string hNameFixed = hName;
	

	gStyle->SetOptStat(0);
	
	TLegend* leg = new TLegend(0.7123746,0.7292746,0.8695652,0.8821244,NULL,"brNDC");
	leg->SetFillColor(kWhite);
	
	string L = "43";
	string lumilabel = "#intLdt~" + L + " pb^{-1}";
	TPaveText* pvtxt = new TPaveText(0.1195652,0.1334197,0.2458194,0.2318653,"brNDC");
	pvtxt->SetFillColor(kWhite);
	TText* txt = pvtxt->AddText( lumilabel.c_str() );
	
	string muonLabel = m_muonSelector.substr(0, m_muonSelector.length()-1);
	TPaveText* pvtxt1 = new TPaveText(0.1421405,0.126943,0.2165552,0.1683938,"brNDC");
	pvtxt1->SetFillColor(kWhite);
	TText* txt1 = pvtxt1->AddText( muonLabel.c_str() );
	
	string cName = "cnv_" + hNameFixed;
	TCanvas* cnv = new TCanvas(cName.c_str(), cName.c_str(), 0,0,1200,800);
	
	
	
	
	TPad *pad_mHat = new TPad("pad_mHat","",0,0,1,1);
	pad_mHat->SetFillColor(kWhite);
	pad_mHat->SetTicky(0);
        pad_mHat->SetLogy();

	TPad *pad_Afb  = new TPad("pad_Afb", "",0,0,1,1);
        pad_Afb->SetTicky(0);
        pad_Afb->SetTickx(1);
	pad_Afb->SetFillStyle(0);
	pad_Afb->SetFrameFillStyle(4000); //will be transparent
	pad_Afb->SetFrameFillColor(0);
	
	
	string s1, s2;
	
	string path = "";
	string sProc = "";
	string channel = "";
	string analysisType = (m_dataAnalysisSelector=="digest") ? "mcDigestControl_" : "mcOfflineControl_";
	
	Float_t mHat;
	Float_t cosTh;
	
	
	// Data
	TH1D* hDataM  = new TH1D("mHat_data","mHat_data", Afb_nbins, Afb_min, Afb_max );
	hDataM->SetTitle("");
	hDataM->SetYTitle("#frac{dN}{d#hat{m}_{#mu#mu}} 1/TeV");
	hDataM->SetLineColor(kBlack);
	hDataM->SetLineWidth(2);
	TH1D* hData   = new TH1D("Afb_data","Afb_data",   Afb_nbins, Afb_min, Afb_max );
	hData->SetMarkerStyle(20);
	hData->SetMarkerColor(kBlack);
	hData->SetMarkerSize(1.2);
	TH1D* hDataNf = new TH1D("dataNf","dataNf",       Afb_nbins, Afb_min, Afb_max );
	TH1D* hDataNb = new TH1D("dataNb","dataNb",       Afb_nbins, Afb_min, Afb_max );
	leg->AddEntry( hData, "Data: A_{FB}#left(#hat{m}_{#mu#mu}#right)", "lep");
	leg->AddEntry( hData, "Data: #frac{dN}{d#hat{m}_{#mu#mu}}", "l");
	
	string sData = (m_dataAnalysisSelector=="digest") ? "digestControl" : "offlineControl";
	
	path = dir + "AtoI2_ZprimeGRL/" + m_muonSelector + sData + ".root";
	TFile* fData = new TFile( path.c_str(), "READ" );
	TTree* Afb_data_tree = (TTree*)fData->Get("Afb/Afb_tree");
	Afb_data_tree->SetBranchAddress( "mHat",  &mHat );
	Afb_data_tree->SetBranchAddress( "cosTh", &cosTh );
	
	
	if (Afb_data_tree==0) return;
	for (Long64_t l64t_jentry=0 ; l64t_jentry<Afb_data_tree->GetEntries() ; l64t_jentry++)
	{
		Afb_data_tree->GetEntry(l64t_jentry);
		
		if(cosTh>=0) hDataNf->Fill(mHat);
		else         hDataNb->Fill(mHat);
		
		hDataM->Fill(mHat);
	}
	for(Int_t b=1 ; b<=hData->GetNbinsX() ; b++)
	{
		Double_t Nf = hDataNf->GetBinContent(b);
		Double_t Nb = hDataNb->GetBinContent(b);
		Double_t N = Nf+Nb;
		
		//if(Nf<1  ||  Nb<1)
		if(N<1)
		{
			//hData->SetBinContent(b,0);
			//hData->SetBinError(b,0);
			continue;
		}
		
		//float afb = (N>0.) ? (Nf-Nb)/N : -999.;
		float afb = (Nf-Nb)/N;
		
		// the Forward-Backward Asymmetry error: 
		// if N=Nf+Nb, p=Nf/N, q=1-p=Nb/N, then A=p-q=2*p-1.
		// The statistical error on p is sqrt(p*q/N) (binomial distribution),
		// and from this, the statistical error on A is sqrt((1-A*A)/N)
		//float dafb = (N>0.) ? sqrt( (1.-afb*afb)/N ) : 0.;
		float dafb = sqrt( (1.-afb*afb)/N );
		
		hData->SetBinContent(b,afb);
		hData->SetBinError(b,dafb);
	}
	
	
	
	// Backgrounds
	channel = "DYmumu: A_{FB}#left(#hat{m}_{#mum#mu}#right)";
	TH1D* hBGsum = new TH1D("Afb_sumBG","Afb_sumBG", Afb_nbins, Afb_min, Afb_max );
	TH1D* hNf    = new TH1D("bgNf","bgNf",           Afb_nbins, Afb_min, Afb_max );
	TH1D* hNb    = new TH1D("bgNb","bgNb",           Afb_nbins, Afb_min, Afb_max );
	hBGsum->SetLineColor(kAzure-5);
	hBGsum->SetFillColor(kAzure-5);
	hBGsum->SetLineWidth(1);
	hBGsum->SetMarkerSize(0);
	hBGsum->SetMarkerColor(0);
	//hBGsum->SetMarkerStyle(kAzure-5);
	//hBGsum->SetMarkerColor(kAzure-5);
	hBGsum->SetTitle("");
	hBGsum->SetXTitle( xTitle.c_str() );
	hBGsum->SetYTitle( yTitle.c_str() );
	leg->AddEntry( hBGsum, channel.c_str(), "f");
	
	
	TList* Afb_sumBG_list = new TList();
	
	sProc = "DYmumu_75M120";
	path = dir + "DYmumu/" + m_muonSelector + analysisType + sProc + ".root";
	TFile* fDYmumu_75M120 = new TFile( path.c_str(), "READ" );
	Afb_sumBG_list->Add( (TTree*)fDYmumu_75M120->Get("Afb/Afb_tree") );
	
	sProc = "DYmumu_120M250";
	path = dir + "DYmumu/" + m_muonSelector + analysisType + sProc + ".root";
	TFile* fDYmumu_120M250 = new TFile( path.c_str(), "READ" );
	Afb_sumBG_list->Add( (TTree*)fDYmumu_120M250->Get("Afb/Afb_tree") );
	
	sProc = "DYmumu_250M400";
	path = dir + "DYmumu/" + m_muonSelector + analysisType + sProc + ".root";
	TFile* fDYmumu_250M400 = new TFile( path.c_str(), "READ" );
	Afb_sumBG_list->Add( (TTree*)fDYmumu_250M400->Get("Afb/Afb_tree") );

	sProc = "DYmumu_400M600";
        path = dir + "DYmumu/" + m_muonSelector + analysisType + sProc + ".root";
        TFile* fDYmumu_400M600 = new TFile( path.c_str(), "READ" );
        Afb_sumBG_list->Add( (TTree*)fDYmumu_400M600->Get("Afb/Afb_tree") );
	

/*	
	sProc = "ZZ_Herwig";
	path = dir + "ZZ_Herwig/" + m_muonSelector + analysisType + sProc + ".root";
	TFile* fZZ = new TFile( path.c_str(), "READ" );
	Afb_sumBG_list->Add( (TTree*)fZZ->Get("Afb/Afb_tree") );
	
	sProc = "WZ_Herwig";
	path = dir + "WZ_Herwig/" + m_muonSelector + analysisType + sProc + ".root";
	TFile* fWZ = new TFile( path.c_str(), "READ" );
	Afb_sumBG_list->Add( (TTree*)fWZ->Get("Afb/Afb_tree") );
	
	sProc = "WW_Herwig";
	path = dir + "WW_Herwig/" + m_muonSelector + analysisType + sProc + ".root";
	TFile* fWW = new TFile( path.c_str(), "READ" );
	Afb_sumBG_list->Add( (TTree*)fWW->Get("Afb/Afb_tree") );
	
	sProc = "T1_McAtNlo_Jimmy";
	path = dir + "T1_McAtNlo_Jimmy/" + m_muonSelector + analysisType + sProc + ".root";
	TFile* fT1 = new TFile( path.c_str(), "READ" );
	Afb_sumBG_list->Add( (TTree*)fT1->Get("Afb/Afb_tree") );
	
	
	sProc = "DYtautau_75M120";
	path = dir + "DYtautau/" + m_muonSelector + analysisType + sProc + ".root";
	TFile* fDYtautau_75M120 = new TFile( path.c_str(), "READ" );
	Afb_sumBG_list->Add( (TTree*)fDYtautau_75M120->Get("Afb/Afb_tree") );
	
	sProc = "DYtautau_120M250";
	path = dir + "DYtautau/" + m_muonSelector + analysisType + sProc + ".root";
	TFile* fDYtautau_120M250 = new TFile( path.c_str(), "READ" );
	Afb_sumBG_list->Add( (TTree*)fDYtautau_120M250->Get("Afb/Afb_tree") );
	
	sProc = "DYtautau_250M400";
	path = dir + "DYtautau/" + m_muonSelector + analysisType + sProc + ".root";
	TFile* fDYtautau_250M400 = new TFile( path.c_str(), "READ" );
	Afb_sumBG_list->Add( (TTree*)fDYtautau_250M400->Get("Afb/Afb_tree") );

*/	
	
	TFile* mergedFile = new TFile("Afb_sumBG_merged.root", "RECREATE");
	cout << "Merging trees...patience..." << endl;
	TTree::MergeTrees(Afb_sumBG_list);
	mergedFile->Write();
	mergedFile->Close();
	
	TFile* fBG = new TFile("Afb_sumBG_merged.root", "READ");
	TTree* Afb_sumBG_tree = (TTree*)fBG->Get("Afb_tree");
	Afb_sumBG_tree->SetBranchAddress( "mHat",  &mHat );
	Afb_sumBG_tree->SetBranchAddress( "cosTh", &cosTh );

	if (Afb_sumBG_tree==0) return;
	for (Long64_t l64t_jentry=0 ; l64t_jentry<Afb_sumBG_tree->GetEntriesFast() ; l64t_jentry++)
	{
		Afb_sumBG_tree->GetEntry(l64t_jentry);
		
		if(cosTh>=0) hNf->Fill(mHat);
		else         hNb->Fill(mHat);
	}
	for(Int_t b=1 ; b<=hBGsum->GetNbinsX() ; b++)
	{
		Double_t Nf = hNf->GetBinContent(b);
		Double_t Nb = hNb->GetBinContent(b);
		Double_t N = Nf+Nb;
		
		//if(Nf<1  ||  Nb<1)
		if(N<1)
		{
			//hBGsum->SetBinContent(b,0);
			//hBGsum->SetBinError(b,0);
			continue;
		}
		
		//float afb = (N>0.) ? (Nf-Nb)/N : -999.;
		float afb = (Nf-Nb)/N;
		
		// the Forward-Backward Asymmetry error: 
		// if N=Nf+Nb, p=Nf/N, q=1-p=Nb/N, then A=p-q=2*p-1.
		// The statistical error on p is sqrt(p*q/N) (binomial distribution),
		// and from this, the statistical error on A is sqrt((1-A*A)/N)
		//float dafb = (N>0.) ? sqrt( (1.-afb*afb)/N ) : 0.;
		float dafb = sqrt( (1.-afb*afb)/N );
		
		hBGsum->SetBinContent(b,afb);
		hBGsum->SetBinError(b,dafb);
	}

	pad_mHat->Draw();
	pad_mHat->cd();
	hDataM->GetYaxis()->SetRangeUser(5.e-1,1.1*hDataM->GetMaximum());
	hDataM->Draw();

	cnv->cd();

	pad_Afb->Draw();
	pad_Afb->cd();
	hBGsum->GetYaxis()->SetRangeUser(m_miny,m_maxy);
	hBGsum->Draw("E6 Y+");
	TH1D* hBGsumTmp = (TH1D*)hBGsum->Clone("");
	hBGsumTmp->Reset();
	for(Int_t b=0 ; b<hBGsumTmp->GetNbinsX() ; b++) hBGsumTmp->SetBinContent(b,hBGsum->GetBinContent(b));
	hBGsumTmp->SetLineColor(kAzure+8);
	hBGsumTmp->Draw("CSAMES");
	hData->Draw("e1x0SAMES");
	pvtxt->Draw("SAMES");
	pvtxt1->Draw("SAMES");
	leg->Draw("SAMES");
	TLine* lUnit = new TLine(Afb_min,0.,Afb_max,0.);
	lUnit->SetLineColor(kBlack);
	lUnit->SetLineStyle(2);
	lUnit->Draw("SAMES");
	//pad_Afb->RedrawAxis();
	
	cnv->cd();
	
	pad_mHat->cd();
	pad_mHat->RedrawAxis();
	pad_mHat->Update();

	cnv->Update();

/*	
	TString fName = "figures/" + (TString)hNameFixed + "_" + (TString)muonLabel;
	cnv->SaveAs(fName+".eps");
	cnv->SaveAs(fName+".C");
	cnv->SaveAs(fName+".root");
	cnv->SaveAs(fName+".png");
*/
}
