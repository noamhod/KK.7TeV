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
		bool findTag(vector<int>* trigger_match, vector<float>* dR);
		int  findProbe(vector<int>* trigger_match, TVectorP2VL& pmu, vector<float>* charge, int itag);
		int  tagNprobeMask(int wasEventTriggered, vector<int>* trigger_match, vector<float>* dR,
						   TVectorP2VL& pmu, vector<float>* charge, int& itag, int& iprobe);
		int  tagNprobeMask(float trigger_min, float trigger_threshold, vector<float>* trigger_pT, vector<int>* trigger_match,
						   TVectorP2VL& pmu, vector<float>* qOp, vector<float>* theta, vector<float>* charge,
						   int& itag, int& iprobe);
		void calculateEfficiency(TH1D* hCandidates, TH1D* hSucceeded, TH1D* hEfficiency, bool isTruth);
		
	private:
};
#endif


