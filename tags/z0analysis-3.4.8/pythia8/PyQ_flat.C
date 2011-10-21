{
	TH1D* h = new TH1D("hTest_flat","hTest_flat",50,-2.5,+2.5);
	
	for(Int_t b=1 ; b<=h->GetNbinsX() ; b++)
	{
		h->SetBinContent(b,0.);
	}

	h->SetMaximum(1.);
	h->SetMinimum(0.);
	h->Draw();
	h->SaveAs("hTest_flat.root");
}
