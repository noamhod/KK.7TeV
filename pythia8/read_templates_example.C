{
	#include<vector>

	TFile f("weights.root");
	Float_t m,mt,w,x;
	TTree* t;
	Int_t N;
	
	TCanvas* c = new TCanvas("c","c", 600,400);
	c->cd();
	c->SetLogy();
	c->SetLogx();
	c->Draw();
	
	TH1D* hXS = (TH1D*)f.Get("histograms/mass_wgt_XS")->Clone("hXS"); // for the binned cross section weights
	
	TH1D* hZ0 = (TH1D*)f.Get("histograms/hMassSumTmp")->Clone("hZ0"); // for the histogram properties (i.e., log-like binning)
	TH1D* hZP = (TH1D*)f.Get("histograms/hMassSumTmp")->Clone("hZP"); // for the histogram properties (i.e., log-like binning)
	TH1D* hKK = (TH1D*)f.Get("histograms/hMassSumTmp")->Clone("hKK"); // for the histogram properties (i.e., log-like binning)
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
		N = t->GetEntries();
		N_Z0 += N;
		for(Int_t i=0 ; i<N ; i++)
		{
			t->GetEntry(i);
			
			// option 1. unbinned cross section weights
			//hZP->Fill(m,x*w);
			//hZ0->Fill(m,x*1.);
			
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
	hZ0->Draw();
	hZP->Draw("SAMES");
	hKK->Draw("SAMES");
	cout << "N_Z0=" << N_Z0 << endl;
}
