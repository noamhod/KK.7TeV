{
	TFile* fZmumu = new TFile("/srv01/tau/hod/z0analysis-tests/z0analysis-r170/data/mcLocalControl_Zmumu.root", "READ");
	TEventList* elist;

	TTree* tree_rec = (TTree*)fZmumu->Get("allCuts/allCuts_tree");
	tree_rec->SetEventList(0);
	tree_rec->Draw(">>elist","Mhat>=0.07"); // TeV
	elist = (TEventList*)gDirectory->Get("elist");
	Double_t Nrec = elist->GetN();
	tree_rec->SetEventList(elist);
	cout << "Nrec = " << Nrec << endl;
	tree_rec->Draw("Mhat");

	/*
	TH1D*       histo = new TH1D("histo","weights",100000,0.,10.);
	tree_rec->SetEventList(0);
	tree_rec->Draw("pileup_weight>>histo","Mhat>=0.07"); // TeV
	Double_t Nwgt = histo->GetSumOfWeights();
	cout << "Nwgt = " << Nwgt << endl;
	histo->Draw();
	*/

	TTree* tree_tru = (TTree*)fZmumu->Get("truth/truth_tree");
	tree_tru->SetEventList(0);
	tree_tru->Draw(">>elist","truth_all_isValid  &&  truth_all_Mhat>=70"); // GeV
	elist = (TEventList*)gDirectory->Get("elist");
	Double_t Ntru = elist->GetN();
	tree_tru->SetEventList(elist);
	cout << "Ntru = " << Ntru << endl;
	tree_tru->Draw("truth_all_Mhat");

	cout << "Acceptance X Efficiency = " << Nrec/Ntru << endl;
	
/* 	tree_tru->SetBranchStatus("*",kFALSE);
	bool truth_all_isValid;
	float truth_all_Mhat;
	bool recon_all_isValid;
	float recon_all_Mhat;
	float all_pileup_weight;
	float all_EW_kfactor_weight;
	float all_QCD_kfactor_weight;
	float all_mcevent_weight;
	tree->SetBranchAddress("truth_all_isValid", &truth_all_isValid);
	tree->SetBranchAddress("recon_all_isValid", &recon_all_isValid);
	tree->SetBranchAddress("all_pileup_weight",      &all_pileup_weight );
	tree->SetBranchAddress("all_EW_kfactor_weight",  &all_EW_kfactor_weight );
	tree->SetBranchAddress("all_QCD_kfactor_weight", &all_QCD_kfactor_weight );
	tree->SetBranchAddress("all_mcevent_weight",     &all_mcevent_weight );
	tree->SetBranchAddress("truth_all_Mhat", &truth_all_Mhat);
	tree->SetBranchAddress("recon_all_Mhat", &recon_all_Mhat);
	
	for(Int_t N=0 ; N<(Int_t)Ntru ; N++)
	{
		tree_tru->GetEntry(N);
		if(truth_all_isValid)
	}
	
	static const double nb2fb = 1.e+6;
	Double_t Lmc = 4878990/(8.3470E-01*nb2fb);
	Double_t Ldt = 4.99467; */
	
}
