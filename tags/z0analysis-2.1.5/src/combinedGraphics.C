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

combinedGraphics::combinedGraphics(cutFlowHandler* cutFlowHandler)
{
	m_cutFlowHandler = cutFlowHandler;
	
	m_cutFlowMapSVD  = m_cutFlowHandler->getCutFlowMapSVDPtr();
	m_cutFlowOrdered = m_cutFlowHandler->getCutFlowOrderedMapPtr();
	m_cutFlowTypeOrdered = m_cutFlowHandler->getCutFlowTypeOrderedMapPtr();
	m_cutFlowNumbers = m_cutFlowHandler->getCutFlowNumbersMapPtr();
	
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
	dataLumi_ipb = 6.865632; ////////////////////////
	/////////////////////////////////////////////////
}

combinedGraphics::~combinedGraphics()
{

}


TCanvas* combinedGraphics::getCanvas(TFile* f, string dir, string cname)
{
	string path = dir + "/" +cname;
	TCanvas* cnv_cutFlow_imass = (TCanvas*)f->Get( path.c_str() );
	return cnv_cutFlow_imass;
}

TH1D* combinedGraphics::getHisto(TFile* f, string dir, string hname)
{
	string path = dir + "/" +hname;
	TH1D* h = (TH1D*)f->Get( path.c_str() );
	return h;
}

void combinedGraphics::fixHisto(TH1D* h)
{
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

void combinedGraphics::getHistosMap(TFile* f, string dir, TMapds* cutFlowOrdered, TMapds* cutFlowTypeOrdered)
{
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
	/*
	gStyle->SetAxisColor(1, "XYZ");
	gStyle->SetStripDecimals(kTRUE);
	gStyle->SetTickLength(0.03, "XYZ");
	gStyle->SetNdivisions(510, "XYZ");
	*/
	
	gStyle->SetOptStat(0);
	gStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
	gStyle->SetPadTickY(1);
	
	gStyle->SetFillColor(10);
	gStyle->SetFrameFillColor(10);
	//gStyle->SetFrameFillStyle(0);
	//gStyle->SetFillStyle(0);
	gStyle->SetCanvasColor(10);
	gStyle->SetPadColor(10);
	gStyle->SetTitleFillColor(0);
	//gStyle->SetStatColor(10);
	

	bool bfirst;
	
	Color_t colorStart  = 100;//kOrange; //40;
	Color_t colorOffset = -10;//1;
	Color_t colorAccumulate = colorStart;
	TMapSP2TH1D::iterator it;
	TMapds::iterator ii;
	string sname = "";
	
	leg_cutFlow_imass = new TLegend(0.7173913,0.3172043,0.8712375,0.8629032,NULL,"brNDC");
	leg_cutFlow_imass->SetFillColor(kWhite);
	leg_cutFlow_pT    = new TLegend(0.7173913,0.3172043,0.8712375,0.8629032,NULL,"brNDC");
	leg_cutFlow_pT->SetFillColor(kWhite);
	
	TPaveText* pvtxt = new TPaveText(0.5365803,0.7590674,0.6637402,0.8748209,"brNDC");
	pvtxt->SetFillColor(kWhite);
	TText* txt = pvtxt->AddText( channel.c_str() );
	
	stringstream strm;
	string L;
	string lumilabel = "";
	strm << m_dataLumi_pb;
	strm >> L;
	lumilabel = "#intLdt~" + L + " pb^{-1}";
	TPaveText* pvtxt1 = new TPaveText(0.5365803,0.5482306,0.7142559,0.7425311,"brNDC");
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
		strm << (*hmap_cutFlow_imass)[sname]->GetBinWidth(1);
		strm >> s1;
		strm.clear();
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
			//(*hmap_cutFlow_imass)[sname]->SetMinimum(5.e-1);
			(*hmap_cutFlow_imass)[sname]->SetMinimum(1.e-2);
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
		strm << (*hmap_cutFlow_pT)[sname]->GetBinWidth(1);
		strm >> s1;
		strm.clear();
		strm << (*hmap_cutFlow_pT)[sname]->GetBinWidth( (*hmap_cutFlow_pT)[sname]->GetNbinsX() );
		strm >> s2;
		string ytitle = "#frac{dN}{dp_{T}^{#mu^{-}}} (" + s1 + "#rightarrow" + s2 + " TeV)^{-1}";
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
		(*hmap_cutFlow_pT)[sname]->SetXTitle("p_{T}^{#mu^{-}} (TeV)");
		(*hmap_cutFlow_pT)[sname]->SetYTitle( ytitle.c_str() );
		(*hmap_cutFlow_pT)[sname]->SetFillColor(colorAccumulate);
		(*hmap_cutFlow_pT)[sname]->SetLineColor(colorAccumulate);
		leg_cutFlow_pT->AddEntry( (*hmap_cutFlow_pT)[sname], str.c_str(), "f");
		if(bfirst)
		{
			(*hmap_cutFlow_pT)[sname]->SetMinimum(1.e-2);
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
	string dir = "/srv01/tau/hod/z0analysis/data/";
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
	path = dir + "mcOfflineControl_Zmumu.root";
	channel = "Z #rightarrow #mu^{+}#mu^{-}";
	setNormVals(989., 1., 299811, dataLumi_ipb);
	TFile* fZmumu = new TFile( path.c_str(), "READ" );
	getHistosMap(fZmumu, hdir, m_cutFlowOrdered, m_cutFlowTypeOrdered);
	drawNormHistosMap(channel, m_cutFlowOrdered, m_cutFlowTypeOrdered);
	cnv_MC_cutFlow_imass->cd(1);
	cnv_cutFlow_imass->DrawClonePad();
	cnv_MC_cutFlow_pT->cd(1);
	cnv_cutFlow_pT->DrawClonePad();
	
	path = dir + "mcOfflineControl_Wmunu.root";
	channel = "W #rightarrow #mu#nuX";
	setNormVals(10454., 1., 989886, dataLumi_ipb);
	TFile* fWmunu = new TFile( path.c_str(), "READ" );
	getHistosMap(fWmunu, hdir, m_cutFlowOrdered, m_cutFlowTypeOrdered);
	drawNormHistosMap(channel, m_cutFlowOrdered, m_cutFlowTypeOrdered);
	cnv_MC_cutFlow_imass->cd(2);
	cnv_cutFlow_imass->DrawClonePad();
	cnv_MC_cutFlow_pT->cd(2);
	cnv_cutFlow_pT->DrawClonePad();
	
	path = dir + "mcOfflineControl_Ztautau.root";
	channel = "Z #rightarrow #tau^{+}#tau^{-}";
	setNormVals(989., 1., 1998598, dataLumi_ipb);
	TFile* fZtautau = new TFile( path.c_str(), "READ" );
	getHistosMap(fZtautau, hdir, m_cutFlowOrdered, m_cutFlowTypeOrdered);
	drawNormHistosMap(channel, m_cutFlowOrdered, m_cutFlowTypeOrdered);
	cnv_MC_cutFlow_imass->cd(3);
	cnv_cutFlow_imass->DrawClonePad();
	cnv_MC_cutFlow_pT->cd(3);
	cnv_cutFlow_pT->DrawClonePad();
	
	path = dir + "mcOfflineControl_TTbar.root";
	channel = "t #bar{t} #rightarrow #mu^{+}#mu^{-}X";
	setNormVals(161., 1., 199838, dataLumi_ipb);
	TFile* fTTbar = new TFile( path.c_str(), "READ" );
	getHistosMap(fTTbar, hdir, m_cutFlowOrdered, m_cutFlowTypeOrdered);
	drawNormHistosMap(channel, m_cutFlowOrdered, m_cutFlowTypeOrdered);
	cnv_MC_cutFlow_imass->cd(4);
	cnv_cutFlow_imass->DrawClonePad();
	cnv_MC_cutFlow_pT->cd(4);
	cnv_cutFlow_pT->DrawClonePad();
	
	path = dir + "mcOfflineControl_bbmuX15.root";
	channel = "b #bar{b} #rightarrow #mu^{+}#mu^{-}X";
	setNormVals(7.39e+4, 1., 4388911, dataLumi_ipb);
	TFile* fbbmuX15 = new TFile( path.c_str(), "READ" );
	getHistosMap(fbbmuX15, hdir, m_cutFlowOrdered, m_cutFlowTypeOrdered);
	drawNormHistosMap(channel, m_cutFlowOrdered, m_cutFlowTypeOrdered);
	cnv_MC_cutFlow_imass->cd(5);
	cnv_cutFlow_imass->DrawClonePad();
	cnv_MC_cutFlow_pT->cd(5);
	cnv_cutFlow_pT->DrawClonePad();
	
	path = dir + "mcOfflineControl_ccmuX15.root";
	channel = "c #bar{c} #rightarrow #mu^{+}#mu^{-}X";
	setNormVals(2.84e+4, 1., 1499257, dataLumi_ipb);
	TFile* fccmuX15 = new TFile( path.c_str(), "READ" );
	getHistosMap(fccmuX15, hdir, m_cutFlowOrdered, m_cutFlowTypeOrdered);
	drawNormHistosMap(channel, m_cutFlowOrdered, m_cutFlowTypeOrdered);
	cnv_MC_cutFlow_imass->cd(6);
	cnv_cutFlow_imass->DrawClonePad();
	cnv_MC_cutFlow_pT->cd(6);
	cnv_cutFlow_pT->DrawClonePad();
}


void combinedGraphics::drawDataCutFlow()
{
	string dir = "/srv01/tau/hod/z0analysis/data/";
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
	
	
	path = dir + "offlineControl.root";
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


void combinedGraphics::drawimass()
{
	string dir = "/srv01/tau/hod/z0analysis/data/";
	string path = "";
	string channel = "";
	string hdir = "allCuts";
	
	
	/*
	gStyle->SetAxisColor(1, "XYZ");
	gStyle->SetStripDecimals(kTRUE);
	gStyle->SetTickLength(0.03, "XYZ");
	gStyle->SetNdivisions(510, "XYZ");
	*/
	
	gStyle->SetOptStat(0);
	gStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
	gStyle->SetPadTickY(1);
	
	gStyle->SetFillColor(10);
	gStyle->SetFrameFillColor(10);
	//gStyle->SetFrameFillStyle(0);
	//gStyle->SetFillStyle(0);
	gStyle->SetCanvasColor(10);
	gStyle->SetPadColor(10);
	gStyle->SetTitleFillColor(0);
	//gStyle->SetStatColor(10);
	
	
	leg_imass = new TLegend(0.7173913,0.3172043,0.8712375,0.8629032,NULL,"brNDC");
	leg_imass->SetFillColor(kWhite);
	
	m_dataLumi_pb = dataLumi_ipb;
	
	stringstream strm;
	string L;
	string lumilabel = "";
	strm << m_dataLumi_pb;
	strm >> L;
	lumilabel = "#intLdt~" + L + " pb^{-1}";
	TPaveText* pvtxt = new TPaveText(0.5365803,0.5482306,0.7142559,0.7425311,"brNDC");
	pvtxt->SetFillColor(kWhite);
	TText* txt = pvtxt->AddText( lumilabel.c_str() );
	
	
	// main canvases
	cnv_imass = new TCanvas("cnv_imass", "cnv_imass", 1200, 800);
	cnv_imass->SetFillColor(kWhite);
	cnv_imass->SetLogx();
	cnv_imass->SetLogy();
	cnv_imass->Draw();
	cnv_imass->cd();
	cnv_imass->Update();
	
	
	Color_t colorStart  = 100;//kOrange; //40;
	Color_t colorOffset = -10;//1;
	Color_t colorAccumulate = colorStart;
	

	path = dir + "offlineControl.root";
	TFile* fdata = new TFile( path.c_str(), "READ" );
	hData = getHisto(fdata, hdir, "imass");
	leg_imass->AddEntry( hData, "Data", "lep");
	
	
	
	path = dir + "mcOfflineControl_Zmumu.root"; // just to get the first histo (Z->mumu)
	channel = "SM(sig+bkg)";
	TFile* fFirstHist = new TFile( path.c_str(), "READ" );
	hMCimass = getHisto(fFirstHist, hdir, "imass");
	setNormVals(989., 1., 299811, dataLumi_ipb);
	NormToDataLumi( hMCimass, m_crossSection_pb, m_branchingRatio, m_nMCevents, m_dataLumi_pb);
	hMCimass->SetFillColor(colorAccumulate);
	hMCimass->SetLineColor(colorAccumulate);
	hMCimass->SetTitle("");
	hMCimass->SetMinimum(1.e-2);
	hMCimass->SetMaximum(1.e+4);
	hMCimass->SetXTitle("#hat{m}_{#mu#mu} (TeV)");
	hMCimass->SetYTitle("Events");
	hMCimass->SetTitle("");
	leg_imass->AddEntry( hMCimass, channel.c_str(), "f");
	colorAccumulate+=colorOffset;
	
	
	path = dir + "mcOfflineControl_Zmumu.root";
	channel = "Z #rightarrow #mu^{+}#mu^{-}";
	TFile* fZmumu = new TFile( path.c_str(), "READ" );
	hZmumu = getHisto(fZmumu, hdir, "imass");
	setNormVals(989., 1., 299811, dataLumi_ipb);
	NormToDataLumi( hZmumu, m_crossSection_pb, m_branchingRatio, m_nMCevents, m_dataLumi_pb);
	hZmumu->SetFillColor(colorAccumulate);
	hZmumu->SetLineColor(colorAccumulate);
	hZmumu->SetTitle("");
	leg_imass->AddEntry( hZmumu, channel.c_str(), "f");
	colorAccumulate+=colorOffset;
	
	
	path = dir + "mcOfflineControl_TTbar.root";
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
	
	path = dir + "mcOfflineControl_Ztautau.root";
	channel = "Z #rightarrow #tau^{+}#tau^{-}";
	TFile* fZtautau = new TFile( path.c_str(), "READ" );
	hZtautau = getHisto(fZtautau, hdir, "imass");
	setNormVals(989., 1., 1998598, dataLumi_ipb);
	NormToDataLumi( hZtautau, m_crossSection_pb, m_branchingRatio, m_nMCevents, m_dataLumi_pb);
	hZtautau->SetFillColor(colorAccumulate);
	hZtautau->SetLineColor(colorAccumulate);
	hZtautau->SetTitle("");
	leg_imass->AddEntry( hZtautau, channel.c_str(), "f");
	colorAccumulate+=colorOffset;
	
	path = dir + "mcOfflineControl_bbmuX15.root";
	channel = "b #bar{b} #rightarrow #mu^{+}#mu^{-}X";
	TFile* fbbmuX15 = new TFile( path.c_str(), "READ" );
	hbbmuX15 = getHisto(fbbmuX15, hdir, "imass");
	setNormVals(7.39e+4, 1., 4388911, dataLumi_ipb);
	NormToDataLumi( hbbmuX15, m_crossSection_pb, m_branchingRatio, m_nMCevents, m_dataLumi_pb);
	hbbmuX15->SetFillColor(colorAccumulate);
	hbbmuX15->SetLineColor(colorAccumulate);
	hbbmuX15->SetTitle("");
	leg_imass->AddEntry( hbbmuX15, channel.c_str(), "f");
	colorAccumulate+=colorOffset;
	
	path = dir + "mcOfflineControl_Wmunu.root";
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
	
	path = dir + "mcOfflineControl_ccmuX15.root";
	channel = "c #bar{c} #rightarrow #mu^{+}#mu^{-}X";
	TFile* fccmuX15 = new TFile( path.c_str(), "READ" );
	hccmuX15 = getHisto(fccmuX15, hdir, "imass");
	setNormVals(2.84e+4, 1., 1499257, dataLumi_ipb);
	NormToDataLumi( hccmuX15, m_crossSection_pb, m_branchingRatio, m_nMCevents, m_dataLumi_pb);
	hccmuX15->SetFillColor(colorAccumulate);
	hccmuX15->SetLineColor(colorAccumulate);
	hccmuX15->SetTitle("");
	leg_imass->AddEntry( hccmuX15, channel.c_str(), "f");
	colorAccumulate+=colorOffset;
	
	
	hMCimass->Add(hTTbar);
	hMCimass->Add(hZtautau);
	hMCimass->Add(hbbmuX15);
	hMCimass->Add(hWmunu);
	hMCimass->Add(hccmuX15);
	
	
	hMCimass->Draw();
	hZmumu->Draw("SAMES");
	hTTbar->Draw("SAMES");
	hZtautau->Draw("SAMES");
	hbbmuX15->Draw("SAMES");
	hWmunu->Draw("SAMES");
	hccmuX15->Draw("SAMES");
	hData->Draw("e1x0SAMES");
	pvtxt->Draw("SAMES");
	leg_imass->Draw("SAMES");
}


void combinedGraphics::drawpT()
{
	string dir = "/srv01/tau/hod/z0analysis/data/";
	string path = "";
	string channel = "";
	string hdir = "allCuts";
	
	
	/*
	gStyle->SetAxisColor(1, "XYZ");
	gStyle->SetStripDecimals(kTRUE);
	gStyle->SetTickLength(0.03, "XYZ");
	gStyle->SetNdivisions(510, "XYZ");
	*/
	
	gStyle->SetOptStat(0);
	gStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
	gStyle->SetPadTickY(1);
	
	gStyle->SetFillColor(10);
	gStyle->SetFrameFillColor(10);
	//gStyle->SetFrameFillStyle(0);
	//gStyle->SetFillStyle(0);
	gStyle->SetCanvasColor(10);
	gStyle->SetPadColor(10);
	gStyle->SetTitleFillColor(0);
	//gStyle->SetStatColor(10);
	
	
	leg_pT = new TLegend(0.7173913,0.3172043,0.8712375,0.8629032,NULL,"brNDC");
	leg_pT->SetFillColor(kWhite);
	
	m_dataLumi_pb = dataLumi_ipb;
	
	stringstream strm;
	string L;
	string lumilabel = "";
	strm << m_dataLumi_pb;
	strm >> L;
	lumilabel = "#intLdt~" + L + " pb^{-1}";
	TPaveText* pvtxt = new TPaveText(0.5365803,0.5482306,0.7142559,0.7425311,"brNDC");
	pvtxt->SetFillColor(kWhite);
	TText* txt = pvtxt->AddText( lumilabel.c_str() );
	
	
	// main canvases
	cnv_pT = new TCanvas("cnv_pT", "cnv_pT", 1200, 800);
	cnv_pT->SetFillColor(kWhite);
	cnv_pT->SetLogx();
	cnv_pT->SetLogy();
	cnv_pT->Draw();
	cnv_pT->cd();
	cnv_pT->Update();
	
	
	Color_t colorStart  = 100;//kOrange; //40;
	Color_t colorOffset = -10;//1;
	Color_t colorAccumulate = colorStart;
	

	path = dir + "offlineControl.root";
	TFile* fdata = new TFile( path.c_str(), "READ" );
	hData = getHisto(fdata, hdir, "pT");
	leg_pT->AddEntry( hData, "Data", "lep");
	
	
	
	path = dir + "mcOfflineControl_Zmumu.root"; // just to get the first histo (Z->mumu)
	channel = "SM(sig+bkg)";
	TFile* fFirstHist = new TFile( path.c_str(), "READ" );
	hMCpT = getHisto(fFirstHist, hdir, "pT");
	setNormVals(989., 1., 299811, dataLumi_ipb);
	NormToDataLumi( hMCpT, m_crossSection_pb, m_branchingRatio, m_nMCevents, m_dataLumi_pb);
	hMCpT->SetFillColor(colorAccumulate);
	hMCpT->SetLineColor(colorAccumulate);
	hMCpT->SetTitle("");
	hMCpT->SetMinimum(1.e-2);
	hMCpT->SetMaximum(1.e+4);
	hMCpT->SetXTitle("p_{T}^{#mu^{-}} (TeV)");
	hMCpT->SetYTitle("Events");
	hMCpT->SetTitle("");
	leg_pT->AddEntry( hMCpT, channel.c_str(), "f");
	colorAccumulate+=colorOffset;
	
	
	path = dir + "mcOfflineControl_Zmumu.root";
	channel = "Z #rightarrow #mu^{+}#mu^{-}";
	TFile* fZmumu = new TFile( path.c_str(), "READ" );
	hZmumu = getHisto(fZmumu, hdir, "pT");
	setNormVals(989., 1., 299811, dataLumi_ipb);
	NormToDataLumi( hZmumu, m_crossSection_pb, m_branchingRatio, m_nMCevents, m_dataLumi_pb);
	hZmumu->SetFillColor(colorAccumulate);
	hZmumu->SetLineColor(colorAccumulate);
	hZmumu->SetTitle("");
	leg_pT->AddEntry( hZmumu, channel.c_str(), "f");
	colorAccumulate+=colorOffset;
	
	
	path = dir + "mcOfflineControl_TTbar.root";
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
	
	path = dir + "mcOfflineControl_Ztautau.root";
	channel = "Z #rightarrow #tau^{+}#tau^{-}";
	TFile* fZtautau = new TFile( path.c_str(), "READ" );
	hZtautau = getHisto(fZtautau, hdir, "pT");
	setNormVals(989., 1., 1998598, dataLumi_ipb);
	NormToDataLumi( hZtautau, m_crossSection_pb, m_branchingRatio, m_nMCevents, m_dataLumi_pb);
	hZtautau->SetFillColor(colorAccumulate);
	hZtautau->SetLineColor(colorAccumulate);
	hZtautau->SetTitle("");
	leg_pT->AddEntry( hZtautau, channel.c_str(), "f");
	colorAccumulate+=colorOffset;
	
	path = dir + "mcOfflineControl_bbmuX15.root";
	channel = "b #bar{b} #rightarrow #mu^{+}#mu^{-}X";
	TFile* fbbmuX15 = new TFile( path.c_str(), "READ" );
	hbbmuX15 = getHisto(fbbmuX15, hdir, "pT");
	setNormVals(7.39e+4, 1., 4388911, dataLumi_ipb);
	NormToDataLumi( hbbmuX15, m_crossSection_pb, m_branchingRatio, m_nMCevents, m_dataLumi_pb);
	hbbmuX15->SetFillColor(colorAccumulate);
	hbbmuX15->SetLineColor(colorAccumulate);
	hbbmuX15->SetTitle("");
	leg_pT->AddEntry( hbbmuX15, channel.c_str(), "f");
	colorAccumulate+=colorOffset;
	
	path = dir + "mcOfflineControl_Wmunu.root";
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
	
	path = dir + "mcOfflineControl_ccmuX15.root";
	channel = "c #bar{c} #rightarrow #mu^{+}#mu^{-}X";
	TFile* fccmuX15 = new TFile( path.c_str(), "READ" );
	hccmuX15 = getHisto(fccmuX15, hdir, "pT");
	setNormVals(2.84e+4, 1., 1499257, dataLumi_ipb);
	NormToDataLumi( hccmuX15, m_crossSection_pb, m_branchingRatio, m_nMCevents, m_dataLumi_pb);
	hccmuX15->SetFillColor(colorAccumulate);
	hccmuX15->SetLineColor(colorAccumulate);
	hccmuX15->SetTitle("");
	leg_pT->AddEntry( hccmuX15, channel.c_str(), "f");
	colorAccumulate+=colorOffset;
	
	
	hMCpT->Add(hTTbar);
	hMCpT->Add(hZtautau);
	hMCpT->Add(hbbmuX15);
	hMCpT->Add(hWmunu);
	hMCpT->Add(hccmuX15);
	
	
	hMCpT->Draw();
	hZmumu->Draw("SAMES");
	hTTbar->Draw("SAMES");
	hZtautau->Draw("SAMES");
	hbbmuX15->Draw("SAMES");
	hWmunu->Draw("SAMES");
	hccmuX15->Draw("SAMES");
	hData->Draw("e1x0SAMES");
	pvtxt->Draw("SAMES");
	leg_pT->Draw("SAMES");
}
