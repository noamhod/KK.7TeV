/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#define analysisModules_cxx
#include "analysisModules.C"

#ifndef COMBINEDGRAPHICS_H
#define COMBINEDGRAPHICS_H

class combinedGraphics : public analysisModules
{
	public:
		TFile* hFile;
	
		// integrated luminosity of the data in 1/pb
		TMapsd period2lumiMap;
		double dataLumi_ipb;
		string m_dataAnalysisSelector;
		string m_mcAnalysisSelector;
	
	/*
		// cutFlowHandler
		cutFlowHandler* m_cutFlowHandler;
		TMapsvd* m_cutFlowMapSVD;
		TMapds*  m_cutFlowOrdered;
		TMapds*  m_cutFlowTypeOrdered;
		TMapsi*  m_cutFlowNumbers;
	*/	
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
		
		// pads
		TVirtualPad* pad_imass;
		TVirtualPad* pad_imass_ratio;
		TVirtualPad* pad_pT;
		TVirtualPad* pad_pT_ratio;
		
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
		TH1D* hbbmu15X;
		TH1D* hccmu15X;
		TH1D* hDYmumu;
		TH1D* hDYtautau;
		TH1D* hWW;
		TH1D* hZprime_mumu_SSM1000;
		TH1D* hZprime_mumu_SSM1250;
		TH1D* hZprime_mumu_SSM1500;
		TH1D* hZprime_mumu_SSM1750;
		TH1D* hZprime_mumu_SSM2000;
		
		TH1D* hRat;
		TH1D* hRatUp;
		TH1D* hRatDwn;
		
		// TLines
		TLine* lUnit;
		TLine* lLowBound;
	
		// colors
		vector<Color_t>* vcolors;
	
	public:
		combinedGraphics();
		combinedGraphics( string sCutFlowFilePath, string sPeriodsFilePath, string sEventDumpFilePath, string sAnalysisSelector, TFile* hfile) :
		analysisModules(sCutFlowFilePath,sPeriodsFilePath,sEventDumpFilePath)
		{
			hFile = hfile;
			initialize(sAnalysisSelector);
		}
		~combinedGraphics();
		void initialize(string analysisSelector);
		
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
		
		void relDiff(TH1D* hInp, TH1D* hRef, TH1D* hRelDiffPos, TH1D* hRelDiffNeg);
		void ratio(double xmin, double xmax, TH1D* hInp, TH1D* hRef, TH1D* hRat, TH1D* hRatUp, TH1D* hRatDwn);
		void drawRatio(double xmin, double xmax, TH1D* hRat);
		void drawRatioWithBand(double xmin, double xmax, TH1D* hRat, TH1D* hRatUp, TH1D* hRatDwn);
		
		void getHistosMap(TFile* f, string dir, TMapds* cutFlowOrdered, TMapds* cutFlowTypeOrdered);
		void drawNormHistosMap(string channel, TMapds* cutFlowOrdered, TMapds* cutFlowTypeOrdered);
		
		TH1D* getNormDYmumu(string sHistName);
		TH1D* getNormDYtautau(string sHistName);
		
		void drawMCcutFlow();
		void drawDataCutFlow();
		void drawimass();
		void drawpT();
	
	private:
};
#endif

