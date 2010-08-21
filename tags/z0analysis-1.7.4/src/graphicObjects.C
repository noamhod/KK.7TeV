/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "graphicObjects.h"

graphicObjects::graphicObjects()
{
	ginitialize();
}

graphicObjects::~graphicObjects()
{
	gfinalize();
}

void graphicObjects::ginitialize()
{
	// canvases
	cnv_imass        = NULL;
	cnv_pT           = NULL;
	cnv_eta          = NULL;
	cnv_costh        = NULL;
	cnv_d0exPV       = NULL;
	cnv_z0exPV       = NULL;
	cnv_cosmicCosth  = NULL;
	cnv_xyVertex     = NULL;
	cnv_imassAllCuts = NULL;
	
	// histos
	h1_imass  = NULL;
	h1_pT     = NULL;
	h1_eta    = NULL;
	h1_costh  = NULL;
	h1_d0exPV = NULL;
	h1_z0exPV = NULL;
	h1_cosmicCosth = NULL;
	h2_xyVertex = NULL;
	h1_imassFinal = NULL;

	// cut flow canvases
	cnv_cutFlow_imass  = NULL;
	cnv_cutFlow_pT     = NULL;
	
	// cut flow legends
	leg_cutFlow_imass  = NULL;
	leg_cutFlow_pT     = NULL;
	
	// fit legends
	leg_imassFinal = NULL;
	
	// cut flow histos maps
	hmap_cutFlow_imass = NULL;
	hmap_cutFlow_pT = NULL;

	// canvas size
	canv_x = 600;
	canv_y = 400;

	// legend size
	leg_x1 = 0.765;
	leg_x2 = 0.919;
	leg_y1 = 0.376;
	leg_y2 = 0.922;

	imass_nbins = 40;
	imass_min   = 0.*d_toGeV;
	imass_max   = 200.*d_toGeV;
	
	pT_nbins    = 20;
	pT_min      = 0.*d_toGeV;
	pT_max      = 100.*d_toGeV;

	eta_nbins   = 25;
	eta_min     = -4.;
	eta_max     = 4.;

	costh_nbins = 25;
	costh_min   = -1.;
	costh_max   = 1.;

	d0exPV_nbins = 50;
	d0exPV_min   = -300.;
	d0exPV_max   = 300.;

	z0exPV_nbins = 50;
	z0exPV_min   = -300.;
	z0exPV_max   = 300.;

	cosmicCosth_nbins = 200;
	cosmicCosth_min   = -1.;
	cosmicCosth_max   = 1.;

	xyVertex_nbins = 40;
	xyVertex_min   = -200.;
	xyVertex_max   = 200.;
}

void graphicObjects::gfinalize()
{

}

void graphicObjects::setStyle()
{
	gROOT->ProcessLine(".x ../src/rootlogon_atlas.C");
	gROOT->SetStyle("ATLAS");
	gROOT->ForceStyle();
}

void graphicObjects::bookBareHistos(TDirectory* tdir)
{
	if(tdir!=NULL) tdir->cd();

	h1_d0exPV = new TH1D("d0exPV","d0exPV", d0exPV_nbins, d0exPV_min, d0exPV_max);
	h1_z0exPV = new TH1D("z0exPV","z0exPV", z0exPV_nbins, z0exPV_min, z0exPV_max);
	h1_cosmicCosth = new TH1D("cosThetaDimu","cosThetaDimu", cosmicCosth_nbins, cosmicCosth_min, cosmicCosth_max);
	h2_xyVertex = new TH2D("xyVertex","xyVertex",   xyVertex_nbins, xyVertex_min, xyVertex_max,
	xyVertex_nbins, xyVertex_min, xyVertex_max);
}

void graphicObjects::bookHistos(TDirectory* tdir)
{
	if(tdir!=NULL) tdir->cd();

	h1_imass = new TH1D("imass","imass", imass_nbins, imass_min, imass_max);
	h1_pT = new TH1D("pT","pT", pT_nbins, pT_min, pT_max);
	h1_eta = new TH1D("eta","eta", eta_nbins, eta_min, eta_max);
	h1_costh = new TH1D("costh","costh", costh_nbins, costh_min, costh_max);
}

void graphicObjects::drawBareHistos(TDirectory* tdir)
{
	if(tdir!=NULL) tdir->cd();
	
	cnv_d0exPV = new TCanvas("d0exPV","d0exPV",canv_x,canv_y);
	cnv_d0exPV->SetLogy();
	cnv_d0exPV->Draw();
	cnv_d0exPV->cd();
	h1_d0exPV->Draw();
	cnv_d0exPV->Update();
        cnv_d0exPV->Write();

	cnv_z0exPV = new TCanvas("z0exPV","z0exPV",canv_x,canv_y);
	cnv_z0exPV->SetLogy();
	cnv_z0exPV->Draw();
	cnv_z0exPV->cd();
	h1_z0exPV->Draw();
	cnv_z0exPV->Update();
        cnv_z0exPV->Write();

	cnv_cosmicCosth = new TCanvas("cosThetaDimu","cosThetaDimu",canv_x,canv_y);
	cnv_cosmicCosth->Draw();
	cnv_cosmicCosth->cd();
	h1_cosmicCosth->Draw();
	cnv_cosmicCosth->Update();
        cnv_cosmicCosth->Write();

	cnv_xyVertex = new TCanvas("xyVertex","xyVertex",canv_x,canv_y);
	cnv_xyVertex->Draw();
	cnv_xyVertex->cd();
	h2_xyVertex->Draw("BOX");
	cnv_xyVertex->Update();
        cnv_xyVertex->Write();
}

void graphicObjects::drawHistos(TDirectory* tdir)
{
	if(tdir!=NULL) tdir->cd();

	cnv_imass = new TCanvas("imass","imass",canv_x,canv_y);
	cnv_imass->SetLogy();
	cnv_imass->Draw();
	cnv_imass->cd();
	h1_imass->Draw();
	cnv_imass->Update();
        cnv_imass->Write();

	cnv_pT = new TCanvas("pT","pT",canv_x,canv_y);
	cnv_pT->SetLogy();
	cnv_pT->Draw();
	cnv_pT->cd();
	h1_pT->Draw();
	cnv_pT->Update();
        cnv_pT->Write();

	cnv_eta = new TCanvas("eta","eta",canv_x,canv_y);
	cnv_eta->Draw();
	cnv_eta->cd();
	h1_eta->Draw();
	cnv_eta->Update();
        cnv_eta->Write();

	cnv_costh = new TCanvas("costh","costh",canv_x,canv_y);
	cnv_costh->Draw();
	cnv_costh->cd();
	h1_costh->Draw();
	cnv_costh->Update();
        cnv_costh->Write();
}

void graphicObjects::bookHistosMap(TMapsd* cutFlowMap, TMapds* cutFlowOrdered, TDirectory* tdir)
{
	if(cutFlowMap==NULL || tdir==NULL) return;

	tdir->cd();

	hmap_cutFlow_imass = new TMapSP2TH1D();
	hmap_cutFlow_pT    = new TMapSP2TH1D();

	for(TMapds::iterator it=cutFlowOrdered->begin() ; it!=cutFlowOrdered->end() ; ++it)
	{
		double snumber = it->first; 

		string sname = "";

		// invariant mass cut flow histos
		sname = "imass." + it->second;
		hmap_cutFlow_imass->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), imass_nbins, imass_min, imass_max) ) );
		cout << "(" << snumber << ") booked " << sname << endl;

		// pT cut flow histos
		sname = "pT." + it->second;
		hmap_cutFlow_pT->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), pT_nbins, pT_min, pT_max) ) );
		cout << "(" << snumber << ") booked " << sname << endl;
	}
}

void graphicObjects::drawHistosMap(TMapsd* cutFlowMap, TMapds* cutFlowOrdered, TDirectory* tdir)
{
	if(cutFlowMap==NULL || tdir==NULL) return;
	
	tdir->cd();

	Color_t colorStart  = 40;
	Color_t colorOffset = 1;
	Color_t colorAccumulate = colorStart;
	TMapSP2TH1D::iterator it;
	TMapds::iterator ii;
	string sname = "";

	leg_cutFlow_imass = new TLegend(leg_x1, leg_y1, leg_x2, leg_y2);
	leg_cutFlow_pT    = new TLegend(leg_x1, leg_y1, leg_x2, leg_y2);

	cnv_cutFlow_imass = new TCanvas("imass.cutFlow","imass.cutFlow",canv_x,canv_y);
	cnv_cutFlow_imass->SetLogy();
	cnv_cutFlow_imass->Draw();
	cnv_cutFlow_imass->cd();
	colorAccumulate = colorStart;
	for(TMapds::iterator ii=cutFlowOrdered->begin() ; ii!=cutFlowOrdered->end() ; ++ii)
	{
		//double num = ii->first;  // irrelevant
		string str = ii->second; 
		it=hmap_cutFlow_imass->find("imass."+str);
		string sname = it->first;
		(*hmap_cutFlow_imass)[sname]->SetFillColor(colorAccumulate);
		(*hmap_cutFlow_imass)[sname]->SetLineColor(colorAccumulate);
		leg_cutFlow_imass->AddEntry( (*hmap_cutFlow_imass)[sname], str.c_str(), "f");
		if(sname=="imass.oppositeCharcge")
		{
			(*hmap_cutFlow_imass)[sname]->SetMinimum(5.e-1);
			(*hmap_cutFlow_imass)[sname]->Draw();
		}
		else (*hmap_cutFlow_imass)[sname]->Draw("SAMES");
		colorAccumulate += colorOffset;
		cout << "drawn " << sname << endl;
	}
	leg_cutFlow_imass->Draw("SAMES");
	cnv_cutFlow_imass->Update();
	cnv_cutFlow_imass->Write();

	cnv_cutFlow_pT = new TCanvas("pT.cutFlow","pT.cutFlow",canv_x,canv_y);
	cnv_cutFlow_pT->SetLogy();
	cnv_cutFlow_pT->Draw();
	cnv_cutFlow_pT->cd();
	colorAccumulate = colorStart;
	for(TMapds::iterator ii=cutFlowOrdered->begin() ; ii!=cutFlowOrdered->end() ; ++ii)
	{
		//double num = ii->first;  // irrelevant
		string str = ii->second;
		it=hmap_cutFlow_pT->find("pT."+str);
		string sname = it->first;
		(*hmap_cutFlow_pT)[sname]->SetFillColor(colorAccumulate);
		(*hmap_cutFlow_pT)[sname]->SetLineColor(colorAccumulate);
		leg_cutFlow_pT->AddEntry( (*hmap_cutFlow_pT)[sname], str.c_str(), "f");
		if(sname=="pT.oppositeCharcge")
		{
			(*hmap_cutFlow_pT)[sname]->SetMinimum(5.e-1);
			(*hmap_cutFlow_pT)[sname]->Draw();
		}
		else (*hmap_cutFlow_pT)[sname]->Draw("SAMES");
		colorAccumulate += colorOffset;
		cout << "drawn " << sname << endl;
	}
	leg_cutFlow_pT->Draw("SAMES");
	cnv_cutFlow_pT->Update();
	cnv_cutFlow_pT->Write();
}

void graphicObjects::bookFitHistos(TDirectory* tdir)
{
	if(tdir!=NULL) tdir->cd();

	h1_imassFinal = new TH1D("imassFinal","imassFinal", imass_nbins, imass_min, imass_max);
}

void graphicObjects::drawFitHistos(TDirectory* tdir, TF1* fGuess, TF1* fFitted)
{
	if(tdir!=NULL) tdir->cd();
	
	leg_imassFinal = new TLegend(leg_x1, leg_y1*2., leg_x2, leg_y2);
	
	cnv_imassAllCuts = new TCanvas("imassFinal","imassFinal",canv_x,canv_y);
	cnv_imassAllCuts->Draw();
	cnv_imassAllCuts->cd();
	
	h1_imassFinal->SetMarkerStyle(20);
	h1_imassFinal->Draw("e1x0");
	
	fGuess->SetLineStyle(1);
	fGuess->SetLineColor(kRed);
	fGuess->SetLineWidth(2);
	//fGuess->Draw("sames");
	
	fFitted->SetLineStyle(1);
	fFitted->SetLineColor(kBlue);
	fFitted->SetLineWidth(2);
	fFitted->Draw("sames");
	
	leg_imassFinal->AddEntry( h1_imassFinal, "Data", "lep");
	//leg_imassFinal->AddEntry( fGuess, "Guess", "L");
	leg_imassFinal->AddEntry( fFitted, "fit", "L");
	leg_imassFinal->Draw("sames");
	
	cnv_imassAllCuts->Update();
	cnv_imassAllCuts->Write();
}

