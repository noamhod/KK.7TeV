{
	#include<vector>

	TFile f("weights.root");
	Float_t m,w,x;
	TTree* t;
	Int_t N;
	
	TCanvas* c = new TCanvas("c","c", 600,400);
	c->cd();
	c->SetLogy();
	c->SetLogx();
	c->Draw();
	
	TH1D* hZ0 = (TH1D*)f.Get("sumTmp")->Clone("hZ0");
	TH1D* hZP = (TH1D*)f.Get("sumTmp")->Clone("hZP");
	TH1D* hKK = (TH1D*)f.Get("sumTmp")->Clone("hKK");
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

	for(int n=1 ; n<=nMassBins ; n++)
	{
		strm.clear();
		str.clear();
		strm << n;
		strm >> str;

		t = (TTree*)f.Get( ("tree_ZP_"+str).c_str() );
		t->SetBranchAddress("mass_rec",&m);
		t->SetBranchAddress("mass_wgt",&w);
		t->SetBranchAddress("xscn_wgt",&x);
		N = t->GetEntries();
		for(Int_t i=0 ; i<N ; i++)
		{
			t->GetEntry(i);
			hZP->Fill(m,x*w);
			hZ0->Fill(m,x*1.);
		}
		
		t = (TTree*)f.Get( ("tree_KK_"+str).c_str() );
		t->SetBranchAddress("mass_rec",&m);
		t->SetBranchAddress("mass_wgt",&w);
		t->SetBranchAddress("xscn_wgt",&x);
		N = t->GetEntries();
		for(Int_t i=0 ; i<N ; i++)
		{
			t->GetEntry(i);
			hKK->Fill(m,x*w);
		}
	}
	hZ0->Draw();
	hZP->Draw("SAMES");
	hKK->Draw("SAMES");
}
