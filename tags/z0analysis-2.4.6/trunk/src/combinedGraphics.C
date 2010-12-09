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

void combinedGraphics::initialize(string analysisSelector)
{
	m_mcAnalysisSelector   = (analysisSelector=="digest") ? "mcDigest" : "mcOffline";
	m_dataAnalysisSelector = (analysisSelector=="digest") ? "digest"   : "offline";

	hFile->cd();
	
	setStyle();
	
	// canvas size
	canv_x = 602;
	canv_y = 400;

	// legend size
	leg_x1 = 0.765;
	leg_x2 = 0.919;
	leg_y1 = 0.376;
	leg_y2 = 0.922;
	
	//vcolors = new vector<Color_t>;
	//vcolors->push_back();
	
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
	period2lumiMap.insert( make_pair( "A",0.158011/1000 ) );
	period2lumiMap.insert( make_pair( "B",8.88014/1000  ) );
	period2lumiMap.insert( make_pair( "C",8.72868/1000  ) );
	period2lumiMap.insert( make_pair( "D",297.341/1000  ) );
	period2lumiMap.insert( make_pair( "E",1081.95/1000  ) );
	period2lumiMap.insert( make_pair( "F",1958.16/1000  ) );
	period2lumiMap.insert( make_pair( "G",8570.07/1000  ) );
	period2lumiMap.insert( make_pair( "H",8522.04/1000  ) );
	period2lumiMap.insert( make_pair( "I",22953.0/1000  ) );
	dataLumi_ipb = 0.;
	for(TMapsd::iterator it=period2lumiMap.begin() ; it!=period2lumiMap.end() ; ++it)
	{
		//if(it->first == "I") continue; // skip period I for now !!!
		dataLumi_ipb += it->second;
	}
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

void combinedGraphics::NormToDataLumi(TH1D* h, double crossSection_pb, double branchingRatio, double nMCevents, double dataLumi_pb)
{ 
	double mcLumi = nMCevents/(crossSection_pb*branchingRatio);
	if ( mcLumi>0 ) Scale(h, dataLumi_pb/mcLumi);
}

void combinedGraphics::setNormVals(double crossSection_pb, double branchingRatio, double nMCevents, double dataLumi_pb)
{
	m_crossSection_pb = crossSection_pb;
	m_branchingRatio = branchingRatio;
	m_nMCevents = nMCevents;
	m_dataLumi_pb = dataLumi_pb;
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
	
	lUnit = new TLine(0,1,hData->GetXaxis()->GetXmax(),1);
	lUnit->SetLineColor(kBlack);
	lUnit->Draw("SAMES");
	
	/*
	lLowBound = new TLine(xmin,hmin,xmin,hmax);
	lLowBound->SetLineColor(kBlack);
	lLowBound->SetLineWidth(3);
	if(xmin!=hData->GetXaxis()->GetXmin())
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
	
	lUnit = new TLine(0,1,hData->GetXaxis()->GetXmax(),1);
	lUnit->SetLineColor(kBlack);
	lUnit->Draw("SAMES");
	
	/*
	lLowBound = new TLine(xmin,1.5*hmin,xmin,0.5*hmax);
	lLowBound->SetLineColor(kBlack);
	lLowBound->SetLineWidth(3);
	if(xmin!=hData->GetXaxis()->GetXmin())
	{
		lLowBound->Draw("SAMES");
	}
	*/
}


void combinedGraphics::getHistosMap(TFile* f, string dir, TMapds* cutFlowOrdered, TMapds* cutFlowTypeOrdered)
{
	hFile->cd();

	hmap_cutFlow_imass = new TMapSP2TH1D();
	hmap_cutFlow_pT    = new TMapSP2TH1D();

	for(TMapds::iterator it=cutFlowOrdered->begin() ; it!=cutFlowOrdered->end() ; ++it)
	{
		double snumber = it->first;
		
		///////////////////////////////////////////////////////////////////////////
		// ignore preselection: ///////////////////////////////////////////////////
		if(cutFlowTypeOrdered->operator[](snumber)=="preselection") continue; /////
		///////////////////////////////////////////////////////////////////////////

		string sname = "";

		// invariant mass cut flow histos
		sname = "imass." + it->second;
		hmap_cutFlow_imass->insert( make_pair( sname, getHisto(f, dir, sname) ) );
		cout << "(" << snumber << ") obtained " << sname << endl;

		// pT cut flow histos
		sname = "pT." + it->second;
		hmap_cutFlow_pT->insert( make_pair( sname, getHisto(f, dir, sname) ) );
		cout << "(" << snumber << ") obtained " << sname << endl;
	}
}

void combinedGraphics::drawNormHistosMap(string channel, TMapds* cutFlowOrdered, TMapds* cutFlowTypeOrdered)
{
	hFile->cd();

	gStyle->SetOptStat(0);

	bool bfirst;
	
	Color_t colorStart  = 100;//kOrange; //40;
	Color_t colorOffset = -10;//1;
	Color_t colorAccumulate = colorStart;
	TMapSP2TH1D::iterator it;
	TMapds::iterator ii;
	string sname = "";
	
	leg_cutFlow_imass = new TLegend(0.8039215,0.4808014,0.9232736,0.9298832,NULL,"brNDC");
	leg_cutFlow_imass->SetFillColor(kWhite);
	leg_cutFlow_pT    = new TLegend(0.8039215,0.4808014,0.9232736,0.9298832,NULL,"brNDC");
	leg_cutFlow_pT->SetFillColor(kWhite);
	
	TPaveText* pvtxt = new TPaveText(0.6379599,0.8069948,0.8035117,0.9274611,"brNDC");
	pvtxt->SetFillColor(kWhite);
	TText* txt = pvtxt->AddText( channel.c_str() );
	
	stringstream strm;
	string L;
	string lumilabel = "";
	strm << setprecision(2);
	strm << dataLumi_ipb;
	strm >> L;
	lumilabel = "#intLdt~" + L + " pb^{-1}";
	TPaveText* pvtxt1 = new TPaveText(0.546462,0.6944909,0.7118499,0.8146912,"brNDC");
	pvtxt1->SetFillColor(kWhite);
	TText* txt1 = pvtxt1->AddText( lumilabel.c_str() );
	
	cnv_cutFlow_imass = new TCanvas("imass.cutFlow","imass.cutFlow",canv_x,canv_y);
	cnv_cutFlow_imass->SetFillColor(kWhite);
	cnv_cutFlow_imass->SetLogy();
	cnv_cutFlow_imass->SetLogx();
	cnv_cutFlow_imass->Draw();
	cnv_cutFlow_imass->cd();
	colorAccumulate = colorStart;
	
	bfirst = true;
	for(TMapds::iterator ii=cutFlowOrdered->begin() ; ii!=cutFlowOrdered->end() ; ++ii)
	{
		double num = ii->first;
		///////////////////////////////////////////////////////////////////////////
		// ignore preselection: ///////////////////////////////////////////////////
		if(cutFlowTypeOrdered->operator[](num)=="preselection") continue; /////////
		///////////////////////////////////////////////////////////////////////////
		
		string str = ii->second;
		it=hmap_cutFlow_imass->find("imass."+str);
		string sname = it->first;
		stringstream strm;
		string s1, s2;
		strm << setprecision(2);
		strm << (*hmap_cutFlow_imass)[sname]->GetBinWidth(1);
		strm >> s1;
		strm.clear();
		strm << setprecision(2);
		strm << (*hmap_cutFlow_imass)[sname]->GetBinWidth( (*hmap_cutFlow_imass)[sname]->GetNbinsX() );
		strm >> s2;
		string ytitle = "#frac{dN}{d#hat{m}} (" + s1 + "#rightarrow" + s2 + " TeV)^{-1}";
		/*
		double norm = (*hmap_cutFlow_imass)[sname]->GetEntries() * (*hmap_cutFlow_imass)[sname]->GetBinWidth(1);
		if(norm<=0)
		{
			cout << "ERROR: norm(" << sname << ") = 0" << endl;
			exit(-1);
		}
		(*hmap_cutFlow_imass)[sname]->Scale(1./norm);
		*/
		
		NormToDataLumi( (*hmap_cutFlow_imass)[sname], m_crossSection_pb, m_branchingRatio, m_nMCevents, m_dataLumi_pb);
		//NormToBinWidth( (*hmap_cutFlow_imass)[sname] );
		//Norm( (*hmap_cutFlow_imass)[sname] );
		(*hmap_cutFlow_imass)[sname]->SetTitle("");
		(*hmap_cutFlow_imass)[sname]->SetXTitle("#hat{m}_{#mu#mu} (TeV)");
		(*hmap_cutFlow_imass)[sname]->SetYTitle( ytitle.c_str() );
		(*hmap_cutFlow_imass)[sname]->SetFillColor(colorAccumulate);
		(*hmap_cutFlow_imass)[sname]->SetLineColor(colorAccumulate);
		leg_cutFlow_imass->AddEntry( (*hmap_cutFlow_imass)[sname], str.c_str(), "f");
		if(bfirst)
		{
			if(channel!="2010 Data") (*hmap_cutFlow_imass)[sname]->SetMinimum(1.e-2);
			//else                     (*hmap_cutFlow_imass)[sname]->SetMinimum(1.e-2);
			(*hmap_cutFlow_imass)[sname]->SetMaximum(1.e+4);
			(*hmap_cutFlow_imass)[sname]->Draw();
		}
		else (*hmap_cutFlow_imass)[sname]->Draw("SAMES");
		
		colorAccumulate += colorOffset;
		cout << "drawn " << sname << endl;
		
		bfirst = false;
	}
	cnv_cutFlow_imass->RedrawAxis();
	pvtxt->Draw("SMAES");
	pvtxt1->Draw("SMAES");
	leg_cutFlow_imass->Draw("SAMES");
	cnv_cutFlow_imass->Update();
	//cnv_cutFlow_imass->Write();
	
	//--------------
	
	cnv_cutFlow_pT = new TCanvas("pT.cutFlow","pT.cutFlow",canv_x,canv_y);
	cnv_cutFlow_pT->SetLogy();
	cnv_cutFlow_pT->SetLogx();
	cnv_cutFlow_pT->Draw();
	cnv_cutFlow_pT->cd();
	colorAccumulate = colorStart;
	
	bfirst = true;
	for(TMapds::iterator ii=cutFlowOrdered->begin() ; ii!=cutFlowOrdered->end() ; ++ii)
	{
		double num = ii->first;
		///////////////////////////////////////////////////////////////////////////
		// ignore preselection: ///////////////////////////////////////////////////
		if(cutFlowTypeOrdered->operator[](num)=="preselection") continue; /////////
		///////////////////////////////////////////////////////////////////////////
		
		string str = ii->second;
		it=hmap_cutFlow_pT->find("pT."+str);
		string sname = it->first;
		stringstream strm;
		string s1, s2;
		strm << setprecision(2);
		strm << (*hmap_cutFlow_pT)[sname]->GetBinWidth(1);
		strm >> s1;
		strm.clear();
		strm << setprecision(2);
		strm << (*hmap_cutFlow_pT)[sname]->GetBinWidth( (*hmap_cutFlow_pT)[sname]->GetNbinsX() );
		strm >> s2;
		string ytitle = "#frac{dN}{dp_{T}^{#mu}} (" + s1 + "#rightarrow" + s2 + " TeV)^{-1}";
		/*
		double norm = (*hmap_cutFlow_pT)[sname]->GetEntries() * (*hmap_cutFlow_pT)[sname]->GetBinWidth(1);
		if(norm<=0)
		{
			cout << "ERROR: norm(" << sname << ") = 0" << endl;
			exit(-1);
		}
		(*hmap_cutFlow_pT)[sname]->Scale(1./norm);
		*/
		
		NormToDataLumi( (*hmap_cutFlow_pT)[sname], m_crossSection_pb, m_branchingRatio, m_nMCevents, m_dataLumi_pb);
		//NormToBinWidth( (*hmap_cutFlow_pT)[sname] );
		//Norm( (*hmap_cutFlow_pT)[sname] );
		(*hmap_cutFlow_pT)[sname]->SetTitle("");
		(*hmap_cutFlow_pT)[sname]->SetXTitle("p_{T}^{#mu} (TeV)");
		(*hmap_cutFlow_pT)[sname]->SetYTitle( ytitle.c_str() );
		(*hmap_cutFlow_pT)[sname]->SetFillColor(colorAccumulate);
		(*hmap_cutFlow_pT)[sname]->SetLineColor(colorAccumulate);
		leg_cutFlow_pT->AddEntry( (*hmap_cutFlow_pT)[sname], str.c_str(), "f");
		if(bfirst)
		{
			if(channel!="2010 Data") (*hmap_cutFlow_pT)[sname]->SetMinimum(1.e-2);
			//else                     (*hmap_cutFlow_pT)[sname]->SetMinimum(1.e-2);
			(*hmap_cutFlow_pT)[sname]->SetMaximum(1.e+4);
			(*hmap_cutFlow_pT)[sname]->Draw();
		}
		else (*hmap_cutFlow_pT)[sname]->Draw("SAMES");
		colorAccumulate += colorOffset;
		cout << "drawn " << sname << endl;
		
		bfirst = false;
	}
	cnv_cutFlow_pT->RedrawAxis();
	pvtxt->Draw("SMAES");
	pvtxt1->Draw("SMAES");
	leg_cutFlow_pT->Draw("SAMES");
	cnv_cutFlow_pT->Update();
	//cnv_cutFlow_pT->Write();
}

void combinedGraphics::drawMCcutFlow()
{
	hFile->cd();

	string dir = "/srv01/tau/hod/";
	dir += (m_dataAnalysisSelector=="digest") ? "digestControl/" : "offlineControl/";
	string path = "";
	string channel = "";
	string hdir = "cutFlow";
	
	// main canvases
	cnv_MC_cutFlow_imass = new TCanvas("cnv_MC_cutFlow_imass", "cnv_MC_cutFlow_imass", 1200, 800);
	cnv_MC_cutFlow_imass->Divide(2,3);
	cnv_MC_cutFlow_imass->SetFillColor(kWhite);
	cnv_MC_cutFlow_imass->Draw();
	cnv_MC_cutFlow_imass->cd();
	cnv_MC_cutFlow_imass->Update();
	
	cnv_MC_cutFlow_pT = new TCanvas("cnv_MC_cutFlow_pT", "cnv_MC_cutFlow_pT", 1200, 800);
	cnv_MC_cutFlow_pT->Divide(2,3);
	cnv_MC_cutFlow_pT->SetFillColor(kWhite);
	cnv_MC_cutFlow_pT->Draw();
	cnv_MC_cutFlow_pT->cd();
	cnv_MC_cutFlow_pT->Update();
	
	
	// pads
	path = dir + m_mcAnalysisSelector + "Control_Zmumu.root";
	channel = "Z #rightarrow #mu^{+}#mu^{-}";
	setNormVals(989., 1., 299811, dataLumi_ipb);
	TFile* fZmumu = new TFile( path.c_str(), "READ" );
	getHistosMap(fZmumu, hdir, m_cutFlowOrdered, m_cutFlowTypeOrdered);
	drawNormHistosMap(channel, m_cutFlowOrdered, m_cutFlowTypeOrdered);
	cnv_MC_cutFlow_imass->cd(1);
	cnv_cutFlow_imass->DrawClonePad();
	cnv_MC_cutFlow_pT->cd(1);
	cnv_cutFlow_pT->DrawClonePad();
	
	path = dir + m_mcAnalysisSelector + "Control_Wmunu.root";
	channel = "W #rightarrow #mu#nuX";
	setNormVals(10454., 1., 989886, dataLumi_ipb);
	TFile* fWmunu = new TFile( path.c_str(), "READ" );
	getHistosMap(fWmunu, hdir, m_cutFlowOrdered, m_cutFlowTypeOrdered);
	drawNormHistosMap(channel, m_cutFlowOrdered, m_cutFlowTypeOrdered);
	cnv_MC_cutFlow_imass->cd(2);
	cnv_cutFlow_imass->DrawClonePad();
	cnv_MC_cutFlow_pT->cd(2);
	cnv_cutFlow_pT->DrawClonePad();
	
	path = dir + m_mcAnalysisSelector + "Control_Ztautau.root";
	channel = "Z #rightarrow #tau^{+}#tau^{-}";
	setNormVals(989., 1., 1998598, dataLumi_ipb);
	TFile* fZtautau = new TFile( path.c_str(), "READ" );
	getHistosMap(fZtautau, hdir, m_cutFlowOrdered, m_cutFlowTypeOrdered);
	drawNormHistosMap(channel, m_cutFlowOrdered, m_cutFlowTypeOrdered);
	cnv_MC_cutFlow_imass->cd(3);
	cnv_cutFlow_imass->DrawClonePad();
	cnv_MC_cutFlow_pT->cd(3);
	cnv_cutFlow_pT->DrawClonePad();
	
	path = dir + m_mcAnalysisSelector + "Control_TTbar.root";
	channel = "t #bar{t} #rightarrow #mu^{+}#mu^{-}X";
	setNormVals(161., 1., 199838, dataLumi_ipb);
	TFile* fTTbar = new TFile( path.c_str(), "READ" );
	getHistosMap(fTTbar, hdir, m_cutFlowOrdered, m_cutFlowTypeOrdered);
	drawNormHistosMap(channel, m_cutFlowOrdered, m_cutFlowTypeOrdered);
	cnv_MC_cutFlow_imass->cd(4);
	cnv_cutFlow_imass->DrawClonePad();
	cnv_MC_cutFlow_pT->cd(4);
	cnv_cutFlow_pT->DrawClonePad();
	
	path = dir + m_mcAnalysisSelector + "Control_bbmu15X.root";
	channel = "b #bar{b} #rightarrow #mu^{+}#mu^{-}X";
	setNormVals(7.39e+4, 1., 4388911, dataLumi_ipb);
	TFile* fbbmu15X = new TFile( path.c_str(), "READ" );
	getHistosMap(fbbmu15X, hdir, m_cutFlowOrdered, m_cutFlowTypeOrdered);
	drawNormHistosMap(channel, m_cutFlowOrdered, m_cutFlowTypeOrdered);
	cnv_MC_cutFlow_imass->cd(5);
	cnv_cutFlow_imass->DrawClonePad();
	cnv_MC_cutFlow_pT->cd(5);
	cnv_cutFlow_pT->DrawClonePad();
	
	path = dir + m_mcAnalysisSelector + "Control_ccmu15X.root";
	channel = "c #bar{c} #rightarrow #mu^{+}#mu^{-}X";
	setNormVals(2.84e+4, 1., 1499257, dataLumi_ipb);
	TFile* fccmu15X = new TFile( path.c_str(), "READ" );
	getHistosMap(fccmu15X, hdir, m_cutFlowOrdered, m_cutFlowTypeOrdered);
	drawNormHistosMap(channel, m_cutFlowOrdered, m_cutFlowTypeOrdered);
	cnv_MC_cutFlow_imass->cd(6);
	cnv_cutFlow_imass->DrawClonePad();
	cnv_MC_cutFlow_pT->cd(6);
	cnv_cutFlow_pT->DrawClonePad();
}


void combinedGraphics::drawDataCutFlow()
{
	hFile->cd();

	string dir = "/srv01/tau/hod/";
	dir += (m_dataAnalysisSelector=="digest") ? "digestControl/" : "offlineControl/";
	string path = "";
	string channel = "";
	string hdir = "cutFlow";
	
	// main canvases
	cnv_data_cutFlow_imass = new TCanvas("cnv_data_cutFlow_imass", "cnv_data_cutFlow_imass", 1200, 800);
	cnv_data_cutFlow_imass->SetFillColor(kWhite);
	cnv_data_cutFlow_imass->Draw();
	cnv_data_cutFlow_imass->cd();
	cnv_data_cutFlow_imass->Update();
	
	cnv_data_cutFlow_pT = new TCanvas("cnv_data_cutFlow_pT", "cnv_data_cutFlow_pT", 1200, 800);
	cnv_data_cutFlow_pT->SetFillColor(kWhite);
	cnv_data_cutFlow_pT->Draw();
	cnv_data_cutFlow_pT->cd();
	cnv_data_cutFlow_pT->Update();
	
	
	path = dir + m_dataAnalysisSelector + "Control.root";
	channel = "2010 Data";
	setNormVals(1., 1., 1, 1.);
	TFile* fZmumu = new TFile( path.c_str(), "READ" );
	getHistosMap(fZmumu, hdir, m_cutFlowOrdered, m_cutFlowTypeOrdered);
	drawNormHistosMap(channel, m_cutFlowOrdered, m_cutFlowTypeOrdered);
	cnv_data_cutFlow_imass->cd();
	cnv_cutFlow_imass->DrawClonePad();
	cnv_data_cutFlow_pT->cd();
	cnv_cutFlow_pT->DrawClonePad();
}

TH1D* combinedGraphics::getNormDYmumu(string sHistName)
{
	hFile->cd();

	string dir = "/srv01/tau/hod/";
	dir += (m_dataAnalysisSelector=="digest") ? "digestControl/" : "offlineControl/";
	string path = "";
	string hdir = "allCuts";
	string tmp = (m_dataAnalysisSelector=="digest") ? "mcDigestControl_" : "mcOfflineControl_";
	
	path = dir + tmp + "DYmumu_75M120.root";
	TFile* fDYmumu75M120 = new TFile( path.c_str(), "READ" );
	TH1D* hDYmumu75M120 = getHisto(fDYmumu75M120, hdir, sHistName.c_str());
	setNormVals(819.93, 1., 19994, dataLumi_ipb);
	NormToDataLumi( hDYmumu75M120, m_crossSection_pb, m_branchingRatio, m_nMCevents, m_dataLumi_pb);
	
	path = dir + tmp + "DYmumu_120M250.root";
	TFile* fDYmumu120M250 = new TFile( path.c_str(), "READ" );
	TH1D* hDYmumu120M250 = getHisto(fDYmumu120M250, hdir, sHistName.c_str());
	setNormVals(8.7158, 1., 19996, dataLumi_ipb);
	NormToDataLumi( hDYmumu120M250, m_crossSection_pb, m_branchingRatio, m_nMCevents, m_dataLumi_pb);
	
	path = dir + tmp + "DYmumu_250M400.root";
	TFile* fDYmumu250M400 = new TFile( path.c_str(), "READ" );
	TH1D* hDYmumu250M400 = getHisto(fDYmumu250M400, hdir, sHistName.c_str());
	setNormVals(0.41571, 1., 19997, dataLumi_ipb);
	NormToDataLumi( hDYmumu250M400, m_crossSection_pb, m_branchingRatio, m_nMCevents, m_dataLumi_pb);
	
	path = dir + tmp + "DYmumu_400M600.root";
	TFile* fDYmumu400M600 = new TFile( path.c_str(), "READ" );
	TH1D* hDYmumu400M600 = getHisto(fDYmumu400M600, hdir, sHistName.c_str());
	setNormVals(0.06724, 1., 19996, dataLumi_ipb);
	NormToDataLumi( hDYmumu400M600, m_crossSection_pb, m_branchingRatio, m_nMCevents, m_dataLumi_pb);
	
	path = dir + tmp + "DYmumu_600M800.root";
	TFile* fDYmumu600M800 = new TFile( path.c_str(), "READ" );
	TH1D* hDYmumu600M800 = getHisto(fDYmumu600M800, hdir, sHistName.c_str());
	setNormVals(0.01116, 1., 19993, dataLumi_ipb);
	NormToDataLumi( hDYmumu600M800, m_crossSection_pb, m_branchingRatio, m_nMCevents, m_dataLumi_pb);
	
	path = dir + tmp + "DYmumu_800M1000.root";
	TFile* fDYmumu800M1000 = new TFile( path.c_str(), "READ" );
	TH1D* hDYmumu800M1000 = getHisto(fDYmumu800M1000, hdir, sHistName.c_str());
	setNormVals(0.0027437, 1., 19946, dataLumi_ipb);
	NormToDataLumi( hDYmumu800M1000, m_crossSection_pb, m_branchingRatio, m_nMCevents, m_dataLumi_pb);
	
	path = dir + tmp + "DYmumu_1000M1250.root";
	TFile* fDYmumu1000M1250 = new TFile( path.c_str(), "READ" );
	TH1D* hDYmumu1000M1250 = getHisto(fDYmumu1000M1250, hdir, sHistName.c_str());
	setNormVals(0.00091775, 1., 19992, dataLumi_ipb);
	NormToDataLumi( hDYmumu1000M1250, m_crossSection_pb, m_branchingRatio, m_nMCevents, m_dataLumi_pb);
	
	path = dir + tmp + "DYmumu_1250M1500.root";
	TFile* fDYmumu1250M1500 = new TFile( path.c_str(), "READ" );
	TH1D* hDYmumu1250M1500 = getHisto(fDYmumu1250M1500, hdir, sHistName.c_str());
	setNormVals(0.00024866, 1., 19995, dataLumi_ipb);
	NormToDataLumi( hDYmumu1250M1500, m_crossSection_pb, m_branchingRatio, m_nMCevents, m_dataLumi_pb);
	
	path = dir + tmp + "DYmumu_1500M1750.root";
	TFile* fDYmumu1500M1750 = new TFile( path.c_str(), "READ" );
	TH1D* hDYmumu1500M1750 = getHisto(fDYmumu1500M1750, hdir, sHistName.c_str());
	setNormVals(0.00007659, 1., 19987, dataLumi_ipb);
	NormToDataLumi( hDYmumu1500M1750, m_crossSection_pb, m_branchingRatio, m_nMCevents, m_dataLumi_pb);
	
	path = dir + tmp + "DYmumu_1750M2000.root";
	TFile* fDYmumu1750M2000 = new TFile( path.c_str(), "READ" );
	TH1D* hDYmumu1750M2000 = getHisto(fDYmumu1750M2000, hdir, sHistName.c_str());
	setNormVals(0.000026361, 1., 19991, dataLumi_ipb);
	NormToDataLumi( hDYmumu1750M2000, m_crossSection_pb, m_branchingRatio, m_nMCevents, m_dataLumi_pb);
	
	path = dir + tmp + "DYmumu_M2000.root";
	TFile* fDYmumuM2000 = new TFile( path.c_str(), "READ" );
	TH1D* hDYmumuM2000 = getHisto(fDYmumuM2000, hdir, sHistName.c_str());
	setNormVals(0.000015325, 1., 19990, dataLumi_ipb);
	NormToDataLumi( hDYmumuM2000, m_crossSection_pb, m_branchingRatio, m_nMCevents, m_dataLumi_pb);
	
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

TH1D* combinedGraphics::getNormDYtautau(string sHistName)
{
	hFile->cd();

	string dir = "/srv01/tau/hod/";
	dir += (m_dataAnalysisSelector=="digest") ? "digestControl/" : "offlineControl/";
	string path = "";
	string hdir = "allCuts";
	string tmp = (m_dataAnalysisSelector=="digest") ? "mcDigestControl_" : "mcOfflineControl_";	

	
	path = dir + tmp + "DYtautau_75M120.root";
	TFile* fDYtautau75M120 = new TFile( path.c_str(), "READ" );
	TH1D* hDYtautau75M120 = getHisto(fDYtautau75M120, hdir, sHistName.c_str());
	setNormVals(817.8, 1., 19998, dataLumi_ipb);
	NormToDataLumi( hDYtautau75M120, m_crossSection_pb, m_branchingRatio, m_nMCevents, m_dataLumi_pb);
	
	path = dir + tmp + "DYtautau_120M250.root";
	TFile* fDYtautau120M250 = new TFile( path.c_str(), "READ" );
	TH1D* hDYtautau120M250 = getHisto(fDYtautau120M250, hdir, sHistName.c_str());
	setNormVals(8.6608, 1., 19996, dataLumi_ipb);
	NormToDataLumi( hDYtautau120M250, m_crossSection_pb, m_branchingRatio, m_nMCevents, m_dataLumi_pb);
	
	path = dir + tmp + "DYtautau_250M400.root";
	TFile* fDYtautau250M400 = new TFile( path.c_str(), "READ" );
	TH1D* hDYtautau250M400 = getHisto(fDYtautau250M400, hdir, sHistName.c_str());
	setNormVals(0.41613, 1., 19994, dataLumi_ipb);
	NormToDataLumi( hDYtautau250M400, m_crossSection_pb, m_branchingRatio, m_nMCevents, m_dataLumi_pb);
	
	path = dir + tmp + "DYtautau_400M600.root";
	TFile* fDYtautau400M600 = new TFile( path.c_str(), "READ" );
	TH1D* hDYtautau400M600 = getHisto(fDYtautau400M600, hdir, sHistName.c_str());
	setNormVals(0.067269, 1., 19992, dataLumi_ipb);
	NormToDataLumi( hDYtautau400M600, m_crossSection_pb, m_branchingRatio, m_nMCevents, m_dataLumi_pb);
	
	path = dir + tmp + "DYtautau_600M800.root";
	TFile* fDYtautau600M800 = new TFile( path.c_str(), "READ" );
	TH1D* hDYtautau600M800 = getHisto(fDYtautau600M800, hdir, sHistName.c_str());
	setNormVals(0.01116, 1., 19986, dataLumi_ipb);
	NormToDataLumi( hDYtautau600M800, m_crossSection_pb, m_branchingRatio, m_nMCevents, m_dataLumi_pb);
	
	path = dir + tmp + "DYtautau_800M1000.root";
	TFile* fDYtautau800M1000 = new TFile( path.c_str(), "READ" );
	TH1D* hDYtautau800M1000 = getHisto(fDYtautau800M1000, hdir, sHistName.c_str());
	setNormVals(0.0027437, 1., 19984, dataLumi_ipb);
	NormToDataLumi( hDYtautau800M1000, m_crossSection_pb, m_branchingRatio, m_nMCevents, m_dataLumi_pb);
	
	path = dir + tmp + "DYtautau_1000M1250.root";
	TFile* fDYtautau1000M1250 = new TFile( path.c_str(), "READ" );
	TH1D* hDYtautau1000M1250 = getHisto(fDYtautau1000M1250, hdir, sHistName.c_str());
	setNormVals(0.00091775, 1., 19980, dataLumi_ipb);
	NormToDataLumi( hDYtautau1000M1250, m_crossSection_pb, m_branchingRatio, m_nMCevents, m_dataLumi_pb);
	
	path = dir + tmp + "DYtautau_1250M1500.root";
	TFile* fDYtautau1250M1500 = new TFile( path.c_str(), "READ" );
	TH1D* hDYtautau1250M1500 = getHisto(fDYtautau1250M1500, hdir, sHistName.c_str());
	setNormVals(0.00024897, 1., 19973, dataLumi_ipb);
	NormToDataLumi( hDYtautau1250M1500, m_crossSection_pb, m_branchingRatio, m_nMCevents, m_dataLumi_pb);
	
	path = dir + tmp + "DYtautau_1500M1750.root";
	TFile* fDYtautau1500M1750 = new TFile( path.c_str(), "READ" );
	TH1D* hDYtautau1500M1750 = getHisto(fDYtautau1500M1750, hdir, sHistName.c_str());
	setNormVals(0.000076551, 1., 19974, dataLumi_ipb);
	NormToDataLumi( hDYtautau1500M1750, m_crossSection_pb, m_branchingRatio, m_nMCevents, m_dataLumi_pb);
	
	path = dir + tmp + "DYtautau_1750M2000.root";
	TFile* fDYtautau1750M2000 = new TFile( path.c_str(), "READ" );
	TH1D* hDYtautau1750M2000 = getHisto(fDYtautau1750M2000, hdir, sHistName.c_str());
	setNormVals(0.000026356, 1., 19968, dataLumi_ipb);
	NormToDataLumi( hDYtautau1750M2000, m_crossSection_pb, m_branchingRatio, m_nMCevents, m_dataLumi_pb);
	
	path = dir + tmp + "DYtautau_M2000.root";
	TFile* fDYtautauM2000 = new TFile( path.c_str(), "READ" );
	TH1D* hDYtautauM2000 = getHisto(fDYtautauM2000, hdir, sHistName.c_str());
	setNormVals(0.000015323, 1., 18966, dataLumi_ipb);
	NormToDataLumi( hDYtautauM2000, m_crossSection_pb, m_branchingRatio, m_nMCevents, m_dataLumi_pb);
	
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


void combinedGraphics::drawimass()
{
	hFile->cd();
	
	string dir = "/srv01/tau/hod/";
	dir += (m_dataAnalysisSelector=="digest") ? "digestControl/" : "offlineControl/";
	string path = "";
	string channel = "";
	string hdir = "allCuts";
	string tmp = (m_dataAnalysisSelector=="digest") ? "mcDigestControl_" : "mcOfflineControl_";
	
	
	gStyle->SetOptStat(0);
	
	
	leg_imass = new TLegend(0.8039215,0.4808014,0.9232736,0.9298832,NULL,"brNDC");
	leg_imass->SetFillColor(kWhite);
	
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
	
	
	// main canvases
	cnv_imass = new TCanvas("cnv_imass", "cnv_imass", 0,0,1200,800);
	cnv_imass->Divide(1,2);
	
	pad_imass = cnv_imass->cd(1);
	pad_imass->SetPad(0.009197324,0.2150259,0.9899666,0.9909326);
	pad_imass->SetFillColor(kWhite);
	pad_imass->SetLogx();
	pad_imass->SetLogy();
	
	pad_imass_ratio = cnv_imass->cd(2);
	pad_imass_ratio->SetPad(0.009197324,0.01036269,0.9899666,0.253886);
	pad_imass_ratio->SetFillColor(kWhite);
	pad_imass_ratio->SetLogx();
	pad_imass_ratio->SetLogy();
	
	cnv_imass->Draw();
	cnv_imass->cd();
	cnv_imass->Update();
	
	Color_t colorStart  = 100;//kOrange; //40;
	Color_t colorOffset = -10;//1;
	Color_t colorAccumulate = colorStart;
	
	string s1, s2;

	//path = dir + m_dataAnalysisSelector + "Control.root";
	//path = dir + "offlineControl_13102010_A-I2_ZprimeGRL_etaBarrel.root";
	path = dir + "offlineControl_16112010_A-I2_ZprimeGRL_barrel.root";
	TFile* fdata = new TFile( path.c_str(), "READ" );
	hData = getHisto(fdata, hdir, "imass");
	leg_imass->AddEntry( hData, "Data", "lep");
	
	
	
	path = dir + m_mcAnalysisSelector + "Control_Zprime_mumu_SSM1000.root";
	channel = "1 TeV Z' #rightarrow #mu^{+}#mu^{-}";
	TFile* fZprime_mumu_SSM1000 = new TFile( path.c_str(), "READ" );
	hZprime_mumu_SSM1000 = getHisto(fZprime_mumu_SSM1000, hdir, "imass");
	setNormVals(0.12881, 1., 19996, dataLumi_ipb);
	NormToDataLumi( hZprime_mumu_SSM1000, m_crossSection_pb, m_branchingRatio, m_nMCevents, m_dataLumi_pb);
	//////////////////////////////////////////////////////
	// Z' interfere with the SM (DYmumu) /////////////////
	//hZprime_mumu_SSM1000->Add( getNormDYmumu() ); ////////
	//////////////////////////////////////////////////////
	hZprime_mumu_SSM1000->SetLineColor(kBlue);
	hZprime_mumu_SSM1000->SetLineWidth(2);
	hZprime_mumu_SSM1000->SetMinimum(5.e-5);
	hZprime_mumu_SSM1000->SetMaximum(3.e+3);
	strm.clear();
	strm << setprecision(2);
	strm << hZprime_mumu_SSM1000->GetBinWidth(1);
	strm >> s1;
	strm.clear();
	strm << setprecision(2);
	strm << hZprime_mumu_SSM1000->GetBinWidth( hZprime_mumu_SSM1000->GetNbinsX() );
	strm >> s2;
	string ytitle = "#frac{dN}{d#hat{m}} (" + s1 + "#rightarrow" + s2 + " TeV)^{-1}";
	hZprime_mumu_SSM1000->SetTitle("");
	hZprime_mumu_SSM1000->SetXTitle("#hat{m}_{#mu#mu} (TeV)");
	hZprime_mumu_SSM1000->SetYTitle( ytitle.c_str() );
	leg_imass->AddEntry( hZprime_mumu_SSM1000, channel.c_str(), "f");
	
	
	channel = "SM(sig+bkg)";
	hMCimass = getNormDYmumu("imass");
	hMCimass->SetFillColor(colorAccumulate);
	hMCimass->SetLineColor(colorAccumulate);
	hMCimass->SetTitle("");
	leg_imass->AddEntry( hMCimass, channel.c_str(), "f");
	colorAccumulate+=colorOffset;
	
	
	channel = "binned DY#mu#mu";
	hDYmumu = getNormDYmumu("imass");
	hDYmumu->SetFillColor(colorAccumulate);
	hDYmumu->SetLineColor(colorAccumulate);
	hDYmumu->SetTitle("");
	leg_imass->AddEntry( hDYmumu, channel.c_str(), "f");
	colorAccumulate+=colorOffset;
	
	
	path = dir + m_mcAnalysisSelector + "Control_TTbar.root";
	channel = "t #bar{t} #rightarrow #mu^{+}#mu^{-}X";
	TFile* fTTbar = new TFile( path.c_str(), "READ" );
	hTTbar = getHisto(fTTbar, hdir, "imass");
	setNormVals(161., 1., 199838, dataLumi_ipb);
	NormToDataLumi( hTTbar, m_crossSection_pb, m_branchingRatio, m_nMCevents, m_dataLumi_pb);
	hTTbar->SetFillColor(colorAccumulate);
	hTTbar->SetLineColor(colorAccumulate);
	hTTbar->SetTitle("");
	leg_imass->AddEntry( hTTbar, channel.c_str(), "f");
	colorAccumulate+=colorOffset;
	
	
	path = dir + m_mcAnalysisSelector + "Control_gg2WW0240_JIMMY_WW_munumunu.root";
	channel = "WW #rightarrow #mu#nu#mu#nu";
	TFile* fWW = new TFile( path.c_str(), "READ" );
	hWW = getHisto(fWW, hdir, "imass");
	setNormVals(0.01524, 0.98981, 9999, dataLumi_ipb);
	NormToDataLumi( hWW, m_crossSection_pb, m_branchingRatio, m_nMCevents, m_dataLumi_pb);
	hWW->SetFillColor(colorAccumulate);
	hWW->SetLineColor(colorAccumulate);
	hWW->SetTitle("");
	leg_imass->AddEntry( hWW, channel.c_str(), "f");
	colorAccumulate+=colorOffset;
	
	
	channel = "binned DY#tau#tau";
	hDYtautau = getNormDYtautau("imass");
	hDYtautau->SetFillColor(colorAccumulate);
	hDYtautau->SetLineColor(colorAccumulate);
	hDYtautau->SetTitle("");
	leg_imass->AddEntry( hDYtautau, channel.c_str(), "f");
	colorAccumulate+=colorOffset;
	
	/*
	path = dir + m_mcAnalysisSelector + "Control_bbmu15X.root";
	channel = "b #bar{b} #rightarrow #mu^{+}#mu^{-}X";
	TFile* fbbmu15X = new TFile( path.c_str(), "READ" );
	hbbmu15X = getHisto(fbbmu15X, hdir, "imass");
	setNormVals(7.39e+4, 1., 4388911, dataLumi_ipb);
	NormToDataLumi( hbbmu15X, m_crossSection_pb, m_branchingRatio, m_nMCevents, m_dataLumi_pb);
	hbbmu15X->SetFillColor(colorAccumulate);
	hbbmu15X->SetLineColor(colorAccumulate);
	hbbmu15X->SetTitle("");
	leg_imass->AddEntry( hbbmu15X, channel.c_str(), "f");
	colorAccumulate+=colorOffset;
	*/
	
	path = dir + m_mcAnalysisSelector + "Control_Wmunu.root";
	channel = "W #rightarrow #mu#nuX";
	TFile* fWmunu = new TFile( path.c_str(), "READ" );
	hWmunu = getHisto(fWmunu, hdir, "imass");
	setNormVals(10454., 1., 989886, dataLumi_ipb);
	NormToDataLumi( hWmunu, m_crossSection_pb, m_branchingRatio, m_nMCevents, m_dataLumi_pb);
	hWmunu->SetFillColor(colorAccumulate);
	hWmunu->SetLineColor(colorAccumulate);
	hWmunu->SetTitle("");
	leg_imass->AddEntry( hWmunu, channel.c_str(), "f");
	colorAccumulate+=colorOffset;
	
	/*
	path = dir + m_mcAnalysisSelector + "Control_ccmu15X.root";
	channel = "c #bar{c} #rightarrow #mu^{+}#mu^{-}X";
	TFile* fccmu15X = new TFile( path.c_str(), "READ" );
	hccmu15X = getHisto(fccmu15X, hdir, "imass");
	setNormVals(2.84e+4, 1., 1499257, dataLumi_ipb);
	NormToDataLumi( hccmu15X, m_crossSection_pb, m_branchingRatio, m_nMCevents, m_dataLumi_pb);
	hccmu15X->SetFillColor(colorAccumulate);
	hccmu15X->SetLineColor(colorAccumulate);
	hccmu15X->SetTitle("");
	leg_imass->AddEntry( hccmu15X, channel.c_str(), "f");
	colorAccumulate+=colorOffset;
	*/
	
	hMCimass->Add(hWW);
	hMCimass->Add(hTTbar);
	hMCimass->Add(hDYtautau);
	//hMCimass->Add(hbbmu15X);
	hMCimass->Add(hWmunu);
	//hMCimass->Add(hccmu15X);
	
	//////////////////////////////////////
	double mHatMin = 0.075; // TeV ///////
	//////////////////////////////////////
	
	/*
	lLowBound = new TLine(mHatMin,hMCimass->GetMinimum(),mHatMin,hMCimass->GetMaximum());
	lLowBound->SetLineColor(kBlack);
	lLowBound->SetLineWidth(3);
	*/
	
	pad_imass->cd();
	hZprime_mumu_SSM1000->Draw();
	hMCimass->Draw("SAMES");
	hDYmumu->Draw("SAMES");
	hTTbar->Draw("SAMES");
	hDYtautau->Draw("SAMES");
	hWW->Draw("SAMES");
	//hbbmu15X->Draw("SAMES");
	hWmunu->Draw("SAMES");
	//hccmu15X->Draw("SAMES");
	hData->Draw("e1x0SAMES");
	pvtxt->Draw("SAMES");
	leg_imass->Draw("SAMES");
	//lLowBound->Draw("SMAES");
	pad_imass->RedrawAxis();
	
	
	hRat = (TH1D*)hData->Clone("ratio");
	hRat->Reset();
	hRatUp = (TH1D*)hData->Clone("ratUp");
	hRatUp->Reset();
	hRatDwn = (TH1D*)hData->Clone("ratDwn");
	hRatDwn->Reset();
	
	ratio(mHatMin, hRat->GetXaxis()->GetXmax(), hData, hMCimass, hRat, hRatUp, hRatDwn);
	pad_imass_ratio->cd();
	drawRatio(mHatMin, hRat->GetXaxis()->GetXmax(), hRat);
	pad_imass_ratio->RedrawAxis();
	
}


void combinedGraphics::drawpT()
{
	hFile->cd();

	string dir = "/srv01/tau/hod/";
	dir += (m_dataAnalysisSelector=="digest") ? "digestControl/" : "offlineControl/";
	string path = "";
	string channel = "";
	string hdir = "allCuts";
	string tmp = (m_dataAnalysisSelector=="digest") ? "mcDigestControl_" : "mcOfflineControl_";
	
	
	gStyle->SetOptStat(0);
	
	
	leg_pT = new TLegend(0.8039215,0.4808014,0.9232736,0.9298832,NULL,"brNDC");
	leg_pT->SetFillColor(kWhite);
	
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
	
	
	// main canvases
	cnv_pT = new TCanvas("cnv_pT", "cnv_pT", 0,0,1200,800);
	cnv_pT->Divide(1,2);
	
	pad_pT = cnv_pT->cd(1);
	pad_pT->SetPad(0.009197324,0.2150259,0.9899666,0.9909326);
	pad_pT->SetFillColor(kWhite);
	pad_pT->SetLogx();
	pad_pT->SetLogy();
	
	pad_pT_ratio = cnv_pT->cd(2);
	pad_pT_ratio->SetPad(0.009197324,0.01036269,0.9899666,0.253886);
	pad_pT_ratio->SetFillColor(kWhite);
	pad_pT_ratio->SetLogx();
	pad_pT_ratio->SetLogy();
	
	cnv_pT->Draw();
	cnv_pT->cd();
	cnv_pT->Update();
	
	Color_t colorStart  = 100;//kOrange; //40;
	Color_t colorOffset = -10;//1;
	Color_t colorAccumulate = colorStart;
	
	string s1, s2;

	//path = dir + m_dataAnalysisSelector + "Control.root";
	//path = dir + "offlineControl_13102010_A-I2_ZprimeGRL_etaBarrel.root";
	path = dir + "offlineControl_16112010_A-I2_ZprimeGRL_barrel.root";
	TFile* fdata = new TFile( path.c_str(), "READ" );
	hData = getHisto(fdata, hdir, "pT");
	leg_pT->AddEntry( hData, "Data", "lep");
	
	
	
	path = dir + m_mcAnalysisSelector + "Control_Zprime_mumu_SSM1000.root";
	channel = "1 TeV Z' #rightarrow #mu^{+}#mu^{-}";
	TFile* fZprime_mumu_SSM1000 = new TFile( path.c_str(), "READ" );
	hZprime_mumu_SSM1000 = getHisto(fZprime_mumu_SSM1000, hdir, "pT");
	setNormVals(0.12881, 1., 19996, dataLumi_ipb);
	NormToDataLumi( hZprime_mumu_SSM1000, m_crossSection_pb, m_branchingRatio, m_nMCevents, m_dataLumi_pb);
	//////////////////////////////////////////////////////
	// Z' interfere with the SM (DYmumu) /////////////////
	//hZprime_mumu_SSM1000->Add( getNormDYmumu() ); ////////
	//////////////////////////////////////////////////////
	hZprime_mumu_SSM1000->SetLineColor(kBlue);
	hZprime_mumu_SSM1000->SetLineWidth(2);
	hZprime_mumu_SSM1000->SetMinimum(5.e-5);
	hZprime_mumu_SSM1000->SetMaximum(3.e+3);
	strm.clear();
	strm << setprecision(2);
	strm << hZprime_mumu_SSM1000->GetBinWidth(1);
	strm >> s1;
	strm.clear();
	strm << setprecision(2);
	strm << hZprime_mumu_SSM1000->GetBinWidth( hZprime_mumu_SSM1000->GetNbinsX() );
	strm >> s2;
	string ytitle = "#frac{dN}{dp_{T}} (" + s1 + "#rightarrow" + s2 + " TeV)^{-1}";
	hZprime_mumu_SSM1000->SetTitle("");
	hZprime_mumu_SSM1000->SetXTitle("p_{T}^{#mu} (TeV)");
	hZprime_mumu_SSM1000->SetYTitle( ytitle.c_str() );
	leg_pT->AddEntry( hZprime_mumu_SSM1000, channel.c_str(), "f");
	
	
	channel = "SM(sig+bkg)";
	hMCpT = getNormDYmumu("pT");
	hMCpT->SetFillColor(colorAccumulate);
	hMCpT->SetLineColor(colorAccumulate);
	hMCpT->SetTitle("");
	leg_pT->AddEntry( hMCpT, channel.c_str(), "f");
	colorAccumulate+=colorOffset;
	
	
	channel = "binned DY#mu#mu";
	hDYmumu = getNormDYmumu("pT");
	hDYmumu->SetFillColor(colorAccumulate);
	hDYmumu->SetLineColor(colorAccumulate);
	hDYmumu->SetTitle("");
	leg_pT->AddEntry( hDYmumu, channel.c_str(), "f");
	colorAccumulate+=colorOffset;
	
	
	path = dir + m_mcAnalysisSelector + "Control_TTbar.root";
	channel = "t #bar{t} #rightarrow #mu^{+}#mu^{-}X";
	TFile* fTTbar = new TFile( path.c_str(), "READ" );
	hTTbar = getHisto(fTTbar, hdir, "pT");
	setNormVals(161., 1., 199838, dataLumi_ipb);
	NormToDataLumi( hTTbar, m_crossSection_pb, m_branchingRatio, m_nMCevents, m_dataLumi_pb);
	hTTbar->SetFillColor(colorAccumulate);
	hTTbar->SetLineColor(colorAccumulate);
	hTTbar->SetTitle("");
	leg_pT->AddEntry( hTTbar, channel.c_str(), "f");
	colorAccumulate+=colorOffset;
	
	path = dir + m_mcAnalysisSelector + "Control_gg2WW0240_JIMMY_WW_munumunu.root";
	channel = "WW #rightarrow #mu#nu#mu#nu";
	TFile* fWW = new TFile( path.c_str(), "READ" );
	hWW = getHisto(fWW, hdir, "imass");
	setNormVals(0.01524, 1., 9999, dataLumi_ipb);
	NormToDataLumi( hWW, m_crossSection_pb, m_branchingRatio, m_nMCevents, m_dataLumi_pb);
	hWW->SetFillColor(colorAccumulate);
	hWW->SetLineColor(colorAccumulate);
	hWW->SetTitle("");
	leg_pT->AddEntry( hWW, channel.c_str(), "f");
	colorAccumulate+=colorOffset;
	
	
	channel = "binned DY#tau#tau";
	hDYtautau = getNormDYtautau("pT");
	hDYtautau->SetFillColor(colorAccumulate);
	hDYtautau->SetLineColor(colorAccumulate);
	hDYtautau->SetTitle("");
	leg_pT->AddEntry( hDYtautau, channel.c_str(), "f");
	colorAccumulate+=colorOffset;
	
	/*
	path = dir + m_mcAnalysisSelector + "Control_bbmu15X.root";
	channel = "b #bar{b} #rightarrow #mu^{+}#mu^{-}X";
	TFile* fbbmu15X = new TFile( path.c_str(), "READ" );
	hbbmu15X = getHisto(fbbmu15X, hdir, "pT");
	setNormVals(7.39e+4, 1., 4388911, dataLumi_ipb);
	NormToDataLumi( hbbmu15X, m_crossSection_pb, m_branchingRatio, m_nMCevents, m_dataLumi_pb);
	hbbmu15X->SetFillColor(colorAccumulate);
	hbbmu15X->SetLineColor(colorAccumulate);
	hbbmu15X->SetTitle("");
	leg_pT->AddEntry( hbbmu15X, channel.c_str(), "f");
	colorAccumulate+=colorOffset;
	*/
	
	path = dir + m_mcAnalysisSelector + "Control_Wmunu.root";
	channel = "W #rightarrow #mu#nuX";
	TFile* fWmunu = new TFile( path.c_str(), "READ" );
	hWmunu = getHisto(fWmunu, hdir, "pT");
	setNormVals(10454., 1., 989886, dataLumi_ipb);
	NormToDataLumi( hWmunu, m_crossSection_pb, m_branchingRatio, m_nMCevents, m_dataLumi_pb);
	hWmunu->SetFillColor(colorAccumulate);
	hWmunu->SetLineColor(colorAccumulate);
	hWmunu->SetTitle("");
	leg_pT->AddEntry( hWmunu, channel.c_str(), "f");
	colorAccumulate+=colorOffset;
	
	/*
	path = dir + m_mcAnalysisSelector + "Control_ccmu15X.root";
	channel = "c #bar{c} #rightarrow #mu^{+}#mu^{-}X";
	TFile* fccmu15X = new TFile( path.c_str(), "READ" );
	hccmu15X = getHisto(fccmu15X, hdir, "pT");
	setNormVals(2.84e+4, 1., 1499257, dataLumi_ipb);
	NormToDataLumi( hccmu15X, m_crossSection_pb, m_branchingRatio, m_nMCevents, m_dataLumi_pb);
	hccmu15X->SetFillColor(colorAccumulate);
	hccmu15X->SetLineColor(colorAccumulate);
	hccmu15X->SetTitle("");
	leg_pT->AddEntry( hccmu15X, channel.c_str(), "f");
	colorAccumulate+=colorOffset;
	*/
	
	hMCpT->Add(hWW);
	hMCpT->Add(hTTbar);
	hMCpT->Add(hDYtautau);
	//hMCpT->Add(hbbmu15X);
	hMCpT->Add(hWmunu);
	//hMCpT->Add(hccmu15X);
	
	//////////////////////////////////////
	double mHatMin = 0.075; // TeV ///////
	//////////////////////////////////////
	
	/*
	lLowBound = new TLine(mHatMin,hMCpT->GetMinimum(),mHatMin,hMCpT->GetMaximum());
	lLowBound->SetLineColor(kBlack);
	lLowBound->SetLineWidth(3);
	*/
	
	pad_pT->cd();
	hZprime_mumu_SSM1000->Draw();
	hMCpT->Draw("SAMES");
	hDYmumu->Draw("SAMES");
	hTTbar->Draw("SAMES");
	hDYtautau->Draw("SAMES");
	hWW->Draw("SAMES");
	//hbbmu15X->Draw("SAMES");
	hWmunu->Draw("SAMES");
	//hccmu15X->Draw("SAMES");
	hData->Draw("e1x0SAMES");
	pvtxt->Draw("SAMES");
	leg_pT->Draw("SAMES");
	//lLowBound->Draw("SMAES");
	pad_pT->RedrawAxis();
	
	
	hRat = (TH1D*)hData->Clone("ratio");
	hRat->Reset();
	hRatUp = (TH1D*)hData->Clone("ratUp");
	hRatUp->Reset();
	hRatDwn = (TH1D*)hData->Clone("ratDwn");
	hRatDwn->Reset();
	
	double hpTmin = 0.025;
	
	ratio(hpTmin/*hRat->GetXaxis()->GetXmin()*/, hRat->GetXaxis()->GetXmax(), hData, hMCpT, hRat, hRatUp, hRatDwn);
	pad_pT_ratio->cd();
	drawRatio(hRat->GetXaxis()->GetXmin(), hRat->GetXaxis()->GetXmax(), hRat);
	pad_pT_ratio->RedrawAxis();
	
	
	cnv_pT->Print( hFile->GetName() );
	cnv_pT->SaveAs("pT.DATA.vs.MC.eps");
	cnv_pT->SaveAs("pT.DATA.vs.MC.C");
	
}
