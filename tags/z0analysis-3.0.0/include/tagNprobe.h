/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#ifndef TAGNPROBE_H
#define TAGNPROBE_H

class tagNprobe
{
	public:
		kinematics kin;
	
		float mHat;
		float mHatDiffThreshold;
		float Q1xQ2;
		float pTtag;
		float pTprobe;
		float dRbest;
		float dRthreshold;
		float muTrig_dRthreshold;
		float mu_dRthreshold;
		int   truth_pTmaxIndex;
		int   recon_pTmaxIndex;
		int   tagIndex;
		int   probeIndex;
		int   triggerIndex;
		bool  isTag;
		bool  isProbe;
		bool  isProbeCandidate;
	
	public:
		tagNprobe();
		~tagNprobe();

		void reset();
		
		//------- for rel 16 ------------------------------------------------------------
		int matchLXtrigger(int mu_ROIindex,
						   float mu_dR,
						   float mu_phi,
						   float mu_eta,
						   float pTthreshold,
						   vector<float>*  trig_phi,
						   vector<float>*  trig_eta,
						   vector<float>*  trig_pt,
						   vector<string>* trig_thresholdName, ofstream* f);
		int matchEFtrigger(int mu_ROIindex,
						   float mu_dR,
						   float mu_phi,
						   float mu_eta,
						   float pTthreshold,
						   vector<vector<float> >* trig_phi,
						   vector<vector<float> >* trig_eta,
						   vector<vector<float> >* trig_pt,
						   vector<vector<int> >*   trig_has, ofstream* f);
		//-------------------------------------------------------------------------------  
									 
		bool findTag(vector<int>* trigger_match, vector<float>* dR);
		int  findProbe(vector<int>* trigger_match, TVectorP2VL& pmu, vector<float>* charge, int itag);
		int  tagNprobeMask(int wasEventTriggered, vector<int>* trigger_match, vector<float>* dR,
						   TVectorP2VL& pmu, vector<float>* charge, int& itag, int& iprobe);
		int  tagNprobeMask(float trigger_min, float trigger_threshold, vector<float>* trigger_pT, vector<int>* trigger_match,
						   TVectorP2VL& pmu, vector<float>* qOp, vector<float>* theta, vector<float>* charge,
						   int& itag, int& iprobe);
		void calculateEfficiency(TH1D* hCandidates, TH1D* hSucceeded, TH1D* hEfficiency, bool isTruth);
		void calculateEfficiency(TH2D* hCandidates, TH2D* hSucceeded, TH2D* hEfficiency, bool isTruth);
		void calculateEfficiency(TMapSP2TH1D* hMapCandidates, TMapSP2TH1D* hMapSucceeded, TMapSP2TH1D* hMapEfficiency, bool isTruth);

		
	private:
};
#endif


