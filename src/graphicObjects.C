/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "graphicObjects.h"

graphicObjects::graphicObjects()
{

}

graphicObjects::~graphicObjects()
{

}

void graphicObjects::setCutFlowMapSVDPtr(TMapsvd* cutFlowMapSVD)
{
	cut_cutFlowMapSVD = cutFlowMapSVD;
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
	cnv_imassFit     = NULL;
	cnv_ipTdiff      = NULL;
	cnv_etaSum       = NULL;
	
	// pads
	pad_pT                 = NULL;
	pad_eta                = NULL;
	pad_pT_muplus          = NULL;
	pad_eta_muplus         = NULL;
	pad_cosmicCosth        = NULL;
	pad_cosmicCosthAllCuts = NULL;
	
	// histos
	h1_imass              = NULL;
	h1_pT                 = NULL;
	h1_pT_muplus          = NULL;
	h1_eta                = NULL;
	h1_eta_muplus         = NULL;
	h1_costh              = NULL;
	h1_d0exPV             = NULL;
	h1_z0exPV             = NULL;
	h1_cosmicCosth        = NULL;
	h1_cosmicCosthAllCuts = NULL;
	h2_xyVertex           = NULL;
	h1_imassFit           = NULL;
	h1_ipTdiff            = NULL;
	h1_etaSum             = NULL;

	// cut flow canvases
	cnv_cutFlow_imass  = NULL;
	cnv_cutFlow_pT     = NULL;
	
	// cut flow legends
	leg_cutFlow_imass  = NULL;
	leg_cutFlow_pT     = NULL;
	
	// fit legends
	leg_imassFit = NULL;
	leg_ipTdiff  = NULL;
	
	// cut flow histos maps
	hmap_cutFlow_imass = NULL;
	hmap_cutFlow_pT    = NULL;

	// canvas size
	canv_x = 602;
	canv_y = 400;

	// legend size
	leg_x1 = 0.765;
	leg_x2 = 0.919;
	leg_y1 = 0.376;
	leg_y2 = 0.922;

	// get the cut value from the cutFlow map
	string pTcutNmae;
	TMapsvd::iterator it1=cut_cutFlowMapSVD->find("pT");
	TMapsvd::iterator it2=cut_cutFlowMapSVD->find("pT_use_qOp_and_theta");
	TMapsvd::iterator it3=cut_cutFlowMapSVD->find("pTandEtaTight");
	TMapsvd::iterator itEnd=cut_cutFlowMapSVD->end();
	if     ( it1 != itEnd ) pTcutNmae = "pT";
	else if( it2 != itEnd ) pTcutNmae = "pT_use_qOp_and_theta";
	else if( it3 != itEnd ) pTcutNmae = "pTandEtaTight";
	else 
	{
		cout << "ERROR: in graphicObjects::ginitialize(): pT cut value was not found, exitting now" << endl;
		exit(-1);
	}
	double pT_cut    = (*cut_cutFlowMapSVD)[pTcutNmae][0];
	double imass_cut = (*cut_cutFlowMapSVD)["imass"][0];
	
	
	imass_nbins   = 100;
	imass_min     = 10.*GeV2TeV;
	imass_min_cut = imass_cut;
	imass_max     = 2010.*GeV2TeV;
	imass_max_cut = 2000.*GeV2TeV+imass_cut;
	
	imass_fit_nbins = 40;
	imass_fit_min   = 0.*GeV2TeV;
	imass_fit_max   = 200.*GeV2TeV;
	
	pT_nbins    = 100;
	pT_min      = 5.*GeV2TeV;
	pT_min_cut  = pT_cut;
	pT_max      = 2005.*GeV2TeV;
	pT_max_cut  = 2000.*GeV2TeV+pT_cut;

	// logarithmic boundries and bins of histograms
	logMmin = log10(imass_min);
	logMmin_cut = log10(imass_min_cut);
	logMmax = log10(imass_max);
	logMmax_cut = log10(imass_max_cut);
	M_binwidth = (Double_t)( (logMmax-logMmin)/(Double_t)imass_nbins );
	M_binwidth_cut = (Double_t)( (logMmax_cut-logMmin_cut)/(Double_t)imass_nbins );
	M_bins[0] = imass_min;
	M_bins_cut[0] = imass_min_cut;
	for (Int_t i=1 ; i<=imass_nbins ; i++)
	{ 
		M_bins[i] = TMath::Power( 10,(logMmin + i*M_binwidth) );
		M_bins_cut[i] = TMath::Power( 10,(logMmin_cut + i*M_binwidth_cut) );
	}
	
	logpTmin = log10(pT_min);
	logpTmin_cut = log10(pT_min_cut);
	logpTmax = log10(pT_max);
	logpTmax_cut = log10(pT_max_cut);
	pT_binwidth = (Double_t)( (logpTmax-logpTmin)/(Double_t)pT_nbins );
	pT_binwidth_cut = (Double_t)( (logpTmax_cut-logpTmin_cut)/(Double_t)pT_nbins );
	pT_bins[0] = pT_min;
	pT_bins_cut[0] = pT_min_cut;
	for (Int_t i=1 ; i<=pT_nbins ; i++)
	{
		pT_bins[i] = TMath::Power( 10,(logpTmin + i*pT_binwidth) );
		pT_bins_cut[i] = TMath::Power( 10,(logpTmin_cut + i*pT_binwidth_cut) );
	}

	
	eta_nbins   = 24;
	eta_min     = -3.;
	eta_max     = 3.;

	costh_nbins = 10;
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
	
	ipTdiff_nbins = 50;
	ipTdiff_min   = -1./(20.*GeV2TeV);
	ipTdiff_max   = +1./(20.*GeV2TeV);
	
	etaSum_nbins = 50;;
	etaSum_min   = -5.;
	etaSum_max   = +5.;
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
	h1_cosmicCosthAllCuts = new TH1D("cosThetaDimuAllCuts","cosThetaDimuAllCuts", cosmicCosth_nbins, cosmicCosth_min, cosmicCosth_max);
	h2_xyVertex = new TH2D("xyVertex","xyVertex",   xyVertex_nbins, xyVertex_min, xyVertex_max,
	xyVertex_nbins, xyVertex_min, xyVertex_max);
}

void graphicObjects::bookHistos(TDirectory* tdir)
{
	if(tdir!=NULL) tdir->cd();

	h1_imass = new TH1D("imass","imass", imass_nbins, M_bins_cut);
	//h1_imass = new TH1D("imass","imass", imass_nbins, M_bins);
	//h1_imass = new TH1D("imass","imass", imass_nbins, imass_min, imass_max);
	h1_ipTdiff = new TH1D("ipTdiff","ipTdiff", ipTdiff_nbins, ipTdiff_min, ipTdiff_max);
	h1_etaSum = new TH1D("etaSum","etaSum", etaSum_nbins, etaSum_min, etaSum_max);
	h1_pT = new TH1D("pT","pT", pT_nbins, pT_bins_cut);
	//h1_pT = new TH1D("pT","pT", pT_nbins, pT_bins);
	//h1_pT = new TH1D("pT","pT", pT_nbins, pT_min, pT_max);
	h1_pT_muplus = new TH1D("pT #mu^{+}","pT #mu^{+}", pT_nbins, pT_bins_cut);
	//h1_pT_muplus = new TH1D("pT #mu^{+}","pT #mu^{+}", pT_nbins, pT_bins);
	//h1_pT_muplus = new TH1D("pT #mu^{+}","pT #mu^{+}", pT_nbins, pT_min, pT_max);
	h1_eta = new TH1D("eta","eta", eta_nbins, eta_min, eta_max);
	h1_eta_muplus = new TH1D("eta #mu^{+}","eta #mu^{+}", eta_nbins, eta_min, eta_max);
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
	cnv_cosmicCosth->Divide(1,2);
	pad_cosmicCosth = cnv_cosmicCosth->cd(1);
	pad_cosmicCosthAllCuts = cnv_cosmicCosth->cd(2);
	cnv_cosmicCosth->Draw();
	cnv_cosmicCosth->cd();
	pad_cosmicCosth->cd();
	h1_cosmicCosth->Draw();
	pad_cosmicCosthAllCuts->cd();
	h1_cosmicCosthAllCuts->Draw();
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
	cnv_pT->Divide(1,2);
	pad_pT = cnv_pT->cd(1);
	pad_pT->SetLogy();
	pad_pT_muplus = cnv_pT->cd(2);
	pad_pT_muplus->SetLogy();
	cnv_pT->Draw();
	cnv_pT->cd();
	pad_pT->cd();
	h1_pT->Draw();
	pad_pT_muplus->cd();
	h1_pT_muplus->Draw();
	cnv_pT->Update();
    cnv_pT->Write();

	cnv_eta = new TCanvas("eta","eta",canv_x,canv_y);
	cnv_eta->Divide(1,2);
	pad_eta = cnv_eta->cd(1);
	pad_eta_muplus = cnv_eta->cd(2);
	cnv_eta->Draw();
	pad_eta->cd();
	h1_eta->Draw();
	pad_eta_muplus->cd();
	h1_eta_muplus->Draw();
	cnv_eta->Update();
    cnv_eta->Write();

	cnv_costh = new TCanvas("costh","costh",canv_x,canv_y);
	cnv_costh->Draw();
	cnv_costh->cd();
	h1_costh->Draw();
	cnv_costh->Update();
    cnv_costh->Write();
	
	cnv_ipTdiff = new TCanvas("ipTdiff","ipTdiff",canv_x,canv_y);
	cnv_ipTdiff->Draw();
	cnv_ipTdiff->cd();
	h1_ipTdiff->SetXTitle("1/p_{T}^{#mu+} - 1/p_{T}^{#mu-} (1/TeV)");
	h1_ipTdiff->Draw("e1x0");
	//-------------------------------------------------------------------------
	TF1* f = new TF1("Lorentzian",Lorentzian,ipTdiff_min,ipTdiff_max, 3);
	f->SetParameters(0,h1_ipTdiff->GetMaximum());
	f->SetParLimits(0,0,h1_ipTdiff->GetEntries());
	f->SetParameters(1,1./(200.*GeV2TeV));
	f->SetParLimits(1,1./(2000.*GeV2TeV),1./(20.*GeV2TeV));
	f->SetParameters(2,0.);
	f->SetParLimits(2,0.1*ipTdiff_min,0.1*ipTdiff_max);
	h1_ipTdiff->Fit(f,"VN","",0.8*ipTdiff_min,0.8*ipTdiff_max);
	cout << "ipTdiff Lorentzian fit :: norm = " << f->GetParameter(0) << " +/- " << f->GetParError(0) << endl;
	cout << "ipTdiff Lorentzian fit :: widt = " << f->GetParameter(1) << " +/- " << f->GetParError(1) << endl;
	cout << "ipTdiff Lorentzian fit :: mean = " << f->GetParameter(2) << " +/- " << f->GetParError(2) << endl;
	cout << "ipTdiff Lorentzian fit :: Chi2 = " << f->GetChisquare() << endl;
	cout << "ipTdiff Lorentzian fit :: NDF  = " << f->GetNDF() << endl;
	cout << "ipTdiff Lorentzian fit :: yield = " << f->GetParameter(0)/h1_ipTdiff->GetBinWidth(1) << " +/- " << f->GetParError(0)/h1_ipTdiff->GetBinWidth(1) << endl;
	f->SetLineColor(kBlue);
	f->Draw("sames");
	leg_ipTdiff = new TLegend(leg_x1*0.8, leg_y1*2., leg_x2, leg_y2);
	leg_ipTdiff->AddEntry( h1_ipTdiff, "Data", "lep");
	leg_ipTdiff->AddEntry( f, "#chi^{2} fit = Lorentzian", "L");
	leg_ipTdiff->Draw("sames");
	//-------------------------------------------------------------------------
	cnv_ipTdiff->Update();
    cnv_ipTdiff->Write();
	
	cnv_etaSum = new TCanvas("etaSum","etaSum",canv_x,canv_y);
	cnv_etaSum->Draw();
	cnv_etaSum->cd();
	h1_etaSum->Draw();
	cnv_etaSum->Update();
    cnv_etaSum->Write();
}

void graphicObjects::bookHistosMap(TMapds* cutFlowOrdered, TMapds* cutFlowTypeOrdered, TDirectory* tdir)
{
	if(tdir==NULL) return;

	tdir->cd();

	hmap_cutFlow_imass = new TMapSP2TH1D();
	hmap_cutFlow_pT    = new TMapSP2TH1D();

	for(TMapds::iterator it=cutFlowOrdered->begin() ; it!=cutFlowOrdered->end() ; ++it)
	{
		double snumber = it->first;
		
		///////////////////////////////////////////////////////////////
		// ignore preselection: ///////////////////////////////////////
		if(cutFlowTypeOrdered->operator[](snumber)=="preselection") continue; /////
		///////////////////////////////////////////////////////////////

		string sname = "";

		// invariant mass cut flow histos
		sname = "imass." + it->second;
		//hmap_cutFlow_imass->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), imass_nbins, imass_min, imass_max) ) );
		hmap_cutFlow_imass->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), imass_nbins, M_bins) ) );
		cout << "(" << snumber << ") booked " << sname << endl;

		// pT cut flow histos
		sname = "pT." + it->second;
		//hmap_cutFlow_pT->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), pT_nbins, pT_min, pT_max) ) );
		hmap_cutFlow_pT->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), pT_nbins, pT_bins) ) );
		cout << "(" << snumber << ") booked " << sname << endl;
	}
}

void graphicObjects::drawHistosMap(TMapds* cutFlowOrdered, TMapds* cutFlowTypeOrdered, TDirectory* tdir)
{
	if(tdir==NULL) return;
	
	tdir->cd();

	bool bfirst;
	
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
	
	bfirst = true;
	for(TMapds::iterator ii=cutFlowOrdered->begin() ; ii!=cutFlowOrdered->end() ; ++ii)
	{
		double num = ii->first;
		///////////////////////////////////////////////////////////////
		// ignore preselection: ///////////////////////////////////////
		if(cutFlowTypeOrdered->operator[](num)=="preselection") continue; /////////
		///////////////////////////////////////////////////////////////
	
		//if(ii == cutFlowOrdered->begin()) bfirst = true;
		//else bfirst = false;
		
		string str = ii->second; 
		it=hmap_cutFlow_imass->find("imass."+str);
		string sname = it->first;
		(*hmap_cutFlow_imass)[sname]->SetFillColor(colorAccumulate);
		(*hmap_cutFlow_imass)[sname]->SetLineColor(colorAccumulate);
		leg_cutFlow_imass->AddEntry( (*hmap_cutFlow_imass)[sname], str.c_str(), "f");
		if(bfirst)
		{
			(*hmap_cutFlow_imass)[sname]->SetMinimum(5.e-1);
			(*hmap_cutFlow_imass)[sname]->Draw();
		}
		else (*hmap_cutFlow_imass)[sname]->Draw("SAMES");
		colorAccumulate += colorOffset;
		cout << "drawn " << sname << endl;
		
		bfirst = false;
	}
	leg_cutFlow_imass->Draw("SAMES");
	cnv_cutFlow_imass->Update();
	cnv_cutFlow_imass->Write();

	//--------------
	
	cnv_cutFlow_pT = new TCanvas("pT.cutFlow","pT.cutFlow",canv_x,canv_y);
	cnv_cutFlow_pT->SetLogy();
	cnv_cutFlow_pT->Draw();
	cnv_cutFlow_pT->cd();
	colorAccumulate = colorStart;
	
	bfirst = true;
	for(TMapds::iterator ii=cutFlowOrdered->begin() ; ii!=cutFlowOrdered->end() ; ++ii)
	{
		double num = ii->first;
		///////////////////////////////////////////////////////////////
		// ignore preselection: ///////////////////////////////////////
		if(cutFlowTypeOrdered->operator[](num)=="preselection") continue; /////////
		///////////////////////////////////////////////////////////////
	
		//if(ii == cutFlowOrdered->begin()) bfirst = true;
		//else bfirst = false;
	
		string str = ii->second;
		it=hmap_cutFlow_pT->find("pT."+str);
		string sname = it->first;
		(*hmap_cutFlow_pT)[sname]->SetFillColor(colorAccumulate);
		(*hmap_cutFlow_pT)[sname]->SetLineColor(colorAccumulate);
		leg_cutFlow_pT->AddEntry( (*hmap_cutFlow_pT)[sname], str.c_str(), "f");
		if(bfirst)
		{
			(*hmap_cutFlow_pT)[sname]->SetMinimum(5.e-1);
			(*hmap_cutFlow_pT)[sname]->Draw();
		}
		else (*hmap_cutFlow_pT)[sname]->Draw("SAMES");
		colorAccumulate += colorOffset;
		cout << "drawn " << sname << endl;
		
		bfirst = false;
	}
	leg_cutFlow_pT->Draw("SAMES");
	cnv_cutFlow_pT->Update();
	cnv_cutFlow_pT->Write();
}

void graphicObjects::bookFitHistos(TDirectory* tdir)
{
	if(tdir!=NULL) tdir->cd();

	h1_imassFit = new TH1D("imassFit","imassFit", imass_fit_nbins, imass_fit_min, imass_fit_max);
}

void graphicObjects::drawFitHistos(TDirectory* tdir, TF1* fGuess, TF1* fFitted)
{
	if(tdir!=NULL) tdir->cd();
	
	leg_imassFit = new TLegend(leg_x1, leg_y1*2., leg_x2, leg_y2);
	
	cnv_imassFit = new TCanvas("imassFit","imassFit",canv_x,canv_y);
	cnv_imassFit->Draw();
	cnv_imassFit->cd();
	
	double h_max = h1_imassFit->GetMaximum();
	double f_max = fFitted->GetMaximum(XMIN,XMAX);
	double max = 0.;
	max = ( f_max > h_max) ? f_max : h_max;
	h1_imassFit->SetMaximum(1.05*max);
	
	h1_imassFit->SetMarkerStyle(20);
	h1_imassFit->Draw("e1x0");
	
	fGuess->SetLineStyle(1);
	fGuess->SetLineColor(kRed);
	fGuess->SetLineWidth(2);
	//fGuess->Draw("sames");
	
	fFitted->SetLineStyle(1);
	fFitted->SetLineColor(kBlue);
	fFitted->SetLineWidth(2);
	fFitted->Draw("sames");
	
	leg_imassFit->AddEntry( h1_imassFit, "Data", "lep");
	//leg_imassFit->AddEntry( fGuess, "Guess", "L");
	leg_imassFit->AddEntry( fFitted, "#chi^{2} fit", "L");
	leg_imassFit->Draw("sames");
	
	cnv_imassFit->Update();
	cnv_imassFit->Write();
}

