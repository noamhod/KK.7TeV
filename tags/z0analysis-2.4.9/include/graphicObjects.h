/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#ifndef GRAPHICOBJECTS_H
#define GRAPHICOBJECTS_H

class graphicObjects// : public utilities
{
	public:
		// canvases
		TCanvas* cnv_imass;
		TCanvas* cnv_pT;
		TCanvas* cnv_eta;
		TCanvas* cnv_costh;
		TCanvas* cnv_d0exPV;
		TCanvas* cnv_z0exPV;
		TCanvas* cnv_cosmicCosth;
		TCanvas* cnv_xyVertex;
		TCanvas* cnv_imassFit;
		TCanvas* cnv_ipTdiff;
		TCanvas* cnv_etaSum;
		TCanvas* cnv_pTdiff;
		TCanvas* cnv_pTratio;
		TCanvas* cnv_pTmevspTid;
		TCanvas* cnv_Afb;
		TCanvas* cnv_efficiency_pT;
		TCanvas* cnv_efficiency_eta;
		TCanvas* cnv_efficiency_phi;
		
		// pads
		TVirtualPad* pad_pT;
		TVirtualPad* pad_eta;
		TVirtualPad* pad_pT_muplus;
		TVirtualPad* pad_eta_muplus;
		TVirtualPad* pad_cosmicCosth;
		TVirtualPad* pad_cosmicCosthAllCuts;
		TVirtualPad* pad_pTdiff;
		TVirtualPad* pad_pTdiff_muplus;
		TVirtualPad* pad_pTratio;
		TVirtualPad* pad_pTratio_muplus;
		TVirtualPad* pad_pTmevspTid;
		TVirtualPad* pad_pTmevspTid_muplus;
		TVirtualPad* pad_candidates_pT;
		TVirtualPad* pad_succeeded_pT;
		TVirtualPad* pad_efficiency_pT;
		TVirtualPad* pad_candidates_eta;
		TVirtualPad* pad_succeeded_eta;
		TVirtualPad* pad_efficiency_eta;
		TVirtualPad* pad_candidates_phi;
		TVirtualPad* pad_succeeded_phi;
		TVirtualPad* pad_efficiency_phi;

		// histos
		TH1D* h1_imass;
		TH1D* h1_pT;
		TH1D* h1_pT_muplus;
		TH1D* h1_eta;
		TH1D* h1_eta_muplus;
		TH1D* h1_costh;
		TH1D* h1_d0exPV;
		TH1D* h1_z0exPV;
		TH1D* h1_cosmicCosth;
		TH1D* h1_cosmicCosthAllCuts;
		TH2D* h2_xyVertex;
		TH1D* h1_imassFit;
		TH1D* h1_ipTdiff;
		TH1D* h1_etaSum;
		TH1D* h1_pTdiff;
		TH1D* h1_pTdiff_muplus;
		TH1D* h1_pTratio;
		TH1D* h1_pTratio_muplus;
		TH2D* h2_pTmevspTid;
		TH2D* h2_pTmevspTid_muplus;
		TH1D* h1_Afb;
		
		// For the graphs
		Int_t nentries;
		TCanvas* cMemoryMonitor;
		TGraph*  gResMemoryMonitor;
		TGraph*  gVirMemoryMonitor;
		Double_t* resMemoryArray;
		Double_t* virMemoryArray;
		Double_t* entryArray;

		// canvases for cut flows
		TCanvas* cnv_cutFlow_imass;
		TCanvas* cnv_cutFlow_pT;

		// legends for the cut flow histod
		TLegend* leg_cutFlow_imass;
		TLegend* leg_cutFlow_pT;
		TLegend* leg_imassFit;
		TLegend* leg_ipTdiff;
		TLegend* leg_memory;

		// map of histos
		TMapSP2TH1D* h1map_cutProfile;
		TMapSP2TH2D* h2map_cutProfile;
		TMapSP2TH1D* hmap_cutFlow_imass;
		TMapSP2TH1D* hmap_cutFlow_pT;
		
		TMapSP2TH1D* h1map_tagNprobe_candidates_pT;
		TMapSP2TH1D* h1map_tagNprobe_succeeded_pT;
		TMapSP2TH1D* h1map_tagNprobe_trigEff_pT;
		TMapSP2TH1D* h1map_tagNprobe_candidates_eta;
		TMapSP2TH1D* h1map_tagNprobe_succeeded_eta;
		TMapSP2TH1D* h1map_tagNprobe_trigEff_eta;
		TMapSP2TH1D* h1map_tagNprobe_candidates_phi;
		TMapSP2TH1D* h1map_tagNprobe_succeeded_phi;
		TMapSP2TH1D* h1map_tagNprobe_trigEff_phi;
		
		TMapSP2TH1D* h1map_truth_candidates_pT;
		TMapSP2TH1D* h1map_truth_succeeded_pT;
		TMapSP2TH1D* h1map_truth_trigEff_pT;
		TMapSP2TH1D* h1map_truth_candidates_eta;
		TMapSP2TH1D* h1map_truth_succeeded_eta;
		TMapSP2TH1D* h1map_truth_trigEff_eta;
		TMapSP2TH1D* h1map_truth_candidates_phi;
		TMapSP2TH1D* h1map_truth_succeeded_phi;
		TMapSP2TH1D* h1map_truth_trigEff_phi;
		
		// map of canvases
		TMapSP2TCNV* cmap_cutProfile;
		
		// map of cutFlow
		TMapsvd* cut_cutFlowMapSVD;
		
		// for the canvases
		Int_t    canv_x;
		Int_t    canv_y;
	
		// for the legends
		Double_t leg_x1;
		Double_t leg_x2;
		Double_t leg_y1;
		Double_t leg_y2;
			
		// for the histos
		Int_t    imass_nbins;
		Double_t imass_min;
		Double_t imass_min_cut;
		Double_t imass_max;
		Double_t imass_max_cut;
		
		Int_t imass_fit_nbins;
		Double_t imass_fit_min;
		Double_t imass_fit_max;

		Int_t    pT_nbins;
		Double_t pT_min;
		Double_t pT_min_cut;
		Double_t pT_max;
		Double_t pT_max_cut;
		
		// logarithmic boundries and bins of histograms
		Double_t logMmin;
		Double_t logMmin_cut;
		Double_t logMmax;
		Double_t logMmax_cut;
		Double_t M_binwidth;
		Double_t M_binwidth_cut;
		Double_t M_bins[100+1]; // M_bins[imass_nbins+1]; !!!!!!!!!!!!
		Double_t M_bins_cut[100+1]; // M_bins[imass_nbins+1]; !!!!!!!!!!!!

		Double_t logpTmin;
		Double_t logpTmin_cut;
		Double_t logpTmax;
		Double_t logpTmax_cut;
		Double_t pT_binwidth;
		Double_t pT_binwidth_cut;
		Double_t pT_bins[100+1]; //pT_bins[pT_nbins+1]; !!!!!!!!!!!!!!!
		Double_t pT_bins_cut[100+1]; //pT_bins[pT_nbins+1]; !!!!!!!!!!!!!!!
		
		Int_t phi_nbins;
		Double_t phi_min;
		Double_t phi_max;
		
		Int_t eta_nbins;
		Double_t eta_min;
		Double_t eta_max;
		
		Int_t costh_nbins;
		Double_t costh_min;
		Double_t costh_max;

		Int_t d0exPV_nbins;
		Double_t d0exPV_min;
		Double_t d0exPV_max;
	
		Int_t z0exPV_nbins;
		Double_t z0exPV_min;
		Double_t z0exPV_max;

		Int_t cosmicCosth_nbins;
		Double_t cosmicCosth_min;
		Double_t cosmicCosth_max;

		Int_t xyVertex_nbins;
		Double_t xyVertex_min;
		Double_t xyVertex_max;
	
		Int_t ipTdiff_nbins;
		Double_t ipTdiff_min;
		Double_t ipTdiff_max;
		
		Int_t etaSum_nbins;
		Double_t etaSum_min;
		Double_t etaSum_max;
		
		Int_t pTdiff_nbins;
		Double_t pTdiff_min;
		Double_t pTdiff_max;
		
		Int_t pTratio_nbins;
		Double_t pTratio_min;
		Double_t pTratio_max;
		
		Int_t pTmevspTid_nbins;
		Double_t pTmevspTid_min;
		Double_t pTmevspTid_max;
		
		Int_t Afb_nbins;
		Double_t Afb_min;
		Double_t Afb_max;
		
		Int_t tagNprobe_pT_nbins;
		Double_t tagNprobe_pT_min;
		Double_t tagNprobe_pT_max;
	
	public:
		graphicObjects();
		~graphicObjects();

		void ginitialize();
		void gfinalize();

		void setStyle();
		
		void setCutFlowMapSVDPtr(TMapsvd* cutFlowMapSVD);

		void bookBareHistos(TDirectory* tdir);
		void drawBareHistos(TDirectory* tdir);
		
		void bookEfficiencyHistos(TMapss* period2triggerperiodMap, TDirectory* tdir);
		void drawEfficiencyHistosMap(TDirectory* tdir);

		void bookHistos(TDirectory* tdir);
		void drawHistos(TDirectory* tdir);

		void bookFitHistos(TDirectory* tdir);
		void drawFitHistos(TDirectory* tdir, TF1* fGuess, TF1* fFitted);

		void bookHistosMap(TMapds* cutFlowOrdered, TMapds* cutFlowTypeOrdered, TDirectory* tdir);
		void drawHistosMap(TMapds* cutFlowOrdered, TMapds* cutFlowTypeOrdered, TDirectory* tdir);
		
		void bookCutProfileHistosMap(TMapds* cutFlowOrdered, TDirectory* tdir);
		void drawCutProfileHistosMap(TDirectory* tdir);
		
		void drawPerformance(vector<int>& vEntries, vector<double>& vResMemory, vector<double>& vVirMemory, TDirectory* tdir);

	private:

};
#endif

