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
	TMapsvd::iterator it4=cut_cutFlowMapSVD->find("pTandEtaBarrel");
	TMapsvd::iterator it5=cut_cutFlowMapSVD->find("pTandEta");
	TMapsvd::iterator itEnd=cut_cutFlowMapSVD->end();
	if     ( it1 != itEnd ) pTcutNmae = "pT";
	else if( it2 != itEnd ) pTcutNmae = "pT_use_qOp_and_theta";
	else if( it3 != itEnd ) pTcutNmae = "pTandEtaTight";
	else if( it4 != itEnd ) pTcutNmae = "pTandEtaBarrel";
	else if( it5 != itEnd ) pTcutNmae = "pTandEta";
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
	
	imass_fit_nbins = 100;
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
	
	phi_nbins   = 15;
	phi_min     = -pi;
	phi_max     = +pi;
	
	eta_nbins   = 150;
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
	
	pTdiff_nbins = 100;
	pTdiff_min   = -50.*GeV2TeV;
	pTdiff_max   = +50.*GeV2TeV;
	
	pTratio_nbins = 120;
	pTratio_min   = 0.;
	pTratio_max   = 3.;
	
	pTmevspTid_nbins = 100;
	pTmevspTid_min   = 0.*GeV2TeV;
	pTmevspTid_max   = 500.*GeV2TeV;
	
	Afb_nbins = 10;
	Afb_min   = 850.*GeV2TeV;
	Afb_max   = 1000.*GeV2TeV;
	
	tagNprobe_pT_nbins = 50;
	tagNprobe_pT_min   = 0.*MeV2GeV;
	tagNprobe_pT_max   = 150.*MeV2GeV;
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
	

	h1_pTdiff = new TH1D("pTdiff_mu-", "pTdiff_mu-", pTdiff_nbins, pTdiff_min, pTdiff_max);
	h1_pTratio = new TH1D("pTratio_mu-", "pTratio_mu-", pTratio_nbins, pTratio_min, pTratio_max);
	h2_pTmevspTid = new TH2D("pTmevspTid_mu-", "pTmevspTid_mu-", pTmevspTid_nbins,pTmevspTid_min,pTmevspTid_max, pTmevspTid_nbins,pTmevspTid_min,pTmevspTid_max);
	h1_pTdiff_muplus = new TH1D("pTdiff_mu+", "pTdiff_mu+", pTdiff_nbins, pTdiff_min, pTdiff_max);
	h1_pTratio_muplus = new TH1D("pTratio_mu+", "pTratio_mu+", pTratio_nbins, pTratio_min, pTratio_max);
	h2_pTmevspTid_muplus = new TH2D("pTmevspTid_mu+", "pTmevspTid_mu+", pTmevspTid_nbins,pTmevspTid_min,pTmevspTid_max, pTmevspTid_nbins,pTmevspTid_min,pTmevspTid_max);
	
	h1_Afb = new TH1D("Afb","Afb",Afb_nbins,Afb_min,Afb_max);
	
	h1_tagNprobe_candidates_pT     = new TH1D("tagNprobe_candidates_pT","tagNprobe_candidates_pT",tagNprobe_pT_nbins,tagNprobe_pT_min,tagNprobe_pT_max);
	h1_tagNprobe_succeeded_pT     = new TH1D("tagNprobe_succeeded_pT","tagNprobe_succeeded_pT",tagNprobe_pT_nbins,tagNprobe_pT_min,tagNprobe_pT_max);
	h1_tagNprobe_efficiency_pT = new TH1D("tagNprobe_efficiency_pT","tagNprobe_efficiency_pT",tagNprobe_pT_nbins,tagNprobe_pT_min,tagNprobe_pT_max);
	h1_tagNprobe_candidates_eta     = new TH1D("tagNprobe_candidates_eta","tagNprobe_candidates_eta",eta_nbins,eta_min,eta_max);
	h1_tagNprobe_succeeded_eta     = new TH1D("tagNprobe_succeeded_eta","tagNprobe_succeeded_eta",eta_nbins,eta_min,eta_max);
	h1_tagNprobe_efficiency_eta = new TH1D("tagNprobe_efficiency_eta","tagNprobe_efficiency_eta",eta_nbins,eta_min,eta_max);
	h1_tagNprobe_candidates_phi     = new TH1D("tagNprobe_candidates_phi","tagNprobe_candidates_phi",phi_nbins,phi_min,phi_max);
	h1_tagNprobe_succeeded_phi     = new TH1D("tagNprobe_succeeded_phi","tagNprobe_succeeded_phi",phi_nbins,phi_min,phi_max);
	h1_tagNprobe_efficiency_phi = new TH1D("tagNprobe_efficiency_phi","tagNprobe_efficiency_phi",phi_nbins,phi_min,phi_max);
	
	h1_truth_candidates_pT = new TH1D("truth_candidates_pT","truth_candidates_pT",tagNprobe_pT_nbins,tagNprobe_pT_min,tagNprobe_pT_max);
	h1_truth_succeeded_pT  = new TH1D("truth_succeeded_pT","truth_succeeded_pT",tagNprobe_pT_nbins,tagNprobe_pT_min,tagNprobe_pT_max);
	h1_truth_efficiency_pT = new TH1D("truth_efficiency_pT","truth_efficiency_pT",tagNprobe_pT_nbins,tagNprobe_pT_min,tagNprobe_pT_max);
	h1_truth_candidates_eta = new TH1D("truth_candidates_eta","truth_candidates_eta",eta_nbins,eta_min,eta_max);
	h1_truth_succeeded_eta  = new TH1D("truth_succeeded_eta","truth_succeeded_eta",eta_nbins,eta_min,eta_max);
	h1_truth_efficiency_eta = new TH1D("truth_efficiency_eta","truth_efficiency_eta",eta_nbins,eta_min,eta_max);
	h1_truth_candidates_phi = new TH1D("truth_candidates_phi","truth_candidates_phi",phi_nbins,phi_min,phi_max);
	h1_truth_succeeded_phi  = new TH1D("truth_succeeded_phi","truth_succeeded_phi",phi_nbins,phi_min,phi_max);
	h1_truth_efficiency_phi = new TH1D("truth_efficiency_phi","truth_efficiency_phi",phi_nbins,phi_min,phi_max);
}

void graphicObjects::drawPerformance(vector<int>& vEntries, vector<double>& vResMemory, vector<double>& vVirMemory, TDirectory* tdir)
{
	if(tdir!=NULL) tdir->cd();
	
	nentries = (Int_t)vEntries.size();
	resMemoryArray = (Double_t*)malloc(nentries*sizeof(Double_t));
	virMemoryArray = (Double_t*)malloc(nentries*sizeof(Double_t));
	entryArray     = (Double_t*)malloc(nentries*sizeof(Double_t));
	for(Int_t i=0 ; i<nentries ; i++)
	{
		resMemoryArray[i] = (Double_t)vResMemory[i];
		virMemoryArray[i] = (Double_t)vVirMemory[i];
		entryArray[i]     = (Double_t)vEntries[i];
	}
	
	cMemoryMonitor = new TCanvas("memory","memory",canv_x,canv_y);
	cMemoryMonitor->Draw();
	cMemoryMonitor->cd();
	
	gVirMemoryMonitor = new TGraph (nentries, entryArray, virMemoryArray);
	gVirMemoryMonitor->SetTitle("");
	gVirMemoryMonitor->SetLineStyle(3);
    gVirMemoryMonitor->SetLineColor(kBlue);
	gVirMemoryMonitor->GetXaxis()->SetTitle("entry");
    gVirMemoryMonitor->GetYaxis()->SetTitle("memory");
    gVirMemoryMonitor->SetMinimum(0.);
    gVirMemoryMonitor->Draw("AC");
	
	gResMemoryMonitor = new TGraph (nentries, entryArray, resMemoryArray);
	gResMemoryMonitor->SetTitle("");
	gResMemoryMonitor->SetLineStyle(1);
    gResMemoryMonitor->SetLineColor(kRed); 
    gResMemoryMonitor->Draw("C");
	
	leg_memory = new TLegend(leg_x1, leg_y1, leg_x2, leg_y2*2./3.);
	leg_memory->AddEntry( gVirMemoryMonitor, "VIRT", "L");
	leg_memory->AddEntry( gResMemoryMonitor, "RES", "L");
	leg_memory->Draw("sames");
	
	cMemoryMonitor->Update();
	cMemoryMonitor->SaveAs("memory.png");
	cMemoryMonitor->Write();
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
	
	cnv_pTdiff = new TCanvas("pTdiff","pTdiff",canv_x,canv_y);
	cnv_pTdiff->Divide(1,2);
	pad_pTdiff = cnv_pTdiff->cd(1);
	pad_pTdiff_muplus = cnv_pTdiff->cd(2);
	cnv_pTdiff->Draw();
	pad_pTdiff->cd();
	h1_pTdiff->Draw();
	pad_pTdiff_muplus->cd();
	h1_pTdiff_muplus->Draw();
	cnv_pTdiff->Update();
    cnv_pTdiff->Write();
	
	cnv_pTratio = new TCanvas("pTratio","pTratio",canv_x,canv_y);
	cnv_pTratio->Divide(1,2);
	pad_pTratio = cnv_pTratio->cd(1);
	pad_pTratio_muplus = cnv_pTratio->cd(2);
	cnv_pTratio->Draw();
	pad_pTratio->cd();
	h1_pTratio->Draw();
	pad_pTratio_muplus->cd();
	h1_pTratio_muplus->Draw();
	cnv_pTratio->Update();
    cnv_pTratio->Write();
	
	cnv_pTmevspTid = new TCanvas("pTmevspTid","pTmevspTid",canv_x,canv_y);
	cnv_pTmevspTid->Divide(1,2);
	pad_pTmevspTid = cnv_pTmevspTid->cd(1);
	pad_pTmevspTid_muplus = cnv_pTmevspTid->cd(2);
	cnv_pTmevspTid->Draw();
	pad_pTmevspTid->cd();
	h2_pTmevspTid->Draw("BOX");
	pad_pTmevspTid_muplus->cd();
	h2_pTmevspTid_muplus->Draw("BOX");
	cnv_pTmevspTid->Update();
    cnv_pTmevspTid->Write();
	
	cnv_Afb = new TCanvas("Afb","Afb",canv_x,canv_y);
	cnv_Afb->Draw();
	cnv_Afb->cd();
	h1_Afb->SetTitle("");
	h1_Afb->SetMinimum(-1.1);
	h1_Afb->SetMaximum(+1.1);
	h1_Afb->SetXTitle("#hat{m}_{#mu#mu} TeV");
	h1_Afb->SetYTitle("A_{FB}");
	h1_Afb->Draw("e1x0");
	cnv_Afb->Update();
	cnv_Afb->Write();
	
	
	cnv_efficiency_pT = new TCanvas("efficiency_pT","efficiency_pT",canv_x,canv_y);
	cnv_efficiency_pT->Divide(1,3);
	pad_candidates_pT    = cnv_efficiency_pT->cd(1);
	pad_succeeded_pT  = cnv_efficiency_pT->cd(2);
	pad_efficiency_pT = cnv_efficiency_pT->cd(3);
	cnv_efficiency_pT->Draw();
	pad_candidates_pT->cd();
	h1_tagNprobe_candidates_pT->SetTitle("");
	h1_tagNprobe_candidates_pT->SetXTitle("p_{T} TeV");
	h1_tagNprobe_candidates_pT->SetYTitle("Candidate probe muons");
	h1_truth_candidates_pT->SetTitle("");
	h1_truth_candidates_pT->SetXTitle("p_{T} TeV");
	h1_truth_candidates_pT->SetYTitle("Candidate probe muons");
	h1_truth_candidates_pT->SetLineColor(kRed);
	h1_truth_candidates_pT->SetLineStyle(2);
	h1_truth_candidates_pT->Draw();
	h1_tagNprobe_candidates_pT->Draw("sames");
	pad_succeeded_pT->cd();
	h1_tagNprobe_succeeded_pT->SetTitle("");
	h1_tagNprobe_succeeded_pT->SetXTitle("p_{T} TeV");
	h1_tagNprobe_succeeded_pT->SetYTitle("Probe muons");
	h1_truth_succeeded_pT->SetTitle("");
	h1_truth_succeeded_pT->SetXTitle("p_{T} TeV");
	h1_truth_succeeded_pT->SetYTitle("Probe muons");
	h1_truth_succeeded_pT->SetLineColor(kRed);
	h1_truth_succeeded_pT->SetLineStyle(2);
	h1_truth_succeeded_pT->Draw();
	h1_tagNprobe_succeeded_pT->Draw("sames");
	pad_efficiency_pT->cd();
	pad_efficiency_pT->SetGrid();
	h1_tagNprobe_efficiency_pT->SetTitle("");
	h1_tagNprobe_efficiency_pT->SetXTitle("p_{T} TeV");
	h1_tagNprobe_efficiency_pT->SetYTitle("#epsilon = #frac{N_{probes}}{N_{probe}^{candidates}}");
	h1_truth_efficiency_pT->SetTitle("");
	h1_truth_efficiency_pT->SetXTitle("p_{T} TeV");
	h1_truth_efficiency_pT->SetYTitle("#epsilon = #frac{N_{probes}}{N_{probe}^{candidates}}");
	h1_truth_efficiency_pT->SetLineColor(kRed);
	h1_truth_efficiency_pT->Draw();
	h1_tagNprobe_efficiency_pT->Draw("e1x0sames");
	cnv_efficiency_pT->Update();
	cnv_efficiency_pT->Write();
	
	cnv_efficiency_eta = new TCanvas("efficiency_eta","efficiency_eta",canv_x,canv_y);
	cnv_efficiency_eta->Divide(1,3);
	pad_candidates_eta    = cnv_efficiency_eta->cd(1);
	pad_succeeded_eta  = cnv_efficiency_eta->cd(2);
	pad_efficiency_eta = cnv_efficiency_eta->cd(3);
	cnv_efficiency_eta->Draw();
	pad_candidates_eta->cd();
	h1_tagNprobe_candidates_eta->SetTitle("");
	h1_tagNprobe_candidates_eta->SetXTitle("#eta");
	h1_tagNprobe_candidates_eta->SetYTitle("Candidate probe muons");
	h1_truth_candidates_eta->SetTitle("");
	h1_truth_candidates_eta->SetXTitle("#eta");
	h1_truth_candidates_eta->SetYTitle("Candidate probe muons");
	h1_truth_candidates_eta->SetLineColor(kRed);
	h1_truth_candidates_eta->SetLineStyle(2);
	h1_truth_candidates_eta->Draw();
	h1_tagNprobe_candidates_eta->Draw("sames");
	pad_succeeded_eta->cd();
	h1_tagNprobe_succeeded_eta->SetTitle("");
	h1_tagNprobe_succeeded_eta->SetXTitle("#eta");
	h1_tagNprobe_succeeded_eta->SetYTitle("Probe muons");
	h1_truth_succeeded_eta->SetTitle("");
	h1_truth_succeeded_eta->SetXTitle("#eta");
	h1_truth_succeeded_eta->SetYTitle("Probe muons");
	h1_truth_succeeded_eta->SetLineColor(kRed);
	h1_truth_succeeded_eta->SetLineStyle(2);
	h1_truth_succeeded_eta->Draw();
	h1_tagNprobe_succeeded_eta->Draw("sames");
	pad_efficiency_eta->cd();
	pad_efficiency_eta->SetGrid();
	h1_tagNprobe_efficiency_eta->SetTitle("");
	h1_tagNprobe_efficiency_eta->SetXTitle("#eta");
	h1_tagNprobe_efficiency_eta->SetYTitle("#epsilon = #frac{N_{probes}}{N_{probe}^{candidates}}");
	h1_truth_efficiency_eta->SetTitle("");
	h1_truth_efficiency_eta->SetXTitle("#eta");
	h1_truth_efficiency_eta->SetYTitle("#epsilon = #frac{N_{probes}}{N_{probe}^{candidates}}");
	h1_truth_efficiency_eta->SetLineColor(kRed);
	h1_truth_efficiency_eta->Draw();
	h1_tagNprobe_efficiency_eta->Draw("e1x0sames");
	cnv_efficiency_eta->Update();
	cnv_efficiency_eta->Write();
	
	cnv_efficiency_phi = new TCanvas("efficiency_phi","efficiency_phi",canv_x,canv_y);
	cnv_efficiency_phi->Divide(1,3);
	pad_candidates_phi    = cnv_efficiency_phi->cd(1);
	pad_succeeded_phi  = cnv_efficiency_phi->cd(2);
	pad_efficiency_phi = cnv_efficiency_phi->cd(3);
	cnv_efficiency_phi->Draw();
	pad_candidates_phi->cd();
	h1_tagNprobe_candidates_phi->SetTitle("");
	h1_tagNprobe_candidates_phi->SetXTitle("#phi");
	h1_tagNprobe_candidates_phi->SetYTitle("Candidate probe muons");
	h1_truth_candidates_phi->SetTitle("");
	h1_truth_candidates_phi->SetXTitle("#phi");
	h1_truth_candidates_phi->SetYTitle("Candidate probe muons");
	h1_truth_candidates_phi->SetLineColor(kRed);
	h1_truth_candidates_phi->SetLineStyle(2);
	h1_truth_candidates_phi->Draw();
	h1_tagNprobe_candidates_phi->Draw("sames");
	pad_succeeded_phi->cd();
	h1_tagNprobe_succeeded_phi->SetTitle("");
	h1_tagNprobe_succeeded_phi->SetXTitle("#phi");
	h1_tagNprobe_succeeded_phi->SetYTitle("Probe muons");
	h1_truth_succeeded_phi->SetTitle("");
	h1_truth_succeeded_phi->SetXTitle("#phi");
	h1_truth_succeeded_phi->SetYTitle("Probe muons");
	h1_truth_succeeded_phi->SetLineColor(kRed);
	h1_truth_succeeded_phi->SetLineStyle(2);
	h1_truth_succeeded_phi->Draw();
	h1_tagNprobe_succeeded_phi->Draw("sames");
	pad_efficiency_phi->cd();
	pad_efficiency_phi->SetGrid();
	h1_tagNprobe_efficiency_phi->SetTitle("");
	h1_tagNprobe_efficiency_phi->SetXTitle("#phi");
	h1_tagNprobe_efficiency_phi->SetYTitle("#epsilon = #frac{N_{probes}}{N_{probe}^{candidates}}");
	h1_truth_efficiency_phi->SetTitle("");
	h1_truth_efficiency_phi->SetXTitle("#phi");
	h1_truth_efficiency_phi->SetYTitle("#epsilon = #frac{N_{probes}}{N_{probe}^{candidates}}");
	h1_truth_efficiency_phi->SetLineColor(kRed);
	h1_truth_efficiency_phi->Draw();
	h1_tagNprobe_efficiency_phi->Draw("e1x0sames");
	cnv_efficiency_phi->Update();
	cnv_efficiency_phi->Write();
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *



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


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 


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


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *


void graphicObjects::bookCutProfileHistosMap(TMapds* cutFlowOrdered, TDirectory* tdir)
{
	if(tdir==NULL) return;

	tdir->cd();

	h1map_cutProfile = new TMapSP2TH1D();
	h2map_cutProfile = new TMapSP2TH2D();
	
	cmap_cutProfile  = new TMapSP2TCNV();

	for(TMapds::iterator it=cutFlowOrdered->begin() ; it!=cutFlowOrdered->end() ; ++it)
	{
		double snumber = it->first;
		string sname   = it->second;

		if(sname=="GRL")
		{
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 2, 0.,2.) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("isGRL");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
		}
		
		else if(sname=="Trigger")
		{
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 2, 0.,2.) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("isTrigger");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
		}
		
		else if(sname=="PV")
		{
			h2map_cutProfile->insert( make_pair( sname, new TH2D(sname.c_str(),sname.c_str(), 600,-300,300.,  200,0,200) ) );
			(*h2map_cutProfile)[sname]->SetXTitle("zVtx");
			(*h2map_cutProfile)[sname]->SetYTitle("nTracks");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
		}
		
		else if(sname=="pT")
		{
			string stmp = sname;
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), pT_nbins, pT_min, pT_max) ) );
			//h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), pT_nbins, pT_bins) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("pT");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), pT_nbins, pT_min, pT_max) ) );
			//h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), pT_nbins, pT_bins) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("pT");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
		}
		
		else if(sname=="pT_use_qOp_and_theta")
		{
			string stmp = sname;
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), pT_nbins, pT_min, pT_max) ) );
			//h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), pT_nbins, pT_bins) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("p_{T}=Q/#left|p#right| #times #sin(#theta)");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), pT_nbins, pT_min, pT_max) ) );
			//h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), pT_nbins, pT_bins) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("p_{T}=Q/#left|p#right| #times #sin(#theta)");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
		}
		
		else if(sname=="eta")
		{
			string stmp = sname;
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), eta_nbins, eta_min, eta_max) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("#eta");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), eta_nbins, eta_min, eta_max) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("#eta");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
		}
		
		else if(sname=="etaTight")
		{
			string stmp = sname;
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), eta_nbins, eta_min, eta_max) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("#eta_{Tight}");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), eta_nbins, eta_min, eta_max) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("#eta_{Tight}");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
		}
		
		else if(sname=="etaBarrel")
		{
			string stmp = sname;
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), eta_nbins, eta_min, eta_max) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("#eta_{Barrel}");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), eta_nbins, eta_min, eta_max) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("#eta_{Barrel}");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
		}
		
		else if(sname=="pTandEta")
		{
			string stmp = sname;
			sname = stmp+"_1";
			h2map_cutProfile->insert( make_pair( sname, new TH2D(sname.c_str(),sname.c_str(), pT_nbins,pT_min,pT_max,  eta_nbins,eta_min,eta_max) ) );
			(*h2map_cutProfile)[sname]->SetXTitle("p_{T}");
			(*h2map_cutProfile)[sname]->SetYTitle("#eta_{Tight}");
			sname = stmp+"_2";
			h2map_cutProfile->insert( make_pair( sname, new TH2D(sname.c_str(),sname.c_str(), pT_nbins,pT_min,pT_max,  eta_nbins,eta_min,eta_max) ) );
			(*h2map_cutProfile)[sname]->SetXTitle("p_{T}");
			(*h2map_cutProfile)[sname]->SetYTitle("#eta_{Tight}");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
		}
		
		else if(sname=="pTandEtaTight")
		{
			string stmp = sname;
			sname = stmp+"_1";
			h2map_cutProfile->insert( make_pair( sname, new TH2D(sname.c_str(),sname.c_str(), pT_nbins,pT_min,pT_max,  eta_nbins,eta_min,eta_max) ) );
			(*h2map_cutProfile)[sname]->SetXTitle("p_{T}");
			(*h2map_cutProfile)[sname]->SetYTitle("#eta_{Tight}");
			sname = stmp+"_2";
			h2map_cutProfile->insert( make_pair( sname, new TH2D(sname.c_str(),sname.c_str(), pT_nbins,pT_min,pT_max,  eta_nbins,eta_min,eta_max) ) );
			(*h2map_cutProfile)[sname]->SetXTitle("p_{T}");
			(*h2map_cutProfile)[sname]->SetYTitle("#eta_{Tight}");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
		}
		
		else if(sname=="pTandEtaBarrel")
		{
			string stmp = sname;
			sname = stmp+"_1";
			h2map_cutProfile->insert( make_pair( sname, new TH2D(sname.c_str(),sname.c_str(), pT_nbins,pT_min,pT_max, eta_nbins, eta_min, eta_max) ) );
			(*h2map_cutProfile)[sname]->SetXTitle("p_{T}");
			(*h2map_cutProfile)[sname]->SetYTitle("#eta_{Barrel}");
			sname = stmp+"_2";
			h2map_cutProfile->insert( make_pair( sname, new TH2D(sname.c_str(),sname.c_str(), pT_nbins,pT_min,pT_max, eta_nbins, eta_min, eta_max) ) );
			(*h2map_cutProfile)[sname]->SetXTitle("p_{T}");
			(*h2map_cutProfile)[sname]->SetYTitle("#eta_{Barrel}");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
		}
		
		else if(sname=="msHits")
		{
			string stmp;
			
			stmp = "nMDTBI";
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("MDT BI passed hits");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("MDT BI passed hits");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
			
			stmp = "nMDTBM";
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("MDT BM passed hits");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("MDT BM passed hits");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
			
			stmp = "nMDTBO";
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("MDT BO passed hits");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("MDT BO passed hits");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
			
			
			stmp = "nRPCPhi1";
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("RPC Phi1 passed hits");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("RPC Phi1 passed hits");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
			
			
			stmp = "nRPCPhi2";
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("RPC Phi2 passed hits");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("RPC Phi2 passed hits");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
			
			stmp = "nRPCPhi3";
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("RPC Phi3 passed hits");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 50,0,50) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("RPC Phi3 passed hits");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
			
		}
		
		else if(sname=="idHits")
		{
			string stmp = sname;
			sname = stmp+"_1";
			h2map_cutProfile->insert( make_pair( sname, new TH2D(sname.c_str(),sname.c_str(), 20,0,20,  20,0,20) ) );
			(*h2map_cutProfile)[sname]->SetXTitle("SCT hits");
			(*h2map_cutProfile)[sname]->SetYTitle("PIX hits");
			sname = stmp+"_2";
			h2map_cutProfile->insert( make_pair( sname, new TH2D(sname.c_str(),sname.c_str(), 20,0,20,  20,0,20) ) );
			(*h2map_cutProfile)[sname]->SetXTitle("SCT hits");
			(*h2map_cutProfile)[sname]->SetYTitle("PIX hits");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
		}
		
		else if(sname=="pTmatchingRatio")
		{
			string stmp = sname;
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), pT_nbins, pT_min, pT_max) ) );
			//h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), pT_nbins, pT_bins) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("p_{T}");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), pT_nbins, pT_min, pT_max) ) );
			//h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), pT_nbins, pT_bins) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("p_{T}");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
		}
		
		else if(sname=="pTmatchingAbsDiff")
		{
			string stmp = sname;
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), pT_nbins, pT_min, pT_max) ) );
			//h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), pT_nbins, pT_bins) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("p_{T}");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), pT_nbins, pT_min, pT_max) ) );
			//h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), pT_nbins, pT_bins) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("p_{T}");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
		}
		
		else if(sname=="d0")
		{
			string stmp = sname;
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 100, -0.5, 0.5) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("d_{0}");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 100, -0.5, 0.5) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("d_{0}");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
		}
		
		else if(sname=="z0")
		{
			string stmp = sname;
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 100, -0.5, 0.5) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("z_{0}");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 100, -0.5, 0.5) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("z_{0}");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
		}
		
		else if(sname=="impactParameter")
		{
			string stmp = sname;
			sname = stmp+"_1";
			h2map_cutProfile->insert( make_pair( sname, new TH2D(sname.c_str(),sname.c_str(), 100,-0.5,0.5,  100,-0.5,0.5) ) );
			(*h2map_cutProfile)[sname]->SetXTitle("d_{0}");
			(*h2map_cutProfile)[sname]->SetYTitle("z_{0}");
			sname = stmp+"_2";
			h2map_cutProfile->insert( make_pair( sname, new TH2D(sname.c_str(),sname.c_str(), 100,-0.5,0.5,  100,-0.5,0.5) ) );
			(*h2map_cutProfile)[sname]->SetXTitle("d_{0}");
			(*h2map_cutProfile)[sname]->SetYTitle("z_{0}");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
		}
		
		else if(sname=="isolation20")
		{
			string stmp = sname;
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 400, 0, 0.01) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("#sum p_{T}^{cone20}/p_{T}");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 400, 0, 0.01) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("#sum p_{T}^{cone20}/p_{T}");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
		}
		
		else if(sname=="isolation30")
		{
			string stmp = sname;
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 400, 0, 0.01) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("#sum p_{T}^{cone30}/p_{T}");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 400, 0, 0.01) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("#sum p_{T}^{cone30}/p_{T}");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
		}
		
		else if(sname=="isolation40")
		{
			string stmp = sname;
			sname = stmp+"_1";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 400, 0, 0.01) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("#sum p_{T}^{cone40}/p_{T}");
			sname = stmp+"_2";
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 400, 0, 0.01) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("#sum p_{T}^{cone40}/p_{T}");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
		}
		
		else if(sname=="oppositeCharge")
		{
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), 2,-1,1) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("Q_{1} #times Q_{2}");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
		}
		
		else if(sname=="imass")
		{
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), imass_nbins, imass_min, imass_max) ) );
			//h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), imass_nbins, M_bins) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("#hat{m}_{#mu#mu}");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
		}
		
		else if(sname=="cosThetaDimu")
		{
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), cosmicCosth_nbins,cosmicCosth_min,cosmicCosth_max) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("#hat{p}_{#mu^{1}} #cdot #hat{p}_{#mu^{2}}");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
		}
		
		else if(sname=="etaSum")
		{
			h1map_cutProfile->insert( make_pair( sname, new TH1D(sname.c_str(),sname.c_str(), etaSum_nbins,etaSum_min,etaSum_max) ) );
			(*h1map_cutProfile)[sname]->SetXTitle("#sum{#eta_{#mu}}");
			cout << "cutProfile: (" << snumber << ") booked " << sname << endl;
		}
		
		else continue;
	}
}

void graphicObjects::drawCutProfileHistosMap(TDirectory* tdir)
{
	if(tdir==NULL) return;
	
	tdir->cd();
	
	string sname = "";
	string snameOrig = "";
	string sNumber = "";
	
	for(TMapSP2TH1D::iterator it=h1map_cutProfile->begin() ; it!=h1map_cutProfile->end() ; ++it)
	{
		sname   = it->first;
		sNumber = sname[sname.length()-1];
		
		if(sNumber=="1")
		{
			snameOrig = "cutProfile_" + sname.substr(0, sname.length()-2);
			cmap_cutProfile->insert( make_pair( snameOrig, new TCanvas(snameOrig.c_str(),snameOrig.c_str(), canv_x,canv_y) ) );
			(*cmap_cutProfile)[snameOrig]->Divide(1,2);
			(*cmap_cutProfile)[snameOrig]->Draw();
			(*cmap_cutProfile)[snameOrig]->cd();
			(*cmap_cutProfile)[snameOrig]->cd(1);
			(*h1map_cutProfile)[sname]->Draw();
		}
		else if(sNumber=="2")
		{
			snameOrig = "cutProfile_" + sname.substr(0, sname.length()-2);
			(*cmap_cutProfile)[snameOrig]->cd(2);
			(*h1map_cutProfile)[sname]->Draw();
			(*cmap_cutProfile)[snameOrig]->Update();
			(*cmap_cutProfile)[snameOrig]->Write();
		}
		else
		{
			snameOrig = "cutProfile_" + sname;
			cmap_cutProfile->insert( make_pair( snameOrig, new TCanvas(snameOrig.c_str(),snameOrig.c_str(), canv_x,canv_y) ) );
			(*cmap_cutProfile)[snameOrig]->Draw();
			(*cmap_cutProfile)[snameOrig]->cd();
			(*h1map_cutProfile)[sname]->Draw();
			(*cmap_cutProfile)[snameOrig]->Update();
			(*cmap_cutProfile)[snameOrig]->Write();
		}
		cout << "drawn cutProfile: " << sname << endl;
	}
	
	for(TMapSP2TH2D::iterator it=h2map_cutProfile->begin() ; it!=h2map_cutProfile->end() ; ++it)
	{
		sname = it->first;
		sNumber = sname[sname.length()-1];
		
		if(sNumber=="1")
		{
			snameOrig = "cutProfile_" + sname.substr(0, sname.length()-2);
			cmap_cutProfile->insert( make_pair( snameOrig, new TCanvas(snameOrig.c_str(),snameOrig.c_str(), canv_x,canv_y) ) );
			(*cmap_cutProfile)[snameOrig]->Divide(1,2);
			(*cmap_cutProfile)[snameOrig]->Draw();
			(*cmap_cutProfile)[snameOrig]->cd();
			(*cmap_cutProfile)[snameOrig]->cd(1);
			(*h2map_cutProfile)[sname]->Draw("BOX");
		}
		else if(sNumber=="2")
		{
			snameOrig = "cutProfile_" + sname.substr(0, sname.length()-2);
			(*cmap_cutProfile)[snameOrig]->cd(2);
			(*h2map_cutProfile)[sname]->Draw("BOX");
			(*cmap_cutProfile)[snameOrig]->Update();
			(*cmap_cutProfile)[snameOrig]->Write();
		}
		else
		{
			snameOrig = "cutProfile_" + sname;
			cmap_cutProfile->insert( make_pair( snameOrig, new TCanvas(snameOrig.c_str(),snameOrig.c_str(), canv_x,canv_y) ) );
			(*cmap_cutProfile)[snameOrig]->Draw();
			(*cmap_cutProfile)[snameOrig]->cd();
			(*h2map_cutProfile)[sname]->Draw("BOX");
			(*cmap_cutProfile)[snameOrig]->Update();
			(*cmap_cutProfile)[snameOrig]->Write();
		}
		cout << "drawn cutProfile: " << sname << endl;
	}
}








