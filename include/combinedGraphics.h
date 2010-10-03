/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#define cutFlowHandler_cxx
#include "cutFlowHandler.C"

#ifndef COMBINEDGRAPHICS_H
#define COMBINEDGRAPHICS_H

class combinedGraphics : public utilities
{
	public:
	
		// cutFlowHandler
		cutFlowHandler* m_cutFlowHandler;
		TMapsvd* m_cutFlowMapSVD;
		TMapds*  m_cutFlowOrdered;
		TMapds*  m_cutFlowTypeOrdered;
		TMapsi*  m_cutFlowNumbers;
		
		// map of histos
		TMapSP2TH1D* hmap_cutFlow_imass;
		TMapSP2TH1D* hmap_cutFlow_pT;
		
		// legends for the cut flow histod
		TLegend* leg_cutFlow_imass;
		TLegend* leg_imass;
		TLegend* leg_cutFlow_pT;
		TLegend* leg_pT;
		
		// canvases for cut flows
		TCanvas* cnv_cutFlow_imass;
		TCanvas* cnv_MC_cutFlow_imass;
		TCanvas* cnv_data_cutFlow_imass;
		TCanvas* cnv_imass;
		TCanvas* cnv_cutFlow_pT;
		TCanvas* cnv_MC_cutFlow_pT;
		TCanvas* cnv_data_cutFlow_pT;
		TCanvas* cnv_pT;
		
		// for the canvases
		Int_t    canv_x;
		Int_t    canv_y;
	
		// for the legends
		Double_t leg_x1;
		Double_t leg_x2;
		Double_t leg_y1;
		Double_t leg_y2;
		
		// lumi norm
		double m_crossSection_pb;
		double m_branchingRatio;
		double m_nMCevents;
		double m_dataLumi_pb;
		
		// histos
		TH1D* hData;
		TH1D* hMCimass;
		TH1D* hMCpT;
		TH1D* hZmumu;
		TH1D* hWmunu;
		TH1D* hZtautau;
		TH1D* hTTbar;
		TH1D* hbbmuX15;
		TH1D* hccmuX15;
		
	
		// colors
		vector<Color_t>* vcolors;
	
	public:
		combinedGraphics();
		combinedGraphics(cutFlowHandler* cutFlowHandler);
		~combinedGraphics();
		
		TCanvas* getCanvas(TFile* f, string dir, string cname);
		TH1D*    getHisto(TFile* f, string dir, string hname);
		void fixHisto(TH1D* h);
		void NormToBinWidth(TH1D* h);
		double Integral(TH1D* h);
		double IntegralOverFlow(TH1D* h);
		void Scale(TH1D* h, double d);
		void Norm(TH1D* h);
		void NormToDataLumi(TH1D* h, double crossSection_pb, double branchingRatio, double nMCevents, double dataLumi_pb);
		void setNormVals(double crossSection_pb, double branchingRatio, double nMCevents, double dataLumi_pb);
		
		void getHistosMap(TFile* f, string dir, TMapds* cutFlowOrdered, TMapds* cutFlowTypeOrdered);
		void drawNormHistosMap(string channel, TMapds* cutFlowOrdered, TMapds* cutFlowTypeOrdered);
		
		void drawMCcutFlow();
		void drawDataCutFlow();
		void drawimass();
		void drawpT();
	
	private:
};
#endif

