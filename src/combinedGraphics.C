/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "combinedGraphics.h"

combinedGraphics::combinedGraphics()
{

}

combinedGraphics::~combinedGraphics()
{

}

void combinedGraphics::initialize(string analysisSelector, string muonSelector)
{
	m_muonSelector = muonSelector + "/";

	m_mcAnalysisSelector   = (analysisSelector=="digest") ? "mcDigest" : "mcOffline";
	m_dataAnalysisSelector = (analysisSelector=="digest") ? "digest"   : "offline";

	hFile->cd();
	
	// canvas size
	canv_x = 602;
	canv_y = 400;

	// legend size
	leg_x1 = 0.765;
	leg_x2 = 0.919;
	leg_y1 = 0.376;
	leg_y2 = 0.922;
	
	
	// see: http://www-cdf.fnal.gov/~bernd/rootcolors.png
	vcolors = new vector<Color_t>;
	vcolors->push_back(61);
	vcolors->push_back(46);
	vcolors->push_back(8);
	vcolors->push_back(98);
	vcolors->push_back(28);
	vcolors->push_back(51);
	vcolors->push_back(94);
	vcolors->push_back(226);
	vcolors->push_back(150);
	vcolors->push_back(49);
	vcolors->push_back(14);
	vcolors->push_back(109);
	vcolors->push_back(199);
	vcolors->push_back(207);
	
	/////////////////////////////////////////////////
	// integrated luminosity of the data in 1/pb ////
	/*
		Period	 Trigger	 	Lumi[/nb]
		A		 L1_MU10		0.158011
		B		 L1_MU10		8.88014
		C		 L1_MU10		8.72868
		D		 L1_MU10		297.341
		E		 EF_mu10		1081.95
		F		 EF_mu10		1958.16
		G		 EF_mu13		8570.07
		H		 EF_mu13_tight	8522.04
		I		 EF_mu13_tight	22953.0
				 total			43400.33
	*/
	period2trigMap.insert( make_pair( "L1_MU10",0.157183/1000 ) );
	period2trigMap.insert( make_pair( "L1_MU10",8.83395/1000  ) );
	period2trigMap.insert( make_pair( "L1_MU10",8.71722/1000  ) );
	period2trigMap.insert( make_pair( "L1_MU10",255.204/1000  ) );
	period2trigMap.insert( make_pair( "EF_mu10",1081.62/1000  ) );
	period2trigMap.insert( make_pair( "EF_mu10",1958.16/1000  ) );
	period2trigMap.insert( make_pair( "EF_mu13",8540.39/1000  ) );
	period2trigMap.insert( make_pair( "EF_mu13_tight",8520.76/1000  ) );
	period2trigMap.insert( make_pair( "EF_mu13_tight",22952.4/1000  ) );
	
	period2lumiMap.insert( make_pair( "A",0.157183/1000 ) );
	period2lumiMap.insert( make_pair( "B",8.83395/1000  ) );
	period2lumiMap.insert( make_pair( "C",8.71722/1000  ) );
	period2lumiMap.insert( make_pair( "D",255.204/1000  ) );
	period2lumiMap.insert( make_pair( "E",1081.62/1000  ) );
	period2lumiMap.insert( make_pair( "F",1958.16/1000  ) );
	period2lumiMap.insert( make_pair( "G",8540.39/1000  ) );
	period2lumiMap.insert( make_pair( "H",8520.76/1000  ) );
	period2lumiMap.insert( make_pair( "I",22952.4/1000  ) );
	dataLumi_ipb = 0.;
	for(TMapsd::iterator it=period2lumiMap.begin() ; it!=period2lumiMap.end() ; ++it)
	{
		dataLumi_ipb += it->second;
	}
	
	//--- mc processes cross section values in pb
	mcProc2sigma.insert(   make_pair("DYmumu_75M120",819.93));
	mcProc2br.insert(      make_pair("DYmumu_75M120",1.));
	mcProc2nevents.insert( make_pair("DYmumu_75M120",19994));
	mcProc2geneff.insert(  make_pair("DYmumu_75M120",1.));
	mcProc2kfactor.insert( make_pair("DYmumu_75M120",1.));
	mcProc2sigma.insert(   make_pair("DYmumu_120M250",8.7158));
	mcProc2br.insert(      make_pair("DYmumu_120M250",1.));
	mcProc2nevents.insert( make_pair("DYmumu_120M250",19996));
	mcProc2geneff.insert(  make_pair("DYmumu_120M250",1.));
	mcProc2kfactor.insert( make_pair("DYmumu_120M250",1.));
	mcProc2sigma.insert(   make_pair("DYmumu_250M400",0.41571));
	mcProc2br.insert(      make_pair("DYmumu_250M400",1.));
	mcProc2nevents.insert( make_pair("DYmumu_250M400",19997));
	mcProc2geneff.insert(  make_pair("DYmumu_250M400",1.));
	mcProc2kfactor.insert( make_pair("DYmumu_250M400",1.));
	mcProc2sigma.insert(   make_pair("DYmumu_400M600",0.06724));
	mcProc2br.insert(      make_pair("DYmumu_400M600",1.));
	mcProc2nevents.insert( make_pair("DYmumu_400M600",19996));
	mcProc2geneff.insert(  make_pair("DYmumu_400M600",1.));
	mcProc2kfactor.insert( make_pair("DYmumu_400M600",1.));
	mcProc2sigma.insert(   make_pair("DYmumu_600M800",0.01116));
	mcProc2br.insert(      make_pair("DYmumu_600M800",1.));
	mcProc2nevents.insert( make_pair("DYmumu_600M800",19993));
	mcProc2geneff.insert(  make_pair("DYmumu_600M800",1.));
	mcProc2kfactor.insert( make_pair("DYmumu_600M800",1.));
	mcProc2sigma.insert(   make_pair("DYmumu_800M1000",0.0027437));
	mcProc2br.insert(      make_pair("DYmumu_800M1000",1.));
	mcProc2nevents.insert( make_pair("DYmumu_800M1000",19946));
	mcProc2geneff.insert(  make_pair("DYmumu_800M1000",1.));
	mcProc2kfactor.insert( make_pair("DYmumu_800M1000",1.));
	mcProc2sigma.insert(   make_pair("DYmumu_1000M1250",0.00091775));
	mcProc2br.insert(      make_pair("DYmumu_1000M1250",1.));
	mcProc2nevents.insert( make_pair("DYmumu_1000M1250",19992));
	mcProc2geneff.insert(  make_pair("DYmumu_1000M1250",1.));
	mcProc2kfactor.insert( make_pair("DYmumu_1000M1250",1.));
	mcProc2sigma.insert(   make_pair("DYmumu_1250M1500",0.00024866));
	mcProc2br.insert(      make_pair("DYmumu_1250M1500",1.));
	mcProc2nevents.insert( make_pair("DYmumu_1250M1500",19995));
	mcProc2geneff.insert(  make_pair("DYmumu_1250M1500",1.));
	mcProc2kfactor.insert( make_pair("DYmumu_1250M1500",1.));
	mcProc2sigma.insert(   make_pair("DYmumu_1500M1750",0.00007659));
	mcProc2br.insert(      make_pair("DYmumu_1500M1750",1.));
	mcProc2nevents.insert( make_pair("DYmumu_1500M1750",19987));
	mcProc2geneff.insert(  make_pair("DYmumu_1500M1750",1.));
	mcProc2kfactor.insert( make_pair("DYmumu_1500M1750",1.));
	mcProc2sigma.insert(   make_pair("DYmumu_1750M2000",0.000026361));
	mcProc2br.insert(      make_pair("DYmumu_1750M2000",1.));
	mcProc2nevents.insert( make_pair("DYmumu_1750M2000",19991));
	mcProc2geneff.insert(  make_pair("DYmumu_1750M2000",1.));
	mcProc2kfactor.insert( make_pair("DYmumu_1750M2000",1.));
	mcProc2sigma.insert(   make_pair("DYmumu_M2000",0.000015325));
	mcProc2br.insert(      make_pair("DYmumu_M2000",1.));
	mcProc2nevents.insert( make_pair("DYmumu_M2000",19990));
	mcProc2geneff.insert(  make_pair("DYmumu_M2000",1.));
	mcProc2kfactor.insert( make_pair("DYmumu_M2000",1.));
	
	mcProc2sigma.insert(   make_pair("DYtautau_75M120",817.8));
	mcProc2br.insert(      make_pair("DYtautau_75M120",1.));
	mcProc2nevents.insert( make_pair("DYtautau_75M120",19998));
	mcProc2geneff.insert(  make_pair("DYtautau_75M120",1.));
	mcProc2kfactor.insert( make_pair("DYtautau_75M120",1.));
	mcProc2sigma.insert(   make_pair("DYtautau_120M250",8.6608));
	mcProc2br.insert(      make_pair("DYtautau_120M250",1.));
	mcProc2nevents.insert( make_pair("DYtautau_120M250",19996));
	mcProc2geneff.insert(  make_pair("DYtautau_120M250",1.));
	mcProc2kfactor.insert( make_pair("DYtautau_120M250",1.));
	mcProc2sigma.insert(   make_pair("DYtautau_250M400",0.41613));
	mcProc2br.insert(      make_pair("DYtautau_250M400",1.));
	mcProc2nevents.insert( make_pair("DYtautau_250M400",19994));
	mcProc2geneff.insert(  make_pair("DYtautau_250M400",1.));
	mcProc2kfactor.insert( make_pair("DYtautau_250M400",1.));
	mcProc2sigma.insert(   make_pair("DYtautau_400M600",0.067269));
	mcProc2br.insert(      make_pair("DYtautau_400M600",1.));
	mcProc2nevents.insert( make_pair("DYtautau_400M600",19992));
	mcProc2geneff.insert(  make_pair("DYtautau_400M600",1.));
	mcProc2kfactor.insert( make_pair("DYtautau_400M600",1.));
	mcProc2sigma.insert(   make_pair("DYtautau_600M800",0.01116));
	mcProc2br.insert(      make_pair("DYtautau_600M800",1.));
	mcProc2nevents.insert( make_pair("DYtautau_600M800",19986));
	mcProc2geneff.insert(  make_pair("DYtautau_600M800",1.));
	mcProc2kfactor.insert( make_pair("DYtautau_600M800",1.));
	mcProc2sigma.insert(   make_pair("DYtautau_800M1000",0.0027437));
	mcProc2br.insert(      make_pair("DYtautau_800M1000",1.));
	mcProc2nevents.insert( make_pair("DYtautau_800M1000",19984));
	mcProc2geneff.insert(  make_pair("DYtautau_800M1000",1.));
	mcProc2kfactor.insert( make_pair("DYtautau_800M1000",1.));
	mcProc2sigma.insert(   make_pair("DYtautau_1000M1250",0.00091775));
	mcProc2br.insert(      make_pair("DYtautau_1000M1250",1.));
	mcProc2nevents.insert( make_pair("DYtautau_1000M1250",19980));
	mcProc2geneff.insert(  make_pair("DYtautau_1000M1250",1.));
	mcProc2kfactor.insert( make_pair("DYtautau_1000M1250",1.));
	mcProc2sigma.insert(   make_pair("DYtautau_1250M1500",0.00024897));
	mcProc2br.insert(      make_pair("DYtautau_1250M1500",1.));
	mcProc2nevents.insert( make_pair("DYtautau_1250M1500",19973));
	mcProc2geneff.insert(  make_pair("DYtautau_1250M1500",1.));
	mcProc2kfactor.insert( make_pair("DYtautau_1250M1500",1.));
	mcProc2sigma.insert(   make_pair("DYtautau_1500M1750",0.000076551));
	mcProc2br.insert(      make_pair("DYtautau_1500M1750",1.));
	mcProc2nevents.insert( make_pair("DYtautau_1500M1750",19974));
	mcProc2geneff.insert(  make_pair("DYtautau_1500M1750",1.));
	mcProc2kfactor.insert( make_pair("DYtautau_1500M1750",1.));
	mcProc2sigma.insert(   make_pair("DYtautau_1750M2000",0.000026356));
	mcProc2br.insert(      make_pair("DYtautau_1750M2000",1.));
	mcProc2nevents.insert( make_pair("DYtautau_1750M2000",19968));
	mcProc2geneff.insert(  make_pair("DYtautau_1750M2000",1.));
	mcProc2kfactor.insert( make_pair("DYtautau_1750M2000",1.));
	mcProc2sigma.insert(   make_pair("DYtautau_M2000",0.000015323));
	mcProc2br.insert(      make_pair("DYtautau_M2000",1.));
	mcProc2nevents.insert( make_pair("DYtautau_M2000",18966));
	mcProc2geneff.insert(  make_pair("DYtautau_M2000",1.));
	mcProc2kfactor.insert( make_pair("DYtautau_M2000",1.));
	
	mcProc2sigma.insert(   make_pair("Zprime_mumu_SSM1000",0.12881));
	mcProc2br.insert(      make_pair("Zprime_mumu_SSM1000",1.));
	mcProc2nevents.insert( make_pair("Zprime_mumu_SSM1000",19996));
	mcProc2geneff.insert(  make_pair("Zprime_mumu_SSM1000",1.));
	mcProc2kfactor.insert( make_pair("Zprime_mumu_SSM1000",1.));
	mcProc2sigma.insert(   make_pair("Zprime_mumu_SSM1250",0.041544));
	mcProc2br.insert(      make_pair("Zprime_mumu_SSM1250",1.));
	mcProc2nevents.insert( make_pair("Zprime_mumu_SSM1250",19995));
	mcProc2geneff.insert(  make_pair("Zprime_mumu_SSM1250",1.));
	mcProc2kfactor.insert( make_pair("Zprime_mumu_SSM1250",1.));
	mcProc2sigma.insert(   make_pair("Zprime_mumu_SSM1500",0.015215));
	mcProc2br.insert(      make_pair("Zprime_mumu_SSM1500",1.));
	mcProc2nevents.insert( make_pair("Zprime_mumu_SSM1500",19995));
	mcProc2geneff.insert(  make_pair("Zprime_mumu_SSM1500",1.));
	mcProc2kfactor.insert( make_pair("Zprime_mumu_SSM1500",1.));
	mcProc2sigma.insert(   make_pair("Zprime_mumu_SSM1750",0.0060546));
	mcProc2br.insert(      make_pair("Zprime_mumu_SSM1750",1.));
	mcProc2nevents.insert( make_pair("Zprime_mumu_SSM1750",19995));
	mcProc2geneff.insert(  make_pair("Zprime_mumu_SSM1750",1.));
	mcProc2kfactor.insert( make_pair("Zprime_mumu_SSM1750",1.));
	mcProc2sigma.insert(   make_pair("Zprime_mumu_SSM2000",0.0025803));
	mcProc2br.insert(      make_pair("Zprime_mumu_SSM2000",1.));
	mcProc2nevents.insert( make_pair("Zprime_mumu_SSM2000",19998));
	mcProc2geneff.insert(  make_pair("Zprime_mumu_SSM2000",1.));
	mcProc2kfactor.insert( make_pair("Zprime_mumu_SSM2000",1.));

	mcProc2sigma.insert(   make_pair("T1_McAtNlo_Jimmy",80.201));
	mcProc2br.insert(      make_pair("T1_McAtNlo_Jimmy",1.));
	mcProc2nevents.insert( make_pair("T1_McAtNlo_Jimmy",984390));
	mcProc2kfactor.insert( make_pair("T1_McAtNlo_Jimmy",1.09));
	mcProc2geneff.insert(  make_pair("T1_McAtNlo_Jimmy",1.));
	
	mcProc2sigma.insert(   make_pair("WW_Herwig",29.592));
	mcProc2br.insert(      make_pair("WW_Herwig",1.));
	mcProc2nevents.insert( make_pair("WW_Herwig",249837));
	mcProc2kfactor.insert( make_pair("WW_Herwig",1.));
	mcProc2geneff.insert(  make_pair("WW_Herwig",0.38863));
	mcProc2sigma.insert(   make_pair("WZ_Herwig",11.23));
	mcProc2br.insert(      make_pair("WZ_Herwig",1.));
	mcProc2nevents.insert( make_pair("WZ_Herwig",244833));
	mcProc2kfactor.insert( make_pair("WZ_Herwig",1.));
	mcProc2geneff.insert(  make_pair("WZ_Herwig",0.30847));
	mcProc2sigma.insert(   make_pair("ZZ_Herwig",4.5964));
	mcProc2br.insert(      make_pair("ZZ_Herwig",1.));
	mcProc2nevents.insert( make_pair("ZZ_Herwig",249725));
	mcProc2kfactor.insert( make_pair("ZZ_Herwig",1.));
	mcProc2geneff.insert(  make_pair("ZZ_Herwig",0.21152));
	
}

TCanvas* combinedGraphics::getCanvas(TFile* f, string dir, string cname)
{
	string path = dir + "/" +cname;
	TCanvas* cnv_cutFlow_imass = (TCanvas*)f->Get( path.c_str() );
	return cnv_cutFlow_imass;
}

TH1D* combinedGraphics::getHisto(TFile* f, string dir, string hname)
{
	hFile->cd();
	string path = dir + "/" +hname;
	TH1D* h = (TH1D*)f->Get( path.c_str() );
	return h;
}

TH1D* combinedGraphics::cloneHisto(TFile* f, string dir, string hname)
{
	hFile->cd();
	string path = dir + "/" +hname;
	TH1D* hTmp = (TH1D*)f->Get( path.c_str() );
	TH1D* h = (TH1D*)hTmp->Clone("");
	return h;
}

void combinedGraphics::fixHisto(TH1D* h)
{
	hFile->cd();
	h->SetTitle("");
	h->SetXTitle("#hat{m}_{#mu#mu} (TeV)");
	h->SetYTitle("Events");
}

void combinedGraphics::NormToBinWidth(TH1D* h)
{
	/// normalise to bin width
	for ( int i=1 ; i<=h->GetNbinsX() ; i++ )
	{ 
		double delta = h->GetBinLowEdge(i+1) - h->GetBinLowEdge(i);
		h->SetBinContent(i,h->GetBinContent(i)/delta);
		//h->SetBinError(i,h->GetBinError(i)/delta);
	}
}

double combinedGraphics::Integral(TH1D* h)
{ 
	/// get integral
	double N=0;
	for ( int i=1 ; i<=h->GetNbinsX() ; i++ ) N += h->GetBinContent(i);
	return N;
}

double combinedGraphics::IntegralOverFlow(TH1D* h)
{ 
	/// get integral including over/underflow
	double N=0;
	for ( int i=0 ; i<=h->GetNbinsX()+1 ; i++ ) N += h->GetBinContent(i);
	return N;
}

void combinedGraphics::Scale(TH1D* h, double d)
{ 
	/// scale including over/underflow
	for ( int i=0 ; i<=h->GetNbinsX()+1 ; i++ )
	{ 
		//h->SetBinError(i,h->GetBinError(i)*d);
		h->SetBinContent(i,h->GetBinContent(i)*d);
	}
}

void combinedGraphics::Norm(TH1D* h)
{ 
	double N = Integral(h);
	if ( N>0 ) Scale(h,1/N);
	N = Integral(h);
}

void combinedGraphics::NormToDataLumi(TH1D* h,
									  double crossSection_pb,
									  double branchingRatio,
									  double nMCevents,
									  double kFactor,
									  double genEff,
									  double dataLumi_pb)
{ 
	double mcLumi = nMCevents/(crossSection_pb*branchingRatio);
	if ( mcLumi>0 ) Scale(h, dataLumi_pb/mcLumi);
}

void combinedGraphics::setNormVals(double crossSection_pb,
								   double branchingRatio,
								   double nMCevents,
								   double kFactor,
								   double genEff,
								   double dataLumi_pb)
{
	m_crossSection_pb = crossSection_pb;
	m_branchingRatio  = branchingRatio;
	m_nMCevents       = nMCevents;
	m_kFactor         = kFactor;
	m_genEff          = genEff;
	m_dataLumi_pb     = dataLumi_pb;
}

void combinedGraphics::relDiff(TH1D* hInp, TH1D* hRef, TH1D* hRelDiffPos, TH1D* hRelDiffNeg)
{
	Int_t nBins = hInp->GetNbinsX();
	Double_t reldiff = 0.;
	Double_t nRef = 0.;
	Double_t nInp = 0.;

	for (Int_t n=1 ; n<=nBins ; n++) {
		nRef = hRef->GetBinContent(n);
		nInp = hInp->GetBinContent(n);
		if ((nRef+nInp)!=0) { // for not dividing by zero...
			reldiff = (nRef-nInp) / sqrt(nRef + nInp);
			if      (reldiff < 0) { hRelDiffNeg->SetBinContent(n,reldiff); }
			else if (reldiff > 0) { hRelDiffPos->SetBinContent(n,reldiff); }
			else if (reldiff == 0) { 
				hRelDiffPos->SetBinContent(n,0);
				hRelDiffNeg->SetBinContent(n,0);
			}
		}
		else {
			hRelDiffPos->SetBinContent(n,0);
			hRelDiffNeg->SetBinContent(n,0);
		}
	}
}

void combinedGraphics::relDiff(TH1D* hInp, TH1D* hRef, TH1D* hRelDiff)
{
	Int_t nBins = hInp->GetNbinsX();
	Double_t reldiff = 0.;
	Double_t nRef = 0.;
	Double_t nInp = 0.;
	Double_t eRef = 0.;
	Double_t eInp = 0.;

	for (Int_t n=1 ; n<=nBins ; n++) {
		nRef = hRef->GetBinContent(n);
		nInp = hInp->GetBinContent(n);
		eRef = hRef->GetBinError(n);
		eInp = hInp->GetBinError(n);
		if (eRef!=0.  &&  eInp!=0.)// for not dividing by zero...
		{
			reldiff = (nRef-nInp) / sqrt(eRef*eRef + eInp*eInp);
			hRelDiff->SetBinContent(n,reldiff);
		}
		else
		{
			hRelDiff->SetBinContent(n,-999.);
		}
	}
}

void combinedGraphics::ratio(double xmin, double xmax, TH1D* hInp, TH1D* hRef, TH1D* hRat, TH1D* hRatUp, TH1D* hRatDwn)
{
	Int_t nBins = hInp->GetNbinsX();
	Double_t rat = 0.;
	Double_t err = 0.;
	Double_t nRef = 0.;
	Double_t nInp = 0.;
	Double_t ratup = 0.;
	Double_t ratdwn = 0.;
	Double_t x = 0.;
	
	vector<Double_t> vrat;
	
	hRat->Reset();
	hRatUp->Reset();
	hRatDwn->Reset();
	
	TAxis *xaxis = hInp->GetXaxis();

	for (Int_t n=1 ; n<=nBins ; n++)
	{
		nRef = hRef->GetBinContent(n);
		nInp = hInp->GetBinContent(n);
		x    = xaxis->GetBinCenter(n);
		
		if (nInp>0  &&  nRef>0  &&  x>=xmin  &&  x<=xmax)
		{ // for not dividing by zero...
		
			rat = nInp/nRef;
			err = sqrt(nInp)/nRef;

			ratdwn = 0.;
			ratup  = 0.;
			vrat.clear();

			if(nRef>1.) vrat.push_back( ( nInp+sqrt(nInp) ) / ( nRef-sqrt(nRef) ) );
			else        vrat.push_back( 0. );

			vrat.push_back( ( nInp+sqrt(nInp) ) / ( nRef+sqrt(nRef) ) );
			vrat.push_back( ( nInp-sqrt(nInp) ) / ( nRef+sqrt(nRef) ) );

			if(nRef>1.) vrat.push_back( ( nInp-sqrt(nInp) ) / ( nRef-sqrt(nRef) ) );
			else        vrat.push_back( 0. );

			for(int r=0 ; r<(int)vrat.size() ; r++)
			{
				if     (vrat[r]>0.  &&  vrat[r]<=rat) ratdwn += (rat-vrat[r])*(rat-vrat[r]);
				else if(vrat[r]>0.  &&  vrat[r]>rat)  ratup  += (rat-vrat[r])*(rat-vrat[r]);
				//cout << "ratdwn=" << ratdwn << "\tratup=" << ratup << endl;
			}

			if(rat>0.)
			{
				hRat->SetBinContent(n,rat);
				hRat->SetBinError(n,err);
				hRatUp->SetBinContent(n,rat+sqrt(ratup));
				hRatDwn->SetBinContent(n,rat-sqrt(ratdwn));
			}
			else
			{
				/*
				hRat->SetBinContent(n,1);
				hRatUp->SetBinContent(n,1);
				hRatDwn->SetBinContent(n,1);
				*/
			}
		}
		else
		{
			/*
			hRat->SetBinContent(n,1);
			hRatDwn->SetBinContent(n,1.);
			hRatUp->SetBinContent(n,1.);
			*/
		}
	}
}

void combinedGraphics::drawRelDiff(double xmin, double xmax, TH1D* hRelDiff)
{
	hFile->cd();

	double hmin = -1;
	double hmax = +1;

	TH1D* hRelDiffFrame = (TH1D*)hRelDiff->Clone("");
	hRelDiffFrame->Reset();
	hRelDiffFrame->SetMaximum(hmax);
	hRelDiffFrame->SetMinimum(hmin);
	hRelDiffFrame->SetTitle("");
	hRelDiffFrame->Draw();
	
	Int_t nfullbins = 0;
	for(Int_t i=1 ; i<=hRelDiff->GetNbinsX() ; i++) { if(hRelDiff->GetBinContent(i)>0) nfullbins++; }
	Double_t *xArray       = (Double_t *)malloc(nfullbins*sizeof(Double_t));
	Double_t *RelDiffArray = (Double_t *)malloc(nfullbins*sizeof(Double_t));
	TAxis *xaxis = hRelDiff->GetXaxis();
	int index = 0;
	for(Int_t i=1 ; i<=hRelDiff->GetNbinsX() ; i++)
	{
		if(hRelDiff->GetBinContent(i)>0)
		{
			xArray[index]       = xaxis->GetBinCenter(i);
			RelDiffArray[index] = hRelDiff->GetBinContent(i);
			index++;
		}
	}
	TGraph *gRelDiff = new TGraph(nfullbins, xArray, RelDiffArray);
	gRelDiff->SetLineStyle(1);
	gRelDiff->SetLineWidth(2);
	gRelDiff->SetLineColor(kRed);
	gRelDiff->SetTitle("");
	gRelDiff->Draw("PSAMES");
	
	//hRelDiff->SetTitle("");
	//hRelDiff->Draw("elx0SAMES");
	
	TLegend* leg_RelDiff = new TLegend(0.8008749,0.6868085,0.8951647,0.8289424,NULL,"brNDC");
	leg_RelDiff->SetFillColor(kWhite);
	leg_RelDiff->AddEntry( gRelDiff, "R=#frac{Data}{MC}", "lep");
	leg_RelDiff->Draw("SAMES");
	
	TLine* lUnit = new TLine(hRelDiffFrame->GetXaxis()->GetXmin(),0,hRelDiffFrame->GetXaxis()->GetXmax(),0);
	lUnit->SetLineColor(kBlack);
	lUnit->Draw("SAMES");
}

void combinedGraphics::drawRatio(double xmin, double xmax, TH1D* hRat)
{
	hFile->cd();

	double hmin = 5.e-2;
	double hmax = 1.5e+1;

	TH1D* hRatFrame = (TH1D*)hRat->Clone("");
	hRatFrame->Reset();
	hRatFrame->SetMaximum(1*hmax);
	hRatFrame->SetMinimum(hmin);
	hRatFrame->SetTitle("");
	hRatFrame->Draw();
	
	Int_t nfullbins = 0;
	for(Int_t i=1 ; i<=hRat->GetNbinsX() ; i++) { if(hRat->GetBinContent(i)>0) nfullbins++; }
	Double_t *imassArray = (Double_t *)malloc(nfullbins*sizeof(Double_t));
	Double_t *ratioArray = (Double_t *)malloc(nfullbins*sizeof(Double_t));
	TAxis *xaxis = hRat->GetXaxis();
	int index = 0;
	for(Int_t i=1 ; i<=hRat->GetNbinsX() ; i++)
	{
		if(hRat->GetBinContent(i)>0)
		{
			imassArray[index] = xaxis->GetBinCenter(i);
			ratioArray[index] = hRat->GetBinContent(i);
			index++;
		}
	}
	TGraph *gRat = new TGraph(nfullbins, imassArray, ratioArray);
	gRat->SetLineStyle(1);
	gRat->SetLineWidth(2);
	gRat->SetLineColor(kRed);
	gRat->SetTitle("");
	gRat->Draw("CSAMES");
	
	hRat->SetTitle("");
	//hRat->SetMarkerSize(0.8);
	hRat->Draw("elx0SAMES");
	
	TLegend* leg_ratio = new TLegend(0.8008749,0.6868085,0.8951647,0.8289424,NULL,"brNDC");
	leg_ratio->SetFillColor(kWhite);
	leg_ratio->AddEntry( hRat, "R=#frac{Data}{MC}", "lep");
	leg_ratio->Draw("SAMES");
	
	TLine* lUnit = new TLine(hRatFrame->GetXaxis()->GetXmin(),1,hRatFrame->GetXaxis()->GetXmax(),1);
	lUnit->SetLineColor(kBlack);
	lUnit->Draw("SAMES");
	
	/*
	TLine* lLowBound = new TLine(xmin,hmin,xmin,hmax);
	lLowBound->SetLineColor(kBlack);
	lLowBound->SetLineWidth(3);
	if(xmin!=hRatFrame->GetXaxis()->GetXmin())
	{
		lLowBound->Draw("SAMES");
	}
	*/
}

void combinedGraphics::drawRatioWithBand(double xmin, double xmax, TH1D* hRat, TH1D* hRatUp, TH1D* hRatDwn)
{
	hFile->cd();

	double hmin = 1.e-2;
	double hmax = 1.e+2;

	hRatUp->SetLineColor(97);
	hRatUp->SetFillColor(97);
	hRatUp->SetMaximum(hmax);
	hRatUp->SetMinimum(hmin);
	hRatUp->SetTitle("");
	//hRatUp->SetXTitle("#hat{m}_{#mu#mu} (TeV)");
	//hRatUp->SetYTitle("#frac{Data}{MC}");
	hRatUp->Draw("");
	
	//hRatDwn->SetLineColor(97);
	hRatDwn->SetLineColor(10);
	hRatDwn->SetFillColor(10);
	hRatDwn->SetTitle("");
	hRatDwn->Draw("SAMES");
	
	hRat->SetLineColor(kBlue);
	hRat->SetTitle("");
	//hRat->SetMarkerStyle(kFullCircle);
	//hRat->SetMarkerSize(1);
	//hRat->SetMarkerColor(kBlue);
	hRat->Draw("CSAMES");
	
	TLegend* leg_ratio = new TLegend(0.7173913,0.5172043,0.8712375,0.8629032,NULL,"brNDC");
	leg_ratio->SetFillColor(kWhite);
	leg_ratio->AddEntry( hRat, "R=#frac{data}{MC}", "L");
	leg_ratio->AddEntry( hRatUp, "Singed quadrature", "f");
	leg_ratio->Draw("SAMES");
	
	TLine* lUnit = new TLine(0,1,hRat->GetXaxis()->GetXmax(),1);
	lUnit->SetLineColor(kBlack);
	lUnit->Draw("SAMES");
	
	/*
	TLine* lLowBound = new TLine(xmin,1.5*hmin,xmin,0.5*hmax);
	lLowBound->SetLineColor(kBlack);
	lLowBound->SetLineWidth(3);
	if(xmin!=hRat->GetXaxis()->GetXmin())
	{
		lLowBound->Draw("SAMES");
	}
	*/
}

TH1D* combinedGraphics::getNormDYmumu(string dir, string hDir, string hName)
{
	hFile->cd();

	//string dir = "/data/hod/D3PDdigest/rel15_barrel_selection/DYmumu/" + m_muonSelector;
	string path  = "";
	string sProc = "";
	//string hDir = "allCuts";
	string analysisType = (m_dataAnalysisSelector=="digest") ? "mcDigestControl_" : "mcOfflineControl_";
	
	sProc = "DYmumu_75M120";
	path = dir + analysisType + sProc + ".root";
	TFile* fDYmumu75M120 = new TFile( path.c_str(), "READ" );
	TH1D* hDYmumu75M120 = getHisto(fDYmumu75M120, hDir, hName.c_str());
	setNormVals(mcProc2sigma[sProc], mcProc2br[sProc], mcProc2nevents[sProc], mcProc2kfactor[sProc], mcProc2geneff[sProc], dataLumi_ipb);
	NormToDataLumi(hDYmumu75M120, mcProc2sigma[sProc], mcProc2br[sProc], mcProc2nevents[sProc], mcProc2kfactor[sProc], mcProc2geneff[sProc], dataLumi_ipb);
	
	sProc = "DYmumu_120M250";
	path = dir + analysisType + sProc + ".root";
	TFile* fDYmumu120M250 = new TFile( path.c_str(), "READ" );
	TH1D* hDYmumu120M250 = getHisto(fDYmumu120M250, hDir, hName.c_str());
	setNormVals(mcProc2sigma[sProc], mcProc2br[sProc], mcProc2nevents[sProc], mcProc2kfactor[sProc], mcProc2geneff[sProc], dataLumi_ipb);
	NormToDataLumi(hDYmumu120M250, mcProc2sigma[sProc], mcProc2br[sProc], mcProc2nevents[sProc], mcProc2kfactor[sProc], mcProc2geneff[sProc], dataLumi_ipb);
	
	sProc = "DYmumu_250M400";
	path = dir + analysisType + sProc + ".root";
	TFile* fDYmumu250M400 = new TFile( path.c_str(), "READ" );
	TH1D* hDYmumu250M400 = getHisto(fDYmumu250M400, hDir, hName.c_str());
	setNormVals(mcProc2sigma[sProc], mcProc2br[sProc], mcProc2nevents[sProc], mcProc2kfactor[sProc], mcProc2geneff[sProc], dataLumi_ipb);
	NormToDataLumi(hDYmumu250M400, mcProc2sigma[sProc], mcProc2br[sProc], mcProc2nevents[sProc], mcProc2kfactor[sProc], mcProc2geneff[sProc], dataLumi_ipb);
	
	sProc = "DYmumu_400M600";
	path = dir + analysisType + sProc + ".root";
	TFile* fDYmumu400M600 = new TFile( path.c_str(), "READ" );
	TH1D* hDYmumu400M600 = getHisto(fDYmumu400M600, hDir, hName.c_str());
	setNormVals(mcProc2sigma[sProc], mcProc2br[sProc], mcProc2nevents[sProc], mcProc2kfactor[sProc], mcProc2geneff[sProc], dataLumi_ipb);
	NormToDataLumi(hDYmumu400M600, mcProc2sigma[sProc], mcProc2br[sProc], mcProc2nevents[sProc], mcProc2kfactor[sProc], mcProc2geneff[sProc], dataLumi_ipb);
	
	sProc = "DYmumu_600M800";
	path = dir + analysisType + sProc + ".root";
	TFile* fDYmumu600M800 = new TFile( path.c_str(), "READ" );
	TH1D* hDYmumu600M800 = getHisto(fDYmumu600M800, hDir, hName.c_str());
	setNormVals(mcProc2sigma[sProc], mcProc2br[sProc], mcProc2nevents[sProc], mcProc2kfactor[sProc], mcProc2geneff[sProc], dataLumi_ipb);
	NormToDataLumi(hDYmumu600M800, mcProc2sigma[sProc], mcProc2br[sProc], mcProc2nevents[sProc], mcProc2kfactor[sProc], mcProc2geneff[sProc], dataLumi_ipb);
	
	sProc = "DYmumu_800M1000";
	path = dir + analysisType + sProc + ".root";
	TFile* fDYmumu800M1000 = new TFile( path.c_str(), "READ" );
	TH1D* hDYmumu800M1000 = getHisto(fDYmumu800M1000, hDir, hName.c_str());
	setNormVals(mcProc2sigma[sProc], mcProc2br[sProc], mcProc2nevents[sProc], mcProc2kfactor[sProc], mcProc2geneff[sProc], dataLumi_ipb);
	NormToDataLumi(hDYmumu800M1000, mcProc2sigma[sProc], mcProc2br[sProc], mcProc2nevents[sProc], mcProc2kfactor[sProc], mcProc2geneff[sProc], dataLumi_ipb);
	
	sProc = "DYmumu_1000M1250";
	path = dir + analysisType + sProc + ".root";
	TFile* fDYmumu1000M1250 = new TFile( path.c_str(), "READ" );
	TH1D* hDYmumu1000M1250 = getHisto(fDYmumu1000M1250, hDir, hName.c_str());
	setNormVals(mcProc2sigma[sProc], mcProc2br[sProc], mcProc2nevents[sProc], mcProc2kfactor[sProc], mcProc2geneff[sProc], dataLumi_ipb);
	NormToDataLumi(hDYmumu1000M1250, mcProc2sigma[sProc], mcProc2br[sProc], mcProc2nevents[sProc], mcProc2kfactor[sProc], mcProc2geneff[sProc], dataLumi_ipb);
	
	sProc = "DYmumu_1250M1500";
	path = dir + analysisType + sProc + ".root";
	TFile* fDYmumu1250M1500 = new TFile( path.c_str(), "READ" );
	TH1D* hDYmumu1250M1500 = getHisto(fDYmumu1250M1500, hDir, hName.c_str());
	setNormVals(mcProc2sigma[sProc], mcProc2br[sProc], mcProc2nevents[sProc], mcProc2kfactor[sProc], mcProc2geneff[sProc], dataLumi_ipb);
	NormToDataLumi(hDYmumu1250M1500, mcProc2sigma[sProc], mcProc2br[sProc], mcProc2nevents[sProc], mcProc2kfactor[sProc], mcProc2geneff[sProc], dataLumi_ipb);
	
	sProc = "DYmumu_1500M1750";
	path = dir + analysisType + sProc + ".root";
	TFile* fDYmumu1500M1750 = new TFile( path.c_str(), "READ" );
	TH1D* hDYmumu1500M1750 = getHisto(fDYmumu1500M1750, hDir, hName.c_str());
	setNormVals(mcProc2sigma[sProc], mcProc2br[sProc], mcProc2nevents[sProc], mcProc2kfactor[sProc], mcProc2geneff[sProc], dataLumi_ipb);
	NormToDataLumi(hDYmumu1500M1750, mcProc2sigma[sProc], mcProc2br[sProc], mcProc2nevents[sProc], mcProc2kfactor[sProc], mcProc2geneff[sProc], dataLumi_ipb);
	
	sProc = "DYmumu_1750M2000";
	path = dir + analysisType + sProc + ".root";
	TFile* fDYmumu1750M2000 = new TFile( path.c_str(), "READ" );
	TH1D* hDYmumu1750M2000 = getHisto(fDYmumu1750M2000, hDir, hName.c_str());
	setNormVals(mcProc2sigma[sProc], mcProc2br[sProc], mcProc2nevents[sProc], mcProc2kfactor[sProc], mcProc2geneff[sProc], dataLumi_ipb);
	NormToDataLumi(hDYmumu1750M2000, mcProc2sigma[sProc], mcProc2br[sProc], mcProc2nevents[sProc], mcProc2kfactor[sProc], mcProc2geneff[sProc], dataLumi_ipb);
	
	sProc = "DYmumu_M2000";
	path = dir + analysisType + sProc + ".root";
	TFile* fDYmumuM2000 = new TFile( path.c_str(), "READ" );
	TH1D* hDYmumuM2000 = getHisto(fDYmumuM2000, hDir, hName.c_str());
	setNormVals(mcProc2sigma[sProc], mcProc2br[sProc], mcProc2nevents[sProc], mcProc2kfactor[sProc], mcProc2geneff[sProc], dataLumi_ipb);
	NormToDataLumi(hDYmumuM2000, mcProc2sigma[sProc], mcProc2br[sProc], mcProc2nevents[sProc], mcProc2kfactor[sProc], mcProc2geneff[sProc], dataLumi_ipb);
	
	hDYmumu75M120->Add(hDYmumu120M250);
	hDYmumu75M120->Add(hDYmumu250M400);
	hDYmumu75M120->Add(hDYmumu400M600);
	hDYmumu75M120->Add(hDYmumu600M800);
	hDYmumu75M120->Add(hDYmumu800M1000);
	hDYmumu75M120->Add(hDYmumu1000M1250);
	hDYmumu75M120->Add(hDYmumu1250M1500);
	hDYmumu75M120->Add(hDYmumu1500M1750);
	hDYmumu75M120->Add(hDYmumu1750M2000);
	hDYmumu75M120->Add(hDYmumuM2000);
	
	return (TH1D*)hDYmumu75M120->Clone();
}

TH1D* combinedGraphics::getNormDYtautau(string dir, string hDir, string hName)
{
	hFile->cd();

	//string dir = "/data/hod/D3PDdigest/rel15_barrel_selection/DYtautau/" + m_muonSelector;
	string path  = "";
	string sProc = "";
	//string hDir = "allCuts";
	string analysisType = (m_dataAnalysisSelector=="digest") ? "mcDigestControl_" : "mcOfflineControl_";
	
	sProc = "DYtautau_75M120";
	path = dir + analysisType + sProc + ".root";
	TFile* fDYtautau75M120 = new TFile( path.c_str(), "READ" );
	TH1D* hDYtautau75M120 = getHisto(fDYtautau75M120, hDir, hName.c_str());
	setNormVals(mcProc2sigma[sProc], mcProc2br[sProc], mcProc2nevents[sProc], mcProc2kfactor[sProc], mcProc2geneff[sProc], dataLumi_ipb);
	NormToDataLumi(hDYtautau75M120, mcProc2sigma[sProc], mcProc2br[sProc], mcProc2nevents[sProc], mcProc2kfactor[sProc], mcProc2geneff[sProc], dataLumi_ipb);
	
	sProc = "DYtautau_120M250";
	path = dir + analysisType + sProc + ".root";
	TFile* fDYtautau120M250 = new TFile( path.c_str(), "READ" );
	TH1D* hDYtautau120M250 = getHisto(fDYtautau120M250, hDir, hName.c_str());
	setNormVals(mcProc2sigma[sProc], mcProc2br[sProc], mcProc2nevents[sProc], mcProc2kfactor[sProc], mcProc2geneff[sProc], dataLumi_ipb);
	NormToDataLumi(hDYtautau120M250, mcProc2sigma[sProc], mcProc2br[sProc], mcProc2nevents[sProc], mcProc2kfactor[sProc], mcProc2geneff[sProc], dataLumi_ipb);
	
	sProc = "DYtautau_250M400";
	path = dir + analysisType + sProc + ".root";
	TFile* fDYtautau250M400 = new TFile( path.c_str(), "READ" );
	TH1D* hDYtautau250M400 = getHisto(fDYtautau250M400, hDir, hName.c_str());
	setNormVals(mcProc2sigma[sProc], mcProc2br[sProc], mcProc2nevents[sProc], mcProc2kfactor[sProc], mcProc2geneff[sProc], dataLumi_ipb);
	NormToDataLumi(hDYtautau250M400, mcProc2sigma[sProc], mcProc2br[sProc], mcProc2nevents[sProc], mcProc2kfactor[sProc], mcProc2geneff[sProc], dataLumi_ipb);
	
	sProc = "DYtautau_400M600";
	path = dir + analysisType + sProc + ".root";
	TFile* fDYtautau400M600 = new TFile( path.c_str(), "READ" );
	TH1D* hDYtautau400M600 = getHisto(fDYtautau400M600, hDir, hName.c_str());
	setNormVals(mcProc2sigma[sProc], mcProc2br[sProc], mcProc2nevents[sProc], mcProc2kfactor[sProc], mcProc2geneff[sProc], dataLumi_ipb);
	NormToDataLumi(hDYtautau400M600, mcProc2sigma[sProc], mcProc2br[sProc], mcProc2nevents[sProc], mcProc2kfactor[sProc], mcProc2geneff[sProc], dataLumi_ipb);
	
	sProc = "DYtautau_600M800";
	path = dir + analysisType + sProc + ".root";
	TFile* fDYtautau600M800 = new TFile( path.c_str(), "READ" );
	TH1D* hDYtautau600M800 = getHisto(fDYtautau600M800, hDir, hName.c_str());
	setNormVals(mcProc2sigma[sProc], mcProc2br[sProc], mcProc2nevents[sProc], mcProc2kfactor[sProc], mcProc2geneff[sProc], dataLumi_ipb);
	NormToDataLumi(hDYtautau600M800, mcProc2sigma[sProc], mcProc2br[sProc], mcProc2nevents[sProc], mcProc2kfactor[sProc], mcProc2geneff[sProc], dataLumi_ipb);
	
	sProc = "DYtautau_800M1000";
	path = dir + analysisType + sProc + ".root";
	TFile* fDYtautau800M1000 = new TFile( path.c_str(), "READ" );
	TH1D* hDYtautau800M1000 = getHisto(fDYtautau800M1000, hDir, hName.c_str());
	setNormVals(mcProc2sigma[sProc], mcProc2br[sProc], mcProc2nevents[sProc], mcProc2kfactor[sProc], mcProc2geneff[sProc], dataLumi_ipb);
	NormToDataLumi(hDYtautau800M1000, mcProc2sigma[sProc], mcProc2br[sProc], mcProc2nevents[sProc], mcProc2kfactor[sProc], mcProc2geneff[sProc], dataLumi_ipb);
	
	sProc = "DYtautau_1000M1250";
	path = dir + analysisType + sProc + ".root";
	TFile* fDYtautau1000M1250 = new TFile( path.c_str(), "READ" );
	TH1D* hDYtautau1000M1250 = getHisto(fDYtautau1000M1250, hDir, hName.c_str());
	setNormVals(mcProc2sigma[sProc], mcProc2br[sProc], mcProc2nevents[sProc], mcProc2kfactor[sProc], mcProc2geneff[sProc], dataLumi_ipb);
	NormToDataLumi(hDYtautau1000M1250, mcProc2sigma[sProc], mcProc2br[sProc], mcProc2nevents[sProc], mcProc2kfactor[sProc], mcProc2geneff[sProc], dataLumi_ipb);
	
	sProc = "DYtautau_1250M1500";
	path = dir + analysisType + sProc + ".root";
	TFile* fDYtautau1250M1500 = new TFile( path.c_str(), "READ" );
	TH1D* hDYtautau1250M1500 = getHisto(fDYtautau1250M1500, hDir, hName.c_str());
	setNormVals(mcProc2sigma[sProc], mcProc2br[sProc], mcProc2nevents[sProc], mcProc2kfactor[sProc], mcProc2geneff[sProc], dataLumi_ipb);
	NormToDataLumi(hDYtautau1250M1500, mcProc2sigma[sProc], mcProc2br[sProc], mcProc2nevents[sProc], mcProc2kfactor[sProc], mcProc2geneff[sProc], dataLumi_ipb);
	
	sProc = "DYtautau_1500M1750";
	path = dir + analysisType + sProc + ".root";
	TFile* fDYtautau1500M1750 = new TFile( path.c_str(), "READ" );
	TH1D* hDYtautau1500M1750 = getHisto(fDYtautau1500M1750, hDir, hName.c_str());
	setNormVals(mcProc2sigma[sProc], mcProc2br[sProc], mcProc2nevents[sProc], mcProc2kfactor[sProc], mcProc2geneff[sProc], dataLumi_ipb);
	NormToDataLumi(hDYtautau1500M1750, mcProc2sigma[sProc], mcProc2br[sProc], mcProc2nevents[sProc], mcProc2kfactor[sProc], mcProc2geneff[sProc], dataLumi_ipb);
	
	sProc = "DYtautau_1750M2000";
	path = dir + analysisType + sProc + ".root";
	TFile* fDYtautau1750M2000 = new TFile( path.c_str(), "READ" );
	TH1D* hDYtautau1750M2000 = getHisto(fDYtautau1750M2000, hDir, hName.c_str());
	setNormVals(mcProc2sigma[sProc], mcProc2br[sProc], mcProc2nevents[sProc], mcProc2kfactor[sProc], mcProc2geneff[sProc], dataLumi_ipb);
	NormToDataLumi(hDYtautau1750M2000, mcProc2sigma[sProc], mcProc2br[sProc], mcProc2nevents[sProc], mcProc2kfactor[sProc], mcProc2geneff[sProc], dataLumi_ipb);
	
	sProc = "DYtautau_M2000";
	path = dir + analysisType + sProc + ".root";
	TFile* fDYtautauM2000 = new TFile( path.c_str(), "READ" );
	TH1D* hDYtautauM2000 = getHisto(fDYtautauM2000, hDir, hName.c_str());
	setNormVals(mcProc2sigma[sProc], mcProc2br[sProc], mcProc2nevents[sProc], mcProc2kfactor[sProc], mcProc2geneff[sProc], dataLumi_ipb);
	NormToDataLumi(hDYtautauM2000, mcProc2sigma[sProc], mcProc2br[sProc], mcProc2nevents[sProc], mcProc2kfactor[sProc], mcProc2geneff[sProc], dataLumi_ipb);
	
	hDYtautau75M120->Add(hDYtautau120M250);
	hDYtautau75M120->Add(hDYtautau250M400);
	hDYtautau75M120->Add(hDYtautau400M600);
	hDYtautau75M120->Add(hDYtautau600M800);
	hDYtautau75M120->Add(hDYtautau800M1000);
	hDYtautau75M120->Add(hDYtautau1000M1250);
	hDYtautau75M120->Add(hDYtautau1250M1500);
	hDYtautau75M120->Add(hDYtautau1500M1750);
	hDYtautau75M120->Add(hDYtautau1750M2000);
	hDYtautau75M120->Add(hDYtautauM2000);
	
	return (TH1D*)hDYtautau75M120->Clone();
}

TH1D* combinedGraphics::setRegularMChisto(string sProc, string channel, string path, string hDir, string hName, Color_t color)
{
	TFile* f = new TFile( path.c_str(), "READ" );
	TH1D*  h = getHisto(f, hDir, hName);
	setNormVals(mcProc2sigma[sProc], mcProc2br[sProc], mcProc2nevents[sProc], mcProc2kfactor[sProc], mcProc2geneff[sProc], dataLumi_ipb);
	NormToDataLumi(h, mcProc2sigma[sProc], mcProc2br[sProc], mcProc2nevents[sProc], mcProc2kfactor[sProc], mcProc2geneff[sProc], dataLumi_ipb);
	h->SetFillColor(color);
	h->SetLineColor(color);
	h->SetTitle("");
	return h;
}

void combinedGraphics::set_allMCvsData(bool logx, bool logy, Double_t min, Double_t max, Double_t minratiox)
{
	m_logx = logx;
	m_logy = logy;
	m_miny  = min;
	m_maxy  = max;
	m_minratiox = minratiox;
}

void combinedGraphics::draw_allMCvsData(string dir, string hDir, string hName, string xTitle, string yTitle)
{
	cout << "getting " << dir+" : " + hDir + " : " + hName << endl;

	string hNameFixed = hName;
	
	hFile->cd();

	gStyle->SetOptStat(0);
	
	TLegend* leg = new TLegend(0.8039215,0.4808014,0.9232736,0.9298832,NULL,"brNDC");
	leg->SetFillColor(kWhite);
	
	m_dataLumi_pb = dataLumi_ipb;
	
	stringstream strm;
	string L;
	string lumilabel = "";
	strm << setprecision(2);
	strm << dataLumi_ipb;
	strm >> L;
	lumilabel = "#intLdt~" + L + " pb^{-1}";
	TPaveText* pvtxt = new TPaveText(0.546462,0.6944909,0.7118499,0.8146912,"brNDC");
	pvtxt->SetFillColor(kWhite);
	TText* txt = pvtxt->AddText( lumilabel.c_str() );
	
	string muonLabel = m_muonSelector.substr(0, m_muonSelector.length()-1);
	TPaveText* pvtxt1 = new TPaveText(0.5747393,0.6552055,0.6850104,0.7388414,"brNDC");
	pvtxt1->SetFillColor(kWhite);
	TText* txt1 = pvtxt1->AddText( muonLabel.c_str() );
	
	string cName = "cnv_" + hNameFixed;
	TCanvas* cnv = new TCanvas(cName.c_str(), cName.c_str(), 0,0,1200,800);
	cnv->Divide(1,2);
	
	TVirtualPad* pad = cnv->cd(1);
	pad->SetPad(0.009197324,0.2150259,0.9899666,0.9909326);
	pad->SetFillColor(kWhite);
	if(m_logx) pad->SetLogx();
	if(m_logy) pad->SetLogy();
	
	TVirtualPad* pad_ratio = cnv->cd(2);
	pad_ratio->SetPad(0.009197324,0.01036269,0.9899666,0.253886);
	pad_ratio->SetFillColor(kWhite);
	if(m_logx) pad_ratio->SetLogx();
	pad_ratio->SetLogy();
	
	cnv->Draw();
	cnv->cd();
	cnv->Update();
	
	Color_t colorStart  = 100;//kOrange; //40;
	Color_t colorOffset = -10;//1;
	Color_t colorAccumulate = colorStart;
	
	string s1, s2;
	
	string path = "";
	string sProc = "";
	string channel = "";
	string analysisType = (m_dataAnalysisSelector=="digest") ? "mcDigestControl_" : "mcOfflineControl_";
	
	double ymin = 1.e10;
	double ymax = 0.;
	
	string sData = (m_dataAnalysisSelector=="digest") ? "digestControl" : "offlineControl";
	path = dir + "AtoI2_ZprimeGRL/" + m_muonSelector + sData + ".root";
	TFile* fdata = new TFile( path.c_str(), "READ" );
	TH1D* hData = getHisto(fdata, hDir, hName);
	if(hData==NULL)
	{
		cout << "ERROR: cannot find histogram with name = " << hName << " in the file." << endl;
		cout << "returning now." << endl;
		return;
	}
	leg->AddEntry( hData, "Data", "lep");
	
	sProc = "Zprime_mumu_SSM1000";
	path = dir + "Zprime_mumu/" + m_muonSelector + analysisType + sProc + ".root";
	channel = "1 TeV Z'";
	TFile* fZprime_mumu_SSM1000 = new TFile( path.c_str(), "READ" );
	TH1D* hZprime_mumu_SSM1000 = getHisto(fZprime_mumu_SSM1000, hDir, hName);
	setNormVals(mcProc2sigma[sProc], mcProc2br[sProc], mcProc2nevents[sProc], mcProc2kfactor[sProc], mcProc2geneff[sProc], dataLumi_ipb);
	NormToDataLumi(hZprime_mumu_SSM1000, mcProc2sigma[sProc], mcProc2br[sProc], mcProc2nevents[sProc], mcProc2kfactor[sProc], mcProc2geneff[sProc], dataLumi_ipb);
	//////////////////////////////////////////////////////
	// Z' interfere with the SM (DYmumu) /////////////////
	//hZprime_mumu_SSM1000->Add( getNormDYmumu() ); ////////
	//////////////////////////////////////////////////////
	hZprime_mumu_SSM1000->SetLineColor(kBlue);
	hZprime_mumu_SSM1000->SetLineWidth(2);
	if(m_miny!=m_maxy) hZprime_mumu_SSM1000->SetMinimum(m_miny);
	if(m_miny!=m_maxy) hZprime_mumu_SSM1000->SetMaximum(m_maxy);
	strm.clear();
	strm << setprecision(2);
	strm << hZprime_mumu_SSM1000->GetBinWidth(1);
	strm >> s1;
	strm.clear();
	strm << setprecision(2);
	strm << hZprime_mumu_SSM1000->GetBinWidth( hZprime_mumu_SSM1000->GetNbinsX() );
	strm >> s2;
	string ytitle = (s1==s2) ? yTitle : yTitle + "(" + s1 + "#rightarrow" + s2 + " TeV)^{-1}";
	hZprime_mumu_SSM1000->SetTitle("");
	hZprime_mumu_SSM1000->SetXTitle( xTitle.c_str() );
	hZprime_mumu_SSM1000->SetYTitle( ytitle.c_str() );
	if(hZprime_mumu_SSM1000->GetMinimum()<ymin) ymin=hZprime_mumu_SSM1000->GetMinimum();
	if(hZprime_mumu_SSM1000->GetMaximum()>ymax) ymax=hZprime_mumu_SSM1000->GetMaximum();
	leg->AddEntry( hZprime_mumu_SSM1000, channel.c_str(), "f");
	
	unsigned int c = 0;
	Color_t color = 0;
	
	color = (c<vcolors->size()) ? vcolors->at(c) : colorAccumulate;
	channel = "SM(sig+bkg)";
	TH1D* hMC = getNormDYmumu(dir+"DYmumu/"+m_muonSelector, hDir, hName);
	hMC->SetFillColor(color);
	hMC->SetLineColor(color);
	hMC->SetTitle("");
	leg->AddEntry( hMC, channel.c_str(), "f");
	colorAccumulate+=colorOffset;
	c++;
	
	color = (c<vcolors->size()) ? vcolors->at(c) : colorAccumulate;
	channel = "Binned DY#mu#mu";
	TH1D* hDYmumu = getNormDYmumu(dir+"DYmumu/"+m_muonSelector, hDir, hName);
	hDYmumu->SetFillColor(color);
	hDYmumu->SetLineColor(color);
	hDYmumu->SetTitle("");
	if(hDYmumu->GetMinimum()<ymin) ymin=hDYmumu->GetMinimum();
	if(hDYmumu->GetMaximum()>ymax) ymax=hDYmumu->GetMaximum();
	leg->AddEntry( hDYmumu, channel.c_str(), "f");
	colorAccumulate+=colorOffset;
	c++;
	
	color = (c<vcolors->size()) ? vcolors->at(c) : colorAccumulate;
	sProc = "ZZ_Herwig";
	path = dir + "ZZ_Herwig/" + m_muonSelector + analysisType + sProc + ".root";
	channel = "ZZ";
	TH1D* hZZ = setRegularMChisto(sProc, channel, path, hDir, hName, color);
	if(hZZ->GetMinimum()<ymin) ymin=hZZ->GetMinimum();
	if(hZZ->GetMaximum()>ymax) ymax=hZZ->GetMaximum();
	leg->AddEntry( hZZ, channel.c_str(), "f");
	colorAccumulate+=colorOffset;
	c++;
	
	color = (c<vcolors->size()) ? vcolors->at(c) : colorAccumulate;
	sProc = "WZ_Herwig";
	path = dir + "WZ_Herwig/" + m_muonSelector + analysisType + sProc + ".root";
	channel = "WZ";
	TH1D* hWZ = setRegularMChisto(sProc, channel, path, hDir, hName, color);
	if(hWZ->GetMinimum()<ymin) ymin=hWZ->GetMinimum();
	if(hWZ->GetMaximum()>ymax) ymax=hWZ->GetMaximum();
	leg->AddEntry( hWZ, channel.c_str(), "f");
	colorAccumulate+=colorOffset;
	c++;
	
	color = (c<vcolors->size()) ? vcolors->at(c) : colorAccumulate;
	sProc = "WW_Herwig";
	path = dir + "WW_Herwig/" + m_muonSelector + analysisType + sProc + ".root";
	channel = "WW";
	TH1D* hWW = setRegularMChisto(sProc, channel, path, hDir, hName, color);
	if(hWW->GetMinimum()<ymin) ymin=hWW->GetMinimum();
	if(hWW->GetMaximum()>ymax) ymax=hWW->GetMaximum();
	leg->AddEntry( hWW, channel.c_str(), "f");
	colorAccumulate+=colorOffset;
	c++;
	
	color = (c<vcolors->size()) ? vcolors->at(c) : colorAccumulate;
	sProc = "T1_McAtNlo_Jimmy";
	path = dir + "T1_McAtNlo_Jimmy/" + m_muonSelector + analysisType + sProc + ".root";
	channel = "t #bar{t}";
	TH1D* hTTbar = setRegularMChisto(sProc, channel, path, hDir, hName, color);
	if(hTTbar->GetMinimum()<ymin) ymin=hTTbar->GetMinimum();
	if(hTTbar->GetMaximum()>ymax) ymax=hTTbar->GetMaximum();
	leg->AddEntry( hTTbar, channel.c_str(), "f");
	colorAccumulate+=colorOffset;
	c++;
	
	color = (c<vcolors->size()) ? vcolors->at(c) : colorAccumulate;
	channel = "Binned DY#tau#tau";
	TH1D* hDYtautau = getNormDYtautau(dir+"DYtautau/"+m_muonSelector, hDir, hName);
	hDYtautau->SetFillColor(color);
	hDYtautau->SetLineColor(color);
	hDYtautau->SetTitle("");
	if(hDYtautau->GetMinimum()<ymin) ymin=hDYtautau->GetMinimum();
	if(hDYtautau->GetMaximum()>ymax) ymax=hDYtautau->GetMaximum();
	leg->AddEntry( hDYtautau, channel.c_str(), "f");
	colorAccumulate+=colorOffset;
	c++;

	hMC->Add(hZZ);
	hMC->Add(hWZ);
	hMC->Add(hWW);
	hMC->Add(hTTbar);
	hMC->Add(hDYtautau);
	if(hMC->GetMinimum()<ymin) ymin=hMC->GetMinimum();
	if(hMC->GetMaximum()>ymax) ymax=hMC->GetMaximum();
	
	pad->cd();
	hZprime_mumu_SSM1000->Draw();
	hMC->Draw("SAMES");
	hDYmumu->Draw("SAMES");
	hZZ->Draw("SAMES");
	hWZ->Draw("SAMES");
	hWW->Draw("SAMES");
	hTTbar->Draw("SAMES");
	hDYtautau->Draw("SAMES");
	hData->Draw("e1x0SAMES");
	pvtxt->Draw("SAMES");
	pvtxt1->Draw("SAMES");
	leg->Draw("SAMES");
	pad->RedrawAxis();
	
	TH1D* hRat = (TH1D*)hData->Clone("ratio");
	hRat->Reset();
	TH1D* hRatUp = (TH1D*)hData->Clone("ratUp");
	hRatUp->Reset();
	TH1D* hRatDwn = (TH1D*)hData->Clone("ratDwn");
	hRatDwn->Reset();
	
	double minrat = (m_minratiox==0.) ? hData->GetXaxis()->GetXmin() : m_minratiox;
	ratio(minrat/*hRat->GetXaxis()->GetXmin()*/, hRat->GetXaxis()->GetXmax(), hData, hMC, hRat, hRatUp, hRatDwn);
	pad_ratio->cd();
	drawRatio(minrat/*hRat->GetXaxis()->GetXmin()*/, hRat->GetXaxis()->GetXmax(), hRat);
	pad_ratio->RedrawAxis();
	
	cout << "hName=" << hName << ": xminratio=" << minrat << ", ymin=" << ymin << ", ymax=" << ymax << endl;
	
	//cnv->Print( hFile->GetName() );
	
	
	TString fName = "figures/" + (TString)hNameFixed + "." + (TString)muonLabel;
	cnv->SaveAs(fName+".eps");
	cnv->SaveAs(fName+".C");
	cnv->SaveAs(fName+".root");
	cnv->SaveAs(fName+".png");
}

void combinedGraphics::set_sumMCvsData(bool logx, bool logy, Double_t min, Double_t max, Double_t minratiox, bool doRatio)
{
	m_logx = logx;
	m_logy = logy;
	m_miny  = min;
	m_maxy  = max;
	m_doRatio  = doRatio;
	m_minratiox = minratiox;
	m_minRelDiffx = minratiox;
}

void combinedGraphics::draw_sumMCvsData(string dir, string hDir, string hName, string xTitle, string yTitle)
{
	cout << "getting " << dir + " : " + hDir + " : " + hName << endl;
	
	string hNameFixed = hName;
	
	hFile->cd();

	gStyle->SetOptStat(0);
	
	TLegend* leg = new TLegend(0.7393469,0.8156218,0.9335198,0.9321636,NULL,"brNDC");
	leg->SetFillColor(kWhite);
	
	m_dataLumi_pb = dataLumi_ipb;
	
	stringstream strm;
	string L;
	string lumilabel = "";
	strm << setprecision(2);
	strm << dataLumi_ipb;
	strm >> L;
	lumilabel = "#intLdt~" + L + " pb^{-1}";
	TPaveText* pvtxt = new TPaveText(0.1424448,0.784087,0.3078514,0.9033709,"brNDC");
	pvtxt->SetFillColor(kWhite);
	TText* txt = pvtxt->AddText( lumilabel.c_str() );
	
	string muonLabel = m_muonSelector.substr(0, m_muonSelector.length()-1);
	TPaveText* pvtxt1 = new TPaveText(0.1640196,0.74981,0.2607065,0.8279615,"brNDC");
	pvtxt1->SetFillColor(kWhite);
	TText* txt1 = pvtxt1->AddText( muonLabel.c_str() );
	
	string cName = "cnv_" + hNameFixed;
	TCanvas* cnv = new TCanvas(cName.c_str(), cName.c_str(), 0,0,1200,800);
	cnv->Divide(1,2);
	
	TVirtualPad* pad = cnv->cd(1);
	pad->SetPad(0.009197324,0.2150259,0.9899666,0.9909326);
	pad->SetFillColor(kWhite);
	if(m_logx) pad->SetLogx();
	if(m_logy) pad->SetLogy();
	
	TVirtualPad* pad_ratio = cnv->cd(2);
	pad_ratio->SetPad(0.009197324,0.01036269,0.9899666,0.253886);
	pad_ratio->SetFillColor(kWhite);
	if(m_logx) pad_ratio->SetLogx();
	if(m_doRatio) pad_ratio->SetLogy();
	
	cnv->Draw();
	cnv->cd();
	cnv->Update();
	
	
	string s1, s2;
	
	string path = "";
	string sProc = "";
	string channel = "";
	string analysisType = (m_dataAnalysisSelector=="digest") ? "mcDigestControl_" : "mcOfflineControl_";
	
	double ymin = 1.e10;
	double ymax = 0.;
	
	string sData = (m_dataAnalysisSelector=="digest") ? "digestControl" : "offlineControl";
	path = dir + "AtoI2_ZprimeGRL/" + m_muonSelector + sData + ".root";
	TFile* fdata = new TFile( path.c_str(), "READ" );
	TH1D* hData = getHisto(fdata, hDir, hName);
	if(hData==NULL)
	{
		cout << "ERROR: cannot find histogram with name = " << hName << " in the file." << endl;
		cout << "returning now." << endl;
		return;
	}
	leg->AddEntry( hData, "Data", "lep");
	
	channel = "SM(sig+bkg)";
	TH1D* hBGsum = getNormDYmumu(dir+"DYmumu/"+m_muonSelector, hDir, hName);
	hBGsum->SetLineColor(kRed);
	//hBGsum->SetFillColor(kRed);
	hBGsum->SetLineWidth(2);
	//hBGsum->SetMarkerStyle(21);
	//hBGsum->SetMarkerColor(kBlue);
	strm.clear();
	strm << setprecision(2);
	strm << hBGsum->GetBinWidth(1);
	strm >> s1;
	strm.clear();
	strm << setprecision(2);
	strm << hBGsum->GetBinWidth( hBGsum->GetNbinsX() );
	strm >> s2;
	string ytitle = (s1==s2) ? yTitle : yTitle + "(" + s1 + "#rightarrow" + s2 + " TeV)^{-1}";
	hBGsum->SetTitle("");
	hBGsum->SetXTitle( xTitle.c_str() );
	hBGsum->SetYTitle( ytitle.c_str() );
	leg->AddEntry( hBGsum, channel.c_str(), "l");
	
	sProc = "ZZ_Herwig";
	path = dir + "ZZ_Herwig/" + m_muonSelector + analysisType + sProc + ".root";
	channel = "ZZ";
	TH1D* hZZ = setRegularMChisto(sProc, channel, path, hDir, hName, kBlue);

	sProc = "WZ_Herwig";
	path = dir + "WZ_Herwig/" + m_muonSelector + analysisType + sProc + ".root";
	channel = "WZ";
	TH1D* hWZ = setRegularMChisto(sProc, channel, path, hDir, hName, kBlue);
	
	sProc = "WW_Herwig";
	path = dir + "WW_Herwig/" + m_muonSelector + analysisType + sProc + ".root";
	channel = "WW";
	TH1D* hWW = setRegularMChisto(sProc, channel, path, hDir, hName, kBlue);
	
	sProc = "T1_McAtNlo_Jimmy";
	path = dir + "T1_McAtNlo_Jimmy/" + m_muonSelector + analysisType + sProc + ".root";
	channel = "t #bar{t}";
	TH1D* hTTbar = setRegularMChisto(sProc, channel, path, hDir, hName, kBlue);
	
	channel = "Binned DY#tau#tau";
	TH1D* hDYtautau = getNormDYtautau(dir+"DYtautau/"+m_muonSelector, hDir, hName);
	
	hBGsum->Add(hZZ);
	hBGsum->Add(hWZ);
	hBGsum->Add(hWW);
	hBGsum->Add(hTTbar);
	hBGsum->Add(hDYtautau);
	
	pad->cd();
	hBGsum->SetMinimum(m_miny);
	hBGsum->SetMaximum(m_maxy);
	//hBGsum->Draw("E4");
	hBGsum->Draw();
	hData->Draw("e1x0SAMES");
	pvtxt->Draw("SAMES");
	pvtxt1->Draw("SAMES");
	leg->Draw("SAMES");
	pad->RedrawAxis();

	
	if(m_doRatio)
	{
		TH1D* hRat = (TH1D*)hData->Clone("ratio");
		hRat->Reset();
		TH1D* hRatUp = (TH1D*)hData->Clone("ratUp");
		hRatUp->Reset();
		TH1D* hRatDwn = (TH1D*)hData->Clone("ratDwn");
		hRatDwn->Reset();
	
		double minrat = (m_minratiox==0.) ? hData->GetXaxis()->GetXmin() : m_minratiox;
		ratio(minrat, hRat->GetXaxis()->GetXmax(), hData, hBGsum, hRat, hRatUp, hRatDwn);
		pad_ratio->cd();
		drawRatio(minrat, hRat->GetXaxis()->GetXmax(), hRat);
		pad_ratio->RedrawAxis();
	}
	else
	{
		TH1D* hRelDiff = (TH1D*)hData->Clone("RelDiffio");
		hRelDiff->Reset();
	
		double minRelDiff = (m_minRelDiffx==0.) ? hData->GetXaxis()->GetXmin() : m_minRelDiffx;
		relDiff(hData, hBGsum, hRelDiff);
		pad_ratio->cd();
		drawRelDiff(minRelDiff, hRelDiff->GetXaxis()->GetXmax(), hRelDiff);
		pad_ratio->RedrawAxis();
	}
	
	TString fName = "figures/" + (TString)hNameFixed + "." + (TString)muonLabel;
	cnv->SaveAs(fName+".eps");
	cnv->SaveAs(fName+".C");
	cnv->SaveAs(fName+".root");
	cnv->SaveAs(fName+".png");
}

void combinedGraphics::set_AfbMCvsData(bool logx, bool logy, Double_t min, Double_t max, Double_t minratiox)
{
	m_logx = logx;
	m_logy = logy;
	m_miny  = min;
	m_maxy  = max;
	m_minratiox = minratiox;
	m_minRelDiffx = minratiox;
}

void combinedGraphics::draw_AfbMCvsData(string dir, string hDir, string hName, string xTitle, string yTitle)
{
	cout << "getting " << dir + " : " + hDir + " : " + hName << endl;

	string hNameFixed = hName;
	
	hFile->cd();

	gStyle->SetOptStat(0);
	
	TLegend* leg = new TLegend(0.7123746,0.7292746,0.8695652,0.8821244,NULL,"brNDC");
	leg->SetFillColor(kWhite);
	
	m_dataLumi_pb = dataLumi_ipb;
	
	stringstream strm;
	string L;
	string lumilabel = "";
	strm << setprecision(2);
	strm << dataLumi_ipb;
	strm >> L;
	lumilabel = "#intLdt~" + L + " pb^{-1}";
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
	hDataM->SetYTitle("#frac{dN}{d#hat{m}_{#mu#mu}} #left(TeV#right)^{-1}");
	hDataM->SetLineColor(kBlack);
	hDataM->SetLineWidth(2);
	TH1D* hData   = new TH1D("Afb_data","Afb_data",   Afb_nbins, Afb_min, Afb_max );
	hData->SetMarkerStyle(20);
	hData->SetMarkerColor(kBlack);
	hData->SetMarkerSize(0.9);
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
		
		if(N<2)
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
	channel = "DYmumu: A_{FB}#left(#hat{m}_{#mu#mu}#right)";
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
	strm.clear();
	strm << setprecision(2);
	strm << hBGsum->GetBinWidth(1);
	strm >> s1;
	strm.clear();
	strm << setprecision(2);
	strm << hBGsum->GetBinWidth( hBGsum->GetNbinsX() );
	strm >> s2;
	string ytitle = (s1==s2) ? yTitle : yTitle + "(" + s1 + "#rightarrow" + s2 + " TeV)^{-1}";
	hBGsum->SetTitle("");
	hBGsum->SetXTitle( xTitle.c_str() );
	hBGsum->SetYTitle( ytitle.c_str() );
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
		
		if(N<2)
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
	
	TString fName = "figures/" + (TString)hNameFixed + "." + (TString)muonLabel;
	cnv->SaveAs(fName+".eps");
	cnv->SaveAs(fName+".C");
	cnv->SaveAs(fName+".root");
	cnv->SaveAs(fName+".png");
}

void combinedGraphics::draw_trigData(string dir, string hDir, string hName)
{
	cout << "getting " << dir + " : " + hDir + " : " + hName << endl;
	
	string hNameFixed = hName;
	
	hFile->cd();

	gStyle->SetOptStat(0);
	
	double trig_dataLumi_ipb = 0.;
	for(TMapsd::iterator it=period2trigMap.begin() ; it!=period2trigMap.end() ; ++it)
	{
		size_t pos = hName.find(it->first);
		if(pos!=string::npos) trig_dataLumi_ipb = it->second;
	}
	
	
	TLegend* leg = new TLegend(0.4572864,0.2132867,0.6243719,0.3496503,NULL,"brNDC");
	leg->SetFillColor(kWhite);
	
	stringstream strm;
	string L;
	string lumilabel = "";
	strm << setprecision(2);
	strm << trig_dataLumi_ipb;
	strm >> L;
	lumilabel = "#intLdt~" + L + " pb^{-1}";
	TPaveText* pvtxt = new TPaveText(0.2550251,0.2237762,0.4208543,0.3426573,"brNDC");
	pvtxt->SetFillColor(kWhite);
	TText* txt = pvtxt->AddText( lumilabel.c_str() );
	
	string muonLabel = m_muonSelector.substr(0, m_muonSelector.length()-1);
	TPaveText* pvtxt1 = new TPaveText(0.281407,0.201049,0.3781407,0.2674825,"brNDC");
	pvtxt1->SetFillColor(kWhite);
	TText* txt1 = pvtxt1->AddText( muonLabel.c_str() );
	
	string cName = "cnv_" + hNameFixed;
	TCanvas* cnv = new TCanvas(cName.c_str(), cName.c_str(), 0,0,1200,800);
	cnv->Draw();
	cnv->cd();
	cnv->Update();
	
	string s1, s2;
	
	string path = "";
	string sProc = "";
	string channel = "";
	string analysisType = (m_dataAnalysisSelector=="digest") ? "mcDigestControl_" : "mcOfflineControl_";
	
	string sData = (m_dataAnalysisSelector=="digest") ? "digestControl" : "offlineControl";
	path = dir + "AtoI2_ZprimeGRL/" + m_muonSelector + sData + ".root";
	TFile* fdata = new TFile( path.c_str(), "READ" );
	TH1D* hData = cloneHisto(fdata, hDir, hName);
	hData->SetTitle(hName.c_str());
	if(hData==NULL)
	{
		cout << "ERROR: cannot find histogram with name = " << hName << " in the file." << endl;
		cout << "returning now." << endl;
		return;
	}
	leg->AddEntry( hData, "Data", "lep");
	
	cnv->cd();
	hData->GetYaxis()->SetRangeUser(0.,1.05);
	hData->Draw("e1x0");
	pvtxt->Draw("SAMES");
	pvtxt1->Draw("SAMES");
	leg->Draw("SAMES");
	cnv->RedrawAxis();
	
	size_t pos = hNameFixed.find("||");
	if(pos!=string::npos) hNameFixed = hNameFixed.substr(0,pos) + ".OR." + hNameFixed.substr(pos+2);
	
	TString fName = "figures/" + (TString)hNameFixed + "." + (TString)muonLabel;
	cnv->SaveAs(fName+".eps");
	cnv->SaveAs(fName+".C");
	cnv->SaveAs(fName+".root");
	cnv->SaveAs(fName+".png");
}

void combinedGraphics::draw_trigTRUvsTnP(string dir, string hDir, string hName)
{
	cout << "getting " << dir + " : " + hDir + " : " + hName << endl;
	
	string hNameFixed = hName;
	
	hFile->cd();

	gStyle->SetOptStat(0);
	
	TLegend* leg = new TLegend(0.4572864,0.2132867,0.6243719,0.3496503,NULL,"brNDC");
	leg->SetFillColor(kWhite);
	
	m_dataLumi_pb = dataLumi_ipb;
	
	stringstream strm;
	string L;
	string lumilabel = "";
	strm << setprecision(2);
	strm << dataLumi_ipb;
	strm >> L;
	lumilabel = "#intLdt~" + L + " pb^{-1}";
	TPaveText* pvtxt = new TPaveText(0.2550251,0.2237762,0.4208543,0.3426573,"brNDC");
	pvtxt->SetFillColor(kWhite);
	TText* txt = pvtxt->AddText( lumilabel.c_str() );
	
	string muonLabel = m_muonSelector.substr(0, m_muonSelector.length()-1);
	TPaveText* pvtxt1 = new TPaveText(0.281407,0.201049,0.3781407,0.2674825,"brNDC");
	pvtxt1->SetFillColor(kWhite);
	TText* txt1 = pvtxt1->AddText( muonLabel.c_str() );
	
	string cName = "cnv_" + hNameFixed;
	TCanvas* cnv = new TCanvas(cName.c_str(), cName.c_str(), 0,0,1200,800);
	cnv->Draw();
	cnv->cd();
	cnv->Update();
	
	string s1, s2;
	
	string path = "";
	string sProc = "";
	string channel = "";
	string analysisType = (m_dataAnalysisSelector=="digest") ? "mcDigestControl_" : "mcOfflineControl_";
	
	//string sData = (m_dataAnalysisSelector=="digest") ? "digestControl" : "offlineControl";
	
	sProc = "DYmumu_75M120";
	path = dir + "DYmumu/" + m_muonSelector + analysisType + sProc + ".root";
	TFile* f = new TFile( path.c_str(), "READ" );
	TH1D* hTnP  = cloneHisto(f, hDir, hName);
	TH1D* hDirect = cloneHisto(f, hDir, "tru" + hName.substr(3,hName.length()));
	hDirect->SetTitle(hName.c_str());
	hDirect->SetLineColor(kRed);
	hDirect->SetLineWidth(2);
	hDirect->SetMarkerColor(kRed);
	hDirect->SetMarkerSize(0.05);
	if(hTnP==NULL || hDirect==NULL)
	{
		cout << "ERROR: cannot find histogram with name = " << hName << " in the file." << endl;
		cout << "returning now." << endl;
		return;
	}
	leg->AddEntry( hDirect,"MC: Direct", "l");
	leg->AddEntry( hTnP, "MC: Tag&Probe", "lep");
	
	cnv->cd();
	hDirect->GetYaxis()->SetRangeUser(0.,1.05);
	hDirect->Draw(); // if dont want errors, use "HIST" option
	hTnP->Draw("e1x0SAMES");
	pvtxt->Draw("SAMES");
	pvtxt1->Draw("SAMES");
	leg->Draw("SAMES");
	cnv->RedrawAxis();
	
	size_t pos = hNameFixed.find("||");
	if(pos!=string::npos) hNameFixed = hNameFixed.substr(0,pos-1) + "_OR_" + hNameFixed.substr(pos+2);
	
	TString fName = "figures/" + (TString)hNameFixed + "." + (TString)muonLabel;
	cnv->SaveAs(fName+".eps");
	cnv->SaveAs(fName+".C");
	cnv->SaveAs(fName+".root");
	cnv->SaveAs(fName+".png");
}

void combinedGraphics::draw_trigMCvsData(string dir, string hDir, string hName)
{
	cout << "getting " << dir + " : " + hDir + " : " + hName << endl;
	
	string hNameFixed = hName;
	
	hFile->cd();

	gStyle->SetOptStat(0);
	
	TLegend* leg = new TLegend(0.4572864,0.2132867,0.6243719,0.3496503,NULL,"brNDC");
	leg->SetFillColor(kWhite);
	
	m_dataLumi_pb = dataLumi_ipb;
	
	stringstream strm;
	string L;
	string lumilabel = "";
	strm << setprecision(2);
	strm << dataLumi_ipb;
	strm >> L;
	lumilabel = "#intLdt~" + L + " pb^{-1}";
	TPaveText* pvtxt = new TPaveText(0.2550251,0.2237762,0.4208543,0.3426573,"brNDC");
	pvtxt->SetFillColor(kWhite);
	TText* txt = pvtxt->AddText( lumilabel.c_str() );
	
	string muonLabel = m_muonSelector.substr(0, m_muonSelector.length()-1);
	TPaveText* pvtxt1 = new TPaveText(0.281407,0.201049,0.3781407,0.2674825,"brNDC");
	pvtxt1->SetFillColor(kWhite);
	TText* txt1 = pvtxt1->AddText( muonLabel.c_str() );
	
	string cName = "cnv_" + hNameFixed;
	TCanvas* cnv = new TCanvas(cName.c_str(), cName.c_str(), 0,0,1200,800);
	cnv->Divide(1,2);
	
	TVirtualPad* pad = cnv->cd(1);
	pad->SetPad(0.009197324,0.2150259,0.9899666,0.9909326);
	pad->SetFillColor(kWhite);
	if(m_logx) pad->SetLogx();
	if(m_logy) pad->SetLogy();
	
	TVirtualPad* pad_ratio = cnv->cd(2);
	pad_ratio->SetPad(0.009197324,0.01036269,0.9899666,0.253886);
	pad_ratio->SetFillColor(kWhite);
	if(m_logx) pad_ratio->SetLogx();
	if(m_doRatio) pad_ratio->SetLogy();
	
	cnv->Draw();
	cnv->cd();
	cnv->Update();
	
	
	string s1, s2;
	
	string path = "";
	string sProc = "";
	string channel = "";
	string analysisType = (m_dataAnalysisSelector=="digest") ? "mcDigestControl_" : "mcOfflineControl_";
	
	double ymin = 1.e10;
	double ymax = 0.;
	
	string sData = (m_dataAnalysisSelector=="digest") ? "digestControl" : "offlineControl";
	path = dir + "AtoI2_ZprimeGRL/" + m_muonSelector + sData + ".root";
	TFile* fdata = new TFile( path.c_str(), "READ" );
	TH1D* hData = getHisto(fdata, hDir, hName);
	hData->SetTitle(hName.c_str());
	if(hData==NULL)
	{
		cout << "ERROR: cannot find histogram with name = " << hName << " in the file." << endl;
		cout << "returning now." << endl;
		return;
	}
	leg->AddEntry( hData, "Data", "lep");
	
	channel = "SM(sig+bkg)";
	TH1D* hBGsum = getNormDYmumu(dir+"DYmumu/"+m_muonSelector, hDir, hName);
	hBGsum->SetLineColor(kRed);
	//hBGsum->SetFillColor(kRed);
	hBGsum->SetLineWidth(2);
	//hBGsum->SetMarkerStyle(21);
	//hBGsum->SetMarkerColor(kBlue);
	hBGsum->SetTitle("");
	leg->AddEntry( hBGsum, channel.c_str(), "l");
	
	sProc = "ZZ_Herwig";
	path = dir + "ZZ_Herwig/" + m_muonSelector + analysisType + sProc + ".root";
	channel = "ZZ";
	TH1D* hZZ = setRegularMChisto(sProc, channel, path, hDir, hName, kBlue);

	sProc = "WZ_Herwig";
	path = dir + "WZ_Herwig/" + m_muonSelector + analysisType + sProc + ".root";
	channel = "WZ";
	TH1D* hWZ = setRegularMChisto(sProc, channel, path, hDir, hName, kBlue);
	
	sProc = "WW_Herwig";
	path = dir + "WW_Herwig/" + m_muonSelector + analysisType + sProc + ".root";
	channel = "WW";
	TH1D* hWW = setRegularMChisto(sProc, channel, path, hDir, hName, kBlue);
	
	sProc = "T1_McAtNlo_Jimmy";
	path = dir + "T1_McAtNlo_Jimmy/" + m_muonSelector + analysisType + sProc + ".root";
	channel = "t #bar{t}";
	TH1D* hTTbar = setRegularMChisto(sProc, channel, path, hDir, hName, kBlue);
	
	channel = "Binned DY#tau#tau";
	TH1D* hDYtautau = getNormDYtautau(dir+"DYtautau/"+m_muonSelector, hDir, hName);
	
	hBGsum->Add(hZZ);
	hBGsum->Add(hWZ);
	hBGsum->Add(hWW);
	hBGsum->Add(hTTbar);
	hBGsum->Add(hDYtautau);
	
	pad->cd();
	hBGsum->SetMinimum(m_miny);
	hBGsum->SetMaximum(m_maxy);
	//hBGsum->Draw("E4");
	hBGsum->Draw();
	hData->Draw("e1x0SAMES");
	pvtxt->Draw("SAMES");
	pvtxt1->Draw("SAMES");
	leg->Draw("SAMES");
	pad->RedrawAxis();

	
	if(m_doRatio)
	{
		TH1D* hRat = (TH1D*)hData->Clone("ratio");
		hRat->Reset();
		TH1D* hRatUp = (TH1D*)hData->Clone("ratUp");
		hRatUp->Reset();
		TH1D* hRatDwn = (TH1D*)hData->Clone("ratDwn");
		hRatDwn->Reset();
	
		double minrat = (m_minratiox==0.) ? hData->GetXaxis()->GetXmin() : m_minratiox;
		ratio(minrat, hRat->GetXaxis()->GetXmax(), hData, hBGsum, hRat, hRatUp, hRatDwn);
		pad_ratio->cd();
		drawRatio(minrat, hRat->GetXaxis()->GetXmax(), hRat);
		pad_ratio->RedrawAxis();
	}
	else
	{
		TH1D* hRelDiff = (TH1D*)hData->Clone("RelDiffio");
		hRelDiff->Reset();
	
		double minRelDiff = (m_minRelDiffx==0.) ? hData->GetXaxis()->GetXmin() : m_minRelDiffx;
		relDiff(hData, hBGsum, hRelDiff);
		pad_ratio->cd();
		drawRelDiff(minRelDiff, hRelDiff->GetXaxis()->GetXmax(), hRelDiff);
		pad_ratio->RedrawAxis();
	}
	
	size_t pos = hNameFixed.find("||");
	if(pos!=string::npos) hNameFixed = hNameFixed.substr(0,pos-1) + "_OR_" + hNameFixed.substr(pos+2);
	
	TString fName = "figures/" + (TString)hNameFixed + "." + (TString)muonLabel;
	cnv->SaveAs(fName+".eps");
	cnv->SaveAs(fName+".C");
	cnv->SaveAs(fName+".root");
	cnv->SaveAs(fName+".png");
}
