/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#ifndef GRAPHICOBJECTS_H
#define GRAPHICOBJECTS_H

class graphicObjects : public utilities
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
		
		// pads
		TVirtualPad* pad_pT;
		TVirtualPad* pad_eta;
		TVirtualPad* pad_pT_muplus;
		TVirtualPad* pad_eta_muplus;
		TVirtualPad* pad_cosmicCosth;
		TVirtualPad* pad_cosmicCosthAllCuts;

		// histos
		TH1D*    h1_imass;
		TH1D*    h1_pT;
		TH1D*    h1_pT_muplus;
		TH1D*    h1_eta;
		TH1D*    h1_eta_muplus;
		TH1D*    h1_costh;
		TH1D*    h1_d0exPV;
		TH1D*    h1_z0exPV;
		TH1D*    h1_cosmicCosth;
		TH1D*    h1_cosmicCosthAllCuts;
		TH2D*    h2_xyVertex;
		TH1D*    h1_imassFit;
		TH1D*    h1_ipTdiff;
		TH1D*    h1_etaSum;

		// canvases for cut flows
		TCanvas* cnv_cutFlow_imass;
		TCanvas* cnv_cutFlow_pT;

		// legends for the cut flow histod
		TLegend* leg_cutFlow_imass;
		TLegend* leg_cutFlow_pT;
		TLegend* leg_imassFit;
		TLegend* leg_ipTdiff;

		// map of histos
		TMapSP2TH1D* hmap_cutFlow_imass;
		TMapSP2TH1D* hmap_cutFlow_pT;

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
		Double_t imass_max;
		
		Int_t imass_fit_nbins;
		Double_t imass_fit_min;
		Double_t imass_fit_max;

		Int_t    pT_nbins;
		Double_t pT_min;
		Double_t pT_max;
		
		// logarithmic boundries and bins of histograms
		Double_t logMmin ;
		Double_t logMmax;
		Double_t M_binwidth;
		Double_t M_bins[100+1]; // M_bins[imass_nbins+1]; !!!!!!!!!!!!

		Double_t logpTmin;
		Double_t logpTmax;
		Double_t pT_binwidth;
		Double_t pT_bins[100+1]; //pT_bins[pT_nbins+1]; !!!!!!!!!!!!!!!
		
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
	
	public:
		graphicObjects();
		~graphicObjects();

		void ginitialize();
		void gfinalize();

		void setStyle();

		void bookBareHistos(TDirectory* tdir);
		void drawBareHistos(TDirectory* tdir);

		void bookHistos(TDirectory* tdir);
		void drawHistos(TDirectory* tdir);

		void bookFitHistos(TDirectory* tdir);
		void drawFitHistos(TDirectory* tdir, TF1* fGuess, TF1* fFitted);

		void bookHistosMap(TMapds* cutFlowOrdered, TMapds* cutFlowTypeOrdered, TDirectory* tdir);
		void drawHistosMap(TMapds* cutFlowOrdered, TMapds* cutFlowTypeOrdered, TDirectory* tdir);

	private:

};
#endif

