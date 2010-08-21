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

		// histos
		TH1D*    h1_imass;
		TH1D*    h1_pT;
		TH1D*    h1_eta;
		TH1D*    h1_costh;
		TH1D*    h1_d0exPV;
		TH1D*    h1_z0exPV;
		TH1D*    h1_cosmicCosth;
		TH2D*    h2_xyVertex;

		// canvases for cut flows
		TCanvas* cnv_cutFlow_imass;
		TCanvas* cnv_cutFlow_pT;

		// map of histos
		TMapSP2TH1D* hmap_cutFlow_imass;
		TMapSP2TH1D* hmap_cutFlow_pT;

		// for the canvases
		Int_t    canv_x;
		Int_t    canv_y;
			
		// for the histos
		Int_t    imass_nbins;
		Double_t imass_min;
		Double_t imass_max;

		Int_t    pT_nbins;
		Double_t pT_min;
		Double_t pT_max;
		
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


		void bookHistosMap(TMapsd* cutFlowMap, TMapds* cutFlowOrdered, TDirectory* tdir);
		void drawHistosMap(TMapsd* cutFlowMap, TMapds* cutFlowOrdered, TDirectory* tdir);

	private:

};
#endif
