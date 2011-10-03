{
	TH1D* h = new TH1D("hTest","hTest",16,-2.5,+2.5);
	
	//h->FillRandom("gaus", 1000000);
	TRandom *evtgen = new TRandom();
	evtgen->SetSeed(0);

	Double_t grnd     = 0.;
	Double_t mean     = 0.;
	Double_t sigma    = 3.;
	Double_t maxeta   = 2.5;
	Double_t norm     = 0.5;
	Double_t fraction = 0.95;

	Int_t N=1000000;
	Int_t evt=1;
	while(evt<=N)
	{
		grnd = evtgen->Gaus(mean,sigma);
		if(fabs(grnd)>maxeta) continue;
		h->Fill(grnd);
		evt++;
	}

	Double_t minH = h->GetMinimum();
	for(Int_t b=1 ; b<=h->GetNbinsX() ; b++)
	{
		h->SetBinContent(b,h->GetBinContent(b)-fraction*minH );
	}

	Double_t maxH = h->GetMaximum();
	Double_t maxP = norm;
	h->Scale(maxP/maxH);
	h->SetMaximum(1.);
	h->SetMinimum(0.);
	h->Draw();
	h->SaveAs("hTest.root");
}
