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
	
		// thresholds
		float dRmax_mu_L1;
		float dRmax_mu_EF;
		float dRmax_mu_trig;
		float dRmax_muTrk_trigTrk;
		float mu_pTmin;
		float mu_pTmax;
		float dd0max_muTag_muProb;
		float dz0max_muTag_muProb;
		float dphimax_muTag_muProb;
		float dMmax_muTag_muProb;
		
		// locals
		vector<int> m_viProbes;
	
	public:
		tagNprobe();
		~tagNprobe();
		
		int matchLXtrigger(int mu_ROIindex,
						   float mu_dR,
						   float mu_phi,
						   float mu_eta,
						   float pTthreshold,
						   vector<float>*  trig_phi,
						   vector<float>*  trig_eta,
						   vector<float>*  trig_pt,
						   vector<string>* trig_thresholdName);
		int matchEFtrigger(int mu_ROIindex,
						   float mu_dR,
						   float mu_phi,
						   float mu_eta,
						   float pTthreshold,
						   vector<vector<float> >* trig_phi,
						   vector<vector<float> >* trig_eta,
						   vector<vector<float> >* trig_pt,
						   vector<vector<int> >*   trig_has);
		
		// tagMask for HLT
		int tagMask
		(
			string sTrigName, string sTrigType, float pTtrigThreshold,
			vector<bool>& mu_qaflg,
			int skipMuIndex, int& muTag, int& ROITag, int& trigTrkTag,
			vector<int>*   mu_index,
			vector<float>* mu_dr,
			vector<float>* mu_phi,
			vector<float>* mu_eta,
			vector<float>* mu_pt,
			vector<float>* mu_qoverp,
			vector<float>* mu_theta,
			vector<vector<float> >* trig_phi,
			vector<vector<float> >* trig_eta,
			vector<vector<float> >* trig_pt,
			vector<vector<int> >*   trig_has
		);
		
		// tagMask for LLT
		int tagMask
		(
			string sTrigName, string sTrigType, float pTtrigThreshold,
			vector<bool>& mu_qaflg,
			int skipMuIndex, int& muTag, int& ROITag,
			vector<int>*   mu_index,
			vector<float>* mu_dr,
			vector<float>* mu_phi,
			vector<float>* mu_eta,
			vector<float>* mu_pt,
			vector<float>* mu_qoverp,
			vector<float>* mu_theta,
			vector<float>* trig_phi,
			vector<float>* trig_eta,
			vector<float>* trig_pt
		);
		
		int probeCandMask
		(
			string sTrigType,
			TVectorP2VL& pmu, vector<bool>& mu_qaflg,
			int muTag,
			vector<float>* mu_phi,
			vector<float>* mu_eta,
			vector<float>* mu_pt,
			vector<float>* mu_qoverp,
			vector<float>* mu_theta,
			vector<float>* mu_d0,
			vector<float>* mu_z0,
			vector<float>* mu_charge
		);
		
		// probeMask for HLT
		int probeMask
		(
			int iprobeCand,
			string sTrigName, float pTtrigThreshold,
			vector<bool>& mu_qaflg,
			int muTag, int ROITag, int trigTrkTag,
			int& muProb, int& ROIProb, int& trigTrkProb,
			vector<int>*   mu_index,
			vector<float>* mu_dr,
			vector<float>* mu_phi,
			vector<float>* mu_eta,
			vector<vector<float> >* trig_phi,
			vector<vector<float> >* trig_eta,
			vector<vector<float> >* trig_pt,
			vector<vector<int> >*   trig_has
		);
		
		// probeMask for LLT
		int probeMask
		(
			int iprobeCand,
			string sTrigName, float pTtrigThreshold,
			vector<bool>& mu_qaflg,
			int muTag, int ROITag,
			int& muProb, int& ROIProb,
			vector<int>*   mu_index,
			vector<float>* mu_dr,
			vector<float>* mu_phi,
			vector<float>* mu_eta,
			vector<float>* trig_phi,
			vector<float>* trig_eta,
			vector<float>* trig_pt
		);
		
		void calculateEfficiency(TH1D* hCandidates, TH1D* hSucceeded, TH1D* hEfficiency, bool isTruth);
		void calculateEfficiency(TH2D* hCandidates, TH2D* hSucceeded, TH2D* hEfficiency, bool isTruth);
		void calculateEfficiency(TMapSP2TH1D* hMapCandidates, TMapSP2TH1D* hMapSucceeded, TMapSP2TH1D* hMapEfficiency, bool isTruth);

		
	private:
};
#endif


