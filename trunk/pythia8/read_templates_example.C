{
	#include "style.h"

	style();
	
	TFile f("weights.root");
	Float_t m,mt,w,x;
	Float_t c,ct,cw;
	TTree* t;
	Int_t N;
	
	TCanvas* c1 = new TCanvas("c1","c1", 600,400);
	c1->cd();
	c1->SetLogy();
	c1->SetLogx();
	c1->Draw();
	
	TCanvas* c2 = new TCanvas("c2","c2", 600,400);
	c2->cd();
	c2->Draw();
	
	
	TH1D* hXS = (TH1D*)f.Get("histograms/hMassXS_wgt")->Clone("hXS"); // for the binned cross section weights
	
	TH1D* hZ0 = (TH1D*)f.Get("histograms/hMassTmp")->Clone("hZ0"); // for the histogram properties (i.e., log-like binning)
	TH1D* hZP = (TH1D*)f.Get("histograms/hMassTmp")->Clone("hZP"); // for the histogram properties (i.e., log-like binning)
	TH1D* hKK = (TH1D*)f.Get("histograms/hMassTmp")->Clone("hKK"); // for the histogram properties (i.e., log-like binning)
	
	
	hZ0->Reset();
	hZP->Reset();
	hKK->Reset();
	hZ0->SetLineColor(kBlack);
	hZP->SetLineColor(kRed);
	hKK->SetLineColor(kBlue);
	hZ0->SetLineWidth(2);
	hZP->SetLineWidth(2);
	hKK->SetLineWidth(2);
	hZ0->SetTitle("templates");
	hZP->SetTitle("templates");
	hKK->SetTitle("templates");
	

	
	TH2D* h2dZ0 = new TH2D("h2dZ0","h2dZ0", 50,-1.,+1., 50,-1.,+1.);
	h2dZ0->SetLineColor(kRed);
	h2dZ0->SetLineColor(kRed);
	h2dZ0->SetXTitle("cos#theta_{tru}");
	h2dZ0->SetYTitle("cos#theta_{rec}");
	
	stringstream strm;
	string str;
	
	t = (TTree*)f.Get("AfbMassBins");
	int nMassBins = t->GetEntries();

	Int_t N_Z0 = 0;
	Int_t B;
	for(int n=1 ; n<=nMassBins ; n++)
	{
		strm.clear();
		str.clear();
		strm << n;
		strm >> str;

		t = (TTree*)f.Get( ("tree_ZP_"+str).c_str() );
		t->SetBranchAddress("mass_tru",&mt);
		t->SetBranchAddress("mass_rec",&m);
		t->SetBranchAddress("mass_wgt",&w);
		t->SetBranchAddress("xscn_wgt",&x);
		t->SetBranchAddress("cost_tru",&ct);
		t->SetBranchAddress("cost_rec",&c);
		t->SetBranchAddress("cost_wgt",&cw);
		
		N = t->GetEntries();
		N_Z0 += N;
		for(Int_t i=0 ; i<N ; i++)
		{
			t->GetEntry(i);
			
			// option 1. unbinned cross section weights
			//hZP->Fill(m,x*w);
			//hZ0->Fill(m,x*1.);
			h2dZ0->Fill(ct,c/*,x*1.*/);
			
			// option 2. binned cross section weights
			B = hXS->FindBin(mt);
			x = hXS->GetBinContent(B);
			hZP->Fill(m,x*w);
			hZ0->Fill(m,x*1.);
		}
		
		t = (TTree*)f.Get( ("tree_KK_"+str).c_str() );
		t->SetBranchAddress("mass_tru",&mt);
		t->SetBranchAddress("mass_rec",&m);
		t->SetBranchAddress("mass_wgt",&w);
		t->SetBranchAddress("xscn_wgt",&x);
		t->SetBranchAddress("cost_tru",&ct);
		t->SetBranchAddress("cost_rec",&c);
		t->SetBranchAddress("cost_wgt",&cw);
		N = t->GetEntries();
		for(Int_t i=0 ; i<N ; i++)
		{
			t->GetEntry(i);
			
			// option 1. unbinned cross section weights
			//hKK->Fill(m,x*w);
			
			// option 2. binned cross section weights
			B = hXS->FindBin(mt);
			x = hXS->GetBinContent(B);
			hKK->Fill(m,x*w);
		}
	}
	c1->cd();
	hZ0->Draw();
	hZP->Draw("SAMES");
	hKK->Draw("SAMES");
	
	c2->cd();
	h2dZ0->Draw("COLZ");
	
	cout << "N_Z0=" << N_Z0 << endl;
}
