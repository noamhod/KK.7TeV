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
		
		// colors
		vector<Color_t>* vcolors;
	
		// integrated luminosity of the data in 1/pb
		TMapsd period2lumiMap;
		
		TMapsd mcProc2sigma;
		TMapsd mcProc2br;
		TMapsd mcProc2kfactor;
		TMapsd mcProc2geneff;
		TMapsi mcProc2nevents;
		
		double dataLumi_ipb;
		string m_muonSelector;
		string m_dataAnalysisSelector;
		string m_mcAnalysisSelector;
		
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
		double m_kFactor;
		double m_genEff;
		double m_dataLumi_pb;
		
		// canvas properties
		Double_t m_miny;
		Double_t m_maxy;
		Double_t m_minratiox;
		bool     m_logx;
		bool     m_logy;
	
	public:
		combinedGraphics();
		combinedGraphics(string sCutFlowFilePath,
						 string sPeriodsFilePath,
						 string sEventDumpFilePath,
						 string sAnalysisSelector,
						 string muonSelector,
						 TFile* hfile) :
		analysisModules(sCutFlowFilePath,sPeriodsFilePath,sEventDumpFilePath)
		{
			hFile = hfile;
			initialize(sAnalysisSelector, muonSelector);
		}
		~combinedGraphics();
		void initialize(string analysisSelector, string muonSelector);
		
		TCanvas* getCanvas(TFile* f, string dir, string cname);
		TH1D*    getHisto(TFile* f, string dir, string hname);
		void fixHisto(TH1D* h);
		void NormToBinWidth(TH1D* h);
		double Integral(TH1D* h);
		double IntegralOverFlow(TH1D* h);
		void Scale(TH1D* h, double d);
		void Norm(TH1D* h);
		void NormToDataLumi(TH1D* h,
							double crossSection_pb,
							double branchingRatio,
							double nMCevents,
							double kFactor,
							double genEff,
							double dataLumi_pb);
		void setNormVals(double crossSection_pb,
						 double branchingRatio,
						 double nMCevents,
						 double kFactor,
						 double genEff,
						 double dataLumi_pb);
		
		void relDiff(TH1D* hInp, TH1D* hRef, TH1D* hRelDiffPos, TH1D* hRelDiffNeg);
		void ratio(double xmin, double xmax, TH1D* hInp, TH1D* hRef, TH1D* hRat, TH1D* hRatUp, TH1D* hRatDwn);
		void drawRatio(double xmin, double xmax, TH1D* hRat);
		void drawRatioWithBand(double xmin, double xmax, TH1D* hRat, TH1D* hRatUp, TH1D* hRatDwn);
		
		TH1D* getNormDYmumu(string sHistName);
		TH1D* getNormDYtautau(string sHistName);
		
		TH1D* setRegularMChisto(string sProc, string channel, string path, string hdir, string hName, Color_t color);
		
		void set_MCvsData(bool logx = false, bool logx = false, Double_t min = 0., Double_t max = 0., Double_t minratiox = 0.);
		void draw_MCvsData(string dir, string hDir, string hName, string xTitle, string yTitle);
	
	private:
};
#endif

