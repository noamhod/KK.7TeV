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
	//return (TH1D*)f->Get( path.c_str() );
	return h;
}

void combinedGraphics::fixHisto(TH1D* h)
{
	h->SetTitle("");
	h->SetXTitle("#hat{m}_{#mu#mu} (MeV)");
	h->SetYTitle("Events");
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
	
	Color_t colorStart  = kOrange; //40;
	Color_t colorOffset = 1;
	Color_t colorAccumulate = colorStart;
	TMapSP2TH1D::iterator it;
	TMapds::iterator ii;
	string sname = "";
	
	leg_cutFlow_imass = new TLegend(0.7173913,0.3172043,0.8712375,0.8629032,NULL,"brNDC");
	leg_cutFlow_imass->SetFillColor(kWhite);
	leg_cutFlow_pT    = new TLegend(0.7173913,0.3172043,0.8712375,0.8629032,NULL,"brNDC");
	leg_cutFlow_pT->SetFillColor(kWhite);
	
	TPaveText* pvtxt = new TPaveText(0.1220736,0.7553763,0.2508361,0.8736559,"brNDC");
	pvtxt->SetFillColor(kWhite);
	TText* txt = pvtxt->AddText( channel.c_str() );
	
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
		string s;
		strm << (*hmap_cutFlow_imass)[sname]->GetBinWidth(1);
		strm >> s;
		string ytitle = "#frac{1}{#sigma}#times#frac{d#sigma}{d#hat{m}} (" + s + " MeV)^{-1}";
		double norm = (*hmap_cutFlow_imass)[sname]->GetEntries() * (*hmap_cutFlow_imass)[sname]->GetBinWidth(1);
		if(norm<=0)
		{
			cout << "ERROR: norm(" << sname << ") = 0" << endl;
			exit(-1);
		}
		(*hmap_cutFlow_imass)[sname]->Scale(1./norm);
		(*hmap_cutFlow_imass)[sname]->SetTitle("");
		(*hmap_cutFlow_imass)[sname]->SetXTitle("#hat{m}_{#mu#mu} (MeV)");
		(*hmap_cutFlow_imass)[sname]->SetYTitle( ytitle.c_str() );
		(*hmap_cutFlow_imass)[sname]->SetFillColor(colorAccumulate);
		(*hmap_cutFlow_imass)[sname]->SetLineColor(colorAccumulate);
		leg_cutFlow_imass->AddEntry( (*hmap_cutFlow_imass)[sname], str.c_str(), "f");
		if(bfirst)
		{
			//(*hmap_cutFlow_imass)[sname]->SetMinimum(5.e-1);
			(*hmap_cutFlow_imass)[sname]->SetMinimum(1.e-10);
			(*hmap_cutFlow_imass)[sname]->SetMaximum(1.e-3);
			(*hmap_cutFlow_imass)[sname]->Draw();
		}
		else (*hmap_cutFlow_imass)[sname]->Draw("SAMES");
		
		colorAccumulate += colorOffset;
		cout << "drawn " << sname << endl;
		
		bfirst = false;
	}
	cnv_cutFlow_imass->RedrawAxis();
	pvtxt->Draw("SMAES");
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
		string s;
		strm << (*hmap_cutFlow_pT)[sname]->GetBinWidth(1);
		strm >> s;
		string ytitle = "#frac{1}{#sigma}#times#frac{d#sigma}{dp_{T}^{#mu^{-}}} (" + s + " MeV)^{-1}";
		double norm = (*hmap_cutFlow_pT)[sname]->GetEntries() * (*hmap_cutFlow_pT)[sname]->GetBinWidth(1);
		if(norm<=0)
		{
			cout << "ERROR: norm(" << sname << ") = 0" << endl;
			exit(-1);
		}
		(*hmap_cutFlow_pT)[sname]->Scale(1./norm);
		(*hmap_cutFlow_pT)[sname]->SetTitle("");
		(*hmap_cutFlow_pT)[sname]->SetXTitle("p_{T}^{#mu^{-}} (MeV)");
		(*hmap_cutFlow_pT)[sname]->SetYTitle( ytitle.c_str() );
		(*hmap_cutFlow_pT)[sname]->SetFillColor(colorAccumulate);
		(*hmap_cutFlow_pT)[sname]->SetLineColor(colorAccumulate);
		leg_cutFlow_pT->AddEntry( (*hmap_cutFlow_pT)[sname], str.c_str(), "f");
		if(bfirst)
		{
			//(*hmap_cutFlow_pT)[sname]->SetMinimum(5.e-1);
			(*hmap_cutFlow_pT)[sname]->SetMinimum(1.e-9);
			(*hmap_cutFlow_pT)[sname]->SetMaximum(1.e-4);
			(*hmap_cutFlow_pT)[sname]->Draw();
		}
		else (*hmap_cutFlow_pT)[sname]->Draw("SAMES");
		colorAccumulate += colorOffset;
		cout << "drawn " << sname << endl;
		
		bfirst = false;
	}
	cnv_cutFlow_pT->RedrawAxis();
	pvtxt->Draw("SMAES");
	leg_cutFlow_pT->Draw("SAMES");
	cnv_cutFlow_pT->Update();
	//cnv_cutFlow_pT->Write();
}

void combinedGraphics::drawCutFlow()
{
	string dir = "/srv01/tau/hod/z0analysis/data/";
	string path = "";
	string channel = "";
	string hdir = "cutFlow";
	
	// main canvases
	cnv_main_cutFlow_imass = new TCanvas("cnv_main_cutFlow_imass", "cnv_main_cutFlow_imass", 1200, 800);
	cnv_main_cutFlow_imass->Divide(2,3);
	cnv_main_cutFlow_imass->SetFillColor(kWhite);
	cnv_main_cutFlow_imass->Draw();
	cnv_main_cutFlow_imass->cd();
	cnv_main_cutFlow_imass->Update();
	
	cnv_main_cutFlow_pT = new TCanvas("cnv_main_cutFlow_pT", "cnv_main_cutFlow_pT", 1200, 800);
	cnv_main_cutFlow_pT->Divide(2,3);
	cnv_main_cutFlow_pT->SetFillColor(kWhite);
	cnv_main_cutFlow_pT->Draw();
	cnv_main_cutFlow_pT->cd();
	cnv_main_cutFlow_pT->Update();
	
	
	// pads
	path = dir + "mcOfflineControl_Zmumu.root";
	channel = "Z #rightarrow #mu^{+}#mu^{-}";
	TFile* fZmumu = new TFile( path.c_str(), "READ" );
	getHistosMap(fZmumu, hdir, m_cutFlowOrdered, m_cutFlowTypeOrdered);
	drawNormHistosMap(channel, m_cutFlowOrdered, m_cutFlowTypeOrdered);
	cnv_main_cutFlow_imass->cd(1);
	cnv_cutFlow_imass->DrawClonePad();
	cnv_main_cutFlow_pT->cd(1);
	cnv_cutFlow_pT->DrawClonePad();
	
	path = dir + "mcOfflineControl_Wmunu.root";
	channel = "W #rightarrow #mu#nuX";
	TFile* fWmunu = new TFile( path.c_str(), "READ" );
	getHistosMap(fWmunu, hdir, m_cutFlowOrdered, m_cutFlowTypeOrdered);
	drawNormHistosMap(channel, m_cutFlowOrdered, m_cutFlowTypeOrdered);
	cnv_main_cutFlow_imass->cd(2);
	cnv_cutFlow_imass->DrawClonePad();
	cnv_main_cutFlow_pT->cd(2);
	cnv_cutFlow_pT->DrawClonePad();
	
	path = dir + "mcOfflineControl_Ztautau.root";
	channel = "Z #rightarrow #tau^{+}#tau^{-}";
	TFile* fZtautau = new TFile( path.c_str(), "READ" );
	getHistosMap(fZtautau, hdir, m_cutFlowOrdered, m_cutFlowTypeOrdered);
	drawNormHistosMap(channel, m_cutFlowOrdered, m_cutFlowTypeOrdered);
	cnv_main_cutFlow_imass->cd(3);
	cnv_cutFlow_imass->DrawClonePad();
	cnv_main_cutFlow_pT->cd(3);
	cnv_cutFlow_pT->DrawClonePad();
	
	path = dir + "mcOfflineControl_TTbar.root";
	channel = "t #bar{t} #rightarrow #mu^{+}#mu^{-}X";
	TFile* fTTbar = new TFile( path.c_str(), "READ" );
	getHistosMap(fTTbar, hdir, m_cutFlowOrdered, m_cutFlowTypeOrdered);
	drawNormHistosMap(channel, m_cutFlowOrdered, m_cutFlowTypeOrdered);
	cnv_main_cutFlow_imass->cd(4);
	cnv_cutFlow_imass->DrawClonePad();
	cnv_main_cutFlow_pT->cd(4);
	cnv_cutFlow_pT->DrawClonePad();
	
	path = dir + "mcOfflineControl_bbmuX15.root";
	channel = "b #bar{b} #rightarrow #mu^{+}#mu^{-}X";
	TFile* fbbmuX15 = new TFile( path.c_str(), "READ" );
	getHistosMap(fbbmuX15, hdir, m_cutFlowOrdered, m_cutFlowTypeOrdered);
	drawNormHistosMap(channel, m_cutFlowOrdered, m_cutFlowTypeOrdered);
	cnv_main_cutFlow_imass->cd(5);
	cnv_cutFlow_imass->DrawClonePad();
	cnv_main_cutFlow_pT->cd(5);
	cnv_cutFlow_pT->DrawClonePad();
	
	path = dir + "mcOfflineControl_ccmuX15.root";
	channel = "c #bar{c} #rightarrow #mu^{+}#mu^{-}X";
	TFile* fccmuX15 = new TFile( path.c_str(), "READ" );
	getHistosMap(fccmuX15, hdir, m_cutFlowOrdered, m_cutFlowTypeOrdered);
	drawNormHistosMap(channel, m_cutFlowOrdered, m_cutFlowTypeOrdered);
	cnv_main_cutFlow_imass->cd(6);
	cnv_cutFlow_imass->DrawClonePad();
	cnv_main_cutFlow_pT->cd(6);
	cnv_cutFlow_pT->DrawClonePad();
}
