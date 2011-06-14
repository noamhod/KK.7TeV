{
	TFile f("/data/hod/D3PDfin/rel16/data_A-I2_eta24/muid/analysisLocalControl.root");
	TTree* t = (TTree*)f.Get("allCuts/allCuts_tree");
	Int_t N = t->GetEntries();
	Int_t counter = 0;
	Float_t Mhat;
	Int_t RunNumber;
	Int_t lbn;
	Int_t EventNumber;
	t->SetBranchAddress("Mhat",&Mhat);
	t->SetBranchAddress("RunNumber",&RunNumber);
	t->SetBranchAddress("lbn",&lbn);
	t->SetBranchAddress("EventNumber",&EventNumber);
	for(Int_t i=0 ; i<N ; i++)
	{
		t->GetEntry(i);
		if(Mhat>0.07 && Mhat<0.4)
		{
			counter++;	
			cout << "RunNumber=" << RunNumber << " lbn=" << lbn << " EventNumber=" << EventNumber << endl;
		}
	}
	cout << "counter=" << counter << endl;
}
