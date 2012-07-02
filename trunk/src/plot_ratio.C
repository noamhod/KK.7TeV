{
	gStyle->SetOptStat(0);
	gStyle->SetFrameBorderMode(0);
	gStyle->SetCanvasBorderMode(0);
	gStyle->SetPadBorderMode(0);
	gStyle->SetPadColor(0);
	gStyle->SetCanvasColor(0);
	gStyle->SetStatColor(0);
	//gStyle->SetFillColor(0);
	gStyle->SetFrameFillColor(0);
	gStyle->SetTitleFillColor(0);
	gStyle->SetPaperSize(20,26);
	gStyle->SetPadTopMargin(0.13);
	gStyle->SetPadRightMargin(0.15);
	gStyle->SetPadBottomMargin(0.14);
	gStyle->SetPadLeftMargin(0.12);
	Int_t font=42;
	Double_t tsize=0.04;
	gStyle->SetTextFont(font);
	gStyle->SetTextSize(tsize);
	gStyle->SetLabelFont(font,"x");
	gStyle->SetTitleFont(font,"x");
	gStyle->SetLabelFont(font,"y");
	gStyle->SetTitleFont(font,"y");
	gStyle->SetLabelFont(font,"z");
	gStyle->SetTitleFont(font,"z");
	gStyle->SetLabelSize(tsize,"x");
	gStyle->SetTitleSize(tsize,"x");
	gStyle->SetLabelSize(tsize,"y");
	gStyle->SetTitleSize(tsize,"y");
	gStyle->SetLabelSize(tsize,"z");
	gStyle->SetTitleSize(tsize,"z");
	gStyle->SetStatBorderSize(0);
	gStyle->SetStatColor(0);
	gStyle->SetStatX(0);
	gStyle->SetStatY(0);
	gStyle->SetStatFont(42);
	gStyle->SetStatFontSize(0);
	gStyle->SetOptStat(0);
	gStyle->SetStatW(0);
	gStyle->SetStatH(0);
	gStyle->SetTitleX(0.12);
	gStyle->SetTitleY(1);
	
	gStyle->SetPalette(1);
	
	gStyle->SetTitleX(0.25); //title X location 
	gStyle->SetTitleY(0.94); //title Y location 
	gStyle->SetTitleW(0.5); //title width 
	gStyle->SetTitleH(0.05); //title height
	gStyle->SetTitleBorderSize(0);
	
	gStyle->cd();


	TCanvas* c = new TCanvas("c","c",600,550);
	c->Divide(1,2);
	c->Draw();
	TVirtualPad* tvp_hists = c->cd(1);
	TVirtualPad* tvp_ratio = c->cd(2);

	tvp_hists->SetPad(0.00, 0.35, 1.00, 1.00);
	tvp_ratio->SetPad(0.00, 0.00, 1.00, 0.355);

	tvp_hists->SetBottomMargin(0.012);
	tvp_ratio->SetBottomMargin(0.20);
	tvp_ratio->SetTopMargin(0.012);

	TH1D* h1 = new TH1D("hdata",";m_{#mu#mu} GeV;Events",100,-5.,+5.);
	TH1D* h2 = new TH1D("hmc",  ";m_{#mu#mu} GeV;Events",100,-5.,+5.);
	TH1D* hr;

	TLine* line = new TLine(-5.,1.,+5.,1.);

	h1->SetLineColor(kBlack);
	h2->SetLineColor(kRed);

	h1->FillRandom("gaus", 10000);
	h2->FillRandom("gaus", 10000);

	h1->Sumw2();
	h2->Sumw2();
	
	hr = (TH1D*)h1->Clone("");
	hr->SetName("Ratio");
	TString sXtitle = "m_{#mu#mu} GeV";
	TString sTitle = "#frac{Data}{#sum MC#times wgt};"+sXtitle+";Ratio";
	hr->SetTitle(sTitle);
	//hr->Divide(h1,h2,1.,1.,"B");
	hr->Divide(h2);

	hr->GetXaxis()->SetLabelSize(0.075);
	hr->GetYaxis()->SetLabelSize(0.075);

	hr->GetXaxis()->SetTitleSize(0.075);
	hr->GetYaxis()->SetTitleSize(0.075);

	hr->SetTitleSize(0.075);
	hr->SetTitleSize(0.075);

	hr->GetYaxis()->SetTitleOffset(0.5);
	
	hr->SetMinimum(0.);
	hr->SetMaximum(+2.);
	
	tvp_hists->cd();
	h1->Draw();
	h2->Draw("SAMES");

	c->Update();

	tvp_ratio->cd();
	//line->Draw();
	//hr->Draw("SAMES e1x1");
	hr->Draw("e1x1");
	line->Draw("SAMES");

	c->Update();
}
