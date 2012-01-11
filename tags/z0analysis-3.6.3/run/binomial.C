{
/*
Int_t Binomial(Int_t ntot, Double_t prob)
 Generates a random integer N according to the binomial law
 Coded from Los Alamos report LA-5061-MS

 N is binomially distributed between 0 and ntot inclusive
 with mean prob*ntot.
 prob is between 0 and 1.

 Note: This function should not be used when ntot is large (say >100).
 The normal approximation is then recommended instead
 (with mean =*ntot+0.5 and standard deviation sqrt(ntot*prob*(1-prob)).
*/
	TRandom* randGen;
	randGen = new TRandom();
	randGen->SetSeed(0); // Note that the machine clock is returned with a precision of 1 second.
	// If one calls SetSeed(0) within a loop and the loop time is less than 1s,
	// all generated numbers will be identical!

	Int_t Nmax = 1;
	Double_t n1 = 390.364;
	Double_t n2 = 470.015;
	Double_t p = n2/(n1+n2);

	TH1I* h = new TH1I("h","h",2,0,2);
	for(Int_t k=1 ; k<=10000000 ; k++)
	{
		Int_t r = randGen->Binomial(Nmax,p);
		h->Fill(r);
	}

	cout << "analytical p=" << p << ", q=" << 1.-p << endl;
	Double_t pr = h->GetBinContent(2)/(h->GetBinContent(1)+h->GetBinContent(2));
	cout << "random     p=" << pr << ", q=" << 1.-pr << endl;

	h->SetMinimum(0);
	h->Draw();
}
